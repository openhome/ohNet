#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Av/Radio/ContentProcessorFactory.h>

/* Example asx files

<asx version = "3.0">
    <title>Absolute Classic Rock</title>
    <entry>
        <PARAM name="HTMLView" value="http://www.absoluteclassicrock.co.uk/" />
        <abstract>Now playing info on our website.</abstract>
        <ref href = "mms://wm.as34763.net/vruk_vc_hi" />
        <ref href = "http://wm.as34763.net/vruk_vc_hi" />
        <ref href = "mmsu://wm.as34763.net/vruk_vc_hi" />
        <ref href = "mmst://wm.as34763.net/vruk_vc_hi" />
        <title>Absolute Classic Rock</title>
        <copyright>SMG Digital Radio Ltd </copyright>
        <author>Now playing info on our website</author>
        <MoreInfo href = "http://www.absoluteclassicrock.co.uk/" />
    </entry>
    <entry>
        <abstract>probs</Abstract>
        <PARAM name="HTMLView" value="http://www.absoluteradio.co.uk/thestation/faq/listenonline.html" />
        <ref href = "mms://wm.as34763.net/prerolls/problems_lo.wma" />
        <title>Absolute Classic Rock</title>
        <copyright>SMG Digital Radio Ltd</copyright>
        <author>Now playing info on our website</author>
        <MoreInfo href = "http://www.absoluteclassicrock.co.uk/" />
    </entry>
</asx>


OR


[Reference]
Ref1=http://wmlive.bbc.co.uk/wms/england/lrcumbria?MSWMExt=.asf
Ref2=http://212.58.252.33:80/wms/england/lrcumbria?MSWMExt=.asf

*/

