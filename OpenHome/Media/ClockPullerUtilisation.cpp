#include <OpenHome/Media/ClockPullerUtilisation.h>
#include <OpenHome/Types.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Media/Debug.h>

#include <cstdlib>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::Media;

// UtilisationHistory

UtilisationHistory::UtilisationHistory(Environment& aEnv, IUtilisationHistoryObserver& aObserver)
    : iOsCtx(aEnv.OsCtx())
    , iObserver(aObserver)
{
    iHistory.reserve(kMaxHistoryElements);
    Reset();
}

void UtilisationHistory::Add(TUint aJiffies)
{
    // rely on caller discarding an appropriate number of initial snapshots to allow things to stabilise (only required if Gorger is enabled?)
    // use next N (10?) values to determine an average.  Discard values and try again if there is significant fluctuation in them.
    // after N values, update history to all use this average
    // Maintain running total of all values in array
    // When array is full, replace the oldest value with newest
    // Any deviation from average in subsequent values is distributed across the history array.  This attempts to smooth out peaks/troughs caused by variable network performance and decode times.
    // If total from all array elements deviates slightly from expected and deviation continues for a number of iterations, calculate how much to pull the clock by.
    // If total deviates substantially, assume we're either experiencing network starvation or a rush of audio following (brief) starvation.  Don't pull the clock in this case.  Instead, wait until audio stabilises to close to previous averages.
    iSamples++;
    if (iHistory.size() < kElementsForInitialAverage) {
        iHistory.push_back(aJiffies);
        if (iHistory.size() == kElementsForInitialAverage) {
            TBool valuesSteady = true;
            const TInt initial = iHistory[0];
            for (TUint i=1; i<iHistory.size(); i++) {
                if ((TUint)std::abs(initial - iHistory[i]) > kMaxExpectedDeviation) {
                    valuesSteady = false;
                    break;
                }
            }
            if (!valuesSteady) {
                /* Too much fluctuation to calculate reliable average.
                   Give up on this data set and try again. */
                //Log::Print("UtilisationHistory::Add() values are unsteady - Reset\n");
                Reset();
            }
            else {
                ASSERT(iTotal == 0);
                /* following is equivalent to std::accumulate except that the return
                   value (iTotal) has wider type than iHistory's elements */
                for (auto it = iHistory.begin(); it != iHistory.end(); ++it) {
                    iTotal += *it;
                }
                iExpectedTotal = (iTotal * iHistory.capacity()) / kElementsForInitialAverage;
                iExpectedAverage = static_cast<TUint>((iTotal + (iHistory.size()/2)) / iHistory.size());
                //Log::Print("%u elements, iTotal: %lld, iExpectedTotal: %lld, iExpectedAverage: %u\n",
                //                kElementsForInitialAverage, iTotal/Jiffies::kPerMs, iExpectedTotal/Jiffies::kPerMs, iExpectedAverage/Jiffies::kPerMs);
                /* Belatedly smooth existing items.
                   Don't worry about losing up to iHistory.size()/2 jiffies of data. */
                std::fill(iHistory.begin(), iHistory.end(), iExpectedAverage);
            }
        }
    }
    else if (iHistory.size() < iHistory.capacity()) {
        Smooth(aJiffies, -1);
        iHistory.push_back(aJiffies);
    }
    else {
        iTotal -= iHistory[iNextHistoryIndex];
        Smooth(aJiffies, iNextHistoryIndex);
        iHistory[iNextHistoryIndex++] = aJiffies;
        if (iNextHistoryIndex == iHistory.capacity()) {
            iNextHistoryIndex = 0;
        }

        TInt diff = (TInt)(iTotal - iExpectedTotal);
        if (/*iDeviationCount == 0 && */(TUint)std::abs(diff) > kMaxAllowedTotalsDeviation) {
            iObserver.NotifyClockDrift(this, diff, iSamples);
            Reset();
        }
    }
}

void UtilisationHistory::Reset()
{
    iHistory.clear();
    iNextHistoryIndex = 0;
    iSamples = 0;
    iTotal = 0;
    iExpectedTotal = 0;
    iExpectedAverage = 0;
    iDeviationCount = 0;
}

void UtilisationHistory::Smooth(TUint& aJiffies, TInt aIndexToSkip)
{
    iTotal += aJiffies;
    TInt deviation = aJiffies - iExpectedAverage;
    const TUint absDeviation = (TUint)std::abs(deviation);
    if (absDeviation > kMaxExpectedDeviation) {
        iDeviationCount++;
    }
    else if (iDeviationCount > 0) {
        iDeviationCount--;
    }
    if (absDeviation >= iHistory.size()) {
        TInt sharePerElement = deviation / (TInt)iHistory.size();
//        const TUint absSharePerElement = (TUint)std::abs(sharePerElement);
        for (TInt i=0; i<(TInt)iHistory.size(); i++) {
            if (i != aIndexToSkip) {
                iHistory[i] += sharePerElement;
                aJiffies -= sharePerElement;
            }
        }
    }
}


// ClockPullerUtilisation

ClockPullerUtilisation::ClockPullerUtilisation(Environment& aEnv, IPullableClock& aPullableClock)
    : iPullableClock(aPullableClock)
    , iMultiplier(IPullableClock::kNominalFreq)
{
    iUtilisation = new UtilisationHistory(aEnv, *this);
}

ClockPullerUtilisation::~ClockPullerUtilisation()
{
    delete iUtilisation;
}

void ClockPullerUtilisation::Reset()
{
    iUtilisation->Reset();
    iMultiplier = IPullableClock::kNominalFreq;
}

void ClockPullerUtilisation::Stop()
{
    iUtilisation->Reset();
}

void ClockPullerUtilisation::Start(TUint /*aExpectedDecodedReservoirJiffies*/)
{
//    iUpdateFrequency = aNotificationFrequency;
    Reset();
}

void ClockPullerUtilisation::NotifySize(TUint /*aJiffies*/)
{
//    iUtilisation->Add(aJiffies);
}

void ClockPullerUtilisation::NotifyClockDrift(UtilisationHistory* /*aHistory*/, TInt aDriftJiffies, TUint aNumSamples)
{
    const TUint64 periodJiffies = aNumSamples * static_cast<TUint64>(iUpdateFrequency);
    ClockPullerUtils::PullClock(iMultiplier, aDriftJiffies, periodJiffies);
    iPullableClock.PullClock(iMultiplier);
}
