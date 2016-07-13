#pragma once

#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Standard.h>

#include <atomic>

namespace OpenHome {
    class ThreadFunctor;
namespace Av {

class SenderThread : public Media::IPipelineElementDownstream
                   , private Media::IMsgProcessor
                   , private INonCopyable
{
    static const TUint kMaxMsgBacklog; // asserts if ever exceeded
public:
    SenderThread(Media::IPipelineElementDownstream& aDownstream,
                 TUint aThreadPriority);
    ~SenderThread();
private: // from Media::IPipelineElementDownstream
    void Push(Media::Msg* aMsg) override;
private:
    void Run();
private: // from Media::IMsgProcessor
    Media::Msg* ProcessMsg(Media::MsgMode* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgTrack* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgDrain* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgDelay* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgEncodedStream* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgAudioEncoded* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgMetaText* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgStreamInterrupted* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgHalt* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgFlush* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgWait* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgDecodedStream* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgBitRate* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgAudioPcm* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgSilence* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgPlayable* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgQuit* aMsg) override;
private:
    Media::IPipelineElementDownstream& iDownstream;
    ThreadFunctor* iThread;
    Mutex iLock;
    FifoLiteDynamic<Media::Msg*> iFifo;
    std::atomic<TUint> iFifoSlotsUsed;
    Semaphore iShutdownSem;
    TBool iQuit;
};

} // namespace Av
} // namespace OpenHome
