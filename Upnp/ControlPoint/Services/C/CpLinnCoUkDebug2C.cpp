#include "CpLinnCoUkDebug2.h"
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

class CpProxyLinnCoUkDebug2C : public CpProxyC
{
public:
    CpProxyLinnCoUkDebug2C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkDebug2C();
    //CpProxyLinnCoUkDebug2* Proxy() { return static_cast<CpProxyLinnCoUkDebug2*>(iProxy); }

    void SyncSetDebugLevel(TUint aaDebugLevel);
    void BeginSetDebugLevel(TUint aaDebugLevel, FunctorAsync& aFunctor);
    void EndSetDebugLevel(IAsync& aAsync);

    void SyncDebugLevel(TUint& aaDebugLevel);
    void BeginDebugLevel(FunctorAsync& aFunctor);
    void EndDebugLevel(IAsync& aAsync, TUint& aaDebugLevel);

    void SyncMemWrite(TUint aaMemAddress, const Brx& aaMemData);
    void BeginMemWrite(TUint aaMemAddress, const Brx& aaMemData, FunctorAsync& aFunctor);
    void EndMemWrite(IAsync& aAsync);


private:
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionSetDebugLevel;
    Action* iActionDebugLevel;
    Action* iActionMemWrite;
};


class SyncSetDebugLevelLinnCoUkDebug2C : public SyncProxyAction
{
public:
    SyncSetDebugLevelLinnCoUkDebug2C(CpProxyLinnCoUkDebug2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDebug2C& iService;
};

SyncSetDebugLevelLinnCoUkDebug2C::SyncSetDebugLevelLinnCoUkDebug2C(CpProxyLinnCoUkDebug2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetDebugLevelLinnCoUkDebug2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDebugLevel(aAsync);
}


class SyncDebugLevelLinnCoUkDebug2C : public SyncProxyAction
{
public:
    SyncDebugLevelLinnCoUkDebug2C(CpProxyLinnCoUkDebug2C& aProxy, TUint& aaDebugLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDebug2C& iService;
    TUint& iaDebugLevel;
};

SyncDebugLevelLinnCoUkDebug2C::SyncDebugLevelLinnCoUkDebug2C(CpProxyLinnCoUkDebug2C& aProxy, TUint& aaDebugLevel)
    : iService(aProxy)
    , iaDebugLevel(aaDebugLevel)
{
}

void SyncDebugLevelLinnCoUkDebug2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDebugLevel(aAsync, iaDebugLevel);
}


class SyncMemWriteLinnCoUkDebug2C : public SyncProxyAction
{
public:
    SyncMemWriteLinnCoUkDebug2C(CpProxyLinnCoUkDebug2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDebug2C& iService;
};

SyncMemWriteLinnCoUkDebug2C::SyncMemWriteLinnCoUkDebug2C(CpProxyLinnCoUkDebug2C& aProxy)
    : iService(aProxy)
{
}

void SyncMemWriteLinnCoUkDebug2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndMemWrite(aAsync);
}

CpProxyLinnCoUkDebug2C::CpProxyLinnCoUkDebug2C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Debug", 2, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
    Zapp::Parameter* param;

    iActionSetDebugLevel = new Action("SetDebugLevel");
    param = new Zapp::ParameterUint("aDebugLevel");
    iActionSetDebugLevel->AddInputParameter(param);

    iActionDebugLevel = new Action("DebugLevel");
    param = new Zapp::ParameterUint("aDebugLevel");
    iActionDebugLevel->AddOutputParameter(param);

    iActionMemWrite = new Action("MemWrite");
    param = new Zapp::ParameterUint("aMemAddress");
    iActionMemWrite->AddInputParameter(param);
    param = new Zapp::ParameterBinary("aMemData");
    iActionMemWrite->AddInputParameter(param);
}

CpProxyLinnCoUkDebug2C::~CpProxyLinnCoUkDebug2C()
{
    delete iActionSetDebugLevel;
    delete iActionDebugLevel;
    delete iActionMemWrite;
}

void CpProxyLinnCoUkDebug2C::SyncSetDebugLevel(TUint aaDebugLevel)
{
    SyncSetDebugLevelLinnCoUkDebug2C sync(*this);
    BeginSetDebugLevel(aaDebugLevel, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDebug2C::BeginSetDebugLevel(TUint aaDebugLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetDebugLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDebugLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaDebugLevel));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDebug2C::EndSetDebugLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDebugLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDebug2C::SyncDebugLevel(TUint& aaDebugLevel)
{
    SyncDebugLevelLinnCoUkDebug2C sync(*this, aaDebugLevel);
    BeginDebugLevel(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDebug2C::BeginDebugLevel(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDebugLevel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDebugLevel->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDebug2C::EndDebugLevel(IAsync& aAsync, TUint& aaDebugLevel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DebugLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaDebugLevel = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkDebug2C::SyncMemWrite(TUint aaMemAddress, const Brx& aaMemData)
{
    SyncMemWriteLinnCoUkDebug2C sync(*this);
    BeginMemWrite(aaMemAddress, aaMemData, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDebug2C::BeginMemWrite(TUint aaMemAddress, const Brx& aaMemData, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionMemWrite, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionMemWrite->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaMemAddress));
    invocation->AddInput(new ArgumentBinary(*inParams[inIndex++], aaMemData));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDebug2C::EndMemWrite(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("MemWrite"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}


THandle CpProxyLinnCoUkDebug2Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkDebug2C(aDevice);
}

void CpProxyLinnCoUkDebug2Destroy(THandle aHandle)
{
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkDebug2SyncSetDebugLevel(THandle aHandle, uint32_t aaDebugLevel)
{
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetDebugLevel(aaDebugLevel);
}

void CpProxyLinnCoUkDebug2BeginSetDebugLevel(THandle aHandle, uint32_t aaDebugLevel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetDebugLevel(aaDebugLevel, functor);
}

int32_t CpProxyLinnCoUkDebug2EndSetDebugLevel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetDebugLevel(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDebug2SyncDebugLevel(THandle aHandle, uint32_t* aaDebugLevel)
{
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncDebugLevel(*aaDebugLevel);
}

void CpProxyLinnCoUkDebug2BeginDebugLevel(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDebugLevel(functor);
}

int32_t CpProxyLinnCoUkDebug2EndDebugLevel(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaDebugLevel)
{
    int32_t err = 0;
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndDebugLevel(*async, *aaDebugLevel);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDebug2SyncMemWrite(THandle aHandle, uint32_t aaMemAddress, const char* aaMemData, uint32_t aaMemDataLen)
{
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMemData;
    buf_aaMemData.Set((const TByte*)aaMemData, aaMemDataLen);
    proxyC->SyncMemWrite(aaMemAddress, buf_aaMemData);
}

void CpProxyLinnCoUkDebug2BeginMemWrite(THandle aHandle, uint32_t aaMemAddress, const char* aaMemData, uint32_t aaMemDataLen, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMemData;
    buf_aaMemData.Set((const TByte*)aaMemData, aaMemDataLen);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginMemWrite(aaMemAddress, buf_aaMemData, functor);
}

int32_t CpProxyLinnCoUkDebug2EndMemWrite(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndMemWrite(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

