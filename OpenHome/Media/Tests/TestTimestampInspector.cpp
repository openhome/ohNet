#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Pipeline/TimestampInspector.h>
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

class NullClockPullerTimestamp : public IClockPullerTimestamp
{
private: // from IClockPullerTimestamp
    void NewStream(TUint aSampleRate) override;
    void Reset() override;
    void Stop() override;
    void Start() override;
    TUint NotifyTimestamp(TInt aDrift, TUint aNetwork) override;
};

class SuiteTimestampInspector : public SuiteUnitTest, private IPipelineElementDownstream, private IMsgProcessor
{
    static const TUint kBitrate = 256;
    static const TUint kSampleRate = 44100;
    static const TUint kChannels = 2;
    static const TUint kBitDepth = 16;
    static const TUint kTimestampIncrement = 128;
public:
    SuiteTimestampInspector();
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
       ,EMsgQuit
    };
private:
    void PushMsg(EMsgType aType);
    void StartStream();
private:
    void NonAudioMsgsPassThrough();
    void NonTimestampedAudioPassesThrough();
    void TimestampedAudioLocks();
    void TimestampedAudioWithoutClockPullerPassesThrough();
    void NonTimestampedMsgWhileLocking();
    void TimestampVariationRestartsLocking();
    void NonTimestampedMsgAtStartOfLocking();
    void NewDecodedStreamIfAudioDiscarded();
    void NewStreamWhileLocking();
    void InterruptedStreamRestartsLocking();
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
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    TimestampInspector* iTimestampInspector;
    EMsgType iLastMsg;
    TUint iMsgTxCount;
    TUint iMsgRxCount;
    TUint iMsgAudioRxCount;
    TUint iNextStreamId;
    TByte iAudioData[884]; // 884 => 5ms @ 44.1, 16-bit, stereo
    TUint64 iTrackOffsetTx;
    TUint64 iTrackOffsetRx;
    NullClockPullerTimestamp iClockPuller;
    TBool iTimestampNextAudioMsg;
    TBool iUseClockPuller;
    TUint iNextNetworkTimestamp;
    TUint iNextRxTimestamp;
};

} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;


void NullClockPullerTimestamp::NewStream(TUint /*aSampleRate*/)
{
}
void NullClockPullerTimestamp::Reset()
{
}
void NullClockPullerTimestamp::Stop()
{
}
void NullClockPullerTimestamp::Start()
{
}
TUint NullClockPullerTimestamp::NotifyTimestamp(TInt /*aDrift*/, TUint /*aNetwork*/)
{
    return IPullableClock::kNominalFreq;
}


SuiteTimestampInspector::SuiteTimestampInspector()
    : SuiteUnitTest("TimestampInspector tests")
{
    AddTest(MakeFunctor(*this, &SuiteTimestampInspector::NonAudioMsgsPassThrough), "NonAudioMsgsPassThrough");
    AddTest(MakeFunctor(*this, &SuiteTimestampInspector::NonTimestampedAudioPassesThrough), "NonTimestampedAudioPassesThrough");
    AddTest(MakeFunctor(*this, &SuiteTimestampInspector::TimestampedAudioLocks), "TimestampedAudioLocks");
    AddTest(MakeFunctor(*this, &SuiteTimestampInspector::TimestampedAudioWithoutClockPullerPassesThrough), "TimestampedAudioWithoutClockPullerPassesThrough");
    AddTest(MakeFunctor(*this, &SuiteTimestampInspector::NonTimestampedMsgWhileLocking), "NonTimestampedMsgWhileLocking");
    AddTest(MakeFunctor(*this, &SuiteTimestampInspector::TimestampVariationRestartsLocking), "TimestampVariationRestartsLocking");
    AddTest(MakeFunctor(*this, &SuiteTimestampInspector::NonTimestampedMsgAtStartOfLocking), "NonTimestampedMsgAtStartOfLocking");
    AddTest(MakeFunctor(*this, &SuiteTimestampInspector::NewDecodedStreamIfAudioDiscarded), "NewDecodedStreamIfAudioDiscarded");
    AddTest(MakeFunctor(*this, &SuiteTimestampInspector::NewStreamWhileLocking), "NewStreamWhileLocking");
    AddTest(MakeFunctor(*this, &SuiteTimestampInspector::InterruptedStreamRestartsLocking), "InterruptedStreamRestartsLocking");
}

