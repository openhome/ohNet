#ifndef HEADER_PIPELINE_CODEC_MPEG4
#define HEADER_PIPELINE_CODEC_MPEG4

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Media/Codec/Container.h>

EXCEPTION(MediaMpeg4FileInvalid);
EXCEPTION(MediaContainerMpeg4Found);

namespace OpenHome {
namespace Media {
namespace Codec {

class Mpeg4
{
public:
    Mpeg4(Selector& aSelector);
    ~Mpeg4();
    TUint32 ContainerSize() const;
private:
	TUint32 iContainerSize;
};


class Mpeg4Box
{
public:
    Mpeg4Box(Selector& aSelector, TUint32 aOffset, TUint32 aBoxSize, const TChar* aIdName = NULL);
    ~Mpeg4Box();
    void ExtractHeaderId();
    void Read(Bwx& aData, TUint aBytes);
    void SkipEntry();
    void Skip(TUint32 aBytes);
    void AddBytesRead(TUint32 aBytes);
    TBool Match(const TChar* aIdName);
    TBool FindBox(const TChar* aIdName);
    TBool Empty();

    const Brx& Id() const { return iId; }
    TUint32 DataBytes() const { return iDataBytes; }
    TUint32 BytesRead() const { return iBoxBytesRead + iBytesRead; }
    TUint32 TotalOffset() const { return iOffset + iBoxBytesRead + iBytesRead; }

private:
    Selector& iSelector;
    Bws<4> iId;
    TUint32 iOffset;                // offset from start of file - required for Peek()
    TUint32 iDataBytes;
    TUint32 iBytesRead;             // bytes read for current entry
    TUint32 iBoxBytesRead;          // bytes read for current box
    TUint32 iBoxSize;               // size of current box
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif //HEADER_PIPELINE_CODEC_MPEG4
