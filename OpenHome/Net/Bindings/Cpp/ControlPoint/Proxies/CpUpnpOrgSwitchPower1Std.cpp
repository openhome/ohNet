#include "CpUpnpOrgSwitchPower1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncSetTargetUpnpOrgSwitchPower1Cpp : public SyncProxyAction
{
public:
    SyncSetTargetUpnpOrgSwitchPower1Cpp(CpProxyUpnpOrgSwitchPower1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetTargetUpnpOrgSwitchPower1Cpp() {}
private:
    CpProxyUpnpOrgSwitchPower1Cpp& iService;
};

SyncSetTargetUpnpOrgSwitchPower1Cpp::SyncSetTargetUpnpOrgSwitchPower1Cpp(CpProxyUpnpOrgSwitchPower1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetTargetUpnpOrgSwitchPower1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetTarget(aAsync);
}


class SyncGetTargetUpnpOrgSwitchPower1Cpp : public SyncProxyAction
{
public:
    SyncGetTargetUpnpOrgSwitchPower1Cpp(CpProxyUpnpOrgSwitchPower1Cpp& aProxy, bool& aRetTargetValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTargetUpnpOrgSwitchPower1Cpp() {}
private:
    CpProxyUpnpOrgSwitchPower1Cpp& iService;
    bool& iRetTargetValue;
};

SyncGetTargetUpnpOrgSwitchPower1Cpp::SyncGetTargetUpnpOrgSwitchPower1Cpp(CpProxyUpnpOrgSwitchPower1Cpp& aProxy, bool& aRetTargetValue)
    : iService(aProxy)
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
    SyncGetStatusUpnpOrgSwitchPower1Cpp(CpProxyUpnpOrgSwitchPower1Cpp& aProxy, bool& aResultStatus);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStatusUpnpOrgSwitchPower1Cpp() {}
private:
    CpProxyUpnpOrgSwitchPower1Cpp& iService;
    bool& iResultStatus;
};

SyncGetStatusUpnpOrgSwitchPower1Cpp::SyncGetStatusUpnpOrgSwitchPower1Cpp(CpProxyUpnpOrgSwitchPower1Cpp& aProxy, bool& aResultStatus)
    : iService(aProxy)
    , iResultStatus(aResultStatus)
{
}

void SyncGetStatusUpnpOrgSwitchPower1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStatus(aAsync, iResultStatus);
}


CpProxyUpnpOrgSwitchPower1Cpp::CpProxyUpnpOrgSwitchPower1Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgSwitchPower1Cpp::StatusPropertyChanged);
    iStatus = new PropertyBool(aDevice.Device().GetCpStack().Env(), "Status", functor);
    AddProperty(iStatus);
}

CpProxyUpnpOrgSwitchPower1Cpp::~CpProxyUpnpOrgSwitchPower1Cpp()
{
    DestroyService();
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
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgSwitchPower1Cpp::EndSetTarget(IAsync& aAsync)
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
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgSwitchPower1Cpp::EndGetTarget(IAsync& aAsync, bool& aRetTargetValue)
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
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgSwitchPower1Cpp::EndGetStatus(IAsync& aAsync, bool& aResultStatus)
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

void CpProxyUpnpOrgSwitchPower1Cpp::SetPropertyStatusChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStatusChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgSwitchPower1Cpp::PropertyStatus(bool& aStatus) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStatus = iStatus->Value();
}

void CpProxyUpnpOrgSwitchPower1Cpp::StatusPropertyChanged()
{
    ReportEvent(iStatusChanged);
}

