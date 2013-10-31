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

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// MediaPlayer

MediaPlayer::MediaPlayer(Net::DvStack& aDvStack, Net::DvDeviceStandard& aDevice,
                         TUint aDriverMaxJiffies, IStaticDataSource& aStaticDataSource,
                         IStoreReadWrite& aReadWriteStore, IConfigurationManager& aConfigManager,
                         IPowerManager& aPowerManager)
    : iDvStack(aDvStack)
    , iDevice(aDevice)
    , iReadWriteStore(aReadWriteStore)
    , iConfigManager(aConfigManager)
    , iPowerManager(aPowerManager)
{
    iInfoLogger = new AllocatorInfoLogger();
    iKvpStore = new KvpStore(aStaticDataSource);
    iPipeline = new PipelineManager(*iInfoLogger, aDriverMaxJiffies);
    iTrackFactory = new Media::TrackFactory(*iInfoLogger, kTrackCount);
    iProduct = new Product(aDevice, *iKvpStore, iReadWriteStore, iConfigManager, iPowerManager, *iInfoLogger);
    iMuteManager = new MuteManager();
    iLeftVolumeHardware = new VolumeSinkLogger("L");   // XXX dummy ...
    iRightVolumeHardware = new VolumeSinkLogger("R");  // XXX volume hardware
    iVolumeManager = new VolumeManagerDefault(*iLeftVolumeHardware, *iRightVolumeHardware, iReadWriteStore, iPowerManager);
    iTime = new ProviderTime(aDevice, *iPipeline);
    iProduct->AddAttribute("Time");
    iInfo = new ProviderInfo(aDevice, *iPipeline);
    iProduct->AddAttribute("Info");
    iVolume = new ProviderVolume(aDevice, *iMuteManager, *iVolumeManager);
    iProduct->AddAttribute("Volume");
    iNetworkMonitor = new Net::NetworkMonitor(aDvStack.Env(), aDevice, iDevice.Udn());  // XXX name
}

MediaPlayer::~MediaPlayer()
{
    ASSERT(!iDevice.Enabled());
    delete iPipeline;
    delete iProduct;
    delete iNetworkMonitor;
    delete iTime;
    delete iInfo;
    delete iVolume;
    delete iMuteManager;
    delete iVolumeManager;
    delete iLeftVolumeHardware;   // XXX dummy ...
    delete iRightVolumeHardware;  // XXX volume hardware
    delete iKvpStore;
    delete iInfoLogger;
    delete iTrackFactory;
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
    iProduct->SetCurrentSource(0); // FIXME - could be available (and left) to client code
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

IConfigurationManager& MediaPlayer::ConfigManager()
{
    return iConfigManager;
}

IPowerManager& MediaPlayer::PowerManager()
{
    return iPowerManager;
}

void MediaPlayer::Add(UriProvider* aUriProvider)
{
    iPipeline->Add(aUriProvider);
}
