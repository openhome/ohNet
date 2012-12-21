#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/RampArray.h>
#include "AllocatorInfoLogger.h"
#include <OpenHome/Media/ProcessorPcmUtils.h>

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
    TByte iBuf[DecodedAudio::kMaxBytes];
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
    TByte iBuf[DecodedAudio::kMaxBytes];
};

class SuiteAudioStream : public Suite
{
    static const TUint kMsgAudioStreamCount = 1;
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

class SuiteAudioFormat : public Suite
{
    static const TUint kMsgAudioFormatCount = 1;
public:
    SuiteAudioFormat();
    ~SuiteAudioFormat();
    void Test();
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
    AllocatorInfoLogger iInfoAggregator;
};

class ProcessorMsgType : public IMsgProcessor
{
public:
    enum EMsgType
    {
        ENone
       ,EMsgAudioEncoded
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgAudioFormat
       ,EMsgTrack
       ,EMsgAudioStream
       ,EMsgMetaText
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgQuit
    };
public:
    ProcessorMsgType();
    EMsgType LastMsgType() const;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgAudioFormat* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgAudioStream* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
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
    AllocatorInfoLogger iInfoAggregator;
};

class SuiteMsgQueueFlushable : public Suite
{
    static const TUint kMsgCount = 8;
public:
    SuiteMsgQueueFlushable();
    ~SuiteMsgQueueFlushable();
    void Test();
private:
    MsgFactory* iMsgFactory;
    AllocatorInfoLogger iInfoAggregator;
};

class TestMsgQueueFlushable : public MsgQueueFlushable
{
public:
    enum EMsgType
    {
        ENone
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgTrack
       ,EMsgAudioStream
       ,EMsgMetaText
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgQuit
    };
public:
    TestMsgQueueFlushable();
    void Enqueue(Msg* aMsg)         { DoEnqueue(aMsg); }
    Msg* Dequeue()                  { return DoDequeue(); }
    void EnqueueAtHead(Msg* aMsg)   { MsgQueueFlushable::EnqueueAtHead(aMsg); }
    TUint Jiffies() const           { return MsgQueueFlushable::Jiffies(); }
    EMsgType LastIn() const         { return iLastMsgIn; }
    EMsgType LastOut() const        { return iLastMsgOut; }
    void SplitNextAudio()           { iSplitNextAudio = true; }
private:
    Msg* ProcessMsgAudioOut(MsgAudio* aMsgAudio);
private: // from MsgQueueFlushable
    void ProcessMsgIn(MsgAudioPcm* aMsg);
    void ProcessMsgIn(MsgSilence* aMsg);
    void ProcessMsgIn(MsgTrack* aMsg);
    void ProcessMsgIn(MsgAudioStream* aMsg);
    void ProcessMsgIn(MsgMetaText* aMsg);
    void ProcessMsgIn(MsgHalt* aMsg);
    void ProcessMsgIn(MsgFlush* aMsg);
    void ProcessMsgIn(MsgQuit* aMsg);
    Msg* ProcessMsgOut(MsgAudioPcm* aMsg);
    Msg* ProcessMsgOut(MsgSilence* aMsg);
    Msg* ProcessMsgOut(MsgTrack* aMsg);
    Msg* ProcessMsgOut(MsgAudioStream* aMsg);
    Msg* ProcessMsgOut(MsgMetaText* aMsg);
    Msg* ProcessMsgOut(MsgHalt* aMsg);
    Msg* ProcessMsgOut(MsgFlush* aMsg);
    Msg* ProcessMsgOut(MsgQuit* aMsg);
private:
    EMsgType iLastMsgIn;
    EMsgType iLastMsgOut;
    TBool iSplitNextAudio;
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


// SuiteMsgAudioEncoded

SuiteMsgAudioEncoded::SuiteMsgAudioEncoded()
    : Suite("MsgAudioEncoded tests")
{
    iMsgFactory = new MsgFactory(iInfoAggregator, kMsgCount, kMsgCount, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
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

    // clean shutdown implies no leaked msgs
}


// SuiteMsgAudio

SuiteMsgAudio::SuiteMsgAudio()
    : Suite("Basic MsgAudio tests")
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, kMsgCount, kMsgCount, kMsgCount, 1, 1, 1, 1, 1, 1, 1, 1, 1);
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
        msg = iMsgFactory->CreateMsgAudioPcm(data, 2, sampleRates[i], 8, EMediaDataLittleEndian, 0);
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
        msgbd[i] = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, bitDepths[i], EMediaDataLittleEndian, 0);
    }
    TEST(msgbd[0]->Jiffies() == 2 * msgbd[1]->Jiffies());
    TEST(msgbd[0]->Jiffies() == 3 * msgbd[2]->Jiffies());
    for (TUint i=0; i<numBitDepths; i++) {
        msgbd[i]->RemoveRef();
    }

    // Split pcm msg.  Check lengths of both parts are as expected.
    msg = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian, Jiffies::kJiffiesPerSecond);
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
    TEST(static_cast<MsgAudioPcm*>(msg)->TrackOffset() == Jiffies::kJiffiesPerSecond);
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
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, kMsgCount, kMsgCount, kMsgCount, kMsgCount, kMsgCount, 1, 1, 1, 1, 1, 1, 1);
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
        audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, sampleRates[i], 8, EMediaDataLittleEndian, 0);
        playable = audioPcm->CreatePlayable();
        bytes = playable->Bytes();
        playable->RemoveRef();
        if (prevBytes != 0) {
            TEST(prevBytes == bytes);
        }
        prevBytes = bytes;
    }

    // Create pcm msg.  Read/validate its content
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian, 0);
    playable = audioPcm->CreatePlayable();
    TEST(playable->Bytes() == data.Bytes());
    ProcessorPcmBufPacked pcmProcessor;
    playable->Read(pcmProcessor);
    playable->RemoveRef();
    const TByte* ptr = pcmProcessor.Ptr();
    TUint subsampleVal = 0xff;
    for (TUint i=0; i<data.Bytes(); i++) {
        TEST(*ptr == subsampleVal);
        ptr++;
        subsampleVal--;
    }

    // Create pcm msg, split it then convert to playable.  Read/validate contents of both
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian, 0);
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
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian, 0);
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
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian, 0);
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
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian, 0);
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

    // Test splitting at the end of a message returns NULL
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian, 0);
    playable = audioPcm->CreatePlayable();
    TEST(NULL == playable->Split(playable->Bytes()));
    playable->RemoveRef();

    // Split pcm msg at invalid positions (0, > Jiffies()).  Check these assert.
    audioPcm = iMsgFactory->CreateMsgAudioPcm(data, 2, 44100, 8, EMediaDataLittleEndian, 0);
    playable = audioPcm->CreatePlayable();
    TEST_THROWS(remainingPlayable = playable->Split(0), AssertionFailed);
    TEST_THROWS(remainingPlayable = playable->Split(playable->Bytes()+1), AssertionFailed);
    playable->RemoveRef();

    // For each sample rate, create a silence msg using the same size
    // Convert to MsgPlayable; check Bytes() increase as sample rates increase
    prevBytes = 0;
    MsgSilence* silence;
    for (TUint i=0; i<numRates; i++) {
        silence = iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs * 5);
        playable = silence->CreatePlayable(sampleRates[i], 8, 2);
        bytes = playable->Bytes();
        playable->RemoveRef();
        if (prevBytes != 0) {
            TEST(prevBytes < bytes);
        }
        prevBytes = bytes;
    }

    // Create silence msg.  Read/validate its content
    silence = iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs);
    playable = silence->CreatePlayable(44100, 8, 1);
    bytes = playable->Bytes();
    ValidateSilence(playable);

    // Create silence msg, convert to playable then split.  Check sizes/contents of each
    silence = iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs);
    playable = silence->CreatePlayable(44100, 8, 1);
    remainingPlayable = playable->Split(playable->Bytes() / 4);
    TEST(3 * playable->Bytes() == remainingPlayable->Bytes());
    TEST(playable->Bytes() + remainingPlayable->Bytes() == bytes);
    ValidateSilence(playable);
    ValidateSilence(remainingPlayable);

    // Create silence msg, split at non-sample boundary.  Check that fragments have the correct total length
    silence = iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs);
    playable = silence->CreatePlayable(44100, 8, 1);
    remainingPlayable = playable->Split((playable->Bytes() / 4) - 1);
    TEST(playable->Bytes() + remainingPlayable->Bytes() == bytes);
    playable->RemoveRef();
    remainingPlayable->RemoveRef();

    // Create silence msg, split at 1 jiffy (non-sample boundary).  Check initial msg has 0 Bytes() but can Write() its content
    silence = iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs);
    MsgSilence* remainingSilence = (MsgSilence*)silence->Split(1);
    playable = silence->CreatePlayable(44100, 8, 1);
    remainingPlayable = remainingSilence->CreatePlayable(44100, 8, 1);
    TEST(playable->Bytes() == 0);
    TEST(remainingPlayable->Bytes() == bytes);
    ValidateSilence(playable);
    remainingPlayable->RemoveRef();

    // clean destruction of class implies no leaked msgs
}

