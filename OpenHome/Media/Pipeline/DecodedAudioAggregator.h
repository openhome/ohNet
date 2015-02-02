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
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    TBool TryGet(IWriter& aWriter, TUint aStreamId, TUint64 aOffset, TUint aBytes) override; // return false if we failed to get aBytes
    void NotifyStarving(const Brx& aMode, TUint aStreamId) override;
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
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
