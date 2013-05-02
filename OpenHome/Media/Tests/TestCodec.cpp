#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Media/EncodedAudioReservoir.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Pipeline.h>
#include <OpenHome/Media/ProcessorPcmUtils.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/ProtocolHttp.h>
#include <OpenHome/Private/File.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/OsWrapper.h>
#include "AllocatorInfoLogger.h"
#include "SuiteUnitTest.h"

#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

namespace OpenHome {
namespace Media {
namespace Codec {

class AudioFileDescriptor
{
public:
    enum ECodec
    {
        eCodecUnknown = 0,
        eCodecWav = 1,
        eCodecFlac = 2,
        eCodecMp3 = 3,
        eCodecAlac = 4,
        eCodecAac = 5,
        eCodecVorbis = 6,
        eCodecWma = 7,
    };
public:
    AudioFileDescriptor(const Brx& aFilename, TUint aSampleRate, TUint aSamples, TUint aBitDepth, TUint aChannels, ECodec aCodec);
    const Brx& Filename() const;
    TUint SampleRate() const;
    TUint Samples() const;
    TUint64 Jiffies() const;
    TUint BitDepth() const;
    TUint Channels() const;
    ECodec Codec() const;
private:
    Brn iFilename;
    TUint iSampleRate;
    TUint iSamples;
    TUint iBitDepth;
    TUint iChannels;
    ECodec iCodec;
};

class TestCodecInfoAggregator : public Av::IInfoAggregator
{
public:
    TestCodecInfoAggregator();
    virtual ~TestCodecInfoAggregator();
public: // from IInfoAggregator
    void Register(Av::IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries);
};

class TestCodecFlushIdProvider : public IFlushIdProvider
{
public:
    TestCodecFlushIdProvider();
    ~TestCodecFlushIdProvider();
public: // from IFlushIdProvider
    TUint NextFlushId();
private:
    TUint iFlushId;
};

class TestCodecFiller : public Thread, private IPipelineIdProvider
{
private:
    static const TUint kInvalidPipelineId = 0;
public:
    TestCodecFiller(Environment& aEnv, ISupply& aSupply, IFlushIdProvider& aFlushIdProvider, Av::IInfoAggregator& aInfoAggregator);
    ~TestCodecFiller();
    void Start(const Brx& aUrl);
    TUint TrackId();
    TUint StreamId();
private: // from Thread
    void Run();
private: // from IPipelineIdProvider
    TUint NextTrackId();
    TUint NextStreamId();
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    void InvalidateAt(const Brx& aStyle, const Brx& aProviderId);
    void InvalidateAfter(const Brx& aStyle, const Brx& aProviderId);
private:
    ProtocolManager* iProtocolManager;
    TrackFactory* iTrackFactory;
    ISupply& iSupply;
    Brn iUrl;
    TUint iNextTrackId;
    TUint iNextStreamId;
};

class TestCodecPipelineElementDownstream : public IPipelineElementDownstream, private INonCopyable
{
public:
    TestCodecPipelineElementDownstream(IMsgProcessor& aMsgProcessor);
    virtual ~TestCodecPipelineElementDownstream();
public: // from IPipelineElementDownstream
    void Push(Msg* aMsg);
private:
    IMsgProcessor& iMsgProcessor;
};

class MsgProcessor : public IMsgProcessor, public INonCopyable
{
public:
    MsgProcessor(Semaphore& aSem);
    ~MsgProcessor();
public: // from IMsgProcessor
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
private:
    Semaphore& iSem;
};

class SuiteCodecStream : public SuiteUnitTest, public MsgProcessor
{
public:
    static const Brn kPrefixHttp;
    static const TUint kLenPrefixHttp;
    static const TUint kMaxUriBytes;
public:
    SuiteCodecStream(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, const Uri& aUri);
protected:
    SuiteCodecStream(const TChar* aSuiteName, std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, const Uri& aUri);
    ~SuiteCodecStream();
    Brx* StartStreaming(const Brx& aTestName, const Brx& aFilename);
private:
    void Init();
    void TestJiffies();
protected: // from SuiteUnitTest
    virtual void Setup();
    virtual void TearDown();
public: // from MsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
protected:
    TUint64 iJiffies;
    Environment& iEnv;
    const Uri& iUri;
    Bwh iFileLocation;
    Semaphore iSem;
    MsgFactory* iMsgFactory;
    TestCodecPipelineElementDownstream* iElementDownstream;
    EncodedAudioReservoir* iReservoir;
    Supply* iSupply;
    TestCodecFlushIdProvider* iFlushIdProvider;
    TestCodecFiller* iFiller;
    TestCodecInfoAggregator* iInfoAggregator;
    Container* iContainer;
    CodecController* iController;
    std::vector<AudioFileDescriptor>& iFiles;
protected:
    TUint iFileNum;
protected:
    static const TUint kEncodedReservoirSizeBytes = 12 * 1024; // in practice, this can be ~500kB, but it must be limited for seek testing
    static const TUint kMaxFilenameLen = 100;    // max filename length
    static const TUint kDuration = 10;          // Test file duration (in seconds).
    static const TUint kTotalJiffies = kDuration * Jiffies::kJiffiesPerSecond;
    static const TUint kFrequencyHz = 1000;
};

class SuiteCodecSeek : public SuiteCodecStream
{
public:
    SuiteCodecSeek(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, const Uri& aUri);
protected:
    SuiteCodecSeek(const TChar* aSuiteName, std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, const Uri& aUri);
    ~SuiteCodecSeek();
    static TUint64 ExpectedJiffies(TUint aDuration, TUint aSeekInit, TUint aSeekPos);
private: // from SuiteUnitTest
    void Setup();
public: // from MsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
private:
    void TestSeeking(TUint aDuration, TUint aSeekPos, AudioFileDescriptor::ECodec aCodec);
    void TestSeekingToStart();
    void TestSeekingToEnd();
    void TestSeekingBackwards();
    void TestSeekingForwards();
protected:
    TBool iSeek;
    TUint iSeekPos;
    TBool iSeekSuccess;
private:
    TUint iFileNumStart;
    TUint iFileNumEnd;
    TUint iFileNumBack;
    TUint iFileNumForward;
};

class SuiteCodecSeekFromStart : public SuiteCodecSeek
{
public:
    SuiteCodecSeekFromStart(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, const Uri& aUri);
private:
    ~SuiteCodecSeekFromStart();
    void TestSeekingFromStart(TUint aDuration, TUint aSeekPos, AudioFileDescriptor::ECodec aCodec);
    void TestSeekingToMiddle();
    void TestSeekingToEnd();
public: // from MsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
private:
    TUint iFileNumMiddle;
    TUint iFileNumEnd;
};

class SuiteCodecZeroCrossings : public SuiteCodecStream
{
public:
    SuiteCodecZeroCrossings(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, const Uri& aUri);
private:
    ~SuiteCodecZeroCrossings();
    void TestCrossingDelta();
    Msg* TestSimilarity(MsgAudioPcm* aMsg);
    void TestZeroCrossings();
private: // from SuiteUnitTest
    void Setup();
public: // from MsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
private:
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iChannels;
    TUint iBytesProcessed;
    TUint iLastCrossingByte;
    TUint iZeroCrossings;
    TUint iUnacceptableCrossingDeltas;
    AudioFileDescriptor::ECodec iCodec;
};

class SuiteCodecInvalidType : public SuiteCodecStream
{
public:
    SuiteCodecInvalidType(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, const Uri& aUri);
protected:
    ~SuiteCodecInvalidType();
private:
    void TestInvalidType();
};

} // Codec
} // Media
} // OpenHome


