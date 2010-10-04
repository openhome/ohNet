#include <Core/CpZappOrgTestDimmableLight1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncGetLevelZappOrgTestDimmableLight1 : public SyncProxyAction
{
public:
    SyncGetLevelZappOrgTestDimmableLight1(CpProxyZappOrgTestDimmableLight1& aService, TUint& aLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestDimmableLight1& iService;
    TUint& iLevel;
};

SyncGetLevelZappOrgTestDimmableLight1::SyncGetLevelZappOrgTestDimmableLight1(CpProxyZappOrgTestDimmableLight1& aService, TUint& aLevel)
    : iService(aService)
    , iLevel(aLevel)
{
}

void SyncGetLevelZappOrgTestDimmableLight1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLevel(aAsync, iLevel);
}


class SyncSetLevelZappOrgTestDimmableLight1 : public SyncProxyAction
{
public:
    SyncSetLevelZappOrgTestDimmableLight1(CpProxyZappOrgTestDimmableLight1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestDimmableLight1& iService;
};

SyncSetLevelZappOrgTestDimmableLight1::SyncSetLevelZappOrgTestDimmableLight1(CpProxyZappOrgTestDimmableLight1& aService)
    : iService(aService)
{
}

void SyncSetLevelZappOrgTestDimmableLight1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLevel(aAsync);
}


CpProxyZappOrgTestDimmableLight1::CpProxyZappOrgTestDimmableLight1(CpDevice& aDevice)
{
    iService = new CpiService("zapp-org", "TestDimmableLight", 1, aDevice.Device());
    Zapp::Parameter* param;

    iActionGetLevel = new Action("GetLevel");
    param = new Zapp::ParameterUint("Level");
    iActionGetLevel->AddOutputParameter(param);

    iActionSetLevel = new Action("SetLevel");
    param = new Zapp::ParameterUint("Level");
    iActionSetLevel->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyZappOrgTestDimmableLight1::A_ARG_LevelPropertyChanged);
    iA_ARG_Level = new PropertyUint("A_ARG_Level", functor);
    iService->AddProperty(iA_ARG_Level);
}

CpProxyZappOrgTestDimmableLight1::~CpProxyZappOrgTestDimmableLight1()
{
    delete iService;
    delete iActionGetLevel;
    delete iActionSetLevel;
}

void CpProxyZappOrgTestDimmableLight1::SyncGetLevel(TUint& aLevel)
{
    SyncGetLevelZappOrgTestDimmableLight1 sync(*this, aLevel);
    BeginGetLevel(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestDimmableLight1::BeginGetLevel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetLevel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestDimmableLight1::EndGetLevel(IAsync& aAsync, TUint& aLevel)
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

void CpProxyZappOrgTestDimmableLight1::SyncSetLevel(TUint aLevel)
{
    SyncSetLevelZappOrgTestDimmableLight1 sync(*this);
    BeginSetLevel(aLevel, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestDimmableLight1::BeginSetLevel(TUint aLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aLevel));
    invocation->Invoke();
}

void CpProxyZappOrgTestDimmableLight1::EndSetLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestDimmableLight1::SetPropertyA_ARG_LevelChanged(Functor& aFunctor)
{
    iLock->Wait();
    iA_ARG_LevelChanged = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestDimmableLight1::PropertyA_ARG_Level(TUint& aA_ARG_Level) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aA_ARG_Level = iA_ARG_Level->Value();
}

void CpProxyZappOrgTestDimmableLight1::A_ARG_LevelPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iA_ARG_LevelChanged != NULL) {
        iA_ARG_LevelChanged();
    }
}

