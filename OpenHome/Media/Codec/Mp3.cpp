#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/MimeTypeList.h>
#include <mad.h>

#include <stdlib.h>
#include <string.h>

EXCEPTION(Mp3SampleInvalid);

namespace OpenHome {
namespace Media {
namespace Codec {

class Mp3Header;

class CodecMp3 : public CodecBase
{
public:
    CodecMp3(IMimeTypeList& aMimeTypeList);
private: // from CodecBase
    ~CodecMp3();
    TBool Recognise(const EncodedStreamInfo& aStreamInfo);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private:
    static const TUint kReadReqBytes = 4096;
    static const TUint kInBufBytes = kReadReqBytes+MAD_BUFFER_GUARD;
    mad_stream  iMadStream;
    mad_frame   iMadFrame;
    mad_synth   iMadSynth;
    TUint64     iSamplesWrittenTotal;
    Mp3Header*  iHeader;
    TUint       iHeaderBytes;
    Bws<kInBufBytes> iInput;
    TUint64     iTrackLengthJiffies;
    TUint64     iTrackOffset;
    Bws<DecodedAudio::kMaxBytes> iOutput;
    TBool       iStreamEnded;
    Bws<6*1024> iRecogBuf;
};

class IMp3HeaderExtended
{
public:
    virtual ~IMp3HeaderExtended() {}
    virtual TUint64 SamplesTotal() const = 0;
    virtual TUint64 SampleToByte(TUint64 aSample) const = 0;
    virtual TUint BitRate() const = 0;
};

class Mp3HeaderExtendedBare : public IMp3HeaderExtended
{
public:
    Mp3HeaderExtendedBare(TUint64 aTotalBytes, TUint aByteRate, TUint aSampleRate);
private: // from IMp3HeaderExtended
    TUint64 SamplesTotal() const { return iSamplesTotal; }
    TUint64 SampleToByte(TUint64 aSample) const;
    TUint BitRate() const { return iBitRate; }
private:
    TUint64 iSamplesTotal;
    TUint iBitRate;
    float iBytesPerSample;
};

class Mp3HeaderExtendedBareNonSeekable : public IMp3HeaderExtended
{
public:
    Mp3HeaderExtendedBareNonSeekable(TUint aByteRate);
private: // from IMp3HeaderExtended
    TUint64 SamplesTotal() const { return 0; }
    TUint64 SampleToByte(TUint64 aSample) const;
    TUint BitRate() const { return iBitRate; }
private:
    TUint iBitRate;
};

class Mp3Header
{
public:
    Mp3Header(const Brx& aHeaderData, TUint aHeaderBytes, TUint64 aTotalBytes);
    ~Mp3Header();
    TUint Channels() const { return iChannels; }
    TUint SampleRate() const { return iSampleRate; }
    TUint64 SamplesTotal() const { return iExtended->SamplesTotal(); }
    TUint64 SampleToByte(TUint64 aSample) const { return iExtended->SampleToByte(aSample) + iHeaderBytes; }
    TUint BitRate() const { return iExtended->BitRate(); }
    const Brx& Name() const { return *(kNames[iVersion][iLayer]); }
    static TBool Exists(const Brx& aData, TUint& aSyncFrameOffsetBytes);
    static TUint ValidSync(const Brx& aSync, TUint& layer, TUint& mode);
private:
    IMp3HeaderExtended* iExtended;
    TUint iHeaderBytes;
    TUint iSampleRate;
    TUint iChannels;
    enum EMpegVersion {
        eMpeg25 = 0,
        eMpegReserved,
        eMpeg2,
        eMpeg1
    } iVersion;

    enum EMpegLayer {
        eLayer1 = 0,
        eLayer2,
        eLayer3,
        eLayerReserved
    } iLayer;

    TBool iMpegLsf;

    static const TUint32 kFrameSyncMask   = 0xFFE00000;
    static const TUint32 kVersionMask     = 0x00180000;
    static const TUint32 kLayerMask       = 0x00060000;
    static const TUint32 kBitRateMask     = 0x0000F000;
    static const TUint32 kSampleRateMask  = 0x00000C00;
    static const TUint32 kChannelMask     = 0x000000C0;

    static const TUint32 kSampleRates[4][3];
    static const TUint32 kBitRates[2][3][15];
    static const TUint32 kFrameSamples[2][3];
    static const Brn*    kNames[4][3];