// AudioFileDescriptor

AudioFileDescriptor::AudioFileDescriptor(const Brx& aFilename, TUint aSampleRate, TUint aSamples, TUint aBitDepth, TUint aChannels, ECodec aCodec)
    : iFilename(aFilename)
    , iSampleRate(aSampleRate)
    , iSamples(aSamples)
    , iBitDepth(aBitDepth)
    , iChannels(aChannels)
    , iCodec(aCodec)
{
}
const Brx& AudioFileDescriptor::Filename() const
{
    return iFilename;
}

TUint AudioFileDescriptor::SampleRate() const
{
    return iSampleRate;
}

TUint AudioFileDescriptor::Samples() const
{
    return iSamples;
}

TUint64 AudioFileDescriptor::Jiffies() const
{
    const TUint jiffiesPerSecond = Jiffies::kJiffiesPerSecond;
    TUint64 jiffies = 0;
    TUint wholeSecs = iSamples/iSampleRate;
    TUint remainingSamples = iSamples - iSampleRate*wholeSecs;
    TUint jiffiesPerSample = jiffiesPerSecond/iSampleRate;

    jiffies = wholeSecs*static_cast<TUint64>(jiffiesPerSecond) + remainingSamples*jiffiesPerSample;
    //LOG(kMedia, "AudioFileDescriptor::Jiffies wholeSecs: %u, remainingSamples: %u, jiffiesPerSample: %u, jiffies: %llu\n", wholeSecs, remainingSamples, jiffiesPerSample, jiffies);
    return jiffies;
}

TUint AudioFileDescriptor::BitDepth() const
{
    return iBitDepth;
}

TUint AudioFileDescriptor::Channels() const
{
    return iChannels;
}

AudioFileDescriptor::ECodec AudioFileDescriptor::Codec() const
{
    return iCodec;
}


// TestCodecFiller

TestCodecFiller::TestCodecFiller(Environment& aEnv, ISupply& aSupply, IFlushIdProvider& aFlushIdProvider, Av::IInfoAggregator& aInfoAggregator)
    : Thread("TCFL")
    , iSupply(aSupply)
    , iNextTrackId(kInvalidPipelineId+1)
    , iNextStreamId(kInvalidPipelineId+1)
{
    iProtocolManager = new ProtocolManager(aSupply, *this, aFlushIdProvider);
    iProtocolManager->Add(new ProtocolHttp(aEnv));
    iTrackFactory = new TrackFactory(aInfoAggregator, 1);
}

TestCodecFiller::~TestCodecFiller()
{
    delete iTrackFactory;
    delete iProtocolManager;
}

void TestCodecFiller::Start(const Brx& aUrl)
{
    iUrl.Set(aUrl);
    Thread::Start();
}

TUint TestCodecFiller::TrackId()
{
    return iNextTrackId-1;
}

TUint TestCodecFiller::StreamId()
{
    return iNextStreamId-1;
}

void TestCodecFiller::Run()
{
    Track* track = iTrackFactory->CreateTrack(iUrl, Brx::Empty(), Brx::Empty(), Brx::Empty(), 0);
    iProtocolManager->DoStream(*track);
    track->RemoveRef();
    // send a msgquit here in case of trying to stream an invalid url during tests
    // could cause race conditions if it isn't sent here
    iSupply.OutputQuit();
}

TUint TestCodecFiller::NextTrackId()
{
    return iNextTrackId++;
}

