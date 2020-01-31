#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/OsWrapper.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

const TUint32 kSleepMs = 500; // short sleep used as a lazy way of avoiding too many dependencies on thread priorities
const TUint64 kInstrumentTriggerUs = 400000; //400ms

class TestStack
{
public:
    TestStack();
    void Push(TChar aChar);
    TBool Pop(TChar aChar);
    TBool IsEmpty() const;
private:
    static const TUint kMaxStackEntries = 2;
    TChar iEnv[kMaxStackEntries];
    TUint iCount;
    mutable Mutex iLock;
};

TestStack::TestStack()
: iCount(0), iLock("")
{}

void TestStack::Push(TChar aChar)
{
    AutoMutex _(iLock);
    ASSERT(iCount < kMaxStackEntries);
    iEnv[iCount++] = aChar;
}

TBool TestStack::Pop(TChar aChar)
{
    AutoMutex _(iLock);
    ASSERT(iCount != 0);
    iCount--;
    return aChar == iEnv[iCount];
}

TBool TestStack::IsEmpty() const
{
    AutoMutex _(iLock);
    return iCount == 0;
}


static TestStack* gTestStack;

class TestThread : public Thread
{
public:
    TestThread(const TChar* aName, TChar aChar, TUint aPriority = kPriorityNormal);
    void Run();
    THandle Handle() const { return iHandle; }
private:
    TChar iChar;
};

TestThread::TestThread(const TChar* aName, TChar aChar, TUint aPriority)
: Thread(aName, aPriority), iChar(aChar)
{
}

void TestThread::Run()
{
    while(1) {
        Wait();
        gTestStack->Push(iChar);
    }
}

class SuiteStartStop : public Suite
{
public:
    SuiteStartStop() : Suite("Starting and Stopping threads") {}
    void Test();
};

void SuiteStartStop::Test()
{
    Thread* threadA = new TestThread("THDA", 'A');
    Thread* threadB = new TestThread("THDB", 'B');

    TEST( ((Thread&) *threadA) == ((Thread&) *threadA) );
    TEST( ((Thread&) *threadA) != ((Thread&) *threadB) );

    threadA->Start();
    threadB->Start();

    for( TUint i = 0 ; i< 10; ++i) {
        TEST(gTestStack->IsEmpty());
        threadA->Signal();
        // use sleeps to avoid dependency on thread priorities being supported
        Thread::Sleep(kSleepMs);
        TEST(gTestStack->Pop('A'));

        threadB->Signal();
        Thread::Sleep(kSleepMs);
        TEST(gTestStack->Pop('B'));

        threadA->Signal();
        Thread::Sleep(kSleepMs);
        TEST(gTestStack->Pop('A'));
    }
    TEST(gTestStack->IsEmpty());

    delete threadA;
    delete threadB;
}

class SuitePriority : public Suite
{
public:
    SuitePriority() : Suite("Thread Priority") {}
    void Test();
};

void SuitePriority::Test()
{
    Thread* threadA = new TestThread("THDA", 'A', kPriorityLow);
    Thread* threadB = new TestThread("THDB", 'B', kPriorityLow + kPriorityLess);
    TEST(gTestStack->IsEmpty());

    threadA->Start();
    threadB->Start();
    TEST(gTestStack->IsEmpty());
    threadA->Signal();
    threadB->Signal();
    TEST(gTestStack->IsEmpty());
    Thread::Sleep(kSleepMs);
    TEST(gTestStack->Pop('B')); //thread B ran second
    TEST(gTestStack->Pop('A')); //thread A ran first
    TEST(gTestStack->IsEmpty());
    delete threadA;
    delete threadB;

    threadA = new TestThread("THDA", 'a', kPriorityLowest);
    threadB = new TestThread("THDB", 'b', kPriorityLowest+1);
    TEST(gTestStack->IsEmpty());

    threadA->Start();
    threadB->Start();
    threadA->Signal();
    threadB->Signal();
    Thread::Sleep(kSleepMs);
    TEST(gTestStack->Pop('a')); //thread A ran second
    TEST(gTestStack->Pop('b')); //thread B ran first
    TEST(gTestStack->IsEmpty());
    delete threadA;
    delete threadB;
}


class SuiteTimeslice: public Suite
{
public:
    SuiteTimeslice() : Suite("Thread Timeslicing") {}
    void Test();
};

