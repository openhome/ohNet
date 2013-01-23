#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Stopper.h>
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

class SuiteStopper : public Suite, private IPipelineElementUpstream, private IStopperObserver, private IMsgProcessor
{
    static const TUint kDecodedAudioCount = 2;
    static const TUint kMsgAudioPcmCount  = 4;

    static const TUint kRampDuration = Jiffies::kJiffiesPerMs * 400;

    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
public:
    SuiteStopper();
    ~SuiteStopper();
    void Test();
private: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IStopperObserver
    void PipelineHalted();
    void PipelineFlushed();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
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
       ,EMsgDecodedStream
       ,EMsgTrack
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgQuit
    };
enum EMsgGenerationState
{
    EStateWait
   ,EStateAudioFillInitial
   ,EStateAudioFillPostStarvation
   ,EStateHalt
   ,EStateQuit
   ,EStateCompleted
};
private:
    void FlushThread();
    MsgAudio* CreateAudio();
private:
    MsgFactory* iMsgFactory;
    AllocatorInfoLogger iInfoAggregator;
    Stopper* iStopper;
    EMsgType iNextGeneratedMsg;
    EMsgType iLastMsg;
    TUint iJiffies;
    TUint iPipelineHaltedCount;
    TUint iPipelineFlushedCount;
    TUint iAudioMsgsDue;
    Semaphore iFlushThreadExit;
    TUint64 iTrackOffset;
    TByte iBuf[DecodedAudio::kMaxBytes];
};

} // namespace Media
} // namespace OpenHome


// SuiteStopper

SuiteStopper::SuiteStopper()
    : Suite("Stopper tests")
    , iNextGeneratedMsg(ENone)
    , iLastMsg(ENone)
    , iJiffies(0)
    , iPipelineHaltedCount(0)
    , iPipelineFlushedCount(0)
    , iAudioMsgsDue(0)
    , iFlushThreadExit("HACK", 0)
    , iTrackOffset(0)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, kDecodedAudioCount, kMsgAudioPcmCount, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    iStopper = new Stopper(*iMsgFactory, *this, *this, kRampDuration);
}

SuiteStopper::~SuiteStopper()
{
    delete iStopper;
    delete iMsgFactory;
}

