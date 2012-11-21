#ifndef HEADER_PIPELINE_PREDRIVER
#define HEADER_PIPELINE_PREDRIVER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which sits at the very right of the generic pipeline.
Passes on Format, Halt and Quit msgs.
Only passes on Format when either sample rate and/or bit depth changes.
Sends Halt before Format, except on startup (when driver is assumed to be effectively halted already).
Converts AudioPcm, Silence msgs to Playable.
Combines Playable msgs into client-specified lengths.
May send shorter msg if format change or Halt is encountered.
*/
    
class PreDriver : public IPipelineElementUpstream, private IMsgProcessor, private INonCopyable
{
public:
    PreDriver(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aMaxPlayableJiffies);
    ~PreDriver();
public: // from IPipelineElementUpstream
    Msg* Pull();
private:
    Msg* NextStoredMsg();
    Msg* AddPlayable(MsgPlayable* aPlayable);
private: // IMsgProcessor
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
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
    TUint iMaxPlayableJiffies;
    TUint iMaxPlayableBytes;
    MsgPlayable* iPlayable;
    MsgAudioFormat* iFormat;
    MsgAudioFormat* iPendingFormatChange;
    MsgHalt* iPendingHalt;
    TBool iHalted;
    Semaphore iShutdownSem;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_PREDRIVER
