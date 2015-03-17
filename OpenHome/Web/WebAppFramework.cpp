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

#include <limits>

using namespace OpenHome;
using namespace OpenHome::Configuration;
using namespace OpenHome::Web;


// FileResourceHandler

FileResourceHandler::FileResourceHandler(const OpenHome::Brx& aRootDir)
    : iRootDir(aRootDir)
    , iFile(NULL)
{
}

TBool FileResourceHandler::Allocated()
{
    return (iFile != NULL);
}

void FileResourceHandler::SetResource(const Brx& aUri)
{
    ASSERT(iFile == NULL);
    Bwh filename(iRootDir.Bytes()+aUri.Bytes()+1);
    filename.Replace(iRootDir);
    filename.Append(aUri);

    try {
        // FIXME - dynamic allocation!
        iFile = new FileAnsii(filename.PtrZ(), eFileReadOnly); // asserts if a file is already open
    }
    catch (FileOpenError&) {
        LOG(kHttp, "FileResourceHandler::SetResource failed to open resource: ");
        LOG(kHttp, filename);
        LOG(kHttp, "\n");
        THROW(ResourceInvalid);
    }

    SetMimeType(aUri);
}

const Brx& FileResourceHandler::MimeType()
{
    ASSERT(iFile != NULL);
    ASSERT(iMimeType.Bytes() != 0);
    return iMimeType;
}

void FileResourceHandler::Write(IWriter& aWriter, TUint aOffset, TUint aBytes)
{
    ASSERT(iFile != NULL);
    if (aOffset != 0) {
        // Seek to desired pos.
        try {
            iFile->Seek(aOffset, eSeekFromStart);
        }
        catch (FileSeekError) {
            THROW(WriterError);
        }
    }

    // Bytes to be written.
    TUint bytes = iFile->Bytes();
    if (aBytes != bytes && aBytes != 0) {   // if aBytes == 0 write whole file
        bytes = aBytes;
    }

    // Write.
    Bws<1024> buf;
    try {
        while (bytes > 0) {
            iFile->Read(buf);
            aWriter.Write(buf);
            bytes -= buf.Bytes();
            buf.SetBytes(0);
        }
    }
    catch (FileReadError&) {
        // FIXME - this behaviour seems undesirable
        // iFile->Read() should EITHER do what we ask, OR throw an exception
        // It shouldn't do both (either partially or fully)!
        if (buf.Bytes() > 0) {
            aWriter.Write(buf);
        }
        THROW(WriterError);
    }
}

void FileResourceHandler::Destroy()
{
    ASSERT(iFile != NULL);
    delete iFile;
    iFile = NULL;
    iMimeType.SetBytes(0);
}

void FileResourceHandler::SetMimeType(const Brx& aUri)
{
    // Infer mime type from file extension.
    Parser p(aUri);
    Brn buf;
    while (!p.Finished()) {
        buf = p.Next('.');
    }

    if (Ascii::CaseInsensitiveEquals(buf, Brn("css"))) {
        iMimeType.Replace(kOhNetMimeTypeCss);
    }
    else if (Ascii::CaseInsensitiveEquals(buf, Brn("js"))) {
        iMimeType.Replace(kOhNetMimeTypeJs);
    }
    else if (Ascii::CaseInsensitiveEquals(buf, Brn("xml"))) {
        iMimeType.Replace(kOhNetMimeTypeXml);
    }
    else if (Ascii::CaseInsensitiveEquals(buf, Brn("bmp"))) {
        iMimeType.Replace(kOhNetMimeTypeBmp);
    }
    else if (Ascii::CaseInsensitiveEquals(buf, Brn("gif"))) {
        iMimeType.Replace(kOhNetMimeTypeGif);
    }
    else if (Ascii::CaseInsensitiveEquals(buf, Brn("jpeg"))) {
        iMimeType.Replace(kOhNetMimeTypeJpeg);
    }
    else if (Ascii::CaseInsensitiveEquals(buf, Brn("png"))) {
        iMimeType.Replace(kOhNetMimeTypePng);
    }
    else {  // default to "text/html"
        iMimeType.Replace(kOhNetMimeTypeHtml);
    }
}


