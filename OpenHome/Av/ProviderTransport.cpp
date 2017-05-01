#include <OpenHome/Av/ProviderTransport.h>
#include <Generated/DvAvOpenhomeOrgTransport1.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/Seeker.h> // for Seeker exceptions
#include <OpenHome/Media/Pipeline/Pipeline.h> // for PipelineStreamNotPausable
#include <OpenHome/PowerManager.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Net;
using namespace OpenHome::Media;

static const TUint kCodeNotSupportedByMode = 801;
static const Brn kMsgNotSupportedByMode("Action not supported by current mode");
static const TUint kCodeNotSupportedByStream = 802;
static const Brn kMsgNotSupportedByStream("Action not supported by current stream");
static const TUint kCodeBadStreamId = 803;
static const Brn kMsgBadStreamId("Stream id not current");
static const TUint kSeekFailureCode = 804;
static const Brn kSeekFailureMsg("Seek failed");

const TUint ProviderTransport::kModesGranularity = 1024;

ProviderTransport::ProviderTransport(Net::DvDevice& aDevice,
                                     PipelineManager& aPipeline,
                                     IPowerManager& aPowerManager,
                                     ITransportActivator& aTransportActivator,
                                     ITransportRepeatRandom& aTransportRepeatRandom)
    : DvProviderAvOpenhomeOrgTransport1(aDevice)
    , iLock("PTR1")
    , iPipeline(aPipeline)
    , iPowerManager(aPowerManager)
    , iTransportActivator(aTransportActivator)
    , iTransportRepeatRandom(aTransportRepeatRandom)
    , iLockTransportControls("PTR2")
    , iTransportState(EPipelineStopped)
    , iStreamId(IPipelineIdProvider::kStreamIdInvalid)
    , iModes(kModesGranularity)
{
    EnablePropertyModes();
    EnablePropertyCanSkipNext();
    EnablePropertyCanSkipPrevious();
    EnablePropertyCanRepeat();
    EnablePropertyCanShuffle();
    EnablePropertyStreamId();
    EnablePropertyCanSeek();
    EnablePropertyCanPause();
    EnablePropertyTransportState();
    EnablePropertyRepeat();
    EnablePropertyShuffle();

    EnableActionPlayAs();
    EnableActionPlay();
    EnableActionPause();
    EnableActionStop();
    EnableActionSkipNext();
    EnableActionSkipPrevious();
    EnableActionSetRepeat();
    EnableActionSetShuffle();
    EnableActionSeekSecondAbsolute();
    EnableActionSeekSecondRelative();
    EnableActionTransportState();
    EnableActionModes();
    EnableActionModeInfo();
    EnableActionStreamInfo();
    EnableActionStreamId();
    EnableActionRepeat();
    EnableActionShuffle();

    iPipeline.AddObserver(*static_cast<Media::IPipelineObserver*>(this));
    iPipeline.AddObserver(*static_cast<Media::IModeObserver*>(this));
    iTransportRepeatRandom.AddObserver(*this);

    (void)SetPropertyCanSkipNext(false);
    (void)SetPropertyCanSkipPrevious(false);
    (void)SetPropertyCanRepeat(false);
    (void)SetPropertyCanShuffle(false);
    (void)SetPropertyStreamId(iStreamId);
    (void)SetPropertyCanSeek(false);
    (void)SetPropertyCanPause(false);
    Brn state(TransportState::FromPipelineState(iTransportState));
    (void)SetPropertyTransportState(state);
}

void ProviderTransport::Start()
{
    (void)SetPropertyModes(iModes.Buffer());
}

void ProviderTransport::NotifyPipelineState(EPipelineState aState)
{
    AutoMutex _(iLock);
    iTransportState = aState;
    Brn state(TransportState::FromPipelineState(iTransportState));
    (void)SetPropertyTransportState(state);
}

void ProviderTransport::NotifyMode(const Brx& /*aMode*/,
                                   const Media::ModeInfo& aInfo,
                                   const Media::ModeTransportControls& aTransportControls)
{
    {
        AutoMutex _(iLockTransportControls);
        iTransportControls = aTransportControls;
    }
    PropertiesLock();
    (void)SetPropertyCanSkipNext(aInfo.SupportsNext());
    (void)SetPropertyCanSkipPrevious(aInfo.SupportsPrev());
    (void)SetPropertyCanRepeat(aInfo.SupportsRepeat());
    (void)SetPropertyCanShuffle(aInfo.SupportsRandom());
    PropertiesUnlock();
}

