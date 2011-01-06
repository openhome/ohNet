#include "DvLinnCoUkInfo1.h"
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkInfo1::SetPropertyTrackCount(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvProviderLinnCoUkInfo1::GetPropertyTrackCount(TUint& aValue)
{
    aValue = iPropertyTrackCount->Value();
}

TBool DvProviderLinnCoUkInfo1::SetPropertyDetailsCount(TUint aValue)
{
    return SetPropertyUint(*iPropertyDetailsCount, aValue);
}

void DvProviderLinnCoUkInfo1::GetPropertyDetailsCount(TUint& aValue)
{
    aValue = iPropertyDetailsCount->Value();
}

TBool DvProviderLinnCoUkInfo1::SetPropertyMetatextCount(TUint aValue)
{
    return SetPropertyUint(*iPropertyMetatextCount, aValue);
}

void DvProviderLinnCoUkInfo1::GetPropertyMetatextCount(TUint& aValue)
{
    aValue = iPropertyMetatextCount->Value();
}

TBool DvProviderLinnCoUkInfo1::SetPropertyUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyUri, aValue);
}

void DvProviderLinnCoUkInfo1::GetPropertyUri(Brhz& aValue)
{
    aValue.Set(iPropertyUri->Value());
}

TBool DvProviderLinnCoUkInfo1::SetPropertyMetadata(const Brx& aValue)
{
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderLinnCoUkInfo1::GetPropertyMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderLinnCoUkInfo1::SetPropertyDuration(TUint aValue)
{
    return SetPropertyUint(*iPropertyDuration, aValue);
}

void DvProviderLinnCoUkInfo1::GetPropertyDuration(TUint& aValue)
{
    aValue = iPropertyDuration->Value();
}

TBool DvProviderLinnCoUkInfo1::SetPropertyBitRate(TUint aValue)
{
    return SetPropertyUint(*iPropertyBitRate, aValue);
}

void DvProviderLinnCoUkInfo1::GetPropertyBitRate(TUint& aValue)
{
    aValue = iPropertyBitRate->Value();
}

TBool DvProviderLinnCoUkInfo1::SetPropertyBitDepth(TUint aValue)
{
    return SetPropertyUint(*iPropertyBitDepth, aValue);
}

void DvProviderLinnCoUkInfo1::GetPropertyBitDepth(TUint& aValue)
{
    aValue = iPropertyBitDepth->Value();
}

TBool DvProviderLinnCoUkInfo1::SetPropertySampleRate(TUint aValue)
{
    return SetPropertyUint(*iPropertySampleRate, aValue);
}

void DvProviderLinnCoUkInfo1::GetPropertySampleRate(TUint& aValue)
{
    aValue = iPropertySampleRate->Value();
}

TBool DvProviderLinnCoUkInfo1::SetPropertyLossless(TBool aValue)
{
    return SetPropertyBool(*iPropertyLossless, aValue);
}

void DvProviderLinnCoUkInfo1::GetPropertyLossless(TBool& aValue)
{
    aValue = iPropertyLossless->Value();
}

TBool DvProviderLinnCoUkInfo1::SetPropertyCodecName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyCodecName, aValue);
}

void DvProviderLinnCoUkInfo1::GetPropertyCodecName(Brhz& aValue)
{
    aValue.Set(iPropertyCodecName->Value());
}

TBool DvProviderLinnCoUkInfo1::SetPropertyMetatext(const Brx& aValue)
{
    return SetPropertyString(*iPropertyMetatext, aValue);
}

void DvProviderLinnCoUkInfo1::GetPropertyMetatext(Brhz& aValue)
{
    aValue.Set(iPropertyMetatext->Value());
}

DvProviderLinnCoUkInfo1::DvProviderLinnCoUkInfo1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Info", 1)
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

void DvProviderLinnCoUkInfo1::EnableActionCounters()
{
    Zapp::Action* action = new Zapp::Action("Counters");
    action->AddOutputParameter(new ParameterRelated("aTrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("aDetailsCount", *iPropertyDetailsCount));
    action->AddOutputParameter(new ParameterRelated("aMetatextCount", *iPropertyMetatextCount));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkInfo1::DoCounters);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkInfo1::EnableActionTrack()
{
    Zapp::Action* action = new Zapp::Action("Track");
    action->AddOutputParameter(new ParameterRelated("aUri", *iPropertyUri));
    action->AddOutputParameter(new ParameterRelated("aMetadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkInfo1::DoTrack);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkInfo1::EnableActionDetails()
{
    Zapp::Action* action = new Zapp::Action("Details");
    action->AddOutputParameter(new ParameterRelated("aDuration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("aBitRate", *iPropertyBitRate));
    action->AddOutputParameter(new ParameterRelated("aBitDepth", *iPropertyBitDepth));
    action->AddOutputParameter(new ParameterRelated("aSampleRate", *iPropertySampleRate));
    action->AddOutputParameter(new ParameterRelated("aLossless", *iPropertyLossless));
    action->AddOutputParameter(new ParameterRelated("aCodecName", *iPropertyCodecName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkInfo1::DoDetails);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkInfo1::EnableActionMetatext()
{
    Zapp::Action* action = new Zapp::Action("Metatext");
    action->AddOutputParameter(new ParameterRelated("aMetatext", *iPropertyMetatext));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkInfo1::DoMetatext);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkInfo1::DoCounters(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaTrackCount(aInvocation, "aTrackCount");
    InvocationResponseUint respaDetailsCount(aInvocation, "aDetailsCount");
    InvocationResponseUint respaMetatextCount(aInvocation, "aMetatextCount");
    Counters(resp, aVersion, respaTrackCount, respaDetailsCount, respaMetatextCount);
}

void DvProviderLinnCoUkInfo1::DoTrack(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaUri(aInvocation, "aUri");
    InvocationResponseString respaMetadata(aInvocation, "aMetadata");
    Track(resp, aVersion, respaUri, respaMetadata);
}

void DvProviderLinnCoUkInfo1::DoDetails(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaDuration(aInvocation, "aDuration");
    InvocationResponseUint respaBitRate(aInvocation, "aBitRate");
    InvocationResponseUint respaBitDepth(aInvocation, "aBitDepth");
    InvocationResponseUint respaSampleRate(aInvocation, "aSampleRate");
    InvocationResponseBool respaLossless(aInvocation, "aLossless");
    InvocationResponseString respaCodecName(aInvocation, "aCodecName");
    Details(resp, aVersion, respaDuration, respaBitRate, respaBitDepth, respaSampleRate, respaLossless, respaCodecName);
}

void DvProviderLinnCoUkInfo1::DoMetatext(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaMetatext(aInvocation, "aMetatext");
    Metatext(resp, aVersion, respaMetatext);
}

void DvProviderLinnCoUkInfo1::Counters(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaTrackCount*/, IInvocationResponseUint& /*aaDetailsCount*/, IInvocationResponseUint& /*aaMetatextCount*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkInfo1::Track(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaUri*/, IInvocationResponseString& /*aaMetadata*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkInfo1::Details(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaDuration*/, IInvocationResponseUint& /*aaBitRate*/, IInvocationResponseUint& /*aaBitDepth*/, IInvocationResponseUint& /*aaSampleRate*/, IInvocationResponseBool& /*aaLossless*/, IInvocationResponseString& /*aaCodecName*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkInfo1::Metatext(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaMetatext*/)
{
    ASSERTS();
}

