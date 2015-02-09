#ifndef HEADER_CLOCK_PULLER_UTILISATION
#define HEADER_CLOCK_PULLER_UTILISATION

#include <OpenHome/Types.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Standard.h>

namespace OpenHome {
    class Environment;
namespace Media {

class UtilisationHistory;

class IUtilisationHistoryObserver
{
public:
    virtual void NotifyClockDrift(UtilisationHistory* aHistory, TInt aDriftJiffies, TUint aNumSamples) = 0;
};

class UtilisationHistory : private INonCopyable
{
    static const TUint kMaxExpectedDeviation = Jiffies::kPerMs * 50; // expect an update every 100ms, so 50ms deviation is 50% from norm
    static const TUint kMaxHistoryElements = 50;
    static const TUint kElementsForInitialAverage = 20;
    static const TUint kMaxAllowedTotalsDeviation = Jiffies::kPerMs * 10;
public:
    UtilisationHistory(Environment& aEnv, IUtilisationHistoryObserver& aObserver);
    void Add(TUint aJiffies);
    void Reset();
private:
    void Smooth(TUint& aJiffies, TInt aIndexToSkip);
private:
    OsContext* iOsCtx;
    IUtilisationHistoryObserver& iObserver;
    std::vector<TInt> iHistory;
    TUint iNextHistoryIndex;
    TUint iSamples; // how often Add() has been called since we last reported drift
    TInt64 iTotal;
    TInt64 iExpectedTotal;
    TUint iExpectedAverage;
    TUint iDeviationCount;
};

// Intended for sources which have a reasonable latency
// ...so can perform all calculations based on state of DecodedAudioReservoir only
class ClockPullerUtilisationPerStreamLeft : public IClockPuller, protected IUtilisationHistoryObserver
{
public:
    ClockPullerUtilisationPerStreamLeft(Environment& aEnv, IPullableClock& aPullableClock);
    ~ClockPullerUtilisationPerStreamLeft();
protected: // from IClockPuller
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
protected: // from IUtilisationHistoryObserver
    void NotifyClockDrift(UtilisationHistory* aHistory, TInt aDriftJiffies, TUint aNumSamples) override;
protected:
    void TryAdd(UtilisationHistory& aHistory, TUint aJiffies);
    void NotifyClockDrift(TInt aDriftJiffies, TUint aNumSamples, TUint aUpdateFrequency);
private:
    IPullableClock& iPullableClock;
    Mutex iLock;
    TUint iStreamIdLeft;
    TUint iStreamIdRight;
    UtilisationHistory* iUtilisationLeft;
    TUint iDecodedReservoirUpdateFrequency;
};

class ClockPullerUtilisationPerStreamFull : public ClockPullerUtilisationPerStreamLeft
{
public:
    ClockPullerUtilisationPerStreamFull(Environment& aEnv, IPullableClock& aPullableClock);
    ~ClockPullerUtilisationPerStreamFull();
private: // from IClockPuller
    void StartStarvationMonitor(TUint aCapacityJiffies, TUint aNotificationFrequency) override;
    void NotifySizeStarvationMonitor(TUint aJiffies) override;
private: // from IUtilisationHistoryObserver
    void NotifyClockDrift(UtilisationHistory* aHistory, TInt aDriftJiffies, TUint aNumSamples) override;
private:
    UtilisationHistory* iUtilisationRight;
    TUint iStarvationMonitorUpdateFrequency;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_CLOCK_PULLER_UTILISATION
