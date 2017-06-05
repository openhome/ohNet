#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Av/Credentials.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Types.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Av/CalmRadio/CalmRadio.h>
#include <OpenHome/Media/SupplyAggregator.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Protocol/Icy.h>

namespace OpenHome {
namespace Av {

class ProtocolCalmRadio : public Media::ProtocolNetwork
                        , private IReader
                        , private Media::IIcyObserver
{
    static const TUint kTcpConnectTimeoutMs = 10 * 1000;
    static const TUint kMaxUserAgentBytes = 64;
public:
    ProtocolCalmRadio(Environment& aEnv, const Brx& aUserAgent, Credentials& aCredentialsManager);
    ~ProtocolCalmRadio();
private: // from Media::Protocol
    void Initialise(Media::MsgFactory& aMsgFactory, Media::IPipelineElementDownstream& aDownstream) override;
    void Interrupt(TBool aInterrupt) override;
    Media::ProtocolStreamResult Stream(const Brx& aUri) override;
    Media::ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes) override;
    void Deactivated() override;
private: // from Media::IStreamHandler
    Media::EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
private: // from IReader
    Brn Read(TUint aBytes) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private: // from Media::IIcyObserver
    void NotifyIcyData(const Brx& aIcyData) override;
private:
    static TBool TryGetTrackId(const Brx& aQuery, Bwx& aTrackId);
    Media::ProtocolStreamResult DoStream();
    Media::ProtocolStreamResult DoSeek(TUint64 aOffset);
    TUint WriteRequestHandleForbidden(TUint64 aOffset);
    TUint WriteRequest(TUint64 aOffset);
    Media::ProtocolStreamResult ProcessContent();
    TBool ContinueStreaming(Media::ProtocolStreamResult aResult);
    TBool IsCurrentStream(TUint aStreamId) const;
private:
    CalmRadio* iCalm;
    Media::SupplyAggregator* iSupply;
    Uri iUri;
    Media::BwsTrackUri iUriBase;
    Media::BwsTrackUri iUriStream;
    WriterHttpRequest iWriterRequest;
    ReaderUntilS<2048> iReaderUntil;
    ReaderHttpResponse iReaderResponse;
    ReaderHttpChunked iDechunker;
    Media::ReaderIcy* iReaderIcy;
    HttpHeaderContentType iHeaderContentType;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderTransferEncoding iHeaderTransferEncoding;
    Media::HeaderIcyMetadata iHeaderIcyMetadata;
    Bws<kMaxUserAgentBytes> iUserAgent;
    Media::IcyObserverDidlLite* iIcyObserverDidlLite;
    TUint64 iTotalStreamBytes;
    TUint64 iTotalBytes;
    TUint iStreamId;
    TBool iSeekable;
    TBool iSeek;
    TBool iLive;
    TBool iStarted;
    TBool iStopped;
    TUint64 iSeekPos;
    TUint64 iOffset;
    Media::ContentProcessor* iContentProcessor;
    TUint iNextFlushId;
    Semaphore iSem;
};

};  // namespace Av
};  // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;
using namespace OpenHome::Configuration;


Protocol* ProtocolFactory::NewCalmRadio(Environment& aEnv, const Brx& aUserAgent, Av::IMediaPlayer& aMediaPlayer)
{ // static
    return new ProtocolCalmRadio(aEnv, aUserAgent, aMediaPlayer.CredentialsManager());
}


// ProtocolCalmRadio

ProtocolCalmRadio::ProtocolCalmRadio(Environment& aEnv, const Brx& aUserAgent, Credentials& aCredentialsManager)
    : ProtocolNetwork(aEnv)
    , iSupply(nullptr)
    , iWriterRequest(iWriterBuf)
    , iReaderUntil(iReaderBuf)
    , iReaderResponse(aEnv, iReaderUntil)
    , iDechunker(iReaderUntil)
    , iUserAgent(aUserAgent)
    , iTotalStreamBytes(0)
    , iTotalBytes(0)
    , iSem("PCR ", 0)
{
    iIcyObserverDidlLite = new Media::IcyObserverDidlLite(*this);
    iReaderIcy = new Media::ReaderIcy(iDechunker, *iIcyObserverDidlLite, iOffset);

    iReaderResponse.AddHeader(iHeaderContentType);
    iReaderResponse.AddHeader(iHeaderContentLength);
    iReaderResponse.AddHeader(iHeaderTransferEncoding);
    iReaderResponse.AddHeader(iHeaderIcyMetadata);

    iCalm = new CalmRadio(aEnv, aCredentialsManager);
    aCredentialsManager.Add(iCalm);
}

