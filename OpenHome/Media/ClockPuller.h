#pragma once

#include <OpenHome/Types.h>

namespace OpenHome {
namespace Media {

class IClockPuller
{
public:
    virtual ~IClockPuller() {}
    virtual void NewStream(TUint aSampleRate) = 0;
    virtual void Reset() = 0;
    virtual void Stop() = 0;
};

class IClockPullerReservoir : public IClockPuller
{
public:
    virtual ~IClockPullerReservoir() {}
    virtual void Start(TUint aNotificationFrequency) = 0;
    virtual void NotifySize(TUint aJiffies) = 0;
};

class IClockPullerTimestamp : public IClockPuller
{
public:
    virtual ~IClockPullerTimestamp() {}
    virtual void Start() = 0;
    virtual void NotifyTimestamp(TInt aDrift, TUint aNetwork) = 0;
};

class IPullableClock
{
public:
    static const TUint kNominalFreq = 1u<<31;
public:
    virtual ~IPullableClock() {}
    /**
     * Signal that the clock should be pulled.
     *
     * @param[in] aSampleRate  Nominal frequency for the stream.
     * @param[in] aMultiplier  Amount to pull by as fix 1.31 value (so, in the range [0..2)).
     *                         kNominalFreq implies no pull - i.e. run at nominal frequency.
     */
    virtual void PullClock(TUint aMultiplier) = 0;
};

class ClockPullerUtils
{
    static const TInt kMaxPull = IPullableClock::kNominalFreq / 20; // only allow pulls in the range (-5%..5%)
public:
    static void PullClock(TUint& aMultiplier, TInt aDriftJiffies, TUint64 aPeriodJiffies);
};

} // namespace Media
} // namespace OpenHome

