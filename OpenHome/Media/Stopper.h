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

class Stopper : public IPipelineElementUpstream, public IStopper, private IMsgProcessor
{
    friend class SuiteStopper;
public:
    Stopper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, ISupply& aSupply, IFlushIdProvider& aIdProvider, IStopperObserver& aObserver, TUint aRampDuration);
    virtual ~Stopper();
    void Start();
    void BeginHalt();
    void BeginFlush();
public: // from IPipelineElementUpstream
    Msg* Pull();
public: // from IStopper
    void RemoveStream(TUint aTrackId, TUint aStreamId);
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    Msg* ProcessMsgAudio(MsgAudio* aMsg);
    void Ramp(MsgAudio* aMsg, Ramp::EDirection aDirection);
    void DoBeginHalt();
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
    IPipelineElementUpstream& iUpstreamElement;
    ISupply& iSupply;
    IFlushIdProvider& iIdProvider;
    IStopperObserver& iObserver;
    Mutex iLock;
    Semaphore iSem;
    EState iState;
    TUint iRampDuration;
    TUint iRemainingRampSize;
    TUint iCurrentRampValue;
    MsgQueue iQueue; // empty unless we have to split a msg during a ramp
    TBool iReportHalted;
    TBool iReportFlushed;
    TBool iFlushStream;
    TBool iRemovingStream;
    TUint iTargetFlushId;
    TUint iTrackId;
    TUint iStreamId;
    IStreamHandler* iStreamHandler;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_STOPPER
