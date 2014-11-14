#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Pipeline/Reporter.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>

#include <string.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteReporter : public Suite, public IPipelineElementUpstream, private IPipelinePropertyObserver
{
#define KTrackUri "http://host:port/path/file.ext"
    static const TUint kTrackId       = 2;
    static const TUint kBitDepth      = 24;
    static const TUint kSampleRate    = 44100;
    static const TUint kBitRate       = kBitDepth * kSampleRate;
#define kCodecName "Dummy codec"
    static const TUint64 kTrackLength = Jiffies::kPerSecond * 60;
    static const TBool kLossless      = true;
    static const TUint kNumChannels   = 2;
#define kMetaText "SuiteReporter sample metatext"
public:
    SuiteReporter();
    ~SuiteReporter();
    void Test();
public: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IPipelinePropertyObserver
    void NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
private:
    enum EMsgType
    {
        ENone
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgDecodedStream
       ,EMsgTrack
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgQuit
    };
private:
    MsgAudio* CreateAudio();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    Reporter* iReporter;
    EMsgType iNextGeneratedMsg;
    TUint64 iTrackOffset;
    TUint iTrackUpdates;
    TUint iMetaTextUpdates;
    TUint iTimeUpdates;
    TUint iAudioFormatUpdates;
    Bws<1024> iTrackUri;
    TUint iTrackIdPipeline;
    Bws<1024> iMetaText;
    TUint iSeconds;
    TUint iTrackDurationSeconds;
};

} // namespace Media
} // namespace OpenHome


// SuiteReporter

SuiteReporter::SuiteReporter()
    : Suite("Reporter tests")
    , iNextGeneratedMsg(ENone)
    , iTrackOffset(0)
    , iTrackUpdates(0)
    , iMetaTextUpdates(0)
    , iTimeUpdates(0)
    , iAudioFormatUpdates(0)
    , iSeconds(0)
    , iTrackDurationSeconds(0)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iReporter = new Reporter(*this, *this);
}

SuiteReporter::~SuiteReporter()
{
    delete iReporter;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteReporter::Test()
{
    TUint expectedTrackUpdates = 0;
    TUint expectedMetaTextUpdates = 0;
    TUint expectedTimeUpdates = 0;
    TUint expectedAudioFormatUpdates = 0;
    TUint expectedTimeSeconds = 0;

    // deliver MsgTrack then MsgDecodedStream.  Check these are notified.
    iNextGeneratedMsg = EMsgTrack;
    Msg* msg = iReporter->Pull();
    msg->RemoveRef();
    expectedTrackUpdates++;
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iTrackUri == Brn(KTrackUri));
    TEST(iTrackIdPipeline == kTrackId);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    iNextGeneratedMsg = EMsgDecodedStream;
    msg = iReporter->Pull();
    msg->RemoveRef();
    expectedAudioFormatUpdates++;
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
        TEST(iTrackUpdates == expectedTrackUpdates);
        TEST(iMetaTextUpdates == expectedMetaTextUpdates);
        TEST(iTimeUpdates == expectedTimeUpdates);
        TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    }

    // deliver MsgMetaText
    iNextGeneratedMsg = EMsgMetaText;
    msg = iReporter->Pull();
    msg->RemoveRef();
    expectedMetaTextUpdates++;
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    TEST(iMetaText == Brn(kMetaText));
    
    // deliver large MsgSilence.  Check this does not cause NotifyTime to be called.
    iNextGeneratedMsg = EMsgSilence;
    msg = iReporter->Pull();
    msg->RemoveRef();
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);

    // deliver single MsgAudioPcm.  Check NotifyTime is called.
    iNextGeneratedMsg = EMsgAudioPcm;
    msg = iReporter->Pull();
    msg->RemoveRef();
    expectedTimeUpdates++;
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    TEST(iSeconds == expectedTimeSeconds);
    
    // deliver 1s of audio.  Check NotifyTime is called again.
    while (iTrackOffset < Jiffies::kPerSecond) {
        TEST(iTrackUpdates == expectedTrackUpdates);
        TEST(iMetaTextUpdates == expectedMetaTextUpdates);
        TEST(iTimeUpdates == expectedTimeUpdates);
        TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
        TEST(iSeconds == expectedTimeSeconds);
        msg = iReporter->Pull();
        msg->RemoveRef();
    }
    expectedTimeUpdates++;
    expectedTimeSeconds = 1;
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
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    TEST(iSeconds == expectedTimeSeconds);
    iNextGeneratedMsg = EMsgAudioPcm;
    msg = iReporter->Pull();
    msg->RemoveRef();
    expectedTimeSeconds = 3;
    expectedTimeUpdates++;
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    TEST(iSeconds == expectedTimeSeconds);

    // deliver 0.5s of audio.  Check NotifyTime is called again.
    while (iTrackOffset < (4 * Jiffies::kPerSecond)) {
        TEST(iTrackUpdates == expectedTrackUpdates);
        TEST(iMetaTextUpdates == expectedMetaTextUpdates);
        TEST(iTimeUpdates == expectedTimeUpdates);
        TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
        TEST(iSeconds == expectedTimeSeconds);
        msg = iReporter->Pull();
        msg->RemoveRef();
    }
    expectedTimeSeconds++;
    expectedTimeUpdates++;
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    TEST(iSeconds == expectedTimeSeconds);
}

Msg* SuiteReporter::Pull()
{
    switch (iNextGeneratedMsg)
    {
    case EMsgAudioPcm:
        return CreateAudio();
    case EMsgSilence:
        return iMsgFactory->CreateMsgSilence(Jiffies::kPerSecond * 10);
    case EMsgDecodedStream:
        return iMsgFactory->CreateMsgDecodedStream(0, kBitRate, kBitDepth, kSampleRate, kNumChannels, Brn(kCodecName), kTrackLength, 0, kLossless, false, false, NULL);
    case EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brn(KTrackUri), Brx::Empty());
        Msg* msg = iMsgFactory->CreateMsgTrack(*track, kTrackId);
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
        return NULL;
    }
}

MsgAudio* SuiteReporter::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0xff, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 16, EMediaDataEndianLittle, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

void SuiteReporter::NotifyTrack(Track& aTrack, const Brx& /*aMode*/, TUint aIdPipeline)
{
    iTrackUpdates++;
    iTrackUri.Replace(aTrack.Uri());
    iTrackIdPipeline = aIdPipeline;
}

void SuiteReporter::NotifyMetaText(const Brx& aText)
{
    iMetaTextUpdates++;
    iMetaText.Replace(aText);
}

void SuiteReporter::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    iTimeUpdates++;
    iSeconds = aSeconds;
    TEST(iTrackDurationSeconds == aTrackDurationSeconds);
}

void SuiteReporter::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    iAudioFormatUpdates++;
    iTrackDurationSeconds = (TUint)(aStreamInfo.TrackLength() / Jiffies::kPerSecond);
}



void TestReporter()
{
    Runner runner("Reporter tests\n");
    runner.Add(new SuiteReporter());
    runner.Run();
}


