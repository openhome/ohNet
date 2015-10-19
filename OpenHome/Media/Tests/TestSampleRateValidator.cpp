#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Pipeline/SampleRateValidator.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Media/ClockPuller.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteSampleRateValidator : public SuiteUnitTest
                               , private IPipelineElementDownstream
                               , private IMsgProcessor
                               , private IPipelineAnimator
                               , private IStreamHandler
{
    static const TUint kBitrate = 256;
    static const TUint kSampleRate = 44100;
    static const TUint kChannels = 2;
    static const TUint kBitDepth = 16;
public:
    SuiteSampleRateValidator();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    enum EMsgType
    {
        EMsgNone
       ,EMsgMode
       ,EMsgTrack
       ,EMsgDrain
       ,EMsgEncodedStream
       ,EMsgDelay
       ,EMsgMetaText
       ,EMsgStreamInterrupted
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgDecodedStream
       ,EMsgBitRate
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgQuit
    };
private:
    void PushMsg(EMsgType aType);
    void StartStream();
private:
    void MsgsPassThrough();
    void SupportedRatePassesThrough();
    void UnsupportedRateStartsFlushing();
    void AudioNotPassedWhileFlushing();
    void MsgsPassWhileFlushing();
    void MsgsEndFlush();
    void ExpectedFlushConsumed();
private: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
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
private: // from IPipelineAnimator
    TUint PipelineDriverDelayJiffies(TUint aSampleRateFrom, TUint aSampleRateTo) override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    SampleRateValidator* iSampleRateValidator;
    EMsgType iLastMsg;
    TUint iNextStreamId;
    TByte iAudioData[884]; // 884 => 5ms @ 44.1, 16-bit, stereo
    TUint64 iTrackOffsetTx;
    TBool iRateSupported;
    TUint iExpectedFlushId;
};

} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;


SuiteSampleRateValidator::SuiteSampleRateValidator()
    : SuiteUnitTest("SampleRateValidator tests")
{
    AddTest(MakeFunctor(*this, &SuiteSampleRateValidator::MsgsPassThrough), "MsgsPassThrough");
    AddTest(MakeFunctor(*this, &SuiteSampleRateValidator::SupportedRatePassesThrough), "SupportedRatePassesThrough");
    AddTest(MakeFunctor(*this, &SuiteSampleRateValidator::UnsupportedRateStartsFlushing), "UnsupportedRateStartsFlushing");
    AddTest(MakeFunctor(*this, &SuiteSampleRateValidator::AudioNotPassedWhileFlushing), "AudioNotPassedWhileFlushing");
    AddTest(MakeFunctor(*this, &SuiteSampleRateValidator::MsgsPassWhileFlushing), "MsgsPassWhileFlushing");
    AddTest(MakeFunctor(*this, &SuiteSampleRateValidator::MsgsEndFlush), "MsgsEndFlush");
    AddTest(MakeFunctor(*this, &SuiteSampleRateValidator::ExpectedFlushConsumed), "ExpectedFlushConsumed");
}

void SuiteSampleRateValidator::Setup()
{
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(6, 5);
    init.SetMsgDecodedStreamCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 3);
    iSampleRateValidator = new SampleRateValidator(*this);
    iSampleRateValidator->SetAnimator(*this);
    iLastMsg = EMsgNone;
    iNextStreamId = 1;
    (void)memset(iAudioData, 0x7f, sizeof(iAudioData));
    iTrackOffsetTx = 0;
    iRateSupported = true;
    iExpectedFlushId = MsgFlush::kIdInvalid;
}

void SuiteSampleRateValidator::TearDown()
{
    delete iSampleRateValidator;
    delete iTrackFactory;
    delete iMsgFactory;
}

