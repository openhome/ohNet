#ifndef HEADER_PIPELINE_AGGREGATOR
#define HEADER_PIPELINE_AGGREGATOR

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/*
Utility class which is not part of the generic pipeline.
May be used by audio drivers to combine/split audio data to a preferred duration.
May send shorter msg if format change or Halt is encountered.
*/

class Aggregator : public IPipelineElementUpstream, private IMsgProcessor, private INonCopyable
{
    friend class SuiteAggregator;
public:
    Aggregator(IPipelineElementUpstream& aUpstreamElement, TUint aMaxPlayableJiffies);
    virtual ~Aggregator();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private:
    Msg* NextStoredMsg(TBool aDeliverShortPlayable);
    Msg* AddPlayable(MsgPlayable* aPlayable);
    void CalculateMaxPlayable();
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    IPipelineElementUpstream& iUpstreamElement;
    const TUint iMaxPlayableJiffies;
    TUint iMaxPlayableBytes;
    MsgPlayable* iPlayable;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iNumChannels;
    Msg* iPending;
    TBool iRecalculateMaxPlayable;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_AGGREGATOR
