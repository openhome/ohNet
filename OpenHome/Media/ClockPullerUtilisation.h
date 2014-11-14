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

class IUtilisationHistoryObserver
{
public:
    virtual void NotifyClockDrift(TInt aDriftJiffies, TUint aNumSamples) = 0;
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
class ClockPullerUtilisation : public IClockPuller, private IUtilisationHistoryObserver
{
public:
    ClockPullerUtilisation(Environment& aEnv, IPullableClock& aPullableClock);
    ~ClockPullerUtilisation();
private: // from IClockPuller
    void StartDecodedReservoir(TUint aCapacityJiffies, TUint aNotificationFrequency) override;
    void NewStreamDecodedReservoir(TUint aTrackId, TUint aStreamId) override;
    void NotifySizeDecodedReservoir(TUint aJiffies) override;
    void StopDecodedReservoir() override;
    void StartStarvationMonitor(TUint aCapacityJiffies) override;
    void NewStreamStarvationMonitor(TUint aTrackId, TUint aStreamId) override;
    void NotifySizeStarvationMonitor(TUint aJiffies) override;
    void StopStarvationMonitor() override;
private: // from IUtilisationHistoryObserver
    void NotifyClockDrift(TInt aDriftJiffies, TUint aNumSamples) override;
private:
    IPullableClock& iPullableClock;
    Mutex iLock;
    StreamId iStreamLeft;
    StreamId iStreamRight;
    UtilisationHistory* iUtilisationLeft;
    TUint iDecodedReservoirUpdateFrequency;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_CLOCK_PULLER_UTILISATION
