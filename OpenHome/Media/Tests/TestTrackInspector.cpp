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
       ,EMsgFlush
    };
private:
    void Pull(EMsgType aGenerateType);
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
};

} // namespace Media
} // namespace OpenHome

// SuiteTrackInspector

SuiteTrackInspector::SuiteTrackInspector()
    : SuiteUnitTest("TrackInspector tests")
{
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackNonLiveStreamAudioReportsPlay));
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackLiveStreamAudioReportsPlay));
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackFlushReportsNothing));
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackNonLiveStreamFlushReportsNothing));
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackFlushTrackReportsNothing));
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackLiveStreamFlushReportsPlay));
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackTrackReportsFail));
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackHaltTrackReportsFail));
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackTrackReportsFailNonLiveStreamAudioReportsPlay));
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackLiveStreamReportsPlayTrackTrackReportsFail));
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TrackLiveStreamReportsPlayTrackFlushReportsNothing));
    AddTest(MakeFunctor(*this, &SuiteTrackInspector::TwoObserversNotified));
}

void SuiteTrackInspector::Setup()
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
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

void SuiteTrackInspector::TrackNonLiveStreamAudioReportsPlay()
{
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    Pull(EMsgDecodedStream);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    Pull(EMsgAudioPcm);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
    // also check that subsequent audio doesn't increase number of notifications
    Pull(EMsgAudioPcm);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
}

void SuiteTrackInspector::TrackLiveStreamAudioReportsPlay()
{
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    iLiveStream = true;
    Pull(EMsgDecodedStream);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
    // also check that subsequent audio doesn't increase number of notifications
    Pull(EMsgAudioPcm);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
}

void SuiteTrackInspector::TrackFlushReportsNothing()
{
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    Pull(EMsgFlush);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
}

void SuiteTrackInspector::TrackNonLiveStreamFlushReportsNothing()
{
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    Pull(EMsgDecodedStream);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    Pull(EMsgFlush);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
}

void SuiteTrackInspector::TrackFlushTrackReportsNothing()
{
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    Pull(EMsgFlush);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
}

void SuiteTrackInspector::TrackLiveStreamFlushReportsPlay()
{
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    iLiveStream = true;
    Pull(EMsgDecodedStream);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
    Pull(EMsgFlush);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
}

void SuiteTrackInspector::TrackTrackReportsFail()
{
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 1);
    // confirm that first track is the one that failed
    TEST(iLastNotifiedTrack->Id() == iTrackIds[0]);
}

void SuiteTrackInspector::TrackHaltTrackReportsFail()
{
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    Pull(EMsgHalt);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 1);
    TEST(iLastNotifiedTrack->Id() == iTrackIds[0]);
}

void SuiteTrackInspector::TrackTrackReportsFailNonLiveStreamAudioReportsPlay()
{
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 1);
    TEST(iLastNotifiedTrack->Id() == iTrackIds[0]);
    Pull(EMsgDecodedStream);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 1);
    Pull(EMsgAudioPcm);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 1);
    TEST(iLastNotifiedTrack->Id() == iTrackIds[1]);
}

void SuiteTrackInspector::TrackLiveStreamReportsPlayTrackTrackReportsFail()
{
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    iLiveStream = true;
    Pull(EMsgDecodedStream);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
    Pull(EMsgTrack);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
    Pull(EMsgTrack);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 1);
    TEST(iLastNotifiedTrack->Id() == iTrackIds[1]);
}

void SuiteTrackInspector::TrackLiveStreamReportsPlayTrackFlushReportsNothing()
{
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    iLiveStream = true;
    Pull(EMsgDecodedStream);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
    Pull(EMsgTrack);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
    Pull(EMsgFlush);
    TEST(iPlayCount == 1);
    TEST(iFailCount == 0);
}

void SuiteTrackInspector::TwoObserversNotified()
{
    iTrackInspector->AddObserver(*this);
    Pull(EMsgTrack);
    TEST(iPlayCount == 0);
    TEST(iFailCount == 0);
    iLiveStream = true;
    Pull(EMsgDecodedStream);
    TEST(iPlayCount == 2);
    TEST(iFailCount == 0);
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

    switch (iNextGeneratedMsg)
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
