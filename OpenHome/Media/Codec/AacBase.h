#ifndef HEADER_PIPELINE_CODEC_AAC_BASE
#define HEADER_PIPELINE_CODEC_AAC_BASE

#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>

extern "C" {
#include <defines.h>
#include <typedef.h>
#include <FFR_bitbuffer.h>
#include <sbrdecoder.h>
#include <spline_resampler.h>
#include <aacdecoder.h>
}


namespace OpenHome {
namespace Media {
    class IMimeTypeList;
namespace Codec {

class CodecAacBase : public CodecBase
{
private:
    static const TUint kSamplesPerFrame = 1024; // FIXME - could also be 960.
    static const TUint kInputBufBytes = 4096;   // Input buf size used by third-party decoder examples.
public:
    static const Brn kCodecAac;
protected:
    CodecAacBase(const TChar* aId, IMimeTypeList& aMimeTypeList);
    ~CodecAacBase();
protected: // from CodecBase
    TBool SupportsMimeType(const Brx& aMimeType);
    void StreamInitialise();
    void Process() = 0;
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
protected:
    void InitialiseDecoder();
    void DecodeFrame(TBool aParseOnly);
    void FlushOutput();
private:
    void BigEndianData(TUint toWrite, TUint samplesWritten);
    static void InterleaveSamples(Word16 *pTimeCh0,
                  Word16 *pTimeCh1,
                  Word16 *pTimeOut,
                  Word32  frameSize,
                  Word16 *channels);
private:
    Bws<16*10240> iDecodedBuf;
    Bws<DecodedAudio::kMaxBytes> iOutBuf;
protected:
    Bws<kInputBufBytes> iInBuf;
    TUint iFrameCounter;

    TUint iSampleRate;
    TUint iOutputSampleRate;
    TUint iBitrateMax;
    TUint iBitrateAverage;
    TUint iChannels;
    TUint iBytesPerSample;
    TUint iBitDepth;
    TUint64 iSamplesTotal;
    TUint64 iTotalSamplesOutput;
    TUint64 iTrackLengthJiffies;
    TUint64 iTrackOffset;

    TBool iNewStreamStarted;
    TBool iStreamEnded;
private:
    // Third-party AAC decoder types.
    Flag iFrameOk;                              /*!< frameOk flag */
    Flag iLastFrameOk;
    Word8 iChannelMode;
    struct BIT_BUF iBitBuf;
    struct BIT_BUF* iHBitBuf;
    AACDECODER iAacDecoderInfo;                 /*!< pointer to aacdecoder structure */
    SBRBITSTREAM iStreamSBR[2];                 /*!< pointer to sbr bitstream buffer */
    SBRDECODER iSbrDecoderInfo;                 /*!< pointer to sbrdecoder structure */
    HANDLE_SPLINE_RESAMPLER iSplineResampler;   /*!< pointer to spline resampler instance */
    Word16 iTimeData[4*kSamplesPerFrame];       /*!< Output buffer */
};

} //namespace Codec
} //namespace Media
} //namespace OpenHome

#endif // HEADER_PIPELINE_CODEC_AAC_BASE
