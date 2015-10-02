#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/*
Abstract element which buffers [0..MaxSize] units of audio.
Msgs can be pulled whenever available.
Blocks further data being enqueued when size is greater that MaxSize.
Discards all data when a Flush msg is queued.
FIXME - no handling of Halt
*/
    
class AudioReservoir : protected MsgReservoir, public IPipelineElementUpstream, public IPipelineElementDownstream
{
    friend class SuiteAudioReservoir;
public:
    ~AudioReservoir();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
public: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
protected:
    AudioReservoir();
    void BlockIfFull();
    void UnblockIfNotFull();
private:
    virtual TBool IsFull() const = 0;
private:
    Mutex iLock;
    Semaphore iSem;
};

} // namespace Media
} // namespace OpenHome

