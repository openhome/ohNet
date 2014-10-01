#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Types.h>
#include <OpenHome/SocketSsl.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Media/Debug.h>

#include <algorithm>

namespace OpenHome {
namespace Media {

class ProtocolHttps : public Protocol, private IProtocolReader
{
    static const TUint kReadBufferBytes = 8 * 1024;
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeoutMs = 5000; // FIXME - should read this + ProtocolNetwork's equivalent from a single client-changable location
    static const TUint kDefaultPort = 443;
public:
    ProtocolHttps(Environment& aEnv);
private: // from Protocol
    void Interrupt(TBool aInterrupt);
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
    TBool Connect();
    ProtocolStreamResult DoStream();
    ProtocolGetResult DoGet(IWriter& aWriter, TUint64 aOffset, TUint aBytes);
private:
    Mutex iLock;
    SocketSsl iSocket;
    Srs<kReadBufferBytes> iReaderBuf;
    Sws<kWriteBufferBytes> iWriterBuf;
    WriterHttpRequest iWriterRequest;
    ReaderHttpResponse iReaderResponse;
    ReaderHttpChunked iDechunker;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderTransferEncoding iHeaderTransferEncoding;
    OpenHome::Uri iUri;
    TUint iStreamId;
    TBool iStopped;
    TUint iNextFlushId;
};

};  // namespace Media
};  // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;


Protocol* ProtocolFactory::NewHttps(Environment& aEnv)
{ // static
    return new ProtocolHttps(aEnv);
}


// ProtocolHttps

ProtocolHttps::ProtocolHttps(Environment& aEnv)
    : Protocol(aEnv)
    , iLock("PHTS")
    , iSocket(aEnv, kReadBufferBytes)
    , iReaderBuf(iSocket)
    , iWriterBuf(iSocket)
    , iWriterRequest(iWriterBuf)
    , iReaderResponse(aEnv, iReaderBuf)
    , iDechunker(iReaderBuf)
{
    iReaderResponse.AddHeader(iHeaderContentLength);
    iReaderResponse.AddHeader(iHeaderTransferEncoding);
}

void ProtocolHttps::Interrupt(TBool aInterrupt)
{
    iLock.Wait();
    if (iActive) {
        LOG(kMedia, "ProtocolHttps::Interrupt(%u)\n", aInterrupt);
        if (aInterrupt) {
            iStopped = true;
        }
        iSocket.Interrupt(aInterrupt);
    }
    iLock.Signal();
}

ProtocolStreamResult ProtocolHttps::Stream(const Brx& aUri)
{
    Reinitialise(aUri);
    if (iUri.Scheme() != Brn("https")) {
        LOG(kMedia, "ProtocolHttps::Stream scheme not recognised\n");
        return EProtocolErrorNotSupported;
    }

    if (!Connect()) {
        LOG2(kMedia, kError, "ProtocolHttps::Stream - connect failed - ");
        LOG2(kMedia, kError, iUri.AbsoluteUri());
        LOG2(kMedia, kError, "\n");
        return EProtocolStreamErrorUnrecoverable;
    }
    ProtocolStreamResult res = DoStream();
    iLock.Wait();
    if (iStopped) {
        iSupply->OutputFlush(iNextFlushId);
    }
    iSocket.Close();
    iLock.Signal();

    return res;
}

ProtocolGetResult ProtocolHttps::Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes)
{
    Reinitialise(aUri);
    if (iUri.Scheme() != Brn("https")) {
        LOG(kMedia, "ProtocolHttps::Get scheme not recognised\n");
        return EProtocolGetErrorNotSupported;
    }
    if (!Connect()) {
        LOG2(kMedia, kError, "ProtocolHttps::Get - connect failed - ");
        LOG2(kMedia, kError, iUri.AbsoluteUri());
        LOG2(kMedia, kError, "\n");
        return EProtocolGetErrorUnrecoverable;
    }

    ProtocolGetResult res = DoGet(aWriter, aOffset, aBytes);
    iSocket.Close();
    return res;
}

EStreamPlay ProtocolHttps::OkToPlay(TUint aTrackId, TUint aStreamId)
{
    return iIdProvider->OkToPlay(aTrackId, aStreamId);
}

TUint ProtocolHttps::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    return MsgFlush::kIdInvalid;
}

TUint ProtocolHttps::TryStop(TUint aTrackId, TUint aStreamId)
{
    iLock.Wait();
    const TBool stop = (iProtocolManager->IsCurrentTrack(aTrackId) && iStreamId == aStreamId);
    if (stop) {
        if (iNextFlushId == MsgFlush::kIdInvalid) {
            /* If a valid flushId is set then We've previously promised to send a Flush but haven't
               got round to it yet.  Re-use the same id for any other requests that come in before
               our main thread gets a chance to issue a Flush */
            iNextFlushId = iFlushIdProvider->NextFlushId();
        }
        iStopped = true;
        iSocket.Interrupt(true);
    }
    iLock.Signal();
    return (stop? iNextFlushId : MsgFlush::kIdInvalid);
}

TBool ProtocolHttps::TryGet(IWriter& aWriter, TUint aTrackId, TUint aStreamId, TUint64 aOffset, TUint aBytes)
{
    AutoMutex a(iLock);
    const TBool isCurrent = (iProtocolManager->IsCurrentTrack(aTrackId) && iStreamId == aStreamId);
    TBool success = false;
    if (isCurrent) {
        success = iProtocolManager->Get(aWriter, iUri.AbsoluteUri(), aOffset, aBytes);
    }
    return success;
}

