#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Media/MimeTypeList.h>

extern "C" {
#include <ivorbisfile.h>
#include <ivorbiscodec.h>
}

#include <limits>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecVorbis : public CodecBase, public IWriter
{
private:
    static const TUint kHeaderBytesReq = 14; // granule pos is byte 6:13 inclusive
    static const TUint kSearchChunkSize = 1024;
    static const TInt kInvalidBitstream;
    static const TUint kIcyMetadataBytes = 255 * 16;
    static const TUint kBitDepth = 16;  // Bit depth always 16 for Vorbis.
public:
    static const Brn kCodecVorbis;
public:
    CodecVorbis(IMimeTypeList& aMimeTypeList);
    ~CodecVorbis();
private: // from CodecBase
    TBool Recognise(const EncodedStreamInfo& aStreamInfo);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
public:
    size_t ReadCallback(void *ptr, size_t size, size_t nmemb);
    int SeekCallback(ogg_int64_t offset, int whence);
    int CloseCallback();
    long TellCallback();
private:
    TBool FindSync();
    TUint64 GetTotalSamples();
    void BigEndian(TInt16* aDst, TInt16* aSrc, TUint aSamples);
    void FlushOutput();
    TBool StreamInfoChanged(TUint aChannels, TUint aSampleRate) const;
    void OutputMetaData();
private:
    ov_callbacks iCallbacks;

    void *iDataSource; // dummy stream identifier
    OggVorbis_File iVf;

    Bws<DecodedAudio::kMaxBytes> iInBuf;
    Bws<DecodedAudio::kMaxBytes> iOutBuf;
    Bws<2*kSearchChunkSize> iSeekBuf;   // can store 2 read chunks, to check for sync word across read boundaries
 
    TUint iSampleRate;
    TUint iBytesPerSec;
    TUint iBitrateAverage;
    TUint iChannels;
    TUint iBytesPerSample;
    TUint64 iSamplesTotal;
    TUint64 iTotalSamplesOutput;
    TUint64 iTrackLengthJiffies;
    TUint64 iTrackOffset;
    TUint64 iReadOffset;
    TInt iBitstream;
    Bws<kIcyMetadataBytes> iIcyMetadata;
    Bws<kIcyMetadataBytes> iNewIcyMetadata;

    TBool iStreamEnded;
    TBool iNewStreamStarted;
};

} //namespace Codec
} //namespace Media
} //namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewVorbis(IMimeTypeList& aMimeTypeList)
{ // static
    return new CodecVorbis(aMimeTypeList);
}


const TInt CodecVorbis::kInvalidBitstream = std::numeric_limits<TInt>::max();
const Brn CodecVorbis::kCodecVorbis("VORBIS");

size_t ReadCallback(void *ptr, size_t size, size_t nmemb, void *datasource);
int SeekCallback(void *datasource, ogg_int64_t offset, int whence);
int CloseCallback(void *datasource);
long TellCallback(void *datasource);

size_t CodecVorbis::ReadCallback(void *ptr, size_t size, size_t nmemb)
{
    TUint bytes = size * nmemb;
    //LOG(kCodec,"CodecVorbis::CallbackRead: attempt to read %u bytes\n", bytes);
    Bwn buf((TByte *)ptr, bytes);
    try{
        if (iReadOffset > iController->StreamPos()) {
            // Have already read some data (during Recognise()) which is now
            // being replayed by Rewinder. Skip it.
            TUint64 remaining = iReadOffset-iController->StreamPos();
            LOG(kCodec, "CodecVorbis::ReadCallback iReadOffset: %llu, iController->StreamPos(): %llu, remaining: %llu\n", iReadOffset, iController->StreamPos(), remaining);
            while (remaining > 0) {
                TUint bytes = buf.MaxBytes();
                if (remaining < bytes) {
                    // Safe cast.
                    // Only enter here if remaining < buf.MaxBytes() (which is a TUint).
                    bytes = static_cast<TUint>(remaining);
                }
                iController->Read(buf, bytes);
                ASSERT(buf.Bytes() != 0); // Managed to read to this pos previously during Recognise().
                remaining -= buf.Bytes();
                buf.SetBytes(0);
            }
        }
        if (!iController->StreamLength() || (iController->StreamPos() < iController->StreamLength())) {
            // Tremor pulls more data after stream exhaustion, as it is looking
            // for 0 bytes to signal EOF. However, controller signals EOF by outputting fewer
            // than requested bytes; any subsequent pulls may pull a quit msg.

            // Account for this by checking if stream has already been exhausted;
            // if not, we'll do another read; otherwise we won't do anything and Tremor
            // will get its EOF identifier.
            iController->Read(buf, bytes);
            iReadOffset = iController->StreamPos();
        }
    }
    catch(CodecStreamEnded) {
        buf.SetBytes(0);
    }

    //LOG(kCodec,"CodecVorbis::CallbackRead: read %u bytes\n", buf.Bytes());
    return buf.Bytes();
}

