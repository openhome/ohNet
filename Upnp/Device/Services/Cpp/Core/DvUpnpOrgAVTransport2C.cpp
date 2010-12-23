#include "DvUpnpOrgAVTransport2C.h"
#include "DvUpnpOrgAVTransport2.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderUpnpOrgAVTransport2C : public DvProviderUpnpOrgAVTransport2
{
public:
    DvProviderUpnpOrgAVTransport2C(DvDevice& aDevice);
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
    void SetAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData);
    void SetNextAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData);
    void GetMediaInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aNrTracks, IInvocationResponseString& aMediaDuration, IInvocationResponseString& aCurrentURI, IInvocationResponseString& aCurrentURIMetaData, IInvocationResponseString& aNextURI, IInvocationResponseString& aNextURIMetaData, IInvocationResponseString& aPlayMedium, IInvocationResponseString& aRecordMedium, IInvocationResponseString& aWriteStatus);
    void GetMediaInfo_Ext(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentType, IInvocationResponseUint& aNrTracks, IInvocationResponseString& aMediaDuration, IInvocationResponseString& aCurrentURI, IInvocationResponseString& aCurrentURIMetaData, IInvocationResponseString& aNextURI, IInvocationResponseString& aNextURIMetaData, IInvocationResponseString& aPlayMedium, IInvocationResponseString& aRecordMedium, IInvocationResponseString& aWriteStatus);
    void GetTransportInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentTransportState, IInvocationResponseString& aCurrentTransportStatus, IInvocationResponseString& aCurrentSpeed);
    void GetPositionInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aTrack, IInvocationResponseString& aTrackDuration, IInvocationResponseString& aTrackMetaData, IInvocationResponseString& aTrackURI, IInvocationResponseString& aRelTime, IInvocationResponseString& aAbsTime, IInvocationResponseInt& aRelCount, IInvocationResponseInt& aAbsCount);
    void GetDeviceCapabilities(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aPlayMedia, IInvocationResponseString& aRecMedia, IInvocationResponseString& aRecQualityModes);
    void GetTransportSettings(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aPlayMode, IInvocationResponseString& aRecQualityMode);
    void Stop(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    void Play(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aSpeed);
    void Pause(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    void Record(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    void Seek(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aUnit, const Brx& aTarget);
    void Next(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    void Previous(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID);
    void SetPlayMode(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNewPlayMode);
    void SetRecordQualityMode(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNewRecordQualityMode);
    void GetCurrentTransportActions(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aActions);
    void GetDRMState(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentDRMState);
    void GetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aStateVariableList, IInvocationResponseString& aStateVariableValuePairs);
    void SetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aAVTransportUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, IInvocationResponseString& aStateVariableList);
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
};

DvProviderUpnpOrgAVTransport2C::DvProviderUpnpOrgAVTransport2C(DvDevice& aDevice)
    : DvProviderUpnpOrgAVTransport2(aDevice)
{
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSetAVTransportURI(CallbackAVTransport2SetAVTransportURI aCallback, void* aPtr)
{
    iCallbackSetAVTransportURI = aCallback;
    iPtrSetAVTransportURI = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionSetAVTransportURI();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSetNextAVTransportURI(CallbackAVTransport2SetNextAVTransportURI aCallback, void* aPtr)
{
    iCallbackSetNextAVTransportURI = aCallback;
    iPtrSetNextAVTransportURI = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionSetNextAVTransportURI();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetMediaInfo(CallbackAVTransport2GetMediaInfo aCallback, void* aPtr)
{
    iCallbackGetMediaInfo = aCallback;
    iPtrGetMediaInfo = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionGetMediaInfo();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetMediaInfo_Ext(CallbackAVTransport2GetMediaInfo_Ext aCallback, void* aPtr)
{
    iCallbackGetMediaInfo_Ext = aCallback;
    iPtrGetMediaInfo_Ext = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionGetMediaInfo_Ext();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetTransportInfo(CallbackAVTransport2GetTransportInfo aCallback, void* aPtr)
{
    iCallbackGetTransportInfo = aCallback;
    iPtrGetTransportInfo = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionGetTransportInfo();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetPositionInfo(CallbackAVTransport2GetPositionInfo aCallback, void* aPtr)
{
    iCallbackGetPositionInfo = aCallback;
    iPtrGetPositionInfo = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionGetPositionInfo();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetDeviceCapabilities(CallbackAVTransport2GetDeviceCapabilities aCallback, void* aPtr)
{
    iCallbackGetDeviceCapabilities = aCallback;
    iPtrGetDeviceCapabilities = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionGetDeviceCapabilities();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetTransportSettings(CallbackAVTransport2GetTransportSettings aCallback, void* aPtr)
{
    iCallbackGetTransportSettings = aCallback;
    iPtrGetTransportSettings = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionGetTransportSettings();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionStop(CallbackAVTransport2Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionStop();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionPlay(CallbackAVTransport2Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionPlay();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionPause(CallbackAVTransport2Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionPause();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionRecord(CallbackAVTransport2Record aCallback, void* aPtr)
{
    iCallbackRecord = aCallback;
    iPtrRecord = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionRecord();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSeek(CallbackAVTransport2Seek aCallback, void* aPtr)
{
    iCallbackSeek = aCallback;
    iPtrSeek = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionSeek();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionNext(CallbackAVTransport2Next aCallback, void* aPtr)
{
    iCallbackNext = aCallback;
    iPtrNext = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionNext();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionPrevious(CallbackAVTransport2Previous aCallback, void* aPtr)
{
    iCallbackPrevious = aCallback;
    iPtrPrevious = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionPrevious();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSetPlayMode(CallbackAVTransport2SetPlayMode aCallback, void* aPtr)
{
    iCallbackSetPlayMode = aCallback;
    iPtrSetPlayMode = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionSetPlayMode();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSetRecordQualityMode(CallbackAVTransport2SetRecordQualityMode aCallback, void* aPtr)
{
    iCallbackSetRecordQualityMode = aCallback;
    iPtrSetRecordQualityMode = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionSetRecordQualityMode();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetCurrentTransportActions(CallbackAVTransport2GetCurrentTransportActions aCallback, void* aPtr)
{
    iCallbackGetCurrentTransportActions = aCallback;
    iPtrGetCurrentTransportActions = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionGetCurrentTransportActions();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetDRMState(CallbackAVTransport2GetDRMState aCallback, void* aPtr)
{
    iCallbackGetDRMState = aCallback;
    iPtrGetDRMState = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionGetDRMState();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionGetStateVariables(CallbackAVTransport2GetStateVariables aCallback, void* aPtr)
{
    iCallbackGetStateVariables = aCallback;
    iPtrGetStateVariables = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionGetStateVariables();
}

void DvProviderUpnpOrgAVTransport2C::EnableActionSetStateVariables(CallbackAVTransport2SetStateVariables aCallback, void* aPtr)
{
    iCallbackSetStateVariables = aCallback;
    iPtrSetStateVariables = aPtr;
    DvProviderUpnpOrgAVTransport2::EnableActionSetStateVariables();
}

void DvProviderUpnpOrgAVTransport2C::SetAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData)
{
    ASSERT(iCallbackSetAVTransportURI != NULL);
    if (0 != iCallbackSetAVTransportURI(iPtrSetAVTransportURI, aVersion, aInstanceID, (const char*)aCurrentURI.Ptr(), (const char*)aCurrentURIMetaData.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::SetNextAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData)
{
    ASSERT(iCallbackSetNextAVTransportURI != NULL);
    if (0 != iCallbackSetNextAVTransportURI(iPtrSetNextAVTransportURI, aVersion, aInstanceID, (const char*)aNextURI.Ptr(), (const char*)aNextURIMetaData.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::GetMediaInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aNrTracks, IInvocationResponseString& aMediaDuration, IInvocationResponseString& aCurrentURI, IInvocationResponseString& aCurrentURIMetaData, IInvocationResponseString& aNextURI, IInvocationResponseString& aNextURIMetaData, IInvocationResponseString& aPlayMedium, IInvocationResponseString& aRecordMedium, IInvocationResponseString& aWriteStatus)
{
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
    if (0 != iCallbackGetMediaInfo(iPtrGetMediaInfo, aVersion, aInstanceID, &NrTracks, &MediaDuration, &CurrentURI, &CurrentURIMetaData, &NextURI, &NextURIMetaData, &PlayMedium, &RecordMedium, &WriteStatus)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aNrTracks.Write(NrTracks);
    Brhz bufMediaDuration((const TChar*)MediaDuration);
    ZappFreeExternal(MediaDuration);
    aMediaDuration.Write(bufMediaDuration);
    aMediaDuration.WriteFlush();
    Brhz bufCurrentURI((const TChar*)CurrentURI);
    ZappFreeExternal(CurrentURI);
    aCurrentURI.Write(bufCurrentURI);
    aCurrentURI.WriteFlush();
    Brhz bufCurrentURIMetaData((const TChar*)CurrentURIMetaData);
    ZappFreeExternal(CurrentURIMetaData);
    aCurrentURIMetaData.Write(bufCurrentURIMetaData);
    aCurrentURIMetaData.WriteFlush();
    Brhz bufNextURI((const TChar*)NextURI);
    ZappFreeExternal(NextURI);
    aNextURI.Write(bufNextURI);
    aNextURI.WriteFlush();
    Brhz bufNextURIMetaData((const TChar*)NextURIMetaData);
    ZappFreeExternal(NextURIMetaData);
    aNextURIMetaData.Write(bufNextURIMetaData);
    aNextURIMetaData.WriteFlush();
    Brhz bufPlayMedium((const TChar*)PlayMedium);
    ZappFreeExternal(PlayMedium);
    aPlayMedium.Write(bufPlayMedium);
    aPlayMedium.WriteFlush();
    Brhz bufRecordMedium((const TChar*)RecordMedium);
    ZappFreeExternal(RecordMedium);
    aRecordMedium.Write(bufRecordMedium);
    aRecordMedium.WriteFlush();
    Brhz bufWriteStatus((const TChar*)WriteStatus);
    ZappFreeExternal(WriteStatus);
    aWriteStatus.Write(bufWriteStatus);
    aWriteStatus.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::GetMediaInfo_Ext(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentType, IInvocationResponseUint& aNrTracks, IInvocationResponseString& aMediaDuration, IInvocationResponseString& aCurrentURI, IInvocationResponseString& aCurrentURIMetaData, IInvocationResponseString& aNextURI, IInvocationResponseString& aNextURIMetaData, IInvocationResponseString& aPlayMedium, IInvocationResponseString& aRecordMedium, IInvocationResponseString& aWriteStatus)
{
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
    if (0 != iCallbackGetMediaInfo_Ext(iPtrGetMediaInfo_Ext, aVersion, aInstanceID, &CurrentType, &NrTracks, &MediaDuration, &CurrentURI, &CurrentURIMetaData, &NextURI, &NextURIMetaData, &PlayMedium, &RecordMedium, &WriteStatus)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufCurrentType((const TChar*)CurrentType);
    ZappFreeExternal(CurrentType);
    aCurrentType.Write(bufCurrentType);
    aCurrentType.WriteFlush();
    aNrTracks.Write(NrTracks);
    Brhz bufMediaDuration((const TChar*)MediaDuration);
    ZappFreeExternal(MediaDuration);
    aMediaDuration.Write(bufMediaDuration);
    aMediaDuration.WriteFlush();
    Brhz bufCurrentURI((const TChar*)CurrentURI);
    ZappFreeExternal(CurrentURI);
    aCurrentURI.Write(bufCurrentURI);
    aCurrentURI.WriteFlush();
    Brhz bufCurrentURIMetaData((const TChar*)CurrentURIMetaData);
    ZappFreeExternal(CurrentURIMetaData);
    aCurrentURIMetaData.Write(bufCurrentURIMetaData);
    aCurrentURIMetaData.WriteFlush();
    Brhz bufNextURI((const TChar*)NextURI);
    ZappFreeExternal(NextURI);
    aNextURI.Write(bufNextURI);
    aNextURI.WriteFlush();
    Brhz bufNextURIMetaData((const TChar*)NextURIMetaData);
    ZappFreeExternal(NextURIMetaData);
    aNextURIMetaData.Write(bufNextURIMetaData);
    aNextURIMetaData.WriteFlush();
    Brhz bufPlayMedium((const TChar*)PlayMedium);
    ZappFreeExternal(PlayMedium);
    aPlayMedium.Write(bufPlayMedium);
    aPlayMedium.WriteFlush();
    Brhz bufRecordMedium((const TChar*)RecordMedium);
    ZappFreeExternal(RecordMedium);
    aRecordMedium.Write(bufRecordMedium);
    aRecordMedium.WriteFlush();
    Brhz bufWriteStatus((const TChar*)WriteStatus);
    ZappFreeExternal(WriteStatus);
    aWriteStatus.Write(bufWriteStatus);
    aWriteStatus.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::GetTransportInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentTransportState, IInvocationResponseString& aCurrentTransportStatus, IInvocationResponseString& aCurrentSpeed)
{
    char* CurrentTransportState;
    char* CurrentTransportStatus;
    char* CurrentSpeed;
    ASSERT(iCallbackGetTransportInfo != NULL);
    if (0 != iCallbackGetTransportInfo(iPtrGetTransportInfo, aVersion, aInstanceID, &CurrentTransportState, &CurrentTransportStatus, &CurrentSpeed)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufCurrentTransportState((const TChar*)CurrentTransportState);
    ZappFreeExternal(CurrentTransportState);
    aCurrentTransportState.Write(bufCurrentTransportState);
    aCurrentTransportState.WriteFlush();
    Brhz bufCurrentTransportStatus((const TChar*)CurrentTransportStatus);
    ZappFreeExternal(CurrentTransportStatus);
    aCurrentTransportStatus.Write(bufCurrentTransportStatus);
    aCurrentTransportStatus.WriteFlush();
    Brhz bufCurrentSpeed((const TChar*)CurrentSpeed);
    ZappFreeExternal(CurrentSpeed);
    aCurrentSpeed.Write(bufCurrentSpeed);
    aCurrentSpeed.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::GetPositionInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aTrack, IInvocationResponseString& aTrackDuration, IInvocationResponseString& aTrackMetaData, IInvocationResponseString& aTrackURI, IInvocationResponseString& aRelTime, IInvocationResponseString& aAbsTime, IInvocationResponseInt& aRelCount, IInvocationResponseInt& aAbsCount)
{
    uint32_t Track;
    char* TrackDuration;
    char* TrackMetaData;
    char* TrackURI;
    char* RelTime;
    char* AbsTime;
    int32_t RelCount;
    int32_t AbsCount;
    ASSERT(iCallbackGetPositionInfo != NULL);
    if (0 != iCallbackGetPositionInfo(iPtrGetPositionInfo, aVersion, aInstanceID, &Track, &TrackDuration, &TrackMetaData, &TrackURI, &RelTime, &AbsTime, &RelCount, &AbsCount)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aTrack.Write(Track);
    Brhz bufTrackDuration((const TChar*)TrackDuration);
    ZappFreeExternal(TrackDuration);
    aTrackDuration.Write(bufTrackDuration);
    aTrackDuration.WriteFlush();
    Brhz bufTrackMetaData((const TChar*)TrackMetaData);
    ZappFreeExternal(TrackMetaData);
    aTrackMetaData.Write(bufTrackMetaData);
    aTrackMetaData.WriteFlush();
    Brhz bufTrackURI((const TChar*)TrackURI);
    ZappFreeExternal(TrackURI);
    aTrackURI.Write(bufTrackURI);
    aTrackURI.WriteFlush();
    Brhz bufRelTime((const TChar*)RelTime);
    ZappFreeExternal(RelTime);
    aRelTime.Write(bufRelTime);
    aRelTime.WriteFlush();
    Brhz bufAbsTime((const TChar*)AbsTime);
    ZappFreeExternal(AbsTime);
    aAbsTime.Write(bufAbsTime);
    aAbsTime.WriteFlush();
    aRelCount.Write(RelCount);
    aAbsCount.Write(AbsCount);
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::GetDeviceCapabilities(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aPlayMedia, IInvocationResponseString& aRecMedia, IInvocationResponseString& aRecQualityModes)
{
    char* PlayMedia;
    char* RecMedia;
    char* RecQualityModes;
    ASSERT(iCallbackGetDeviceCapabilities != NULL);
    if (0 != iCallbackGetDeviceCapabilities(iPtrGetDeviceCapabilities, aVersion, aInstanceID, &PlayMedia, &RecMedia, &RecQualityModes)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufPlayMedia((const TChar*)PlayMedia);
    ZappFreeExternal(PlayMedia);
    aPlayMedia.Write(bufPlayMedia);
    aPlayMedia.WriteFlush();
    Brhz bufRecMedia((const TChar*)RecMedia);
    ZappFreeExternal(RecMedia);
    aRecMedia.Write(bufRecMedia);
    aRecMedia.WriteFlush();
    Brhz bufRecQualityModes((const TChar*)RecQualityModes);
    ZappFreeExternal(RecQualityModes);
    aRecQualityModes.Write(bufRecQualityModes);
    aRecQualityModes.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::GetTransportSettings(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aPlayMode, IInvocationResponseString& aRecQualityMode)
{
    char* PlayMode;
    char* RecQualityMode;
    ASSERT(iCallbackGetTransportSettings != NULL);
    if (0 != iCallbackGetTransportSettings(iPtrGetTransportSettings, aVersion, aInstanceID, &PlayMode, &RecQualityMode)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufPlayMode((const TChar*)PlayMode);
    ZappFreeExternal(PlayMode);
    aPlayMode.Write(bufPlayMode);
    aPlayMode.WriteFlush();
    Brhz bufRecQualityMode((const TChar*)RecQualityMode);
    ZappFreeExternal(RecQualityMode);
    aRecQualityMode.Write(bufRecQualityMode);
    aRecQualityMode.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::Stop(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::Play(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aSpeed)
{
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, aVersion, aInstanceID, (const char*)aSpeed.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::Pause(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackPause != NULL);
    if (0 != iCallbackPause(iPtrPause, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::Record(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackRecord != NULL);
    if (0 != iCallbackRecord(iPtrRecord, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::Seek(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aUnit, const Brx& aTarget)
{
    ASSERT(iCallbackSeek != NULL);
    if (0 != iCallbackSeek(iPtrSeek, aVersion, aInstanceID, (const char*)aUnit.Ptr(), (const char*)aTarget.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::Next(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackNext != NULL);
    if (0 != iCallbackNext(iPtrNext, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::Previous(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackPrevious != NULL);
    if (0 != iCallbackPrevious(iPtrPrevious, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::SetPlayMode(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNewPlayMode)
{
    ASSERT(iCallbackSetPlayMode != NULL);
    if (0 != iCallbackSetPlayMode(iPtrSetPlayMode, aVersion, aInstanceID, (const char*)aNewPlayMode.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::SetRecordQualityMode(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNewRecordQualityMode)
{
    ASSERT(iCallbackSetRecordQualityMode != NULL);
    if (0 != iCallbackSetRecordQualityMode(iPtrSetRecordQualityMode, aVersion, aInstanceID, (const char*)aNewRecordQualityMode.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::GetCurrentTransportActions(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aActions)
{
    char* Actions;
    ASSERT(iCallbackGetCurrentTransportActions != NULL);
    if (0 != iCallbackGetCurrentTransportActions(iPtrGetCurrentTransportActions, aVersion, aInstanceID, &Actions)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufActions((const TChar*)Actions);
    ZappFreeExternal(Actions);
    aActions.Write(bufActions);
    aActions.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::GetDRMState(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentDRMState)
{
    char* CurrentDRMState;
    ASSERT(iCallbackGetDRMState != NULL);
    if (0 != iCallbackGetDRMState(iPtrGetDRMState, aVersion, aInstanceID, &CurrentDRMState)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufCurrentDRMState((const TChar*)CurrentDRMState);
    ZappFreeExternal(CurrentDRMState);
    aCurrentDRMState.Write(bufCurrentDRMState);
    aCurrentDRMState.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::GetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aStateVariableList, IInvocationResponseString& aStateVariableValuePairs)
{
    char* StateVariableValuePairs;
    ASSERT(iCallbackGetStateVariables != NULL);
    if (0 != iCallbackGetStateVariables(iPtrGetStateVariables, aVersion, aInstanceID, (const char*)aStateVariableList.Ptr(), &StateVariableValuePairs)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufStateVariableValuePairs((const TChar*)StateVariableValuePairs);
    ZappFreeExternal(StateVariableValuePairs);
    aStateVariableValuePairs.Write(bufStateVariableValuePairs);
    aStateVariableValuePairs.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport2C::SetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aAVTransportUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, IInvocationResponseString& aStateVariableList)
{
    char* StateVariableList;
    ASSERT(iCallbackSetStateVariables != NULL);
    if (0 != iCallbackSetStateVariables(iPtrSetStateVariables, aVersion, aInstanceID, (const char*)aAVTransportUDN.Ptr(), (const char*)aServiceType.Ptr(), (const char*)aServiceId.Ptr(), (const char*)aStateVariableValuePairs.Ptr(), &StateVariableList)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufStateVariableList((const TChar*)StateVariableList);
    ZappFreeExternal(StateVariableList);
    aStateVariableList.Write(bufStateVariableList);
    aStateVariableList.WriteFlush();
    aResponse.End();
}



THandle DvProviderUpnpOrgAVTransport2Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgAVTransport2C(*(DviDeviceC::DeviceFromHandle(aDevice)));
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

