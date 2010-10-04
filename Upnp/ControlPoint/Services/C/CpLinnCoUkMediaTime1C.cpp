#include <C/CpLinnCoUkMediaTime1.h>
#include <Core/CpLinnCoUkMediaTime1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkMediaTime1C : public CpProxyC
{
public:
    CpProxyLinnCoUkMediaTime1C(CpDeviceC aDevice);
    CpProxyLinnCoUkMediaTime1* Proxy() { return static_cast<CpProxyLinnCoUkMediaTime1*>(iProxy); }
};

CpProxyLinnCoUkMediaTime1C::CpProxyLinnCoUkMediaTime1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkMediaTime1(*iDevice);
}


THandle CpProxyLinnCoUkMediaTime1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkMediaTime1C(aDevice);
}

void CpProxyLinnCoUkMediaTime1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkMediaTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkMediaTime1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkMediaTime1SyncSeconds(THandle aHandle, uint32_t* aaSeconds)
{
    CpProxyLinnCoUkMediaTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkMediaTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSeconds(*aaSeconds);
}

void CpProxyLinnCoUkMediaTime1BeginSeconds(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkMediaTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkMediaTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSeconds(functor);
}

int32_t CpProxyLinnCoUkMediaTime1EndSeconds(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSeconds)
{
    int32_t err = 0;
    CpProxyLinnCoUkMediaTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkMediaTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSeconds(*async, *aaSeconds);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkMediaTime1SetPropertySecondsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkMediaTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkMediaTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertySecondsChanged(functor);
}

void CpProxyLinnCoUkMediaTime1PropertySeconds(THandle aHandle, uint32_t* aSeconds)
{
    CpProxyLinnCoUkMediaTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkMediaTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertySeconds(*aSeconds);
}

