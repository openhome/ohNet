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
#include <OpenHome/Configuration/ConfigManager.h>

int mygetch();


using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Av::Test;
using namespace OpenHome::Configuration;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// TestMediaPlayer

TestMediaPlayer::TestMediaPlayer(Net::DvStack& aDvStack, const Brx& aUdn, const TChar* aRoom, const TChar* aProductName, TUint aMaxDriverJiffies, const TChar* aTuneInUserName)
    : iDisabled("test", 0)
    , iSongcastTimestamper(aDvStack.Env())
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
    friendlyName.Append(":MediaRenderer");
    iDeviceUpnpAv->SetAttribute("Upnp.FriendlyName", friendlyName.PtrZ());
    iDeviceUpnpAv->SetAttribute("Upnp.Manufacturer", "OpenHome");
    iDeviceUpnpAv->SetAttribute("Upnp.ModelName", "TestMediaPlayer");

    // create read/write store.  This creates a number of static (constant) entries automatically
    // FIXME - to be removed; this only exists to populate static data
    iRamStore = new RamStore();

    // create a read/write store using the new config framework
    iConfigRamStore = new ConfigRamStore();

    // FIXME - available store keys should be listed somewhere
    iConfigRamStore->Write(Brn("Product.Room"), Brn(aRoom));
    iConfigRamStore->Write(Brn("Product.Name"), Brn(aProductName));
    iConfigRamStore->Write(Brn("Radio.TuneInUserName"), Brn(aTuneInUserName));
    iConfigRamStore->Print();

    // create MediaPlayer
    iMediaPlayer = new MediaPlayer(aDvStack, *iDevice, aMaxDriverJiffies, *iRamStore, *iConfigRamStore);
    iPipelineObserver = new LoggingPipelineObserver();
    iMediaPlayer->Pipeline().AddObserver(*iPipelineObserver);

    //iProduct->SetCurrentSource(0);
}

TestMediaPlayer::~TestMediaPlayer()
{
    ASSERT(!iDevice->Enabled());
    delete iDevice;
    delete iDeviceUpnpAv;
    delete iRamStore;
    delete iConfigRamStore;
}

void TestMediaPlayer::DestroyPipeline()
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
    delete iPipelineObserver;
}

void TestMediaPlayer::AddAttribute(const TChar* aAttribute)
{
    iMediaPlayer->AddAttribute(aAttribute);
}

void TestMediaPlayer::Run()
{
    RegisterPlugins(iMediaPlayer->Env());
    iDevice->SetEnabled();
    iDeviceUpnpAv->SetEnabled();
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
    const Brn kSupportedProtocols( 
        "http-get:*:audio/x-flac:*,"   // Flac
        "http-get:*:audio/wav:*,"      // Wav
        "http-get:*:audio/wave:*,"     // Wav
        "http-get:*:audio/x-wav:*,"    // Wav
        "http-get:*:audio/aiff:*,"     // AIFF codec not implemented
        "http-get:*:audio/x-aiff:*,"   // AIFF codec not implemented
        "http-get:*:audio/x-m4a:*,"    // Alac
        "http-get:*:audio/x-scpls:*,"  // M3u (content processor)
        "http-get:*:text/xml:*,"       // Opml ??  (content processor)
        "http-get:*:audio/aac:*,"      // Aac
        "http-get:*:audio/aacp:*,"     // Aac
        "http-get:*:audio/mp4:*,"      // Mpeg4 (container)
        "http-get:*:audio/ogg:*,"      // Vorbis
        "http-get:*:audio/x-ogg:*,"    // Vorbis
        "http-get:*:application/ogg:*" // Vorbis
        );
    DoRegisterPlugins(aEnv, kSupportedProtocols);
}

void TestMediaPlayer::DoRegisterPlugins(Environment& aEnv, const Brx& aSupportedProtocols)
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
    iMediaPlayer->Add(SourceFactory::NewPlaylist(*iMediaPlayer, aSupportedProtocols));
    iMediaPlayer->Add(SourceFactory::NewRadio(*iMediaPlayer, aSupportedProtocols));
    iSourceUpnp = SourceFactory::NewUpnpAv(*iMediaPlayer, *iDeviceUpnpAv, aSupportedProtocols);
    Bwh hostName(iDevice->Udn().Bytes()+1); // space for null terminator
    hostName.Replace(iDevice->Udn());
    iMediaPlayer->Add(SourceFactory::NewRaop(*iMediaPlayer, hostName.PtrZ(), iDevice->Udn(), kRaopDiscoveryPort));   // FIXME - name should be product name
    iMediaPlayer->Add(SourceFactory::NewReceiver(*iMediaPlayer, iSongcastTimestamper)); // FIXME - will want to replace timestamper with access to a driver on embedded platforms
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
