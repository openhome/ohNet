#ifndef HEADER_TESTCODEC
#define HEADER_TESTCODEC

#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/SuiteUnitTest.h>

namespace OpenHome {
    class Uri;
    class Environment;

namespace Media {
    class EncodedAudioReservoir;
    class ProtocolManager;

namespace Codec {
    class Container;
    class CodecController;

class AudioFileDescriptor
{
public:
    static const TUint kCodecUnknown  = 0;
    static const TUint kCodecWav      = 1;
    static const TUint kCodecFlac     = 2;
    static const TUint kCodecAlac     = 3;
    static const TUint kCodecAac      = 4;
    static const TUint kCodecVorbis   = 5;
    static const TUint kCodecAiff     = 6;
    static const TUint kCodecAifc     = 7;
    static const TUint kCodecAdts     = 8;
    static const TUint kCodecMp3      = 9;
public:
    AudioFileDescriptor(const Brx& aFilename, TUint aSampleRate, TUint aSamples, TUint aBitDepth, TUint aChannels, TUint aCodec, TBool aSeekable);
    const Brx& Filename() const;
    TUint SampleRate() const;
    TUint Samples() const;
    TUint64 Jiffies() const;
    TUint BitDepth() const;
    TUint Channels() const;
    TUint Codec() const;
    TBool Seekable() const;
private:
    Brn iFilename;
    TUint iSampleRate;
    TUint iSamples;
    TUint iBitDepth;
    TUint iChannels;
    TUint iCodec;
    TBool iSeekable;
};

class AudioFileCollection
{
public:
    AudioFileCollection();
    AudioFileCollection(std::vector<AudioFileDescriptor> aReqFiles
                      , std::vector<AudioFileDescriptor> aExtraFiles
                      , std::vector<AudioFileDescriptor> aInvalidFiles
                      , std::vector<AudioFileDescriptor> aStreamOnlyFiles
                      );
    void AddRequiredFile(AudioFileDescriptor aFile);
    void AddExtraFile(AudioFileDescriptor aFile);
    void AddInvalidFile(AudioFileDescriptor aFile);
    void AddStreamOnlyFile(AudioFileDescriptor aFile);
    std::vector<AudioFileDescriptor>& RequiredFiles();
    std::vector<AudioFileDescriptor>& ExtraFiles();
    std::vector<AudioFileDescriptor>& InvalidFiles();
    std::vector<AudioFileDescriptor>& StreamOnlyFiles();
private:
    std::vector<AudioFileDescriptor> iReqFiles;
    std::vector<AudioFileDescriptor> iExtraFiles;
    std::vector<AudioFileDescriptor> iInvalidFiles;
    std::vector<AudioFileDescriptor> iStreamOnlyFiles;
};

class TestCodecInfoAggregator : public IInfoAggregator
{
public:
    TestCodecInfoAggregator();
    virtual ~TestCodecInfoAggregator();
public: // from IInfoAggregator
    void Register(IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries);
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

class TestCodecFiller : public IUrlBlockWriter, public Thread, private IPipelineIdProvider
{
private:
    static const TUint kInvalidPipelineId = 0;
public:
    TestCodecFiller(Environment& aEnv, IPipelineElementDownstream& aDownstream, MsgFactory& aMsgFactory, IFlushIdProvider& aFlushIdProvider, IInfoAggregator& aInfoAggregator);
    ~TestCodecFiller();
    void Start(const Brx& aUrl);
    TUint StreamId();
public: // from IUrlBlockWriter
    TBool TryGet(IWriter& aWriter, const Brx& aUrl, TUint64 aOffset, TUint aBytes) override;
private: // from Thread
    void Run();
private: // from IPipelineIdProvider
    TUint NextStreamId() override;
    EStreamPlay OkToPlay(TUint aStreamId) override;
private:
    ProtocolManager* iProtocolManager;
    TrackFactory* iTrackFactory;
    IPipelineElementDownstream& iPipeline;
    MsgFactory& iMsgFactory;
    Brn iUrl;
    TUint iNextStreamId;
};

class TestCodecPipelineElementDownstream : public IPipelineElementDownstream, private INonCopyable
{
public:
    TestCodecPipelineElementDownstream(IMsgProcessor& aMsgProcessor);
    virtual ~TestCodecPipelineElementDownstream();
public: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
private:
    IMsgProcessor& iMsgProcessor;
};

class TestCodecMinimalPipeline : private IUrlBlockWriter
{
private:
    static const TUint kEncodedAudioCount = 100;
    static const TUint kMsgAudioEncodedCount = 100;
    static const TUint kEncodedReservoirSizeBytes = 9 * 1024; // in practice, this can be ~500kB, but it must be limited for seek testing
    static const TUint kEncodedReservoirMaxStreams = 10;
public:
    TestCodecMinimalPipeline(Environment& aEnv, IMsgProcessor& aMsgProcessor);
    virtual ~TestCodecMinimalPipeline();
    void StartPipeline();
    void StartStreaming(const Brx& aUrl);
    TBool SeekCurrentTrack(TUint aSecondsAbsolute, ISeekObserver& aSeekObserver, TUint& aHandle);
protected:
    virtual void RegisterPlugins();
private: // from IUrlBlockWriter
    TBool TryGet(IWriter& aWriter, const Brx& aUrl, TUint64 aOffset, TUint aBytes) override;
protected:
    Container* iContainer;
    CodecController* iController;
private:
    TestCodecInfoAggregator* iInfoAggregator;
    MsgFactory* iMsgFactory;
    TestCodecPipelineElementDownstream* iElementDownstream;
    EncodedAudioReservoir* iReservoir;
    Logger* iLoggerEncodedAudioReservoir;
    Logger* iLoggerContainer;
    Logger* iLoggerCodecController;
    TestCodecFlushIdProvider* iFlushIdProvider;
    TestCodecFiller* iFiller;
};

typedef TestCodecMinimalPipeline* (*CreateTestCodecPipelineFunc)(Environment& aEnv, IMsgProcessor& aMsgProcessor);
typedef AudioFileCollection* (*GetTestFiles)();

class MsgProcessor : public IMsgProcessor, public INonCopyable
{
public:
    MsgProcessor(Semaphore& aSem);
    ~MsgProcessor();
public: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgChangeInput* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    Semaphore& iSem;
};

class SuiteCodecStream : public TestFramework::SuiteUnitTest, public MsgProcessor
{
public:
    static const Brn kPrefixHttp;
    static const TUint kLenPrefixHttp;
    static const TUint kMaxUriBytes;
protected:
    static const TUint kSemWaitMs = 50;
public:
    SuiteCodecStream(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, CreateTestCodecPipelineFunc aFunc, const Uri& aUri);
protected:
    SuiteCodecStream(const TChar* aSuiteName, std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, CreateTestCodecPipelineFunc aFunc, const Uri& aUri);
    ~SuiteCodecStream();
    Brx* StartStreaming(const Brx& aTestName, const Brx& aFilename);
private:
    void TestJiffies();
protected: // from SuiteUnitTest
    virtual void Setup();
    virtual void TearDown();
public: // from MsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
protected:
    TUint64 iJiffies;
    Environment& iEnv;
    const Uri& iUri;
    Bwh iFileLocation;
    Semaphore iSem;
    TestCodecMinimalPipeline* iPipeline;
    std::vector<AudioFileDescriptor>& iFiles;
    TUint iFileNum;
private:
    CreateTestCodecPipelineFunc iCreatePipeline;
protected:
    static const TUint kMaxFilenameLen = 100;    // max filename length
    static const TUint kFrequencyHz = 1000;
};

class SuiteCodecSeek : public SuiteCodecStream, public ISeekObserver
{
public:
    SuiteCodecSeek(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, CreateTestCodecPipelineFunc aFunc, const Uri& aUri);
protected:
    SuiteCodecSeek(const TChar* aSuiteName, std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, CreateTestCodecPipelineFunc aFunc, const Uri& aUri);
    ~SuiteCodecSeek();
    static TUint64 ExpectedJiffies(TUint64 aJiffiesTotal, TUint64 aSeekStartJiffies, TUint aSeekPosSeconds);
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
public: // from MsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
private: // ISeekObserver
    void NotifySeekComplete(TUint aHandle, TUint aFlushId);
private:
    void TestSeeking(TUint64 aDurationJiffies, TUint64 aSeekPosJiffies, TUint aCodec, TBool aSeekable);
    void TestSeekingToStart();
    void TestSeekingToEnd();
    void TestSeekingBeyondEnd();
    void TestSeekingBackwards();
    void TestSeekingForwards();
protected:
    TBool iSeek;
    TUint iSeekPos;
    TBool iSeekSuccess;
    TUint iHandle;
    Semaphore* iSemSeek;
    TUint64 iTotalJiffies;
private:
    TUint iFileNumStart;
    TUint iFileNumEnd;
    TUint iFileNumBeyondEnd;
    TUint iFileNumBack;
    TUint iFileNumForward;
};

class SuiteCodecSeekFromStart : public SuiteCodecSeek
{
public:
    SuiteCodecSeekFromStart(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, CreateTestCodecPipelineFunc aFunc, const Uri& aUri);
private:
    ~SuiteCodecSeekFromStart();
    void TestSeekingFromStart(TUint64 aDurationJiffies, TUint64 aSeekPosJiffies, TUint aCodec, TBool aSeekable);
    void TestSeekingToMiddle();
    void TestSeekingToEnd();
    void TestSeekingBeyondEnd();
public: // from MsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
private:
    TUint iFileNumMiddle;
    TUint iFileNumEnd;
    TUint iFileNumBeyondEnd;
};

class SuiteCodecZeroCrossings : public SuiteCodecStream
{
public:
    SuiteCodecZeroCrossings(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, CreateTestCodecPipelineFunc aFunc, const Uri& aUri);
private:
    ~SuiteCodecZeroCrossings();
    void TestCrossingDelta();
    Msg* TestSimilarity(MsgAudioPcm* aMsg);
    void TestZeroCrossings();
private: // from SuiteUnitTest
    void Setup();
public: // from MsgProcessor
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
private:
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iChannels;
    TUint iBytesProcessed;
    TInt iLastSubsample;
    TUint iLastCrossingByte;
    TUint iZeroCrossings;
    TUint iUnacceptableCrossingDeltas;
    TUint iCodec;
    TBool iSeekable;
};

class SuiteCodecInvalidType : public SuiteCodecStream
{
public:
    SuiteCodecInvalidType(std::vector<AudioFileDescriptor>& aFiles, Environment& aEnv, CreateTestCodecPipelineFunc aFunc, const Uri& aUri);
protected:
    ~SuiteCodecInvalidType();
private:
    void TestInvalidType();
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif // HEADER_TESTCODEC
