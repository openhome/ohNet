#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Web/WebAppFramework.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/File.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/MimeTypes.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Configuration/ConfigManager.h>

#include <functional>
#include <limits>

using namespace OpenHome;
using namespace OpenHome::Configuration;
using namespace OpenHome::Web;


// FrameworkTabHandler

FrameworkTabHandler::FrameworkTabHandler(IFrameworkSemaphore& aSemRead, IFrameworkSemaphore& aSemWrite, IFrameworkTimer& aTimer, TUint aSendQueueSize, TUint aSendTimeoutMs)
    : iSendTimeoutMs(aSendTimeoutMs)
    , iFifo(aSendQueueSize)
    , iEnabled(false)
    , iPolling(false)
    , iLock("FTHL")
    , iSemRead(aSemRead)
    , iSemWrite(aSemWrite)
    , iTimer(aTimer)
{
    iSemRead.Clear();
    iSemWrite.Clear();
    // Allow msgs to be queued via Send().
    for (TUint i=0; i<aSendQueueSize; i++) {
        iSemWrite.Signal();
    }
}

FrameworkTabHandler::~FrameworkTabHandler()
{
    AutoMutex a(iLock);
    ASSERT(iFifo.SlotsUsed() == 0);
}

void FrameworkTabHandler::LongPoll(IWriter& aWriter)
{
    // This routine has 3 paths:
    // - There are >= 1 msgs in FIFO. If so, output and return.
    // - There are no msgs in FIFO. Block until a msg arrives via Send(), output it, and return.
    // - There are no msgs in FIFO. Block until timer triggers a timeout and return.
    {
        // Don't accept any long polls if in an interrupted state.
        // Don't accept long polls if already polling (i.e., misbehaving client is making overlapping long polls).
        AutoMutex a(iLock);
        if (!iEnabled || iPolling) {
            return;
        }
        iPolling = true;
    }

    // Start timer.
    iTimer.Start(iSendTimeoutMs, *this);

    TBool msgOutput = false;
    for (;;) {
        TBool cancelTimer = false;
        TBool slotsZero = false;
        iSemRead.Wait();
        {
            // Check if this was interrupted.
            AutoMutex a(iLock);
            if (!iEnabled || !iPolling) {
                // No need to cancel timer.
                // Can only get here via Disable() call (which cancels timer if
                // polling active) or Complete() call (in which case, timer has
                // already fired due to timeout).
                if (msgOutput) {
                    aWriter.Write(Brn("]"));
                }
                return;
            }

            ITabMessage* msg = iFifo.Read();
            try {
                if (!msgOutput) {
                    // Now committed to sending a msg in response to this lp.
                    // Cancel timer and clear polling state.
                    cancelTimer = true;
                    aWriter.Write(Brn("["));
                    msgOutput = true;
                }
                msg->Send(aWriter);
                // All but last msg should be followed by "," in a JSON array.
                if (iFifo.SlotsUsed() > 0) {
                    aWriter.Write(Brn(","));
                }
            }
            catch (WriterError&) {
                // Destroy msg and rethrow so that higher level can take
                // appropriate action.
                msg->Destroy();
                iSemWrite.Signal();
                if(cancelTimer) {
                    iTimer.Cancel();
                }
                throw;
            }
            msg->Destroy();
            iSemWrite.Signal();

            // If FIFO has been exhausted, output what was queued and return
            // instead of blocking for entire long poll duration.
            if (iFifo.SlotsUsed() == 0) {
                iPolling = false;
                if (msgOutput) {
                    aWriter.Write(Brn("]"));
                }
                slotsZero = true;
            }
        }
        if(cancelTimer)
        {
            iTimer.Cancel();
        }
        if(slotsZero)
        {
            return;
        }
    }
}

void FrameworkTabHandler::Disable()
{
    // Set interrupted state so that no further polls/sends can take place.
    TBool polling;
    {
        AutoMutex a(iLock);
        iEnabled = false;
        polling = iPolling;
    }

    if(polling){
        iTimer.Cancel();
        AutoMutex a(iLock);
        iPolling = false;
    }

    // Only need to signal iSemRead here. When FIFO is cleared, iSemWrite will be signalled.
    iSemRead.Signal();

    AutoMutex a(iLock);
    while (iFifo.SlotsUsed() > 0) {
        ITabMessage* msg = iFifo.Read();
        msg->Destroy();
        iSemWrite.Signal(); // Unblock any Send() calls. Should just discard messages.
    }
}

void FrameworkTabHandler::Enable()
{
    AutoMutex a(iLock);
    iEnabled = true;
    // Clear iSemRead in case it wasn't being waited on when Disable() was last called.
    // No need to clear iSemWrite as its Wait()/Signal() calls should always match up.
    iSemRead.Clear();
}

void FrameworkTabHandler::Send(ITabMessage& aMessage)
{
    // Blocks until message can be sent.

    iSemWrite.Wait();
    AutoMutex a(iLock);
    if (!iEnabled) {
        aMessage.Destroy();
        iSemWrite.Signal(); // Dropped message instead of putting in FIFO, so can just resignal.
    }
    else {
        iFifo.Write(&aMessage);
        iSemRead.Signal();
    }
}

void FrameworkTabHandler::Complete()
{
    AutoMutex a(iLock);
    if (iPolling) {
        iPolling = false;
        iSemRead.Signal();      // FIXME - will this mess up sem count? Not if we are still in blocking send method. But what if Cancel() is called?
    }
}


// FrameworkTimer

