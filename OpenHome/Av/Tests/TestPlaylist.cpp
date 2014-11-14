#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Av/Tests/RamStore.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Av/SourceFactory.h>
#include <Generated/CpAvOpenhomeOrgPlaylist1.h>
#include <OpenHome/Net/Core/CpDeviceDv.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Configuration/Tests/ConfigRamStore.h>
#include <OpenHome/PowerManager.h>

#include <array>
#include <limits.h>
#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;

namespace OpenHome {
namespace Av {
namespace TestPlaylist {

class DummyAsyncOutput : private IAsyncOutput
{
public:
    void LogError(IAsync& aAsync);
    virtual ~DummyAsyncOutput() {}
private:
    void Output(const TChar* aKey, const TChar* aValue);
};

class DummyDriver : public Thread, private IMsgProcessor
{
public:
    DummyDriver(IPipelineElementUpstream& aPipeline);
    ~DummyDriver();
    void PullTrack(Functor aTrackCompleted);
    void PullUntilNewTrack(Functor aTrackChanged, TInt aSampleVal);
    void Mark();
    TUint MarkEnd();
private: // from Thread
    void Run() override;
private:
    void TrackCompleted();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    Mutex iLock;
    IPipelineElementUpstream& iPipeline;
    Functor iTrackCompleted;
    Functor iTrackChanged;
    TUint iJiffiesPerSample;
    TUint iBitDepth;
    TUint iNumChannels;
    TInt iTargetTrackSample;
    TUint64 iJiffies;
    TBool iCountJiffies;
    TBool iQuit;
};
    
class SuitePlaylist : public SuiteUnitTest, private IPipelineObserver
{
    static const TUint kNumTracks = 4;
    static const TChar* kFmtTone;
public:
    SuitePlaylist(CpStack& aCpStack, DvStack& aDvStack);
    ~SuitePlaylist();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState) override;
    void NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) override;
private:
    void TransportStateRemainsPlayingAcrossTracks();
    void NextInterruptsCurrentTrack();
    void PlayCompleteList();
    void SeekId();
    void SeekIdPrev();
    void SeekIndexValid();
    void SeekIndexInvalid();
    void DeletePlaying();
    void PlayNextDelete();
    void SeekIdPrevDelete();
    void PlayDeleteAll();
    void PlayDeleteAllPlay();
    void AddTrackJustBeforeCompletingPlaylist();
private:
    void Disabled();
    void TrackChanged();
private:
    Semaphore iDeviceDisabled;
    Semaphore iTrackChanged;
    CpStack& iCpStack;
    DvStack& iDvStack;
    DvDeviceStandard* iDevice;
    RamStore* iRamStore;
    ConfigRamStore* iConfigRamStore;
    MediaPlayer* iMediaPlayer;
    DummyDriver* iDriver;
    CpProxyAvOpenhomeOrgPlaylist1* iProxy;
    std::array<TUint, kNumTracks> iTrackIds;
    TUint iCurrentTrackId;
    TUint iTrackCount;
    EPipelineState iTransportState;
    TUint iTransportStateCount[EPipelineStateCount];
    Semaphore iTimeSem;
    Semaphore iSemPrefetched;
    TBool iPrefetchCompleted;
};

} // namespace TestPlaylist
} // namespace Av
} // namespace OpenHome

using namespace OpenHome::Av::TestPlaylist;

/*
Test cases:
    - play track #2 as soon as #1 finishes.  TransportState remains Playing
    - Next while #1 is playing.  Switch to #2 within Stopper + StarvationMonitor bounds
    - Play entire playlist.  Check Halt msg is delivered at end of this and that Track #1 is queued but not playing
    - SeekId for #2 plays #2
    - SeekIndex for #2 plays #2
    - SeekIndex for #10 does nothing
    - SeekId for #2.  Prev switches to #1 within Stopper + StarvationMonitor bounds
    - Delete playing track. Check next starts within Stopper + StarvationMonitor bounds
    - Next then Delete newly queued track.  Check we move to the following track.
    - SeekId for #3; Prev then Delete newly queued track.  Check we move to the preceeding track (#1).
    - Play then DeleteAll.  Check TransportState changes to ??? within Stopper + StarvationMonitor bounds
    - Seek to last track.  Add new track after it when we're ~2secs from the end.  Check this new track is played.
*/

