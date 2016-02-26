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
private:
    static const TUint kMaxByteDepth = 4;
    static const TUint kTypicalSamplesPerFrame = 4096;
protected:
    static const TUint kMaxChannels = 2;
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
    Bws<kTypicalSamplesPerFrame*kMaxByteDepth*kMaxChannels> iInBuf;
    Bws<kTypicalSamplesPerFrame*kMaxByteDepth*kMaxChannels> iDecodedBuf;
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

