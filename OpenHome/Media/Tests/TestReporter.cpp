#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Pipeline/Reporter.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Media/Pipeline/ElementObserver.h>

#include <string.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteReporter : public Suite, public IPipelineElementUpstream, private IPipelinePropertyObserver
{
#define kMode "DummyMode"
#define kTrackUri "http://host:port/path/file.ext"
    static const TUint kBitDepth      = 24;
    static const TUint kSampleRate    = 44100;
    static const TUint kBitRate       = kBitDepth * kSampleRate;
#define kCodecName "Dummy codec"
    static const TUint64 kTrackLength = Jiffies::kPerSecond * 60;
    static const TBool kLossless      = true;
    static const TUint kNumChannels   = 2;
    static const SpeakerProfile kProfile = SpeakerProfile::eStereo;
#define kMetaText "SuiteReporter sample metatext"
    static const TUint kTimeoutMs = 5000;
    static const TUint kThreadPriorityReporter = kPriorityNormal;
public:
    SuiteReporter();
    ~SuiteReporter();
    void Test() override;
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from IPipelinePropertyObserver
    void NotifyMode(const Brx& aMode, const ModeInfo& aInfo) override;
    void NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) override;
private:
    enum EMsgType
    {
        ENone
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgDecodedStream
       ,EMsgMode
       ,EMsgTrack
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgQuit
    };
private:
    void RunTests();
    MsgAudio* CreateAudio();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    PipelineElementObserverThread* iEventThread;
    Reporter* iReporter;
    EMsgType iNextGeneratedMsg;
    TUint64 iTrackOffset;
    TUint iModeUpdates;
    TUint iTrackUpdates;
    TUint iMetaTextUpdates;
    TUint iTimeUpdates;
    TUint iAudioFormatUpdates;
    BwsMode iMode;
    Bws<1024> iTrackUri;
    Bws<1024> iMetaText;
    TUint iSeconds;
    TUint iTrackDurationSeconds;
    Semaphore iSemMode;
    Semaphore iSemTrack;
    Semaphore iSemStream;
    Semaphore iSemMetatext;
    Semaphore iSemTime;
};

} // namespace Media
} // namespace OpenHome


// SuiteReporter

SuiteReporter::SuiteReporter()
    : Suite("Reporter tests")
    , iNextGeneratedMsg(ENone)
    , iTrackOffset(0)
    , iModeUpdates(0)
    , iTrackUpdates(0)
    , iMetaTextUpdates(0)
    , iTimeUpdates(0)
    , iAudioFormatUpdates(0)
    , iSeconds(0)
    , iTrackDurationSeconds(0)
    , iSemMode("SRS1", 0)
    , iSemTrack("SRS2", 0)
    , iSemStream("SRS3", 0)
    , iSemMetatext("SRS4", 0)
    , iSemTime("SRS5", 0)
{
    MsgFactoryInitParams init;
    init.SetMsgDecodedStreamCount(3);
    init.SetMsgTrackCount(3);
    init.SetMsgMetaTextCount(3);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 3);
    iEventThread = new PipelineElementObserverThread(kThreadPriorityReporter-1);
    iReporter = new Reporter(*this, *this, *iEventThread); // aim for a priority just below thread that runs Reporter
}

