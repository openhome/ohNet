#include "DvAvOpenhomeOrgInfo1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyTrackCount(TUint aValue)
{
    ASSERT(iPropertyTrackCount != NULL);
    return SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyTrackCount(TUint& aValue)
{
    ASSERT(iPropertyTrackCount != NULL);
    aValue = iPropertyTrackCount->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyDetailsCount(TUint aValue)
{
    ASSERT(iPropertyDetailsCount != NULL);
    return SetPropertyUint(*iPropertyDetailsCount, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyDetailsCount(TUint& aValue)
{
    ASSERT(iPropertyDetailsCount != NULL);
    aValue = iPropertyDetailsCount->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyMetatextCount(TUint aValue)
{
    ASSERT(iPropertyMetatextCount != NULL);
    return SetPropertyUint(*iPropertyMetatextCount, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyMetatextCount(TUint& aValue)
{
    ASSERT(iPropertyMetatextCount != NULL);
    aValue = iPropertyMetatextCount->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyUri(const Brx& aValue)
{
    ASSERT(iPropertyUri != NULL);
    return SetPropertyString(*iPropertyUri, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyUri(Brhz& aValue)
{
    ASSERT(iPropertyUri != NULL);
    aValue.Set(iPropertyUri->Value());
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyMetadata(const Brx& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyMetadata(Brhz& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyDuration(TUint aValue)
{
    ASSERT(iPropertyDuration != NULL);
    return SetPropertyUint(*iPropertyDuration, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyDuration(TUint& aValue)
{
    ASSERT(iPropertyDuration != NULL);
    aValue = iPropertyDuration->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyBitRate(TUint aValue)
{
    ASSERT(iPropertyBitRate != NULL);
    return SetPropertyUint(*iPropertyBitRate, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyBitRate(TUint& aValue)
{
    ASSERT(iPropertyBitRate != NULL);
    aValue = iPropertyBitRate->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyBitDepth(TUint aValue)
{
    ASSERT(iPropertyBitDepth != NULL);
    return SetPropertyUint(*iPropertyBitDepth, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyBitDepth(TUint& aValue)
{
    ASSERT(iPropertyBitDepth != NULL);
    aValue = iPropertyBitDepth->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertySampleRate(TUint aValue)
{
    ASSERT(iPropertySampleRate != NULL);
    return SetPropertyUint(*iPropertySampleRate, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertySampleRate(TUint& aValue)
{
    ASSERT(iPropertySampleRate != NULL);
    aValue = iPropertySampleRate->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyLossless(TBool aValue)
{
    ASSERT(iPropertyLossless != NULL);
    return SetPropertyBool(*iPropertyLossless, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyLossless(TBool& aValue)
{
    ASSERT(iPropertyLossless != NULL);
    aValue = iPropertyLossless->Value();
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyCodecName(const Brx& aValue)
{
    ASSERT(iPropertyCodecName != NULL);
    return SetPropertyString(*iPropertyCodecName, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyCodecName(Brhz& aValue)
{
    ASSERT(iPropertyCodecName != NULL);
    aValue.Set(iPropertyCodecName->Value());
}

TBool DvProviderAvOpenhomeOrgInfo1::SetPropertyMetatext(const Brx& aValue)
{
    ASSERT(iPropertyMetatext != NULL);
    return SetPropertyString(*iPropertyMetatext, aValue);
}

void DvProviderAvOpenhomeOrgInfo1::GetPropertyMetatext(Brhz& aValue)
{
    ASSERT(iPropertyMetatext != NULL);
    aValue.Set(iPropertyMetatext->Value());
}

DvProviderAvOpenhomeOrgInfo1::DvProviderAvOpenhomeOrgInfo1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Info", 1)
{
    Construct();
}

DvProviderAvOpenhomeOrgInfo1::DvProviderAvOpenhomeOrgInfo1(DviDevice& aDevice)
    : DvProvider(aDevice, "av.openhome.org", "Info", 1)
{
    Construct();
}

void DvProviderAvOpenhomeOrgInfo1::Construct()
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

void DvProviderAvOpenhomeOrgInfo1::EnablePropertyTrackCount()
{
    iPropertyTrackCount = new PropertyUint(iDvStack.Env(), new ParameterUint("TrackCount"));
    iService->AddProperty(iPropertyTrackCount); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1::EnablePropertyDetailsCount()
{
    iPropertyDetailsCount = new PropertyUint(iDvStack.Env(), new ParameterUint("DetailsCount"));
    iService->AddProperty(iPropertyDetailsCount); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1::EnablePropertyMetatextCount()
{
    iPropertyMetatextCount = new PropertyUint(iDvStack.Env(), new ParameterUint("MetatextCount"));
    iService->AddProperty(iPropertyMetatextCount); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1::EnablePropertyUri()
{
    iPropertyUri = new PropertyString(iDvStack.Env(), new ParameterString("Uri"));
    iService->AddProperty(iPropertyUri); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1::EnablePropertyMetadata()
{
    iPropertyMetadata = new PropertyString(iDvStack.Env(), new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1::EnablePropertyDuration()
{
    iPropertyDuration = new PropertyUint(iDvStack.Env(), new ParameterUint("Duration"));
    iService->AddProperty(iPropertyDuration); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1::EnablePropertyBitRate()
{
    iPropertyBitRate = new PropertyUint(iDvStack.Env(), new ParameterUint("BitRate"));
    iService->AddProperty(iPropertyBitRate); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1::EnablePropertyBitDepth()
{
    iPropertyBitDepth = new PropertyUint(iDvStack.Env(), new ParameterUint("BitDepth"));
    iService->AddProperty(iPropertyBitDepth); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1::EnablePropertySampleRate()
{
    iPropertySampleRate = new PropertyUint(iDvStack.Env(), new ParameterUint("SampleRate"));
    iService->AddProperty(iPropertySampleRate); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1::EnablePropertyLossless()
{
    iPropertyLossless = new PropertyBool(iDvStack.Env(), new ParameterBool("Lossless"));
    iService->AddProperty(iPropertyLossless); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1::EnablePropertyCodecName()
{
    iPropertyCodecName = new PropertyString(iDvStack.Env(), new ParameterString("CodecName"));
    iService->AddProperty(iPropertyCodecName); // passes ownership
}

void DvProviderAvOpenhomeOrgInfo1::EnablePropertyMetatext()
{
    iPropertyMetatext = new PropertyString(iDvStack.Env(), new ParameterString("Metatext"));
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

void DvProviderAvOpenhomeOrgInfo1::DoCounters(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respTrackCount(aInvocation, "TrackCount");
    DviInvocationResponseUint respDetailsCount(aInvocation, "DetailsCount");
    DviInvocationResponseUint respMetatextCount(aInvocation, "MetatextCount");
    Counters(invocation, respTrackCount, respDetailsCount, respMetatextCount);
}

void DvProviderAvOpenhomeOrgInfo1::DoTrack(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respUri(aInvocation, "Uri");
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    Track(invocation, respUri, respMetadata);
}

void DvProviderAvOpenhomeOrgInfo1::DoDetails(IDviInvocation& aInvocation)
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
    Details(invocation, respDuration, respBitRate, respBitDepth, respSampleRate, respLossless, respCodecName);
}

void DvProviderAvOpenhomeOrgInfo1::DoMetatext(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    Metatext(invocation, respValue);
}

void DvProviderAvOpenhomeOrgInfo1::Counters(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aTrackCount*/, IDvInvocationResponseUint& /*aDetailsCount*/, IDvInvocationResponseUint& /*aMetatextCount*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgInfo1::Track(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aUri*/, IDvInvocationResponseString& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgInfo1::Details(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aDuration*/, IDvInvocationResponseUint& /*aBitRate*/, IDvInvocationResponseUint& /*aBitDepth*/, IDvInvocationResponseUint& /*aSampleRate*/, IDvInvocationResponseBool& /*aLossless*/, IDvInvocationResponseString& /*aCodecName*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgInfo1::Metatext(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

