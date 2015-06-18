#include <OpenHome/Media/Codec/AiffBase.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>

#include <string.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecAiff : public CodecAiffBase
{
public:
    CodecAiff();
    ~CodecAiff();
private: // from CodecAiffBase
    TUint GetCommChunkHeader();
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewAiff()
{ // static
    return new CodecAiff();
}



CodecAiff::CodecAiff()
    : CodecAiffBase("AIFF")
{
}

CodecAiff::~CodecAiff()
{
}

TUint CodecAiff::GetCommChunkHeader()
{
    // format of AIFF header taken from http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/AIFF/Docs/AIFF-1.3.pdf

    TUint commChunkBytes = FindChunk(Brn("COMM"));
    if (commChunkBytes != 18) {
        THROW(CodecStreamCorrupt);
    }
    return commChunkBytes;
}