SuiteReporter::~SuiteReporter()
{
    iEventThread->Stop();
    delete iReporter;
    delete iEventThread;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteReporter::Test()
{
    ThreadFunctor* th = new ThreadFunctor("TestReporter", MakeFunctor(*this, &SuiteReporter::RunTests), kThreadPriorityReporter);
    th->Start();
    delete th; // blocks until thread exits
}

void SuiteReporter::RunTests()
{
    TUint expectedModeUpdates = 0;
    TUint expectedTrackUpdates = 0;
    TUint expectedMetaTextUpdates = 0;
    TUint expectedTimeUpdates = 0;
    TUint expectedAudioFormatUpdates = 0;
    TUint expectedTimeSeconds = 0;

    // deliver MsgMode.  Check it is notified
    iNextGeneratedMsg = EMsgMode;
    Msg* msg = iReporter->Pull();
    msg->RemoveRef();
    iSemMode.Wait(kTimeoutMs);
    expectedModeUpdates++;
    TEST(iModeUpdates == expectedModeUpdates);
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);

    // deliver MsgTrack then MsgDecodedStream.  Check these are notified.
    iNextGeneratedMsg = EMsgTrack;
    msg = iReporter->Pull();
    msg->RemoveRef();
    iSemTrack.Wait(kTimeoutMs);
    expectedTrackUpdates++;
    TEST(iModeUpdates == expectedModeUpdates);
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iTrackUri == Brn(kTrackUri));
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    iNextGeneratedMsg = EMsgDecodedStream;
    msg = iReporter->Pull();
    msg->RemoveRef();
    expectedAudioFormatUpdates++;
    expectedTimeUpdates++;
    iSemStream.Wait(kTimeoutMs);
    iSemTime.Wait(kTimeoutMs);
    TEST(iModeUpdates == expectedModeUpdates);
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);

    // deliver MsgWait, MsgHalt, MsgQuit.  Check these are passed through and don't cause any notifications.
    EMsgType types[] = { EMsgWait, EMsgHalt, EMsgQuit };
    for (TUint i=0; i<sizeof(types)/sizeof(types[0]); i++) {
        iNextGeneratedMsg = types[i];
        msg = iReporter->Pull();
        msg->RemoveRef();
        TEST(iModeUpdates == expectedModeUpdates);
        TEST(iTrackUpdates == expectedTrackUpdates);
        TEST(iMetaTextUpdates == expectedMetaTextUpdates);
        TEST(iTimeUpdates == expectedTimeUpdates);
        TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    }
    TEST(!iSemMode.Clear());
    TEST(!iSemTrack.Clear());
    TEST(!iSemStream.Clear());
    TEST(!iSemMetatext.Clear());
    TEST(!iSemTime.Clear());

    // deliver MsgMetaText
    iNextGeneratedMsg = EMsgMetaText;
    msg = iReporter->Pull();
    msg->RemoveRef();
    expectedMetaTextUpdates++;
    iSemMetatext.Wait(kTimeoutMs);
    TEST(iModeUpdates == expectedModeUpdates);
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    TEST(iMetaText == Brn(kMetaText));
    
    // deliver large MsgSilence.  Check this does not cause NotifyTime to be called.
    iNextGeneratedMsg = EMsgSilence;
    msg = iReporter->Pull();
    msg->RemoveRef();
    Thread::Sleep(1); // tiny delay, leaving room for Reporter's observer thread to be scheduled
    TEST(iModeUpdates == expectedModeUpdates);
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    TEST(!iSemMode.Clear());
    TEST(!iSemTrack.Clear());
    TEST(!iSemStream.Clear());
    TEST(!iSemMetatext.Clear());
    TEST(!iSemTime.Clear());

    // deliver 1s of audio.  Check NotifyTime is called again.
    iNextGeneratedMsg = EMsgAudioPcm;
    while (iTrackOffset < Jiffies::kPerSecond) {
        TEST(iModeUpdates == expectedModeUpdates);
        TEST(iTrackUpdates == expectedTrackUpdates);
        TEST(iMetaTextUpdates == expectedMetaTextUpdates);
        TEST(iTimeUpdates == expectedTimeUpdates);
        TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
        TEST(iSeconds == expectedTimeSeconds);
        msg = iReporter->Pull();
        msg->RemoveRef();
        Thread::Sleep(1); // tiny delay, leaving room for Reporter's observer thread to be scheduled
    }
    iSemTime.Wait(kTimeoutMs);
    TEST(!iSemMode.Clear());
    TEST(!iSemTrack.Clear());
    TEST(!iSemStream.Clear());
    TEST(!iSemMetatext.Clear());
    TEST(!iSemTime.Clear());
    expectedTimeUpdates++;
    expectedTimeSeconds = 1;
    TEST(iModeUpdates == expectedModeUpdates);
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    TEST(iSeconds == expectedTimeSeconds);

    // simulate seeking to 3.5s then deliver single audio msg.  Check NotifyTime is called.
    iTrackOffset = (3 * Jiffies::kPerSecond) + (Jiffies::kPerSecond / 2);
    iNextGeneratedMsg = EMsgDecodedStream;
    msg = iReporter->Pull();
    msg->RemoveRef();
    expectedAudioFormatUpdates++;
    expectedTimeUpdates++;
    expectedTimeSeconds = 3;
    iSemStream.Wait(kTimeoutMs);
    iSemTime.Wait(kTimeoutMs);
    TEST(iModeUpdates == expectedModeUpdates);
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    TEST(iSeconds == expectedTimeSeconds);

    // deliver 0.5s of audio.  Check NotifyTime is called again.
    iNextGeneratedMsg = EMsgAudioPcm;
    while (iTrackOffset < (4 * Jiffies::kPerSecond)) {
        TEST(iTrackUpdates == expectedTrackUpdates);
        TEST(iMetaTextUpdates == expectedMetaTextUpdates);
        TEST(iTimeUpdates == expectedTimeUpdates);
        TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
        TEST(iSeconds == expectedTimeSeconds);
        msg = iReporter->Pull();
        msg->RemoveRef();
        Thread::Sleep(1); // tiny delay, leaving room for Reporter's observer thread to be scheduled
    }
    expectedTimeSeconds++;
    expectedTimeUpdates++;
    iSemTime.Wait(kTimeoutMs);
    TEST(!iSemMode.Clear());
    TEST(!iSemTrack.Clear());
    TEST(!iSemStream.Clear());
    TEST(!iSemMetatext.Clear());
    TEST(!iSemTime.Clear());
    TEST(iModeUpdates == expectedModeUpdates);
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    TEST(iSeconds == expectedTimeSeconds);

    // Check for races - deliver large numbers of track/stream/metatext msgs close together
    EMsgType msgs[] = { EMsgTrack, EMsgDecodedStream, EMsgMetaText };
    size_t numElems = sizeof(msgs)/sizeof(msgs[0]);
    for (TUint i=0; i<numElems; i++) {
        iNextGeneratedMsg = msgs[i];
        for (TUint j=0; j<1000; j++) {
            msg = iReporter->Pull();
            TEST(msg != nullptr); // don't ever expect this to fail - just a nasty way of showing progress
            msg->RemoveRef();
            if (j%64 == 0) {
                Thread::Sleep(1);
            }
        }
    }
    for (TUint k=0; k<1000; k++) {
        iNextGeneratedMsg = msgs[k%numElems];
        msg = iReporter->Pull();
        TEST(msg != nullptr); // don't ever expect this to fail - just a nasty way of showing progress
        msg->RemoveRef();
        if (k%64 == 0) {
            Thread::Sleep(1);
        }
    }
}