TUint TestCodecFiller::NextStreamId()
{
    return iNextStreamId++;
}

EStreamPlay TestCodecFiller::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    return ePlayYes;
}

void TestCodecFiller::InvalidateAt(const Brx& /*aStyle*/, const Brx& /*aProviderId*/)
{
    ASSERTS();
}

void TestCodecFiller::InvalidateAfter(const Brx& /*aStyle*/, const Brx& /*aProviderId*/)
{
    ASSERTS();
}


//class TestCodecFlushIdProvider

TestCodecFlushIdProvider::TestCodecFlushIdProvider()
    : iFlushId(MsgFlush::kIdInvalid+1)
{
}

TestCodecFlushIdProvider::~TestCodecFlushIdProvider()
{
}

TUint TestCodecFlushIdProvider::NextFlushId()
{
    return iFlushId++;
}


// MsgProcessor

MsgProcessor::MsgProcessor(Semaphore& aSem)
    : iSem(aSem)
{
}

MsgProcessor::~MsgProcessor()
{
}

Msg* MsgProcessor::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    //LOG(kMedia, ">MsgProcessor::ProcessMsgAudioEncoded\n");
    ASSERTS();
    return NULL;
}
Msg* MsgProcessor::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    //LOG(kMedia, ">MsgProcessor::ProcessMsgAudioPcm\n");
    ASSERTS();
    return NULL;
}
Msg* MsgProcessor::ProcessMsg(MsgSilence* /*aMsg*/)
{
    //LOG(kMedia, ">MsgProcessor::ProcessMsgSilence\n");
    ASSERTS();
    return NULL;
}
Msg* MsgProcessor::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    //LOG(kMedia, ">MsgProcessor::ProcessMsgPlayable\n");
    ASSERTS();
    return NULL;
}
Msg* MsgProcessor::ProcessMsg(MsgDecodedStream* aMsg)
{
    //LOG(kMedia, ">MsgProcessor::ProcessMsgDecodedStream\n");
    return aMsg;
}
Msg* MsgProcessor::ProcessMsg(MsgTrack* aMsg)
{
    //LOG(kMedia, ">MsgProcessor::ProcessMsgTrack\n");
    return aMsg;
}
Msg* MsgProcessor::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    //Log::Print(">MsgProcessor::ProcessMsgEncodedStream\n");
    ASSERTS();
    return NULL;
}
Msg* MsgProcessor::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    //LOG(kMedia, ">MsgProcessor::ProcessMsgMetaText\n");
    ASSERTS();
    return NULL;
}
Msg* MsgProcessor::ProcessMsg(MsgHalt* /*aMsg*/)
{
    //LOG(kMedia, ">MsgProcessor::ProcessMsgHalt\n");
    ASSERTS();
    return NULL;
}
Msg* MsgProcessor::ProcessMsg(MsgFlush* /*aMsg*/)
{
    //LOG(kMedia, ">MsgProcessor::ProcessMsgFlush\n");
    return NULL;
}
Msg* MsgProcessor::ProcessMsg(MsgQuit* /*aMsg*/)
{
    //LOG(kMedia, ">MsgProcessor::ProcessMsgQuit\n");
    iSem.Signal();
    return NULL;
}


// SuiteCodecStream

const Brn SuiteCodecStream::kPrefixHttp("http://");;
const TUint SuiteCodecStream::kLenPrefixHttp = sizeof("http://")-1;
const TUint SuiteCodecStream::kMaxUriBytes = Endpoint::kMaxEndpointBytes + kLenPrefixHttp;

SuiteCodecStream::SuiteCodecStream(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, const Uri& aUri)
    : SuiteUnitTest("Codec stream tests")
    , MsgProcessor(iSem)
    , iJiffies(0)
    , iEnv(aEnv)
    , iUri(aUri)
    , iFileLocation(iUri.AbsoluteUri().Bytes()+kMaxFilenameLen)
    , iSem("TCO1", 0)
    , iController(NULL)
    , iFiles(aFiles)
    , iFileNum(0)
{
    std::vector<AudioFileDescriptor>::iterator it;
    for (it = iFiles.begin(); it != iFiles.end(); ++it) {
        AddTest(MakeFunctor(*this, &SuiteCodecStream::TestJiffies));
    }
    Init();
}

SuiteCodecStream::SuiteCodecStream(const TChar* aSuiteName, std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, const Uri& aUri)
    : SuiteUnitTest(aSuiteName)
    , MsgProcessor(iSem)
    , iJiffies(0)
    , iEnv(aEnv)
    , iUri(aUri)
    , iFileLocation(iUri.AbsoluteUri().Bytes()+kMaxFilenameLen)
    , iSem("TCO1", 0)
    , iController(NULL)
    , iFiles(aFiles)
    , iFileNum(0)
{
    Init();
}

SuiteCodecStream::~SuiteCodecStream()
{
    delete iContainer;
    delete iMsgFactory;
    delete iInfoAggregator;
    delete iElementDownstream;
    delete iSupply;
    delete iReservoir;
    delete iFlushIdProvider;
}

void SuiteCodecStream::Init()
{
    iInfoAggregator = new TestCodecInfoAggregator();
    iMsgFactory = new MsgFactory(*iInfoAggregator, 100, 100, 5, 5, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1);
    // iFiller(ProtocolManager) -> iSupply -> iReservoir -> iContainer -> iController -> iElementDownstream(this)
    iElementDownstream = new TestCodecPipelineElementDownstream(*this);
    iReservoir = new EncodedAudioReservoir(kEncodedReservoirSizeBytes);
    iSupply = new Supply(*iMsgFactory, *iReservoir);
    iFlushIdProvider = new TestCodecFlushIdProvider();
    iContainer = new Container(*iMsgFactory, *iReservoir);
}

