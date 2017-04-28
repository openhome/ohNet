#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/Reporter.h>
#include <OpenHome/Media/Pipeline/SpotifyReporter.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Tests/TestPipe.h>

#include <limits>
#include <string.h>
#include <vector>

namespace OpenHome {
namespace Media {
namespace Test {

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

class MockPipelineElementUpstream : public IPipelineElementUpstream
{
public:
    MockPipelineElementUpstream(TUint aMaxMsgs);
    ~MockPipelineElementUpstream();
    void Enqueue(Msg* aMsg);
private: // from IPipelineElementUpstream
    Msg* Pull() override;
private:
    FifoLiteDynamic<Msg*> iMsgs;
    Mutex iLock;
};

class WriterBool : private INonCopyable
{
public:
    WriterBool(IWriter& aWriter);
    void WriteBool(TBool aBool);
private:
    IWriter& iWriter;
};

class MockMsgProcessor : public IMsgProcessor, private INonCopyable
{
private:
    static const TUint kMaxMsgBytes = OpenHome::Test::TestPipeDynamic::kMaxMsgBytes;
public:
    MockMsgProcessor(OpenHome::Test::ITestPipeWritable& aTestPipe);
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
    OpenHome::Test::ITestPipeWritable& iTestPipe;
};

class SuiteSpotifyReporter : public TestFramework::SuiteUnitTest
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
private:
    MsgAudio* CreateAudio(TUint aNumChannels, TUint aSampleRate, TUint64& aTrackOffset);
    void TestMsgsCauseAssertion();
    void TestMsgsPassedThroughNoSamplesInPipeline();
    void TestMsgsPassedThroughSamplesInPipeline();
    void TestMsgModeResets();
    void TestSubSamples();
    void TestSampleRateChange();
    void TestNumChannelsChange();
    void TestInvalidSampleRate();
    void TestInvalidNumChannels();
    void TestPassThroughInjectTrack();
    void TestModeSpotifyTrackInjected();
    void TestModeSpotifySeek();
private:
    OpenHome::Test::TestPipeDynamic* iTestPipe;
    MockPipelineElementUpstream* iUpstream;
    MockMsgProcessor* iMsgProcessor;
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    MockSpotifyMetadataAllocator* iMetadataAllocator;
    SpotifyReporter* iReporter;
};

} // namespace Test
} // namespace Media
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Test;


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


// MockPipelineElementUpstream

MockPipelineElementUpstream::MockPipelineElementUpstream(TUint aMaxMsgs)
    : iMsgs(aMaxMsgs)
    , iLock("MPEU")
{
}

MockPipelineElementUpstream::~MockPipelineElementUpstream()
{
    AutoMutex _(iLock);
    ASSERT(iMsgs.SlotsUsed() == 0);
}

void MockPipelineElementUpstream::Enqueue(Msg* aMsg)
{
    AutoMutex _(iLock);
    ASSERT(iMsgs.SlotsFree() > 0);
    iMsgs.Write(aMsg);
}

Msg* MockPipelineElementUpstream::Pull()
{
    AutoMutex _(iLock);
    ASSERT(iMsgs.SlotsUsed() > 0);
    auto* m = iMsgs.Read();
    return m;
}


// WriterBool

WriterBool::WriterBool(IWriter& aWriter)
    : iWriter(aWriter)
{
}

void WriterBool::WriteBool(TBool aBool)
{
    if (aBool) {
        iWriter.Write('Y');
    }
    else {
        iWriter.Write('N');
    }
}


// MockMsgProcessor

MockMsgProcessor::MockMsgProcessor(OpenHome::Test::ITestPipeWritable& aTestPipe)
    : iTestPipe(aTestPipe)
{
}

