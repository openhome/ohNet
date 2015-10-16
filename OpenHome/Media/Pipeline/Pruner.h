#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which removes msgs which aren't needed downstream:
    MsgTrack
    MsgDelay
    MsgEncodedStream
    MsgMetaText
    MsgWait
    All content for tracks that don't contain any audio
*/

class Pruner : public PipelineElement, public IPipelineElementUpstream, private INonCopyable
{
    static const TUint kSupportedMsgTypes;
public:
    Pruner(IPipelineElementUpstream& aUpstreamElement);
    virtual ~Pruner();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private:
    Msg* TryQueue(Msg* aMsg);
    Msg* TryQueueCancelWaiting(Msg* aMsg);
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    IPipelineElementUpstream& iUpstreamElement;
    MsgQueue iQueue;
    MsgMode* iPendingMode;
    TBool iWaitingForAudio;
    TBool iConsumeHalts;
};

} // namespace Media
} // namespace OpenHome

