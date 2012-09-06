#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/InfoProvider.h>

#include <string.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class InfoAggregator : public Av::IInfoAggregator, private IWriter
{
public:
    InfoAggregator();
    void PrintStats();
private: // from IInfoAggregator
    void Register(Av::IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries);
private: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
private:
    std::vector<Av::IInfoProvider*> iInfoProviders;
};

class SuiteAllocator : public Suite
{
public:
    SuiteAllocator();
    void Test();
private:
    static const TUint kNumTestCells = 10;
    InfoAggregator iInfoAggregator;
};

class TestCell : public Allocated
{
public:
    TestCell(AllocatorBase& aAllocator);
    void Fill(TChar aVal);
    void CheckIsFilled(TChar aVal) const;
private:
    static const TUint kNumBytes = 10;
    TChar iBytes[kNumBytes];
};
#if 0
class SuiteMsgAudio : public Suite
{
    static const TUint kMsgCount = 8;
public:
    SuiteMsgAudio();
    ~SuiteMsgAudio();
    void Test();
private:
    MsgFactory* iMsgFactory;
    InfoAggregator iInfoAggregator;
};

class SuiteMsgQueue : public Suite
{
    static const TUint kMsgCount = 8;
public:
    SuiteMsgQueue();
    ~SuiteMsgQueue();
    void Test();
private:
    MsgFactory* iMsgFactory;
    InfoAggregator iInfoAggregator;
};

class ProcessorMsgAudio : public IMsgProcessor
{
public:
    ProcessorMsgAudio();
    TUint LastMsgAudioBytes() const;
private:
    void ProcessMsg(MsgAudio& aMsg);
    void ProcessMsg(MsgTrack& aMsg);
    void ProcessMsg(MsgStartOfAudio& aMsg);
    void ProcessMsg(MsgMetaText& aMsg);
    void ProcessMsg(MsgHalt& aMsg);
    void ProcessMsg(MsgFlush& aMsg);
private:
    TUint iLastMsgAudioBytes;
};
#endif // 0
} // namespace Media
} // namespace OpenHome


// InfoAggregator

InfoAggregator::InfoAggregator()
{
}

void InfoAggregator::PrintStats()
{
    for (size_t i=0; i<iInfoProviders.size(); i++) {
        iInfoProviders[i]->QueryInfo(AllocatorBase::kQueryMemory, *this);
    }
}

void InfoAggregator::Register(Av::IInfoProvider& aProvider, std::vector<Brn>& /*aSupportedQueries*/)
{
    iInfoProviders.push_back(&aProvider);
}

void InfoAggregator::Write(TByte aValue)
{
    Print("%c", aValue);
}

void InfoAggregator::Write(const Brx& aBuffer)
{
    Print(aBuffer);
}

void InfoAggregator::WriteFlush()
{
}


// TestCell

TestCell::TestCell(AllocatorBase& aAllocator)
    : Allocated(aAllocator)
{
    Fill((TByte)0xff);
}

void TestCell::Fill(TChar aVal)
{
    memset(&iBytes[0], aVal, kNumBytes);
}

void TestCell::CheckIsFilled(TChar aVal) const
{
    for (TUint i=0; i<kNumBytes; i++) {
        TEST(iBytes[i] == aVal);
    }
}


// SuiteAllocator

SuiteAllocator::SuiteAllocator()
    : Suite("Allocator tests")
{
}

void SuiteAllocator::Test()
{
    //Print("\nCreate Allocator with 10 TestCells.  Check that 10 TestCells can be allocated\n");
    Allocator<TestCell>* allocator = new Allocator<TestCell>("TestCell", kNumTestCells, iInfoAggregator);
    TestCell* cells[kNumTestCells];
    for (TUint i=0; i<kNumTestCells; i++) {
        cells[i] = allocator->Allocate();
        TEST(cells[i] != NULL);
    }
    
    //Print("\nalloc 11th TestCell.  Check this throws\n");
    // currently disabled until allocator throws rather than blocking when full
    //TEST_THROWS(allocator->Allocate(), AllocatorNoMemory);
    
    //Print("\nuse InfoProvider.  Visually check results\n");
    iInfoAggregator.PrintStats();
    
    //Print("\nmemset each TestCell to a different value, check that all can be read back (so TestCells don't overlap)\n");
    for (TUint i=0; i<kNumTestCells; i++) {
        cells[i]->Fill((TByte)i);
    }
    for (TUint i=0; i<kNumTestCells; i++) {
        cells[i]->CheckIsFilled((TByte)i);
    }
    
    //Print("\nfree all TestCells.  Check values of iTestCellsUsed and iTestCellsUsedMax\n");
    TEST(allocator->CellsUsed() == kNumTestCells);
    TEST(allocator->CellsUsedMax() == kNumTestCells);
    for (TUint i=0; i<kNumTestCells; i++) {
        allocator->Free(cells[i]);
        TEST(allocator->CellsUsed() == kNumTestCells - i - 1);
        TEST(allocator->CellsUsedMax() == kNumTestCells);
    }
    
    //Print("\nreallocate all TestCells, confirming that freed TestCells can be reused\n");
    for (TUint i=0; i<kNumTestCells; i++) {
        cells[i] = allocator->Allocate();
        TEST(cells[i] != NULL);
    }
    TEST(allocator->CellsUsed() == kNumTestCells);
    
    //Print("\nfree 9 of the 10 TestCells then delete allocator.  Check this asserts (due to the memory leak)\n");
    // disabled until Fifo is updated to enable this assert
    // ...even then we may not want the test if it causes valgrind failures
    /*for (TUint i=0; i<9; i++) {
        allocator->Free(cells[i]);
    }
    TEST(allocator->iTestCellsUsed == 1);
    TEST_THROWS(delete allocator, AssertionFailed);*/

    //Print("Free all cells; check that allocator can now be deleted.\n");
    for (TUint i=0; i<kNumTestCells; i++) {
        allocator->Free(cells[i]);
    }
    delete allocator;
}

