#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Supply.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class DummyStreamHandler : public IStreamHandler
{
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId) override;
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aTrackId, TUint aStreamId) override;
    TBool TryGet(IWriter& aWriter, TUint aTrackId, TUint aStreamId, TUint64 aOffset, TUint aBytes) override;
    void NotifyStarving(const Brx& aMode, TUint aTrackId, TUint aStreamId) override;
};

class SuiteSupply : public Suite, private IPipelineElementDownstream, private IMsgProcessor
{
    #define kUri "http://www.openhome.org/dir/file.ext"
    static const TUint kTrackId    = 1;
    static const TUint kTotalBytes = 32000000;
    static const TBool kSeekable   = true;
    static const TBool kLive       = false;
    static const TUint kStreamId   = 3;
    #define kTestData "0123456789012345678901234567890123456789"
    #define kMetaData "Wee bit of meta data"
    #define kMode "TestMode"
    static const TBool kSupportsLatency = true;
    static const TBool kIsRealTime = true;
    static const TUint kDelayJiffies = 12345;
public:
    SuiteSupply();
    ~SuiteSupply();
    void Test() override;
private: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
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
       ,EMsgAudioEncoded
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgDecodedStream
       ,EMsgMode
       ,EMsgSession
       ,EMsgTrack
       ,EMsgDelay
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
    Supply* iSupply;
    DummyStreamHandler iDummyStreamHandler;
    EMsgType iLastMsg;
    TUint iMsgPushCount;
};

} // namespace Media
} // namespace OpenHome


// DummyStreamHandler

EStreamPlay DummyStreamHandler::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS();
    return ePlayNo;
}

TUint DummyStreamHandler::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint DummyStreamHandler::TryStop(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TBool DummyStreamHandler::TryGet(IWriter& /*aWriter*/, TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    ASSERTS();
    return false;
}

void DummyStreamHandler::NotifyStarving(const Brx& /*aMode*/, TUint /*aTrackId*/, TUint /*aStreamId*/)
{
}


// SuiteSupply

SuiteSupply::SuiteSupply()
    : Suite("Supply tests")
    , iLastMsg(ENone)
    , iMsgPushCount(0)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iSupply = new Supply(*iMsgFactory, *this);
}

SuiteSupply::~SuiteSupply()
{
    delete iSupply;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteSupply::Test()
{
    TUint expectedMsgCount = 0;
    iSupply->OutputSession();
    TEST(++expectedMsgCount == iMsgPushCount);
    Track* track = iTrackFactory->CreateTrack(Brn(kUri), Brx::Empty());
    iSupply->OutputTrack(*track, kTrackId);
    track->RemoveRef();
    TEST(++expectedMsgCount == iMsgPushCount);
    iSupply->OutputDelay(kDelayJiffies);
    TEST(++expectedMsgCount == iMsgPushCount);
    iSupply->OutputStream(Brn(kUri), kTotalBytes, kSeekable, kLive, iDummyStreamHandler, kStreamId);
    TEST(++expectedMsgCount == iMsgPushCount);
    iSupply->OutputData(Brn(kTestData));
    TEST(++expectedMsgCount == iMsgPushCount);
    iSupply->OutputMetadata(Brn(kMetaData));
    TEST(++expectedMsgCount == iMsgPushCount);
    iSupply->OutputFlush(1);
    TEST(++expectedMsgCount == iMsgPushCount);
    iSupply->OutputWait();
    TEST(++expectedMsgCount == iMsgPushCount);
}

void SuiteSupply::Push(Msg* aMsg)
{
    aMsg->Process(*this)->RemoveRef();
    iMsgPushCount++;
}

Msg* SuiteSupply::ProcessMsg(MsgMode* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    iLastMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgSession* aMsg)
{
    iLastMsg = EMsgSession;
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgTrack* aMsg)
{
    iLastMsg = EMsgTrack;
    TEST(aMsg->Track().Uri() == Brn(kUri));
    TEST(aMsg->IdPipeline() == kTrackId);
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgDelay* aMsg)
{
    iLastMsg = EMsgDelay;
    TEST(aMsg->DelayJiffies() == kDelayJiffies);
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastMsg = EMsgEncodedStream;
    TEST(aMsg->Uri()           == Brn(kUri));
    TEST(aMsg->MetaText()      == Brx::Empty()); // FIXME - should either make it possible to set stream metadata or remove it
    TEST(aMsg->TotalBytes()    == kTotalBytes);
    TEST(aMsg->StreamId()      == kStreamId);
    TEST(aMsg->Seekable()      == kSeekable);
    TEST(aMsg->Live()          == kLive);
    TEST(aMsg->StreamHandler() == &iDummyStreamHandler);

    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iLastMsg = EMsgAudioEncoded;
    TEST(aMsg->Bytes() == sizeof(kTestData)-1);
    TByte audioEnc[64];
    aMsg->CopyTo(audioEnc);
    TEST(memcmp(kTestData, audioEnc, sizeof(kTestData)-1) == 0);
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgMetaText* aMsg)
{
    iLastMsg = EMsgMetaText;
    TEST(aMsg->MetaText() == Brn(kMetaData));
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgHalt* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    iLastMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgFlush* aMsg)
{
    iLastMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgWait* aMsg)
{
    iLastMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgDecodedStream* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    iLastMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgAudioPcm* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    iLastMsg = EMsgAudioPcm;
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgSilence* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    iLastMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgPlayable* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    iLastMsg = EMsgPlayable;
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgQuit* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    iLastMsg = EMsgQuit;
    return aMsg;
}



void TestSupply()
{
    Runner runner("Supply tests\n");
    runner.Add(new SuiteSupply());
    runner.Run();
}
