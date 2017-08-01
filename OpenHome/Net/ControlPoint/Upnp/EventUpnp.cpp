#include <OpenHome/Net/Private/EventUpnp.h>
#include <OpenHome/Net/Private/CpiSubscription.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Net/Private/ProtocolUpnp.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Private/XmlParser.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/ProtocolUpnp.h>
#include <OpenHome/Private/Parser.h>

using namespace OpenHome;
using namespace OpenHome::Net;

const Brn EventSessionUpnp::kMethodNotify("NOTIFY");
const Brn EventSessionUpnp::kExpectedNt("upnp:event");
const Brn EventSessionUpnp::kExpectedNts("upnp:propchange");

// EventSessionUpnp

EventSessionUpnp::EventSessionUpnp(CpStack& aCpStack)
    : iCpStack(aCpStack)
    , iShutdownSem("EVSD", 1)
{
    iReadBuffer = new Srs<1024>(*this);
    iReaderUntil = new ReaderUntilS<1024>(*iReadBuffer);
    iDechunker = new ReaderHttpChunked(*iReaderUntil);
    iReaderRequest = new ReaderHttpRequest(aCpStack.Env(), *iReaderUntil);

    iReaderRequest->AddMethod(kMethodNotify);
    iReaderRequest->AddHeader(iHeaderNt);
    iReaderRequest->AddHeader(iHeaderNts);
    iReaderRequest->AddHeader(iHeaderSid);
    iReaderRequest->AddHeader(iHeaderSeq);
    iReaderRequest->AddHeader(iHeaderContentLength);
    iReaderRequest->AddHeader(iHeaderTransferEncoding);
}

EventSessionUpnp::~EventSessionUpnp()
{
    Interrupt(true);
    iShutdownSem.Wait();

    delete iDechunker;
    delete iReaderUntil;
    delete iReadBuffer;
    delete iReaderRequest;
}

void EventSessionUpnp::Error(const HttpStatus& aStatus)
{
    const Brx& reason = aStatus.Reason();
    LOG_ERROR(kEvent, "EventSessionUpnp::Error %.*s\n", PBUF(reason));
    iErrorStatus = &aStatus;
    THROW(HttpError);
}

#ifdef DEFINE_TRACE
void EventSessionUpnp::LogError(CpiSubscription* aSubscription, const TChar* aErr)
#else
void EventSessionUpnp::LogError(CpiSubscription* aSubscription, const TChar* /*aErr*/)
#endif
{
    const Brx& sid = iHeaderSid.Sid();
    LOG_ERROR(kEvent, "EventSessionUpnp::Run, %s handling\n    sid - %.*s seq - %u\n",
                         aErr, PBUF(sid), iHeaderSeq.Seq());
    if (aSubscription != NULL) {
        aSubscription->SetNotificationError();
    }
}

