#ifndef HEADER_TESTCODECCONTROLLER
#define HEADER_TESTCODECCONTROLLER

#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Media/MimeTypeList.h>

#include <list>
#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

namespace OpenHome {
namespace Media {

class TestCodecControllerDummyCodec : public Codec::CodecBase
{
private:
    static const TChar* kId;
public:
    TestCodecControllerDummyCodec(TUint aReadBufBytes);
    void SetStreamInfo(TUint aReadBytes, TUint aChannels, TUint aSampleRate, TUint aBitDepth, AudioDataEndian aEndianness, const SpeakerProfile& aProfile);
public: // from CodecBase
    TBool Recognise(const EncodedStreamInfo& aStreamInfo) override;
    void StreamInitialise() override;
    void Process() override;
    TBool TrySeek(TUint aStreamId, TUint64 aSample) override;
    void StreamCompleted() override;
protected:
    Bwh iReadBuf;
    TUint iReadBytes;
    TUint iChannels;
    TUint iSampleRate;
    TUint iBitDepth;
    AudioDataEndian iEndianness;
    SpeakerProfile iProfile;
    TUint64 iTrackOffset;
};

class SuiteCodecControllerBase : public SuiteUnitTest
                               , private IPipelineElementUpstream
                               , private IPipelineElementDownstream
                               , private IStreamHandler
                               , private IUrlBlockWriter
                               , private IMsgProcessor
{
public:
    SuiteCodecControllerBase(const TChar* aName);
protected: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryDiscard(TUint aJiffies) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private: // from IUrlBlockWriter
    TBool TryGet(IWriter& aWriter, const Brx& aUrl, TUint64 aOffset, TUint aBytes) override;
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
protected:
    enum EMsgType
    {
        ENone
       ,EMsgMode
       ,EMsgTrack
       ,EMsgDrain
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgStreamInterrupted
       ,EMsgDecodedStream
       ,EMsgBitRate
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgQuit
    };
protected:
    void Queue(Msg* aMsg);
    void PullNext();
    void PullNext(EMsgType aExpectedMsg);
    void PullNext(EMsgType aExpectedMsg, TUint64 aExpectedJiffies);
    Msg* CreateTrack();
    Msg* CreateEncodedStream();
    MsgFlush* CreateFlush();
protected:
    static const TUint kMaxMsgBytes = 960;
    static const TUint kWavHeaderBytes = 44;
    static const TUint kSampleRate = 44100;
    static const TUint kNumChannels = 2;
    static const SpeakerProfile kProfile;
    static const TUint kExpectedFlushId = 5;
    static const TUint kSemWaitMs = 5000;   // only required in case tests fail
    MsgFactory* iMsgFactory;
    CodecController* iController;
    Semaphore* iSemStop;
    TUint iTotalBytes;
    TUint64 iTrackOffset;
    TUint iTrackOffsetBytes;
    TUint64 iJiffies;
    TUint64 iMsgOffset;
    TUint iStopCount;
    TUint iStreamId;
    IStreamHandler* iStreamHandler;
    std::list<Msg*> iPendingMsgs;
    std::list<Msg*> iReceivedMsgs;
    EMsgType iLastReceivedMsg;
private:
    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    Semaphore* iSemPending;
    Semaphore* iSemReceived;
    Mutex* iLockPending;
    Mutex* iLockReceived;
    TUint iNextStreamId;
    TBool iSeekable;
};

class SuiteCodecControllerStream : public SuiteCodecControllerBase
                                 , public ISeekObserver
                                 , private IMimeTypeList
{
public:
    SuiteCodecControllerStream();
private: // from SuiteCodecControllerBase
    void Setup() override;
    void TearDown() override;
private: // from SuiteCodecControllerBase
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
private: // from ISeekObserver
    void NotifySeekComplete(TUint aHandle, TUint aFlushId) override;
private: // from IMimeTypeList
    void Add(const TChar* aMimeType) override;
private:
    static void WriteUint16Le(WriterBinary& aWriter, TUint16 aValue);
    static void WriteUint32Le(WriterBinary& aWriter, TUint32 aValue);
    Msg* CreateAudio(TBool aValidHeader, TUint aDataBytes);
    void TestStreamSuccessful();
    void TestRecognitionFail();
    void TestTruncatedStreamInRecognition();
    void TestNoDataAfterRecognition();
    void TestTruncatedStream();
    void TestTrackTrack();
    void TestTrackMetatext();
    void TestTrackEncodedStreamMetatext();
    void TestSeek();
    void TestSeekNewStream();
private:
    Semaphore* iSemSeek;
    TUint iHandle;
    TUint iExpectedFlushId;
    TUint iFlushId;
};

class SuiteCodecControllerPcmSize : public SuiteCodecControllerBase
{
private:
    static const TUint kBitsPerSample = 16;
    static const TUint kSamplesPerMsg = 16;
    static const TUint kAudioBytesPerMsg = 2*2*kSamplesPerMsg; // 16 bits (2 bytes) * 2 channels * kSamplesPerMsg
public:
    SuiteCodecControllerPcmSize();
private: // // from SuiteCodecControllerBase
    void Setup() override;
    void TearDown() override;
private:
    Msg* CreateAudio();
    void TestPcmIsExpectedSize();
private:
    TestCodecControllerDummyCodec* iCodec;
};

class TestCodecControllerDummyCodecStreamInitialise : public TestCodecControllerDummyCodec
{
public:
    TestCodecControllerDummyCodecStreamInitialise(TUint aReadBufBytes, Semaphore& aSemStreamInitPending, Semaphore& aSemStreamInitContinue);
public: // from TestCodecControllerDummyCodec
    void StreamInitialise() override;
private:
    Semaphore& iSemStreamInitPending;   // Notifies test code that StreamInitialise() has been entered.
    Semaphore& iSemStreamInitContinue;  // Blocks output of MsgDecodedStream until signalled.
};

class SuiteCodecControllerStopDuringStreamInit : public SuiteCodecControllerBase
{
private:
    static const TUint kAudioBytesPerMsg = 1024;
public:
    SuiteCodecControllerStopDuringStreamInit();
private: // from SuiteCodecControllerBase
    void Setup() override;
    void TearDown() override;
private:
    void TestStopDuringStreamInit();
private:
    Semaphore* iSemStreamInitPending;
    Semaphore* iSemStreamInitContinue;
    TestCodecControllerDummyCodecStreamInitialise* iCodec;
};

class SuiteCodecControllerSeekInvalid : public SuiteCodecControllerBase, public ISeekObserver
{
private:
    static const TUint kAudioBytesPerMsg = 1024;
public:
    SuiteCodecControllerSeekInvalid();
private: // from SuiteCodecControllerBase
    void Setup() override;
    void TearDown() override;
private: // from SuiteCodecControllerBase
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
private: // from ISeekObserver
    void NotifySeekComplete(TUint aHandle, TUint aFlushId) override;
private:
    void TestSeekInvalid();
private:
    Semaphore* iSemSeek;
    TUint iHandle;
    TUint iFlushId;
    TestCodecControllerDummyCodec* iCodec;
};

/**
 * Misbehaving codec that buffers some of its decoded audio and attempts to
 * flush its internal buffer when it detects a CodecStreamStart/CodecStreamEnded
 * has been thrown.
 *
 * Simulates codecs that have some internal buffering to avoid outputting lots
 * small MsgAudioPcm into the pipeline.
 */
class TestCodecControllerDummyCodecBuffered : public TestCodecControllerDummyCodec
{
public:
    TestCodecControllerDummyCodecBuffered(TUint aReadBufBytes);
public: // from TestCodecControllerDummyCodec
    void Process() override;
private:
    Bwh iOutBuf;
};

class SuiteCodecControllerUnexpectedFlush : public SuiteCodecControllerBase
{
private:
    static const TUint kAudioBytesPerMsg = 1024;
public:
    SuiteCodecControllerUnexpectedFlush();
private: // from SuiteCodecControllerBase
    void Setup() override;
    void TearDown() override;
private:
    void TestUnexpectedFlush();
private:
    TestCodecControllerDummyCodecBuffered* iCodec;
};

} // namespace Media
} // namespace OpenHome


