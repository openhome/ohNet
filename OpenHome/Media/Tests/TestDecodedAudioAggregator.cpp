#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/DecodedAudioAggregator.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>

#include <list>
#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteDecodedAudioAggregator : public SuiteUnitTest
                                  , public IPipelineElementDownstream
                                  , public IStreamHandler
                                  , public IMsgProcessor
{
public:
    SuiteDecodedAudioAggregator();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryDiscard(TUint aJiffies) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
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
private:
    void Queue(Msg* aMsg);
    void PullNext(EMsgType aExpectedMsg);
    void PullNext(EMsgType aExpectedMsg, TUint64 aExpectedJiffies);
    Msg* CreateTrack();
    Msg* CreateEncodedStream();
    MsgDecodedStream* CreateDecodedStream();
    MsgFlush* CreateFlush();
    MsgAudioPcm* CreateAudio(TUint aBytes, TUint aSampleRate=kSampleRate, TUint aBitDepth=kBitDepth, TUint aNumChannels=kChannels);
private:
    void TestStreamSuccessful();
    void TestNoDataAfterDecodedStream();
    void TestShortStream();
    void TestTrackTrack();
    void TestTrackEncodedStreamTrack();
    void TestPcmIsExpectedSize();
    void TestRawPcmNotAggregated();
private:
    static const TUint kWavHeaderBytes = 44;
    static const TUint kSampleRate = 44100;
    static const TUint kChannels = 2;
    static const SpeakerProfile kProfile;
    static const TUint kBitDepth = 16;
    static const TUint kExpectedFlushId = 5;
    static const TUint kSemWaitMs = 5000;   // only required in case tests fail
    MsgFactory* iMsgFactory;
    DecodedAudioAggregator* iDecodedAudioAggregator;
    Semaphore* iSemStop;
    TUint64 iTrackOffset;
    TUint iTrackOffsetBytes;
    TUint64 iJiffies;
    TUint64 iMsgOffset;
    TUint iStopCount;
    TUint iStreamId;

    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    std::list<Msg*> iReceivedMsgs;
    Semaphore* iSemReceived;
    Mutex* iLockReceived;
    EMsgType iLastReceivedMsg;
    TUint iNextStreamId;
    TBool iSeekable;
};

} // namespace Media
} // namespace OpenHome



// SuiteDecodedAudioAggregator

const SpeakerProfile SuiteDecodedAudioAggregator::kProfile(2);

SuiteDecodedAudioAggregator::SuiteDecodedAudioAggregator()
    : SuiteUnitTest("SuiteDecodedAudioAggregator")
{
    AddTest(MakeFunctor(*this, &SuiteDecodedAudioAggregator::TestStreamSuccessful), "TestStreamSuccessful");
    AddTest(MakeFunctor(*this, &SuiteDecodedAudioAggregator::TestNoDataAfterDecodedStream), "TestNoDataAfterDecodedStream");
    AddTest(MakeFunctor(*this, &SuiteDecodedAudioAggregator::TestShortStream), "TestShortStream");
    AddTest(MakeFunctor(*this, &SuiteDecodedAudioAggregator::TestTrackTrack), "TestTrackTrack");
    AddTest(MakeFunctor(*this, &SuiteDecodedAudioAggregator::TestTrackEncodedStreamTrack), "TestTrackEncodedStreamTrack");
    AddTest(MakeFunctor(*this, &SuiteDecodedAudioAggregator::TestPcmIsExpectedSize), "TestPcmIsExpectedSize");
    AddTest(MakeFunctor(*this, &SuiteDecodedAudioAggregator::TestRawPcmNotAggregated), "TestRawPcmNotAggregated");
}

void SuiteDecodedAudioAggregator::Setup()
{
    iTrackFactory = new TrackFactory(iInfoAggregator, 5);
    // Need so many (Msg)AudioEncoded because kMaxMsgBytes is currently 960, and msgs are queued in advance of being pulled for these tests.
    MsgFactoryInitParams init;
    init.SetMsgAudioEncodedCount(400, 400);
    init.SetMsgAudioPcmCount(100, 100);
    init.SetMsgSilenceCount(10);
    init.SetMsgPlayableCount(50, 0);
    init.SetMsgDecodedStreamCount(2);
    init.SetMsgTrackCount(2);
    init.SetMsgEncodedStreamCount(2);
    init.SetMsgMetaTextCount(2);
    init.SetMsgHaltCount(2);
    init.SetMsgFlushCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iDecodedAudioAggregator = new DecodedAudioAggregator(*this);
    iSemReceived = new Semaphore("TCSR", 0);
    iSemStop = new Semaphore("TCSS", 0);
    iLockReceived = new Mutex("TCMR");
    iStreamId = UINT_MAX;
    iNextStreamId = 0;
    iTrackOffsetBytes = 0;
    iTrackOffset = 0;
    iJiffies = 0;
    iMsgOffset = 0;
    iSeekable = true;
    iStopCount = 0;
}

