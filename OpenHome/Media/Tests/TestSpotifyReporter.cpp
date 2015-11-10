#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/Reporter.h>
#include <OpenHome/Media/Pipeline/SpotifyReporter.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Private/Ascii.h>

#include <limits>
#include <string.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

template <class T>
class MsgIdentifier : public PipelineElement
{
public:
    MsgIdentifier();
    T* GetMsg(Msg* aMsg);   // ASSERTS if not msg of type T passed in.
private: // from PipelineElement
    Msg* ProcessMsg(T* aMsg) override;
private:
    T* iMsg;
};

class MockDidlLiteWriter : public IDidlLiteWriter
{
public: // from IDidlLiteWriter
    void WriteDidlLite(IWriter& aWriter, TUint aBitDepth, TUint aChannels, TUint aSampleRate) const override;
};

class SuiteSpotifyReporter : public SuiteUnitTest, public IPipelineElementUpstream
{
#define kDefaultMode "null"
#define kModeSpotify "Spotify"
#define kTrackUri "http://host:port/path/file.ext"
    static const TUint kBitDepth      = 16;
    static const TUint kByteDepth = kBitDepth/8;
    static const TUint kDefaultSampleRate = 44100;
    static const TUint kDefaultNumChannels = 2;
    static const TUint kDefaultBitrate = kBitDepth * kDefaultSampleRate;
    static const TUint kDefaultTrackLength = Jiffies::kPerSecond * 10;
    static const TUint kDefaultSampleStart = 0;
#define kCodecName "Dummy codec"
    static const TUint64 kTrackLength = Jiffies::kPerSecond * 60;
    static const TBool kLossless      = true;
#define kMetaText "SuiteSpotifyReporter sample metatext"
    static const TUint kDataBytes = 3 * 1024;   // bytes per MsgAudioPcm
public:
    SuiteSpotifyReporter();
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
       ,EMsgTrack
       ,EMsgDrain
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
    void DrainCallback();
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
    void TestPassThroughInjectTrack();
    void TestModeSpotifyNoTrackInjectedAtStart();
    void TestModeSpotifyTrackInjected();
    void TestModeSpotifySeek();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    SpotifyReporter* iReporter;
    EMsgType iNextGeneratedMsg;
    Msg* iLastMsg;
    BwsMode iMode;
    TUint64 iTrackOffset;
    Bws<1024> iTrackUri;
    TUint iSampleRate;
    TUint iNumChannels;
    TUint iBitRate;
    TUint64 iTrackLength;
    TUint64 iSampleStart;
};

} // namespace Media
} // namespace OpenHome


// MsgIdentifier

template <class T>
MsgIdentifier<T>::MsgIdentifier()
    : PipelineElement(0)
    , iMsg(nullptr)
{
}

template <class T>
T* MsgIdentifier<T>::GetMsg(Msg* aMsg)
{
    Msg* msg = aMsg->Process(*this);
    ASSERT(msg == nullptr);
    ASSERT(iMsg != nullptr);
    T* msgOut = iMsg;
    iMsg = nullptr;
    return msgOut;
}

template <class T>
Msg* MsgIdentifier<T>::ProcessMsg(T* aMsg)
{
    iMsg = aMsg;
    return nullptr;
}


// MockDidlLiteWriter

void MockDidlLiteWriter::WriteDidlLite(IWriter& aWriter, TUint aBitDepth, TUint aChannels, TUint aSampleRate) const
{
    Bws<Ascii::kMaxUintStringBytes> bufUint;
    aWriter.Write(Brn("bitDepth: "));
    Ascii::AppendDec(bufUint, aBitDepth);
    aWriter.Write(bufUint);
    aWriter.Write(Brn(", numChannels: "));
    bufUint.SetBytes(0);
    Ascii::AppendDec(bufUint, aChannels);
    aWriter.Write(bufUint);
    aWriter.Write(Brn(", sampleRate: "));
    bufUint.SetBytes(0);
    Ascii::AppendDec(bufUint, aSampleRate);
    aWriter.Write(bufUint);
}



// SuiteSpotifyReporter