void SuiteCodecStream::Setup()
{
    iJiffies = 0;
    iFiller = new TestCodecFiller(iEnv, *iSupply, *iFlushIdProvider, *iInfoAggregator);
    iController = new CodecController(*iMsgFactory, *iContainer, *iElementDownstream);
    // These can be re-ordered to check for problems in the recognise function of each codec.
    iController->AddCodec(CodecFactory::NewWav());
    iController->AddCodec(CodecFactory::NewFlac());
    iController->AddCodec(CodecFactory::NewWma());
    iController->AddCodec(CodecFactory::NewAac());
    iController->AddCodec(CodecFactory::NewMp3());
    iController->AddCodec(CodecFactory::NewAlac());
    iController->AddCodec(CodecFactory::NewVorbis());

    iController->Start();
}

void SuiteCodecStream::TearDown()
{
    delete iController;
    delete iFiller;
}

Msg* SuiteCodecStream::ProcessMsg(MsgAudioPcm* aMsg)
{
    iJiffies += aMsg->Jiffies();
    //LOG(kMedia, "iJiffies: %llu\n", iJiffies);
    return aMsg;
}

Brx* SuiteCodecStream::StartStreaming(const Brx& aTestName, const Brx& aFilename)
{
    // Try streaming a full file.
    Log::Print(aTestName);
    Log::Print(": ");
    Log::Print(aFilename);
    Log::Print("\n");

    ASSERT(aFilename.Bytes() <= kMaxFilenameLen);
    Bwh* fileLocation = new Bwh(iUri.AbsoluteUri().Bytes() + aFilename.Bytes() + 1);
    fileLocation->Replace(iUri.AbsoluteUri());
    fileLocation->Append("/");
    fileLocation->Append(aFilename);
    iFiller->Start(*fileLocation);
    return fileLocation;
}

void SuiteCodecStream::TestJiffies()
{
        Brn filename(iFiles[iFileNum].Filename());
        TUint64 jiffies = iFiles[iFileNum].Jiffies();
        iFileNum++;

        Brx* fileLocation = StartStreaming(Brn("SuiteCodecStream"), filename);
        iSem.Wait();
        delete fileLocation;

        //LOG(kMedia, "iJiffies: %llu, track jiffies: %llu\n", iJiffies, jiffies);
        //Log::Print("iJiffies: %llu, track jiffies: %llu\n", iJiffies, jiffies);
        TEST(iJiffies == jiffies);
}


// SuiteCodecSeek

SuiteCodecSeek::SuiteCodecSeek(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, const Uri& aUri)
    : SuiteCodecStream("Codec seek tests", aFiles, aEnv, aUri)
    , iSeek(true)
    , iSeekPos(0)
    , iSeekSuccess(false)
    , iFileNumStart(0)
    , iFileNumEnd(0)
    , iFileNumBack(0)
    , iFileNumForward(0)
{
    std::vector<AudioFileDescriptor>::iterator it;
    for (it = iFiles.begin(); it != iFiles.end(); ++it) {
        AddTest(MakeFunctor(*this, &SuiteCodecSeek::TestSeekingToStart));
        AddTest(MakeFunctor(*this, &SuiteCodecSeek::TestSeekingToEnd));
        AddTest(MakeFunctor(*this, &SuiteCodecSeek::TestSeekingBackwards));
        AddTest(MakeFunctor(*this, &SuiteCodecSeek::TestSeekingForwards));
    }
}

SuiteCodecSeek::SuiteCodecSeek(const TChar* aSuiteName, std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, const Uri& aUri)
    : SuiteCodecStream(aSuiteName, aFiles, aEnv, aUri)
    , iSeek(true)
    , iSeekPos(0)
    , iSeekSuccess(false)
    , iFileNumStart(0)
    , iFileNumEnd(0)
    , iFileNumBack(0)
    , iFileNumForward(0)
{
}

SuiteCodecSeek::~SuiteCodecSeek()
{
}

Msg* SuiteCodecSeek::ProcessMsg(MsgAudioPcm* aMsg)
{
    aMsg = (MsgAudioPcm*) SuiteCodecStream::ProcessMsg(aMsg);
    if (iSeek && (iJiffies >= SuiteCodecStream::kTotalJiffies/2)) {
        iSeekSuccess = iController->Seek(iFiller->TrackId(), iFiller->StreamId(), iSeekPos);
        iSeek = false;
    }
    return aMsg;
}

void SuiteCodecSeek::Setup()
{
    SuiteCodecStream::Setup();
    iSeek = true;
    iSeekSuccess = false;
}

TUint64 SuiteCodecSeek::ExpectedJiffies(TUint aDuration, TUint aSeekInit, TUint aSeekPos)
{
    TUint durationInSecs = aSeekInit + (aDuration-aSeekPos);
    TUint64 jiffies = durationInSecs * Jiffies::kJiffiesPerSecond;
    return jiffies;
}

