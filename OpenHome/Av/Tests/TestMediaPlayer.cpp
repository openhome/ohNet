#include "TestMediaPlayer.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/KvpStore.h>
#include "RamStore.h"
#include <OpenHome/Av/UpnpAv/UpnpAv.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Configuration/Tests/ConfigRamStore.h>
#include <OpenHome/Av/Utils/IconDriverSongcastSender.h>
#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Net/Private/ShellCommandDebug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Av/Credentials.h>
#include <OpenHome/Media/Pipeline/Pipeline.h>
#include <OpenHome/Web/WebAppFramework.h>
#include <OpenHome/Web/ConfigUi/ConfigUi.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Av::Test;
using namespace OpenHome::Configuration;
using namespace OpenHome::Media;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Web;

// VolumeProfile

TUint VolumeProfile::VolumeMax() const
{
    return kVolumeMax;
}

TUint VolumeProfile::VolumeDefault() const
{
    return kVolumeDefault;
}

TUint VolumeProfile::VolumeUnity() const
{
    return kVolumeUnity;
}

TUint VolumeProfile::VolumeDefaultLimit() const
{
    return kVolumeDefaultLimit;
}

TUint VolumeProfile::VolumeStep() const
{
    return kVolumeStep;
}

TUint VolumeProfile::VolumeMilliDbPerStep() const
{
    return kVolumeMilliDbPerStep;
}

TUint VolumeProfile::BalanceMax() const
{
    return kBalanceMax;
}

TUint VolumeProfile::FadeMax() const
{
    return kFadeMax;
}


// VolumeSinkLogger

void VolumeSinkLogger::SetVolume(TUint aVolume)
{
    Log::Print("SetVolume: %u\n", aVolume);
}

void VolumeSinkLogger::SetBalance(TInt aBalance)
{
    Log::Print("SetBalance: %d\n", aBalance);
}

void VolumeSinkLogger::SetFade(TInt aFade)
{
    Log::Print("SetFade: %d\n", aFade);
}


// TestMediaPlayer

const Brn TestMediaPlayer::kSongcastSenderIconFileName("SongcastSenderIcon");

TestMediaPlayer::TestMediaPlayer(Net::DvStack& aDvStack, const Brx& aUdn, const TChar* aRoom, const TChar* aProductName,
                                 const Brx& aTuneInPartnerId, const Brx& aTidalId, const Brx& aQobuzIdSecret, const Brx& aUserAgent)
    : iSemShutdown("TMPS", 0)
    , iDisabled("test", 0)
    , iTuneInPartnerId(aTuneInPartnerId)
    , iTidalId(aTidalId)
    , iQobuzIdSecret(aQobuzIdSecret)
    , iUserAgent(aUserAgent)
    , iPullableClock(nullptr)
    , iObservableFriendlyName(new Bws<RaopDevice::kMaxNameBytes>())
    , iTxTimestamper(nullptr)
    , iRxTimestamper(nullptr)
    , iTxTsMapper(nullptr)
    , iRxTsMapper(nullptr)
{
    Bws<256> friendlyName;
    friendlyName.Append(aRoom);
    friendlyName.Append(':');
    friendlyName.Append(aProductName);

    // create UPnP device
    iDevice = new DvDeviceStandard(aDvStack, aUdn, *this);
    iDevice->SetAttribute("Upnp.Domain", "av.openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Source");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", friendlyName.PtrZ());
    iDevice->SetAttribute("Upnp.Manufacturer", "OpenHome");
    iDevice->SetAttribute("Upnp.ModelName", "TestMediaPlayer");

    // create separate UPnP device for standard MediaRenderer
    Bws<256> buf(aUdn);
    buf.Append("-MediaRenderer");
    // The renderer name should be <room name>:<UPnP AV source name> to allow
    // our control point to match the renderer device to the upnp av source.
    //
    // FIXME - will have to allow this to be dynamically changed at runtime if
    // someone changes the name of the UPnP AV source.
    // Disable device -> change name -> re-enable device.
    Bws<256> rendererName(aRoom);
    rendererName.Append(":");
    rendererName.Append(SourceUpnpAv::kSourceName);
    iDeviceUpnpAv = new DvDeviceStandard(aDvStack, buf);
    iDeviceUpnpAv->SetAttribute("Upnp.Domain", "upnp.org");
    iDeviceUpnpAv->SetAttribute("Upnp.Type", "MediaRenderer");
    iDeviceUpnpAv->SetAttribute("Upnp.Version", "1");
    friendlyName.Append(":MediaRenderer");
    iDeviceUpnpAv->SetAttribute("Upnp.FriendlyName", rendererName.PtrZ());
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

    VolumeProfile volumeProfile;
    VolumeConsumer volumeInit;
    volumeInit.SetVolume(iVolumeLogger);
    volumeInit.SetBalance(iVolumeLogger);
    volumeInit.SetFade(iVolumeLogger);

    // create MediaPlayer
    auto pipelineInit = PipelineInitParams::New();
    pipelineInit->SetStarvationMonitorMaxSize(100 * Jiffies::kPerMs); // larger StarvationMonitor size useful for desktop
                                                                      // platforms with slightly unpredictable thread scheduling
    iMediaPlayer = new MediaPlayer(aDvStack, *iDevice, *iRamStore, *iConfigRamStore, pipelineInit,
                                   volumeInit, volumeProfile, aUdn, Brn("Main Room"), Brn("Softplayer"));
    iPipelineObserver = new LoggingPipelineObserver();
    iMediaPlayer->Pipeline().AddObserver(*iPipelineObserver);

    // register our PowerDownUpnp function with the PowerManager
    IPowerManager& powerManager = iMediaPlayer->PowerManager();
    iPowerObserver = powerManager.Register(*this, kPowerPriorityLowest);

    // create a shell
    iShell = new Shell(aDvStack.Env(), 0);
    Log::Print("Shell running on port %u\n", iShell->Port());
    iShellDebug = new ShellCommandDebug(*iShell);

    // Set up config app.
    static const TUint addr = 0;    // Bind to all addresses.
    static const TUint port = 0;    // Bind to whatever free port the OS allocates to the framework server.
    iAppFramework = new WebAppFramework(aDvStack.Env(), addr, port, kMaxUiTabs, kUiSendQueueSize);
}

