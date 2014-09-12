#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/Seeker.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>

#include <list>
#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteSeeker : public SuiteUnitTest, private IPipelineElementUpstream, private ISeeker, private IStreamHandler, private IMsgProcessor
{
    static const TUint kRampDuration = Jiffies::kPerMs * 20;
    static const TUint kExpectedFlushId = 5;
    static const TUint kExpectedSeekSeconds = 51;
    static const TUint kSampleRate = 44100;
    static const TUint kNumChannels = 2;
public:
    SuiteSeeker();
    ~SuiteSeeker();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private: // from IPipelineElementUpstream
    Msg* Pull();
private: // from ISeeker
    void StartSeek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute, ISeekObserver& aObserver, TUint& aHandle);
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
    TBool TryGet(IWriter& aWriter, TUint aTrackId, TUint aStreamId, TUint64 aOffset, TUint aBytes);
    void NotifyStarving(const Brx& aMode, TUint aTrackId, TUint aStreamId);
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg);
    Msg* ProcessMsg(MsgSession* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgDelay* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgWait* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    enum EMsgType
    {
        ENone
       ,EMsgMode
       ,EMsgSession
       ,EMsgTrack
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgDecodedStream
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgQuit
    };
private:
    void PullNext();
    void PullNext(EMsgType aExpectedMsg);
    Msg* CreateTrack();
    Msg* CreateEncodedStream();
    Msg* CreateDecodedStream();
    Msg* CreateAudio();
    void SeekResponseThread();
    void TestAllMsgsPassWhileNotSeeking();
    void TestRampInvalidTrackId();
    void TestRampInvalidStreamId();
    void TestRampNonSeekableStream();
    //void TestRampSeekerRejects();
    void TestRampSeekerAccepts();
    //void TestNoRampSeekerRejects();
    void TestNoRampSeekerAccepts();
    void TestNewTrackCancelsRampDownAndSeek();
    void TestNewTrackCancelsRampUp();
    void TestOverlappingSeekIgnored();
    void TestSeekForwardFailStillSeeks();
private:
    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    MsgFactory* iMsgFactory;
    Seeker* iSeeker;
    EMsgType iLastPulledMsg;
    TBool iRampingDown;
    TBool iRampingUp;
    TBool iSeekable;
    TBool iGenerateAudio;
    TUint iTrackId;
    TUint iStreamId;
    TUint iMsgAudioSize;
    TUint64 iTrackOffset;
    TUint64 iJiffies;
    std::list<Msg*> iPendingMsgs;
    TUint iLastSubsample;
    TUint iNextTrackId;
    TUint iNextStreamId;
    ISeekObserver* iSeekObserver;
    TUint iSeekHandle;
    Semaphore iSeekerResponse;
    TUint iNextSeekResponse;
    TUint iSeekSeconds;
    ThreadFunctor* iSeekResponseThread;
};

} // namespace Media
} // namespace OpenHome


SuiteSeeker::SuiteSeeker()
    : SuiteUnitTest("Seeker")
    , iSeekerResponse("TSEK", 0)
{
    AddTest(MakeFunctor(*this, &SuiteSeeker::TestAllMsgsPassWhileNotSeeking), "TestAllMsgsPassWhileNotSeeking");
    AddTest(MakeFunctor(*this, &SuiteSeeker::TestRampInvalidTrackId), "TestRampInvalidTrackId");
    AddTest(MakeFunctor(*this, &SuiteSeeker::TestRampInvalidStreamId), "TestRampInvalidStreamId");
    AddTest(MakeFunctor(*this, &SuiteSeeker::TestRampNonSeekableStream), "TestRampNonSeekableStream");
    /* All seeks ramp down and may flush for a short while before being informed that the ISeeker failed to seek.
       It isn't easy to test for this without a moderate amount of change.
       Testing that a new track cancels a seek already covers behaviour for the most likely cause of seek failure. */
    //AddTest(MakeFunctor(*this, &SuiteSeeker::TestRampSeekerRejects), "TestRampSeekerRejects");
    AddTest(MakeFunctor(*this, &SuiteSeeker::TestRampSeekerAccepts), "TestRampSeekerAccepts");
    //AddTest(MakeFunctor(*this, &SuiteSeeker::TestNoRampSeekerRejects), "TestNoRampSeekerRejects");
    AddTest(MakeFunctor(*this, &SuiteSeeker::TestNoRampSeekerAccepts), "TestNoRampSeekerAccepts");
    AddTest(MakeFunctor(*this, &SuiteSeeker::TestNewTrackCancelsRampDownAndSeek), "TestNewTrackCancelsRampDownAndSeek");
    AddTest(MakeFunctor(*this, &SuiteSeeker::TestNewTrackCancelsRampUp), "TestNewTrackCancelsRampUp");
    AddTest(MakeFunctor(*this, &SuiteSeeker::TestOverlappingSeekIgnored), "TestOverlappingSeekIgnored");
    AddTest(MakeFunctor(*this, &SuiteSeeker::TestSeekForwardFailStillSeeks), "TestSeekForwardFailStillSeeks");
}

