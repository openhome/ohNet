#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/Tests/AllocatorInfoLogger.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/Av/Product.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// MediaPlayer

MediaPlayer::MediaPlayer(Net::DvStack& aDvStack, Net::DvDevice& aDevice, TUint aDriverMaxJiffies, IStaticDataSource& aStaticDataSource, IPersister& aPersistor)
    : iDvStack(aDvStack)
    , iDevice(aDevice)
{
    iInfoLogger = new AllocatorInfoLogger();
    iPipelineObserver = new LoggingPipelineObserver();
    iKvpStore = new KvpStore(aStaticDataSource, aPersistor);
    iPipeline = new PipelineManager(*iInfoLogger, aDriverMaxJiffies);
    iPipeline->AddObserver(*iPipelineObserver);
    iTrackFactory = new Media::TrackFactory(*iInfoLogger, kTrackCount);
    iProduct = new Product(aDevice, *iKvpStore, *iInfoLogger);
}

MediaPlayer::~MediaPlayer()
{
    ASSERT(!iDevice.Enabled());
    delete iPipeline;
    delete iTrackFactory;
    delete iProduct;
    delete iKvpStore;
    delete iInfoLogger;
    delete iPipelineObserver;
}

void MediaPlayer::Add(Codec::CodecBase* aCodec)
{
    iPipeline->Add(aCodec);
}

void MediaPlayer::Add(Protocol* aProtocol)
{
    iPipeline->Add(aProtocol);
}

void MediaPlayer::Add(ContentProcessor* aContentProcessor)
{
    iPipeline->Add(aContentProcessor);
}

void MediaPlayer::Add(ISource* aSource)
{
    iProduct->AddSource(aSource);
}

void MediaPlayer::AddAttribute(const TChar* aAttribute)
{
    iProduct->AddAttribute(aAttribute);
}

void MediaPlayer::Start()
{
    iProduct->SetCurrentSource(0); // FIXME - could be available (and left) to client code
    iPipeline->Start();
    iProduct->Start();
}

Environment& MediaPlayer::Env()
{
    return iDvStack.Env();
}

Net::DvStack& MediaPlayer::DvStack()
{
    return iDvStack;
}

Net::DvDevice& MediaPlayer::Device()
{
    return iDevice;
}

Media::PipelineManager& MediaPlayer::Pipeline()
{
    return *iPipeline;
}

Media::TrackFactory& MediaPlayer::TrackFactory()
{
    return *iTrackFactory;
}

IReadStore& MediaPlayer::ReadStore()
{
    return *iKvpStore;
}

void MediaPlayer::Add(UriProvider* aUriProvider)
{
    iPipeline->Add(aUriProvider);
}
