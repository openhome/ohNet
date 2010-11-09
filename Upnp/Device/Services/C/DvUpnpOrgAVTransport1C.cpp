#include <C/DvUpnpOrgAVTransport1.h>
#include <Core/DvUpnpOrgAVTransport1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderUpnpOrgAVTransport1C : public DvProviderUpnpOrgAVTransport1
{
public:
    DvProviderUpnpOrgAVTransport1C(DvDevice& aDevice);
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

DvProviderUpnpOrgAVTransport1C::DvProviderUpnpOrgAVTransport1C(DvDevice& aDevice)
    : DvProviderUpnpOrgAVTransport1(aDevice)
{
}

void DvProviderUpnpOrgAVTransport1C::EnableActionSetAVTransportURI(CallbackAVTransport1SetAVTransportURI aCallback, void* aPtr)
{
    iCallbackSetAVTransportURI = aCallback;
    iPtrSetAVTransportURI = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionSetAVTransportURI();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionSetNextAVTransportURI(CallbackAVTransport1SetNextAVTransportURI aCallback, void* aPtr)
{
    iCallbackSetNextAVTransportURI = aCallback;
    iPtrSetNextAVTransportURI = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionSetNextAVTransportURI();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionGetMediaInfo(CallbackAVTransport1GetMediaInfo aCallback, void* aPtr)
{
    iCallbackGetMediaInfo = aCallback;
    iPtrGetMediaInfo = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionGetMediaInfo();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionGetTransportInfo(CallbackAVTransport1GetTransportInfo aCallback, void* aPtr)
{
    iCallbackGetTransportInfo = aCallback;
    iPtrGetTransportInfo = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionGetTransportInfo();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionGetPositionInfo(CallbackAVTransport1GetPositionInfo aCallback, void* aPtr)
{
    iCallbackGetPositionInfo = aCallback;
    iPtrGetPositionInfo = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionGetPositionInfo();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionGetDeviceCapabilities(CallbackAVTransport1GetDeviceCapabilities aCallback, void* aPtr)
{
    iCallbackGetDeviceCapabilities = aCallback;
    iPtrGetDeviceCapabilities = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionGetDeviceCapabilities();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionGetTransportSettings(CallbackAVTransport1GetTransportSettings aCallback, void* aPtr)
{
    iCallbackGetTransportSettings = aCallback;
    iPtrGetTransportSettings = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionGetTransportSettings();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionStop(CallbackAVTransport1Stop aCallback, void* aPtr)
{
    iCallbackStop = aCallback;
    iPtrStop = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionStop();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionPlay(CallbackAVTransport1Play aCallback, void* aPtr)
{
    iCallbackPlay = aCallback;
    iPtrPlay = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionPlay();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionPause(CallbackAVTransport1Pause aCallback, void* aPtr)
{
    iCallbackPause = aCallback;
    iPtrPause = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionPause();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionRecord(CallbackAVTransport1Record aCallback, void* aPtr)
{
    iCallbackRecord = aCallback;
    iPtrRecord = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionRecord();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionSeek(CallbackAVTransport1Seek aCallback, void* aPtr)
{
    iCallbackSeek = aCallback;
    iPtrSeek = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionSeek();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionNext(CallbackAVTransport1Next aCallback, void* aPtr)
{
    iCallbackNext = aCallback;
    iPtrNext = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionNext();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionPrevious(CallbackAVTransport1Previous aCallback, void* aPtr)
{
    iCallbackPrevious = aCallback;
    iPtrPrevious = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionPrevious();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionSetPlayMode(CallbackAVTransport1SetPlayMode aCallback, void* aPtr)
{
    iCallbackSetPlayMode = aCallback;
    iPtrSetPlayMode = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionSetPlayMode();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionSetRecordQualityMode(CallbackAVTransport1SetRecordQualityMode aCallback, void* aPtr)
{
    iCallbackSetRecordQualityMode = aCallback;
    iPtrSetRecordQualityMode = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionSetRecordQualityMode();
}

void DvProviderUpnpOrgAVTransport1C::EnableActionGetCurrentTransportActions(CallbackAVTransport1GetCurrentTransportActions aCallback, void* aPtr)
{
    iCallbackGetCurrentTransportActions = aCallback;
    iPtrGetCurrentTransportActions = aPtr;
    DvProviderUpnpOrgAVTransport1::EnableActionGetCurrentTransportActions();
}

void DvProviderUpnpOrgAVTransport1C::SetAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData)
{
    ASSERT(iCallbackSetAVTransportURI != NULL);
    if (0 != iCallbackSetAVTransportURI(iPtrSetAVTransportURI, aVersion, aInstanceID, (const char*)aCurrentURI.Ptr(), (const char*)aCurrentURIMetaData.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport1C::SetNextAVTransportURI(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData)
{
    ASSERT(iCallbackSetNextAVTransportURI != NULL);
    if (0 != iCallbackSetNextAVTransportURI(iPtrSetNextAVTransportURI, aVersion, aInstanceID, (const char*)aNextURI.Ptr(), (const char*)aNextURIMetaData.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport1C::GetMediaInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aNrTracks, IInvocationResponseString& aMediaDuration, IInvocationResponseString& aCurrentURI, IInvocationResponseString& aCurrentURIMetaData, IInvocationResponseString& aNextURI, IInvocationResponseString& aNextURIMetaData, IInvocationResponseString& aPlayMedium, IInvocationResponseString& aRecordMedium, IInvocationResponseString& aWriteStatus)
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

void DvProviderUpnpOrgAVTransport1C::GetTransportInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentTransportState, IInvocationResponseString& aCurrentTransportStatus, IInvocationResponseString& aCurrentSpeed)
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

void DvProviderUpnpOrgAVTransport1C::GetPositionInfo(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aTrack, IInvocationResponseString& aTrackDuration, IInvocationResponseString& aTrackMetaData, IInvocationResponseString& aTrackURI, IInvocationResponseString& aRelTime, IInvocationResponseString& aAbsTime, IInvocationResponseInt& aRelCount, IInvocationResponseInt& aAbsCount)
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

void DvProviderUpnpOrgAVTransport1C::GetDeviceCapabilities(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aPlayMedia, IInvocationResponseString& aRecMedia, IInvocationResponseString& aRecQualityModes)
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

void DvProviderUpnpOrgAVTransport1C::GetTransportSettings(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aPlayMode, IInvocationResponseString& aRecQualityMode)
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

void DvProviderUpnpOrgAVTransport1C::Stop(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackStop != NULL);
    if (0 != iCallbackStop(iPtrStop, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport1C::Play(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aSpeed)
{
    ASSERT(iCallbackPlay != NULL);
    if (0 != iCallbackPlay(iPtrPlay, aVersion, aInstanceID, (const char*)aSpeed.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport1C::Pause(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackPause != NULL);
    if (0 != iCallbackPause(iPtrPause, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport1C::Record(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackRecord != NULL);
    if (0 != iCallbackRecord(iPtrRecord, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport1C::Seek(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aUnit, const Brx& aTarget)
{
    ASSERT(iCallbackSeek != NULL);
    if (0 != iCallbackSeek(iPtrSeek, aVersion, aInstanceID, (const char*)aUnit.Ptr(), (const char*)aTarget.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport1C::Next(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackNext != NULL);
    if (0 != iCallbackNext(iPtrNext, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport1C::Previous(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID)
{
    ASSERT(iCallbackPrevious != NULL);
    if (0 != iCallbackPrevious(iPtrPrevious, aVersion, aInstanceID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport1C::SetPlayMode(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNewPlayMode)
{
    ASSERT(iCallbackSetPlayMode != NULL);
    if (0 != iCallbackSetPlayMode(iPtrSetPlayMode, aVersion, aInstanceID, (const char*)aNewPlayMode.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport1C::SetRecordQualityMode(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aNewRecordQualityMode)
{
    ASSERT(iCallbackSetRecordQualityMode != NULL);
    if (0 != iCallbackSetRecordQualityMode(iPtrSetRecordQualityMode, aVersion, aInstanceID, (const char*)aNewRecordQualityMode.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgAVTransport1C::GetCurrentTransportActions(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aActions)
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



THandle DvProviderUpnpOrgAVTransport1Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgAVTransport1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
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

