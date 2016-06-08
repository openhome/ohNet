#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Media/MimeTypeList.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

namespace OpenHome {
namespace Media {
namespace Codec {

class TestUrlBlockWriter : public IUrlBlockWriter
{
public:
    TBool TryGet(IWriter& aWriter, const Brx& aUrl, TUint64 aOffset, TUint aBytes) override;
};

class ContainerNullBuffered : public ContainerNull
{
public:
    static const TUint kStartOffsetBytes = 5;
public:
    ContainerNullBuffered();
private: // from ContainerNull
    Msg* Pull() override;
    TBool TrySeek(TUint aStreamId, TUint64 aOffset) override;
private:
    static const TUint kBufferedAudioBytes = EncodedAudio::kMaxBytes*2;
};

class TestContainerMsgGenerator : public IPipelineElementUpstream, private INonCopyable
{
public:
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
    TestContainerMsgGenerator(MsgFactory& aMsgFactory
                             , TrackFactory& aTrackFactory
                             , IPipelineIdProvider& aPipelineIdProvider
                             , IFlushIdProvider& aFlushIdProvider
                             , IStreamHandler& aStreamHandler
                             );
    void SetMsgOrder(std::vector<EMsgType>& aMsgOrder);
    Msg* NextMsg();
    EMsgType LastMsgType();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private:
    MsgAudioEncoded* GenerateAudioMsg();
    Msg* GenerateMsg(EMsgType aType);
private:
    MsgFactory& iMsgFactory;
    TrackFactory& iTrackFactory;
    IPipelineIdProvider& iPipelineIdProvider;
    IFlushIdProvider& iFlushIdProvider;
    IStreamHandler& iStreamHandler;
    std::vector<EMsgType> iMsgOrder;
    TUint iMsgCount;
    TUint iAudioMsgCount;
    EMsgType iLastMsgType;
};

class TestContainerProvider : public IPipelineIdProvider, public IFlushIdProvider, public IStreamHandler
{
public:
    TestContainerProvider();
public: // from IFlushIdProvider
    TUint NextFlushId() override;
public: // from IPipelineIdProvider
    TUint NextStreamId() override;
public: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryDiscard(TUint aJiffies) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
public:
    TUint OkToPlayCount();
    TUint SeekCount();
    TUint StopCount();
    TUint LastSeekStreamId();
    TUint64 LastSeekOffset();
private:
    TUint iPendingFlushId;
    TUint iCurrentFlushId;
    TUint iNextStreamId;
    TUint iOkToPlayCount;
    TUint iSeekCount;
    TUint iStopCount;

    TUint iLastSeekStreamId;
    TUint64 iLastSeekOffset;
};

class TestContainerMsgProcessor : public IMsgProcessor
{
public: // from IMsgProcessor
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
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
};

//class SuiteMsgAudioEncodedCache : public SuiteUnitTest
//{
//public:
//    SuiteMsgAudioEncodedCache();
//private: // from SuiteUnitTest
//    void Setup() override;
//    void TearDown() override;
//private:
//    void TestDiscard();
//    void TestInspect(); // FIXME - need to test reading from cache that is already populated (i.e., doesn't have to pull more msgs through to satisfy request).
//    void TestAccumulate();
//    void TestMultiple();
//    void TestPassThrough();
//    void TestInterleaving();
//    void TestReset();
//private:
//    MsgAudioEncodedCache iCache;
//};

/**
 * Tests aspects of the ContainerController like msg ordering and stream 
 * handling. ContainerNull is implicitly shown to work by the fact that these
 * tests run to completion.
 */
class SuiteContainerBase : public SuiteUnitTest, public TestContainerMsgProcessor
{
public:
    SuiteContainerBase(const TChar* aSuiteName);
    ~SuiteContainerBase();
protected: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
protected:
    void PullAndProcess();
    TBool TestMsgAudioEncodedContent(MsgAudioEncoded& aMsg, TByte aValue);
    virtual TBool TestMsgAudioEncodedValue(MsgAudioEncoded& aMsg, TByte aValue);
    virtual TUint ExpectedSeekStartOffset();
protected: // Tests
    void TestNormalOperation();
    void TestMsgOrdering();
    void TestStreamHandling();
    void TestNewStream();
    void TestFlushPending();
    void TestFlushPendingStreamHandler();
private:
    void AddBaseTests();
protected:
    TestContainerMsgGenerator* iGenerator;
    TestContainerProvider* iProvider;
    TestUrlBlockWriter* iUrlBlockWriter;
    ContainerController* iContainer;
    TUint iStreamId;
    IStreamHandler* iStreamHandler;
    TUint iMsgRcvdCount;
    TByte iAudioRcvdCount;
private:
    static const TUint kEncodedAudioCount = 100;
    static const TUint kMsgAudioEncodedCount = 100;
    AllocatorInfoLogger iInfoAggregator;
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
};

class SuiteContainerUnbuffered : public SuiteContainerBase
{
public:
    SuiteContainerUnbuffered();
};

/**
 * Container that refuses to recognise any stream.
 */
class TestDummyContainer : public ContainerBase
{
public:
    TestDummyContainer();
    TUint RecogniseCount() const;
    TUint ResetCount() const;
public: // from SuiteContainerBase
    Msg* Recognise() override;
    TBool Recognised() const override;
    void Reset() override;
    TBool TrySeek(TUint aStreamId, TUint64 aOffset) override;
    Msg* Pull() override;
private:
    TUint iRecogniseCount;
    TUint iResetCount;
};

class SuiteContainerNull : public SuiteContainerBase
{
public:
    SuiteContainerNull();
private: // from SuiteUnitTest
    void Setup();
private:
    void TestNullContainer();
private:
    TestDummyContainer* iDummyContainer;
};

} // Codec
} // Media
} // OpenHome


