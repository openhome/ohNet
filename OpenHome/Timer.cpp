#include <OpenHome/Private/Timer.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;

// Time

TUint Time::Now(Environment& aEnv)
{
    return Os::TimeInMs(aEnv.OsCtx());
};

TBool Time::IsBeforeOrAt(TUint aQuestionableTime, TUint aTime)
{
    TInt diff = aTime - aQuestionableTime;
    return (diff >= 0);
}

TBool Time::IsAfter(TUint aQuestionableTime, TUint aTime)
{
    TInt diff = aTime - aQuestionableTime;
    return (diff < 0);
}

TBool Time::IsInPastOrNow(Environment& aEnv, TUint aTime)
{
    return (IsBeforeOrAt(aTime, Now(aEnv)));
}

TBool Time::IsInFuture(Environment& aEnv, TUint aTime)
{
    return (IsAfter(aTime, Now(aEnv)));
}

TInt Time::TimeToWaitFor(Environment& aEnv, TUint aTime)
{
    return (aTime - Os::TimeInMs(aEnv.OsCtx()));
}

// Timer

Timer::Timer(Environment& aEnv, Functor aFunctor, const TChar* aId)
    : iMgr(aEnv.TimerManager())
    , iFunctor(aFunctor)
    , iId(aId)
{
}

void Timer::FireIn(TUint aTime)
{
    LOG(kTimer, ">Timer::FireIn(%d)\n", aTime);
    FireAt(Time::Now(iMgr.iEnv) + aTime);
    LOG(kTimer, "<Timer::FireIn(%d)\n", aTime);
}

void Timer::FireAt(TUint aTime)
{
    LOG(kTimer, ">Timer::FireAt(%d)\n", aTime);
    iMgr.FireAt(*this, aTime);
    LOG(kTimer, "<Timer::FireAt(%d)\n", aTime);
}

void Timer::Cancel()
{
    LOG(kTimer, ">Timer::Cancel()\n");
    TBool lock = !IsInManagerThread(iMgr);
    if (lock) {
        iMgr.CallbackLock();
    }
    iMgr.Remove(*this);
    if (lock) {
        iMgr.CallbackUnlock();
    }
    LOG(kTimer, "<Timer::Cancel()\n");
}

const TChar* Timer::Id() const
{
    return iId;
}

TBool Timer::IsInManagerThread(OpenHome::Environment& aEnv)
{ // static
    return IsInManagerThread(aEnv.TimerManager());
}

TBool Timer::IsInManagerThread(TimerManager& aMgr)
{ // static
    return (Thread::Current() == aMgr.MgrThread());
}

Timer::~Timer()
{
    Cancel();
}

// TimerManager

TimerManager::TimerManager(Environment& aEnv)
    : iEnv(aEnv)
    , iMutexNow("TIM1")
    , iRemoving(false)
    , iSemaphore("TIMM", 0)
    , iMutex("TIM2")
    , iMutexTimer("TIM3")
    , iNextTimer(0)
    , iStop(false)
    , iStopped("MTS2", 0)
    , iCallbackMutex("TMCB")
    , iThreadHandle(NULL)
    , iBusyStartTimeMs(0)
    , iLastRunTimeMs(0)
    , iCallbacksPerTick(0)
{
    LOG(kTimer, ">TimerManager::TimerManager()\n");
    iThread = new ThreadFunctor("TimerManager", MakeFunctor(*this, &TimerManager::Run), kPriorityHigh);
    iThread->Start();
    LOG(kTimer, "<TimerManager::TimerManager()\n");
}

TimerManager::~TimerManager()
{
    LOG(kTimer, ">TimerManager::~TimerManager()\n");
    Stop();
    delete iThread;
    LOG(kTimer, "<TimerManager::~TimerManager()\n");
}

void TimerManager::Stop()
{
    LOG(kTimer, ">TimerManager::Stop()\n");

    iMutex.Wait();
    
    if (!iStop) {
        iStop = true;
        iMutex.Signal();
        iSemaphore.Signal();
        LOG(kTimer, "-TimerManager::Stop() Wait for stopped\n");
        iStopped.Wait();
    }
    else {
        iMutex.Signal();
        LOG(kTimer, "-TimerManager::Stop() Already stopped\n");
    }
    
    LOG(kTimer, "<TimerManager::Stop()\n");
}