// Sorry for the bulk, I went a bit overboard on the Timeslicing stuff.
// Basically, the test suite launches a monitor thread, which in turn
// launches counter threads and monitors their progress.
//
// There are two test cases - one tests for equal progress made by both
// counter threads, and the other creates a higher priority thread to
// preempt the counters. The monitor thread then tests for zero-progress
// in the second counter thread.

const TUint kThreadCounterMaxCount      = 20000000;
const TUint kThreadDisruptorPeriodMs    = 100;
const TUint kThreadMonitorPeriodMs      = 1000;
const TUint kSuitePriority              = kPrioritySystemHighest;

// <ThreadCounter>
class ThreadCounter : public Thread
{
public:
    ThreadCounter( TUint aPriority, TUint aCeiling )
        : Thread( "CounterThread", aPriority ),
        iHasFinished(false),
        iCount(0),
        iOldCount(0),
        iCeiling(aCeiling)
        {};

    void Run();
    TBool HasMadeProgress();
    TBool HasFinished()          { return iHasFinished; };
private:
    TBool   iHasFinished;
    TUint   iCount;
    TUint   iOldCount;
    TUint   iCeiling;
};

void ThreadCounter::Run()
{
    for ( iCount = 0 ; iCount < iCeiling ; iCount++ )
    {
        if ( iCount == 0 )              // Forces optimisation to make iCount available.
        {
            Print( "" );
        }
    }

    iHasFinished = true;
    Wait();
}

TBool ThreadCounter::HasMadeProgress()
{
    TBool hasMadeProgress = ( iCount > iOldCount );
    iOldCount = iCount;
    return hasMadeProgress;
}
// </ThreadCounter>

// <ThreadDisruptor> This Thread periodcally preempts all lower priority threads
class ThreadDisruptor : public Thread
{
public:
    ThreadDisruptor( TUint aPriority, TUint aPeriodMs )
        : Thread( "DisruptorThread", aPriority ),
        iPeriodMs( aPeriodMs )
        {}
    void Run();
private:
    TUint iPeriodMs;
};

void ThreadDisruptor::Run()
{
    while(1)
    {
        Sleep( iPeriodMs );
        CheckForKill();
    }
}
// </ThreadDisruptor>


// <ThreadMonitor> This class creates two ThreadCounters and monitors their progress.
class ThreadMonitor : public Thread
{
public:
    ThreadMonitor( TUint aPriority, TUint aPeriodMs, TBool aUseDisruptor, Thread& aCaller )
        : Thread( "MonitorThread", aPriority ),
        iUseDisruptor( aUseDisruptor ),
        iPeriodMs( aPeriodMs ),
        iCaller( aCaller ),
        iPriority(aPriority)
        {}

    void Run();
private:
    TBool               iUseDisruptor;
    TUint               iPeriodMs;
    Thread&             iCaller;
    TUint               iPriority;
};

void ThreadMonitor::Run()
{
    TUint testCounter = 0;

    ThreadDisruptor *threadDisruptor = NULL;
    ThreadCounter   *threadCounter1 = new ThreadCounter( iPriority-2, kThreadCounterMaxCount );        // Create counters
    ThreadCounter   *threadCounter2 = new ThreadCounter( iPriority-2, kThreadCounterMaxCount );

    if ( iUseDisruptor )
    {
        threadDisruptor = new ThreadDisruptor( iPriority-1, kThreadDisruptorPeriodMs );
        threadDisruptor->Start();                              // Start disruptor thread if required.
    }

    threadCounter1->Start();                                   // Start counters
    threadCounter2->Start();

    Sleep( iPeriodMs );                                         // Do initial sleep()

    while( (testCounter++ < 4) && (!threadCounter1->HasFinished()) )
    {
        if ( ! iUseDisruptor )
        {
            TEST( threadCounter1->HasMadeProgress() );         // If normal mode, test for progress in both threads
            TEST( threadCounter2->HasMadeProgress() );
        }
        else
        {
            TEST(   threadCounter1->HasMadeProgress() );       // else test for zero-progress in second thread
            TEST( ! threadCounter2->HasMadeProgress() );
        }

        Sleep( iPeriodMs );
    }

    if ( iUseDisruptor )
    {
        delete threadDisruptor;
    }

    threadCounter1->Signal();                                  // Allow conter threads to terminate normally.
    threadCounter2->Signal();

    delete threadCounter1;
    delete threadCounter2;

    iCaller.Signal();
}


