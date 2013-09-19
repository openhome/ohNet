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

class CodecAiff : public CodecAiffBase
{
public:
     CodecAiff();
     ~CodecAiff();
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

CodecBase* CodecFactory::NewAiff()
{ // static
    return new CodecAiff();
}



CodecAiff::CodecAiff()
    : CodecAiffBase(EMediaDataBigEndian)
{
}

CodecAiff::~CodecAiff()
{
}

TBool CodecAiff::Recognise(const Brx& aData)
{
    const TChar* ptr = reinterpret_cast<const TChar*>(aData.Ptr());
    if(strncmp(ptr, "FORM", 4) == 0) {
        if(strncmp(ptr+8, "AIFF", 4) == 0) {
            return true;
        }
    }
    return false;
}

void CodecAiff::ProcessHeader()
{
    LOG(kMedia, "CodecAiff::ProcessHeader()\n");

    // format of AIFF header taken from http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/AIFF/Docs/AIFF-1.3.pdf

    TUint audioOffset = 0;

    //Should be FORM,<FileBytes>,AIFF,<audio data>
    iController->Read(iReadBuf, 12); //Read the first 12 bytes of the IFF file, the FORM header
    const TByte* header = iReadBuf.Ptr();

    //We shouldn't be in the aiff codec unless this says 'AIFF'
    //This isn't a track corrupt issue as it was previously checked by Recognise
    ASSERT(strncmp((const TChar*)header, "FORM", 4) == 0);

    // Get the file size (FIXME - disabled for now since we're not considering continuous streams yet)
    //here the given size includes four bytes for the file type (AIFF)
    //TUint bytesTotal = Converter::BeUint32At(iReadBuf, 4) + 8;

    //We shouldn't be in the aiff codec unless this says 'AIFF'
    //This isn't a track corrupt issue as it was previously checked by Recognise
    ASSERT(strncmp((const TChar*)header+8, "AIFF", 4) == 0);

    audioOffset += 12;

    // Find the COMMON chunk
    TUint commChunkBytes = FindChunk(Brn("COMM"));
    if (commChunkBytes != 18) {
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
