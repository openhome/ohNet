#include <Std/DvLinnCoUkDs1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

bool DvProviderLinnCoUkDs1Cpp::SetPropertySupportedProtocols(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertySupportedProtocols, buf);
}

void DvProviderLinnCoUkDs1Cpp::GetPropertySupportedProtocols(std::string& aValue)
{
    const Brx& val = iPropertySupportedProtocols->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderLinnCoUkDs1Cpp::SetPropertyTrackDuration(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyTrackDuration, aValue);
}

void DvProviderLinnCoUkDs1Cpp::GetPropertyTrackDuration(uint32_t& aValue)
{
    aValue = iPropertyTrackDuration->Value();
}

bool DvProviderLinnCoUkDs1Cpp::SetPropertyTrackBitRate(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyTrackBitRate, aValue);
}

void DvProviderLinnCoUkDs1Cpp::GetPropertyTrackBitRate(uint32_t& aValue)
{
    aValue = iPropertyTrackBitRate->Value();
}

bool DvProviderLinnCoUkDs1Cpp::SetPropertyTrackLossless(bool aValue)
{
    return SetPropertyBool(*iPropertyTrackLossless, aValue);
}

void DvProviderLinnCoUkDs1Cpp::GetPropertyTrackLossless(bool& aValue)
{
    aValue = iPropertyTrackLossless->Value();
}

bool DvProviderLinnCoUkDs1Cpp::SetPropertyTrackBitDepth(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyTrackBitDepth, aValue);
}

void DvProviderLinnCoUkDs1Cpp::GetPropertyTrackBitDepth(uint32_t& aValue)
{
    aValue = iPropertyTrackBitDepth->Value();
}

bool DvProviderLinnCoUkDs1Cpp::SetPropertyTrackSampleRate(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyTrackSampleRate, aValue);
}

void DvProviderLinnCoUkDs1Cpp::GetPropertyTrackSampleRate(uint32_t& aValue)
{
    aValue = iPropertyTrackSampleRate->Value();
}

bool DvProviderLinnCoUkDs1Cpp::SetPropertyTrackCodecName(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyTrackCodecName, buf);
}

void DvProviderLinnCoUkDs1Cpp::GetPropertyTrackCodecName(std::string& aValue)
{
    const Brx& val = iPropertyTrackCodecName->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderLinnCoUkDs1Cpp::SetPropertyTrackId(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyTrackId, aValue);
}

void DvProviderLinnCoUkDs1Cpp::GetPropertyTrackId(uint32_t& aValue)
{
    aValue = iPropertyTrackId->Value();
}

bool DvProviderLinnCoUkDs1Cpp::SetPropertyTransportState(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyTransportState, buf);
}