void TimerManager::CallbackLock()
{
    iCallbackMutex.Wait();
}

void TimerManager::CallbackUnlock()
{
    iCallbackMutex.Signal();
}

// Called when the head item in the base timer queue changes
// Prime the master timer accordingly, unless this change in the head item
// is due to us removing already expired items

void TimerManager::HeadChanged(QueueSortedEntry& aEntry)
{
    LOG(kTimer, ">TimerManager::HeadChanged()\n", iRemoving);

    if(IsTail(aEntry)) {
        LOG(kTimer, "<TimerManager::HeadChanged() queue is empty\n");
        return;
    }

    iMutexNow.Wait();

    if (!iRemoving) {
        iMutexNow.Signal();
        iMutex.Wait();
        iNextTimer = Entry(aEntry).iTime;
        iMutex.Signal();
        iSemaphore.Signal();
        LOG(kTimer, "<TimerManager::HeadChanged() retrigger timer\n");
        return;
    }

    if (&aEntry == &iNow) {
        iRemoving = false;
    }

    iMutexNow.Signal();

    LOG(kTimer, "<TimerManager::HeadChanged() while removing\n");
}

// Fire expired timers
//
// This is achieved by inserting a dummy entry that represents 'now' into the sorted timer queue,
// then removing head items until we reach this 'now' item. All queue entries removed during this process
// represent expired timers.
//
// Note that during this process any change to the head item in the queue does does not cause the master timer
// to be retriggered. (See HeadChanged) 

void TimerManager::Fire()
{
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
    iMutexNow.Wait();
    iRemoving = true;
    iNow.iTime = now + 1; // will go after all the entries before or at now
    iMutexNow.Signal();

    // Add an entry for now, then ...

    DoAdd(iNow);
    
    LOG(kTimer, "-TimerManager::Fire() - TimerExpired, removing entries before %d\n", iNow.iTime);

    // remove all the entries before now
    // See HeadChanged() for how iRemoving gets turned off
    // Note that it has to be done this way so that the first
    // item to become the head after the dummy now entry has
    // been removed gets to prime the timer driver

    CallbackLock();
    for (;;) {
        Timer& head = RemoveHead();
        if(&head == &iNow) {
            LOG(kTimer, "-TimerManager::Fire() done signalling\n");
            break;
        }
        iCallbackList.Add(head);
        if (++iCallbacksPerTick > kMaxCallbacksPerTick) {
            iCallbackList.Log();
            ASSERTS();
        }
        head.iFunctor(); // run the timer's callback
        LOG(kTimer, "-TimerManager::Fire() signaling consumer\n");
    }
    CallbackUnlock();
}

void TimerManager::FireAt(Timer& aTimer, TUint aTime)
{
    AutoMutex mutex(iMutexTimer);
    Remove(aTimer);
    aTimer.iTime = aTime;
    Add(aTimer);
}

Thread* TimerManager::MgrThread() const
{
    return iThreadHandle;
}

TInt TimerManager::Compare(QueueSortedEntry& aEntry1, QueueSortedEntry& aEntry2)
{
    return (Entry(aEntry1).iTime - Entry(aEntry2).iTime);
}

void TimerManager::Run()
{
    iThreadHandle = Thread::Current();
    iSemaphore.Wait();
    iMutex.Wait();
    while (!iStop) {
        TInt delay = Time::TimeToWaitFor(iEnv, iNextTimer);
        iMutex.Signal();
        if (delay <= 0) { // in the past or now
            Fire();
            iSemaphore.Wait();
        }
        else { // in the future
            try {
                iSemaphore.Wait(delay);
            }
            catch (Timeout&) {
            }
        }
        iMutex.Wait();
    }
    iMutex.Signal();
    iStopped.Signal();
}


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
    (void)memset(iList, 0, sizeof(iList));
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
