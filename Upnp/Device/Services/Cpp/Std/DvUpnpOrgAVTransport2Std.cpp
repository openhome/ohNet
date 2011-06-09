#include "DvUpnpOrgAVTransport2.h"
#include <OhNetTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgAVTransport2Cpp::SetPropertyLastChange(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyLastChange, buf);
}

void DvProviderUpnpOrgAVTransport2Cpp::GetPropertyLastChange(std::string& aValue)
{
    const Brx& val = iPropertyLastChange->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderUpnpOrgAVTransport2Cpp::SetPropertyDRMState(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyDRMState, buf);
}

void DvProviderUpnpOrgAVTransport2Cpp::GetPropertyDRMState(std::string& aValue)
{
    const Brx& val = iPropertyDRMState->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderUpnpOrgAVTransport2Cpp::DvProviderUpnpOrgAVTransport2Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "AVTransport", 2)
{
    
    TChar** allowedValues;
    TUint index;
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"OK";
    iPropertyDRMState = new PropertyString(new ParameterString("DRMState", allowedValues, 1));
    delete[] allowedValues;
    iService->AddProperty(iPropertyDRMState); // passes ownership
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionSetAVTransportURI()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("CurrentURI"));
    action->AddInputParameter(new ParameterString("CurrentURIMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoSetAVTransportURI);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionSetNextAVTransportURI()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetNextAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NextURI"));
    action->AddInputParameter(new ParameterString("NextURIMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoSetNextAVTransportURI);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionGetMediaInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetMediaInfo");
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoGetMediaInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionGetMediaInfo_Ext()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetMediaInfo_Ext");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"NO_MEDIA";
    allowedValues[index++] = (TChar*)"TRACK_AWARE";
    allowedValues[index++] = (TChar*)"TRACK_UNAWARE";
    action->AddOutputParameter(new ParameterString("CurrentType", allowedValues, 3));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterUint("NrTracks", 0, 0));
    action->AddOutputParameter(new ParameterString("MediaDuration"));
    action->AddOutputParameter(new ParameterString("CurrentURI"));
    action->AddOutputParameter(new ParameterString("CurrentURIMetaData"));
    action->AddOutputParameter(new ParameterString("NextURI"));
    action->AddOutputParameter(new ParameterString("NextURIMetaData"));
    action->AddOutputParameter(new ParameterString("PlayMedium"));
    action->AddOutputParameter(new ParameterString("RecordMedium"));
    action->AddOutputParameter(new ParameterString("WriteStatus"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoGetMediaInfo_Ext);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionGetTransportInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetTransportInfo");
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoGetTransportInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionGetPositionInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetPositionInfo");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("Track", 0, 0, 1));
    action->AddOutputParameter(new ParameterString("TrackDuration"));
    action->AddOutputParameter(new ParameterString("TrackMetaData"));
    action->AddOutputParameter(new ParameterString("TrackURI"));
    action->AddOutputParameter(new ParameterString("RelTime"));
    action->AddOutputParameter(new ParameterString("AbsTime"));
    action->AddOutputParameter(new ParameterInt("RelCount"));
    action->AddOutputParameter(new ParameterInt("AbsCount"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoGetPositionInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionGetDeviceCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetDeviceCapabilities");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("PlayMedia"));
    action->AddOutputParameter(new ParameterString("RecMedia"));
    action->AddOutputParameter(new ParameterString("RecQualityModes"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoGetDeviceCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionGetTransportSettings()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoGetTransportSettings);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionStop()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionPlay()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"1";
    action->AddInputParameter(new ParameterString("Speed", allowedValues, 1));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionPause()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Pause");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionRecord()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Record");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoRecord);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionSeek()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Seek");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"TRACK_NR";
    action->AddInputParameter(new ParameterString("Unit", allowedValues, 1));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterString("Target"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoSeek);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionNext()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Next");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoNext);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionPrevious()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Previous");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoPrevious);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionSetPlayMode()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoSetPlayMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionSetRecordQualityMode()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRecordQualityMode");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NewRecordQualityMode"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoSetRecordQualityMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionGetCurrentTransportActions()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetCurrentTransportActions");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("Actions"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoGetCurrentTransportActions);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionGetDRMState()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetDRMState");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterRelated("CurrentDRMState", *iPropertyDRMState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoGetDRMState);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionGetStateVariables()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("StateVariableList"));
    action->AddOutputParameter(new ParameterString("StateVariableValuePairs"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoGetStateVariables);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::EnableActionSetStateVariables()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("AVTransportUDN"));
    action->AddInputParameter(new ParameterString("ServiceType"));
    action->AddInputParameter(new ParameterString("ServiceId"));
    action->AddInputParameter(new ParameterString("StateVariableValuePairs"));
    action->AddOutputParameter(new ParameterString("StateVariableList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2Cpp::DoSetStateVariables);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2Cpp::DoSetAVTransportURI(IDviInvocation& aInvocation, uint32_t aVersion)
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

void DvProviderUpnpOrgAVTransport2Cpp::DoSetNextAVTransportURI(IDviInvocation& aInvocation, uint32_t aVersion)
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

void DvProviderUpnpOrgAVTransport2Cpp::DoGetMediaInfo(IDviInvocation& aInvocation, uint32_t aVersion)
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
    Brn buf_MediaDuration((const TByte*)respMediaDuration.c_str(), (TUint)respMediaDuration.length());
    respWriterMediaDuration.Write(buf_MediaDuration);
    aInvocation.InvocationWriteStringEnd("MediaDuration");
    InvocationResponseString respWriterCurrentURI(aInvocation, "CurrentURI");
    Brn buf_CurrentURI((const TByte*)respCurrentURI.c_str(), (TUint)respCurrentURI.length());
    respWriterCurrentURI.Write(buf_CurrentURI);
    aInvocation.InvocationWriteStringEnd("CurrentURI");
    InvocationResponseString respWriterCurrentURIMetaData(aInvocation, "CurrentURIMetaData");
    Brn buf_CurrentURIMetaData((const TByte*)respCurrentURIMetaData.c_str(), (TUint)respCurrentURIMetaData.length());
    respWriterCurrentURIMetaData.Write(buf_CurrentURIMetaData);
    aInvocation.InvocationWriteStringEnd("CurrentURIMetaData");
    InvocationResponseString respWriterNextURI(aInvocation, "NextURI");
    Brn buf_NextURI((const TByte*)respNextURI.c_str(), (TUint)respNextURI.length());
    respWriterNextURI.Write(buf_NextURI);
    aInvocation.InvocationWriteStringEnd("NextURI");
    InvocationResponseString respWriterNextURIMetaData(aInvocation, "NextURIMetaData");
    Brn buf_NextURIMetaData((const TByte*)respNextURIMetaData.c_str(), (TUint)respNextURIMetaData.length());
    respWriterNextURIMetaData.Write(buf_NextURIMetaData);
    aInvocation.InvocationWriteStringEnd("NextURIMetaData");
    InvocationResponseString respWriterPlayMedium(aInvocation, "PlayMedium");
    Brn buf_PlayMedium((const TByte*)respPlayMedium.c_str(), (TUint)respPlayMedium.length());
    respWriterPlayMedium.Write(buf_PlayMedium);
    aInvocation.InvocationWriteStringEnd("PlayMedium");
    InvocationResponseString respWriterRecordMedium(aInvocation, "RecordMedium");
    Brn buf_RecordMedium((const TByte*)respRecordMedium.c_str(), (TUint)respRecordMedium.length());
    respWriterRecordMedium.Write(buf_RecordMedium);
    aInvocation.InvocationWriteStringEnd("RecordMedium");
    InvocationResponseString respWriterWriteStatus(aInvocation, "WriteStatus");
    Brn buf_WriteStatus((const TByte*)respWriteStatus.c_str(), (TUint)respWriteStatus.length());
    respWriterWriteStatus.Write(buf_WriteStatus);
    aInvocation.InvocationWriteStringEnd("WriteStatus");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::DoGetMediaInfo_Ext(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respCurrentType;
    uint32_t respNrTracks;
    std::string respMediaDuration;
    std::string respCurrentURI;
    std::string respCurrentURIMetaData;
    std::string respNextURI;
    std::string respNextURIMetaData;
    std::string respPlayMedium;
    std::string respRecordMedium;
    std::string respWriteStatus;
    GetMediaInfo_Ext(aVersion, InstanceID, respCurrentType, respNrTracks, respMediaDuration, respCurrentURI, respCurrentURIMetaData, respNextURI, respNextURIMetaData, respPlayMedium, respRecordMedium, respWriteStatus);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterCurrentType(aInvocation, "CurrentType");
    Brn buf_CurrentType((const TByte*)respCurrentType.c_str(), (TUint)respCurrentType.length());
    respWriterCurrentType.Write(buf_CurrentType);
    aInvocation.InvocationWriteStringEnd("CurrentType");
    InvocationResponseUint respWriterNrTracks(aInvocation, "NrTracks");
    respWriterNrTracks.Write(respNrTracks);
    InvocationResponseString respWriterMediaDuration(aInvocation, "MediaDuration");
    Brn buf_MediaDuration((const TByte*)respMediaDuration.c_str(), (TUint)respMediaDuration.length());
    respWriterMediaDuration.Write(buf_MediaDuration);
    aInvocation.InvocationWriteStringEnd("MediaDuration");
    InvocationResponseString respWriterCurrentURI(aInvocation, "CurrentURI");
    Brn buf_CurrentURI((const TByte*)respCurrentURI.c_str(), (TUint)respCurrentURI.length());
    respWriterCurrentURI.Write(buf_CurrentURI);
    aInvocation.InvocationWriteStringEnd("CurrentURI");
    InvocationResponseString respWriterCurrentURIMetaData(aInvocation, "CurrentURIMetaData");
    Brn buf_CurrentURIMetaData((const TByte*)respCurrentURIMetaData.c_str(), (TUint)respCurrentURIMetaData.length());
    respWriterCurrentURIMetaData.Write(buf_CurrentURIMetaData);
    aInvocation.InvocationWriteStringEnd("CurrentURIMetaData");
    InvocationResponseString respWriterNextURI(aInvocation, "NextURI");
    Brn buf_NextURI((const TByte*)respNextURI.c_str(), (TUint)respNextURI.length());
    respWriterNextURI.Write(buf_NextURI);
    aInvocation.InvocationWriteStringEnd("NextURI");
    InvocationResponseString respWriterNextURIMetaData(aInvocation, "NextURIMetaData");
    Brn buf_NextURIMetaData((const TByte*)respNextURIMetaData.c_str(), (TUint)respNextURIMetaData.length());
    respWriterNextURIMetaData.Write(buf_NextURIMetaData);
    aInvocation.InvocationWriteStringEnd("NextURIMetaData");
    InvocationResponseString respWriterPlayMedium(aInvocation, "PlayMedium");
    Brn buf_PlayMedium((const TByte*)respPlayMedium.c_str(), (TUint)respPlayMedium.length());
    respWriterPlayMedium.Write(buf_PlayMedium);
    aInvocation.InvocationWriteStringEnd("PlayMedium");
    InvocationResponseString respWriterRecordMedium(aInvocation, "RecordMedium");
    Brn buf_RecordMedium((const TByte*)respRecordMedium.c_str(), (TUint)respRecordMedium.length());
    respWriterRecordMedium.Write(buf_RecordMedium);
    aInvocation.InvocationWriteStringEnd("RecordMedium");
    InvocationResponseString respWriterWriteStatus(aInvocation, "WriteStatus");
    Brn buf_WriteStatus((const TByte*)respWriteStatus.c_str(), (TUint)respWriteStatus.length());
    respWriterWriteStatus.Write(buf_WriteStatus);
    aInvocation.InvocationWriteStringEnd("WriteStatus");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::DoGetTransportInfo(IDviInvocation& aInvocation, uint32_t aVersion)
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
    Brn buf_CurrentTransportState((const TByte*)respCurrentTransportState.c_str(), (TUint)respCurrentTransportState.length());
    respWriterCurrentTransportState.Write(buf_CurrentTransportState);
    aInvocation.InvocationWriteStringEnd("CurrentTransportState");
    InvocationResponseString respWriterCurrentTransportStatus(aInvocation, "CurrentTransportStatus");
    Brn buf_CurrentTransportStatus((const TByte*)respCurrentTransportStatus.c_str(), (TUint)respCurrentTransportStatus.length());
    respWriterCurrentTransportStatus.Write(buf_CurrentTransportStatus);
    aInvocation.InvocationWriteStringEnd("CurrentTransportStatus");
    InvocationResponseString respWriterCurrentSpeed(aInvocation, "CurrentSpeed");
    Brn buf_CurrentSpeed((const TByte*)respCurrentSpeed.c_str(), (TUint)respCurrentSpeed.length());
    respWriterCurrentSpeed.Write(buf_CurrentSpeed);
    aInvocation.InvocationWriteStringEnd("CurrentSpeed");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::DoGetPositionInfo(IDviInvocation& aInvocation, uint32_t aVersion)
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
    Brn buf_TrackDuration((const TByte*)respTrackDuration.c_str(), (TUint)respTrackDuration.length());
    respWriterTrackDuration.Write(buf_TrackDuration);
    aInvocation.InvocationWriteStringEnd("TrackDuration");
    InvocationResponseString respWriterTrackMetaData(aInvocation, "TrackMetaData");
    Brn buf_TrackMetaData((const TByte*)respTrackMetaData.c_str(), (TUint)respTrackMetaData.length());
    respWriterTrackMetaData.Write(buf_TrackMetaData);
    aInvocation.InvocationWriteStringEnd("TrackMetaData");
    InvocationResponseString respWriterTrackURI(aInvocation, "TrackURI");
    Brn buf_TrackURI((const TByte*)respTrackURI.c_str(), (TUint)respTrackURI.length());
    respWriterTrackURI.Write(buf_TrackURI);
    aInvocation.InvocationWriteStringEnd("TrackURI");
    InvocationResponseString respWriterRelTime(aInvocation, "RelTime");
    Brn buf_RelTime((const TByte*)respRelTime.c_str(), (TUint)respRelTime.length());
    respWriterRelTime.Write(buf_RelTime);
    aInvocation.InvocationWriteStringEnd("RelTime");
    InvocationResponseString respWriterAbsTime(aInvocation, "AbsTime");
    Brn buf_AbsTime((const TByte*)respAbsTime.c_str(), (TUint)respAbsTime.length());
    respWriterAbsTime.Write(buf_AbsTime);
    aInvocation.InvocationWriteStringEnd("AbsTime");
    InvocationResponseInt respWriterRelCount(aInvocation, "RelCount");
    respWriterRelCount.Write(respRelCount);
    InvocationResponseInt respWriterAbsCount(aInvocation, "AbsCount");
    respWriterAbsCount.Write(respAbsCount);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::DoGetDeviceCapabilities(IDviInvocation& aInvocation, uint32_t aVersion)
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
    Brn buf_PlayMedia((const TByte*)respPlayMedia.c_str(), (TUint)respPlayMedia.length());
    respWriterPlayMedia.Write(buf_PlayMedia);
    aInvocation.InvocationWriteStringEnd("PlayMedia");
    InvocationResponseString respWriterRecMedia(aInvocation, "RecMedia");
    Brn buf_RecMedia((const TByte*)respRecMedia.c_str(), (TUint)respRecMedia.length());
    respWriterRecMedia.Write(buf_RecMedia);
    aInvocation.InvocationWriteStringEnd("RecMedia");
    InvocationResponseString respWriterRecQualityModes(aInvocation, "RecQualityModes");
    Brn buf_RecQualityModes((const TByte*)respRecQualityModes.c_str(), (TUint)respRecQualityModes.length());
    respWriterRecQualityModes.Write(buf_RecQualityModes);
    aInvocation.InvocationWriteStringEnd("RecQualityModes");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::DoGetTransportSettings(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respPlayMode;
    std::string respRecQualityMode;
    GetTransportSettings(aVersion, InstanceID, respPlayMode, respRecQualityMode);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterPlayMode(aInvocation, "PlayMode");
    Brn buf_PlayMode((const TByte*)respPlayMode.c_str(), (TUint)respPlayMode.length());
    respWriterPlayMode.Write(buf_PlayMode);
    aInvocation.InvocationWriteStringEnd("PlayMode");
    InvocationResponseString respWriterRecQualityMode(aInvocation, "RecQualityMode");
    Brn buf_RecQualityMode((const TByte*)respRecQualityMode.c_str(), (TUint)respRecQualityMode.length());
    respWriterRecQualityMode.Write(buf_RecQualityMode);
    aInvocation.InvocationWriteStringEnd("RecQualityMode");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::DoStop(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    Stop(aVersion, InstanceID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::DoPlay(IDviInvocation& aInvocation, uint32_t aVersion)
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

void DvProviderUpnpOrgAVTransport2Cpp::DoPause(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    Pause(aVersion, InstanceID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::DoRecord(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    Record(aVersion, InstanceID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::DoSeek(IDviInvocation& aInvocation, uint32_t aVersion)
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

void DvProviderUpnpOrgAVTransport2Cpp::DoNext(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    Next(aVersion, InstanceID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::DoPrevious(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    Previous(aVersion, InstanceID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::DoSetPlayMode(IDviInvocation& aInvocation, uint32_t aVersion)
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

void DvProviderUpnpOrgAVTransport2Cpp::DoSetRecordQualityMode(IDviInvocation& aInvocation, uint32_t aVersion)
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

void DvProviderUpnpOrgAVTransport2Cpp::DoGetCurrentTransportActions(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respActions;
    GetCurrentTransportActions(aVersion, InstanceID, respActions);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterActions(aInvocation, "Actions");
    Brn buf_Actions((const TByte*)respActions.c_str(), (TUint)respActions.length());
    respWriterActions.Write(buf_Actions);
    aInvocation.InvocationWriteStringEnd("Actions");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::DoGetDRMState(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respCurrentDRMState;
    GetDRMState(aVersion, InstanceID, respCurrentDRMState);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterCurrentDRMState(aInvocation, "CurrentDRMState");
    Brn buf_CurrentDRMState((const TByte*)respCurrentDRMState.c_str(), (TUint)respCurrentDRMState.length());
    respWriterCurrentDRMState.Write(buf_CurrentDRMState);
    aInvocation.InvocationWriteStringEnd("CurrentDRMState");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::DoGetStateVariables(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_StateVariableList;
    aInvocation.InvocationReadString("StateVariableList", buf_StateVariableList);
    std::string StateVariableList((const char*)buf_StateVariableList.Ptr(), buf_StateVariableList.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respStateVariableValuePairs;
    GetStateVariables(aVersion, InstanceID, StateVariableList, respStateVariableValuePairs);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterStateVariableValuePairs(aInvocation, "StateVariableValuePairs");
    Brn buf_StateVariableValuePairs((const TByte*)respStateVariableValuePairs.c_str(), (TUint)respStateVariableValuePairs.length());
    respWriterStateVariableValuePairs.Write(buf_StateVariableValuePairs);
    aInvocation.InvocationWriteStringEnd("StateVariableValuePairs");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::DoSetStateVariables(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_AVTransportUDN;
    aInvocation.InvocationReadString("AVTransportUDN", buf_AVTransportUDN);
    std::string AVTransportUDN((const char*)buf_AVTransportUDN.Ptr(), buf_AVTransportUDN.Bytes());
    Brhz buf_ServiceType;
    aInvocation.InvocationReadString("ServiceType", buf_ServiceType);
    std::string ServiceType((const char*)buf_ServiceType.Ptr(), buf_ServiceType.Bytes());
    Brhz buf_ServiceId;
    aInvocation.InvocationReadString("ServiceId", buf_ServiceId);
    std::string ServiceId((const char*)buf_ServiceId.Ptr(), buf_ServiceId.Bytes());
    Brhz buf_StateVariableValuePairs;
    aInvocation.InvocationReadString("StateVariableValuePairs", buf_StateVariableValuePairs);
    std::string StateVariableValuePairs((const char*)buf_StateVariableValuePairs.Ptr(), buf_StateVariableValuePairs.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respStateVariableList;
    SetStateVariables(aVersion, InstanceID, AVTransportUDN, ServiceType, ServiceId, StateVariableValuePairs, respStateVariableList);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterStateVariableList(aInvocation, "StateVariableList");
    Brn buf_StateVariableList((const TByte*)respStateVariableList.c_str(), (TUint)respStateVariableList.length());
    respWriterStateVariableList.Write(buf_StateVariableList);
    aInvocation.InvocationWriteStringEnd("StateVariableList");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgAVTransport2Cpp::SetAVTransportURI(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aCurrentURI*/, const std::string& /*aCurrentURIMetaData*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::SetNextAVTransportURI(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aNextURI*/, const std::string& /*aNextURIMetaData*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::GetMediaInfo(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aNrTracks*/, std::string& /*aMediaDuration*/, std::string& /*aCurrentURI*/, std::string& /*aCurrentURIMetaData*/, std::string& /*aNextURI*/, std::string& /*aNextURIMetaData*/, std::string& /*aPlayMedium*/, std::string& /*aRecordMedium*/, std::string& /*aWriteStatus*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::GetMediaInfo_Ext(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, std::string& /*aCurrentType*/, uint32_t& /*aNrTracks*/, std::string& /*aMediaDuration*/, std::string& /*aCurrentURI*/, std::string& /*aCurrentURIMetaData*/, std::string& /*aNextURI*/, std::string& /*aNextURIMetaData*/, std::string& /*aPlayMedium*/, std::string& /*aRecordMedium*/, std::string& /*aWriteStatus*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::GetTransportInfo(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, std::string& /*aCurrentTransportState*/, std::string& /*aCurrentTransportStatus*/, std::string& /*aCurrentSpeed*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::GetPositionInfo(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aTrack*/, std::string& /*aTrackDuration*/, std::string& /*aTrackMetaData*/, std::string& /*aTrackURI*/, std::string& /*aRelTime*/, std::string& /*aAbsTime*/, int32_t& /*aRelCount*/, int32_t& /*aAbsCount*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::GetDeviceCapabilities(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, std::string& /*aPlayMedia*/, std::string& /*aRecMedia*/, std::string& /*aRecQualityModes*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::GetTransportSettings(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, std::string& /*aPlayMode*/, std::string& /*aRecQualityMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::Stop(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::Play(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aSpeed*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::Pause(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::Record(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::Seek(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aUnit*/, const std::string& /*aTarget*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::Next(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::Previous(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::SetPlayMode(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aNewPlayMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::SetRecordQualityMode(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aNewRecordQualityMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::GetCurrentTransportActions(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, std::string& /*aActions*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::GetDRMState(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, std::string& /*aCurrentDRMState*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::GetStateVariables(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aStateVariableList*/, std::string& /*aStateVariableValuePairs*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2Cpp::SetStateVariables(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aAVTransportUDN*/, const std::string& /*aServiceType*/, const std::string& /*aServiceId*/, const std::string& /*aStateVariableValuePairs*/, std::string& /*aStateVariableList*/)
{
    ASSERTS();
}