void DvProviderLinnCoUkDs1Cpp::GetPropertyTransportState(std::string& aValue)
{
    const Brx& val = iPropertyTransportState->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderLinnCoUkDs1Cpp::DvProviderLinnCoUkDs1Cpp(DvDeviceStd& aDevice)
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

void DvProviderLinnCoUkDs1Cpp::EnableActionPlay()
{
    Zapp::Action* action = new Zapp::Action("Play");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkDs1Cpp::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1Cpp::EnableActionPause()
{
    Zapp::Action* action = new Zapp::Action("Pause");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkDs1Cpp::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1Cpp::EnableActionStop()
{
    Zapp::Action* action = new Zapp::Action("Stop");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkDs1Cpp::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1Cpp::EnableActionSeekSecondAbsolute()
{
    Zapp::Action* action = new Zapp::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("aSecond"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkDs1Cpp::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1Cpp::EnableActionSeekSecondRelative()
{
    Zapp::Action* action = new Zapp::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("aSecond"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkDs1Cpp::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1Cpp::EnableActionSeekTrackId()
{
    Zapp::Action* action = new Zapp::Action("SeekTrackId");
    action->AddInputParameter(new ParameterRelated("aTrackId", *iPropertyTrackId));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkDs1Cpp::DoSeekTrackId);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1Cpp::EnableActionSeekTrackAbsolute()
{
    Zapp::Action* action = new Zapp::Action("SeekTrackAbsolute");
    action->AddInputParameter(new ParameterUint("aTrack"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkDs1Cpp::DoSeekTrackAbsolute);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1Cpp::EnableActionSeekTrackRelative()
{
    Zapp::Action* action = new Zapp::Action("SeekTrackRelative");
    action->AddInputParameter(new ParameterInt("aTrack"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkDs1Cpp::DoSeekTrackRelative);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1Cpp::EnableActionState()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkDs1Cpp::DoState);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1Cpp::EnableActionProtocolInfo()
{
    Zapp::Action* action = new Zapp::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("aSupportedProtocols", *iPropertySupportedProtocols));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkDs1Cpp::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDs1Cpp::DoPlay(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Play(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDs1Cpp::DoPause(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Pause(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDs1Cpp::DoStop(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Stop(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDs1Cpp::DoSeekSecondAbsolute(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aSecond = aInvocation.InvocationReadUint("aSecond");
    aInvocation.InvocationReadEnd();
    SeekSecondAbsolute(aVersion, aSecond);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDs1Cpp::DoSeekSecondRelative(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t aSecond = aInvocation.InvocationReadInt("aSecond");
    aInvocation.InvocationReadEnd();
    SeekSecondRelative(aVersion, aSecond);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDs1Cpp::DoSeekTrackId(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aTrackId = aInvocation.InvocationReadUint("aTrackId");
    aInvocation.InvocationReadEnd();
    SeekTrackId(aVersion, aTrackId);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDs1Cpp::DoSeekTrackAbsolute(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aTrack = aInvocation.InvocationReadUint("aTrack");
    aInvocation.InvocationReadEnd();
    SeekTrackAbsolute(aVersion, aTrack);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDs1Cpp::DoSeekTrackRelative(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t aTrack = aInvocation.InvocationReadInt("aTrack");
    aInvocation.InvocationReadEnd();
    SeekTrackRelative(aVersion, aTrack);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDs1Cpp::DoState(IDvInvocation& aInvocation, TUint aVersion)
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
    Brn buf_aTransportState((const TByte*)respaTransportState.c_str(), (TUint)respaTransportState.length());
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
    Brn buf_aTrackCodecName((const TByte*)respaTrackCodecName.c_str(), (TUint)respaTrackCodecName.length());
    respWriteraTrackCodecName.Write(buf_aTrackCodecName);
    aInvocation.InvocationWriteStringEnd("aTrackCodecName");
    InvocationResponseUint respWriteraTrackId(aInvocation, "aTrackId");
    respWriteraTrackId.Write(respaTrackId);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDs1Cpp::DoProtocolInfo(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaSupportedProtocols;
    ProtocolInfo(aVersion, respaSupportedProtocols);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraSupportedProtocols(aInvocation, "aSupportedProtocols");
    Brn buf_aSupportedProtocols((const TByte*)respaSupportedProtocols.c_str(), (TUint)respaSupportedProtocols.length());
    respWriteraSupportedProtocols.Write(buf_aSupportedProtocols);
    aInvocation.InvocationWriteStringEnd("aSupportedProtocols");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDs1Cpp::Play(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1Cpp::Pause(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1Cpp::Stop(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1Cpp::SeekSecondAbsolute(uint32_t /*aVersion*/, uint32_t /*aaSecond*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1Cpp::SeekSecondRelative(uint32_t /*aVersion*/, int32_t /*aaSecond*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1Cpp::SeekTrackId(uint32_t /*aVersion*/, uint32_t /*aaTrackId*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1Cpp::SeekTrackAbsolute(uint32_t /*aVersion*/, uint32_t /*aaTrack*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1Cpp::SeekTrackRelative(uint32_t /*aVersion*/, int32_t /*aaTrack*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1Cpp::State(uint32_t /*aVersion*/, std::string& /*aaTransportState*/, uint32_t& /*aaTrackDuration*/, uint32_t& /*aaTrackBitRate*/, bool& /*aaTrackLossless*/, uint32_t& /*aaTrackBitDepth*/, uint32_t& /*aaTrackSampleRate*/, std::string& /*aaTrackCodecName*/, uint32_t& /*aaTrackId*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDs1Cpp::ProtocolInfo(uint32_t /*aVersion*/, std::string& /*aaSupportedProtocols*/)
{
    ASSERTS();
}

