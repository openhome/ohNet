#include <OpenHome/Media/Pipeline/DecodedAudioReservoir.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/ClockPuller.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DecodedAudioReservoir

DecodedAudioReservoir::DecodedAudioReservoir(MsgFactory& aMsgFactory, TUint aMaxSize, TUint aMaxStreamCount)
    : iMsgFactory(aMsgFactory)
    , iLock("DCR1")
    , iMaxJiffies(aMaxSize)
    , iMaxStreamCount(aMaxStreamCount)
    , iClockPuller(nullptr)
    , iStreamHandler(nullptr)
{
}

TUint DecodedAudioReservoir::SizeInJiffies() const
{
    return Jiffies();
}

TBool DecodedAudioReservoir::IsFull() const
{
    return (Jiffies() > iMaxJiffies         ||
            TrackCount() >= iMaxStreamCount ||
            DecodedStreamCount() >= iMaxStreamCount);
}

void DecodedAudioReservoir::ProcessMsgIn(MsgMode* aMsg)
{
    AutoMutex _(iLock);
    if (iClockPuller != nullptr) {
        iClockPuller->Stop();
    }
    iClockPuller = aMsg->ClockPullers().PipelineBuffer();
}

void DecodedAudioReservoir::ProcessMsgIn(MsgTrack* /*aMsg*/)
{
    BlockIfFull();
}

void DecodedAudioReservoir::ProcessMsgIn(MsgDrain* /*aMsg*/)
{
    AutoMutex _(iLock);
    if (iClockPuller != nullptr) {
        iClockPuller->Stop();
    }
}

void DecodedAudioReservoir::ProcessMsgIn(MsgDecodedStream* /*aMsg*/)
{
    BlockIfFull();
}

void DecodedAudioReservoir::ProcessMsgIn(MsgAudioPcm* aMsg)
{
    BlockIfFull();
    AutoMutex _(iLock);
    if (iClockPuller != nullptr) {
        aMsg->SetObserver(*iClockPuller);
    }
}

void DecodedAudioReservoir::ProcessMsgIn(MsgSilence* /*aMsg*/)
{
    ASSERTS(); // don't expect anything upstream to be generating silence
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgDecodedStream* aMsg)
{
    AutoMutex _(iLock);
    iStreamHandler = aMsg->StreamInfo().StreamHandler();
    auto msg = iMsgFactory.CreateMsgDecodedStream(aMsg, this);
    aMsg->RemoveRef();
    return msg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgAudioPcm* aMsg)
{
    return aMsg;
}

EStreamPlay DecodedAudioReservoir::OkToPlay(TUint aStreamId)
{
    AutoMutex _(iLock);
    if (iStreamHandler == nullptr) {
        return ePlayNo;
    }
    return iStreamHandler->OkToPlay(aStreamId);
}

TUint DecodedAudioReservoir::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint DecodedAudioReservoir::TryStop(TUint aStreamId)
{
    AutoMutex _(iLock);
    if (iStreamHandler == nullptr) {
        return MsgFlush::kIdInvalid;
    }
    const TUint flushId = iStreamHandler->TryStop(aStreamId);
    if (flushId != MsgFlush::kIdInvalid && iClockPuller != nullptr) {
        iClockPuller->Stop();
    }
    return flushId;
}

void DecodedAudioReservoir::NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving)
{
    AutoMutex _(iLock);
    if (iStreamHandler != nullptr) {
        iStreamHandler->NotifyStarving(aMode, aStreamId, aStarving);
    }
}
