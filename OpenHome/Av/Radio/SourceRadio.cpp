#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/Pipeline.h> // for PipelineStreamNotPausable
#include <OpenHome/Av/Radio/PresetDatabase.h>
#include <OpenHome/Av/Radio/UriProviderRadio.h>
#include <OpenHome/Av/Radio/ProviderRadio.h>
#include <OpenHome/Av/Radio/TuneIn.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Av/Radio/ContentProcessorFactory.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/PowerManager.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Optional.h>

#include <limits.h>
#include <memory>


using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;
using namespace OpenHome::Net;
using namespace OpenHome::Media;

// SourceFactory

ISource* SourceFactory::NewRadio(IMediaPlayer& aMediaPlayer)
{ // static
    return new SourceRadio(aMediaPlayer, Brx::Empty());
}

ISource* SourceFactory::NewRadio(IMediaPlayer& aMediaPlayer, const Brx& aTuneInPartnerId)
{ // static
    return new SourceRadio(aMediaPlayer, aTuneInPartnerId);
}

const TChar* SourceFactory::kSourceTypeRadio = "Radio";
const Brn SourceFactory::kSourceNameRadio("Radio");

// SourceRadio

SourceRadio::SourceRadio(IMediaPlayer& aMediaPlayer, const Brx& aTuneInPartnerId)
    : Source(SourceFactory::kSourceNameRadio, SourceFactory::kSourceTypeRadio, aMediaPlayer.Pipeline(), aMediaPlayer.PowerManager())
    , iLock("SRAD")
    , iUriProvider(nullptr)
    , iTrack(nullptr)
    , iTrackPosSeconds(0)
    , iStreamId(UINT_MAX)
    , iLive(false)
    , iPresetsUpdated(false)
    , iAutoPlay(false)
{
    MimeTypeList& mimeTypes = aMediaPlayer.MimeTypes();

    iPipeline.Add(ContentProcessorFactory::NewM3u(mimeTypes));
    iPipeline.Add(ContentProcessorFactory::NewM3u(mimeTypes));
    iPipeline.Add(ContentProcessorFactory::NewM3uX());
    iPipeline.Add(ContentProcessorFactory::NewM3uX());
    iPipeline.Add(ContentProcessorFactory::NewPls(mimeTypes));
    iPipeline.Add(ContentProcessorFactory::NewPls(mimeTypes));
    iPipeline.Add(ContentProcessorFactory::NewOpml(mimeTypes));
    iPipeline.Add(ContentProcessorFactory::NewOpml(mimeTypes));
    iPipeline.Add(ContentProcessorFactory::NewAsx());
    iPipeline.Add(ContentProcessorFactory::NewAsx());
    iPipeline.AddObserver(*this);
    iStorePresetNumber = new StoreInt(aMediaPlayer.ReadWriteStore(), aMediaPlayer.PowerManager(),
                                  kPowerPriorityNormal, Brn("Radio.PresetId"),
                                  IPresetDatabaseReader::kPresetIdNone);

    iPresetDatabase = new PresetDatabase(aMediaPlayer.TrackFactory());
    iPresetDatabase->AddObserver(*this);

    iUriProvider = new UriProviderRadio(aMediaPlayer.TrackFactory(), *iPresetDatabase);
    iUriProvider->SetTransportPlay(MakeFunctor(*this, &SourceRadio::Play));
    iUriProvider->SetTransportPause(MakeFunctor(*this, &SourceRadio::Pause));
    iUriProvider->SetTransportStop(MakeFunctor(*this, &SourceRadio::Stop));
    aMediaPlayer.Add(iUriProvider);

    iProviderRadio = new ProviderRadio(aMediaPlayer.Device(), *this, *iPresetDatabase);
    mimeTypes.AddUpnpProtocolInfoObserver(MakeFunctorGeneric(*iProviderRadio, &ProviderRadio::NotifyProtocolInfo));
    if (aTuneInPartnerId.Bytes() == 0) {
        iTuneIn = nullptr;
    }
    else {
        iTuneIn = new RadioPresetsTuneIn(aMediaPlayer.Env(), aTuneInPartnerId,
                                         *iPresetDatabase, aMediaPlayer.ConfigInitialiser(),
                                         aMediaPlayer.CredentialsManager(), mimeTypes);
    }
}

SourceRadio::~SourceRadio()
{
    delete iTuneIn;
    delete iPresetDatabase;
    delete iStorePresetNumber;
    delete iProviderRadio;
    if (iTrack != nullptr) {
        iTrack->RemoveRef();
    }
}

void SourceRadio::Activate(TBool aAutoPlay)
{
    SourceBase::Activate(aAutoPlay);
    if (iTuneIn != nullptr) {
        iTuneIn->Refresh();
    }
    iTrackPosSeconds = 0;
    iActive = true;
    iAutoPlay = aAutoPlay;
    if (!iNoPipelinePrefetchOnActivation) {
        const TUint trackId = (iTrack==nullptr? Track::kIdNone : iTrack->Id());
        iPipeline.StopPrefetch(iUriProvider->Mode(), trackId);
        if (trackId != Track::kIdNone && aAutoPlay) {
            iPipeline.Play();
        }
    }
}

