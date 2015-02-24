#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Media/Supply.h>

#include <algorithm>

namespace OpenHome {
namespace Media {

class HttpReader
{

};

class ITimerHandler
{
public:
    virtual void TimerFired() = 0;
    virtual ~ITimerHandler() {}
};

class ITimer
{
public:
    virtual void Start(TUint aDurationMs, ITimerHandler& aHandler) = 0;
    virtual void Cancel() = 0;
    virtual ~ITimer() {}
};

class TimerGeneric : public ITimer
{
public:
    TimerGeneric(Environment& aEnv, const TChar* aId);
    ~TimerGeneric();
private: // from ITimer
    void Start(TUint aDurationMs, ITimerHandler& aHandler) override;
    void Cancel() override;
private:
    void TimerFired();
private:
    Timer* iTimer;
    ITimerHandler* iHandler;
    TBool iPending;
    Mutex iLock;
};

class ISegmentUriProvider
{
public:
    virtual TUint NextSegmentUri(Uri& aUri) = 0;    // returns segment duration (in seconds)
    virtual ~ISegmentUriProvider() {}
};

// FIXME - must be able to interrupt
class HlsM3uReader : public ITimerHandler, public ISegmentUriProvider
{
private:
    static const TUint kMaxM3uVersion = 2;
    static const TUint kMillisecondsPerSecond = 1000;
    static const TUint kReadBufferBytes = 9 * 1024; // Based on ProtocolHttp buffer size.
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeoutMs = 3000;
public:
    HlsM3uReader(Environment& aEnv, ITimer& aTimer);
    // FIXME - take URI as constructor param?
    void SetUri(const Uri& aUri);
    TUint Version() const;
private: // from ITimerHandler
    void TimerFired() override;
private: // from ISegmentUriProvider
    TUint NextSegmentUri(Uri& aUri) override;
public:
    void Interrupt(TBool aInterrupt);
    void Close();
private:
    TBool Connect(const OpenHome::Uri& aUri, TUint aDefaultPort);
    void Open();
    TUint WriteRequest(TUint64 aOffset);
    void ReloadVariantPlaylist();
    void SetSegmentUri(Uri& aUri, const Brx& aSegmentUri);
private:
    // FIXME - could have some intelligent logic to limit retries
    // e.g. in addition to waiting for, at the minimum, the target duration (or half target duration if playlist has not changed), could instead choose:
    // max(targetDuration, sum(newSegmentDurations)-targetDuration);
    Environment& iEnv;
    ITimer& iTimer;
    Srs<kReadBufferBytes> iReaderBuf;
    Sws<kWriteBufferBytes> iWriterBuf;
    Mutex iLock;
    SocketTcpClient iTcpClient;
    TBool iSocketIsOpen;
    WriterHttpRequest iWriterRequest;
    ReaderHttpResponse iReaderResponse;
    ReaderHttpChunked iDechunker;
    HttpHeaderContentType iHeaderContentType;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderLocation iHeaderLocation;
    HttpHeaderTransferEncoding iHeaderTransferEncoding;
    OpenHome::Uri iUri;
    TBool iActive;
    TUint64 iTotalBytes;
    TUint64 iOffset;
    TUint iVersion;
    TUint64 iMediaSequence;
    TUint64 iLastSegment;
    TUint iTargetDuration;
    Brn iNextLine;
    Semaphore iSem;
};

class SegmentStreamer : public IProtocolReader
{
private:
    static const TUint kReadBufferBytes = 9 * 1024; // Based on ProtocolHttp buffer size.
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeoutMs = 3000;
public:
    SegmentStreamer(Environment& aEnv);
    ProtocolStreamResult Stream(ISegmentUriProvider& aSegmentUriProvider);
public: // from IProtocolReader
    Brn Read(TUint aBytes) override;
    Brn ReadUntil(TByte aSeparator) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
    Brn ReadRemaining() override;
private:
    TBool Connect(const OpenHome::Uri& aUri, TUint aDefaultPort);
    void Interrupt(TBool aInterrupt);
    void Open();
    void Close();
    TUint WriteRequest(TUint64 aOffset);
    void GetNextSegment();
private:
    Environment& iEnv;
    Srs<kReadBufferBytes> iReaderBuf;
    Sws<kWriteBufferBytes> iWriterBuf;
    Mutex iLock;
    SocketTcpClient iTcpClient;
    TBool iSocketIsOpen;
    WriterHttpRequest iWriterRequest;
    ReaderHttpResponse iReaderResponse;
    ReaderHttpChunked iDechunker;
    HttpHeaderContentType iHeaderContentType;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderLocation iHeaderLocation;
    HttpHeaderTransferEncoding iHeaderTransferEncoding;
    OpenHome::Uri iUri;
    TUint64 iTotalBytes;
    TUint64 iOffset;
    ISegmentUriProvider* iSegmentUriProvider;
    Semaphore iSem;
};

class ProtocolHls : public Protocol
{
public:
    ProtocolHls(Environment& aEnv);
    ~ProtocolHls();
private: // from Protocol
    void Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream) override;
    void Interrupt(TBool aInterrupt) override;
    ProtocolStreamResult Stream(const Brx& aUri) override;
    ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes) override;
    void Deactivated() override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    TBool TryGet(IWriter& aWriter, TUint aStreamId, TUint64 aOffset, TUint aBytes) override;
private:
    void Reinitialise();
    void StartStream(const Uri& aUri);
private:
    Supply* iSupply;
    TimerGeneric iTimer;
    HlsM3uReader iM3uReader;
    SegmentStreamer iSegmentStreamer;
    TUint iStreamId;
    TBool iStarted;
    TBool iStopped;
    ContentProcessor* iContentProcessor;
    TUint iNextFlushId;
    Semaphore iSem;
    Mutex iLock;
};

};  // namespace Media
};  // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;


