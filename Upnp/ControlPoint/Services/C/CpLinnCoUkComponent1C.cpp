#include <C/CpLinnCoUkComponent1.h>
#include <Core/CpLinnCoUkComponent1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkComponent1C : public CpProxyC
{
public:
    CpProxyLinnCoUkComponent1C(CpDeviceC aDevice);
    CpProxyLinnCoUkComponent1* Proxy() { return static_cast<CpProxyLinnCoUkComponent1*>(iProxy); }
};

CpProxyLinnCoUkComponent1C::CpProxyLinnCoUkComponent1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkComponent1(*iDevice);
}


THandle CpProxyLinnCoUkComponent1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkComponent1C(aDevice);
}

void CpProxyLinnCoUkComponent1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkComponent1SyncAmplifierEnabled(THandle aHandle, uint32_t* aaEnabled)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaEnabled = 0;
    proxyC->Proxy()->SyncAmplifierEnabled(*(TBool*)aaEnabled);
}

void CpProxyLinnCoUkComponent1BeginAmplifierEnabled(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginAmplifierEnabled(functor);
}

int32_t CpProxyLinnCoUkComponent1EndAmplifierEnabled(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaEnabled)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaEnabled = 0;
    try {
        proxyC->Proxy()->EndAmplifierEnabled(*async, *(TBool*)aaEnabled);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncSetAmplifierEnabled(THandle aHandle, uint32_t aaEnabled)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetAmplifierEnabled((aaEnabled==0? false : true));
}

void CpProxyLinnCoUkComponent1BeginSetAmplifierEnabled(THandle aHandle, uint32_t aaEnabled, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetAmplifierEnabled((aaEnabled==0? false : true), functor);
}