class TimesliceTestThread : public Thread
{
public:
    TimesliceTestThread(Semaphore& aSem) : Thread("TSLT", kSuitePriority), iSem(aSem) {}
    void Run();
private:
    Semaphore& iSem;
};

void TimesliceTestThread::Run()
{
    // Starting Normal Timeslicing Conditions ...
    ThreadMonitor *tm1 = new ThreadMonitor((kSuitePriority-1), kThreadMonitorPeriodMs, false, *this);
    tm1->Start();
    Wait();
    iSem.Signal();
}

void SuiteTimeslice::Test()
{
    Semaphore sem("TSLS", 0);
    TimesliceTestThread* th = new TimesliceTestThread(sem);
    th->Start();
    sem.Wait();
    delete th;
}

class SuiteSemaphore : public Suite
{
public:
    SuiteSemaphore() : Suite("Semaphore") {}
    void Test();
};

class SemaphoreThread : public Thread
{
public:
    SemaphoreThread(Semaphore& aSem) : Thread("SEMT", kPriorityVeryLow), iSem(aSem), iWaitsGuard("SMWG", 0), iWaits(0) {}
    ~SemaphoreThread();
    void Run();
    TInt Waits();
private:
    Semaphore& iSem;
    Semaphore iWaitsGuard;
    TInt iWaits;
};

SemaphoreThread::~SemaphoreThread()
{
    TEST(!iWaitsGuard.Clear());
}

void SemaphoreThread::Run()
{
    // we use iWaitsGuard to synchronise our two threads in the absense of reliable thread priorities
    // its unfortunate that we have to rely on correct behaviour from a semaphore to test a semaphore...
    iWaitsGuard.Signal();
    iSem.Wait();
    iWaits++;
    iWaitsGuard.Signal();
    iSem.Wait();
    iWaits++;
    iSem.Wait();
    iWaits++;
    iSem.Wait();
    iWaits++;
    iWaitsGuard.Signal();
    iSem.Wait();
}

TInt SemaphoreThread::Waits()
{
    iWaitsGuard.Wait();
    return iWaits;
}

class SignalThread : public Thread
{
public:
    SignalThread(Semaphore& aOwner);
    ~SignalThread();
    Semaphore& Sem() { return iSelf; }
    void Run();
private:
    Semaphore& iOwner;
    Semaphore  iSelf;
};

SignalThread::SignalThread(Semaphore& aOwner)
    : Thread("SEM2")
    , iOwner(aOwner)
    , iSelf("STHS", 0)
{
}

SignalThread::~SignalThread()
{
    Kill();
    iSelf.Signal();
    Join();
}

void SignalThread::Run()
{
    while (1) {
        iSelf.Wait();
        iOwner.Signal();
        CheckForKill();
    }
}

void SuiteSemaphore::Test()
{
    // basic test - stack Semaphore
    Semaphore sem1("TMP1", 1);
    sem1.Wait();
    TEST_THROWS(sem1.Wait(1), Timeout);
    TEST(sem1.Clear() == false);
    sem1.Signal();
    TEST(sem1.Clear() == true);
    sem1.Signal();

    // basic test - heap Semaphore
    Semaphore* sem2 = new Semaphore("TMP2", 1);
    sem2->Wait();
    TEST(sem2->Clear() == false);
    sem2->Signal();
    TEST(sem2->Clear() == true);
    delete sem2;

    // check that another thread will wait on signal
    // ...and that multiple calls to Signal() complete multiple Wait()s
    Semaphore sem3("TMP3", 0);
    SemaphoreThread* semTh = new SemaphoreThread(sem3);
    semTh->Start();
    TEST(semTh->Waits() == 0);
    sem3.Signal();
    TEST(semTh->Waits() == 1);
    sem3.Signal();
    sem3.Signal();
    sem3.Signal();
    TEST(semTh->Waits() == 4);
    sem3.Signal();
    delete semTh;

    // test thread safety of Semaphore
    Semaphore sem4("TMP4", 0);
    static const int kNumSignalThreads = 10;
    SignalThread* th[kNumSignalThreads];
    int i, j;
    for (i=0; i<kNumSignalThreads; i++) {
        th[i] = new SignalThread(sem4);
        th[i]->Start();
    }
    for (i=0; i<1000; i++) {
        for (j=0; j<kNumSignalThreads; j++) {
            th[j]->Sem().Signal();
        }
        for (j=0; j<kNumSignalThreads; j++) {
            try {
                sem4.Wait(500);
            }
            catch(Timeout&) {
                TEST(1==0);
            }
        }
        TEST(!sem4.Clear());
    }
    for (i=0; i<kNumSignalThreads; i++) {
        delete th[i];
    }
}


