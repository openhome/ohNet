#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/MimeTypes.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Net/Private/Globals.h>

#include <time.h>

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

Environment::Environment(OsContext* aOsContext)
    : iOsContext(aOsContext)
    , iInitParams(NULL)
    , iTimerManager(NULL)
    , iNetworkAdapterList(NULL)
    , iSequenceNumber(0)
    , iCpStack(NULL)
    , iDvStack(NULL)
{
    Construct();
}

Environment::Environment(OsContext* aOsContext, InitialisationParams* aInitParams)
    : iOsContext(aOsContext)
    , iInitParams(aInitParams)
    , iNetworkAdapterList(NULL)
    , iSequenceNumber(0)
    , iCpStack(NULL)
    , iDvStack(NULL)
{
    Construct();
    SetAssertHandler(AssertHandlerDefault);
    SetRandomSeed((TUint)(time(NULL) % UINT32_MAX));
    iTimerManager = new OpenHome::TimerManager(*this);
    iNetworkAdapterList = new OpenHome::NetworkAdapterList(*this, 0);
    Functor& subnetListChangeListener = iInitParams->SubnetListChangedListener();
    if (subnetListChangeListener) {
        iNetworkAdapterList->AddSubnetListChangeListener(subnetListChangeListener, false);
    }
    FunctorNetworkAdapter &subnetAddedListener = iInitParams->SubnetAddedListener();
    if (subnetAddedListener) {
        iNetworkAdapterList->AddSubnetAddedListener(subnetAddedListener);
    }
    FunctorNetworkAdapter &subnetRemovedListener = iInitParams->SubnetRemovedListener();
    if (subnetRemovedListener) {
        iNetworkAdapterList->AddSubnetRemovedListener(subnetRemovedListener);
    }
    FunctorNetworkAdapter &networkAdapterChangeListener = iInitParams->NetworkAdapterChangedListener();
    if (networkAdapterChangeListener) {
        iNetworkAdapterList->AddNetworkAdapterChangeListener(networkAdapterChangeListener);
    }
}

void Environment::Construct()
{
    gEnv = this;
    iPublicLock = new OpenHome::Mutex("GMUT");
    iPrivateLock = new OpenHome::Mutex("SOML");
}

Environment::~Environment()
{
    iPublicLock->Wait();
    iPublicLock->Signal();
    delete iCpStack;
    delete iDvStack;
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

NetworkAdapterList& Environment::NetworkAdapterList()
{
    return *iNetworkAdapterList;
}

Net::SsdpListenerMulticast& Environment::MulticastListenerClaim(TIpAddress aInterface)
{
    AutoMutex a(*iPrivateLock);
    const TInt count = (TUint)iMulticastListeners.size();
    for (TInt i=0; i<count; i++) {
        Environment::MListener* listener = iMulticastListeners[i];
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
        Environment::MListener* listener = iMulticastListeners[i];
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

TUint Environment::SequenceNumber()
{
    iPrivateLock->Wait();
    TUint seq = iSequenceNumber++;
    iPrivateLock->Signal();
    return seq;
}

InitialisationParams& Environment::InitParams()
{
    return *iInitParams;
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


// Environment::MListener

Environment::MListener::MListener(Environment& aEnv, TIpAddress aInterface)
    : iListener(aEnv, aInterface)
    , iRefCount(1)
{
}

Environment::MListener::~MListener()
{
}

Net::SsdpListenerMulticast& Environment::MListener::Listener()
{
    return iListener;
}

TIpAddress Environment::MListener::Interface() const
{
    return iListener.Interface();
}

void Environment::MListener::AddRef()
{
    iRefCount++;
}

TBool Environment::MListener::RemoveRef()
{
    iRefCount--;
    return (iRefCount == 0);
}
