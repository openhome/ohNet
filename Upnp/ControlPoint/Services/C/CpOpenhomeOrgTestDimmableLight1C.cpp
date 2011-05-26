#include "CpOpenhomeOrgTestDimmableLight1.h"
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>
#include <OhNetTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class CpProxyOpenhomeOrgTestDimmableLight1C : public CpProxyC
{
public:
    CpProxyOpenhomeOrgTestDimmableLight1C(CpDeviceC aDevice);
    ~CpProxyOpenhomeOrgTestDimmableLight1C();
    //CpProxyOpenhomeOrgTestDimmableLight1* Proxy() { return static_cast<CpProxyOpenhomeOrgTestDimmableLight1*>(iProxy); }

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


class SyncGetLevelOpenhomeOrgTestDimmableLight1C : public SyncProxyAction
{
public:
    SyncGetLevelOpenhomeOrgTestDimmableLight1C(CpProxyOpenhomeOrgTestDimmableLight1C& aProxy, TUint& aLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestDimmableLight1C& iService;
    TUint& iLevel;
};

SyncGetLevelOpenhomeOrgTestDimmableLight1C::SyncGetLevelOpenhomeOrgTestDimmableLight1C(CpProxyOpenhomeOrgTestDimmableLight1C& aProxy, TUint& aLevel)
    : iService(aProxy)
    , iLevel(aLevel)
{
}

void SyncGetLevelOpenhomeOrgTestDimmableLight1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLevel(aAsync, iLevel);
}


class SyncSetLevelOpenhomeOrgTestDimmableLight1C : public SyncProxyAction
{
public:
    SyncSetLevelOpenhomeOrgTestDimmableLight1C(CpProxyOpenhomeOrgTestDimmableLight1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestDimmableLight1C& iService;
};

SyncSetLevelOpenhomeOrgTestDimmableLight1C::SyncSetLevelOpenhomeOrgTestDimmableLight1C(CpProxyOpenhomeOrgTestDimmableLight1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetLevelOpenhomeOrgTestDimmableLight1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLevel(aAsync);
}

CpProxyOpenhomeOrgTestDimmableLight1C::CpProxyOpenhomeOrgTestDimmableLight1C(CpDeviceC aDevice)
    : CpProxyC("openhome-org", "TestDimmableLight", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    OpenHome::Net::Parameter* param;

    iActionGetLevel = new Action("GetLevel");
    param = new OpenHome::Net::ParameterUint("Level");
    iActionGetLevel->AddOutputParameter(param);

    iActionSetLevel = new Action("SetLevel");
    param = new OpenHome::Net::ParameterUint("Level");
    iActionSetLevel->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyOpenhomeOrgTestDimmableLight1C::A_ARG_LevelPropertyChanged);
    iA_ARG_Level = new PropertyUint("A_ARG_Level", functor);
    AddProperty(iA_ARG_Level);
}

CpProxyOpenhomeOrgTestDimmableLight1C::~CpProxyOpenhomeOrgTestDimmableLight1C()
{
    DestroyService();
    delete iActionGetLevel;
    delete iActionSetLevel;
}

void CpProxyOpenhomeOrgTestDimmableLight1C::SyncGetLevel(TUint& aLevel)
{
    SyncGetLevelOpenhomeOrgTestDimmableLight1C sync(*this, aLevel);
    BeginGetLevel(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestDimmableLight1C::BeginGetLevel(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetLevel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestDimmableLight1C::EndGetLevel(IAsync& aAsync, TUint& aLevel)
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

void CpProxyOpenhomeOrgTestDimmableLight1C::SyncSetLevel(TUint aLevel)
{
    SyncSetLevelOpenhomeOrgTestDimmableLight1C sync(*this);
    BeginSetLevel(aLevel, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestDimmableLight1C::BeginSetLevel(TUint aLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aLevel));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestDimmableLight1C::EndSetLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestDimmableLight1C::SetPropertyA_ARG_LevelChanged(Functor& aFunctor)
{
    iLock.Wait();
    iA_ARG_LevelChanged = aFunctor;
    iLock.Signal();
}

void CpProxyOpenhomeOrgTestDimmableLight1C::PropertyA_ARG_Level(TUint& aA_ARG_Level) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aA_ARG_Level = iA_ARG_Level->Value();
    PropertyReadUnlock();
}

void CpProxyOpenhomeOrgTestDimmableLight1C::A_ARG_LevelPropertyChanged()
{
    ReportEvent(iA_ARG_LevelChanged);
}


THandle CpProxyOpenhomeOrgTestDimmableLight1Create(CpDeviceC aDevice)
{
    return new CpProxyOpenhomeOrgTestDimmableLight1C(aDevice);
}

void CpProxyOpenhomeOrgTestDimmableLight1Destroy(THandle aHandle)
{
    CpProxyOpenhomeOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestDimmableLight1C*>(aHandle);
    delete proxyC;
}

void CpProxyOpenhomeOrgTestDimmableLight1SyncGetLevel(THandle aHandle, uint32_t* aLevel)
{
    CpProxyOpenhomeOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetLevel(*aLevel);
}

void CpProxyOpenhomeOrgTestDimmableLight1BeginGetLevel(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetLevel(functor);
}

int32_t CpProxyOpenhomeOrgTestDimmableLight1EndGetLevel(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aLevel)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestDimmableLight1C*>(aHandle);
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

void CpProxyOpenhomeOrgTestDimmableLight1SyncSetLevel(THandle aHandle, uint32_t aLevel)
{
    CpProxyOpenhomeOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetLevel(aLevel);
}

void CpProxyOpenhomeOrgTestDimmableLight1BeginSetLevel(THandle aHandle, uint32_t aLevel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetLevel(aLevel, functor);
}

int32_t CpProxyOpenhomeOrgTestDimmableLight1EndSetLevel(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestDimmableLight1C*>(aHandle);
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

void CpProxyOpenhomeOrgTestDimmableLight1SetPropertyA_ARG_LevelChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyA_ARG_LevelChanged(functor);
}

void CpProxyOpenhomeOrgTestDimmableLight1PropertyA_ARG_Level(THandle aHandle, uint32_t* aA_ARG_Level)
{
    CpProxyOpenhomeOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyA_ARG_Level(*aA_ARG_Level);
}

