#include <C/CpLinnCoUkInfo1.h>
#include <Core/CpLinnCoUkInfo1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkInfo1C : public CpProxyC
{
public:
    CpProxyLinnCoUkInfo1C(CpDeviceC aDevice);
    CpProxyLinnCoUkInfo1* Proxy() { return static_cast<CpProxyLinnCoUkInfo1*>(iProxy); }
};

CpProxyLinnCoUkInfo1C::CpProxyLinnCoUkInfo1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkInfo1(*iDevice);
}


THandle CpProxyLinnCoUkInfo1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkInfo1C(aDevice);
}

void CpProxyLinnCoUkInfo1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkInfo1SyncCounters(THandle aHandle, uint32_t* aaTrackCount, uint32_t* aaDetailsCount, uint32_t* aaMetatextCount)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncCounters(*aaTrackCount, *aaDetailsCount, *aaMetatextCount);
}

void CpProxyLinnCoUkInfo1BeginCounters(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginCounters(functor);
}

int32_t CpProxyLinnCoUkInfo1EndCounters(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaTrackCount, uint32_t* aaDetailsCount, uint32_t* aaMetatextCount)
{
    int32_t err = 0;
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndCounters(*async, *aaTrackCount, *aaDetailsCount, *aaMetatextCount);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkInfo1SyncTrack(THandle aHandle, char** aaUri, char** aaMetadata)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri;
    Brh buf_aaMetadata;
    proxyC->Proxy()->SyncTrack(buf_aaUri, buf_aaMetadata);
    *aaUri = buf_aaUri.Extract();
    *aaMetadata = buf_aaMetadata.Extract();
}

void CpProxyLinnCoUkInfo1BeginTrack(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginTrack(functor);
}

int32_t CpProxyLinnCoUkInfo1EndTrack(THandle aHandle, ZappHandleAsync aAsync, char** aaUri, char** aaMetadata)
{
    int32_t err = 0;
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaUri;
    *aaUri = NULL;
    Brh buf_aaMetadata;
    *aaMetadata = NULL;
    try {
        proxyC->Proxy()->EndTrack(*async, buf_aaUri, buf_aaMetadata);
        *aaUri = buf_aaUri.Extract();
        *aaMetadata = buf_aaMetadata.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkInfo1SyncDetails(THandle aHandle, uint32_t* aaDuration, uint32_t* aaBitRate, uint32_t* aaBitDepth, uint32_t* aaSampleRate, uint32_t* aaLossless, char** aaCodecName)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaLossless = 0;
    Brh buf_aaCodecName;
    proxyC->Proxy()->SyncDetails(*aaDuration, *aaBitRate, *aaBitDepth, *aaSampleRate, *(TBool*)aaLossless, buf_aaCodecName);
    *aaCodecName = buf_aaCodecName.Extract();
}

void CpProxyLinnCoUkInfo1BeginDetails(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDetails(functor);
}

int32_t CpProxyLinnCoUkInfo1EndDetails(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaDuration, uint32_t* aaBitRate, uint32_t* aaBitDepth, uint32_t* aaSampleRate, uint32_t* aaLossless, char** aaCodecName)
{
    int32_t err = 0;
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaLossless = 0;
    Brh buf_aaCodecName;
    *aaCodecName = NULL;
    try {
        proxyC->Proxy()->EndDetails(*async, *aaDuration, *aaBitRate, *aaBitDepth, *aaSampleRate, *(TBool*)aaLossless, buf_aaCodecName);
        *aaCodecName = buf_aaCodecName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkInfo1SyncMetatext(THandle aHandle, char** aaMetatext)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMetatext;
    proxyC->Proxy()->SyncMetatext(buf_aaMetatext);
    *aaMetatext = buf_aaMetatext.Extract();
}

void CpProxyLinnCoUkInfo1BeginMetatext(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginMetatext(functor);
}

int32_t CpProxyLinnCoUkInfo1EndMetatext(THandle aHandle, ZappHandleAsync aAsync, char** aaMetatext)
{
    int32_t err = 0;
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaMetatext;
    *aaMetatext = NULL;
    try {
        proxyC->Proxy()->EndMetatext(*async, buf_aaMetatext);
        *aaMetatext = buf_aaMetatext.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkInfo1SetPropertyTrackCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTrackCountChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyDetailsCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyDetailsCountChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyMetatextCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyMetatextCountChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyUriChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyUriChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyMetadataChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyMetadataChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyDurationChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyDurationChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyBitRateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyBitRateChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyBitDepthChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyBitDepthChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertySampleRateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertySampleRateChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyLosslessChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyLosslessChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyCodecNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyCodecNameChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyMetatextChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyMetatextChanged(functor);
}

void CpProxyLinnCoUkInfo1PropertyTrackCount(THandle aHandle, uint32_t* aTrackCount)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyTrackCount(*aTrackCount);
}

void CpProxyLinnCoUkInfo1PropertyDetailsCount(THandle aHandle, uint32_t* aDetailsCount)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyDetailsCount(*aDetailsCount);
}

void CpProxyLinnCoUkInfo1PropertyMetatextCount(THandle aHandle, uint32_t* aMetatextCount)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyMetatextCount(*aMetatextCount);
}

void CpProxyLinnCoUkInfo1PropertyUri(THandle aHandle, char** aUri)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aUri;
    proxyC->Proxy()->PropertyUri(buf_aUri);
    *aUri = buf_aUri.Transfer();
}

void CpProxyLinnCoUkInfo1PropertyMetadata(THandle aHandle, char** aMetadata)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aMetadata;
    proxyC->Proxy()->PropertyMetadata(buf_aMetadata);
    *aMetadata = buf_aMetadata.Transfer();
}

void CpProxyLinnCoUkInfo1PropertyDuration(THandle aHandle, uint32_t* aDuration)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyDuration(*aDuration);
}

void CpProxyLinnCoUkInfo1PropertyBitRate(THandle aHandle, uint32_t* aBitRate)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyBitRate(*aBitRate);
}

void CpProxyLinnCoUkInfo1PropertyBitDepth(THandle aHandle, uint32_t* aBitDepth)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyBitDepth(*aBitDepth);
}

void CpProxyLinnCoUkInfo1PropertySampleRate(THandle aHandle, uint32_t* aSampleRate)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertySampleRate(*aSampleRate);
}

void CpProxyLinnCoUkInfo1PropertyLossless(THandle aHandle, uint32_t* aLossless)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aLossless = false;
    proxyC->Proxy()->PropertyLossless(*(TBool*)aLossless);
}

void CpProxyLinnCoUkInfo1PropertyCodecName(THandle aHandle, char** aCodecName)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aCodecName;
    proxyC->Proxy()->PropertyCodecName(buf_aCodecName);
    *aCodecName = buf_aCodecName.Transfer();
}

void CpProxyLinnCoUkInfo1PropertyMetatext(THandle aHandle, char** aMetatext)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aMetatext;
    proxyC->Proxy()->PropertyMetatext(buf_aMetatext);
    *aMetatext = buf_aMetatext.Transfer();
}

