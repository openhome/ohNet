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

class MockSpotifyMetadata;

class MockSpotifyMetadataAllocator
{
public:
    MockSpotifyMetadataAllocator();
    ~MockSpotifyMetadataAllocator();
    MockSpotifyMetadata* Allocate(const Brx& aTrack, const Brx& aArtist, const Brx& aAlbum, const Brx& aAlbumArtUrl, TUint aDurationMs);
    void Destroy(MockSpotifyMetadata* aMetadata);
    TUint DeallocatedCount() const;
private:
    TUint iAllocCount;
    TUint iDeallocCount;
};

class MockSpotifyMetadata : public ISpotifyMetadata, private INonCopyable
{
    friend class MockSpotifyMetadataAllocator;
private:
    MockSpotifyMetadata(MockSpotifyMetadataAllocator& aAllocator, const Brx& aTrack, const Brx& aArtist, const Brx& aAlbum, const Brx& aAlbumArtUrl, TUint aDurationMs);
public: // from ISpotifyMetadata
    const Brx& PlaybackSource() const override;
    const Brx& PlaybackSourceUri() const override;
    const Brx& Track() const override;
    const Brx& TrackUri() const override;
    const Brx& Artist() const override;
    const Brx& ArtistUri() const override;
    const Brx& Album() const override;
    const Brx& AlbumUri() const override;
    const Brx& AlbumCoverUri() const override;
    const Brx& AlbumCoverUrl() const override;
    TUint DurationMs() const override;
    void Destroy() override;
private:
    MockSpotifyMetadataAllocator& iAllocator;
    const Brh iTrack;
    const Brh iArtist;
    const Brh iAlbum;
    const Brh iAlbumArtUrl;
    const TUint iDurationMs;
};

class SuiteSpotifyReporter : public SuiteUnitTest, public IPipelineElementUpstream
{
#define kDefaultMode "null"
#define kModeSpotify "Spotify"
#define kTrackUri "http://host:port/path/file.ext"
#define kTrackTitle "spotify track"
#define kTrackArtist "spotify artist"
#define kTrackAlbum "spotify album"
#define kTrackAlbumArt "http://some/album/art.jpg"
    static const TUint kBitDepth      = 16;
    static const TUint kByteDepth = kBitDepth/8;
    static const TUint kDefaultSampleRate = 44100;
    static const TUint kDefaultNumChannels = 2;
    static const SpeakerProfile kDefaultProfile;
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
    void TestModeSpotifyTrackInjected();
    void TestModeSpotifySeek();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    MockSpotifyMetadataAllocator* iMetadataAllocator;
    SpotifyReporter* iReporter;
    EMsgType iNextGeneratedMsg;
    Msg* iLastMsg;
    BwsMode iMode;
    TUint64 iTrackOffset;
    Bws<1024> iTrackUri;
    TUint iSampleRate;
    TUint iNumChannels;
    SpeakerProfile iProfile;
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


// MockSpotifyMetadataAllocator

MockSpotifyMetadataAllocator::MockSpotifyMetadataAllocator()
    : iAllocCount(0)
    , iDeallocCount(0)
{
}

MockSpotifyMetadataAllocator::~MockSpotifyMetadataAllocator()
{
    // Ensure all metadata has been deallocated.
    ASSERT(iAllocCount == iDeallocCount);
}

MockSpotifyMetadata* MockSpotifyMetadataAllocator::Allocate(const Brx& aTrack, const Brx& aArtist, const Brx& aAlbum, const Brx& aAlbumArtUrl, TUint aDurationMs)
{
    MockSpotifyMetadata* metadata = new MockSpotifyMetadata(*this, aTrack, aArtist, aAlbum, aAlbumArtUrl, aDurationMs);
    iAllocCount++;
    return metadata;
}

void MockSpotifyMetadataAllocator::Destroy(MockSpotifyMetadata* aMetadata)
{
    ASSERT(aMetadata != nullptr);
    iDeallocCount++;
    delete aMetadata;
}

TUint MockSpotifyMetadataAllocator::DeallocatedCount() const
{
    return iDeallocCount;
}


// MockSpotifyMetadata

MockSpotifyMetadata::MockSpotifyMetadata(MockSpotifyMetadataAllocator& aAllocator, const Brx& aTrack, const Brx& aArtist, const Brx& aAlbum, const Brx& aAlbumArtUrl, TUint aDurationMs)
    : iAllocator(aAllocator)
    , iTrack(aTrack)
    , iArtist(aArtist)
    , iAlbum(aAlbum)
    , iAlbumArtUrl(aAlbumArtUrl)
    , iDurationMs(aDurationMs)
{
}

const Brx& MockSpotifyMetadata::PlaybackSource() const
{
    ASSERTS();
    return Brx::Empty();
}

const Brx& MockSpotifyMetadata::PlaybackSourceUri() const
{
    ASSERTS();
    return Brx::Empty();
}

const Brx& MockSpotifyMetadata::Track() const
{
    return iTrack;
}

const Brx& MockSpotifyMetadata::TrackUri() const
{
    ASSERTS();
    return Brx::Empty();
}

const Brx& MockSpotifyMetadata::Artist() const
{
    return iArtist;
}

const Brx& MockSpotifyMetadata::ArtistUri() const
{
    ASSERTS();
    return Brx::Empty();
}

const Brx& MockSpotifyMetadata::Album() const
{
    return iAlbum;
}

const Brx& MockSpotifyMetadata::AlbumUri() const
{
    ASSERTS();
    return Brx::Empty();
}

const Brx& MockSpotifyMetadata::AlbumCoverUri() const
{
    ASSERTS();
    return Brx::Empty();
}

const Brx& MockSpotifyMetadata::AlbumCoverUrl() const
{
    return iAlbumArtUrl;
}

TUint MockSpotifyMetadata::DurationMs() const
{
    return iDurationMs;
}

void MockSpotifyMetadata::Destroy()
{
    iAllocator.Destroy(this);
}


// SuiteSpotifyReporter

const SpeakerProfile SuiteSpotifyReporter::kDefaultProfile(2);

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
    iProfile = kDefaultProfile;
    iBitRate = kDefaultBitrate;
    iTrackLength = kDefaultTrackLength;
    iSampleStart = kDefaultSampleStart;
    MsgFactoryInitParams init;
    init.SetMsgDecodedStreamCount(2);   // SpotifyReporter always caches last seen MsgDecodedStream, so require at least 2 in pipeline.
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 2);   // Require at least 2 Tracks for SpotifyReporter, as it will cache one.
    iMetadataAllocator = new MockSpotifyMetadataAllocator();
    iReporter = new SpotifyReporter(*this, *iMsgFactory, *iTrackFactory);
}