ProtocolCalmRadio::~ProtocolCalmRadio()
{
    delete iReaderIcy;
    delete iIcyObserverDidlLite;
    delete iSupply;
}

void ProtocolCalmRadio::Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream)
{
    iSupply = new SupplyAggregatorBytes(aMsgFactory, aDownstream);
}

void ProtocolCalmRadio::Interrupt(TBool aInterrupt)
{
    AutoMutex _(iLock);
    if (iActive) {
        LOG(kMedia, "ProtocolCalmRadio::Interrupt(%u)\n", aInterrupt);
        if (aInterrupt) {
            iStopped = true;
        }
        iTcpClient.Interrupt(aInterrupt);
        iCalm->Interrupt(aInterrupt);
    }
}

ProtocolStreamResult ProtocolCalmRadio::Stream(const Brx& aUri)
{
    iTotalBytes = iSeekPos = iOffset = 0;
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iSeekable = iSeek = iLive = iStarted = iStopped = false;
    iContentProcessor = nullptr;
    iNextFlushId = MsgFlush::kIdInvalid;
    iCalm->Interrupt(false);
    iUri.Replace(aUri);
    iReaderIcy->Reset();

    if (iUri.Scheme() != Brn("calmradio")) {
        return EProtocolErrorNotSupported;
    }
    const Brx& host = iUri.Host();
    if (host != Brn("stream")) {
        LOG2(kMedia, kError, "Unsupported host for Calm Radio - %.*s\n", PBUF(host));
        return EProtocolErrorNotSupported;
    }
    ProtocolStreamResult res;
    const Brx& query = iUri.Query();
    if (query.Bytes() == 0) {
        LOG2(kMedia, kError, "No query in Calm Radio uri - %.*s\n", PBUF(aUri));
        return EProtocolErrorNotSupported;
    }
    Brn uri = query.Split(1); // remove leading '?'
    Uri::Unescape(iUriBase, uri);
    LOG(kMedia, "ProtocolCalmRadio::Stream(%.*s)\n", PBUF(iUriBase));
    try {
        iUriStream.Replace(iUriBase);
        iCalm->GetStreamUrl(iUriStream);
        iUri.Replace(iUriStream);

        res = DoStream();
        if (res == EProtocolStreamErrorUnrecoverable) {
            if (iContentProcessor != nullptr) {
                iContentProcessor->Reset();
            }
            return res;
        }
        if (iLive) {
            // don't want to buffer content from a live stream
            // ...so need to wait on pipeline signalling it is ready to play
            LOG(kMedia, "ProtocolCalmRadio::Stream live stream waiting to be (re-)started\n");
            Close();
            iSem.Wait();
            LOG(kMedia, "ProtocolCalmRadio::Stream live stream restart\n");
            res = EProtocolStreamErrorRecoverable; // bodge to drop into the loop below
        }
        while (ContinueStreaming(res)) {
            if (iStopped) {
                res = EProtocolStreamStopped;
                break;
            }
            if (iSeek) {
                {
                    AutoMutex _(iLock);
                    iSupply->OutputFlush(iNextFlushId);
                    iNextFlushId = MsgFlush::kIdInvalid;
                    iOffset = iSeekPos;
                    iSeek = false;
                }
                res = DoSeek(iOffset);
            }
            else {
                // FIXME - if stream is non-seekable, set ErrorUnrecoverable as soon as Connect succeeds
                /* FIXME - reconnects should use extra http headers to check that content hasn't changed
                   since our first attempt at reading it.  Any change should result in ErrorUnrecoverable */
                const TUint code = WriteRequestHandleForbidden(iOffset);
                if (code != 0) {
                    iTotalBytes = iHeaderContentLength.ContentLength();
                    res = ProcessContent();
                }
            }
            if (res == EProtocolStreamErrorRecoverable) {
                Thread::Sleep(50);
            }
        }
    }
    catch (CalmRadioNoToken&) {
        res = EProtocolStreamErrorUnrecoverable;
    }

    iSupply->Flush();
    {
        AutoMutex _(iLock);
        if ((iStopped || iSeek) && iNextFlushId != MsgFlush::kIdInvalid) {
            iSupply->OutputFlush(iNextFlushId);
        }
        // clear iStreamId to prevent TrySeek or TryStop returning a valid flush id
        iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    }

    return res;
}