// FrameworkTabHandler

FrameworkTabHandler::FrameworkTabHandler(IFrameworkSemaphore& aSemaphore, TUint aSendQueueSize, TUint aSendTimeoutMs)
    : iSendTimeoutMs(aSendTimeoutMs)
    , iFifo(aSendQueueSize)
    , iLock("FTHL")
    , iSem(aSemaphore)
{
}

FrameworkTabHandler::~FrameworkTabHandler()
{
    Clear();
}

void FrameworkTabHandler::BlockingSend(IWriter& aWriter)
{
    try {
        iSem.Wait(iSendTimeoutMs);

        AutoMutex a(iLock);
        // If iSem signalled, msg is in iFifo.
        aWriter.Write(Brn("["));
        while (iFifo.SlotsUsed() > 0) {
            ITabMessage* msg = iFifo.Read();
            msg->Send(aWriter);
            // All but last msg should be followed by "," in a JSON array.
            if (iFifo.SlotsUsed() > 0) {
                aWriter.Write(Brn(","));
            }
            msg->Destroy();
        }
        aWriter.Write(Brn("]"));
        iSem.Clear();   // FIXME - clear this here, or should/can we pick up each signal each time round loop?
    }
    catch (Timeout&) {
        THROW(Timeout); // FIXME - bother rethrowing this, or just don't tell upper layer that we didn't send anything?
    }
}

void FrameworkTabHandler::Clear()
{
    AutoMutex a(iLock);
    while (iFifo.SlotsUsed() > 0) {
        ITabMessage* msg = iFifo.Read();
        msg->Destroy();
    }
    iSem.Clear();
}

void FrameworkTabHandler::Send(ITabMessage& aMessage)
{
    AutoMutex a(iLock);
    //ASSERT(iFifo.SlotsUsed() < iFifo.Slots());
    iFifo.Write(&aMessage); // FIXME - should this block or not?
    iSem.Signal();
}


// FrameworkTimer

FrameworkTimer::FrameworkTimer(Environment& aEnv)
    : iHandler(NULL)
    , iLock("FRTL")
    , iStartCount(0)
    , iCancelCount(0)
    , iCompleteCount(0)
{
    iTimer = new Timer(aEnv, MakeFunctor(*this, &FrameworkTimer::Complete), "WebUiFrameworkTimer");
}

FrameworkTimer::~FrameworkTimer()
{
    AutoMutex a(iLock);
    iTimer->Cancel();
    delete iTimer;
}

void FrameworkTimer::Start(TUint aDurationMs, IFrameworkTimerHandler& aHandler)
{
    AutoMutex a(iLock);
    iStartCount++;
    ASSERT(iHandler == NULL);
    iHandler = &aHandler;
    iTimer->FireIn(aDurationMs);
}

void FrameworkTimer::Cancel()
{
    AutoMutex a(iLock);
    iCancelCount++;
    ASSERT(iHandler != NULL);
    iTimer->Cancel();
    iHandler = NULL;
}

void FrameworkTimer::Complete()
{
    AutoMutex a(iLock);
    iCompleteCount++;
    ASSERT(iHandler != NULL);
    iHandler->Complete();
    iHandler = NULL;
}


// PollTimer

PollTimer::PollTimer(IFrameworkTimer& aTimer) // FIXME - each PollTimer should get a unique IFrameworkTimer - is this what's happening?
    : iTimer(aTimer)
    , iHandler(NULL)
    , iLock("TTDL")
{
}

void PollTimer::StartPollWait(TUint aTimeoutMs, IPollTimerHandler& aHandler)
{
    AutoMutex a(iLock);
    ASSERT(iHandler == NULL);
    iHandler = &aHandler;
    iTimer.Start(aTimeoutMs, *this);
}

void PollTimer::CancelPollWait()
{
    AutoMutex a(iLock);
    ASSERT(iHandler != NULL);
    iTimer.Cancel();
    iHandler = NULL;
}