int CodecVorbis::SeekCallback(ogg_int64_t offset, int whence)
{
    LOG(kCodec,"CodecVorbis::SeekCallback offset %lld, whence %d, iSamplesTotal %llu, iController->StreamLength() %llu\n", offset, whence, iSamplesTotal, iController->StreamLength());
    // want Vorbis to handle this as a non-seekable stream
    return -1;  // non-seekable
}

int CodecVorbis::CloseCallback()
{
    LOG(kCodec,"CodecVorbis::CLOSE\n");
    return 0;
}

long CodecVorbis::TellCallback()
{
    TUint64 tell;
    tell = iController->StreamPos();
    LOG(kCodec,"CodecVorbis::Tell %llu\n", tell);

    return (long)tell;
}

size_t ReadCallback(void *ptr, size_t size, size_t nmemb, void *datasource)
{
  LOG(kCodec,"CallbackRead\n");

    return ((CodecVorbis *)datasource)->ReadCallback(ptr, size, nmemb);
}

int SeekCallback(void *datasource, ogg_int64_t offset, int whence)
{
    return ((CodecVorbis *)datasource)->SeekCallback(offset, whence);
}

int CloseCallback(void *datasource)
{
    return ((CodecVorbis *)datasource)->CloseCallback();
}

long TellCallback(void *datasource)
{
    return ((CodecVorbis *)datasource)->TellCallback();
}


CodecVorbis::CodecVorbis(IMimeTypeList& aMimeTypeList)
    : CodecBase("Vorbis", kCostHigh)
{
    iDataSource = this;
    iCallbacks.read_func = ::ReadCallback;
    iCallbacks.seek_func = ::SeekCallback;
    iCallbacks.close_func = ::CloseCallback;
    iCallbacks.tell_func = ::TellCallback;
    aMimeTypeList.Add("audio/ogg");
    aMimeTypeList.Add("audio/x-ogg");
    aMimeTypeList.Add("application/ogg");
}

CodecVorbis::~CodecVorbis()
{
    LOG(kCodec, "CodecVorbis::~CodecVorbis\n");
}

TBool CodecVorbis::Recognise(const EncodedStreamInfo& aStreamInfo)
{
    LOG(kCodec, "CodecVorbis::Recognise\n");

    if (aStreamInfo.RawPcm()) {
        return false;
    }
    iReadOffset = 0;
    iSamplesTotal = 0;
    TBool isVorbis = (ov_test_callbacks(iDataSource, &iVf, nullptr, 0, iCallbacks) == 0);

    return isVorbis;
}

void CodecVorbis::StreamInitialise()
{
    LOG(kCodec, "CodecVorbis::StreamInitialise\n");
    iBitstream = kInvalidBitstream;
    iStreamEnded = false;
    iNewStreamStarted = false;

    const TInt opened = ov_test_open(&iVf);
    if (opened < 0) {
        THROW(CodecStreamCorrupt);
    }

    vorbis_info* info = ov_info(&iVf, -1);
    iChannels = info->channels;
    iBitrateAverage = info->bitrate_nominal;
    iSampleRate = info->rate;

    iTotalSamplesOutput = 0;
    iInBuf.SetBytes(0);
    iOutBuf.SetBytes(0);

    iBytesPerSample = iChannels*kBitDepth/8;
    iBytesPerSec = iBitrateAverage/8; // bitrate of raw data rather than the output bitrate
    iTrackLengthJiffies = 0;
    iTrackOffset = 0;
    iIcyMetadata.Replace(Brx::Empty());

    if (iController->StreamLength() > 0) {
        // Try do an out-of-band read and parse the final Ogg page ourselves to
        // get the granule pos field. When Vorbis is contained within an Ogg,
        // the granule pos field contains the sample pos, and the final Ogg
        // page tells us the total number of samples in that stream (for
        // non-chained streams).

        // If trying to read and parse the final Ogg page fails, fall back to
        // estimating the track length via a calculation.

        if (FindSync()) {
            try {
                iSamplesTotal = GetTotalSamples();
            }
            catch (CodecStreamCorrupt&)
            {}
        }


        if (iSamplesTotal == 0) { // didn't manage to parse last Ogg page; fall back to estimation
            iSamplesTotal = iSampleRate * iController->StreamLength() / iBytesPerSec; // estimate from average bitrate and file size
        }

        iTrackLengthJiffies = (iSamplesTotal * Jiffies::kPerSecond) / iSampleRate;
    }

    LOG(kCodec, "CodecVorbis::StreamInitialise iBitrateAverage %u, kBitDepth %u, iSampleRate %u, iChannels %u, iTrackLengthJiffies %llu\n", iBitrateAverage, kBitDepth, iSampleRate, iChannels, iTrackLengthJiffies);
    iController->OutputDecodedStream(iBitrateAverage, kBitDepth, iSampleRate, iChannels, kCodecVorbis, iTrackLengthJiffies, 0, false);
}

