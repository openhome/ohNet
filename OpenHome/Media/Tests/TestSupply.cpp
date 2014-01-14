#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Supply.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/InfoProvider.h>
#include "AllocatorInfoLogger.h"

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class DummyStreamHandler : public IStreamHandler
{
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
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
public:
    SuiteSupply();
    ~SuiteSupply();
    void Test();
private: // from IPipelineElementDownstream
    void Push(Msg* aMsg);
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


// SuiteSupply

SuiteSupply::SuiteSupply()
    : Suite("Supply tests")
    , iLastMsg(ENone)
    , iMsgPushCount(0)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
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
    Track* track = iTrackFactory->CreateTrack(Brn(kUri), Brx::Empty(), NULL, false);
    iSupply->OutputTrack(*track, kTrackId, Brx::Empty());
    track->RemoveRef();
    TEST(++expectedMsgCount == iMsgPushCount);
    iSupply->OutputStream(Brn(kUri), kTotalBytes, kSeekable, kLive, iDummyStreamHandler, kStreamId);
    TEST(++expectedMsgCount == iMsgPushCount);
    iSupply->OutputData(Brn(kTestData));
    TEST(++expectedMsgCount == iMsgPushCount);
    iSupply->OutputMetadata(Brn(kMetaData));
    TEST(++expectedMsgCount == iMsgPushCount);
    iSupply->OutputFlush(1);
    TEST(++expectedMsgCount == iMsgPushCount);
    iSupply->OutputHalt(MsgHalt::kIdNone + 1);
    TEST(++expectedMsgCount == iMsgPushCount);
    iSupply->OutputQuit();
    TEST(++expectedMsgCount == iMsgPushCount);
}

void SuiteSupply::Push(Msg* aMsg)
{
    aMsg->Process(*this)->RemoveRef();
    iMsgPushCount++;
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

Msg* SuiteSupply::ProcessMsg(MsgDecodedStream* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    iLastMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgTrack* aMsg)
{
    iLastMsg = EMsgTrack;
    TEST(aMsg->Track().Uri() == Brn(kUri));
    TEST(aMsg->IdPipeline() == kTrackId);
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

Msg* SuiteSupply::ProcessMsg(MsgMetaText* aMsg)
{
    iLastMsg = EMsgMetaText;
    TEST(aMsg->MetaText() == Brn(kMetaData));
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgHalt* aMsg)
{
    iLastMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgFlush* aMsg)
{
    iLastMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteSupply::ProcessMsg(MsgQuit* aMsg)
{
    iLastMsg = EMsgQuit;
    return aMsg;
}



void TestSupply()
{
    Runner runner("Supply tests\n");
    runner.Add(new SuiteSupply());
    runner.Run();
}
