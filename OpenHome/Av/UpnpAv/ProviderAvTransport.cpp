#include <OpenHome/Av/UpnpAv/ProviderAvTransport.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <Generated/DvUpnpOrgAVTransport1.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Av/FaultCode.h>
#include <climits>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;

// UPnP AVTransport spec:
// http://upnp.org/specs/av/UPnP-av-AVTransport-v1-Service.pdf


// iTransportStateOverride exists to support a corner case in SetAVTransportUri.
// From ~2.4.1.3 (Effect on State of SetAVTransportURI action):
// ....
// If the current transport state is “NO MEDIA PRESENT” the transport state
// changes to “STOPPED”. In all other cases, this action does not change the
// transport state of the specified instance.
//
// To support remaining in the PAUSED state when a new URI is set, the state
// reported by the pipeline (which is STOPPED) needs to be overridden until
// an action changes the state.


// iTargetTransportState exists to support corner cases in Play.
// From ~2.4.9 (Play):
// Start playing the resource of the specified instance, at the specified speed
// , starting at the current position, according to the current play mode. Keep
// playing until the resource ends or the transport state is changed via
// actions Stop or Pause.
// ...
//
// If Play is invoked during TRANSITIONING, the pipeline could be buffering an
// already playing track, or moving to a different state than before the
// transition. To ensure an already playing track isn't restarted, the target
// state after the transition is stored on Play/Pause/Stop actions or when
// the pipeline state changes and is checked when Play is invoked.


// For a MediaRenderer device with no ConnectionManager.PrepareForConnection()
// action, the only valid AVTransportID is 0
static const TUint kInstanceId = 0;

static const TUint kTransitionNotAvailableCode = 701;
static const Brn kTransitionNotAvailableMsg("Transition not available");
static const TUint kInvalidInstanceIdCode = 718;
static const Brn kInvalidInstanceIdMsg("Invalid InstanceID");
static const TUint kInvalidSeekModeCode = 710;
static const Brn kInvalidSeekModeMsg("Seek mode not supported");
static const TUint kIllegalSeekTargetCode = 711;
static const Brn kIllegalSeekTargetMsg("Illegal seek target");
static const TUint kUnsupportedPlaySpeedCode = 717;
static const Brn kUnsupportedPlaySpeedMsg("Play speed not supported");

const Brn ProviderAvTransport::kNotImplemented("NOT_IMPLEMENTED");
const Brn ProviderAvTransport::kTransportStateStopped("STOPPED");
const Brn ProviderAvTransport::kTransportStatePlaying("PLAYING");
const Brn ProviderAvTransport::kTransportStatePausedPlayback("PAUSED_PLAYBACK");
const Brn ProviderAvTransport::kTransportStateTransitioning("TRANSITIONING");
const Brn ProviderAvTransport::kTransportStateNoMediaPresent("NO_MEDIA_PRESENT");
const Brn ProviderAvTransport::kTransportStatusOk("OK");
const Brn ProviderAvTransport::kTransportStatusErrorOccurred("ERROR_OCCURRED");
const Brn ProviderAvTransport::kCurrentMediaCategoryNoMedia("NO_MEDIA");
const Brn ProviderAvTransport::kCurrentMediaCategoryTrackAware("TRACK_AWARE");
const Brn ProviderAvTransport::kCurrentMediaCategoryTrackUnaware("TRACK_UNAWARE");
const Brn ProviderAvTransport::kPlaybackStorageMediumNone("NONE");
const Brn ProviderAvTransport::kPlaybackStorageMediumNetwork("NETWORK");
const Brn ProviderAvTransport::kRecordStorageMediumNotImplemented("NOT_IMPLEMENTED");
const Brn ProviderAvTransport::kCurrentPlayModeNormal("NORMAL");
const Brn ProviderAvTransport::kTransportPlaySpeed1("1");
const Brn ProviderAvTransport::kRecordMediumWriteStatusNotImplemented("NOT_IMPLEMENTED");
const Brn ProviderAvTransport::kCurrentRecordQualityModeNotImplemented("NOT_IMPLEMENTED");
const Brn ProviderAvTransport::kSeekModeTrackNr("TRACK_NR");
const Brn ProviderAvTransport::kSeekModeAbsTime("ABS_TIME");
const Brn ProviderAvTransport::kSeekModeRelTime("REL_TIME");

