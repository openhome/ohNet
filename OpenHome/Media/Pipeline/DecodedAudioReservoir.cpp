#include <OpenHome/Media/Pipeline/DecodedAudioReservoir.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/ClockPuller.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DecodedAudioReservoir

DecodedAudioReservoir::DecodedAudioReservoir(TUint aMaxSize, TUint aMaxStreamCount)
    : iClockPuller(nullptr)
    , iLock("DCAR")
    , iMaxJiffies(aMaxSize)
    , iMaxStreamCount(aMaxStreamCount)
    , iJiffiesUntilNextUsageReport(kUtilisationSamplePeriodJiffies)
    , iThreadExcludeBlock(nullptr)
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

void DecodedAudioReservoir::ProcessMsgIn(MsgTrack* /*aMsg*/)
{
    DoProcessMsgIn();
}

void DecodedAudioReservoir::ProcessMsgIn(MsgDecodedStream* /*aMsg*/)
{
    DoProcessMsgIn();
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
    const TBool blockIfFull =  (iThreadExcludeBlock == nullptr || Thread::Current() != iThreadExcludeBlock);
    iLock.Signal();
    if (blockIfFull) {
        BlockIfFull();
    }
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgMode* aMsg)
{
    if (iClockPuller != nullptr) {
        iClockPuller->Stop();
    }
    iClockPuller = aMsg->ClockPullers().ReservoirLeft();
    if (iClockPuller != nullptr) {
        iClockPuller->Start(kUtilisationSamplePeriodJiffies);
    }
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgDrain* aMsg)
{
    if (iClockPuller != nullptr) {
        iClockPuller->Reset();
    }
    iJiffiesUntilNextUsageReport = kUtilisationSamplePeriodJiffies;
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgDecodedStream* aMsg)
{
    if (iClockPuller != nullptr) {
        iClockPuller->NewStream(aMsg->StreamInfo().SampleRate());
    }
    iJiffiesUntilNextUsageReport = kUtilisationSamplePeriodJiffies;
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
    if (iClockPuller == nullptr) {
        return aMsg;
    }
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
        iThreadExcludeBlock = nullptr;
        iLock.Signal();
    }
    iJiffiesUntilNextUsageReport -= aMsg->Jiffies();
    if (iJiffiesUntilNextUsageReport == 0) {
        const TUint multiplier = iClockPuller->NotifySize(Jiffies());
        aMsg->SetClockPull(multiplier);
        iJiffiesUntilNextUsageReport = kUtilisationSamplePeriodJiffies;
    }

    return aMsg;
}
