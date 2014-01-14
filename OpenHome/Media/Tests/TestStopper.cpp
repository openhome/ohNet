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

class SuiteStopper : public Suite, private IPipelineElementUpstream, private IFlushIdProvider, private IStopperObserver, private IStreamHandler, private IMsgProcessor, private ISupply
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
private: // from IFlushIdProvider
    TUint NextFlushId();
private: // from IStopperObserver
    void PipelineHalted(TUint aHaltId);
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
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
private: // from ISupply
    void OutputTrack(Track& aTrack, TUint aTrackId, const Brx& aMode);
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId);
    void OutputData(const Brx& aData);
    void OutputMetadata(const Brx& aMetadata);
    void OutputFlush(TUint aFlushId);
    void OutputHalt(TUint aHaltId);
    void OutputQuit();
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
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    Stopper* iStopper;
    EStreamPlay iOkToPlay;
    EMsgType iNextGeneratedMsg;
    EMsgType iLastMsg;
    TUint iJiffies;
    TUint iPipelineHaltedCount;
    TUint iAudioMsgsDue;
    TUint iFlushMsgsDue;
    TUint iNextFlushId;
    TUint iTrackId;
    TUint iStreamId;
    MsgFlush* iFlush;
    Semaphore iFlushThreadExit;
    TUint64 iTrackOffset;
    TByte iBuf[DecodedAudio::kMaxBytes];
    TUint iLastHaltId;
    TUint iLastObserverHaltId;
    TUint iNextHaltId;
};

} // namespace Media
} // namespace OpenHome


// SuiteStopper

SuiteStopper::SuiteStopper()
    : Suite("Stopper tests")
    , iOkToPlay(ePlayYes)
    , iNextGeneratedMsg(ENone)
    , iLastMsg(ENone)
    , iJiffies(0)
    , iPipelineHaltedCount(0)
    , iAudioMsgsDue(0)
    , iFlushMsgsDue(0)
    , iNextFlushId(MsgFlush::kIdInvalid + 1000)
    , iTrackId(0)
    , iStreamId(0)
    , iFlush(NULL)
    , iFlushThreadExit("HACK", 0)
    , iTrackOffset(0)
    , iLastHaltId(MsgHalt::kIdInvalid)
    , iLastObserverHaltId(MsgHalt::kIdInvalid)
    , iNextHaltId(MsgHalt::kIdNone)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, kDecodedAudioCount, kMsgAudioPcmCount, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iStopper = new Stopper(*iMsgFactory, *this, *this, *this, *this, kRampDuration);
}