TestMediaPlayer::~TestMediaPlayer()
{
    delete iAppFramework;
    delete iPowerObserver;
    ASSERT(!iDevice->Enabled());
    delete iMediaPlayer;
    delete iPipelineObserver;
    delete iShellDebug;
    delete iShell;
    delete iDevice;
    delete iDeviceUpnpAv;
    delete iRamStore;
    delete iConfigRamStore;
}

void TestMediaPlayer::SetPullableClock(IPullableClock& aPullableClock)
{
    iPullableClock = &aPullableClock;
}

void TestMediaPlayer::SetSongcastTimestampers(IOhmTimestamper& aTxTimestamper, IOhmTimestamper& aRxTimestamper)
{
    iTxTimestamper = &aTxTimestamper;
    iRxTimestamper = &aRxTimestamper;
}

void TestMediaPlayer::SetSongcastTimestampMappers(IOhmTimestampMapper& aTxTsMapper, IOhmTimestampMapper& aRxTsMapper)
{
    iTxTsMapper = &aTxTsMapper;
    iRxTsMapper = &aRxTsMapper;
}

void TestMediaPlayer::StopPipeline()
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
    iMediaPlayer->Quit();
    iSemShutdown.Signal();
}

void TestMediaPlayer::AddAttribute(const TChar* aAttribute)
{
    iMediaPlayer->AddAttribute(aAttribute);
}

void TestMediaPlayer::Run()
{
    RegisterPlugins(iMediaPlayer->Env());
    AddConfigApp();
    iMediaPlayer->Start();
    InitialiseSubsystems();

    // Debugging for ConfigManager.
    IConfigManager& configManager = iMediaPlayer->ConfigManager();
    configManager.Print();
    configManager.DumpToStore();

    iAppFramework->Start();
    iDevice->SetEnabled();
    iDeviceUpnpAv->SetEnabled();

    iConfigRamStore->Print();

    Log::Print("\nFull (software) media player\n");
    Log::Print("Intended to be controlled via a separate, standard CP (Kazoo etc.)\n");

    Log::Print("Press <q> followed by <enter> to quit:\n");
    Log::Print("\n");
    while (getchar() != 'q')    // getchar catches stdin, getch does not.....
        ;

    //IPowerManager& powerManager = iMediaPlayer->PowerManager();
    //powerManager.PowerDown(); // FIXME - this should probably be replaced by a normal shutdown procedure
    iConfigRamStore->Print();
}