void ProviderTransport::NotifyTrack(Track& /*aTrack*/, const Brx& /*aMode*/, TBool /*aStartOfStream*/)
{
    AutoMutex _(iLock);
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
}

void ProviderTransport::NotifyMetaText(const Brx& /*aText*/)
{
}

void ProviderTransport::NotifyTime(TUint aSeconds, TUint /*aTrackDurationSeconds*/)
{
    AutoMutex _(iLock);
    iTrackPosSeconds = aSeconds;
}

void ProviderTransport::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    AutoMutex _(iLock);
    iStreamId = aStreamInfo.StreamId();
    (void)SetPropertyStreamId(iStreamId);
    (void)SetPropertyCanSeek(aStreamInfo.Seekable());
    (void)SetPropertyCanPause(!aStreamInfo.Live());
}

void ProviderTransport::NotifyModeAdded(const Brx& aMode)
{
    if (iModes.Buffer().Bytes() > 0) {
        iModes.Write(' ');
    }
    iModes.Write(aMode);
}

void ProviderTransport::TransportRepeatChanged(TBool aRepeat)
{
    (void)SetPropertyRepeat(aRepeat);
}

void ProviderTransport::TransportRandomChanged(TBool aRandom)
{
    (void)SetPropertyShuffle(aRandom);
}