int32_t CpProxyLinnCoUkComponent1EndSetAmplifierEnabled(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetAmplifierEnabled(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncAmplifierAttenuation(THandle aHandle, char** aaAttenuation)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaAttenuation;
    proxyC->Proxy()->SyncAmplifierAttenuation(buf_aaAttenuation);
    *aaAttenuation = buf_aaAttenuation.Extract();
}

void CpProxyLinnCoUkComponent1BeginAmplifierAttenuation(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginAmplifierAttenuation(functor);
}

int32_t CpProxyLinnCoUkComponent1EndAmplifierAttenuation(THandle aHandle, ZappHandleAsync aAsync, char** aaAttenuation)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaAttenuation;
    *aaAttenuation = NULL;
    try {
        proxyC->Proxy()->EndAmplifierAttenuation(*async, buf_aaAttenuation);
        *aaAttenuation = buf_aaAttenuation.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncSetAmplifierAttenuation(THandle aHandle, const char* aaAttenuation)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaAttenuation(aaAttenuation);
    proxyC->Proxy()->SyncSetAmplifierAttenuation(buf_aaAttenuation);
}

void CpProxyLinnCoUkComponent1BeginSetAmplifierAttenuation(THandle aHandle, const char* aaAttenuation, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaAttenuation(aaAttenuation);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetAmplifierAttenuation(buf_aaAttenuation, functor);
}

int32_t CpProxyLinnCoUkComponent1EndSetAmplifierAttenuation(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetAmplifierAttenuation(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncSetVolumeControlEnabled(THandle aHandle, uint32_t aaEnabled)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetVolumeControlEnabled((aaEnabled==0? false : true));
}

void CpProxyLinnCoUkComponent1BeginSetVolumeControlEnabled(THandle aHandle, uint32_t aaEnabled, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetVolumeControlEnabled((aaEnabled==0? false : true), functor);
}

int32_t CpProxyLinnCoUkComponent1EndSetVolumeControlEnabled(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetVolumeControlEnabled(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncVolumeControlEnabled(THandle aHandle, uint32_t* aaEnabled)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaEnabled = 0;
    proxyC->Proxy()->SyncVolumeControlEnabled(*(TBool*)aaEnabled);
}

void CpProxyLinnCoUkComponent1BeginVolumeControlEnabled(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginVolumeControlEnabled(functor);
}

int32_t CpProxyLinnCoUkComponent1EndVolumeControlEnabled(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaEnabled)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaEnabled = 0;
    try {
        proxyC->Proxy()->EndVolumeControlEnabled(*async, *(TBool*)aaEnabled);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncSetDigitalAudioOutputRaw(THandle aHandle, uint32_t aaRaw)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetDigitalAudioOutputRaw((aaRaw==0? false : true));
}

void CpProxyLinnCoUkComponent1BeginSetDigitalAudioOutputRaw(THandle aHandle, uint32_t aaRaw, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetDigitalAudioOutputRaw((aaRaw==0? false : true), functor);
}

int32_t CpProxyLinnCoUkComponent1EndSetDigitalAudioOutputRaw(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetDigitalAudioOutputRaw(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncDigitalAudioOutputRaw(THandle aHandle, uint32_t* aaRaw)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaRaw = 0;
    proxyC->Proxy()->SyncDigitalAudioOutputRaw(*(TBool*)aaRaw);
}

void CpProxyLinnCoUkComponent1BeginDigitalAudioOutputRaw(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDigitalAudioOutputRaw(functor);
}

int32_t CpProxyLinnCoUkComponent1EndDigitalAudioOutputRaw(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaRaw)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaRaw = 0;
    try {
        proxyC->Proxy()->EndDigitalAudioOutputRaw(*async, *(TBool*)aaRaw);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncAmplifierOverTemperature(THandle aHandle, uint32_t* aaOverTemperature)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaOverTemperature = 0;
    proxyC->Proxy()->SyncAmplifierOverTemperature(*(TBool*)aaOverTemperature);
}

void CpProxyLinnCoUkComponent1BeginAmplifierOverTemperature(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginAmplifierOverTemperature(functor);
}

int32_t CpProxyLinnCoUkComponent1EndAmplifierOverTemperature(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaOverTemperature)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaOverTemperature = 0;
    try {
        proxyC->Proxy()->EndAmplifierOverTemperature(*async, *(TBool*)aaOverTemperature);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncEthernetLinkConnected(THandle aHandle, uint32_t* aaLinkConnected)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaLinkConnected = 0;
    proxyC->Proxy()->SyncEthernetLinkConnected(*(TBool*)aaLinkConnected);
}

void CpProxyLinnCoUkComponent1BeginEthernetLinkConnected(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginEthernetLinkConnected(functor);
}

int32_t CpProxyLinnCoUkComponent1EndEthernetLinkConnected(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaLinkConnected)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaLinkConnected = 0;
    try {
        proxyC->Proxy()->EndEthernetLinkConnected(*async, *(TBool*)aaLinkConnected);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncLocate(THandle aHandle)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncLocate();
}

void CpProxyLinnCoUkComponent1BeginLocate(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginLocate(functor);
}

int32_t CpProxyLinnCoUkComponent1EndLocate(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndLocate(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SetPropertyAmplifierEnabledChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyAmplifierEnabledChanged(functor);
}

void CpProxyLinnCoUkComponent1SetPropertyAmplifierAttenuationChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyAmplifierAttenuationChanged(functor);
}

void CpProxyLinnCoUkComponent1SetPropertyVolumeControlEnabledChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyVolumeControlEnabledChanged(functor);
}

void CpProxyLinnCoUkComponent1SetPropertyDigitalAudioOutputRawChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyDigitalAudioOutputRawChanged(functor);
}

void CpProxyLinnCoUkComponent1PropertyAmplifierEnabled(THandle aHandle, uint32_t* aAmplifierEnabled)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aAmplifierEnabled = false;
    proxyC->Proxy()->PropertyAmplifierEnabled(*(TBool*)aAmplifierEnabled);
}

void CpProxyLinnCoUkComponent1PropertyAmplifierAttenuation(THandle aHandle, char** aAmplifierAttenuation)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aAmplifierAttenuation;
    proxyC->Proxy()->PropertyAmplifierAttenuation(buf_aAmplifierAttenuation);
    *aAmplifierAttenuation = buf_aAmplifierAttenuation.Transfer();
}

void CpProxyLinnCoUkComponent1PropertyVolumeControlEnabled(THandle aHandle, uint32_t* aVolumeControlEnabled)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aVolumeControlEnabled = false;
    proxyC->Proxy()->PropertyVolumeControlEnabled(*(TBool*)aVolumeControlEnabled);
}

void CpProxyLinnCoUkComponent1PropertyDigitalAudioOutputRaw(THandle aHandle, uint32_t* aDigitalAudioOutputRaw)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aDigitalAudioOutputRaw = false;
    proxyC->Proxy()->PropertyDigitalAudioOutputRaw(*(TBool*)aDigitalAudioOutputRaw);
}