static const Brn kTimeNone("0:00:00");
static const TUint kCounterNotImplemented = 2147483647;

static const TUint kEventModerationMs = 200;

ProviderAvTransport::ProviderAvTransport(Net::DvDevice& aDevice, Environment& aEnv, ISourceUpnpAv& aSourceUpnpAv)
    : DvProviderUpnpOrgAVTransport1(aDevice)
    , iSourceUpnpAv(aSourceUpnpAv)
    , iLock("UpAv")
    , iModerationTimerStarted(false)
    , iTransportStateOverride(Brx::Empty())
    , iTargetTransportState(Brx::Empty())
    , iTransportState(kTransportStateNoMediaPresent)
    , iTransportStatus(kTransportStatusOk)
    , iCurrentMediaCategory(kCurrentMediaCategoryNoMedia)
    , iPlaybackStorageMedium(kPlaybackStorageMediumNone)
    , iNumberOfTracks(0)
    , iCurrentTrack(0)
    , iTrackDuration(kTimeNone)
    , iCurrentTrackUri(Brx::Empty())
    , iAvTransportUri(Brx::Empty())
    , iCurrentTrackMetaData(Brx::Empty())
    , iAvTransportUriMetaData(Brx::Empty())
    , iPossiblePlaybackStorageMedia(kPlaybackStorageMediumNetwork)
    , iCurrentPlayMode(kCurrentPlayModeNormal)
    , iTransportPlaySpeed(kTransportPlaySpeed1)
    , iNextAvTransportUri(kNotImplemented)
    , iNextAvTransportUriMetaData(kNotImplemented)
    , iRecordStorageMedium(kNotImplemented)
    , iPossibleRecordStorageMedia(kNotImplemented)
    , iRecordMediumWriteStatus(kNotImplemented)
    , iCurrentRecordQualityMode(kNotImplemented)
    , iPossibleRecordQualityModes(kNotImplemented)
    , iRelativeTimeSeconds(0)
    , iAbsoluteTimePosition(kNotImplemented)
    , iRelativeCounterPosition(kCounterNotImplemented)
    , iAbsoluteCounterPosition(kCounterNotImplemented)
{
    iModerationTimer = new Timer(aEnv, MakeFunctor(*this, &ProviderAvTransport::ModerationTimerExpired), "ProviderAvTransport");

    EnablePropertyLastChange();
    
    EnableActionSetAVTransportURI();
    EnableActionGetMediaInfo();
    EnableActionGetTransportInfo();
    EnableActionGetPositionInfo();
    EnableActionGetDeviceCapabilities();
    EnableActionGetTransportSettings();
    EnableActionStop();
    EnableActionPlay();
    EnableActionPause();
    EnableActionSeek();
    EnableActionNext();
    EnableActionPrevious();

    UpdateEventedState();
}

ProviderAvTransport::~ProviderAvTransport()
{
    delete iModerationTimer;
}

