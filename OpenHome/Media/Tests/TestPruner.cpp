#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Pipeline/Pruner.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Functor.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuitePruner : public SuiteUnitTest, private IPipelineElementUpstream, private IMsgProcessor
{
public:
    SuitePruner();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    enum EMsgType
    {
        ENone
       ,EMsgMode
       ,EMsgTrack
       ,EMsgDrain
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgAudioEncoded
       ,EMsgMetaText
       ,EMsgStreamInterrupted
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgDecodedStream
       ,EMsgBitRate
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgQuit
    };
private:
    EMsgType DoPull();
    void MsgsDiscarded();
    void QuitDoesntWaitForAudio();
    void HaltPassedOn();
    void DrainPassedOn();
    void StreamInterruptedPassedOn();
    void DecodedStreamPassedOn();
    void TrackWithoutAudioAllMsgsDiscarded();
    void SilenceUnblocksStreamMsgs();
    void ModeWithoutAudioAllMsgsDiscarded();
    void StreamWithoutAudioAllMsgsDiscarded();
    void HaltWithoutAudioDiscarded();
private: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // IMsgProcessor
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
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    Pruner* iPruner;
    EMsgType iLastPulledMsg;
    TUint iPulledTrackId;
    std::vector<EMsgType> iPendingMsgs;
};

} // namespace Media
} // namespace OpenHome

// SuitePruner

SuitePruner::SuitePruner()
    : SuiteUnitTest("Pruner tests")
{
    AddTest(MakeFunctor(*this, &SuitePruner::MsgsDiscarded), "MsgsDiscarded");
    AddTest(MakeFunctor(*this, &SuitePruner::QuitDoesntWaitForAudio), "QuitDoesntWaitForAudio");
    AddTest(MakeFunctor(*this, &SuitePruner::HaltPassedOn), "HaltPassedOn");
    AddTest(MakeFunctor(*this, &SuitePruner::DrainPassedOn), "DrainPassedOn");
    AddTest(MakeFunctor(*this, &SuitePruner::StreamInterruptedPassedOn), "StreamInterruptedPassedOn");
    AddTest(MakeFunctor(*this, &SuitePruner::DecodedStreamPassedOn), "DecodedStreamPassedOn");
    AddTest(MakeFunctor(*this, &SuitePruner::TrackWithoutAudioAllMsgsDiscarded), "TrackWithoutAudioAllMsgsDiscarded");
    AddTest(MakeFunctor(*this, &SuitePruner::SilenceUnblocksStreamMsgs), "SilenceUnblocksStreamMsgs");
    AddTest(MakeFunctor(*this, &SuitePruner::ModeWithoutAudioAllMsgsDiscarded), "ModeWithoutAudioAllMsgsDiscarded");
    AddTest(MakeFunctor(*this, &SuitePruner::StreamWithoutAudioAllMsgsDiscarded), "StreamWithoutAudioAllMsgsDiscarded");
    AddTest(MakeFunctor(*this, &SuitePruner::HaltWithoutAudioDiscarded), "HaltWithoutAudioDiscarded");
}

void SuitePruner::Setup()
{
    MsgFactoryInitParams init;
    init.SetMsgDecodedStreamCount(3);
    init.SetMsgTrackCount(3);
    init.SetMsgHaltCount(4);
    init.SetMsgModeCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 3);
    iPruner = new Pruner(*this);
    iPulledTrackId = UINT_MAX/2;
}

void SuitePruner::TearDown()
{
    delete iPruner;
    delete iMsgFactory;
    delete iTrackFactory;
}

SuitePruner::EMsgType SuitePruner::DoPull()
{
    Msg* msg = iPruner->Pull();
    msg = msg->Process(*this);
    if (msg != nullptr) {
        msg->RemoveRef();
    }
    return iLastPulledMsg;
}

#define NUM_EMEMS(arr) sizeof(arr) / sizeof(arr[0])

void SuitePruner::MsgsDiscarded()
{
    EMsgType msgs[] = { EMsgMode, EMsgTrack, EMsgDelay, EMsgDecodedStream, EMsgMetaText, EMsgWait, EMsgBitRate, EMsgAudioPcm };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    TEST(DoPull() == EMsgMode);
    TEST(DoPull() == EMsgDecodedStream);
    TEST(DoPull() == EMsgAudioPcm);
    TEST(iPendingMsgs.size() == 0);
}