SuiteSeeker::~SuiteSeeker()
{
}

void SuiteSeeker::Setup()
{
    iTrackFactory = new TrackFactory(iInfoAggregator, 5);
    iMsgFactory = new MsgFactory(iInfoAggregator, 0, 0, 5, 5, 10, 1, 0, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1);
    iSeeker = new Seeker(*iMsgFactory, *this, *this, kRampDuration);
    iSeekResponseThread = new ThreadFunctor("SeekResponse", MakeFunctor(*this, &SuiteSeeker::SeekResponseThread));
    iSeekResponseThread->Start();
    iTrackId = iStreamId = UINT_MAX;
    iMsgAudioSize = 0;
    iTrackOffset = 0;
    iRampingDown = iRampingUp = false;
    iSeekable = true;
    iGenerateAudio = false;
    iLastSubsample = 0xffffff;
    iNextTrackId = 1;
    iNextStreamId = 1;
    iJiffies = 0;
    iSeekObserver = NULL;
    iSeekHandle = 0;
    iSeekerResponse.Clear();
    iNextSeekResponse = MsgFlush::kIdInvalid;
    iSeekSeconds = UINT_MAX;
}

void SuiteSeeker::TearDown()
{
    while (iPendingMsgs.size() > 0) {
        iPendingMsgs.front()->RemoveRef();
        iPendingMsgs.pop_front();
    }
    delete iSeekResponseThread;
    delete iSeeker;
    delete iMsgFactory;
    delete iTrackFactory;
}

Msg* SuiteSeeker::Pull()
{
    if (iGenerateAudio) {
        return CreateAudio();
    }
    ASSERT(iPendingMsgs.size() > 0);
    Msg* msg = iPendingMsgs.front();
    iPendingMsgs.pop_front();
    return msg;
}

EStreamPlay SuiteSeeker::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS();
    return ePlayNo;
}

void SuiteSeeker::StartSeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint aSecondsAbsolute, ISeekObserver& aObserver, TUint& aHandle)
{
    iSeekSeconds = aSecondsAbsolute;
    iSeekObserver = &aObserver;
    aHandle = ++iSeekHandle;
    iSeekResponseThread->Signal();
}

TUint SuiteSeeker::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteSeeker::TryStop(TUint aTrackId, TUint aStreamId)
{
    if (aTrackId == iTrackId && aStreamId == iStreamId) {
        return kExpectedFlushId;
    }
    return MsgFlush::kIdInvalid;
}

TBool SuiteSeeker::TryGet(IWriter& /*aWriter*/, TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    ASSERTS();
    return false;
}

void SuiteSeeker::NotifyStarving(const Brx& /*aMode*/, TUint /*aTrackId*/, TUint /*aStreamId*/)
{
}

