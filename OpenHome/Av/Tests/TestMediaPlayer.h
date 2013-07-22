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

namespace OpenHome {
namespace Net {
    class DvStack;
    class DvDevice;
}
namespace Media {
    class PipelineManager;
    class DriverSongcastSender;
}
namespace Av {
    class RamStore;
    class ISource;
namespace Test {

class TestMediaPlayer
{
    static const TUint kTrackCount = 1200;
    static const TUint kRaopDiscoveryPort = 5048;
public:
    TestMediaPlayer(Net::DvStack& aDvStack, const Brx& aUdn, const TChar* aRoom, const TChar* aProductName, TUint aMaxDriverJiffies, const TChar* aTuneInUserName);
    virtual ~TestMediaPlayer();
    void AddAttribute(const TChar* aAttribute); // FIXME - only required by Songcasting driver
    void Run();
    Media::PipelineManager& Pipeline();
    Net::DvDevice* Device();
protected:
    virtual void RegisterPlugins(Environment& aEnv);
private:
    TBool TryDisable(Net::DvDevice& aDevice);
    void Disabled();
protected:
    static const Brn kSupportedProtocols;
    MediaPlayer* iMediaPlayer;
    Net::DvDevice* iDevice;
    Net::DvDevice* iDeviceUpnpAv;
    RamStore* iRamStore;
private:
    Semaphore iDisabled;
    Media::DriverSongcastSender* iDriver;
    ISource* iSourceUpnp; // FIXME - see #169
};

TestMediaPlayer* CreateMediaPlayer(Net::DvStack& aDvStack, const Brx& aUdn, const TChar* aRoom, const TChar* aProductName, TUint aMaxDriverJiffies, const TChar* aTuneInUserName);
int ExecuteTestMediaPlayer(int aArgc, char* aArgv[]);

} // namespace Test
} // namespace Av
} // namespace OpenHome

#endif // HEADER_TESTMEDIAPLAYER