void SourceRadio::Deactivate()
{
    iProviderRadio->SetTransportState(EPipelineStopped);
    iStorePresetNumber->Write();
    Source::Deactivate();
}

TBool SourceRadio::TryActivateNoPrefetch(const Brx& aMode)
{
    if (iUriProvider->Mode() != aMode) {
        return false;
    }
    EnsureActiveNoPrefetch();
    return true;
}

void SourceRadio::StandbyEnabled()
{
    Stop();
}

void SourceRadio::PipelineStopped()
{
    // FIXME - could nullptr iPipeline (if we also changed it to be a pointer)
}

TBool SourceRadio::TryFetch(TUint aPresetId, const Brx& aUri)
{
    AutoMutex _(iLock);
    if (aPresetId == IPresetDatabaseReader::kPresetIdNone) {
        return false;
    }
    if (aUri.Bytes() > 0) {
        iPresetUri.Replace(aUri);
        if (!iPresetDatabase->TryGetPresetById(aPresetId, iPresetMetadata)) {
            return false;
        }
    }
    else if (!iPresetDatabase->TryGetPresetById(aPresetId, iPresetUri, iPresetMetadata)) {
        return false;
    }
    iStorePresetNumber->Set(iPresetDatabase->GetPresetNumber(aPresetId));
    iProviderRadio->NotifyPresetInfo(aPresetId, iPresetUri, iPresetMetadata);
    FetchLocked(iPresetUri, iPresetMetadata);
    return true;
}

void SourceRadio::Fetch(const Brx& aUri, const Brx& aMetaData)
{
    AutoMutex _(iLock);
    iStorePresetNumber->Set(IPresetDatabaseReader::kPresetIdNone);
    FetchLocked(aUri, aMetaData);
}

void SourceRadio::FetchLocked(const Brx& aUri, const Brx& aMetaData)
{
    if (!IsActive()) {
        DoActivate();
    }
    if (iTrack == nullptr || iTrack->Uri() != aUri) {
        if (iTrack != nullptr) {
            iTrack->RemoveRef();
        }
        iTrack = iUriProvider->SetTrack(aUri, aMetaData);
        if (iTrack != nullptr) {
            iPipeline.StopPrefetch(iUriProvider->Mode(), iTrack->Id());
        }
    }
}

/*
 * Some control points do not chain calls to SetChannel()/Play() on the provider,
 * which can result in those actions coming in out of order.
 *
 * This causes problems, particularly when no radio station has been pre-fetched,
 * as Play() does nothing due to encountering a nullptr track, followed by a valid
 * track being queued up in the pipeline via Fetch(), which never gets played
 * as the call to Play() has already been issued on a nullptr track.
 */
void SourceRadio::Play()
{
    AutoMutex _(iLock);
    if (!IsActive()) {
        DoActivate();
    }
    if (iTrack == nullptr) {
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
    iPipeline.Begin(iUriProvider->Mode(), iTrack->Id());
    DoPlay();
}

void SourceRadio::Pause()
{
    if (IsActive()) {
        if (iLive) {
            iPipeline.Stop();
        }
        else {
            try {
                iPipeline.Pause();
            }
            catch (PipelineStreamNotPausable&) {}
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

void SourceRadio::SeekRelative(TInt aSeconds)
{
    TUint abs;
    if (aSeconds < 0 && (TUint)(-aSeconds) > iTrackPosSeconds) {
        abs = 0;
    }
    else {
        abs = aSeconds + iTrackPosSeconds;
    }
    SeekAbsolute(abs);
}

void SourceRadio::NotifyPipelineState(EPipelineState aState)
{
    if (IsActive()) {
        iProviderRadio->SetTransportState(aState);
    }
}

void SourceRadio::PresetDatabaseChanged()
{
    AutoMutex _(iLock);
    if (iPresetsUpdated) {
        return;
    }
    iPresetsUpdated = true;
    if (iTrack != nullptr) {
        return;
    }
 
    const TUint presetId = iPresetDatabase->GetPresetId(iStorePresetNumber->Get());
    if (presetId == IPresetDatabaseReader::kPresetIdNone) {
        return;
    }
    if (!iPresetDatabase->TryGetPresetById(presetId, iPresetUri, iPresetMetadata)) {
        iStorePresetNumber->Set(IPresetDatabaseReader::kPresetIdNone);
        return;
    }
    iProviderRadio->NotifyPresetInfo(presetId, iPresetUri, iPresetMetadata);
    if (IsActive() && iAutoPlay) {
        iProviderRadio->NotifyPresetInfo(presetId, iPresetUri, iPresetMetadata);
        FetchLocked(iPresetUri, iPresetMetadata);
        iPipeline.Play();
    }
    else {
        iTrack = iUriProvider->SetTrack(iPresetUri, iPresetMetadata);
    }
}

void SourceRadio::NotifyMode(const Brx& /*aMode*/,
                             const ModeInfo& /*aInfo*/,
                             const ModeTransportControls& /*aTransportControls*/)
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
