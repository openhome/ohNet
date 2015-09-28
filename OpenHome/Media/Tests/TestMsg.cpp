#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/RampArray.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>

#include <string.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteAllocator : public Suite
{
public:
    SuiteAllocator();
    void Test();
private:
    static const TUint kNumTestCells = 10;
    AllocatorInfoLogger iInfoAggregator;
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

class SuiteMsgAudioEncoded : public Suite
{
    static const TUint kMsgCount = 8;
public:
    SuiteMsgAudioEncoded();
    ~SuiteMsgAudioEncoded();
    void Test();
private:
    MsgFactory* iMsgFactory;
    AllocatorInfoLogger iInfoAggregator;
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
    AllocatorInfoLogger iInfoAggregator;
};

class SuiteMsgPlayable : public Suite
{
    static const TUint kMsgCount = 2;
public:
    SuiteMsgPlayable();
    ~SuiteMsgPlayable();
    void Test();
private:
    void ValidateSilence(MsgPlayable* aMsg);
private:
    MsgFactory* iMsgFactory;
    AllocatorInfoLogger iInfoAggregator;
};

class SuiteRamp : public Suite
{
    static const TUint kMsgCount = 8;
public:
    SuiteRamp();
    ~SuiteRamp();
    void Test();
private:
    MsgFactory* iMsgFactory;
    AllocatorInfoLogger iInfoAggregator;
};

class SuiteAudioStream : public Suite
{
    static const TUint kMsgEncodedStreamCount = 1;
public:
    SuiteAudioStream();
    ~SuiteAudioStream();
    void Test();
private:
    MsgFactory* iMsgFactory;
    AllocatorInfoLogger iInfoAggregator;
};

class SuiteMetaText : public Suite
{
    static const TUint kMsgMetaTextCount = 1;
public:
    SuiteMetaText();
    ~SuiteMetaText();
    void Test();
private:
    MsgFactory* iMsgFactory;
    AllocatorInfoLogger iInfoAggregator;
};

class SuiteTrack : public Suite
{
    static const TUint kMsgTrackCount = 1;
public:
    SuiteTrack();
    ~SuiteTrack();
    void Test();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
};

class SuiteFlush : public Suite
{
    static const TUint kMsgFlushCount = 1;
public:
    SuiteFlush();
    ~SuiteFlush();
    void Test();
private:
    MsgFactory* iMsgFactory;
    AllocatorInfoLogger iInfoAggregator;
};

class SuiteHalt : public Suite
{
    static const TUint kMsgHaltCount = 1;
public:
    SuiteHalt();
    ~SuiteHalt();
    void Test();
private:
    MsgFactory* iMsgFactory;
    AllocatorInfoLogger iInfoAggregator;
};

class SuiteMode : public Suite
{
    static const TUint kMsgModeCount = 1;
public:
    SuiteMode();
    ~SuiteMode();
    void Test();
private:
    MsgFactory* iMsgFactory;
    AllocatorInfoLogger iInfoAggregator;
};

class SuiteDelay : public Suite
{
    static const TUint kMsgDelayCount = 1;
public:
    SuiteDelay();
    ~SuiteDelay();
    void Test();
private:
    MsgFactory* iMsgFactory;
    AllocatorInfoLogger iInfoAggregator;
};

class SuiteDecodedStream : public Suite, private IStreamHandler
{
    static const TUint kMsgDecodedStreamCount = 1;
public:
    SuiteDecodedStream();
    ~SuiteDecodedStream();
    void Test();
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    MsgFactory* iMsgFactory;
    AllocatorInfoLogger iInfoAggregator;
};

class SuiteMsgProcessor : public Suite
{
public:
    SuiteMsgProcessor();
    ~SuiteMsgProcessor();
    void Test();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
};

class ProcessorMsgType : public IMsgProcessor
{
public:
    enum EMsgType
    {
        ENone
       ,EMsgMode
       ,EMsgTrack
       ,EMsgDrain
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgAudioEncoded
       ,EMsgMetaText
       ,EMsgStreamInterrupted
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgDecodedStream
       ,EMsgBitRate
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgQuit
    };
public:
    ProcessorMsgType();
    EMsgType LastMsgType() const;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    EMsgType iLastMsgType;
};

class SuiteMsgQueue : public Suite
{
public:
    SuiteMsgQueue();
    ~SuiteMsgQueue();
    void Test();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
};

class SuiteMsgReservoir : public Suite
{
    static const TUint kMsgCount = 8;
public:
    SuiteMsgReservoir();
    ~SuiteMsgReservoir();
    void Test();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
};

class TestMsgReservoir : public MsgReservoir
{
public:
    enum EMsgType
    {
        ENone
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgMode
       ,EMsgTrack
       ,EMsgDrain
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgDecodedStream
       ,EMsgBitRate
       ,EMsgMetaText
       ,EMsgStreamInterrupted
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgQuit
    };
public:
    TestMsgReservoir();
    void Enqueue(Msg* aMsg)          { DoEnqueue(aMsg); }
    Msg* Dequeue()                   { return DoDequeue(); }
    void EnqueueAtHead(Msg* aMsg)    { MsgReservoir::EnqueueAtHead(aMsg); }
    TUint Jiffies() const            { return MsgReservoir::Jiffies(); }
    TUint EncodedStreamCount() const { return MsgReservoir::EncodedStreamCount(); }
    TUint DecodedStreamCount() const { return MsgReservoir::DecodedStreamCount(); }
    EMsgType LastIn() const          { return iLastMsgIn; }
    EMsgType LastOut() const         { return iLastMsgOut; }
    void SplitNextAudio()            { iSplitNextAudio = true; }
private:
    Msg* ProcessMsgAudioOut(MsgAudio* aMsgAudio);
private: // from MsgQueueFlushable
    void ProcessMsgIn(MsgAudioPcm* aMsg) override;
    void ProcessMsgIn(MsgSilence* aMsg) override;
    void ProcessMsgIn(MsgMode* aMsg) override;
    void ProcessMsgIn(MsgTrack* aMsg) override;
    void ProcessMsgIn(MsgDrain* aMsg) override;
    void ProcessMsgIn(MsgDelay* aMsg) override;
    void ProcessMsgIn(MsgEncodedStream* aMsg) override;
    void ProcessMsgIn(MsgDecodedStream* aMsg) override;
    void ProcessMsgIn(MsgBitRate* aMsg) override;
    void ProcessMsgIn(MsgMetaText* aMsg) override;
    void ProcessMsgIn(MsgStreamInterrupted* aMsg) override;
    void ProcessMsgIn(MsgHalt* aMsg) override;
    void ProcessMsgIn(MsgFlush* aMsg) override;
    void ProcessMsgIn(MsgWait* aMsg) override;
    void ProcessMsgIn(MsgQuit* aMsg) override;
    Msg* ProcessMsgOut(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsgOut(MsgSilence* aMsg) override;
    Msg* ProcessMsgOut(MsgMode* aMsg) override;
    Msg* ProcessMsgOut(MsgTrack* aMsg) override;
    Msg* ProcessMsgOut(MsgDrain* aMsg) override;
    Msg* ProcessMsgOut(MsgDelay* aMsg) override;
    Msg* ProcessMsgOut(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsgOut(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsgOut(MsgBitRate* aMsg) override;
    Msg* ProcessMsgOut(MsgMetaText* aMsg) override;
    Msg* ProcessMsgOut(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsgOut(MsgHalt* aMsg) override;
    Msg* ProcessMsgOut(MsgFlush* aMsg) override;
    Msg* ProcessMsgOut(MsgWait* aMsg) override;
    Msg* ProcessMsgOut(MsgQuit* aMsg) override;
private:
    EMsgType iLastMsgIn;
    EMsgType iLastMsgOut;
    TBool iSplitNextAudio;
};

class DummyElement : public PipelineElement, private INonCopyable
{
public:
    DummyElement(TUint aSupported);
    void Process(Msg* aMsg);
};

class SuitePipelineElement : public Suite
{
public:
    SuitePipelineElement();
    ~SuitePipelineElement();
    void Test();
private:
    Msg* CreateMsg(ProcessorMsgType::EMsgType aType);
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
};

} // namespace Media
} // namespace OpenHome


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
        TEST(cells[i] != nullptr);
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
        cells[i]->iRefCount--; // clear ref from Allocate() to avoid assertion if we re-Allocate() this object
        allocator->Free(cells[i]);
        TEST(allocator->CellsUsed() == kNumTestCells - i - 1);
        TEST(allocator->CellsUsedMax() == kNumTestCells);
    }
    
    //Print("\nreallocate all TestCells, confirming that freed TestCells can be reused\n");
    for (TUint i=0; i<kNumTestCells; i++) {
        cells[i] = allocator->Allocate();
        TEST(cells[i] != nullptr);
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


// SuiteMsgAudioEncoded

SuiteMsgAudioEncoded::SuiteMsgAudioEncoded()
    : Suite("MsgAudioEncoded tests")
{
    MsgFactoryInitParams init;
    init.SetMsgAudioEncodedCount(kMsgCount, kMsgCount);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
}

SuiteMsgAudioEncoded::~SuiteMsgAudioEncoded()
{
    delete iMsgFactory;
}

void SuiteMsgAudioEncoded::Test()
{
    // create msg, check it reports the correct number of bytes
    const TUint kNumBytes = 64;
    TByte data[kNumBytes];
    for (TUint i=0; i<sizeof(data)/sizeof(data[0]); i++) {
        data[i] = (TByte)i;
    }
    Brn buf(data, sizeof(data));
    MsgAudioEncoded* msg = iMsgFactory->CreateMsgAudioEncoded(buf);
    TEST(msg->Bytes() == buf.Bytes());

    // check that CopyTo outputs the expected data
    TByte output[128];
    msg->CopyTo(output);
    for (TUint i=0; i<msg->Bytes(); i++) {
        TEST(output[i] == buf[i]);
    }

    // split msg, check its two parts report the same number of bytes
    TUint totalSize = msg->Bytes();
    TUint splitPos = 49;
    MsgAudioEncoded* msg2 = msg->Split(splitPos);
    TEST(msg->Bytes() == splitPos);
    TEST(msg2->Bytes() == totalSize - splitPos);

    // check that each part outputs the expected data
    (void)memset(output, 0xde, sizeof(output));
    msg->CopyTo(output);
    for (TUint i=0; i<msg->Bytes(); i++) {
        TEST(output[i] == buf[i]);
    }
    (void)memset(output, 0xde, sizeof(output));
    msg2->CopyTo(output);
    for (TUint i=0; i<msg2->Bytes(); i++) {
        TEST(output[i] == buf[splitPos + i]);
    }
    msg->RemoveRef();
    msg2->RemoveRef();

    // create two msgs; add them together; check their size and output
    TByte data2[kNumBytes/2];
    for (TUint i=0; i<sizeof(data2)/sizeof(data2[0]); i++) {
        data2[i] = (TByte)(255 - i);
    }
    Brn buf2(data2, sizeof(data2));
    msg = iMsgFactory->CreateMsgAudioEncoded(buf);
    TUint msg1Size = msg->Bytes();
    msg2 = iMsgFactory->CreateMsgAudioEncoded(buf2);
    TUint msg2Size = msg2->Bytes();
    msg->Add(msg2);
    TEST(msg->Bytes() == msg1Size + msg2Size);
    (void)memset(output, 0xde, sizeof(output));
    msg->CopyTo(output);
    for (TUint i=0; i<msg->Bytes(); i++) {
        if (i < buf.Bytes()) {
            TEST(output[i] == buf[i]);
        }
        else {
            TEST(output[i] == buf2[i - buf.Bytes()]);
        }
    }

    // split in second msg; check size/output of both
    splitPos = 10;
    msg2 = msg->Split(msg1Size + splitPos);
    TEST(msg->Bytes() == msg1Size + splitPos);
    TEST(msg2->Bytes() == msg2Size - splitPos);
    (void)memset(output, 0xde, sizeof(output));
    msg->CopyTo(output);
    for (TUint i=0; i<msg->Bytes(); i++) {
        if (i < buf.Bytes()) {
            TEST(output[i] == buf[i]);
        }
        else {
            TEST(output[i] == buf2[i - buf.Bytes()]);
        }
    }
    (void)memset(output, 0xde, sizeof(output));
    msg2->CopyTo(output);
    for (TUint i=0; i<msg2->Bytes(); i++) {
        TEST(output[i] == buf2[i + splitPos]);
    }
    msg2->RemoveRef();

    // split first fragment inside first msg; check size/output of both
    msg1Size = msg->Bytes();
    msg2 = msg->Split(splitPos);
    TEST(msg->Bytes() == splitPos);
    TEST(msg2->Bytes() == msg1Size - splitPos);
    (void)memset(output, 0xde, sizeof(output));
    msg->CopyTo(output);
    for (TUint i=0; i<msg->Bytes(); i++) {
        TEST(output[i] == buf[i]);
    }
    msg->RemoveRef();
    (void)memset(output, 0xde, sizeof(output));
    msg2->CopyTo(output);
    for (TUint i=0; i<msg2->Bytes(); i++) {
        if (i < buf.Bytes() - splitPos) {
            TEST(output[i] == buf[i + splitPos]);
        }
        else {
            TEST(output[i] == buf2[i - buf.Bytes() + splitPos]);
        }
    }
    msg2->RemoveRef();

     // create chained msg, try split at various positions, including message boundaries
    msg = iMsgFactory->CreateMsgAudioEncoded(buf);
    msg1Size = msg->Bytes();
    msg2 = iMsgFactory->CreateMsgAudioEncoded(buf2);
    msg2Size = msg2->Bytes();
    msg->Add(msg2);
    TEST(msg->Bytes() == msg1Size + msg2Size);
    // try split at start of message
    TEST_THROWS(msg->Split(0), AssertionFailed);
    // try split at end of message
    TEST_THROWS(msg->Split(msg->Bytes()), AssertionFailed);
    // try split beyond end of message
    TEST_THROWS(msg->Split(msg->Bytes()+1), AssertionFailed);

    // try split at boundary between two messages
    splitPos = msg1Size;
    msg2 = msg->Split(splitPos);
    TEST(msg->Bytes() == msg1Size);
    TEST(msg2->Bytes() == msg2Size);
    (void)memset(output, 0xde, sizeof(output));
    msg->CopyTo(output);
    for (TUint i=0; i<msg->Bytes(); i++) {
        TEST(output[i] == buf[i]);
    }
    msg->RemoveRef();
    (void)memset(output, 0xde, sizeof(output));
    msg2->CopyTo(output);
    for (TUint i=0; i<msg2->Bytes(); i++) {
        if (i < buf.Bytes() - splitPos) {
            TEST(output[i] == buf[i + splitPos]);
        }
        else {
            TEST(output[i] == buf2[i - buf.Bytes() + splitPos]);
        }
    }
    msg2->RemoveRef();

    // try cloning a message, check size and output of both are same
    msg = iMsgFactory->CreateMsgAudioEncoded(buf);
    msg2 = msg->Clone();

    msg1Size = msg->Bytes();
    msg2Size = msg2->Bytes();
    TEST(msg1Size == msg2Size);

    (void)memset(output, 0xde, sizeof(output));
    msg->CopyTo(output);
    for (TUint i=0; i<msg->Bytes(); i++) {
        TEST(output[i] == buf[i]);
    }
    (void)memset(output, 0xde, sizeof(output));
    msg2->CopyTo(output);
    for (TUint i=0; i<msg2->Bytes(); i++) {
        TEST(output[i] == buf[i]);
    }
    msg->RemoveRef();
    msg2->RemoveRef();

    // try cloning a chained message, check size and output are same
    msg = iMsgFactory->CreateMsgAudioEncoded(buf);
    msg1Size = msg->Bytes();
    msg2 = iMsgFactory->CreateMsgAudioEncoded(buf2);
    msg2Size = msg2->Bytes();
    msg->Add(msg2);
    MsgAudioEncoded* msg3 = msg->Clone();
    TEST(msg3->Bytes() == msg1Size + msg2Size);

    (void)memset(output, 0xde, sizeof(output));
    msg3->CopyTo(output);
    for (TUint i=0; i<msg3->Bytes(); i++) {
        if (i < buf.Bytes()) {
            TEST(output[i] == buf[i]);
        }
        else {
            TEST(output[i] == buf2[i - buf.Bytes()]);
        }
    }
    msg->RemoveRef();
    msg3->RemoveRef();

    // Append adds full buffer when space available
    memset(data, 0, sizeof(data));
    buf.Set(data, sizeof(data));
    msg = iMsgFactory->CreateMsgAudioEncoded(buf);
    memset(data, 1, sizeof(data));
    TUint consumed = msg->Append(buf);
    TEST(consumed == buf.Bytes());
    msg->CopyTo(output);
    TEST(output[buf.Bytes() - 1] == 0);
    TEST(output[buf.Bytes()] == 1);
    msg->RemoveRef();

    // Append truncates buffer when insufficient space
    TByte data3[1023];
    memset(data3, 9, sizeof(data3));
    buf.Set(data3, sizeof(data3));
    msg = iMsgFactory->CreateMsgAudioEncoded(buf);
    do {
        consumed = msg->Append(buf);
    } while (consumed == buf.Bytes());
    TEST(consumed == EncodedAudio::kMaxBytes % buf.Bytes());
    msg->RemoveRef();

    // clean shutdown implies no leaked msgs
}


// SuiteMsgAudio

SuiteMsgAudio::SuiteMsgAudio()
    : Suite("Basic MsgAudio tests")
{
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(kMsgCount, kMsgCount);
    init.SetMsgSilenceCount(kMsgCount);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
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
        msg = iMsgFactory->CreateMsgAudioPcm(data, 2, sampleRates[i], 8, EMediaDataEndianLittle, 0);
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
        msgbd[i] = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, bitDepths[i], EMediaDataEndianLittle, 0);
    }
    TEST(msgbd[0]->Jiffies() == 2 * msgbd[1]->Jiffies());
    TEST(msgbd[0]->Jiffies() == 3 * msgbd[2]->Jiffies());
    for (TUint i=0; i<numBitDepths; i++) {
        msgbd[i]->RemoveRef();
    }

    // Split pcm msg.  Check lengths of both parts are as expected.
    msg = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataEndianLittle, Jiffies::kPerSecond);
    static const TUint kSplitPos = 800;
    jiffies = msg->Jiffies();
    MsgAudio* remaining = msg->Split(kSplitPos);
    TEST(remaining != nullptr);
    TUint newJiffies = msg->Jiffies();
    TUint remainingJiffies = remaining->Jiffies();
    remaining->RemoveRef();
    TEST(newJiffies > 0);
    TEST(remainingJiffies > 0);
    TEST(newJiffies < jiffies);
    TEST(remainingJiffies < jiffies);
    TEST(newJiffies + remainingJiffies == jiffies);
    TEST(static_cast<MsgAudioPcm*>(msg)->TrackOffset() == Jiffies::kPerSecond);
    TEST(static_cast<MsgAudioPcm*>(remaining)->TrackOffset() == static_cast<MsgAudioPcm*>(msg)->TrackOffset() + msg->Jiffies());

    // Split pcm msg at invalid positions (0, > Jiffies()).  Check these assert.
    TEST_THROWS(remaining = msg->Split(0), AssertionFailed);
    TEST_THROWS(remaining = msg->Split(msg->Jiffies()), AssertionFailed);
    TEST_THROWS(remaining = msg->Split(msg->Jiffies()+1), AssertionFailed);

    // Clone pcm msg.  Check lengths of clone & parent match
    MsgAudio* clone = msg->Clone();
    jiffies = clone->Jiffies();
    TEST(jiffies == msg->Jiffies());
    TEST(static_cast<MsgAudioPcm*>(msg)->TrackOffset() == static_cast<MsgAudioPcm*>(clone)->TrackOffset());
    msg->RemoveRef();
    // confirm clone is usable after parent is destroyed
    TEST(jiffies == clone->Jiffies());
    clone->RemoveRef();

    // Add 2 msgs.  Check their combined lengths are reported
    msg = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataEndianLittle, Jiffies::kPerSecond);
    clone = msg->Clone();
    jiffies = msg->Jiffies();
    TUint combinedJiffies = msg->Jiffies() + clone->Jiffies();
    msg->Add(clone);
    TEST(msg->Jiffies() == combinedJiffies);
    // split inside clone
    remaining = msg->Split(jiffies + 100);
    TEST(msg->Jiffies() == jiffies + 100);
    TEST(remaining->Jiffies() == combinedJiffies - (jiffies + 100));
    // confirm clone is destroyed along with msg
    msg->RemoveRef();
    TEST(clone->Jiffies() == 0);
    remaining->RemoveRef();
    TEST(remaining->Jiffies() == 0);

    // Add 2 msgs.  Split at their boundary.
    msg = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataEndianLittle, Jiffies::kPerMs * 5);
    MsgAudioPcm* msg2 = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataEndianLittle, Jiffies::kPerMs * 2);
    jiffies = msg->Jiffies();
    msg->Add(msg2);
    MsgAudio* split = msg->Split(jiffies);
    TEST(msg->Jiffies() == jiffies);
    TEST(split->Jiffies() == msg2->Jiffies());
    msg->RemoveRef();
    msg2->RemoveRef();

    // Aggregate 2 msgs. Check their combined lengths are reported.
    static const TUint dataSizeHalfDecodedAudio = DecodedAudio::kMaxBytes/2;
    static const TUint secondOffsetSamples = dataSizeHalfDecodedAudio / 2; // iBitDepth = 8 bits = 1 byte
    static const TUint secondsOffsetJiffies = Jiffies::JiffiesPerSample(44100) * secondOffsetSamples;
    Bwh data1(dataSizeHalfDecodedAudio, dataSizeHalfDecodedAudio);
    (void)memset((void*)data1.Ptr(), 0x01, data1.Bytes());
    Bwh data2(dataSizeHalfDecodedAudio, dataSizeHalfDecodedAudio);
    (void)memset((void*)data2.Ptr(), 0x02, data2.Bytes());

    MsgAudioPcm* msgAggregate1 = iMsgFactory->CreateMsgAudioPcm(data1, 2, 44100, 8, EMediaDataEndianLittle, 0);
    MsgAudioPcm* msgAggregate2 = iMsgFactory->CreateMsgAudioPcm(data2, 2, 44100, 8, EMediaDataEndianLittle, secondsOffsetJiffies);
    TUint expectedJiffiesAggregated = msgAggregate1->Jiffies() + msgAggregate2->Jiffies();
    msgAggregate1->Aggregate(msgAggregate2); // ref is removed
    TEST(msgAggregate1->Jiffies() == expectedJiffiesAggregated);

    // Check underlying DecodedAudio was also combined (i.e. check that MsgAudioPcm->iSize wasn't just updated).
    MsgPlayable* aggregatedPlayable = msgAggregate1->CreatePlayable();
    TEST(aggregatedPlayable->Bytes() == dataSizeHalfDecodedAudio*2);
    ProcessorPcmBufTest pcmProcessor;
    aggregatedPlayable->Read(pcmProcessor);
    aggregatedPlayable->RemoveRef();
    const TByte* ptr = pcmProcessor.Ptr();
    TUint subsampleVal = 0x01;
    for (TUint i=0; i<data1.Bytes(); i++) {
        TEST(*ptr == subsampleVal);
        ptr++;
    }
    subsampleVal = 0x02;
    for (TUint i=data1.Bytes(); i<data1.Bytes()+data2.Bytes(); i++) {
        TEST(*ptr == subsampleVal);
        ptr++;
    }

    // Try aggregate two msgs with different: #channels
    msgAggregate1 = iMsgFactory->CreateMsgAudioPcm(data1, 2, 44100, 8, EMediaDataEndianLittle, 0);
    msgAggregate2 = iMsgFactory->CreateMsgAudioPcm(data2, 1, 44100, 8, EMediaDataEndianLittle, secondsOffsetJiffies);
    TEST_THROWS(msgAggregate1->Aggregate(msgAggregate2), AssertionFailed);
    msgAggregate1->RemoveRef();
    msgAggregate2->RemoveRef();

    // Try aggregate two msgs with different: sample rate
    msgAggregate1 = iMsgFactory->CreateMsgAudioPcm(data1, 2, 44100, 8, EMediaDataEndianLittle, 0);
    msgAggregate2 = iMsgFactory->CreateMsgAudioPcm(data2, 2, 48000, 8, EMediaDataEndianLittle, secondsOffsetJiffies);
    TEST_THROWS(msgAggregate1->Aggregate(msgAggregate2), AssertionFailed);
    msgAggregate1->RemoveRef();
    msgAggregate2->RemoveRef();

    // Try aggregate two msgs with different: bit depth
    msgAggregate1 = iMsgFactory->CreateMsgAudioPcm(data1, 2, 44100, 8, EMediaDataEndianLittle, 0);
    msgAggregate2 = iMsgFactory->CreateMsgAudioPcm(data2, 2, 44100, 16, EMediaDataEndianLittle, secondsOffsetJiffies);
    TEST_THROWS(msgAggregate1->Aggregate(msgAggregate2), AssertionFailed);
    msgAggregate1->RemoveRef();
    msgAggregate2->RemoveRef();

    // Try aggregate two msgs, where one has a ramp set
    msgAggregate1 = iMsgFactory->CreateMsgAudioPcm(data1, 2, 44100, 8, EMediaDataEndianLittle, 0);
    msgAggregate2 = iMsgFactory->CreateMsgAudioPcm(data2, 2, 44100, 8, EMediaDataEndianLittle, secondsOffsetJiffies);
    TUint rampRemaining = Ramp::kMax;
    MsgAudio* msgRemaining = nullptr;
    msgAggregate2->SetRamp(0, rampRemaining, Ramp::EUp, msgRemaining);
    TEST_THROWS(msgAggregate1->Aggregate(msgAggregate2), AssertionFailed);
    msgAggregate1->RemoveRef();
    msgAggregate2->RemoveRef();

    // Try aggregate two msgs that will overflow underlying DecodedAudio
    Bwh data3(dataSizeHalfDecodedAudio*2, dataSizeHalfDecodedAudio*2);
    (void)memset((void*)data3.Ptr(), 0x03, data3.Bytes());
    msgAggregate1 = iMsgFactory->CreateMsgAudioPcm(data1, 2, 44100, 8, EMediaDataEndianLittle, 0);
    msgAggregate2 = iMsgFactory->CreateMsgAudioPcm(data3, 2, 44100, 8, EMediaDataEndianLittle, secondsOffsetJiffies);

    TEST_THROWS(msgAggregate1->Aggregate(msgAggregate2), AssertionFailed);
    msgAggregate1->RemoveRef();
    msgAggregate2->RemoveRef();

    // Try aggregate two msgs, where one has a msg chain
    Bwh data4(dataSizeHalfDecodedAudio/2, dataSizeHalfDecodedAudio/2);
    (void)memset((void*)data4.Ptr(), 0x04, data4.Bytes());
    msgAggregate1 = iMsgFactory->CreateMsgAudioPcm(data1, 2, 44100, 8, EMediaDataEndianLittle, 0);
    msgAggregate2 = iMsgFactory->CreateMsgAudioPcm(data4, 2, 44100, 8, EMediaDataEndianLittle, secondsOffsetJiffies);
    MsgAudioPcm* msgChained = iMsgFactory->CreateMsgAudioPcm(data4, 2, 44100, 8, EMediaDataEndianLittle, secondsOffsetJiffies);
    msgAggregate2->Add(msgChained);
    TEST_THROWS(msgAggregate1->Aggregate(msgAggregate2), AssertionFailed);
    msgAggregate1->RemoveRef();
    msgAggregate2->RemoveRef();

    // Check creating zero-length msg asserts
    TEST_THROWS(iMsgFactory->CreateMsgAudioPcm(Brx::Empty(), 2, 44100, 8, EMediaDataEndianLittle, 0), AssertionFailed);

    // Create silence msg.  Check its length is as expected
    jiffies = Jiffies::kPerMs;
    msg = iMsgFactory->CreateMsgSilence(jiffies);
    TEST(jiffies == msg->Jiffies());

    // Split silence msg.  Check lengths of both parts are as expected.
    remaining = msg->Split(jiffies/4);
    TEST(remaining != nullptr);
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

    // MsgSilence needs to take a pointer to its iAllocatorPlayable when cloning.
    // As we don't have access to iAllocatorPlayable, try calling CreatePlayable(),
    // which should fail if iAllocatorPlayable hasn't been assigned.
    MsgPlayable* playable = static_cast<MsgSilence*>(clone)->CreatePlayable(44100, 16, 2); // removes ref from clone
    msg->RemoveRef();
    playable->RemoveRef();

    // clean destruction of class implies no leaked msgs
}


