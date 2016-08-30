#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Av/Raop/CodecRaopApple.h>
#include <OpenHome/Media/Codec/AlacAppleBase.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Media/Debug.h>

#include <ALACDecoder.h>
#include <ALACBitUtilities.h>


using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;
using namespace OpenHome::Av;


// CodecRaopApple

CodecRaopApple::CodecRaopApple()
    : CodecAlacAppleBase("RAOP")
{
    LOG(kCodec, "CodecRaopApple::CodecRaopApple\n");
}

CodecRaopApple::~CodecRaopApple()
{
    LOG(kCodec, "CodecRaopApple::~CodecRaopApple\n");
}

TBool CodecRaopApple::Recognise(const EncodedStreamInfo& aStreamInfo)
{
    LOG(kCodec, "CodecRaopApple::Recognise\n");
    if (aStreamInfo.RawPcm()) {
        return false;
    }
    Bws<4> buf;
    iController->Read(buf, buf.MaxBytes());

    if (buf == Brn("Raop")) {
        LOG(kCodec, "CodecRaopApple::Recognise airplay\n");
        return true;
    }

    return false;
}

void CodecRaopApple::StreamInitialise()
{
    LOG(kCodec, "CodecRaopApple::StreamInitialise\n");

    CodecAlacAppleBase::Initialise();

    iInBuf.SetBytes(0);
    iController->Read(iInBuf, 4);
    ASSERT(iInBuf == Brn("Raop")); // Already saw this during Recognise().

    // Read and parse fmtp string.
    iInBuf.SetBytes(0);
    iController->Read(iInBuf, 4);
    try {
        const TUint fmtpBytes = Ascii::Uint(iInBuf);    // size of fmtp string
        iInBuf.SetBytes(0);
        iController->Read(iInBuf, fmtpBytes);
        ParseFmtp(iInBuf);
    }
    catch (AsciiError&) {
        THROW(CodecStreamCorrupt);
    }

    if (iFrameLength > kMaxSamplesPerFrame) {
        // Current buffer size doesn't accomodate more than kMaxSamplesPerFrame.
        THROW(CodecStreamCorrupt);
    }
    if (iChannels > kMaxChannels) {
        // Current buffer size doesn't support more than kMaxChannels.
        THROW(CodecStreamCorrupt);
    }

    iInBuf.SetBytes(0);

    // Apple's implementation requires a 24-byte config and ignores first 4 bytes from CodecSpecificData.
    static const TUint kConfigBytes = 24;
    Bws<kConfigBytes> config(Brn(iCodecSpecificData.Ptr()+4, iCodecSpecificData.Bytes()-4));

    // Configure decoder (re-initialise rather than delete/new whole object).
    TInt status = iDecoder->Init((void*)(config.Ptr()), config.Bytes());
    if (status != ALAC_noErr) {
        THROW(CodecStreamCorrupt);
    }

    iBytesPerSample = iChannels*iBitDepth / 8;
    iSamplesWrittenTotal = 0;
    iBitRate = iSampleRate * iBytesPerSample * 8;
    iTrackLengthJiffies = 0;// (iDuration * Jiffies::kPerSecond) / iTimescale;


    /*LOG(kCodec, "CodecRaopApple::StreamInitialise  iBitRate: %u, iBitDepth %u, iTimeScale: %u, iSampleRate: %u, iSamplesTotal %llu, iChannels %u, iTrackLengthJiffies %u\n", iBitRate, 
                  iContainer->BitDepth(), iContainer->Timescale(), iContainer->SampleRate(), iContainer->Duration(), iContainer->Channels(), iTrackLengthJiffies);*/
    iController->OutputDecodedStream(iBitRate, iBitDepth, iSampleRate, iChannels, kCodecAlac, iTrackLengthJiffies, 0, true);
}

TBool CodecRaopApple::TrySeek(TUint aStreamId, TUint64 aSample)
{
    LOG(kCodec, "CodecRaopApple::TrySeek(%u, %llu)\n", aStreamId, aSample);
    return false;
}

void CodecRaopApple::StreamCompleted()
{
    LOG(kCodec, "CodecRaopApple::StreamCompleted\n");
    CodecAlacAppleBase::StreamCompleted();
}

void CodecRaopApple::Process() 
{
    //LOG(kCodec, "CodecRaopApple::Process\n");
    iInBuf.SetBytes(0);

    try {
        // Get size of next packet.
        static const TUint kSizeBytes = 4;
        iController->Read(iInBuf, kSizeBytes);
        if (iInBuf.Bytes() < kSizeBytes) {
            THROW(CodecStreamEnded);
        }

        // Read in next packet.
        try {
            ReaderBuffer readerBuffer(iInBuf);
            ReaderBinary readerBinary(readerBuffer);
            const TUint bytes = readerBinary.ReadUintBe(4);
            iInBuf.SetBytes(0);
            iController->Read(iInBuf, bytes);
            if (iInBuf.Bytes() < bytes) {
                THROW(CodecStreamEnded);
            }
        }
        catch (ReaderError&) {
            THROW(CodecStreamCorrupt);
        }

        Decode();   // Outputs all audio from packet.
    }
    catch (CodecStreamStart&) {
        LOG(kCodec, "CodecRaopApple::Process caught CodecStreamStart\n");
        throw;
    }
    catch (CodecStreamEnded&) {
        LOG(kCodec, "CodecRaopApple::Process caught CodecStreamEnded\n");
        throw;
    }
}

void CodecRaopApple::ParseFmtp(const Brx& aFmtp)
{
    // SDP FMTP (format parameters) data is received as a string of form:
    // a=fmtp:96 4096 0 16 40 10 14 2 255 0 0 44100
    // Third party ALAC decoder expects the data present in this string to be
    // in a packed binary format, so parse the FMTP and pack it here.

    LOG(kMedia, "CodecRaopApple::ParseFmtp [%.*s]\n", PBUF(aFmtp));

    Parser p(aFmtp);

    iCodecSpecificData.SetBytes(0);

    try {
        WriterBuffer writerBuf(iCodecSpecificData);
        WriterBinary writerBin(writerBuf);
        writerBin.WriteUint32Be(Ascii::Uint(p.Next())); // ?
        iFrameLength = Ascii::Uint(p.Next());
        writerBin.WriteUint32Be(iFrameLength);          // max_samples_per_frame
        writerBin.WriteUint8(Ascii::Uint(p.Next()));    // 7a

        iBitDepth = Ascii::Uint(p.Next());              // bit depth
        writerBin.WriteUint8(iBitDepth);

        writerBin.WriteUint8(Ascii::Uint(p.Next()));    // rice_historymult
        writerBin.WriteUint8(Ascii::Uint(p.Next()));    // rice_initialhistory
        writerBin.WriteUint8(Ascii::Uint(p.Next()));    // rice_kmodifier

        iChannels = Ascii::Uint(p.Next());              // 7f
        writerBin.WriteUint8(iChannels);

        writerBin.WriteUint16Be(Ascii::Uint(p.Next())); // 80
        writerBin.WriteUint32Be(Ascii::Uint(p.Next())); // 82
        writerBin.WriteUint32Be(Ascii::Uint(p.Next())); // 86

        iSampleRate = Ascii::Uint(p.Next());
        writerBin.WriteUint32Be(iSampleRate);
    }
    catch (AsciiError&) {
        THROW(CodecStreamCorrupt);
    }
}