class SuiteMutex : public Suite
{
public:
    SuiteMutex() : Suite("Mutexes") {}
    void Test();
};

class MutexThread : public Thread
{
public:
    MutexThread(IMutex& aMutex, TInt& aCount) : Thread("MUTT"), iMutex(aMutex), iCount(aCount) {}
    void Run();
private:
    IMutex& iMutex;
    TInt& iCount;
};

void MutexThread::Run()
{
    iMutex.Wait();
    iCount++;
    iMutex.Signal();
}

void SuiteMutex::Test()
{
#if 0
    {
        Mutex mutex("MUT1");
        mutex.Wait();
        mutex.Signal();

        // check that another thread will block waiting on this mutex
        TInt count = 0;
        mutex.Wait();
        MutexThread* mutexTh = new MutexThread(mutex, count);
        mutexTh->Start();
        Thread::Sleep(kSleepMs);
        TEST(count == 0);
        mutex.Signal();
        Thread::Sleep(kSleepMs);
        mutex.Wait();
        TEST(count == 1);
        mutex.Signal();
        delete mutexTh;
    }
    {
        IMutex* mutex = MutexFactory::Create("MUT1", true, kInstrumentTriggerUs);
        mutex->Wait();
        mutex->Signal();

        // check that another thread will block waiting on this mutex
        TInt count = 0;
        mutex->Wait();
        MutexThread* mutexTh = new MutexThread(*mutex, count);
        mutexTh->Start();
        Thread::Sleep(kSleepMs);
        TEST(count == 0);
        mutex->Signal();
        Thread::Sleep(kSleepMs);
        mutex->Wait();
        TEST(count == 1);
        mutex->Signal();
        delete mutexTh;
        delete mutex;
    }
#endif
}

class SuitePerformance : public Suite
{
public:
    SuitePerformance() : Suite("Performance") {}
    void Test();
};

class ThreadPerformance : public Thread
{
public:
    ThreadPerformance(TUint aPriority=kPriorityNormal);
    void Run();
    void Signal() { iSem.Signal(); }
private:
    Semaphore iSem;
};

ThreadPerformance::ThreadPerformance(TUint aPriority)
    : Thread("PERF", aPriority), iSem("", 0)
{
}

void ThreadPerformance::Run()
{
    iSem.Wait();
}

void SuitePerformance::Test()
{
    const TUint kNumThreads = 60;
    ThreadPerformance* threads[kNumThreads];
    TUint i=0;

    TUint start = TimeStart();
    for(i = 0; i<kNumThreads; i++) {
        threads[i] = new ThreadPerformance(kPriorityLow);
    }
    TUint time = TimeStop(start);
    TEST(time < 50);

    start = TimeStart();
    for(i=0; i<kNumThreads; i++) {
        threads[i]->Start();
    }
    time = TimeStop(start);
    TEST(time < 21);

    // Let the threads die
    for(i = 0; i<kNumThreads; i++) {
        threads[i]->Signal();
    }
    OpenHome::Thread::Sleep(50);
}


class SuiteAutoMutex : public Suite
{
public:
    SuiteAutoMutex() : Suite("AutoMutex Functionality") {}
    void Test();
    void Hold(Mutex& aMutex);
};

void SuiteAutoMutex::Hold(Mutex& aMutex)
{
    AutoMutex a(aMutex);
}

void SuiteAutoMutex::Test()
{
    Mutex mA("muta");
    Mutex mB("mutb");

    Hold(mA);
    mA.Wait();

    {
        AutoMutex amB(mB);
    }
    mB.Wait();
    mB.Signal();
    mA.Signal();
}


class SuiteAutoSemaphore : public Suite
{
public:
    SuiteAutoSemaphore() : Suite("AutoSemaphore functionality") {}
    void Test();
};

void SuiteAutoSemaphore::Test()
{
    Semaphore sem("asem", 1);
    {
        AutoSemaphore _(sem);
        TEST(!sem.Clear());
    }
    TEST(sem.Clear());
}

