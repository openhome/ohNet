#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <FLAC/format.h>
#include <FLAC/stream_decoder.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/MimeTypeList.h>

#include <algorithm>
#include <string.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecFlac : public CodecBase
{
    static const TUint kMaxOutputChannels;
public:
    CodecFlac(IMimeTypeList& aMimeTypeList);
    ~CodecFlac();
private: // from CodecBase
    TBool Recognise(const EncodedStreamInfo& aStreamInfo);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
public:
    FLAC__StreamDecoderReadStatus CallbackRead(const FLAC__StreamDecoder* aDecoder,
                                               TUint8 aBuffer[],  TUint* aBytes);
    FLAC__StreamDecoderSeekStatus CallbackSeek(const FLAC__StreamDecoder* aDecoder,
                                               TUint64 aOffsetBytes);
    FLAC__StreamDecoderTellStatus CallbackTell(const FLAC__StreamDecoder* aDecoder,
                                               TUint64* aOffsetBytes);
    FLAC__StreamDecoderLengthStatus CallbackLength(const FLAC__StreamDecoder* aDecoder,
                                                   TUint64* aStreamBytes);
    TBool CallbackEof(const FLAC__StreamDecoder* aDecoder);
    FLAC__StreamDecoderWriteStatus CallbackWrite(const FLAC__StreamDecoder* aDecoder,
                                                 const FLAC__Frame* aFrame,
                                                 const TInt32* const aBuffer[]);
    void CallbackMetadata(const FLAC__StreamDecoder* aDecoder,
                          const FLAC__StreamMetadata* aMetadata);

    void CallbackError(const FLAC__StreamDecoder* aDecoder,
                       FLAC__StreamDecoderErrorStatus aStatus);
private:
    TByte iBuf[DecodedAudio::kMaxBytes];
    FLAC__StreamDecoder* iDecoder;
    Brn iName;
    TUint64 iSampleStart;
    TUint64 iTrackOffset;
    TUint iSampleRate;
    TUint64 iTrackLengthJiffies;
    TBool iStreamMsgDue;
    TBool iOgg;
    TUint iStreamId;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewFlac(IMimeTypeList& aMimeTypeList)
{ // static
    return new CodecFlac(aMimeTypeList);
}



static inline CodecFlac* CodecFromClientData(void* aClientData)
{
    return reinterpret_cast<CodecFlac*>(aClientData);
}

FLAC__StreamDecoderReadStatus CallbackRead(const FLAC__StreamDecoder *aDecoder, TUint8 aBuffer[], 
                                           size_t *aBytes, void* aClientData)
{
    return CodecFromClientData(aClientData)->CallbackRead(aDecoder, aBuffer, (TUint*)aBytes);
}

FLAC__StreamDecoderSeekStatus CallbackSeek(const FLAC__StreamDecoder* aDecoder,
                                           TUint64 aOffsetBytes, void* aClientData)
{
    return CodecFromClientData(aClientData)->CallbackSeek(aDecoder, aOffsetBytes);
}

FLAC__StreamDecoderTellStatus CallbackTell(const FLAC__StreamDecoder* aDecoder,
                                           TUint64* aOffsetBytes, void* aClientData)
{
    return CodecFromClientData(aClientData)->CallbackTell(aDecoder, aOffsetBytes);
}

FLAC__StreamDecoderLengthStatus CallbackLength(const FLAC__StreamDecoder* aDecoder,
                                               TUint64* aStreamBytes, void* aClientData)
{
    return CodecFromClientData(aClientData)->CallbackLength(aDecoder, aStreamBytes);
}

FLAC__bool CallbackEof(const FLAC__StreamDecoder* aDecoder, void* aClientData)
{
    return CodecFromClientData(aClientData)->CallbackEof(aDecoder);
}

FLAC__StreamDecoderWriteStatus CallbackWrite(const FLAC__StreamDecoder *aDecoder,
                                             const FLAC__Frame* aFrame,
                                             const FLAC__int32* const aBuffer[],
                                             void* aClientData)
{
    return CodecFromClientData(aClientData)->CallbackWrite(aDecoder, aFrame, aBuffer);
}

void CallbackMetadata(const FLAC__StreamDecoder *aDecoder,
                      const FLAC__StreamMetadata* aMetadata,
                      void* aClientData)
{
    return CodecFromClientData(aClientData)->CallbackMetadata(aDecoder, aMetadata);
}

void CallbackError(const FLAC__StreamDecoder *aDecoder, 
    FLAC__StreamDecoderErrorStatus aStatus, void* aClientData)
{
    return CodecFromClientData(aClientData)->CallbackError(aDecoder, aStatus);
}


// CodecFlac

const TUint CodecFlac::kMaxOutputChannels = 2;

CodecFlac::CodecFlac(IMimeTypeList& aMimeTypeList)
    : CodecBase("FLAC")
    , iName("FLAC")
    , iStreamMsgDue(true)
{
    iDecoder = FLAC__stream_decoder_new();
    ASSERT(iDecoder != nullptr);
    // By default, only the STREAMINFO metadata block is returned, but let's just explicitly tell the decoder that's all we want.
    ASSERT(FLAC__stream_decoder_set_metadata_respond(iDecoder, FLAC__METADATA_TYPE_STREAMINFO));
    aMimeTypeList.Add("audio/x-flac");
}

CodecFlac::~CodecFlac()
{
    FLAC__stream_decoder_delete(iDecoder);
}

TBool CodecFlac::Recognise(const EncodedStreamInfo& aStreamInfo)
{
    if (aStreamInfo.RawPcm()) {
        return false;
    }
    Bws<42> buf;
    iController->Read(buf, buf.MaxBytes());
    const TChar* ptr = reinterpret_cast<const TChar*>(buf.Ptr());
    if(buf.Bytes() >= 4) {
        if(strncmp(ptr, "fLaC", 4) == 0) {
            iOgg = false;
            return true;
        }
        else if(strncmp(ptr, "OggS", 4) == 0) {
            if(buf.Bytes() >= 42) {
                if(strncmp(ptr+37, "fLaC", 4) == 0) {
                    iOgg = true;
                    return true;
                }
            }
        }
    }
    return false;
}

void CodecFlac::StreamInitialise()
{
    iStreamMsgDue = true;
    iSampleStart = 0;
    iTrackOffset = 0;
    iSampleRate = 0;
    iTrackLengthJiffies = 0;

    FLAC__StreamDecoderState state;
    state = FLAC__stream_decoder_get_state(iDecoder);
    // Ensure that any previous runs of the decoder were reset (via FLAC__stream_decoder_finish)
    ASSERT(state == FLAC__STREAM_DECODER_UNINITIALIZED);

    /* This next line ensures that you decode every sample correct but uses a fair amount of cpu.
       This is useful however for early testing to ensure that a new version of flac is decoding
       correctly.  Definitely should not be on in released code! */
    //FLAC__stream_decoder_set_md5_checking(iDecoder, true);

    FLAC__StreamDecoderInitStatus initState;
    if(iOgg) {
        initState= FLAC__stream_decoder_init_ogg_stream(
            iDecoder,
            ::CallbackRead,
            ::CallbackSeek,
            ::CallbackTell,
            ::CallbackLength,
            ::CallbackEof,
            ::CallbackWrite,
            ::CallbackMetadata,
            ::CallbackError,
            this);
    }
    else {
        initState = FLAC__stream_decoder_init_stream(
            iDecoder,
            ::CallbackRead,
            ::CallbackSeek,
            ::CallbackTell,
            ::CallbackLength,
            ::CallbackEof,
            ::CallbackWrite,
            ::CallbackMetadata,
            ::CallbackError,
            this);
    }

    if(initState != FLAC__STREAM_DECODER_INIT_STATUS_OK) {
        state = FLAC__stream_decoder_get_state(iDecoder);
        LOG(kError, "Flac::Initialise stream decoder init failed with: %d, state: %d\n", initState, state);
        // All flac reported errors here are unrecoverable.
        ASSERTS();
    }
}

void CodecFlac::Process()
{
    FLAC__stream_decoder_process_single(iDecoder);
    FLAC__StreamDecoderState state = FLAC__stream_decoder_get_state(iDecoder);
    switch(state) {
        case FLAC__STREAM_DECODER_SEARCH_FOR_METADATA:
        case FLAC__STREAM_DECODER_READ_METADATA:
        case FLAC__STREAM_DECODER_SEARCH_FOR_FRAME_SYNC:
        case FLAC__STREAM_DECODER_READ_FRAME:
            break;
        case FLAC__STREAM_DECODER_END_OF_STREAM:
            // we've decoded the entire stream.  Can now either return or throw CodecStreamEnded
            THROW(CodecStreamEnded);
        case FLAC__STREAM_DECODER_OGG_ERROR:
            // We don't support ogg currently, bug in code -- unrecoverable
            THROW(CodecStreamCorrupt);
            break;
        case FLAC__STREAM_DECODER_SEEK_ERROR:
            FLAC__stream_decoder_flush(iDecoder);
            //THROW(CodecStreamCorrupt);
            break;
        case FLAC__STREAM_DECODER_ABORTED:
            THROW(CodecStreamCorrupt);
            break;
        case FLAC__STREAM_DECODER_MEMORY_ALLOCATION_ERROR:
            // Bug in code -- unrecoverable
            THROW(CodecStreamCorrupt);
            break;
        case FLAC__STREAM_DECODER_UNINITIALIZED:
            // Bug in code -- unrecoverable
            THROW(CodecStreamCorrupt);
            break;
        default:
            // Mismatch in code between us and Flac, haven't covered all cases
            // --> bug --> unrecoverable
            THROW(CodecStreamCorrupt);
            break;
    }
}

TBool CodecFlac::TrySeek(TUint aStreamId, TUint64 aSample)
{
    iStreamId = aStreamId;
    iSampleStart = aSample;
    FLAC__bool ret = FLAC__stream_decoder_seek_absolute(iDecoder, aSample);
    if (ret == 0) {
        // Seeking failed.
        // Must check if decoder state is FLAC__STREAM_DECODER_SEEK_ERROR and call FLAC__stream_decoder_flush() before continuing.
        return false;
    }
    return true;
}

void CodecFlac::StreamCompleted()
{
    FLAC__stream_decoder_finish(iDecoder);
    (void)FLAC__stream_decoder_get_state(iDecoder);
}

FLAC__StreamDecoderReadStatus CodecFlac::CallbackRead(const FLAC__StreamDecoder* /*aDecoder*/,
                                                      TUint8 aBuffer[], TUint *aBytes)
{
    Bwn buf(aBuffer, *aBytes);
    try {
        iController->Read(buf, *aBytes);
        *aBytes = buf.Bytes();
        return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
    }
    catch (CodecStreamEnded&) {
        *aBytes = 0;
        return FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;
    }
    catch (CodecStreamStopped&) {
        *aBytes = 0;
        return FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;
    }
}

FLAC__StreamDecoderSeekStatus CodecFlac::CallbackSeek(const FLAC__StreamDecoder* /*aDecoder*/, TUint64 aOffsetBytes)
{
    if (!iController->TrySeekTo(iStreamId, aOffsetBytes)) {
        //return FLAC__STREAM_DECODER_SEEK_STATUS_ERROR;
        return FLAC__STREAM_DECODER_SEEK_STATUS_UNSUPPORTED;
    }
    iTrackOffset = iSampleStart * Jiffies::PerSample(iSampleRate);
    iStreamMsgDue = true;
    return FLAC__STREAM_DECODER_SEEK_STATUS_OK;
}

FLAC__StreamDecoderTellStatus CodecFlac::CallbackTell(const FLAC__StreamDecoder* /*aDecoder*/, TUint64* aOffsetBytes)
{
    TUint64 offset = iController->StreamPos();
    if(offset == 0) {
        return FLAC__STREAM_DECODER_TELL_STATUS_UNSUPPORTED;
    }
    *aOffsetBytes = offset;
    return FLAC__STREAM_DECODER_TELL_STATUS_OK;
}

FLAC__StreamDecoderLengthStatus CodecFlac::CallbackLength(const FLAC__StreamDecoder* /*aDecoder*/, TUint64* aStreamBytes)
{
    TUint64 len = iController->StreamLength();
    if(len == 0) {
        return FLAC__STREAM_DECODER_LENGTH_STATUS_UNSUPPORTED;
    }
    *aStreamBytes = len;
    return FLAC__STREAM_DECODER_LENGTH_STATUS_OK;
}

TBool CodecFlac::CallbackEof(const FLAC__StreamDecoder* /*aDecoder*/)
{
    //Log::Print("FIXME - CodecFlac::CallbackEof unimplemented\n");
    return false;
}

FLAC__StreamDecoderWriteStatus CodecFlac::CallbackWrite(const FLAC__StreamDecoder* /*aDecoder*/,
                                                        const FLAC__Frame* aFrame, 
                                                        const TInt32* const aBuffer[])
{
    const TUint channels = std::min((TUint)aFrame->header.channels,
                                    kMaxOutputChannels); /* don't want to support multi-channel
                                                            ...at least until songcast sender can downmix to stereo */
    TUint samplesToWrite = aFrame->header.blocksize;
    const TUint bitDepth = aFrame->header.bits_per_sample;
    const TUint sampleRate = aFrame->header.sample_rate;

    if (iStreamMsgDue) {
        /* If we get a Audio Frame prior to a metadata frame (and therefore
           iStreamMsgDue is still true) we must have picked up a file mid-stream.
           Therefore, put out a MsgDecodedStream on the basis of what we know mid-stream. */
        const TUint bitRate = sampleRate * bitDepth * channels;
        iController->OutputDecodedStream(bitRate, bitDepth, sampleRate, channels, iName, iTrackLengthJiffies, iSampleStart, true, DeriveProfile(channels));
        iStreamMsgDue = false;
    }
    
    const TUint bytesPerSample = (bitDepth/8) * channels;
    const TUint maxSamples = sizeof(iBuf) / bytesPerSample;
    TUint startI=0, endI;
    while (samplesToWrite > 0) {
        const TUint samples = (samplesToWrite > maxSamples? maxSamples : samplesToWrite);
        TByte* p = iBuf;
        endI = startI + samples;
        for (TUint i=startI; i<endI; i++) {
            for (TUint j=0; j<channels; j++) {
                TUint subsample = aBuffer[j][i];
                // pipeline audio data is big endian so we might as well convert to that here
                switch (bitDepth)
                {
                case 8:
                    *p++ = (TByte)subsample;
                    break;
                case 16:
                    *p++ = (TByte)(subsample >> 8);
                    *p++ = (TByte)subsample;
                    break;
                case 24:
                    *p++ = (TByte)(subsample >> 16);
                    *p++ = (TByte)(subsample >> 8);
                    *p++ = (TByte)subsample;
                    break;
                default:
                    Log::Print("Unsupported bit depth in CodecFlac::CallbackWrite - %u\n", bitDepth);
                    THROW(CodecStreamFeatureUnsupported);
                }
            }
        }
        const TUint bytes = samples * bytesPerSample;
        Brn encodedAudio(iBuf, bytes);
        iTrackOffset += iController->OutputAudioPcm(encodedAudio, channels, sampleRate,
                                                    bitDepth, AudioDataEndian::Big, iTrackOffset);
        samplesToWrite -= samples;
        startI = endI;
    }

    return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

void CodecFlac::CallbackError(const FLAC__StreamDecoder * /*aDecoder*/,
                              FLAC__StreamDecoderErrorStatus /*aStatus*/)
{
    THROW(CodecStreamCorrupt);
}

void CodecFlac::CallbackMetadata(const FLAC__StreamDecoder * /*aDecoder*/,
                                 const FLAC__StreamMetadata* aMetadata)
{
    ASSERT(aMetadata->type == FLAC__METADATA_TYPE_STREAMINFO);
    const FLAC__StreamMetadata_StreamInfo* streamInfo = &aMetadata->data.stream_info;

    iSampleRate = streamInfo->sample_rate;
    const TUint bitRate = iSampleRate * streamInfo->bits_per_sample * streamInfo->channels;
    iTrackLengthJiffies = (streamInfo->total_samples * Jiffies::kPerSecond) / iSampleRate;
    const TUint channels = std::min((TUint)streamInfo->channels,
                                    kMaxOutputChannels); /* don't want to support multi-channel
                                                            ...at least until songcast sender can downmix to stereo */

    iController->OutputDecodedStream(bitRate, streamInfo->bits_per_sample, iSampleRate, channels, iName, iTrackLengthJiffies, iSampleStart, true, DeriveProfile(channels));
    iStreamMsgDue = false;
}
