#include "DvAvOpenhomeOrgInfo1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderAvOpenhomeOrgInfo1Cpp::SetPropertyTrackCount(uint32_t aValue)
{
    ASSERT(iPropertyTrackCount != NULL);
    return SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::GetPropertyTrackCount(uint32_t& aValue)
{
    ASSERT(iPropertyTrackCount != NULL);
    aValue = iPropertyTrackCount->Value();
}

bool DvProviderAvOpenhomeOrgInfo1Cpp::SetPropertyDetailsCount(uint32_t aValue)
{
    ASSERT(iPropertyDetailsCount != NULL);
    return SetPropertyUint(*iPropertyDetailsCount, aValue);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::GetPropertyDetailsCount(uint32_t& aValue)
{
    ASSERT(iPropertyDetailsCount != NULL);
    aValue = iPropertyDetailsCount->Value();
}

bool DvProviderAvOpenhomeOrgInfo1Cpp::SetPropertyMetatextCount(uint32_t aValue)
{
    ASSERT(iPropertyMetatextCount != NULL);
    return SetPropertyUint(*iPropertyMetatextCount, aValue);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::GetPropertyMetatextCount(uint32_t& aValue)
{
    ASSERT(iPropertyMetatextCount != NULL);
    aValue = iPropertyMetatextCount->Value();
}

bool DvProviderAvOpenhomeOrgInfo1Cpp::SetPropertyUri(const std::string& aValue)
{
    ASSERT(iPropertyUri != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyUri, buf);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::GetPropertyUri(std::string& aValue)
{
    ASSERT(iPropertyUri != NULL);
    const Brx& val = iPropertyUri->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgInfo1Cpp::SetPropertyMetadata(const std::string& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyMetadata, buf);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::GetPropertyMetadata(std::string& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    const Brx& val = iPropertyMetadata->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgInfo1Cpp::SetPropertyDuration(uint32_t aValue)
{
    ASSERT(iPropertyDuration != NULL);
    return SetPropertyUint(*iPropertyDuration, aValue);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::GetPropertyDuration(uint32_t& aValue)
{
    ASSERT(iPropertyDuration != NULL);
    aValue = iPropertyDuration->Value();
}

bool DvProviderAvOpenhomeOrgInfo1Cpp::SetPropertyBitRate(uint32_t aValue)
{
    ASSERT(iPropertyBitRate != NULL);
    return SetPropertyUint(*iPropertyBitRate, aValue);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::GetPropertyBitRate(uint32_t& aValue)
{
    ASSERT(iPropertyBitRate != NULL);
    aValue = iPropertyBitRate->Value();
}

bool DvProviderAvOpenhomeOrgInfo1Cpp::SetPropertyBitDepth(uint32_t aValue)
{
    ASSERT(iPropertyBitDepth != NULL);
    return SetPropertyUint(*iPropertyBitDepth, aValue);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::GetPropertyBitDepth(uint32_t& aValue)
{
    ASSERT(iPropertyBitDepth != NULL);
    aValue = iPropertyBitDepth->Value();
}

bool DvProviderAvOpenhomeOrgInfo1Cpp::SetPropertySampleRate(uint32_t aValue)
{
    ASSERT(iPropertySampleRate != NULL);
    return SetPropertyUint(*iPropertySampleRate, aValue);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::GetPropertySampleRate(uint32_t& aValue)
{
    ASSERT(iPropertySampleRate != NULL);
    aValue = iPropertySampleRate->Value();
}

bool DvProviderAvOpenhomeOrgInfo1Cpp::SetPropertyLossless(bool aValue)
{
    ASSERT(iPropertyLossless != NULL);
    return SetPropertyBool(*iPropertyLossless, aValue);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::GetPropertyLossless(bool& aValue)
{
    ASSERT(iPropertyLossless != NULL);
    aValue = iPropertyLossless->Value();
}

bool DvProviderAvOpenhomeOrgInfo1Cpp::SetPropertyCodecName(const std::string& aValue)
{
    ASSERT(iPropertyCodecName != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyCodecName, buf);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::GetPropertyCodecName(std::string& aValue)
{
    ASSERT(iPropertyCodecName != NULL);
    const Brx& val = iPropertyCodecName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgInfo1Cpp::SetPropertyMetatext(const std::string& aValue)
{
    ASSERT(iPropertyMetatext != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyMetatext, buf);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::GetPropertyMetatext(std::string& aValue)
{
    ASSERT(iPropertyMetatext != NULL);
    const Brx& val = iPropertyMetatext->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderAvOpenhomeOrgInfo1Cpp::DvProviderAvOpenhomeOrgInfo1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Info", 1)
{
    iPropertyTrackCount = NULL;
    iPropertyDetailsCount = NULL;
    iPropertyMetatextCount = NULL;
    iPropertyUri = NULL;
    iPropertyMetadata = NULL;
    iPropertyDuration = NULL;
    iPropertyBitRate = NULL;
    iPropertyBitDepth = NULL;
    iPropertySampleRate = NULL;
    iPropertyLossless = NULL;
    iPropertyCodecName = NULL;
    iPropertyMetatext = NULL;
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnablePropertyTrackCount()
{
    iPropertyTrackCount = new PropertyUint(iDvStack.Env(), new ParameterUint("TrackCount"));
    iService->AddProperty(iPropertyTrackCount); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnablePropertyDetailsCount()
{
    iPropertyDetailsCount = new PropertyUint(iDvStack.Env(), new ParameterUint("DetailsCount"));
    iService->AddProperty(iPropertyDetailsCount); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnablePropertyMetatextCount()
{
    iPropertyMetatextCount = new PropertyUint(iDvStack.Env(), new ParameterUint("MetatextCount"));
    iService->AddProperty(iPropertyMetatextCount); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnablePropertyUri()
{
    iPropertyUri = new PropertyString(iDvStack.Env(), new ParameterString("Uri"));
    iService->AddProperty(iPropertyUri); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnablePropertyMetadata()
{
    iPropertyMetadata = new PropertyString(iDvStack.Env(), new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnablePropertyDuration()
{
    iPropertyDuration = new PropertyUint(iDvStack.Env(), new ParameterUint("Duration"));
    iService->AddProperty(iPropertyDuration); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnablePropertyBitRate()
{
    iPropertyBitRate = new PropertyUint(iDvStack.Env(), new ParameterUint("BitRate"));
    iService->AddProperty(iPropertyBitRate); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnablePropertyBitDepth()
{
    iPropertyBitDepth = new PropertyUint(iDvStack.Env(), new ParameterUint("BitDepth"));
    iService->AddProperty(iPropertyBitDepth); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnablePropertySampleRate()
{
    iPropertySampleRate = new PropertyUint(iDvStack.Env(), new ParameterUint("SampleRate"));
    iService->AddProperty(iPropertySampleRate); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnablePropertyLossless()
{
    iPropertyLossless = new PropertyBool(iDvStack.Env(), new ParameterBool("Lossless"));
    iService->AddProperty(iPropertyLossless); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnablePropertyCodecName()
{
    iPropertyCodecName = new PropertyString(iDvStack.Env(), new ParameterString("CodecName"));
    iService->AddProperty(iPropertyCodecName); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnablePropertyMetatext()
{
    iPropertyMetatext = new PropertyString(iDvStack.Env(), new ParameterString("Metatext"));
    iService->AddProperty(iPropertyMetatext); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnableActionCounters()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Counters");
    action->AddOutputParameter(new ParameterRelated("TrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("DetailsCount", *iPropertyDetailsCount));
    action->AddOutputParameter(new ParameterRelated("MetatextCount", *iPropertyMetatextCount));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgInfo1Cpp::DoCounters);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnableActionTrack()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Track");
    action->AddOutputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgInfo1Cpp::DoTrack);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnableActionDetails()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Details");
    action->AddOutputParameter(new ParameterRelated("Duration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("BitRate", *iPropertyBitRate));
    action->AddOutputParameter(new ParameterRelated("BitDepth", *iPropertyBitDepth));
    action->AddOutputParameter(new ParameterRelated("SampleRate", *iPropertySampleRate));
    action->AddOutputParameter(new ParameterRelated("Lossless", *iPropertyLossless));
    action->AddOutputParameter(new ParameterRelated("CodecName", *iPropertyCodecName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgInfo1Cpp::DoDetails);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::EnableActionMetatext()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Metatext");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyMetatext));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgInfo1Cpp::DoMetatext);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgInfo1Cpp::DoCounters(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respTrackCount;
    uint32_t respDetailsCount;
    uint32_t respMetatextCount;
    DvInvocationStd invocation(aInvocation);
    Counters(invocation, respTrackCount, respDetailsCount, respMetatextCount);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterTrackCount(aInvocation, "TrackCount");
    respWriterTrackCount.Write(respTrackCount);
    DviInvocationResponseUint respWriterDetailsCount(aInvocation, "DetailsCount");
    respWriterDetailsCount.Write(respDetailsCount);
    DviInvocationResponseUint respWriterMetatextCount(aInvocation, "MetatextCount");
    respWriterMetatextCount.Write(respMetatextCount);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgInfo1Cpp::DoTrack(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respUri;
    std::string respMetadata;
    DvInvocationStd invocation(aInvocation);
    Track(invocation, respUri, respMetadata);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterUri(aInvocation, "Uri");
    Brn buf_Uri((const TByte*)respUri.c_str(), (TUint)respUri.length());
    respWriterUri.Write(buf_Uri);
    aInvocation.InvocationWriteStringEnd("Uri");
    DviInvocationResponseString respWriterMetadata(aInvocation, "Metadata");
    Brn buf_Metadata((const TByte*)respMetadata.c_str(), (TUint)respMetadata.length());
    respWriterMetadata.Write(buf_Metadata);
    aInvocation.InvocationWriteStringEnd("Metadata");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgInfo1Cpp::DoDetails(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respDuration;
    uint32_t respBitRate;
    uint32_t respBitDepth;
    uint32_t respSampleRate;
    bool respLossless;
    std::string respCodecName;
    DvInvocationStd invocation(aInvocation);
    Details(invocation, respDuration, respBitRate, respBitDepth, respSampleRate, respLossless, respCodecName);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterDuration(aInvocation, "Duration");
    respWriterDuration.Write(respDuration);
    DviInvocationResponseUint respWriterBitRate(aInvocation, "BitRate");
    respWriterBitRate.Write(respBitRate);
    DviInvocationResponseUint respWriterBitDepth(aInvocation, "BitDepth");
    respWriterBitDepth.Write(respBitDepth);
    DviInvocationResponseUint respWriterSampleRate(aInvocation, "SampleRate");
    respWriterSampleRate.Write(respSampleRate);
    DviInvocationResponseBool respWriterLossless(aInvocation, "Lossless");
    respWriterLossless.Write(respLossless);
    DviInvocationResponseString respWriterCodecName(aInvocation, "CodecName");
    Brn buf_CodecName((const TByte*)respCodecName.c_str(), (TUint)respCodecName.length());
    respWriterCodecName.Write(buf_CodecName);
    aInvocation.InvocationWriteStringEnd("CodecName");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgInfo1Cpp::DoMetatext(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValue;
    DvInvocationStd invocation(aInvocation);
    Metatext(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterValue(aInvocation, "Value");
    Brn buf_Value((const TByte*)respValue.c_str(), (TUint)respValue.length());
    respWriterValue.Write(buf_Value);
    aInvocation.InvocationWriteStringEnd("Value");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgInfo1Cpp::Counters(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aTrackCount*/, uint32_t& /*aDetailsCount*/, uint32_t& /*aMetatextCount*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgInfo1Cpp::Track(IDvInvocationStd& /*aInvocation*/, std::string& /*aUri*/, std::string& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgInfo1Cpp::Details(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aDuration*/, uint32_t& /*aBitRate*/, uint32_t& /*aBitDepth*/, uint32_t& /*aSampleRate*/, bool& /*aLossless*/, std::string& /*aCodecName*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgInfo1Cpp::Metatext(IDvInvocationStd& /*aInvocation*/, std::string& /*aValue*/)
{
    ASSERTS();
}

