#pragma once

namespace OpenHome {
namespace Media {
    class IMimeTypeList;
namespace Codec {

class ContainerBase;

class ContainerFactory
{
public:
    static ContainerBase* NewId3v2();
    static ContainerBase* NewMpeg4(IMimeTypeList& aMimeTypeList);
    static ContainerBase* NewMpegTs(IMimeTypeList& aMimeTypeList);
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome
