#include <XmlFetcher.h>
#include <Stack.h>
#include <CpiStack.h>
#include <Stream.h>
#include <Http.h>
#include <Exception.h>
#include <Debug.h>

#include <stdlib.h>

using namespace Zapp;

// XmlFetch

void XmlFetch::Set(Zapp::Uri* aUri, FunctorAsync& aFunctor)
{
    iUri = aUri;
    iFunctor = aFunctor;
    iSequenceNumber = Stack::SequenceNumber();
}

XmlFetch::~XmlFetch()
{
    delete iUri;
}

const Zapp::Uri& XmlFetch::Uri() const
{
    return *iUri;
}

void XmlFetch::SignalCompleted()
{
    FunctorAsync& asyncEndHandler = Stack::InitParams().AsyncEndHandler();
    if (asyncEndHandler) {
        asyncEndHandler(*this);
    }
    ASSERT(iFunctor);
    try {
        iFunctor(*this);
    }
    catch(XmlFetchError&) {
        FunctorAsync& asyncErrorHandler = Stack::InitParams().AsyncErrorHandler();
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
    
    SocketTcpClient socket;
    socket.Open();
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
        TUint timeout = Stack::InitParams().TcpConnectTimeoutMs();
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

XmlFetch::XmlFetch()
    : iUri(NULL)
    , iLock("XMLM")
    , iInterrupted(false)
{
}

void XmlFetch::WriteRequest(SocketTcpClient& aSocket)
{
    Sws<kRwBufferLength> writeBuffer(aSocket);
    WriterHttpRequest writerRequest(writeBuffer);

    writerRequest.WriteMethod(Http::kMethodGet, iUri->Path(), Http::eHttp11);
    Http::WriteHeaderHost(writerRequest, *iUri);
    Http::WriteHeaderContentLength(writerRequest, 0);
    Http::WriteHeaderConnectionClose(writerRequest);
    writerRequest.WriteFlush();
}

void XmlFetch::Read(SocketTcpClient& aSocket)
{
    Srs<kRwBufferLength> readBuffer(aSocket);
    ReaderHttpResponse readerResponse(readBuffer);
    HttpHeaderContentLength headerContentLength;
    HttpHeaderTransferEncoding headerTransferEncoding;

    readerResponse.AddHeader(headerContentLength);
    readerResponse.AddHeader(headerTransferEncoding);
    readerResponse.Read();
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
    Mutex& lock = Stack::Mutex();
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

XmlFetchManager::XmlFetchManager()
    : Thread("FETM")
    , iLock("FETL")
    , iFree(Stack::InitParams().NumXmlFetcherThreads())
{
    iFetchers = (XmlFetcher**)malloc(sizeof(*iFetchers) * Stack::InitParams().NumXmlFetcherThreads());
    TChar thName[5] = "FET ";
#ifndef _WIN32
    ASSERT(Stack::InitParams().NumXmlFetcherThreads() <= 9);
#endif
    for (TUint i=0; i<Stack::InitParams().NumXmlFetcherThreads(); i++) {
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
    Kill();
    Join();
    iLock.Signal();

    iFree.ReadInterrupt();

    for (TUint i=0; i<Stack::InitParams().NumXmlFetcherThreads(); i++) {
        delete iFetchers[i];
    }
    free(iFetchers);

    TUint size = iList.size();
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
    return new XmlFetch;
}

void XmlFetchManager::Fetch(XmlFetch* aFetch)
{
    XmlFetchManager& self = Self();
    LOG(kXmlFetch, "Fetch for ");
    LOG(kXmlFetch, aFetch->Uri().AbsoluteUri());
    LOG(kXmlFetch, "\n");

    FunctorAsync& asyncBeginHandler = Stack::InitParams().AsyncBeginHandler();
    if (asyncBeginHandler) {
        asyncBeginHandler(*aFetch);
    }

    AutoMutex a(self.iLock);
    if (!self.iActive) {
        aFetch->SetError(Error::eAsync, Error::eCodeShutdown,
                         Error::kDescriptionAsyncShutdown);
        aFetch->SignalCompleted();
        delete aFetch;
        return;
    }
    self.iList.push_back(aFetch);
    self.Signal();
}

XmlFetchManager& XmlFetchManager::Self()
{
    return CpiStack::XmlFetchManager();;
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