void SuitePruner::QuitDoesntWaitForAudio()
{
    EMsgType msgs[] = { EMsgTrack, EMsgQuit };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    TEST(DoPull() == EMsgQuit);
    TEST(iPendingMsgs.size() == 0);
}

void SuitePruner::HaltPassedOn()
{
    EMsgType msgs[] = { EMsgTrack, EMsgDecodedStream, EMsgHalt };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    TEST(DoPull() == EMsgDecodedStream);
    TEST(DoPull() == EMsgHalt);
}

void SuitePruner::DrainPassedOn()
{
    EMsgType msgs[] ={ EMsgTrack, EMsgDrain };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    TEST(DoPull() == EMsgDrain);
    TEST(iPendingMsgs.size() == 0);
}

void SuitePruner::StreamInterruptedPassedOn()
{
    EMsgType msgs[] ={ EMsgTrack, EMsgDecodedStream, EMsgAudioPcm, EMsgStreamInterrupted };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    TEST(DoPull() == EMsgDecodedStream);
    TEST(DoPull() == EMsgAudioPcm);
    TEST(DoPull() == EMsgStreamInterrupted);
}

void SuitePruner::DecodedStreamPassedOn()
{
    EMsgType msgs[] = { EMsgDecodedStream, EMsgAudioPcm };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    TEST(DoPull() == EMsgDecodedStream);
    TEST(iPendingMsgs.size() == 0);
    TEST(DoPull() == EMsgAudioPcm);
}

void SuitePruner::TrackWithoutAudioAllMsgsDiscarded()
{
    EMsgType msgs[] = { EMsgMode, EMsgTrack, EMsgDecodedStream, EMsgTrack, EMsgDecodedStream, EMsgAudioPcm };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    TEST(DoPull() == EMsgMode);
    TEST(DoPull() == EMsgDecodedStream);
    TEST(DoPull() == EMsgAudioPcm);
    TEST(iPendingMsgs.size() == 0);
}

void SuitePruner::SilenceUnblocksStreamMsgs()
{
    EMsgType msgs[] = { EMsgTrack, EMsgDecodedStream, EMsgSilence };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    TEST(DoPull() == EMsgDecodedStream);
    TEST(DoPull() == EMsgSilence);
    TEST(iPendingMsgs.size() == 0);
}

void SuitePruner::ModeWithoutAudioAllMsgsDiscarded()
{
    EMsgType msgs[] = { EMsgMode, EMsgTrack, EMsgDecodedStream, EMsgTrack, EMsgDecodedStream,
                        EMsgMode, EMsgTrack, EMsgDecodedStream, EMsgAudioPcm };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    TEST(DoPull() == EMsgMode);
    TEST(DoPull() == EMsgDecodedStream);
    TEST(DoPull() == EMsgAudioPcm);
    TEST(iPendingMsgs.size() == 0);
}

void SuitePruner::StreamWithoutAudioAllMsgsDiscarded()
{
    EMsgType msgs[] ={ EMsgMode, EMsgTrack, EMsgDecodedStream, EMsgDecodedStream, EMsgAudioPcm };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    TEST(DoPull() == EMsgMode);
    TEST(DoPull() == EMsgDecodedStream);
    TEST(DoPull() == EMsgAudioPcm);
    TEST(iPendingMsgs.size() == 0);
}

void SuitePruner::HaltWithoutAudioDiscarded()
{
    EMsgType msgs[] = { EMsgMode, EMsgTrack, EMsgDecodedStream, EMsgAudioPcm, EMsgHalt,
                        EMsgTrack, EMsgHalt,
                        EMsgTrack, EMsgDecodedStream, EMsgHalt,
                        EMsgDecodedStream, EMsgAudioPcm, EMsgHalt, EMsgAudioPcm, EMsgHalt };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));

    TEST(DoPull() == EMsgMode);
    TEST(DoPull() == EMsgDecodedStream);
    TEST(DoPull() == EMsgAudioPcm);
    TEST(DoPull() == EMsgHalt);
    TEST(DoPull() == EMsgDecodedStream);
    TEST(DoPull() == EMsgAudioPcm);
    TEST(DoPull() == EMsgHalt);
    TEST(DoPull() == EMsgAudioPcm);
    TEST(DoPull() == EMsgHalt);
}