void CodecVorbis::StreamCompleted()
{
    LOG(kCodec, "CodecVorbis::StreamCompleted\n");
    ov_clear(&iVf);
}

void CodecVorbis::Write(TByte aValue)
{
    iSeekBuf.Append(aValue);
}

void CodecVorbis::Write(const Brx& aBuffer)
{
    iSeekBuf.Append(aBuffer);
}

void CodecVorbis::WriteFlush()
{
}

TBool CodecVorbis::TrySeek(TUint aStreamId, TUint64 aSample)
{
    LOG(kCodec, "CodecVorbis::TrySeek(%u, %llu)\n", aStreamId, aSample);

    // Convert to approximate byte position in file.
    TUint64 bytes = aSample * iController->StreamLength()/iSamplesTotal;
    if (bytes > iController->StreamLength()) {
        bytes = iController->StreamLength() - 1;
    }

    TBool canSeek = iController->TrySeekTo(aStreamId, bytes);
    LOG(kCodec, "CodecVorbis::Seek to sample: %lld, byte: %llu returned %u\n", aSample, bytes, canSeek);
    if (canSeek) {
        iTotalSamplesOutput = aSample;
        iTrackOffset = (aSample * Jiffies::kPerSecond) / iSampleRate;
        iInBuf.SetBytes(0);
        iOutBuf.SetBytes(0);
        iController->OutputDecodedStream(0, kBitDepth, iSampleRate, iChannels, kCodecVorbis, iTrackLengthJiffies, aSample, false);
    }
    return canSeek;
}

TBool CodecVorbis::FindSync()
{
    // If this method finds the Ogg sync word ("OggS"), it will return true and
    // iSeekBuf will be the data from the last sync word found onwards.
    // It will return false otherwise and the state of iSeekBuf will be
    // undefined.

    // Vorbis codec reads backwards in 1024-byte chunks, so we do the same.

    TBool keepLooking = true;
    TUint searchSize = kSearchChunkSize;
    TUint64 offset = iController->StreamLength();
    TBool syncFound = false;
    Bws<kSearchChunkSize> stashBuf;

    if (iController->StreamLength() < searchSize) {
        offset = 0;
        searchSize = static_cast<TUint>(iController->StreamLength());
    }
    else {
        offset = iController->StreamLength()-searchSize;
    }

    while (keepLooking) {
        iSeekBuf.SetBytes(0);

        // This will cause callbacks via the IWriter interface.
        // iSeekBuf will only be modified by IWriter callbacks during the
        // Read() below.
        TBool res = iController->Read(*this, offset, searchSize);

        // Try to find the "OggS" sync word.
        TUint idx = 0;
        if (res) {
            iSeekBuf.Append(stashBuf); // sync word may occur across read boundary
            Brn sync("OggS");
            TInt bytes = iSeekBuf.Bytes() - sync.Bytes(); // will go -ve if incompatible sizes
            TInt i = 0;
            for (i=0; i<=bytes; i++) {
                if ((strncmp((char*)&iSeekBuf[i], (char*)&sync[0], sync.Bytes()) == 0)
                        && (iSeekBuf.Bytes()-i >= kHeaderBytesReq)) {
                    // Don't break here - there may still be more Ogg pages
                    // in the buffer. We want the last one, so process
                    // whole buf in case there are more.
                    syncFound = true;
                    idx = i;
                    keepLooking = false;
                }
            }
        }

        if (syncFound) {
            // Shift last Ogg page to front of buffer.
            iSeekBuf.Replace(iSeekBuf.Split(idx));
            break;
        }

        if (!res || offset == 0) {
            // Problem reading stream, or exhausted entire stream without
            // finding required data.
            keepLooking = false;
        }
        else {
            stashBuf.Replace(iSeekBuf.Ptr(), searchSize);   // stash prev read in case Ogg page
                                                            // is split on read boundary.
            TUint64 stepBack = kSearchChunkSize;
            if (offset < kSearchChunkSize) {
                stepBack = offset;
                searchSize = static_cast<TUint>(offset);
            }
            offset -= stepBack;
        }
    }

    return syncFound;
}