// SuiteCodecControllerBase

const SpeakerProfile SuiteCodecControllerBase::kProfile(2);

SuiteCodecControllerBase::SuiteCodecControllerBase(const TChar* aName)
    : SuiteUnitTest(aName)
{
}

void SuiteCodecControllerBase::Setup()
{
    iTrackFactory = new TrackFactory(iInfoAggregator, 5);
    // Need so many (Msg)AudioEncoded because kMaxMsgBytes is currently 960, and msgs are queued in advance of being pulled for these tests.
    MsgFactoryInitParams init;
    init.SetMsgAudioEncodedCount(400, 400);
    init.SetMsgAudioPcmCount(900, 900);
    init.SetMsgSilenceCount(10);
    init.SetMsgPlayableCount(50, 0);
    init.SetMsgTrackCount(2);
    init.SetMsgEncodedStreamCount(2);
    init.SetMsgMetaTextCount(2);
    init.SetMsgHaltCount(2);
    init.SetMsgFlushCount(2);
    init.SetMsgDecodedStreamCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iController = new CodecController(*iMsgFactory, *this, *this, *this, Jiffies::kPerMs * 5, kPriorityNormal, true);
    iSemPending = new Semaphore("TCSP", 0);
    iSemReceived = new Semaphore("TCSR", 0);
    iSemStop = new Semaphore("TCSS", 0);
    iLockPending = new Mutex("TCMP");
    iLockReceived = new Mutex("TCMR");
    iStreamId = UINT_MAX;
    iStreamHandler = nullptr;
    iNextStreamId = 0;
    iTotalBytes = iTrackOffsetBytes = 0;
    iTrackOffset = 0;
    iJiffies = 0;
    iMsgOffset = 0;
    iSeekable = true;
    iStopCount = 0;
}

void SuiteCodecControllerBase::TearDown()
{
    Queue(iMsgFactory->CreateMsgQuit());
    do {
        PullNext();
    } while (iLastReceivedMsg != EMsgQuit);

    iLockPending->Wait();
    ASSERT(iPendingMsgs.size() == 0);
    iLockPending->Signal();
    iLockReceived->Wait();
    ASSERT(iReceivedMsgs.size() == 0);
    iLockReceived->Signal();

    delete iLockReceived;
    delete iLockPending;
    delete iSemStop;
    delete iSemReceived;
    delete iSemPending;
    delete iController;
    delete iMsgFactory;
    delete iTrackFactory;
}

Msg* SuiteCodecControllerBase::Pull()
{
    // This is called from CodecController's own thread, so block until msg
    // available.

    iSemPending->Wait(kSemWaitMs);
    AutoMutex a(*iLockPending);
    ASSERT(iPendingMsgs.size() > 0);
    Msg* msg = iPendingMsgs.front();
    iPendingMsgs.pop_front();
    return msg;
}

void SuiteCodecControllerBase::Push(Msg* aMsg)
{
    iLockReceived->Wait();
    iReceivedMsgs.push_back(aMsg);
    iLockReceived->Signal();
    iSemReceived->Signal();
}

EStreamPlay SuiteCodecControllerBase::OkToPlay(TUint /*aStreamId*/)
{
    return ePlayNo;
}

TUint SuiteCodecControllerBase::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteCodecControllerBase::TryDiscard(TUint /*aJiffies*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteCodecControllerBase::TryStop(TUint aStreamId)
{
    iStopCount++;
    iSemStop->Signal();
    if (aStreamId == iStreamId) {
        return kExpectedFlushId;
    }
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

void SuiteCodecControllerBase::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/, TBool /*aStarving*/)
{
}