void SuiteTimestampInspector::Setup()
{
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(6, 5);
    init.SetMsgDecodedStreamCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 3);
    iTimestampInspector = new TimestampInspector(*iMsgFactory, *this);
    iLastMsg = EMsgNone;
    iMsgTxCount = iMsgRxCount = iMsgAudioRxCount= 0;
    iNextStreamId = 1;
    (void)memset(iAudioData, 0x7f, sizeof(iAudioData));
    iTrackOffsetTx = iTrackOffsetRx = 0;
    iTimestampNextAudioMsg = false;
    iUseClockPuller = true;
    iNextNetworkTimestamp = 0x40000;
    iNextRxTimestamp = 0x100;
}

void SuiteTimestampInspector::TearDown()
{
    delete iTimestampInspector;
    delete iTrackFactory;
    delete iMsgFactory;
}

void SuiteTimestampInspector::PushMsg(EMsgType aType)
{
    Msg* msg = nullptr;
    switch (aType)
    {
    case EMsgMode:
    {
        ModeClockPullers clockPullers(nullptr, nullptr, iUseClockPuller? &iClockPuller : nullptr);
        msg = iMsgFactory->CreateMsgMode(Brn("dummyMode"), true, false, clockPullers, false, false);
    }
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
        msg = iMsgFactory->CreateMsgFlush(1);
        break;
    case EMsgWait:
        msg = iMsgFactory->CreateMsgWait();
        break;
    case EMsgDecodedStream:
        msg = iMsgFactory->CreateMsgDecodedStream(iNextStreamId++, kBitrate, kBitDepth, kSampleRate, kChannels, Brn("Dummy"), 0, 0, true, true, false, false, nullptr);
        break;
    case EMsgBitRate:
        msg = iMsgFactory->CreateMsgBitRate(200);
        break;
    case EMsgAudioPcm:
    {
        Brn audioBuf(iAudioData, sizeof(iAudioData));
        MsgAudioPcm* msgPcm;
        if (!iTimestampNextAudioMsg) {
            msgPcm = iMsgFactory->CreateMsgAudioPcm(audioBuf, kChannels, kSampleRate, kBitDepth, EMediaDataEndianLittle, iTrackOffsetTx);
        }
        else {
            msgPcm = iMsgFactory->CreateMsgAudioPcm(audioBuf, kChannels, kSampleRate, kBitDepth, EMediaDataEndianLittle, iTrackOffsetTx, iNextRxTimestamp, iNextNetworkTimestamp);
            iNextRxTimestamp += kTimestampIncrement;
            iNextNetworkTimestamp += kTimestampIncrement;
        }
        iTrackOffsetTx += msgPcm->Jiffies();
        msg = msgPcm;
    }
        break;
    case EMsgQuit:
        msg = iMsgFactory->CreateMsgQuit();
        break;
    case EMsgNone:
    default:
        ASSERTS();
        break;
    }
    iMsgTxCount++;
    static_cast<IPipelineElementDownstream*>(iTimestampInspector)->Push(msg);
}

void SuiteTimestampInspector::StartStream()
{
    EMsgType types[] = { EMsgMode, EMsgTrack, EMsgEncodedStream, EMsgDecodedStream };
    const size_t numElems = sizeof(types) / sizeof(types[0]);
    for (size_t i=0; i<numElems; i++) {
        PushMsg(types[i]);
    }
}

