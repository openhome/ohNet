#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// ClockPullerUtils

void ClockPullerUtils::PullClock(TUint& aMultiplier, TInt aDriftJiffies, TUint64 aPeriodJiffies)
{ // static
    LOG(kMedia, "PullClock: drifted %dms in %ums\n", aDriftJiffies/(TInt)Jiffies::kPerMs, (TUint)aPeriodJiffies/Jiffies::kPerMs);
    TInt64 driftJiffies = aDriftJiffies;
    TInt64 update = -driftJiffies * aMultiplier;
    update /= (TInt64)aPeriodJiffies;
    if (update > kMaxPull || update < -kMaxPull) {
        LOG(kMedia, "Rejected pull of %llx (%d%%)\n", update, static_cast<TInt>((100*update)/aMultiplier));
    }
    else {
        aMultiplier += (TInt)update;
    }
}
