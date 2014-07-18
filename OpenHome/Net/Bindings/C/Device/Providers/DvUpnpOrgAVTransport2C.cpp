#include "DvUpnpOrgAVTransport2.h"
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/C/DvInvocation.h>
#include <OpenHome/Net/C/DvInvocationPrivate.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class DvProviderUpnpOrgAVTransport2C : public DvProvider
{
public:
    DvProviderUpnpOrgAVTransport2C(DvDeviceC aDevice);
    TBool SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
    TBool SetPropertyDRMState(const Brx& aValue);
    void GetPropertyDRMState(Brhz& aValue);
    void EnablePropertyLastChange();
    void EnablePropertyDRMState();
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
    void DoSetAVTransportURI(IDviInvocation& aInvocation);
    void DoSetNextAVTransportURI(IDviInvocation& aInvocation);
    void DoGetMediaInfo(IDviInvocation& aInvocation);
    void DoGetMediaInfo_Ext(IDviInvocation& aInvocation);
    void DoGetTransportInfo(IDviInvocation& aInvocation);
    void DoGetPositionInfo(IDviInvocation& aInvocation);
    void DoGetDeviceCapabilities(IDviInvocation& aInvocation);
    void DoGetTransportSettings(IDviInvocation& aInvocation);
    void DoStop(IDviInvocation& aInvocation);
    void DoPlay(IDviInvocation& aInvocation);
    void DoPause(IDviInvocation& aInvocation);
    void DoRecord(IDviInvocation& aInvocation);
    void DoSeek(IDviInvocation& aInvocation);
    void DoNext(IDviInvocation& aInvocation);
    void DoPrevious(IDviInvocation& aInvocation);
    void DoSetPlayMode(IDviInvocation& aInvocation);
    void DoSetRecordQualityMode(IDviInvocation& aInvocation);
    void DoGetCurrentTransportActions(IDviInvocation& aInvocation);
    void DoGetDRMState(IDviInvocation& aInvocation);
    void DoGetStateVariables(IDviInvocation& aInvocation);
    void DoSetStateVariables(IDviInvocation& aInvocation);
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
    iPropertyLastChange = NULL;
    iPropertyDRMState = NULL;
}

