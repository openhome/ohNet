#ifndef HEADER_PIPELINE_CODEC_ID3V2
#define HEADER_PIPELINE_CODEC_ID3V2

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Media/Codec/Container.h>

EXCEPTION(MediaCodecId3v2NotFound);

namespace OpenHome {
namespace Media {
namespace Codec {

class Id3v2
{
public:
    Id3v2(IContainer& aContainer);
    TUint32 ContainerSize() const;
private:
	TUint32 iContainerSize;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_CODEC_ID3V2
