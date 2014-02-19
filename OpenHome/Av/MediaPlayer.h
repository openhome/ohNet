#ifndef HEADER_MEDIAPLAYER
#define HEADER_MEDIAPLAYER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>

namespace OpenHome {
    class Environment;
    class IPowerManager;
    class PowerManager;
namespace Net {
    class DvStack;
    class DvDeviceStandard;
}
namespace Media {
    class PipelineManager;
    class IMuteManager;
    class IVolume;  // XXX dummy volume hardware
    class IVolumeManagerLimits;
    class UriProvider;
    class Protocol;
    class ContentProcessor;
    namespace Codec {
        class CodecBase;
    }
    class AllocatorInfoLogger;
    class LoggingPipelineObserver;
    class TrackFactory;
}
namespace Configuration {
    class ConfigManager;
    class IConfigManagerReader;
    class IConfigManagerWriter;
    class IStoreReadWrite;
    class ConfigText;
}
namespace Net {
    class NetworkMonitor;
}
namespace Av {

class IReadStore;
class ISource;
class IStaticDataSource;
class IPersister;
class Product;
class ProviderTime;
class ProviderInfo;
class ProviderVolume;
class KvpStore;

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
    virtual Configuration::IConfigManagerReader& ConfigManagerReader() = 0;
    virtual Configuration::IConfigManagerWriter& ConfigManagerWriter() = 0;
    virtual IPowerManager& PowerManager() = 0;
    virtual void Add(Media::UriProvider* aUriProvider) = 0;
    virtual void AddAttribute(const TChar* aAttribute) = 0;
};

class MediaPlayer : public IMediaPlayer, private INonCopyable
{
    static const TUint kTrackCount = 1200;
public:
    MediaPlayer(Net::DvStack& aDvStack, Net::DvDeviceStandard& aDevice,
                TUint aDriverMaxJiffies, IStaticDataSource& aStaticDataSource,
                Configuration::IStoreReadWrite& aReadWriteStore);
    ~MediaPlayer();
    void Add(Media::Codec::CodecBase* aCodec);
    void Add(Media::Protocol* aProtocol);
    void Add(Media::ContentProcessor* aContentProcessor);
    void Add(ISource* aSource);
    void Start();
public: // from IMediaPlayer
    Environment& Env();
    Net::DvStack& DvStack();
    Net::DvDeviceStandard& Device();
    Media::PipelineManager& Pipeline();
    Media::TrackFactory& TrackFactory();
    IReadStore& ReadStore();
    Configuration::IStoreReadWrite& ReadWriteStore();
    Configuration::IConfigManagerReader& ConfigManagerReader();
    Configuration::IConfigManagerWriter& ConfigManagerWriter();
    IPowerManager& PowerManager();
    void Add(Media::UriProvider* aUriProvider);
    void AddAttribute(const TChar* aAttribute);
private:
    Net::DvStack& iDvStack;
    Net::DvDeviceStandard& iDevice;
    Media::AllocatorInfoLogger* iInfoLogger;
    Media::PipelineManager* iPipeline;
    Media::TrackFactory* iTrackFactory;
    Product* iProduct;
    Media::IMuteManager* iMuteManager;
    Media::IVolume* iLeftVolumeHardware;   // XXX dummy ...
    Media::IVolume* iRightVolumeHardware;  // XXX volume hardware
    Media::IVolumeManagerLimits* iVolumeManager;
    ProviderTime* iTime;
    ProviderInfo* iInfo;
    ProviderVolume* iVolume;
    Net::NetworkMonitor* iNetworkMonitor;
    KvpStore* iKvpStore;
    Configuration::IStoreReadWrite& iReadWriteStore;
    Configuration::ConfigManager* iConfigManager;
    OpenHome::PowerManager* iPowerManager;
    Configuration::ConfigText* iConfigProductRoom;
    Configuration::ConfigText* iConfigProductName;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_MEDIAPLAYER