TBool SuiteCodecControllerBase::TryGet(IWriter& /*aWriter*/, const Brx& /*aUrl*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return false;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgMode* aMsg)
{
    iLastReceivedMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgTrack* aMsg)
{
    iLastReceivedMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgDrain* aMsg)
{
    iLastReceivedMsg = EMsgDrain;
    return aMsg;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgDelay* aMsg)
{
    iLastReceivedMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastReceivedMsg = EMsgEncodedStream;
    iStreamId = aMsg->StreamId();
    iStreamHandler = aMsg->StreamHandler();
    return aMsg;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgMetaText* aMsg)
{
    iLastReceivedMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastReceivedMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgHalt* aMsg)
{
    iLastReceivedMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgFlush* aMsg)
{
    iLastReceivedMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgWait* aMsg)
{
    iLastReceivedMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastReceivedMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgBitRate* aMsg)
{
    iLastReceivedMsg = EMsgBitRate;
    return aMsg;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastReceivedMsg = EMsgAudioPcm;
    iMsgOffset = aMsg->TrackOffset();
    iJiffies += aMsg->Jiffies();
    MsgPlayable* playable = aMsg->CreatePlayable();
    ProcessorPcmBufTest pcmProcessor;
    playable->Read(pcmProcessor);
    Brn buf(pcmProcessor.Buf());
    ASSERT(buf.Bytes() >= 4);   // check we have enough bytes to examine first
                                // and last subsamples before manipulating pointers
    const TByte* ptr = buf.Ptr();
    const TUint bytes = buf.Bytes();
    const TUint firstSubsample = (ptr[0]<<8) | ptr[1];
    TEST(firstSubsample == 0x7f7f);
    const TUint lastSubsample = (ptr[bytes-2]<<8) | ptr[bytes-1];
    TEST(lastSubsample == 0x7f7f);

    return playable;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgSilence* aMsg)
{
    iLastReceivedMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteCodecControllerBase::ProcessMsg(MsgQuit* aMsg)
{
    iLastReceivedMsg = EMsgQuit;
    return aMsg;
}

void SuiteCodecControllerBase::Queue(Msg* aMsg)
{
    iLockPending->Wait();
    iPendingMsgs.push_back(aMsg);
    iLockPending->Signal();
    iSemPending->Signal();
}

void SuiteCodecControllerBase::PullNext()
{
    iSemReceived->Wait(kSemWaitMs);
    iLockReceived->Wait();
    ASSERT(iReceivedMsgs.size() > 0);
    Msg* msg = iReceivedMsgs.front();
    iReceivedMsgs.pop_front();
    iLockReceived->Signal();

    msg = msg->Process(*this);
    msg->RemoveRef();
    //Log::Print("SuiteCodecControllerBase::PullNext iLastReceivedMsg: %u, aExpectedMsg: %u\n", iLastReceivedMsg, aExpectedMsg);
}

void SuiteCodecControllerBase::PullNext(EMsgType aExpectedMsg)
{
    PullNext();
    TEST(iLastReceivedMsg == aExpectedMsg);
}

void SuiteCodecControllerBase::PullNext(EMsgType aExpectedMsg, TUint64 aExpectedJiffies)
{
    TUint64 jiffiesStart = iJiffies;
    PullNext(aExpectedMsg);
    TUint64 jiffiesDiff = iJiffies - jiffiesStart;
    //Log::Print("jiffiesDiff: %llu, aExpectedJiffies: %llu\n", jiffiesDiff, aExpectedJiffies);
    TEST(jiffiesDiff == aExpectedJiffies);
}

Msg* SuiteCodecControllerBase::CreateTrack()
{
    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    Msg* msg = iMsgFactory->CreateMsgTrack(*track);
    track->RemoveRef();
    return msg;
}

Msg* SuiteCodecControllerBase::CreateEncodedStream()
{
    return iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 1<<21, 0, ++iNextStreamId, iSeekable, false, Multiroom::Allowed, this);
}

MsgFlush* SuiteCodecControllerBase::CreateFlush()
{
    return iMsgFactory->CreateMsgFlush(kExpectedFlushId);
}


// SuiteCodecControllerStream

SuiteCodecControllerStream::SuiteCodecControllerStream()
    : SuiteCodecControllerBase("SuiteCodecControllerStream")
{
    AddTest(MakeFunctor(*this, &SuiteCodecControllerStream::TestStreamSuccessful), "TestStreamSuccessful");
    AddTest(MakeFunctor(*this, &SuiteCodecControllerStream::TestRecognitionFail), "TestRecognitionFail");
    AddTest(MakeFunctor(*this, &SuiteCodecControllerStream::TestTrackTrack), "TestTrackTrack");
    AddTest(MakeFunctor(*this, &SuiteCodecControllerStream::TestTrackMetatext), "TestTrackMetatext");
    AddTest(MakeFunctor(*this, &SuiteCodecControllerStream::TestTrackEncodedStreamMetatext), "TestTrackEncodedStreamMetatext");
    AddTest(MakeFunctor(*this, &SuiteCodecControllerStream::TestTruncatedStreamInRecognition), "TestTruncatedStreamInRecognition");
    AddTest(MakeFunctor(*this, &SuiteCodecControllerStream::TestNoDataAfterRecognition), "TestNoDataAfterRecognition");
    AddTest(MakeFunctor(*this, &SuiteCodecControllerStream::TestTruncatedStream), "TestTruncatedStream");
    AddTest(MakeFunctor(*this, &SuiteCodecControllerStream::TestSeek), "TestSeek");
    AddTest(MakeFunctor(*this, &SuiteCodecControllerStream::TestSeekNewStream), "TestSeekNewStream");
}

void SuiteCodecControllerStream::Setup()
{
    SuiteCodecControllerBase::Setup();
    iSemSeek = new Semaphore("SCCS", 0);
    iHandle = ISeeker::kHandleError;
    iExpectedFlushId = iFlushId = MsgFlush::kIdInvalid;
    iController->AddCodec(CodecFactory::NewWav(*this));
    iController->Start();
}

void SuiteCodecControllerStream::TearDown()
{
    delete iSemSeek;
    SuiteCodecControllerBase::TearDown();
}

TUint SuiteCodecControllerStream::TrySeek(TUint aStreamId, TUint64 /*aOffset*/)
{
    TEST(aStreamId == aStreamId);
    return kExpectedFlushId;
}

void SuiteCodecControllerStream::NotifySeekComplete(TUint aHandle, TUint aFlushId)
{
    iHandle = aHandle;
    iFlushId = aFlushId;
    iSemSeek->Signal();
}

void SuiteCodecControllerStream::Add(const TChar* /*aMimeType*/)
{
}

void SuiteCodecControllerStream::WriteUint16Le(WriterBinary& aWriter, TUint16 aValue)
{
    aWriter.WriteUint16Be(SwapEndian16(aValue));
}

void SuiteCodecControllerStream::WriteUint32Le(WriterBinary& aWriter, TUint32 aValue)
{
    // WriterBinary only has ability to output big endian values.
    // This test suite has a rare case where little endian data is required for
    // a WAV header.
    // Instead of adding little endian methods to WriterBinary only for this
    // test, provide these helper methods to force little endian output.
    aWriter.WriteUint32Be(SwapEndian32(aValue));
}

