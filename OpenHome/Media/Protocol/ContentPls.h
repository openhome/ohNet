#ifndef HEADER_PIPELINE_CONTENT_PLS
#define HEADER_PIPELINE_CONTENT_PLS

#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Stream.h>

namespace OpenHome {
namespace Media {

class ContentPls : public ContentProcessor
{
public:
private: // from ContentProcessor
    TBool Recognise(const Brx& aUri, const Brx& aMimeType, const Brx& aData);
    ProtocolStreamResult Stream(Srx& aReader, TUint64 aRemainingBytes, TUint aMaxReadBytes);
private:
    Brn ReadLine(Srx& aReader);
};

} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_CONTENT_PLS
