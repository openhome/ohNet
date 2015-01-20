#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/SampleReporter.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>

#include <string.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteSampleReporter : public SuiteUnitTest, public IPipelineElementUpstream
{
#define KTrackUri "http://host:port/path/file.ext"
    static const TUint kTrackId       = 2;
    static const TUint kBitDepth      = 16;
    static const TUint kByteDepth = kBitDepth/8;
#define kCodecName "Dummy codec"
    static const TUint64 kTrackLength = Jiffies::kPerSecond * 60;
    static const TBool kLossless      = true;
#define kMetaText "SuiteSampleReporter sample metatext"
    static const TUint kDataBytes = 3 * 1024;   // bytes per MsgAudioPcm
public:
    SuiteSampleReporter();
public: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private:
    enum EMsgType
    {
        ENone
       ,EMsgMode
       ,EMsgSession
       ,EMsgTrack
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgAudioEncoded
       ,EMsgMetaText
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgDecodedStream
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgQuit
    };
private:
    MsgAudio* CreateAudio();
    void TestMsgsCauseAssertion();
    void TestMsgsPassedThroughNoSamplesInPipeline();
    void TestMsgsPassedThroughSamplesInPipeline();
    void TestMsgModeResets();
    void TestSubSamples();
    void TestSubSamplesDiff();
    void TestSampleRateChange();
    void TestNumChannelsChange();
    void TestInvalidSampleRate();
    void TestInvalidNumChannels();
    void TestSampleAtOverflowLimit();
    void TestSampleOverflow();
    void TestSampleMultipleOverflows();
    void TestInjectTrack();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    SampleReporter* iReporter;
    EMsgType iNextGeneratedMsg;
    Msg* iLastMsg;
    TUint64 iTrackOffset;
    Bws<1024> iTrackUri;
    TUint iTrackIdPipeline;
    TUint iSampleRate;
    TUint iNumChannels;
    TUint iBitRate;
};

} // namespace Media
} // namespace OpenHome


// SuiteSampleReporter

SuiteSampleReporter::SuiteSampleReporter()
    : SuiteUnitTest("SuiteSampleReporter")
{
    AddTest(MakeFunctor(*this, &SuiteSampleReporter::TestMsgsPassedThroughNoSamplesInPipeline), "TestMsgsPassedThroughNoSamplesInPipeline");
    AddTest(MakeFunctor(*this, &SuiteSampleReporter::TestMsgsPassedThroughSamplesInPipeline), "TestMsgsPassedThroughSamplesInPipeline");
    AddTest(MakeFunctor(*this, &SuiteSampleReporter::TestMsgModeResets), "TestMsgModeResets");
    AddTest(MakeFunctor(*this, &SuiteSampleReporter::TestSubSamples), "TestSubSamples");
    AddTest(MakeFunctor(*this, &SuiteSampleReporter::TestSubSamplesDiff), "TestSubSamplesDiff");
    AddTest(MakeFunctor(*this, &SuiteSampleReporter::TestSampleRateChange), "TestSampleRateChange");
    AddTest(MakeFunctor(*this, &SuiteSampleReporter::TestNumChannelsChange), "TestNumChannelsChange");
    AddTest(MakeFunctor(*this, &SuiteSampleReporter::TestInvalidSampleRate), "TestInvalidSampleRate");
    AddTest(MakeFunctor(*this, &SuiteSampleReporter::TestInvalidNumChannels), "TestInvalidNumChannels");
}

void SuiteSampleReporter::Setup()
{
    iNextGeneratedMsg = ENone;
    iLastMsg = NULL;
    iTrackOffset = 0;
    iSampleRate = 44100;
    iNumChannels = 2;
    iBitRate = kBitDepth * iSampleRate;
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iReporter = new SampleReporter(*this, *iMsgFactory);
}

void SuiteSampleReporter::TearDown()
{
    delete iReporter;
    delete iMsgFactory;
    delete iTrackFactory;
}