Msg* SuiteCodecControllerStream::CreateAudio(TBool aValidHeader, TUint aDataBytes)
{
    ASSERT(iTotalBytes > 0);
    static const TUint32 kFmtChunkSize = 16;
    static const TUint16 kFmtAudioFormat = 1;
    static const TUint16 kBitsPerSample = 16;
    static const TUint kBytesPerSample = kBitsPerSample/8;

    TUint headerBytes = kWavHeaderBytes;
    if (iTotalBytes < headerBytes) {
        headerBytes = iTotalBytes;
    }
    const TUint audioBytes = iTotalBytes-headerBytes;
    TByte encodedAudioData[kMaxMsgBytes];

    Bws<kWavHeaderBytes> header;
    WriterBuffer writerBuf(header);
    WriterBinary writerBin(writerBuf);
    //TUint dataBytes = kMaxMsgBytes;
    TUint dataBytes = aDataBytes;
    if (iTrackOffset == 0) {
        // populate wav header
        // RIFF header
        if (aValidHeader) {
            writerBuf.Write(Brn("RIFF"));                                       // ChunkID
        }
        else {
            writerBuf.Write(Brn("NULL"));
        }

        WriteUint32Le(writerBin, 36+audioBytes);                                // ChunkSize
        writerBuf.Write(Brn("WAVE"));                                           // Format

        // fmt subchunk
        writerBuf.Write(Brn("fmt "));                                           // Subchunk1ID
        WriteUint32Le(writerBin, kFmtChunkSize);                                // Subchunk1Size
        WriteUint16Le(writerBin, kFmtAudioFormat);                              // AudioFormat
        WriteUint16Le(writerBin, kNumChannels);                                 // NumChannels
        WriteUint32Le(writerBin, kSampleRate);                                  // SampleRate
        WriteUint32Le(writerBin, kSampleRate*kNumChannels*kBytesPerSample);     // ByteRate
        WriteUint16Le(writerBin, kNumChannels*kBytesPerSample);                 // BlockAlign
        WriteUint16Le(writerBin, kBitsPerSample);                               // BitsPerSample

        // data subchunk
        writerBuf.Write(Brn("data"));                                           // Subchunk2ID
        WriteUint32Le(writerBin, audioBytes);                                   // Subchunk2Size

        // append to encoded bytes buffer
        (void)memcpy(encodedAudioData, header.Ptr(), headerBytes);

        // update data byte count
        dataBytes -= headerBytes;
    }

    // Only output iTotalBytes-kWavHeaderBytes of audio in total.
    TUint remaining = audioBytes - iTrackOffsetBytes;
    if (dataBytes > remaining) {
        dataBytes = remaining;
    }

    TUint dataByteOffset = 0;
    TUint dataBytesTotal = dataBytes;
    if (iTrackOffset == 0) {
        dataByteOffset += kWavHeaderBytes;
        dataBytesTotal += headerBytes;
    }

    (void)memset(encodedAudioData+dataByteOffset, 0x7f, dataBytes);
    Brn encodedAudioBuf(encodedAudioData, dataBytesTotal);
    MsgAudioEncoded* audio = iMsgFactory->CreateMsgAudioEncoded(encodedAudioBuf);

    TUint samples = dataBytes / (kNumChannels*kBytesPerSample);
    TUint jiffiesPerSample = Jiffies::kPerSecond / kSampleRate;
    iTrackOffset += samples * jiffiesPerSample;
    iTrackOffsetBytes += dataBytes;
    return audio;
}

void SuiteCodecControllerStream::TestStreamSuccessful()
{
    static const TUint kAudioBytes = 6144;
    iTotalBytes = kWavHeaderBytes + kAudioBytes;
    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    while (iTrackOffsetBytes < kAudioBytes) {
        Queue(CreateAudio(true, kMaxMsgBytes));
    }
    // Pushing a MsgEncodedAudio should cause a MsgDecodedStream to be pushed
    // out other end of CodecController.
    PullNext(EMsgDecodedStream);
    do {
        PullNext(EMsgAudioPcm);
    } while (iJiffies < iTrackOffset);

    ASSERT(iTrackOffsetBytes == kAudioBytes);
    TEST(iJiffies == iTrackOffset);
}

void SuiteCodecControllerStream::TestRecognitionFail()
{
    static const TUint kAudioBytes = 6144;
    iTotalBytes = kWavHeaderBytes + kAudioBytes;
    Queue(CreateTrack());
    PullNext(EMsgTrack);

    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    Queue(CreateAudio(false, kMaxMsgBytes));

    iSemStop->Wait();
    TEST(iStopCount == 1);
}

void SuiteCodecControllerStream::TestTruncatedStreamInRecognition()
{
    // This partially tests the ability of the WAV codec to return from its
    // Recognise() method, but what we're interested in is that the
    // CodecController then attempts to stop the unrecognised stream.
    //
    // WAV tries to read in 12 bytes for recognition, so give it fewer.
    iTotalBytes = 10;
    Queue(CreateTrack());
    PullNext(EMsgTrack);

    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    Queue(CreateAudio(true, kMaxMsgBytes));

    // Flush remaining audio from stream out by sending a new MsgEncodedStream.
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    iSemStop->Wait(kSemWaitMs);
    TEST(iStopCount == 1);

    TEST(iJiffies == iTrackOffset);
}

void SuiteCodecControllerStream::TestNoDataAfterRecognition()
{
    // WAV codec requires 12 bytes for successful recognition.
    iTotalBytes = 12;
    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    // Only send one msg (i.e., a truncated stream).
    // Won't get a MsgDecodedStream, as data is truncated.
    Queue(CreateAudio(true, kMaxMsgBytes));

    // Flush remaining audio from stream out by sending a new MsgTrack.
    Queue(CreateTrack());
    PullNext(EMsgTrack);

    TEST(iJiffies == iTrackOffset);
}

void SuiteCodecControllerStream::TestTruncatedStream()
{
    static const TUint kAudioBytes = 6144;
    iTotalBytes = kWavHeaderBytes + kAudioBytes;
    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    // Only send one msg (i.e., a truncated stream).
    Queue(CreateAudio(true, 400));
    PullNext(EMsgDecodedStream);

    // Flush remaining audio from stream out by sending a new MsgTrack.
    Queue(CreateTrack());
    PullNext(EMsgAudioPcm); // remaining audio from prev track
    PullNext(EMsgTrack);

    TEST(iJiffies == iTrackOffset);
}

void SuiteCodecControllerStream::TestTrackTrack()
{
    Queue(CreateTrack());
    PullNext(EMsgTrack);

    Queue(CreateTrack());
    PullNext(EMsgTrack);
}

void SuiteCodecControllerStream::TestTrackMetatext()
{
    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(iMsgFactory->CreateMsgMetaText(Brn("dummy")));
    PullNext(EMsgMetaText);
}