void SuiteStopper::Test()
{
    /*
    Test goes something like
        Create Stopper.  Start() then deliver 0x7f filled audio until ramp up completes.  
        Check that ramp size matches kRampDuration and that the final msg was Split to ensure this.
        Check that remaining audio is not ramped.
        Deliver Track, Metatext, Quit msgs.  Check they're passed through.
        BeginHalt.  Deliver more audio, checking it ramps down
        BeginFlush.  Deliver other msgs, check none are delivered and PipelineFlushed is called.
        Start() then deliver 0x7f filled audio.  Check it ramps up.
        Halt then re-Start soon after.  Check no halt msg is output
        Send halt msg.  Check there was no previous ramping down.
    */

    TEST(iStopper->iState == Stopper::EHalted);
    iStopper->Start();
    TEST(iStopper->iState == Stopper::EStarting);
    iNextGeneratedMsg = EMsgAudioPcm;
    Msg* msg;
    // Pull (audio) until state changes to ERunning.  Check we've ramped over kRampDuration.
    do {
        TEST(iStopper->iState == Stopper::EStarting);
        TEST(iStopper->iQueue.IsEmpty());
        msg = iStopper->Pull();
        msg = msg->Process(*this);
        if (msg != NULL) {
            msg->RemoveRef();
        }
        TEST(iLastMsg == EMsgAudioPcm);
    } while(iJiffies < kRampDuration);
    TEST(iJiffies == kRampDuration);
    TEST(iStopper->iState == Stopper::ERunning);
    TEST(!iStopper->iQueue.IsEmpty());

    // Check that remaining audio is not ramped.
    msg = iStopper->Pull();
    (void)msg->Process(*this);
    TEST(iLastMsg == EMsgAudioPcm);
    TEST(iStopper->iQueue.IsEmpty());

    // Deliver Silence, Track, AudioStream, Metatext, Quit msgs.  Check they're passed through.
    EMsgType expected[] = { EMsgSilence, EMsgDecodedStream, EMsgTrack, EMsgEncodedStream, EMsgMetaText, EMsgQuit };
    for (TUint i=0; i<sizeof(expected)/sizeof(expected[0]); i++) {
        iNextGeneratedMsg = expected[i];
        msg = iStopper->Pull();
        (void)msg->Process(*this);
        msg->RemoveRef();
        TEST(iLastMsg == expected[i]);
    }

    // BeginHalt.  Deliver more audio, checking it ramps down
    TEST(iStopper->iState == Stopper::ERunning);
    iStopper->BeginHalt();
    iJiffies = 0;
    iNextGeneratedMsg = EMsgAudioPcm;
    do {
        TEST(iStopper->iState == Stopper::EHalting);
        TEST(iStopper->iQueue.IsEmpty());
        msg = iStopper->Pull();
        msg = msg->Process(*this);
        if (msg != NULL) {
            msg->RemoveRef();
        }
        TEST(iLastMsg == EMsgAudioPcm);
    } while(iJiffies < kRampDuration);
    TEST(iJiffies == kRampDuration);
    TEST(iStopper->iState == Stopper::EHaltPending);
    TEST(iPipelineHaltedCount == 0);
    msg = iStopper->Pull();
    (void)msg->Process(*this);
    msg->RemoveRef();
    TEST(iPipelineHaltedCount == 1);
    TEST(iPipelineFlushedCount == 0);
    TEST(iStopper->iState == Stopper::EHalted);
    TEST(iLastMsg == EMsgHalt);

    // BeginFlush.  Deliver other msgs, check none are delivered and PipelineFlushed is called.
    // Pull() will block when Stopper reads a Flush until Start() is called again
    // We avoid deadlock here by pulling from a different thread and calling Start
    // ...here when we noticed the Stopper is blocked
    iLastMsg = ENone;
    ThreadFunctor* flushThread = new ThreadFunctor("HACK", MakeFunctor(*this, &SuiteStopper::FlushThread));
    iAudioMsgsDue = 5;
    iNextGeneratedMsg = EMsgFlush;
    iStopper->BeginFlush();
    TEST(iStopper->iState == Stopper::EFlushing);
    flushThread->Start();
    for (;;) {
        if (iStopper->iState == Stopper::EHalted) {
            break;
        }
        Thread::Sleep(10);
    }
    TEST(iLastMsg == ENone);
    TEST(iStopper->iQueue.IsEmpty());
    TEST(iPipelineHaltedCount == 1);
    TEST(iPipelineFlushedCount == 1);
        
    // Start() then deliver 0x7f filled audio.  Check it ramps up.
    iNextGeneratedMsg = EMsgAudioPcm;
    iJiffies = 0;
    iStopper->Start();
    TEST(iStopper->iState == Stopper::EStarting);
    iFlushThreadExit.Wait();
    // Pull (audio, again) until state changes to ERunning.  Check we've ramped over kRampDuration.
    do {
        if (iStopper->iState != Stopper::EStarting) {
            Print("iJiffies=%08x (from duration %08x).  State=%u\n", iJiffies, kRampDuration, iStopper->iState);
        }
        TEST(iStopper->iState == Stopper::EStarting);
        TEST(iStopper->iQueue.IsEmpty());
        msg = iStopper->Pull();
        msg = msg->Process(*this);
        if (msg != NULL) {
            msg->RemoveRef();
        }
        TEST(iLastMsg == EMsgAudioPcm);
    } while(iJiffies < kRampDuration);
    delete flushThread; // can't be deleted until the next msg is Pulled
    TEST(iJiffies == kRampDuration);
    TEST(iStopper->iState == Stopper::ERunning);
    TEST(!iStopper->iQueue.IsEmpty());

    // Halt then re-Start soon after.  Check no halt msg is output
    iJiffies = 0;
    iStopper->BeginHalt();
    msg = iStopper->Pull();
    (void)msg->Process(*this);
    TEST(iLastMsg == EMsgAudioPcm);
    TEST(iStopper->iState == Stopper::EHalting);
    iStopper->Start();
    TEST(iStopper->iState == Stopper::EStarting);
    msg = iStopper->Pull();
    (void)msg->Process(*this);
    TEST(iLastMsg == EMsgAudioPcm);
    TEST(iStopper->iState == Stopper::ERunning);
    TEST(iPipelineHaltedCount == 1);
    TEST(iPipelineFlushedCount == 1);

    // Send halt msg.  Check there was no previous ramping down.
    msg = iStopper->Pull();
    (void)msg->Process(*this);
    TEST(iLastMsg == EMsgAudioPcm);
    TEST(iStopper->iState == Stopper::ERunning);
    iNextGeneratedMsg = EMsgHalt;
    msg = iStopper->Pull();
    (void)msg->Process(*this);
    msg->RemoveRef();
    TEST(iLastMsg == EMsgHalt);
}

