#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Pipeline/AudioReservoir.h>
#include <OpenHome/Media/Pipeline/DecodedAudioReservoir.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Media/ClockPuller.h>

#include <string.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteAudioReservoir : public Suite, private IMsgProcessor
{
    static const TUint kDecodedAudioCount = 512;
    static const TUint kMsgAudioPcmCount  = 512;
    static const TUint kMsgSilenceCount   = 1;

    static const TUint kReservoirSize = Jiffies::kPerMs * 500;
    static const TUint kMaxStreams = 5;

    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
public:
    SuiteAudioReservoir();
    ~SuiteAudioReservoir();
    void Test();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    enum EMsgType
    {
        ENone
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgDecodedStream
       ,EMsgMode
       ,EMsgSession
       ,EMsgTrack
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgQuit
    };
enum EMsgGenerationState
{
    EGenerateSingle
   ,EFillReservoir
   ,EExit
};
private:
    void GenerateMsg(EMsgType aType);
    void GenerateMsgs(EMsgType aType);
    void Generate(EMsgGenerationState aState, EMsgType aType);
    void MsgEnqueueThread();
    TBool EnqueueMsg(EMsgType aType);
    MsgAudio* CreateAudio();
    TBool ReservoirIsFull() const { return static_cast<AudioReservoir*>(iReservoir)->IsFull(); }
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    DecodedAudioReservoir* iReservoir;
    ThreadFunctor* iThread;
    EMsgGenerationState iMsgGenerationState;
    EMsgType iNextGeneratedMsg;
    EMsgType iLastMsg;
    Semaphore iSemUpstream;
    Semaphore iSemUpstreamComplete;
    TUint64 iTrackOffset;
};

class SuiteReservoirHistory : public Suite, private IMsgProcessor, private IClockPuller
{
    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
    static const TUint kBitDepth = 16;
    static const TUint kReservoirSize = Jiffies::kPerMs * 1000;
    static const TUint kMaxStreams = 5;
    static const TUint kMaxHistorySamples = 10;
    static const TUint kTotalHistoryUpdates = kMaxHistorySamples * 2;
public:
    SuiteReservoirHistory();
    ~SuiteReservoirHistory();
private: // from Suite
    void Test();
private:
    void PullerThread();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private: // from IClockPuller
    void StartDecodedReservoir(TUint aCapacityJiffies, TUint aNotificationFrequency);
    void NewStreamDecodedReservoir(TUint aTrackId, TUint aStreamId);
    void NotifySizeDecodedReservoir(TUint aJiffies);
    void StopDecodedReservoir();
    void StartStarvationMonitor(TUint aCapacityJiffies, TUint aNotificationFrequency);
    void NewStreamStarvationMonitor(TUint aTrackId, TUint aStreamId);
    void NotifySizeStarvationMonitor(TUint aJiffies);
    void StopStarvationMonitor();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    DecodedAudioReservoir* iReservoir;
    ThreadFunctor* iThread;
    TUint64 iDequeuedJiffies;
    TUint iHistoryPointCount;
    TBool iStopAudioGeneration;
    TByte iBuf[DecodedAudio::kMaxBytes];
    TUint iTrackId;
    TUint iStreamId;
    TBool iStartCalled;
    TBool iNewStreamCalled;
    TBool iNotifySizeCalled;
};

} // namespace Media
} // namespace OpenHome


// SuiteAudioReservoir

SuiteAudioReservoir::SuiteAudioReservoir()
    : Suite("Decoded Audio Reservoir tests")
    , iLastMsg(ENone)
    , iSemUpstream("TRSV", 0)
    , iSemUpstreamComplete("TRSV", 0)
    , iTrackOffset(0)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, kDecodedAudioCount, kMsgAudioPcmCount, kMsgSilenceCount, 1, 1, kMaxStreams+2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iReservoir = new DecodedAudioReservoir(kReservoirSize, kMaxStreams, kMaxStreams);
    iThread = new ThreadFunctor("TEST", MakeFunctor(*this, &SuiteAudioReservoir::MsgEnqueueThread));
    iThread->Start();
    iSemUpstreamComplete.Wait();
}

