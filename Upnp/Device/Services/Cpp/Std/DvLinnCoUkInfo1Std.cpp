#include <Std/DvLinnCoUkInfo1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

bool DvProviderLinnCoUkInfo1Cpp::SetPropertyTrackCount(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvProviderLinnCoUkInfo1Cpp::GetPropertyTrackCount(uint32_t& aValue)
{
    aValue = iPropertyTrackCount->Value();
}

bool DvProviderLinnCoUkInfo1Cpp::SetPropertyDetailsCount(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyDetailsCount, aValue);
}

void DvProviderLinnCoUkInfo1Cpp::GetPropertyDetailsCount(uint32_t& aValue)
{
    aValue = iPropertyDetailsCount->Value();
}

bool DvProviderLinnCoUkInfo1Cpp::SetPropertyMetatextCount(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyMetatextCount, aValue);
}

void DvProviderLinnCoUkInfo1Cpp::GetPropertyMetatextCount(uint32_t& aValue)
{
    aValue = iPropertyMetatextCount->Value();
}

bool DvProviderLinnCoUkInfo1Cpp::SetPropertyUri(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyUri, buf);
}

void DvProviderLinnCoUkInfo1Cpp::GetPropertyUri(std::string& aValue)
{
    const Brx& val = iPropertyUri->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderLinnCoUkInfo1Cpp::SetPropertyMetadata(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyMetadata, buf);
}

void DvProviderLinnCoUkInfo1Cpp::GetPropertyMetadata(std::string& aValue)
{
    const Brx& val = iPropertyMetadata->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderLinnCoUkInfo1Cpp::SetPropertyDuration(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyDuration, aValue);
}

void DvProviderLinnCoUkInfo1Cpp::GetPropertyDuration(uint32_t& aValue)
{
    aValue = iPropertyDuration->Value();
}

bool DvProviderLinnCoUkInfo1Cpp::SetPropertyBitRate(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyBitRate, aValue);
}

void DvProviderLinnCoUkInfo1Cpp::GetPropertyBitRate(uint32_t& aValue)
{
    aValue = iPropertyBitRate->Value();
}

bool DvProviderLinnCoUkInfo1Cpp::SetPropertyBitDepth(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyBitDepth, aValue);
}

void DvProviderLinnCoUkInfo1Cpp::GetPropertyBitDepth(uint32_t& aValue)
{
    aValue = iPropertyBitDepth->Value();
}

bool DvProviderLinnCoUkInfo1Cpp::SetPropertySampleRate(uint32_t aValue)
{
    return SetPropertyUint(*iPropertySampleRate, aValue);
}

void DvProviderLinnCoUkInfo1Cpp::GetPropertySampleRate(uint32_t& aValue)
{
    aValue = iPropertySampleRate->Value();
}

bool DvProviderLinnCoUkInfo1Cpp::SetPropertyLossless(bool aValue)
{
    return SetPropertyBool(*iPropertyLossless, aValue);
}

void DvProviderLinnCoUkInfo1Cpp::GetPropertyLossless(bool& aValue)
{
    aValue = iPropertyLossless->Value();
}

bool DvProviderLinnCoUkInfo1Cpp::SetPropertyCodecName(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyCodecName, buf);
}

void DvProviderLinnCoUkInfo1Cpp::GetPropertyCodecName(std::string& aValue)
{
    const Brx& val = iPropertyCodecName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderLinnCoUkInfo1Cpp::SetPropertyMetatext(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyMetatext, buf);
}

