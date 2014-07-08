#ifndef HEADER_PIPELINE_PREDRIVER
#define HEADER_PIPELINE_PREDRIVER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which sits at the very right of the generic pipeline.
Passes on Format, Halt and Quit msgs.
Only passes on Format when either sample rate and/or bit depth changes.
Converts AudioPcm, Silence msgs to Playable.
*/
    
class PreDriver : public IPipelineElementUpstream, private IMsgProcessor, private INonCopyable
{
public:
    PreDriver(IPipelineElementUpstream& aUpstreamElement);
    virtual ~PreDriver();
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
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iNumChannels;
    Semaphore iShutdownSem;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_PREDRIVER
