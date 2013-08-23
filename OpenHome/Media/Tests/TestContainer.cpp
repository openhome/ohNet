#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/Id3v2.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include "AllocatorInfoLogger.h"
#include <OpenHome/Av/Debug.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

namespace OpenHome {
namespace Media {
namespace Codec {

//class DummyContainerGenerator
//{
//public:
//    DummyContainerGenerator(TUint aHeaderBytes, TUint aFileBytes, TBool aInterleaved = false, TUint aInterleaveCount = 0);
//    ~DummyContainerGenerator();
//    TUint Bytes();
//    void Next(Bwx& aBuf, TUint aBytes);
//    void Next(Bwx& aBuf);
//private:
//    TUint iHeaderBytes;
//    TUint iFileBytes;
//    TUint iSize;
//    TBool iInterleaved;
//    TUint iInterleaveCount;
//    Bwh*  iHeader;
//    Bws<EncodedAudio::kMaxBytes> iData;
//};

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
        ,EMsgTrack
        ,EMsgEncodedStream
        ,EMsgMetaText
        ,EMsgHalt
        ,EMsgFlush
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
    Msg* Pull();
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

//class TestContainerGenerator : public TestContainerMsgGenerator
//{
//public:
//    TestContainerGenerator(DummyContainerGenerator& aGenerator, MsgFactory& aMsgFactory, IFlushIdProvider& aFlushIdProvider, std::vector<EMsgType> aMsgOrder);
//private: // from TestContainerMsgGenerator
//    MsgAudioEncoded* GenerateAudioMsg();
//};

class TestContainerProvider : public IPipelineIdProvider, public IFlushIdProvider, public IStreamHandler
{
public:
    TestContainerProvider();
public: // from IFlushIdProvider
    TUint NextFlushId();
public: // from IPipelineIdProvider
    TUint NextTrackId();
    TUint NextStreamId();
public: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
public:
    TUint OkToPlayCount();
    TUint SeekCount();
    TUint StopCount();
private:
    TUint iFlushId;
    TUint iNextTrackId;
    TUint iNextStreamId;
    TUint iOkToPlayCount;
    TUint iSeekCount;
    TUint iStopCount;
};

class TestContainerMsgProcessor : public IMsgProcessor
{
public: // from IMsgProcessor
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
};

class SuiteContainerBase : public SuiteUnitTest, public TestContainerMsgProcessor
{
public:
    SuiteContainerBase(const TChar* aSuiteName);
    ~SuiteContainerBase();
protected: // from SuiteUnitTest
    virtual void Setup();
    virtual void TearDown();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
protected:
    void PullAndProcess();
private:
    TBool TestMsgAudioEncodedValue(MsgAudioEncoded& aMsg, TByte aValue);
private: // Tests
    void TestNormalOperation();
    void TestMsgOrdering();
    void TestStreamHandling();
    void TestEndOfStreamQuit();
    void TestNewStream();
    void TestFlushPending();
    void TestNullContainer();
private:
    static const TUint kEncodedAudioCount = 100;
    static const TUint kMsgAudioEncodedCount = 100;
    TestContainerProvider* iProvider;
    AllocatorInfoLogger iInfoAggregator;
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    TestContainerMsgGenerator* iGenerator;
    Container* iContainer;
    TUint iTrackId;
    TUint iStreamId;
    TByte iAudioRcvdCount;
};

} // Codec
} // Media
} // OpenHome


// DummyContainerGenerator

