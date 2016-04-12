#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Codec/CodecController.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecAiffBase : public CodecBase
{
protected:
    CodecAiffBase(const TChar* aName);
    ~CodecAiffBase();
private: // from CodecBase
    TBool Recognise(const EncodedStreamInfo& aStreamInfo);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
protected:
    TUint FindChunk(const Brx& aChunkId);
    virtual TUint GetCommChunkHeader() = 0;
    virtual void ProcessCommChunkExtra(); // for e.g., getting compression format for AIFC
private:
    TUint DetermineRate(TUint16 aExponent, TUint32 aMantissa);
    void ProcessHeader();
    void ProcessFormChunk();
    void ParseCommChunk(TUint aChunkSize); // helper for ProcessCommChunk
    void ProcessCommChunk();
    void ProcessSsndChunk();
    void SendMsgDecodedStream(TUint64 aStartSample);
protected:
    Bws<DecodedAudio::kMaxBytes> iReadBuf;
    TUint64 iTrackStart;
    AudioDataEndian iEndian;
private:
    static const TUint kUnder65kHz = 0x4013;
    static const TUint k11127Hz = 11127; // Macintosh "close enough" sample rate
    static const TUint k11025Hz = 11025;
    static const TUint k22255Hz = 22255; // Macintosh "close enough" sample rate
    static const TUint k22050Hz = 22050;
    Brn iName;
    TUint iNumChannels;
    TUint64 iSamplesTotal;
    TUint iBitDepth;
    TUint iSampleRate;
    TUint iBitRate;
    TUint iAudioBytesTotal;
    TUint iAudioBytesRemaining;
    TUint64 iTrackLengthJiffies;
    TUint64 iTrackOffset;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