FrameworkTimer::FrameworkTimer(Environment& aEnv, const TChar* aStringId, TUint aNumericId)
    : iStringId(aStringId)
    , iNumericId(aNumericId)
    , iTimer(aEnv, MakeFunctor(*this, &FrameworkTimer::Complete), "WebUiTimer")
    , iHandler(nullptr)
    , iLock("FRTL")
{
    // Make use of iStringId and iNumericId to prevent compilers complaining about unused members.
    ASSERT(strlen(iStringId) > 0);
    ASSERT(iNumericId >= 0);
}

FrameworkTimer::~FrameworkTimer()
{
    iTimer.Cancel();
}

void FrameworkTimer::Start(TUint aDurationMs, IFrameworkTimerHandler& aHandler)
{
    //LOG(kHttp, "FrameworkTimer::Start iStringId: %s, iNumericId: %u, aDurationMs: %u\n", iStringId, iNumericId, aDurationMs);
    AutoMutex a(iLock);
    ASSERT(iHandler == nullptr);
    iHandler = &aHandler;
    iTimer.FireIn(aDurationMs);
}

void FrameworkTimer::Cancel()
{
    //LOG(kHttp, "FrameworkTimer::Cancel iStringId: %s, iNumericId: %u\n", iStringId, iNumericId);
    TBool nullHandler;
    {
        AutoMutex a(iLock);
        nullHandler = (iHandler == nullptr);
    } //Mutex must be split over two blocks, because iTimer has callback mutex

    if (!nullHandler) {
        iTimer.Cancel();
    }

    {
        AutoMutex b(iLock);
        iHandler = nullptr;
    }
}

void FrameworkTimer::Complete()
{
    //LOG(kHttp, "FrameworkTimer::Complete: iStringId: %s, iNumericId: %u\n", iStringId, iNumericId);
    IFrameworkTimerHandler* handler = nullptr;
    {
        AutoMutex a(iLock);
        ASSERT(iHandler != nullptr);
        handler = iHandler;
        iHandler = nullptr;
    }
    handler->Complete();    // Avoid issues with attempted recursive locks on mutex if client calls back into Start()/Cancel() during callback.
}


// FrameworkSemaphore

FrameworkSemaphore::FrameworkSemaphore(const TChar* aName, TUint aCount)
    : iSem(aName, aCount)
{
}

void FrameworkSemaphore::Wait()
{
    iSem.Wait();
}

TBool FrameworkSemaphore::Clear()
{
    return iSem.Clear();
}

void FrameworkSemaphore::Signal()
{
    iSem.Signal();
}


// FrameworkTab

FrameworkTab::FrameworkTab(TUint aTabId, IFrameworkTimer& aTimer, IFrameworkTabHandler& aTabHandler, TUint aPollTimeoutMs)
    : iTabId(aTabId)
    , iPollTimeoutMs(aPollTimeoutMs)
    , iHandler(aTabHandler)
    , iTimer(aTimer)
    , iSessionId(kInvalidTabId)
    , iDestroyHandler(nullptr)
    , iTab(nullptr)
    , iPollActive(false)
    , iLock("FRTL")
{
}

FrameworkTab::~FrameworkTab()
{
    // Owner must have called Clear().
    //TBool tabIsAllocated = false;
    //{
    //    AutoMutex a(iLock);
    //    tabIsAllocated = (iTab != nullptr);
    //}

    //if (tabIsAllocated) {
    //    Clear(); // Clear before asserting to avoid memory leaks in tests.
    //    ASSERTS();
    //}

    // Owner must have called Clear().
    AutoMutex a(iLock);
    ASSERT(iTab == nullptr);
}

TUint FrameworkTab::SessionId() const
{
    AutoMutex a(iLock);
    return iSessionId;
}

void FrameworkTab::CreateTab(TUint aSessionId, ITabCreator& aTabCreator, ITabDestroyHandler& aDestroyHandler, const std::vector<char*>& aLanguages)
{
    LOG(kHttp, "FrameworkTab::CreateTab iSessionId: %u, iTabId: %u\n", iSessionId, iTabId);
    ASSERT(aSessionId != kInvalidTabId);
    AutoMutex a(iLock);
    ASSERT(iTab == nullptr);
    iSessionId = aSessionId;
    iDestroyHandler = &aDestroyHandler;
    iHandler.Enable();          // Ensure TabHandler is ready to receive messages (and not drop them).
    iLanguages.clear();
    for (auto it=aLanguages.begin(); it!=aLanguages.end(); ++it) {
        Bws<10> lang(*it);
        for (TUint i=0; i<lang.Bytes(); i++) {
            lang[i] = Ascii::ToLowerCase(lang[i]);
        }
        iLanguages.push_back(lang);
    }
    try {
        iTab = &aTabCreator.Create(iHandler, iLanguages);
        iTimer.Start(iPollTimeoutMs, *this);
    }
    catch (TabAllocatorFull&) {
        iHandler.Disable();
        iSessionId = kInvalidTabId;
        iDestroyHandler = nullptr;
        iLanguages.clear();
        throw;
    }
}

void FrameworkTab::Clear()
{
    // Should not be used internally. Should only be called via owner of this class.

    // Must be forgiving for cases where:
    // - Tab is in use, but framework is being destroyed.
    // - Tab has already been destroyed, but destroy is being called again (e.g., where a terminate request has come in from a client while a long poll request is active. The terminate request could cause a WriterError during the long poll request, which would cause Destroy() to be called again).
    AutoMutex a(iLock);

    if (iTab != nullptr) {
        iTimer.Cancel();    // FIXME - recursive if this Clear() comes from a FrameworkTab::Complete() call.
        iHandler.Disable();   // Should reject/drop any further calls to Send() from ITab.
        iSessionId = kInvalidTabId;
        iTab->Destroy();
        iTab = nullptr;
        iLanguages.clear();
    }
}

