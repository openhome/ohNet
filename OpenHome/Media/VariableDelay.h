#ifndef HEADER_PIPELINE_VARIABLE_DELAY
#define HEADER_PIPELINE_VARIABLE_DELAY

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Stopper.h> // FIXME - inappropriate location for IPipelineElement

namespace OpenHome {
namespace Media {

class VariableDelay : public IPipelineElement, private IMsgProcessor
{
    static const TUint kMaxMsgSilenceDuration = Jiffies::kJiffiesPerMs * 5;
public:
    VariableDelay(MsgFactory& aMsgFactory, IPipelineElement& aUpstreamElement, TUint aRampDuration);
    ~VariableDelay();
    void AdjustDelay(TUint aJiffies);
public: // from IPipelineElement
    Msg* Pull();
private:
    MsgAudio* DoProcessAudioMsg(MsgAudio* aMsg);
    void RampMsg(MsgAudio* aMsg);
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
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
    IPipelineElement& iUpstreamElement;
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
