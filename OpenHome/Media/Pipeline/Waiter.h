#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>

#include <atomic>

namespace OpenHome {
namespace Media {

class IWaiterObserver
{
public:
    virtual void PipelineWaiting(TBool aWaiting) = 0; // allows switching between EFlushing and EPlaying
};

/*
 * Element which facilitates flushing of audio packets and putting the pipeline
 * into a waiting state.
 *
 * If a track is playing when Wait() is called, it is ramped down and the
 * observers are notified that they should be in a waiting state.
 *
 * Further audio msgs arriving at this element are disposed of until the
 * expected MsgFlush arrives, or until a new MsgTrack arrives.
 *
 * Element expects it will always be Waiting on the current stream. MsgFlush
 * should always reach this element, i.e., no upstream element should consume
 * the MsgFlush expected by this element.
 */

class IPipelineElementObserverThread;

class Waiter : public PipelineElement, public IPipelineElementUpstream
{
    static const TUint kSupportedMsgTypes;
public:
    Waiter(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IWaiterObserver& aObserver,
           IPipelineElementObserverThread& aObserverThread, TUint aRampDuration);
    virtual ~Waiter();
    void Wait(TUint aFlushId, TBool aRampDown);
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
private:
    void DoWait();
    Msg* ProcessFlushable(Msg* aMsg);
    void HandleAudio();
    void NewStream();
    void ScheduleEvent(TBool aWaiting);
    void ReportEvent();
private:
    enum EState
    {
        ERunning
       ,ERampingDown
       ,ERampingUp
       ,EFlushing   // required for RAOP protocol
       ,EWaiting    // required for Songcast protocol
    };
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    IWaiterObserver& iObserver;
    IPipelineElementObserverThread& iObserverThread;
    Mutex iLock;
    EState iState;
    const TUint iRampDuration;
    TUint iRemainingRampSize;
    TUint iCurrentRampValue;
    MsgQueue iQueue; // empty unless we have to split a msg during a ramp
    TUint iTargetFlushId;
    TUint iEventId;
    std::atomic<TBool> iEventWaiting;
};

} // namespace Media
} // namespace OpenHome