void SuiteDecodedAudioAggregator::TearDown()
{
    Queue(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);

    iLockReceived->Wait();
    ASSERT(iReceivedMsgs.size() == 0);
    iLockReceived->Signal();

    delete iLockReceived;
    delete iSemStop;
    delete iSemReceived;
    delete iDecodedAudioAggregator;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteDecodedAudioAggregator::Push(Msg* aMsg)
{
    iLockReceived->Wait();
    iReceivedMsgs.push_back(aMsg);
    iLockReceived->Signal();
    iSemReceived->Signal();
}

EStreamPlay SuiteDecodedAudioAggregator::OkToPlay(TUint /*aStreamId*/)
{
    ASSERTS();
    return ePlayNo;
}

TUint SuiteDecodedAudioAggregator::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteDecodedAudioAggregator::TryDiscard(TUint /*aJiffies*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteDecodedAudioAggregator::TryStop(TUint aStreamId)
{
    iStopCount++;
    iSemStop->Signal();
    if (aStreamId == iStreamId) {
        return kExpectedFlushId;
    }
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

void SuiteDecodedAudioAggregator::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/, TBool /*aStarving*/)
{
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgMode* aMsg)
{
    iLastReceivedMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgTrack* aMsg)
{
    iLastReceivedMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgDrain* aMsg)
{
    iLastReceivedMsg = EMsgDrain;
    return aMsg;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgDelay* aMsg)
{
    iLastReceivedMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastReceivedMsg = EMsgEncodedStream;
    iStreamId = aMsg->StreamId();
    return aMsg;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgMetaText* aMsg)
{
    iLastReceivedMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastReceivedMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgHalt* aMsg)
{
    iLastReceivedMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgFlush* aMsg)
{
    iLastReceivedMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgWait* aMsg)
{
    iLastReceivedMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastReceivedMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgBitRate* aMsg)
{
    iLastReceivedMsg = EMsgBitRate;
    return aMsg;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgAudioPcm* aMsg)
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

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgSilence* aMsg)
{
    iLastReceivedMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteDecodedAudioAggregator::ProcessMsg(MsgQuit* aMsg)
{
    iLastReceivedMsg = EMsgQuit;
    return aMsg;
}

void SuiteDecodedAudioAggregator::Queue(Msg* aMsg)
{
    iDecodedAudioAggregator->Push(aMsg);
}

void SuiteDecodedAudioAggregator::PullNext(EMsgType aExpectedMsg)
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

void SuiteDecodedAudioAggregator::PullNext(EMsgType aExpectedMsg, TUint64 aExpectedJiffies)
{
    TUint64 jiffiesStart = iJiffies;
    PullNext(aExpectedMsg);
    TUint64 jiffiesDiff = iJiffies - jiffiesStart;
    //Log::Print("jiffiesDiff: %llu, aExpectedJiffies: %llu\n", jiffiesDiff, aExpectedJiffies);
    TEST(jiffiesDiff == aExpectedJiffies);
}

Msg* SuiteDecodedAudioAggregator::CreateTrack()
{
    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    Msg* msg = iMsgFactory->CreateMsgTrack(*track);
    track->RemoveRef();
    return msg;
}

Msg* SuiteDecodedAudioAggregator::CreateEncodedStream()
{
    return iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 1<<21, 0, ++iNextStreamId, iSeekable, false, Multiroom::Allowed, this);
}

MsgDecodedStream* SuiteDecodedAudioAggregator::CreateDecodedStream()
{
    static const TUint kBitrate = 256;
    return iMsgFactory->CreateMsgDecodedStream(++iNextStreamId, kBitrate, kBitDepth, kSampleRate, kChannels, Brn("Dummy"), 0, 0, true, true, false, false, Multiroom::Allowed, kProfile, this);
}

MsgFlush* SuiteDecodedAudioAggregator::CreateFlush()
{
    return iMsgFactory->CreateMsgFlush(kExpectedFlushId);
}