void FrameworkTab::LongPoll(IWriter& aWriter)
{
    {
        AutoMutex a(iLock);
        ASSERT(iTab != nullptr);

        if (iPollActive) {
            return;
        }

        iTimer.Cancel();
        iPollActive = true;
    }
    iHandler.LongPoll(aWriter);
    // Will only reach here if blocking send isn't terminated (i.e., tab is still active).
    AutoMutex a(iLock);
    if (iTab != nullptr) {
        // Tab hasn't been deallocated, so expect another poll.
        iTimer.Start(iPollTimeoutMs, *this);
    }
    iPollActive = false;
}

void FrameworkTab::Receive(const Brx& aMessage)
{
    AutoMutex a(iLock);
    ASSERT(iTab != nullptr);
    iTab->Receive(aMessage);
}

void FrameworkTab::Send(ITabMessage& aMessage)
{
    {
        AutoMutex a(iLock);
        ASSERT(iTab != nullptr);
    }

    // Can't lock here. If message queue is full, could cause deadlock.
    iHandler.Send(aMessage);
}

void FrameworkTab::Complete()
{
    iDestroyHandler->Destroy(iSessionId);
}


// FrameworkTabFull

FrameworkTabFull::FrameworkTabFull(Environment& aEnv, TUint aTabId, TUint aSendQueueSize, TUint aSendTimeoutMs, TUint aPollTimeoutMs)
    : iSemRead("FTSR", 0)
    , iSemWrite("FTSW", aSendQueueSize)
    , iTabHandlerTimer(aEnv, "TabHandlerTimer", aTabId)
    , iTabHandler(iSemRead, iSemWrite, iTabHandlerTimer, aSendQueueSize, aSendTimeoutMs)
    , iTabTimer(aEnv, "TabTimer", aTabId)
    , iTab(aTabId, iTabTimer, iTabHandler, aPollTimeoutMs)
{
}

TUint FrameworkTabFull::SessionId() const
{
    return iTab.SessionId();
}

void FrameworkTabFull::CreateTab(TUint aSessionId, ITabCreator& aTabCreator, ITabDestroyHandler& aDestroyHandler, const std::vector<char*>& aLanguages)
{
    iTab.CreateTab(aSessionId, aTabCreator, aDestroyHandler, aLanguages);
}

void FrameworkTabFull::Clear()
{
    iTab.Clear();
}

void FrameworkTabFull::Receive(const Brx& aMessage)
{
    iTab.Receive(aMessage);
}

void FrameworkTabFull::LongPoll(IWriter& aWriter)
{
    iTab.LongPoll(aWriter);
}


// TabManager

TabManager::TabManager(const std::vector<IFrameworkTab*>& aTabs)
    : iTabs(aTabs)
    , iNextSessionId(IFrameworkTab::kInvalidTabId+1)
    , iEnabled(true)
    , iLock("TBML")
{
}

TabManager::~TabManager()
{
    AutoMutex a(iLock);
    ASSERT(!iEnabled);  // Disable() must have been called.
    for (TUint i=0; i<iTabs.size(); i++) {
        iTabs[i]->Clear();
        delete iTabs[i];    // Will remove any references still held (i.e., when client holds a browser tab open).
    }
}

void TabManager::Disable()
{
    AutoMutex a(iLock);
    iEnabled = false;   // Invalidate all future calls to TabManager.

    // Clear active tabs. Will terminate any blocking LongPolls.
    for (TUint i=0; i<iTabs.size(); i++) {
        if (iTabs[i]->SessionId() != FrameworkTab::kInvalidTabId) {
            iTabs[i]->Clear();
        }
    }
}

TUint TabManager::CreateTab(ITabCreator& aTabCreator, const std::vector<char*>& aLanguageList)
{
    AutoMutex a(iLock);
    if (!iEnabled) {
        THROW(TabManagerFull);
    }

    for (TUint i=0; i<iTabs.size(); i++) {
        if (iTabs[i]->SessionId() == FrameworkTab::kInvalidTabId) {
            const TUint sessionId = iNextSessionId++;
            iTabs[i]->CreateTab(sessionId, aTabCreator, *this, aLanguageList); // Takes ownership of (buffers in) language list.
            return sessionId;
        }
    }
    LOG(kHttp, "TabManager::CreateTab tab manager full\n");
    THROW(TabManagerFull);  // Shouldn't reach here unless there isn't enough space.
}

void TabManager::LongPoll(TUint aId, IWriter& aWriter)
{
    if (aId == IFrameworkTab::kInvalidTabId) {
        LOG(kHttp, "TabManager::LongPoll kInvalidTabId\n");
        THROW(InvalidTabId);
    }

    LOG(kHttp, "TabManager::LongPoll aId: %u\n", aId);
    IFrameworkTab* tab = nullptr;
    {
        AutoMutex a(iLock);
        if (!iEnabled) {
            THROW(InvalidTabId);
        }

        for (TUint i=0; i<iTabs.size(); i++) {
            if (iTabs[i]->SessionId() == aId) {
                tab = iTabs[i];
                break;
            }
        }
    }
    if (tab == nullptr) {
        THROW(InvalidTabId);
    }
    // FIXME - race condition. As lock is released before this call, tab could potentially have been Destroy()ed and then re-assigned to a new tab before the LongPoll() call.
    // Maybe have reference counting on FrameworkTabs to avoid that, or set flag to show tab is currently being long-polled and shouldn't be destroyed until the long-poll is complete. Is the latter just a limited form of reference counting?
    tab->LongPoll(aWriter);
}

