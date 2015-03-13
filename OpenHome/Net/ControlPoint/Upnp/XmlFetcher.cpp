#include <OpenHome/Net/Private/XmlFetcher.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Core/OhNet.h>

#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// XmlFetch

void XmlFetch::Set(OpenHome::Uri* aUri, FunctorAsync& aFunctor)
{
    iUri = aUri;
    iFunctor = aFunctor;
    iSequenceNumber = iCpStack.Env().SequenceNumber();
}

void XmlFetch::CheckContactable(OpenHome::Uri* aUri, FunctorAsync& aFunctor)
{
    Set(aUri, aFunctor);
    iCheckContactable = true;
}

XmlFetch::~XmlFetch()
{
    delete iUri;
}

const OpenHome::Uri& XmlFetch::Uri() const
{
    return *iUri;
}

void XmlFetch::SignalCompleted()
{
    FunctorAsync& asyncEndHandler = iCpStack.Env().InitParams()->AsyncEndHandler();
    if (asyncEndHandler) {
        asyncEndHandler(*this);
    }
    ASSERT(iFunctor);
    try {
        iFunctor(*this);
    }
    catch(XmlFetchError&) {
        FunctorAsync& asyncErrorHandler = iCpStack.Env().InitParams()->AsyncErrorHandler();
        if (asyncErrorHandler) {
            asyncErrorHandler(*this);
        }
    }
}

TBool XmlFetch::Error() const
{
    return (iError.Level() != Error::eNone);
}

void XmlFetch::SetError(Error::ELevel aLevel, TUint aCode, const Brx& aDescription)
{
    /* If an error is set repeatedly, assume that the first setter will have had
       access to the most accurate description */
    if (iError.Level() == Error::eNone) {
        iError.Set(aLevel, aCode, aDescription);
    }
}

void XmlFetch::Fetch()
{
    LOG(kXmlFetch, "> XmlFetch::Fetch for ");
    LOG(kXmlFetch, iUri->AbsoluteUri());
    LOG(kXmlFetch, "\n");

    iLock.Wait();
    iSocket.Interrupt(false);
    iLock.Signal();
    iSocket.Open(iCpStack.Env());
    AutoSocket a(iSocket);
    iLock.Wait();
    if (iInterrupted) {
        SetError(Error::eAsync, Error::eCodeInterrupted, Error::kDescriptionAsyncInterrupted);
        iLock.Signal();
        THROW(ReaderError);
    }
    iLock.Signal();
    try {
        const TUint port = (iUri->Port()==Uri::kPortNotSpecified? 80 : iUri->Port());
        Endpoint endpoint(port, iUri->Host());
        TUint timeout = iCpStack.Env().InitParams()->TcpConnectTimeoutMs();
        iSocket.Connect(endpoint, timeout);
        WriteRequest();
        Read();
    }
    catch (NetworkTimeout&) {
        SetError(Error::eSocket, Error::eCodeTimeout, Error::kDescriptionSocketTimeout);
    }
    catch (HttpError&) {
        SetError(Error::eHttp, Error::kCodeUnknown, Error::kDescriptionUnknown);
    }
    catch (WriterError&) {
        SetError(Error::eSocket, Error::kCodeUnknown, Error::kDescriptionUnknown);
    }
    catch (ReaderError&) {
        SetError(Error::eSocket, Error::kCodeUnknown, Error::kDescriptionUnknown);
    }

    LOG(kXmlFetch, "< XmlFetch::Fetch for ");
    LOG(kXmlFetch, iUri->AbsoluteUri());
    LOG(kXmlFetch, "\n");
}

void XmlFetch::Interrupt()
{
    iLock.Wait();
    iInterrupted = true;
    iSocket.Interrupt(true);
    iLock.Signal();
}

TBool XmlFetch::Interrupted() const
{
    TBool ret;
    iLock.Wait();
    ret = iInterrupted;
    iLock.Signal();
    return ret;
}

Bwh& XmlFetch::Xml(IAsync& aAsync)
{ // static
    ASSERT(((Async&)aAsync).Type() == Async::eXmlFetch);
    XmlFetch& self = (XmlFetch&)aAsync;
    if (self.Error()) {
        THROW(XmlFetchError);
    }
    return self.iXml;
}

TBool XmlFetch::WasContactable(IAsync& aAsync)
{ // static
    ASSERT(((Async&)aAsync).Type() == Async::eXmlFetch);
    XmlFetch& self = (XmlFetch&)aAsync;
    if (self.Error()) {
        THROW(XmlFetchError);
    }
    return self.iContactable;
}

