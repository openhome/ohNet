#pragma once

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

class ClockPullerUtilisation : public IClockPullerReservoir, private IUtilisationHistoryObserver, private INonCopyable
{
public:
    ClockPullerUtilisation(Environment& aEnv);
    ~ClockPullerUtilisation();
private: // from IClockPullerReservoir
    void NewStream(TUint aSampleRate) override;
    void Reset() override;
    void Stop() override;
    void Start(TUint aNotificationFrequency) override;
    TUint NotifySize(TUint aJiffies) override;
private: // from IUtilisationHistoryObserver
    void NotifyClockDrift(UtilisationHistory* aHistory, TInt aDriftJiffies, TUint aNumSamples) override;
private:
    UtilisationHistory* iUtilisation;
    TUint iUpdateFrequency;
    TUint iMultiplier;
};

} // namespace Media
} // namespace OpenHome