namespace OpenHome {
namespace Av {

class ContentAsx : public Media::ContentProcessor
{
    static const TUint kMaxReadBytes = 4 * 1024;
public:
    ContentAsx();
    ~ContentAsx();
private: // from ContentProcessor
    TBool Recognise(const Brx& aUri, const Brx& aMimeType, const Brx& aData) override;
    Media::ProtocolStreamResult Stream(IReader& aReader, TUint64 aTotalBytes) override;
    void Reset();
private:
    enum FormatVersion
    {
        eUnknown
       ,eXml
       ,ePlainText
    };
private:
    ReaderUntil* iReaderUntil;
    FormatVersion iFormatVersion;
    TBool iInEntryBlock;
};

} // namespace Av
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;


ContentProcessor* ContentProcessorFactory::NewAsx()
{ // static
    return new ContentAsx();
}


// ContentAsx

ContentAsx::ContentAsx()
{
    iReaderUntil = new ReaderUntilS<kMaxReadBytes>(*this);
}

ContentAsx::~ContentAsx()
{
    delete iReaderUntil;
}

TBool ContentAsx::Recognise(const Brx& /*aUri*/, const Brx& aMimeType, const Brx& aData)
{
    if (Ascii::CaseInsensitiveEquals(aMimeType, Brn("video/x-ms-asf")) ||
        Ascii::CaseInsensitiveEquals(aMimeType, Brn("video/x-ms-wax")) ||
        Ascii::CaseInsensitiveEquals(aMimeType, Brn("video/x-ms-wvx")) ||
        Ascii::CaseInsensitiveEquals(aMimeType, Brn("audio/x-ms-asf")) ||
        Ascii::CaseInsensitiveEquals(aMimeType, Brn("audio/x-ms-wax")) ||
        Ascii::CaseInsensitiveEquals(aMimeType, Brn("audio/x-ms-wvx"))) {
        return true;
    }
    if (Ascii::Contains(aData, Brn("[Reference]"))  ||
        Ascii::Contains(aData, Brn("<asx version")) ||
        Ascii::Contains(aData, Brn("<ASX version"))) {
        return true;
    }
    return false;
}

ProtocolStreamResult ContentAsx::Stream(IReader& aReader, TUint64 aTotalBytes)
{
    SetStream(aReader);
    try {
        /* check for xml or another description format 
           first character for xml is '<', alternative is '[Reference]' at start else unsupported */
        while (iFormatVersion == eUnknown) {
            Brn format(iReaderUntil->Read(1));
            if (format.Bytes() == 0) {
                continue;
            }
            aTotalBytes--;
            switch (format[0])
            {
            case '<':
            {
                Brn tag(iReaderUntil->ReadUntil('>'));
                aTotalBytes -= tag.Bytes();
                Parser parser(tag);
                if (!Ascii::CaseInsensitiveEquals(parser.Next('='), Brn("asx version"))) {
                    return EProtocolStreamErrorUnrecoverable;
                }
                iFormatVersion = eXml;
            }
                break;
            case '[':
            {
                Brn value(iReaderUntil->ReadUntil(']'));
                aTotalBytes -= value.Bytes();
                if (!Ascii::CaseInsensitiveEquals(value, Brn("Reference"))) {
                    return EProtocolStreamErrorUnrecoverable;
                }
                iFormatVersion = ePlainText;
            }
                break;
            case ' ':
            case '\r':
            case '\n':
                continue;
            default:
                return EProtocolStreamErrorUnrecoverable;
            }
        }

        if (iFormatVersion == eXml) {
            TBool playedSomething = false;
            for (;;) {
                Brn tag;
                if (!iInEntryBlock) {
                    tag.Set(ReadTag(*iReaderUntil, aTotalBytes));
                }
                if (iInEntryBlock || Ascii::CaseInsensitiveEquals(tag, Brn("entry"))) {
                    iInEntryBlock = true;
                    TBool tryPlay = true;
                    for (;;) {
                        tag.Set(ReadTag(*iReaderUntil, aTotalBytes));
                        if (Ascii::CaseInsensitiveEquals(tag, Brn("entry"))) {
                            // don't expect to find another <entry> tag inside an <entry> block
                            return EProtocolStreamErrorUnrecoverable;
                        }
                        else if (Ascii::CaseInsensitiveEquals(tag, Brn("/entry"))) {
                            iInEntryBlock = false;
                            break;
                        }
                        else if (tryPlay && tag.BeginsWith(Brn("ref "))) {
                            Parser parser(tag);
                            parser.Next('\"');
                            Brn uri = parser.Next('\"');
                            ProtocolStreamResult res = iProtocolSet->Stream(uri);
                            if (res == EProtocolStreamStopped || res == EProtocolStreamErrorRecoverable) {
                                return res;
                            }
                            tryPlay = (res != EProtocolStreamSuccess);
                        }
                    }
                    playedSomething = playedSomething || !tryPlay;
                }
                else if (Ascii::CaseInsensitiveEquals(tag, Brn("/asx"))) {
                    return (playedSomething? EProtocolStreamSuccess : EProtocolStreamErrorUnrecoverable);
                }
            }
        }
        else if (iFormatVersion == ePlainText) {
            for (;;) {
                Brn line(ReadLine(*iReaderUntil, aTotalBytes));
                if (line.Bytes() < 3) {
                    continue;
                }
                Brn ref(line.Ptr(), 3);                
                if (Ascii::CaseInsensitiveEquals(ref, Brn("Ref"))) {
                    Parser parser(line);
                    parser.Next('=');
                    Brn value = parser.NextToEnd();
                    if(value.Bytes() == 0) {
                        continue;
                    }
                    // When the payload format is [Reference] translate http uri to mms
                    Bws<1024> uri;
                    if (value.BeginsWith(Brn("http"))) {
                        uri.Append("mms");
                        uri.Append(value.Split(4));
                        value.Set(uri);
                    }
                    ProtocolStreamResult res = iProtocolSet->Stream(value);
                    if (res == EProtocolStreamStopped) {
                        return EProtocolStreamStopped;
                    }
                    else if (res == EProtocolStreamSuccess) {
                        return EProtocolStreamSuccess;
                    }
                }
            }
            // end of file and we haven't managed to play anything
            //return EProtocolStreamErrorUnrecoverable;
        }
    }
    catch (ReaderError&) {
        if (aTotalBytes == 0) {
            return EProtocolStreamErrorUnrecoverable;
        }
        return EProtocolStreamErrorRecoverable;
    }

    return EProtocolStreamErrorUnrecoverable;
}

void ContentAsx::Reset()
{
    iReaderUntil->ReadFlush();
    ContentProcessor::Reset();
    iInEntryBlock = false;
    iFormatVersion = eUnknown;
}