Msg* MockMsgProcessor::ProcessMsg(MsgMode* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgMode ");
    buf.Append(aMsg->Mode());
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgTrack* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgTrack ");
    WriterBuffer writerBuffer(buf);
    WriterAscii writerAscii(writerBuffer);
    WriterBool writerBool(writerBuffer);
    writerAscii.Write(aMsg->Track().Uri());
    writerAscii.WriteSpace();
    writerAscii.WriteUint(aMsg->Track().Id());
    writerAscii.WriteSpace();
    writerBool.WriteBool(aMsg->StartOfStream());
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgDrain* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgDrain ");
    WriterBuffer writerBuffer(buf);
    WriterAscii writerAscii(writerBuffer);
    writerAscii.WriteUint(aMsg->Id());
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgDelay* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgDelay ");
    WriterBuffer writerBuffer(buf);
    WriterAscii writerAscii(writerBuffer);
    writerAscii.WriteUint(aMsg->DelayJiffies());
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgEncodedStream* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgEncodedStream ");
    WriterBuffer writerBuffer(buf);
    WriterAscii writerAscii(writerBuffer);
    WriterBool writerBool(writerBuffer);
    writerAscii.Write(aMsg->Uri());
    writerAscii.WriteSpace();
    writerAscii.WriteUint64(aMsg->TotalBytes());
    writerAscii.WriteSpace();
    writerAscii.WriteUint64(aMsg->StartPos());
    writerAscii.WriteSpace();
    writerAscii.WriteUint(aMsg->StreamId());
    writerAscii.WriteSpace();
    writerBool.WriteBool(aMsg->Seekable());
    writerAscii.WriteSpace();
    writerBool.WriteBool(aMsg->Live());
    writerAscii.WriteSpace();
    writerBool.WriteBool(aMsg->RawPcm());
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgAudioEncoded* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgAudioEncoded ");
    WriterBuffer writerBuffer(buf);
    WriterAscii writerAscii(writerBuffer);
    writerAscii.WriteUint(aMsg->Bytes());
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgMetaText* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgMetaText ");
    buf.Append(aMsg->MetaText());
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgStreamInterrupted");
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgHalt* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgHalt ");
    WriterBuffer writerBuffer(buf);
    WriterAscii writerAscii(writerBuffer);
    writerAscii.WriteUint(aMsg->Id());
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgFlush* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgFlush ");
    WriterBuffer writerBuffer(buf);
    WriterAscii writerAscii(writerBuffer);
    writerAscii.WriteUint(aMsg->Id());
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgWait* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgWait");
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgDecodedStream* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgDecodedStream ");
    WriterBuffer writerBuffer(buf);
    WriterAscii writerAscii(writerBuffer);
    WriterBool writerBool(writerBuffer);
    writerAscii.WriteUint(aMsg->StreamInfo().StreamId());
    writerAscii.WriteSpace();
    writerAscii.WriteUint(aMsg->StreamInfo().BitRate());
    writerAscii.WriteSpace();
    writerAscii.WriteUint(aMsg->StreamInfo().BitDepth());
    writerAscii.WriteSpace();
    writerAscii.WriteUint(aMsg->StreamInfo().SampleRate());
    writerAscii.WriteSpace();
    writerAscii.WriteUint(aMsg->StreamInfo().NumChannels());
    writerAscii.WriteSpace();
    writerAscii.Write(aMsg->StreamInfo().CodecName());
    writerAscii.WriteSpace();
    writerAscii.WriteUint64(aMsg->StreamInfo().TrackLength());
    writerAscii.WriteSpace();
    writerAscii.WriteUint64(aMsg->StreamInfo().SampleStart());
    writerAscii.WriteSpace();
    writerBool.WriteBool(aMsg->StreamInfo().Lossless());
    writerAscii.WriteSpace();
    writerBool.WriteBool(aMsg->StreamInfo().Seekable());
    writerAscii.WriteSpace();
    writerBool.WriteBool(aMsg->StreamInfo().Live());
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgBitRate* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgBitRate ");
    WriterBuffer writerBuffer(buf);
    WriterAscii writerAscii(writerBuffer);
    writerAscii.WriteUint(aMsg->BitRate());
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgAudioPcm* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgAudioPcm ");
    WriterBuffer writerBuffer(buf);
    WriterAscii writerAscii(writerBuffer);
    writerAscii.WriteUint(aMsg->Jiffies());
    writerAscii.WriteSpace();
    writerAscii.WriteUint64(aMsg->TrackOffset());
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgSilence* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgSilence ");
    WriterBuffer writerBuffer(buf);
    WriterAscii writerAscii(writerBuffer);
    writerAscii.WriteUint(aMsg->Jiffies());
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgPlayable* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgPlayable ");
    WriterBuffer writerBuffer(buf);
    WriterAscii writerAscii(writerBuffer);
    writerAscii.WriteUint(aMsg->Bytes());
    writerAscii.WriteSpace();
    writerAscii.WriteUint(aMsg->Jiffies());
    iTestPipe.Write(buf);
    return aMsg;
}

Msg* MockMsgProcessor::ProcessMsg(MsgQuit* aMsg)
{
    Bws<kMaxMsgBytes> buf("MMP::ProcessMsg MsgQuit");
    iTestPipe.Write(buf);
    return aMsg;
}


// SuiteSpotifyReporter

SuiteSpotifyReporter::SuiteSpotifyReporter()
    : SuiteUnitTest("SuiteSpotifyReporter")
{
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestMsgsCauseAssertion), "TestMsgsCauseAssertion");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestMsgsPassedThroughNoSamplesInPipeline), "TestMsgsPassedThroughNoSamplesInPipeline");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestMsgsPassedThroughSamplesInPipeline), "TestMsgsPassedThroughSamplesInPipeline");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestMsgModeResets), "TestMsgModeResets");
    AddTest(MakeFunctor(*this, &SuiteSpotifyReporter::TestSubSamples), "TestSubSamples");
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
    iTestPipe = new OpenHome::Test::TestPipeDynamic();
    iUpstream = new MockPipelineElementUpstream(10);
    iMsgProcessor = new MockMsgProcessor(*iTestPipe);

    MsgFactoryInitParams init;
    init.SetMsgDecodedStreamCount(2);   // SpotifyReporter always caches last seen MsgDecodedStream, so require at least 2 in pipeline.
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 2);   // Require at least 2 Tracks for SpotifyReporter, as it will cache one.
    iMetadataAllocator = new MockSpotifyMetadataAllocator();

    iReporter = new SpotifyReporter(*iUpstream, *iMsgFactory, *iTrackFactory);

    TEST(iTestPipe->ExpectEmpty());
}

