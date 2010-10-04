#include <C/CpLinnCoUkJukebox1.h>
#include <Core/CpLinnCoUkJukebox1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkJukebox1C : public CpProxyC
{
public:
    CpProxyLinnCoUkJukebox1C(CpDeviceC aDevice);
    CpProxyLinnCoUkJukebox1* Proxy() { return static_cast<CpProxyLinnCoUkJukebox1*>(iProxy); }
};

CpProxyLinnCoUkJukebox1C::CpProxyLinnCoUkJukebox1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkJukebox1(*iDevice);
}


THandle CpProxyLinnCoUkJukebox1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkJukebox1C(aDevice);
}

void CpProxyLinnCoUkJukebox1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkJukebox1SyncSetPresetPrefix(THandle aHandle, const char* aaUri)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    proxyC->Proxy()->SyncSetPresetPrefix(buf_aaUri);
}

void CpProxyLinnCoUkJukebox1BeginSetPresetPrefix(THandle aHandle, const char* aaUri, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetPresetPrefix(buf_aaUri, functor);
}

int32_t CpProxyLinnCoUkJukebox1EndSetPresetPrefix(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetPresetPrefix(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SyncPresetPrefix(THandle aHandle, char** aaUri)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri;
    proxyC->Proxy()->SyncPresetPrefix(buf_aaUri);
    *aaUri = buf_aaUri.Extract();
}

void CpProxyLinnCoUkJukebox1BeginPresetPrefix(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPresetPrefix(functor);
}

int32_t CpProxyLinnCoUkJukebox1EndPresetPrefix(THandle aHandle, ZappHandleAsync aAsync, char** aaUri)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaUri;
    *aaUri = NULL;
    try {
        proxyC->Proxy()->EndPresetPrefix(*async, buf_aaUri);
        *aaUri = buf_aaUri.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SyncSetAlbumArtFileName(THandle aHandle, const char* aaName)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    proxyC->Proxy()->SyncSetAlbumArtFileName(buf_aaName);
}

void CpProxyLinnCoUkJukebox1BeginSetAlbumArtFileName(THandle aHandle, const char* aaName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetAlbumArtFileName(buf_aaName, functor);
}

int32_t CpProxyLinnCoUkJukebox1EndSetAlbumArtFileName(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetAlbumArtFileName(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SyncAlbumArtFileName(THandle aHandle, char** aaName)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName;
    proxyC->Proxy()->SyncAlbumArtFileName(buf_aaName);
    *aaName = buf_aaName.Extract();
}

void CpProxyLinnCoUkJukebox1BeginAlbumArtFileName(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginAlbumArtFileName(functor);
}

int32_t CpProxyLinnCoUkJukebox1EndAlbumArtFileName(THandle aHandle, ZappHandleAsync aAsync, char** aaName)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaName;
    *aaName = NULL;
    try {
        proxyC->Proxy()->EndAlbumArtFileName(*async, buf_aaName);
        *aaName = buf_aaName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SyncSetCurrentPreset(THandle aHandle, uint32_t aaPreset)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetCurrentPreset(aaPreset);
}

void CpProxyLinnCoUkJukebox1BeginSetCurrentPreset(THandle aHandle, uint32_t aaPreset, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetCurrentPreset(aaPreset, functor);
}

int32_t CpProxyLinnCoUkJukebox1EndSetCurrentPreset(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetCurrentPreset(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SyncCurrentPreset(THandle aHandle, uint32_t* aaPreset)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncCurrentPreset(*aaPreset);
}

void CpProxyLinnCoUkJukebox1BeginCurrentPreset(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginCurrentPreset(functor);
}

int32_t CpProxyLinnCoUkJukebox1EndCurrentPreset(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaPreset)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndCurrentPreset(*async, *aaPreset);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SyncPresetMetaData(THandle aHandle, uint32_t aaPreset, char** aaMetaData)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMetaData;
    proxyC->Proxy()->SyncPresetMetaData(aaPreset, buf_aaMetaData);
    *aaMetaData = buf_aaMetaData.Extract();
}

void CpProxyLinnCoUkJukebox1BeginPresetMetaData(THandle aHandle, uint32_t aaPreset, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPresetMetaData(aaPreset, functor);
}

int32_t CpProxyLinnCoUkJukebox1EndPresetMetaData(THandle aHandle, ZappHandleAsync aAsync, char** aaMetaData)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaMetaData;
    *aaMetaData = NULL;
    try {
        proxyC->Proxy()->EndPresetMetaData(*async, buf_aaMetaData);
        *aaMetaData = buf_aaMetaData.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SyncLoadManifest(THandle aHandle, uint32_t* aaTotalPresets)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncLoadManifest(*aaTotalPresets);
}

void CpProxyLinnCoUkJukebox1BeginLoadManifest(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginLoadManifest(functor);
}

int32_t CpProxyLinnCoUkJukebox1EndLoadManifest(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaTotalPresets)
{
    int32_t err = 0;
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndLoadManifest(*async, *aaTotalPresets);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkJukebox1SetPropertyCurrentPresetChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyCurrentPresetChanged(functor);
}

void CpProxyLinnCoUkJukebox1SetPropertyPresetPrefixChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyPresetPrefixChanged(functor);
}

void CpProxyLinnCoUkJukebox1SetPropertyAlbumArtFileNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyAlbumArtFileNameChanged(functor);
}

void CpProxyLinnCoUkJukebox1PropertyCurrentPreset(THandle aHandle, uint32_t* aCurrentPreset)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyCurrentPreset(*aCurrentPreset);
}

void CpProxyLinnCoUkJukebox1PropertyPresetPrefix(THandle aHandle, char** aPresetPrefix)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aPresetPrefix;
    proxyC->Proxy()->PropertyPresetPrefix(buf_aPresetPrefix);
    *aPresetPrefix = buf_aPresetPrefix.Transfer();
}

void CpProxyLinnCoUkJukebox1PropertyAlbumArtFileName(THandle aHandle, char** aAlbumArtFileName)
{
    CpProxyLinnCoUkJukebox1C* proxyC = reinterpret_cast<CpProxyLinnCoUkJukebox1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aAlbumArtFileName;
    proxyC->Proxy()->PropertyAlbumArtFileName(buf_aAlbumArtFileName);
    *aAlbumArtFileName = buf_aAlbumArtFileName.Transfer();
}

