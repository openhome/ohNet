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

class TestCodecPipelineElementUpstream;
class TestCodecPipelineElementDownstream;
class TestCodecInfoAggregator;

class SuiteCodec : public Suite
{
public:
    enum EMode
    {
        eStreamFull = 0,            // Stream full audio
        eStreamSeekBack = 1,        // Stream audio, seeking backwards in the middle
        eStreamSimilar = 2,         // Check output audio is similar to input audio
    };
public:
    enum ECodec
    {
        eCodecWav = 0,
        eCodecFlac = 1,
        eCodecMp3 = 2,
    };
public:
    SuiteCodec();
public:
    static CodecBase* CreateCodec(ECodec aCodec);
private: // from Suite
    ~SuiteCodec();
    void Test();
private:
    void Reset();
    void SetMode(EMode iMode);
    void TestStreamingFull();
    void TestSeekingToStart();
    void TestSeeking();
    TUint TestSimilarity(MsgAudioPcm* aMsg);
    void TestComparison();
    void TestCodec(const Brx& aFilename, ECodec aCodec);
    void TestWav();
    void TestFlac();
    void TestMp3();
private:
    EMode iMode;
    Semaphore iSem;
    Semaphore iSemProcess;
    MsgFactory* iMsgFactory;
    TestCodecPipelineElementUpstream* iElementUpstream;
    TestCodecPipelineElementDownstream* iElementDownstream;
    TestCodecInfoAggregator* iInfoAggregator;
    Container* iContainer;
    CodecController* iController;
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
    ~TestCodecPipelineElementUpstream();
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
    TBool StreamComplete(TUint aTrackId, TUint aStreamId);
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

class TestCodecInfoAggregator : public Av::IInfoAggregator
{
public:
    TestCodecInfoAggregator();
    ~TestCodecInfoAggregator();
public: // from IInfoAggregator
    void Register(Av::IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries);
};

class TestCodecPipelineElementDownstream : public IPipelineElementDownstream, private IMsgProcessor, private INonCopyable
{
public:
    TestCodecPipelineElementDownstream(Semaphore& aSem, Semaphore& aSemProcess, SuiteCodec::EMode aMode);
    ~TestCodecPipelineElementDownstream();
    TUint Jiffies();
    TBool Quit();
    void Reset();
    MsgAudioPcm* AudioPcm();
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
    else if (iSeekEncodedStream) {
        // This is only valid for case of streaming again from beginning of file.
        msg = iMsgFactory.CreateMsgEncodedStream(Brn("10.2.0.1/somefile"),
                Brn("This is an audio file"), iFile->Bytes(), kStreamId, true, false, this);
        iSeekEncodedStream = false;
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
    ASSERTS();
    return 0;
}

TBool TestCodecPipelineElementUpstream::StreamComplete(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    if (iBytesRead >= iFile->Bytes()) {
        return true;
    }
    return false;
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
    if (iMode != SuiteCodec::eStreamSimilar) {
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
    //delete iMsgFactory;
    delete iInfoAggregator;
    delete iElementDownstream;
    delete iElementUpstream;
    
}

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
    iSem.Wait(500);
    TEST(iElementDownstream->Jiffies() == TestCodecPipelineElementUpstream::kTotalJiffies);
    Reset();
}

void SuiteCodec::TestSeekingToStart()
{
    // Try seeking back to start of file.
    SetMode(eStreamSeekBack);
    iSem.Wait(500);              // Should try seek now.
    TBool trySeek = iController->Seek(0, TestCodecPipelineElementUpstream::kStreamId, 0);
    SetMode(eStreamFull);       // Reset mode to continute streaming as normal.
    iSem.Wait(500);             // Wait for end of stream.
    TEST(trySeek == true);
    TUint totalJiffies = TestCodecPipelineElementUpstream::kTotalJiffies;
    totalJiffies += totalJiffies / 2;   // Did a seek back to start from middle of file, so jiffies should be time + time/2.
    LOG(kMedia, "SuiteCodec::Test iElementDownstream->Jiffies() %u\n", iElementDownstream->Jiffies());
    LOG(kMedia, "SuiteCodec::Test totalJiffies() %u\n", totalJiffies);
    // Seeking isn't entirely accurate, so check within a bounded range of +/- 1 second.
    TEST(iElementDownstream->Jiffies() >= totalJiffies - Jiffies::kJiffiesPerSecond);   // Lower bound.
    TEST(iElementDownstream->Jiffies() <= totalJiffies + Jiffies::kJiffiesPerSecond);   // Upper bound.
    Reset();
}

void SuiteCodec::TestSeeking() // FIXME
{
    SetMode(eStreamFull);
    iSem.Wait(500);    // Wait on all messages so we can have an easy cleanup.
    Reset();
}

TUint SuiteCodec::TestSimilarity(MsgAudioPcm* aMsg)
{
    TUint zeroCrossings = 0;
    TBool negative = false;
    TBool positive = false;
    MsgPlayable* msg = aMsg->CreatePlayable();
    TUint bytes = msg->Bytes();
    ProcessorPcmBufPacked pcmProcessor;

    msg->Read(pcmProcessor);
    const TInt8* ptr = (TInt8*) pcmProcessor.Ptr();

    // Measure how many times subsamples pass through zero.
    for (TUint i = 0; i < bytes; i+=2) {
        TInt subsample = ((*ptr++)<<8) + *ptr++;
        if (subsample < 0) {
            if (positive && !negative)
            {
                zeroCrossings++;
            }
            negative = true;
            positive = false;
        }
        else {
            if (negative && !positive)
            {
                zeroCrossings++;
            }
            negative = false;
            positive = true;
        }
    }

    msg->RemoveRef();
    return zeroCrossings;
}

void SuiteCodec::TestComparison()
{
    // Try comparing input vs output samples.
    SetMode(eStreamSimilar);
    const TUint sampleCount = 1;
    TUint count = 0;
    while (true)
    {
        iSem.Wait();
        if (!iElementDownstream->Quit()) {
            if (count < sampleCount) {
                MsgAudioPcm* msg = iElementDownstream->AudioPcm();
                TUint measuredZeroCrossings = TestSimilarity(msg);
                const TUint jiffies = msg->Jiffies();
                const TUint jiffiesMultiples = (Jiffies::kJiffiesPerSecond / jiffies);
                const TUint sineWaves = TestCodecPipelineElementUpstream::kFrequencyHz / jiffiesMultiples;
                const TUint calculatedZeroCrossings = sineWaves*2 - 1;

                LOG(kMedia, "SuiteCodec::Test calculatedZeroCrossings: %u\n", calculatedZeroCrossings);
                LOG(kMedia, "SuiteCodec::Test measuredZeroCrossings: %u\n", measuredZeroCrossings);

                TEST(measuredZeroCrossings >= calculatedZeroCrossings-2);
                TEST(measuredZeroCrossings <= calculatedZeroCrossings+2);
                count++;
                if (count >= sampleCount) {
                    SetMode(eStreamFull);   // Break out of comparison mode, bypassing semaphore-based processing.
                    iSemProcess.Signal();
                    break;
                }
            }
            //else {
            //    SetMode(eStreamFull);
            //    break;
            //}
        }
        else {
            break;
        }
        //iSemProcess.Signal();
    }
    iSem.Wait();
    Reset();
}

void SuiteCodec::TestCodec(const Brx& aFilename, ECodec aCodec)
{
    iElementUpstream->Initialise(aFilename);
    iController = new CodecController(*iMsgFactory, *iContainer, *iElementDownstream);
    iController->AddCodec(CreateCodec(aCodec));
    TestStreamingFull();
    iController = new CodecController(*iMsgFactory, *iContainer, *iElementDownstream);
    iController->AddCodec(CreateCodec(aCodec));
    TestSeekingToStart();
    iController = new CodecController(*iMsgFactory, *iContainer, *iElementDownstream);
    iController->AddCodec(CreateCodec(aCodec));
    TestSeeking();
    iController = new CodecController(*iMsgFactory, *iContainer, *iElementDownstream);
    iController->AddCodec(CreateCodec(aCodec));
    TestComparison();
    Reset();
}

CodecBase* SuiteCodec::CreateCodec(ECodec aCodec)
{
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

void SuiteCodec::TestWav()
{
    Brn file("1k_tone-10s.wav");
    TestCodec(file, eCodecWav);
}

void SuiteCodec::TestFlac()
{
    Brn file("1k_tone-10s-flac_l5_16bit.flac");
    TestCodec(file, eCodecFlac);
}

void SuiteCodec::TestMp3()
{
    Brn file("1k_tone-10s.mp3");
    TestCodec(file, eCodecMp3);
}

void SuiteCodec::Test()
{
    TestWav();
    //TestFlac();
    //TestMp3();
}

void TestCodec()
{
    Runner runner("Codec tests\n");
    runner.Add(new SuiteCodec());
    runner.Run();
}
