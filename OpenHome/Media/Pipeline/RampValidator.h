#ifndef HEADER_PIPELINE_RAMP_VALIDATOR
#define HEADER_PIPELINE_RAMP_VALIDATOR

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/*
Utility class which is not part of the generic pipeline.
May be used to validate ramps output by the overall pipeline or individual elements.
*/

class RampValidator : public PipelineElement, public IPipelineElementUpstream, public IPipelineElementDownstream, private INonCopyable
{
    static const TUint kSupportedMsgTypes;
public:
    RampValidator(IPipelineElementUpstream& aUpstream, const TChar* aId);
    RampValidator(const TChar* aId, IPipelineElementDownstream& aDownstream);
    virtual ~RampValidator();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
public: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
private:
    void Reset(const TChar* aCallerId);
    void ResetIfRampComplete(const Ramp& aRamp);
    void ProcessAudio(const Ramp& aRamp);
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
private:
    const TChar* iId;
    IPipelineElementUpstream* iUpstream;
    IPipelineElementDownstream* iDownstream;
    TBool iRamping;
    TBool iRampedDown;
    TBool iWaitingForAudio;
    TUint iLastRamp;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_RAMP_VALIDATOR
