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

#include "FileSender.h"

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

