#include <Core/DvLinnCoUkInfo1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkInfo1::SetPropertyTrackCount(TUint aValue)
{
    SetPropertyUint(*iPropertyTrackCount, aValue);
}

void DvServiceLinnCoUkInfo1::GetPropertyTrackCount(TUint& aValue)
{
    aValue = iPropertyTrackCount->Value();
}

void DvServiceLinnCoUkInfo1::SetPropertyDetailsCount(TUint aValue)
{
    SetPropertyUint(*iPropertyDetailsCount, aValue);
}

void DvServiceLinnCoUkInfo1::GetPropertyDetailsCount(TUint& aValue)
{
    aValue = iPropertyDetailsCount->Value();
}

void DvServiceLinnCoUkInfo1::SetPropertyMetatextCount(TUint aValue)
{
    SetPropertyUint(*iPropertyMetatextCount, aValue);
}

void DvServiceLinnCoUkInfo1::GetPropertyMetatextCount(TUint& aValue)
{
    aValue = iPropertyMetatextCount->Value();
}

void DvServiceLinnCoUkInfo1::SetPropertyUri(const Brx& aValue)
{
    SetPropertyString(*iPropertyUri, aValue);
}

void DvServiceLinnCoUkInfo1::GetPropertyUri(Brhz& aValue)
{
    aValue.Set(iPropertyUri->Value());
}

void DvServiceLinnCoUkInfo1::SetPropertyMetadata(const Brx& aValue)
{
    SetPropertyString(*iPropertyMetadata, aValue);
}

void DvServiceLinnCoUkInfo1::GetPropertyMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyMetadata->Value());
}

void DvServiceLinnCoUkInfo1::SetPropertyDuration(TUint aValue)
{
    SetPropertyUint(*iPropertyDuration, aValue);
}

void DvServiceLinnCoUkInfo1::GetPropertyDuration(TUint& aValue)
{
    aValue = iPropertyDuration->Value();
}

void DvServiceLinnCoUkInfo1::SetPropertyBitRate(TUint aValue)
{
    SetPropertyUint(*iPropertyBitRate, aValue);
}

void DvServiceLinnCoUkInfo1::GetPropertyBitRate(TUint& aValue)
{
    aValue = iPropertyBitRate->Value();
}

void DvServiceLinnCoUkInfo1::SetPropertyBitDepth(TUint aValue)
{
    SetPropertyUint(*iPropertyBitDepth, aValue);
}

void DvServiceLinnCoUkInfo1::GetPropertyBitDepth(TUint& aValue)
{
    aValue = iPropertyBitDepth->Value();
}

void DvServiceLinnCoUkInfo1::SetPropertySampleRate(TUint aValue)
{
    SetPropertyUint(*iPropertySampleRate, aValue);
}

void DvServiceLinnCoUkInfo1::GetPropertySampleRate(TUint& aValue)
{
    aValue = iPropertySampleRate->Value();
}

void DvServiceLinnCoUkInfo1::SetPropertyLossless(TBool aValue)
{
    SetPropertyBool(*iPropertyLossless, aValue);
}

void DvServiceLinnCoUkInfo1::GetPropertyLossless(TBool& aValue)
{
    aValue = iPropertyLossless->Value();
}

void DvServiceLinnCoUkInfo1::SetPropertyCodecName(const Brx& aValue)
{
    SetPropertyString(*iPropertyCodecName, aValue);
}

void DvServiceLinnCoUkInfo1::GetPropertyCodecName(Brhz& aValue)
{
    aValue.Set(iPropertyCodecName->Value());
}

void DvServiceLinnCoUkInfo1::SetPropertyMetatext(const Brx& aValue)
{
    SetPropertyString(*iPropertyMetatext, aValue);
}

void DvServiceLinnCoUkInfo1::GetPropertyMetatext(Brhz& aValue)
{
    aValue.Set(iPropertyMetatext->Value());
}

DvServiceLinnCoUkInfo1::DvServiceLinnCoUkInfo1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Info", 1)
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

void DvServiceLinnCoUkInfo1::EnableActionCounters()
{
    Zapp::Action* action = new Zapp::Action("Counters");
    action->AddOutputParameter(new ParameterRelated("aTrackCount", *iPropertyTrackCount));
    action->AddOutputParameter(new ParameterRelated("aDetailsCount", *iPropertyDetailsCount));
    action->AddOutputParameter(new ParameterRelated("aMetatextCount", *iPropertyMetatextCount));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkInfo1::DoCounters);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkInfo1::EnableActionTrack()
{
    Zapp::Action* action = new Zapp::Action("Track");
    action->AddOutputParameter(new ParameterRelated("aUri", *iPropertyUri));
    action->AddOutputParameter(new ParameterRelated("aMetadata", *iPropertyMetadata));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkInfo1::DoTrack);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkInfo1::EnableActionDetails()
{
    Zapp::Action* action = new Zapp::Action("Details");
    action->AddOutputParameter(new ParameterRelated("aDuration", *iPropertyDuration));
    action->AddOutputParameter(new ParameterRelated("aBitRate", *iPropertyBitRate));
    action->AddOutputParameter(new ParameterRelated("aBitDepth", *iPropertyBitDepth));
    action->AddOutputParameter(new ParameterRelated("aSampleRate", *iPropertySampleRate));
    action->AddOutputParameter(new ParameterRelated("aLossless", *iPropertyLossless));
    action->AddOutputParameter(new ParameterRelated("aCodecName", *iPropertyCodecName));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkInfo1::DoDetails);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkInfo1::EnableActionMetatext()
{
    Zapp::Action* action = new Zapp::Action("Metatext");
    action->AddOutputParameter(new ParameterRelated("aMetatext", *iPropertyMetatext));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkInfo1::DoMetatext);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkInfo1::DoCounters(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaTrackCount(aInvocation, "aTrackCount");
    InvocationResponseUint respaDetailsCount(aInvocation, "aDetailsCount");
    InvocationResponseUint respaMetatextCount(aInvocation, "aMetatextCount");
    Counters(resp, aVersion, respaTrackCount, respaDetailsCount, respaMetatextCount);
}

void DvServiceLinnCoUkInfo1::DoTrack(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaUri(aInvocation, "aUri");
    InvocationResponseString respaMetadata(aInvocation, "aMetadata");
    Track(resp, aVersion, respaUri, respaMetadata);
}

void DvServiceLinnCoUkInfo1::DoDetails(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkInfo1::DoMetatext(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaMetatext(aInvocation, "aMetatext");
    Metatext(resp, aVersion, respaMetatext);
}

void DvServiceLinnCoUkInfo1::Counters(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaTrackCount*/, IInvocationResponseUint& /*aaDetailsCount*/, IInvocationResponseUint& /*aaMetatextCount*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkInfo1::Track(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaUri*/, IInvocationResponseString& /*aaMetadata*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkInfo1::Details(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaDuration*/, IInvocationResponseUint& /*aaBitRate*/, IInvocationResponseUint& /*aaBitDepth*/, IInvocationResponseUint& /*aaSampleRate*/, IInvocationResponseBool& /*aaLossless*/, IInvocationResponseString& /*aaCodecName*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkInfo1::Metatext(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaMetatext*/)
{
    ASSERTS();
}

