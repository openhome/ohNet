#ifndef HEADER_TESTCODECCONTROLLER
#define HEADER_TESTCODECCONTROLLER

#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/InfoProvider.h>
#include "AllocatorInfoLogger.h"
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Media/ProcessorPcmUtils.h>

#include <list>
#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;


class SuiteCodecController : public SuiteUnitTest
                             , private IPipelineElementUpstream
                             , private IPipelineElementDownstream
                             , private IStreamHandler
                             , private IMsgProcessor
{
public:
    SuiteCodecController();
public: // from SuiteUnitTest
    void Setup();
    void TearDown();
private: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IPipelineElementDownstream
    void Push(Msg* aMsg);
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
    TBool TryGet(IWriter& aWriter, TUint aTrackId, TUint aStreamId, TUint64 aOffset, TUint aBytes);
    void NotifyStarving(const Brx& aMode, TUint aTrackId, TUint aStreamId);
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgDelay* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgWait* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    enum EMsgType
    {
        ENone
       ,EMsgMode
       ,EMsgTrack
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgDecodedStream
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgQuit
    };
private:
    void Queue(Msg* aMsg);
    void PullNext(EMsgType aExpectedMsg);
    Msg* CreateTrack();
    Msg* CreateEncodedStream();
    Msg* CreateAudio(TBool aValidHeader);

    void TestStreamSuccessful();
    void TestRecognitionFail();
    void TestTruncatedStreamInRecognition();
    void TestNoDataAfterRecognition();
    void TestTruncatedStream();
    void TestTrackTrack();
    void TestTrackEncodedStreamTrack();
private:
    static const TUint kWavHeaderBytes = 44;
    static const TUint kSampleRate = 44100;
    static const TUint kNumChannels = 2;
    static const TUint kExpectedFlushId = 5;
    static const TUint kSemWaitMs = 5000;   // only required in case tests fail

    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    MsgFactory* iMsgFactory;
    CodecController* iController;

    std::list<Msg*> iPendingMsgs;
    std::list<Msg*> iReceivedMsgs;
    Semaphore* iSemPending;
    Semaphore* iSemReceived;
    Semaphore* iSemStop;
    Mutex* iLockPending;
    Mutex* iLockReceived;
    EMsgType iLastReceivedMsg;

    TUint iTrackId;
    TUint iStreamId;
    TUint iNextTrackId;
    TUint iNextStreamId;
    TUint iTotalBytes;
    TUint iTrackOffset;
    TUint iTrackOffsetBytes;
    TUint iJiffies;
    TBool iSeekable;
    TUint iStopCount;
};


SuiteCodecController::SuiteCodecController()
    : SuiteUnitTest("SuiteCodecController")
{
    AddTest(MakeFunctor(*this, &SuiteCodecController::TestStreamSuccessful), "TestStreamSuccessful");
    AddTest(MakeFunctor(*this, &SuiteCodecController::TestRecognitionFail), "TestRecognitionFail");
    AddTest(MakeFunctor(*this, &SuiteCodecController::TestTrackTrack), "TestTrackTrack");
    AddTest(MakeFunctor(*this, &SuiteCodecController::TestTrackEncodedStreamTrack), "TestTrackEncodedStreamTrack");
    AddTest(MakeFunctor(*this, &SuiteCodecController::TestTruncatedStreamInRecognition), "TestTruncatedStreamInRecognition");
    AddTest(MakeFunctor(*this, &SuiteCodecController::TestNoDataAfterRecognition), "TestNoDataAfterRecognition");
    AddTest(MakeFunctor(*this, &SuiteCodecController::TestTruncatedStream), "TestTruncatedStream");
}

void SuiteCodecController::Setup()
{
    iTrackFactory = new TrackFactory(iInfoAggregator, 5);
    iMsgFactory = new MsgFactory(iInfoAggregator, 20, 20, 5, 5, 10, 1, 0, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1);
    iController = new CodecController(*iMsgFactory, *this, *this);
    iSemPending = new Semaphore("TCSP", 0);
    iSemReceived = new Semaphore("TCSR", 0);
    iSemStop = new Semaphore("TCSS", 0);
    iLockPending = new Mutex("TCMP");
    iLockReceived = new Mutex("TCMR");
    iTrackId = iStreamId = UINT_MAX;
    iNextTrackId = iNextStreamId = 1;
    iTotalBytes = iTrackOffset = iTrackOffsetBytes = 0;
    iJiffies = 0;
    iSeekable = true;
    iStopCount = 0;

    iController->AddCodec(CodecFactory::NewWav());
    iController->Start();
}

