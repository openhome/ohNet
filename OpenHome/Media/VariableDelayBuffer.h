#ifndef HEADER_PIPELINE_VARIABLE_DELAY_BUFFER
#define HEADER_PIPELINE_VARIABLE_DELAY_BUFFER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

class VariableDelayBuffer : private MsgQueueJiffies
{
public:
    static const TUint kDefaultRampTime = Jiffies::kJiffiesPerMs * 50;
public:
    VariableDelayBuffer(MsgFactory& aMsgFactory, TUint aMaxSizeJiffies, TUint aInitialDelay, TUint aRampTime = kDefaultRampTime);
    ~VariableDelayBuffer();
    void AdjustDelay(TUint aJiffies);
    void Enqueue(Msg* aMsg);
    Msg* Dequeue();
private:
    MsgAudio* DoProcessMsgOut(MsgAudio* aMsg);
    void RampMsg(MsgAudio* aMsg);
private: // from MsgQueueJiffies
    Msg* ProcessMsgOut(MsgAudioPcm* aMsg);
    Msg* ProcessMsgOut(MsgSilence* aMsg);
private:
    enum EStatus
    {
        EDefault
       ,ERampingDown
       ,ERampedDown
       ,ERampingUp
    };
private:
    MsgFactory& iMsgFactory;
    TUint iMaxJiffies;
    TUint iDelayJiffies;
    Mutex iLock;
    Semaphore iSem;
    TInt iDelayAdjustment;
    EStatus iStatus;
    Ramp::EDirection iRampDirection;
    const TUint iRampDuration;
    TUint iCurrentRampValue;
    TUint iRemainingRampSize;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_VARIABLE_DELAY_BUFFER
