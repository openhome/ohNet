#ifndef HEADER_CLOCK_PULLER
#define HEADER_CLOCK_PULLER

#include <OpenHome/Types.h>

namespace OpenHome {
namespace Media {

class IClockPuller
{
public:
    virtual ~IClockPuller() {}
    virtual void StartTimestamp() = 0;
    virtual void NotifyTimestampSampleRate(TUint aSampleRate) = 0;
    virtual void NotifyTimestamp(TInt aDrift, TUint aNetwork) = 0;
    virtual void StopTimestamp() = 0;
    virtual void StartDecodedReservoir(TUint aCapacityJiffies, TUint aNotificationFrequency) = 0;
    virtual void NewStreamDecodedReservoir(TUint aStreamId) = 0;
    virtual void NotifySizeDecodedReservoir(TUint aJiffies) = 0;
    virtual void StopDecodedReservoir() = 0;
    virtual void StartStarvationMonitor(TUint aCapacityJiffies, TUint aNotificationFrequency) = 0;
    virtual void NewStreamStarvationMonitor(TUint aStreamId) = 0;
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

class ClockPullerUtils
{
public:
    static void PullClock(IPullableClock& aPullableClock, TInt aDriftJiffies, TUint64 aPeriodJiffies);
};

class ClockPullerNull : public IClockPuller
{
private: // from IClockPuller
    void StartTimestamp() override;
    void NotifyTimestampSampleRate(TUint aSampleRate) override;
    void NotifyTimestamp(TInt aDrift, TUint aNetwork) override;
    void StopTimestamp() override;
    void StartDecodedReservoir(TUint aCapacityJiffies, TUint aNotificationFrequency) override;
    void NewStreamDecodedReservoir(TUint aStreamId) override;
    void NotifySizeDecodedReservoir(TUint aJiffies) override;
    void StopDecodedReservoir() override;
    void StartStarvationMonitor(TUint aCapacityJiffies, TUint aNotificationFrequency) override;
    void NewStreamStarvationMonitor(TUint aStreamId) override;
    void NotifySizeStarvationMonitor(TUint aJiffies) override;
    void StopStarvationMonitor() override;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_CLOCK_PULLER
