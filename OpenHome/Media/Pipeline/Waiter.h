#ifndef HEADER_PIPELINE_WAITER
#define HEADER_PIPELINE_WAITER

#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>

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
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
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