void SuiteMsgPlayable::ValidateSilence(MsgPlayable* aMsg)
{
    TUint bytes = aMsg->Bytes();
    ProcessorPcmBufPacked pcmProcessor;
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
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, kMsgCount, kMsgCount, kMsgCount, kMsgCount, kMsgCount, 1, 1, 1, 1, 1, 1, 1);
}

SuiteRamp::~SuiteRamp()
{
    delete iMsgFactory;
}

void SuiteRamp::Test()
{
    TUint jiffies = Jiffies::kJiffiesPerMs;

    // start=Ramp::kMax, direction=down, duration=fragmentSize.  Apply, check end is Ramp::kMin
    Ramp ramp;
    Ramp split;
    TUint splitPos;
    TEST(!ramp.Set(Ramp::kRampMax, jiffies, jiffies, Ramp::EDown, split, splitPos));
    TEST(ramp.Start() == Ramp::kRampMax);
    TEST(ramp.End() == Ramp::kRampMin);
    TEST(ramp.Direction() == Ramp::EDown);

    // start=Ramp::kMax, direction=up, duration=fragmentSize.  Check asserts as invalid to ramp up beyond max
    ramp.Reset();
    TEST_THROWS(ramp.Set(Ramp::kRampMax, jiffies, jiffies, Ramp::EUp, split, splitPos), AssertionFailed);

    // start=Ramp::kMin, direction=up, duration=fragmentSize.  Apply, check end is Ramp::kMax
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kRampMin, jiffies, jiffies, Ramp::EUp, split, splitPos));
    TEST(ramp.Start() == Ramp::kRampMin);
    TEST(ramp.End() == Ramp::kRampMax);
    TEST(ramp.Direction() == Ramp::EUp);

    // start=Ramp::kMax, direction=down, duration=2*fragmentSize.  Apply, check end is 50%
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kRampMax, jiffies, 2*jiffies, Ramp::EDown, split, splitPos));
    TEST(ramp.Start() == Ramp::kRampMax);
    TEST(ramp.End() == (Ramp::kRampMax - Ramp::kRampMin) / 2);
    TEST(ramp.Direction() == Ramp::EDown);

    // start=Ramp::kMin, direction=up, duration=2*fragmentSize.  Apply, check end is 50%
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kRampMin, jiffies, 2*jiffies, Ramp::EUp, split, splitPos));
    TEST(ramp.Start() == Ramp::kRampMin);
    TEST(ramp.End() == (Ramp::kRampMax - Ramp::kRampMin) / 2);
    TEST(ramp.Direction() == Ramp::EUp);

    // start=50%, direction=down, duration=4*fragmentSize.  Apply, check end is 25%
    ramp.Reset();
    TUint start = (Ramp::kRampMax - Ramp::kRampMin) / 2;
    TEST(!ramp.Set(start, jiffies, 4*jiffies, Ramp::EDown, split, splitPos));
    TEST(ramp.Start() == start);
    TEST(ramp.End() == (Ramp::kRampMax - Ramp::kRampMin) / 4);
    TEST(ramp.Direction() == Ramp::EDown);

    // start=50%, direction=up, duration=4*fragmentSize.  Apply, check end is 75%
    ramp.Reset();
    start = (Ramp::kRampMax - Ramp::kRampMin) / 2;
    TEST(!ramp.Set(start, jiffies, 4*jiffies, Ramp::EUp, split, splitPos));
    TEST(ramp.Start() == start);
    TEST(ramp.End() == Ramp::kRampMax - ((Ramp::kRampMax - Ramp::kRampMin) / 4));
    TEST(ramp.Direction() == Ramp::EUp);

    // Apply ramp [Max...Min].  Check start/end values and that subsequent values never rise
