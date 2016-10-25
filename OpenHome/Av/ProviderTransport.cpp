#include <OpenHome/Av/ProviderTransport.h>
#include <Generated/DvAvOpenhomeOrgTransport1.h>
#include <OpenHome/Av/TransportControl.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/Seeker.h> // for Seeker exceptions
#include <OpenHome/Media/Pipeline/Pipeline.h> // for PipelineStreamNotPausable

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Net;
using namespace OpenHome::Media;

//static const TUint kCodeNotSupportedByMode = 801;
//static const Brn kMsgNotSupportedByMode("Action not supported by current mode");
static const TUint kCodeNotSupportedByStream = 802;
static const Brn kMsgNotSupportedByStream("Action not supported by current stream");
static const TUint kCodeBadStreamId = 803;
static const Brn kMsgBadStreamId("Stream id not current");
static const TUint kSeekFailureCode = 804;
static const Brn kSeekFailureMsg("Seek failed");

ProviderTransport::ProviderTransport(Net::DvDevice& aDevice, PipelineManager& aPipeline)
    : DvProviderAvOpenhomeOrgTransport1(aDevice)
    , iLock("PTPR")
    , iPipeline(aPipeline)
    , iStreamId(IPipelineIdProvider::kStreamIdInvalid)
{
    EnablePropertyModes();
    EnablePropertyModeCount();
    EnablePropertyTrackCount();
    EnablePropertyMode();
    EnablePropertySequenceNumbers();
    EnablePropertyStreamCount();
    EnablePropertyMetatextCount();
    EnablePropertyNextAvailable();
    EnablePropertyPrevAvailable();
    EnablePropertyStreamId();
    EnablePropertyDuration();
    EnablePropertySeekable();
    EnablePropertyPausable();
    EnablePropertyBitRate();
    EnablePropertyBitDepth();
    EnablePropertySampleRate();
    EnablePropertyLossless();
    EnablePropertyCodecName();
    EnablePropertyMetatext();
    EnablePropertyTransportState();

    EnableActionPlayAs();
    EnableActionPlay();
    EnableActionPause();
    EnableActionStop();
    EnableActionNext();
    EnableActionPrev();
    EnableActionSeekSecondsAbsolute();
    EnableActionSeekSecondsRelative();
    EnableActionTransportState();
    EnableActionModes();
    EnableActionCounters();
    EnableActionModeInfo();
    EnableActionTrackInfo();
    EnableActionStreamInfo();
    EnableActionStreamId();

    // FIXME - can we rely on observer callbacks initialising all properties?
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
}

void ProviderTransport::PlayAs(IDvInvocation& /*aInvocation*/, const Brx& /*aMode*/, const Brx& /*aCommand*/)
{
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

void ProviderTransport::Modes(IDvInvocation& /*aInvocation*/, IDvInvocationResponseString& /*aModes*/)
{
}

void ProviderTransport::Counters(IDvInvocation& /*aInvocation*/,
                                 IDvInvocationResponseUint& /*aModeCount*/, IDvInvocationResponseUint& /*aTrackCount*/,
                                 IDvInvocationResponseUint& /*aStreamCount*/, IDvInvocationResponseUint& /*aMetatextCount*/)
{
}

void ProviderTransport::ModeInfo(IDvInvocation& /*aInvocation*/,
                                 IDvInvocationResponseBool& /*aNextAvailable*/, IDvInvocationResponseBool& /*aPrevAvailable*/)
{
}

void ProviderTransport::TrackInfo(IDvInvocation& /*aInvocation*/,
                                  IDvInvocationResponseString& /*aUri*/, IDvInvocationResponseString& /*aMetadata*/)
{
}

void ProviderTransport::StreamInfo(IDvInvocation& /*aInvocation*/,
                                   IDvInvocationResponseUint& /*aStreamId*/, IDvInvocationResponseString& /*aUri*/,
                                   IDvInvocationResponseString& /*aMetadata*/, IDvInvocationResponseBool& /*aSeekable*/,
                                   IDvInvocationResponseBool& /*aPausable*/, IDvInvocationResponseUint& /*aDuration*/,
                                   IDvInvocationResponseUint& /*aBitRate*/, IDvInvocationResponseUint& /*aBitDepth*/,
                                   IDvInvocationResponseUint& /*aSampleRate*/, IDvInvocationResponseBool& /*aLossless*/,
                                   IDvInvocationResponseString& /*aCodecName*/)
{
}

void ProviderTransport::StreamId(IDvInvocation& /*aInvocation*/, IDvInvocationResponseUint& /*aStreamId*/)
{
}

void ProviderTransport::Metatext(IDvInvocation& /*aInvocation*/, IDvInvocationResponseString& /*aMetatext*/)
{
}