void TestMediaPlayer::RunWithSemaphore()
{
    RegisterPlugins(iMediaPlayer->Env());
    AddConfigApp();
    iMediaPlayer->Start();
    InitialiseSubsystems();

    // Debugging for ConfigManager.
    IConfigManager& configManager = iMediaPlayer->ConfigManager();
    configManager.Print();
    configManager.DumpToStore();

    iAppFramework->Start();
    iDevice->SetEnabled();
    iDeviceUpnpAv->SetEnabled();

    iConfigRamStore->Print();

    iSemShutdown.Wait();    // FIXME - can Run() and RunWithSemaphore() be refactored out? only difference is how they wait for termination signal

    //IPowerManager& powerManager = iMediaPlayer->PowerManager();
    //powerManager.PowerDown(); // FIXME - this should probably be replaced by a normal shutdown procedure
    iConfigRamStore->Print();
}

PipelineManager& TestMediaPlayer::Pipeline()
{
    return iMediaPlayer->Pipeline();
}

DvDeviceStandard* TestMediaPlayer::Device()
{
    return iDevice;
}

void TestMediaPlayer::RegisterPlugins(Environment& aEnv)
{
    // Add codecs
    iMediaPlayer->Add(Codec::CodecFactory::NewFlac(iMediaPlayer->MimeTypes()));
    iMediaPlayer->Add(Codec::CodecFactory::NewWav(iMediaPlayer->MimeTypes()));
    iMediaPlayer->Add(Codec::CodecFactory::NewAiff(iMediaPlayer->MimeTypes()));
    iMediaPlayer->Add(Codec::CodecFactory::NewAifc(iMediaPlayer->MimeTypes()));
    iMediaPlayer->Add(Codec::CodecFactory::NewAac(iMediaPlayer->MimeTypes()));
    iMediaPlayer->Add(Codec::CodecFactory::NewAdts(iMediaPlayer->MimeTypes()));
    iMediaPlayer->Add(Codec::CodecFactory::NewAlac(iMediaPlayer->MimeTypes()));
    iMediaPlayer->Add(Codec::CodecFactory::NewMp3(iMediaPlayer->MimeTypes()));
    iMediaPlayer->Add(Codec::CodecFactory::NewPcm());
    iMediaPlayer->Add(Codec::CodecFactory::NewVorbis(iMediaPlayer->MimeTypes()));

    // Add protocol modules (Radio source can require several stacked Http instances)
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv, iUserAgent));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv, iUserAgent));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv, iUserAgent));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv, iUserAgent));
    iMediaPlayer->Add(ProtocolFactory::NewHttp(aEnv, iUserAgent));
    iMediaPlayer->Add(ProtocolFactory::NewHls(aEnv, iUserAgent));

    // only add Tidal if we have a token to use with login
    if (iTidalId.Bytes() > 0) {
        iMediaPlayer->Add(ProtocolFactory::NewTidal(aEnv, iTidalId, iMediaPlayer->CredentialsManager(), iMediaPlayer->ConfigInitialiser()));
    }
    // ...likewise, only add Qobuz if we have ids for login
    if (iQobuzIdSecret.Bytes() > 0) {
        Parser p(iQobuzIdSecret);
        Brn appId(p.Next(':'));
        Brn appSecret(p.Remaining());
        Log::Print("Qobuz: appId = ");
        Log::Print(appId);
        Log::Print(", appSecret = ");
        Log::Print(appSecret);
        Log::Print("\n");
        iMediaPlayer->Add(ProtocolFactory::NewQobuz(aEnv, appId, appSecret, iMediaPlayer->CredentialsManager(), iMediaPlayer->ConfigInitialiser()));
    }

    // Add sources
    iMediaPlayer->Add(SourceFactory::NewPlaylist(*iMediaPlayer));
    if (iTuneInPartnerId.Bytes() == 0) {
        iMediaPlayer->Add(SourceFactory::NewRadio(*iMediaPlayer, iPullableClock));
    }
    else {
        iMediaPlayer->Add(SourceFactory::NewRadio(*iMediaPlayer, iPullableClock, iTuneInPartnerId));
    }
    iMediaPlayer->Add(SourceFactory::NewUpnpAv(*iMediaPlayer, *iDeviceUpnpAv));

    Bwh hostName(iDevice->Udn().Bytes()+1); // space for null terminator
    hostName.Replace(iDevice->Udn());
    Bws<12> macAddr;
    MacAddrFromUdn(aEnv, macAddr);
    const TChar* friendlyName;
    iDevice->GetAttribute("Upnp.FriendlyName", &friendlyName);
    iObservableFriendlyName.Replace(Brn(friendlyName));
    iMediaPlayer->Add(SourceFactory::NewRaop(*iMediaPlayer, iPullableClock, hostName.PtrZ(), iObservableFriendlyName, macAddr));

    iMediaPlayer->Add(SourceFactory::NewReceiver(*iMediaPlayer, iPullableClock, iTxTimestamper, iTxTsMapper, iRxTimestamper, iRxTsMapper, kSongcastSenderIconFileName));
}

