#include <TestFramework.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <Thread.h>
#include <Printer.h>
#include <Os.h>
#include <Zapp.h>
#include <Debug.h>

#include <stdlib.h>

using namespace Zapp;
using namespace Zapp::TestFramework;

TUint gFail;
TUint gPass;
const TChar* gLastSuccessfulFile;
TUint gLastSuccessfulLine;

class TestConsole
{
public:
    void Log(const char* aMsg);
};

void TestConsole::Log(const char* aMsg)
{
    Os::ConsoleWrite(aMsg);
}


// AssertHandler

void Zapp::TestFramework::AssertHandlerTest(const TChar* aFile, TUint aLine)
{
    THROW_WITH_FILE_LINE(AssertionFailed, aFile, aLine);
}

// Suite

Suite::Suite(const TChar* aDesc) : iNext(0), iDesc(aDesc)
{
}

Suite::~Suite()
{
}

const TChar* Suite::Description() const
{
    return iDesc;
}


// Runner

Runner::Runner(const TChar* aDesc) : iFirst(0), iLast(0), iDesc(aDesc)
{
}

Runner::~Runner()
{
}

void Runner::Add(Suite* aSuite)
{
    if(iFirst == 0) {
        iFirst = aSuite;
        iLast = aSuite;
    } else {
        assert(iLast->iNext == 0);
        iLast->iNext = aSuite;
        aSuite->iNext = 0;
        iLast = aSuite;
    }
}

void Runner::Run()
{
    Print("Starting Test Runner: %s\n", iDesc);
    SetAssertHandler(AssertHandlerTest);
    gPass = 0;
    gFail = 0;

    Suite* suite = iFirst;
    TUint i=1;
    for(; suite != 0; i++) {
        Print("Suite %d: %s\n", i,suite->Description());
        try {
            suite->Test();
        } catch(Zapp::Exception& e) {
            Print("\nFAILURE: Suite: %d caused an unhandled exception: %s.  Exception thrown at:  File: %s.  Line: %d\n",i,e.Message(),e.File(),e.Line());
            Print("Last successful test: %s:%d\n", gLastSuccessfulFile, gLastSuccessfulLine);
            gFail++;
        } catch(...) {
            Print("\nFAILURE: Suite: %d caused an unhandled, unknown exception\n", i);
            Print("Last successful test: %s:%d\n", gLastSuccessfulFile, gLastSuccessfulLine);
            gFail++;
        }
        Print("\n");

        Suite* finishedSuite = suite;
        suite = suite->iNext;
        delete finishedSuite;
    }
    Print("Finished Test Runner: %s\n", iDesc);
    Print("%d of %d tests passed.\n",gPass, gPass+gFail);
    Print("%d of %d tests failed.\n",gFail, gPass+gFail);
    if (gFail != 0) {
        const char* a = getenv("ABORT_ON_FAILURE");
        if (a != NULL && atoi(a) == 1) {
            abort();
        }
    }
}

void Zapp::TestFramework::Fail(const TChar* aFile, TUint aLine,
    const TChar* /*aExp*/, const TChar* aMsg)
{
    gFail++;
    Print("\nFAILURE: %s:%d\n", aFile, aLine);
    if(aMsg) {
        Print(" -- %s", aMsg);
    }
    Print("\n");
}

void Zapp::TestFramework::Succeed(const TChar* aFile, TUint aLine)
{
    SucceedQuietly( aFile, aLine );
    Print(".");
}

void Zapp::TestFramework::SucceedQuietly(const TChar* aFile, TUint aLine)
{
    gPass++;
    gLastSuccessfulFile = aFile;
    gLastSuccessfulLine = aLine;
    // No printing output!
}



TUint Zapp::TestFramework::TimeStart()
{
    return Zapp::Os::TimeInMs();
}

TUint Zapp::TestFramework::TimeStop(TUint aStartTime)
{
    TUint time = Zapp::Os::TimeInMs();
    return time - aStartTime;
}

TInt Zapp::TestFramework::Print(const TChar* aFormat, ...)
{
    TestConsole console;
    FunctorMsg functor = MakeFunctorMsg(console, &TestConsole::Log);
    va_list args;
    va_start(args, aFormat);
    TInt n = Log::Print(functor, aFormat, args);
    va_end(args);
    return n;
}

TInt Zapp::TestFramework::Print(const TChar* aFormat, va_list aArgs)
{
    TestConsole console;
    FunctorMsg functor = MakeFunctorMsg(console, &TestConsole::Log);
    return Log::Print(functor, aFormat, aArgs);
}

TInt Zapp::TestFramework::Print(const Brx& aB)
{
    TestConsole console;
    FunctorMsg functor = MakeFunctorMsg(console, &TestConsole::Log);
    return Log::Print(functor, aB);
}

TInt Zapp::TestFramework::PrintHex(const Brx& aB)
{
    TestConsole console;
    FunctorMsg functor = MakeFunctorMsg(console, &TestConsole::Log);
    return Log::PrintHex(functor, aB);
}


// Blocker

Blocker::Blocker()
    : iSem("SBLK", 0)
{
    iTimer = new Timer(MakeFunctor(*this, &Blocker::TimerExpired));
}

Blocker::~Blocker()
{
    delete iTimer;
}

void Blocker::Wait(TUint aSecs)
{
    iTimer->FireIn(aSecs * 1000);
    iSem.Wait();
}

void Blocker::TimerExpired()
{
    iSem.Signal();
}