void SuiteCodecControllerStream::TestTrackEncodedStreamMetatext()
{
    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    // MsgMetaText should be buffered until audio is recognised.
    Queue(iMsgFactory->CreateMsgMetaText(Brn("dummy")));

    static const TUint kAudioBytes = 200;
    iTotalBytes = kWavHeaderBytes + kAudioBytes;
    Queue(CreateAudio(true, iTotalBytes));
    // Start-of-stream audio should be recognised, so MsgMetaText should be passed on.
    PullNext(EMsgMetaText);
    PullNext(EMsgDecodedStream);

    // Flush remaining audio from stream out by sending a new MsgEncodedStream.
    Queue(CreateEncodedStream());
    PullNext(EMsgAudioPcm);
    PullNext(EMsgEncodedStream);
}

void SuiteCodecControllerStream::TestSeek()
{
    static const TUint kMaxEncodedBytes = kMaxMsgBytes;
    static const TUint kSeconds = 3;
    static const TUint kChannels = 2;
    static const TUint kBitDepthBytes = 16/8;
    static const TUint kSamples = kSampleRate * kSeconds;
    static const TUint kAudioBytes = kSamples * kChannels * kBitDepthBytes;
    iTotalBytes = kWavHeaderBytes + kAudioBytes;

    Queue(CreateTrack());
    PullNext(EMsgTrack);

    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    while (iTrackOffsetBytes < kAudioBytes/2) { // get halfway through stream
        Queue(CreateAudio(true, kMaxEncodedBytes));
    }
    // Pushing a MsgEncodedAudio should cause a MsgDecodedStream to be pushed
    // out other end of CodecController.
    PullNext(EMsgDecodedStream);

    // Can only pull through queued-1 msgs, as CodecController will block when no more available.
    TUint maxPullBytes = iTrackOffsetBytes - kMaxEncodedBytes;
    TUint maxPullSamples = maxPullBytes/kChannels/kBitDepthBytes;
    TUint maxPullJiffies = maxPullSamples * Jiffies::PerSample(kSampleRate);
    while (iJiffies < maxPullJiffies) {
        TUint64 jiffiesBefore = iJiffies;
        PullNext(EMsgAudioPcm);
        TUint64 offsetAfter = iMsgOffset;
        TEST(offsetAfter == jiffiesBefore); // check next Msg starts where previous msg ended in stream
    }

    // Do a seek.
    Thread::Sleep(50);  // FIXME - quick fix to stop race condition where last
                        // encoded audio msg may not have been processed before
                        // seek (and is thus discarded).
    ISeeker& seeker = *iController;
    TUint handle = ISeeker::kHandleError;
    TUint seekSeconds = 1;
    seeker.StartSeek(iStreamId, seekSeconds, *this, handle); // seek to 1s

    // Send some more msgs down to cause CodecController to unblock and start the seek.
    // These will be discarded.
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));

    // Wait for seek to complete.
    iSemSeek->Wait(kSemWaitMs);
    TEST(iHandle == handle);
    TEST(iFlushId == kExpectedFlushId);

    // Adjust sending offsets and queue some more msgs.
    //iTrackOffsetBytes = kWavHeaderBytes + kSampleRate*kChannels*kBitDepthBytes * seekSeconds;
    iTrackOffsetBytes = kSampleRate*kChannels*kBitDepthBytes * seekSeconds;
    iTrackOffset = Jiffies::kPerSecond * seekSeconds;
    Queue(CreateFlush());
    while (iTrackOffsetBytes < kAudioBytes) {
        Queue(CreateAudio(true, kMaxEncodedBytes));
    }
    Queue(CreateEncodedStream()); // allows us to retrieve ALL MsgAudioPcm

    // Pull last EMsgAudioPcm that has been flushed out.
    TUint64 jiffiesBefore = iJiffies;
    PullNext(EMsgAudioPcm);
    TUint64 offsetAfter = iMsgOffset;
    TEST(offsetAfter == jiffiesBefore);

    // MsgFlush and MsgDecodedStream follow a successful seek.
    do {
        PullNext();
    } while (iLastReceivedMsg != EMsgFlush);
    PullNext(EMsgDecodedStream);

    // Adjust jiffy total to account for seek.
    TUint64 totalJiffies = iJiffies + (kSeconds-seekSeconds)*Jiffies::kPerSecond;

    // Get first MsgAudioPcm after seek.
    TUint64 jiffiesOffset = iJiffies;
    PullNext(EMsgAudioPcm);
    TUint64 offsetAfterSeek = iMsgOffset;
    TEST(offsetAfterSeek == Jiffies::kPerSecond*seekSeconds); // check new offset is seek position

    // Pull remainder of stream.
    while (iJiffies < totalJiffies) {
        TUint64 jiffiesBefore = iJiffies;
        PullNext(EMsgAudioPcm);
        TUint64 offsetAfter = iMsgOffset + jiffiesOffset - offsetAfterSeek;
        if (offsetAfter != jiffiesBefore) {
            Print("offsetAfter %llu, jiffiesBefore %llu\n", offsetAfter, jiffiesBefore);
        }
        TEST(offsetAfter == jiffiesBefore);
    }

    PullNext(EMsgEncodedStream);
    //PullNext(EMsgDecodedStream);    // WAV doesn't output this until more audio passes through

    TEST(iJiffies == totalJiffies);
}

