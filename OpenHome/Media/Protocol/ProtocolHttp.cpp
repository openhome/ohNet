#include <OpenHome/Media/Protocol/ProtocolHttp.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>

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

static const Brn kUserAgentString("Linn DS"); // FIXME

ProtocolHttp::ProtocolHttp(Environment& aEnv)
    : ProtocolNetwork(aEnv)
    , iWriterRequest(iWriterBuf)
    , iReaderResponse(aEnv, iReaderBuf)
    , iTotalBytes(0)
    , iSeekable(false)
    , iSem("PRTH", 0)
{
    iReaderResponse.AddHeader(iHeaderContentType);
    iReaderResponse.AddHeader(iHeaderContentLength);
    iReaderResponse.AddHeader(iHeaderLocation);
    iReaderResponse.AddHeader(iHeaderIcyMetadata);
}

ProtocolStreamResult ProtocolHttp::Stream(const Brx& aUri)
{
    iTotalBytes = iSeekPos = iOffset = 0;
    iStreamId = ProtocolManager::kStreamIdInvalid;
    iSeekable = iSeek = iLive = iStarted = iStopped = iStreamIncludesMetaData = false;
    iDataChunkSize = iDataChunkRemaining = 0;
    iContentProcessor = NULL;
    iNextFlushId = MsgFlush::kIdInvalid;
    (void)iSem.Clear();
    iUri.Replace(aUri);

    LOG(kMedia, "ProtocolHttp::Stream ");
    LOG(kMedia, iUri.AbsoluteUri());
    LOG(kMedia, "\n");

    if (iUri.Scheme() != Brn("http")) {
        LOG(kMedia, "ProtocolHttp::Stream Scheme not recognised\n");
        return EProtocolErrorNotSupported;
    }
    
    ProtocolStreamResult res = DoStream();
    if (res == EProtocolStreamErrorUnrecoverable) {
        // FIXME - error msg
        return res;
    }
    if (iLive) {
        iSem.Wait();
        res = EProtocolStreamErrorRecoverable; // bodge to drop into the loop below
    }
    while (res == EProtocolStreamErrorRecoverable) {
        if (iLive) {
            res = DoLiveStream();
        }
        else if (iSeek) {
            iSupply->OutputFlush(iNextFlushId);
            iOffset = iSeekPos;
            iSeek = false;
            res = DoSeek(iOffset);
        }
        else {
            // FIXME - if stream is non-seekable, set ErrorUnrecoverable as soon as Connect succeeds
            /* FIXME - reconnects should use extra http headers to check that content hasn't changed
               since our first attempt at reading it.  Any change should result in ErrorUnrecoverable */
            TUint code = WriteRequest(iOffset);
            if (code != 0) {
                iTotalBytes = iHeaderContentLength.ContentLength();
                res = ProcessContent();
            }
        }
        if (res == EProtocolStreamErrorUnrecoverable) {
            // FIXME - msg to indicate bad track
        }
        if (res == EProtocolStreamErrorRecoverable) {
            Thread::Sleep(50);
        }
        if (iStopped) {
            iSupply->OutputFlush(iNextFlushId);
            res = EProtocolStreamStopped;
        }
    }
    iLock.Wait();
    // FIXME - clear track, stream ids
    // TBool stopped = iStopped;
    iLock.Signal();
    if (iContentProcessor != NULL) {
        iContentProcessor->Reset();
    }
    return res;
}

TBool ProtocolHttp::OkToPlay(TUint aTrackId, TUint aStreamId)
{
    const TBool canPlay = iIdProvider->OkToPlay(aTrackId);
    if (canPlay && iLive && iStreamId == aStreamId) {
        iSem.Signal();
    }
    return canPlay;
}

TUint ProtocolHttp::TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset)
{
    LOG(kMedia, "ProtocolHttp::Seek\n");

    iLock.Wait();
    const TBool streamIsValid = (iProtocolManager->OkToSeek(aTrackId) && iStreamId == aStreamId);
    if (streamIsValid) {
        iSeek = true;
        iSeekPos = aOffset;
        iNextFlushId = iFlushIdProvider->NextFlushId();
    }
    iLock.Signal();
    if (!streamIsValid) {
        return MsgFlush::kIdInvalid;
    }
    iTcpClient.Interrupt(true);
    return iNextFlushId;
}

TUint ProtocolHttp::TryStop(TUint /*aTrackId*/, TUint aStreamId)
{
    // FIXME - check aTrackId
    iLock.Wait();
    const TBool stop = (iStreamId == aStreamId);
    if (stop) {
        iNextFlushId = iFlushIdProvider->NextFlushId();
        iStopped = true;
        iTcpClient.Interrupt(true);
    }
    iLock.Signal();
    return (stop? iNextFlushId : MsgFlush::kIdInvalid);
}