void ProviderAvTransport::SetAVTransportURI(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    aInvocation.StartResponse();
    {
        TBool playing = false;
        iLock.Wait();
        Brn metaData(aCurrentURIMetaData);
        if (metaData.Bytes() > iCurrentTrackMetaData.MaxBytes()) {
            metaData.Set(metaData.Split(0, iCurrentTrackMetaData.MaxBytes()));
        }
        if (aCurrentURI == Brx::Empty()) {
            iTransportStateOverride.Set(Brx::Empty());
            iTransportState.Set(kTransportStateNoMediaPresent);
            iTargetTransportState.Set(Brx::Empty());
        }
        else if (iTransportState == kTransportStateNoMediaPresent) {
            iTransportStateOverride.Set(Brx::Empty());
            iTransportState.Set(kTransportStateStopped);
            iTargetTransportState.Set(Brx::Empty());
        }
        else {
            if (iTransportState == kTransportStatePlaying) {
                playing = true;
            }
            else {
                // Only pick up iTransportState is there isn't a pending iTransportStateOverride
                if (iTransportStateOverride.Bytes() == 0) {
                    iTransportStateOverride.Set(iTransportState);
                }
            }
        }
        iCurrentTrackUri.Replace(aCurrentURI);
        iCurrentTrackMetaData.Replace(metaData);
        iAvTransportUri.Replace(iCurrentTrackUri);
        iAvTransportUriMetaData.Replace(iCurrentTrackMetaData);
        iCurrentMediaCategory.Set(kCurrentMediaCategoryTrackAware);
        iPlaybackStorageMedium.Set(kPlaybackStorageMediumNetwork);
        iNumberOfTracks = 1;
        iCurrentTrack = 1;
        iRelativeTimeSeconds = 0;
        iTrackDuration.Replace(kTimeNone);

        UpdateEventedState();
        iLock.Signal();
        iSourceUpnpAv.SetTrack(aCurrentURI, metaData);  // do outside lock; would cause attempted recursive
                                                        // lock on mutex when IPipelineObserver calls came
                                                        // back in.

        // Resume playing if already playing before new URI came in.
        if (playing) {
            iSourceUpnpAv.Play();
        }
    }
    aInvocation.EndResponse();
}

void ProviderAvTransport::GetMediaInfo(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseUint& aNrTracks,
                                       IDvInvocationResponseString& aMediaDuration, IDvInvocationResponseString& aCurrentURI,
                                       IDvInvocationResponseString& aCurrentURIMetaData, IDvInvocationResponseString& aNextURI,
                                       IDvInvocationResponseString& aNextURIMetaData, IDvInvocationResponseString& aPlayMedium,
                                       IDvInvocationResponseString& aRecordMedium, IDvInvocationResponseString& aWriteStatus)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    aInvocation.StartResponse();
    {
        AutoMutex a(iLock);
        aNrTracks.Write(iNumberOfTracks);
        aMediaDuration.Write(iTrackDuration);
        aMediaDuration.WriteFlush();
        aCurrentURI.Write(iAvTransportUri);
        aCurrentURI.WriteFlush();
        aCurrentURIMetaData.Write(iAvTransportUriMetaData);
        aCurrentURIMetaData.WriteFlush();
        aNextURI.Write(iNextAvTransportUri);
        aNextURI.WriteFlush();
        aNextURIMetaData.Write(iNextAvTransportUriMetaData);
        aNextURIMetaData.WriteFlush();
        aPlayMedium.Write(iPlaybackStorageMedium);
        aPlayMedium.WriteFlush();
        aRecordMedium.Write(iRecordStorageMedium);
        aRecordMedium.WriteFlush();
        aWriteStatus.Write(iRecordMediumWriteStatus);
        aWriteStatus.WriteFlush();
    }
    aInvocation.EndResponse();
}

void ProviderAvTransport::GetTransportInfo(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseString& aCurrentTransportState,
                                           IDvInvocationResponseString& aCurrentTransportStatus, IDvInvocationResponseString& aCurrentSpeed)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    aInvocation.StartResponse();
    {
        AutoMutex a(iLock);
        if (iTransportStateOverride.Bytes() != 0) {
            aCurrentTransportState.Write(iTransportStateOverride);
        }
        else {
            aCurrentTransportState.Write(iTransportState);
        }
        aCurrentTransportState.WriteFlush();
        aCurrentTransportStatus.Write(iTransportStatus);
        aCurrentTransportStatus.WriteFlush();
        aCurrentSpeed.Write(iTransportPlaySpeed);
        aCurrentSpeed.WriteFlush();
    }
    aInvocation.EndResponse();
}

