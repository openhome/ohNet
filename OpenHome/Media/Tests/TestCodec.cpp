#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Codec/Alac.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/Flac.h>
#include <OpenHome/Media/Codec/Mp3.h>
#include <OpenHome/Media/Codec/Wav.h>
#include <OpenHome/Media/ProcessorPcmUtils.h>
#include <OpenHome/Private/File.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/Thread.h>

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
        eCodecWav = 0,
        eCodecFlac = 1,
        eCodecMp3 = 2,
        eCodecAlac = 3,
        eCodecUnknown = 4,
    };
public:
    AudioFileDescriptor(const Brx& aFilename, TUint aBitDepth, TUint aChannels, ECodec aCodec);
    const Brx& Filename() const;
    TUint BitDepth() const;
    TUint Channels() const;
    ECodec Codec() const;
private:
    Brn iFilename;
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

class TestCodecPipelineElementUpstream : public IPipelineElementUpstream, public IStreamHandler
{
public:
    static const TUint kTrackId = 0;
    static const TUint kStreamId = 0;
    static const TUint kDuration = 10;          // Test file duration (in seconds).
    static const TUint kTotalJiffies = kDuration * Jiffies::kJiffiesPerSecond;
    static const TUint kFrequencyHz = 1000;
public:
    TestCodecPipelineElementUpstream(MsgFactory& aMsgFactory);
    virtual ~TestCodecPipelineElementUpstream();
    void Initialise(const Brx& aFilename);
    TUint FileBytes();
    TUint BytesRead();
    void Reset();
public: // from IPipelineElementUpstream
    Msg* Pull();
public: // from IStreamHandler
    TBool OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
private:
    IFile* iFile;
    Brhz iFilename;
    MsgFactory& iMsgFactory;
    Bws<EncodedAudio::kMaxBytes> iBuf;
    TUint iBytesRead;
    TUint iPullCount;
    TBool iSeekFlush;
    TUint iFlushId;
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

class SuiteCodecStream : public Suite, public MsgProcessor
{
public:
    SuiteCodecStream(std::vector<AudioFileDescriptor>& aFiles);
protected:
    SuiteCodecStream(const TChar* aSuiteName, std::vector<AudioFileDescriptor>& aFiles);
    ~SuiteCodecStream();
    void Reinitialise(const Brx& aFilename);
private:
    void Init();
private: // from Suite
    void Test();
public: // from MsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
protected:
    TUint iJiffies;
    Semaphore iSem;
    MsgFactory* iMsgFactory;
    TestCodecPipelineElementUpstream* iElementUpstream;
    TestCodecPipelineElementDownstream* iElementDownstream;
    TestCodecInfoAggregator* iInfoAggregator;
    Container* iContainer;
    CodecController* iController;
    std::vector<AudioFileDescriptor>& iFiles;
};

class SuiteCodecSeek : public SuiteCodecStream
{
public:
    SuiteCodecSeek(std::vector<AudioFileDescriptor>& aFiles);
protected:
    SuiteCodecSeek(const TChar* aSuiteName, std::vector<AudioFileDescriptor>& aFiles);
    ~SuiteCodecSeek();
    void Reinitialise(const Brx& aFilename);
    static TUint ExpectedJiffies(TUint aDuration, TUint aSeekInit, TUint aSeekPos);
private: // from Suite
    void Test();
public: // from MsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
private:
    void TestSeeking(const Brx& aFilename, TUint aDuration, TUint aSeekPos);
protected:
    TBool iSeek;
    TUint iSeekPos;
    TBool iSeekSuccess;
};

class SuiteCodecSeekFromStart : public SuiteCodecSeek
{
public:
    SuiteCodecSeekFromStart(std::vector<AudioFileDescriptor>& aFiles);
private:
    ~SuiteCodecSeekFromStart();
    void TestSeekingFromStart(const Brx& aFilename, TUint aDuration, TUint aSeekPos);
private: // from Suite
    void Test();
public: // from MsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
};

class SuiteCodecZeroCrossings : public SuiteCodecStream
{
public:
    SuiteCodecZeroCrossings(std::vector<AudioFileDescriptor>& aFiles);
private:
    ~SuiteCodecZeroCrossings();
    Msg* TestSimilarity(MsgAudioPcm* aMsg);
private: // from Suite
    void Test();
private: // from SuiteCodecStream
    void Reinitialise(const Brx& aFilename);
public: // from MsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
private:
    TUint iBitDepth;
    TUint iChannels;
    TUint iZeroCrossings;
    TBool iCrossingDeltaAcceptable;
    AudioFileDescriptor::ECodec iCodec;
};

class SuiteCodecInvalidType : public SuiteCodecStream
{
public:
    SuiteCodecInvalidType(std::vector<AudioFileDescriptor>& aFiles);
protected:
    ~SuiteCodecInvalidType();
private: // from Suite
    void Test();
};

} // Codec
} // Media
} // OpenHome


