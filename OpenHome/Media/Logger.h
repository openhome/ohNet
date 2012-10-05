#ifndef HEADER_PIPELINE_LOGGER
#define HEADER_PIPELINE_LOGGER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which logs msgs as they pass through.
Can be inserted [0..n] times through the pipeline, depending on your debugging needs.
*/

class Logger : public IPipelineElementUpstream, private IMsgProcessor, private INonCopyable
{
public:
    Logger(IPipelineElementUpstream& aUpstreamElement, const TChar* aId);
public: // from IPipelineElementUpstream
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
    IPipelineElementUpstream& iUpstreamElement;
    const TChar* iId;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_LOGGER
