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
    UriProviderRadio(IMediaPlayer& aMediaPlayer, Media::IPullableClock* aPullableClock);
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

ISource* SourceFactory::NewRadio(IMediaPlayer& aMediaPlayer, Media::IPullableClock* aPullableClock, const Brx& aSupportedProtocols)
{ // static
    UriProviderSingleTrack* radioUriProvider = new UriProviderRadio(aMediaPlayer, aPullableClock);
    aMediaPlayer.Add(radioUriProvider);
    return new SourceRadio(aMediaPlayer.Env(), aMediaPlayer.Device(), aMediaPlayer.Pipeline(),
                           *radioUriProvider, aSupportedProtocols, Brx::Empty(),
                           aMediaPlayer.ConfigInitialiser(), aMediaPlayer.CredentialsManager());
}

ISource* SourceFactory::NewRadio(IMediaPlayer& aMediaPlayer, Media::IPullableClock* aPullableClock, const Brx& aSupportedProtocols, const Brx& aTuneInPartnerId)
{ // static
    UriProviderSingleTrack* radioUriProvider = new UriProviderRadio(aMediaPlayer, aPullableClock);
    aMediaPlayer.Add(radioUriProvider);
    return new SourceRadio(aMediaPlayer.Env(), aMediaPlayer.Device(), aMediaPlayer.Pipeline(),
                           *radioUriProvider, aSupportedProtocols, aTuneInPartnerId,
                           aMediaPlayer.ConfigInitialiser(), aMediaPlayer.CredentialsManager());
}


// UriProviderRadio

UriProviderRadio::UriProviderRadio(IMediaPlayer& aMediaPlayer, Media::IPullableClock* aPullableClock)
    : UriProviderSingleTrack("Radio", false, false, aMediaPlayer.TrackFactory())
{
    if (aPullableClock == NULL) {
        iClockPuller = NULL;
    }
    else {
        iClockPuller = new ClockPullerUtilisationPerStreamLeft(aMediaPlayer.Env(), *aPullableClock);
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

SourceRadio::SourceRadio(Environment& aEnv, DvDevice& aDevice, PipelineManager& aPipeline,
                         UriProviderSingleTrack& aUriProvider, const Brx& aProtocolInfo, const Brx& aTuneInPartnerId,
                         IConfigInitialiser& aConfigInit, Credentials& aCredentialsManager)
    : Source("Radio", "Radio")
    , iLock("SRAD")
    , iPipeline(aPipeline)
    , iUriProvider(aUriProvider)
    , iTrack(NULL)
    , iTrackPosSeconds(0)
    , iStreamId(UINT_MAX)
    , iLive(false)
{
    iPresetDatabase = new PresetDatabase();
    iProviderRadio = new ProviderRadio(aDevice, *this, *iPresetDatabase, aProtocolInfo);
    if (aTuneInPartnerId.Bytes() == 0) {
        iTuneIn = NULL;
    }
    else {
        iTuneIn = new RadioPresetsTuneIn(aEnv, aPipeline, aTuneInPartnerId, *iPresetDatabase, aConfigInit, aCredentialsManager);
    }
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
    AutoMutex _(iLock);
    if (!IsActive()) {
        DoActivate();
    }
    if (iTrack == NULL || iTrack->Uri() != aUri) {
        if (iTrack != NULL) {
            iTrack->RemoveRef();
        }
        iTrack = iUriProvider.SetTrack(aUri, aMetaData);
        if (iTrack != NULL) {
            iPipeline.StopPrefetch(iUriProvider.Mode(), iTrack->Id());
        }
    }
}

/*
 * Some control points do not chain calls to SetChannel()/Play() on the provider,
 * which can result in those actions coming in out of order.
 *
 * This causes problems, particularly when no radio station has been pre-fetched,
 * as Play() does nothing due to encountering a NULL track, followed by a valid
 * track being queued up in the pipeline via Fetch(), which never gets played
 * as the call to Play() has already been issued on a NULL track.
 */
void SourceRadio::Play()
{
    AutoMutex _(iLock);
    if (!IsActive()) {
        DoActivate();
    }
    if (iTrack == NULL) {
        return;
    }

    /*
     * Fetch() is always called each time a new URI is set. That causes some
     * data to be buffered in the pipeline, which may be stale by the time
     * Play() is called.
     *
     * Therefore, always call RemoveAll(), even if the pipeline has already
     * been initialised with the desired track URI.
     *
     * Pre-fetching and then clearing pipeline may cause the pipeline to report:
     * "Failure to recognise audio format, flushing stream..."
     * which is just a false-positive in this scenario.
     */
    iPipeline.RemoveAll();
    iPipeline.Begin(iUriProvider.Mode(), iTrack->Id());
    iPipeline.Play();
}

void SourceRadio::Pause()
{
    if (IsActive()) {
        if (iLive) {
            iPipeline.Stop();
        }
        else {
            iPipeline.Pause();
        }
    }
}

void SourceRadio::Stop()
{
    if (IsActive()) {
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

void SourceRadio::NotifyMode(const Brx& /*aMode*/, const ModeInfo& /*aInfo*/)
{
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
    iLive = aStreamInfo.Live();
    iLock.Signal();
}