// SuiteMsgPlayable

SuiteMsgPlayable::SuiteMsgPlayable()
    : Suite("Basic MsgPlayable tests")
{
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(kMsgCount, kMsgCount);
    init.SetMsgSilenceCount(kMsgCount);
    init.SetMsgPlayableCount(kMsgCount, kMsgCount);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
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
        audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, sampleRates[i], 8, EMediaDataEndianLittle, 0);
        playable = audioPcm->CreatePlayable();
        bytes = playable->Bytes();
        playable->RemoveRef();
        if (prevBytes != 0) {
            TEST(prevBytes == bytes);
        }
        prevBytes = bytes;
    }

    // Create pcm msg.  Read/validate its content
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataEndianLittle, 0);
    playable = audioPcm->CreatePlayable();
    TEST(playable->Bytes() == data.Bytes());
    ProcessorPcmBufTest pcmProcessor;
    playable->Read(pcmProcessor);
    playable->RemoveRef();
    const TByte* ptr = pcmProcessor.Ptr();
    TUint subsampleVal = 0xff;
    for (TUint i=0; i<data.Bytes(); i++) {
        TEST(*ptr == subsampleVal);
        ptr++;
        subsampleVal--;
    }

    // Create multiple pcm msgs, then add together. Check content.
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataEndianLittle, 0);
    MsgAudioPcm* audioPcm2 = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataEndianLittle, 0);
    audioPcm->Add(audioPcm2);
    playable = audioPcm->CreatePlayable();
    TEST(playable->Bytes() == data.Bytes()*2);
    playable->Read(pcmProcessor);
    playable->RemoveRef();
    ptr = pcmProcessor.Ptr();
    subsampleVal = 0xff;
    // first half of msg
    for (TUint i=0; i<data.Bytes(); i++) {
        TEST(*ptr == subsampleVal);
        ptr++;
        subsampleVal--;
    }
    // second half of msg
    subsampleVal = 0xff;
    for (TUint i=0; i<data.Bytes(); i++) {
        TEST(*ptr == subsampleVal);
        ptr++;
        subsampleVal--;
    }

    // Create pcm msg, split it then convert to playable.  Read/validate contents of both
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataEndianLittle, 0);
    MsgAudioPcm* remainingPcm = (MsgAudioPcm*)audioPcm->Split(audioPcm->Jiffies()/4);
    playable = audioPcm->CreatePlayable();
    MsgPlayable* remainingPlayable = remainingPcm->CreatePlayable();
    TEST(remainingPlayable->Bytes() == 3 * playable->Bytes());
    playable->Read(pcmProcessor);
    playable->RemoveRef();
    subsampleVal = 0xff;
    Brn buf(pcmProcessor.Buf());
    ptr = buf.Ptr();
    for (TUint i=0; i<buf.Bytes(); i++) {
        TEST(*ptr == subsampleVal);
        ptr++;
        subsampleVal--;
    }
    remainingPlayable->Read(pcmProcessor);
    remainingPlayable->RemoveRef();
    buf.Set(pcmProcessor.Buf());
    ptr = buf.Ptr();
    for (TUint i=0; i<buf.Bytes(); i++) {
        TEST(*ptr == subsampleVal);
        ptr++;
        subsampleVal--;
    }

    // Create pcm msg, convert to playable then split.  Read/validate contents of both
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataEndianLittle, 0);
    playable = audioPcm->CreatePlayable();
    remainingPlayable = playable->Split(playable->Bytes()/4);
    TEST(remainingPlayable->Bytes() == 3 * playable->Bytes());
    playable->Read(pcmProcessor);
    playable->RemoveRef();
    buf.Set(pcmProcessor.Buf());
    ptr = buf.Ptr();
    subsampleVal = 0xff;
    for (TUint i=0; i<buf.Bytes(); i++) {
        TEST(*ptr == subsampleVal);
        ptr++;
        subsampleVal--;
    }
    remainingPlayable->Read(pcmProcessor);
    remainingPlayable->RemoveRef();
    buf.Set(pcmProcessor.Buf());
    ptr = buf.Ptr();
    for (TUint i=0; i<buf.Bytes(); i++) {
        TEST(*ptr == subsampleVal);
        ptr++;
        subsampleVal--;
    }

    // Create pcm msg, split at non-sample boundary.  Read/validate contents of each fragment
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataEndianLittle, 0);
    remainingPcm = (MsgAudioPcm*)audioPcm->Split((audioPcm->Jiffies()/4) - 1);
    playable = audioPcm->CreatePlayable();
    remainingPlayable = remainingPcm->CreatePlayable();
    playable->Read(pcmProcessor);
    playable->RemoveRef();
    buf.Set(pcmProcessor.Buf());
    ptr = buf.Ptr();
    subsampleVal = 0xff;
    for (TUint i=0; i<buf.Bytes(); i++) {
        TEST(*ptr == subsampleVal);
        ptr++;
        subsampleVal--;
    }
    remainingPlayable->Read(pcmProcessor);
    remainingPlayable->RemoveRef();
    buf.Set(pcmProcessor.Buf());
    ptr = buf.Ptr();
    for (TUint i=0; i<buf.Bytes(); i++) {
        TEST(*ptr == subsampleVal);
        ptr++;
        subsampleVal--;
    }

    // Create pcm msg, split at 1 jiffy (non-sample boundary).  Check initial msg has 0 Bytes() but can Write() its content
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataEndianLittle, 0);
    remainingPcm = (MsgAudioPcm*)audioPcm->Split(1);
    playable = audioPcm->CreatePlayable();
    remainingPlayable = remainingPcm->CreatePlayable();
    playable->Read(pcmProcessor);
    playable->RemoveRef();
    buf.Set(pcmProcessor.Buf());
    TEST(buf.Bytes() == 0);
    remainingPlayable->Read(pcmProcessor);
    remainingPlayable->RemoveRef();
    buf.Set(pcmProcessor.Buf());
    TEST(buf.Bytes() == data.Bytes());

    // Test splitting at the end of a message returns nullptr
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataEndianLittle, 0);
    playable = audioPcm->CreatePlayable();
    TEST(nullptr == playable->Split(playable->Bytes()));
    playable->RemoveRef();

    // Split pcm msg at invalid positions (0, > Jiffies()).  Check these assert.
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataEndianLittle, 0);
    playable = audioPcm->CreatePlayable();
    TEST_THROWS(remainingPlayable = playable->Split(0), AssertionFailed);
    TEST_THROWS(remainingPlayable = playable->Split(playable->Bytes()+1), AssertionFailed);
    playable->RemoveRef();

    // For each sample rate, create a silence msg using the same size
    // Convert to MsgPlayable; check Bytes() increase as sample rates increase
    prevBytes = 0;
    MsgSilence* silence;
    for (TUint i=0; i<numRates; i++) {
        silence = iMsgFactory->CreateMsgSilence(Jiffies::kPerMs * 5);
        playable = silence->CreatePlayable(sampleRates[i], 8, 2);
        bytes = playable->Bytes();
        playable->RemoveRef();
        if (prevBytes != 0) {
            TEST(prevBytes < bytes);
        }
        prevBytes = bytes;
    }

    // Create silence msg.  Read/validate its content
    silence = iMsgFactory->CreateMsgSilence(Jiffies::kPerMs);
    playable = silence->CreatePlayable(44100, 8, 1);
    bytes = playable->Bytes();
    ValidateSilence(playable);

    // Create silence msg, convert to playable then split.  Check sizes/contents of each
    silence = iMsgFactory->CreateMsgSilence(Jiffies::kPerMs);
    playable = silence->CreatePlayable(44100, 8, 1);
    remainingPlayable = playable->Split(playable->Bytes() / 4);
    TEST(3 * playable->Bytes() == remainingPlayable->Bytes());
    TEST(playable->Bytes() + remainingPlayable->Bytes() == bytes);
    ValidateSilence(playable);
    ValidateSilence(remainingPlayable);

    // Create silence msg, split at non-sample boundary.  Check that fragments have the correct total length
    silence = iMsgFactory->CreateMsgSilence(Jiffies::kPerMs);
    playable = silence->CreatePlayable(44100, 8, 1);
    remainingPlayable = playable->Split((playable->Bytes() / 4) - 1);
    TEST(playable->Bytes() + remainingPlayable->Bytes() == bytes);
    playable->RemoveRef();
    remainingPlayable->RemoveRef();

    // Create silence msg, split at 1 jiffy (non-sample boundary).  Check initial msg has 0 Bytes() but can Write() its content
    silence = iMsgFactory->CreateMsgSilence(Jiffies::kPerMs);
    MsgSilence* remainingSilence = (MsgSilence*)silence->Split(1);
    playable = silence->CreatePlayable(44100, 8, 1);
    remainingPlayable = remainingSilence->CreatePlayable(44100, 8, 1);
    TEST(playable->Bytes() == 0);
    TEST(remainingPlayable->Bytes() == bytes);
    ValidateSilence(playable);
    remainingPlayable->RemoveRef();

    // check we can read from a chained PlayablePcm -> PlayableSilence
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataEndianLittle, 0);
    playable = audioPcm->CreatePlayable();
    silence = iMsgFactory->CreateMsgSilence(Jiffies::kPerMs);
    playable->Add(silence->CreatePlayable(44100, 8, 1));
    playable->Read(pcmProcessor);
    playable->RemoveRef();

    // clean destruction of class implies no leaked msgs
}

