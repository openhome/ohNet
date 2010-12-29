#include "DvUpnpOrgAVTransport2.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

class DvProviderUpnpOrgAVTransport2C : public DvProvider
{
public:
    DvProviderUpnpOrgAVTransport2C(DvDeviceC aDevice);
    TBool SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
    TBool SetPropertyDRMState(const Brx& aValue);
    void GetPropertyDRMState(Brhz& aValue);
    void EnableActionSetAVTransportURI(CallbackAVTransport2SetAVTransportURI aCallback, void* aPtr);
    void EnableActionSetNextAVTransportURI(CallbackAVTransport2SetNextAVTransportURI aCallback, void* aPtr);
    void EnableActionGetMediaInfo(CallbackAVTransport2GetMediaInfo aCallback, void* aPtr);
    void EnableActionGetMediaInfo_Ext(CallbackAVTransport2GetMediaInfo_Ext aCallback, void* aPtr);
    void EnableActionGetTransportInfo(CallbackAVTransport2GetTransportInfo aCallback, void* aPtr);
    void EnableActionGetPositionInfo(CallbackAVTransport2GetPositionInfo aCallback, void* aPtr);
    void EnableActionGetDeviceCapabilities(CallbackAVTransport2GetDeviceCapabilities aCallback, void* aPtr);
    void EnableActionGetTransportSettings(CallbackAVTransport2GetTransportSettings aCallback, void* aPtr);
    void EnableActionStop(CallbackAVTransport2Stop aCallback, void* aPtr);
    void EnableActionPlay(CallbackAVTransport2Play aCallback, void* aPtr);
    void EnableActionPause(CallbackAVTransport2Pause aCallback, void* aPtr);
    void EnableActionRecord(CallbackAVTransport2Record aCallback, void* aPtr);
    void EnableActionSeek(CallbackAVTransport2Seek aCallback, void* aPtr);
    void EnableActionNext(CallbackAVTransport2Next aCallback, void* aPtr);
    void EnableActionPrevious(CallbackAVTransport2Previous aCallback, void* aPtr);
    void EnableActionSetPlayMode(CallbackAVTransport2SetPlayMode aCallback, void* aPtr);
    void EnableActionSetRecordQualityMode(CallbackAVTransport2SetRecordQualityMode aCallback, void* aPtr);
    void EnableActionGetCurrentTransportActions(CallbackAVTransport2GetCurrentTransportActions aCallback, void* aPtr);
    void EnableActionGetDRMState(CallbackAVTransport2GetDRMState aCallback, void* aPtr);
    void EnableActionGetStateVariables(CallbackAVTransport2GetStateVariables aCallback, void* aPtr);
    void EnableActionSetStateVariables(CallbackAVTransport2SetStateVariables aCallback, void* aPtr);
private:
    void DoSetAVTransportURI(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetNextAVTransportURI(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetMediaInfo(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetMediaInfo_Ext(IDviInvocation& aInvocation, TUint aVersion);
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
    void DoGetDRMState(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetStateVariables(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStateVariables(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackAVTransport2SetAVTransportURI iCallbackSetAVTransportURI;
    void* iPtrSetAVTransportURI;
    CallbackAVTransport2SetNextAVTransportURI iCallbackSetNextAVTransportURI;
    void* iPtrSetNextAVTransportURI;
    CallbackAVTransport2GetMediaInfo iCallbackGetMediaInfo;
    void* iPtrGetMediaInfo;
    CallbackAVTransport2GetMediaInfo_Ext iCallbackGetMediaInfo_Ext;
    void* iPtrGetMediaInfo_Ext;
    CallbackAVTransport2GetTransportInfo iCallbackGetTransportInfo;
    void* iPtrGetTransportInfo;
    CallbackAVTransport2GetPositionInfo iCallbackGetPositionInfo;
    void* iPtrGetPositionInfo;
    CallbackAVTransport2GetDeviceCapabilities iCallbackGetDeviceCapabilities;
    void* iPtrGetDeviceCapabilities;
    CallbackAVTransport2GetTransportSettings iCallbackGetTransportSettings;
    void* iPtrGetTransportSettings;
    CallbackAVTransport2Stop iCallbackStop;
    void* iPtrStop;
    CallbackAVTransport2Play iCallbackPlay;
    void* iPtrPlay;
    CallbackAVTransport2Pause iCallbackPause;
    void* iPtrPause;
    CallbackAVTransport2Record iCallbackRecord;
    void* iPtrRecord;
    CallbackAVTransport2Seek iCallbackSeek;
    void* iPtrSeek;
    CallbackAVTransport2Next iCallbackNext;
    void* iPtrNext;
    CallbackAVTransport2Previous iCallbackPrevious;
    void* iPtrPrevious;
    CallbackAVTransport2SetPlayMode iCallbackSetPlayMode;
    void* iPtrSetPlayMode;
    CallbackAVTransport2SetRecordQualityMode iCallbackSetRecordQualityMode;
    void* iPtrSetRecordQualityMode;
    CallbackAVTransport2GetCurrentTransportActions iCallbackGetCurrentTransportActions;
    void* iPtrGetCurrentTransportActions;
    CallbackAVTransport2GetDRMState iCallbackGetDRMState;
    void* iPtrGetDRMState;
    CallbackAVTransport2GetStateVariables iCallbackGetStateVariables;
    void* iPtrGetStateVariables;
    CallbackAVTransport2SetStateVariables iCallbackSetStateVariables;
    void* iPtrSetStateVariables;
    PropertyString* iPropertyLastChange;
    PropertyString* iPropertyDRMState;
};

DvProviderUpnpOrgAVTransport2C::DvProviderUpnpOrgAVTransport2C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "upnp.org", "AVTransport", 2)
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

TBool DvProviderUpnpOrgAVTransport2C::SetPropertyLastChange(const Brx& aValue)
{
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgAVTransport2C::GetPropertyLastChange(Brhz& aValue)
{
    aValue.Set(iPropertyLastChange->Value());
}

TBool DvProviderUpnpOrgAVTransport2C::SetPropertyDRMState(const Brx& aValue)
{
    return SetPropertyString(*iPropertyDRMState, aValue);
}

void DvProviderUpnpOrgAVTransport2C::GetPropertyDRMState(Brhz& aValue)
{
    aValue.Set(iPropertyDRMState->Value());
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSetAVTransportURI(CallbackAVTransport2SetAVTransportURI aCallback, void* aPtr)
{
    iCallbackSetAVTransportURI = aCallback;
    iPtrSetAVTransportURI = aPtr;
    Zapp::Action* action = new Zapp::Action("SetAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("CurrentURI"));
    action->AddInputParameter(new ParameterString("CurrentURIMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoSetAVTransportURI);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSetNextAVTransportURI(CallbackAVTransport2SetNextAVTransportURI aCallback, void* aPtr)
{
    iCallbackSetNextAVTransportURI = aCallback;
    iPtrSetNextAVTransportURI = aPtr;
    Zapp::Action* action = new Zapp::Action("SetNextAVTransportURI");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NextURI"));
    action->AddInputParameter(new ParameterString("NextURIMetaData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoSetNextAVTransportURI);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetMediaInfo(CallbackAVTransport2GetMediaInfo aCallback, void* aPtr)
{
    iCallbackGetMediaInfo = aCallback;
    iPtrGetMediaInfo = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetMediaInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetMediaInfo_Ext(CallbackAVTransport2GetMediaInfo_Ext aCallback, void* aPtr)
{
    iCallbackGetMediaInfo_Ext = aCallback;
    iPtrGetMediaInfo_Ext = aPtr;
    Zapp::Action* action = new Zapp::Action("GetMediaInfo_Ext");
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetMediaInfo_Ext);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetTransportInfo(CallbackAVTransport2GetTransportInfo aCallback, void* aPtr)
{
    iCallbackGetTransportInfo = aCallback;
    iPtrGetTransportInfo = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetTransportInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetPositionInfo(CallbackAVTransport2GetPositionInfo aCallback, void* aPtr)
{
    iCallbackGetPositionInfo = aCallback;
    iPtrGetPositionInfo = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetPositionInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetDeviceCapabilities(CallbackAVTransport2GetDeviceCapabilities aCallback, void* aPtr)
{
    iCallbackGetDeviceCapabilities = aCallback;
    iPtrGetDeviceCapabilities = aPtr;
    Zapp::Action* action = new Zapp::Action("GetDeviceCapabilities");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("PlayMedia"));
    action->AddOutputParameter(new ParameterString("RecMedia"));
    action->AddOutputParameter(new ParameterString("RecQualityModes"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetDeviceCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetTransportSettings(CallbackAVTransport2GetTransportSettings aCallback, void* aPtr)
{
    iCallbackGetTransportSettings = aCallback;
    iPtrGetTransportSettings = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetTransportSettings);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionStop(CallbackAVTransport2Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    Zapp::Action* action = new Zapp::Action("Stop");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionPlay(CallbackAVTransport2Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    Zapp::Action* action = new Zapp::Action("Play");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"1";
    action->AddInputParameter(new ParameterString("Speed", allowedValues, 1));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionPause(CallbackAVTransport2Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    Zapp::Action* action = new Zapp::Action("Pause");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionRecord(CallbackAVTransport2Record aCallback, void* aPtr)
{
    iCallbackRecord = aCallback;
    iPtrRecord = aPtr;
    Zapp::Action* action = new Zapp::Action("Record");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoRecord);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSeek(CallbackAVTransport2Seek aCallback, void* aPtr)
{
    iCallbackSeek = aCallback;
    iPtrSeek = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoSeek);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionNext(CallbackAVTransport2Next aCallback, void* aPtr)
{
    iCallbackNext = aCallback;
    iPtrNext = aPtr;
    Zapp::Action* action = new Zapp::Action("Next");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoNext);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionPrevious(CallbackAVTransport2Previous aCallback, void* aPtr)
{
    iCallbackPrevious = aCallback;
    iPtrPrevious = aPtr;
    Zapp::Action* action = new Zapp::Action("Previous");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoPrevious);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSetPlayMode(CallbackAVTransport2SetPlayMode aCallback, void* aPtr)
{
    iCallbackSetPlayMode = aCallback;
    iPtrSetPlayMode = aPtr;
    Zapp::Action* action = new Zapp::Action("SetPlayMode");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"NORMAL";
    action->AddInputParameter(new ParameterString("NewPlayMode", allowedValues, 1));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoSetPlayMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSetRecordQualityMode(CallbackAVTransport2SetRecordQualityMode aCallback, void* aPtr)
{
    iCallbackSetRecordQualityMode = aCallback;
    iPtrSetRecordQualityMode = aPtr;
    Zapp::Action* action = new Zapp::Action("SetRecordQualityMode");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NewRecordQualityMode"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoSetRecordQualityMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetCurrentTransportActions(CallbackAVTransport2GetCurrentTransportActions aCallback, void* aPtr)
{
    iCallbackGetCurrentTransportActions = aCallback;
    iPtrGetCurrentTransportActions = aPtr;
    Zapp::Action* action = new Zapp::Action("GetCurrentTransportActions");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("Actions"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetCurrentTransportActions);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetDRMState(CallbackAVTransport2GetDRMState aCallback, void* aPtr)
{
    iCallbackGetDRMState = aCallback;
    iPtrGetDRMState = aPtr;
    Zapp::Action* action = new Zapp::Action("GetDRMState");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterRelated("CurrentDRMState", *iPropertyDRMState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetDRMState);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetStateVariables(CallbackAVTransport2GetStateVariables aCallback, void* aPtr)
{
    iCallbackGetStateVariables = aCallback;
    iPtrGetStateVariables = aPtr;
    Zapp::Action* action = new Zapp::Action("GetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("StateVariableList"));
    action->AddOutputParameter(new ParameterString("StateVariableValuePairs"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetStateVariables);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSetStateVariables(CallbackAVTransport2SetStateVariables aCallback, void* aPtr)
{
    iCallbackSetStateVariables = aCallback;
    iPtrSetStateVariables = aPtr;
    Zapp::Action* action = new Zapp::Action("SetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("AVTransportUDN"));
    action->AddInputParameter(new ParameterString("ServiceType"));
    action->AddInputParameter(new ParameterString("ServiceId"));
    action->AddInputParameter(new ParameterString("StateVariableValuePairs"));
    action->AddOutputParameter(new ParameterString("StateVariableList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoSetStateVariables);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::DoSetAVTransportURI(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgAVTransport2C::DoSetNextAVTransportURI(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgAVTransport2C::DoGetMediaInfo(IDviInvocation& aInvocation, TUint aVersion)
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
    ZappFreeExternal(MediaDuration);
    respMediaDuration.Write(bufMediaDuration);
    respMediaDuration.WriteFlush();
    Brhz bufCurrentURI((const TChar*)CurrentURI);
    ZappFreeExternal(CurrentURI);
    respCurrentURI.Write(bufCurrentURI);
    respCurrentURI.WriteFlush();
    Brhz bufCurrentURIMetaData((const TChar*)CurrentURIMetaData);
    ZappFreeExternal(CurrentURIMetaData);
    respCurrentURIMetaData.Write(bufCurrentURIMetaData);
    respCurrentURIMetaData.WriteFlush();
    Brhz bufNextURI((const TChar*)NextURI);
    ZappFreeExternal(NextURI);
    respNextURI.Write(bufNextURI);
    respNextURI.WriteFlush();
    Brhz bufNextURIMetaData((const TChar*)NextURIMetaData);
    ZappFreeExternal(NextURIMetaData);
    respNextURIMetaData.Write(bufNextURIMetaData);
    respNextURIMetaData.WriteFlush();
    Brhz bufPlayMedium((const TChar*)PlayMedium);
    ZappFreeExternal(PlayMedium);
    respPlayMedium.Write(bufPlayMedium);
    respPlayMedium.WriteFlush();
    Brhz bufRecordMedium((const TChar*)RecordMedium);
    ZappFreeExternal(RecordMedium);
    respRecordMedium.Write(bufRecordMedium);
    respRecordMedium.WriteFlush();
    Brhz bufWriteStatus((const TChar*)WriteStatus);
    ZappFreeExternal(WriteStatus);
    respWriteStatus.Write(bufWriteStatus);
    respWriteStatus.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgAVTransport2C::DoGetMediaInfo_Ext(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* CurrentType;
    uint32_t NrTracks;
    char* MediaDuration;
    char* CurrentURI;
    char* CurrentURIMetaData;
    char* NextURI;
    char* NextURIMetaData;
    char* PlayMedium;
    char* RecordMedium;
    char* WriteStatus;
    ASSERT(iCallbackGetMediaInfo_Ext != NULL);
    if (0 != iCallbackGetMediaInfo_Ext(iPtrGetMediaInfo_Ext, aVersion, InstanceID, &CurrentType, &NrTracks, &MediaDuration, &CurrentURI, &CurrentURIMetaData, &NextURI, &NextURIMetaData, &PlayMedium, &RecordMedium, &WriteStatus)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respCurrentType(aInvocation, "CurrentType");
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
    Brhz bufCurrentType((const TChar*)CurrentType);
    ZappFreeExternal(CurrentType);
    respCurrentType.Write(bufCurrentType);
    respCurrentType.WriteFlush();
    respNrTracks.Write(NrTracks);
    Brhz bufMediaDuration((const TChar*)MediaDuration);
    ZappFreeExternal(MediaDuration);
    respMediaDuration.Write(bufMediaDuration);
    respMediaDuration.WriteFlush();
    Brhz bufCurrentURI((const TChar*)CurrentURI);
    ZappFreeExternal(CurrentURI);
    respCurrentURI.Write(bufCurrentURI);
    respCurrentURI.WriteFlush();
    Brhz bufCurrentURIMetaData((const TChar*)CurrentURIMetaData);
    ZappFreeExternal(CurrentURIMetaData);
    respCurrentURIMetaData.Write(bufCurrentURIMetaData);
    respCurrentURIMetaData.WriteFlush();
    Brhz bufNextURI((const TChar*)NextURI);
    ZappFreeExternal(NextURI);
    respNextURI.Write(bufNextURI);
    respNextURI.WriteFlush();
    Brhz bufNextURIMetaData((const TChar*)NextURIMetaData);
    ZappFreeExternal(NextURIMetaData);
    respNextURIMetaData.Write(bufNextURIMetaData);
    respNextURIMetaData.WriteFlush();
    Brhz bufPlayMedium((const TChar*)PlayMedium);
    ZappFreeExternal(PlayMedium);
    respPlayMedium.Write(bufPlayMedium);
    respPlayMedium.WriteFlush();
    Brhz bufRecordMedium((const TChar*)RecordMedium);
    ZappFreeExternal(RecordMedium);
    respRecordMedium.Write(bufRecordMedium);
    respRecordMedium.WriteFlush();
    Brhz bufWriteStatus((const TChar*)WriteStatus);
    ZappFreeExternal(WriteStatus);
    respWriteStatus.Write(bufWriteStatus);
    respWriteStatus.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgAVTransport2C::DoGetTransportInfo(IDviInvocation& aInvocation, TUint aVersion)
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
    ZappFreeExternal(CurrentTransportState);
    respCurrentTransportState.Write(bufCurrentTransportState);
    respCurrentTransportState.WriteFlush();
    Brhz bufCurrentTransportStatus((const TChar*)CurrentTransportStatus);
    ZappFreeExternal(CurrentTransportStatus);
    respCurrentTransportStatus.Write(bufCurrentTransportStatus);
    respCurrentTransportStatus.WriteFlush();
    Brhz bufCurrentSpeed((const TChar*)CurrentSpeed);
    ZappFreeExternal(CurrentSpeed);
    respCurrentSpeed.Write(bufCurrentSpeed);
    respCurrentSpeed.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgAVTransport2C::DoGetPositionInfo(IDviInvocation& aInvocation, TUint aVersion)
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
    ZappFreeExternal(TrackDuration);
    respTrackDuration.Write(bufTrackDuration);
    respTrackDuration.WriteFlush();
    Brhz bufTrackMetaData((const TChar*)TrackMetaData);
    ZappFreeExternal(TrackMetaData);
    respTrackMetaData.Write(bufTrackMetaData);
    respTrackMetaData.WriteFlush();
    Brhz bufTrackURI((const TChar*)TrackURI);
    ZappFreeExternal(TrackURI);
    respTrackURI.Write(bufTrackURI);
    respTrackURI.WriteFlush();
    Brhz bufRelTime((const TChar*)RelTime);
    ZappFreeExternal(RelTime);
    respRelTime.Write(bufRelTime);
    respRelTime.WriteFlush();
    Brhz bufAbsTime((const TChar*)AbsTime);
    ZappFreeExternal(AbsTime);
    respAbsTime.Write(bufAbsTime);
    respAbsTime.WriteFlush();
    respRelCount.Write(RelCount);
    respAbsCount.Write(AbsCount);
    resp.End();
}

void DvProviderUpnpOrgAVTransport2C::DoGetDeviceCapabilities(IDviInvocation& aInvocation, TUint aVersion)
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
    ZappFreeExternal(PlayMedia);
    respPlayMedia.Write(bufPlayMedia);
    respPlayMedia.WriteFlush();
    Brhz bufRecMedia((const TChar*)RecMedia);
    ZappFreeExternal(RecMedia);
    respRecMedia.Write(bufRecMedia);
    respRecMedia.WriteFlush();
    Brhz bufRecQualityModes((const TChar*)RecQualityModes);
    ZappFreeExternal(RecQualityModes);
    respRecQualityModes.Write(bufRecQualityModes);
    respRecQualityModes.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgAVTransport2C::DoGetTransportSettings(IDviInvocation& aInvocation, TUint aVersion)
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
    ZappFreeExternal(PlayMode);
    respPlayMode.Write(bufPlayMode);
    respPlayMode.WriteFlush();
    Brhz bufRecQualityMode((const TChar*)RecQualityMode);
    ZappFreeExternal(RecQualityMode);
    respRecQualityMode.Write(bufRecQualityMode);
    respRecQualityMode.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgAVTransport2C::DoStop(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgAVTransport2C::DoPlay(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgAVTransport2C::DoPause(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgAVTransport2C::DoRecord(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgAVTransport2C::DoSeek(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgAVTransport2C::DoNext(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgAVTransport2C::DoPrevious(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgAVTransport2C::DoSetPlayMode(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgAVTransport2C::DoSetRecordQualityMode(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgAVTransport2C::DoGetCurrentTransportActions(IDviInvocation& aInvocation, TUint aVersion)
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
    ZappFreeExternal(Actions);
    respActions.Write(bufActions);
    respActions.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgAVTransport2C::DoGetDRMState(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* CurrentDRMState;
    ASSERT(iCallbackGetDRMState != NULL);
    if (0 != iCallbackGetDRMState(iPtrGetDRMState, aVersion, InstanceID, &CurrentDRMState)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respCurrentDRMState(aInvocation, "CurrentDRMState");
    resp.Start();
    Brhz bufCurrentDRMState((const TChar*)CurrentDRMState);
    ZappFreeExternal(CurrentDRMState);
    respCurrentDRMState.Write(bufCurrentDRMState);
    respCurrentDRMState.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgAVTransport2C::DoGetStateVariables(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz StateVariableList;
    aInvocation.InvocationReadString("StateVariableList", StateVariableList);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* StateVariableValuePairs;
    ASSERT(iCallbackGetStateVariables != NULL);
    if (0 != iCallbackGetStateVariables(iPtrGetStateVariables, aVersion, InstanceID, (const char*)StateVariableList.Ptr(), &StateVariableValuePairs)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respStateVariableValuePairs(aInvocation, "StateVariableValuePairs");
    resp.Start();
    Brhz bufStateVariableValuePairs((const TChar*)StateVariableValuePairs);
    ZappFreeExternal(StateVariableValuePairs);
    respStateVariableValuePairs.Write(bufStateVariableValuePairs);
    respStateVariableValuePairs.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgAVTransport2C::DoSetStateVariables(IDviInvocation& aInvocation, TUint aVersion)
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
    InvocationResponse resp(aInvocation);
    char* StateVariableList;
    ASSERT(iCallbackSetStateVariables != NULL);
    if (0 != iCallbackSetStateVariables(iPtrSetStateVariables, aVersion, InstanceID, (const char*)AVTransportUDN.Ptr(), (const char*)ServiceType.Ptr(), (const char*)ServiceId.Ptr(), (const char*)StateVariableValuePairs.Ptr(), &StateVariableList)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respStateVariableList(aInvocation, "StateVariableList");
    resp.Start();
    Brhz bufStateVariableList((const TChar*)StateVariableList);
    ZappFreeExternal(StateVariableList);
    respStateVariableList.Write(bufStateVariableList);
    respStateVariableList.WriteFlush();
    resp.End();
}



THandle DvProviderUpnpOrgAVTransport2Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgAVTransport2C(aDevice);
}

void DvProviderUpnpOrgAVTransport2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider);
}

void DvProviderUpnpOrgAVTransport2EnableActionSetAVTransportURI(THandle aProvider, CallbackAVTransport2SetAVTransportURI aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionSetAVTransportURI(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionSetNextAVTransportURI(THandle aProvider, CallbackAVTransport2SetNextAVTransportURI aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionSetNextAVTransportURI(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionGetMediaInfo(THandle aProvider, CallbackAVTransport2GetMediaInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetMediaInfo(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionGetMediaInfo_Ext(THandle aProvider, CallbackAVTransport2GetMediaInfo_Ext aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetMediaInfo_Ext(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionGetTransportInfo(THandle aProvider, CallbackAVTransport2GetTransportInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetTransportInfo(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionGetPositionInfo(THandle aProvider, CallbackAVTransport2GetPositionInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetPositionInfo(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionGetDeviceCapabilities(THandle aProvider, CallbackAVTransport2GetDeviceCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetDeviceCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionGetTransportSettings(THandle aProvider, CallbackAVTransport2GetTransportSettings aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetTransportSettings(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionStop(THandle aProvider, CallbackAVTransport2Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionStop(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionPlay(THandle aProvider, CallbackAVTransport2Play aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionPlay(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionPause(THandle aProvider, CallbackAVTransport2Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionPause(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionRecord(THandle aProvider, CallbackAVTransport2Record aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionRecord(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionSeek(THandle aProvider, CallbackAVTransport2Seek aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionSeek(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionNext(THandle aProvider, CallbackAVTransport2Next aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionNext(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionPrevious(THandle aProvider, CallbackAVTransport2Previous aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionPrevious(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionSetPlayMode(THandle aProvider, CallbackAVTransport2SetPlayMode aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionSetPlayMode(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionSetRecordQualityMode(THandle aProvider, CallbackAVTransport2SetRecordQualityMode aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionSetRecordQualityMode(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionGetCurrentTransportActions(THandle aProvider, CallbackAVTransport2GetCurrentTransportActions aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetCurrentTransportActions(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionGetDRMState(THandle aProvider, CallbackAVTransport2GetDRMState aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetDRMState(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionGetStateVariables(THandle aProvider, CallbackAVTransport2GetStateVariables aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetStateVariables(aCallback, aPtr);
}

void DvProviderUpnpOrgAVTransport2EnableActionSetStateVariables(THandle aProvider, CallbackAVTransport2SetStateVariables aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionSetStateVariables(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgAVTransport2SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->SetPropertyLastChange(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgAVTransport2GetPropertyLastChange(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderUpnpOrgAVTransport2SetPropertyDRMState(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->SetPropertyDRMState(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgAVTransport2GetPropertyDRMState(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->GetPropertyDRMState(buf);
    *aValue = (char*)buf.Transfer();
}

