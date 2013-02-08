#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/ProtocolHttp.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Codec/Flac.h>
#include <OpenHome/Media/Codec/Wav.h>
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

class SupplierProtocolHttp : public Thread, public ISupplier, private ISupply
{
public:
    SupplierProtocolHttp(Environment& aEnv);
    ~SupplierProtocolHttp();
    void Start(const Brx& aUrl);
private: // from Thread
    void Run();
private: // from ISupplier
    void Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement);
    void Play();
    void Flush(Msg* aMsg);
    void Quit(Msg* aMsg);
private: // from ISupply
    void Start(TUint64 aTotalBytes, ILiveStreamer* aLiveStreamer, IRestreamer* aRestreamer, TUint aStreamId);
    void OutputData(const Brx& aData);
    void OutputMetadata(const Brx& aMetadata);
    void OutputFlush();
    void End();
private:
    MsgFactory* iMsgFactory;
    IPipelineElementDownstream* iPipeline;
    ProtocolManager* iProtocolManager;
    Brn iUrl;
};

class TestProtocolHttp : private IPipelineObserver
{
    static const TUint kMaxDriverJiffies = Jiffies::kJiffiesPerMs * 5;
    static const TUint kSeekStepSeconds = 10;
public:
    TestProtocolHttp(Environment& aEnv, Net::DvStack& aDvStack, const Brx& aUrl, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel);
    virtual ~TestProtocolHttp();
    int Run();
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack();
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
private:
    SupplierProtocolHttp* iSupplier;
    AllocatorInfoLogger iInfoAggregator;
    PipelineManager* iPipeline;
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

// SupplierProtocolHttp

SupplierProtocolHttp::SupplierProtocolHttp(Environment& aEnv)
    : Thread("SPHt")
    , iMsgFactory(NULL)
    , iPipeline(NULL)
{
    iProtocolManager = new ProtocolManager(*this);
    ProtocolHttp* protocolHttp = new ProtocolHttp(aEnv, *iProtocolManager);
    iProtocolManager->Add(protocolHttp);
}

SupplierProtocolHttp::~SupplierProtocolHttp()
{
    delete iProtocolManager;
}

void SupplierProtocolHttp::Start(const Brx& aUrl)
{
    iUrl.Set(aUrl);
    Thread::Start();
}

void SupplierProtocolHttp::Run()
{
    iProtocolManager->DoStream(iUrl);
}

void SupplierProtocolHttp::Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement)
{
    iMsgFactory = &aMsgFactory;
    iPipeline = &aDownstreamElement;
}

void SupplierProtocolHttp::Play()
{
}

void SupplierProtocolHttp::Flush(Msg* aMsg)
{
    iPipeline->Push(aMsg);
}

void SupplierProtocolHttp::Quit(Msg* aMsg)
{
    iPipeline->Push(aMsg);
}

void SupplierProtocolHttp::Start(TUint64 aTotalBytes, ILiveStreamer* aLiveStreamer, IRestreamer* aRestreamer, TUint aStreamId)
{
    Msg* msg = iMsgFactory->CreateMsgTrack(); // FIXME - should output this as soon as PipelineManager is told to play a track
    iPipeline->Push(msg);
    msg = iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), aTotalBytes, aStreamId, aRestreamer, aLiveStreamer);
    iPipeline->Push(msg);
}

void SupplierProtocolHttp::OutputData(const Brx& aData)
{
    Brn data(aData);
    do {
        Brn remaining;
        if (data.Bytes() > EncodedAudio::kMaxBytes) {
            remaining = data.Split(EncodedAudio::kMaxBytes);
            data.Set(data.Ptr(), EncodedAudio::kMaxBytes);
        }
        Msg* msg = iMsgFactory->CreateMsgAudioEncoded(data);
        iPipeline->Push(msg);
        data.Set(remaining);
    } while (data.Bytes() > 0);
}

void SupplierProtocolHttp::OutputMetadata(const Brx& aMetadata)
{
    Msg* metaText = iMsgFactory->CreateMsgMetaText(aMetadata);
    iPipeline->Push(metaText);
}

void SupplierProtocolHttp::OutputFlush()
{
    Msg* flush = iMsgFactory->CreateMsgFlush();
    iPipeline->Push(flush);
}

void SupplierProtocolHttp::End()
{
    Log::Print("FIXME - End\n");
}


// TestProtocolHttp

TestProtocolHttp::TestProtocolHttp(Environment& aEnv, Net::DvStack& aDvStack, const Brx& aUrl, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel)
    : iUrl(aUrl)
    , iStreamId(0)
{
    iSupplier = new SupplierProtocolHttp(aEnv);
    iPipeline = new PipelineManager(iInfoAggregator, *iSupplier, *this, kMaxDriverJiffies);
    iPipeline->AddCodec(new Codec::CodecFlac());
    iPipeline->AddCodec(new Codec::CodecWav());

    iDevice = new DvDeviceStandard(aDvStack, aSenderUdn);
    iDevice->SetAttribute("Upnp.Domain", "av.openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Sender");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", aSenderFriendlyName);
    iDevice->SetAttribute("Upnp.Manufacturer", "Openhome");
    iDevice->SetAttribute("Upnp.ManufacturerUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.ModelDescription", "ohMediaPlayer TestProtocolHttp");
    iDevice->SetAttribute("Upnp.ModelName", "ohMediaPlayer TestProtocolHttp");
    iDevice->SetAttribute("Upnp.ModelNumber", "1");
    iDevice->SetAttribute("Upnp.ModelUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.SerialNumber", "");
    iDevice->SetAttribute("Upnp.Upc", "");

    iDriver = new DriverSongcastSender(iPipeline->FinalElement(), kMaxDriverJiffies, aEnv, *iDevice, aSenderUdn, aSenderChannel, aAdapter, false /*unicast*/);
    iDevice->SetEnabled();
}

TestProtocolHttp::~TestProtocolHttp()
{
    delete iPipeline;
    delete iSupplier;
    delete iDriver;
    delete iDevice;
}

int TestProtocolHttp::Run()
{
    iSupplier->Start(iUrl);

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
                iSupplier->Block();
            }
            else {
                iSupplier->Unblock();
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
void TestProtocolHttp::NotifyPipelineState(EPipelineState aState)
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

void TestProtocolHttp::NotifyTrack()
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: TRACK\n");
#endif
}

void TestProtocolHttp::NotifyMetaText(const Brx& aText)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: METATEXT {");
    Log::Print(aText);
    Log::Print("}\n");
#endif
}

void TestProtocolHttp::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    iSeconds = aSeconds;
    iTrackDurationSeconds = aTrackDurationSeconds;
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: TIME {secs=%u; duration=%u}\n", aSeconds, aTrackDurationSeconds);
#endif
}

void TestProtocolHttp::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
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
    OptionParser parser;
    OptionString optionUrl("", "--url", Brn("http://10.2.9.146:26125/content/c2/b16/f44100/d2336-co13582.wav"), "[url] http url of file to play");
    parser.AddOption(&optionUrl);
    OptionString optionUdn("-u", "--udn", Brn("TestProtocolHttp"), "[udn] udn for the upnp device");
    parser.AddOption(&optionUdn);
    OptionString optionName("-n", "--name", Brn("TestProtocolHttp"), "[name] name of the sender");
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

    TestProtocolHttp* tph = new TestProtocolHttp(lib->Env(), *dvStack, optionUrl.Value(), adapter, optionUdn.Value(), optionName.CString(), optionChannel.Value());
    const int ret = tph->Run();
    delete tph;
    
    delete lib;

    return ret;
}