void PollTimer::Complete()
{
    AutoMutex a(iLock);
    ASSERT(iHandler != NULL);
    iHandler->PollWaitComplete();
    iHandler = NULL;
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

void FrameworkSemaphore::Wait(TUint aTimeoutMs)
{
    iSem.Wait(aTimeoutMs);
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

FrameworkTab::FrameworkTab(TUint aId, ITabDestroyHandler& aDestroyHandler, IFrameworkTimer& aTimer, TUint aSendQueueSize, TUint aSendTimeoutMs, TUint aPollTimeoutMs)
    : iId(aId)
    , iPollTimeoutMs(aPollTimeoutMs)
    , iDestroyHandler(aDestroyHandler)
    , iTabSem("FRTS", 0)
    , iHandler(iTabSem, aSendQueueSize, aSendTimeoutMs)
    , iPollTimer(aTimer)
    , iTab(NULL)
    , iRefCount(0)
    , iDestructionPending(false)
    , iLock("FRTL")
{
}

FrameworkTab::~FrameworkTab()
{
    AutoMutex a(iLock);
    // All clients must have called RemoveRef() before this object is destructed.
    ASSERT(iRefCount == 0);
    //iPollTimer.CancelPollWait(); - called by Destroy()
}

TBool FrameworkTab::Allocated() const
{
    AutoMutex a(iLock);
    TBool allocated = (iTab != NULL);
    return allocated;
}

TBool FrameworkTab::Available() const
{
    AutoMutex a(iLock);
    TBool available = (!iDestructionPending && iTab != NULL);
    return available;
}

void FrameworkTab::Set(ITab& aTab, std::vector<const Brx*>& aLanguages)
{
    AutoMutex a(iLock);
    ASSERT(iTab == NULL);
    ASSERT(iRefCount == 0);
    ASSERT(!iDestructionPending);
    ASSERT(iLanguages.size() == 0);
    iLanguages = aLanguages;    // takes ownership of pointers
    iTab = &aTab;
    iRefCount++;    // reference now held by caller of this
}

void FrameworkTab::BlockingSend(IWriter& aWriter)
{
    {
        AutoMutex a(iLock);
        ASSERT(iTab != NULL);
        ASSERT(!iDestructionPending);
    }
    iHandler.BlockingSend(aWriter);
}

void FrameworkTab::StartPollWait()
{
    AutoMutex a(iLock);
    ASSERT(iTab != NULL);
    iPollTimer.StartPollWait(iPollTimeoutMs, *this);
}

void FrameworkTab::CancelPollWait()
{
    AutoMutex a(iLock);
    ASSERT(iTab != NULL);
    iPollTimer.CancelPollWait();
}

void FrameworkTab::Receive(const OpenHome::Brx& aMessage)
{
    AutoMutex a(iLock);
    ASSERT(iTab != NULL);
    ASSERT(!iDestructionPending);
    iTab->Receive(aMessage);
}

void FrameworkTab::Destroy()
{
    // Removes ref held by caller and passes on call to IDestroyHandler.
    AutoMutex a(iLock);
    ASSERT(iTab != NULL && !iDestructionPending);
    //iPollTimer.CancelPollWait(); // FIXME - attempted recursive lock on mutex
    iDestructionPending = true;
    RemoveRefUnlocked();
    iDestroyHandler.Destroy(*this);
    for (TUint i=0; i<iLanguages.size(); i++) {
        delete iLanguages[i];
    }
    iLanguages.clear();
}

void FrameworkTab::Send(ITabMessage& aMessage)
{
    iHandler.Send(aMessage);
}

void FrameworkTab::PollWaitComplete()
{
    // Timer callback method.
    AddRef();   // all calls to Destroy() must be made by caller with ref held
    Destroy();
}

void FrameworkTab::AddRef()
{
    AutoMutex a(iLock);
    AddRefUnlocked();
}

void FrameworkTab::RemoveRef()
{
    AutoMutex a(iLock);
    RemoveRefUnlocked();
}

void FrameworkTab::AddRefUnlocked()
{
    ASSERT(iTab != NULL);
    ASSERT(!iDestructionPending);
    ASSERT(iRefCount < std::numeric_limits<TUint>::max());
    iRefCount++;
}

void FrameworkTab::RemoveRefUnlocked()
{
    ASSERT(iTab != NULL);
    ASSERT(iRefCount > 0);
    iRefCount--;

    if (iRefCount == 0) {
        iTab->Destroy();
        iTab = NULL;
        iHandler.Clear();
        iDestructionPending = false;
    }
}


// TabManager

TabManager::TabManager(Environment& aEnv, TUint aMaxTabs, TUint aSendQueueSize, TUint aSendTimeoutMs, TUint aPollTimeoutMs)
    : iMaxTabs(aMaxTabs)
    , iLock("TBML")
{
    for (TUint i=0; i<iMaxTabs; i++) {
        iTimers.push_back(new FrameworkTimer(aEnv));
        iTabs.push_back(new FrameworkTab(i, *this, *iTimers[i], aSendQueueSize, aSendTimeoutMs, aPollTimeoutMs));
    }
}

TabManager::~TabManager()
{
    // Expect all clients to have released their references to tabs by this
    // point. So, any tabs still allocated can have RemoveRef() called, as this
    // should be only object holding a reference.
    AutoMutex a(iLock);
    for (TUint i=0; i<iMaxTabs; i++) {
        FrameworkTab* tab = iTabs[i];
        if (tab->Allocated()) {
            tab->RemoveRefUnlocked();
        }
        delete tab;
        delete iTimers[i];
    }
}

TUint TabManager::CreateTab(IWebApp& aApp, std::vector<const Brx*>& aLanguageList)
{
    AutoMutex a(iLock);
    for (TUint i=0; i<iTabs.size(); i++) {
        if (!iTabs[i]->Allocated()) {
            LOG(kHttp, "TabManager::CreateTab creating tab with ID: %u for WebApp: ", i);
            LOG(kHttp, aApp.ResourcePrefix());
            LOG(kHttp, "\n");
            ITab& tab = aApp.Create(*iTabs[i], aLanguageList);
            iTabs[i]->Set(tab, aLanguageList);  // Takes ownership of (buffers in) language list.
            TUint clientId = TabManagerIdToClientId(i);
            return clientId;
        }
    }
    LOG(kHttp, "TabManager::CreateTab tab manager full\n");
    THROW(TabManagerFull);  // shouldn't reach here unless there isn't enough space.
}

IFrameworkTab& TabManager::GetTab(TUint aTabId)
{
    if (aTabId == 0) { // 0 is invalid Tab ID
        THROW(InvalidTabId);
    }

    TUint id = ClientIdToTabManagerId(aTabId);
    AutoMutex a(iLock);
    if (id < iTabs.size() && iTabs[id]->Available()) {
        FrameworkTab& tab = *iTabs[id];
        tab.AddRef();
        return tab;
    }
    THROW(InvalidTabId);
}

void TabManager::Destroy(IRefCountableUnlocked& aRefCountable)
{
    AutoMutex a(iLock);
    aRefCountable.RemoveRefUnlocked();
}

TUint TabManager::TabManagerIdToClientId(TUint aId)
{
    ASSERT(aId < std::numeric_limits<TUint>::max());
    return aId+1;
}

TUint TabManager::ClientIdToTabManagerId(TUint aId)
{
    ASSERT(aId != 0);
    return aId-1;
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

ITab& WebAppInternal::Create(ITabHandler& aHandler, std::vector<const Brx*>& aLanguageList)
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

WebAppFramework::WebAppFramework(Environment& aEnv, TIpAddress aInterface, TUint aPort, TUint aMaxSessions, TUint aSendQueueSize, TUint aSendTimeoutMs, TUint aPollTimeoutMs)
    : iEnv(aEnv)
    , iPollTimer(iEnv)
    , iPort(aPort)
    , iMaxLpSessions(aMaxSessions)
    , iTabManager(iEnv, iMaxLpSessions, aSendQueueSize, aSendTimeoutMs, aPollTimeoutMs)
    , iStarted(false)
    , iCurrentAdapter(NULL)
{
    iServer = new SocketTcpServer(iEnv, kName, iPort, aInterface);

    Functor functor = MakeFunctor(*this, &WebAppFramework::CurrentAdapterChanged);
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    iAdapterListenerId = nifList.AddCurrentChangeListener(functor, false);

    CurrentAdapterChanged();    // Force to set iCurrentAdapter, as not called at point of subscription.

    AddSessions();
}

WebAppFramework::~WebAppFramework()
{
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    nifList.RemoveCurrentChangeListener(iAdapterListenerId);

    if (iCurrentAdapter != NULL) {
        iCurrentAdapter->RemoveRef(kAdapterCookie);
    }

    WebAppMap::iterator it;
    for (it=iWebApps.begin(); it!=iWebApps.end(); ++it) {
        // First elem is pointer to ref.
        delete it->second;
    }

    delete iServer;
}

void WebAppFramework::Start()
{
    // FIXME - lock here?
    ASSERT(iWebApps.size() > 0);
    iStarted = true;
}

TUint WebAppFramework::Port() const
{
    return iServer->Port();
}

TIpAddress WebAppFramework::Interface() const
{
    return iServer->Interface();
}

void WebAppFramework::Add(IWebApp* aWebApp, FunctorPresentationUrl aFunctor)
{
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
        if (iCurrentAdapter != NULL) {
            addr = iCurrentAdapter->Address();
        }
    }
    Endpoint ep(iServer->Port(), addr);

    Bws<Uri::kMaxUriBytes> uri("http://");
    ep.AppendEndpoint(uri);
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
    ASSERT(iStarted);
    WebAppMap::const_iterator it = iWebApps.find(&aResourcePrefix);
    if (it == iWebApps.cend()) {
        THROW(InvalidAppPrefix);
    }

    return *(it->second);
}

IResourceHandler& WebAppFramework::CreateResourceHandler(const Brx& aResource)
{
    ASSERT(iStarted);
    Parser p(aResource);
    p.Next('/');    // skip leading '/'
    Brn prefix = p.Next('/');
    Brn tail = p.Next('/');

    WebAppMap::const_iterator it = iWebApps.find(&prefix);
    if (it == iWebApps.cend()) {
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
        Bwh name(kSessionPrefix.Bytes()+2); // space for numerical suffix + '\0'
        name.Replace(kSessionPrefix);
        Ascii::AppendDec(name, i+1);
        iServer->Add(name.PtrZ(), new HttpSession(iEnv, *this, iTabManager, *this));
    }
}

void WebAppFramework::CurrentAdapterChanged()
{
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    AutoNetworkAdapterRef ref(iEnv, "WebAppFramework::CurrentAdapterChanged");
    NetworkAdapter* current = ref.Adapter();

    // Get current subnet, otherwise choose first from a list
    if (current == NULL) {
        std::vector<NetworkAdapter*>* subnetList = nifList.CreateSubnetList();
        if (subnetList->size() > 0) {
            current = (*subnetList)[0];
        }
        NetworkAdapterList::DestroySubnetList(subnetList);
    }
    if (iCurrentAdapter != current) {
        if (iCurrentAdapter != NULL) {
            iCurrentAdapter->RemoveRef(kAdapterCookie);
        }
        iCurrentAdapter = current;
        if (iCurrentAdapter != NULL) {
            iCurrentAdapter->AddRef(kAdapterCookie);
        }
    }

    // Don't rebind if we have nothing to rebind to - should this ever be the case?
    //if (current != NULL) {
        delete iServer;
        // FIXME - bind only to current adapter or all adapters?
        iServer = new SocketTcpServer(iEnv, kName, iPort, current->Address());
        AddSessions();
    //}
}


// HttpSession

HttpSession::HttpSession(Environment& aEnv, IWebAppManager& aAppManager, ITabManager& aTabManager, IResourceManager& aResourceManager)
    : iAppManager(aAppManager)
    , iTabManager(aTabManager)
    , iResourceManager(aResourceManager)
    , iResponseStarted(false)
    , iResponseEnded(false)
    , iResourceWriterHeadersOnly(false)
    , iUpdateCount(0)
{
    iReadBuffer = new Srs<kMaxRequestBytes>(*this);
    iReaderRequest = new ReaderHttpRequest(aEnv, *iReadBuffer);
    iWriterChunked = new WriterHttpChunked(*this);
    iWriterBuffer = new Sws<kMaxResponseBytes>(*iWriterChunked);
    iWriterResponse = new WriterHttpResponse(*iWriterBuffer);

    iReaderRequest->AddMethod(Http::kMethodGet);
    iReaderRequest->AddMethod(Http::kMethodPost);
    iReaderRequest->AddMethod(Http::kMethodHead);

    iReaderRequest->AddHeader(iHeaderHost);
    iReaderRequest->AddHeader(iHeaderContentLength);
    iReaderRequest->AddHeader(iHeaderTransferEncoding);
    iReaderRequest->AddHeader(iHeaderConnection);
    iReaderRequest->AddHeader(iHeaderAcceptLanguage);
}

HttpSession::~HttpSession()
{
    // Run() has exited before this is called.
}

void HttpSession::Run()
{
    iErrorStatus = &HttpStatus::kOk;
    iReaderRequest->Flush();
    iWriterChunked->SetChunked(false);
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

        LOG(kHttp, "HttpSession::Run Method: ");
        LOG(kHttp, method);
        LOG(kHttp, ", URI: ");
        LOG(kHttp, iReaderRequest->Uri());
        LOG(kHttp, "\n");

        iResponseStarted = false;
        iResponseEnded = false;
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
    if (iReaderRequest->Version() == Http::eHttp11) {
        if (!iHeaderHost.Received()) {
            Error(HttpStatus::kBadRequest);
        }
    }

    // Try access requested resource.
    const Brx& uri = iReaderRequest->Uri();
    IResourceHandler& resourceHandler = iResourceManager.CreateResourceHandler(uri);    // throws ResourceInvalid

    LOG(kHttp, "HttpSession::Get URI: ");
    LOG(kHttp, uri);
    LOG(kHttp, " Content-Type: ");
    LOG(kHttp, resourceHandler.MimeType());
    LOG(kHttp, "\n");

    // Write response headers.
    iResponseStarted = true;
    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eHttp11);
    IWriterAscii& writer = iWriterResponse->WriteHeaderField(Http::kHeaderContentType);
    writer.Write(resourceHandler.MimeType());
    //writer.Write(Brn("; charset=\"utf-8\""));
    writer.WriteFlush();
    iWriterResponse->WriteHeader(Http::kHeaderConnection, Http::kConnectionClose);
    //WriteServerHeader(*iWriterResponse);
    //if (iReaderRequest->Version() == Http::eHttp11) {
    //    iWriterResponse->WriteHeader(Http::kHeaderTransferEncoding, Http::kTransferEncodingChunked);
    //}
    iWriterResponse->WriteFlush();

    // Write content.
    resourceHandler.Write(*iWriterBuffer, 0, 0);
    iWriterBuffer->WriteFlush(); // FIXME - move into iResourceWriter.Write()?
    resourceHandler.Destroy();
    iResponseEnded = true;

    if (iResponseStarted) {
        ASSERT(iResponseEnded);
    }
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
    Brn uriTail = uriParser.NextToEnd();

    if (uriTail == Brn("lpcreate")) {
        try {
            IWebApp& app = iAppManager.GetApp(uriPrefix); // FIXME - pass full uri to this instead of prefix?
            std::vector<char*>& languageList = iHeaderAcceptLanguage.LanguageList();
            std::vector<const Brx*> languageListHeapBufs;
            for (TUint i=0; i<languageList.size(); i++) {
                languageListHeapBufs.push_back(new Brh(languageList[i]));
            }
            TUint id = iTabManager.CreateTab(app, languageListHeapBufs);
            IFrameworkTab& tab = iTabManager.GetTab(id);
            iResponseStarted = true;
            WriteLongPollHeaders();
            Bws<sizeof(id)> idBuf;
            Ascii::AppendDec(idBuf, id);
            iWriterBuffer->Write(Brn("session-id: "));
            iWriterBuffer->Write(idBuf);
            iWriterBuffer->WriteFlush();
            iResponseEnded = true;
            tab.StartPollWait();
            tab.RemoveRef();
        }
        catch (InvalidAppPrefix&) {
            ASSERTS(); // programmer error/misuse by client
        }
        catch (TabManagerFull&) {
            Error(HttpStatus::kServiceUnavailable); // FIXME - if we return this state, Javascript code should keep attempting to poll
        }
        catch (InvalidTabId&) {
            ASSERTS();  // shouldn't happen - we've just created the tab
        }
    }
    else if (uriTail == Brn("lp")) {
        // parse session-id and retrieve tab
        if (iHeaderContentLength.ContentLength() != 0) {
            Brn buf = iReadBuffer->Read(iHeaderContentLength.ContentLength());
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
                Log::Print("lp session-id: %u\n", sessionId);
                IFrameworkTab* tab = NULL;
                try {
                    tab = &iTabManager.GetTab(sessionId);
                    tab->CancelPollWait(); // what if polling timer has fired
                    // between GetTab() and CancelPollWait()?
                    // - reference to tab is still valid
                    // - CancelPollWait() should do nothing.

                    // If we have data, write it immediately.
                    // If we have no data, wait on semaphore, and if some arrives, write it immediately.
                    // If we have no data and still none after semaphore, write headers and no data.
                    // BlockingSend() covers all the above requirements for us.

                    iResponseStarted = true;
                    WriteLongPollHeaders();
                    // FIXME - bother throwing Timeout if there is nothing useful to do with it?
                    try {
                        tab->BlockingSend(*iWriterBuffer);  // may write no data
                    }
                    catch (Timeout&)
                    {
                        // No data was sent. Do nothing.
                    }
                    iWriterBuffer->WriteFlush();
                    iResponseEnded = true;
                    tab->StartPollWait();
                    tab->RemoveRef();
                }
                catch (InvalidTabId&) {
                    Error(HttpStatus::kNotFound);
                }
                catch(WriterError&) {
                    tab->Destroy();
                    THROW(WriterError);
                }
            }
        }
    }
    else if (uriTail == Brn("lpterminate")) {
        // parse session-id and retrieve tab
        if (iHeaderContentLength.ContentLength() != 0) {
            Brn buf = iReadBuffer->Read(iHeaderContentLength.ContentLength());
            Parser p(buf);
            Brn sessionBuf = p.Next();
            if (sessionBuf == Brn("session-id:")) { // if this isn't found, respond with badrequest?
                sessionBuf = p.Next();
                TUint sessionId = 0;
                try {
                    sessionId = Ascii::Uint(sessionBuf);
                }
                catch (AsciiError&) {
                    Error(HttpStatus::kNotFound);
                }
                Log::Print("lpterminate session-id: %u\n", sessionId);
                try {
                    IFrameworkTab& tab = iTabManager.GetTab(sessionId);
                    tab.CancelPollWait();
                    tab.Destroy();
                    iResponseStarted = true;
                    WriteLongPollHeaders();
                    iWriterBuffer->WriteFlush();
                    iResponseEnded = true;
                }
                catch (InvalidTabId&) {
                    Error(HttpStatus::kNotFound);
                }
            }
        }
    }
    else if (uriTail == Brn("update")) {
        Log::Print("\nupdate request\n");
        // parse session-id and retrieve tab
        if (iHeaderContentLength.ContentLength() != 0) {
            Brn buf = iReadBuffer->Read(iHeaderContentLength.ContentLength());
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
                Log::Print("update session-id: %u\n", sessionId);
                try {
                    Brn input = p.NextToEnd();
                    // FIXME - what if session-id = 0?
                    // i.e., update has been sent before long polling has been set up
                    IFrameworkTab& tab = iTabManager.GetTab(sessionId);
                    tab.Receive(input);
                    tab.RemoveRef();
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
                // Could not parse sessionBuf - bad request
            }
        }
    }
    else if (uriTail == Brn("probe")) {
        ASSERTS(); // FIXME - implement behaviour
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
