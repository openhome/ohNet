#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/AudioReservoir.h>
#include <OpenHome/Media/DecodedAudioReservoir.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/InfoProvider.h>
#include "AllocatorInfoLogger.h"
#include <OpenHome/Media/ProcessorPcmUtils.h>

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

    static const TUint kReservoirSize = Jiffies::kJiffiesPerMs * 500;

    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
public:
    SuiteAudioReservoir();
    ~SuiteAudioReservoir();
    void Test();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgAudioFormat* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    enum EMsgType
    {
        ENone
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgAudioFormat
       ,EMsgTrack
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgHalt
       ,EMsgFlush
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
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, kDecodedAudioCount, kMsgAudioPcmCount, kMsgSilenceCount, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    iReservoir = new DecodedAudioReservoir(kReservoirSize);
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
    Msg* msg = iReservoir->Pull();
    msg = msg->Process(*this);
    TEST(iLastMsg == EMsgAudioPcm);
    ASSERT(msg == NULL);

    // Check that Silence, Track, AudioStream, MetaText, Quit & Halt msgs are passed through.
    EMsgType types[] = { EMsgSilence, EMsgAudioFormat, EMsgTrack, EMsgEncodedStream, EMsgMetaText, EMsgHalt, EMsgQuit };
    for (TUint i=0; i<sizeof(types)/sizeof(types[0]); i++) {
        GenerateMsg(types[0]);
        msg = iReservoir->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
        TEST(iLastMsg == types[0]);
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

    // Pull single audio msg.  Add Flush; check that next msg Pull()ed is the Flush and that reservoir is now empty.
    msg = iReservoir->Pull();
    msg = msg->Process(*this);
    TEST(iLastMsg == EMsgAudioPcm);
    ASSERT(msg == NULL);
    (void)iSemUpstreamComplete.Clear();
    GenerateMsg(EMsgFlush);
    iSemUpstreamComplete.Wait();
    msg = iReservoir->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
    TEST(iLastMsg == EMsgFlush);
    TEST(iReservoir->Jiffies() == 0);
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
    Msg* msg = NULL;
    switch (aType)
    {
    default:
    case ENone:
    case EMsgPlayable:
        ASSERTS();
        break;
    case EMsgAudioPcm:
        msg = CreateAudio();
        break;
    case EMsgSilence:
        msg = iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs);
        break;
    case EMsgAudioFormat:
        msg = iMsgFactory->CreateMsgAudioFormat(0, 0, 0, 0, Brx::Empty(), 0, false);
        break;
    case EMsgTrack:
        msg = iMsgFactory->CreateMsgTrack();
        break;
    case EMsgEncodedStream:
        msg = iMsgFactory->CreateMsgEncodedStream(Brn("http://127.0.0.1:65535"), Brn("metatext"), 0, false, false, 0, NULL);
        break;
    case EMsgMetaText:
        msg = iMsgFactory->CreateMsgMetaText(Brn("metatext"));
        break;
    case EMsgHalt:
        msg = iMsgFactory->CreateMsgHalt();
        break;
    case EMsgFlush:
        msg = iMsgFactory->CreateMsgFlush();
        break;
    case EMsgQuit:
        msg = iMsgFactory->CreateMsgQuit();
        break;
    }
    return iReservoir->Enqueue(msg);
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

Msg* SuiteAudioReservoir::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return NULL;
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

Msg* SuiteAudioReservoir::ProcessMsg(MsgAudioFormat* aMsg)
{
    iLastMsg = EMsgAudioFormat;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgTrack* aMsg)
{
    iLastMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastMsg = EMsgEncodedStream;
    return aMsg;
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

Msg* SuiteAudioReservoir::ProcessMsg(MsgQuit* aMsg)
{
    iLastMsg = EMsgQuit;
    return aMsg;
}



void TestAudioReservoir()
{
    Runner runner("Decoded Audio Reservoir tests\n");
    runner.Add(new SuiteAudioReservoir());
    runner.Run();
}


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestAudioReservoir();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
