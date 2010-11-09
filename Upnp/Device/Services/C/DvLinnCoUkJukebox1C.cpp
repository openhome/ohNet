#include <C/DvLinnCoUkJukebox1.h>
#include <Core/DvLinnCoUkJukebox1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkJukebox1C : public DvProviderLinnCoUkJukebox1
{
public:
    DvProviderLinnCoUkJukebox1C(DvDevice& aDevice);
    void EnableActionSetPresetPrefix(CallbackJukebox1SetPresetPrefix aCallback, void* aPtr);
    void EnableActionPresetPrefix(CallbackJukebox1PresetPrefix aCallback, void* aPtr);
    void EnableActionSetAlbumArtFileName(CallbackJukebox1SetAlbumArtFileName aCallback, void* aPtr);
    void EnableActionAlbumArtFileName(CallbackJukebox1AlbumArtFileName aCallback, void* aPtr);
    void EnableActionSetCurrentPreset(CallbackJukebox1SetCurrentPreset aCallback, void* aPtr);
    void EnableActionCurrentPreset(CallbackJukebox1CurrentPreset aCallback, void* aPtr);
    void EnableActionPresetMetaData(CallbackJukebox1PresetMetaData aCallback, void* aPtr);
    void EnableActionLoadManifest(CallbackJukebox1LoadManifest aCallback, void* aPtr);
private:
    void SetPresetPrefix(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaUri);
    void PresetPrefix(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUri);
    void SetAlbumArtFileName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaName);
    void AlbumArtFileName(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaName);
    void SetCurrentPreset(IInvocationResponse& aResponse, TUint aVersion, TUint aaPreset);
    void CurrentPreset(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPreset);
    void PresetMetaData(IInvocationResponse& aResponse, TUint aVersion, TUint aaPreset, IInvocationResponseString& aaMetaData);
    void LoadManifest(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTotalPresets);
private:
    CallbackJukebox1SetPresetPrefix iCallbackSetPresetPrefix;
    void* iPtrSetPresetPrefix;
    CallbackJukebox1PresetPrefix iCallbackPresetPrefix;
    void* iPtrPresetPrefix;
    CallbackJukebox1SetAlbumArtFileName iCallbackSetAlbumArtFileName;
    void* iPtrSetAlbumArtFileName;
    CallbackJukebox1AlbumArtFileName iCallbackAlbumArtFileName;
    void* iPtrAlbumArtFileName;
    CallbackJukebox1SetCurrentPreset iCallbackSetCurrentPreset;
    void* iPtrSetCurrentPreset;
    CallbackJukebox1CurrentPreset iCallbackCurrentPreset;
    void* iPtrCurrentPreset;
    CallbackJukebox1PresetMetaData iCallbackPresetMetaData;
    void* iPtrPresetMetaData;
    CallbackJukebox1LoadManifest iCallbackLoadManifest;
    void* iPtrLoadManifest;
};

DvProviderLinnCoUkJukebox1C::DvProviderLinnCoUkJukebox1C(DvDevice& aDevice)
    : DvProviderLinnCoUkJukebox1(aDevice)
{
}

void DvProviderLinnCoUkJukebox1C::EnableActionSetPresetPrefix(CallbackJukebox1SetPresetPrefix aCallback, void* aPtr)
{
    iCallbackSetPresetPrefix = aCallback;
    iPtrSetPresetPrefix = aPtr;
    DvProviderLinnCoUkJukebox1::EnableActionSetPresetPrefix();
}

void DvProviderLinnCoUkJukebox1C::EnableActionPresetPrefix(CallbackJukebox1PresetPrefix aCallback, void* aPtr)
{
    iCallbackPresetPrefix = aCallback;
    iPtrPresetPrefix = aPtr;
    DvProviderLinnCoUkJukebox1::EnableActionPresetPrefix();
}

void DvProviderLinnCoUkJukebox1C::EnableActionSetAlbumArtFileName(CallbackJukebox1SetAlbumArtFileName aCallback, void* aPtr)
{
    iCallbackSetAlbumArtFileName = aCallback;
    iPtrSetAlbumArtFileName = aPtr;
    DvProviderLinnCoUkJukebox1::EnableActionSetAlbumArtFileName();
}

void DvProviderLinnCoUkJukebox1C::EnableActionAlbumArtFileName(CallbackJukebox1AlbumArtFileName aCallback, void* aPtr)
{
    iCallbackAlbumArtFileName = aCallback;
    iPtrAlbumArtFileName = aPtr;
    DvProviderLinnCoUkJukebox1::EnableActionAlbumArtFileName();
}

void DvProviderLinnCoUkJukebox1C::EnableActionSetCurrentPreset(CallbackJukebox1SetCurrentPreset aCallback, void* aPtr)
{
    iCallbackSetCurrentPreset = aCallback;
    iPtrSetCurrentPreset = aPtr;
    DvProviderLinnCoUkJukebox1::EnableActionSetCurrentPreset();
}

void DvProviderLinnCoUkJukebox1C::EnableActionCurrentPreset(CallbackJukebox1CurrentPreset aCallback, void* aPtr)
{
    iCallbackCurrentPreset = aCallback;
    iPtrCurrentPreset = aPtr;
    DvProviderLinnCoUkJukebox1::EnableActionCurrentPreset();
}

void DvProviderLinnCoUkJukebox1C::EnableActionPresetMetaData(CallbackJukebox1PresetMetaData aCallback, void* aPtr)
{
    iCallbackPresetMetaData = aCallback;
    iPtrPresetMetaData = aPtr;
    DvProviderLinnCoUkJukebox1::EnableActionPresetMetaData();
}

