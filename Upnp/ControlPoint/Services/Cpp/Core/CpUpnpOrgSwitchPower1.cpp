#include <Core/CpUpnpOrgSwitchPower1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncSetTargetUpnpOrgSwitchPower1 : public SyncProxyAction
{
public:
    SyncSetTargetUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgSwitchPower1& iService;
};

SyncSetTargetUpnpOrgSwitchPower1::SyncSetTargetUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1& aService)
    : iService(aService)
{
}

void SyncSetTargetUpnpOrgSwitchPower1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetTarget(aAsync);
}


class SyncGetTargetUpnpOrgSwitchPower1 : public SyncProxyAction
{
public:
    SyncGetTargetUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1& aService, TBool& aRetTargetValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgSwitchPower1& iService;
    TBool& iRetTargetValue;
};

SyncGetTargetUpnpOrgSwitchPower1::SyncGetTargetUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1& aService, TBool& aRetTargetValue)
    : iService(aService)
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
    SyncGetStatusUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1& aService, TBool& aResultStatus);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgSwitchPower1& iService;
    TBool& iResultStatus;
};

SyncGetStatusUpnpOrgSwitchPower1::SyncGetStatusUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1& aService, TBool& aResultStatus)
    : iService(aService)
    , iResultStatus(aResultStatus)
{
}

void SyncGetStatusUpnpOrgSwitchPower1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStatus(aAsync, iResultStatus);
}


CpProxyUpnpOrgSwitchPower1::CpProxyUpnpOrgSwitchPower1(CpDevice& aDevice)
{
    iService = new CpiService("schemas-upnp-org", "SwitchPower", 1, aDevice.Device());
    Zapp::Parameter* param;

    iActionSetTarget = new Action("SetTarget");
    param = new Zapp::ParameterBool("newTargetValue");
    iActionSetTarget->AddInputParameter(param);

    iActionGetTarget = new Action("GetTarget");
    param = new Zapp::ParameterBool("RetTargetValue");
    iActionGetTarget->AddOutputParameter(param);

    iActionGetStatus = new Action("GetStatus");
    param = new Zapp::ParameterBool("ResultStatus");
    iActionGetStatus->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgSwitchPower1::StatusPropertyChanged);
    iStatus = new PropertyBool("Status", functor);
    iService->AddProperty(iStatus);
}

CpProxyUpnpOrgSwitchPower1::~CpProxyUpnpOrgSwitchPower1()
{
    delete iService;
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
    invocation->Invoke();
}

void CpProxyUpnpOrgSwitchPower1::EndSetTarget(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetTarget"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgSwitchPower1::EndGetTarget(IAsync& aAsync, TBool& aRetTargetValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetTarget"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgSwitchPower1::EndGetStatus(IAsync& aAsync, TBool& aResultStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetStatus"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStatus = iStatus->Value();
}

void CpProxyUpnpOrgSwitchPower1::StatusPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iStatusChanged != NULL) {
        iStatusChanged();
    }
}