void TestMediaPlayer::InitialiseSubsystems()
{
}

void TestMediaPlayer::CreateConfigApp(const std::vector<const Brx*>& aSources, const Brx& aResourceDir, TUint aMaxUiTabs, TUint aMaxSendQueueSize)
{
    iConfigApp = new ConfigAppMediaPlayer(iMediaPlayer->ConfigManager(), aSources, Brn("Softplayer"), aResourceDir, aMaxUiTabs, aMaxSendQueueSize);
}

void TestMediaPlayer::WriteResource(const Brx& aUriTail, TIpAddress /*aInterface*/, std::vector<char*>& /*aLanguageList*/, IResourceWriter& aResourceWriter)
{
    if (aUriTail == kSongcastSenderIconFileName) {
        aResourceWriter.WriteResourceBegin(sizeof(kIconDriverSongcastSender), kIconDriverSongcastSenderMimeType);
        aResourceWriter.WriteResource(kIconDriverSongcastSender, sizeof(kIconDriverSongcastSender));
        aResourceWriter.WriteResourceEnd();
    }
}

void TestMediaPlayer::PowerUp()
{
    // FIXME - enable UPnP devices here?
    // - would need to account for two-stage create->run process either by
    //  - setting a flag here which is checked in Run() OR
    //  - registering with IPowerManager in Run() call
    //iDevice->SetEnabled();
    //iDeviceUpnpAv->SetEnabled();
}

void TestMediaPlayer::PowerDown()
{
    Log::Print("TestMediaPlayer::PowerDown\n");
    PowerDownDisable(*iDevice);
    PowerDownDisable(*iDeviceUpnpAv);
}

//void TestMediaPlayer::Add(IWebApp* aWebApp, FunctorPresentationUrl aFunctor)
//{
//    // Last added WebApp will be set as presentation page.
//    iAppFramework->Add(aWebApp, aFunctor);
//}

void TestMediaPlayer::AddConfigApp()
{
    std::vector<const Brx*> sourcesBufs;
    Product& product = iMediaPlayer->Product();
    for (TUint i=0; i<product.SourceCount(); i++) {
        Bws<ISource::kMaxSystemNameBytes> systemName;
        Bws<ISource::kMaxSourceNameBytes> name;
        Bws<ISource::kMaxSourceTypeBytes> type;
        TBool visible;
        product.GetSourceDetails(i, systemName, type, name, visible);
        sourcesBufs.push_back(new Brh(systemName));
    }
    // FIXME - take resource dir as param or copy res dir to build dir
    CreateConfigApp(sourcesBufs, Brn("res/"), kMaxUiTabs, kUiSendQueueSize);    // Initialises iConfigApp.
    iAppFramework->Add(iConfigApp, MakeFunctorGeneric(*this, &TestMediaPlayer::PresentationUrlChanged));
    //Add(iConfigApp, MakeFunctorGeneric(*this, &TestMediaPlayer::PresentationUrlChanged));    // iAppFramework takes ownership
    for (TUint i=0;i<sourcesBufs.size(); i++) {
        delete sourcesBufs[i];
    }
}

TUint TestMediaPlayer::Hash(const Brx& aBuf)
{
    TUint hash = 0;
    for (TUint i=0; i<aBuf.Bytes(); i++) {
        hash += aBuf[i];
    }
    return hash;
}

void TestMediaPlayer::GenerateMacAddr(Environment& aEnv, TUint aSeed, Bwx& aMacAddr)
{
    // Generate a 48-bit, 12-byte hex string.
    // Method:
    // - Generate two random numbers in the range 0 - 2^24
    // - Get the hex representation of these numbers
    // - Combine the two hex representations into the output buffer, aMacAddr
    const TUint maxLimit = 0x01000000;
    Bws<8> macBuf1;
    Bws<8> macBuf2;

    aEnv.SetRandomSeed(aSeed);
    TUint mac1 = aEnv.Random(maxLimit, 0);
    TUint mac2 = aEnv.Random(maxLimit, 0);

    Ascii::AppendHex(macBuf1, mac1);
    Ascii::AppendHex(macBuf2, mac2);

    aMacAddr.Append(macBuf1.Split(2));
    aMacAddr.Append(macBuf2.Split(2));
}

