#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>

#include <atomic>

namespace OpenHome {
namespace Media {

/*
Element which implements ramp up/down around a Pause
...or flushes (pulls then discards) all data from the pipeline before signalling Stopped.
Doesn't hold any audio itself (bar the special case where applying a ramp forces a msg to be split).
Pause is implemented by telling the stopper to BeginPause
...if the Stopper was running, RampDuration of audio is then passed through, gradually ramping down
...Pull then blocks until Play() is called again
BeginStop(aId) is implemented by telling the stopper to Play
...then ramping down as for pause
...followed by calling IStreamHandler::TryStop to attempt to stop delivery of the current stream
...followed by pulling/discarding all remaining content for that stream
...repeat for any other streams until a Halt msg with id==aId is pulled
Flush msgs are not propogated.  Any audio which gets past this element is guaranteed to be played
*/

class IStopperObserver
{
public:
    virtual void PipelinePaused() = 0;
    virtual void PipelineStopped() = 0;
    virtual void PipelinePlaying() = 0;
};

class IPipelineElementObserverThread;

class Stopper : public IPipelineElementUpstream, private IMsgProcessor, private IStreamHandler
{
    friend class SuiteStopper;
public:
    Stopper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IStopperObserver& aObserver,
            IPipelineElementObserverThread& aObserverThread, TUint aRampDuration);
    virtual ~Stopper();
    void SetStreamPlayObserver(IStreamPlayObserver& aObserver);
    void Play();
    void BeginPause();
    void BeginStop(TUint aHaltId);
    void StopNow();
    void Quit();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    enum EState
    {
        ERunning
       ,ERampingDown
       ,ERampingUp
       ,EPaused
       ,EStopped
       ,EFlushing
    };
    enum EEventedState
    {
        EEventNone
       ,EEventPlaying
       ,EEventPaused
       ,EEventStopped
    };
private:
    Msg* ProcessFlushable(Msg* aMsg);
    void OkToPlay();
    void RampCompleted();
    void NewStream();
    void HandlePaused();
    void HandleStopped();
    void SetState(EState aState);
    void ScheduleEvent(EEventedState aState);
    void ReportEvent();
    const TChar* State() const;
    static const TChar* State(EState aState);
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    IStopperObserver& iObserver;
    IPipelineElementObserverThread& iObserverThread;
    Mutex iLock;
    Semaphore iSem;
    IStreamPlayObserver* iStreamPlayObserver;
    EState iState;
    const TUint iRampDuration;
    TUint iRemainingRampSize;
    TUint iCurrentRampValue;
    MsgQueue iQueue; // empty unless we have to split a msg during a ramp
    TUint iTargetHaltId;
    TUint iTrackId;
    TUint iStreamId;
    IStreamHandler* iStreamHandler;
    TBool iCheckedStreamPlayable;
    TBool iHaltPending;
    TBool iFlushStream;
    TBool iBuffering;
    TBool iQuit;
    TUint iEventId;
    std::atomic<EEventedState> iEventState;
    EEventedState iLastEventedState;
};

} // namespace Media
} // namespace OpenHome

