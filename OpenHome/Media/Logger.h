#ifndef HEADER_PIPELINE_LOGGER
#define HEADER_PIPELINE_LOGGER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/private/Standard.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which logs msgs as they pass through.
Can be inserted [0..n] times through the pipeline, depending on your debugging needs.
*/

class Logger : public IPipelineElement, private IMsgProcessor, private INonCopyable
{
public:
    Logger(IPipelineElement& aUpstreamElement, const TChar* aId);
public: // from IPipelineElement
    Msg* Pull();
private: // IMsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    IPipelineElement& iUpstreamElement;
    const TChar* iId;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_LOGGER
