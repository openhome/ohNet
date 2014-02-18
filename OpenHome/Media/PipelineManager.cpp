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
    , iPipelineState(EPipelineStopped)
    , iPipelineStoppedSem("PLMG", 1)
{
    iPipeline = new Pipeline(aInfoAggregator, *this, aDriverMaxAudioBytes);
    iIdManager = new IdManager(*iPipeline);
    iFiller = new Filler(*iPipeline, *iIdManager);
    iProtocolManager = new ProtocolManager(*iFiller, *iIdManager, *iPipeline);
    iFiller->Start(*iProtocolManager);
}

PipelineManager::~PipelineManager()
{
    TUint haltId = MsgHalt::kIdInvalid;
    iLock.Wait();
    const TBool waitStop = (iPipelineState != EPipelineStopped);
    if (waitStop) {
        haltId = iFiller->Stop();
    }
    else {
        iFiller->StopNoHalt();
    }
    iPipeline->RemoveCurrentStream();
    iLock.Signal();
    iIdManager->InvalidatePending();
    if (waitStop) {
        iPipeline->Stop(haltId);
        iPipelineStoppedSem.Wait();
    }

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
    iLock.Wait();
    iObservers.push_back(&aObserver);
    iLock.Signal();
}

void PipelineManager::RemoveObserver(IPipelineObserver& aObserver)
{
    iLock.Wait();
    for (TUint i=0; i<iObservers.size(); i++) {
        if (iObservers[i] == &aObserver) {
            iObservers.erase(iObservers.begin()+i);
            break;
        }
    }
    iLock.Signal();
}

void PipelineManager::AddObserver(ITrackObserver& aObserver)
{
    iPipeline->AddObserver(aObserver);
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
    const TUint haltId = iFiller->Stop();
    iPipeline->Stop(haltId);
    iIdManager->InvalidatePending(); /* don't use InvalidateAll - iPipeline->Stop() will
                                        have removed current stream.  InvalidateAll ends
                                        up with Stopper trying to halt (pause) which would
                                        override the attempt to Stop it. */
}

void PipelineManager::StopPrefetch(const Brx& aMode, TUint aTrackId)
{
    /*const TUint haltId = */iFiller->Stop(); // FIXME - could get away without Filler generating a Halt here
    iPipeline->RemoveCurrentStream();
    iIdManager->InvalidatePending();
    iFiller->PlayLater(aMode, aTrackId);
    iPipeline->Play(); // in case pipeline is paused/stopped, force it to pull until a new track
}

void PipelineManager::RemoveAll()
{
    /*TUint haltId = */iFiller->Stop();
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
    iIdManager->InvalidateAt(iTrackId);
    iFiller->Next(iMode);
}

void PipelineManager::Prev()
{
    if (iMode.Bytes() == 0) {
        return; // nothing playing or ready to be played so nothing we can advance relative to
    }
    iFiller->Stop();
    iIdManager->InvalidateAll();
    iFiller->Prev(iMode);
}

TBool PipelineManager::SupportsMimeType(const Brx& aMimeType)
{
    return iPipeline->SupportsMimeType(aMimeType);
}

IPipelineElementDownstream* PipelineManager::SetSender(IPipelineElementDownstream& aSender)
{
    return iPipeline->SetSender(aSender);
}

Msg* PipelineManager::Pull()
{
    return iPipeline->Pull();
}

void PipelineManager::InvalidateAt(TUint aId)
{
    iIdManager->InvalidateAt(aId);
}

void PipelineManager::InvalidateAfter(TUint aId)
{
    iIdManager->InvalidateAfter(aId);
}

void PipelineManager::InvalidatePending()
{
    iIdManager->InvalidatePending();
}

void PipelineManager::InvalidateAll()
{
    iIdManager->InvalidateAll();
}

void PipelineManager::NotifyPipelineState(EPipelineState aState)
{
    for (TUint i=0; i<iObservers.size(); i++) {
        iObservers[i]->NotifyPipelineState(aState);
    }
    iLock.Wait();
    iPipelineState = aState;
    iLock.Signal();
    if (iPipelineState == EPipelineStopped) {
        iPipelineStoppedSem.Signal();
    }
    else {
        (void)iPipelineStoppedSem.Clear();
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
