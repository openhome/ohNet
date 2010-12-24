#include "CpLinnCoUkPtest1.h"
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

class CpProxyLinnCoUkPtest1C : public CpProxyC
{
public:
    CpProxyLinnCoUkPtest1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkPtest1C();
    //CpProxyLinnCoUkPtest1* Proxy() { return static_cast<CpProxyLinnCoUkPtest1*>(iProxy); }

    void SyncTestComPort(TUint aaPort, TBool& aaResult);
    void BeginTestComPort(TUint aaPort, FunctorAsync& aFunctor);
    void EndTestComPort(IAsync& aAsync, TBool& aaResult);

    void SyncLedsOn();
    void BeginLedsOn(FunctorAsync& aFunctor);
    void EndLedsOn(IAsync& aAsync);

    void SyncLedsOff();
    void BeginLedsOff(FunctorAsync& aFunctor);
    void EndLedsOff(IAsync& aAsync);


private:
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionTestComPort;
    Action* iActionLedsOn;
    Action* iActionLedsOff;
};


class SyncTestComPortLinnCoUkPtest1C : public SyncProxyAction
{
public:
    SyncTestComPortLinnCoUkPtest1C(CpProxyLinnCoUkPtest1C& aProxy, TBool& aaResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPtest1C& iService;
    TBool& iaResult;
};

SyncTestComPortLinnCoUkPtest1C::SyncTestComPortLinnCoUkPtest1C(CpProxyLinnCoUkPtest1C& aProxy, TBool& aaResult)
    : iService(aProxy)
    , iaResult(aaResult)
{
}

void SyncTestComPortLinnCoUkPtest1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTestComPort(aAsync, iaResult);
}


class SyncLedsOnLinnCoUkPtest1C : public SyncProxyAction
{
public:
    SyncLedsOnLinnCoUkPtest1C(CpProxyLinnCoUkPtest1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPtest1C& iService;
};

SyncLedsOnLinnCoUkPtest1C::SyncLedsOnLinnCoUkPtest1C(CpProxyLinnCoUkPtest1C& aProxy)
    : iService(aProxy)
{
}

void SyncLedsOnLinnCoUkPtest1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndLedsOn(aAsync);
}


class SyncLedsOffLinnCoUkPtest1C : public SyncProxyAction
{
public:
    SyncLedsOffLinnCoUkPtest1C(CpProxyLinnCoUkPtest1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPtest1C& iService;
};

SyncLedsOffLinnCoUkPtest1C::SyncLedsOffLinnCoUkPtest1C(CpProxyLinnCoUkPtest1C& aProxy)
    : iService(aProxy)
{
}

void SyncLedsOffLinnCoUkPtest1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndLedsOff(aAsync);
}

CpProxyLinnCoUkPtest1C::CpProxyLinnCoUkPtest1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Ptest", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
    Zapp::Parameter* param;

    iActionTestComPort = new Action("TestComPort");
    param = new Zapp::ParameterUint("aPort");
    iActionTestComPort->AddInputParameter(param);
    param = new Zapp::ParameterBool("aResult");
    iActionTestComPort->AddOutputParameter(param);

    iActionLedsOn = new Action("LedsOn");

    iActionLedsOff = new Action("LedsOff");
}

CpProxyLinnCoUkPtest1C::~CpProxyLinnCoUkPtest1C()
{
    delete iActionTestComPort;
    delete iActionLedsOn;
    delete iActionLedsOff;
}

void CpProxyLinnCoUkPtest1C::SyncTestComPort(TUint aaPort, TBool& aaResult)
{
    SyncTestComPortLinnCoUkPtest1C sync(*this, aaResult);
    BeginTestComPort(aaPort, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPtest1C::BeginTestComPort(TUint aaPort, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTestComPort, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionTestComPort->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaPort));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTestComPort->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPtest1C::EndTestComPort(IAsync& aAsync, TBool& aaResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("TestComPort"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaResult = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkPtest1C::SyncLedsOn()
{
    SyncLedsOnLinnCoUkPtest1C sync(*this);
    BeginLedsOn(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPtest1C::BeginLedsOn(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionLedsOn, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPtest1C::EndLedsOn(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("LedsOn"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPtest1C::SyncLedsOff()
{
    SyncLedsOffLinnCoUkPtest1C sync(*this);
    BeginLedsOff(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPtest1C::BeginLedsOff(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionLedsOff, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPtest1C::EndLedsOff(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("LedsOff"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}


THandle CpProxyLinnCoUkPtest1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkPtest1C(aDevice);
}

void CpProxyLinnCoUkPtest1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkPtest1SyncTestComPort(THandle aHandle, uint32_t aaPort, uint32_t* aaResult)
{
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaResult = 0;
    proxyC->SyncTestComPort(aaPort, *(TBool*)aaResult);
}

void CpProxyLinnCoUkPtest1BeginTestComPort(THandle aHandle, uint32_t aaPort, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginTestComPort(aaPort, functor);
}

int32_t CpProxyLinnCoUkPtest1EndTestComPort(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaResult)
{
    int32_t err = 0;
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaResult = 0;
    try {
        proxyC->EndTestComPort(*async, *(TBool*)aaResult);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPtest1SyncLedsOn(THandle aHandle)
{
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncLedsOn();
}

void CpProxyLinnCoUkPtest1BeginLedsOn(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginLedsOn(functor);
}

int32_t CpProxyLinnCoUkPtest1EndLedsOn(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndLedsOn(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPtest1SyncLedsOff(THandle aHandle)
{
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncLedsOff();
}

void CpProxyLinnCoUkPtest1BeginLedsOff(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginLedsOff(functor);
}

int32_t CpProxyLinnCoUkPtest1EndLedsOff(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndLedsOff(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

