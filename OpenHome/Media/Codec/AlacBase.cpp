#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/AlacBase.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>

extern "C" {
int host_bigendian;     // used by alac.c
}


using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;


// CodecAlacBase

const Brn CodecAlacBase::kCodecAlac("ALAC");

CodecAlacBase::CodecAlacBase(const TChar* aId)
    : CodecBase(aId)
    , alac(nullptr)
{
    LOG(kCodec, "CodecAlacBase::CodecAlacBase\n");
}

CodecAlacBase::~CodecAlacBase()
{
    LOG(kCodec, "CodecAlacBase::~CodecAlacBase\n");
    alac_free_buffers(alac);
    alac = nullptr;
}

void CodecAlacBase::Initialise()
{
#ifdef DEFINE_BIG_ENDIAN
    host_bigendian = true; // used within decode_frame()
#else
    host_bigendian = false;
#endif
    LOG(kCodec, "CodecAlacBase::Initialise\n");

    iStreamStarted = iStreamEnded = false;
    iInBuf.SetBytes(0);
    iDecodedBuf.SetBytes(0);
    iOutBuf.SetBytes(0);
    iTrackOffset = 0;
}

TBool CodecAlacBase::TrySeek(TUint /*aStreamId*/, TUint64 /*aSample*/)
{
    return false;
}

void CodecAlacBase::StreamCompleted()
{
    LOG(kCodec, "CodecAlacBase::StreamCompleted\n");
    // Free all malloc'ed buffers.
    alac_free_buffers(alac);
    alac = nullptr;
}

void CodecAlacBase::BigEndianData(TUint aToWrite, TUint aSamplesWritten)
{
    // Alac decoder outputs in little endian.
    TByte* dst = const_cast<TByte*>(iOutBuf.Ptr()) + iOutBuf.Bytes();
    TByte* src = const_cast<TByte*>(iDecodedBuf.Ptr()) + (aSamplesWritten * iBytesPerSample);

    TUint i=0;

    for (i=0 ; i<aToWrite*iChannels; i++) {
        switch (iBitDepth) {
        case 8:
            *dst++ = *src++;
            break;
        case 16:
            *dst++ = src[1];
            *dst++ = src[0];
            src += 2;
            break;
        case 24:
            *dst++ = src[2];
            *dst++ = src[1];
            *dst++ = src[0];
            src += 3;
            break;
        default:
            ASSERTS();
        }
    }
}

void CodecAlacBase::Decode() 
{
    //LOG(kCodec, "CodecAlacBase::Process\n");

    // Decode sample.
    TInt outputBytes = iDecodedBuf.MaxBytes();
    // Use alac decoder to decode a frame at a time.
    if (decode_frame(alac, (unsigned char*)iInBuf.Ptr(), (void*)iDecodedBuf.Ptr(), (int*)&outputBytes) == 0) {
        THROW(CodecStreamCorrupt); // Decode error.
    }
    iDecodedBuf.SetBytes(outputBytes);
    //LOG(kCodec, "CodecAlacBase::Process  decoded output %d\n", outputBytes);

    // Output samples.
    TUint samplesToWrite = iDecodedBuf.Bytes()/iBytesPerSample;
    TUint samplesWritten = 0;
    while (samplesToWrite > 0) {
        TUint bytes = samplesToWrite * (iBitDepth/8) * iChannels;
        TUint samples = samplesToWrite;
        TUint outputSpace = iOutBuf.MaxBytes() - iOutBuf.Bytes();
        if (bytes > outputSpace) {
            samples = outputSpace / (iChannels * (iBitDepth/8));
            bytes = samples * (iBitDepth/8) * iChannels;
        }
        BigEndianData(samples, samplesWritten);
        iOutBuf.SetBytes(iOutBuf.Bytes() + bytes);
        if (iOutBuf.MaxBytes() - iOutBuf.Bytes() < (TUint)(iBitDepth/8) * iChannels) {
            iTrackOffset += iController->OutputAudioPcm(iOutBuf, iChannels, iSampleRate,
                iBitDepth, EMediaDataEndianBig, iTrackOffset);
            iOutBuf.SetBytes(0);
        }
        samplesToWrite -= samples;
        samplesWritten += samples;
        iSamplesWrittenTotal += samples;
        //LOG(kCodec, "CodecAlacBase::iSamplesWrittenTotal: %llu\n", iSamplesWrittenTotal);
    }
}

void CodecAlacBase::OutputFinal()
{
    if (iStreamStarted || iStreamEnded) {
        // Flush remaining samples.
        if (iOutBuf.Bytes() > 0) {
            iTrackOffset += iController->OutputAudioPcm(iOutBuf, iChannels, iSampleRate,
                iBitDepth, EMediaDataEndianBig, iTrackOffset);
            iOutBuf.SetBytes(0);
        }
        if (iStreamStarted) {
            THROW(CodecStreamStart);
        }
        THROW(CodecStreamEnded);
    }
}
