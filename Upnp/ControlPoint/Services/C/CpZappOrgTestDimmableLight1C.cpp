#include "CpZappOrgTestDimmableLight1.h"
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;

class CpProxyZappOrgTestDimmableLight1C : public CpProxyC
{
public:
    CpProxyZappOrgTestDimmableLight1C(CpDeviceC aDevice);
    ~CpProxyZappOrgTestDimmableLight1C();
    //CpProxyZappOrgTestDimmableLight1* Proxy() { return static_cast<CpProxyZappOrgTestDimmableLight1*>(iProxy); }

    void SyncGetLevel(TUint& aLevel);
    void BeginGetLevel(FunctorAsync& aFunctor);
    void EndGetLevel(IAsync& aAsync, TUint& aLevel);

    void SyncSetLevel(TUint aLevel);
    void BeginSetLevel(TUint aLevel, FunctorAsync& aFunctor);
    void EndSetLevel(IAsync& aAsync);

    void SetPropertyA_ARG_LevelChanged(Functor& aFunctor);

    void PropertyA_ARG_Level(TUint& aA_ARG_Level) const;
private:
    void A_ARG_LevelPropertyChanged();
private:
    Mutex iLock;
    Action* iActionGetLevel;
    Action* iActionSetLevel;
    PropertyUint* iA_ARG_Level;
    Functor iA_ARG_LevelChanged;
};


class SyncGetLevelZappOrgTestDimmableLight1C : public SyncProxyAction
{
public:
    SyncGetLevelZappOrgTestDimmableLight1C(CpProxyZappOrgTestDimmableLight1C& aProxy, TUint& aLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestDimmableLight1C& iService;
    TUint& iLevel;
};

SyncGetLevelZappOrgTestDimmableLight1C::SyncGetLevelZappOrgTestDimmableLight1C(CpProxyZappOrgTestDimmableLight1C& aProxy, TUint& aLevel)
    : iService(aProxy)
    , iLevel(aLevel)
{
}

void SyncGetLevelZappOrgTestDimmableLight1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLevel(aAsync, iLevel);
}


class SyncSetLevelZappOrgTestDimmableLight1C : public SyncProxyAction
{
public:
    SyncSetLevelZappOrgTestDimmableLight1C(CpProxyZappOrgTestDimmableLight1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestDimmableLight1C& iService;
};

SyncSetLevelZappOrgTestDimmableLight1C::SyncSetLevelZappOrgTestDimmableLight1C(CpProxyZappOrgTestDimmableLight1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetLevelZappOrgTestDimmableLight1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLevel(aAsync);
}

CpProxyZappOrgTestDimmableLight1C::CpProxyZappOrgTestDimmableLight1C(CpDeviceC aDevice)
    : CpProxyC("zapp-org", "TestDimmableLight", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    Zapp::Parameter* param;

    iActionGetLevel = new Action("GetLevel");
    param = new Zapp::ParameterUint("Level");
    iActionGetLevel->AddOutputParameter(param);

    iActionSetLevel = new Action("SetLevel");
    param = new Zapp::ParameterUint("Level");
    iActionSetLevel->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyZappOrgTestDimmableLight1C::A_ARG_LevelPropertyChanged);
    iA_ARG_Level = new PropertyUint("A_ARG_Level", functor);
    AddProperty(iA_ARG_Level);
}

CpProxyZappOrgTestDimmableLight1C::~CpProxyZappOrgTestDimmableLight1C()
{
    DestroyService();
    delete iActionGetLevel;
    delete iActionSetLevel;
}

void CpProxyZappOrgTestDimmableLight1C::SyncGetLevel(TUint& aLevel)
{
    SyncGetLevelZappOrgTestDimmableLight1C sync(*this, aLevel);
    BeginGetLevel(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestDimmableLight1C::BeginGetLevel(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetLevel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestDimmableLight1C::EndGetLevel(IAsync& aAsync, TUint& aLevel)
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

void CpProxyZappOrgTestDimmableLight1C::SyncSetLevel(TUint aLevel)
{
    SyncSetLevelZappOrgTestDimmableLight1C sync(*this);
    BeginSetLevel(aLevel, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestDimmableLight1C::BeginSetLevel(TUint aLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aLevel));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestDimmableLight1C::EndSetLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestDimmableLight1C::SetPropertyA_ARG_LevelChanged(Functor& aFunctor)
{
    iLock.Wait();
    iA_ARG_LevelChanged = aFunctor;
    iLock.Signal();
}

void CpProxyZappOrgTestDimmableLight1C::PropertyA_ARG_Level(TUint& aA_ARG_Level) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aA_ARG_Level = iA_ARG_Level->Value();
    PropertyReadUnlock();
}

void CpProxyZappOrgTestDimmableLight1C::A_ARG_LevelPropertyChanged()
{
    ReportEvent(iA_ARG_LevelChanged);
}


THandle CpProxyZappOrgTestDimmableLight1Create(CpDeviceC aDevice)
{
    return new CpProxyZappOrgTestDimmableLight1C(aDevice);
}

void CpProxyZappOrgTestDimmableLight1Destroy(THandle aHandle)
{
    CpProxyZappOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyZappOrgTestDimmableLight1C*>(aHandle);
    delete proxyC;
}

void CpProxyZappOrgTestDimmableLight1SyncGetLevel(THandle aHandle, uint32_t* aLevel)
{
    CpProxyZappOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyZappOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetLevel(*aLevel);
}

void CpProxyZappOrgTestDimmableLight1BeginGetLevel(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyZappOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetLevel(functor);
}

int32_t CpProxyZappOrgTestDimmableLight1EndGetLevel(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aLevel)
{
    int32_t err = 0;
    CpProxyZappOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyZappOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetLevel(*async, *aLevel);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestDimmableLight1SyncSetLevel(THandle aHandle, uint32_t aLevel)
{
    CpProxyZappOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyZappOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetLevel(aLevel);
}

void CpProxyZappOrgTestDimmableLight1BeginSetLevel(THandle aHandle, uint32_t aLevel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyZappOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetLevel(aLevel, functor);
}

int32_t CpProxyZappOrgTestDimmableLight1EndSetLevel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyZappOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetLevel(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestDimmableLight1SetPropertyA_ARG_LevelChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyZappOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyA_ARG_LevelChanged(functor);
}

void CpProxyZappOrgTestDimmableLight1PropertyA_ARG_Level(THandle aHandle, uint32_t* aA_ARG_Level)
{
    CpProxyZappOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyZappOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyA_ARG_Level(*aA_ARG_Level);
}

