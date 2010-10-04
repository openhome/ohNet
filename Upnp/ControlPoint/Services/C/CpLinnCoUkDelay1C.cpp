#include <C/CpLinnCoUkDelay1.h>
#include <Core/CpLinnCoUkDelay1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkDelay1C : public CpProxyC
{
public:
    CpProxyLinnCoUkDelay1C(CpDeviceC aDevice);
    CpProxyLinnCoUkDelay1* Proxy() { return static_cast<CpProxyLinnCoUkDelay1*>(iProxy); }
};

CpProxyLinnCoUkDelay1C::CpProxyLinnCoUkDelay1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkDelay1(*iDevice);
}


THandle CpProxyLinnCoUkDelay1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkDelay1C(aDevice);
}

void CpProxyLinnCoUkDelay1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkDelay1SyncPresetXml(THandle aHandle, char** aaPresetXml)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaPresetXml;
    proxyC->Proxy()->SyncPresetXml(buf_aaPresetXml);
    *aaPresetXml = buf_aaPresetXml.Extract();
}

void CpProxyLinnCoUkDelay1BeginPresetXml(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPresetXml(functor);
}

int32_t CpProxyLinnCoUkDelay1EndPresetXml(THandle aHandle, ZappHandleAsync aAsync, char** aaPresetXml)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaPresetXml;
    *aaPresetXml = NULL;
    try {
        proxyC->Proxy()->EndPresetXml(*async, buf_aaPresetXml);
        *aaPresetXml = buf_aaPresetXml.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncPresetIndex(THandle aHandle, uint32_t* aaIndex)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncPresetIndex(*aaIndex);
}

void CpProxyLinnCoUkDelay1BeginPresetIndex(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPresetIndex(functor);
}

int32_t CpProxyLinnCoUkDelay1EndPresetIndex(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaIndex)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndPresetIndex(*async, *aaIndex);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncSetPresetIndex(THandle aHandle, uint32_t aaIndex)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetPresetIndex(aaIndex);
}

void CpProxyLinnCoUkDelay1BeginSetPresetIndex(THandle aHandle, uint32_t aaIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetPresetIndex(aaIndex, functor);
}

int32_t CpProxyLinnCoUkDelay1EndSetPresetIndex(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetPresetIndex(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncSetPresetDelay(THandle aHandle, uint32_t aaIndex, uint32_t aaDelay)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetPresetDelay(aaIndex, aaDelay);
}

void CpProxyLinnCoUkDelay1BeginSetPresetDelay(THandle aHandle, uint32_t aaIndex, uint32_t aaDelay, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetPresetDelay(aaIndex, aaDelay, functor);
}

int32_t CpProxyLinnCoUkDelay1EndSetPresetDelay(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetPresetDelay(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncSetPresetVisible(THandle aHandle, uint32_t aaIndex, uint32_t aaVisible)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetPresetVisible(aaIndex, (aaVisible==0? false : true));
}

void CpProxyLinnCoUkDelay1BeginSetPresetVisible(THandle aHandle, uint32_t aaIndex, uint32_t aaVisible, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetPresetVisible(aaIndex, (aaVisible==0? false : true), functor);
}

int32_t CpProxyLinnCoUkDelay1EndSetPresetVisible(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetPresetVisible(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncSetPresetName(THandle aHandle, uint32_t aaIndex, const char* aaName)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    proxyC->Proxy()->SyncSetPresetName(aaIndex, buf_aaName);
}

void CpProxyLinnCoUkDelay1BeginSetPresetName(THandle aHandle, uint32_t aaIndex, const char* aaName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetPresetName(aaIndex, buf_aaName, functor);
}

int32_t CpProxyLinnCoUkDelay1EndSetPresetName(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetPresetName(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncDelayMinimum(THandle aHandle, uint32_t* aaDelay)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncDelayMinimum(*aaDelay);
}

void CpProxyLinnCoUkDelay1BeginDelayMinimum(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDelayMinimum(functor);
}

int32_t CpProxyLinnCoUkDelay1EndDelayMinimum(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaDelay)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDelayMinimum(*async, *aaDelay);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncDelayMaximum(THandle aHandle, uint32_t* aaDelay)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncDelayMaximum(*aaDelay);
}

void CpProxyLinnCoUkDelay1BeginDelayMaximum(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDelayMaximum(functor);
}

int32_t CpProxyLinnCoUkDelay1EndDelayMaximum(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaDelay)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDelayMaximum(*async, *aaDelay);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SyncPresetCount(THandle aHandle, uint32_t* aaCount)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncPresetCount(*aaCount);
}

void CpProxyLinnCoUkDelay1BeginPresetCount(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPresetCount(functor);
}

int32_t CpProxyLinnCoUkDelay1EndPresetCount(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaCount)
{
    int32_t err = 0;
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndPresetCount(*async, *aaCount);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDelay1SetPropertyPresetXmlChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyPresetXmlChanged(functor);
}

void CpProxyLinnCoUkDelay1SetPropertyPresetIndexChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyPresetIndexChanged(functor);
}

void CpProxyLinnCoUkDelay1PropertyPresetXml(THandle aHandle, char** aPresetXml)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aPresetXml;
    proxyC->Proxy()->PropertyPresetXml(buf_aPresetXml);
    *aPresetXml = buf_aPresetXml.Transfer();
}

void CpProxyLinnCoUkDelay1PropertyPresetIndex(THandle aHandle, uint32_t* aPresetIndex)
{
    CpProxyLinnCoUkDelay1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDelay1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyPresetIndex(*aPresetIndex);
}

