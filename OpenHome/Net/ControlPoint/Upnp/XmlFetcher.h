/**
 * Fetcher for UPnP device XML
 */

#ifndef HEADER_XML_FETCHER
#define HEADER_XML_FETCHER

#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Exception.h>

EXCEPTION(XmlFetchError)

namespace OpenHome {
class SocketTcpClient;
namespace Net {

class CpStack;
class XmlFetcher;
class XmlFetchBlock;
class XmlFetchManager;

// A caller should only ever interact with XmlFetch via XmlFetchManager::Fetch/CheckContactable
// and the static methods on XmlFetch.
// To perform a fetch, the caller should:
// - Use XmlFetchManager::Fetch/CheckContactable function to generate a queued XmlFetch
// - Use XmlFetchManager::Interrupt(__) should you wish to cancel a pending fetch
// - ONCE FETCH HAS CALLED BACK
//      - Use the static functions on XmlFetch to access the result of the fetch.
//
// NOTE: XmlFetch instances are pooled internally and so the result of the fetch is only
//       valid whilst your completion callback is running.
class XmlFetch : public Async
{
public:
    static Bwh& Xml(IAsync& aAsync);
    static TBool WasContactable(IAsync& aAsync);
    static TBool DidError(IAsync& aAsync);
    static OpenHome::Net::Error& GetError(IAsync& aAsync); // Throws XMLFetchError if not errored. Check DidError() first

private:
    void SetError(Error::ELevel aLevel, TUint aCode, const Brx& aDescription);
    TBool Error() const;
    virtual void Output(IAsyncOutput& aConsole);
    virtual TUint Type() const;
private:
    XmlFetch* iNext;
    Brn iLocation;
    FunctorAsync iFunctor;
    Bwh iXml;
    OpenHome::Net::Error iError;
    TUint iSequenceNumber;
    TBool iInterrupted;
    TBool iCheckContactable;
    TBool iContactable;

    friend class XmlFetcher;
    friend class XmlFetchManager;
};

class XmlFetcher : public Thread
{
public:
    XmlFetcher(const TChar* aName, Environment& aEnv, XmlFetchManager& aManager);
    ~XmlFetcher();
    TBool InterruptIfRunning(XmlFetch& aFetch);
private:
    void LogError(const TChar* aErr);
    void Run();
    void DoFetch();
    void WriteRequest(const Brx& aMethod);
    TBool Read();
private:
    static const TUint kRwBufferLength    = 16*1024;
    static const TUint kResponseTimeoutMs = 60 * 1000;

    Environment& iEnv;
    XmlFetchManager& iManager;
    Mutex iLock;
    XmlFetch* iFetch;
    Uri iUri;
    SocketTcpClient iSocket;
    Srs<1024> iReadBuffer;
    ReaderUntilS<1024> iReaderUntil;
    ReaderHttpChunked iDechunker;
    ReaderHttpEntity iReaderEntity;
};

class XmlFetchManager
{
public:
    XmlFetchManager(CpStack& aCpStack);
    ~XmlFetchManager();
    XmlFetch* Fetch(const Brx& aAbsoluteUri, FunctorAsync& aFunctor);
    XmlFetch* CheckContactable(const Brx& aAbsoluteUri, FunctorAsync& aFunctor);
    void Interrupt(XmlFetch& aFetch);
private:
    void EnqueueFetch(XmlFetch* aFetch);
    XmlFetch* NextFetch();
    TBool IsFetchInterrupted(XmlFetch* aFetch);
    void AddPoolBlock();
    XmlFetch* AcquireFetch();
    void ReleaseFetch(XmlFetch* aFetch);
    void ReleaseFetchLocked(XmlFetch* aFetch);
    void SetFetchShutdownError(XmlFetch* aFetch);
private:
    CpStack& iCpStack;
    Mutex iLock;
    Semaphore iPending;
    XmlFetchBlock* iPool;
    XmlFetch* iFreeList;
    XmlFetch* iPendingListHead;
    XmlFetch* iPendingListTail;
    XmlFetcher** iFetchers;
    TBool iActive;

    // XmlFetch usage stats
    TUint iNumBlocks;
    TUint iNumInUse;
    TUint iMaxInUse;

    friend class XmlFetcher;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_XML_FETCHER
