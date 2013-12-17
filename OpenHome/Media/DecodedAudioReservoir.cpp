#include <OpenHome/Media/DecodedAudioReservoir.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DecodedAudioReservoir

DecodedAudioReservoir::DecodedAudioReservoir(TUint aMaxSize)
    : AudioReservoir(aMaxSize)
    , iLock("DCAR")
    , iHistoryCount(0)
    , iHistoryNextIndex(0)
    , iJiffiesUntilNextHistoryPoint(kUtilisationSamplePeriodJiffies)
    , iThreadExcludeBlock(NULL)
{
}

TUint DecodedAudioReservoir::Size() const
{
    return Jiffies();
}

void DecodedAudioReservoir::ProcessMsgIn(MsgAudioPcm* /*aMsg*/)
{
    DoProcessMsgIn();
}

void DecodedAudioReservoir::ProcessMsgIn(MsgSilence* /*aMsg*/)
{
    DoProcessMsgIn();
}

void DecodedAudioReservoir::DoProcessMsgIn()
{
    iLock.Wait();
    const TBool blockIfFull =  (iThreadExcludeBlock == NULL || Thread::Current() != iThreadExcludeBlock);
    iLock.Signal();
    if (blockIfFull) {
        BlockIfFull();
    }
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgAudioPcm* aMsg)
{
    return DoProcessMsgOut(aMsg);
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgSilence* aMsg)
{
    return DoProcessMsgOut(aMsg);
}

Msg* DecodedAudioReservoir::DoProcessMsgOut(MsgAudio* aMsg)
{
    // FIXME - should maybe take dfferent action if we're flushing (currently held as private state in parent)
    if (iJiffiesUntilNextHistoryPoint < aMsg->Jiffies()) {
        MsgAudio* remaining = aMsg->Split(static_cast<TUint>(iJiffiesUntilNextHistoryPoint));
        /* calling EnqueueAtHead risks blocking the pulling thread (if the pushing thread
           has already been scheduled and filled the gap pulling this msg created).
           Avoid this by disabling calls to BlockIfFull() around the EnqueueAtHead() call */
        iLock.Wait();
        iThreadExcludeBlock = Thread::Current();
        iLock.Signal();
        EnqueueAtHead(remaining);
        iLock.Wait();
        iThreadExcludeBlock = NULL;
        iLock.Signal();
    }
    iJiffiesUntilNextHistoryPoint -= aMsg->Jiffies();
    if (iJiffiesUntilNextHistoryPoint == 0) {
        iHistory[iHistoryNextIndex++] = Jiffies();
        if (iHistoryNextIndex == kMaxUtilisationSamplePoints) {
            iHistoryNextIndex = kMaxUtilisationSamplePoints;
        }
        if (iHistoryCount < kMaxUtilisationSamplePoints) {
            iHistoryCount++;
        }
        iJiffiesUntilNextHistoryPoint = kUtilisationSamplePeriodJiffies;
    }

    return aMsg;
}
