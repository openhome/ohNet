#include <OpenHome/Av/Raop/CodecRaop.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Codec/AlacBase.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Av/Raop/RaopHeader.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;
using namespace OpenHome::Av;


// CodecRaop

CodecRaop::CodecRaop() 
    : CodecAlacBase("RAOP")
{
    LOG(kCodec, "CodecRaop::CodecRaop\n");
}

CodecRaop::~CodecRaop()
{
    LOG(kCodec, "CodecRaop::~CodecRaop\n");
}

TBool CodecRaop::Recognise(const EncodedStreamInfo& aStreamInfo)
{
    LOG(kCodec, "CodecRaop::Recognise\n");
    if (aStreamInfo.RawPcm()) {
        return false;
    }
    Bws<4> buf;
    iController->Read(buf, buf.MaxBytes());

    if (buf == Brn("Raop")) {
        LOG(kCodec, "CodecRaop::Recognise airplay\n");
        return true;
    }

    return false;
}

void CodecRaop::StreamInitialise()
{
    LOG(kCodec, "CodecRaop::StreamInitialise\n");

    CodecAlacBase::Initialise();

    ProcessHeader();

    iInBuf.SetBytes(0);
    alac = create_alac(iBitDepth, iChannels);

    // FIXME - use iInBuf here instead of local stack buffer?
    Bws<IMpeg4InfoWritable::kMaxStreamDescriptorBytes> streamDescriptor;
    static const TUint kStreamDescriptorIgnoreBytes = 20; // First 20 bytes are ignored by decoder.
    streamDescriptor.SetBytes(kStreamDescriptorIgnoreBytes);
    streamDescriptor.Append(iCodecSpecificData);

    alac_set_info(alac, (char*)streamDescriptor.Ptr()); // Configure decoder.

    iBytesPerSample = iChannels*iBitDepth / 8;
    iSamplesWrittenTotal = 0;
    iTrackLengthJiffies = 0;// (iDuration * Jiffies::kPerSecond) / iTimescale;


    //LOG(kCodec, "CodecAlac::StreamInitialise  iBitDepth %u, iTimeScale: %u, iSampleRate: %u, iSamplesTotal %llu, iChannels %u, iTrackLengthJiffies %u\n", iContainer->BitDepth(), iContainer->Timescale(), iContainer->SampleRate(), iContainer->Duration(), iContainer->Channels(), iTrackLengthJiffies);
    iController->OutputDecodedStream(0, iBitDepth, iTimescale, iChannels, kCodecAlac, iTrackLengthJiffies, 0, true);
}

TBool CodecRaop::TrySeek(TUint aStreamId, TUint64 aSample)
{
    LOG(kCodec, "CodecRaop::TrySeek(%u, %llu)\n", aStreamId, aSample);
    return false;
}

void CodecRaop::StreamCompleted()
{
    LOG(kCodec, "CodecRaop::StreamCompleted\n");
    CodecAlacBase::StreamCompleted();
}

void CodecRaop::Process() 
{
    //LOG(kCodec, "CodecRaop::Process\n");
    iInBuf.SetBytes(0);

    try {
        // read in a packet worth of raop data
        Bws<sizeof(RaopDataHeader)> binheader;
        iController->Read(binheader, sizeof(RaopDataHeader));   // extract header
        if (sizeof(RaopDataHeader) > binheader.Bytes()) {
            THROW(CodecStreamEnded);
        }
        Brn audio(binheader);
        RaopDataHeader header(audio);
        iController->Read(iInBuf, header.Bytes());
        if (iInBuf.Bytes() < header.Bytes()) {
            THROW(CodecStreamEnded);
        }
        Decode();
    }
    catch (CodecStreamStart&) {
        iStreamStarted = true;
        LOG(kCodec, "CodecRaop::Process caught CodecStreamStart\n");
    }
    catch (CodecStreamEnded&) {
        iStreamEnded = true;
        LOG(kCodec, "CodecRaop::Process caught CodecStreamEnded\n");
    }

    OutputFinal();
}

void CodecRaop::ProcessHeader()
{
    LOG(kMedia, "Checking for Raop container\n");

    try {
        Bws<60> data;
        iController->Read(data, 4);

        LOG(kMedia, "data %x {", data[0]);
        LOG(kMedia, data);
        LOG(kMedia, "}\n");

        if (data != Brn("Raop")) {
            THROW(MediaCodecRaopNotFound);  // FIXME - CodecStreamCorrupt
        }

        // fmtp should hold the sdp fmtp numbers from e.g. a=fmtp:96 4096 0 16 40 10 14 2 255 0 0 44100
        // extract enough info from this for codec selector, then pass the raw fmtp through for alac decoder
        // first read the number of bytes in for the fmtp
        data.SetBytes(0);
        iController->Read(data, 4);
        TUint bytes = Ascii::Uint(data);    // size of fmtp string
        data.SetBytes(0);
        iController->Read(data, bytes);
        Parser fmtp(data);

        LOG(kMedia, "fmtp [");
        LOG(kMedia, fmtp.NextLine());
        LOG(kMedia, "]\n");

        fmtp.Set(data);
        iCodecSpecificData.SetBytes(0);

        try {
            WriterBuffer writerBuf(iCodecSpecificData);
            WriterBinary writerBin(writerBuf);
            writerBin.WriteUint32Be(Ascii::Uint(fmtp.Next()));  // ?
            writerBin.WriteUint32Be(Ascii::Uint(fmtp.Next()));  // max_samples_per_frame
            writerBin.WriteUint8(Ascii::Uint(fmtp.Next()));     // 7a

            iBitDepth = Ascii::Uint(fmtp.Next());               // bit depth
            writerBin.WriteUint8(iBitDepth);

            writerBin.WriteUint8(Ascii::Uint(fmtp.Next()));     // rice_historymult
            writerBin.WriteUint8(Ascii::Uint(fmtp.Next()));     // rice_initialhistory
            writerBin.WriteUint8(Ascii::Uint(fmtp.Next()));     // rice_kmodifier

            iChannels = Ascii::Uint(fmtp.Next());               // 7f
            writerBin.WriteUint8(iChannels);

            writerBin.WriteUint16Be(Ascii::Uint(fmtp.Next()));  // 80
            writerBin.WriteUint32Be(Ascii::Uint(fmtp.Next()));  // 82
            writerBin.WriteUint32Be(Ascii::Uint(fmtp.Next()));  // 86

            iTimescale = Ascii::Uint(fmtp.NextLine());
            writerBin.WriteUint32Be(iTimescale);    // parsed fmtp data to be passed to alac decoder
        }
        catch (AsciiError&) {
            THROW(MediaCodecRaopNotFound);
        }

        LOG(kMedia, "Mpeg4MediaInfoBase RAOP header found %d bytes\n", bytes);
    }
    catch (CodecStreamCorrupt&) {   // FIXME - can this actually be thrown from operations in here?
        THROW(MediaCodecRaopNotFound); // not enough data found to be Raop container
    }
    catch (AsciiError&) {
        THROW(CodecStreamCorrupt);
    }
}
