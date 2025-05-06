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

static const Brn kHttpErrorDescription("Http Error");
static const Brn kReaderErrorDescription("Reader Error");
static const Brn kWriterErrorDescription("Writer Error");
static const Brn kNetworkErrorDescription("Network Error");


// XmlFetch

void XmlFetch::Set(const Brx& aAbsoluteUri, FunctorAsync& aFunctor)
{
    iUri.Replace(aAbsoluteUri);
    iFunctor = aFunctor;
    iSequenceNumber = iCpStack.Env().SequenceNumber();
}

void XmlFetch::CheckContactable(const Brx& aAbsoluteUri, FunctorAsync& aFunctor)
{
    Set(aAbsoluteUri, aFunctor);
    iCheckContactable = true;
}

XmlFetch::~XmlFetch()
{
}

const OpenHome::Uri& XmlFetch::Uri() const
{
    return iUri;
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
        if (iInterrupted && aLevel != Error::eAsync) {
            iError.Set(Error::eAsync, Error::eCodeInterrupted, Error::kDescriptionAsyncInterrupted);
        }
        else {
            iError.Set(aLevel, aCode, aDescription);
        }
    }
}

void XmlFetch::Fetch()
{
    const Brx& absUri = iUri.AbsoluteUri();
    LOG(kXmlFetch, "> XmlFetch::Fetch for %.*s\n", PBUF(absUri));

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
        const TUint port = (iUri.Port()==Uri::kPortNotSpecified? 80 : iUri.Port());
        Endpoint endpoint(port, iUri.Host());
        TUint timeout = iCpStack.Env().InitParams()->TcpConnectTimeoutMs();
        iSocket.Connect(endpoint, timeout);
        WriteRequest(iCheckContactable ? Http::kMethodHead : Http::kMethodGet);
        try {
            Read();
        }
        catch (HttpError&) {
            if (!iCheckContactable) {
                throw;
            }

            // possible the device doesn't support HTTP HEAD method, try again with GET
            // close then re-open socket - some devices don't like keep-alive and additional requests
            iSocket.Close();
            iSocket.Open(iCpStack.Env());
            iSocket.Connect(endpoint, timeout);

            iError.Clear();
            WriteRequest(Http::kMethodGet);
            Read();
        }
    }
    catch (NetworkTimeout&) {
        SetError(Error::eSocket, Error::eCodeTimeout, Error::kDescriptionSocketTimeout);
    }
    catch (NetworkError&) {
        SetError(Error::eSocket, Error::kCodeUnknown, kNetworkErrorDescription);
    }
    catch (HttpError&) {
        SetError(Error::eHttp, Error::kCodeUnknown, kHttpErrorDescription);
    }
    catch (WriterError&) {
        SetError(Error::eSocket, Error::kCodeUnknown, kWriterErrorDescription);
    }
    catch (ReaderError&) {
        SetError(Error::eSocket, Error::kCodeUnknown, kReaderErrorDescription);
    }

    LOG(kXmlFetch, "< XmlFetch::Fetch for %.*s\n", PBUF(absUri));
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

TBool XmlFetch::DidError(IAsync& aAsync)
{ // static
    ASSERT(((Async&)aAsync).Type() == Async::eXmlFetch);
    XmlFetch& self = (XmlFetch&)aAsync;
    return self.Error();
}

Error& XmlFetch::GetError(IAsync& aAsync)
{ // static
    ASSERT(((Async&)aAsync).Type() == Async::eXmlFetch);
    XmlFetch& self = (XmlFetch&)aAsync;
    if (self.Error()) {
        return self.iError;
    }
    
    // Can't return an error if there is none.
    THROW(XmlFetchError); 
}

XmlFetch::XmlFetch(CpStack& aCpStack)
    : iCpStack(aCpStack)
    , iSequenceNumber(0)
    , iLock("XMLM")
    , iInterrupted(false)
    , iCheckContactable(false)
    , iContactable(false)
    , iReadBuffer(iSocket)
    , iReaderUntil(iReadBuffer)
    , iDechunker(iReaderUntil)
    , iReaderEntity(iReaderUntil)
{
}

void XmlFetch::WriteRequest(const Brx& aMethod)
{
    Sws<kRwBufferLength> writeBuffer(iSocket);
    WriterHttpRequest writerRequest(writeBuffer);

    writerRequest.WriteMethod(aMethod, iUri.PathAndQuery(), Http::eHttp11);
    const TUint port = (iUri.Port()==Uri::kPortNotSpecified? 80 : iUri.Port());
    Http::WriteHeaderHostAndPort(writerRequest, iUri.Host(), port);
    Http::WriteHeaderContentLength(writerRequest, 0);
    Http::WriteHeaderConnectionClose(writerRequest);
    writerRequest.WriteFlush();
}

