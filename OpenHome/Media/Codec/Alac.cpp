#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/Codec/Alac.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>

#include <stream.h>
#include <demux.h>
#include <decomp.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

int host_bigendian;     // used by alac.c


const Brn CodecAlac::kCodecAlac("alac");

CodecAlac::CodecAlac() 
    : iMp4(NULL)
{
    //LOG(kCodec, "CodecAlac::CodecAlac\n");
}

CodecAlac::~CodecAlac()
{
    //LOG(kCodec, "CodecAlac::~CodecAlac\n");
    if (iMp4) {
        delete iMp4;
    }
}

TBool CodecAlac::Recognise(const Brx& aData)
{
    //LOG(kCodec, "CodecAlac::Recognise\n");
    Bws<4> codec;

    try {
        Mpeg4MediaInfo::GetCodec(aData, codec);
    }
    catch (MediaMpeg4FileInvalid) {
        // We couldn't recognise this as an MPEG4/ALAC file.
        return false;
    }

    if (codec == kCodecAlac) {
        //LOG(kCodec, "CodecAlac::Recognise alac\n");
        return true;
    }
    return false;
}

void CodecAlac::StreamInitialise()
{
    //LOG(kCodec, "CodecAlac::StreamInitialise\n");
#ifdef DEFINE_BIG_ENDIAN
    host_bigendian = true; // used within decode_frame()
#else
    host_bigendian = false;
#endif

    iInBuf.SetBytes(0);
    iDecodedBuf.SetBytes(0);
    iOutBuf.SetBytes(0);

    iMp4 = new Mpeg4MediaInfo(*iController);
    alac = create_alac(iMp4->BitDepth(), iMp4->Channels());

    // We initialised codec-specific data in the recognise function.
    Bws<64> info;
    info.SetBytes(20);                          // first 20 bytes are ignored by decoder
    info.Append(iMp4->CodecSpecificData());            // add data extracted from MPEG-4 header
    alac_set_info(alac, (char*)info.Ptr());     // configure decoder

    iBitDepth = alac_sample_size(alac);         // sample size may be re-defined in the codec specific data in the MPEG4 header
    iBytesPerSample = iMp4->Channels()*iMp4->BitDepth()/8;
    iCurrentSample = 0;
    iSamplesWrittenTotal = 0;

    iTrackLengthJiffies = (iMp4->Duration() * Jiffies::kJiffiesPerSecond) / iMp4->SampleRate();
    iTrackOffset = 0;

    //LOG(kCodec, "CodecAlac::StreamInitialise  iBitDepth %u, iSampleRate: %u, iSamplesTotal %llu, iChannels %u, iTrackLengthJiffies %u\n", iBitDepth, iMp4->SampleRate(), iMp4->Duration(), iMp4->Channels(), iTrackLengthJiffies);
    iController->OutputDecodedStream(0, iBitDepth, iMp4->SampleRate(), iMp4->Channels(), kCodecAlac, iTrackLengthJiffies, 0, true);
}

TBool CodecAlac::TrySeek(TUint aStreamId, TUint64 aSample) 
{
    //LOG(kCodec, "CodecAlac::TrySeek(%lld)\n", aSample);
    TUint64 startSample = 0;
    TUint64 bytes = iMp4->GetSeekTable().Offset(iSamplesWrittenTotal, startSample);     // find file offset relating to given audio sample
    //LOG(kCodec, "CodecAlac::TrySeek to sample: %llu, byte: %lld\n", startSample, bytes);
    TBool canSeek = iController->TrySeek(aStreamId, bytes);
    if (canSeek) {
        iSamplesWrittenTotal = aSample;
        iCurrentSample = startSample;
        iTrackOffset = (aSample * Jiffies::kJiffiesPerSecond) / iMp4->SampleRate();
        iController->OutputDecodedStream(0, iBitDepth, iMp4->SampleRate(), iMp4->Channels(), kCodecAlac, iTrackLengthJiffies, aSample, true);
    }
    return canSeek;
}

void CodecAlac::StreamCompleted()
{
    //LOG(kCodec, "CodecAlac::StreamCompleted\n");

    // free all malloc'ed buffers
    alac_free_buffers(alac);
}