// DummyAsyncOutput

void DummyAsyncOutput::LogError(IAsync& aAsync)
{
    aAsync.Output(*this);
}

void DummyAsyncOutput::Output(const TChar* /*aKey*/, const TChar* /*aValue*/)
{
}


// DummyDriver

DummyDriver::DummyDriver(IPipelineElementUpstream& aPipeline)
    : Thread("DummyDriver")
    , iLock("DMYD")
    , iPipeline(aPipeline)
    , iJiffiesPerSample(0)
    , iBitDepth(0)
    , iNumChannels(0)
    , iTargetTrackSample(INT_MAX)
    , iCountJiffies(false)
    , iQuit(false)
{
    Start();
}

DummyDriver::~DummyDriver()
{
    Kill();
    Join();
}

void DummyDriver::PullTrack(Functor aTrackCompleted)
{
    iLock.Wait();
    iTrackCompleted = aTrackCompleted;
    iLock.Signal();
}

void DummyDriver::PullUntilNewTrack(Functor aTrackChanged, TInt aSampleVal)
{
    iLock.Wait();
    iTrackChanged = aTrackChanged;
    iTargetTrackSample = aSampleVal;
    iLock.Signal();
}

void DummyDriver::Mark()
{
    iLock.Wait();
    iJiffies = 0;
    iCountJiffies = true;
    iLock.Signal();
}

TUint DummyDriver::MarkEnd()
{
    iLock.Wait();
    ASSERT(iCountJiffies);
    iCountJiffies = false;
    TUint milliSecs = (TUint)(iJiffies / Jiffies::kPerMs);
    iJiffies = 0;
    iLock.Signal();
    return milliSecs;
}

void DummyDriver::Run()
{
    /* FIXME - If we Sleep on every loop below, the test is painfully slow
               If we only Sleep every nth iteration, StarvationMonitor kicks in
               under valgrind and Playing/Buffering counts increase, breaking tests */
    //TUint count = 0;
    do {
        Msg* msg = iPipeline.Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
        //if (++count % 4 == 0) {
            Thread::Sleep(1); // slow driver to reduce (avoid?) chances of drop-outs
        //}
    } while (!iQuit);
}

void DummyDriver::TrackCompleted()
{
    if (iTrackCompleted) {
        iTrackCompleted();
    }
}

Msg* DummyDriver::ProcessMsg(MsgMode* /*aMsg*/)
{
    ASSERTS(); // msg type not expected at the far right of the pipeline
    return NULL;
}

Msg* DummyDriver::ProcessMsg(MsgSession* /*aMsg*/)
{
    ASSERTS(); // msg type not expected at the far right of the pipeline
    return NULL;
}

Msg* DummyDriver::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS(); // msg type not expected at the far right of the pipeline
    return NULL;
}

Msg* DummyDriver::ProcessMsg(MsgDelay* /*aMsg*/)
{
    ASSERTS(); // msg type not expected at the far right of the pipeline
    return NULL;
}

Msg* DummyDriver::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS(); // msg type not expected at the far right of the pipeline
    return NULL;
}

Msg* DummyDriver::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); // msg type not expected at the far right of the pipeline
    return NULL;
}

Msg* DummyDriver::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS(); // msg type not expected at the far right of the pipeline
    return NULL;
}

Msg* DummyDriver::ProcessMsg(MsgHalt* aMsg)
{
    TrackCompleted();
    return aMsg;
}

Msg* DummyDriver::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // msg type not expected at the far right of the pipeline
    return NULL;
}

Msg* DummyDriver::ProcessMsg(MsgWait* /*aMsg*/)
{
    ASSERTS(); // msg type not expected at the far right of the pipeline
    return NULL;
}