SuiteAudioReservoir::~SuiteAudioReservoir()
{
    iMsgGenerationState = EExit;
    iSemUpstream.Signal();
    delete iThread;
    delete iReservoir;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteAudioReservoir::Test()
{
    /*
    Test goes something like
        Add single 0xff filled audio.  Check it can be Pull()ed.
        Check that Silence, Track, MetaText, Quit & Halt msgs are passed through.
        Add audio until we exceed MaxSize.  Check adding thread is blocked.
        Pull single audio msg.  Add Flush; check that next msg Pull()ed is the Flush and that reservoir is now empty.
    */

    // Add single 0xff filled audio.  Check it can be Pull()ed.
    TEST(iLastMsg == ENone);
    GenerateMsg(EMsgAudioPcm);
    iSemUpstreamComplete.Wait();
    Msg* msg = iReservoir->Pull();
    msg = msg->Process(*this);
    TEST(iLastMsg == EMsgAudioPcm);
    ASSERT(msg == NULL);

    // Check that uninteresting msgs are passed through.
    EMsgType types[] = { EMsgSilence, EMsgDecodedStream, EMsgMode, EMsgSession, EMsgTrack, EMsgDelay, EMsgEncodedStream, EMsgMetaText, EMsgFlush, EMsgWait, EMsgHalt, EMsgQuit };
    for (TUint i=0; i<sizeof(types)/sizeof(types[0]); i++) {
        EMsgType msgType = types[i];
        GenerateMsg(msgType);
        iSemUpstreamComplete.Wait();
        msg = iReservoir->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
        TEST(iLastMsg == msgType);
    }

    // Add audio until we exceed MaxSize.  Check adding thread is blocked.
    GenerateMsgs(EMsgAudioPcm);
    while (iReservoir->Jiffies() < kReservoirSize) {
        Thread::Sleep(10);
    }
    TUint jiffies = iReservoir->Jiffies();
    // lazy check that Enqueue has blocked
    // ...sleep for a while then check size of reservoir is unchanged
    Thread::Sleep(25);
    TEST(iReservoir->Jiffies() == jiffies);

    // Pull single msg to unblock iThread
    msg = iReservoir->Pull();
    msg = msg->Process(*this);
    ASSERT(msg == NULL);
    jiffies = iReservoir->Jiffies();

    // Keep adding DecodedStream until Enqueue blocks
    for (TUint i=0; i<kMaxStreams-1; i++) {
        GenerateMsg(EMsgDecodedStream);
        iSemUpstreamComplete.Wait();
    }
    TEST(!ReservoirIsFull());
    GenerateMsg(EMsgDecodedStream);
    while (!ReservoirIsFull()) {
        Thread::Sleep(1);
    }
    TEST(ReservoirIsFull());
    TEST(iReservoir->Jiffies() == jiffies);
    do {
        TEST(ReservoirIsFull());
        msg = iReservoir->Pull();
        msg = msg->Process(*this);
    } while (iLastMsg == EMsgAudioPcm);
    TEST(iLastMsg == EMsgDecodedStream);
    msg->RemoveRef();
    TEST(!ReservoirIsFull());
}

void SuiteAudioReservoir::GenerateMsg(EMsgType aType)
{
    Generate(EGenerateSingle, aType);
}

void SuiteAudioReservoir::GenerateMsgs(EMsgType aType)
{
    Generate(EFillReservoir, aType);
}

void SuiteAudioReservoir::Generate(EMsgGenerationState aState, EMsgType aType)
{
    iMsgGenerationState = aState;
    iNextGeneratedMsg = aType;
    iSemUpstream.Signal();
}

void SuiteAudioReservoir::MsgEnqueueThread()
{
    for (;;) {
        iSemUpstreamComplete.Signal();
        iSemUpstream.Wait();
        switch (iMsgGenerationState)
        {
        case EGenerateSingle:
            EnqueueMsg(iNextGeneratedMsg);
            break;
        case EFillReservoir:
            while (!EnqueueMsg(iNextGeneratedMsg)) {
            }
            break;
        case EExit:
            return;
        }
    }
}

TBool SuiteAudioReservoir::EnqueueMsg(EMsgType aType)
{
    TBool shouldBlock = false;
    Msg* msg = NULL;
    switch (aType)
    {
    default:
    case ENone:
    case EMsgPlayable:
        ASSERTS();
        break;
    case EMsgAudioPcm:
    {
        MsgAudio* audio = CreateAudio();
        shouldBlock = (iReservoir->SizeInJiffies() + audio->Jiffies() >= kReservoirSize);
        msg = audio;
        break;
    }
    case EMsgSilence:
    {
        MsgAudio* audio = iMsgFactory->CreateMsgSilence(Jiffies::kPerMs);
        shouldBlock = (iReservoir->SizeInJiffies() + audio->Jiffies() >= kReservoirSize);
        msg = audio;
        break;
    }
    case EMsgDecodedStream:
        msg = iMsgFactory->CreateMsgDecodedStream(0, 0, 0, 0, 0, Brx::Empty(), 0, 0, false, false, false, NULL);
        break;
    case EMsgMode:
        msg = iMsgFactory->CreateMsgMode(Brx::Empty(), true, true, NULL);
        break;
    case EMsgSession:
        msg = iMsgFactory->CreateMsgSession();
        break;
    case EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
        msg = iMsgFactory->CreateMsgTrack(*track, 0);
        track->RemoveRef();
    }
        break;
    case EMsgDelay:
        msg = iMsgFactory->CreateMsgDelay(Jiffies::kPerMs * 5);
        break;
    case EMsgEncodedStream:
        msg = iMsgFactory->CreateMsgEncodedStream(Brn("http://127.0.0.1:65535"), Brn("metatext"), 0, 0, false, false, NULL);
        break;
    case EMsgMetaText:
        msg = iMsgFactory->CreateMsgMetaText(Brn("metatext"));
        break;
    case EMsgHalt:
        msg = iMsgFactory->CreateMsgHalt();
        break;
    case EMsgFlush:
        msg = iMsgFactory->CreateMsgFlush(1);
        break;
    case EMsgWait:
        msg = iMsgFactory->CreateMsgWait();
        break;
    case EMsgQuit:
        msg = iMsgFactory->CreateMsgQuit();
        break;
    }
    iReservoir->Push(msg);
    return shouldBlock;
}

