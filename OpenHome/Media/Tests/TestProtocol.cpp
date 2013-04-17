#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/ProtocolHttp.h>
#include <OpenHome/Media/Protocol/ProtocolFile.h>
#include <OpenHome/Media/Pipeline.h>
#include <OpenHome/Media/Codec/Aac.h>
#include <OpenHome/Media/Codec/Alac.h>
#include <OpenHome/Media/Codec/Flac.h>
#include <OpenHome/Media/Codec/Wav.h>
#include <OpenHome/Media/Codec/Mp3.h>
#include <OpenHome/Media/DriverSongcastSender.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Debug.h>
#include "AllocatorInfoLogger.h"

#include <stdio.h>

#ifdef _WIN32

# define CDECL __cdecl

# include <conio.h>

int mygetch()
{
    return (_getch());
}

#elif defined(NOTERMIOS)

#define CDECL

int mygetch()
{
    return 0;
}

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

namespace OpenHome {
namespace Media {

class DummyFiller : public Thread, private IPipelineIdProvider
{
public:
    DummyFiller(Environment& aEnv, ISupply& aSupply, IFlushIdProvider& aFlushIdProvider);
    ~DummyFiller();
    void Start(const Brx& aUrl);
private: // from Thread
    void Run();
private: // from IPipelineIdProvider
    TUint NextTrackId();
    TUint NextStreamId();
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    void InvalidateAt(const Brx& aStyle, const Brx& aProviderId);
    void InvalidateAfter(const Brx& aStyle, const Brx& aProviderId);
private:
    ProtocolManager* iProtocolManager;
    Brn iUrl;
    TUint iNextTrackId;
    TUint iNextStreamId;
    static const TUint kInvalidPipelineId = 0;
};

class TestProtocol : private IPipelineObserver
{
    static const TUint kMaxDriverJiffies = Jiffies::kJiffiesPerMs * 5;
    static const TUint kSeekStepSeconds = 10;
public:
    TestProtocol(Environment& aEnv, Net::DvStack& aDvStack, const Brx& aUrl, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel);
    virtual ~TestProtocol();
    int Run();
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack(const Brx& aUri, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
private:
    DummyFiller* iFiller;
    AllocatorInfoLogger iInfoAggregator;
    Pipeline* iPipeline;
    Net::DvDeviceStandard* iDevice;
    DriverSongcastSender* iDriver;
    Brh iUrl;
    TUint iSeconds;
    TUint iTrackDurationSeconds;
    TUint iStreamId;
};

} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// DummyFiller

DummyFiller::DummyFiller(Environment& aEnv, ISupply& aSupply, IFlushIdProvider& aFlushIdProvider)
    : Thread("SPHt")
    , iNextTrackId(kInvalidPipelineId+1)
    , iNextStreamId(kInvalidPipelineId+1)
{
    iProtocolManager = new ProtocolManager(aSupply, *this, aFlushIdProvider);
    iProtocolManager->Add(new ProtocolHttp(aEnv));
    iProtocolManager->Add(new ProtocolFile(aEnv));
}

DummyFiller::~DummyFiller()
{
    delete iProtocolManager;
}

void DummyFiller::Start(const Brx& aUrl)
{
    iUrl.Set(aUrl);
    Thread::Start();
}

void DummyFiller::Run()
{
    iProtocolManager->DoStream(iUrl);
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


// TestProtocol

TestProtocol::TestProtocol(Environment& aEnv, Net::DvStack& aDvStack, const Brx& aUrl, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel)
    : iUrl(aUrl)
    , iStreamId(0)
{
    iPipeline = new Pipeline(iInfoAggregator, *this, kMaxDriverJiffies);
    iFiller = new DummyFiller(aEnv, *iPipeline, *iPipeline);
    iPipeline->AddCodec(new Codec::CodecFlac());
    iPipeline->AddCodec(new Codec::CodecWav());
    iPipeline->AddCodec(new Codec::CodecMp3());
    iPipeline->AddCodec(new Codec::CodecAlac());
    iPipeline->AddCodec(new Codec::CodecAac());
    iPipeline->Start();

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

    iDriver = new DriverSongcastSender(*iPipeline, kMaxDriverJiffies, aEnv, *iDevice, aSenderUdn, aSenderChannel, aAdapter, false /*unicast*/);
    iDevice->SetEnabled();
}

TestProtocol::~TestProtocol()
{
    delete iPipeline;
    delete iFiller;
    delete iDriver;
    delete iDevice;
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




int CDECL main(int aArgc, char* aArgv[])
{
    /* Useful test urls:
    http://10.2.9.146:26125/content/c2/b16/f44100/d2336-co13582.wav
    http://10.2.9.146:26125/content/c2/b16/f44100/d35587-co6318.flac
    http://10.2.9.146:26125/content/c2/b16/f44100/d40842-co4625.mp3
    file:///c:/test.wav
    http://10.2.11.131:9000/disk/NON-DLNA/music/O0$1$4I4009/Waiting%20for%20the%207.18.m4a  // alac
    http://10.2.11.174:26125/content/c2/b16/f48000/d2599-co459.m4a                          // aac
    http://10.2.11.174:26125/content/c2/b16/f44100/d3220-co459.ogg
    */
    OptionParser parser;
    OptionString optionUrl("", "--url", Brn("http://10.2.9.146:26125/content/c2/b16/f44100/d2336-co13582.wav"), "[url] http url of file to play");
    parser.AddOption(&optionUrl);
    OptionString optionUdn("-u", "--udn", Brn("TestProtocol"), "[udn] udn for the upnp device");
    parser.AddOption(&optionUdn);
    OptionString optionName("-n", "--name", Brn("TestProtocol"), "[name] name of the sender");
    parser.AddOption(&optionName);
    OptionUint optionChannel("-c", "--channel", 0, "[0..65535] sender channel");
    parser.AddOption(&optionChannel);
    OptionUint optionAdapter("-a", "--adapter", 0, "[adapter] index of network adapter to use");
    parser.AddOption(&optionAdapter);

    if (!parser.Parse(aArgc, aArgv)) {
        return 1;
    }

    InitialisationParams* initParams = InitialisationParams::Create();
	Net::Library* lib = new Net::Library(initParams);
    Net::DvStack* dvStack = lib->StartDv();
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    const TUint adapterIndex = optionAdapter.Value();
    if (subnetList->size() <= adapterIndex) {
		Log::Print("ERROR: adapter %d doesn't exist\n", adapterIndex);
		ASSERTS();
    }
    Log::Print ("adapter list:\n");
    for (unsigned i=0; i<subnetList->size(); ++i) {
		TIpAddress addr = (*subnetList)[i]->Address();
		Log::Print ("  %d: %d.%d.%d.%d\n", i, addr&0xff, (addr>>8)&0xff, (addr>>16)&0xff, (addr>>24)&0xff);
    }
    TIpAddress subnet = (*subnetList)[adapterIndex]->Subnet();
    TIpAddress adapter = (*subnetList)[adapterIndex]->Address();
    Library::DestroySubnetList(subnetList);
    lib->SetCurrentSubnet(subnet);
    Log::Print("using subnet %d.%d.%d.%d\n", subnet&0xff, (subnet>>8)&0xff, (subnet>>16)&0xff, (subnet>>24)&0xff);

    TestProtocol* tph = new TestProtocol(lib->Env(), *dvStack, optionUrl.Value(), adapter, optionUdn.Value(), optionName.CString(), optionChannel.Value());
    const int ret = tph->Run();
    delete tph;
    
    delete lib;

    return ret;
}