class ThreadKillable : public Thread
{
public:
    ThreadKillable(Semaphore& aSem) : Thread("KILL"), iSem(aSem) {}
    void Run();
private:
    Semaphore& iSem;
};

void ThreadKillable::Run()
{
    try {
        TEST(TryWait() == false);
        Signal();
        TEST(TryWait() == true);
        CheckForKill();
        Kill();
        TEST_THROWS(CheckForKill(), ThreadKill);
        TEST_THROWS(Wait(), ThreadKill);
        TEST_THROWS(TryWait(), ThreadKill);
    }
    catch(ThreadKill&) {
        ASSERT(0);
    }
    iSem.Signal();
}

class SuiteThreadKill : public Suite
{
public:
    SuiteThreadKill() : Suite("Thread kill") {}
    void Test();
};

void SuiteThreadKill::Test()
{
    Semaphore sem("", 0);
    Thread* th = new ThreadKillable(sem);
    th->Start();
    sem.Wait();
    delete th;
}

class ThreadDummy : public Thread
{
public:
    ThreadDummy(TUint aPriority = kPriorityNormal) : Thread("DUMM", aPriority) {}
public: // from Thread
    void Run() {}
};


class SuiteThreadNotStarted : public Suite
{
public:
    SuiteThreadNotStarted() : Suite("Thread not started") {}
    void Test();
};

void SuiteThreadNotStarted::Test()
{
    Thread* th = new ThreadDummy();
    delete th;

    // Successful completion of this test signifies that Threads can be deleted
    // without having been Start()ed.
}

// A saw wave of priorities. For fun, and also to make StartDelete code more readable.
class PrioSaw
{
public:
    PrioSaw(TUint aPrioMin, TUint aPrioMax)
    : iPrioMin(aPrioMin)
    , iPrioMax(aPrioMax)
    , iPrioCurrent(iPrioMin)
    , iStep(1)
    {
        ASSERT(iPrioMin < iPrioMax);
    }
    TUint Next()
    {
        TUint prio = iPrioCurrent;
        iPrioCurrent += iStep;
        if ( iPrioCurrent == iPrioMin || iPrioCurrent == iPrioMax ) {
            iStep *= -1;
        }
        return prio;
    }
private:
    TUint iPrioMin;
    TUint iPrioMax;
    TUint iPrioCurrent;
    TInt iStep;
};

class SuiteThreadStartDelete : public Suite
{
private:
    static const TUint kThreadCount = 10000;
    static const TUint kUpdateInterval = 100;
public:
    SuiteThreadStartDelete() : Suite("Thread start and delete cycle") {}
    void Test();
};

void SuiteThreadStartDelete::Test()
{
    PrioSaw ps(kPrioritySystemLowest, kPrioritySystemHighest);

    for (TUint i=0; i< kThreadCount; i++) {
        Thread* th = new ThreadDummy(ps.Next());
        th->Start();
        delete th;

        if (i % kUpdateInterval == 0) {
            TEST(true); // only to show progress
            Thread::Sleep(100); // FreeRTOS delegates freeing of thread resources to the idle thread. We allow it to run here.
        }
    }
}


class SuiteThreadFunctor : public Suite
{
public:
    SuiteThreadFunctor() : Suite("ThreadFunctor") {}
    void Test();
private:
    void Run();
private:
    Semaphore* iSem;
    ThreadFunctor* iFunctor;
};

void SuiteThreadFunctor::Test()
{
    iSem = new Semaphore("", 0);
    iFunctor = new ThreadFunctor("STFF", MakeFunctor(*this, &SuiteThreadFunctor::Run));
    iFunctor->Start();
    iSem->Wait();
    delete iFunctor;
    delete iSem;
}

void SuiteThreadFunctor::Run()
{
    try {
        TEST(iFunctor->TryWait() == false);
        iFunctor->Signal();
        TEST(iFunctor->TryWait() == true);
        iFunctor->CheckCurrentForKill();
        iFunctor->Kill();
        TEST_THROWS(iFunctor->CheckCurrentForKill(), ThreadKill);
        TEST_THROWS(iFunctor->Wait(), ThreadKill);
        TEST_THROWS(iFunctor->TryWait(), ThreadKill);
    }
    catch(ThreadKill&) {
        ASSERT(0);
    }
    iSem->Signal();
}


