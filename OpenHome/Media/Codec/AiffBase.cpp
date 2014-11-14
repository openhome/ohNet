#include <OpenHome/Media/Codec/AiffBase.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;


CodecAiffBase::CodecAiffBase(const Brx& aName)
    : iName(aName)
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


TBool CodecAiffBase::Recognise(const EncodedStreamInfo& aStreamInfo)
{
    if (aStreamInfo.RawPcm()) {
        return false;
    }
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
    iEndian = EMediaDataEndianBig;
    iReadBuf.SetBytes(0);

    ProcessHeader(); // Could throw CodecStreamEnded/CodecStreamCorrupt.
    SendMsgDecodedStream(0);
    iReadBuf.SetBytes(0);
}

void CodecAiffBase::Process()
{
    LOG(kCodec, "> CodecAiffBase::Process()\n");

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

    iTrackOffset += iController->OutputAudioPcm(iReadBuf, iNumChannels, iSampleRate, iBitDepth, iEndian, iTrackOffset);
    iAudioBytesRemaining -= bytes;

    if (iReadBuf.Bytes() < bytes) { // stream ended unexpectedly
        THROW(CodecStreamEnded);
    }

    LOG(kCodec, "< CodecAiffBase::Process()\n");
}

TBool CodecAiffBase::TrySeek(TUint aStreamId, TUint64 aSample)
{
    const TUint byteDepth = iBitDepth/8;
    const TUint64 bytePos = aSample * iNumChannels * byteDepth;
    if (!iController->TrySeek(aStreamId, iTrackStart + bytePos)) {
        return false;
    }
    iTrackOffset = ((TUint64)aSample * Jiffies::kPerSecond) / iSampleRate;
    iAudioBytesRemaining = iAudioBytesTotal - (TUint)(aSample * iNumChannels * byteDepth);
    SendMsgDecodedStream(aSample);
    return true;
}

TUint CodecAiffBase::FindChunk(const Brx& aChunkId)
{
    LOG(kCodec, "CodecAiffBase::FindChunk: ");
    LOG(kCodec, aChunkId);
    LOG(kCodec, "\n");

    for (;;) {
        iReadBuf.SetBytes(0);
        iController->Read(iReadBuf, 8); //Read chunk id and chunk size
        if (iReadBuf.Bytes() < 8) {
            THROW(CodecStreamEnded);
        }
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
            if (iReadBuf.Bytes() < bytes) {
                THROW(CodecStreamEnded);
            }
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
     *
     * Some AIFF files use 22255Hz and 11127Hz sample rates, which are
     * old Macintosh "good enough" sample rates. Adjust these into playable
     * sample rates here.
     *
     * Source:
     * http://homepages.gold.ac.uk/ems/pdf/Hyperprism/Files/hppc_digital_audio.html
     */
    TUint rate = 0;

    if (aExponent < kUnder65kHz) {
        rate = aMantissa >> (0x401e - aExponent);
    }
    else {
        rate = aMantissa >> (aExponent - 0x4007);
    }

    if (rate == k22255Hz) {
        LOG(kCodec, "CodecAiffBase::DetermineRate Adjusting 22255Hz to 22050Hz\n");
        rate = k22050Hz;
    }
    else if (rate ==  k11127Hz) {
        LOG(kCodec, "CodecAiffBase::DetermineRate Adjusting 11127Hz to 11025Hz\n");
        rate = k11025Hz;
    }

    return rate;
}

void CodecAiffBase::ProcessHeader()
{
    LOG(kCodec, "CodecAiff::ProcessHeader()\n");
    // Any of these methods could throw a CodecStreamEnded/CodecStreamCorrupt.
    ProcessFormChunk();
    // FIXME - these could appear be in any order, i.e. metadata could be after
    // audio; still need to parse them in this kind of order, but should be
    // able to seek back if above is the case
    ProcessCommChunk();
    ProcessSsndChunk();
}

void CodecAiffBase::ProcessFormChunk()
{
    //Should be FORM,<FileBytes>,AIFF/AIFC,<audio data>
    iController->Read(iReadBuf, 12); //Read the first 12 bytes of the IFF file, the FORM header
    if (iReadBuf.Bytes() < 12) {
        THROW(CodecStreamEnded);
    }
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

void CodecAiffBase::ParseCommChunk(TUint aChunkSize)
{
    iReadBuf.SetBytes(0);
    iController->Read(iReadBuf, aChunkSize);
    if (iReadBuf.Bytes() < aChunkSize) {
        THROW(CodecStreamEnded);
    }
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

    iReadBuf.SetBytes(0);
    iController->Read(iReadBuf, 8); // read in offset and blocksize
    if (iReadBuf.Bytes() < 8) {
        THROW(CodecStreamEnded);
    }

    iTrackStart += 16;

    if (iAudioBytesTotal % (iNumChannels * (iBitDepth/8)) != 0) {
        // There aren't an exact number of samples in the file => file is corrupt
        THROW(CodecStreamCorrupt);
    }

    const TUint numSamples = iAudioBytesTotal / (iNumChannels * (iBitDepth/8));
    if (numSamples != iSamplesTotal) {
        THROW(CodecStreamCorrupt);
    }
    iTrackLengthJiffies = ((TUint64)numSamples * Jiffies::kPerSecond) / iSampleRate;
}

void CodecAiffBase::SendMsgDecodedStream(TUint64 aStartSample)
{
    iController->OutputDecodedStream(iBitRate, iBitDepth, iSampleRate, iNumChannels, Brn("AIFF"), iTrackLengthJiffies, aStartSample, true);
}