XmlFetch::XmlFetch(CpStack& aCpStack)
    : iCpStack(aCpStack)
    , iUri(NULL)
    , iSequenceNumber(0)
    , iLock("XMLM")
    , iInterrupted(false)
    , iCheckContactable(false)
    , iContactable(false)
    , iReadBuffer(iSocket)
    , iReaderUntil(iReadBuffer)
    , iDechunker(iReaderUntil)
{
}

void XmlFetch::WriteRequest()
{
    Sws<kRwBufferLength> writeBuffer(iSocket);
    WriterHttpRequest writerRequest(writeBuffer);

    writerRequest.WriteMethod((iCheckContactable? Http::kMethodHead : Http::kMethodGet), iUri->PathAndQuery(), Http::eHttp11);
    const TUint port = (iUri->Port()==Uri::kPortNotSpecified? 80 : iUri->Port());
    Http::WriteHeaderHostAndPort(writerRequest, iUri->Host(), port);
    Http::WriteHeaderContentLength(writerRequest, 0);
    Http::WriteHeaderConnectionClose(writerRequest);
    writerRequest.WriteFlush();
}

void XmlFetch::Read()
{
    iDechunker.ReadFlush();
    ReaderHttpResponse readerResponse(iCpStack.Env(), iReaderUntil);
    HttpHeaderContentLength headerContentLength;
    HttpHeaderTransferEncoding headerTransferEncoding;

    readerResponse.AddHeader(headerContentLength);
    readerResponse.AddHeader(headerTransferEncoding);
    readerResponse.Read(kResponseTimeoutMs);
    const HttpStatus& status = readerResponse.Status();
    if (status != HttpStatus::kOk) {
        LOG2(kXmlFetch, kError, "XmlFetch::Read, http error %u ", status.Code());
        LOG2(kXmlFetch, kError, status.Reason());
        LOG2(kXmlFetch, kError, "\n");
        SetError(Error::eHttp, status.Code(), status.Reason());
        THROW(HttpError);
    }
    if (iCheckContactable) {
        iContactable = true;
        return;
    }

    WriterBwh writer(1024);
    static const TUint kMaxReadBytes = 4 * 1024;
    if (headerTransferEncoding.IsChunked()) {
        iDechunker.SetChunked(true);
        for (;;) {
            Brn buf = iDechunker.Read(kMaxReadBytes);
            writer.Write(buf);
            if (buf.Bytes() == 0) { // end of stream
                break;
            }
        }
    }
    else {
        TUint remaining = headerContentLength.ContentLength();
        if (remaining == 0) { // no content length - read until connection closed by server
            try {
                for (;;) {
                    writer.Write(iReaderUntil.Read(kMaxReadBytes));
                }
            }
            catch (ReaderError&) {
            }
        }
        else {
            do {
                Brn buf = iReaderUntil.Read(kMaxReadBytes);
                remaining -= buf.Bytes();
                writer.Write(buf);
            } while (remaining > 0);
        }
    }
    writer.TransferTo(iXml);
}

void XmlFetch::Output(IAsyncOutput& aConsole)
{
    Mutex& lock = iCpStack.Env().Mutex();
    lock.Wait();
    Bws<Ascii::kMaxUintStringBytes+1> buf;
    (void)Ascii::AppendDec(buf, iSequenceNumber);
    buf.PtrZ();
    aConsole.Output("SequenceNumber", (const TChar*)buf.Ptr());
    Bws<Uri::kMaxUriBytes+1> uri(iUri->AbsoluteUri());
    uri.PtrZ();
    aConsole.Output("XmlFetch", (const TChar*)uri.Ptr());
    if (Error()) {
        iError.Output(aConsole);
    }
    lock.Signal();
}

TUint XmlFetch::Type() const
{
    return Async::eXmlFetch;
}


// XmlFetcher

XmlFetcher::XmlFetcher(const TChar* aName, Fifo<XmlFetcher*>& aFree)
    : Thread(aName)
    , iFree(aFree)
{
}

XmlFetcher::~XmlFetcher()
{
    Kill();
    Join();
}

void XmlFetcher::Fetch(XmlFetch* aFetch)
{
    iFetch = aFetch;
    Signal();
}

