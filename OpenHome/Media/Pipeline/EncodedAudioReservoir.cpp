#include <OpenHome/Media/Pipeline/EncodedAudioReservoir.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// EncodedAudioReservoir

EncodedAudioReservoir::EncodedAudioReservoir(MsgFactory& aMsgFactory, IFlushIdProvider& aFlushIdProvider, TUint aMsgCount, TUint aMaxStreamCount)
    : iMsgFactory(aMsgFactory)
    , iFlushIdProvider(aFlushIdProvider)
    , iMsgCount(aMsgCount)
    , iMaxStreamCount(aMaxStreamCount)
    , iLock2("ENCR")
    , iStreamHandler(nullptr)
    , iStreamId(IPipelineIdProvider::kStreamIdInvalid)
    , iStreamPos(0)
    , iNextFlushId(MsgFlush::kIdInvalid)
    , iSeekPos(0)
    , iPostSeekFlushId(MsgFlush::kIdInvalid)
    , iPostSeekStreamPos(0)
{
}

TUint EncodedAudioReservoir::SizeInBytes() const
{
    return EncodedBytes();
}

inline IStreamHandler* EncodedAudioReservoir::StreamHandler()
{
    iLock2.Wait();
    auto streamHandler = iStreamHandler;
    iLock2.Signal();
    return streamHandler;
}

Msg* EncodedAudioReservoir::EndSeek(Msg* aMsg)
{
    EnqueueAtHead(aMsg);
    auto flush = iMsgFactory.CreateMsgFlush(iNextFlushId);
    iNextFlushId = MsgFlush::kIdInvalid;
    iSeekPos = 0;
    return flush;
}

TBool EncodedAudioReservoir::IsFull() const
{
    return (EncodedAudioCount() > iMsgCount ||
            TrackCount() >= iMaxStreamCount ||
            EncodedStreamCount() >= iMaxStreamCount);
}

void EncodedAudioReservoir::ProcessMsgIn(MsgTrack* /*aMsg*/)
{
    BlockIfFull();
}

void EncodedAudioReservoir::ProcessMsgIn(MsgEncodedStream* /*aMsg*/)
{
    BlockIfFull();
}

void EncodedAudioReservoir::ProcessMsgIn(MsgAudioEncoded* /*aMsg*/)
{
    BlockIfFull();
}

Msg* EncodedAudioReservoir::ProcessMsgOut(MsgEncodedStream* aMsg)
{
    {
        AutoMutex _(iLock2);
        if (iNextFlushId != MsgFlush::kIdInvalid) {
            return EndSeek(aMsg);
        }
        iStreamHandler = aMsg->StreamHandler();
        iStreamId = aMsg->StreamId();
        iStreamPos = aMsg->StartPos();
    }
    auto msg = iMsgFactory.CreateMsgEncodedStream(aMsg, this);
    aMsg->RemoveRef();
    return msg;
}

Msg* EncodedAudioReservoir::ProcessMsgOut(MsgAudioEncoded* aMsg)
{
    AutoMutex _(iLock2);
    TUint64 newStreamPos = iStreamPos + aMsg->Bytes();
    if (iSeekPos != 0) {
        if (iStreamPos == iSeekPos) {
            return EndSeek(aMsg);
        }
        if (newStreamPos > iSeekPos) {
            const TUint remainingBytes = static_cast<TUint>(newStreamPos - iSeekPos);
            const TUint splitPos = aMsg->Bytes() - remainingBytes;
            auto split = aMsg->Split(splitPos);
            EnqueueAtHead(split);
            newStreamPos -= remainingBytes;
        }
        iStreamPos = newStreamPos;
        aMsg->RemoveRef();
        UnblockIfNotFull();
        return nullptr;
    }
    iStreamPos = newStreamPos;
    return aMsg;
}

Msg* EncodedAudioReservoir::ProcessMsgOut(MsgFlush* aMsg)
{
    AutoMutex _(iLock2);
    if (iPostSeekFlushId != MsgFlush::kIdInvalid && aMsg->Id() == iPostSeekFlushId) {
        iPostSeekFlushId = MsgFlush::kIdInvalid;
        iStreamPos = iPostSeekStreamPos;
        iPostSeekStreamPos = 0;
    }
    return aMsg;
}

EStreamPlay EncodedAudioReservoir::OkToPlay(TUint aStreamId)
{
    IStreamHandler* streamHandler = StreamHandler();
    if (streamHandler != nullptr) {
        return streamHandler->OkToPlay(aStreamId);
    }
    return ePlayNo;
}

TUint EncodedAudioReservoir::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    AutoMutex _(iLock2);
    const TUint64 lastBufferedPos = iStreamPos + SizeInBytes();
    if (iStreamId == aStreamId && iStreamPos <= aOffset && lastBufferedPos >= aOffset) {
        iSeekPos = aOffset;
        if (iNextFlushId == MsgFlush::kIdInvalid) {
            iNextFlushId = iFlushIdProvider.NextFlushId();
        }
        LOG(kPipeline, "TrySeek(%u, %llu) can be satisfied by encoded reservoir (runs %llu ... %llu)\n",
                        aStreamId, aOffset, iStreamPos, lastBufferedPos);
        return iNextFlushId;
    }
    if (iStreamHandler != nullptr) {
        const TUint flushId = iStreamHandler->TrySeek(aStreamId, aOffset);
        if (flushId != MsgFlush::kIdInvalid) {
            iPostSeekFlushId = flushId;
            iPostSeekStreamPos = aOffset;
            return flushId;
        }
    }
    return MsgFlush::kIdInvalid;
}

TUint EncodedAudioReservoir::TryDiscard(TUint /*aJiffies*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint EncodedAudioReservoir::TryStop(TUint aStreamId)
{
    IStreamHandler* streamHandler = StreamHandler();
    if (streamHandler != nullptr) {
        return streamHandler->TryStop(aStreamId);
    }
    return MsgFlush::kIdInvalid;
}

void EncodedAudioReservoir::NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving)
{
    IStreamHandler* streamHandler = StreamHandler();
    if (streamHandler != nullptr) {
        streamHandler->NotifyStarving(aMode, aStreamId, aStarving);
    }
}