Msg* DummyDriver::ProcessMsg(MsgDecodedStream* aMsg)
{
    ASSERT(aMsg->StreamInfo().BitDepth() == 16); // ProcessMsg for MsgPlayable will need to change if this isn't true
    iJiffiesPerSample = Jiffies::JiffiesPerSample(aMsg->StreamInfo().SampleRate());
    iBitDepth = aMsg->StreamInfo().BitDepth();
    iNumChannels = aMsg->StreamInfo().NumChannels();
    return aMsg;
}

Msg* DummyDriver::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS(); // msg type not expected at the far right of the pipeline
    return NULL;
}

Msg* DummyDriver::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); // msg type not expected at the far right of the pipeline
    return NULL;
}

Msg* DummyDriver::ProcessMsg(MsgPlayable* aMsg)
{
    AutoMutex a(iLock);
    if (iCountJiffies) {
        const TUint numSamples = aMsg->Bytes() / ((iBitDepth/8) * iNumChannels);
        iJiffies += numSamples * iJiffiesPerSample;
    }

    ProcessorPcmBufPacked proc;
    aMsg->Read(proc);
    Brn buf = proc.Buf();
    const TInt subsample = (buf[buf.Bytes()-1] << 8) | buf[buf.Bytes()-2];
    //Log::Print("Pulled audio with subsamples %u\n", subsample);
    if (subsample == iTargetTrackSample && iTrackChanged) {
        iTrackChanged();
        iTrackChanged = Functor();
    }
    return aMsg;
}

Msg* DummyDriver::ProcessMsg(MsgQuit* aMsg)
{
    TrackCompleted();
    iQuit = true;
    return aMsg;
}


// SuitePlaylist

const TChar* SuitePlaylist::kFmtTone = "tone://constant-%u.wav?bitdepth=16&samplerate=44100&pitch=50&channels=1&duration=5";

SuitePlaylist::SuitePlaylist(CpStack& aCpStack, DvStack& aDvStack)
    : SuiteUnitTest("Playlist")
    , iDeviceDisabled("TPLY", 0)
    , iTrackChanged("TPLY", 0)
    , iCpStack(aCpStack)
    , iDvStack(aDvStack)
    , iTimeSem("TPL1", 0)
    , iSemPrefetched("TPL2", 0)
{
    AddTest(MakeFunctor(*this, &SuitePlaylist::TransportStateRemainsPlayingAcrossTracks), "TransportStateRemainsPlayingAcrossTracks");
    AddTest(MakeFunctor(*this, &SuitePlaylist::NextInterruptsCurrentTrack), "NextInterruptsCurrentTrack");
    AddTest(MakeFunctor(*this, &SuitePlaylist::PlayCompleteList), "PlayCompleteList");
    AddTest(MakeFunctor(*this, &SuitePlaylist::SeekId), "SeekId");
    AddTest(MakeFunctor(*this, &SuitePlaylist::SeekIdPrev), "SeekIdPrev");
    AddTest(MakeFunctor(*this, &SuitePlaylist::SeekIndexValid), "SeekIndexValid");
    AddTest(MakeFunctor(*this, &SuitePlaylist::SeekIndexInvalid), "SeekIndexInvalid");
    AddTest(MakeFunctor(*this, &SuitePlaylist::DeletePlaying), "DeletePlaying");
    AddTest(MakeFunctor(*this, &SuitePlaylist::PlayNextDelete), "PlayNextDelete");
    //AddTest(MakeFunctor(*this, &SuitePlaylist::SeekIdPrevDelete), "SeekIdPrevDelete");
    AddTest(MakeFunctor(*this, &SuitePlaylist::PlayDeleteAll), "PlayDeleteAll");
    AddTest(MakeFunctor(*this, &SuitePlaylist::PlayDeleteAllPlay), "PlayDeleteAllPlay");
    AddTest(MakeFunctor(*this, &SuitePlaylist::AddTrackJustBeforeCompletingPlaylist), "AddTrackJustBeforeCompletingPlaylist");
}