    friend class Mp3HeaderExtendedXing;
};

class Mp3HeaderExtendedXing : public IMp3HeaderExtended
{
public:
    Mp3HeaderExtendedXing(const Brx& aHeaderData, const Mp3Header& aHeader);
    virtual TUint64 SamplesTotal() const { return iSamplesTotal; }
    virtual TUint64 SampleToByte(TUint64 aSample) const;
    virtual TUint BitRate() const { return iBitRate; }
private:
    TUint64 iSamplesTotal;
    TUint32 iFrames; //total number of frames
    TUint32 iBytes;  //number of bytes in the mp3 audio data _only_ no tags included
    TUint iBitRate;
    mutable Bws<100> iToc;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

EXCEPTION(CodecExtendedHeaderNotFound);
EXCEPTION(CodecSyncInvalid);

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

const TUint kBitDepth = 24;


CodecBase* CodecFactory::NewMp3(IMimeTypeList& aMimeTypeList)
{ // static
    return new CodecMp3(aMimeTypeList);
}



// Mp3HeaderExtendedBare

Mp3HeaderExtendedBare::Mp3HeaderExtendedBare(TUint64 aTotalBytes, TUint aByteRate, TUint aSampleRate) : iBitRate(aByteRate*8)
{    
    /* Provide an estimate of the total samples.  This won't be valid for all
       files, but it's a worst case guess if we don't have further information
       in another header.  This isn't prefectly accurate because of the mp3
       header in each frame as well as any id3 or similar tags included in the
       file.  However, it's close enough for our seeking purposes. */
    TUint64 seconds = aTotalBytes / aByteRate;
    iSamplesTotal = seconds * aSampleRate;
    iBytesPerSample = (float)aByteRate / aSampleRate;
    //LOG(kCodec, "Mp3HeaderExtendedBare::Mp3HeaderExtendedBare: iSamplesTotal: %lld, iBytesPerSample: %f\n", iSamplesTotal, iBytesPerSample);
}

TUint64 Mp3HeaderExtendedBare::SampleToByte(TUint64 aSample) const
{
    //LOG(kCodec, "Mp3HeaderExtendedBare::SampleToByte(%lld), iBytesPerSample: %f\n", aSample, iBytesPerSample);
    TUint64 byte = (TUint64)(aSample * iBytesPerSample);
    return byte;
}


// Mp3HeaderExtendedBareNonSeekable

Mp3HeaderExtendedBareNonSeekable::Mp3HeaderExtendedBareNonSeekable(TUint aByteRate)
    : iBitRate(aByteRate*8)
{
}

TUint64 Mp3HeaderExtendedBareNonSeekable::SampleToByte(TUint64 /*aSample*/) const
{
    THROW(Mp3SampleInvalid);
}


// Mp3HeaderExtendedXing

Mp3HeaderExtendedXing::Mp3HeaderExtendedXing(const Brx& aHeaderData, const Mp3Header& aHeader)
{
    // We already know we have at least an mp3 file (checked by CodecMp3::Recognise)
    // See if there is a XING or INFO header at any of the common positions
    // Byte Pos of "XING" or "INFO" for LAYER 3 ONLY
    //              MPEG 1      MPEG 2/2.5
    // Stereo/Joint 0x24        0x15
    // Mono         0x15        0x0d
    //
    // For layer 2 it's not possible to generically find this.  For layer 1,
    // it's too complicated to bother (especially given number of layer 1 files
    // in existence: none).  In these cases, the file will play fine, but we
    // won't have the extended vbr info.
    //
    const TChar* kXing = "Xing";
    const TChar* kInfo = "Info";
    TBool found = false;
    Brn value;
    const TChar* check;

    TUint offBytes = 0x15;
    if (aHeader.Channels() == 1) {
        value = aHeaderData.Split(offBytes);
        check = (const TChar*) value.Ptr();
        //LOG(kCodec, "Xing check at offbytes %x: ", offBytes);
        //LOG(kCodec, Brn(value.Ptr(), 4));
        //LOG(kCodec, "\n");
        if ((strncmp(check, kXing, 4) == 0) || (strncmp(check, kInfo, 4) == 0)) {
            found = true;
            //LOG(kCodec, "mp3 mono vbr header found\n");
        }
    }
    else {
        offBytes = 0x24;
        value = aHeaderData.Split(offBytes);
        check = (const TChar*) value.Ptr();
        //LOG(kCodec, "Xing check at offbytes %x: ", offBytes);
        //LOG(kCodec, Brn(value.Ptr(), 4));
        //LOG(kCodec, "\n");
        if ((strncmp(check, kXing, 4) == 0) || (strncmp(check, kInfo, 4) == 0)) {
            found = true;
            //LOG(kCodec, "mp3 2 channel vbr header found\n");
        }
    }
    if (!found) {
        THROW(CodecExtendedHeaderNotFound);
    }

    offBytes += 4;
    TUint32 flags = Converter::BeUint32At(aHeaderData, offBytes);
    //LOG(kCodec, "VBR flags: %08x\n", flags);

    if ((flags & 0x7) == 0x7) { // frames, bytes, toc
        if (flags & 0x01) { // Frames field present
            offBytes += 4;
            iFrames = Converter::BeUint32At(aHeaderData, offBytes);
        }
        if (flags & 0x02) { // Bytes field present
            offBytes += 4;
            iBytes = Converter::BeUint32At(aHeaderData, offBytes);
        }
        if (flags & 0x04) { // Toc present
            offBytes += 4;
            iToc.Replace(aHeaderData.Ptr() + offBytes, 100); // Toc always 100 bytes 
        }
    }
    else { 
        // If there's a Xing header, but frames, bytes, and toc are not all
        // present, then the header is more or less pointless, just use the bare
        // header for default approximations.
        THROW(CodecExtendedHeaderNotFound);
    }

    TUint32 samplesPerFrame = aHeader.kFrameSamples[aHeader.iMpegLsf][aHeader.iLayer];
    iSamplesTotal = iFrames * samplesPerFrame;

    // BitRate = (TotalBytes / TotalSamples) * SampleRate * 8
    // Done in order below to avoid floating point divison
    // Believed not to overflow as mp3 total bytes is no bigger than 32 bit.
    TUint64 bitRate = (TUint64)iBytes * aHeader.SampleRate();
    bitRate *= 8;
    bitRate /= iSamplesTotal;
    iBitRate = (TUint32)bitRate;

    //LOG(kCodec, "Mp3HeaderExtendedXing: frames: %d, bytes: %d, SamplesTotal: %lld, BitRate: %d\n", iFrames, iBytes, iSamplesTotal, iBitRate);
}

TUint64 Mp3HeaderExtendedXing::SampleToByte(TUint64 aSamples) const
{
    if (aSamples >= iSamplesTotal) {
        THROW(Mp3SampleInvalid);
    }
    // TOC has 100 entries of 1 byte.  Each byte has the following value:
    // (TOC[i] / 256) * fileBytes

    // 1) Each entry in toc represents 1%.  Find % of file seek request is:
    //   Req% = (aSamples / iSamplesTotal) * 100
    //
    // Multiplying by 100 before dividing avoids requiring floating point numbers.
    // This is overflow safe as mp3 can actually only support 32 bit samples.
    TUint64 percent = aSamples * 100; 
    // The truncation here is fine as the toc is only approximate. 
    percent /= iSamplesTotal; 

    // 2) Ensure we don't exceed iToc boundaries (this is possible if aSamples
    // == iSamplesTotal)
    if (percent > 99) {
        percent = 99;
    }

    // 3) (iToc[%] / 256) * fileBytes
    TUint64 bytes = iToc.At((TUint)percent);
    bytes *= iBytes; //won't overflow as iBytes is 32 bit 
    bytes >>= 8;
    //LOG(kCodec, "Mp3HeaderExtendedXing::SampleToByte(%lld), percent: %lld, bytes: %lld, totalBytes: %d\n", aSamples, percent, bytes, iBytes);
    return bytes; 
}


// Mp3Header

const TUint32 Mp3Header::kSampleRates[4][3] =
{ 
    {11025, 12000, 8000,  },    // MPEG 2.5
    {0,     0,     0,     },    // reserved
    {22050, 24000, 16000, },    // MPEG 2
    {44100, 48000, 32000  }     // MPEG 1
};

const TUint32 Mp3Header::kBitRates[2][3][15] = 
{
    {   // MPEG 1
        {0,32,64,96,128,160,192,224,256,288,320,352,384,416,448,}, // Layer1
        {0,32,48,56, 64, 80, 96,112,128,160,192,224,256,320,384,}, // Layer2
        {0,32,40,48, 56, 64, 80, 96,112,128,160,192,224,256,320,}  // Layer3
    },
    {   // MPEG 2, 2.5
        {0,32,48,56,64,80,96,112,128,144,160,176,192,224,256,},    // Layer1
        {0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,},         // Layer2
        {0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,}          // Layer3
    }
};

const TUint32 Mp3Header::kFrameSamples[2][3] =
{
    {384, 1152, 1152 },  //MPEG 1      -- layer 1,2,3
    {384, 1152, 576, }   //MPEG 2, 2.5 -- layer 1,2,3
};

const Brn kNameM1L1("Mpeg1 Layer 1");
const Brn kNameM1L2("MP2");
const Brn kNameM1L3("MP3");
const Brn kNameM2L1("Mpeg2 Layer1");
const Brn kNameM2L2("Mpeg2 Layer2");
const Brn kNameM2L3("Mpeg2 Layer3");
const Brn kNameM25L1("Mpeg2.5 Layer1");
const Brn kNameM25L2("Mpeg2.5 Layer2");
const Brn kNameM25L3("Mpeg2.5 Layer3");

const Brn* Mp3Header::kNames[4][3] =
{ 
    {&kNameM25L1, &kNameM25L2, &kNameM25L3,  },    // MPEG 2.5
    {0,           0,           0,            },    // reserved
    {&kNameM2L1,  &kNameM2L2,  &kNameM2L3,   },    // MPEG 2
    {&kNameM1L1,  &kNameM1L2,  &kNameM1L3    }     // MPEG 1
};

Mp3Header::Mp3Header(const Brx& aHeaderData, TUint aHeaderBytes, TUint64 aTotalBytes)
    :iHeaderBytes(aHeaderBytes)
{
    TUint32 frame = Converter::BeUint32At(aHeaderData, 0);
    //LOG(kCodec, "Mp3Header::Mp3Header frame: %08x, totalBytes: %lld\n", frame, aTotalBytes);
    
    // We must only be given the beginning of an mp3 frame.
    ASSERT((frame & kFrameSyncMask) == kFrameSyncMask);

    iVersion = EMpegVersion((frame & kVersionMask) >> 19);
    if (iVersion == eMpegReserved) {
        THROW(CodecStreamCorrupt);
    }
    if (iVersion == eMpeg1) {
        iMpegLsf = false;
    }
    else {
        iMpegLsf = true;
    }
    iLayer = EMpegLayer(3 - ((frame & kLayerMask) >> 17));
    if (iLayer == eLayerReserved) {
        THROW(CodecStreamCorrupt);
    }

    TUint32 bitRateIndex = (frame & kBitRateMask) >> 12;
    if (bitRateIndex == 0xF) { //reserved
        THROW(CodecStreamCorrupt);
    }
    TUint32 byteRate = kBitRates[iMpegLsf][iLayer][bitRateIndex] * 1000 / 8;

    TUint32 sampleRateIndex = (frame & kSampleRateMask) >> 10;
    if (sampleRateIndex == 0x3) { //reserved
        THROW(CodecStreamCorrupt);
    }
    iSampleRate = kSampleRates[iVersion][sampleRateIndex];

    TUint32 channelIndex = (frame & kChannelMask) >> 6;
    if (channelIndex == 0x3) {
        iChannels = 1; //Mono(0b11)
    }
    else {
        // Stereo (0b00), JointStereo(0b01), DualChannel(0b10) are all 2
        // channels from our persepective
        iChannels = 2; 
    }

    //LOG(kCodec, "Mp3Header::Mp3Header: iLayer: %d\nbitRate: %d\nsampleRate: %d\nchannels: %d\n", iLayer+1, byteRate*8, iSampleRate, iChannels);
    if (aTotalBytes == 0) { //non seekable stream
        iExtended = new Mp3HeaderExtendedBareNonSeekable(byteRate);
    }
    else {
        try {
            iExtended = new Mp3HeaderExtendedXing(aHeaderData, *this);
        }
        catch (CodecExtendedHeaderNotFound&) {
            iExtended = new Mp3HeaderExtendedBare(aTotalBytes-iHeaderBytes, byteRate, iSampleRate);
        }
    }
}

Mp3Header::~Mp3Header()
{
    //LOG(kCodec, "Mp3Header::~Mp3Header\n");
    delete iExtended;
}

TBool Mp3Header::Exists(const Brx& aData, TUint& aSyncFrameOffsetBytes)
{
    // Search for a bare mpeg sync frame.  Bizarrely, sync frames don't 
    // necessarily (although commonly they do) exist at the beginning.  So we 
    // search through up to kSearchSpace bytes for a sync frame.
    // Typically a frame is either 1044 or 1045 bytes long, but can be 1440, so search
    // through at least a full frame of data for the initial sync.
    const TUint kSearchSpace = 1500;
    const TUint kSyncsReq = 3;
    TUint toSearch = kSearchSpace;

    //LOG(kCodec, "Mp3Header::Exists search %d bytes from %d\n", toSearch, aData.Bytes());

    if (aData.Bytes() < toSearch + 1) { // +1 for ptr[i+1] below
        toSearch = aData.Bytes() - 1;
    }
    TUint i; // index from beginning of aData
    TUint8* ptr = (TUint8*)aData.Ptr();
    for (i=0; i < toSearch; i++) {
        if ((ptr[i] == 0xff) && ((ptr[i+1] & 0xe0) == 0xe0)) {
            // This is a potential sync frame (11 ones), pass it to mad to
            // determine if it actually is
            //LOG(kCodec, "Mp3Header::Exists found potential sync frame at: %d bytes [%x][%x]\n", i, ptr[i], ptr[i+1]);

            aSyncFrameOffsetBytes = i;    
            TUint j = 0; //index from potential sync 

            try {
                TUint layer, last_layer = 0;
                TUint mode = 0;
                // initialisation of last_layer & last_mode required to avoid (incorrect) MSVC warning
                for (TUint syncsFound = 0; syncsFound < kSyncsReq; syncsFound++) {
                    TUint offset = i+j;
                    //LOG(kCodec, "Mp3Header::Exists syncsFound: %d of req: %d at pos: %d\n", syncsFound, kSyncsReq, offset);
                    if (offset >= aData.Bytes()) {
                        //LOG(kCodec, "Mp3Header::Exists ran out of buffer to find required syncs\n");
                        return false; //haven't found required syncs within aData
                    }
                    Brn frame(ptr+offset, aData.Bytes()-offset);
                    j += ValidSync(frame, layer, mode);
                    if (syncsFound == 0) {
                        last_layer = layer;
                    }
                    // Don't compare modes. Some extended metadata frames can
                    // have a different mode from rest of stream - but we don't
                    // want to discard that metadata.
                    if (last_layer != layer) {
                        //LOG(kCodec, "Mp3Header::Exists, inconsistent layers/modes\n");
                        THROW(CodecSyncInvalid);
                    }
                }
                // We've found kSyncsReq sync frames, assuming this to be valid mp3
                return true;
            }
            catch (CodecSyncInvalid& ) {
                //LOG(kCodec, "Mp3Header::Exists, potential sync was fake\n");
                // This potential sync was invalid, keep searching from 
                // original position in outer loop
                continue;
            }
        }
    }
    return false;
}

TUint Mp3Header::ValidSync(const Brx& aSync, TUint& layer, TUint& mode)
{
    //LOG(kCodec, "Mp3Header::ValidSync?\n");
    struct mad_stream stream;
    mad_stream_init(&stream);

    mad_stream_buffer(&stream, aSync.Ptr(), aSync.Bytes());

    struct mad_header header;
    mad_header_init(&header);

    TInt ret = mad_header_decode(&header, &stream);
    if ((ret == 0) && (stream.sync == 1)) {
        //LOG(kCodec, "layer: %d\nmode: %d\nemphasis: %d\nbitrate: %d\nsamplerate: %d\nchannels: %d\n",header.layer,header.mode,header.emphasis,header.bitrate,header.samplerate,MAD_NCHANNELS(&header));
        //LOG(kCodec, "madstream:\nbuffer: %p\nbufend: %p\nsync: %d\nthis_frame: %p\nnext_frame: %p\nptr: %p\nerror: %s\n",stream.buffer,stream.bufend,stream.sync,stream.this_frame,stream.next_frame,stream.ptr.byte,mad_stream_errorstr(&stream));
        TUint frameBytes = stream.next_frame - stream.this_frame;
        //LOG(kCodec, "Frame size: %d\n", frameBytes);

        layer = header.layer;
        mode = header.mode;
        return frameBytes;
    }
    THROW(CodecSyncInvalid);
}



// Synthesized samples need to be converted from libmad's fixed
// point representation to standard pcm.
// libmad stores in 32 bits the following:
//   SWWWFFFF FFFFFFFF FFFFFFFF FFFFFFF
//      where 
//        S: sign 
//        W: whole number
//        F: fraction of W
//
// MAD_F_FRACBITS is the number of F's and is architecture dependent (28 on all
// platforms we currently care about).
//
// After checking for clipping (first two if's) we then convert to 24-bit with the bottom 8 bits unused.
static TUint32 fixedToPcm(mad_fixed_t aFixed)
{
    const TUint32 kPlusOne  = 0x7FFFFF00l;
    const TUint32 kMinusOne = 0x80000000l;
    if (aFixed >= MAD_F_ONE) {
        //LOG(kCodec, "fixedToPcm upper CLIPPED: %08x ret: %08x\n", aFixed, kPlusOne);
        return kPlusOne;
    }
    if (aFixed <= -MAD_F_ONE) {
        //LOG(kCodec, "fixedToPcm lower CLIPPED: %08x ret: %08x\n", aFixed, kMinusOne);
        return kMinusOne; 
    }
    // if no clipping, then the 24 bit number is composed of the lsb W and 23 of
    // the most significant F's.  Linn stores the 24 bits in the higher order
    // bits with the bottom eight bits zeroed.
    TInt32 value = (aFixed << 3) & 0xFFFFFF00l;
    return (TUint32)value;
}


// CodecMp3

CodecMp3::CodecMp3(IMimeTypeList& aMimeTypeList)
    : CodecBase("MP3")
    , iHeader(nullptr)
    , iHeaderBytes(0)
{
    (void)memset(&iMadStream, 0, sizeof(iMadStream));
    (void)memset(&iMadFrame, 0, sizeof(iMadFrame));
    (void)memset(&iMadSynth, 0, sizeof(iMadSynth));
    aMimeTypeList.Add("audio/mpeg");
    aMimeTypeList.Add("audio/x-mpeg");
    aMimeTypeList.Add("audio/mp1");
}

CodecMp3::~CodecMp3()
{
}

TBool CodecMp3::Recognise(const EncodedStreamInfo& aStreamInfo)
{
    if (aStreamInfo.RawPcm()) {
        return false;
    }
    ASSERT(iHeaderBytes == 0);

    iRecogBuf.SetBytes(0);
    iController->Read(iRecogBuf, iRecogBuf.MaxBytes());

    if (iRecogBuf.Bytes() > 4) {
        TUint syncFrameOffsetBytes = 0;
        if (Mp3Header::Exists(iRecogBuf, syncFrameOffsetBytes)) {
            iHeaderBytes = syncFrameOffsetBytes;
            return true;
        }
    }
    return false;
}

void CodecMp3::StreamInitialise()
{
    //LOG(kCodec, "CodecMp3::StreamInitialise, syncFrameOffsetBytes: %d\n", iHeaderBytes);

    iSamplesWrittenTotal = 0;
    iHeader = nullptr;
    iTrackOffset = 0;
    iStreamEnded = false;
    mad_stream_init(&iMadStream);
    mad_frame_init(&iMadFrame);
    mad_synth_init(&iMadSynth);

    // Discard bytes preceeding frame start.
    iInput.SetBytes(0);
    if (iHeaderBytes > 0) {
        iController->Read(iInput, iHeaderBytes);
        if (iInput.Bytes() < iHeaderBytes) {
            THROW(CodecStreamEnded);
        }
        iInput.SetBytes(0);
    }

    iController->Read(iInput, kReadReqBytes);
    if (iInput.Bytes() < kReadReqBytes) {
        THROW(CodecStreamEnded);
    }
    ASSERT_DEBUG(iHeader == nullptr);
    iHeader = new Mp3Header(iInput, iHeaderBytes, iController->StreamLength());

    iTrackLengthJiffies = (iHeader->SamplesTotal() * Jiffies::kPerSecond) / iHeader->SampleRate();
    iController->OutputDecodedStream(iHeader->BitRate(), kBitDepth, iHeader->SampleRate(), iHeader->Channels(), iHeader->Name(), iTrackLengthJiffies, 0, false);
}

void CodecMp3::StreamCompleted()
{
    //LOG(kCodec, "CodecMp3::Deinitialise\n");

    delete iHeader;
    iHeader = nullptr;
    iInput.SetBytes(0);
    iHeaderBytes = 0;

    mad_synth_finish(&iMadSynth);
    mad_frame_finish(&iMadFrame);
    mad_stream_finish(&iMadStream);
}

TBool CodecMp3::TrySeek(TUint aStreamId, TUint64 aSample)
{
    TUint64 bytes = 0;
    try {
        bytes = iHeader->SampleToByte(aSample);
    }
    catch (Mp3SampleInvalid&) {
        return false;
    }
    //LOG(kCodec, "CodecMp3::Seek(%lld), byte: %lld\n", aSamples, bytes);
    // FIXME - need to know how much data has been consumed by the container
    //bytes += iController->ContainerSize();
    if (bytes >= iController->StreamLength()) {
        bytes = iController->StreamLength() - 1;    // keep seek within file bounds
    }
    TBool canSeek = iController->TrySeekTo(aStreamId, bytes);
    if (canSeek) {
        iInput.SetBytes(0);
        iSamplesWrittenTotal = aSample;
        iTrackOffset = (aSample * Jiffies::kPerSecond) / iHeader->SampleRate();
        iController->OutputDecodedStream(iHeader->BitRate(), kBitDepth, iHeader->SampleRate(), iHeader->Channels(), iHeader->Name(), iTrackLengthJiffies, aSample, false);
    }
    return canSeek;
}

void CodecMp3::Process()
{
    //LOG(kCodec, "CodecMp3::Process\n");

    TBool newStreamStarted = false;

    // Step 1: If this is the first time (buffer == 0) or the previous
    // iteration didn't have enough data in iInput for libmad to decode it
    // (MAD_ERROR_BUFLEN) then we get more data for the iInput buffer
    if (iMadStream.buffer == 0 || iMadStream.error == MAD_ERROR_BUFLEN) {
        //LOG(kCodec, "CodecMp3::Process iMadStream.buffer: %d, error: %s\n", iMadStream.buffer, mad_stream_errorstr(&iMadStream));

        // mad does not necessarily consume all bytes of the input buffer.
        // If the last frame in the buffer does not entirely fit, then that
        // frame's start is pointed to by mad_stream::next_frame.  This can
        // happen when mad_frame_decode returns an error and leaves
        // next_frame pointing to the frame after the bad frame
        if (iMadStream.next_frame != nullptr) {
            //LOG(kCodec, "CodecMp3::Process next_frame != 0\n");
            TUint prevBytes = iMadStream.bufend - iMadStream.next_frame;
            (void)memmove((void*)iInput.Ptr(), iMadStream.next_frame, prevBytes);
            iInput.SetBytes(prevBytes);
        }

        try {
            //LOG(kCodec, "CodecMp3::Process calling iController->Read() for: %d bytes sample: %lld\n", kReadReqBytes - iInput.Bytes(), iSamplesWrittenTotal);
            TUint bytesToRead = kReadReqBytes - iInput.Bytes();
            if (bytesToRead) { // FIXME - dubious test
                iController->Read(iInput, bytesToRead);
                if (iInput.Bytes() < bytesToRead) {
                    THROW(CodecStreamEnded);
                }
            }
        }

        // When decoding the last frame of a file, it must be followed by MAD_BUFFER_GUARD
        // zero bytes if one wants to decode that last frame.  When we detect the end of a
        // stream, we append the zero bytes and decode as normal.  Then once done decoding
        // the final frame, we'll rethrow the exception and end this track normally.
        catch (CodecStreamStart&) {
            newStreamStarted = true;
            //LOG(kCodec, "CodecMp3::Process caught CodecStreamStart\n");
        }
        catch (CodecStreamEnded&) {
            iStreamEnded = true;
            //LOG(kCodec, "CodecMp3::Process caught CodecStreamEnded\n");
        }
        if (newStreamStarted || iStreamEnded) {
            ASSERT_DEBUG(iInput.Bytes() + MAD_BUFFER_GUARD < iInput.MaxBytes()); // FIXME - volkano just assumes this holds true.  Why is that safe?
            TUint8* ptr = (TUint8*)iInput.Ptr() + iInput.Bytes();
            (void)memset(ptr, 0, MAD_BUFFER_GUARD);
            iInput.SetBytes(iInput.Bytes() + MAD_BUFFER_GUARD);
        }

        mad_stream_buffer(&iMadStream, iInput.Ptr(), iInput.Bytes());
        iMadStream.error = (mad_error)0;
    }

    // Decode the next mpeg frame.  mad_frame_decode returns a non zero value on error
    TInt ret = mad_frame_decode(&iMadFrame, &iMadStream);
    if (ret) {
        if (MAD_RECOVERABLE(iMadStream.error)) {
            //LOG(kCodec, "CodecMp3::Process recoverable error: %s\n", mad_stream_errorstr(&iMadStream));
            return;
        }
        else {
            if (iMadStream.error == MAD_ERROR_BUFLEN && !(newStreamStarted || iStreamEnded)) {
                // If buffer was too small to decode then return now and get more data
                // the next time we're called.  If the stream has ended and the buffer
                // is too small, then the file is corrupt (truncated)
                return;
            }
            else {
                //LOG(kCodec, "CodecMp3::Process unrecoverable error: %s eos: %d\n", mad_stream_errorstr(&iMadStream), iEos);
                THROW(CodecStreamCorrupt);
            }
        }
    }
        
    // Once frame is decoded, synthesize to pcm samples.  
    (void)mad_synth_frame(&iMadSynth, &iMadFrame);
    TUint channels = iHeader->Channels();
    TUint samplesToWrite = iMadSynth.pcm.length;
    //LOG(kCodec, "CodecMp3::Process samplesToWrite: %d, written: %lld\n", samplesToWrite, iSamplesWrittenTotal);

    // limit output of samples to total defined in header, unless its a live stream
    if (iHeader->SamplesTotal()) {
//        const TUint64 remaining = (iHeader->SamplesTotal() - iSamplesWrittenTotal);
        if (samplesToWrite > (iHeader->SamplesTotal() - iSamplesWrittenTotal)) {
            samplesToWrite = (TUint)(iHeader->SamplesTotal() - iSamplesWrittenTotal);
        }
    }

    TUint pcmIndex = 0;
    do {
        TUint bytes = samplesToWrite * (kBitDepth/8) * channels;
        TUint samples = samplesToWrite;
        TUint outputSpace = iOutput.MaxBytes() - iOutput.Bytes();
        if (bytes > outputSpace) {
            samples = outputSpace / (channels * (kBitDepth/8));
            bytes = samples * (kBitDepth/8) * channels;
        }
        TByte* dst = const_cast<TByte*>(iOutput.Ptr()) + iOutput.Bytes();
        for (TUint i=pcmIndex; i<pcmIndex+samples; i++) {
            for (TUint j=0; j<channels; j++) {
                TUint subsample = fixedToPcm(iMadSynth.pcm.samples[j][i]);
                // output is always 24-bit
                *dst++ = (TByte)(subsample >> 24);
                *dst++ = (TByte)(subsample >> 16);
                *dst++ = (TByte)(subsample >> 8);
            }
        }
        pcmIndex += samples;
        iOutput.SetBytes(iOutput.Bytes() + bytes);
        // only output audio when we have data for a full-sized msg.
        // any data not output now will be picked up the next time round
        if (iOutput.MaxBytes() - iOutput.Bytes() < (kBitDepth/8) * channels) {
            iTrackOffset += iController->OutputAudioPcm(iOutput, channels, iHeader->SampleRate(),
                                                        kBitDepth, EMediaDataEndianBig, iTrackOffset);
            iOutput.SetBytes(0);
        }
        iSamplesWrittenTotal += samples;
        samplesToWrite -= samples;
    } while (samplesToWrite > 0);

    // now propogate any end of stream exception
    // first check we have processed remaining frames of this stream
    if ((iMadStream.md_len == 0) && (iStreamEnded || newStreamStarted)) {
        if (iOutput.Bytes() > 0) { // only output if there is audio remaining
            iController->OutputAudioPcm(iOutput, channels, iHeader->SampleRate(),
                                        kBitDepth, EMediaDataEndianBig, iTrackOffset);
        }
        if (newStreamStarted) {
            THROW(CodecStreamStart);
        }
        THROW(CodecStreamEnded);
    }
}
