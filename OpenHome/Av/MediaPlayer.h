#ifndef HEADER_MEDIAPLAYER
#define HEADER_MEDIAPLAYER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>

namespace OpenHome {
    class Environment;
namespace Net {
    class DvStack;
    class DvDevice;
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
    virtual Net::DvDevice& Device() = 0;
    virtual Media::PipelineManager& Pipeline() = 0;
    virtual Media::TrackFactory& TrackFactory() = 0;
    virtual IReadStore& ReadStore() = 0;
    virtual void Add(Media::UriProvider* aUriProvider) = 0;
};

class MediaPlayer : public IMediaPlayer, private INonCopyable
{
    static const TUint kTrackCount = 1200;
public:
    MediaPlayer(Net::DvStack& aDvStack, Net::DvDevice& aDevice, TUint aDriverMaxJiffies, IStaticDataSource& aStaticDataSource, IPersister& aPersistor);
    ~MediaPlayer();
    void Add(Media::Codec::CodecBase* aCodec);
    void Add(Media::Protocol* aProtocol);
    void Add(Media::ContentProcessor* aContentProcessor);
    void Add(ISource* aSource);
    void AddAttribute(const TChar* aAttribute); // FIXME - temp enabler for Songcasting driver setting a "Sender" attribute
    void Start();
public: // from IMediaPlayer
    Environment& Env();
    Net::DvStack& DvStack();
    Net::DvDevice& Device();
    Media::PipelineManager& Pipeline();
    Media::TrackFactory& TrackFactory();
    IReadStore& ReadStore();
    void Add(Media::UriProvider* aUriProvider);
private:
    Net::DvStack& iDvStack;
    Net::DvDevice& iDevice;
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
    KvpStore* iKvpStore;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_MEDIAPLAYER
