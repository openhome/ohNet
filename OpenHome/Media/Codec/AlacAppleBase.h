#pragma once

#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
#include <ALACDecoder.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecAlacAppleBase : public CodecBase
{
public:
    static const Brn kCodecAlac;
protected:
    CodecAlacAppleBase(const TChar* aId);
    ~CodecAlacAppleBase();
protected: // from CodecBase
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
protected:
    // FIXME - implement StreamInitialise() (from CodecBase) here, which does some work and calls into a virtual void Initialise() = 0; that deriving classes must implement (e.g., for ALAC codec to initialise sample size table)
    void Initialise();
    void Decode();
private:
    static EMediaDataEndian Endianness();
protected:
    ALACDecoder iDecoder;
    Bws<4096*2*2> iInBuf;
    Bws<4096*2*2> iDecodedBuf;  // Typical alac frame samples * bit depth * channels.
    TUint iChannels;
    TUint iBitDepth;
    TUint iBytesPerSample;
    TUint iSampleRate;
    TUint64 iSamplesWrittenTotal;
    TUint64 iTrackLengthJiffies;
    TUint64 iTrackOffset;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

