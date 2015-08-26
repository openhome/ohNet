#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/Rewinder.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>

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
        ,EMsgMode
        ,EMsgTrack
        ,EMsgDrain
        ,EMsgDelay
        ,EMsgEncodedStream
        ,EMsgMetaText
        ,EMsgStreamInterrupted
        ,EMsgHalt
        ,EMsgFlush
        ,EMsgWait
        ,EMsgQuit
    };
public:
    SuiteRewinder(const TChar* aName);
    SuiteRewinder();
protected:
    virtual void InitMsgOrder();
    void Init(TUint aEncodedAudioCount, TUint aMsgAudioEncodedCount);
    TBool TestMsgAudioEncodedValue(MsgAudioEncoded& aMsg, TByte aValue);
    Msg* GenerateNextMsg();
    void PullAndProcess();
    void PullFlush();
private:
    TByte LastCount();
    void SetLastCount(TByte aCount);
    MsgAudioEncoded* CreateAudio();
    Msg* GenerateMsg(EMsgType aType);
    void TestStop();
    void TestTrySeekToStart();
    void TestUpstreamRequestPassThrough();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
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
protected:
    AllocatorInfoLogger iInfoAggregator;
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    Rewinder* iRewinder;
    IStreamHandler* iStreamHandler;
    std::vector<EMsgType> iMsgOrder;
    TUint iMsgCount;
    Msg* iLastMsg;
    EMsgType iLastMsgType;
    EMsgType iRcvdMsgType;
    TByte iAudioOut;
    TByte iAudioIn;
    TUint iCurrentFlushId;
    TUint iOkToPlayCount;
    TUint iTrySeekCount;
    TUint64 iLastSeekOffset;
    TUint iTryStopCount;
    TUint iStreamId;
    TUint iNextStreamId;
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
protected:
    TByte iStartOfStreamValue;
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
    void TestMultipleMsgEncodedStreamRewindStop();
    TBool PullAndCompare(EMsgType aMsgType, TUint aStreamId);
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
    AddTest(MakeFunctor(*this, &SuiteRewinder::TestStop), "TestStop");
    AddTest(MakeFunctor(*this, &SuiteRewinder::TestTrySeekToStart), "TestTrySeekToStart");
    AddTest(MakeFunctor(*this, &SuiteRewinder::TestUpstreamRequestPassThrough), "TestUpstreamRequestPassThrough");
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

void SuiteRewinder::Init(TUint aEncodedAudioCount, TUint aMsgAudioEncodedCount)
{
    MsgFactoryInitParams init;
    init.SetMsgAudioEncodedCount(aMsgAudioEncodedCount, aEncodedAudioCount);
    init.SetMsgAudioPcmCount(100, 100);
    init.SetMsgEncodedStreamCount(3);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iRewinder = new Rewinder(*iMsgFactory, *this);
    iStreamHandler = nullptr;
    iMsgOrder.clear();
    iMsgCount = 0;
    iLastMsgType = ENone;
    iRcvdMsgType = ENone;
    iAudioOut = 0;
    iAudioIn = 0;
    iCurrentFlushId = 1;
    iOkToPlayCount = 0;
    iTrySeekCount = 0;
    iLastSeekOffset = 0;
    iTryStopCount = 0;
    iStreamId = 0;
    iNextStreamId = IPipelineIdProvider::kStreamIdInvalid+1;
    InitMsgOrder();
}

void SuiteRewinder::Setup()
{
    Init(kEncodedAudioCount, kMsgAudioEncodedCount);
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

EStreamPlay SuiteRewinder::OkToPlay(TUint /*aStreamId*/)
{
    iOkToPlayCount++;
    return ePlayYes;
}

TUint SuiteRewinder::TrySeek(TUint /*aStreamId*/, TUint64 aOffset)
{
    iTrySeekCount++;
    iLastSeekOffset = aOffset;
    return ++iCurrentFlushId;
}

TUint SuiteRewinder::TryStop(TUint /*aStreamId*/)
{
    iTryStopCount++;
    return ++iCurrentFlushId;
}

void SuiteRewinder::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/, TBool /*aStarving*/)
{
}

