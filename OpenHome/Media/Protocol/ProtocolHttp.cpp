#include <OpenHome/Media/Protocol/ProtocolHttp.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Converter.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// HeaderIcyMetadata

void HeaderIcyMetadata::Write(WriterHttpHeader& aWriter)
{
    LOG(kMedia, "HeaderIcyMetadata::Write\n");
    aWriter.WriteHeader(Brn("Icy-MetaData"), Brn("1"));
}

TUint HeaderIcyMetadata::Bytes() const
{
    LOG(kMedia, "HeaderIcyMetadata::Bytes %d\n", iBytes);
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
    LOG(kMedia, "HeaderIcyMetadata::Process ");
    LOG(kMedia, aValue);
    LOG(kMedia, "\n");
    
    try {
        iBytes = Ascii::Uint(aValue);
        SetReceived();
    }
    catch (AsciiError&) {
        THROW(HttpError);
    }
    
    LOG(kMedia, "HeaderIcyMetadata::Process SUCCEEDED (%d)\n", iBytes);
}


// ProtocolHttp

static const Brn kM3uAppendix("\r\n");
static const Brn kUserAgentString("Linn DS"); // FIXME

ProtocolHttp::ProtocolHttp(Environment& aEnv, ProtocolManager& aManager)
    : ProtocolNetwork(aEnv, aManager)
    , iWriterRequest(iWriterBuf)
    , iReaderResponse(iReaderBuf)
    , iTotalBytes(0)
    , iSeekable(false)
    , iSnaffling(false)
{
    iReaderResponse.AddHeader(iHeaderContentType);
    iReaderResponse.AddHeader(iHeaderContentLength);
    iReaderResponse.AddHeader(iHeaderLocation);
    iReaderResponse.AddHeader(iHeaderIcyMetadata);
}

void ProtocolHttp::Stream()
{
    const OpenHome::Uri& uri = Uri();
    LOG(kMedia, "ProtocolHttp::Stream ");
    LOG(kMedia, uri.AbsoluteUri());
    LOG(kMedia, "\n");

    if (uri.Scheme() != Brn("http")) {
        LOG(kMedia, "ProtocolHttp::Stream Scheme not recognised\n");
        return;
    }
    
    iTotalBytes = 0;
    iSeekable = false;

    if (!Connect(80)) {
        LOG(kMedia, "ProtocolHttp::Stream Connection failure\n");
        return;
    }
        
    try {
        LOG(kMedia, "ProtocolHttp::Stream send request\n");
        iWriterRequest.WriteMethod(Http::kMethodGet, uri.PathAndQuery(), Http::eHttp11);
        Http::WriteHeaderHost(iWriterRequest, uri);
        iWriterRequest.WriteHeader(Http::kHeaderUserAgent, kUserAgentString); // FIXME - why are we sending a UA?
        Http::WriteHeaderConnectionClose(iWriterRequest);
        HeaderIcyMetadata::Write(iWriterRequest);
        Http::WriteHeaderRangeFirstOnly(iWriterRequest, 0);
        iWriterRequest.WriteFlush();
    }
    catch(WriterError&) {
        LOG(kMedia, "ProtocolHttp::Stream writer error\n");
        return;
    }
    
    try {
        LOG(kMedia, "ProtocolHttp::Stream read response\n");
        iReaderResponse.Read();
    }
    catch(HttpError&) {
        LOG(kMedia, "ProtocolHttp::Stream http error\n");
        return;
    }
    catch(ReaderError&) {
        LOG(kMedia, "ProtocolHttp::Stream reader error\n");
        return;
    }
    
    const TUint code = iReaderResponse.Status().Code();
    LOG(kMedia, "ProtocolHttp::Stream response code %d\n", code);
    // Check for redirection
    if (code >= HttpStatus::kRedirectionCodes && code <= HttpStatus::kClientErrorCodes) {
        if (iHeaderLocation.Received()) {
            Redirect(iHeaderLocation.Location());
        }
        return;
    }
    
    iTotalBytes = iHeaderContentLength.ContentLength();
    // Check for success seekable
    if (code == HttpStatus::kPartialContent.Code()) {
        if (iTotalBytes > 0) {
            iSeekable = true;
        }
        LOG(kMedia, "ProtocolHttp::Connect 'Partial Content' seekable=%d (%lld bytes)\n", iSeekable, iTotalBytes);
        ProcessContentType();
        return;
    }        
    
    // Check for success non-seekable
    if (code == HttpStatus::kOk.Code()) {
        iSeekable = false;
        LOG(kMedia, "ProtocolHttp::Connect 'OK' non-seekable (%lld bytes)\n", iTotalBytes);
        ProcessContentType();
        return;
    }
        
    LOG(kMedia, "ProtocolHttp::Stream Failed\n");
}