void TabManager::Receive(TUint aId, const Brx& aMessage)
{
    if (aId == IFrameworkTab::kInvalidTabId) {
        LOG(kHttp, "TabManager::Receive kInvalidTabId, aMessage: %.*s\n", PBUF(aMessage));
        THROW(InvalidTabId);
    }

    LOG(kHttp, "TabManager::Receive aId: %u\n", aId);
    {
        AutoMutex a(iLock);
        if (!iEnabled) {
            THROW(InvalidTabId);
        }

        for (TUint i=0; i<iTabs.size(); i++) {
            IFrameworkTab* tab = iTabs[i];
            if (tab->SessionId() == aId) {
                tab->Receive(aMessage);
                return;
            }
        }
    }
    THROW(InvalidTabId);
}

void TabManager::Destroy(TUint aId)
{
    if (aId == IFrameworkTab::kInvalidTabId) {
        LOG(kHttp, "TabManager::Destroy kInvalidTabId\n");
        THROW(InvalidTabId);
    }

    LOG(kHttp, "TabManager::Destroy aId: %u\n", aId);
    {
        AutoMutex a(iLock);
        if (!iEnabled) {
            THROW(InvalidTabId);
        }

        for (TUint i=0; i<iTabs.size(); i++) {
            IFrameworkTab* tab = iTabs[i];
            if (tab->SessionId() == aId) {
                tab->Clear();
                return;
            }
        }
    }
    THROW(InvalidTabId);
}


// WebAppFramework::BrxPtrCmp

TBool WebAppFramework::BrxPtrCmp::operator()(const Brx* aStr1, const Brx* aStr2) const
{
    return BufferCmp()(*aStr1, *aStr2);
}


// WebAppInternal

WebAppInternal::WebAppInternal(IWebApp* aWebApp, FunctorPresentationUrl aFunctor)
    : iWebApp(aWebApp)
    , iFunctor(aFunctor)
{
}

WebAppInternal::~WebAppInternal()
{
    delete iWebApp;
}

void WebAppInternal::SetPresentationUrl(const Brx& aPresentationUrl)
{
    iFunctor(aPresentationUrl);
}

IResourceHandler& WebAppInternal::CreateResourceHandler(const Brx& aResource)
{
    return iWebApp->CreateResourceHandler(aResource);
}

ITab& WebAppInternal::Create(ITabHandler& aHandler, const std::vector<Bws<10>>& aLanguageList)
{
    return iWebApp->Create(aHandler, aLanguageList);
}

const Brx& WebAppInternal::ResourcePrefix() const
{
    return iWebApp->ResourcePrefix();
}


// WebAppFramework

const TChar* WebAppFramework::kName("WebUiServer");
const TChar* WebAppFramework::kAdapterCookie("WebAppFramework");
const Brn WebAppFramework::kSessionPrefix("WebUiSession");

WebAppFramework::WebAppFramework(Environment& aEnv, TIpAddress /*aInterface*/, TUint aPort, TUint aMaxSessions, TUint aSendQueueSize, TUint aSendTimeoutMs, TUint aPollTimeoutMs)
    : iEnv(aEnv)
    , iPollTimer(iEnv, "WebAppFrameworkPollTimer", 0)
    , iPort(aPort)
    , iMaxLpSessions(aMaxSessions)
    , iServer(nullptr)
    , iDefaultApp(nullptr)
    , iStarted(false)
    , iCurrentAdapter(nullptr)
    , iMutex("webapp")
{
    std::vector<IFrameworkTab*> tabs;
    for (TUint i=0; i<iMaxLpSessions; i++) {
        tabs.push_back(new FrameworkTabFull(aEnv, i, aSendQueueSize, aSendTimeoutMs, aPollTimeoutMs));
    }
    iTabManager = new TabManager(tabs); // Takes ownership.

    Functor functor = MakeFunctor(*this, &WebAppFramework::CurrentAdapterChanged);
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    iAdapterListenerId = nifList.AddCurrentChangeListener(functor, "WebAppFramework", false);

    CurrentAdapterChanged();    // Force to set iCurrentAdapter, as not called at point of subscription.
    // no need to call AddSessions() - this happens inside CurrentAdapterChanged()
}

WebAppFramework::~WebAppFramework()
{
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    nifList.RemoveCurrentChangeListener(iAdapterListenerId);

    if (iCurrentAdapter != nullptr) {
        iCurrentAdapter->RemoveRef(kAdapterCookie);
    }

    // Terminate any blocking LongPoll() calls that server may have open and prevent further access/creation of tabs.
    iTabManager->Disable();

    // Don't allow any more web requests.
    delete iServer;

    // Delete TabManager before WebApps to allow it to free up any WebApp tabs that it may hold reference for.
    delete iTabManager;

    WebAppMap::iterator it;
    for (it=iWebApps.begin(); it!=iWebApps.end(); ++it) {
        // First elem is pointer to ref.
        delete it->second;
    }
}

void WebAppFramework::Start()
{
    AutoMutex amx(iMutex);
    ASSERT(iWebApps.size() > 0);
    ASSERT(!iStarted);
    iStarted = true;
    for (HttpSession& s : iSessions) {
        s.StartSession();
    }
}