SuitePlaylist::~SuitePlaylist()
{
}

void SuitePlaylist::Setup()
{
    Environment& env = iDvStack.Env();
    Bwh udn("TestPlaylist");
    RandomiseUdn(env, udn);
    iDevice = new DvDeviceStandard(iDvStack, udn);
    iDevice->SetAttribute("Upnp.Domain", "av.openhome.org");
    iDevice->SetAttribute("Upnp.Type", "MediaPlayer");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", "TestPlaylist");
    iDevice->SetAttribute("Upnp.Manufacturer", "OpenHome");
    iDevice->SetAttribute("Upnp.ModelName", "TestPlaylist");

    iRamStore = new RamStore();
    iConfigRamStore = new ConfigRamStore();
    iMediaPlayer = new MediaPlayer(iDvStack, *iDevice, *iRamStore, *iConfigRamStore, NULL, udn);
    iMediaPlayer->Add(Codec::CodecFactory::NewWav());
    iMediaPlayer->Add(ProtocolFactory::NewTone(env));
    // No content processors
    iMediaPlayer->Add(SourceFactory::NewPlaylist(*iMediaPlayer, Brn("*")));
    iMediaPlayer->Pipeline().AddObserver(*this);
    iMediaPlayer->Start();

    iDriver = new DummyDriver(iMediaPlayer->Pipeline());

    iDevice->SetEnabled();
    CpDeviceDv* cpDevice = CpDeviceDv::New(iCpStack, *iDevice);
    iProxy = new CpProxyAvOpenhomeOrgPlaylist1(*cpDevice);
    cpDevice->RemoveRef(); // iProxy will have claimed a reference to the device so no need for us to hang onto another

    iCurrentTrackId = Track::kIdNone;
    iTrackCount = 0;
    iTransportState = EPipelineStateCount;
    for (TInt i=0; i<EPipelineStateCount; i++) {
        iTransportStateCount[i] = 0;
    }

    iPrefetchCompleted = false;
    iSemPrefetched.Clear();
    TUint after = Track::kIdNone;
    Bws<128> tone;
    for (TUint i=0; i<kNumTracks; i++) {
        tone.SetBytes(0);
        tone.AppendPrintf(kFmtTone, i+1);
        iProxy->SyncInsert(after, tone, Brx::Empty(), iTrackIds[i]);
        after = iTrackIds[i];
    }
    iTrackChanged.Clear();
    iTimeSem.Clear();
    iSemPrefetched.Wait(); // wait for initial Track to make it as far as the Stopper
}

void SuitePlaylist::TearDown()
{
    delete iProxy;
    iDevice->SetDisabled(MakeFunctor(*this, &SuitePlaylist::Disabled));
    iDeviceDisabled.Wait();
    iMediaPlayer->Quit();
    delete iDriver;
    delete iMediaPlayer;
    delete iConfigRamStore;
    delete iRamStore;
    delete iDevice;
}

void SuitePlaylist::NotifyPipelineState(EPipelineState aState)
{
#if 0
    Log::Print("NotifyPipelineState - %s\n", TransportState::FromPipelineState(aState));
#endif
    iTransportState = aState;
    iTransportStateCount[aState]++;
}

void SuitePlaylist::NotifyTrack(Track& aTrack, const Brx& /*aMode*/, TUint /*aIdPipeline*/)
{
    //Log::Print("NotifyTrack: id=%u\n", aTrack.Id());
    iCurrentTrackId = aTrack.Id();
    iTrackCount++;
}

void SuitePlaylist::NotifyMetaText(const Brx& /*aText*/)
{
}

void SuitePlaylist::NotifyTime(TUint /*aSeconds*/, TUint /*aTrackDurationSeconds*/)
{
    //Log::Print("NotifyTime: secs= %u\n", aSeconds);
    iTimeSem.Signal();
}