TBool ProtocolHttp::Restream(TUint64 aOffset)
{
    LOG(kMedia, "ProtocolHttp::Restream %lld\n", aOffset);

    if (!Connect(80)) {
        LOG(kMedia, "ProtocolHttp::Restream Connection failure\n");
        return true;
    }
        
    try {
        LOG(kMedia, "ProtocolHttp::Stream send request\n");
        iWriterRequest.WriteMethod(Http::kMethodGet, Uri().PathAndQuery(), Http::eHttp11);
        Http::WriteHeaderHost(iWriterRequest, Uri());
        iWriterRequest.WriteHeader(Http::kHeaderUserAgent, kUserAgentString); // FIXME - why are we sending a UA?
        Http::WriteHeaderConnectionClose(iWriterRequest);
        HeaderIcyMetadata::Write(iWriterRequest);
        Http::WriteHeaderRangeFirstOnly(iWriterRequest, aOffset);
        iWriterRequest.WriteFlush();
    }
    catch(WriterError&) {
        LOG(kMedia, "ProtocolHttp::Restream writer error\n");
        return true;
    }
    
    try {
        LOG(kMedia, "ProtocolHttp::Restream read response\n");
        iReaderResponse.Read();
    }
    catch(HttpError&) {
        LOG(kMedia, "ProtocolHttp::Restream http error\n");
        return true;
    }
    catch(ReaderError&) {
        LOG(kMedia, "ProtocolHttp::Restream reader error\n");
        return true;
    }
    
    const TUint code = iReaderResponse.Status().Code();
    LOG(kMedia, "ProtocolHttp::Restream response code %d\n", code);
    iTotalBytes = iHeaderContentLength.ContentLength();
    // Check for success seekable
    if (code != HttpStatus::kPartialContent.Code()) {
        LOG(kMedia, "ProtocolHttp::Restream Not seekable\n");
        return false; // return with unrecoverable error if connected but file/server problem arisen
    }       

    ProcessAudio();
    return true;
}

void ProtocolHttp::ProcessContentType()
{
    try {
        ReaderBuffer preview;
        TUint peekBytes = 1024;
        if (iTotalBytes > 0 && (iTotalBytes < peekBytes)) {
            peekBytes = (TUint)iTotalBytes;
        }
        preview.Set(iReaderBuf.Peek(peekBytes)); // examine start of file only

        if (iHeaderContentType.Received()) {
            LOG(kMedia, "ProtocolHttp::ProcessContentType ");
            LOG(kMedia, iHeaderContentType.Type());
            LOG(kMedia, "\n");

            const Brx& contentType = iHeaderContentType.Type();
            if (Ascii::CaseInsensitiveEquals(contentType, Brn("audio/x-scpls"))) {
                ProcessPls(preview);
                return;
            }

            if (Ascii::CaseInsensitiveEquals(contentType, Brn("audio/x-mpegurl"))
                    || Ascii::CaseInsensitiveEquals(contentType, Brn("audio/mpegurl")) // alias
                    ) {
                ProcessM3u(preview);
                return;
            }

            if (Ascii::CaseInsensitiveEquals(contentType, Brn("video/x-ms-asf"))
                    || Ascii::CaseInsensitiveEquals(contentType, Brn("video/x-ms-wax"))
                    || Ascii::CaseInsensitiveEquals(contentType, Brn("video/x-ms-wvx"))
                    || Ascii::CaseInsensitiveEquals(contentType, Brn("audio/x-ms-asf"))
                    || Ascii::CaseInsensitiveEquals(contentType, Brn("audio/x-ms-wax"))
                    || Ascii::CaseInsensitiveEquals(contentType, Brn("audio/x-ms-wvx"))
                    ) {
                ProcessAsx(preview);
                return;
            }

            if (Ascii::CaseInsensitiveEquals(contentType, Brn("text/xml"))) {
                ProcessXml(preview);
                return;
            }
        }

        // content type not recognised, so parse file to determine type without using content-type
        Brn header(preview.Read((preview.Bytes() < 100) ? preview.Bytes() : 100)); // read section from start of preview buffer for recognition process
        preview.ReadFlush(); // then reset to the beginning of the preview buffer for next level of processing

        if (Ascii::Contains(header, Brn("#EXTM3U"))) {
            ProcessM3u(preview);
            return;
        }
        if (Ascii::Contains(header, Brn("[playlist]"))) {
            ProcessPls(preview);
            return;
        }
        if (Ascii::Contains(header, Brn("<asx version"))) {
            ProcessAsx(preview);
            return;
        }
        if (Ascii::Contains(header, Brn("[Reference]"))) {
            ProcessAsx(preview);
            return;
        }
        if (Ascii::Contains(header, Brn("<opml version"))) {
            ProcessXml(preview);
            return;
        }
    }
    catch (ReaderError) {
        return;
    }
    LOG(kMedia, "ProtocolHttp::ProcessContentType Audio\n");
    
    if (!Start(iTotalBytes, iTotalBytes == 0, iSeekable)) {
        LOG(kMedia, "ProtocolHttp::ProcessContentType Start rejected\n");
        return;
    }

    ProcessAudio();
}

