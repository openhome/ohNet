#include <C/CpUpnpOrgRenderingControl1.h>
#include <Core/CpUpnpOrgRenderingControl1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyUpnpOrgRenderingControl1C : public CpProxyC
{
public:
    CpProxyUpnpOrgRenderingControl1C(CpDeviceC aDevice);
    CpProxyUpnpOrgRenderingControl1* Proxy() { return static_cast<CpProxyUpnpOrgRenderingControl1*>(iProxy); }
};

CpProxyUpnpOrgRenderingControl1C::CpProxyUpnpOrgRenderingControl1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyUpnpOrgRenderingControl1(*iDevice);
}


THandle CpProxyUpnpOrgRenderingControl1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyUpnpOrgRenderingControl1C(aDevice);
}

void CpProxyUpnpOrgRenderingControl1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgRenderingControl1SyncListPresets(THandle aHandle, uint32_t aInstanceID, char** aCurrentPresetNameList)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentPresetNameList;
    proxyC->Proxy()->SyncListPresets(aInstanceID, buf_aCurrentPresetNameList);
    *aCurrentPresetNameList = buf_aCurrentPresetNameList.Extract();
}

void CpProxyUpnpOrgRenderingControl1BeginListPresets(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginListPresets(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndListPresets(THandle aHandle, ZappHandleAsync aAsync, char** aCurrentPresetNameList)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSelectPreset(THandle aHandle, uint32_t aInstanceID, const char* aPresetName)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aPresetName(aPresetName);
    proxyC->Proxy()->SyncSelectPreset(aInstanceID, buf_aPresetName);
}

void CpProxyUpnpOrgRenderingControl1BeginSelectPreset(THandle aHandle, uint32_t aInstanceID, const char* aPresetName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aPresetName(aPresetName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSelectPreset(aInstanceID, buf_aPresetName, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSelectPreset(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBrightness)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetBrightness(aInstanceID, *aCurrentBrightness);
}

void CpProxyUpnpOrgRenderingControl1BeginGetBrightness(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetBrightness(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetBrightness(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentBrightness)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBrightness)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetBrightness(aInstanceID, aDesiredBrightness);
}

void CpProxyUpnpOrgRenderingControl1BeginSetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBrightness, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetBrightness(aInstanceID, aDesiredBrightness, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetBrightness(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentContrast)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetContrast(aInstanceID, *aCurrentContrast);
}

void CpProxyUpnpOrgRenderingControl1BeginGetContrast(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetContrast(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetContrast(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentContrast)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredContrast)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetContrast(aInstanceID, aDesiredContrast);
}

void CpProxyUpnpOrgRenderingControl1BeginSetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredContrast, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetContrast(aInstanceID, aDesiredContrast, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetContrast(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentSharpness)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetSharpness(aInstanceID, *aCurrentSharpness);
}

void CpProxyUpnpOrgRenderingControl1BeginGetSharpness(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSharpness(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetSharpness(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentSharpness)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredSharpness)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetSharpness(aInstanceID, aDesiredSharpness);
}

void CpProxyUpnpOrgRenderingControl1BeginSetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredSharpness, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetSharpness(aInstanceID, aDesiredSharpness, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetSharpness(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentRedVideoGain)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetRedVideoGain(aInstanceID, *aCurrentRedVideoGain);
}

void CpProxyUpnpOrgRenderingControl1BeginGetRedVideoGain(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRedVideoGain(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetRedVideoGain(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentRedVideoGain)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetRedVideoGain(aInstanceID, aDesiredRedVideoGain);
}

void CpProxyUpnpOrgRenderingControl1BeginSetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetRedVideoGain(aInstanceID, aDesiredRedVideoGain, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetRedVideoGain(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoGain)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetGreenVideoGain(aInstanceID, *aCurrentGreenVideoGain);
}

void CpProxyUpnpOrgRenderingControl1BeginGetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetGreenVideoGain(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetGreenVideoGain(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentGreenVideoGain)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain);
}

void CpProxyUpnpOrgRenderingControl1BeginSetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetGreenVideoGain(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoGain)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetBlueVideoGain(aInstanceID, *aCurrentBlueVideoGain);
}

void CpProxyUpnpOrgRenderingControl1BeginGetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetBlueVideoGain(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetBlueVideoGain(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentBlueVideoGain)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain);
}

void CpProxyUpnpOrgRenderingControl1BeginSetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetBlueVideoGain(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentRedVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetRedVideoBlackLevel(aInstanceID, *aCurrentRedVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl1BeginGetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRedVideoBlackLevel(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetRedVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentRedVideoBlackLevel)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl1BeginSetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetRedVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetGreenVideoBlackLevel(aInstanceID, *aCurrentGreenVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl1BeginGetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetGreenVideoBlackLevel(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetGreenVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentGreenVideoBlackLevel)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl1BeginSetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetGreenVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetBlueVideoBlackLevel(aInstanceID, *aCurrentBlueVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl1BeginGetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetBlueVideoBlackLevel(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetBlueVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentBlueVideoBlackLevel)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel);
}

void CpProxyUpnpOrgRenderingControl1BeginSetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetBlueVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentColorTemperature)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetColorTemperature(aInstanceID, *aCurrentColorTemperature);
}

void CpProxyUpnpOrgRenderingControl1BeginGetColorTemperature(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetColorTemperature(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetColorTemperature(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentColorTemperature)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredColorTemperature)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetColorTemperature(aInstanceID, aDesiredColorTemperature);
}

void CpProxyUpnpOrgRenderingControl1BeginSetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredColorTemperature, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetColorTemperature(aInstanceID, aDesiredColorTemperature, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetColorTemperature(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t* aCurrentHorizontalKeystone)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetHorizontalKeystone(aInstanceID, *aCurrentHorizontalKeystone);
}

void CpProxyUpnpOrgRenderingControl1BeginGetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetHorizontalKeystone(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetHorizontalKeystone(THandle aHandle, ZappHandleAsync aAsync, int32_t* aCurrentHorizontalKeystone)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone);
}

