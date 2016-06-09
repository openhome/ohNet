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
#include <OpenHome/Av/Tidal/Tidal.h>
#include <OpenHome/Media/SupplyAggregator.h>
        
namespace OpenHome {
namespace Av {

class ProtocolTidal : public Media::ProtocolNetwork, private IReader
{
    static const TUint kTcpConnectTimeoutMs = 10 * 1000;
public:
    ProtocolTidal(Environment& aEnv, const Brx& aToken, Credentials& aCredentialsManager, Configuration::IConfigInitialiser& aConfigInitialiser);
    ~ProtocolTidal();
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
private:
    static TBool TryGetTrackId(const Brx& aQuery, Bwx& aTrackId);
    Media::ProtocolStreamResult DoStream();
    Media::ProtocolStreamResult DoSeek(TUint64 aOffset);
    TUint WriteRequest(TUint64 aOffset);
    Media::ProtocolStreamResult ProcessContent();
    TBool ContinueStreaming(Media::ProtocolStreamResult aResult);
    TBool IsCurrentStream(TUint aStreamId) const;
private:
    Tidal* iTidal;
    Media::SupplyAggregator* iSupply;
    Uri iUri;
    Bws<12> iTrackId;
    Bws<1024> iStreamUrl;
    Bws<64> iSessionId;
    WriterHttpRequest iWriterRequest;
    ReaderUntilS<2048> iReaderUntil;
    ReaderHttpResponse iReaderResponse;
    HttpHeaderContentType iHeaderContentType;
    HttpHeaderContentLength iHeaderContentLength;
    TUint64 iTotalBytes;
    TUint iStreamId;
    TBool iSeekable;
    TBool iSeek;
    TBool iStarted;
    TBool iStopped;
    TUint64 iSeekPos;
    TUint64 iOffset;
    Media::ContentProcessor* iContentProcessor;
    TUint iNextFlushId;
};

};  // namespace Av
};  // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;
using namespace OpenHome::Configuration;


Protocol* ProtocolFactory::NewTidal(Environment& aEnv, const Brx& aToken, Av::IMediaPlayer& aMediaPlayer)
{ // static
    return new ProtocolTidal(aEnv, aToken, aMediaPlayer.CredentialsManager(), aMediaPlayer.ConfigInitialiser());
}


// ProtocolTidal

ProtocolTidal::ProtocolTidal(Environment& aEnv, const Brx& aToken, Credentials& aCredentialsManager, IConfigInitialiser& aConfigInitialiser)
    : ProtocolNetwork(aEnv)
    , iSupply(nullptr)
    , iWriterRequest(iWriterBuf)
    , iReaderUntil(iReaderBuf)
    , iReaderResponse(aEnv, iReaderUntil)
    , iTotalBytes(0)
    , iSeekable(false)
{
    iReaderResponse.AddHeader(iHeaderContentType);
    iReaderResponse.AddHeader(iHeaderContentLength);

    iTidal = new Tidal(aEnv, aToken, aCredentialsManager, aConfigInitialiser);
    aCredentialsManager.Add(iTidal);
}

ProtocolTidal::~ProtocolTidal()
{
    delete iSupply;
}

void ProtocolTidal::Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream)
{
    iSupply = new SupplyAggregatorBytes(aMsgFactory, aDownstream);
}

void ProtocolTidal::Interrupt(TBool aInterrupt)
{
    iLock.Wait();
    if (iActive) {
        LOG(kMedia, "ProtocolTidal::Interrupt(%u)\n", aInterrupt);
        if (aInterrupt) {
            iStopped = true;
        }
        iTcpClient.Interrupt(aInterrupt);
        iTidal->Interrupt(aInterrupt);
    }
    iLock.Signal();
}

