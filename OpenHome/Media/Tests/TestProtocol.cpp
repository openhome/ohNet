#include "TestProtocol.h"
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Pipeline/Pipeline.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Utils/DriverBasic.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>

#include <stdio.h>

int mygetch();


using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Net;
using namespace OpenHome::Av;

// DummyFiller

DummyFiller::DummyFiller(Environment& aEnv, Pipeline& aPipeline, IFlushIdProvider& aFlushIdProvider, IInfoAggregator& aInfoAggregator, IPowerManager& /*aPowerManager*/)
    : Thread("SPHt")
    , iPipeline(aPipeline)
    , iNextTrackId(kInvalidPipelineId+1)
    , iNextStreamId(kInvalidPipelineId+1)
{
    iTrackFactory = new TrackFactory(aInfoAggregator, 10);

    iProtocolManager = new ProtocolManager(aPipeline, *this, aFlushIdProvider);
    iProtocolManager->Add(ProtocolFactory::NewHttp(aEnv));
    iProtocolManager->Add(ProtocolFactory::NewFile(aEnv));
    iProtocolManager->Add(ProtocolFactory::NewTone(aEnv));
    iProtocolManager->Add(ProtocolFactory::NewRtsp(aEnv, Brn("GUID-TestProtocol-0123456789")));
}

DummyFiller::~DummyFiller()
{
    delete iProtocolManager;
    delete iTrackFactory;
}

void DummyFiller::Start(const Brx& aUrl)
{
    iUrl.Set(aUrl);
    Thread::Start();
}

void DummyFiller::Run()
{
    Track* track = iTrackFactory->CreateTrack(iUrl, Brx::Empty());
    iProtocolManager->DoStream(*track);
    track->RemoveRef();
    iPipeline.OutputQuit();

}

TUint DummyFiller::NextTrackId()
{
    return iNextTrackId++;
}

TUint DummyFiller::NextStreamId()
{
    return iNextStreamId++;
}

EStreamPlay DummyFiller::OkToPlay(TUint /*aStreamId*/)
{
    return ePlayYes;
}


// TestProtocol

TestProtocol::TestProtocol(Environment& aEnv, Net::DvStack& aDvStack, const Brx& aUrl, const Brx& /*aSenderUdn*/, TUint /*aSenderChannel*/)
    : iUrl(aUrl)
    , iStreamId(0)
{
    iPipeline = new Pipeline(PipelineInitParams::New(), iInfoAggregator, *this, *this, *this);
    iFiller = new DummyFiller(aEnv, *iPipeline, *iPipeline, iInfoAggregator, iPowerManager);

    iDriver = new DriverBasic(aDvStack.Env());
    iDriver->SetPipeline(*iPipeline);
}

TestProtocol::~TestProtocol()
{
    delete iPipeline;
    delete iFiller;
    delete iDriver;
}

int TestProtocol::Run()
{
    RegisterPlugins();
    iPipeline->Start();
    iFiller->Start(iUrl);

    TBool playing = false;
    //TBool starve = false;
    TBool quit = false;

    Log::Print("\nPipeline test using ProtocolHttp as supplier.  Usage:\n");
    Log::Print("p: Toggle between play/pause\n");
    Log::Print("n: Toggle between start/stop simulating network starvation\n");
    Log::Print("s: Stop (only valid when paused)\n");
    Log::Print("q: Quit\n");
    Log::Print("e: Emergency stop\n");
    Log::Print("\n");
    do {
        int key = mygetch();
        switch (key)
        {
        case 'p':
            playing = !playing;
            if (playing) {
                iPipeline->Play();
            }
            else {
                iPipeline->Pause();
            }
            break;
        /*case 'n':
            starve = !starve;
            if (starve) {
                iFiller->Block();
            }
            else {
                iFiller->Unblock();
            }
            break;*/
        case 's':
            if (!playing) {
                //iPipeline->Stop();
                Log::Print("Stop currently disabled.  Use TestMediaPlayer for interactive testing instead\n");
            }
            break;
        case 'q':
            quit = true;
            break;
        case 'e':
            Log::Print("Calling PowerDown() on IPowerManager\n");
            iPowerManager.PowerDown();
            quit = true;
            break;
        case '+':
        {
            TUint seekAbsolute = iSeconds + kSeekStepSeconds;
            if (seekAbsolute > iTrackDurationSeconds) {
                seekAbsolute = iTrackDurationSeconds;
            }
            (void)iPipeline->Seek(1, iStreamId, seekAbsolute);
        }
            break;
        case '-':
        {
            const TUint seekAbsolute = (iSeconds > kSeekStepSeconds? iSeconds - kSeekStepSeconds : 0);
            (void)iPipeline->Seek(1, 1, seekAbsolute);
        }
            break;
        default:
            break;
        }
    } while (!quit);

    return 0;
}

