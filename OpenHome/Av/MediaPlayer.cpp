#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/PipelineManager.h>
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
#include <OpenHome/Av/ProviderDebug.h>

#include <memory>

namespace OpenHome {
namespace Av {

class BufferedLogger
{
public:
    BufferedLogger(Net::DvDevice& aDevice, Product& aProduct, TUint aBytes)
    {
        iRingBufferLogger.reset(new RingBufferLogger(aBytes));
        iProviderDebug.reset(new ProviderDebug(aDevice, *iRingBufferLogger));
        aProduct.AddAttribute("Debug");
    }
    RingBufferLogger* LogBuffer()
    {
        return iRingBufferLogger.get();
    }
private:
    std::unique_ptr<RingBufferLogger> iRingBufferLogger;
    std::unique_ptr<ProviderDebug> iProviderDebug;
};

}
}


using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// MediaPlayer

MediaPlayer::MediaPlayer(Net::DvStack& aDvStack, Net::DvDeviceStandard& aDevice,
                         IStaticDataSource& aStaticDataSource,
                         IStoreReadWrite& aReadWriteStore,
                         PipelineInitParams* aPipelineInitParams,
                         VolumeConsumer& aVolumeConsumer, IVolumeProfile& aVolumeProfile,
                         Media::IInfoAggregator& aInfoAggregator,
                         const Brx& aEntropy,
                         const Brx& aDefaultRoom,
                         const Brx& aDefaultName)
    : iDvStack(aDvStack)
    , iDevice(aDevice)
    , iReadWriteStore(aReadWriteStore)
    , iConfigProductRoom(nullptr)
    , iConfigProductName(nullptr)
    , iConfigAutoPlay(nullptr)
    , iConfigStartupSource(nullptr)
    , iBufferedLogger(nullptr)
{
    iKvpStore = new KvpStore(aStaticDataSource);
    iTrackFactory = new Media::TrackFactory(aInfoAggregator, kTrackCount);
    iConfigManager = new Configuration::ConfigManager(iReadWriteStore);
    iPowerManager = new OpenHome::PowerManager(*iConfigManager);
    iConfigProductRoom = new ConfigText(*iConfigManager, Product::kConfigIdRoomBase /* + Brx::Empty() */, Product::kMaxRoomBytes, aDefaultRoom);
    iConfigProductName = new ConfigText(*iConfigManager, Product::kConfigIdNameBase /* + Brx::Empty() */, Product::kMaxNameBytes, aDefaultName);
    std::vector<TUint> choices;
    choices.push_back(Product::kAutoPlayDisable);
    choices.push_back(Product::kAutoPlayEnable);
    iConfigAutoPlay = new ConfigChoice(*iConfigManager, Product::kConfigIdAutoPlay, choices, Product::kAutoPlayDisable);
    iProduct = new Av::Product(aDvStack.Env(), aDevice, *iKvpStore, iReadWriteStore, *iConfigManager, *iConfigManager, *iPowerManager);
    iFriendlyNameManager = new Av::FriendlyNameManager(*iProduct);
    iPipeline = new PipelineManager(aPipelineInitParams, aInfoAggregator, *iTrackFactory);
    iVolumeConfig = new VolumeConfig(aReadWriteStore, *iConfigManager, *iPowerManager, aVolumeProfile);
    iVolumeManager = new Av::VolumeManager(aVolumeConsumer, iPipeline, *iVolumeConfig, aDevice, *iProduct, *iConfigManager, *iPowerManager);
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
    /**
     * Circular dependency between ConfigStartupSource and Product on certain ConfigValues.
     * Force ConfigStartupSource to de-register its source name listeners.
     * Safe to do as WebAppFramework must already have been stopped.
     */
    delete iProduct;
    delete iFriendlyNameManager;    // All observers should have deregistered.
    delete iConfigStartupSource;
    delete iVolumeManager;
    delete iVolumeConfig;
    //delete iTransportControl;
    delete iProviderConfig;
    delete iProviderTime;
    delete iProviderInfo;
    delete iConfigAutoPlay;
    delete iConfigProductRoom;
    delete iConfigProductName;
    delete iPowerManager;
    delete iConfigManager;
    delete iTrackFactory;
    delete iKvpStore;
    delete iBufferedLogger;
}

void MediaPlayer::Quit()
{
    iProduct->Stop();
    iPipeline->Quit();
}

void MediaPlayer::Add(Codec::ContainerBase* aContainer)
{
    iPipeline->Add(aContainer);
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

void MediaPlayer::BufferLogOutput(TUint aBytes)
{
    iBufferedLogger = new BufferedLogger(iDevice, *iProduct, aBytes);
}

void MediaPlayer::Start()
{
    // All sources must have been added to Product by time this is called.
    // So, can now initialise startup source ConfigVal.
    iConfigStartupSource = new ConfigStartupSource(*iConfigManager);

    iConfigManager->Open();
    iPipeline->Start(*iVolumeManager);
    iCredentials->Start();
    iMimeTypes.Start();
    iProduct->Start();
    iPowerManager->Start();
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

IFriendlyNameObservable& MediaPlayer::FriendlyNameObservable()
{
    return *iFriendlyNameManager;
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

RingBufferLogger* MediaPlayer::LogBuffer()
{
    return (iBufferedLogger ? iBufferedLogger->LogBuffer() : nullptr);
}
