#include <OpenHome/Media/Pipeline/DecodedAudioReservoir.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Media/Debug.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DecodedAudioReservoir

DecodedAudioReservoir::DecodedAudioReservoir(MsgFactory& aMsgFactory, TUint aMaxSize, TUint aMaxStreamCount, TUint aGorgeSize)
    : iMsgFactory(aMsgFactory)
    , iLock("DCR1")
    , iMaxJiffies(aMaxSize)
    , iMaxStreamCount(aMaxStreamCount)
    , iClockPuller(nullptr)
    , iStreamHandler(nullptr)
    , iGorgeLock("DCR2")
    , iGorgeSize(aGorgeSize)
    , iSemOut("DCR3", 0)
    , iCanGorge(false)
    , iShouldGorge(false)
    , iStartOfMode(false)
    , iGorging(false)
    , iPriorityMsgCount(0)
{
}

TUint DecodedAudioReservoir::SizeInJiffies() const
{
    return Jiffies();
}

Msg* DecodedAudioReservoir::Pull()
{
    iGorgeLock.Wait();
    TBool wait = (iGorging && Jiffies() < iGorgeSize);
    if (wait) {
        (void)iSemOut.Clear();
    }
    iGorgeLock.Signal();
    if (wait) {
        iSemOut.Wait();
    }
    Msg* msg = AudioReservoir::Pull();
    iGorgeLock.Wait();
    if (iShouldGorge
        && iPriorityMsgCount == 0
        && !iStartOfMode
        && Jiffies() < iGorgeSize) {
        iShouldGorge = false;
        SetGorging(true, "Pull");
    }
    iGorgeLock.Signal();
    return msg;
}

void DecodedAudioReservoir::Push(Msg* aMsg)
{
    iGorgeLock.Wait();
    const TUint oldPriorityMsgCount = iPriorityMsgCount;
    iGorgeLock.Signal();
    DoEnqueue(aMsg);
    iGorgeLock.Wait();
    if (iGorging) {
        if (Jiffies() >= iGorgeSize) {
            iGorging = false;
            iSemOut.Signal();
        }
        else if (oldPriorityMsgCount == 0 && iPriorityMsgCount > 0) {
            iGorging = false;
            iShouldGorge = true;
            iSemOut.Signal();
        }
    }
    iGorgeLock.Signal();
}

TBool DecodedAudioReservoir::IsFull() const
{
    return (Jiffies() > iMaxJiffies         ||
            TrackCount() >= iMaxStreamCount ||
            DecodedStreamCount() >= iMaxStreamCount);
}

void DecodedAudioReservoir::SetGorging(TBool aGorging, const TChar* aId)
{
    const TBool unblockRight = (iGorging && !aGorging);
    LOG(kPipeline, "Gorger::SetGorging(%u) from %s.  unblockRight=%u\n",
                   aGorging, aId, unblockRight);
    iGorging = aGorging;
    if (unblockRight) {
        iSemOut.Signal();
    }
}

void DecodedAudioReservoir::ProcessMsgIn(MsgMode* aMsg)
{
    AutoMutex _(iLock);
    if (iClockPuller != nullptr) {
        iClockPuller->Stop();
    }
    iClockPuller = aMsg->ClockPullers().PipelineBuffer();

    iStartOfMode = true;
    iShouldGorge = false;
    iPriorityMsgCount++;
    SetGorging(false, "ModeIn");
}

void DecodedAudioReservoir::ProcessMsgIn(MsgTrack* /*aMsg*/)
{
    BlockIfFull();
    iPriorityMsgCount++;
}

void DecodedAudioReservoir::ProcessMsgIn(MsgDrain* /*aMsg*/)
{
    iLock.Wait();
    if (iClockPuller != nullptr) {
        iClockPuller->Stop();
    }
    iLock.Signal();
    iGorgeLock.Wait();
    iPriorityMsgCount++;
    iGorgeLock.Signal();
}

void DecodedAudioReservoir::ProcessMsgIn(MsgEncodedStream* /*aMsg*/)
{
    BlockIfFull();
    iPriorityMsgCount++;
}

void DecodedAudioReservoir::ProcessMsgIn(MsgHalt* /*aMsg*/)
{
    iPriorityMsgCount++;
}

void DecodedAudioReservoir::ProcessMsgIn(MsgDecodedStream* /*aMsg*/)
{
    BlockIfFull();
    iPriorityMsgCount++;
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

void DecodedAudioReservoir::ProcessMsgIn(MsgQuit* /*aMsg*/)
{
    iPriorityMsgCount++; // last msg to be handled so we don't bother decrementing count on way out
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgMode* aMsg)
{
    iGorgeLock.Wait();
    iMode.Replace(aMsg->Mode());
    iCanGorge = !aMsg->Info().IsRealTime();
    iShouldGorge = iCanGorge;
    iPriorityMsgCount--;
    iGorgeLock.Signal();
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgTrack* aMsg)
{
    iGorgeLock.Wait();
    iPriorityMsgCount--;
    iGorgeLock.Signal();
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgDrain* aMsg)
{
    iGorgeLock.Wait();
    iPriorityMsgCount--;
    iGorgeLock.Signal();
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgEncodedStream* aMsg)
{
    iGorgeLock.Wait();
    iPriorityMsgCount--;
    iGorgeLock.Signal();
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgDecodedStream* aMsg)
{
    AutoMutex _(iLock);
    iStreamHandler = aMsg->StreamInfo().StreamHandler();
    auto msg = iMsgFactory.CreateMsgDecodedStream(aMsg, this);
    aMsg->RemoveRef();

    iGorgeLock.Wait();
    iPriorityMsgCount--;
    iStartOfMode = false;
    iGorgeLock.Signal();

    return msg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgHalt* aMsg)
{
    iGorgeLock.Wait();
    iPriorityMsgCount--;
    iShouldGorge = iCanGorge;
    iGorgeLock.Signal();
    return aMsg;
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
    {
        AutoMutex __(iGorgeLock);
        if (aStarving
            && aMode == iMode
            && iCanGorge
            && iPriorityMsgCount == 0
            && !iStartOfMode) {
            SetGorging(true, "NotifyStarving");
        }
    }
    AutoMutex _(iLock);
    if (iStreamHandler != nullptr) {
        iStreamHandler->NotifyStarving(aMode, aStreamId, aStarving);
    }
}
