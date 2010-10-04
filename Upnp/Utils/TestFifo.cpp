#include <TestFramework.h>
#include <Fifo.h>
#include <Thread.h>

using namespace Zapp;
using namespace Zapp::TestFramework;

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
    TEST_THROWS(q.Read(50), Timeout);
    TEST(q.SlotsFree() == 4);

    q.Write(&i1);
    q.Write(&i2);
    q.Write(&i3);
    q.Write(&i4);
    TEST(q.SlotsUsed() == 4);
    TEST_THROWS(q.Write(&i1, 100), Timeout);

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
    TEST_THROWS(q.Write(&i1, 100), Timeout);

    TEST(q.Read() == &i4);
    TEST(q.Read() == &i1);
    TEST(q.Read() == &i2);
    TEST(q.Read() == &i3);
    TEST(q.SlotsUsed() == 0);
    TEST_THROWS(q.Read(50), Timeout);
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

void MultipleWriteTest(TUint aRPriority, TUint aW0Priority, TUint aW1Priority)
{
    const TUint writer0Iters = 300;
    const TUint writer1Iters = 500;
    FifoTest q(32);
    Writer0 writer0(q, *Thread::Current(),  writer0Iters);
    Functor fWriter0 = MakeFunctor(writer0, &Writer0::Run);
    Writer1 writer1(q, *Thread::Current(), writer1Iters);
    Functor fWriter1 = MakeFunctor(writer1, &Writer1::Run);
    Reader reader(q, *Thread::Current(), writer0Iters + writer1Iters);
    Functor fReader = MakeFunctor(reader, &Reader::Run);

    ThreadFunctor* tReader0 = new ThreadFunctor("TSTA", fReader, aRPriority);
    ThreadFunctor* tWriter0 = new ThreadFunctor("TSTB", fWriter0, aW0Priority);
    ThreadFunctor* tWriter1 = new ThreadFunctor("TSTC", fWriter1, aW1Priority);
    tReader0->Start();
    tWriter0->Start();
    tWriter1->Start();

    Thread* th = Thread::Current();
    ASSERT(th != NULL);
    th->Wait();
    th->Wait();
    th->Wait();

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
    MultipleWriteTest(kPriorityNormal, kPriorityNormal, kPriorityNormal);
    Print("\n\nTestB\n\n");
    MultipleWriteTest(kPriorityNormal, kPriorityLow, kPriorityHigh);
    Print("\n\nTestC\n\n");
    MultipleWriteTest(kPriorityNormal, kPriorityHigh, kPriorityLow);
    Print("\n\nTestD\n\n");
    MultipleWriteTest(kPriorityLow, kPriorityNormal, kPriorityNormal);
    Print("\n\nTestE\n\n");
    MultipleWriteTest(kPriorityLow, kPriorityNormal, kPriorityHigh);
    Print("\n\nTestF\n\n");
    MultipleWriteTest(kPriorityLow, kPriorityHigh, kPriorityNormal);
    Print("\n\nTestG\n\n");
    MultipleWriteTest(kPriorityHigh, kPriorityNormal, kPriorityNormal);
    Print("\n\nTestH\n\n");
    MultipleWriteTest(kPriorityHigh, kPriorityLow, kPriorityNormal);
    Print("\n\nTestI\n\n");
    MultipleWriteTest(kPriorityHigh, kPriorityNormal, kPriorityLow);

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

    //WriteBack

    Print("\n\nWriteBack tests\n\n");

    FifoLite<I*, 4> q2;
    TEST(q2.Slots() == 4);
    TEST(q2.SlotsUsed() == 0);
    TEST(q2.SlotsFree() == 4);
    
    q2.WriteBack(&i1);
    TEST(q2.Slots() == 4);
    TEST(q2.SlotsUsed() == 1);
    TEST(q2.SlotsFree() == 3);

    TEST(q2.Read() == &i1);

    q2.Write(&i2);
    q2.Write(&i3);
    q2.WriteBack(&i1);
    q2.Write(&i4);
    TEST(q2.Slots() == 4);
    TEST(q2.SlotsUsed() == 4);
    TEST(q2.SlotsFree() == 0);
    TEST(q2.Read() == &i1);
    TEST(q2.Read() == &i2);
    TEST(q2.Read() == &i3);
    TEST(q2.Read() == &i4);

    q2.Write(&i2);
    q2.Write(&i3);
    TEST(q2.Read() == &i2);
    q2.WriteBack(&i2);
    TEST(q2.SlotsUsed() == 2);
    TEST(q2.Read() == &i2);
    TEST(q2.Read() == &i3);
    TEST(q2.SlotsUsed() == 0);
}

void Zapp::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
{
    UpnpLibrary::InitialiseMinimal(aInitParams);

    Debug::SetLevel(Debug::kNone);

    Runner runner("FifoS testing\n");
    runner.Add(new SuiteFifoBasic());
    runner.Add(new SuiteFifoThreadSafety());
    runner.Add(new SuiteFifoLiteBasic());
    runner.Run();

    UpnpLibrary::Close();
}
