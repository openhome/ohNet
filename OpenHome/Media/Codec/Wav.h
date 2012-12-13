#ifndef HEADER_PIPELINE_CODEC_WAV
#define HEADER_PIPELINE_CODEC_WAV

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecWav : public CodecBase
{
public:
    CodecWav();
private: // from CodecBase
    TBool Recognise(const Brx& aData);
    void Process();
private:
    void ProcessHeader(const Brx& aHeader, TUint& aNumChannels, TUint& aSampleRate, TUint& aBitDepth, TUint& aAudioBytes);
private:
    Bws<DecodedAudio::kMaxBytes> iReadBuf;
};

}; // namespace Codec
}; // namespace Media
}; // namespace OpenHome

#endif // HEADER_PIPELINE_CODEC_WAV