Protocol* ProtocolFactory::NewHls(Environment& aEnv)
{ // static
    return new ProtocolHls(aEnv);
}


// TimerGeneric

TimerGeneric::TimerGeneric(Environment& aEnv, const TChar* aId)
    : iHandler(NULL)
    , iPending(false)
    , iLock("TIGL")
{
    iTimer = new Timer(aEnv, MakeFunctor(*this, &TimerGeneric::TimerFired), aId);
}

TimerGeneric::~TimerGeneric()
{
    delete iTimer;
}

void TimerGeneric::Start(TUint aDurationMs, ITimerHandler& aHandler)
{
    AutoMutex a(iLock);
    ASSERT(!iPending);  // Can't set timer when it's already pending.
    iPending = true;
    iHandler = &aHandler;
    iTimer->FireIn(aDurationMs);
}

void TimerGeneric::Cancel()
{
    AutoMutex a(iLock);
    ASSERT(!iPending);
    iPending = false;
    iTimer->Cancel();
}

void TimerGeneric::TimerFired()
{
    AutoMutex a(iLock);
    if (iPending) {
        iPending = false;
        iHandler->TimerFired(); // FIXME - problem if iHandler calls back into ::Start() during TimerFired()
    }
}


// HlsM3uReader

HlsM3uReader::HlsM3uReader(Environment& aEnv, ITimer& aTimer)
    : iEnv(aEnv)
    , iTimer(aTimer)
    , iWriterBuf(iTcpClient)
    , iReaderBuf(iTcpClient)
    , iLock("HMRL")
    , iSocketIsOpen(false)
    , iWriterRequest(iWriterBuf)
    , iReaderResponse(aEnv, iReaderBuf)
    , iDechunker(iReaderBuf)
    , iActive(false)
    , iTotalBytes(0)
    , iVersion(1)
    , iMediaSequence(0)
    , iLastSegment(0)
    , iTargetDuration(0)
    , iSem("HMRS", 0)
{
    iReaderResponse.AddHeader(iHeaderContentType);
    iReaderResponse.AddHeader(iHeaderContentLength);
    iReaderResponse.AddHeader(iHeaderLocation);
    iReaderResponse.AddHeader(iHeaderTransferEncoding);
}

void HlsM3uReader::SetUri(const Uri& aUri)
{
    iTimer.Cancel();
    iSem.Signal();
    iUri.Replace(aUri.AbsoluteUri());
    iActive = true;

    ReloadVariantPlaylist();
}

