#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/MimeTypes.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Shell.h>
#include <OpenHome/Private/InfoProvider.h>
#include <OpenHome/Private/ShellCommandDebug.h>

#ifdef PLATFORM_MACOSX_GNU
# include <sys/time.h>
#else
# include <time.h>
#endif // PLATFORM_MACOSX_GNU
#include <stdlib.h>

namespace OpenHome {

class MListener
{
public:
    MListener(Environment& aStack, TIpAddress aInterface);
    ~MListener();
    Net::SsdpListenerMulticast& Listener();
    TIpAddress Interface() const;
    void AddRef();
    TBool RemoveRef();
private:
    Net::SsdpListenerMulticast iListener;
    TInt iRefCount;
};

} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Net;

// Strings declared in MimeTypes.h

const char kOhNetMimeTypeCss[]  = "text/css";
const char kOhNetMimeTypeHtml[] = "text/html";
const char kOhNetMimeTypeJs[]   = "application/javascript";
const char kOhNetMimeTypeXml[]  = "text/xml";
const char kOhNetMimeTypeBmp[]  = "image/bmp";
const char kOhNetMimeTypeGif[]  = "image/gif";
const char kOhNetMimeTypeJpeg[] = "image/jpeg";
const char kOhNetMimeTypePng[]  = "image/png";


// Environment

static const TUint kVersionMajor = 1;
static const TUint kVersionMinor = 0;

Environment::Environment(FunctorMsg& aLogOutput)
    : iOsContext(NULL)
    , iInitParams(NULL)
    , iTimerManager(NULL)
    , iNetworkAdapterList(NULL)
    , iShell(NULL)
    , iInfoAggregator(NULL)
    , iShellCommandDebug(NULL)
    , iSequenceNumber(0)
    , iCpStack(NULL)
    , iDvStack(NULL)
{
    Construct(aLogOutput);
}

Environment* Environment::Create(FunctorMsg& aLogOutput)
{
    return new Environment(aLogOutput);
}

Environment::Environment(InitialisationParams* aInitParams)
    : iOsContext(NULL)
    , iInitParams(aInitParams)
    , iNetworkAdapterList(NULL)
    , iShell(NULL)
    , iInfoAggregator(NULL)
    , iShellCommandDebug(NULL)
    , iSequenceNumber(0)
    , iCpStack(NULL)
    , iDvStack(NULL)
{
    Construct(aInitParams->LogOutput());
#ifdef PLATFORM_MACOSX_GNU
    /* Non-portable way of setting a better random seed than time(NULL)
       This is needed on Mac as CI for x86 and x64 tests use the same host
       with the builds appearing to run in perfect sync, leaving two
       versions of this test that choose identical udns for device stack tests. */
    struct timeval tv;
    (void)gettimeofday(&tv, NULL);
    SetRandomSeed((TUint)tv.tv_usec);
#else
    SetRandomSeed((TUint)(time(NULL) % UINT32_MAX));
#endif // PLATFORM_MACOSX_GNU
    iTimerManager = new OpenHome::TimerManager(*this, iInitParams->TimerManagerPriority());
    iNetworkAdapterList = new OpenHome::NetworkAdapterList(*this, 0);
    Functor& subnetListChangeListener = iInitParams->SubnetListChangedListener();
    if (subnetListChangeListener) {
        iNetworkAdapterList->AddSubnetListChangeListener(subnetListChangeListener, "Env", false);
    }
    FunctorNetworkAdapter &subnetAddedListener = iInitParams->SubnetAddedListener();
    if (subnetAddedListener) {
        iNetworkAdapterList->AddSubnetAddedListener(subnetAddedListener, "Env");
    }
    FunctorNetworkAdapter &subnetRemovedListener = iInitParams->SubnetRemovedListener();
    if (subnetRemovedListener) {
        iNetworkAdapterList->AddSubnetRemovedListener(subnetRemovedListener, "Env");
    }
    FunctorNetworkAdapter &networkAdapterChangeListener = iInitParams->NetworkAdapterChangedListener();
    if (networkAdapterChangeListener) {
        iNetworkAdapterList->AddNetworkAdapterChangeListener(networkAdapterChangeListener, "Env");
    }

    CreateShell();
}

Environment* Environment::Create(InitialisationParams* aInitParams)
{
    return new Environment(aInitParams);
}

