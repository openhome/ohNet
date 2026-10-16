#ifndef HEADER_TIMER
#define HEADER_TIMER

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Time.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Functor.h>

namespace OpenHome {

class Environment;

class TimerManager;

class ITimer
{
public:
    virtual ~ITimer() {}
    virtual void FireIn(TUint aMs) = 0;
    virtual void Cancel() = 0;
};

class ITimerFactory
{
public:
    virtual ~ITimerFactory() {}
    virtual ITimer* CreateTimer(Functor aCallback, const TChar* aId) = 0;
};

class TimerFactory : public ITimerFactory, private OpenHome::INonCopyable
{
public:
    TimerFactory(Environment& aEnv);
public: // from ITimerFactory
    ITimer* CreateTimer(Functor aCallback, const TChar* aId);
private:
    Environment& iEnv;
};

class Timer : public ITimer, private OpenHome::INonCopyable
{
    friend class TimerManager;
public:
    Timer(Environment& aEnv, Functor aFunctor, const TChar* aId);
    void FireIn(TUint aTime); // Relative (milliseconds from now)
    void FireAt(TUint aTime); // Absolute (at specified millisecond)
    void Cancel();
    const TChar* Id() const;
    ~Timer();
private:
    TimerManager& iMgr;
    Functor iFunctor;
    const TChar* iId;
    Timer* iNext;  // Next entry in TimerManager's list.  NULL if last, or if not queued.
    TUint iTime;   // Absolute (milliseconds from startup).  Only meaningful while iQueued.
    TBool iQueued; // True iff this timer is currently in TimerManager's list.
};

/* Timers are held in a single list, sorted by deadline, owned outright by the
   manager thread's lock.  Callbacks run on the manager thread with no lock
   held, so a callback may take any lock, and any thread may cancel any timer
   other than the one whose callback is running at that instant. */

class TimerManager : private OpenHome::INonCopyable
{
    friend class Timer;
public:
    TimerManager(Environment& aEnv, TUint aThreadPriority);
    void Stop();
    ~TimerManager();
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
    void FireAt(Timer& aTimer, TUint aTime);
    void Cancel(Timer& aTimer);
    void InsertLocked(Timer& aTimer);
    void RemoveLocked(Timer& aTimer);
private:
    Environment& iEnv;
    Mutex iLock;           // guards iHead, iRunning, iCancelWaiters, iStop
    Semaphore iWake;       // wakes the manager thread when the list changes
    Semaphore iCancelDone; // signalled once a callback returns, for waiting cancellers
    Timer* iHead;          // sorted by deadline, soonest first.  NULL when empty.
    Timer* iRunning;       // timer whose callback is executing, else NULL
    ThreadFunctor* iThread;
    TBool iStop;
    Semaphore iStopped;
    static const TUint kMaxBusyTimeMs = 1000 * 60 * 30; // 30 minutes
    static const TUint kMaxTimerGranularityMs = 10;
    static const TUint kMaxCallbacksPerTick = 1000;
    // the following are only ever touched by the manager thread
    TUint iBusyStartTimeMs;
    TUint iLastRunTimeMs;
    TUint iCallbacksPerTick;
    CallbackList iCallbackList;
};

} // namespace OpenHome

#endif // HEADER_TIMER
