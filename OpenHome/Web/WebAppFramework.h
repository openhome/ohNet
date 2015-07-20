#ifndef HEADER_WEB_APPFRAMEWORK
#define HEADER_WEB_APPFRAMEWORK

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/File.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Net/Private/DviServerUpnp.h> // FIXME - move HeaderAcceptLanguage out of this

EXCEPTION(ResourceInvalid);
EXCEPTION(TabCreationFailed);
EXCEPTION(TabManagerFull);
EXCEPTION(InvalidTabId);
EXCEPTION(TabAllocated);
EXCEPTION(InvalidAppPrefix);


namespace OpenHome {
    class NetworkAdapter;

namespace Web {

class IResourceHandler
{
public:
    static const TUint kMaxMimeTypeBytes = 255; // RFC 4288 (4.2) (RFC 6838 (4.2) obseletes this and recommends 127 bytes)
public:
    virtual const OpenHome::Brx& MimeType() = 0;
    virtual void Write(OpenHome::IWriter& aWriter, TUint aOffset, TUint aBytes) = 0;    // THROWS WriterError
    virtual void Destroy() = 0;
    virtual ~IResourceHandler() {}
};

class IResourceManager
{
public:
    // FIXME - rename param to aResourceTail? - to differentiate between
    // a full resource URI and the fact that WebApps now have a method for
    // retrieving their prefix
    // - Or just pass in full URI after checking first part of URI matches
    // IWebApp::ResourcePrefix()?
    virtual IResourceHandler& CreateResourceHandler(const OpenHome::Brx& aResource) = 0;  // THROWS ResourceInvalid
    virtual ~IResourceManager() {}
};

// FIXME - file handling should eventually be replaced with a cross-platform
// resource handling layer. This currently only works on posix-style filesystems.
// FIXME - make this thread aware
// - could state of Allocated() be changed while a (thread-safe) ResourceManager is inspecting it?
// Not thread-aware.
class FileResourceHandler : public IResourceHandler
{
public:
    FileResourceHandler(const OpenHome::Brx& aRootDir);
    TBool Allocated();
    void SetResource(const OpenHome::Brx& aUri);
public : // from IResourceHandler
    const OpenHome::Brx& MimeType();
    void Write(OpenHome::IWriter& aWriter, TUint aOffset, TUint aBytes);
    void Destroy();
private:
    void SetMimeType(const OpenHome::Brx& aUri);
private:
    OpenHome::Brh iRootDir;
    OpenHome::FileAnsii* iFile;
    OpenHome::Bws<kMaxMimeTypeBytes> iMimeType;
};


// Interfaces and abstract classes relevant to clients wishing to make use of
// the HttpFramework.

/**
 * Interface representing a web browser tab. A tab must be able to be passed
 * data from the framework (via the Receive() method) and provide some
 * implementation-specific way of being destroyed (e.g., freeing memory on the
 * heap, or passing the tab back into some allocator for fixed-size memory
 * solutions).
 */
class ITab
{
public:
    virtual void Receive(const OpenHome::Brx& aMessage) = 0;
    virtual void Destroy() = 0;
    virtual ~ITab() {}
};

/**
 * Interface representing a message that can be sent.
 */
class ITabMessage
{
public:
    virtual void Send(OpenHome::IWriter& aWriter) = 0;
    virtual void Destroy() = 0;
    virtual ~ITabMessage() {}
};

/**
 * Interface that will be passed by the framework when it requests that an
 * application creates a new tab. Allows tabs to pass data into the framework.
 */
class ITabHandler
{
public:
    virtual void Send(ITabMessage& aMessage) = 0;
    virtual ~ITabHandler() {}
};

class IFrameworkTimer;

/**
 * Interface representing an HTTP application that will make use of the
 * framework. Requires implementations for returning a new tab and the
 * processing of resources.
 */
class IWebApp : public IResourceManager
{
public:
    virtual ITab& Create(ITabHandler& aHandler, std::vector<const Brx*>& aLanguageList) = 0;    // throws TabCreationFailed
    //virtual IFrameworkTimer& CreateTimer() = 0;         // throws TimerCreationFailed
    virtual const OpenHome::Brx& ResourcePrefix() const = 0; // FIXME - rename to UriPrefix?
    virtual ~IWebApp() {}
};


// Classes relevant to the HTTP framework.

// Private classes for internal tab + session management.

class IFrameworkSemaphore
{
public:
    virtual void Wait() = 0;
    virtual void Wait(TUint aTimeoutMs) = 0;
    virtual TBool Clear() = 0;
    virtual void Signal() = 0;
    virtual ~IFrameworkSemaphore() {}
};

/**
 * Internal tab handler API for framework.
 */
class FrameworkTabHandler : public ITabHandler
{
public:
    FrameworkTabHandler(IFrameworkSemaphore& aSemaphore, TUint aSendQueueSize, TUint aSendTimeoutMs);
    ~FrameworkTabHandler();
    void BlockingSend(OpenHome::IWriter& aWriter); // THROWS Timeout
    void Clear();   // clears FIFO and any signals // FIXME - is this called anywhere?
public: // from ITabHandler
    void Send(ITabMessage& aMessage);
private:
    const TUint iSendTimeoutMs;
    OpenHome::FifoLiteDynamic<ITabMessage*> iFifo;
    OpenHome::Mutex iLock;
    IFrameworkSemaphore& iSem;
};

class IFrameworkTimerHandler
{
public:
    virtual void Complete() = 0;
    virtual ~IFrameworkTimerHandler() {}
};

class IFrameworkTimer
{
public:
    virtual void Start(TUint aDurationMs, IFrameworkTimerHandler& aHandler) = 0;
    virtual void Cancel() = 0;
    virtual ~IFrameworkTimer() {}
};

class IPollTimerHandler
{
public:
    virtual void PollWaitComplete() = 0;
    virtual ~IPollTimerHandler() {}
};

class IPollTimer
{
public:
    virtual void StartPollWait(TUint aTimeoutMs, IPollTimerHandler& aHandler) = 0;
    virtual void CancelPollWait() = 0;
    virtual ~IPollTimer() {}
};

class FrameworkTimer : public IFrameworkTimer
{
public:
    FrameworkTimer(OpenHome::Environment& aEnv);
    ~FrameworkTimer();
public: // from IFrameworkTimer
    void Start(TUint aDurationMs, IFrameworkTimerHandler& aHandler);
    void Cancel();
private:
    void Complete();
private:
    OpenHome::Timer* iTimer;
    IFrameworkTimerHandler* iHandler;
    OpenHome::Mutex iLock;  // FIXME - is this necessary?
    // FIXME - testing only - remove
    TUint iStartCount;
    TUint iCancelCount;
    TUint iCompleteCount;
};

class PollTimer : public IPollTimer, public IFrameworkTimerHandler, public OpenHome::INonCopyable
{
public:
    PollTimer(IFrameworkTimer& aTimer);
public: // from IPollTimer
    void StartPollWait(TUint aTimeoutMs, IPollTimerHandler& aHandler);
    void CancelPollWait();
private: // from IFrameworkTimerHandler
    void Complete();
private:
    IFrameworkTimer& iTimer;
    IPollTimerHandler* iHandler;
    OpenHome::Mutex iLock;
};

class IRefCountable
{
public:
    virtual void AddRef() = 0;
    virtual void RemoveRef() = 0;
    virtual ~IRefCountable() {}
};

class IRefCountableUnlocked
{
public:
    virtual void AddRefUnlocked() = 0;
    virtual void RemoveRefUnlocked() = 0;
    virtual ~IRefCountableUnlocked() {}
};

class ITabDestroyHandler
{
public:
    virtual void Destroy(IRefCountableUnlocked& aRefCountable) = 0;
    virtual ~ITabDestroyHandler() {}
};

class IBlockingSender
{
public:
    virtual void BlockingSend(OpenHome::IWriter& aWriter) = 0;
    virtual ~IBlockingSender() {}
};

class IFrameworkTab : public ITab, public IBlockingSender, public IRefCountable
{
public:
    virtual void StartPollWait() = 0;
    virtual void CancelPollWait() = 0;
public: // from ITab
    virtual void Receive(const OpenHome::Brx& aMessage) = 0;
    virtual void Destroy() = 0;
public: // from IBlockingSender
    virtual void BlockingSend(OpenHome::IWriter& aWriter) = 0;
public: // from IRefCountable
    virtual void AddRef() = 0;
    virtual void RemoveRef() = 0;
public:
    virtual ~IFrameworkTab() {}
};

class FrameworkSemaphore : public IFrameworkSemaphore
{
public:
    FrameworkSemaphore(const TChar* aName, TUint aCount);
public: // from IFrameworkSemaphore
    void Wait();
    void Wait(TUint aTimeoutMs);
    TBool Clear();
    void Signal();
private:
    OpenHome::Semaphore iSem;
};

/**
 * Internal tab for framework.
 */
class FrameworkTab : public IFrameworkTab, public ITabHandler, public IPollTimerHandler, public IRefCountableUnlocked
{
public:
    FrameworkTab(TUint aId, ITabDestroyHandler& aDestroyHandler, IFrameworkTimer& aTimer, TUint aSendQueueSize, TUint aSendTimeoutMs, TUint aPollTimeoutMs);
    ~FrameworkTab();
    TBool Allocated() const;    // calls between this and SetTab() not thread-safe; must lock entire object
    TBool Available() const;    // calls between this and AddRef() not thread-safe; Destroy() may be called by another thread. Appropriate locking must be in place to ensure thread-safety among these calls and the ITabDestroyHandler.
    void Set(ITab& aTab, std::vector<const Brx*>& aLanguages);
    void StartPollWait();
    void CancelPollWait();
public: // from IFrameworkTab
    void Receive(const OpenHome::Brx& aMessage);
    void Destroy();
    void BlockingSend(OpenHome::IWriter& aWriter);
    void AddRef();
    void RemoveRef();
public: // from ITabHandler
    void Send(ITabMessage& aMessage);
private: // from IPollTimerHandler
    void PollWaitComplete();
public: // from IRefCountableUnlocked - for clients using an external lock
    void AddRefUnlocked();
    void RemoveRefUnlocked();
private:
    const TUint iId;
    const TUint iPollTimeoutMs;
    ITabDestroyHandler& iDestroyHandler;
    FrameworkSemaphore iTabSem; // FIXME - pass this in as parameter for testing purposes?
    FrameworkTabHandler iHandler;
    PollTimer iPollTimer;
    ITab* iTab;
    std::vector<const Brx*> iLanguages; // takes ownership of pointers
    TUint iRefCount;
    TBool iDestructionPending;
    mutable OpenHome::Mutex iLock;
};

/**
 * Interface representing a central collection of IBufferedTabs.
 */
class ITabManager
{
public:
    virtual TUint CreateTab(IWebApp& aApp, std::vector<const Brx*>& aLanguageList) = 0;    // returns tab ID; THROWS TabManagerFull
    virtual IFrameworkTab& GetTab(TUint aTabId) = 0;    // THROWS InvalidTabId
    virtual ~ITabManager() {}
};

class TabManager : public ITabManager, public ITabDestroyHandler, public OpenHome::INonCopyable
{
public:
    TabManager(OpenHome::Environment& aEnv, TUint aMaxTabs, TUint aSendQueueSize, TUint aSendTimeoutMs, TUint aPollTimeoutMs);
    ~TabManager();
public: // from ITabManager
    TUint CreateTab(IWebApp& aApp, std::vector<const Brx*>& aLanguageList);    // THROWS TabManagerFull
    IFrameworkTab& GetTab(TUint aTabId);    // THROWS InvalidTabId
private: // from ITabDestroyHandler
    void Destroy(IRefCountableUnlocked& aRefCountable);
private:
    static TUint TabManagerIdToClientId(TUint aId);
    static TUint ClientIdToTabManagerId(TUint aId);
private:
    std::vector<FrameworkTimer*> iTimers;
    std::vector<FrameworkTab*> iTabs;
    const TUint iMaxTabs;
    OpenHome::Mutex iLock;
};

class IWebAppFramework
{
public:
    typedef FunctorGeneric<const Brx&> FunctorPresentationUrl;
public:
    virtual void Add(IWebApp* aWebApp, FunctorPresentationUrl aFunctor) = 0; // aFunctor will be called whenever presentation URL is updated
    virtual ~IWebAppFramework() {}
};

class IWebAppManager
{
public:
    // FIXME - automatically append "/" to end of resource prefix if not present?
    virtual IWebApp& GetApp(const OpenHome::Brx& aResourcePrefix) = 0; // THROWS InvalidAppPrefix
    virtual ~IWebAppManager() {}
};

class IServer
{
public:
    virtual TUint Port() const = 0;
    virtual TIpAddress Interface() const = 0;
    virtual ~IServer() {}
};

class WebAppInternal : public IWebApp, private INonCopyable
{
public:
    typedef IWebAppFramework::FunctorPresentationUrl FunctorPresentationUrl;
public:
    WebAppInternal(IWebApp* aWebApp, FunctorPresentationUrl aFunctor);
    ~WebAppInternal();
    void SetPresentationUrl(const Brx& aPresentationUrl);
public: // from IWebApp
    IResourceHandler& CreateResourceHandler(const Brx& aResource) override;
    ITab& Create(ITabHandler& aHandler, std::vector<const Brx*>& aLanguageList) override;
    const Brx& ResourcePrefix() const override;
private:
    IWebApp* iWebApp;
    FunctorPresentationUrl iFunctor;
};

// FIXME - handle redirects from "/" to "/index.html"? - job of resource handler
class WebAppFramework : public IWebAppFramework, public IWebAppManager, public IResourceManager, public IServer
{
public:
    static const TChar* kName;
    static const TChar* kAdapterCookie;
    static const Brn kSessionPrefix;
private:
    static const TUint kMaxSessionNameBytes = 32;  // Should be capable of storing string of form kSessionPrefix + ID (0-99) + '\0', e.g., "WebUiSession01\0".
private:
    class BrxPtrCmp
    {
    public:
        TBool operator()(const Brx* aStr1, const Brx* aStr2) const;
    };
private:
    // Spare session(s) for receiving user input and rejecting new long polling
    // connections when iMaxLpSessions in use.
    static const TUint kSpareSessions = 1;
    typedef std::pair<const OpenHome::Brx*,WebAppInternal*> WebAppPair;
    typedef std::map<const OpenHome::Brx*,WebAppInternal*, BrxPtrCmp> WebAppMap;
public:
    WebAppFramework(OpenHome::Environment& aEnv, TIpAddress aInterface = 0, TUint aPort = 0, TUint aMaxSessions = 6, TUint aSendQueueSize = 1024, TUint aSendTimeoutMs = 5000, TUint aPollTimeoutMs = 5000);
    ~WebAppFramework();
    void Start(); // FIXME - implement
    // Can't call Add() after Start()
public: // from IWebAppFramework
    void Add(IWebApp* aWebApp, FunctorPresentationUrl aFunctor) override;
private: // from IWebAppManager
    IWebApp& GetApp(const OpenHome::Brx& aResourcePrefix) override;  // THROWS InvalidAppPrefix
private: // from IResourceManager
    IResourceHandler& CreateResourceHandler(const OpenHome::Brx& aResource) override;  // THROWS ResourceInvalid
public: // from IServer
    TUint Port() const;
    TIpAddress Interface() const;
private:
    void AddSessions();
    void CurrentAdapterChanged();
private:
    OpenHome::Environment& iEnv;
    FrameworkTimer iPollTimer; // FIXME  remove
    const TUint iPort;
    const TUint iMaxLpSessions;
    TUint iAdapterListenerId;
    OpenHome::SocketTcpServer* iServer;
    TabManager* iTabManager;
    WebAppMap iWebApps; // FIXME - need comparator
    TBool iStarted;
    NetworkAdapter* iCurrentAdapter;
};

/**
 * HttpSession that handles serving files (via GET), processing POST requests
 * and allows long polling.
 */
class HttpSession : public OpenHome::SocketTcpSession
{
private:
    static const TUint kMaxRequestBytes = 4*1024;
    static const TUint kMaxResponseBytes = 4*1024;
    static const TUint kReadTimeoutMs = 5 * 1000;
    static const TUint kPollTimeoutMs = 5 * 1000;
    static const TUint kPollPeriodTimeoutMs = 5*1000;
public:
    HttpSession(OpenHome::Environment& aEnv, IWebAppManager& aAppManager, ITabManager& aTabManager, IResourceManager& aResourceManager);
    ~HttpSession();
    void Start();   // FIXME - Until this is called, return a service (temporarily) unavailable status?
private: // from SocketTcpSession
    void Run();
private:
    void Error(const OpenHome::HttpStatus& aStatus);
    void Get();
    void Post();
    void WriteLongPollHeaders();
private:
    IWebAppManager& iAppManager;
    ITabManager& iTabManager;
    IResourceManager& iResourceManager;
    OpenHome::Srx* iReadBuffer;
    ReaderUntil* iReaderUntilPreChunker;
    OpenHome::ReaderHttpRequest* iReaderRequest;
    ReaderHttpChunked* iReaderChunked;
    ReaderUntil* iReaderUntil;
    OpenHome::WriterHttpChunked* iWriterChunked;
    OpenHome::Sws<kMaxResponseBytes>* iWriterBuffer;
    OpenHome::WriterHttpResponse* iWriterResponse;
    OpenHome::HttpHeaderHost iHeaderHost;
    OpenHome::HttpHeaderTransferEncoding iHeaderTransferEncoding;
    OpenHome::HttpHeaderConnection iHeaderConnection;
    Net::HeaderAcceptLanguage iHeaderAcceptLanguage;
    const OpenHome::HttpStatus* iErrorStatus;
    TBool iResponseStarted;
    TBool iResponseEnded;
    TBool iResourceWriterHeadersOnly;
    TUint iUpdateCount;
};

} // namespace Web
} // namespace OpenHome

#endif // HEADER_WEB_APPFRAMEWORK