//DummyContainerGenerator::DummyContainerGenerator(TUint aHeaderBytes, TUint aFileBytes, TBool aInterleaved, TUint aInterleaveCount)
//    : iHeaderBytes(aHeaderBytes)
//    , iFileBytes(aFileBytes)
//    , iSize(aHeaderBytes + aFileBytes)
//    , iInterleaved(aInterleaved)
//    , iInterleaveCount(aInterleaveCount)
//{
//    if (iInterleaved) {
//        ASSERT(iFileBytes >= iFileBytes/(iHeaderBytes*iInterleaveCount));
//    }
//    iHeader = new Bwh(iHeaderBytes);
//    memset((void*)iHeader->Ptr(), 0, iHeader->MaxBytes());
//    // This should probably be moved to the Next() function for the case of interleaved headers
//    iHeader->Append("dumh");
//    iHeader->Append(aHeaderBytes);
//    iHeader->Append(aFileBytes);
//    iHeader->SetBytes(aHeaderBytes);
//    memset((void*)iData.Ptr(), 0, iData.MaxBytes());
//}
//
//DummyContainerGenerator::~DummyContainerGenerator()
//{
//    delete iHeader;
//}
//
//TUint DummyContainerGenerator::Bytes()
//{
//    return iSize;
//}
//
//void DummyContainerGenerator::Next(Bwx& aBuf, TUint aBytes)
//{
//    iData.SetBytes(iData.MaxBytes());
//
//    aBuf.MaxBytes();
//    aBuf.Bytes();
//    ASSERT(aBuf.MaxBytes()-aBuf.Bytes() >= aBytes);
//    if (iHeader->Bytes() > 0) {
//        if (iHeader->Bytes() > aBytes) {
//            Brn tmp = iHeader->Split(aBytes);
//            aBuf.Append(iHeader->Ptr(), aBytes);
//            aBytes -= iHeader->Bytes();
//            //iFileBytes -= iHeader->Bytes();
//            iHeader->Replace(tmp);
//        }
//        else {
//            aBuf.Append(*iHeader);
//            aBytes -= iHeader->Bytes();
//            //iFileBytes -= iHeader->Bytes();
//            iHeader->SetBytes(0);
//        }
//    }
//
//    if (iFileBytes > 0 && aBytes > 0) {
//        while (iFileBytes > 0 && aBytes > 0) {  // terminate when reached filesize or filled external buf
//            if (iFileBytes >= aBytes) {
//                iData.SetBytes(aBytes);
//                aBuf.Append(iData);
//                aBytes -= iData.Bytes();
//                iFileBytes -= iData.Bytes();
//                iData.SetBytes(iData.MaxBytes());
//            }
//            else {
//                while (iFileBytes > 0) {
//                    if (iFileBytes >= aBytes) {
//                        iData.SetBytes(aBytes);
//                        aBuf.Append(iData);
//                        aBytes -= iData.Bytes();
//                        iFileBytes -= iData.Bytes();
//                        iData.SetBytes(iData.MaxBytes());
//                    }
//                    else {
//                        iData.SetBytes(iFileBytes);
//                        aBuf.Append(iData);
//                        aBytes -= iData.Bytes();
//                        iFileBytes -= iData.Bytes();
//                        iData.SetBytes(iData.MaxBytes());
//                    }
//                }
//            }
//        }
//    }
//}
//
//void DummyContainerGenerator::Next(Bwx& aBuf)
//{
//    Next(aBuf, aBuf.MaxBytes()-aBuf.Bytes());
//}


// TestContainerGenerator

