#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/Tests/AllocatorInfoLogger.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/MuteManager.h>
#include <OpenHome/Media/VolumeManager.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Av/ProviderTime.h>
#include <OpenHome/Av/ProviderInfo.h>
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
                         TUint aDriverMaxJiffies, IStaticDataSource& aStaticDataSource,
                         IStoreReadWrite& aReadWriteStore)
    : iDvStack(aDvStack)
    , iDevice(aDevice)
    , iReadWriteStore(aReadWriteStore)
    , iConfigProductRoom(NULL)
    , iConfigProductName(NULL)
{
    iInfoLogger = new AllocatorInfoLogger();
    iKvpStore = new KvpStore(aStaticDataSource);
    iTrackFactory = new Media::TrackFactory(*iInfoLogger, kTrackCount);
    iPipeline = new PipelineManager(*iInfoLogger, *iTrackFactory, aDriverMaxJiffies);
    iConfigManager = new ConfigManager(iReadWriteStore);
    iPowerManager = new OpenHome::PowerManager();
    iConfigProductRoom = new ConfigText(*iConfigManager, Product::kConfigIdRoomBase /* + Brx::Empty() */, Product::kMaxRoomBytes, Brn("Main Room")); // FIXME - should this be localised?
    iConfigProductName = new ConfigText(*iConfigManager, Product::kConfigIdNameBase /* + Brx::Empty() */, Product::kMaxNameBytes, Brn("SoftPlayer")); // FIXME - assign appropriate product name
    iProduct = new Product(aDevice, *iKvpStore, iReadWriteStore, *iConfigManager, *iConfigManager, *iPowerManager, Brx::Empty());
    iMuteManager = new MuteManager();
    iLeftVolumeHardware = new VolumeSinkLogger("L");   // XXX dummy ...
    iRightVolumeHardware = new VolumeSinkLogger("R");  // XXX volume hardware
    iVolumeManager = new VolumeManagerDefault(*iLeftVolumeHardware, *iRightVolumeHardware, iReadWriteStore, *iPowerManager);
    iTime = new ProviderTime(aDevice, *iPipeline);
    iProduct->AddAttribute("Time");
    iInfo = new ProviderInfo(aDevice, *iPipeline);
    iProduct->AddAttribute("Info");
    iVolume = new ProviderVolume(aDevice, *iMuteManager, *iVolumeManager);
    iProduct->AddAttribute("Volume");
    iProviderConfig = new ProviderConfig(aDevice, *iConfigManager);
    iProduct->AddAttribute("Configuration");
    iNetworkMonitor = new Net::NetworkMonitor(aDvStack.Env(), aDevice, iDevice.Udn());  // XXX name
}

MediaPlayer::~MediaPlayer()
{
    ASSERT(!iDevice.Enabled());
    delete iPipeline;
    delete iProduct;
    delete iNetworkMonitor;
    delete iProviderConfig;
    delete iTime;
    delete iInfo;
    delete iVolume;
    delete iMuteManager;
    delete iVolumeManager;
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

void MediaPlayer::Add(ContentProcessor* aContentProcessor)
{
    iPipeline->Add(aContentProcessor);
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
    iConfigManager->Close();
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

IConfigManagerReader& MediaPlayer::ConfigManagerReader()
{
    return *iConfigManager;
}

IConfigManagerWriter& MediaPlayer::ConfigManagerWriter()
{
    return *iConfigManager;
}

IPowerManager& MediaPlayer::PowerManager()
{
    return *iPowerManager;
}

void MediaPlayer::Add(UriProvider* aUriProvider)
{
    iPipeline->Add(aUriProvider);
}
