#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/MimeTypes.h>

#include <time.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// Strings declared in MimeTypes.h

const char kOhNetMimeTypeCss[]  = "text/css";
const char kOhNetMimeTypeHtml[] = "text/html";
const char kOhNetMimeTypeJs[]   = "application/x-javascript";
const char kOhNetMimeTypeXml[]  = "application/xml";
const char kOhNetMimeTypeBmp[]  = "image/bmp";
const char kOhNetMimeTypeGif[]  = "image/gif";
const char kOhNetMimeTypeJpeg[] = "image/jpeg";
const char kOhNetMimeTypePng[]  = "image/png";


// Stack

TUint gStackInitCount = 0;
Stack* gStack = NULL;

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
    ASSERT(gStackInitCount == 0);
    gStack = this;
    gStackInitCount++;
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
    ASSERT(gStackInitCount == 0);
    gStack = this;
    gStackInitCount++;
    SetRandomSeed((TUint)(time(NULL) % UINT32_MAX));
    iTimerManager = new OpenHome::TimerManager();
    iNetworkAdapterList = new OpenHome::NetworkAdapterList(0);
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

void Stack::Destroy()
{
    delete gStack;
}

Stack::~Stack()
{
    ASSERT(gStackInitCount == 1);
    gStackInitCount = 0;
    iPublicLock.Wait();
    ASSERT(iMulticastListeners.size() == 0);
    iPublicLock.Signal();
    if (iTimerManager != NULL) {
        iTimerManager->Stop();
    }
    delete iCpStack;
    delete iDvStack;
    delete iNetworkAdapterList;
    if (iObjectMap.size() != 0) {
        Log::Print("ERROR: destroying stack before some owned objects\n");
        Log::Print("...leaked objects are\n");
        DoListObjects();
        ASSERTS();
    }
    delete iInitParams;
    gStack = NULL;
}

TBool Stack::IsInitialised()
{
    return (gStack != NULL);
}

void Stack::GetVersion(TUint& aMajor, TUint& aMinor)
{
	aMajor = kVersionMajor;
	aMinor = kVersionMinor;
}

OpenHome::TimerManager& Stack::TimerManager()
{
    return *(gStack->iTimerManager);
}

OpenHome::Mutex& Stack::Mutex()
{
    return gStack->iPublicLock;
}

NetworkAdapterList& Stack::NetworkAdapterList()
{
    return *(gStack->iNetworkAdapterList);
}

SsdpListenerMulticast& Stack::MulticastListenerClaim(TIpAddress aInterface)
{
    AutoMutex a(gStack->iPrivateLock);
    const TInt count = (TUint)gStack->iMulticastListeners.size();
    for (TInt i=0; i<count; i++) {
        Stack::MListener* listener = gStack->iMulticastListeners[i];
        if (listener->Interface() == aInterface) {
            listener->AddRef();
            return listener->Listener();
        }
    }
    // first request on this interface; create a shared multicast listener for it
    MListener* listener = new MListener(aInterface);
    gStack->iMulticastListeners.push_back(listener);
    listener->Listener().Start();
    return listener->Listener();
}

void Stack::MulticastListenerRelease(TIpAddress aInterface)
{
    gStack->iPrivateLock.Wait();
    const TInt count = (TUint)gStack->iMulticastListeners.size();
    for (TInt i=0; i<count; i++) {
        Stack::MListener* listener = gStack->iMulticastListeners[i];
        if (listener->Interface() == aInterface) {
            if (listener->RemoveRef()) {
                delete listener;
                gStack->iMulticastListeners.erase(gStack->iMulticastListeners.begin() + i);
                break;
            }
        }
    }
    gStack->iPrivateLock.Signal();
}

TUint Stack::SequenceNumber()
{
    TUint seq;
    OpenHome::Mutex& lock = Stack::Mutex();
    lock.Wait();
    seq = gStack->iSequenceNumber++;
    lock.Signal();
    return seq;
}

InitialisationParams& Stack::InitParams()
{
    return *(gStack->iInitParams);
}

void Stack::AddObject(void* aPtr, const char* aClassName)
{
    if (gStack != NULL)  {
        gStack->DoAddObject(aPtr, aClassName);
    }
}

void Stack::RemoveObject(void* aPtr, const char* aClassName)
{
    if (gStack != NULL)  {
        gStack->DoRemoveObject(aPtr, aClassName);
    }
}

void Stack::ListObjects()
{
    if (gStack != NULL)  {
        gStack->DoListObjects();
    }
}

void Stack::DoAddObject(void* aPtr, const char* aClassName)
{
    iPrivateLock.Wait();
    Brn key(aClassName);
    ObjectType* map = NULL;
    ObjectTypeMap::iterator it = iObjectMap.find(key);
    if (it != iObjectMap.end()) {
        map = it->second;
        key.Set(map->Name());
    }
    else {
        ObjectType* o = new ObjectType(aClassName);
        map = o;
        key.Set(o->Name());
        iObjectMap.insert(std::pair<Brn,ObjectType*>(key, o));
    }
    map->Map().insert(std::pair<void*,void*>(aPtr, aPtr));
    iPrivateLock.Signal();
}

void Stack::DoRemoveObject(void* aPtr, const char* aClassName)
{
    iPrivateLock.Wait();
    Brn key(aClassName);
    ObjectTypeMap::iterator it = iObjectMap.find(key);
    if (it != iObjectMap.end()) {
        ObjectMap& map = it->second->Map();
        ObjectMap::iterator it2 = map.find(aPtr);
        if (it2 != map.end()) {
            map.erase(it2);
            if (map.size() == 0) {
                delete it->second;
                iObjectMap.erase(it);
            }
        }
    }
    iPrivateLock.Signal();
}

void Stack::DoListObjects()
{
    iPrivateLock.Wait();
    ObjectTypeMap::iterator it = iObjectMap.begin();
    while (it != iObjectMap.end()) {
        Log::Print("  ");
        ObjectType* o = it->second;
        Log::Print(o->Name());
        Log::Print("\n");
        ObjectMap& objects = o->Map();
        ObjectMap::iterator it2 = objects.begin();
        while (it2 != objects.end()) {
            Log::Print("    %8x\n", it2->second);
            it2++;
        }
        it++;
    }
    iPrivateLock.Signal();
}

void Stack::SetCpiStack(IStack* aStack)
{
    gStack->iCpStack = aStack;
}

void Stack::SetDviStack(IStack* aStack)
{
    gStack->iDvStack = aStack;
}

IStack* Stack::CpiStack()
{
    return gStack->iCpStack;
}

IStack* Stack::DviStack()
{
    return gStack->iDvStack;
}


// Stack::MListener

Stack::MListener::MListener(TIpAddress aInterface)
    : iListener(aInterface)
    , iRefCount(1)
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


// Stack::ObjectType

Stack::ObjectType::ObjectType(const TChar* aName)
    : iClassName(aName)
{
}

Stack::ObjectType::~ObjectType()
{
    ASSERT(iMap.size() == 0);
}
