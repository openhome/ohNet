// Tests that input to and output from pipeline are identical
// ...in the absense of any user action which would cause ramping
// Kind of like TestPipeline2 but this time with manufactured data.
//
// Relies on thread priorities being respected so may be problematic on Linux

#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Net/Core/OhNet.h>
#include "AllocatorInfoLogger.h"
#include <OpenHome/Media/ProcessorPcmUtils.h>

#include <stdio.h>

namespace OpenHome {
namespace Media {

class SupplierTp3 : public Thread, public ISupplier
{
    static const TUint kNumChannels = 2;
    static const TUint kSampleRate = 44100;
    static const TUint kBitDepth = 16;
    static const TUint kMsgAudioCount = 2000;
public:
    SupplierTp3();
    ~SupplierTp3();
private: // from Thread
    void Run();
private: // from ISupplier
    void Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement);
    void Play();
    void Flush(Msg* aMsg);
    void Quit(Msg* aMsg);
private:
    MsgFactory* iMsgFactory;
    IPipelineElementDownstream* iPipeline;
    Bws<DecodedAudio::kMaxBytes> iBuf;
    TUint iRemainingMsgAudio;
    TUint64 iTrackOffset;
};

class DriverTp3 : public Thread, private IMsgProcessor, private IPcmProcessor
{
public:
    DriverTp3(IPipelineElementUpstream& aPipeline);
    ~DriverTp3();
private: // from Thread
    void Run();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgAudioFormat* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private: // from IPcmProcessor
    void BeginBlock();
    TBool ProcessFragment8(const Brx& aData, TUint aNumChannels);
    TBool ProcessFragment16(const Brx& aData, TUint aNumChannels);
    TBool ProcessFragment24(const Brx& aData, TUint aNumChannels);
    void ProcessSample8(const TByte* aSample, TUint aNumChannels);
    void ProcessSample16(const TByte* aSample, TUint aNumChannels);
    void ProcessSample24(const TByte* aSample, TUint aNumChannels);
    void EndBlock();
private:
    IPipelineElementUpstream& iPipeline;
    TUint iExpectedNextSubsample;
    TBool iQuit;
};

class TestPipeline3 : private IPipelineObserver
{
public:
    TestPipeline3();
    ~TestPipeline3();
    void Run();
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack();
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyAudioFormat(const AudioFormat& aFormat);
private:
    Semaphore iSem;
    SupplierTp3* iSupplier;
    AllocatorInfoLogger iInfoAggregator;
    PipelineManager* iPipeline;
    DriverTp3* iDriver;
};

} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// SupplierTp3

SupplierTp3::SupplierTp3()
    : Thread("SWAV"/*, kPriorityHighest*/)
    , iMsgFactory(NULL)
    , iPipeline(NULL)
    , iRemainingMsgAudio(kMsgAudioCount)
    , iTrackOffset(0)
{
    TByte* p = const_cast<TByte*>(iBuf.Ptr());
    iBuf.SetBytes(iBuf.MaxBytes());
    const TUint bytesPerSample = kNumChannels * (kBitDepth/8);
    TByte val = 0;
    for (TUint i=0; i<iBuf.Bytes(); i+=bytesPerSample) {
        for (TUint j=0; j<bytesPerSample; j++) {
            p[i+j] = val++;
        }
    }
}

SupplierTp3::~SupplierTp3()
{
    Join();
}

void SupplierTp3::Run()
{
    Msg* msg = iMsgFactory->CreateMsgTrack();
    iPipeline->Push(msg);
    const TUint bitRate = kSampleRate * kBitDepth * kNumChannels;
    const TUint numSamples = kMsgAudioCount * (iBuf.Bytes() / (kNumChannels * (kBitDepth/8)));
    const TUint64 trackLengthJiffies = ((TUint64)numSamples * Jiffies::kJiffiesPerSecond) / kSampleRate;
    msg = iMsgFactory->CreateMsgAudioFormat(bitRate, kBitDepth, kSampleRate, kNumChannels, Brn("MadeUp"), trackLengthJiffies, true);
    iPipeline->Push(msg);
    while (iRemainingMsgAudio > 0) {
        MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(iBuf, kNumChannels, kSampleRate, kBitDepth, EMediaDataBigEndian, iTrackOffset);
        iTrackOffset += audio->Jiffies();
        iPipeline->Push(audio);
        Thread::Sleep(1);
        iRemainingMsgAudio--;
    }
    msg = iMsgFactory->CreateMsgHalt();
    iPipeline->Push(msg);
}

