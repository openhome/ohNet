#pragma once

#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Http.h>

namespace OpenHome {
namespace Media {

class RtspHeader
{
public:
    // General headers
    static const Brn kCacheControl;
    static const Brn kConnection;
    static const Brn kDate;
    static const Brn kVia;
    // Request headers
    static const Brn kAccept;
    static const Brn kAcceptEncoding;
    static const Brn kAcceptLanguage;
    static const Brn kAuthorization;
    static const Brn kFrom;
    static const Brn kIfModifiedSince;
    static const Brn kRange;
    static const Brn kReferer;
    static const Brn kUserAgent;
    // Response headers
    static const Brn kLocation;
    static const Brn kProxyAuthenticate;
    static const Brn kPublic;
    static const Brn kRetryAfter;
    static const Brn kServer;
    static const Brn kVary;
    static const Brn kWwwAuthenticate;
    // Entity headers
    static const Brn kAllow;
    static const Brn kContentBase;
    static const Brn kContentEncoding;
    static const Brn kContentLanguage;
    static const Brn kContentLength;
    static const Brn kContentLocation;
    static const Brn kContentType;
    static const Brn kSession;
    static const Brn kExpires;
    static const Brn kLastModified;
};

class RtspMethod
{
public:
    static const Brn kDescribe;
    static const Brn kAnnounce;
    static const Brn kGetParameter;
    static const Brn kOptions;
    static const Brn kPause;
    static const Brn kPlay;
    static const Brn kRecord;
    static const Brn kRedirect;
    static const Brn kSetup;
    static const Brn kSetParameter;
    static const Brn kFlush;
    static const Brn kTeardown;
    static const Brn kPost;
};

class RtspStatus : HttpStatus
{
public:
    RtspStatus(TUint aCode, const Brn aReason);

public:
    static const HttpStatus kContinue;
    static const HttpStatus kOk;
    static const HttpStatus kCreated;
    static const HttpStatus kLowOnStorageSpace;
    static const HttpStatus kMultipleChoices;
    static const HttpStatus kMovedPermanently;
    static const HttpStatus kMovedTemporarily;
    static const HttpStatus kSeeOther;
    static const HttpStatus kNotModified;
    static const HttpStatus kUseProxy;
    static const HttpStatus kBadRequest;
    static const HttpStatus kUnauthorized;
    static const HttpStatus kPaymentRequired;
    static const HttpStatus kForbidden;
    static const HttpStatus kNotFound;
    static const HttpStatus kMethodNotAllowed;
    static const HttpStatus kNotAcceptable;
    static const HttpStatus kProxyAuthenticationRequired;
    static const HttpStatus kRequestTimeout;
    static const HttpStatus kGone;
    static const HttpStatus kLengthRequired;
    static const HttpStatus kPreconditionFailed;
    static const HttpStatus kRequestEntityTooLarge;
    static const HttpStatus kRequestUriTooLarge;
    static const HttpStatus kUnsupportedMediaType;
    static const HttpStatus kParameterNotUnderstood;
    static const HttpStatus kConferenceNotFound;
    static const HttpStatus kNotEnoughBandwidth;
    static const HttpStatus kSessionNotFound;
    static const HttpStatus kMethodNotValidInThisState;
    static const HttpStatus kHeaderFieldNotValidForResource;
    static const HttpStatus kInvalidRange;
    static const HttpStatus kParameterIsReadOnly;
    static const HttpStatus kAggregateOperationNotAllowed;
    static const HttpStatus kOnlyAggregateOperationAllowed;
    static const HttpStatus kUnsupportedTransport;
    static const HttpStatus kDestinationUnreachable;
    static const HttpStatus kInternalServerError;
    static const HttpStatus kNotImplemented;
    static const HttpStatus kBadGateway;
    static const HttpStatus kServiceUnavailable;
    static const HttpStatus kGatewayTimeout;
    static const HttpStatus kRtspVersionNotSupported;
    static const HttpStatus kOptionNotSupported;
};

class IWriterRtspMethod
{
public:
    virtual void WriteMethod(const Brx& aMethod, const Brx& aUri) = 0;
    virtual ~IWriterRtspMethod() {}
};

// WriterRtspRequest

class WriterRtspRequest : public WriterHttpHeader, public IWriterRtspMethod
{
public:
    WriterRtspRequest(IWriter& aWriter);
    virtual void WriteMethod(const Brx& aMethod, const Brx& aUri);
};

// ReaderRtspResponse

class ReaderRtspResponse : public ReaderHttpResponse
{
public:
    ReaderRtspResponse(Environment& aEnv, ReaderUntil& aReader);
    void ReadRtsp(TChar aFirstChar);
    void ReadRtsp();
protected:
    virtual void ProcessStatus(const Brx& aVersion, const Brx& aCode, const Brx& aDescription);
};


class HeaderRtspSession : public IHttpHeader
{
    static const TUint kMaxSessionIdBytes = 100;
public:
    TBool Received() const;
    const Brx& SessionId() const;
    TUint Timeout() const;
private:
    virtual void Reset();
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    Bws<kMaxSessionIdBytes> iSessionId;
    TUint iTimeout;
    TBool iReceived;
};


class ISdpHandler
{
public:
    virtual void Reset() = 0;
    virtual void Decode(TByte aType, const Brx& aValue) = 0;
    ~ISdpHandler() {}
};

class SdpInfo : public ISdpHandler
{
    static const TUint kMaxMediaTransportBytes = 20;
    static const TUint kMaxMediaFormatBytes = 100;
    static const TUint kMaxAudioPgmpuBytes = 8 * 1024;
    static const TUint kMaxAudioControlUriBytes = 1024;
    static const TUint kMaxSessionControlUriBytes = 1024;
    static const TUint kMaxFmtpBytes = 80;
    static const TUint kMaxRsaaeskeyBytes = 512; //actually 16 I think - ToDo
    static const TUint kMaxAesivBytes = 16;

public:
    SdpInfo();
    const Brx& ContentType() const;
    TUint MediaCount() const;
    TUint MediaAudioCount() const;
    TUint MediaVideoCount() const;
    TUint MediaApplicationCount() const;
    TUint MediaDataCount() const;
    TUint MediaAudioPort() const;
    const Brx& MediaAudioTransport() const;
    const Brx& MediaAudioFormat() const;
    const Brx& AudioPgmpu() const;
    const Brx& AudioControlUri() const;
    const Brx& Fmtp() const;
    const Brx& Rsaaeskey() const;
    const Brx& Aesiv() const;
    TUint AudioStream() const;
    const Brx& SessionControlUri() const;

private:
    // ISdpHandler
    virtual void Reset();
    virtual void Decode(TByte aType, const Brx& aValue);
    // Helpers
    void DecodeA(const Brx& aValue);
    void DecodeM(const Brx& aValue);
    void DecodeAttributeAudioPgmpu(const Brx& aValue);
    void DecodeAttributeAudioControl(const Brx& aValue);
    void DecodeAttributeAudioStream(const Brx& aValue);
    void DecodeAttributeSessionControl(const Brx& aValue);
    void DecodeAttributeFmtp(const Brx& aValue);
    void DecodeAttributeRsaaeskey(const Brx& aValue);
    void DecodeAttributeAesiv(const Brx& aValue);
    TBool FirstMediaAudio() const;
private:
    TByte iCurrentMedia;
    TUint iMediaCount;
    TUint iMediaAudioCount;
    TUint iMediaVideoCount;
    TUint iMediaApplicationCount;
    TUint iMediaDataCount;
    TUint iMediaAudioPort;
    Bws<kMaxMediaTransportBytes> iMediaAudioTransport;
    Bws<kMaxMediaFormatBytes> iMediaAudioFormat;
    Bws<kMaxAudioPgmpuBytes> iAudioPgmpu;
    Bws<kMaxAudioControlUriBytes> iAudioControlUri;
    TUint iAudioStream;
    Bws<kMaxSessionControlUriBytes> iSessionControlUri;
    Bws<kMaxFmtpBytes> iFmtp;
    Bws<kMaxRsaaeskeyBytes> iRsaaeskey;
    Bws<kMaxAesivBytes> iAesiv;
};

// The same socket receives RTP, RTSP requests, RTSP responses.
// This class reports which msg type is starting and optionally (for RTP) consumes the first byte
class ReaderRtp : public IReader, private INonCopyable
{
public:
    enum MsgType
    {
        eRtp
       ,eRtspRequest
       ,eRtspResponse
    };
public:
    ReaderRtp(IReader& aReader);
    MsgType ReadType();
public: // from IReader
    Brn Read(TUint aBytes) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    IReader& iReader;
    Bws<1> iChar;
};

class RtspClient
{
public:
    static const TUint kReadBufferBytes = 12 * 1024; // allow for long codec data
    static const TUint kWriteBufferBytes = 1024;
    static const TUint kConnectTimeout = 5000; // in milliseconds
    static const TUint kMaxUriBytes = 1024;
public:
    RtspClient(Environment& aEnv, IReader& aReader, IWriter& aWriter, const Brx& aGuid);