SuiteStopper::~SuiteStopper()
{
    delete iStopper;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteStopper::Test()
{
    /*
    Test goes something like
        Start.  Check that audio isn't ramped.
        Deliver Track, Metatext, Quit msgs.  Check they're passed through.
        BeginHalt then re-Start soon after.  Check no Halt msg is output
        BeginHalt.  Deliver more audio, checking it ramps down
        Start() then deliver 0x7f filled audio.  Check it ramps up.
        BeginHalt(id).  Deliver more audio, checking it ramps down
        Start; deliver 0x7f filled audio, check it is discarded
        ...deliver MsgEncodedStream followed by more audio, check it is passed on
        Deliver new MsgEncodedStream; respond Later to OkToPlay; check Halt is output.
        Start() then deliver 0x7f filled audio.  Check initial audio isn't ramped.
        RemoveCurrentStream().  Check that audio ramps down then flushes.
        Check that subsequent audio is discarded.
        Check that subsequent stream plays.
        BeginHalt.  Deliver more audio, checking it ramps down
        RemoveCurrentStream().  Check that subsequent audio is discarded.
    */

    Print("Start.  Check that audio isn't ramped\n");
    TEST(iStopper->iState == Stopper::EHalted);
    iStopper->Start();
    TEST(iStopper->iState == Stopper::EStarting);
    iNextGeneratedMsg = EMsgEncodedStream;
    Msg* msg = iStopper->Pull();
    (void)msg->Process(*this);
    msg->RemoveRef();
    TEST(iStopper->iState == Stopper::ERunning);
    iNextGeneratedMsg = EMsgAudioPcm;
    msg = iStopper->Pull();
    (void)msg->Process(*this);
    TEST(iLastMsg == EMsgAudioPcm);
    TEST(iStopper->iQueue.IsEmpty());

    Print("\nCheck msgs are passed through\n");
    // Deliver Track, DecodedStream, Metatext, Quit msgs.  Check they're passed through.
    // FIXME - may want to include test for EncodedStream but these aren't passed on by Stopper at present
    EMsgType expected[] = { EMsgDecodedStream, EMsgTrack, EMsgMetaText, EMsgQuit };
    for (TUint i=0; i<sizeof(expected)/sizeof(expected[0]); i++) {
        iNextGeneratedMsg = expected[i];
        msg = iStopper->Pull();
        (void)msg->Process(*this);
        msg->RemoveRef();
        TEST(iLastMsg == expected[i]);
    }

    Print("\nBeginHalt then re-Start soon after.  Check no Halt msg is output\n");
    TUint pipelineHaltedCount = 0;
    iStopper->BeginHalt();
    TEST(iStopper->iState != Stopper::EHalted);
    iNextGeneratedMsg = EMsgAudioPcm;
    iStopper->Start();
    msg = iStopper->Pull();
    msg = msg->Process(*this);
    if (msg != NULL) {
        msg->RemoveRef();
    }
    TEST(iLastMsg != EMsgHalt);
    TEST(iStopper->iState == Stopper::ERunning);
    TEST(iPipelineHaltedCount == pipelineHaltedCount);

    Print("\nBeginHalt.  Deliver more audio, checking it ramps down\n");
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
    TEST(iPipelineHaltedCount == pipelineHaltedCount);
    msg = iStopper->Pull();
    (void)msg->Process(*this);
    msg->RemoveRef();
    TEST(iPipelineHaltedCount == ++pipelineHaltedCount);
    TEST(iStopper->iState == Stopper::EHalted);
    TEST(iLastMsg == EMsgHalt);

    Print("\nStart then deliver 0x7f filled audio.  Check it ramps up.\n");
    iNextGeneratedMsg = EMsgAudioPcm;
    iJiffies = 0;
    iStopper->Start();
    while (!iStopper->iQueue.IsEmpty()) {
        /* Discard any audio fragment left over from earlier ramp
           If we don't do this, we risk Pull()ing a tiny fragment whose ramp is [0..0]
           ...which would confuse our ramping tests in ProcessMsg(MsgAudioPcm*) */
        msg = iStopper->Pull()->Process(*this);
        if (msg != NULL) {
            msg->RemoveRef();
        }
    }
    TEST(iStopper->iState == Stopper::EStarting);
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
    TEST(iJiffies == kRampDuration);
    TEST(iStopper->iState == Stopper::ERunning);
    TEST(!iStopper->iQueue.IsEmpty());


    // BeginHalt(id).  Deliver more audio, checking it ramps down; PipelineHalted() should pass id back to us.
    Print("BeginHalt(id)\n");
    TEST(iStopper->iState == Stopper::ERunning);
    static const TUint kHaltId = 1234;
    iStopper->BeginHalt(kHaltId);
    iNextHaltId = kHaltId;
    iJiffies = 0;
    while (!iStopper->iQueue.IsEmpty()) {
        msg = iStopper->Pull()->Process(*this);
        if (msg != NULL) {
            msg->RemoveRef();
        }
    }
    iNextGeneratedMsg = EMsgAudioPcm;
    do {
        TEST(iStopper->iState == Stopper::EHalting);
        if (iStopper->iState != Stopper::EHalting) {
            Print("iStopper->iState=%d\n", iStopper->iState);
        }
        TEST(iStopper->iQueue.IsEmpty());
        msg = iStopper->Pull();
        msg = msg->Process(*this);
        if (msg != NULL) {
            msg->RemoveRef();
        }
        TEST(iLastMsg == EMsgAudioPcm);
    } while(iJiffies < kRampDuration);
    TEST(iJiffies == kRampDuration);
    TEST(iStopper->iState == Stopper::EFlushing);
    TEST(iPipelineHaltedCount == pipelineHaltedCount);
    iAudioMsgsDue = 5;
    iNextGeneratedMsg = EMsgHalt;
    msg = iStopper->Pull();
    (void)msg->Process(*this);
    msg->RemoveRef();
    TEST(iPipelineHaltedCount == ++pipelineHaltedCount);
    TEST(iStopper->iState == Stopper::EHalted);
    TEST(iLastMsg == EMsgHalt);
    TEST(iLastHaltId == kHaltId);
    TEST(iLastObserverHaltId == kHaltId);
    iNextHaltId = MsgHalt::kIdNone;

    // Start; deliver 0x7f filled audio, check it is discarded
    // ...deliver MsgEncodedStream followed by more audio, check it is passed on
    // Check initial audio isn't ramped.
    Print("\nDiscard audio until new stream\n");
    iStopper->Start();
    iAudioMsgsDue = 5;
    iNextGeneratedMsg = EMsgEncodedStream;
    msg = iStopper->Pull()->Process(*this);
    if (msg != NULL) {
        msg->RemoveRef();
    }
    TEST(iLastMsg == EMsgDecodedStream); // EMsgDecodedStream due to test strangeness
    iNextGeneratedMsg = EMsgAudioPcm;
    TEST(iStopper->iState == Stopper::ERunning);
    msg = iStopper->Pull()->Process(*this);
    if (msg != NULL) {
        msg->RemoveRef();
    }
    TEST(iLastMsg == EMsgAudioPcm);
    TEST(iStopper->iState == Stopper::ERunning);

    // Deliver new MsgEncodedStream; respond Later to OkToPlay; check Halt is output.
    Print("\nOkToPlay returns ePlayLater\n");
    iOkToPlay = ePlayLater;
    iNextGeneratedMsg = EMsgEncodedStream;
    msg = iStopper->Pull()->Process(*this);
    if (msg != NULL) {
        msg->RemoveRef();
    }
    TEST(iLastMsg == EMsgHalt);
    TEST(iStopper->iState == Stopper::EHalted);
    TEST(iPipelineHaltedCount == ++pipelineHaltedCount);
    TEST(iLastHaltId == MsgHalt::kIdNone);
    TEST(iLastObserverHaltId == MsgHalt::kIdNone);

    // Start() then RemoveStream().  Check that audio ramps down then flushes.
    // Check that subsequent audio is discarded.
    // Check that subsequent stream plays.
    Print("\nRemoveStream\n");
    iNextGeneratedMsg = EMsgAudioPcm;
    iOkToPlay = ePlayYes;
    iStopper->Start();
    msg = iStopper->Pull()->Process(*this);
    if (msg != NULL) {
        msg->RemoveRef();
    }
    TEST(iLastMsg == EMsgAudioPcm);
    TEST(iStopper->iState == Stopper::ERunning);
    iStopper->RemoveCurrentStream();
    iJiffies = 0;
    iNextGeneratedMsg = EMsgAudioPcm;
    do {
        TEST(iStopper->iState == Stopper::EHalting);
        TEST(iStopper->iQueue.IsEmpty());
        msg = iStopper->Pull()->Process(*this);
        if (msg != NULL) {
            msg->RemoveRef();
        }
        TEST(iLastMsg == EMsgAudioPcm);
    } while(iJiffies < kRampDuration);
    TEST(iJiffies == kRampDuration);
    TEST(iStopper->iState == Stopper::EHaltPending);
    msg = iStopper->Pull()->Process(*this);
    msg->RemoveRef();
    TEST(iPipelineHaltedCount == pipelineHaltedCount);
    TEST(iStopper->iState == Stopper::ERunning);
    TEST(iLastMsg == EMsgHalt);
    iAudioMsgsDue = 5;
    iNextGeneratedMsg = EMsgEncodedStream;
    msg = iStopper->Pull()->Process(*this);
    if (msg != NULL) {
        msg->RemoveRef();
    }
    TEST(iLastMsg == EMsgDecodedStream); // EMsgDecodedStream due to test strangeness
    iNextGeneratedMsg = EMsgAudioPcm;
    TEST(iStopper->iState == Stopper::ERunning);

    // bug #231
    // BeginHalt.  Deliver more audio, checking it ramps down
    // RemoveCurrentStream().  Check that subsequent audio is discarded.
    Print("\nRemoveCurrentStream when halted\n");
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
    TEST(iPipelineHaltedCount == pipelineHaltedCount);
    msg = iStopper->Pull();
    (void)msg->Process(*this);
    msg->RemoveRef();
    TEST(iPipelineHaltedCount == ++pipelineHaltedCount);
    TEST(iStopper->iState == Stopper::EHalted);
    TEST(iLastMsg == EMsgHalt);
    iStopper->RemoveCurrentStream();
    iStopper->Start();
    iAudioMsgsDue = 5;
    iNextGeneratedMsg = EMsgEncodedStream;
    msg = iStopper->Pull()->Process(*this);
    if (msg != NULL) {
        msg->RemoveRef();
    }
    TEST(iLastMsg == EMsgDecodedStream); // EMsgDecodedStream due to test strangeness
    iNextGeneratedMsg = EMsgAudioPcm;
    TEST(iStopper->iState == Stopper::ERunning);
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
    if (iFlushMsgsDue > 0) {
        --iFlushMsgsDue;
        return iMsgFactory->CreateMsgFlush(1);
    }
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
        return iMsgFactory->CreateMsgDecodedStream(iStreamId, 0, 0, 0, 0, Brx::Empty(), 0, 0, false, false, false);
    case EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty(), NULL, false);
        Msg* msg = iMsgFactory->CreateMsgTrack(*track, iTrackId, Brx::Empty());
        track->RemoveRef();
        return msg;
    }
    case EMsgEncodedStream:
        /* Stopper consumes EncodedStream internally
           ...so we need to have another msg ready to be Pull()ed after this */
        iNextGeneratedMsg = EMsgDecodedStream;
        return iMsgFactory->CreateMsgEncodedStream(Brn("http://1.2.3.4:5"), Brn("metatext"), 0, 0, false, false, this);
    case EMsgMetaText:
        return iMsgFactory->CreateMsgMetaText(Brn("metatext"));
    case EMsgHalt:
        return iMsgFactory->CreateMsgHalt(iNextHaltId);
    case EMsgFlush:
        if (iFlush != NULL) {
            Msg* msg = iFlush;
            iFlush = NULL;
            return msg;
        }
        return iMsgFactory->CreateMsgFlush(1);
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
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 24, EMediaDataLittleEndian, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