TUint HlsM3uReader::Version() const
{
    return iVersion;
}

TUint HlsM3uReader::NextSegmentUri(Uri& aUri)
{
    TUint duration = 0;
    Brn segmentUri = Brx::Empty();
    try {
        TBool expectUri = false;
        while (segmentUri == Brx::Empty()) {
            Brn uri;
            if (iOffset >= iTotalBytes) {
                ReloadVariantPlaylist();
            }


            if (iNextLine == Brx::Empty()) {
                iNextLine = iDechunker.ReadUntil('\n');
                iOffset += iNextLine.Bytes()+1;  // Separator has been trimmed.
            }
            if (expectUri) {
                segmentUri = iNextLine;    // FIXME - strip '\r' from line?
                expectUri = false;
                Log::Print("segmentUri: ");
                Log::Print(segmentUri);
                Log::Print("\n");
                iLastSegment++;
            }
            else {
                Parser p(iNextLine);
                Brn tag = p.Next(':');
                if (tag == Brn("#EXTINF")) {
                    duration = Ascii::Uint(p.Next(','));    // Duration is always TUint in version 2 and below.
                    Log::Print("duration: %u\n", duration);
                    expectUri = true;
                }
            }
            iNextLine = Brx::Empty();
        }

        try {
            SetSegmentUri(aUri, segmentUri);
        }
        catch (UriError&) {
            LOG(kMedia, "HlsM3uReader::NextSegmentUri UriError\n");
            return 0;
        }
    }
    catch (AsciiError&) {   // FIXME - throw these exceptions up?
        LOG(kMedia, "HlsM3uReader::NextSegmentUri AsciiError\n");
        return 0;
    }
    catch (HttpError&) {
        LOG(kMedia, "HlsM3uReader::NextSegmentUri HttpError\n");
        return 0;
    }
    catch (ReaderError&) {
        LOG(kMedia, "HlsM3uReader::NextSegmentUri ReaderError\n");
        return 0;
    }

    return duration;
}

void HlsM3uReader::TimerFired()
{
    iSem.Signal();
}

TBool HlsM3uReader::Connect(const OpenHome::Uri& aUri, TUint aDefaultPort)
{
    LOG(kMedia, ">HlsM3uReader::Connect\n");

    Endpoint endpoint;
    try {
        endpoint.SetAddress(aUri.Host());
        TInt port = aUri.Port();
        if (port == -1) {
            port = (TInt)aDefaultPort;
        }
        endpoint.SetPort(port);
    }
    catch (NetworkError&) {
        LOG(kMedia, "<HlsM3uReader::Connect error setting address and port\n");
        return false;
    }

    try {
        Open();
    }
    catch (NetworkError&) {
        LOG(kMedia, "<HlsM3uReader::Connect error opening\n");
        return false;
    }
    try {
        iTcpClient.Connect(endpoint, kConnectTimeoutMs);
    }
    catch (NetworkTimeout&) {
        Close();
        LOG(kMedia, "<HlsM3uReader::Connect error connecting\n");
        return false;
    }

    LOG(kMedia, "<HlsM3uReader::Connect\n");
    return true;
}

void HlsM3uReader::Interrupt(TBool aInterrupt)
{
    iLock.Wait();
    if (iActive) {
        iTcpClient.Interrupt(aInterrupt);
    }
    iLock.Signal();
}

void HlsM3uReader::Open()
{
    LOG(kMedia, "HlsM3uReader::Open\n");

    iTcpClient.Open(iEnv);
    ASSERT(!iSocketIsOpen);
    iSocketIsOpen = true;
}

void HlsM3uReader::Close()
{
    LOG(kMedia, "HlsM3uReader::Close\n");

    if (iSocketIsOpen) {
        iSocketIsOpen = false;
        iTcpClient.Close();
    }
}

