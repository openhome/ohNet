#ifndef HEADER_PIPELINE_PROTOCOL_TONE
#define HEADER_PIPELINE_PROTOCOL_TONE

#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>

EXCEPTION(ToneUriParseError);

namespace OpenHome {
namespace Media {

// audio parameters specifically for tone generation in RIFF-WAVE format
// c'tors and (in-)equality operators allow terser test implementation
struct ToneParams
{
    ToneParams();
    ToneParams(TUint16 aBitsPerSample, TUint aSampleRate, TUint aPitch, TUint16 aNumChannels, TUint aDuration);

    // tighter packing possible, but universal order convention more valuable
    TUint16 bitsPerSample;
    TUint   sampleRate;
    TUint   pitch;
    TUint16 numChannels;
    TUint   duration;
};

inline bool operator==(const struct ToneParams& one, const struct ToneParams& other)
{
    return (one.bitsPerSample == other.bitsPerSample)
        && (one.sampleRate == other.sampleRate)
        && (one.pitch == other.pitch)
        && (one.numChannels == other.numChannels)
        && (one.duration == other.duration);
}

inline bool operator!=(const struct ToneParams& one, const struct ToneParams& other)
{
    return !(one == other);
}

class ToneUriParser
{
    static const TUint kMaxNameBytes = 100;
public:
    ToneUriParser();

    void Parse(const Brx& aUri);  // throws ToneUriParseError

    const ToneParams& Params() const;
    const Brx& Name() const;
private:
    ToneParams iParams;
    Bws<kMaxNameBytes> iName;
};

} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL_TONE
