#ifndef HEADER_HTTP_HTTP
#define HEADER_HTTP_HTTP

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/Standard.h>

#include <vector>

EXCEPTION(HttpError)
EXCEPTION(HttpInvalidResponse)

namespace OpenHome {

class WriterHttpHeader;

class Http
{
public:
    // Methods
    static const Brn kMethodOptions;
    static const Brn kMethodGet;
    static const Brn kMethodHead;
    static const Brn kMethodPost;
    static const Brn kMethodPut;
    static const Brn kMethodDelete;
    static const Brn kMethodTrace;
    static const Brn kMethodConnect;
    static const Brn kMethodExtension;
    // General headers
    static const Brn kHeaderCacheControl;
    static const Brn kHeaderConnection;
    static const Brn kHeaderDate;
    static const Brn kHeaderPragma;
    static const Brn kHeaderTrailer;
    static const Brn kHeaderTransferEncoding;
    static const Brn kHeaderUpgrade;
    static const Brn kHeaderVia;
    static const Brn kHeaderWarning;
    // Request headers
    static const Brn kHeaderAccept;
    static const Brn kHeaderAcceptCharset;
    static const Brn kHeaderAcceptEncoding;
    static const Brn kHeaderAcceptLanguage;
    static const Brn kHeaderAuthorization;
    static const Brn kHeaderExpect;
    static const Brn kHeaderFrom;
    static const Brn kHeaderHost;
    static const Brn kHeaderIfMatch;
    static const Brn kHeaderIfModifiedSince;
    static const Brn kHeaderIfNoneMatch;
    static const Brn kHeaderIfRange;
    static const Brn kHeaderIfUnmodifiedSince;
    static const Brn kHeaderMaxForwards;
    static const Brn kHeaderProxyAuthorization;
    static const Brn kHeaderRange;
    static const Brn kHeaderReferer;
    static const Brn kHeaderTe;
    static const Brn kHeaderUserAgent;
    static const Brn kHeaderAccessControlRequestMethod;
    // Response headers
    static const Brn kHeaderAcceptRanges;
    static const Brn kHeaderAge;
    static const Brn kHeaderETag;
    static const Brn kHeaderLocation;
    static const Brn kHeaderProxyAuthenticate;
    static const Brn kHeaderRetryAfter;
    static const Brn kHeaderServer;
    static const Brn kHeaderVary;
    static const Brn kHeaderWwwAuthenticate;
    static const Brn kHeaderAllowOrigin;
    // Entity headers
    static const Brn kHeaderAllow;
    static const Brn kHeaderContentEncoding;
    static const Brn kHeaderContentLanguage;
    static const Brn kHeaderContentLength;
    static const Brn kHeaderContentLocation;
    static const Brn kHeaderContentMd5;
    static const Brn kHeaderContentRange;
    static const Brn kHeaderContentType;
    static const Brn kHeaderExpires;
    static const Brn kHeaderLastModified;
    // other constants
    static const Brn kSchemeHttp;
    static const Brn kValueZero;
    static const Brn kHeaderSeparator;
    static const Brn kHeaderTerminator;
    static const Brn kConnectionClose;
    static const Brn kConnectionUpgrade;
    static const Brn kContentLanguageEnglish;
    static const Brn kRangeBytes;
    static const Brn kRangeSeparator;
    static const Brn kExpect100Continue;
    static const Brn kChunkedCountSeparator;
    static const Brn kTransferEncodingChunked;
    static const Brn kTransferEncodingIdentity;
public:
    enum EVersion
    {
        eHttp09 = 9,    // HTTP/0.9
        eHttp10 = 10,   // HTTP/1.0
        eHttp11 = 11,   // HTTP/1.1
        eRtsp10 = 12,   // RTSP/1.0
    };
public:
    static EVersion Version(const Brx& aBuffer);
    static const Brx& Version(EVersion aVersion);
    static void WriteHeaderRangeFirstOnly(WriterHttpHeader& aWriter, TUint64 aFirst); //bytes=<aFirst>-
    static void WriteHeaderRange(WriterHttpHeader& aWriter, TUint64 aFirst, TUint64 aLast); //bytes=<aFirst>-<aLast>
    static void WriteHeaderHostAndPort(WriterHttpHeader& aWriter, const Brx& aHost, TUint aPort);
    static void WriteHeaderContentLength(WriterHttpHeader& aWriter, TUint aLength);
    static void WriteHeaderContentType(WriterHttpHeader& aWriter, const Brx& aType);
    static void WriteHeaderConnectionClose(WriterHttpHeader& aWriter);
};

class HttpStatus
{
public:
    static const TUint kInformationCodes = 100;
    static const TUint kSuccessCodes = 200;
    static const TUint kRedirectionCodes = 300;
    static const TUint kClientErrorCodes = 400;
    static const TUint kServerErrorCodes = 500;
public:
    static const HttpStatus kContinue;
    static const HttpStatus kSwitchingProtocols;
    static const HttpStatus kOk;
    static const HttpStatus kCreated;
    static const HttpStatus kAccepted;
    static const HttpStatus kNonAuthoritativeInformation;
    static const HttpStatus kNoContent;
    static const HttpStatus kResetContent;
    static const HttpStatus kPartialContent;
    static const HttpStatus kMultipleChoices;
    static const HttpStatus kMovedPermanently;
    static const HttpStatus kFound;
    static const HttpStatus kSeeOther;
    static const HttpStatus kNotModified;
    static const HttpStatus kUseProxy;
    static const HttpStatus kTemporaryRedirect;
    static const HttpStatus kBadRequest;
    static const HttpStatus kUnauthorized;
    static const HttpStatus kPaymentRequired;
    static const HttpStatus kForbidden;
    static const HttpStatus kNotFound;
    static const HttpStatus kMethodNotAllowed;
    static const HttpStatus kNotAcceptable;
    static const HttpStatus kProxyAuthenticationRequired;
    static const HttpStatus kRequestTimeout;
    static const HttpStatus kConflict;
    static const HttpStatus kGone;
    static const HttpStatus kLengthRequired;
    static const HttpStatus kPreconditionFailed;
    static const HttpStatus kRequestEntityTooLarge;
    static const HttpStatus kRequestUriTooLarge;
    static const HttpStatus kUnsupportedMediaType;
    static const HttpStatus kRequestedRangeNotSatisfiable;
    static const HttpStatus kExpectationFailure;
    static const HttpStatus kInternalServerError;
    static const HttpStatus kNotImplemented;
    static const HttpStatus kBadGateway;
    static const HttpStatus kServiceUnavailable;
    static const HttpStatus kGatewayTimeout;
    static const HttpStatus kHttpVersionNotSupported;
public:
    TUint Code() const;
    const Brx& Reason() const;
    TBool operator==(const HttpStatus& aStatus) const;
    TBool operator!=(const HttpStatus& aStatus) const;
protected:
    HttpStatus(TUint aCode, const Brn aReason);
protected:
    TUint iCode;
    Brn iReason;
};

class IWriterHttpMethod
{
public:
    virtual void WriteMethod(const Brx& aMethod, const Brx& aUri, Http::EVersion aVersion) = 0;
    virtual ~IWriterHttpMethod() {}
};

class IWriterHttpStatus
{
public:
    virtual void WriteStatus(const HttpStatus& aStatus, Http::EVersion aVersion) = 0;
    virtual ~IWriterHttpStatus() {}
};

class IWriterField : public IWriterAscii
{
};

class IWriterHttpHeader : public IWriter
{
public:
    virtual void WriteHeader(const Brx& aField, const Brx& aValue) = 0;
    virtual IWriterAscii& WriteHeaderField(const Brx& aField) = 0; // returns a stream for writing the value
    virtual ~IWriterHttpHeader() {}
};

class IHttpHeader
{
public:
    virtual void Reset() = 0;
    virtual TBool Recognise(const Brx& aHeader) = 0;
    virtual void Process(const Brx& aValue) = 0;
    virtual ~IHttpHeader() {}
};

class HttpHeader : public IHttpHeader
{
public:
    TBool Received() const;
protected:
    HttpHeader();
    void SetReceived();
    virtual void Reset();
private:
    TBool iReceived;
};

class Environment;

class ReaderHttpHeader : protected INonCopyable
{
public:
    IHttpHeader& Header() const;
    void AddHeader(IHttpHeader& aHeader);
protected:
    ReaderHttpHeader(Environment& aEnv);
    void ResetHeaders();
    void ProcessHeader(const Brx& aField, const Brx& aValue);
protected:
    Environment& iEnv;
private:
    IHttpHeader* iHeader;
    std::vector<IHttpHeader*> iHeaders;
};

class Timer;

class ReaderHttpRequest : public ReaderHttpHeader
{
    static const TUint kMaxMethodBytes = 20;
    static const TUint kMaxUriBytes = 200;
public:
    ReaderHttpRequest(Environment& aEnv, IReader& aReader);
    virtual ~ReaderHttpRequest();
    void Read(TUint aTimeoutMs = 0);
    void Flush();
    void Interrupt();
    void AddMethod(const Brx& aMethod);
    const Brx& Method() const;
    const Brx& Uri() const;
    Http::EVersion Version() const;
    TBool MethodNotAllowed() const;
    void UnescapeUri();
protected:
    void ProcessMethod(const Brx& aMethod, const Brx& aUri, const Brx& aVersion);
private:
    void ReadTimeout();
protected:
    IReader& iReader;
    Timer* iTimer;
    std::vector<const Brx*> iMethods;
    const Brx* iMethod;
    Bws<kMaxUriBytes> iUri;
    Http::EVersion iVersion;
};

class ReaderHttpResponse : public ReaderHttpHeader
{
public:
    static const TUint kMaxDescriptionBytes = 100;
    static const TUint kMaxUriBytes = 200;
public:
    ReaderHttpResponse(Environment& aEnv, IReader& aReader);
    virtual ~ReaderHttpResponse();
    void Read(TUint aTimeoutMs = 0);
    void Flush();
    void Interrupt();
    Http::EVersion Version() const;
    const HttpStatus& Status() const;
protected:
    virtual void ProcessStatus(const Brx& aVersion, const Brx& aCode, const Brx& aDescription);
private:
    void ReadTimeout();
protected:
    class StatusWritable : public HttpStatus
    {
    public:
        StatusWritable();
        void Set(TUint aCode, const Brx& aDescription);
    };
protected:
    IReader& iReader;
    Timer* iTimer;
    Http::EVersion iVersion;
    StatusWritable iStatus;
    Bws<kMaxDescriptionBytes> iDescription;
};

class WriterHttpField : public WriterAscii
{
    friend class WriterHttpHeader;
public:
    WriterHttpField(IWriter& aWriter);
    // IWriter
    virtual void Write(TByte aValue);
    virtual void Write(const Brx& aBuffer);
    virtual void WriteFlush();
private:
    void Flush();
};

class WriterHttpHeader : public IWriterHttpHeader
{
public:
    // IWriter
    virtual void Write(TByte aValue);
    virtual void Write(const Brx& aBuffer);
    virtual void WriteFlush();
    // IWriterHeader
    virtual void WriteHeader(const Brx& aField, const Brx& aValue);
    virtual void WriteHeaderBase64(const Brx& aField, const Brx& aValue);
    virtual IWriterAscii& WriteHeaderField(const Brx& aField); // returns a stream for writing the value
protected:
    WriterHttpHeader(IWriter& aWriter);
protected:
    WriterHttpField iWriter;
};

class WriterHttpRequest : public WriterHttpHeader, public IWriterHttpMethod
{
public:
    WriterHttpRequest(IWriter& aWriter);
    virtual void WriteMethod(const Brx& aMethod, const Brx& aUri, Http::EVersion aVersion);
};

class WriterHttpResponse : public WriterHttpHeader, public IWriterHttpStatus
{
public:
    WriterHttpResponse(IWriter& aWriter);
    virtual void WriteStatus(const HttpStatus& aStatus, Http::EVersion aVersion);
    virtual void Write(const Brx& aBuffer);
};

// Standard Header Processors

class HttpHeaderHost : public HttpHeader
{
public:
    OpenHome::Endpoint& Endpoint();
    const Brx& Host() const;
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    OpenHome::Endpoint iEndpoint;
    Brh iHost;
};

class HttpHeaderContentLength : public HttpHeader
{
public:
    TUint ContentLength() const;
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    TUint iContentLength;
};

class HttpHeaderTransferEncoding : public HttpHeader
{
public:
    TBool IsChunked() const;
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    TBool iChunked;
};

class HttpHeaderConnection : public HttpHeader
{
public:
    TBool Close() const;
    TBool Upgrade() const;
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    TBool iClose;
    TBool iUpgrade;
};

class HttpHeaderLocation : public HttpHeader
{
    static const TUint kMaxLocationBytes = 1000;
public:
    const Brx& Location() const;
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    Bws<kMaxLocationBytes> iLocation;
};

class HttpHeaderContentType : public HttpHeader
{
    static const TUint kMaxTypeBytes = 100;
public:
    const Brx& Type() const;
protected:
    void Process(const Brx& aKey, const Brx& aValue);
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
protected:
    TBool iReceived;
    Bws<kMaxTypeBytes> iType;
};

class HttpHeaderExpect : public HttpHeader
{
public:
    TBool Continue() const;
private:
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    TBool iContinue;
};

class HttpHeaderAccessControlRequestMethod : public HttpHeader
{
public:
    const Brx& Method() const;
private:
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    static const TUint kMaxMethodBytes = 32;
    Bws<kMaxMethodBytes> iMethod;
};

class EndpointHttp : public Endpoint
{
public:
    EndpointHttp(const Uri& aUri);
};

class ReaderHttpChunkedDynamic // deprecated
{
public:
    ReaderHttpChunkedDynamic(IReader& aReader); // IReader must allow reads at least 4k
    void Read();
    void TransferTo(Bwh& aBuf);
private:
    ReaderHttpChunkedDynamic& operator=(const ReaderHttpChunkedDynamic&);
private:
    IReader& iReader;
    Bwh iEntity;
};

class ReaderHttpChunked : public IReader
{
    static const TUint kChunkSizeBufBytes = 10;
    static const TUint kBufSizeBytes = (10 * 1024) + kChunkSizeBufBytes; // FIXME - allow user-definable size
public:
    ReaderHttpChunked(Srx& aReader);
    void SetChunked(TBool aChunked);
    Brn ReadRemaining();
public: // from IReader
    Brn Read(TUint aBytes);
    Brn ReadUntil(TByte aSeparator);
    void ReadFlush();
    void ReadInterrupt();
private:
    Brn Dechunk(Brn& aBuf);
    void ReadNextChunkSize(Brn& aBuf);
private:
    Srx& iReader;
    Bws<kBufSizeBytes> iDechunkBuf;
    Bws<kBufSizeBytes> iOutputBuf;
    TUint iChunkBytesRemaining;
    TBool iChunked;
};

class WriterHttpChunked : public IWriter
{
    static const TUint kMaxBufferBytes = 6000;
public:
    WriterHttpChunked(IWriter& aWriter);
    void SetChunked(TBool aValue);
    virtual void Write(TByte aValue);
    virtual void Write(const Brx& aBuffer);
    virtual void WriteFlush();
private:
    Sws<kMaxBufferBytes> iBuffer;
    TBool iChunked;
};


class HttpReader : public IReader
{
private:
    static const TUint kHttpPort = 80;
    static const TUint kReadBufferBytes = 4 * 1024;
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeoutMs = 3000;
    static const TUint kResponseTimeoutMs = 60 * 1000;

public:
    HttpReader(Environment& aEnv);
    HttpReader(Environment& aEnv, const Brx& aUserAgent);
    ~HttpReader();

    TBool Connect(const Uri& aUri);
    void Close();
    void Interrupt(TBool aInterrupt);
    TUint ContentLength() const;
    Brn ReadRemaining();
public: // from IReader
    Brn Read(TUint aBytes) override;
    virtual Brn ReadUntil(TByte aSeparator) override;
    virtual void ReadFlush() override;
    virtual void ReadInterrupt() override;
private:
    TUint WriteRequest(const Uri& aUri);
    TBool ConnectAndProcessHeader(const Uri& aUri);
    TBool Connect(Endpoint aEndpoint);
    void Open();

private:
    Environment& iEnv;
    Bwh iUserAgent;
    SocketTcpClient iTcpClient;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderLocation iHeaderLocation;
    HttpHeaderTransferEncoding iHeaderTransferEncoding;
    Srs<kReadBufferBytes> iReadBuffer;
    ReaderHttpResponse iReaderResponse;
    Sws<kWriteBufferBytes> iWriteBuffer;
    WriterHttpRequest iWriterRequest;
    ReaderHttpChunked iReader;
    TBool iSocketIsOpen;
    TBool iConnected;
    TUint iTotalBytes;
};



} // namespace OpenHome

#endif // HEADER_HTTP_HTTP
