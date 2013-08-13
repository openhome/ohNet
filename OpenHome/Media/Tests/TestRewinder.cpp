#include <OpenHome/Private/SuiteUnitTest.h>
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

class SuiteRewinder : public SuiteUnitTest, public IPipelineElementUpstream, private IStreamHandler, protected IMsgProcessor
{
public:
    static const TUint kPreAudioMsgCount = 2;
    static const TUint kEncodedAudioCount = 256;
    static const TUint kMsgAudioEncodedCount = 256;
public:
    SuiteRewinder(const TChar* aName);
    SuiteRewinder();
protected:
    void Init(TUint aEncodedAudioCount, TUint aMsgAudioEncodedCount, TUint aRewinderSlots);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
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
protected:
    enum EMsgType
    {
        ENone
        ,ENull
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
    void SetLastCount(TByte aCount);
    MsgAudioEncoded* CreateAudio();
    Msg* GenerateMsg(EMsgType aType);
    virtual Msg* GenerateNextMsg();
    void TestAllocatorExhaustion();
    void TestTryStop();
    void TestNoNulls();
    void TestTrySeekToStart();
    void TestTrySeekToStartAfterMiscAudio();
    void TestUpstreamRequestPassThrough();
    void TestMsgOrdering();
protected:
    AllocatorInfoLogger iInfoAggregator;
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    Rewinder* iRewinder;
    IStreamHandler* iStreamHandler;
    Msg* iLastMsg;
    EMsgType iLastMsgType;
    TByte iOut;
    TByte iIn;
    TUint iOkToPlayCount;
    TUint iTrySeekCount;
    TUint64 iLastSeekOffset;
    TUint iTryStopCount;
};

class SuiteRewinderMaxCapacity : public SuiteRewinder
{
public:
    SuiteRewinderMaxCapacity();
private: // from SuiteUnitTest
    void Setup();
private:
    void TestMaxCapacity();

};

} // namespace Media
} // namespace OpenHome


// SuiteRewinder

SuiteRewinder::SuiteRewinder(const TChar* aName)
    : SuiteUnitTest(aName)
{
}

SuiteRewinder::SuiteRewinder()
    : SuiteUnitTest("Rewinder tests")
{
    AddTest(MakeFunctor(*this, &SuiteRewinder::TestAllocatorExhaustion));
    AddTest(MakeFunctor(*this, &SuiteRewinder::TestTryStop));
    AddTest(MakeFunctor(*this, &SuiteRewinder::TestNoNulls));
    AddTest(MakeFunctor(*this, &SuiteRewinder::TestTrySeekToStart));
    AddTest(MakeFunctor(*this, &SuiteRewinder::TestTrySeekToStartAfterMiscAudio));
    AddTest(MakeFunctor(*this, &SuiteRewinder::TestUpstreamRequestPassThrough));
    AddTest(MakeFunctor(*this, &SuiteRewinder::TestMsgOrdering));
}

void SuiteRewinder::Init(TUint aEncodedAudioCount, TUint aMsgAudioEncodedCount, TUint aRewinderSlots)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, aEncodedAudioCount, aMsgAudioEncodedCount, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iRewinder = new Rewinder(*iMsgFactory, *this, aRewinderSlots);
    iStreamHandler = NULL;
    iLastMsgType = ENone;
    iOut = 0;
    iIn = 0;
    iOkToPlayCount = 0;
    iTrySeekCount = 0;
    iLastSeekOffset = 0;
    iTryStopCount = 0;
}

void SuiteRewinder::Setup()
{
    Init(kEncodedAudioCount, kMsgAudioEncodedCount, kMsgAudioEncodedCount);
}

void SuiteRewinder::TearDown()
{
    delete iRewinder;
    delete iTrackFactory;
    delete iMsgFactory;
}

Msg* SuiteRewinder::Pull()
{
    iLastMsg = GenerateNextMsg();
    return iLastMsg;
}

EStreamPlay SuiteRewinder::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    iOkToPlayCount++;
    return ePlayYes;
}

TUint SuiteRewinder::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 aOffset)
{
    iTrySeekCount++;
    iLastSeekOffset = aOffset;
    return 1;
}

TUint SuiteRewinder::TryStop(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    iTryStopCount++;
    return 1;
}

