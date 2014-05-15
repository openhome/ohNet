#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>

#include <algorithm>

namespace OpenHome {
namespace Media {

class HeaderIcyMetadata : public HttpHeader
{
public:
    static void Write(WriterHttpHeader& aWriter);
    TUint Bytes() const;
private: // from HttpHeader
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    TUint iBytes;
};

class ProtocolHttp : public ProtocolNetwork, private IProtocolReader
{
    static const TUint kIcyMetadataBytes = 255 * 16;
public:
    ProtocolHttp(Environment& aEnv);
private: // from Protocol
    ProtocolStreamResult Stream(const Brx& aUri);
    ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes);
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
    TBool TryGet(IWriter& aWriter, TUint aTrackId, TUint aStreamId, TUint64 aOffset, TUint aBytes);
private: // from IProtocolReader
    Brn Read(TUint aBytes);
    Brn ReadUntil(TByte aSeparator);
    void ReadFlush();
    void ReadInterrupt();
    Brn ReadRemaining();
private:
    void Reinitialise(const Brx& aUri);
    ProtocolStreamResult DoStream();
    ProtocolStreamResult DoSeek(TUint64 aOffset);
    ProtocolStreamResult DoLiveStream();
    void StartStream();
    TUint WriteRequest(TUint64 aOffset);
    ProtocolStreamResult ProcessContent();
    void ExtractMetadata();
private:
    WriterHttpRequest iWriterRequest;
    ReaderHttpResponse iReaderResponse;
    ReaderHttpChunked iDechunker;
    HttpHeaderContentType iHeaderContentType;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderLocation iHeaderLocation;
    HttpHeaderTransferEncoding iHeaderTransferEncoding;
    HeaderIcyMetadata iHeaderIcyMetadata;
    Bws<kIcyMetadataBytes> iIcyMetadata;
    Bws<kIcyMetadataBytes> iNewIcyMetadata; // only used in a single function but too large to comfortably declare on the stack
    OpenHome::Uri iUri;
    TUint64 iTotalBytes;
    TUint iStreamId;
    TBool iSeekable;
    TBool iSeek;
    TBool iLive;
    TBool iStarted;
    TBool iStopped;
    TBool iStreamIncludesMetaData;
    TUint iDataChunkSize;
    TUint iDataChunkRemaining;
    TUint64 iSeekPos;
    TUint64 iOffset;
    ContentProcessor* iContentProcessor;
    TUint iNextFlushId;
    Semaphore iSem;
};

};  // namespace Media
};  // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;


Protocol* ProtocolFactory::NewHttp(Environment& aEnv)
{ // static
    return new ProtocolHttp(aEnv);
}


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
    , iDechunker(iReaderBuf)
    , iTotalBytes(0)
    , iSeekable(false)
    , iSem("PRTH", 0)
{
    iReaderResponse.AddHeader(iHeaderContentType);
    iReaderResponse.AddHeader(iHeaderContentLength);
    iReaderResponse.AddHeader(iHeaderLocation);
    iReaderResponse.AddHeader(iHeaderTransferEncoding);
    iReaderResponse.AddHeader(iHeaderIcyMetadata);
}

ProtocolStreamResult ProtocolHttp::Stream(const Brx& aUri)
{
    Reinitialise(aUri);

    LOG(kMedia, "ProtocolHttp::Stream ");
    LOG(kMedia, iUri.AbsoluteUri());
    LOG(kMedia, "\n");

    if (iUri.Scheme() != Brn("http")) {
        LOG(kMedia, "ProtocolHttp::Stream Scheme not recognised\n");
        Close();
        return EProtocolErrorNotSupported;
    }

    ProtocolStreamResult res = DoStream();
    if (res == EProtocolStreamErrorUnrecoverable) {
        // FIXME - error msg
        Close();
        return res;
    }
    if (iLive) {
        // don't want to buffer content from a live stream
        // ...so need to wait on pipeline signalling it is ready to play
        Close();
        iSem.Wait();
        res = EProtocolStreamErrorRecoverable; // bodge to drop into the loop below
    }
    while (res == EProtocolStreamErrorRecoverable) {
        if (iStopped) {
            res = EProtocolStreamStopped;
            break;
        }
        Close();
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
    }
    iLock.Wait();
    if (iStopped) {
        iSupply->OutputFlush(iNextFlushId);
    }
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iLock.Signal();
    if (iContentProcessor != NULL) {
        iContentProcessor->Reset();
    }
    Close();
    return res;
}

