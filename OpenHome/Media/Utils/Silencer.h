#ifndef HEADER_PIPELINE_SILENCER
#define HEADER_PIPELINE_SILENCER

#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Media {

/**
 * Utility class which generates silence when no other data is available.
 *
 * Is not part of the generic pipeline.
 * May be used by audio drivers which cannot cope with audio underruns to generate
 * silence when no audio is available.
 * Note that use of this interferes with synchronisation between devcies.
 */
class Silencer : public IMsgProcessor, public IPipelineElementUpstream, private INonCopyable
{
    friend class SuiteSilencer;
public:
    Silencer(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aThreadPriority, TUint aSilenceJiffies, TUint aMaxNumMsgs);
    ~Silencer();
private:
    void Run();
private: // IPipelineElementUpstream
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
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    TUint iSilenceJiffies;
    Fifo<Msg*> iFifo;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iNumChannels;
    ThreadFunctor* iThread;
    TBool iQuit;
    TBool iHalted;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_SILENCER
