#include <OpenHome/Media/Codec/AiffBase.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Media/MimeTypeList.h>

#include <string.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecAifc : public CodecAiffBase
{
public:
    CodecAifc(IMimeTypeList& aMimeTypeList);
    ~CodecAifc();
private: // from CodecAiffBase
    TUint GetCommChunkHeader();
    void ProcessCommChunkExtra();
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewAifc(IMimeTypeList& aMimeTypeList)
{ // static
    return new CodecAifc(aMimeTypeList);
}



CodecAifc::CodecAifc(IMimeTypeList& aMimeTypeList)
    : CodecAiffBase("AIFC")
{
    aMimeTypeList.Add("audio/aifc");
    aMimeTypeList.Add("audio/x-aifc");
}

CodecAifc::~CodecAifc()
{
}

TUint CodecAifc::GetCommChunkHeader()
{
    // format of AIFC header taken from http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/AIFF/Docs/AIFF-C.9.26.91.pdf

    TUint commChunkBytes = FindChunk(Brn("COMM"));
    if (commChunkBytes < 22) {
        THROW(CodecStreamCorrupt);
    }
    return commChunkBytes;
}

void CodecAifc::ProcessCommChunkExtra()
{
    const TByte* commData = iReadBuf.Ptr();
    //Apple's proprietary aifc compression format where the 'compression' is Little endian
    if ((strncmp((const TChar*)commData+18, "sowt", 4) == 0)
            || (strncmp((const TChar*)commData+18, "SOWT", 4) == 0)) {
        iEndian = EMediaDataEndianLittle;
    }
    else if (strncmp((const TChar*)commData+18, "NONE", 4) != 0) {
        THROW(CodecStreamFeatureUnsupported);   // unsupported compression
    }
}
