#ifndef HEADER_PIPELINE_CODEC_RAOP_CONTAINER
#define HEADER_PIPELINE_CODEC_RAOP_CONTAINER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecInitContainer.h>

EXCEPTION(MediaCodecRaopNotFound);

namespace OpenHome {
namespace Media {
namespace Codec {

class Mpeg4MediaInfoBase
{
public:
    RaopContainer(ICodecController& aController);
    ~RaopContainer();
public:
    virtual const Brx& CodecSpecificData();
    virtual TUint32 SampleRate();
    virtual TUint32 Timescale();
    virtual TUint16 Channels();
    virtual TUint16 BitDepth();
    virtual TUint64 Duration();
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_CODEC_RAOP_CONTAINER
