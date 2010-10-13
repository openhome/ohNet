#include <C/CpLinnCoUkPreamp4.h>
#include <Core/CpLinnCoUkPreamp4.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkPreamp4C : public CpProxyC
{
public:
    CpProxyLinnCoUkPreamp4C(CpDeviceC aDevice);
    CpProxyLinnCoUkPreamp4* Proxy() { return static_cast<CpProxyLinnCoUkPreamp4*>(iProxy); }
};

CpProxyLinnCoUkPreamp4C::CpProxyLinnCoUkPreamp4C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkPreamp4(*iDevice);
}


THandle CpProxyLinnCoUkPreamp4Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkPreamp4C(aDevice);
}

void CpProxyLinnCoUkPreamp4Destroy(THandle aHandle)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkPreamp4SyncVolumeInc(THandle aHandle)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncVolumeInc();
}

void CpProxyLinnCoUkPreamp4BeginVolumeInc(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginVolumeInc(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndVolumeInc(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndVolumeInc(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncVolumeDec(THandle aHandle)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncVolumeDec();
}

void CpProxyLinnCoUkPreamp4BeginVolumeDec(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginVolumeDec(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndVolumeDec(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndVolumeDec(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncSetVolume(THandle aHandle, uint32_t aaVolume)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetVolume(aaVolume);
}

void CpProxyLinnCoUkPreamp4BeginSetVolume(THandle aHandle, uint32_t aaVolume, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetVolume(aaVolume, functor);
}

int32_t CpProxyLinnCoUkPreamp4EndSetVolume(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
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

void CpProxyLinnCoUkPreamp4SyncVolume(THandle aHandle, uint32_t* aaVolume)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncVolume(*aaVolume);
}

void CpProxyLinnCoUkPreamp4BeginVolume(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginVolume(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndVolume(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaVolume)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndVolume(*async, *aaVolume);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncSetMute(THandle aHandle, uint32_t aaMute)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetMute((aaMute==0? false : true));
}

void CpProxyLinnCoUkPreamp4BeginSetMute(THandle aHandle, uint32_t aaMute, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetMute((aaMute==0? false : true), functor);
}

int32_t CpProxyLinnCoUkPreamp4EndSetMute(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
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

void CpProxyLinnCoUkPreamp4SyncMute(THandle aHandle, uint32_t* aaMute)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaMute = 0;
    proxyC->Proxy()->SyncMute(*(TBool*)aaMute);
}

void CpProxyLinnCoUkPreamp4BeginMute(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginMute(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndMute(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaMute)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaMute = 0;
    try {
        proxyC->Proxy()->EndMute(*async, *(TBool*)aaMute);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncSetBalance(THandle aHandle, int32_t aaBalance)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetBalance(aaBalance);
}

void CpProxyLinnCoUkPreamp4BeginSetBalance(THandle aHandle, int32_t aaBalance, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetBalance(aaBalance, functor);
}

int32_t CpProxyLinnCoUkPreamp4EndSetBalance(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetBalance(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncBalance(THandle aHandle, int32_t* aaBalance)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncBalance(*aaBalance);
}

void CpProxyLinnCoUkPreamp4BeginBalance(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginBalance(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndBalance(THandle aHandle, ZappHandleAsync aAsync, int32_t* aaBalance)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndBalance(*async, *aaBalance);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncSetVolumeLimit(THandle aHandle, uint32_t aaVolumeLimit)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetVolumeLimit(aaVolumeLimit);
}

void CpProxyLinnCoUkPreamp4BeginSetVolumeLimit(THandle aHandle, uint32_t aaVolumeLimit, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetVolumeLimit(aaVolumeLimit, functor);
}

int32_t CpProxyLinnCoUkPreamp4EndSetVolumeLimit(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetVolumeLimit(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncVolumeLimit(THandle aHandle, uint32_t* aaVolumeLimit)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncVolumeLimit(*aaVolumeLimit);
}

void CpProxyLinnCoUkPreamp4BeginVolumeLimit(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginVolumeLimit(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndVolumeLimit(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaVolumeLimit)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndVolumeLimit(*async, *aaVolumeLimit);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncSetStartupVolume(THandle aHandle, uint32_t aaStartupVolume)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetStartupVolume(aaStartupVolume);
}

void CpProxyLinnCoUkPreamp4BeginSetStartupVolume(THandle aHandle, uint32_t aaStartupVolume, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetStartupVolume(aaStartupVolume, functor);
}

int32_t CpProxyLinnCoUkPreamp4EndSetStartupVolume(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetStartupVolume(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncStartupVolume(THandle aHandle, uint32_t* aaStartupVolume)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStartupVolume(*aaStartupVolume);
}

void CpProxyLinnCoUkPreamp4BeginStartupVolume(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStartupVolume(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndStartupVolume(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStartupVolume)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndStartupVolume(*async, *aaStartupVolume);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncSetStartupVolumeEnabled(THandle aHandle, uint32_t aaStartupVolumeEnabled)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetStartupVolumeEnabled((aaStartupVolumeEnabled==0? false : true));
}

void CpProxyLinnCoUkPreamp4BeginSetStartupVolumeEnabled(THandle aHandle, uint32_t aaStartupVolumeEnabled, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetStartupVolumeEnabled((aaStartupVolumeEnabled==0? false : true), functor);
}

int32_t CpProxyLinnCoUkPreamp4EndSetStartupVolumeEnabled(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetStartupVolumeEnabled(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncStartupVolumeEnabled(THandle aHandle, uint32_t* aaStartupVolumeEnabled)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaStartupVolumeEnabled = 0;
    proxyC->Proxy()->SyncStartupVolumeEnabled(*(TBool*)aaStartupVolumeEnabled);
}

void CpProxyLinnCoUkPreamp4BeginStartupVolumeEnabled(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStartupVolumeEnabled(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndStartupVolumeEnabled(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStartupVolumeEnabled)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaStartupVolumeEnabled = 0;
    try {
        proxyC->Proxy()->EndStartupVolumeEnabled(*async, *(TBool*)aaStartupVolumeEnabled);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SetPropertyVolumeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyVolumeChanged(functor);
}

void CpProxyLinnCoUkPreamp4SetPropertyMuteChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyMuteChanged(functor);
}

void CpProxyLinnCoUkPreamp4SetPropertyBalanceChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyBalanceChanged(functor);
}

void CpProxyLinnCoUkPreamp4SetPropertyVolumeLimitChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyVolumeLimitChanged(functor);
}

void CpProxyLinnCoUkPreamp4SetPropertyStartupVolumeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyStartupVolumeChanged(functor);
}

void CpProxyLinnCoUkPreamp4SetPropertyStartupVolumeEnabledChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyStartupVolumeEnabledChanged(functor);
}

void CpProxyLinnCoUkPreamp4PropertyVolume(THandle aHandle, uint32_t* aVolume)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyVolume(*aVolume);
}

void CpProxyLinnCoUkPreamp4PropertyMute(THandle aHandle, uint32_t* aMute)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aMute = false;
    proxyC->Proxy()->PropertyMute(*(TBool*)aMute);
}

void CpProxyLinnCoUkPreamp4PropertyBalance(THandle aHandle, int32_t* aBalance)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyBalance(*aBalance);
}

void CpProxyLinnCoUkPreamp4PropertyVolumeLimit(THandle aHandle, uint32_t* aVolumeLimit)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyVolumeLimit(*aVolumeLimit);
}

void CpProxyLinnCoUkPreamp4PropertyStartupVolume(THandle aHandle, uint32_t* aStartupVolume)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyStartupVolume(*aStartupVolume);
}

void CpProxyLinnCoUkPreamp4PropertyStartupVolumeEnabled(THandle aHandle, uint32_t* aStartupVolumeEnabled)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aStartupVolumeEnabled = false;
    proxyC->Proxy()->PropertyStartupVolumeEnabled(*(TBool*)aStartupVolumeEnabled);
}