TUint HlsM3uReader::WriteRequest(TUint64 /*aOffset*/)
{
    //iTcpClient.LogVerbose(true);
    Close();
    const TUint port = (iUri.Port() == -1? 80 : (TUint)iUri.Port());
    if (!Connect(iUri, port)) {
        LOG(kMedia, "HlsM3uReader::WriteRequest Connection failure\n");
        return 0;
    }

    try {
        LOG(kMedia, "HlsM3uReader::WriteRequest send request\n");
        iWriterRequest.WriteMethod(Http::kMethodGet, iUri.PathAndQuery(), Http::eHttp11);
        const TUint port = (iUri.Port() == -1? 80 : (TUint)iUri.Port());
        Http::WriteHeaderHostAndPort(iWriterRequest, iUri.Host(), port);
        //iWriterRequest.WriteHeader(Http::kHeaderUserAgent, kUserAgentString); // FIXME - why are we sending a UA?
        Http::WriteHeaderConnectionClose(iWriterRequest);
        iWriterRequest.WriteFlush();
    }
    catch(WriterError&) {
        LOG(kMedia, "HlsM3uReader::WriteRequest writer error\n");
        return 0;
    }

    try {
        LOG(kMedia, "HlsM3uReader::WriteRequest read response\n");
        //iTcpClient.LogVerbose(true);
        iReaderResponse.Read();
        //iTcpClient.LogVerbose(false);
    }
    catch(HttpError&) {
        LOG(kMedia, "HlsM3uReader::WriteRequest http error\n");
        return 0;
    }
    catch(ReaderError&) {
        LOG(kMedia, "HlsM3uReader::WriteRequest reader error\n");
        return 0;
    }
    const TUint code = iReaderResponse.Status().Code();
    LOG(kMedia, "HlsM3uReader::WriteRequest response code %d\n", code);
    return code;
}

void HlsM3uReader::ReloadVariantPlaylist()
{
    // Timer should be started BEFORE refreshing playlist.
    // However, not very useful if we don't yet have target duration, so just
    // start timer after processing part of playlist.

    iSem.Wait();
    iSem.Clear();   // Clear in case iSem has been signalled multiple times. E.g., blocking while filling buffers during last playlist reload.

    TUint code;
    for (;;) { // loop until we don't get a redirection response (i.e. normally don't loop at all!)
        code = WriteRequest(0);
        if (code == 0) {
            //THROW(InvalidUri/MalformedUri)
            //return EProtocolStreamErrorUnrecoverable;
        }
        // Check for redirection
        if (code >= HttpStatus::kRedirectionCodes && code <= HttpStatus::kClientErrorCodes) {
            if (!iHeaderLocation.Received()) {
                //THROW(InvalidURI);
                //return EProtocolStreamErrorUnrecoverable;
            }
            iUri.Replace(iHeaderLocation.Location());
            continue;
        }
        break;
    }

    if (code != 0) {
        iTotalBytes = iHeaderContentLength.ContentLength();
        iOffset = 0;
    }


    // FIXME - move this block to helper method
    TUint64 skipSegments = 0;
    try {
        while (iOffset < iTotalBytes) {
            // FIXME - move next 2 lines to helper function.
            iNextLine = iDechunker.ReadUntil('\n');
            iOffset += iNextLine.Bytes()+1;  // Separator has been trimmed.
            Parser p(iNextLine);
            Brn tag = p.Next(':');

            // FIXME - have HTTP style header processors?

            // FIXME - what about #EXT-X-ENDLIST
            if (tag == Brn("#EXT-X-VERSION")) {
                iVersion = Ascii::Uint(p.Next());
                if (iVersion > kMaxM3uVersion) {
                    LOG(kMedia, "Unsupported M3U version. Max supported version: %u, version encountered: %u\n", kMaxM3uVersion, iVersion);
                }
                Log::Print("iVersion: %u\n", iVersion);
            }
            if (tag == Brn("#EXT-X-MEDIA-SEQUENCE")) {
                // If this isn't found, it must be assumed that first segment in playlist is 0.
                TUint64 mediaSeq = Ascii::Uint64(p.Next());
                if (iLastSegment == 0) {
                    iLastSegment = mediaSeq;
                }
                if (mediaSeq <= iLastSegment) {
                    skipSegments = (iLastSegment-mediaSeq)+1;
                }
                Log::Print("mediaSeq: %llu\n", mediaSeq);
            }
            else if (tag == Brn("#EXT-X-TARGETDURATION")) {
                iTargetDuration = Ascii::Uint(p.Next());
                Log::Print("iTargetDuration: %u\n", iTargetDuration);
            }
            else if (tag == Brn("#EXTINF")) {
                if (skipSegments > 0) {
                    skipSegments--;
                }
                else {
                    // Found start/continuation of audio.
                    break;
                }
            }
        }
    }
    catch (AsciiError&) {
        LOG(kMedia, "HlsM3uReader::NextSegmentUri AsciiError\n");
        //THROW
    }
    catch (HttpError&) {    // FIXME - throw these exceptions up?
        LOG(kMedia, "HlsM3uReader::NextSegmentUri HttpError\n");
        //THROW
    }
    catch (ReaderError&) {
        LOG(kMedia, "HlsM3uReader::NextSegmentUri ReaderError\n");
        //THROW
    }

    if (iOffset >= iTotalBytes) {
        LOG(kMedia, "HlsM3uReader::ReloadVariantPlaylist exhausted file\n");
        // THROW exception here
    }

    if (iTargetDuration == 0) { // #EXT-X-TARGETDURATION is a required tag.
        LOG(kMedia, "HlsM3uReader::ReloadVariantPlaylist malformed file\n");
        // THROW exception here
    }

    iTimer.Start(iTargetDuration*kMillisecondsPerSecond, *this);
}

