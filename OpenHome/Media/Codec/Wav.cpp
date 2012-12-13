#include <OpenHome/Media/Codec/Wav.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecWav::CodecWav()
{
}

TBool CodecWav::Recognise(const Brx& aData)
{
    const TChar* ptr = reinterpret_cast<const TChar*>(aData.Ptr());
    if(strncmp(ptr, "RIFF", 4) == 0) {
        if(strncmp(ptr+8, "WAVE", 4) == 0) {
            return true;
        }
    }
    return false;
}

void CodecWav::Process()
{
    LOG(kMedia, "> CodecWav::Process()\n");

    iController->Read(iReadBuf, 44);
    TUint numChannels, sampleRate, bitDepth, audioBytes;
    ProcessHeader(iReadBuf, numChannels, sampleRate, bitDepth, audioBytes);
    TUint64 trackOffset = 0;
    TUint chunkSize = DecodedAudio::kMaxBytes - (DecodedAudio::kMaxBytes % (numChannels * (bitDepth/8)));
    if (chunkSize > sizeof(iReadBuf)) {
        chunkSize = sizeof(iReadBuf);
    }
    while (audioBytes > 0) {
        const TUint bytes = (chunkSize < audioBytes? chunkSize : audioBytes);
        iController->Read(iReadBuf, bytes);
        Brn encodedAudioBuf(iReadBuf.Ptr(), bytes);
        MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, numChannels, sampleRate, bitDepth, EMediaDataLittleEndian, trackOffset);
        trackOffset += audio->Jiffies();
        audioBytes -= bytes;
        iController->Output(audio);
    }

    LOG(kMedia, "< CodecWav::Process()\n"); // FIXME - will we ever reach here (need to decide whether to return from Process() or throw)
}

void CodecWav::ProcessHeader(const Brx& aHeader, TUint& aNumChannels, TUint& aSampleRate, TUint& aBitDepth, TUint& aAudioBytes)
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
    aNumChannels = header[22] | (header[23] << 8);
    aSampleRate = header[24] | (header[25] << 8) | (header[26] << 16) | (header[27] << 24);
    const TUint byteRate = header[28] | (header[29] << 8) | (header[30] << 16) | (header[31] << 24);
    //const TUint blockAlign = header[32] | (header[33] << 8);
    aBitDepth = header[34] | (header[35] << 8);
    if (strncmp((const TChar*)header+36, "data", 4) != 0) {
        THROW(CodecStreamFeatureUnsupported);
    }
    aAudioBytes = header[40] | (header[41] << 8) | (header[42] << 16) | (header[43] << 24);

    const TUint bitRate = byteRate * 8;
    if (aAudioBytes % (aNumChannels * (aBitDepth/8)) != 0) {
        // There aren't an exact number of samples in the file => file is corrupt
        THROW(CodecStreamCorrupt);
    }
    const TUint numSamples = aAudioBytes / (aNumChannels * (aBitDepth/8));
    const TUint64 trackLengthJiffies = ((TUint64)numSamples * Jiffies::kJiffiesPerSecond) / aSampleRate;

    MsgAudioFormat* msg = iMsgFactory->CreateMsgAudioFormat(bitRate, aBitDepth, aSampleRate, aNumChannels, Brn("WAV"), trackLengthJiffies, true);
    iController->Output(msg);
}
