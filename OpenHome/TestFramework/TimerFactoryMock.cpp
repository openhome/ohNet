#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/TimerFactoryMock.h>

#include <map>
#include <list>
#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

// TimerMock

TimerMock::TimerMock(ITimerFactoryMock& aFactory, OpenHome::Functor aCb, const TChar* aId)
    : iFactory(aFactory)
    , iCb(aCb)
    , iId(aId)
    , iBusy("TMKS", 1)
    , iRefCount(0)
{
}

TimerMock::~TimerMock()
{
    iBusy.Wait();
    iFactory.Remove(*this);
}

void TimerMock::FireIn(TUint aMs)
{
    iFactory.Queue(*this, aMs);
}

void TimerMock::Cancel()
{
    iFactory.Cancel(*this);
}

void TimerMock::AddRef()
{
    if (++iRefCount == 1) {
        iBusy.Wait();
    }
}

void TimerMock::RemoveRef()
{
    if (--iRefCount == 0) {
        iBusy.Signal();
    }
}


// TimerFactoryMock

const TUint TimerFactoryMock::kDueTimeNever = UINT_MAX;

TimerFactoryMock::TimerFactoryMock()
    : iLock("TMMK")
    , iNowMs(0)
{
}

TimerFactoryMock::~TimerFactoryMock()
{
    ASSERT(iTimers.size() == 0);
}

void TimerFactoryMock::Advance(TUint aMs)
{
    const TUint targetNowMs = iNowMs + aMs;

    for (;;)
    {
        // If next timer would expire on or before targetNowMs, erase it from iTimers,
        // and move iNowMs forward to this point.

        TimerMock* timer;
        {
            AutoMutex amtx(iLock);

            if (iTimers.size() == 0)
                break;

            const auto nextTimerIt = iTimers.begin();
            TUint timerAbsTime = nextTimerIt->first;
            timer = nextTimerIt->second;

            if (timerAbsTime <= targetNowMs)
            {
                iTimers.erase(nextTimerIt);
                timer->AddRef();

                iNowMs = timerAbsTime;
            }
            else {
                // no further timers expiring in our advance window. terminate loop.
                iNowMs = targetNowMs;
                break;
            }
        }

        timer->iCb();
        timer->RemoveRef();
    }
}

ITimer* TimerFactoryMock::CreateTimer(Functor aCallback, const TChar* aId)
{
    auto timer = new TimerMock(*this, aCallback, aId);
    iTimers.insert(std::pair<TUint, TimerMock*>(kDueTimeNever, timer));
    return timer;
}

void TimerFactoryMock::Queue(TimerMock& aTimer, TUint aDue)
{
    AutoMutex _(iLock);
    RemoveLocked(aTimer);
    iTimers.insert(std::pair<TUint, TimerMock*>(iNowMs+aDue, &aTimer));
}

void TimerFactoryMock::Cancel(TimerMock& aTimer)
{
    Queue(aTimer, kDueTimeNever-iNowMs); // subtraction of iNowMs ensures we get the correct absolute time (kDueTimeNever).
}

void TimerFactoryMock::Remove(TimerMock& aTimer)
{
    AutoMutex _(iLock);
    RemoveLocked(aTimer);
}

void TimerFactoryMock::RemoveLocked(TimerMock& aTimer)
{
    for (auto it=iTimers.begin(); it!=iTimers.end(); ++it) {
        if (it->second == &aTimer) {
            iTimers.erase(it);
            return;
        }
    }
}