Msg* SuiteRewinder::ProcessMsg(MsgAudioEncoded* aMsg)
{
    TEST(iLastMsgType == EMsgAudioEncoded);
    TEST(aMsg->Bytes() == EncodedAudio::kMaxBytes);
    Bws<EncodedAudio::kMaxBytes> buf;
    aMsg->CopyTo(const_cast<TByte*>(buf.Ptr()));
    buf.SetBytes(aMsg->Bytes());
    ASSERT(buf[0] == iIn);
    ASSERT(buf[buf.Bytes()-1] == iIn);
    iIn++;
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
    TEST(iLastMsgType == EMsgTrack);
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgEncodedStream* aMsg)
{
    TEST(iLastMsgType == EMsgEncodedStream);
    iStreamHandler = aMsg->StreamHandler();
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgMetaText* aMsg)
{
    TEST(iLastMsgType == EMsgMetaText);
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgHalt* aMsg)
{
    TEST(iLastMsgType == EMsgHalt);
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgFlush* aMsg)
{
    TEST(iLastMsgType == EMsgFlush);
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgQuit* aMsg)
{
    TEST(iLastMsgType == EMsgQuit);
    return aMsg;
}

MsgAudioEncoded* SuiteRewinder::CreateAudio()
{
    // create a MsgAudioEncoded filled with iOut;
    // iOut is incremented after each call
    static const TUint kDataBytes = EncodedAudio::kMaxBytes;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, iOut, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioEncoded* audio = iMsgFactory->CreateMsgAudioEncoded(encodedAudioBuf);
    iOut++;
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
    case ENull:
        return NULL;
    case EMsgTrack:
        {
        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty(), NULL);
        msg = iMsgFactory->CreateMsgTrack(*track, 0, Brx::Empty());
        track->RemoveRef();
        }
        iLastMsgType = EMsgTrack;
        break;
    case EMsgEncodedStream:
        msg = iMsgFactory->CreateMsgEncodedStream(Brn("http://127.0.0.1:65535"), Brn("metatext"), 0, 0, false, false, this);
        iLastMsgType = EMsgEncodedStream;
        break;
    case EMsgAudioEncoded:
        msg = CreateAudio();
        iLastMsgType = EMsgAudioEncoded;
        break;
    case EMsgMetaText:
        msg = iMsgFactory->CreateMsgMetaText(Brn("metatext"));
        iLastMsgType = EMsgMetaText;
        break;
    case EMsgHalt:
        msg = iMsgFactory->CreateMsgHalt();
        iLastMsgType = EMsgHalt;
        break;
    case EMsgFlush:
        msg = iMsgFactory->CreateMsgFlush(1);
        iLastMsgType = EMsgFlush;
        break;
    case EMsgQuit:
        msg = iMsgFactory->CreateMsgQuit();
        iLastMsgType = EMsgQuit;
        break;
    }
    return msg;
}

Msg* SuiteRewinder::GenerateNextMsg()
{
    // generate 1 track -> 1 stream -> >0 audio encoded msgs to simulate normal operation
    Msg* msg = NULL;
    switch (iLastMsgType)
    {
    default:
    case EMsgPlayable:
    case EMsgAudioPcm:
    case EMsgSilence:
        ASSERTS();
        break;
    case ENone:
        msg = GenerateMsg(EMsgTrack);
        break;
    case EMsgTrack:
        msg = GenerateMsg(EMsgEncodedStream);
        break;
    case EMsgEncodedStream:
    case EMsgAudioEncoded:
        msg = GenerateMsg(EMsgAudioEncoded);
        break;
    }
    return msg;
}

void SuiteRewinder::TestAllocatorExhaustion()
{
    // test that pulling kMsgAudioEncodedCount+1 into Rewinder causes AllocatorNoMemory to be thrown
    for (TUint i = 0; i < kPreAudioMsgCount+kMsgAudioEncodedCount; i++)
    {
        Msg* msg = iRewinder->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
    }
    TEST_THROWS(iRewinder->Pull(), AllocatorNoMemory);
}

void SuiteRewinder::TestTryStop()
{
    // test that normal sequence can be pulled, then TryStop to tell Rewinder
    // to stop buffering, and that subsequent messages are ordered correctly
    // (and that Rewinder can no longer be exhausted, as it's no longer buffering)
    static const TUint kPreTryStopAudioCount = 5;
    static const TUint kPostTryStopAudioCount = kMsgAudioEncodedCount;   // any value >Rewinder slots
    for (TUint i = 0; i < kPreAudioMsgCount+kPreTryStopAudioCount; i++)
    {
        Msg* msg = iRewinder->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
    }
    iStreamHandler->TryStop(0, 0);
    TEST(iTryStopCount == 0); // no TryStop msg should have been passed up
    for (TUint i = 0; i < kPostTryStopAudioCount; i++)
    {
        Msg* msg = iRewinder->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
    }
    // if executions gets to here, no longer buffering
}

void SuiteRewinder::TestNoNulls()
{
    // test that, under normal conditions, if a NULL msg is passed down the
    // pipeline, the Rewinder only ever returns non-NULL msgs
}

