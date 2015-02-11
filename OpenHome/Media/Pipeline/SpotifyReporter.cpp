#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/SpotifyReporter.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Net/Private/XmlParser.h>

#include <limits>

using namespace OpenHome;
using namespace OpenHome::Media;


// SpotifyReporter

const Brn SpotifyReporter::kInterceptMode("Spotify");

SpotifyReporter::SpotifyReporter(IPipelineElementUpstream& aUpstreamElement, IPipelinePropertyObserver& aObserver)
    : iUpstreamElement(aUpstreamElement)
    , iPropertyObserver(aObserver)
    , iTrackDurationMs(0)
    , iTrackOffsetSubSamples(0)
    , iReporterSubSampleStart(0)
    , iChannels(0)
    , iSampleRate(0)
    , iSubSamples(0)
    , iInterceptMode(false)
    , iLock("SARL")
{
}

Msg* SpotifyReporter::Pull()
{
    Msg* msg = iUpstreamElement.Pull();
    (void)msg->Process(*this);
    return msg;
}

TUint64 SpotifyReporter::SubSamples()
{
    AutoMutex a(iLock);
    return iSubSamples;
}

TUint64 SpotifyReporter::SubSamplesDiff(TUint64 aPrevSubSamples)
{
    AutoMutex a(iLock);
    ASSERT(iSubSamples > aPrevSubSamples);
    return iSubSamples - aPrevSubSamples;
}

void SpotifyReporter::TrackChanged(TrackFactory& aTrackFactory, IPipelineIdProvider& /*aIdProvider*/, const Brx& aMetadata, TUint aStartMs)
{
    iTrackOffsetSubSamples = aStartMs;
    Brn duration = Net::XmlParserBasic::FindAttribute("res", "duration", aMetadata);
    iTrackDurationMs = ParseDurationMs(duration);
    iReporterSubSampleStart = iSubSamples;

    // FIXME - if we retrieved a new track ID by calling NextTrackId(), seeking
    // (and stopping) would break as SourceSpotify would be aware of the new
    // track, but the rest of the pipeline would not.
    // As a hack, reuse the pipeline ID of the last MsgTrack that was seen.
    Track* track = aTrackFactory.CreateTrack(Brn("spotify://"), aMetadata);
    iPropertyObserver.NotifyTrack(*track, kInterceptMode, true);
    track->RemoveRef();
}

void SpotifyReporter::NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream)
{
    iPropertyObserver.NotifyTrack(aTrack, aMode, aStartOfStream);
}

void SpotifyReporter::NotifyMetaText(const Brx& aText)
{
    iPropertyObserver.NotifyMetaText(aText);
}

void SpotifyReporter::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    iLock.Wait();
    if (iInterceptMode) {
        // Adjust to expected time based on number of (sub)samples seen since
        // TrackChanged() or a MsgDecodedStream.
        TUint durationSeconds = iTrackDurationMs/1000;
        TUint64 subSamples = (iSubSamples-iReporterSubSampleStart)+iTrackOffsetSubSamples;
        TUint64 seconds = subSamples/iChannels/iSampleRate;

        iLock.Signal();
        ASSERT(seconds <= std::numeric_limits<TUint>::max());
        TUint secondsCast = static_cast<TUint>(seconds);
        iPropertyObserver.NotifyTime(secondsCast, durationSeconds);
    }
    else {
        iLock.Signal();
        iPropertyObserver.NotifyTime(aSeconds, aTrackDurationSeconds);
    }
}

void SpotifyReporter::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    iPropertyObserver.NotifyStreamInfo(aStreamInfo);
}

Msg* SpotifyReporter::ProcessMsg(MsgMode* aMsg)
{
    AutoMutex a(iLock);
    if (aMsg->Mode() == kInterceptMode) {
        iInterceptMode = true;
    }
    else {
        iInterceptMode = false;
    }
    iTrackOffsetSubSamples = 0;
    iReporterSubSampleStart = 0;
    iChannels = 0;
    iSampleRate = 0;
    iSubSamples = 0;
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgSession* aMsg)
{
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgEncodedStream* aMsg)
{
    ASSERTS(); // don't expect to see MsgEncodedStream at this stage of the pipeline
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return NULL;
}

Msg* SpotifyReporter::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // don't expect to see MsgFlush at this stage of the pipeline
    return NULL;
}

Msg* SpotifyReporter::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& streamInfo = aMsg->StreamInfo();
    AutoMutex a(iLock);
    iChannels = streamInfo.NumChannels();
    iSampleRate = streamInfo.SampleRate();
    ASSERT(iChannels != 0);
    ASSERT(iSampleRate != 0);

    iTrackOffsetSubSamples = streamInfo.SampleStart()*iChannels;
    iReporterSubSampleStart = iSubSamples;
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgAudioPcm* aMsg)
{
    ASSERT(iChannels != 0);
    ASSERT(iSampleRate != 0);
    TUint samples = aMsg->Jiffies()/Jiffies::JiffiesPerSample(iSampleRate);
    AutoMutex a(iLock);
    TUint64 subSamplesPrev = iSubSamples;
    iSubSamples += samples*iChannels;
    ASSERT(iSubSamples > subSamplesPrev); // Overflow not handled.
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgSilence* aMsg)
{
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // don't expect to see MsgPlayable in the pipeline
    return NULL;
}

Msg* SpotifyReporter::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}

TUint SpotifyReporter::ParseDurationMs(const Brx& aDuration)
{
    // H+:MM:SS[.F0/F1]
    Parser p(aDuration);
    TUint hours = Ascii::Uint(p.Next(':'));
    TUint minutes = Ascii::Uint(p.Next(':'));
    TUint seconds = Ascii::Uint(p.Next('.'));
    TUint partialSeconds = 0;
    TUint partialSecondsDivisor = 0;
    if (!p.Finished()) {
        partialSeconds = Ascii::Uint(p.Next('/'));
        partialSecondsDivisor = Ascii::Uint(p.Next());
    }
    ASSERT(p.Finished());

    TUint milliseconds = hours*3600*1000;
    milliseconds += minutes*60*1000;
    milliseconds += seconds*1000;

    if (partialSeconds != 0) {
        ASSERT(partialSecondsDivisor == 1000);
        milliseconds += partialSeconds;
    }

    return milliseconds;
}