// TestUrlBlockWriter

TBool TestUrlBlockWriter::TryGet(IWriter& /*aWriter*/, const Brx& /*aUrl*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return false;
}


// TestContainerMsgGenerator

TestContainerMsgGenerator::TestContainerMsgGenerator(MsgFactory& aMsgFactory
                                                    , TrackFactory& aTrackFactory
                                                    , IPipelineIdProvider& aPipelineIdProvider
                                                    , IFlushIdProvider& aFlushIdProvider
                                                    , IStreamHandler& aStreamHandler
                                                    )
    : iMsgFactory(aMsgFactory)
    , iTrackFactory(aTrackFactory)
    , iPipelineIdProvider(aPipelineIdProvider)
    , iFlushIdProvider(aFlushIdProvider)
    , iStreamHandler(aStreamHandler)
    , iMsgCount(0)
    , iAudioMsgCount(0)
    , iLastMsgType(ENone)
{
}

void TestContainerMsgGenerator::SetMsgOrder(std::vector<EMsgType>& aMsgOrder)
{
    iMsgOrder = aMsgOrder;
    iMsgCount = 0;
    iAudioMsgCount = 0;
    iLastMsgType = ENone;
}

Msg* TestContainerMsgGenerator::NextMsg()
{
    Msg* msg = nullptr;
    if (iMsgCount >= iMsgOrder.size()) {
        ASSERTS();
    }
    //ASSERT(iMsgCount < iMsgOrder.size());
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
        msg = nullptr;
        break;
    case EMsgMode:
        msg = GenerateMsg(EMsgMode);
        break;
    case EMsgTrack:
        msg = GenerateMsg(EMsgTrack);
        break;
    case EMsgDrain:
        msg = GenerateMsg(EMsgDrain);
        break;
    case EMsgDelay:
        msg = GenerateMsg(EMsgDelay);
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
    case EMsgStreamInterrupted:
        msg = GenerateMsg(EMsgStreamInterrupted);
        break;
    case EMsgHalt:
        msg = GenerateMsg(EMsgHalt);
        break;
    case EMsgFlush:
        msg = GenerateMsg(EMsgFlush);
        break;
    case EMsgWait:
        msg = GenerateMsg(EMsgWait);
        break;
    case EMsgQuit:
        msg = GenerateMsg(EMsgQuit);
        break;
    }
    return msg;
}

TestContainerMsgGenerator::EMsgType TestContainerMsgGenerator::LastMsgType()
{
    return iLastMsgType;
}

Msg* TestContainerMsgGenerator::Pull()
{
    return NextMsg();
}

MsgAudioEncoded* TestContainerMsgGenerator::GenerateAudioMsg()
{
    // create a MsgAudioEncoded filled with iAudioMsgCount;
    // iAudioMsgCount is incremented after each call
    static const TUint kDataBytes = EncodedAudio::kMaxBytes;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, iAudioMsgCount, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioEncoded* audio = iMsgFactory.CreateMsgAudioEncoded(encodedAudioBuf);
    iAudioMsgCount++;
    return audio;
}

Msg* TestContainerMsgGenerator::GenerateMsg(EMsgType aType)
{
    Msg* msg = nullptr;
    //Log::Print("TestContainerMsgGenerator::GenerateMsg: %u\n", aType);
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
    case EMsgMode:
        msg = iMsgFactory.CreateMsgMode(Brx::Empty(), true, ModeClockPullers(), false, false);
        iLastMsgType = EMsgMode;
        break;
    case EMsgTrack:
        {
        Track* track = iTrackFactory.CreateTrack(Brx::Empty(), Brx::Empty());
        msg = iMsgFactory.CreateMsgTrack(*track);
        track->RemoveRef();
        }
        iLastMsgType = EMsgTrack;
        break;
    case EMsgDrain:
        msg = iMsgFactory.CreateMsgDrain(Functor());
        iLastMsgType = EMsgDrain;
        break;
    case EMsgDelay:
        msg = iMsgFactory.CreateMsgDelay(Jiffies::kPerMs * 20);
        iLastMsgType = EMsgDelay;
        break;
    case EMsgEncodedStream:
        msg = iMsgFactory.CreateMsgEncodedStream(Brn("http://127.0.0.1:65535"), Brn("metatext"), 0, 0, iPipelineIdProvider.NextStreamId(), false, false, &iStreamHandler);
        iLastMsgType = EMsgEncodedStream;
        break;
    case EMsgAudioEncoded:
        msg = GenerateAudioMsg();
        iLastMsgType = EMsgAudioEncoded;
        break;
    case EMsgMetaText:
        msg = iMsgFactory.CreateMsgMetaText(Brn("metatext"));
        iLastMsgType = EMsgMetaText;
        break;
    case EMsgStreamInterrupted:
        msg = iMsgFactory.CreateMsgStreamInterrupted();
        iLastMsgType = EMsgStreamInterrupted;
        break;
    case EMsgHalt:
        msg = iMsgFactory.CreateMsgHalt();
        iLastMsgType = EMsgHalt;
        break;
    case EMsgFlush:
        msg = iMsgFactory.CreateMsgFlush(iFlushIdProvider.NextFlushId());
        iLastMsgType = EMsgFlush;
        break;
    case EMsgWait:
        msg = iMsgFactory.CreateMsgWait();
        iLastMsgType = EMsgWait;
        break;
    case EMsgQuit:
        msg = iMsgFactory.CreateMsgQuit();
        iLastMsgType = EMsgQuit;
        break;
    }
    return msg;
}


// TestContainerProvider
TestContainerProvider::TestContainerProvider()
    : iPendingFlushId(MsgFlush::kIdInvalid+1)
    , iCurrentFlushId(iPendingFlushId)
    , iNextStreamId(1)
    , iOkToPlayCount(0)
    , iSeekCount(0)
    , iStopCount(0)
    , iLastSeekStreamId(0)
    , iLastSeekOffset(0)
{
}

TUint TestContainerProvider::NextFlushId()
{
    return iPendingFlushId++;
}

TUint TestContainerProvider::NextStreamId()
{
    return iNextStreamId++;
}

EStreamPlay TestContainerProvider::OkToPlay(TUint /*aStreamId*/)
{
    iOkToPlayCount++;
    return ePlayYes;
}

