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

class SuiteRewinder : public SuiteUnitTest, public IPipelineElementUpstream, public IFlushIdProvider, private IStreamHandler, protected IMsgProcessor
{
public:
    static const TUint kPreAudioMsgCount = 2;
    static const TUint kEncodedAudioCount = 256;
    static const TUint kMsgAudioEncodedCount = 256;
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
public:
    SuiteRewinder(const TChar* aName);
    SuiteRewinder();
protected:
    virtual void InitMsgOrder();
    void Init(TUint aEncodedAudioCount, TUint aMsgAudioEncodedCount, TUint aRewinderSlots);
    TBool TestMsgAudioEncodedValue(MsgAudioEncoded& aMsg, TByte aValue);
    Msg* GenerateNextMsg();
    void PullAndProcess();
    void PullFlush();
private:
    TByte LastCount();
    void SetLastCount(TByte aCount);
    MsgAudioEncoded* CreateAudio();
    Msg* GenerateMsg(EMsgType aType);
    void TestAllocatorExhaustion();
    void TestTryStop();
    void TestTrySeekToStart();
    void TestUpstreamRequestPassThrough();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
public: // from IPipelineElementUpstream
    Msg* Pull();
public: // from IFlushIdProvider
    TUint NextFlushId();
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
    AllocatorInfoLogger iInfoAggregator;
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    Rewinder* iRewinder;
    IStreamHandler* iStreamHandler;
    TUint iNextFlushId;
    std::vector<EMsgType> iMsgOrder;
    TUint iMsgCount;
    Msg* iLastMsg;
    EMsgType iLastMsgType;
    EMsgType iRcvdMsgType;
    TByte iAudioOut;
    TByte iAudioIn;
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

class SuiteRewinderNullMsgs : public SuiteRewinder
{
public:
    SuiteRewinderNullMsgs();
private: // from SuiteUnitTest
    void Setup();
private: // from SuiteRewinder
    void InitMsgOrder();
private:
    void TestNoNulls();
private:
    TByte iAudioEncodedCount;
};

class SuiteRewinderSeekToStartAfterMiscAudio : public SuiteRewinder
{
public:
    SuiteRewinderSeekToStartAfterMiscAudio();
    SuiteRewinderSeekToStartAfterMiscAudio(const TChar* aName);
private: // from SuiteRewinder
    void InitMsgOrder();
private:
    void TestTrySeekToStartAfterMiscAudio();
protected:
    static const TUint kStartOfNewStream = 10;
};

class SuiteRewinderSeekToStartMultipleStreams : public SuiteRewinderSeekToStartAfterMiscAudio
{
public:
    SuiteRewinderSeekToStartMultipleStreams();
private: // from SuiteRewinder
    void InitMsgOrder();
};

class SuiteRewinderMsgOrdering: public SuiteRewinder
{
public:
    SuiteRewinderMsgOrdering();
private: // from SuiteRewinder
    void InitMsgOrder();
private:
    void TestMsgOrdering();
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
    AddTest(MakeFunctor(*this, &SuiteRewinder::TestTrySeekToStart));
    AddTest(MakeFunctor(*this, &SuiteRewinder::TestUpstreamRequestPassThrough));
}

void SuiteRewinder::InitMsgOrder()
{
    // generate 1 track -> 1 stream -> >0 audio encoded msgs to simulate normal operation
    iMsgOrder.push_back(EMsgTrack);
    iMsgOrder.push_back(EMsgEncodedStream);
    // make sure there are more than enough MsgAudioEncodeds for our needs
    for (TUint i=0; i<kMsgAudioEncodedCount*2; i++){
        iMsgOrder.push_back(EMsgAudioEncoded);
    }
}

void SuiteRewinder::Init(TUint aEncodedAudioCount, TUint aMsgAudioEncodedCount, TUint aRewinderSlots)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, aEncodedAudioCount, aMsgAudioEncodedCount, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iRewinder = new Rewinder(*iMsgFactory, *this, *this, aRewinderSlots);
    iStreamHandler = NULL;
    iNextFlushId = MsgFlush::kIdInvalid+1;
    iMsgOrder.clear();
    iMsgCount = 0;
    iLastMsgType = ENone;
    iRcvdMsgType = ENone;
    iAudioOut = 0;
    iAudioIn = 0;
    iOkToPlayCount = 0;
    iTrySeekCount = 0;
    iLastSeekOffset = 0;
    iTryStopCount = 0;
    InitMsgOrder();
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

TUint SuiteRewinder::NextFlushId()
{
    return iNextFlushId++;
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
    TBool isCorrectMsg = TestMsgAudioEncodedValue(*aMsg, iAudioIn);
    TEST(isCorrectMsg == true);
    iAudioIn++;
    iRcvdMsgType = EMsgAudioEncoded;
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
    iRcvdMsgType = EMsgTrack;
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgEncodedStream* aMsg)
{
    TEST(iLastMsgType == EMsgEncodedStream);
    iStreamHandler = aMsg->StreamHandler();
    iRcvdMsgType = EMsgEncodedStream;
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgMetaText* aMsg)
{
    TEST(iLastMsgType == EMsgMetaText);
    iRcvdMsgType = EMsgMetaText;
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgHalt* aMsg)
{
    TEST(iLastMsgType == EMsgHalt);
    iRcvdMsgType = EMsgHalt;
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgFlush* aMsg)
{
    TEST(iLastMsgType == EMsgFlush);
    iRcvdMsgType = EMsgFlush;
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgQuit* aMsg)
{
    TEST(iLastMsgType == EMsgQuit);
    iRcvdMsgType = EMsgQuit;
    return aMsg;
}

TBool SuiteRewinder::TestMsgAudioEncodedValue(MsgAudioEncoded& aMsg, TByte aValue)
{
    if ((iLastMsgType != EMsgAudioEncoded) || (aMsg.Bytes() != EncodedAudio::kMaxBytes))
    {
        return false;
    }
    Bws<EncodedAudio::kMaxBytes> buf;
    aMsg.CopyTo(const_cast<TByte*>(buf.Ptr()));
    buf.SetBytes(aMsg.Bytes());
    if ((buf[0] != aValue) || (buf[buf.Bytes()-1] != aValue)) {
        return false;
    }
    return true;
}

MsgAudioEncoded* SuiteRewinder::CreateAudio()
{
    // create a MsgAudioEncoded filled with iAudioOut;
    // iAudioOut is incremented after each call
    static const TUint kDataBytes = EncodedAudio::kMaxBytes;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, iAudioOut, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioEncoded* audio = iMsgFactory->CreateMsgAudioEncoded(encodedAudioBuf);
    iAudioOut++;
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
        msg = iMsgFactory->CreateMsgFlush(NextFlushId());
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
    Msg* msg = NULL;
    ASSERT(iMsgCount < iMsgOrder.size());
    switch (iMsgOrder[iMsgCount++])
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
        msg = NULL;
        break;
    case EMsgTrack:
        msg = GenerateMsg(EMsgTrack);
        break;
    case EMsgEncodedStream:
        msg = GenerateMsg(EMsgEncodedStream);
        break;
    case EMsgAudioEncoded:
        msg = GenerateMsg(EMsgAudioEncoded);
        break;
    case EMsgMetaText:
        msg = GenerateMsg(EMsgMetaText);
        break;
    case EMsgHalt:
        msg = GenerateMsg(EMsgHalt);
        break;
    case EMsgFlush:
        msg = GenerateMsg(EMsgFlush);
        break;
    case EMsgQuit:
        msg = GenerateMsg(EMsgQuit);
        break;
    }
    return msg;
}

