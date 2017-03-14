#include <OpenHome/Tests/TestPipe.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Test;


// TestPipeDynamic

TestPipeDynamic::TestPipeDynamic(TUint aSlots)
    : iFifo(aSlots)
    , iLock("TPDL")
{
}

TestPipeDynamic::~TestPipeDynamic()
{
    AutoMutex a(iLock);
    while (iFifo.SlotsUsed() > 0) {
        Bwh* buf = iFifo.Read();
        delete buf;
    }
}

void TestPipeDynamic::Print()
{
    AutoMutex a(iLock);
    const TUint slots = iFifo.SlotsUsed();
    Log::Print("\nTestPipeDynamic::Print\n");
    Log::Print("[\n");
    for (TUint i=0; i<slots; i++) {
        Bwh* buf = iFifo.Read();
        Log::Print("\t");
        Log::Print(*buf);
        Log::Print("\n");
        iFifo.Write(buf);
    }
    Log::Print("]\n");
}

void TestPipeDynamic::Write(const Brx& aMessage)
{
    AutoMutex a(iLock);
    Bwh* buf = new Bwh(aMessage);
    iFifo.Write(buf);
}

TBool TestPipeDynamic::Expect(const Brx& aMessage)
{
    AutoMutex a(iLock);
    if (iFifo.SlotsUsed() > 0) {
        Bwh* buf = iFifo.Read();
        const TBool match = (*buf == aMessage);
        if (!match) {
            Log::Print("TestPipeDynamic::Expect ERROR. expected: ");
            Log::Print(aMessage);
            Log::Print(" got: ");
            Log::Print(*buf);
            Log::Print("\n");
        }
        delete buf;
        return match;
    }
    Log::Print("TestPipeDynamic::Expect ERROR. msg list empty; expected: ");
    Log::Print(aMessage);
    Log::Print("\n");
    return false;
}

TBool TestPipeDynamic::ExpectEmpty()
{
    AutoMutex a(iLock);
    const TUint msgs = iFifo.SlotsUsed();
    if (msgs > 0) {
        Log::Print("TestPipeDynamic::ExpectEmpty ERROR. %u msgs remaining:\n", msgs);
        for (TUint i=0; i<iFifo.SlotsUsed(); i++) {
            Bwh* buf = iFifo.Read();
            Log::Print("\t");
            Log::Print(*buf);
            Log::Print("\n");
            iFifo.Write(buf);
        }
        return false;
    }
    return true;
}
