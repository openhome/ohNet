#include <Std/DvLinnCoUkJukebox1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkJukebox1Cpp::SetPropertyCurrentPreset(uint32_t aValue)
{
    SetPropertyUint(*iPropertyCurrentPreset, aValue);
}

void DvServiceLinnCoUkJukebox1Cpp::GetPropertyCurrentPreset(uint32_t& aValue)
{
    aValue = iPropertyCurrentPreset->Value();
}

void DvServiceLinnCoUkJukebox1Cpp::SetPropertyPresetPrefix(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyPresetPrefix, buf);
}

void DvServiceLinnCoUkJukebox1Cpp::GetPropertyPresetPrefix(std::string& aValue)
{
    const Brx& val = iPropertyPresetPrefix->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkJukebox1Cpp::SetPropertyAlbumArtFileName(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyAlbumArtFileName, buf);
}

void DvServiceLinnCoUkJukebox1Cpp::GetPropertyAlbumArtFileName(std::string& aValue)
{
    const Brx& val = iPropertyAlbumArtFileName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvServiceLinnCoUkJukebox1Cpp::DvServiceLinnCoUkJukebox1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Jukebox", 1)
{
    Functor empty;
    iPropertyCurrentPreset = new PropertyUint(new ParameterUint("CurrentPreset"), empty);
    iService->AddProperty(iPropertyCurrentPreset); // passes ownership
    iPropertyPresetPrefix = new PropertyString(new ParameterString("PresetPrefix"), empty);
    iService->AddProperty(iPropertyPresetPrefix); // passes ownership
    iPropertyAlbumArtFileName = new PropertyString(new ParameterString("AlbumArtFileName"), empty);
    iService->AddProperty(iPropertyAlbumArtFileName); // passes ownership
}

void DvServiceLinnCoUkJukebox1Cpp::EnableActionSetPresetPrefix()
{
    Zapp::Action* action = new Zapp::Action("SetPresetPrefix");
    action->AddInputParameter(new ParameterRelated("aUri", *iPropertyPresetPrefix));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkJukebox1Cpp::DoSetPresetPrefix);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkJukebox1Cpp::EnableActionPresetPrefix()
{
    Zapp::Action* action = new Zapp::Action("PresetPrefix");
    action->AddOutputParameter(new ParameterRelated("aUri", *iPropertyPresetPrefix));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkJukebox1Cpp::DoPresetPrefix);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkJukebox1Cpp::EnableActionSetAlbumArtFileName()
{
    Zapp::Action* action = new Zapp::Action("SetAlbumArtFileName");
    action->AddInputParameter(new ParameterRelated("aName", *iPropertyAlbumArtFileName));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkJukebox1Cpp::DoSetAlbumArtFileName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkJukebox1Cpp::EnableActionAlbumArtFileName()
{
    Zapp::Action* action = new Zapp::Action("AlbumArtFileName");
    action->AddOutputParameter(new ParameterRelated("aName", *iPropertyAlbumArtFileName));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkJukebox1Cpp::DoAlbumArtFileName);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkJukebox1Cpp::EnableActionSetCurrentPreset()
{
    Zapp::Action* action = new Zapp::Action("SetCurrentPreset");
    action->AddInputParameter(new ParameterRelated("aPreset", *iPropertyCurrentPreset));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkJukebox1Cpp::DoSetCurrentPreset);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkJukebox1Cpp::EnableActionCurrentPreset()
{
    Zapp::Action* action = new Zapp::Action("CurrentPreset");
    action->AddOutputParameter(new ParameterRelated("aPreset", *iPropertyCurrentPreset));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkJukebox1Cpp::DoCurrentPreset);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkJukebox1Cpp::EnableActionPresetMetaData()
{
    Zapp::Action* action = new Zapp::Action("PresetMetaData");
    action->AddInputParameter(new ParameterRelated("aPreset", *iPropertyCurrentPreset));
    action->AddOutputParameter(new ParameterString("aMetaData"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkJukebox1Cpp::DoPresetMetaData);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkJukebox1Cpp::EnableActionLoadManifest()
{
    Zapp::Action* action = new Zapp::Action("LoadManifest");
    action->AddOutputParameter(new ParameterRelated("aTotalPresets", *iPropertyCurrentPreset));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkJukebox1Cpp::DoLoadManifest);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkJukebox1Cpp::DoSetPresetPrefix(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aUri;
    aInvocation.InvocationReadString("aUri", buf_aUri);
    std::string aUri((const char*)buf_aUri.Ptr(), buf_aUri.Bytes());
    aInvocation.InvocationReadEnd();
    SetPresetPrefix(aVersion, aUri);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkJukebox1Cpp::DoPresetPrefix(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaUri;
    PresetPrefix(aVersion, respaUri);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraUri(aInvocation, "aUri");
    Brn buf_aUri((const TByte*)respaUri.c_str(), respaUri.length());
    respWriteraUri.Write(buf_aUri);
    aInvocation.InvocationWriteStringEnd("aUri");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkJukebox1Cpp::DoSetAlbumArtFileName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aName;
    aInvocation.InvocationReadString("aName", buf_aName);
    std::string aName((const char*)buf_aName.Ptr(), buf_aName.Bytes());
    aInvocation.InvocationReadEnd();
    SetAlbumArtFileName(aVersion, aName);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkJukebox1Cpp::DoAlbumArtFileName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaName;
    AlbumArtFileName(aVersion, respaName);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraName(aInvocation, "aName");
    Brn buf_aName((const TByte*)respaName.c_str(), respaName.length());
    respWriteraName.Write(buf_aName);
    aInvocation.InvocationWriteStringEnd("aName");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkJukebox1Cpp::DoSetCurrentPreset(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aPreset = aInvocation.InvocationReadUint("aPreset");
    aInvocation.InvocationReadEnd();
    SetCurrentPreset(aVersion, aPreset);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkJukebox1Cpp::DoCurrentPreset(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaPreset;
    CurrentPreset(aVersion, respaPreset);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraPreset(aInvocation, "aPreset");
    respWriteraPreset.Write(respaPreset);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkJukebox1Cpp::DoPresetMetaData(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aPreset = aInvocation.InvocationReadUint("aPreset");
    aInvocation.InvocationReadEnd();
    std::string respaMetaData;
    PresetMetaData(aVersion, aPreset, respaMetaData);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraMetaData(aInvocation, "aMetaData");
    Brn buf_aMetaData((const TByte*)respaMetaData.c_str(), respaMetaData.length());
    respWriteraMetaData.Write(buf_aMetaData);
    aInvocation.InvocationWriteStringEnd("aMetaData");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkJukebox1Cpp::DoLoadManifest(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaTotalPresets;
    LoadManifest(aVersion, respaTotalPresets);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraTotalPresets(aInvocation, "aTotalPresets");
    respWriteraTotalPresets.Write(respaTotalPresets);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkJukebox1Cpp::SetPresetPrefix(uint32_t /*aVersion*/, const std::string& /*aaUri*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkJukebox1Cpp::PresetPrefix(uint32_t /*aVersion*/, std::string& /*aaUri*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkJukebox1Cpp::SetAlbumArtFileName(uint32_t /*aVersion*/, const std::string& /*aaName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkJukebox1Cpp::AlbumArtFileName(uint32_t /*aVersion*/, std::string& /*aaName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkJukebox1Cpp::SetCurrentPreset(uint32_t /*aVersion*/, uint32_t /*aaPreset*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkJukebox1Cpp::CurrentPreset(uint32_t /*aVersion*/, uint32_t& /*aaPreset*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkJukebox1Cpp::PresetMetaData(uint32_t /*aVersion*/, uint32_t /*aaPreset*/, std::string& /*aaMetaData*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkJukebox1Cpp::LoadManifest(uint32_t /*aVersion*/, uint32_t& /*aaTotalPresets*/)
{
    ASSERTS();
}

