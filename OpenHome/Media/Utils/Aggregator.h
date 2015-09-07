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

class Aggregator : public PipelineElement, public IPipelineElementUpstream, private INonCopyable
{
    friend class SuiteAggregator;
    static const TUint kSupportedMsgTypes;
public:
    Aggregator(IPipelineElementUpstream& aUpstreamElement, TUint aMaxPlayableJiffies);
    virtual ~Aggregator();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private:
    Msg* NextStoredMsg(TBool aDeliverShortPlayable);
    void CalculateMaxPlayable();
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
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