void SuitePlaylist::NotifyStreamInfo(const DecodedStreamInfo& /*aStreamInfo*/)
{
    if (!iPrefetchCompleted) {
        iPrefetchCompleted = true;
        iSemPrefetched.Signal();
    }
}

void SuitePlaylist::TransportStateRemainsPlayingAcrossTracks()
{
    iDriver->PullUntilNewTrack(MakeFunctor(*this, &SuitePlaylist::TrackChanged), 1);
    iProxy->SyncPlay();
    iTrackChanged.Wait();
    TUint transportStateCount[EPipelineStateCount];
    (void)memcpy(transportStateCount, iTransportStateCount, sizeof(transportStateCount));
    TEST(iCurrentTrackId == iTrackIds[0]);
    TEST(iTransportState == EPipelinePlaying);
    iDriver->PullUntilNewTrack(MakeFunctor(*this, &SuitePlaylist::TrackChanged), 2);
    iTrackChanged.Wait();
    TEST(iCurrentTrackId == iTrackIds[1]);
    TEST(iTransportState == EPipelinePlaying);
    TEST(iTransportStateCount[EPipelinePlaying] == transportStateCount[EPipelinePlaying]);
    TEST(iTransportStateCount[EPipelinePaused] == transportStateCount[EPipelinePaused]);
    TEST(iTransportStateCount[EPipelineStopped] == transportStateCount[EPipelineStopped]);
    TEST(iTransportStateCount[EPipelineBuffering] == transportStateCount[EPipelineBuffering]);
}

void SuitePlaylist::NextInterruptsCurrentTrack()
{
    iProxy->SyncPlay();
    iTimeSem.Wait();
    iTimeSem.Wait();
    TEST(iCurrentTrackId == iTrackIds[0]);
    // now 1 sec into track #1
    iDriver->Mark();
    iDriver->PullUntilNewTrack(MakeFunctor(*this, &SuitePlaylist::TrackChanged), 2);
    iMediaPlayer->Pipeline().Next();
    iTrackChanged.Wait();
    const TUint ms = iDriver->MarkEnd();
    Print("Pulled %ums audio", ms);
    //TEST(iDriver->Jiffies() < ...  // FIXME
    TEST(iCurrentTrackId == iTrackIds[1]);
    TEST(iTransportState == EPipelinePlaying);
}

void SuitePlaylist::PlayCompleteList()
{
    iProxy->SyncPlay();
    iDriver->PullUntilNewTrack(MakeFunctor(*this, &SuitePlaylist::TrackChanged), 1);
    iTrackChanged.Wait();
    TUint transportStateCount[EPipelineStateCount];
    (void)memcpy(transportStateCount, iTransportStateCount, sizeof(transportStateCount));
    TEST(iCurrentTrackId == iTrackIds[0]);
    for (TUint i=1; i<kNumTracks; i++) {
        iDriver->PullUntilNewTrack(MakeFunctor(*this, &SuitePlaylist::TrackChanged), i+1);
        iTrackChanged.Wait();
        TEST(iCurrentTrackId == iTrackIds[i]);
    }
    TEST(iTransportState == EPipelinePlaying);
    TEST(iTransportStateCount[EPipelinePlaying] == transportStateCount[EPipelinePlaying]);
    TEST(iTransportStateCount[EPipelinePaused] == transportStateCount[EPipelinePaused]);
    TEST(iTransportStateCount[EPipelineStopped] == transportStateCount[EPipelineStopped]);
    TEST(iTransportStateCount[EPipelineBuffering] == transportStateCount[EPipelineBuffering]);
}

void SuitePlaylist::SeekId()
{
    iProxy->SyncSeekId(iTrackIds[1]);
    iDriver->PullUntilNewTrack(MakeFunctor(*this, &SuitePlaylist::TrackChanged), 2);
    iTrackChanged.Wait();
    TEST(iCurrentTrackId == iTrackIds[1]);
    TEST(iTrackCount == 2);
    TEST(iTransportState == EPipelinePlaying);
    TEST(iTransportStateCount[EPipelinePlaying] == 1);
}