TUint WebAppFramework::Port() const
{
    AutoMutex amx(iMutex);
    return iServer->Port();
}

TIpAddress WebAppFramework::Interface() const
{
    AutoMutex amx(iMutex);
    return iServer->Interface();
}

void WebAppFramework::SetDefaultApp(const Brx& aResourcePrefix)
{
    AutoMutex amx(iMutex);
    ASSERT(!iStarted);
    ASSERT(iDefaultApp == nullptr); // Don't want clashes in setting default app.
    WebAppMap::const_iterator it = iWebApps.find(&aResourcePrefix);
    if (it == iWebApps.cend()) {
        THROW(InvalidAppPrefix);
    }
    iDefaultApp = it->second;
}

void WebAppFramework::Add(IWebApp* aWebApp, FunctorPresentationUrl aFunctor)
{
    AutoMutex amx(iMutex);
    ASSERT(!iStarted);

    WebAppMap::const_iterator it = iWebApps.find(&aWebApp->ResourcePrefix());
    if (it != iWebApps.cend()) {
        ASSERTS(); // app with given resource prefix already exists
    }

    // Dynamic allocation here is acceptible as Start() hasn't been called and
    // class will persist for lifetime of WebAppFramework.
    WebAppInternal* webAppInternal = new WebAppInternal(aWebApp, aFunctor);
    iWebApps.insert(WebAppPair(&webAppInternal->ResourcePrefix(), webAppInternal));

    TIpAddress addr = iServer->Interface();
    if (addr == 0) {
        if (iCurrentAdapter != nullptr) {
            addr = iCurrentAdapter->Address();
        }
    }

    Bws<Uri::kMaxUriBytes> uri;
    uri.Append(":");
    Ascii::AppendDec(uri, iServer->Port());
    uri.Append("/");
    uri.Append(aWebApp->ResourcePrefix());
    uri.Append("/");
    //uri.Append(aWebApp->HomePage());
    uri.Append("index.html");   // FIXME - hard-coded info about webapp-specific resource!
                                // webapps are resource handlers (which may know how to redirect '/')
                                // so should probably be able to provide access to their own homepage
    webAppInternal->SetPresentationUrl(uri);
}

IWebApp& WebAppFramework::GetApp(const Brx& aResourcePrefix)
{
    AutoMutex amx(iMutex);
    ASSERT(iStarted);

    if (aResourcePrefix.Bytes() == 0 && iDefaultApp != nullptr) {
        return *iDefaultApp;
    }

    WebAppMap::const_iterator it = iWebApps.find(&aResourcePrefix);
    if (it == iWebApps.cend()) {
        THROW(InvalidAppPrefix);
    }

    return *(it->second);
}

IResourceHandler& WebAppFramework::CreateResourceHandler(const Brx& aResource)
{
    AutoMutex amx(iMutex);
    ASSERT(iStarted);
    Parser p(aResource);
    p.Next('/');    // skip leading '/'
    Brn prefix = p.Next('/');
    Brn tail = p.Next('?'); // Read up to query string (if any).

    if (prefix.Bytes() == 0) {
        if (iDefaultApp != nullptr) {
            return iDefaultApp->CreateResourceHandler(tail);
        }
        else {
            THROW(ResourceInvalid);
        }
    }

    WebAppMap::const_iterator it = iWebApps.find(&prefix);
    if (it == iWebApps.cend()) {
        // Didn't find an app with the given prefix.
        // Maybe it wasn't a prefix and was actually a URI tail for the default app.
        // Need to re-parse aResource in case there were multiple '/' in it.
        Parser p(aResource);
        p.Next('/');    // skip leading '/'
        Brn tail = p.Next('?'); // Read up to query string (if any).
        if (iDefaultApp != nullptr) {
            return iDefaultApp->CreateResourceHandler(tail);
        }
        THROW(ResourceInvalid);
    }

    IWebApp& app = *(it->second);
    return app.CreateResourceHandler(tail);
}

void WebAppFramework::AddSessions()
{
    // Add iMaxLpSessions+kSpareSessions to create spare session(s) for when
    // iMaxLpSessions are in use to allow processing of user input and
    // rejection of new connections.
    for (TUint i=0; i<iMaxLpSessions+kSpareSessions; i++) {
        Bws<kMaxSessionNameBytes> name(kSessionPrefix);
        Ascii::AppendDec(name, i+1);
        auto* session = new HttpSession(iEnv, *this, *iTabManager, *this);
        iSessions.push_back(*session);
        iServer->Add(name.PtrZ(), session);
    }
}

void WebAppFramework::CurrentAdapterChanged()
{
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    AutoNetworkAdapterRef ref(iEnv, "WebAppFramework::CurrentAdapterChanged");
    NetworkAdapter* current = ref.Adapter();

    // Get current subnet, otherwise choose first from a list
    if (current == nullptr) {
        std::vector<NetworkAdapter*>* subnetList = nifList.CreateSubnetList();
        if (subnetList->size() > 0) {
            current = (*subnetList)[0];
        }
        NetworkAdapterList::DestroySubnetList(subnetList);
    }

    AutoMutex amx(iMutex);

    if (iCurrentAdapter != current) {
        if (iCurrentAdapter != nullptr) {
            iCurrentAdapter->RemoveRef(kAdapterCookie);
        }
        iCurrentAdapter = current;
        if (iCurrentAdapter != nullptr) {
            iCurrentAdapter->AddRef(kAdapterCookie);
        }
    }

    // Don't rebind if we have nothing to rebind to - should this ever be the case?
    if (current != nullptr) {
        delete iServer;
        iSessions.clear();
        iServer = new SocketTcpServer(iEnv, kName, iPort, current->Address());
        AddSessions();
        if (iStarted) {
            for (HttpSession& s : iSessions) {
                s.StartSession();
            }
        }
    }
}


