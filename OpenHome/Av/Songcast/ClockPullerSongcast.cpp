#include <OpenHome/Av/Songcast/ClockPullerSongcast.h>
#include <OpenHome/Types.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Private/Env.h>

#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::Media;

// StreamId

StreamId::StreamId()
    : iTrackId(IPipelineIdProvider::kTrackIdInvalid)
    , iStreamId(IPipelineIdProvider::kStreamIdInvalid)
{
}

void StreamId::SetTrack(TUint aId)
{
    iTrackId = aId;
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
}

void StreamId::SetStream(TUint aId)
{
    ASSERT(iTrackId != IPipelineIdProvider::kTrackIdInvalid);
    iStreamId = aId;
}

TBool StreamId::operator ==(const StreamId& aId) const
{
    return (iTrackId == aId.iTrackId && iStreamId == aId.iStreamId);
}


// UtilisationHistory

UtilisationHistory::UtilisationHistory(TUint aMaxElements)
    : iNextIndex(0)
{
    iHistory.reserve(aMaxElements);
    Clear();
}

void UtilisationHistory::Clear()
{
    iHistory.clear();
    iNextIndex = 0;
    iStartValue = 0;
    iLastValue = 0;
    iMinValue = 0;
    iMaxValue = 0;
    iStartTime = 0;
    iSamplePointsSinceLastChange = 0; // defeat pulling via constant tiny changes?
    iAverage = 0;
    iTotal = 0;
}

void UtilisationHistory::Add(TUint aJiffies)
{
    if (iLastValue == aJiffies) {
        iSamplePointsSinceLastChange++;
    }
    else {
        iSamplePointsSinceLastChange = 0;
    }

    if (iHistory.size() < iHistory.capacity()) {
        if (iHistory.size() == 0) {
            iStartValue = aJiffies;
            iMinValue = aJiffies;
            iStartTime = Os::TimeInMs(gEnv->OsCtx()); // FIXME - lazy to rely on global env pointer
        }
        iHistory.push_back(aJiffies);
    }
    else {
        iTotal -= iHistory[iNextIndex];
        iHistory[iNextIndex++] = aJiffies;
        if (iNextIndex == iHistory.capacity()) {
            iNextIndex = 0;
        }
    }

    iLastValue = aJiffies;
    iMinValue = std::min(iMinValue, aJiffies);
    iMaxValue = std::min(iMaxValue, aJiffies);
    iTotal += aJiffies;
    iAverage = iTotal / iHistory.size();

#define J2MS(j) (j / Jiffies::kPerMs)
    Log::Print("Start=%u (%08x), last=%u (%08x), min=%u (%08x), max=%u (%08x), avg=%u (%08x)\n",
               J2MS(iStartValue), iStartValue, J2MS(iLastValue), iLastValue,
               J2MS(iMinValue), iMinValue, J2MS(iMaxValue), iMaxValue,
               J2MS(iAverage), iAverage);
}


// ClockPullerSongcast

ClockPullerSongcast::ClockPullerSongcast()
    : iLock("CPLS")
    , iActiveCount(0)
    , iUtilisationLeft(100)
    , iUtilisationRight(100)
{
}

void ClockPullerSongcast::StartDecodedReservoir(TUint /*aCapacityJiffies*/)
{
    AutoMutex a(iLock);
    iActiveCount++;
}

void ClockPullerSongcast::NewStreamDecodedReservoir(TUint aTrackId, TUint aStreamId)
{
    AutoMutex a(iLock);
    iStreamLeft.SetTrack(aTrackId);
    iStreamLeft.SetStream(aStreamId);
}

void ClockPullerSongcast::NotifySizeDecodedReservoir(TUint /*aJiffies*/)
{
}

void ClockPullerSongcast::StopDecodedReservoir()
{
    AutoMutex a(iLock);
    iActiveCount--;
}

void ClockPullerSongcast::StartStarvationMonitor(TUint /*aCapacityJiffies*/)
{
    AutoMutex a(iLock);
    iActiveCount++;
}

void ClockPullerSongcast::NewStreamStarvationMonitor(TUint aTrackId, TUint aStreamId)
{
    iStreamRight.SetTrack(aTrackId);
    iStreamRight.SetStream(aStreamId);
}

void ClockPullerSongcast::NotifySizeStarvationMonitor(TUint /*aJiffies*/)
{
}

void ClockPullerSongcast::StopStarvationMonitor()
{
    AutoMutex a(iLock);
    iActiveCount--;
}
