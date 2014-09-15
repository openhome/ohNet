#include <OpenHome/Media/Pipeline/DecodedAudioReservoir.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/ClockPuller.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DecodedAudioReservoir

DecodedAudioReservoir::DecodedAudioReservoir(TUint aMaxSize, TUint aMaxStreamCount)
    : AudioReservoir(aMaxSize, aMaxStreamCount)
    , iClockPuller(NULL)
    , iLock("DCAR")
    , iMaxJiffies(aMaxSize)
    , iJiffiesUntilNextUsageReport(kUtilisationSamplePeriodJiffies)
    , iThreadExcludeBlock(NULL)
    , iTrackId(Track::kIdNone)
    , iStreamId(UINT_MAX)
{
}

TUint DecodedAudioReservoir::SizeInJiffies() const
{
    return Jiffies();
}

TUint DecodedAudioReservoir::Size() const
{
    return Jiffies();
}

TUint DecodedAudioReservoir::StreamCount() const
{
    return DecodedStreamCount();
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

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgMode* aMsg)
{
    if (iClockPuller != NULL) {
        iClockPuller->StopDecodedReservoir();
    }
    iClockPuller = aMsg->ClockPuller();
    if (iClockPuller != NULL) {
        iClockPuller->StartDecodedReservoir(iMaxJiffies, kUtilisationSamplePeriodJiffies);
    }
    iTrackId = Track::kIdNone;
    iStreamId = UINT_MAX;
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgTrack* aMsg)
{
    iTrackId = aMsg->IdPipeline();
    iStreamId = UINT_MAX;
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgDecodedStream* aMsg)
{
    iStreamId = aMsg->StreamInfo().StreamId();
    if (iClockPuller != NULL) {
        iClockPuller->NewStreamDecodedReservoir(iTrackId, iStreamId);
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
    if (iClockPuller == NULL) {
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
        iThreadExcludeBlock = NULL;
        iLock.Signal();
    }
    iJiffiesUntilNextUsageReport -= aMsg->Jiffies();
    if (iJiffiesUntilNextUsageReport == 0) {
        iClockPuller->NotifySizeDecodedReservoir(Jiffies());
        iJiffiesUntilNextUsageReport = kUtilisationSamplePeriodJiffies;
    }

    return aMsg;
}
