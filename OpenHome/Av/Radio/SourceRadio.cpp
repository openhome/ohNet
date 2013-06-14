#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/Radio/PresetDatabase.h>
#include <OpenHome/Av/Radio/ProviderRadio.h>
#include <OpenHome/Av/Radio/TuneIn.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Av/KvpStore.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Net;
using namespace OpenHome::Media;

// SourceRadio

SourceRadio::SourceRadio(Environment& aEnv, DvDevice& aDevice, PipelineManager& aPipeline, PresetDatabase& aDatabase, UriProviderSingleTrack& aUriProvider, const TChar* aProtocolInfo, IReadStore& aReadStore)
    : Source("Radio", "Radio")
    , iPipeline(aPipeline)
    , iDatabase(aDatabase)
    , iUriProvider(aUriProvider)
    , iTrackId(UINT_MAX)
    , iTrackPosSeconds(0)
    , iPipelineTrackId(UINT_MAX)
    , iStreamId(UINT_MAX)
{
    iProviderRadio = new ProviderRadio(aDevice, *this, iDatabase, aProtocolInfo);
    Bws<40> username;
    if (aReadStore.TryReadStoreItem(Brn("Radio.TuneInUserName"), username)) {
        iTuneIn = new RadioPresetsTuneIn(aEnv, iDatabase, username);
    }
    else {
        iTuneIn = NULL; // FIXME - should maybe just initialise iTuneIn anyway (once we allow runtime change of rwstore anyway)
    }
    iPipeline.AddObserver(*this);
}

SourceRadio::~SourceRadio()
{
    delete iProviderRadio;
    delete iTuneIn;
}

void SourceRadio::Activate()
{
    iTrackPosSeconds = 0;
    iActive = true;
}

void SourceRadio::Fetch(const Brx& aUri, const Brx& aMetaData)
{
    iTrackId = iUriProvider.SetTrack(aUri, aMetaData);
    iPipeline.Begin(iUriProvider.Mode(), iTrackId);
}

void SourceRadio::Play()
{
    if (!IsActive()) {
        Activate();
    }
    iPipeline.Play();
}

void SourceRadio::Pause()
{
    if (IsActive()) {
        iPipeline.Pause();
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
        (void)iPipeline.Seek(iPipelineTrackId, iStreamId, aSeconds);
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

void SourceRadio::NotifyTrack(Track& /*aTrack*/, const Brx& /*aMode*/, TUint aIdPipeline)
{
    iPipelineTrackId = aIdPipeline;
}

void SourceRadio::NotifyMetaText(const Brx& /*aText*/)
{
}

void SourceRadio::NotifyTime(TUint aSeconds, TUint /*aTrackDurationSeconds*/)
{
    iTrackPosSeconds = aSeconds;
}

void SourceRadio::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    iStreamId = aStreamInfo.StreamId();
}
