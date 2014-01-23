#include <OpenHome/Media/Rewinder.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Pipeline.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Standard.h>

#include <limits.h>

namespace OpenHome {
namespace Media {

class RewindQueueProcessor : private IMsgProcessor
{
    static const TUint kDefaultTrackId = UINT_MAX;
    static const TUint kDefaultStreamId = UINT_MAX;
public:
    RewindQueueProcessor(MsgQueue& aQueue);
    void ClearStream();
    TBool UpdateIds(TUint& aTrackId, TUint& aStreamId);
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
    MsgQueue* iQueue;
    TUint iTrackId;
    TUint iStreamId;
    TBool iClearedStream;
};

class MsgCloner : private IMsgProcessor
{
public:
    static Msg* NewRef(Msg& aMsg);
private:
    MsgCloner();
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
};

} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;

// RewindQueueProcessor

RewindQueueProcessor::RewindQueueProcessor(MsgQueue& aQueue)
    : iQueue(&aQueue)
    , iTrackId(kDefaultTrackId)
    , iStreamId(kDefaultStreamId)
    , iClearedStream(false)
{
}

void RewindQueueProcessor::ClearStream()
{
    while (!iClearedStream && !iQueue->IsEmpty()) {
        Msg* msg = iQueue->Dequeue();
        msg = msg->Process(*this);
        msg->RemoveRef();
    }
}

TBool RewindQueueProcessor::UpdateIds(TUint& aTrackId, TUint& aStreamId)
{
    if (iTrackId != kDefaultTrackId) {
        aTrackId = iTrackId;
    }
    if (iTrackId != kDefaultStreamId) {
        aStreamId = iStreamId;
    }
    return iClearedStream;
}

Msg* RewindQueueProcessor::ProcessMsg(MsgAudioEncoded* aMsg)
{
    return aMsg;
}

Msg* RewindQueueProcessor::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* RewindQueueProcessor::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* RewindQueueProcessor::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* RewindQueueProcessor::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* RewindQueueProcessor::ProcessMsg(MsgTrack* aMsg)
{
    iTrackId = aMsg->IdPipeline();
    return aMsg;
}

Msg* RewindQueueProcessor::ProcessMsg(MsgEncodedStream* aMsg)
{
    iClearedStream = true;
    iStreamId = aMsg->StreamId();
    return aMsg;
}

Msg* RewindQueueProcessor::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* RewindQueueProcessor::ProcessMsg(MsgHalt* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* RewindQueueProcessor::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* RewindQueueProcessor::ProcessMsg(MsgQuit* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}


// MsgCloner

Msg* MsgCloner::NewRef(Msg& aMsg)
{ // static
    MsgCloner self;
    return aMsg.Process(self);
}

MsgCloner::MsgCloner()
{
}

Msg* MsgCloner::ProcessMsg(MsgAudioEncoded* aMsg)
{
    return aMsg->Clone();
}

Msg* MsgCloner::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* MsgCloner::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* MsgCloner::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* MsgCloner::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* MsgCloner::ProcessMsg(MsgTrack* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* MsgCloner::ProcessMsg(MsgEncodedStream* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* MsgCloner::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* MsgCloner::ProcessMsg(MsgHalt* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* MsgCloner::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* MsgCloner::ProcessMsg(MsgQuit* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}


// Rewinder

Rewinder::Rewinder(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iStreamHandler(NULL)
    , iBuffering(false)
    , iLock("REWI")
    , iTrackIdLatest(UINT_MAX)
    , iStreamIdLatest(UINT_MAX)
    , iTrackIdEarliest(UINT_MAX)
    , iStreamIdEarliest(UINT_MAX)
{
    iQueueCurrent = new MsgQueue();
    iQueueNext = new MsgQueue();
}

Rewinder::~Rewinder()
{
    delete iQueueCurrent;
    delete iQueueNext;
}

void Rewinder::DrainQueue(MsgQueue& aQueue)
{
    Msg* msg;
    while (!aQueue.IsEmpty()) {
        msg = aQueue.Dequeue();
        msg->RemoveRef();
    }
}

void Rewinder::TryBuffer(Msg* aMsg)
{
    if (iBuffering) {
        try {
            Msg* copy = MsgCloner::NewRef(*aMsg);
            iQueueNext->Enqueue(copy);
        }
        catch (AllocatorNoMemory&) {
            // can't clone msg; push back onto head of current queue so memory isn't lost
            iQueueCurrent->EnqueueAtHead(aMsg);
            throw; // can't do anything other than pass exception on now
        }
    }
}

Msg* Rewinder::Pull()
{
    Msg* msg = NULL;
    do {
        iLock.Wait();
        if (!iQueueCurrent->IsEmpty()) {
            msg = iQueueCurrent->Dequeue();
            TryBuffer(msg);
        }
        iLock.Signal();
        if (msg == NULL) {
            msg = iUpstreamElement.Pull();
            if (msg != NULL) {
                iLock.Wait();
                msg = msg->Process(*this);
                iLock.Signal();
            }
        }
    } while (msg == NULL);
    return msg;
}

Msg* Rewinder::ProcessMsg(MsgAudioEncoded* aMsg)
{
    TryBuffer(aMsg);
    return aMsg;
}

Msg* Rewinder::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return NULL;
}

Msg* Rewinder::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return NULL;
}

Msg* Rewinder::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // only expect encoded audio at this stage of the pipeline
    return NULL;
}

Msg* Rewinder::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); // expect this Msg to be generated by a downstream decoder element
    return NULL;
}

Msg* Rewinder::ProcessMsg(MsgTrack* aMsg)
{
    iTrackIdLatest = aMsg->IdPipeline();
    if (!iBuffering) {
        iTrackIdEarliest = iTrackIdLatest;
    }
    TryBuffer(aMsg);
    return aMsg;
}

Msg* Rewinder::ProcessMsg(MsgEncodedStream* aMsg)
{
    iStreamHandler = aMsg->StreamHandler();
    iStreamIdLatest = aMsg->StreamId();
    if (!iBuffering) {
        iStreamIdEarliest = iStreamIdLatest;
    }
    MsgEncodedStream* msg = iMsgFactory.CreateMsgEncodedStream(aMsg->Uri(), aMsg->MetaText(), aMsg->TotalBytes(), aMsg->StreamId(), aMsg->Seekable(), aMsg->Live(), this);
    aMsg->RemoveRef();
    TryBuffer(msg);
    iBuffering = true;
    return msg;
}

Msg* Rewinder::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* Rewinder::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* Rewinder::ProcessMsg(MsgFlush* aMsg)
{
    return aMsg;
}

Msg* Rewinder::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}

