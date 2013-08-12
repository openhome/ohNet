#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Rewinder.h>
#include <OpenHome/Media/Msg.h>
#include "AllocatorInfoLogger.h"

#include <string.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteRewinder : public Suite, public IPipelineElementUpstream, private IStreamHandler, private IMsgProcessor
{
public:
    static const TUint kEncodedAudioCount = 512;
    static const TUint kMsgAudioEncodedCount = 512;
public:
    SuiteRewinder();
    ~SuiteRewinder();
public: // from Suite
    void Test();
public: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
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
    enum EMsgType
    {
        ENone
        ,EMsgAudioEncoded
        ,EMsgAudioPcm
        ,EMsgSilence
        ,EMsgPlayable
        ,EMsgDecodedStream
        ,EMsgTrack
        ,EMsgEncodedStream
        ,EMsgMetaText
        ,EMsgHalt
        ,EMsgFlush
        ,EMsgQuit
    };
private:
    TByte LastCount();
    MsgAudioEncoded* CreateAudio();
    Msg* GenerateMsg(EMsgType aType);
    Msg* GenerateNextMsg();
private:
    AllocatorInfoLogger iInfoAggregator;
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    Rewinder* iRewinder;
    EMsgType iLastMsg;
    TByte iCount;
};

} // namespace Media
} // namespace OpenHome


// SuiteRewinder

SuiteRewinder::SuiteRewinder()
    : Suite("Rewinder tests")
    , iLastMsg(ENone)
    , iCount(0)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, kEncodedAudioCount, kMsgAudioEncodedCount, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iRewinder = new Rewinder(*iMsgFactory, *this, kMsgAudioEncodedCount);
}

SuiteRewinder::~SuiteRewinder()
{
    delete iRewinder;
    delete iTrackFactory;
    delete iMsgFactory;
}

void SuiteRewinder::Test()
{
    // test that pulling kMsgAudioEncodedCount+1 into Rewinder causes AllocatorNoMemory to be thrown
    for (TUint i = 0; i < 2+kMsgAudioEncodedCount; i++)
    {
        Msg* msg = iRewinder->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
    }
    TEST_THROWS(iRewinder->Pull(), AllocatorNoMemory);
}

Msg* SuiteRewinder::Pull()
{
    return GenerateNextMsg();
}

EStreamPlay SuiteRewinder::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    return ePlayYes;
}

TUint SuiteRewinder::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    return false;
}

TUint SuiteRewinder::TryStop(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    return false;
}

Msg* SuiteRewinder::ProcessMsg(MsgAudioEncoded* aMsg)
{
    TEST(iLastMsg == EMsgAudioEncoded);
    TEST(aMsg->Bytes() == EncodedAudio::kMaxBytes);
    Bws<EncodedAudio::kMaxBytes> buf;
    aMsg->CopyTo(const_cast<TByte*>(buf.Ptr()));
    buf.SetBytes(aMsg->Bytes());
    ASSERT(buf[0] == LastCount());
    ASSERT(buf[buf.Bytes()-1] == LastCount());
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return NULL;
}

Msg* SuiteRewinder::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return NULL;
}

Msg* SuiteRewinder::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return NULL;
}

Msg* SuiteRewinder::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return NULL;
}

Msg* SuiteRewinder::ProcessMsg(MsgTrack* aMsg)
{
    TEST(iLastMsg == EMsgTrack);
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgEncodedStream* aMsg)
{
    TEST(iLastMsg == EMsgEncodedStream);
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgMetaText* aMsg)
{
    TEST(iLastMsg == EMsgMetaText);
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgHalt* aMsg)
{
    TEST(iLastMsg == EMsgHalt);
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgFlush* aMsg)
{
    TEST(iLastMsg == EMsgFlush);
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgQuit* aMsg)
{
    TEST(iLastMsg == EMsgQuit);
    return aMsg;
}

TByte SuiteRewinder::LastCount()
{
    return iCount-1;
}

MsgAudioEncoded* SuiteRewinder::CreateAudio()
{
    // create a MsgAudioEncoded filled with iCount;
    // iCount is incremented after each call
    static const TUint kDataBytes = EncodedAudio::kMaxBytes;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, iCount, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioEncoded* audio = iMsgFactory->CreateMsgAudioEncoded(encodedAudioBuf);
    iCount++;
    return audio;
}

Msg* SuiteRewinder::GenerateMsg(EMsgType aType)
{
    Msg* msg = NULL;
    switch (aType)
    {
    default:
    case ENone:
    case EMsgPlayable:
    case EMsgAudioPcm:
    case EMsgSilence:
    case EMsgDecodedStream:
        ASSERTS();
        break;
    case EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty(), NULL);
        msg = iMsgFactory->CreateMsgTrack(*track, 0, Brx::Empty());
        track->RemoveRef();
    }
        break;
    case EMsgEncodedStream:
        msg = iMsgFactory->CreateMsgEncodedStream(Brn("http://127.0.0.1:65535"), Brn("metatext"), 0, 0, false, false, NULL);
        break;
    case EMsgAudioEncoded:
        msg = CreateAudio();
        break;
    case EMsgMetaText:
        msg = iMsgFactory->CreateMsgMetaText(Brn("metatext"));
        break;
    case EMsgHalt:
        msg = iMsgFactory->CreateMsgHalt();
        break;
    case EMsgFlush:
        msg = iMsgFactory->CreateMsgFlush(1);
        break;
    case EMsgQuit:
        msg = iMsgFactory->CreateMsgQuit();
        break;
    }
    return msg;
}

Msg* SuiteRewinder::GenerateNextMsg()
{
    // generate 1 track -> 1 stream -> >0 audio encoded msgs to simulate normal operation
    Msg* msg = NULL;
    switch (iLastMsg)
    {
    default:
    case EMsgPlayable:
    case EMsgAudioPcm:
    case EMsgSilence:
        ASSERTS();
        break;
    case ENone:
        iLastMsg = EMsgTrack;
        msg = GenerateMsg(iLastMsg);
        break;
    case EMsgTrack:
        iLastMsg = EMsgEncodedStream;
        msg = GenerateMsg(iLastMsg);
        break;
    case EMsgEncodedStream:
    case EMsgAudioEncoded:
        iLastMsg = EMsgAudioEncoded;
        msg = GenerateMsg(iLastMsg);
        break;
    }
    return msg;
}

void TestRewinder()
{
    Runner runner("Rewinder tests\n");
    runner.Add(new SuiteRewinder());
    runner.Run();
}
