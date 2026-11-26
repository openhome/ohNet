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

static const Brn kUriErrorDescription("Uri Error");
static const Brn kHttpErrorDescription("Http Error");
static const Brn kReaderErrorDescription("Reader Error");
static const Brn kWriterErrorDescription("Writer Error");
static const Brn kNetworkErrorDescription("Network Error");


// XmlFetch
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

XmlFetcher::XmlFetcher(const TChar* aName, Environment& aEnv, XmlFetchManager& aManager)
    : Thread(aName)
    , iEnv(aEnv)
    , iManager(aManager)
    , iLock("XMLF")
    , iFetch(NULL)
    , iReadBuffer(iSocket)
    , iReaderUntil(iReadBuffer)
    , iDechunker(iReaderUntil)
    , iReaderEntity(iReaderUntil)
{ }

XmlFetcher::~XmlFetcher()
{
    Kill();

    iLock.Wait();
    iSocket.Interrupt(true);
    iLock.Signal();

    Join();
}

TBool XmlFetcher::InterruptIfRunning(XmlFetch& aFetch)
{
    TBool didInterrupt = false;

    iLock.Wait();
    if (iFetch == &aFetch) {
        iSocket.Interrupt(true);
        didInterrupt = true;
    }
    iLock.Signal();

    return didInterrupt;
}

#ifdef DEFINE_TRACE
void XmlFetcher::LogError(const TChar* aErr)
#else
void XmlFetcher::LogError(const TChar* /*aErr*/)
#endif
{
    LOG_ERROR(kXmlFetch, "Error - %s - from %.*s\n", aErr, PBUF(iFetch->iLocation));
}

