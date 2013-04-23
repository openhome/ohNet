#ifndef HEADER_PIPELINE_CODEC_WMA
#define HEADER_PIPELINE_CODEC_WMA

#include <OpenHome/Media/Codec/Container.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecWma : public CodecBase
{
public:
    static const Brn kCodecWma;
public:
    CodecWma();
    ~CodecWma();
    void CopyToBigEndian(TUint aSamples, TUint aBytesPerSample);
    TUint32 Read(const TUint8 **aDataPtr, TUint32 aBytes, TUint64 aOffset, TBool aPeek);
private:
    private: // from CodecBase
    TBool Recognise(const Brx& aData);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private:
    Bws<EncodedAudio::kMaxBytes> iRecogBuf;
    Bws<4*1024> iInBuf;          // how big can these go and need to go ?
    Bws<DecodedAudio::kMaxBytes> iDecodedBuf;
    Bws<DecodedAudio::kMaxBytes> iOutBuf;

    TUint64 iWmaReadOffset;
    TUint32 iPcmSamples;
    TUint32 iSampleRate;
    TUint32 iBytesPerSec;
    TUint32 iBitrate;
    TUint32 iDuration;
    TUint16 iChannels;
    TUint16 iBytesPerSample;
    TUint16 iBitDepth;
    TUint16 iBitStorage;
    TUint64 iStartSample;
    TUint64 iSamplesTotal;
    TUint64 iTotalSamplesOutput;
    TUint64 iSeekOffset;
    TUint64 iTrackLengthJiffies;
    TUint64 iTrackOffset;
};

} //namespace Codec
} //namespace Media
} //namespace OpenHome

#endif //HEADER_PIPELINE_CODEC_WMA
