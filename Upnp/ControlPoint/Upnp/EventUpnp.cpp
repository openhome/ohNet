#include <EventUpnp.h>
#include <CpiSubscription.h>
#include <Http.h>
#include <ProtocolUpnp.h>
#include <Buffer.h>
#include <Stream.h>
#include <Stack.h>
#include <Debug.h>
#include <XmlParser.h>
#include <CpProxy.h>
#include <ProtocolUpnp.h>
#include <Parser.h>

using namespace OpenHome::Net;

const Brn EventSessionUpnp::kMethodNotify("NOTIFY");
const Brn EventSessionUpnp::kExpectedNt("upnp:event");
const Brn EventSessionUpnp::kExpectedNts("upnp:propchange");

// EventSessionUpnp

EventSessionUpnp::EventSessionUpnp()
{
    iReadBuffer = new Srs<kMaxReadBytes>(*this);
    iReaderRequest = new ReaderHttpRequest(*iReadBuffer);

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
    delete iReadBuffer;
    delete iReaderRequest;
}

void EventSessionUpnp::Error(const HttpStatus& aStatus)
{
    LOG2(kEvent, kError, "EventSessionUpnp::Error ");
    LOG2(kEvent, kError, aStatus.Reason());
    LOG2(kEvent, kError, "\n");
    iErrorStatus = &aStatus;
    THROW(HttpError);
}

#ifdef DEFINE_TRACE
void EventSessionUpnp::LogError(CpiSubscription* aSubscription, const TChar* aErr)
#else
void EventSessionUpnp::LogError(CpiSubscription* aSubscription, const TChar* /*aErr*/)
#endif
{
    LOG2(kEvent, kError, "EventSessionUpnp::Run, %s handling\n    sid - ", aErr);
    LOG2(kEvent, kError, iHeaderSid.Sid());
    LOG2(kEvent, kError, " seq - %u\n", iHeaderSeq.Seq());
    if (aSubscription != NULL) {
        aSubscription->SetNotificationError();
    }
}

void EventSessionUpnp::Run()
{
    CpiSubscription* subscription = NULL;
    iErrorStatus = &HttpStatus::kOk;
    try {
        iReaderRequest->Flush();
        iReaderRequest->Read();
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

        subscription = CpiSubscriptionManager::FindSubscription(iHeaderSid.Sid());
        if (subscription == NULL) {
            /* the UPnP spec contains a potential race condition where the first NOTIFY
               message can be processed ahead of the SUBSCRIBE reply which provides
               the sid.  Wait until any in-progress subscriptions complete and try
               again in case that's what has happened here */
            CpiSubscriptionManager::WaitForPendingAdds();
            subscription = CpiSubscriptionManager::FindSubscription(iHeaderSid.Sid());
            if (subscription == NULL) {
                LOG2(kEvent, kError, "notification for unexpected device - ")
                LOG2(kEvent, kError, iHeaderSid.Sid());
                LOG2(kEvent, kError, "\n");
                Error(HttpStatus::kPreconditionFailed);
            }
        }

        if (!subscription->UpdateSequenceNumber(iHeaderSeq.Seq())) {
            subscription->SetNotificationError();
            subscription->RemoveRef();
            subscription = NULL;
        }
    }
    catch(HttpError) {}
    catch(ReaderError) {}

    try {
        // write response
        Sws<128> writerBuffer(*this);
        WriterHttpResponse response(writerBuffer);
        response.WriteStatus(*iErrorStatus, Http::eHttp11);
        response.WriteFlush();

        // read entity
        if (subscription != NULL) {
            Bwh entity;
            if (iHeaderTransferEncoding.IsChunked()) {
                ReaderHttpChunked dechunker(*iReadBuffer);
                dechunker.Read();
                dechunker.TransferTo(entity);
            }
            else {
                TUint length = iHeaderContentLength.ContentLength();
                if (length == 0) {
                    THROW(HttpError);
                }
                entity.Grow(length);
                while (length > 0) {
                    TUint readBytes = (length<kMaxReadBytes? length : kMaxReadBytes);
                    entity.Append(iReadBuffer->Read(readBytes));
                    length -= readBytes;
                }
            }

            // process entity
            LOG(kEvent, "EventSessionUpnp::Run, sid - ");
            LOG(kEvent, iHeaderSid.Sid());
            LOG(kEvent, " seq - %u\n", iHeaderSeq.Seq());
            ProcessNotification(*subscription, entity);
        }
    }
    catch(HttpError) {
        LogError(subscription, "HttpError");
    }
    catch(ReaderError) {
        LogError(subscription, "ReaderError");
    }
    catch(WriterError) {
        LogError(subscription, "WriterError");
    }
    catch(NetworkError) {
        LogError(subscription, "NetworkError");
    }
    catch(XmlError) {
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
            prop.Set(XmlParserBasic::Find("property", propertySet, remaining));
            prop.Set(Ascii::Trim(prop));
            if (prop.Bytes() < 8 || prop[0] != '<' || prop[1] == '/') {
                THROW(XmlError);
            }
            Parser parser(prop);
            (void)parser.Next('<');
            Brn tagName = parser.Next('>');
            Brn val = parser.Next('<');
            Brn closingTag = parser.Next('/');
            closingTag.Set(parser.Next('>'));
            if (tagName != closingTag) {
                THROW(XmlError);
            }

            try {
                aEventProcessor.EventUpdate(tagName, val, outputProcessor);
            }
            catch(AsciiError&) {
                THROW(XmlError);
            }

            propertySet.Set(remaining);
        }
    }
    catch(XmlError&) {}
    aEventProcessor.EventUpdateEnd();
}

// EventServerUpnp

EventServerUpnp::EventServerUpnp(TIpAddress aInterface)
    : iTcpServer("EVNT", 0, aInterface)
{
    TChar name[5] = "ESS ";
#ifndef _WIN32
    // nothing terribly bad would happen if this assertion failed so its not worth a separate Windows implementation
    ASSERT(Stack::InitParams().NumEventSessionThreads() < 10);
#endif
    for (TUint i=0; i<Stack::InitParams().NumEventSessionThreads(); i++) {
        name[3] = (TChar)('0' + i);
        iTcpServer.Add(&name[0], new EventSessionUpnp());
    }
}
