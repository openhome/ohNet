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

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// SupplierFile

SupplierFile::SupplierFile(const Brx& aFileName)
    : Thread("SFIL")
    , iLock("SFIL")
    , iBlocker("SFIL", 0)
    , iMsgFactory(NULL)
    , iPipeline(NULL)
    , iPendingMsg(NULL)
    , iBlock(true)
    , iQuit(false)
    , iFile(NULL)
    , iBuf(EncodedAudio::kMaxBytes)
{
    Brhz file(aFileName);

    try {
        iFile = IFile::Open(file.CString(), eFileReadOnly);
    }
    catch ( FileOpenError ) {
        Kill();
        Start();
        Join();
        throw;
    }

    iDataSize = iFile->Bytes();
    iBytesRemaining = iDataSize;
}

SupplierFile::~SupplierFile()
{
    Join();
    delete iFile;
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
    CheckForKill();
    Msg* msg = iMsgFactory->CreateMsgTrack();
    iPipeline->Push(msg);
    msg = iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), iDataSize, 1, false, false, NULL);
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
            //iTerminal.Print("Reached end of track, pipeline will shut down\n");
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
    TUint bytes = iBuf.MaxBytes();
    if (iBytesRemaining < bytes) {
        bytes = iBytesRemaining;
    }

    iFile->Read(iBuf, bytes);
    
    if (iBuf.Bytes() != bytes) {
        //iTerminal.Print("ERROR: Unable to read file data\n");
        ASSERTS();
    }
    iBytesRemaining -= bytes;
    return iMsgFactory->CreateMsgAudioEncoded(iBuf);
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
    iFile->Seek(0, eSeekFromStart);
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

FileSender::FileSender(Environment& aEnv, Terminal& aTerminal, Net::DvStack& aDvStack, const Brx& aFileName, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel, TBool aMulticast)
    : iTerminal(aTerminal)
    , iFileName(aFileName)
{
    iSupplier = new SupplierFile(aFileName);
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

    iDriver = new DriverSongcastSender(iPipeline->FinalElement(), kMaxDriverJiffies, aEnv, *iDevice, aSenderUdn, aSenderChannel, aAdapter, aMulticast);
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
    iSupplier->Start();

    TBool playing = false;
    TBool starve = false;
    TBool quit = false;

    iTerminal.Print("\nFileSender pipeline test.  Usage:\n");
    iTerminal.Print("p: Toggle between play/pause\n");
    iTerminal.Print("n: Toggle between start/stop simulating network starvation\n");
    iTerminal.Print("s: Stop (only valid when paused)\n");
    iTerminal.Print("q: Quit\n");
    iTerminal.Print("\n");
    do {
        TChar key = iTerminal.GetChar();
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
    iTerminal.Print("Pipeline state change: %s\n", state);
#endif
}

void FileSender::NotifyTrack()
{
#ifdef LOG_PIPELINE_OBSERVER
    iTerminal.Print("Pipeline report property: TRACK\n");
#endif
}

void FileSender::NotifyMetaText(const Brx& aText)
{
#ifdef LOG_PIPELINE_OBSERVER
    iTerminal.Print("Pipeline report property: METATEXT {");
    iTerminal.Print(aText);
    iTerminal.Print("}\n");
#endif
}

void FileSender::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
#ifdef LOG_PIPELINE_OBSERVER
    iTerminal.Print("Pipeline report property: TIME {secs=%u; duration=%u}\n", aSeconds, aTrackDurationSeconds);
#endif
}

void FileSender::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
#ifdef LOG_PIPELINE_OBSERVER
    iTerminal.Print("Pipeline report property: FORMAT {bitRate=%u; bitDepth=%u, sampleRate=%u, numChannels=%u, codec=",
           aStreamInfo.BitRate(), aStreamInfo.BitDepth(), aStreamInfo.SampleRate(), aStreamInfo.NumChannels());
    iTerminal.Print(aStreamInfo.CodecName());
    iTerminal.Print("; trackLength=%llx, lossless=%u}\n", aStreamInfo.TrackLength(), aStreamInfo.Lossless());
#endif
}

