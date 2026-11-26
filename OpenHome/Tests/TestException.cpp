#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/TestFramework.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

/* Set by Runner::Main before the library is initialised - see TestExceptionMain.cpp.
   Reported from a suite because Runner::Run() zeroes the pass/fail counters. */
TBool gThrewWithNoEnv = false;

class SuiteNoEnv : public Suite
{
public:
    SuiteNoEnv() : Suite("Exception outside the library lifetime") {}
    void Test();
};

void SuiteNoEnv::Test()
{
    /* gEnv is NULL before Initialise() and again after Close(), and the Exception
       ctor used to dereference it unconditionally.  Reaching this line at all
       means the probe in Runner::Main did not segfault; the flag confirms the
       exception was also thrown and caught normally. */
    TEST(gThrewWithNoEnv);
}

class SuiteThreadSafety : public Suite
{
public:
    SuiteThreadSafety();
    void Test();
private:
    void ThreadWork();
};

SuiteThreadSafety::SuiteThreadSafety()
: Suite("Exception threadsafety test")
{}

void SuiteThreadSafety::ThreadWork()
{
    for(;;)
    {
        Thread::CheckCurrentForKill();

        for ( TUint counter = 0 ; counter < 2000 ; ++counter )
        {
            try {
                throw Thread::Current();
            }
            catch ( Thread* throwThread )
            {
                Thread* currentThread = Thread::Current();
                if ( throwThread != currentThread )
                    TEST(false);
            }
        }
    }
}

void SuiteThreadSafety::Test()
{
    Functor workFunctor = MakeFunctor(*this, &SuiteThreadSafety::ThreadWork);

    ThreadFunctor t1("w1", workFunctor);
    ThreadFunctor t2("w2", workFunctor);
    ThreadFunctor t3("w3", workFunctor);
    ThreadFunctor t4("w4", workFunctor);
    t1.Start();
    t2.Start();
    t3.Start();
    t4.Start();

    for ( TUint soakSeconds = 5 ; soakSeconds > 0 ; --soakSeconds )
    {
        Print("%d\n", soakSeconds);
        Thread::Sleep(1000);
    }
}

void TestException()
{
    Runner runner("Binary Buffer Testing");
    runner.Add(new SuiteNoEnv());
    runner.Add(new SuiteThreadSafety());
    runner.Run();
}

