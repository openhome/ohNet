#include <OpenHome/Media/Codec/AacBase.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Media/Debug.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecAac : public CodecAacBase
{
public:
    CodecAac();
    ~CodecAac();
private: // from CodecBase
    TBool Recognise(const EncodedStreamInfo& aStreamInfo);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private:
    void ProcessMpeg4();
    TUint SkipEsdsTag(const TByte& aPtr);
private:
    static const TUint kMaxRecogBytes = 6 * 1024; // copied from previous CodecController behaviour
    Bws<kMaxRecogBytes> iRecogBuf;
    SampleSizeTable iSampleSizeTable;
    SeekTable iSeekTable;
    TUint iCurrentSample;       // Sample count is 32 bits in stsz box.
};

} //namespace Codec
} //namespace Media
} //namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewAac()
{ // static
    return new CodecAac();
}



// CodecAac

CodecAac::CodecAac()
    : CodecAacBase("AAC")
{
    LOG(kCodec, "CodecAac::CodecAac\n");
}

CodecAac::~CodecAac()
{
    LOG(kCodec, "CodecAac::~CodecAac\n");
}

TBool CodecAac::Recognise(const EncodedStreamInfo& aStreamInfo)
{
    LOG(kCodec, "CodecAac::Recognise\n");

    if (aStreamInfo.RawPcm()) {
        return false;
    }
    iRecogBuf.SetBytes(0);
    iController->Read(iRecogBuf, iRecogBuf.MaxBytes());
    if (iRecogBuf.Bytes() >= 4) {
        if (Brn(iRecogBuf.Ptr(), 4) == Brn("mp4a")) {
            // FIXME - should also check codec type that is passed within esds to determine that it is definitely AAC and not another codec (e.g., MP3)
            LOG(kCodec, "CodecAac::Recognise aac mp4a\n");
            return true;
        }
    }
    return false;
}

TUint CodecAac::SkipEsdsTag(const TByte& aPtr)
{
    switch(aPtr) {
        case 0x80:
        case 0x81:
        case 0xFE:
            return 3;
        default:
            return 0;
    }
}

