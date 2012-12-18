#include <OpenHome/Media/Codec/Flac.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <FLAC/stream_decoder.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

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

CodecFlac::CodecFlac() 
    : iName("FLAC")
    , iMsgFormatSent(false)
{
    iDecoder = FLAC__stream_decoder_new();
    ASSERT(iDecoder != NULL);
}

CodecFlac::~CodecFlac()
{
    FLAC__stream_decoder_delete(iDecoder);
}

TBool CodecFlac::Recognise(const Brx& aMsg)
{
    const TChar* ptr = reinterpret_cast<const TChar*>(aMsg.Ptr());
    if(aMsg.Bytes() >= 4) {
        if(strncmp(ptr, "fLaC", 4) == 0) {
            iOgg = false;
            return true;
        }
        else if(strncmp(ptr, "OggS", 4) == 0) {
            if(aMsg.Bytes() >= 42) {
                if(strncmp(ptr+37, "fLaC", 4) == 0) {
                    iOgg = true;
                    return true;
                }
            }
        }
    }
    return false;
}

void CodecFlac::Initialise()
{
    iMsgFormatSent = false;
    iTrackOffset = 0;
    
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

    while(!iMsgFormatSent) {
		// Decode until the streaminfo metadata block or an audio frame are found, both of which put out the Soa.
    	// There may be other metadata types decoded first, eg picture metadata, which will be ignored.
		if(!FLAC__stream_decoder_process_single(iDecoder)) {
			state = FLAC__stream_decoder_get_state(iDecoder);
			LOG(kError, "Flac::Initialise failed to get metadata or decode anything, decoder state: %d\n", state);
			ASSERTS();
		}
    }
}

void CodecFlac::Process()
{
    Initialise();

    for (;;) {
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
                return;
            case FLAC__STREAM_DECODER_OGG_ERROR:
                // We don't support ogg currently, bug in code -- unrecoverable
                THROW(CodecStreamCorrupt);
                break;
            case FLAC__STREAM_DECODER_SEEK_ERROR:
                /* Is this recoverable?  throw here?  How is this different to
                   seek_absolute returning false? -- see comments above
                   (Flac::Seek())about throwing in the middle of seeks */
                THROW(CodecStreamCorrupt);
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
    iController->Read(buf, *aBytes);
    *aBytes = buf.Bytes();
    return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
}

FLAC__StreamDecoderSeekStatus CodecFlac::CallbackSeek(const FLAC__StreamDecoder* /*aDecoder*/, TUint64 /*aOffsetBytes*/)
{
    return FLAC__STREAM_DECODER_SEEK_STATUS_UNSUPPORTED;
}

FLAC__StreamDecoderTellStatus CodecFlac::CallbackTell(const FLAC__StreamDecoder* /*aDecoder*/, TUint64* /*aOffsetBytes*/)
{
    return FLAC__STREAM_DECODER_TELL_STATUS_UNSUPPORTED;
}

FLAC__StreamDecoderLengthStatus CodecFlac::CallbackLength(const FLAC__StreamDecoder* /*aDecoder*/,
                                                          TUint64* /*aStreamBytes*/)
{
    return FLAC__STREAM_DECODER_LENGTH_STATUS_UNSUPPORTED;
}

TBool CodecFlac::CallbackEof(const FLAC__StreamDecoder* /*aDecoder*/)
{
    return false;
}

FLAC__StreamDecoderWriteStatus CodecFlac::CallbackWrite(const FLAC__StreamDecoder* /*aDecoder*/,
                                                        const FLAC__Frame* aFrame, 
                                                        const TInt32* const aBuffer[])
{
    const TUint channels = aFrame->header.channels;
    TUint samplesToWrite = aFrame->header.blocksize;
    const TUint bitDepth = aFrame->header.bits_per_sample;
    const TUint sampleRate = aFrame->header.sample_rate;

    if (!iMsgFormatSent) {
        /* If we get a Audio Frame prior to a metadata frame (and therefore
           iMsgFormatSent is still false) we must have picked up a file mid-stream.
           Therefore, put out a MsgAudioFormat on the basis of what we know mid-stream. */
        const TUint bitRate = sampleRate * bitDepth * channels;
        MsgAudioFormat* format = iMsgFactory->CreateMsgAudioFormat(bitRate, bitDepth, sampleRate,
                                                                   channels, iName, 0, true);
        iController->Output(format);
        iMsgFormatSent = true;
    }
    
    const TUint maxSamples = sizeof(iBuf) / ((bitDepth/8) * channels);
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
                    ASSERTS();
                }
            }
        }
        const TUint bytes = samples * (bitDepth/8) * channels;
        Brn encodedAudio(iBuf, bytes);
        MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudio, channels, sampleRate,
                                                            bitDepth, EMediaDataBigEndian, iTrackOffset);
        iTrackOffset += audio->Jiffies();
        iController->Output(audio);
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
    ASSERT(!iMsgFormatSent);
    const FLAC__StreamMetadata_StreamInfo* streamInfo = &aMetadata->data.stream_info;

    const TUint bitRate = streamInfo->sample_rate * streamInfo->bits_per_sample * streamInfo->channels;
    const TUint64 trackLengthJiffies = (streamInfo->total_samples * Jiffies::kJiffiesPerSecond) / streamInfo->sample_rate;

    MsgAudioFormat* format = iMsgFactory->CreateMsgAudioFormat(bitRate, streamInfo->bits_per_sample,
                                                               streamInfo->sample_rate, streamInfo->channels,
                                                               iName, trackLengthJiffies, true);
    iController->Output(format);
    iMsgFormatSent = true;
}
