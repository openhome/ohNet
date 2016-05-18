#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which applies a ramp up at the start of a stream when necessary.
Is NOT responsible for all ramping.  Many other elements also apply ramps in other circumstances.
*/

class Ramper : public PipelineElement, public IPipelineElementUpstream, private INonCopyable
{
    friend class SuiteRamper;

    static const TUint kSupportedMsgTypes;
public:
    Ramper(IPipelineElementUpstream& aUpstreamElement, TUint aRampDuration);
    virtual ~Ramper();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // IMsgProcessor
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
private:
    IPipelineElementUpstream& iUpstreamElement;
    TUint iStreamId;
    TBool iRamping;
    const TUint iRampDuration;
    TUint iRemainingRampSize;
    TUint iCurrentRampValue;
    MsgQueueLite iQueue;
};

} // namespace Media
} // namespace OpenHome

