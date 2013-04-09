#ifndef HEADER_PIPELINE_CODEC_MPEG4
#define HEADER_PIPELINE_CODEC_MPEG4

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecController.h>

EXCEPTION(MediaMpeg4FileInvalid);

namespace OpenHome {
namespace Media {
namespace Codec {

class Mpeg4Box
{
public:
    Mpeg4Box(IContainer& aContainer, Mpeg4Box* aParent = NULL, const TChar* aIdName = NULL, TUint aOffset = 0);
    Mpeg4Box(ICodecController& aController, Mpeg4Box* aParent = NULL, const TChar* aIdName = NULL);
    Mpeg4Box(const Brx& aBuffer, Mpeg4Box* aParent = NULL, const TChar* aIdName = NULL, TUint aOffset = 0);
    ~Mpeg4Box();
    void Read(Bwx& aData, TUint aBytes);
    void SkipEntry();
    void Skip(TUint32 aBytes);
    TBool Empty();
    TBool Match(const TChar* aIdName);
    TBool FindBox(const TChar* aIdName);
    const Brx& Id() const;
    TUint BoxSize() const;
    TUint BytesRead() const;
    TUint Offset() const;
    TUint FileOffset() const;
private:
    void ExtractHeaderId();
    void Reset();
    void UpdateBytesRead(TUint aBytes);
private:
    IContainer* iContainer;
    ICodecController* iController;
    const Brx* iInput;
    Mpeg4Box *iParent;
    Bws<4> iId;             // ID of box.
    Bws<32> iBuf;           // Local buffer.
    TUint iBytesRead;       // Bytes read for current entry.
    TUint iBoxSize;         // Size of current box.
    TUint iOffset;          // Read offset from start of file.
};

class Mpeg4
{
public:
    Mpeg4(IContainer& aContainer);
    ~Mpeg4();
    TUint ContainerSize() const;
private:
    TUint iContainerSize;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

#endif //HEADER_PIPELINE_CODEC_MPEG4