void SuiteSpotifyReporter::TearDown()
{
    delete iReporter;
    delete iMetadataAllocator;
    delete iTrackFactory;
    delete iMsgFactory;

    delete iMsgProcessor;
    delete iUpstream;
    TEST(iTestPipe->ExpectEmpty());
    delete iTestPipe;
}

MsgAudio* SuiteSpotifyReporter::CreateAudio(TUint aNumChannels, TUint aSampleRate, TUint64& aTrackOffset)
{
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0xff, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, aNumChannels, aSampleRate, kBitDepth, AudioDataEndian::Little, aTrackOffset);
    aTrackOffset += audio->Jiffies();
    return audio;
}

void SuiteSpotifyReporter::TestMsgsCauseAssertion()
{
    // Don't expect to see certain msgs at the point in pipeline where
    // SpotifyReporter is placed.

    // MsgEncodedStream
    MsgEncodedStream* msgEncodedStream = iMsgFactory->CreateMsgEncodedStream(Brn("spotify://"), Brx::Empty(), 1234, 0, 1, true, false, Multiroom::Allowed, nullptr);
    iUpstream->Enqueue(msgEncodedStream);
    TEST_THROWS(iReporter->Pull(), AssertionFailed);
    msgEncodedStream->RemoveRef();   // Avoid memory leaks.

    // MsgAudioEncoded
    Brn audioEncodedData("01234567");
    MsgAudioEncoded* msgAudioEncoded = iMsgFactory->CreateMsgAudioEncoded(audioEncodedData);
    iUpstream->Enqueue(msgAudioEncoded);
    TEST_THROWS(iReporter->Pull(), AssertionFailed);
    msgAudioEncoded->RemoveRef();   // Avoid memory leaks.

    // MsgFlush
    MsgFlush* msgFlush = iMsgFactory->CreateMsgFlush(1);
    iUpstream->Enqueue(msgFlush);
    TEST_THROWS(iReporter->Pull(), AssertionFailed);
    msgFlush->RemoveRef();   // Avoid memory leaks.

    // MsgPlayable
    // Need to first create a MsgAudioPcm, and then extract a MsgPlayable from it.
    Brn msgAudioPcmData("01234567");
    MsgAudioPcm* msgAudioPcm = iMsgFactory->CreateMsgAudioPcm(msgAudioPcmData, 2, 44100, 16, AudioDataEndian::Little, 0);
    MsgPlayable* msgPlayable = msgAudioPcm->CreatePlayable(); // Removes ref from owning MsgAudioPcm.
    iUpstream->Enqueue(msgPlayable);
    TEST_THROWS(iReporter->Pull(), AssertionFailed);
    msgPlayable->RemoveRef();   // Avoid memory leaks.
}

void SuiteSpotifyReporter::TestMsgsPassedThroughNoSamplesInPipeline()
{
    // All msgs should pass through unchanged. However, only MsgMode,
    // MsgDecodedStream and MsgAudioPcm should change the state of the
    // SpotifyReporter, so test the others.

    Track* track = iTrackFactory->CreateTrack(Brn("spotify://"), Brn("Spotify track meta text"));
    iUpstream->Enqueue(iMsgFactory->CreateMsgTrack(*track));
    track->RemoveRef();

    iUpstream->Enqueue(iMsgFactory->CreateMsgDelay(0));
    iUpstream->Enqueue(iMsgFactory->CreateMsgMetaText(Brn("Spotify meta text")));
    iUpstream->Enqueue(iMsgFactory->CreateMsgHalt());
    iUpstream->Enqueue(iMsgFactory->CreateMsgWait());
    TUint sizeJiffies = Jiffies::kPerSecond * 10;
    iUpstream->Enqueue(iMsgFactory->CreateMsgSilence(sizeJiffies, 44100, 16, 2));
    iUpstream->Enqueue(iMsgFactory->CreateMsgQuit());

    for (TUint i=0; i<7; i++) {
        Msg* msg = iReporter->Pull();
        msg->Process(*iMsgProcessor);
        msg->RemoveRef();
        // No audio, so no subsamples to report.
        TEST(iReporter->SubSamples() == 0);
    }

    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 1 Y")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgDelay 0")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgMetaText Spotify meta text")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgHalt 0")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgWait")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgSilence 564480000")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgQuit")));
}