TUint TestContainerProvider::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    iSeekCount++;
    iLastSeekStreamId = aStreamId;
    iLastSeekOffset = aOffset;
    return iCurrentFlushId++;
}

TUint TestContainerProvider::TryDiscard(TUint /*aJiffies*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint TestContainerProvider::TryStop(TUint /*aStreamId*/)
{
    iStopCount++;
    return iCurrentFlushId++;
}

void TestContainerProvider::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/, TBool /*aStarving*/)
{
}

TUint TestContainerProvider::OkToPlayCount()
{
    return iOkToPlayCount;
}

TUint TestContainerProvider::SeekCount()
{
    return iSeekCount;
}

TUint TestContainerProvider::StopCount()
{
    return iStopCount;
}

TUint TestContainerProvider::LastSeekStreamId()
{
    return iLastSeekStreamId;
}

TUint64 TestContainerProvider::LastSeekOffset()
{
    return iLastSeekOffset;
}


// TestContainerMsgProcessor

Msg* TestContainerMsgProcessor::ProcessMsg(MsgAudioEncoded* aMsg)
{
    return aMsg;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return nullptr;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return nullptr;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return nullptr;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return nullptr;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgBitRate* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return nullptr;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgDrain* aMsg)
{
    return aMsg;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgEncodedStream* aMsg)
{
    return aMsg;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    return aMsg;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgFlush* aMsg)
{
    return aMsg;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}


