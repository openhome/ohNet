#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/Id3v2.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
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
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    TUint TrySeek(TUint aStreamId, TUint64 aOffset);
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
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
};

class SuiteContainerBase : public SuiteUnitTest, public TestContainerMsgProcessor
{
public:
    SuiteContainerBase(const TChar* aSuiteName);
    ~SuiteContainerBase();
protected: // from SuiteUnitTest
    void Setup();
    void TearDown();
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
    void TestEndOfStreamQuit();
    void TestNewStream();
    void TestFlushPending();
    void TestFlushPendingStreamHandler();
private:
    void AddBaseTests();
protected:
    TestContainerMsgGenerator* iGenerator;
    TestContainerProvider* iProvider;
    TestUrlBlockWriter* iUrlBlockWriter;
    Container* iContainer;
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

class SuiteContainerBuffered : public SuiteContainerBase
{
public:
    SuiteContainerBuffered();
private: // from SuiteUnitTest
    void Setup();
private: // from SuiteContainerBase
    TBool TestMsgAudioEncodedContent(MsgAudioEncoded& aMsg, TByte aValue);
    TBool TestMsgAudioEncodedValue(MsgAudioEncoded& aMsg, TByte aValue);
    TUint ExpectedSeekStartOffset();
private:
    TUint iMsgBytesRcvd;
};

class SuiteContainerNull : public SuiteContainerBase
{
public:
    SuiteContainerNull();
private: // from SuiteUnitTest
    void Setup();
private: // Tests
    void TestNullContainer();
private:
    MimeTypeList iMimeTypes;
};

} // Codec
} // Media
} // OpenHome


// TestUrlBlockWriter

