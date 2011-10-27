#ifndef HEADER_THREAD
#define HEADER_THREAD

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/OsTypes.h>

EXCEPTION(ThreadKill);
EXCEPTION(Timeout);
EXCEPTION(ThreadUnknown);

namespace OpenHome {

enum ThreadPriority {
    //Total priority range is 50 -> 150 inclusive = 101 possible priorities
    //NOTE: Do not use less than eLowest or greater than eHighest without
    //discussing the system wide implications with others.
    kPriorityMuchMore = 4
   ,kPriorityMore = 2
   ,kPriorityLess = -2
   ,kPriorityMuchLess = -4

   ,kPrioritySystemLowest = 51
   ,kPriorityLowest = 60
   ,kPriorityVeryLow = 70
   ,kPriorityLower = 80
   ,kPriorityLow = 90
   ,kPriorityNormal = 100
   ,kPriorityHigh = 110
   ,kPriorityHigher = 120
   ,kPriorityVeryHigh = 130
   ,kPriorityHighest = 140
   ,kPrioritySystemHighest = 150
};

class Semaphore : public INonCopyable
{
public:
    static const TUint kWaitForever = 0;
    Semaphore(const TChar* aName, TUint aCount);
    virtual ~Semaphore();

    void Wait();
    // Note: aTimeoutMs == 0 means wait forever
    void Wait(TUint aTimeoutMs);
    /**
     * Clear any pending signals
     *
     * @return  true if signals were cleared; false otherwise
     */
    TBool Clear();
    void Signal();
private:
    THandle iHandle;
};

class DllExportClass Mutex : public INonCopyable
{
public:
    DllExport Mutex(const TChar* aName);
    DllExport virtual ~Mutex();

    DllExport void Wait();
    DllExport void Signal();
private:
    THandle iHandle;
    TChar iName[5];
};

/**
 * Abstract runnable thread class
 *
 * Only threads created using this library can be treated as Thread objects
 */
class Thread : public INonCopyable
{
    friend class SemaphoreActive;
public:
    static const TUint kDefaultStackBytes;
public:
    /**
     * Destructor.  Automatically calls Join()
     */
    virtual ~Thread();

    /**
     * Second phase constructor.  The thread will not Run() until this is called
     */
    void Start();
public:
    /**
     * Wait on the thread being signalled or killed.
     * Will not automatically complete when the thread exits.
     * Throws ThreadKill if Kill() has been called.
     */
    void Wait();

    /**
     * Completes one (current or future) caller to Wait()
     */
    void Signal();

    /**
     * Wait()s only if the thread has already been signalled.
     * Throws ThreadKill if Kill() has been called.
     */
    TBool TryWait();

    /**
     * Pause the current thread.  Won't automatically block other threads but may
     * block some if this thread holds resources they are waiting for.
     *
     * @param aMilliSecs   Number of milliseconds to sleep for
     */
    static void Sleep(TUint aMilliSecs);
    
    /**
     * Return a reference to the current thread.
     */
    static Thread* Current();

    /**
     * Query whether the platform port supports thread priorities
     */
    static TBool SupportsPriorities();

    /**
     * Mark a thread as to be killed.  The thread will not exit immediately
     */
    void Kill();

    /**
     * Returns the thread's 4 char name
     */
    const Brx& Name() const;

    bool operator== (const Thread&) const;
    bool operator!= (const Thread&) const;
protected:
    /**
     * Constructor.
     *
     * @param aName        Thread name.  Max 4 chars; need not be unique
     * @param aPriority    Priority to run the thread at
     * @param aStackBytes  Stack size in bytes
     */
    Thread(const TChar* aName, TUint aPriority = kPriorityNormal, TUint aStackBytes = kDefaultStackBytes);
    virtual void Run() = 0;

    /**
     * Throws ThreadKill if Kill() has been called.
     */
    void CheckForKill() const;

    /**
     * Intended for use from derived destructors.  Multiple levels of dtor can all Join() safely
     */
    void Join();
private:
    static void EntryPoint(void* aArg);
protected:
    THandle iHandle;
    static const TUint kNameBytes = 4;
    Bws<kNameBytes+1> iName;
    Semaphore iSema;
private:
    Semaphore iTerminated;
    TBool     iKill;
    TUint     iStackBytes;
    TUint     iPriority;
};

/**
 * Create a custom thread without needing to create a custom subclass
 */
class ThreadFunctor : public Thread
{
public:
    /**
     * Constructor.
     *
     * @param aName        Thread name.  Max 4 chars; need not be unique
     * @param aFunctor     Entrypoint function to run
     * @param aPriority    Priority to run the thread at
     * @param aStackBytes  Stack size in bytes
     */
    ThreadFunctor(const TChar* aName, Functor aFunctor, TUint aPriority = kPriorityNormal, TUint aStackBytes = kDefaultStackBytes);
    ~ThreadFunctor();
private:
    virtual void Run();
private:
    Functor iFunctor;
    Semaphore iStarted;
};

class SemaphoreActive
{
public:
    SemaphoreActive(Semaphore& aSema);
    SemaphoreActive(Thread& aThread);
    void Signal();
    TBool Signalled();
    void ConsumeOne();
    void ConsumeAll();
private:
    Semaphore& iSema;
    Mutex iLock;
    TInt iCount;
};

/**
 * Utility class.
 *
 * Create an AutoMutex on the stack using a reference to a Mutex. It will
 * automatically be signalled on stack cleanup (ie on return or when an
 * exception passes up).
 */
class DllExportClass AutoMutex : public INonCopyable
{
public:
    DllExport AutoMutex(Mutex& aMutex);
    DllExport ~AutoMutex();
private:
    Mutex& iMutex;
};

class AtomicInt : public INonCopyable
{
public:
    AtomicInt(TInt aInitialValue);
    AtomicInt();
    TInt Inc();
    TInt Dec();
private:
    TInt iInt;
};

} // namespace OpenHome

#endif