void ProviderTransport::PlayAs(IDvInvocation& aInvocation, const Brx& aMode, const Brx& aCommand)
{
    if (!iTransportActivator.TryActivate(aMode)) {
        aInvocation.Error(kCodeNotSupportedByMode, kMsgNotSupportedByMode);
    }
    iPipeline.PlayAs(aMode, aCommand);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::Play(IDvInvocation& aInvocation)
{
    iPowerManager.StandbyDisable(StandbyDisableReason::User);
    {
        AutoMutex _(iLockTransportControls);
        auto f = iTransportControls.Play();
        if (f) {
            f();
        }
        else {
            iPipeline.Play();
        }
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::Pause(IDvInvocation& aInvocation)
{
    {
        AutoMutex _(iLockTransportControls);
        auto f = iTransportControls.Pause();
        if (f) {
            f();
        }
        else {
            try {
                iPipeline.Pause();
            }
            catch (PipelineStreamNotPausable&) {
                aInvocation.Error(kCodeNotSupportedByStream, kMsgNotSupportedByStream);
            }
        }
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::Stop(IDvInvocation& aInvocation)
{
    {
        AutoMutex _(iLockTransportControls);
        auto f = iTransportControls.Stop();
        if (f) {
            f();
        }
        else {
            iPipeline.Stop();
        }
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::SkipNext(IDvInvocation& aInvocation)
{
    iPowerManager.StandbyDisable(StandbyDisableReason::User);
    {
        AutoMutex _(iLockTransportControls);
        auto f = iTransportControls.Next();
        if (f) {
            f();
        }
        else {
            iPipeline.Next();
        }
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::SkipPrevious(IDvInvocation& aInvocation)
{
    iPowerManager.StandbyDisable(StandbyDisableReason::User);
    {
        AutoMutex _(iLockTransportControls);
        auto f = iTransportControls.Prev();
        if (f) {
            f();
        }
        else {
            iPipeline.Prev();
        }
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::SetRepeat(IDvInvocation& aInvocation, TBool aRepeat)
{
    iTransportRepeatRandom.SetRepeat(aRepeat);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::SetShuffle(IDvInvocation& aInvocation, TBool aShuffle)
{
    iTransportRepeatRandom.SetRandom(aShuffle);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::SeekSecondAbsolute(IDvInvocation& aInvocation,
                                            TUint aStreamId, TUint aSecondAbsolute)
{
    iPowerManager.StandbyDisable(StandbyDisableReason::User);
    {
        AutoMutex _(iLockTransportControls);
        auto f = iTransportControls.Seek();
        if (f) {
            f(aSecondAbsolute);
        }
        else {
            try {
                iPipeline.Seek(aStreamId, aSecondAbsolute);
                iPipeline.Play();
            }
            catch (SeekStreamInvalid&) {
                aInvocation.Error(kCodeBadStreamId, kMsgBadStreamId);
            }
            catch (SeekAlreadyInProgress&) {
                aInvocation.Error(kSeekFailureCode, kSeekFailureMsg);
            }
            catch (SeekStreamNotSeekable&) {
                aInvocation.Error(kSeekFailureCode, kSeekFailureMsg);
            }
            catch (SeekPosInvalid&) {
                aInvocation.Error(kSeekFailureCode, kSeekFailureMsg);
            }
        }
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::SeekSecondRelative(IDvInvocation& aInvocation,
                                            TUint aStreamId, TInt aSecondRelative)
{
    iLock.Wait();
    TUint seconds = aSecondRelative + iTrackPosSeconds;
    if (aSecondRelative < 0 && -aSecondRelative >(TInt)iTrackPosSeconds) {
        seconds = 0;
    }
    iLock.Signal();
    SeekSecondAbsolute(aInvocation, aStreamId, seconds);
}

void ProviderTransport::TransportState(IDvInvocation& aInvocation, IDvInvocationResponseString& aState)
{
    AutoMutex _(iLock);
    aInvocation.StartResponse();
    Brn state(TransportState::FromPipelineState(iTransportState));
    aState.Write(state);
    aState.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderTransport::Modes(IDvInvocation& aInvocation, IDvInvocationResponseString& aModes)
{
    aInvocation.StartResponse();
    aModes.Write(iModes.Buffer());
    aModes.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderTransport::ModeInfo(IDvInvocation& aInvocation,
                                 IDvInvocationResponseBool& aCanSkipNext,
                                 IDvInvocationResponseBool& aCanSkipPrevious,
                                 IDvInvocationResponseBool& aCanRepeat,
                                 IDvInvocationResponseBool& aCanShuffle)
{
    AutoMutex _(iLock);
    TBool next, prev, repeat, shuffle;
    GetPropertyCanSkipNext(next);
    GetPropertyCanSkipPrevious(prev);
    GetPropertyCanRepeat(repeat);
    GetPropertyCanShuffle(shuffle);
    aInvocation.StartResponse();
    aCanSkipNext.Write(next);
    aCanSkipPrevious.Write(prev);
    aCanRepeat.Write(repeat);
    aCanShuffle.Write(shuffle);
    aInvocation.EndResponse();
}

void ProviderTransport::StreamInfo(IDvInvocation& aInvocation,
                                   IDvInvocationResponseUint& aStreamId,
                                   IDvInvocationResponseBool& aCanSeek,
                                   IDvInvocationResponseBool& aCanPause)
{
    AutoMutex _(iLock);
    TUint streamId;
    TBool seekable, pausable;
    GetPropertyStreamId(streamId);
    GetPropertyCanSeek(seekable);
    GetPropertyCanPause(pausable);
    aInvocation.StartResponse();
    aStreamId.Write(streamId);
    aCanSeek.Write(seekable);
    aCanPause.Write(pausable);
    aInvocation.EndResponse();
}

void ProviderTransport::StreamId(IDvInvocation& aInvocation, IDvInvocationResponseUint& aStreamId)
{
    AutoMutex _(iLock);
    TUint streamId;
    GetPropertyStreamId(streamId);
    aInvocation.StartResponse();
    aStreamId.Write(streamId);
    aInvocation.EndResponse();
}

void ProviderTransport::Repeat(IDvInvocation& aInvocation, IDvInvocationResponseBool& aRepeat)
{
    AutoMutex _(iLock);
    TBool repeat;
    GetPropertyRepeat(repeat);
    aInvocation.StartResponse();
    aRepeat.Write(repeat);
    aInvocation.EndResponse();
}

void ProviderTransport::Shuffle(IDvInvocation& aInvocation, IDvInvocationResponseBool& aRandom)
{
    AutoMutex _(iLock);
    TBool shuffle;
    GetPropertyShuffle(shuffle);
    aInvocation.StartResponse();
    aRandom.Write(shuffle);
    aInvocation.EndResponse();
}