void SuiteSpotifyReporter::TestMsgsPassedThroughSamplesInPipeline()
{
    // First, put some audio into pipeline.
    iUpstream->Enqueue(iMsgFactory->CreateMsgMode(Brn("null")));
    Track* track = iTrackFactory->CreateTrack(Brn("spotify://"), Brn("Spotify track meta text"));
    iUpstream->Enqueue(iMsgFactory->CreateMsgTrack(*track));
    track->RemoveRef();
    iUpstream->Enqueue(iMsgFactory->CreateMsgDecodedStream(0, 705600, 16, 44100, 2, Brn("CODC"), 3386880000, 0, true, false, false, false, Multiroom::Allowed, SpeakerProfile(2), nullptr));
    TUint64 trackOffset = 0;
    iUpstream->Enqueue(CreateAudio(2, 44100, trackOffset));
    
    for (TUint i=0; i<4; i++) {
        Msg* msg = iReporter->Pull();
        msg->Process(*iMsgProcessor);
        msg->RemoveRef();
    }
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgMode null")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 1 Y")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgDecodedStream 0 705600 16 44100 2 CODC 3386880000 0 Y N N")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 0")));

    // Even although MsgAudioPcm was passed through, it was in a stream with a
    // non-Spotify MsgMode, so 0 subsamples should be reported.
    TEST(iReporter->SubSamples() == 0);
}

void SuiteSpotifyReporter::TestMsgModeResets()
{
    const TUint samplesExpected = kDataBytes/kByteDepth;

    MockSpotifyMetadata* metadata = iMetadataAllocator->Allocate(Brn(kTrackTitle), Brn(kTrackArtist), Brn(kTrackAlbum), Brn(kTrackAlbumArt), 1234);
    iReporter->TrackChanged(Brn("spotify://"), metadata, 0);

    // Send in a Spotify MsgMode.
    iUpstream->Enqueue(iMsgFactory->CreateMsgMode(Brn("Spotify")));
    Track* track = iTrackFactory->CreateTrack(Brn("spotify://"), Brn("Spotify track meta text"));
    iUpstream->Enqueue(iMsgFactory->CreateMsgTrack(*track));
    track->RemoveRef();
    iUpstream->Enqueue(iMsgFactory->CreateMsgDecodedStream(0, 705600, 16, 44100, 2, Brn("CODC"), 3386880000, 0, true, false, false, false, Multiroom::Allowed, SpeakerProfile(2), nullptr));
    TUint64 trackOffset = 0;
    iUpstream->Enqueue(CreateAudio(2, 44100, trackOffset));

    for (TUint i=0; i<5; i++) {
        Msg* msg = iReporter->Pull();
        msg->Process(*iMsgProcessor);
        msg->RemoveRef();
    }
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgMode Spotify")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 1 Y")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 2 N")));
    // Track duration is from track message injected into SpotifyReporter.
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgDecodedStream 0 705600 16 44100 2 CODC 69656832 0 Y N N")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 0")));

    TEST(iReporter->SubSamples() == samplesExpected);

    // Now, send another Spotify MsgMode, which should reset sample count.
    iUpstream->Enqueue(iMsgFactory->CreateMsgMode(Brn("Spotify")));
    Msg* msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgMode Spotify")));
    TEST(iReporter->SubSamples() == 0);
}

void SuiteSpotifyReporter::TestSubSamples()
{
    // FIXME - vary number of samples in msgs to catch overflow issue
    // Will need to have an iDataBytes value, instead of kDataBytes, that can
    // be varied
    TUint samplesExpectedPerMsg = kDataBytes/kByteDepth;
    TUint samplesExpected = samplesExpectedPerMsg;

    // Set up sequence.
    MockSpotifyMetadata* metadata = iMetadataAllocator->Allocate(Brn(kTrackTitle), Brn(kTrackArtist), Brn(kTrackAlbum), Brn(kTrackAlbumArt), 1234);
    iReporter->TrackChanged(Brn("spotify://"), metadata, 0);

    // Send in a Spotify MsgMode.
    iUpstream->Enqueue(iMsgFactory->CreateMsgMode(Brn("Spotify")));
    Track* track = iTrackFactory->CreateTrack(Brn("spotify://"), Brn("Spotify track meta text"));
    iUpstream->Enqueue(iMsgFactory->CreateMsgTrack(*track));
    track->RemoveRef();
    iUpstream->Enqueue(iMsgFactory->CreateMsgDecodedStream(0, 705600, 16, 44100, 2, Brn("CODC"), 3386880000, 0, true, false, false, false, Multiroom::Allowed, SpeakerProfile(2), nullptr));

    for (TUint i=0; i<4; i++) {
        Msg* msg = iReporter->Pull();
        msg->Process(*iMsgProcessor);
        msg->RemoveRef();
    }
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgMode Spotify")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 1 Y")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 2 N")));
    // Track duration is from track message injected into SpotifyReporter.
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgDecodedStream 0 705600 16 44100 2 CODC 69656832 0 Y N N")));

    TEST(iReporter->SubSamples() == 0);


    // Send audio.
    TUint64 trackOffset = 0;
    for (TUint i=0; i<3; i++) {
        iUpstream->Enqueue(CreateAudio(2, 44100, trackOffset));
        Msg* msg = iReporter->Pull();
        msg->Process(*iMsgProcessor);
        msg->RemoveRef();
        TEST(iReporter->SubSamples() == samplesExpected);
        samplesExpected += samplesExpectedPerMsg;
    }
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 0")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 983040")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 1966080")));
}