void SuiteCodecSeek::TestSeeking(TUint aDuration, TUint aSeekPos, AudioFileDescriptor::ECodec aCodec)
{
    // Try seeking forward to end of file.
    iSeekPos = aSeekPos;
    iSem.Wait();
    TUint64 expectedJiffies = ExpectedJiffies(aDuration, aDuration/2, iSeekPos);
    //LOG(kMedia, "iJiffies: %llu, expectedJiffies: %llu\n", iJiffies, expectedJiffies);
    //Log::Print("iJiffies: %llu, expectedJiffies: %llu\n", iJiffies, expectedJiffies);
    TEST(iSeekSuccess);

    if (aCodec != AudioFileDescriptor::eCodecVorbis) {
        // Vorbis (and MP3) seeking is isn't particularly accurate

        // Seeking isn't entirely accurate, so check within a bounded range of +/- 1 second.
        TEST(iJiffies >= expectedJiffies - Jiffies::kJiffiesPerSecond);   // Lower bound.
        TEST(iJiffies <= expectedJiffies + Jiffies::kJiffiesPerSecond);   // Upper bound.
    }
}

void SuiteCodecSeek::TestSeekingToStart()
{
    TUint duration = SuiteCodecStream::kDuration;
    Brn filename(iFiles[iFileNumStart].Filename());
    AudioFileDescriptor::ECodec codec = iFiles[iFileNumStart].Codec();
    iFileNumStart++;

    Brx* fileLocation = StartStreaming(Brn("SuiteCodecSeek seeking to start"), filename);
    TestSeeking(duration, 0, codec);
    delete fileLocation;
}

void SuiteCodecSeek::TestSeekingToEnd()
{
    TUint duration = SuiteCodecStream::kDuration;
    Brn filename(iFiles[iFileNumEnd].Filename());
    AudioFileDescriptor::ECodec codec = iFiles[iFileNumEnd].Codec();
    iFileNumEnd++;

    Brx* fileLocation = StartStreaming(Brn("SuiteCodecSeek seeking to end"), filename);
    TestSeeking(duration, duration, codec);
    delete fileLocation;
}

void SuiteCodecSeek::TestSeekingBackwards()
{
    TUint duration = SuiteCodecStream::kDuration;
    Brn filename(iFiles[iFileNumBack].Filename());
    AudioFileDescriptor::ECodec codec = iFiles[iFileNumBack].Codec();
    iFileNumBack++;

    Brx* fileLocation = StartStreaming(Brn("SuiteCodecSeek seeking backwards"), filename);
    TestSeeking(duration, duration/4, codec);
    delete fileLocation;
}

void SuiteCodecSeek::TestSeekingForwards()
{
    TUint duration = SuiteCodecStream::kDuration;
    Brn filename(iFiles[iFileNumForward].Filename());
    AudioFileDescriptor::ECodec codec = iFiles[iFileNumForward].Codec();
    iFileNumForward++;

    Brx* fileLocation = StartStreaming(Brn("SuiteCodecSeek seeking forwards"), filename);
    TestSeeking(duration, duration - duration/4, codec);
    delete fileLocation;
}


// SuiteCodecSeekFromStart

SuiteCodecSeekFromStart::SuiteCodecSeekFromStart(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, const Uri& aUri)
    : SuiteCodecSeek("Codec seek from start tests", aFiles, aEnv, aUri)
    , iFileNumMiddle(0)
    , iFileNumEnd(0)
{
    std::vector<AudioFileDescriptor>::iterator it;
    for (it = iFiles.begin(); it != iFiles.end(); ++it) {
        AddTest(MakeFunctor(*this, &SuiteCodecSeekFromStart::TestSeekingToMiddle));
        AddTest(MakeFunctor(*this, &SuiteCodecSeekFromStart::TestSeekingToEnd));
    }
}

SuiteCodecSeekFromStart::~SuiteCodecSeekFromStart()
{
}

Msg* SuiteCodecSeekFromStart::ProcessMsg(MsgAudioPcm* aMsg)
{
    aMsg = (MsgAudioPcm*) SuiteCodecStream::ProcessMsg(aMsg);
    if (iSeek) {
        iSeekSuccess = iController->Seek(iFiller->TrackId(), iFiller->StreamId(), iSeekPos);
        iSeek = false;
    }
    return aMsg;
}

void SuiteCodecSeekFromStart::TestSeekingFromStart(TUint aDuration, TUint aSeekPos, AudioFileDescriptor::ECodec aCodec)
{
    iSeekPos = aSeekPos;
    iSem.Wait();
    TUint64 expectedJiffies = ExpectedJiffies(aDuration, 0, iSeekPos);
    //LOG(kMedia, "iJiffies: %llu, expectedJiffies: %llu\n", iJiffies, expectedJiffies);
    //Log::Print("iJiffies: %llu, expectedJiffies: %llu\n", iJiffies, expectedJiffies);
    TEST(iSeekSuccess);

    if (aCodec != AudioFileDescriptor::eCodecVorbis) {
        // Vorbis (and MP3) seeking is isn't particularly accurate

        // Seeking isn't entirely accurate, so check within a bounded range of +/- 1 second.
        TEST(iJiffies >= 0);   // Lower bound.
        TEST(iJiffies <= expectedJiffies + Jiffies::kJiffiesPerSecond);   // Upper bound.
    }
}

void SuiteCodecSeekFromStart::TestSeekingToMiddle()
{
    TUint duration = SuiteCodecStream::kDuration;
    Brn filename(iFiles[iFileNumMiddle].Filename());
    AudioFileDescriptor::ECodec codec = iFiles[iFileNumMiddle].Codec();
    iFileNumMiddle++;

    Brx* fileLocation = StartStreaming(Brn("SuiteCodecSeekFromStart seeking to middle"), filename);
    TestSeekingFromStart(duration, duration/2, codec);
    delete fileLocation;
}