Brn ProtocolHttps::Read(TUint aBytes)
{
    return iDechunker.Read(aBytes);
}

Brn ProtocolHttps::ReadUntil(TByte aSeparator)
{
    return iDechunker.ReadUntil(aSeparator);
}

void ProtocolHttps::ReadFlush()
{
    iDechunker.ReadFlush();
}

void ProtocolHttps::ReadInterrupt()
{
    iDechunker.ReadInterrupt();
}

Brn ProtocolHttps::ReadRemaining()
{
    return iDechunker.ReadRemaining();
}

void ProtocolHttps::Reinitialise(const Brx& aUri)
{
    iSocket.Interrupt(false);
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iStopped = false;
    iNextFlushId = MsgFlush::kIdInvalid;
    iUri.Replace(aUri);
}

TBool ProtocolHttps::Connect()
{
    Endpoint ep;
    try {
        ep.SetAddress(iUri.Host());
        TInt port = iUri.Port();
        if (port == -1) {
            port = (TInt)kDefaultPort;
        }
        ep.SetPort(port);
        iSocket.Connect(ep, kConnectTimeoutMs);
    }
    catch (NetworkError&) {
        return false;
    }
    return true;
}

ProtocolStreamResult ProtocolHttps::DoStream()
{
    try {
        LOG(kMedia, "ProtocolHttps::Stream send request\n");
        iWriterRequest.WriteMethod(Http::kMethodGet, iUri.PathAndQuery(), Http::eHttp11);
        const TUint port = (iUri.Port() == -1? kDefaultPort : (TUint)iUri.Port());
        Http::WriteHeaderHostAndPort(iWriterRequest, iUri.Host(), port);
        Http::WriteHeaderConnectionClose(iWriterRequest);
        iWriterRequest.WriteFlush();
    }
    catch(WriterError&) {
        LOG2(kMedia, kError, "ProtocolHttps::Stream writer error\n");
        return EProtocolStreamErrorUnrecoverable;
    }

    ContentProcessor* cp = NULL;
    ProtocolStreamResult res = EProtocolStreamErrorUnrecoverable;
    try {
        LOG(kMedia, "ProtocolHttps read response\n");
        iReaderResponse.Read();
        const TUint code = iReaderResponse.Status().Code();
        if (code != HttpStatus::kOk.Code()) {
            LOG(kMedia, "ProtocolHttps GET failed (%d)\n", code);
            return EProtocolStreamErrorUnrecoverable;
        }

        iStreamId = iIdProvider->NextStreamId();
        const TUint64 totalBytes = iHeaderContentLength.ContentLength();
        iSupply->OutputStream(iUri.AbsoluteUri(), totalBytes, false/*seekable*/, false/*live*/, *this, iStreamId);
        iDechunker.SetChunked(iHeaderTransferEncoding.IsChunked());
        cp = iProtocolManager->GetAudioProcessor();
        res = cp->Stream(*this, totalBytes);
    }
    catch (ReaderError&) {
    }
    if (cp != NULL) {
        cp->Reset();
    }
    return res;
}

ProtocolGetResult ProtocolHttps::DoGet(IWriter& aWriter, TUint64 aOffset, TUint aBytes)
{
    try {
        LOG(kMedia, "ProtocolHttps::DoGet send request\n");
        iWriterRequest.WriteMethod(Http::kMethodGet, iUri.PathAndQuery(), Http::eHttp11);
        const TUint port = (iUri.Port() == -1? kDefaultPort : (TUint)iUri.Port());
        Http::WriteHeaderHostAndPort(iWriterRequest, iUri.Host(), port);
        Http::WriteHeaderConnectionClose(iWriterRequest);
        TUint64 last = aOffset+aBytes-1;
        Http::WriteHeaderRange(iWriterRequest, aOffset, last);
        iWriterRequest.WriteFlush();
    }
    catch(WriterError&) {
        LOG2(kMedia, kError, "ProtocolHttps::DoGet writer error\n");
        return EProtocolGetErrorUnrecoverable;
    }

    try {
        LOG(kMedia, "ProtocolHttps read response\n");
        iReaderResponse.Read();
        const TUint code = iReaderResponse.Status().Code();
        if (code != HttpStatus::kPartialContent.Code() && code != HttpStatus::kOk.Code()) {
            LOG(kMedia, "ProtocolHttps GET failed (%d)\n", code);
            return EProtocolGetErrorUnrecoverable;
        }

        TUint64 totalBytes = iHeaderContentLength.ContentLength();
        totalBytes = std::min(totalBytes, (TUint64)aBytes);
        iDechunker.SetChunked(iHeaderTransferEncoding.IsChunked());
        if (totalBytes >= aBytes) {
            TUint64 count = 0;
            TUint bytes = 1024; // FIXME - choose better value or justify this
            while (count < totalBytes) {
                const TUint remaining = static_cast<TUint>(totalBytes-count);
                if (remaining < bytes) {
                    bytes = remaining;
                }
                Brn buf = Read(bytes);
                aWriter.Write(buf);
                count += buf.Bytes();
            }
            return EProtocolGetSuccess;
        }

    }
    catch (ReaderError&) {
    }
    catch (WriterError&) {
    }

    return EProtocolGetErrorUnrecoverable;
}
