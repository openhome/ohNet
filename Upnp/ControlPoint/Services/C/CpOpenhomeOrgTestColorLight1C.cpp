#include <C/CpOpenhomeOrgTestColorLight1.h>
#include <Core/CpOpenhomeOrgTestColorLight1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyOpenhomeOrgTestColorLight1C : public CpProxyC
{
public:
    CpProxyOpenhomeOrgTestColorLight1C(CpDeviceC aDevice);
    CpProxyOpenhomeOrgTestColorLight1* Proxy() { return static_cast<CpProxyOpenhomeOrgTestColorLight1*>(iProxy); }
};

CpProxyOpenhomeOrgTestColorLight1C::CpProxyOpenhomeOrgTestColorLight1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyOpenhomeOrgTestColorLight1(*iDevice);
}


THandle CpProxyOpenhomeOrgTestColorLight1Create(CpDeviceC aDevice)
{
    return new CpProxyOpenhomeOrgTestColorLight1C(aDevice);
}

void CpProxyOpenhomeOrgTestColorLight1Destroy(THandle aHandle)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    delete proxyC;
}

void CpProxyOpenhomeOrgTestColorLight1SyncGetName(THandle aHandle, char** aFriendlyName)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFriendlyName;
    proxyC->Proxy()->SyncGetName(buf_aFriendlyName);
    *aFriendlyName = buf_aFriendlyName.Extract();
}

void CpProxyOpenhomeOrgTestColorLight1BeginGetName(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetName(functor);
}

int32_t CpProxyOpenhomeOrgTestColorLight1EndGetName(THandle aHandle, ZappHandleAsync aAsync, char** aFriendlyName)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aFriendlyName;
    *aFriendlyName = NULL;
    try {
        proxyC->Proxy()->EndGetName(*async, buf_aFriendlyName);
        *aFriendlyName = buf_aFriendlyName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyOpenhomeOrgTestColorLight1SyncSetColor(THandle aHandle, uint32_t aRed, uint32_t aGreen, uint32_t aBlue)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetColor(aRed, aGreen, aBlue);
}

void CpProxyOpenhomeOrgTestColorLight1BeginSetColor(THandle aHandle, uint32_t aRed, uint32_t aGreen, uint32_t aBlue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetColor(aRed, aGreen, aBlue, functor);
}

int32_t CpProxyOpenhomeOrgTestColorLight1EndSetColor(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetColor(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyOpenhomeOrgTestColorLight1SyncGetColor(THandle aHandle, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetColor(*aRed, *aGreen, *aBlue);
}

void CpProxyOpenhomeOrgTestColorLight1BeginGetColor(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetColor(functor);
}

int32_t CpProxyOpenhomeOrgTestColorLight1EndGetColor(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetColor(*async, *aRed, *aGreen, *aBlue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyOpenhomeOrgTestColorLight1SyncGetMaxColors(THandle aHandle, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetMaxColors(*aRed, *aGreen, *aBlue);
}

void CpProxyOpenhomeOrgTestColorLight1BeginGetMaxColors(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetMaxColors(functor);
}

int32_t CpProxyOpenhomeOrgTestColorLight1EndGetMaxColors(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetMaxColors(*async, *aRed, *aGreen, *aBlue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

