#include <OpenHome/Private/Timer.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;


// Timer

Timer::Timer(Environment& aEnv, Functor aFunctor, const TChar* aId)
    : iMgr(aEnv.TimerManager())
    , iFunctor(aFunctor)
    , iId(aId)
    , iNext(NULL)
    , iTime(0)
    , iQueued(false)
{
}

void Timer::FireIn(TUint aTime)
{
    FireAt(Time::Now(iMgr.iEnv) + aTime);
}

void Timer::FireAt(TUint aTime)
{
    //LOG(kTimer, "Timer::FireAt(%u) for %s\n", aTime, iId);
    iMgr.FireAt(*this, aTime);
}

void Timer::Cancel()
{
    //LOG(kTimer, "Timer::Cancel() for %s\n", iId);
    iMgr.Cancel(*this);
}

const TChar* Timer::Id() const
{
    return iId;
}

Timer::~Timer()
{
    Cancel();
}


// TimerManager
TimerManager::TimerManager(Environment& aEnv, TUint aThreadPriority)
    : iEnv(aEnv)
    , iLock("TIM1")
    , iWake("TIMW", 0)
    , iCancelDone("TIMC", 0)
    , iHead(NULL)
    , iRunning(NULL)
    , iThread(NULL)
    , iStop(false)
    , iStopped("MTS2", 0)
    , iBusyStartTimeMs(0)
    , iLastRunTimeMs(0)
    , iCallbacksPerTick(0)
{
    iThread = new ThreadFunctor("TimerManager", MakeFunctor(*this, &TimerManager::Run), aThreadPriority);
    iThread->Start();
}

TimerManager::~TimerManager()
{
    Stop();
    delete iThread;
}

void TimerManager::Stop()
{
    iLock.Wait();

    if (!iStop) {
        iStop = true;
        iLock.Signal();
        iWake.Signal();
        iStopped.Wait();
    }
    else {
        iLock.Signal();
    }
}



void TimerManager::InsertLocked(Timer& aTimer)
{
    ASSERT(!aTimer.iQueued);

    //NOTE: We use signed difference to ensure ordering is correct when the clock wraps
    Timer** ptr = &iHead;
    while (*ptr != NULL && (TInt)((*ptr)->iTime - aTimer.iTime) <= 0) {
        ptr = &((*ptr)->iNext);
    }

    aTimer.iNext   = *ptr;
    *ptr           = &aTimer;
    aTimer.iQueued = true;
}

void TimerManager::RemoveLocked(Timer& aTimer)
{
    if (!aTimer.iQueued) {
        return;
    }

    Timer** ptr = &iHead;

    while (*ptr != NULL) {
        if (*ptr == &aTimer) {
            *ptr = aTimer.iNext;
            break;
        }
        ptr = &((*ptr)->iNext);
    }

    aTimer.iNext   = NULL;
    aTimer.iQueued = false;
}

void TimerManager::FireAt(Timer& aTimer, TUint aTime)
{
    iLock.Wait();
    RemoveLocked(aTimer);
    aTimer.iTime = aTime;
    InsertLocked(aTimer);
    iLock.Signal();

    /* Always wake the manager - it recomputes the head deadline for itself.
       An occasional spurious wake-up is far cheaper than tracking whether this
       change actually moved the head. */
    iWake.Signal();
}


void TimerManager::Cancel(Timer& aTimer)
{
    // NOTE: We guarantee that the given timer's callback is not currently in progress,
    //       so that it will be sage to destory whatever the callback references.

    iLock.Wait();
    RemoveLocked(aTimer);

    TBool isTimerRunning  = iRunning == &aTimer;
    TBool isManagerThread = Thread::Current() == iThread;
    TBool wait            = isTimerRunning && !isManagerThread;
    iLock.Signal();

    if (wait) {
        iCancelDone.Wait();
    }
}

