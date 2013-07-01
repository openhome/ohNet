#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Av/UpnpAv/UpnpAv.h>
#include <OpenHome/Media/Tests/AllocatorInfoLogger.h>
#include <OpenHome/Media/Tests/SongcastingDriver.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Av/Radio/PresetDatabase.h>
#include <OpenHome/Av/Debug.h>

#include <ctype.h>
#include <limits.h>
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
    
class PresetDatabase;

class TestRadio : private Media::IPipelineObserver
{
    static const TUint kTrackCount = 3;
public:
    TestRadio(Net::DvStack& aDvStack, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel);
    ~TestRadio();
    void Run(PresetDatabase& aDb);
private: // from Media::IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState);
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo);
private:
    Media::AllocatorInfoLogger iInfoLogger;
    Media::PipelineManager* iPipeline;
    Media::TrackFactory* iTrackFactory;
    Media::SimpleSongcastingDriver* iDriver;
    Media::UriProviderSingleTrack* iUriProvider;
    //DummySourceUpnpAv* iSourceUpnpAv;
};

} // namespace Av
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// TestRadio

TestRadio::TestRadio(DvStack& aDvStack, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel)
{
    iPipeline = new PipelineManager(iInfoLogger, SimpleSongcastingDriver::kMaxDriverJiffies);
    iPipeline->AddObserver(*this);
    iPipeline->Add(Codec::CodecFactory::NewAac());
    iPipeline->Add(Codec::CodecFactory::NewAlac());
    iPipeline->Add(Codec::CodecFactory::NewAdts());
    iPipeline->Add(Codec::CodecFactory::NewFlac());
    iPipeline->Add(Codec::CodecFactory::NewMp3());
    iPipeline->Add(Codec::CodecFactory::NewVorbis());
    iPipeline->Add(Codec::CodecFactory::NewWav());
    iPipeline->Add(Codec::CodecFactory::NewWma());
    Environment& env = aDvStack.Env();
    iPipeline->Add(ProtocolFactory::NewHttp(env));
    iPipeline->Add(ProtocolFactory::NewHttp(env));
    iPipeline->Add(ProtocolFactory::NewHttp(env));
    iPipeline->Add(ProtocolFactory::NewHttp(env));
    iPipeline->Add(ProtocolFactory::NewHttp(env));
    iPipeline->Add(ContentProcessorFactory::NewM3u());
    iPipeline->Add(ContentProcessorFactory::NewM3u());
    iPipeline->Add(ContentProcessorFactory::NewPls());
    iPipeline->Add(ContentProcessorFactory::NewPls());
    iPipeline->Add(ContentProcessorFactory::NewOpml());
    iPipeline->Add(ContentProcessorFactory::NewOpml());
    iTrackFactory = new TrackFactory(iInfoLogger, kTrackCount);
    iDriver = new SimpleSongcastingDriver(aDvStack, *iPipeline, aAdapter, aSenderUdn, aSenderFriendlyName, aSenderChannel);
    iUriProvider = new UriProviderSingleTrack("Radio", *iTrackFactory);
    iPipeline->Add(iUriProvider);
    iPipeline->Start();
//    iSourceUpnpAv = new DummySourceUpnpAv(aDvStack, *iPipeline, *iUriProvider);
}

TestRadio::~TestRadio()
{
    delete iPipeline;
    delete iDriver;
//    delete iSourceUpnpAv;
    delete iUriProvider;
    delete iTrackFactory;
}

void TestRadio::Run(PresetDatabase& aDb)
{
    Log::Print("\nRadio test.  Press 'q' to quit:\n");
    Log::Print("\n");
    for (;;) {
        int ch = mygetch();
        if (ch == 'q') {
            break;
        }
        if (isdigit(ch)) {
            TUint index = ch - '0';
            Log::Print("Try to play preset index %u\n", index);
            Bws<1024> uri;
            TUint ignore;
            aDb.GetPreset(index, ignore, uri);
            iPipeline->Stop();
            Track* track = iUriProvider->SetTrack(uri, Brx::Empty());
            iPipeline->Begin(iUriProvider->Mode(), track->Id());
            iPipeline->Play();
        }
        else {
            Log::Print("Unsupported command - %c\n", (char)ch);
        }
    }
}

