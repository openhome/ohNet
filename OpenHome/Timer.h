#ifndef HEADER_TIMER
#define HEADER_TIMER

#include <OpenHome/Private/Standard.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Queue.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Functor.h>

namespace OpenHome {

namespace Net {
    class Stack;
} // namespace OpenHome

class Time
{
public:
    static TUint Now(Net::Stack& aStack);
    static TBool IsBeforeOrAt(TUint aQuestionableTime, TUint aTime);
    static TBool IsAfter(TUint aQuestionableTime, TUint aTime);
    static TBool IsInPastOrNow(Net::Stack& aStack, TUint aTime);
    static TBool IsInFuture(Net::Stack& aStack, TUint aTime);
    static TInt TimeToWaitFor(Net::Stack& aStack, TUint aTime);
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
    Timer(Net::Stack& aStack, Functor aFunctor);
    void FireIn(TUint aTime); // Relative (milliseconds from now)
    void FireAt(TUint aTime); // Absolute (at specified millisecond)
    void Cancel();
    ~Timer();
    static TBool IsInManagerThread(Net::Stack& aStack);
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
    TimerManager(Net::Stack& aStack);
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
    Net::Stack& iStack;
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
