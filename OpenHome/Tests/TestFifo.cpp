#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Thread.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

class I
{
public:
    I(TUint aValue) : iValue(aValue) {}
    TUint Value() const {return iValue;}
    TBool operator==(const I* aI) {return (aI->Value() == Value());}
private:
    TUint iValue;
};

I i1(1);
I i2(2);
I i3(3);
I i4(4);

class SuiteFifoBasic : public Suite
{
public:
    SuiteFifoBasic() : Suite("Single threaded basic Fifo testing") {}
    void Test();
};


void SuiteFifoBasic::Test()
{
    Fifo<I*> q(4);
    TEST(q.Slots() == 4);
    TEST(q.SlotsUsed() == 0);
    TEST(q.SlotsFree() == 4);

    //iWriteIndex >= iReadIndex
    q.Write(&i1);
    TEST(q.Slots() == 4);
    TEST(q.SlotsUsed() == 1);
    TEST(q.SlotsFree() == 3);
    q.Write(&i2);
    TEST(q.SlotsUsed() == 2);
    TEST(q.SlotsFree() == 2);

    TEST(q.Read() == &i1);
    TEST(q.SlotsUsed() == 1);
    TEST(q.Read() == &i2);
    TEST(q.SlotsUsed() == 0);
    TEST(q.SlotsFree() == 4);

    q.Write(&i1);
    q.Write(&i2);
    q.Write(&i3);
    q.Write(&i4);
    TEST(q.SlotsUsed() == 4);

    TEST(q.Read() == &i1);
    TEST(q.Read() == &i2);
    TEST(q.Read() == &i3);
    TEST(q.SlotsUsed() == 1);
    TEST(q.SlotsFree() == 3);

    //iWriteIndex < iReadIndex
    q.Write(&i1);
    q.Write(&i2);
    q.Write(&i3);
    TEST(q.SlotsUsed() == 4);
    TEST(q.SlotsFree() == 0);

    TEST(q.Read() == &i4);
    TEST(q.Read() == &i1);
    TEST(q.Read() == &i2);
    TEST(q.Read() == &i3);
    TEST(q.SlotsUsed() == 0);
    TEST(q.SlotsFree() == 4);
}

typedef Fifo<I*> FifoTest;

class Reader : public INonCopyable
{
public:
    Reader(FifoTest& aFifo, Thread& aCaller, TUint aIter)
        : iFifo(aFifo), iCaller(aCaller), iIter(aIter) {}
    void Run();
private:
    FifoTest& iFifo;
    Thread& iCaller;
    TUint iIter;
};

void Reader::Run()
{
    ASSERT(iIter < 1000000);
    TUint i=0;
    TUint exp1 = 1;
    TUint exp2 = 1000000;
    for(; i < iIter; i++) {
        I* read = iFifo.Read();
        ASSERT(read != NULL);
        TUint value = read->Value();
        delete read;
        if(value == exp1) {
            TEST(1);
            exp1++;
        }
        else if(value == exp2) {
            TEST(1);
            exp2++;
        }
        else {
            TEST(0);
            Print("Expected: %d or %d\n", exp1, exp2);
        }
    }
    iCaller.Signal();
}

class Writer0 : public INonCopyable
{
public:
    Writer0(FifoTest& aFifo, Thread& aCaller, TUint aIter)
        : iFifo(aFifo), iCaller(aCaller), iIter(aIter) {}
    void Run();
private:
    FifoTest& iFifo;
    Thread& iCaller;
    TUint iIter;
};

void Writer0::Run()
{
    TUint j=0;
    TUint next = 1;
    for(; j < iIter; j++) {
        I* i = new I(next);
        iFifo.Write(i);
        next++;
    }
    iCaller.Signal();
}

class Writer1 : public INonCopyable
{
public:
    Writer1(FifoTest& aFifo, Thread& aCaller, TUint aIter)
        : iFifo(aFifo), iCaller(aCaller), iIter(aIter) {}
    void Run();
private:
    FifoTest& iFifo;
    Thread& iCaller;
    TUint iIter;
};

void Writer1::Run()
{
    TUint j=0;
    TUint next = 1000000;
    for(; j < iIter; j++) {
        I* i = new I(next);
        iFifo.Write(i);
        next++;
    }
    iCaller.Signal();
}

