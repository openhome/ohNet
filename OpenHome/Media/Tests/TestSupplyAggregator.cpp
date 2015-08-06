#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/SupplyAggregator.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {
namespace TestSupplyAggregator {

class DummyStreamHandler : public IStreamHandler
{
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId) override;
};

class SuiteSupplyAggregator : public Suite, private IPipelineElementDownstream, private IMsgProcessor
{
    #define kUri "http://www.openhome.org/dir/file.ext"
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
    SuiteSupplyAggregator();
    ~SuiteSupplyAggregator();
    void Test();
private:
    void OutputNextNonAudioMsg();
private: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
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
        EMsgAudioEncoded
       ,EMsgTrack
       ,EMsgDrain
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgStreamInterrupted
       ,EMsgFlush
       ,EMsgWait
       ,EMsgNone
    };
private:
    MsgAudio* CreateAudio();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    SupplyAggregator* iSupply;
    DummyStreamHandler iDummyStreamHandler;
    EMsgType iLastMsg;
    EMsgType iGenMsgType;
    TUint iMsgPushCount;
    Bws<EncodedAudio::kMaxBytes> iAudio;
    TBool iExpectFullAudioMsg;
    TBool iExpectAudioStream;
    TBool iTestAudioData;
    TChar iLastAudioByte;
};

} // namespace TestSupplyAggregator
} // namespace Media
} // namespace OpenHome

using namespace OpenHome::Media::TestSupplyAggregator;


// DummyStreamHandler

EStreamPlay DummyStreamHandler::OkToPlay(TUint /*aStreamId*/)
{
    ASSERTS();
    return ePlayNo;
}

