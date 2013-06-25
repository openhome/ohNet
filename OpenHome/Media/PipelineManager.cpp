#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Pipeline.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Media/IdManager.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// PipelineManager

PipelineManager::PipelineManager(Av::IInfoAggregator& aInfoAggregator, TUint aDriverMaxAudioBytes)
    : iLock("PLMG")
{
    iPipeline = new Pipeline(aInfoAggregator, *this, aDriverMaxAudioBytes);
    iIdManager = new IdManager(*iPipeline);
    iFiller = new Filler(*iPipeline, *iIdManager);
    iProtocolManager = new ProtocolManager(*iFiller, *iIdManager, *iPipeline);
    iFiller->Start(*iProtocolManager);
}

PipelineManager::~PipelineManager()
{
    iFiller->Stop();
    delete iPipeline;
    delete iProtocolManager;
    delete iFiller;
    delete iIdManager;
    for (TUint i=0; i<iUriProviders.size(); i++) {
        delete iUriProviders[i];
    }
}

void PipelineManager::Add(Codec::CodecBase* aCodec)
{
    iPipeline->AddCodec(aCodec);
}

void PipelineManager::Add(Protocol* aProtocol)
{
    iProtocolManager->Add(aProtocol);
}

void PipelineManager::Add(ContentProcessor* aContentProcessor)
{
    iProtocolManager->Add(aContentProcessor);
}

void PipelineManager::Add(UriProvider* aUriProvider)
{
    iUriProviders.push_back(aUriProvider);
    iFiller->Add(*aUriProvider);
}

void PipelineManager::Start()
{
    iPipeline->Start();
}

void PipelineManager::AddObserver(IPipelineObserver& aObserver)
{
    iObservers.push_back(&aObserver);
}

void PipelineManager::Begin(const Brx& aMode, TUint aTrackId)
{
    iLock.Wait();
    iMode.Replace(aMode);
    iTrackId = aTrackId;
    iLock.Signal();
    iFiller->Play(aMode, aTrackId);
}

void PipelineManager::Play()
{
    iPipeline->Play();
}

void PipelineManager::Pause()
{
    iPipeline->Pause();
}

void PipelineManager::Stop()
{
    iFiller->Stop();
    iPipeline->Stop();
    iIdManager->InvalidateAll();
}

void PipelineManager::RemoveAll()
{
    iFiller->Stop();
    iLock.Wait();
    iPipeline->RemoveCurrentStream();
    iLock.Signal();
    iIdManager->InvalidateAll();
}

TBool PipelineManager::Seek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute)
{
    return iPipeline->Seek(aTrackId, aStreamId, aSecondsAbsolute);
}

void PipelineManager::Next()
{
    if (iMode.Bytes() == 0) {
        return; // nothing playing or ready to be played so nothing we can advance relative to
    }
    iFiller->Stop();
    // I think its safe to invalidate the current track only, leaving the uri provider to invalidate any others
    // can always revert to an equivalent implementation to Prev() if this proves incorrect
    iIdManager->InvalidateAt(iTrackId); // FIXME - need a pipelineTrackId here (i.e. the id associated with a MsgTrack, *not* the one associated with a Track
    iFiller->Next(iMode, iTrackId);
}

void PipelineManager::Prev()
{
    if (iMode.Bytes() == 0) {
        return; // nothing playing or ready to be played so nothing we can advance relative to
    }
    iFiller->Stop();
    iIdManager->InvalidateAll();
    iFiller->Prev(iMode, iTrackId);
}

Msg* PipelineManager::Pull()
{
    return iPipeline->Pull();
}

void PipelineManager::NotifyPipelineState(EPipelineState aState)
{
    for (TUint i=0; i<iObservers.size(); i++) {
        iObservers[i]->NotifyPipelineState(aState);
    }
}

void PipelineManager::NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline)
{
    iLock.Wait();
    iMode.Replace(aMode);
    iTrackId = aTrack.Id();
    iLock.Signal();
    for (TUint i=0; i<iObservers.size(); i++) {
        iObservers[i]->NotifyTrack(aTrack, aMode, aIdPipeline);
    }
}

void PipelineManager::NotifyMetaText(const Brx& aText)
{
    for (TUint i=0; i<iObservers.size(); i++) {
        iObservers[i]->NotifyMetaText(aText);
    }
}

void PipelineManager::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    for (TUint i=0; i<iObservers.size(); i++) {
        iObservers[i]->NotifyTime(aSeconds, aTrackDurationSeconds);
    }
}

void PipelineManager::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    for (TUint i=0; i<iObservers.size(); i++) {
        iObservers[i]->NotifyStreamInfo(aStreamInfo);
    }
}