//TestContainerGenerator::TestContainerGenerator(DummyContainerGenerator& aGenerator, MsgFactory& aMsgFactory, IFlushIdProvider& /*aFlushIdProvider*/, Av::IInfoAggregator& aInfoAggregator)
//    : iGenerator(aGenerator)
//    , iMsgFactory(aMsgFactory)
//    , iTrackId(1)
//    , iStreamId(1)
//    , iTrackSent(false)
//    , iStreamSent(false)
//{
//    iTrackFactory = new TrackFactory(aInfoAggregator, 1);
//}
//
//TestContainerGenerator::~TestContainerGenerator()
//{
//    delete iTrackFactory;
//}
//
//TUint TestContainerGenerator::TrackId()
//{
//    return iTrackId;
//}
//
//TUint TestContainerGenerator::StreamId()
//{
//    return iStreamId;
//}
//
//Msg* TestContainerGenerator::Pull()
//{
//    if (!iTrackSent) {
//        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty(), NULL);
//        // send track msg
//        Msg* msg = iMsgFactory.CreateMsgTrack(*track, kPipelineId, Brx::Empty());
//        track->RemoveRef();
//        iTrackSent = true;
//        return msg;
//    }
//    if (!iStreamSent) {
//        Msg* msg = iMsgFactory.CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), iGenerator.Bytes(), NextStreamId(), false, false, NULL);
//        iStreamSent = true;
//        return msg;
//    }
//
//    // sent initialisers; send stream now
//    iData.SetBytes(0);
//    iGenerator.Next(iData);
//    Msg* msg = NULL;
//    if (iData.Bytes()) {
//        msg = iMsgFactory.CreateMsgAudioEncoded(iData);
//    }
//    else {
//        msg = iMsgFactory.CreateMsgQuit();
//    }
//    return msg;
//
//    // send a flush or quit msg?
//}
//
//TUint TestContainerGenerator::NextTrackId()
//{
//    return iTrackId++;
//}
//
//TUint TestContainerGenerator::NextStreamId()
//{
//    return iStreamId++;
//}


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
        Track* track = iTrackFactory.CreateTrack(Brx::Empty(), Brx::Empty(), NULL);
        msg = iMsgFactory.CreateMsgTrack(*track, iPipelineIdProvider.NextTrackId(), Brx::Empty());
        track->RemoveRef();
        }
        iLastMsgType = EMsgTrack;
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
    case EMsgHalt:
        msg = iMsgFactory.CreateMsgHalt();
        iLastMsgType = EMsgHalt;
        break;
    case EMsgFlush:
        msg = iMsgFactory.CreateMsgFlush(iFlushIdProvider.NextFlushId());
        iLastMsgType = EMsgFlush;
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
    : iFlushId(MsgFlush::kIdInvalid+1)
    , iNextTrackId(1)
    , iNextStreamId(1)
    , iOkToPlayCount(0)
    , iSeekCount(0)
    , iStopCount(0)
{
}

TUint TestContainerProvider::NextFlushId()
{
    return iFlushId++;
}

TUint TestContainerProvider::NextTrackId()
{
    return iNextTrackId++;
}

TUint TestContainerProvider::NextStreamId()
{
    return iNextStreamId++;
}

EStreamPlay TestContainerProvider::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    iOkToPlayCount++;
    return ePlayYes;
}

TUint TestContainerProvider::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    iSeekCount++;
    return NextFlushId();
}

TUint TestContainerProvider::TryStop(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    iStopCount++;
    return NextFlushId();
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


// TestContainerMsgProcessor

Msg* TestContainerMsgProcessor::ProcessMsg(MsgAudioEncoded* aMsg)
{
    return aMsg;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return NULL;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return NULL;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return NULL;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with encoded audio at this stage of the pipeline */
    return NULL;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgTrack* aMsg)
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
Msg* TestContainerMsgProcessor::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}
Msg* TestContainerMsgProcessor::ProcessMsg(MsgFlush* aMsg)
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
    AddTest(MakeFunctor(*this, &SuiteContainerBase::TestNormalOperation));
    AddTest(MakeFunctor(*this, &SuiteContainerBase::TestMsgOrdering));
    AddTest(MakeFunctor(*this, &SuiteContainerBase::TestStreamHandling));
    AddTest(MakeFunctor(*this, &SuiteContainerBase::TestEndOfStreamQuit));
    AddTest(MakeFunctor(*this, &SuiteContainerBase::TestNewStream));
    AddTest(MakeFunctor(*this, &SuiteContainerBase::TestFlushPending));
    AddTest(MakeFunctor(*this, &SuiteContainerBase::TestNullContainer));
}

SuiteContainerBase::~SuiteContainerBase()
{
}