Msg* SuiteReporter::Pull()
{
    switch (iNextGeneratedMsg)
    {
    case EMsgAudioPcm:
        return CreateAudio();
    case EMsgSilence:
    {
        TUint size = Jiffies::kPerMs * 10;
        return iMsgFactory->CreateMsgSilence(size, kSampleRate, 16, kNumChannels);
    }
    case EMsgDecodedStream:
    {
        const TUint64 sampleStart = iTrackOffset / Jiffies::PerSample(kSampleRate);
        return iMsgFactory->CreateMsgDecodedStream(0, kBitRate, kBitDepth, kSampleRate, kNumChannels, Brn(kCodecName), kTrackLength, sampleStart, kLossless, false, false, false, kProfile, nullptr);
    }
    case EMsgMode:
        return iMsgFactory->CreateMsgMode(Brn(kMode), true, ModeClockPullers(), true, false);
    case EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brn(kTrackUri), Brx::Empty());
        Msg* msg = iMsgFactory->CreateMsgTrack(*track);
        track->RemoveRef();
        return msg;
    }
    case EMsgMetaText:
        return iMsgFactory->CreateMsgMetaText(Brn(kMetaText));
    case EMsgHalt:
        return iMsgFactory->CreateMsgHalt();
    case EMsgFlush:
        return iMsgFactory->CreateMsgFlush(1);
    case EMsgWait:
        return iMsgFactory->CreateMsgWait();
    case EMsgQuit:
        return iMsgFactory->CreateMsgQuit();
    default:
        ASSERTS();
        return nullptr;
    }
}

MsgAudio* SuiteReporter::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0xff, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 16, AudioDataEndian::Little, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

void SuiteReporter::NotifyMode(const Brx& aMode, const ModeInfo& /*aInfo*/)
{
    iModeUpdates++;
    iMode.Replace(aMode);
    iSemMode.Signal();
}

void SuiteReporter::NotifyTrack(Track& aTrack, const Brx& /*aMode*/, TBool /*aStartOfStream*/)
{
    iTrackUpdates++;
    iTrackUri.Replace(aTrack.Uri());
    iSemTrack.Signal();
}

void SuiteReporter::NotifyMetaText(const Brx& aText)
{
    iMetaTextUpdates++;
    iMetaText.Replace(aText);
    iSemMetatext.Signal();
}

void SuiteReporter::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    iTimeUpdates++;
    iSeconds = aSeconds;
    TEST(iTrackDurationSeconds == aTrackDurationSeconds);
    iSemTime.Signal();
}

void SuiteReporter::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    iAudioFormatUpdates++;
    iTrackDurationSeconds = (TUint)(aStreamInfo.TrackLength() / Jiffies::kPerSecond);
    iSemStream.Signal();
}



void TestReporter()
{
    Runner runner("Reporter tests\n");
    runner.Add(new SuiteReporter());
    runner.Run();
}


