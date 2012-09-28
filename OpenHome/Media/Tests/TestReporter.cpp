#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Reporter.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/InfoProvider.h>

#include <string.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class InfoAggregator : public Av::IInfoAggregator, private IWriter
{
public:
    InfoAggregator();
    void PrintStats();
private: // from IInfoAggregator
    void Register(Av::IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries);
private: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
private:
    std::vector<Av::IInfoProvider*> iInfoProviders;
};

class SuiteReporter : public Suite, public IPipelineElement, private IPipelinePropertyObserver
{
    static const TUint kBitDepth      = 24;
    static const TUint kSampleRate    = 44100;
    static const TUint kBitRate       = kBitDepth * kSampleRate;
#define kCodecName "Dummy codec"
    static const TUint64 kTrackLength = Jiffies::kJiffiesPerSecond * 60;
    static const TBool kLossless      = true;
    static const TUint kNumChannels   = 2;
#define kMetaText "SuiteReporter sample metatext"
public:
    SuiteReporter();
    ~SuiteReporter();
    void Test();
public: // from IPipelineElement
    Msg* Pull();
private: // from IMsgProcessor
    void NotifyTrack();
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyAudioFormat(const AudioFormat& aFormat);
private:
    enum EMsgType
    {
        ENone
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgAudioFormat
       ,EMsgTrack
       ,EMsgMetaText
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgQuit
    };
private:
    MsgAudio* CreateAudio();
private:
    MsgFactory* iMsgFactory;
    InfoAggregator iInfoAggregator;
    Reporter* iReporter;
    EMsgType iNextGeneratedMsg;
    TUint64 iTrackOffset;
    TUint iTrackUpdates;
    TUint iMetaTextUpdates;
    TUint iTimeUpdates;
    TUint iAudioFormatUpdates;
    Bws<1024> iMetaText;
    TUint iSeconds;
    TUint iTrackDurationSeconds;
};

} // namespace Media
} // namespace OpenHome


// InfoAggregator

InfoAggregator::InfoAggregator()
{
}

void InfoAggregator::PrintStats()
{
    for (size_t i=0; i<iInfoProviders.size(); i++) {
        iInfoProviders[i]->QueryInfo(AllocatorBase::kQueryMemory, *this);
    }
}

void InfoAggregator::Register(Av::IInfoProvider& aProvider, std::vector<Brn>& /*aSupportedQueries*/)
{
    iInfoProviders.push_back(&aProvider);
}

void InfoAggregator::Write(TByte aValue)
{
    Print("%c", aValue);
}

void InfoAggregator::Write(const Brx& aBuffer)
{
    Print(aBuffer);
}

void InfoAggregator::WriteFlush()
{
}


// SuiteReporter

SuiteReporter::SuiteReporter()
    : Suite("Variable delay tests")
    , iNextGeneratedMsg(ENone)
    , iTrackOffset(0)
    , iTrackUpdates(0)
    , iMetaTextUpdates(0)
    , iTimeUpdates(0)
    , iAudioFormatUpdates(0)
    , iSeconds(0)
    , iTrackDurationSeconds(0)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    iReporter = new Reporter(*this, *this);
}

SuiteReporter::~SuiteReporter()
{
    delete iReporter;
    delete iMsgFactory;
}

void SuiteReporter::Test()
{
    TUint expectedTrackUpdates = 0;
    TUint expectedMetaTextUpdates = 0;
    TUint expectedTimeUpdates = 0;
    TUint expectedAudioFormatUpdates = 0;
    TUint expectedTimeSeconds = 0;

    // deliver MsgTrack then MsgAudioFormat.  Check these are notified.
    iNextGeneratedMsg = EMsgTrack;
    Msg* msg = iReporter->Pull();
    msg->RemoveRef();
    expectedTrackUpdates++;
    expectedMetaTextUpdates++;
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);
    iNextGeneratedMsg = EMsgAudioFormat;
    msg = iReporter->Pull();
    msg->RemoveRef();
    expectedAudioFormatUpdates++;
    TEST(iTrackUpdates == expectedTrackUpdates);
    TEST(iMetaTextUpdates == expectedMetaTextUpdates);
    TEST(iTimeUpdates == expectedTimeUpdates);
    TEST(iAudioFormatUpdates == expectedAudioFormatUpdates);

    // deliver MsgHalt, MsgQuit.  Check these are passed through and don't cause any notifications.
    EMsgType types[] = { EMsgHalt, EMsgQuit };
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
    while (iTrackOffset < Jiffies::kJiffiesPerSecond) {
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
    iTrackOffset = (3 * Jiffies::kJiffiesPerSecond) + (Jiffies::kJiffiesPerSecond / 2);
    iNextGeneratedMsg = EMsgAudioFormat;
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
    while (iTrackOffset < (4 * Jiffies::kJiffiesPerSecond)) {
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
        return iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerSecond * 10);
    case EMsgAudioFormat:
        return iMsgFactory->CreateMsgAudioFormat(kBitRate, kBitDepth, kSampleRate, Brn(kCodecName), kTrackLength, kLossless);
    case EMsgTrack:
        return iMsgFactory->CreateMsgTrack();
    case EMsgMetaText:
        return iMsgFactory->CreateMsgMetaText(Brn(kMetaText));
    case EMsgHalt:
        return iMsgFactory->CreateMsgHalt();
    case EMsgFlush:
        return iMsgFactory->CreateMsgFlush();
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
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 16, EMediaDataLittleEndian, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

void SuiteReporter::NotifyTrack()
{
    iTrackUpdates++;
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

void SuiteReporter::NotifyAudioFormat(const AudioFormat& aFormat)
{
    iAudioFormatUpdates++;
    iTrackDurationSeconds = (TUint)(aFormat.TrackLength() / Jiffies::kJiffiesPerSecond);
}



void TestReporter()
{
    Runner runner("Reporter tests\n");
    runner.Add(new SuiteReporter());
    runner.Run();
}


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestReporter();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
