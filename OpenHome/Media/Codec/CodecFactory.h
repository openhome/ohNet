#pragma once

namespace OpenHome {
namespace Av {
    class OhmMsgFactory;
}
namespace Media {
    class IMimeTypeList;
namespace Codec {

class CodecBase;

class CodecFactory
{
public:
    static CodecBase* NewAac(IMimeTypeList& aMimeTypeList);
    static CodecBase* NewAifc(IMimeTypeList& aMimeTypeList);
    static CodecBase* NewAiff(IMimeTypeList& aMimeTypeList);
    static CodecBase* NewAlacApple(IMimeTypeList& aMimeTypeList);
    static CodecBase* NewAdts(IMimeTypeList& aMimeTypeList);
    static CodecBase* NewFlac(IMimeTypeList& aMimeTypeList);
    static CodecBase* NewMp3(IMimeTypeList& aMimeTypeList);
    static CodecBase* NewPcm();
    static CodecBase* NewRaop();
    static CodecBase* NewVorbis(IMimeTypeList& aMimeTypeList);
    static CodecBase* NewWav(IMimeTypeList& aMimeTypeList);
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