void HlsM3uReader::SetSegmentUri(Uri& aUri, const Brx& aSegmentUri)
{
    // Segment URI MAY be relative.
    // If it is relative, it is relative to URI of playlist that contains it.
    static const Brn kSchemeHttp("http");

    Brn split(aSegmentUri.Ptr(), kSchemeHttp.Bytes());
    split;


    if (aSegmentUri.Bytes() > kSchemeHttp.Bytes()
            && Brn(aSegmentUri.Ptr(), kSchemeHttp.Bytes()) == kSchemeHttp) {
        // Segment URI is absolute.

        // May throw UriError.
        aUri.Replace(aSegmentUri);
    }
    else {
        // Segment URI is relative.
        Bws<Uri::kMaxUriBytes> uriBuf;
        uriBuf.Replace(iUri.Scheme());
        uriBuf.Append("://");
        uriBuf.Append(iUri.Host());
        TInt port = iUri.Port();
        if (port > 0) {
            uriBuf.Append(":");
            Ascii::AppendDec(uriBuf, iUri.Port());
        }

        // Get URI path minus file.
        Parser uriParser(iUri.Path());
        while (!uriParser.Finished()) {
            Brn fragment = uriParser.Next('/');
            if (!uriParser.Finished()) {
                uriBuf.Append(fragment);
                uriBuf.Append("/");
            }
        }

        // May throw UriError.
        aUri.Replace(uriBuf, aSegmentUri);
    }
}


// SegmentStreamer

SegmentStreamer::SegmentStreamer(Environment& aEnv)
    : iEnv(aEnv)
    , iSegmentUriProvider(NULL)
    , iReaderBuf(iTcpClient)
    , iWriterBuf(iTcpClient)
    , iLock("SESL")
    , iSocketIsOpen(false)
    , iWriterRequest(iWriterBuf)
    , iReaderResponse(iEnv, iReaderBuf)
    , iDechunker(iReaderBuf)
    , iTotalBytes(0)
    , iOffset(0)
    , iSem("SEGS", 0)
{
    iReaderResponse.AddHeader(iHeaderContentType);
    iReaderResponse.AddHeader(iHeaderContentLength);
    iReaderResponse.AddHeader(iHeaderLocation);
    iReaderResponse.AddHeader(iHeaderTransferEncoding);
}

ProtocolStreamResult SegmentStreamer::Stream(ISegmentUriProvider& aSegmentUriProvider)
{
    iSegmentUriProvider = &aSegmentUriProvider;
    GetNextSegment();

    return EProtocolStreamErrorUnrecoverable;   // FIXME - shouldn't return anything
}

