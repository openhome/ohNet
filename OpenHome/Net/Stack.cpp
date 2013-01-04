#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/MimeTypes.h>
#include <OpenHome/Private/Timer.h>

#include <time.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// Strings declared in MimeTypes.h

const char kOhNetMimeTypeCss[]  = "text/css";
const char kOhNetMimeTypeHtml[] = "text/html";
const char kOhNetMimeTypeJs[]   = "application/javascript";
const char kOhNetMimeTypeXml[]  = "application/xml";
const char kOhNetMimeTypeBmp[]  = "image/bmp";
const char kOhNetMimeTypeGif[]  = "image/gif";
const char kOhNetMimeTypeJpeg[] = "image/jpeg";
const char kOhNetMimeTypePng[]  = "image/png";


// Stack

static const TUint kVersionMajor = 1;
static const TUint kVersionMinor = 0;

Stack::Stack()
    : iInitParams(NULL)
    , iTimerManager(NULL)
    , iPublicLock("GMUT")
    , iNetworkAdapterList(NULL)
    , iSequenceNumber(0)
    , iCpStack(NULL)
    , iDvStack(NULL)
    , iPrivateLock("SOML")
{
}

Stack::Stack(InitialisationParams* aInitParams)
    : iInitParams(aInitParams)
    , iPublicLock("GMUT")
    , iNetworkAdapterList(NULL)
    , iSequenceNumber(0)
    , iCpStack(NULL)
    , iDvStack(NULL)
    , iPrivateLock("SOML")
{
    SetAssertHandler(AssertHandlerDefault);
    SetRandomSeed((TUint)(time(NULL) % UINT32_MAX));
    iTimerManager = new OpenHome::TimerManager();
    iNetworkAdapterList = new OpenHome::NetworkAdapterList(*this, 0);
    Functor& subnetListChangeListener = iInitParams->SubnetListChangedListener();
    if (subnetListChangeListener) {
        iNetworkAdapterList->AddSubnetListChangeListener(subnetListChangeListener);
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

Stack::~Stack()
{
    iPublicLock.Wait();
    iPublicLock.Signal();
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
}

void Stack::GetVersion(TUint& aMajor, TUint& aMinor)
{
    aMajor = kVersionMajor;
    aMinor = kVersionMinor;
}

OpenHome::TimerManager& Stack::TimerManager()
{
    return *iTimerManager;
}

OpenHome::Mutex& Stack::Mutex()
{
    return iPublicLock;
}

NetworkAdapterList& Stack::NetworkAdapterList()
{
    return *iNetworkAdapterList;
}

SsdpListenerMulticast& Stack::MulticastListenerClaim(TIpAddress aInterface)
{
    AutoMutex a(iPrivateLock);
    const TInt count = (TUint)iMulticastListeners.size();
    for (TInt i=0; i<count; i++) {
        Stack::MListener* listener = iMulticastListeners[i];
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

void Stack::MulticastListenerRelease(TIpAddress aInterface)
{
    iPrivateLock.Wait();
    const TInt count = (TUint)iMulticastListeners.size();
    for (TInt i=0; i<count; i++) {
        Stack::MListener* listener = iMulticastListeners[i];
        if (listener->Interface() == aInterface) {
            if (listener->RemoveRef()) {
                delete listener;
                iMulticastListeners.erase(iMulticastListeners.begin() + i);
                break;
            }
        }
    }
    iPrivateLock.Signal();
}

TUint Stack::SequenceNumber()
{
    iPrivateLock.Wait();
    TUint seq = iSequenceNumber++;
    iPrivateLock.Signal();
    return seq;
}

InitialisationParams& Stack::InitParams()
{
    return *iInitParams;
}

void Stack::AddObject(IStackObject* aObject)
{
    iPrivateLock.Wait();
    ObjectMap::iterator it = iObjectMap.find(aObject);
    ASSERT(it == iObjectMap.end());
    iObjectMap.insert(std::pair<IStackObject*,IStackObject*>(aObject, aObject));
    iPrivateLock.Signal();
}

void Stack::RemoveObject(IStackObject* aObject)
{
    iPrivateLock.Wait();
    ObjectMap::iterator it = iObjectMap.find(aObject);
    if (it != iObjectMap.end()) {
        iObjectMap.erase(it);
    }
    iPrivateLock.Signal();
}

void Stack::ListObjects()
{
    iPrivateLock.Wait();
    ObjectMap::iterator it = iObjectMap.begin();
    while (it != iObjectMap.end()) {
        it->second->ListObjectDetails();
        it++;
    }
    iPrivateLock.Signal();
}

void Stack::SetCpStack(IStack* aStack)
{
    iCpStack = aStack;
}

void Stack::SetDvStack(IStack* aStack)
{
    iDvStack = aStack;
}

IStack* Stack::CpiStack()
{
    return iCpStack;
}

IStack* Stack::DviStack()
{
    return iDvStack;
}


// Stack::MListener

Stack::MListener::MListener(Stack& aStack, TIpAddress aInterface)
    : iListener(aStack, aInterface)
    , iRefCount(1)
{
}

Stack::MListener::~MListener()
{
}

SsdpListenerMulticast& Stack::MListener::Listener()
{
    return iListener;
}

TIpAddress Stack::MListener::Interface() const
{
    return iListener.Interface();
}

void Stack::MListener::AddRef()
{
    iRefCount++;
}

TBool Stack::MListener::RemoveRef()
{
    iRefCount--;
    return (iRefCount == 0);
}