ProtocolStreamResult ProtocolTidal::Stream(const Brx& aUri)
{
    iTotalBytes = iSeekPos = iOffset = 0;
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iSeekable = iSeek = iStarted = iStopped = false;
    iContentProcessor = nullptr;
    iNextFlushId = MsgFlush::kIdInvalid;
    iTidal->Interrupt(false);
    iUri.Replace(aUri);

    if (iUri.Scheme() != Brn("tidal")) {
        return EProtocolErrorNotSupported;
    }
    LOG(kMedia, "ProtocolTidal::Stream(%.*s)\n", PBUF(aUri));
    if (!TryGetTrackId(iUri.Query(), iTrackId)) {
        return EProtocolStreamErrorUnrecoverable;
    }

    ProtocolStreamResult res = EProtocolStreamErrorUnrecoverable;
    if (iSessionId.Bytes() == 0 && !iTidal->TryLogin(iSessionId)) {
        return EProtocolStreamErrorUnrecoverable;
    }
    if (!iTidal->TryGetStreamUrl(iTrackId, iStreamUrl)) {
        // any error might be due to our session having expired
        // attempt logout, login, getStreamUrl to see if that fixes things
        (void)iTidal->TryLogout(iSessionId);
        if (!iTidal->TryLogin(iSessionId) || !iTidal->TryGetStreamUrl(iTrackId, iStreamUrl)) {
            return EProtocolStreamErrorUnrecoverable;
        }
    }
    iUri.Replace(iStreamUrl);

    res = DoStream();
    if (res == EProtocolStreamErrorUnrecoverable) {
        return res;
    }
    while (ContinueStreaming(res)) {
        if (iStopped) {
            res = EProtocolStreamStopped;
            break;
        }
        if (iSeek) {
            iLock.Wait();
            iSupply->OutputFlush(iNextFlushId);
            iNextFlushId = MsgFlush::kIdInvalid;
            iOffset = iSeekPos;
            iSeek = false;
            iLock.Signal();
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
        if (res == EProtocolStreamErrorRecoverable) {
            Thread::Sleep(50);
        }
    }

    iLock.Wait();
    if ((iStopped || iSeek) && iNextFlushId != MsgFlush::kIdInvalid) {
        iSupply->OutputFlush(iNextFlushId);
    }
    // clear iStreamId to prevent TrySeek or TryStop returning a valid flush id
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iLock.Signal();

    return res;
}

ProtocolGetResult ProtocolTidal::Get(IWriter& /*aWriter*/, const Brx& /*aUri*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return EProtocolGetErrorNotSupported;
}

void ProtocolTidal::Deactivated()
{
    if (iContentProcessor != nullptr) {
        iContentProcessor->Reset();
        iContentProcessor = nullptr;
    }
    iReaderUntil.ReadFlush();
    Close();
}

EStreamPlay ProtocolTidal::OkToPlay(TUint aStreamId)
{
    LOG(kMedia, "ProtocolTidal::OkToPlay(%u)\n", aStreamId);
    return iIdProvider->OkToPlay(aStreamId);
}

TUint ProtocolTidal::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    LOG(kMedia, "ProtocolTidal::TrySeek\n");

    iLock.Wait();
    const TBool streamIsValid = IsCurrentStream(aStreamId);
    if (streamIsValid) {
        iSeek = true;
        iSeekPos = aOffset;
        if (iNextFlushId == MsgFlush::kIdInvalid) {
            /* If a valid flushId is set then We've previously promised to send a Flush but haven't
               got round to it yet.  Re-use the same id for any other requests that come in before
               our main thread gets a chance to issue a Flush */
            iNextFlushId = iFlushIdProvider->NextFlushId();
        }
    }
    iLock.Signal();
    if (!streamIsValid) {
        return MsgFlush::kIdInvalid;
    }
    iTcpClient.Interrupt(true);
    return iNextFlushId;
}

TUint ProtocolTidal::TryStop(TUint aStreamId)
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
        iTcpClient.Interrupt(true);
    }
    iLock.Signal();
    return (stop? iNextFlushId : MsgFlush::kIdInvalid);
}

Brn ProtocolTidal::Read(TUint aBytes)
{
    Brn buf = iReaderUntil.Read(aBytes);
    iOffset += buf.Bytes();
    return buf;
}

void ProtocolTidal::ReadFlush()
{
    iReaderUntil.ReadFlush();
}

void ProtocolTidal::ReadInterrupt()
{
    iReaderUntil.ReadInterrupt();
}

TBool ProtocolTidal::TryGetTrackId(const Brx& aQuery, Bwx& aTrackId)
{ // static
    Parser parser(aQuery);
    (void)parser.Next('?');
    Brn buf = parser.Next('=');
    if (buf != Brn("version")) {
        LOG2(kPipeline, kError, "TryGetTrackId failed - no version\n");
        return false;
    }
    Brn verBuf = parser.Next('&');
    try {
        const TUint ver = Ascii::Uint(verBuf);
        if (ver != 1) {
            LOG2(kPipeline, kError, "TryGetTrackId failed - unsupported version - %d\n", ver);
            return false;
        }
    }
    catch (AsciiError&) {
        LOG2(kPipeline, kError, "TryGetTrackId failed - invalid version\n");
        return false;
    }
    buf.Set(parser.Next('='));
    if (buf != Brn("trackId")) {
        LOG2(kPipeline, kError, "TryGetTrackId failed - no track id tag\n");
        return false;
    }
    aTrackId.Replace(parser.Remaining());
    if (aTrackId.Bytes() == 0) {
        LOG2(kPipeline, kError, "TryGetTrackId failed - no track id value\n");
        return false;
    }
    return true;
}

