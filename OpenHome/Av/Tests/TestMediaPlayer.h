#ifndef HEADER_TESTMEDIAPLAYER
#define HEADER_TESTMEDIAPLAYER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>

#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/DriverSongcastSender.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/KvpStore.h>
#include "RamStore.h"
#include <OpenHome/Av/Songcast/OhmTimestamp.h>

namespace OpenHome {
    class PowerManager;
namespace Net {
    class DvStack;
    class DvDevice;
}
namespace Media {
    class PipelineManager;
    class DriverSongcastSender;
}
namespace Configuration {
    class ConfigRamStore;
    class ConfigManager;
}
namespace Av {
    class RamStore;
    class ISource;
namespace Test {

class TestMediaPlayer : private Net::IResourceManager
{
    static const Brn kSongcastSenderIconFileName;
    static const TUint kTrackCount = 1200;
public:
    TestMediaPlayer(Net::DvStack& aDvStack, const Brx& aUdn, const TChar* aRoom, const TChar* aProductName, TUint aMaxDriverJiffies, const TChar* aTuneInUserName);
    virtual ~TestMediaPlayer();
    void DestroyPipeline();
    void AddAttribute(const TChar* aAttribute); // FIXME - only required by Songcasting driver
    void Run();
    Media::PipelineManager& Pipeline();
    Net::DvDeviceStandard* Device();
protected:
    virtual void RegisterPlugins(Environment& aEnv);
    void DoRegisterPlugins(Environment& aEnv, const Brx& aSupportedProtocols);
private: // from Net::IResourceManager
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, Net::IResourceWriter& aResourceWriter);
private:
    void PowerDownUpnp();
    void PowerDownDisable(Net::DvDevice& aDevice);
    void PowerDownUpnpCallback();
    TBool TryDisable(Net::DvDevice& aDevice);
    void Disabled();
protected:
    MediaPlayer* iMediaPlayer;
    Media::LoggingPipelineObserver* iPipelineObserver;
    Net::DvDeviceStandard* iDevice;
    Net::DvDevice* iDeviceUpnpAv;
    RamStore* iRamStore;
    Configuration::ConfigRamStore* iConfigRamStore;
    PowerManager* iPowerManager;
private:
    Semaphore iDisabled;
    ISource* iSourceUpnp; // FIXME - see #169
    DefaultTimestamper iSongcastTimestamper; // FIXME - will want to replace this with access to a driver on embedded platforms
};

typedef TestMediaPlayer* (*CreateMediaPlayerFunc)(Net::DvStack& aDvStack, const Brx& aUdn, const TChar* aRoom, const TChar* aProductName, TUint aMaxDriverJiffies, const TChar* aTuneInUserName);
int ExecuteTestMediaPlayer(int aArgc, char* aArgv[], CreateMediaPlayerFunc aFunc);

} // namespace Test
} // namespace Av
} // namespace OpenHome

#endif // HEADER_TESTMEDIAPLAYER
