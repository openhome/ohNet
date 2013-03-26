#ifndef HEADER_PIPELINE_CODEC_MP3
#define HEADER_PIPELINE_CODEC_MP3

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Msg.h>

class Mp3Header;
struct mad_stream;
struct mad_frame;
struct mad_synth;

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecMp3 : public CodecBase
{
public:
    CodecMp3();
private: // from CodecBase
    ~CodecMp3();
    TBool Recognise(const Brx& aData);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private:
    static const TUint kReadReqBytes = 4096;
    mad_stream* iMadStream;
    mad_frame*  iMadFrame;
    mad_synth*  iMadSynth;
    TUint64     iSamplesWrittenTotal;
    Mp3Header*  iHeader;
    TUint       iHeaderBytes;
    Bwh         iInput;
    TUint64     iTrackLengthJiffies;
    TUint64     iTrackOffset;
    Bws<DecodedAudio::kMaxBytes> iOutput;
    TBool       iStreamEnded;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_CODEC_MP3
