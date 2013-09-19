#include <OpenHome/Media/Codec/AiffBase.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Av/Debug.h>

#include <string.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecAifc : public CodecAiffBase
{
public:
     CodecAifc();
    ~ CodecAifc();
private: // from CodecAiffBase
    TBool Recognise(const Brx& aData);
    void ProcessHeader();
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
    : CodecAiffBase(EMediaDataLittleEndian)
{
}

CodecAifc::~CodecAifc()
{
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
