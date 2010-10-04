#include <Zapp.h>
#include <Stack.h>
#include <Standard.h>
#include <Os.h>
#include <Discovery.h>
#include <NetworkInterfaceList.h>
#include <Printer.h>
#include <Maths.h>
#include <MimeTypes.h>

#include <time.h>

using namespace Zapp;

// Strings declared in MimeTypes.h

const char kZappMimeTypeCss[]  = "text/css";
const char kZappMimeTypeHtml[] = "text/html";
const char kZappMimeTypeJs[]   = "application/x-javascript";
const char kZappMimeTypeXml[]  = "application/xml";
const char kZappMimeTypeBmp[]  = "image/bmp";
const char kZappMimeTypeGif[]  = "image/gif";
const char kZappMimeTypeJpeg[] = "image/jpeg";
const char kZappMimeTypePng[]  = "image/png";


// Stack

TUint gStackInitCount = 0;
Stack* gStack = NULL;

static const TUint kVersionMajor = 1;
static const TUint kVersionMinor = 0;

Stack::Stack(InitialisationParams* aInitParams)
    : iInitParams(aInitParams)
    , iLock("GMUT")
    , iSequenceNumber(0)
    , iCpStack(NULL)
    , iDvStack(NULL)
{
    SetAssertHandler(AssertHandlerDefault);
    ASSERT(gStackInitCount == 0);
    gStack = this;
    gStackInitCount++;
    SetRandomSeed((TUint)(time(NULL) % UINT32_MAX));
    iNetworkInterfaceList = new Zapp::NetworkInterfaceList(iInitParams->DefaultSubnet());
    Functor& subnetChangeListener = iInitParams->SubnetChangedListener();
    if (subnetChangeListener) {
        iNetworkInterfaceList->AddSubnetChangeListener(subnetChangeListener);
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
    iTimerManager.Stop();
    delete iCpStack;
    delete iDvStack;
    delete iNetworkInterfaceList;
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

Zapp::TimerManager& Stack::TimerManager()
{
    return gStack->iTimerManager;
}

Zapp::Mutex& Stack::Mutex()
{
    return gStack->iLock;
}

NetworkInterfaceList& Stack::NetworkInterfaceList()
{
    return *(gStack->iNetworkInterfaceList);
}

SsdpListenerMulticast& Stack::MulticastListenerClaim(TIpAddress aInterface)
{
    AutoMutex a(gStack->iLock);
    const TInt count = gStack->iMulticastListeners.size();
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
    gStack->iLock.Wait();
    const TInt count = gStack->iMulticastListeners.size();
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
    gStack->iLock.Signal();
}

TUint Stack::SequenceNumber()
{
    TUint seq;
    Zapp::Mutex& lock = Stack::Mutex();
    lock.Wait();
    seq = gStack->iSequenceNumber++;
    lock.Signal();
    return seq;
}

InitialisationParams& Stack::InitParams()
{
    return *(gStack->iInitParams);
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