// AudioFileDescriptor

AudioFileDescriptor::AudioFileDescriptor(const Brx& aFilename, TUint aBitDepth, TUint aChannels, ECodec aCodec)
    : iFilename(aFilename)
    , iBitDepth(aBitDepth)
    , iChannels(aChannels)
    , iCodec(aCodec)
{
}
const Brx& AudioFileDescriptor::Filename() const
{
    return iFilename;
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


// TestCodecPipelineElementUpstream

TestCodecPipelineElementUpstream::TestCodecPipelineElementUpstream(MsgFactory& aMsgFactory)
    : iFile(NULL)
    , iMsgFactory(aMsgFactory)
    , iBytesRead(0)
    , iPullCount(0)
    , iSeekFlush(false)
    , iFlushId(MsgFlush::kIdInvalid)
{
}

TestCodecPipelineElementUpstream::~TestCodecPipelineElementUpstream()
{
    if (iFile != NULL) {
        delete iFile;
    }
}

void TestCodecPipelineElementUpstream::Initialise(const Brx& aFilename)
{
    iFilename.Set(aFilename);

    if (iFile != NULL) {
        delete iFile;
    }
    // Try opening the file.
    try {
        iFile = IFile::Open(iFilename.CString(), eFileReadOnly);
    }
    catch (FileOpenError) {
        ASSERTS();
        //throw;
    }
}

TUint TestCodecPipelineElementUpstream::FileBytes()
{
    return iFile->Bytes();
}

TUint TestCodecPipelineElementUpstream::BytesRead()
{
    return iBytesRead;
}

void TestCodecPipelineElementUpstream::Reset()
{
    iBytesRead = 0;
    iPullCount = 0;
}

Msg* TestCodecPipelineElementUpstream::Pull()
{
    //LOG(kMedia, ">TestCodecPipelineElementUpstream::Pull\n");
    Msg* msg = NULL;

    if (iPullCount == 0) {
        msg = iMsgFactory.CreateMsgTrack(Brn("10.2.0.1/someplaylistfile"), kTrackId);
    }
    else if (iPullCount == 1) {
        msg = iMsgFactory.CreateMsgEncodedStream(Brn("10.2.0.1/somefile"),
                Brn("This is an audio file"), iFile->Bytes(), kStreamId, true, false, this);
    }
    else if (iSeekFlush) {
        msg = iMsgFactory.CreateMsgFlush(iFlushId);
        iSeekFlush = false;
    }
    else {
        if (iBytesRead < iFile->Bytes()) {
            TUint bytesToRead = EncodedAudio::kMaxBytes;
            TUint bytesRemaining = iFile->Bytes()-iBytesRead;
            if (bytesRemaining < bytesToRead) {
                bytesToRead = bytesRemaining;
            }
            iBuf.SetBytes(0);
            iFile->Read(iBuf, EncodedAudio::kMaxBytes);
            msg = iMsgFactory.CreateMsgAudioEncoded(iBuf);
            iBytesRead += bytesToRead;
        }
        else {
            msg = iMsgFactory.CreateMsgQuit();
        }
    }
    iPullCount++;

    //LOG(kMedia, "<TestCodecPipelineElementUpstream::Pull\n");
    return msg;
}

TBool TestCodecPipelineElementUpstream::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS();
    return false;
}

