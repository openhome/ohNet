#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/VariableDelay.h>
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

class SuiteVariableDelay : public Suite, public IPipelineElement, private IMsgProcessor
{
    static const TUint kDecodedAudioCount = 2;
    static const TUint kMsgAudioPcmCount  = 2;
    static const TUint kMsgSilenceCount   = 1;

    static const TUint kRampDuration = Jiffies::kJiffiesPerMs * 50;
    static const TUint kDelay1       = Jiffies::kJiffiesPerMs * 500;
    static const TUint kDelay2       = Jiffies::kJiffiesPerMs * 300;

    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
public:
    SuiteVariableDelay();
    ~SuiteVariableDelay();
    void Test();
public: // from IPipelineElement
    Msg* Pull();
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
    VariableDelay* iVariableDelay;
    EMsgType iNextGeneratedMsg;
    EMsgType iLastMsg;
    TUint iJiffies;
    TUint iNumMsgsGenerated;
    TUint iAudioMsgSizeJiffies;
    TUint64 iTrackOffset;
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


// SuiteVariableDelay

SuiteVariableDelay::SuiteVariableDelay()
    : Suite("Variable delay tests")
    , iLastMsg(ENone)
    , iNumMsgsGenerated(0)
    , iAudioMsgSizeJiffies(0)
    , iTrackOffset(0)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, kDecodedAudioCount, kMsgAudioPcmCount, kMsgSilenceCount, 1, 1, 1, 1, 1, 1, 1, 1);
    iVariableDelay = new VariableDelay(*iMsgFactory, *this, kRampDuration);
}

SuiteVariableDelay::~SuiteVariableDelay()
{
    delete iVariableDelay;
    delete iMsgFactory;
}

void SuiteVariableDelay::Test()
{
    /*
    Test goes something like
        Add single 0xff filled audio.  Check it can be Pull()ed without ramping.
        Set a delay.  Check audio ramps down, 'delay' jiffies of silence is delivered, audio ramps up.  Check duration of ramps.
        Check that next audio msg is delivered unaltered.
        Check that Silence, Track, MetaText, Halt, Flush & Quit msgs are passed through.
        Reduce delay.  Check audio ramps down then count number of jiffies audio discarded.  Check audio then ramps up.
    */

    // Add single 0xff filled audio.  Check it can be Pull()ed without ramping.
    TEST(iVariableDelay->iStatus == VariableDelay::ERunning);
    iNextGeneratedMsg = EMsgAudioPcm;
    iJiffies = kRampDuration;
    Msg* msg = iVariableDelay->Pull();
    msg = msg->Process(*this);
    ASSERT(msg == NULL);
    TEST(iLastMsg == EMsgAudioPcm);
    TEST(iVariableDelay->iStatus == VariableDelay::ERunning);

    // Set a delay.  Check audio ramps down, 'delay' jiffies of silence is delivered, audio ramps up.  Check duration of ramps.
    iJiffies = 0;
    iVariableDelay->AdjustDelay(kDelay1);
    TEST(iVariableDelay->iStatus == VariableDelay::ERampingDown);
    do {
        msg = iVariableDelay->Pull();
        msg = msg->Process(*this);
        ASSERT(msg == NULL);
        TEST(iLastMsg == EMsgAudioPcm);
    } while (iVariableDelay->iStatus == VariableDelay::ERampingDown);
    TEST(iJiffies == kRampDuration);
    iJiffies = 0;
    do {
        msg = iVariableDelay->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
        TEST(iLastMsg == EMsgSilence);
    } while (iVariableDelay->iStatus == VariableDelay::ERampedDown);
    TEST(iJiffies == kDelay1);
    iJiffies = 0;
    do {
        msg = iVariableDelay->Pull();
        msg = msg->Process(*this);
        ASSERT(msg == NULL);
        TEST(iLastMsg == EMsgAudioPcm);
    } while (iVariableDelay->iStatus == VariableDelay::ERampingUp);
    TEST(iJiffies == kRampDuration);
    TEST(iVariableDelay->iStatus == VariableDelay::ERunning);

    // Check that next audio msg is delivered unaltered.
    msg = iVariableDelay->Pull();
    msg = msg->Process(*this);
    ASSERT(msg == NULL);
    TEST(iLastMsg == EMsgAudioPcm);
    TEST(iVariableDelay->iStatus == VariableDelay::ERunning);

    // Check that Silence, Track, MetaText, Halt, Flush & Quit msgs are passed through.
    EMsgType types[] = { EMsgSilence, EMsgAudioFormat, EMsgTrack, EMsgMetaText, EMsgHalt, EMsgFlush, EMsgQuit };
    for (TUint i=0; i<sizeof(types)/sizeof(types[0]); i++) {
        iNextGeneratedMsg = types[i];
        msg = iVariableDelay->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
        TEST(iLastMsg == types[i]);
        TEST(iVariableDelay->iStatus == VariableDelay::ERunning);
    }

    // Reduce delay.  Check audio ramps down then count number of jiffies audio discarded.  Check audio then ramps up.
    TEST(iVariableDelay->iQueue.IsEmpty());
    iJiffies = 0;
    iNextGeneratedMsg = EMsgAudioPcm;
    iVariableDelay->AdjustDelay(kDelay2);
    TEST(iVariableDelay->iStatus == VariableDelay::ERampingDown);
    do {
        msg = iVariableDelay->Pull();
        msg = msg->Process(*this);
        ASSERT(msg == NULL);
        TEST(iLastMsg == EMsgAudioPcm);
    } while (iVariableDelay->iStatus == VariableDelay::ERampingDown);
    TEST(iJiffies == kRampDuration);
    if (kRampDuration % iAudioMsgSizeJiffies == 0) {
        TEST(iVariableDelay->iQueue.IsEmpty());
    }
    else {
        TEST(!iVariableDelay->iQueue.IsEmpty());
    }
    TEST(iVariableDelay->iStatus == VariableDelay::ERampedDown);
    iJiffies = 0;
    TUint numMsgsGenerated = iNumMsgsGenerated;
    msg = iVariableDelay->Pull();
    msg = msg->Process(*this);
    ASSERT(msg == NULL);
    TEST(iVariableDelay->iStatus == VariableDelay::ERampingUp);
    TEST((kDelay1 - kDelay2) == ((iNumMsgsGenerated - numMsgsGenerated) * iAudioMsgSizeJiffies) + (iAudioMsgSizeJiffies - iJiffies) - (kRampDuration % iAudioMsgSizeJiffies));
    do {
        msg = iVariableDelay->Pull();
        msg = msg->Process(*this);
        ASSERT(msg == NULL);
        TEST(iLastMsg == EMsgAudioPcm);
    } while (iVariableDelay->iStatus == VariableDelay::ERampingUp);
    TEST(iJiffies == kRampDuration);
    TEST(iVariableDelay->iStatus == VariableDelay::ERunning);
}