void TestMediaPlayer::MacAddrFromUdn(Environment& aEnv, Bwx& aMacAddr)
{
    TUint hash = Hash(iDevice->Udn());
    GenerateMacAddr(aEnv, hash, aMacAddr);
}

void TestMediaPlayer::PresentationUrlChanged(const Brx& aUrl)
{
    if (!iDevice->Enabled()) {
        // FIXME - can only set Product attribute once (meaning no updates on subnet change)
        const TBool firstChange = (iPresentationUrl.Bytes() == 0);
        iPresentationUrl.Replace(aUrl);
        iDevice->SetAttribute("Upnp.PresentationUrl", iPresentationUrl.PtrZ());
        if (firstChange) {
            Bws<128> configAtt("App:Config=");
            configAtt.Append(iPresentationUrl);
            iMediaPlayer->Product().AddAttribute(configAtt);
        }
    }
}

void TestMediaPlayer::PowerDownDisable(DvDevice& aDevice)
{
    if (aDevice.Enabled()) {
        aDevice.SetDisabled(MakeFunctor(*this, &TestMediaPlayer::PowerDownUpnpCallback));
    }
}

void TestMediaPlayer::PowerDownUpnpCallback()
{
    // do nothing; only exists to avoid lengthy Upnp shutdown waits during power fail
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


// TestMediaPlayerInit

OpenHome::Net::Library* TestMediaPlayerInit::CreateLibrary(TBool aLoopback, TUint aAdapter)
{
    InitialisationParams* initParams = InitialisationParams::Create();
    initParams->SetDvEnableBonjour();
    if (aLoopback == true) {
        initParams->SetUseLoopbackNetworkAdapter();
    }

    Debug::SetLevel(Debug::kPipeline | Debug::kSources | Debug::kMedia);
    Net::Library* lib = new Net::Library(initParams);
    //Net::DvStack* dvStack = lib->StartDv();
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    const TUint adapterIndex = aAdapter;
    if (subnetList->size() <= adapterIndex) {
        Log::Print("ERROR: adapter %u doesn't exist\n", adapterIndex);
        ASSERTS();
    }
    Log::Print ("adapter list:\n");
    for (unsigned i=0; i<subnetList->size(); ++i) {
        TIpAddress addr = (*subnetList)[i]->Address();
        Log::Print ("  %d: %d.%d.%d.%d\n", i, addr&0xff, (addr>>8)&0xff, (addr>>16)&0xff, (addr>>24)&0xff);
    }
    //TIpAddress address = (*subnetList)[adapterIndex]->Address();
    TIpAddress subnet = (*subnetList)[adapterIndex]->Subnet();
    Library::DestroySubnetList(subnetList);
    lib->SetCurrentSubnet(subnet);
    Log::Print("using subnet %d.%d.%d.%d\n", subnet&0xff, (subnet>>8)&0xff, (subnet>>16)&0xff, (subnet>>24)&0xff);
    return lib;
}

void TestMediaPlayerInit::SeedRandomNumberGenerator(Environment& aEnv, const Brx& aRoom, TIpAddress aAddress, DviServerUpnp& aServer)
{
    if (aRoom == Brx::Empty()) {
        Log::Print("ERROR: room must be set\n");
        ASSERTS();
    }
    // Re-seed random number generator with hash of (unique) room name + UPnP
    // device server port to avoid UDN clashes.
    TUint port = aServer.Port(aAddress);
    Log::Print("UPnP DV server using port: %u\n", port);
    TUint hash = 0;
    for (TUint i=0; i<aRoom.Bytes(); i++) {
        hash += aRoom[i];
    }
    hash += port;
    Log::Print("Seeding random number generator with: %u\n", hash);
    aEnv.SetRandomSeed(hash);
}

void TestMediaPlayerInit::AppendUniqueId(Environment& aEnv, const Brx& aUserUdn, const Brx& aDefaultUdn, Bwh& aOutput)
{
    if (aUserUdn.Bytes() == 0) {
        if (aOutput.MaxBytes() < aDefaultUdn.Bytes()) {
            aOutput.Grow(aDefaultUdn.Bytes());
        }
        aOutput.Replace(aDefaultUdn);
        RandomiseUdn(aEnv, aOutput);
    }
    else {
        if (aUserUdn.Bytes() > aOutput.MaxBytes()) {
            aOutput.Grow(aUserUdn.Bytes());
        }
        aOutput.Replace(aUserUdn);
    }
}
