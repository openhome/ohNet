#include <OpenHome/Av/Scd/Receiver/OhMetadata.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Scd/ScdMsg.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Stream.h>

namespace OpenHome {
namespace Scd {

class Oh2DidlTagMapping
{
public:
    Oh2DidlTagMapping(const TChar* aOhKey, const TChar* aDidlTag, const OpenHome::Brx& aNs)
        : iOhKey(aOhKey)
        , iDidlTag(aDidlTag)
        , iNs(aNs)
        , iRole(OpenHome::Brx::Empty())
    {}
    Oh2DidlTagMapping(const TChar* aOhKey, const TChar* aDidlTag, const OpenHome::Brx& aNs, const TChar* aRole)
        : iOhKey(aOhKey)
        , iDidlTag(aDidlTag)
        , iNs(aNs)
        , iRole(aRole)
    {}
public:
    Brn iOhKey;
    Brn iDidlTag;
    Brn iNs;
    Brn iRole;
};

} // namespace Scd
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Scd;

const Brn OhMetadata::kNsDc("dc=\"http://purl.org/dc/elements/1.1/\"");
const Brn OhMetadata::kNsUpnp("upnp=\"urn:schemas-upnp-org:metadata-1-0/upnp/\"");
const Brn OhMetadata::kNsOh("oh=\"http://www.openhome.org\"");


Media::Track* OhMetadata::ToTrack(const OpenHomeMetadataBuf& aMetadata,
                                  Media::TrackFactory& aTrackFactory)
{ // static
    OhMetadata self(aMetadata);
    try {
        self.Parse();
    }
    catch (BufferOverflow&) {
        self.iMetaDataDidl.Replace(Brx::Empty());
    }
    return aTrackFactory.CreateTrack(self.iUri, self.iMetaDataDidl);
}

void OhMetadata::ToDidlLite(const OpenHomeMetadataBuf& aMetadata, Bwx& aDidl)
{ // static
    OhMetadata self(aMetadata);
    try {
        self.Parse();
        aDidl.Replace(self.iMetaDataDidl);
    }
    catch (BufferOverflow&) {
        aDidl.Replace(Brx::Empty());
    }
}

OhMetadata::OhMetadata(const OpenHomeMetadataBuf& aMetadata)
    : iMetadata(aMetadata)
{
}

void OhMetadata::Parse()
{
    static const Oh2DidlTagMapping kOh2Didl[] = {
        { "artist", "upnp:artist", kNsUpnp },
        { "albumArtist", "upnp:artist", kNsUpnp, "AlbumArtist" },
        { "composer", "upnp:artist", kNsUpnp, "composer" },
        { "conductor", "upnp:artist", kNsUpnp, "conductor" },
        { "narrator", "upnp:artist", kNsUpnp, "narrator" },
        { "performer", "upnp:artist", kNsUpnp, "performer" },
        { "genre", "upnp:genre", kNsUpnp },
        { "albumGenre", "upnp:genre", kNsUpnp },
        { "author", "dc:author", kNsDc },
        { "title", "dc:title", kNsDc },
        { "year", "dc:date", kNsDc },
        { "albumTitle", "upnp:album", kNsUpnp },
        { "albumArtwork", "upnp:albumArtURI", kNsUpnp },
        { "provider", "oh:provider", kNsOh },
        { "artwork", "oh:artwork", kNsOh },
        { "track", "upnp:originalTrackNumber", kNsUpnp },
        { "tracks", "oh:originalTrackCount", kNsOh },
        { "disc", "oh:originalDiscNumber", kNsOh },
        { "discs", "oh:originalDiscCount", kNsOh },
        { "work", "oh:work", kNsOh },
        { "movement", "oh:movement", kNsOh },
        { "show", "oh:show", kNsOh },
        { "episode", "oh:episodeNumber", kNsOh },
        { "episodes", "oh:episodeCount", kNsOh },
        { "published", "oh:published", kNsOh },
        { "website", "oh:website", kNsOh },
        { "location", "oh:location", kNsOh },
        { "details", "oh:details", kNsOh },
        { "extensions", "oh:extensions", kNsOh },
        { "publisher", "dc:publisher", kNsDc },
        { "rating", "upnp:rating", kNsUpnp }
    };
    static const TUint kNumOh2DidlMappings = sizeof kOh2Didl / sizeof kOh2Didl[0];

    iUri.Replace(Brx::Empty());
    iMetaDataDidl.Replace(Brx::Empty());

    Brn val;
    if (TryGetValue("uri", val)) {
        iUri.Replace(val);
    }

    TryAppend("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    TryAppend("<DIDL-Lite xmlns=\"urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/\">");
    TryAppend("<item");
    TryAddAttribute("id", "id");
    TryAppend(" parentID=\"-1\" restricted=\"1\">");
    for (TUint i=0; i<kNumOh2DidlMappings; i++) {
        auto& mapping = kOh2Didl[i];
        TryAddTag(mapping.iOhKey, mapping.iDidlTag, mapping.iNs, mapping.iRole);
    }
    TryAppend("<res");
    if (TryGetValue("duration", val)) {
        TryAppend(" duration=\"");
        TUint duration = Ascii::Uint(val);
        const TUint secs = duration % 60;
        duration /= 60;
        const TUint mins = duration % 60;
        const TUint hours = duration / 60;
        Bws<32> formatted;
        formatted.AppendPrintf("%u:%02u:%02u.000", hours, mins, secs);
        TryAppend(formatted);
        TryAppend("\"");
    }
    if (TryGetValue("bitRate", val)) {
        TryAppend(" bitrate=\"");
        TUint bitRate = Ascii::Uint(val);
        bitRate /= 8; // DIDL-Lite bitrate attribute actually refers to a byte rate!
        Bws<Ascii::kMaxUintStringBytes> brBuf;
        (void)Ascii::AppendDec(brBuf, bitRate);
        TryAppend(brBuf);
        TryAppend("\"");
    }
    TryAddAttribute("bitDepth", "bitsPerSample");
    TryAddAttribute("sampleRate", "sampleFrequency");
    TryAddAttribute("channels", "nrAudioChannels");
    TryAddAttribute("mimeType", "protocolInfo");
    TryAppend(">");
    if (iUri.Bytes() > 0) {
        WriterBuffer writer(iMetaDataDidl);
        Converter::ToXmlEscaped(writer, iUri);
    }
    TryAppend("</res>");
    if (TryGetValue("type", val)) {
        TryAddTag(Brn("upnp:class"), kNsUpnp, Brx::Empty(),
                  Brn("object.item.audioItem.musicTrack"));
    }
    TryAppend("</item>");
    TryAppend("</DIDL-Lite>");
}

TBool OhMetadata::TryGetValue(const TChar* aKey, Brn& aValue) const
{
    Brn key(aKey);
    return TryGetValue(key, aValue);
}

TBool OhMetadata::TryGetValue(const Brx& aKey, Brn& aValue) const
{
    for (auto kvp : iMetadata) {
        if (kvp.first== aKey) {
            aValue.Set(kvp.second);
            return true;
        }
    }
    return false;
}

void OhMetadata::TryAddAttribute(const TChar* aOhKey, const TChar* aDidlAttr)
{
    Brn key(aOhKey);
    Brn val;
    if (TryGetValue(key, val)) {
        TryAppend(" ");
        TryAppend(aDidlAttr);
        TryAppend("=\"");
        TryAppend(val);
        TryAppend("\"");
    }
}

void OhMetadata::TryAddTag(const Brx& aOhKey, const Brx& aDidlTag,
                           const Brx& aNs, const Brx& aRole)
{
    Brn key(aOhKey);
    Brn val;
    if (TryGetValue(key, val)) {
        TryAppendTag(aDidlTag, aNs, aRole, val);
    }
}

void OhMetadata::TryAppendTag(const Brx& aDidlTag, const Brx& aNs,
                              const Brx& aRole, const Brx& aValue)
{
    TryAppend("<");
    TryAppend(aDidlTag);
    TryAppend(" xmlns:");
    TryAppend(aNs);
    if (aRole.Bytes() > 0) {
        TryAppend(" role=\"");
        TryAppend(aRole);
        TryAppend("\"");
    }
    TryAppend(">");
    WriterBuffer writer(iMetaDataDidl);
    Converter::ToXmlEscaped(writer, aValue);
    TryAppend("</");
    TryAppend(aDidlTag);
    TryAppend(">");
}

void OhMetadata::TryAppend(const TChar* aStr)
{
    Brn buf(aStr);
    TryAppend(buf);
}

void OhMetadata::TryAppend(const Brx& aBuf)
{
    if (!iMetaDataDidl.TryAppend(aBuf)) {
        THROW(BufferOverflow);
    }
}