Brn ProtocolHttp::Read(TUint aBytes)
{
    TUint bytes = aBytes;
    if (iStreamIncludesMetaData) {
        if (iDataChunkRemaining == 0) {
            ExtractMetadata();
            iDataChunkRemaining = iDataChunkSize;
        }
        if (iDataChunkRemaining < bytes) {
            bytes = iDataChunkRemaining;
        }
        iDataChunkRemaining -= bytes;
    }
    Brn buf = iReaderBuf.Read(bytes);
    iOffset += buf.Bytes();
    return buf;
}

Brn ProtocolHttp::ReadUntil(TByte aSeparator)
{
    ASSERT(!iStreamIncludesMetaData); /* assume only audio streams contain icy data
                                         and they just read a number of bytes */
    Brn buf = iReaderBuf.ReadUntil(aSeparator);
    iOffset += buf.Bytes();
    return buf;
}

void ProtocolHttp::ReadFlush()
{
    iReaderBuf.ReadFlush();
}

void ProtocolHttp::ReadInterrupt()
{
    iReaderBuf.ReadInterrupt();
}

Brn ProtocolHttp::ReadRemaining()
{
    Brn buf = iReaderBuf.Snaffle();
    iOffset += buf.Bytes();
    return buf;
}

ProtocolStreamResult ProtocolHttp::DoStream()
{
    TUint code;
    for (;;) { // loop until we don't get a redirection response (i.e. normally don't loop at all!)
        code = WriteRequest(0);
        if (code == 0) {
            return EProtocolStreamErrorUnrecoverable;
        }
        // Check for redirection
        if (code >= HttpStatus::kRedirectionCodes && code <= HttpStatus::kClientErrorCodes) {
            if (!iHeaderLocation.Received()) {
                return EProtocolStreamErrorUnrecoverable;
            }
            iUri.Replace(iHeaderLocation.Location());
            continue;
        }
        break;
    }
    
    iSeekable = false;
    iTotalBytes = iHeaderContentLength.ContentLength();
    iLive = (iTotalBytes == 0);
    if (code != HttpStatus::kPartialContent.Code() && code != HttpStatus::kOk.Code()) {
        LOG(kMedia, "ProtocolHttp::Stream Failed\n");
        return EProtocolStreamErrorUnrecoverable;
    }
    if (code == HttpStatus::kPartialContent.Code()) {
        if (iTotalBytes > 0) {
            iSeekable = true;
        }
        LOG(kMedia, "ProtocolHttp::Connect 'Partial Content' seekable=%d (%lld bytes)\n", iSeekable, iTotalBytes);
    }
    else { // code == HttpStatus::kOk.Code()
        LOG(kMedia, "ProtocolHttp::Connect 'OK' non-seekable (%lld bytes)\n", iTotalBytes);
    }
    if (iHeaderIcyMetadata.Received()) {
        ASSERT(iTotalBytes == 0); // if non-live streams contain icy data, we'll need to adjust totalBytes passed to content processor
        iStreamIncludesMetaData = true;
        iDataChunkSize = iDataChunkRemaining = iHeaderIcyMetadata.Bytes();
    }

    if (!iStarted && iLive) {
        StartStream();
        // don't want to buffer content from a live stream so need to wait on pipeline signalling it is ready to play
        Close();
        return EProtocolStreamErrorRecoverable;
    }

    return ProcessContent();
}

ProtocolStreamResult ProtocolHttp::DoSeek(TUint64 aOffset)
{
    LOG(kMedia, "ProtocolHttp::DoRestream %lld\n", aOffset);

    Interrupt(false);
    Close();
    const TUint code = WriteRequest(aOffset);
    if (code == 0) {
        return EProtocolStreamErrorRecoverable;
    }
    iTotalBytes = iHeaderContentLength.ContentLength();
    if (code != HttpStatus::kPartialContent.Code()) {
        LOG(kMedia, "ProtocolHttp::DoRestream Not seekable\n");
        return EProtocolStreamErrorUnrecoverable;
    }       

    return ProcessContent();
}

ProtocolStreamResult ProtocolHttp::DoLiveStream()
{
    LOG(kMedia, "ProtocolHttp::DoLiveStream\n");

    Interrupt(false);
    Close();
    const TUint code = WriteRequest(0);
    iLive = false;
    if (code == 0) {
        return EProtocolStreamErrorRecoverable;
    }

    return ProcessContent();
}

