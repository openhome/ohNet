#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Printer.h>

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

class CodecVorbis : public CodecBase
{
public:
    static const Brn kCodecVorbis;
public:
    CodecVorbis();
    ~CodecVorbis();
private: // from CodecBase
    TBool Recognise(const Brx& aData);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
public:
    size_t ReadCallback(void *ptr, size_t size, size_t nmemb);
    int SeekCallback(ogg_int64_t offset, int whence);
    int CloseCallback();
    long TellCallback();
    void PrintCallback(char *message);
private:
    void BigEndian(TInt16* aDst, TInt16* aSrc, TUint aSamples);
    void FlushOutput();

    ov_callbacks iCallbacks;

    void *iDataSource; // dummy stream identifier
    OggVorbis_File iVf;
    vorbis_info* iInfo;

    Bws<EncodedAudio::kMaxBytes> iRecogBuf;
    Bws<DecodedAudio::kMaxBytes> iInBuf;
    Bws<DecodedAudio::kMaxBytes> iOutBuf;
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
    TBool iRecognising;
    TUint64 iPeekOffset;
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



const Brn CodecVorbis::kCodecVorbis("vorbis");

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
        if(iRecognising) {
            ASSERT(iRecogBuf.Bytes() > 0);  // check buffer has been initialised
            if ((iRecogBuf.Bytes() < iPeekOffset) || (iRecogBuf.Bytes()-iPeekOffset < bytes)) {
                // our buffer is incorrectly sized (programmer error)
                // OR we've exhausted the recognise buffer and still not recognised stream,
                // so probably not a valid Vorbis stream
                //ASSERTS();
                buf.SetBytes(0);
            }
            else {
                //LOG(kCodec,"CodecVorbis::CallbackRead: buf.Bytes: %u, iPeekOffset: %u, bytes: %u\n", buf.Bytes(), iPeekOffset, bytes);
                Brn tmpBuf = iRecogBuf.Split(static_cast<TUint>(iPeekOffset), bytes);
                buf.Replace(tmpBuf);
                iPeekOffset += bytes;
            }
        }
        else {
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
    if(iRecognising) {
        tell = iPeekOffset;
    }
    else {
        tell = iController->StreamPos();
    }
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
    : iRecognising(false)
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


TBool CodecVorbis::Recognise(const Brx& aData)
{
    LOG(kCodec, "CodecVorbis::Recognise\n");

    iPeekOffset = 0;
    iRecognising = true;
    iSamplesTotal = 0;
    ASSERT(aData.Bytes() <= EncodedAudio::kMaxBytes); // check we don't try overflow the buffer capacity
    iRecogBuf.Replace(aData);

    TBool isVorbis = (ov_open_callbacks(iDataSource, &iVf, NULL, 0, iCallbacks) == 0);

    iRecognising = false;
    iRecogBuf.SetBytes(0);

    return isVorbis;
}

void CodecVorbis::StreamInitialise()
{
    LOG(kCodec, "CodecVorbis::StreamInitialise\n");
    iLink = 0;
    iStreamEnded = false;
    iNewStreamStarted = false;

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

    if (iController->StreamLength()) {
        iSamplesTotal = iSampleRate * iController->StreamLength() / iBytesPerSec; // estimate from average bitrate and file size
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