void MultipleWriteTest(Thread& aCurrentThread, TUint aRPriority, TUint aW0Priority, TUint aW1Priority)
{
    const TUint writer0Iters = 300;
    const TUint writer1Iters = 500;
    FifoTest q(32);
    Writer0 writer0(q, aCurrentThread,  writer0Iters);
    Functor fWriter0 = MakeFunctor(writer0, &Writer0::Run);
    Writer1 writer1(q, aCurrentThread, writer1Iters);
    Functor fWriter1 = MakeFunctor(writer1, &Writer1::Run);
    Reader reader(q, aCurrentThread, writer0Iters + writer1Iters);
    Functor fReader = MakeFunctor(reader, &Reader::Run);

    ThreadFunctor* tReader0 = new ThreadFunctor("TSTA", fReader, aRPriority);
    ThreadFunctor* tWriter0 = new ThreadFunctor("TSTB", fWriter0, aW0Priority);
    ThreadFunctor* tWriter1 = new ThreadFunctor("TSTC", fWriter1, aW1Priority);
    tReader0->Start();
    tWriter0->Start();
    tWriter1->Start();

    aCurrentThread.Wait();
    aCurrentThread.Wait();
    aCurrentThread.Wait();

    // The worker threads should be ready to remove.
    delete tReader0;
    delete tWriter0;
    delete tWriter1;
}

class SuiteFifoThreadSafety : public Suite
{
public:
    SuiteFifoThreadSafety() : Suite("Fifo thread safety multiple writers, 1 reader") {}
    void Test();
};

class ThreadSafetyTests : public Thread
{
public:
    ThreadSafetyTests(Semaphore& aSem) : Thread("THST"), iSem(aSem) {}
    void Run();
private:
    Semaphore& iSem;
};

void ThreadSafetyTests::Run()
{
    Print("\n\nTestA\n\n");
    MultipleWriteTest(*this, kPriorityNormal, kPriorityNormal, kPriorityNormal);
    Print("\n\nTestB\n\n");
    MultipleWriteTest(*this, kPriorityNormal, kPriorityLow, kPriorityHigh);
    Print("\n\nTestC\n\n");
    MultipleWriteTest(*this, kPriorityNormal, kPriorityHigh, kPriorityLow);
    Print("\n\nTestD\n\n");
    MultipleWriteTest(*this, kPriorityLow, kPriorityNormal, kPriorityNormal);
    Print("\n\nTestE\n\n");
    MultipleWriteTest(*this, kPriorityLow, kPriorityNormal, kPriorityHigh);
    Print("\n\nTestF\n\n");
    MultipleWriteTest(*this, kPriorityLow, kPriorityHigh, kPriorityNormal);
    Print("\n\nTestG\n\n");
    MultipleWriteTest(*this, kPriorityHigh, kPriorityNormal, kPriorityNormal);
    Print("\n\nTestH\n\n");
    MultipleWriteTest(*this, kPriorityHigh, kPriorityLow, kPriorityNormal);
    Print("\n\nTestI\n\n");
    MultipleWriteTest(*this, kPriorityHigh, kPriorityNormal, kPriorityLow);

    iSem.Signal();
}

void SuiteFifoThreadSafety::Test()
{
    Semaphore s("SFTS", 0);
    ThreadSafetyTests* th = new ThreadSafetyTests(s);
    th->Start();
    s.Wait();
    delete th;
}

class SuiteFifoInterrupt : public Suite
{
public:
    SuiteFifoInterrupt();
    void Test();
private:
    void RunWriter();
private:
    static const TUint kSleepMs = 5;
    // this must be > #items so a cancelled interrupt can be tested after
    // removing all elems from fifo without fifo wrapping round
    static const TUint kMaxQueueSize = 8;
    Fifo<I*> iQueue;
    Semaphore iSemWrite;
    Semaphore iSemRead;
};

SuiteFifoInterrupt::SuiteFifoInterrupt()
    : Suite("SuiteFifoInterrupt")
    , iQueue(kMaxQueueSize)
    , iSemWrite("SFIW", 0)
    , iSemRead("SFIR", 0)
{
}

