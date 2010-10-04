#include <Std/CpUpnpOrgSwitchPower1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncSetTargetUpnpOrgSwitchPower1Cpp : public SyncProxyAction
{
public:
    SyncSetTargetUpnpOrgSwitchPower1Cpp(CpProxyUpnpOrgSwitchPower1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgSwitchPower1Cpp& iService;
};

SyncSetTargetUpnpOrgSwitchPower1Cpp::SyncSetTargetUpnpOrgSwitchPower1Cpp(CpProxyUpnpOrgSwitchPower1Cpp& aService)
    : iService(aService)
{
}

void SyncSetTargetUpnpOrgSwitchPower1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetTarget(aAsync);
}


class SyncGetTargetUpnpOrgSwitchPower1Cpp : public SyncProxyAction
{
public:
    SyncGetTargetUpnpOrgSwitchPower1Cpp(CpProxyUpnpOrgSwitchPower1Cpp& aService, bool& aRetTargetValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgSwitchPower1Cpp& iService;
    bool& iRetTargetValue;
};

SyncGetTargetUpnpOrgSwitchPower1Cpp::SyncGetTargetUpnpOrgSwitchPower1Cpp(CpProxyUpnpOrgSwitchPower1Cpp& aService, bool& aRetTargetValue)
    : iService(aService)
    , iRetTargetValue(aRetTargetValue)
{
}

void SyncGetTargetUpnpOrgSwitchPower1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTarget(aAsync, iRetTargetValue);
}


class SyncGetStatusUpnpOrgSwitchPower1Cpp : public SyncProxyAction
{
public:
    SyncGetStatusUpnpOrgSwitchPower1Cpp(CpProxyUpnpOrgSwitchPower1Cpp& aService, bool& aResultStatus);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgSwitchPower1Cpp& iService;
    bool& iResultStatus;
};

SyncGetStatusUpnpOrgSwitchPower1Cpp::SyncGetStatusUpnpOrgSwitchPower1Cpp(CpProxyUpnpOrgSwitchPower1Cpp& aService, bool& aResultStatus)
    : iService(aService)
    , iResultStatus(aResultStatus)
{
}

void SyncGetStatusUpnpOrgSwitchPower1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStatus(aAsync, iResultStatus);
}


CpProxyUpnpOrgSwitchPower1Cpp::CpProxyUpnpOrgSwitchPower1Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgSwitchPower1Cpp::StatusPropertyChanged);
    iStatus = new PropertyBool("Status", functor);
    iService->AddProperty(iStatus);
}

CpProxyUpnpOrgSwitchPower1Cpp::~CpProxyUpnpOrgSwitchPower1Cpp()
{
    delete iService;
    delete iActionSetTarget;
    delete iActionGetTarget;
    delete iActionGetStatus;
}

void CpProxyUpnpOrgSwitchPower1Cpp::SyncSetTarget(bool anewTargetValue)
{
    SyncSetTargetUpnpOrgSwitchPower1Cpp sync(*this);
    BeginSetTarget(anewTargetValue, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgSwitchPower1Cpp::BeginSetTarget(bool anewTargetValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetTarget, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetTarget->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], anewTargetValue));
    invocation->Invoke();
}

void CpProxyUpnpOrgSwitchPower1Cpp::EndSetTarget(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetTarget"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgSwitchPower1Cpp::SyncGetTarget(bool& aRetTargetValue)
{
    SyncGetTargetUpnpOrgSwitchPower1Cpp sync(*this, aRetTargetValue);
    BeginGetTarget(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgSwitchPower1Cpp::BeginGetTarget(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetTarget, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetTarget->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgSwitchPower1Cpp::EndGetTarget(IAsync& aAsync, bool& aRetTargetValue)
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

void CpProxyUpnpOrgSwitchPower1Cpp::SyncGetStatus(bool& aResultStatus)
{
    SyncGetStatusUpnpOrgSwitchPower1Cpp sync(*this, aResultStatus);
    BeginGetStatus(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgSwitchPower1Cpp::BeginGetStatus(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetStatus, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStatus->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgSwitchPower1Cpp::EndGetStatus(IAsync& aAsync, bool& aResultStatus)
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

void CpProxyUpnpOrgSwitchPower1Cpp::SetPropertyStatusChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStatusChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgSwitchPower1Cpp::PropertyStatus(bool& aStatus) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStatus = iStatus->Value();
}

void CpProxyUpnpOrgSwitchPower1Cpp::StatusPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iStatusChanged != NULL) {
        iStatusChanged();
    }
}