TBool DvProviderUpnpOrgAVTransport2C::SetPropertyLastChange(const Brx& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgAVTransport2C::GetPropertyLastChange(Brhz& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    aValue.Set(iPropertyLastChange->Value());
}

TBool DvProviderUpnpOrgAVTransport2C::SetPropertyDRMState(const Brx& aValue)
{
    ASSERT(iPropertyDRMState != NULL);
    return SetPropertyString(*iPropertyDRMState, aValue);
}

void DvProviderUpnpOrgAVTransport2C::GetPropertyDRMState(Brhz& aValue)
{
    ASSERT(iPropertyDRMState != NULL);
    aValue.Set(iPropertyDRMState->Value());
}

void DvProviderUpnpOrgAVTransport2C::EnablePropertyLastChange()
{
    iPropertyLastChange = new PropertyString(iDvStack.Env(), new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgAVTransport2C::EnablePropertyDRMState()
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

void DvProviderUpnpOrgAVTransport2C::EnableActionSetAVTransportURI(CallbackAVTransport2SetAVTransportURI aCallback, void* aPtr)
{
    iCallbackSetAVTransportURI = aCallback;
    iPtrSetAVTransportURI = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetAVTransportURI");
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
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetNextAVTransportURI");
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetMediaInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetMediaInfo_Ext(CallbackAVTransport2GetMediaInfo_Ext aCallback, void* aPtr)
{
    iCallbackGetMediaInfo_Ext = aCallback;
    iPtrGetMediaInfo_Ext = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetMediaInfo_Ext);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetTransportInfo(CallbackAVTransport2GetTransportInfo aCallback, void* aPtr)
{
    iCallbackGetTransportInfo = aCallback;
    iPtrGetTransportInfo = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetTransportInfo");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("CurrentTransportState"));
    action->AddOutputParameter(new ParameterString("CurrentTransportStatus"));
    action->AddOutputParameter(new ParameterString("CurrentSpeed"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetTransportInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetPositionInfo(CallbackAVTransport2GetPositionInfo aCallback, void* aPtr)
{
    iCallbackGetPositionInfo = aCallback;
    iPtrGetPositionInfo = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetPositionInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetDeviceCapabilities(CallbackAVTransport2GetDeviceCapabilities aCallback, void* aPtr)
{
    iCallbackGetDeviceCapabilities = aCallback;
    iPtrGetDeviceCapabilities = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetDeviceCapabilities");
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetTransportSettings);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionStop(CallbackAVTransport2Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionPlay(CallbackAVTransport2Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Speed"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionPause(CallbackAVTransport2Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Pause");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionRecord(CallbackAVTransport2Record aCallback, void* aPtr)
{
    iCallbackRecord = aCallback;
    iPtrRecord = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Record");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoRecord);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSeek(CallbackAVTransport2Seek aCallback, void* aPtr)
{
    iCallbackSeek = aCallback;
    iPtrSeek = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoSeek);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionNext(CallbackAVTransport2Next aCallback, void* aPtr)
{
    iCallbackNext = aCallback;
    iPtrNext = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Next");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoNext);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionPrevious(CallbackAVTransport2Previous aCallback, void* aPtr)
{
    iCallbackPrevious = aCallback;
    iPtrPrevious = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Previous");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoPrevious);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSetPlayMode(CallbackAVTransport2SetPlayMode aCallback, void* aPtr)
{
    iCallbackSetPlayMode = aCallback;
    iPtrSetPlayMode = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoSetPlayMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSetRecordQualityMode(CallbackAVTransport2SetRecordQualityMode aCallback, void* aPtr)
{
    iCallbackSetRecordQualityMode = aCallback;
    iPtrSetRecordQualityMode = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRecordQualityMode");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("NewRecordQualityMode"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoSetRecordQualityMode);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetCurrentTransportActions(CallbackAVTransport2GetCurrentTransportActions aCallback, void* aPtr)
{
    iCallbackGetCurrentTransportActions = aCallback;
    iPtrGetCurrentTransportActions = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetCurrentTransportActions");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("Actions"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetCurrentTransportActions);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetDRMState(CallbackAVTransport2GetDRMState aCallback, void* aPtr)
{
    iCallbackGetDRMState = aCallback;
    iPtrGetDRMState = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetDRMState");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterRelated("CurrentDRMState", *iPropertyDRMState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoGetDRMState);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetStateVariables(CallbackAVTransport2GetStateVariables aCallback, void* aPtr)
{
    iCallbackGetStateVariables = aCallback;
    iPtrGetStateVariables = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStateVariables");
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
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("AVTransportUDN"));
    action->AddInputParameter(new ParameterString("ServiceType"));
    action->AddInputParameter(new ParameterString("ServiceId"));
    action->AddInputParameter(new ParameterString("StateVariableValuePairs"));
    action->AddOutputParameter(new ParameterString("StateVariableList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport2C::DoSetStateVariables);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport2C::DoSetAVTransportURI(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz CurrentURI;
    aInvocation.InvocationReadString("CurrentURI", CurrentURI);
    Brhz CurrentURIMetaData;
    aInvocation.InvocationReadString("CurrentURIMetaData", CurrentURIMetaData);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetAVTransportURI != NULL);
    if (0 != iCallbackSetAVTransportURI(iPtrSetAVTransportURI, invocationC, invocationCPtr, InstanceID, (const char*)CurrentURI.Ptr(), (const char*)CurrentURIMetaData.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoSetNextAVTransportURI(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz NextURI;
    aInvocation.InvocationReadString("NextURI", NextURI);
    Brhz NextURIMetaData;
    aInvocation.InvocationReadString("NextURIMetaData", NextURIMetaData);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetNextAVTransportURI != NULL);
    if (0 != iCallbackSetNextAVTransportURI(iPtrSetNextAVTransportURI, invocationC, invocationCPtr, InstanceID, (const char*)NextURI.Ptr(), (const char*)NextURIMetaData.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoGetMediaInfo(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
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
    if (0 != iCallbackGetMediaInfo(iPtrGetMediaInfo, invocationC, invocationCPtr, InstanceID, &NrTracks, &MediaDuration, &CurrentURI, &CurrentURIMetaData, &NextURI, &NextURIMetaData, &PlayMedium, &RecordMedium, &WriteStatus)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respNrTracks(aInvocation, "NrTracks");
    DviInvocationResponseString respMediaDuration(aInvocation, "MediaDuration");
    DviInvocationResponseString respCurrentURI(aInvocation, "CurrentURI");
    DviInvocationResponseString respCurrentURIMetaData(aInvocation, "CurrentURIMetaData");
    DviInvocationResponseString respNextURI(aInvocation, "NextURI");
    DviInvocationResponseString respNextURIMetaData(aInvocation, "NextURIMetaData");
    DviInvocationResponseString respPlayMedium(aInvocation, "PlayMedium");
    DviInvocationResponseString respRecordMedium(aInvocation, "RecordMedium");
    DviInvocationResponseString respWriteStatus(aInvocation, "WriteStatus");
    invocation.StartResponse();
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
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoGetMediaInfo_Ext(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
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
    if (0 != iCallbackGetMediaInfo_Ext(iPtrGetMediaInfo_Ext, invocationC, invocationCPtr, InstanceID, &CurrentType, &NrTracks, &MediaDuration, &CurrentURI, &CurrentURIMetaData, &NextURI, &NextURIMetaData, &PlayMedium, &RecordMedium, &WriteStatus)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
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
    invocation.StartResponse();
    Brhz bufCurrentType((const TChar*)CurrentType);
    OhNetFreeExternal(CurrentType);
    respCurrentType.Write(bufCurrentType);
    respCurrentType.WriteFlush();
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
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoGetTransportInfo(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* CurrentTransportState;
    char* CurrentTransportStatus;
    char* CurrentSpeed;
    ASSERT(iCallbackGetTransportInfo != NULL);
    if (0 != iCallbackGetTransportInfo(iPtrGetTransportInfo, invocationC, invocationCPtr, InstanceID, &CurrentTransportState, &CurrentTransportStatus, &CurrentSpeed)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respCurrentTransportState(aInvocation, "CurrentTransportState");
    DviInvocationResponseString respCurrentTransportStatus(aInvocation, "CurrentTransportStatus");
    DviInvocationResponseString respCurrentSpeed(aInvocation, "CurrentSpeed");
    invocation.StartResponse();
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
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoGetPositionInfo(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Track;
    char* TrackDuration;
    char* TrackMetaData;
    char* TrackURI;
    char* RelTime;
    char* AbsTime;
    int32_t RelCount;
    int32_t AbsCount;
    ASSERT(iCallbackGetPositionInfo != NULL);
    if (0 != iCallbackGetPositionInfo(iPtrGetPositionInfo, invocationC, invocationCPtr, InstanceID, &Track, &TrackDuration, &TrackMetaData, &TrackURI, &RelTime, &AbsTime, &RelCount, &AbsCount)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respTrack(aInvocation, "Track");
    DviInvocationResponseString respTrackDuration(aInvocation, "TrackDuration");
    DviInvocationResponseString respTrackMetaData(aInvocation, "TrackMetaData");
    DviInvocationResponseString respTrackURI(aInvocation, "TrackURI");
    DviInvocationResponseString respRelTime(aInvocation, "RelTime");
    DviInvocationResponseString respAbsTime(aInvocation, "AbsTime");
    DviInvocationResponseInt respRelCount(aInvocation, "RelCount");
    DviInvocationResponseInt respAbsCount(aInvocation, "AbsCount");
    invocation.StartResponse();
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
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoGetDeviceCapabilities(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* PlayMedia;
    char* RecMedia;
    char* RecQualityModes;
    ASSERT(iCallbackGetDeviceCapabilities != NULL);
    if (0 != iCallbackGetDeviceCapabilities(iPtrGetDeviceCapabilities, invocationC, invocationCPtr, InstanceID, &PlayMedia, &RecMedia, &RecQualityModes)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respPlayMedia(aInvocation, "PlayMedia");
    DviInvocationResponseString respRecMedia(aInvocation, "RecMedia");
    DviInvocationResponseString respRecQualityModes(aInvocation, "RecQualityModes");
    invocation.StartResponse();
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
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoGetTransportSettings(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* PlayMode;
    char* RecQualityMode;
    ASSERT(iCallbackGetTransportSettings != NULL);
    if (0 != iCallbackGetTransportSettings(iPtrGetTransportSettings, invocationC, invocationCPtr, InstanceID, &PlayMode, &RecQualityMode)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respPlayMode(aInvocation, "PlayMode");
    DviInvocationResponseString respRecQualityMode(aInvocation, "RecQualityMode");
    invocation.StartResponse();
    Brhz bufPlayMode((const TChar*)PlayMode);
    OhNetFreeExternal(PlayMode);
    respPlayMode.Write(bufPlayMode);
    respPlayMode.WriteFlush();
    Brhz bufRecQualityMode((const TChar*)RecQualityMode);
    OhNetFreeExternal(RecQualityMode);
    respRecQualityMode.Write(bufRecQualityMode);
    respRecQualityMode.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoStop(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, invocationC, invocationCPtr, InstanceID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoPlay(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Speed;
    aInvocation.InvocationReadString("Speed", Speed);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, invocationC, invocationCPtr, InstanceID, (const char*)Speed.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoPause(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackPause != NULL);
    if (0 != iCallbackPause(iPtrPause, invocationC, invocationCPtr, InstanceID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoRecord(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackRecord != NULL);
    if (0 != iCallbackRecord(iPtrRecord, invocationC, invocationCPtr, InstanceID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoSeek(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Unit;
    aInvocation.InvocationReadString("Unit", Unit);
    Brhz Target;
    aInvocation.InvocationReadString("Target", Target);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSeek != NULL);
    if (0 != iCallbackSeek(iPtrSeek, invocationC, invocationCPtr, InstanceID, (const char*)Unit.Ptr(), (const char*)Target.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoNext(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackNext != NULL);
    if (0 != iCallbackNext(iPtrNext, invocationC, invocationCPtr, InstanceID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoPrevious(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackPrevious != NULL);
    if (0 != iCallbackPrevious(iPtrPrevious, invocationC, invocationCPtr, InstanceID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoSetPlayMode(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz NewPlayMode;
    aInvocation.InvocationReadString("NewPlayMode", NewPlayMode);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetPlayMode != NULL);
    if (0 != iCallbackSetPlayMode(iPtrSetPlayMode, invocationC, invocationCPtr, InstanceID, (const char*)NewPlayMode.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoSetRecordQualityMode(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz NewRecordQualityMode;
    aInvocation.InvocationReadString("NewRecordQualityMode", NewRecordQualityMode);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetRecordQualityMode != NULL);
    if (0 != iCallbackSetRecordQualityMode(iPtrSetRecordQualityMode, invocationC, invocationCPtr, InstanceID, (const char*)NewRecordQualityMode.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoGetCurrentTransportActions(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Actions;
    ASSERT(iCallbackGetCurrentTransportActions != NULL);
    if (0 != iCallbackGetCurrentTransportActions(iPtrGetCurrentTransportActions, invocationC, invocationCPtr, InstanceID, &Actions)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respActions(aInvocation, "Actions");
    invocation.StartResponse();
    Brhz bufActions((const TChar*)Actions);
    OhNetFreeExternal(Actions);
    respActions.Write(bufActions);
    respActions.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoGetDRMState(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* CurrentDRMState;
    ASSERT(iCallbackGetDRMState != NULL);
    if (0 != iCallbackGetDRMState(iPtrGetDRMState, invocationC, invocationCPtr, InstanceID, &CurrentDRMState)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respCurrentDRMState(aInvocation, "CurrentDRMState");
    invocation.StartResponse();
    Brhz bufCurrentDRMState((const TChar*)CurrentDRMState);
    OhNetFreeExternal(CurrentDRMState);
    respCurrentDRMState.Write(bufCurrentDRMState);
    respCurrentDRMState.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoGetStateVariables(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz StateVariableList;
    aInvocation.InvocationReadString("StateVariableList", StateVariableList);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* StateVariableValuePairs;
    ASSERT(iCallbackGetStateVariables != NULL);
    if (0 != iCallbackGetStateVariables(iPtrGetStateVariables, invocationC, invocationCPtr, InstanceID, (const char*)StateVariableList.Ptr(), &StateVariableValuePairs)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respStateVariableValuePairs(aInvocation, "StateVariableValuePairs");
    invocation.StartResponse();
    Brhz bufStateVariableValuePairs((const TChar*)StateVariableValuePairs);
    OhNetFreeExternal(StateVariableValuePairs);
    respStateVariableValuePairs.Write(bufStateVariableValuePairs);
    respStateVariableValuePairs.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgAVTransport2C::DoSetStateVariables(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
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
    char* StateVariableList;
    ASSERT(iCallbackSetStateVariables != NULL);
    if (0 != iCallbackSetStateVariables(iPtrSetStateVariables, invocationC, invocationCPtr, InstanceID, (const char*)AVTransportUDN.Ptr(), (const char*)ServiceType.Ptr(), (const char*)ServiceId.Ptr(), (const char*)StateVariableValuePairs.Ptr(), &StateVariableList)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respStateVariableList(aInvocation, "StateVariableList");
    invocation.StartResponse();
    Brhz bufStateVariableList((const TChar*)StateVariableList);
    OhNetFreeExternal(StateVariableList);
    respStateVariableList.Write(bufStateVariableList);
    respStateVariableList.WriteFlush();
    invocation.EndResponse();
}



THandle STDCALL DvProviderUpnpOrgAVTransport2Create(DvDeviceC aDevice)
{
    return new DvProviderUpnpOrgAVTransport2C(aDevice);
}

void STDCALL DvProviderUpnpOrgAVTransport2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionSetAVTransportURI(THandle aProvider, CallbackAVTransport2SetAVTransportURI aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionSetAVTransportURI(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionSetNextAVTransportURI(THandle aProvider, CallbackAVTransport2SetNextAVTransportURI aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionSetNextAVTransportURI(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetMediaInfo(THandle aProvider, CallbackAVTransport2GetMediaInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetMediaInfo(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetMediaInfo_Ext(THandle aProvider, CallbackAVTransport2GetMediaInfo_Ext aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetMediaInfo_Ext(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetTransportInfo(THandle aProvider, CallbackAVTransport2GetTransportInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetTransportInfo(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetPositionInfo(THandle aProvider, CallbackAVTransport2GetPositionInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetPositionInfo(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetDeviceCapabilities(THandle aProvider, CallbackAVTransport2GetDeviceCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetDeviceCapabilities(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetTransportSettings(THandle aProvider, CallbackAVTransport2GetTransportSettings aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetTransportSettings(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionStop(THandle aProvider, CallbackAVTransport2Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionStop(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionPlay(THandle aProvider, CallbackAVTransport2Play aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionPlay(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionPause(THandle aProvider, CallbackAVTransport2Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionPause(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionRecord(THandle aProvider, CallbackAVTransport2Record aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionRecord(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionSeek(THandle aProvider, CallbackAVTransport2Seek aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionSeek(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionNext(THandle aProvider, CallbackAVTransport2Next aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionNext(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionPrevious(THandle aProvider, CallbackAVTransport2Previous aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionPrevious(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionSetPlayMode(THandle aProvider, CallbackAVTransport2SetPlayMode aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionSetPlayMode(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionSetRecordQualityMode(THandle aProvider, CallbackAVTransport2SetRecordQualityMode aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionSetRecordQualityMode(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetCurrentTransportActions(THandle aProvider, CallbackAVTransport2GetCurrentTransportActions aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetCurrentTransportActions(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetDRMState(THandle aProvider, CallbackAVTransport2GetDRMState aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetDRMState(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetStateVariables(THandle aProvider, CallbackAVTransport2GetStateVariables aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionGetStateVariables(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport2EnableActionSetStateVariables(THandle aProvider, CallbackAVTransport2SetStateVariables aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnableActionSetStateVariables(aCallback, aPtr);
}

int32_t STDCALL DvProviderUpnpOrgAVTransport2SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->SetPropertyLastChange(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgAVTransport2GetPropertyLastChange(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderUpnpOrgAVTransport2SetPropertyDRMState(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->SetPropertyDRMState(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgAVTransport2GetPropertyDRMState(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->GetPropertyDRMState(buf);
    *aValue = (char*)buf.Transfer();
}

void STDCALL DvProviderUpnpOrgAVTransport2EnablePropertyLastChange(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnablePropertyLastChange();
}

void STDCALL DvProviderUpnpOrgAVTransport2EnablePropertyDRMState(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport2C*>(aProvider)->EnablePropertyDRMState();
}