void XmlFetcher::Run()
{
    XmlFetch* fetch = NULL;

    for (;;) {
        fetch = iManager.NextFetch();
        if (fetch == NULL) {
            break; // No more work, we're shutting down.
        }

        iLock.Wait();
        iFetch = fetch;
        iLock.Signal();

        if (fetch != NULL) {
            try {
                iUri.Replace(fetch->iLocation);
                DoFetch();
            }
            catch (UriError&) {
                iFetch->SetError(Error::eHttp, Error::kCodeUnknown, kUriErrorDescription);
                LogError("Http(URI)");
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

            FunctorAsync& asyncEndHandler = iEnv.InitParams()->AsyncEndHandler();
            if (asyncEndHandler) {
                asyncEndHandler(*fetch);
            }
            ASSERT(fetch->iFunctor);
            try {
                fetch->iFunctor(*fetch);
            }
            catch(XmlFetchError&) {
                FunctorAsync& asyncErrorHandler = iEnv.InitParams()->AsyncErrorHandler();
                if (asyncErrorHandler) {
                    asyncErrorHandler(*fetch);
                }
            }

            iManager.ReleaseFetch(fetch);
        }
    }
}

void XmlFetcher::DoFetch()
{
    const Brx& absUri = iUri.AbsoluteUri();
    LOG(kXmlFetch, "> XmlFetch::Fetch for %.*s\n", PBUF(absUri));

    iLock.Wait();
    iSocket.Interrupt(false);
    iLock.Signal();
    iSocket.Open(iEnv);
    AutoSocket a(iSocket);
    iLock.Wait();

    if (iManager.IsFetchInterrupted(iFetch)) {
        iFetch->SetError(Error::eAsync, Error::eCodeInterrupted, Error::kDescriptionAsyncInterrupted);
        iLock.Signal();
        THROW(ReaderError);
    }
    iLock.Signal();
    try {
        const TUint port = (iUri.Port()==Uri::kPortNotSpecified? 80 : iUri.Port());
        Endpoint endpoint(port, iUri.Host());
        TUint timeout = iEnv.InitParams()->TcpConnectTimeoutMs();
        iSocket.Connect(endpoint, timeout);
        WriteRequest(iFetch->iCheckContactable ? Http::kMethodHead : Http::kMethodGet);

        TBool success = Read();
        if (!success) {
            if (!iFetch->iCheckContactable) {
                THROW(HttpError);
            }

            // possible the device doesn't support HTTP HEAD method, try again with GET
            // close then re-open socket - some devices don't like keep-alive and additional requests
            iSocket.Close();
            iSocket.Open(iEnv);
            iSocket.Connect(endpoint, timeout);

            iFetch->iError.Clear();
            WriteRequest(Http::kMethodGet);
            if (!Read()) {
                THROW(HttpError);
            }
        }
    }
    catch (NetworkTimeout&) {
        iFetch->SetError(Error::eSocket, Error::eCodeTimeout, Error::kDescriptionSocketTimeout);
    }
    catch (NetworkError&) {
        iFetch->SetError(Error::eSocket, Error::kCodeUnknown, kNetworkErrorDescription);
    }
    catch (HttpError&) {
        iFetch->SetError(Error::eHttp, Error::kCodeUnknown, kHttpErrorDescription);
    }
    catch (WriterError&) {
        iFetch->SetError(Error::eSocket, Error::kCodeUnknown, kWriterErrorDescription);
    }
    catch (ReaderError&) {
        iFetch->SetError(Error::eSocket, Error::kCodeUnknown, kReaderErrorDescription);
    }

    LOG(kXmlFetch, "< XmlFetch::Fetch for %.*s\n", PBUF(absUri));
}

void XmlFetcher::WriteRequest(const Brx& aMethod)
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

TBool XmlFetcher::Read()
{
    iReaderEntity.ReadFlush();
    ReaderHttpResponse readerResponse(iEnv, iReaderUntil);
    HttpHeaderContentLength headerContentLength;
    HttpHeaderTransferEncoding headerTransferEncoding;

    readerResponse.AddHeader(headerContentLength);
    readerResponse.AddHeader(headerTransferEncoding);
    readerResponse.Read(kResponseTimeoutMs);
    const HttpStatus& status = readerResponse.Status();
    if (status != HttpStatus::kOk) {
        const Brx& reason = status.Reason();
        LOG_TRACE(kXmlFetch, "XmlFetch::Read, http error %u %.*s\n", status.Code(), PBUF(reason));
        iFetch->SetError(Error::eHttp, status.Code(), reason);
        return false;
    }
    if (iFetch->iCheckContactable) {
        iFetch->iContactable = true;
        return true;
    }

    WriterBwh writer(1024);
    iReaderEntity.ReadAll(writer, headerContentLength, headerTransferEncoding,
                          ReaderHttpEntity::Client);
    writer.TransferTo(iFetch->iXml);
    return true;
}

// XmlFetchBlock
//
// @PoolBlockSize
// Previously an XmlFetch instance would contain it's own URI, socket, read/write buffers and HTTP readers.
// This was changed so that these are owned by XmlFetcher instead and reused across multiple fetches.
// As such the size of XmlFetch reduced from ~5KB to ~150bytes. With this in mind, a single XMLFetch from before
// used the same about of RAM as about 30 instances today.
// Most users have 1 or 2 products on the network and with a conservative estimate of 5 fetches per device, a block
// size of 5KB more than covers this need. When tested on the office network, a peek of around 60 fetches was observed
// requiring only 2 blocks to service the pool.
namespace OpenHome {
namespace Net {

class XmlFetchBlock
{
    static const TUint kMaxBlockSize   = 5 * 1024; //@PoolBlockSize
    static const TUint kFetchesPerBlock = kMaxBlockSize / sizeof(XmlFetch);

    XmlFetchBlock* iNext;
    XmlFetch iFetches[kFetchesPerBlock];
};

} // namespace Net
} // namespace OpenHome


// XmlFetchManager

// TODO: XmlFetchBlocks are never freed during runtime. If we wanted to be really nice we could offer
//       a global "Cleanup" function that does some housekeeping and could remove blocks who don't have
//       a single fetch in use.

// TODO: The current pending list operates in LIFO order. This is different from the previous case that was
//       FIFO order. In most networks, the number of devices are small and so shouldn't have much of an impact

XmlFetchManager::XmlFetchManager(CpStack& aCpStack)
    : iCpStack(aCpStack)
    , iLock("FETL")
    , iPending("FETP", 0)
    , iPool(NULL)
    , iFreeList(NULL)
    , iPendingListHead(NULL)
    , iPendingListTail(NULL)
    , iNumBlocks(0)
    , iNumInUse(0)
    , iMaxInUse(0)
{
    const TUint numThreads = iCpStack.Env().InitParams()->NumXmlFetcherThreads();
    iFetchers = (XmlFetcher**)malloc(sizeof(*iFetchers) * numThreads);
    for (TUint i=0; i<numThreads; i++) {
        Bws<Thread::kMaxNameBytes+1> thName;
        thName.AppendPrintf("XmlFetcher %d", i);
        thName.PtrZ();
        iFetchers[i] = new XmlFetcher((const TChar*)thName.Ptr(), iCpStack.Env(), *this);
        iFetchers[i]->Start();
    }

    AddPoolBlock();
    iActive = true;
}

XmlFetchManager::~XmlFetchManager()
{
    LOG(kXmlFetch, "> ~XmlFetchManager\n");

    iLock.Wait();
    iActive = false;
    iLock.Signal();

    iLock.Wait();
    for (TUint i = 0; i < iCpStack.Env().InitParams()-> NumXmlFetcherThreads(); i += 1) {
        iPending.Signal();
    }
    iLock.Signal();


    for (TUint i=0; i<iCpStack.Env().InitParams()->NumXmlFetcherThreads(); i++) {
        delete iFetchers[i];
    }
    free(iFetchers);

    while (iPendingListHead) {
        XmlFetch* fetch  = iPendingListHead;
        iPendingListHead = fetch->iNext;

        SetFetchShutdownError(fetch);
        // Don't bother calling release as the fetches are all released next
    }

    while (iPool) {
        XmlFetchBlock* block = iPool;
        iPool                = block->iNext;
        delete block;
    }

    LOG(kEssential, "~XmlFetchManager: XmlFetchPool was %u blocks in size (a total of %u instances). Peak usage: %u\n", iNumBlocks, iNumBlocks * XmlFetchBlock::kFetchesPerBlock, iMaxInUse);
    LOG(kXmlFetch, "< ~XmlFetchManager\n");
}

XmlFetch* XmlFetchManager::Fetch(const Brx& aAbsoluteUri, FunctorAsync& aFunctor)
{
    XmlFetch* fetch          = AcquireFetch();
    fetch->iFunctor          = aFunctor;
    fetch->iSequenceNumber   = iCpStack.Env().SequenceNumber();
    fetch->iCheckContactable = false;
    fetch->iLocation.Set(aAbsoluteUri);
    fetch->iError.Clear();
    EnqueueFetch(fetch);
    return fetch;
}

XmlFetch* XmlFetchManager::CheckContactable(const Brx& aAbsoluteUri, FunctorAsync& aFunctor)
{
    XmlFetch* fetch          = AcquireFetch();
    fetch->iFunctor          = aFunctor;
    fetch->iSequenceNumber   = iCpStack.Env().SequenceNumber();
    fetch->iCheckContactable = true;
    fetch->iLocation.Set(aAbsoluteUri);
    fetch->iError.Clear();
    EnqueueFetch(fetch);
    return fetch;
}

void XmlFetchManager::Interrupt(XmlFetch& aFetch)
{
    Log::Print(">XmlFetchManager::Interrupt\n");

    iLock.Wait();
    aFetch.iInterrupted = true;
    iLock.Signal();

    for (TUint i = 0; i < iCpStack.Env().InitParams()->NumXmlFetcherThreads(); i += 1) {
        TBool didInterrupt = iFetchers[i]->InterruptIfRunning(aFetch);
        if (didInterrupt) {
            break;
        }
    }

    Log::Print("<XmlFetchManager::Interrupt\n");
}

void XmlFetchManager::EnqueueFetch(XmlFetch* aFetch)
{
    LOG(kXmlFetch, "Fetch for %.*s\n", PBUF(aFetch->iLocation));

    FunctorAsync& asyncBeginHandler = iCpStack.Env().InitParams()->AsyncBeginHandler();
    if (asyncBeginHandler) {
        asyncBeginHandler(*aFetch);
    }

    AutoMutex a(iLock);
    if (!iActive) {
        SetFetchShutdownError(aFetch);
        ReleaseFetchLocked(aFetch);
    }
    else {
        aFetch->iNext = NULL;

        if (iPendingListTail) {
            iPendingListTail->iNext = aFetch;
        }
        else {
            iPendingListHead = aFetch;
        }

        iPendingListTail = aFetch;

        iPending.Signal();
    }
}

void XmlFetchManager::SetFetchShutdownError(XmlFetch* aFetch)
{
    aFetch->SetError(Error::eAsync,
                     Error::eCodeShutdown,
                     Error::kDescriptionAsyncShutdown);

    FunctorAsync& asyncEndHandler = iCpStack.Env().InitParams()->AsyncEndHandler();
    if (asyncEndHandler) {
        asyncEndHandler(*aFetch);
    }
    ASSERT(aFetch->iFunctor);
    try {
        aFetch->iFunctor(*aFetch);
    }
    catch(XmlFetchError&) {
        FunctorAsync& asyncErrorHandler = iCpStack.Env().InitParams()->AsyncErrorHandler();
        if (asyncErrorHandler) {
            asyncErrorHandler(*aFetch);
        }
    }
}

XmlFetch* XmlFetchManager::NextFetch()
{
    iPending.Wait();

    AutoMutex m(iLock);
    if (!iActive) {
        return NULL; // Signal for XmlFetcher threads to exit
    }

    ASSERT(iPendingListHead != NULL);

    XmlFetch* fetch  = iPendingListHead;
    iPendingListHead = fetch->iNext;
    fetch->iNext     = NULL;

    if (iPendingListHead == NULL) {
        iPendingListTail = NULL;
    }

    return fetch;
}

XmlFetch* XmlFetchManager::AcquireFetch()
{
    AutoMutex a(iLock);

    if (iFreeList == NULL) {
        AddPoolBlock();
    }

    XmlFetch* fetch = iFreeList;
    iFreeList       = fetch->iNext;
    fetch->iNext    = NULL;

    iNumInUse += 1;
    if (iNumInUse > iMaxInUse) {
        iMaxInUse = iNumInUse;
    }

    return fetch;
}

void XmlFetchManager::ReleaseFetch(XmlFetch* aFetch)
{
    AutoMutex a(iLock);
    ReleaseFetchLocked(aFetch);
}

void XmlFetchManager::ReleaseFetchLocked(XmlFetch* aFetch)
{
    aFetch->iNext = iFreeList;
    iFreeList     = aFetch;

    iNumInUse -= 1;
}

void XmlFetchManager::AddPoolBlock()
{
    XmlFetchBlock* newBlock = new XmlFetchBlock();
    ASSERT(newBlock != NULL);

    newBlock->iNext = iPool;
    iPool           = newBlock;

    for (TUint i = 0; i < XmlFetchBlock::kFetchesPerBlock; i += 1) {
        XmlFetch& fetch = newBlock->iFetches[i];
        fetch.iNext     = iFreeList;
        iFreeList       = &fetch;
    }

    iNumBlocks += 1;
    if (iNumBlocks > 1) {
        LOG(Debug::kEssential, "XmlFetchManager: XmlFetch pool increasing. Now: %u blocks of %u fetches (%u in total)\n", iNumBlocks, XmlFetchBlock::kFetchesPerBlock, iNumBlocks * XmlFetchBlock::kFetchesPerBlock);
    }
}

TBool XmlFetchManager::IsFetchInterrupted(XmlFetch* aFetch)
{
    TBool result = false;
    iLock.Wait();
    result = aFetch->iInterrupted;;
    iLock.Signal();
    return result;
}