Msg* SuiteSeeker::ProcessMsg(MsgMode* aMsg)
{
    iLastPulledMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteSeeker::ProcessMsg(MsgSession* aMsg)
{
    iLastPulledMsg = EMsgSession;
    return aMsg;
}

Msg* SuiteSeeker::ProcessMsg(MsgTrack* aMsg)
{
    iLastPulledMsg = EMsgTrack;
    iTrackId = aMsg->IdPipeline();
    return aMsg;
}

Msg* SuiteSeeker::ProcessMsg(MsgDelay* aMsg)
{
    iLastPulledMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteSeeker::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastPulledMsg = EMsgEncodedStream;
    iStreamId = aMsg->StreamId();
    return aMsg;
}

Msg* SuiteSeeker::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuiteSeeker::ProcessMsg(MsgMetaText* aMsg)
{
    iLastPulledMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteSeeker::ProcessMsg(MsgHalt* aMsg)
{
    iLastPulledMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteSeeker::ProcessMsg(MsgFlush* aMsg)
{
    iLastPulledMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteSeeker::ProcessMsg(MsgWait* aMsg)
{
    iLastPulledMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteSeeker::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastPulledMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteSeeker::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastPulledMsg = EMsgAudioPcm;
    iJiffies += aMsg->Jiffies();
    MsgPlayable* playable = aMsg->CreatePlayable();
    ProcessorPcmBufPacked pcmProcessor;
    playable->Read(pcmProcessor);
    Brn buf(pcmProcessor.Buf());
    ASSERT(buf.Bytes() >= 6);
    const TByte* ptr = buf.Ptr();
    const TUint bytes = buf.Bytes();
    const TUint firstSubsample = (ptr[0]<<16) | (ptr[1]<<8) | ptr[2];

    if (iRampingDown) {
        ASSERT(!iRampingUp);
    }
    
    if (iRampingDown) {
        TEST(firstSubsample <= iLastSubsample);
    }
    else if (iRampingUp) {
        TEST(firstSubsample >= iLastSubsample);
    }
    else {
        TEST(firstSubsample == 0x7f7f7f);
    }
    iLastSubsample = (ptr[bytes-3]<<16) | (ptr[bytes-2]<<8) | ptr[bytes-1];
    if (iRampingDown) {
        TEST(iLastSubsample < firstSubsample);
        iRampingDown = (iLastSubsample > 0);
    }
    else if (iRampingUp) {
        TEST(iLastSubsample > firstSubsample);
        iRampingUp = (iLastSubsample < 0x7f7f7e); // FIXME - see #830
    }
    else {
        TEST(firstSubsample == 0x7f7f7f);
    }

    return playable;
}

Msg* SuiteSeeker::ProcessMsg(MsgSilence* aMsg)
{
    iLastPulledMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteSeeker::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuiteSeeker::ProcessMsg(MsgQuit* aMsg)
{
    iLastPulledMsg = EMsgQuit;
    return aMsg;
}

void SuiteSeeker::PullNext()
{
    Msg* msg = iSeeker->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
}

void SuiteSeeker::PullNext(EMsgType aExpectedMsg)
{
    Msg* msg = iSeeker->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
    TEST(iLastPulledMsg == aExpectedMsg);
}

Msg* SuiteSeeker::CreateTrack()
{
    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    Msg* msg = iMsgFactory->CreateMsgTrack(*track, iNextTrackId++);
    track->RemoveRef();
    return msg;
}

Msg* SuiteSeeker::CreateEncodedStream()
{
    return iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 1<<21, ++iNextStreamId, iSeekable, false, this);
}

Msg* SuiteSeeker::CreateDecodedStream()
{
    return iMsgFactory->CreateMsgDecodedStream(iNextStreamId, 100, 24, kSampleRate, kNumChannels, Brn("notARealCodec"), 1LL<<38, 0, true, iSeekable, false, NULL);
}

Msg* SuiteSeeker::CreateAudio()
{
    static const TUint kDataBytes = 960;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0x7f, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 24, EMediaDataLittleEndian, iTrackOffset);
    iMsgAudioSize = audio->Jiffies();
    iTrackOffset += audio->Jiffies();
    return audio;
}

void SuiteSeeker::SeekResponseThread()
{
    iSeekResponseThread->Wait();
    iSeekObserver->NotifySeekComplete(iSeekHandle, iNextSeekResponse);
    iSeekerResponse.Signal();
}

void SuiteSeeker::TestAllMsgsPassWhileNotSeeking()
{
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(Brx::Empty(), false, true, NULL));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSession());
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgDelay(0));
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(CreateAudio());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSilence(Jiffies::kPerMs * 3));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(2));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    iPendingMsgs.push_back(CreateTrack());

    PullNext(EMsgMode);
    PullNext(EMsgSession);
    PullNext(EMsgTrack);
    PullNext(EMsgDelay);
    PullNext(EMsgEncodedStream);
    PullNext(EMsgMetaText);
    PullNext(EMsgDecodedStream);
    PullNext(EMsgAudioPcm);
    PullNext(EMsgSilence);
    PullNext(EMsgHalt);
    PullNext(EMsgFlush);
    PullNext(EMsgWait);
    PullNext(EMsgQuit);
    PullNext(EMsgTrack);
}