void SuiteSpotifyReporter::TearDown()
{
    delete iReporter;
    delete iMetadataAllocator;
    delete iTrackFactory;
    delete iMsgFactory;
}

Msg* SuiteSpotifyReporter::Pull()
{
    switch (iNextGeneratedMsg)
    {
    case EMsgMode:
        iLastMsg = iMsgFactory->CreateMsgMode(iMode, false, ModeClockPullers(), false, false);
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
        iLastMsg = iMsgFactory->CreateMsgDrain(Functor());
        return iLastMsg;
    case EMsgDelay:
        iLastMsg = iMsgFactory->CreateMsgDelay(0);
        return iLastMsg;
    case EMsgEncodedStream:
        iLastMsg = iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 0, 0, 0, false /* not seekable */, true /* live */, Multiroom::Allowed, nullptr);
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
        iLastMsg = iMsgFactory->CreateMsgDecodedStream(0, iBitRate, kBitDepth, iSampleRate, iNumChannels, Brn(kCodecName), iTrackLength, iSampleStart, kLossless, false, false, false, Multiroom::Allowed, iProfile, nullptr);
        return iLastMsg;
    case EMsgAudioPcm:
        iLastMsg = CreateAudio();
        return iLastMsg;
    case EMsgSilence:
    {
        TUint size = Jiffies::kPerSecond * 10;
        iLastMsg = iMsgFactory->CreateMsgSilence(size, iSampleRate, kBitDepth, iNumChannels);
        return iLastMsg;
    }
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
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, iNumChannels, iSampleRate, kBitDepth, AudioDataEndian::Little, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
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
    iProfile = SpeakerProfile(1);  // mono
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
    const TUint kOffsetMs = 0;

    MockSpotifyMetadata* metadata = iMetadataAllocator->Allocate(Brn(kTrackTitle), Brn(kTrackArtist), Brn(kTrackAlbum), Brn(kTrackAlbumArt), kDurationMs);
    iReporter->TrackChanged(kSpotifyTrackUri, metadata, kOffsetMs);
    static const TUint kSeekMs = 500;
    iReporter->NotifySeek(kSeekMs);

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
    // If in pass-through mode, metadata won't be deallocated until more is passed in, forcing current metadata to be deallocated, or at shutdown (which internal allocator check will catch).
    TEST(iMetadataAllocator->DeallocatedCount() == 0);

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

void SuiteSpotifyReporter::TestModeSpotifyTrackInjected()
{
    // Inject a track to simulate real-world condition where out-of-band track notification is reach SpotifyReporter before MsgMode at Spotify initialisation.
    static const Brn kSpotifyTrackUri("spotify://");
    const TUint kDurationMs = 1234;
    const TUint64 kDurationJiffies = (static_cast<TUint64>(kDurationMs*iSampleRate)*Jiffies::PerSample(iSampleRate))/1000;
    const TUint kOffsetMs = 0;
    MockSpotifyMetadata* metadata = iMetadataAllocator->Allocate(Brn(kTrackTitle), Brn(kTrackArtist), Brn(kTrackAlbum), Brn(kTrackAlbumArt), kDurationMs);
    iReporter->TrackChanged(kSpotifyTrackUri, metadata, kOffsetMs);
    static const TUint kSeekMs = 500;
    static const TUint kSeekSample = (kSeekMs*iSampleRate)/1000;
    iReporter->NotifySeek(kSeekMs);

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

    // Queue up MsgDecodedStream and pull again. Should be injected track.
    iNextGeneratedMsg = EMsgDecodedStream;
    msg = iReporter->Pull();
    msgTrack = msgIdTrack.GetMsg(msg);
    TEST(msgTrack->Track().Uri() == kSpotifyTrackUri);
    TEST(msgTrack->Track().MetaData().Bytes() != 0);
    msgTrack->RemoveRef();
    TEST(iMetadataAllocator->DeallocatedCount() == 1);

    // Pull again. Modified MsgDecodedStream should be output.
    msg = iReporter->Pull();
    MsgIdentifier<MsgDecodedStream> msgIdDecodedStream;
    MsgDecodedStream* msgDecodedStream = msgIdDecodedStream.GetMsg(msg);
    const DecodedStreamInfo& info = msgDecodedStream->StreamInfo();
    TEST(info.TrackLength() == kDurationJiffies);
    TEST(info.SampleStart() == kSeekSample);
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
    const TUint64 kDurationJiffies2 = (static_cast<TUint64>(kDuration2*iSampleRate)*Jiffies::PerSample(iSampleRate))/1000;
    metadata = iMetadataAllocator->Allocate(Brn(kTrackTitle), Brn(kTrackArtist), Brn(kTrackAlbum), Brn(kTrackAlbumArt), kDuration2);
    iReporter->TrackChanged(kSpotifyTrackUri, metadata, kOffsetMs);

    // Set audio to be pulled.
    iNextGeneratedMsg = EMsgAudioPcm;

    // Now pull. Should get generated MsgTrack.
    msg = iReporter->Pull();
    msgTrack = msgIdTrack.GetMsg(msg);
    TEST(msgTrack->Track().Uri() == kSpotifyTrackUri);
    TEST(msgTrack->Track().MetaData().Bytes() != 0);
    msgTrack->RemoveRef();
    TEST(iMetadataAllocator->DeallocatedCount() == 2);
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
    const TUint kDurationJiffies = (static_cast<TUint64>(kDuration*iSampleRate)*Jiffies::PerSample(iSampleRate))/1000;
    const TUint kOffsetMs = 0;
    MockSpotifyMetadata* metadata = iMetadataAllocator->Allocate(Brn(kTrackTitle), Brn(kTrackArtist), Brn(kTrackAlbum), Brn(kTrackAlbumArt), kDuration);
    iReporter->TrackChanged(kSpotifyTrackUri, metadata, kOffsetMs);
    static const TUint kSeekMs = 500;
    iReporter->NotifySeek(kSeekMs);

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

    // Queue up MsgDecodedStream and pull again. Should get injected track.
    iNextGeneratedMsg = EMsgDecodedStream;
    msg = iReporter->Pull();
    msg->RemoveRef();
    TEST(iMetadataAllocator->DeallocatedCount() == 1);

    // Pull again. Delayed MsgDecodedStream should be output with modified info.
    static const TUint kStartSample = 88200;
    iSampleStart = kStartSample;

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

    // Tell SpotifyReporter about a seek.
    static const TUint kSeekMs2 = 250;
    static const TUint kSeekSample2 = (kSeekMs2*iSampleRate)/1000;
    iReporter->NotifySeek(kSeekMs2);

    // MsgDrain, followed by MsgDecodedStream to signify a flush.
    iNextGeneratedMsg = EMsgDrain;
    msg = iReporter->Pull();
    MsgIdentifier<MsgDrain> msgIdDrain;
    MsgDrain* msgDrain = msgIdDrain.GetMsg(msg);
    msgDrain->RemoveRef();

    iNextGeneratedMsg = EMsgDecodedStream;
    msg = iReporter->Pull();
    MsgIdentifier<MsgDecodedStream> msgIdDecodedStream;
    MsgDecodedStream* msgDecodedStream = msgIdDecodedStream.GetMsg(msg);
    const DecodedStreamInfo& info = msgDecodedStream->StreamInfo();
    TEST(info.TrackLength() == kDurationJiffies);   // Duration should have been updated by SpotifyReporter.
    TEST(info.SampleStart() == kSeekSample2);       // Start sample should also have been updated due to NotifySeek() call.
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