void SuiteSampleRateValidator::PushMsg(EMsgType aType)
{
    Msg* msg = nullptr;
    switch (aType)
    {
    case EMsgMode:
        msg = iMsgFactory->CreateMsgMode(Brn("dummyMode"), true, false, ModeClockPullers(), false, false);
        break;
    case EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
        msg = iMsgFactory->CreateMsgTrack(*track);
        track->RemoveRef();
    }
        break;
    case EMsgDrain:
        msg = iMsgFactory->CreateMsgDrain(Functor());
        break;
    case EMsgEncodedStream:
        msg = iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 0, 0, iNextStreamId, false, true, nullptr);
        break;
    case EMsgDelay:
        msg = iMsgFactory->CreateMsgDelay(Jiffies::kPerSecond);
        break;
    case EMsgMetaText:
        msg = iMsgFactory->CreateMsgMetaText(Brn("dummy metatext"));
        break;
    case EMsgStreamInterrupted:
        msg = iMsgFactory->CreateMsgStreamInterrupted();
        break;
    case EMsgHalt:
        msg = iMsgFactory->CreateMsgHalt();
        break;
    case EMsgFlush:
        msg = iMsgFactory->CreateMsgFlush(iExpectedFlushId);
        break;
    case EMsgWait:
        msg = iMsgFactory->CreateMsgWait();
        break;
    case EMsgDecodedStream:
        msg = iMsgFactory->CreateMsgDecodedStream(iNextStreamId++, kBitrate, kBitDepth, kSampleRate, kChannels, Brn("Dummy"), 0, 0, true, true, false, this);
        break;
    case EMsgBitRate:
        msg = iMsgFactory->CreateMsgBitRate(123);
        break;
    case EMsgAudioPcm:
    {
        Brn audioBuf(iAudioData, sizeof(iAudioData));
        MsgAudioPcm* msgPcm = iMsgFactory->CreateMsgAudioPcm(audioBuf, kChannels, kSampleRate, kBitDepth, EMediaDataEndianLittle, iTrackOffsetTx);
        iTrackOffsetTx += msgPcm->Jiffies();
        msg = msgPcm;
    }
        break;
    case EMsgSilence:
        msg = iMsgFactory->CreateMsgSilence(Jiffies::kPerMs * 4);
        break;
    case EMsgQuit:
        msg = iMsgFactory->CreateMsgQuit();
        break;
    case EMsgNone:
    default:
        ASSERTS();
        break;
    }
    static_cast<IPipelineElementDownstream*>(iSampleRateValidator)->Push(msg);
}

void SuiteSampleRateValidator::StartStream()
{
    EMsgType types[] = { EMsgMode, EMsgTrack, EMsgEncodedStream, EMsgDecodedStream };
    const size_t numElems = sizeof(types) / sizeof(types[0]);
    for (size_t i=0; i<numElems; i++) {
        PushMsg(types[i]);
    }
}

void SuiteSampleRateValidator::MsgsPassThrough()
{
    EMsgType types[] = { EMsgMode, EMsgTrack, EMsgDrain, EMsgEncodedStream, EMsgDelay,
                         EMsgMetaText, EMsgStreamInterrupted, EMsgHalt, EMsgFlush, EMsgWait, EMsgDecodedStream,
                         EMsgBitRate, EMsgAudioPcm, EMsgSilence, EMsgQuit };
    const size_t numElems = sizeof(types) / sizeof(types[0]);
    for (size_t i=0; i<numElems; i++) {
        PushMsg(types[i]);
        TEST(iLastMsg == types[i]);
    }
}

void SuiteSampleRateValidator::SupportedRatePassesThrough()
{
    iRateSupported = true;
    EMsgType types[] = { EMsgDecodedStream, EMsgAudioPcm, EMsgSilence };
    const size_t numElems = sizeof(types) / sizeof(types[0]);
    for (size_t i=0; i<numElems; i++) {
        PushMsg(types[i]);
        TEST(iLastMsg == types[i]);
    }
}

void SuiteSampleRateValidator::UnsupportedRateStartsFlushing()
{
    iRateSupported = false;
    PushMsg(EMsgDecodedStream);
    TEST(iLastMsg == EMsgNone);
    TEST(iSampleRateValidator->iFlushing);
}

void SuiteSampleRateValidator::AudioNotPassedWhileFlushing()
{
    iRateSupported = false;
    PushMsg(EMsgDecodedStream);
    TEST(iSampleRateValidator->iFlushing);
    PushMsg(EMsgAudioPcm);
    TEST(iLastMsg == EMsgNone);
    PushMsg(EMsgSilence);
    TEST(iLastMsg == EMsgNone);
}