void SuiteCodecSeekFromStart::TestSeekingToEnd()
{
    TUint duration = SuiteCodecStream::kDuration;
    Brn filename(iFiles[iFileNumEnd].Filename());
    AudioFileDescriptor::ECodec codec = iFiles[iFileNumEnd].Codec();
    iFileNumEnd++;

    Brx* fileLocation = StartStreaming(Brn("SuiteCodecSeekFromStart seeking to end"), filename);
    TestSeekingFromStart(duration, duration, codec);
    delete fileLocation;
}


// SuiteCodecZeroCrossings

SuiteCodecZeroCrossings::SuiteCodecZeroCrossings(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, const Uri& aUri)
    : SuiteCodecStream("Codec zero crossing tests", aFiles, aEnv, aUri)
    , iSampleRate(0)
    , iBitDepth(0)
    , iChannels(0)
    , iBytesProcessed(0)
    , iLastCrossingByte(0)
    , iZeroCrossings(0)
    , iUnacceptableCrossingDeltas(0)
    , iCodec(AudioFileDescriptor::eCodecUnknown)
{
    std::vector<AudioFileDescriptor>::iterator it;
    for (it = iFiles.begin(); it != iFiles.end(); ++it) {
        AddTest(MakeFunctor(*this, &SuiteCodecZeroCrossings::TestZeroCrossings));
    }
}

SuiteCodecZeroCrossings::~SuiteCodecZeroCrossings()
{
}

void SuiteCodecZeroCrossings::Setup()
{
    SuiteCodecStream::Setup();
    iBytesProcessed = 0;
    iLastCrossingByte = 0;
    iZeroCrossings = 0;
    iUnacceptableCrossingDeltas = 0;
}

void SuiteCodecZeroCrossings::TestCrossingDelta()
{
    const TUint bytesPerSample = (iBitDepth * iChannels) / 8;
    const TUint bytesPerSec = bytesPerSample * 44100;
    const TUint bytesPerSine = bytesPerSec/SuiteCodecStream::kFrequencyHz;
    const TUint bytesPerCrossing = bytesPerSine/2;
    TUint byteDelta = iBytesProcessed - iLastCrossingByte;

    iZeroCrossings++;
    //LOG(kMedia, "byteDelta: %u, bytesPerCrossing: %u\n", byteDelta, bytesPerCrossing);
    if (iLastCrossingByte != 0 && byteDelta != bytesPerCrossing)
    {
        if (byteDelta < bytesPerCrossing-6 || byteDelta > bytesPerCrossing+6) {
            iUnacceptableCrossingDeltas++;
        }
    }
    iLastCrossingByte = iBytesProcessed;
}

Msg* SuiteCodecZeroCrossings::TestSimilarity(MsgAudioPcm* aMsg)
{
    TBool negative = false;
    TBool positive = false;

    MsgPlayable* msg = aMsg->CreatePlayable();
    TUint bytes = msg->Bytes();
    ProcessorPcmBufPacked pcmProcessor;
    const TUint increment = (iBitDepth/8) * iChannels;

    msg->Read(pcmProcessor);
    const TByte* ptr = (TByte*)pcmProcessor.Ptr();

    // Measure how many times subsamples pass through zero.
    for (TUint i = 0; i < bytes; i += increment) {
        for (TUint j = 0; j < iChannels; j++) {
            TInt subsample = 0;

            switch (iBitDepth)
            {
            case 16:
                subsample = ((ptr[0] << 24) | (ptr[1] << 16)) >> 16;
                ptr += 2;
                break;
            case 24:
                subsample = ((ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8)) >> 8;
                ptr += 3;
                break;
            default:
                ASSERTS();
            }

            if (j == 0) { // Only do subsample comparison on a single channel.
                if (subsample < 0) {
                    if (positive && !negative) {
                        TestCrossingDelta();
                    }
                    negative = true;
                    positive = false;
                }
                else if (subsample > 0) {
                    if (negative && !positive) {
                        TestCrossingDelta();
                    }
                    negative = false;
                    positive = true;
                }
                else {
                    if (negative || positive) {
                        TestCrossingDelta();
                    }
                    negative = false;
                    positive = false;
                }
            }
            iBytesProcessed += iBitDepth/8;
        }
    }

    return msg;
}

Msg* SuiteCodecZeroCrossings::ProcessMsg(MsgAudioPcm* aMsg)
{
    //aMsg = (MsgAudioPcm*) SuiteCodecStream::ProcessMsg(aMsg);
    Msg* msgOut = TestSimilarity(aMsg);
    msgOut->RemoveRef();
    msgOut = NULL;
    return msgOut;
}

