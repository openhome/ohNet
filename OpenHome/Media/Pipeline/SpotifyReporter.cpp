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

SpotifyReporter::SpotifyReporter(IPipelineElementUpstream& aUpstreamElement, MsgFactory& aMsgFactory)
    : iUpstreamElement(aUpstreamElement)
    , iMsgFactory(aMsgFactory)
    , iTrackDurationMs(0)
    , iTrackOffsetSamples(0)
    , iTrackPending(nullptr)
    , iMsgDecodedStreamPending(false)
    , iDecodedStream(nullptr)
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
        if (iInterceptMode) {
            if (iTrackPending != nullptr) {
                const TBool startOfStream = false;  // Report false as don't want downstream elements to re-enter any stream detection mode.
                MsgTrack* msg = iMsgFactory.CreateMsgTrack(*iTrackPending, startOfStream);
                iTrackPending->RemoveRef();
                iTrackPending = nullptr;
                return msg;
            }
            if (iMsgDecodedStreamPending) {
                /*
                 * If iDecodedStream == nullptr, means still need to pull first
                 * MsgDecodedStream of Spotify stream from upstream element.
                 * Return control to keep pulling from upstream until first
                 * MsgDecodedStream is eventually pulled.
                 */
                if (iDecodedStream != nullptr) {
                    iMsgDecodedStreamPending = false;
                    MsgDecodedStream* msg = CreateMsgDecodedStreamLocked();
                    UpdateDecodedStreamLocked(*msg);
                    return iDecodedStream;
                }
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

void SpotifyReporter::TrackChanged(Track* aTrack, TUint aDurationMs)
{
    AutoMutex a(iLock);
    /*
     * Start offset is always 0 when out-of-band track is seen.
     * If there is a non-zero start or seek offset, Protocol will output it in
     * a MsgEncodedStream.
     * Modified MsgDecodedStream will pick up last set value for track offset,
     * which is always the correct one.
     */
    iTrackOffsetSamples = 0;
    iTrackDurationMs = aDurationMs;

    if (iTrackPending) {
        /*
         * Notified of new track before opportunity to output previous track.
         * May be a valid state due to race conditions around track
         * notifications and pipeline playback starting.
         */
        iTrackPending->RemoveRef();
    }
    iTrackPending = aTrack;
    iMsgDecodedStreamPending = true;
}

Msg* SpotifyReporter::ProcessMsg(MsgMode* aMsg)
{
    // Not safe to clear iTrackPending here, as out-of-band track update call may already have arrived before this msg made its way down pipeline.
    AutoMutex a(iLock);
    if (aMsg->Mode() == kInterceptMode) {
        iInterceptMode = true;
    }
    else {
        iInterceptMode = false;
    }
    iMsgDecodedStreamPending = true;
    ClearDecodedStreamLocked();
    iTrackOffsetSamples = 0;
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
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgDecodedStream* aMsg)
{
    AutoMutex a(iLock);

    if (iInterceptMode) {
        // Clear any previous cached MsgDecodedStream and cache the one received.
        UpdateDecodedStreamLocked(*aMsg);
        aMsg->RemoveRef();  // UpdateDecodedStreamLocked() adds its own reference.

        const DecodedStreamInfo& info = iDecodedStream->StreamInfo();
        iTrackOffsetSamples = info.SampleStart();

        // Generate a new MsgDecodedStream (which requires most up-to-date MsgDecodedStream in cache).
        MsgDecodedStream* msg = CreateMsgDecodedStreamLocked();
        // Now, update the cache with the new MsgDecodedStream.
        UpdateDecodedStreamLocked(*msg);
        return iDecodedStream;
    }
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgBitRate* aMsg)
{
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgAudioPcm* aMsg)
{
    AutoMutex a(iLock);
    ASSERT(iDecodedStream != nullptr);  // Can't receive audio until MsgDecodedStream seen.
    const DecodedStreamInfo& info = iDecodedStream->StreamInfo();
    TUint samples = aMsg->Jiffies()/Jiffies::JiffiesPerSample(info.SampleRate());
    TUint64 subSamplesPrev = iSubSamples;
    iSubSamples += samples*info.NumChannels();
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

void SpotifyReporter::ClearDecodedStreamLocked()
{
    if (iDecodedStream != nullptr) {
        iDecodedStream->RemoveRef();
        iDecodedStream = nullptr;
    }
}

void SpotifyReporter::UpdateDecodedStreamLocked(MsgDecodedStream& aMsg)
{
    ClearDecodedStreamLocked();
    iDecodedStream = &aMsg;
    iDecodedStream->AddRef();
}

TUint64 SpotifyReporter::TrackLengthSamplesLocked() const
{
    if (iTrackDurationMs == 0) {
        return 0;
    }

    ASSERT(iDecodedStream != nullptr);
    const DecodedStreamInfo& info = iDecodedStream->StreamInfo();
    const TUint64 trackLengthSamples = (static_cast<TUint64>(iTrackDurationMs)*info.SampleRate())/1000;
    return trackLengthSamples;
}

MsgDecodedStream* SpotifyReporter::CreateMsgDecodedStreamLocked() const
{
    ASSERT(iDecodedStream != nullptr);
    const DecodedStreamInfo& info = iDecodedStream->StreamInfo();
    // Due to out-of-band track notification from Spotify, audio for current track was probably pushed into pipeline before track offset was known, so use updated value here.
    const TUint64 trackLengthSamples = TrackLengthSamplesLocked();
    const TUint64 trackLengthJiffies = Jiffies::JiffiesPerSample(info.SampleRate())*trackLengthSamples;
    MsgDecodedStream* msg = iMsgFactory.CreateMsgDecodedStream(info.StreamId(), info.BitRate(), info.BitDepth(), info.SampleRate(), info.NumChannels(), info.CodecName(), trackLengthJiffies, iTrackOffsetSamples, info.Lossless(), info.Seekable(), info.Live(), info.StreamHandler());
    return msg;
}
