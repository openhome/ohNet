#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/TrackInspector.h>
#include <OpenHome/Media/Msg.h>
#include "AllocatorInfoLogger.h"
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Functor.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteTrackInspector : public SuiteUnitTest, private ITrackObserver, private IPipelineElementUpstream
{
public:
    SuiteTrackInspector();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    enum EMsgType
    {
        ENone
       ,EMsgAudioPcm
       ,EMsgDecodedStream
       ,EMsgTrack
       ,EMsgHalt
       ,EMsgWait
       ,EMsgFlush
       ,EMsgQuit
    };
private:
    void Pull(EMsgType aGenerateType);
    void DoPull();
    void TrackNonLiveStreamAudioReportsPlay();
    void TrackLiveStreamAudioReportsPlay();
    void TrackFlushReportsNothing();
    void TrackNonLiveStreamFlushReportsNothing();
    void TrackFlushTrackReportsNothing();
    void TrackLiveStreamFlushReportsPlay();
    void TrackTrackReportsFail();
    void TrackHaltTrackReportsFail();
    void TrackTrackReportsFailNonLiveStreamAudioReportsPlay();
    void TrackLiveStreamReportsPlayTrackTrackReportsFail();
    void TrackLiveStreamReportsPlayTrackFlushReportsNothing();
    void TrackLiveStreamReportsPlayWaitReportsNothing();
    void TwoObserversNotified();
private: // from ITrackObserver
    void NotifyTrackPlay(Track& aTrack);
    void NotifyTrackFail(Track& aTrack);
private: // from IPipelineElementUpstream
    Msg* Pull();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    TrackInspector* iTrackInspector;
    TUint iPlayCount;
    TUint iFailCount;
    Track* iLastNotifiedTrack;
    EMsgType iNextGeneratedMsg;
    TUint iNextTrackId;
    TBool iLiveStream;
    std::vector<TUint> iTrackIds;
    std::vector<EMsgType> iPendingMsgs;
};

} // namespace Media
} // namespace OpenHome

// SuiteTrackInspector

SuiteTrackInspector::SuiteTrackInspector()
    : SuiteUnitTest("TrackInspector tests")
{
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackNonLiveStreamAudioReportsPlay), "TrackNonLiveStreamAudioReportsPlay");
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackLiveStreamAudioReportsPlay), "TrackLiveStreamAudioReportsPlay");
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackFlushReportsNothing), "TrackFlushReportsNothing");
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackNonLiveStreamFlushReportsNothing), "TrackNonLiveStreamFlushReportsNothing");
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackFlushTrackReportsNothing), "TrackFlushTrackReportsNothing");
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackLiveStreamFlushReportsPlay), "TrackLiveStreamFlushReportsPlay");
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackTrackReportsFail), "TrackTrackReportsFail");
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackHaltTrackReportsFail), "TrackHaltTrackReportsFail");
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackTrackReportsFailNonLiveStreamAudioReportsPlay), "TrackTrackReportsFailNonLiveStreamAudioReportsPlay");
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackLiveStreamReportsPlayTrackTrackReportsFail), "TrackLiveStreamReportsPlayTrackTrackReportsFail");
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackLiveStreamReportsPlayTrackFlushReportsNothing), "TrackLiveStreamReportsPlayTrackFlushReportsNothing");
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TwoObserversNotified), "TwoObserversNotified");
}

void SuiteTrackInspector::Setup()
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1);
    iTrackFactory = new TrackFactory(iInfoAggregator, 3);
    iTrackInspector = new TrackInspector(*this);
    iTrackInspector->AddObserver(*this);
    iPlayCount = 0;
    iFailCount = 0;
    iLastNotifiedTrack = NULL;
    iNextTrackId = 0;
    iLiveStream = false;
    iTrackIds.clear();
}