void SuiteSeeker::TestRampInvalidTrackId()
{
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(CreateAudio());
    for (TUint i=0; i<4; i++) {
        PullNext();
    }
    TEST(iLastPulledMsg == EMsgAudioPcm);

    TEST(!iSeeker->Seek(iTrackId+1, iStreamId, kExpectedSeekSeconds, true));
    iPendingMsgs.push_back(CreateAudio());
    TEST(iLastPulledMsg == EMsgAudioPcm);
}

void SuiteSeeker::TestRampInvalidStreamId()
{
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(CreateAudio());
    for (TUint i=0; i<4; i++) {
        PullNext();
    }
    TEST(iLastPulledMsg == EMsgAudioPcm);

    TEST(!iSeeker->Seek(iTrackId, iStreamId+1, kExpectedSeekSeconds, true));
    iPendingMsgs.push_back(CreateAudio());
    TEST(iLastPulledMsg == EMsgAudioPcm);
}

void SuiteSeeker::TestRampNonSeekableStream()
{
    iPendingMsgs.push_back(CreateTrack());
    iSeekable = false;
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(CreateAudio());
    for (TUint i=0; i<4; i++) {
        PullNext();
    }
    TEST(iLastPulledMsg == EMsgAudioPcm);

    TEST(!iSeeker->Seek(iTrackId, iStreamId+1, kExpectedSeekSeconds, true));
    iPendingMsgs.push_back(CreateAudio());
    TEST(iLastPulledMsg == EMsgAudioPcm);
}

void SuiteSeeker::TestRampSeekerAccepts()
{
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(CreateAudio());
    for (TUint i=0; i<4; i++) {
        PullNext();
    }

    iNextSeekResponse = kExpectedFlushId;
    TEST(iSeeker->Seek(iTrackId, iStreamId, kExpectedSeekSeconds, true));
    iRampingDown = true;
    iJiffies = 0;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
    PullNext(EMsgHalt);
    // no audio retained from end-of-ramp
    TEST(iSeeker->iQueue.IsEmpty());
    iSeekerResponse.Wait();

    // very few msg types get through while we're flushing
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    iPendingMsgs.push_back(CreateAudio());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSilence(Jiffies::kPerMs * 3));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(2));
    PullNext(EMsgFlush);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    PullNext(EMsgWait);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);

    // end of seek Flush is consumed
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(kExpectedFlushId));
    TEST(iSeeker->iQueue.IsEmpty());
    // ramping up now
    iRampingUp = true;
    iJiffies = 0;

    // non-audio msgs are passed through
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    PullNext(EMsgMetaText);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(2));
    PullNext(EMsgFlush);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    PullNext(EMsgWait);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);

    // audio is immediately ramped up
    while (iRampingUp) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
}