Msg* SuiteVariableDelay::Pull()
{
    iNumMsgsGenerated++;
    switch (iNextGeneratedMsg)
    {
    case EMsgAudioPcm:
        return CreateAudio();
    case EMsgSilence:
        return iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs);
    case EMsgAudioFormat:
        return iMsgFactory->CreateMsgAudioFormat(0, 0, 0, Brx::Empty(), 0, false);
    case EMsgTrack:
        return iMsgFactory->CreateMsgTrack();
    case EMsgMetaText:
        return iMsgFactory->CreateMsgMetaText(Brn("metatext"));
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

MsgAudio* SuiteVariableDelay::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0xff, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 16, EMediaDataLittleEndian, iTrackOffset);
    iAudioMsgSizeJiffies = audio->Jiffies();
    iTrackOffset += iAudioMsgSizeJiffies;
    return audio;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastMsg = EMsgAudioPcm;
    TUint jiffies = aMsg->Jiffies();

    MsgPlayable* playable = aMsg->CreatePlayable();
    WriterBwh writerBuf(1024);
    playable->Write(writerBuf);
    Brh buf;
    writerBuf.TransferTo(buf);
    const TUint* ptr = (const TUint*)buf.Ptr();
    const TUint firstSubsample = ptr[0];
    const TUint numSubsamples = buf.Bytes() / sizeof(TUint);
    const TUint lastSubsample = ptr[numSubsamples - 1];

    switch (iVariableDelay->iStatus)
    {
    case VariableDelay::ERampingDown:
        TEST(firstSubsample > lastSubsample);
        break;
    case VariableDelay::ERampingUp:
        TEST(firstSubsample < lastSubsample);
        break;
    case VariableDelay::ERampedDown:
        break;
    case VariableDelay::ERunning:
        if (iJiffies >= kRampDuration) {
            TEST(firstSubsample == lastSubsample);
        }
        break;
    }
    iJiffies += jiffies;
    return NULL;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgSilence* aMsg)
{
    iLastMsg = EMsgSilence;
    iJiffies += aMsg->Jiffies();
    return aMsg;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // MsgPlayable not expected at this stage of the pipeline
    return NULL;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgAudioFormat* aMsg)
{
    iLastMsg = EMsgAudioFormat;
    return aMsg;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgTrack* aMsg)
{
    iLastMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgMetaText* aMsg)
{
    iLastMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgHalt* aMsg)
{
    iLastMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgFlush* aMsg)
{
    iLastMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteVariableDelay::ProcessMsg(MsgQuit* aMsg)
{
    iLastMsg = EMsgQuit;
    return aMsg;
}



void TestVariableDelay()
{
    Runner runner("Variable delay tests\n");
    runner.Add(new SuiteVariableDelay());
    runner.Run();
}


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestVariableDelay();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
