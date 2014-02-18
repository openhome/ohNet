#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Av/Songcast/ProviderReceiver.h>
#include <OpenHome/Av/Songcast/ZoneHandler.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Av/Songcast/ProtocolOhu.h>
#include <OpenHome/Av/Songcast/ProtocolOhm.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/Songcast/OhmMsg.h>
#include <OpenHome/Media/Sender.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Configuration/ConfigManager.h>

namespace OpenHome {
namespace Media {
    class PipelineManager;
    class Sender;
}
namespace Av {

class SourceReceiver : public Source, private ISourceReceiver, private IZoneListener, private Media::IPipelineObserver
{
    static const TChar* kProtocolInfo;
    static const TUint kSenderLatencyMs = 100; // FIXME - should get this from Pipeline
public:
    SourceReceiver(IMediaPlayer& aMediaPlayer, IOhmTimestamper& aTimestamper, const Brx& aSenderIconFileName);
    ~SourceReceiver();
private: // from ISource
    void Activate();
    void Deactivate();
private: // from ISourceReceiver
    void Play();
    void Stop();
    void SetSender(const Brx& aUri, const Brx& aMetadata);
private: // from IZoneListener
    void ZoneUriChanged(const Brx& aZone, const Brx& aUri);
    void NotifyPresetInfo(TUint aPreset, const Brx& aMetadata);
private: // from Media::IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState);
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo);
private:
    void DoPlay();
    void ConfigRoomChanged(Configuration::KeyValuePair<const Brx&>& aKvp);
    void ConfigNameChanged(Configuration::KeyValuePair<const Brx&>& aKvp);
    void UpdateSenderName();
private:
    Mutex iLock;
    Media::PipelineManager& iPipeline;
    ZoneHandler* iZoneHandler;
    ProviderReceiver* iProviderReceiver;
    Media::UriProviderSingleTrack* iUriProvider;
    OhmMsgFactory* iOhmMsgFactory;
    Media::Sender* iSender;
    Uri iUri; // allocated here as stack requirements are too high for an automatic variable
    Bws<ZoneHandler::kMaxZoneBytes> iZone;
    Media::BwsTrackUri iTrackUri;
    Media::BwsTrackMetaData iTrackMetadata;
    TBool iPlaying;
    Configuration::ConfigText* iConfigRoom;
    TUint iConfigRoomSubscriberId;
    Configuration::ConfigText* iConfigName;
    TUint iConfigNameSubscriberId;
    Bws<Product::kMaxRoomBytes> iRoom;
    Bws<Product::kMaxNameBytes> iName;
};

} // namespace Av
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Net;
using namespace OpenHome::Media;
using namespace OpenHome::Configuration;

// SourceFactory

ISource* SourceFactory::NewReceiver(IMediaPlayer& aMediaPlayer, IOhmTimestamper& aTimestamper, const Brx& aSenderIconFileName)
{ // static
    return new SourceReceiver(aMediaPlayer, aTimestamper, aSenderIconFileName);
}


// SourceReceiver

const TChar* SourceReceiver::kProtocolInfo = "ohz:*:*:*,ohm:*:*:*,ohu:*.*.*";

SourceReceiver::SourceReceiver(IMediaPlayer& aMediaPlayer, IOhmTimestamper& aTimestamper, const Brx& aSenderIconFileName)
    : Source("Songcast", "Receiver")
    , iLock("SRCV")
    , iPipeline(aMediaPlayer.Pipeline())
    , iPlaying(false)
{
    Environment& env = aMediaPlayer.Env();
    DvDeviceStandard& device = aMediaPlayer.Device();
    iZoneHandler = new ZoneHandler(env, device.Udn());

    // Receiver
    iProviderReceiver = new ProviderReceiver(device, *this, kProtocolInfo);
    TrackFactory& trackFactory = aMediaPlayer.TrackFactory();
    static const TChar * kMode = "Receiver";
    const Brn kModeBuf(kMode);
    iUriProvider = new UriProviderSingleTrack(kMode, trackFactory);
    iPipeline.Add(iUriProvider);
    iOhmMsgFactory = new OhmMsgFactory(250, 250, 10, 10);
    iPipeline.Add(Codec::CodecFactory::NewOhm(*iOhmMsgFactory));
    iPipeline.Add(new ProtocolOhm(env, *iOhmMsgFactory, trackFactory, aTimestamper, kModeBuf));
    iPipeline.Add(new ProtocolOhu(env, *iOhmMsgFactory, trackFactory, aTimestamper, kModeBuf, aMediaPlayer.PowerManager()));
    iZoneHandler->AddListener(*this);
    iPipeline.AddObserver(*this);

    // Sender
    IConfigManagerWriter& configManagerWriter = aMediaPlayer.ConfigManagerWriter();
    IConfigManagerReader& configManagerReader = aMediaPlayer.ConfigManagerReader();
    iSender = new Sender(env, device, *iZoneHandler, configManagerWriter, Brx::Empty(), kSenderLatencyMs, aSenderIconFileName);
    (void)iPipeline.SetSender(*iSender);
    aMediaPlayer.AddAttribute("Sender");
    iConfigRoom = &configManagerReader.GetText(Product::kConfigIdRoomBase);
    iConfigRoomSubscriberId = iConfigRoom->Subscribe(MakeFunctorConfigText(*this, &SourceReceiver::ConfigRoomChanged));
    iConfigName = &configManagerReader.GetText(Product::kConfigIdNameBase);
    iConfigNameSubscriberId = iConfigName->Subscribe(MakeFunctorConfigText(*this, &SourceReceiver::ConfigNameChanged));
    UpdateSenderName();
}