//    const TUint kNumChannels = 2;
    const TUint kAudioDataSize = 804;
    TByte audioData[kAudioDataSize];
    (void)memset(audioData, 0x7f, kAudioDataSize);
    Brn audioBuf(audioData, kAudioDataSize);

    ramp.Reset();
    TEST(!ramp.Set(Ramp::kRampMax, kAudioDataSize, kAudioDataSize, Ramp::EDown, split, splitPos));
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
    TEST(!ramp.Set(Ramp::kRampMax, kAudioDataSize, kAudioDataSize, Ramp::EDown, split, splitPos));
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
    TEST(!ramp.Set(Ramp::kRampMax, kAudioDataSize, kAudioDataSize, Ramp::EDown, split, splitPos));
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
    TEST(!ramp.Set(Ramp::kRampMin, kAudioDataSize, kAudioDataSize, Ramp::EUp, split, splitPos));
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
    TEST(!ramp.Set(Ramp::kRampMax, kAudioDataSize, kAudioDataSize*2, Ramp::EDown, split, splitPos));
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
    TEST(!ramp.Set(Ramp::kRampMin, kAudioDataSize, kAudioDataSize*2, Ramp::EUp, split, splitPos));
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
    TEST(!ramp.Set(Ramp::kRampMax / 2, kAudioDataSize, kAudioDataSize*4, Ramp::EDown, split, splitPos)); // *4 as the highest sample rate gives 4 jiffies per sample
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
    TEST(!ramp.Set(Ramp::kRampMax / 2, jiffies, 2 * jiffies, Ramp::EDown, split, splitPos));
    TEST(ramp.Set(Ramp::kRampMin, jiffies, 2 * jiffies, Ramp::EUp, split, splitPos));
    TEST(ramp.Start() == 0);
    TEST(ramp.End() == Ramp::kRampMax / 4);
    TEST(ramp.Direction() == Ramp::EUp);
    TEST(split.Start() == ramp.End());
    TEST(split.End() == 0);
    TEST(split.Direction() == Ramp::EDown);
    TEST(ramp.IsEnabled());
    TEST(split.IsEnabled());

    // Create [50%...25%] ramp.  Add [70%...30%] ramp.  Check original ramp is retained.
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kRampMax / 2, jiffies, 4 * jiffies, Ramp::EDown, split, splitPos));
    start = ramp.Start();
    TUint end = ramp.End();
    Ramp::EDirection direction = ramp.Direction();
    TEST(!ramp.Set(((TUint64)10 * Ramp::kRampMax) / 7, jiffies, (5 * jiffies) / 2, Ramp::EDown, split, splitPos));
    TEST(ramp.Start() == start);
    TEST(ramp.End() == end);
    TEST(ramp.Direction() == direction);

    // Create [50%...25%] ramp.  Add [40%...Min] ramp.  Check new ramp is used.
    ramp.Reset();
    TEST(!ramp.Set(Ramp::kRampMax / 2, jiffies, 4 * jiffies, Ramp::EDown, split, splitPos));
    start = ramp.Start();
    start = ((TUint64)2 * Ramp::kRampMax) / 5;
    TEST(!ramp.Set(start, jiffies, (5 * jiffies) / 2, Ramp::EDown, split, splitPos));
    TEST(ramp.Start() == start);
    TEST(ramp.End() == 0);
    TEST(ramp.Direction() == Ramp::EDown);

    // Create MsgSilence.  Set [Max...Min] ramp.  Convert to playable and check output is all zeros
    MsgSilence* silence = iMsgFactory->CreateMsgSilence(jiffies);
    MsgAudio* remaining = NULL;
    TEST(Ramp::kRampMin == silence->SetRamp(Ramp::kRampMax, jiffies, Ramp::EDown, remaining));
    TEST(remaining == NULL);
    MsgPlayable* playable = silence->CreatePlayable(44100, 8, 2);
    TEST(playable != NULL);
    ProcessorPcmBufPacked pcmProcessor;
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
    MsgAudioPcm* audioPcm = iMsgFactory->CreateMsgAudioPcm(encodedAudio, kNumChannels, 44100, 16, EMediaDataLittleEndian, 0);
    jiffies = audioPcm->Jiffies();
    TEST(Ramp::kRampMin == audioPcm->SetRamp(Ramp::kRampMax / 2, jiffies*2, Ramp::EDown, remaining));
    TEST(Ramp::kRampMin == audioPcm->SetRamp(Ramp::kRampMin, jiffies*2, Ramp::EUp, remaining));
    TEST(remaining != NULL);
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
    silence = iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs * 17);
    MsgSilence* silence2 = iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs * 23);
    const TUint duration = silence->Jiffies() + silence2->Jiffies();
    TUint currentRamp = Ramp::kRampMax;
    currentRamp = silence->SetRamp(currentRamp, duration, Ramp::EDown, remaining);
    currentRamp = silence2->SetRamp(currentRamp, duration, Ramp::EDown, remaining);
    TEST(currentRamp == Ramp::kRampMin);
    silence->RemoveRef();
    silence2->RemoveRef();
}


