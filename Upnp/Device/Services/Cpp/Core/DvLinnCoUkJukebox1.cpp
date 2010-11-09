#include <Core/DvLinnCoUkJukebox1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkJukebox1::SetPropertyCurrentPreset(TUint aValue)
{
    return SetPropertyUint(*iPropertyCurrentPreset, aValue);
}

void DvProviderLinnCoUkJukebox1::GetPropertyCurrentPreset(TUint& aValue)
{
    aValue = iPropertyCurrentPreset->Value();
}

TBool DvProviderLinnCoUkJukebox1::SetPropertyPresetPrefix(const Brx& aValue)
{
    return SetPropertyString(*iPropertyPresetPrefix, aValue);
}

void DvProviderLinnCoUkJukebox1::GetPropertyPresetPrefix(Brhz& aValue)
{
    aValue.Set(iPropertyPresetPrefix->Value());
}

TBool DvProviderLinnCoUkJukebox1::SetPropertyAlbumArtFileName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyAlbumArtFileName, aValue);
}

void DvProviderLinnCoUkJukebox1::GetPropertyAlbumArtFileName(Brhz& aValue)
{
    aValue.Set(iPropertyAlbumArtFileName->Value());
}

DvProviderLinnCoUkJukebox1::DvProviderLinnCoUkJukebox1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Jukebox", 1)
{
    Functor empty;
    iPropertyCurrentPreset = new PropertyUint(new ParameterUint("CurrentPreset"), empty);
    iService->AddProperty(iPropertyCurrentPreset); // passes ownership
    iPropertyPresetPrefix = new PropertyString(new ParameterString("PresetPrefix"), empty);
    iService->AddProperty(iPropertyPresetPrefix); // passes ownership
    iPropertyAlbumArtFileName = new PropertyString(new ParameterString("AlbumArtFileName"), empty);
    iService->AddProperty(iPropertyAlbumArtFileName); // passes ownership
}

void DvProviderLinnCoUkJukebox1::EnableActionSetPresetPrefix()
{
    Zapp::Action* action = new Zapp::Action("SetPresetPrefix");
    action->AddInputParameter(new ParameterRelated("aUri", *iPropertyPresetPrefix));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkJukebox1::DoSetPresetPrefix);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1::EnableActionPresetPrefix()
{
    Zapp::Action* action = new Zapp::Action("PresetPrefix");
    action->AddOutputParameter(new ParameterRelated("aUri", *iPropertyPresetPrefix));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkJukebox1::DoPresetPrefix);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1::EnableActionSetAlbumArtFileName()
{
    Zapp::Action* action = new Zapp::Action("SetAlbumArtFileName");
    action->AddInputParameter(new ParameterRelated("aName", *iPropertyAlbumArtFileName));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkJukebox1::DoSetAlbumArtFileName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1::EnableActionAlbumArtFileName()
{
    Zapp::Action* action = new Zapp::Action("AlbumArtFileName");
    action->AddOutputParameter(new ParameterRelated("aName", *iPropertyAlbumArtFileName));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkJukebox1::DoAlbumArtFileName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1::EnableActionSetCurrentPreset()
{
    Zapp::Action* action = new Zapp::Action("SetCurrentPreset");
    action->AddInputParameter(new ParameterRelated("aPreset", *iPropertyCurrentPreset));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkJukebox1::DoSetCurrentPreset);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1::EnableActionCurrentPreset()
{
    Zapp::Action* action = new Zapp::Action("CurrentPreset");
    action->AddOutputParameter(new ParameterRelated("aPreset", *iPropertyCurrentPreset));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkJukebox1::DoCurrentPreset);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1::EnableActionPresetMetaData()
{
    Zapp::Action* action = new Zapp::Action("PresetMetaData");
    action->AddInputParameter(new ParameterRelated("aPreset", *iPropertyCurrentPreset));
    action->AddOutputParameter(new ParameterString("aMetaData"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkJukebox1::DoPresetMetaData);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1::EnableActionLoadManifest()
{
    Zapp::Action* action = new Zapp::Action("LoadManifest");
    action->AddOutputParameter(new ParameterRelated("aTotalPresets", *iPropertyCurrentPreset));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkJukebox1::DoLoadManifest);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkJukebox1::DoSetPresetPrefix(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aUri;
    aInvocation.InvocationReadString("aUri", aUri);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetPresetPrefix(resp, aVersion, aUri);
}

void DvProviderLinnCoUkJukebox1::DoPresetPrefix(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaUri(aInvocation, "aUri");
    PresetPrefix(resp, aVersion, respaUri);
}

void DvProviderLinnCoUkJukebox1::DoSetAlbumArtFileName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aName;
    aInvocation.InvocationReadString("aName", aName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetAlbumArtFileName(resp, aVersion, aName);
}

void DvProviderLinnCoUkJukebox1::DoAlbumArtFileName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaName(aInvocation, "aName");
    AlbumArtFileName(resp, aVersion, respaName);
}

void DvProviderLinnCoUkJukebox1::DoSetCurrentPreset(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aPreset = aInvocation.InvocationReadUint("aPreset");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetCurrentPreset(resp, aVersion, aPreset);
}

void DvProviderLinnCoUkJukebox1::DoCurrentPreset(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaPreset(aInvocation, "aPreset");
    CurrentPreset(resp, aVersion, respaPreset);
}

void DvProviderLinnCoUkJukebox1::DoPresetMetaData(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aPreset = aInvocation.InvocationReadUint("aPreset");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaMetaData(aInvocation, "aMetaData");
    PresetMetaData(resp, aVersion, aPreset, respaMetaData);
}

void DvProviderLinnCoUkJukebox1::DoLoadManifest(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaTotalPresets(aInvocation, "aTotalPresets");
    LoadManifest(resp, aVersion, respaTotalPresets);
}

void DvProviderLinnCoUkJukebox1::SetPresetPrefix(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaUri*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkJukebox1::PresetPrefix(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaUri*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkJukebox1::SetAlbumArtFileName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkJukebox1::AlbumArtFileName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkJukebox1::SetCurrentPreset(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaPreset*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkJukebox1::CurrentPreset(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaPreset*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkJukebox1::PresetMetaData(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaPreset*/, IInvocationResponseString& /*aaMetaData*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkJukebox1::LoadManifest(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaTotalPresets*/)
{
    ASSERTS();
}

