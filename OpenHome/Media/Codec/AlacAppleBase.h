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
protected:
    static const TUint kMaxSamplesPerFrame = 4096;  // ALAC files typically use 4096 samples per frame.
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
    AudioDataEndian Endianness() const;
protected:
    /*
     * ALACDecoder::Init() allocates memory that is only freed upon deleting
     * the decoder object. So, must new/delete ALACDecoder in StreamInitialise()
     * and StreamCompleted(), respectively, to avoid memory leaks.
     */
    ALACDecoder* iDecoder;
    Bws<kMaxSamplesPerFrame*kMaxByteDepth*kMaxChannels> iInBuf;
    Bws<kMaxSamplesPerFrame*kMaxByteDepth*kMaxChannels> iDecodedBuf;
    TUint iFrameLength;
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

