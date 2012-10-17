#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/DriverSongcastSender.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Debug.h>

#include <stdio.h>

#ifdef _WIN32

# define CDECL __cdecl

# include <conio.h>

int mygetch()
{
    return (_getch());
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

class InfoAggregator : public Av::IInfoAggregator, private IWriter
{
public:
    InfoAggregator();
    void PrintStats();
private: // from IInfoAggregator
    void Register(Av::IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries);
private: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
private:
    std::vector<Av::IInfoProvider*> iInfoProviders;
};

class SupplierWav : public Thread, public ISupplier
{
    static const size_t kFileHeaderBytes = 44;
    static const TUint kBitDepth    = 16;
    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
public:
    SupplierWav();
    ~SupplierWav();
    TBool LoadFile(const Brx& aFileName);
    void Block();
    void Unblock();
private: // from Thread
    void Run();
private:
    MsgAudio* CreateAudio();
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
    TUint iNumChannels;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint64 iTrackOffset;
};

class WavSender : private IPipelineObserver
{
    static const TUint kMaxDriverJiffies = Jiffies::kJiffiesPerMs * 5;
public:
    WavSender(const Brx& aWavFile, TUint aAdapterIndex, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel);
    ~WavSender();
    int Run();
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack();
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyAudioFormat(const AudioFormat& aFormat);
private:
    SupplierWav* iSupplier;
    InfoAggregator iInfoAggregator;
    PipelineManager* iPipeline;
    Net::DvDeviceStandard* iDevice;
    DriverSongcastSender* iDriver;
    Brh iWavFileName;
};

} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// InfoAggregator

InfoAggregator::InfoAggregator()
{
}

void InfoAggregator::PrintStats()
{
    for (size_t i=0; i<iInfoProviders.size(); i++) {
        iInfoProviders[i]->QueryInfo(AllocatorBase::kQueryMemory, *this);
    }
}

void InfoAggregator::Register(Av::IInfoProvider& aProvider, std::vector<Brn>& /*aSupportedQueries*/)
{
    iInfoProviders.push_back(&aProvider);
}

void InfoAggregator::Write(TByte aValue)
{
    Log::Print("%c", aValue);
}

void InfoAggregator::Write(const Brx& aBuffer)
{
    Log::Print(aBuffer);
}

void InfoAggregator::WriteFlush()
{
}


// SupplierWav

SupplierWav::SupplierWav()
    : Thread("SWAV")
    , iLock("SWAV")
    , iBlocker("SWAV", 0)
    , iMsgFactory(NULL)
    , iPipeline(NULL)
    , iPendingMsg(NULL)
    , iBlock(true)
    , iQuit(false)
    , iTrackOffset(0)
{
}

SupplierWav::~SupplierWav()
{
    Join();
    (void)fclose(iFh);
}

TBool SupplierWav::LoadFile(const Brx& aFileName)
{
	Brhz file(aFileName);
    if (file.Bytes() == 0) {
    	printf("ERROR: No wav file specified\n");
    	return false;
    }
    iFh = fopen(file.CString(), "rb");
    if (iFh == NULL) {
    	printf("ERROR: Unable to open specified wav file\n");
    	return false;
    }
    TByte header[kFileHeaderBytes];
    if (fread(header, 1, kFileHeaderBytes, iFh) != kFileHeaderBytes) {
    	printf("ERROR: Failed to read wav file header\n");
    	return false;
    }
    if (header[0] != 'R' || header[1] != 'I' || header[2] != 'F' || header[3] != 'F') {
    	printf("ERROR: Invalid wav file\n");
    	return false;
    }
    // skip reading next 4 bytes (chunk size)
    if (header[8] != 'W' || header[9] != 'A' || header[10] != 'V' || header[11] != 'E') {
    	printf("ERROR: Invalid wav file\n");
    	return false;
    }
    if (header[12] != 'f' || header[13] != 'm' || header[14] != 't' || header[15] != ' ') {
    	printf("ERROR: Invalid wav file\n");
    	return false;
    }
    const TUint subChunk1Size = header[16] | (header[17] << 8) | (header[18] << 16) | (header[19] << 24);
    if (subChunk1Size != 16) {
    	printf("ERROR: Unsupported wav file\n");
    	return false;
    }
    const TUint audioFormat = header[20] | (header[21] << 8);
    if (audioFormat != 1) {
    	printf("ERROR: Unsupported wav file\n");
    	return false;
    }
    iNumChannels = header[22] | (header[23] << 8);
    iSampleRate = header[24] | (header[25] << 8) | (header[26] << 16) | (header[27] << 24);
    //const TUint byteRate = header[28] | (header[29] << 8) | (header[30] << 16) | (header[31] << 24);
    //const TUint blockAlign = header[32] | (header[33] << 8);
    iBitDepth = header[34] | (header[35] << 8);
    if (header[36] != 'd' || header[37] != 'a' || header[38] != 't' || header[39] != 'a') {
    	printf("ERROR: Invalid wav file\n");
    	return false;
    }
    iDataSize = header[40] | (header[41] << 8) | (header[42] << 16) | (header[43] << 24);
    iBytesRemaining = iDataSize;
    
//    printf("numChannels=%u, sampleRate=%u, byteRate=%u, blockAlign=%u, bitsDepth=%u, subChunk2Size=%u\n",
//           iNumChannels, iSampleRate, byteRate, blockAlign, iBitDepth, iDataBytes);

    return true;
}