TUint SuiteStopper::NextFlushId()
{
    return iNextFlushId++;
}

void SuiteStopper::PipelineHalted(TUint aHaltId)
{
    iPipelineHaltedCount++;
    iLastObserverHaltId = aHaltId;
}

EStreamPlay SuiteStopper::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    return iOkToPlay;
}

TUint SuiteStopper::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    return MsgFlush::kIdInvalid;
}

TUint SuiteStopper::TryStop(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    return MsgFlush::kIdInvalid;
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
    const TInt firstSubsample = (ptr[0]<<16) | (ptr[1]<<8) | ptr[2];
    const TUint bytes = buf.Bytes();
    const TInt lastSubsample = (ptr[bytes-3]<<16) | (ptr[bytes-2]<<8) | ptr[bytes-1];

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
    iLastHaltId = aMsg->Id();
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

void SuiteStopper::OutputTrack(Track& /*aTrack*/, TUint /*aTrackId*/, const Brx& /*aMode*/)
{
    ASSERTS();
}

void SuiteStopper::OutputStream(const Brx& /*aUri*/, TUint64 /*aTotalBytes*/, TBool /*aSeekable*/, TBool /*aLive*/, IStreamHandler& /*aStreamHandler*/, TUint /*aStreamId*/)
{
    ASSERTS();
}

void SuiteStopper::OutputData(const Brx& /*aData*/)
{
    ASSERTS();
}

void SuiteStopper::OutputMetadata(const Brx& /*aMetadata*/)
{
    ASSERTS();
}

void SuiteStopper::OutputFlush(TUint aFlushId)
{
    iFlush = iMsgFactory->CreateMsgFlush(aFlushId);
}

void SuiteStopper::OutputHalt(TUint /*aHaltId*/)
{
    ASSERTS();
}

void SuiteStopper::OutputQuit()
{
    ASSERTS();
}



void TestStopper()
{
    Runner runner("Stopper tests\n");
    runner.Add(new SuiteStopper());
    runner.Run();
}


