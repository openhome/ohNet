#include <C/CpLinnCoUkTime1.h>
#include <Core/CpLinnCoUkTime1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkTime1C : public CpProxyC
{
public:
    CpProxyLinnCoUkTime1C(CpDeviceC aDevice);
    CpProxyLinnCoUkTime1* Proxy() { return static_cast<CpProxyLinnCoUkTime1*>(iProxy); }
};

CpProxyLinnCoUkTime1C::CpProxyLinnCoUkTime1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkTime1(*iDevice);
}


THandle CpProxyLinnCoUkTime1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkTime1C(aDevice);
}

void CpProxyLinnCoUkTime1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkTime1SyncTime(THandle aHandle, uint32_t* aaTrackCount, uint32_t* aaDuration, uint32_t* aaSeconds)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncTime(*aaTrackCount, *aaDuration, *aaSeconds);
}

void CpProxyLinnCoUkTime1BeginTime(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginTime(functor);
}

int32_t CpProxyLinnCoUkTime1EndTime(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaTrackCount, uint32_t* aaDuration, uint32_t* aaSeconds)
{
    int32_t err = 0;
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndTime(*async, *aaTrackCount, *aaDuration, *aaSeconds);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkTime1SetPropertyTrackCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTrackCountChanged(functor);
}

void CpProxyLinnCoUkTime1SetPropertyDurationChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyDurationChanged(functor);
}

void CpProxyLinnCoUkTime1SetPropertySecondsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertySecondsChanged(functor);
}

void CpProxyLinnCoUkTime1PropertyTrackCount(THandle aHandle, uint32_t* aTrackCount)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyTrackCount(*aTrackCount);
}

void CpProxyLinnCoUkTime1PropertyDuration(THandle aHandle, uint32_t* aDuration)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyDuration(*aDuration);
}

void CpProxyLinnCoUkTime1PropertySeconds(THandle aHandle, uint32_t* aSeconds)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertySeconds(*aSeconds);
}