void Rewinder::Rewind()
{
    AutoMutex a(iLock);
    ASSERT(iBuffering);

    while (!iQueueCurrent->IsEmpty()) {
        iQueueNext->Enqueue(iQueueCurrent->Dequeue());
    }
    MsgQueue* tmpQueue = iQueueCurrent;
    iQueueCurrent = iQueueNext;
    iQueueNext = tmpQueue;
}

void Rewinder::Stop(TUint aTrackId, TUint aStreamId)
{
    AutoMutex a(iLock);
    ASSERT(iBuffering);
    ASSERT(aTrackId == iTrackIdEarliest);
    ASSERT(aStreamId == iStreamIdEarliest);
    DoStop();
}

void Rewinder::DoStop()
{
    RewindQueueProcessor rqp(*iQueueNext);
    rqp.ClearStream();
    iBuffering = rqp.UpdateIds(iTrackIdEarliest, iStreamIdEarliest);
}

EStreamPlay Rewinder::OkToPlay(TUint aTrackId, TUint aStreamId)
{
    return iStreamHandler->OkToPlay(aTrackId, aStreamId);
}

TUint Rewinder::TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset)
{
    AutoMutex a(iLock);
    // can't seek if buffering current track
    ASSERT(!iBuffering || (aTrackId != iTrackIdLatest) || (aStreamId != iStreamIdLatest));
    return iStreamHandler->TrySeek(aTrackId, aStreamId, aOffset);
}

TUint Rewinder::TryStop(TUint aTrackId, TUint aStreamId)
{
    AutoMutex a(iLock);
    const TUint flushId = iStreamHandler->TryStop(aTrackId, aStreamId);
    if (flushId != MsgFlush::kIdInvalid && iBuffering && aTrackId == iTrackIdLatest && aStreamId == iStreamIdLatest) {
        ASSERT(iTrackIdEarliest == iTrackIdLatest);
        ASSERT(iStreamIdEarliest == iStreamIdLatest);
        DoStop();
    }
    return flushId;
}
