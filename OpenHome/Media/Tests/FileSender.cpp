#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Codec/Flac.h>
#include <OpenHome/Media/Codec/Wav.h>
#include <OpenHome/Media/DriverSongcastSender.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Debug.h>
#include "AllocatorInfoLogger.h"

#include <stdio.h>

#ifdef _WIN32

# define CDECL __cdecl

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
namespace Media {

class SupplierFile : public Thread, public ISupplier
{
public:
    SupplierFile();
    ~SupplierFile();
    TBool LoadFile(const Brx& aFileName);
    void Block();
    void Unblock();
private: // from Thread
    void Run();
private:
    MsgAudioEncoded* CreateAudio();
private: // from ISupplier
    void Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement);
    void Play();
    void Flush(Msg* aMsg);
    void Quit(Msg* aMsg);
private:
    Mutex iLock;
    Semaphore iBlocker;
    MsgFactory* iMsgFactory;
    IPipelineElementDownstream* iPipeline;
    Msg* iPendingMsg;
    TBool iBlock;
    TBool iQuit;
    FILE* iFh;
    TByte iBuf[DecodedAudio::kMaxBytes];
    TUint iDataSize;
    TUint iBytesRemaining;
};

class FileSender : private IPipelineObserver
{
    static const TUint kMaxDriverJiffies = Jiffies::kJiffiesPerMs * 5;
public:
    FileSender(Environment& aEnv, Net::DvStack& aDvStack, const Brx& aFileName, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel);
    virtual ~FileSender();
    int Run();
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack();
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
private:
    SupplierFile* iSupplier;
    AllocatorInfoLogger iInfoAggregator;
    PipelineManager* iPipeline;
    Net::DvDeviceStandard* iDevice;
    DriverSongcastSender* iDriver;
    Brh iFileName;
};

} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// SupplierFile

SupplierFile::SupplierFile()
    : Thread("SFIL")
    , iLock("SFIL")
    , iBlocker("SFIL", 0)
    , iMsgFactory(NULL)
    , iPipeline(NULL)
    , iPendingMsg(NULL)
    , iBlock(true)
    , iQuit(false)
{
}

SupplierFile::~SupplierFile()
{
    Join();
    (void)fclose(iFh);
}

TBool SupplierFile::LoadFile(const Brx& aFileName)
{
    Brhz file(aFileName);
    if (file.Bytes() == 0) {
        Log::Print("ERROR: No file specified\n");
        return false;
    }
    iFh = fopen(file.CString(), "rb");
    if (iFh == NULL) {
        Log::Print("ERROR: Unable to open specified file\n");
        return false;
    }

    if (fseek(iFh, 0L, SEEK_END) == -1) {
        Log::Print("ERROR: Unable to seek to end of file\n");
        return false;
    }
    iDataSize = ftell(iFh);
    if (fseek(iFh, 0L, SEEK_SET) == -1) {
        Log::Print("ERROR: Unable to seek back to start of file\n");
        return false;
    }
    iBytesRemaining = iDataSize;

    return true;
}

void SupplierFile::Block()
{
    iBlock = true;
    (void)iBlocker.Clear();
}

void SupplierFile::Unblock()
{
    iBlocker.Signal();
    iBlock = false;
}

void SupplierFile::Run()
{
    Msg* msg = iMsgFactory->CreateMsgTrack();
    iPipeline->Push(msg);
    while (!iQuit) {
        if (iBlock) {
            iBlocker.Wait();
        }
        iLock.Wait();
        if (iPendingMsg != NULL) {
            msg = iPendingMsg;
            iPendingMsg = NULL;
            iBlock = !iQuit; // nasty way of blocking after delivering a Flush
        }
        else if (iBytesRemaining > 0) {
            msg = CreateAudio();
        }
        else {
            Log::Print("Reached end of track, pipeline will shut down\n");
            msg = iMsgFactory->CreateMsgHalt();
            iBlock = true; // wait for a quit command now
        }
        iLock.Signal();
        iPipeline->Push(msg);
        Thread::Sleep(2); // small delay to avoid this thread hogging all cpu on platforms without priorities
    }
    if (iPendingMsg != NULL) {
        iPipeline->Push(iPendingMsg);
        iPendingMsg = NULL;
    }
}

MsgAudioEncoded* SupplierFile::CreateAudio()
{
    TUint bytes = EncodedAudio::kMaxBytes;
    if (iBytesRemaining < bytes) {
        bytes = iBytesRemaining;
    }
    if (fread(iBuf, 1, bytes, iFh) != bytes) {
        Log::Print("ERROR: Unable to read file data\n");
        ASSERTS();
    }
    iBytesRemaining -= bytes;
    Brn encodedAudioBuf(iBuf, bytes);
    return iMsgFactory->CreateMsgAudioEncoded(encodedAudioBuf);
}