SuiteSpotifyReporter::SuiteSpotifyReporter()
    : SuiteUnitTest("SuiteSpotifyReporter")
{
    //AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestMsgsCauseAssertion), "TestMsgsCauseAssertion");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestMsgsPassedThroughNoSamplesInPipeline), "TestMsgsPassedThroughNoSamplesInPipeline");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestMsgsPassedThroughSamplesInPipeline), "TestMsgsPassedThroughSamplesInPipeline");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestMsgModeResets), "TestMsgModeResets");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestSubSamples), "TestSubSamples");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestSubSamplesDiff), "TestSubSamplesDiff");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestSampleRateChange), "TestSampleRateChange");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestNumChannelsChange), "TestNumChannelsChange");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestInvalidSampleRate), "TestInvalidSampleRate");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestInvalidNumChannels), "TestInvalidNumChannels");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestPassThroughInjectTrack), "TestPassThroughInjectTrack");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestModeSpotifyNoTrackInjectedAtStart), "TestModeSpotifyNoTrackInjectedAtStart");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestModeSpotifyTrackInjected), "TestModeSpotifyTrackInjected");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestModeSpotifySeek), "TestModeSpotifySeek");
}

void SuiteSpotifyReporter::Setup()
{
    iNextGeneratedMsg = ENone;
    iLastMsg = nullptr;
    iMode.Replace(kDefaultMode);
    iTrackOffset = 0;
    iSampleRate = kDefaultSampleRate;
    iNumChannels = kDefaultNumChannels;
    iBitRate = kDefaultBitrate;
    iTrackLength = kDefaultTrackLength;
    iSampleStart = kDefaultSampleStart;
    MsgFactoryInitParams init;
    init.SetMsgDecodedStreamCount(2);   // SpotifyReporter always caches last seen MsgDecodedStream, so require at least 2 in pipeline.
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 2);   // Require at least 2 Tracks for SpotifyReporter, as it will cache one.
    iReporter = new SpotifyReporter(*this, *iMsgFactory, *iTrackFactory);
}

void SuiteSpotifyReporter::TearDown()
{
    delete iReporter;
    delete iTrackFactory;
    delete iMsgFactory;
}

Msg* SuiteSpotifyReporter::Pull()
{
    switch (iNextGeneratedMsg)
    {
    case EMsgMode:
        iLastMsg = iMsgFactory->CreateMsgMode(iMode, false, true, ModeClockPullers(), false, false);
        return iLastMsg;
    case EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brn(kTrackUri), Brx::Empty());
        Msg* msg = iMsgFactory->CreateMsgTrack(*track);
        track->RemoveRef();
        iLastMsg = msg;
        return iLastMsg;
    }
    case EMsgDrain:
        iLastMsg = iMsgFactory->CreateMsgDrain(MakeFunctor(*this, &SuiteSpotifyReporter::DrainCallback));
        return iLastMsg;
    case EMsgDelay:
        iLastMsg = iMsgFactory->CreateMsgDelay(0);
        return iLastMsg;
    case EMsgEncodedStream:
        iLastMsg = iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 0, 0, 0, false /* not seekable */, true /* live */, nullptr);
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
        iLastMsg = iMsgFactory->CreateMsgDecodedStream(0, iBitRate, kBitDepth, iSampleRate, iNumChannels, Brn(kCodecName), iTrackLength, iSampleStart, kLossless, false, false, nullptr);
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
        return nullptr;
    }
}

