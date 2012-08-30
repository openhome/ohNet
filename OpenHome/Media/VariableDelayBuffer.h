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
    VariableDelayBuffer(MsgFactory& aMsgFactory, TUint aMaxSizeJiffies, TUint aInitialDelay);
    ~VariableDelayBuffer();
    void AdjustDelay(TUint aJiffies);
    void Enqueue(Msg* aMsg);
    Msg* Dequeue();
private:
    MsgAudio* DoProcessMsgOut(MsgAudio* aMsg);
private: // from MsgQueueJiffies
    Msg* ProcessMsgOut(MsgAudioPcm* aMsg);
    Msg* ProcessMsgOut(MsgSilence* aMsg);
private:
    MsgFactory& iMsgFactory;
    TUint iMaxJiffies;
    TUint iDelayJiffies;
    MsgQueue iQueue;
    Mutex iLock;
    Semaphore iSem;
    TInt iDelayAdjustment;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_VARIABLE_DELAY_BUFFER
