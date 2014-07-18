#include "DvUpnpOrgAVTransport1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderUpnpOrgAVTransport1::SetPropertyLastChange(const Brx& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgAVTransport1::GetPropertyLastChange(Brhz& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    aValue.Set(iPropertyLastChange->Value());
}

DvProviderUpnpOrgAVTransport1::DvProviderUpnpOrgAVTransport1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "AVTransport", 1)
{
    Construct();
}

DvProviderUpnpOrgAVTransport1::DvProviderUpnpOrgAVTransport1(DviDevice& aDevice)
    : DvProvider(aDevice, "upnp.org", "AVTransport", 1)
{
    Construct();
}

void DvProviderUpnpOrgAVTransport1::Construct()
{
    iPropertyLastChange = NULL;
}

void DvProviderUpnpOrgAVTransport1::EnablePropertyLastChange()
{
    iPropertyLastChange = new PropertyString(iDvStack.Env(), new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgAVTransport1::EnableActionSetAVTransportURI()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("CurrentURI"));
    action->AddInputParameter(new ParameterString("CurrentURIMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoSetAVTransportURI);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionSetNextAVTransportURI()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetNextAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NextURI"));
    action->AddInputParameter(new ParameterString("NextURIMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoSetNextAVTransportURI);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionGetMediaInfo()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoGetMediaInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionGetTransportInfo()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoGetTransportInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionGetPositionInfo()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoGetPositionInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionGetDeviceCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetDeviceCapabilities");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("PlayMedia"));
    action->AddOutputParameter(new ParameterString("RecMedia"));
    action->AddOutputParameter(new ParameterString("RecQualityModes"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoGetDeviceCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionGetTransportSettings()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoGetTransportSettings);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionStop()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionPlay()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Speed"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionPause()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Pause");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionRecord()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Record");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoRecord);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionSeek()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoSeek);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionNext()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Next");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoNext);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionPrevious()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Previous");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoPrevious);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionSetPlayMode()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoSetPlayMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionSetRecordQualityMode()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRecordQualityMode");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NewRecordQualityMode"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoSetRecordQualityMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionGetCurrentTransportActions()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetCurrentTransportActions");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("Actions"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoGetCurrentTransportActions);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::DoSetAVTransportURI(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1::DoSetNextAVTransportURI(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1::DoGetMediaInfo(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1::DoGetTransportInfo(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1::DoGetPositionInfo(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1::DoGetDeviceCapabilities(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1::DoGetTransportSettings(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respPlayMode(aInvocation, "PlayMode");
    DviInvocationResponseString respRecQualityMode(aInvocation, "RecQualityMode");
    GetTransportSettings(invocation, InstanceID, respPlayMode, respRecQualityMode);
}

void DvProviderUpnpOrgAVTransport1::DoStop(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Stop(invocation, InstanceID);
}

void DvProviderUpnpOrgAVTransport1::DoPlay(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Speed;
    aInvocation.InvocationReadString("Speed", Speed);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Play(invocation, InstanceID, Speed);
}

void DvProviderUpnpOrgAVTransport1::DoPause(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Pause(invocation, InstanceID);
}

void DvProviderUpnpOrgAVTransport1::DoRecord(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Record(invocation, InstanceID);
}

void DvProviderUpnpOrgAVTransport1::DoSeek(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1::DoNext(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Next(invocation, InstanceID);
}

void DvProviderUpnpOrgAVTransport1::DoPrevious(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Previous(invocation, InstanceID);
}

void DvProviderUpnpOrgAVTransport1::DoSetPlayMode(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz NewPlayMode;
    aInvocation.InvocationReadString("NewPlayMode", NewPlayMode);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetPlayMode(invocation, InstanceID, NewPlayMode);
}

void DvProviderUpnpOrgAVTransport1::DoSetRecordQualityMode(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz NewRecordQualityMode;
    aInvocation.InvocationReadString("NewRecordQualityMode", NewRecordQualityMode);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetRecordQualityMode(invocation, InstanceID, NewRecordQualityMode);
}

void DvProviderUpnpOrgAVTransport1::DoGetCurrentTransportActions(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respActions(aInvocation, "Actions");
    GetCurrentTransportActions(invocation, InstanceID, respActions);
}

void DvProviderUpnpOrgAVTransport1::SetAVTransportURI(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aCurrentURI*/, const Brx& /*aCurrentURIMetaData*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::SetNextAVTransportURI(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aNextURI*/, const Brx& /*aNextURIMetaData*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::GetMediaInfo(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aNrTracks*/, IDvInvocationResponseString& /*aMediaDuration*/, IDvInvocationResponseString& /*aCurrentURI*/, IDvInvocationResponseString& /*aCurrentURIMetaData*/, IDvInvocationResponseString& /*aNextURI*/, IDvInvocationResponseString& /*aNextURIMetaData*/, IDvInvocationResponseString& /*aPlayMedium*/, IDvInvocationResponseString& /*aRecordMedium*/, IDvInvocationResponseString& /*aWriteStatus*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::GetTransportInfo(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseString& /*aCurrentTransportState*/, IDvInvocationResponseString& /*aCurrentTransportStatus*/, IDvInvocationResponseString& /*aCurrentSpeed*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::GetPositionInfo(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aTrack*/, IDvInvocationResponseString& /*aTrackDuration*/, IDvInvocationResponseString& /*aTrackMetaData*/, IDvInvocationResponseString& /*aTrackURI*/, IDvInvocationResponseString& /*aRelTime*/, IDvInvocationResponseString& /*aAbsTime*/, IDvInvocationResponseInt& /*aRelCount*/, IDvInvocationResponseInt& /*aAbsCount*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::GetDeviceCapabilities(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseString& /*aPlayMedia*/, IDvInvocationResponseString& /*aRecMedia*/, IDvInvocationResponseString& /*aRecQualityModes*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::GetTransportSettings(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseString& /*aPlayMode*/, IDvInvocationResponseString& /*aRecQualityMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::Stop(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::Play(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aSpeed*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::Pause(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::Record(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::Seek(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aUnit*/, const Brx& /*aTarget*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::Next(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::Previous(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::SetPlayMode(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aNewPlayMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::SetRecordQualityMode(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aNewRecordQualityMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::GetCurrentTransportActions(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseString& /*aActions*/)
{
    ASSERTS();
}

