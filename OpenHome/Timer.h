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

class ITimer
{
public:
    virtual ~ITimer() {}
    virtual void FireIn(TUint aMs) = 0;
    virtual void Cancel() = 0;
};

class Timer : public QueueSortedEntryTimer, public ITimer
{
    friend class TimerManager;
public:
    Timer(Environment& aEnv, Functor aFunctor, const TChar* aId);
    void FireIn(TUint aTime); // Relative (milliseconds from now)
    void FireAt(TUint aTime); // Absolute (at specified millisecond)
    void Cancel();
    const TChar* Id() const;
    ~Timer();
    static TBool IsInManagerThread(Environment& aEnv);
private:
    static TBool IsInManagerThread(TimerManager& aMgr);
private:
    TimerManager& iMgr;
    Functor iFunctor;
    const TChar* iId;
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
    class Callback
    {
    public:
        Callback();
        void Set(void* aPtr, const TChar* aId);
        void Log() const;
    private:
        void* iPtr;
        const TChar* iId;
    };
    class CallbackList
    {
        static const TUint kElements = 100;
    public:
        CallbackList();
        void Add(Timer& aTimer);
        void Log() const;
    private:
        static void IncIndex(TUint& aIndex);
        static void DecIndex(TUint& aIndex);
    private:
        Callback iList[kElements];
        TUint iHead;
        TUint iTail;
    };
private:
    void Run();
    void Fire();
    void FireAt(Timer& aTimer, TUint aTime);
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
    Mutex iMutexTimer;
    TUint iNextTimer;
    TBool iStop;
    Semaphore iStopped;
    Mutex iCallbackMutex;
    Thread* iThreadHandle;
    static const TUint kMaxBusyTimeMs = 1000 * 60 * 30; // 30 minutes
    static const TUint kMaxTimerGranularityMs = 10;
    static const TUint kMaxCallbacksPerTick = 1000;
    TUint iBusyStartTimeMs;
    TUint iLastRunTimeMs;
    TUint iCallbacksPerTick;
    CallbackList iCallbackList;
};

} // namespace OpenHome

#endif // HEADER_TIMER