void EventSessionUpnp::Run()
{
    AutoSemaphore a(iShutdownSem);
    CpiSubscription* subscription = NULL;
    iErrorStatus = &HttpStatus::kOk;
    iDechunker->SetChunked(false);
    iDechunker->ReadFlush();
    try {
        iReaderRequest->Flush();
        iReaderRequest->Read(kReadTimeoutMs);
        // check headers
        if (iReaderRequest->MethodNotAllowed()) {
            Error(HttpStatus::kBadRequest);
        }

        if (!iHeaderNt.Received() || !iHeaderNts.Received()) {
            Error(HttpStatus::kBadRequest);
        }

        if (iHeaderNt.Value() != kExpectedNt || iHeaderNts.Value() != kExpectedNts ||
            !iHeaderSid.Received() || iHeaderSid.Sid().Bytes() == 0 || !iHeaderSeq.Received()) {
            Error(HttpStatus::kPreconditionFailed);
        }

        Parser parser(iReaderRequest->Uri());
        (void)parser.Next('/');
        Brn idBuf = parser.Next('/');
        TUint id = 0;
        try {
            id = Ascii::Uint(idBuf);
        }
        catch (AsciiError&) {
            const Brx& sid = iHeaderSid.Sid();
            LOG_ERROR(kEvent, "notification for %.*s failed to include id in path\n", PBUF(sid));
            Error(HttpStatus::kPreconditionFailed);
        }
        subscription = iCpStack.SubscriptionManager().FindSubscription(id);
        if (subscription == NULL) {
            const Brx& sid = iHeaderSid.Sid();
            LOG_ERROR(kEvent, "notification for unexpected device - %.*s\n", PBUF(sid))
            Error(HttpStatus::kPreconditionFailed);
        }
    }
    catch(HttpError&) {}
    catch(ReaderError&) {}

    try {
        // write response
        Sws<128> writerBuffer(*this);
        WriterHttpResponse response(writerBuffer);
        response.WriteStatus(*iErrorStatus, Http::eHttp11);
        response.WriteFlush();

        // read entity
        if (subscription != NULL) {
            Bwh entity;
            WriterBwh writer(1024);
            if (iHeaderTransferEncoding.IsChunked()) {
                iDechunker->SetChunked(true);
                for (;;) {
                    Brn buf = iDechunker->Read(kMaxReadBytes);
                    writer.Write(buf);
                    if (buf.Bytes() == 0) { // end of stream
                        break;
                    }
                }
            }
            else {
                TUint length = iHeaderContentLength.ContentLength();
                if (length == 0) {
                    // no Content-Length header, so read until remote socket closed (so ReaderError is thrown)
                    try {
                        for (;;) {
                            writer.Write(iReaderUntil->Read(kMaxReadBytes));
                        }
                    }
                    catch (ReaderError&) {
                    }
                } else {
                    TUint remaining = length;
                    do {
                        TUint bytes = remaining;
                        if (bytes > kMaxReadBytes) {
                            bytes = kMaxReadBytes;
                        }
                        Brn buf = iReaderUntil->Read(bytes);
                        remaining -= buf.Bytes();
                        writer.Write(buf);
                    } while (remaining > 0);
                }
            }
            writer.TransferTo(entity);

            // process entity
            {
                const Brx& sid = iHeaderSid.Sid();
                LOG(kEvent, "EventSessionUpnp::Run, sid - %.*s seq - %u\n", PBUF(sid), iHeaderSeq.Seq());
            }

            /* defer validating the seq number till now to avoid holding subscription's lock during
               potentially long-running network reads */
            if (subscription->UpdateSequenceNumber(iHeaderSeq.Seq())) {
                try {
                    ProcessNotification(*subscription, entity);
                }
                catch (Exception& ex) {
                    Log::Print("EventSessionUpnp::Run() unexpected exception %s from %s:%u\n", ex.Message(), ex.File(), ex.Line());
                    ASSERTS(); // ProcessNotification isn't expected to throw
                }
                subscription->Unlock();
            }
            else {
                subscription->SetNotificationError();
            }
        }
    }
    catch(HttpError&) {
        LogError(subscription, "HttpError");
    }
    catch(ReaderError&) {
        LogError(subscription, "ReaderError");
    }
    catch(WriterError&) {
        LogError(subscription, "WriterError");
    }
    catch(NetworkError&) {
        LogError(subscription, "NetworkError");
    }
    catch(XmlError&) {
        LogError(subscription, "XmlError");
    }
    if (subscription != NULL) {
        subscription->RemoveRef();
    }    
}

void EventSessionUpnp::ProcessNotification(IEventProcessor& aEventProcessor, const Brx& aEntity)
{
    aEventProcessor.EventUpdateStart();
    OutputProcessorUpnp outputProcessor;
    Brn propertySet = XmlParserBasic::Find("propertyset", aEntity);
    Brn prop;
    Brn remaining;
    try {
        for (;;) {
            try {
                prop.Set(XmlParserBasic::Find("property", propertySet, remaining));
            }
            catch (XmlError&) {
                // we've successfully processed all <property> tags from aEntity
                break;
            }
            prop.Set(Ascii::Trim(prop));
            if (prop.Bytes() < 8 || prop[0] != '<' || prop[1] == '/') {
                THROW(XmlError);
            }
            Parser parser(prop);
            (void)parser.Next('<');
            Brn tagNameFull = parser.Next('>');
            Brn tagName = tagNameFull;
            TUint bytes = tagNameFull.Bytes();
            TUint i;
            for (i = 0; i < bytes; i++) {
                if (Ascii::IsWhitespace(tagNameFull[i])) {
                    break;
                }
            }
            if (i < bytes) {
                tagName.Set(tagNameFull.Split(0, i));
            }
            Brn val;
            if (bytes > 0 && tagNameFull[bytes-1] == '/') {
                // empty element tag
                val.Set(Brx::Empty());
                if (i == bytes) { // no white space before '/'
                    tagName.Set(tagName.Split(0, bytes-1));
                }
            }
            else {
                val.Set(parser.Next('<'));
                Brn closingTag = parser.Next('/');
                closingTag.Set(parser.Next('>'));
                if (tagName != closingTag) {
                    THROW(XmlError);
                }
            }

            try {
                aEventProcessor.EventUpdate(tagName, val, outputProcessor);
            }
            catch(AsciiError&) {
                THROW(XmlError);
            }

            propertySet.Set(remaining);
        }
        aEventProcessor.EventUpdateEnd();
    }
    catch(XmlError&) {
        aEventProcessor.EventUpdateError();
    }
}

// EventServerUpnp

EventServerUpnp::EventServerUpnp(CpStack& aCpStack, TIpAddress aInterface)
    : iTcpServer(aCpStack.Env(), "EventServer", aCpStack.Env().InitParams()->CpUpnpEventServerPort(), aInterface)
{
    const TUint numThread = aCpStack.Env().InitParams()->NumEventSessionThreads();
    for (TUint i=0; i<numThread; i++) {
        Bws<Thread::kMaxNameBytes+1> thName;
        thName.AppendPrintf("EventSession %d", i);
        thName.PtrZ();
        iTcpServer.Add((const TChar*)thName.Ptr(), new EventSessionUpnp(aCpStack));
    }
}