void SuiteRewinder::TestTrySeekToStart()
{
    // test that buffering, then seeking back to the start works correctly
    static const TUint kPreTryStopAudioCount = 5;
    static const TUint kPostTryStopAudioCount = kPreTryStopAudioCount+5;
    for (TUint i = 0; i < kPreAudioMsgCount+kPreTryStopAudioCount; i++)
    {
        Msg* msg = iRewinder->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
    }
    // try seeking back to start
    iStreamHandler->TrySeek(0, 0, 0);
    iIn = 0;
    for (TUint i = 0; i < kPostTryStopAudioCount; i++)
    {
        Msg* msg = iRewinder->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
    }
    // try seeking again
    iStreamHandler->TrySeek(0, 0, 0);
    iIn = 0;
    for (TUint i = 0; i < kPostTryStopAudioCount; i++)
    {
        Msg* msg = iRewinder->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
    }
}

void SuiteRewinder::TestTrySeekToStartAfterMiscAudio()
{
    // test that after receiving X msgs of MsgAudioEncoded, then a
    // MsgEncodedStream followed by a TrySeek, only MsgAudioEncodeds received
    // after the MsgEncodedStream are passed through
}

void SuiteRewinder::TestUpstreamRequestPassThrough()
{
    // test that upstream msgs are successfully (and correctly) passed through
    // to the IStreamHandler
    static const TUint kAudioCount = 5;
    static const TUint kNonZeroSeekOffset = 10;

    TUint seekRes = 0;
    TUint expectedSeekCount = 0;
    EStreamPlay playRes = ePlayNo;
    TUint expectedOkToPlayCount = 1;
    TUint stopRes = 0;

    TEST(iStreamHandler == NULL);
    for (TUint i = 0; i < kPreAudioMsgCount+kAudioCount; i++)
    {
        Msg* msg = iRewinder->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
    }
    // TrySeek shouldn't be passed through while buffering
    seekRes = iStreamHandler->TrySeek(0,0,0);
    TEST(seekRes == 0);
    TEST(iTrySeekCount == expectedSeekCount++);
    TEST(iLastSeekOffset == 0);
    // test seeking anywhere other than start during buffering causes assert
    TEST_THROWS(iStreamHandler->TrySeek(0,0,1), AssertionFailed);
    // OkToPlay should always be passed through
    playRes = iStreamHandler->OkToPlay(0,0);
    TEST(playRes == ePlayYes);
    TEST(iOkToPlayCount == expectedOkToPlayCount++);

    // now call a TryStop and repeat calls - ALL calls should be passed through afterwards
    stopRes = iStreamHandler->TryStop(0,0);
    TEST(stopRes == 0);
    TEST(iTryStopCount == 0);   // first TryStop shouldn't be passed through
    // TrySeek to 0
    seekRes = iStreamHandler->TrySeek(0,0,0);
    TEST(seekRes == 1);
    TEST(iTrySeekCount == expectedSeekCount++);
    TEST(iLastSeekOffset == 0);
    // TrySeek to 10
    seekRes = iStreamHandler->TrySeek(0,0,kNonZeroSeekOffset);
    TEST(seekRes == 1);
    TEST(iTrySeekCount == expectedSeekCount++);
    TEST(iLastSeekOffset == kNonZeroSeekOffset);
    // OkToPlay
    playRes = iStreamHandler->OkToPlay(0,0);
    TEST(playRes == ePlayYes);
    TEST(iOkToPlayCount == expectedOkToPlayCount++);
    // TryStop again - should be passed through this time
    stopRes = iStreamHandler->TryStop(0,0);
    TEST(stopRes == 1);
    TEST(iTryStopCount == 1);
}

void SuiteRewinder::TestMsgOrdering()
{
    // test that Rewinder passes through ALL msgs in order (even buffered ones)
}


// SuiteRewinderMaxCapacity

SuiteRewinderMaxCapacity::SuiteRewinderMaxCapacity()
    : SuiteRewinder("RewinderMaxCapacity tests")
{
    AddTest(MakeFunctor(*this, &SuiteRewinderMaxCapacity::TestMaxCapacity));
}

void SuiteRewinderMaxCapacity::Setup()
{
    Init(kEncodedAudioCount, kMsgAudioEncodedCount, kMsgAudioEncodedCount-1);
}

void SuiteRewinderMaxCapacity::TestMaxCapacity()
{
    // test that pulling kMsgAudioEncodedCount into a Rewinder with
    // kMsgAudioEncodedCount-1 slots causes assertion
    Msg* msg = NULL;
    for (TUint i = 0; i < kPreAudioMsgCount+(kMsgAudioEncodedCount-1); i++)
    {
        msg = iRewinder->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
    }
    // pulling msg #kMsgAudioEncodedCount
    TEST_THROWS(msg = iRewinder->Pull(), AssertionFailed);
    iLastMsg->RemoveRef();
}

void TestRewinder()
{
    Runner runner("Rewinder tests\n");
    runner.Add(new SuiteRewinder());
    runner.Add(new SuiteRewinderMaxCapacity());
    runner.Run();
}
