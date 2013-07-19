#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/DriverSongcastSender.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/KvpStore.h>
#include "RamStore.h"
#include <OpenHome/Av/Product.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Av/Source.h> // FIXME - see #169

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
    static const TUint kRaopDiscoveryPort = 5048;
public:
    TestMediaPlayer(Net::DvStack& aDvStack, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aFriendlyName, TUint aSenderChannel, const TChar* aTuneInUserName);
    ~TestMediaPlayer();
    void Run();
    TBool TryDisable(Net::DvDevice& aDevice);
private:
    void Disabled();
private:
    Semaphore iDisabled;
    MediaPlayer* iMediaPlayer;
    Net::DvDevice* iDevice;
    Net::DvDevice* iDeviceUpnpAv;
    RamStore* iRamStore;
    Media::DriverSongcastSender* iDriver;
    ISource* iSourceUpnp; // FIXME - see #169
};

} // namespace Av
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// TestMediaPlayer

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

TestMediaPlayer::TestMediaPlayer(Net::DvStack& aDvStack, TIpAddress aAdapter, const Brx& aUdn, const TChar* aFriendlyName, TUint aSenderChannel, const TChar* aTuneInUserName)
    : iDisabled("test", 0)
{
    // create UPnP device
    iDevice = new DvDeviceStandard(aDvStack, aUdn);
    iDevice->SetAttribute("Upnp.Domain", "av.openhome.org");
    iDevice->SetAttribute("Upnp.Type", "MediaPlayer");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", aFriendlyName);
    iDevice->SetAttribute("Upnp.Manufacturer", "OpenHome");
    iDevice->SetAttribute("Upnp.ModelName", "TestMediaPlayer");

    // create separate UPnP device for standard MediaRenderer
    Bwh udn("UpnpErrorTests");
    Bws<256> buf(aUdn);
    buf.Append("-MediaRenderer");
    iDeviceUpnpAv = new DvDeviceStandard(aDvStack, buf);
    iDeviceUpnpAv->SetAttribute("Upnp.Domain", "upnp.org");
    iDeviceUpnpAv->SetAttribute("Upnp.Type", "MediaRenderer");
    iDeviceUpnpAv->SetAttribute("Upnp.Version", "1");
    buf.Replace(aFriendlyName);
    buf.Append("-MediaRenderer");
    iDeviceUpnpAv->SetAttribute("Upnp.FriendlyName", buf.PtrZ());
    iDeviceUpnpAv->SetAttribute("Upnp.Manufacturer", "OpenHome");
    iDeviceUpnpAv->SetAttribute("Upnp.ModelName", "TestMediaPlayer");


    // create read/write store.  This creates a number of static (constant) entries automatically
    iRamStore = new RamStore();
    // add a single user (runtime changeable) setting
    iRamStore->AddItem("Radio.TuneInUserName", aTuneInUserName);

    // create MediaPlayer
    iMediaPlayer = new MediaPlayer(aDvStack, *iDevice, kMaxDriverJiffies, *iRamStore, *iRamStore);

    // Create driver & attach it to the pipeline
    Environment& env = iMediaPlayer->Env();
    iDriver = new DriverSongcastSender(iMediaPlayer->Pipeline(), kMaxDriverJiffies, env, *iDevice, aUdn, aSenderChannel, aAdapter, false /*unicast*/);
    iMediaPlayer->AddAttribute("Sender");

    // Add codecs
    iMediaPlayer->Add(Codec::CodecFactory::NewAac());
    iMediaPlayer->Add(Codec::CodecFactory::NewAlac());
    iMediaPlayer->Add(Codec::CodecFactory::NewAdts());
    iMediaPlayer->Add(Codec::CodecFactory::NewFlac());
    iMediaPlayer->Add(Codec::CodecFactory::NewRaop());
    iMediaPlayer->Add(Codec::CodecFactory::NewVorbis());
    iMediaPlayer->Add(Codec::CodecFactory::NewWav());

    // Add protocol modules (Radio source can require several stacked Http instances)
    iMediaPlayer->Add(ProtocolFactory::NewHttp(env));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(env));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(env));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(env));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(env));

    // Add content processors (mainly required for Radio)
    iMediaPlayer->Add(ContentProcessorFactory::NewM3u());
    iMediaPlayer->Add(ContentProcessorFactory::NewM3u());
    iMediaPlayer->Add(ContentProcessorFactory::NewPls());
    iMediaPlayer->Add(ContentProcessorFactory::NewPls());
    iMediaPlayer->Add(ContentProcessorFactory::NewOpml());
    iMediaPlayer->Add(ContentProcessorFactory::NewOpml());
    iMediaPlayer->Add(ContentProcessorFactory::NewAsx());
    iMediaPlayer->Add(ContentProcessorFactory::NewAsx());

    // Add sources
    iMediaPlayer->Add(SourceFactory::NewPlaylist(*iMediaPlayer, kSupportedProtocols));
    iMediaPlayer->Add(SourceFactory::NewRadio(*iMediaPlayer, kSupportedProtocols));
    iSourceUpnp = SourceFactory::NewUpnpAv(*iMediaPlayer, *iDeviceUpnpAv, kSupportedProtocols);
    iMediaPlayer->Add(SourceFactory::NewRaop(*iMediaPlayer, aUdn, kRaopDiscoveryPort));   // FIXME - name should be product name

    iDevice->SetEnabled();
    iDeviceUpnpAv->SetEnabled();
    //iProduct->SetCurrentSource(0);
}

TestMediaPlayer::~TestMediaPlayer()
{
    TUint waitCount = 0;
    if (TryDisable(*iDevice)) {
        waitCount++;
    }
    if (TryDisable(*iDeviceUpnpAv)) {
        waitCount++;
    }
    while (waitCount > 0) {
        iDisabled.Wait();
        waitCount--;
    }
    delete iSourceUpnp;
    delete iMediaPlayer;
    delete iDriver;
    delete iDevice;
    delete iDeviceUpnpAv;
    delete iRamStore;
}

void TestMediaPlayer::Run()
{
    iMediaPlayer->Start();

    Log::Print("\nFull (software) media player\n");
    Log::Print("Intended to be controlled via a separate, standard CP (Kinsky etc.)\n");
    Log::Print("Press 'q' to quit:\n");
    Log::Print("\n");
    while (mygetch() != 'q')
        ;
}

TBool TestMediaPlayer::TryDisable(DvDevice& aDevice)
{
    if (aDevice.Enabled()) {
        aDevice.SetDisabled(MakeFunctor(*this, &TestMediaPlayer::Disabled));
        return true;
    }
    return false;
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
    initParams->SetDvEnableBonjour();
//    initParams->SetUseLoopbackNetworkAdapter();
    //Debug::SetLevel(Debug::kDvEvent);
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

    TestMediaPlayer* tmp = new TestMediaPlayer(*dvStack, adapter, optionUdn.Value(), optionName.CString(), optionChannel.Value(), optionTuneIn.CString());
    tmp->Run();
    delete tmp;
    
    delete lib;

    return 0;
}
