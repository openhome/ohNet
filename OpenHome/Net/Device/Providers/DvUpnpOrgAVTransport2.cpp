#include "DvUpnpOrgAVTransport2.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderUpnpOrgAVTransport2::SetPropertyLastChange(const Brx& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgAVTransport2::GetPropertyLastChange(Brhz& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    aValue.Set(iPropertyLastChange->Value());
}

TBool DvProviderUpnpOrgAVTransport2::SetPropertyDRMState(const Brx& aValue)
{
    ASSERT(iPropertyDRMState != NULL);
    return SetPropertyString(*iPropertyDRMState, aValue);
}

void DvProviderUpnpOrgAVTransport2::GetPropertyDRMState(Brhz& aValue)
{
    ASSERT(iPropertyDRMState != NULL);
    aValue.Set(iPropertyDRMState->Value());
}

DvProviderUpnpOrgAVTransport2::DvProviderUpnpOrgAVTransport2(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "AVTransport", 2)
{
    Construct();
}

DvProviderUpnpOrgAVTransport2::DvProviderUpnpOrgAVTransport2(DviDevice& aDevice)
    : DvProvider(aDevice, "upnp.org", "AVTransport", 2)
{
    Construct();
}

void DvProviderUpnpOrgAVTransport2::Construct()
{
    iPropertyLastChange = NULL;
    iPropertyDRMState = NULL;
}

