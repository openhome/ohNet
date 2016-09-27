#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Media/MimeTypeList.h>

#include <string.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecWav : public CodecBase
{
public:
    CodecWav(IMimeTypeList& aMimeTypeList);
    ~CodecWav();
private: // from CodecBase
    TBool Recognise(const EncodedStreamInfo& aStreamInfo);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
private:
    void ProcessHeader();
    void ProcessRiffChunk();
    void ProcessFmtChunk();
    void ProcessDataChunk();
    TUint FindChunk(const Brx& aChunkId);
    void SendMsgDecodedStream(TUint64 aStartSample);
private:
    Bws<DecodedAudio::kMaxBytes> iReadBuf;
    TUint iNumChannels;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iAudioBytesTotal;
    TUint iAudioBytesRemaining;
    TUint iBitRate;
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

CodecBase* CodecFactory::NewWav(IMimeTypeList& aMimeTypeList)
{ // static
    return new CodecWav(aMimeTypeList);
}



CodecWav::CodecWav(IMimeTypeList& aMimeTypeList)
    : CodecBase("WAV", kCostLow)
{
    aMimeTypeList.Add("audio/wav");
    aMimeTypeList.Add("audio/wave");
    aMimeTypeList.Add("audio/x-wav");
}

CodecWav::~CodecWav()
{
}

TBool CodecWav::Recognise(const EncodedStreamInfo& aStreamInfo)
{
    if (aStreamInfo.RawPcm()) {
        return false;
    }
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
    iTrackStart = 0;
    iTrackOffset = 0;
    iReadBuf.SetBytes(0);
}

void CodecWav::Process()
{
    if (iNumChannels == 0) {
        ProcessHeader();
        SendMsgDecodedStream(0);
        iReadBuf.SetBytes(0);
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

        iTrackOffset += iController->OutputAudioPcm(iReadBuf, iNumChannels, iSampleRate, iBitDepth, AudioDataEndian::Little, iTrackOffset);
        iAudioBytesRemaining -= iReadBuf.Bytes();

        if (iReadBuf.Bytes() < bytes) { // stream ended unexpectedly
            THROW(CodecStreamEnded);
        }
    }
}

TBool CodecWav::TrySeek(TUint aStreamId, TUint64 aSample)
{
    const TUint byteDepth = iBitDepth/8;
    const TUint64 bytePos = aSample * iNumChannels * byteDepth;

    // Some bounds checking.
    const TUint64 seekPosJiffies = Jiffies::PerSample(iSampleRate)*aSample;
    if (seekPosJiffies > iTrackLengthJiffies) {
        return false;
    }

    if (!iController->TrySeekTo(aStreamId, iTrackStart + bytePos)) {
        return false;
    }
    iTrackOffset = ((TUint64)aSample * Jiffies::kPerSecond) / iSampleRate;
    iAudioBytesRemaining = iAudioBytesTotal - (TUint)(aSample * iNumChannels * byteDepth);
    iReadBuf.SetBytes(0);
    SendMsgDecodedStream(aSample);
    return true;
}

void CodecWav::ProcessHeader()
{
    LOG(kMedia, "Wav::ProcessHeader()\n");

    // format of WAV header taken from https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
    // More useful description of WAV file format: http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html

    // We expect chunks in this order:
    // - RIFF chunk
    // - fmt chunk
    // - LIST/INFO chunk (optional)
    // - data chunk

    ProcessRiffChunk();
    ProcessFmtChunk();
    ProcessDataChunk();
}

void CodecWav::ProcessRiffChunk()
{
    iReadBuf.SetBytes(0);
    iController->Read(iReadBuf, 12);
    if (iReadBuf.Bytes() < 12) {
        THROW(CodecStreamEnded);
    }
    const TByte* header = iReadBuf.Ptr();

    //We shouldn't be in the wav codec unless this says 'RIFF'
    //This isn't a track corrupt issue as it was previously checked by Recognise
    ASSERT(strncmp((const TChar*)header, "RIFF", 4) == 0);

    // Get the file size (FIXME - disabled for now since we're not considering continuous streams yet)
    //TUint bytesTotal = (header[7]<<24) | (header[6]<<16) | (header[5]<<8) | header[4];

    //We shouldn't be in the wav codec unless this says 'WAVE'
    //This isn't a track corrupt issue as it was previously checked by Recognise
    ASSERT(strncmp((const TChar*)header+8, "WAVE", 4) == 0);

    iTrackStart += 12;
}

void CodecWav::ProcessFmtChunk()
{
    // Find "fmt " chunk (and get size).
    TUint fmtChunkBytes = FindChunk(Brn("fmt "));
    if (fmtChunkBytes != 16 && fmtChunkBytes != 18 && fmtChunkBytes != 40) {
        THROW(CodecStreamCorrupt);
    }

    // Read in remainder of "fmt " chunk.
    iReadBuf.SetBytes(0);
    iController->Read(iReadBuf, fmtChunkBytes);
    if (iReadBuf.Bytes() < fmtChunkBytes) {
        THROW(CodecStreamEnded);
    }

    // Parse "fmt " chunk.
    const TUint audioFormat = Converter::LeUint16At(iReadBuf, 0);
    // 0xfffe is WAVE_FORMAT_EXTENSIBLE, i.e., 24 bits or >2 channels.
    if (audioFormat != 0x01 && audioFormat != 0xfffe) {
        THROW(CodecStreamFeatureUnsupported);
    }

    iNumChannels = Converter::LeUint16At(iReadBuf, 2);
    iSampleRate = Converter::LeUint32At(iReadBuf, 4);
    const TUint byteRate = Converter::LeUint32At(iReadBuf, 8);
    iBitRate = byteRate * 8;
    //const TUint blockAlign = Converter::LeUint16At(iReadBuf, 12);
    iBitDepth = Converter::LeUint16At(iReadBuf, 14);

    //TUint bitStorage = 0;
    //switch(iBitDepth) {
    //    case 8:
    //        bitStorage = 8;
    //        break;
    //    case 16:
    //        bitStorage = 16;
    //        break;
    //    case 20:
    //    case 24:
    //        bitStorage = 24;
    //        break;
    //    default:
    //        THROW(CodecStreamFeatureUnsupported);
    //}

    //if ((audioFormat != 0xfffe) && (fmtChunkBytes > 16)) {
    //    if (Converter::LeUint16At(iReadBuf, 16) == 22) {
    //        if (Converter::LeUint16At(iReadBuf, 18) != bitStorage) {
    //            THROW(CodecStreamFeatureUnsupported);
    //        }
    //    }
    //}

    if (iNumChannels == 0 || iSampleRate == 0 || iBitRate == 0
            || iBitDepth == 0 || iBitDepth % 8 != 0) {
        THROW(CodecStreamCorrupt);
    }

    iTrackStart += fmtChunkBytes + 8;
}

void CodecWav::ProcessDataChunk()
{
    // Find the "data" chunk.
    TUint dataChunkBytes = FindChunk(Brn("data"));

    iAudioBytesTotal = dataChunkBytes;
    iAudioBytesRemaining = iAudioBytesTotal;

    iTrackStart += 8;

    if (iAudioBytesTotal % (iNumChannels * (iBitDepth/8)) != 0) {
        // There aren't an exact number of samples in the file => file is corrupt
        THROW(CodecStreamCorrupt);
    }
    const TUint numSamples = iAudioBytesTotal / (iNumChannels * (iBitDepth/8));
    iTrackLengthJiffies = ((TUint64)numSamples * Jiffies::kPerSecond) / iSampleRate;
}

TUint CodecWav::FindChunk(const Brx& aChunkId)
{
    LOG(kCodec, "CodecWav::FindChunk: %.*s\n", PBUF(aChunkId));

    for (;;) {
        iReadBuf.SetBytes(0);
        iController->Read(iReadBuf, 8); //Read chunk id and chunk size
        if (iReadBuf.Bytes() < 8) {
            THROW(CodecStreamEnded);
        }
        TUint bytes = Converter::LeUint32At(iReadBuf, 4);
        bytes += (bytes % 2); // one byte padding if chunk size is odd

        if (Brn(iReadBuf.Ptr(), 4) == aChunkId) {
            return bytes;
        }
        else {
            // Discard remainder of chunk.
            TUint bytesRemaining = bytes;
            while (bytesRemaining > 0) {
                iReadBuf.SetBytes(0);

                TUint readBytes = bytesRemaining;
                if (readBytes > iReadBuf.MaxBytes()) {
                    readBytes = iReadBuf.MaxBytes();
                }
                iController->Read(iReadBuf, readBytes);

                // Check if all data was delivered. (If not, the stream ended.)
                if (iReadBuf.Bytes() < readBytes) {
                    THROW(CodecStreamEnded);
                }

                bytesRemaining -= readBytes;
            }

            iTrackStart += 8 + bytes;
        }
    }
}

void CodecWav::SendMsgDecodedStream(TUint64 aStartSample)
{
    iController->OutputDecodedStream(iBitRate, iBitDepth, iSampleRate, iNumChannels, Brn("WAV"), iTrackLengthJiffies, aStartSample, true);
}