MsgAudio* SuiteSpotifyReporter::CreateAudio()
{
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0xff, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, iNumChannels, iSampleRate, kBitDepth, EMediaDataEndianLittle, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

void SuiteSpotifyReporter::DrainCallback()
{
}

void SuiteSpotifyReporter::TestMsgsCauseAssertion()
{
    // Don't expect to see certain msgs at the point in pipeline where
    // SpotifyReporter is placed.
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

void SuiteSpotifyReporter::TestMsgsPassedThroughNoSamplesInPipeline()
{
    // All msgs should pass through unchanged. However, only MsgMode,
    // MsgDecodedStream and MsgAudioPcm should change the state of the
    // SpotifyReporter, so test the others.

    EMsgType types[] = {
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

void SuiteSpotifyReporter::TestMsgsPassedThroughSamplesInPipeline()
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

    // Now, test msg types that should have no effect on state of SpotifyReporter.
    EMsgType passThroughTypes[] = {
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

void SuiteSpotifyReporter::TestMsgModeResets()
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

void SuiteSpotifyReporter::TestSubSamples()
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

void SuiteSpotifyReporter::TestSubSamplesDiff()
{
    TUint samplesExpectedPerMsg = kDataBytes/kByteDepth;
    TUint samplesExpected = 0;

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
        samplesExpected += samplesExpectedPerMsg;
        Msg* msg = iReporter->Pull();
        msg->RemoveRef();
        TEST(iReporter->SubSamplesDiff(0) == samplesExpected);
    }

    // Finally, test code asserts if passed in a subsample value greater than what SpotifyReporter has observed.
    TEST_THROWS(iReporter->SubSamplesDiff(samplesExpected+1), AssertionFailed);
}

void SuiteSpotifyReporter::TestSampleRateChange()
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

void SuiteSpotifyReporter::TestNumChannelsChange()
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

void SuiteSpotifyReporter::TestInvalidSampleRate()
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

void SuiteSpotifyReporter::TestInvalidNumChannels()
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

void SuiteSpotifyReporter::TestPassThroughInjectTrack()
{
    // This could happen if Spotify source is just starting, but audio has yet to arrive at SpotifyReporter, so track is injected during non-Spotify stream.
    static const Brn kSpotifyTrackUri("spotify://");
    const TUint kDurationMs = 1234;

    MockDidlLiteWriter writer;
    iReporter->TrackChanged(kSpotifyTrackUri, writer, kDurationMs);

    iNextGeneratedMsg = EMsgMode;
    Msg* msg = iReporter->Pull();
    msg->RemoveRef();

    iNextGeneratedMsg = EMsgTrack;
    msg = iReporter->Pull();
    MsgIdentifier<MsgTrack> msgIdTrack;
    MsgTrack* msgTrack = msgIdTrack.GetMsg(msg);
    TEST(msgTrack->Track().Uri() == Brn(kTrackUri));
    TEST(msgTrack->Track().MetaData() == Brx::Empty());
    msgTrack->RemoveRef();

    iNextGeneratedMsg = EMsgDecodedStream;
    msg = iReporter->Pull();
    MsgIdentifier<MsgDecodedStream> msgIdDecodedStream;
    MsgDecodedStream* msgDecodedStream = msgIdDecodedStream.GetMsg(msg);
    const DecodedStreamInfo& info = msgDecodedStream->StreamInfo();
    // Check a modified MsgDecodedStream wasn't inserted.
    TEST(info.TrackLength() == kDefaultTrackLength);
    msgDecodedStream->RemoveRef();

    // Pull some audio to check that no modified MsgTrack or MsgDecodedStream is injected.
    const TUint samplesExpectedPerMsg = kDataBytes/kByteDepth;
    iNextGeneratedMsg = EMsgAudioPcm;
    msg = iReporter->Pull();
    msg->RemoveRef();
    TEST(iReporter->SubSamples() == samplesExpectedPerMsg);
}

void SuiteSpotifyReporter::TestModeSpotifyNoTrackInjectedAtStart()
{
    // Enter Spotify mode, but have no track injected.
    // MsgDecodedStream should end up with zero length, as length not yet known.
    iMode.Replace(kModeSpotify);
    iNextGeneratedMsg = EMsgMode;
    Msg* msg = iReporter->Pull();
    msg->RemoveRef();

    // URI for in-band track doesn't matter in SpotifyReporter.
    iNextGeneratedMsg = EMsgTrack;
    msg = iReporter->Pull();
    MsgIdentifier<MsgTrack> msgIdTrack;
    MsgTrack* msgTrack = msgIdTrack.GetMsg(msg);
    TEST(msgTrack->Track().Uri() == Brn(kTrackUri));
    TEST(msgTrack->Track().MetaData() == Brx::Empty());
    msgTrack->RemoveRef();

    const TUint kStartSample = 88200;
    iSampleStart = kStartSample;
    iNextGeneratedMsg = EMsgDecodedStream;
    msg = iReporter->Pull();
    MsgIdentifier<MsgDecodedStream> msgIdDecodedStream;
    MsgDecodedStream* msgDecodedStream = msgIdDecodedStream.GetMsg(msg);
    const DecodedStreamInfo& info = msgDecodedStream->StreamInfo();
    // Check MsgDecodedStream length has been set to 0, but that start sample unmodified.
    TEST(info.TrackLength() == 0);
    TEST(info.SampleStart() == kStartSample);
    msgDecodedStream->RemoveRef();

    // Pull some audio.
    TUint64 expectedSubsamples = 0;
    const TUint samplesExpectedPerMsg = kDataBytes/kByteDepth;
    iNextGeneratedMsg = EMsgAudioPcm;
    msg = iReporter->Pull();
    MsgIdentifier<MsgAudioPcm> msgIdAudioPcm;
    MsgAudioPcm* msgAudioPcm = msgIdAudioPcm.GetMsg(msg);
    msgAudioPcm->RemoveRef();
    expectedSubsamples += samplesExpectedPerMsg;
    TEST(iReporter->SubSamples() == expectedSubsamples);

    // Now, inject a Track. Should now pull a MsgTrack followed by a MsgDecodedStream.
    static const Brn kSpotifyTrackUri("spotify://");
    const TUint kDurationMs = 1234;
    const TUint64 kDurationJiffies = (static_cast<TUint64>(kDurationMs*iSampleRate)*Jiffies::JiffiesPerSample(iSampleRate))/1000;
    MockDidlLiteWriter writer;
    iReporter->TrackChanged(kSpotifyTrackUri, writer, kDurationMs);

    // First, set audio to be pulled next.
    iNextGeneratedMsg = EMsgAudioPcm;
    // Now, try pull. MsgTrack should be output.
    msg = iReporter->Pull();
    msgTrack = msgIdTrack.GetMsg(msg);
    TEST(msgTrack->Track().Uri() == kSpotifyTrackUri);
    TEST(msgTrack->Track().MetaData() == Brn("bitDepth: 16, numChannels: 2, sampleRate: 44100"));
    msgTrack->RemoveRef();
    // Try pull again. Should be MsgDecodedStream with injected duration and sample start of 0 (as track injection resets sample start).
    msg = iReporter->Pull();
    msgDecodedStream = msgIdDecodedStream.GetMsg(msg);
    const DecodedStreamInfo& info2 = msgDecodedStream->StreamInfo();
    TEST(info2.TrackLength() == kDurationJiffies);
    TEST(info2.SampleStart() == 0);
    msgDecodedStream->RemoveRef();
    // Pull again. Should finally be the audio that was queued up.
    msg = iReporter->Pull();
    msg->RemoveRef();
    expectedSubsamples += samplesExpectedPerMsg;
    TEST(iReporter->SubSamples() == expectedSubsamples);
}

void SuiteSpotifyReporter::TestModeSpotifyTrackInjected()
{
    // Inject a track to simulate real-world condition where out-of-band track notification is reach SpotifyReporter before MsgMode at Spotify initialisation.
    static const Brn kSpotifyTrackUri("spotify://");
    const TUint kDurationMs = 1234;
    const TUint64 kDurationJiffies = (static_cast<TUint64>(kDurationMs*iSampleRate)*Jiffies::JiffiesPerSample(iSampleRate))/1000;
    MockDidlLiteWriter writer;
    iReporter->TrackChanged(kSpotifyTrackUri, writer, kDurationMs);

    // Pull mode.
    iMode.Replace(kModeSpotify);
    iNextGeneratedMsg = EMsgMode;
    Msg* msg = iReporter->Pull();
    msg->RemoveRef();

    // Set track to be next msg down pipeline.
    // Pull again. Should be in-band pipeline MsgTrack.
    iNextGeneratedMsg = EMsgTrack;
    msg = iReporter->Pull();
    MsgIdentifier<MsgTrack> msgIdTrack;
    MsgTrack* msgTrack = msgIdTrack.GetMsg(msg);
    TEST(msgTrack->Track().Uri() == Brn(kTrackUri));
    TEST(msgTrack->Track().MetaData() == Brx::Empty());
    msgTrack->RemoveRef();

    // Pull again. Should be injected track.
    msg = iReporter->Pull();
    msgTrack = msgIdTrack.GetMsg(msg);
    TEST(msgTrack->Track().Uri() == kSpotifyTrackUri);
    TEST(msgTrack->Track().MetaData() == Brn("bitDepth: 0, numChannels: 0, sampleRate: 0"));
    msgTrack->RemoveRef();

    // Now, queue up MsgDecodedStream. Should be intercepted and a modified one output.
    static const TUint kStartSample = 88200;
    iSampleStart = kStartSample;
    iNextGeneratedMsg = EMsgDecodedStream;
    msg = iReporter->Pull();
    MsgIdentifier<MsgDecodedStream> msgIdDecodedStream;
    MsgDecodedStream* msgDecodedStream = msgIdDecodedStream.GetMsg(msg);
    const DecodedStreamInfo& info = msgDecodedStream->StreamInfo();
    TEST(info.TrackLength() == kDurationJiffies);
    TEST(info.SampleStart() == kStartSample);   // Last seen sample start is the one output.
    msgDecodedStream->RemoveRef();

    // Now, queue up some audio.
    TUint64 expectedSubsamples = 0;
    const TUint samplesExpectedPerMsg = kDataBytes/kByteDepth;
    iNextGeneratedMsg = EMsgAudioPcm;
    msg = iReporter->Pull();
    msg->RemoveRef();
    expectedSubsamples += samplesExpectedPerMsg;
    TEST(iReporter->SubSamples() == expectedSubsamples);




    // Now, insert another track to signify track change.

    // Inject a MsgTrack.
    const TUint kDuration2 = 5678;
    const TUint64 kDurationJiffies2 = (static_cast<TUint64>(kDuration2*iSampleRate)*Jiffies::JiffiesPerSample(iSampleRate))/1000;
    iReporter->TrackChanged(kSpotifyTrackUri, writer, kDuration2);

    // Set audio to be pulled.
    iNextGeneratedMsg = EMsgAudioPcm;

    // Now pull. Should get generated MsgTrack.
    msg = iReporter->Pull();
    msgTrack = msgIdTrack.GetMsg(msg);
    TEST(msgTrack->Track().Uri() == kSpotifyTrackUri);
    TEST(msgTrack->Track().MetaData() == Brn("bitDepth: 16, numChannels: 2, sampleRate: 44100"));
    msgTrack->RemoveRef();
    // Pull again. Should be generated MsgDecodedStream. SampleStart should now be 0, as injected track resets it.
    msg = iReporter->Pull();
    msgDecodedStream = msgIdDecodedStream.GetMsg(msg);
    const DecodedStreamInfo& info2 = msgDecodedStream->StreamInfo();
    TEST(info2.TrackLength() == kDurationJiffies2);
    TEST(info2.SampleStart() == 0);
    msgDecodedStream->RemoveRef();
    // Pull again. Should finally be audio that was queued up.
    msg = iReporter->Pull();
    msg->RemoveRef();
    expectedSubsamples += samplesExpectedPerMsg;
    TEST(iReporter->SubSamples() == expectedSubsamples);
}

void SuiteSpotifyReporter::TestModeSpotifySeek()
{
    // Pass in a MsgMode followed by a MsgDecodedStream mid-way through stream to simulate a seek.
    // First part of this test is already tested by TestModeSpotifyTrackInjected().
    static const Brn kSpotifyTrackUri("spotify://");
    const TUint kDuration = 1234;
    const TUint kDurationJiffies = (static_cast<TUint64>(kDuration*iSampleRate)*Jiffies::JiffiesPerSample(iSampleRate))/1000;
    MockDidlLiteWriter writer;
    iReporter->TrackChanged(kSpotifyTrackUri, writer, kDuration);

    // Pull mode.
    iMode.Replace(kModeSpotify);
    iNextGeneratedMsg = EMsgMode;
    Msg* msg = iReporter->Pull();
    msg->RemoveRef();

    // Set track to be next msg down pipeline.
    // Pull again. Should be in-band pipeline MsgTrack.
    iNextGeneratedMsg = EMsgTrack;
    msg = iReporter->Pull();
    msg->RemoveRef();

    // Pull again. Should be injected track.
    msg = iReporter->Pull();
    msg->RemoveRef();

    // Now, queue up MsgDecodedStream. Should be intercepted and a modified one output.
    static const TUint kStartSample = 88200;
    iSampleStart = kStartSample;
    iNextGeneratedMsg = EMsgDecodedStream;
    msg = iReporter->Pull();
    msg->RemoveRef();

    // Now, queue up some audio.
    TUint64 expectedSubsamples = 0;
    const TUint samplesExpectedPerMsg = kDataBytes/kByteDepth;
    iNextGeneratedMsg = EMsgAudioPcm;
    msg = iReporter->Pull();
    msg->RemoveRef();
    expectedSubsamples += samplesExpectedPerMsg;

    /* ---------- Setup code ends; test case begins. ---------- */

    // MsgDrain, followed by MsgDecodedStream to signify a flush.
    iNextGeneratedMsg = EMsgDrain;
    msg = iReporter->Pull();
    MsgIdentifier<MsgDrain> msgIdDrain;
    MsgDrain* msgDrain = msgIdDrain.GetMsg(msg);
    msgDrain->RemoveRef();

    iSampleStart = 5678;
    iNextGeneratedMsg = EMsgDecodedStream;
    msg = iReporter->Pull();
    MsgIdentifier<MsgDecodedStream> msgIdDecodedStream;
    MsgDecodedStream* msgDecodedStream = msgIdDecodedStream.GetMsg(msg);
    const DecodedStreamInfo& info = msgDecodedStream->StreamInfo();
    TEST(info.TrackLength() == kDurationJiffies);   // Duration should have been updated by SpotifyReporter.
    TEST(info.SampleStart() == iSampleStart);   // Sample start passed with this should be unchanged.
    msgDecodedStream->RemoveRef();

    // Pull some audio.
    iNextGeneratedMsg = EMsgAudioPcm;
    msg = iReporter->Pull();
    msg->RemoveRef();
    expectedSubsamples += samplesExpectedPerMsg;
    TEST(iReporter->SubSamples() == expectedSubsamples);
}



void TestSpotifyReporter()
{
    Runner runner("SpotifyReporter tests\n");
    runner.Add(new SuiteSpotifyReporter());
    runner.Run();
}
