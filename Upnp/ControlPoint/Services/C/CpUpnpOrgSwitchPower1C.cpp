#include <C/CpUpnpOrgSwitchPower1.h>
#include <Core/CpUpnpOrgSwitchPower1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyUpnpOrgSwitchPower1C : public CpProxyC
{
public:
    CpProxyUpnpOrgSwitchPower1C(CpDeviceC aDevice);
    CpProxyUpnpOrgSwitchPower1* Proxy() { return static_cast<CpProxyUpnpOrgSwitchPower1*>(iProxy); }
};

CpProxyUpnpOrgSwitchPower1C::CpProxyUpnpOrgSwitchPower1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyUpnpOrgSwitchPower1(*iDevice);
}


THandle CpProxyUpnpOrgSwitchPower1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyUpnpOrgSwitchPower1C(aDevice);
}

void CpProxyUpnpOrgSwitchPower1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgSwitchPower1SyncSetTarget(THandle aHandle, uint32_t anewTargetValue)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetTarget((anewTargetValue==0? false : true));
}

void CpProxyUpnpOrgSwitchPower1BeginSetTarget(THandle aHandle, uint32_t anewTargetValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetTarget((anewTargetValue==0? false : true), functor);
}

int32_t CpProxyUpnpOrgSwitchPower1EndSetTarget(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetTarget(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgSwitchPower1SyncGetTarget(THandle aHandle, uint32_t* aRetTargetValue)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aRetTargetValue = 0;
    proxyC->Proxy()->SyncGetTarget(*(TBool*)aRetTargetValue);
}

void CpProxyUpnpOrgSwitchPower1BeginGetTarget(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetTarget(functor);
}

int32_t CpProxyUpnpOrgSwitchPower1EndGetTarget(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aRetTargetValue)
{
    int32_t err = 0;
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aRetTargetValue = 0;
    try {
        proxyC->Proxy()->EndGetTarget(*async, *(TBool*)aRetTargetValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgSwitchPower1SyncGetStatus(THandle aHandle, uint32_t* aResultStatus)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aResultStatus = 0;
    proxyC->Proxy()->SyncGetStatus(*(TBool*)aResultStatus);
}

void CpProxyUpnpOrgSwitchPower1BeginGetStatus(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetStatus(functor);
}

int32_t CpProxyUpnpOrgSwitchPower1EndGetStatus(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aResultStatus)
{
    int32_t err = 0;
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aResultStatus = 0;
    try {
        proxyC->Proxy()->EndGetStatus(*async, *(TBool*)aResultStatus);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgSwitchPower1SetPropertyStatusChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyStatusChanged(functor);
}

void CpProxyUpnpOrgSwitchPower1PropertyStatus(THandle aHandle, uint32_t* aStatus)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aStatus = false;
    proxyC->Proxy()->PropertyStatus(*(TBool*)aStatus);
}