void TestProtocol::RegisterPlugins()
{
    iPipeline->AddCodec(Codec::CodecFactory::NewFlac());
    iPipeline->AddCodec(Codec::CodecFactory::NewWav());
    iPipeline->AddCodec(Codec::CodecFactory::NewAac());
    iPipeline->AddCodec(Codec::CodecFactory::NewAlac());
    iPipeline->AddCodec(Codec::CodecFactory::NewVorbis());
}

#define LOG_PIPELINE_OBSERVER
#ifdef _WIN32
// suppress 'unreferenced formal parameter' warnings which come and go depending
// on the state of LOG_PIPELINE_OBSERVER
# pragma warning(disable:4100)
#endif
void TestProtocol::NotifyPipelineState(EPipelineState aState)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline state change: %s\n", TransportState::FromPipelineState(aState));
#endif
}

void TestProtocol::NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline)
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

void TestProtocol::NotifyMetaText(const Brx& aText)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: METATEXT {");
    Log::Print(aText);
    Log::Print("}\n");
#endif
}

void TestProtocol::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    iSeconds = aSeconds;
    iTrackDurationSeconds = aTrackDurationSeconds;
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: TIME {secs=%u; duration=%u}\n", aSeconds, aTrackDurationSeconds);
#endif
}

void TestProtocol::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    iStreamId = aStreamInfo.StreamId();
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: FORMAT {bitRate=%u; bitDepth=%u, sampleRate=%u, numChannels=%u, codec=",
           aStreamInfo.BitRate(), aStreamInfo.BitDepth(), aStreamInfo.SampleRate(), aStreamInfo.NumChannels());
    Log::Print(aStreamInfo.CodecName());
    Log::Print("; trackLength=%llx, lossless=%u}\n", aStreamInfo.TrackLength(), aStreamInfo.Lossless());
#endif
}

void TestProtocol::NotifyTrackFailed(TUint /*aTrackId*/)
{
}

void TestProtocol::NotifyStreamPlayStatus(TUint /*aTrackId*/, TUint /*aStreamId*/, EStreamPlay /*aStatus*/)
{
}

TUint TestProtocol::SeekRestream(const Brx& /*aMode*/, TUint /*aTrackId*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}



int OpenHome::Media::ExecuteTestProtocol(int aArgc, char* aArgv[], CreateProtocolFunc aFunc)
{
    /* Useful test urls:
    http://10.2.9.146:26125/content/c2/b16/f44100/d2336-co13582.wav
    http://10.2.9.146:26125/content/c2/b16/f44100/d35587-co6318.flac
    http://10.2.9.146:26125/content/c2/b16/f44100/d40842-co4625.mp3
    file:///c:/test.wav
    http://10.2.11.131:9000/disk/NON-DLNA/music/O0$1$4I4009/Waiting%20for%20the%207.18.m4a  // alac
    http://10.2.11.174:26125/content/c2/b16/f48000/d2599-co459.m4a                          // aac
    http://10.2.11.174:26125/content/c2/b16/f44100/d3220-co459.ogg
    http://10.2.11.174:26125/content/c2/b16/f44100/d4505-co2377.ogg // ogg with cover art - exhausts recognise buf
    http://10.2.11.174:26125/content/c2/b16/f44100/d3450-co475.wma
    http://10.2.11.174:26125/content/c2/b16/f44100/d3395-co476.wma // wma (with cover art?) - exhausts recognise buf
    */
    OptionParser parser;
    OptionString optionUrl("", "--url", Brn("http://10.2.9.146:26125/content/c2/b16/f44100/d2336-co13582.wav"), "[url] http url of file to play");
    parser.AddOption(&optionUrl);
    OptionString optionUdn("-u", "--udn", Brn("TestProtocol"), "[udn] udn for the upnp device");
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
        Log::Print("ERROR: adapter %d doesn't exist\n", adapterIndex);
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

    //Debug::SetLevel(Debug::kSongcast);
    TestProtocol* tph = (*aFunc)(lib->Env(), *dvStack, optionUrl.Value(), optionUdn.Value(), optionChannel.Value());
    const int ret = tph->Run();
    delete tph;
    
    delete lib;

    return ret;
}
