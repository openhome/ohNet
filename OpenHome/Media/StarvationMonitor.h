#ifndef HEADER_PIPELINE_STARVATION_MONITOR
#define HEADER_PIPELINE_STARVATION_MONITOR

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Stopper.h> // FIXME - inappropriate location for IPipelineElement

namespace OpenHome {
namespace Media {

/*
Fixed buffer which implements a delay (prob 100ms) to allow time for songcast sending

Starts with BufferSize of silence.
Pulls audio, stopping pulling whenever it grows above a 'normal use' threshold (BufferSize)
If audio drops below starvation threshold, ramp down (then send halt?)
After starvation, pull until audio reaches an upper 'gorge' threshold before start delivering it again.
...don't pull more audio until stored falls to normal threshold
If halt msg encountered, allow buffer to be exhausted without ramping down
Halt msg or startup allows us to grow from little/no data without ramping up
*/
    
class StarvationMonitor : private MsgQueueJiffies, public IPipelineElement
{
public:
    StarvationMonitor(MsgFactory& aMsgFactory, TUint aSize, TUint aStarvationThreshold, TUint aGorgeSize, TUint aRampUpSize);
    void Enqueue(Msg* aMsg);
public: // from IPipelineElement
    Msg* Pull();
private:
    enum EStatus
    {
        ERunning
       ,ERampingDown
       ,EStarving
       ,ERampingUp
    };
private:
    MsgAudio* DoProcessMsgOut(MsgAudio* aMsg);
    void Ramp(MsgAudio* aMsg, TUint aRampDuration, Ramp::EDirection aDirection);
private: // from MsgQueueJiffies
    void ProcessMsgIn(MsgHalt* aMsg);
    void ProcessMsgIn(MsgFlush* aMsg);
    Msg* ProcessMsgOut(MsgAudioPcm* aMsg);
    Msg* ProcessMsgOut(MsgSilence* aMsg);
private:
    TUint iNormalMax;
    TUint iStarvationThreshold;
    TUint iGorgeSize;
    TUint iRampUpSize;
    Mutex iLock;
    Semaphore iSemIn;
    Semaphore iSemOut;
    EStatus iStatus;
    TUint iCurrentRampValue;
    TUint iRampDownDuration;
    TUint iRemainingRampSize;
    TBool iPlannedHalt;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_STARVATION_MONITOR
