#include <C/DvUpnpOrgAVTransport2.h>
#include <Core/DvUpnpOrgAVTransport2.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceUpnpOrgAVTransport2C : public DvServiceUpnpOrgAVTransport2
{
public:
    DvServiceUpnpOrgAVTransport2C(DvDevice& aDevice);
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

DvServiceUpnpOrgAVTransport2C::DvServiceUpnpOrgAVTransport2C(DvDevice& aDevice)
    : DvServiceUpnpOrgAVTransport2(aDevice)
{
}

void DvServiceUpnpOrgAVTransport2C::EnableActionSetAVTransportURI(CallbackAVTransport2SetAVTransportURI aCallback, void* aPtr)
{
    iCallbackSetAVTransportURI = aCallback;
    iPtrSetAVTransportURI = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionSetAVTransportURI();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionSetNextAVTransportURI(CallbackAVTransport2SetNextAVTransportURI aCallback, void* aPtr)
{
    iCallbackSetNextAVTransportURI = aCallback;
    iPtrSetNextAVTransportURI = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionSetNextAVTransportURI();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionGetMediaInfo(CallbackAVTransport2GetMediaInfo aCallback, void* aPtr)
{
    iCallbackGetMediaInfo = aCallback;
    iPtrGetMediaInfo = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionGetMediaInfo();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionGetMediaInfo_Ext(CallbackAVTransport2GetMediaInfo_Ext aCallback, void* aPtr)
{
    iCallbackGetMediaInfo_Ext = aCallback;
    iPtrGetMediaInfo_Ext = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionGetMediaInfo_Ext();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionGetTransportInfo(CallbackAVTransport2GetTransportInfo aCallback, void* aPtr)
{
    iCallbackGetTransportInfo = aCallback;
    iPtrGetTransportInfo = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionGetTransportInfo();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionGetPositionInfo(CallbackAVTransport2GetPositionInfo aCallback, void* aPtr)
{
    iCallbackGetPositionInfo = aCallback;
    iPtrGetPositionInfo = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionGetPositionInfo();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionGetDeviceCapabilities(CallbackAVTransport2GetDeviceCapabilities aCallback, void* aPtr)
{
    iCallbackGetDeviceCapabilities = aCallback;
    iPtrGetDeviceCapabilities = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionGetDeviceCapabilities();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionGetTransportSettings(CallbackAVTransport2GetTransportSettings aCallback, void* aPtr)
{
    iCallbackGetTransportSettings = aCallback;
    iPtrGetTransportSettings = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionGetTransportSettings();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionStop(CallbackAVTransport2Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionStop();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionPlay(CallbackAVTransport2Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionPlay();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionPause(CallbackAVTransport2Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionPause();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionRecord(CallbackAVTransport2Record aCallback, void* aPtr)
{
    iCallbackRecord = aCallback;
    iPtrRecord = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionRecord();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionSeek(CallbackAVTransport2Seek aCallback, void* aPtr)
{
    iCallbackSeek = aCallback;
    iPtrSeek = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionSeek();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionNext(CallbackAVTransport2Next aCallback, void* aPtr)
{
    iCallbackNext = aCallback;
    iPtrNext = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionNext();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionPrevious(CallbackAVTransport2Previous aCallback, void* aPtr)
{
    iCallbackPrevious = aCallback;
    iPtrPrevious = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionPrevious();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionSetPlayMode(CallbackAVTransport2SetPlayMode aCallback, void* aPtr)
{
    iCallbackSetPlayMode = aCallback;
    iPtrSetPlayMode = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionSetPlayMode();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionSetRecordQualityMode(CallbackAVTransport2SetRecordQualityMode aCallback, void* aPtr)
{
    iCallbackSetRecordQualityMode = aCallback;
    iPtrSetRecordQualityMode = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionSetRecordQualityMode();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionGetCurrentTransportActions(CallbackAVTransport2GetCurrentTransportActions aCallback, void* aPtr)
{
    iCallbackGetCurrentTransportActions = aCallback;
    iPtrGetCurrentTransportActions = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionGetCurrentTransportActions();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionGetDRMState(CallbackAVTransport2GetDRMState aCallback, void* aPtr)
{
    iCallbackGetDRMState = aCallback;
    iPtrGetDRMState = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionGetDRMState();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionGetStateVariables(CallbackAVTransport2GetStateVariables aCallback, void* aPtr)
{
    iCallbackGetStateVariables = aCallback;
    iPtrGetStateVariables = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionGetStateVariables();
}

void DvServiceUpnpOrgAVTransport2C::EnableActionSetStateVariables(CallbackAVTransport2SetStateVariables aCallback, void* aPtr)
{
    iCallbackSetStateVariables = aCallback;
    iPtrSetStateVariables = aPtr;
    DvServiceUpnpOrgAVTransport2::EnableActionSetStateVariables();
}

void DvServiceUpnpOrgAVTransport2C::SetAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData)
{
    ASSERT(iCallbackSetAVTransportURI != NULL);
    if (0 != iCallbackSetAVTransportURI(iPtrSetAVTransportURI, aVersion, aInstanceID, (const char*)aCurrentURI.Ptr(), (const char*)aCurrentURIMetaData.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport2C::SetNextAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData)
{
    ASSERT(iCallbackSetNextAVTransportURI != NULL);
    if (0 != iCallbackSetNextAVTransportURI(iPtrSetNextAVTransportURI, aVersion, aInstanceID, (const char*)aNextURI.Ptr(), (const char*)aNextURIMetaData.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport2C::GetMediaInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aNrTracks, IInvocationResponseString& aMediaDuration, IInvocationResponseString& aCurrentURI, IInvocationResponseString& aCurrentURIMetaData, IInvocationResponseString& aNextURI, IInvocationResponseString& aNextURIMetaData, IInvocationResponseString& aPlayMedium, IInvocationResponseString& aRecordMedium, IInvocationResponseString& aWriteStatus)
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

void DvServiceUpnpOrgAVTransport2C::GetMediaInfo_Ext(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentType, IInvocationResponseUint& aNrTracks, IInvocationResponseString& aMediaDuration, IInvocationResponseString& aCurrentURI, IInvocationResponseString& aCurrentURIMetaData, IInvocationResponseString& aNextURI, IInvocationResponseString& aNextURIMetaData, IInvocationResponseString& aPlayMedium, IInvocationResponseString& aRecordMedium, IInvocationResponseString& aWriteStatus)
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

void DvServiceUpnpOrgAVTransport2C::GetTransportInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentTransportState, IInvocationResponseString& aCurrentTransportStatus, IInvocationResponseString& aCurrentSpeed)
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

void DvServiceUpnpOrgAVTransport2C::GetPositionInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aTrack, IInvocationResponseString& aTrackDuration, IInvocationResponseString& aTrackMetaData, IInvocationResponseString& aTrackURI, IInvocationResponseString& aRelTime, IInvocationResponseString& aAbsTime, IInvocationResponseInt& aRelCount, IInvocationResponseInt& aAbsCount)
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

void DvServiceUpnpOrgAVTransport2C::GetDeviceCapabilities(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aPlayMedia, IInvocationResponseString& aRecMedia, IInvocationResponseString& aRecQualityModes)
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

void DvServiceUpnpOrgAVTransport2C::GetTransportSettings(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aPlayMode, IInvocationResponseString& aRecQualityMode)
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

void DvServiceUpnpOrgAVTransport2C::Stop(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport2C::Play(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aSpeed)
{
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, aVersion, aInstanceID, (const char*)aSpeed.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport2C::Pause(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackPause != NULL);
    if (0 != iCallbackPause(iPtrPause, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport2C::Record(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackRecord != NULL);
    if (0 != iCallbackRecord(iPtrRecord, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport2C::Seek(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aUnit, const Brx& aTarget)
{
    ASSERT(iCallbackSeek != NULL);
    if (0 != iCallbackSeek(iPtrSeek, aVersion, aInstanceID, (const char*)aUnit.Ptr(), (const char*)aTarget.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport2C::Next(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackNext != NULL);
    if (0 != iCallbackNext(iPtrNext, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport2C::Previous(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackPrevious != NULL);
    if (0 != iCallbackPrevious(iPtrPrevious, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport2C::SetPlayMode(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNewPlayMode)
{
    ASSERT(iCallbackSetPlayMode != NULL);
    if (0 != iCallbackSetPlayMode(iPtrSetPlayMode, aVersion, aInstanceID, (const char*)aNewPlayMode.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport2C::SetRecordQualityMode(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNewRecordQualityMode)
{
    ASSERT(iCallbackSetRecordQualityMode != NULL);
    if (0 != iCallbackSetRecordQualityMode(iPtrSetRecordQualityMode, aVersion, aInstanceID, (const char*)aNewRecordQualityMode.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport2C::GetCurrentTransportActions(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aActions)
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

void DvServiceUpnpOrgAVTransport2C::GetDRMState(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentDRMState)
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

void DvServiceUpnpOrgAVTransport2C::GetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aStateVariableList, IInvocationResponseString& aStateVariableValuePairs)
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

void DvServiceUpnpOrgAVTransport2C::SetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aAVTransportUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, IInvocationResponseString& aStateVariableList)
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



THandle DvServiceUpnpOrgAVTransport2Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceUpnpOrgAVTransport2C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceUpnpOrgAVTransport2Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService);
}

void DvServiceUpnpOrgAVTransport2EnableActionSetAVTransportURI(THandle aService, CallbackAVTransport2SetAVTransportURI aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionSetAVTransportURI(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionSetNextAVTransportURI(THandle aService, CallbackAVTransport2SetNextAVTransportURI aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionSetNextAVTransportURI(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionGetMediaInfo(THandle aService, CallbackAVTransport2GetMediaInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionGetMediaInfo(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionGetMediaInfo_Ext(THandle aService, CallbackAVTransport2GetMediaInfo_Ext aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionGetMediaInfo_Ext(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionGetTransportInfo(THandle aService, CallbackAVTransport2GetTransportInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionGetTransportInfo(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionGetPositionInfo(THandle aService, CallbackAVTransport2GetPositionInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionGetPositionInfo(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionGetDeviceCapabilities(THandle aService, CallbackAVTransport2GetDeviceCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionGetDeviceCapabilities(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionGetTransportSettings(THandle aService, CallbackAVTransport2GetTransportSettings aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionGetTransportSettings(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionStop(THandle aService, CallbackAVTransport2Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionStop(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionPlay(THandle aService, CallbackAVTransport2Play aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionPlay(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionPause(THandle aService, CallbackAVTransport2Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionPause(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionRecord(THandle aService, CallbackAVTransport2Record aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionRecord(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionSeek(THandle aService, CallbackAVTransport2Seek aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionSeek(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionNext(THandle aService, CallbackAVTransport2Next aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionNext(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionPrevious(THandle aService, CallbackAVTransport2Previous aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionPrevious(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionSetPlayMode(THandle aService, CallbackAVTransport2SetPlayMode aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionSetPlayMode(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionSetRecordQualityMode(THandle aService, CallbackAVTransport2SetRecordQualityMode aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionSetRecordQualityMode(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionGetCurrentTransportActions(THandle aService, CallbackAVTransport2GetCurrentTransportActions aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionGetCurrentTransportActions(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionGetDRMState(THandle aService, CallbackAVTransport2GetDRMState aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionGetDRMState(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionGetStateVariables(THandle aService, CallbackAVTransport2GetStateVariables aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionGetStateVariables(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport2EnableActionSetStateVariables(THandle aService, CallbackAVTransport2SetStateVariables aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->EnableActionSetStateVariables(aCallback, aPtr);
}

int32_t DvServiceUpnpOrgAVTransport2SetPropertyLastChange(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->SetPropertyLastChange(buf);
    return 0;
}

void DvServiceUpnpOrgAVTransport2GetPropertyLastChange(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceUpnpOrgAVTransport2SetPropertyDRMState(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->SetPropertyDRMState(buf);
    return 0;
}

void DvServiceUpnpOrgAVTransport2GetPropertyDRMState(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgAVTransport2C*>(aService)->GetPropertyDRMState(buf);
    *aValue = (char*)buf.Transfer();
}

