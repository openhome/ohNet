#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/AudioReservoir.h>
#include <OpenHome/Media/DecodedAudioReservoir.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/InfoProvider.h>
#include "AllocatorInfoLogger.h"
#include <OpenHome/Media/ProcessorPcmUtils.h>
#include <OpenHome/Media/ClockPuller.h>

#include <string.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteAudioReservoir : public Suite, private IMsgProcessor, private IClockPuller
{
    static const TUint kDecodedAudioCount = 512;
    static const TUint kMsgAudioPcmCount  = 512;
    static const TUint kMsgSilenceCount   = 1;

    static const TUint kReservoirSize = Jiffies::kJiffiesPerMs * 500;

    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
public:
    SuiteAudioReservoir();
    ~SuiteAudioReservoir();
    void Test();
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
private: // from IClockPuller
    void NotifySize(TUint aJiffies);
    void Stop();
private:
    enum EMsgType
    {
        ENone
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgDecodedStream
       ,EMsgMode
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
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    AudioReservoir* iReservoir;
    ThreadFunctor* iThread;
    EMsgGenerationState iMsgGenerationState;
    EMsgType iNextGeneratedMsg;
    EMsgType iLastMsg;
    Semaphore iSemUpstream;
    Semaphore iSemUpstreamComplete;
    TUint64 iTrackOffset;
    TByte iBuf[DecodedAudio::kMaxBytes];
};

class SuiteReservoirHistory : public Suite, private IMsgProcessor
{
    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
    static const TUint kBitDepth = 16;
    static const TUint kReservoirSize = Jiffies::kJiffiesPerMs * 1000;
    static const TUint kMaxHistorySamples = 10;
    static const TUint kTotalHistoryUpdates = kMaxHistorySamples * 2;
public:
    SuiteReservoirHistory();
    ~SuiteReservoirHistory();
private: // from Suite
    void Test();
private:
    void PullerThread();
    void HistoryPointAdded();
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
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    DecodedAudioReservoir* iReservoir;
    ThreadFunctor* iThread;
    TUint64 iDequeuedJiffies;
    UtilisationHistory* iHistory;
    TUint iHistoryPointCount;
    TBool iStopAudioGeneration;
    TByte iBuf[DecodedAudio::kMaxBytes];
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
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, kDecodedAudioCount, kMsgAudioPcmCount, kMsgSilenceCount, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iReservoir = new DecodedAudioReservoir(kReservoirSize, *this    );
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
    EMsgType types[] = { EMsgSilence, EMsgDecodedStream, EMsgMode, EMsgTrack, EMsgDelay, EMsgEncodedStream, EMsgMetaText, EMsgFlush, EMsgWait, EMsgHalt, EMsgQuit };
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
    iSemUpstreamComplete.Wait();
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
        shouldBlock = (iReservoir->Size() + audio->Jiffies() >= kReservoirSize);
        msg = audio;
        break;
    }
    case EMsgSilence:
    {
        MsgAudio* audio = iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs);
        shouldBlock = (iReservoir->Size() + audio->Jiffies() >= kReservoirSize);
        msg = audio;
        break;
    }
    case EMsgDecodedStream:
        msg = iMsgFactory->CreateMsgDecodedStream(0, 0, 0, 0, 0, Brx::Empty(), 0, 0, false, false, false, NULL);
        break;
    case EMsgMode:
        msg = iMsgFactory->CreateMsgMode(Brx::Empty(), true, true);
        break;
    case EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty(), NULL, false);
        msg = iMsgFactory->CreateMsgTrack(*track, 0);
        track->RemoveRef();
    }
        break;
    case EMsgDelay:
        msg = iMsgFactory->CreateMsgDelay(Jiffies::kJiffiesPerMs * 5);
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
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 16, EMediaDataLittleEndian, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgMode* aMsg)
{
    iLastMsg = EMsgMode;
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

void SuiteAudioReservoir::NotifySize(TUint /*aJiffies*/)
{
}

void SuiteAudioReservoir::Stop()
{
}


// SuiteReservoirHistory

SuiteReservoirHistory::SuiteReservoirHistory()
    : Suite("DecodedReservoir History")
    , iDequeuedJiffies(0)
    , iHistoryPointCount(0)
    , iStopAudioGeneration(false)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 200, 200, 20, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iHistory = new UtilisationHistory(kMaxHistorySamples, MakeFunctor(*this, &SuiteReservoirHistory::HistoryPointAdded));
    iReservoir = new DecodedAudioReservoir(kReservoirSize, *iHistory);
    memset(iBuf, 0xff, sizeof(iBuf));
}

SuiteReservoirHistory::~SuiteReservoirHistory()
{
    delete iReservoir;
    delete iHistory;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteReservoirHistory::Test()
{
    static const TUint kPcmMsgCount = 15;
    iThread = new ThreadFunctor("RHPT", MakeFunctor(*this, &SuiteReservoirHistory::PullerThread));
    iThread->Start();
    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty(), NULL, true);
    MsgTrack* msgTrack = iMsgFactory->CreateMsgTrack(*track, 0);
    track->RemoveRef();
    iReservoir->Push(msgTrack);
    TUint pcmMsgs = kPcmMsgCount;
    TUint64 trackOffset = 0;
    Brn audioBuf(iBuf, sizeof(iBuf));
    while (!iStopAudioGeneration) {
        MsgAudio* audio;
        if (pcmMsgs == 0) {
            audio = iMsgFactory->CreateMsgSilence(400 * Jiffies::kJiffiesPerMs);
            pcmMsgs = kPcmMsgCount;
        }
        else {
            audio = iMsgFactory->CreateMsgAudioPcm(audioBuf, kNumChannels, kSampleRate, kBitDepth, EMediaDataLittleEndian, trackOffset);
            pcmMsgs--;
        }
        trackOffset += audio->Jiffies();
        iReservoir->Push(audio);
    }
    delete iThread;
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

void SuiteReservoirHistory::HistoryPointAdded()
{
    iHistoryPointCount++;
    const std::vector<TUint64>& history = iHistory->History();
    TEST(history.capacity() == kMaxHistorySamples);
    if (iHistoryPointCount > kMaxHistorySamples) {
        TEST(iHistory->StartIndex() == iHistoryPointCount % kMaxHistorySamples);
    }
    for (TUint i=0; i<history.size(); i++) {
        TEST(history[i] != 0);
        TEST(history[i] < 0xffffffffu); // arbitrarily chosen value.  2^32 or ~70s of audio
    }
    if (iHistoryPointCount == kTotalHistoryUpdates) {
        iStopAudioGeneration = true;
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

Msg* SuiteReservoirHistory::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return NULL;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgMode* aMsg)
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


void TestAudioReservoir()
{
    Runner runner("Decoded Audio Reservoir tests\n");
    runner.Add(new SuiteAudioReservoir());
    runner.Add(new SuiteReservoirHistory());
    runner.Run();
}