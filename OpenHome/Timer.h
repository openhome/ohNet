#ifndef HEADER_TIMER
#define HEADER_TIMER

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Queue.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Functor.h>

namespace OpenHome {

class Environment;

class Time
{
public:
    static TUint Now(Environment& aEnv);
    static TBool IsBeforeOrAt(TUint aQuestionableTime, TUint aTime);
    static TBool IsAfter(TUint aQuestionableTime, TUint aTime);
    static TBool IsInPastOrNow(Environment& aEnv, TUint aTime);
    static TBool IsInFuture(Environment& aEnv, TUint aTime);
    static TInt TimeToWaitFor(Environment& aEnv, TUint aTime);
};

class QueueSortedEntryTimer : public QueueSortedEntry
{
    friend class TimerManager;
protected:
    TUint iTime;  // Absolute (milliseconds from startup)
};

class TimerManager;

class Timer : public QueueSortedEntryTimer
{
    friend class TimerManager;
public:
    Timer(Environment& aEnv, Functor aFunctor);
    void FireIn(TUint aTime); // Relative (milliseconds from now)
    void FireAt(TUint aTime); // Absolute (at specified millisecond)
    void Cancel();
    ~Timer();
    static TBool IsInManagerThread(Environment& aEnv);
private:
    static TBool IsInManagerThread(TimerManager& aMgr);
private:
    TimerManager& iMgr;
    Functor iFunctor;
};

class TimerManager : public QueueSorted<Timer>
{
    friend class Timer;
public:
    TimerManager(Environment& aEnv);
    void Stop();
    ~TimerManager();
    void CallbackLock();
    void CallbackUnlock();
private:
    void Run();
    void Fire();
    Thread* MgrThread() const;
    virtual void HeadChanged(QueueSortedEntry& aEntry);
    virtual TInt Compare(QueueSortedEntry& aEntry1, QueueSortedEntry& aEntry2);
private:
    Environment& iEnv;
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
    Thread* iThreadHandle;
};

} // namespace OpenHome

#endif // HEADER_TIMER
