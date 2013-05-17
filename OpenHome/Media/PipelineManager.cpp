#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Pipeline.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Media/IdProvider.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// PipelineManager

PipelineManager::PipelineManager(Av::IInfoAggregator& aInfoAggregator, TUint aDriverMaxAudioBytes)
    : iLock("PLMG")
{
    iPipeline = new Pipeline(aInfoAggregator, *this, aDriverMaxAudioBytes);
    iIdProvider = new PipelineIdProvider(*iPipeline);
    iFiller = new Filler(*iPipeline, *iIdProvider);
    iProtocolManager = new ProtocolManager(*iFiller, *iIdProvider, *iPipeline);
    iFiller->Start(*iProtocolManager);
}

PipelineManager::~PipelineManager()
{
    iFiller->Stop();
    delete iPipeline;
    delete iProtocolManager;
    delete iFiller;
    delete iIdProvider;
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

void PipelineManager::Begin(const Brx& aStyle, const Brx& aProviderId)
{
    iLock.Wait();
    iStyle.Replace(aStyle);
    iProviderId.Replace(aProviderId);
    iLock.Signal();
    iFiller->Play(aStyle, aProviderId);
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
    static_cast<IPipelineIdProvider*>(iIdProvider)->InvalidateAll();
}

TBool PipelineManager::Seek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute)
{
    return iPipeline->Seek(aTrackId, aStreamId, aSecondsAbsolute);
}

void PipelineManager::Next()
{
    if (iStyle.Bytes() == 0 && iProviderId.Bytes() == 0) {
        return; // nothing playing or ready to be played so nothing we to advance relative to
    }
    iFiller->Stop();
    // I think its safe to invalidate the current track only, leaving the uri provider to invalidate any others
    // can always revert to an equivalent implementation to Prev() if this proves incorrect
    static_cast<IPipelineIdProvider*>(iIdProvider)->InvalidateAt(iStyle, iProviderId);
    iFiller->Next(iStyle, iProviderId);
}

void PipelineManager::Prev()
{
    if (iStyle.Bytes() == 0 && iProviderId.Bytes() == 0) {
        return; // nothing playing or ready to be played so nothing we to advance relative to
    }
    iFiller->Stop();
    static_cast<IPipelineIdProvider*>(iIdProvider)->InvalidateAll();
    iFiller->Prev(iStyle, iProviderId);
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

void PipelineManager::NotifyTrack(Track& aTrack, TUint aIdPipeline)
{
    iLock.Wait();
    iStyle.Replace(aTrack.Style());
    iProviderId.Replace(aTrack.ProviderId());
    iLock.Signal();
    for (TUint i=0; i<iObservers.size(); i++) {
        iObservers[i]->NotifyTrack(aTrack, aIdPipeline);
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
