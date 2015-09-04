#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Codec/AlacBase.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Media/MimeTypeList.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecAlac : public CodecAlacBase
{
public:
    CodecAlac(IMimeTypeList& aMimeTypeList);
    ~CodecAlac();
private: // from CodecBase
    TBool Recognise(const EncodedStreamInfo& aStreamInfo);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private:
    static const TUint kMaxRecogBytes = 6 * 1024; // copied from previous CodecController behaviour
    Bws<kMaxRecogBytes> iRecogBuf;
    SampleSizeTable iSampleSizeTable;
    SeekTable iSeekTable;
    TUint iCurrentSample;       // Sample count is 32 bits in stsz box.
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewAlac(IMimeTypeList& aMimeTypeList)
{ // static
    return new CodecAlac(aMimeTypeList);
}


// CodecAlac

CodecAlac::CodecAlac(IMimeTypeList& aMimeTypeList)
    : CodecAlacBase("ALAC")
{
    LOG(kCodec, "CodecAlac::CodecAlac\n");
    aMimeTypeList.Add("audio/x-m4a");
}

CodecAlac::~CodecAlac()
{
    LOG(kCodec, "CodecAlac::~CodecAlac\n");
}

TBool CodecAlac::Recognise(const EncodedStreamInfo& aStreamInfo)
{
    LOG(kCodec, "CodecAlac::Recognise\n");

    if (aStreamInfo.RawPcm()) {
        return false;
    }
    iRecogBuf.SetBytes(0);
    iController->Read(iRecogBuf, iRecogBuf.MaxBytes());
    if (iRecogBuf.Bytes() >= 4) {
        if (Brn(iRecogBuf.Ptr(), 4) == Brn("alac")) {
            // FIXME - also check codec type that is passed within alac to determine that it is definitely alac?
            LOG(kCodec, "CodecAlac::Recognise recognised alac\n");
            return true;
        }
    }
    return false;
}

void CodecAlac::StreamInitialise()
{
    LOG(kCodec, "CodecAlac::StreamInitialise\n");

    CodecAlacBase::Initialise();

    iCurrentSample = 0;

    // Use iInBuf for gathering initialisation data, as it doesn't need to be used for audio until Process() starts being called.
    Mpeg4Info info;
    try {
        CodecBufferedReader codecBufReader(*iController, iInBuf);
        Mpeg4InfoReader mp4Reader(codecBufReader);
        mp4Reader.Read(info);

        // Read sample size table.
        ReaderBinary readerBin(codecBufReader);
        iSampleSizeTable.Clear();
        const TUint sampleCount = readerBin.ReadUintBe(4);
        iSampleSizeTable.Init(sampleCount);
        for (TUint i=0; i<sampleCount; i++) {
            const TUint sampleSize = readerBin.ReadUintBe(4);
            iSampleSizeTable.AddSampleSize(sampleSize);
        }

        // Read seek table.
        iSeekTable.Deinitialise();
        SeekTableInitialiser seekTableInitialiser(iSeekTable, codecBufReader);
        seekTableInitialiser.Init();
    }
    catch (MediaMpeg4FileInvalid&) {
        THROW(CodecStreamCorrupt);
    }
    catch (ReaderError&) {
        THROW(CodecStreamEnded);
    }

    iInBuf.SetBytes(0);
    alac = create_alac(info.BitDepth(), info.Channels());

    // FIXME - use iInBuf here instead of local stack buffer?
    Bws<IMpeg4InfoWritable::kMaxStreamDescriptorBytes> streamDescriptor;
    static const TUint kStreamDescriptorIgnoreBytes = 20; // First 20 bytes are ignored by decoder.
    streamDescriptor.SetBytes(kStreamDescriptorIgnoreBytes);
    streamDescriptor.Append(info.StreamDescriptor());

    alac_set_info(alac, (char*)streamDescriptor.Ptr()); // Configure decoder.

    iChannels = info.Channels();
    iBitDepth = info.BitDepth();
    iBytesPerSample = info.Channels()*iBitDepth/8;
    iSampleRate = info.Timescale();
    iSamplesWrittenTotal = 0;
    iTrackLengthJiffies = (info.Duration() * Jiffies::kPerSecond) / info.Timescale();


    //LOG(kCodec, "CodecAlac::StreamInitialise  iBitDepth %u, iTimeScale: %u, iSampleRate: %u, iSamplesTotal %llu, iChannels %u, iTrackLengthJiffies %u\n", iContainer->BitDepth(), iContainer->Timescale(), iContainer->SampleRate(), iContainer->Duration(), iContainer->Channels(), iTrackLengthJiffies);
    iController->OutputDecodedStream(0, info.BitDepth(), info.Timescale(), info.Channels(), kCodecAlac, iTrackLengthJiffies, 0, true);
}

TBool CodecAlac::TrySeek(TUint aStreamId, TUint64 aSample)
{
    LOG(kCodec, "CodecAlac::TrySeek(%u, %llu)\n", aStreamId, aSample);

    try {
        TUint64 startSample = 0;
        TUint64 bytes = iSeekTable.Offset(aSample, startSample);     // find file offset relating to given audio sample
        LOG(kCodec, "CodecAlac::TrySeek to sample: %llu, byte: %lld\n", startSample, bytes);
        TBool canSeek = iController->TrySeekTo(aStreamId, bytes);
        if (canSeek) {
            iSamplesWrittenTotal = aSample;
            iCurrentSample = static_cast<TUint>(startSample);
            iTrackOffset = (aSample * Jiffies::kPerSecond) / iSampleRate;
            iInBuf.SetBytes(0);
            iDecodedBuf.SetBytes(0);
            iOutBuf.SetBytes(0);
            iController->OutputDecodedStream(0, iBitDepth, iSampleRate, iChannels, kCodecAlac, iTrackLengthJiffies, aSample, true);
        }
        return canSeek;
    }
    catch (MediaMpeg4OutOfRange&) {
        LOG(kCodec, "CodecAlac::TrySeek caught MediaMpeg4OutOfRange sample aStreamId: %u, aSample: %lld\n", aStreamId, aSample);
        return false;
    }
    catch (MediaMpeg4FileInvalid&) {
        LOG(kCodec, "CodecAlac::TrySeek caught MediaMpeg4FileInvalid sample aStreamId: %u, aSample: %lld\n", aStreamId, aSample);
        return false;
    }
}

void CodecAlac::StreamCompleted()
{
    LOG(kCodec, "CodecAlac::StreamCompleted\n");
    CodecAlacBase::StreamCompleted();
}

void CodecAlac::Process() 
{
    //LOG(kCodec, "CodecAlac::Process\n");

    if (iCurrentSample < iSampleSizeTable.Count()) {
        // Read in a single alac sample.
        iInBuf.SetBytes(0);

        try {
            LOG(kCodec, "CodecAlac::Process  iCurrentSample: %u, size: %u, inBuf.MaxBytes(): %u\n", iCurrentSample, iSampleSizeTable.SampleSize(iCurrentSample), iInBuf.MaxBytes());
            TUint sampleSize = iSampleSizeTable.SampleSize(iCurrentSample);
            iController->Read(iInBuf, sampleSize);
            if (iInBuf.Bytes() < sampleSize) {
                THROW(CodecStreamEnded);
            }
            iCurrentSample++;
            Decode();
        }
        catch (CodecStreamStart&) {
            iStreamStarted = true;
            LOG(kCodec, "CodecAlac::Process caught CodecStreamStart\n");
        }
        catch (CodecStreamEnded&) {
            iStreamEnded = true;
            LOG(kCodec, "CodecAlac::Process caught CodecStreamEnded\n");
        }
    }
    else {
        iStreamEnded = true;
    }

    OutputFinal();
}
