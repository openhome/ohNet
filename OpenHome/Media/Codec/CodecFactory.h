#ifndef HEADER_PIPELINE_CODEC_FACTORY
#define HEADER_PIPELINE_CODEC_FACTORY

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecBase;

class CodecFactory
{
public:
    static CodecBase* NewAac();
    static CodecBase* NewAlac();
    static CodecBase* NewAdts();
    static CodecBase* NewFlac();
    static CodecBase* NewRaop();
    static CodecBase* NewVorbis();
    static CodecBase* NewWav();
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_CODEC_FACTORY