void SuiteContainerBase::Setup()
{
    //iGenerator = new DummyContainerGenerator(1234, 12345);

    iProvider = new TestContainerProvider();
    iMsgFactory = new MsgFactory(iInfoAggregator, kEncodedAudioCount, kMsgAudioEncodedCount, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    std::vector<TestContainerMsgGenerator::EMsgType> msgOrder;
    iGenerator = new TestContainerMsgGenerator(*iMsgFactory, *iTrackFactory, *iProvider, *iProvider, *iProvider);
    iContainer = new Container(*iMsgFactory, *iGenerator);
    iTrackId = 0;
    iStreamId = 0;
    iAudioRcvdCount = 0;

    //std::vector<ContainerBase&>::iterator it;
    //for (it = iContainers.begin(); it != iContainers.end(); ++it) {
    //    iContainer->AddContainer(it);
    //}
    //iContainer->AddContainer(new Id3v2());
    //iContainer->AddContainer(new Mpeg4Start());
}

void SuiteContainerBase::TearDown()
{
    delete iContainer;
    delete iGenerator;
    delete iMsgFactory;
    delete iProvider;
}

void SuiteContainerBase::PullAndProcess()
{
    Msg* msg = iContainer->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
}

TBool SuiteContainerBase::TestMsgAudioEncodedValue(MsgAudioEncoded& aMsg, TByte aValue)
{
    if ((iGenerator->LastMsgType() != TestContainerMsgGenerator::EMsgAudioEncoded) || (aMsg.Bytes() != EncodedAudio::kMaxBytes))
    {
        return false;
    }
    Bws<EncodedAudio::kMaxBytes> buf;
    aMsg.CopyTo(const_cast<TByte*>(buf.Ptr()));
    buf.SetBytes(aMsg.Bytes());
    //Log::Print("TestMsgAudioEncodedValue: buf[0]: %d, aValue: %d\n", buf[0], aValue);
    if ((buf[0] != aValue) || (buf[buf.Bytes()-1] != aValue)) {
        return false;
    }
    return true;
}

Msg* SuiteContainerBase::ProcessMsg(MsgAudioEncoded* aMsg)
{
    TBool expected = TestMsgAudioEncodedValue(*aMsg, iAudioRcvdCount);
    TEST(expected);
    iAudioRcvdCount++;
    return aMsg;
}

Msg* SuiteContainerBase::ProcessMsg(MsgTrack* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgTrack);
    iTrackId = aMsg->IdPipeline();
    return aMsg;
}

Msg* SuiteContainerBase::ProcessMsg(MsgEncodedStream* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgEncodedStream);
    iStreamId = aMsg->StreamId();
    return aMsg;
}

Msg* SuiteContainerBase::ProcessMsg(MsgMetaText* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgMetaText);
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

Msg* SuiteContainerBase::ProcessMsg(MsgQuit* aMsg)
{
    TEST(iGenerator->LastMsgType() == TestContainerMsgGenerator::EMsgQuit);
    return aMsg;
}

void SuiteContainerBase::TestNormalOperation()
{
    // populate vector with normal type/order of stream msgs
    std::vector<TestContainerMsgGenerator::EMsgType> msgOrder;
    msgOrder.push_back(TestContainerMsgGenerator::EMsgTrack);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgEncodedStream);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);

    iGenerator->SetMsgOrder(msgOrder);

    for (TUint i = 0; i < msgOrder.size(); i++)
    {
        PullAndProcess();
    }
}

void SuiteContainerBase::TestMsgOrdering()
{
}