void SuiteSpotifyReporter::TestSampleRateChange()
{
    TUint samplesExpectedPerMsg = kDataBytes/kByteDepth;
    TUint samplesExpected = 0;

    // Set up sequence.
    MockSpotifyMetadata* metadata = iMetadataAllocator->Allocate(Brn(kTrackTitle), Brn(kTrackArtist), Brn(kTrackAlbum), Brn(kTrackAlbumArt), 1234);
    iReporter->TrackChanged(Brn("spotify://"), metadata, 0);

    // Send in a Spotify MsgMode.
    iUpstream->Enqueue(iMsgFactory->CreateMsgMode(Brn("Spotify")));
    Track* track = iTrackFactory->CreateTrack(Brn("spotify://"), Brn("Spotify track meta text"));
    iUpstream->Enqueue(iMsgFactory->CreateMsgTrack(*track));
    track->RemoveRef();
    iUpstream->Enqueue(iMsgFactory->CreateMsgDecodedStream(0, 705600, 16, 44100, 2, Brn("CODC"), 3386880000, 0, true, false, false, false, Multiroom::Allowed, SpeakerProfile(2), nullptr));

    for (TUint i=0; i<4; i++) {
        Msg* msg = iReporter->Pull();
        msg->Process(*iMsgProcessor);
        msg->RemoveRef();
    }
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgMode Spotify")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 1 Y")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 2 N")));
    // Track duration is from track message injected into SpotifyReporter.
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgDecodedStream 0 705600 16 44100 2 CODC 69656832 0 Y N N")));

    TEST(iReporter->SubSamples() == 0);


    // Send audio.
    TUint64 trackOffset = 0;
    for (TUint i=0; i<3; i++) {
        iUpstream->Enqueue(CreateAudio(2, 44100, trackOffset));
        Msg* msg = iReporter->Pull();
        msg->Process(*iMsgProcessor);
        msg->RemoveRef();
        samplesExpected += samplesExpectedPerMsg;
        TEST(iReporter->SubSamples() == samplesExpected);
    }
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 0")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 983040")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 1966080")));


    // Now, change sample rate and send more audio.
    Track* track2 = iTrackFactory->CreateTrack(Brn("spotify://"), Brn("Spotify track meta text 2"));
    iUpstream->Enqueue(iMsgFactory->CreateMsgTrack(*track2));
    track2->RemoveRef();
    iUpstream->Enqueue(iMsgFactory->CreateMsgDecodedStream(0, 768000, 16, 48000, 2, Brn("CODC"), 3386880000, 0, true, false, false, false, Multiroom::Allowed, SpeakerProfile(2), nullptr));
    for (TUint i=0; i<2; i++) {
        Msg* msg = iReporter->Pull();
        msg->Process(*iMsgProcessor);
        msg->RemoveRef();
    }
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 3 Y")));
    // Track duration is from track message injected into SpotifyReporter.
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgDecodedStream 0 768000 16 48000 2 CODC 69656832 0 Y N N")));

    // Send audio.
    iUpstream->Enqueue(CreateAudio(2, 48000, trackOffset));
    Msg* msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();

    samplesExpected += samplesExpectedPerMsg;
    TEST(iReporter->SubSamples() == samplesExpected);

    // There are still the same number of samples per message, as the same
    // number of bytes is going into same message.
    // However, as the sample rate has increased, while the number of samples
    // has remained the same, there will be fewer samples per time unit
    // (i.e., jiffies, in this case).

    // 3072 bytes in this message.
    // 3072 / 2 bytes (for byte depth) = 1536 samples in message (across 2 channels).
    // 1536 / 2 (for number of channels) = 768 samples per channel.
    // 56648000 / 48000 = 1176 jiffies per sample @ 48000KHz.
    // 768 * 1176 = 903168 jiffies in this message.
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 903168 2949120")));
}

