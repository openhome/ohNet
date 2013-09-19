#ifndef HEADER_PIPELINE_CODEC_AIFF_BASE
#define HEADER_PIPELINE_CODEC_AIFF_BASE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Codec/CodecController.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecAiffBase : public CodecBase
{
public:
    CodecAiffBase(EMediaDataEndian aEndian);
    ~CodecAiffBase();
private: // from CodecBase
    TBool SupportsMimeType(const Brx& aMimeType);
    TBool Recognise(const Brx& aData) = 0;
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
protected:
    virtual void ProcessHeader() = 0;
    TUint FindChunk(const Brx& aChunkId);
    TUint DetermineRate(TUint16 aExponent, TUint32 aMantissa);
private:
    void SendMsgDecodedStream(TUint64 aStartSample);
protected:
    Bws<DecodedAudio::kMaxBytes> iReadBuf;
    TUint iNumChannels;
    TUint64 iSamplesTotal;
    TUint iBitDepth;
    TUint iSampleRate;
    TUint iBitRate;
    TUint iAudioBytesTotal;
    TUint iAudioBytesRemaining;
    TUint64 iTrackStart;
    TUint64 iTrackLengthJiffies;
private:
    EMediaDataEndian iEndian;
    TUint64 iTrackOffset;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_CODEC_AIFF_BASE