// SuiteAudioStream

SuiteAudioStream::SuiteAudioStream()
    : Suite("MsgAudioStream tests")
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 1, 1, 1, 1, 1, 1, 1, kMsgAudioStreamCount, 1, 1, 1, 1);
}

SuiteAudioStream::~SuiteAudioStream()
{
    delete iMsgFactory;
}

void SuiteAudioStream::Test()
{
    // create MetaText msg, check its text can be retrieved
    Brn uri("http://255.1.33.76:8734/path?query");
    Brn metaText("metaText");
    MsgAudioStream* msg = iMsgFactory->CreateMsgAudioStream(uri, metaText);
    TEST(msg != NULL);
    TEST(msg->Uri() == uri);
    TEST(msg->MetaText() == metaText);
    msg->RemoveRef();

#ifdef DEFINE_DEBUG
    // access freed msg (doesn't bother valgrind as this is still allocated memory).  Check text has been cleared.
    TEST(msg->Uri() != uri);
    TEST(msg->MetaText() != metaText);
#endif

    // create second MetaText msg, check its text can be retrieved
    uri.Set("http://3.4.5.6:8");
    metaText.Set("updated");
    msg = iMsgFactory->CreateMsgAudioStream(uri, metaText);
    TEST(msg != NULL);
    TEST(msg->Uri() == uri);
    TEST(msg->MetaText() == metaText);
    msg->RemoveRef();
}


