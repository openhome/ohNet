#include <C/CpUpnpOrgDimming1.h>
#include <Core/CpUpnpOrgDimming1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyUpnpOrgDimming1C : public CpProxyC
{
public:
    CpProxyUpnpOrgDimming1C(CpDeviceC aDevice);
    CpProxyUpnpOrgDimming1* Proxy() { return static_cast<CpProxyUpnpOrgDimming1*>(iProxy); }
};

CpProxyUpnpOrgDimming1C::CpProxyUpnpOrgDimming1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyUpnpOrgDimming1(*iDevice);
}


THandle CpProxyUpnpOrgDimming1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyUpnpOrgDimming1C(aDevice);
}

void CpProxyUpnpOrgDimming1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgDimming1SyncSetLoadLevelTarget(THandle aHandle, uint32_t anewLoadlevelTarget)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetLoadLevelTarget(anewLoadlevelTarget);
}

void CpProxyUpnpOrgDimming1BeginSetLoadLevelTarget(THandle aHandle, uint32_t anewLoadlevelTarget, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetLoadLevelTarget(anewLoadlevelTarget, functor);
}

int32_t CpProxyUpnpOrgDimming1EndSetLoadLevelTarget(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetLoadLevelTarget(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetLoadLevelTarget(THandle aHandle, uint32_t* aGetLoadlevelTarget)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetLoadLevelTarget(*aGetLoadlevelTarget);
}

void CpProxyUpnpOrgDimming1BeginGetLoadLevelTarget(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetLoadLevelTarget(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetLoadLevelTarget(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aGetLoadlevelTarget)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetLoadLevelTarget(*async, *aGetLoadlevelTarget);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetLoadLevelStatus(THandle aHandle, uint32_t* aretLoadlevelStatus)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetLoadLevelStatus(*aretLoadlevelStatus);
}

void CpProxyUpnpOrgDimming1BeginGetLoadLevelStatus(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetLoadLevelStatus(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetLoadLevelStatus(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aretLoadlevelStatus)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetLoadLevelStatus(*async, *aretLoadlevelStatus);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncSetOnEffectLevel(THandle aHandle, uint32_t anewOnEffectLevel)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetOnEffectLevel(anewOnEffectLevel);
}

void CpProxyUpnpOrgDimming1BeginSetOnEffectLevel(THandle aHandle, uint32_t anewOnEffectLevel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetOnEffectLevel(anewOnEffectLevel, functor);
}

int32_t CpProxyUpnpOrgDimming1EndSetOnEffectLevel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetOnEffectLevel(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncSetOnEffect(THandle aHandle, const char* anewOnEffect)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_anewOnEffect(anewOnEffect);
    proxyC->Proxy()->SyncSetOnEffect(buf_anewOnEffect);
}

void CpProxyUpnpOrgDimming1BeginSetOnEffect(THandle aHandle, const char* anewOnEffect, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_anewOnEffect(anewOnEffect);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetOnEffect(buf_anewOnEffect, functor);
}

int32_t CpProxyUpnpOrgDimming1EndSetOnEffect(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetOnEffect(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetOnEffectParameters(THandle aHandle, char** aretOnEffect, uint32_t* aretOnEffectLevel)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aretOnEffect;
    proxyC->Proxy()->SyncGetOnEffectParameters(buf_aretOnEffect, *aretOnEffectLevel);
    *aretOnEffect = buf_aretOnEffect.Extract();
}

void CpProxyUpnpOrgDimming1BeginGetOnEffectParameters(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetOnEffectParameters(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetOnEffectParameters(THandle aHandle, ZappHandleAsync aAsync, char** aretOnEffect, uint32_t* aretOnEffectLevel)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aretOnEffect;
    *aretOnEffect = NULL;
    try {
        proxyC->Proxy()->EndGetOnEffectParameters(*async, buf_aretOnEffect, *aretOnEffectLevel);
        *aretOnEffect = buf_aretOnEffect.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncStepUp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStepUp();
}

void CpProxyUpnpOrgDimming1BeginStepUp(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStepUp(functor);
}

int32_t CpProxyUpnpOrgDimming1EndStepUp(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndStepUp(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncStepDown(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStepDown();
}

void CpProxyUpnpOrgDimming1BeginStepDown(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStepDown(functor);
}

int32_t CpProxyUpnpOrgDimming1EndStepDown(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndStepDown(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncStartRampUp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStartRampUp();
}

void CpProxyUpnpOrgDimming1BeginStartRampUp(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStartRampUp(functor);
}

int32_t CpProxyUpnpOrgDimming1EndStartRampUp(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndStartRampUp(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncStartRampDown(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStartRampDown();
}

void CpProxyUpnpOrgDimming1BeginStartRampDown(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStartRampDown(functor);
}

int32_t CpProxyUpnpOrgDimming1EndStartRampDown(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndStartRampDown(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncStopRamp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStopRamp();
}

void CpProxyUpnpOrgDimming1BeginStopRamp(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStopRamp(functor);
}

int32_t CpProxyUpnpOrgDimming1EndStopRamp(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndStopRamp(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncStartRampToLevel(THandle aHandle, uint32_t anewLoadLevelTarget, uint32_t anewRampTime)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStartRampToLevel(anewLoadLevelTarget, anewRampTime);
}

void CpProxyUpnpOrgDimming1BeginStartRampToLevel(THandle aHandle, uint32_t anewLoadLevelTarget, uint32_t anewRampTime, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStartRampToLevel(anewLoadLevelTarget, anewRampTime, functor);
}

int32_t CpProxyUpnpOrgDimming1EndStartRampToLevel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndStartRampToLevel(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncSetStepDelta(THandle aHandle, uint32_t anewStepDelta)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetStepDelta(anewStepDelta);
}

void CpProxyUpnpOrgDimming1BeginSetStepDelta(THandle aHandle, uint32_t anewStepDelta, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetStepDelta(anewStepDelta, functor);
}

int32_t CpProxyUpnpOrgDimming1EndSetStepDelta(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetStepDelta(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetStepDelta(THandle aHandle, uint32_t* aretStepDelta)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetStepDelta(*aretStepDelta);
}

void CpProxyUpnpOrgDimming1BeginGetStepDelta(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetStepDelta(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetStepDelta(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aretStepDelta)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetStepDelta(*async, *aretStepDelta);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncSetRampRate(THandle aHandle, uint32_t anewRampRate)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetRampRate(anewRampRate);
}

void CpProxyUpnpOrgDimming1BeginSetRampRate(THandle aHandle, uint32_t anewRampRate, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetRampRate(anewRampRate, functor);
}

int32_t CpProxyUpnpOrgDimming1EndSetRampRate(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetRampRate(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetRampRate(THandle aHandle, uint32_t* aretRampRate)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetRampRate(*aretRampRate);
}

void CpProxyUpnpOrgDimming1BeginGetRampRate(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRampRate(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetRampRate(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aretRampRate)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetRampRate(*async, *aretRampRate);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncPauseRamp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncPauseRamp();
}

void CpProxyUpnpOrgDimming1BeginPauseRamp(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPauseRamp(functor);
}

int32_t CpProxyUpnpOrgDimming1EndPauseRamp(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndPauseRamp(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncResumeRamp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncResumeRamp();
}

void CpProxyUpnpOrgDimming1BeginResumeRamp(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginResumeRamp(functor);
}

int32_t CpProxyUpnpOrgDimming1EndResumeRamp(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndResumeRamp(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetIsRamping(THandle aHandle, uint32_t* aretIsRamping)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aretIsRamping = 0;
    proxyC->Proxy()->SyncGetIsRamping(*(TBool*)aretIsRamping);
}

void CpProxyUpnpOrgDimming1BeginGetIsRamping(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetIsRamping(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetIsRamping(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aretIsRamping)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aretIsRamping = 0;
    try {
        proxyC->Proxy()->EndGetIsRamping(*async, *(TBool*)aretIsRamping);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetRampPaused(THandle aHandle, uint32_t* aretRampPaused)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aretRampPaused = 0;
    proxyC->Proxy()->SyncGetRampPaused(*(TBool*)aretRampPaused);
}

void CpProxyUpnpOrgDimming1BeginGetRampPaused(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRampPaused(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetRampPaused(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aretRampPaused)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aretRampPaused = 0;
    try {
        proxyC->Proxy()->EndGetRampPaused(*async, *(TBool*)aretRampPaused);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetRampTime(THandle aHandle, uint32_t* aretRampTime)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetRampTime(*aretRampTime);
}

void CpProxyUpnpOrgDimming1BeginGetRampTime(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRampTime(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetRampTime(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aretRampTime)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetRampTime(*async, *aretRampTime);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SetPropertyLoadLevelStatusChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyLoadLevelStatusChanged(functor);
}

void CpProxyUpnpOrgDimming1SetPropertyStepDeltaChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyStepDeltaChanged(functor);
}

void CpProxyUpnpOrgDimming1SetPropertyRampRateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyRampRateChanged(functor);
}

void CpProxyUpnpOrgDimming1SetPropertyIsRampingChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyIsRampingChanged(functor);
}

void CpProxyUpnpOrgDimming1SetPropertyRampPausedChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyRampPausedChanged(functor);
}

void CpProxyUpnpOrgDimming1PropertyLoadLevelStatus(THandle aHandle, uint32_t* aLoadLevelStatus)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyLoadLevelStatus(*aLoadLevelStatus);
}

void CpProxyUpnpOrgDimming1PropertyStepDelta(THandle aHandle, uint32_t* aStepDelta)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyStepDelta(*aStepDelta);
}

void CpProxyUpnpOrgDimming1PropertyRampRate(THandle aHandle, uint32_t* aRampRate)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyRampRate(*aRampRate);
}

void CpProxyUpnpOrgDimming1PropertyIsRamping(THandle aHandle, uint32_t* aIsRamping)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aIsRamping = false;
    proxyC->Proxy()->PropertyIsRamping(*(TBool*)aIsRamping);
}

void CpProxyUpnpOrgDimming1PropertyRampPaused(THandle aHandle, uint32_t* aRampPaused)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aRampPaused = false;
    proxyC->Proxy()->PropertyRampPaused(*(TBool*)aRampPaused);
}