void ProviderAvTransport::GetPositionInfo(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseUint& aTrack,
                                          IDvInvocationResponseString& aTrackDuration, IDvInvocationResponseString& aTrackMetaData,
                                          IDvInvocationResponseString& aTrackURI, IDvInvocationResponseString& aRelTime, IDvInvocationResponseString& aAbsTime,
                                          IDvInvocationResponseInt& aRelCount, IDvInvocationResponseInt& aAbsCount)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    aInvocation.StartResponse();
    {
        AutoMutex a(iLock);
        aTrack.Write(iCurrentTrack);
        aTrackDuration.Write(iTrackDuration);
        aTrackDuration.WriteFlush();
        aTrackMetaData.Write(iCurrentTrackMetaData);
        aTrackMetaData.WriteFlush();
        aTrackURI.Write(iCurrentTrackUri);
        aTrackURI.WriteFlush();
        BwsTime time;
        SecondsToTimeString(iRelativeTimeSeconds, time);
        aRelTime.Write(time);
        aRelTime.WriteFlush();
        aAbsTime.Write(iAbsoluteTimePosition);
        aAbsTime.WriteFlush();
        aRelCount.Write(iRelativeCounterPosition);
        aAbsCount.Write(iAbsoluteCounterPosition);
    }
    aInvocation.EndResponse();
}

void ProviderAvTransport::GetDeviceCapabilities(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseString& aPlayMedia,
                                                IDvInvocationResponseString& aRecMedia, IDvInvocationResponseString& aRecQualityModes)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    aInvocation.StartResponse();
    {
        AutoMutex a(iLock);
        aPlayMedia.Write(iPossiblePlaybackStorageMedia);
        aPlayMedia.WriteFlush();
        aRecMedia.Write(iPossibleRecordStorageMedia);
        aRecMedia.WriteFlush();
        aRecQualityModes.Write(iPossibleRecordQualityModes);
        aRecQualityModes.WriteFlush();
    }
    aInvocation.EndResponse();
}

void ProviderAvTransport::GetTransportSettings(IDvInvocation& aInvocation, TUint aInstanceID, IDvInvocationResponseString& aPlayMode, IDvInvocationResponseString& aRecQualityMode)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    aInvocation.StartResponse();
    {
        AutoMutex a(iLock);
        aPlayMode.Write(iCurrentPlayMode);
        aPlayMode.WriteFlush();
        aRecQualityMode.Write(iCurrentRecordQualityMode);
        aRecQualityMode.WriteFlush();
    }
    aInvocation.EndResponse();
}

void ProviderAvTransport::Stop(IDvInvocation& aInvocation, TUint aInstanceID)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    {
        AutoMutex a(iLock);
        if (iTransportState == kTransportStateNoMediaPresent) {
            aInvocation.Error(kTransitionNotAvailableCode, kTransitionNotAvailableMsg);
        }
    }
    aInvocation.StartResponse();
    {
        AutoMutex a(iLock);
        iTransportStateOverride.Set(Brx::Empty());
        iTargetTransportState.Set(kTransportStateStopped);
    }
    iSourceUpnpAv.Stop();
    {
        AutoMutex a(iLock);
        iRelativeTimeSeconds = 0;
    }
    aInvocation.EndResponse();
}

void ProviderAvTransport::Play(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aSpeed)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    if (aSpeed != kTransportPlaySpeed1) {
        aInvocation.Error(kUnsupportedPlaySpeedCode, kUnsupportedPlaySpeedMsg);
    }
    {
        AutoMutex a(iLock);
        if (iTransportState == kTransportStateNoMediaPresent) {
            aInvocation.Error(kTransitionNotAvailableCode, kTransitionNotAvailableMsg);
        }
    }
    aInvocation.StartResponse();
    TBool play = true;
    {
        AutoMutex a(iLock);
        if (iTransportState == kTransportStatePlaying || iTargetTransportState == kTransportStatePlaying) {
            // Already playing.
            play = false;
        }
        iTransportStateOverride.Set(Brx::Empty());
        iTargetTransportState.Set(kTransportStatePlaying);
    }
    if (play) {
        iSourceUpnpAv.Play();
    }
    aInvocation.EndResponse();
}