void CpProxyUpnpOrgRenderingControl1BeginSetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetHorizontalKeystone(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t* aCurrentVerticalKeystone)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetVerticalKeystone(aInstanceID, *aCurrentVerticalKeystone);
}

void CpProxyUpnpOrgRenderingControl1BeginGetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetVerticalKeystone(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetVerticalKeystone(THandle aHandle, ZappHandleAsync aAsync, int32_t* aCurrentVerticalKeystone)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone);
}

void CpProxyUpnpOrgRenderingControl1BeginSetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetVerticalKeystone(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentMute)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    *aCurrentMute = 0;
    proxyC->Proxy()->SyncGetMute(aInstanceID, buf_aChannel, *(TBool*)aCurrentMute);
}

void CpProxyUpnpOrgRenderingControl1BeginGetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetMute(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetMute(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentMute)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->Proxy()->SyncSetMute(aInstanceID, buf_aChannel, (aDesiredMute==0? false : true));
}

void CpProxyUpnpOrgRenderingControl1BeginSetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetMute(aInstanceID, buf_aChannel, (aDesiredMute==0? false : true), functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetMute(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentVolume)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->Proxy()->SyncGetVolume(aInstanceID, buf_aChannel, *aCurrentVolume);
}

void CpProxyUpnpOrgRenderingControl1BeginGetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetVolume(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetVolume(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentVolume)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->Proxy()->SyncSetVolume(aInstanceID, buf_aChannel, aDesiredVolume);
}

void CpProxyUpnpOrgRenderingControl1BeginSetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetVolume(aInstanceID, buf_aChannel, aDesiredVolume, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetVolume(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t* aCurrentVolume)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->Proxy()->SyncGetVolumeDB(aInstanceID, buf_aChannel, *aCurrentVolume);
}

void CpProxyUpnpOrgRenderingControl1BeginGetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetVolumeDB(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetVolumeDB(THandle aHandle, ZappHandleAsync aAsync, int32_t* aCurrentVolume)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->Proxy()->SyncSetVolumeDB(aInstanceID, buf_aChannel, aDesiredVolume);
}

void CpProxyUpnpOrgRenderingControl1BeginSetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetVolumeDB(aInstanceID, buf_aChannel, aDesiredVolume, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetVolumeDB(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetVolumeDBRange(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t* aMinValue, int32_t* aMaxValue)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->Proxy()->SyncGetVolumeDBRange(aInstanceID, buf_aChannel, *aMinValue, *aMaxValue);
}

void CpProxyUpnpOrgRenderingControl1BeginGetVolumeDBRange(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetVolumeDBRange(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetVolumeDBRange(THandle aHandle, ZappHandleAsync aAsync, int32_t* aMinValue, int32_t* aMaxValue)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncGetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentLoudness)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    *aCurrentLoudness = 0;
    proxyC->Proxy()->SyncGetLoudness(aInstanceID, buf_aChannel, *(TBool*)aCurrentLoudness);
}

void CpProxyUpnpOrgRenderingControl1BeginGetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetLoudness(aInstanceID, buf_aChannel, functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndGetLoudness(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentLoudness)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SyncSetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    proxyC->Proxy()->SyncSetLoudness(aInstanceID, buf_aChannel, (aDesiredLoudness==0? false : true));
}

void CpProxyUpnpOrgRenderingControl1BeginSetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aChannel(aChannel);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetLoudness(aInstanceID, buf_aChannel, (aDesiredLoudness==0? false : true), functor);
}

int32_t CpProxyUpnpOrgRenderingControl1EndSetLoudness(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
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

void CpProxyUpnpOrgRenderingControl1SetPropertyLastChangeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyLastChangeChanged(functor);
}

void CpProxyUpnpOrgRenderingControl1PropertyLastChange(THandle aHandle, char** aLastChange)
{
    CpProxyUpnpOrgRenderingControl1C* proxyC = reinterpret_cast<CpProxyUpnpOrgRenderingControl1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aLastChange;
    proxyC->Proxy()->PropertyLastChange(buf_aLastChange);
    *aLastChange = buf_aLastChange.Transfer();
}

