#include <C/CpUpnpOrgRenderingControl2.h>
#include <Core/CpUpnpOrgRenderingControl2.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyUpnpOrgRenderingControl2C : public CpProxyC
{
public:
    CpProxyUpnpOrgRenderingControl2C(CpDeviceC aDevice);
    CpProxyUpnpOrgRenderingControl2* Proxy() { return static_cast<CpProxyUpnpOrgRenderingControl2*>(iProxy); }
};

CpProxyUpnpOrgRenderingControl2C::CpProxyUpnpOrgRenderingControl2C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyUpnpOrgRenderingControl2(*iDevice);
}


THandle CpProxyUpnpOrgRenderingControl2Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyUpnpOrgRenderingControl2C(aDevice);
}

void CpProxyUpnpOrgRenderingControl2Destroy(THandle aHandle)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgRenderingControl2SyncListPresets(THandle aHandle, uint32_t aInstanceID, char** aCurrentPresetNameList)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentPresetNameList;
    proxyC->Proxy()->SyncListPresets(aInstanceID, buf_aCurrentPresetNameList);
    *aCurrentPresetNameList = buf_aCurrentPresetNameList.Extract();
}

void CpProxyUpnpOrgRenderingControl2BeginListPresets(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginListPresets(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndListPresets(THandle aHandle, ZappHandleAsync aAsync, char** aCurrentPresetNameList)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aCurrentPresetNameList;
    *aCurrentPresetNameList = NULL;
    try {
        proxyC->Proxy()->EndListPresets(*async, buf_aCurrentPresetNameList);
        *aCurrentPresetNameList = buf_aCurrentPresetNameList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSelectPreset(THandle aHandle, uint32_t aInstanceID, const char* aPresetName)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aPresetName(aPresetName);
    proxyC->Proxy()->SyncSelectPreset(aInstanceID, buf_aPresetName);
}

void CpProxyUpnpOrgRenderingControl2BeginSelectPreset(THandle aHandle, uint32_t aInstanceID, const char* aPresetName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aPresetName(aPresetName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSelectPreset(aInstanceID, buf_aPresetName, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSelectPreset(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSelectPreset(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBrightness)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetBrightness(aInstanceID, *aCurrentBrightness);
}

void CpProxyUpnpOrgRenderingControl2BeginGetBrightness(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetBrightness(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetBrightness(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentBrightness)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetBrightness(*async, *aCurrentBrightness);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBrightness)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetBrightness(aInstanceID, aDesiredBrightness);
}

void CpProxyUpnpOrgRenderingControl2BeginSetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBrightness, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetBrightness(aInstanceID, aDesiredBrightness, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetBrightness(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetBrightness(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentContrast)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetContrast(aInstanceID, *aCurrentContrast);
}

void CpProxyUpnpOrgRenderingControl2BeginGetContrast(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetContrast(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetContrast(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentContrast)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetContrast(*async, *aCurrentContrast);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredContrast)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetContrast(aInstanceID, aDesiredContrast);
}

void CpProxyUpnpOrgRenderingControl2BeginSetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredContrast, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetContrast(aInstanceID, aDesiredContrast, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetContrast(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetContrast(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentSharpness)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetSharpness(aInstanceID, *aCurrentSharpness);
}

void CpProxyUpnpOrgRenderingControl2BeginGetSharpness(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSharpness(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetSharpness(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentSharpness)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetSharpness(*async, *aCurrentSharpness);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredSharpness)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetSharpness(aInstanceID, aDesiredSharpness);
}

void CpProxyUpnpOrgRenderingControl2BeginSetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredSharpness, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetSharpness(aInstanceID, aDesiredSharpness, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetSharpness(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetSharpness(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentRedVideoGain)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetRedVideoGain(aInstanceID, *aCurrentRedVideoGain);
}

void CpProxyUpnpOrgRenderingControl2BeginGetRedVideoGain(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRedVideoGain(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetRedVideoGain(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentRedVideoGain)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetRedVideoGain(*async, *aCurrentRedVideoGain);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetRedVideoGain(aInstanceID, aDesiredRedVideoGain);
}

void CpProxyUpnpOrgRenderingControl2BeginSetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetRedVideoGain(aInstanceID, aDesiredRedVideoGain, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetRedVideoGain(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetRedVideoGain(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoGain)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetGreenVideoGain(aInstanceID, *aCurrentGreenVideoGain);
}

void CpProxyUpnpOrgRenderingControl2BeginGetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetGreenVideoGain(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetGreenVideoGain(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentGreenVideoGain)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetGreenVideoGain(*async, *aCurrentGreenVideoGain);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain);
}

void CpProxyUpnpOrgRenderingControl2BeginSetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetGreenVideoGain(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetGreenVideoGain(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoGain)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetBlueVideoGain(aInstanceID, *aCurrentBlueVideoGain);
}

void CpProxyUpnpOrgRenderingControl2BeginGetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetBlueVideoGain(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetBlueVideoGain(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentBlueVideoGain)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetBlueVideoGain(*async, *aCurrentBlueVideoGain);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain);
}

void CpProxyUpnpOrgRenderingControl2BeginSetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetBlueVideoGain(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetBlueVideoGain(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentRedVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetRedVideoBlackLevel(aInstanceID, *aCurrentRedVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl2BeginGetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRedVideoBlackLevel(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetRedVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentRedVideoBlackLevel)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetRedVideoBlackLevel(*async, *aCurrentRedVideoBlackLevel);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl2BeginSetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetRedVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetRedVideoBlackLevel(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetGreenVideoBlackLevel(aInstanceID, *aCurrentGreenVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl2BeginGetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetGreenVideoBlackLevel(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetGreenVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentGreenVideoBlackLevel)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetGreenVideoBlackLevel(*async, *aCurrentGreenVideoBlackLevel);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl2BeginSetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetGreenVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetGreenVideoBlackLevel(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetBlueVideoBlackLevel(aInstanceID, *aCurrentBlueVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl2BeginGetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetBlueVideoBlackLevel(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetBlueVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentBlueVideoBlackLevel)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetBlueVideoBlackLevel(*async, *aCurrentBlueVideoBlackLevel);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl2BeginSetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetBlueVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetBlueVideoBlackLevel(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentColorTemperature)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetColorTemperature(aInstanceID, *aCurrentColorTemperature);
}

void CpProxyUpnpOrgRenderingControl2BeginGetColorTemperature(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetColorTemperature(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetColorTemperature(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentColorTemperature)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetColorTemperature(*async, *aCurrentColorTemperature);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredColorTemperature)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetColorTemperature(aInstanceID, aDesiredColorTemperature);
}

void CpProxyUpnpOrgRenderingControl2BeginSetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredColorTemperature, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetColorTemperature(aInstanceID, aDesiredColorTemperature, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetColorTemperature(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetColorTemperature(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t* aCurrentHorizontalKeystone)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetHorizontalKeystone(aInstanceID, *aCurrentHorizontalKeystone);
}

void CpProxyUpnpOrgRenderingControl2BeginGetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetHorizontalKeystone(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetHorizontalKeystone(THandle aHandle, ZappHandleAsync aAsync, int32_t* aCurrentHorizontalKeystone)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetHorizontalKeystone(*async, *aCurrentHorizontalKeystone);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone);
}

void CpProxyUpnpOrgRenderingControl2BeginSetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetHorizontalKeystone(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetHorizontalKeystone(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t* aCurrentVerticalKeystone)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetVerticalKeystone(aInstanceID, *aCurrentVerticalKeystone);
}

void CpProxyUpnpOrgRenderingControl2BeginGetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetVerticalKeystone(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetVerticalKeystone(THandle aHandle, ZappHandleAsync aAsync, int32_t* aCurrentVerticalKeystone)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetVerticalKeystone(*async, *aCurrentVerticalKeystone);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone);
}

void CpProxyUpnpOrgRenderingControl2BeginSetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetVerticalKeystone(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetVerticalKeystone(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentMute)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    *aCurrentMute = 0;
    proxyC->Proxy()->SyncGetMute(aInstanceID, buf_aChannel, *(TBool*)aCurrentMute);
}

void CpProxyUpnpOrgRenderingControl2BeginGetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetMute(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetMute(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentMute)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aCurrentMute = 0;
    try {
        proxyC->Proxy()->EndGetMute(*async, *(TBool*)aCurrentMute);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->Proxy()->SyncSetMute(aInstanceID, buf_aChannel, (aDesiredMute==0? false : true));
}

void CpProxyUpnpOrgRenderingControl2BeginSetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetMute(aInstanceID, buf_aChannel, (aDesiredMute==0? false : true), functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetMute(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetMute(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentVolume)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->Proxy()->SyncGetVolume(aInstanceID, buf_aChannel, *aCurrentVolume);
}

void CpProxyUpnpOrgRenderingControl2BeginGetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetVolume(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetVolume(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentVolume)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetVolume(*async, *aCurrentVolume);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->Proxy()->SyncSetVolume(aInstanceID, buf_aChannel, aDesiredVolume);
}

void CpProxyUpnpOrgRenderingControl2BeginSetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetVolume(aInstanceID, buf_aChannel, aDesiredVolume, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetVolume(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetVolume(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t* aCurrentVolume)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->Proxy()->SyncGetVolumeDB(aInstanceID, buf_aChannel, *aCurrentVolume);
}

void CpProxyUpnpOrgRenderingControl2BeginGetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetVolumeDB(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetVolumeDB(THandle aHandle, ZappHandleAsync aAsync, int32_t* aCurrentVolume)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetVolumeDB(*async, *aCurrentVolume);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->Proxy()->SyncSetVolumeDB(aInstanceID, buf_aChannel, aDesiredVolume);
}

void CpProxyUpnpOrgRenderingControl2BeginSetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetVolumeDB(aInstanceID, buf_aChannel, aDesiredVolume, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetVolumeDB(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetVolumeDB(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetVolumeDBRange(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t* aMinValue, int32_t* aMaxValue)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->Proxy()->SyncGetVolumeDBRange(aInstanceID, buf_aChannel, *aMinValue, *aMaxValue);
}

void CpProxyUpnpOrgRenderingControl2BeginGetVolumeDBRange(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetVolumeDBRange(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetVolumeDBRange(THandle aHandle, ZappHandleAsync aAsync, int32_t* aMinValue, int32_t* aMaxValue)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetVolumeDBRange(*async, *aMinValue, *aMaxValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentLoudness)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    *aCurrentLoudness = 0;
    proxyC->Proxy()->SyncGetLoudness(aInstanceID, buf_aChannel, *(TBool*)aCurrentLoudness);
}

void CpProxyUpnpOrgRenderingControl2BeginGetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetLoudness(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetLoudness(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentLoudness)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aCurrentLoudness = 0;
    try {
        proxyC->Proxy()->EndGetLoudness(*async, *(TBool*)aCurrentLoudness);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->Proxy()->SyncSetLoudness(aInstanceID, buf_aChannel, (aDesiredLoudness==0? false : true));
}

void CpProxyUpnpOrgRenderingControl2BeginSetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetLoudness(aInstanceID, buf_aChannel, (aDesiredLoudness==0? false : true), functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetLoudness(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetLoudness(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncGetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aStateVariableList, char** aStateVariableValuePairs)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aStateVariableList(aStateVariableList);
    Brh buf_aStateVariableValuePairs;
    proxyC->Proxy()->SyncGetStateVariables(aInstanceID, buf_aStateVariableList, buf_aStateVariableValuePairs);
    *aStateVariableValuePairs = buf_aStateVariableValuePairs.Extract();
}

void CpProxyUpnpOrgRenderingControl2BeginGetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aStateVariableList, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aStateVariableList(aStateVariableList);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetStateVariables(aInstanceID, buf_aStateVariableList, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndGetStateVariables(THandle aHandle, ZappHandleAsync aAsync, char** aStateVariableValuePairs)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aStateVariableValuePairs;
    *aStateVariableValuePairs = NULL;
    try {
        proxyC->Proxy()->EndGetStateVariables(*async, buf_aStateVariableValuePairs);
        *aStateVariableValuePairs = buf_aStateVariableValuePairs.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SyncSetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aRenderingControlUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, char** aStateVariableList)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRenderingControlUDN(aRenderingControlUDN);
    Brh buf_aServiceType(aServiceType);
    Brh buf_aServiceId(aServiceId);
    Brh buf_aStateVariableValuePairs(aStateVariableValuePairs);
    Brh buf_aStateVariableList;
    proxyC->Proxy()->SyncSetStateVariables(aInstanceID, buf_aRenderingControlUDN, buf_aServiceType, buf_aServiceId, buf_aStateVariableValuePairs, buf_aStateVariableList);
    *aStateVariableList = buf_aStateVariableList.Extract();
}

void CpProxyUpnpOrgRenderingControl2BeginSetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aRenderingControlUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRenderingControlUDN(aRenderingControlUDN);
    Brh buf_aServiceType(aServiceType);
    Brh buf_aServiceId(aServiceId);
    Brh buf_aStateVariableValuePairs(aStateVariableValuePairs);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetStateVariables(aInstanceID, buf_aRenderingControlUDN, buf_aServiceType, buf_aServiceId, buf_aStateVariableValuePairs, functor);
}

int32_t CpProxyUpnpOrgRenderingControl2EndSetStateVariables(THandle aHandle, ZappHandleAsync aAsync, char** aStateVariableList)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aStateVariableList;
    *aStateVariableList = NULL;
    try {
        proxyC->Proxy()->EndSetStateVariables(*async, buf_aStateVariableList);
        *aStateVariableList = buf_aStateVariableList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgRenderingControl2SetPropertyLastChangeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyLastChangeChanged(functor);
}

void CpProxyUpnpOrgRenderingControl2PropertyLastChange(THandle aHandle, char** aLastChange)
{
    CpProxyUpnpOrgRenderingControl2C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aLastChange;
    proxyC->Proxy()->PropertyLastChange(buf_aLastChange);
    *aLastChange = buf_aLastChange.Transfer();
}