void Environment::Construct(FunctorMsg& aLogOutput)
{
    gEnv = this;
    iOsContext = OpenHome::Os::Create();
    if (iOsContext == NULL) {
        throw std::bad_alloc();
    }
    iLogger = new Log(aLogOutput);
    TUint hostMin, hostMax;
    Os::ThreadGetPriorityRange(iOsContext, hostMin, hostMax);
    iThreadPriorityArbitrator = new ThreadPriorityArbitrator(hostMin, hostMax);
    iPublicLock = new OpenHome::Mutex("GMUT");
    iPrivateLock = new OpenHome::Mutex("ENVP");
    iSuspendResumeObserverLock = new OpenHome::Mutex("ENVR");
}

Environment::~Environment()
{
    iPublicLock->Wait();
    iPublicLock->Signal();
    delete iCpStack;
    delete iDvStack;
    delete iShellCommandDebug;
    delete iInfoAggregator;
    delete iShell;
    delete iNetworkAdapterList;
    if (iObjectMap.size() != 0) {
        Log::Print("ERROR: destroying stack before some owned objects\n");
        Log::Print("...leaked objects are\n");
        ListObjects();
        ASSERTS();
    }
    delete iTimerManager;
    delete iInitParams;
    delete iPublicLock;
    delete iPrivateLock;
    ASSERT(iSuspendObservers.size() == 0);
    ASSERT(iResumeObservers.size() == 0);
    delete iSuspendResumeObserverLock;
    delete iThreadPriorityArbitrator;
    delete iLogger;
    Os::Destroy(iOsContext);
}

void Environment::GetVersion(TUint& aMajor, TUint& aMinor)
{
    aMajor = kVersionMajor;
    aMinor = kVersionMinor;
}

OpenHome::TimerManager& Environment::TimerManager()
{
    return *iTimerManager;
}

OpenHome::Mutex& Environment::Mutex()
{
    return *iPublicLock;
}

OsContext* Environment::OsCtx()
{
    return iOsContext;
}

Log& Environment::Logger()
{
    return *iLogger;
}

NetworkAdapterList& Environment::NetworkAdapterList()
{
    return *iNetworkAdapterList;
}

ThreadPriorityArbitrator& Environment::PriorityArbitrator()
{
    return *iThreadPriorityArbitrator;
}

OpenHome::Shell* Environment::Shell()
{
    return iShell;
}

IInfoAggregator* Environment::InfoAggregator()
{
    return iInfoAggregator;
}

Net::SsdpListenerMulticast& Environment::MulticastListenerClaim(TIpAddress aInterface)
{
    AutoMutex a(*iPrivateLock);
    const TInt count = (TUint)iMulticastListeners.size();
    for (TInt i=0; i<count; i++) {
        MListener* listener = iMulticastListeners[i];
        if (listener->Interface() == aInterface) {
            listener->AddRef();
            return listener->Listener();
        }
    }
    // first request on this interface; create a shared multicast listener for it
    MListener* listener = new MListener(*this, aInterface);
    iMulticastListeners.push_back(listener);
    listener->Listener().Start();
    return listener->Listener();
}

void Environment::MulticastListenerRelease(TIpAddress aInterface)
{
    iPrivateLock->Wait();
    const TInt count = (TUint)iMulticastListeners.size();
    for (TInt i=0; i<count; i++) {
        MListener* listener = iMulticastListeners[i];
        if (listener->Interface() == aInterface) {
            if (listener->RemoveRef()) {
                iMulticastListeners.erase(iMulticastListeners.begin() + i);
                iPrivateLock->Signal();
                delete listener;
                return;
            }
        }
    }
    iPrivateLock->Signal();
}

void Environment::AddSuspendObserver(ISuspendObserver& aObserver)
{
    iSuspendResumeObserverLock->Wait();
    iSuspendObservers.push_back(&aObserver);
    iSuspendResumeObserverLock->Signal();
}

void Environment::AddResumeObserver(IResumeObserver& aObserver)
{
    iSuspendResumeObserverLock->Wait();
    iResumeObservers.push_back(&aObserver);
    iSuspendResumeObserverLock->Signal();
}

void Environment::RemoveSuspendObserver(ISuspendObserver& aObserver)
{
    iSuspendResumeObserverLock->Wait();
    for (TUint i=0; i<iSuspendObservers.size(); i++) {
        if (iSuspendObservers[i] == &aObserver) {
            iSuspendObservers.erase(iSuspendObservers.begin() + i);
            break;
        }
    }
    iSuspendResumeObserverLock->Signal();
}

