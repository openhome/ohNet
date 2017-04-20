#include <OpenHome/Av/TransportControl.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Av;


TransportRepeatRandom::TransportRepeatRandom()
    : iLock("TCRR")
    , iRepeat(false)
    , iRandom(false)
{
}

void TransportRepeatRandom::SetRepeat(TBool aRepeat)
{
    AutoMutex _(iLock);
    if (iRepeat == aRepeat) {
        return;
    }
    iRepeat = aRepeat;
    for (auto obs: iObservers) {
        obs->TransportRepeatChanged(iRepeat);
    }
}

void TransportRepeatRandom::SetRandom(TBool aRandom)
{
    AutoMutex _(iLock);
    if (iRandom == aRandom) {
        return;
    }
    iRandom = aRandom;
    for (auto obs: iObservers) {
        obs->TransportRandomChanged(iRandom);
    }
}

void TransportRepeatRandom::AddObserver(ITransportRepeatRandomObserver& aObserver)
{
    AutoMutex _(iLock);
    iObservers.push_back(&aObserver);
    aObserver.TransportRepeatChanged(iRepeat);
    aObserver.TransportRandomChanged(iRandom);
}

void TransportRepeatRandom::RemoveObserver(ITransportRepeatRandomObserver& aObserver)
{
    AutoMutex _(iLock);
    for (auto it=iObservers.begin(); it!=iObservers.end(); ++it) {
        if (*it == &aObserver) {
            iObservers.erase(it);
            return;
        }
    }
}
