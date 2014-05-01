#ifndef HEADER_PIPELINE_WAITER
#define HEADER_PIPELINE_WAITER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

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
class Waiter : public IPipelineElementUpstream, private IMsgProcessor
{
public:
    Waiter(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IWaiterObserver& aObserver, TUint aRampDuration);
    virtual ~Waiter();
    void Wait(TUint aFlushId, TBool aRampDown);
public: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg);
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
    void DoWait();
    Msg* ProcessFlushable(Msg* aMsg);
    Msg* ProcessAudio(MsgAudio* aMsg);
    void NewStream();
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
    Mutex iLock;
    EState iState;
    const TUint iRampDuration;
    TUint iRemainingRampSize;
    TUint iCurrentRampValue;
    MsgQueue iQueue; // empty unless we have to split a msg during a ramp
    TUint iTargetFlushId;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_WAITER
