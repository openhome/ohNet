#include <Std/DvLinnCoUkDs1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkDs1Cpp::SetPropertySupportedProtocols(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertySupportedProtocols, buf);
}

void DvServiceLinnCoUkDs1Cpp::GetPropertySupportedProtocols(std::string& aValue)
{
    const Brx& val = iPropertySupportedProtocols->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkDs1Cpp::SetPropertyTrackDuration(uint32_t aValue)
{
    SetPropertyUint(*iPropertyTrackDuration, aValue);
}

void DvServiceLinnCoUkDs1Cpp::GetPropertyTrackDuration(uint32_t& aValue)
{
    aValue = iPropertyTrackDuration->Value();
}

void DvServiceLinnCoUkDs1Cpp::SetPropertyTrackBitRate(uint32_t aValue)
{
    SetPropertyUint(*iPropertyTrackBitRate, aValue);
}

void DvServiceLinnCoUkDs1Cpp::GetPropertyTrackBitRate(uint32_t& aValue)
{
    aValue = iPropertyTrackBitRate->Value();
}

void DvServiceLinnCoUkDs1Cpp::SetPropertyTrackLossless(bool aValue)
{
    SetPropertyBool(*iPropertyTrackLossless, aValue);
}

void DvServiceLinnCoUkDs1Cpp::GetPropertyTrackLossless(bool& aValue)
{
    aValue = iPropertyTrackLossless->Value();
}

void DvServiceLinnCoUkDs1Cpp::SetPropertyTrackBitDepth(uint32_t aValue)
{
    SetPropertyUint(*iPropertyTrackBitDepth, aValue);
}

void DvServiceLinnCoUkDs1Cpp::GetPropertyTrackBitDepth(uint32_t& aValue)
{
    aValue = iPropertyTrackBitDepth->Value();
}

void DvServiceLinnCoUkDs1Cpp::SetPropertyTrackSampleRate(uint32_t aValue)
{
    SetPropertyUint(*iPropertyTrackSampleRate, aValue);
}

void DvServiceLinnCoUkDs1Cpp::GetPropertyTrackSampleRate(uint32_t& aValue)
{
    aValue = iPropertyTrackSampleRate->Value();
}

void DvServiceLinnCoUkDs1Cpp::SetPropertyTrackCodecName(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyTrackCodecName, buf);
}

void DvServiceLinnCoUkDs1Cpp::GetPropertyTrackCodecName(std::string& aValue)
{
    const Brx& val = iPropertyTrackCodecName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkDs1Cpp::SetPropertyTrackId(uint32_t aValue)
{
    SetPropertyUint(*iPropertyTrackId, aValue);
}

void DvServiceLinnCoUkDs1Cpp::GetPropertyTrackId(uint32_t& aValue)
{
    aValue = iPropertyTrackId->Value();
}

void DvServiceLinnCoUkDs1Cpp::SetPropertyTransportState(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyTransportState, buf);
}