TUint64 CodecVorbis::GetTotalSamples()
{
    if (iSeekBuf.Bytes() >= kHeaderBytesReq) {
        TUint64 granulePos1 = Converter::LeUint32At(iSeekBuf, 6);
        TUint64 granulePos2 = Converter::LeUint32At(iSeekBuf, 10);
        TUint64 granulePos = (granulePos1 | (granulePos2 << 32));
        return granulePos;
    }

    // We shouldn't have a truncated Ogg page, as we check there are enough
    // header bytes during the sync word search.
    THROW(CodecStreamCorrupt);
}

// copy audio data to output buffer, converting to big endian if required.
void CodecVorbis::BigEndian(TInt16* aDst, TInt16* aSrc, TUint aSamples)
{
    aSamples *= iChannels;
    while(aSamples--) {
        *aDst++ = Arch::BigEndian2(*aSrc++);
    }
}

void CodecVorbis::Process()
{
    LOG(kCodec, "\n CodecVorbis::Process\n");

    TInt bitstream = 0;
    TUint iPrevBytes = iOutBuf.Bytes();

    if(!iStreamEnded || !iNewStreamStarted) {
        LOG(kCodec, "CodecVorbis::Process bitstream %d\n", bitstream);
        try {
            char *pcm = (char *)iInBuf.Ptr();
            TInt request = (iOutBuf.MaxBytes() - iOutBuf.Bytes());
            ASSERT((TInt)iInBuf.MaxBytes() >= request);

            TInt bytes = 0;
            bytes = ov_read(&iVf, pcm, request, (int*)&bitstream);

            if (bytes == 0) {
                THROW(CodecStreamEnded);
            }

            if (bytes == OV_HOLE) {
                LOG(kCodec, "CodecVorbis::Process ov_read error OV_HOLE, requested %u bytes. Attempting to continue decoding.\n", request);
                return;
            }

            if (bytes < 0) {
                LOG(kCodec, "CodecVorbis::Process ov_read error %d, requested %d bytes\n", bytes, request);
                THROW(CodecStreamCorrupt);
            }

            if(bitstream != iBitstream) {
                LOG(kCodec, "CodecVorbis::Process new bitstream %d, %d\n", iBitstream, bitstream);
                iBitstream = bitstream;

                // Encountered a new logical bitstream. Better push any
                // buffered PCM from previous stream.
                if (iOutBuf.Bytes() > 0) {
                    iTrackOffset += iController->OutputAudioPcm(iOutBuf, iChannels, iSampleRate,
                        kBitDepth, EMediaDataEndianBig, iTrackOffset);
                    iOutBuf.SetBytes(0);
                    LOG(kCodec, "CodecVorbis::Process output (new bitstream detected) - total samples = %llu\n", iTotalSamplesOutput);
                }

                // From ov_read() docs:
                // "However, when reading audio back, the application must be aware that multiple bitstream sections do not necessarily use the same number of channels or sampling rate."

                // Call ov_info() and send a MsgDecodedStream to notify of channel count and/or sample rate changes, send a new MsgMetaText, then continue decoding as normal.
                vorbis_info* info = ov_info(&iVf, -1);
                const TBool infoChanged = StreamInfoChanged(info->channels, info->rate);

                iChannels = info->channels;
                iBitrateAverage = info->bitrate_nominal;
                iSampleRate = info->rate;

                iBytesPerSample = iChannels*kBitDepth/8;
                iBytesPerSec = iBitrateAverage/8; // bitrate of raw data rather than the output bitrate

                // FIXME - reusing iTrackLengthJiffies is incorrect, but it was
                // almost definitely wrong when we started this chained stream anyway.

                LOG(kCodec, "CodecVorbis::Process new bitstream: iBitrateAverage %u, kBitDepth %u, iSampleRate %u, iChannels %u, iTrackLengthJiffies %llu\n", iBitrateAverage, kBitDepth, iSampleRate, iChannels, iTrackLengthJiffies);


                // FIXME - output MsgBitrate here if iBitrateAverage has changed.

                if (infoChanged) {
                    iController->OutputDecodedStream(iBitrateAverage, kBitDepth, iSampleRate, iChannels, kCodecVorbis, iTrackLengthJiffies, 0, false);
                }

                OutputMetaData();
            }

            TUint samples = bytes/iBytesPerSample;
            TByte* dstByte = const_cast<TByte*>(iOutBuf.Ptr()) + iOutBuf.Bytes();
            TInt16* dst = reinterpret_cast<TInt16*>(dstByte);
            BigEndian(dst, (TInt16 *)pcm, samples);
            iOutBuf.SetBytes(iOutBuf.Bytes()+bytes);
            iTotalSamplesOutput += samples;

            LOG(kCodec, "CodecVorbis::Process read - bytes %d, iPrevBytes %d\n", bytes, iPrevBytes);
            if (iOutBuf.MaxBytes() - iOutBuf.Bytes() < (TUint)((kBitDepth/8) * iChannels)) {
                iTrackOffset += iController->OutputAudioPcm(iOutBuf, iChannels, iSampleRate,
                    kBitDepth, EMediaDataEndianBig, iTrackOffset);
                iOutBuf.SetBytes(0);
                LOG(kCodec, "CodecVorbis::Process output - total samples = %llu\n", iTotalSamplesOutput);
            }
        }
        catch(CodecStreamEnded) {
            iStreamEnded = true;
        }
        catch (CodecStreamStart) {
            iNewStreamStarted = true;
        }
    }

    FlushOutput();
}