Msg* SuiteRewinder::ProcessMsg(MsgMode* aMsg)
{
    TEST(iLastMsgType == EMsgMode);
    iRcvdMsgType = EMsgMode;
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgTrack* aMsg)
{
    TEST(iLastMsgType == EMsgTrack);
    iRcvdMsgType = EMsgTrack;
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgDrain* aMsg)
{
    TEST(iLastMsgType == EMsgDrain);
    iRcvdMsgType = EMsgDrain;
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgDelay* aMsg)
{
    TEST(iLastMsgType == EMsgDelay);
    iRcvdMsgType = EMsgDelay;
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgEncodedStream* aMsg)
{
    TEST(iLastMsgType == EMsgEncodedStream);
    iStreamHandler = aMsg->StreamHandler();
    iRcvdMsgType = EMsgEncodedStream;
    iStreamId = aMsg->StreamId();
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgAudioEncoded* aMsg)
{
    TBool isCorrectMsg = TestMsgAudioEncodedValue(*aMsg, iAudioIn);
    TEST(isCorrectMsg == true);
    iAudioIn++;
    iRcvdMsgType = EMsgAudioEncoded;
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgMetaText* aMsg)
{
    TEST(iLastMsgType == EMsgMetaText);
    iRcvdMsgType = EMsgMetaText;
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    TEST(iLastMsgType == EMsgStreamInterrupted);
    iRcvdMsgType = EMsgStreamInterrupted;
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

Msg* SuiteRewinder::ProcessMsg(MsgWait* aMsg)
{
    TEST(iLastMsgType == EMsgWait);
    iRcvdMsgType = EMsgWait;
    return aMsg;
}

Msg* SuiteRewinder::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return nullptr;
}

Msg* SuiteRewinder::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return nullptr;
}

Msg* SuiteRewinder::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return nullptr;
}

Msg* SuiteRewinder::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return nullptr;
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
    Msg* msg = nullptr;
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
        return nullptr;
    case EMsgTrack:
        {
        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
        msg = iMsgFactory->CreateMsgTrack(*track);
        track->RemoveRef();
        }
        iLastMsgType = EMsgTrack;
        break;
    case EMsgDrain:
        msg = iMsgFactory->CreateMsgDrain(Functor());
        iLastMsgType = EMsgDrain;
        break;
    case EMsgEncodedStream:
        msg = iMsgFactory->CreateMsgEncodedStream(Brn("http://127.0.0.1:65535"), Brn("metatext"), 0, iNextStreamId++, false, false, this);
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
    case EMsgStreamInterrupted:
        msg = iMsgFactory->CreateMsgStreamInterrupted();
        iLastMsgType = EMsgStreamInterrupted;
        break;
    case EMsgHalt:
        msg = iMsgFactory->CreateMsgHalt();
        iLastMsgType = EMsgHalt;
        break;
    case EMsgFlush:
        msg = iMsgFactory->CreateMsgFlush(0);
        iLastMsgType = EMsgFlush;
        break;
    case EMsgWait:
        msg = iMsgFactory->CreateMsgWait();
        iLastMsgType = EMsgWait;
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
    ASSERT(iMsgCount < iMsgOrder.size());
    return GenerateMsg(iMsgOrder[iMsgCount++]);
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