ProtocolGetResult ProtocolHttp::Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes)
{
    Reinitialise(aUri);

    if (iUri.Scheme() != Brn("http")) {
        LOG(kMedia, "ProtocolHttp::Stream Scheme not recognised\n");
        Close();
        return EProtocolGetErrorNotSupported;
    }

    Close();
    if (!Connect(iUri, 80)) {
        LOG(kMedia, "ProtocolHttp::Get Connection failure\n");
        return EProtocolGetErrorUnrecoverable;
    }

    try {
        LOG(kMedia, "ProtocolHttp::Get send request\n");
        iWriterRequest.WriteMethod(Http::kMethodGet, iUri.PathAndQuery(), Http::eHttp11);
        const TUint port = (iUri.Port() == -1? 80 : (TUint)iUri.Port());
        Http::WriteHeaderHostAndPort(iWriterRequest, iUri.Host(), port);
        Http::WriteHeaderConnectionClose(iWriterRequest);
        TUint64 last = aOffset+aBytes;
        if (last > 0) {
            last -= 1;  // need to adjust for last byte position as request
                        // requires absolute positions, rather than range
        }
        Http::WriteHeaderRange(iWriterRequest, aOffset, last);
        iWriterRequest.WriteFlush();
    }
    catch(WriterError&) {
        LOG(kMedia, "ProtocolHttp::Get WriterError\n");
        return EProtocolGetErrorUnrecoverable;
    }

    try {
        LOG(kMedia, "ProtocolHttp::Get read response\n");
        iReaderResponse.Read();

        const TUint code = iReaderResponse.Status().Code();
        iTotalBytes = iHeaderContentLength.ContentLength();
        // FIXME - should parse the Content-Range response to ensure we're
        // getting the bytes requested - the server may (validly) opt not to
        // honour our request.
        LOG(kMedia, "ProtocolHttp::Get response code %d\n", code);
        if (code != HttpStatus::kPartialContent.Code() && code != HttpStatus::kOk.Code()) {
            LOG(kMedia, "ProtocolHttp::Get failed\n");
            return EProtocolGetErrorUnrecoverable;
        }
        if (code == HttpStatus::kPartialContent.Code()) {
            LOG(kMedia, "ProtocolHttp::Get 'Partial Content' (%lld bytes)\n", iTotalBytes);
            if (iTotalBytes >= aBytes) {
                TUint64 count = 0;
                TUint bytes = 1024; // FIXME - choose better value or justify this
                while (count < iTotalBytes) {
                    const TUint remaining = static_cast<TUint>(iTotalBytes-count);
                    if (remaining < bytes) {
                        bytes = remaining;
                    }
                    Brn buf = Read(bytes);
                    aWriter.Write(buf);
                    count += buf.Bytes();
                    // If we start pushing some bytes to IWriter then get an
                    // error, will fall through and return
                    // EProtocolGetErrorUnrecoverable below, so IWriter won't
                    // receive duplicate data and TryGet() will return false,
                    // so IWriter knows to invalidate any data it's received.
                }
                return EProtocolGetSuccess;
            }
        }
        else { // code == HttpStatus::kOk.Code()
            LOG(kMedia, "ProtocolHttp::Get 'OK' (%lld bytes)\n", iTotalBytes);
        }

    }
    catch(HttpError&) {
        LOG(kMedia, "ProtocolHttp::Get HttpError\n");
    }
    catch(ReaderError&) {
        LOG(kMedia, "ProtocolHttp::Get ReaderError\n");
    }
    return EProtocolGetErrorUnrecoverable;
}