void SuiteStopper::FlushThread()
{
    Msg* msg = iStopper->Pull();
    (void)msg->Process(*this);
    TEST(iLastMsg == EMsgAudioPcm);
    iFlushThreadExit.Signal();
}

Msg* SuiteStopper::Pull()
{
    if (iAudioMsgsDue > 0) {
        --iAudioMsgsDue;
        return CreateAudio();
    }
    switch (iNextGeneratedMsg)
    {
    case EMsgAudioPcm:
        return CreateAudio();
    case EMsgSilence:
        return iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs);
    case EMsgDecodedStream:
        return iMsgFactory->CreateMsgDecodedStream(0, 0, 0, 0, 0, Brx::Empty(), 0, 0, false);
    case EMsgTrack:
        return iMsgFactory->CreateMsgTrack();
    case EMsgEncodedStream:
        return iMsgFactory->CreateMsgEncodedStream(Brn("http://1.2.3.4:5"), Brn("metatext"), 0, false, false, 0, NULL);
    case EMsgMetaText:
        return iMsgFactory->CreateMsgMetaText(Brn("metatext"));
    case EMsgHalt:
        return iMsgFactory->CreateMsgHalt();
    case EMsgFlush:
        return iMsgFactory->CreateMsgFlush();
    case EMsgQuit:
        return iMsgFactory->CreateMsgQuit();
    default:
        ASSERTS();
        return NULL;
    }
}

MsgAudio* SuiteStopper::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0x7f, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 16, EMediaDataLittleEndian, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

void SuiteStopper::PipelineHalted()
{
    iPipelineHaltedCount++;
}

void SuiteStopper::PipelineFlushed()
{
    iPipelineFlushedCount++;
}

Msg* SuiteStopper::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return NULL;
}

Msg* SuiteStopper::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastMsg = EMsgAudioPcm;
    TUint jiffies = aMsg->Jiffies();

    MsgPlayable* playable = aMsg->CreatePlayable();
    ProcessorPcmBufPacked pcmProcessor;
    playable->Read(pcmProcessor);
    Brn buf(pcmProcessor.Buf());
    playable->RemoveRef();
    const TByte* ptr = buf.Ptr();
    const TInt firstSubsample = (ptr[0]<<8) | ptr[1];
    const TUint bytes = buf.Bytes();
    const TInt lastSubsample = (ptr[bytes-2]<<8) | ptr[bytes-1];

    switch (iStopper->iState)
    {
    case Stopper::EHalting:
        TEST(firstSubsample > lastSubsample);
        break;
    case Stopper::EStarting:
        TEST(firstSubsample < lastSubsample);
        break;
    default:
        if (iJiffies >= kRampDuration) {
            TEST(firstSubsample == lastSubsample);
        }
        break;
    }
    iJiffies += jiffies;
    return NULL;
}

Msg* SuiteStopper::ProcessMsg(MsgSilence* aMsg)
{
    iLastMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // MsgPlayable not expected at this stage of the pipeline
    return NULL;
}

Msg* SuiteStopper::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgTrack* aMsg)
{
    iLastMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastMsg = EMsgEncodedStream;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgMetaText* aMsg)
{
    iLastMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgHalt* aMsg)
{
    iLastMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgFlush* aMsg)
{
    iLastMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgQuit* aMsg)
{
    iLastMsg = EMsgQuit;
    return aMsg;
}



void TestStopper()
{
    Runner runner("Stopper tests\n");
    runner.Add(new SuiteStopper());
    runner.Run();
}