void ProviderAvTransport::Pause(IDvInvocation& aInvocation, TUint aInstanceID)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    {
        AutoMutex a(iLock);
        if (iTransportState == kTransportStateNoMediaPresent || iTransportState == kTransportStateStopped) {
            aInvocation.Error(kTransitionNotAvailableCode, kTransitionNotAvailableMsg);
        }
    }
    aInvocation.StartResponse();
    {
        AutoMutex a(iLock);
        iTransportStateOverride.Set(Brx::Empty());
        iTargetTransportState.Set(kTransportStatePausedPlayback);
    }
    iSourceUpnpAv.Pause();
    aInvocation.EndResponse();
}

void ProviderAvTransport::Seek(IDvInvocation& aInvocation, TUint aInstanceID, const Brx& aUnit, const Brx& aTarget)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    {
        AutoMutex a(iLock);
        if (iTransportState == kTransportStateStopped || iTransportState == kTransportStatePausedPlayback) {
            aInvocation.Error(kTransitionNotAvailableCode, kTransitionNotAvailableMsg);
        }
    }
    TUint secs = 0;
    if (aUnit == kSeekModeTrackNr) {
        TUint trackNum = UINT_MAX;
        try {
            trackNum = Ascii::Uint(aTarget);
        }
        catch (AsciiError&) {
            aInvocation.Error(kIllegalSeekTargetCode, kIllegalSeekTargetMsg);
        }
        if (trackNum > 1) {
            aInvocation.Error(kIllegalSeekTargetCode, kIllegalSeekTargetMsg);
        }
        // return to start of track (i.e. leave secs == 0)
    }
    else if (aUnit == kSeekModeAbsTime || aUnit == kSeekModeRelTime) {
        try {
            secs = TimeStringToSeconds(aTarget);
        }
        catch (AsciiError&) {
            aInvocation.Error(kIllegalSeekTargetCode, kIllegalSeekTargetMsg);
        }
        if (aUnit == kSeekModeRelTime) {
            iLock.Wait();
            secs += iRelativeTimeSeconds;
            iLock.Signal();
        }
    }
    else {
        aInvocation.Error(kInvalidSeekModeCode, kInvalidSeekModeMsg);
    }

    aInvocation.StartResponse();
    iSourceUpnpAv.Seek(secs);
    {
        AutoMutex a(iLock);
        iTransportStateOverride.Set(Brx::Empty());
    }
    aInvocation.EndResponse();
}

void ProviderAvTransport::Next(IDvInvocation& aInvocation, TUint aInstanceID)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    aInvocation.StartResponse();
    iSourceUpnpAv.Next();
    {
        AutoMutex a(iLock);
        iTransportStateOverride.Set(Brx::Empty());
        iRelativeTimeSeconds = 0;
    }
    aInvocation.EndResponse();
}

void ProviderAvTransport::Previous(IDvInvocation& aInvocation, TUint aInstanceID)
{
    if (aInstanceID != kInstanceId) {
        aInvocation.Error(kInvalidInstanceIdCode, kInvalidInstanceIdMsg);
    }
    aInvocation.StartResponse();
    iSourceUpnpAv.Prev();
    {
        AutoMutex a(iLock);
        iTransportStateOverride.Set(Brx::Empty());
        iRelativeTimeSeconds = 0;
    }
    aInvocation.EndResponse();
}

void ProviderAvTransport::NotifyPipelineState(EPipelineState aState)
{
    // Set iTargetTransportState each time a long-term state is encountered
    // (i.e., not TRANSITIONING). Ensures that if state goes TRANSITIONING
    // while playing, it can be known that it will resume playing. Otherwise,
    // transitioning to a non-playing state.
    iLock.Wait();
    switch (aState)
    {
    case EPipelinePlaying:
        iTransportState.Set(kTransportStatePlaying);
        iTargetTransportState.Set(kTransportStatePlaying);
        break;
    case EPipelinePaused:
    case EPipelineWaiting:
        iTransportState.Set(kTransportStatePausedPlayback);
        iTargetTransportState.Set(kTransportStatePausedPlayback);
        break;
    case EPipelineStopped:
        if (iCurrentTrackUri != Brx::Empty()) {
            iTransportState.Set(kTransportStateStopped);
            iTargetTransportState.Set(kTransportStateStopped);
        }
        else {
            iTransportState.Set(kTransportStateNoMediaPresent); // no track to play
            iTargetTransportState.Set(Brx::Empty());
        }
        break;
    case EPipelineBuffering:
        iTransportState.Set(kTransportStateTransitioning);
        break;
    default:
        ASSERTS();
        break;
    }
    QueueStateUpdate();
    iLock.Signal();
}

