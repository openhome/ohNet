#include <OpenHome/Media/DecodedAudioReservoir.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/ClockPuller.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DecodedAudioReservoir

DecodedAudioReservoir::DecodedAudioReservoir(TUint aMaxSize, IClockPuller& aClockPuller)
    : AudioReservoir(aMaxSize)
    , iClockPuller(aClockPuller)
    , iLock("DCAR")
    , iJiffiesUntilNextUsageReport(kUtilisationSamplePeriodJiffies)
    , iThreadExcludeBlock(NULL)
    , iTrackIsPullable(false)
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

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgTrack* aMsg)
{
    iTrackIsPullable = aMsg->Track().Pullable();
    if (iTrackIsPullable) {
        iJiffiesUntilNextUsageReport = kUtilisationSamplePeriodJiffies;
    }
    iClockPuller.Stop();
    return aMsg;
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
    if (!iTrackIsPullable) {
        return aMsg;
    }
    // FIXME - should maybe take different action if we're flushing (currently held as private state in parent)
    if (iJiffiesUntilNextUsageReport < aMsg->Jiffies()) {
        MsgAudio* remaining = aMsg->Split(static_cast<TUint>(iJiffiesUntilNextUsageReport));
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
    iJiffiesUntilNextUsageReport -= aMsg->Jiffies();
    if (iJiffiesUntilNextUsageReport == 0) {
        iClockPuller.NotifySize(Jiffies());
        iJiffiesUntilNextUsageReport = kUtilisationSamplePeriodJiffies;
    }

    return aMsg;
}
