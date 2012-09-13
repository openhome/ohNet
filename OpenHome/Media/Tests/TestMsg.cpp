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

class SuiteMsgPlayable : public Suite
{
    static const TUint kMsgCount = 8;
public:
    SuiteMsgPlayable();
    ~SuiteMsgPlayable();
    void Test();
private:
    MsgFactory* iMsgFactory;
    InfoAggregator iInfoAggregator;
};

#if 0
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


// SuiteMsgAudio

SuiteMsgAudio::SuiteMsgAudio()
    : Suite("Basic MsgAudio tests")
{
    iMsgFactory = new MsgFactory(iInfoAggregator, kMsgCount, kMsgCount, kMsgCount, 1, 1, 1, 1, 1, 1);
}

SuiteMsgAudio::~SuiteMsgAudio()
{
    delete iMsgFactory;
}

void SuiteMsgAudio::Test()
{
    static const TUint dataSize = 1200;
    Bwh data(dataSize, dataSize);
    (void)memset((void*)data.Ptr(), 0xde, data.Bytes());

    // Create a pcm msg using the same data at each supported sample rate.
    // Check that lower sample rates report higher numbers of jiffies.
    const TUint sampleRates[] = { 7350, 8000, 11025, 12000, 14700, 16000, 22050, 24000, 29400, 32000, 44100, 48000, 88200, 96000, 176400, 192000 };
    const TUint numRates = sizeof(sampleRates) / sizeof(sampleRates[0]);
    TUint prevJiffies = 0xffffffff;
    TUint jiffies;
    MsgAudio* msg;
    for (TUint i=0; i<numRates; i++) {
        msg = iMsgFactory->CreateMsgAudioPcm(data, 2, sampleRates[i], 8, EMediaDataLittleEndian);
        jiffies = msg->Jiffies();
        msg->RemoveRef();
        TEST(prevJiffies > jiffies);
        prevJiffies = jiffies;
    }

    // Create pcm msgs using the same data & sample rates but different bit depths.  Check higher bit depths report lower jiffies
    prevJiffies = 0;
    const TUint bitDepths[] = { 8, 16, 24 };
#define numBitDepths (sizeof(bitDepths) / sizeof(bitDepths[0]))
    MsgAudio* msgbd[numBitDepths];
    for (TUint i=0; i<numBitDepths; i++) {
        msgbd[i] = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, bitDepths[i], EMediaDataLittleEndian);
    }
    TEST(msgbd[0]->Jiffies() == 2 * msgbd[1]->Jiffies());
    TEST(msgbd[0]->Jiffies() == 3 * msgbd[2]->Jiffies());
    for (TUint i=0; i<numBitDepths; i++) {
        msgbd[i]->RemoveRef();
    }

    // Split pcm msg.  Check lengths of both parts are as expected.
    msg = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian);
    static const TUint kSplitPos = 800;
    jiffies = msg->Jiffies();
    MsgAudio* remaining = msg->Split(kSplitPos);
    TEST(remaining != NULL);
    TUint newJiffies = msg->Jiffies();
    TUint remainingJiffies = remaining->Jiffies();
    remaining->RemoveRef();
    TEST(newJiffies > 0);
    TEST(remainingJiffies > 0);
    TEST(newJiffies < jiffies);
    TEST(remainingJiffies < jiffies);
    TEST(newJiffies + remainingJiffies == jiffies);

    // Split pcm msg at invalid positions (0, > Jiffies()).  Check these assert.
    TEST_THROWS(remaining = msg->Split(0), AssertionFailed);
    TEST_THROWS(remaining = msg->Split(msg->Jiffies()), AssertionFailed);
    TEST_THROWS(remaining = msg->Split(msg->Jiffies()+1), AssertionFailed);

    // Clone pcm msg.  Check lengths of clone & parent match
    MsgAudio* clone = msg->Clone();
    jiffies = clone->Jiffies();
    TEST(jiffies == msg->Jiffies());
    msg->RemoveRef();
    // confirm clone is usable after parent is destroyed
    TEST(jiffies == clone->Jiffies());
    clone->RemoveRef();

    // Create silence msg.  Check its length is as expected
    jiffies = Jiffies::kJiffiesPerMs;
    msg = iMsgFactory->CreateMsgSilence(jiffies);
    TEST(jiffies == msg->Jiffies());

    // Split silence msg.  Check lengths of both parts are as expected.
    remaining = msg->Split(jiffies/4);
    TEST(remaining != NULL);
    TEST(msg->Jiffies() == jiffies/4);
    TEST(remaining->Jiffies() == (3*jiffies)/4);
    remaining->RemoveRef();

    // Split silence msg at invalid positions (0, > Jiffies()).  Check these assert.
    TEST_THROWS(remaining = msg->Split(0), AssertionFailed);
    TEST_THROWS(remaining = msg->Split(msg->Jiffies()), AssertionFailed);
    TEST_THROWS(remaining = msg->Split(msg->Jiffies()+1), AssertionFailed);

    // Clone silence msg.  Check lengths of clone & parent match
    clone = msg->Clone();
    jiffies = clone->Jiffies();
    TEST(jiffies == msg->Jiffies());
    msg->RemoveRef();
    clone->RemoveRef();

    // clean destruction of class implies no leaked msgs
}