TUint TestCodecPipelineElementUpstream::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 aOffset)
{
    //LOG(kMedia, ">TestCodecStreamHandler::TrySeek\n");
    iFlushId++;
    iFile->Seek((TUint) aOffset, eSeekFromStart);
    iBytesRead = (TUint) aOffset;
    iSeekFlush = true;
    return iFlushId;
}

TUint TestCodecPipelineElementUpstream::TryStop(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    return 0;
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

SuiteCodecStream::SuiteCodecStream(std::vector<AudioFileDescriptor>& aFiles)
    : Suite("Codec stream tests")
    , MsgProcessor(iSem)
    , iJiffies(0)
    , iSem("TCO1", 0)
    , iController(NULL)
    , iFiles(aFiles)
{
    Init();
}

SuiteCodecStream::SuiteCodecStream(const TChar* aSuiteName, std::vector<AudioFileDescriptor>& aFiles)
    : Suite(aSuiteName)
    , MsgProcessor(iSem)
    , iJiffies(0)
    , iSem("TCO1", 0)
    , iController(NULL)
    , iFiles(aFiles)
{
    Init();
}

SuiteCodecStream::~SuiteCodecStream()
{
    if (iController != NULL)
    {
        delete iController;
    }
    delete iContainer;
    delete iMsgFactory;
    delete iInfoAggregator;
    delete iElementDownstream;
    delete iElementUpstream;
}

void SuiteCodecStream::Init()
{
    iInfoAggregator = new TestCodecInfoAggregator();
    iMsgFactory = new MsgFactory(*iInfoAggregator, 5, 5, 5, 5, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1);
    iElementDownstream = new TestCodecPipelineElementDownstream(*this);
    iElementUpstream = new TestCodecPipelineElementUpstream(*iMsgFactory);
    iContainer = new Container(*iMsgFactory, *iElementUpstream);
}

Msg* SuiteCodecStream::ProcessMsg(MsgAudioPcm* aMsg)
{
    iJiffies += aMsg->Jiffies();
    return aMsg;
}

void SuiteCodecStream::Reinitialise(const Brx& aFilename)
{
    iJiffies = 0;
    if (iController != NULL) {
        delete iController;
        iController = NULL;
    }
    iElementUpstream->Reset();
    iElementUpstream->Initialise(aFilename);
    iController = new CodecController(*iMsgFactory, *iContainer, *iElementDownstream);
    iController->AddCodec(new CodecWav());
    iController->AddCodec(new CodecFlac());
    iController->AddCodec(new CodecMp3());
    iController->AddCodec(new CodecAlac());
    iController->Start();
}

void SuiteCodecStream::Test()
{
    std::vector<AudioFileDescriptor>::iterator it;
    for (it = iFiles.begin(); it != iFiles.end(); ++it) {
        Brn filename((*it).Filename());
        AudioFileDescriptor::ECodec codec = (*it).Codec();

        // Try streaming a full file.
        Log::Print("SuiteCodecStream: ");
        Log::Print(filename);
        Log::Print("\n");
        Reinitialise(filename);
        iSem.Wait();
        if (codec == AudioFileDescriptor::eCodecMp3) {
            // LAME FAQ suggests at least ~1057 and ~288 samples can be added to start and end of track, respectively.
            // For our 44.1KHz tracks, we have 1368 extra samples, ~1751040 extra jiffies.
            TUint totalJiffies = TestCodecPipelineElementUpstream::kTotalJiffies + 1751040;
            LOG(kMedia, "iJiffies: %u, totalJiffies: %u\n", iJiffies, totalJiffies);
            //Log::Print("iJiffies: %u, totalJiffies: %u\n", iJiffies, totalJiffies);
            TEST(iJiffies == totalJiffies);
        }
        else {
            LOG(kMedia, "iJiffies: %u, totalJiffies: %u\n", iJiffies, TestCodecPipelineElementUpstream::kTotalJiffies);
            //Log::Print("iJiffies: %u, totalJiffies: %u\n", iJiffies, TestCodecPipelineElementUpstream::kTotalJiffies);
            TEST(iJiffies == TestCodecPipelineElementUpstream::kTotalJiffies);
        }
    }
}


// SuiteCodecSeek

SuiteCodecSeek::SuiteCodecSeek(std::vector<AudioFileDescriptor>& aFiles)
    : SuiteCodecStream("Codec seek tests", aFiles)
    , iSeek(true)
    , iSeekPos(0)
    , iSeekSuccess(false)
{
}

SuiteCodecSeek::SuiteCodecSeek(const TChar* aSuiteName, std::vector<AudioFileDescriptor>& aFiles)
    : SuiteCodecStream(aSuiteName, aFiles)
    , iSeek(true)
    , iSeekPos(0)
    , iSeekSuccess(false)
{
}

SuiteCodecSeek::~SuiteCodecSeek()
{
}

Msg* SuiteCodecSeek::ProcessMsg(MsgAudioPcm* aMsg)
{
    aMsg = (MsgAudioPcm*) SuiteCodecStream::ProcessMsg(aMsg);
    if (iSeek && (iJiffies >= TestCodecPipelineElementUpstream::kTotalJiffies/2)) {
        iSeekSuccess = iController->Seek(0, 0, iSeekPos);
        iSeek = false;
    }
    return aMsg;
}

void SuiteCodecSeek::Reinitialise(const Brx& aFilename)
{
    SuiteCodecStream::Reinitialise(aFilename);
    iSeek = true;
    iSeekSuccess = false;
}

TUint SuiteCodecSeek::ExpectedJiffies(TUint aDuration, TUint aSeekInit, TUint aSeekPos)
{
    TUint durationInSecs = aSeekInit + (aDuration-aSeekPos);
    TUint jiffies = durationInSecs * Jiffies::kJiffiesPerSecond;
    return jiffies;
}

void SuiteCodecSeek::TestSeeking(const Brx& aFilename, TUint aDuration, TUint aSeekPos)
{
    // Try seeking forward to end of file.
    iSeekPos = aSeekPos;
    Reinitialise(aFilename);
    iSem.Wait();
    TUint expectedJiffies = ExpectedJiffies(aDuration, aDuration/2, iSeekPos);
    LOG(kMedia, "iJiffies: %u, expectedJiffies: %u\n", iJiffies, expectedJiffies);
    //Log::Print("iJiffies: %u, expectedJiffies: %u\n", iJiffies, expectedJiffies);
    TEST(iSeekSuccess);
    // Seeking isn't entirely accurate, so check within a bounded range of +/- 1 second.
    TEST(iJiffies >= expectedJiffies - Jiffies::kJiffiesPerSecond);   // Lower bound.
    TEST(iJiffies <= expectedJiffies + Jiffies::kJiffiesPerSecond);   // Upper bound.

}

void SuiteCodecSeek::Test()
{
    std::vector<AudioFileDescriptor>::iterator it;
    for (it = iFiles.begin(); it != iFiles.end(); ++it) {
        TUint duration = TestCodecPipelineElementUpstream::kDuration;
        Brn filename((*it).Filename());

        // Try seeking back to start of file.
        Log::Print("SuiteCodecSeek seeking to start: ");
        Log::Print(filename);
        Log::Print("\n");
        TestSeeking(filename, duration, 0);

        // Try seeking forward to end of file.
        Log::Print("SuiteCodecSeek seeking to end: ");
        Log::Print(filename);
        Log::Print("\n");
        TestSeeking(filename, duration, duration);

        // Try seeking backwards in file.
        Log::Print("SuiteCodecSeek seeking backwards: ");
        Log::Print(filename);
        Log::Print("\n");
        TestSeeking(filename, duration, duration/4);

        // Try seeking forwards in file.
        Log::Print("SuiteCodecSeek seeking forwards: ");
        Log::Print(filename);
        Log::Print("\n");
        TestSeeking(filename, duration, duration - duration/4);
    }
}


// SuiteCodecSeekFromStart

SuiteCodecSeekFromStart::SuiteCodecSeekFromStart(std::vector<AudioFileDescriptor>& aFiles)
    : SuiteCodecSeek("Codec seek from start tests", aFiles)
{
}

SuiteCodecSeekFromStart::~SuiteCodecSeekFromStart()
{
}

Msg* SuiteCodecSeekFromStart::ProcessMsg(MsgAudioPcm* aMsg)
{
    aMsg = (MsgAudioPcm*) SuiteCodecStream::ProcessMsg(aMsg);
    if (iSeek) {
        iSeekSuccess = iController->Seek(0, 0, iSeekPos);
        iSeek = false;
    }
    return aMsg;
}

void SuiteCodecSeekFromStart::TestSeekingFromStart(const Brx& aFilename, TUint aDuration, TUint aSeekPos)
{
    iSeekPos = aSeekPos;
    Reinitialise(aFilename);
    iSem.Wait();
    TUint expectedJiffies = ExpectedJiffies(aDuration, 0, iSeekPos);
    LOG(kMedia, "iJiffies: %u, expectedJiffies: %u\n", iJiffies, expectedJiffies);
    //Log::Print("iJiffies: %u, expectedJiffies: %u\n", iJiffies, expectedJiffies);
    TEST(iSeekSuccess);
    // Seeking isn't entirely accurate, so check within a bounded range of +/- 1 second.
    TEST(iJiffies >= 0);   // Lower bound.
    TEST(iJiffies <= expectedJiffies + Jiffies::kJiffiesPerSecond);   // Upper bound.

}

void SuiteCodecSeekFromStart::Test()
{
    std::vector<AudioFileDescriptor>::iterator it;
    for (it = iFiles.begin(); it != iFiles.end(); ++it) {
        TUint duration = TestCodecPipelineElementUpstream::kDuration;
        Brn filename((*it).Filename());

        // Try seeking from start to middle of file.
        Log::Print("SuiteCodecSeekFromStart seeking to middle: ");
        Log::Print(filename);
        Log::Print("\n");
        TestSeekingFromStart(filename, duration, duration/2);

        // Try seeking from start to end of file.
        Log::Print("SuiteCodecSeekFromStart seeking to end: ");
        TestSeekingFromStart(filename, duration, duration);
        Log::Print(filename);
        Log::Print("\n");
    }
}


// SuiteCodecZeroCrossings

SuiteCodecZeroCrossings::SuiteCodecZeroCrossings(std::vector<AudioFileDescriptor>& aFiles)
    : SuiteCodecStream("Codec zero crossing tests", aFiles)
    , iBitDepth(0)
    , iChannels(0)
    , iZeroCrossings(0)
    , iCrossingDeltaAcceptable(true)
    , iCodec(AudioFileDescriptor::eCodecUnknown)
{
}

SuiteCodecZeroCrossings::~SuiteCodecZeroCrossings()
{
}

void SuiteCodecZeroCrossings::Reinitialise(const Brx& aFilename)
{
    SuiteCodecStream::Reinitialise(aFilename);
    iZeroCrossings = 0;
    iCrossingDeltaAcceptable = true;
}

Msg* SuiteCodecZeroCrossings::TestSimilarity(MsgAudioPcm* aMsg)
{
    TUint byteCount = 0;
    TUint lastCrossingByte = 0;
    TBool negative = false;
    TBool positive = false;

    MsgPlayable* msg = aMsg->CreatePlayable();
    TUint bytes = msg->Bytes();
    ProcessorPcmBufPacked pcmProcessor;
    TUint increment = (iBitDepth/8) * iChannels;
    TUint bytesPerSec = (44100 * iBitDepth * iChannels) / 8;
    TUint bytesPerSine = bytesPerSec/TestCodecPipelineElementUpstream::kFrequencyHz;
    TUint bytesPerCrossing = bytesPerSine/2;
    TUint byteDelta = 0;

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
                        iZeroCrossings++;
                        byteDelta = byteCount - lastCrossingByte;
                        if (lastCrossingByte != 0 && byteDelta != bytesPerCrossing)
                        {
                            if (iCodec != AudioFileDescriptor::eCodecMp3) { // MP3 has problems with zero crossings.
                                if (byteDelta < bytesPerCrossing-10 || byteDelta > bytesPerCrossing+10) {
                                    iCrossingDeltaAcceptable = false;
                                }
                            }
                        }
                        lastCrossingByte = byteCount;
                    }
                    negative = true;
                    positive = false;
                }
                else if (subsample > 0) {
                    if (negative && !positive) {
                        iZeroCrossings++;
                        byteDelta = byteCount - lastCrossingByte;
                        if (lastCrossingByte != 0 && byteDelta != bytesPerCrossing)
                        {
                            if (iCodec != AudioFileDescriptor::eCodecMp3) { // MP3 has problems with zero crossings.
                                if (byteDelta < bytesPerCrossing-10 || byteDelta > bytesPerCrossing+10) {
                                    iCrossingDeltaAcceptable = false;
                                }
                            }
                        }
                        lastCrossingByte = byteCount;
                    }
                    negative = false;
                    positive = true;
                }
            }
            byteCount += iBitDepth/8;
        }
    }

    return msg;
}

