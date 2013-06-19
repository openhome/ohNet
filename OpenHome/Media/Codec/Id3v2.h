#ifndef HEADER_PIPELINE_CODEC_ID3V2
#define HEADER_PIPELINE_CODEC_ID3V2

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/Codec/Container.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class Id3v2 : public ContainerBase
{
public:
    Id3v2();
public: // from ContainerBase
    void Initialise();
    TBool Recognise();
    TUint Size();
    TBool AppendDuringSeek();
    TUint Process();
    TUint Split();
private:
    TUint32 iSize;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_CODEC_ID3V2