MsgAudio* SuiteAudioReservoir::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0xff, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 16, EMediaDataEndianLittle, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgMode* aMsg)
{
    iLastMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgSession* aMsg)
{
    iLastMsg = EMsgSession;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgTrack* aMsg)
{
    iLastMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgDelay* aMsg)
{
    iLastMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastMsg = EMsgEncodedStream;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return NULL;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgMetaText* aMsg)
{
    iLastMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgHalt* aMsg)
{
    iLastMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgFlush* aMsg)
{
    iLastMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgWait* aMsg)
{
    iLastMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastMsg = EMsgAudioPcm;
    MsgPlayable* playable = aMsg->CreatePlayable();
    ProcessorPcmBufPacked pcmProcessor;
    playable->Read(pcmProcessor);
    Brn buf(pcmProcessor.Buf());
//    playable->RemoveRef();
    const TByte* ptr = buf.Ptr();
    const TInt firstSubsample = (ptr[0]<<8) | ptr[1];
    const TUint bytes = buf.Bytes();
    const TInt lastSubsample = (ptr[bytes-2]<<8) | ptr[bytes-1];
    TEST(firstSubsample == 0xffff);
    TEST(firstSubsample == lastSubsample);
    if (firstSubsample != lastSubsample) {
        Print("firstSubsample=%08x, lastSubsample=%08x\n", firstSubsample, lastSubsample);
    }
    playable->RemoveRef();
    return NULL;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgSilence* aMsg)
{
    iLastMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // MsgPlayable not used in this test
    return NULL;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgQuit* aMsg)
{
   iLastMsg = EMsgQuit;
    return aMsg;
}


// SuiteReservoirHistory

SuiteReservoirHistory::SuiteReservoirHistory()
    : Suite("DecodedReservoir History")
    , iDequeuedJiffies(0)
    , iHistoryPointCount(0)
    , iStopAudioGeneration(false)
    , iTrackId(UINT_MAX)
    , iStreamId(UINT_MAX)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 200, 200, 20, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iReservoir = new DecodedAudioReservoir(kReservoirSize, kMaxStreams, kMaxStreams);
    memset(iBuf, 0xff, sizeof(iBuf));
}

