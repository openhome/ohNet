#ifndef HEADER_PIPELINE_CONTENT_M3U
#define HEADER_PIPELINE_CONTENT_M3U

#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Stream.h>

namespace OpenHome {
namespace Media {

class ContentM3u : public ContentProcessor
{
private: // from ContentProcessor
    TBool Recognise(const Brx& aUri, const Brx& aMimeType, const Brx& aData);
    ProtocolStreamResult Stream(Srx& aReader, TUint64 aTotalBytes, TUint64& aOffset);
};

} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_CONTENT_M3U