void SuiteSpotifyReporter::TestNumChannelsChange()
{
    TUint samplesExpectedPerMsg = kDataBytes/kByteDepth;
    TUint samplesExpected = 0;

    // Set up sequence.
    MockSpotifyMetadata* metadata = iMetadataAllocator->Allocate(Brn(kTrackTitle), Brn(kTrackArtist), Brn(kTrackAlbum), Brn(kTrackAlbumArt), 1234);
    iReporter->TrackChanged(Brn("spotify://"), metadata, 0);

    // Send in a Spotify MsgMode.
    iUpstream->Enqueue(iMsgFactory->CreateMsgMode(Brn("Spotify")));
    Track* track = iTrackFactory->CreateTrack(Brn("spotify://"), Brn("Spotify track meta text"));
    iUpstream->Enqueue(iMsgFactory->CreateMsgTrack(*track));
    track->RemoveRef();
    iUpstream->Enqueue(iMsgFactory->CreateMsgDecodedStream(0, 705600, 16, 44100, 2, Brn("CODC"), 3386880000, 0, true, false, false, false, Multiroom::Allowed, SpeakerProfile(2), nullptr));

    for (TUint i=0; i<4; i++) {
        Msg* msg = iReporter->Pull();
        msg->Process(*iMsgProcessor);
        msg->RemoveRef();
    }
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgMode Spotify")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 1 Y")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 2 N")));
    // Track duration is from track message injected into SpotifyReporter.
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgDecodedStream 0 705600 16 44100 2 CODC 69656832 0 Y N N")));

    TEST(iReporter->SubSamples() == 0);


    // Send audio.
    TUint64 trackOffset = 0;
    for (TUint i=0; i<3; i++) {
        iUpstream->Enqueue(CreateAudio(2, 44100, trackOffset));
        Msg* msg = iReporter->Pull();
        msg->Process(*iMsgProcessor);
        msg->RemoveRef();
        samplesExpected += samplesExpectedPerMsg;
        TEST(iReporter->SubSamples() == samplesExpected);
    }
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 0")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 983040")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 1966080")));


    // Now, change number of channels and send more audio.
    Track* track2 = iTrackFactory->CreateTrack(Brn("spotify://"), Brn("Spotify track meta text"));
    iUpstream->Enqueue(iMsgFactory->CreateMsgTrack(*track2));
    track2->RemoveRef();
    iUpstream->Enqueue(iMsgFactory->CreateMsgDecodedStream(0, 705600, 16, 44100, 1, Brn("CODC"), 3386880000, 0, true, false, false, false, Multiroom::Allowed, SpeakerProfile(1), nullptr));
    for (TUint i=0; i<2; i++) {
        Msg* msg = iReporter->Pull();
        msg->Process(*iMsgProcessor);
        msg->RemoveRef();
    }
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 3 Y")));
    // Track duration is from track message injected into SpotifyReporter.
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgDecodedStream 0 705600 16 44100 1 CODC 69656832 0 Y N N")));

    for (TUint i=0; i<3; i++) {
        iUpstream->Enqueue(CreateAudio(1, 44100, trackOffset));
        Msg* msg = iReporter->Pull();
        msg->Process(*iMsgProcessor);
        msg->RemoveRef();
        samplesExpected += samplesExpectedPerMsg;
        TEST(iReporter->SubSamples() == samplesExpected);
    }
    // Number of jiffies is now double that previously reported, due to same
    // amount of data in each message, but only half the number of channels.
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 1966080 2949120")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 1966080 4915200")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 1966080 6881280")));
}

void SuiteSpotifyReporter::TestInvalidSampleRate()
{
    const TUint sampleRate = 0; // Invalid sample rate.
    MockSpotifyMetadata* metadata = iMetadataAllocator->Allocate(Brn(kTrackTitle), Brn(kTrackArtist), Brn(kTrackAlbum), Brn(kTrackAlbumArt), 1234);
    iReporter->TrackChanged(Brn("spotify://"), metadata, 0);

    // Send in a Spotify MsgMode.
    iUpstream->Enqueue(iMsgFactory->CreateMsgMode(Brn("Spotify")));
    Track* track = iTrackFactory->CreateTrack(Brn("spotify://"), Brn("Spotify track meta text"));
    iUpstream->Enqueue(iMsgFactory->CreateMsgTrack(*track));
    track->RemoveRef();
    MsgDecodedStream* decodedStream = iMsgFactory->CreateMsgDecodedStream(0, 705600, 16, sampleRate, 2, Brn("CODC"), 3386880000, 0, true, false, false, false, Multiroom::Allowed, SpeakerProfile(2), nullptr);
    iUpstream->Enqueue(decodedStream);

    for (TUint i=0; i<2; i++) {
        Msg* msg = iReporter->Pull();
        msg->Process(*iMsgProcessor);
        msg->RemoveRef();
    }
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgMode Spotify")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 1 Y")));

    TEST_THROWS(iReporter->Pull(), AssertionFailed);
    decodedStream->RemoveRef(); // Avoid memory leaks.
}

