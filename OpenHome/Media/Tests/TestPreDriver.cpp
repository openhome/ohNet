#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/PreDriver.h>
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

class SuitePreDriver : public Suite, private IPipelineElementUpstream, private IMsgProcessor
{
    static const TUint kMsgFormatCount = 2;

    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
public:
    SuitePreDriver();
    ~SuitePreDriver();
    void Test();
private: // from IPipelineElementUpstream
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
    PreDriver* iPreDriver;
    EMsgType iNextGeneratedMsg;
    EMsgType iLastMsg;
    TUint64 iTrackOffset;
    TUint iSampleRate;
    TUint iBitDepth;
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


// SuitePreDriver

SuitePreDriver::SuitePreDriver()
    : Suite("Pre-Driver tests")
    , iLastMsg(ENone)
    , iTrackOffset(0)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 1, 1, 1, kMsgFormatCount, 1, 1, 1, 1, 1);
    iPreDriver = new PreDriver(*iMsgFactory, *this);
}

SuitePreDriver::~SuitePreDriver()
{
    delete iPreDriver;
    delete iMsgFactory;
}

void SuitePreDriver::Test()
{
    /*
    Test goes something like
        Send Format msg; check it is passed on.
        Send Audio; check it is passed on.
        Send Silence; check it is passed on.
        Send Quit; check it is passed on.
        Send Track than MetaText; check neither are passed on.
        Send Format with same sample rate + bit depth.  Check it isn't passed on (we move on to Silence instead).
        Send Halt; check it is passed on.
        Send Audio then Format with different sample rate.  Check Halt is delivered before Format.
        Send Audio then Format with different bit depth.  Check Halt is delivered before Format.
    */

    iSampleRate = 44100;
    iBitDepth = 16;

    // Send Format msg; check it is passed on.
    iNextGeneratedMsg = EMsgAudioFormat;
    Msg* msg = iPreDriver->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
    TEST(iLastMsg == EMsgAudioFormat);

    // Send Audio; check it is passed on.
    iNextGeneratedMsg = EMsgAudioPcm;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgPlayable);

    // Send Silence; check it is passed on.
    iNextGeneratedMsg = EMsgSilence;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgPlayable);

    // Send Quit; check it is passed on.
    iNextGeneratedMsg = EMsgQuit;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgQuit);

    // Send Track than MetaText; check neither are passed on.
    iNextGeneratedMsg = EMsgTrack;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgPlayable);
    iNextGeneratedMsg = EMsgMetaText;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgPlayable);

    // Send Format with same sample rate + bit depth.  Check it isn't passed on (we move on to Silence instead).
    iNextGeneratedMsg = EMsgAudioFormat;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgPlayable);

    // Send Halt; check it is passed on.
    iNextGeneratedMsg = EMsgHalt;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgHalt);

    // Send Audio then Format with different sample rate.  Check Halt is delivered before Format.
    iNextGeneratedMsg = EMsgAudioPcm;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgPlayable);
    iSampleRate = 48000;
    iNextGeneratedMsg = EMsgAudioFormat;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgHalt);
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgAudioFormat);

    // Send Audio then Format with different bit depth.  Check Halt is delivered before Format.
    iNextGeneratedMsg = EMsgAudioPcm;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgPlayable);
    iBitDepth = 24;
    iNextGeneratedMsg = EMsgAudioFormat;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgHalt);
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgAudioFormat);
}

Msg* SuitePreDriver::Pull()
{
    switch (iNextGeneratedMsg)
    {
    default:
    case ENone:
    case EMsgPlayable:
        ASSERTS();
        return NULL;
    case EMsgAudioPcm:
        return CreateAudio();
    case EMsgSilence:
        return iMsgFactory->CreateMsgSilence(Jiffies::kJiffiesPerMs);
    case EMsgAudioFormat:
        iNextGeneratedMsg = EMsgSilence;
        return iMsgFactory->CreateMsgAudioFormat(128000, iBitDepth, iSampleRate, kNumChannels, Brn("dummy codec"), (TUint64)1<<31, false);
    case EMsgTrack:
        iNextGeneratedMsg = EMsgAudioPcm; // msg will be discarded by PreDriver which will immediately Pull again.
                                          // Ensure we have something different to deliver to avoid an infinite loop.
        return iMsgFactory->CreateMsgTrack();
    case EMsgMetaText:
        iNextGeneratedMsg = EMsgAudioPcm;
        return iMsgFactory->CreateMsgMetaText(Brn("metatext"));
    case EMsgHalt:
        return iMsgFactory->CreateMsgHalt();
    case EMsgFlush:
        return iMsgFactory->CreateMsgFlush();
    case EMsgQuit:
        return iMsgFactory->CreateMsgQuit();
    }
}

MsgAudio* SuitePreDriver::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0xff, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 16, EMediaDataLittleEndian, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

Msg* SuitePreDriver::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePreDriver::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePreDriver::ProcessMsg(MsgPlayable* aMsg)
{
    iLastMsg = EMsgPlayable;
    return aMsg;
}

Msg* SuitePreDriver::ProcessMsg(MsgAudioFormat* aMsg)
{
    TEST(aMsg->Format().BitDepth() == iBitDepth);
    TEST(aMsg->Format().SampleRate() == iSampleRate);
    iLastMsg = EMsgAudioFormat;
    return aMsg;
}

Msg* SuitePreDriver::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePreDriver::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePreDriver::ProcessMsg(MsgHalt* aMsg)
{
    iLastMsg = EMsgHalt;
    return aMsg;
}

Msg* SuitePreDriver::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePreDriver::ProcessMsg(MsgQuit* aMsg)
{
    iLastMsg = EMsgQuit;
    return aMsg;
}



void TestPreDriver()
{
    Runner runner("Pre-Driver tests\n");
    runner.Add(new SuitePreDriver());
    runner.Run();
}


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestPreDriver();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
