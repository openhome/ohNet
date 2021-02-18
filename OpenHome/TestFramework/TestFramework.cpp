#include <OpenHome/Private/TestFramework.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/NetworkAdapterList.h>

#include <time.h>
#include <stdlib.h>
#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

TUint gFail;
TUint gPass;
const TChar* gLastSuccessfulFile;
TUint gLastSuccessfulLine;

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
    SetAssertThrows(true);
    gPass = 0;
    gFail = 0;

    Suite* suite = iFirst;
    TUint i=1;
    for(; suite != 0; i++) {
        Print("Suite %d: %s\n", i,suite->Description());
        try {
            suite->Test();
        } catch(OpenHome::Exception& e) {
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
        if ( a == NULL || atoi(a) == 1 ) {
            // If env var is unset, or is set to "1", then exit.
            exit(1);
        }
    }
}

void OpenHome::TestFramework::Fail(const TChar* aFile, TUint aLine,
    const TChar* /*aExp*/, const TChar* aMsg)
{
    gFail++;
    Print("\nFAILURE: %s:%d\n", aFile, aLine);
    if(aMsg) {
        Print(" -- %s", aMsg);
    }
    Print("\n");
}

void OpenHome::TestFramework::Succeed(const TChar* aFile, TUint aLine)
{
    SucceedQuietly( aFile, aLine );
    Print(".");
}

void OpenHome::TestFramework::SucceedQuietly(const TChar* aFile, TUint aLine)
{
    gPass++;
    gLastSuccessfulFile = aFile;
    gLastSuccessfulLine = aLine;
    // No printing output!
}



TUint OpenHome::TestFramework::TimeStart()
{
    return OpenHome::Os::TimeInMs(gEnv->OsCtx());
}

TUint OpenHome::TestFramework::TimeStop(TUint aStartTime)
{
    TUint time = OpenHome::Os::TimeInMs(gEnv->OsCtx());
    return time - aStartTime;
}

void STDCALL defaultPrinter(void* /*aPtr*/, const char* aMsg)
{
    Os::ConsoleWrite(aMsg);
}

static FunctorMsg gPrinter = MakeFunctorMsgC(NULL, defaultPrinter);

void OpenHome::TestFramework::SetPrinter(FunctorMsg& aPrinter)
{
    gPrinter = aPrinter;
}

TInt OpenHome::TestFramework::Print(const TChar* aFormat, ...)
{
    va_list args;
    va_start(args, aFormat);
    TInt n = Log::Print(gPrinter, aFormat, args);
    va_end(args);
    return n;
}

TInt OpenHome::TestFramework::Print(const TChar* aFormat, va_list aArgs)
{
    return Log::Print(gPrinter, aFormat, aArgs);
}

TInt OpenHome::TestFramework::Print(const Brx& aB)
{
    return Log::Print(gPrinter, aB);
}

TInt OpenHome::TestFramework::PrintHex(const Brx& aB)
{
    return Log::PrintHex(gPrinter, aB);
}


void OpenHome::TestFramework::RandomiseUdn(Environment& aEnv, Bwh& aUdn)
{
    aUdn.Grow(aUdn.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1);
    aUdn.Append('-');
    Bws<Ascii::kMaxUintStringBytes> buf;
    std::vector<NetworkAdapter*>* subnetList = aEnv.NetworkAdapterList().CreateSubnetList();
    TUint max = UINT_MAX;
    if ((subnetList->size() > 0) &&
        ((*subnetList)[0]->Address().family == kFamilyV4)) {
        max = (*subnetList)[0]->Address().v4;
    }
    aEnv.NetworkAdapterList().DestroySubnetList(subnetList);
    (void)Ascii::AppendDec(buf, aEnv.Random(max));
    aUdn.Append(buf);
    aUdn.PtrZ();
}


// Blocker

Blocker::Blocker(Environment& aEnv)
    : iSem("SBLK", 0)
{
    iTimer = new Timer(aEnv, MakeFunctor(*this, &Blocker::TimerExpired), "Blocker");
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