void SuiteFifoInterrupt::Test()
{
    // test read interrupt cancellation pattern (i.e., ReadInterrupt(true); ReadInterrupt(false))

    ThreadFunctor tWriter("TFIW", MakeFunctor(*this, &SuiteFifoInterrupt::RunWriter));
    tWriter.Start();

    // test calling and cancelling interrupt before anything in queue
    iQueue.ReadInterrupt(true);
    iQueue.ReadInterrupt(false);
    // there is a race condition after this between the reader and the writer;
    // this is easiest way to set up test; to get somewhat reliable behaviour
    // set kSleepMs to a high enough value that allows reader opportunity to
    // read before writer writes
    iSemWrite.Signal();
    I* val = iQueue.Read();
    TEST(val == &i1);

    // test calling and cancelling interrupt before then emptying queue and trying to read
    iSemRead.Wait();
    iQueue.ReadInterrupt(true);
    iQueue.ReadInterrupt(false);
    while (iQueue.SlotsUsed() > 0) {
        iQueue.Read();
    }
    iSemWrite.Signal();
    val = iQueue.Read();
    TEST(val == &i1);

    // test that a normal interrupt works as expected
    iSemRead.Wait();
    iQueue.ReadInterrupt(true);
    TEST_THROWS(iQueue.Read(), FifoReadError);

    // test that a read after a normal interrupt works
    val = iQueue.Read();
    TEST(val == &i2);

    // test shutdown: mark tWriter as killed, then unblock it.
    tWriter.Kill();
    iSemWrite.Signal();
}

void SuiteFifoInterrupt::RunWriter()
{
    // wait on a semaphore before starting to write data into a queue
    while (true) {
        iSemWrite.Wait();
        Thread::CheckCurrentForKill();
        Thread::Sleep(kSleepMs);
        iQueue.Write(&i1);
        iQueue.Write(&i2);
        iQueue.Write(&i3);
        iQueue.Write(&i4);
        iSemRead.Signal();
    }
}

class SuiteFifoLiteBasic : public Suite
{
public:
    SuiteFifoLiteBasic() : Suite("FifoLite testing") {}
    void Test();
};


void SuiteFifoLiteBasic::Test()
{
    FifoLite<I*, 4> q;
    TEST(q.Slots() == 4);
    TEST(q.SlotsUsed() == 0);
    TEST(q.SlotsFree() == 4);
    
    //iWriteIndex >= iReadIndex
    q.Write(&i1);
    TEST(q.Slots() == 4);
    TEST(q.SlotsUsed() == 1);
    TEST(q.SlotsFree() == 3);
    q.Write(&i2);
    TEST(q.SlotsUsed() == 2);
    TEST(q.SlotsFree() == 2);

    TEST(q.Read() == &i1);
    TEST(q.SlotsUsed() == 1);
    TEST(q.Read() == &i2);
    TEST(q.SlotsUsed() == 0);
    TEST(q.SlotsFree() == 4);

    q.Write(&i1);
    q.Write(&i2);
    q.Write(&i3);
    q.Write(&i4);
    TEST(q.SlotsUsed() == 4);

    TEST(q.Read() == &i1);
    TEST(q.Read() == &i2);
    TEST(q.Read() == &i3);
    TEST(q.SlotsUsed() == 1);
    TEST(q.SlotsFree() == 3);

    //iWriteIndex < iReadIndex
    q.Write(&i1);
    q.Write(&i2);
    q.Write(&i3);
    TEST(q.SlotsUsed() == 4);
    TEST(q.SlotsFree() == 0);

    TEST(q.Read() == &i4);
    TEST(q.Read() == &i1);
    TEST(q.Read() == &i2);
    TEST(q.Read() == &i3);
    TEST(q.SlotsUsed() == 0);
    TEST(q.SlotsFree() == 4);

    FifoLite<I*, 1> q1;
    TEST(q1.Slots() == 1);
    TEST(q1.SlotsUsed() == 0);
    TEST(q1.SlotsFree() == 1);
    
    q1.Write(&i1);
    TEST(q1.Slots() == 1);
    TEST(q1.SlotsUsed() == 1);
    TEST(q1.SlotsFree() == 0);

    TEST(q1.Read() == &i1);
    TEST(q1.SlotsUsed() == 0);

    q1.Write(&i2);
    TEST(q1.SlotsUsed() == 1);
    TEST(q1.Read() == &i2);
    TEST(q1.SlotsUsed() == 0);
}

void TestFifo()
{
    Debug::SetLevel(Debug::kNone);

    Runner runner("FifoS testing\n");
    runner.Add(new SuiteFifoBasic());
    runner.Add(new SuiteFifoThreadSafety());
    runner.Add(new SuiteFifoInterrupt());
    runner.Add(new SuiteFifoLiteBasic());
    runner.Run();
}
