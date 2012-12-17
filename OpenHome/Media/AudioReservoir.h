#ifndef HEADER_PIPELINE_AUDIO_RESERVOIR
#define HEADER_PIPELINE_AUDIO_RESERVOIR

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

/*
Abstract element which buffers [0..MaxSize] units of audio.
Msgs can be pulled whenever available.
Blocks further data being enqueued when size is greater that MaxSize.
Discards all data when a Flush msg is queued.
FIXME - no handling of Halt
*/
    
class AudioReservoir : protected MsgQueueFlushable, public IPipelineElementUpstream, public IPipelineElementDownstream
{
    friend class SuiteAudioReservoir;
public:
    ~AudioReservoir();
public: // from IPipelineElementUpstream
    Msg* Pull();
public: // from IPipelineElementDownstream
    void Push(Msg* aMsg);
protected:
    AudioReservoir(TUint aMaxSize);
    TBool Enqueue(Msg* aMsg); // returns true if was blocked
private:
    virtual TUint Size() const = 0;
private:
    TUint iMaxSize;
    Mutex iLock;
    Semaphore iSem;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_AUDIO_RESERVOIR