SuiteReservoirHistory::~SuiteReservoirHistory()
{
    delete iReservoir;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteReservoirHistory::Test()
{
    static const TUint kPcmMsgCount = 15;
    iThread = new ThreadFunctor("RHPT", MakeFunctor(*this, &SuiteReservoirHistory::PullerThread));
    iThread->Start();
    iStartCalled = iNewStreamCalled = iNotifySizeCalled = false;
    iReservoir->Push(iMsgFactory->CreateMsgMode(Brn("ClockPullTest"), false, true, this));
    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    MsgTrack* msgTrack = iMsgFactory->CreateMsgTrack(*track, 0);
    iTrackId = msgTrack->IdPipeline();
    track->RemoveRef();
    iReservoir->Push(msgTrack);
    MsgDecodedStream* msgStream = iMsgFactory->CreateMsgDecodedStream(100, 12, 16, 44100, 2, Brn("dummy"), 1LL<<40, 0, false, false, false, NULL);
    iStreamId = msgStream->StreamInfo().StreamId();
    iReservoir->Push(msgStream);
    TUint pcmMsgs = kPcmMsgCount;
    TUint64 trackOffset = 0;
    Brn audioBuf(iBuf, sizeof(iBuf));
    while (!iStopAudioGeneration) {
        MsgAudio* audio;
        if (pcmMsgs == 0) {
            audio = iMsgFactory->CreateMsgSilence(400 * Jiffies::kPerMs);
            pcmMsgs = kPcmMsgCount;
        }
        else {
            audio = iMsgFactory->CreateMsgAudioPcm(audioBuf, kNumChannels, kSampleRate, kBitDepth, EMediaDataEndianLittle, trackOffset);
            pcmMsgs--;
        }
        trackOffset += audio->Jiffies();
        iReservoir->Push(audio);
    }
    delete iThread;
    TEST(iStartCalled);
    TEST(iNewStreamCalled);
    TEST(iNotifySizeCalled);
}

void SuiteReservoirHistory::PullerThread()
{
    Thread::Sleep(200); /* We test below that history sizes are non-zero.  Give pushing
                           thread a chance to fill the reservoir to limit the chances
                           of it always being close to empty */
    while (!iStopAudioGeneration) {
        Msg* msg = iReservoir->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
        Thread::Sleep(1);
    }

    // consume any remaining msgs in case pushing thread is blocked
    while (!iReservoir->IsEmpty()) {
        iReservoir->Pull()->RemoveRef();
    }
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return NULL;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgAudioPcm* aMsg)
{
    iDequeuedJiffies += aMsg->Jiffies();
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgSilence* aMsg)
{
    iDequeuedJiffies += aMsg->Jiffies();
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return NULL;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgDecodedStream* aMsg)
{
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgSession* aMsg)
{
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return NULL;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return NULL;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgHalt* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return NULL;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return NULL;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgWait* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return NULL;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgQuit* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return NULL;
}

void SuiteReservoirHistory::StartDecodedReservoir(TUint aCapacityJiffies, TUint aNotificationFrequency)
{
    TEST(aCapacityJiffies == kReservoirSize);
    TEST(aNotificationFrequency == iReservoir->kUtilisationSamplePeriodJiffies);
    iStartCalled = true;
}

void SuiteReservoirHistory::NewStreamDecodedReservoir(TUint aTrackId, TUint aStreamId)
{
    TEST(aTrackId == iTrackId);
    TEST(aStreamId == iStreamId);
    iNewStreamCalled = true;
}

void SuiteReservoirHistory::NotifySizeDecodedReservoir(TUint aJiffies)
{
    iHistoryPointCount++;
    TEST(aJiffies != 0);
    TEST(aJiffies < 0x40000000); // arbitrarily chosen value.  2^30 or ~17s of audio

    if (iHistoryPointCount == kTotalHistoryUpdates) {
        iStopAudioGeneration = true;
    }
    iNotifySizeCalled = true;
}

void SuiteReservoirHistory::StopDecodedReservoir()
{
    ASSERTS(); // test only generates a single MsgMode so this shouldn't be called
}

void SuiteReservoirHistory::StartStarvationMonitor(TUint /*aCapacityJiffies*/, TUint /*aNotificationFrequency*/)
{
    ASSERTS();
}

void SuiteReservoirHistory::NewStreamStarvationMonitor(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS();
}

void SuiteReservoirHistory::NotifySizeStarvationMonitor(TUint /*aJiffies*/)
{
    ASSERTS();
}

void SuiteReservoirHistory::StopStarvationMonitor()
{
    ASSERTS();
}



void TestAudioReservoir()
{
    Runner runner("Decoded Audio Reservoir tests\n");
    runner.Add(new SuiteAudioReservoir());
    runner.Add(new SuiteReservoirHistory());
    runner.Run();
}
