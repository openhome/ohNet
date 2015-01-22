#ifndef HEADER_PIPELINE_CODEC_ID3V2
#define HEADER_PIPELINE_CODEC_ID3V2

#include <OpenHome/Types.h>
#include <OpenHome/Media/Codec/Container.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class Id3v2 : public ContainerBase
{
public:
    Id3v2();
public: // from IRecogniser
    TBool Recognise(Brx& aBuf);
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
private: // from IStreamHandler
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
private:
    static const TUint kRecogniseBytes = 10;
    TUint iSize;
    TUint iTotalSize;
    Bws<kRecogniseBytes> iBuf;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_CODEC_ID3V2