void DvProviderUpnpOrgAVTransport2::EnablePropertyLastChange()
{
    iPropertyLastChange = new PropertyString(iDvStack.Env(), new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgAVTransport2::EnablePropertyDRMState()
{
    TChar** allowedValues;
    TUint index = 0;
    allowedValues = new TChar*[8];
    allowedValues[index++] = (TChar*)"OK";
    allowedValues[index++] = (TChar*)"UNKNOWN";
    allowedValues[index++] = (TChar*)"PROCESSING_CONTENT_KEY";
    allowedValues[index++] = (TChar*)"CONTENT_KEY_FAILURE";
    allowedValues[index++] = (TChar*)"ATTEMPTING_AUTHENTICATION";
    allowedValues[index++] = (TChar*)"FAILED_AUTHENTICATION";
    allowedValues[index++] = (TChar*)"NOT_AUTHENTICATED";
    allowedValues[index++] = (TChar*)"DEVICE_REVOCATION";
    iPropertyDRMState = new PropertyString(iDvStack.Env(), new ParameterString("DRMState", allowedValues, 8));
    delete[] allowedValues;
    iService->AddProperty(iPropertyDRMState); // passes ownership
}

void DvProviderUpnpOrgAVTransport2::EnableActionSetAVTransportURI()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("CurrentURI"));
    action->AddInputParameter(new ParameterString("CurrentURIMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoSetAVTransportURI);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionSetNextAVTransportURI()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetNextAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NextURI"));
    action->AddInputParameter(new ParameterString("NextURIMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoSetNextAVTransportURI);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionGetMediaInfo()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoGetMediaInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionGetMediaInfo_Ext()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoGetMediaInfo_Ext);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionGetTransportInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetTransportInfo");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("CurrentTransportState"));
    action->AddOutputParameter(new ParameterString("CurrentTransportStatus"));
    action->AddOutputParameter(new ParameterString("CurrentSpeed"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoGetTransportInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionGetPositionInfo()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoGetPositionInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionGetDeviceCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetDeviceCapabilities");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("PlayMedia"));
    action->AddOutputParameter(new ParameterString("RecMedia"));
    action->AddOutputParameter(new ParameterString("RecQualityModes"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoGetDeviceCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionGetTransportSettings()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetTransportSettings");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[7];
    allowedValues[index++] = (TChar*)"NORMAL";
    allowedValues[index++] = (TChar*)"SHUFFLE";
    allowedValues[index++] = (TChar*)"REPEAT_ONE";
    allowedValues[index++] = (TChar*)"REPEAT_ALL";
    allowedValues[index++] = (TChar*)"RANDOM";
    allowedValues[index++] = (TChar*)"DIRECT_1";
    allowedValues[index++] = (TChar*)"INTRO";
    action->AddOutputParameter(new ParameterString("PlayMode", allowedValues, 7));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterString("RecQualityMode"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoGetTransportSettings);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionStop()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionPlay()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Speed"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionPause()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Pause");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionRecord()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Record");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoRecord);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionSeek()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Seek");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[8];
    allowedValues[index++] = (TChar*)"ABS_TIME";
    allowedValues[index++] = (TChar*)"REL_TIME";
    allowedValues[index++] = (TChar*)"ABS_COUNT";
    allowedValues[index++] = (TChar*)"REL_COUNT";
    allowedValues[index++] = (TChar*)"TRACK_NR";
    allowedValues[index++] = (TChar*)"CHANNEL_FREQ";
    allowedValues[index++] = (TChar*)"TAPE-INDEX";
    allowedValues[index++] = (TChar*)"FRAME";
    action->AddInputParameter(new ParameterString("Unit", allowedValues, 8));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterString("Target"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoSeek);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionNext()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Next");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoNext);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionPrevious()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Previous");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoPrevious);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionSetPlayMode()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetPlayMode");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[7];
    allowedValues[index++] = (TChar*)"NORMAL";
    allowedValues[index++] = (TChar*)"SHUFFLE";
    allowedValues[index++] = (TChar*)"REPEAT_ONE";
    allowedValues[index++] = (TChar*)"REPEAT_ALL";
    allowedValues[index++] = (TChar*)"RANDOM";
    allowedValues[index++] = (TChar*)"DIRECT_1";
    allowedValues[index++] = (TChar*)"INTRO";
    action->AddInputParameter(new ParameterString("NewPlayMode", allowedValues, 7));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoSetPlayMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionSetRecordQualityMode()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRecordQualityMode");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NewRecordQualityMode"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoSetRecordQualityMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionGetCurrentTransportActions()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetCurrentTransportActions");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("Actions"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoGetCurrentTransportActions);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionGetDRMState()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetDRMState");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterRelated("CurrentDRMState", *iPropertyDRMState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoGetDRMState);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionGetStateVariables()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("StateVariableList"));
    action->AddOutputParameter(new ParameterString("StateVariableValuePairs"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoGetStateVariables);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::EnableActionSetStateVariables()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("AVTransportUDN"));
    action->AddInputParameter(new ParameterString("ServiceType"));
    action->AddInputParameter(new ParameterString("ServiceId"));
    action->AddInputParameter(new ParameterString("StateVariableValuePairs"));
    action->AddOutputParameter(new ParameterString("StateVariableList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2::DoSetStateVariables);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2::DoSetAVTransportURI(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz CurrentURI;
    aInvocation.InvocationReadString("CurrentURI", CurrentURI);
    Brhz CurrentURIMetaData;
    aInvocation.InvocationReadString("CurrentURIMetaData", CurrentURIMetaData);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetAVTransportURI(invocation, InstanceID, CurrentURI, CurrentURIMetaData);
}

void DvProviderUpnpOrgAVTransport2::DoSetNextAVTransportURI(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz NextURI;
    aInvocation.InvocationReadString("NextURI", NextURI);
    Brhz NextURIMetaData;
    aInvocation.InvocationReadString("NextURIMetaData", NextURIMetaData);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetNextAVTransportURI(invocation, InstanceID, NextURI, NextURIMetaData);
}

void DvProviderUpnpOrgAVTransport2::DoGetMediaInfo(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respNrTracks(aInvocation, "NrTracks");
    DviInvocationResponseString respMediaDuration(aInvocation, "MediaDuration");
    DviInvocationResponseString respCurrentURI(aInvocation, "CurrentURI");
    DviInvocationResponseString respCurrentURIMetaData(aInvocation, "CurrentURIMetaData");
    DviInvocationResponseString respNextURI(aInvocation, "NextURI");
    DviInvocationResponseString respNextURIMetaData(aInvocation, "NextURIMetaData");
    DviInvocationResponseString respPlayMedium(aInvocation, "PlayMedium");
    DviInvocationResponseString respRecordMedium(aInvocation, "RecordMedium");
    DviInvocationResponseString respWriteStatus(aInvocation, "WriteStatus");
    GetMediaInfo(invocation, InstanceID, respNrTracks, respMediaDuration, respCurrentURI, respCurrentURIMetaData, respNextURI, respNextURIMetaData, respPlayMedium, respRecordMedium, respWriteStatus);
}

void DvProviderUpnpOrgAVTransport2::DoGetMediaInfo_Ext(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respCurrentType(aInvocation, "CurrentType");
    DviInvocationResponseUint respNrTracks(aInvocation, "NrTracks");
    DviInvocationResponseString respMediaDuration(aInvocation, "MediaDuration");
    DviInvocationResponseString respCurrentURI(aInvocation, "CurrentURI");
    DviInvocationResponseString respCurrentURIMetaData(aInvocation, "CurrentURIMetaData");
    DviInvocationResponseString respNextURI(aInvocation, "NextURI");
    DviInvocationResponseString respNextURIMetaData(aInvocation, "NextURIMetaData");
    DviInvocationResponseString respPlayMedium(aInvocation, "PlayMedium");
    DviInvocationResponseString respRecordMedium(aInvocation, "RecordMedium");
    DviInvocationResponseString respWriteStatus(aInvocation, "WriteStatus");
    GetMediaInfo_Ext(invocation, InstanceID, respCurrentType, respNrTracks, respMediaDuration, respCurrentURI, respCurrentURIMetaData, respNextURI, respNextURIMetaData, respPlayMedium, respRecordMedium, respWriteStatus);
}

void DvProviderUpnpOrgAVTransport2::DoGetTransportInfo(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respCurrentTransportState(aInvocation, "CurrentTransportState");
    DviInvocationResponseString respCurrentTransportStatus(aInvocation, "CurrentTransportStatus");
    DviInvocationResponseString respCurrentSpeed(aInvocation, "CurrentSpeed");
    GetTransportInfo(invocation, InstanceID, respCurrentTransportState, respCurrentTransportStatus, respCurrentSpeed);
}

void DvProviderUpnpOrgAVTransport2::DoGetPositionInfo(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respTrack(aInvocation, "Track");
    DviInvocationResponseString respTrackDuration(aInvocation, "TrackDuration");
    DviInvocationResponseString respTrackMetaData(aInvocation, "TrackMetaData");
    DviInvocationResponseString respTrackURI(aInvocation, "TrackURI");
    DviInvocationResponseString respRelTime(aInvocation, "RelTime");
    DviInvocationResponseString respAbsTime(aInvocation, "AbsTime");
    DviInvocationResponseInt respRelCount(aInvocation, "RelCount");
    DviInvocationResponseInt respAbsCount(aInvocation, "AbsCount");
    GetPositionInfo(invocation, InstanceID, respTrack, respTrackDuration, respTrackMetaData, respTrackURI, respRelTime, respAbsTime, respRelCount, respAbsCount);
}

void DvProviderUpnpOrgAVTransport2::DoGetDeviceCapabilities(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respPlayMedia(aInvocation, "PlayMedia");
    DviInvocationResponseString respRecMedia(aInvocation, "RecMedia");
    DviInvocationResponseString respRecQualityModes(aInvocation, "RecQualityModes");
    GetDeviceCapabilities(invocation, InstanceID, respPlayMedia, respRecMedia, respRecQualityModes);
}

void DvProviderUpnpOrgAVTransport2::DoGetTransportSettings(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respPlayMode(aInvocation, "PlayMode");
    DviInvocationResponseString respRecQualityMode(aInvocation, "RecQualityMode");
    GetTransportSettings(invocation, InstanceID, respPlayMode, respRecQualityMode);
}

void DvProviderUpnpOrgAVTransport2::DoStop(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Stop(invocation, InstanceID);
}

void DvProviderUpnpOrgAVTransport2::DoPlay(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Speed;
    aInvocation.InvocationReadString("Speed", Speed);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Play(invocation, InstanceID, Speed);
}

void DvProviderUpnpOrgAVTransport2::DoPause(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Pause(invocation, InstanceID);
}

void DvProviderUpnpOrgAVTransport2::DoRecord(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Record(invocation, InstanceID);
}

void DvProviderUpnpOrgAVTransport2::DoSeek(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Unit;
    aInvocation.InvocationReadString("Unit", Unit);
    Brhz Target;
    aInvocation.InvocationReadString("Target", Target);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Seek(invocation, InstanceID, Unit, Target);
}

void DvProviderUpnpOrgAVTransport2::DoNext(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Next(invocation, InstanceID);
}

void DvProviderUpnpOrgAVTransport2::DoPrevious(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Previous(invocation, InstanceID);
}

void DvProviderUpnpOrgAVTransport2::DoSetPlayMode(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz NewPlayMode;
    aInvocation.InvocationReadString("NewPlayMode", NewPlayMode);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetPlayMode(invocation, InstanceID, NewPlayMode);
}

void DvProviderUpnpOrgAVTransport2::DoSetRecordQualityMode(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz NewRecordQualityMode;
    aInvocation.InvocationReadString("NewRecordQualityMode", NewRecordQualityMode);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetRecordQualityMode(invocation, InstanceID, NewRecordQualityMode);
}

void DvProviderUpnpOrgAVTransport2::DoGetCurrentTransportActions(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respActions(aInvocation, "Actions");
    GetCurrentTransportActions(invocation, InstanceID, respActions);
}

void DvProviderUpnpOrgAVTransport2::DoGetDRMState(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respCurrentDRMState(aInvocation, "CurrentDRMState");
    GetDRMState(invocation, InstanceID, respCurrentDRMState);
}

void DvProviderUpnpOrgAVTransport2::DoGetStateVariables(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz StateVariableList;
    aInvocation.InvocationReadString("StateVariableList", StateVariableList);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respStateVariableValuePairs(aInvocation, "StateVariableValuePairs");
    GetStateVariables(invocation, InstanceID, StateVariableList, respStateVariableValuePairs);
}

void DvProviderUpnpOrgAVTransport2::DoSetStateVariables(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz AVTransportUDN;
    aInvocation.InvocationReadString("AVTransportUDN", AVTransportUDN);
    Brhz ServiceType;
    aInvocation.InvocationReadString("ServiceType", ServiceType);
    Brhz ServiceId;
    aInvocation.InvocationReadString("ServiceId", ServiceId);
    Brhz StateVariableValuePairs;
    aInvocation.InvocationReadString("StateVariableValuePairs", StateVariableValuePairs);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respStateVariableList(aInvocation, "StateVariableList");
    SetStateVariables(invocation, InstanceID, AVTransportUDN, ServiceType, ServiceId, StateVariableValuePairs, respStateVariableList);
}

void DvProviderUpnpOrgAVTransport2::SetAVTransportURI(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aCurrentURI*/, const Brx& /*aCurrentURIMetaData*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::SetNextAVTransportURI(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aNextURI*/, const Brx& /*aNextURIMetaData*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::GetMediaInfo(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aNrTracks*/, IDvInvocationResponseString& /*aMediaDuration*/, IDvInvocationResponseString& /*aCurrentURI*/, IDvInvocationResponseString& /*aCurrentURIMetaData*/, IDvInvocationResponseString& /*aNextURI*/, IDvInvocationResponseString& /*aNextURIMetaData*/, IDvInvocationResponseString& /*aPlayMedium*/, IDvInvocationResponseString& /*aRecordMedium*/, IDvInvocationResponseString& /*aWriteStatus*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::GetMediaInfo_Ext(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseString& /*aCurrentType*/, IDvInvocationResponseUint& /*aNrTracks*/, IDvInvocationResponseString& /*aMediaDuration*/, IDvInvocationResponseString& /*aCurrentURI*/, IDvInvocationResponseString& /*aCurrentURIMetaData*/, IDvInvocationResponseString& /*aNextURI*/, IDvInvocationResponseString& /*aNextURIMetaData*/, IDvInvocationResponseString& /*aPlayMedium*/, IDvInvocationResponseString& /*aRecordMedium*/, IDvInvocationResponseString& /*aWriteStatus*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::GetTransportInfo(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseString& /*aCurrentTransportState*/, IDvInvocationResponseString& /*aCurrentTransportStatus*/, IDvInvocationResponseString& /*aCurrentSpeed*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::GetPositionInfo(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aTrack*/, IDvInvocationResponseString& /*aTrackDuration*/, IDvInvocationResponseString& /*aTrackMetaData*/, IDvInvocationResponseString& /*aTrackURI*/, IDvInvocationResponseString& /*aRelTime*/, IDvInvocationResponseString& /*aAbsTime*/, IDvInvocationResponseInt& /*aRelCount*/, IDvInvocationResponseInt& /*aAbsCount*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::GetDeviceCapabilities(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseString& /*aPlayMedia*/, IDvInvocationResponseString& /*aRecMedia*/, IDvInvocationResponseString& /*aRecQualityModes*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::GetTransportSettings(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseString& /*aPlayMode*/, IDvInvocationResponseString& /*aRecQualityMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::Stop(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::Play(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aSpeed*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::Pause(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::Record(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::Seek(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aUnit*/, const Brx& /*aTarget*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::Next(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::Previous(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::SetPlayMode(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aNewPlayMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::SetRecordQualityMode(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aNewRecordQualityMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::GetCurrentTransportActions(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseString& /*aActions*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::GetDRMState(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseString& /*aCurrentDRMState*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::GetStateVariables(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aStateVariableList*/, IDvInvocationResponseString& /*aStateVariableValuePairs*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport2::SetStateVariables(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aAVTransportUDN*/, const Brx& /*aServiceType*/, const Brx& /*aServiceId*/, const Brx& /*aStateVariableValuePairs*/, IDvInvocationResponseString& /*aStateVariableList*/)
{
    ASSERTS();
}