class SuiteThreadFunctorNotStarted : public Suite
{
public:
    SuiteThreadFunctorNotStarted() : Suite("ThreadFunctor not started") {}
    void Test();
private:
    void Run() {}
};

void SuiteThreadFunctorNotStarted::Test()
{
    ThreadFunctor* tf = new ThreadFunctor("STFF", MakeFunctor(*this, &SuiteThreadFunctorNotStarted::Run));
    delete tf;

    // Successful completion of this test signifies that ThreadFunctors can be
    // deleted without having been Start()ed.
}


class SuiteThreadFunctorStartDelete : public Suite
{
private:
    static const TUint kThreadCount = 10000;
    static const TUint kUpdateInterval = 100;
public:
    SuiteThreadFunctorStartDelete() : Suite("ThreadFunctor start and delete cycle") {}
    void Test();
private:
    void Run() {}
};

void SuiteThreadFunctorStartDelete::Test()
{
    PrioSaw ps(kPrioritySystemLowest, kPrioritySystemHighest);

    for (TUint i=0; i< kThreadCount; i++) {
        ThreadFunctor* tf = new ThreadFunctor("TFSD", MakeFunctor(*this, &SuiteThreadFunctorStartDelete::Run), ps.Next());
        tf->Start();
        delete tf;

        if (i % kUpdateInterval == 0) {
            TEST(true); // only to show progress
            Thread::Sleep(100); // FreeRTOS delegates freeing of thread resources to the idle thread. We allow it to run here.
        }
    }
}


class PriorityArbitratorDummy : public IPriorityArbitrator
{
public:
    PriorityArbitratorDummy(TUint aMin, TUint aMax, TUint aRange)
        : iMin(aMin)
        , iMax(aMax)
        , iRange(aRange)
    {}
private: // from IPriorityArbitrator
    TUint Priority(const TChar* /*aId*/, TUint /*aRequested*/, TUint /*aHostMax*/) { ASSERTS(); return 0; }
    TUint OpenHomeMin() const { return iMin; }
    TUint OpenHomeMax() const { return iMax; }
    TUint HostRange() const { return iRange; }
private:
    TUint iMin;
    TUint iMax;
    TUint iRange;
};

class SuitePriorityArbitrator : public Suite, private IPriorityArbitrator
{
public:
    SuitePriorityArbitrator();
private: // from Suite
    void Test();
private: // from IPriorityArbitrator
    TUint Priority(const TChar* aId, TUint aRequested, TUint aHostMax);
    TUint OpenHomeMin() const;
    TUint OpenHomeMax() const;
    TUint HostRange() const;
private:
    TUint iOpenHomeMin;
    TUint iOpenHomeMax;
    TUint iHostRange;
    TUint iHostMax;
};

SuitePriorityArbitrator::SuitePriorityArbitrator()
    : Suite("ThreadPriorityArbitrator")
    , iOpenHomeMin(1000)
    , iOpenHomeMax(0)
    , iHostRange(0)
    , iHostMax(0)
{
}

void SuitePriorityArbitrator::Test()
{
    // no arbitrators => requested priority delivered
    {
        ThreadPriorityArbitrator arb(1, 100);
        const TUint kPriority = 50;
        const TUint p = arb.CalculatePriority("foo", kPriority);
        TEST(p == kPriority);
    }

    // overlapping ranges asserts
    {
        ThreadPriorityArbitrator arb(1, 100);
        PriorityArbitratorDummy a1(90, 95, 5);
        arb.Add(a1);
        PriorityArbitratorDummy a2(90, 95, 5);
        TEST_THROWS(arb.Add(a2), AssertionFailed);
        PriorityArbitratorDummy a3(95, 100, 5);
        TEST_THROWS(arb.Add(a3), AssertionFailed);
        PriorityArbitratorDummy a4(80, 90, 5);
        TEST_THROWS(arb.Add(a4), AssertionFailed);
    }

    // gap between ranges asserts on Validate()
    {
        ThreadPriorityArbitrator arb(1, 50);
        PriorityArbitratorDummy a1(90, 95, 5);
        arb.Add(a1);
        TEST_THROWS(arb.Validate(), AssertionFailed);
        PriorityArbitratorDummy a2(96, 100, 1);
        arb.Add(a2);
        PriorityArbitratorDummy a3(1, 30, 10);
        arb.Add(a3);
        TEST_THROWS(arb.Validate(), AssertionFailed);
        PriorityArbitratorDummy a4(31, 89, 10);
        arb.Add(a4);
        arb.Validate();
    }

    // arbitrator or default called when appropriate
    {
        ThreadPriorityArbitrator arb(1, 30);
        PriorityArbitratorDummy a1(100, 100, 1);
        arb.Add(a1);
        iOpenHomeMin = 96;
        iOpenHomeMax = 99;
        iHostRange = 4;
        iHostMax = 29;
        arb.Add(*this); // covers next 4 OpenHome / Host priorities
        PriorityArbitratorDummy a3(85, 95, 5);
        arb.Add(a3);
        TEST_THROWS(arb.CalculatePriority("foo", 100), AssertionFailed);
        TUint i;
        for (i=85; i<=95; i++) {
            TEST_THROWS(arb.CalculatePriority("foo", i), AssertionFailed);
        }
        for (i=iOpenHomeMin; i<=iOpenHomeMax; i++) {
            TUint p = arb.CalculatePriority("foo", i);
            TEST(p == iHostMax - (iOpenHomeMax - i));
        }
        TEST(arb.CalculatePriority("foo", 1) == 1);
        TEST(arb.CalculatePriority("foo", 20) == 5);
    }
}

