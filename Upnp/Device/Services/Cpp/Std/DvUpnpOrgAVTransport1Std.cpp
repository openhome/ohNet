#include <Std/DvUpnpOrgAVTransport1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgAVTransport1Cpp::SetPropertyLastChange(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyLastChange, buf);
}

void DvServiceUpnpOrgAVTransport1Cpp::GetPropertyLastChange(std::string& aValue)
{
    const Brx& val = iPropertyLastChange->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvServiceUpnpOrgAVTransport1Cpp::DvServiceUpnpOrgAVTransport1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "upnp.org", "AVTransport", 1)
{
    Functor empty;
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"), empty);
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionSetAVTransportURI()
{
    Zapp::Action* action = new Zapp::Action("SetAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("CurrentURI"));
    action->AddInputParameter(new ParameterString("CurrentURIMetaData"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoSetAVTransportURI);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionSetNextAVTransportURI()
{
    Zapp::Action* action = new Zapp::Action("SetNextAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NextURI"));
    action->AddInputParameter(new ParameterString("NextURIMetaData"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoSetNextAVTransportURI);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionGetMediaInfo()
{
    Zapp::Action* action = new Zapp::Action("GetMediaInfo");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("NrTracks", 0, 0));
    action->AddOutputParameter(new ParameterString("MediaDuration"));
    action->AddOutputParameter(new ParameterString("CurrentURI"));
    action->AddOutputParameter(new ParameterString("CurrentURIMetaData"));
    action->AddOutputParameter(new ParameterString("NextURI"));
    action->AddOutputParameter(new ParameterString("NextURIMetaData"));
    action->AddOutputParameter(new ParameterString("PlayMedium"));
    action->AddOutputParameter(new ParameterString("RecordMedium"));
    action->AddOutputParameter(new ParameterString("WriteStatus"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoGetMediaInfo);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionGetTransportInfo()
{
    Zapp::Action* action = new Zapp::Action("GetTransportInfo");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"STOPPED";
    allowedValues[index++] = (TChar*)"PLAYING";
    action->AddOutputParameter(new ParameterString("CurrentTransportState", allowedValues, 2));
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"OK";
    allowedValues[index++] = (TChar*)"ERROR_OCCURRED";
    action->AddOutputParameter(new ParameterString("CurrentTransportStatus", allowedValues, 2));
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"1";
    action->AddOutputParameter(new ParameterString("CurrentSpeed", allowedValues, 1));
    delete[] allowedValues;
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoGetTransportInfo);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionGetPositionInfo()
{
    Zapp::Action* action = new Zapp::Action("GetPositionInfo");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("Track", 0, 0, 1));
    action->AddOutputParameter(new ParameterString("TrackDuration"));
    action->AddOutputParameter(new ParameterString("TrackMetaData"));
    action->AddOutputParameter(new ParameterString("TrackURI"));
    action->AddOutputParameter(new ParameterString("RelTime"));
    action->AddOutputParameter(new ParameterString("AbsTime"));
    action->AddOutputParameter(new ParameterInt("RelCount"));
    action->AddOutputParameter(new ParameterInt("AbsCount"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoGetPositionInfo);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionGetDeviceCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetDeviceCapabilities");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("PlayMedia"));
    action->AddOutputParameter(new ParameterString("RecMedia"));
    action->AddOutputParameter(new ParameterString("RecQualityModes"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoGetDeviceCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionGetTransportSettings()
{
    Zapp::Action* action = new Zapp::Action("GetTransportSettings");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"NORMAL";
    action->AddOutputParameter(new ParameterString("PlayMode", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterString("RecQualityMode"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoGetTransportSettings);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionStop()
{
    Zapp::Action* action = new Zapp::Action("Stop");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoStop);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionPlay()
{
    Zapp::Action* action = new Zapp::Action("Play");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"1";
    action->AddInputParameter(new ParameterString("Speed", allowedValues, 1));
    delete[] allowedValues;
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoPlay);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionPause()
{
    Zapp::Action* action = new Zapp::Action("Pause");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoPause);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionRecord()
{
    Zapp::Action* action = new Zapp::Action("Record");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoRecord);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionSeek()
{
    Zapp::Action* action = new Zapp::Action("Seek");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"TRACK_NR";
    action->AddInputParameter(new ParameterString("Unit", allowedValues, 1));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterString("Target"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoSeek);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionNext()
{
    Zapp::Action* action = new Zapp::Action("Next");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoNext);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionPrevious()
{
    Zapp::Action* action = new Zapp::Action("Previous");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoPrevious);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionSetPlayMode()
{
    Zapp::Action* action = new Zapp::Action("SetPlayMode");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"NORMAL";
    action->AddInputParameter(new ParameterString("NewPlayMode", allowedValues, 1));
    delete[] allowedValues;
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoSetPlayMode);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionSetRecordQualityMode()
{
    Zapp::Action* action = new Zapp::Action("SetRecordQualityMode");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NewRecordQualityMode"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoSetRecordQualityMode);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::EnableActionGetCurrentTransportActions()
{
    Zapp::Action* action = new Zapp::Action("GetCurrentTransportActions");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("Actions"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgAVTransport1Cpp::DoGetCurrentTransportActions);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgAVTransport1Cpp::DoSetAVTransportURI(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_CurrentURI;
    aInvocation.InvocationReadString("CurrentURI", buf_CurrentURI);
    std::string CurrentURI((const char*)buf_CurrentURI.Ptr(), buf_CurrentURI.Bytes());
    Brhz buf_CurrentURIMetaData;
    aInvocation.InvocationReadString("CurrentURIMetaData", buf_CurrentURIMetaData);
    std::string CurrentURIMetaData((const char*)buf_CurrentURIMetaData.Ptr(), buf_CurrentURIMetaData.Bytes());
    aInvocation.InvocationReadEnd();
    SetAVTransportURI(aVersion, InstanceID, CurrentURI, CurrentURIMetaData);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoSetNextAVTransportURI(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_NextURI;
    aInvocation.InvocationReadString("NextURI", buf_NextURI);
    std::string NextURI((const char*)buf_NextURI.Ptr(), buf_NextURI.Bytes());
    Brhz buf_NextURIMetaData;
    aInvocation.InvocationReadString("NextURIMetaData", buf_NextURIMetaData);
    std::string NextURIMetaData((const char*)buf_NextURIMetaData.Ptr(), buf_NextURIMetaData.Bytes());
    aInvocation.InvocationReadEnd();
    SetNextAVTransportURI(aVersion, InstanceID, NextURI, NextURIMetaData);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoGetMediaInfo(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respNrTracks;
    std::string respMediaDuration;
    std::string respCurrentURI;
    std::string respCurrentURIMetaData;
    std::string respNextURI;
    std::string respNextURIMetaData;
    std::string respPlayMedium;
    std::string respRecordMedium;
    std::string respWriteStatus;
    GetMediaInfo(aVersion, InstanceID, respNrTracks, respMediaDuration, respCurrentURI, respCurrentURIMetaData, respNextURI, respNextURIMetaData, respPlayMedium, respRecordMedium, respWriteStatus);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterNrTracks(aInvocation, "NrTracks");
    respWriterNrTracks.Write(respNrTracks);
    InvocationResponseString respWriterMediaDuration(aInvocation, "MediaDuration");
    Brn buf_MediaDuration((const TByte*)respMediaDuration.c_str(), respMediaDuration.length());
    respWriterMediaDuration.Write(buf_MediaDuration);
    aInvocation.InvocationWriteStringEnd("MediaDuration");
    InvocationResponseString respWriterCurrentURI(aInvocation, "CurrentURI");
    Brn buf_CurrentURI((const TByte*)respCurrentURI.c_str(), respCurrentURI.length());
    respWriterCurrentURI.Write(buf_CurrentURI);
    aInvocation.InvocationWriteStringEnd("CurrentURI");
    InvocationResponseString respWriterCurrentURIMetaData(aInvocation, "CurrentURIMetaData");
    Brn buf_CurrentURIMetaData((const TByte*)respCurrentURIMetaData.c_str(), respCurrentURIMetaData.length());
    respWriterCurrentURIMetaData.Write(buf_CurrentURIMetaData);
    aInvocation.InvocationWriteStringEnd("CurrentURIMetaData");
    InvocationResponseString respWriterNextURI(aInvocation, "NextURI");
    Brn buf_NextURI((const TByte*)respNextURI.c_str(), respNextURI.length());
    respWriterNextURI.Write(buf_NextURI);
    aInvocation.InvocationWriteStringEnd("NextURI");
    InvocationResponseString respWriterNextURIMetaData(aInvocation, "NextURIMetaData");
    Brn buf_NextURIMetaData((const TByte*)respNextURIMetaData.c_str(), respNextURIMetaData.length());
    respWriterNextURIMetaData.Write(buf_NextURIMetaData);
    aInvocation.InvocationWriteStringEnd("NextURIMetaData");
    InvocationResponseString respWriterPlayMedium(aInvocation, "PlayMedium");
    Brn buf_PlayMedium((const TByte*)respPlayMedium.c_str(), respPlayMedium.length());
    respWriterPlayMedium.Write(buf_PlayMedium);
    aInvocation.InvocationWriteStringEnd("PlayMedium");
    InvocationResponseString respWriterRecordMedium(aInvocation, "RecordMedium");
    Brn buf_RecordMedium((const TByte*)respRecordMedium.c_str(), respRecordMedium.length());
    respWriterRecordMedium.Write(buf_RecordMedium);
    aInvocation.InvocationWriteStringEnd("RecordMedium");
    InvocationResponseString respWriterWriteStatus(aInvocation, "WriteStatus");
    Brn buf_WriteStatus((const TByte*)respWriteStatus.c_str(), respWriteStatus.length());
    respWriterWriteStatus.Write(buf_WriteStatus);
    aInvocation.InvocationWriteStringEnd("WriteStatus");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoGetTransportInfo(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respCurrentTransportState;
    std::string respCurrentTransportStatus;
    std::string respCurrentSpeed;
    GetTransportInfo(aVersion, InstanceID, respCurrentTransportState, respCurrentTransportStatus, respCurrentSpeed);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterCurrentTransportState(aInvocation, "CurrentTransportState");
    Brn buf_CurrentTransportState((const TByte*)respCurrentTransportState.c_str(), respCurrentTransportState.length());
    respWriterCurrentTransportState.Write(buf_CurrentTransportState);
    aInvocation.InvocationWriteStringEnd("CurrentTransportState");
    InvocationResponseString respWriterCurrentTransportStatus(aInvocation, "CurrentTransportStatus");
    Brn buf_CurrentTransportStatus((const TByte*)respCurrentTransportStatus.c_str(), respCurrentTransportStatus.length());
    respWriterCurrentTransportStatus.Write(buf_CurrentTransportStatus);
    aInvocation.InvocationWriteStringEnd("CurrentTransportStatus");
    InvocationResponseString respWriterCurrentSpeed(aInvocation, "CurrentSpeed");
    Brn buf_CurrentSpeed((const TByte*)respCurrentSpeed.c_str(), respCurrentSpeed.length());
    respWriterCurrentSpeed.Write(buf_CurrentSpeed);
    aInvocation.InvocationWriteStringEnd("CurrentSpeed");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoGetPositionInfo(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respTrack;
    std::string respTrackDuration;
    std::string respTrackMetaData;
    std::string respTrackURI;
    std::string respRelTime;
    std::string respAbsTime;
    int32_t respRelCount;
    int32_t respAbsCount;
    GetPositionInfo(aVersion, InstanceID, respTrack, respTrackDuration, respTrackMetaData, respTrackURI, respRelTime, respAbsTime, respRelCount, respAbsCount);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterTrack(aInvocation, "Track");
    respWriterTrack.Write(respTrack);
    InvocationResponseString respWriterTrackDuration(aInvocation, "TrackDuration");
    Brn buf_TrackDuration((const TByte*)respTrackDuration.c_str(), respTrackDuration.length());
    respWriterTrackDuration.Write(buf_TrackDuration);
    aInvocation.InvocationWriteStringEnd("TrackDuration");
    InvocationResponseString respWriterTrackMetaData(aInvocation, "TrackMetaData");
    Brn buf_TrackMetaData((const TByte*)respTrackMetaData.c_str(), respTrackMetaData.length());
    respWriterTrackMetaData.Write(buf_TrackMetaData);
    aInvocation.InvocationWriteStringEnd("TrackMetaData");
    InvocationResponseString respWriterTrackURI(aInvocation, "TrackURI");
    Brn buf_TrackURI((const TByte*)respTrackURI.c_str(), respTrackURI.length());
    respWriterTrackURI.Write(buf_TrackURI);
    aInvocation.InvocationWriteStringEnd("TrackURI");
    InvocationResponseString respWriterRelTime(aInvocation, "RelTime");
    Brn buf_RelTime((const TByte*)respRelTime.c_str(), respRelTime.length());
    respWriterRelTime.Write(buf_RelTime);
    aInvocation.InvocationWriteStringEnd("RelTime");
    InvocationResponseString respWriterAbsTime(aInvocation, "AbsTime");
    Brn buf_AbsTime((const TByte*)respAbsTime.c_str(), respAbsTime.length());
    respWriterAbsTime.Write(buf_AbsTime);
    aInvocation.InvocationWriteStringEnd("AbsTime");
    InvocationResponseInt respWriterRelCount(aInvocation, "RelCount");
    respWriterRelCount.Write(respRelCount);
    InvocationResponseInt respWriterAbsCount(aInvocation, "AbsCount");
    respWriterAbsCount.Write(respAbsCount);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoGetDeviceCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respPlayMedia;
    std::string respRecMedia;
    std::string respRecQualityModes;
    GetDeviceCapabilities(aVersion, InstanceID, respPlayMedia, respRecMedia, respRecQualityModes);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterPlayMedia(aInvocation, "PlayMedia");
    Brn buf_PlayMedia((const TByte*)respPlayMedia.c_str(), respPlayMedia.length());
    respWriterPlayMedia.Write(buf_PlayMedia);
    aInvocation.InvocationWriteStringEnd("PlayMedia");
    InvocationResponseString respWriterRecMedia(aInvocation, "RecMedia");
    Brn buf_RecMedia((const TByte*)respRecMedia.c_str(), respRecMedia.length());
    respWriterRecMedia.Write(buf_RecMedia);
    aInvocation.InvocationWriteStringEnd("RecMedia");
    InvocationResponseString respWriterRecQualityModes(aInvocation, "RecQualityModes");
    Brn buf_RecQualityModes((const TByte*)respRecQualityModes.c_str(), respRecQualityModes.length());
    respWriterRecQualityModes.Write(buf_RecQualityModes);
    aInvocation.InvocationWriteStringEnd("RecQualityModes");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoGetTransportSettings(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respPlayMode;
    std::string respRecQualityMode;
    GetTransportSettings(aVersion, InstanceID, respPlayMode, respRecQualityMode);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterPlayMode(aInvocation, "PlayMode");
    Brn buf_PlayMode((const TByte*)respPlayMode.c_str(), respPlayMode.length());
    respWriterPlayMode.Write(buf_PlayMode);
    aInvocation.InvocationWriteStringEnd("PlayMode");
    InvocationResponseString respWriterRecQualityMode(aInvocation, "RecQualityMode");
    Brn buf_RecQualityMode((const TByte*)respRecQualityMode.c_str(), respRecQualityMode.length());
    respWriterRecQualityMode.Write(buf_RecQualityMode);
    aInvocation.InvocationWriteStringEnd("RecQualityMode");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoStop(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    Stop(aVersion, InstanceID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoPlay(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Speed;
    aInvocation.InvocationReadString("Speed", buf_Speed);
    std::string Speed((const char*)buf_Speed.Ptr(), buf_Speed.Bytes());
    aInvocation.InvocationReadEnd();
    Play(aVersion, InstanceID, Speed);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoPause(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    Pause(aVersion, InstanceID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoRecord(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    Record(aVersion, InstanceID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoSeek(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Unit;
    aInvocation.InvocationReadString("Unit", buf_Unit);
    std::string Unit((const char*)buf_Unit.Ptr(), buf_Unit.Bytes());
    Brhz buf_Target;
    aInvocation.InvocationReadString("Target", buf_Target);
    std::string Target((const char*)buf_Target.Ptr(), buf_Target.Bytes());
    aInvocation.InvocationReadEnd();
    Seek(aVersion, InstanceID, Unit, Target);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoNext(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    Next(aVersion, InstanceID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoPrevious(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    Previous(aVersion, InstanceID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoSetPlayMode(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_NewPlayMode;
    aInvocation.InvocationReadString("NewPlayMode", buf_NewPlayMode);
    std::string NewPlayMode((const char*)buf_NewPlayMode.Ptr(), buf_NewPlayMode.Bytes());
    aInvocation.InvocationReadEnd();
    SetPlayMode(aVersion, InstanceID, NewPlayMode);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoSetRecordQualityMode(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_NewRecordQualityMode;
    aInvocation.InvocationReadString("NewRecordQualityMode", buf_NewRecordQualityMode);
    std::string NewRecordQualityMode((const char*)buf_NewRecordQualityMode.Ptr(), buf_NewRecordQualityMode.Bytes());
    aInvocation.InvocationReadEnd();
    SetRecordQualityMode(aVersion, InstanceID, NewRecordQualityMode);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::DoGetCurrentTransportActions(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respActions;
    GetCurrentTransportActions(aVersion, InstanceID, respActions);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterActions(aInvocation, "Actions");
    Brn buf_Actions((const TByte*)respActions.c_str(), respActions.length());
    respWriterActions.Write(buf_Actions);
    aInvocation.InvocationWriteStringEnd("Actions");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgAVTransport1Cpp::SetAVTransportURI(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aCurrentURI*/, const std::string& /*aCurrentURIMetaData*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::SetNextAVTransportURI(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aNextURI*/, const std::string& /*aNextURIMetaData*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::GetMediaInfo(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aNrTracks*/, std::string& /*aMediaDuration*/, std::string& /*aCurrentURI*/, std::string& /*aCurrentURIMetaData*/, std::string& /*aNextURI*/, std::string& /*aNextURIMetaData*/, std::string& /*aPlayMedium*/, std::string& /*aRecordMedium*/, std::string& /*aWriteStatus*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::GetTransportInfo(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, std::string& /*aCurrentTransportState*/, std::string& /*aCurrentTransportStatus*/, std::string& /*aCurrentSpeed*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::GetPositionInfo(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aTrack*/, std::string& /*aTrackDuration*/, std::string& /*aTrackMetaData*/, std::string& /*aTrackURI*/, std::string& /*aRelTime*/, std::string& /*aAbsTime*/, int32_t& /*aRelCount*/, int32_t& /*aAbsCount*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::GetDeviceCapabilities(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, std::string& /*aPlayMedia*/, std::string& /*aRecMedia*/, std::string& /*aRecQualityModes*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::GetTransportSettings(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, std::string& /*aPlayMode*/, std::string& /*aRecQualityMode*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::Stop(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::Play(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aSpeed*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::Pause(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::Record(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::Seek(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aUnit*/, const std::string& /*aTarget*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::Next(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::Previous(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::SetPlayMode(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aNewPlayMode*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::SetRecordQualityMode(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aNewRecordQualityMode*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgAVTransport1Cpp::GetCurrentTransportActions(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, std::string& /*aActions*/)
{
    ASSERTS();
}

