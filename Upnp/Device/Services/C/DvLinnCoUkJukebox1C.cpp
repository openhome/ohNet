#include "DvLinnCoUkJukebox1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

class DvProviderLinnCoUkJukebox1C : public DvProvider
{
public:
    DvProviderLinnCoUkJukebox1C(DvDeviceC aDevice);
    TBool SetPropertyCurrentPreset(TUint aValue);
    void GetPropertyCurrentPreset(TUint& aValue);
    TBool SetPropertyPresetPrefix(const Brx& aValue);
    void GetPropertyPresetPrefix(Brhz& aValue);
    TBool SetPropertyAlbumArtFileName(const Brx& aValue);
    void GetPropertyAlbumArtFileName(Brhz& aValue);
    void EnableActionSetPresetPrefix(CallbackJukebox1SetPresetPrefix aCallback, void* aPtr);
    void EnableActionPresetPrefix(CallbackJukebox1PresetPrefix aCallback, void* aPtr);
    void EnableActionSetAlbumArtFileName(CallbackJukebox1SetAlbumArtFileName aCallback, void* aPtr);
    void EnableActionAlbumArtFileName(CallbackJukebox1AlbumArtFileName aCallback, void* aPtr);
    void EnableActionSetCurrentPreset(CallbackJukebox1SetCurrentPreset aCallback, void* aPtr);
    void EnableActionCurrentPreset(CallbackJukebox1CurrentPreset aCallback, void* aPtr);
    void EnableActionPresetMetaData(CallbackJukebox1PresetMetaData aCallback, void* aPtr);
    void EnableActionLoadManifest(CallbackJukebox1LoadManifest aCallback, void* aPtr);
private:
    void DoSetPresetPrefix(IDviInvocation& aInvocation, TUint aVersion);
    void DoPresetPrefix(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetAlbumArtFileName(IDviInvocation& aInvocation, TUint aVersion);
    void DoAlbumArtFileName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetCurrentPreset(IDviInvocation& aInvocation, TUint aVersion);
    void DoCurrentPreset(IDviInvocation& aInvocation, TUint aVersion);
    void DoPresetMetaData(IDviInvocation& aInvocation, TUint aVersion);
    void DoLoadManifest(IDviInvocation& aInvocation, TUint aVersion);
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
    PropertyUint* iPropertyCurrentPreset;
    PropertyString* iPropertyPresetPrefix;
    PropertyString* iPropertyAlbumArtFileName;
};

DvProviderLinnCoUkJukebox1C::DvProviderLinnCoUkJukebox1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Jukebox", 1)
{
    
    iPropertyCurrentPreset = new PropertyUint(new ParameterUint("CurrentPreset"));
    iService->AddProperty(iPropertyCurrentPreset); // passes ownership
    iPropertyPresetPrefix = new PropertyString(new ParameterString("PresetPrefix"));
    iService->AddProperty(iPropertyPresetPrefix); // passes ownership
    iPropertyAlbumArtFileName = new PropertyString(new ParameterString("AlbumArtFileName"));
    iService->AddProperty(iPropertyAlbumArtFileName); // passes ownership
}

TBool DvProviderLinnCoUkJukebox1C::SetPropertyCurrentPreset(TUint aValue)
{
    return SetPropertyUint(*iPropertyCurrentPreset, aValue);
}

void DvProviderLinnCoUkJukebox1C::GetPropertyCurrentPreset(TUint& aValue)
{
    aValue = iPropertyCurrentPreset->Value();
}

TBool DvProviderLinnCoUkJukebox1C::SetPropertyPresetPrefix(const Brx& aValue)
{
    return SetPropertyString(*iPropertyPresetPrefix, aValue);
}

void DvProviderLinnCoUkJukebox1C::GetPropertyPresetPrefix(Brhz& aValue)
{
    aValue.Set(iPropertyPresetPrefix->Value());
}

TBool DvProviderLinnCoUkJukebox1C::SetPropertyAlbumArtFileName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyAlbumArtFileName, aValue);
}

void DvProviderLinnCoUkJukebox1C::GetPropertyAlbumArtFileName(Brhz& aValue)
{
    aValue.Set(iPropertyAlbumArtFileName->Value());
}