void DvProviderLinnCoUkInfo1Cpp::GetPropertyMetatext(std::string& aValue)
{
    const Brx& val = iPropertyMetatext->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderLinnCoUkInfo1Cpp::DvProviderLinnCoUkInfo1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Info", 1)
{
    Functor empty;
    iPropertyTrackCount = new PropertyUint(new ParameterUint("TrackCount"), empty);
    iService->AddProperty(iPropertyTrackCount); // passes ownership
    iPropertyDetailsCount = new PropertyUint(new ParameterUint("DetailsCount"), empty);
    iService->AddProperty(iPropertyDetailsCount); // passes ownership
    iPropertyMetatextCount = new PropertyUint(new ParameterUint("MetatextCount"), empty);
    iService->AddProperty(iPropertyMetatextCount); // passes ownership
    iPropertyUri = new PropertyString(new ParameterString("Uri"), empty);
    iService->AddProperty(iPropertyUri); // passes ownership
    iPropertyMetadata = new PropertyString(new ParameterString("Metadata"), empty);
    iService->AddProperty(iPropertyMetadata); // passes ownership
    iPropertyDuration = new PropertyUint(new ParameterUint("Duration"), empty);
    iService->AddProperty(iPropertyDuration); // passes ownership
    iPropertyBitRate = new PropertyUint(new ParameterUint("BitRate"), empty);
    iService->AddProperty(iPropertyBitRate); // passes ownership
    iPropertyBitDepth = new PropertyUint(new ParameterUint("BitDepth"), empty);
    iService->AddProperty(iPropertyBitDepth); // passes ownership
    iPropertySampleRate = new PropertyUint(new ParameterUint("SampleRate"), empty);
    iService->AddProperty(iPropertySampleRate); // passes ownership
    iPropertyLossless = new PropertyBool(new ParameterBool("Lossless"), empty);
    iService->AddProperty(iPropertyLossless); // passes ownership
    iPropertyCodecName = new PropertyString(new ParameterString("CodecName"), empty);
    iService->AddProperty(iPropertyCodecName); // passes ownership
    iPropertyMetatext = new PropertyString(new ParameterString("Metatext"), empty);
    iService->AddProperty(iPropertyMetatext); // passes ownership
}

void DvProviderLinnCoUkInfo1Cpp::EnableActionCounters()
{
    Zapp::Action* action = new Zapp::Action("Counters");
    action->AddOutputParameter(new ParameterRelated("aTrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("aDetailsCount", *iPropertyDetailsCount));
    action->AddOutputParameter(new ParameterRelated("aMetatextCount", *iPropertyMetatextCount));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkInfo1Cpp::DoCounters);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkInfo1Cpp::EnableActionTrack()
{
    Zapp::Action* action = new Zapp::Action("Track");
    action->AddOutputParameter(new ParameterRelated("aUri", *iPropertyUri));
    action->AddOutputParameter(new ParameterRelated("aMetadata", *iPropertyMetadata));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkInfo1Cpp::DoTrack);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkInfo1Cpp::EnableActionDetails()
{
    Zapp::Action* action = new Zapp::Action("Details");
    action->AddOutputParameter(new ParameterRelated("aDuration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("aBitRate", *iPropertyBitRate));
    action->AddOutputParameter(new ParameterRelated("aBitDepth", *iPropertyBitDepth));
    action->AddOutputParameter(new ParameterRelated("aSampleRate", *iPropertySampleRate));
    action->AddOutputParameter(new ParameterRelated("aLossless", *iPropertyLossless));
    action->AddOutputParameter(new ParameterRelated("aCodecName", *iPropertyCodecName));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkInfo1Cpp::DoDetails);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkInfo1Cpp::EnableActionMetatext()
{
    Zapp::Action* action = new Zapp::Action("Metatext");
    action->AddOutputParameter(new ParameterRelated("aMetatext", *iPropertyMetatext));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkInfo1Cpp::DoMetatext);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkInfo1Cpp::DoCounters(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaTrackCount;
    uint32_t respaDetailsCount;
    uint32_t respaMetatextCount;
    Counters(aVersion, respaTrackCount, respaDetailsCount, respaMetatextCount);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraTrackCount(aInvocation, "aTrackCount");
    respWriteraTrackCount.Write(respaTrackCount);
    InvocationResponseUint respWriteraDetailsCount(aInvocation, "aDetailsCount");
    respWriteraDetailsCount.Write(respaDetailsCount);
    InvocationResponseUint respWriteraMetatextCount(aInvocation, "aMetatextCount");
    respWriteraMetatextCount.Write(respaMetatextCount);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkInfo1Cpp::DoTrack(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaUri;
    std::string respaMetadata;
    Track(aVersion, respaUri, respaMetadata);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraUri(aInvocation, "aUri");
    Brn buf_aUri((const TByte*)respaUri.c_str(), (TUint)respaUri.length());
    respWriteraUri.Write(buf_aUri);
    aInvocation.InvocationWriteStringEnd("aUri");
    InvocationResponseString respWriteraMetadata(aInvocation, "aMetadata");
    Brn buf_aMetadata((const TByte*)respaMetadata.c_str(), (TUint)respaMetadata.length());
    respWriteraMetadata.Write(buf_aMetadata);
    aInvocation.InvocationWriteStringEnd("aMetadata");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkInfo1Cpp::DoDetails(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaDuration;
    uint32_t respaBitRate;
    uint32_t respaBitDepth;
    uint32_t respaSampleRate;
    bool respaLossless;
    std::string respaCodecName;
    Details(aVersion, respaDuration, respaBitRate, respaBitDepth, respaSampleRate, respaLossless, respaCodecName);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraDuration(aInvocation, "aDuration");
    respWriteraDuration.Write(respaDuration);
    InvocationResponseUint respWriteraBitRate(aInvocation, "aBitRate");
    respWriteraBitRate.Write(respaBitRate);
    InvocationResponseUint respWriteraBitDepth(aInvocation, "aBitDepth");
    respWriteraBitDepth.Write(respaBitDepth);
    InvocationResponseUint respWriteraSampleRate(aInvocation, "aSampleRate");
    respWriteraSampleRate.Write(respaSampleRate);
    InvocationResponseBool respWriteraLossless(aInvocation, "aLossless");
    respWriteraLossless.Write(respaLossless);
    InvocationResponseString respWriteraCodecName(aInvocation, "aCodecName");
    Brn buf_aCodecName((const TByte*)respaCodecName.c_str(), (TUint)respaCodecName.length());
    respWriteraCodecName.Write(buf_aCodecName);
    aInvocation.InvocationWriteStringEnd("aCodecName");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkInfo1Cpp::DoMetatext(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaMetatext;
    Metatext(aVersion, respaMetatext);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraMetatext(aInvocation, "aMetatext");
    Brn buf_aMetatext((const TByte*)respaMetatext.c_str(), (TUint)respaMetatext.length());
    respWriteraMetatext.Write(buf_aMetatext);
    aInvocation.InvocationWriteStringEnd("aMetatext");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkInfo1Cpp::Counters(uint32_t /*aVersion*/, uint32_t& /*aaTrackCount*/, uint32_t& /*aaDetailsCount*/, uint32_t& /*aaMetatextCount*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkInfo1Cpp::Track(uint32_t /*aVersion*/, std::string& /*aaUri*/, std::string& /*aaMetadata*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkInfo1Cpp::Details(uint32_t /*aVersion*/, uint32_t& /*aaDuration*/, uint32_t& /*aaBitRate*/, uint32_t& /*aaBitDepth*/, uint32_t& /*aaSampleRate*/, bool& /*aaLossless*/, std::string& /*aaCodecName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkInfo1Cpp::Metatext(uint32_t /*aVersion*/, std::string& /*aaMetatext*/)
{
    ASSERTS();
}