void SuiteRewinder::PullAndProcess()
{
    Msg* msg = iRewinder->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
}

void SuiteRewinder::PullFlush()
{
    EMsgType tmpType = iLastMsgType;
    iLastMsgType = EMsgFlush;
    PullAndProcess();
    iLastMsgType = tmpType;
}

void SuiteRewinder::TestAllocatorExhaustion()
{
    // test that pulling kMsgAudioEncodedCount+1 into Rewinder causes AllocatorNoMemory to be thrown
    for (TUint i = 0; i < kPreAudioMsgCount+kMsgAudioEncodedCount; i++)
    {
        PullAndProcess();
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
        PullAndProcess();
    }
    iStreamHandler->TryStop(0, 0);
    TEST(iTryStopCount == 0); // no TryStop msg should have been passed up
    for (TUint i = 0; i < kPostTryStopAudioCount; i++)
    {
        PullAndProcess();
    }
    // if executions gets to here, no longer buffering
}

void SuiteRewinder::TestTrySeekToStart()
{
    // test that buffering, then seeking back to the start works correctly
    static const TUint kPreTryStopAudioCount = 5;
    static const TUint kPostTryStopAudioCount = kPreTryStopAudioCount+5;
    for (TUint i = 0; i < kPreAudioMsgCount+kPreTryStopAudioCount; i++)
    {
        PullAndProcess();
    }
    // try seeking back to start
    iStreamHandler->TrySeek(0, 0, 0);
    PullFlush();
    iAudioIn = 0;
    for (TUint i = 0; i < kPostTryStopAudioCount; i++)
    {
        PullAndProcess();
    }
    // try seeking again
    iStreamHandler->TrySeek(0, 0, 0);
    PullFlush();
    iAudioIn = 0;
    for (TUint i = 0; i < kPostTryStopAudioCount; i++)
    {
        PullAndProcess();
    }
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
        PullAndProcess();
    }
    // TrySeek shouldn't be passed through while buffering
    seekRes = iStreamHandler->TrySeek(0,0,0);
    TEST(seekRes == iNextFlushId-1);
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