void SuiteCodecControllerStream::TestSeekNewStream()
{
    static const TUint kMaxEncodedBytes = kMaxMsgBytes;
    static const TUint kSeconds = 3;
    static const TUint kChannels = 2;
    static const TUint kBitDepthBytes = 16/8;
    static const TUint kSamples = kSampleRate * kSeconds;
    static const TUint kAudioBytes = kSamples * kChannels * kBitDepthBytes;
    iTotalBytes = kWavHeaderBytes + kAudioBytes;

    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    const TUint bytesToOutput = kAudioBytes/2;
    const TUint msgsToOutput = (bytesToOutput/kMaxEncodedBytes) + 1;
    for (TUint i=0; i<msgsToOutput; i++) {
        Queue(CreateAudio(true, kMaxEncodedBytes));
    }
    // Pushing MsgEncodedAudio should cause a MsgDecodedStream to be pushed
    // out other end of CodecController.
    PullNext(EMsgDecodedStream);

    // Can only pull through queued-1 msgs, as CodecController will block when no more available.
    const TUint samplesPerMsg = kMaxEncodedBytes/kChannels/kBitDepthBytes;
    const TUint jiffiesPerMsg = samplesPerMsg * Jiffies::PerSample(kSampleRate);
    const TUint jiffiesToPull = (msgsToOutput-1)*jiffiesPerMsg;
    while (iJiffies < jiffiesToPull) {
        PullNext(EMsgAudioPcm);
    }

    // Do a seek.
    Thread::Sleep(50);  // FIXME - quick fix to stop race condition where last
    // encoded audio msg may not have been processed before
    // seek (and is thus discarded).
    ISeeker& seeker = *iController;
    TUint handle = ISeeker::kHandleError;
    TUint seekSeconds = 0;
    seeker.StartSeek(iStreamId, seekSeconds, *this, handle); // seek to 1s

    // Send some more msgs down to cause CodecController to unblock and start the seek.
    // These will be discarded.
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));

    // Pull audio that was output just before seek start.
    PullNext(EMsgAudioPcm);

    // Wait for seek to complete.
    iSemSeek->Wait(kSemWaitMs);
    TEST(iHandle == handle);
    TEST(iFlushId == kExpectedFlushId);

    // Flush to signify seek end.
    Queue(CreateFlush());
    do {
        PullNext();
    } while (iLastReceivedMsg != EMsgFlush);

    // Start new stream.
    iTrackOffsetBytes = 0;
    iTrackOffset = 0;
    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));
    Queue(CreateAudio(true, kMaxEncodedBytes));

    PullNext(EMsgDecodedStream);
    PullNext(EMsgAudioPcm);
    Queue(CreateEncodedStream());
    PullNext(EMsgAudioPcm);
    do {
        PullNext();
    } while (iLastReceivedMsg == EMsgAudioPcm);
    TEST(iLastReceivedMsg == EMsgEncodedStream);
}


// SuiteCodecControllerPcmSize

SuiteCodecControllerPcmSize::SuiteCodecControllerPcmSize()
    : SuiteCodecControllerBase("SuiteCodecControllerPcmSize")
{
    AddTest(MakeFunctor(*this, &SuiteCodecControllerPcmSize::TestPcmIsExpectedSize), "TestPcmIsExpectedSize");
}

void SuiteCodecControllerPcmSize::Setup()
{
    SuiteCodecControllerBase::Setup();
    iCodec = new TestCodecControllerDummyCodec(kAudioBytesPerMsg);
    iController->AddCodec(iCodec);  // Takes ownership.
    iController->Start();
}

void SuiteCodecControllerPcmSize::TearDown()
{
    SuiteCodecControllerBase::TearDown();
}

Msg* SuiteCodecControllerPcmSize::CreateAudio()
{
    static const TUint kBytesPerSample = kBitsPerSample/8;
    static const TUint dataBytes = kAudioBytesPerMsg;

    TByte encodedAudioData[kAudioBytesPerMsg];
    (void)memset(encodedAudioData, 0x7f, dataBytes);
    Brn encodedAudioBuf(encodedAudioData, dataBytes);
    MsgAudioEncoded* audio = iMsgFactory->CreateMsgAudioEncoded(encodedAudioBuf);

    TUint samples = dataBytes / (kNumChannels*kBytesPerSample);
    TUint jiffiesPerSample = Jiffies::kPerSecond / kSampleRate;
    iTrackOffset += samples * jiffiesPerSample;
    iTrackOffsetBytes += dataBytes;
    return audio;
}

void SuiteCodecControllerPcmSize::TestPcmIsExpectedSize()
{
    static const TUint kAudioBytes = 6144;
    static const TUint64 kJiffiesPerEncodedMsg = (Jiffies::kPerSecond / 44100) * kSamplesPerMsg;

    iTotalBytes = kWavHeaderBytes + kAudioBytes;

    iCodec->SetStreamInfo(kAudioBytesPerMsg, kNumChannels, kSampleRate, kBitsPerSample, AudioDataEndian::Big, kProfile);

    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    while (iTrackOffsetBytes < kAudioBytes) {
        Queue(CreateAudio());
    }
    Queue(CreateEncodedStream());

    // Pushing a MsgEncodedAudio should cause a MsgDecodedStream to be pushed
    // out other end of CodecController.
    PullNext(EMsgDecodedStream);
    while (iJiffies < iTrackOffset) {
        PullNext(EMsgAudioPcm, kJiffiesPerEncodedMsg);
    }

    PullNext(EMsgEncodedStream);
    PullNext(EMsgDecodedStream);    // dummy codec will always recognise a stream and output MsgDecodedStream

    ASSERT(iTrackOffsetBytes == kAudioBytes); // check correct number of bytes have been output by test code
    TEST(iJiffies == iTrackOffset);
}


// TestCodecControllerDummyCodec

const TChar* TestCodecControllerDummyCodec::kId("DUMC");

TestCodecControllerDummyCodec::TestCodecControllerDummyCodec(TUint aReadBufBytes)
    : CodecBase(kId, CodecBase::RecognitionComplexity::kCostLow)
    , iReadBuf(aReadBufBytes)
    , iReadBytes(0)
    , iChannels(0)
    , iSampleRate(0)
    , iBitDepth(0)
    , iEndianness(AudioDataEndian::Invalid)
    , iTrackOffset(0)
{
}

void TestCodecControllerDummyCodec::SetStreamInfo(TUint aReadBytes, TUint aChannels, TUint aSampleRate, TUint aBitDepth, AudioDataEndian aEndianness, const SpeakerProfile& aProfile)
{
    ASSERT(aReadBytes <= iReadBuf.MaxBytes());
    iReadBytes = aReadBytes;
    iChannels = aChannels;
    iSampleRate = aSampleRate;
    iBitDepth = aBitDepth;
    iEndianness = aEndianness;
    iProfile = aProfile;
    iTrackOffset = 0;
}

TBool TestCodecControllerDummyCodec::Recognise(const EncodedStreamInfo& /*aStreamInfo*/)
{
    ASSERT(iReadBytes != 0);    // Ensure SetStreamInfo() has been called.
    return true;
}

void TestCodecControllerDummyCodec::StreamInitialise()
{
    iTrackOffset = 0;
    iController->OutputDecodedStream(0, iBitDepth, iSampleRate, iChannels, Brn("PASS"), 0, 0, true, iProfile);
}

