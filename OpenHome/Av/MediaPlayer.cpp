#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/MuteManager.h>
#include <OpenHome/Media/VolumeManager.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Av/ConfigInitialiserVolume.h>
#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Av/ProviderTime.h>
#include <OpenHome/Av/ProviderInfo.h>
#include <OpenHome/Av/ProviderFactory.h>
#include <OpenHome/Av/ProviderVolume.h>
#include <OpenHome/NetworkMonitor.h>
#include <OpenHome/Av/Songcast/ZoneHandler.h>
#include <OpenHome/Configuration/IStore.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Configuration/ProviderConfig.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// MediaPlayer

MediaPlayer::MediaPlayer(Net::DvStack& aDvStack, Net::DvDeviceStandard& aDevice,
                         IStaticDataSource& aStaticDataSource,
                         IStoreReadWrite& aReadWriteStore,
                         IPullableClock* aPullableClock)
    : iDvStack(aDvStack)
    , iDevice(aDevice)
    , iReadWriteStore(aReadWriteStore)
    , iPullableClock(aPullableClock)
    , iConfigProductRoom(NULL)
    , iConfigProductName(NULL)
{
    iInfoLogger = new AllocatorInfoLogger();
    iKvpStore = new KvpStore(aStaticDataSource);
    iTrackFactory = new Media::TrackFactory(*iInfoLogger, kTrackCount);
    iPipeline = new PipelineManager(*iInfoLogger, *iTrackFactory);
    iConfigManager = new ConfigManager(iReadWriteStore);
    iPowerManager = new OpenHome::PowerManager();
    iConfigProductRoom = new ConfigText(*iConfigManager, Product::kConfigIdRoomBase /* + Brx::Empty() */, Product::kMaxRoomBytes, Brn("Main Room")); // FIXME - should this be localised?
    iConfigProductName = new ConfigText(*iConfigManager, Product::kConfigIdNameBase /* + Brx::Empty() */, Product::kMaxNameBytes, Brn("SoftPlayer")); // FIXME - assign appropriate product name
    iProduct = new Av::Product(aDevice, *iKvpStore, iReadWriteStore, *iConfigManager, *iConfigManager, *iPowerManager);
    //iMuteManager = new MuteManager();
    iLeftVolumeHardware = new VolumeSinkLogger("L");   // XXX dummy ...
    iRightVolumeHardware = new VolumeSinkLogger("R");  // XXX volume hardware
    //iVolumeManager = new VolumeManagerDefault(*iLeftVolumeHardware, *iRightVolumeHardware, iReadWriteStore, *iPowerManager);
    iProviderTime = new ProviderTime(aDevice, *iPipeline);
    iProduct->AddAttribute("Time");
    iProviderInfo = new ProviderInfo(aDevice, *iPipeline);
    iProduct->AddAttribute("Info");
    iConfigInitVolume = new ConfigInitialiserVolume(*iConfigManager, iVolumeProfile);
    iProviderVolume = ProviderFactory::NewVolume(*iProduct, aDevice, *iConfigManager, *iConfigManager, *iPowerManager, iVolumeProfile, iVolume, iVolumeLimit, iBalance, iMute);
    iProviderConfig = new ProviderConfig(aDevice, *iConfigManager);
    iProduct->AddAttribute("Configuration");
    iNetworkMonitor = new NetworkMonitor(aDvStack.Env(), aDevice, iDevice.Udn());  // XXX name
}

MediaPlayer::~MediaPlayer()
{
    ASSERT(!iDevice.Enabled());
    delete iPipeline;
    delete iProduct;
    delete iNetworkMonitor;
    delete iProviderConfig;
    delete iProviderTime;
    delete iProviderInfo;
    delete iProviderVolume;
    delete iConfigInitVolume;
    //delete iMuteManager;
    //delete iVolumeManager;
    delete iLeftVolumeHardware;   // XXX dummy ...
    delete iRightVolumeHardware;  // XXX volume hardware
    delete iConfigProductRoom;
    delete iConfigProductName;
    delete iPowerManager;
    delete iConfigManager;
    delete iTrackFactory;
    delete iKvpStore;
    delete iInfoLogger;
}

void MediaPlayer::Quit()
{
    iProduct->Stop();
    iPipeline->Quit();
}

void MediaPlayer::Add(Codec::CodecBase* aCodec)
{
    iPipeline->Add(aCodec);
}

void MediaPlayer::Add(Protocol* aProtocol)
{
    iPipeline->Add(aProtocol);
}

void MediaPlayer::Add(ISource* aSource)
{
    iProduct->AddSource(aSource);
}

void MediaPlayer::AddAttribute(const TChar* aAttribute)
{
    iProduct->AddAttribute(aAttribute);
}

void MediaPlayer::Start()
{
    iConfigManager->Open();
    iConfigManager->Print();
    iConfigManager->DumpToStore();  // debugging
    iPipeline->Start();
    iProduct->Start();
}

Environment& MediaPlayer::Env()
{
    return iDvStack.Env();
}

Net::DvStack& MediaPlayer::DvStack()
{
    return iDvStack;
}

Net::DvDeviceStandard& MediaPlayer::Device()
{
    return iDevice;
}

Media::PipelineManager& MediaPlayer::Pipeline()
{
    return *iPipeline;
}

Media::TrackFactory& MediaPlayer::TrackFactory()
{
    return *iTrackFactory;
}

IReadStore& MediaPlayer::ReadStore()
{
    return *iKvpStore;
}

IStoreReadWrite& MediaPlayer::ReadWriteStore()
{
    return iReadWriteStore;
}

IPullableClock* MediaPlayer::PullableClock()
{
    return iPullableClock;
}

IConfigManagerReader& MediaPlayer::ConfigManagerReader()
{
    return *iConfigManager;
}

IConfigManagerInitialiser& MediaPlayer::ConfigManagerInitialiser()
{
    return *iConfigManager;
}

IPowerManager& MediaPlayer::PowerManager()
{
    return *iPowerManager;
}

Product& MediaPlayer::Product()
{
    return *iProduct;
}

void MediaPlayer::Add(UriProvider* aUriProvider)
{
    iPipeline->Add(aUriProvider);
}

TUint MediaPlayer::VolumeProfile::MaxVolume() const
{
    return 100;
}

TUint MediaPlayer::VolumeProfile::VolumeUnity() const
{
    return 80;
}

TUint MediaPlayer::VolumeProfile::VolumeSteps() const
{
    return MaxVolume();  // [0..100] in steps of 1
}

TUint MediaPlayer::VolumeProfile::VolumeMilliDbPerStep() const
{
    return 1024;
}

TInt MediaPlayer::VolumeProfile::MaxBalance() const
{
    return 15;
}

void MediaPlayer::VolumePrinter::SetVolume(TUint aVolume)
{
    Log::Print("Volume: %u\n", aVolume);
}

void MediaPlayer::BalancePrinter::SetBalance(TInt aBalance)
{
    Log::Print("Balance: %d\n", aBalance);
}

void MediaPlayer::MutePrinter::Mute()
{
    Log::Print("Volume: muted\n");
}

void MediaPlayer::MutePrinter::Unmute()
{
    Log::Print("Volume: unmuted\n");
}
