#ifndef HEADER_PIPELINE_STOPPER
#define HEADER_PIPELINE_STOPPER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

class IStopperObserver
{
public:
    virtual void PipelineHalted() = 0;
    virtual void PipelineFlushed() = 0;
};
    
/*
Element which implements ramp up/down at the start/end of a playlist (or equivalent).
Doesn't hold any audio itself (bar the special case where applying a ramp forces a msg to be split).
Halt (pause) is implemented by telling the stopper to BeginHalt
...RampDuration of audio is then passed through, gradually ramping down
...Pull then blocks until Start() is called again
Flush (stop) is implemented by telling the stopper to begin
...then adding Flush msg to the leftmost pipeline element
...then waiting for the Flush msg to reach the stopper, which informs IStopperObserver
Flush msgs are not propogated.  Any audio which gets past this element is guaranteed to be played
Note that Flush msg can only be added to pipeline once it is halted (when PipelineHalted() has been called)
*/

class Stopper : public IPipelineElement, private IMsgProcessor
{
    friend class SuiteStopper;
public:
    Stopper(MsgFactory& aMsgFactory, IPipelineElement& aUpstreamElement, IStopperObserver& aObserver, TUint aRampDuration);
    void Start();
    void BeginHalt();
    void BeginFlush();
public: // from IPipelineElement
    Msg* Pull();
private: // from IMsgProcessor
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
    Msg* ProcessMsgAudio(MsgAudio* aMsg);
    void Ramp(MsgAudio* aMsg, Ramp::EDirection aDirection);
private:
    enum EState
    {
        ERunning
       ,EHalted
       ,EStarting
       ,EHalting
       ,EHaltPending
       ,EFlushing
    };
private:
    MsgFactory& iMsgFactory;
    IPipelineElement& iUpstreamElement;
    IStopperObserver& iObserver;
    Mutex iLock;
    Semaphore iSem;
    EState iState;
    TUint iRampDuration;
    TUint iRemainingRampSize;
    TUint iCurrentRampValue;
    MsgQueue iQueue; // empty unless we have to split a msg during a ramp
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_STOPPER
