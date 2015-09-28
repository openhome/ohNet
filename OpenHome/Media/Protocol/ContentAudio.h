#pragma once

#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Media/SupplyAggregator.h>

namespace OpenHome {
namespace Media {

class MsgFactory;
class IPipelineElementDownstream;

class ContentAudio : public ContentProcessor
{
private:
    static const TUint kMaxReadBytes = EncodedAudio::kMaxBytes;
public:
    ContentAudio(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream);
    ~ContentAudio();
private: // from ContentProcessor
    TBool Recognise(const Brx& aUri, const Brx& aMimeType, const Brx& aData);
    ProtocolStreamResult Stream(IReader& aReader, TUint64 aTotalBytes);
private:
    SupplyAggregator* iSupply;
};

} // namespace Media
} // namespace OpenHome