void TimerManager::Run()
{
    for (;;) {

        /* Clear before reading the head so that any timer queued after this
           point leaves a pending signal behind and cannot be slept through. */
        (void)iWake.Clear();

        iLock.Wait();
        if (iStop) {
            iLock.Signal();
            break;
        }
        const TBool pending = (iHead != NULL);
        const TInt delay = (pending? Time::TimeToWaitFor(iEnv, iHead->iTime) : 0);
        iLock.Signal();

        if (!pending) {
            iWake.Wait(); // nothing scheduled - sleep until something is
        }
        else if (delay > 0) {
            (void)iWake.TryWait((TUint)delay);
        }

        // Watchdog bookkeeping...
        const TUint now = Os::TimeInMs(iEnv.OsCtx());
        if (iLastRunTimeMs > now) { // wrapped
            iLastRunTimeMs = 0;
            iCallbacksPerTick = 0;
        }
        else if (iLastRunTimeMs == now) {
        }
        else if (now - iLastRunTimeMs > kMaxTimerGranularityMs) {
            iBusyStartTimeMs = now;
            iCallbacksPerTick = 0;
        }
        if (iBusyStartTimeMs == 0 || iBusyStartTimeMs > now) { // Clock has wrapped.  Reset our busy counter for the sake of simplicity
            iBusyStartTimeMs = now;
        }
        else if (now - iBusyStartTimeMs > kMaxBusyTimeMs) {
            iCallbackList.Log();
            ASSERTS();
        }
        iLastRunTimeMs = now;

        // Fire timers...
        for (;;) {
            iLock.Wait();
            Timer* timer = iHead;
            if (timer == NULL || !Time::IsInPastOrNow(iEnv, timer->iTime)) {
                iLock.Signal();
                break;
            }
            RemoveLocked(*timer);
            iRunning = timer;
            iCancelDone.Clear();
            iLock.Signal();

            iCallbackList.Add(*timer);
            if (++iCallbacksPerTick > kMaxCallbacksPerTick) {
                iCallbackList.Log();
                ASSERTS();
            }
            LOG(kTimer, "TimerManager::DrainExpired() - running %s\n", timer->iId);

            // NOTE: Timers are fired without holding a lock
            timer->iFunctor();

            iLock.Wait();
            iRunning = NULL;
            iLock.Signal();
            iCancelDone.Signal(); // We always signal this regardless of if we have waiters. It's cleared above before each run
        }
    }

    iStopped.Signal();
}

// Run every timer whose deadline has passed.
//
// Entries are unlinked one at a time and the callback is run with iLock
// released, so a callback is free to take any lock, to (re)schedule timers, or
// to cancel any timer other than itself.


// TimerManager::Callback

TimerManager::Callback::Callback()
    : iPtr(NULL)
    , iId(NULL)
{
}

void TimerManager::Callback::Set(void* aPtr, const TChar* aId)
{
    iPtr = &aPtr;
    iId = aId;
}

void TimerManager::Callback::Log() const
{
    Log::Print("Timer: %s (%p)\n", iId, iPtr);
}


// TimerManager::CallbackList

TimerManager::CallbackList::CallbackList()
    : iHead(0)
    , iTail(0)
{
    (void)memset((void*)iList, 0, sizeof(iList));
}

void TimerManager::CallbackList::Add(Timer& aTimer)
{
    iList[iTail].Set(&aTimer, aTimer.Id());
    IncIndex(iTail);
    if (iTail == iHead) {
        IncIndex(iHead);
    }
}

void TimerManager::CallbackList::Log() const
{
    Log::Print("Suspicious (implausible) activity in TimerManager.  Recent timers are:\n");
    if (iHead == iTail) {
        ASSERT(iHead == 0); // i.e. no timers have ever run
        return;
    }
    TUint tail = iTail;
    do {
        DecIndex(tail);
        iList[tail].Log();
    } while (tail != iHead);
}

void TimerManager::CallbackList::IncIndex(TUint& aIndex)
{ // static
    if (++aIndex == kElements) {
        aIndex = 0;
    }
}

void TimerManager::CallbackList::DecIndex(TUint& aIndex)
{ // static
    if (aIndex == 0) {
        aIndex = kElements-1;
    }
    --aIndex;
}

// TimerFactory

TimerFactory::TimerFactory(Environment& aEnv)
    : iEnv(aEnv)
{
}

ITimer* TimerFactory::CreateTimer(Functor aCallback, const TChar* aId)
{
    return new Timer(iEnv, aCallback, aId);
}