void SupplierTp3::Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement)
{
    iMsgFactory = &aMsgFactory;
    iPipeline = &aDownstreamElement;
}

void SupplierTp3::Play()
{
    Start();
}

void SupplierTp3::Flush(Msg* aMsg)
{
    iPipeline->Push(aMsg);
}

void SupplierTp3::Quit(Msg* aMsg)
{
    iPipeline->Push(aMsg);
}


// DriverTp3

DriverTp3::DriverTp3(IPipelineElementUpstream& aPipeline)
    : Thread("DRAC", kPriorityLowest)
    , iPipeline(aPipeline)
    , iExpectedNextSubsample(0)
    , iQuit(false)
{
    Start();
}

DriverTp3::~DriverTp3()
{
    Join();
}

void DriverTp3::Run()
{
    do {
        Msg* msg = iPipeline.Pull();
        (void)msg->Process(*this);
        Thread::Sleep(2); // nasty but don't seem able to rely on highest priority thread always being scheduled
    } while (!iQuit);
}

Msg* DriverTp3::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverTp3::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverTp3::ProcessMsg(MsgPlayable* aMsg)
{
    aMsg->Read(*this);
    aMsg->RemoveRef();
    return NULL;
}

Msg* DriverTp3::ProcessMsg(MsgAudioFormat* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* DriverTp3::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverTp3::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverTp3::ProcessMsg(MsgHalt* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* DriverTp3::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverTp3::ProcessMsg(MsgQuit* aMsg)
{
    iQuit = true;
    aMsg->RemoveRef();
    return NULL;
}

void DriverTp3::BeginBlock()
{
}

TBool DriverTp3::ProcessFragment8(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    return false;
}

TBool DriverTp3::ProcessFragment16(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    return false;
}

TBool DriverTp3::ProcessFragment24(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    return false;
}

void DriverTp3::ProcessSample8(const TByte* /*aSample*/, TUint /*aNumChannels*/)
{
    ASSERTS(); // expecting 16-bit data
}

void DriverTp3::ProcessSample16(const TByte* aSample, TUint aNumChannels)
{
    for (TUint i=0; i<2*aNumChannels; i++) {
        ASSERT(*aSample++ == iExpectedNextSubsample++);
    }
    if (iExpectedNextSubsample == 256) {
        iExpectedNextSubsample = 0;
    }
}

void DriverTp3::ProcessSample24(const TByte* /*aSample*/, TUint /*aNumChannels*/)
{
    ASSERTS(); // expecting 16-bit data
}

void DriverTp3::EndBlock()
{
}


// TestPipeline3

TestPipeline3::TestPipeline3()
    : iSem("TP3 ", 0)
{
    iSupplier = new SupplierTp3();
    iPipeline = new PipelineManager(iInfoAggregator, *iSupplier, *this, Jiffies::kJiffiesPerMs * 5);
    iDriver = new DriverTp3(iPipeline->FinalElement());
}

TestPipeline3::~TestPipeline3()
{
    delete iPipeline;
    delete iSupplier;
    delete iDriver;
}

void TestPipeline3::Run()
{
    iPipeline->Play();
    iSem.Wait(); // blocks until all audio has been played
}

void TestPipeline3::NotifyPipelineState(EPipelineState aState)
{
    if (aState == EPipelinePaused) {
        iSem.Signal();
    }
}

void TestPipeline3::NotifyTrack()
{
}

void TestPipeline3::NotifyMetaText(const Brx& /*aText*/)
{
}

void TestPipeline3::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    Log::Print("Pipeline report property: TIME {secs=%u; duration=%u}\n", aSeconds, aTrackDurationSeconds);
}

void TestPipeline3::NotifyAudioFormat(const AudioFormat& /*aFormat*/)
{
}



void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestPipeline3* tp3 = new TestPipeline3();
    tp3->Run();
    Log::Print("\nTest complete.  All audio transmitted correctly.\n");
    delete tp3;
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
