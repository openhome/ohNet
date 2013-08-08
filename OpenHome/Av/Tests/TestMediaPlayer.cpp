#include "TestMediaPlayer.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/KvpStore.h>
#include "RamStore.h"
#include <OpenHome/Av/Source.h> // FIXME - see #169

int mygetch();


using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Av::Test;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// TestMediaPlayer

const Brn TestMediaPlayer::kSupportedProtocols( 
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
    "http-get:*:application/ogg:*");

TestMediaPlayer::TestMediaPlayer(Net::DvStack& aDvStack, const Brx& aUdn, const TChar* aRoom, const TChar* aProductName, TUint aMaxDriverJiffies, const TChar* aTuneInUserName)
    : iDisabled("test", 0)
{
    Bws<256> friendlyName;
    friendlyName.Append(aRoom);
    friendlyName.Append(':');
    friendlyName.Append(aProductName);

    // create UPnP device
    iDevice = new DvDeviceStandard(aDvStack, aUdn);
    iDevice->SetAttribute("Upnp.Domain", "av.openhome.org");
    iDevice->SetAttribute("Upnp.Type", "MediaPlayer");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", friendlyName.PtrZ());
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
    friendlyName.Append("-MediaRenderer");
    iDeviceUpnpAv->SetAttribute("Upnp.FriendlyName", friendlyName.PtrZ());
    iDeviceUpnpAv->SetAttribute("Upnp.Manufacturer", "OpenHome");
    iDeviceUpnpAv->SetAttribute("Upnp.ModelName", "TestMediaPlayer");

    // create read/write store.  This creates a number of static (constant) entries automatically
    iRamStore = new RamStore();

    // FIXME - available store keys should be listed somewhere
    iRamStore->AddItem("Product.Room", aRoom);
    iRamStore->AddItem("Product.Name", aProductName);
    iRamStore->AddItem("Radio.TuneInUserName", aTuneInUserName);

    // create MediaPlayer
    iMediaPlayer = new MediaPlayer(aDvStack, *iDevice, aMaxDriverJiffies, *iRamStore, *iRamStore);

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

void TestMediaPlayer::AddAttribute(const TChar* aAttribute)
{
    iMediaPlayer->AddAttribute(aAttribute);
}

void TestMediaPlayer::Run()
{
    iDevice->SetEnabled();
    iDeviceUpnpAv->SetEnabled();
    RegisterPlugins(iMediaPlayer->Env());
    iMediaPlayer->Start();

    Log::Print("\nFull (software) media player\n");
    Log::Print("Intended to be controlled via a separate, standard CP (Kinsky etc.)\n");
    Log::Print("Press 'q' to quit:\n");
    Log::Print("\n");
    while (mygetch() != 'q')
        ;
}

PipelineManager& TestMediaPlayer::Pipeline()
{
    return iMediaPlayer->Pipeline();
}

DvDevice* TestMediaPlayer::Device()
{
    return iDevice;
}

void TestMediaPlayer::RegisterPlugins(Environment& aEnv)
{
    // Add codecs
    iMediaPlayer->Add(Codec::CodecFactory::NewAac());
    iMediaPlayer->Add(Codec::CodecFactory::NewAlac());
    iMediaPlayer->Add(Codec::CodecFactory::NewAdts());
    iMediaPlayer->Add(Codec::CodecFactory::NewFlac());
    iMediaPlayer->Add(Codec::CodecFactory::NewRaop());
    iMediaPlayer->Add(Codec::CodecFactory::NewVorbis());
    iMediaPlayer->Add(Codec::CodecFactory::NewWav());

    // Add protocol modules (Radio source can require several stacked Http instances)
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv));

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
    iMediaPlayer->Add(SourceFactory::NewRaop(*iMediaPlayer, iDevice->Udn(), kRaopDiscoveryPort));   // FIXME - name should be product name
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