void ProtocolHttp::ExtractMetadata()
{
#if 0 // FIXME - need to bring across DidlLite class
    Brn metadata = iReaderBuf.Read(1);
    TUint metadataBytes = metadata[0] * 16;
    Bws<kIcyMetadataBytes> newMetadata;
    DidlLite didl;
    if (metadataBytes != 0) {
        Parser data(iReaderBuf.Read(metadataBytes));
        while(!data.Finished()) {
            Brn name = data.Next('=');
            if (name == Brn("StreamTitle")) {
                // metadata is in the format: 'data';
                // may contain single quote characters so seek to the semicolon and discard the trailing single quote
                data.Next('\'');
                Brn title = data.Next(';');
                if (title.Bytes() > 1) {
                    didl.SetTitle(Brn(title.Ptr(), title.Bytes()-1));
                }
                didl.SetClass(DidlLite::eObjectItem);
                break;
            }
        }
        didl.Create(newMetadata);
        // if the message has changed put it into the pipeline
        if (newMetadata != iIcyMetadata) {
            iIcyMetadata.Replace(newMetadata);
            OutputMetadata(iIcyMetadata);
        }
    }
#endif // 0
}

void ProtocolHttp::ProcessAudio()
{
    LOG(kMedia, "ProtocolHttp::ProcessAudio %lld\n", iTotalBytes);
    
    iIcyMetadata.SetBytes(0);
    TUint64 bytes = iTotalBytes;
    TBool finite = bytes > 0;
    TUint dataBytes = 0;

    for (;;) {
        if (Interrupt()) {  // FIXME - new approach to interrupting sockets now
           LOG(kMedia, "ProtocolHttp::ProcessAudio Interrupted\n");
           return;
        }
        try {
            TUint required;
            if (iHeaderIcyMetadata.Received()) {
                if (dataBytes == 0) {
                    dataBytes = iHeaderIcyMetadata.Bytes();
                }
                if (dataBytes > kAudioBytes) {
                    required = kAudioBytes;
                }
                else {
                    required = dataBytes;
                }
                dataBytes -= required;
            }
            else {
                required = kAudioBytes;
            }
            
            if (finite) {
                if (bytes == 0) {
                    LOG(kMedia, "ProtocolHttp::ProcessAudio completed\n");
                    End();
                    break;
                }
                if (bytes < required) {
                    required = (TUint)bytes;
                }
                bytes -= required;
            }
            
            OutputData(iReaderBuf.Read(required));

            if (iHeaderIcyMetadata.Received() && dataBytes == 0) { // at start of metadata
                ExtractMetadata();
            }
        }
        catch (ReaderError&)
        {
            LOG(kMedia, "ProtocolHttp::ProcessAudio ReaderError bytes %lld, iTotalBytes %lld\n", bytes, iTotalBytes);
            return;
        }
    }
}

/* Example pls file

[playlist]
NumberOfEntries=3

File1=http://streamexample.com:80
Title1=My Favorite Online Radio
Length1=-1

File2=http://example.com/song.mp3
Title2=Remote MP3
Length2=286

File3=/home/myaccount/album.flac
Title3=Local album
Length3=3487

Version=2

*/

