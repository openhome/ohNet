#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/PreDriver.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/InfoProvider.h>
#include "AllocatorInfoLogger.h"
#include <OpenHome/Media/ProcessorPcmUtils.h>

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
    Msg* Pull();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg);
    Msg* ProcessMsg(MsgSession* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgDelay* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgWait* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
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
    iPreDriver = new PreDriver(*iMsgFactory, *this, iAudioMsgSizeJiffies);
}

SuitePreDriver::~SuitePreDriver()
{
    delete iPreDriver;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuitePreDriver::Test()
{
    /*
    Test goes something like
        Send Format msg; check it is passed on.
        Send Audio; check it is passed on.
        Send Silence; check it is passed on.
        Send Quit; check it is passed on.
        Send Track, AudioStream, MetaText; check neither are passed on.
        Send Format with same sample rate + bit depth.  Check it isn't passed on (we move on to Silence instead).
        Send Halt; check it is passed on.
        Send Audio then Format with different sample rate.  Check Halt is delivered before Format.
        Send Audio then Format with different bit depth.  Check Halt is delivered before Format.
    */

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

    // Send Audio then Format with different sample rate.  Check Halt is delivered before Format.
    iNextGeneratedMsg = EMsgAudioPcm;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgPlayable);
    iSampleRate = 48000;
    iNextGeneratedMsg = EMsgDecodedStream;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgHalt);
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgDecodedStream);

    // Send Audio then Format with different bit depth.  Check Halt is delivered before Format.
    iNextGeneratedMsg = EMsgAudioPcm;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgPlayable);
    iBitDepth = 24;
    iNextGeneratedMsg = EMsgDecodedStream;
    do {
        iPreDriver->Pull()->Process(*this)->RemoveRef();
    } while (iLastMsg != EMsgHalt);
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgDecodedStream);

    // Send Format with same sample rate + bit depth but different no. channels.
    iNumChannels = 1;
    iNextGeneratedMsg = EMsgDecodedStream;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgDecodedStream);

    // Send Audio then Format with same sample rate + bit depth but different no. channels.
    // Check Halt is delivered before Format.
    iNextGeneratedMsg = EMsgAudioPcm;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgPlayable);
    iNumChannels = 2;
    iNextGeneratedMsg = EMsgDecodedStream;
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgPlayable);
    iPreDriver->Pull()->Process(*this)->RemoveRef();
    TEST(iLastMsg == EMsgHalt);
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
    case EMsgTrack:
    {
        iNextGeneratedMsg = EMsgAudioPcm; // msg will be discarded by PreDriver which will immediately Pull again.
                                          // Ensure we have something different to deliver to avoid an infinite loop.
        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
        Msg* msg = iMsgFactory->CreateMsgTrack(*track, 0);
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
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, iNumChannels, kSampleRate, 16, EMediaDataLittleEndian, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

Msg* SuitePreDriver::ProcessMsg(MsgMode* /*aMsg*/)
{
    ASSERTS();
    return NULL;
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