// SuiteMetaText

SuiteMetaText::SuiteMetaText()
    : Suite("MsgMetaText tests")
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, kMsgMetaTextCount, 1, 1, 1);
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
    TEST(msg != NULL);
    TEST(msg->MetaText() == metaText);
    msg->RemoveRef();

#ifdef DEFINE_DEBUG
    // access freed msg (doesn't bother valgrind as this is still allocated memory).  Check text has been cleared.
    TEST(msg->MetaText() != metaText);
#endif

    // create second MetaText msg, check its text can be retrieved
    metaText.Set("updated");
    msg = iMsgFactory->CreateMsgMetaText(metaText);
    TEST(msg != NULL);
    TEST(msg->MetaText() == metaText);
    msg->RemoveRef();
}


// SuiteAudioFormat

SuiteAudioFormat::SuiteAudioFormat()
    : Suite("MsgAudioFormat tests")
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 1, 1, 1, 1, 1, 1, kMsgAudioFormatCount, 1, 1, 1, 1, 1);
}

SuiteAudioFormat::~SuiteAudioFormat()
{
    delete iMsgFactory;
}

void SuiteAudioFormat::Test()
{
    // create AudioFormat msg, check its text can be retrieved
    TUint bitRate = 128; // nonsense value but doesn't matter for this test
    TUint bitDepth = 16;
    TUint sampleRate = 44100;
    TUint numChannels = 2;
    Brn codecName("test codec");
    TUint64 trackLength = 1<<16;
    TBool lossless = true;
    MsgAudioFormat* msg = iMsgFactory->CreateMsgAudioFormat(bitRate, bitDepth, sampleRate, numChannels, codecName, trackLength, lossless);
    TEST(msg != NULL);
    TEST(msg->Format().BitRate() == bitRate);
    TEST(msg->Format().BitDepth() == bitDepth);
    TEST(msg->Format().SampleRate() == sampleRate);
    TEST(msg->Format().NumChannels() == numChannels);
    TEST(msg->Format().CodecName() == codecName);
    TEST(msg->Format().TrackLength() == trackLength);
    TEST(msg->Format().Lossless() == lossless);
    msg->RemoveRef();

#ifdef DEFINE_DEBUG
    // access freed msg (doesn't bother valgrind as this is still allocated memory).  Check text has been cleared.
    TEST(msg->Format().BitRate() != bitRate);
    TEST(msg->Format().BitDepth() != bitDepth);
    TEST(msg->Format().SampleRate() != sampleRate);
    TEST(msg->Format().NumChannels() != numChannels);
    TEST(msg->Format().CodecName() != codecName);
    TEST(msg->Format().TrackLength() != trackLength);
    TEST(msg->Format().Lossless() != lossless);
#endif

    // create second MetaText msg, check its text can be retrieved
    bitRate = 700;
    bitDepth = 24;
    sampleRate = 192000;
    numChannels = 1;
    codecName.Set("new codec name (a bit longer)");
    trackLength = 1<<30;
    lossless = false;
    msg = iMsgFactory->CreateMsgAudioFormat(bitRate, bitDepth, sampleRate, numChannels, codecName, trackLength, lossless);
    TEST(msg != NULL);
    TEST(msg->Format().BitRate() == bitRate);
    TEST(msg->Format().BitDepth() == bitDepth);
    TEST(msg->Format().SampleRate() == sampleRate);
    TEST(msg->Format().NumChannels() == numChannels);
    TEST(msg->Format().CodecName() == codecName);
    TEST(msg->Format().TrackLength() == trackLength);
    TEST(msg->Format().Lossless() == lossless);
    msg->RemoveRef();
}


// SuiteMsgProcessor