#if 0
// SuiteMsgAudio

SuiteMsgAudio::SuiteMsgAudio()
    : Suite("Basic MsgAudio tests")
{
    iMsgFactory = new MsgFactory(iInfoAggregator, kMsgCount, kMsgCount, 1, 1, 1, 1);
}

SuiteMsgAudio::~SuiteMsgAudio()
{
    delete iMsgFactory;
}

void SuiteMsgAudio::Test()
{
    // create 3 msgs.  Check their lengths are as expected
    Brn data1("0123456789");
    Brn data2("abcde");
    Brn data3("fghijklmnopqrstuvwxyz");
    MsgAudio* msg1 = iMsgFactory->CreateMsgAudio(data1, 1, 44100, 8, EMediaDataLittleEndian);
    TEST(msg1->Bytes() == data1.Bytes() * sizeof(TUint));
    MsgAudio* msg2 = iMsgFactory->CreateMsgAudio(data2, 1, 44100, 8, EMediaDataLittleEndian);
    TEST(msg2->Bytes() == data2.Bytes() * sizeof(TUint));
    MsgAudio* msg3 = iMsgFactory->CreateMsgAudio(data3, 1, 44100, 8, EMediaDataLittleEndian);
    TEST(msg3->Bytes() == data3.Bytes() * sizeof(TUint));

    // Add msgs.  Check length of #1 increases as expected
    msg1->Add(msg2);
    TEST(msg1->Bytes() == (data1.Bytes() + data2.Bytes()) * sizeof(TUint));
    msg1->Add(msg3);
    TEST(msg1->Bytes() == (data1.Bytes() + data2.Bytes() + data3.Bytes()) * sizeof(TUint));

    // split message inside #3.  Check lengths of #1 and (new) #4 are as expected
    const TUint kData3SplitBytes = 2;
    MsgAudio* msg4 = msg1->SplitBytes((data1.Bytes() + data2.Bytes() + kData3SplitBytes) * sizeof(TUint));
    TEST(msg1->Bytes() == (data1.Bytes() + data2.Bytes() + kData3SplitBytes) * sizeof(TUint));
    TEST(msg4->Bytes() == (data3.Bytes() - kData3SplitBytes) * sizeof(TUint));

    // clone #1.  Check that clone's length matches #1's
    MsgAudio* msg5 = msg1->Clone();
    TEST(msg1->Bytes() == msg5->Bytes());

    // read/validate data from #1
    Bws<40> outputBytes1;
    outputBytes1.Append(data1);
    outputBytes1.Append(data2);
    outputBytes1.Append(Brn(data3.Ptr(), kData3SplitBytes));
    Bws<40> outputBytes2;
    outputBytes2.Append(data3.Split(kData3SplitBytes));
    TUint outputWords[40];
    TUint subsamples = msg1->Bytes() / sizeof(TUint);
    msg1->CopyTo(outputWords);
    for (TUint i=0; i<subsamples; i++) {
        TEST(outputBytes1[i] == (TChar)(outputWords[i]>>24));
    }

    // read/validate data from #5 (clone)
    TUint outputWordsClone[40];
    msg5->CopyTo(outputWordsClone);
    for (TUint i=0; i<subsamples; i++) {
        TEST(outputWords[i] == outputWordsClone[i]);
    }
    TEST(0 == memcmp(outputWords, outputWordsClone, subsamples * sizeof(outputWords[0])));

    // read/validate data from msg4
    Brn outputWordsMsg4 = data3.Split(kData3SplitBytes);
    subsamples = msg4->Bytes() / sizeof(TUint);
    msg4->CopyTo(outputWords);
    for (TUint i=0; i<subsamples; i++) {
        TEST(outputWordsMsg4[i] == (TChar)(outputWords[i]>>24));
    }

    // create a Msg then free it without consuming its data in the normal CopyTo way
    MsgAudio* msg6 = iMsgFactory->CreateMsgAudio(data1, 1, 44100, 8, EMediaDataLittleEndian);
    msg6->RemoveRef();

    // create a Msg, Add() another to it them check that removing the first one's reference frees both
    MsgAudio* msg7 = iMsgFactory->CreateMsgAudio(data1, 1, 44100, 8, EMediaDataLittleEndian);
    MsgAudio* msg8 = iMsgFactory->CreateMsgAudio(data1, 1, 44100, 8, EMediaDataLittleEndian);
    msg7->Add(msg8);
    msg7->RemoveRef();

    // splt a single message into 3.  Check their lengths/contents are as expected
    MsgAudio* msg9 = iMsgFactory->CreateMsgAudio(data1, 1, 44100, 8, EMediaDataLittleEndian);
    const TUint kData1SplitBytes = 4;
    MsgAudio* msg10 = msg9->SplitBytes(kData1SplitBytes * sizeof(TUint));
    MsgAudio* msg11 = msg10->SplitBytes(kData1SplitBytes * sizeof(TUint));

    TEST(msg9->Bytes() == kData1SplitBytes * sizeof(TUint));
    Brn expected(data1.Ptr(), kData1SplitBytes);
    subsamples = msg9->Bytes() / sizeof(TUint);
    msg9->CopyTo(outputWords);
    for (TUint i=0; i<subsamples; i++) {
        TEST(expected[i] == (TChar)(outputWords[i]>>24));
    }

    TEST(msg10->Bytes() == kData1SplitBytes * sizeof(TUint));
    expected.Set(data1.Split(kData1SplitBytes, kData1SplitBytes));
    subsamples = msg10->Bytes() / sizeof(TUint);
    msg10->CopyTo(outputWords);
    for (TUint i=0; i<subsamples; i++) {
        TEST(expected[i] == (TChar)(outputWords[i]>>24));
    }

    TEST(msg11->Bytes() == (data1.Bytes() - (2 * kData1SplitBytes)) * sizeof(TUint));
    expected.Set(data1.Split(2 * kData1SplitBytes));
    subsamples = msg11->Bytes() / sizeof(TUint);
    msg11->CopyTo(outputWords);
    for (TUint i=0; i<subsamples; i++) {
        TEST(expected[i] == (TChar)(outputWords[i]>>24));
    }

    // clean destruction of class implies no leaked msgs
}


