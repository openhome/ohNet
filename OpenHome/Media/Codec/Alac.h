#ifndef HEADER_PIPELINE_CODEC_ALAC
#define HEADER_PIPELINE_CODEC_ALAC

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Media/Msg.h>

#include <alac_decoder/alac.h>

extern void alac_free_buffers(alac_file *alac);

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecAlac : public CodecBase
{
public:
    static const Brn kCodecAlac;
public:
    CodecAlac();
    ~CodecAlac();
private: // from CodecBase
    TBool Recognise(const Brx& aData);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private:
    void BigEndianData(TUint toWrite, TUint aSamplesWritten);
private:
    Bws<4*10240> iInBuf;          // how big can these go and need to go ?
    Bws<16*10240> iDecodedBuf;
    Bws<DecodedAudio::kMaxBytes> iOutBuf;
    Mpeg4MediaInfo* iMp4;
    alac_file *alac;

    TUint16 iBitDepth;      // alac decoder may redefine the bit depth
    TUint16 iBytesPerSample;
    TUint64 iCurrentSample;
    TUint64 iSamplesWrittenTotal;
    TUint64 iTrackLengthJiffies;
    TUint64 iTrackOffset;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_CODEC_ALAC
