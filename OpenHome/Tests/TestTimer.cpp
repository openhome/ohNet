#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Net/Private/Globals.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

#ifdef _WIN32
# pragma warning(disable:4355) // use of 'this' in ctor lists safe in this case
#endif

class MyTimer : public Timer
{
public:
    MyTimer() : Timer(*gEnv, MakeFunctor(*this, &MyTimer::Run)), iCount(0), iSemaphore("TIMR", 0) {}
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
    MicrosecondTimer() : iTimer(*gEnv, MakeFunctor(*this, &MicrosecondTimer::Expired)), iSemaphore("MICR", 0) {}
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

class SuiteTimerBasic : public Suite
{
public:
    SuiteTimerBasic() : Suite("Basic Timer testing") {}
    void Test();
};

void SuiteTimerBasic::Test()
{
    MyTimer a;

    TUint i=0;
    for( ; i < 1000; i++ ) {
        a.FireIn(300);
        Thread::Sleep(Random(30, 10));
        Print(".");
    }

    a.Wait();
    TUint count0 = a.Count();

    Thread::Sleep(3000);

    TUint count1 = a.Count();

    TEST(count0 == count1);

    for( i=0; i < 100; i++ ) {
        a.FireIn(300);
        TUint j = Random(3500, 2500);
        TUint k=0;
        for( ; k < j; k++) {
            Print("."); 
        }
    }

    a.Wait();

    Thread::Sleep(3000);

    MyTimer b;
    
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

    for (TUint i = 1; i < 21; i++) {
        Print("Wait for 1 second then a further %d millisecond\n", i);
        a.FireIn(1000);
        b.FireIn(1000 + i);
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
    
    MyTimer c;
    
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
    
    MyTimer* d = new MyTimer();
    
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
    
    MyTimer e;
    
    a.FireIn(1000);
    e.FireIn(2000);
    b.FireIn(3000);
    a.Wait();
    Print("Wait finished 1\n");
    TEST(e.Count() == 0);
    e.FireIn(3000);
    b.Wait();
    Print("Wait finished 2\n");
    TEST(e.Count() == 0);
    e.Wait();
    Print("Wait finished 3\n");
    TEST(e.Count() == 1);
}


class SuiteTimerThrash : public Suite
{
public:
    SuiteTimerThrash() : Suite("Thrash Timer testing") {}
    void Fire() { iCount++; }
    void Test();
private:
    TUint iCount;
    Timer* iTimers[10000];
};

void SuiteTimerThrash::Test()
{
    Functor f = MakeFunctor(*this, &SuiteTimerThrash::Fire);
    
    for (TUint i = 0; i < 10000; i++) {
        iTimers[i] = new Timer(*gEnv, f);
    }
    
    Print("Firing 10000 timers over 10 seconds\n");
    
    iCount = 0;
    
    for (TUint i = 0; i < 10000; i++) {
        iTimers[i]->FireIn(Random(10000)); // fire 10000 timers in the following 10 seconds
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
    TimerTestThread();
    void Run();
};

TimerTestThread::TimerTestThread()
    : Thread("MAIN", kPriorityNormal)
{
}

void TimerTestThread::Run()
{
    //Debug::SetLevel(Debug::kTimer);
    Runner runner("Timer testing\n");
    runner.Add(new SuiteTimerBasic());
    runner.Add(new SuiteTimerThrash());
    runner.Run();
    Signal();
}

void TestTimer()
{
    Thread* th = new TimerTestThread();
    th->Start();
    th->Wait();
    delete th;
}