Brn SegmentStreamer::Read(TUint aBytes)
{
    //TUint bytesRemaining = aBytes;
    //while (bytesRemaining > 0) {
    //    TUint bytes = aBytes;
    //    TUint segmentBytesRemaining = iTotalBytes-iOffset;
    //    if (bytesRemaining > segmentBytesRemaining) {
    //        bytes = segmentBytesRemaining;
    //    }
    if (iOffset == iTotalBytes) {
        GetNextSegment();
    }
        Brn buf = iDechunker.Read(aBytes);
        iOffset += buf.Bytes(); // if bytes remaining < aBytes, must request next segment
    //}

    return buf;
}

Brn SegmentStreamer::ReadUntil(TByte aSeparator)
{
    if (iOffset == iTotalBytes) {
        GetNextSegment();
    }
    Brn buf = iDechunker.ReadUntil(aSeparator);
    iOffset += buf.Bytes()+1;   // Separator has been trimmed.
    return buf;
}

void SegmentStreamer::ReadFlush()
{
    iDechunker.ReadFlush();
}

void SegmentStreamer::ReadInterrupt()
{
    iDechunker.ReadInterrupt();
}

Brn SegmentStreamer::ReadRemaining()
{
    if (iOffset == iTotalBytes) {
        GetNextSegment();
    }
    Brn buf = iDechunker.ReadRemaining();
    iOffset += buf.Bytes();
    // FIXME - request next segment
    return buf;
}

TBool SegmentStreamer::Connect(const OpenHome::Uri& aUri, TUint aDefaultPort)
{
    LOG(kMedia, ">SegmentStreamer::Connect\n");

    Endpoint endpoint;
    try {
        endpoint.SetAddress(aUri.Host());
        TInt port = aUri.Port();
        if (port == -1) {
            port = (TInt)aDefaultPort;
        }
        endpoint.SetPort(port);
    }
    catch (NetworkError&) {
        LOG(kMedia, "<SegmentStreamer::Connect error setting address and port\n");
        return false;
    }

    try {
        Open();
    }
    catch (NetworkError&) {
        LOG(kMedia, "<SegmentStreamer::Connect error opening\n");
        return false;
    }
    try {
        iTcpClient.Connect(endpoint, kConnectTimeoutMs);
    }
    catch (NetworkTimeout&) {
        Close();
        LOG(kMedia, "<SegmentStreamer::Connect error connecting\n");
        return false;
    }

    LOG(kMedia, "<SegmentStreamer::Connect\n");
    return true;
}

void SegmentStreamer::Interrupt(TBool aInterrupt)
{
    iLock.Wait();
    //if (iActive) {
    if (iSocketIsOpen) {
        iTcpClient.Interrupt(aInterrupt);
    }
    iLock.Signal();
}

void SegmentStreamer::Open()
{
    LOG(kMedia, "SegmentStreamer::Open\n");

    iTcpClient.Open(iEnv);
    ASSERT(!iSocketIsOpen);
    iSocketIsOpen = true;
}

void SegmentStreamer::Close()
{
    LOG(kMedia, "SegmentStreamer::Close\n");

    if (iSocketIsOpen) {
        iSocketIsOpen = false;
        iTcpClient.Close();
    }
}

TUint SegmentStreamer::WriteRequest(TUint64 /*aOffset*/)
{
    //iTcpClient.LogVerbose(true);
    Close();
    const TUint port = (iUri.Port() == -1? 80 : (TUint)iUri.Port());
    if (!Connect(iUri, port)) {
        LOG(kMedia, "SegmentStreamer::WriteRequest Connection failure\n");
        return 0;
    }

    try {
        LOG(kMedia, "SegmentStreamer::WriteRequest send request\n");
        iWriterRequest.WriteMethod(Http::kMethodGet, iUri.PathAndQuery(), Http::eHttp11);
        const TUint port = (iUri.Port() == -1? 80 : (TUint)iUri.Port());
        Http::WriteHeaderHostAndPort(iWriterRequest, iUri.Host(), port);
        //iWriterRequest.WriteHeader(Http::kHeaderUserAgent, kUserAgentString); // FIXME - why are we sending a UA?
        Http::WriteHeaderConnectionClose(iWriterRequest);
        //Http::WriteHeaderRangeFirstOnly(iWriterRequest, aOffset);
        iWriterRequest.WriteFlush();
    }
    catch(WriterError&) {
        LOG(kMedia, "SegmentStreamer::WriteRequest writer error\n");
        return 0;
    }

    try {
        LOG(kMedia, "SegmentStreamer::WriteRequest read response\n");
        //iTcpClient.LogVerbose(true);
        iReaderResponse.Read();
        //iTcpClient.LogVerbose(false);
    }
    catch(HttpError&) {
        LOG(kMedia, "SegmentStreamer::WriteRequest http error\n");
        return 0;
    }
    catch(ReaderError&) {
        LOG(kMedia, "SegmentStreamer::WriteRequest reader error\n");
        return 0;
    }
    const TUint code = iReaderResponse.Status().Code();
    LOG(kMedia, "SegmentStreamer::WriteRequest response code %d\n", code);
    return code;
}