void SuiteCodecController::TearDown()
{
    Queue(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);

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

Msg* SuiteCodecController::Pull()
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

void SuiteCodecController::Push(Msg* aMsg)
{
    iLockReceived->Wait();
    iReceivedMsgs.push_back(aMsg);
    iLockReceived->Signal();
    iSemReceived->Signal();
}

EStreamPlay SuiteCodecController::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS();
    return ePlayNo;
}

TUint SuiteCodecController::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteCodecController::TryStop(TUint aTrackId, TUint aStreamId)
{
    iStopCount++;
    iSemStop->Signal();
    if (aTrackId == iTrackId && aStreamId == iStreamId) {
        return kExpectedFlushId;
    }
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TBool SuiteCodecController::TryGet(IWriter& /*aWriter*/, TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    ASSERTS();
    return false;
}

void SuiteCodecController::NotifyStarving(const Brx& /*aMode*/, TUint /*aTrackId*/, TUint /*aStreamId*/)
{
}

Msg* SuiteCodecController::ProcessMsg(MsgMode* aMsg)
{
    iLastReceivedMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteCodecController::ProcessMsg(MsgTrack* aMsg)
{
    iLastReceivedMsg = EMsgTrack;
    iTrackId = aMsg->IdPipeline();
    return aMsg;
}

Msg* SuiteCodecController::ProcessMsg(MsgDelay* aMsg)
{
    iLastReceivedMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteCodecController::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastReceivedMsg = EMsgEncodedStream;
    iStreamId = aMsg->StreamId();
    return aMsg;
}

Msg* SuiteCodecController::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuiteCodecController::ProcessMsg(MsgMetaText* aMsg)
{
    iLastReceivedMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteCodecController::ProcessMsg(MsgHalt* aMsg)
{
    iLastReceivedMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteCodecController::ProcessMsg(MsgFlush* aMsg)
{
    iLastReceivedMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteCodecController::ProcessMsg(MsgWait* aMsg)
{
    iLastReceivedMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteCodecController::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastReceivedMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteCodecController::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastReceivedMsg = EMsgAudioPcm;
    iJiffies += aMsg->Jiffies();
    MsgPlayable* playable = aMsg->CreatePlayable();
    ProcessorPcmBufPacked pcmProcessor;
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

Msg* SuiteCodecController::ProcessMsg(MsgSilence* aMsg)
{
    iLastReceivedMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteCodecController::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuiteCodecController::ProcessMsg(MsgQuit* aMsg)
{
    iLastReceivedMsg = EMsgQuit;
    return aMsg;
}

void SuiteCodecController::Queue(Msg* aMsg)
{
    iLockPending->Wait();
    iPendingMsgs.push_back(aMsg);
    iLockPending->Signal();
    iSemPending->Signal();
}

void SuiteCodecController::PullNext(EMsgType aExpectedMsg)
{
    iSemReceived->Wait(kSemWaitMs);
    iLockReceived->Wait();
    ASSERT(iReceivedMsgs.size() > 0);
    Msg* msg = iReceivedMsgs.front();
    iReceivedMsgs.pop_front();
    iLockReceived->Signal();

    msg = msg->Process(*this);
    msg->RemoveRef();
    TEST(iLastReceivedMsg == aExpectedMsg);
}

Msg* SuiteCodecController::CreateTrack()
{
    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    Msg* msg = iMsgFactory->CreateMsgTrack(*track, iNextTrackId++);
    track->RemoveRef();
    return msg;
}

Msg* SuiteCodecController::CreateEncodedStream()
{
    return iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 1<<21, ++iNextStreamId, iSeekable, false, this);
}

Msg* SuiteCodecController::CreateAudio(TBool aValidHeader)
{
    ASSERT(iTotalBytes > 0);
    static const TUint32 kFmtChunkSize = 16;
    static const TUint16 kFmtAudioFormat = 1;
    static const TUint16 kBitsPerSample = 16;
    static const TUint kBytesPerSample = kBitsPerSample/8;
    static const TUint kDataBytes = 960;

    TUint headerBytes = kWavHeaderBytes;
    if (iTotalBytes < headerBytes) {
        headerBytes = iTotalBytes;
    }
    const TUint audioBytes = iTotalBytes-headerBytes;
    TByte encodedAudioData[kDataBytes];

    Bws<kWavHeaderBytes> header;
    TUint dataBytes = kDataBytes;
    if (iTrackOffset == 0) {
        // populate wav header
        // RIFF header
        if (aValidHeader) {
            header.Append("RIFF");                                                      // ChunkID
        }
        else {
            header.Append("NULL");
        }
        header.Append(Arch::LittleEndian4(36+audioBytes));                              // ChunkSize
        header.Append("WAVE");                                                          // Format

        // fmt subchunk
        header.Append("fmt ");                                                          // Subchunk1ID
        header.Append(Arch::LittleEndian4(kFmtChunkSize));                              // Subchunk1Size
        header.Append(Arch::LittleEndian2(kFmtAudioFormat));                            // AudioFormat
        header.Append(Arch::LittleEndian2(kNumChannels));                               // NumChannels
        header.Append(Arch::LittleEndian4(kSampleRate));                                // SampleRate
        header.Append(Arch::LittleEndian4(kSampleRate*kNumChannels*kBytesPerSample));   // ByteRate
        header.Append(Arch::LittleEndian2(kNumChannels*kBytesPerSample));               // BlockAlign
        header.Append(Arch::LittleEndian2(kBitsPerSample));                             // BitsPerSample

        // data subchunk
        header.Append("data");                                                          // Subchunk2ID
        header.Append(Arch::LittleEndian4(audioBytes));                                 // Subchunk2Size

        // append to encoded bytes buffer
        (void)memcpy(encodedAudioData, header.Ptr(), headerBytes);

        // update data byte count
        dataBytes = kDataBytes - headerBytes;
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

void SuiteCodecController::TestStreamSuccessful()
{
    static const TUint kAudioBytes = 6144;
    iTotalBytes = kWavHeaderBytes + kAudioBytes;
    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    while (iTrackOffsetBytes < kAudioBytes) {
        Queue(CreateAudio(true));
    }
    // Pushing a MsgEncodedAudio should cause a MsgDecodedStream to be pushed
    // out other end of CodecController.
    PullNext(EMsgDecodedStream);
    PullNext(EMsgAudioPcm);

    ASSERT(iTrackOffsetBytes == kAudioBytes);
    TEST(iJiffies == iTrackOffset);
}

void SuiteCodecController::TestRecognitionFail()
{
    static const TUint kAudioBytes = 6144;
    iTotalBytes = kWavHeaderBytes + kAudioBytes;
    Queue(CreateTrack());
    PullNext(EMsgTrack);

    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    Queue(CreateAudio(false));

    iSemStop->Wait();
    TEST(iStopCount == 1);
}

void SuiteCodecController::TestTruncatedStreamInRecognition()
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

    Queue(CreateAudio(true));

    // Flush remaining audio from stream out by sending a new MsgTrack.
    Queue(CreateTrack());
    PullNext(EMsgTrack);

    iSemStop->Wait(kSemWaitMs);
    TEST(iStopCount == 1);

    TEST(iJiffies == iTrackOffset);
}

void SuiteCodecController::TestNoDataAfterRecognition()
{
    // WAV codec requires 12 bytes for successful recognition.
    iTotalBytes = 12;
    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    // Only send one msg (i.e., a truncated stream).
    // Won't get a MsgDecodedStream, as data is truncated.
    Queue(CreateAudio(true));

    // Flush remaining audio from stream out by sending a new MsgTrack.
    Queue(CreateTrack());
    PullNext(EMsgTrack);

    TEST(iJiffies == iTrackOffset);
}

void SuiteCodecController::TestTruncatedStream()
{
    static const TUint kAudioBytes = 6144;
    iTotalBytes = kWavHeaderBytes + kAudioBytes;
    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    // Only send one msg (i.e., a truncated stream).
    Queue(CreateAudio(true));
    PullNext(EMsgDecodedStream);

    // Flush remaining audio from stream out by sending a new MsgTrack.
    Queue(CreateTrack());
    PullNext(EMsgAudioPcm); // remaining audio from prev track
    PullNext(EMsgTrack);

    TEST(iJiffies == iTrackOffset);
}

void SuiteCodecController::TestTrackTrack()
{
    Queue(CreateTrack());
    PullNext(EMsgTrack);

    Queue(CreateTrack());
    PullNext(EMsgTrack);
}

void SuiteCodecController::TestTrackEncodedStreamTrack()
{
    Queue(CreateTrack());
    PullNext(EMsgTrack);

    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    Queue(CreateTrack());
    PullNext(EMsgTrack);

    iSemStop->Wait();
    TEST(iStopCount == 1);
}

void TestCodecController()
{
    Runner runner("CodecController tests\n");
    runner.Add(new SuiteCodecController());
    runner.Run();
}

#endif // HEADER_TESTCODECCONTROLLER
