#pragma once

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
class Silencer : public PipelineElement, public IPipelineElementUpstream, private INonCopyable
{
    friend class SuiteSilencer;
    static const TUint kSupportedMsgTypes;
public:
    Silencer(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aThreadPriority, TUint aSilenceJiffies, TUint aMaxNumMsgs);
    ~Silencer();
private:
    void Run();
private: // IPipelineElementUpstream
    Msg* Pull() override;
private: // IMsgProcessor
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
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

