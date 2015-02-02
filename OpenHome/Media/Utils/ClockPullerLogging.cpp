#include <OpenHome/Media/Utils/ClockPullerLogging.h>
#include <OpenHome/Types.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Env.h>

#include <numeric>
#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::Media;

// Utilisation

Utilisation::Utilisation(TUint aEntries, IUtilisationObserver& aObserver)
    : iObserver(aObserver)
{
    iHistory.reserve(aEntries);
}

void Utilisation::Add(TUint aJiffies)
{
    iHistory.push_back(aJiffies);
    if (iHistory.size() == iHistory.capacity()) {
        const TUint avg = (std::accumulate(iHistory.begin(), iHistory.end(), 0) + (iHistory.size()/2)) / iHistory.size();
        iObserver.AddAverage(avg);
        iHistory.clear();
    }
}

void Utilisation::Clear()
{
    iHistory.clear();
}


// UtilisationHistoryLogging

UtilisationHistoryLogging::UtilisationHistoryLogging(Environment& aEnv)
    : iEnv(aEnv)
    , iNextHistoryIndex(0)
{
    iLevel1 = new Utilisation(10, *this);
    iHistory.reserve(10);
    Clear();
}

UtilisationHistoryLogging::~UtilisationHistoryLogging()
{
    delete iLevel1;
}

void UtilisationHistoryLogging::Add(TUint aJiffies)
{
    iLevel1->Add(aJiffies);
}

void UtilisationHistoryLogging::Clear()
{
    iLevel1->Clear();
    iHistory.clear();
    iNextHistoryIndex = 0;
    iStartValue = 0;
    iLastValue = 0;
    iMinValue = 0;
    iMaxValue = 0;
    iStartTime = 0;
}

void UtilisationHistoryLogging::AddAverage(TUint aJiffies)
{
    if (iHistory.size() < iHistory.capacity()) {
        if (iHistory.size() == 0) {
            iStartValue = aJiffies;
            iMinValue = aJiffies;
            iStartTime = Os::TimeInMs(iEnv.OsCtx());
        }
        iHistory.push_back(aJiffies);
    }
    else {
        iHistory[iNextHistoryIndex++] = aJiffies;
        if (iNextHistoryIndex == iHistory.capacity()) {
            iNextHistoryIndex = 0;
        }
    }

    iLastValue = aJiffies;
    iMinValue = std::min(iMinValue, aJiffies);
    iMaxValue = std::max(iMaxValue, aJiffies);

#define J2MS(j) (j / Jiffies::kPerMs)
    Log::Print("Start=%u, last=%u, min=%u, max=%u\n",
               J2MS(iStartValue), J2MS(iLastValue), J2MS(iMinValue), J2MS(iMaxValue));
/*    Log::Print("Start=%u (%08x), last=%u (%08x), min=%u (%08x), max=%u (%08x)\n",
               J2MS(iStartValue), iStartValue, J2MS(iLastValue), iLastValue,
               J2MS(iMinValue), iMinValue, J2MS(iMaxValue), iMaxValue);*/
}


// ClockPullerLogging

ClockPullerLogging::ClockPullerLogging(Environment& aEnv)
    : iLock("CPLL")
    , iUtilisationLeft(aEnv)
    , iUtilisationRight(aEnv)
    , iActiveCount(0)
{
}

void ClockPullerLogging::StartTimestamp()
{
}

void ClockPullerLogging::NotifyTimestampSampleRate(TUint /*aSampleRate*/)
{
}

void ClockPullerLogging::NotifyTimestamp(TInt /*aDelta*/, TUint /*aNetwork*/)
{
}

void ClockPullerLogging::StopTimestamp()
{
}

void ClockPullerLogging::StartDecodedReservoir(TUint /*aCapacityJiffies*/, TUint /*aNotificationFrequency*/)
{
    AutoMutex a(iLock);
    iActiveCount++;
}

void ClockPullerLogging::NewStreamDecodedReservoir(TUint aStreamId)
{
    AutoMutex a(iLock);
    iStreamIdLeft = aStreamId;
    iUtilisationLeft.Clear();
    iUtilisationRight.Clear();
}

void ClockPullerLogging::NotifySizeDecodedReservoir(TUint aJiffies)
{
    if (iStreamIdLeft == iStreamIdRight) {
        iUtilisationLeft.Add(aJiffies);
    }
}

void ClockPullerLogging::StopDecodedReservoir()
{
    AutoMutex a(iLock);
    iActiveCount--;
}

void ClockPullerLogging::StartStarvationMonitor(TUint /*aCapacityJiffies*/, TUint /*aNotificationFrequency*/)
{
    AutoMutex a(iLock);
    iActiveCount++;
}

void ClockPullerLogging::NewStreamStarvationMonitor(TUint aStreamId)
{
    iStreamIdRight = aStreamId;
}

void ClockPullerLogging::NotifySizeStarvationMonitor(TUint /*aJiffies*/)
{
}

void ClockPullerLogging::StopStarvationMonitor()
{
    AutoMutex a(iLock);
    iActiveCount--;
}