// SuiteRewinderNullMsgs

SuiteRewinderNullMsgs::SuiteRewinderNullMsgs()
    : SuiteRewinder("RewinderNullMsgs tests")
{
    AddTest(MakeFunctor(*this, &SuiteRewinderNullMsgs::TestNoNulls));
}

void SuiteRewinderNullMsgs::InitMsgOrder()
{
    // populate vector with normal stream interleaved with nulls
    iMsgOrder.push_back(ENull);
    iMsgOrder.push_back(EMsgTrack);
    iMsgOrder.push_back(ENull);
    iMsgOrder.push_back(ENull);
    iMsgOrder.push_back(EMsgEncodedStream);
    iMsgOrder.push_back(ENull);
    for (TUint i = 0; i < 10; i++) {
        iMsgOrder.push_back(EMsgAudioEncoded);
        iAudioEncodedCount++;
    }
    iMsgOrder.push_back(ENull);
    for (TUint i = 0; i < 5; i++) {
        iMsgOrder.push_back(EMsgAudioEncoded);
        iAudioEncodedCount++;
    }
    iMsgOrder.push_back(ENull);
    iMsgOrder.push_back(ENull);
    for (TUint i = 0; i < 10; i++) {
        iMsgOrder.push_back(EMsgAudioEncoded);
        iAudioEncodedCount++;
    }
    iMsgOrder.push_back(ENull);
    // end with a MsgAudioEncoded, otherwise Rewinder will keep pulling on NULLs
    // and test won't end sensibly
    iMsgOrder.push_back(EMsgAudioEncoded);
    iAudioEncodedCount++;
}

void SuiteRewinderNullMsgs::Setup()
{
    iAudioEncodedCount = 0;
    Init(kEncodedAudioCount, kMsgAudioEncodedCount, kMsgAudioEncodedCount);
}

void SuiteRewinderNullMsgs::TestNoNulls()
{
    // test that, under normal conditions, if a NULL msg is passed down the
    // pipeline, the Rewinder only ever returns non-NULL msgs
    for (TByte i = 0; i < kPreAudioMsgCount+iAudioEncodedCount-1; i++)
    {
        Msg* msg = iRewinder->Pull();
        TEST(msg != NULL);
        msg = msg->Process(*this);
        msg->RemoveRef();
    }
    // test that last msg pulled is final msg we queued
    Msg* msg = iRewinder->Pull();
    TEST(msg != NULL);
    TBool isFinalMsgSent = TestMsgAudioEncodedValue(*dynamic_cast<MsgAudioEncoded*>(msg), iAudioEncodedCount-1);
    TEST(isFinalMsgSent == true);
    msg = msg->Process(*this);
    msg->RemoveRef();
}


// SuiteRewinderSeekToStartAfterMiscAudio

SuiteRewinderSeekToStartAfterMiscAudio::SuiteRewinderSeekToStartAfterMiscAudio()
    : SuiteRewinder("RewinderSeekToStartAfterMiscAudio tests")
{
    AddTest(MakeFunctor(*this, &SuiteRewinderSeekToStartAfterMiscAudio::TestTrySeekToStartAfterMiscAudio));
}

SuiteRewinderSeekToStartAfterMiscAudio::SuiteRewinderSeekToStartAfterMiscAudio(const TChar* aName)
    : SuiteRewinder(aName)
{
    AddTest(MakeFunctor(*this, &SuiteRewinderSeekToStartAfterMiscAudio::TestTrySeekToStartAfterMiscAudio));
}

