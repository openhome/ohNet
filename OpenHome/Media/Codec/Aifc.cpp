#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Av/Debug.h>

#include <string.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecAifc : public CodecBase
{
public:
     CodecAifc();
    ~ CodecAifc();
private: // from CodecBase
    TBool SupportsMimeType(const Brx& aMimeType);
    TBool Recognise(const Brx& aData);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
private:
    TUint FindChunk(const Brx& aChunkId);
    TUint DetermineRate(TUint16 aExponent, TUint32 aMantissa);
    void ProcessHeader();
    void SendMsgDecodedStream(TUint64 aStartSample);
private:
    Bws<DecodedAudio::kMaxBytes> iReadBuf;
    TUint iNumChannels;
    TUint64 iSamplesTotal;
    TUint iBitDepth;
    TUint iSampleRate;
    TUint iBitRate;
    TUint iAudioBytesTotal;
    TUint iAudioBytesRemaining;
    TUint64 iTrackStart;
    TUint64 iTrackOffset;
    TUint64 iTrackLengthJiffies;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewAifc()
{ // static
    return new CodecAifc();
}



CodecAifc::CodecAifc()
{
}

CodecAifc::~CodecAifc()
{
}

TBool CodecAifc::SupportsMimeType(const Brx& aMimeType)
{
    static const Brn kMimeAifc("audio/aiff");
    static const Brn kMimeXAifc("audio/x-aiff");
    if (aMimeType == kMimeAifc || aMimeType == kMimeXAifc) {
        return true;
    }
    return false;
}

TBool CodecAifc::Recognise(const Brx& aData)
{
    const TChar* ptr = reinterpret_cast<const TChar*>(aData.Ptr());
    if(strncmp(ptr, "FORM", 4) == 0) {
        if(strncmp(ptr+8, "AIFC", 4) == 0) {
            return true;
        }
    }
    return false;
}

void CodecAifc::StreamInitialise()
{
    iNumChannels = 0;
    iSamplesTotal = 0;
    iBitDepth = 0;
    iSampleRate = 0;
    iBitRate = 0;
    iAudioBytesTotal = 0;
    iAudioBytesRemaining = 0;
    iTrackStart = 0;
    iTrackOffset = 0;
    iTrackLengthJiffies = 0;
    iReadBuf.SetBytes(0);

    ProcessHeader();
    SendMsgDecodedStream(0);
}

void CodecAifc::Process()
{
    LOG(kMedia, "> CodecAifc::Process()\n");

    if (iAudioBytesRemaining == 0) {
        THROW(CodecStreamEnded);
    }
    TUint chunkSize = DecodedAudio::kMaxBytes - (DecodedAudio::kMaxBytes % (iNumChannels * (iBitDepth/8)));
    ASSERT_DEBUG(chunkSize <= iReadBuf.MaxBytes());
    iReadBuf.SetBytes(0);
    const TUint bytes = (chunkSize < iAudioBytesRemaining? chunkSize : iAudioBytesRemaining);
    iController->Read(iReadBuf, bytes);
    Brn encodedAudioBuf(iReadBuf.Ptr(), bytes);
    iTrackOffset += iController->OutputAudioPcm(encodedAudioBuf, iNumChannels, iSampleRate, iBitDepth, EMediaDataLittleEndian, iTrackOffset);
    iAudioBytesRemaining -= bytes;

    LOG(kMedia, "< CodecAifc::Process()\n");
}

TBool CodecAifc::TrySeek(TUint aStreamId, TUint64 aSample)
{
    const TUint byteDepth = iBitDepth/8;
    const TUint64 bytePos = aSample * iNumChannels * byteDepth;
    if (!iController->TrySeek(aStreamId, iTrackStart + bytePos)) {
        return false;
    }
    iTrackOffset = ((TUint64)aSample * Jiffies::kJiffiesPerSecond) / iSampleRate;
    iAudioBytesRemaining = iAudioBytesTotal - (TUint)(aSample * iNumChannels * byteDepth);
    SendMsgDecodedStream(aSample);
    return true;
}

TUint CodecAifc::FindChunk(const Brx& aChunkId)
{
    LOG(kMedia, "CodecAifc::FindChunk: ");
    LOG(kMedia, aChunkId);
    LOG(kMedia, "\n");

    for (;;) {
        iReadBuf.SetBytes(0);
        iController->Read(iReadBuf, 8); //Read chunk id and chunk size
        TUint bytes = Converter::BeUint32At(iReadBuf, 4);
        bytes += (bytes % 2); // aiff pads by one byte if chunk size is odd

        if (Brn(iReadBuf.Ptr(), 4) == aChunkId) {
            return bytes;
        }
        else {
            iReadBuf.SetBytes(0);
            if (iReadBuf.MaxBytes() < bytes) {
                // FIXME - this could be the case if, e.g., COMM comes after SSND
                // don't want to exhaust MsgAudioEncodeds by trying to skip over
                // an extremely large amount of data
                // FIXME - CodecStreamFeatureUnsupported appears to be unhandled
                THROW(CodecStreamFeatureUnsupported);
            }
            iController->Read(iReadBuf, bytes);
        }
    }
}

TUint CodecAifc::DetermineRate(TUint16 aExponent, TUint32 aMantissa)
{
    /*
     * Uses normalised 80 bit IEEE 754 floating point representation. This
     * offsets the exponent by 16382, so find true exponent by subtracting 16382.
     * To keep within 32 bit integer result divide down by 65536,
     * i.e. offset exponent and shift right
     * exp = exp - 16382
     * exp = 32 - exp
     * srate = mant >> exp
     */
    aExponent -= 16382;
    TUint srate = aMantissa >> aExponent;

    return srate;
}

void CodecAifc::ProcessHeader()
{
    LOG(kMedia, "CodecAifc::ProcessHeader()\n");

    // format of AIFC header taken from http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/AIFF/Docs/AIFF-C.9.26.91.pdf

    TUint audioOffset = 0;

    //Should be FORM,<FileBytes>,AIFC,<audio data>
    iController->Read(iReadBuf, 12); //Read the first 12 bytes of the IFF file, the FORM header
    const TByte* header = iReadBuf.Ptr();

    //We shouldn't be in the aifc codec unless this says 'AIFC'
    //This isn't a track corrupt issue as it was previously checked by Recognise
    ASSERT(strncmp((const TChar*)header, "FORM", 4) == 0);

    // Get the file size (FIXME - disabled for now since we're not considering continuous streams yet)
    //here the given size includes four bytes for the file type (AIFC)
    //TUint bytesTotal = Converter::BeUint32At(iReadBuf, 4) + 8;

    //We shouldn't be in the aifc codec unless this says 'AIFC'
    //This isn't a track corrupt issue as it was previously checked by Recognise
    ASSERT(strncmp((const TChar*)header+8, "AIFC", 4) == 0);

    audioOffset += 12;

    // Find the FVER chunk - should check it exists, but contains no useful data
    TUint fverChunkBytes = FindChunk(Brn("FVER"));
    if (fverChunkBytes != 4) {
        THROW(CodecStreamCorrupt);
    }
    // read remainder of chunk
    iReadBuf.SetBytes(0);
    iController->Read(iReadBuf, fverChunkBytes);

    audioOffset += fverChunkBytes + 8;

    // Find the COMMON chunk
    TUint commChunkBytes = FindChunk(Brn("COMM"));
    if (commChunkBytes < 22) {
        THROW(CodecStreamCorrupt);
    }

    iReadBuf.SetBytes(0);
    iController->Read(iReadBuf, commChunkBytes);
    iNumChannels = Converter::BeUint16At(iReadBuf, 0);
    iSamplesTotal = Converter::BeUint32At(iReadBuf, 2);
    iBitDepth = Converter::BeUint16At(iReadBuf, 6);

    //the sample rate is expressed as a 80-bit floating point number
    iSampleRate = DetermineRate(Converter::BeUint16At(iReadBuf, 8), Converter::BeUint32At(iReadBuf, 10));

    switch(iBitDepth) {
        case 8:
        case 16:
        case 24:
            break;
        case 20:
            iBitDepth = 24;
            break;
        default:
            THROW(CodecStreamFeatureUnsupported);
    }

    TUint bytesPerSample = iNumChannels * (iBitDepth/8);
    TUint bytesPerSec = iSampleRate * bytesPerSample;
    iBitRate = bytesPerSec * 8;

    const TByte* commData = iReadBuf.Ptr();
    //Apple's proprietary aifc compression format where the 'compression' is Little endian
    if ((strncmp((const TChar*)commData+18, "sowt", 4) != 0)
        && (strncmp((const TChar*)commData+18, "SOWT", 4) != 0)) {
        THROW(CodecStreamFeatureUnsupported);
    }

    audioOffset += commChunkBytes + 8;

    // Find the sound chunk
    TUint ssndChunkBytes = FindChunk(Brn("SSND"));

    // There are 8 bytes included for offset and blocksize in this number
    iAudioBytesTotal = ssndChunkBytes - 8;
    iAudioBytesRemaining = iAudioBytesTotal;

    iController->Read(iReadBuf, 8); // read in offset and blocksize

    audioOffset += 16;
    iTrackStart = audioOffset;

    if (iAudioBytesTotal % (iNumChannels * (iBitDepth/8)) != 0) {
        // There aren't an exact number of samples in the file => file is corrupt
        THROW(CodecStreamCorrupt);
    }

    const TUint numSamples = iAudioBytesTotal / (iNumChannels * (iBitDepth/8));
    if (numSamples != iSamplesTotal) {
        THROW(CodecStreamCorrupt);
    }
    iTrackLengthJiffies = ((TUint64)numSamples * Jiffies::kJiffiesPerSecond) / iSampleRate;
}

void CodecAifc::SendMsgDecodedStream(TUint64 aStartSample)
{
    iController->OutputDecodedStream(iBitRate, iBitDepth, iSampleRate, iNumChannels, Brn("AIFF"), iTrackLengthJiffies, aStartSample, true);
}
