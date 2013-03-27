#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/Flac.h>
#include <OpenHome/Media/Codec/Mp3.h>
#include <OpenHome/Media/Codec/Wav.h>
#include <OpenHome/Media/ProcessorPcmUtils.h>
#include <OpenHome/Private/File.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/Thread.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

namespace OpenHome {
namespace Media {
namespace Codec {

class TestCodecInfoAggregator : public Av::IInfoAggregator
{
public:
    TestCodecInfoAggregator();
    virtual ~TestCodecInfoAggregator();
public: // from IInfoAggregator
    void Register(Av::IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries);
};

class TestCodecPipelineElementUpstream;
class TestCodecPipelineElementDownstream;

class SuiteCodec : public Suite
{
public:
    enum EMode
    {
        eStreamFull = 0,            // Stream full audio
        eStreamSeekBack = 1,        // Stream audio, seeking backwards in the middle
        eStreamSimilar = 2,         // Check output audio is similar to input audio
    };
    enum ECodec
    {
        eCodecWav = 0,
        eCodecFlac = 1,
        eCodecMp3 = 2,
    };
public:
    SuiteCodec();
    CodecBase* CreateCodec(ECodec aCodec);
private: // from Suite
    ~SuiteCodec();
    void Test();
private:
    //void InitialiseFull(const Brx& aFilename);
    void Reset();
    void SetMode(EMode iMode);
    void TestStreamingFull();
    void TestSeekingToStart();
    void TestSeeking();
    TUint Delta(TInt aSubSampleA, TInt aSubSampleB) const;
    TUint TestSimilarity(MsgAudioPcm* aMsg);
    void TestZeroCrossings();
    void TestCodec(const Brx& aFilename, ECodec aCodec);
    void TestWavMono();
    void TestWavStereo();
    void TestFlac16BitMono();
    void TestFlac16BitStereo();
    void TestFlac24BitMono();
    void TestFlac24BitStereo();
    void TestMp3Mono();
    void TestMp3Stereo();
    //void TestInvalidFileType(const Brx& aFilename);
    //void TestCorruptFile(const Brx& aFilename, TUint aJiffies);
private:
    EMode iMode;
    ECodec iCodec;
    Semaphore iSem;
    Semaphore iSemProcess;
    MsgFactory* iMsgFactory;
    TestCodecPipelineElementUpstream* iElementUpstream;
    TestCodecPipelineElementDownstream* iElementDownstream;
    TestCodecInfoAggregator* iInfoAggregator;
    Container* iContainer;
    CodecController* iController;
    TUint iBitDepth;
    TUint iChannels;
};

class TestCodecPipelineElementUpstream : public IPipelineElementUpstream, public IStreamHandler
{
public:
    static const TUint kStreamId = 0;
    static const TUint kDuration = 10;          // Test file duration (in seconds).
    static const TUint kTotalJiffies = kDuration * Jiffies::kJiffiesPerSecond;
    static const TUint kFrequencyHz = 1000;
public:
    TestCodecPipelineElementUpstream(MsgFactory& aMsgFactory, TestCodecPipelineElementDownstream& aElement, Semaphore& aSem, SuiteCodec::EMode aMode);
    virtual ~TestCodecPipelineElementUpstream();
    void Initialise(const Brx& aFilename);
    TUint FileBytes();
    TUint BytesRead();
    void Reset();
    void SetMode(SuiteCodec::EMode aMode);
private: // from Thread
    void Run();
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
    TestCodecPipelineElementDownstream& iElementDownstream;
    Bws<EncodedAudio::kMaxBytes> iBuf;
    TUint iBytesRead;
    TUint iPullCount;
    TBool iSeekFlush;
    TBool iSeekEncodedStream;
    TUint iFlushId;
    SuiteCodec::EMode iMode;
    Semaphore& iSem;
};

class TestCodecPipelineElementDownstream : public IPipelineElementDownstream, private IMsgProcessor, private INonCopyable
{
public:
    TestCodecPipelineElementDownstream(Semaphore& aSem, Semaphore& aSemProcess, SuiteCodec::EMode aMode);
    virtual ~TestCodecPipelineElementDownstream();
    TUint Jiffies();
    TBool Quit();
    void Reset();
    MsgAudioPcm* AudioPcm();
    void ClearAudioPcm();
    void SetMode(SuiteCodec::EMode aMode);
    TBool AllMsgsReceived() const;
public: // from IPipelineElementDownstream
    void Push(Msg* aMsg);
private: // from IMsgProcessor
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
    SuiteCodec::EMode iMode;
    TUint iJiffies;
    Semaphore& iSem;
    Semaphore& iSemProcess;
    TBool iQuit;
    TBool iAllMsgsReceived;
    MsgAudioPcm* iMsg;
};

} // Codec
} // Media
} // OpenHome


