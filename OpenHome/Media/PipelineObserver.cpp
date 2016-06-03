#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// TransportState

const TChar* TransportState::FromPipelineState(EPipelineState aState)
{ // static
    const TChar* state;
    switch (aState)
    {
    case EPipelinePlaying:
        state = "Playing";
        break;
    case EPipelinePaused:
        state = "Paused";
        break;
    case EPipelineStopped:
        state = "Stopped";
        break;
    case EPipelineBuffering:
        state = "Buffering";
        break;
    case EPipelineWaiting:
        state = "Waiting";
        break;
    default:
        ASSERTS();
        state = "";
        break;
    }
    return state;
}

    
// NullPipelineObserver

void NullPipelineObserver::NotifyPipelineState(EPipelineState /*aState*/)
{
}

void NullPipelineObserver::NotifyMode(const Brx& /*aMode*/, const ModeInfo& /*aInfo*/)
{
}

void NullPipelineObserver::NotifyTrack(Track& /*aTrack*/, const Brx& /*aMode*/, TBool /*aStartOfStream*/)
{
}

void NullPipelineObserver::NotifyMetaText(const Brx& /*aText*/)
{
}

void NullPipelineObserver::NotifyTime(TUint /*aSeconds*/, TUint /*aTrackDurationSeconds*/)
{
}


void NullPipelineObserver::NotifyStreamInfo(const DecodedStreamInfo& /*aStreamInfo*/)
{
}


// LoggingPipelineObserver

LoggingPipelineObserver::LoggingPipelineObserver()
    : iEnable(true)
{
}

void LoggingPipelineObserver::Enable(TBool aEnable)
{
    iEnable = aEnable;
}

void LoggingPipelineObserver::NotifyPipelineState(EPipelineState aState)
{
    if (!iEnable) {
        return;
    }
    const char* state = "";
    switch (aState)
    {
    case EPipelinePlaying:
        state = "playing";
        break;
    case EPipelinePaused:
        state = "paused";
        break;
    case EPipelineStopped:
        state = "stopped";
        break;
    case EPipelineBuffering:
        state = "buffering";
        break;
    case EPipelineWaiting:
        state = "waiting";
        break;
    default:
        ASSERTS();
    }
    Log::Print("Pipeline state change: %s\n", state);
}

void LoggingPipelineObserver::NotifyMode(const Brx& aMode, const ModeInfo& aInfo)
{
    if (!iEnable) {
        return;
    }
    Log::Print("Pipeline report property: MODE {mode=%.*s; supportsLatency=%u; supportsNext=%u; supportsPrev=%u}\n",
               PBUF(aMode), aInfo.SupportsLatency(), aInfo.SupportsNext(), aInfo.SupportsPrev());
}

void LoggingPipelineObserver::NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream)
{
    if (!iEnable) {
        return;
    }
    Log::Print("Pipeline report property: TRACK {uri=%.*s; mode=%.*s; trackId=%u; startOfStream=%u}\n",
               PBUF(aTrack.Uri()), PBUF(aMode), aTrack.Id(), aStartOfStream);
}

void LoggingPipelineObserver::NotifyMetaText(const Brx& aText)
{
    if (!iEnable) {
        return;
    }
    Log::Print("Pipeline report property: METATEXT {%.*s}\n", PBUF(aText));
}

void LoggingPipelineObserver::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    if (!iEnable) {
        return;
    }
    Log::Print("Pipeline report property: TIME {secs=%u; duration=%u}\n", aSeconds, aTrackDurationSeconds);
}

void LoggingPipelineObserver::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    if (!iEnable) {
        return;
    }
    Log::Print("Pipeline report property: FORMAT {bitRate=%u; bitDepth=%u, sampleRate=%u, numChannels=%u, codec=%.*s; trackLength=%llx, lossless=%u}\n",
               aStreamInfo.BitRate(), aStreamInfo.BitDepth(), aStreamInfo.SampleRate(), aStreamInfo.NumChannels(),
               PBUF(aStreamInfo.CodecName()), aStreamInfo.TrackLength(), aStreamInfo.Lossless());
}