ProtocolGetResult ProtocolCalmRadio::Get(IWriter& /*aWriter*/, const Brx& /*aUri*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return EProtocolGetErrorNotSupported;
}

void ProtocolCalmRadio::Deactivated()
{
    if (iContentProcessor != nullptr) {
        iContentProcessor->Reset();
        iContentProcessor = nullptr;
    }
    iReaderIcy->ReadFlush();
    iReaderIcy->Reset();
    Close();
}

EStreamPlay ProtocolCalmRadio::OkToPlay(TUint aStreamId)
{
    LOG(kMedia, "ProtocolCalmRadio::OkToPlay(%u)\n", aStreamId);
    const EStreamPlay canPlay = iIdProvider->OkToPlay(aStreamId);
    if (canPlay != ePlayNo && iLive && iStreamId == aStreamId) {
        iSem.Signal();
    }
    LOG(kMedia, "< ProtocolCalmRadio::OkToPlay(%u) == %s\n", aStreamId, kStreamPlayNames[canPlay]);
    return canPlay;
}

TUint ProtocolCalmRadio::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    LOG(kMedia, "ProtocolCalmRadio::TrySeek\n");

    AutoMutex _(iLock);
    if (!IsCurrentStream(aStreamId)) {
        return MsgFlush::kIdInvalid;
    }

    if (!iLive && aOffset >= iTotalStreamBytes) {
        // Attempting to request beyond end of file.
        LOG(kMedia, "ProtocolCalmRadio::TrySeek attempting to seek beyond end of file. aStreamId: %u, aOffset: %llu, iTotalBytes: %llu\n",
                    aStreamId, aOffset, iTotalBytes);
        return MsgFlush::kIdInvalid;
    }

    iSeek = true;
    iSeekPos = aOffset;
    if (iNextFlushId == MsgFlush::kIdInvalid) {
        /* If a valid flushId is set then We've previously promised to send a Flush but haven't
        got round to it yet.  Re-use the same id for any other requests that come in before
        our main thread gets a chance to issue a Flush */
        iNextFlushId = iFlushIdProvider->NextFlushId();
    }

    iTcpClient.Interrupt(true);
    return iNextFlushId;
}

TUint ProtocolCalmRadio::TryStop(TUint aStreamId)
{
    AutoMutex _(iLock);
    if (!IsCurrentStream(aStreamId)) {
        return MsgFlush::kIdInvalid;
    }

    if (iNextFlushId == MsgFlush::kIdInvalid) {
        /* If a valid flushId is set then We've previously promised to send a Flush but haven't
        got round to it yet.  Re-use the same id for any other requests that come in before
        our main thread gets a chance to issue a Flush */
        iNextFlushId = iFlushIdProvider->NextFlushId();
    }
    iStopped = true;
    iTcpClient.Interrupt(true);
    if (iLive) {
        iSem.Signal();
    }
    return iNextFlushId;
}

Brn ProtocolCalmRadio::Read(TUint aBytes)
{
    Brn buf = iReaderIcy->Read(aBytes);
    return buf;
}

void ProtocolCalmRadio::ReadFlush()
{
    iReaderIcy->ReadFlush();
}

void ProtocolCalmRadio::ReadInterrupt()
{
    iReaderIcy->ReadInterrupt();
}

void ProtocolCalmRadio::NotifyIcyData(const Brx& aIcyData)
{
    iSupply->OutputMetadata(aIcyData);
}

TBool ProtocolCalmRadio::ContinueStreaming(ProtocolStreamResult aResult)
{
    AutoMutex _(iLock);
    if (aResult == EProtocolStreamErrorRecoverable) {
        return true;
    }
    return false;
}

TBool ProtocolCalmRadio::IsCurrentStream(TUint aStreamId) const
{
    if (iStreamId != aStreamId || aStreamId == IPipelineIdProvider::kStreamIdInvalid) {
        return false;
    }
    return true;
}

