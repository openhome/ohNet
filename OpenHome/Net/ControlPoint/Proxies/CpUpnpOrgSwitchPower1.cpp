#include "CpUpnpOrgSwitchPower1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncSetTargetUpnpOrgSwitchPower1 : public SyncProxyAction
{
public:
    SyncSetTargetUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetTargetUpnpOrgSwitchPower1() {}
private:
    CpProxyUpnpOrgSwitchPower1& iService;
};

SyncSetTargetUpnpOrgSwitchPower1::SyncSetTargetUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1& aProxy)
    : iService(aProxy)
{
}

void SyncSetTargetUpnpOrgSwitchPower1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetTarget(aAsync);
}


class SyncGetTargetUpnpOrgSwitchPower1 : public SyncProxyAction
{
public:
    SyncGetTargetUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1& aProxy, TBool& aRetTargetValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTargetUpnpOrgSwitchPower1() {}
private:
    CpProxyUpnpOrgSwitchPower1& iService;
    TBool& iRetTargetValue;
};

SyncGetTargetUpnpOrgSwitchPower1::SyncGetTargetUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1& aProxy, TBool& aRetTargetValue)
    : iService(aProxy)
    , iRetTargetValue(aRetTargetValue)
{
}

void SyncGetTargetUpnpOrgSwitchPower1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTarget(aAsync, iRetTargetValue);
}


class SyncGetStatusUpnpOrgSwitchPower1 : public SyncProxyAction
{
public:
    SyncGetStatusUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1& aProxy, TBool& aResultStatus);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStatusUpnpOrgSwitchPower1() {}
private:
    CpProxyUpnpOrgSwitchPower1& iService;
    TBool& iResultStatus;
};

SyncGetStatusUpnpOrgSwitchPower1::SyncGetStatusUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1& aProxy, TBool& aResultStatus)
    : iService(aProxy)
    , iResultStatus(aResultStatus)
{
}

void SyncGetStatusUpnpOrgSwitchPower1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStatus(aAsync, iResultStatus);
}


CpProxyUpnpOrgSwitchPower1::CpProxyUpnpOrgSwitchPower1(CpDevice& aDevice)
    : CpProxy("schemas-upnp-org", "SwitchPower", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;

    iActionSetTarget = new Action("SetTarget");
    param = new OpenHome::Net::ParameterBool("newTargetValue");
    iActionSetTarget->AddInputParameter(param);

    iActionGetTarget = new Action("GetTarget");
    param = new OpenHome::Net::ParameterBool("RetTargetValue");
    iActionGetTarget->AddOutputParameter(param);

    iActionGetStatus = new Action("GetStatus");
    param = new OpenHome::Net::ParameterBool("ResultStatus");
    iActionGetStatus->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgSwitchPower1::StatusPropertyChanged);
    iStatus = new PropertyBool(aDevice.Device().GetCpStack().Env(), "Status", functor);
    AddProperty(iStatus);
}

CpProxyUpnpOrgSwitchPower1::~CpProxyUpnpOrgSwitchPower1()
{
    DestroyService();
    delete iActionSetTarget;
    delete iActionGetTarget;
    delete iActionGetStatus;
}

void CpProxyUpnpOrgSwitchPower1::SyncSetTarget(TBool anewTargetValue)
{
    SyncSetTargetUpnpOrgSwitchPower1 sync(*this);
    BeginSetTarget(anewTargetValue, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgSwitchPower1::BeginSetTarget(TBool anewTargetValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetTarget, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetTarget->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], anewTargetValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgSwitchPower1::EndSetTarget(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetTarget"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgSwitchPower1::SyncGetTarget(TBool& aRetTargetValue)
{
    SyncGetTargetUpnpOrgSwitchPower1 sync(*this, aRetTargetValue);
    BeginGetTarget(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgSwitchPower1::BeginGetTarget(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetTarget, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetTarget->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgSwitchPower1::EndGetTarget(IAsync& aAsync, TBool& aRetTargetValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetTarget"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aRetTargetValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgSwitchPower1::SyncGetStatus(TBool& aResultStatus)
{
    SyncGetStatusUpnpOrgSwitchPower1 sync(*this, aResultStatus);
    BeginGetStatus(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgSwitchPower1::BeginGetStatus(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetStatus, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStatus->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgSwitchPower1::EndGetStatus(IAsync& aAsync, TBool& aResultStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetStatus"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aResultStatus = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgSwitchPower1::SetPropertyStatusChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStatusChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgSwitchPower1::PropertyStatus(TBool& aStatus) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStatus = iStatus->Value();
}

void CpProxyUpnpOrgSwitchPower1::StatusPropertyChanged()
{
    ReportEvent(iStatusChanged);
}