void SuiteRewinder::TestStop()
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
    iRewinder->Stop();
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
    // try rewinding back to start
    iRewinder->Rewind();
    iAudioIn = 0;
    for (TUint i = 0; i < kPostTryStopAudioCount; i++)
    {
        PullAndProcess();
    }
    // try rewinding again
    iRewinder->Rewind();
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

    TUint seekRes = 0;
    TUint expectedSeekCount = 1;
    EStreamPlay playRes = ePlayNo;
    TUint expectedOkToPlayCount = 1;
    TUint stopRes = 0;
    TUint expectedStopCount = 1;

    TEST(iStreamHandler == nullptr);
    for (TUint i = 0; i < kPreAudioMsgCount+kAudioCount; i++)
    {
        PullAndProcess();
    }

    // TrySeek should be passed through, regardless of buffering state
    // non-current track
    seekRes = iStreamHandler->TrySeek(0,1);
    TEST(seekRes == iCurrentFlushId);
    TEST(iTrySeekCount == expectedSeekCount++);
    TEST(iLastSeekOffset == 1);
    // non-current stream
    seekRes = iStreamHandler->TrySeek(1,2);
    TEST(seekRes == iCurrentFlushId);
    TEST(iTrySeekCount == expectedSeekCount++);
    TEST(iLastSeekOffset == 2);
    // non-current track and stream
    seekRes = iStreamHandler->TrySeek(1,3);
    TEST(seekRes == iCurrentFlushId);
    TEST(iTrySeekCount == expectedSeekCount++);
    TEST(iLastSeekOffset == 3);

    // non-current track
    stopRes = iStreamHandler->TryStop(0);
    TEST(stopRes == iCurrentFlushId);
    TEST(iTryStopCount == expectedStopCount++);
    // non-current stream
    stopRes = iStreamHandler->TryStop(1);
    TEST(stopRes == iCurrentFlushId);
    TEST(iTryStopCount == expectedStopCount++);
    // non-current track or stream
    stopRes = iStreamHandler->TryStop(1);
    TEST(stopRes == iCurrentFlushId);
    TEST(iTryStopCount == expectedStopCount++);

    // OkToPlay should always be passed through
    playRes = iStreamHandler->OkToPlay(0);
    TEST(playRes == ePlayYes);
    TEST(iOkToPlayCount == expectedOkToPlayCount++);

    // now call Stop and repeat calls - ALL calls should be passed through afterwards
    iRewinder->Stop();
    // TrySeek on current track should succeed when no longer buffering
    seekRes = iStreamHandler->TrySeek(0,0);
    TEST(seekRes == iCurrentFlushId);
    TEST(iTrySeekCount == expectedSeekCount++);
    TEST(iLastSeekOffset == 0);
    // TrySeek should be passed through while buffering if not current track or stream
    // non-current track
    seekRes = iStreamHandler->TrySeek(0,1);
    TEST(seekRes == iCurrentFlushId);
    TEST(iTrySeekCount == expectedSeekCount++);
    TEST(iLastSeekOffset == 1);
    // non-current stream
    seekRes = iStreamHandler->TrySeek(1,2);
    TEST(seekRes == iCurrentFlushId);
    TEST(iTrySeekCount == expectedSeekCount++);
    TEST(iLastSeekOffset == 2);
    // non-current track or stream
    seekRes = iStreamHandler->TrySeek(1,3);
    TEST(seekRes == iCurrentFlushId);
    TEST(iTrySeekCount == expectedSeekCount++);
    TEST(iLastSeekOffset == 3);

    // TryStop should have same behaviour as TrySeek when no longer buffering
    // TryStop on current track should succeed when no longer buffering
    stopRes = iStreamHandler->TryStop(0);
    TEST(stopRes == iCurrentFlushId);
    TEST(iTryStopCount == expectedStopCount++);
    // non-current track
    stopRes = iStreamHandler->TryStop(0);
    TEST(stopRes == iCurrentFlushId);
    TEST(iTryStopCount == expectedStopCount++);
    // non-current stream
    stopRes = iStreamHandler->TryStop(1);
    TEST(stopRes == iCurrentFlushId);
    TEST(iTryStopCount == expectedStopCount++);
    // non-current track or stream
    stopRes = iStreamHandler->TryStop(1);
    TEST(stopRes == iCurrentFlushId);
    TEST(iTryStopCount == expectedStopCount++);

    // OkToPlay should always be passed through
    playRes = iStreamHandler->OkToPlay(0);
    TEST(playRes == ePlayYes);
    TEST(iOkToPlayCount == expectedOkToPlayCount++);
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
    Init(kEncodedAudioCount, kMsgAudioEncodedCount);
}