TUint SuitePriorityArbitrator::Priority(const TChar* /*aId*/, TUint aRequested, TUint aHostMax)
{
    return aHostMax - (iOpenHomeMax - aRequested);
}

TUint SuitePriorityArbitrator::OpenHomeMin() const
{
    return iOpenHomeMin;
}

TUint SuitePriorityArbitrator::OpenHomeMax() const
{
    return iOpenHomeMax;
}

TUint SuitePriorityArbitrator::HostRange() const
{
    return iHostRange;
}

class SuiteNotify : public Suite
{
public:
    SuiteNotify() : Suite("Thread::Notify{Wait,Signal}") {}
    void Test();
    void BodySignaller();
private:
    Thread* iSignalTargetThread;
};

void SuiteNotify::BodySignaller()
{
    Thread::Sleep(100);
    iSignalTargetThread->NotifySignal();
}

void SuiteNotify::Test()
{
    iSignalTargetThread = Thread::Current();
    ASSERT(iSignalTargetThread);
    ThreadFunctor signaller("sig", MakeFunctor(*this, &SuiteNotify::BodySignaller));
    signaller.Start();
    iSignalTargetThread->NotifyWait(); // ourselves
}

class MainTestThread : public Thread
{
public:
    MainTestThread(TBool aFull)
        : Thread("MAIN")
        , iFull(aFull)
    {}
    void Run();
private:
    TBool iFull;
};

void MainTestThread::Run()
{
    Runner runner("Threading System");
    runner.Add(new SuiteSemaphore());
    runner.Add(new SuiteMutex());
    runner.Add(new SuiteAutoMutex());
    runner.Add(new SuiteAutoSemaphore());
    runner.Add(new SuiteNotify());
    if (iFull) {
        runner.Add(new SuiteStartStop());
    }
    // Performance tests disabled as they cause intermittent failures for automated tests
    // (which run on servers with variable loads)
    //runner.Add(new SuitePerformance());
    runner.Add(new SuiteThreadKill());
    runner.Add(new SuiteThreadNotStarted());
    if (iFull) {
        runner.Add(new SuiteThreadStartDelete());
    }
    runner.Add(new SuiteThreadFunctor());
    runner.Add(new SuiteThreadFunctorNotStarted());
    if (iFull) {
        runner.Add(new SuiteThreadFunctorStartDelete());
    }
    runner.Add(new SuitePriorityArbitrator());
    if (OpenHome::Thread::SupportsPriorities())
    {
        runner.Add(new SuitePriority());
        runner.Add(new SuiteTimeslice());
    }
    runner.Run();

    Signal();
}

void TestThread(const std::vector<Brn>& aArgs)
{
    OptionParser parser;
    OptionBool full("-f", "--full", "Run full (slow) set of test cases");
    parser.AddOption(&full);
    if (!parser.Parse(aArgs, true) || parser.HelpDisplayed()) {
        return;
    }

    gTestStack = new TestStack();
    Thread* th = new MainTestThread(full.Value());
    th->Start();
    th->Wait();
    delete th;
    delete gTestStack;
}
