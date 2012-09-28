#ifndef HEADER_PIPELINE_SPLITTER
#define HEADER_PIPELINE_SPLITTER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

class IPipelineBranch
{
public:
    virtual void AddMsg(Msg* aMsg) = 0;
};
    
/*
Element which allows the pipeline to fork, with msgs going down both branches.
Secondary branch is animated by the primary branch being Pull()ed.
When enabled, audio msgs are cloned for the branch; others have a reference claimed.
*/

class Splitter : public IPipelineElement, private IMsgProcessor, private INonCopyable
{
public:
    Splitter(IPipelineElement& aUpstreamElement, IPipelineBranch& aBranch);
public: // from IPipelineElement
    Msg* Pull();
private: // IMsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgAudioFormat* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    IPipelineElement& iUpstreamElement;
    IPipelineBranch& iBranch;
};

// Test code helper
class PipelineBranchNull : public IPipelineBranch
{
public: // from IPipelineBranch
    void AddMsg(Msg* aMsg);
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_SPLITTER
