#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Utils/Aggregator.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>

#include <string.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteAggregator : public SuiteUnitTest, private IPipelineElementUpstream, private IMsgProcessor
{
public:
    SuiteAggregator();
    ~SuiteAggregator();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private:
    void TestPlayablesAreAggregated();
    void TestPlayablesAreSplit();
    void TestModeCausesShortPlayableToBePulled();
    void TestHaltCausesShortPlayableToBePulled();
    void TestChangeSampleRate();
    void TestChangeBitDepth();
    void TestChangeNumChannels();
private: // from IPipelineElementUpstream
    Msg* Pull() override;
private:
    MsgPlayable* CreateAudio();
    void PullMsg();
    TBool TimesEqual(TUint aJiffy1, TUint aJiffy2);
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
    enum EMsgType
    {
        ENone
       ,EMsgPlayable
       ,EMsgDecodedStream
       ,EMsgMode
       ,EMsgHalt
       ,EMsgQuit
    };
private:
    static const TUint kAggregatorJiffies = Jiffies::kPerMs * 5;
    static const TUint kMaxAudioBytes = 12 * 1024;

    MsgFactory* iMsgFactory;
    AllocatorInfoLogger iInfoAggregator;
    Aggregator* iAggregator;
    EMsgType iNextGeneratedMsg;
    EMsgType iLastMsg;
    TUint64 iTrackOffset;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iNumChannels;
    TUint iAudioMsgSizeJiffies;
    TByte iAudioSrc[kMaxAudioBytes];
    TUint iLastPulledBytes;
    TUint iLastPulledJiffies;
    TUint iGeneratedMsgCount;
};

} // namespace Media
} // namespace OpenHome


// SuiteAggregator

SuiteAggregator::SuiteAggregator()
    : SuiteUnitTest("Aggregator tests")
    , iLastMsg(ENone)
    , iTrackOffset(0)
    , iNumChannels(2)
{
    memset(iAudioSrc, 0xff, sizeof(iAudioSrc));

    AddTest(MakeFunctor(*this, &SuiteAggregator::TestPlayablesAreAggregated), "TestPlayablesAreAggregated");
    AddTest(MakeFunctor(*this, &SuiteAggregator::TestPlayablesAreSplit), "TestPlayablesAreSplit");
    AddTest(MakeFunctor(*this, &SuiteAggregator::TestModeCausesShortPlayableToBePulled), "TestModeCausesShortPlayableToBePulled");
    AddTest(MakeFunctor(*this, &SuiteAggregator::TestHaltCausesShortPlayableToBePulled), "TestHaltCausesShortPlayableToBePulled");
    AddTest(MakeFunctor(*this, &SuiteAggregator::TestChangeSampleRate), "TestChangeSampleRate");
    AddTest(MakeFunctor(*this, &SuiteAggregator::TestChangeBitDepth), "TestChangeBitDepth");
    AddTest(MakeFunctor(*this, &SuiteAggregator::TestChangeNumChannels), "TestChangeNumChannels");
}

SuiteAggregator::~SuiteAggregator()
{
}

void SuiteAggregator::Setup()
{
    iSampleRate = 44100;
    iBitDepth = 16;
    iNumChannels = 2;
    iTrackOffset = 0;
    iAudioMsgSizeJiffies = kAggregatorJiffies + Jiffies::kPerMs; /* choose a size that doesn't match kAggregatorJiffies
                                                                    to force the Aggregator to do some work */
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(10, 10);
    init.SetMsgSilenceCount(10);
    init.SetMsgPlayableCount(10, 10);
    init.SetMsgDecodedStreamCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iAggregator = new Aggregator(*this, kAggregatorJiffies);
    iLastPulledBytes = iLastPulledJiffies = 0;
    iGeneratedMsgCount = 0;
}

void SuiteAggregator::TearDown()
{
    delete iAggregator;
    delete iMsgFactory;
}

