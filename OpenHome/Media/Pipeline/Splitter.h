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
    Msg* Pull();
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
    IPipelineElementDownstream* iBranch;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_SPLITTER
