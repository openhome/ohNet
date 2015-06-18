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
    , iContainer(NULL)
    , alac(NULL)
{
    LOG(kCodec, "CodecAlacBase::CodecAlacBase\n");
}

CodecAlacBase::~CodecAlacBase()
{
    LOG(kCodec, "CodecAlacBase::~CodecAlacBase\n");
    alac_free_buffers(alac);
    alac = NULL;
    if (iContainer) {   // clean up in case not terminating under normal conditions
        delete iContainer;
        iContainer = NULL;
    }
}

void CodecAlacBase::Initialise()
{
#ifdef DEFINE_BIG_ENDIAN
    host_bigendian = true; // used within decode_frame()
#else
    host_bigendian = false;
#endif
    LOG(kCodec, "CodecAlacBase::Initialise\n");

    // iContainer must have been initialised in a derived class
    ASSERT(iContainer);

    iStreamStarted = iStreamEnded = false;
    iInBuf.SetBytes(0);
    iDecodedBuf.SetBytes(0);
    iOutBuf.SetBytes(0);

    alac = create_alac(iContainer->BitDepth(), iContainer->Channels());

    // We initialised codec-specific data in the recognise function.
    Bws<64> info;
    info.SetBytes(20);                          // first 20 bytes are ignored by decoder
    info.Append(iContainer->CodecSpecificData());            // add data extracted from MPEG-4 header
    alac_set_info(alac, (char*)info.Ptr());     // configure decoder

    iBitDepth = iContainer->BitDepth();
    iBytesPerSample = iContainer->Channels()*iContainer->BitDepth()/8;
    iCurrentSample = 0;
    iSamplesWrittenTotal = 0;

    iTrackLengthJiffies = (iContainer->Duration() * Jiffies::kPerSecond) / iContainer->Timescale();
    iTrackOffset = 0;

    LOG(kCodec, "CodecAlacBase::StreamInitialise  iBitDepth %u, iTimeScale: %u, iSampleRate: %u, iSamplesTotal %llu, iChannels %u, iTrackLengthJiffies %u\n", iContainer->BitDepth(), iContainer->Timescale(), iContainer->SampleRate(), iContainer->Duration(), iContainer->Channels(), iTrackLengthJiffies);
    iController->OutputDecodedStream(0, iContainer->BitDepth(), iContainer->Timescale(), iContainer->Channels(), kCodecAlac, iTrackLengthJiffies, 0, true);
}

TBool CodecAlacBase::SupportsMimeType(const Brx& aMimeType)
{
    static const Brn kMimeAlac("audio/x-m4a");
    if (aMimeType == kMimeAlac) {
        return true;
    }
    return false;
}

TBool CodecAlacBase::TrySeek(TUint /*aStreamId*/, TUint64 /*aSample*/)
{
    return false;
}

void CodecAlacBase::StreamCompleted()
{
    LOG(kCodec, "CodecAlacBase::StreamCompleted\n");

    // free all malloc'ed buffers
    alac_free_buffers(alac);
    alac = NULL;
    if (iContainer) {
        delete iContainer;
        iContainer = NULL;
    }
}

void CodecAlacBase::BigEndianData(TUint aToWrite, TUint aSamplesWritten)
{
    // Alac decoder outputs in little endian.
    TByte* dst = const_cast<TByte*>(iOutBuf.Ptr()) + iOutBuf.Bytes();
    TByte* src = const_cast<TByte*>(iDecodedBuf.Ptr()) + (aSamplesWritten * iBytesPerSample);

    TUint i=0;

    for (i=0 ; i<aToWrite*iContainer->Channels(); i++) {
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

    // decode sample
    int outputBytes;
    outputBytes = iDecodedBuf.MaxBytes();
    // use alac decoder to decode a frame at a time
    if (decode_frame(alac, (unsigned char*)iInBuf.Ptr(), (void*)iDecodedBuf.Ptr(), &outputBytes) == 0) {
        THROW(CodecStreamCorrupt); // decode error
    }
    iDecodedBuf.SetBytes(outputBytes);
    //LOG(kCodec, "CodecAlacBase::Process  decoded output %d\n", outputBytes);

    // output samples
    TUint samplesToWrite = iDecodedBuf.Bytes()/iBytesPerSample;
    TUint samplesWritten = 0;
    while (samplesToWrite > 0) {
        TUint bytes = samplesToWrite * (iBitDepth/8) * iContainer->Channels();
        TUint samples = samplesToWrite;
        TUint outputSpace = iOutBuf.MaxBytes() - iOutBuf.Bytes();
        if (bytes > outputSpace) {
            samples = outputSpace / (iContainer->Channels() * (iBitDepth/8));
            bytes = samples * (iBitDepth/8) * iContainer->Channels();
        }
        BigEndianData(samples, samplesWritten);
        iOutBuf.SetBytes(iOutBuf.Bytes() + bytes);
        if (iOutBuf.MaxBytes() - iOutBuf.Bytes() < (TUint)(iBitDepth/8) * iContainer->Channels()) {
            iTrackOffset += iController->OutputAudioPcm(iOutBuf, iContainer->Channels(), iContainer->Timescale(),
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
        // flush remaining samples
        if (iOutBuf.Bytes() > 0) {
            iTrackOffset += iController->OutputAudioPcm(iOutBuf, iContainer->Channels(), iContainer->Timescale(),
                iBitDepth, EMediaDataEndianBig, iTrackOffset);
            iOutBuf.SetBytes(0);
        }
        if (iStreamStarted) {
            THROW(CodecStreamStart);
        }
        THROW(CodecStreamEnded);
    }
}