SuiteMsgProcessor::SuiteMsgProcessor()
    : Suite("IMsgProcessor tests")
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
}

SuiteMsgProcessor::~SuiteMsgProcessor()
{
    delete iMsgFactory;
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

    MsgAudioPcm* audioPcm = iMsgFactory->CreateMsgAudioPcm(audioBuf, 2, 44100, 8, EMediaDataLittleEndian, 0);
    TEST(audioPcm == static_cast<Msg*>(audioPcm)->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgAudioPcm);
    MsgPlayable* playable = audioPcm->CreatePlayable();
    TEST(playable == static_cast<Msg*>(playable)->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgPlayable);
    playable->RemoveRef();

    MsgSilence* silence = iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs);
    TEST(silence == static_cast<Msg*>(silence)->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgSilence);
    playable = silence->CreatePlayable(44100, 8, 2);
    TEST(playable == static_cast<Msg*>(playable)->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgPlayable);
    playable->RemoveRef();

    Msg* msg = iMsgFactory->CreateMsgAudioFormat(0, 0, 0, 0, Brx::Empty(), 0, false);
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgAudioFormat);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgTrack();
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgTrack);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgAudioStream(Brn("http://1.2.3.4:5"), Brn("Test metatext"));
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgAudioStream);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgMetaText(Brn("Test metatext"));
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgMetaText);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgHalt();
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgHalt);
    msg->RemoveRef();

    msg = iMsgFactory->CreateMsgFlush();
    TEST(msg == msg->Process(processor));
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgFlush);
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

Msg* ProcessorMsgType::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgAudioEncoded;
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

Msg* ProcessorMsgType::ProcessMsg(MsgAudioFormat* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgAudioFormat;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgTrack* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgTrack;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgAudioStream* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgAudioStream;
    return aMsg;
}

Msg* ProcessorMsgType::ProcessMsg(MsgMetaText* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgMetaText;
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

Msg* ProcessorMsgType::ProcessMsg(MsgQuit* aMsg)
{
    iLastMsgType = ProcessorMsgType::EMsgQuit;
    return aMsg;
}


// SuiteMsgQueue

SuiteMsgQueue::SuiteMsgQueue()
    : Suite("MsgQueue tests")
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
}

SuiteMsgQueue::~SuiteMsgQueue()
{
    delete iMsgFactory;
}

void SuiteMsgQueue::Test()
{
    MsgQueue* queue = new MsgQueue();
    
    // queue can be populated and read from
    TEST(queue->IsEmpty());
    Msg* msg = iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs);
    queue->Enqueue(msg);
    TEST(!queue->IsEmpty());
    Msg* dequeued = queue->Dequeue();
    TEST(msg == dequeued);
    TEST(queue->IsEmpty());
    dequeued->RemoveRef();

    // queue can be emptied then reused
    msg = iMsgFactory->CreateMsgTrack();
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
    msg = iMsgFactory->CreateMsgFlush();
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
    TEST(queue->IsEmpty());
    dequeued->Process(processor);
    TEST(processor.LastMsgType() == ProcessorMsgType::EMsgQuit);
    dequeued->RemoveRef();

    // EnqueueAtHead skips existing items
    msg = iMsgFactory->CreateMsgMetaText(Brn("blah"));
    queue->Enqueue(msg);
    msg = iMsgFactory->CreateMsgHalt();
    queue->Enqueue(msg);
    msg = iMsgFactory->CreateMsgFlush();
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

    // FIXME - no check yet that reading from an empty queue blocks
    
    delete queue;
}


// SuiteMsgQueueFlushable

SuiteMsgQueueFlushable::SuiteMsgQueueFlushable()
    : Suite("MsgQueueFlushable tests")
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1);
}

SuiteMsgQueueFlushable::~SuiteMsgQueueFlushable()
{
    delete iMsgFactory;
}

