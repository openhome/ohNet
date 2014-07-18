#ifndef HEADER_CODEC_RAOP
#define HEADER_CODEC_RAOP

#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/AlacBase.h>
#include <OpenHome/Types.h>

namespace OpenHome {
namespace Av {

class CodecRaop : public Media::Codec::CodecAlacBase
{
public:
    CodecRaop();
    ~CodecRaop();
private: // from CodecBase
    TBool Recognise();
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_CODEC_RAOP
