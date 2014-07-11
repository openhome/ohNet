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
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    TUint iSilenceJiffies;
    Fifo<Msg*> iFifo;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iNumChannels;
    ThreadFunctor* iThread;
    TBool iQuit;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_SILENCER
