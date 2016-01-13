#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

    class DecodedAudioAggregator : public PipelineElement, public IPipelineElementDownstream, private INonCopyable
{
public:
    static const TUint kMaxBytes = DecodedAudio::kMaxBytes;
    static const TUint kMaxMs = 5;  // buffer MsgAudioPcm until we have this many ms
                                    // (unless we hit DecodedAudio::kMaxBytes first).
                                    // kMaxMs may be violated if it's possible to add
                                    // a MsgAudioPcm without chopping it (and without
                                    // violating kMaxBytes).
    static const TUint kMaxJiffies = Jiffies::kPerMs * kMaxMs;
    static const TUint kSupportedMsgTypes;
public:
    DecodedAudioAggregator(IPipelineElementDownstream& aDownstreamElement);
public: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    static TBool AggregatorFull(TUint aBytes, TUint aJiffies);
    MsgAudioPcm* TryAggregate(MsgAudioPcm* aMsg);
    void OutputAggregatedAudio();
private:
    IPipelineElementDownstream& iDownstreamElement;
    MsgAudioPcm* iDecodedAudio;
    TUint iChannels;
    TUint iSampleRate;
    TUint iBitDepth;
};

}
}