// HttpSession

HttpSession::HttpSession(Environment& aEnv, IWebAppManager& aAppManager, ITabManager& aTabManager, IResourceManager& aResourceManager)
    : iAppManager(aAppManager)
    , iTabManager(aTabManager)
    , iResourceManager(aResourceManager)
    , iResponseStarted(false)
    , iResponseEnded(false)
    , iResourceWriterHeadersOnly(false)
    , iStarted(false)
    , iLock("HTSL")
{
    iReadBuffer = new Srs<kMaxRequestBytes>(*this);
    iReaderUntilPreChunker = new ReaderUntilS<kMaxRequestBytes>(*iReadBuffer);
    iReaderRequest = new ReaderHttpRequest(aEnv, *iReaderUntilPreChunker);
    iReaderChunked = new ReaderHttpChunked(*iReaderUntilPreChunker);
    iReaderUntil = new ReaderUntilS<kMaxRequestBytes>(*iReaderChunked);
    iWriterBuffer = new Sws<kMaxResponseBytes>(*this);
    iWriterResponse = new WriterHttpResponse(*iWriterBuffer);

    iReaderRequest->AddMethod(Http::kMethodGet);
    iReaderRequest->AddMethod(Http::kMethodPost);
    iReaderRequest->AddMethod(Http::kMethodHead);

    iReaderRequest->AddHeader(iHeaderHost);
    iReaderRequest->AddHeader(iHeaderTransferEncoding);
    iReaderRequest->AddHeader(iHeaderConnection);
    iReaderRequest->AddHeader(iHeaderAcceptLanguage);
}

HttpSession::~HttpSession()
{
    delete iWriterResponse;
    delete iWriterBuffer;
    delete iReaderUntil;
    delete iReaderChunked;
    delete iReaderRequest;
    delete iReaderUntilPreChunker;
    delete iReadBuffer;
}

void HttpSession::StartSession()
{
    AutoMutex a(iLock);
    iStarted = true;
}

void HttpSession::Run()
{
    iErrorStatus = &HttpStatus::kOk;
    iReaderRequest->Flush();
    iResourceWriterHeadersOnly = false;
    // check headers
    try {
        try {
            iReaderRequest->Read(kReadTimeoutMs);
        }
        catch (HttpError&) {
            Error(HttpStatus::kBadRequest);
        }
        if (iReaderRequest->MethodNotAllowed()) {
            Error(HttpStatus::kMethodNotAllowed);
        }
        const Brx& method = iReaderRequest->Method();
        iReaderRequest->UnescapeUri();

        const Brx& uri = iReaderRequest->Uri();
        LOG(kHttp, "HttpSession::Run Method: %.*s, URI: %.*s\n", PBUF(method), PBUF(uri));

        iResponseStarted = false;
        iResponseEnded = false;

        iReaderChunked->SetChunked(iHeaderTransferEncoding.IsChunked());

        {
            /* TCP server is already active (and can't be temporarily deactivated),
            * even if !iStarted.
            * So, it is possible that, e.g., an existing web session, attempts to
            * access a web app before a new device with the same IP address is
            * fully initialised.
            * Report a 503 (Service Unavailable) in that case.
            */
            AutoMutex a(iLock);
            if (!iStarted) {
                THROW(WebAppServiceUnavailable);
            }
        }

        if (method == Http::kMethodGet) {
            Get();
        }
        else if (method == Http::kMethodHead) {
            iResourceWriterHeadersOnly = true;
            Get();
        }
        else if (method == Http::kMethodPost) {
            Post();
        }
    }
    catch (ResourceInvalid&) {
        if (iErrorStatus == &HttpStatus::kOk) {
            iErrorStatus = &HttpStatus::kNotFound;
        }
    }
    catch (HttpError&) {
        if (iErrorStatus == &HttpStatus::kOk) {
            iErrorStatus = &HttpStatus::kBadRequest;
        }
    }
    catch (ReaderError&) {
        if (iErrorStatus == &HttpStatus::kOk) {
            iErrorStatus = &HttpStatus::kBadRequest;
        }
    }
    catch (WebAppServiceUnavailable&) {
        iErrorStatus = &HttpStatus::kServiceUnavailable;
    }
    catch (WriterError&) {
    }
    try {
        if (!iResponseStarted) {
            if (iErrorStatus == &HttpStatus::kOk) {
                iErrorStatus = &HttpStatus::kNotFound;
            }
            iWriterResponse->WriteStatus(*iErrorStatus, Http::eHttp11);
            Http::WriteHeaderConnectionClose(*iWriterResponse);
            iWriterResponse->WriteFlush();
            // FIXME - serve up some kind of error page in case browser does not display its own?
        }
        else if (!iResponseEnded) {
            iWriterResponse->WriteFlush();
        }
    }
    catch (WriterError&) {}
}

void HttpSession::Error(const HttpStatus& aStatus)
{
    iErrorStatus = &aStatus;
    THROW(HttpError);
}