Msg* SuitePruner::ProcessMsg(MsgMode* aMsg)
{
    iLastPulledMsg = EMsgMode;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgTrack* aMsg)
{
    iPulledTrackId = aMsg->Track().Id();
    iLastPulledMsg = EMsgTrack;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgDrain* aMsg)
{
    iLastPulledMsg = EMsgDrain;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgDelay* aMsg)
{
    iLastPulledMsg = EMsgDelay;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastPulledMsg = EMsgEncodedStream;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iLastPulledMsg = EMsgAudioEncoded;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgMetaText* aMsg)
{
    iLastPulledMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastPulledMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgHalt* aMsg)
{
    iLastPulledMsg = EMsgHalt;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgFlush* aMsg)
{
    iLastPulledMsg = EMsgFlush;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgWait* aMsg)
{
    iLastPulledMsg = EMsgWait;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastPulledMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgBitRate* aMsg)
{
    iLastPulledMsg = EMsgBitRate;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastPulledMsg = EMsgAudioPcm;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgSilence* aMsg)
{
    iLastPulledMsg = EMsgSilence;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgPlayable* aMsg)
{
    iLastPulledMsg = EMsgPlayable;
    return aMsg;
}

Msg* SuitePruner::ProcessMsg(MsgQuit* aMsg)
{
    iLastPulledMsg = EMsgQuit;
    return aMsg;
}

Msg* SuitePruner::Pull()
{
    static const TUint kStreamId      = 0;
    static const TUint kBitDepth      = 24;
    static const TUint kSampleRate    = 44100;
    static const TUint kBitRate       = kBitDepth * kSampleRate;
    static const TUint64 kTrackLength = Jiffies::kPerSecond * 60;
    static const TBool kLossless      = true;
    static const TBool kSeekable      = false;
    static const TBool kLive          = false;
    static const TUint kNumChannels   = 2;
    static TUint64 iTrackOffset = 0;

    EMsgType msgType = iPendingMsgs[0];
    iPendingMsgs.erase(iPendingMsgs.begin());
    switch (msgType)
    {
    case EMsgMode:
        return iMsgFactory->CreateMsgMode(Brx::Empty(), true, ModeClockPullers(), false, false);
    case EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
        Msg* msg = iMsgFactory->CreateMsgTrack(*track);
        track->RemoveRef();
        return msg;
    }
    case EMsgDrain:
        return iMsgFactory->CreateMsgDrain(Functor());
    case EMsgDelay:
        return iMsgFactory->CreateMsgDelay(0);
    case EMsgEncodedStream:
    {
        return iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), UINT_MAX/4, 0, kStreamId, kSeekable, kLive, nullptr);
    }
    case EMsgMetaText:
    {
        return iMsgFactory->CreateMsgMetaText(Brn("dummy metatext"));
    }
    case EMsgStreamInterrupted:
        return iMsgFactory->CreateMsgStreamInterrupted();
    case EMsgHalt:
        return iMsgFactory->CreateMsgHalt();
    case EMsgWait:
        return iMsgFactory->CreateMsgWait();
    case EMsgDecodedStream:
        return iMsgFactory->CreateMsgDecodedStream(kStreamId, kBitRate, kBitDepth, kSampleRate, kNumChannels, Brn("Dummy codec"), kTrackLength, 0, kLossless, kSeekable, kLive, false, nullptr);
    case EMsgBitRate:
        return iMsgFactory->CreateMsgBitRate(kBitRate + 1000);
    case EMsgAudioPcm:
    {
        static const TUint kDataBytes = 3 * 1024;
        TByte encodedAudioData[kDataBytes];
        (void)memset(encodedAudioData, 0xff, kDataBytes);
        Brn encodedAudioBuf(encodedAudioData, kDataBytes);
        MsgAudio* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 16, AudioDataEndian::Little, iTrackOffset);
        iTrackOffset += audio->Jiffies();
        return audio;
    }
    case EMsgSilence:
    {
        TUint size = Jiffies::kPerMs * 5;
        return iMsgFactory->CreateMsgSilence(size, kSampleRate, 16, kNumChannels);
    }
    case EMsgQuit:
        return iMsgFactory->CreateMsgQuit();
    case EMsgAudioEncoded:
    case EMsgFlush:
    case EMsgPlayable:
    default:
        ASSERTS();
        return nullptr;
    }
}



void TestPruner()
{
    Runner runner("Pruner tests\n");
    runner.Add(new SuitePruner());
    runner.Run();
}