void SuiteMsgQueueFlushable::Test()
{
    // Add msg of each type.  After each addition, check type of last in and that only audio increases Jiffies()
    // Dequeue msgs.  After each, check type of last out and that only audio decreases Jiffies()

    TestMsgQueueFlushable* queue = new TestMsgQueueFlushable();
    TUint jiffies = queue->Jiffies();
    TEST(jiffies == 0);
    TEST(queue->LastIn() == TestMsgQueueFlushable::ENone);
    TEST(queue->LastOut() == TestMsgQueueFlushable::ENone);

    Msg* msg = iMsgFactory->CreateMsgTrack();
    queue->Enqueue(msg);
    jiffies = queue->Jiffies();
    TEST(jiffies == 0);
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgTrack);
    TEST(queue->LastOut() == TestMsgQueueFlushable::ENone);

    msg = iMsgFactory->CreateMsgAudioStream(Brn("http://1.2.3.4:5"), Brn("metatext"));
    queue->Enqueue(msg);
    TEST(queue->Jiffies() == 0);
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgAudioStream);
    TEST(queue->LastOut() == TestMsgQueueFlushable::ENone);

    MsgAudio* audio = iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs);
    queue->Enqueue(audio);
    TEST(queue->Jiffies() == jiffies + audio->Jiffies());
    jiffies = queue->Jiffies();
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgSilence);
    TEST(queue->LastOut() == TestMsgQueueFlushable::ENone);

    msg = iMsgFactory->CreateMsgMetaText(Brn("foo"));
    queue->Enqueue(msg);
    TEST(queue->Jiffies() == jiffies);
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgMetaText);
    TEST(queue->LastOut() == TestMsgQueueFlushable::ENone);

    msg = iMsgFactory->CreateMsgQuit();
    queue->Enqueue(msg);
    TEST(queue->Jiffies() == jiffies);
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgQuit);
    TEST(queue->LastOut() == TestMsgQueueFlushable::ENone);

    const TUint kDataBytes = 256;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0xab, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, 2, 44100, 8, EMediaDataLittleEndian, 0);
    const TUint audioJiffies = audio->Jiffies();
    queue->Enqueue(audio);
    TEST(queue->Jiffies() == jiffies + audioJiffies);
    jiffies = queue->Jiffies();
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgAudioPcm);
    TEST(queue->LastOut() == TestMsgQueueFlushable::ENone);

    msg = iMsgFactory->CreateMsgHalt();
    queue->Enqueue(msg);
    TEST(queue->Jiffies() == jiffies);
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgHalt);
    TEST(queue->LastOut() == TestMsgQueueFlushable::ENone);

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgHalt);
    TEST(queue->LastOut() == TestMsgQueueFlushable::EMsgTrack);
    TEST(queue->Jiffies() == jiffies);
    msg->RemoveRef();

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgHalt);
    TEST(queue->LastOut() == TestMsgQueueFlushable::EMsgAudioStream);
    TEST(queue->Jiffies() == jiffies);
    msg->RemoveRef();

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgHalt);
    TEST(queue->LastOut() == TestMsgQueueFlushable::EMsgSilence);
    TEST(queue->Jiffies() == jiffies - Jiffies::kJiffiesPerMs);
    jiffies = queue->Jiffies();
    msg->RemoveRef();

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgHalt);
    TEST(queue->LastOut() == TestMsgQueueFlushable::EMsgMetaText);
    TEST(queue->Jiffies() == jiffies);
    msg->RemoveRef();

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgHalt);
    TEST(queue->LastOut() == TestMsgQueueFlushable::EMsgQuit);
    TEST(queue->Jiffies() == jiffies);
    msg->RemoveRef();

    queue->SplitNextAudio();
    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgAudioPcm);
    TEST(queue->LastOut() == TestMsgQueueFlushable::EMsgAudioPcm);
    TEST(queue->Jiffies() == jiffies - (audioJiffies/2));
    jiffies = queue->Jiffies();
    msg->RemoveRef();
    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgAudioPcm);
    TEST(queue->LastOut() == TestMsgQueueFlushable::EMsgAudioPcm);
    TEST(queue->Jiffies() == 0);
    msg->RemoveRef();

    msg = queue->Dequeue();
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgAudioPcm);
    TEST(queue->LastOut() == TestMsgQueueFlushable::EMsgHalt);
    TEST(queue->Jiffies() == 0);
    msg->RemoveRef();

    // Add some msgs then a Flush.  Add another msg.  Check dequeue delivers that last msg.
    /*msg = iMsgFactory->CreateMsgFlush();
    queue->Enqueue(msg);
    TEST(queue->Jiffies() == jiffies);
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgFlush);
    TEST(queue->LastOut() == TestMsgQueueFlushable::ENone);*/
    queue->Enqueue(iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs));
    queue->Enqueue(iMsgFactory->CreateMsgTrack());
    queue->Enqueue(iMsgFactory->CreateMsgSilence(2 * Jiffies::kJiffiesPerMs));
    TEST(queue->Jiffies() == 3 * Jiffies::kJiffiesPerMs);
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgSilence);
    TEST(queue->LastOut() == TestMsgQueueFlushable::EMsgHalt);
    queue->Enqueue(iMsgFactory->CreateMsgFlush());
    TEST(queue->Jiffies() == 3 * Jiffies::kJiffiesPerMs);
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgFlush);
    TEST(queue->LastOut() == TestMsgQueueFlushable::EMsgHalt);
    queue->Enqueue(iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, 2, 44100, 8, EMediaDataLittleEndian, 0));
    TEST(queue->Jiffies() == (3 * Jiffies::kJiffiesPerMs) + audioJiffies);
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgAudioPcm);
    TEST(queue->LastOut() == TestMsgQueueFlushable::EMsgHalt);
    msg = queue->Dequeue();
    TEST(queue->Jiffies() == audioJiffies);
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgAudioPcm);
    TEST(queue->LastOut() == TestMsgQueueFlushable::EMsgFlush);
    msg->RemoveRef();
    msg = queue->Dequeue();
    TEST(queue->Jiffies() == 0);
    TEST(queue->LastIn() == TestMsgQueueFlushable::EMsgAudioPcm);
    TEST(queue->LastOut() == TestMsgQueueFlushable::EMsgAudioPcm);
    msg->RemoveRef();

    delete queue;
}


