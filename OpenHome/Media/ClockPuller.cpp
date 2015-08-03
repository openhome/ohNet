#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// ClockPullerUtils

void ClockPullerUtils::PullClock(IPullableClock& aPullableClock, TInt aDriftJiffies, TUint64 aPeriodJiffies)
{ // static
    static const TInt fracOne = 1<<29;
    LOG(kPipeline, "PullClock: %dms in %ums\n", aDriftJiffies/(TInt)Jiffies::kPerMs, (TUint)aPeriodJiffies/Jiffies::kPerMs);
    TInt64 driftJiffies = aDriftJiffies;
    TInt64 driftFrac = driftJiffies * fracOne;
    const TInt64 pull = (-driftFrac) / (TInt64)aPeriodJiffies;
    if (pull > INT_MAX || pull < INT_MIN) {
        LOG(kPipeline, "Rejected pull of %llx (%d%%)\n", pull, static_cast<TInt>((100*pull)/fracOne));
    }
    else {
        aPullableClock.PullClock((TInt)pull);
    }
}


// ClockPullerNull

void ClockPullerNull::StartTimestamp()
{
}

void ClockPullerNull::NotifyTimestampSampleRate(TUint /*aSampleRate*/)
{
}

void ClockPullerNull::NotifyTimestamp(TInt /*aDelta*/, TUint /*aNetwork*/)
{
}

void ClockPullerNull::StopTimestamp()
{
}

void ClockPullerNull::StartDecodedReservoir(TUint /*aCapacityJiffies*/, TUint /*aNotificationFrequency*/)
{
}

void ClockPullerNull::NewStreamDecodedReservoir(TUint /*aStreamId*/)
{
}

void ClockPullerNull::NotifySizeDecodedReservoir(TUint /*aJiffies*/)
{
}

void ClockPullerNull::StopDecodedReservoir()
{
}

void ClockPullerNull::StartStarvationMonitor(TUint /*aCapacityJiffies*/, TUint /*aNotificationFrequency*/)
{
}

void ClockPullerNull::NewStreamStarvationMonitor(TUint /*aStreamId*/)
{
}

void ClockPullerNull::NotifySizeStarvationMonitor(TUint /*aJiffies*/)
{
}

void ClockPullerNull::StopStarvationMonitor()
{
}
