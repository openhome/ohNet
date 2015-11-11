#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/SpotifyReporter.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Net/Private/XmlParser.h>

#include <limits>

using namespace OpenHome;
using namespace OpenHome::Media;


// SpotifyReporter

const TUint SpotifyReporter::kSupportedMsgTypes =   eMode
                                                  | eTrack
                                                  | eDrain
                                                  | eDelay
                                                  | eMetatext
                                                  | eStreamInterrupted
                                                  | eHalt
                                                  | eWait
                                                  | eDecodedStream
                                                  | eBitRate
                                                  | eAudioPcm
                                                  | eSilence
                                                  | eQuit;

const Brn SpotifyReporter::kInterceptMode("Spotify");

SpotifyReporter::SpotifyReporter(IPipelineElementUpstream& aUpstreamElement, MsgFactory& aMsgFactory, TrackFactory& aTrackFactory)
    : PipelineElement(kSupportedMsgTypes)
    , iUpstreamElement(aUpstreamElement)
    , iMsgFactory(aMsgFactory)
    , iTrackFactory(aTrackFactory)
    , iTrackInfoAccessor(nullptr)
    , iMsgTrackPending(nullptr)
    , iMsgDecodedStreamPending(false)
    , iDecodedStream(nullptr)
    , iSubSamples(0)
    , iInterceptMode(false)
    , iPipelineTrackSeen(false)
    , iLock("SARL")
{
}

SpotifyReporter::~SpotifyReporter()
{
    if (iDecodedStream != nullptr) {
        iDecodedStream->RemoveRef();
    }
}

