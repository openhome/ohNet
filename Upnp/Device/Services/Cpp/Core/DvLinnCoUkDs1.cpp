#include <Core/DvLinnCoUkDs1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkDs1::SetPropertySupportedProtocols(const Brx& aValue)
{
    return SetPropertyString(*iPropertySupportedProtocols, aValue);
}

void DvProviderLinnCoUkDs1::GetPropertySupportedProtocols(Brhz& aValue)
{
    aValue.Set(iPropertySupportedProtocols->Value());
}

TBool DvProviderLinnCoUkDs1::SetPropertyTrackDuration(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackDuration, aValue);
}

void DvProviderLinnCoUkDs1::GetPropertyTrackDuration(TUint& aValue)
{
    aValue = iPropertyTrackDuration->Value();
}

TBool DvProviderLinnCoUkDs1::SetPropertyTrackBitRate(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackBitRate, aValue);
}

void DvProviderLinnCoUkDs1::GetPropertyTrackBitRate(TUint& aValue)
{
    aValue = iPropertyTrackBitRate->Value();
}

TBool DvProviderLinnCoUkDs1::SetPropertyTrackLossless(TBool aValue)
{
    return SetPropertyBool(*iPropertyTrackLossless, aValue);
}

void DvProviderLinnCoUkDs1::GetPropertyTrackLossless(TBool& aValue)
{
    aValue = iPropertyTrackLossless->Value();
}

TBool DvProviderLinnCoUkDs1::SetPropertyTrackBitDepth(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackBitDepth, aValue);
}

void DvProviderLinnCoUkDs1::GetPropertyTrackBitDepth(TUint& aValue)
{
    aValue = iPropertyTrackBitDepth->Value();
}

TBool DvProviderLinnCoUkDs1::SetPropertyTrackSampleRate(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackSampleRate, aValue);
}

void DvProviderLinnCoUkDs1::GetPropertyTrackSampleRate(TUint& aValue)
{
    aValue = iPropertyTrackSampleRate->Value();
}

TBool DvProviderLinnCoUkDs1::SetPropertyTrackCodecName(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTrackCodecName, aValue);
}

void DvProviderLinnCoUkDs1::GetPropertyTrackCodecName(Brhz& aValue)
{
    aValue.Set(iPropertyTrackCodecName->Value());
}

TBool DvProviderLinnCoUkDs1::SetPropertyTrackId(TUint aValue)
{
    return SetPropertyUint(*iPropertyTrackId, aValue);
}

void DvProviderLinnCoUkDs1::GetPropertyTrackId(TUint& aValue)
{
    aValue = iPropertyTrackId->Value();
}

TBool DvProviderLinnCoUkDs1::SetPropertyTransportState(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTransportState, aValue);
}

void DvProviderLinnCoUkDs1::GetPropertyTransportState(Brhz& aValue)
{
    aValue.Set(iPropertyTransportState->Value());
}

DvProviderLinnCoUkDs1::DvProviderLinnCoUkDs1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Ds", 1)
{
    Functor empty;
    TChar** allowedValues;
    TUint index;
    iPropertySupportedProtocols = new PropertyString(new ParameterString("SupportedProtocols"), empty);
    iService->AddProperty(iPropertySupportedProtocols); // passes ownership
    iPropertyTrackDuration = new PropertyUint(new ParameterUint("TrackDuration"), empty);
    iService->AddProperty(iPropertyTrackDuration); // passes ownership
    iPropertyTrackBitRate = new PropertyUint(new ParameterUint("TrackBitRate"), empty);
    iService->AddProperty(iPropertyTrackBitRate); // passes ownership
    iPropertyTrackLossless = new PropertyBool(new ParameterBool("TrackLossless"), empty);
    iService->AddProperty(iPropertyTrackLossless); // passes ownership
    iPropertyTrackBitDepth = new PropertyUint(new ParameterUint("TrackBitDepth"), empty);
    iService->AddProperty(iPropertyTrackBitDepth); // passes ownership
    iPropertyTrackSampleRate = new PropertyUint(new ParameterUint("TrackSampleRate"), empty);
    iService->AddProperty(iPropertyTrackSampleRate); // passes ownership
    iPropertyTrackCodecName = new PropertyString(new ParameterString("TrackCodecName"), empty);
    iService->AddProperty(iPropertyTrackCodecName); // passes ownership
    iPropertyTrackId = new PropertyUint(new ParameterUint("TrackId"), empty);
    iService->AddProperty(iPropertyTrackId); // passes ownership
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Buffering";
    iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues, 4), empty);
    delete[] allowedValues;
    iService->AddProperty(iPropertyTransportState); // passes ownership
}

