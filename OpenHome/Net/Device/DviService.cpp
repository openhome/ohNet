#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Private/DviStack.h>

#include <stdlib.h>


namespace OpenHome {
namespace Net {
class AutoFunctor
{
public:
    AutoFunctor(Functor aFunctor);
    ~AutoFunctor();
private:
    Functor iFunctor;
};
} // namespace Net
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Net;

// AutoFunctor

AutoFunctor::AutoFunctor(Functor aFunctor)
    : iFunctor(aFunctor)
{
}

AutoFunctor::~AutoFunctor()
{
    iFunctor();
}


// DvAction

DvAction::DvAction(OpenHome::Net::Action* aAction, FunctorDviInvocation aFunctor)
    : iAction(aAction)
    , iFunctor(aFunctor)
{
}

OpenHome::Net::Action* DvAction::Action()
{
    return iAction;
}

const OpenHome::Net::Action* DvAction::Action() const
{
    return iAction;
}

FunctorDviInvocation DvAction::Functor() const
{
    return iFunctor;
}


// DviService

DviService::DviService(DvStack& aDvStack, const TChar* aDomain, const TChar* aName, TUint aVersion)
    : Service(aDvStack.Env(), aDomain, aName, aVersion)
    , iDvStack(aDvStack)
    , iLock("DVSM")
    , iRefCount(1)
    , iPropertiesLock("SPRM")
    , iDisabled(true)
    , iCurrentInvocationCount(0)
    , iDisabledSem("DVSS", 0)
{
    iDisabledSem.Signal();
    iDvStack.Env().AddObject(this);
}

DviService::~DviService()
{
    StopSubscriptions();
    iLock.Wait();
    TUint i=0;
    for (i=0; i<iDvActions.size(); i++) {
        delete iDvActions[i].Action();
    }
    for (i=0; i<iProperties.size(); i++) {
        delete iProperties[i];
    }
    iLock.Signal();
    iDvStack.Env().RemoveObject(this);
}

void DviService::StopSubscriptions()
{
    AutoMutex _(iLock);
    for (TUint i=0; i<iSubscriptions.size(); i++) {
        DviSubscription* subscription = iSubscriptions[i];
        iLock.Signal();
        subscription->Stop();
        iLock.Wait();
        iDvStack.SubscriptionManager().RemoveSubscription(*subscription);
        subscription->RemoveRef();
    }
    iSubscriptions.clear();
}

void DviService::AddRef()
{
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    iRefCount++;
    lock.Signal();
}

void DviService::RemoveRef()
{
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    iRefCount--;
    TBool dead = (iRefCount == 0);
    lock.Signal();
    if (dead) {
        delete this;
    }
}

void DviService::Disable()
{
    iLock.Wait();
    iDisabled = true;
    iLock.Signal();
    iDisabledSem.Wait();
    iDisabledSem.Signal(); // allow for possible further calls to Disable()
}

void DviService::Enable()
{
    iLock.Wait();
    iDisabled = false;
    AssertPropertiesInitialised();
    iDisabledSem.Signal();
    iLock.Signal();
}

void DviService::AddAction(Action* aAction, FunctorDviInvocation aFunctor)
{
    DvAction action(aAction, aFunctor);
    iDvActions.push_back(action);
}

const std::vector<DvAction>& DviService::DvActions() const
{
    return iDvActions;
}

void DviService::Invoke(IDviInvocation& aInvocation, const Brx& aActionName)
{
    iLock.Wait();
    LOG(kDvInvocation, "Service: %.*s, Action: %.*s\n",
                       PBUF(iServiceType.Name()), PBUF(aActionName));
    TBool disabled = iDisabled;
    if (disabled) {
        iLock.Signal();
        aInvocation.InvocationReportError(502, Brn("Action not available"));
    }
    iCurrentInvocationCount++;
    (void)iDisabledSem.Clear();
    iLock.Signal();

    {
        AutoFunctor a(MakeFunctor(*this, &DviService::InvocationCompleted));
        for (TUint i=0; i<iDvActions.size(); i++) {
            if (iDvActions[i].Action()->Name() == aActionName) {
                try {
                    iDvActions[i].Functor()(aInvocation);
                }
                catch (InvocationError&) {
                    // avoid calls to aInvocation.InvocationReportError in other catch blocks
                    throw;
                }
                catch (AssertionFailed&) {
                    throw;
                }
                catch (Exception& e) {
                    Brn msg(e.Message());
                    aInvocation.InvocationReportError(801, msg);
                }
                catch (...) {
                    aInvocation.InvocationReportError(801, Brn("Unknown error"));
                }
                return;
            }
        }
    }

    aInvocation.InvocationReportError(501, Brn("Action not implemented"));
}

void DviService::InvocationCompleted()
{
    iLock.Wait();
    iCurrentInvocationCount--;
    if (iCurrentInvocationCount == 0) {
        iDisabledSem.Signal();
    }
    iLock.Signal();
}

void DviService::PropertiesLock()
{
    iPropertiesLock.Wait();
}

void DviService::PropertiesUnlock()
{
    iPropertiesLock.Signal();
}

void DviService::AddProperty(Property* aProperty)
{
    iProperties.push_back(aProperty);
}

const std::vector<Property*>& DviService::Properties() const
{
    return iProperties;
}

void DviService::PublishPropertyUpdates()
{
    iLock.Wait();
    for (TUint i=0; i<iSubscriptions.size(); i++) {
        iDvStack.SubscriptionManager().QueueUpdate(*(iSubscriptions[i]));
    }
    iLock.Signal();
}

void DviService::AddSubscription(DviSubscription* aSubscription)
{
    aSubscription->Start(*this);
    iLock.Wait();
    iSubscriptions.push_back(aSubscription);
    iLock.Signal();
    iDvStack.SubscriptionManager().QueueUpdate(*aSubscription);
}

void DviService::RemoveSubscription(const Brx& aSid)
{
    iLock.Wait();
    for (TUint i=0; i<iSubscriptions.size(); i++) {
        DviSubscription* subscription = iSubscriptions[i];
        if (subscription->Sid() == aSid) {
            iDvStack.SubscriptionManager().RemoveSubscription(*subscription);
            iSubscriptions.erase(iSubscriptions.begin() + i);
            iLock.Signal();
            subscription->Stop();
            subscription->RemoveRef();
            return;
        }
    }
    iLock.Signal();
}

TBool DviService::AssertPropertiesInitialised() const
{
    for (TUint i=0; i<iProperties.size(); i++) {
        if (iProperties[i]->SequenceNumber() == 0) {
            Log::Print("ERROR: uninitialised property.  Provider: ");
            Log::Print(ServiceType().Name());
            Log::Print(", property: ");
            Log::Print(iProperties[i]->Parameter().Name());
            Log::Print("\n");
            ASSERTS();
        }
    }
    return true;
}

void DviService::ListObjectDetails() const
{
    Log::Print("  DviService: addr=%p, serviceType=", this);
    Log::Print(ServiceType().FullName());
    Log::Print(", refCount=%u, subscriptions=%u\n", iRefCount, iSubscriptions.size());
}


// AutoServiceRef

AutoServiceRef::AutoServiceRef(DviService*& aService)
    : iService(aService)
{
}

AutoServiceRef::~AutoServiceRef()
{
    if (iService != NULL) {
        iService->RemoveRef();
        iService = NULL;
    }
}


// DviInvocation

DviInvocation::DviInvocation(IDviInvocation& aInvocation)
    : iInvocation(aInvocation)
{
}

TUint DviInvocation::Version() const
{
    return iInvocation.Version();
}

void DviInvocation::Error(TInt aCode, const Brx& aReason)
{
    iInvocation.InvocationReportError(aCode, aReason);
}

void DviInvocation::StartResponse()
{
    iInvocation.InvocationWriteStart();
}

void DviInvocation::EndResponse()
{
    iInvocation.InvocationWriteEnd();
}

TIpAddress DviInvocation::Adapter() const
{
    return iInvocation.Adapter();
}

const char* DviInvocation::ResourceUriPrefix() const
{
    return iInvocation.ResourceUriPrefix();
}

Endpoint DviInvocation::ClientEndpoint() const
{
    return iInvocation.ClientEndpoint();
}


// DviInvocationResponseBool

DviInvocationResponseBool::DviInvocationResponseBool(IDviInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
{
}

void DviInvocationResponseBool::Write(TBool aValue)
{
    iInvocation.InvocationWriteBool(iName, aValue);
}


// DviInvocationResponseUint

DviInvocationResponseUint::DviInvocationResponseUint(IDviInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
{
}

void DviInvocationResponseUint::Write(TUint aValue)
{
    iInvocation.InvocationWriteUint(iName, aValue);
}


// DviInvocationResponseInt

DviInvocationResponseInt::DviInvocationResponseInt(IDviInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
{
}

void DviInvocationResponseInt::Write(TInt aValue)
{
    iInvocation.InvocationWriteInt(iName, aValue);
}


// DviInvocationResponseBinary

DviInvocationResponseBinary::DviInvocationResponseBinary(IDviInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
    , iFirst(true)
{
}

void DviInvocationResponseBinary::CheckFirst()
{
    if (iFirst) {
        iInvocation.InvocationWriteBinaryStart(iName);
        iFirst = false;
    }
}

void DviInvocationResponseBinary::Write(TByte aValue)
{
    CheckFirst();
    iInvocation.InvocationWriteBinary(aValue);
}

void DviInvocationResponseBinary::Write(const Brx& aValue)
{
    CheckFirst();
    iInvocation.InvocationWriteBinary(aValue);
}

void DviInvocationResponseBinary::WriteFlush()
{
    CheckFirst();
    iInvocation.InvocationWriteBinaryEnd(iName);
}


// DviInvocationResponseString

DviInvocationResponseString::DviInvocationResponseString(IDviInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
    , iFirst(true)
{
}

void DviInvocationResponseString::CheckFirst()
{
    if (iFirst) {
        iInvocation.InvocationWriteStringStart(iName);
        iFirst = false;
    }
}

void DviInvocationResponseString::Write(TByte aValue)
{
    CheckFirst();
    iInvocation.InvocationWriteString(aValue);
}

void DviInvocationResponseString::Write(const Brx& aValue)
{
    CheckFirst();
    iInvocation.InvocationWriteString(aValue);
}

void DviInvocationResponseString::WriteFlush()
{
    CheckFirst();
    iInvocation.InvocationWriteStringEnd(iName);
}
