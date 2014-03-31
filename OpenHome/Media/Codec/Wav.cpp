#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Av/Debug.h>

#include <string.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecWav : public CodecBase
{
public:
    CodecWav();
    ~CodecWav();
private: // from CodecBase
    TBool SupportsMimeType(const Brx& aMimeType);
    TBool Recognise();
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
private:
    void ProcessHeader(const Brx& aHeader);
    void SendMsgDecodedStream(TUint64 aStartSample);
private:
    static const TUint kHeaderBytes = 44;
    Bws<DecodedAudio::kMaxBytes> iReadBuf;
    TUint iNumChannels;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iAudioBytesTotal;
    TUint iAudioBytesRemaining;
    TUint iBitRate;
    TUint64 iTrackOffset;
    TUint64 iTrackLengthJiffies;

};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewWav()
{ // static
    return new CodecWav();
}



CodecWav::CodecWav()
{
}

CodecWav::~CodecWav()
{
}

TBool CodecWav::SupportsMimeType(const Brx& aMimeType)
{
    static const Brn kMimeWav("audio/wav");
    static const Brn kMimeWave("audio/wave");
    static const Brn kMimeXWav("audio/x-wav");
    if (aMimeType == kMimeWav || aMimeType == kMimeWave || aMimeType == kMimeXWav) {
        return true;
    }
    return false;
}

TBool CodecWav::Recognise()
{
    Bws<12> buf;
    iController->Read(buf, buf.MaxBytes());
    const TChar* ptr = reinterpret_cast<const TChar*>(buf.Ptr());
    if (buf.Bytes() == 12 && strncmp(ptr, "RIFF", 4) == 0 && strncmp(ptr+8, "WAVE", 4) == 0) {
        return true;
    }
#if 0 // debug helper
    Log::Print("CodecWav::Recognise() failed.  Was passed data \n  ");
    for (TUint i=0; i<buf.Bytes(); i++) {
        Log::Print(" %02x", buf[i]);
    }
    Log::Print("\n");
#endif
    return false;
}

void CodecWav::StreamInitialise()
{
    iNumChannels = 0;
    iSampleRate = 0;
    iBitDepth = 0;
    iAudioBytesTotal = 0;
    iAudioBytesRemaining = 0;
    iTrackOffset = 0;
    iReadBuf.SetBytes(0);
}

void CodecWav::Process()
{
    LOG(kMedia, "> CodecWav::Process()\n");

    if (iNumChannels == 0) {
        iController->Read(iReadBuf, kHeaderBytes);
        if (iReadBuf.Bytes() != kHeaderBytes) {
            THROW(CodecStreamEnded);
        }
        ProcessHeader(iReadBuf);
        SendMsgDecodedStream(0);
    }
    else {
        if (iAudioBytesRemaining == 0) {
            THROW(CodecStreamEnded);
        }
        TUint chunkSize = DecodedAudio::kMaxBytes - (DecodedAudio::kMaxBytes % (iNumChannels * (iBitDepth/8)));
        ASSERT_DEBUG(chunkSize <= iReadBuf.MaxBytes());
        iReadBuf.SetBytes(0);
        const TUint bytes = (chunkSize < iAudioBytesRemaining? chunkSize : iAudioBytesRemaining);
        iController->Read(iReadBuf, bytes);

        // Truncate to a sensible sample boundary.
        TUint remainder = iReadBuf.Bytes() % (iNumChannels * (iBitDepth/8));
        Brn split = iReadBuf.Split(iReadBuf.Bytes()-remainder);
        iReadBuf.SetBytes(iReadBuf.Bytes()-remainder);

        iTrackOffset += iController->OutputAudioPcm(iReadBuf, iNumChannels, iSampleRate, iBitDepth, EMediaDataLittleEndian, iTrackOffset);
        iAudioBytesRemaining -= iReadBuf.Bytes();

        if (remainder > 0) {
            iReadBuf.Replace(split);
        }
        if (iReadBuf.Bytes() < bytes) { // stream ended unexpectedly
            THROW(CodecStreamEnded);
        }
    }

    LOG(kMedia, "< CodecWav::Process()\n");
}