// TestMsgQueueFlushable

TestMsgQueueFlushable::TestMsgQueueFlushable()
    : iLastMsgIn(ENone)
    , iLastMsgOut(ENone)
    , iSplitNextAudio(false)
{
}
    
Msg* TestMsgQueueFlushable::ProcessMsgAudioOut(MsgAudio* aMsgAudio)
{
    if (iSplitNextAudio) {
        iSplitNextAudio = false;
        MsgAudio* remaining = aMsgAudio->Split(aMsgAudio->Jiffies() / 2);
        EnqueueAtHead(remaining);
    }
    return aMsgAudio;
}
    
void TestMsgQueueFlushable::ProcessMsgIn(MsgAudioPcm* /*aMsg*/)
{
    iLastMsgIn = EMsgAudioPcm;
}

void TestMsgQueueFlushable::ProcessMsgIn(MsgSilence* /*aMsg*/)
{
    iLastMsgIn = EMsgSilence;
}

void TestMsgQueueFlushable::ProcessMsgIn(MsgTrack* /*aMsg*/)
{
    iLastMsgIn = EMsgTrack;
}

void TestMsgQueueFlushable::ProcessMsgIn(MsgAudioStream* /*aMsg*/)
{
    iLastMsgIn = EMsgAudioStream;
}

void TestMsgQueueFlushable::ProcessMsgIn(MsgMetaText* /*aMsg*/)
{
    iLastMsgIn = EMsgMetaText;
}

void TestMsgQueueFlushable::ProcessMsgIn(MsgHalt* /*aMsg*/)
{
    iLastMsgIn = EMsgHalt;
}

void TestMsgQueueFlushable::ProcessMsgIn(MsgFlush* /*aMsg*/)
{
    iLastMsgIn = EMsgFlush;
}

void TestMsgQueueFlushable::ProcessMsgIn(MsgQuit* /*aMsg*/)
{
    iLastMsgIn = EMsgQuit;
}

Msg* TestMsgQueueFlushable::ProcessMsgOut(MsgAudioPcm* aMsg)
{
    iLastMsgOut = EMsgAudioPcm;
    return ProcessMsgAudioOut(aMsg);
}

Msg* TestMsgQueueFlushable::ProcessMsgOut(MsgSilence* aMsg)
{
    iLastMsgOut = EMsgSilence;
    return ProcessMsgAudioOut(aMsg);
}

Msg* TestMsgQueueFlushable::ProcessMsgOut(MsgTrack* aMsg)
{
    iLastMsgOut = EMsgTrack;
    return aMsg;
}

Msg* TestMsgQueueFlushable::ProcessMsgOut(MsgAudioStream* aMsg)
{
    iLastMsgOut = EMsgAudioStream;
    return aMsg;
}

Msg* TestMsgQueueFlushable::ProcessMsgOut(MsgMetaText* aMsg)
{
    iLastMsgOut = EMsgMetaText;
    return aMsg;
}

Msg* TestMsgQueueFlushable::ProcessMsgOut(MsgHalt* aMsg)
{
    iLastMsgOut = EMsgHalt;
    return aMsg;
}

Msg* TestMsgQueueFlushable::ProcessMsgOut(MsgFlush* aMsg)
{
    iLastMsgOut = EMsgFlush;
    return aMsg;
}

Msg* TestMsgQueueFlushable::ProcessMsgOut(MsgQuit* aMsg)
{
    iLastMsgOut = EMsgQuit;
    return aMsg;
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
    runner.Add(new SuiteAudioFormat());
    runner.Add(new SuiteMsgProcessor());
    runner.Add(new SuiteMsgQueue());
    runner.Add(new SuiteMsgQueueFlushable());
    runner.Run();
}


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestMsg();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
