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
#include <OpenHome/Media/Supply.h>

#include <algorithm>

namespace OpenHome {
namespace Media {

class ProtocolHttps : public Protocol, private IReader
{
    static const TUint kReadBufferBytes = 8 * 1024;
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeoutMs = 5000; // FIXME - should read this + ProtocolNetwork's equivalent from a single client-changable location
    static const TUint kDefaultPort = 443;
public:
    ProtocolHttps(Environment& aEnv);
    ~ProtocolHttps();
private: // from Protocol
    void Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream) override;
    void Interrupt(TBool aInterrupt) override;
    ProtocolStreamResult Stream(const Brx& aUri) override;
    ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes) override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
private: // from IReader
    Brn Read(TUint aBytes) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    void Reinitialise(const Brx& aUri);
    TBool Connect();
    ProtocolStreamResult DoStream();
    ProtocolGetResult DoGet(IWriter& aWriter, TUint64 aOffset, TUint aBytes);
    TBool IsCurrentStream(TUint aStreamId) const;
private:
    Mutex iLock;
    Supply* iSupply;
    SocketSsl iSocket;
    Srs<1024> iReaderBuf;
    ReaderUntilS<kReadBufferBytes> iReaderUntil;
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
    , iSupply(nullptr)
    , iSocket(aEnv, kReadBufferBytes)
    , iReaderBuf(iSocket)
    , iReaderUntil(iReaderBuf)
    , iWriterBuf(iSocket)
    , iWriterRequest(iWriterBuf)
    , iReaderResponse(aEnv, iReaderUntil)
    , iDechunker(iReaderUntil)
{
    iReaderResponse.AddHeader(iHeaderContentLength);
    iReaderResponse.AddHeader(iHeaderTransferEncoding);
}

ProtocolHttps::~ProtocolHttps()
{
    delete iSupply;
}

void ProtocolHttps::Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream)
{
    iSupply = new Supply(aMsgFactory, aDownstream);
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
        LOG2(kMedia, kError, "ProtocolHttps::Stream(%.*s) - connect failure\n", PBUF(aUri));
        return EProtocolStreamErrorUnrecoverable;
    }
    ProtocolStreamResult res = DoStream();
    iLock.Wait();
    if (iStopped) {
        iSupply->OutputFlush(iNextFlushId);
    }
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
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

EStreamPlay ProtocolHttps::OkToPlay(TUint aStreamId)
{
    return iIdProvider->OkToPlay(aStreamId);
}

TUint ProtocolHttps::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    return MsgFlush::kIdInvalid;
}

TUint ProtocolHttps::TryStop(TUint aStreamId)
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
        iSocket.Interrupt(true);
    }
    iLock.Signal();
    return (stop? iNextFlushId : MsgFlush::kIdInvalid);
}

Brn ProtocolHttps::Read(TUint aBytes)
{
    return iDechunker.Read(aBytes);
}

void ProtocolHttps::ReadFlush()
{
    iDechunker.ReadFlush();
}

void ProtocolHttps::ReadInterrupt()
{
    iDechunker.ReadInterrupt();
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

    ContentProcessor* cp = nullptr;
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
        iSupply->OutputStream(iUri.AbsoluteUri(), totalBytes, 0, false/*seekable*/, false/*live*/, *this, iStreamId);
        iDechunker.SetChunked(iHeaderTransferEncoding.IsChunked());
        cp = iProtocolManager->GetAudioProcessor();
        res = cp->Stream(*this, totalBytes);
    }
    catch (ReaderError&) {
    }
    if (cp != nullptr) {
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

TBool ProtocolHttps::IsCurrentStream(TUint aStreamId) const
{
    if (iStreamId != aStreamId || aStreamId == IPipelineIdProvider::kStreamIdInvalid) {
        return false;
    }
    return true;
}