// SuiteMsgQueue

SuiteMsgQueue::SuiteMsgQueue()
    : Suite("MsgQueue tests")
{
    iMsgFactory = new MsgFactory(iInfoAggregator, kMsgCount, kMsgCount, 1, 1);
}

SuiteMsgQueue::~SuiteMsgQueue()
{
    delete iMsgFactory;
}

void SuiteMsgQueue::Test()
{
    Brn data1("0123456789");
    Brn data2("abcde");
    Brn data3("fghijklmnopqrstuvwxyz");

    // test that queue can be populated and read from
    MsgAudio* msg1 = iMsgFactory->CreateMsgAudio(data1, 1, 44100, 8, EMediaDataLittleEndian);
    MsgAudio* msg2 = iMsgFactory->CreateMsgAudio(data2, 1, 44100, 8, EMediaDataLittleEndian);
    MsgAudio* msg3 = iMsgFactory->CreateMsgAudio(data3, 1, 44100, 8, EMediaDataLittleEndian);
    MsgQueue* queue = new MsgQueue();
    queue->Enqueue(msg1);
    queue->Enqueue(msg2);
    queue->Enqueue(msg3);
    ProcessorMsgAudio processor;
    Msg* msg = queue->Dequeue();
    msg->Process(processor);
    TEST(processor.LastMsgAudioBytes() == msg1->Bytes());
    msg->RemoveRef();
    msg = queue->Dequeue();
    msg->Process(processor);
    TEST(processor.LastMsgAudioBytes() == msg2->Bytes());
    msg->RemoveRef();
    msg = queue->Dequeue();
    msg->Process(processor);
    TEST(processor.LastMsgAudioBytes() == msg3->Bytes());
    // test that the queue can be emptied then reused
    queue->Enqueue(msg);
    msg = queue->Dequeue();
    delete queue;
    msg->Process(processor);
    TEST(processor.LastMsgAudioBytes() == msg3->Bytes());
    msg->RemoveRef();

    // FIXME - no check yet that reading from an empty queue blocks
}


// ProcessorMsgAudio

ProcessorMsgAudio::ProcessorMsgAudio()
    : iLastMsgAudioBytes(0)
{
}

TUint ProcessorMsgAudio::LastMsgAudioBytes() const
{
    return iLastMsgAudioBytes;
}

void ProcessorMsgAudio::ProcessMsg(MsgAudio& aMsg)
{
    iLastMsgAudioBytes = aMsg.Bytes();
}

void ProcessorMsgAudio::ProcessMsg(MsgTrack& /*aMsg*/)
{
    ASSERTS();
}

void ProcessorMsgAudio::ProcessMsg(MsgStartOfAudio& /*aMsg*/)
{
    ASSERTS();
}

void ProcessorMsgAudio::ProcessMsg(MsgMetaText& /*aMsg*/)
{
    ASSERTS();
}
#endif // 0
    
void TestMsg()
{
    Runner runner("Basic Msg tests\n");
    runner.Add(new SuiteAllocator());
#if 0
    runner.Add(new SuiteMsgAudio());
    runner.Add(new SuiteMsgQueue());
#endif // 0
    runner.Run();
}


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestMsg();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
