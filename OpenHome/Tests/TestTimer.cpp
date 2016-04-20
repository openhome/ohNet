#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Env.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

#ifdef _WIN32
# pragma warning(disable:4355) // use of 'this' in ctor lists safe in this case
#endif

class MyTimer : public Timer
{
public:
    MyTimer(Environment& aEnv) : Timer(aEnv, MakeFunctor(*this, &MyTimer::Run), "MyTimer"), iCount(0), iSemaphore("TIMR", 0) {}
    void Wait() { iSemaphore.Wait(); }
    TUint Count() { return (iCount); }
    ~MyTimer() { iCount = 0xffffffff; }
private:
    void Run() { iCount++; ASSERT(iCount); iSemaphore.Signal(); }
private:
    TUint iCount;
    Semaphore iSemaphore;
};

class MicrosecondTimer
{
public:
    MicrosecondTimer(Environment& aEnv) : iTimer(aEnv, MakeFunctor(*this, &MicrosecondTimer::Expired), "MicrosecondTimer"), iSemaphore("MICR", 0) {}
    void Calibrate();
    void FireIn(TUint aMicroseconds);
private:
    void Expired();
private:
    TUint64 iCount;
    Timer iTimer;
    TBool iExpired;
    Semaphore iSemaphore;
};

void MicrosecondTimer::FireIn(TUint aMicroseconds)
{
    TUint64 value = iCount * aMicroseconds / 100000;
    while(value--);
}

void MicrosecondTimer::Calibrate()
{
    iCount = 0;

    Expired();
    
    iExpired = false;
    
    while(!iExpired) {
    }
    
    iExpired = false;

    while(!iExpired) {
        iCount++;
    }

    iTimer.Cancel();
}

void MicrosecondTimer::Expired()
{
    iExpired = true;
    iTimer.FireIn(100);
}

class SuiteTimerBasic : public Suite, private INonCopyable
{
public:
    SuiteTimerBasic(Environment& aEnv) : Suite("Basic Timer testing"), iEnv(aEnv) {}
    void Test();
private:
    Environment& iEnv;
};

void SuiteTimerBasic::Test()
{
    MyTimer a(iEnv);

    TUint i=0;
    for( ; i < 100; i++ ) {
        a.FireIn(300);
        Thread::Sleep(iEnv.Random(30, 10));
        Print(".");
    }
#if 0
    a.Wait();
    TUint count0 = a.Count();

    Thread::Sleep(3000);

    TUint count1 = a.Count();

    TEST(count0 == count1);

    for( i=0; i < 100; i++ ) {
        a.FireIn(300);
        TUint j = iEnv.Random(3500, 2500);
        TUint k=0;
        for( ; k < j; k++) {
            Print("."); 
        }
    }

    a.Wait();

    Thread::Sleep(3000);

    MyTimer b(iEnv);
    
    Print("\nWait for 5 seconds\n");
    a.FireIn(5000);
    a.Wait();
    Print("Wait finished\n");
    
    Print("Wait for 3 seconds then a further 2 seconds\n");
    a.FireIn(5000);
    b.FireIn(3000);
    b.Wait();
    Print("Wait finished 1\n");
    a.Wait();
    Print("Wait finished 2\n");

    for (TUint j = 1; j < 21; j++) {
        Print("Wait for 1 second then a further %d millisecond\n", j);
        a.FireIn(1000);
        b.FireIn(1000 + j);
        a.Wait();
        Print("Wait finished 1\n");
        b.Wait();
        Print("Wait finished 2\n");
    }
    
    Print("Wait for 0 seconds\n");
    a.FireIn(0);
    a.Wait();
    Print("Wait finished\n");

    Print("Cancel a timer\n");
    
    MyTimer c(iEnv);
    
    a.FireIn(1000);
    c.FireIn(2000);
    b.FireIn(3000);
    a.Wait();
    Print("Wait finished 1\n");
    TEST(c.Count() == 0);
    c.Cancel();
    b.Wait();
    Print("Wait finished 2\n");
    TEST(c.Count() == 0);
    
    Print("Delete a timer\n");
    
    MyTimer* d = new MyTimer(iEnv);
    
    a.FireIn(1000);
    d->FireIn(2000);
    b.FireIn(3000);
    a.Wait();
    Print("Wait finished 1\n");
    TEST(d->Count() == 0);
    delete d;
    b.Wait();
    Print("Wait finished 2\n");

    Print("Change a timer\n");
    
    // Replaced 'a' with a new timer 'a2', as this code
    // assumes the MyTimer sema count is 0. Not guaranteed though :(
    MyTimer a2(iEnv);
    MyTimer e(iEnv);
    
    a2.FireIn(1000);
    e.FireIn(2000);
    b.FireIn(3000);
    a2.Wait();
    Print("Wait finished 1\n");
    TEST(e.Count() == 0);
    e.FireIn(3000);
    b.Wait();
    Print("Wait finished 2\n");
    TEST(e.Count() == 0);
    e.Wait();
    Print("Wait finished 3\n");
    TEST(e.Count() == 1);
#endif
}


class SuiteTimerThrash : public Suite, private INonCopyable
{
public:
    SuiteTimerThrash(Environment& aEnv) : Suite("Thrash Timer testing"), iEnv(aEnv) {}
    void Fire() { iCount++; }
    void Test();
private:
    Environment& iEnv;
    TUint iCount;
    Timer* iTimers[10000];
};

void SuiteTimerThrash::Test()
{
    Functor f = MakeFunctor(*this, &SuiteTimerThrash::Fire);
    
    for (TUint i = 0; i < 10000; i++) {
        iTimers[i] = new Timer(iEnv, f, "SuiteTimerThrash");
    }
    
    Print("Firing 10000 timers over 10 seconds\n");
    
    iCount = 0;
    
    for (TUint i = 0; i < 10000; i++) {
        iTimers[i]->FireIn(iEnv.Random(10000)); // fire 10000 timers in the following 10 seconds
    }
    
    Thread::Sleep(11000);   // wait 11 seconds 

    TEST(iCount == 10000);  // ensure all 10000 timers did fire
    
    for (TUint i = 0; i < 10000; i++) {
        delete (iTimers[i]);
    }
}

class TimerTestThread : public Thread
{
public:
    TimerTestThread(Environment& aEnv);
    void Run();
private:
    Environment& iEnv;
};

TimerTestThread::TimerTestThread(Environment& aEnv)
    : Thread("MAIN", kPriorityNormal)
    , iEnv(aEnv)
{
}

void TimerTestThread::Run()
{
    //Debug::SetLevel(Debug::kTimer);
    Runner runner("Timer testing\n");
    runner.Add(new SuiteTimerBasic(iEnv));
    runner.Add(new SuiteTimerThrash(iEnv));
    runner.Run();
    Signal();
}

void TestTimer(Environment& aEnv)
{
    Thread* th = new TimerTestThread(aEnv);
    th->Start();
    th->Wait();
    delete th;
}