void SuitePlaylist::SeekIdPrev()
{
    iProxy->SyncSeekId(iTrackIds[1]);
    while (iCurrentTrackId != iTrackIds[1]) {
        Thread::Sleep(1); /* Lazy poll until SeekId takes effect
                             Without this, we don't know whether we'll need to call SyncPlay() after SyncPrevious() */
    }
    iProxy->SyncPrevious();
    iDriver->PullUntilNewTrack(MakeFunctor(*this, &SuitePlaylist::TrackChanged), 1);
    iTrackChanged.Wait();
    TEST(iCurrentTrackId == iTrackIds[0]);
    TEST(iTrackCount == 3);
    TEST(iTransportState == EPipelinePlaying);
    TEST(iTransportStateCount[EPipelinePlaying] == 1);
}

void SuitePlaylist::SeekIndexValid()
{
    iProxy->SyncSeekIndex(1);
    iDriver->PullUntilNewTrack(MakeFunctor(*this, &SuitePlaylist::TrackChanged), 2);
    iTrackChanged.Wait();
    TEST(iCurrentTrackId == iTrackIds[1]);
    TEST(iTrackCount == 2);
    TEST(iTransportState == EPipelinePlaying);
    TEST(iTransportStateCount[EPipelinePlaying] == 1);
}

void SuitePlaylist::SeekIndexInvalid()
{
    try {
        iProxy->SyncSeekIndex(100);
        TEST(false);
    }
    catch (ProxyError&) {}
    TEST(true);
}

void SuitePlaylist::DeletePlaying()
{
    iProxy->SyncPlay();
    iTimeSem.Wait();
    iTimeSem.Wait();
    // now 1 sec into track #1
    TEST(iCurrentTrackId == iTrackIds[0]);
    iDriver->PullUntilNewTrack(MakeFunctor(*this, &SuitePlaylist::TrackChanged), 2);
    iProxy->SyncDeleteId(iTrackIds[0]);
    iDriver->Mark();
    iTrackChanged.Wait();
    const TUint ms = iDriver->MarkEnd();
    Print("Pulled %ums audio", ms);
    //TEST(iDriver->Jiffies() < ... // FIXME
    TEST(iCurrentTrackId == iTrackIds[1]);
    TEST(iTrackCount == 2);
    TEST(iTransportState == EPipelinePlaying);
    TEST(iTransportStateCount[EPipelinePlaying] == 1);
}

void SuitePlaylist::PlayNextDelete()
{
    iProxy->SyncPlay();
    iProxy->SyncNext();
    iProxy->SyncDeleteId(iTrackIds[1]);
    iDriver->Mark();
    iDriver->PullUntilNewTrack(MakeFunctor(*this, &SuitePlaylist::TrackChanged), 3); // FIXME - pulling until subsample==2 demonstrates ePlayLater bug (plays immediately?)
    iTrackChanged.Wait();
    const TUint ms = iDriver->MarkEnd();
    Print("Pulled %ums audio", ms);
    //TEST(iDriver->Jiffies() < ...  // FIXME
    TEST(iCurrentTrackId == iTrackIds[2]);
    TEST(iTransportState == EPipelinePlaying);
    TEST(iTransportStateCount[EPipelinePlaying] == 1);
}

void SuitePlaylist::SeekIdPrevDelete()
{
    iProxy->SyncSeekId(iTrackIds[2]);
    iProxy->SyncPrevious();
    iProxy->SyncDeleteId(iTrackIds[1]);
    iProxy->SyncPlay();
    iDriver->Mark();
    iDriver->PullUntilNewTrack(MakeFunctor(*this, &SuitePlaylist::TrackChanged), 3); // exect content from iTrackIds[2] after queuing then deleting iTrackIds[1]
    iTrackChanged.Wait();
    const TUint ms = iDriver->MarkEnd();
    Print("Pulled %ums audio", ms);
    //TEST(iDriver->Jiffies() < ...  // FIXME
    TEST(iCurrentTrackId == iTrackIds[2]);
    TEST(iTransportState == EPipelinePlaying);
    TEST(iTransportStateCount[EPipelinePlaying] == 1);
}