void SegmentStreamer::GetNextSegment()
{
    Uri segment;
    TUint duration = iSegmentUriProvider->NextSegmentUri(segment);
    duration;
    iUri.Replace(segment.AbsoluteUri());  // FIXME - don't really need iUri?

    TUint code;
    for (;;) { // loop until we don't get a redirection response (i.e. normally don't loop at all!)
        code = WriteRequest(0);
        if (code == 0) {
            //THROW(InvalidUri/MalformedUri)
            //return EProtocolStreamErrorUnrecoverable;
        }
        // Check for redirection
        if (code >= HttpStatus::kRedirectionCodes && code <= HttpStatus::kClientErrorCodes) {
            if (!iHeaderLocation.Received()) {
                //THROW(InvalidURI);
                //return EProtocolStreamErrorUnrecoverable;
            }
            iUri.Replace(iHeaderLocation.Location());
            continue;
        }
        break;
    }

    if (code != 0) {
        iTotalBytes = iHeaderContentLength.ContentLength();
        iOffset = 0;
    }
}


// ProtocolHls

static const Brn kUserAgentString("Linn DS"); // FIXME

ProtocolHls::ProtocolHls(Environment& aEnv)
    : Protocol(aEnv)
    , iSupply(NULL)
    , iTimer(iEnv, "PHLS")
    , iM3uReader(iEnv, iTimer)
    , iSegmentStreamer(iEnv)
    , iSem("PRTH", 0)
    , iLock("PRHL")
{
}

ProtocolHls::~ProtocolHls()
{
    delete iSupply;
}

void ProtocolHls::Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream)
{
    iSupply = new Supply(aMsgFactory, aDownstream);
}

void ProtocolHls::Interrupt(TBool aInterrupt)
{
    iLock.Wait();
    if (iActive) {
        LOG(kMedia, "ProtocolHls::Interrupt(%u)\n", aInterrupt);
        if (aInterrupt) {
            iStopped = true;
        }
        iM3uReader.Interrupt(aInterrupt);
        //iTcpClient.Interrupt(aInterrupt);
    }
    iLock.Signal();
}