void SuiteSpotifyReporter::TestInvalidNumChannels()
{
    const TUint channels = 0;
    const SpeakerProfile profile(0);

    MockSpotifyMetadata* metadata = iMetadataAllocator->Allocate(Brn(kTrackTitle), Brn(kTrackArtist), Brn(kTrackAlbum), Brn(kTrackAlbumArt), 1234);
    iReporter->TrackChanged(Brn("spotify://"), metadata, 0);

    // Send in a Spotify MsgMode.
    iUpstream->Enqueue(iMsgFactory->CreateMsgMode(Brn("Spotify")));
    Track* track = iTrackFactory->CreateTrack(Brn("spotify://"), Brn("Spotify track meta text"));
    iUpstream->Enqueue(iMsgFactory->CreateMsgTrack(*track));
    track->RemoveRef();
    MsgDecodedStream* decodedStream = iMsgFactory->CreateMsgDecodedStream(0, 705600, 16, 44100, channels, Brn("CODC"), 3386880000, 0, true, false, false, false, Multiroom::Allowed, profile, nullptr);
    iUpstream->Enqueue(decodedStream);

    for (TUint i=0; i<2; i++) {
        Msg* msg = iReporter->Pull();
        msg->Process(*iMsgProcessor);
        msg->RemoveRef();
    }
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgMode Spotify")));
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 1 Y")));

    TEST_THROWS(iReporter->Pull(), AssertionFailed);
    decodedStream->RemoveRef(); // Avoid memory leaks.
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

    // NOT "Spotify" mode.
    iUpstream->Enqueue(iMsgFactory->CreateMsgMode(Brn("null")));
    Msg* msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgMode null")));

    Track* track = iTrackFactory->CreateTrack(Brn("spotify://"), Brn("Spotify track meta text"));
    iUpstream->Enqueue(iMsgFactory->CreateMsgTrack(*track));
    track->RemoveRef();
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 1 Y")));
    msg->RemoveRef();
    // If in pass-through mode, metadata won't be deallocated until more is passed in, forcing current metadata to be deallocated, or at shutdown (which internal allocator check will catch).
    TEST(iMetadataAllocator->DeallocatedCount() == 0);

    iUpstream->Enqueue(iMsgFactory->CreateMsgDecodedStream(0, 705600, 16, 44100, 2, Brn("CODC"), 3386880000, 0, true, false, false, false, Multiroom::Allowed, SpeakerProfile(2), nullptr));
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    // Check a modified MsgDecodedStream wasn't inserted (should report track
    // duration of the MsgDecodedStream sent down pipeline, instead of injected
    // track).
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgDecodedStream 0 705600 16 44100 2 CODC 3386880000 0 Y N N")));
    msg->RemoveRef();

    // Pull some audio to check that no modified MsgTrack or MsgDecodedStream is injected.
    TUint64 trackOffset = 0;
    iUpstream->Enqueue(CreateAudio(2, 44100, trackOffset));
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 0")));
    TEST(iReporter->SubSamples() == 0); // Was not "Spotify" mode, so no subsamples should be reported.
}

void SuiteSpotifyReporter::TestModeSpotifyTrackInjected()
{
    // Inject a track to simulate real-world condition where out-of-band track notification is reach SpotifyReporter before MsgMode at Spotify initialisation.
    static const Brn kSpotifyTrackUri("spotify://");
    const TUint kDurationMs = 1234;
    const TUint kOffsetMs = 0;
    MockSpotifyMetadata* metadata = iMetadataAllocator->Allocate(Brn(kTrackTitle), Brn(kTrackArtist), Brn(kTrackAlbum), Brn(kTrackAlbumArt), kDurationMs);
    iReporter->TrackChanged(kSpotifyTrackUri, metadata, kOffsetMs);
    static const TUint kSeekMs = 500; // Sample 22050 @ 44.1KHz.
    iReporter->NotifySeek(kSeekMs);

    // Pull mode.
    iUpstream->Enqueue(iMsgFactory->CreateMsgMode(Brn("Spotify")));
    Msg* msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgMode Spotify")));

    // Set track to be next msg down pipeline.
    // Pull again. Should be in-band pipeline MsgTrack.
    Track* track = iTrackFactory->CreateTrack(Brn("spotify://"), Brn("Spotify track meta text"));
    iUpstream->Enqueue(iMsgFactory->CreateMsgTrack(*track));
    track->RemoveRef();
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 1 Y")));

    // Queue up MsgDecodedStream and pull again. Should be injected track.
    iUpstream->Enqueue(iMsgFactory->CreateMsgDecodedStream(0, 705600, 16, 44100, 2, Brn("CODC"), 3386880000, 0, true, false, false, false, Multiroom::Allowed, SpeakerProfile(2), nullptr));
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 2 N")));
    TEST(iMetadataAllocator->DeallocatedCount() == 1);

    // Pull again. Modified MsgDecodedStream should be output.
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    // Track duration is from track message injected into SpotifyReporter.
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgDecodedStream 0 705600 16 44100 2 CODC 69656832 22050 Y N N")));

    // Now, queue up some audio.
    const TUint samplesExpectedPerMsg = kDataBytes/kByteDepth;
    TUint samplesExpected = samplesExpectedPerMsg;
    TUint64 trackOffset = 0;
    iUpstream->Enqueue(CreateAudio(2, 44100, trackOffset));
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 0")));
    TEST(iReporter->SubSamples() == samplesExpected);


    // Now, insert another track to signify track change.

    // Inject a MsgTrack.
    const TUint kDuration2 = 5678;
    metadata = iMetadataAllocator->Allocate(Brn(kTrackTitle), Brn(kTrackArtist), Brn(kTrackAlbum), Brn(kTrackAlbumArt), kDuration2);
    iReporter->TrackChanged(kSpotifyTrackUri, metadata, kOffsetMs);

    // Now pull. Should get generated MsgTrack.
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 3 N")));
    TEST(iMetadataAllocator->DeallocatedCount() == 2);
    // Pull again. Should be generated MsgDecodedStream. SampleStart should now be 0, as injected track resets it.
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgDecodedStream 0 705600 16 44100 2 CODC 320511744 0 Y N N")));
    // Pull audio.
    iUpstream->Enqueue(CreateAudio(2, 44100, trackOffset));
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    samplesExpected += samplesExpectedPerMsg;
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 983040")));
    TEST(iReporter->SubSamples() == samplesExpected);
}