void SuiteCodecZeroCrossings::TestZeroCrossings()
{
    Brn filename(iFiles[iFileNum].Filename());
    TUint64 jiffies = iFiles[iFileNum].Jiffies();
    iSampleRate = iFiles[iFileNum].SampleRate();
    iBitDepth = iFiles[iFileNum].BitDepth();
    iChannels = iFiles[iFileNum].Channels();
    iCodec = iFiles[iFileNum].Codec();
    iFileNum++;

    const TUint jiffiesPerSine = Jiffies::kJiffiesPerSecond / SuiteCodecStream::kFrequencyHz;
    const TUint sineWaves = (TUint)jiffies/jiffiesPerSine;
    const TUint expectedZeroCrossings = sineWaves*2 - 1;

    Brx* fileLocation = StartStreaming(Brn("SuiteCodecZeroCrossings"), filename);
    iSem.Wait();
    delete fileLocation;

    //LOG(kMedia, "iZeroCrossings: %u, expectedZeroCrossings: %u, iUnacceptableCrossingDeltas: %u\n", iZeroCrossings, expectedZeroCrossings, iUnacceptableCrossingDeltas);
    //Log::Print("iZeroCrossings: %u, expectedZeroCrossings: %u, iUnacceptableCrossingDeltas: %u\n", iZeroCrossings, expectedZeroCrossings, iUnacceptableCrossingDeltas);
    TEST(iZeroCrossings >= expectedZeroCrossings-100);
    if (iCodec == AudioFileDescriptor::eCodecMp3) {
        // MP3 encoders/decoders add silence and some samples of random data to
        // start and end of tracks for filter routines.
        // LAME FAQ suggests this is for at least 1057 samples at start and 288 at end.
        TEST(iZeroCrossings <= expectedZeroCrossings+70);
    }
    else {
        TEST(iZeroCrossings <= expectedZeroCrossings+15);
    }
    // Test that less than 1% of the zero crossings have an unnaceptable spacing.
    TEST(iUnacceptableCrossingDeltas < expectedZeroCrossings/100);
}


// SuiteCodecInvalidType

SuiteCodecInvalidType::SuiteCodecInvalidType(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, const Uri& aUri)
    : SuiteCodecStream("Codec invalid type tests", aFiles, aEnv, aUri)
{
    std::vector<AudioFileDescriptor>::iterator it;
    for (it = iFiles.begin(); it != iFiles.end(); ++it) {
        AddTest(MakeFunctor(*this, &SuiteCodecInvalidType::TestInvalidType));
    }
}

SuiteCodecInvalidType::~SuiteCodecInvalidType()
{
}

void SuiteCodecInvalidType::TestInvalidType()
{
    Brn filename(iFiles[iFileNum].Filename());
    iFileNum++;

    Brx* fileLocation = StartStreaming(Brn("SuiteCodecInvalidType"), filename);
    iSem.Wait();
    delete fileLocation;

    //LOG(kMedia, "iJiffies: %llu, kTotalJiffies: %llu\n", iJiffies, TestCodecPipelineElementUpstream::kTotalJiffies);
    TEST(iJiffies == 0); // If we don't exit cleanly and with 0 jiffies of output audio, something is misbehaving.
}


// TestCodecPipelineElementDownstream

TestCodecPipelineElementDownstream::TestCodecPipelineElementDownstream(IMsgProcessor& aMsgProcessor)
    : iMsgProcessor(aMsgProcessor)
{
}

TestCodecPipelineElementDownstream::~TestCodecPipelineElementDownstream()
{
}

void TestCodecPipelineElementDownstream::Push(Msg* aMsg)
{
    //LOG(kMedia, ">TestCodecPipelineElementDownstream::Push\n");
    aMsg->Process(iMsgProcessor);
    if (aMsg != NULL) {
        aMsg->RemoveRef();
    }
}


// TestCodecInfoAggregator

TestCodecInfoAggregator::TestCodecInfoAggregator()
{
}

TestCodecInfoAggregator::~TestCodecInfoAggregator()
{
}

void TestCodecInfoAggregator::Register(Av::IInfoProvider& /*aProvider*/, std::vector<Brn>& /*aSupportedQueries*/)
{
}

