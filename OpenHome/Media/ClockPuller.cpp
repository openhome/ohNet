#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// ClockPullerUtils

void ClockPullerUtils::PullClock(IPullableClock& aPullableClock, TInt aDriftJiffies, TUint64 aPeriodJiffies)
{ // static
    Log::Print("NotifyClockDrift: %dms in %ums\n", aDriftJiffies/(TInt)Jiffies::kPerMs, aPeriodJiffies/Jiffies::kPerMs);
    TInt64 drift = (TInt64)(aDriftJiffies * 100) << 29LL;
    const TInt64 pull = (drift) / ((TInt64)aPeriodJiffies);
    if (pull > INT_MAX || pull < INT_MIN) {
        Log::Print("Rejected pull of %llx (%d%%)\n", pull, pull/(1<<29));
    }
    else {
        aPullableClock.PullClock((TInt32)pull);
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
