#ifndef HEADER_PIPELINE_PROTOCOL_TONE
#define HEADER_PIPELINE_PROTOCOL_TONE

#include <OpenHome/Media/Protocol/Protocol.h>
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
    void Set(TUint16 aBitsPerSample, TUint aSampleRate, TUint aPitch, TUint16 aNumChannels, TUint aDuration);

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

class ToneGenerator
{
public:
    virtual ~ToneGenerator() { }
    TBool Recognise(const Brx& aName) const;
    virtual TInt32 Generate(TUint aOffset, TUint aMaxOffset) = 0;  // really 24-bit max
protected:
    ToneGenerator(const TChar* aName);
private:
    Brn iName;
};

#ifdef DEFINE_DEBUG
class ToneGeneratorPattern : public ToneGenerator
{
public:
    ToneGeneratorPattern();
    TInt32 Generate(TUint aOffset, TUint aMaxOffset);  // from ToneGenerator
};
#endif  // DEFINE_DEBUG

class ToneGeneratorSilence : public ToneGenerator
{
public:
    ToneGeneratorSilence();
    TInt32 Generate(TUint aOffset, TUint aMaxOffset);  // from ToneGenerator
};


class ToneGeneratorSquare : public ToneGenerator
{
public:
    ToneGeneratorSquare();
    TInt32 Generate(TUint aOffset, TUint aMaxOffset);  // from ToneGenerator
};

class ProtocolTone : public Protocol
{
public:
    ProtocolTone(Environment& aEnv);
    ~ProtocolTone();
#ifdef DEFINE_DEBUG
private:
    void HexDump(const TByte *aBase, TUint aSize) const;
#endif  // DEFINE_DEBUG
private: // from Protocol
    ProtocolStreamResult Stream(const Brx& aUri);
private:  // from IStreamHandler
    TUint TryStop(TUint aTrackId, TUint aStreamId);
private:
    std::vector<ToneGenerator*> iToneGenerators;
    // 1[ms] x 192000[Hz] x 8[channels] x 24[bit/channel] x 1/8[B/bit] = 4,608[B]
    Bws<4608> iAudioBuf;
};

} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL_TONE