void ProviderAvTransport::NotifyTrack(Track& aTrack, const Brx& /*aMode*/, TBool /*aStartOfStream*/)
{
    iLock.Wait();
    iCurrentTrackUri.Replace(aTrack.Uri());
    iCurrentTrackMetaData.Replace(aTrack.MetaData());
    if (aTrack.Uri() == Brx::Empty()) {
        iAvTransportUri.Replace(iCurrentTrackUri);
        iAvTransportUriMetaData.Replace(iCurrentTrackMetaData);
        iCurrentMediaCategory.Set(kCurrentMediaCategoryNoMedia);
        iPlaybackStorageMedium.Set(kPlaybackStorageMediumNone);
        iNumberOfTracks = 0;
        iCurrentTrack = 0;
        iRelativeTimeSeconds = 0;
        iTrackDuration.Replace(kTimeNone);
        iTransportState.Set(kTransportStateNoMediaPresent);
    }
    QueueStateUpdate();
    iLock.Signal();
}

void ProviderAvTransport::NotifyMetaText(const Brx& aText)
{
    iLock.Wait();
    iCurrentTrackMetaData.Replace(aText);
    QueueStateUpdate();
    iLock.Signal();
}

void ProviderAvTransport::NotifyTime(TUint aSeconds, TUint /*aTrackDurationSeconds*/)
{
    iLock.Wait();
    iRelativeTimeSeconds = aSeconds;
    iLock.Signal();
    // no call to UpdateEventedState here.  We don't want to include a constantly changing variable in iEventedState
}

void ProviderAvTransport::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    const TUint trackDurationSeconds = (TUint)(aStreamInfo.TrackLength() / Jiffies::kPerSecond);
    iLock.Wait();
    SecondsToTimeString(trackDurationSeconds, iTrackDuration);
    QueueStateUpdate();
    iLock.Signal();
}

void ProviderAvTransport::QueueStateUpdate()
{
    // assumes iLock is held by caller
    if (!iModerationTimerStarted) {
        iModerationTimer->FireIn(kEventModerationMs);
        iModerationTimerStarted = true;
    }
}

void ProviderAvTransport::ModerationTimerExpired()
{
    iLock.Wait();
    iModerationTimerStarted = false;
    UpdateEventedState();
    iLock.Signal();
}