ProtocolStreamResult ProtocolHls::Stream(const Brx& aUri)
{
    // There is no notion of a live or seekable stream in HLS!
    //
    // By default, all streams are live.
    //
    // It is legal to perform a seek, as long as it is within the current
    // stream segments available within the variant playlist.
    // (i.e., if the first available segment was some_stream-002.ts, and the
    // user wished to seek to a position that would be in some_stream-001.ts,
    // that seek would be invalid.)
    //
    // It is also legal to attempt to pause an HLS stream (albeit that the
    // position at which it can resume is bounded by the segments available in
    // the variant playlist).
    // (i.e., if paused during some_stream-002.ts and when unpaused first
    // segment now available was some_stream-004.ts, there would be a forced
    // discontinuity in the audio.)
    //
    // Given the limited usefulness of this behaviour (because it is bound by
    // the limits of the periodically changing variant playlist), the use case
    // (why would a client wish to seek during a live radio stream?), and the
    // increased complexity of the code required, just don't allow
    // seeking/pausing.



    Reinitialise();
    Uri uri(aUri);
    LOG(kMedia, "ProtocolHls::Stream ");
    LOG(kMedia, uri.AbsoluteUri());
    LOG(kMedia, "\n");

    if (uri.Scheme() != Brn("hls")) {
        LOG(kMedia, "ProtocolHls::Stream scheme not recognised\n");
        return EProtocolErrorNotSupported;
    }

    if (!iStarted) {
        StartStream(uri);
    }



    //// don't want to buffer content from a live stream
    //// ...so need to wait on pipeline signalling it is ready to play
    //LOG(kMedia, "ProtocolHttp::Stream live stream waiting to be (re-)started\n");
    //iM3uReader.Close();
    //iSem.Wait();
    //LOG(kMedia, "ProtocolHttp::Stream live stream restart\n");
    //res = EProtocolStreamErrorRecoverable; // bodge to drop into the loop below





    iM3uReader.SetUri(uri); // rename to Reinitialise()
    iSegmentStreamer.Stream(iM3uReader);

    if (iContentProcessor == NULL) {
        iContentProcessor = iProtocolManager->GetAudioProcessor();  // returns stream state
    }
    ProtocolStreamResult res = EProtocolStreamErrorRecoverable;
    while (res == EProtocolStreamErrorRecoverable) {    // FIXME - what is terminating condition?
        iContentProcessor->Stream(iSegmentStreamer, 0);
    }

    // FIXME - sort this:
    res = EProtocolStreamErrorUnrecoverable;

    iM3uReader.Close();

    iLock.Wait();
    if (iStopped && iNextFlushId != MsgFlush::kIdInvalid) {
        iSupply->OutputFlush(iNextFlushId);
    }
    // clear iStreamId to prevent TrySeek or TryStop returning a valid flush id
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iLock.Signal();

    return res;
}

ProtocolGetResult ProtocolHls::Get(IWriter& /*aWriter*/, const Brx& /*aUri*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return EProtocolGetErrorNotSupported;
}

void ProtocolHls::Deactivated()
{
    if (iContentProcessor != NULL) {
        iContentProcessor->Reset();
        iContentProcessor = NULL;
    }
    iM3uReader.Close();
}

EStreamPlay ProtocolHls::OkToPlay(TUint aStreamId)
{
    LOG(kMedia, "> ProtocolHls::OkToPlay(%u)\n", aStreamId);
    const EStreamPlay canPlay = iIdProvider->OkToPlay(aStreamId);
    if (canPlay != ePlayNo && iStreamId == aStreamId) {
        iSem.Signal();
    }
    LOG(kMedia, "< ProtocolHls::OkToPlay(%u) == %s\n", aStreamId, kStreamPlayNames[canPlay]);
    return canPlay;
}

TUint ProtocolHls::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    LOG(kMedia, "ProtocolHls::TrySeek\n");
    return MsgFlush::kIdInvalid;
}

TUint ProtocolHls::TryStop(TUint aStreamId)
{
    iLock.Wait();
    const TBool stop = iProtocolManager->IsCurrentStream(aStreamId);
    if (stop) {
        if (iNextFlushId == MsgFlush::kIdInvalid) {
            /* If a valid flushId is set then We've previously promised to send a Flush but haven't
            got round to it yet.  Re-use the same id for any other requests that come in before
            our main thread gets a chance to issue a Flush */
            iNextFlushId = iFlushIdProvider->NextFlushId();
        }
        iStopped = true;
        iM3uReader.Interrupt(true);
        iSem.Signal();
    }
    iLock.Signal();
    return (stop? iNextFlushId : MsgFlush::kIdInvalid);
}

TBool ProtocolHls::TryGet(IWriter& /*aWriter*/, TUint /*aStreamId*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    LOG(kMedia, "ProtocolHls::TryGet\n");
    return false;;
}

void ProtocolHls::Reinitialise()
{
    Log::Print("ProtocolHls::Reinitialise\n");
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iStarted = iStopped = false;
    iContentProcessor = NULL;
    iNextFlushId = MsgFlush::kIdInvalid;
    (void)iSem.Clear();
}

void ProtocolHls::StartStream(const Uri& aUri)
{
    LOG(kMedia, "ProtocolHls::StartStream\n");
    TBool totalBytes = 0;
    TBool seekable = false;
    TBool live = true;
    iStreamId = iIdProvider->NextStreamId();
    iSupply->OutputStream(aUri.AbsoluteUri(), totalBytes, seekable, live, *this, iStreamId);
    iStarted = true;
}