void DvServiceLinnCoUkDs1Cpp::GetPropertyTransportState(std::string& aValue)
{
    const Brx& val = iPropertyTransportState->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvServiceLinnCoUkDs1Cpp::DvServiceLinnCoUkDs1Cpp(DvDeviceStd& aDevice)
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

void DvServiceLinnCoUkDs1Cpp::EnableActionPlay()
{
    Zapp::Action* action = new Zapp::Action("Play");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1Cpp::DoPlay);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1Cpp::EnableActionPause()
{
    Zapp::Action* action = new Zapp::Action("Pause");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1Cpp::DoPause);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1Cpp::EnableActionStop()
{
    Zapp::Action* action = new Zapp::Action("Stop");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1Cpp::DoStop);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1Cpp::EnableActionSeekSecondAbsolute()
{
    Zapp::Action* action = new Zapp::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("aSecond"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1Cpp::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1Cpp::EnableActionSeekSecondRelative()
{
    Zapp::Action* action = new Zapp::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("aSecond"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1Cpp::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1Cpp::EnableActionSeekTrackId()
{
    Zapp::Action* action = new Zapp::Action("SeekTrackId");
    action->AddInputParameter(new ParameterRelated("aTrackId", *iPropertyTrackId));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1Cpp::DoSeekTrackId);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1Cpp::EnableActionSeekTrackAbsolute()
{
    Zapp::Action* action = new Zapp::Action("SeekTrackAbsolute");
    action->AddInputParameter(new ParameterUint("aTrack"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1Cpp::DoSeekTrackAbsolute);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1Cpp::EnableActionSeekTrackRelative()
{
    Zapp::Action* action = new Zapp::Action("SeekTrackRelative");
    action->AddInputParameter(new ParameterInt("aTrack"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1Cpp::DoSeekTrackRelative);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1Cpp::EnableActionState()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1Cpp::DoState);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1Cpp::EnableActionProtocolInfo()
{
    Zapp::Action* action = new Zapp::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("aSupportedProtocols", *iPropertySupportedProtocols));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDs1Cpp::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDs1Cpp::DoPlay(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Play(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDs1Cpp::DoPause(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Pause(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDs1Cpp::DoStop(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Stop(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDs1Cpp::DoSeekSecondAbsolute(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aSecond = aInvocation.InvocationReadUint("aSecond");
    aInvocation.InvocationReadEnd();
    SeekSecondAbsolute(aVersion, aSecond);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDs1Cpp::DoSeekSecondRelative(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t aSecond = aInvocation.InvocationReadInt("aSecond");
    aInvocation.InvocationReadEnd();
    SeekSecondRelative(aVersion, aSecond);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDs1Cpp::DoSeekTrackId(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aTrackId = aInvocation.InvocationReadUint("aTrackId");
    aInvocation.InvocationReadEnd();
    SeekTrackId(aVersion, aTrackId);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDs1Cpp::DoSeekTrackAbsolute(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aTrack = aInvocation.InvocationReadUint("aTrack");
    aInvocation.InvocationReadEnd();
    SeekTrackAbsolute(aVersion, aTrack);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDs1Cpp::DoSeekTrackRelative(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t aTrack = aInvocation.InvocationReadInt("aTrack");
    aInvocation.InvocationReadEnd();
    SeekTrackRelative(aVersion, aTrack);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDs1Cpp::DoState(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaTransportState;
    uint32_t respaTrackDuration;
    uint32_t respaTrackBitRate;
    bool respaTrackLossless;
    uint32_t respaTrackBitDepth;
    uint32_t respaTrackSampleRate;
    std::string respaTrackCodecName;
    uint32_t respaTrackId;
    State(aVersion, respaTransportState, respaTrackDuration, respaTrackBitRate, respaTrackLossless, respaTrackBitDepth, respaTrackSampleRate, respaTrackCodecName, respaTrackId);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraTransportState(aInvocation, "aTransportState");
    Brn buf_aTransportState((const TByte*)respaTransportState.c_str(), respaTransportState.length());
    respWriteraTransportState.Write(buf_aTransportState);
    aInvocation.InvocationWriteStringEnd("aTransportState");
    InvocationResponseUint respWriteraTrackDuration(aInvocation, "aTrackDuration");
    respWriteraTrackDuration.Write(respaTrackDuration);
    InvocationResponseUint respWriteraTrackBitRate(aInvocation, "aTrackBitRate");
    respWriteraTrackBitRate.Write(respaTrackBitRate);
    InvocationResponseBool respWriteraTrackLossless(aInvocation, "aTrackLossless");
    respWriteraTrackLossless.Write(respaTrackLossless);
    InvocationResponseUint respWriteraTrackBitDepth(aInvocation, "aTrackBitDepth");
    respWriteraTrackBitDepth.Write(respaTrackBitDepth);
    InvocationResponseUint respWriteraTrackSampleRate(aInvocation, "aTrackSampleRate");
    respWriteraTrackSampleRate.Write(respaTrackSampleRate);
    InvocationResponseString respWriteraTrackCodecName(aInvocation, "aTrackCodecName");
    Brn buf_aTrackCodecName((const TByte*)respaTrackCodecName.c_str(), respaTrackCodecName.length());
    respWriteraTrackCodecName.Write(buf_aTrackCodecName);
    aInvocation.InvocationWriteStringEnd("aTrackCodecName");
    InvocationResponseUint respWriteraTrackId(aInvocation, "aTrackId");
    respWriteraTrackId.Write(respaTrackId);
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDs1Cpp::DoProtocolInfo(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaSupportedProtocols;
    ProtocolInfo(aVersion, respaSupportedProtocols);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraSupportedProtocols(aInvocation, "aSupportedProtocols");
    Brn buf_aSupportedProtocols((const TByte*)respaSupportedProtocols.c_str(), respaSupportedProtocols.length());
    respWriteraSupportedProtocols.Write(buf_aSupportedProtocols);
    aInvocation.InvocationWriteStringEnd("aSupportedProtocols");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDs1Cpp::Play(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1Cpp::Pause(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1Cpp::Stop(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1Cpp::SeekSecondAbsolute(uint32_t /*aVersion*/, uint32_t /*aaSecond*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1Cpp::SeekSecondRelative(uint32_t /*aVersion*/, int32_t /*aaSecond*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1Cpp::SeekTrackId(uint32_t /*aVersion*/, uint32_t /*aaTrackId*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1Cpp::SeekTrackAbsolute(uint32_t /*aVersion*/, uint32_t /*aaTrack*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1Cpp::SeekTrackRelative(uint32_t /*aVersion*/, int32_t /*aaTrack*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1Cpp::State(uint32_t /*aVersion*/, std::string& /*aaTransportState*/, uint32_t& /*aaTrackDuration*/, uint32_t& /*aaTrackBitRate*/, bool& /*aaTrackLossless*/, uint32_t& /*aaTrackBitDepth*/, uint32_t& /*aaTrackSampleRate*/, std::string& /*aaTrackCodecName*/, uint32_t& /*aaTrackId*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDs1Cpp::ProtocolInfo(uint32_t /*aVersion*/, std::string& /*aaSupportedProtocols*/)
{
    ASSERTS();
}

