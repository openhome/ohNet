#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Av/Radio/ContentProcessorFactory.h>

/* Example OPML file

<?xml version="1.0" encoding="UTF-8"?>
<opml version="1">
        <head>
        <title>Listening Options</title>
        <status>200</status>
        </head>
        <body>
            <outline type="audio" text="stuff" URL="url" bitrate="num" reliability="num_percentage" guide_id="id" station_id="num" title="str" now_playing_id="id" media_type="type"/>
            <outline type="audio" text="stuff" URL="url" bitrate="num" reliability="num_percentage" guide_id="id" station_id="num" title="str" now_playing_id="id" media_type="type"/>
            ...
        </body>
</opml>
*/

namespace OpenHome {
namespace Av {

class ContentOpml : public Media::ContentProcessor
{
    static const TUint kMaxLineBytes = 2 * 1024;
public:
    ContentOpml();
    ~ContentOpml();
private: // from ContentProcessor
    TBool Recognise(const Brx& aUri, const Brx& aMimeType, const Brx& aData) override;
    Media::ProtocolStreamResult Stream(IReader& aReader, TUint64 aTotalBytes) override;
    void Reset() override;
private:
    Bws<1024> iUri;
    ReaderUntil* iReaderUntil;
};

} // namespace Av
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Av;


ContentProcessor* ContentProcessorFactory::NewOpml()
{ // static
    return new ContentOpml();
}


// ContentOpml

ContentOpml::ContentOpml()
{
    iReaderUntil = new ReaderUntilS<kMaxLineBytes>(*this);
}

ContentOpml::~ContentOpml()
{
    delete iReaderUntil;
}

TBool ContentOpml::Recognise(const Brx& /*aUri*/, const Brx& /*aMimeType*/, const Brx& aData)
{
    /* Ignore
            Ascii::CaseInsensitiveEquals(aMimeType, Brn("text/xml")
       test.  A content match is a far better indicator of success than knowing we're dealing with some sort of xml doc. */
    if (Ascii::Contains(aData, Brn("<opml version"))) {
        return true;
    }
    return false;
}

ProtocolStreamResult ContentOpml::Stream(IReader& aReader, TUint64 aTotalBytes)
{
    LOG(kMedia, "ContentOpml::Stream\n");

    SetStream(aReader);
    TUint64 bytesRemaining = aTotalBytes;
    
    try {
        for (;;) {
            Brn line(ReadLine(*iReaderUntil, bytesRemaining));
            ReaderBuffer rb(line);
            rb.ReadUntil('<');
            Parser parser(rb.ReadUntil('>'));
            Brn name = parser.Next();
            if (!Ascii::CaseInsensitiveEquals(name, Brn("outline"))) {
                continue;
            }
            Brn att = parser.Next('=');            
            if (!Ascii::CaseInsensitiveEquals(att, Brn("type"))) {
                continue;
            }
            parser.Next('"');
            Brn type = parser.Next('"');
            att.Set(parser.Next('='));            
            if (!Ascii::CaseInsensitiveEquals(att, Brn("text"))) {
                continue;
            }
            parser.Next('"');
            Brn text = parser.Next('"'); // metadata - station name
            att.Set(parser.Next('='));            
            if (!Ascii::CaseInsensitiveEquals(att, Brn("url"))) {
                continue;
            }
            parser.Next('"');
            Brn uri = parser.Next('"');
            TUint bytes = uri.Bytes();
            if (bytes == 0) {
                continue;
            }

            // could maybe skip the copy into another buffer if we know that this function won't be called again for the same underlying buffer
            iUri.Replace(uri);
            Converter::FromXmlEscaped(iUri);
            ProtocolStreamResult res = iProtocolSet->Stream(iUri);
            if (res == EProtocolStreamStopped || res == EProtocolStreamSuccess) {
                return res;
            }

        }
    }
    catch (ReaderError&) {
    }
    if (bytesRemaining > 0) {
        return EProtocolStreamErrorRecoverable;
    }
    return EProtocolStreamErrorUnrecoverable;
}

void ContentOpml::Reset()
{
    iReaderUntil->ReadFlush();
    ContentProcessor::Reset();
}