// SuiteContainerBase

SuiteContainerBase::SuiteContainerBase(const TChar* aSuiteName)
    : SuiteUnitTest(aSuiteName)
{
    AddBaseTests();
}

SuiteContainerBase::~SuiteContainerBase()
{
}

void SuiteContainerBase::Setup()
{
    iProvider = new TestContainerProvider();
    MsgFactoryInitParams init;
    init.SetMsgAudioEncodedCount(kEncodedAudioCount, kEncodedAudioCount);
    init.SetMsgEncodedStreamCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    std::vector<TestContainerMsgGenerator::EMsgType> msgOrder;
    iGenerator = new TestContainerMsgGenerator(*iMsgFactory, *iTrackFactory, *iProvider, *iProvider, *iProvider);
    iUrlBlockWriter = new TestUrlBlockWriter();
    iContainer = new ContainerController(*iMsgFactory, *iGenerator, *iUrlBlockWriter);
    iStreamId = 0;
    iStreamHandler = nullptr;
    iMsgRcvdCount = 0;
    iAudioRcvdCount = 0;
}

void SuiteContainerBase::TearDown()
{
    delete iContainer;
    delete iUrlBlockWriter;
    delete iGenerator;
    delete iMsgFactory;
    delete iProvider;
    delete iTrackFactory;
}

void SuiteContainerBase::AddBaseTests()
{
    AddTest(MakeFunctor(*this, &SuiteContainerBase::TestNormalOperation), "TestNormalOperation");
    AddTest(MakeFunctor(*this, &SuiteContainerBase::TestMsgOrdering), "TestMsgOrdering");
    AddTest(MakeFunctor(*this, &SuiteContainerBase::TestStreamHandling), "TestStreamHandling");
    AddTest(MakeFunctor(*this, &SuiteContainerBase::TestNewStream), "TestNewStream");
    AddTest(MakeFunctor(*this, &SuiteContainerBase::TestFlushPending), "TestFlushPending");
    AddTest(MakeFunctor(*this, &SuiteContainerBase::TestFlushPendingStreamHandler), "TestFlushPendingStreamHandler");
}

void SuiteContainerBase::PullAndProcess()
{
    Msg* msg = iContainer->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
    iMsgRcvdCount++;
}

TBool SuiteContainerBase::TestMsgAudioEncodedContent(MsgAudioEncoded& aMsg, TByte aValue)
{
    // Test MsgAudioEncoded is correct size and contains expected value.
    Bws<EncodedAudio::kMaxBytes> buf;
    //Log::Print("TestMsgAudioEncodedContent: aMsg.Bytes(): %u, buf.MaxBytes(): %u\n", aMsg.Bytes(), buf.MaxBytes());
    ASSERT(aMsg.Bytes() <= buf.MaxBytes());
    aMsg.CopyTo(const_cast<TByte*>(buf.Ptr()));
    buf.SetBytes(aMsg.Bytes());
    //Log::Print("TestMsgAudioEncodedContent: buf[0]: %d, aValue: %d\n", buf[0], aValue);
    if ((buf[0] != aValue) || (buf[buf.Bytes()-1] != aValue)) {
        return false;
    }
    return true;
}

