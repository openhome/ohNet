// Tests that input to and output from pipeline are identical
// ...in the absense of any user action which would cause ramping
//
// Relies on having many tens of MB RAM plus thread priorities available
// ...so probably only works on Windows

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Net/Core/OhNet.h>
#include "AllocatorInfoLogger.h"
#include <OpenHome/Media/ProcessorPcmUtils.h>

#include <stdio.h>

#ifdef _WIN32
# define CDECL __cdecl
#else
# define CDECL
#endif

namespace OpenHome {
namespace Media {

class SupplierWav : public Thread, public ISupplier
{
    static const size_t kFileHeaderBytes = 44;
public:
    SupplierWav();
    ~SupplierWav();
    Brn LoadFile(const Brx& aFileName);
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
    MsgFactory* iMsgFactory;
    IPipelineElementDownstream* iPipeline;
    TByte* iBuf;
    TUint iDataSize;
    TUint iDataPos;
    TUint iNumChannels;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint64 iTrackOffset;
};

class DriverAudioCheck : public Thread, private IMsgProcessor
{
public:
    DriverAudioCheck(IPipelineElementUpstream& aPipeline, const Brx& aExpectedAudio);
    ~DriverAudioCheck();
private: // from Thread
    void Run();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    IPipelineElementUpstream& iPipeline;
    Brn iExpectedAudio;
    TBool iQuit;
    TUint iPos;
};

} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// SupplierWav

SupplierWav::SupplierWav()
    : Thread("SWAV", kPriorityHighest)
    , iMsgFactory(NULL)
    , iPipeline(NULL)
    , iBuf(NULL)
    , iDataPos(0)
    , iTrackOffset(0)
{
}

SupplierWav::~SupplierWav()
{
    Join();
    delete[] iBuf;
}

Brn SupplierWav::LoadFile(const Brx& aFileName)
{
    Brn audioData;
	Brhz file(aFileName);
    if (file.Bytes() == 0) {
    	Log::Print("ERROR: No wav file specified\n");
    	return audioData;
    }
    FILE* fh = fopen(file.CString(), "rb");
    if (fh == NULL) {
    	Log::Print("ERROR: Unable to open specified wav file\n");
    	return audioData;
    }
    TByte header[kFileHeaderBytes];
    if (fread(header, 1, kFileHeaderBytes, fh) != kFileHeaderBytes) {
    	Log::Print("ERROR: Failed to read wav file header\n");
    	goto exit;
    }
    if (header[0] != 'R' || header[1] != 'I' || header[2] != 'F' || header[3] != 'F') {
    	Log::Print("ERROR: Invalid wav file\n");
    	goto exit;
    }
    // skip reading next 4 bytes (chunk size)
    if (header[8] != 'W' || header[9] != 'A' || header[10] != 'V' || header[11] != 'E') {
    	Log::Print("ERROR: Invalid wav file\n");
    	goto exit;
    }
    if (header[12] != 'f' || header[13] != 'm' || header[14] != 't' || header[15] != ' ') {
    	Log::Print("ERROR: Invalid wav file\n");
    	goto exit;
    }
    {
        // gcc doesn't like gotos jumping over declaration for below variables
        // ...so move them into their own scope
        const TUint subChunk1Size = header[16] | (header[17] << 8) | (header[18] << 16) | (header[19] << 24);
        if (subChunk1Size != 16) {
            Log::Print("ERROR: Unsupported wav file\n");
            goto exit;
        }
        const TUint audioFormat = header[20] | (header[21] << 8);
        if (audioFormat != 1) {
            Log::Print("ERROR: Unsupported wav file\n");
            goto exit;
        }
    }
    iNumChannels = header[22] | (header[23] << 8);
    iSampleRate = header[24] | (header[25] << 8) | (header[26] << 16) | (header[27] << 24);
    //const TUint byteRate = header[28] | (header[29] << 8) | (header[30] << 16) | (header[31] << 24);
    //const TUint blockAlign = header[32] | (header[33] << 8);
    iBitDepth = header[34] | (header[35] << 8);
    if (header[36] != 'd' || header[37] != 'a' || header[38] != 't' || header[39] != 'a') {
    	Log::Print("ERROR: Invalid wav file\n");
    	goto exit;
    }
    iDataSize = header[40] | (header[41] << 8) | (header[42] << 16) | (header[43] << 24);

//    Log::Print("numChannels=%u, sampleRate=%u, byteRate=%u, blockAlign=%u, bitsDepth=%u, subChunk2Size=%u\n",
//           iNumChannels, iSampleRate, byteRate, blockAlign, iBitDepth, iDataBytes);

    iBuf = new TByte[iDataSize];
    if (fread(iBuf, 1, iDataSize, fh) != iDataSize) {
    	Log::Print("ERROR: Unable to read wav file data\n");
    	goto exit;
    }
    audioData.Set(iBuf, iDataSize);

exit:
    fclose(fh);
    return audioData;
}

void SupplierWav::Run()
{
    Msg* msg = iMsgFactory->CreateMsgTrack();
    iPipeline->Push(msg);
    const TUint bitRate = iSampleRate * iBitDepth * iNumChannels;
    ASSERT(iDataSize % (iNumChannels * (iBitDepth/8)) == 0);
    const TUint numSamples = iDataSize / (iNumChannels * (iBitDepth/8));
    const TUint64 trackLengthJiffies = ((TUint64)numSamples * Jiffies::kJiffiesPerSecond) / iSampleRate;
    msg = iMsgFactory->CreateMsgDecodedStream(1, bitRate, iBitDepth, iSampleRate, iNumChannels, Brn("WAV"), trackLengthJiffies, 0, true, NULL);
    iPipeline->Push(msg);
    while (iDataPos < iDataSize) {
        msg = CreateAudio();
        iPipeline->Push(msg);
    }
    msg = iMsgFactory->CreateMsgQuit();
    iPipeline->Push(msg);
}

MsgAudio* SupplierWav::CreateAudio()
{
    TUint bytes = DecodedAudio::kMaxBytes / (iBitDepth/8);
    TUint remaining = iDataSize - iDataPos;
    if (remaining < bytes) {
        bytes = remaining;
    }
    Brn encodedAudioBuf(&iBuf[iDataPos], bytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, iNumChannels, iSampleRate, iBitDepth, EMediaDataLittleEndian, iTrackOffset);
    iDataPos += bytes;
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
    Start();
}

void SupplierWav::Flush(Msg* /*aMsg*/)
{
    ASSERTS();
}

void SupplierWav::Quit(Msg* /*aMsg*/)
{
    ASSERTS();
}


// DriverAudioCheck

DriverAudioCheck::DriverAudioCheck(IPipelineElementUpstream& aPipeline, const Brx& aExpectedAudio)
    : Thread("DRAC", kPriorityLowest)
    , iPipeline(aPipeline)
    , iExpectedAudio(aExpectedAudio)
    , iQuit(false)
    , iPos(0)
{
    Start();
}

DriverAudioCheck::~DriverAudioCheck()
{
    Join();
}

void DriverAudioCheck::Run()
{
    do {
        Msg* msg = iPipeline.Pull();
        (void)msg->Process(*this);
        Thread::Sleep(1); // nasty but don't seem able to rely on highest priority thread always being scheduled
    } while (!iQuit);
    Log::Print("Expected %u bytes, got %u\n", iExpectedAudio.Bytes(), iPos);
}

Msg* DriverAudioCheck::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverAudioCheck::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverAudioCheck::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverAudioCheck::ProcessMsg(MsgPlayable* aMsg)
{
    ProcessorPcmBufPacked pcmProcessor;
    aMsg->Read(pcmProcessor);
    Brn buf = pcmProcessor.Buf();
    for (TUint i=0; i<buf.Bytes(); i++) {
        if (buf[i] != iExpectedAudio[iPos]) {
            Log::Print("Content mismatch (expected %08x, got %08x) at byte %u\n", iExpectedAudio[iPos], buf[i], iPos);
        }
        iPos++;
    }
    aMsg->RemoveRef();
    return NULL;
}

Msg* DriverAudioCheck::ProcessMsg(MsgDecodedStream* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* DriverAudioCheck::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverAudioCheck::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverAudioCheck::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverAudioCheck::ProcessMsg(MsgHalt* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* DriverAudioCheck::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverAudioCheck::ProcessMsg(MsgQuit* aMsg)
{
    iQuit = true;
    aMsg->RemoveRef();
    return NULL;
}



int CDECL main(int aArgc, char* aArgv[])
{
    OptionParser parser;
    OptionString optionFile("-f", "--file", Brn("c:\\test.wav"), "[file] wav file to play");
    parser.AddOption(&optionFile);
    if (!parser.Parse(aArgc, aArgv)) {
        return 1;
    }

    InitialisationParams* initParams = InitialisationParams::Create();
    UpnpLibrary::Initialise(initParams);
    
    SupplierWav* supplier = new SupplierWav();
    Brn audioData = supplier->LoadFile(optionFile.Value());
    if (audioData.Bytes() == 0) {
        delete supplier;
        return 1;
    }
    AllocatorInfoLogger infoAggregator;
    //NullPipelineObserver observer;
    LoggingPipelineObserver observer;
    PipelineManager* pipeline = new PipelineManager(infoAggregator, *supplier, observer, Jiffies::kJiffiesPerMs * 5);
    DriverAudioCheck* driver = new DriverAudioCheck(pipeline->FinalElement(), audioData);
    pipeline->Play();

    delete driver; // blocks until MsgQuit is received (and all audio data processed)
    delete pipeline;
    delete supplier;

    UpnpLibrary::Close();

    return 0;
}