    void Initialise(const Uri& aUri);

    void WriteMethodDescribe();
    void WriteMethodAnnounce();
    void WriteMethodGetParameter(const Brx& aUri);
    void WriteMethodOptions();
    void WriteMethodPause(const Brx& aUri);
    void WriteMethodPlay(const Brx& aUri);
    void WriteMethodRecord(const Brx& aUri);
    void WriteMethodRedirect();
    void WriteMethodSetup(const Brx& aUri);
    void WriteMethodSetParameter(const Brx& aUri);
    void WriteMethodFlush(const Brx& aUri);
    void WriteMethodTeardown(const Brx& aUri);

    void WriteHeaderSeq();
    void WriteHeaderUserAgent();
    void WriteHeaderAccept(const Brx& aValue);
    void WriteHeaderTransport(const Brx& aValue);
    void WriteHeaderSupported(const Brx& aValue);
    void WriteHeaderAccelerateStreaming(TUint aDuration, TUint aBandwidth);
    void WriteHeaderSession();

    const Brx& SessionId() const;

    void WriteFlush();

    TUint Read();
    void Flush();
    void Interrupt();

    Brn ReadRtsp(SdpInfo& aSdpInfo);
    Brn ReadRtp();
    void ReadSdp(ISdpHandler& aSdpHandler);
    TUint Timeout() const;
private:
    WriterRtspRequest iWriterRequest;
    ReaderRtp iReaderRtp;
    ReaderUntilS<kReadBufferBytes> iReaderUntil;
    ReaderHttpRequest iReaderRequest;
    ReaderRtspResponse iReaderResponse;
    Bws<kMaxUriBytes> iUri;
    TUint iSeq;
    HttpHeaderContentLength iHeaderContentLength;
    HeaderRtspSession iHeaderRtspSession;
    const Bws<100> iGuid;         // unique; same GUID must be used for all requests in a single streaming session
};

} //namespace Media
} //namespace OpenHome