TBool SuiteContainerBase::TestMsgAudioEncodedValue(MsgAudioEncoded& aMsg, TByte aValue)
{
    if ((iGenerator->LastMsgType() != TestContainerMsgGenerator::EMsgAudioEncoded) || (aMsg.Bytes() != EncodedAudio::kMaxBytes))
    {
        return false;
    }
    return TestMsgAudioEncodedContent(aMsg, aValue);
}

TUint SuiteContainerBase::ExpectedSeekStartOffset()
{
    return 0;
}

Msg* SuiteContainerBase::ProcessMsg(MsgAudioEncoded* aMsg)
{
    TBool expected = TestMsgAudioEncodedValue(*aMsg, iAudioRcvdCount);
    TEST(expected);
    iAudioRcvdCount++;
    return aMsg;
}

Msg* SuiteContainerBase::ProcessMsg(MsgMode* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgMode);
    return aMsg;
}

Msg* SuiteContainerBase::ProcessMsg(MsgTrack* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgTrack);
    return aMsg;
}

Msg* SuiteContainerBase::ProcessMsg(MsgDrain* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgDrain);
    return aMsg;
}

Msg* SuiteContainerBase::ProcessMsg(MsgDelay* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgDelay);
    return aMsg;
}

Msg* SuiteContainerBase::ProcessMsg(MsgEncodedStream* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgEncodedStream);
    iStreamHandler = aMsg->StreamHandler();
    iStreamId = aMsg->StreamId();
    return aMsg;
}

Msg* SuiteContainerBase::ProcessMsg(MsgMetaText* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgMetaText);
    return aMsg;
}

Msg* SuiteContainerBase::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgStreamInterrupted);
    return aMsg;
}

Msg* SuiteContainerBase::ProcessMsg(MsgHalt* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgHalt);
    return aMsg;
}

Msg* SuiteContainerBase::ProcessMsg(MsgFlush* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgFlush);
    return aMsg;
}

Msg* SuiteContainerBase::ProcessMsg(MsgWait* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgWait);
    return aMsg;
}

Msg* SuiteContainerBase::ProcessMsg(MsgQuit* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgQuit);
    return aMsg;
}

void SuiteContainerBase::TestNormalOperation()
{
    // Populate vector with normal type/order of stream msgs
    std::vector<TestContainerMsgGenerator::EMsgType> msgOrder;
    msgOrder.push_back(TestContainerMsgGenerator::EMsgMode);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgTrack);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgDrain);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgDelay);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgEncodedStream);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgStreamInterrupted);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgQuit);

    iGenerator->SetMsgOrder(msgOrder);

    while (iMsgRcvdCount < msgOrder.size()) {
        PullAndProcess();
    }
}

void SuiteContainerBase::TestMsgOrdering()
{
    // Pull through a variety of Msgs and let the ProcessMsg methods above do
    // the checking that the Msg pulled was the last sent.
    // Successful completion of this test means all msgs were pulled through in
    // correct order.
    // MsgFlush is tested elsewhere, as sending a MsgFlush during this test
    // will cause loss of any buffered audio.
    std::vector<TestContainerMsgGenerator::EMsgType> msgOrder;
    msgOrder.push_back(TestContainerMsgGenerator::EMsgTrack);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgEncodedStream);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgMetaText);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgWait);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgEncodedStream);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgHalt);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgQuit);

    iGenerator->SetMsgOrder(msgOrder);

    while (iMsgRcvdCount < msgOrder.size()) {
        PullAndProcess();
    }
}

void SuiteContainerBase::TestStreamHandling()
{
    // Test IStreamHandler calls are successfully passed through while streaming
    // Can't pull any MsgAudioEncoded in this test, as can't accurately
    // determine how many to pull for both unbuffered and buffered containers
    // before pulling the MsgQuit.
    std::vector<TestContainerMsgGenerator::EMsgType> msgOrder;
    msgOrder.push_back(TestContainerMsgGenerator::EMsgTrack);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgEncodedStream);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgQuit);

    iGenerator->SetMsgOrder(msgOrder);

    for (TUint i=0; i < 2; i++) { // pull until new stream marker
        PullAndProcess();
    }

    EStreamPlay iOkToPlayRes = iContainer->OkToPlay(iStreamId);
    TEST(iOkToPlayRes == ePlayYes);
    TEST(iProvider->OkToPlayCount() == 1);
    TUint iSeekRes = iContainer->TrySeek(iStreamId, 0);
    TEST(iSeekRes != MsgFlush::kIdInvalid);
    TEST(iProvider->SeekCount() == 1);
    TUint iStopRes = iContainer->TryStop(iStreamId);
    TEST(iStopRes != MsgFlush::kIdInvalid);
    TEST(iProvider->StopCount() == 1);

    while (iMsgRcvdCount < msgOrder.size()) { // pull remainder through
        PullAndProcess();
    }
}

