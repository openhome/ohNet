#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Av/UpnpAv/UpnpAv.h>
#include <OpenHome/Av/UpnpAv/ProviderAvTransport.h>
#include <OpenHome/Av/UpnpAv/ProviderConnectionManager.h>
#include <OpenHome/Av/UpnpAv/ProviderRenderingControl.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Av/Utils/DriverSongcastSender.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>

#include <climits>
#include <stdio.h>

#ifdef _WIN32
#if !defined(CDECL)
# define CDECL __cdecl
#endif

# include <conio.h>

int mygetch()
{
    return (_getch());
}

#elif defined(NOTERMIOS)

#define CDECL

int mygetch()
{
    return 0;
}

#else

# define CDECL

# include <termios.h>
# include <unistd.h>

int mygetch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

#endif // _WIN32

namespace OpenHome {
namespace Av {

class DummySourceUpnpAv : private IPipelineObserver, private ISourceUpnpAv, private INonCopyable
{
    static const Brn kDummyBrn;
public:
    DummySourceUpnpAv(DvStack& aDvStack, PipelineManager& aPipelineManager, UriProviderSingleTrack& aUriProvider);
    ~DummySourceUpnpAv();
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState) override;
    void NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) override;
private: // from ISourceUpnpAv
    void SetTrack(const Brx& aUri, const Brx& aMetaData) override;
    void Play() override;
    void Pause() override;
    void Stop() override;
    void Next() override;
    void Prev() override;
    void Seek(TUint aSecondsAbsolute) override;
private:
    PipelineManager& iPipeline;
    UriProviderSingleTrack& iUriProvider;
    UpnpAv* iUpnpAv;
    TBool iActive;
    IPipelineObserver* iDownstreamObserver;
    TUint iStreamId;
};

class TestUpnpAv
{
    static const TUint kTrackCount = 3;
public:
    TestUpnpAv(DvStack& aDvStack, const Brx& aSenderUdn, TUint aSenderChannel);
    ~TestUpnpAv();
    void Run();
private:
    AllocatorInfoLogger iInfoLogger;
    PipelineManager* iPipeline;
    TrackFactory* iTrackFactory;
    DriverSongcastSender* iDriver;
    UriProviderSingleTrack* iUriProvider;
    DummySourceUpnpAv* iSourceUpnpAv;
};

} // namespace Av
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// DummySourceUpnpAv

const Brn DummySourceUpnpAv::kDummyBrn("udn-TestUpnpAv");
static const TChar* kDummyFriendlyName = "TestUpnpAv";
static const TChar* kDummyManufacturer = "None";
static const TChar* kDummyModelName = "SoftPlayer";
static const TChar* kSupportedProtocols = 
    "http-get:*:audio/x-flac:*,"
    "http-get:*:audio/wav:*,"
    "http-get:*:audio/wave:*,"
    "http-get:*:audio/x-wav:*,"
    "http-get:*:audio/aiff:*,"
    "http-get:*:audio/x-aiff:*,"
    "http-get:*:audio/x-m4a:*,"
    "http-get:*:audio/x-scpls:*,"
    "http-get:*:text/xml:*,"
    "http-get:*:audio/aac:*,"
    "http-get:*:audio/aacp:*,"
    "http-get:*:audio/mp4:*,"
    "http-get:*:audio/ogg:*,"
    "http-get:*:audio/x-ogg:*,"
    "http-get:*:application/ogg:*";

DummySourceUpnpAv::DummySourceUpnpAv(DvStack& aDvStack, PipelineManager& aPipelineManager, UriProviderSingleTrack& aUriProvider)
    : iPipeline(aPipelineManager)
    , iUriProvider(aUriProvider)
    , iActive(true)
{
    iUpnpAv = new UpnpAv(aDvStack, *this, kDummyBrn, kDummyFriendlyName, kDummyManufacturer, kDummyModelName, kSupportedProtocols);
    iDownstreamObserver = iUpnpAv;

}

DummySourceUpnpAv::~DummySourceUpnpAv()
{
    delete iUpnpAv;
}

void DummySourceUpnpAv::NotifyPipelineState(EPipelineState aState)
{
    if (iActive) {
        iDownstreamObserver->NotifyPipelineState(aState);
    }
}

void DummySourceUpnpAv::NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream)
{
    iStreamId = UINT_MAX;
    if (iActive) {
        iDownstreamObserver->NotifyTrack(aTrack, aMode, aStartOfStream);
    }
}

void DummySourceUpnpAv::NotifyMetaText(const Brx& aText)
{
    if (iActive) {
        iDownstreamObserver->NotifyMetaText(aText);
    }
}

void DummySourceUpnpAv::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    if (iActive) {
        iDownstreamObserver->NotifyTime(aSeconds, aTrackDurationSeconds);
    }
}

void DummySourceUpnpAv::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    iStreamId = aStreamInfo.StreamId();
    if (iActive) {
        iDownstreamObserver->NotifyStreamInfo(aStreamInfo);
    }
}

