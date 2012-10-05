#ifndef HEADER_PIPELINE_PREDRIVER
#define HEADER_PIPELINE_PREDRIVER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which sits at the very right of the generic pipeline.
Passes on Playable, Format, Halt and Quit msgs only.
Only passes on Format when either sample rate and/or bit depth changes.
Sends Halt before Format, except on startup (when driver is assumed to be effectively halted already).
Converts AudioPcm, Silence msgs to Playable.
*/
    
class PreDriver : public IPipelineElementUpstream, private IMsgProcessor, private INonCopyable
{
public:
    PreDriver(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement);
    ~PreDriver();
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
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    MsgAudioFormat* iFormat;
    MsgAudioFormat* iPendingFormatChange;
    TBool iHalted;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_PREDRIVER