void ProtocolHttp::ProcessPls(ReaderBuffer& aHeader)
{
    LOG(kMedia, "ProtocolHttp::ProcessPls\n");

    try {
        // Find [playlist]
        for (;;) {
            if (Interrupt()) { // FIXME - review all code for interrupting sockets
                return;
            }
            Brn line = EntityReadLine(aHeader);
            if (line == Brn("[playlist]")) {
                break;
            }
        }

        for (;;) {
            if (Interrupt()) { // FIXME - review all code for interrupting sockets
                return;
            }
            Brn line = EntityReadLine(aHeader);
            Parser parser(line);
            Brn key = parser.Next('=');
            if (key.BeginsWith(Brn("File"))) {
                Brn value = parser.Next();
                if (Protocol::Stream(value)) {
                    return;
                }
            }
        }
    }
    catch (ReaderError&) {
    }
}

/* Example m3u file

#EXTM3U

#EXTINF:123,Sample title
C:\Documents and Settings\I\My Music\Sample.mp3

#EXTINF:321,Example title
C:\Documents and Settings\I\My Music\Greatest Hits\Example.ogg

*/

void ProtocolHttp::ProcessM3u(ReaderBuffer& aHeader)
{
    LOG(kMedia, "ProtocolHttp::ProcessM3u\n");
    
    try {
        for (;;) {
            if (Interrupt()) { // FIXME - review all code for interrupting sockets
                return;
            }
            Brn line = EntityReadLine(aHeader);
            if (line.BeginsWith(Brn("#"))) {
                continue; // comment line
            }
            if (Protocol::Stream(line)) {
                return;
            }
        }
    }
    catch (ReaderError&) {
    }
}

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

void ProtocolHttp::ProcessAsx(ReaderBuffer& aHeader)
{
    LOG(kMedia, "ProtocolHttp::ProcessAsx\n");
    
    // check for xml or another description format 
    // first character for xml is '<', alternative is '[Reference]' at start else unsupported
    try {
        for (;;) {
            if (Interrupt()) { // FIXME - review all code for interrupting sockets
                return;
            }
            
            Brn format(aHeader.Read(1));
            if (format.BeginsWith(Brn("<"))) {
                Parser parser(aHeader.ReadUntil('>')); // read first tag
                if (!Ascii::CaseInsensitiveEquals(parser.Next('='), Brn("asx version"))) {
                    continue;
                }

                // in an attempt to ignore intro uris and commence playing from the main
                // uri, search through all uri's and start to play from the entry which
                // contains the most.  This is certainly not ideal but will hopefully
                // catch the majority of use cases until true support is added.
                // correct method is to allow playing through each entry in the file - ToDo
                // build list of uris
                UriList uriList;
                for (;;) {
                    Parser parser;
                    try {
                        parser.Set(EntityReadTag(aHeader));
                    }
                    catch (ReaderError&) {
                        break; // at end of asx data
                    }
                    Brn name(parser.Next());
                    if (Ascii::CaseInsensitiveEquals(name, Brn("entry"))) {
                        uriList.NextEntry();
                    }
                    else if (Ascii::CaseInsensitiveEquals(name, Brn("/entry"))) {
                    }
                    else {
                        if (!Ascii::CaseInsensitiveEquals(name, Brn("ref"))) {
                            continue;
                        }
            
                        Brn att = parser.Next('=');
                        if (!Ascii::CaseInsensitiveEquals(att, Brn("href"))) {
                            continue;
                        }
                        parser.Next('"');
                        Brn uri = parser.Next('"');
                        TUint bytes = uri.Bytes();
                        if (bytes == 0) {
                            continue;
                        }
                        uriList.AddUri(uri);
                    }
                }
                
                // attempt to play each until successful
                Brn uri;
                uriList.FindFirst();
                while(uriList.FindNext(uri)) {
                    if (Protocol::Stream(uri)) {
                        return;
                    }
                }
            }
            else if (format.BeginsWith(Brn("["))) {            // alternative format
                Parser parser(aHeader.ReadUntil(']'));    // read first tag
                for (;;) {
                    Brn line(EntityReadLine(aHeader));
                    Brn ref(line.Ptr(), 3);                
                    if (Ascii::CaseInsensitiveEquals(ref, Brn("Ref"))) {
                        Parser parser(line);
                        parser.Next('=');
                        Brn value = parser.NextToEnd();
                        if (value.Bytes()) {
                            // When the payload format is [Reference] translate http uri to mms
                            if (iAsxUri.Scheme() == Brn("http")) {
                                LOG(kMedia, " replace http scheme with mms\n");
                                iMmsUri.Replace(Brn("mms"));
                                iMmsUri.Append(iAsxUri.AbsoluteUri().Split(4));
                                iAsxUri.Replace(iMmsUri);
                            }
                            if (Protocol::Stream(iAsxUri.AbsoluteUri())) {
                                return;
                            }
                        }
                    }
                }
            }
        }
    }    
    catch (ReaderError&) {
    }
}

