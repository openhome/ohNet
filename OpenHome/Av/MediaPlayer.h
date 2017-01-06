#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/MimeTypeList.h>
#include <OpenHome/Optional.h>
#include <OpenHome/Av/Logger.h>

namespace OpenHome {
    class Environment;
    class IPowerManager;
    class PowerManager;
    class RingBufferLogger;
    class IUnixTimestamp;
    class IShell;
    class IInfoAggregator;
namespace Net {
    class DvStack;
    class DvDeviceStandard;
    class DvProvider;
}
namespace Media {
    class PipelineManager;
    class PipelineInitParams;
    class IPipelineAnimator;
    class IMuteManager;
    class UriProvider;
    class Protocol;
    namespace Codec {
        class ContainerBase;
        class CodecBase;
    }
    class LoggingPipelineObserver;
    class TrackFactory;
}
namespace Configuration {
    class ConfigManager;
    class IConfigManager;
    class IConfigInitialiser;
    class IStoreReadWrite;
    class ConfigText;
    class ConfigChoice;
    class ProviderConfig;
}
namespace Av {

class IFriendlyNameObservable;
class FriendlyNameManager;
class IReadStore;
class ISource;
class IStaticDataSource;
class IPersister;
class IProvider;
class Product;
class ProviderTime;
class ProviderInfo;
class ProviderVolume;
class KvpStore;
class Credentials;
class VolumeManager;
class VolumeConfig;
class VolumeConsumer;
class IVolumeManager;
class IVolumeProfile;
class ConfigStartupSource;

class IMediaPlayer
{
public:
    virtual ~IMediaPlayer() {}
    virtual Environment& Env() = 0;
    virtual Net::DvStack& DvStack() = 0;
    virtual Net::DvDeviceStandard& Device() = 0;
    virtual Media::PipelineManager& Pipeline() = 0;
    virtual Media::TrackFactory& TrackFactory() = 0;
    virtual IReadStore& ReadStore() = 0;
    virtual Configuration::IStoreReadWrite& ReadWriteStore() = 0;
    virtual Configuration::IConfigManager& ConfigManager() = 0;
    virtual Configuration::IConfigInitialiser& ConfigInitialiser() = 0;
    virtual IPowerManager& PowerManager() = 0;
    virtual Av::Product& Product() = 0;
    virtual Av::IFriendlyNameObservable& FriendlyNameObservable() = 0;
    virtual IVolumeManager& VolumeManager() = 0;
    virtual Credentials& CredentialsManager() = 0;
    virtual Media::MimeTypeList& MimeTypes() = 0;
    virtual void Add(Media::UriProvider* aUriProvider) = 0;
    virtual void AddAttribute(const TChar* aAttribute) = 0;
    virtual ILoggerSerial& BufferLogOutput(TUint aBytes, IShell& aShell, Optional<ILogPoster> aLogPoster) = 0; // must be called before Start()
    virtual IUnixTimestamp& UnixTimestamp() = 0;
};

class MediaPlayer : public IMediaPlayer, private INonCopyable
{
    static const TUint kTrackCount = 1200;
public:
    MediaPlayer(Net::DvStack& aDvStack, Net::DvDeviceStandard& aDevice,
                IStaticDataSource& aStaticDataSource,
                Configuration::IStoreReadWrite& aReadWriteStore,
                Media::PipelineInitParams* aPipelineInitParams,
                VolumeConsumer& aVolumeConsumer, IVolumeProfile& aVolumeProfile,
                IInfoAggregator& aInfoAggregator,
                const Brx& aEntropy,
                const Brx& aDefaultRoom,
                const Brx& aDefaultName);
    ~MediaPlayer();
    void Quit();
    void Add(Media::Codec::ContainerBase* aContainer);
    void Add(Media::Codec::CodecBase* aCodec);
    void Add(Media::Protocol* aProtocol);
    void Add(ISource* aSource);
    RingBufferLogger* LogBuffer(); // an optional component. returns nullptr if not available. no transfer of ownership.
    void Start();
public: // from IMediaPlayer
    Environment& Env() override;
    Net::DvStack& DvStack() override;
    Net::DvDeviceStandard& Device() override;
    Media::PipelineManager& Pipeline() override;
    Media::TrackFactory& TrackFactory() override;
    IReadStore& ReadStore() override;
    Configuration::IStoreReadWrite& ReadWriteStore() override;
    Configuration::IConfigManager& ConfigManager() override;
    Configuration::IConfigInitialiser& ConfigInitialiser() override;
    IPowerManager& PowerManager() override;
    Av::Product& Product() override;
    Av::IFriendlyNameObservable& FriendlyNameObservable() override;
    OpenHome::Av::IVolumeManager& VolumeManager() override;
    Credentials& CredentialsManager() override;
    Media::MimeTypeList& MimeTypes() override;
    void Add(Media::UriProvider* aUriProvider) override;
    void AddAttribute(const TChar* aAttribute) override;
    ILoggerSerial& BufferLogOutput(TUint aBytes, IShell& aShell, Optional<ILogPoster> aLogPoster) override; // must be called before Start()
    IUnixTimestamp& UnixTimestamp() override;
private:
    Net::DvStack& iDvStack;
    Net::DvDeviceStandard& iDevice;
    KvpStore* iKvpStore;
    Media::PipelineManager* iPipeline;
    Media::TrackFactory* iTrackFactory;
    Configuration::IStoreReadWrite& iReadWriteStore;
    Configuration::ConfigManager* iConfigManager;
    OpenHome::PowerManager* iPowerManager;
    Configuration::ConfigText* iConfigProductRoom;
    Configuration::ConfigText* iConfigProductName;
    Configuration::ConfigChoice* iConfigAutoPlay;
    Av::Product* iProduct;
    Av::FriendlyNameManager* iFriendlyNameManager;
    VolumeConfig* iVolumeConfig;
    Av::VolumeManager* iVolumeManager;
    ConfigStartupSource* iConfigStartupSource;
    Credentials* iCredentials;
    Media::MimeTypeList iMimeTypes;
    ProviderTime* iProviderTime;
    ProviderInfo* iProviderInfo;
    Configuration::ProviderConfig* iProviderConfig;
    LoggerBuffered* iLoggerBuffered;
    IUnixTimestamp* iUnixTimestamp;
    //TransportControl* iTransportControl;
};

} // namespace Av
} // namespace OpenHome