void SuiteContainerBase::TestStreamHandling()
{
    // test IStreamHandler calls are successfully passed through while streaming
    std::vector<TestContainerMsgGenerator::EMsgType> msgOrder;
    msgOrder.push_back(TestContainerMsgGenerator::EMsgTrack);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgEncodedStream);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);
    msgOrder.push_back(TestContainerMsgGenerator::EMsgAudioEncoded);

    iGenerator->SetMsgOrder(msgOrder);

    for (TUint i = 0; i < msgOrder.size(); i++)
    {
        PullAndProcess();
    }

    EStreamPlay iOkToPlayRes = iContainer->OkToPlay(iTrackId, iStreamId);
    TEST(iOkToPlayRes == ePlayYes);
    TEST(iProvider->OkToPlayCount() == 1);
    TUint iSeekRes = iContainer->TrySeek(iTrackId, iStreamId, 0);
    TEST(iSeekRes != MsgFlush::kIdInvalid);
    TEST(iProvider->SeekCount() == 1);
    TUint iStopRes = iContainer->TryStop(iTrackId, iStreamId);
    TEST(iStopRes != MsgFlush::kIdInvalid);
    TEST(iProvider->StopCount() == 1);
}

void SuiteContainerBase::TestEndOfStreamQuit()
{
    // populate vector with normal type/order of stream msgs, ending with a quit.
    // all buffered MsgAudioEncoded should be passed down before the quit
    // (and TryStop/TrySeek/OkToPlay should not be passed up for current stream
    // once a quit has been pulled
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

    // OkToPlay/TrySeek/TryStop should all fail after a MsgQuit has been pulled
    EStreamPlay iOkToPlayRes = iContainer->OkToPlay(iTrackId, iStreamId);
    TEST(iOkToPlayRes == ePlayNo);
    TEST(iProvider->OkToPlayCount() == 0);
    TUint iSeekRes = iContainer->TrySeek(iTrackId, iStreamId, 0);
    TEST(iSeekRes == MsgFlush::kIdInvalid);
    TEST(iProvider->SeekCount() == 0);
    TUint iStopRes = iContainer->TryStop(iTrackId, iStreamId);
    TEST(iStopRes == MsgFlush::kIdInvalid);
    TEST(iProvider->StopCount() == 0);
}

void SuiteContainerBase::TestNewStream()
{
}

void SuiteContainerBase::TestFlushPending()
{
}

void SuiteContainerBase::TestNullContainer()
{
    // add some plugins to the container and send a stream through which none
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

    iContainer->AddContainer(new Id3v2());
    iContainer->AddContainer(new Mpeg4Start());

    for (TUint i = 0; i < msgOrder.size(); i++)
    {
        PullAndProcess();
    }
}


//Msg* SuiteContainerBase::ProcessMsg(MsgAudioEncoded* aMsg)
//{
//    //LOG(kMedia, ">SuiteContainerBase::ProcessMsgAudioPcm\n");
//    iBytes += aMsg->Bytes();
//    //LOG(kMedia, "iBytes: %u\n", iBytes);
//    //Log::Print("iBytes: %u\n", iBytes);
//    return aMsg;
//}
//
//Msg* SuiteContainerBase::ProcessMsg(MsgQuit* aMsg)
//{
//    //LOG(kMedia, ">SuiteContainerBase::ProcessMsgQuit\n");
//    iSem.Signal();
//    iQuit = true;
//    return aMsg;
//}
//
//void SuiteContainerBase::TestBytes()
//{
//    this->Start();
//    iSem.Wait();
//    //LOG(kMedia, "iBytes: %u, track bytes: %lu\n", iBytes, iGenerator->Bytes());
//    Log::Print("iBytes: %u, track bytes: %u\n", iBytes, iGenerator->Bytes());
//    TEST(iBytes == iGenerator->Bytes());
//}


void TestContainer()
{
    Log::Print("TestContainer\n");

    Runner runner("Container tests\n");
    runner.Add(new SuiteContainerBase("SuiteContainerBase"));
    //runner.Add(new SuiteContainerNoHeader());
    //runner.Add(new SuiteContainerUnidentifiedHeader());
    //runner.Add(new SuiteContainerHeader());
    //runner.Add(new SuiteContainerNoHeaderInterleaved());
    //runner.Add(new SuiteContainerHeaderInterleaved());
    runner.Run();
}
