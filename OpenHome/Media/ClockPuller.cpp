#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Media;

// UtilisationHistory

UtilisationHistory::UtilisationHistory(TUint aMaxSamples, Functor aChanged)
    : iChanged(aChanged)
    , iNextIndex(0)
{
    iHistory.reserve(aMaxSamples);
}

const std::vector<TUint64>& UtilisationHistory::History() const
{
    return iHistory;
}

TUint UtilisationHistory::StartIndex() const
{
    return iNextIndex;
}

void UtilisationHistory::NotifySize(TUint aJiffies)
{
    if (iHistory.size() < iHistory.capacity()) {
        iHistory.push_back(aJiffies);
    }
    else {
        iHistory[iNextIndex++] = aJiffies;
        if (iNextIndex == iHistory.capacity()) {
            iNextIndex = 0;
        }
    }
    iChanged();
}

void UtilisationHistory::Stop()
{
    iHistory.clear();
    iNextIndex = 0;
}


// ClockPuller

ClockPuller::ClockPuller()
{
    iDecodedReservoirHistory = new UtilisationHistory(kMaxSamplePoints, MakeFunctor(*this, &ClockPuller::DecodedReservoirChanged));
    iStarvationMonitorHistory = new UtilisationHistory(kMaxSamplePoints, MakeFunctor(*this, &ClockPuller::StarvationMonitorChanged));
}

ClockPuller::~ClockPuller()
{
    delete iDecodedReservoirHistory;
    delete iStarvationMonitorHistory;
}

IClockPuller& ClockPuller::DecodedReservoirHistory()
{
    return *iDecodedReservoirHistory;
}

IClockPuller& ClockPuller::StarvationMonitorHistory()
{
    return *iStarvationMonitorHistory;
}

void ClockPuller::DecodedReservoirChanged()
{
}

void ClockPuller::StarvationMonitorChanged()
{
}
