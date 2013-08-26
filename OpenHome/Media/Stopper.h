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
    virtual void PipelineHalted(TUint aHaltId) = 0;
};
    
/*
Element which implements ramp up/down around a pause
...or ramps down before removing the currently playing stream.
Doesn't hold any audio itself (bar the special case where applying a ramp forces a msg to be split).
Halt (pause) is implemented by telling the stopper to BeginHalt
...RampDuration of audio is then passed through, gradually ramping down
...Pull then blocks until Start() is called again
Halt(aId) is implemented by telling the stopper to start
...then ramping down as for pause
...followed by calling IStreamHandler::TryStop to attempt to stop delivery of the current stream
...followed by pulling/discarding all remaining content for that stream
...repeat for any other streams until a Halt msg with id==aId is pulled
RemoveCurrentStream ramps down as with pause then discards audio + metatext content until the next MsgEncodedStream
Flush msgs are not propogated.  Any audio which gets past this element is guaranteed to be played
*/

class Stopper : public IPipelineElementUpstream, public IStopper, private IMsgProcessor
{
    friend class SuiteStopper;
public:
    Stopper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, ISupply& aSupply, IFlushIdProvider& aIdProvider, IStopperObserver& aObserver, TUint aRampDuration);
    virtual ~Stopper();
    void Start();
    void BeginHalt();
    void BeginHalt(TUint aHaltId);
    void RemoveCurrentStream();
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
    void DoRemoveCurrentStream();
private:
    enum EState
    {
        ERunning
       ,EHalted
       ,EStarting
       ,EHalting
       ,EHaltPending
       ,EFlushPending
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
    const TUint iRampDuration;
    TUint iRemainingRampSize;
    TUint iCurrentRampValue;
    MsgQueue iQueue; // empty unless we have to split a msg during a ramp
    TBool iFlushStream;
    TBool iRemovingStream;
    TBool iResumeAfterHalt;
    TUint iTargetHaltId;
    TUint iTrackId;
    TUint iStreamId;
    IStreamHandler* iStreamHandler;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_STOPPER