void CodecAlac::BigEndianData(TUint aToWrite, TUint aSamplesWritten)
{
    // Alac decoder outputs in little endian.
    TByte* dst = const_cast<TByte*>(iOutBuf.Ptr()) + iOutBuf.Bytes();
    TByte* src = const_cast<TByte*>(iDecodedBuf.Ptr()) + (aSamplesWritten * iBytesPerSample);

    TUint i=0;

    switch(iBitDepth) {
        case 8:
            for(i=0 ; i<aToWrite*iMp4->Channels(); i++) {
                *dst++ = *src++;
            }
            break;
        case 16:
            for(i=0 ; i<aToWrite*iMp4->Channels(); i++) {
                *dst++ = src[1];
                *dst++ = src[0];
                src += 2;
            }
            break;
        case 24:
            for(i=0 ; i<aToWrite*iMp4->Channels(); i++) {
                *dst++ = src[2];
                *dst++ = src[1];
                *dst++ = src[0];
                src += 3;
            }
            break;
        default:
            ASSERTS();
    }
}
 
void CodecAlac::Process() 
{
    //LOG(kCodec, "CodecAlac::Process\n");

    TBool newStreamStarted = false;
    TBool streamEnded = false;

    if (iCurrentSample < iMp4->GetSampleSizeTable().Count()) {
        // read in a single alac sample
        iInBuf.SetBytes(0);

        try {
            //LOG(kCodec, "CodecAlac::Process  sample = %u, size = %u, inBuf max size %u\n", iCurrentSample, iMp4->GetSampleSizeTable().SampleSize((TUint)iCurrentSample), iInBuf.MaxBytes());
            iController->Read(iInBuf, iMp4->GetSampleSizeTable().SampleSize((TUint)iCurrentSample));
            iCurrentSample++;
        }
        catch (CodecStreamStart&) {
            newStreamStarted = true;
            //LOG(kCodec, "CodecAlac::Process caught CodecStreamStart\n");
        }
        catch (CodecStreamEnded&) {
            streamEnded = true;
            //LOG(kCodec, "CodecAlac::Process caught CodecStreamEnded\n");
        }

        // decode sample
        int outputBytes;
        outputBytes = iDecodedBuf.MaxBytes();
        // use alac decoder to decode a frame at a time
        if (decode_frame(alac, (unsigned char*)iInBuf.Ptr(), (void*)iDecodedBuf.Ptr(), &outputBytes) == 0) {
            THROW(CodecStreamCorrupt); // decode error
        }
        iDecodedBuf.SetBytes(outputBytes);
        //LOG(kCodec, "CodecAlac::Process  decoded output %d\n", outputBytes);

        // output samples
        TUint samplesToWrite = iDecodedBuf.Bytes()/iBytesPerSample;
        TUint samplesWritten = 0;
        while (samplesToWrite > 0) {
            TUint bytes = samplesToWrite * (iBitDepth/8) * iMp4->Channels();
            TUint samples = samplesToWrite;
            TUint outputSpace = iOutBuf.MaxBytes() - iOutBuf.Bytes();
            if (bytes > outputSpace) {
                samples = outputSpace / (iMp4->Channels() * (iBitDepth/8));
                bytes = samples * (iBitDepth/8) * iMp4->Channels();
            }
            BigEndianData(samples, samplesWritten);
            iOutBuf.SetBytes(iOutBuf.Bytes() + bytes);
            if (iOutBuf.MaxBytes() - iOutBuf.Bytes() < (TUint)(iBitDepth/8) * iMp4->Channels()) {
                iTrackOffset += iController->OutputAudioPcm(iOutBuf, iMp4->Channels(), iMp4->SampleRate(),
                    iBitDepth, EMediaDataBigEndian, iTrackOffset);
                iOutBuf.SetBytes(0);
            }
            samplesToWrite -= samples;
            samplesWritten += samples;
            iSamplesWrittenTotal += samples;
            //LOG(kCodec, "CodecAlac::iSamplesWrittenTotal: %llu\n", iSamplesWrittenTotal);
        }
    }
    else {
        streamEnded = true;
    }

    if (newStreamStarted || streamEnded) {
        // flush remaining samples
        if (iOutBuf.Bytes() > 0) {
            iTrackOffset += iController->OutputAudioPcm(iOutBuf, iMp4->Channels(), iMp4->SampleRate(),
                iBitDepth, EMediaDataBigEndian, iTrackOffset);
            iOutBuf.SetBytes(0);
	}
        if (newStreamStarted) {
            THROW(CodecStreamStart);
        }
        THROW(CodecStreamEnded);
    }
}