void XmlFetch::Read()
{
    iReaderEntity.ReadFlush();
    ReaderHttpResponse readerResponse(iCpStack.Env(), iReaderUntil);
    HttpHeaderContentLength headerContentLength;
    HttpHeaderTransferEncoding headerTransferEncoding;

    readerResponse.AddHeader(headerContentLength);
    readerResponse.AddHeader(headerTransferEncoding);
    readerResponse.Read(kResponseTimeoutMs);
    const HttpStatus& status = readerResponse.Status();
    if (status != HttpStatus::kOk) {
        const Brx& reason = status.Reason();
        LOG_TRACE(kXmlFetch, "XmlFetch::Read, http error %u %.*s\n", status.Code(), PBUF(reason));
        SetError(Error::eHttp, status.Code(), reason);
        THROW(HttpError);
    }
    if (iCheckContactable) {
        iContactable = true;
        return;
    }

    WriterBwh writer(1024);
    iReaderEntity.ReadAll(writer, headerContentLength, headerTransferEncoding,
                          ReaderHttpEntity::Client);
    writer.TransferTo(iXml);
}

void XmlFetch::Output(IAsyncOutput& /*aConsole*/)
{
    // Its non-trivial to serialise output from different fetcher threads.
    // Code is disabled for now as we haven't used this in years... 
    /*
    Mutex& lock = iCpStack.Env().Mutex();
    lock.Wait();
    Bws<Ascii::kMaxUintStringBytes+1> buf;
    (void)Ascii::AppendDec(buf, iSequenceNumber);
    buf.PtrZ();
    aConsole.Output("SequenceNumber", (const TChar*)buf.Ptr());
    Bws<Uri::kMaxUriBytes+1> uri(iUri.AbsoluteUri());
    uri.PtrZ();
    aConsole.Output("XmlFetch", (const TChar*)uri.Ptr());
    if (Error()) {
        iError.Output(aConsole);
    }
    lock.Signal();
    */
}

TUint XmlFetch::Type() const
{
    return Async::eXmlFetch;
}


// XmlFetcher

XmlFetcher::XmlFetcher(const TChar* aName, Fifo<XmlFetcher*>& aFree)
    : Thread(aName)
    , iFree(aFree)
    , iLock("XMLF")
    , iFetch(NULL)
{
}

XmlFetcher::~XmlFetcher()
{
    Kill();

    iLock.Wait();
    if (iFetch != NULL) {
        iFetch->Interrupt();
    }
    iLock.Signal();

    Join();
}

void XmlFetcher::Fetch(XmlFetch* aFetch)
{
    iLock.Wait();
    iFetch = aFetch;
    iLock.Signal();

    Signal();
}

#ifdef DEFINE_TRACE
void XmlFetcher::LogError(const TChar* aErr)
#else
void XmlFetcher::LogError(const TChar* /*aErr*/)
#endif
{
    const Brx& absUri = iFetch->Uri().AbsoluteUri();
    LOG_ERROR(kXmlFetch, "Error - %s - from %.*s\n", aErr, PBUF(absUri));
}

void XmlFetcher::Run()
{
    XmlFetch *fetch = NULL;

    for (;;) {
        Wait();

        iLock.Wait();
        fetch = iFetch;
        iLock.Signal();

        if (fetch != NULL) {
            try {
                if (fetch->Interrupted()) {
                    fetch->SetError(Error::eAsync, Error::eCodeInterrupted,
                                    Error::kDescriptionAsyncInterrupted);
                } else {
                    fetch->Fetch();
                }
            }
            catch (HttpError &) {
                LogError("Http");
            }
            catch (NetworkTimeout &) {
                // error already set in XmlFetch::Fetch()
                LogError("NetworkTimeout");
            }
            catch (NetworkError &) {
                iFetch->SetError(Error::eSocket, Error::kCodeUnknown, kNetworkErrorDescription);
                LogError("Network");
            }
            catch (WriterError &) {
                LogError("Writer");
            }
            catch (ReaderError &) {
                iFetch->SetError(Error::eSocket, Error::kCodeUnknown, kReaderErrorDescription);
                LogError("Reader");
            }

            iLock.Wait();
            iFetch = NULL;
            iLock.Signal();

            fetch->SignalCompleted();
            delete fetch;
        }

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
    const Brx& absUri = aFetch->Uri().AbsoluteUri();
    LOG(kXmlFetch, "Fetch for %.*s\n", PBUF(absUri));

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
