#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/File.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Net/Private/DviServerUpnp.h>

#include <functional>

EXCEPTION(ResourceInvalid);
EXCEPTION(TabAllocatorFull);    // Thrown by an IWebApp when its allocator is full.
EXCEPTION(TabManagerFull);
EXCEPTION(InvalidTabId);
EXCEPTION(TabAllocated);
EXCEPTION(InvalidAppPrefix);
EXCEPTION(WebAppServiceUnavailable);


namespace OpenHome {
    class NetworkAdapter;

namespace Web {

class IResourceHandler
{
public:
    virtual TBool Allocated() = 0;
    virtual void SetResource(const Brx& aUri) = 0;
    virtual TUint Bytes() = 0; // 0 => unknown size
    virtual void Write(IWriter& aWriter) = 0;    // THROWS WriterError
    virtual void Destroy() = 0;
    virtual ~IResourceHandler() {}
};

class IResourceManager
{
public:
    virtual IResourceHandler& CreateResourceHandler(const Brx& aResourceTail) = 0;  // THROWS ResourceInvalid
    virtual ~IResourceManager() {}
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
    virtual void Receive(const Brx& aMessage) = 0;
    virtual void Destroy() = 0;
    virtual ~ITab() {}
};

/**
 * Interface representing a message that can be sent.
 */
class ITabMessage
{
public:
    virtual void Send(IWriter& aWriter) = 0;
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

// FIXME - rename to IWebAppTimer
class IFrameworkTimer;

class ITabCreator
{
public:
    virtual ITab& Create(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList) = 0;    // throws TabAllocatorFull
    virtual ~ITabCreator() {}
};

/**
 * Interface representing an HTTP application that will make use of the
 * framework. Requires implementations for returning a new tab and the
 * processing of resources.
 */
class IWebApp : public ITabCreator, public IResourceManager
{
public:
    //virtual IFrameworkTimer& CreateTimer() = 0;         // throws TimerCreationFailed
    virtual const Brx& ResourcePrefix() const = 0;
    virtual ~IWebApp() {}
};


// Classes relevant to the HTTP framework.

// Private classes for internal tab + session management.

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

class IFrameworkSemaphore
{
public:
    virtual void Wait() = 0;
    virtual TBool Clear() = 0;
    virtual void Signal() = 0;
    virtual ~IFrameworkSemaphore() {}
};

class IFrameworkTabHandler : public ITabHandler
{
public: // from ITabHandler
    virtual void Send(ITabMessage& aMessage) = 0;
public:
    virtual void LongPoll(IWriter& aWriter) = 0;    // THROWS WriterError.
    virtual void Enable() = 0;
    virtual void Disable() = 0; // Disallow LongPoll()/Send() calls.
    virtual ~IFrameworkTabHandler() {}
};

/**
 * Internal tab handler API for framework.
 */
class FrameworkTabHandler : public IFrameworkTabHandler, public IFrameworkTimerHandler
{
public:
    FrameworkTabHandler(IFrameworkSemaphore& aSemRead, IFrameworkSemaphore& aSemWrite, IFrameworkTimer& aTimer, TUint aSendQueueSize, TUint aSendTimeoutMs);
    ~FrameworkTabHandler();
private: // from IFrameworkTabHandler
    void Send(ITabMessage& aMessage) override;
    void LongPoll(IWriter& aWriter) override;   // THROWS WriterError.
    void Enable() override;  // Allow new polls/sends to take place.
    void Disable() override; // Cancel blocking send and clear FIFO.
private: // from IFrameworkTimerHandler
    void Complete() override;
private:
    const TUint iSendTimeoutMs;
    FifoLiteDynamic<ITabMessage*> iFifo;
    TBool iEnabled;
    TBool iPolling;
    Mutex iLock;
    IFrameworkSemaphore& iSemRead;
    IFrameworkSemaphore& iSemWrite;
    IFrameworkTimer& iTimer;
};

class FrameworkTimer : public IFrameworkTimer
{
public:
    FrameworkTimer(Environment& aEnv, const TChar* aStringId, TUint aNumericId);
    ~FrameworkTimer();
public: // from IFrameworkTimer
    void Start(TUint aDurationMs, IFrameworkTimerHandler& aHandler) override;
    void Cancel() override;
private:
    void Complete();
private:
    const TChar* iStringId;
    const TUint iNumericId;
    Timer iTimer;
    IFrameworkTimerHandler* iHandler;
    Mutex iLock;
};

class ITabDestroyHandler
{
public:
    virtual void Destroy(TUint aId) = 0;
    virtual ~ITabDestroyHandler() {}
};

class FrameworkSemaphore : public IFrameworkSemaphore
{
public:
    FrameworkSemaphore(const TChar* aName, TUint aCount);
public: // from IFrameworkSemaphore
    void Wait() override;
    TBool Clear() override;
    void Signal() override;
private:
    Semaphore iSem;
};

class IFrameworkTab
{
public:
    static const TUint kInvalidTabId = 0;
public:
    virtual TUint SessionId() const = 0;
    virtual void CreateTab(TUint aSessionId, ITabCreator& aTabCreator, ITabDestroyHandler& aDestroyHandler, const std::vector<char*>& aLanguages) = 0;
    virtual void Clear() = 0;   // Terminates any blocking sends or outstanding timers.
    virtual void Receive(const Brx& aMessage) = 0;
    virtual void LongPoll(IWriter& aWriter) = 0;    // Terminates poll timer on entry; restarts poll timer on exit. THROWS WriterError.
    virtual ~IFrameworkTab() {}
};

/**
 * Internal tab for framework.
 */
class FrameworkTab : public IFrameworkTab, public ITabHandler, public IFrameworkTimerHandler
{

public:
    FrameworkTab(TUint aTabId, IFrameworkTimer& aTimer, IFrameworkTabHandler& aTabHandler, TUint aPollTimeoutMs);
    ~FrameworkTab();
public: // from IFrameworkTab
    TUint SessionId() const override;
    void CreateTab(TUint aSessionId, ITabCreator& aTabCreator, ITabDestroyHandler& aDestroyHandler, const std::vector<char*>& aLanguages) override;
    void Clear() override;   // Terminates any blocking sends or outstanding timers.
    void Receive(const Brx& aMessage) override;
    void LongPoll(IWriter& aWriter) override;    // Terminates poll timer on entry; restarts poll timer on exit. THROWS WriterError.
private: // from ITabHandler
    void Send(ITabMessage& aMessage) override;
private: // from IFrameworkTimerHandler
    void Complete() override;
private:
    const TUint iTabId;
    const TUint iPollTimeoutMs;
    IFrameworkTabHandler& iHandler;
    IFrameworkTimer& iTimer;
    TUint iSessionId;
    ITabDestroyHandler* iDestroyHandler;
    ITab* iTab;
    std::vector<Bws<10>> iLanguages; // Takes ownership of pointers.
    TBool iPollActive;
    mutable Mutex iLock;
};

/**
 * Class that brings together a FrameworkTab with a FrameworkTabHandler and the
 * associated Semaphores and Timers that are required.
 */
class FrameworkTabFull : public IFrameworkTab
{
public:
    FrameworkTabFull(Environment& aEnv, TUint aTabId, TUint aSendQueueSize, TUint aSendTimeoutMs, TUint aPollTimeoutMs);
public: // from IFrameworkTab
    TUint SessionId() const override;
    void CreateTab(TUint aSessionId, ITabCreator& aTabCreator, ITabDestroyHandler& aDestroyHandler, const std::vector<char*>& aLanguages) override;
    void Clear() override;
    void Receive(const Brx& aMessage) override;
    void LongPoll(IWriter& aWriter) override;   // THROWS WriterError.
private:
    FrameworkSemaphore iSemRead;
    FrameworkSemaphore iSemWrite;
    FrameworkTimer iTabHandlerTimer;
    FrameworkTabHandler iTabHandler;
    FrameworkTimer iTabTimer;
    FrameworkTab iTab;
};

/**
 * Interface allowing a client to create and interact with IWebApp tabs.
 */
class ITabManager : public ITabDestroyHandler
{
public: // from ITabDestroyHandler
    virtual void Destroy(TUint aId) = 0;
public:
    virtual TUint CreateTab(ITabCreator& aTabCreator, const std::vector<char*>& aLanguageList) = 0;    // Returns tab ID; THROWS TabManagerFull, TabAllocatorFull.

