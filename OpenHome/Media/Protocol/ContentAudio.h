#ifndef HEADER_PIPELINE_CONTENT_AUDIO
#define HEADER_PIPELINE_CONTENT_AUDIO

#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Stream.h>

namespace OpenHome {
namespace Media {

class ContentAudio : public ContentProcessor
{
public:
    ContentAudio(ISupply& aSupply);
private: // from ContentProcessor
    TBool Recognise(const Brx& aUri, const Brx& aMimeType, const Brx& aData);
    ProtocolStreamResult Stream(IProtocolReader& aReader, TUint64 aTotalBytes);
private:
    ISupply& iSupply;
};

} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_CONTENT_AUDIO
