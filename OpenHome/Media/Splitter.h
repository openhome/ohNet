#ifndef HEADER_PIPELINE_SPLITTER
#define HEADER_PIPELINE_SPLITTER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
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
Is animated by being Pull()ed.
Branching can be toggled at runtime (default is off).
When enabled, audio msgs are cloned for the branch; others have a reference claimed.
*/

class Splitter : public IPipelineElement, private IMsgProcessor
{
public:
    Splitter(IPipelineElement& aUpstreamElement, IPipelineBranch& aBranch);
    void SetEnabled(TBool aEnabled);
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
    Mutex iLock;
    TBool iEnabled;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_SPLITTER
