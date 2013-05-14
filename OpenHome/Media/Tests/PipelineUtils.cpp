#include "PipelineUtils.h"

#include <stdio.h>


int mygetch();

#ifdef _WIN32

# define CDECL __cdecl

# include <conio.h>

int mygetch()
{
    return (_getch());
}

#elif defined(NOTERMIOS)

#define CDECL

#else

# define CDECL

# include <termios.h>
# include <unistd.h>

int mygetch()
{
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
}

#endif // _WIN32



using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// DummyFiller

DummyFiller::DummyFiller(Environment& aEnv, ISupply& aSupply, IFlushIdProvider& aFlushIdProvider, Av::IInfoAggregator& aInfoAggregator)
    : Thread("SPHt")
    , iNextTrackId(kInvalidPipelineId+1)
    , iNextStreamId(kInvalidPipelineId+1)
{
    iProtocolManager = new ProtocolManager(aSupply, *this, aFlushIdProvider);
    iProtocolManager->Add(new ProtocolHttp(aEnv));
    iProtocolManager->Add(new ProtocolFile(aEnv));
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
    Track* track = iTrackFactory->CreateTrack(iUrl, Brx::Empty(), Brx::Empty(), Brx::Empty(), 0);
    iProtocolManager->DoStream(*track);
    track->RemoveRef();
}

TUint DummyFiller::NextTrackId()
{
    return iNextTrackId++;
}

TUint DummyFiller::NextStreamId()
{
    return iNextStreamId++;
}

EStreamPlay DummyFiller::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    return ePlayYes;
}

void DummyFiller::InvalidateAt(const Brx& /*aStyle*/, const Brx& /*aProviderId*/)
{
    ASSERTS();
}

void DummyFiller::InvalidateAfter(const Brx& /*aStyle*/, const Brx& /*aProviderId*/)
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
    iPipeline->AddCodec(Codec::CodecFactory::NewWma());
    iPipeline->AddCodec(Codec::CodecFactory::NewMp3());
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
    , iDevice(0)
    , iDriver(0)
{
    iDevice = new DvDeviceStandard(aDvStack, aSenderUdn);
    iDevice->SetAttribute("Upnp.Domain", "av.openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Sender");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", aSenderFriendlyName);
    iDevice->SetAttribute("Upnp.Manufacturer", "Openhome");
    iDevice->SetAttribute("Upnp.ManufacturerUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.ModelDescription", "ohMediaPlayer TestProtocol");
    iDevice->SetAttribute("Upnp.ModelName", "ohMediaPlayer TestProtocol");
    iDevice->SetAttribute("Upnp.ModelNumber", "1");
    iDevice->SetAttribute("Upnp.ModelUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.SerialNumber", "");
    iDevice->SetAttribute("Upnp.Upc", "");

    iDriver = new DriverSongcastSender(iTestProtocol->GetPipeline(), iTestProtocol->GetMaxDriverJiffies(), aEnv, *iDevice, aSenderUdn, aSenderChannel, aAdapter, false);
    iDevice->SetEnabled();
}

PipelineSongcast::~PipelineSongcast()
{
    delete iTestProtocol;
    delete iDriver;
    delete iDevice;
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
    const char* state = "";
    switch (aState)
    {
    case EPipelinePlaying:
        state = "playing";
        break;
    case EPipelinePaused:
        state = "paused";
        break;
    case EPipelineStopped:
        state = "stopped";
        break;
    case EPipelineBuffering:
        state = "buffering";
        break;
    default:
        ASSERTS();
    }
    Log::Print("Pipeline state change: %s\n", state);
#endif
}

void TestProtocol::NotifyTrack(const Brx& aUri, TUint aIdPipeline)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: TRACK {uri=");
    Log::Print(aUri);
    Log::Print("; idPipeline=%u}\n", aIdPipeline);
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

