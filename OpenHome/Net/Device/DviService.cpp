#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Private/DviStack.h>

#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Net;

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

DviService::DviService(const TChar* aDomain, const TChar* aName, TUint aVersion)
    : Service(aDomain, aName, aVersion)
    , iLock("DVSM")
    , iRefCount(1)
    , iPropertiesLock("SPRM")
{
    Stack::AddObject(this);
}

DviService::~DviService()
{
    iLock.Wait();
    TUint i=0;
    for (; i<iSubscriptions.size(); i++) {
        DviSubscription* subscription = iSubscriptions[i];
        subscription->Stop();
        DviSubscriptionManager::RemoveSubscription(*subscription);
        subscription->RemoveRef();
    }
    for (i=0; i<iDvActions.size(); i++) {
        delete iDvActions[i].Action();
    }
    for (i=0; i<iProperties.size(); i++) {
        delete iProperties[i];
    }
    iLock.Signal();
    Stack::RemoveObject(this);
}

void DviService::AddRef()
{
    Stack::Mutex().Wait();
    iRefCount++;
    Stack::Mutex().Signal();
}

void DviService::RemoveRef()
{
    Stack::Mutex().Wait();
    iRefCount--;
    TBool dead = (iRefCount == 0);
    Stack::Mutex().Signal();
    if (dead) {
        delete this;
    }
}

void DviService::AddAction(Action* aAction, FunctorDviInvocation aFunctor)
{
    DvAction action(aAction, aFunctor);
    iDvActions.push_back(action);
}

const DviService::VectorActions& DviService::DvActions() const
{
    return iDvActions;
}

void DviService::Invoke(IDviInvocation& aInvocation, const Brx& aActionName)
{
    for (TUint i=0; i<iDvActions.size(); i++) {
        if (iDvActions[i].Action()->Name() == aActionName) {
            iDvActions[i].Functor()(aInvocation);
            return;
        }
    }

    aInvocation.InvocationReportError(501, Brn("Action not implemented"));
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

const DviService::VectorProperties& DviService::Properties() const
{
    return iProperties;
}

void DviService::PublishPropertyUpdates()
{
    iLock.Wait();
    for (TUint i=0; i<iSubscriptions.size(); i++) {
        DviSubscriptionManager::QueueUpdate(*(iSubscriptions[i]));
    }
    iLock.Signal();
}

void DviService::AddSubscription(DviSubscription* aSubscription)
{
    aSubscription->Start(*this);
    iLock.Wait();
    iSubscriptions.push_back(aSubscription);
    iLock.Signal();
    DviSubscriptionManager::QueueUpdate(*aSubscription);
}

void DviService::RemoveSubscription(const Brx& aSid)
{
    iLock.Wait();
    for (TUint i=0; i<iSubscriptions.size(); i++) {
        DviSubscription* subscription = iSubscriptions[i];
        if (subscription->Sid() == aSid) {
            DviSubscriptionManager::RemoveSubscription(*subscription);
            iSubscriptions.erase(iSubscriptions.begin() + i);
            iLock.Signal();
            subscription->RemoveRef();
            return;
        }
    }
    iLock.Signal();
}

void DviService::ListObjectDetails() const
{
    Log::Print("  DviService: addr=%p, serviceType=", this);
    Log::Print(ServiceType().FullName());
    Log::Print(", refCount=%u, subscriptions=%u\n", iRefCount, iSubscriptions.size());
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