void DvProviderLinnCoUkDs1::EnableActionPlay()
{
    Zapp::Action* action = new Zapp::Action("Play");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1::EnableActionPause()
{
    Zapp::Action* action = new Zapp::Action("Pause");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1::EnableActionStop()
{
    Zapp::Action* action = new Zapp::Action("Stop");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1::EnableActionSeekSecondAbsolute()
{
    Zapp::Action* action = new Zapp::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("aSecond"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1::EnableActionSeekSecondRelative()
{
    Zapp::Action* action = new Zapp::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("aSecond"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1::EnableActionSeekTrackId()
{
    Zapp::Action* action = new Zapp::Action("SeekTrackId");
    action->AddInputParameter(new ParameterRelated("aTrackId", *iPropertyTrackId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1::DoSeekTrackId);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1::EnableActionSeekTrackAbsolute()
{
    Zapp::Action* action = new Zapp::Action("SeekTrackAbsolute");
    action->AddInputParameter(new ParameterUint("aTrack"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1::DoSeekTrackAbsolute);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1::EnableActionSeekTrackRelative()
{
    Zapp::Action* action = new Zapp::Action("SeekTrackRelative");
    action->AddInputParameter(new ParameterInt("aTrack"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1::DoSeekTrackRelative);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1::EnableActionState()
{
    Zapp::Action* action = new Zapp::Action("State");
    action->AddOutputParameter(new ParameterRelated("aTransportState", *iPropertyTransportState));
    action->AddOutputParameter(new ParameterRelated("aTrackDuration", *iPropertyTrackDuration));
    action->AddOutputParameter(new ParameterRelated("aTrackBitRate", *iPropertyTrackBitRate));
    action->AddOutputParameter(new ParameterRelated("aTrackLossless", *iPropertyTrackLossless));
    action->AddOutputParameter(new ParameterRelated("aTrackBitDepth", *iPropertyTrackBitDepth));
    action->AddOutputParameter(new ParameterRelated("aTrackSampleRate", *iPropertyTrackSampleRate));
    action->AddOutputParameter(new ParameterRelated("aTrackCodecName", *iPropertyTrackCodecName));
    action->AddOutputParameter(new ParameterRelated("aTrackId", *iPropertyTrackId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1::DoState);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1::EnableActionProtocolInfo()
{
    Zapp::Action* action = new Zapp::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("aSupportedProtocols", *iPropertySupportedProtocols));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDs1::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1::DoPlay(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Play(resp, aVersion);
}

void DvProviderLinnCoUkDs1::DoPause(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Pause(resp, aVersion);
}

void DvProviderLinnCoUkDs1::DoStop(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Stop(resp, aVersion);
}

void DvProviderLinnCoUkDs1::DoSeekSecondAbsolute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSecond = aInvocation.InvocationReadUint("aSecond");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekSecondAbsolute(resp, aVersion, aSecond);
}

void DvProviderLinnCoUkDs1::DoSeekSecondRelative(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aSecond = aInvocation.InvocationReadInt("aSecond");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekSecondRelative(resp, aVersion, aSecond);
}

void DvProviderLinnCoUkDs1::DoSeekTrackId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aTrackId = aInvocation.InvocationReadUint("aTrackId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekTrackId(resp, aVersion, aTrackId);
}

void DvProviderLinnCoUkDs1::DoSeekTrackAbsolute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aTrack = aInvocation.InvocationReadUint("aTrack");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekTrackAbsolute(resp, aVersion, aTrack);
}

void DvProviderLinnCoUkDs1::DoSeekTrackRelative(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aTrack = aInvocation.InvocationReadInt("aTrack");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekTrackRelative(resp, aVersion, aTrack);
}

void DvProviderLinnCoUkDs1::DoState(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaTransportState(aInvocation, "aTransportState");
    InvocationResponseUint respaTrackDuration(aInvocation, "aTrackDuration");
    InvocationResponseUint respaTrackBitRate(aInvocation, "aTrackBitRate");
    InvocationResponseBool respaTrackLossless(aInvocation, "aTrackLossless");
    InvocationResponseUint respaTrackBitDepth(aInvocation, "aTrackBitDepth");
    InvocationResponseUint respaTrackSampleRate(aInvocation, "aTrackSampleRate");
    InvocationResponseString respaTrackCodecName(aInvocation, "aTrackCodecName");
    InvocationResponseUint respaTrackId(aInvocation, "aTrackId");
    State(resp, aVersion, respaTransportState, respaTrackDuration, respaTrackBitRate, respaTrackLossless, respaTrackBitDepth, respaTrackSampleRate, respaTrackCodecName, respaTrackId);
}

void DvProviderLinnCoUkDs1::DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaSupportedProtocols(aInvocation, "aSupportedProtocols");
    ProtocolInfo(resp, aVersion, respaSupportedProtocols);
}

void DvProviderLinnCoUkDs1::Play(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1::Pause(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1::Stop(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1::SeekSecondAbsolute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSecond*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1::SeekSecondRelative(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aaSecond*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1::SeekTrackId(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaTrackId*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1::SeekTrackAbsolute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaTrack*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1::SeekTrackRelative(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aaTrack*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1::State(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaTransportState*/, IInvocationResponseUint& /*aaTrackDuration*/, IInvocationResponseUint& /*aaTrackBitRate*/, IInvocationResponseBool& /*aaTrackLossless*/, IInvocationResponseUint& /*aaTrackBitDepth*/, IInvocationResponseUint& /*aaTrackSampleRate*/, IInvocationResponseString& /*aaTrackCodecName*/, IInvocationResponseUint& /*aaTrackId*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1::ProtocolInfo(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaSupportedProtocols*/)
{
    ASSERTS();
}

