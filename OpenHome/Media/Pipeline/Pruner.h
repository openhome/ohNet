#ifndef HEADER_PIPELINE_PRUNER
#define HEADER_PIPELINE_PRUNER

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which removes msgs which aren't needed downstream:
    MsgSession
    MsgDelay
    MsgEncodedStream
    MsgMetaText
    MsgWait
    All content for tracks that don't contain any audio
*/

class Pruner : public IPipelineElementUpstream, private IMsgProcessor, private INonCopyable
{
public:
    Pruner(IPipelineElementUpstream& aUpstreamElement);
    virtual ~Pruner();
public: // from IPipelineElementUpstream
    Msg* Pull();
private:
    Msg* TryQueue(Msg* aMsg);
    Msg* TryQueueCancelWaiting(Msg* aMsg);
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
    IPipelineElementUpstream& iUpstreamElement;
    MsgQueue iQueue;
    MsgMode* iPendingMode;
    TBool iWaitingForAudio;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_PRUNER