void SuitePlaylist::PlayDeleteAll()
{
    iProxy->SyncPlay();
    iTimeSem.Wait();
    iTimeSem.Wait();
    iProxy->SyncDeleteAll();
    while (iTransportState != EPipelineStopped) {
        // lazy way of waiting for the playing track to ramp down and the pipeline to actually stop
        Thread::Sleep(50);
    }
    //TEST(iTransportState == EPipelineStopped);
    TEST(iCurrentTrackId == 1); // FIXME - duplicating knowledge of Filler's NullTrack
    TEST(iTransportStateCount[EPipelinePaused] == 0); // # transitions through other states is unpredictable
}

void SuitePlaylist::PlayDeleteAllPlay()
{
    iProxy->SyncPlay();
    iTimeSem.Wait();
    iTimeSem.Wait();
    iProxy->SyncDeleteAll();
    iProxy->SyncPlay();
    while (iTransportState != EPipelineStopped) {
        // lazy way of waiting for the playing track to ramp down and the pipeline to actually stop
        Thread::Sleep(50);
    }
    //TEST(iTransportState == EPipelineStopped);
    TEST(iCurrentTrackId == 1); // FIXME - duplicating knowledge of Filler's NullTrack
    TEST(iTransportStateCount[EPipelinePaused] == 0); // # transitions through other states is unpredictable
}

void SuitePlaylist::AddTrackJustBeforeCompletingPlaylist()
{
    iProxy->SyncPlay();
    for (TUint i=0; i<kNumTracks-1; i++) {
        iDriver->PullUntilNewTrack(MakeFunctor(*this, &SuitePlaylist::TrackChanged), i+1);
        iTrackChanged.Wait();
        TEST(iCurrentTrackId == iTrackIds[i]);
    }
    (void)iTimeSem.Clear();
    iTimeSem.Wait();
    iTimeSem.Wait();
    iTimeSem.Wait(); // 2-3s into final track in the playlist

    Bws<128> tone;
    tone.AppendPrintf(kFmtTone, kNumTracks+1);
    TUint trackId;
    iProxy->SyncInsert(iTrackIds[kNumTracks-1], tone, Brx::Empty(), trackId);
    iDriver->PullUntilNewTrack(MakeFunctor(*this, &SuitePlaylist::TrackChanged), kNumTracks+1);
    iTrackChanged.Wait();
    TEST(iCurrentTrackId == trackId);
    TEST(iTrackCount == kNumTracks+1);
    TEST(iTransportState == EPipelinePlaying);
    TEST(iTransportStateCount[EPipelinePlaying] == 1);
}

void SuitePlaylist::TrackChanged()
{
    iTrackChanged.Signal();
}

void SuitePlaylist::Disabled()
{
    iDeviceDisabled.Signal();
}


void TestPlaylist(CpStack& aCpStack, DvStack& aDvStack)
{
    DummyAsyncOutput errorSuppressor;
    InitialisationParams* initParams = aDvStack.Env().InitParams();
    FunctorAsync oldAsyncErrorHandler = initParams->AsyncErrorHandler();
    initParams->SetAsyncErrorHandler(MakeFunctorAsync(errorSuppressor, &DummyAsyncOutput::LogError));
    /* TestFramework handler is only required for TEST_THROWS(..., AssertionFailed).
       We don't use that; the TF handler obfuscates all other assertion failures so is better disabled. */
    //AssertHandler assertHandler = SetAssertHandler(AssertHandlerDefault);
    Runner runner("Playlist tests\n");
    runner.Add(new SuitePlaylist(aCpStack, aDvStack));
    runner.Run();
    initParams->SetAsyncErrorHandler(oldAsyncErrorHandler);
    //(void)SetAssertHandler(assertHandler);
}
