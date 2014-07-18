#include "DvUpnpOrgAVTransport1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgAVTransport1Cpp::SetPropertyLastChange(const std::string& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyLastChange, buf);
}

void DvProviderUpnpOrgAVTransport1Cpp::GetPropertyLastChange(std::string& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    const Brx& val = iPropertyLastChange->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderUpnpOrgAVTransport1Cpp::DvProviderUpnpOrgAVTransport1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "AVTransport", 1)
{
    iPropertyLastChange = NULL;
}

void DvProviderUpnpOrgAVTransport1Cpp::EnablePropertyLastChange()
{
    iPropertyLastChange = new PropertyString(iDvStack.Env(), new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionSetAVTransportURI()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("CurrentURI"));
    action->AddInputParameter(new ParameterString("CurrentURIMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoSetAVTransportURI);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionSetNextAVTransportURI()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetNextAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NextURI"));
    action->AddInputParameter(new ParameterString("NextURIMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoSetNextAVTransportURI);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionGetMediaInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetMediaInfo");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("NrTracks", 0));
    action->AddOutputParameter(new ParameterString("MediaDuration"));
    action->AddOutputParameter(new ParameterString("CurrentURI"));
    action->AddOutputParameter(new ParameterString("CurrentURIMetaData"));
    action->AddOutputParameter(new ParameterString("NextURI"));
    action->AddOutputParameter(new ParameterString("NextURIMetaData"));
    action->AddOutputParameter(new ParameterString("PlayMedium"));
    action->AddOutputParameter(new ParameterString("RecordMedium"));
    index = 0;
    allowedValues = new TChar*[5];
    allowedValues[index++] = (TChar*)"WRITABLE";
    allowedValues[index++] = (TChar*)"PROTECTED";
    allowedValues[index++] = (TChar*)"NOT_WRITABLE";
    allowedValues[index++] = (TChar*)"UNKNOWN";
    allowedValues[index++] = (TChar*)"NOT_IMPLEMENTED";
    action->AddOutputParameter(new ParameterString("WriteStatus", allowedValues, 5));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoGetMediaInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionGetTransportInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetTransportInfo");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[7];
    allowedValues[index++] = (TChar*)"STOPPED";
    allowedValues[index++] = (TChar*)"PLAYING";
    allowedValues[index++] = (TChar*)"TRANSITIONING";
    allowedValues[index++] = (TChar*)"PAUSED_PLAYBACK";
    allowedValues[index++] = (TChar*)"PAUSED_RECORDING";
    allowedValues[index++] = (TChar*)"RECORDING";
    allowedValues[index++] = (TChar*)"NO_MEDIA_PRESENT";
    action->AddOutputParameter(new ParameterString("CurrentTransportState", allowedValues, 7));
    delete[] allowedValues;
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"OK";
    allowedValues[index++] = (TChar*)"ERROR_OCCURRED";
    action->AddOutputParameter(new ParameterString("CurrentTransportStatus", allowedValues, 2));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterString("CurrentSpeed"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoGetTransportInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionGetPositionInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetPositionInfo");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("Track", 0, 2147483647, 1));
    action->AddOutputParameter(new ParameterString("TrackDuration"));
    action->AddOutputParameter(new ParameterString("TrackMetaData"));
    action->AddOutputParameter(new ParameterString("TrackURI"));
    action->AddOutputParameter(new ParameterString("RelTime"));
    action->AddOutputParameter(new ParameterString("AbsTime"));
    action->AddOutputParameter(new ParameterInt("RelCount"));
    action->AddOutputParameter(new ParameterInt("AbsCount"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoGetPositionInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionGetDeviceCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetDeviceCapabilities");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("PlayMedia"));
    action->AddOutputParameter(new ParameterString("RecMedia"));
    action->AddOutputParameter(new ParameterString("RecQualityModes"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoGetDeviceCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionGetTransportSettings()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetTransportSettings");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"NORMAL";
    action->AddOutputParameter(new ParameterString("PlayMode", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterString("RecQualityMode"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoGetTransportSettings);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionStop()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionPlay()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Speed"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionPause()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Pause");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionRecord()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Record");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoRecord);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionSeek()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Seek");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[8];
    allowedValues[index++] = (TChar*)"TRACK_NR";
    allowedValues[index++] = (TChar*)"ABS_TIME";
    allowedValues[index++] = (TChar*)"REL_TIME";
    allowedValues[index++] = (TChar*)"ABS_COUNT";
    allowedValues[index++] = (TChar*)"REL_COUNT";
    allowedValues[index++] = (TChar*)"CHANNEL_FREQ";
    allowedValues[index++] = (TChar*)"TAPE-INDEX";
    allowedValues[index++] = (TChar*)"FRAME";
    action->AddInputParameter(new ParameterString("Unit", allowedValues, 8));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterString("Target"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoSeek);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionNext()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Next");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoNext);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionPrevious()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Previous");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoPrevious);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionSetPlayMode()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetPlayMode");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"NORMAL";
    action->AddInputParameter(new ParameterString("NewPlayMode", allowedValues, 1));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoSetPlayMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionSetRecordQualityMode()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRecordQualityMode");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NewRecordQualityMode"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoSetRecordQualityMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::EnableActionGetCurrentTransportActions()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetCurrentTransportActions");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("Actions"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1Cpp::DoGetCurrentTransportActions);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1Cpp::DoSetAVTransportURI(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    SetAVTransportURI(invocation, InstanceID, CurrentURI, CurrentURIMetaData);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoSetNextAVTransportURI(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    SetNextAVTransportURI(invocation, InstanceID, NextURI, NextURIMetaData);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoGetMediaInfo(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    GetMediaInfo(invocation, InstanceID, respNrTracks, respMediaDuration, respCurrentURI, respCurrentURIMetaData, respNextURI, respNextURIMetaData, respPlayMedium, respRecordMedium, respWriteStatus);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterNrTracks(aInvocation, "NrTracks");
    respWriterNrTracks.Write(respNrTracks);
    DviInvocationResponseString respWriterMediaDuration(aInvocation, "MediaDuration");
    Brn buf_MediaDuration((const TByte*)respMediaDuration.c_str(), (TUint)respMediaDuration.length());
    respWriterMediaDuration.Write(buf_MediaDuration);
    aInvocation.InvocationWriteStringEnd("MediaDuration");
    DviInvocationResponseString respWriterCurrentURI(aInvocation, "CurrentURI");
    Brn buf_CurrentURI((const TByte*)respCurrentURI.c_str(), (TUint)respCurrentURI.length());
    respWriterCurrentURI.Write(buf_CurrentURI);
    aInvocation.InvocationWriteStringEnd("CurrentURI");
    DviInvocationResponseString respWriterCurrentURIMetaData(aInvocation, "CurrentURIMetaData");
    Brn buf_CurrentURIMetaData((const TByte*)respCurrentURIMetaData.c_str(), (TUint)respCurrentURIMetaData.length());
    respWriterCurrentURIMetaData.Write(buf_CurrentURIMetaData);
    aInvocation.InvocationWriteStringEnd("CurrentURIMetaData");
    DviInvocationResponseString respWriterNextURI(aInvocation, "NextURI");
    Brn buf_NextURI((const TByte*)respNextURI.c_str(), (TUint)respNextURI.length());
    respWriterNextURI.Write(buf_NextURI);
    aInvocation.InvocationWriteStringEnd("NextURI");
    DviInvocationResponseString respWriterNextURIMetaData(aInvocation, "NextURIMetaData");
    Brn buf_NextURIMetaData((const TByte*)respNextURIMetaData.c_str(), (TUint)respNextURIMetaData.length());
    respWriterNextURIMetaData.Write(buf_NextURIMetaData);
    aInvocation.InvocationWriteStringEnd("NextURIMetaData");
    DviInvocationResponseString respWriterPlayMedium(aInvocation, "PlayMedium");
    Brn buf_PlayMedium((const TByte*)respPlayMedium.c_str(), (TUint)respPlayMedium.length());
    respWriterPlayMedium.Write(buf_PlayMedium);
    aInvocation.InvocationWriteStringEnd("PlayMedium");
    DviInvocationResponseString respWriterRecordMedium(aInvocation, "RecordMedium");
    Brn buf_RecordMedium((const TByte*)respRecordMedium.c_str(), (TUint)respRecordMedium.length());
    respWriterRecordMedium.Write(buf_RecordMedium);
    aInvocation.InvocationWriteStringEnd("RecordMedium");
    DviInvocationResponseString respWriterWriteStatus(aInvocation, "WriteStatus");
    Brn buf_WriteStatus((const TByte*)respWriteStatus.c_str(), (TUint)respWriteStatus.length());
    respWriterWriteStatus.Write(buf_WriteStatus);
    aInvocation.InvocationWriteStringEnd("WriteStatus");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoGetTransportInfo(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respCurrentTransportState;
    std::string respCurrentTransportStatus;
    std::string respCurrentSpeed;
    DvInvocationStd invocation(aInvocation);
    GetTransportInfo(invocation, InstanceID, respCurrentTransportState, respCurrentTransportStatus, respCurrentSpeed);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterCurrentTransportState(aInvocation, "CurrentTransportState");
    Brn buf_CurrentTransportState((const TByte*)respCurrentTransportState.c_str(), (TUint)respCurrentTransportState.length());
    respWriterCurrentTransportState.Write(buf_CurrentTransportState);
    aInvocation.InvocationWriteStringEnd("CurrentTransportState");
    DviInvocationResponseString respWriterCurrentTransportStatus(aInvocation, "CurrentTransportStatus");
    Brn buf_CurrentTransportStatus((const TByte*)respCurrentTransportStatus.c_str(), (TUint)respCurrentTransportStatus.length());
    respWriterCurrentTransportStatus.Write(buf_CurrentTransportStatus);
    aInvocation.InvocationWriteStringEnd("CurrentTransportStatus");
    DviInvocationResponseString respWriterCurrentSpeed(aInvocation, "CurrentSpeed");
    Brn buf_CurrentSpeed((const TByte*)respCurrentSpeed.c_str(), (TUint)respCurrentSpeed.length());
    respWriterCurrentSpeed.Write(buf_CurrentSpeed);
    aInvocation.InvocationWriteStringEnd("CurrentSpeed");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoGetPositionInfo(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    GetPositionInfo(invocation, InstanceID, respTrack, respTrackDuration, respTrackMetaData, respTrackURI, respRelTime, respAbsTime, respRelCount, respAbsCount);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterTrack(aInvocation, "Track");
    respWriterTrack.Write(respTrack);
    DviInvocationResponseString respWriterTrackDuration(aInvocation, "TrackDuration");
    Brn buf_TrackDuration((const TByte*)respTrackDuration.c_str(), (TUint)respTrackDuration.length());
    respWriterTrackDuration.Write(buf_TrackDuration);
    aInvocation.InvocationWriteStringEnd("TrackDuration");
    DviInvocationResponseString respWriterTrackMetaData(aInvocation, "TrackMetaData");
    Brn buf_TrackMetaData((const TByte*)respTrackMetaData.c_str(), (TUint)respTrackMetaData.length());
    respWriterTrackMetaData.Write(buf_TrackMetaData);
    aInvocation.InvocationWriteStringEnd("TrackMetaData");
    DviInvocationResponseString respWriterTrackURI(aInvocation, "TrackURI");
    Brn buf_TrackURI((const TByte*)respTrackURI.c_str(), (TUint)respTrackURI.length());
    respWriterTrackURI.Write(buf_TrackURI);
    aInvocation.InvocationWriteStringEnd("TrackURI");
    DviInvocationResponseString respWriterRelTime(aInvocation, "RelTime");
    Brn buf_RelTime((const TByte*)respRelTime.c_str(), (TUint)respRelTime.length());
    respWriterRelTime.Write(buf_RelTime);
    aInvocation.InvocationWriteStringEnd("RelTime");
    DviInvocationResponseString respWriterAbsTime(aInvocation, "AbsTime");
    Brn buf_AbsTime((const TByte*)respAbsTime.c_str(), (TUint)respAbsTime.length());
    respWriterAbsTime.Write(buf_AbsTime);
    aInvocation.InvocationWriteStringEnd("AbsTime");
    DviInvocationResponseInt respWriterRelCount(aInvocation, "RelCount");
    respWriterRelCount.Write(respRelCount);
    DviInvocationResponseInt respWriterAbsCount(aInvocation, "AbsCount");
    respWriterAbsCount.Write(respAbsCount);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoGetDeviceCapabilities(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respPlayMedia;
    std::string respRecMedia;
    std::string respRecQualityModes;
    DvInvocationStd invocation(aInvocation);
    GetDeviceCapabilities(invocation, InstanceID, respPlayMedia, respRecMedia, respRecQualityModes);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterPlayMedia(aInvocation, "PlayMedia");
    Brn buf_PlayMedia((const TByte*)respPlayMedia.c_str(), (TUint)respPlayMedia.length());
    respWriterPlayMedia.Write(buf_PlayMedia);
    aInvocation.InvocationWriteStringEnd("PlayMedia");
    DviInvocationResponseString respWriterRecMedia(aInvocation, "RecMedia");
    Brn buf_RecMedia((const TByte*)respRecMedia.c_str(), (TUint)respRecMedia.length());
    respWriterRecMedia.Write(buf_RecMedia);
    aInvocation.InvocationWriteStringEnd("RecMedia");
    DviInvocationResponseString respWriterRecQualityModes(aInvocation, "RecQualityModes");
    Brn buf_RecQualityModes((const TByte*)respRecQualityModes.c_str(), (TUint)respRecQualityModes.length());
    respWriterRecQualityModes.Write(buf_RecQualityModes);
    aInvocation.InvocationWriteStringEnd("RecQualityModes");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoGetTransportSettings(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respPlayMode;
    std::string respRecQualityMode;
    DvInvocationStd invocation(aInvocation);
    GetTransportSettings(invocation, InstanceID, respPlayMode, respRecQualityMode);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterPlayMode(aInvocation, "PlayMode");
    Brn buf_PlayMode((const TByte*)respPlayMode.c_str(), (TUint)respPlayMode.length());
    respWriterPlayMode.Write(buf_PlayMode);
    aInvocation.InvocationWriteStringEnd("PlayMode");
    DviInvocationResponseString respWriterRecQualityMode(aInvocation, "RecQualityMode");
    Brn buf_RecQualityMode((const TByte*)respRecQualityMode.c_str(), (TUint)respRecQualityMode.length());
    respWriterRecQualityMode.Write(buf_RecQualityMode);
    aInvocation.InvocationWriteStringEnd("RecQualityMode");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoStop(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Stop(invocation, InstanceID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoPlay(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Speed;
    aInvocation.InvocationReadString("Speed", buf_Speed);
    std::string Speed((const char*)buf_Speed.Ptr(), buf_Speed.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Play(invocation, InstanceID, Speed);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoPause(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Pause(invocation, InstanceID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoRecord(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Record(invocation, InstanceID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoSeek(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    Seek(invocation, InstanceID, Unit, Target);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoNext(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Next(invocation, InstanceID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoPrevious(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Previous(invocation, InstanceID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoSetPlayMode(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_NewPlayMode;
    aInvocation.InvocationReadString("NewPlayMode", buf_NewPlayMode);
    std::string NewPlayMode((const char*)buf_NewPlayMode.Ptr(), buf_NewPlayMode.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetPlayMode(invocation, InstanceID, NewPlayMode);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoSetRecordQualityMode(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_NewRecordQualityMode;
    aInvocation.InvocationReadString("NewRecordQualityMode", buf_NewRecordQualityMode);
    std::string NewRecordQualityMode((const char*)buf_NewRecordQualityMode.Ptr(), buf_NewRecordQualityMode.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetRecordQualityMode(invocation, InstanceID, NewRecordQualityMode);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::DoGetCurrentTransportActions(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respActions;
    DvInvocationStd invocation(aInvocation);
    GetCurrentTransportActions(invocation, InstanceID, respActions);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterActions(aInvocation, "Actions");
    Brn buf_Actions((const TByte*)respActions.c_str(), (TUint)respActions.length());
    respWriterActions.Write(buf_Actions);
    aInvocation.InvocationWriteStringEnd("Actions");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport1Cpp::SetAVTransportURI(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aCurrentURI*/, const std::string& /*aCurrentURIMetaData*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::SetNextAVTransportURI(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aNextURI*/, const std::string& /*aNextURIMetaData*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::GetMediaInfo(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aNrTracks*/, std::string& /*aMediaDuration*/, std::string& /*aCurrentURI*/, std::string& /*aCurrentURIMetaData*/, std::string& /*aNextURI*/, std::string& /*aNextURIMetaData*/, std::string& /*aPlayMedium*/, std::string& /*aRecordMedium*/, std::string& /*aWriteStatus*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::GetTransportInfo(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, std::string& /*aCurrentTransportState*/, std::string& /*aCurrentTransportStatus*/, std::string& /*aCurrentSpeed*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::GetPositionInfo(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aTrack*/, std::string& /*aTrackDuration*/, std::string& /*aTrackMetaData*/, std::string& /*aTrackURI*/, std::string& /*aRelTime*/, std::string& /*aAbsTime*/, int32_t& /*aRelCount*/, int32_t& /*aAbsCount*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::GetDeviceCapabilities(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, std::string& /*aPlayMedia*/, std::string& /*aRecMedia*/, std::string& /*aRecQualityModes*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::GetTransportSettings(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, std::string& /*aPlayMode*/, std::string& /*aRecQualityMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::Stop(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::Play(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aSpeed*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::Pause(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::Record(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::Seek(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aUnit*/, const std::string& /*aTarget*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::Next(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::Previous(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::SetPlayMode(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aNewPlayMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::SetRecordQualityMode(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aNewRecordQualityMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1Cpp::GetCurrentTransportActions(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, std::string& /*aActions*/)
{
    ASSERTS();
}

