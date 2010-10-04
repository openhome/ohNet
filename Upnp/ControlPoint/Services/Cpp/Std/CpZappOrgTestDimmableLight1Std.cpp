#include <Std/CpZappOrgTestDimmableLight1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncGetLevelZappOrgTestDimmableLight1Cpp : public SyncProxyAction
{
public:
    SyncGetLevelZappOrgTestDimmableLight1Cpp(CpProxyZappOrgTestDimmableLight1Cpp& aService, uint32_t& aLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestDimmableLight1Cpp& iService;
    uint32_t& iLevel;
};

SyncGetLevelZappOrgTestDimmableLight1Cpp::SyncGetLevelZappOrgTestDimmableLight1Cpp(CpProxyZappOrgTestDimmableLight1Cpp& aService, uint32_t& aLevel)
    : iService(aService)
    , iLevel(aLevel)
{
}

void SyncGetLevelZappOrgTestDimmableLight1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLevel(aAsync, iLevel);
}


class SyncSetLevelZappOrgTestDimmableLight1Cpp : public SyncProxyAction
{
public:
    SyncSetLevelZappOrgTestDimmableLight1Cpp(CpProxyZappOrgTestDimmableLight1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestDimmableLight1Cpp& iService;
};

SyncSetLevelZappOrgTestDimmableLight1Cpp::SyncSetLevelZappOrgTestDimmableLight1Cpp(CpProxyZappOrgTestDimmableLight1Cpp& aService)
    : iService(aService)
{
}

void SyncSetLevelZappOrgTestDimmableLight1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLevel(aAsync);
}


CpProxyZappOrgTestDimmableLight1Cpp::CpProxyZappOrgTestDimmableLight1Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyZappOrgTestDimmableLight1Cpp::A_ARG_LevelPropertyChanged);
    iA_ARG_Level = new PropertyUint("A_ARG_Level", functor);
    iService->AddProperty(iA_ARG_Level);
}

CpProxyZappOrgTestDimmableLight1Cpp::~CpProxyZappOrgTestDimmableLight1Cpp()
{
    delete iService;
    delete iActionGetLevel;
    delete iActionSetLevel;
}

void CpProxyZappOrgTestDimmableLight1Cpp::SyncGetLevel(uint32_t& aLevel)
{
    SyncGetLevelZappOrgTestDimmableLight1Cpp sync(*this, aLevel);
    BeginGetLevel(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestDimmableLight1Cpp::BeginGetLevel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetLevel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestDimmableLight1Cpp::EndGetLevel(IAsync& aAsync, uint32_t& aLevel)
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

void CpProxyZappOrgTestDimmableLight1Cpp::SyncSetLevel(uint32_t aLevel)
{
    SyncSetLevelZappOrgTestDimmableLight1Cpp sync(*this);
    BeginSetLevel(aLevel, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestDimmableLight1Cpp::BeginSetLevel(uint32_t aLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aLevel));
    invocation->Invoke();
}

void CpProxyZappOrgTestDimmableLight1Cpp::EndSetLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestDimmableLight1Cpp::SetPropertyA_ARG_LevelChanged(Functor& aFunctor)
{
    iLock->Wait();
    iA_ARG_LevelChanged = aFunctor;
    iLock->Signal();
}

void CpProxyZappOrgTestDimmableLight1Cpp::PropertyA_ARG_Level(uint32_t& aA_ARG_Level) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aA_ARG_Level = iA_ARG_Level->Value();
}

void CpProxyZappOrgTestDimmableLight1Cpp::A_ARG_LevelPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iA_ARG_LevelChanged != NULL) {
        iA_ARG_LevelChanged();
    }
}