void SuiteSampleRateValidator::MsgsPassWhileFlushing()
{
    iRateSupported = false;
    PushMsg(EMsgDecodedStream);
    TEST(iSampleRateValidator->iFlushing);
    EMsgType types[] = { EMsgEncodedStream, EMsgDelay, EMsgHalt, EMsgFlush, EMsgWait, EMsgQuit };
    const size_t numElems = sizeof(types) / sizeof(types[0]);
    for (size_t i=0; i<numElems; i++) {
        PushMsg(types[i]);
        TEST(iLastMsg == types[i]);
        TEST(iSampleRateValidator->iFlushing);
    }
}

void SuiteSampleRateValidator::MsgsEndFlush()
{
    iRateSupported = false;
    EMsgType types[] = { EMsgMode, EMsgTrack };
    const size_t numElems = sizeof(types) / sizeof(types[0]);
    for (size_t i=0; i<numElems; i++) {
        PushMsg(EMsgDecodedStream);
        TEST(iSampleRateValidator->iFlushing);
        PushMsg(types[i]);
        TEST(iLastMsg == types[i]);
        TEST(!iSampleRateValidator->iFlushing);
    }

    iLastMsg = EMsgNone;
    PushMsg(EMsgDecodedStream);
    TEST(iSampleRateValidator->iFlushing);
    TEST(iLastMsg == EMsgNone);
    iRateSupported = true;
    PushMsg(EMsgDecodedStream);
    TEST(!iSampleRateValidator->iFlushing);
    TEST(iLastMsg == EMsgDecodedStream);
}

void SuiteSampleRateValidator::ExpectedFlushConsumed()
{
    iRateSupported = false;
    PushMsg(EMsgDecodedStream);
    PushMsg(EMsgAudioPcm);
    TEST(iSampleRateValidator->iFlushing);
    TEST(iLastMsg == EMsgNone);
    PushMsg(EMsgFlush);
    TEST(iSampleRateValidator->iFlushing);
    TEST(iLastMsg == EMsgFlush);
    iExpectedFlushId = 42;
    iLastMsg = EMsgNone;
    PushMsg(EMsgFlush);
    TEST(iSampleRateValidator->iFlushing);
    TEST(iLastMsg == EMsgFlush);
}

void SuiteSampleRateValidator::Push(Msg* aMsg)
{
    aMsg = aMsg->Process(*this);
    aMsg->RemoveRef();
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgMode* aMsg)
{
    iLastMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgTrack* aMsg)
{
    iLastMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgDrain* aMsg)
{
    iLastMsg = EMsgDrain;
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgDelay* aMsg)
{
    iLastMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastMsg = EMsgEncodedStream;
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgAudioEncoded* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgMetaText* aMsg)
{
    iLastMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgHalt* aMsg)
{
    iLastMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgFlush* aMsg)
{
    iLastMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgWait* aMsg)
{
    iLastMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgBitRate* aMsg)
{
    iLastMsg = EMsgBitRate;
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastMsg = EMsgAudioPcm;
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgSilence* aMsg)
{
    iLastMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgPlayable* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* SuiteSampleRateValidator::ProcessMsg(MsgQuit* aMsg)
{
    iLastMsg = EMsgQuit;
    return aMsg;
}

TUint SuiteSampleRateValidator::PipelineDriverDelayJiffies(TUint aSampleRateFrom, TUint /*aSampleRateTo*/)
{
    ASSERT(aSampleRateFrom == 0);
    if (!iRateSupported) {
        THROW(SampleRateUnsupported);
    }
    return 0;
}

EStreamPlay SuiteSampleRateValidator::OkToPlay(TUint /*aStreamId*/)
{
    return ePlayNo;
}

TUint SuiteSampleRateValidator::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteSampleRateValidator::TryStop(TUint /*aStreamId*/)
{
    return iExpectedFlushId;
}

void SuiteSampleRateValidator::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/, TBool /*aStarving*/)
{
    ASSERTS();
}



void TestSampleRateValidator()
{
    Runner runner("SampleRateValidator tests\n");
    runner.Add(new SuiteSampleRateValidator());
    runner.Run();
}