Msg* SuiteSampleReporter::Pull()
{
    switch (iNextGeneratedMsg)
    {
    case EMsgMode:
        iLastMsg = iMsgFactory->CreateMsgMode(Brn("null"), false, true, NULL);
        return iLastMsg;
    case EMsgSession:
        iLastMsg = iMsgFactory->CreateMsgSession();
        return iLastMsg;
    case EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brn(KTrackUri), Brx::Empty());
        Msg* msg = iMsgFactory->CreateMsgTrack(*track, kTrackId);
        track->RemoveRef();
        iLastMsg = msg;
        return iLastMsg;
    }
    case EMsgDelay:
        iLastMsg = iMsgFactory->CreateMsgDelay(0);
        return iLastMsg;
    case EMsgEncodedStream:
        iLastMsg = iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 0, 0, false /* not seekable */, true /* live */, NULL);
        return iLastMsg;
    case EMsgMetaText:
        iLastMsg = iMsgFactory->CreateMsgMetaText(Brn(kMetaText));
        return iLastMsg;
    case EMsgHalt:
        iLastMsg = iMsgFactory->CreateMsgHalt();
        return iLastMsg;
    case EMsgFlush:
        iLastMsg = iMsgFactory->CreateMsgFlush(1);
        return iLastMsg;
    case EMsgWait:
        iLastMsg = iMsgFactory->CreateMsgWait();
        return iLastMsg;
    case EMsgDecodedStream:
        iLastMsg = iMsgFactory->CreateMsgDecodedStream(0, iBitRate, kBitDepth, iSampleRate, iNumChannels, Brn(kCodecName), kTrackLength, 0, kLossless, false, false, NULL);
        return iLastMsg;
    case EMsgAudioPcm:
        iLastMsg = CreateAudio();
        return iLastMsg;
    case EMsgSilence:
        iLastMsg = iMsgFactory->CreateMsgSilence(Jiffies::kPerSecond * 10);
        return iLastMsg;
    case EMsgQuit:
        iLastMsg = iMsgFactory->CreateMsgQuit();
        return iLastMsg;
    default:
        ASSERTS();
        return NULL;
    }
}