// SuiteMsgPlayable

SuiteMsgPlayable::SuiteMsgPlayable()
    : Suite("Basic MsgPlayable tests")
{
    iMsgFactory = new MsgFactory(iInfoAggregator, kMsgCount, kMsgCount, kMsgCount, kMsgCount, kMsgCount, 1, 1, 1, 1);
}

SuiteMsgPlayable::~SuiteMsgPlayable()
{
    delete iMsgFactory;
}

void SuiteMsgPlayable::Test()
{
    static const TUint kDataSize = 256;
    Bws<kDataSize> data(kDataSize);
    for (TUint i=0; i<kDataSize; i++) {
        data.At(i) = 0xff - (TByte)i;
    }

    // Create a pcm msg using the same data at each supported sample rate.
    // Convert to MsgPlayable; check Bytes() for each are identical
    const TUint sampleRates[] = { 7350, 8000, 11025, 12000, 14700, 16000, 22050, 24000, 29400, 32000, 44100, 48000, 88200, 96000, 176400, 192000 };
    const TUint numRates = sizeof(sampleRates) / sizeof(sampleRates[0]);
    TUint prevBytes = 0;
    TUint bytes;
    MsgAudioPcm* audioPcm;
    MsgPlayable* playable;
    for (TUint i=0; i<numRates; i++) {
        audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, sampleRates[i], 8, EMediaDataLittleEndian);
        playable = audioPcm->CreatePlayable();
        bytes = playable->Bytes();
        playable->RemoveRef();
        if (prevBytes != 0) {
            TEST(prevBytes == bytes);
        }
        prevBytes = bytes;
    }

    // Create pcm msg.  Read/validate its content
    static const TUint kWriterBufGranularity = 1024;
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian);
    playable = audioPcm->CreatePlayable();
    TEST(playable->Bytes() == data.Bytes() * DecodedAudio::kBytesPerSubsample);
    WriterBwh* writerBuf = new WriterBwh(kWriterBufGranularity);
    playable->Write(*writerBuf);
    Brh buf;
    writerBuf->TransferTo(buf);
    delete writerBuf;
    const TUint* ptr = (const TUint*)buf.Ptr();
    TUint subsampleVal = 0xff;
    for (TUint i=0; i<buf.Bytes(); i+=4) {
        TEST(*ptr == subsampleVal << 24);
        ptr++;
        subsampleVal--;
    }

    // Create pcm msg, split it then convert to playable.  Read/validate contents of both
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian);
    MsgAudioPcm* remainingPcm = (MsgAudioPcm*)audioPcm->Split(audioPcm->Jiffies()/4);
    playable = audioPcm->CreatePlayable();
    MsgPlayable* remainingPlayable = remainingPcm->CreatePlayable();
    TEST(remainingPlayable->Bytes() == 3 * playable->Bytes());
    writerBuf = new WriterBwh(kWriterBufGranularity);
    playable->Write(*writerBuf);
    writerBuf->TransferTo(buf);
    delete writerBuf;
    subsampleVal = 0xff;
    ptr = (const TUint*)buf.Ptr();
    for (TUint i=0; i<buf.Bytes(); i+=4) {
        TEST(*ptr == subsampleVal << 24);
        ptr++;
        subsampleVal--;
    }
    writerBuf = new WriterBwh(kWriterBufGranularity);
    remainingPlayable->Write(*writerBuf);
    writerBuf->TransferTo(buf);
    delete writerBuf;
    ptr = (const TUint*)buf.Ptr();
    for (TUint i=0; i<buf.Bytes(); i+=4) {
        TEST(*ptr == subsampleVal << 24);
        ptr++;
        subsampleVal--;
    }

    // Create pcm msg, convert to playable then split.  Read/validate contents of both
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian);
    playable = audioPcm->CreatePlayable();
    remainingPlayable = playable->Split(playable->Bytes()/4);
    TEST(remainingPlayable->Bytes() == 3 * playable->Bytes());
    writerBuf = new WriterBwh(kWriterBufGranularity);
    playable->Write(*writerBuf);
    writerBuf->TransferTo(buf);
    delete writerBuf;
    subsampleVal = 0xff;
    ptr = (const TUint*)buf.Ptr();
    for (TUint i=0; i<buf.Bytes(); i+=4) {
        TEST(*ptr == subsampleVal << 24);
        ptr++;
        subsampleVal--;
    }
    writerBuf = new WriterBwh(kWriterBufGranularity);
    remainingPlayable->Write(*writerBuf);
    writerBuf->TransferTo(buf);
    delete writerBuf;
    ptr = (const TUint*)buf.Ptr();
    for (TUint i=0; i<buf.Bytes(); i+=4) {
        TEST(*ptr == subsampleVal << 24);
        ptr++;
        subsampleVal--;
    }

    // Create pcm msg, split at non-sample boundary.  Read/validate contents of each fragment
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian);
    remainingPcm = (MsgAudioPcm*)audioPcm->Split((audioPcm->Jiffies()/4) - 1);
    playable = audioPcm->CreatePlayable();
    remainingPlayable = remainingPcm->CreatePlayable();
    writerBuf = new WriterBwh(kWriterBufGranularity);
    playable->Write(*writerBuf);
    writerBuf->TransferTo(buf);
    delete writerBuf;
    subsampleVal = 0xff;
    ptr = (const TUint*)buf.Ptr();
    for (TUint i=0; i<buf.Bytes(); i+=4) {
        TEST(*ptr == subsampleVal << 24);
        ptr++;
        subsampleVal--;
    }
    writerBuf = new WriterBwh(kWriterBufGranularity);
    remainingPlayable->Write(*writerBuf);
    writerBuf->TransferTo(buf);
    delete writerBuf;
    ptr = (const TUint*)buf.Ptr();
    for (TUint i=0; i<buf.Bytes(); i+=4) {
        TEST(*ptr == subsampleVal << 24);
        ptr++;
        subsampleVal--;
    }

    // Create pcm msg, split at 1 jiffy (non-sample boundary).  Check initial msg has 0 Bytes() but can Write() its content
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian);
    remainingPcm = (MsgAudioPcm*)audioPcm->Split(1);
    playable = audioPcm->CreatePlayable();
    remainingPlayable = remainingPcm->CreatePlayable();
    writerBuf = new WriterBwh(kWriterBufGranularity);
    playable->Write(*writerBuf);
    writerBuf->TransferTo(buf);
    delete writerBuf;
    TEST(buf.Bytes() == 0);
    writerBuf = new WriterBwh(kWriterBufGranularity);
    remainingPlayable->Write(*writerBuf);
    writerBuf->TransferTo(buf);
    delete writerBuf;
    TEST(buf.Bytes() == data.Bytes() * DecodedAudio::kBytesPerSubsample);

    // Split pcm msg at invalid positions (0, > Jiffies()).  Check these assert.
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian);
    playable = audioPcm->CreatePlayable();
    TEST_THROWS(remainingPlayable = playable->Split(0), AssertionFailed);
    TEST_THROWS(remainingPlayable = playable->Split(playable->Bytes()), AssertionFailed);
    TEST_THROWS(remainingPlayable = playable->Split(playable->Bytes()+1), AssertionFailed);
    playable->RemoveRef();

    // For each sample rate, create a silence msg using the same size
    // Convert to MsgPlayable; check Bytes() decrease as sample rates increase

    // Create silence msg.  Read/validate its content

    // Create silence msg, convert to playable then split.  Read/validate contents of both

    // Create silence msg, split at non-sample boundary.  Read/validate contents of each fragment

    // Create silence msg, split at 1 jiffy (non-sample boundary).  Check initial msg has 0 Bytes() but can Write() its content

    // clean destruction of class implies no leaked msgs
}


void TestMsg()
{
    Runner runner("Basic Msg tests\n");
    runner.Add(new SuiteAllocator());
#if 0
    runner.Add(new SuiteMsgQueue());
#endif // 0
    runner.Add(new SuiteMsgAudio());
    runner.Add(new SuiteMsgPlayable());
    // MsgAudio - Pcm & Silence
    // Playable.  Both Pcm & Silence.  Include checks that can split on non-sample boundaries without losing data
    // Ramp (stand-alone class, then as part of MsgAudio, then as part of MsgPlayable)
    // MsgProcessor.  Check that function for each msg type can be called
    // MsgQueue
    // MsgQueueJiffies
    runner.Run();
}


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestMsg();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