void TestCodecControllerDummyCodec::Process()
{
    iReadBuf.SetBytes(0);
    try {
        iController->Read(iReadBuf, iReadBytes);
        if (iReadBuf.Bytes() < iReadBytes) {
            THROW(CodecStreamEnded);
        }
    }
    catch (CodecStreamEnded&) {
        throw; // rethrow CodecStreamEnded
    }
    iTrackOffset += iController->OutputAudioPcm(iReadBuf, iChannels, iSampleRate, iBitDepth, iEndianness, iTrackOffset);
}

TBool TestCodecControllerDummyCodec::TrySeek(TUint aStreamId, TUint64 aSample)
{
    TUint64 byte = aSample*(iBitDepth/8)*iChannels;
    // NOTE: not doing any bounds checking here.
    // Tests expect CodecController to do it on behalf of this codec.
    TBool canSeek = iController->TrySeekTo(aStreamId, byte);
    if (canSeek) {
        iController->OutputDecodedStream(aStreamId, iBitDepth, iSampleRate, iChannels, Brn("PASS"), 0, aSample, true, iProfile);
        return true;
    }
    return false;
}

void TestCodecControllerDummyCodec::StreamCompleted()
{
}


// TestCodecControllerDummyCodecStreamInitialise

TestCodecControllerDummyCodecStreamInitialise::TestCodecControllerDummyCodecStreamInitialise(TUint aReadBufBytes, Semaphore& aSemStreamInitPending, Semaphore& aSemStreamInitContinue)
    : TestCodecControllerDummyCodec(aReadBufBytes)
    , iSemStreamInitPending(aSemStreamInitPending)
    , iSemStreamInitContinue(aSemStreamInitContinue)
{
}

void TestCodecControllerDummyCodecStreamInitialise::StreamInitialise()
{
    iSemStreamInitPending.Signal();
    iSemStreamInitContinue.Wait();
    TestCodecControllerDummyCodec::StreamInitialise();
}


// SuiteCodecControllerStopDuringStreamInit

SuiteCodecControllerStopDuringStreamInit::SuiteCodecControllerStopDuringStreamInit()
    : SuiteCodecControllerBase("SuiteCodecControllerStopDuringStreamInit")
{
    AddTest(MakeFunctor(*this, &SuiteCodecControllerStopDuringStreamInit::TestStopDuringStreamInit), "TestStopDuringStreamInit");
}

void SuiteCodecControllerStopDuringStreamInit::Setup()
{
    SuiteCodecControllerBase::Setup();
    iSemStreamInitPending = new Semaphore("SCCP", 0);
    iSemStreamInitContinue = new Semaphore("SCCC", 0);
    iCodec = new TestCodecControllerDummyCodecStreamInitialise(kAudioBytesPerMsg, *iSemStreamInitPending, *iSemStreamInitContinue);
    iController->AddCodec(iCodec);  // Takes ownership.
    iController->Start();
}

void SuiteCodecControllerStopDuringStreamInit::TearDown()
{
    iCodec = nullptr;
    delete iSemStreamInitContinue;
    delete iSemStreamInitPending;
    SuiteCodecControllerBase::TearDown();
}

void SuiteCodecControllerStopDuringStreamInit::TestStopDuringStreamInit()
{
    iCodec->SetStreamInfo(kAudioBytesPerMsg, 2, 44100, 16, AudioDataEndian::Little, SpeakerProfile());

    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    // Call TryStop() while inside StreamInitialise in codec.
    iSemStreamInitPending->Wait();
    iStreamHandler->TryStop(iStreamId);
    iSemStreamInitContinue->Signal();

    // Should now get MsgDecodedStream that was pushed just after TryStop() was called.
    PullNext(EMsgDecodedStream);

    // MsgMetaText should be passed through without issue.
    Queue(iMsgFactory->CreateMsgMetaText(Brn("dummy")));
    PullNext(EMsgMetaText);

    // Push flush for TryStop().
    Queue(CreateFlush());
    PullNext(EMsgFlush);

    // Start pulling new track.
    // Locking in DummyCodec ensures StreamInitialise() call above must return before SetStreamInfo() happens.
    iCodec->SetStreamInfo(kAudioBytesPerMsg, 2, 48000, 16, AudioDataEndian::Little, SpeakerProfile());
    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    // Allow StreamInitialise() to complete.
    iSemStreamInitPending->Wait();
    iSemStreamInitContinue->Signal();

    // Output some audio.
    TByte encodedAudioData[kAudioBytesPerMsg];
    (void)memset(encodedAudioData, 0x7f, kAudioBytesPerMsg);
    Brn encodedAudioBuf(encodedAudioData, kAudioBytesPerMsg);
    MsgAudioEncoded* audio = iMsgFactory->CreateMsgAudioEncoded(encodedAudioBuf);
    Queue(audio);

    PullNext(EMsgDecodedStream);
    PullNext(EMsgAudioPcm);
}


// SuiteCodecControllerSeekInvalid

SuiteCodecControllerSeekInvalid::SuiteCodecControllerSeekInvalid()
    : SuiteCodecControllerBase("SuiteCodecControllerSeekInvalid")
{
    AddTest(MakeFunctor(*this, &SuiteCodecControllerSeekInvalid::TestSeekInvalid), "TestSeekInvalid");
}

void SuiteCodecControllerSeekInvalid::Setup()
{
    SuiteCodecControllerBase::Setup();
    iSemSeek = new Semaphore("SCCS", 0);
    iHandle = ISeeker::kHandleError;
    iFlushId = MsgFlush::kIdInvalid;
    iCodec = new TestCodecControllerDummyCodec(kAudioBytesPerMsg);
    iController->AddCodec(iCodec);  // Takes ownership.
    iController->Start();
}

void SuiteCodecControllerSeekInvalid::TearDown()
{
    delete iSemSeek;
    SuiteCodecControllerBase::TearDown();
}

TUint SuiteCodecControllerSeekInvalid::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    // CodecController should do bounds checking, so don't expect call to reach here.
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

void SuiteCodecControllerSeekInvalid::NotifySeekComplete(TUint aHandle, TUint aFlushId)
{
    iHandle = aHandle;
    iFlushId = aFlushId;
    iSemSeek->Signal();
}