void HttpSession::Get()
{
    auto reqVersion = iReaderRequest->Version();
    if (reqVersion == Http::eHttp11) {
        if (!iHeaderHost.Received()) {
            Error(HttpStatus::kBadRequest);
        }
    }

    // Try access requested resource.
    const Brx& uri = iReaderRequest->Uri();
    IResourceHandler& resourceHandler = iResourceManager.CreateResourceHandler(uri);    // throws ResourceInvalid

    Brn mimeType = MimeUtils::MimeTypeFromUri(uri);
    LOG(kHttp, "HttpSession::Get URI: %.*s  Content-Type: %.*s\n", PBUF(uri), PBUF(mimeType));

    // Write response headers.
    iResponseStarted = true;
    iWriterResponse->WriteStatus(HttpStatus::kOk, reqVersion);
    IWriterAscii& writer = iWriterResponse->WriteHeaderField(Http::kHeaderContentType);
    writer.Write(mimeType);
    //writer.Write(Brn("; charset=\"utf-8\""));
    writer.WriteFlush();
    iWriterResponse->WriteHeader(Http::kHeaderConnection, Http::kConnectionClose);
    const TUint len = resourceHandler.Bytes();
    ASSERT(len > 0);    // Resource handler reporting incorrect byte count or corrupt resource.
    Http::WriteHeaderContentLength(*iWriterResponse, len);
    iWriterResponse->WriteFlush();

    // Write content.
    resourceHandler.Write(*iWriterBuffer);
    iWriterBuffer->WriteFlush(); // FIXME - move into iResourceWriter.Write()?
    resourceHandler.Destroy();
    iResponseEnded = true;
}

void HttpSession::Post()
{
    if (iReaderRequest->Version() == Http::eHttp11) {
        if (!iHeaderHost.Received()) {
            Error(HttpStatus::kBadRequest);
        }
    }

    const Brx& uri = iReaderRequest->Uri();
    Parser uriParser(uri);
    uriParser.Next('/');    // skip leading '/'
    Brn uriPrefix = uriParser.Next('/');
    Brn uriTail = uriParser.Next('?'); // Read up to query string (if any).

    // Try retrieve IWebApp using assumed prefix, in case it was actually the
    // URI tail and there is no prefix as the assumed app is the default app.
    try {
        (void)iAppManager.GetApp(uriPrefix);
    }
    catch (InvalidAppPrefix&) {
        // There was no app with the given uriPrefix, so maybe it's the default
        // app and the uriPrefix is actually uriTail.
        (void)iAppManager.GetApp(Brx::Empty());    // See if default app set.
        uriTail.Set(uriPrefix);         // Default app set, so assume uriPrefix is actually uriTail.
        uriPrefix.Set(Brx::Empty());    // Default app.
    }

    if (uriTail == Brn("lpcreate")) {
        try {
            IWebApp& app = iAppManager.GetApp(uriPrefix);
            TUint id = iTabManager.CreateTab(app, iHeaderAcceptLanguage.LanguageList());
            iResponseStarted = true;
            WriteLongPollHeaders();
            Bws<sizeof(id)> idBuf;
            Ascii::AppendDec(idBuf, id);
            iWriterBuffer->Write(Brn("lpcreate\r\n"));
            iWriterBuffer->Write(Brn("session-id: "));
            iWriterBuffer->Write(idBuf);
            iWriterBuffer->Write(Brn("\r\n"));
            iWriterBuffer->WriteFlush();
            iResponseEnded = true;
        }
        catch (InvalidAppPrefix&) {
            // FIXME - just respond with error instead of asserting?

            // Programmer error/misuse by client.
            // Long-polling can only be initiated from a page served up by this framework (which implies that it must have a valid app prefix!).
            ASSERTS();
        }
        catch (TabAllocatorFull&) { // FIXME - do something to distinguish between this (an IWebApp having all tabs allocated) vs TabManagerFull (the WebAppFramework has had its available tabs exhausted).
            Error(HttpStatus::kServiceUnavailable);
        }
        catch (TabManagerFull&) {
            Error(HttpStatus::kServiceUnavailable); // FIXME - if we return this state, Javascript code should keep attempting to poll
        }
        catch (InvalidTabId&) {
            ASSERTS();  // shouldn't happen - we've just created the tab
        }
    }
    else if (uriTail == Brn("lp")) {
        // Parse session-id and retrieve tab.
        Brn buf;
        // Don't rely on a content-length header (may be chunked encoding, or may be poor client implementation missing the header), as we know format of expected data.
        try {
            buf = Ascii::Trim(iReaderUntil->ReadUntil(Ascii::kLf));
        }
        catch (ReaderError&) {
            Error(HttpStatus::kBadRequest);
        }
        Parser p(buf);
        Brn sessionBuf = p.Next();
        if (sessionBuf == Brn("session-id:")) {
            sessionBuf = p.Next();
            TUint sessionId = 0;
            try {
                sessionId = Ascii::Uint(sessionBuf);
            }
            catch (AsciiError&) {
                // respond with bad request?
                Error(HttpStatus::kNotFound);
            }
            //Log::Print("lp session-id: %u\n", sessionId);
            try {
                iResponseStarted = true;
                WriteLongPollHeaders();
                iWriterBuffer->Write(Brn("lp\r\n"));
                iTabManager.LongPoll(sessionId, *iWriterBuffer);    // May write no data and can throw WriterError.
                iWriterBuffer->WriteFlush();
                iResponseEnded = true;
            }
            catch (InvalidTabId&) {
                Error(HttpStatus::kNotFound);
            }
            catch (WriterError&) {
                try {
                    iTabManager.Destroy(sessionId);
                }
                catch (InvalidTabId&) {
                    // Don't set error state to kNotFound.
                    // Just fall through to WriterError;
                    //Error(HttpStatus::kNotFound);
                }
                THROW(WriterError);
            }
        }
        else {
            // No session request made.
            Error(HttpStatus::kBadRequest);
        }
    }
    else if (uriTail == Brn("lpterminate")) {
        // Parse session-id and retrieve tab.
        Brn buf;
        try {
            buf = Ascii::Trim(iReaderUntil->ReadUntil(Ascii::kLf));
        }
        catch (ReaderError&) {
            Error(HttpStatus::kBadRequest);
        }
        Parser p(buf);
        Brn sessionBuf = p.Next();
        if (sessionBuf == Brn("session-id:")) {
            sessionBuf = p.Next();
            TUint sessionId = 0;
            try {
                sessionId = Ascii::Uint(sessionBuf);
            }
            catch (AsciiError&) {
                Error(HttpStatus::kNotFound);
            }
            //Log::Print("lpterminate session-id: %u\n", sessionId);
            try {
                iTabManager.Destroy(sessionId);
                iResponseStarted = true;
                WriteLongPollHeaders();
                iWriterBuffer->WriteFlush();
                iResponseEnded = true;
            }
            catch (InvalidTabId&) {
                Error(HttpStatus::kNotFound);
            }
        }
        else {
            // No session request made.
            Error(HttpStatus::kBadRequest);
        }
    }
    else if (uriTail == Brn("update")) {
        // Parse session-id and retrieve tab.
        Brn buf;
        try {
            buf = Ascii::Trim(iReaderUntil->ReadUntil(Ascii::kLf));
        }
        catch (ReaderError&) {
            Error(HttpStatus::kBadRequest);
        }
        Parser p(buf);
        Brn sessionLine = p.NextLine();
        Parser sessionParser(sessionLine);
        Brn sessionTag = sessionParser.Next();
        if (sessionTag == Brn("session-id:")) {
            Brn sessionIdBuf = sessionParser.Next();
            TUint sessionId = 0;
            try {
                sessionId = Ascii::Uint(sessionIdBuf);
            }
            catch (AsciiError&) {
                Error(HttpStatus::kNotFound);
            }

            Brn update;
            // Read in rest of update request. Should be a single ConfigVal per request (so should fit in read buffer).
            try {
                update = Ascii::Trim(iReaderUntil->ReadUntil(Ascii::kLf));
            }
            catch (ReaderError&) {
                Error(HttpStatus::kBadRequest);
            }

            try {
                iTabManager.Receive(sessionId, update);
                iResponseStarted = true;
                iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eHttp11);
                //IWriterAscii& writer = iWriterResponse->WriteHeaderField(Http::kHeaderContentType);
                // FIXME - need to provide content-type if adding this header
                //writer.WriteFlush();
                iWriterResponse->WriteHeader(Http::kHeaderConnection, Http::kConnectionClose);
                iWriterResponse->WriteFlush();
                iWriterBuffer->WriteFlush();
                iResponseEnded = true;
            }
            catch (InvalidTabId&) {
                Error(HttpStatus::kNotFound);
            }
        }
        else {
            // No session request made.
            Error(HttpStatus::kBadRequest);
        }
    }
    else {
        Error(HttpStatus::kNotFound);
    }
}

