#include <OpenHome/Av/TransportControl.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Av/ProviderTransportControlEriskay.h>

using namespace OpenHome;
using namespace OpenHome::Av;

TransportControl::TransportControl(Net::DvDevice& aDevice, Media::PipelineManager& aPipeline)
    : iLock("MTPC")
    , iPipeline(aPipeline)
    , iPlaySupported(false)
    , iPauseSupported(false)
    , iStopSupported(false)
    , iNextSupported(false)
    , iPrevSupported(false)
    , iSeekSupported(false)
    , iStreamId(Media::IPipelineIdProvider::kStreamIdInvalid)
{
    iProvider = new ProviderTransportControlEriskay(aDevice, *this);
    iPipeline.AddObserver(*this);
}

TransportControl::~TransportControl()
{
    delete iProvider;
}

void TransportControl::Play()
{
    AutoMutex _(iLock);
    if (!iPlaySupported) {
        THROW(TransportControlActionNotAllowed);
    }
    iPipeline.Play();
}

void TransportControl::Pause(TUint aStreamId)
{
    AutoMutex _(iLock);
    if (iStreamId != aStreamId) {
        THROW(TransportControlIncorrectStreamId);
    }
    if (!iPauseSupported) {
        THROW(TransportControlActionNotAllowed);
    }
    iPipeline.Pause();
}

void TransportControl::Stop(TUint aStreamId)
{
    AutoMutex _(iLock);
    if (iStreamId != aStreamId) {
        THROW(TransportControlIncorrectStreamId);
    }
    if (!iStopSupported) {
        THROW(TransportControlActionNotAllowed);
    }
    iPipeline.Stop();
}

void TransportControl::Next(TUint aStreamId)
{
    AutoMutex _(iLock);
    if (iStreamId != aStreamId) {
        THROW(TransportControlIncorrectStreamId);
    }
    if (!iNextSupported) {
        THROW(TransportControlActionNotAllowed);
    }
    iPipeline.Next();
}

void TransportControl::Prev(TUint aStreamId)
{
    AutoMutex _(iLock);
    if (iStreamId != aStreamId) {
        THROW(TransportControlIncorrectStreamId);
    }
    if (!iPrevSupported) {
        THROW(TransportControlActionNotAllowed);
    }
    iPipeline.Prev();
}

void TransportControl::SeekSecondsAbsolute(TUint aStreamId, TUint aSeconds)
{
    AutoMutex _(iLock);
    SeekLocked(aStreamId, aSeconds);
}

void TransportControl::SeekSecondsRelative(TUint aStreamId, TInt aSeconds)
{
    AutoMutex _(iLock);
    iSeconds += aSeconds;
    SeekLocked(aStreamId, aSeconds);
}

void TransportControl::SeekLocked(TUint aStreamId, TUint aSecondsAbsolute)
{
    if (iStreamId != aStreamId) {
        THROW(TransportControlIncorrectStreamId);
    }
    if (!iSeekSupported) {
        THROW(TransportControlActionNotAllowed);
    }
    if (!iPipeline.Seek(aStreamId, aSecondsAbsolute)) {
        THROW(TransportControlIncorrectStreamId);
    }
}

void TransportControl::NotifyPipelineState(Media::EPipelineState aState)
{
    iProvider->NotifyState(aState);
}

void TransportControl::NotifyTrack(Media::Track& /*aTrack*/, const Brx& /*aMode*/, TBool /*aStartOfStream*/)
{
}

void TransportControl::NotifyMetaText(const Brx& /*aText*/)
{
}

void TransportControl::NotifyTime(TUint aSeconds, TUint /*aTrackDurationSeconds*/)
{
    iLock.Wait();
    iSeconds = aSeconds;
    iLock.Signal();
}

void TransportControl::NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo)
{
    iLock.Wait();
    iStreamId       =  aStreamInfo.StreamId();
    iPauseSupported = !aStreamInfo.Live();
    iSeekSupported  =  aStreamInfo.Seekable();
    iLock.Signal();
    iProvider->NotifyStream(iStreamId, iPauseSupported, iSeekSupported);
}
