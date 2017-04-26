#include <OpenHome/Av/ProviderTransport.h>
#include <Generated/DvAvOpenhomeOrgTransport1.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/Seeker.h> // for Seeker exceptions
#include <OpenHome/Media/Pipeline/Pipeline.h> // for PipelineStreamNotPausable

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
const TUint ProviderTransport::kRepeatOff    = 0;
const TUint ProviderTransport::kRepeatOnAll  = 1;
const TUint ProviderTransport::kShuffleOff   = 0;
const TUint ProviderTransport::kShuffleOnAll = 1;

ProviderTransport::ProviderTransport(Net::DvDevice& aDevice,
                                     PipelineManager& aPipeline,
                                     ITransportActivator& aTransportActivator,
                                     ITransportRepeatRandom& aTransportRepeatRandom)
    : DvProviderAvOpenhomeOrgTransport1(aDevice)
    , iLock("PTPR")
    , iPipeline(aPipeline)
    , iTransportActivator(aTransportActivator)
    , iTransportRepeatRandom(aTransportRepeatRandom)
    , iTransportState(EPipelineStopped)
    , iStreamId(IPipelineIdProvider::kStreamIdInvalid)
    , iModes(kModesGranularity)
{
    EnablePropertyModes();
    EnablePropertyNextAvailable();
    EnablePropertyPreviousAvailable();
    EnablePropertyRepeatAvailable();
    EnablePropertyShuffleAvailable();
    EnablePropertyStreamId();
    EnablePropertySeekable();
    EnablePropertyPausable();
    EnablePropertyTransportState();
    EnablePropertyRepeat();
    EnablePropertyShuffle();

    EnableActionPlayAs();
    EnableActionPlay();
    EnableActionPause();
    EnableActionStop();
    EnableActionNext();
    EnableActionPrevious();
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

    (void)SetPropertyNextAvailable(false);
    (void)SetPropertyPreviousAvailable(false);
    (void)SetPropertyRepeatAvailable(false);
    (void)SetPropertyShuffleAvailable(false);
    (void)SetPropertyStreamId(iStreamId);
    (void)SetPropertySeekable(false);
    (void)SetPropertyPausable(false);
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

void ProviderTransport::NotifyMode(const Brx& /*aMode*/, const Media::ModeInfo& aInfo)
{
    PropertiesLock();
    (void)SetPropertyNextAvailable(aInfo.SupportsNext());
    (void)SetPropertyPreviousAvailable(aInfo.SupportsPrev());
    (void)SetPropertyRepeatAvailable(aInfo.SupportsRepeat());
    (void)SetPropertyShuffleAvailable(aInfo.SupportsRandom());
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
    (void)SetPropertySeekable(aStreamInfo.Seekable());
    (void)SetPropertyPausable(!aStreamInfo.Live());
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
    (void)SetPropertyRepeat(aRepeat? kRepeatOnAll : kRepeatOff);
}

void ProviderTransport::TransportRandomChanged(TBool aRandom)
{
    (void)SetPropertyShuffle(aRandom? kShuffleOnAll : kShuffleOff);
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
    iPipeline.Play();
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::Pause(IDvInvocation& aInvocation)
{
    try {
        iPipeline.Pause();
    }
    catch (PipelineStreamNotPausable&) {
        aInvocation.Error(kCodeNotSupportedByStream, kMsgNotSupportedByStream);
    }
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::Stop(IDvInvocation& aInvocation)
{
    iPipeline.Stop();
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::Next(IDvInvocation& aInvocation)
{
    AutoMutex _(iLock);
    iPipeline.Next();
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::Previous(IDvInvocation& aInvocation)
{
    AutoMutex _(iLock);
    iPipeline.Prev();
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
                                            TUint aStreamId, TUint aSecondsAbsolute)
{
    try {
        iPipeline.Seek(aStreamId, aSecondsAbsolute);
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
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::SeekSecondRelative(IDvInvocation& aInvocation,
                                            TUint aStreamId, TInt aSecondsRelative)
{
    iLock.Wait();
    TUint seconds = aSecondsRelative + iTrackPosSeconds;
    if (aSecondsRelative < 0 && -aSecondsRelative >(TInt)iTrackPosSeconds) {
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
                                 IDvInvocationResponseBool& aNextAvailable,
                                 IDvInvocationResponseBool& aPreviousAvailable,
                                 IDvInvocationResponseBool& aRepeatAvailable,
                                 IDvInvocationResponseBool& aShuffleAvailable)
{
    AutoMutex _(iLock);
    TBool next, prev;
    TUint repeat, shuffle;
    GetPropertyNextAvailable(next);
    GetPropertyPreviousAvailable(prev);
    GetPropertyRepeat(repeat);
    GetPropertyShuffle(shuffle);
    aInvocation.StartResponse();
    aNextAvailable.Write(next);
    aPreviousAvailable.Write(prev);
    aRepeatAvailable.Write(repeat != kRepeatOff);
    aShuffleAvailable.Write(shuffle != kShuffleOff);
    aInvocation.EndResponse();
}

void ProviderTransport::StreamInfo(IDvInvocation& aInvocation,
                                   IDvInvocationResponseUint& aStreamId,
                                   IDvInvocationResponseBool& aSeekable,
                                   IDvInvocationResponseBool& aPausable)
{
    AutoMutex _(iLock);
    TUint streamId;
    TBool seekable, pausable;
    GetPropertyStreamId(streamId);
    GetPropertySeekable(seekable);
    GetPropertyPausable(pausable);
    aInvocation.StartResponse();
    aStreamId.Write(streamId);
    aSeekable.Write(seekable);
    aPausable.Write(pausable);
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

void ProviderTransport::Repeat(IDvInvocation& aInvocation, IDvInvocationResponseUint& aRepeat)
{
    AutoMutex _(iLock);
    TUint repeat;
    GetPropertyRepeat(repeat);
    aInvocation.StartResponse();
    aRepeat.Write(repeat);
    aInvocation.EndResponse();
}

void ProviderTransport::Shuffle(IDvInvocation& aInvocation, IDvInvocationResponseUint& aRandom)
{
    AutoMutex _(iLock);
    TUint shuffle;
    GetPropertyShuffle(shuffle);
    aInvocation.StartResponse();
    aRandom.Write(shuffle);
    aInvocation.EndResponse();
}
