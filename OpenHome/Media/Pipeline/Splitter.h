#ifndef HEADER_PIPELINE_SPLITTER
#define HEADER_PIPELINE_SPLITTER

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which allows the pipeline to fork, with msgs going down both branches.
Secondary branch is animated by the primary branch being Pull()ed.
When enabled, audio msgs are cloned for the branch; others have a reference claimed.
*/

class Splitter : public IPipelineElementUpstream, private IMsgProcessor, private INonCopyable
{
public:
    Splitter(IPipelineElementUpstream& aUpstreamElement);
    virtual ~Splitter();
    IPipelineElementDownstream* SetPipelineBranch(IPipelineElementDownstream& aBranch);
public: // from IPipelineElementUpstream
    Msg* Pull() override;
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
    IPipelineElementUpstream& iUpstreamElement;
    IPipelineElementDownstream* iBranch;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_SPLITTER