TUint DummyStreamHandler::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint DummyStreamHandler::TryStop(TUint /*aStreamId*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

void DummyStreamHandler::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/)
{
}


// SuiteSupplyAggregator

SuiteSupplyAggregator::SuiteSupplyAggregator()
    : Suite("Supply tests")
    , iLastMsg(EMsgNone)
    , iMsgPushCount(0)
{
    MsgFactoryInitParams init;
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iSupply = new SupplyAggregatorBytes(*iMsgFactory, *this);
}

SuiteSupplyAggregator::~SuiteSupplyAggregator()
{
    delete iSupply;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteSupplyAggregator::Test()
{
    // test msgs passed through
    TUint expectedMsgCount = 0;
    iGenMsgType = EMsgTrack;
    do {
        OutputNextNonAudioMsg();
        TEST(++expectedMsgCount == iMsgPushCount);
    } while (iGenMsgType != EMsgNone);

    // test data is buffered
    iExpectFullAudioMsg = true;
    iExpectAudioStream = false;
    iTestAudioData = true;
    do {
        iSupply->OutputData(Brn(kTestData));
    } while (expectedMsgCount == iMsgPushCount);
    TEST(++expectedMsgCount == iMsgPushCount);

    // any other msg flushes buffered data.  No duplicate/missing data in second msg
    iExpectFullAudioMsg = false;
    iExpectAudioStream = true;
    iSupply->OutputWait();
    TEST(iMsgPushCount == expectedMsgCount+2);
    expectedMsgCount = iMsgPushCount;

    // all other msgs flush buffered data
    iExpectAudioStream = false;
    iTestAudioData = false;
    iGenMsgType = EMsgTrack;
    do {
        iSupply->OutputData(Brn(kTestData));
        OutputNextNonAudioMsg();
        TEST(iMsgPushCount == expectedMsgCount+2);
        expectedMsgCount = iMsgPushCount;
    } while (iGenMsgType != EMsgNone);

    // buffered audio can be Flush()ed
    iSupply->OutputData(Brn(kTestData));
    TEST(iMsgPushCount == expectedMsgCount);
    iSupply->Flush();
    TEST(iMsgPushCount == ++expectedMsgCount);
    {
        AutoSupplyFlush _(*iSupply);
        iSupply->OutputData(Brn(kTestData));
        TEST(iMsgPushCount == expectedMsgCount);
    }
    TEST(iMsgPushCount == ++expectedMsgCount);
}

void SuiteSupplyAggregator::OutputNextNonAudioMsg()
{
    switch (iGenMsgType)
    {
    case EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brn(kUri), Brx::Empty());
        iSupply->OutputTrack(*track);
        track->RemoveRef();
    }
        break;
    case EMsgDrain:
        iSupply->OutputDrain(Functor());
        break;
    case EMsgDelay:
        iSupply->OutputDelay(kDelayJiffies);
        break;
    case EMsgEncodedStream:
        iSupply->OutputStream(Brn(kUri), kTotalBytes, kSeekable, kLive, iDummyStreamHandler, kStreamId);
        break;
    case EMsgMetaText:
        iSupply->OutputMetadata(Brn(kMetaData));
        break;
    case EMsgStreamInterrupted:
        iSupply->OutputStreamInterrupted();
        break;
    case EMsgFlush:
        iSupply->OutputFlush(1);
        break;
    case EMsgWait:
        iSupply->OutputWait();
        break;
    default:
        ASSERTS();
    }
    iGenMsgType = (EMsgType)((TUint)iGenMsgType + 1);
}

void SuiteSupplyAggregator::Push(Msg* aMsg)
{
    aMsg->Process(*this)->RemoveRef();
    iMsgPushCount++;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgMode* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    return aMsg;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgTrack* aMsg)
{
    iLastMsg = EMsgTrack;
    TEST(aMsg->Track().Uri() == Brn(kUri));
    return aMsg;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgDrain* aMsg)
{
    iLastMsg = EMsgDrain;
    return aMsg;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgDelay* aMsg)
{
    iLastMsg = EMsgDelay;
    TEST(aMsg->DelayJiffies() == kDelayJiffies);
    return aMsg;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgEncodedStream* aMsg)
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

Msg* SuiteSupplyAggregator::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iLastMsg = EMsgAudioEncoded;
    if (iExpectFullAudioMsg) {
        TEST(aMsg->Bytes() == EncodedAudio::kMaxBytes);
    }
    iAudio.SetBytes(aMsg->Bytes());
    aMsg->CopyTo(const_cast<TByte*>(iAudio.Ptr()));
    if (iExpectAudioStream) {
        // test first byte follows on from last msg
        if (iLastAudioByte < '9') {
            if (iAudio[0] != iLastAudioByte+1) {
                Print("Expected %u, got %u\n", iLastAudioByte+1, iAudio[0]);
            }
            TEST_QUIETLY(iAudio[0] == iLastAudioByte+1);
        }
        else {
            TEST_QUIETLY(iAudio[0] == '0');
        }
    }
    if (iTestAudioData) {
        TChar c = iAudio[0];
        for (TUint i=1; i<iAudio.Bytes(); i++) {
            if (c < '9') {
                TEST_QUIETLY(iAudio[i] == c+1);
            }
            else {
                TEST_QUIETLY(iAudio[i] == '0');
            }
            c = iAudio[i];
        }
    }
    iLastAudioByte = iAudio[iAudio.Bytes()-1];
    return aMsg;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgMetaText* aMsg)
{
    iLastMsg = EMsgMetaText;
    TEST(aMsg->MetaText() == Brn(kMetaData));
    return aMsg;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgHalt* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    return aMsg;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgFlush* aMsg)
{
    iLastMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgWait* aMsg)
{
    iLastMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgDecodedStream* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    return aMsg;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgAudioPcm* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    return aMsg;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgSilence* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    return aMsg;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgPlayable* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    return aMsg;
}

Msg* SuiteSupplyAggregator::ProcessMsg(MsgQuit* aMsg)
{
    ASSERTS(); // don't expect this type of msg at the start of the pipeline
    return aMsg;
}



void TestSupplyAggregator()
{
    Runner runner("Supply tests\n");
    runner.Add(new SuiteSupplyAggregator());
    runner.Run();
}