void SuiteTrackInspector::TearDown()
{
    if (iLastNotifiedTrack != NULL) {
        iLastNotifiedTrack->RemoveRef();
    }
    delete iTrackInspector;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteTrackInspector::Pull(EMsgType aGenerateType)
{
    iNextGeneratedMsg = aGenerateType;
    Msg* msg = iTrackInspector->Pull();
    msg->RemoveRef();
}

void SuiteTrackInspector::DoPull()
{
    iTrackInspector->Pull()->RemoveRef();
}

#define NUM_EMEMS(arr) sizeof(arr) / sizeof(arr[0])

void SuiteTrackInspector::TrackNonLiveStreamAudioReportsPlay()
{
    EMsgType msgs[] = { EMsgTrack, EMsgDecodedStream, EMsgAudioPcm, EMsgAudioPcm };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    DoPull();
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
    TEST(iPendingMsgs.size() == 1);
    // also check that subsequent audio doesn't increase number of notifications
    while (iPendingMsgs.size() > 0) {
        DoPull();
        TEST(iPlayCount == 1);
        TEST(iFailCount == 0);
    }
}

void SuiteTrackInspector::TrackLiveStreamAudioReportsPlay()
{
    EMsgType msgs[] = { EMsgTrack, EMsgDecodedStream, EMsgQuit };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    iLiveStream = true;

    DoPull();
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
    TEST(iPendingMsgs.size() == 0);
}

void SuiteTrackInspector::TrackFlushReportsNothing()
{
    EMsgType msgs[] = { EMsgTrack, EMsgFlush, EMsgQuit };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    DoPull();
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    TEST(iPendingMsgs.size() == 0);
}

void SuiteTrackInspector::TrackNonLiveStreamFlushReportsNothing()
{
    EMsgType msgs[] = { EMsgTrack, EMsgDecodedStream, EMsgFlush, EMsgQuit };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    DoPull();
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    TEST(iPendingMsgs.size() == 0);
}

void SuiteTrackInspector::TrackFlushTrackReportsNothing()
{
    EMsgType msgs[] = { EMsgTrack, EMsgFlush, EMsgTrack, EMsgQuit };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    DoPull();
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    TEST(iPendingMsgs.size() == 0);
}

void SuiteTrackInspector::TrackLiveStreamFlushReportsPlay()
{
    EMsgType msgs[] = { EMsgTrack, EMsgDecodedStream, EMsgFlush, EMsgQuit };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    iLiveStream = true;
    DoPull();
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
    TEST(iPendingMsgs.size() == 0);
}

void SuiteTrackInspector::TrackTrackReportsFail()
{
    EMsgType msgs[] = { EMsgTrack, EMsgTrack, EMsgQuit };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    DoPull();
    TEST(iPlayCount == 0);
    TEST(iFailCount == 1);
    TEST(iPendingMsgs.size() == 0);
    // confirm that first track is the one that failed
    TEST(iLastNotifiedTrack->Id() == iTrackIds[0]);
}

void SuiteTrackInspector::TrackHaltTrackReportsFail()
{
    EMsgType msgs[] = { EMsgTrack, EMsgHalt, EMsgTrack, EMsgQuit };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    DoPull();
    TEST(iPlayCount == 0);
    TEST(iFailCount == 1);
    TEST(iPendingMsgs.size() == 0);
    TEST(iLastNotifiedTrack->Id() == iTrackIds[0]);
}

void SuiteTrackInspector::TrackTrackReportsFailNonLiveStreamAudioReportsPlay()
{
    EMsgType msgs[] = { EMsgTrack, EMsgTrack, EMsgDecodedStream, EMsgAudioPcm };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    DoPull();
    TEST(iPlayCount == 1);
    TEST(iFailCount == 1);
    TEST(iPendingMsgs.size() == 0);
    TEST(iLastNotifiedTrack->Id() == iTrackIds[1]);
}

void SuiteTrackInspector::TrackLiveStreamReportsPlayTrackTrackReportsFail()
{
    EMsgType msgs[] = { EMsgTrack, EMsgDecodedStream, EMsgTrack, EMsgTrack, EMsgQuit };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    iLiveStream = true;
    DoPull();
    TEST(iPlayCount == 1);
    TEST(iFailCount == 1);
    TEST(iPendingMsgs.size() == 0);
    TEST(iLastNotifiedTrack->Id() == iTrackIds[1]);
}

void SuiteTrackInspector::TrackLiveStreamReportsPlayTrackFlushReportsNothing()
{
    EMsgType msgs[] = { EMsgTrack, EMsgDecodedStream, EMsgTrack, EMsgFlush, EMsgQuit };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    iLiveStream = true;
    DoPull();
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
    TEST(iPendingMsgs.size() == 0);
    TEST(iLastNotifiedTrack->Id() == iTrackIds[0]);
}

void SuiteTrackInspector::TrackLiveStreamReportsPlayWaitReportsNothing()
{
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    iLiveStream = true;
    Pull(EMsgDecodedStream);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
    Pull(EMsgAudioPcm);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
    // check that MsgWait doesn't increase number of notifications
    Pull(EMsgWait);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
    Pull(EMsgAudioPcm);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
}

void SuiteTrackInspector::TwoObserversNotified()
{
    iTrackInspector->AddObserver(*this);
    EMsgType msgs[] = { EMsgTrack, EMsgDecodedStream, EMsgQuit };
    iPendingMsgs.assign(msgs, msgs+NUM_EMEMS(msgs));
    iLiveStream = true;
    DoPull();
    TEST(iPlayCount == 2);
    TEST(iFailCount == 0);
    TEST(iPendingMsgs.size() == 0);
}

void SuiteTrackInspector::NotifyTrackPlay(Track& aTrack)
{
    iPlayCount++;
    if (iLastNotifiedTrack != NULL) {
        iLastNotifiedTrack->RemoveRef();
    }
    iLastNotifiedTrack = &aTrack;
    iLastNotifiedTrack->AddRef();
}

void SuiteTrackInspector::NotifyTrackFail(Track& aTrack)
{
    iFailCount++;
    if (iLastNotifiedTrack != NULL) {
        iLastNotifiedTrack->RemoveRef();
    }
    iLastNotifiedTrack = &aTrack;
    iLastNotifiedTrack->AddRef();
}

Msg* SuiteTrackInspector::Pull()
{
    static const TUint kStreamId      = 0;
    static const TUint kBitDepth      = 24;
    static const TUint kSampleRate    = 44100;
    static const TUint kBitRate       = kBitDepth * kSampleRate;
    static const TUint64 kTrackLength = Jiffies::kJiffiesPerSecond * 60;
    static const TBool kLossless      = true;
    static const TBool kSeekable      = false;
    static const TUint kNumChannels   = 2;
    static TUint64 iTrackOffset = 0;

    EMsgType msgType = iPendingMsgs[0];
    iPendingMsgs.erase(iPendingMsgs.begin());
    switch (msgType)
    {
    case EMsgAudioPcm:
    {
        static const TUint kDataBytes = 3 * 1024;
        TByte encodedAudioData[kDataBytes];
        (void)memset(encodedAudioData, 0xff, kDataBytes);
        Brn encodedAudioBuf(encodedAudioData, kDataBytes);
        MsgAudio* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 16, EMediaDataLittleEndian, iTrackOffset);
        iTrackOffset += audio->Jiffies();
        return audio;
    }
    case EMsgDecodedStream:
    {
        return iMsgFactory->CreateMsgDecodedStream(kStreamId, kBitRate, kBitDepth, kSampleRate, kNumChannels, Brn("Dummy codec"), kTrackLength, 0, kLossless, kSeekable, iLiveStream);
    }
    case EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty(), NULL, false);
        Msg* msg = iMsgFactory->CreateMsgTrack(*track, iNextTrackId, Brx::Empty());
        iTrackIds.push_back(track->Id());
        track->RemoveRef();
        iNextTrackId++;
        return msg;
    }
    case EMsgHalt:
        return iMsgFactory->CreateMsgHalt();
    case EMsgFlush:
        return iMsgFactory->CreateMsgFlush(1);
    case EMsgWait:
        return iMsgFactory->CreateMsgWait();
    case EMsgQuit:
        return iMsgFactory->CreateMsgQuit();
    default:
        ASSERTS();
        return NULL;
    }
}



void TestTrackInspector()
{
    Runner runner("TrackInspector tests\n");
    runner.Add(new SuiteTrackInspector());
    runner.Run();
}