void SuiteMsgPlayable::ValidateSilence(MsgPlayable* aMsg)
{
    TUint bytes = aMsg->Bytes();
    ProcessorPcmBufTest pcmProcessor;
    aMsg->Read(pcmProcessor);
    aMsg->RemoveRef();
    const TByte* ptr = pcmProcessor.Ptr();
    for (TUint i=0; i<bytes; i++) {
        TEST(ptr[i] == 0);
    }
}


// SuiteRamp

SuiteRamp::SuiteRamp()
    : Suite("Ramp tests")
{
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(kMsgCount, kMsgCount);
    init.SetMsgSilenceCount(kMsgCount);
    init.SetMsgPlayableCount(kMsgCount, kMsgCount);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
}

SuiteRamp::~SuiteRamp()
{
    delete iMsgFactory;
}

void SuiteRamp::Test()
{
    TUint jiffies = Jiffies::kPerMs;

    // start=Ramp::kMax, direction=down, duration=fragmentSize.  Apply, check end is Ramp::kMin
    Ramp ramp;
    Ramp split;
    TUint splitPos;
    TEST(!ramp.Set(Ramp::kMax, jiffies, jiffies, Ramp::EDown, split, splitPos));
    TEST(ramp.Start() == Ramp::kMax);
    TEST(ramp.End() == Ramp::kMin);
    TEST(ramp.Direction() == Ramp::EDown);

    // start=Ramp::kMax, direction=up, duration=fragmentSize.  Check asserts as invalid to ramp up beyond max
    ramp.Reset();
    TEST_THROWS(ramp.Set(Ramp::kMax, jiffies, jiffies, Ramp::EUp, split, splitPos), AssertionFailed);

    // start=Ramp::kMin, direction=up, duration=fragmentSize.  Apply, check end is Ramp::kMax
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kMin, jiffies, jiffies, Ramp::EUp, split, splitPos));
    TEST(ramp.Start() == Ramp::kMin);
    TEST(ramp.End() == Ramp::kMax);
    TEST(ramp.Direction() == Ramp::EUp);

    // start=Ramp::kMax, direction=down, duration=2*fragmentSize.  Apply, check end is 50%
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kMax, jiffies, 2*jiffies, Ramp::EDown, split, splitPos));
    TEST(ramp.Start() == Ramp::kMax);
    TEST(ramp.End() == (Ramp::kMax - Ramp::kMin) / 2);
    TEST(ramp.Direction() == Ramp::EDown);

    // start=Ramp::kMin, direction=up, duration=2*fragmentSize.  Apply, check end is 50%
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kMin, jiffies, 2*jiffies, Ramp::EUp, split, splitPos));
    TEST(ramp.Start() == Ramp::kMin);
    TEST(ramp.End() == (Ramp::kMax - Ramp::kMin) / 2);
    TEST(ramp.Direction() == Ramp::EUp);

    // start=50%, direction=down, duration=4*fragmentSize (so remainingDuration=2*fragmentSize).  Apply, check end is 25%
    ramp.Reset();
    TUint start = (Ramp::kMax - Ramp::kMin) / 2;
    TEST(!ramp.Set(start, jiffies, 2*jiffies, Ramp::EDown, split, splitPos));
    TEST(ramp.Start() == start);
    TEST(ramp.End() == (Ramp::kMax - Ramp::kMin) / 4);
    TEST(ramp.Direction() == Ramp::EDown);

    // start=50%, direction=up, duration=4*fragmentSize (so remainingDuration=2*fragmentSize).  Apply, check end is 75%
    ramp.Reset();
    start = (Ramp::kMax - Ramp::kMin) / 2;
    TEST(!ramp.Set(start, jiffies, 2*jiffies, Ramp::EUp, split, splitPos));
    TEST(ramp.Start() == start);
    TEST(ramp.End() == Ramp::kMax - ((Ramp::kMax - Ramp::kMin) / 4));
    TEST(ramp.Direction() == Ramp::EUp);

    // Apply ramp [Max...Min].  Check start/end values and that subsequent values never rise
