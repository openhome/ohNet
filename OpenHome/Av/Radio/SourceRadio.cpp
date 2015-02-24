#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Av/Radio/PresetDatabase.h>
#include <OpenHome/Av/Radio/ProviderRadio.h>
#include <OpenHome/Av/Radio/TuneIn.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Av/Radio/ContentProcessorFactory.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media//ClockPullerUtilisation.h>

#include <limits.h>

namespace OpenHome {
namespace Av {

class UriProviderRadio : public Media::UriProviderSingleTrack
{
public:
    UriProviderRadio(IMediaPlayer& aMediaPlayer);
    ~UriProviderRadio();
private: // from UriProvider
    Media::IClockPuller* ClockPuller() override;
private:
    Media::ClockPullerUtilisationPerStreamLeft* iClockPuller;
};

} // namespace Av
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;
using namespace OpenHome::Net;
using namespace OpenHome::Media;

// SourceFactory

ISource* SourceFactory::NewRadio(IMediaPlayer& aMediaPlayer, const Brx& aSupportedProtocols)
{ // static
    UriProviderSingleTrack* radioUriProvider = new UriProviderRadio(aMediaPlayer);
    aMediaPlayer.Add(radioUriProvider);
    return new SourceRadio(aMediaPlayer.Env(), aMediaPlayer.Device(), aMediaPlayer.Pipeline(), *radioUriProvider, aSupportedProtocols, aMediaPlayer.ConfigInitialiser());
}


// UriProviderRadio

UriProviderRadio::UriProviderRadio(IMediaPlayer& aMediaPlayer)
    : UriProviderSingleTrack("Radio", false, false, aMediaPlayer.TrackFactory())
{
    IPullableClock* pullable = aMediaPlayer.PullableClock();
    if (pullable == NULL) {
        iClockPuller = NULL;
    }
    else {
        iClockPuller = new ClockPullerUtilisationPerStreamLeft(aMediaPlayer.Env(), *pullable);
    }
}

UriProviderRadio::~UriProviderRadio()
{
    delete iClockPuller;
}

IClockPuller* UriProviderRadio::ClockPuller()
{
    return iClockPuller;
}


// SourceRadio

SourceRadio::SourceRadio(Environment& aEnv, DvDevice& aDevice, PipelineManager& aPipeline, UriProviderSingleTrack& aUriProvider, const Brx& aProtocolInfo, IConfigInitialiser& aConfigInit)
    : Source("Radio", "Radio")
    , iLock("SRAD")
    , iPipeline(aPipeline)
    , iUriProvider(aUriProvider)
    , iTrack(NULL)
    , iTrackPosSeconds(0)
    , iStreamId(UINT_MAX)
    , iTransportState(Media::EPipelineStopped)
{
    iPresetDatabase = new PresetDatabase();
    iProviderRadio = new ProviderRadio(aDevice, *this, *iPresetDatabase, aProtocolInfo);
    iTuneIn = new RadioPresetsTuneIn(aEnv, aPipeline, *iPresetDatabase, aConfigInit);
    iPipeline.Add(ContentProcessorFactory::NewM3u());
    iPipeline.Add(ContentProcessorFactory::NewM3u());
    iPipeline.Add(ContentProcessorFactory::NewM3uX());
    iPipeline.Add(ContentProcessorFactory::NewM3uX());
    iPipeline.Add(ContentProcessorFactory::NewPls());
    iPipeline.Add(ContentProcessorFactory::NewPls());
    iPipeline.Add(ContentProcessorFactory::NewOpml());
    iPipeline.Add(ContentProcessorFactory::NewOpml());
    iPipeline.Add(ContentProcessorFactory::NewAsx());
    iPipeline.Add(ContentProcessorFactory::NewAsx());
    iPipeline.AddObserver(*this);
}

SourceRadio::~SourceRadio()
{
    delete iTuneIn;
    delete iPresetDatabase;
    delete iProviderRadio;
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
}

void SourceRadio::Activate()
{
    iTrackPosSeconds = 0;
    iActive = true;
    const TUint trackId = (iTrack==NULL? Track::kIdNone : iTrack->Id());
    iPipeline.StopPrefetch(iUriProvider.Mode(), trackId);
}

void SourceRadio::Deactivate()
{
    iLock.Wait();
    iTransportState = EPipelineStopped;
    iProviderRadio->SetTransportState(EPipelineStopped);
    iLock.Signal();
    Source::Deactivate();
}

void SourceRadio::PipelineStopped()
{
    // FIXME - could NULL iPipeline (if we also changed it to be a pointer)
}

void SourceRadio::Fetch(const Brx& aUri, const Brx& aMetaData)
{
    if (!IsActive()) {
        DoActivate();
    }
    if (iTrack == NULL || iTrack->Uri() != aUri) {
        iPipeline.RemoveAll();
        if (iTrack != NULL) {
            iTrack->RemoveRef();
        }
        iTrack = iUriProvider.SetTrack(aUri, aMetaData);
        iPipeline.Begin(iUriProvider.Mode(), iTrack->Id());
        if (iTransportState == Media::EPipelinePlaying) {
            iPipeline.Play();
        }
    }
}

void SourceRadio::Play()
{
    if (!IsActive()) {
        DoActivate();
    }
    if (iTrack == NULL) {
        return;
    }
    iLock.Wait();
    iTransportState = Media::EPipelinePlaying;
    iLock.Signal();
    iPipeline.Begin(iUriProvider.Mode(), iTrack->Id());
    iPipeline.Play();
}

void SourceRadio::Pause()
{
    if (IsActive()) {
        iLock.Wait();
        iTransportState = Media::EPipelinePaused;
        iLock.Signal();
        iPipeline.Pause();
    }
}

void SourceRadio::Stop()
{
    if (IsActive()) {
        iLock.Wait();
        iTransportState = Media::EPipelineStopped;
        iLock.Signal();
        iPipeline.Stop();
    }
}

void SourceRadio::SeekAbsolute(TUint aSeconds)
{
    if (IsActive()) {
        (void)iPipeline.Seek(iStreamId, aSeconds);
    }
}

void SourceRadio::SeekRelative(TUint aSeconds)
{
    SeekAbsolute(aSeconds + iTrackPosSeconds);
}

void SourceRadio::NotifyPipelineState(EPipelineState aState)
{
    if (IsActive()) {
        iProviderRadio->SetTransportState(aState);
    }
}

void SourceRadio::NotifyTrack(Track& /*aTrack*/, const Brx& /*aMode*/, TBool /*aStartOfStream*/)
{
    if (!IsActive()) {
        return;
    }
}

void SourceRadio::NotifyMetaText(const Brx& /*aText*/)
{
}

void SourceRadio::NotifyTime(TUint aSeconds, TUint /*aTrackDurationSeconds*/)
{
    iLock.Wait();
    iTrackPosSeconds = aSeconds;
    iLock.Signal();
}

void SourceRadio::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    iLock.Wait();
    iStreamId = aStreamInfo.StreamId();
    iLock.Signal();
}
