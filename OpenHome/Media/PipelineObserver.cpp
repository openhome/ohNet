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

void NullPipelineObserver::NotifyTrack(Track& /*aTrack*/, const Brx& /*aMode*/)
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

void LoggingPipelineObserver::NotifyTrack(Track& aTrack, const Brx& aMode)
{
    if (!iEnable) {
        return;
    }
    Log::Print("Pipeline report property: TRACK {uri=");
    Log::Print(aTrack.Uri());
    //Log::Print("; metadata=");
    //Log::Print(aTrack.MetaData());
    Log::Print("; mode=");
    Log::Print(aMode);
    Log::Print("; trackId=%u}\n", aTrack.Id());
}

void LoggingPipelineObserver::NotifyMetaText(const Brx& aText)
{
    if (!iEnable) {
        return;
    }
    Log::Print("Pipeline report property: METATEXT {");
    Log::Print(aText);
    Log::Print("}\n");
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
    Log::Print("Pipeline report property: FORMAT {bitRate=%u; bitDepth=%u, sampleRate=%u, numChannels=%u, codec=",
           aStreamInfo.BitRate(), aStreamInfo.BitDepth(), aStreamInfo.SampleRate(), aStreamInfo.NumChannels());
    Log::Print(aStreamInfo.CodecName());
    Log::Print("; trackLength=%llx, lossless=%u}\n", aStreamInfo.TrackLength(), aStreamInfo.Lossless());
}
