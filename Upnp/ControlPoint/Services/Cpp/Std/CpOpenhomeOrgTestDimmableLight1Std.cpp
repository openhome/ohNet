#include "CpOpenhomeOrgTestDimmableLight1.h"
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncGetLevelOpenhomeOrgTestDimmableLight1Cpp : public SyncProxyAction
{
public:
    SyncGetLevelOpenhomeOrgTestDimmableLight1Cpp(CpProxyOpenhomeOrgTestDimmableLight1Cpp& aProxy, uint32_t& aLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestDimmableLight1Cpp& iService;
    uint32_t& iLevel;
};

SyncGetLevelOpenhomeOrgTestDimmableLight1Cpp::SyncGetLevelOpenhomeOrgTestDimmableLight1Cpp(CpProxyOpenhomeOrgTestDimmableLight1Cpp& aProxy, uint32_t& aLevel)
    : iService(aProxy)
    , iLevel(aLevel)
{
}

void SyncGetLevelOpenhomeOrgTestDimmableLight1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLevel(aAsync, iLevel);
}


class SyncSetLevelOpenhomeOrgTestDimmableLight1Cpp : public SyncProxyAction
{
public:
    SyncSetLevelOpenhomeOrgTestDimmableLight1Cpp(CpProxyOpenhomeOrgTestDimmableLight1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestDimmableLight1Cpp& iService;
};

SyncSetLevelOpenhomeOrgTestDimmableLight1Cpp::SyncSetLevelOpenhomeOrgTestDimmableLight1Cpp(CpProxyOpenhomeOrgTestDimmableLight1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetLevelOpenhomeOrgTestDimmableLight1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLevel(aAsync);
}


CpProxyOpenhomeOrgTestDimmableLight1Cpp::CpProxyOpenhomeOrgTestDimmableLight1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("openhome-org", "TestDimmableLight", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;

    iActionGetLevel = new Action("GetLevel");
    param = new OpenHome::Net::ParameterUint("Level");
    iActionGetLevel->AddOutputParameter(param);

    iActionSetLevel = new Action("SetLevel");
    param = new OpenHome::Net::ParameterUint("Level");
    iActionSetLevel->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyOpenhomeOrgTestDimmableLight1Cpp::A_ARG_LevelPropertyChanged);
    iA_ARG_Level = new PropertyUint("A_ARG_Level", functor);
    AddProperty(iA_ARG_Level);
}

CpProxyOpenhomeOrgTestDimmableLight1Cpp::~CpProxyOpenhomeOrgTestDimmableLight1Cpp()
{
    DestroyService();
    delete iActionGetLevel;
    delete iActionSetLevel;
}

void CpProxyOpenhomeOrgTestDimmableLight1Cpp::SyncGetLevel(uint32_t& aLevel)
{
    SyncGetLevelOpenhomeOrgTestDimmableLight1Cpp sync(*this, aLevel);
    BeginGetLevel(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestDimmableLight1Cpp::BeginGetLevel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetLevel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestDimmableLight1Cpp::EndGetLevel(IAsync& aAsync, uint32_t& aLevel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aLevel = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyOpenhomeOrgTestDimmableLight1Cpp::SyncSetLevel(uint32_t aLevel)
{
    SyncSetLevelOpenhomeOrgTestDimmableLight1Cpp sync(*this);
    BeginSetLevel(aLevel, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestDimmableLight1Cpp::BeginSetLevel(uint32_t aLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aLevel));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestDimmableLight1Cpp::EndSetLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestDimmableLight1Cpp::SetPropertyA_ARG_LevelChanged(Functor& aFunctor)
{
    iLock->Wait();
    iA_ARG_LevelChanged = aFunctor;
    iLock->Signal();
}

void CpProxyOpenhomeOrgTestDimmableLight1Cpp::PropertyA_ARG_Level(uint32_t& aA_ARG_Level) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aA_ARG_Level = iA_ARG_Level->Value();
    PropertyReadUnlock();
}

void CpProxyOpenhomeOrgTestDimmableLight1Cpp::A_ARG_LevelPropertyChanged()
{
    ReportEvent(iA_ARG_LevelChanged);
}