void ProtocolHttp::StartStream()
{
    LOG(kMedia, "ProtocolHttp::StartStream\n");

    iStreamId = iIdProvider->NextStreamId();
    iSupply->OutputStream(iUri.AbsoluteUri(), iTotalBytes, iSeekable, iLive, *this, iStreamId);
    iStarted = true;
}

TUint ProtocolHttp::WriteRequest(TUint64 aOffset)
{
    Close();
    if (!Connect(iUri, 80)) {
        LOG(kMedia, "ProtocolHttp::WriteRequest Connection failure\n");
        return 0;
    }
        
    try {
        LOG(kMedia, "ProtocolHttp::Stream send request\n");
        iWriterRequest.WriteMethod(Http::kMethodGet, iUri.PathAndQuery(), Http::eHttp11);
        Http::WriteHeaderHost(iWriterRequest, iUri);
        iWriterRequest.WriteHeader(Http::kHeaderUserAgent, kUserAgentString); // FIXME - why are we sending a UA?
        Http::WriteHeaderConnectionClose(iWriterRequest);
        HeaderIcyMetadata::Write(iWriterRequest);
        Http::WriteHeaderRangeFirstOnly(iWriterRequest, aOffset);
        iWriterRequest.WriteFlush();
    }
    catch(WriterError&) {
        LOG(kMedia, "ProtocolHttp::WriteRequest writer error\n");
        return 0;
    }
    
    try {
        LOG(kMedia, "ProtocolHttp::WriteRequest read response\n");
        iReaderResponse.Read();
    }
    catch(HttpError&) {
        LOG(kMedia, "ProtocolHttp::WriteRequest http error\n");
        return 0;
    }
    catch(ReaderError&) {
        LOG(kMedia, "ProtocolHttp::WriteRequest reader error\n");
        return 0;
    }
    const TUint code = iReaderResponse.Status().Code();
    LOG(kMedia, "ProtocolHttp response code %d\n", code);
    return code;
}

ProtocolStreamResult ProtocolHttp::ProcessContent()
{
    LOG(kMedia, "ProtocolHttp::ProcessContent %lld\n", iTotalBytes);
    
    if (iContentProcessor == NULL && !iStarted) {
        try {
            Brn contentStart = iReaderBuf.Peek(100);
            iContentProcessor = iProtocolManager->GetContentProcessor(iUri.AbsoluteUri(), iHeaderContentType.Received()? iHeaderContentType.Type() : Brx::Empty(), contentStart);
        }
        catch (ReaderError&) {
            return EProtocolStreamErrorRecoverable;
        }
    }
    if (iContentProcessor != NULL) {
        return iContentProcessor->Stream(*this, iTotalBytes);
    }

    if (!iStarted) {
        StartStream();
    }
    iContentProcessor = iProtocolManager->GetAudioProcessor();
    return iContentProcessor->Stream(*this, iTotalBytes);
}

void ProtocolHttp::ExtractMetadata()
{
    Brn metadata = iReaderBuf.Read(1);
    iOffset++;
    TUint metadataBytes = metadata[0] * 16;
#if 1 // FIXME - need to bring across DidlLite class
    iReaderBuf.Read(metadataBytes);
    iOffset += metadataBytes;
#else
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

#if 0
// unused but retained until all content processors are factored out



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
    catch (ReaderError&) {
        return;
    }
    LOG(kMedia, "ProtocolHttp::ProcessContentType Audio\n");
    
    iStreamId = REVIEW_ME_Start(iTotalBytes, (iTotalBytes == 0? this : NULL), (iSeekable? this : NULL));
    iStarted = true;

    ProcessAudio();
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
            Brn line = EntityReadLine(aHeader);
            if (line == Brn("[playlist]")) {
                break;
            }
        }

        for (;;) {
            Brn line = EntityReadLine(aHeader);
            Parser parser(line);
            Brn key = parser.Next('=');
            if (key.BeginsWith(Brn("File"))) {
                Brn value = parser.Next();
                if (Protocol::REVIEW_ME_Stream(value)) {
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
            Brn line = EntityReadLine(aHeader);
            if (line.BeginsWith(Brn("#"))) {
                continue; // comment line
            }
            if (Protocol::REVIEW_ME_Stream(line)) {
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
                    if (Protocol::REVIEW_ME_Stream(uri)) {
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
                            if (Protocol::REVIEW_ME_Stream(iAsxUri.AbsoluteUri())) {
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

                    if (Protocol::REVIEW_ME_Stream(iXmlUri)) {
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
#endif // 0