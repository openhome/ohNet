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
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
private:
    void ProcessHeader(const Brx& aHeader);
    void SendMsgDecodedStream(TUint64 aStartSample);
private:
    static const TUint kHeaderBytes = 44;
    Bws<DecodedAudio::kMaxBytes> iReadBuf;
    TUint iNumChannels;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iAudioBytesTotal;
    TUint iAudioBytesRemaining;
    TUint iBitRate;
    TUint64 iTrackOffset;
    TUint64 iTrackLengthJiffies;

};

}; // namespace Codec
}; // namespace Media
}; // namespace OpenHome

#endif // HEADER_PIPELINE_CODEC_WAV