Msg* SpotifyReporter::Pull()
{
    Msg* msg = nullptr;
    while (msg == nullptr) {
        {
            AutoMutex a(iLock);
            if (iInterceptMode && iPipelineTrackSeen) {
                // Only want to output generated MsgTrack if it's pending and if stream format is known to get certain elements for track metadata.
                if (iMsgTrackPending && iDecodedStream != nullptr) {    // FIXME - can move iDecodedStream check into outer if statement.

                    const DecodedStreamInfo& info = iDecodedStream->StreamInfo();
                    const TUint bitDepth = info.BitDepth();
                    const TUint channels = info.NumChannels();
                    const TUint sampleRate = info.SampleRate();

                    Bws<IDidlLiteWriter::kMaxBytes> metadata;
                    WriterBuffer writerBuf(metadata);
                    MetadataWriter metadataWriter(writerBuf, bitDepth, channels, sampleRate); // Writer will omit any fields with value 0.
                    iTrackInfoAccessor->WriteMetadata(metadataWriter);  // FIXME - locking issues here. Left-hand side of pipeline may be trying to push audio into pipeline from Spotify thread (which holds lock during callbacks), and pipeline is blocked until this element output the MsgDecodedStream, but call to WriteMetadata acquires same lock as Spotify thread.
                    Track* track = iTrackFactory.CreateTrack(iTrackUri, metadata);

                    const TBool startOfStream = false;  // Report false as don't want downstream elements to re-enter any stream detection mode.
                    MsgTrack* msg = iMsgFactory.CreateMsgTrack(*track, startOfStream);
                    track->RemoveRef();
                    iMsgTrackPending = false;
                    return msg;
                }
                if (!iMsgTrackPending && iMsgDecodedStreamPending && iDecodedStream != nullptr) {
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

        msg = iUpstreamElement.Pull();
        msg = msg->Process(*this);
    }
    return msg;
}

TUint64 SpotifyReporter::SubSamples() const
{
    return iSubSamples;
}

TUint64 SpotifyReporter::SubSamplesDiff(TUint64 aPrevSubSamples) const
{
    const TUint64 subSamples = iSubSamples;
    ASSERT(subSamples >= aPrevSubSamples);
    return subSamples - aPrevSubSamples;
}

void SpotifyReporter::RegisterTrackAccessor(const Brx& aUri, ITrackInfoAccessor& aInfoAccessor)
{
    ASSERT(iTrackInfoAccessor == nullptr);
    iTrackUri.Replace(aUri);
    iTrackInfoAccessor = &aInfoAccessor;
}

void SpotifyReporter::TrackChanged()
{
    AutoMutex a(iLock);
    iMsgTrackPending = true;
    iMsgDecodedStreamPending = true;
}

Msg* SpotifyReporter::ProcessMsg(MsgMode* aMsg)
{
    AutoMutex a(iLock);
    ASSERT(iTrackInfoAccessor != nullptr);  // 2-stage initialisation must be complete.
    if (aMsg->Mode() == kInterceptMode) {
        iInterceptMode = true;
    }
    else {
        iInterceptMode = false;
    }
    iPipelineTrackSeen = false;
    iMsgTrackPending = true;
    iMsgDecodedStreamPending = true;
    ClearDecodedStreamLocked();

    iSubSamples = 0;
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgTrack* aMsg)
{
    AutoMutex a(iLock);
    iPipelineTrackSeen = true;  // Only matters when in iInterceptMode. Ensures in-band MsgTrack is output before any are generated from out-of-band notifications.
    return aMsg;
}

Msg* SpotifyReporter::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& info = aMsg->StreamInfo();
    ASSERT(info.SampleRate() != 0);
    ASSERT(info.NumChannels() != 0);
    AutoMutex a(iLock);
    // Clear any previous cached MsgDecodedStream and cache the one received.
    UpdateDecodedStreamLocked(*aMsg);

    if (iInterceptMode) {
        aMsg->RemoveRef();  // UpdateDecodedStreamLocked() adds its own reference.
        iMsgDecodedStreamPending = true;    // Set flag so that a MsgDecodedStream with updated attributes is output in place of this.
        return nullptr;
    }
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

TUint64 SpotifyReporter::TrackLengthJiffiesLocked() const
{
    ASSERT(iDecodedStream != nullptr);
    const TUint trackDurationMs = iTrackInfoAccessor->DurationMs();
    const DecodedStreamInfo& info = iDecodedStream->StreamInfo();
    const TUint64 trackLengthJiffies = (static_cast<TUint64>(trackDurationMs)*info.SampleRate()*Jiffies::JiffiesPerSample(info.SampleRate()))/1000;
    return trackLengthJiffies;
}

MsgDecodedStream* SpotifyReporter::CreateMsgDecodedStreamLocked() const
{
    ASSERT(iDecodedStream != nullptr);
    const DecodedStreamInfo& info = iDecodedStream->StreamInfo();
    // Due to out-of-band track notification from Spotify, audio for current track was probably pushed into pipeline before track offset/duration was known, so use updated values here.
    const TUint trackOffsetMs = iTrackInfoAccessor->PlaybackPositionMs();
    const TUint64 trackOffsetSamples = (static_cast<TUint64>(trackOffsetMs)*info.SampleRate())/1000;

    const TUint64 trackLengthJiffies = TrackLengthJiffiesLocked();
    MsgDecodedStream* msg = iMsgFactory.CreateMsgDecodedStream(info.StreamId(), info.BitRate(), info.BitDepth(), info.SampleRate(), info.NumChannels(), info.CodecName(), trackLengthJiffies, trackOffsetSamples, info.Lossless(), info.Seekable(), info.Live(), info.StreamHandler());
    return msg;
}


// MetadataWriter

MetadataWriter::MetadataWriter(IWriter& aWriter, TUint aBitDepth, TUint aChannels, TUint aSampleRate)
    : iWriter(aWriter)
    , iBitDepth(aBitDepth)
    , iChannels(aChannels)
    , iSampleRate(aSampleRate)
{
}

void MetadataWriter::WriteMetadata(const IDidlLiteWriter& aWriter)
{
    aWriter.WriteDidlLite(iWriter, iBitDepth, iChannels, iSampleRate);
}