void ProtocolHttp::ProcessXml(ReaderBuffer& aHeader)
{
    LOG(kMedia, "ProtocolHttp::ProcessXml\n");
    
    // check for xml or another description format 
    // first character for xml is '<', alternative is '[Reference]' at start else unsupported
    try {
        for (;;) {
            if (Interrupt()) { // FIXME - review all code for interrupting sockets
                return;
            }
            Brn format(EntityReadLine(aHeader));
            if (format.BeginsWith(Brn("<"))) {
                Parser parser(format);
                if (!Ascii::CaseInsensitiveEquals(parser.Next('='), Brn("<opml version"))) {
                    continue;
                }
                for (;;) {
                    Parser parser(EntityReadTag(aHeader));
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
                    iXmlUri.Replace(uri);
                    Converter::FromXmlEscaped(iXmlUri); // FIXME - Converter has slightly different functionality vs volkano's Syslib Xml::Unescape

                    LOG(kMedia, "radio uri[");
                    LOG(kMedia, iXmlUri);
                    LOG(kMedia, "]\n");

                    if (Protocol::Stream(iXmlUri)) {
                        return;
                    }
                }
            }
        }
    }
    catch (ReaderError&) {
    }
}

Brn ProtocolHttp::EntityReadLine(ReaderBuffer& aHeader)
{
    TBool done = false;
    while (!done) {
        Brn line;
        try {
            line.Set(Ascii::Trim(aHeader.ReadUntil(Ascii::kLf)));
        }
        catch (ReaderError&) {
            line.Set(aHeader.ReadRemaining());
            done = true;
        }
        if (line.Bytes() > 0) {
            LOG(kMedia, line);
            LOG(kMedia, "\n");

            return line;
        }
    }
    return Brx::Empty();
}

Brn ProtocolHttp::EntityReadTag(ReaderBuffer& aHeader)
{
    aHeader.ReadUntil('<');
    return aHeader.ReadUntil('>');
}


// UriEntry

UriEntry::UriEntry(Brn aUri, TUint aEntry)
    : iUri(aUri)
    , iEntry(aEntry)
{
}


// UriList

UriList::UriList()
    : iMaxUris(0)
    , iMaxUrisEntry(0)
    , iEntry(0)
    , iUriCount(0)
    , iUriIndex(0)
{
}

UriList::~UriList()
{
    for (TUint i = 0; i < (TUint)iUriList.size(); i++) {
        delete(iUriList[i]);
    }
}

void UriList::NextEntry()
{
    iEntry++;
    iUriCount = 0;
}

void UriList::AddUri(Brn aUri)
{
    iUriCount++;
    if (iMaxUris < iUriCount) {
        iMaxUris = iUriCount;
        iMaxUrisEntry = iEntry;
    }
    iUriList.push_back(new UriEntry(aUri, iEntry));
}


void UriList::FindFirst()
{
    for (iUriIndex = 0; iUriIndex < iUriList.size(); iUriIndex++) {
        if (iUriList[iUriIndex]->Entry() == iMaxUrisEntry) {
            return;
        }
    }

}

TBool UriList::FindNext(Brn& aUri)
{
    while (iUriIndex < iUriList.size()) {
        UriEntry* uriEntry = iUriList[iUriIndex++];
        if (uriEntry->Entry() == iMaxUrisEntry) {
            aUri.Set(uriEntry->Uri());
            LOG(kMedia, "uri[");
            LOG(kMedia, aUri);
            LOG(kMedia, "]\n");

            return true;
        }
    }
    return false;
}