//    const TUint kNumChannels = 2;
    const TUint kAudioDataSize = 804;
    TByte audioData[kAudioDataSize];
    (void)memset(audioData, 0x7f, kAudioDataSize);
    Brn audioBuf(audioData, kAudioDataSize);

    ramp.Reset();
    TEST(!ramp.Set(Ramp::kMax, kAudioDataSize, kAudioDataSize, Ramp::EDown, split, splitPos));
    RampApplicator applicator(ramp);
    TUint prevSampleVal = 0x7f, sampleVal = 0;
    TByte sample[DecodedAudio::kMaxNumChannels * 3];
    TUint numSamples = applicator.Start(audioBuf, 8, 2);
    for (TUint i=0; i<numSamples; i++) {
        applicator.GetNextSample(sample);
        sampleVal = sample[0];
        if (i==0) {
            TEST(sampleVal >= 0x7d); // test that start of ramp is close to initial value
        }
        TEST(sampleVal == sample[1]);
        TEST(prevSampleVal >= sampleVal);
        prevSampleVal = sampleVal;
    }
    TEST(sampleVal == 0);

    // Repeat the above test, but for 16-bit subsamples
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kMax, kAudioDataSize, kAudioDataSize, Ramp::EDown, split, splitPos));
    prevSampleVal = 0x7f7f;
    numSamples = applicator.Start(audioBuf, 16, 2);
    for (TUint i=0; i<numSamples; i++) {
        applicator.GetNextSample(sample);
        sampleVal = (sample[0]<<8) | sample[1];
        TEST(sampleVal == (TUint)(sample[2]<<8 | sample[3]));
        TEST(prevSampleVal >= sampleVal);
        prevSampleVal = sampleVal;
    }

    // Repeat the above test, but for 24-bit subsamples
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kMax, kAudioDataSize, kAudioDataSize, Ramp::EDown, split, splitPos));
    prevSampleVal = 0x7f7f7f;
    numSamples = applicator.Start(audioBuf, 24, 2);
    for (TUint i=0; i<numSamples; i++) {
        applicator.GetNextSample(sample);
        sampleVal = (sample[0]<<16) | (sample[1]<<8) | sample[2];
        TEST(sampleVal == (TUint)((sample[3]<<16) | (sample[4]<<8) | sample[5]));
        TEST(prevSampleVal >= sampleVal);
        prevSampleVal = sampleVal;
    }

    // Apply ramp [Min...Max].  Check start/end values and that subsequent values never fall
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kMin, kAudioDataSize, kAudioDataSize, Ramp::EUp, split, splitPos));
    prevSampleVal = 0;
    numSamples = applicator.Start(audioBuf, 8, 2);
    for (TUint i=0; i<numSamples; i++) {
        applicator.GetNextSample(sample);
        sampleVal = sample[0];
        if (i==0) {
            TEST(sampleVal <= 0x02); // test that start of ramp is close to zero
        }
        TEST(sampleVal == sample[1]);
        TEST(prevSampleVal <= sampleVal);
        prevSampleVal = sampleVal;
    }
    TEST(sampleVal >= 0x7d); // test that end of ramp is close to max

    // Apply ramp [Max...50%].  Check start/end values
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kMax, kAudioDataSize, kAudioDataSize*2, Ramp::EDown, split, splitPos));
    prevSampleVal = 0;
    numSamples = applicator.Start(audioBuf, 8, 2);
    for (TUint i=0; i<numSamples; i++) {
        applicator.GetNextSample(sample);
        sampleVal = sample[0];
        if (i==0) {
            TEST(sampleVal >= 0x7d); // test that start of ramp is close to max
        }
    }
    TUint endValGuess = (((TUint64)0x7f * kRampArray[256])>>31);
    TEST(endValGuess - sampleVal <= 0x02);

    // Apply ramp [Min...50%].  Check start/end values
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kMin, kAudioDataSize, kAudioDataSize*2, Ramp::EUp, split, splitPos));
    prevSampleVal = 0;
    numSamples = applicator.Start(audioBuf, 8, 2);
    for (TUint i=0; i<numSamples; i++) {
        applicator.GetNextSample(sample);
        sampleVal = sample[0];
        if (i==0) {
            TEST(sampleVal <= 0x02); // test that start of ramp is close to zero
        }
    }
    endValGuess = (((TUint64)0x7f * kRampArray[256])>>31);
    TEST(endValGuess - sampleVal <= 0x02);

    // Apply ramp [50%...25%].  Check start/end values
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kMax / 2, kAudioDataSize, kAudioDataSize*2, Ramp::EDown, split, splitPos));
    prevSampleVal = 0;
    numSamples = applicator.Start(audioBuf, 8, 2);
    for (TUint i=0; i<numSamples; i++) {
        applicator.GetNextSample(sample);
        sampleVal = sample[0];
        if (i==0) {
            TUint startValGuess = (((TUint64)0x7f * kRampArray[256])>>31);
            TEST(startValGuess - sampleVal < 0x02);
        }
    }
    endValGuess = (((TUint64)0x7f * kRampArray[384])>>31);
    TEST(endValGuess - sampleVal <= 0x02);

    // Create [50%...Min] ramp.  Add [Min...50%] ramp.  Check this splits into [Min...25%], [25%...Min]
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kMax / 2, jiffies, jiffies, Ramp::EDown, split, splitPos));
    TEST(ramp.Set(Ramp::kMin, jiffies, 2 * jiffies, Ramp::EUp, split, splitPos));
    TEST(ramp.Start() == 0);
    TEST(ramp.End() == Ramp::kMax / 4);
    TEST(ramp.Direction() == Ramp::EUp);
    TEST(split.Start() == ramp.End());
    TEST(split.End() == 0);
    TEST(split.Direction() == Ramp::EDown);
    TEST(ramp.IsEnabled());
    TEST(split.IsEnabled());

    // Create [50%...25%] ramp.  Add [70%...30%] ramp.  Check original ramp is retained.
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kMax / 2, jiffies, 4 * jiffies, Ramp::EDown, split, splitPos));
    start = ramp.Start();
    TUint end = ramp.End();
    Ramp::EDirection direction = ramp.Direction();
    TEST(!ramp.Set(((TUint64)10 * Ramp::kMax) / 7, jiffies, (5 * jiffies) / 2, Ramp::EDown, split, splitPos));
    TEST(ramp.Start() == start);
    TEST(ramp.End() == end);
    TEST(ramp.Direction() == direction);

    // Create [50%...25%] ramp.  Add [40%...Min] ramp.  Check new ramp is used.
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kMax / 2, jiffies, 2 * jiffies, Ramp::EDown, split, splitPos));
    start = ramp.Start();
    start = ((TUint64)2 * Ramp::kMax) / 5;
    TEST(!ramp.Set(start, jiffies, jiffies, Ramp::EDown, split, splitPos));
    TEST(ramp.Start() == start);
    TEST(ramp.End() == 0);
    TEST(ramp.Direction() == Ramp::EDown);

    // Create MsgSilence.  Set [Max...Min] ramp.  Convert to playable and check output is all zeros
    MsgSilence* silence = iMsgFactory->CreateMsgSilence(jiffies);
    MsgAudio* remaining = nullptr;
    TEST(Ramp::kMin == silence->SetRamp(Ramp::kMax, jiffies, Ramp::EDown, remaining));
    TEST(remaining == nullptr);
    MsgPlayable* playable = silence->CreatePlayable(44100, 8, 2);
    TEST(playable != nullptr);
    ProcessorPcmBufTest pcmProcessor;
    playable->Read(pcmProcessor);
    const TByte* ptr = pcmProcessor.Ptr();
    for (TUint i=0; i<playable->Bytes(); i++) {
        TEST(*ptr == 0);
        ptr++;
    }
    playable->RemoveRef();

    // Create MsgAudioPcm.  Set [50%...Min] ramp.  Add [Min...50%] ramp.  Convert to playable and check output
    const TUint kEncodedAudioSize = 768;
    TByte encodedAudioData[kEncodedAudioSize];
    (void)memset(encodedAudioData, 0x7f, kEncodedAudioSize);
    Brn encodedAudio(encodedAudioData, kEncodedAudioSize);
    const TUint kNumChannels = 2;
    MsgAudioPcm* audioPcm = iMsgFactory->CreateMsgAudioPcm(encodedAudio, kNumChannels, 44100, 16, EMediaDataEndianLittle, 0);
    jiffies = audioPcm->Jiffies();
    TUint remainingDuration = jiffies;
    TEST(Ramp::kMin == audioPcm->SetRamp(Ramp::kMax / 2, remainingDuration, Ramp::EDown, remaining));
    remainingDuration = jiffies * 2;
    TEST(Ramp::kMin != audioPcm->SetRamp(Ramp::kMin, remainingDuration, Ramp::EUp, remaining));
    TEST(remaining != nullptr);
    TEST(remaining->Ramp().IsEnabled());
    TEST(remaining->Ramp().End() == Ramp::kMin);
    TEST(audioPcm->Jiffies() == jiffies / 2);
    TEST(audioPcm->Jiffies() == remaining->Jiffies());
    playable = audioPcm->CreatePlayable();
    playable->Read(pcmProcessor);
    playable->RemoveRef();
    ptr = pcmProcessor.Ptr();
    TUint bytes = pcmProcessor.Buf().Bytes();
    prevSampleVal = 0;
    TEST(((ptr[0]<<8) | ptr[1]) == 0);
    for (TUint i=0; i<bytes; i+=4) {
        sampleVal = (TUint)((ptr[i]<<8) | ptr[i+1]);
        TEST(sampleVal == (TUint)((ptr[i+2]<<8) | ptr[i+3]));
        if (i > 0) {
            TEST(prevSampleVal <= sampleVal);
        }
        prevSampleVal = sampleVal;
    }
    playable = ((MsgAudioPcm*)remaining)->CreatePlayable();
    playable->Read(pcmProcessor);
    playable->RemoveRef();
    ptr = pcmProcessor.Ptr();
    bytes = pcmProcessor.Buf().Bytes();
    TEST(((ptr[bytes-2]<<8) | ptr[bytes-1]) == 0);
    for (TUint i=0; i<bytes; i+=4) {
        sampleVal = (TUint)((ptr[i]<<8) | ptr[i+1]);
        TEST(sampleVal == (TUint)((ptr[i+2]<<8) | ptr[i+3]));
        if (i > 0) {
            TEST(prevSampleVal >= sampleVal);
        }
        prevSampleVal = sampleVal;
    }

    // Create 2 MsgSilences with different durations.
    // Check can ramp down over them (i.e. there is no rounding error at msg boundary)
    silence = iMsgFactory->CreateMsgSilence(Jiffies::kPerMs * 17);
    MsgSilence* silence2 = iMsgFactory->CreateMsgSilence(Jiffies::kPerMs * 23);
    const TUint duration = silence->Jiffies() + silence2->Jiffies();
    remainingDuration = duration;
    TUint currentRamp = Ramp::kMax;
    currentRamp = silence->SetRamp(currentRamp, remainingDuration, Ramp::EDown, remaining);
    currentRamp = silence2->SetRamp(currentRamp, remainingDuration, Ramp::EDown, remaining);
    TEST(currentRamp == Ramp::kMin);
    silence->RemoveRef();
    silence2->RemoveRef();

    // see #3118
    ramp.Reset();
    ramp.iStart = 0x3529a489;
    ramp.iEnd = 0x35cd7b93;
    ramp.iDirection = Ramp::EUp;
    ramp.iEnabled = true;
    ramp.Set(0x33cf3a6c, 0x00044e80, 0x0009c300, Ramp::EDown, split, splitPos); // asserts

    // muted ramp
    ramp.Reset();
    ramp.SetMuted();
    TEST(ramp.Direction() == Ramp::EMute);
    TEST(ramp.Start() == Ramp::kMin);
    TEST(ramp.End() == Ramp::kMin);

    audioPcm = iMsgFactory->CreateMsgAudioPcm(encodedAudio, 1, 44100, 8, EMediaDataEndianLittle, 0);
    audioPcm->SetMuted();
    remainingDuration = Jiffies::kPerMs * 20;
    audioPcm->SetRamp(Ramp::kMax, remainingDuration, Ramp::EDown, remaining);
    playable = audioPcm->CreatePlayable();
    playable->Read(pcmProcessor);
    playable->RemoveRef();
    ptr = pcmProcessor.Ptr();
    bytes = pcmProcessor.Buf().Bytes();
    for (TUint i=0; i<bytes; i++) {
        TEST(*ptr++ == 0);
    }

    audioPcm = iMsgFactory->CreateMsgAudioPcm(encodedAudio, 1, 44100, 8, EMediaDataEndianLittle, 0);
    remainingDuration = Jiffies::kPerMs * 20;
    audioPcm->SetRamp(Ramp::kMax, remainingDuration, Ramp::EDown, remaining);
    audioPcm->SetMuted();
    playable = audioPcm->CreatePlayable();
    playable->Read(pcmProcessor);
    playable->RemoveRef();
    ptr = pcmProcessor.Ptr();
    bytes = pcmProcessor.Buf().Bytes();
    for (TUint i=0; i<bytes; i++) {
        TEST(*ptr++ == 0);
    }
}