EStreamPlay ProtocolHttp::OkToPlay(TUint aTrackId, TUint aStreamId)
{
    const EStreamPlay canPlay = iIdProvider->OkToPlay(aTrackId, aStreamId);
    if (canPlay != ePlayNo && iLive && iStreamId == aStreamId) {
        iSem.Signal();
    }
    return canPlay;
}

TUint ProtocolHttp::TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset)
{
    LOG(kMedia, "ProtocolHttp::Seek\n");

    iLock.Wait();
    const TBool streamIsValid = (iProtocolManager->IsCurrentTrack(aTrackId) && iStreamId == aStreamId);
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

TUint ProtocolHttp::TryStop(TUint aTrackId, TUint aStreamId)
{
    iLock.Wait();
    const TBool stop = (iProtocolManager->IsCurrentTrack(aTrackId) && iStreamId == aStreamId);
    if (stop) {
        iNextFlushId = iFlushIdProvider->NextFlushId();
        iStopped = true;
        iTcpClient.Interrupt(true);
        if (iLive) {
            iSem.Signal();
        }
    }
    iLock.Signal();
    return (stop? iNextFlushId : MsgFlush::kIdInvalid);
}

TBool ProtocolHttp::TryGet(IWriter& aWriter, TUint aTrackId, TUint aStreamId, TUint64 aOffset, TUint aBytes)
{
    iLock.Wait();
    const TBool isCurrent = (iProtocolManager->IsCurrentTrack(aTrackId) && iStreamId == aStreamId);
    TBool success = false;
    if (isCurrent) {
        success = iProtocolManager->Get(aWriter, iUri.AbsoluteUri(), aOffset, aBytes);
    }
    iLock.Signal();
    return success;
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
    Brn buf = iDechunker.Read(bytes);
    iOffset += buf.Bytes();
    return buf;
}

Brn ProtocolHttp::ReadUntil(TByte aSeparator)
{
    ASSERT(!iStreamIncludesMetaData); /* assume only audio streams contain icy data
                                         and they just read a number of bytes */
    Brn buf = iDechunker.ReadUntil(aSeparator);
    iOffset += buf.Bytes();
    return buf;
}

void ProtocolHttp::ReadFlush()
{
    iDechunker.ReadFlush();
}

void ProtocolHttp::ReadInterrupt()
{
    iDechunker.ReadInterrupt();
}

Brn ProtocolHttp::ReadRemaining()
{
    Brn buf = iDechunker.ReadRemaining();
    iOffset += buf.Bytes();
    return buf;
}

void ProtocolHttp::Reinitialise(const Brx& aUri)
{
    iTotalBytes = iSeekPos = iOffset = 0;
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iSeekable = iSeek = iLive = iStarted = iStopped = iStreamIncludesMetaData = false;
    iDataChunkSize = iDataChunkRemaining = 0;
    iContentProcessor = NULL;
    iNextFlushId = MsgFlush::kIdInvalid;
    (void)iSem.Clear();
    iUri.Replace(aUri);
    iIcyMetadata.SetBytes(0);
    iNewIcyMetadata.SetBytes(0);
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
    if (iHeaderContentType.Received() && (iHeaderContentType.Type() == Brn("audio/x-mpegurl") ||
                                          iHeaderContentType.Type() == Brn("video/x-ms-asf"))) { // FIXME - we'll end up slowly duplicating ContentProcessor mime type checks this way
        // if the stream has a known Content-Type we assume it is a url pointing towards a radio stream, rather than the radio stream itself
        iLive = false;
    }
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

    iDechunker.SetChunked(iHeaderTransferEncoding.IsChunked());

    if (!iStarted && iLive) {
        StartStream();
        return EProtocolStreamErrorRecoverable;
    }

    return ProcessContent();
}

ProtocolStreamResult ProtocolHttp::DoSeek(TUint64 aOffset)
{
    LOG(kMedia, "ProtocolHttp::DoRestream %lld\n", aOffset);

    Interrupt(false);
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
    //iTcpClient.LogVerbose(true);
    Close();
    if (!Connect(iUri, 80)) {
        LOG(kMedia, "ProtocolHttp::WriteRequest Connection failure\n");
        return 0;
    }

    /* GETting ASX for BBC Scotland responds with invalid chunking if we request ICY metadata.
       Suppress this header if we're requesting a resource with an extension that matches
       a known ContentProcessor */
    Brn path(iUri.Path());
    ASSERT_DEBUG(path.Bytes() > 0 && path[0] != '.');
    Brn ext;
    for (TUint i=path.Bytes()-1; i!=0; i--) {
        if (path[i] == '.') {
            ext.Set(path.Split(i));
            break;
        }
    }
    TBool suppressIcyHeader = false;
    if (Ascii::CaseInsensitiveEquals(ext, Brn(".asx")) ||
        Ascii::CaseInsensitiveEquals(ext, Brn(".pls")) ||
        Ascii::CaseInsensitiveEquals(ext, Brn(".m3u")) ||
        Ascii::CaseInsensitiveEquals(ext, Brn(".xml")) ||
        Ascii::CaseInsensitiveEquals(ext, Brn(".opml"))) {
        suppressIcyHeader = true;;
    }
    try {
        LOG(kMedia, "ProtocolHttp::Stream send request\n");
        iWriterRequest.WriteMethod(Http::kMethodGet, iUri.PathAndQuery(), Http::eHttp11);
        const TUint port = (iUri.Port() == -1? 80 : (TUint)iUri.Port());
        Http::WriteHeaderHostAndPort(iWriterRequest, iUri.Host(), port);
        iWriterRequest.WriteHeader(Http::kHeaderUserAgent, kUserAgentString); // FIXME - why are we sending a UA?
        Http::WriteHeaderConnectionClose(iWriterRequest);
        if (!suppressIcyHeader) {
            HeaderIcyMetadata::Write(iWriterRequest);
        }
        Http::WriteHeaderRangeFirstOnly(iWriterRequest, aOffset);
        iWriterRequest.WriteFlush();
    }
    catch(WriterError&) {
        LOG(kMedia, "ProtocolHttp::WriteRequest writer error\n");
        return 0;
    }

    try {
        LOG(kMedia, "ProtocolHttp::WriteRequest read response\n");
        //iTcpClient.LogVerbose(true);
        iReaderResponse.Read();
        //iTcpClient.LogVerbose(false);
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
            TUint bytes = 100;
            if (iTotalBytes != 0 && bytes > iTotalBytes) {
                bytes = (TUint)iTotalBytes;
            }
            Brn contentStart;
            try {
                contentStart.Set(iReaderBuf.Peek(bytes)); // FIXME - should ideally be reading via iDechunker here
            }
            catch (ReaderError&) {
                if (iTotalBytes != 0) {
                    throw;
                }
                contentStart.Set(iReaderBuf.Snaffle());
            }
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
    iOffset += metadataBytes;

    if (metadataBytes != 0) {

        Brn buf = iReaderBuf.Read(metadataBytes);

        iNewIcyMetadata.Replace("<DIDL-Lite xmlns:dc='http://purl.org/dc/elements/1.1/' ");
        iNewIcyMetadata.Append("xmlns:upnp='urn:schemas-upnp-org:metadata-1-0/upnp/' ");
        iNewIcyMetadata.Append("xmlns='urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/'>");
        iNewIcyMetadata.Append("<item id='' parentID='' restricted='True'><dc:title>");

        Parser data(buf);
        while(!data.Finished()) {
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
                    iIcyMetadata.Replace(iNewIcyMetadata);
                    iSupply->OutputMetadata(iIcyMetadata);
                }
                break;
            }
        }
    }
}