void SuiteRewinderNullMsgs::TestNoNulls()
{
    // test that, under normal conditions, if a nullptr msg is passed down the
    // pipeline, the Rewinder only ever returns non-nullptr msgs
    for (TByte i = 0; i < kPreAudioMsgCount+iAudioEncodedCount-1; i++)
    {
        Msg* msg = iRewinder->Pull();
        TEST(msg != nullptr);
        msg = msg->Process(*this);
        msg->RemoveRef();
    }
    // test that last msg pulled is final msg we queued
    Msg* msg = iRewinder->Pull();
    TEST(msg != nullptr);
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
    iStartOfStreamValue = kStartOfNewStream;
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
    for (TByte i = 0; i < iMsgOrder.size(); i++) {
        PullAndProcess();
    }
    // try rewind back to start of stream and test that seek is to start of
    // second stream of MsgAudioEncodeds
    iRewinder->Rewind();
    // pull next msg and test seek was to start of first stream
    iAudioIn = iStartOfStreamValue;
    Msg* msg = iRewinder->Pull();
    TBool isStartOfStream = TestMsgAudioEncodedValue(*dynamic_cast<MsgAudioEncoded*>(msg), iStartOfStreamValue);
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
    iStartOfStreamValue = 0;
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
    AddTest(MakeFunctor(*this, &SuiteRewinderMsgOrdering::TestMsgOrdering), "TestMsgOrdering");
    AddTest(MakeFunctor(*this, &SuiteRewinderMsgOrdering::TestMultipleMsgEncodedStreamRewindStop), "TestMultipleMsgEncodedStreamRewindStop");
}

void SuiteRewinderMsgOrdering::InitMsgOrder()
{
    iMsgOrder.push_back(EMsgFlush);
    iMsgOrder.push_back(EMsgTrack);
    iMsgOrder.push_back(EMsgDrain);
    iMsgOrder.push_back(EMsgEncodedStream);
    for (TUint i = 0; i < 10; i++) {
        iMsgOrder.push_back(EMsgAudioEncoded);
    }
    iMsgOrder.push_back(EMsgMetaText);
    iMsgOrder.push_back(EMsgStreamInterrupted);
    iMsgOrder.push_back(EMsgAudioEncoded);
    iMsgOrder.push_back(EMsgFlush);
    iMsgOrder.push_back(EMsgAudioEncoded);
    iMsgOrder.push_back(EMsgWait);
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

void SuiteRewinderMsgOrdering::TestMultipleMsgEncodedStreamRewindStop()
{
    iMsgOrder.clear();

    // generate 1 track -> 3 stream to test buffering
    iMsgOrder.push_back(EMsgTrack);
    iMsgOrder.push_back(EMsgEncodedStream);
    iMsgOrder.push_back(EMsgEncodedStream);
    iMsgOrder.push_back(EMsgEncodedStream);

    Msg* msg = iRewinder->Pull();
    msg = msg->Process(*this);
    TEST(iRcvdMsgType == EMsgTrack);
    msg->RemoveRef();

    TEST(PullAndCompare(EMsgEncodedStream, 1) == true);
    TEST(PullAndCompare(EMsgEncodedStream, 2) == true);
    iRewinder->Rewind();

    // Check that when we pull on the Rewinder again after rewinding, we still
    // get the buffered MsgEncodedStream (i.e., ensure it hasn't been discarded).
    TEST(PullAndCompare(EMsgEncodedStream, 2) == true);
    iRewinder->Rewind();
    iRewinder->Stop();

    TEST(PullAndCompare(EMsgEncodedStream, 2) == true);
    TEST(PullAndCompare(EMsgEncodedStream, 3) == true);
    iRewinder->Rewind();
    iRewinder->Stop();

    TEST(PullAndCompare(EMsgEncodedStream, 3) == true);
    iRewinder->Rewind();
    iRewinder->Stop();
}

TBool SuiteRewinderMsgOrdering::PullAndCompare(EMsgType aMsgType, TUint aStreamId)
{
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    Msg* msg = iRewinder->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
    if (iRcvdMsgType != aMsgType) {
        return false;
    }
    if (iStreamId != aStreamId) {
        return false;
    }
    return true;
}


void TestRewinder()
{
    Runner runner("Rewinder tests\n");
    runner.Add(new SuiteRewinder());
    runner.Add(new SuiteRewinderNullMsgs());
    runner.Add(new SuiteRewinderSeekToStartAfterMiscAudio());
    runner.Add(new SuiteRewinderSeekToStartMultipleStreams());
    runner.Add(new SuiteRewinderMsgOrdering());
    runner.Run();
}
