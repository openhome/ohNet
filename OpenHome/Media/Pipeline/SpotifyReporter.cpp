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

SpotifyReporter::SpotifyReporter(IPipelineElementUpstream& aUpstreamElement, MsgFactory& aMsgFactory, IPipelinePropertyObserver& aObserver)
    : iUpstreamElement(aUpstreamElement)
    , iMsgFactory(aMsgFactory)
    , iPropertyObserver(aObserver)
    , iTrackDurationMs(0)
    , iTrackOffsetSubSamples(0)
    , iReporterSubSampleStart(0)
    , iTrackPending(nullptr)
    , iMsgDecodedStreamPending(false)
    , iDecodedStream(nullptr)
    , iChannels(0)
    , iSampleRate(0)
    , iSubSamples(0)
    , iInterceptMode(false)
    , iLock("SARL")
{
}

SpotifyReporter::~SpotifyReporter()
{
    if (iTrackPending != nullptr) {
        iTrackPending->RemoveRef();
    }
    if (iDecodedStream != nullptr) {
        iDecodedStream->RemoveRef();
    }
}

Msg* SpotifyReporter::Pull()
{
    {
        AutoMutex a(iLock);
        if (iTrackPending != nullptr) {
            const TBool startOfStream = false;  // Report false as don't want downstream elements to re-enter any stream detection mode.
            MsgTrack* msg = iMsgFactory.CreateMsgTrack(*iTrackPending, startOfStream);
            iTrackPending->RemoveRef();
            iTrackPending = nullptr;
            return msg;
        }
        if (iMsgDecodedStreamPending) {
            // If iDecodedStream is nullptr, means still need to pull first MsgDecodedStream from upstream element. Return control to keep pulling from upstream until first MsgDecodedStream is eventually pulled.
            if (iDecodedStream != nullptr) {
                iMsgDecodedStreamPending = false;

                const DecodedStreamInfo& info = iDecodedStream->StreamInfo();
                const TUint64 trackLengthSamples = (static_cast<TUint64>(iTrackDurationMs)*iSampleRate)/1000;
                const TUint64 trackLengthJiffies = Jiffies::JiffiesPerSample(info.SampleRate())*trackLengthSamples;
                MsgDecodedStream* msg = iMsgFactory.CreateMsgDecodedStream(info.StreamId(), info.BitRate(), info.BitDepth(), info.SampleRate(), info.NumChannels(), info.CodecName(), trackLengthJiffies, iTrackOffsetSubSamples, info.Lossless(), info.Seekable(), info.Live(), info.StreamHandler());

                iDecodedStream->RemoveRef();    // Discard old MsgDecodedStream
                iDecodedStream = msg;           // Hold reference to new MsgDecodedStream.
                iDecodedStream->AddRef();

                return iDecodedStream;
            }
        }
    }
    Msg* msg = iUpstreamElement.Pull();
    msg = msg->Process(*this);
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
    ASSERT(iSubSamples >= aPrevSubSamples);
    return iSubSamples - aPrevSubSamples;
}

// FIXME - why even pass in both a TrackFactory and metadata? Just pass in a ptr to a Track that's already been allocated! Then, this class doesn't need to know anything about Spotify protocol format, or the TrackFactory!
void SpotifyReporter::TrackChanged(TrackFactory& aTrackFactory, IPipelineIdProvider& /*aIdProvider*/, const Brx& aMetadata, TUint /*aStartMs*/)
{
    AutoMutex a(iLock);
    Brn duration = Net::XmlParserBasic::FindAttribute("res", "duration", aMetadata);

    // FIXME - pass track duration as param, instead of having an element upstream write out metadata, only for this to have to parse it and waste time undoing all that work.

    // Start offset should always be 0 when this is seen.
    // If a seek is performed, a new MsgEncodedStream will be output by Protocol with start sample, which is passed into MsgDecodedStream.
    // But, when Spotify runs on to next track, only get this notification, and start offset should definitely be 0 in that case.
    // Modified MsgDecodedStream will pick up last set value for track offset, which is always the correct one.
    iTrackOffsetSubSamples = 0; // FIXME - always 0 now; can remove aStartMs param.
    iTrackDurationMs = ParseDurationMs(duration);
    iReporterSubSampleStart = iSubSamples;

    // FIXME - only set these if in intercept mode.
    iTrackPending = aTrackFactory.CreateTrack(Brn("spotify://"), aMetadata);
    iMsgDecodedStreamPending = true;
}

