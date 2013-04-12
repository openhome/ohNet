#ifndef HEADER_PIPELINE_CODEC_AAC
#define HEADER_PIPELINE_CODEC_AAC

#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Mpeg4.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class Adts
{
public:
    Adts();
    TBool   ReadHeader(Brn aHeader);
    TUint16 Profile() { return(iProfile); }
    TUint16 ChannelConfig() { return(iChannelConfig); }
    TUint32 SamplingFreq() { return(iSamplingFreq); }
    TUint32 PayloadBytes() { return(iPayloadBytes); }
    TUint32 HeaderBytes() { return(iHeaderBytes); }
    TUint32 StartOffset() { return(iStartOffset); }
    void SetStartOffset(TUint32 aStartOffset) { iStartOffset = aStartOffset; }
    TUint32 PayloadBytesAve() { return iPayloadBytesAve; }
    void SetPayloadBytesAve(TUint32 aPayloadBytesAve) { iPayloadBytesAve = aPayloadBytesAve; }
private:
    TUint8  iProfile;
    TUint8  iChannelConfig;
    TUint32 iSamplingFreq;
    TUint32 iPayloadBytes;
    TUint32 iHeaderBytes;
    TUint32 iStartOffset;
    TUint32 iPayloadBytesAve;
};

class CodecAac : public CodecBase
{
public:
    static const Brn kCodecAac;
public:
    CodecAac();
    ~CodecAac();
private: // from CodecBase
    TBool Recognise(const Brx& aData);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private:
    void ProcessHeader();
    void BigEndianData(TUint toWrite, TUint samplesWritten);
    void ProcessMpeg4();
    void ProcessAdts(TBool aParseOnly);
    void FlushOutput();
    void DecodeFrame(TBool aParseOnly);
    TUint SkipEsdsTag(const TByte& aPtr);

    Brn iName;
    Bws<4*1024> iInBuf;          // how big can these go and need to go ?
    Bws<16*10240> iDecodedBuf;
    Bws<DecodedAudio::kMaxBytes> iOutBuf;
    Mpeg4MediaInfo* iMp4;
    TUint32 iAudioBytes;
    TBool iAacMpeg4Format;
    TUint iFrameCounter;
    Adts iAdts;

    TUint32 iSampleRate;
    TUint32 iBitrateMax;    
    TUint32 iBitrateAverage;
    TUint16 iChannels;
    TUint16 iBytesPerSample;
    TUint16 iBitDepth;
    TUint64 iSamplesTotal;
    TUint64 iCurrentSample;
    TUint64 iTotalSamplesOutput;
    TUint64 iTrackLengthJiffies;
    TUint64 iTrackOffset;

    TBool iNewStreamStarted;
    TBool iStreamEnded;
};

} //namespace Codec
} //namespace Media
} //namespace Linn

#endif //HEADER_PIPELINE_CODEC_AAC
