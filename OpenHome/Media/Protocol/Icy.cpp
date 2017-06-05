#include <OpenHome/Media/Protocol/Icy.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Media/Debug.h>

#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::Media;

// HeaderIcyMetadata

void HeaderIcyMetadata::Write(WriterHttpHeader& aWriter)
{
    aWriter.WriteHeader(Brn("Icy-MetaData"), Brn("1"));
}

TUint HeaderIcyMetadata::Bytes() const
{
    if (Received()) {
        return iBytes;
    }
    return 0;
}

TBool HeaderIcyMetadata::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Brn("icy-metaint"));
}

void HeaderIcyMetadata::Process(const Brx& aValue)
{
    try {
        iBytes = Ascii::Uint(aValue);
        SetReceived();
    }
    catch (AsciiError&) {
        THROW(HttpError);
    }
}


// ReaderIcy

ReaderIcy::ReaderIcy(IReader& aReader, IIcyObserver& aObserver, TUint64& aStreamOffset)
    : iReader(aReader)
    , iObserver(aObserver)
    , iOffset(aStreamOffset)
{
    Reset();
}

void ReaderIcy::Reset()
{
    iIcyData.Replace(Brx::Empty());
    iDataChunkSize= iDataChunkRemaining = 0;
    iEnabled = false;
}

void ReaderIcy::SetEnabled(TUint aChunkBytes)
{
    iEnabled = true;
    iDataChunkSize = iDataChunkRemaining = aChunkBytes;
}

Brn ReaderIcy::Read(TUint aBytes)
{
    TUint bytes = aBytes;
    if (iEnabled) {
        if (iDataChunkRemaining == 0) {
            ExtractMetadata();
            iDataChunkRemaining = iDataChunkSize;
        }
        bytes = std::min(iDataChunkRemaining, bytes);
    }
    Brn buf = iReader.Read(bytes);
    if (iEnabled) {
        iDataChunkRemaining -= buf.Bytes();
    }
    iOffset += buf.Bytes();
    return buf;
}

void ReaderIcy::ReadFlush()
{
    iReader.ReadFlush();
}

void ReaderIcy::ReadInterrupt()
{
    iReader.ReadInterrupt();
}

void ReaderIcy::ExtractMetadata()
{
    Brn metadata = iReader.Read(1);
    if (metadata.Bytes() == 0) { // EoS
        return;
    }

    iOffset++;
    TUint metadataBytes = metadata[0] * 16;
    if (metadataBytes == 0) {
        return;
    }

    iIcyData.Replace(Brx::Empty());
    do {
        Brn buf = iReader.Read(metadataBytes);
        iOffset += buf.Bytes();
        metadataBytes -= buf.Bytes();
        iIcyData.Append(buf);
    } while (metadataBytes != 0);
    iObserver.NotifyIcyData(iIcyData);
}


// IcyObserverDidlLite

IcyObserverDidlLite::IcyObserverDidlLite(IIcyObserver& aObserver)
    : iObserver(aObserver)
{
}

void IcyObserverDidlLite::Reset()
{
    iIcyMetadata.Replace(Brx::Empty());
    iNewIcyMetadata.Replace(Brx::Empty());
}

void IcyObserverDidlLite::NotifyIcyData(const Brx& aIcyData)
{
    iNewIcyMetadata.Replace("<DIDL-Lite xmlns:dc='http://purl.org/dc/elements/1.1/' ");
    iNewIcyMetadata.Append("xmlns:upnp='urn:schemas-upnp-org:metadata-1-0/upnp/' ");
    iNewIcyMetadata.Append("xmlns='urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/'>");
    iNewIcyMetadata.Append("<item id='' parentID='' restricted='True'><dc:title>");

    Parser data(aIcyData);
    while (!data.Finished()) {
        Brn name = data.Next('=');
        if (name == Brn("StreamTitle")) {
            // metadata is in the format: 'data';
            // may contain single quote characters so seek to the semicolon and discard the trailing single quote
            data.Next('\'');
            Brn title = data.Next(';');
            if (title.Bytes() > 1) {
                iNewIcyMetadata.Append(Brn(title.Ptr(), title.Bytes()-1));
            }

            iNewIcyMetadata.Append("</dc:title><upnp:albumArtURI></upnp:albumArtURI>");
            iNewIcyMetadata.Append("<upnp:class>object.item</upnp:class></item></DIDL-Lite>");
            if (iNewIcyMetadata != iIcyMetadata) {
                LOG(kMedia, "IcyObserverDidlLite::NotifyIcyData() - %.*s\n", PBUF(iNewIcyMetadata));
                iIcyMetadata.Replace(iNewIcyMetadata);
                iObserver.NotifyIcyData(iIcyMetadata);
            }
            break;
        }
    }
}
