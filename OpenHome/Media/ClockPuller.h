#ifndef HEADER_CLOCK_PULLER
#define HEADER_CLOCK_PULLER

#include <OpenHome/Types.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>

#include <vector>

namespace OpenHome {
namespace Media {

class IClockPuller
{
public:
    virtual ~IClockPuller() {}
    virtual void StartTimestamp() = 0;
    virtual void NotifyTimestamp(TInt aDrift, TUint aNetwork) = 0;
    virtual void StopTimestamp() = 0;
    virtual void StartDecodedReservoir(TUint aCapacityJiffies, TUint aNotificationFrequency) = 0;
    virtual void NewStreamDecodedReservoir(TUint aTrackId, TUint aStreamId) = 0;
    virtual void NotifySizeDecodedReservoir(TUint aJiffies) = 0;
    virtual void StopDecodedReservoir() = 0;
    virtual void StartStarvationMonitor(TUint aCapacityJiffies, TUint aNotificationFrequency) = 0;
    virtual void NewStreamStarvationMonitor(TUint aTrackId, TUint aStreamId) = 0;
    virtual void NotifySizeStarvationMonitor(TUint aJiffies) = 0;
    virtual void StopStarvationMonitor() = 0;
};

class IPullableClock
{
public:
    virtual ~IPullableClock() {}
    /**
     * Signal that the clock should be pulled.
     *
     * @param[in] aValue      Percentage of current rate in the range (4%..-4%].
     *                        Top bit gives sign, next two bits are integer value, remaining 29 bits are fraction.
     */
    virtual void PullClock(TInt32 aValue) = 0;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_CLOCK_PULLER
