#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Av/Debug.h>

#undef X        //defined in os_types.h!

extern "C" {

#include <ogg.h>
#include <os_types.h>
#include <config_types.h>
#include <ivorbisfile.h>
#include <ivorbiscodec.h>
}

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecVorbis : public CodecBase, public IWriter
{
public:
    static const Brn kCodecVorbis;
public:
    CodecVorbis();
    ~CodecVorbis();
private: // from CodecBase
    TBool SupportsMimeType(const Brx& aMimeType);
    TBool Recognise();
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
    void PrintCallback(char *message);
private:
    TUint64 GetTotalSamples(TUint aIndex, const Brx& aStashBuf);
    void BigEndian(TInt16* aDst, TInt16* aSrc, TUint aSamples);
    void FlushOutput();
private:
    static const TUint kSearchChunkSize = 1024;

    ov_callbacks iCallbacks;

    void *iDataSource; // dummy stream identifier
    OggVorbis_File iVf;
    vorbis_info* iInfo;

    Bws<DecodedAudio::kMaxBytes> iInBuf;
    Bws<DecodedAudio::kMaxBytes> iOutBuf;
    Bws<kSearchChunkSize> iSeekBuf;
    TUint32 iAudioBytes;
 
    TUint32 iSampleRate;
    TUint32 iBytesPerSec;
    TUint32 iBitrateMax;
    TUint32 iBitrateAverage;
    TUint16 iChannels;
    TUint16 iBytesPerSample;
    TUint16 iBitDepth;
    TUint64 iSamplesTotal;
    TUint64 iTotalSamplesOutput;
    TUint64 iTrackLengthJiffies;
    TUint64 iTrackOffset;
    TInt iLink;

    TBool iStreamEnded;
    TBool iNewStreamStarted;
};

} //namespace Codec
} //namespace Media
} //namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewVorbis()
{ // static
    return new CodecVorbis();
}



const Brn CodecVorbis::kCodecVorbis("VORBIS");

size_t ReadCallback(void *ptr, size_t size, size_t nmemb, void *datasource);
int SeekCallback(void *datasource, ogg_int64_t offset, int whence);
int CloseCallback(void *datasource);
long TellCallback(void *datasource);
void PrintCallback (void *datasource, char *message);