TBool CodecWav::TrySeek(TUint aStreamId, TUint64 aSample)
{
    const TUint byteDepth = iBitDepth/8;
    const TUint64 bytePos = aSample * iNumChannels * byteDepth;
    if (!iController->TrySeek(aStreamId, bytePos)) {
        return false;
    }
    iTrackOffset = ((TUint64)aSample * Jiffies::kJiffiesPerSecond) / iSampleRate;
    iAudioBytesRemaining = iAudioBytesTotal - (TUint)(aSample * iNumChannels * byteDepth);
    SendMsgDecodedStream(aSample);
    return true;
}

void CodecWav::ProcessHeader(const Brx& aHeader)
{
    LOG(kMedia, "Wav::ProcessHeader()\n");

    // format of WAV header taken from https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
    
    const TByte* header = aHeader.Ptr();
    //We shouldn't be in the wav codec unless this says 'RIFF'
    //This isn't a track corrupt issue as it was previously checked by Recognise
    ASSERT(strncmp((const TChar*)header, "RIFF", 4) == 0);

    // Get the file size (FIXME - disabled for now since we're not considering continuous streams yet)
    //TUint bytesTotal = (header[7]<<24) | (header[6]<<16) | (header[5]<<8) | header[4];

    //We shouldn't be in the wav codec unless this says 'WAVE'
    //This isn't a track corrupt issue as it was previously checked by Recognise
    ASSERT(strncmp((const TChar*)header+8, "WAVE", 4) == 0);

    // Find the fmt chunk
    if (strncmp((const TChar*)header+12, "fmt ", 4) != 0) {
        THROW(CodecStreamCorrupt);
    }

    const TUint subChunk1Size = header[16] | (header[17] << 8) | (header[18] << 16) | (header[19] << 24);
    if (subChunk1Size != 16) { // FIXME - volkano allows values of 18, 40 also
        THROW(CodecStreamFeatureUnsupported);
    }
    const TUint audioFormat = header[20] | (header[21] << 8);
    if (audioFormat != 1) {
        THROW(CodecStreamFeatureUnsupported);
    }
    iNumChannels = header[22] | (header[23] << 8);
    iSampleRate = header[24] | (header[25] << 8) | (header[26] << 16) | (header[27] << 24);
    const TUint byteRate = header[28] | (header[29] << 8) | (header[30] << 16) | (header[31] << 24);
    //const TUint blockAlign = header[32] | (header[33] << 8);
    iBitDepth = header[34] | (header[35] << 8);
    if (iNumChannels == 0 || iSampleRate == 0 || iBitDepth == 0 || iBitDepth % 8 != 0) {
        THROW(CodecStreamCorrupt);
    }
    if (strncmp((const TChar*)header+36, "data", 4) != 0) {
        THROW(CodecStreamFeatureUnsupported);
    }
    iAudioBytesTotal = header[40] | (header[41] << 8) | (header[42] << 16) | (header[43] << 24);
    iAudioBytesRemaining = iAudioBytesTotal;

    iBitRate = byteRate * 8;
    if (iAudioBytesTotal % (iNumChannels * (iBitDepth/8)) != 0) {
        // There aren't an exact number of samples in the file => file is corrupt
        THROW(CodecStreamCorrupt);
    }
    const TUint numSamples = iAudioBytesTotal / (iNumChannels * (iBitDepth/8));
    iTrackLengthJiffies = ((TUint64)numSamples * Jiffies::kJiffiesPerSecond) / iSampleRate;
}

void CodecWav::SendMsgDecodedStream(TUint64 aStartSample)
{
    iController->OutputDecodedStream(iBitRate, iBitDepth, iSampleRate, iNumChannels, Brn("WAV"), iTrackLengthJiffies, aStartSample, true);
}
