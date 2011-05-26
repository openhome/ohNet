#include "CpOpenhomeOrgTestDimmableLight1.h"
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncGetLevelOpenhomeOrgTestDimmableLight1 : public SyncProxyAction
{
public:
    SyncGetLevelOpenhomeOrgTestDimmableLight1(CpProxyOpenhomeOrgTestDimmableLight1& aProxy, TUint& aLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestDimmableLight1& iService;
    TUint& iLevel;
};

SyncGetLevelOpenhomeOrgTestDimmableLight1::SyncGetLevelOpenhomeOrgTestDimmableLight1(CpProxyOpenhomeOrgTestDimmableLight1& aProxy, TUint& aLevel)
    : iService(aProxy)
    , iLevel(aLevel)
{
}

void SyncGetLevelOpenhomeOrgTestDimmableLight1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLevel(aAsync, iLevel);
}


class SyncSetLevelOpenhomeOrgTestDimmableLight1 : public SyncProxyAction
{
public:
    SyncSetLevelOpenhomeOrgTestDimmableLight1(CpProxyOpenhomeOrgTestDimmableLight1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestDimmableLight1& iService;
};

SyncSetLevelOpenhomeOrgTestDimmableLight1::SyncSetLevelOpenhomeOrgTestDimmableLight1(CpProxyOpenhomeOrgTestDimmableLight1& aProxy)
    : iService(aProxy)
{
}

void SyncSetLevelOpenhomeOrgTestDimmableLight1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLevel(aAsync);
}


CpProxyOpenhomeOrgTestDimmableLight1::CpProxyOpenhomeOrgTestDimmableLight1(CpDevice& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyOpenhomeOrgTestDimmableLight1::A_ARG_LevelPropertyChanged);
    iA_ARG_Level = new PropertyUint("A_ARG_Level", functor);
    AddProperty(iA_ARG_Level);
}

CpProxyOpenhomeOrgTestDimmableLight1::~CpProxyOpenhomeOrgTestDimmableLight1()
{
    DestroyService();
    delete iActionGetLevel;
    delete iActionSetLevel;
}

void CpProxyOpenhomeOrgTestDimmableLight1::SyncGetLevel(TUint& aLevel)
{
    SyncGetLevelOpenhomeOrgTestDimmableLight1 sync(*this, aLevel);
    BeginGetLevel(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestDimmableLight1::BeginGetLevel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetLevel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestDimmableLight1::EndGetLevel(IAsync& aAsync, TUint& aLevel)
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

void CpProxyOpenhomeOrgTestDimmableLight1::SyncSetLevel(TUint aLevel)
{
    SyncSetLevelOpenhomeOrgTestDimmableLight1 sync(*this);
    BeginSetLevel(aLevel, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestDimmableLight1::BeginSetLevel(TUint aLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aLevel));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestDimmableLight1::EndSetLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestDimmableLight1::SetPropertyA_ARG_LevelChanged(Functor& aFunctor)
{
    iLock->Wait();
    iA_ARG_LevelChanged = aFunctor;
    iLock->Signal();
}

void CpProxyOpenhomeOrgTestDimmableLight1::PropertyA_ARG_Level(TUint& aA_ARG_Level) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aA_ARG_Level = iA_ARG_Level->Value();
    PropertyReadUnlock();
}

void CpProxyOpenhomeOrgTestDimmableLight1::A_ARG_LevelPropertyChanged()
{
    ReportEvent(iA_ARG_LevelChanged);
}