MsgAudioPcm* SuiteDecodedAudioAggregator::CreateAudio(TUint aBytes, TUint aSampleRate, TUint aBitDepth, TUint aNumChannels)
{
    TByte* decodedAudioData = new TByte[aBytes];
    (void)memset(decodedAudioData, 0x7f, aBytes);
    Brn decodedAudioBuf(decodedAudioData, aBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(decodedAudioBuf, aNumChannels, aSampleRate, aBitDepth, AudioDataEndian::Little, iTrackOffset);
    delete[] decodedAudioData;

    TUint samples = aBytes / (aNumChannels * (aBitDepth/8));
    TUint jiffiesPerSample = Jiffies::kPerSecond / aSampleRate;
    iTrackOffset += samples * jiffiesPerSample;
    iTrackOffsetBytes += aBytes;
    return audio;
}

void SuiteDecodedAudioAggregator::TestStreamSuccessful()
{
    static const TUint kMaxMsgBytes = DecodedAudio::kMaxBytes;
    static const TUint kAudioBytes = DecodedAudio::kMaxBytes*5;
    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    Queue(CreateDecodedStream());
    PullNext(EMsgDecodedStream);

    while (iTrackOffsetBytes < kAudioBytes) {
        Queue(CreateAudio(kMaxMsgBytes));
    }
    PullNext(EMsgAudioPcm);
    PullNext(EMsgAudioPcm);
    PullNext(EMsgAudioPcm);
    PullNext(EMsgAudioPcm);
    PullNext(EMsgAudioPcm);

    ASSERT(iTrackOffsetBytes == kAudioBytes);
    TEST(iJiffies == iTrackOffset);
}

void SuiteDecodedAudioAggregator::TestNoDataAfterDecodedStream()
{
    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    Queue(CreateDecodedStream());
    PullNext(EMsgDecodedStream);

    // Send a new MsgTrack.
    Queue(CreateTrack());
    PullNext(EMsgTrack);

    TEST(iJiffies == iTrackOffset);
}

void SuiteDecodedAudioAggregator::TestShortStream()
{
    static const TUint kMaxMsgBytes = DecodedAudio::kMaxBytes;
    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    Queue(CreateDecodedStream());
    PullNext(EMsgDecodedStream);

    Queue(CreateAudio(kMaxMsgBytes));
    PullNext(EMsgAudioPcm);

    ASSERT(iTrackOffsetBytes == kMaxMsgBytes);
    TEST(iJiffies == iTrackOffset);
}

void SuiteDecodedAudioAggregator::TestTrackTrack()
{
    Queue(CreateTrack());
    PullNext(EMsgTrack);

    Queue(CreateTrack());
    PullNext(EMsgTrack);
}

void SuiteDecodedAudioAggregator::TestTrackEncodedStreamTrack()
{
    Queue(CreateTrack());
    PullNext(EMsgTrack);

    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);

    Queue(CreateTrack());
    PullNext(EMsgTrack);
}

void SuiteDecodedAudioAggregator::TestPcmIsExpectedSize()
{
    static const TUint kMaxMsgBytes = 64;
    static const TUint kAudioBytes = DecodedAudio::kMaxBytes;
    static const TUint kSamplesPerMsg = 16;
    static const TUint64 kJiffiesPerMsg = (Jiffies::kPerSecond / kSampleRate) * kSamplesPerMsg;
    static const TUint kMaxDecodedBufferedMs = 5;   // dependant on value in CodecController
    static const TUint kMaxDecodedBufferedJiffies = Jiffies::kPerMs * kMaxDecodedBufferedMs;

    // kMaxDecodedBufferedJiffies probably isn't on a msg boundary, so:
    // - work out how much over last boundary it goes
    static const TUint kRemainderJiffies = kMaxDecodedBufferedJiffies % kJiffiesPerMsg;
    // - and then adjust expected jiffies to last boundary + 1 msg (as ms limit can be violated as long as byte limit is not violated)
    static const TUint kExpectedJiffiesPerMsg = kMaxDecodedBufferedJiffies-kRemainderJiffies + kJiffiesPerMsg;

    ASSERT(kMaxDecodedBufferedJiffies%kJiffiesPerMsg != 0);

    Queue(CreateTrack());
    PullNext(EMsgTrack);
    Queue(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    Queue(CreateDecodedStream());
    PullNext(EMsgDecodedStream);

    while (iTrackOffsetBytes < kAudioBytes) {
        Queue(CreateAudio(kMaxMsgBytes));
    }
    Queue(CreateEncodedStream());   // flush out remaining audio

    while (iJiffies < (iTrackOffset-kMaxDecodedBufferedJiffies)) {
        PullNext(EMsgAudioPcm, kExpectedJiffiesPerMsg);
    }
    if (iJiffies < iTrackOffset) {
        // Still a final (shorter) MsgAudioPcm to pull.
        const TUint64 finalMsgJiffies = iTrackOffset-iJiffies;
        PullNext(EMsgAudioPcm, finalMsgJiffies);
    }

    PullNext(EMsgEncodedStream);

    ASSERT(iTrackOffsetBytes == kAudioBytes); // check correct number of bytes have been output by test code
    TEST(iJiffies == iTrackOffset);
}

void SuiteDecodedAudioAggregator::TestRawPcmNotAggregated()
{
    Queue(iMsgFactory->CreateMsgMode(Brn("dummyMode"), true, ModeClockPullers(), false, false));
    Queue(CreateTrack());
    PcmStreamInfo pcmStream;
    pcmStream.Set(32, 48000, 2, AudioDataEndian::Big, SpeakerProfile(), 0LL);
    Queue(iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 1<<21, 0, ++iNextStreamId, iSeekable, false, Multiroom::Allowed, this, pcmStream));
    Queue(CreateDecodedStream());
    Queue(CreateAudio(8, 48000, 32, 2)); // one sample for 32-bit stereo
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgEncodedStream);
    PullNext(EMsgDecodedStream);
    PullNext(EMsgAudioPcm);
    TEST(iJiffies == Jiffies::PerSample(48000));
    TEST(iJiffies == iTrackOffset);
}


void TestDecodedAudioAggregator()
{
    Runner runner("DecodedAudioAggregator tests\n");
    runner.Add(new SuiteDecodedAudioAggregator());
    runner.Run();
}