void SpotifyReporter::NotifyMode(const Brx& aMode, const ModeInfo& aInfo)
{
    iPropertyObserver.NotifyMode(aMode, aInfo);
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
    //iLock.Wait();
    //if (iInterceptMode) {
    //    // Adjust to expected time based on number of (sub)samples seen since
    //    // TrackChanged() or a MsgDecodedStream.
    //    TUint durationSeconds = iTrackDurationMs/1000;
    //    TUint64 subSamples = (iSubSamples-iReporterSubSampleStart)+iTrackOffsetSubSamples;
    //    TUint64 seconds = subSamples/iChannels/iSampleRate;

    //    iLock.Signal();
    //    ASSERT(seconds <= std::numeric_limits<TUint>::max());
    //    TUint secondsCast = static_cast<TUint>(seconds);
    //    iPropertyObserver.NotifyTime(secondsCast, durationSeconds);
    //}
    //else {
    //    iLock.Signal();
        iPropertyObserver.NotifyTime(aSeconds, aTrackDurationSeconds);
    //}
}

void SpotifyReporter::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    iPropertyObserver.NotifyStreamInfo(aStreamInfo);
}

Msg* SpotifyReporter::ProcessMsg(MsgMode* aMsg)
{
    // FIXME - clear iDecodedStream here?
    // Probably not safe to clear Track here, due to race condition.
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

Msg* SpotifyReporter::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgDrain* aMsg)
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
    return nullptr;
}

Msg* SpotifyReporter::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgStreamInterrupted* aMsg)
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
    return nullptr;
}

Msg* SpotifyReporter::ProcessMsg(MsgWait* aMsg)
{
    // FIXME - if we see this, should anything be done to update subsamples? Maybe just reset iSubSamples (and associated members) and make it a requirement that when Spotify protocol is resuming (MsgEncodedStream) from a wait, it resets its sample counter to whatever this class currently reports.
    // Actually, does that mean that iSubSamples SHOULDN'T be reset here, as protocol module has no idea when MsgWait or MsgDecodedStream will arrive here?
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& info = aMsg->StreamInfo();
    AutoMutex a(iLock);
    iChannels = info.NumChannels();
    iSampleRate = info.SampleRate();
    ASSERT(iChannels != 0);
    ASSERT(iSampleRate != 0);


    // FIXME - don't do this if spotify isn't active as it will alter MsgDecodedStream belonging to non-Spotify sources.

    //iTrackOffsetSubSamples = info.SampleStart()*iChannels;
    iReporterSubSampleStart = iSubSamples;  // FIXME - rather than storing/manipulating iTrackOffsetSubSamples along with iSubSamples/iReporterSubSampleStart, just increment iSubSamples with the value of iTrackOffsetSubSamples and do away with that member?


    // FIXME - what if iTrackDurationMs is 0? (i.e., haven't been notified of track yet? Is that possible?

    // Update track duration, which should now be known, as it probably wasn't known when the audio belonging to this decoded stream was pushed into the pipeline.
    iTrackOffsetSubSamples = info.SampleStart();    // FIXME - rename to iTrackOffsetSamples.

    const TUint64 trackLengthSamples = (static_cast<TUint64>(iTrackDurationMs)*iSampleRate)/1000;
    const TUint64 trackLengthJiffies = Jiffies::JiffiesPerSample(info.SampleRate())*trackLengthSamples;// *info.NumChannels(); // FIXME - require #channels in calculation?
    MsgDecodedStream* msg = iMsgFactory.CreateMsgDecodedStream(info.StreamId(), info.BitRate(), info.BitDepth(), info.SampleRate(), info.NumChannels(), info.CodecName(), trackLengthJiffies, iTrackOffsetSubSamples, info.Lossless(), info.Seekable(), info.Live(), info.StreamHandler());

    aMsg->RemoveRef();
    if (iDecodedStream != nullptr) {
        iDecodedStream->RemoveRef();
    }
    iDecodedStream = msg;
    iDecodedStream->AddRef();
    iMsgDecodedStreamPending = false;

    return iDecodedStream;



    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgBitRate* aMsg)
{
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
    ASSERT(iSubSamples >= subSamplesPrev); // Overflow not handled.
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgSilence* aMsg)
{
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // don't expect to see MsgPlayable in the pipeline
    return nullptr;
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
