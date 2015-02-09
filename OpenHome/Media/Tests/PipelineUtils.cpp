#include "PipelineUtils.h"
#include <OpenHome/Media/Tests/GetCh.h>
#include <OpenHome/Media/Tests/Cdecl.h>

#include <stdio.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// DummyFiller

DummyFiller::DummyFiller(Environment& aEnv, ISupply& aSupply, IFlushIdProvider& aFlushIdProvider, IInfoAggregator& aInfoAggregator)
    : Thread("SPHt")
    , iNextStreamId(kInvalidPipelineId+1)
{
    iProtocolManager = new ProtocolManager(aSupply, *this, aFlushIdProvider);
    iProtocolManager->Add(ProtocolFactory::NewHttp(aEnv));
    iProtocolManager->Add(ProtocolFactory::NewFile(aEnv));
    iTrackFactory = new TrackFactory(aInfoAggregator, 1);
}

DummyFiller::~DummyFiller()
{
    delete iProtocolManager;
    delete iTrackFactory;
}

void DummyFiller::Start(const Brx& aUrl)
{
    iUrl.Set(aUrl);
    Thread::Start();
}

void DummyFiller::Run()
{
    Track* track = iTrackFactory->CreateTrack(iUrl, Brx::Empty());
    iProtocolManager->DoStream(*track, Brx::Empty());
    track->RemoveRef();
}

TUint DummyFiller::NextStreamId()
{
    return iNextStreamId++;
}

EStreamPlay DummyFiller::OkToPlay(TUint /*aStreamId*/)
{
    return ePlayYes;
}

void DummyFiller::InvalidateAt(TUint /*aId*/)
{
    ASSERTS();
}

void DummyFiller::InvalidateAfter(TUint /*aId*/)
{
    ASSERTS();
}

void DummyFiller::InvalidatePending()
{
    ASSERTS();
}

void DummyFiller::InvalidateAll()
{
    ASSERTS();
}



// TestProtocol

TestProtocol::TestProtocol(Environment& aEnv, const Brx& aUrl)
    : iUrl(aUrl)
    , iStreamId(0)
{
    iPipeline = new Pipeline(iInfoAggregator, *this, kMaxDriverJiffies);
    iFiller = new DummyFiller(aEnv, *iPipeline, *iPipeline, iInfoAggregator);
    iPipeline->AddCodec(Codec::CodecFactory::NewFlac());
    iPipeline->AddCodec(Codec::CodecFactory::NewWav());
    iPipeline->AddCodec(Codec::CodecFactory::NewAac());
    iPipeline->AddCodec(Codec::CodecFactory::NewAlac());
    iPipeline->AddCodec(Codec::CodecFactory::NewVorbis());
    iPipeline->Start();
}

IPipelineElementUpstream& TestProtocol::GetPipeline() const
{
    return *iPipeline;
}

TUint TestProtocol::GetMaxDriverJiffies() const
{
    return kMaxDriverJiffies;
}

TestProtocol::~TestProtocol()
{
    delete iPipeline;
    delete iFiller;
}

int TestProtocol::Run()
{
    iFiller->Start(iUrl);

    TBool playing = false;
    //TBool starve = false;
    TBool quit = false;

    Log::Print("\nPipeline test using ProtocolHttp as supplier.  Usage:\n");
    Log::Print("p: Toggle between play/pause\n");
    Log::Print("n: Toggle between start/stop simulating network starvation\n");
    Log::Print("s: Stop (only valid when paused)\n");
    Log::Print("q: Quit\n");
    Log::Print("\n");
    do {
        int key = mygetch();
        switch (key)
        {
        case 'p':
            playing = !playing;
            if (playing) {
                iPipeline->Play();
            }
            else {
                iPipeline->Pause();
            }
            break;
        /*case 'n':
            starve = !starve;
            if (starve) {
                iFiller->Block();
            }
            else {
                iFiller->Unblock();
            }
            break;*/
        case 's':
            if (!playing) {
                iPipeline->Stop();
            }
            break;
        case 'q':
            quit = true;
            break;
        case '+':
        {
            TUint seekAbsolute = iSeconds + kSeekStepSeconds;
            if (seekAbsolute > iTrackDurationSeconds) {
                seekAbsolute = iTrackDurationSeconds;
            }
            (void)iPipeline->Seek(1, iStreamId, seekAbsolute);
        }
            break;
        case '-':
        {
            const TUint seekAbsolute = (iSeconds > kSeekStepSeconds? iSeconds - kSeekStepSeconds : 0);
            (void)iPipeline->Seek(1, 1, seekAbsolute);
        }
            break;
        default:
            break;
        }
    } while (!quit);

    return 0;
}

PipelineSongcast::PipelineSongcast(TestProtocol* aTestProtocol, Environment& aEnv, Net::DvStack& aDvStack, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel)
    : iTestProtocol(aTestProtocol)
    , iDriver(NULL)
{
    iDriver = new DriverSongcastSender(iTestProtocol->GetPipeline(), iTestProtocol->GetMaxDriverJiffies(), aDvStack, aSenderUdn, aSenderChannel);
}

PipelineSongcast::~PipelineSongcast()
{
    delete iTestProtocol;
    delete iDriver;
}

int PipelineSongcast::Run()
{
    return iTestProtocol->Run();
}

#define LOG_PIPELINE_OBSERVER
#ifdef _WIN32
// suppress 'unreferenced formal parameter' warnings which come and go depending
// on the state of LOG_PIPELINE_OBSERVER
# pragma warning(disable:4100)
#endif
void TestProtocol::NotifyPipelineState(EPipelineState aState)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline state change: %s\n", TransportState::FromPipelineState(aState));
#endif
}

void TestProtocol::NotifyTrack(const Brx& aUri, const Brx& aMode)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: TRACK {uri=");
    Log::Print(aUri);
    Log::Print("; mode=");
    Log::Print(aMode);
    Log::Print("\n");
#endif
}

void TestProtocol::NotifyMetaText(const Brx& aText)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: METATEXT {");
    Log::Print(aText);
    Log::Print("}\n");
#endif
}

void TestProtocol::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    iSeconds = aSeconds;
    iTrackDurationSeconds = aTrackDurationSeconds;
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: TIME {secs=%u; duration=%u}\n", aSeconds, aTrackDurationSeconds);
#endif
}

void TestProtocol::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    iStreamId = aStreamInfo.StreamId();
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: FORMAT {bitRate=%u; bitDepth=%u, sampleRate=%u, numChannels=%u, codec=",
           aStreamInfo.BitRate(), aStreamInfo.BitDepth(), aStreamInfo.SampleRate(), aStreamInfo.NumChannels());
    Log::Print(aStreamInfo.CodecName());
    Log::Print("; trackLength=%llx, lossless=%u}\n", aStreamInfo.TrackLength(), aStreamInfo.Lossless());
#endif
}