// TestCodecPipelineElementUpstream

TestCodecPipelineElementUpstream::TestCodecPipelineElementUpstream(
        MsgFactory& aMsgFactory, TestCodecPipelineElementDownstream& aElement,
        Semaphore& aSem, SuiteCodec::EMode aMode)
    : iFile(NULL)
    , iMsgFactory(aMsgFactory)
    , iElementDownstream(aElement)
    , iBytesRead(0)
    , iPullCount(0)
    , iSeekFlush(false)
    , iSeekEncodedStream(false)
    , iFlushId(MsgFlush::kIdInvalid)
    , iSem(aSem)
{
    iMode = aMode;
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
    // Try reopening the file.
    if (iFile != NULL) {
        delete iFile;
    }
    try {
        iFile = IFile::Open(iFilename.CString(), eFileReadOnly);
    }
    catch (FileOpenError) {
        ASSERTS();
        //throw;
    }
    iBytesRead = 0;
    iPullCount = 0;
}

void TestCodecPipelineElementUpstream::SetMode(SuiteCodec::EMode aMode)
{
    iMode = aMode;
}

Msg* TestCodecPipelineElementUpstream::Pull()
{
    //LOG(kMedia, ">TestCodecPipelineElementUpstream::Pull\n");
    Msg* msg = NULL;

    if (iPullCount == 0) {
        msg = iMsgFactory.CreateMsgEncodedStream(Brn("10.2.0.1/somefile"),
                Brn("This is an audio file"), iFile->Bytes(), kStreamId, true, false, this);
    }
    else if (iSeekFlush) {
        msg = iMsgFactory.CreateMsgFlush(iFlushId);
        iSeekFlush = false;
    }
    //else if (iSeekEncodedStream) {
    //    // This is only valid for case of streaming again from beginning of file.
    //    msg = iMsgFactory.CreateMsgEncodedStream(Brn("10.2.0.1/somefile"),
    //            Brn("This is an audio file"), iFile->Bytes()-iBytesRead, kStreamId, true, false, this);
    //    iSeekEncodedStream = false;
    //}
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

    if (iMode == SuiteCodec::eStreamSeekBack) {
        if (iBytesRead >= iFile->Bytes()/2) {
            iSem.Signal();
        }
    }

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
    iSeekEncodedStream = true;
    return iFlushId;
}

TUint TestCodecPipelineElementUpstream::TryStop(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    return 0;
}


// TestCodecPipelineElementDownstream

TestCodecPipelineElementDownstream::TestCodecPipelineElementDownstream(Semaphore& aSem, Semaphore& aSemProcess, SuiteCodec::EMode aMode)
    : iJiffies(0)
    , iSem(aSem)
    , iSemProcess(aSemProcess)
    , iQuit(false)
    , iMsg(NULL)
{
    iMode = aMode;
}

TestCodecPipelineElementDownstream::~TestCodecPipelineElementDownstream()
{
}

TUint TestCodecPipelineElementDownstream::Jiffies()
{
    return iJiffies;
}

TBool TestCodecPipelineElementDownstream::Quit()
{
    return iQuit;
}

MsgAudioPcm* TestCodecPipelineElementDownstream::AudioPcm()
{
    return iMsg;
}

void TestCodecPipelineElementDownstream::ClearAudioPcm()
{
    iMsg = NULL;
}

void TestCodecPipelineElementDownstream::Reset()
{
    iJiffies = 0;
    iQuit = false;
}

