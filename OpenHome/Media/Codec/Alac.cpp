#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Media/Protocol/ProtocolRaop.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Av/Debug.h>

extern "C"{
#include <decomp.h>
int host_bigendian;     // used by alac.c
}

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecAlac : public CodecBase
{
public:
    static const Brn kCodecAlac;
public:
    CodecAlac();
    ~CodecAlac();
private: // from CodecBase
    TBool Recognise(const Brx& aData);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private:
    void BigEndianData(TUint toWrite, TUint aSamplesWritten);
private:
    Bws<4*10240> iInBuf;          // how big can these go and need to go ?
    Bws<16*10240> iDecodedBuf;
    Bws<DecodedAudio::kMaxBytes> iOutBuf;
    Mpeg4MediaInfoBase* iContainer;
    Mpeg4MediaInfo* iMp4;
    alac_file *alac;

    TUint16 iBitDepth;      // alac decoder may redefine the bit depth
    TUint16 iBytesPerSample;
    TUint64 iCurrentSample;
    TUint64 iSamplesWrittenTotal;
    TUint64 iTrackLengthJiffies;
    TUint64 iTrackOffset;
    TBool iAirplay;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewAlac()
{ // static
    return new CodecAlac();
}



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
    iAirplay = false;

    if(aData.Bytes() >= 4) {
        Bws<4> identifier(aData.Ptr(), 4);
        if(identifier == Brn("Raop")) {
            LOG(kCodec, "CodecAlac::Recognise airplay\n");
            iAirplay = true;
            return true;
        }
    }

    try {
        Mpeg4MediaInfo::GetCodec(aData, codec);
    }
    catch (MediaMpeg4FileInvalid) {
        // We couldn't recognise this as an MPEG4/ALAC file.
        return false;
    }

    if (codec == kCodecAlac) {
        LOG(kCodec, "CodecAlac::Recognise alac\n");
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

    if (iAirplay) {
        iContainer = new Mpeg4MediaInfoBase(*iController);
        alac = create_alac(iContainer->BitDepth(), iContainer->Channels());

        // fmtp parsing is partially duplicated in RaopContainer() - rationalise - ToDo
        Parser fmtp(iContainer->CodecSpecificData());

        Bws<Mpeg4MediaInfoBase::kMaxCSDSize> csdBuf;
        try {
            // pack fmtp data into the format required for alac_sent_info
            csdBuf.SetBytes(20);
            csdBuf.Append(Arch::BigEndian4(Ascii::Uint(fmtp.Next())));   // first number is ignored
            csdBuf.Append(Arch::BigEndian4(Ascii::Uint(fmtp.Next())));
            csdBuf.Append(static_cast<TUint8>(Ascii::Uint(fmtp.Next())));
            csdBuf.Append(static_cast<TUint8>(Ascii::Uint(fmtp.Next()))); // in bits
            csdBuf.Append(static_cast<TUint8>(Ascii::Uint(fmtp.Next())));
            csdBuf.Append(static_cast<TUint8>(Ascii::Uint(fmtp.Next())));
            csdBuf.Append(static_cast<TUint8>(Ascii::Uint(fmtp.Next())));
            csdBuf.Append(static_cast<TUint8>(Ascii::Uint(fmtp.Next())));
            csdBuf.Append(static_cast<TUint16>(Ascii::Uint(fmtp.Next())));
            csdBuf.Append(Arch::BigEndian4(Ascii::Uint(fmtp.Next()))); // max sample size??
            csdBuf.Append(Arch::BigEndian4(Ascii::Uint(fmtp.Next()))); // bit rate (average)??
            csdBuf.Append(Arch::BigEndian4(Ascii::Uint(fmtp.NextLine())));
        }
        catch(AsciiError) {
            THROW(CodecStreamCorrupt);
        }

        alac_set_info(alac, (char*)csdBuf.Ptr());        // configure decoder with airplay specific defaults
    }
    else {
        iMp4 = new Mpeg4MediaInfo(*iController);
        iContainer = iMp4;
        alac = create_alac(iContainer->BitDepth(), iContainer->Channels());

        // We initialised codec-specific data in the recognise function.
        Bws<64> info;
        info.SetBytes(20);                          // first 20 bytes are ignored by decoder
        info.Append(iContainer->CodecSpecificData());            // add data extracted from MPEG-4 header
        alac_set_info(alac, (char*)info.Ptr());     // configure decoder
    }

    iBitDepth = iContainer->BitDepth();
    //iBitDepth = alac->setinfo_sample_size;         // sample size may be re-defined in the codec specific data in the MPEG4 header
    iBytesPerSample = iContainer->Channels()*iContainer->BitDepth()/8;
    iCurrentSample = 0;
    iSamplesWrittenTotal = 0;

    iTrackLengthJiffies = (iContainer->Duration() * Jiffies::kJiffiesPerSecond) / iContainer->SampleRate();
    iTrackOffset = 0;

    //LOG(kCodec, "CodecAlac::StreamInitialise  iBitDepth %u, iSampleRate: %u, iSamplesTotal %llu, iChannels %u, iTrackLengthJiffies %u\n", iBitDepth, iContainer->SampleRate(), iContainer->Duration(), iContainer->Channels(), iTrackLengthJiffies);
    iController->OutputDecodedStream(0, iBitDepth, iContainer->SampleRate(), iContainer->Channels(), kCodecAlac, iTrackLengthJiffies, 0, true);
}

TBool CodecAlac::TrySeek(TUint aStreamId, TUint64 aSample)
{
    //LOG(kCodec, "CodecAlac::TrySeek(%lld)\n", aSample);
    if (!iAirplay) {
        TUint64 startSample = 0;
        TUint64 bytes = iMp4->GetSeekTable().Offset(aSample, startSample);     // find file offset relating to given audio sample
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
    else {
        return false;
    }
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
            for(i=0 ; i<aToWrite*iContainer->Channels(); i++) {
                *dst++ = *src++;
            }
            break;
        case 16:
            for(i=0 ; i<aToWrite*iContainer->Channels(); i++) {
                *dst++ = src[1];
                *dst++ = src[0];
                src += 2;
            }
            break;
        case 24:
            for(i=0 ; i<aToWrite*iContainer->Channels(); i++) {
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

    if (iAirplay || iCurrentSample < iMp4->GetSampleSizeTable().Count()) {
        // read in a single alac sample
        iInBuf.SetBytes(0);

        if (iAirplay) { // processing airplay stream
            Bws<sizeof(RaopDataHeader)> binheader;
            iController->Read(binheader, sizeof(RaopDataHeader));   // extract header

            Brn audio(binheader);

            RaopDataHeader header(audio);
            //latency = header.Latency();
            //senderSkew = header.SenderSkew();
            //timestamp = header.Timestamp();
            //mute = header.Mute();
            iController->Read(iInBuf, header.Bytes());
        }
        else {          // processing normal alac stream
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
                iTrackOffset += iController->OutputAudioPcm(iOutBuf, iContainer->Channels(), iContainer->SampleRate(),
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
            iTrackOffset += iController->OutputAudioPcm(iOutBuf, iContainer->Channels(), iContainer->SampleRate(),
                iBitDepth, EMediaDataBigEndian, iTrackOffset);
            iOutBuf.SetBytes(0);
    }
        if (newStreamStarted) {
            THROW(CodecStreamStart);
        }
        THROW(CodecStreamEnded);
    }
}