void SuiteContainerBase::TestNewStream()
{
    // Test that when a new MsgEncodedStream is coming down the pipeline, all
    // MsgAudioEncoded from previous stream are received before it, to avoid
    // any out-of-order issues (or corruption/loss of buffered audio)

    std::vector<TestContainerMsgGenerator::EMsgType> msgOrder;
    msgOrder.push_back(TestContainerMsgGenerator::EMsgTrack);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgEncodedStream);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgEncodedStream);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgQuit);

    iGenerator->SetMsgOrder(msgOrder);

    while (iMsgRcvdCount < msgOrder.size()) {
        PullAndProcess();
    }
}

void SuiteContainerBase::TestFlushPending()
{
    // Get a pending flush by doing a TrySeek or TryStop then pump more
    // MsgAudioEncoded down the pipeline before eventually sending the expected
    // seek. all MsgAudioEncoded sent during waiting on the pending flush
    // must be disposed of

    // calculate msg counts for calling seek and stop, and determine end of msgs
    static const TUint kDiscardedAudio = 3;

    std::vector<TestContainerMsgGenerator::EMsgType> msgOrder;
    msgOrder.push_back(TestContainerMsgGenerator::EMsgTrack);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgEncodedStream);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    static const TUint kMsgCountSeek = 5;

    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgFlush);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    static const TUint kMsgCountStop = kMsgCountSeek + 7;

    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgFlush);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgQuit);
    static const TUint kCountFinish = kMsgCountStop + 8;

    iGenerator->SetMsgOrder(msgOrder);

    // pull msgs until we're halfway through first batch of audio
    while (iMsgRcvdCount < kMsgCountSeek)
    {
        PullAndProcess();
    }

    // then call a TrySeek so Container awaits a pending flush
    TUint seekRes = iContainer->TrySeek(iStreamId, 0);
    TEST(iProvider->SeekCount() == 1);
    TEST(seekRes != MsgFlush::kIdInvalid);
    TEST(iProvider->LastSeekStreamId() == iStreamId);
    TEST(iProvider->LastSeekOffset() == ExpectedSeekStartOffset());

    // then pull more through - all MsgAudioEncoded up to MsgFlush should be
    // disposed of; increment iAudioRcvdCount/iMsgRcvdCount to account for this
    iAudioRcvdCount += kDiscardedAudio;
    iMsgRcvdCount += kDiscardedAudio;
    while (iMsgRcvdCount < kMsgCountStop)
    {
        PullAndProcess();
    }

    // then do a TryStop, as with the TrySeek above
    TUint stopRes = iContainer->TryStop(iStreamId);
    TEST(iProvider->StopCount() == 1);
    TEST(stopRes != MsgFlush::kIdInvalid);

    // pull remainder of msgs through
    iAudioRcvdCount += kDiscardedAudio;
    iMsgRcvdCount += kDiscardedAudio;
    while (iMsgRcvdCount < kCountFinish) {
        PullAndProcess();
    }
}