#ifdef DEFINE_TRACE
void XmlFetcher::LogError(const TChar* aErr)
#else
void XmlFetcher::LogError(const TChar* /*aErr*/)
#endif
{
    LOG2(kXmlFetch, kError, "Error - %s - from ", aErr);
    LOG2(kXmlFetch, kError, iFetch->Uri().AbsoluteUri());
    LOG2(kXmlFetch, kError, "\n");
}

void XmlFetcher::Run()
{
    for (;;) {
        Wait();
        try {
            if (iFetch->Interrupted()) {
                iFetch->SetError(Error::eAsync, Error::eCodeInterrupted,
                                 Error::kDescriptionAsyncInterrupted);
            }
            else {
                iFetch->Fetch();
            }
        }
        catch (HttpError&) {
            LogError("Http");
        }
        catch (NetworkTimeout&) {
            // error already set in XmlFetch::Fetch()
            LogError("NetworkTimeout");
        }
        catch (NetworkError&) {
            iFetch->SetError(Error::eSocket, Error::kCodeUnknown, Error::kDescriptionUnknown);
            LogError("Network");
        }
        catch (WriterError&) {
            LogError("Writer");
        }
        catch (ReaderError&) {
            iFetch->SetError(Error::eSocket, Error::kCodeUnknown, Error::kDescriptionUnknown);
            LogError("Reader");
        }
        iFetch->SignalCompleted();
        delete iFetch;
        iFetch = NULL;

        iFree.Write(this);
    }
}


// XmlFetchManager

XmlFetchManager::XmlFetchManager(CpStack& aCpStack)
    : Thread("XmlFetchManager")
    , iCpStack(aCpStack)
    , iLock("FETL")
    , iFree(iCpStack.Env().InitParams()->NumXmlFetcherThreads())
{
    const TUint numThreads = iCpStack.Env().InitParams()->NumXmlFetcherThreads();
    iFetchers = (XmlFetcher**)malloc(sizeof(*iFetchers) * numThreads);
    for (TUint i=0; i<numThreads; i++) {
        Bws<Thread::kMaxNameBytes+1> thName;
        thName.AppendPrintf("XmlFetcher %d", i);
        thName.PtrZ();
        iFetchers[i] = new XmlFetcher((const TChar*)thName.Ptr(), iFree);
        iFree.Write(iFetchers[i]);
        iFetchers[i]->Start();
    }

    iActive = true;
    Start();
}

XmlFetchManager::~XmlFetchManager()
{
    LOG(kXmlFetch, "> ~XmlFetchManager\n");

    iLock.Wait();
    iActive = false;
    iLock.Signal();
    Kill();
    Join();

    iFree.ReadInterrupt();

    for (TUint i=0; i<iCpStack.Env().InitParams()->NumXmlFetcherThreads(); i++) {
        delete iFetchers[i];
    }
    free(iFetchers);

    TUint size = (TUint)iList.size();
    while (size > 0) {
        XmlFetch* fetch = iList.front();
        fetch->SetError(Error::eAsync, Error::eCodeShutdown,
                        Error::kDescriptionAsyncShutdown);
        fetch->SignalCompleted();
        iList.pop_front();
        size--;
    }

    LOG(kXmlFetch, "< ~XmlFetchManager\n");
}

XmlFetch* XmlFetchManager::Fetch()
{
    return new XmlFetch(iCpStack);
}

void XmlFetchManager::Fetch(XmlFetch* aFetch)
{
    LOG(kXmlFetch, "Fetch for ");
    LOG(kXmlFetch, aFetch->Uri().AbsoluteUri());
    LOG(kXmlFetch, "\n");

    FunctorAsync& asyncBeginHandler = iCpStack.Env().InitParams()->AsyncBeginHandler();
    if (asyncBeginHandler) {
        asyncBeginHandler(*aFetch);
    }

    AutoMutex a(iLock);
    if (!iActive) {
        aFetch->SetError(Error::eAsync, Error::eCodeShutdown,
                         Error::kDescriptionAsyncShutdown);
        aFetch->SignalCompleted();
        delete aFetch;
        return;
    }
    iList.push_back(aFetch);
    Signal();
}

void XmlFetchManager::Run()
{
    for (;;) {
        Wait();
        XmlFetcher* fetcher = iFree.Read();
        iLock.Wait();
        if (!iActive) {
            iLock.Signal();
            continue; // the next Wait() will throw ThreadKill
        }
        XmlFetch* fetch = iList.front();
        iList.front() = NULL;
        iList.pop_front();
        iLock.Signal();
        fetcher->Fetch(fetch);
    }
}
