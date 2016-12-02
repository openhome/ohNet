#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

class SampleRateValidator : public PipelineElement, public IPipelineElementDownstream, private INonCopyable
{
    friend class SuiteSampleRateValidator;

    static const TUint kSupportedMsgTypes;
public:
    SampleRateValidator(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement);
    void SetAnimator(IPipelineAnimator& aPipelineAnimator);
private: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
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
    MsgFactory& iMsgFactory;
    IPipelineElementDownstream& iDownstream;
    IPipelineAnimator* iAnimator;
    TUint iTargetFlushId;
    TBool iFlushing;
};

} // namespace Media
} // namespace OpenHome

