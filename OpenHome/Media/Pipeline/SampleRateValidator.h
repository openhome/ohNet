#ifndef HEADER_PIPELINE_SAMPLE_RATE_VALIDATOR
#define HEADER_PIPELINE_SAMPLE_RATE_VALIDATOR

#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

class SampleRateValidator : public PipelineElement, public IPipelineElementDownstream, private INonCopyable
{
    friend class SuiteSampleRateValidator;

    static const TUint kSupportedMsgTypes;
public:
    SampleRateValidator(IPipelineElementDownstream& aDownstreamElement);
    void SetAnimator(IPipelineAnimator& aPipelineAnimator);
private: // from IPipelineElementDownstream
    void Push(Msg* aMsg);
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
private:
    Msg* ProcessFlushable(Msg* aMsg);
private:
    IPipelineElementDownstream& iDownstream;
    IPipelineAnimator* iAnimator;
    TUint iTargetFlushId;
    TBool iFlushing;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_SAMPLE_RATE_VALIDATOR
