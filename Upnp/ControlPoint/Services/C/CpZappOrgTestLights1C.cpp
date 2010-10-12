#include <C/CpZappOrgTestLights1.h>
#include <Core/CpZappOrgTestLights1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyZappOrgTestLights1C : public CpProxyC
{
public:
    CpProxyZappOrgTestLights1C(CpDeviceC aDevice);
    CpProxyZappOrgTestLights1* Proxy() { return static_cast<CpProxyZappOrgTestLights1*>(iProxy); }
};

CpProxyZappOrgTestLights1C::CpProxyZappOrgTestLights1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyZappOrgTestLights1(*iDevice);
}


THandle CpProxyZappOrgTestLights1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyZappOrgTestLights1C(aDevice);
}

void CpProxyZappOrgTestLights1Destroy(THandle aHandle)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    delete proxyC;
}

void CpProxyZappOrgTestLights1SyncGetCount(THandle aHandle, uint32_t* aCount)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetCount(*aCount);
}

void CpProxyZappOrgTestLights1BeginGetCount(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetCount(functor);
}

int32_t CpProxyZappOrgTestLights1EndGetCount(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCount)
{
    int32_t err = 0;
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetCount(*async, *aCount);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestLights1SyncGetRoom(THandle aHandle, uint32_t aIndex, char** aRoomName)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRoomName;
    proxyC->Proxy()->SyncGetRoom(aIndex, buf_aRoomName);
    *aRoomName = buf_aRoomName.Extract();
}

void CpProxyZappOrgTestLights1BeginGetRoom(THandle aHandle, uint32_t aIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRoom(aIndex, functor);
}

int32_t CpProxyZappOrgTestLights1EndGetRoom(THandle aHandle, ZappHandleAsync aAsync, char** aRoomName)
{
    int32_t err = 0;
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aRoomName;
    *aRoomName = NULL;
    try {
        proxyC->Proxy()->EndGetRoom(*async, buf_aRoomName);
        *aRoomName = buf_aRoomName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestLights1SyncGetName(THandle aHandle, uint32_t aIndex, char** aFriendlyName)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFriendlyName;
    proxyC->Proxy()->SyncGetName(aIndex, buf_aFriendlyName);
    *aFriendlyName = buf_aFriendlyName.Extract();
}

void CpProxyZappOrgTestLights1BeginGetName(THandle aHandle, uint32_t aIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetName(aIndex, functor);
}

int32_t CpProxyZappOrgTestLights1EndGetName(THandle aHandle, ZappHandleAsync aAsync, char** aFriendlyName)
{
    int32_t err = 0;
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
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

void CpProxyZappOrgTestLights1SyncGetPosition(THandle aHandle, uint32_t aIndex, uint32_t* aX, uint32_t* aY, uint32_t* aZ)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetPosition(aIndex, *aX, *aY, *aZ);
}

void CpProxyZappOrgTestLights1BeginGetPosition(THandle aHandle, uint32_t aIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetPosition(aIndex, functor);
}

int32_t CpProxyZappOrgTestLights1EndGetPosition(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aX, uint32_t* aY, uint32_t* aZ)
{
    int32_t err = 0;
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetPosition(*async, *aX, *aY, *aZ);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestLights1SyncSetColor(THandle aHandle, uint32_t aIndex, uint32_t aColor)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetColor(aIndex, aColor);
}

void CpProxyZappOrgTestLights1BeginSetColor(THandle aHandle, uint32_t aIndex, uint32_t aColor, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetColor(aIndex, aColor, functor);
}

int32_t CpProxyZappOrgTestLights1EndSetColor(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
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

void CpProxyZappOrgTestLights1SyncGetColor(THandle aHandle, uint32_t aIndex, uint32_t* aColor)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetColor(aIndex, *aColor);
}

void CpProxyZappOrgTestLights1BeginGetColor(THandle aHandle, uint32_t aIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetColor(aIndex, functor);
}

int32_t CpProxyZappOrgTestLights1EndGetColor(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aColor)
{
    int32_t err = 0;
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetColor(*async, *aColor);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestLights1SyncGetColorComponents(THandle aHandle, uint32_t aColor, uint32_t* aBrightness, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetColorComponents(aColor, *aBrightness, *aRed, *aGreen, *aBlue);
}

void CpProxyZappOrgTestLights1BeginGetColorComponents(THandle aHandle, uint32_t aColor, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetColorComponents(aColor, functor);
}

int32_t CpProxyZappOrgTestLights1EndGetColorComponents(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aBrightness, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue)
{
    int32_t err = 0;
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetColorComponents(*async, *aBrightness, *aRed, *aGreen, *aBlue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