SourceReceiver::~SourceReceiver()
{
    iConfigRoom->Unsubscribe(iConfigRoomSubscriberId);
    iConfigName->Unsubscribe(iConfigNameSubscriberId);
    delete iSender;
    delete iOhmMsgFactory;
    iZoneHandler->RemoveListener(*this);
    delete iProviderReceiver;
    delete iZoneHandler;
}

void SourceReceiver::Activate()
{
    iActive = true;
}

void SourceReceiver::Deactivate()
{
    iProviderReceiver->NotifyPipelineState(EPipelineStopped);
    Source::Deactivate();
}

void SourceReceiver::Play()
{
    if (!IsActive()) {
        DoActivate();
    }
    AutoMutex a(iLock);
    iPlaying = true;
    if (iTrackUri.Bytes() > 0) {
        DoPlay();
    }
}

void SourceReceiver::Stop()
{
    iLock.Wait();
    iPlaying = false;
    iLock.Signal();
    iPipeline.Stop();
}

void SourceReceiver::SetSender(const Brx& aUri, const Brx& aMetadata)
{
    AutoMutex a(iLock);
    iUri.Replace(aUri);
    // FIXME - may later want to handle a 'preset' scheme to allow presets to be selected from UI code
    if (iUri.Scheme() == ZoneHandler::kProtocolZone) {
        Endpoint ep(iUri.Port(), iUri.Host());
        const Endpoint& tgt = iZoneHandler->MulticastEndpoint();
        if (ep.Address() != tgt.Address() || ep.Port() != tgt.Port()) {
            THROW(UriError);
        }
        const Brx& path = iUri.Path();
        if (path.Bytes() < 2 || path[0] != '/') {
            THROW(UriError);
        }
        iZone.Replace(path.Split(1)); // remove leading /
        iZoneHandler->StartMonitoring(iZone);
        iTrackUri.Replace(Brx::Empty());
    }
    else {
        iZone.Replace(Brx::Empty());
        iTrackUri.Replace(aUri);
    }
    iTrackMetadata.Replace(aMetadata);
}

void SourceReceiver::ZoneUriChanged(const Brx& aZone, const Brx& aUri)
{
    AutoMutex a(iLock);
    if (aZone == iZone && aUri != iTrackUri) {
        iTrackUri.Replace(aUri);
        if (iPlaying) {
            DoPlay();
        }
    }
}

void SourceReceiver::NotifyPresetInfo(TUint /*aPreset*/, const Brx& /*aMetadata*/)
{
    // FIXME - will need to implement this once we support preset selection via UI
}

void SourceReceiver::NotifyPipelineState(EPipelineState aState)
{
    if (iActive) {
        iProviderReceiver->NotifyPipelineState(aState);
    }
    iSender->NotifyPipelineState(aState);
}

void SourceReceiver::NotifyTrack(Track& /*aTrack*/, const Brx& /*aMode*/, TUint /*aIdPipeline*/)
{
}

void SourceReceiver::NotifyMetaText(const Brx& /*aText*/)
{
}

void SourceReceiver::NotifyTime(TUint /*aSeconds*/, TUint /*aTrackDurationSeconds*/)
{
}

void SourceReceiver::NotifyStreamInfo(const DecodedStreamInfo& /*aStreamInfo*/)
{
}

void SourceReceiver::DoPlay()
{
    Track* track = iUriProvider->SetTrack(iTrackUri, iTrackMetadata, true);
    iPipeline.RemoveAll();
    iPipeline.Begin(iUriProvider->Mode(), track->Id());
    track->RemoveRef();
    iPipeline.Play();
}

void SourceReceiver::ConfigRoomChanged(KeyValuePair<const Brx&>& aKvp)
{
    AutoMutex a(iLock);
    iRoom.Replace(aKvp.Value());
    UpdateSenderName();
}

void SourceReceiver::ConfigNameChanged(KeyValuePair<const Brx&>& aKvp)
{
    AutoMutex a(iLock);
    iName.Replace(aKvp.Value());
    UpdateSenderName();
}

void SourceReceiver::UpdateSenderName()
{
    Bws<Product::kMaxRoomBytes + Product::kMaxNameBytes + 3> name;
    name.Append(iRoom);
    name.Append(' ');
    name.Append('(');
    name.Append(iName);
    name.Append(')');
    iSender->SetName(name);
}
