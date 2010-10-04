#include <DviService.h>
#include <Service.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <Http.h>
#include <Printer.h>
#include <DviSubscription.h>

using namespace Zapp;

// DvAction

DvAction::DvAction(Zapp::Action* aAction, FunctorDvInvocation aFunctor)
    : iAction(aAction)
    , iFunctor(aFunctor)
{
}

Zapp::Action* DvAction::Action()
{
    return iAction;
}

const Zapp::Action* DvAction::Action() const
{
    return iAction;
}

FunctorDvInvocation DvAction::Functor() const
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
}

DviService::~DviService()
{
    iLock.Wait();
    TUint i=0;
    for (; i<iSubscriptions.size(); i++) {
        DviSubscription* subscription = iSubscriptions[i];
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
}

void DviService::AddRef()
{
    iLock.Wait();
    iRefCount++;
    iLock.Signal();
}

void DviService::RemoveRef()
{
    iLock.Wait();
    iRefCount--;
    TBool dead = (iRefCount == 0);
    iLock.Signal();
    if (dead) {
        delete this;
    }
}

void DviService::AddAction(Action* aAction, FunctorDvInvocation aFunctor)
{
    DvAction action(aAction, aFunctor);
    iDvActions.push_back(action);
}

const DviService::VectorActions& DviService::DvActions() const
{
    return iDvActions;
}

void DviService::Invoke(IDvInvocation& aInvocation, TUint aVersion, const Brx& aActionName)
{
    for (TUint i=0; i<iDvActions.size(); i++) {
        if (iDvActions[i].Action()->Name() == aActionName) {
            iDvActions[i].Functor()(aInvocation, aVersion);
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
    /* Removing a reference from a subscription may cause the subscription to be deleted
       Deleting a subscription causes it to release its reference to a device
       Removing the device reference may cause the device to be deleted
       Deleting the device will cause it to release its references to its services (including this one)
       Avoid this service being deleted mid-function by claiming our own reference */
    AddRef();
    iLock.Wait();
    for (TUint i=0; i<iSubscriptions.size(); i++) {
        DviSubscription* subscription = iSubscriptions[i];
        if (subscription->Sid() == aSid) {
            DviSubscriptionManager::RemoveSubscription(*subscription);
            iSubscriptions.erase(iSubscriptions.begin() + i);
            iLock.Signal();
            subscription->RemoveRef();
            RemoveRef();
            return;
        }
    }
    iLock.Signal();
    RemoveRef();
}


// InvocationResponse

InvocationResponse::InvocationResponse(IDvInvocation& aInvocation)
    : iInvocation(aInvocation)
{
}

void InvocationResponse::Error(TInt aCode, const Brx& aReason)
{
	iInvocation.InvocationReportError(aCode, aReason);
}

void InvocationResponse::Start()
{
	iInvocation.InvocationWriteStart();
}

void InvocationResponse::End()
{
	iInvocation.InvocationWriteEnd();
}


// InvocationResponseBool

InvocationResponseBool::InvocationResponseBool(IDvInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
{
}

void InvocationResponseBool::Write(TBool aValue)
{
	iInvocation.InvocationWriteBool(iName, aValue);
}


// InvocationResponseUint

InvocationResponseUint::InvocationResponseUint(IDvInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
{
}

void InvocationResponseUint::Write(TUint aValue)
{
	iInvocation.InvocationWriteUint(iName, aValue);
}


// InvocationResponseInt

InvocationResponseInt::InvocationResponseInt(IDvInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
{
}

void InvocationResponseInt::Write(TInt aValue)
{
	iInvocation.InvocationWriteInt(iName, aValue);
}


// InvocationResponseBinary

InvocationResponseBinary::InvocationResponseBinary(IDvInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
    , iFirst(true)
{
}


void InvocationResponseBinary::CheckFirst()
{
	if (iFirst) {
		iInvocation.InvocationWriteBinaryStart(iName);
		iFirst = false;
	}
}

void InvocationResponseBinary::Write(TByte aValue)
{
	CheckFirst();
	iInvocation.InvocationWriteBinary(aValue);
}

void InvocationResponseBinary::Write(const Brx& aValue)
{
	CheckFirst();
	iInvocation.InvocationWriteBinary(aValue);
}

void InvocationResponseBinary::WriteFlush()
{
	CheckFirst();
	iInvocation.InvocationWriteBinaryEnd(iName);
}


// InvocationResponseString

InvocationResponseString::InvocationResponseString(IDvInvocation& aInvocation, const TChar* aName)
    : iInvocation(aInvocation)
    , iName(aName)
    , iFirst(true)
{
}


void InvocationResponseString::CheckFirst()
{
	if (iFirst) {
		iInvocation.InvocationWriteStringStart(iName);
		iFirst = false;
	}
}

void InvocationResponseString::Write(TByte aValue)
{
	CheckFirst();
	iInvocation.InvocationWriteString(aValue);
}

void InvocationResponseString::Write(const Brx& aValue)
{
	CheckFirst();
	iInvocation.InvocationWriteString(aValue);
}

void InvocationResponseString::WriteFlush()
{
	CheckFirst();
	iInvocation.InvocationWriteStringEnd(iName);
}