void SupplierWav::Block()
{
    iBlock = true;
    (void)iBlocker.Clear();
}

void SupplierWav::Unblock()
{
    iBlocker.Signal();
    iBlock = false;
}

void SupplierWav::Run()
{
    Msg* msg = iMsgFactory->CreateMsgTrack();
    iPipeline->Push(msg);
    const TUint bitRate = iSampleRate * iBitDepth * iNumChannels;
    ASSERT(iDataSize % (iNumChannels * (iBitDepth/8)) == 0);
    const TUint numSamples = iDataSize / (iNumChannels * (iBitDepth/8));
    const TUint64 trackLengthJiffies = ((TUint64)numSamples * Jiffies::kJiffiesPerSecond) / iSampleRate;
    msg = iMsgFactory->CreateMsgAudioFormat(bitRate, iBitDepth, iSampleRate, iNumChannels, Brn("WAV"), trackLengthJiffies, true);
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
            printf("Reached end of track, pipeline will shut down\n");
            msg = iMsgFactory->CreateMsgHalt();
            iPendingMsg = iMsgFactory->CreateMsgQuit();
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

MsgAudio* SupplierWav::CreateAudio()
{
    TUint bytes = DecodedAudio::kMaxSubsamples * (iBitDepth / 8);
    if (iBytesRemaining < bytes) {
        bytes = iBytesRemaining;
    }
    if (fread(iBuf, 1, bytes, iFh) != bytes) {
    	printf("ERROR: Unable to read wav file data\n");
    	ASSERTS();
    }
    iBytesRemaining -= bytes;
    Brn encodedAudioBuf(iBuf, bytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, iNumChannels, iSampleRate, iBitDepth, EMediaDataLittleEndian, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

void SupplierWav::Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement)
{
    iMsgFactory = &aMsgFactory;
    iPipeline = &aDownstreamElement;
}

void SupplierWav::Play()
{
    Unblock();
}

void SupplierWav::Flush(Msg* aMsg)
{
    iLock.Wait();
    iPendingMsg = aMsg;
    ASSERT(0 == fseek(iFh, kFileHeaderBytes, SEEK_SET));
    iBytesRemaining = iDataSize;
    iLock.Signal();
}

void SupplierWav::Quit(Msg* aMsg)
{
    iLock.Wait();
    iPendingMsg = aMsg;
    iQuit = true;
    if (iBlock) {
        Unblock();
    }
    iLock.Signal();
}


// WavSender

WavSender::WavSender(const Brx& aWavFile, TUint aAdapterIndex, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel)
    : iWavFileName(aWavFile)
{
    iSupplier = new SupplierWav();
    iPipeline = new PipelineManager(iInfoAggregator, *iSupplier, *this, kMaxDriverJiffies);

    InitialisationParams* initParams = InitialisationParams::Create();
	UpnpLibrary::Initialise(initParams);
    UpnpLibrary::StartDv();
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    if (subnetList->size() <= aAdapterIndex) {
		printf("ERROR: adapter %d doesn't exist\n", aAdapterIndex);
		ASSERTS();
    }
    printf ("adapter list:\n");
    for (unsigned i=0; i<subnetList->size(); ++i) {
		TIpAddress addr = (*subnetList)[i]->Address();
		printf ("  %d: %d.%d.%d.%d\n", i, addr&0xff, (addr>>8)&0xff, (addr>>16)&0xff, (addr>>24)&0xff);
    }
    TIpAddress subnet = (*subnetList)[aAdapterIndex]->Subnet();
    TIpAddress adapter = (*subnetList)[aAdapterIndex]->Address();
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::SetCurrentSubnet(subnet);

    printf("using subnet %d.%d.%d.%d\n", subnet&0xff, (subnet>>8)&0xff, (subnet>>16)&0xff, (subnet>>24)&0xff);

    iDevice = new DvDeviceStandard(aSenderUdn);
    iDevice->SetAttribute("Upnp.Domain", "av.openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Sender");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", aSenderFriendlyName);
    iDevice->SetAttribute("Upnp.Manufacturer", "Openhome");
    iDevice->SetAttribute("Upnp.ManufacturerUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.ModelDescription", "ohMediaPlayer WavSender");
    iDevice->SetAttribute("Upnp.ModelName", "ohMediaPlayer WavSender");
    iDevice->SetAttribute("Upnp.ModelNumber", "1");
    iDevice->SetAttribute("Upnp.ModelUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.SerialNumber", "");
    iDevice->SetAttribute("Upnp.Upc", "");

    iDriver = new DriverSongcastSender(iPipeline->FinalElement(), kMaxDriverJiffies, *iDevice, aSenderUdn, aSenderChannel, adapter);
    iDevice->SetEnabled();
}

WavSender::~WavSender()
{
    delete iPipeline;
    delete iSupplier;
    delete iDriver;
    delete iDevice;
	UpnpLibrary::Close();
}

int WavSender::Run()
{
    if (!iSupplier->LoadFile(iWavFileName)) {
        return 1;
    }
    iSupplier->Start();

    TBool playing = false;
    TBool starve = false;
    TBool quit = false;

    printf("\nWavSender pipeline test.  Usage:\n");
    printf("p: Toggle between play/pause\n");
    printf("n: Toggle between start/stop simulating network starvation\n");
    printf("s: Stop (only valid when paused)\n");
    printf("q: Quit\n");
    printf("\n");
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
void WavSender::NotifyPipelineState(EPipelineState aState)
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

void WavSender::NotifyTrack()
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: TRACK\n");
#endif
}

void WavSender::NotifyMetaText(const Brx& aText)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: METATEXT {");
    Log::Print(aText);
    Log::Print("}\n");
#endif
}

void WavSender::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: TIME {secs=%u; duration=%u}\n", aSeconds, aTrackDurationSeconds);
#endif
}

void WavSender::NotifyAudioFormat(const AudioFormat& aFormat)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: FORMAT {bitRate=%u; bitDepth=%u, sampleRate=%u, numChannels=%u, codec=",
           aFormat.BitRate(), aFormat.BitDepth(), aFormat.SampleRate(), aFormat.NumChannels());
    Log::Print(aFormat.CodecName());
    Log::Print("; trackLength=%llx, lossless=%u}\n", aFormat.TrackLength(), aFormat.Lossless());
#endif
}




int CDECL main(int aArgc, char* aArgv[])
{
    OptionParser parser;
    OptionString optionFile("-f", "--file", Brn(""), "[file] wav file to play");
    parser.AddOption(&optionFile);
    OptionString optionUdn("-u", "--udn", Brn("PipelineWavSender"), "[udn] udn for the upnp device");
    parser.AddOption(&optionUdn);
    OptionString optionName("-n", "--name", Brn("Pipeline WavSender"), "[name] name of the sender");
    parser.AddOption(&optionName);
    OptionUint optionChannel("-c", "--channel", 0, "[0..65535] sender channel");
    parser.AddOption(&optionChannel);
    OptionUint optionAdapter("-a", "--adapter", 0, "[adapter] index of network adapter to use");
    parser.AddOption(&optionAdapter);

    if (!parser.Parse(aArgc, aArgv)) {
        return 1;
    }

    WavSender* wavSender = new WavSender(optionFile.Value(), optionAdapter.Value(), optionUdn.Value(), optionName.CString(), optionChannel.Value());
    const int ret = wavSender->Run();
    delete wavSender;

    return ret;
}