void SuiteSpotifyReporter::TestModeSpotifySeek()
{
    // Pass in a MsgMode followed by a MsgDecodedStream mid-way through stream to simulate a seek.
    // First part of this test is already tested by TestModeSpotifyTrackInjected().
    static const Brn kSpotifyTrackUri("spotify://");
    const TUint kDuration = 1234;
    const TUint kOffsetMs = 0;
    MockSpotifyMetadata* metadata = iMetadataAllocator->Allocate(Brn(kTrackTitle), Brn(kTrackArtist), Brn(kTrackAlbum), Brn(kTrackAlbumArt), kDuration);
    iReporter->TrackChanged(kSpotifyTrackUri, metadata, kOffsetMs);
    static const TUint kSeekMs = 500; // Sample 22050 @ 44.1KHz.
    iReporter->NotifySeek(kSeekMs);

    // Pull mode.
    iUpstream->Enqueue(iMsgFactory->CreateMsgMode(Brn("Spotify")));
    Msg* msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgMode Spotify")));

    // Set track to be next msg down pipeline.
    // Pull again. Should be in-band pipeline MsgTrack.
    Track* track = iTrackFactory->CreateTrack(Brn("spotify://"), Brn("Spotify track meta text"));
    iUpstream->Enqueue(iMsgFactory->CreateMsgTrack(*track));
    track->RemoveRef();
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 1 Y")));

    // Queue up MsgDecodedStream and pull again. Should get injected track.
    iUpstream->Enqueue(iMsgFactory->CreateMsgDecodedStream(0, 705600, 16, 44100, 2, Brn("CODC"), 3386880000, 0, true, false, false, false, Multiroom::Allowed, SpeakerProfile(2), nullptr));
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgTrack spotify:// 2 N")));
    TEST(iMetadataAllocator->DeallocatedCount() == 1);

    // Pull again. Delayed MsgDecodedStream should be output with modified info.
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgDecodedStream 0 705600 16 44100 2 CODC 69656832 22050 Y N N")));

    // Now, queue up some audio.
    const TUint samplesExpectedPerMsg = kDataBytes/kByteDepth;
    TUint samplesExpected = samplesExpectedPerMsg;
    TUint64 trackOffset = 0;
    iUpstream->Enqueue(CreateAudio(2, 44100, trackOffset));
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 0")));
    TEST(iReporter->SubSamples() == samplesExpected);

    /* ---------- Setup code ends; test case begins. ---------- */

    // Tell SpotifyReporter about a seek.
    static const TUint kSeekMs2 = 250; // Sample 11025 @ 44.1KHz.
    iReporter->NotifySeek(kSeekMs2);

    // MsgDrain, followed by MsgDecodedStream to signify a flush.
    Semaphore sem("TSRS", 0);
    iUpstream->Enqueue(iMsgFactory->CreateMsgDrain(MakeFunctor(sem, &Semaphore::Signal)));
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    dynamic_cast<MsgDrain*>(msg)->ReportDrained();
    msg->RemoveRef();
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgDrain 0")));

    iUpstream->Enqueue(iMsgFactory->CreateMsgDecodedStream(0, 705600, 16, 44100, 2, Brn("CODC"), 3386880000, 0, true, false, false, false, Multiroom::Allowed, SpeakerProfile(2), nullptr));
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    // Start offset is updated due to NotifySeek() call to 250 ms above.
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgDecodedStream 0 705600 16 44100 2 CODC 69656832 11025 Y N N")));

    // Pull some audio.
    iUpstream->Enqueue(CreateAudio(2, 44100, trackOffset));
    msg = iReporter->Pull();
    msg->Process(*iMsgProcessor);
    msg->RemoveRef();
    samplesExpected += samplesExpectedPerMsg;
    TEST(iReporter->SubSamples() == samplesExpected);
    samplesExpected += samplesExpectedPerMsg;
    TEST(iTestPipe->Expect(Brn("MMP::ProcessMsg MsgAudioPcm 983040 983040")));
}



void TestSpotifyReporter()
{
    Runner runner("SpotifyReporter tests\n");
    runner.Add(new SuiteSpotifyReporter());
    runner.Run();
}