void SuiteAggregator::TestPlayablesAreAggregated()
{
    iNextGeneratedMsg = EMsgDecodedStream;
    PullMsg();
    TEST(iLastMsg == EMsgDecodedStream);

    iAudioMsgSizeJiffies /= 4;
    iNextGeneratedMsg = EMsgPlayable;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(iGeneratedMsgCount > 2);
    TEST(TimesEqual(iLastPulledJiffies, kAggregatorJiffies));
}

void SuiteAggregator::TestPlayablesAreSplit()
{
    iNextGeneratedMsg = EMsgDecodedStream;
    PullMsg();
    TEST(iLastMsg == EMsgDecodedStream);

    iNextGeneratedMsg = EMsgPlayable;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(iGeneratedMsgCount == 2);
    TEST(iAggregator->iPlayable != nullptr);
    TEST(TimesEqual(iLastPulledJiffies, kAggregatorJiffies));
}

void SuiteAggregator::TestModeCausesShortPlayableToBePulled()
{
    iNextGeneratedMsg = EMsgDecodedStream;
    PullMsg();
    TEST(iLastMsg == EMsgDecodedStream);
    iNextGeneratedMsg = EMsgPlayable;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(iAggregator->iPlayable != nullptr);

    iNextGeneratedMsg = EMsgMode;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(iAggregator->iPlayable == nullptr);
    PullMsg();
    TEST(iLastMsg == EMsgMode);
}

void SuiteAggregator::TestHaltCausesShortPlayableToBePulled()
{
    iNextGeneratedMsg = EMsgDecodedStream;
    PullMsg();
    TEST(iLastMsg == EMsgDecodedStream);
    iNextGeneratedMsg = EMsgPlayable;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(iAggregator->iPlayable != nullptr);

    iNextGeneratedMsg = EMsgHalt;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(iAggregator->iPlayable == nullptr);
    PullMsg();
    TEST(iLastMsg == EMsgHalt);
}

void SuiteAggregator::TestChangeSampleRate()
{
    iNextGeneratedMsg = EMsgDecodedStream;
    PullMsg();
    TEST(iLastMsg == EMsgDecodedStream);
    iNextGeneratedMsg = EMsgPlayable;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(iAggregator->iPlayable != nullptr);
    const TUint prevBytes = iLastPulledBytes;

    iSampleRate /= 2;
    iNextGeneratedMsg = EMsgDecodedStream;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(iAggregator->iPlayable == nullptr);

    PullMsg();
    TEST(iLastMsg == EMsgDecodedStream);
    iNextGeneratedMsg = EMsgPlayable;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(TimesEqual(iLastPulledJiffies, kAggregatorJiffies));
    TEST(iLastPulledBytes == prevBytes/2);
}

void SuiteAggregator::TestChangeBitDepth()
{
    iNextGeneratedMsg = EMsgDecodedStream;
    PullMsg();
    TEST(iLastMsg == EMsgDecodedStream);
    iNextGeneratedMsg = EMsgPlayable;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(iAggregator->iPlayable != nullptr);
    const TUint prevBytes = iLastPulledBytes;

    iBitDepth = 8;
    iNextGeneratedMsg = EMsgDecodedStream;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(iAggregator->iPlayable == nullptr);

    PullMsg();
    TEST(iLastMsg == EMsgDecodedStream);
    iNextGeneratedMsg = EMsgPlayable;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(TimesEqual(iLastPulledJiffies, kAggregatorJiffies));
    TEST(iLastPulledBytes == prevBytes/2);
}

void SuiteAggregator::TestChangeNumChannels()
{
    iNextGeneratedMsg = EMsgDecodedStream;
    PullMsg();
    TEST(iLastMsg == EMsgDecodedStream);
    iNextGeneratedMsg = EMsgPlayable;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(iAggregator->iPlayable != nullptr);
    const TUint prevBytes = iLastPulledBytes;

    iNumChannels = 1;
    iNextGeneratedMsg = EMsgDecodedStream;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(iAggregator->iPlayable == nullptr);

    PullMsg();
    TEST(iLastMsg == EMsgDecodedStream);
    iNextGeneratedMsg = EMsgPlayable;
    PullMsg();
    TEST(iLastMsg == EMsgPlayable);
    TEST(TimesEqual(iLastPulledJiffies, kAggregatorJiffies));
    TEST(iLastPulledBytes == prevBytes/2);
}

