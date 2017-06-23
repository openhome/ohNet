#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Av/Scd/ScdMsg.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Scd {

class OhMetadata : private INonCopyable
{
    static const Brn kNsDc;
    static const Brn kNsUpnp;
    static const Brn kNsOh;
public:
    static Media::Track* ToTrack(const OpenHomeMetadataBuf& aMetadata,
                                 Media::TrackFactory& aTrackFactory);
    static void ToDidlLite(const OpenHomeMetadataBuf& aMetadata, Bwx& aDidl);
private:
    OhMetadata(const OpenHomeMetadataBuf& aMetadata);
    void Parse();
    TBool TryGetValue(const TChar* aKey, Brn& aValue) const;
    TBool TryGetValue(const Brx& aKey, Brn& aValue) const;
    void TryAddAttribute(const TChar* aOhKey, const TChar* aDidlAttr);
    void TryAddTag(const Brx& aOhKey, const Brx& aDidlTag,
                   const Brx& aNs, const Brx& aRole);
    void TryAppendTag(const Brx& aDidlTag, const Brx& aNs,
                      const Brx& aRole, const Brx& aValue);
    void TryAppend(const TChar* aStr);
    void TryAppend(const Brx& aBuf);
private:
    const OpenHomeMetadataBuf& iMetadata;
    Media::BwsTrackUri iUri;
    Media::BwsTrackUri iMetaDataDidl;
};

} // namespace Scd
} // namespace OpenHome
