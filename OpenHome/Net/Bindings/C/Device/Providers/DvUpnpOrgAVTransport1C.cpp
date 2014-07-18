#include "DvUpnpOrgAVTransport1.h"
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

class DvProviderUpnpOrgAVTransport1C : public DvProvider
{
public:
    DvProviderUpnpOrgAVTransport1C(DvDeviceC aDevice);
    TBool SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
    void EnablePropertyLastChange();
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
    void DoSetAVTransportURI(IDviInvocation& aInvocation);
    void DoSetNextAVTransportURI(IDviInvocation& aInvocation);
    void DoGetMediaInfo(IDviInvocation& aInvocation);
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
    iPropertyLastChange = NULL;
}

TBool DvProviderUpnpOrgAVTransport1C::SetPropertyLastChange(const Brx& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgAVTransport1C::GetPropertyLastChange(Brhz& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    aValue.Set(iPropertyLastChange->Value());
}

void DvProviderUpnpOrgAVTransport1C::EnablePropertyLastChange()
{
    iPropertyLastChange = new PropertyString(iDvStack.Env(), new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgAVTransport1C::DoGetTransportInfo);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgAVTransport1C::EnableActionGetPositionInfo(CallbackAVTransport1GetPositionInfo aCallback, void* aPtr)
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
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Speed"));
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

void DvProviderUpnpOrgAVTransport1C::DoSetAVTransportURI(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoSetNextAVTransportURI(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoGetMediaInfo(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoGetTransportInfo(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoGetPositionInfo(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoGetDeviceCapabilities(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoGetTransportSettings(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoStop(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoPlay(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoPause(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoRecord(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoSeek(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoNext(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoPrevious(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoSetPlayMode(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoSetRecordQualityMode(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgAVTransport1C::DoGetCurrentTransportActions(IDviInvocation& aInvocation)
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



THandle STDCALL DvProviderUpnpOrgAVTransport1Create(DvDeviceC aDevice)
{
    return new DvProviderUpnpOrgAVTransport1C(aDevice);
}

void STDCALL DvProviderUpnpOrgAVTransport1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionSetAVTransportURI(THandle aProvider, CallbackAVTransport1SetAVTransportURI aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionSetAVTransportURI(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionSetNextAVTransportURI(THandle aProvider, CallbackAVTransport1SetNextAVTransportURI aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionSetNextAVTransportURI(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionGetMediaInfo(THandle aProvider, CallbackAVTransport1GetMediaInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionGetMediaInfo(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionGetTransportInfo(THandle aProvider, CallbackAVTransport1GetTransportInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionGetTransportInfo(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionGetPositionInfo(THandle aProvider, CallbackAVTransport1GetPositionInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionGetPositionInfo(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionGetDeviceCapabilities(THandle aProvider, CallbackAVTransport1GetDeviceCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionGetDeviceCapabilities(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionGetTransportSettings(THandle aProvider, CallbackAVTransport1GetTransportSettings aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionGetTransportSettings(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionStop(THandle aProvider, CallbackAVTransport1Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionStop(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionPlay(THandle aProvider, CallbackAVTransport1Play aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionPlay(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionPause(THandle aProvider, CallbackAVTransport1Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionPause(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionRecord(THandle aProvider, CallbackAVTransport1Record aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionRecord(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionSeek(THandle aProvider, CallbackAVTransport1Seek aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionSeek(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionNext(THandle aProvider, CallbackAVTransport1Next aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionNext(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionPrevious(THandle aProvider, CallbackAVTransport1Previous aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionPrevious(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionSetPlayMode(THandle aProvider, CallbackAVTransport1SetPlayMode aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionSetPlayMode(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionSetRecordQualityMode(THandle aProvider, CallbackAVTransport1SetRecordQualityMode aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionSetRecordQualityMode(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgAVTransport1EnableActionGetCurrentTransportActions(THandle aProvider, CallbackAVTransport1GetCurrentTransportActions aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnableActionGetCurrentTransportActions(aCallback, aPtr);
}

int32_t STDCALL DvProviderUpnpOrgAVTransport1SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->SetPropertyLastChange(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgAVTransport1GetPropertyLastChange(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

void STDCALL DvProviderUpnpOrgAVTransport1EnablePropertyLastChange(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgAVTransport1C*>(aProvider)->EnablePropertyLastChange();
}

