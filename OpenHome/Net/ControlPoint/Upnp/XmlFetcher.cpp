#include <OpenHome/Net/Private/XmlFetcher.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>

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
    FunctorAsync& asyncEndHandler = iCpStack.Env().InitParams().AsyncEndHandler();
    if (asyncEndHandler) {
        asyncEndHandler(*this);
    }
    ASSERT(iFunctor);
    try {
        iFunctor(*this);
    }
    catch(XmlFetchError&) {
        FunctorAsync& asyncErrorHandler = iCpStack.Env().InitParams().AsyncErrorHandler();
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
    
    OpenHome::SocketTcpClient socket;
    socket.Open(iCpStack.Env());
    AutoSocket a(socket);
    iLock.Wait();
    if (iInterrupted) {
        SetError(Error::eAsync, Error::eCodeInterrupted, Error::kDescriptionAsyncInterrupted);
        iLock.Signal();
        THROW(ReaderError);
    }
    iSocket = &socket;
    iLock.Signal();
    try {
        Endpoint endpoint(iUri->Port(), iUri->Host());
        TUint timeout = iCpStack.Env().InitParams().TcpConnectTimeoutMs();
        socket.Connect(endpoint, timeout);
    }
    catch (NetworkTimeout&) {
        SetError(Error::eSocket, Error::eCodeTimeout, Error::kDescriptionSocketTimeout);
        THROW(NetworkTimeout);
    }
    WriteRequest(socket);
    Read(socket);
    iLock.Wait();
    iSocket = NULL;
    iLock.Signal();

    LOG(kXmlFetch, "< XmlFetch::Fetch for ");
    LOG(kXmlFetch, iUri->AbsoluteUri());
    LOG(kXmlFetch, "\n");
}

void XmlFetch::Interrupt()
{
    iLock.Wait();
    iInterrupted = true;
    if (iSocket != NULL) {
        iSocket->Interrupt(true);
    }
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
{
    ASSERT(((Async&)aAsync).Type() == Async::eXmlFetch);
    XmlFetch& self = (XmlFetch&)aAsync;
    if (self.Error()) {
        THROW(XmlFetchError);
    }
    return self.iXml;
}

XmlFetch::XmlFetch(CpStack& aCpStack)
    : iCpStack(aCpStack)
    , iUri(NULL)
    , iSequenceNumber(0)
    , iLock("XMLM")
    , iInterrupted(false)
    , iSocket(NULL)
{
}

void XmlFetch::WriteRequest(SocketTcpClient& aSocket)
{
    Sws<kRwBufferLength> writeBuffer(aSocket);
    WriterHttpRequest writerRequest(writeBuffer);

    writerRequest.WriteMethod(Http::kMethodGet, iUri->PathAndQuery(), Http::eHttp11);
    Http::WriteHeaderHost(writerRequest, *iUri);
    Http::WriteHeaderContentLength(writerRequest, 0);
    Http::WriteHeaderConnectionClose(writerRequest);
    writerRequest.WriteFlush();
}

void XmlFetch::Read(SocketTcpClient& aSocket)
{
    Srd readBuffer(kRwBufferLength, aSocket);
    ReaderHttpResponse readerResponse(iCpStack.Env(), readBuffer);
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

    if (headerTransferEncoding.IsChunked()) {
        ReaderHttpChunked dechunker(readBuffer);
        dechunker.Read();
        dechunker.TransferTo(iXml);
    }
    else {
        TUint remaining = headerContentLength.ContentLength();
        if (remaining == 0) { // no content length - read until connection closed by server
            try {
                for (;;) {
                    Brn buf = readBuffer.Read(kRwBufferLength);
                    iXml.Grow(iXml.Bytes() + kRwBufferLength);
                    iXml.Append(buf);
                }
            }
            catch (ReaderError&) {
                Brn snaffle = readBuffer.Snaffle();
                iXml.Grow(iXml.Bytes() + snaffle.Bytes());
                iXml.Append(snaffle);
            }
        }
        else {
            while (remaining > 0) {
                TInt readBytes = (remaining > kRwBufferLength ? kRwBufferLength : remaining);
                Brn buf = readBuffer.Read(readBytes);
                iXml.Grow(iXml.Bytes() + readBytes);
                iXml.Append(buf);
                remaining -= readBytes;
            }
        }
    }
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
            iFetch->SetError(Error::eHttp, Error::kCodeUnknown, Error::kDescriptionUnknown);
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
            iFetch->SetError(Error::eSocket, Error::kCodeUnknown, Error::kDescriptionUnknown);
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
    : Thread("FETM")
    , iCpStack(aCpStack)
    , iLock("FETL")
    , iFree(iCpStack.Env().InitParams().NumXmlFetcherThreads())
{
    const TUint numThreads = iCpStack.Env().InitParams().NumXmlFetcherThreads();
    iFetchers = (XmlFetcher**)malloc(sizeof(*iFetchers) * numThreads);
    TChar thName[5] = "FET ";
#ifndef _WIN32
    ASSERT(numThreads <= 9);
#endif
    for (TUint i=0; i<numThreads; i++) {
        thName[3] = (TChar)('0'+i);
        iFetchers[i] = new XmlFetcher(&thName[0], iFree);
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

    for (TUint i=0; i<iCpStack.Env().InitParams().NumXmlFetcherThreads(); i++) {
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

    FunctorAsync& asyncBeginHandler = iCpStack.Env().InitParams().AsyncBeginHandler();
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
