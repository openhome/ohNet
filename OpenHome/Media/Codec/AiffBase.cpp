#include <OpenHome/Media/Codec/AiffBase.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Av/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;


CodecAiffBase::CodecAiffBase(EMediaDataEndian aEndian)
    :iEndian(aEndian)
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

void CodecAiffBase::SendMsgDecodedStream(TUint64 aStartSample)
{
    iController->OutputDecodedStream(iBitRate, iBitDepth, iSampleRate, iNumChannels, Brn("AIFF"), iTrackLengthJiffies, aStartSample, true);
}
