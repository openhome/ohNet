#include "DvAvOpenhomeOrgInfo1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

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
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respTrackCount(aInvocation, "TrackCount");
    DviInvocationResponseUint respDetailsCount(aInvocation, "DetailsCount");
    DviInvocationResponseUint respMetatextCount(aInvocation, "MetatextCount");
    Counters(invocation, aVersion, respTrackCount, respDetailsCount, respMetatextCount);
}

void DvProviderAvOpenhomeOrgInfo1::DoTrack(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respUri(aInvocation, "Uri");
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    Track(invocation, aVersion, respUri, respMetadata);
}

void DvProviderAvOpenhomeOrgInfo1::DoDetails(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respDuration(aInvocation, "Duration");
    DviInvocationResponseUint respBitRate(aInvocation, "BitRate");
    DviInvocationResponseUint respBitDepth(aInvocation, "BitDepth");
    DviInvocationResponseUint respSampleRate(aInvocation, "SampleRate");
    DviInvocationResponseBool respLossless(aInvocation, "Lossless");
    DviInvocationResponseString respCodecName(aInvocation, "CodecName");
    Details(invocation, aVersion, respDuration, respBitRate, respBitDepth, respSampleRate, respLossless, respCodecName);
}

void DvProviderAvOpenhomeOrgInfo1::DoMetatext(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    Metatext(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgInfo1::Counters(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aTrackCount*/, IDvInvocationResponseUint& /*aDetailsCount*/, IDvInvocationResponseUint& /*aMetatextCount*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgInfo1::Track(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aUri*/, IDvInvocationResponseString& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgInfo1::Details(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aDuration*/, IDvInvocationResponseUint& /*aBitRate*/, IDvInvocationResponseUint& /*aBitDepth*/, IDvInvocationResponseUint& /*aSampleRate*/, IDvInvocationResponseBool& /*aLossless*/, IDvInvocationResponseString& /*aCodecName*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgInfo1::Metatext(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

