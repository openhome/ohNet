#include "DvUpnpOrgAVTransport1.h"
#include <OhNetTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/OhNet.h>
#include <OhNetTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome::Net;

class DvProviderUpnpOrgAVTransport1C : public DvProvider
{
public:
    DvProviderUpnpOrgAVTransport1C(DvDeviceC aDevice);
    TBool SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
    void EnableActionSetAVTransportURI(CallbackAVTransport1SetAVTransportURI aCallback, void* aPtr);
    void EnableActionSetNextAVTransportURI(CallbackAVTransport1SetNextAVTransportURI aCallback, void* aPtr);
    void EnableActionGetMediaInfo(CallbackAVTransport1GetMediaInfo aCallback, void* aPtr);
    void EnableActionGetTransportInfo(CallbackAVTransport1GetTransportInfo aCallback, void* aPtr);
    void EnableActionGetPositionInfo(CallbackAVTransport1GetPositionInfo aCallback, void* aPtr);
    void EnableActionGetDeviceCapabilities(CallbackAVTransport1GetDeviceCapabilities aCallback, void* aPtr);
    void EnableActionGetTransportSettings(CallbackAVTransport1GetTransportSettings aCallback, void* aPtr);
    void EnableActionStop(CallbackAVTransport1Stop aCallback, void* aPtr);
    void EnableActionPlay(CallbackAVTransport1Play aCallback, void* aPtr);
    void EnableActionPause(CallbackAVTransport1Pause aCallback, void* aPtr);
    void EnableActionRecord(CallbackAVTransport1Record aCallback, void* aPtr);
    void EnableActionSeek(CallbackAVTransport1Seek aCallback, void* aPtr);
    void EnableActionNext(CallbackAVTransport1Next aCallback, void* aPtr);
    void EnableActionPrevious(CallbackAVTransport1Previous aCallback, void* aPtr);
    void EnableActionSetPlayMode(CallbackAVTransport1SetPlayMode aCallback, void* aPtr);
    void EnableActionSetRecordQualityMode(CallbackAVTransport1SetRecordQualityMode aCallback, void* aPtr);
    void EnableActionGetCurrentTransportActions(CallbackAVTransport1GetCurrentTransportActions aCallback, void* aPtr);
private:
    void DoSetAVTransportURI(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetNextAVTransportURI(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetMediaInfo(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetTransportInfo(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetPositionInfo(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetDeviceCapabilities(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetTransportSettings(IDviInvocation& aInvocation, TUint aVersion);
    void DoStop(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlay(IDviInvocation& aInvocation, TUint aVersion);
    void DoPause(IDviInvocation& aInvocation, TUint aVersion);
    void DoRecord(IDviInvocation& aInvocation, TUint aVersion);
    void DoSeek(IDviInvocation& aInvocation, TUint aVersion);
    void DoNext(IDviInvocation& aInvocation, TUint aVersion);
    void DoPrevious(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetPlayMode(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRecordQualityMode(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetCurrentTransportActions(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackAVTransport1SetAVTransportURI iCallbackSetAVTransportURI;
    void* iPtrSetAVTransportURI;
    CallbackAVTransport1SetNextAVTransportURI iCallbackSetNextAVTransportURI;
    void* iPtrSetNextAVTransportURI;
    CallbackAVTransport1GetMediaInfo iCallbackGetMediaInfo;
    void* iPtrGetMediaInfo;
    CallbackAVTransport1GetTransportInfo iCallbackGetTransportInfo;
    void* iPtrGetTransportInfo;
    CallbackAVTransport1GetPositionInfo iCallbackGetPositionInfo;
    void* iPtrGetPositionInfo;
    CallbackAVTransport1GetDeviceCapabilities iCallbackGetDeviceCapabilities;
    void* iPtrGetDeviceCapabilities;
    CallbackAVTransport1GetTransportSettings iCallbackGetTransportSettings;
    void* iPtrGetTransportSettings;
    CallbackAVTransport1Stop iCallbackStop;
    void* iPtrStop;
    CallbackAVTransport1Play iCallbackPlay;
    void* iPtrPlay;
    CallbackAVTransport1Pause iCallbackPause;
    void* iPtrPause;
    CallbackAVTransport1Record iCallbackRecord;
    void* iPtrRecord;
    CallbackAVTransport1Seek iCallbackSeek;
    void* iPtrSeek;
    CallbackAVTransport1Next iCallbackNext;
    void* iPtrNext;
    CallbackAVTransport1Previous iCallbackPrevious;
    void* iPtrPrevious;
    CallbackAVTransport1SetPlayMode iCallbackSetPlayMode;
    void* iPtrSetPlayMode;
    CallbackAVTransport1SetRecordQualityMode iCallbackSetRecordQualityMode;
    void* iPtrSetRecordQualityMode;
    CallbackAVTransport1GetCurrentTransportActions iCallbackGetCurrentTransportActions;
    void* iPtrGetCurrentTransportActions;
    PropertyString* iPropertyLastChange;
};

DvProviderUpnpOrgAVTransport1C::DvProviderUpnpOrgAVTransport1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "upnp.org", "AVTransport", 1)
{
    
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

TBool DvProviderUpnpOrgAVTransport1C::SetPropertyLastChange(const Brx& aValue)
{
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgAVTransport1C::GetPropertyLastChange(Brhz& aValue)
{
    aValue.Set(iPropertyLastChange->Value());
}

void DvProviderUpnpOrgAVTransport1C::EnableActionSetAVTransportURI(CallbackAVTransport1SetAVTransportURI aCallback, void* aPtr)
{
    iCallbackSetAVTransportURI = aCallback;
    iPtrSetAVTransportURI = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("CurrentURI"));
    action->AddInputParameter(new ParameterString("CurrentURIMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoSetAVTransportURI);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionSetNextAVTransportURI(CallbackAVTransport1SetNextAVTransportURI aCallback, void* aPtr)
{
    iCallbackSetNextAVTransportURI = aCallback;
    iPtrSetNextAVTransportURI = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetNextAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NextURI"));
    action->AddInputParameter(new ParameterString("NextURIMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoSetNextAVTransportURI);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionGetMediaInfo(CallbackAVTransport1GetMediaInfo aCallback, void* aPtr)
{
    iCallbackGetMediaInfo = aCallback;
    iPtrGetMediaInfo = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoGetMediaInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionGetTransportInfo(CallbackAVTransport1GetTransportInfo aCallback, void* aPtr)
{
    iCallbackGetTransportInfo = aCallback;
    iPtrGetTransportInfo = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoGetTransportInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionGetPositionInfo(CallbackAVTransport1GetPositionInfo aCallback, void* aPtr)
{
    iCallbackGetPositionInfo = aCallback;
    iPtrGetPositionInfo = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoGetPositionInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionGetDeviceCapabilities(CallbackAVTransport1GetDeviceCapabilities aCallback, void* aPtr)
{
    iCallbackGetDeviceCapabilities = aCallback;
    iPtrGetDeviceCapabilities = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetDeviceCapabilities");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("PlayMedia"));
    action->AddOutputParameter(new ParameterString("RecMedia"));
    action->AddOutputParameter(new ParameterString("RecQualityModes"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoGetDeviceCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionGetTransportSettings(CallbackAVTransport1GetTransportSettings aCallback, void* aPtr)
{
    iCallbackGetTransportSettings = aCallback;
    iPtrGetTransportSettings = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoGetTransportSettings);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionStop(CallbackAVTransport1Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionPlay(CallbackAVTransport1Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"1";
    action->AddInputParameter(new ParameterString("Speed", allowedValues, 1));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionPause(CallbackAVTransport1Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Pause");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionRecord(CallbackAVTransport1Record aCallback, void* aPtr)
{
    iCallbackRecord = aCallback;
    iPtrRecord = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Record");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoRecord);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionSeek(CallbackAVTransport1Seek aCallback, void* aPtr)
{
    iCallbackSeek = aCallback;
    iPtrSeek = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoSeek);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionNext(CallbackAVTransport1Next aCallback, void* aPtr)
{
    iCallbackNext = aCallback;
    iPtrNext = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Next");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoNext);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionPrevious(CallbackAVTransport1Previous aCallback, void* aPtr)
{
    iCallbackPrevious = aCallback;
    iPtrPrevious = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Previous");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoPrevious);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionSetPlayMode(CallbackAVTransport1SetPlayMode aCallback, void* aPtr)
{
    iCallbackSetPlayMode = aCallback;
    iPtrSetPlayMode = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetPlayMode");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"NORMAL";
    action->AddInputParameter(new ParameterString("NewPlayMode", allowedValues, 1));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoSetPlayMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionSetRecordQualityMode(CallbackAVTransport1SetRecordQualityMode aCallback, void* aPtr)
{
    iCallbackSetRecordQualityMode = aCallback;
    iPtrSetRecordQualityMode = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRecordQualityMode");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NewRecordQualityMode"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoSetRecordQualityMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionGetCurrentTransportActions(CallbackAVTransport1GetCurrentTransportActions aCallback, void* aPtr)
{
    iCallbackGetCurrentTransportActions = aCallback;
    iPtrGetCurrentTransportActions = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetCurrentTransportActions");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("Actions"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoGetCurrentTransportActions);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::DoSetAVTransportURI(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz CurrentURI;
    aInvocation.InvocationReadString("CurrentURI", CurrentURI);
    Brhz CurrentURIMetaData;
    aInvocation.InvocationReadString("CurrentURIMetaData", CurrentURIMetaData);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetAVTransportURI != NULL);
    if (0 != iCallbackSetAVTransportURI(iPtrSetAVTransportURI, aVersion, InstanceID, (const char*)CurrentURI.Ptr(), (const char*)CurrentURIMetaData.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoSetNextAVTransportURI(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz NextURI;
    aInvocation.InvocationReadString("NextURI", NextURI);
    Brhz NextURIMetaData;
    aInvocation.InvocationReadString("NextURIMetaData", NextURIMetaData);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetNextAVTransportURI != NULL);
    if (0 != iCallbackSetNextAVTransportURI(iPtrSetNextAVTransportURI, aVersion, InstanceID, (const char*)NextURI.Ptr(), (const char*)NextURIMetaData.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoGetMediaInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t NrTracks;
    char* MediaDuration;
    char* CurrentURI;
    char* CurrentURIMetaData;
    char* NextURI;
    char* NextURIMetaData;
    char* PlayMedium;
    char* RecordMedium;
    char* WriteStatus;
    ASSERT(iCallbackGetMediaInfo != NULL);
    if (0 != iCallbackGetMediaInfo(iPtrGetMediaInfo, aVersion, InstanceID, &NrTracks, &MediaDuration, &CurrentURI, &CurrentURIMetaData, &NextURI, &NextURIMetaData, &PlayMedium, &RecordMedium, &WriteStatus)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respNrTracks(aInvocation, "NrTracks");
    InvocationResponseString respMediaDuration(aInvocation, "MediaDuration");
    InvocationResponseString respCurrentURI(aInvocation, "CurrentURI");
    InvocationResponseString respCurrentURIMetaData(aInvocation, "CurrentURIMetaData");
    InvocationResponseString respNextURI(aInvocation, "NextURI");
    InvocationResponseString respNextURIMetaData(aInvocation, "NextURIMetaData");
    InvocationResponseString respPlayMedium(aInvocation, "PlayMedium");
    InvocationResponseString respRecordMedium(aInvocation, "RecordMedium");
    InvocationResponseString respWriteStatus(aInvocation, "WriteStatus");
    resp.Start();
    respNrTracks.Write(NrTracks);
    Brhz bufMediaDuration((const TChar*)MediaDuration);
    OhNetFreeExternal(MediaDuration);
    respMediaDuration.Write(bufMediaDuration);
    respMediaDuration.WriteFlush();
    Brhz bufCurrentURI((const TChar*)CurrentURI);
    OhNetFreeExternal(CurrentURI);
    respCurrentURI.Write(bufCurrentURI);
    respCurrentURI.WriteFlush();
    Brhz bufCurrentURIMetaData((const TChar*)CurrentURIMetaData);
    OhNetFreeExternal(CurrentURIMetaData);
    respCurrentURIMetaData.Write(bufCurrentURIMetaData);
    respCurrentURIMetaData.WriteFlush();
    Brhz bufNextURI((const TChar*)NextURI);
    OhNetFreeExternal(NextURI);
    respNextURI.Write(bufNextURI);
    respNextURI.WriteFlush();
    Brhz bufNextURIMetaData((const TChar*)NextURIMetaData);
    OhNetFreeExternal(NextURIMetaData);
    respNextURIMetaData.Write(bufNextURIMetaData);
    respNextURIMetaData.WriteFlush();
    Brhz bufPlayMedium((const TChar*)PlayMedium);
    OhNetFreeExternal(PlayMedium);
    respPlayMedium.Write(bufPlayMedium);
    respPlayMedium.WriteFlush();
    Brhz bufRecordMedium((const TChar*)RecordMedium);
    OhNetFreeExternal(RecordMedium);
    respRecordMedium.Write(bufRecordMedium);
    respRecordMedium.WriteFlush();
    Brhz bufWriteStatus((const TChar*)WriteStatus);
    OhNetFreeExternal(WriteStatus);
    respWriteStatus.Write(bufWriteStatus);
    respWriteStatus.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoGetTransportInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* CurrentTransportState;
    char* CurrentTransportStatus;
    char* CurrentSpeed;
    ASSERT(iCallbackGetTransportInfo != NULL);
    if (0 != iCallbackGetTransportInfo(iPtrGetTransportInfo, aVersion, InstanceID, &CurrentTransportState, &CurrentTransportStatus, &CurrentSpeed)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respCurrentTransportState(aInvocation, "CurrentTransportState");
    InvocationResponseString respCurrentTransportStatus(aInvocation, "CurrentTransportStatus");
    InvocationResponseString respCurrentSpeed(aInvocation, "CurrentSpeed");
    resp.Start();
    Brhz bufCurrentTransportState((const TChar*)CurrentTransportState);
    OhNetFreeExternal(CurrentTransportState);
    respCurrentTransportState.Write(bufCurrentTransportState);
    respCurrentTransportState.WriteFlush();
    Brhz bufCurrentTransportStatus((const TChar*)CurrentTransportStatus);
    OhNetFreeExternal(CurrentTransportStatus);
    respCurrentTransportStatus.Write(bufCurrentTransportStatus);
    respCurrentTransportStatus.WriteFlush();
    Brhz bufCurrentSpeed((const TChar*)CurrentSpeed);
    OhNetFreeExternal(CurrentSpeed);
    respCurrentSpeed.Write(bufCurrentSpeed);
    respCurrentSpeed.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoGetPositionInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Track;
    char* TrackDuration;
    char* TrackMetaData;
    char* TrackURI;
    char* RelTime;
    char* AbsTime;
    int32_t RelCount;
    int32_t AbsCount;
    ASSERT(iCallbackGetPositionInfo != NULL);
    if (0 != iCallbackGetPositionInfo(iPtrGetPositionInfo, aVersion, InstanceID, &Track, &TrackDuration, &TrackMetaData, &TrackURI, &RelTime, &AbsTime, &RelCount, &AbsCount)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respTrack(aInvocation, "Track");
    InvocationResponseString respTrackDuration(aInvocation, "TrackDuration");
    InvocationResponseString respTrackMetaData(aInvocation, "TrackMetaData");
    InvocationResponseString respTrackURI(aInvocation, "TrackURI");
    InvocationResponseString respRelTime(aInvocation, "RelTime");
    InvocationResponseString respAbsTime(aInvocation, "AbsTime");
    InvocationResponseInt respRelCount(aInvocation, "RelCount");
    InvocationResponseInt respAbsCount(aInvocation, "AbsCount");
    resp.Start();
    respTrack.Write(Track);
    Brhz bufTrackDuration((const TChar*)TrackDuration);
    OhNetFreeExternal(TrackDuration);
    respTrackDuration.Write(bufTrackDuration);
    respTrackDuration.WriteFlush();
    Brhz bufTrackMetaData((const TChar*)TrackMetaData);
    OhNetFreeExternal(TrackMetaData);
    respTrackMetaData.Write(bufTrackMetaData);
    respTrackMetaData.WriteFlush();
    Brhz bufTrackURI((const TChar*)TrackURI);
    OhNetFreeExternal(TrackURI);
    respTrackURI.Write(bufTrackURI);
    respTrackURI.WriteFlush();
    Brhz bufRelTime((const TChar*)RelTime);
    OhNetFreeExternal(RelTime);
    respRelTime.Write(bufRelTime);
    respRelTime.WriteFlush();
    Brhz bufAbsTime((const TChar*)AbsTime);
    OhNetFreeExternal(AbsTime);
    respAbsTime.Write(bufAbsTime);
    respAbsTime.WriteFlush();
    respRelCount.Write(RelCount);
    respAbsCount.Write(AbsCount);
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoGetDeviceCapabilities(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* PlayMedia;
    char* RecMedia;
    char* RecQualityModes;
    ASSERT(iCallbackGetDeviceCapabilities != NULL);
    if (0 != iCallbackGetDeviceCapabilities(iPtrGetDeviceCapabilities, aVersion, InstanceID, &PlayMedia, &RecMedia, &RecQualityModes)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respPlayMedia(aInvocation, "PlayMedia");
    InvocationResponseString respRecMedia(aInvocation, "RecMedia");
    InvocationResponseString respRecQualityModes(aInvocation, "RecQualityModes");
    resp.Start();
    Brhz bufPlayMedia((const TChar*)PlayMedia);
    OhNetFreeExternal(PlayMedia);
    respPlayMedia.Write(bufPlayMedia);
    respPlayMedia.WriteFlush();
    Brhz bufRecMedia((const TChar*)RecMedia);
    OhNetFreeExternal(RecMedia);
    respRecMedia.Write(bufRecMedia);
    respRecMedia.WriteFlush();
    Brhz bufRecQualityModes((const TChar*)RecQualityModes);
    OhNetFreeExternal(RecQualityModes);
    respRecQualityModes.Write(bufRecQualityModes);
    respRecQualityModes.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoGetTransportSettings(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* PlayMode;
    char* RecQualityMode;
    ASSERT(iCallbackGetTransportSettings != NULL);
    if (0 != iCallbackGetTransportSettings(iPtrGetTransportSettings, aVersion, InstanceID, &PlayMode, &RecQualityMode)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respPlayMode(aInvocation, "PlayMode");
    InvocationResponseString respRecQualityMode(aInvocation, "RecQualityMode");
    resp.Start();
    Brhz bufPlayMode((const TChar*)PlayMode);
    OhNetFreeExternal(PlayMode);
    respPlayMode.Write(bufPlayMode);
    respPlayMode.WriteFlush();
    Brhz bufRecQualityMode((const TChar*)RecQualityMode);
    OhNetFreeExternal(RecQualityMode);
    respRecQualityMode.Write(bufRecQualityMode);
    respRecQualityMode.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoStop(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, aVersion, InstanceID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoPlay(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Speed;
    aInvocation.InvocationReadString("Speed", Speed);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, aVersion, InstanceID, (const char*)Speed.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoPause(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackPause != NULL);
    if (0 != iCallbackPause(iPtrPause, aVersion, InstanceID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoRecord(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackRecord != NULL);
    if (0 != iCallbackRecord(iPtrRecord, aVersion, InstanceID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoSeek(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Unit;
    aInvocation.InvocationReadString("Unit", Unit);
    Brhz Target;
    aInvocation.InvocationReadString("Target", Target);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSeek != NULL);
    if (0 != iCallbackSeek(iPtrSeek, aVersion, InstanceID, (const char*)Unit.Ptr(), (const char*)Target.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoNext(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackNext != NULL);
    if (0 != iCallbackNext(iPtrNext, aVersion, InstanceID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoPrevious(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackPrevious != NULL);
    if (0 != iCallbackPrevious(iPtrPrevious, aVersion, InstanceID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoSetPlayMode(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz NewPlayMode;
    aInvocation.InvocationReadString("NewPlayMode", NewPlayMode);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetPlayMode != NULL);
    if (0 != iCallbackSetPlayMode(iPtrSetPlayMode, aVersion, InstanceID, (const char*)NewPlayMode.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoSetRecordQualityMode(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz NewRecordQualityMode;
    aInvocation.InvocationReadString("NewRecordQualityMode", NewRecordQualityMode);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetRecordQualityMode != NULL);
    if (0 != iCallbackSetRecordQualityMode(iPtrSetRecordQualityMode, aVersion, InstanceID, (const char*)NewRecordQualityMode.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgAVTransport1C::DoGetCurrentTransportActions(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Actions;
    ASSERT(iCallbackGetCurrentTransportActions != NULL);
    if (0 != iCallbackGetCurrentTransportActions(iPtrGetCurrentTransportActions, aVersion, InstanceID, &Actions)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respActions(aInvocation, "Actions");
    resp.Start();
    Brhz bufActions((const TChar*)Actions);
    OhNetFreeExternal(Actions);
    respActions.Write(bufActions);
    respActions.WriteFlush();
    resp.End();
}



THandle DvProviderUpnpOrgAVTransport1Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgAVTransport1C(aDevice);
}

void DvProviderUpnpOrgAVTransport1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider);
}

void DvProviderUpnpOrgAVTransport1EnableActionSetAVTransportURI(THandle aProvider, CallbackAVTransport1SetAVTransportURI aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionSetAVTransportURI(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionSetNextAVTransportURI(THandle aProvider, CallbackAVTransport1SetNextAVTransportURI aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionSetNextAVTransportURI(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionGetMediaInfo(THandle aProvider, CallbackAVTransport1GetMediaInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionGetMediaInfo(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionGetTransportInfo(THandle aProvider, CallbackAVTransport1GetTransportInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionGetTransportInfo(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionGetPositionInfo(THandle aProvider, CallbackAVTransport1GetPositionInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionGetPositionInfo(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionGetDeviceCapabilities(THandle aProvider, CallbackAVTransport1GetDeviceCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionGetDeviceCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionGetTransportSettings(THandle aProvider, CallbackAVTransport1GetTransportSettings aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionGetTransportSettings(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionStop(THandle aProvider, CallbackAVTransport1Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionStop(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionPlay(THandle aProvider, CallbackAVTransport1Play aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionPlay(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionPause(THandle aProvider, CallbackAVTransport1Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionPause(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionRecord(THandle aProvider, CallbackAVTransport1Record aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionRecord(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionSeek(THandle aProvider, CallbackAVTransport1Seek aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionSeek(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionNext(THandle aProvider, CallbackAVTransport1Next aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionNext(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionPrevious(THandle aProvider, CallbackAVTransport1Previous aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionPrevious(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionSetPlayMode(THandle aProvider, CallbackAVTransport1SetPlayMode aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionSetPlayMode(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionSetRecordQualityMode(THandle aProvider, CallbackAVTransport1SetRecordQualityMode aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionSetRecordQualityMode(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport1EnableActionGetCurrentTransportActions(THandle aProvider, CallbackAVTransport1GetCurrentTransportActions aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionGetCurrentTransportActions(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgAVTransport1SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->SetPropertyLastChange(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgAVTransport1GetPropertyLastChange(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

