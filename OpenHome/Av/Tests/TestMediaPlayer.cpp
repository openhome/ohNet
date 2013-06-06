#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Av/UpnpAv/UpnpAv.h>
#include <OpenHome/Media/Tests/AllocatorInfoLogger.h>
#include <OpenHome/Media/DriverSongcastSender.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Av/KvpStore.h>
#include "RamStore.h"
#include <OpenHome/Av/Radio/PresetDatabase.h> // FIXME
#include <OpenHome/Av/Product.h>
#include <OpenHome/Av/Radio/SourceRadio.h>

#ifdef _WIN32
#if !defined(CDECL)
# define CDECL __cdecl
#endif

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
namespace Av {

class TestMediaPlayer
{
    static const TUint kTrackCount = 1200;
    static const TUint kMaxDriverJiffies = Media::Jiffies::kJiffiesPerMs * 5;
public:
    TestMediaPlayer(Net::DvStack& aDvStack, Net::DvDevice& aDevice, IStaticDataSource& aStaticDataSource, IPersister& aPersistor, TIpAddress aAdapter, const Brx& aSenderUdn, TUint aSenderChannel);
    ~TestMediaPlayer();
    void Run();
    void Disable();
private:
    void Disabled();
private:
    Semaphore iDisabled;
    Net::DvDevice& iDevice;
    Media::AllocatorInfoLogger iInfoLogger;
    Media::LoggingPipelineObserver iPipelineObserver;
    Media::PipelineManager* iPipeline;
    Media::TrackFactory* iTrackFactory;
    Media::DriverSongcastSender* iDriver;
    Product* iProduct;
    KvpStore* iKvpStore;
    PresetDatabase* iPresetDatabase; // FIXME
};

} // namespace Av
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

static const TChar* kSupportedProtocols = 
    "http-get:*:audio/x-flac:*"
    "http-get:*:audio/wav:*"
    "http-get:*:audio/wave:*"
    "http-get:*:audio/x-wav:*"
    "http-get:*:audio/mpeg:*"
    "http-get:*:audio/x-mpeg:*"
    "http-get:*:audio/mp1:*"
    "http-get:*:audio/aiff:*"
    "http-get:*:audio/x-aiff:*"
    "http-get:*:audio/x-m4a:*"
    "http-get:*:audio/x-ms-wma:*"
    "rtsp-rtp-udp:*:audio/x-ms-wma:*"
    "http-get:*:audio/x-scpls:*"
    "http-get:*:audio/x-mpegurl:*"
    "http-get:*:audio/x-ms-asf:*"
    "http-get:*:audio/x-ms-wax:*"
    "http-get:*:audio/x-ms-wvx:*"
    "http-get:*:video/x-ms-asf:*"
    "http-get:*:video/x-ms-wax:*"
    "http-get:*:video/x-ms-wvx:*"
    "http-get:*:text/xml:*"
    "http-get:*:audio/aac:*"
    "http-get:*:audio/aacp:*"
    "http-get:*:audio/mp4:*"
    "http-get:*:audio/ogg:*"
    "http-get:*:audio/x-ogg:*"
    "http-get:*:application/ogg:*";

// TestMediaPlayer

TestMediaPlayer::TestMediaPlayer(Net::DvStack& aDvStack, Net::DvDevice& aDevice, IStaticDataSource& aStaticDataSource, IPersister& aPersistor, TIpAddress aAdapter, const Brx& aSenderUdn, TUint aSenderChannel)
    : iDisabled("test", 0)
    , iDevice(aDevice)
{
    iKvpStore = new KvpStore(aStaticDataSource, aPersistor);
    iPipeline = new PipelineManager(iInfoLogger, kMaxDriverJiffies);
    iPipeline->AddObserver(iPipelineObserver);
    iTrackFactory = new TrackFactory(iInfoLogger, kTrackCount);
    Environment& env = aDvStack.Env();
    iProduct = new Product(aDevice, *iKvpStore, iInfoLogger);
    iDriver = new DriverSongcastSender(*iPipeline, kMaxDriverJiffies, env, aDevice, aSenderUdn, aSenderChannel, aAdapter, false /*unicast*/);
    iProduct->AddAttribute("Sender");

    iPipeline->Add(Codec::CodecFactory::NewAac());
    iPipeline->Add(Codec::CodecFactory::NewAlac());
    iPipeline->Add(Codec::CodecFactory::NewFlac());
    iPipeline->Add(Codec::CodecFactory::NewMp3());
    iPipeline->Add(Codec::CodecFactory::NewVorbis());
    iPipeline->Add(Codec::CodecFactory::NewWav());
    iPipeline->Add(Codec::CodecFactory::NewWma());
    iPipeline->Add(ProtocolFactory::NewHttp(env));
    iPipeline->Add(ProtocolFactory::NewHttp(env));
    iPipeline->Add(ProtocolFactory::NewHttp(env));
    iPipeline->Add(ProtocolFactory::NewHttp(env));
    iPipeline->Add(ProtocolFactory::NewHttp(env));
    iPipeline->Add(ContentProcessorFactory::NewM3u());
    iPipeline->Add(ContentProcessorFactory::NewM3u());
    iPipeline->Add(ContentProcessorFactory::NewPls());
    iPipeline->Add(ContentProcessorFactory::NewPls());
    iPipeline->Add(ContentProcessorFactory::NewOpml());
    iPipeline->Add(ContentProcessorFactory::NewOpml());

    // Radio stuff - should be factored out to a separate function
    UriProviderSingleTrack* radioUriProvider = new UriProviderSingleTrack("Radio", *iTrackFactory);
    iPipeline->Add(radioUriProvider);
    iPresetDatabase = new PresetDatabase();
    iProduct->AddSource(new SourceRadio(env, aDevice, *iPipeline, *iPresetDatabase, *radioUriProvider, kSupportedProtocols));
    
    iProduct->SetCurrentSource(0);
}