    // Following calls may all throw InvalidTabId.
    virtual void LongPoll(TUint aId, IWriter& aWriter) = 0;  // Will block until something is written or poll timeout. THROWS WriterError on write failure.
    virtual void Receive(TUint aId, const Brx& aMessage) = 0;
    virtual ~ITabManager() {}
};

class TabManager : public ITabManager, private INonCopyable
{
public:
    TabManager(const std::vector<IFrameworkTab*>& aTabs);
    ~TabManager();
    void Disable(); // Terminate any blocking LongPoll calls and prevent any new tabs from being created.
public: // from ITabManager
    TUint CreateTab(ITabCreator& aTabCreator, const std::vector<char*>& aLanguageList) override;
    void LongPoll(TUint aId, IWriter& aWriter) override;    // THROWS WriterError.
    void Receive(TUint aId, const Brx& aMessage) override;
    void Destroy(TUint aId) override;
private:
    const std::vector<IFrameworkTab*> iTabs;
    TUint iNextSessionId;
    TBool iEnabled;
    Mutex iLock;
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
    virtual IWebApp& GetApp(const Brx& aResourcePrefix) = 0; // THROWS InvalidAppPrefix
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
    ITab& Create(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList) override;
    const Brx& ResourcePrefix() const override;
private:
    IWebApp* iWebApp;
    FunctorPresentationUrl iFunctor;
};

class HttpSession;

class WebAppFrameworkInitParams
{
private:
    static const TUint kDefaultPort = 0;
    static const TUint kDefaultMinServerThreadsResources = 1;
    static const TUint kDefaultMaxServerThreadsLongPoll = 1;
    static const TUint kDefaultSendQueueSize = 1024;
    static const TUint kDefaultSendTimeoutMs = 5000;
    static const TUint kDefaultLongPollTimeoutMs = 5000;
public:
    WebAppFrameworkInitParams();
    void SetPort(TUint aPort);
    void SetMinServerThreadsResources(TUint aThreadResourcesCount);
    void SetMaxServerThreadsLongPoll(TUint aThreadLongPollCount);
    void SetSendQueueSize(TUint aSendQueueSize);
    void SetSendTimeoutMs(TUint aSendTimeoutMs);
    void SetLongPollTimeoutMs(TUint aLongPollTimeoutMs);
    TUint Interface() const;
    TUint Port() const;
    TUint MinServerThreadsResources() const;
    TUint MaxServerThreadsLongPoll() const;
    TUint SendQueueSize() const;
    TUint SendTimeoutMs() const;
    TUint LongPollTimeoutMs() const;
private:
    TUint iPort;
    TUint iThreadResourcesCount;
    TUint iThreadLongPollCount;
    TUint iSendQueueSize;
    TUint iSendTimeoutMs;
    TUint iLongPollTimeoutMs;
};

/*
 * FIXME - If we wish to support multiple WebApps in the WebAppFramework, there are two approaches to tab limits:
 * - WebAppFramework dictates how many tabs each WebApp must support (i.e., memory usage is: WAF tab limit * app count).
 * -- Forces fixed minimum bounds of memory usage.
 * -- Guarantees that only limit exceeded will be number of long poll server threads.
 * - Each WebApp can define how many tabs it will provide.
 * -- Different apps can support different requirements to minimise memory usage.
 * -- Must have a way of distinguishing when WebApp has exhausted available tabs and when WebAppFramework has exhausted available long poll server threads (e.g., WAF supports 4 long poll tabs, but app only supports 3 tabs, and client tries to load 4 tabs).
 * -- HttpSession::Post() should probably send up a status string, along with the 503 error, along the lines of the following for the respective conditions above:
 * --- When TabAllocatorFull caught: "Error: Too many instances of Konfig app open. Please close an instance of Konfig.", where "Konfig" is replaced with relevant app's user-friendly name.
 * --- When TabManagerFull caught: "Error: Too many server requests for apps. Please close an existing app."
 */

// FIXME - handle redirects from "/" to "/index.html"? - job of resource handler
class WebAppFramework : public IWebAppFramework, public IWebAppManager, public IResourceManager, public IServer
{
public:
    static const TChar* kName;
    static const TChar* kAdapterCookie;
    static const Brn kSessionPrefix;
private:
    // NOTE: No need for a "spare" session. Impossible to enforce such a
    // feature, and as long as normal server threads >= 1, will always
    // (eventually) serve all requests, as there will be no calls which block
    // for long periods.
    // NOTE: This is the MINIMUM number of server resource threads, because the
    // server will also use long poll threads for serving static resources, if
    // there are any free.
    static const TUint kDefaultMinResourceServerThreads = 1;
    static const TUint kDefaultLongPollServerThreads = 1;
    static const TUint kMaxSessionNameBytes = 32;  // Should be capable of storing string of form kSessionPrefix + ID (0-99) + '\0', e.g., "WebUiSession01\0".
private:
    class BrxPtrCmp
    {
    public:
        TBool operator()(const Brx* aStr1, const Brx* aStr2) const;
    };
private:
    typedef std::pair<const Brx*, WebAppInternal*> WebAppPair;
    typedef std::map<const Brx*, WebAppInternal*, BrxPtrCmp> WebAppMap;
public:
    // FIXME - replace this with an init params object, similar to what ohNet and the pipeline take.
    WebAppFramework(Environment& aEnv, WebAppFrameworkInitParams* aInitParms);
    ~WebAppFramework();
    void Start();
    /**
     * Set the app that requests should be directed to if no resource prefix is
     * provided in the request path.
     */
    void SetDefaultApp(const Brx& aResourcePrefix); // THROWS InvalidAppPrefix
public: // from IWebAppFramework
    void Add(IWebApp* aWebApp, FunctorPresentationUrl aFunctor) override;
private: // from IWebAppManager
    IWebApp& GetApp(const Brx& aResourcePrefix) override;  // THROWS InvalidAppPrefix
private: // from IResourceManager
    IResourceHandler& CreateResourceHandler(const Brx& aResource) override;  // THROWS ResourceInvalid
public: // from IServer
    TUint Port() const override;
    TIpAddress Interface() const override;
private:
    void AddSessions();
    void CurrentAdapterChanged();
private:
    Environment& iEnv;
    WebAppFrameworkInitParams* iInitParams;
    TUint iAdapterListenerId;
    SocketTcpServer* iServer;
    TabManager* iTabManager;    // Should there be one tab manager for ALL apps, or one TabManager per app? (And, similarly, one set of server sessions for all apps, or a set of server sessions per app? Also, need at least one extra session for receiving (and declining) additional long polling requests.)
    WebAppMap iWebApps;
    std::vector<std::reference_wrapper<HttpSession>> iSessions;
    IWebApp* iDefaultApp;
    TBool iStarted;
    NetworkAdapter* iCurrentAdapter;
    mutable Mutex iMutex;
};

/**
 * HttpSession that handles serving files (via GET), processing POST requests
 * and allows long polling.
 */
class HttpSession : public SocketTcpSession
{
private:
    static const TUint kMaxRequestBytes = 4*1024;
    static const TUint kMaxResponseBytes = 4*1024;
    static const TUint kReadTimeoutMs = 5 * 1000;
    static const TUint kPollTimeoutMs = 5 * 1000;
    static const TUint kPollPeriodTimeoutMs = 5*1000;
public:
    HttpSession(Environment& aEnv, IWebAppManager& aAppManager, ITabManager& aTabManager, IResourceManager& aResourceManager);
    ~HttpSession();
    // Will return 503 (Service Unavailable) to all requests until StartSession() is called.
    void StartSession();    // Avoid clash with SocketTcpSession::Start().
private: // from SocketTcpSession
    void Run();
private:
    void Error(const HttpStatus& aStatus);
    void Get();
    void Post();
    void WriteLongPollHeaders();
private:
    IWebAppManager& iAppManager;
    ITabManager& iTabManager;
    IResourceManager& iResourceManager;
    Srx* iReadBuffer;
    ReaderUntil* iReaderUntilPreChunker;
    ReaderHttpRequest* iReaderRequest;
    ReaderHttpChunked* iReaderChunked;
    ReaderUntil* iReaderUntil;
    Sws<kMaxResponseBytes>* iWriterBuffer;
    WriterHttpResponse* iWriterResponse;
    HttpHeaderHost iHeaderHost;
    HttpHeaderTransferEncoding iHeaderTransferEncoding;
    HttpHeaderConnection iHeaderConnection;
    Net::HeaderAcceptLanguage iHeaderAcceptLanguage;
    const HttpStatus* iErrorStatus;
    TBool iResponseStarted;
    TBool iResponseEnded;
    TBool iResourceWriterHeadersOnly;
    TBool iStarted;
    Mutex iLock;
};

class MimeUtils
{
    static const Brn kExtCss;
    static const Brn kExtJs;
    static const Brn kExtXml;
    static const Brn kExtBmp;
    static const Brn kExtGif;
    static const Brn kExtJpeg;
    static const Brn kExtPng;
public:
    static Brn MimeTypeFromUri(const Brx& aUri);
};

} // namespace Web
} // namespace OpenHome