size_t CodecVorbis::ReadCallback(void *ptr, size_t size, size_t nmemb)
{
    TUint bytes = size * nmemb;
    //LOG(kCodec,"CodecVorbis::CallbackRead: attempt to read %u bytes\n", bytes);
    Bwn buf((TByte *)ptr, bytes);
    try{
        if (!iController->StreamLength() || (iController->StreamPos() < iController->StreamLength())) {
            // Tremor pulls more data after stream exhaustion, as it is looking
            // for 0 bytes to signal EOF. However, controller signals EOF by outputting fewer
            // than requested bytes; any subsequent pulls may pull a quit msg.

            // Account for this by checking if stream has already been exhausted;
            // if not, we'll do another read; otherwise we won't do anything and Tremor
            // will get its EOF identifier.
            iController->Read(buf, bytes);
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

void CodecVorbis::PrintCallback (char *message)
{
    LOG(kCodec,"%s", message);
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

void PrintCallback(void *datasource, char *message)
{
    ((CodecVorbis *)datasource)->PrintCallback(message);
}


CodecVorbis::CodecVorbis()
{
    iDataSource = this;
    iCallbacks.read_func = ::ReadCallback;
    iCallbacks.seek_func = ::SeekCallback;
    iCallbacks.close_func = ::CloseCallback;
    iCallbacks.tell_func = ::TellCallback;
    iCallbacks.print_func = ::PrintCallback;
}

CodecVorbis::~CodecVorbis()
{
    LOG(kCodec, "CodecVorbis::~CodecVorbis\n");
}

TBool CodecVorbis::SupportsMimeType(const Brx& aMimeType)
{
    static const Brn kMimeOgg1("audio/ogg");
    static const Brn kMimeXOgg("audio/x-ogg");
    static const Brn kMimeOgg2("application/ogg");
    if (aMimeType == kMimeOgg1 || aMimeType == kMimeXOgg || aMimeType == kMimeOgg2) {
        return true;
    }
    return false;
}

TBool CodecVorbis::Recognise()
{
    LOG(kCodec, "CodecVorbis::Recognise\n");

    iSamplesTotal = 0;
    TBool isVorbis = (ov_test_callbacks(iDataSource, &iVf, NULL, 0, iCallbacks) == 0);

    return isVorbis;
}

void CodecVorbis::StreamInitialise()
{
    LOG(kCodec, "CodecVorbis::StreamInitialise\n");
    iLink = 0;
    iStreamEnded = false;
    iNewStreamStarted = false;

    ov_test_open(&iVf);

    iInfo = ov_info(&iVf, -1);
    iChannels = (TUint16)iInfo->channels;
    iBitrateMax = iInfo->bitrate_upper;
    iBitrateAverage = iInfo->bitrate_nominal;
    iSampleRate = iInfo->rate;

    iBitDepth = 16;                 //always 16bit
    iTotalSamplesOutput = 0;
    iInBuf.SetBytes(0);

    iBytesPerSample = iChannels*iBitDepth/8;
    iBytesPerSec = iBitrateAverage/8; // bitrate of raw data rather than the output bitrate
    iTrackLengthJiffies = 0;
    iTrackOffset = 0;

    if (iController->StreamLength() > 0) {
        // Try do an out-of-band read and parse the final Ogg page ourselves to
        // get the granule pos field. When Vorbis is contained within an Ogg,
        // the granule pos field contains the sample pos, and the final Ogg
        // page tells us the total number of samples in that stream (for
        // non-chained streams).

        // If trying to read and parse the final Ogg page fails, fall back to
        // estimating the track length via a calculation.

        // Vorbis codec reads backwards in 1024-byte chunks, so we do the same.

        TBool keepLooking = true;
        TUint searchSize = kSearchChunkSize;
        TUint64 offset = iController->StreamLength();
        Bws<kSearchChunkSize> stashBuf; // stash prev read in case Ogg page is
                                        // split on read boundary.
        TBool syncFound = false;
        TInt idx = 0;

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
            if (res) {
                Brn sync("OggS");
                TInt bytes = iSeekBuf.Bytes() - sync.Bytes(); // will go -ve if incompatible sizes

                TInt i = 0;
                for (i=0; i<=bytes; i++) {
                    if (strncmp((char*)&iSeekBuf[i], (char*)&sync[0], sync.Bytes()) == 0) {
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
                break;
            }

            if (!res || offset == 0) {
                // Problem reading stream, or exhausted entire stream without
                // finding required data.
                keepLooking = false;
            }
            else {
                stashBuf.Replace(iSeekBuf); // don't want to get here if syncFound == true - reason for break block above
                TUint64 stepBack = kSearchChunkSize;
                if (offset < kSearchChunkSize) {
                    stepBack = offset;
                    searchSize = static_cast<TUint>(offset);
                }
                offset -= stepBack;
            }
        }


        // If we've found sync, may not have enough data in iSeekBuf
        // - might have to concatenate it with stashBuf.
        if (syncFound) {
            try {
                iSamplesTotal = GetTotalSamples(idx, stashBuf);
            }
            catch (CodecStreamCorrupt&)
            {}
        }


        if (iSamplesTotal == 0) { // didn't manage to parse last Ogg page; fall back to estimation
            iSamplesTotal = iSampleRate * iController->StreamLength() / iBytesPerSec; // estimate from average bitrate and file size
        }

        iTrackLengthJiffies = (iSamplesTotal * Jiffies::kJiffiesPerSecond) / iSampleRate;
    }

    LOG(kCodec, "CodecVorbis::StreamInitialise iBitrateAverage %u, iBitDepth %u, iSampleRate %u, iChannels %u, iTrackLengthJiffies %llu\n", iBitrateAverage, iBitDepth, iSampleRate, iChannels, iTrackLengthJiffies);
    iController->OutputDecodedStream(iBitrateAverage, iBitDepth, iSampleRate, iChannels, kCodecVorbis, iTrackLengthJiffies, 0, false);
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
    LOG(kCodec, "CodecVorbis::Seek(%u, %llu)\n", aStreamId, aSample);

    // convert to approximate byte position in file
    TUint64 bytes = aSample * iController->StreamLength()/iSamplesTotal;
    if (bytes > iController->StreamLength()) {
        bytes = iController->StreamLength() - 1;
    }

    LOG(kCodec, "CodecVorbis::Seek to sample: %lld, byte: %llu\n", aSample, bytes);
    TBool canSeek = iController->TrySeek(aStreamId, bytes);
    if (canSeek) {
        iTotalSamplesOutput = aSample;
        iTrackOffset = (aSample * Jiffies::kJiffiesPerSecond) / iSampleRate;
        iController->OutputDecodedStream(0, iBitDepth, iSampleRate, iChannels, kCodecVorbis, iTrackLengthJiffies, aSample, false);
    }
    return canSeek;
}

TUint64 CodecVorbis::GetTotalSamples(TUint aIndex, const Brx& aStashBuf)
{
    // If we've found sync, may not have enough data in iSeekBuf
    // - might have to concatenate it with aStashBuf.
    static const TUint kHeaderBytesReq = 14; // granule pos is byte 6:13 inclusive
    Bws<kHeaderBytesReq> pageBuf;
    // We require 14 bytes from start of Ogg page for granule pos.
    // If we don't have that, split data in iSeekBuf and stashBuf
    // and combine them so we have what we need.
    if (iSeekBuf.Bytes()-aIndex >= kHeaderBytesReq) {
        pageBuf.Replace(iSeekBuf.Split(aIndex, kHeaderBytesReq));
    }
    else {
        const TUint remainder = kHeaderBytesReq-pageBuf.Bytes();
        if (aStashBuf.Bytes() >= remainder) {
            pageBuf.Replace(iSeekBuf.Split(aIndex));
            pageBuf.Append(aStashBuf.Split(0, remainder));
        }
        else {
            // Stream is truncated at last ogg; could check this before
            // we finish requesting data and get lastOgg-1.
            // FIXME - Just give up here for now.
            pageBuf.SetBytes(0);
        }
    }

    if (pageBuf.Bytes() > 0) {
        TUint64 granulePos1 = Converter::LeUint32At(pageBuf, 6);
        TUint64 granulePos2 = Converter::LeUint32At(pageBuf, 10);
        TUint64 granulePos = (granulePos1 | (granulePos2 << 32));
        return granulePos;
    }
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

    TInt *bitstream = 0;
    TUint iPrevBytes = iOutBuf.Bytes();

    if(!iStreamEnded || !iNewStreamStarted) {
        LOG(kCodec, "CodecVorbis::Process bitstream %d\n", *bitstream);
        try {
            char *pcm = (char *)iInBuf.Ptr();
            TInt request = (iOutBuf.MaxBytes() - iOutBuf.Bytes());
            ASSERT((TInt)iInBuf.MaxBytes() >= request);

            TInt bytes = 0;
            bytes = ov_read(&iVf, pcm, request, (int *)bitstream);

            if(bytes == 0) {
                THROW(CodecStreamEnded);
            }
            if(bytes < 0) {
                LOG(kCodec, "CodecVorbis::Process ov_read error %d, requested %d\n", bytes, request);
                THROW(CodecStreamCorrupt);
            }

            if(iLink != iVf.current_link) {
                // new track - new metadata
                // As the vorbis decoder is not preloaded with all vorbis_info structs,
                // usual scenario is where we encounter our first (logical) bitstream of
                // audio in the chain, so link goes from 0 to 1.
                LOG(kCodec, "CodecVorbis::Process new track %d, %d\n", iLink, iVf.current_link);
                iLink = iVf.current_link;
                // We don't yet handle the case of chained bitstreams.
                if (iLink > 1) {
                    Log::Print("\nERROR: CodecVorbis::Process new track identified within Ogg container.\n");
                    iStreamEnded = true;
                }
            }

            TUint samples = bytes/iBytesPerSample;
            TByte* dstByte = const_cast<TByte*>(iOutBuf.Ptr()) + iOutBuf.Bytes();
            TInt16* dst = reinterpret_cast<TInt16*>(dstByte);
            BigEndian(dst, (TInt16 *)pcm, samples);
            iOutBuf.SetBytes(iOutBuf.Bytes()+bytes);
            iTotalSamplesOutput += samples;

            LOG(kCodec, "CodecVorbis::Process read - bytes %d, iPrevBytes %d\n", bytes, iPrevBytes);
            if (iOutBuf.MaxBytes() - iOutBuf.Bytes() < (TUint)((iBitDepth/8) * iChannels)) {
                iTrackOffset += iController->OutputAudioPcm(iOutBuf, iChannels, iSampleRate,
                    iBitDepth, EMediaDataBigEndian, iTrackOffset);
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
                iBitDepth, EMediaDataBigEndian, iTrackOffset);
            iOutBuf.SetBytes(0);
        }
        if (iNewStreamStarted) {
            THROW(CodecStreamStart);
        }
        THROW(CodecStreamEnded);
    }
}
