#include "CpOpenhomeOrgSubscriptionLongPoll1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Private/CpiDevice.h>

namespace OpenHome {
namespace Net {

class SyncSubscribeOpenhomeOrgSubscriptionLongPoll1 : public SyncProxyAction
{
public:
    SyncSubscribeOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1& aProxy, Brh& aSid, TUint& aDuration);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgSubscriptionLongPoll1& iService;
    Brh& iSid;
    TUint& iDuration;
};

class SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1 : public SyncProxyAction
{
public:
    SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgSubscriptionLongPoll1& iService;
};

class SyncRenewOpenhomeOrgSubscriptionLongPoll1 : public SyncProxyAction
{
public:
    SyncRenewOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1& aProxy, TUint& aDuration);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgSubscriptionLongPoll1& iService;
    TUint& iDuration;
};

class SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1 : public SyncProxyAction
{
public:
    SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1& aProxy, Brh& aUpdates);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgSubscriptionLongPoll1& iService;
    Brh& iUpdates;
};

} // namespace Net
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Net;


// SyncSubscribeOpenhomeOrgSubscriptionLongPoll1

SyncSubscribeOpenhomeOrgSubscriptionLongPoll1::SyncSubscribeOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1& aProxy, Brh& aSid, TUint& aDuration)
    : iService(aProxy)
    , iSid(aSid)
    , iDuration(aDuration)
{
}

void SyncSubscribeOpenhomeOrgSubscriptionLongPoll1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSubscribe(aAsync, iSid, iDuration);
}

// SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1

SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1::SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1& aProxy)
    : iService(aProxy)
{
}

void SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1::CompleteRequest(IAsync& aAsync)
{
    iService.EndUnsubscribe(aAsync);
}

// SyncRenewOpenhomeOrgSubscriptionLongPoll1

SyncRenewOpenhomeOrgSubscriptionLongPoll1::SyncRenewOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1& aProxy, TUint& aDuration)
    : iService(aProxy)
    , iDuration(aDuration)
{
}

void SyncRenewOpenhomeOrgSubscriptionLongPoll1::CompleteRequest(IAsync& aAsync)
{
    iService.EndRenew(aAsync, iDuration);
}

// SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1

SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1::SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1& aProxy, Brh& aUpdates)
    : iService(aProxy)
    , iUpdates(aUpdates)
{
}

void SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPropertyUpdates(aAsync, iUpdates);
}


// CpProxyOpenhomeOrgSubscriptionLongPoll1

CpProxyOpenhomeOrgSubscriptionLongPoll1::CpProxyOpenhomeOrgSubscriptionLongPoll1(CpDevice& aDevice)
    : CpProxy("openhome-org", "SubscriptionLongPoll", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;

    iActionSubscribe = new Action("Subscribe");
    param = new OpenHome::Net::ParameterString("ClientId");
    iActionSubscribe->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Udn");
    iActionSubscribe->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Service");
    iActionSubscribe->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("RequestedDuration");
    iActionSubscribe->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Sid");
    iActionSubscribe->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("Duration");
    iActionSubscribe->AddOutputParameter(param);

    iActionUnsubscribe = new Action("Unsubscribe");
    param = new OpenHome::Net::ParameterString("Sid");
    iActionUnsubscribe->AddInputParameter(param);

    iActionRenew = new Action("Renew");
    param = new OpenHome::Net::ParameterString("Sid");
    iActionRenew->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("RequestedDuration");
    iActionRenew->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("Duration");
    iActionRenew->AddOutputParameter(param);

    iActionGetPropertyUpdates = new Action("GetPropertyUpdates");
    param = new OpenHome::Net::ParameterString("ClientId");
    iActionGetPropertyUpdates->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Updates");
    iActionGetPropertyUpdates->AddOutputParameter(param);
}

CpProxyOpenhomeOrgSubscriptionLongPoll1::~CpProxyOpenhomeOrgSubscriptionLongPoll1()
{
    DestroyService();
    delete iActionSubscribe;
    delete iActionUnsubscribe;
    delete iActionRenew;
    delete iActionGetPropertyUpdates;
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1::SyncSubscribe(const Brx& aClientId, const Brx& aUdn, const Brx& aService, TUint aRequestedDuration, Brh& aSid, TUint& aDuration)
{
    SyncSubscribeOpenhomeOrgSubscriptionLongPoll1 sync(*this, aSid, aDuration);
    BeginSubscribe(aClientId, aUdn, aService, aRequestedDuration, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1::BeginSubscribe(const Brx& aClientId, const Brx& aUdn, const Brx& aService, TUint aRequestedDuration, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSubscribe, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSubscribe->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aClientId));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aUdn));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aService));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedDuration));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSubscribe->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1::EndSubscribe(IAsync& aAsync, Brh& aSid, TUint& aDuration)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Subscribe"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aSid);
    aDuration = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1::SyncUnsubscribe(const Brx& aSid)
{
    SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1 sync(*this);
    BeginUnsubscribe(aSid, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1::BeginUnsubscribe(const Brx& aSid, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionUnsubscribe, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionUnsubscribe->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSid));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1::EndUnsubscribe(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Unsubscribe"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1::SyncRenew(const Brx& aSid, TUint aRequestedDuration, TUint& aDuration)
{
    SyncRenewOpenhomeOrgSubscriptionLongPoll1 sync(*this, aDuration);
    BeginRenew(aSid, aRequestedDuration, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1::BeginRenew(const Brx& aSid, TUint aRequestedDuration, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRenew, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionRenew->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aSid));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRequestedDuration));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRenew->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1::EndRenew(IAsync& aAsync, TUint& aDuration)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Renew"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aDuration = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1::SyncGetPropertyUpdates(const Brx& aClientId, Brh& aUpdates)
{
    SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1 sync(*this, aUpdates);
    BeginGetPropertyUpdates(aClientId, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1::BeginGetPropertyUpdates(const Brx& aClientId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetPropertyUpdates, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetPropertyUpdates->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aClientId));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetPropertyUpdates->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgSubscriptionLongPoll1::EndGetPropertyUpdates(IAsync& aAsync, Brh& aUpdates)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetPropertyUpdates"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aUpdates);
}

