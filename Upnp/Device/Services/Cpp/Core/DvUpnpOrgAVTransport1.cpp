#include <Core/DvUpnpOrgAVTransport1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderUpnpOrgAVTransport1::SetPropertyLastChange(const Brx& aValue)
{
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgAVTransport1::GetPropertyLastChange(Brhz& aValue)
{
    aValue.Set(iPropertyLastChange->Value());
}

DvProviderUpnpOrgAVTransport1::DvProviderUpnpOrgAVTransport1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "AVTransport", 1)
{
    
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgAVTransport1::EnableActionSetAVTransportURI()
{
    Zapp::Action* action = new Zapp::Action("SetAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("CurrentURI"));
    action->AddInputParameter(new ParameterString("CurrentURIMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoSetAVTransportURI);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionSetNextAVTransportURI()
{
    Zapp::Action* action = new Zapp::Action("SetNextAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NextURI"));
    action->AddInputParameter(new ParameterString("NextURIMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoSetNextAVTransportURI);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionGetMediaInfo()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoGetMediaInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionGetTransportInfo()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoGetTransportInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionGetPositionInfo()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoGetPositionInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionGetDeviceCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetDeviceCapabilities");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("PlayMedia"));
    action->AddOutputParameter(new ParameterString("RecMedia"));
    action->AddOutputParameter(new ParameterString("RecQualityModes"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoGetDeviceCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionGetTransportSettings()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoGetTransportSettings);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionStop()
{
    Zapp::Action* action = new Zapp::Action("Stop");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionPlay()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionPause()
{
    Zapp::Action* action = new Zapp::Action("Pause");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionRecord()
{
    Zapp::Action* action = new Zapp::Action("Record");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoRecord);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionSeek()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoSeek);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionNext()
{
    Zapp::Action* action = new Zapp::Action("Next");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoNext);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionPrevious()
{
    Zapp::Action* action = new Zapp::Action("Previous");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoPrevious);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionSetPlayMode()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoSetPlayMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionSetRecordQualityMode()
{
    Zapp::Action* action = new Zapp::Action("SetRecordQualityMode");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NewRecordQualityMode"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoSetRecordQualityMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::EnableActionGetCurrentTransportActions()
{
    Zapp::Action* action = new Zapp::Action("GetCurrentTransportActions");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("Actions"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1::DoGetCurrentTransportActions);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1::DoSetAVTransportURI(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz CurrentURI;
    aInvocation.InvocationReadString("CurrentURI", CurrentURI);
    Brhz CurrentURIMetaData;
    aInvocation.InvocationReadString("CurrentURIMetaData", CurrentURIMetaData);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetAVTransportURI(resp, aVersion, InstanceID, CurrentURI, CurrentURIMetaData);
}

void DvProviderUpnpOrgAVTransport1::DoSetNextAVTransportURI(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz NextURI;
    aInvocation.InvocationReadString("NextURI", NextURI);
    Brhz NextURIMetaData;
    aInvocation.InvocationReadString("NextURIMetaData", NextURIMetaData);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetNextAVTransportURI(resp, aVersion, InstanceID, NextURI, NextURIMetaData);
}

void DvProviderUpnpOrgAVTransport1::DoGetMediaInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respNrTracks(aInvocation, "NrTracks");
    InvocationResponseString respMediaDuration(aInvocation, "MediaDuration");
    InvocationResponseString respCurrentURI(aInvocation, "CurrentURI");
    InvocationResponseString respCurrentURIMetaData(aInvocation, "CurrentURIMetaData");
    InvocationResponseString respNextURI(aInvocation, "NextURI");
    InvocationResponseString respNextURIMetaData(aInvocation, "NextURIMetaData");
    InvocationResponseString respPlayMedium(aInvocation, "PlayMedium");
    InvocationResponseString respRecordMedium(aInvocation, "RecordMedium");
    InvocationResponseString respWriteStatus(aInvocation, "WriteStatus");
    GetMediaInfo(resp, aVersion, InstanceID, respNrTracks, respMediaDuration, respCurrentURI, respCurrentURIMetaData, respNextURI, respNextURIMetaData, respPlayMedium, respRecordMedium, respWriteStatus);
}

void DvProviderUpnpOrgAVTransport1::DoGetTransportInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respCurrentTransportState(aInvocation, "CurrentTransportState");
    InvocationResponseString respCurrentTransportStatus(aInvocation, "CurrentTransportStatus");
    InvocationResponseString respCurrentSpeed(aInvocation, "CurrentSpeed");
    GetTransportInfo(resp, aVersion, InstanceID, respCurrentTransportState, respCurrentTransportStatus, respCurrentSpeed);
}

void DvProviderUpnpOrgAVTransport1::DoGetPositionInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respTrack(aInvocation, "Track");
    InvocationResponseString respTrackDuration(aInvocation, "TrackDuration");
    InvocationResponseString respTrackMetaData(aInvocation, "TrackMetaData");
    InvocationResponseString respTrackURI(aInvocation, "TrackURI");
    InvocationResponseString respRelTime(aInvocation, "RelTime");
    InvocationResponseString respAbsTime(aInvocation, "AbsTime");
    InvocationResponseInt respRelCount(aInvocation, "RelCount");
    InvocationResponseInt respAbsCount(aInvocation, "AbsCount");
    GetPositionInfo(resp, aVersion, InstanceID, respTrack, respTrackDuration, respTrackMetaData, respTrackURI, respRelTime, respAbsTime, respRelCount, respAbsCount);
}

void DvProviderUpnpOrgAVTransport1::DoGetDeviceCapabilities(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respPlayMedia(aInvocation, "PlayMedia");
    InvocationResponseString respRecMedia(aInvocation, "RecMedia");
    InvocationResponseString respRecQualityModes(aInvocation, "RecQualityModes");
    GetDeviceCapabilities(resp, aVersion, InstanceID, respPlayMedia, respRecMedia, respRecQualityModes);
}

void DvProviderUpnpOrgAVTransport1::DoGetTransportSettings(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respPlayMode(aInvocation, "PlayMode");
    InvocationResponseString respRecQualityMode(aInvocation, "RecQualityMode");
    GetTransportSettings(resp, aVersion, InstanceID, respPlayMode, respRecQualityMode);
}

void DvProviderUpnpOrgAVTransport1::DoStop(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Stop(resp, aVersion, InstanceID);
}

void DvProviderUpnpOrgAVTransport1::DoPlay(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Speed;
    aInvocation.InvocationReadString("Speed", Speed);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Play(resp, aVersion, InstanceID, Speed);
}

void DvProviderUpnpOrgAVTransport1::DoPause(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Pause(resp, aVersion, InstanceID);
}

void DvProviderUpnpOrgAVTransport1::DoRecord(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Record(resp, aVersion, InstanceID);
}

void DvProviderUpnpOrgAVTransport1::DoSeek(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Unit;
    aInvocation.InvocationReadString("Unit", Unit);
    Brhz Target;
    aInvocation.InvocationReadString("Target", Target);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Seek(resp, aVersion, InstanceID, Unit, Target);
}

void DvProviderUpnpOrgAVTransport1::DoNext(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Next(resp, aVersion, InstanceID);
}

void DvProviderUpnpOrgAVTransport1::DoPrevious(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Previous(resp, aVersion, InstanceID);
}

void DvProviderUpnpOrgAVTransport1::DoSetPlayMode(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz NewPlayMode;
    aInvocation.InvocationReadString("NewPlayMode", NewPlayMode);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetPlayMode(resp, aVersion, InstanceID, NewPlayMode);
}

void DvProviderUpnpOrgAVTransport1::DoSetRecordQualityMode(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz NewRecordQualityMode;
    aInvocation.InvocationReadString("NewRecordQualityMode", NewRecordQualityMode);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRecordQualityMode(resp, aVersion, InstanceID, NewRecordQualityMode);
}

void DvProviderUpnpOrgAVTransport1::DoGetCurrentTransportActions(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respActions(aInvocation, "Actions");
    GetCurrentTransportActions(resp, aVersion, InstanceID, respActions);
}

void DvProviderUpnpOrgAVTransport1::SetAVTransportURI(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aCurrentURI*/, const Brx& /*aCurrentURIMetaData*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::SetNextAVTransportURI(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aNextURI*/, const Brx& /*aNextURIMetaData*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::GetMediaInfo(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aNrTracks*/, IInvocationResponseString& /*aMediaDuration*/, IInvocationResponseString& /*aCurrentURI*/, IInvocationResponseString& /*aCurrentURIMetaData*/, IInvocationResponseString& /*aNextURI*/, IInvocationResponseString& /*aNextURIMetaData*/, IInvocationResponseString& /*aPlayMedium*/, IInvocationResponseString& /*aRecordMedium*/, IInvocationResponseString& /*aWriteStatus*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::GetTransportInfo(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseString& /*aCurrentTransportState*/, IInvocationResponseString& /*aCurrentTransportStatus*/, IInvocationResponseString& /*aCurrentSpeed*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::GetPositionInfo(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aTrack*/, IInvocationResponseString& /*aTrackDuration*/, IInvocationResponseString& /*aTrackMetaData*/, IInvocationResponseString& /*aTrackURI*/, IInvocationResponseString& /*aRelTime*/, IInvocationResponseString& /*aAbsTime*/, IInvocationResponseInt& /*aRelCount*/, IInvocationResponseInt& /*aAbsCount*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::GetDeviceCapabilities(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseString& /*aPlayMedia*/, IInvocationResponseString& /*aRecMedia*/, IInvocationResponseString& /*aRecQualityModes*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::GetTransportSettings(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseString& /*aPlayMode*/, IInvocationResponseString& /*aRecQualityMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::Stop(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::Play(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aSpeed*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::Pause(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::Record(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::Seek(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aUnit*/, const Brx& /*aTarget*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::Next(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::Previous(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::SetPlayMode(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aNewPlayMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::SetRecordQualityMode(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aNewRecordQualityMode*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgAVTransport1::GetCurrentTransportActions(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseString& /*aActions*/)
{
    ASSERTS();
}

