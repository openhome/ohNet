#ifndef HEADER_PIPELINE_AUDIO_RESERVOIR
#define HEADER_PIPELINE_AUDIO_RESERVOIR

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Stopper.h> // FIXME - inappropriate location for IPipelineElement

namespace OpenHome {
namespace Media {

/*
Element which buffers [0..MaxSize] jiffies of decoded audio.
Msgs can be pulled whenever available.
Blocks further data being enqueued when size is greater that MaxSize.
Discards all data when a Flush msg is queued.
FIXME - no handling of Halt
*/
    
class AudioReservoir : private MsgQueueJiffies, public IPipelineElement
{
    friend class SuiteAudioReservoir;
public:
    AudioReservoir(TUint aMaxSize);
    ~AudioReservoir();
    TBool Enqueue(Msg* aMsg); // returns true if was blocked (due to reservoir temporarily being full)
public: // from IPipelineElement
    Msg* Pull();
private: // from MsgQueueJiffies
    void ProcessMsgIn(MsgFlush* aMsg);
    Msg* ProcessMsgOut(MsgFlush* aMsg);
private:
    enum EStatus
    {
        ERunning
       ,EFlushing
    };
private:
    TUint iMaxSize;
    Mutex iLock;
    Semaphore iSem;
    EStatus iStatus;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_AUDIO_RESERVOIR
