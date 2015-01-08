#ifndef HEADER_PIPELINE_PROTOCOL_TONE
#define HEADER_PIPELINE_PROTOCOL_TONE

#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Supply.h>

EXCEPTION(ToneUriParseError);

namespace OpenHome {
namespace Media {

// audio parameters specifically for tone generation in RIFF-WAVE format
// c'tors and (in-)equality operators allow terser test implementation
class ToneParams
{
public:
    ToneParams();
    ToneParams(TUint aBitsPerSample, TUint aSampleRate, TUint aPitch, TUint aNumChannels, TUint aDuration);
    void Set(TUint aBitsPerSample, TUint aSampleRate, TUint aPitch, TUint aNumChannels, TUint aDuration);
    TUint BitsPerSample() const { return iBitsPerSample; }
    TUint SampleRate() const { return iSampleRate; }
    TUint Pitch() const { return iPitch; }
    TUint NumChannels() const { return iNumChannels; }
    TUint DurationSeconds() const { return iDuration; }
private:
    TUint iBitsPerSample;
    TUint iSampleRate;
    TUint iPitch;
    TUint iNumChannels;
    TUint iDuration;
};

inline bool operator==(const ToneParams& one, const ToneParams& other)
{
    return (one.BitsPerSample() == other.BitsPerSample())
        && (one.SampleRate() == other.SampleRate())
        && (one.Pitch() == other.Pitch())
        && (one.NumChannels() == other.NumChannels())
        && (one.DurationSeconds() == other.DurationSeconds());
}

inline bool operator!=(const ToneParams& one, const ToneParams& other)
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
    virtual TBool Recognise(const Brx& aName) const;
    virtual TInt32 Generate(TUint aOffset, TUint aMaxOffset) = 0;  // must return 24-bit value
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


// .  /|    /|      .
// .   |   / |      .
// .  ~|~~/~~|~~>t  .
// .   | /   |      .
// .   |/    |/     .
class ToneGeneratorSawtooth : public ToneGenerator
{
public:
    ToneGeneratorSawtooth();
    TInt32 Generate(TUint aOffset, TUint aMaxOffset);  // from ToneGenerator
};

// .       /\        .
// .      /  \       .
// .  ~~~/~~~~\~~~>t .
// .    /      \     .
// .  \/        \/   .
class ToneGeneratorTriangle : public ToneGenerator
{
public:
    ToneGeneratorTriangle();
    TInt32 Generate(TUint aOffset, TUint aMaxOffset);  // from ToneGenerator
};

class ToneGeneratorSine : public ToneGenerator
{
public:
    ToneGeneratorSine();
    TInt32 Generate(TUint aOffset, TUint aMaxOffset);  // from ToneGenerator
};

class ToneGeneratorConstant : public ToneGenerator
{
public:
    ToneGeneratorConstant();
private: // from ToneGenerator
    TBool Recognise(const Brx& aName) const;
    TInt32 Generate(TUint aOffset, TUint aMaxOffset);
private:
    mutable TInt32 iValue;
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
    void Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream);
    void Interrupt(TBool aInterrupt);
    ProtocolStreamResult Stream(const Brx& aUri);
    ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes);
private:  // from IStreamHandler
    TUint TryStop(TUint aTrackId, TUint aStreamId);
private:
    Mutex iLock;
    Supply* iSupply;
    std::vector<ToneGenerator*> iToneGenerators;
    // 1[ms] x 192000[Hz] x 8[channels] x 24[bit/channel] x 1/8[B/bit] = 4,608[B]
    Bws<4608> iAudioBuf;
    TUint iStreamId;
    TBool iStop;
    TUint iNextFlushId;
};

} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL_TONE