void SuiteSeeker::TestNoRampSeekerAccepts()
{
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(CreateAudio());
    for (TUint i=0; i<4; i++) {
        PullNext();
    }

    iNextSeekResponse = kExpectedFlushId;
    TEST(iSeeker->Seek(iTrackId, iStreamId, kExpectedSeekSeconds, false));
    PullNext(EMsgHalt);
    // no audio retained from end-of-ramp
    TEST(iSeeker->iQueue.IsEmpty());
    iSeekerResponse.Wait();

    // very few msg types get through while we're flushing
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    iPendingMsgs.push_back(CreateAudio());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSilence(Jiffies::kPerMs * 3));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(2));
    PullNext(EMsgFlush);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    PullNext(EMsgWait);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);

    // end of seek Flush is consumed
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(kExpectedFlushId));
    TEST(iSeeker->iQueue.IsEmpty());
    // ramping up now
    iRampingUp = true;
    iJiffies = 0;

    // non-audio msgs are passed through
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    PullNext(EMsgMetaText);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(2));
    PullNext(EMsgFlush);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    PullNext(EMsgWait);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);

    // audio is immediately ramped up
    iLastSubsample = 0;
    while (iRampingUp) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
}

void SuiteSeeker::TestNewTrackCancelsRampDownAndSeek()
{
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(CreateAudio());
    for (TUint i=0; i<4; i++) {
        PullNext();
    }

    iNextSeekResponse = kExpectedFlushId;
    TEST(iSeeker->Seek(iTrackId, iStreamId, kExpectedSeekSeconds, true));
    iRampingDown = true;
    if (iSeeker->iQueue.IsEmpty()) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    else {
        while (!iSeeker->iQueue.IsEmpty()) {
            PullNext(EMsgAudioPcm);
        }
    }
    TEST(iRampingDown);

    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iRampingDown = false;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    for (TUint i=0; i<20; i++) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iSeekSeconds == UINT_MAX); // i.e. TrySeek has not been called
}

void SuiteSeeker::TestNewTrackCancelsRampUp()
{
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(CreateAudio());
    for (TUint i=0; i<4; i++) {
        PullNext();
    }

    iNextSeekResponse = kExpectedFlushId;
    TEST(iSeeker->Seek(iTrackId, iStreamId, kExpectedSeekSeconds, false));
    iSeekerResponse.Wait();
    PullNext(EMsgHalt);
    iRampingUp = true;
    iLastSubsample = 0;
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(kExpectedFlushId));
    TEST(iSeeker->iQueue.IsEmpty());
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    TEST(iRampingUp);
}

void SuiteSeeker::TestOverlappingSeekIgnored()
{
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(CreateAudio());
    for (TUint i=0; i<4; i++) {
        PullNext();
    }

    iNextSeekResponse = kExpectedFlushId;
    TEST(iSeeker->Seek(iTrackId, iStreamId, kExpectedSeekSeconds, true));
    TEST(iSeekSeconds != kExpectedSeekSeconds);
    iRampingDown = true;
    TEST(!iSeeker->Seek(iTrackId, iStreamId, kExpectedSeekSeconds+10, true));
    TEST(iSeekSeconds != kExpectedSeekSeconds);
    iJiffies = 0;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iSeekSeconds == kExpectedSeekSeconds);
}

void SuiteSeeker::TestSeekForwardFailStillSeeks()
{
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(CreateAudio());
    for (TUint i=0; i<4; i++) {
        PullNext();
    }

    iNextSeekResponse = MsgFlush::kIdInvalid;
    static const TUint kSeekSecs = 5;
    TEST(iSeeker->Seek(iTrackId, iStreamId, kSeekSecs, true));
    iRampingDown = true;
    iJiffies = 0;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iSeeker->iState == Seeker::EFlushing);
    PullNext(EMsgHalt);
    iGenerateAudio = true;
    iRampingUp = true; // not true yet but will be for the next msg we pull
    PullNext(EMsgAudioPcm);
    TEST(iTrackOffset >= kSeekSecs * Jiffies::kPerSecond);
    TEST(iTrackOffset < (kSeekSecs * Jiffies::kPerSecond) + iMsgAudioSize);
}


void TestSeeker()
{
    Runner runner("Seeker tests\n");
    runner.Add(new SuiteSeeker());
    runner.Run();
}