MsgAudio* SuiteSampleReporter::CreateAudio()
{
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0xff, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, iNumChannels, iSampleRate, kBitDepth, EMediaDataEndianLittle, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

void SuiteSampleReporter::TestMsgsCauseAssertion()
{
    // Don't expect to see certain msgs at the point in pipeline where
    // SampleReporter is placed.
    EMsgType unexpectedTypes[] = {
        EMsgEncodedStream,
        EMsgAudioEncoded,
        EMsgFlush,
        EMsgPlayable
    };
    for (TUint i=0; i<sizeof(unexpectedTypes)/sizeof(unexpectedTypes[0]); i++) {
        iNextGeneratedMsg = unexpectedTypes[i];
        TEST_THROWS(iReporter->Pull(), AssertionFailed);
        iLastMsg->RemoveRef();  // avoid memory leaks
    }
}

void SuiteSampleReporter::TestMsgsPassedThroughNoSamplesInPipeline()
{
    // All msgs should pass through unchanged. However, only MsgMode,
    // MsgDecodedStream and MsgAudioPcm should change the state of the
    // SampleReporter, so test the others.

    EMsgType types[] = {
        EMsgSession,
        EMsgTrack,
        EMsgDelay,
        EMsgMetaText,
        EMsgHalt,
        EMsgWait,
        EMsgSilence,
        EMsgQuit
    };
    for (TUint i=0; i<sizeof(types)/sizeof(types[0]); i++) {
        iNextGeneratedMsg = types[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
        TEST(iReporter->SubSamples() == 0);
        TEST(iReporter->SubSamplesDiff(0) == 0);
    }
}

void SuiteSampleReporter::TestMsgsPassedThroughSamplesInPipeline()
{
    TUint samplesExpected = kDataBytes/kByteDepth;
    // First, put some audio into pipeline.
    EMsgType audioSetupTypes[] = {
        EMsgMode,
        EMsgTrack,
        EMsgDecodedStream,
        EMsgAudioPcm,
    };
    for (TUint i=0; i<sizeof(audioSetupTypes)/sizeof(audioSetupTypes[0]); i++) {
        iNextGeneratedMsg = audioSetupTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
    }
    TEST(iReporter->SubSamples() == samplesExpected);
    TEST(iReporter->SubSamplesDiff(0) == samplesExpected);

    // Now, test msg types that should have no effect on state of SampleReporter.
    EMsgType passThroughTypes[] = {
        EMsgSession,
        EMsgTrack,
        EMsgDelay,
        EMsgMetaText,
        EMsgHalt,
        EMsgWait,
        EMsgSilence,
        EMsgQuit
    };
    for (TUint i=0; i<sizeof(passThroughTypes)/sizeof(passThroughTypes[0]); i++) {
        iNextGeneratedMsg = passThroughTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
        TEST(iReporter->SubSamples() == samplesExpected);
        TEST(iReporter->SubSamplesDiff(0) == samplesExpected);
    }
}

void SuiteSampleReporter::TestMsgModeResets()
{
    TUint samplesExpected = kDataBytes/kByteDepth;
    // First, put some audio into pipeline.
    EMsgType audioSetupTypes[] = {
        EMsgMode,
        EMsgTrack,
        EMsgDecodedStream,
        EMsgAudioPcm,
    };
    for (TUint i=0; i<sizeof(audioSetupTypes)/sizeof(audioSetupTypes[0]); i++) {
        iNextGeneratedMsg = audioSetupTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
    }
    TEST(iReporter->SubSamples() == samplesExpected);
    TEST(iReporter->SubSamplesDiff(0) == samplesExpected);

    // Now, send a MsgMode, which should reset sample count.
    iNextGeneratedMsg = EMsgMode;
    Msg* msg = iReporter->Pull();
    msg->RemoveRef();
    TEST(iReporter->SubSamples() == 0);
    TEST(iReporter->SubSamplesDiff(0) == 0);
}

void SuiteSampleReporter::TestSubSamples()
{
    // FIXME - vary number of samples in msgs to catch overflow issue
    // Will need to have an iDataBytes value, instead of kDataBytes, that can
    // be varied
    TUint samplesExpectedPerMsg = kDataBytes/kByteDepth;
    TUint samplesExpected = samplesExpectedPerMsg;

    // Set up sequence.
    EMsgType setupTypes[] = {
        EMsgMode,
        EMsgTrack,
        EMsgDecodedStream,
    };
    for (TUint i=0; i<sizeof(setupTypes)/sizeof(setupTypes[0]); i++) {
        iNextGeneratedMsg = setupTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
    }
    TEST(iReporter->SubSamples() == 0);

    // Send audio.
    EMsgType audioTypes[] = {
        EMsgAudioPcm,
        EMsgAudioPcm,
        EMsgAudioPcm,
    };
    for (TUint i=0; i<sizeof(audioTypes)/sizeof(audioTypes[0]); i++) {
        iNextGeneratedMsg = audioTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
        TEST(iReporter->SubSamples() == samplesExpected);
        samplesExpected += samplesExpectedPerMsg;
    }
}

void SuiteSampleReporter::TestSubSamplesDiff()
{
    TUint samplesExpectedPerMsg = kDataBytes/kByteDepth;
    TUint samplesExpected = samplesExpectedPerMsg;

    // Set up sequence.
    EMsgType setupTypes[] = {
        EMsgMode,
        EMsgTrack,
        EMsgDecodedStream,
    };
    for (TUint i=0; i<sizeof(setupTypes)/sizeof(setupTypes[0]); i++) {
        iNextGeneratedMsg = setupTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
    }
    TEST(iReporter->SubSamplesDiff(0) == 0);

    // Send audio.
    EMsgType audioTypes[] = {
        EMsgAudioPcm,
        EMsgAudioPcm,
        EMsgAudioPcm,
    };
    for (TUint i=0; i<sizeof(audioTypes)/sizeof(audioTypes[0]); i++) {
        iNextGeneratedMsg = audioTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
        TEST(iReporter->SubSamplesDiff(0) == samplesExpected);
        samplesExpected += samplesExpectedPerMsg;
    }
}

void SuiteSampleReporter::TestSampleRateChange()
{
    TUint samplesExpectedPerMsg = kDataBytes/kByteDepth;
    TUint samplesExpected = samplesExpectedPerMsg;

    // Set up sequence.
    EMsgType setupTypes[] = {
        EMsgMode,
        EMsgTrack,
        EMsgDecodedStream,
    };
    for (TUint i=0; i<sizeof(setupTypes)/sizeof(setupTypes[0]); i++) {
        iNextGeneratedMsg = setupTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
    }

    // Send audio.
    EMsgType audioTypes[] = {
        EMsgAudioPcm,
        EMsgAudioPcm,
        EMsgAudioPcm,
    };
    for (TUint i=0; i<sizeof(audioTypes)/sizeof(audioTypes[0]); i++) {
        iNextGeneratedMsg = audioTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
        TEST(iReporter->SubSamples() == samplesExpected);
        samplesExpected += samplesExpectedPerMsg;
    }


    // Now, change sample rate and send more audio.
    iSampleRate = 48000;
    iBitRate = kBitDepth * iSampleRate;
    EMsgType reinitTypes[] = {
        EMsgTrack,
        EMsgDecodedStream,
    };
    for (TUint i=0; i<sizeof(reinitTypes)/sizeof(reinitTypes[0]); i++) {
        iNextGeneratedMsg = reinitTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
    }

    // Send audio.
    for (TUint i=0; i<sizeof(audioTypes)/sizeof(audioTypes[0]); i++) {
        iNextGeneratedMsg = audioTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
        TEST(iReporter->SubSamples() == samplesExpected);
        samplesExpected += samplesExpectedPerMsg;
    }
}

void SuiteSampleReporter::TestNumChannelsChange()
{
    TUint samplesExpectedPerMsg = kDataBytes/kByteDepth;
    TUint samplesExpected = samplesExpectedPerMsg;

    // Set up sequence.
    EMsgType setupTypes[] = {
        EMsgMode,
        EMsgTrack,
        EMsgDecodedStream,
    };
    for (TUint i=0; i<sizeof(setupTypes)/sizeof(setupTypes[0]); i++) {
        iNextGeneratedMsg = setupTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
    }

    // Send audio.
    EMsgType audioTypes[] = {
        EMsgAudioPcm,
        EMsgAudioPcm,
        EMsgAudioPcm,
    };
    for (TUint i=0; i<sizeof(audioTypes)/sizeof(audioTypes[0]); i++) {
        iNextGeneratedMsg = audioTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
        TEST(iReporter->SubSamples() == samplesExpected);
        samplesExpected += samplesExpectedPerMsg;
    }


    // Now, change sample rate and send more audio.
    iNumChannels = 1;
    EMsgType reinitTypes[] = {
        EMsgTrack,
        EMsgDecodedStream,
    };
    for (TUint i=0; i<sizeof(reinitTypes)/sizeof(reinitTypes[0]); i++) {
        iNextGeneratedMsg = reinitTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
    }

    // Send audio.
    for (TUint i=0; i<sizeof(audioTypes)/sizeof(audioTypes[0]); i++) {
        iNextGeneratedMsg = audioTypes[i];
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
        TEST(iReporter->SubSamples() == samplesExpected);
        samplesExpected += samplesExpectedPerMsg;
    }
}

void SuiteSampleReporter::TestInvalidSampleRate()
{
    iSampleRate = 0;
    iBitRate = kBitDepth * iSampleRate;

    iNextGeneratedMsg = EMsgMode;
    Msg* msg = iReporter->Pull();
    msg->RemoveRef();

    iNextGeneratedMsg = EMsgTrack;
    msg = iReporter->Pull();
    msg->RemoveRef();

    iNextGeneratedMsg = EMsgDecodedStream;
    TEST_THROWS(iReporter->Pull(), AssertionFailed);
    iLastMsg->RemoveRef();  // avoid memory leaks
}

void SuiteSampleReporter::TestInvalidNumChannels()
{
    iNumChannels = 0;

    iNextGeneratedMsg = EMsgMode;
    Msg* msg = iReporter->Pull();
    msg->RemoveRef();

    iNextGeneratedMsg = EMsgTrack;
    msg = iReporter->Pull();
    msg->RemoveRef();

    iNextGeneratedMsg = EMsgDecodedStream;
    TEST_THROWS(iReporter->Pull(), AssertionFailed);
    iLastMsg->RemoveRef();  // avoid memory leaks
}


void TestSampleReporter()
{
    Runner runner("SampleReporter tests\n");
    runner.Add(new SuiteSampleReporter());
    runner.Run();
}
