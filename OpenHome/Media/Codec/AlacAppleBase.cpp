#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/AlacAppleBase.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>

#include <ALACDecoder.h>
#include <ALACBitUtilities.h>


using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;


// CodecAlacAppleBase

const Brn CodecAlacAppleBase::kCodecAlac("ALAC");

CodecAlacAppleBase::CodecAlacAppleBase(const TChar* aId)
    : CodecBase(aId)
{
    LOG(kCodec, "CodecAlacAppleBase::CodecAlacAppleBase\n");
}

CodecAlacAppleBase::~CodecAlacAppleBase()
{
    LOG(kCodec, "CodecAlacAppleBase::~CodecAlacAppleBase\n");
}

void CodecAlacAppleBase::Initialise()
{
    LOG(kCodec, "CodecAlacAppleBase::Initialise\n");

    iInBuf.SetBytes(0);
    iDecodedBuf.SetBytes(0);
    iTrackOffset = 0;
}

TBool CodecAlacAppleBase::TrySeek(TUint /*aStreamId*/, TUint64 /*aSample*/)
{
    return false;
}

void CodecAlacAppleBase::StreamCompleted()
{
    LOG(kCodec, "CodecAlacAppleBase::StreamCompleted\n");
}

void CodecAlacAppleBase::Decode() 
{
    //LOG(kCodec, "CodecAlacAppleBase::Process\n");

    // Decode samples.
    TUint outSamples = 0;
    BitBuffer bitBuffer;
    BitBufferInit(&bitBuffer, (uint8_t*)iInBuf.Ptr(), iInBuf.Bytes());

    // Use alac decoder to decode a frame at a time.
    TUint status = iDecoder.Decode(&bitBuffer, (uint8_t*)iDecodedBuf.Ptr(), iDecoder.mConfig.frameLength, iDecoder.mConfig.numChannels, &outSamples);
    if (status != ALAC_noErr) {
        LOG(kCodec, "CodecAlacAppleBase::Decode third-party decoder error. status: %d\n", status);
        THROW(CodecStreamCorrupt);
    }

    iDecodedBuf.SetBytes(outSamples*(iDecoder.mConfig.bitDepth/8)*iDecoder.mConfig.numChannels);
    //LOG(kCodec, "CodecAlacAppleBase::Process  iDecodedBuf.Bytes(): %u\n", iDecodedBuf.Bytes());

    // Output all samples, as will probably fill full iDecodedBuf on next decode.
    TUint idx = 0;
    TUint samplesToWrite = iDecodedBuf.Bytes()/iBytesPerSample;
    while (samplesToWrite > 0) {
        TUint bytesToOutput = DecodedAudio::kMaxBytes;
        Brn out;
        if (iDecodedBuf.Bytes()-idx < bytesToOutput) {
            bytesToOutput = iDecodedBuf.Bytes()-idx;
        }
        out.Set(iDecodedBuf.Ptr()+idx, bytesToOutput);
        TUint samplesOut = bytesToOutput/iBytesPerSample;

        iTrackOffset += iController->OutputAudioPcm(out, iChannels, iSampleRate, iBitDepth, Endianness(), iTrackOffset);

        idx += out.Bytes();
        out.Set(Brx::Empty());
        samplesToWrite -= samplesOut;
        iSamplesWrittenTotal += samplesOut;
    }
    iDecodedBuf.SetBytes(0);
}

EMediaDataEndian CodecAlacAppleBase::Endianness()
{
    // Apple's ALAC implementation outputs samples in platform endianness, so
    // use this to select correct endianness.
#ifdef DEFINE_BIG_ENDIAN
    return EMediaDataEndian::EMediaDataEndianBig;
#else
    return EMediaDataEndian::EMediaDataEndianLittle;
#endif
}