// SuiteAudioStream

SuiteAudioStream::SuiteAudioStream()
    : Suite("MsgEncodedStream tests")
{
    MsgFactoryInitParams init;
    init.SetMsgEncodedStreamCount(kMsgEncodedStreamCount);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
}

SuiteAudioStream::~SuiteAudioStream()
{
    delete iMsgFactory;
}

void SuiteAudioStream::Test()
{
    // create MetaText msg, check its data can be retrieved
    Brn uri("http://255.1.33.76:8734/path?query");
    Brn metaText("metaText");
    TUint totalBytes = 1234;
    TUint streamId = 8;
    TBool seekable = true;
    TBool live = true;
    MsgEncodedStream* msg = iMsgFactory->CreateMsgEncodedStream(uri, metaText, totalBytes, streamId, seekable, live, nullptr);
    TEST(msg != nullptr);
    TEST(msg->Uri() == uri);
    TEST(msg->MetaText() == metaText);
    TEST(msg->TotalBytes() == totalBytes);
    TEST(msg->StreamId() == streamId);
    TEST(msg->Seekable() == seekable);
    TEST(msg->Live() == live);
    TEST(msg->StreamHandler() == nullptr);
    msg->RemoveRef();

#ifdef DEFINE_DEBUG
    // access freed msg (doesn't bother valgrind as this is still allocated memory).  Check text has been cleared.
    TEST(msg->Uri() != uri);
    TEST(msg->MetaText() != metaText);
    TEST(msg->TotalBytes() != totalBytes);
    TEST(msg->StreamId() != streamId);
    TEST(msg->Seekable() != seekable);
    TEST(msg->Live() != live);
    TEST(msg->StreamHandler() == nullptr);
#endif

    // create second MetaText msg, check its data can be retrieved
    uri.Set("http://3.4.5.6:8");
    metaText.Set("updated");
    totalBytes = 65537;
    streamId = 99;
    seekable = false;
    live = false;
    msg = iMsgFactory->CreateMsgEncodedStream(uri, metaText, totalBytes, streamId, seekable, live, nullptr);
    TEST(msg != nullptr);
    TEST(msg->Uri() == uri);
    TEST(msg->MetaText() == metaText);
    TEST(msg->TotalBytes() == totalBytes);
    TEST(msg->StreamId() == streamId);
    TEST(msg->Seekable() == seekable);
    TEST(msg->Live() == live);
    TEST(msg->StreamHandler() == nullptr);
    msg->RemoveRef();
}


// SuiteMetaText

SuiteMetaText::SuiteMetaText()
    : Suite("MsgMetaText tests")
{
    MsgFactoryInitParams init;
    init.SetMsgMetaTextCount(kMsgMetaTextCount);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
}

SuiteMetaText::~SuiteMetaText()
{
    delete iMsgFactory;
}

void SuiteMetaText::Test()
{
    // create MetaText msg, check its text can be retrieved
    Brn metaText("metaText");
    MsgMetaText* msg = iMsgFactory->CreateMsgMetaText(metaText);
    TEST(msg != nullptr);
    TEST(msg->MetaText() == metaText);
    msg->RemoveRef();

#ifdef DEFINE_DEBUG
    // access freed msg (doesn't bother valgrind as this is still allocated memory).  Check text has been cleared.
    TEST(msg->MetaText() != metaText);
#endif

    // create second MetaText msg, check its text can be retrieved
    metaText.Set("updated");
    msg = iMsgFactory->CreateMsgMetaText(metaText);
    TEST(msg != nullptr);
    TEST(msg->MetaText() == metaText);
    msg->RemoveRef();
}


// SuiteTrack

SuiteTrack::SuiteTrack()
    : Suite("MsgTrack tests")
{
    MsgFactoryInitParams init;
    init.SetMsgTrackCount(kMsgTrackCount);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
}

