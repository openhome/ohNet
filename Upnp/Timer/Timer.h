#ifndef HEADER_TIMER
#define HEADER_TIMER

#include <Standard.h>
#include <ZappTypes.h>
#include <Queue.h>
#include <Thread.h>
#include <Functor.h>

namespace Zapp {

class Time
{
public:
    static TUint Now();
    static TBool IsBeforeOrAt(TUint aQuestionableTime, TUint aTime);
    static TBool IsAfter(TUint aQuestionableTime, TUint aTime);
    static TBool IsInPastOrNow(TUint aTime);
    static TBool IsInFuture(TUint aTime);
    static TInt TimeToWaitFor(TUint aTime);
};

class QueueSortedEntryTimer : public QueueSortedEntry
{
    friend class TimerManager;
protected:
    TUint iTime;  // Absolute (milliseconds from startup)
};

class Timer : public QueueSortedEntryTimer
{
    friend class TimerManager;
public:
    Timer(Functor aFunctor);
    void FireIn(TUint aTime); // Relative (milliseconds from now)
    void FireAt(TUint aTime); // Absolute (at specified millisecond)
    void Cancel();
    ~Timer();
private:
    Functor iFunctor;
};

class TimerManager : public QueueSorted<Timer>
{
    friend class Timer;
public:
    TimerManager();
    void Stop();
    ~TimerManager();
private:
    void Run();
    void Fire();
    Zapp::Thread* Thread() const;
    virtual void HeadChanged(QueueSortedEntry& aEntry);
    virtual TInt Compare(QueueSortedEntry& aEntry1, QueueSortedEntry& aEntry2);
private:
    QueueSortedEntryTimer iNow;
    Mutex iMutexNow;
    TBool iRemoving;
    ThreadFunctor* iThread;
    Semaphore iSemaphore;
    Mutex iMutex;
    TUint iNextTimer;
    TBool iStop;
    Semaphore iStopped;
    Mutex iCallbackMutex;
    Zapp::Thread* iThreadHandle;
};

class Moderator
{
public:
    Moderator(Functor aFunctor, TUint aModerationMs);
    ~Moderator();
    void Moderate();
private:
    void Redirect();
    Timer* iTimer;
    TBool iTimerStarted;
    Mutex iMutex;
    Functor iModeratedFunctor;
    TUint iModerationMs;
};

} // namespace Zapp

#endif // HEADER_TIMER