ProtocolStreamResult ProtocolCalmRadio::DoStream()
{
    // no support for redirects - its not clear whether we'd need to reapply the username/token query for these

    TUint code = WriteRequestHandleForbidden(0);
    iSeekable = false;
    iTotalStreamBytes = iHeaderContentLength.ContentLength();
    iTotalBytes = iTotalStreamBytes;
    iLive = (iTotalBytes == 0);

    if (code != HttpStatus::kPartialContent.Code() && code != HttpStatus::kOk.Code()) {
        LOG2(kPipeline, kError, "ProtocolCalmRadio::DoStream server returned error %u\n", code);
        return EProtocolStreamErrorUnrecoverable;
    }
    if (code == HttpStatus::kPartialContent.Code()) {
        if (iTotalBytes > 0) {
            iSeekable = true;
        }
        LOG(kMedia, "ProtocolCalmRadio::DoStream 'Partial Content' seekable=%d (%lld bytes)\n", iSeekable, iTotalBytes);
    }
    else { // code == HttpStatus::kOk.Code()
        LOG(kMedia, "ProtocolCalmRadio::DoStream 'OK' non-seekable (%lld bytes)\n", iTotalBytes);
    }
    if (iHeaderIcyMetadata.Received()) {
        iReaderIcy->SetEnabled(iHeaderIcyMetadata.Bytes());
    }
    iDechunker.SetChunked(iHeaderTransferEncoding.IsChunked());

    return ProcessContent();
}

TUint ProtocolCalmRadio::WriteRequestHandleForbidden(TUint64 aOffset)
{
    TUint code = WriteRequest(aOffset);
    if (code == 403) {
        iCalm->ForceLogin();
        iUriStream.Replace(iUriBase);
        iCalm->GetStreamUrl(iUriStream);
        iUri.Replace(iUriStream);
        code = WriteRequest(aOffset);
    }
    return code;
}

TUint ProtocolCalmRadio::WriteRequest(TUint64 aOffset)
{
    iReaderIcy->ReadFlush();
    Close();
    const TUint port = (iUri.Port() == -1? 80 : (TUint)iUri.Port());
    if (!Connect(iUri, port, kTcpConnectTimeoutMs)) {
        LOG2(kPipeline, kError, "ProtocolCalmRadio::WriteRequest Connection failure\n");
        return 0;
    }

    try {
        LOG(kMedia, "ProtocolCalmRadio::WriteRequest send request\n");
        iWriterRequest.WriteMethod(Http::kMethodGet, iUri.PathAndQuery(), Http::eHttp11);
        const TUint port = (iUri.Port() == -1? 80 : (TUint)iUri.Port());
        Http::WriteHeaderHostAndPort(iWriterRequest, iUri.Host(), port);
        if (iUserAgent.Bytes() > 0) {
            iWriterRequest.WriteHeader(Http::kHeaderUserAgent, iUserAgent);
        }
        Http::WriteHeaderConnectionClose(iWriterRequest);
        HeaderIcyMetadata::Write(iWriterRequest);
        Http::WriteHeaderRangeFirstOnly(iWriterRequest, aOffset);
        iWriterRequest.WriteFlush();
    }
    catch(WriterError&) {
        LOG2(kPipeline, kError, "ProtocolCalmRadio::WriteRequest WriterError\n");
        return 0;
    }

    try {
        LOG(kMedia, "ProtocolCalmRadio::WriteRequest read response\n");
        iTcpClient.LogVerbose(true);
        iReaderResponse.Read();
        iTcpClient.LogVerbose(false);
    }
    catch(HttpError&) {
        LOG2(kPipeline, kError, "ProtocolCalmRadio::WriteRequest HttpError\n");
        return 0;
    }
    catch(ReaderError&) {
        LOG2(kPipeline, kError, "ProtocolCalmRadio::WriteRequest ReaderError\n");
        return 0;
    }
    const TUint code = iReaderResponse.Status().Code();
    LOG(kMedia, "ProtocolCalmRadio::WriteRequest response code %d\n", code);
    return code;
}

ProtocolStreamResult ProtocolCalmRadio::ProcessContent()
{
    if (!iStarted) {
        iStreamId = iIdProvider->NextStreamId();
        iSupply->OutputStream(iUri.AbsoluteUri(), iTotalBytes, iOffset, iSeekable, false, Multiroom::Allowed, *this, iStreamId);
        iStarted = true;
    }
    iContentProcessor = iProtocolManager->GetAudioProcessor();
    return iContentProcessor->Stream(*this, iTotalBytes);
}

ProtocolStreamResult ProtocolCalmRadio::DoSeek(TUint64 aOffset)
{
    Interrupt(false);
    const TUint code = WriteRequestHandleForbidden(aOffset);
    if (code == 0) {
        return EProtocolStreamErrorRecoverable;
    }
    iTotalBytes = iHeaderContentLength.ContentLength();
    if (code != HttpStatus::kPartialContent.Code()) {
        return EProtocolStreamErrorUnrecoverable;
    }

    return ProcessContent();
}