// flush any remaining samples from the decoded buffer
void CodecVorbis::FlushOutput()
{    
    LOG(kCodec, "CodecVorbis::FlushOutput\n");

    if (iStreamEnded || iNewStreamStarted) {
        if (iOutBuf.Bytes() > 0) {
            iTrackOffset += iController->OutputAudioPcm(iOutBuf, iChannels, iSampleRate,
                kBitDepth, EMediaDataEndianBig, iTrackOffset);
            iOutBuf.SetBytes(0);
        }
        if (iNewStreamStarted) {
            THROW(CodecStreamStart);
        }
        THROW(CodecStreamEnded);
    }
}

TBool CodecVorbis::StreamInfoChanged(TUint aChannels, TUint aSampleRate) const
{
    return (aChannels != iChannels || aSampleRate != iSampleRate);
}

void CodecVorbis::OutputMetaData()
{
    vorbis_comment* vc = ov_comment(&iVf, -1);
    Brn artist = Brx::Empty();
    Brn title = Brx::Empty();

    for (TInt i=0; i<vc->comments; i++) {
        Brn comment(reinterpret_cast<const TByte*>(vc->user_comments[i]), vc->comment_lengths[i]);
        LOG(kCodec, "CodecVorbis::OutputMetaData comment: ");
        LOG(kCodec, comment);
        LOG(kCodec, "\n");

        Parser parser(comment);
        Brn tag = parser.Next('=');
        if (Ascii::CaseInsensitiveEquals(tag, Brn("artist"))) {
            artist = parser.Remaining();
        }
        else if (Ascii::CaseInsensitiveEquals(tag, Brn("title"))) {
            title = parser.Remaining();
        }

        if (artist != Brx::Empty() && title != Brx::Empty()) {
            break; // terminate loop early if we have both artist and title
        }
    }

    if (artist != Brx::Empty() || title != Brx::Empty()) {
        iNewIcyMetadata.Replace("<DIDL-Lite xmlns:dc='http://purl.org/dc/elements/1.1/' ");
        iNewIcyMetadata.Append("xmlns:upnp='urn:schemas-upnp-org:metadata-1-0/upnp/' ");
        iNewIcyMetadata.Append("xmlns='urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/'>");
        iNewIcyMetadata.Append("<item id='' parentID='' restricted='True'><dc:title>");

        iNewIcyMetadata.Append(artist);
        if (artist != Brx::Empty() && title != Brx::Empty()) {
            iNewIcyMetadata.Append(" - ");
        }
        iNewIcyMetadata.Append(title);

        iNewIcyMetadata.Append("</dc:title><upnp:albumArtURI></upnp:albumArtURI>");
        iNewIcyMetadata.Append("<upnp:class>object.item</upnp:class></item></DIDL-Lite>");
        if (iNewIcyMetadata != iIcyMetadata) {
            iIcyMetadata.Replace(iNewIcyMetadata);
            iController->OutputMetaText(iIcyMetadata);
        }
    }
}