void DummySourceUpnpAv::SetTrack(const Brx& /*aUri*/, const Brx& /*aMetaData*/)
{
    iPipeline.Stop();
    // FIXME - requires update following updates to replace providerId with uint trackId
    // FIXME - aMetaData not being passed onto iUriProvider
    //iPipeline.Begin(iUriProvider.Mode(), aUri);
}

void DummySourceUpnpAv::Play()
{
    if (iActive) {
        iPipeline.Play();
    }
}

void DummySourceUpnpAv::Pause()
{
    if (iActive) {
        iPipeline.Pause();
    }
}

void DummySourceUpnpAv::Stop()
{
    if (iActive) {
        iPipeline.Stop();
    }
}

void DummySourceUpnpAv::Next()
{
    if (iActive) {
        iPipeline.Stop();
    }
}

void DummySourceUpnpAv::Prev()
{
    if (iActive) {
        iPipeline.Stop();
    }
}

void DummySourceUpnpAv::Seek(TUint aSecondsAbsolute)
{
    if (iActive) {
        iPipeline.Seek(iStreamId, aSecondsAbsolute);
    }
}


// TestUpnpAv

TestUpnpAv::TestUpnpAv(DvStack& aDvStack, const Brx& aSenderUdn, TUint aSenderChannel)
{
    static const TUint kMaxDriverJiffies = Jiffies::kPerMs * 5;
    iTrackFactory = new TrackFactory(iInfoLogger, kTrackCount);
    iPipeline = new PipelineManager(iInfoLogger, *iTrackFactory, kMaxDriverJiffies);
    iPipeline->Add(Codec::CodecFactory::NewAac());
    iPipeline->Add(Codec::CodecFactory::NewAlac());
    iPipeline->Add(Codec::CodecFactory::NewFlac());
    iPipeline->Add(Codec::CodecFactory::NewMp3());
    iPipeline->Add(Codec::CodecFactory::NewVorbis());
    iPipeline->Add(Codec::CodecFactory::NewWav());
    iPipeline->Add(Codec::CodecFactory::NewWma());
    iPipeline->Add(ProtocolFactory::NewHttp(aDvStack.Env()));
    iDriver = new DriverSongcastSender(*iPipeline, kMaxDriverJiffies, aDvStack, aSenderUdn, aSenderChannel);
    iUriProvider = new UriProviderSingleTrack("UpnpAv", false, false, *iTrackFactory);
    iPipeline->Add(iUriProvider);
    iPipeline->Start();
    iSourceUpnpAv = new DummySourceUpnpAv(aDvStack, *iPipeline, *iUriProvider);
}

TestUpnpAv::~TestUpnpAv()
{
    delete iPipeline;
    delete iDriver;
    delete iSourceUpnpAv;
    delete iUriProvider;
    delete iTrackFactory;
}

void TestUpnpAv::Run()
{
    Log::Print("\nUPnP:AV test.  Press 'q' to quit:\n");
    Log::Print("\n");
    while (mygetch() != 'q')
        ;
}



int CDECL main(int aArgc, char* aArgv[])
{
    OptionParser parser;
    OptionString optionUdn("-u", "--udn", Brn("TestUpnpAvSender"), "[udn] udn for the upnp device");
    parser.AddOption(&optionUdn);
    OptionUint optionChannel("-c", "--channel", 0, "[0..65535] sender channel");
    parser.AddOption(&optionChannel);
    OptionUint optionAdapter("-a", "--adapter", 0, "[adapter] index of network adapter to use");
    parser.AddOption(&optionAdapter);

    if (!parser.Parse(aArgc, aArgv)) {
        return 1;
    }

    InitialisationParams* initParams = InitialisationParams::Create();
    Net::Library* lib = new Net::Library(initParams);
    Net::DvStack* dvStack = lib->StartDv();
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    const TUint adapterIndex = optionAdapter.Value();
    if (subnetList->size() <= adapterIndex) {
        Log::Print("ERROR: adapter %u doesn't exist\n", adapterIndex);
        ASSERTS();
    }
    Log::Print ("adapter list:\n");
    for (unsigned i=0; i<subnetList->size(); ++i) {
        TIpAddress addr = (*subnetList)[i]->Address();
        Log::Print ("  %d: %d.%d.%d.%d\n", i, addr&0xff, (addr>>8)&0xff, (addr>>16)&0xff, (addr>>24)&0xff);
    }
    TIpAddress subnet = (*subnetList)[adapterIndex]->Subnet();
    TIpAddress adapter = (*subnetList)[adapterIndex]->Address();
    Library::DestroySubnetList(subnetList);
    lib->SetCurrentSubnet(subnet);
    Log::Print("using subnet %d.%d.%d.%d\n", subnet&0xff, (subnet>>8)&0xff, (subnet>>16)&0xff, (subnet>>24)&0xff);

    TestUpnpAv* tuav = new TestUpnpAv(*dvStack, optionUdn.Value(), optionChannel.Value());
    tuav->Run();
    delete tuav;
    
    delete lib;

    return 0;
}
