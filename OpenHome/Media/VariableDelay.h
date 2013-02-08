#ifndef HEADER_PIPELINE_VARIABLE_DELAY
#define HEADER_PIPELINE_VARIABLE_DELAY

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which introduces a delay (likely for lip syncing)
If the delay is increased, silence is introduced.
If the delay is decreased, audio (pulled from upstream) is discarded.
Before any change in delay is actioned, audio spends RampDuration ramping down.
After a delay is actioned, audio spends RampDuration ramping up.
FIXME - no handling of pause-resumes
*/
    
class VariableDelay : public IPipelineElementUpstream, private IMsgProcessor
{
    static const TUint kMaxMsgSilenceDuration = Jiffies::kJiffiesPerMs * 5;
    friend class SuiteVariableDelay;
public:
    VariableDelay(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aRampDuration);
    virtual ~VariableDelay();
    void AdjustDelay(TUint aJiffies);
public: // from IPipelineElementUpstream
    Msg* Pull();
private:
    MsgAudio* DoProcessAudioMsg(MsgAudio* aMsg);
    void RampMsg(MsgAudio* aMsg);
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
    enum EStatus
    {
        ERunning
       ,ERampingDown
       ,ERampedDown
       ,ERampingUp
    };
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    TUint iDelayJiffies;
    Mutex iLock;
    TInt iDelayAdjustment;
    EStatus iStatus;
    Ramp::EDirection iRampDirection;
    const TUint iRampDuration;
    TUint iCurrentRampValue;
    TUint iRemainingRampSize;
    MsgQueue iQueue; // empty unless we have to split a msg during a ramp
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_VARIABLE_DELAY
