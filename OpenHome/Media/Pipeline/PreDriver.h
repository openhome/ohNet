#ifndef HEADER_PIPELINE_PREDRIVER
#define HEADER_PIPELINE_PREDRIVER

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which sits at the very right of the generic pipeline.
Passes on Format, Halt and Quit msgs.
Only passes on Format when either sample rate and/or bit depth changes.
Converts AudioPcm, Silence msgs to Playable.
Consumes StreamInterrupted
*/
    
class PreDriver : public PipelineElement, public IPipelineElementUpstream, private INonCopyable
{
    static const TUint kSupportedMsgTypes;
public:
    PreDriver(IPipelineElementUpstream& aUpstreamElement);
    virtual ~PreDriver();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // IMsgProcessor
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
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
