#include <OpenHome/Av/Songcast/ClockPullerSongcast.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Media/ClockPullerUtilisation.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Av/Debug.h>

#include <cstdlib>
#include <vector>
#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

// ClockPullerSongcast

ClockPullerSongcast::ClockPullerSongcast(Environment& aEnv, Media::IPullableClock& aPullableClock)
    : iPullableClock(aPullableClock)
    , iUseTimestamps(false)
    , iRunning(false)
    , iStoreNetworkTimestamp(false)
    , iNextHistoryIndex(0)
    , iNetworkTimestampStart(0)
    , iNetworkTimestampLast(0)
    , iNetworkTimeOverflowCount(0)
    , iSampleRate(0)
    , iTimestampTotalDrift(0)
    , iTimestampMaxAllowedDrift(UINT_MAX)
{
    iHistoryLeft = new UtilisationHistory(aEnv, *this);
    iHistoryRight = new UtilisationHistory(aEnv, *this);
    iTimestampHistory.reserve(kMaxHistoryElements);
}

ClockPullerSongcast::~ClockPullerSongcast()
{
    delete iHistoryLeft;
    delete iHistoryRight;
}

void ClockPullerSongcast::ResetTimestampHistory()
{
    iStoreNetworkTimestamp = true;
    iTimestampHistory.clear();
    iNextHistoryIndex = 0;
    iTimestampTotalDrift = 0;
    iNetworkTimestampStart = 0;
    iNetworkTimestampLast = 0;
    iNetworkTimeOverflowCount = 0;
}

void ClockPullerSongcast::SmoothTimestamps(TInt& aDrift, TInt aIndexToSkip)
{
    iTimestampTotalDrift += aDrift;

    if (iTimestampHistory.size() == 0) {
        return;
    }

    const TUint absDeviation = (TUint)std::abs(aDrift);
    TInt i;

    if (absDeviation >= iTimestampHistory.size()) {
        TInt sharePerElement = aDrift / (TInt)iTimestampHistory.size();
        for (i=0; i<(TInt)iTimestampHistory.size(); i++) {
            if (i != aIndexToSkip) {
                iTimestampHistory[i] += sharePerElement;
                aDrift -= sharePerElement;
            }
        }
    }
    // share the remaining [0..size()) amongst the elements with longest to live
    TInt rem = aDrift % iTimestampHistory.size();
    if (rem != 0) {
        rem--; // leave aDrift == +/-1
        TInt adjustment = (aDrift > 0? 1 : -1);
        for (i=aIndexToSkip-1; i>=0 && rem>0; i--) {
            iTimestampHistory[i] += adjustment;
        }
        for (i=iTimestampHistory.size()-1; i>aIndexToSkip; i--) {
            iTimestampHistory[i] += adjustment;
        }
        aDrift = adjustment;
    }
}

void ClockPullerSongcast::StartTimestamp()
{
    iUseTimestamps = true;
}

void ClockPullerSongcast::NotifyTimestampSampleRate(TUint aSampleRate)
{
    iTimestampMaxAllowedDrift = iTimestampHistory.capacity() *
                                    static_cast<TUint64>(
                                        Jiffies::ToSongcastTime(kMaxExpectedDeviation, aSampleRate));
    ResetTimestampHistory();
    iSampleRate = aSampleRate;
}

void ClockPullerSongcast::NotifyTimestamp(TInt aDrift, TUint aNetwork)
{
    if (iStoreNetworkTimestamp) {
        iNetworkTimestampStart = aNetwork;
        iStoreNetworkTimestamp = false;
    }
    else if (aNetwork < iNetworkTimestampLast) {
        if (iNetworkTimestampLast - aNetwork > UINT_MAX/2) {
            LOG2(kError, kSongcast, "WARNING: songcast sender clock appears unreliable (moved backwards)\n");
        }
        else {
            iNetworkTimeOverflowCount++;
        }
    }
    iNetworkTimestampLast = aNetwork;

    if (iTimestampHistory.size() < iTimestampHistory.capacity()) {
        SmoothTimestamps(aDrift, -1);
        iTimestampHistory.push_back(aDrift);
    }
    else {
        iTimestampTotalDrift -= iTimestampHistory[iNextHistoryIndex];
        SmoothTimestamps(aDrift, iNextHistoryIndex);
        iTimestampHistory[iNextHistoryIndex++] = aDrift;
        if (iNextHistoryIndex == iTimestampHistory.capacity()) {
            iNextHistoryIndex = 0;
        }

        if ((TUint)std::abs(iTimestampTotalDrift) > iTimestampMaxAllowedDrift) {
            const TUint64 networkTimeElapsed = (static_cast<TUint64>(iNetworkTimeOverflowCount) * UINT_MAX) +
                                                    static_cast<TInt>(aNetwork - iNetworkTimestampStart);
            const TUint period = Jiffies::FromSongcastTime(networkTimeElapsed, iSampleRate);
            TInt drift = Jiffies::FromSongcastTime(std::abs(iTimestampTotalDrift)/iTimestampHistory.size(), iSampleRate);
            if (iTimestampTotalDrift < 0) {
                drift *= -1;
            }
            ClockPullerUtils::PullClock(iPullableClock, drift, period);
            ResetTimestampHistory();
        }
    }
}

void ClockPullerSongcast::StopTimestamp()
{
    iUseTimestamps = false;
    ResetTimestampHistory();
}

void ClockPullerSongcast::StartDecodedReservoir(TUint /*aCapacityJiffies*/, TUint aNotificationFrequency)
{
    iDecodedReservoirUpdateFrequency = aNotificationFrequency;
    iHistoryLeft->Reset();
}

void ClockPullerSongcast::NewStreamDecodedReservoir(TUint /*aStreamId*/)
{
}

void ClockPullerSongcast::NotifySizeDecodedReservoir(TUint aJiffies)
{
    if (iRunning && !iUseTimestamps) {
        iHistoryLeft->Add(aJiffies);
    }
}

void ClockPullerSongcast::StopDecodedReservoir()
{
}

void ClockPullerSongcast::StartStarvationMonitor(TUint /*aCapacityJiffies*/, TUint aNotificationFrequency)
{
    iRunning = true;
    iStarvationMonitorUpdateFrequency = aNotificationFrequency;
    iHistoryRight->Reset();
}

void ClockPullerSongcast::NewStreamStarvationMonitor(TUint /*aStreamId*/)
{
}

void ClockPullerSongcast::NotifySizeStarvationMonitor(TUint aJiffies)
{
    if (iRunning && !iUseTimestamps) {
        iHistoryRight->Add(aJiffies);
    }
}

void ClockPullerSongcast::StopStarvationMonitor()
{
    iRunning = false;
}

void ClockPullerSongcast::NotifyClockDrift(UtilisationHistory* aHistory, TInt aDriftJiffies, TUint aNumSamples)
{
    if (iRunning && !iUseTimestamps) {
        const TUint64 updateFreq = (aHistory == iHistoryLeft? iDecodedReservoirUpdateFrequency : iStarvationMonitorUpdateFrequency);
        const TUint64 periodJiffies = aNumSamples * updateFreq;
        ClockPullerUtils::PullClock(iPullableClock, aDriftJiffies, periodJiffies);
    }
}
