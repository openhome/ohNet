#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <Generated/DvUpnpOrgAVTransport1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Av/UpnpAv/UpnpAv.h>

namespace OpenHome {
namespace Av {

class ProviderAvTransport : public Net::DvProviderUpnpOrgAVTransport1, public Media::IPipelineObserver
{
    typedef Bws<7> BwsTime; // H:MM:SS format
public:
    static const Brn kNotImplemented;
    static const Brn kTransportStateStopped;
    static const Brn kTransportStatePlaying;
    static const Brn kTransportStatePausedPlayback;
    static const Brn kTransportStateTransitioning;
    static const Brn kTransportStateNoMediaPresent;
    static const Brn kTransportStatusOk;
    static const Brn kTransportStatusErrorOccurred;
    static const Brn kCurrentMediaCategoryNoMedia;
    static const Brn kCurrentMediaCategoryTrackAware;
    static const Brn kCurrentMediaCategoryTrackUnaware;
    static const Brn kPlaybackStorageMediumNone;
    static const Brn kPlaybackStorageMediumNetwork;
    static const Brn kRecordStorageMediumNotImplemented;
    static const Brn kCurrentPlayModeNormal;
    static const Brn kTransportPlaySpeed1;
    static const Brn kRecordMediumWriteStatusNotImplemented;
    static const Brn kCurrentRecordQualityModeNotImplemented;
    static const Brn kSeekModeTrackNr;
    static const Brn kSeekModeAbsTime;
    static const Brn kSeekModeRelTime;
public:
    ProviderAvTransport(Net::DvDevice& aDevice, Environment& aEnv, ISourceUpnpAv& aSourceUpnpAv);
    ~ProviderAvTransport();
private: // from Net::DvProviderUpnpOrgAvTransport1
    void SetAVTransportURI(Net::IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData) override;
    void GetMediaInfo(Net::IDvInvocation& aInvocation, TUint aInstanceID, Net::IDvInvocationResponseUint& aNrTracks,
                      Net::IDvInvocationResponseString& aMediaDuration, Net::IDvInvocationResponseString& aCurrentURI,
                      Net::IDvInvocationResponseString& aCurrentURIMetaData, Net::IDvInvocationResponseString& aNextURI,
                      Net::IDvInvocationResponseString& aNextURIMetaData, Net::IDvInvocationResponseString& aPlayMedium,
                      Net::IDvInvocationResponseString& aRecordMedium, Net::IDvInvocationResponseString& aWriteStatus) override;
    void GetTransportInfo(Net::IDvInvocation& aInvocation, TUint aInstanceID, Net::IDvInvocationResponseString& aCurrentTransportState,
                          Net::IDvInvocationResponseString& aCurrentTransportStatus, Net::IDvInvocationResponseString& aCurrentSpeed) override;
    void GetPositionInfo(Net::IDvInvocation& aInvocation, TUint aInstanceID, Net::IDvInvocationResponseUint& aTrack,
                         Net::IDvInvocationResponseString& aTrackDuration, Net::IDvInvocationResponseString& aTrackMetaData,
                         Net::IDvInvocationResponseString& aTrackURI, Net::IDvInvocationResponseString& aRelTime, Net::IDvInvocationResponseString& aAbsTime,
                         Net::IDvInvocationResponseInt& aRelCount, Net::IDvInvocationResponseInt& aAbsCount) override;
    void GetDeviceCapabilities(Net::IDvInvocation& aInvocation, TUint aInstanceID, Net::IDvInvocationResponseString& aPlayMedia,
                               Net::IDvInvocationResponseString& aRecMedia, Net::IDvInvocationResponseString& aRecQualityModes) override;
    void GetTransportSettings(Net::IDvInvocation& aInvocation, TUint aInstanceID, Net::IDvInvocationResponseString& aPlayMode, Net::IDvInvocationResponseString& aRecQualityMode) override;
    void Stop(Net::IDvInvocation& aInvocation, TUint aInstanceID) override;
    void Play(Net::IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aSpeed) override;
    void Pause(Net::IDvInvocation& aInvocation, TUint aInstanceID) override;
    void Seek(Net::IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aUnit, const Brx& aTarget) override;
    void Next(Net::IDvInvocation& aInvocation, TUint aInstanceID) override;
    void Previous(Net::IDvInvocation& aInvocation, TUint aInstanceID) override;
private: // from Media::IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState) override;
    void NotifyMode(const Brx& aMode, const Media::ModeInfo& aInfo) override;
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo) override;
private:
    void QueueStateUpdate();
    void ModerationTimerExpired();
    void UpdateEventedState();
    void AddStateVariable(const Brx& aName, const Brx& aValue);
    void AddStateVariable(const Brx& aName, TUint aValue);
    void AddStateVariableEscaped(const Brx& aName, const Brx& aValue);
    static void SecondsToTimeString(TUint aSeconds, Bwx& aTime);
    static TUint TimeStringToSeconds(const Brx& aTime);
private:
    ISourceUpnpAv& iSourceUpnpAv;
    Mutex iLock;
    Timer* iModerationTimer;
    TBool iModerationTimerStarted;
    Bws<6*1024> iXmlEscapedStateVar;

    // These state variables are currently implemented and their values change
    Brn iTransportStateOverride;    // used when reporting PAUSED state when new track is queued
    Brn iTargetTransportState;      // used during transitions
    Brn iTransportState;
    Brn iTransportStatus;
    Brn iCurrentMediaCategory;
    Brn iPlaybackStorageMedium;
    TUint32 iNumberOfTracks;
    TUint32 iCurrentTrack;
    BwsTime iTrackDuration;
    Media::BwsTrackUri iCurrentTrackUri;
    Media::BwsTrackUri iAvTransportUri;
    Media::BwsTrackMetaData iCurrentTrackMetaData;
    Media::BwsTrackMetaData iAvTransportUriMetaData;

    // These state variables are currently implemented but their values do not change
    const Brn iPossiblePlaybackStorageMedia;
    const Brn iCurrentPlayMode;
    const Brn iTransportPlaySpeed;

    // These state variables are currently unimplemented but may be in the future
    const Brn iNextAvTransportUri;
    const Brn iNextAvTransportUriMetaData;

    // These state variables will not be implemented in the forseeable future
    const Brn iRecordStorageMedium;
    const Brn iPossibleRecordStorageMedia;
    const Brn iRecordMediumWriteStatus;
    const Brn iCurrentRecordQualityMode;
    const Brn iPossibleRecordQualityModes;

    // These state variables should never be evented
    TUint iRelativeTimeSeconds;
    const Bws<16> iAbsoluteTimePosition;
    const TInt32 iRelativeCounterPosition;
    const TInt32 iAbsoluteCounterPosition;

    // buffer storing an aggregated version of the above state variables
    Bws<20*1024> iEventedState;
};

} // namespace Av
} // namespace OpenHome