void SuiteCodecControllerSeekInvalid::TestSeekInvalid()
{
    iCodec->SetStreamInfo(kAudioBytesPerMsg, 2, 44100, 16, AudioDataEndian::Little, SpeakerProfile());

    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    // Output some audio.
    TByte encodedAudioData[kAudioBytesPerMsg];
    (void)memset(encodedAudioData, 0x7f, kAudioBytesPerMsg);
    Brn encodedAudioBuf(encodedAudioData, kAudioBytesPerMsg);
    MsgAudioEncoded* audio = iMsgFactory->CreateMsgAudioEncoded(encodedAudioBuf);
    Queue(audio);
    audio = iMsgFactory->CreateMsgAudioEncoded(encodedAudioBuf);
    Queue(audio);

    PullNext(EMsgDecodedStream);
    PullNext(EMsgAudioPcm);

    // Do a seek.
    ISeeker& seeker = *iController;
    TUint handle = ISeeker::kHandleError;
    TUint seekSeconds = 100;    // Out of range.
    seeker.StartSeek(iStreamId, seekSeconds, *this, handle);

    // Send another audio msg down to cause CodecController to unblock and start the seek.
    audio = iMsgFactory->CreateMsgAudioEncoded(encodedAudioBuf);
    Queue(audio);

    // Wait for seek to complete.
    iSemSeek->Wait(kSemWaitMs);
    TEST(iHandle == handle);
    TEST(iFlushId == MsgFlush::kIdInvalid);

    while (iReceivedMsgs.size() > 0) {
        // we don't know how many encoded audios were pulled before the seek failed, ending the stream
        PullNext(EMsgAudioPcm);
    }
    while (iPendingMsgs.size() > 0) {
        Thread::Sleep(10); // leave time for any pending msgs to be pulled by CodecController
    }
}


// TestCodecControllerDummyCodecBuffered

TestCodecControllerDummyCodecBuffered::TestCodecControllerDummyCodecBuffered(TUint aReadBufBytes)
    : TestCodecControllerDummyCodec(aReadBufBytes)
    , iOutBuf(aReadBufBytes*2)  // Enough space to buffer 2 msgs.
{
}

void TestCodecControllerDummyCodecBuffered::Process()
{
    iReadBuf.SetBytes(0);
    try {
        iController->Read(iReadBuf, iReadBytes);
        if (iReadBuf.Bytes() < iReadBytes) {
            THROW(CodecStreamEnded);
        }
        ASSERT(iOutBuf.BytesRemaining() >= iReadBuf.Bytes());
        iOutBuf.Append(iReadBuf);
        iReadBuf.SetBytes(0);

        // Always buffer half a msg.
        // - If more than 1 msg buffered (which should be exactly 1.5 msgs) output 1 message.
        // - If exactly 1 msg buffered (e.g., start of stream), only output 0.5 msgs.
        Brn out;
        if (iOutBuf.Bytes() > iReadBytes) {
            out.Set(iOutBuf.Ptr(), iReadBytes);
        }
        else if (iOutBuf.Bytes() == iReadBytes) {
            out.Set(iOutBuf.Ptr(), iReadBytes/2);
        }
        else {
            ASSERTS();
        }
        iTrackOffset += iController->OutputAudioPcm(out, iChannels, iSampleRate, iBitDepth, iEndianness, iTrackOffset);
        iOutBuf.Replace(iOutBuf.Ptr()+out.Bytes(), iOutBuf.Bytes()-out.Bytes());
    }
    catch (CodecStreamStart&) {
        // Flush output buffer.
        if (iOutBuf.Bytes() > 0) {
            iTrackOffset += iController->OutputAudioPcm(iOutBuf, iChannels, iSampleRate, iBitDepth, iEndianness, iTrackOffset);
            iOutBuf.SetBytes(0);
        }
        throw; // rethrow CodecStreamStart
    }
    catch (CodecStreamEnded&) {
        // Flush output buffer.
        if (iOutBuf.Bytes() > 0) {
            iTrackOffset += iController->OutputAudioPcm(iOutBuf, iChannels, iSampleRate, iBitDepth, iEndianness, iTrackOffset);
            iOutBuf.SetBytes(0);
        }
        throw; // rethrow CodecStreamEnded
    }
}


// SuiteCodecControllerUnexpectedFlush

SuiteCodecControllerUnexpectedFlush::SuiteCodecControllerUnexpectedFlush()
    : SuiteCodecControllerBase("SuiteCodecControllerUnexpectedFlush")
{
    AddTest(MakeFunctor(*this, &SuiteCodecControllerUnexpectedFlush::TestUnexpectedFlush), "TestUnexpectedFlush");
}

void SuiteCodecControllerUnexpectedFlush::Setup()
{
    SuiteCodecControllerBase::Setup();
    iCodec = new TestCodecControllerDummyCodecBuffered(kAudioBytesPerMsg);
    iController->AddCodec(iCodec);  // Takes ownership.
    iController->Start();
}

void SuiteCodecControllerUnexpectedFlush::TearDown()
{
    SuiteCodecControllerBase::TearDown();
}

void SuiteCodecControllerUnexpectedFlush::TestUnexpectedFlush()
{
    iCodec->SetStreamInfo(kAudioBytesPerMsg, 2, 44100, 16, AudioDataEndian::Little, SpeakerProfile());

    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    // Output some audio.
    TByte encodedAudioData[kAudioBytesPerMsg];
    (void)memset(encodedAudioData, 0x7f, kAudioBytesPerMsg);
    Brn encodedAudioBuf(encodedAudioData, kAudioBytesPerMsg);
    Queue(iMsgFactory->CreateMsgAudioEncoded(encodedAudioBuf));
    PullNext(EMsgDecodedStream);
    PullNext(EMsgAudioPcm);

    // Push unexpected flush. Buffered audio should be pushed before the flush.
    Queue(CreateFlush());
    PullNext(EMsgAudioPcm);
    PullNext(EMsgFlush);

    // Push a MsgEncodedStream to start new stream, as flush will have terminated previous stream.
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    // Push some audio.
    Queue(iMsgFactory->CreateMsgAudioEncoded(encodedAudioBuf));
    PullNext(EMsgDecodedStream);
    PullNext(EMsgAudioPcm);

    // Push a MsgEncodedStream to cause codec to flush its buffer.
    Queue(CreateEncodedStream());
    PullNext(EMsgAudioPcm);
    PullNext(EMsgEncodedStream);
    PullNext(EMsgDecodedStream);
}



void TestCodecController()
{
    Runner runner("CodecController tests\n");
    runner.Add(new SuiteCodecControllerStream());
    runner.Add(new SuiteCodecControllerPcmSize());
    runner.Add(new SuiteCodecControllerStopDuringStreamInit());
    runner.Add(new SuiteCodecControllerSeekInvalid());
    runner.Add(new SuiteCodecControllerUnexpectedFlush());
    runner.Run();
}

#endif // HEADER_TESTCODECCONTROLLER
