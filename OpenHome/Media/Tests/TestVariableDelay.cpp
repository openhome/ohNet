#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/VariableDelay.h>
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

class SuiteVariableDelay : public Suite, public IPipelineElementUpstream, private IMsgProcessor
{
    static const TUint kDecodedAudioCount = 2;
    static const TUint kMsgAudioPcmCount  = 2;
    static const TUint kMsgSilenceCount   = 1;

    static const TUint kRampDuration = Jiffies::kJiffiesPerMs * 50;
    static const TUint kDelay1       = Jiffies::kJiffiesPerMs * 500;
    static const TUint kDelay2       = Jiffies::kJiffiesPerMs * 300;

    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
public:
    SuiteVariableDelay();
    ~SuiteVariableDelay();
    void Test();
public: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgTrack* aMsg);
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
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgDecodedStream
       ,EMsgTrack
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgQuit
    };
private:
    MsgAudio* CreateAudio();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    VariableDelay* iVariableDelay;
    EMsgType iNextGeneratedMsg;
    EMsgType iLastMsg;
    TUint iJiffies;
    TUint iNumMsgsGenerated;
    TUint iAudioMsgSizeJiffies;
    TUint64 iTrackOffset;
    TByte iBuf[DecodedAudio::kMaxBytes];
};

} // namespace Media
} // namespace OpenHome


// SuiteVariableDelay

SuiteVariableDelay::SuiteVariableDelay()
    : Suite("Variable delay tests")
    , iLastMsg(ENone)
    , iNumMsgsGenerated(0)
    , iAudioMsgSizeJiffies(0)
    , iTrackOffset(0)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, kDecodedAudioCount, kMsgAudioPcmCount, kMsgSilenceCount, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iVariableDelay = new VariableDelay(*iMsgFactory, *this, kRampDuration);
}

