#ifndef HEADER_PIPELINE_CODEC_ALAC_BASE
#define HEADER_PIPELINE_CODEC_ALAC_BASE

#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Codec/AlacBase.h>
#include <OpenHome/Media/Codec/Mpeg4.h>

extern "C" {
#include <decomp.h>
}

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecAlacBase : public CodecBase
{
public:
    static const Brn kCodecAlac;
public:
    CodecAlacBase();
    ~CodecAlacBase();
protected: // from CodecBase
    TBool SupportsMimeType(const Brx& aMimeType);
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private:
    void BigEndianData(TUint toWrite, TUint aSamplesWritten);
protected:
    // FIXME - implement StreamInitialise() (from CodecBase) here, which does some work and calls into a virtual void Initialise() = 0; that deriving classes must implement (e.g., for ALAC codec to initialise sample size table)
    void Initialise();
    void Decode();
    void OutputFinal();
protected:
    alac_file *alac;
    TBool iStreamStarted;
    TBool iStreamEnded;
    Bws<4*10240> iInBuf;          // how big can these go and need to go ?
    TUint iChannels;
    TUint iBitDepth;          // alac decoder may redefine the bit depth
    TUint iBytesPerSample;
    TUint iTimescale;
    TUint64 iSamplesWrittenTotal;
    TUint64 iTrackLengthJiffies;
    TUint64 iTrackOffset;
private:
    Bws<16*10240> iDecodedBuf;
    Bws<DecodedAudio::kMaxBytes> iOutBuf;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_CODEC_ALAC_BASE