void SuiteContainerBase::TestFlushPendingStreamHandler()
{
    // Get a pending flush by doing a TrySeek or TryStop then pump more
    // MsgAudioEncoded down the pipeline before eventually sending the expected
    // seek. all MsgAudioEncoded sent during waiting on the pending flush
    // must be disposed of

    // calculate msg counts for calling seek and stop, and determine end of msgs
    static const TUint kDiscardedAudio = 3;

    std::vector<TestContainerMsgGenerator::EMsgType> msgOrder;
    msgOrder.push_back(TestContainerMsgGenerator::EMsgTrack);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgEncodedStream);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    static const TUint kMsgCountSeek = 5;

    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgFlush);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    static const TUint kMsgCountStop = kMsgCountSeek + 7;

    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgFlush);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgQuit);
    static const TUint kCountFinish = kMsgCountStop + 8;

    iGenerator->SetMsgOrder(msgOrder);

    // pull msgs until we're halfway through first batch of audio
    while (iMsgRcvdCount < kMsgCountSeek)
    {
        PullAndProcess();
    }

    // then call a TrySeek so Container awaits a pending flush

    // Call TrySeek()/TryStop() on the IStreamHandler that's been passed down,
    // instead of directly on iContainer.
    ASSERT(iStreamHandler != nullptr);
    TUint seekRes = iStreamHandler->TrySeek(iStreamId, 0);
    TEST(iProvider->SeekCount() == 1);
    TEST(seekRes != MsgFlush::kIdInvalid);
    TEST(iProvider->LastSeekStreamId() == iStreamId);
    TEST(iProvider->LastSeekOffset() == ExpectedSeekStartOffset());

    // then pull more through - all MsgAudioEncoded up to MsgFlush should be
    // disposed of; increment iAudioRcvdCount/iMsgRcvdCount to account for this
    iAudioRcvdCount += kDiscardedAudio;
    iMsgRcvdCount += kDiscardedAudio;
    while (iMsgRcvdCount < kMsgCountStop)
    {
        PullAndProcess();
    }

    // then do a TryStop, as with the TrySeek above
    TUint stopRes = iStreamHandler->TryStop(iStreamId);
    TEST(iProvider->StopCount() == 1);
    TEST(stopRes != MsgFlush::kIdInvalid);

    // pull remainder of msgs through
    iAudioRcvdCount += kDiscardedAudio;
    iMsgRcvdCount += kDiscardedAudio;
    while (iMsgRcvdCount < kCountFinish) {
        PullAndProcess();
    }
}


// SuiteContainerUnbuffered

SuiteContainerUnbuffered::SuiteContainerUnbuffered()
    : SuiteContainerBase("SuiteContainerUnbuffered")
{
}


// TestDummyContainer

TestDummyContainer::TestDummyContainer()
    : ContainerBase(Brn("DUMC"))
    , iRecogniseCount(0)
    , iResetCount(0)
{
}

TUint TestDummyContainer::RecogniseCount() const
{
    return iRecogniseCount;
}

TUint TestDummyContainer::ResetCount() const
{
    return iResetCount;
}

Msg* TestDummyContainer::Recognise()
{
    iRecogniseCount++;
    return nullptr;
}

TBool TestDummyContainer::Recognised() const
{
    return false;
}

void TestDummyContainer::Reset()
{
    iResetCount++;
}

TBool TestDummyContainer::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return false;
}

Msg* TestDummyContainer::Pull()
{
    ASSERTS();
    return nullptr;
}


// SuiteContainerNull
SuiteContainerNull::SuiteContainerNull()
    : SuiteContainerBase("SuiteContainerNull")
{
    AddTest(MakeFunctor(*this, &SuiteContainerNull::TestNullContainer), "TestNullContainer");
}

void SuiteContainerNull::Setup()
{
    SuiteContainerBase::Setup();
    iDummyContainer = new TestDummyContainer();
    iContainer->AddContainer(iDummyContainer);  // Takes ownership.
}

void SuiteContainerNull::TestNullContainer()
{
    // add some plugins to the container and send through a stream which none
    // will recognise; the Null container should still end up recognising it

    // successful completion of this test shows that the Null plugin is working

    std::vector<TestContainerMsgGenerator::EMsgType> msgOrder;
    msgOrder.push_back(TestContainerMsgGenerator::EMsgTrack);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgEncodedStream);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgQuit);

    iGenerator->SetMsgOrder(msgOrder);

    for (TUint i = 0; i < msgOrder.size(); i++) {
        PullAndProcess();
    }

    TEST(iDummyContainer->RecogniseCount() == 1);
    TEST(iDummyContainer->ResetCount() > 0);
}


void TestContainer()
{
    Runner runner("Container tests\n");
    runner.Add(new SuiteContainerUnbuffered());
    runner.Add(new SuiteContainerNull());
    runner.Run();
}