TestMediaPlayer::~TestMediaPlayer()
{
    delete iPresetDatabase; // FIXME
    delete iPipeline;
    delete iDriver;
    delete iTrackFactory;
    delete iProduct;
    delete iKvpStore;
}

void TestMediaPlayer::Run()
{
    iPipeline->Start();
    iProduct->Start();

    Log::Print("\nFull (software) media player\n");
    Log::Print("Intended to be controlled via a separate, standard CP (Kinsky etc.)\n");
    Log::Print("Press 'q' to quit:\n");
    Log::Print("\n");
    while (mygetch() != 'q')
        ;
}

void TestMediaPlayer::Disable()
{
    iDevice.SetDisabled(MakeFunctor(*this, &TestMediaPlayer::Disabled));
    iDisabled.Wait();
}

void TestMediaPlayer::Disabled()
{
    iDisabled.Signal();
}


using namespace OpenHome::TestFramework;

int CDECL main(int aArgc, char* aArgv[])
{
    OptionParser parser;
    OptionString optionUdn("-u", "--udn", Brn("TestMediaPlayer"), "[udn] udn for the upnp device");
    parser.AddOption(&optionUdn);
    OptionString optionName("-n", "--name", Brn("SoftPlayer"), "[name] name of the sender");
    parser.AddOption(&optionName);
    OptionUint optionChannel("-c", "--channel", 0, "[0..65535] sender channel");
    parser.AddOption(&optionChannel);
    OptionUint optionAdapter("-a", "--adapter", 0, "[adapter] index of network adapter to use");
    parser.AddOption(&optionAdapter);
    OptionString optionTuneIn("-n", "--tunein", Brn("linnproducts"), "TuneIn user name");
    parser.AddOption(&optionTuneIn);

    if (!parser.Parse(aArgc, aArgv)) {
        return 1;
    }

    InitialisationParams* initParams = InitialisationParams::Create();
    //Debug::SetLevel(Debug::kMedia);
	Net::Library* lib = new Net::Library(initParams);
    Net::DvStack* dvStack = lib->StartDv();
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    const TUint adapterIndex = optionAdapter.Value();
    if (subnetList->size() <= adapterIndex) {
		Log::Print("ERROR: adapter %u doesn't exist\n", adapterIndex);
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

    DvDevice* device = new DvDeviceStandard(*dvStack, optionUdn.Value());
    device->SetAttribute("Upnp.Domain", "av.openhome.org");
    device->SetAttribute("Upnp.Type", "MediaPlayer");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", optionName.CString());
    device->SetAttribute("Upnp.Manufacturer", "OpenHome");
    device->SetAttribute("Upnp.ModelName", "TestMediaPlayer");
    RamStore* ramStore = new RamStore();
    ramStore->AddItem("Radio.TuneInUserName", optionTuneIn.CString()); // FIXME

    TestMediaPlayer* tmp = new TestMediaPlayer(*dvStack, *device, *ramStore, *ramStore, adapter, optionUdn.Value(), optionChannel.Value());
    device->SetEnabled();
    tmp->Run();
    tmp->Disable();
    delete tmp;
    delete device;
    delete ramStore;
    
    delete lib;

    return 0;
}
