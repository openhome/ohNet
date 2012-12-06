#ifndef HEADER_PIPELINE_CODEC_RAOP_CONTAINER
#define HEADER_PIPELINE_CODEC_RAOP_CONTAINER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Media/Codec/Container.h>

EXCEPTION(MediaCodecRaopNotFound);

namespace OpenHome {
namespace Media {
namespace Codec {

class RaopContainer
{
public:
	RaopContainer(Selector& aSelector);
    TUint32 ContainerSize() const;
private:
	TUint32 iContainerSize;
};

}; // namespace Codec
}; // namespace Media
}; // namespace OpenHome

#endif  // HEADER_PIPELINE_CODEC_RAOP_CONTAINER