SuiteTrack::~SuiteTrack()
{
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteTrack::Test()
{
    // create Track msg, check its uri/id can be retrieved
    Brn uri("http://host:port/folder/file.ext");
    Brn metadata("metadata#1");
    Track* track = iTrackFactory->CreateTrack(uri, metadata);
    TBool startOfStream = true;
    MsgTrack* msg = iMsgFactory->CreateMsgTrack(*track, startOfStream);
    track->RemoveRef();
    TEST(msg != nullptr);
    TEST(msg->Track().Uri() == uri);
    TEST(msg->Track().MetaData() == metadata);
    TEST(msg->StartOfStream() == startOfStream);
    TUint trackId = msg->Track().Id();
    msg->RemoveRef();

#ifdef DEFINE_DEBUG
    // access freed msg (doesn't bother valgrind as this is still allocated memory).  Check uri/id have been cleared.
    TEST_THROWS(msg->Track(), AssertionFailed);
    TEST(track->Uri() != uri);
    TEST(track->MetaData() != metadata);
    TEST(track->Id() != trackId);
    TEST(msg->StartOfStream() != startOfStream);
#endif

    // create second Track msg, check its uri/id can be retrieved
    uri.Set("http://newhost:newport/newfolder/newfile.newext");
    metadata.Set("metadata#2");
    startOfStream = false;
    track = iTrackFactory->CreateTrack(uri, metadata);
    msg = iMsgFactory->CreateMsgTrack(*track, startOfStream);
    TEST(msg != nullptr);
    TEST(msg->Track().Uri() == uri);
    TEST(msg->Track().MetaData() == metadata);
    TEST(msg->Track().Id() != trackId);
    TEST(msg->StartOfStream() == startOfStream);
    trackId = msg->Track().Id();
    msg->RemoveRef();
    TEST(track->Uri() == uri);
    TEST(track->MetaData() == metadata);
    TEST(track->Id() == trackId);
    track->RemoveRef();
}


// SuiteFlush

SuiteFlush::SuiteFlush()
    : Suite("MsgFlush tests")
{
    MsgFactoryInitParams init;
    init.SetMsgFlushCount(kMsgFlushCount);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
}

SuiteFlush::~SuiteFlush()
{
    delete iMsgFactory;
}

void SuiteFlush::Test()
{
    TUint id = MsgFlush::kIdInvalid + 1;
    MsgFlush* msg = iMsgFactory->CreateMsgFlush(id);
    TEST(msg->Id() == id);
    TEST(msg->Id() != MsgFlush::kIdInvalid);
    msg->RemoveRef();
    TEST(id != msg->Id()); // slightly dodgy to assert that Clear()ing a flush resets its id

    id++;
    msg = iMsgFactory->CreateMsgFlush(id);
    TEST(msg->Id() != MsgFlush::kIdInvalid);
    TEST(msg->Id() == id);
    msg->RemoveRef();
}



// SuiteHalt

SuiteHalt::SuiteHalt()
    : Suite("MsgHalt tests")
{
    MsgFactoryInitParams init;
    init.SetMsgHaltCount(kMsgHaltCount);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
}

SuiteHalt::~SuiteHalt()
{
    delete iMsgFactory;
}

void SuiteHalt::Test()
{
    MsgHalt* msg = iMsgFactory->CreateMsgHalt();
    TEST(msg->Id() == MsgHalt::kIdNone);
    msg->RemoveRef();
    TEST(msg->Id() != MsgHalt::kIdNone);

    msg = iMsgFactory->CreateMsgHalt(MsgHalt::kIdInvalid);
    TEST(msg->Id() == MsgHalt::kIdInvalid);
    msg->RemoveRef();

    TUint id = MsgHalt::kIdNone;
    msg = iMsgFactory->CreateMsgHalt();
    TEST(msg->Id() == MsgHalt::kIdNone);
    msg->RemoveRef();

    id++;
    msg = iMsgFactory->CreateMsgHalt(id);
    TEST(msg->Id() == id);
    msg->RemoveRef();
    TEST(msg->Id() != id);
}


// SuiteMode

SuiteMode::SuiteMode()
    : Suite("MsgMode tests")
{
    MsgFactoryInitParams init;
    init.SetMsgModeCount(kMsgModeCount);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
}

SuiteMode::~SuiteMode()
{
    delete iMsgFactory;
}

void SuiteMode::Test()
{
    Brn mode("First");
    MsgMode* msg = iMsgFactory->CreateMsgMode(mode, true, true, nullptr, true, true);
    TEST(msg->Mode() == mode);
    const ModeInfo& info = msg->Info();
    TEST(info.SupportsLatency());
    TEST(info.IsRealTime());
    TEST(info.SupportsNext());
    TEST(info.SupportsPrev());
    msg->RemoveRef();
    TEST(msg->Mode() != mode);

    Brn mode2("Second");
    msg = iMsgFactory->CreateMsgMode(mode2, false, false, nullptr, false, false);
    TEST(msg->Mode() == mode2);
    TEST(!info.SupportsLatency());
    TEST(!info.IsRealTime());
    TEST(!info.SupportsNext());
    TEST(!info.SupportsPrev());
    msg->RemoveRef();
    TEST(msg->Mode() != mode2);
}

    
// SuiteDelay

SuiteDelay::SuiteDelay()
    : Suite("MsgDelay tests")
{
    MsgFactoryInitParams init;
    init.SetMsgDelayCount(kMsgDelayCount);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
}

SuiteDelay::~SuiteDelay()
{
    delete iMsgFactory;
}

void SuiteDelay::Test()
{
    const TUint kDelayJiffies = Jiffies::kPerMs * 100;
    MsgDelay* msg = iMsgFactory->CreateMsgDelay(kDelayJiffies);
    TEST(msg->DelayJiffies() == kDelayJiffies);
    msg->RemoveRef();
    TEST(msg->DelayJiffies() != kDelayJiffies);

    msg = iMsgFactory->CreateMsgDelay(0);
    TEST(msg->DelayJiffies() == 0);
    msg->RemoveRef();
    TEST(msg->DelayJiffies() != 0);
}


// SuiteDecodedStream

SuiteDecodedStream::SuiteDecodedStream()
    : Suite("MsgDecodedStream tests")
{
    MsgFactoryInitParams init;
    init.SetMsgDecodedStreamCount(kMsgDecodedStreamCount);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
}

SuiteDecodedStream::~SuiteDecodedStream()
{
    delete iMsgFactory;
}

void SuiteDecodedStream::Test()
{
    // create AudioFormat msg, check its text can be retrieved
    TUint streamId = 3; // nonsense value but doesn't matter for this test
    TUint bitRate = 128;
    TUint bitDepth = 16;
    TUint sampleRate = 44100;
    TUint numChannels = 2;
    Brn codecName("test codec");
    TUint64 trackLength = 1<<16;
    TUint64 startSample = 1LL<33;
    TBool lossless = true;
    TBool seekable = true;
    TBool live = true;
    IStreamHandler* handler = this;
    MsgDecodedStream* msg = iMsgFactory->CreateMsgDecodedStream(streamId, bitRate, bitDepth, sampleRate, numChannels, codecName, trackLength, startSample, lossless, seekable, live, handler);
    TEST(msg != nullptr);
    TEST(msg->StreamInfo().StreamId() == streamId);
    TEST(msg->StreamInfo().BitRate() == bitRate);
    TEST(msg->StreamInfo().BitDepth() == bitDepth);
    TEST(msg->StreamInfo().SampleRate() == sampleRate);
    TEST(msg->StreamInfo().NumChannels() == numChannels);
    TEST(msg->StreamInfo().CodecName() == codecName);
    TEST(msg->StreamInfo().TrackLength() == trackLength);
    TEST(msg->StreamInfo().SampleStart() == startSample);
    TEST(msg->StreamInfo().Lossless() == lossless);
    TEST(msg->StreamInfo().Seekable() == seekable);
    TEST(msg->StreamInfo().Live() == live);
    TEST(msg->StreamInfo().StreamHandler() == handler);
    msg->RemoveRef();

#ifdef DEFINE_DEBUG
    // access freed msg (doesn't bother valgrind as this is still allocated memory).  Check text has been cleared.
    TEST(msg->StreamInfo().StreamId() != streamId);
    TEST(msg->StreamInfo().BitRate() != bitRate);
    TEST(msg->StreamInfo().BitDepth() != bitDepth);
    TEST(msg->StreamInfo().SampleRate() != sampleRate);
    TEST(msg->StreamInfo().NumChannels() != numChannels);
    TEST(msg->StreamInfo().CodecName() != codecName);
    TEST(msg->StreamInfo().TrackLength() != trackLength);
    TEST(msg->StreamInfo().SampleStart() != startSample);
    TEST(msg->StreamInfo().Lossless() != lossless);
    TEST(msg->StreamInfo().Seekable() != seekable);
    TEST(msg->StreamInfo().Live() != live);
    TEST(msg->StreamInfo().StreamHandler() != handler);
#endif

    streamId = 4;
    bitRate = 700;
    bitDepth = 24;
    sampleRate = 192000;
    numChannels = 1;
    codecName.Set("new codec name (a bit longer)");
    trackLength = 1<<30;
    startSample += 111;
    lossless = false;
    seekable = false;
    live = false;
    msg = iMsgFactory->CreateMsgDecodedStream(streamId, bitRate, bitDepth, sampleRate, numChannels, codecName, trackLength, startSample, lossless, seekable, live, handler);
    TEST(msg != nullptr);
    TEST(msg->StreamInfo().StreamId() == streamId);
    TEST(msg->StreamInfo().BitRate() == bitRate);
    TEST(msg->StreamInfo().BitDepth() == bitDepth);
    TEST(msg->StreamInfo().SampleRate() == sampleRate);
    TEST(msg->StreamInfo().NumChannels() == numChannels);
    TEST(msg->StreamInfo().CodecName() == codecName);
    TEST(msg->StreamInfo().TrackLength() == trackLength);
    TEST(msg->StreamInfo().SampleStart() == startSample);
    TEST(msg->StreamInfo().Lossless() == lossless);
    TEST(msg->StreamInfo().Seekable() == seekable);
    TEST(msg->StreamInfo().Live() == live);
    TEST(msg->StreamInfo().StreamHandler() == handler);
        msg->RemoveRef();
}

EStreamPlay SuiteDecodedStream::OkToPlay(TUint /*aStreamId*/)
{
    ASSERTS();
    return ePlayNo;
}

TUint SuiteDecodedStream::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteDecodedStream::TryStop(TUint /*aStreamId*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

void SuiteDecodedStream::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/, TBool /*aStarving*/)
{
    ASSERTS();
}


// SuiteMsgProcessor

SuiteMsgProcessor::SuiteMsgProcessor()
    : Suite("IMsgProcessor tests")
{
    MsgFactoryInitParams init;
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
}

SuiteMsgProcessor::~SuiteMsgProcessor()
{
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteMsgProcessor::Test()
{
    ProcessorMsgType processor;
    // lots of code duplication here.
    // If we factored out the repeating block of code, any failures would be in a common method so pretty meaningless
    const TUint kDataBytes = 256;
    TByte audioData[kDataBytes];
    (void)memset(audioData, 0xab, kDataBytes);
    Brn audioBuf(audioData, kDataBytes);
    
    MsgAudioEncoded* audioEncoded = iMsgFactory->CreateMsgAudioEncoded(audioBuf);
    TEST(audioEncoded == static_cast<Msg*>(audioEncoded)->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgAudioEncoded);
    audioEncoded->RemoveRef();

    MsgAudioPcm* audioPcm = iMsgFactory->CreateMsgAudioPcm(audioBuf, 2, 44100, 8, EMediaDataEndianLittle, 0);
    TEST(audioPcm == static_cast<Msg*>(audioPcm)->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgAudioPcm);
    MsgPlayable* playable = audioPcm->CreatePlayable();
    TEST(playable == static_cast<Msg*>(playable)->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgPlayable);
    playable->RemoveRef();

    MsgSilence* silence = iMsgFactory->CreateMsgSilence(Jiffies::kPerMs);
    TEST(silence == static_cast<Msg*>(silence)->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgSilence);
    playable = silence->CreatePlayable(44100, 8, 2);
    TEST(playable == static_cast<Msg*>(playable)->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgPlayable);
    playable->RemoveRef();

    Msg* msg = iMsgFactory->CreateMsgDecodedStream(0, 0, 0, 0, 0, Brx::Empty(), 0, 0, false, false, false, nullptr);
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgDecodedStream);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgMode(Brx::Empty(), true, true, nullptr, false, false);
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgMode);
    msg->RemoveRef();

    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    msg = iMsgFactory->CreateMsgTrack(*track);
    track->RemoveRef();
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgTrack);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgDrain(Functor());
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgDrain);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgDelay(0);
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgDelay);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgEncodedStream(Brn("http://1.2.3.4:5"), Brn("Test metatext"), 0, 0, false, false, nullptr);
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgEncodedStream);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgMetaText(Brn("Test metatext"));
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgMetaText);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgStreamInterrupted();
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgStreamInterrupted);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgHalt();
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgHalt);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgFlush(1);
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgFlush);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgWait();
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgWait);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgQuit();
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgQuit);
    msg->RemoveRef();
}


// ProcessorMsgType

ProcessorMsgType::ProcessorMsgType()
    : iLastMsgType(ENone)
{
}

ProcessorMsgType::EMsgType ProcessorMsgType::LastMsgType() const
{
    return iLastMsgType;
}

Msg* ProcessorMsgType::ProcessMsg(MsgMode* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgMode;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgTrack* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgTrack;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgDrain* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgDrain;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgDelay* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgDelay;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgEncodedStream;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgAudioEncoded;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgMetaText* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgMetaText;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgStreamInterrupted;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgHalt* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgHalt;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgFlush* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgFlush;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgWait* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgWait;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgDecodedStream;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgBitRate* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgBitRate;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgAudioPcm;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgSilence* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgSilence;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgPlayable* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgPlayable;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgQuit* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgQuit;
    return aMsg;
}


// SuiteMsgQueue

SuiteMsgQueue::SuiteMsgQueue()
    : Suite("MsgQueue tests")
{
    MsgFactoryInitParams init;
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
}

