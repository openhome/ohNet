#include <Core/DvLinnCoUkDs1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkDs1::SetPropertySupportedProtocols(const Brx& aValue)
{
    SetPropertyString(*iPropertySupportedProtocols, aValue);
}

void DvServiceLinnCoUkDs1::GetPropertySupportedProtocols(Brhz& aValue)
{
    aValue.Set(iPropertySupportedProtocols->Value());
}

void DvServiceLinnCoUkDs1::SetPropertyTrackDuration(TUint aValue)
{
    SetPropertyUint(*iPropertyTrackDuration, aValue);
}

void DvServiceLinnCoUkDs1::GetPropertyTrackDuration(TUint& aValue)
{
    aValue = iPropertyTrackDuration->Value();
}

void DvServiceLinnCoUkDs1::SetPropertyTrackBitRate(TUint aValue)
{
    SetPropertyUint(*iPropertyTrackBitRate, aValue);
}

void DvServiceLinnCoUkDs1::GetPropertyTrackBitRate(TUint& aValue)
{
    aValue = iPropertyTrackBitRate->Value();
}

void DvServiceLinnCoUkDs1::SetPropertyTrackLossless(TBool aValue)
{
    SetPropertyBool(*iPropertyTrackLossless, aValue);
}

void DvServiceLinnCoUkDs1::GetPropertyTrackLossless(TBool& aValue)
{
    aValue = iPropertyTrackLossless->Value();
}

void DvServiceLinnCoUkDs1::SetPropertyTrackBitDepth(TUint aValue)
{
    SetPropertyUint(*iPropertyTrackBitDepth, aValue);
}

void DvServiceLinnCoUkDs1::GetPropertyTrackBitDepth(TUint& aValue)
{
    aValue = iPropertyTrackBitDepth->Value();
}

void DvServiceLinnCoUkDs1::SetPropertyTrackSampleRate(TUint aValue)
{
    SetPropertyUint(*iPropertyTrackSampleRate, aValue);
}

void DvServiceLinnCoUkDs1::GetPropertyTrackSampleRate(TUint& aValue)
{
    aValue = iPropertyTrackSampleRate->Value();
}

void DvServiceLinnCoUkDs1::SetPropertyTrackCodecName(const Brx& aValue)
{
    SetPropertyString(*iPropertyTrackCodecName, aValue);
}

void DvServiceLinnCoUkDs1::GetPropertyTrackCodecName(Brhz& aValue)
{
    aValue.Set(iPropertyTrackCodecName->Value());
}

void DvServiceLinnCoUkDs1::SetPropertyTrackId(TUint aValue)
{
    SetPropertyUint(*iPropertyTrackId, aValue);
}

void DvServiceLinnCoUkDs1::GetPropertyTrackId(TUint& aValue)
{
    aValue = iPropertyTrackId->Value();
}

void DvServiceLinnCoUkDs1::SetPropertyTransportState(const Brx& aValue)
{
    SetPropertyString(*iPropertyTransportState, aValue);
}

void DvServiceLinnCoUkDs1::GetPropertyTransportState(Brhz& aValue)
{
    aValue.Set(iPropertyTransportState->Value());
}

DvServiceLinnCoUkDs1::DvServiceLinnCoUkDs1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Ds", 1)
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

void DvServiceLinnCoUkDs1::EnableActionPlay()
{
    Zapp::Action* action = new Zapp::Action("Play");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1::DoPlay);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1::EnableActionPause()
{
    Zapp::Action* action = new Zapp::Action("Pause");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1::DoPause);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1::EnableActionStop()
{
    Zapp::Action* action = new Zapp::Action("Stop");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1::DoStop);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1::EnableActionSeekSecondAbsolute()
{
    Zapp::Action* action = new Zapp::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("aSecond"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1::EnableActionSeekSecondRelative()
{
    Zapp::Action* action = new Zapp::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("aSecond"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1::EnableActionSeekTrackId()
{
    Zapp::Action* action = new Zapp::Action("SeekTrackId");
    action->AddInputParameter(new ParameterRelated("aTrackId", *iPropertyTrackId));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1::DoSeekTrackId);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1::EnableActionSeekTrackAbsolute()
{
    Zapp::Action* action = new Zapp::Action("SeekTrackAbsolute");
    action->AddInputParameter(new ParameterUint("aTrack"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1::DoSeekTrackAbsolute);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1::EnableActionSeekTrackRelative()
{
    Zapp::Action* action = new Zapp::Action("SeekTrackRelative");
    action->AddInputParameter(new ParameterInt("aTrack"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1::DoSeekTrackRelative);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1::EnableActionState()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1::DoState);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1::EnableActionProtocolInfo()
{
    Zapp::Action* action = new Zapp::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("aSupportedProtocols", *iPropertySupportedProtocols));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1::DoPlay(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Play(resp, aVersion);
}

void DvServiceLinnCoUkDs1::DoPause(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Pause(resp, aVersion);
}

void DvServiceLinnCoUkDs1::DoStop(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Stop(resp, aVersion);
}

void DvServiceLinnCoUkDs1::DoSeekSecondAbsolute(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aSecond = aInvocation.InvocationReadUint("aSecond");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekSecondAbsolute(resp, aVersion, aSecond);
}

void DvServiceLinnCoUkDs1::DoSeekSecondRelative(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aSecond = aInvocation.InvocationReadInt("aSecond");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekSecondRelative(resp, aVersion, aSecond);
}

void DvServiceLinnCoUkDs1::DoSeekTrackId(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aTrackId = aInvocation.InvocationReadUint("aTrackId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekTrackId(resp, aVersion, aTrackId);
}

void DvServiceLinnCoUkDs1::DoSeekTrackAbsolute(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aTrack = aInvocation.InvocationReadUint("aTrack");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekTrackAbsolute(resp, aVersion, aTrack);
}

void DvServiceLinnCoUkDs1::DoSeekTrackRelative(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt aTrack = aInvocation.InvocationReadInt("aTrack");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekTrackRelative(resp, aVersion, aTrack);
}

void DvServiceLinnCoUkDs1::DoState(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkDs1::DoProtocolInfo(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaSupportedProtocols(aInvocation, "aSupportedProtocols");
    ProtocolInfo(resp, aVersion, respaSupportedProtocols);
}

void DvServiceLinnCoUkDs1::Play(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1::Pause(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1::Stop(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1::SeekSecondAbsolute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaSecond*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1::SeekSecondRelative(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aaSecond*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1::SeekTrackId(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaTrackId*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1::SeekTrackAbsolute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaTrack*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1::SeekTrackRelative(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aaTrack*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1::State(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaTransportState*/, IInvocationResponseUint& /*aaTrackDuration*/, IInvocationResponseUint& /*aaTrackBitRate*/, IInvocationResponseBool& /*aaTrackLossless*/, IInvocationResponseUint& /*aaTrackBitDepth*/, IInvocationResponseUint& /*aaTrackSampleRate*/, IInvocationResponseString& /*aaTrackCodecName*/, IInvocationResponseUint& /*aaTrackId*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1::ProtocolInfo(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaSupportedProtocols*/)
{
    ASSERTS();
}

