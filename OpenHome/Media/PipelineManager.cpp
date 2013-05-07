#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Pipeline.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Media/IdProvider.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// PipelineManager

PipelineManager::PipelineManager(Av::IInfoAggregator& aInfoAggregator, TUint aDriverMaxAudioBytes)
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

Msg* PipelineManager::Pull()
{
    return iPipeline->Pull();
}

void PipelineManager::NotifyPipelineState(EPipelineState /*aState*/)
{
}

void PipelineManager::NotifyTrack(Track& /*aTrack*/, TUint /*aIdPipeline*/)
{
}

void PipelineManager::NotifyMetaText(const Brx& /*aText*/)
{
}

void PipelineManager::NotifyTime(TUint /*aSeconds*/, TUint /*aTrackDurationSeconds*/)
{
}

void PipelineManager::NotifyStreamInfo(const DecodedStreamInfo& /*aStreamInfo*/)
{
}