TBool ProtocolTidal::ContinueStreaming(ProtocolStreamResult aResult)
{
    AutoMutex a(iLock);
    if (aResult == EProtocolStreamErrorRecoverable) {
        return true;
    }
    return false;
}

TBool ProtocolTidal::IsCurrentStream(TUint aStreamId) const
{
    if (iStreamId != aStreamId || aStreamId == IPipelineIdProvider::kStreamIdInvalid) {
        return false;
    }
    return true;
}

ProtocolStreamResult ProtocolTidal::DoStream()
{
    TUint code = WriteRequest(0);
    iSeekable = false;
    iTotalBytes = iHeaderContentLength.ContentLength();

    if (code != HttpStatus::kPartialContent.Code() && code != HttpStatus::kOk.Code()) {
        LOG2(kPipeline, kError, "ProtocolTidal::DoStream server returned error %u\n", code);
        return EProtocolStreamErrorUnrecoverable;
    }
    if (code == HttpStatus::kPartialContent.Code()) {
        if (iTotalBytes > 0) {
            iSeekable = true;
        }
        LOG(kMedia, "ProtocolTidal::DoStream 'Partial Content' seekable=%d (%lld bytes)\n", iSeekable, iTotalBytes);
    }
    else { // code == HttpStatus::kOk.Code()
        LOG(kMedia, "ProtocolTidal::DoStream 'OK' non-seekable (%lld bytes)\n", iTotalBytes);
    }

    return ProcessContent();
}

TUint ProtocolTidal::WriteRequest(TUint64 aOffset)
{
    iReaderUntil.ReadFlush();
    Close();
    const TUint port = (iUri.Port() == -1? 80 : (TUint)iUri.Port());
    if (!Connect(iUri, port, kTcpConnectTimeoutMs)) {
        LOG2(kPipeline, kError, "ProtocolTidal::WriteRequest Connection failure\n");
        return 0;
    }

    try {
        LOG(kMedia, "ProtocolTidal::WriteRequest send request\n");
        iWriterRequest.WriteMethod(Http::kMethodGet, iUri.PathAndQuery(), Http::eHttp11);
        const TUint port = (iUri.Port() == -1? 80 : (TUint)iUri.Port());
        Http::WriteHeaderHostAndPort(iWriterRequest, iUri.Host(), port);
        Http::WriteHeaderConnectionClose(iWriterRequest);
        Http::WriteHeaderRangeFirstOnly(iWriterRequest, aOffset);
        iWriterRequest.WriteFlush();
    }
    catch(WriterError&) {
        LOG2(kPipeline, kError, "ProtocolTidal::WriteRequest WriterError\n");
        return 0;
    }

    try {
        LOG(kMedia, "ProtocolTidal::WriteRequest read response\n");
        //iTcpClient.LogVerbose(true);
        iReaderResponse.Read();
        //iTcpClient.LogVerbose(false);
    }
    catch(HttpError&) {
        LOG2(kPipeline, kError, "ProtocolTidal::WriteRequest HttpError\n");
        return 0;
    }
    catch(ReaderError&) {
        LOG2(kPipeline, kError, "ProtocolTidal::WriteRequest ReaderError\n");
        return 0;
    }
    const TUint code = iReaderResponse.Status().Code();
    LOG(kMedia, "ProtocolTidal::WriteRequest response code %d\n", code);
    return code;
}

ProtocolStreamResult ProtocolTidal::ProcessContent()
{
    if (!iStarted) {
        iStreamId = iIdProvider->NextStreamId();
        iSupply->OutputStream(iUri.AbsoluteUri(), iTotalBytes, iOffset, iSeekable, false, *this, iStreamId);
        iStarted = true;
    }
    iContentProcessor = iProtocolManager->GetAudioProcessor();
    auto res = iContentProcessor->Stream(*this, iTotalBytes);
    if (res == EProtocolStreamErrorRecoverable && !(iSeek || iStopped)) {
        if (iTidal->TryReLogin(iSessionId, iSessionId) &&
            iTidal->TryGetStreamUrl(iTrackId, iStreamUrl)) {
            iUri.Replace(iStreamUrl);
        }
    }
    return res;
}

ProtocolStreamResult ProtocolTidal::DoSeek(TUint64 aOffset)
{
    Interrupt(false);
    const TUint code = WriteRequest(aOffset);
    if (code == 0) {
        return EProtocolStreamErrorRecoverable;
    }
    iTotalBytes = iHeaderContentLength.ContentLength();
    if (code != HttpStatus::kPartialContent.Code()) {
        return EProtocolStreamErrorUnrecoverable;
    }

    return ProcessContent();
}
