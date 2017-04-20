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
    EnablePropertyPrevAvailable();
    EnablePropertyRepeatAvailable();
    EnablePropertyRandomAvailable();
    EnablePropertyStreamId();
    EnablePropertySeekable();
    EnablePropertyPausable();
    EnablePropertyTransportState();
    EnablePropertyRepeat();
    EnablePropertyRandom();

    EnableActionPlayAs();
    EnableActionPlay();
    EnableActionPause();
    EnableActionStop();
    EnableActionNext();
    EnableActionPrev();
    EnableActionSetRepeat();
    EnableActionSetRandom();
    EnableActionSeekSecondsAbsolute();
    EnableActionSeekSecondsRelative();
    EnableActionTransportState();
    EnableActionModes();
    EnableActionModeInfo();
    EnableActionStreamInfo();
    EnableActionStreamId();
    EnableActionRepeat();
    EnableActionRandom();

    iPipeline.AddObserver(*static_cast<Media::IPipelineObserver*>(this));
    iPipeline.AddObserver(*static_cast<Media::IModeObserver*>(this));
    iTransportRepeatRandom.AddObserver(*this);

    (void)SetPropertyNextAvailable(false);
    (void)SetPropertyPrevAvailable(false);
    (void)SetPropertyRepeatAvailable(false);
    (void)SetPropertyRandomAvailable(false);
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
    (void)SetPropertyPrevAvailable(aInfo.SupportsPrev());
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
    (void)SetPropertyRepeat(aRepeat);
}

void ProviderTransport::TransportRandomChanged(TBool aRandom)
{
    (void)SetPropertyRandom(aRandom);
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

void ProviderTransport::Next(IDvInvocation& aInvocation, TUint aStreamId)
{
    AutoMutex _(iLock);
    if (iStreamId != aStreamId) {
        aInvocation.Error(kCodeBadStreamId, kMsgBadStreamId);
    }
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iPipeline.Next();
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::Prev(IDvInvocation& aInvocation, TUint aStreamId)
{
    AutoMutex _(iLock);
    if (iStreamId != aStreamId) {
        aInvocation.Error(kCodeBadStreamId, kMsgBadStreamId);
    }
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
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

void ProviderTransport::SetRandom(IDvInvocation& aInvocation, TBool aRandom)
{
    iTransportRepeatRandom.SetRandom(aRandom);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}

void ProviderTransport::SeekSecondsAbsolute(IDvInvocation& aInvocation,
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

void ProviderTransport::SeekSecondsRelative(IDvInvocation& aInvocation,
                                            TUint aStreamId, TInt aSecondsRelative)
{
    iLock.Wait();
    TUint seconds = aSecondsRelative + iTrackPosSeconds;
    if (aSecondsRelative < 0 && -aSecondsRelative >(TInt)iTrackPosSeconds) {
        seconds = 0;
    }
    iLock.Signal();
    SeekSecondsAbsolute(aInvocation, aStreamId, seconds);
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
                                 IDvInvocationResponseBool& aPrevAvailable,
                                 IDvInvocationResponseBool& aRepeatAvailable,
                                 IDvInvocationResponseBool& aRandomAvailable)
{
    AutoMutex _(iLock);
    TBool next, prev, repeat, random;
    GetPropertyNextAvailable(next);
    GetPropertyPrevAvailable(prev);
    GetPropertyRepeat(repeat);
    GetPropertyRandom(random);
    aInvocation.StartResponse();
    aNextAvailable.Write(next);
    aPrevAvailable.Write(prev);
    aRepeatAvailable.Write(repeat);
    aRandomAvailable.Write(random);
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

void ProviderTransport::Repeat(IDvInvocation& aInvocation, IDvInvocationResponseBool& aRepeat)
{
    AutoMutex _(iLock);
    TBool repeat;
    GetPropertyRepeat(repeat);
    aInvocation.StartResponse();
    aRepeat.Write(repeat);
    aInvocation.EndResponse();
}

void ProviderTransport::Random(IDvInvocation& aInvocation, IDvInvocationResponseBool& aRandom)
{
    AutoMutex _(iLock);
    TBool random;
    GetPropertyRandom(random);
    aInvocation.StartResponse();
    aRandom.Write(random);
    aInvocation.EndResponse();
}
