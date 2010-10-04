#include <C/DvLinnCoUkJukebox1.h>
#include <Core/DvLinnCoUkJukebox1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkJukebox1C : public DvServiceLinnCoUkJukebox1
{
public:
    DvServiceLinnCoUkJukebox1C(DvDevice& aDevice);
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

DvServiceLinnCoUkJukebox1C::DvServiceLinnCoUkJukebox1C(DvDevice& aDevice)
    : DvServiceLinnCoUkJukebox1(aDevice)
{
}

void DvServiceLinnCoUkJukebox1C::EnableActionSetPresetPrefix(CallbackJukebox1SetPresetPrefix aCallback, void* aPtr)
{
    iCallbackSetPresetPrefix = aCallback;
    iPtrSetPresetPrefix = aPtr;
    DvServiceLinnCoUkJukebox1::EnableActionSetPresetPrefix();
}

void DvServiceLinnCoUkJukebox1C::EnableActionPresetPrefix(CallbackJukebox1PresetPrefix aCallback, void* aPtr)
{
    iCallbackPresetPrefix = aCallback;
    iPtrPresetPrefix = aPtr;
    DvServiceLinnCoUkJukebox1::EnableActionPresetPrefix();
}

void DvServiceLinnCoUkJukebox1C::EnableActionSetAlbumArtFileName(CallbackJukebox1SetAlbumArtFileName aCallback, void* aPtr)
{
    iCallbackSetAlbumArtFileName = aCallback;
    iPtrSetAlbumArtFileName = aPtr;
    DvServiceLinnCoUkJukebox1::EnableActionSetAlbumArtFileName();
}

void DvServiceLinnCoUkJukebox1C::EnableActionAlbumArtFileName(CallbackJukebox1AlbumArtFileName aCallback, void* aPtr)
{
    iCallbackAlbumArtFileName = aCallback;
    iPtrAlbumArtFileName = aPtr;
    DvServiceLinnCoUkJukebox1::EnableActionAlbumArtFileName();
}

void DvServiceLinnCoUkJukebox1C::EnableActionSetCurrentPreset(CallbackJukebox1SetCurrentPreset aCallback, void* aPtr)
{
    iCallbackSetCurrentPreset = aCallback;
    iPtrSetCurrentPreset = aPtr;
    DvServiceLinnCoUkJukebox1::EnableActionSetCurrentPreset();
}

void DvServiceLinnCoUkJukebox1C::EnableActionCurrentPreset(CallbackJukebox1CurrentPreset aCallback, void* aPtr)
{
    iCallbackCurrentPreset = aCallback;
    iPtrCurrentPreset = aPtr;
    DvServiceLinnCoUkJukebox1::EnableActionCurrentPreset();
}

void DvServiceLinnCoUkJukebox1C::EnableActionPresetMetaData(CallbackJukebox1PresetMetaData aCallback, void* aPtr)
{
    iCallbackPresetMetaData = aCallback;
    iPtrPresetMetaData = aPtr;
    DvServiceLinnCoUkJukebox1::EnableActionPresetMetaData();
}

void DvServiceLinnCoUkJukebox1C::EnableActionLoadManifest(CallbackJukebox1LoadManifest aCallback, void* aPtr)
{
    iCallbackLoadManifest = aCallback;
    iPtrLoadManifest = aPtr;
    DvServiceLinnCoUkJukebox1::EnableActionLoadManifest();
}

void DvServiceLinnCoUkJukebox1C::SetPresetPrefix(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaUri)
{
    ASSERT(iCallbackSetPresetPrefix != NULL);
    if (0 != iCallbackSetPresetPrefix(iPtrSetPresetPrefix, aVersion, (const char*)aaUri.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkJukebox1C::PresetPrefix(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaUri)
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

void DvServiceLinnCoUkJukebox1C::SetAlbumArtFileName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaName)
{
    ASSERT(iCallbackSetAlbumArtFileName != NULL);
    if (0 != iCallbackSetAlbumArtFileName(iPtrSetAlbumArtFileName, aVersion, (const char*)aaName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkJukebox1C::AlbumArtFileName(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaName)
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

void DvServiceLinnCoUkJukebox1C::SetCurrentPreset(IInvocationResponse& aResponse, TUint aVersion, TUint aaPreset)
{
    ASSERT(iCallbackSetCurrentPreset != NULL);
    if (0 != iCallbackSetCurrentPreset(iPtrSetCurrentPreset, aVersion, aaPreset)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkJukebox1C::CurrentPreset(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPreset)
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

void DvServiceLinnCoUkJukebox1C::PresetMetaData(IInvocationResponse& aResponse, TUint aVersion, TUint aaPreset, IInvocationResponseString& aaMetaData)
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

void DvServiceLinnCoUkJukebox1C::LoadManifest(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTotalPresets)
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



THandle DvServiceLinnCoUkJukebox1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkJukebox1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkJukebox1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService);
}

void DvServiceLinnCoUkJukebox1EnableActionSetPresetPrefix(THandle aService, CallbackJukebox1SetPresetPrefix aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService)->EnableActionSetPresetPrefix(aCallback, aPtr);
}

void DvServiceLinnCoUkJukebox1EnableActionPresetPrefix(THandle aService, CallbackJukebox1PresetPrefix aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService)->EnableActionPresetPrefix(aCallback, aPtr);
}

void DvServiceLinnCoUkJukebox1EnableActionSetAlbumArtFileName(THandle aService, CallbackJukebox1SetAlbumArtFileName aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService)->EnableActionSetAlbumArtFileName(aCallback, aPtr);
}

void DvServiceLinnCoUkJukebox1EnableActionAlbumArtFileName(THandle aService, CallbackJukebox1AlbumArtFileName aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService)->EnableActionAlbumArtFileName(aCallback, aPtr);
}

void DvServiceLinnCoUkJukebox1EnableActionSetCurrentPreset(THandle aService, CallbackJukebox1SetCurrentPreset aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService)->EnableActionSetCurrentPreset(aCallback, aPtr);
}

void DvServiceLinnCoUkJukebox1EnableActionCurrentPreset(THandle aService, CallbackJukebox1CurrentPreset aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService)->EnableActionCurrentPreset(aCallback, aPtr);
}

void DvServiceLinnCoUkJukebox1EnableActionPresetMetaData(THandle aService, CallbackJukebox1PresetMetaData aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService)->EnableActionPresetMetaData(aCallback, aPtr);
}

void DvServiceLinnCoUkJukebox1EnableActionLoadManifest(THandle aService, CallbackJukebox1LoadManifest aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService)->EnableActionLoadManifest(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkJukebox1SetPropertyCurrentPreset(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService)->SetPropertyCurrentPreset(aValue);
    return 0;
}

void DvServiceLinnCoUkJukebox1GetPropertyCurrentPreset(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService)->GetPropertyCurrentPreset(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkJukebox1SetPropertyPresetPrefix(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService)->SetPropertyPresetPrefix(buf);
    return 0;
}

void DvServiceLinnCoUkJukebox1GetPropertyPresetPrefix(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService)->GetPropertyPresetPrefix(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkJukebox1SetPropertyAlbumArtFileName(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService)->SetPropertyAlbumArtFileName(buf);
    return 0;
}

void DvServiceLinnCoUkJukebox1GetPropertyAlbumArtFileName(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkJukebox1C*>(aService)->GetPropertyAlbumArtFileName(buf);
    *aValue = (char*)buf.Transfer();
}

