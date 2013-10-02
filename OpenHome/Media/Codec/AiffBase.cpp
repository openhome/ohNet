#include <OpenHome/Media/Codec/AiffBase.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Av/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;


CodecAiffBase::CodecAiffBase(const Brx& aName, EMediaDataEndian aEndian)
    : iName(aName)
    , iEndian(aEndian)
{
}

CodecAiffBase::~CodecAiffBase()
{
}

TBool CodecAiffBase::SupportsMimeType(const Brx& aMimeType)
{
    static const Brn kMimeAiff("audio/aiff");
    static const Brn kMimeXAiff("audio/x-aiff");
    if (aMimeType == kMimeAiff || aMimeType == kMimeXAiff) {
        return true;
    }
    return false;
}


TBool CodecAiffBase::Recognise()
{
    Bws<12> buf;
    iController->Read(buf, buf.MaxBytes());
    const TChar* ptr = reinterpret_cast<const TChar*>(buf.Ptr());
    if(strncmp(ptr, "FORM", 4) == 0) {
        if(strncmp(ptr+8, reinterpret_cast<const TChar*>(iName.Ptr()), 4) == 0) {
            return true;
        }
    }
    return false;
}

void CodecAiffBase::StreamInitialise()
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

void CodecAiffBase::Process()
{
    LOG(kMedia, "> CodecAiffBase::Process()\n");

    if (iAudioBytesRemaining == 0) {
        THROW(CodecStreamEnded);
    }
    TUint chunkSize = DecodedAudio::kMaxBytes - (DecodedAudio::kMaxBytes % (iNumChannels * (iBitDepth/8)));
    ASSERT_DEBUG(chunkSize <= iReadBuf.MaxBytes());
    iReadBuf.SetBytes(0);
    const TUint bytes = (chunkSize < iAudioBytesRemaining? chunkSize : iAudioBytesRemaining);
    iController->Read(iReadBuf, bytes);
    Brn encodedAudioBuf(iReadBuf.Ptr(), bytes);
    iTrackOffset += iController->OutputAudioPcm(encodedAudioBuf, iNumChannels, iSampleRate, iBitDepth, iEndian, iTrackOffset);
    iAudioBytesRemaining -= bytes;

    LOG(kMedia, "< CodecAiffBase::Process()\n");
}

TBool CodecAiffBase::TrySeek(TUint aStreamId, TUint64 aSample)
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

TUint CodecAiffBase::FindChunk(const Brx& aChunkId)
{
    LOG(kMedia, "CodecAiffBase::FindChunk: ");
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
            iTrackStart += 8 + bytes;
        }
    }
}

TUint CodecAiffBase::DetermineRate(TUint16 aExponent, TUint32 aMantissa)
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

void CodecAiffBase::ProcessHeader()
{
    LOG(kMedia, "CodecAiff::ProcessHeader()\n");
    ProcessFormChunk();
    // FIXME - these could appear be in any order, i.e. metadata could be after
    // audio; still need to parse them in this kind of order, but should be
    // able to seek back if above is the case
    ProcessMiscChunks();
    ProcessCommChunk();
    ProcessSsndChunk();
}

void CodecAiffBase::ProcessFormChunk()
{
    //Should be FORM,<FileBytes>,AIFF/AIFC,<audio data>
    iController->Read(iReadBuf, 12); //Read the first 12 bytes of the IFF file, the FORM header
    const TByte* header = iReadBuf.Ptr();

    //We shouldn't be in the aiff codec unless this says 'AIFF/AIFC'
    //This isn't a track corrupt issue as it was previously checked by Recognise
    ASSERT(strncmp((const TChar*)header, "FORM", 4) == 0);

    // Get the file size (FIXME - disabled for now since we're not considering continuous streams yet)
    //here the given size includes four bytes for the file type (AIFF/AIFC)
    //TUint bytesTotal = Converter::BeUint32At(iReadBuf, 4) + 8;

    //We shouldn't be in the aiff codec unless this says 'AIFF/AIFC'
    //This isn't a track corrupt issue as it was previously checked by Recognise
    ASSERT(strncmp((const TChar*)header+8, (const TChar*)iName.Ptr(), 4) == 0);

    iTrackStart += 12;
}

void CodecAiffBase::ProcessMiscChunks()
{
    // do nothing by default
}

void CodecAiffBase::ParseCommChunk(TUint aChunkSize)
{
    iReadBuf.SetBytes(0);
    iController->Read(iReadBuf, aChunkSize);
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

    iTrackStart += aChunkSize + 8;
}

void CodecAiffBase::ProcessCommChunkExtra()
{
    // do nothing by default
}

void CodecAiffBase::ProcessCommChunk()
{
    TUint chunkSize = GetCommChunkHeader();
    ParseCommChunk(chunkSize);
    ProcessCommChunkExtra();
}

void CodecAiffBase::ProcessSsndChunk()
{
    // Find the sound chunk
    TUint ssndChunkBytes = FindChunk(Brn("SSND"));

    // There are 8 bytes included for offset and blocksize in this number
    iAudioBytesTotal = ssndChunkBytes - 8;
    iAudioBytesRemaining = iAudioBytesTotal;

    iController->Read(iReadBuf, 8); // read in offset and blocksize

    iTrackStart += 16;

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

void CodecAiffBase::SendMsgDecodedStream(TUint64 aStartSample)
{
    iController->OutputDecodedStream(iBitRate, iBitDepth, iSampleRate, iNumChannels, Brn("AIFF"), iTrackLengthJiffies, aStartSample, true);
}