void CodecAac::StreamInitialise()
{
    LOG(kCodec, "CodecAac::StreamInitialise\n");

    CodecAacBase::StreamInitialise();

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
        THROW(CodecStreamCorrupt);
    }

    iInBuf.SetBytes(0);

    // see http://wiki.multimedia.cx/index.php?title=Understanding_AAC for details
    // or http://xhelmboyx.tripod.com/formats/mp4-layout.txt - search for 'esds'

    // also see APar_Extract_esds_Info() in
    //          http://m4sharp.googlecode.com/svn-history/r3/trunk/m4aSharp/m4aSharp/AP_AtomExtracts.cpp
    // and
    //          http://www.jthink.net/jaudiotagger/javadoc/org/jaudiotagger/audio/mp4/atom/Mp4EsdsBox.html
    /*
    EsdsBox ( stream specific description box), usually holds the Bitrate/No of Channels

    It contains a number of (possibly optional?) sections (section 3 - 6) (containing optional filler) with differeent info in each section.

    -> 4 bytes version/flags = 8-bit hex version + 24-bit hex flags (current = 0)

    Section 3 -> 1 byte ES descriptor type tag = 8-bit hex value 0x03
    -> 3 bytes optional extended descriptor type tag string = 3 * 8-bit hex value - types are 0x80,0x81,0xFE
    -> 1 byte descriptor type length = 8-bit unsigned length
    -> 2 bytes ES ID = 16-bit unsigned value
    -> 1 byte stream priority = 8-bit unsigned value - Defaults to 16 and ranges from 0 through to 31

    Section 4 -> 1 byte decoder config descriptor type tag = 8-bit hex value 0x04
    -> 3 bytes optional extended descriptor type tag string = 3 * 8-bit hex value - types are 0x80,0x81,0xFE
    -> 1 byte descriptor type length = 8-bit unsigned length *
    -> 1 byte object type ID = 8-bit unsigned value
    - type IDs are system v1 = 1 ; system v2 = 2
    - type IDs are MPEG-4 video = 32 ; MPEG-4 AVC SPS = 33
    - type IDs are MPEG-4 AVC PPS = 34 ; MPEG-4 audio = 64
    - type IDs are MPEG-2 simple video = 96
    - type IDs are MPEG-2 main video = 97
    - type IDs are MPEG-2 SNR video = 98
    - type IDs are MPEG-2 spatial video = 99
    - type IDs are MPEG-2 high video = 100
    - type IDs are MPEG-2 4:2:2 video = 101
    - type IDs are MPEG-4 ADTS main = 102
    - type IDs are MPEG-4 ADTS Low Complexity = 103
    - type IDs are MPEG-4 ADTS Scalable Sampling Rate = 104
    - type IDs are MPEG-2 ADTS = 105 ; MPEG-1 video = 106
    - type IDs are MPEG-1 ADTS = 107 ; JPEG video = 108
    - type IDs are private audio = 192 ; private video = 208
    - type IDs are 16-bit PCM LE audio = 224 ; vorbis audio = 225
    - type IDs are dolby v3 (AC3) audio = 226 ; alaw audio = 227
    - type IDs are mulaw audio = 228 ; G723 ADPCM audio = 229
    - type IDs are 16-bit PCM Big Endian audio = 230
    - type IDs are Y'CbCr 4:2:0 (YV12) video = 240 ; H264 video = 241
    - type IDs are H263 video = 242 ; H261 video = 243

    -> 6 bits stream type = 3/4 byte hex value - type IDs are object descript. = 1 ; clock ref. = 2 - type IDs are scene descript. = 4 ; visual = 4 - type IDs are audio = 5 ; MPEG-7 = 6 ; IPMP = 7 - type IDs are OCI = 8 ; MPEG Java = 9 - type IDs are user private = 32
    -> 1 bit upstream flag = 1/8 byte hex value
    -> 1 bit reserved flag = 1/8 byte hex value set to 1
    -> 3 bytes buffer size = 24-bit unsigned value
    -> 4 bytes maximum bit rate = 32-bit unsigned value
    -> 4 bytes average bit rate = 32-bit unsigned value

    Section 5 -> 1 byte decoder specific descriptor type tag 8-bit hex value 0x05
    -> 3 bytes optional extended descriptor type tag string = 3 * 8-bit hex value - types are 0x80,0x81,0xFE
    -> 1 byte descriptor type length = 8-bit unsigned length
    -> 1 byte Audio profile Id - 5 bits Profile Id - 3 bits Unknown
    -> 8 bits other flags - 3 bits unknown - 2 bits is No of Channels - 3 bits unknown

    Section 6
    -> 1 byte SL config descriptor type tag = 8-bit hex value 0x06
    -> 3 bytes optional extended descriptor type tag string = 3 * 8-bit hex value - types are 0x80,0x81,0xFE
    -> 1 byte descriptor type length = 8-bit unsigned length
    -> 1 byte SL value = 8-bit hex value set to 0x02

    Valid Type ID seen for aac is "MPEG-4 audio" - not sure if any others are used so no checking for this is done
    */
    iChannels = 0;
    const TByte *ptr = info.StreamDescriptor().Ptr();
    //ptr += 4;   // Container should already have skipped over 32-bit version field.

    if(*ptr == 3) {     // section 3
        ptr++;
        ptr += SkipEsdsTag(*ptr);
        if(*ptr != 0) {
            ptr += 4;
            if(*ptr == 4) {     // section 4
                ptr++;
                ptr += SkipEsdsTag(*ptr);
                if(*ptr != 0) {
                    ptr++; //ObjectTypeIndication
                    ptr++; // a_v_flag
                    ptr += 4;
                    //extract bitrates
                    iBitrateMax = Converter::BeUint32At(Brn(ptr,4), 0);
                    ptr += 4;
                    iBitrateAverage = Converter::BeUint32At(Brn(ptr,4), 0);
                    ptr += 4;
                    if(*ptr == 5) {     // section 5
                        ptr++;
                        ptr += SkipEsdsTag(*ptr);
                        if(*ptr != 0) {
                            ptr += 2;
                            iChannels = (*ptr >> 3) & 0xf;  // FIXME - compare against iInfo.Channels() - or is that not valid?
                        }
                    }

                }
            }
        }
    }

    iSampleRate = info.Timescale();
    iOutputSampleRate = iSampleRate;
    iBitDepth = info.BitDepth();
    //iChannels = iMp4->Channels();     // not valid !!!
    iSamplesTotal = info.Duration();

    iBytesPerSample = iChannels*iBitDepth/8;
    InitialiseDecoder();

    iTrackLengthJiffies = (iSamplesTotal * Jiffies::kPerSecond) / iSampleRate;
    iTrackOffset = 0;

    LOG(kCodec, "CodecAac::StreamInitialise iBitrateAverage %u, iBitDepth %u, iSampleRate: %u, iSamplesTotal %llu, iChannels %u, iTrackLengthJiffies %u\n", iBitrateAverage, iBitDepth, iOutputSampleRate, iSamplesTotal, iChannels, iTrackLengthJiffies);
    iController->OutputDecodedStream(iBitrateAverage, iBitDepth, iOutputSampleRate, iChannels, kCodecAac, iTrackLengthJiffies, 0, false);
}