SuiteVariableDelay::~SuiteVariableDelay()
{
    delete iVariableDelay;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteVariableDelay::Test()
{
    /*
    Test goes something like
        Add single 0xff filled audio.  Check it can be Pull()ed without ramping.
        Set a delay.  Check audio ramps down, 'delay' jiffies of silence is delivered, audio ramps up.  Check duration of ramps.
        Check that next audio msg is delivered unaltered.
        Check that Silence, Track, MetaText, Halt, Flush & Quit msgs are passed through.
        Reduce delay.  Check audio ramps down then count number of jiffies audio discarded.  Check audio then ramps up.
    */

    // Add single 0xff filled audio.  Check it can be Pull()ed without ramping.
    TEST(iVariableDelay->iStatus == VariableDelay::ERunning);
    iNextGeneratedMsg = EMsgAudioPcm;
    iJiffies = kRampDuration;
    Msg* msg = iVariableDelay->Pull();
    msg = msg->Process(*this);
    ASSERT(msg == NULL);
    TEST(iLastMsg == EMsgAudioPcm);
    TEST(iVariableDelay->iStatus == VariableDelay::ERunning);

    // Set a delay.  Check audio ramps down, 'delay' jiffies of silence is delivered, audio ramps up.  Check duration of ramps.
    iJiffies = 0;
    iVariableDelay->AdjustDelay(kDelay1);
    TEST(iVariableDelay->iStatus == VariableDelay::ERampingDown);
    do {
        msg = iVariableDelay->Pull();
        msg = msg->Process(*this);
        ASSERT(msg == NULL);
        TEST(iLastMsg == EMsgAudioPcm);
    } while (iVariableDelay->iStatus == VariableDelay::ERampingDown);
    TEST(iJiffies == kRampDuration);
    iJiffies = 0;
    do {
        msg = iVariableDelay->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
        TEST(iLastMsg == EMsgSilence);
    } while (iVariableDelay->iStatus == VariableDelay::ERampedDown);
    TEST(iJiffies == kDelay1);
    iJiffies = 0;
    do {
        msg = iVariableDelay->Pull();
        msg = msg->Process(*this);
        ASSERT(msg == NULL);
        TEST(iLastMsg == EMsgAudioPcm);
    } while (iVariableDelay->iStatus == VariableDelay::ERampingUp);
    TEST(iJiffies == kRampDuration);
    TEST(iVariableDelay->iStatus == VariableDelay::ERunning);

    // Check that next audio msg is delivered unaltered.
    msg = iVariableDelay->Pull();
    msg = msg->Process(*this);
    ASSERT(msg == NULL);
    TEST(iLastMsg == EMsgAudioPcm);
    TEST(iVariableDelay->iStatus == VariableDelay::ERunning);

    // Check that Silence, Track, AudioStream, MetaText, Halt, Flush, Wait & Quit msgs are passed through.
    EMsgType types[] = { EMsgSilence, EMsgDecodedStream, EMsgTrack, EMsgEncodedStream, EMsgMetaText, EMsgHalt, EMsgFlush, EMsgWait, EMsgQuit };
    for (TUint i=0; i<sizeof(types)/sizeof(types[0]); i++) {
        iNextGeneratedMsg = types[i];
        msg = iVariableDelay->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
        TEST(iLastMsg == types[i]);
        TEST(iVariableDelay->iStatus == VariableDelay::ERunning);
    }

    // Reduce delay.  Check audio ramps down then count number of jiffies audio discarded.  Check audio then ramps up.
    TEST(iVariableDelay->iQueue.IsEmpty());
    iJiffies = 0;
    iNextGeneratedMsg = EMsgAudioPcm;
    iVariableDelay->AdjustDelay(kDelay2);
    TEST(iVariableDelay->iStatus == VariableDelay::ERampingDown);
    do {
        msg = iVariableDelay->Pull();
        msg = msg->Process(*this);
        ASSERT(msg == NULL);
        TEST(iLastMsg == EMsgAudioPcm);
    } while (iVariableDelay->iStatus == VariableDelay::ERampingDown);
    TEST(iJiffies == kRampDuration);
    if (kRampDuration % iAudioMsgSizeJiffies == 0) {
        TEST(iVariableDelay->iQueue.IsEmpty());
    }
    else {
        TEST(!iVariableDelay->iQueue.IsEmpty());
    }
    TEST(iVariableDelay->iStatus == VariableDelay::ERampedDown);
    iJiffies = 0;
    TUint numMsgsGenerated = iNumMsgsGenerated;
    msg = iVariableDelay->Pull();
    msg = msg->Process(*this);
    ASSERT(msg == NULL);
    TEST(iVariableDelay->iStatus == VariableDelay::ERampingUp);
    TEST((kDelay1 - kDelay2) == ((iNumMsgsGenerated - numMsgsGenerated) * iAudioMsgSizeJiffies) + (iAudioMsgSizeJiffies - iJiffies) - (kRampDuration % iAudioMsgSizeJiffies));
    do {
        msg = iVariableDelay->Pull();
        msg = msg->Process(*this);
        ASSERT(msg == NULL);
        TEST(iLastMsg == EMsgAudioPcm);
    } while (iVariableDelay->iStatus == VariableDelay::ERampingUp);
    TEST(iJiffies == kRampDuration);
    TEST(iVariableDelay->iStatus == VariableDelay::ERunning);
}

Msg* SuiteVariableDelay::Pull()
{
    iNumMsgsGenerated++;
    switch (iNextGeneratedMsg)
    {
    case EMsgAudioPcm:
        return CreateAudio();
    case EMsgSilence:
        return iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs);
    case EMsgDecodedStream:
        return iMsgFactory->CreateMsgDecodedStream(0, 0, 0, 0, 0, Brx::Empty(), 0, 0, false, false, false);
    case EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty(), NULL, false);
        Msg* msg = iMsgFactory->CreateMsgTrack(*track, 0, Brx::Empty());
        track->RemoveRef();
        return msg;
    }
    case EMsgEncodedStream:
        return iMsgFactory->CreateMsgEncodedStream(Brn("http://1.2.3.4:5"), Brn("metatext"), 0, 0, false, false, NULL);
    case EMsgMetaText:
        return iMsgFactory->CreateMsgMetaText(Brn("metatext"));
    case EMsgHalt:
        return iMsgFactory->CreateMsgHalt();
    case EMsgFlush:
        return iMsgFactory->CreateMsgFlush(1);
    case EMsgWait:
        return iMsgFactory->CreateMsgWait();
    case EMsgQuit:
        return iMsgFactory->CreateMsgQuit();
    default:
        ASSERTS();
        return NULL;
    }
}

MsgAudio* SuiteVariableDelay::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0x7f, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 16, EMediaDataLittleEndian, iTrackOffset);
    iAudioMsgSizeJiffies = audio->Jiffies();
    iTrackOffset += iAudioMsgSizeJiffies;
    return audio;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgTrack* aMsg)
{
    iLastMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastMsg = EMsgEncodedStream;
    return aMsg;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return NULL;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgMetaText* aMsg)
{
    iLastMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgHalt* aMsg)
{
    iLastMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgFlush* aMsg)
{
    iLastMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgWait* aMsg)
{
    iLastMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgAudioPcm* aMsg)
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

    switch (iVariableDelay->iStatus)
    {
    case VariableDelay::ERampingDown:
        TEST(firstSubsample > lastSubsample);
        break;
    case VariableDelay::ERampingUp:
        TEST(firstSubsample < lastSubsample);
        break;
    case VariableDelay::ERampedDown:
        break;
    case VariableDelay::ERunning:
        if (iJiffies >= kRampDuration) {
            TEST(firstSubsample == lastSubsample);
        }
        break;
    }
    iJiffies += jiffies;
    return NULL;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgSilence* aMsg)
{
    iLastMsg = EMsgSilence;
    iJiffies += aMsg->Jiffies();
    return aMsg;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // MsgPlayable not expected at this stage of the pipeline
    return NULL;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgQuit* aMsg)
{
    iLastMsg = EMsgQuit;
    return aMsg;
}



void TestVariableDelay()
{
    Runner runner("Variable delay tests\n");
    runner.Add(new SuiteVariableDelay());
    runner.Run();
}


