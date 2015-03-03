#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/ProtocolHls.h>
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

class SemaphoreGeneric : public ISemaphore
{
public:
    SemaphoreGeneric(const TChar* aName, TUint aCount);
public: // from ISemaphore
    void Wait() override;
    TBool Clear() override;
    void Signal() override;
private:
    Semaphore iSem;
};

class ProtocolHls : public Protocol
{
public:
    ProtocolHls(Environment& aEnv, const Brx& aUserAgent);
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
    TBool IsCurrentStream(TUint aStreamId) const;
private:
    Supply* iSupply;
    TimerGeneric iTimer;
    HttpReader iHttpReaderM3u;
    SemaphoreGeneric iSemReaderM3u;
    HlsM3uReader iM3uReader;
    HttpReader iHttpSegStreamer;
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


Protocol* ProtocolFactory::NewHls(Environment& aEnv, const Brx& aUserAgent)
{ // static
    return new ProtocolHls(aEnv, aUserAgent);
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
    //ASSERT(!iPending);
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


// SemaphoreGeneric

SemaphoreGeneric::SemaphoreGeneric(const TChar* aName, TUint aCount)
    : iSem(aName, aCount)
{
}

void SemaphoreGeneric::Wait()
{
    iSem.Wait();
}

TBool SemaphoreGeneric::Clear()
{
    return iSem.Clear();
}

void SemaphoreGeneric::Signal()
{
    return iSem.Signal();
}



// HlsM3uReader

HlsM3uReader::HlsM3uReader(IHttpSocket& aSocket, IReaderBuffered& aReader, ITimer& aTimer, ISemaphore& aSemaphore)
    : iTimer(aTimer)
    , iSocket(aSocket)
    , iReader(aReader)
    , iTotalBytes(0)
    , iVersion(2)
    , iLastSegment(0)
    , iTargetDuration(0)
    , iEndlist(false)
    , iLock("HMRL")
    , iSem(aSemaphore)
    , iInterrupted(true)
{
}

void HlsM3uReader::SetUri(const Uri& aUri)
{
    {
        AutoMutex a(iLock);
        // FIXME - re-enable this assertion.
        //ASSERT(iInterrupted);   // Interrupt() should be called before re-calling SetUri().
                                // iInterrupted is set to true at construction, so will be true on first call to SetUri().
        iUri.Replace(aUri.AbsoluteUri());
        iLastSegment = 0;
        iTargetDuration = 0;
        iEndlist = false;
        iNextLine.Set(Brx::Empty());
        iSem.Clear();
        iSem.Signal();
        iInterrupted = false;
    }
}

TUint HlsM3uReader::Version() const
{
    return iVersion;
}

void HlsM3uReader::Close()
{
    // It is responsibility of client of this class to call Interrupt() prior
    // to this (if class is active).
    iSocket.Close();
}

TUint HlsM3uReader::NextSegmentUri(Uri& aUri)
{
    TUint duration = 0;
    Brn segmentUri = Brx::Empty();
    try {
        TBool expectUri = false;
        while (segmentUri == Brx::Empty()) {
            Brn uri;
            if ((iLastSegment == 0 && iTargetDuration == 0) || iOffset >= iTotalBytes) {
                if (!iEndlist) {
                    if (!ReloadVariantPlaylist()) {
                        THROW(HlsVariantPlaylistError);
                    }
                }
                else {
                    THROW(HlsEndOfStream);
                }
            }

            if (iNextLine == Brx::Empty()) {
                ReadNextLine();
            }
            if (expectUri) {
                segmentUri = Ascii::Trim(iNextLine);
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
                    Brn durationBuf = p.Next(',');
                    Parser durationParser(durationBuf);
                    Brn durationWhole = durationParser.Next('.');
                    duration = Ascii::Uint(durationWhole) * kMillisecondsPerSecond;
                    if (!durationParser.Finished()) {
                        // Looks like duration is a float.
                        // Duration is only guaranteed to be int in version 2 and below
                        Brn durationDecimalBuf = durationParser.Next();
                        if (!durationParser.Finished() && durationDecimalBuf.Bytes()>3) {
                            // Error in M3U8 format.
                            THROW(HlsVariantPlaylistError);
                        }
                        TUint durationDecimal = Ascii::Uint(durationDecimalBuf);
                        duration += durationDecimal;
                    }
                    Log::Print("duration: %u\n", duration);
                    expectUri = true;
                }
                else if (tag == Brn("#EXT-X-ENDLIST")) {
                    iEndlist = true;
                }
            }
            iNextLine = Brx::Empty();
        }

        try {
            SetSegmentUri(aUri, segmentUri);
        }
        catch (UriError&) {
            LOG(kMedia, "HlsM3uReader::NextSegmentUri UriError\n");
            THROW(HlsVariantPlaylistError);
        }
    }
    catch (AsciiError&) {
        LOG(kMedia, "HlsM3uReader::NextSegmentUri AsciiError\n");
        THROW(HlsVariantPlaylistError);
    }
    catch (HttpError&) {
        LOG(kMedia, "HlsM3uReader::NextSegmentUri HttpError\n");
        THROW(HlsVariantPlaylistError);
    }
    catch (ReaderError&) {
        LOG(kMedia, "HlsM3uReader::NextSegmentUri ReaderError\n");
        THROW(HlsVariantPlaylistError);
    }

    return duration;
}

void HlsM3uReader::TimerFired()
{
    iSem.Signal();
}

void HlsM3uReader::Interrupt()
{
    // Must NOT close socket here - undefined behaviour will result.
    AutoMutex a(iLock);
    if (!iInterrupted) {
        iInterrupted = true;
        iTimer.Cancel();
        iReader.ReadInterrupt();
        iSem.Signal();
    }
}

void HlsM3uReader::ReadNextLine()
{
    // May throw ReaderError.
    iNextLine = iReader.ReadUntil('\n');
    iOffset += iNextLine.Bytes()+1;  // Separator has been trimmed.
}

TBool HlsM3uReader::ReloadVariantPlaylist()
{
    // Timer should be started BEFORE refreshing playlist.
    // However, not very useful if we don't yet have target duration, so just
    // start timer after processing part of playlist.

    iSem.Wait();
    iSem.Clear();   // Clear in case iSem has been signalled multiple times. E.g., blocking while filling buffers during last playlist reload.

    {
        AutoMutex a(iLock);
        if (iInterrupted) {
            return false;
        }
    }

    iSocket.Close();
    TBool success = iSocket.Connect(iUri);
    if (success) {
        // FIXME - must handle case of iTotalBytes being 0 - is the case for some M3Us. If so, will just have to read until ReaderError is thrown.
        iTotalBytes = iSocket.ContentLength();
        iOffset = 0;
    }
    else {
        return false;
    }

    try {
        if (!PreprocessM3u()) {
            return false;
        }
    }
    catch (AsciiError&) {
        LOG(kMedia, "HlsM3uReader::NextSegmentUri AsciiError\n");
        return false;
    }
    catch (HttpError&) {
        LOG(kMedia, "HlsM3uReader::NextSegmentUri HttpError\n");
        return false;
    }
    catch (ReaderError&) {
        LOG(kMedia, "HlsM3uReader::NextSegmentUri ReaderError\n");
        return false;
    }

    if (iOffset >= iTotalBytes) {
        LOG(kMedia, "HlsM3uReader::ReloadVariantPlaylist exhausted file\n");
        return false;
    }

    if (iTargetDuration == 0) { // #EXT-X-TARGETDURATION is a required tag.
        LOG(kMedia, "HlsM3uReader::ReloadVariantPlaylist malformed file\n");
        return false;
    }

    iTimer.Start(iTargetDuration*kMillisecondsPerSecond, *this);
    return true;
}

TBool HlsM3uReader::PreprocessM3u()
{
    TUint64 skipSegments = 0;
    TBool mediaSeqFound = false;
    try {
        while (iOffset < iTotalBytes) {
            ReadNextLine();
            Parser p(iNextLine);
            Brn tag = p.Next(':');

            if (tag == Brn("#EXT-X-VERSION")) {
                iVersion = Ascii::Uint(p.Next());
                if (iVersion > kMaxM3uVersion) {
                    LOG(kMedia, "Unsupported M3U version. Max supported version: %u, version encountered: %u\n", kMaxM3uVersion, iVersion);
                }
                Log::Print("iVersion: %u\n", iVersion);
            }
            if (tag == Brn("#EXT-X-MEDIA-SEQUENCE")) {
                mediaSeqFound = true;
                // If this isn't found, it must be assumed that first segment in playlist is 0.
                TUint64 mediaSeq = Ascii::Uint64(p.Next());
                if (iLastSegment == 0) {
                    iLastSegment = mediaSeq;
                    skipSegments = 0;
                }
                else if (mediaSeq <= iLastSegment) {
                    skipSegments = (iLastSegment-mediaSeq);
                }
                Log::Print("mediaSeq: %llu\n", mediaSeq);
            }
            else if (tag == Brn("#EXT-X-TARGETDURATION")) {
                iTargetDuration = Ascii::Uint(p.Next());
                Log::Print("iTargetDuration: %u\n", iTargetDuration);
            }
            else if (tag == Brn("#EXT-X-ENDLIST")) {
                iEndlist = true;
                Log::Print("#EXT-X-ENDLIST\n");
            }
            else if (tag == Brn("#EXTINF")) {
                if (!mediaSeqFound) {
                    // EXT-X-MEDIA-SEQUENCE MUST appear before EXTINF, so must
                    // have seen it by now if present.
                    skipSegments = iLastSegment;
                    mediaSeqFound = true;   // Don't want to enter this block again.
                }

                if (skipSegments > 0) {
                    skipSegments--;
                }
                else {
                    // Found start/continuation of audio.
                    // iNextLine will remain populated with this "#EXTINF" line
                    // for starting parsing of outstanding segments elsewhere.
                    return true;
                }
            }
        }
    }
    catch (AsciiError&) {
        LOG(kMedia, "HlsM3uReader::PreprocessM3u AsciiError\n");
        return false;
    }
    catch (HttpError&) {
        LOG(kMedia, "HlsM3uReader::PreprocessM3u HttpError\n");
        return false;
    }
    catch (ReaderError&) {
        LOG(kMedia, "HlsM3uReader::PreprocessM3u ReaderError\n");
        return false;
    }
    return false;
}

void HlsM3uReader::SetSegmentUri(Uri& aUri, const Brx& aSegmentUri)
{
    // Segment URI MAY be relative.
    // If it is relative, it is relative to URI of playlist that contains it.
    static const Brn kSchemeHttp("http");

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

SegmentStreamer::SegmentStreamer(IHttpSocket& aSocket, IReaderBuffered& aReader)
    : iSocket(aSocket)
    , iReader(aReader)
    , iSegmentUriProvider(NULL)
    , iTotalBytes(0)
    , iOffset(0)
    , iInterrupted(true)
    , iLock("SEGL")
{
}

void SegmentStreamer::Stream(ISegmentUriProvider& aSegmentUriProvider)
{
    {
        AutoMutex a(iLock);
        ASSERT(iInterrupted);
        iInterrupted = false;
        iSegmentUriProvider = &aSegmentUriProvider;
        iTotalBytes = 0;
        iOffset = 0;
    }
}

Brn SegmentStreamer::Read(TUint aBytes)
{
    EnsureSegmentIsReady();
    Brn buf = iReader.Read(aBytes);
    iOffset += buf.Bytes();
    return buf;
}

Brn SegmentStreamer::ReadUntil(TByte aSeparator)
{
    EnsureSegmentIsReady();
    Brn buf = iReader.ReadUntil(aSeparator);
    iOffset += buf.Bytes()+1;   // Separator has been trimmed.
    return buf;
}

void SegmentStreamer::ReadFlush()
{
    iReader.ReadFlush();
}

void SegmentStreamer::ReadInterrupt()
{
    AutoMutex a(iLock);
    iInterrupted = true;
    iReader.ReadInterrupt();
}

Brn SegmentStreamer::ReadRemaining()
{
    Brn buf = iReader.ReadRemaining();
    if (buf.Bytes() == 0) {
        iOffset = iTotalBytes;
    }
    else {
        iOffset += buf.Bytes();
    }
    return buf;
}

void SegmentStreamer::Close()
{
    LOG(kMedia, "SegmentStreamer::Close\n");
    iSocket.Close();
}

void SegmentStreamer::GetNextSegment()
{
    Uri segment;
    (void)iSegmentUriProvider->NextSegmentUri(segment); // pass up HlsVariantPlaylistError, HlsEndOfStream

    iUri.Replace(segment.AbsoluteUri());

    iSocket.Close();
    TBool success = iSocket.Connect(iUri);
    {
        AutoMutex a(iLock);
        if (iInterrupted || !success) {
            THROW(HlsSegmentError);
        }
    }
    if (success) {
        // FIXME - must handle case of iTotalBytes being 0 - is the case for some M3Us. If so, will just have to read until ReaderError is thrown.
        iTotalBytes = iSocket.ContentLength();
        iOffset = 0;
    }
}

void SegmentStreamer::EnsureSegmentIsReady()
{
    // FIXME - what if iTotalBytes == 0?
    if (iOffset == iTotalBytes) {
        GetNextSegment();
    }
}


// ProtocolHls

ProtocolHls::ProtocolHls(Environment& aEnv, const Brx& aUserAgent)
    : Protocol(aEnv)
    , iSupply(NULL)
    , iTimer(iEnv, "PHLS")
    , iHttpReaderM3u(iEnv, aUserAgent)
    , iSemReaderM3u("HMRS", 0)
    , iM3uReader(iHttpReaderM3u, iHttpReaderM3u, iTimer, iSemReaderM3u)
    , iHttpSegStreamer(iEnv, aUserAgent)
    , iSegmentStreamer(iHttpSegStreamer, iHttpSegStreamer)
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
        iSegmentStreamer.ReadInterrupt();
        iM3uReader.Interrupt();
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
    Uri uriHls(aUri);
    LOG(kMedia, "ProtocolHls::Stream ");
    LOG(kMedia, uriHls.AbsoluteUri());
    LOG(kMedia, "\n");

    if (uriHls.Scheme() != Brn("hls")) {
        LOG(kMedia, "ProtocolHls::Stream scheme not recognised\n");
        return EProtocolErrorNotSupported;
    }

    if (!iStarted) {
        StartStream(uriHls);
    }

    // Don't want to buffer content from a live stream
    // ...so need to wait on pipeline signalling it is ready to play
    LOG(kMedia, "ProtocolHls::Stream live stream waiting to be (re-)started\n");
    iSegmentStreamer.Close();
    iM3uReader.Close();
    iSem.Wait();            // FIXME - is Reinitialise() calling iSem.Clear() and messing with this?
    LOG(kMedia, "ProtocolHls::Stream live stream restart\n");

    // Convert hls:// scheme to http:// scheme
    const Brx& uriHlsBuf = uriHls.AbsoluteUri();
    Parser p(uriHlsBuf);
    p.Next(':');    // skip "hls" scheme
    Bws<Uri::kMaxUriBytes> uriHttpBuf("http:");
    uriHttpBuf.Append(p.NextToEnd());
    Uri uriHttp(uriHttpBuf);    // may throw UriError

    iM3uReader.SetUri(uriHttp); // rename to Reinitialise()
    iSegmentStreamer.Stream(iM3uReader);

    if (iContentProcessor == NULL) {
        iContentProcessor = iProtocolManager->GetAudioProcessor();  // returns stream state
    }
    ProtocolStreamResult res = EProtocolStreamErrorRecoverable;
    while (res == EProtocolStreamErrorRecoverable) {
        if (iStopped) {
            res = EProtocolStreamStopped;
            break;
        }
        //res = iContentProcessor->Stream(iSegmentStreamer, 0);



        try {
            res = iContentProcessor->Stream(iSegmentStreamer, 0);
        }
        catch (HlsEndOfStream&) {
            res = EProtocolStreamSuccess;
            //break;
        }
        catch (HlsVariantPlaylistError&) {
            res = EProtocolStreamErrorUnrecoverable;
            //break;
        }
        catch (HlsSegmentError&) {
            res = EProtocolStreamErrorUnrecoverable;
            //break;
        }
    }

    iSegmentStreamer.Close();
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
    iSegmentStreamer.Close();
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
    const TBool stop = IsCurrentStream(aStreamId);
    if (stop) {
        if (iNextFlushId == MsgFlush::kIdInvalid) {
            /* If a valid flushId is set then We've previously promised to send a Flush but haven't
            got round to it yet.  Re-use the same id for any other requests that come in before
            our main thread gets a chance to issue a Flush */
            iNextFlushId = iFlushIdProvider->NextFlushId();
        }
        iStopped = true;
        iM3uReader.Interrupt();
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

TBool ProtocolHls::IsCurrentStream(TUint aStreamId) const
{
    if (iStreamId != aStreamId || aStreamId == IPipelineIdProvider::kStreamIdInvalid) {
        return false;
    }
    return true;
}