void ProviderAvTransport::UpdateEventedState()
{
    // Write the header for the event
    iEventedState.Replace("<Event xmlns=\"urn:schemas-upnp-org:metadata-1-0/AVT/\">\n");
    iEventedState.Append("    <InstanceID val=\"");
    Ascii::AppendDec(iEventedState, kInstanceId);
    iEventedState.Append("\">\n");

    if (iTransportStateOverride.Bytes() != 0) {
        AddStateVariable(Brn("TransportState"), iTransportStateOverride);
    }
    else {
        AddStateVariable(Brn("TransportState"), iTransportState);
    }
    AddStateVariable(Brn("TransportStatus"), iTransportStatus);
    AddStateVariable(Brn("CurrentMediaCategory"), iCurrentMediaCategory);
    AddStateVariable(Brn("PlaybackStorageMedium"), iPlaybackStorageMedium);
    AddStateVariable(Brn("NumberOfTracks"), iNumberOfTracks);
    AddStateVariable(Brn("CurrentTrack"), iCurrentTrack);
    AddStateVariable(Brn("CurrentTrackDuration"), iTrackDuration);
    AddStateVariable(Brn("CurrentMediaDuration"), iTrackDuration); // Media and Track durations are identical for us
    AddStateVariable(Brn("CurrentTrackURI"), iCurrentTrackUri);
    AddStateVariable(Brn("AVTransportURI"), iAvTransportUri);
    AddStateVariable(Brn("CurrentTrackMetaData"), iCurrentTrackMetaData);
    AddStateVariable(Brn("AVTransportURIMetaData"), iAvTransportUriMetaData);
    AddStateVariable(Brn("PossiblePlaybackStorageMedia"), iPossiblePlaybackStorageMedia);
    AddStateVariable(Brn("CurrentPlayMode"), iCurrentPlayMode);
    AddStateVariable(Brn("TransportPlaySpeed"), iTransportPlaySpeed);
    AddStateVariable(Brn("NextAVTransportURI"), iNextAvTransportUri);
    AddStateVariable(Brn("NextAVTransportURIMetaData"), iNextAvTransportUriMetaData);
    AddStateVariable(Brn("RecordStorageMedium"), iRecordStorageMedium);
    AddStateVariable(Brn("PossibleRecordStorageMedia"), iPossibleRecordStorageMedia);
    AddStateVariable(Brn("RecordMediumWriteStatus"), iRecordMediumWriteStatus);
    AddStateVariable(Brn("CurrentRecordQualityMode"), iCurrentRecordQualityMode);
    AddStateVariable(Brn("PossibleRecordQualityModes"), iPossibleRecordQualityModes);

    // End of event
    iEventedState.Append("    </InstanceID>\n</Event>\n");

    (void)SetPropertyLastChange(iEventedState);
}

void ProviderAvTransport::AddStateVariable(const Brx& aName, const Brx& aValue)
{
    iXmlEscapedStateVar.SetBytes(0);
    WriterBuffer writer(iXmlEscapedStateVar);
    Converter::ToXmlEscaped(writer, aValue);
    AddStateVariableEscaped(aName, iXmlEscapedStateVar);
}

void ProviderAvTransport::AddStateVariable(const Brx& aName, TUint aValue)
{
    Bws<Ascii::kMaxUintStringBytes> valBuf;
    Ascii::AppendDec(valBuf, aValue);
    AddStateVariableEscaped(aName, valBuf);
}

void ProviderAvTransport::AddStateVariableEscaped(const Brx& aName, const Brx& aValue)
{
    iEventedState.Append("        <");
    iEventedState.Append(aName);
    iEventedState.Append(" val=\"");
    iEventedState.Append(aValue);
    iEventedState.Append("\"/>\n");
}

void ProviderAvTransport::SecondsToTimeString(TUint aSeconds, Bwx& aTime)
{ // static
    const TUint seconds = aSeconds % 60;
    aSeconds -= seconds;
    const TUint minutes = (aSeconds % (60 * 60)) / 60;
    aSeconds -= minutes;
    const TUint hours = aSeconds / (60 * 60);

    aTime.SetBytes(0);
    Ascii::AppendDec(aTime, hours);
    aTime.Append(":");
    if (minutes < 10) {
        aTime.Append("0");
    }
    Ascii::AppendDec(aTime, minutes);
    aTime.Append(":");
    if (seconds < 10) {
        aTime.Append("0");
    }
    Ascii::AppendDec(aTime, seconds);
}

TUint ProviderAvTransport::TimeStringToSeconds(const Brx& aTime)
{ // static
    Parser parser(aTime);
    const TUint hours = Ascii::Uint(parser.Next(':'));
    const TUint minutes = Ascii::Uint(parser.Next(':'));
    parser.Set(parser.Remaining());
    TUint seconds;
    if (parser.Remaining().Bytes() > 2) {
        seconds = Ascii::Uint(parser.Next('.'));
    } else {
        seconds = Ascii::Uint(parser.Remaining());
    }
    if (minutes > 59 || seconds > 59) {
        THROW(AsciiError);
    }
    return (hours * 60 * 60) + (minutes * 60) + seconds;
}
