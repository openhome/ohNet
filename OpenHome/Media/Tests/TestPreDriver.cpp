#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Pipeline/PreDriver.h>
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

class SuitePreDriver : public Suite, private IPipelineElementUpstream, private IMsgProcessor
{
    static const TUint kMsgFormatCount = 2;

    static const TUint kSampleRate  = 44100;
public:
    SuitePreDriver();
    ~SuitePreDriver();
    void Test();
private: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
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
    MsgAudioPcm* CreateAudio();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    PreDriver* iPreDriver;
    EMsgType iNextGeneratedMsg;
    EMsgType iLastMsg;
    TUint64 iTrackOffset;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iNumChannels;
    TUint iAudioMsgSizeJiffies;
    TUint iNextMsgSilenceSize;
};

} // namespace Media
} // namespace OpenHome


// SuitePreDriver

SuitePreDriver::SuitePreDriver()
    : Suite("Pre-Driver tests")
    , iLastMsg(ENone)
    , iTrackOffset(0)
    , iNumChannels(2)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 10, 10, 10, 10, 10, kMsgFormatCount, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    MsgAudioPcm* audio = CreateAudio();
    iAudioMsgSizeJiffies = audio->Jiffies();
    audio->RemoveRef();
    iNextMsgSilenceSize = iAudioMsgSizeJiffies;
    iPreDriver = new PreDriver(*this);
}

SuitePreDriver::~SuitePreDriver()
{
    delete iPreDriver;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuitePreDriver::Test()
{
    iSampleRate = 44100;
    iBitDepth = 16;

    // Send Format msg; check it is passed on.
    iNextGeneratedMsg = EMsgDecodedStream;
    Msg* msg = iPreDriver->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
    TEST(iLastMsg == EMsgDecodedStream);

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

    // Send Mode; check it is passed on.
    iNextGeneratedMsg = EMsgMode;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgMode);

    // Send Track; check it isn't passed on.
    iNextGeneratedMsg = EMsgTrack;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgPlayable);

    // Send Format with same sample rate + bit depth + no. channels.  Check it isn't passed on (we move on to Silence instead).
    iNextGeneratedMsg = EMsgDecodedStream;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgPlayable);

    // Send Halt; check it is passed on.
    iNextGeneratedMsg = EMsgHalt;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgHalt);

    // Send Audio then Format with different sample rate.
    iNextGeneratedMsg = EMsgAudioPcm;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgPlayable);
    iSampleRate = 48000;
    iNextGeneratedMsg = EMsgDecodedStream;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgDecodedStream);
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
        return iMsgFactory->CreateMsgSilence(iNextMsgSilenceSize);
    case EMsgDecodedStream:
        iNextGeneratedMsg = EMsgSilence;
        return iMsgFactory->CreateMsgDecodedStream(0, 128000, iBitDepth, iSampleRate, iNumChannels, Brn("dummy codec"), (TUint64)1<<31, 0, false, false, false, NULL);
    case EMsgMode:
        iNextGeneratedMsg = EMsgTrack;
        return iMsgFactory->CreateMsgMode(Brn("dummyMode"), true, false, NULL);
    case EMsgTrack:
    {
        iNextGeneratedMsg = EMsgAudioPcm; // msg will be discarded by PreDriver which will immediately Pull again.
                                          // Ensure we have something different to deliver to avoid an infinite loop.
        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
        Msg* msg = iMsgFactory->CreateMsgTrack(*track);
        track->RemoveRef();
        return msg;
    }
    case EMsgEncodedStream:
        iNextGeneratedMsg = EMsgAudioPcm;
        return iMsgFactory->CreateMsgEncodedStream(Brn("http://1.2.3.4:5"), Brn("metatext"), 0, 0, false, false, NULL);
    case EMsgMetaText:
        iNextGeneratedMsg = EMsgAudioPcm;
        return iMsgFactory->CreateMsgMetaText(Brn("metatext"));
    case EMsgHalt:
        return iMsgFactory->CreateMsgHalt();
    case EMsgFlush:
        return iMsgFactory->CreateMsgFlush(1);
    case EMsgWait:
        return iMsgFactory->CreateMsgWait();
    case EMsgQuit:
        return iMsgFactory->CreateMsgQuit();
    }
}

MsgAudioPcm* SuitePreDriver::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0xff, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, iNumChannels, kSampleRate, 16, EMediaDataEndianLittle, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

Msg* SuitePreDriver::ProcessMsg(MsgMode* aMsg)
{
    iLastMsg = EMsgMode;
    return aMsg;
}

Msg* SuitePreDriver::ProcessMsg(MsgSession* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePreDriver::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePreDriver::ProcessMsg(MsgDelay* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePreDriver::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePreDriver::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
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

Msg* SuitePreDriver::ProcessMsg(MsgWait* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePreDriver::ProcessMsg(MsgDecodedStream* aMsg)
{
    TEST(aMsg->StreamInfo().BitDepth() == iBitDepth);
    TEST(aMsg->StreamInfo().SampleRate() == iSampleRate);
    TEST(aMsg->StreamInfo().NumChannels() == iNumChannels);
    iLastMsg = EMsgDecodedStream;
    return aMsg;
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
