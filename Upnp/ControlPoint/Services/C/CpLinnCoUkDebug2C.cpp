#include <C/CpLinnCoUkDebug2.h>
#include <Core/CpLinnCoUkDebug2.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkDebug2C : public CpProxyC
{
public:
    CpProxyLinnCoUkDebug2C(CpDeviceC aDevice);
    CpProxyLinnCoUkDebug2* Proxy() { return static_cast<CpProxyLinnCoUkDebug2*>(iProxy); }
};

CpProxyLinnCoUkDebug2C::CpProxyLinnCoUkDebug2C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkDebug2(*iDevice);
}


THandle CpProxyLinnCoUkDebug2Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkDebug2C(aDevice);
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
    proxyC->Proxy()->SyncSetDebugLevel(aaDebugLevel);
}

void CpProxyLinnCoUkDebug2BeginSetDebugLevel(THandle aHandle, uint32_t aaDebugLevel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetDebugLevel(aaDebugLevel, functor);
}

int32_t CpProxyLinnCoUkDebug2EndSetDebugLevel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetDebugLevel(*async);
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
    proxyC->Proxy()->SyncDebugLevel(*aaDebugLevel);
}

void CpProxyLinnCoUkDebug2BeginDebugLevel(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDebugLevel(functor);
}

int32_t CpProxyLinnCoUkDebug2EndDebugLevel(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaDebugLevel)
{
    int32_t err = 0;
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDebugLevel(*async, *aaDebugLevel);
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
    proxyC->Proxy()->SyncMemWrite(aaMemAddress, buf_aaMemData);
}

void CpProxyLinnCoUkDebug2BeginMemWrite(THandle aHandle, uint32_t aaMemAddress, const char* aaMemData, uint32_t aaMemDataLen, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMemData;
    buf_aaMemData.Set((const TByte*)aaMemData, aaMemDataLen);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginMemWrite(aaMemAddress, buf_aaMemData, functor);
}

int32_t CpProxyLinnCoUkDebug2EndMemWrite(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDebug2C* proxyC = reinterpret_cast<CpProxyLinnCoUkDebug2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndMemWrite(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

