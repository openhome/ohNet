#include "DvAvOpenhomeOrgInfo1.h"
#include <OhNetTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyTrackCount(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyTrackCount(TUint& aValue)
{
    aValue = iPropertyTrackCount->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyDetailsCount(TUint aValue)
{
    return SetPropertyUint(*iPropertyDetailsCount, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyDetailsCount(TUint& aValue)
{
    aValue = iPropertyDetailsCount->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyMetatextCount(TUint aValue)
{
    return SetPropertyUint(*iPropertyMetatextCount, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyMetatextCount(TUint& aValue)
{
    aValue = iPropertyMetatextCount->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyUri, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyUri(Brhz& aValue)
{
    aValue.Set(iPropertyUri->Value());
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyMetadata(const Brx& aValue)
{
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyDuration(TUint aValue)
{
    return SetPropertyUint(*iPropertyDuration, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyDuration(TUint& aValue)
{
    aValue = iPropertyDuration->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyBitRate(TUint aValue)
{
    return SetPropertyUint(*iPropertyBitRate, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyBitRate(TUint& aValue)
{
    aValue = iPropertyBitRate->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyBitDepth(TUint aValue)
{
    return SetPropertyUint(*iPropertyBitDepth, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyBitDepth(TUint& aValue)
{
    aValue = iPropertyBitDepth->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertySampleRate(TUint aValue)
{
    return SetPropertyUint(*iPropertySampleRate, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertySampleRate(TUint& aValue)
{
    aValue = iPropertySampleRate->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyLossless(TBool aValue)
{
    return SetPropertyBool(*iPropertyLossless, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyLossless(TBool& aValue)
{
    aValue = iPropertyLossless->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyCodecName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyCodecName, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyCodecName(Brhz& aValue)
{
    aValue.Set(iPropertyCodecName->Value());
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyMetatext(const Brx& aValue)
{
    return SetPropertyString(*iPropertyMetatext, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyMetatext(Brhz& aValue)
{
    aValue.Set(iPropertyMetatext->Value());
}

DvProviderAvOpenhomeOrgInfo1::DvProviderAvOpenhomeOrgInfo1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Info", 1)
{
    
    iPropertyTrackCount = new PropertyUint(new ParameterUint("TrackCount"));
    iService->AddProperty(iPropertyTrackCount); // passes ownership
    iPropertyDetailsCount = new PropertyUint(new ParameterUint("DetailsCount"));
    iService->AddProperty(iPropertyDetailsCount); // passes ownership
    iPropertyMetatextCount = new PropertyUint(new ParameterUint("MetatextCount"));
    iService->AddProperty(iPropertyMetatextCount); // passes ownership
    iPropertyUri = new PropertyString(new ParameterString("Uri"));
    iService->AddProperty(iPropertyUri); // passes ownership
    iPropertyMetadata = new PropertyString(new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
    iPropertyDuration = new PropertyUint(new ParameterUint("Duration"));
    iService->AddProperty(iPropertyDuration); // passes ownership
    iPropertyBitRate = new PropertyUint(new ParameterUint("BitRate"));
    iService->AddProperty(iPropertyBitRate); // passes ownership
    iPropertyBitDepth = new PropertyUint(new ParameterUint("BitDepth"));
    iService->AddProperty(iPropertyBitDepth); // passes ownership
    iPropertySampleRate = new PropertyUint(new ParameterUint("SampleRate"));
    iService->AddProperty(iPropertySampleRate); // passes ownership
    iPropertyLossless = new PropertyBool(new ParameterBool("Lossless"));
    iService->AddProperty(iPropertyLossless); // passes ownership
    iPropertyCodecName = new PropertyString(new ParameterString("CodecName"));
    iService->AddProperty(iPropertyCodecName); // passes ownership
    iPropertyMetatext = new PropertyString(new ParameterString("Metatext"));
    iService->AddProperty(iPropertyMetatext); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1::EnableActionCounters()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Counters");
    action->AddOutputParameter(new ParameterRelated("TrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("DetailsCount", *iPropertyDetailsCount));
    action->AddOutputParameter(new ParameterRelated("MetatextCount", *iPropertyMetatextCount));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgInfo1::DoCounters);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgInfo1::EnableActionTrack()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Track");
    action->AddOutputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgInfo1::DoTrack);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgInfo1::EnableActionDetails()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Details");
    action->AddOutputParameter(new ParameterRelated("Duration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("BitRate", *iPropertyBitRate));
    action->AddOutputParameter(new ParameterRelated("BitDepth", *iPropertyBitDepth));
    action->AddOutputParameter(new ParameterRelated("SampleRate", *iPropertySampleRate));
    action->AddOutputParameter(new ParameterRelated("Lossless", *iPropertyLossless));
    action->AddOutputParameter(new ParameterRelated("CodecName", *iPropertyCodecName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgInfo1::DoDetails);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgInfo1::EnableActionMetatext()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Metatext");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyMetatext));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgInfo1::DoMetatext);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgInfo1::DoCounters(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respTrackCount(aInvocation, "TrackCount");
    InvocationResponseUint respDetailsCount(aInvocation, "DetailsCount");
    InvocationResponseUint respMetatextCount(aInvocation, "MetatextCount");
    Counters(resp, aVersion, respTrackCount, respDetailsCount, respMetatextCount);
}

void DvProviderAvOpenhomeOrgInfo1::DoTrack(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respUri(aInvocation, "Uri");
    InvocationResponseString respMetadata(aInvocation, "Metadata");
    Track(resp, aVersion, respUri, respMetadata);
}

void DvProviderAvOpenhomeOrgInfo1::DoDetails(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respDuration(aInvocation, "Duration");
    InvocationResponseUint respBitRate(aInvocation, "BitRate");
    InvocationResponseUint respBitDepth(aInvocation, "BitDepth");
    InvocationResponseUint respSampleRate(aInvocation, "SampleRate");
    InvocationResponseBool respLossless(aInvocation, "Lossless");
    InvocationResponseString respCodecName(aInvocation, "CodecName");
    Details(resp, aVersion, respDuration, respBitRate, respBitDepth, respSampleRate, respLossless, respCodecName);
}

void DvProviderAvOpenhomeOrgInfo1::DoMetatext(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respValue(aInvocation, "Value");
    Metatext(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgInfo1::Counters(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aTrackCount*/, IInvocationResponseUint& /*aDetailsCount*/, IInvocationResponseUint& /*aMetatextCount*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgInfo1::Track(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aUri*/, IInvocationResponseString& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgInfo1::Details(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aDuration*/, IInvocationResponseUint& /*aBitRate*/, IInvocationResponseUint& /*aBitDepth*/, IInvocationResponseUint& /*aSampleRate*/, IInvocationResponseBool& /*aLossless*/, IInvocationResponseString& /*aCodecName*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgInfo1::Metatext(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