void DvProviderLinnCoUkJukebox1C::EnableActionSetPresetPrefix(CallbackJukebox1SetPresetPrefix aCallback, void* aPtr)
{
    iCallbackSetPresetPrefix = aCallback;
    iPtrSetPresetPrefix = aPtr;
    Zapp::Action* action = new Zapp::Action("SetPresetPrefix");
    action->AddInputParameter(new ParameterRelated("aUri", *iPropertyPresetPrefix));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkJukebox1C::DoSetPresetPrefix);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1C::EnableActionPresetPrefix(CallbackJukebox1PresetPrefix aCallback, void* aPtr)
{
    iCallbackPresetPrefix = aCallback;
    iPtrPresetPrefix = aPtr;
    Zapp::Action* action = new Zapp::Action("PresetPrefix");
    action->AddOutputParameter(new ParameterRelated("aUri", *iPropertyPresetPrefix));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkJukebox1C::DoPresetPrefix);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1C::EnableActionSetAlbumArtFileName(CallbackJukebox1SetAlbumArtFileName aCallback, void* aPtr)
{
    iCallbackSetAlbumArtFileName = aCallback;
    iPtrSetAlbumArtFileName = aPtr;
    Zapp::Action* action = new Zapp::Action("SetAlbumArtFileName");
    action->AddInputParameter(new ParameterRelated("aName", *iPropertyAlbumArtFileName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkJukebox1C::DoSetAlbumArtFileName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1C::EnableActionAlbumArtFileName(CallbackJukebox1AlbumArtFileName aCallback, void* aPtr)
{
    iCallbackAlbumArtFileName = aCallback;
    iPtrAlbumArtFileName = aPtr;
    Zapp::Action* action = new Zapp::Action("AlbumArtFileName");
    action->AddOutputParameter(new ParameterRelated("aName", *iPropertyAlbumArtFileName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkJukebox1C::DoAlbumArtFileName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1C::EnableActionSetCurrentPreset(CallbackJukebox1SetCurrentPreset aCallback, void* aPtr)
{
    iCallbackSetCurrentPreset = aCallback;
    iPtrSetCurrentPreset = aPtr;
    Zapp::Action* action = new Zapp::Action("SetCurrentPreset");
    action->AddInputParameter(new ParameterRelated("aPreset", *iPropertyCurrentPreset));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkJukebox1C::DoSetCurrentPreset);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1C::EnableActionCurrentPreset(CallbackJukebox1CurrentPreset aCallback, void* aPtr)
{
    iCallbackCurrentPreset = aCallback;
    iPtrCurrentPreset = aPtr;
    Zapp::Action* action = new Zapp::Action("CurrentPreset");
    action->AddOutputParameter(new ParameterRelated("aPreset", *iPropertyCurrentPreset));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkJukebox1C::DoCurrentPreset);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1C::EnableActionPresetMetaData(CallbackJukebox1PresetMetaData aCallback, void* aPtr)
{
    iCallbackPresetMetaData = aCallback;
    iPtrPresetMetaData = aPtr;
    Zapp::Action* action = new Zapp::Action("PresetMetaData");
    action->AddInputParameter(new ParameterRelated("aPreset", *iPropertyCurrentPreset));
    action->AddOutputParameter(new ParameterString("aMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkJukebox1C::DoPresetMetaData);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1C::EnableActionLoadManifest(CallbackJukebox1LoadManifest aCallback, void* aPtr)
{
    iCallbackLoadManifest = aCallback;
    iPtrLoadManifest = aPtr;
    Zapp::Action* action = new Zapp::Action("LoadManifest");
    action->AddOutputParameter(new ParameterRelated("aTotalPresets", *iPropertyCurrentPreset));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkJukebox1C::DoLoadManifest);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1C::DoSetPresetPrefix(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aUri;
    aInvocation.InvocationReadString("aUri", aUri);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetPresetPrefix != NULL);
    if (0 != iCallbackSetPresetPrefix(iPtrSetPresetPrefix, aVersion, (const char*)aUri.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkJukebox1C::DoPresetPrefix(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aUri;
    ASSERT(iCallbackPresetPrefix != NULL);
    if (0 != iCallbackPresetPrefix(iPtrPresetPrefix, aVersion, &aUri)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaUri(aInvocation, "aUri");
    resp.Start();
    Brhz bufaUri((const TChar*)aUri);
    ZappFreeExternal(aUri);
    respaUri.Write(bufaUri);
    respaUri.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkJukebox1C::DoSetAlbumArtFileName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aName;
    aInvocation.InvocationReadString("aName", aName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetAlbumArtFileName != NULL);
    if (0 != iCallbackSetAlbumArtFileName(iPtrSetAlbumArtFileName, aVersion, (const char*)aName.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkJukebox1C::DoAlbumArtFileName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aName;
    ASSERT(iCallbackAlbumArtFileName != NULL);
    if (0 != iCallbackAlbumArtFileName(iPtrAlbumArtFileName, aVersion, &aName)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaName(aInvocation, "aName");
    resp.Start();
    Brhz bufaName((const TChar*)aName);
    ZappFreeExternal(aName);
    respaName.Write(bufaName);
    respaName.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkJukebox1C::DoSetCurrentPreset(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aPreset = aInvocation.InvocationReadUint("aPreset");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetCurrentPreset != NULL);
    if (0 != iCallbackSetCurrentPreset(iPtrSetCurrentPreset, aVersion, aPreset)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkJukebox1C::DoCurrentPreset(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aPreset;
    ASSERT(iCallbackCurrentPreset != NULL);
    if (0 != iCallbackCurrentPreset(iPtrCurrentPreset, aVersion, &aPreset)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaPreset(aInvocation, "aPreset");
    resp.Start();
    respaPreset.Write(aPreset);
    resp.End();
}

void DvProviderLinnCoUkJukebox1C::DoPresetMetaData(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aPreset = aInvocation.InvocationReadUint("aPreset");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aMetaData;
    ASSERT(iCallbackPresetMetaData != NULL);
    if (0 != iCallbackPresetMetaData(iPtrPresetMetaData, aVersion, aPreset, &aMetaData)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaMetaData(aInvocation, "aMetaData");
    resp.Start();
    Brhz bufaMetaData((const TChar*)aMetaData);
    ZappFreeExternal(aMetaData);
    respaMetaData.Write(bufaMetaData);
    respaMetaData.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkJukebox1C::DoLoadManifest(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aTotalPresets;
    ASSERT(iCallbackLoadManifest != NULL);
    if (0 != iCallbackLoadManifest(iPtrLoadManifest, aVersion, &aTotalPresets)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaTotalPresets(aInvocation, "aTotalPresets");
    resp.Start();
    respaTotalPresets.Write(aTotalPresets);
    resp.End();
}



THandle DvProviderLinnCoUkJukebox1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkJukebox1C(aDevice);
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