Msg* SuiteCodecZeroCrossings::ProcessMsg(MsgAudioPcm* aMsg)
{
    //aMsg = (MsgAudioPcm*) SuiteCodecStream::ProcessMsg(aMsg);
    // This isn't really a MsgAudioPcm! (But it's fine, as all that should be done after is RemoveRef()).
    aMsg = (MsgAudioPcm*) TestSimilarity(aMsg);
    aMsg->RemoveRef();
    aMsg = NULL;
    return aMsg;
}

void SuiteCodecZeroCrossings::Test()
{
    std::vector<AudioFileDescriptor>::iterator it;
    for (it = iFiles.begin(); it != iFiles.end(); ++it) {
        const TUint sineWaves = TestCodecPipelineElementUpstream::kFrequencyHz * TestCodecPipelineElementUpstream::kDuration;
        const TUint expectedZeroCrossings = sineWaves*2 - 1;
        Brn filename((*it).Filename());
        iBitDepth = (*it).BitDepth();
        iChannels = (*it).Channels();
        iCodec = (*it).Codec();

        Log::Print("SuiteCodecZeroCrossings: ");
        Log::Print(filename);
        Log::Print("\n");
        Reinitialise(filename);
        iSem.Wait();
        LOG(kMedia, "iZeroCrossings: %u, expectedZeroCrossings: %u\n", iZeroCrossings, expectedZeroCrossings);
        Log::Print("iZeroCrossings: %u, expectedZeroCrossings: %u\n", iZeroCrossings, expectedZeroCrossings);
        TEST(iZeroCrossings >= expectedZeroCrossings-20);
        if (iCodec == AudioFileDescriptor::eCodecMp3) {
            // MP3 encoders/decoders add silence and some samples of random data to
            // start and end of tracks for filter routines.
            // LAME FAQ suggests this is for at least 1057 samples at start and 288 at end.
            TEST(iZeroCrossings <= expectedZeroCrossings+130);
        }
        else {
            TEST(iZeroCrossings <= expectedZeroCrossings+15);
        }
        TEST(iCrossingDeltaAcceptable);
    }
}


