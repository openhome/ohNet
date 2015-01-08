#include "TestRadio.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Av/UpnpAv/UpnpAv.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Av/Utils/DriverSongcastSender.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Av/Radio/ContentProcessorFactory.h>
#include <OpenHome/Av/Radio/PresetDatabase.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Media/Pipeline/Pipeline.h>

#include <ctype.h>
#include <limits.h>
#include <stdio.h>

int mygetch();


using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;
using namespace OpenHome::Av::Test;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// TestRadio

TestRadio::TestRadio(DvStack& aDvStack, const Brx& aSenderUdn, TUint aSenderChannel)
{
    static const TUint kMaxDriverJiffies = Jiffies::kPerMs * 5;
    iTrackFactory = new TrackFactory(iInfoLogger, kTrackCount);
    iPipeline = new PipelineManager(PipelineInitParams::New(), iInfoLogger, *iTrackFactory);
    iPipeline->AddObserver(*this);
    iEnv = &aDvStack.Env();

    iDriver = new DriverSongcastSender(*iPipeline, kMaxDriverJiffies, aDvStack, aSenderUdn, aSenderChannel);
    iUriProvider = new UriProviderSingleTrack("Radio", false, false, *iTrackFactory);
    iPipeline->Add(iUriProvider);
//    iSourceUpnpAv = new DummySourceUpnpAv(aDvStack, *iPipeline, *iUriProvider);
}

TestRadio::~TestRadio()
{
    delete iPipeline;
    delete iDriver;
//    delete iSourceUpnpAv;
    delete iTrackFactory;
}

void TestRadio::Run(PresetDatabase& aDb)
{
    Log::Print("\nRadio test.  Press 'q' to quit:\n");
    Log::Print("\n");
    RegisterPlugins(*iEnv);
    iPipeline->Start();
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

void TestRadio::RegisterPlugins(Environment& aEnv)
{
    // Add codecs
    iPipeline->Add(Codec::CodecFactory::NewAac());
    iPipeline->Add(Codec::CodecFactory::NewAlac());
    iPipeline->Add(Codec::CodecFactory::NewAdts());
    iPipeline->Add(Codec::CodecFactory::NewFlac());
    iPipeline->Add(Codec::CodecFactory::NewVorbis());
    iPipeline->Add(Codec::CodecFactory::NewWav());

    // Add protocol modules
    iPipeline->Add(ProtocolFactory::NewHttp(aEnv));
    iPipeline->Add(ProtocolFactory::NewHttp(aEnv));
    iPipeline->Add(ProtocolFactory::NewHttp(aEnv));
    iPipeline->Add(ProtocolFactory::NewHttp(aEnv));
    iPipeline->Add(ProtocolFactory::NewHttp(aEnv));
    iPipeline->Add(ProtocolFactory::NewRtsp(aEnv, Brn("notarealguid")));

    // Add content processors
    iPipeline->Add(ContentProcessorFactory::NewM3u());
    iPipeline->Add(ContentProcessorFactory::NewM3u());
    iPipeline->Add(ContentProcessorFactory::NewPls());
    iPipeline->Add(ContentProcessorFactory::NewPls());
    iPipeline->Add(ContentProcessorFactory::NewOpml());
    iPipeline->Add(ContentProcessorFactory::NewOpml());
    iPipeline->Add(ContentProcessorFactory::NewAsx());
    iPipeline->Add(ContentProcessorFactory::NewAsx());
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
    Log::Print("Pipeline state change: %s\n", TransportState::FromPipelineState(aState));
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


int OpenHome::Av::Test::ExecuteTestRadio(int aArgc, char* aArgv[], CreateRadioFunc aFunc, std::vector<const TChar*> aPresets)
{
    OptionParser parser;
    OptionString optionUdn("-u", "--udn", Brn("TestRadioSender"), "[udn] udn for the upnp device");
    parser.AddOption(&optionUdn);
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
    Library::DestroySubnetList(subnetList);
    lib->SetCurrentSubnet(subnet);
    Log::Print("using subnet %d.%d.%d.%d\n", subnet&0xff, (subnet>>8)&0xff, (subnet>>16)&0xff, (subnet>>24)&0xff);

    PresetDatabase* db = new PresetDatabase();
    db->BeginSetPresets();
    for (TUint i=0; i<aPresets.size(); i++) {
        Brn urlAsMetaData(aPresets[i]);
        (void)db->SetPreset(i, urlAsMetaData, urlAsMetaData);
    }
    db->EndSetPresets();
    TestRadio* tr = (*aFunc)(*dvStack, optionUdn.Value(), optionChannel.Value());
    tr->Run(*db);
    delete tr;
    delete db;
    
    delete lib;

    return 0;
}