void Environment::RemoveResumeObserver(IResumeObserver& aObserver)
{
    iSuspendResumeObserverLock->Wait();
    for (TUint i=0; i<iResumeObservers.size(); i++) {
        if (iResumeObservers[i] == &aObserver) {
            iResumeObservers.erase(iResumeObservers.begin() + i);
            break;
        }
    }
    iSuspendResumeObserverLock->Signal();
}

void Environment::NotifySuspended()
{
    LOG(kTrace, "NotifySuspended\n");
    iSuspendResumeObserverLock->Wait();
    for (TUint i=0; i<iSuspendObservers.size(); i++) {
        iSuspendObservers[i]->NotifySuspended();
    }
    iSuspendResumeObserverLock->Signal();
}

void Environment::NotifyResumed()
{
    LOG(kTrace, "NotifyResumed\n");
    iSuspendResumeObserverLock->Wait();
    for (TUint i=0; i<iResumeObservers.size(); i++) {
        iResumeObservers[i]->NotifyResumed();
    }
    iSuspendResumeObserverLock->Signal();
}

TUint Environment::SequenceNumber()
{
    iPrivateLock->Wait();
    TUint seq = iSequenceNumber++;
    iPrivateLock->Signal();
    return seq;
}

TInt Environment::Random()
{
    iPrivateLock->Wait();
    TInt num = rand();
    iPrivateLock->Signal();
    return num;
}

TUint Environment::Random(TUint aMaxValue, TUint aMinValue)
{
    TUint val = (TUint)Random();
    val = val % (aMaxValue - aMinValue);
    val += aMinValue;
    return val;
}

void Environment::SetRandomSeed(TUint aSeed)
{
    iPrivateLock->Wait();
    srand(aSeed);
    iPrivateLock->Signal();
}

InitialisationParams* Environment::InitParams()
{
    return iInitParams;
}

void Environment::AddObject(IStackObject* aObject)
{
    iPrivateLock->Wait();
    ObjectMap::iterator it = iObjectMap.find(aObject);
    ASSERT(it == iObjectMap.end());
    iObjectMap.insert(std::pair<IStackObject*,IStackObject*>(aObject, aObject));
    iPrivateLock->Signal();
}

void Environment::RemoveObject(IStackObject* aObject)
{
    iPrivateLock->Wait();
    ObjectMap::iterator it = iObjectMap.find(aObject);
    if (it != iObjectMap.end()) {
        iObjectMap.erase(it);
    }
    iPrivateLock->Signal();
}

void Environment::ListObjects()
{
    iPrivateLock->Wait();
    ObjectMap::iterator it = iObjectMap.begin();
    while (it != iObjectMap.end()) {
        it->second->ListObjectDetails();
        it++;
    }
    iPrivateLock->Signal();
}

void Environment::CreateShell()
{
    if (iShell != NULL) {
        return;
    }
    TUint shellPort, shellSessionPriority;
    if (!iInitParams->IsShellEnabled(shellPort, shellSessionPriority)) {
        return;
    }
    iShell = new OpenHome::Shell(*this, shellPort, shellSessionPriority);
    iInfoAggregator = new OpenHome::InfoAggregator(*iShell);
    iShellCommandDebug = new ShellCommandDebug(*iShell);
}

void Environment::SetCpStack(IStack* aStack)
{
    iCpStack = aStack;
}

void Environment::SetDvStack(IStack* aStack)
{
    iDvStack = aStack;
}

IStack* Environment::CpiStack()
{
    return iCpStack;
}

IStack* Environment::DviStack()
{
    return iDvStack;
}

void Environment::SetInitParams(InitialisationParams* aInitParams)
{
    delete iInitParams;
    iInitParams = aInitParams;
    CreateShell();
}


// MListener

MListener::MListener(Environment& aEnv, TIpAddress aInterface)
    : iListener(aEnv, aInterface)
    , iRefCount(1)
{
}

MListener::~MListener()
{
}

Net::SsdpListenerMulticast& MListener::Listener()
{
    return iListener;
}

TIpAddress MListener::Interface() const
{
    return iListener.Interface();
}

void MListener::AddRef()
{
    iRefCount++;
}

TBool MListener::RemoveRef()
{
    iRefCount--;
    return (iRefCount == 0);
}
