#include <C/DvUpnpOrgAVTransport1.h>
#include <Core/DvUpnpOrgAVTransport1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceUpnpOrgAVTransport1C : public DvServiceUpnpOrgAVTransport1
{
public:
    DvServiceUpnpOrgAVTransport1C(DvDevice& aDevice);
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
    void SetAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData);
    void SetNextAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData);
    void GetMediaInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aNrTracks, IInvocationResponseString& aMediaDuration, IInvocationResponseString& aCurrentURI, IInvocationResponseString& aCurrentURIMetaData, IInvocationResponseString& aNextURI, IInvocationResponseString& aNextURIMetaData, IInvocationResponseString& aPlayMedium, IInvocationResponseString& aRecordMedium, IInvocationResponseString& aWriteStatus);
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
};

DvServiceUpnpOrgAVTransport1C::DvServiceUpnpOrgAVTransport1C(DvDevice& aDevice)
    : DvServiceUpnpOrgAVTransport1(aDevice)
{
}

void DvServiceUpnpOrgAVTransport1C::EnableActionSetAVTransportURI(CallbackAVTransport1SetAVTransportURI aCallback, void* aPtr)
{
    iCallbackSetAVTransportURI = aCallback;
    iPtrSetAVTransportURI = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionSetAVTransportURI();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionSetNextAVTransportURI(CallbackAVTransport1SetNextAVTransportURI aCallback, void* aPtr)
{
    iCallbackSetNextAVTransportURI = aCallback;
    iPtrSetNextAVTransportURI = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionSetNextAVTransportURI();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionGetMediaInfo(CallbackAVTransport1GetMediaInfo aCallback, void* aPtr)
{
    iCallbackGetMediaInfo = aCallback;
    iPtrGetMediaInfo = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionGetMediaInfo();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionGetTransportInfo(CallbackAVTransport1GetTransportInfo aCallback, void* aPtr)
{
    iCallbackGetTransportInfo = aCallback;
    iPtrGetTransportInfo = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionGetTransportInfo();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionGetPositionInfo(CallbackAVTransport1GetPositionInfo aCallback, void* aPtr)
{
    iCallbackGetPositionInfo = aCallback;
    iPtrGetPositionInfo = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionGetPositionInfo();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionGetDeviceCapabilities(CallbackAVTransport1GetDeviceCapabilities aCallback, void* aPtr)
{
    iCallbackGetDeviceCapabilities = aCallback;
    iPtrGetDeviceCapabilities = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionGetDeviceCapabilities();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionGetTransportSettings(CallbackAVTransport1GetTransportSettings aCallback, void* aPtr)
{
    iCallbackGetTransportSettings = aCallback;
    iPtrGetTransportSettings = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionGetTransportSettings();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionStop(CallbackAVTransport1Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionStop();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionPlay(CallbackAVTransport1Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionPlay();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionPause(CallbackAVTransport1Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionPause();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionRecord(CallbackAVTransport1Record aCallback, void* aPtr)
{
    iCallbackRecord = aCallback;
    iPtrRecord = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionRecord();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionSeek(CallbackAVTransport1Seek aCallback, void* aPtr)
{
    iCallbackSeek = aCallback;
    iPtrSeek = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionSeek();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionNext(CallbackAVTransport1Next aCallback, void* aPtr)
{
    iCallbackNext = aCallback;
    iPtrNext = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionNext();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionPrevious(CallbackAVTransport1Previous aCallback, void* aPtr)
{
    iCallbackPrevious = aCallback;
    iPtrPrevious = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionPrevious();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionSetPlayMode(CallbackAVTransport1SetPlayMode aCallback, void* aPtr)
{
    iCallbackSetPlayMode = aCallback;
    iPtrSetPlayMode = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionSetPlayMode();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionSetRecordQualityMode(CallbackAVTransport1SetRecordQualityMode aCallback, void* aPtr)
{
    iCallbackSetRecordQualityMode = aCallback;
    iPtrSetRecordQualityMode = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionSetRecordQualityMode();
}

void DvServiceUpnpOrgAVTransport1C::EnableActionGetCurrentTransportActions(CallbackAVTransport1GetCurrentTransportActions aCallback, void* aPtr)
{
    iCallbackGetCurrentTransportActions = aCallback;
    iPtrGetCurrentTransportActions = aPtr;
    DvServiceUpnpOrgAVTransport1::EnableActionGetCurrentTransportActions();
}

void DvServiceUpnpOrgAVTransport1C::SetAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData)
{
    ASSERT(iCallbackSetAVTransportURI != NULL);
    if (0 != iCallbackSetAVTransportURI(iPtrSetAVTransportURI, aVersion, aInstanceID, (const char*)aCurrentURI.Ptr(), (const char*)aCurrentURIMetaData.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport1C::SetNextAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData)
{
    ASSERT(iCallbackSetNextAVTransportURI != NULL);
    if (0 != iCallbackSetNextAVTransportURI(iPtrSetNextAVTransportURI, aVersion, aInstanceID, (const char*)aNextURI.Ptr(), (const char*)aNextURIMetaData.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport1C::GetMediaInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aNrTracks, IInvocationResponseString& aMediaDuration, IInvocationResponseString& aCurrentURI, IInvocationResponseString& aCurrentURIMetaData, IInvocationResponseString& aNextURI, IInvocationResponseString& aNextURIMetaData, IInvocationResponseString& aPlayMedium, IInvocationResponseString& aRecordMedium, IInvocationResponseString& aWriteStatus)
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

void DvServiceUpnpOrgAVTransport1C::GetTransportInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentTransportState, IInvocationResponseString& aCurrentTransportStatus, IInvocationResponseString& aCurrentSpeed)
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

void DvServiceUpnpOrgAVTransport1C::GetPositionInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aTrack, IInvocationResponseString& aTrackDuration, IInvocationResponseString& aTrackMetaData, IInvocationResponseString& aTrackURI, IInvocationResponseString& aRelTime, IInvocationResponseString& aAbsTime, IInvocationResponseInt& aRelCount, IInvocationResponseInt& aAbsCount)
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

void DvServiceUpnpOrgAVTransport1C::GetDeviceCapabilities(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aPlayMedia, IInvocationResponseString& aRecMedia, IInvocationResponseString& aRecQualityModes)
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

void DvServiceUpnpOrgAVTransport1C::GetTransportSettings(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aPlayMode, IInvocationResponseString& aRecQualityMode)
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

void DvServiceUpnpOrgAVTransport1C::Stop(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport1C::Play(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aSpeed)
{
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, aVersion, aInstanceID, (const char*)aSpeed.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport1C::Pause(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackPause != NULL);
    if (0 != iCallbackPause(iPtrPause, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport1C::Record(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackRecord != NULL);
    if (0 != iCallbackRecord(iPtrRecord, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport1C::Seek(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aUnit, const Brx& aTarget)
{
    ASSERT(iCallbackSeek != NULL);
    if (0 != iCallbackSeek(iPtrSeek, aVersion, aInstanceID, (const char*)aUnit.Ptr(), (const char*)aTarget.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport1C::Next(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackNext != NULL);
    if (0 != iCallbackNext(iPtrNext, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport1C::Previous(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackPrevious != NULL);
    if (0 != iCallbackPrevious(iPtrPrevious, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport1C::SetPlayMode(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNewPlayMode)
{
    ASSERT(iCallbackSetPlayMode != NULL);
    if (0 != iCallbackSetPlayMode(iPtrSetPlayMode, aVersion, aInstanceID, (const char*)aNewPlayMode.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport1C::SetRecordQualityMode(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNewRecordQualityMode)
{
    ASSERT(iCallbackSetRecordQualityMode != NULL);
    if (0 != iCallbackSetRecordQualityMode(iPtrSetRecordQualityMode, aVersion, aInstanceID, (const char*)aNewRecordQualityMode.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgAVTransport1C::GetCurrentTransportActions(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aActions)
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



THandle DvServiceUpnpOrgAVTransport1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceUpnpOrgAVTransport1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceUpnpOrgAVTransport1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService);
}

void DvServiceUpnpOrgAVTransport1EnableActionSetAVTransportURI(THandle aService, CallbackAVTransport1SetAVTransportURI aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionSetAVTransportURI(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionSetNextAVTransportURI(THandle aService, CallbackAVTransport1SetNextAVTransportURI aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionSetNextAVTransportURI(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionGetMediaInfo(THandle aService, CallbackAVTransport1GetMediaInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionGetMediaInfo(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionGetTransportInfo(THandle aService, CallbackAVTransport1GetTransportInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionGetTransportInfo(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionGetPositionInfo(THandle aService, CallbackAVTransport1GetPositionInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionGetPositionInfo(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionGetDeviceCapabilities(THandle aService, CallbackAVTransport1GetDeviceCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionGetDeviceCapabilities(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionGetTransportSettings(THandle aService, CallbackAVTransport1GetTransportSettings aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionGetTransportSettings(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionStop(THandle aService, CallbackAVTransport1Stop aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionStop(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionPlay(THandle aService, CallbackAVTransport1Play aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionPlay(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionPause(THandle aService, CallbackAVTransport1Pause aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionPause(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionRecord(THandle aService, CallbackAVTransport1Record aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionRecord(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionSeek(THandle aService, CallbackAVTransport1Seek aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionSeek(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionNext(THandle aService, CallbackAVTransport1Next aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionNext(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionPrevious(THandle aService, CallbackAVTransport1Previous aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionPrevious(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionSetPlayMode(THandle aService, CallbackAVTransport1SetPlayMode aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionSetPlayMode(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionSetRecordQualityMode(THandle aService, CallbackAVTransport1SetRecordQualityMode aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionSetRecordQualityMode(aCallback, aPtr);
}

void DvServiceUpnpOrgAVTransport1EnableActionGetCurrentTransportActions(THandle aService, CallbackAVTransport1GetCurrentTransportActions aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->EnableActionGetCurrentTransportActions(aCallback, aPtr);
}

int32_t DvServiceUpnpOrgAVTransport1SetPropertyLastChange(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->SetPropertyLastChange(buf);
    return 0;
}

void DvServiceUpnpOrgAVTransport1GetPropertyLastChange(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgAVTransport1C*>(aService)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