// SuiteCodecInvalidType

SuiteCodecInvalidType::SuiteCodecInvalidType(std::vector<AudioFileDescriptor>& aFiles)
    : SuiteCodecStream("Codec invalid type tests", aFiles)
{
}

SuiteCodecInvalidType::~SuiteCodecInvalidType()
{
}


void SuiteCodecInvalidType::Test()
{
    std::vector<AudioFileDescriptor>::iterator it;
    for (it = iFiles.begin(); it != iFiles.end(); ++it) {
        Brn filename((*it).Filename());

        // Try streaming a corrupt file.
        Log::Print("SuiteCodecInvalidType: ");
        Log::Print(filename);
        Log::Print("\n");
        Reinitialise(filename);
        iSem.Wait();
        LOG(kMedia, "iJiffies: %u, kTotalJiffies: %u\n", iJiffies, TestCodecPipelineElementUpstream::kTotalJiffies);
        TEST(iJiffies == 0); // If we don't exit cleanly and with 0 jiffies of output audio, something is misbehaving.
    }
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

void TestCodec()
{
    std::vector<AudioFileDescriptor> stdFiles;
    stdFiles.push_back(AudioFileDescriptor(Brn("1k_tone-10s-mono.wav"), 16, 1, AudioFileDescriptor::eCodecWav));
    stdFiles.push_back(AudioFileDescriptor(Brn("1k_tone-10s-stereo.wav"), 16, 2, AudioFileDescriptor::eCodecWav));
    stdFiles.push_back(AudioFileDescriptor(Brn("1k_tone-10s-mono-l5-16bit.flac"), 16, 1, AudioFileDescriptor::eCodecFlac));
    stdFiles.push_back(AudioFileDescriptor(Brn("1k_tone-10s-stereo-l5-16bit.flac"), 16, 2, AudioFileDescriptor::eCodecFlac));
    stdFiles.push_back(AudioFileDescriptor(Brn("1k_tone-10s-mono-l5-24bit.flac"), 24, 1, AudioFileDescriptor::eCodecFlac));
    stdFiles.push_back(AudioFileDescriptor(Brn("1k_tone-10s-stereo-l5-24bit.flac"), 24, 2, AudioFileDescriptor::eCodecFlac));
    //stdFiles.push_back(AudioFileDescriptor(Brn("1k_tone-10s-mono-128k.mp3"), 24, 1, AudioFileDescriptor::eCodecMp3));
    //stdFiles.push_back(AudioFileDescriptor(Brn("1k_tone-10s-stereo-128k.mp3"), 24, 2, AudioFileDescriptor::eCodecMp3));
    //stdFiles.push_back(AudioFileDescriptor(Brn("1k-10s-mono-44k.m4a"), 16, 1, AudioFileDescriptor::eCodecAlac));
    //stdFiles.push_back(AudioFileDescriptor(Brn("1k-10s-stereo-44k.m4a"), 16, 2, AudioFileDescriptor::eCodecAlac));
    //stdFiles.push_back(AudioFileDescriptor(Brn("1k-10s-stereo-44k-24bit.m4a"), 24, 2, AudioFileDescriptor::eCodecAlac));

    std::vector<AudioFileDescriptor> invalidFiles;
    invalidFiles.push_back(AudioFileDescriptor(Brn("filetasks.py"), 16, 1, AudioFileDescriptor::eCodecUnknown));          // Large invalid file.
    invalidFiles.push_back(AudioFileDescriptor(Brn("dependencies.json"), 16, 1, AudioFileDescriptor::eCodecUnknown));   // Short invalid file.

    Runner runner("Codec tests\n");
    runner.Add(new SuiteCodecStream(stdFiles));
    runner.Add(new SuiteCodecSeek(stdFiles));
    runner.Add(new SuiteCodecSeekFromStart(stdFiles));
    runner.Add(new SuiteCodecZeroCrossings(stdFiles));
    runner.Add(new SuiteCodecInvalidType(invalidFiles));
    runner.Run();
}