TBool TestUrlBlockWriter::TryGet(IWriter& /*aWriter*/, const Brx& /*aUrl*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return false;
}


// ContainerNullBuffered

ContainerNullBuffered::ContainerNullBuffered()
    : ContainerNull()
{
}

Msg* ContainerNullBuffered::ProcessMsg(MsgAudioEncoded* aMsg)
{
    MsgAudioEncoded* msg = nullptr;

    // throw away msg if awaiting a MsgFlush
    if (iExpectedFlushId != MsgFlush::kIdInvalid) {
        aMsg->RemoveRef();
        return nullptr;
    }

    AddToAudioEncoded(aMsg);

    // buffer msgs until we have at least kBufferedAudioBytes
    // so that there is almost always audio in iAudioEncoded during streaming
    if (!iPulling) {
        if ((iAudioEncoded != nullptr) && (iAudioEncoded->Bytes() > kBufferedAudioBytes)) {
            MsgAudioEncoded* remaining = iAudioEncoded->Split(kBufferedAudioBytes/2);
            msg = iAudioEncoded;
            iAudioEncoded = remaining;
        }
    }
    return msg;
}

TUint ContainerNullBuffered::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    TUint64 offset = aOffset + kStartOffsetBytes;
    iExpectedFlushId = iStreamHandler->TrySeek(aStreamId, offset);
    return iExpectedFlushId;
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
        msg = iMsgFactory.CreateMsgMode(Brx::Empty(), true, true, nullptr, false, false);
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
        msg = iMsgFactory.CreateMsgEncodedStream(Brn("http://127.0.0.1:65535"), Brn("metatext"), 0, iPipelineIdProvider.NextStreamId(), false, false, &iStreamHandler);
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
    iContainer = new Container(*iMsgFactory, *iGenerator, *iUrlBlockWriter);
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
    AddTest(MakeFunctor(*this, &SuiteContainerBase::TestEndOfStreamQuit), "TestEndOfStreamQuit");
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

void SuiteContainerBase::TestEndOfStreamQuit()
{
    // Populate vector with normal type/order of stream msgs, ending with a quit.
    // all buffered MsgAudioEncoded should be passed down before the quit
    // (and TryStop/TrySeek/OkToPlay should not be passed up for current stream
    // once a quit has been pulled)
    std::vector<TestContainerMsgGenerator::EMsgType> msgOrder;
    msgOrder.push_back(TestContainerMsgGenerator::EMsgTrack);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgEncodedStream);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgQuit);

    iGenerator->SetMsgOrder(msgOrder);

    while (iMsgRcvdCount < msgOrder.size()) {
        PullAndProcess();
    }

    // OkToPlay/TrySeek should fail after a MsgQuit has been pulled; TryStop should work as before
    EStreamPlay iOkToPlayRes = iContainer->OkToPlay(iStreamId);
    TEST(iOkToPlayRes == ePlayNo);
    TEST(iProvider->OkToPlayCount() == 0);
    TUint iSeekRes = iContainer->TrySeek(iStreamId, 0);
    TEST(iSeekRes == MsgFlush::kIdInvalid);
    TEST(iProvider->SeekCount() == 0);
    TUint iStopRes = iContainer->TryStop(iStreamId);
    TEST(iStopRes != MsgFlush::kIdInvalid);
    TEST(iProvider->StopCount() == 1);
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


// SuiteContainerBuffered

SuiteContainerBuffered::SuiteContainerBuffered()
    : SuiteContainerBase("SuiteContainerBuffered")
{
}

void SuiteContainerBuffered::Setup()
{
    SuiteContainerBase::Setup();
    iContainer->AddContainer(new ContainerNullBuffered());
    iMsgBytesRcvd = 0;
}

TBool SuiteContainerBuffered::TestMsgAudioEncodedContent(MsgAudioEncoded& aMsg, TByte aValue)
{
    // Need to handle buffered msgs that may have been split or chained
    // i.e., msg may contain less, or more than, one distinct msg, so may
    // contain several values. This method keeps a byte counter as it processes
    // msgs to ensure it checks correct portion of msgs.

    Bwh buf(aMsg.Bytes());
    TByte value = aValue;
    //Log::Print("TestMsgAudioEncodedContent: aMsg.Bytes(): %u, buf.MaxBytes(): %u\n", aMsg.Bytes(), buf.MaxBytes());
    ASSERT(aMsg.Bytes() <= buf.MaxBytes());
    aMsg.CopyTo(const_cast<TByte*>(buf.Ptr()));
    buf.SetBytes(aMsg.Bytes());

    TUint bytesToProcess = aMsg.Bytes();
    TUint msgBytesRemaining = EncodedAudio::kMaxBytes - iMsgBytesRcvd;
    TUint lowerBound = 0;
    TUint upperBound = buf.Bytes()-1;
    TUint bytesProcessed = 0;
    while (bytesToProcess > 0) {
        ASSERT(iMsgBytesRcvd < EncodedAudio::kMaxBytes); // iMsgBytesRcvd should ALWAYS be less than max at start of processing
        // determine cut-off, if any
        msgBytesRemaining = EncodedAudio::kMaxBytes - iMsgBytesRcvd;
        upperBound = buf.Bytes()-1;
        if (msgBytesRemaining < aMsg.Bytes()) {
            upperBound = lowerBound + msgBytesRemaining-1;
        }

        // do comparison here; increment iMsgBytesRcvd
        //Log::Print("TestMsgAudioEncodedContent: lowerBound: %u, upperBound: %u, buf[lowerBound]: %d, buf[upperBound]: %d, value: %d\n", lowerBound, upperBound, buf[lowerBound], buf[upperBound], value);
        if ((buf[lowerBound] != value) || (buf[upperBound] != value)) {
            return false;
        }
        bytesProcessed = (upperBound-lowerBound)+1;
        iMsgBytesRcvd += bytesProcessed;
        bytesToProcess -= bytesProcessed;
        lowerBound = upperBound+1;

        ASSERT(iMsgBytesRcvd <= EncodedAudio::kMaxBytes); // implementation error in tests
        if (iMsgBytesRcvd == EncodedAudio::kMaxBytes) {
            iMsgBytesRcvd = 0;
            if (bytesToProcess > 0) {
                iMsgRcvdCount++;
                iAudioRcvdCount++; // only do this if iMsgBytesRcvd has increased to EncodedAudio::kMaxBytes
                value++;
            }
        }
    }

    return true;
}

TBool SuiteContainerBuffered::TestMsgAudioEncodedValue(MsgAudioEncoded& aMsg, TByte aValue)
{
    // Test if a non-audio msg was pulled down the pipeline while audio was
    // being buffered

    if (((iGenerator->LastMsgType() != TestContainerMsgGenerator::EMsgAudioEncoded)
        || (aMsg.Bytes() != EncodedAudio::kMaxBytes))
        && (iGenerator->LastMsgType() != TestContainerMsgGenerator::EMsgTrack)
        && (iGenerator->LastMsgType() != TestContainerMsgGenerator::EMsgEncodedStream)
        && (iGenerator->LastMsgType() != TestContainerMsgGenerator::EMsgQuit)
        )
    {
        return false;
    }
    return TestMsgAudioEncodedContent(aMsg, aValue);
}

TUint SuiteContainerBuffered::ExpectedSeekStartOffset()
{
    return ContainerNullBuffered::kStartOffsetBytes;
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
    iContainer->AddContainer(new Id3v2());
    iContainer->AddContainer(new Mpeg4Container(iMimeTypes));
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

    for (TUint i = 0; i < msgOrder.size(); i++)
    {
        PullAndProcess();
    }
}



void TestContainer()
{
    Runner runner("Container tests\n");
    runner.Add(new SuiteContainerUnbuffered());
    runner.Add(new SuiteContainerBuffered());
    runner.Add(new SuiteContainerNull());
    runner.Run();
}