SuiteMsgQueue::~SuiteMsgQueue()
{
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteMsgQueue::Test()
{
    MsgQueue* queue = new MsgQueue();
    
    // queue can be populated and read from
    TEST(queue->IsEmpty());
    Msg* msg = iMsgFactory->CreateMsgSilence(Jiffies::kPerMs);
    queue->Enqueue(msg);
    TEST(!queue->IsEmpty());
    Msg* dequeued = queue->Dequeue();
    TEST(msg == dequeued);
    TEST(queue->IsEmpty());
    dequeued->RemoveRef();

    // queue can be emptied then reused
    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    msg = iMsgFactory->CreateMsgTrack(*track);
    track->RemoveRef();
    queue->Enqueue(msg);
    TEST(!queue->IsEmpty());
    dequeued = queue->Dequeue();
    TEST(msg == dequeued);
    TEST(queue->IsEmpty());
    dequeued->RemoveRef();

    // queue is fifo by default
    msg = iMsgFactory->CreateMsgMetaText(Brn("Test metatext"));
    queue->Enqueue(msg);
    msg = iMsgFactory->CreateMsgHalt();
    queue->Enqueue(msg);
    msg = iMsgFactory->CreateMsgFlush(1);
    queue->Enqueue(msg);
    msg = iMsgFactory->CreateMsgWait();
    queue->Enqueue(msg);
    msg = iMsgFactory->CreateMsgQuit();
    queue->Enqueue(msg);
    TEST(!queue->IsEmpty());
    ProcessorMsgType processor;
    dequeued = queue->Dequeue();
    TEST(!queue->IsEmpty());
    dequeued->Process(processor);
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgMetaText);
    dequeued->RemoveRef();
    dequeued = queue->Dequeue();
    TEST(!queue->IsEmpty());
    dequeued->Process(processor);
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgHalt);
    dequeued->RemoveRef();
    dequeued = queue->Dequeue();
    TEST(!queue->IsEmpty());
    dequeued->Process(processor);
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgFlush);
    dequeued->RemoveRef();
    dequeued = queue->Dequeue();
    TEST(!queue->IsEmpty());
    dequeued->Process(processor);
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgWait);
    dequeued->RemoveRef();
    dequeued = queue->Dequeue();
    TEST(queue->IsEmpty());
    dequeued->Process(processor);
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgQuit);
    dequeued->RemoveRef();

    // EnqueueAtHead skips existing items
    msg = iMsgFactory->CreateMsgMetaText(Brn("blah"));
    queue->Enqueue(msg);
    msg = iMsgFactory->CreateMsgHalt();
    queue->Enqueue(msg);
    msg = iMsgFactory->CreateMsgFlush(1);
    queue->EnqueueAtHead(msg);
    TEST(!queue->IsEmpty());
    dequeued = queue->Dequeue();
    TEST(!queue->IsEmpty());
    dequeued->Process(processor);
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgFlush);
    dequeued->RemoveRef();
    dequeued = queue->Dequeue();
    TEST(!queue->IsEmpty());
    dequeued->Process(processor);
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgMetaText);
    dequeued->RemoveRef();
    dequeued = queue->Dequeue();
    TEST(queue->IsEmpty());
    dequeued->Process(processor);
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgHalt);
    dequeued->RemoveRef();

    // EnqueueAtHead for empty list correctly sets Head and Tail
    TEST(queue->IsEmpty());
    msg = iMsgFactory->CreateMsgMetaText(Brn("blah"));
    queue->EnqueueAtHead(msg);
    msg = iMsgFactory->CreateMsgHalt();
    queue->Enqueue(msg);
    TEST(!queue->IsEmpty());
    dequeued = queue->Dequeue();
    dequeued->Process(processor);
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgMetaText);
    dequeued->RemoveRef();
    TEST(!queue->IsEmpty());
    dequeued = queue->Dequeue();
    dequeued->Process(processor);
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgHalt);
    dequeued->RemoveRef();
    TEST(queue->IsEmpty());

    // Enqueueing the same msg consecutively fails
    msg = iMsgFactory->CreateMsgFlush(1);
    queue->Enqueue(msg);
    TEST_THROWS(queue->Enqueue(msg), AssertionFailed);
    dequeued = queue->Dequeue();
    dequeued->RemoveRef();
    TEST(queue->IsEmpty());

    // Enqueueing the same msg at head consecutively fails
    msg = iMsgFactory->CreateMsgFlush(1);
    queue->EnqueueAtHead(msg);
    TEST_THROWS(queue->EnqueueAtHead(msg), AssertionFailed);
    dequeued = queue->Dequeue();
    dequeued->RemoveRef();
    TEST(queue->IsEmpty());

    // Enqueueing the same msg at head and tail consecutively fails
    // queue at tail first, then head
    msg = iMsgFactory->CreateMsgMetaText(Brn("blah")); // filler msg so that iHead != iTail
    queue->Enqueue(msg);
    msg = iMsgFactory->CreateMsgFlush(1);
    queue->Enqueue(msg);
    TEST_THROWS(queue->EnqueueAtHead(msg), AssertionFailed);
    dequeued = queue->Dequeue();
    dequeued->RemoveRef();
    dequeued = queue->Dequeue();
    dequeued->RemoveRef();
    TEST(queue->IsEmpty());
    // queue at head first, then tail
    msg = iMsgFactory->CreateMsgMetaText(Brn("blah")); // filler msg so that iHead != iTail
    queue->Enqueue(msg);
    msg = iMsgFactory->CreateMsgFlush(1);
    queue->EnqueueAtHead(msg);
    TEST_THROWS(queue->Enqueue(msg), AssertionFailed);
    dequeued = queue->Dequeue();
    dequeued->RemoveRef();
    dequeued = queue->Dequeue();
    dequeued->RemoveRef();
    TEST(queue->IsEmpty());

#ifdef DEFINE_DEBUG
    // Enqueueing the same msg as a msg already in queue fails
    msg = iMsgFactory->CreateMsgMetaText(Brn("blah")); // filler msg so that iHead != iTail
    queue->Enqueue(msg);
    Msg* flushMsg = iMsgFactory->CreateMsgFlush(1);
    queue->Enqueue(flushMsg);
    msg = iMsgFactory->CreateMsgHalt();
    queue->Enqueue(msg);
    TEST_THROWS(queue->Enqueue(flushMsg), AssertionFailed);
    // try do the same again, but by enqueuing at head
    TEST_THROWS(queue->EnqueueAtHead(flushMsg), AssertionFailed);
    // clear queue
    dequeued = queue->Dequeue();
    dequeued->RemoveRef();
    dequeued = queue->Dequeue();
    dequeued->RemoveRef();
    dequeued = queue->Dequeue();
    dequeued->RemoveRef();
    TEST(queue->IsEmpty());
#endif

    // Clear() removes all items
    msg = iMsgFactory->CreateMsgHalt();
    queue->Enqueue(msg);
    msg = iMsgFactory->CreateMsgFlush(1);
    queue->Enqueue(msg);
    msg = iMsgFactory->CreateMsgWait();
    queue->Enqueue(msg);
    msg = iMsgFactory->CreateMsgQuit();
    queue->Enqueue(msg);
    TEST(!queue->IsEmpty());
    queue->Clear();
    TEST(queue->IsEmpty());

    // FIXME - no check yet that reading from an empty queue blocks

    delete queue;
}


// SuiteMsgReservoir

SuiteMsgReservoir::SuiteMsgReservoir()
    : Suite("MsgReservoir tests")
{
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(2, 1);
    init.SetMsgSilenceCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
}

SuiteMsgReservoir::~SuiteMsgReservoir()
{
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteMsgReservoir::Test()
{
    // Add msg of each type.  After each addition, check type of last in and that only audio increases Jiffies()
    // Dequeue msgs.  After each, check type of last out and that only audio decreases Jiffies()

    TestMsgReservoir* queue = new TestMsgReservoir();
    TUint jiffies = queue->Jiffies();
    TEST(jiffies == 0);
    TEST(queue->LastIn() == TestMsgReservoir::ENone);
    TEST(queue->LastOut() == TestMsgReservoir::ENone);

    Msg* msg = iMsgFactory->CreateMsgMode(Brx::Empty(), true, true, nullptr, false, false);
    queue->Enqueue(msg);
    jiffies = queue->Jiffies();
    TEST(jiffies == 0);
    TEST(queue->LastIn() == TestMsgReservoir::EMsgMode);
    TEST(queue->LastOut() == TestMsgReservoir::ENone);

    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    msg = iMsgFactory->CreateMsgTrack(*track);
    track->RemoveRef();
    queue->Enqueue(msg);
    jiffies = queue->Jiffies();
    TEST(jiffies == 0);
    TEST(queue->LastIn() == TestMsgReservoir::EMsgTrack);
    TEST(queue->LastOut() == TestMsgReservoir::ENone);

    msg = iMsgFactory->CreateMsgDelay(0);
    queue->Enqueue(msg);
    jiffies = queue->Jiffies();
    TEST(jiffies == 0);
    TEST(queue->LastIn() == TestMsgReservoir::EMsgDelay);
    TEST(queue->LastOut() == TestMsgReservoir::ENone);

    msg = iMsgFactory->CreateMsgEncodedStream(Brn("http://1.2.3.4:5"), Brn("metatext"), 0, 0, false, false, nullptr);
    TEST(queue->EncodedStreamCount() == 0);
    queue->Enqueue(msg);
    TEST(queue->Jiffies() == 0);
    TEST(queue->LastIn() == TestMsgReservoir::EMsgEncodedStream);
    TEST(queue->EncodedStreamCount() == 1);
    TEST(queue->LastOut() == TestMsgReservoir::ENone);

    msg = iMsgFactory->CreateMsgDecodedStream(3, 128, 16, 44100, 2, Brn("test codec"), 1<<16, 0, true, true, false, nullptr);
    TEST(queue->DecodedStreamCount() == 0);
    queue->Enqueue(msg);
    TEST(queue->Jiffies() == 0);
    TEST(queue->LastIn() == TestMsgReservoir::EMsgDecodedStream);
    TEST(queue->DecodedStreamCount() == 1);
    TEST(queue->LastOut() == TestMsgReservoir::ENone);

    static const TUint kBitRate = 12345;
    msg = iMsgFactory->CreateMsgBitRate(kBitRate);
    queue->Enqueue(msg);
    TEST(queue->Jiffies() == 0);
    TEST(queue->LastIn() == TestMsgReservoir::EMsgBitRate);
    TEST(queue->LastOut() == TestMsgReservoir::ENone);

    MsgAudio* audio = iMsgFactory->CreateMsgSilence(Jiffies::kPerMs);
    queue->Enqueue(audio);
    TEST(queue->Jiffies() == jiffies + audio->Jiffies());
    jiffies = queue->Jiffies();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgSilence);
    TEST(queue->LastOut() == TestMsgReservoir::ENone);

    msg = iMsgFactory->CreateMsgMetaText(Brn("foo"));
    queue->Enqueue(msg);
    TEST(queue->Jiffies() == jiffies);
    TEST(queue->LastIn() == TestMsgReservoir::EMsgMetaText);
    TEST(queue->LastOut() == TestMsgReservoir::ENone);

    msg = iMsgFactory->CreateMsgFlush(5); // arbitrary flush id
    queue->Enqueue(msg);
    TEST(queue->Jiffies() == jiffies);
    TEST(queue->LastIn() == TestMsgReservoir::EMsgFlush);
    TEST(queue->LastOut() == TestMsgReservoir::ENone);

    msg = iMsgFactory->CreateMsgWait();
    queue->Enqueue(msg);
    TEST(queue->Jiffies() == jiffies);
    TEST(queue->LastIn() == TestMsgReservoir::EMsgWait);
    TEST(queue->LastOut() == TestMsgReservoir::ENone);

    msg = iMsgFactory->CreateMsgQuit();
    queue->Enqueue(msg);
    TEST(queue->Jiffies() == jiffies);
    TEST(queue->LastIn() == TestMsgReservoir::EMsgQuit);
    TEST(queue->LastOut() == TestMsgReservoir::ENone);

    const TUint kDataBytes = 256;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0xab, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, 2, 44100, 8, EMediaDataEndianLittle, 0);
    const TUint audioJiffies = audio->Jiffies();
    queue->Enqueue(audio);
    TEST(queue->Jiffies() == jiffies + audioJiffies);
    jiffies = queue->Jiffies();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgAudioPcm);
    TEST(queue->LastOut() == TestMsgReservoir::ENone);

    msg = iMsgFactory->CreateMsgHalt();
    queue->Enqueue(msg);
    TEST(queue->Jiffies() == jiffies);
    TEST(queue->LastIn() == TestMsgReservoir::EMsgHalt);
    TEST(queue->LastOut() == TestMsgReservoir::ENone);

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgHalt);
    TEST(queue->LastOut() == TestMsgReservoir::EMsgMode);
    TEST(queue->Jiffies() == jiffies);
    msg->RemoveRef();

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgHalt);
    TEST(queue->LastOut() == TestMsgReservoir::EMsgTrack);
    TEST(queue->Jiffies() == jiffies);
    msg->RemoveRef();

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgHalt);
    TEST(queue->LastOut() == TestMsgReservoir::EMsgDelay);
    TEST(queue->Jiffies() == jiffies);
    msg->RemoveRef();

    TEST(queue->EncodedStreamCount() == 1);
    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgHalt);
    TEST(queue->LastOut() == TestMsgReservoir::EMsgEncodedStream);
    TEST(queue->EncodedStreamCount() == 0);
    TEST(queue->Jiffies() == jiffies);
    msg->RemoveRef();

    TEST(queue->DecodedStreamCount() == 1);
    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgHalt);
    TEST(queue->LastOut() == TestMsgReservoir::EMsgDecodedStream);
    TEST(queue->DecodedStreamCount() == 0);
    TEST(queue->Jiffies() == jiffies);
    msg->RemoveRef();

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgHalt);
    TEST(queue->LastOut() == TestMsgReservoir::EMsgBitRate);
    msg->RemoveRef();

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgHalt);
    TEST(queue->LastOut() == TestMsgReservoir::EMsgSilence);
    TEST(queue->Jiffies() == jiffies - Jiffies::kPerMs);
    jiffies = queue->Jiffies();
    msg->RemoveRef();

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgHalt);
    TEST(queue->LastOut() == TestMsgReservoir::EMsgMetaText);
    TEST(queue->Jiffies() == jiffies);
    msg->RemoveRef();

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgHalt);
    TEST(queue->LastOut() == TestMsgReservoir::EMsgFlush);
    TEST(queue->Jiffies() == jiffies);
    msg->RemoveRef();

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgHalt);
    TEST(queue->LastOut() == TestMsgReservoir::EMsgWait);
    TEST(queue->Jiffies() == jiffies);
    msg->RemoveRef();

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgHalt);
    TEST(queue->LastOut() == TestMsgReservoir::EMsgQuit);
    TEST(queue->Jiffies() == jiffies);
    msg->RemoveRef();

    queue->SplitNextAudio();
    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgAudioPcm);
    TEST(queue->LastOut() == TestMsgReservoir::EMsgAudioPcm);
    TEST(queue->Jiffies() == jiffies - (audioJiffies/2));
    jiffies = queue->Jiffies();
    msg->RemoveRef();
    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgAudioPcm);
    TEST(queue->LastOut() == TestMsgReservoir::EMsgAudioPcm);
    TEST(queue->Jiffies() == 0);
    msg->RemoveRef();

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgReservoir::EMsgAudioPcm);
    TEST(queue->LastOut() == TestMsgReservoir::EMsgHalt);
    TEST(queue->Jiffies() == 0);
    msg->RemoveRef();

    delete queue;
}


