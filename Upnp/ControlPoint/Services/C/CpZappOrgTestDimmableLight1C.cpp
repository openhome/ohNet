#include <C/CpZappOrgTestDimmableLight1.h>
#include <Core/CpZappOrgTestDimmableLight1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyZappOrgTestDimmableLight1C : public CpProxyC
{
public:
    CpProxyZappOrgTestDimmableLight1C(CpDeviceC aDevice);
    CpProxyZappOrgTestDimmableLight1* Proxy() { return static_cast<CpProxyZappOrgTestDimmableLight1*>(iProxy); }
};

CpProxyZappOrgTestDimmableLight1C::CpProxyZappOrgTestDimmableLight1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyZappOrgTestDimmableLight1(*iDevice);
}


THandle CpProxyZappOrgTestDimmableLight1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyZappOrgTestDimmableLight1C(aDevice);
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
    proxyC->Proxy()->SyncGetLevel(*aLevel);
}

void CpProxyZappOrgTestDimmableLight1BeginGetLevel(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyZappOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetLevel(functor);
}

int32_t CpProxyZappOrgTestDimmableLight1EndGetLevel(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aLevel)
{
    int32_t err = 0;
    CpProxyZappOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyZappOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetLevel(*async, *aLevel);
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
    proxyC->Proxy()->SyncSetLevel(aLevel);
}

void CpProxyZappOrgTestDimmableLight1BeginSetLevel(THandle aHandle, uint32_t aLevel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyZappOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetLevel(aLevel, functor);
}

int32_t CpProxyZappOrgTestDimmableLight1EndSetLevel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyZappOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetLevel(*async);
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
    proxyC->Proxy()->SetPropertyA_ARG_LevelChanged(functor);
}

void CpProxyZappOrgTestDimmableLight1PropertyA_ARG_Level(THandle aHandle, uint32_t* aA_ARG_Level)
{
    CpProxyZappOrgTestDimmableLight1C* proxyC = reinterpret_cast<CpProxyZappOrgTestDimmableLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyA_ARG_Level(*aA_ARG_Level);
}

