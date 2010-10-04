#include <C/CpLinnCoUkPtest1.h>
#include <Core/CpLinnCoUkPtest1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkPtest1C : public CpProxyC
{
public:
    CpProxyLinnCoUkPtest1C(CpDeviceC aDevice);
    CpProxyLinnCoUkPtest1* Proxy() { return static_cast<CpProxyLinnCoUkPtest1*>(iProxy); }
};

CpProxyLinnCoUkPtest1C::CpProxyLinnCoUkPtest1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkPtest1(*iDevice);
}


THandle CpProxyLinnCoUkPtest1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkPtest1C(aDevice);
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
    proxyC->Proxy()->SyncTestComPort(aaPort, *(TBool*)aaResult);
}

void CpProxyLinnCoUkPtest1BeginTestComPort(THandle aHandle, uint32_t aaPort, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginTestComPort(aaPort, functor);
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
        proxyC->Proxy()->EndTestComPort(*async, *(TBool*)aaResult);
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
    proxyC->Proxy()->SyncLedsOn();
}

void CpProxyLinnCoUkPtest1BeginLedsOn(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginLedsOn(functor);
}

int32_t CpProxyLinnCoUkPtest1EndLedsOn(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndLedsOn(*async);
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
    proxyC->Proxy()->SyncLedsOff();
}

void CpProxyLinnCoUkPtest1BeginLedsOff(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginLedsOff(functor);
}

int32_t CpProxyLinnCoUkPtest1EndLedsOff(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPtest1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPtest1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndLedsOff(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