void CodecAac::StreamCompleted()
{
    LOG(kCodec, "CodecAac::StreamCompleted\n");
}

TBool CodecAac::TrySeek(TUint aStreamId, TUint64 aSample)
{
    LOG(kCodec, "CodecAac::TrySeek(%u, %llu)\n", aStreamId, aSample);
    TUint64 startSample;

    TUint64 sampleInSeekTable = aSample;
    if (iOutputSampleRate != iSampleRate) {
        TUint divisor = iOutputSampleRate / iSampleRate;
        sampleInSeekTable /= divisor;
    }

    try {
        TUint64 bytes = iSeekTable.Offset(sampleInSeekTable, startSample);     // find file offset relating to given audio sample
        LOG(kCodec, "CodecAac::Seek to sample: %llu, byte: %llu\n", startSample, bytes);
        TBool canSeek = iController->TrySeekTo(aStreamId, bytes);
        if (canSeek) {
            iTotalSamplesOutput = aSample;
            iCurrentSample = static_cast<TUint>(startSample);
            iTrackOffset = (Jiffies::kPerSecond/iOutputSampleRate)*aSample;

            iController->OutputDecodedStream(iBitrateAverage, iBitDepth, iOutputSampleRate, iChannels, kCodecAac, iTrackLengthJiffies, aSample, false);
        }
        return canSeek;
    }
    catch (MediaMpeg4OutOfRange&) {
        LOG(kCodec, "CodecAac::TrySeek caught MediaMpeg4OutOfRange sample aStreamId: %u, aSample: %lld\n", aStreamId, aSample);
        return false;
    }
    catch (MediaMpeg4FileInvalid&) {
        LOG(kCodec, "CodecAac::TrySeek caught MediaMpeg4FileInvalid aStreamId: %u, aSample: %lld\n", aStreamId, aSample);
        return false;
    }
}

void CodecAac::Process()
{
    ProcessMpeg4();

    if (iNewStreamStarted) {
        THROW(CodecStreamStart);
    }
    if (iStreamEnded) {
        THROW(CodecStreamEnded);
    }
}

void CodecAac::ProcessMpeg4() 
{
    LOG(kCodec, "CodecAac::Process\n");
    if (iCurrentSample < iSampleSizeTable.Count()) {

        // Read in a single aac sample.
        iInBuf.SetBytes(0);

        try {
            LOG(kCodec, "CodecAac::Process  iCurrentSample: %u, size: %u, inBuf.MaxBytes(): %u\n", iCurrentSample, iSampleSizeTable.SampleSize(iCurrentSample), iInBuf.MaxBytes());
            TUint sampleSize = iSampleSizeTable.SampleSize(iCurrentSample);
            iController->Read(iInBuf, sampleSize);
            LOG(kCodec, "CodecAac::Process  read iInBuf.Bytes() = %u\n", iInBuf.Bytes());
            if (iInBuf.Bytes() < sampleSize) {
                THROW(CodecStreamEnded);
            }
            iCurrentSample++;

            // Now decode and output
            DecodeFrame(false);
        }
        catch (CodecStreamStart&) {
            iNewStreamStarted = true;
            LOG(kCodec, "CodecAac::ProcessMpeg4 caught CodecStreamStart\n");
        }
        catch (CodecStreamEnded&) {
            iStreamEnded = true;
            LOG(kCodec, "CodecAac::ProcessMpeg4 caught CodecStreamEnded\n");
        }
    }
    else {
        iStreamEnded = true;
    }
    FlushOutput();
}