// TestMsgReservoir

TestMsgReservoir::TestMsgReservoir()
    : iLastMsgIn(ENone)
    , iLastMsgOut(ENone)
    , iSplitNextAudio(false)
{
}
    
Msg* TestMsgReservoir::ProcessMsgAudioOut(MsgAudio* aMsgAudio)
{
    if (iSplitNextAudio) {
        iSplitNextAudio = false;
        MsgAudio* remaining = aMsgAudio->Split(aMsgAudio->Jiffies() / 2);
        EnqueueAtHead(remaining);
    }
    return aMsgAudio;
}
    
void TestMsgReservoir::ProcessMsgIn(MsgAudioPcm* /*aMsg*/)
{
    iLastMsgIn = EMsgAudioPcm;
}

void TestMsgReservoir::ProcessMsgIn(MsgSilence* /*aMsg*/)
{
    iLastMsgIn = EMsgSilence;
}

void TestMsgReservoir::ProcessMsgIn(MsgMode* /*aMsg*/)
{
    iLastMsgIn = EMsgMode;
}

void TestMsgReservoir::ProcessMsgIn(MsgTrack* /*aMsg*/)
{
    iLastMsgIn = EMsgTrack;
}

void TestMsgReservoir::ProcessMsgIn(MsgDrain* /*aMsg*/)
{
    iLastMsgIn = EMsgDrain;
}

void TestMsgReservoir::ProcessMsgIn(MsgDelay* /*aMsg*/)
{
    iLastMsgIn = EMsgDelay;
}

void TestMsgReservoir::ProcessMsgIn(MsgEncodedStream* /*aMsg*/)
{
    iLastMsgIn = EMsgEncodedStream;
}

void TestMsgReservoir::ProcessMsgIn(MsgDecodedStream* /*aMsg*/)
{
    iLastMsgIn = EMsgDecodedStream;
}

void TestMsgReservoir::ProcessMsgIn(MsgBitRate* /*aMsg*/)
{
    iLastMsgIn = EMsgBitRate;
}

void TestMsgReservoir::ProcessMsgIn(MsgMetaText* /*aMsg*/)
{
    iLastMsgIn = EMsgMetaText;
}

void TestMsgReservoir::ProcessMsgIn(MsgStreamInterrupted* /*aMsg*/)
{
    iLastMsgIn = EMsgStreamInterrupted;
}

void TestMsgReservoir::ProcessMsgIn(MsgHalt* /*aMsg*/)
{
    iLastMsgIn = EMsgHalt;
}

void TestMsgReservoir::ProcessMsgIn(MsgFlush* /*aMsg*/)
{
    iLastMsgIn = EMsgFlush;
}

void TestMsgReservoir::ProcessMsgIn(MsgWait* /*aMsg*/)
{
    iLastMsgIn = EMsgWait;
}

void TestMsgReservoir::ProcessMsgIn(MsgQuit* /*aMsg*/)
{
    iLastMsgIn = EMsgQuit;
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgAudioPcm* aMsg)
{
    iLastMsgOut = EMsgAudioPcm;
    return ProcessMsgAudioOut(aMsg);
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgSilence* aMsg)
{
    iLastMsgOut = EMsgSilence;
    return ProcessMsgAudioOut(aMsg);
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgMode* aMsg)
{
    iLastMsgOut = EMsgMode;
    return aMsg;
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgTrack* aMsg)
{
    iLastMsgOut = EMsgTrack;
    return aMsg;
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgDrain* aMsg)
{
    iLastMsgOut = EMsgDrain;
    return aMsg;
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgDelay* aMsg)
{
    iLastMsgOut = EMsgDelay;
    return aMsg;
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgEncodedStream* aMsg)
{
    iLastMsgOut = EMsgEncodedStream;
    return aMsg;
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgDecodedStream* aMsg)
{
    iLastMsgOut = EMsgDecodedStream;
    return aMsg;
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgBitRate* aMsg)
{
    iLastMsgOut = EMsgBitRate;
    return aMsg;
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgMetaText* aMsg)
{
    iLastMsgOut = EMsgMetaText;
    return aMsg;
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgStreamInterrupted* aMsg)
{
    iLastMsgOut = EMsgStreamInterrupted;
    return aMsg;
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgHalt* aMsg)
{
    iLastMsgOut = EMsgHalt;
    return aMsg;
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgFlush* aMsg)
{
    iLastMsgOut = EMsgFlush;
    return aMsg;
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgWait* aMsg)
{
    iLastMsgOut = EMsgWait;
    return aMsg;
}

Msg* TestMsgReservoir::ProcessMsgOut(MsgQuit* aMsg)
{
    iLastMsgOut = EMsgQuit;
    return aMsg;
}


// DummyElement

DummyElement::DummyElement(TUint aSupported)
    : PipelineElement(aSupported)
{
}

void DummyElement::Process(Msg* aMsg)
{
    auto msg = aMsg->Process(*this);
    TEST(msg == aMsg);
    msg->RemoveRef();
}


// SuitePipelineElement

SuitePipelineElement::SuitePipelineElement()
    : Suite("PipelineElement tests")
{
    MsgFactoryInitParams init;
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
}

SuitePipelineElement::~SuitePipelineElement()
{
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuitePipelineElement::Test()
{
    for (TInt s = ProcessorMsgType::EMsgMode; s <= ProcessorMsgType::EMsgQuit; s++) {
        const TUint supported = 1<<(s-1); // dodgy mapping that relies on ProcessorMsgType and PipelineElement declaring types in the same order
        auto element = new DummyElement(supported);
        for (TInt t=ProcessorMsgType::EMsgMode; t <= ProcessorMsgType::EMsgQuit; t++) {
            auto msg = CreateMsg((ProcessorMsgType::EMsgType)t);
            if (t == s) {
                element->Process(msg);
            }
            else {
                TEST_THROWS(element->Process(msg), AssertionFailed);
                msg->RemoveRef();
            }
        }
        delete element;
    }

    auto element = new DummyElement(0xffffffff);
    for (TInt t=ProcessorMsgType::EMsgMode; t <= ProcessorMsgType::EMsgQuit; t++) {
        auto msg = CreateMsg((ProcessorMsgType::EMsgType)t);
        element->Process(msg);
    }
    delete element;
}

Msg* SuitePipelineElement::CreateMsg(ProcessorMsgType::EMsgType aType)
{
    switch (aType)
    {
    default:
    case ProcessorMsgType::ENone:
        break;
    case ProcessorMsgType::EMsgMode:
        return iMsgFactory->CreateMsgMode(Brx::Empty(), true, true, nullptr, false, false);
    case ProcessorMsgType::EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
        auto msg = iMsgFactory->CreateMsgTrack(*track);
        track->RemoveRef();
        return msg;
    }
    case ProcessorMsgType::EMsgDrain:
        return iMsgFactory->CreateMsgDrain(Functor());
    case ProcessorMsgType::EMsgDelay:
        return iMsgFactory->CreateMsgDelay(0);
    case ProcessorMsgType::EMsgEncodedStream:
        return iMsgFactory->CreateMsgEncodedStream(Brn("http://1.2.3.4:5"), Brn("Test metatext"), 0, 0, false, false, nullptr);
    case ProcessorMsgType::EMsgAudioEncoded:
    {
        const TUint kDataBytes = 256;
        TByte audioData[kDataBytes];
        (void)memset(audioData, 0xab, kDataBytes);
        Brn audioBuf(audioData, kDataBytes);
        return iMsgFactory->CreateMsgAudioEncoded(audioBuf);
    }
    case ProcessorMsgType::EMsgMetaText:
        return iMsgFactory->CreateMsgMetaText(Brn("Test metatext"));
    case ProcessorMsgType::EMsgStreamInterrupted:
        return iMsgFactory->CreateMsgStreamInterrupted();
    case ProcessorMsgType::EMsgHalt:
        return iMsgFactory->CreateMsgHalt();
    case ProcessorMsgType::EMsgFlush:
        return iMsgFactory->CreateMsgFlush(1);
    case ProcessorMsgType::EMsgWait:
        return iMsgFactory->CreateMsgWait();
    case ProcessorMsgType::EMsgDecodedStream:
        return iMsgFactory->CreateMsgDecodedStream(0, 0, 0, 0, 0, Brx::Empty(), 0, 0, false, false, false, nullptr);
    case ProcessorMsgType::EMsgBitRate:
        return iMsgFactory->CreateMsgBitRate(1234);
    case ProcessorMsgType::EMsgAudioPcm:
    {
        const TUint kDataBytes = 256;
        TByte audioData[kDataBytes];
        (void)memset(audioData, 0xab, kDataBytes);
        Brn audioBuf(audioData, kDataBytes);
        return iMsgFactory->CreateMsgAudioPcm(audioBuf, 2, 44100, 8, EMediaDataEndianLittle, 0);
    }
    case ProcessorMsgType::EMsgSilence:
        return iMsgFactory->CreateMsgSilence(Jiffies::kPerMs);
    case ProcessorMsgType::EMsgPlayable:
    {
        const TUint kDataBytes = 256;
        TByte audioData[kDataBytes];
        (void)memset(audioData, 0xab, kDataBytes);
        Brn audioBuf(audioData, kDataBytes);
        MsgAudioPcm* audioPcm = iMsgFactory->CreateMsgAudioPcm(audioBuf, 2, 44100, 8, EMediaDataEndianLittle, 0);
        return audioPcm->CreatePlayable();
    }
    case ProcessorMsgType::EMsgQuit:
        return iMsgFactory->CreateMsgQuit();
    }
    ASSERTS();
    return nullptr;
}



void TestMsg()
{
    Runner runner("Basic Msg tests\n");
    runner.Add(new SuiteAllocator());
    runner.Add(new SuiteMsgAudioEncoded());
    runner.Add(new SuiteMsgAudio());
    runner.Add(new SuiteMsgPlayable());
    runner.Add(new SuiteRamp());
    runner.Add(new SuiteAudioStream());
    runner.Add(new SuiteMetaText());
    runner.Add(new SuiteTrack());
    runner.Add(new SuiteFlush());
    runner.Add(new SuiteHalt());
    runner.Add(new SuiteMode());
    runner.Add(new SuiteDelay());
    runner.Add(new SuiteDecodedStream());
    runner.Add(new SuiteMsgProcessor());
    runner.Add(new SuiteMsgQueue());
    runner.Add(new SuiteMsgReservoir());
    runner.Add(new SuitePipelineElement());
    runner.Run();
}
