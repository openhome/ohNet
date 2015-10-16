#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/MuteManager.h>
#include <OpenHome/Av/VolumeManager.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Av/ProviderTime.h>
#include <OpenHome/Av/ProviderInfo.h>
#include <OpenHome/Av/ProviderFactory.h>
#include <OpenHome/Av/Songcast/ZoneHandler.h>
#include <OpenHome/Configuration/IStore.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Configuration/ProviderConfig.h>
#include <OpenHome/Av/Credentials.h>
#include <OpenHome/Media/MimeTypeList.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// MediaPlayer

MediaPlayer::MediaPlayer(Net::DvStack& aDvStack, Net::DvDeviceStandard& aDevice,
                         Net::IShell& aShell,
                         IStaticDataSource& aStaticDataSource,
                         IStoreReadWrite& aReadWriteStore,
                         PipelineInitParams* aPipelineInitParams,
                         VolumeConsumer& aVolumeConsumer, IVolumeProfile& aVolumeProfile,
                         const Brx& aEntropy,
                         const Brx& aDefaultRoom,
                         const Brx& aDefaultName)
    : iDvStack(aDvStack)
    , iDevice(aDevice)
    , iReadWriteStore(aReadWriteStore)
    , iConfigProductRoom(nullptr)
    , iConfigProductName(nullptr)
{
    iInfoLogger = new AllocatorInfoLogger();
    iKvpStore = new KvpStore(aStaticDataSource);
    iTrackFactory = new Media::TrackFactory(*iInfoLogger, kTrackCount);
    iPipeline = new PipelineManager(aPipelineInitParams, *iInfoLogger, *iTrackFactory, iMimeTypes, aShell);
    iConfigManager = new Configuration::ConfigManager(iReadWriteStore);
    iPowerManager = new OpenHome::PowerManager();
    iConfigProductRoom = new ConfigText(*iConfigManager, Product::kConfigIdRoomBase /* + Brx::Empty() */, Product::kMaxRoomBytes, aDefaultRoom);
    iConfigProductName = new ConfigText(*iConfigManager, Product::kConfigIdNameBase /* + Brx::Empty() */, Product::kMaxNameBytes, aDefaultName);
    iProduct = new Av::Product(aDevice, *iKvpStore, iReadWriteStore, *iConfigManager, *iConfigManager, *iPowerManager);
    iVolumeConfig = new VolumeConfig(aReadWriteStore, *iConfigManager, *iPowerManager, aVolumeProfile);
    iVolumeManager = new OpenHome::Av::VolumeManager(aVolumeConsumer, iPipeline, *iVolumeConfig, aDevice, *iProduct, *iConfigManager);
    iCredentials = new Credentials(aDvStack.Env(), aDevice, aReadWriteStore, aEntropy, *iConfigManager);
    iProduct->AddAttribute("Credentials");
    iProviderTime = new ProviderTime(aDevice, *iPipeline);
    iProduct->AddAttribute("Time");
    iProviderInfo = new ProviderInfo(aDevice, *iPipeline);
    iProduct->AddAttribute("Info");
    iProviderConfig = new ProviderConfig(aDevice, *iConfigManager);
    iProduct->AddAttribute("Configuration");
    //iTransportControl = new TransportControl(aDevice, *iPipeline);
    //iProduct->AddAttribute("TransportControl");
}

MediaPlayer::~MediaPlayer()
{
    ASSERT(!iDevice.Enabled());
    delete iPipeline;
    delete iCredentials;
    delete iProduct;
    delete iVolumeManager;
    delete iVolumeConfig;
    //delete iTransportControl;
    delete iProviderConfig;
    delete iProviderTime;
    delete iProviderInfo;
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
    iCredentials->Start();
    iMimeTypes.Start();
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

IConfigManager& MediaPlayer::ConfigManager()
{
    return *iConfigManager;
}

IConfigInitialiser& MediaPlayer::ConfigInitialiser()
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

IVolumeManager& MediaPlayer::VolumeManager()
{
    ASSERT(iVolumeManager != nullptr);
    return *iVolumeManager;
}

Credentials& MediaPlayer::CredentialsManager()
{
    ASSERT(iCredentials != nullptr);
    return *iCredentials;
}

MimeTypeList& MediaPlayer::MimeTypes()
{
    return iMimeTypes;
}

void MediaPlayer::Add(UriProvider* aUriProvider)
{
    iPipeline->Add(aUriProvider);
}