void HttpSession::WriteLongPollHeaders()
{
    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eHttp11);
    IWriterAscii& writer = iWriterResponse->WriteHeaderField(Http::kHeaderContentType);
    writer.Write(Brn("text/plain"));
    writer.Write(Brn("; charset=\"utf-8\""));
    writer.WriteFlush();
    iWriterResponse->WriteHeader(Http::kHeaderConnection, Http::kConnectionClose);
    iWriterResponse->WriteFlush();
}


// MimeUtils

const Brn MimeUtils::kExtCss("css");
const Brn MimeUtils::kExtJs("js");
const Brn MimeUtils::kExtXml("xml");
const Brn MimeUtils::kExtBmp("bmp");
const Brn MimeUtils::kExtGif("gif");
const Brn MimeUtils::kExtJpeg("jpeg");
const Brn MimeUtils::kExtPng("png");

Brn MimeUtils::MimeTypeFromUri(const Brx& aUri)
{ // static
    Parser p(aUri);
    Brn buf;
    while (!p.Finished()) {
        buf = p.Next('.');
    }

    if (Ascii::CaseInsensitiveEquals(buf, kExtCss)) {
        return Brn(kOhNetMimeTypeCss);
    }
    else if (Ascii::CaseInsensitiveEquals(buf, kExtJs)) {
        return Brn(kOhNetMimeTypeJs);
    }
    else if (Ascii::CaseInsensitiveEquals(buf, kExtXml)) {
        return Brn(kOhNetMimeTypeXml);
    }
    else if (Ascii::CaseInsensitiveEquals(buf, kExtBmp)) {
        return Brn(kOhNetMimeTypeBmp);
    }
    else if (Ascii::CaseInsensitiveEquals(buf, kExtGif)) {
        return Brn(kOhNetMimeTypeGif);
    }
    else if (Ascii::CaseInsensitiveEquals(buf, kExtJpeg)) {
        return Brn(kOhNetMimeTypeJpeg);
    }
    else if (Ascii::CaseInsensitiveEquals(buf, kExtPng)) {
        return Brn(kOhNetMimeTypePng);
    }
    // default to "text/html"
    return Brn(kOhNetMimeTypeHtml);
}