void SupplierFile::Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement)
{
    iMsgFactory = &aMsgFactory;
    iPipeline = &aDownstreamElement;
}

void SupplierFile::Play()
{
    Unblock();
}

void SupplierFile::Flush(Msg* aMsg)
{
    iLock.Wait();
    iPendingMsg = aMsg;
    ASSERT(0 == fseek(iFh, 0, SEEK_SET));
    iBytesRemaining = iDataSize;
    iLock.Signal();
}

void SupplierFile::Quit(Msg* aMsg)
{
    iLock.Wait();
    iPendingMsg = aMsg;
    iQuit = true;
    if (iBlock) {
        Unblock();
    }
    iLock.Signal();
}


// FileSender

FileSender::FileSender(Environment& aEnv, Net::DvStack& aDvStack, const Brx& aFileName, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel)
    : iFileName(aFileName)
{
    iSupplier = new SupplierFile();
    iPipeline = new PipelineManager(iInfoAggregator, *iSupplier, *this, kMaxDriverJiffies);
    iPipeline->AddCodec(new Codec::CodecFlac());
    iPipeline->AddCodec(new Codec::CodecWav());

    iDevice = new DvDeviceStandard(aDvStack, aSenderUdn);
    iDevice->SetAttribute("Upnp.Domain", "av.openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Sender");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", aSenderFriendlyName);
    iDevice->SetAttribute("Upnp.Manufacturer", "Openhome");
    iDevice->SetAttribute("Upnp.ManufacturerUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.ModelDescription", "ohMediaPlayer FileSender");
    iDevice->SetAttribute("Upnp.ModelName", "ohMediaPlayer FileSender");
    iDevice->SetAttribute("Upnp.ModelNumber", "1");
    iDevice->SetAttribute("Upnp.ModelUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.SerialNumber", "");
    iDevice->SetAttribute("Upnp.Upc", "");

    iDriver = new DriverSongcastSender(iPipeline->FinalElement(), kMaxDriverJiffies, aEnv, *iDevice, aSenderUdn, aSenderChannel, aAdapter);
    iDevice->SetEnabled();
}

FileSender::~FileSender()
{
    delete iPipeline;
    delete iSupplier;
    delete iDriver;
    delete iDevice;
}

int FileSender::Run()
{
    if (!iSupplier->LoadFile(iFileName)) {
        return 1;
    }
    iSupplier->Start();

    TBool playing = false;
    TBool starve = false;
    TBool quit = false;

    Log::Print("\nFileSender pipeline test.  Usage:\n");
    Log::Print("p: Toggle between play/pause\n");
    Log::Print("n: Toggle between start/stop simulating network starvation\n");
    Log::Print("s: Stop (only valid when paused)\n");
    Log::Print("q: Quit\n");
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
        case 'n':
            starve = !starve;
            if (starve) {
                iSupplier->Block();
            }
            else {
                iSupplier->Unblock();
            }
            break;
        case 's':
            if (!playing) {
                iPipeline->Stop();
            }
            break;
        case 'q':
            quit = true;
            break;
        default:
            break;
        }
    } while (!quit);

    return 0;
}

#define LOG_PIPELINE_OBSERVER
#ifdef _WIN32
// suppress 'unreferenced formal parameter' warnings which come and go depending
// on the state of LOG_PIPELINE_OBSERVER
# pragma warning(disable:4100)
#endif
void FileSender::NotifyPipelineState(EPipelineState aState)
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

void FileSender::NotifyTrack()
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: TRACK\n");
#endif
}

void FileSender::NotifyMetaText(const Brx& aText)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: METATEXT {");
    Log::Print(aText);
    Log::Print("}\n");
#endif
}

void FileSender::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: TIME {secs=%u; duration=%u}\n", aSeconds, aTrackDurationSeconds);
#endif
}

void FileSender::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
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
    OptionString optionFile("-f", "--file", Brn(""), "[file] flac/wav file to play");
    parser.AddOption(&optionFile);
    OptionString optionUdn("-u", "--udn", Brn("PipelineFileSender"), "[udn] udn for the upnp device");
    parser.AddOption(&optionUdn);
    OptionString optionName("-n", "--name", Brn("Pipeline FileSender"), "[name] name of the sender");
    parser.AddOption(&optionName);
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
    TIpAddress adapter = (*subnetList)[adapterIndex]->Address();
    Library::DestroySubnetList(subnetList);
    lib->SetCurrentSubnet(subnet);
    Log::Print("using subnet %d.%d.%d.%d\n", subnet&0xff, (subnet>>8)&0xff, (subnet>>16)&0xff, (subnet>>24)&0xff);

    FileSender* fileSender = new FileSender(lib->Env(), *dvStack, optionFile.Value(), adapter, optionUdn.Value(), optionName.CString(), optionChannel.Value());
    const int ret = fileSender->Run();
    delete fileSender;
    
    delete lib;

    return ret;
}
