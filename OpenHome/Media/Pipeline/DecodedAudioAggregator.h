#ifndef HEADER_PIPELINE_DECODED_AUDIO_AGGREGATOR
#define HEADER_PIPELINE_DECODED_AUDIO_AGGREGATOR

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

class DecodedAudioAggregator : public IPipelineElementDownstream, private IStreamHandler, private IMsgProcessor, private INonCopyable
{
public:
    static const TUint kMaxBytes = DecodedAudio::kMaxBytes;
    static const TUint kMaxMs = 5;  // buffer MsgAudioPcm until we have this many ms
                                    // (unless we hit DecodedAudio::kMaxBytes first).
                                    // kMaxMs may be violated if it's possible to add
                                    // a MsgAudioPcm without chopping it (and without
                                    // violating kMaxBytes).
    static const TUint kMaxJiffies = Jiffies::kPerMs * kMaxMs;
public: 
    DecodedAudioAggregator(IPipelineElementDownstream& aDownstreamElement, MsgFactory& aMsgFactory);
public: // from IPipelineElementDownstream
    void Push(Msg* aMsg);
public: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
    TBool TryGet(IWriter& aWriter, TUint aTrackId, TUint aStreamId, TUint64 aOffset, TUint aBytes); // return false if we failed to get aBytes
    void NotifyStarving(const Brx& aMode, TUint aTrackId, TUint aStreamId);
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg);
    Msg* ProcessMsg(MsgSession* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgDelay* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgWait* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    TBool AggregatorFull(TUint aBytes, TUint aJiffies);
    MsgAudioPcm* TryAggregate(MsgAudioPcm* aMsg);
    void Queue(Msg* aMsg);
    void OutputAggregatedAudio();
    void ReleaseAggregatedAudio();
private:
    IPipelineElementDownstream& iDownstreamElement;
    MsgFactory& iMsgFactory;
    IStreamHandler* iStreamHandler;
    MsgAudioPcm* iDecodedAudio;
    TUint iTrackId;
    TUint iStreamId;
    TUint iChannels;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iExpectedFlushId;
    Mutex iLock;
};

}
}

#endif // HEADER_PIPELINE_DECODED_AUDIO_AGGREGATOR
