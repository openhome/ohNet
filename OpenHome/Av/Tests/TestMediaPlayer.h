#ifndef HEADER_TESTMEDIAPLAYER
#define HEADER_TESTMEDIAPLAYER

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>

#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Av/Utils/DriverSongcastSender.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/KvpStore.h>
#include "RamStore.h"
#include <OpenHome/Av/Songcast/OhmTimestamp.h>
#include <OpenHome/PowerManager.h>

namespace OpenHome {
    class PowerManager;
namespace Net {
    class DviServerUpnp;
    class DvStack;
    class DvDevice;
    class Shell;
    class ShellCommandDebug;
}
namespace Media {
    class PipelineManager;
    class DriverSongcastSender;
    class IPullableClock;
}
namespace Configuration {
    class ConfigRamStore;
    class ConfigManager;
}
namespace Av {
    class RamStore;
namespace Test {

class TestMediaPlayer : private Net::IResourceManager, public IPowerHandler
{
    static const Brn kSongcastSenderIconFileName;
    static const TUint kTrackCount = 1200;
public:
    TestMediaPlayer(Net::DvStack& aDvStack, const Brx& aUdn, const TChar* aRoom, const TChar* aProductName, const TChar* aTuneInUserName, Media::IPullableClock* aPullableClock);
    virtual ~TestMediaPlayer();
    void StopPipeline();
    void AddAttribute(const TChar* aAttribute); // FIXME - only required by Songcasting driver
    void Run();
    Media::PipelineManager& Pipeline();
    Net::DvDeviceStandard* Device();
protected:
    virtual void RegisterPlugins(Environment& aEnv);
    void DoRegisterPlugins(Environment& aEnv, const Brx& aSupportedProtocols);
private: // from Net::IResourceManager
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, Net::IResourceWriter& aResourceWriter);
private: // from IPowerHandler
    void PowerUp();
    void PowerDown();
private:
    static TUint Hash(const Brx& aBuf);
    static void GenerateMacAddr(Environment& aEnv, TUint aSeed, Bwx& aMacAddr);
    void MacAddrFromUdn(Environment& aEnv, Bwx& aMacAddr);
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
private:
    Semaphore iDisabled;
    DefaultTimestamper iSongcastTimestamper; // FIXME - will want to replace this with access to a driver on embedded platforms
    IPowerManagerObserver* iPowerObserver;
    Net::Shell* iShell;
    Net::ShellCommandDebug* iShellDebug;
};

class TestMediaPlayerOptions
{
public:
    TestMediaPlayerOptions();
    TBool Parse(int aArgc, char* aArgv[]);
    TestFramework::OptionString& Room();
    TestFramework::OptionString& Name();
    TestFramework::OptionString& Udn();
    TestFramework::OptionUint& Channel();
    TestFramework::OptionUint& Adapter();
    TestFramework::OptionString& TuneIn();
    TestFramework::OptionBool& Loopback();
private:
    TestFramework::OptionParser iParser;
    TestFramework::OptionString iOptionRoom;
    TestFramework::OptionString iOptionName;
    TestFramework::OptionString iOptionUdn;
    TestFramework::OptionUint iOptionChannel;
    TestFramework::OptionUint iOptionAdapter;
    TestFramework::OptionString iOptionTuneIn;
    TestFramework::OptionBool iOptionLoopback;
};

// Not very nice, but only to allow reusable test functions.
class TestMediaPlayerInit
{
public:
    static OpenHome::Net::Library* CreateLibrary(TBool aLoopback, TUint aAdapter);  // creates lib; client must start appropriate stacks
    static void SeedRandomNumberGenerator(Environment& aEnv, const Brx& aRoom, TIpAddress aAddress, Net::DviServerUpnp& aServer);    // seed from room + server port
    static void AppendUniqueId(Environment& aEnv, const Brx& aUserUdn, const Brx& aDefaultUdn, Bwh& aOutput);
};

typedef TestMediaPlayer* (*CreateMediaPlayerFunc)(Net::CpStack& aCpStack, Net::DvStack& aDvStack, const Brx& aUdn, const TChar* aRoom, const TChar* aProductName, const TChar* aTuneInUserName, Media::IPullableClock* aPullableClock);
int ExecuteTestMediaPlayer(int aArgc, char* aArgv[], CreateMediaPlayerFunc aFunc);

} // namespace Test
} // namespace Av
} // namespace OpenHome

#endif // HEADER_TESTMEDIAPLAYER