void SuiteRewinderSeekToStartAfterMiscAudio::InitMsgOrder()
{
    for (TUint i = 0; i < kStartOfNewStream; i++) {
        iMsgOrder.push_back(EMsgAudioEncoded);
    }
    iMsgOrder.push_back(EMsgTrack);
    iMsgOrder.push_back(EMsgEncodedStream);
    for (TUint i = 0; i < 15; i++) {
        iMsgOrder.push_back(EMsgAudioEncoded);
    }
}

void SuiteRewinderSeekToStartAfterMiscAudio::TestTrySeekToStartAfterMiscAudio()
{
    // test that after receiving X msgs of MsgAudioEncoded, then a
    // MsgEncodedStream followed by a TrySeek, only MsgAudioEncodeds received
    // after the MsgEncodedStream are passed through
    for (TByte i = 0; i < iMsgOrder.size(); i++)
    {
        PullAndProcess();
    }
    // try seek back to start of stream and test that seek is to start of
    // second stream of MsgAudioEncodeds
    TUint seekRes = iStreamHandler->TrySeek(0,0,0);
    TEST(seekRes == iNextFlushId-1);
    PullFlush();

    TEST(iTrySeekCount == 0);   // seek shouldn't have been passed upstream
    // pull next msg and test seek was to start of second stream
    iAudioIn = kStartOfNewStream;
    Msg* msg = iRewinder->Pull();
    TBool isStartOfStream = TestMsgAudioEncodedValue(*dynamic_cast<MsgAudioEncoded*>(msg), kStartOfNewStream);
    TEST(isStartOfStream == true);
    msg = msg->Process(*this);
    msg->RemoveRef();
}


// SuiteRewinderSeekToStartMultipleStreams

SuiteRewinderSeekToStartMultipleStreams::SuiteRewinderSeekToStartMultipleStreams()
    : SuiteRewinderSeekToStartAfterMiscAudio("RewinderSeekToStartMultipleStreams tests")
{
}

void SuiteRewinderSeekToStartMultipleStreams::InitMsgOrder()
{
    iMsgOrder.push_back(EMsgTrack);
    iMsgOrder.push_back(EMsgEncodedStream);
    for (TUint i = 0; i < kStartOfNewStream; i++) {
        iMsgOrder.push_back(EMsgAudioEncoded);
    }
    iMsgOrder.push_back(EMsgTrack);
    iMsgOrder.push_back(EMsgEncodedStream);
    for (TUint i = 0; i < 15; i++) {
        iMsgOrder.push_back(EMsgAudioEncoded);
    }
}


// SuiteRewinderMsgOrdering
SuiteRewinderMsgOrdering::SuiteRewinderMsgOrdering()
    : SuiteRewinder("RewinderMsgOrdering tests")
{
    AddTest(MakeFunctor(*this, &SuiteRewinderMsgOrdering::TestMsgOrdering));
}

void SuiteRewinderMsgOrdering::InitMsgOrder()
{
    iMsgOrder.push_back(EMsgFlush);
    iMsgOrder.push_back(EMsgTrack);
    iMsgOrder.push_back(EMsgEncodedStream);
    for (TUint i = 0; i < 10; i++) {
        iMsgOrder.push_back(EMsgAudioEncoded);
    }
    iMsgOrder.push_back(EMsgMetaText);
    iMsgOrder.push_back(EMsgAudioEncoded);
    iMsgOrder.push_back(EMsgFlush);
    iMsgOrder.push_back(EMsgAudioEncoded);
    iMsgOrder.push_back(EMsgHalt);
    iMsgOrder.push_back(EMsgAudioEncoded);
    iMsgOrder.push_back(EMsgQuit);
    iMsgOrder.push_back(EMsgAudioEncoded);
}

void SuiteRewinderMsgOrdering::TestMsgOrdering()
{
    // test that Rewinder passes through ALL msgs in order (even buffered ones)
    for (TByte i = 0; i < iMsgOrder.size(); i++)
    {
        Msg* msg = iRewinder->Pull();
        msg = msg->Process(*this);
        TEST(iRcvdMsgType == iMsgOrder[i]);
        msg->RemoveRef();
    }
}

void TestRewinder()
{
    Runner runner("Rewinder tests\n");
    runner.Add(new SuiteRewinder());
    runner.Add(new SuiteRewinderMaxCapacity());
    runner.Add(new SuiteRewinderNullMsgs());
    runner.Add(new SuiteRewinderSeekToStartAfterMiscAudio());
    runner.Add(new SuiteRewinderSeekToStartMultipleStreams());
    runner.Add(new SuiteRewinderMsgOrdering());
    runner.Run();
}
