#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/File.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Net/Private/DviServerUpnp.h>

EXCEPTION(ResourceInvalid);
EXCEPTION(TabAllocatorFull);    // Thrown by an IWebApp when its allocator is full.
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
    virtual IResourceHandler& CreateResourceHandler(const OpenHome::Brx& aResourceTail) = 0;  // THROWS ResourceInvalid
    virtual ~IResourceManager() {}
};

// FIXME - file handling should eventually be replaced with a cross-platform
// resource handling layer. This currently only works on posix-style filesystems.
// FIXME - make this thread aware
// - could state of Allocated() be changed while a (thread-safe) ResourceManager is inspecting it?
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
    virtual ITab& Create(ITabHandler& aHandler, const std::vector<const Brx*>& aLanguageList) = 0;    // throws TabAllocatorFull
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
    virtual const OpenHome::Brx& ResourcePrefix() const = 0;
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
    void LongPoll(IWriter& aWriter) override;
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
    FrameworkTimer(OpenHome::Environment& aEnv);
    ~FrameworkTimer();
public: // from IFrameworkTimer
    void Start(TUint aDurationMs, IFrameworkTimerHandler& aHandler) override;
    void Cancel() override;
private:
    void Complete();
private:
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
    virtual void CreateTab(TUint aSessionId, ITabCreator& aTabCreator, ITabDestroyHandler& aDestroyHandler, const std::vector<const Brx*>& aLanguages) = 0;
    virtual void Clear() = 0;   // Terminates any blocking sends or outstanding timers.
    virtual void Receive(const Brx& aMessage) = 0;
    virtual void LongPoll(IWriter& aWriter) = 0;    // Terminates poll timer on entry; restarts poll timer on exit.
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
    void CreateTab(TUint aSessionId, ITabCreator& aTabCreator, ITabDestroyHandler& aDestroyHandler, const std::vector<const Brx*>& aLanguages) override;
    void Clear() override;   // Terminates any blocking sends or outstanding timers.
    void Receive(const Brx& aMessage) override;
    void LongPoll(IWriter& aWriter) override;    // Terminates poll timer on entry; restarts poll timer on exit.
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
    std::vector<const Brx*> iLanguages; // Takes ownership of pointers.
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
    void CreateTab(TUint aSessionId, ITabCreator& aTabCreator, ITabDestroyHandler& aDestroyHandler, const std::vector<const Brx*>& aLanguages) override;
    void Clear() override;
    void Receive(const Brx& aMessage) override;
    void LongPoll(IWriter& aWriter) override;
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
    virtual TUint CreateTab(ITabCreator& aTabCreator, const std::vector<const Brx*>& aLanguageList) = 0;    // Returns tab ID; THROWS TabManagerFull, TabAllocatorFull.

    // Following calls may all throw InvalidTabId.
    virtual void LongPoll(TUint aId, IWriter& aWriter) = 0;  // Will block until something is written or poll timeout.
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
    TUint CreateTab(ITabCreator& aTabCreator, const std::vector<const Brx*>& aLanguageList) override;
    void LongPoll(TUint aId, IWriter& aWriter) override;
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
    ITab& Create(ITabHandler& aHandler, const std::vector<const Brx*>& aLanguageList) override;
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
    // FIXME - Can't call Add() after Start()
public: // from IWebAppFramework
    void Add(IWebApp* aWebApp, FunctorPresentationUrl aFunctor) override;
private: // from IWebAppManager
    IWebApp& GetApp(const OpenHome::Brx& aResourcePrefix) override;  // THROWS InvalidAppPrefix
private: // from IResourceManager
    IResourceHandler& CreateResourceHandler(const OpenHome::Brx& aResource) override;  // THROWS ResourceInvalid
public: // from IServer
    TUint Port() const override;
    TIpAddress Interface() const override;
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
    TabManager* iTabManager;    // Should there be one tab manager for ALL apps, or one TabManager per app? (And, similarly, one set of server sessions for all apps, or a set of server sessions per app? Also, need at least one extra session for receiving (and declining) additional long polling requests.)

    // FIXME - what if this is created with a max of 4 tabs and an app is added that is only capable of creating 3 apps and 4 clients try to load apps?

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