void SuiteTimestampInspector::NonAudioMsgsPassThrough()
{
    EMsgType types[] = { EMsgMode, EMsgTrack, EMsgDrain, EMsgEncodedStream, EMsgDelay,
                         EMsgMetaText, EMsgStreamInterrupted, EMsgHalt, EMsgFlush, EMsgWait, EMsgDecodedStream,
                         EMsgBitRate, EMsgQuit };
    const size_t numElems = sizeof(types) / sizeof(types[0]);
    TUint prevTxCount = iMsgTxCount;
    for (size_t i=0; i<numElems; i++) {
        PushMsg(types[i]);
        TEST(iLastMsg == types[i]);
        TEST(iMsgTxCount == iMsgRxCount);
        TEST(iMsgTxCount == prevTxCount + 1);
        prevTxCount = iMsgTxCount;
    }
}

void SuiteTimestampInspector::NonTimestampedAudioPassesThrough()
{
    StartStream();
    TUint prevTxCount = iMsgTxCount;
    TEST(iMsgTxCount == iMsgRxCount);
    PushMsg(EMsgAudioPcm);
    TEST(iMsgTxCount == prevTxCount + 1);
    TEST(iMsgTxCount == iMsgRxCount);
}

void SuiteTimestampInspector::TimestampedAudioLocks()
{
    StartStream();
    iTimestampNextAudioMsg = true;
    TUint prevTxCount = iMsgTxCount;
    TUint count = 0;
    while (!iTimestampInspector->iLockedToStream) {
        TEST(prevTxCount == iMsgRxCount);
        PushMsg(EMsgAudioPcm);
        count++;
    }
    TEST(iMsgAudioRxCount == 0);
    TEST(count == iTimestampInspector->kLockingMsgCount);
    PushMsg(EMsgAudioPcm);
    TEST(iMsgAudioRxCount == 1);
}

void SuiteTimestampInspector::TimestampedAudioWithoutClockPullerPassesThrough()
{
    iTimestampNextAudioMsg = true;
    iUseClockPuller = false;
    StartStream();
    TUint prevTxCount = iMsgTxCount;
    PushMsg(EMsgAudioPcm);
    TEST(iMsgTxCount == prevTxCount + 1);
    TEST(iMsgTxCount == iMsgRxCount);
}

void SuiteTimestampInspector::NonTimestampedMsgWhileLocking()
{
    StartStream();
    iTimestampNextAudioMsg = true;
    TUint prevTxCount = iMsgTxCount;
    TUint count = 0;
    while (!iTimestampInspector->iLockedToStream) {
        TEST(prevTxCount == iMsgRxCount);
        PushMsg(EMsgAudioPcm);
        count++;
        iTimestampNextAudioMsg = (count != 1);
    }
    TEST(iMsgAudioRxCount == 0);
    TEST(count == iTimestampInspector->kLockingMsgCount + 1);
    PushMsg(EMsgAudioPcm);
    TEST(iMsgAudioRxCount == 1);
}

void SuiteTimestampInspector::TimestampVariationRestartsLocking()
{
    StartStream();
    iTimestampNextAudioMsg = true;
    TUint prevTxCount = iMsgTxCount;
    TUint count = 0;
    while (!iTimestampInspector->iLockedToStream) {
        TEST(prevTxCount == iMsgRxCount);
        PushMsg(EMsgAudioPcm);
        if (++count == 2) {
            iNextNetworkTimestamp += Jiffies::kPerMs;
        }
    }
    TEST(iMsgAudioRxCount == 0);
    TEST(count == iTimestampInspector->kLockingMsgCount + 3); // 3 discarded msgs
    PushMsg(EMsgAudioPcm);
    TEST(iMsgAudioRxCount == 1);
}

void SuiteTimestampInspector::NonTimestampedMsgAtStartOfLocking()
{
    StartStream();
    iTimestampNextAudioMsg = true;
    PushMsg(EMsgAudioPcm);
    TEST(iTimestampInspector->iStreamIsTimestamped);
    TEST(!iTimestampInspector->iLockedToStream);
    iNextNetworkTimestamp += Jiffies::kPerMs;
    PushMsg(EMsgAudioPcm);
    TUint prevRxCount = iMsgRxCount;
    iTimestampNextAudioMsg = false;
    PushMsg(EMsgAudioPcm);
    TEST(prevRxCount == iMsgRxCount); // i.e. last msg was discarded
}