#define LOG_PIPELINE_OBSERVER
#ifndef LOG_PIPELINE_OBSERVER
# ifdef _WIN32
// suppress 'unreferenced formal parameter' warnings which come and go depending
// on the state of LOG_PIPELINE_OBSERVER
#  pragma warning(disable:4100)
# endif // _WIN32
#endif // !LOG_PIPELINE_OBSERVER
void TestRadio::NotifyPipelineState(EPipelineState aState)
{
#ifdef LOG_PIPELINE_OBSERVER
    const char* state = "";
    switch (aState)
    {
    case EPipelinePlaying:
        state = "playing";
        break;
    case EPipelinePaused:
        state = "paused";
        break;
    case EPipelineStopped:
        state = "stopped";
        break;
    case EPipelineBuffering:
        state = "buffering";
        break;
    default:
        ASSERTS();
    }
    Log::Print("Pipeline state change: %s\n", state);
#endif
}

void TestRadio::NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: TRACK {uri=");
    Log::Print(aTrack.Uri());
    Log::Print("; metadata=");
    Log::Print(aTrack.MetaData());
    Log::Print("; mode=");
    Log::Print(aMode);
    Log::Print("; trackId=%u; idPipeline=%u}\n", aTrack.Id(), aIdPipeline);
#endif
}

void TestRadio::NotifyMetaText(const Brx& aText)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: METATEXT {");
    Log::Print(aText);
    Log::Print("}\n");
#endif
}

void TestRadio::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: TIME {secs=%u; duration=%u}\n", aSeconds, aTrackDurationSeconds);
#endif
}

void TestRadio::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: FORMAT {bitRate=%u; bitDepth=%u, sampleRate=%u, numChannels=%u, codec=",
           aStreamInfo.BitRate(), aStreamInfo.BitDepth(), aStreamInfo.SampleRate(), aStreamInfo.NumChannels());
    Log::Print(aStreamInfo.CodecName());
    Log::Print("; trackLength=%llx, lossless=%u}\n", aStreamInfo.TrackLength(), aStreamInfo.Lossless());
#endif
}


int CDECL main(int aArgc, char* aArgv[])
{
    OptionParser parser;
    OptionString optionUdn("-u", "--udn", Brn("TestRadioSender"), "[udn] udn for the upnp device");
    parser.AddOption(&optionUdn);
    OptionString optionName("-n", "--name", Brn("TestRadioSender"), "[name] name of the sender");
    parser.AddOption(&optionName);
    OptionUint optionChannel("-c", "--channel", 0, "[0..65535] sender channel");
    parser.AddOption(&optionChannel);
    OptionUint optionAdapter("-a", "--adapter", 0, "[adapter] index of network adapter to use");
    parser.AddOption(&optionAdapter);

    if (!parser.Parse(aArgc, aArgv)) {
        return 1;
    }

    InitialisationParams* initParams = InitialisationParams::Create();
    //Debug::SetLevel(Debug::kMedia);
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

    PresetDatabase* db = new PresetDatabase();
    db->BeginSetPresets();
    const TChar* presets[] = {
        "http://opml.radiotime.com/Tune.ashx?id=s122119&formats=mp3,wma,aac,wmvideo,ogg&partnerId=ah2rjr68&username=chisholmsi&c=ebrowse" // (Linn Radio, MP3)
       ,"http://opml.radiotime.com/Tune.ashx?id=s2377&formats=mp3,wma,aac,wmvideo,ogg&partnerId=ah2rjr68&username=chisholmsi&c=ebrowse"   // (Planet Rock, AAC, 22.05KHz, mono)
       ,"http://opml.radiotime.com/Tune.ashx?id=s24940&formats=mp3,wma,aac,wmvideo,ogg&partnerId=ah2rjr68&username=chisholmsi&c=ebrowse"  // (Radio 2, AAC)
       ,"http://opml.radiotime.com/Tune.ashx?id=s92182&formats=mp3,wma,aac,wmvideo,ogg&partnerId=ah2rjr68&username=chisholmsi&c=ebrowse"  // (Birdsong Radio, MP3)
       ,"http://opml.radiotime.com/Tune.ashx?id=s24945&formats=mp3,wma,aac,wmvideo,ogg&partnerId=ah2rjr68&username=chisholmsi&c=ebrowse"  // (Radio Scotland, WMA)
    };
    for (TUint i=0; i<sizeof(presets)/sizeof(presets[0]); i++) {
        Brn urlAsMetaData(presets[i]);
        (void)db->SetPreset(i, urlAsMetaData, urlAsMetaData);
    }
    db->EndSetPresets();
    TestRadio* tr = new TestRadio(*dvStack, adapter, optionUdn.Value(), optionName.CString(), optionChannel.Value());
    tr->Run(*db);
    delete tr;
    delete db;
    
    delete lib;

    return 0;
}