void DvProviderLinnCoUkJukebox1C::EnableActionLoadManifest(CallbackJukebox1LoadManifest aCallback, void* aPtr)
{
    iCallbackLoadManifest = aCallback;
    iPtrLoadManifest = aPtr;
    DvProviderLinnCoUkJukebox1::EnableActionLoadManifest();
}

void DvProviderLinnCoUkJukebox1C::SetPresetPrefix(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaUri)
{
    ASSERT(iCallbackSetPresetPrefix != NULL);
    if (0 != iCallbackSetPresetPrefix(iPtrSetPresetPrefix, aVersion, (const char*)aaUri.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkJukebox1C::PresetPrefix(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUri)
{
    char* aUri;
    ASSERT(iCallbackPresetPrefix != NULL);
    if (0 != iCallbackPresetPrefix(iPtrPresetPrefix, aVersion, &aUri)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaUri((const TChar*)aUri);
    ZappFreeExternal(aUri);
    aaUri.Write(bufaUri);
    aaUri.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkJukebox1C::SetAlbumArtFileName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaName)
{
    ASSERT(iCallbackSetAlbumArtFileName != NULL);
    if (0 != iCallbackSetAlbumArtFileName(iPtrSetAlbumArtFileName, aVersion, (const char*)aaName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkJukebox1C::AlbumArtFileName(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaName)
{
    char* aName;
    ASSERT(iCallbackAlbumArtFileName != NULL);
    if (0 != iCallbackAlbumArtFileName(iPtrAlbumArtFileName, aVersion, &aName)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaName((const TChar*)aName);
    ZappFreeExternal(aName);
    aaName.Write(bufaName);
    aaName.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkJukebox1C::SetCurrentPreset(IInvocationResponse& aResponse, TUint aVersion, TUint aaPreset)
{
    ASSERT(iCallbackSetCurrentPreset != NULL);
    if (0 != iCallbackSetCurrentPreset(iPtrSetCurrentPreset, aVersion, aaPreset)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkJukebox1C::CurrentPreset(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPreset)
{
    uint32_t aPreset;
    ASSERT(iCallbackCurrentPreset != NULL);
    if (0 != iCallbackCurrentPreset(iPtrCurrentPreset, aVersion, &aPreset)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaPreset.Write(aPreset);
    aResponse.End();
}

void DvProviderLinnCoUkJukebox1C::PresetMetaData(IInvocationResponse& aResponse, TUint aVersion, TUint aaPreset, IInvocationResponseString& aaMetaData)
{
    char* aMetaData;
    ASSERT(iCallbackPresetMetaData != NULL);
    if (0 != iCallbackPresetMetaData(iPtrPresetMetaData, aVersion, aaPreset, &aMetaData)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaMetaData((const TChar*)aMetaData);
    ZappFreeExternal(aMetaData);
    aaMetaData.Write(bufaMetaData);
    aaMetaData.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkJukebox1C::LoadManifest(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTotalPresets)
{
    uint32_t aTotalPresets;
    ASSERT(iCallbackLoadManifest != NULL);
    if (0 != iCallbackLoadManifest(iPtrLoadManifest, aVersion, &aTotalPresets)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaTotalPresets.Write(aTotalPresets);
    aResponse.End();
}



THandle DvProviderLinnCoUkJukebox1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkJukebox1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkJukebox1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider);
}

void DvProviderLinnCoUkJukebox1EnableActionSetPresetPrefix(THandle aProvider, CallbackJukebox1SetPresetPrefix aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider)->EnableActionSetPresetPrefix(aCallback, aPtr);
}

void DvProviderLinnCoUkJukebox1EnableActionPresetPrefix(THandle aProvider, CallbackJukebox1PresetPrefix aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider)->EnableActionPresetPrefix(aCallback, aPtr);
}

void DvProviderLinnCoUkJukebox1EnableActionSetAlbumArtFileName(THandle aProvider, CallbackJukebox1SetAlbumArtFileName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider)->EnableActionSetAlbumArtFileName(aCallback, aPtr);
}

void DvProviderLinnCoUkJukebox1EnableActionAlbumArtFileName(THandle aProvider, CallbackJukebox1AlbumArtFileName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider)->EnableActionAlbumArtFileName(aCallback, aPtr);
}

void DvProviderLinnCoUkJukebox1EnableActionSetCurrentPreset(THandle aProvider, CallbackJukebox1SetCurrentPreset aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider)->EnableActionSetCurrentPreset(aCallback, aPtr);
}

void DvProviderLinnCoUkJukebox1EnableActionCurrentPreset(THandle aProvider, CallbackJukebox1CurrentPreset aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider)->EnableActionCurrentPreset(aCallback, aPtr);
}

void DvProviderLinnCoUkJukebox1EnableActionPresetMetaData(THandle aProvider, CallbackJukebox1PresetMetaData aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider)->EnableActionPresetMetaData(aCallback, aPtr);
}

void DvProviderLinnCoUkJukebox1EnableActionLoadManifest(THandle aProvider, CallbackJukebox1LoadManifest aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider)->EnableActionLoadManifest(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkJukebox1SetPropertyCurrentPreset(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider)->SetPropertyCurrentPreset(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkJukebox1GetPropertyCurrentPreset(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider)->GetPropertyCurrentPreset(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkJukebox1SetPropertyPresetPrefix(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider)->SetPropertyPresetPrefix(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkJukebox1GetPropertyPresetPrefix(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider)->GetPropertyPresetPrefix(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkJukebox1SetPropertyAlbumArtFileName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider)->SetPropertyAlbumArtFileName(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkJukebox1GetPropertyAlbumArtFileName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkJukebox1C*>(aProvider)->GetPropertyAlbumArtFileName(buf);
    *aValue = (char*)buf.Transfer();
}