void TestCodec(Net::Library& aLib, const std::vector<Brn>& aArgs)
{
    Log::Print("TestCodec\n");

    OptionParser parser;
    OptionString optionServer("-s", "--server", Brn("127.0.0.1"), "address of server to connect to");
    parser.AddOption(&optionServer);
    OptionUint optionPort("-p", "--port", 8080, "server port to connect on");
    parser.AddOption(&optionPort);
    if (!parser.Parse(aArgs) || parser.HelpDisplayed()) {
        return;
    }
    ASSERT(optionPort.Value() <= 65535);

    Net::InitialisationParams::ELoopback loopback;
    if (optionServer.Value().Equals(Brn("127.0.0.1"))) { // using loopback
        loopback = Net::InitialisationParams::ELoopbackUse;
    }
    else {
        loopback = Net::InitialisationParams::ELoopbackExclude;
    }
    std::vector<NetworkAdapter*>* ifs = Os::NetworkListAdapters(aLib.Env(), loopback, "TestCodec");
    ASSERT(ifs->size() > 0);
    TIpAddress addr = (*ifs)[0]->Address(); // assume we are only on one subnet (or using loopback)
    for (TUint i=0; i<ifs->size(); i++) {
        TIpAddress addrTmp = (*ifs)[i]->Address();
        Endpoint endpt(optionPort.Value(), addrTmp);
        Endpoint::AddressBuf buf;
        endpt.AppendAddress(buf);
        (*ifs)[i]->RemoveRef("TestCodec");
    }
    delete ifs;

    Endpoint endptClient(0, addr);
    Endpoint::AddressBuf buf;
    endptClient.AppendAddress(buf);
    Log::Print("Using network interface %s\n", buf.Ptr());

    // set up server uri
    Endpoint endptServer = Endpoint(optionPort.Value(), optionServer.Value());
    Bws<SuiteCodecStream::kMaxUriBytes> uriBuf;
    uriBuf.Append(SuiteCodecStream::kPrefixHttp);
    endptServer.AppendEndpoint(uriBuf);
    Uri uri(uriBuf);
    Log::Print("Connecting to server: ");
    Log::Print(uri.AbsoluteUri());
    Log::Print("\n");



    // test files
    std::vector<AudioFileDescriptor> stdFiles;
    stdFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k.wav"), 44100, 441000, 16, 1, AudioFileDescriptor::eCodecWav));
    stdFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k.wav"), 44100, 441000, 16, 2, AudioFileDescriptor::eCodecWav));
    stdFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-l5-16bit.flac"), 44100, 441000, 16, 1, AudioFileDescriptor::eCodecFlac));
    stdFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-l5-16bit.flac"), 44100, 441000, 16, 2, AudioFileDescriptor::eCodecFlac));
    stdFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-l5-24bit.flac"), 44100, 441000, 24, 1, AudioFileDescriptor::eCodecFlac));
    stdFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-l5-24bit.flac"), 44100, 441000, 24, 2, AudioFileDescriptor::eCodecFlac));

    //// MP3 encoders/decoders can add extra samples at start of tracks, which are used for their routines.
    //stdFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-128k.mp3"), 44100, 442368, 24, 1, AudioFileDescriptor::eCodecMp3));
    //stdFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-128k.mp3"), 44100, 442368, 24, 2, AudioFileDescriptor::eCodecMp3));

    stdFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-alac.m4a"), 44100, 441000, 16, 1, AudioFileDescriptor::eCodecAlac));
    stdFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-alac.m4a"), 44100, 441000, 16, 2, AudioFileDescriptor::eCodecAlac));
    stdFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-24bit-alac.m4a"), 44100, 441000, 24, 2, AudioFileDescriptor::eCodecAlac));

    // AAC encoders can add/drop samples from start of files.
    // Need to account for discarded samples from start of AAC files - decoder drops first frame, which is usually 1024 samples.
    stdFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-aac.m4a"), 44100, 443392-1024, 16, 1, AudioFileDescriptor::eCodecAac));
    stdFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-aac.m4a"), 44100, 443392-1024, 16, 2, AudioFileDescriptor::eCodecAac));

    // Vorbis files
    stdFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-q5.ogg"), 44100, 441000, 16, 1, AudioFileDescriptor::eCodecVorbis));
    stdFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-q5.ogg"), 44100, 441000, 16, 2, AudioFileDescriptor::eCodecVorbis));

    // WMA encoder omits some samples, then adds extra for its own use. Decoder then strips samples to less than original PCM.
    stdFiles.push_back(AudioFileDescriptor(Brn("10s-mono-44k-96k.wma"), 44100, 440320, 16, 1, AudioFileDescriptor::eCodecWma));
    stdFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-96k.wma"), 44100, 440320, 16, 2, AudioFileDescriptor::eCodecWma));


    // Some files that shouldn't play with any codec.
    std::vector<AudioFileDescriptor> invalidFiles;
    invalidFiles.push_back(AudioFileDescriptor(Brn("invalid_long_file"), 0, 0, 16, 1, AudioFileDescriptor::eCodecUnknown));            // Large invalid file.
    invalidFiles.push_back(AudioFileDescriptor(Brn("invalid_short_file"), 0, 0, 16, 1, AudioFileDescriptor::eCodecUnknown));       // Small invalid file.

    // MP4 with moov atom after mdat atom.
    // Currently can't handle this type of file, so check we at least fail to handle them gracefully.
    invalidFiles.push_back(AudioFileDescriptor(Brn("10s-stereo-44k-aac-moov_end.m4a"), 0, 0, 16, 1, AudioFileDescriptor::eCodecUnknown));


    // Files to check behaviour of codec wrappers (and/or container), other than their decoding behaviour.
    std::vector<AudioFileDescriptor> streamOnlyFiles;
    // Test different combinations of ID3 tags.
    //streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-no_tags.mp3"), 44100, 133632, 24, 2, AudioFileDescriptor::eCodecMp3));
    //streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-id3v1.mp3"), 44100, 133632, 24, 2, AudioFileDescriptor::eCodecMp3));
    //streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-id3v2.mp3"), 44100, 133632, 24, 2, AudioFileDescriptor::eCodecMp3));
    //streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-dual_tags.mp3"), 44100, 133632, 24, 2, AudioFileDescriptor::eCodecMp3));
    // Files with two sets of ID3v2 tags
    //streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-two_id3v2_headers.mp3"), 44100, 133632, 24, 2, AudioFileDescriptor::eCodecMp3));
    // Second ID3v2 header on a msg boundary (assuming MsgAudioEncoded is normally 6144 bytes) to test container checking/pulling on demand
    //streamOnlyFiles.push_back(AudioFileDescriptor(Brn("3s-stereo-44k-two_id3v2_headers_msg_boundary.mp3"), 44100, 133632, 24, 2, AudioFileDescriptor::eCodecMp3));
    // A file that does not play on existing DS's (is recognised as AAC ADTS)
    //streamOnlyFiles.push_back(AudioFileDescriptor(Brn("mp3-8~24-stereo.mp3"), 24000, 4834944, 24, 2, AudioFileDescriptor::eCodecMp3));

    Runner runner("Codec tests\n");
    runner.Add(new SuiteCodecStream(stdFiles, aLib.Env(), uri));
    runner.Add(new SuiteCodecSeek(stdFiles, aLib.Env(), uri));
    runner.Add(new SuiteCodecSeekFromStart(stdFiles, aLib.Env(), uri));
    runner.Add(new SuiteCodecZeroCrossings(stdFiles, aLib.Env(), uri));
    runner.Add(new SuiteCodecInvalidType(invalidFiles, aLib.Env(), uri));
    runner.Add(new SuiteCodecStream(streamOnlyFiles, aLib.Env(), uri));
    runner.Run();
}