void SuiteTimestampInspector::NewDecodedStreamIfAudioDiscarded()
{
    StartStream();
    iTimestampNextAudioMsg = true;
    TUint prevTxCount = iMsgTxCount;
    TUint pendingCount = 0;
    while (!iTimestampInspector->iLockedToStream) {
        TEST(prevTxCount == iMsgRxCount);
        PushMsg(EMsgAudioPcm);
        if (++pendingCount == 2) {
            iNextNetworkTimestamp += Jiffies::kPerMs;
        }
    }
    TEST(iMsgTxCount > iMsgRxCount);
    TEST(iTrackOffsetTx == iTrackOffsetRx);
}

void SuiteTimestampInspector::NewStreamWhileLocking()
{
    iTimestampNextAudioMsg = true;
    EMsgType types[] = { EMsgTrack, EMsgEncodedStream, EMsgDecodedStream };
    const size_t numElems = sizeof(types) / sizeof(types[0]);
    for (size_t i=0; i<numElems; i++) {
        StartStream();
        PushMsg(EMsgAudioPcm);
        TEST(!iTimestampInspector->iCheckForTimestamp);
        TEST(iTimestampInspector->iStreamIsTimestamped);
        TEST(!iTimestampInspector->iLockedToStream);
        PushMsg(types[i]);
        TEST(!iTimestampInspector->iCheckForTimestamp);
        TEST(iTimestampInspector->iStreamIsTimestamped);
    }
}

void SuiteTimestampInspector::InterruptedStreamRestartsLocking()
{
    iTimestampNextAudioMsg = true;
    EMsgType types[] = { EMsgHalt, EMsgFlush, EMsgWait };
    const size_t numElems = sizeof(types) / sizeof(types[0]);
    for (size_t i=0; i<numElems; i++) {
        StartStream();
        PushMsg(EMsgAudioPcm);
        TEST(iTimestampInspector->iStreamIsTimestamped);
        TEST(!iTimestampInspector->iLockedToStream);
        do {
            PushMsg(EMsgAudioPcm);
        } while (!iTimestampInspector->iLockedToStream);
        PushMsg(types[i]);
        TEST(iTimestampInspector->iStreamIsTimestamped);
        TEST(!iTimestampInspector->iLockedToStream);
    }
}

void SuiteTimestampInspector::Push(Msg* aMsg)
{
    aMsg = aMsg->Process(*this);
    aMsg->RemoveRef();
    iMsgRxCount++;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgMode* aMsg)
{
    iLastMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgTrack* aMsg)
{
    iLastMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgDrain* aMsg)
{
    iLastMsg = EMsgDrain;
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgDelay* aMsg)
{
    iLastMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastMsg = EMsgEncodedStream;
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgAudioEncoded* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgMetaText* aMsg)
{
    iLastMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgHalt* aMsg)
{
    iLastMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgFlush* aMsg)
{
    iLastMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgWait* aMsg)
{
    iLastMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastMsg = EMsgDecodedStream;
    const DecodedStreamInfo& s = aMsg->StreamInfo();
    iTrackOffsetRx = s.SampleStart() * Jiffies::JiffiesPerSample(s.SampleRate());
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgBitRate* aMsg)
{
    iLastMsg = EMsgBitRate;
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastMsg = EMsgAudioPcm;
    iMsgAudioRxCount++;
    iTrackOffsetRx += aMsg->Jiffies();
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgSilence* aMsg)
{
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgPlayable* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* SuiteTimestampInspector::ProcessMsg(MsgQuit* aMsg)
{
    iLastMsg = EMsgQuit;
    return aMsg;
}



void TestTimestampInspector()
{
    Runner runner("TimestampInspector tests\n");
    runner.Add(new SuiteTimestampInspector());
    runner.Run();
}
