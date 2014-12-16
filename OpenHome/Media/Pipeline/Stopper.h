#ifndef HEADER_PIPELINE_STOPPER
#define HEADER_PIPELINE_STOPPER

#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>

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

class Stopper : public IPipelineElementUpstream, private IMsgProcessor
{
    friend class SuiteStopper;
public:
    Stopper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IStopperObserver& aObserver, TUint aRampDuration);
    virtual ~Stopper();
    void SetStreamPlayObserver(IStreamPlayObserver& aObserver);
    void Play();
    void BeginPause();
    void BeginStop(TUint aHaltId);
    void StopNow();
    void Quit();
public: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IMsgProcessor
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
    enum EState
    {
        ERunning
       ,ERampingDown
       ,ERampingUp
       ,EPaused
       ,EStopped
       ,EFlushing
    };
private:
    Msg* ProcessFlushable(Msg* aMsg);
    void OkToPlay();
    Msg* ProcessAudio(MsgAudio* aMsg);
    void NewStream();
    void HandleStopped();
    void SetState(EState aState);
    const TChar* State() const;
    static const TChar* State(EState aState);
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    IStopperObserver& iObserver;
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
    TUint iTrackIdPipeline;
    TUint iStreamId;
    IStreamHandler* iStreamHandler;
    TBool iCheckedStreamPlayable;
    TBool iHaltPending;
    TBool iFlushStream;
    TBool iQuit;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_STOPPER