Msg* SuiteAggregator::Pull()
{
    iGeneratedMsgCount++;
    switch (iNextGeneratedMsg)
    {
    case EMsgPlayable:
        return CreateAudio();
    case EMsgDecodedStream:
        return iMsgFactory->CreateMsgDecodedStream(0, 128000, iBitDepth, iSampleRate, iNumChannels, Brn("dummy codec"), (TUint64)1<<31, 0, false, false, false, false, nullptr);
    case EMsgMode:
        return iMsgFactory->CreateMsgMode(Brn("dummyMode"), true, false, ModeClockPullers(), false, false);
    case EMsgHalt:
        return iMsgFactory->CreateMsgHalt();
    case EMsgQuit:
        return iMsgFactory->CreateMsgQuit();
    default:
        ASSERTS();
        return nullptr;
    }
}

MsgPlayable* SuiteAggregator::CreateAudio()
{
    TUint jiffies = iAudioMsgSizeJiffies + Jiffies::kPerMs; /* choose a size that doesn't match kAggregatorJiffies
                                                               to force the Aggregator to do some work */
    const TUint bytes = Jiffies::ToBytes(jiffies, Jiffies::PerSample(iSampleRate), iNumChannels, iBitDepth/8);
    Brn encodedAudioBuf(iAudioSrc, bytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, iNumChannels, iSampleRate, iBitDepth, EMediaDataEndianLittle, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    MsgPlayable* playable = audio->CreatePlayable();
    return playable;
}

void SuiteAggregator::PullMsg()
{
    Msg* msg = iAggregator->Pull();
    ASSERT(msg != nullptr);
    msg = msg->Process(*this);
    if (msg != nullptr) {
        msg->RemoveRef();
    }
}

TBool SuiteAggregator::TimesEqual(TUint aJiffy1, TUint aJiffy2)
{
    /* Not all sample rates can represent a precise number of milliseconds.
       So we might end up pulling slightly more or less audio than we expect.
       This nasty bodge checks that times are roughly equivalent, all we need for this test. */
    static const TUint kJiffyEpsilon = Jiffies::kPerMs / 10;
    if (aJiffy1 > aJiffy2) {
        return (aJiffy1 - aJiffy2 < kJiffyEpsilon);
    }
    return (aJiffy2 - aJiffy1 < kJiffyEpsilon);
}

Msg* SuiteAggregator::ProcessMsg(MsgMode* aMsg)
{
    iLastMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteAggregator::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAggregator::ProcessMsg(MsgDrain* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAggregator::ProcessMsg(MsgDelay* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAggregator::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAggregator::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAggregator::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAggregator::ProcessMsg(MsgStreamInterrupted* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAggregator::ProcessMsg(MsgHalt* aMsg)
{
    iLastMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteAggregator::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAggregator::ProcessMsg(MsgWait* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAggregator::ProcessMsg(MsgDecodedStream* aMsg)
{
    TEST(aMsg->StreamInfo().BitDepth() == iBitDepth);
    TEST(aMsg->StreamInfo().SampleRate() == iSampleRate);
    TEST(aMsg->StreamInfo().NumChannels() == iNumChannels);
    iLastMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteAggregator::ProcessMsg(MsgBitRate* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAggregator::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAggregator::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAggregator::ProcessMsg(MsgPlayable* aMsg)
{
    iLastMsg = EMsgPlayable;
    iLastPulledBytes = aMsg->Bytes();
    const TUint jiffiesPerSample = Jiffies::PerSample(iSampleRate);
    const TUint bytesPerSample = iNumChannels * iBitDepth/8;
    iLastPulledJiffies = (iLastPulledBytes / bytesPerSample) * jiffiesPerSample;
    return aMsg;
}

Msg* SuiteAggregator::ProcessMsg(MsgQuit* aMsg)
{
    iLastMsg = EMsgQuit;
    return aMsg;
}



void TestAggregator()
{
    Runner runner("Aggregator tests\n");
    runner.Add(new SuiteAggregator());
    runner.Run();
}