void TestCodecPipelineElementDownstream::SetMode(SuiteCodec::EMode aMode)
{
    iMode = aMode;
}

TBool TestCodecPipelineElementDownstream::AllMsgsReceived() const
{
    return iAllMsgsReceived;
}

void TestCodecPipelineElementDownstream::Push(Msg* aMsg)
{
    //LOG(kMedia, ">TestCodecPipelineElementDownstream::Push\n");
    aMsg->Process(*this);
    if (iMode != SuiteCodec::eStreamSimilar || iMsg == NULL) {
        aMsg->RemoveRef();
    }
}

Msg* TestCodecPipelineElementDownstream::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    //LOG(kMedia, ">TestCodecPipelineElementDownstream::ProcessMsgAudioEncoded\n");
    ASSERTS();
    return NULL;
}
Msg* TestCodecPipelineElementDownstream::ProcessMsg(MsgAudioPcm* aMsg)
{
    //LOG(kMedia, ">TestCodecPipelineElementDownstream::ProcessMsgAudioPcm\n");
    iJiffies += aMsg->Jiffies();
    if (iMode == SuiteCodec::eStreamSimilar) {
        iMsg = aMsg;
        iSem.Signal();
        iSemProcess.Wait();
    }
    return NULL;
}
Msg* TestCodecPipelineElementDownstream::ProcessMsg(MsgSilence* /*aMsg*/)
{
    //LOG(kMedia, ">TestCodecPipelineElementDownstream::ProcessMsgSilence\n");
    ASSERTS();
    return NULL;
}
Msg* TestCodecPipelineElementDownstream::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    //LOG(kMedia, ">TestCodecPipelineElementDownstream::ProcessMsgPlayable\n");
    ASSERTS();
    return NULL;
}
Msg* TestCodecPipelineElementDownstream::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    //LOG(kMedia, ">TestCodecPipelineElementDownstream::ProcessMsgDecodedStream\n");
    return NULL;
}
Msg* TestCodecPipelineElementDownstream::ProcessMsg(MsgTrack* /*aMsg*/)
{
    //LOG(kMedia, ">TestCodecPipelineElementDownstream::ProcessMsgTrack\n");
    ASSERTS();
    return NULL;
}
Msg* TestCodecPipelineElementDownstream::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    //Log::Print("TestCodecPipelineElementDownstream::ProcessMsgEncodedStream\n");
    ASSERTS();
    return NULL;
}
Msg* TestCodecPipelineElementDownstream::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    //LOG(kMedia, ">TestCodecPipelineElementDownstream::ProcessMsgMetaText\n");
    ASSERTS();
    return NULL;
}
Msg* TestCodecPipelineElementDownstream::ProcessMsg(MsgHalt* /*aMsg*/)
{
    //LOG(kMedia, ">TestCodecPipelineElementDownstream::ProcessMsgHalt\n");
    ASSERTS();
    return NULL;
}
Msg* TestCodecPipelineElementDownstream::ProcessMsg(MsgFlush* /*aMsg*/)
{
    //LOG(kMedia, ">TestCodecPipelineElementDownstream::ProcessMsgFlush\n");
    return NULL;
}
Msg* TestCodecPipelineElementDownstream::ProcessMsg(MsgQuit* /*aMsg*/)
{
    //LOG(kMedia, ">TestCodecPipelineElementDownstream::ProcessMsgQuit\n");
    iQuit = true;
    iSem.Signal();
    return NULL;
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


// SuiteCodec

SuiteCodec::SuiteCodec()
    : Suite("Codec tests")
    , iSem("TCO1", 0)
    , iSemProcess("TCO2", 0)
    , iController(NULL)
    , iBitDepth(0)
    , iChannels(0)
{
    iInfoAggregator = new TestCodecInfoAggregator();
    iMsgFactory = new MsgFactory(*iInfoAggregator, 5, 5, 5, 5, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1);
    iElementDownstream = new TestCodecPipelineElementDownstream(iSem, iSemProcess, eStreamFull);
    iElementUpstream = new TestCodecPipelineElementUpstream(*iMsgFactory, *iElementDownstream, iSem, eStreamFull);
    iContainer = new Container(*iMsgFactory, *iElementUpstream);
}

SuiteCodec::~SuiteCodec()
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

//void SuiteCodec::InitialiseFull(const Brx& aFilename)
//{
//    iElementUpstream->Initialise(aFilename);
//    iController = new CodecController(*iMsgFactory, *iContainer, *iElementDownstream);
//    iController->AddCodec(new CodecWav());
//    iController->AddCodec(new CodecFlac());
//    iController->AddCodec(new CodecMp3());
//}

void SuiteCodec::Reset()
{
    if (iController != NULL) {
        delete iController;
        iController = NULL;
    }
    iElementUpstream->Reset();
    iElementDownstream->Reset();
    //iController = new CodecController(*iMsgFactory, *iContainer, *iElementDownstream);
}

void SuiteCodec::SetMode(EMode aMode)
{
    iMode = aMode;
    iElementUpstream->SetMode(aMode);
    iElementDownstream->SetMode(iMode);
}

void SuiteCodec::TestStreamingFull()
{
    // Try streaming a full file.
    SetMode(eStreamFull);
    iSem.Wait();
    LOG(kMedia, "SuiteCodec::TestStreamingFull iElementDownstream->Jiffies: %u, kTotalJiffies: %u\n", iElementDownstream->Jiffies(), TestCodecPipelineElementUpstream::kTotalJiffies);
    TEST(iElementDownstream->Jiffies() == TestCodecPipelineElementUpstream::kTotalJiffies);
    Reset();
}

void SuiteCodec::TestSeekingToStart()
{
    // Try seeking back to start of file.
    SetMode(eStreamSeekBack);
    iSem.Wait();              // Should try seek now.
    TBool trySeek = iController->Seek(0, TestCodecPipelineElementUpstream::kStreamId, 0);
    SetMode(eStreamFull);       // Reset mode to continute streaming as normal.
    iSem.Wait();             // Wait for end of stream.
    TEST(trySeek == true);
    TUint totalJiffies = TestCodecPipelineElementUpstream::kTotalJiffies;
    totalJiffies += totalJiffies / 2;   // Did a seek back to start from middle of file, so jiffies should be time + time/2.
    LOG(kMedia, "SuiteCodec::TestSeekingToStart iElementDownstream->Jiffies() %u\n", iElementDownstream->Jiffies());
    LOG(kMedia, "SuiteCodec::TestSeekingToStart totalJiffies() %u\n", totalJiffies);
        Log::Print("SuiteCodec::TestSeekingToStart iElementDownstream->Jiffies() %u\n", iElementDownstream->Jiffies());
    Log::Print("SuiteCodec::TestSeekingToStart totalJiffies() %u\n", totalJiffies);
    // Seeking isn't entirely accurate, so check within a bounded range of +/- 1 second.
    TEST(iElementDownstream->Jiffies() >= totalJiffies - Jiffies::kJiffiesPerSecond);   // Lower bound.
    TEST(iElementDownstream->Jiffies() <= totalJiffies + Jiffies::kJiffiesPerSecond);   // Upper bound.
    Reset();
}

void SuiteCodec::TestSeeking() // FIXME
{
    SetMode(eStreamFull);
    iSem.Wait();    // Wait on all messages so we can have an easy cleanup.
    Reset();
}

TUint SuiteCodec::TestSimilarity(MsgAudioPcm* aMsg)
{
    TUint zeroCrossings = 0;
    TBool negative = false;
    TBool positive = false;
    //TInt lastValue = 0;
    //TUint lastDelta = 0;
    MsgPlayable* msg = aMsg->CreatePlayable();
    iElementDownstream->ClearAudioPcm();    // MsgPlayable takes reference away.
    TUint bytes = msg->Bytes();
    ProcessorPcmBufPacked pcmProcessor;
    TUint increment = (iBitDepth/8) * iChannels;

    msg->Read(pcmProcessor);
    const TInt8* ptr = (TInt8*) pcmProcessor.Ptr();

    // Measure how many times subsamples pass through zero.
    for (TUint i = 0; i < bytes; i += increment) {
        for (TUint j = 0; j < iChannels; j++) {
            TInt subsample = 0;

            switch (iBitDepth)
            {
            case 16:
                subsample += ((*ptr++) << 8);
                subsample += *ptr++;
                break;
            case 24:
                subsample += ((*ptr++) << 16);
                subsample += ((*ptr++) << 8);
                subsample += *ptr++;
                break;
            default:
                ASSERTS();
            }

            if (j == 0) { // Only do subsample comparison on a single channel.
                if (subsample < 0) {
                    if (positive && !negative) {
                        zeroCrossings++;
                    }
                    negative = true;
                    positive = false;
                }
                else if (subsample > 0) {
                    if (negative && !positive) {
                        zeroCrossings++;
                    }
                    negative = false;
                    positive = true;
                }
                //lastDelta = Delta(lastValue, subsample);
                //lastValue = subsample;
            }
        }
    }

    msg->RemoveRef();
    return zeroCrossings;
}

void SuiteCodec::TestZeroCrossings()
{
    // Try comparing input vs output samples.
    SetMode(eStreamSimilar);

    TUint measuredZeroCrossings = 0;
    const TUint sineWaves = TestCodecPipelineElementUpstream::kFrequencyHz * TestCodecPipelineElementUpstream::kDuration;
    const TUint calculatedZeroCrossings = sineWaves*2 - 1;

    while (true) {
        iSem.Wait();
        if (!iElementDownstream->Quit()) {  // iSem only signalled when stepping-through AudioPcm processing or on quit.
            MsgAudioPcm* msg = iElementDownstream->AudioPcm();

            LOG(kMedia, "SuiteCodec::TestComparison calculatedZeroCrossings: %u\n", calculatedZeroCrossings);
            LOG(kMedia, "SuiteCodec::TestComparison measuredZeroCrossings: %u\n", measuredZeroCrossings);

            measuredZeroCrossings += TestSimilarity(msg);
            iSemProcess.Signal();
            //Log::Print("measuredZeroCrossings: %u, calculatedZeroCrossings: %u\n", measuredZeroCrossings, calculatedZeroCrossings);
        }
        else {
            break;
        }
    }

    TEST(measuredZeroCrossings >= calculatedZeroCrossings-20);
    if (iCodec == eCodecMp3) {
        // MP3 encoders/decoders add silence and some samples of random data to start of tracks for filter routines.
        // LAME FAQ suggests this is for 1057 samples.
        TEST(measuredZeroCrossings <= calculatedZeroCrossings+100);
    }
    else {
        TEST(measuredZeroCrossings <= calculatedZeroCrossings+15);
    }

    Reset();
}

//void SuiteCodec::TestInvalidFileType(const Brx& aFilename)
//{
//    Log::Print("TestInvalidFileType\n");
//    // Send in a non-audio file to test that no audio data is output.
//    SetMode(eStreamFull);
//    InitialiseFull(aFilename);
//    iSem.Wait();
//    LOG(kMedia, "SuiteCodec::TestInvalidFileType iElementDownstream->Jiffies: %u\n", iElementDownstream->Jiffies());
//    TEST(iElementDownstream->Jiffies() == 0);
//    Reset();
//}

//void SuiteCodec::TestCorruptFile(const Brx& aFilename, TUint aJiffies)
//{
//    // Send in a corrupt audio file.
//    SetMode(eStreamFull);
//    InitialiseFull(aFilename);
//    iSem.Wait();
//    LOG(kMedia, "SuiteCodec::TestCorruptFileStartStream iElementDownstream->Jiffies: %u, aJiffies: %u\n", iElementDownstream->Jiffies(), aJiffies);
//    TEST(iElementDownstream->Jiffies() == aJiffies);
//    Reset();
//}

void SuiteCodec::TestCodec(const Brx& aFilename, ECodec aCodec)
{
    iElementUpstream->Initialise(aFilename);
    iController = new CodecController(*iMsgFactory, *iContainer, *iElementDownstream);
    iController->AddCodec(CreateCodec(aCodec));
    TestStreamingFull();
    //iController = new CodecController(*iMsgFactory, *iContainer, *iElementDownstream);
    //iController->AddCodec(CreateCodec(aCodec));
    //TestSeekingToStart();
    iController = new CodecController(*iMsgFactory, *iContainer, *iElementDownstream);
    iController->AddCodec(CreateCodec(aCodec));
    TestSeeking();
    iController = new CodecController(*iMsgFactory, *iContainer, *iElementDownstream);
    iController->AddCodec(CreateCodec(aCodec));
    TestZeroCrossings();
    Reset();
}

CodecBase* SuiteCodec::CreateCodec(ECodec aCodec)
{
    iCodec = aCodec;

    switch (aCodec)
    {
    case eCodecWav:
        return new CodecWav();
    case eCodecFlac:
        return new CodecFlac();
    case eCodecMp3:
        return new CodecMp3();
    default:
        ASSERTS();      // Shouldn't happen in test cases.
        return NULL;    // Compiler doesn't know assert will prevent reaching here.
    }
}

void SuiteCodec::TestWavMono()
{
    Log::Print("TestWavMono\n");
    Brn file("1k_tone-10s-mono.wav");
    iBitDepth = 16;
    iChannels = 1;
    TestCodec(file, eCodecWav);
}

void SuiteCodec::TestWavStereo()
{
    Log::Print("TestWavStereo\n");
    Brn file("1k_tone-10s-stereo.wav");
    iBitDepth = 16;
    iChannels = 2;
    TestCodec(file, eCodecWav);
}

void SuiteCodec::TestFlac16BitMono()
{
    Log::Print("TestFlac16BitMono\n");
    Brn file("1k_tone-10s-mono-l5-16bit.flac");
    iBitDepth = 16;
    iChannels = 1;
    TestCodec(file, eCodecFlac);
}

void SuiteCodec::TestFlac16BitStereo()
{
    Log::Print("TestFlac16BitStereo\n");
    Brn file("1k_tone-10s-stereo-l5-16bit.flac");
    iBitDepth = 16;
    iChannels = 2;
    TestCodec(file, eCodecFlac);
}

void SuiteCodec::TestFlac24BitMono()
{
    Log::Print("TestFlac24BitMono\n");
    Brn file("1k_tone-10s-mono-l5-24bit.flac");
    iBitDepth = 24;
    iChannels = 1;
    TestCodec(file, eCodecFlac);
}

void SuiteCodec::TestFlac24BitStereo()
{
    Log::Print("TestFlac24BitStereo\n");
    Brn file("1k_tone-10s-stereo-l5-24bit.flac");
    iBitDepth = 24;
    iChannels = 2;
    TestCodec(file, eCodecFlac);
}

void SuiteCodec::TestMp3Mono()
{
    Log::Print("TestMp3Mono\n");
    Brn file("1k_tone-10s-mono-128k.mp3");
    iBitDepth = 24;
    iChannels = 1;
    TestCodec(file, eCodecMp3);
}

void SuiteCodec::TestMp3Stereo()
{
    Log::Print("TestMp3Stereo\n");
    Brn file("1k_tone-10s-stereo-128k.mp3");
    iBitDepth = 24;
    iChannels = 2;
    TestCodec(file, eCodecMp3);
}



void SuiteCodec::Test()
{
    TestWavMono();
    TestWavStereo();
    TestFlac16BitMono();
    TestFlac16BitStereo();
    TestFlac24BitMono();
    TestFlac24BitStereo();
    TestMp3Mono();
    TestMp3Stereo();
    //TestInvalidFileType(Brn("config.log"));
    //TestCorruptFile(Brn("1k_tone-10s-stereo-l5-16bit-error_start.flac"), 0);
    //TestCorruptFile(Brn("1k_tone-10s-stereo-l5-16bit-error_mid.flac"), 0);
    //TestCorruptFile(Brn("1k_tone-10s-stereo-l5-16bit-error_shortmid.flac"), 0);
    //TestCorruptFile(Brn("1k_tone-10s-stereo-l5-16bit-error_end.flac"), 0);
}

void TestCodec()
{
    Runner runner("Codec tests\n");
    runner.Add(new SuiteCodec());
    runner.Run();
}
