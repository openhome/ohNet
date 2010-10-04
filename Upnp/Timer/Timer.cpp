#include <Timer.h>
#include <Os.h>
#include <Stack.h>
#include <Debug.h>

using namespace Zapp;

// Time

TUint Time::Now()
{
    return Os::TimeInMs();
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

TBool Time::IsInPastOrNow(TUint aTime)
{
    return (IsBeforeOrAt(aTime, Now()));
}

TBool Time::IsInFuture(TUint aTime)
{
    return (IsAfter(aTime, Now()));
}

TInt Time::TimeToWaitFor(TUint aTime)
{
    return (aTime - Os::TimeInMs());
}

// Timer

Timer::Timer(Functor aFunctor)
: iFunctor(aFunctor)
{
}

void Timer::FireIn(TUint aTime)
{
    LOG(kTimer, ">Timer::FireIn(%d)\n", aTime);
    FireAt(Time::Now() + aTime);
    LOG(kTimer, "<Timer::FireIn(%d)\n", aTime);
}

void Timer::FireAt(TUint aTime)
{
    LOG(kTimer, ">Timer::FireAt(%d)\n", aTime);
    TimerManager& manager = Zapp::Stack::TimerManager();
    manager.Remove(*this);
    iTime = aTime;
    manager.Add(*this);
    LOG(kTimer, "<Timer::FireAt(%d)\n", aTime);
}

void Timer::Cancel()
{
    LOG(kTimer, ">Timer::Cancel()\n");
    Zapp::Stack::TimerManager().Remove(*this);
    LOG(kTimer, "<Timer::Cancel()\n");
}

Timer::~Timer()
{
    TimerManager& mgr = Stack::TimerManager();
    TBool lock = (Thread::Current() != mgr.Thread());
    if (lock) {
        mgr.iCallbackMutex.Wait();
    }
    Cancel();
    if (lock) {
        mgr.iCallbackMutex.Signal();
    }
}

// TimerManager

TimerManager::TimerManager()
    : iMutexNow("NOWM")
    , iRemoving(false)
    , iSemaphore("TIMM", 0)
    , iMutex("TIMM")
    , iNextTimer(0)
    , iStop(false)
    , iStopped("MTS2", 0)
    , iCallbackMutex("TMCB")
    , iThreadHandle(NULL)
{
    LOG(kTimer, ">TimerManager::TimerManager()\n");
    iThread = new ThreadFunctor("TIMM", MakeFunctor(*this, &TimerManager::Run), kPriorityHigh);
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
    TUint now = Os::TimeInMs();
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

    iCallbackMutex.Wait();
    for (;;) {
        Timer& head = RemoveHead();
        if(&head == &iNow) {
            LOG(kTimer, "-TimerManager::Fire() done signalling\n");
            break;
        }
        head.iFunctor(); // run the timer's callback
        LOG(kTimer, "-TimerManager::Fire() signaling consumer\n");
    }
    iCallbackMutex.Signal();
}

Zapp::Thread* TimerManager::Thread() const
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
        TInt delay = Time::TimeToWaitFor(iNextTimer);
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


// Moderator

Moderator::Moderator(Functor aFunctor, TUint aModerationMs)
    : iTimerStarted(false)
    , iMutex("MODR")
    , iModeratedFunctor(aFunctor)
    , iModerationMs(aModerationMs)
{
    iTimer = new Timer(MakeFunctor(*this, &Moderator::Redirect));
}

Moderator::~Moderator()
{
    delete iTimer;
}

void Moderator::Moderate()
{
    //This mutex protects us from multiple threads calling Moderate
    //not from the consumer calling ::Redirect
    iMutex.Wait();

    if(!iTimerStarted) {
        iTimer->FireIn(iModerationMs);
        iTimerStarted = true;
    }

    iMutex.Signal();
}

void Moderator::Redirect()
{
    //No mutex lock required here as setting false is atomic
    iTimerStarted = false;
    iModeratedFunctor();
}
