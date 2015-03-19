#include <OpenHome/Media/Protocol/Rtsp.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>

using namespace OpenHome;
using namespace Media;

// General headers
const Brn RtspHeader::kCacheControl("Cache-Control");
const Brn RtspHeader::kConnection("Connection");
const Brn RtspHeader::kDate("Date");
const Brn RtspHeader::kVia("Via");

// Request headers
const Brn RtspHeader::kAccept("Accept");
const Brn RtspHeader::kAcceptEncoding("Accept-Encoding");
const Brn RtspHeader::kAcceptLanguage("Accept-Language");
const Brn RtspHeader::kAuthorization("Authorization");
const Brn RtspHeader::kFrom("From");
const Brn RtspHeader::kIfModifiedSince("If-Modified-Since");
const Brn RtspHeader::kRange("Range");
const Brn RtspHeader::kReferer("Referer");
const Brn RtspHeader::kUserAgent("User-Agent");

// Response headers
const Brn RtspHeader::kLocation("Location");
const Brn RtspHeader::kProxyAuthenticate("ProxyAuthenticate");
const Brn RtspHeader::kPublic("Public");
const Brn RtspHeader::kRetryAfter("Retry-After");
const Brn RtspHeader::kServer("Server");
const Brn RtspHeader::kVary("Vary");
const Brn RtspHeader::kWwwAuthenticate("WWW-Authenticate");

// Entity headers
const Brn RtspHeader::kAllow("Allow");
const Brn RtspHeader::kContentBase("Content-Base");
const Brn RtspHeader::kContentEncoding("Content-Encoding");
const Brn RtspHeader::kContentLanguage("Content-Language");
const Brn RtspHeader::kContentLength("Content-Length");
const Brn RtspHeader::kContentLocation("Content-Location");
const Brn RtspHeader::kContentType("Content-Type");
const Brn RtspHeader::kSession("Session");
const Brn RtspHeader::kExpires("Expires");
const Brn RtspHeader::kLastModified("Last-Modified");

// Methods
const Brn RtspMethod::kDescribe("DESCRIBE");
const Brn RtspMethod::kAnnounce("ANNOUNCE");
const Brn RtspMethod::kGetParameter("GET_PARAMETER");
const Brn RtspMethod::kOptions("OPTIONS");
const Brn RtspMethod::kPause("PAUSE");
const Brn RtspMethod::kPlay("PLAY");
const Brn RtspMethod::kRecord("RECORD");
const Brn RtspMethod::kRedirect("REDIRECT");
const Brn RtspMethod::kSetup("SETUP");
const Brn RtspMethod::kSetParameter("SET_PARAMETER");
const Brn RtspMethod::kFlush("FLUSH");
const Brn RtspMethod::kTeardown("TEARDOWN");
const Brn RtspMethod::kPost("POST");

RtspStatus::RtspStatus(TUint aCode, const Brn aReason)
    : HttpStatus(aCode, aReason)
{
}

// Informational codes
const HttpStatus RtspStatus::kContinue = RtspStatus(100, Brn("Continue"));
// Success codes
const HttpStatus RtspStatus::kOk = RtspStatus(200, Brn("OK"));
const HttpStatus RtspStatus::kCreated = RtspStatus(201, Brn("Created"));
const HttpStatus RtspStatus::kLowOnStorageSpace = RtspStatus(250, Brn("Low On Storage Space"));
// Redirection codes
const HttpStatus RtspStatus::kMultipleChoices = RtspStatus(300, Brn("Multiple Choices"));
const HttpStatus RtspStatus::kMovedPermanently = RtspStatus(301, Brn("Moved Permanently"));
const HttpStatus RtspStatus::kMovedTemporarily = RtspStatus(302, Brn("Moved Temporarily"));
const HttpStatus RtspStatus::kSeeOther = RtspStatus(303, Brn("See Other"));
const HttpStatus RtspStatus::kNotModified = RtspStatus(304, Brn("Not Modified"));
const HttpStatus RtspStatus::kUseProxy = RtspStatus(305, Brn("Use Proxy"));
// Client error codes
const HttpStatus RtspStatus::kBadRequest = RtspStatus(400, Brn("Bad Request"));
const HttpStatus RtspStatus::kUnauthorized = RtspStatus(401, Brn("Unauthorized"));
const HttpStatus RtspStatus::kPaymentRequired = RtspStatus(402, Brn("Payment Required"));
const HttpStatus RtspStatus::kForbidden = RtspStatus(403, Brn("Forbidden"));
const HttpStatus RtspStatus::kNotFound = RtspStatus(404, Brn("Not Found"));
const HttpStatus RtspStatus::kMethodNotAllowed = RtspStatus(405, Brn("Method Not Allowed"));
const HttpStatus RtspStatus::kNotAcceptable = RtspStatus(406, Brn("Not Acceptable"));
const HttpStatus RtspStatus::kProxyAuthenticationRequired = RtspStatus(407, Brn("Proxy Authentication Required"));
const HttpStatus RtspStatus::kRequestTimeout = RtspStatus(408, Brn("Request Timeout"));
const HttpStatus RtspStatus::kGone = RtspStatus(410, Brn("Gone"));
const HttpStatus RtspStatus::kLengthRequired = RtspStatus(411, Brn("Length Required"));
const HttpStatus RtspStatus::kPreconditionFailed = RtspStatus(412, Brn("Precondition Failed"));
const HttpStatus RtspStatus::kRequestEntityTooLarge = RtspStatus(413, Brn("Request Entity Too Large"));
const HttpStatus RtspStatus::kRequestUriTooLarge = RtspStatus(414, Brn("Request URI Too Large"));
const HttpStatus RtspStatus::kUnsupportedMediaType = RtspStatus(415, Brn("Unsupported Media Type"));
const HttpStatus RtspStatus::kParameterNotUnderstood = RtspStatus(451, Brn("Parameter Not Understood"));
const HttpStatus RtspStatus::kConferenceNotFound = RtspStatus(452, Brn("Conference Not Found"));
const HttpStatus RtspStatus::kNotEnoughBandwidth = RtspStatus(453, Brn("Not Enough Bandwidth"));
const HttpStatus RtspStatus::kSessionNotFound = RtspStatus(454, Brn("Session Not Found"));
const HttpStatus RtspStatus::kMethodNotValidInThisState = RtspStatus(455, Brn("Method Not Valid In This State"));
const HttpStatus RtspStatus::kHeaderFieldNotValidForResource = RtspStatus(456, Brn("Header Field Not Valid For Resource"));
const HttpStatus RtspStatus::kInvalidRange = RtspStatus(457, Brn("Invalid Range"));
const HttpStatus RtspStatus::kParameterIsReadOnly = RtspStatus(458, Brn("Parameter Is Read-Only"));
const HttpStatus RtspStatus::kAggregateOperationNotAllowed = RtspStatus(459, Brn("Aggregate Operation Not Allowed"));
const HttpStatus RtspStatus::kOnlyAggregateOperationAllowed = RtspStatus(460, Brn("Only Aggregate Operation Allowed"));
const HttpStatus RtspStatus::kUnsupportedTransport = RtspStatus(461, Brn("Unsupported Transport"));
const HttpStatus RtspStatus::kDestinationUnreachable = RtspStatus(462, Brn("Destination Unreachable"));
// Server error codes
const HttpStatus RtspStatus::kInternalServerError = RtspStatus(500, Brn("Internal Server Error"));
const HttpStatus RtspStatus::kNotImplemented = RtspStatus(501, Brn("Not Implemented"));
const HttpStatus RtspStatus::kBadGateway = RtspStatus(502, Brn("Bad Gateway"));
const HttpStatus RtspStatus::kServiceUnavailable = RtspStatus(503, Brn("Service Unavailable"));
const HttpStatus RtspStatus::kGatewayTimeout = RtspStatus(504, Brn("Gateway Timeout"));
const HttpStatus RtspStatus::kRtspVersionNotSupported = RtspStatus(505, Brn("RTSP Version Not Supported"));
const HttpStatus RtspStatus::kOptionNotSupported = RtspStatus(551, Brn("Option Not Supported"));


// WriterRtspRequest

static const Brn kRtspVersion("RTSP/1.0");

WriterRtspRequest::WriterRtspRequest(IWriter& aWriter)
    : WriterHttpHeader(aWriter)
{
}

void WriterRtspRequest::WriteMethod(const Brx& aMethod, const Brx& aUri)
{
    LOG(kHttp, "Http Write Method   ");
    
    iWriter.Write(aMethod);
    iWriter.WriteSpace();
    iWriter.Write(aUri);
    iWriter.WriteSpace();
    iWriter.Write(kRtspVersion);
    iWriter.WriteNewline();
}


// ReaderRtspResponse

ReaderRtspResponse::ReaderRtspResponse(Environment& aEnv, ReaderUntil& aReader)
    : ReaderHttpResponse(aEnv, aReader)
{
    iVersion = Http::eRtsp10;
}

void ReaderRtspResponse::ReadRtsp()
{
    Read(); //use http implementation
}

void ReaderRtspResponse::ReadRtsp(TChar aFirstChar)
{
    //iReader.ReadFlush(); // FIXME - why do this?
    ResetHeaders();

    TUint count = 0;
    Bws<500> firstLine;
    firstLine.Append(aFirstChar);
    LOG(kHttp, "RTSP Read Response first char (");
    LOG(kHttp, firstLine);
    LOG(kHttp, ")\n");
    firstLine.Append(iReader.ReadUntil(Ascii::kLf));
    LOG(kHttp, "RTSP Read Response  first line (");
    LOG(kHttp, firstLine);
    LOG(kHttp, ")\n");
    Brn line(firstLine);

    for (;;) {
        LOG(kHttp, "RTSP Read Response  ");
        LOG(kHttp, line);
        LOG(kHttp, "\n");

        TUint bytes = line.Bytes();
        if (!bytes && count) {
            return;     // terminate on blank line, unless before first header(RFC 2616 section 4.1)
        }

        if (!bytes || !Ascii::IsWhitespace(line[0])) { // a line starting with spaces is a continuation line
            Parser parser(line);
            if (count == 0) { // status
                LOG(kHttp, " HttpStatus   ");
                Brn version = parser.Next(' ');
                Brn code = parser.Next(' ');
                Brn description = Ascii::Trim(parser.Remaining());
                ProcessStatus(version, code, description);
            }
            else { // header
                LOG(kHttp, " header  ");
                Brn field = parser.Next(':');
                Brn value = Ascii::Trim(parser.Remaining());
                ProcessHeader(field, value);    // must be able to read section after method block in RTSP - defined by "Content-Length"
            }
            count++;
        }
        line.Set(iReader.ReadUntil(Ascii::kLf));
    }
}

void ReaderRtspResponse::ProcessStatus(const Brx& aVersion, const Brx& aCode, const Brx& aDescription)
{
    TUint code = 0;
    if (aVersion != kRtspVersion) {
        THROW(HttpError);
    }
    if (aDescription.Bytes() > kMaxDescriptionBytes) {
        THROW(HttpError);
    }
    try {
        code = Ascii::Uint(aCode);
    }
    catch (AsciiError) {
        THROW(HttpError);
    }
    iStatus.Set(code, aDescription);
}


// HeaderRtspSession

TBool HeaderRtspSession::Received() const
{
    return iReceived;
}

const Brx& HeaderRtspSession::SessionId() const
{
    return iSessionId;
}

TBool HeaderRtspSession::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Brn("Session"));
}

TUint HeaderRtspSession::Timeout() const
{
    return iTimeout;
}

void HeaderRtspSession::Reset()
{
    iReceived = false;
    iTimeout = 60;
}

void HeaderRtspSession::Process(const Brx& aValue)
{
    if (aValue.Bytes() > kMaxSessionIdBytes) {
        THROW(HttpError);
    }
    Parser parser(aValue);
    iSessionId.ReplaceThrow(parser.Next(';'));
    iReceived = true;
    parser.Next('=');
    iTimeout = Ascii::Uint(parser.Remaining());
}


// ReaderRtp

ReaderRtp::ReaderRtp(IReader& aReader)
    : iReader(aReader)
{
}

ReaderRtp::MsgType ReaderRtp::ReadType()
{
    MsgType type = eRtspRequest;
    iChar.Replace(iReader.Read(1));
    if (iChar[0] == '$') {
        type = eRtp;
        iChar.SetBytes(0);
    }
    else if (iChar[0] == 'R') {
        type = eRtspResponse;
    }
    return type;
}

Brn ReaderRtp::Read(TUint aBytes)
{
    if (iChar.Bytes() > 0) {
        Brn buf(iChar);
        iChar.SetBytes(0);
        return buf;
    }
    return iReader.Read(aBytes);
}

void ReaderRtp::ReadFlush()
{
    iChar.SetBytes(0);
    iReader.ReadFlush();
}

void ReaderRtp::ReadInterrupt()
{
    iReader.ReadInterrupt();
}


// RtspClient

RtspClient::RtspClient(Environment& aEnv, IReader& aReader, IWriter& aWriter, const Brx& aGuid)
    : iWriterRequest(aWriter)
    , iReaderRtp(aReader)
    , iReaderUntil(iReaderRtp)
    , iReaderRequest(aEnv, iReaderUntil)
    , iReaderResponse(aEnv, iReaderUntil)
    , iSeq(1)
    , iGuid(aGuid)
{
    iReaderRequest.AddMethod(RtspMethod::kSetParameter);
    iReaderRequest.AddMethod(RtspMethod::kAnnounce);
    iReaderRequest.AddHeader(iHeaderContentLength);
    iReaderResponse.AddHeader(iHeaderContentLength);
    iReaderResponse.AddHeader(iHeaderRtspSession);
}
    
void RtspClient::Initialise(const Uri& aUri)
{
    iUri.Replace(Brn("rtsp://"));
    iUri.Append(aUri.Host());
    iUri.Append(aUri.Path());
    iUri.Append(aUri.Query());
    iUri.Append(aUri.Fragment());
    
    iSeq = 1; // reset sequence number

    LOG(kHttp, "RtspClient::Initialise ");
    LOG(kHttp, iUri);
    LOG(kHttp, "\n");
}

void RtspClient::WriteMethodDescribe()
{
    iWriterRequest.WriteMethod(RtspMethod::kDescribe, iUri);
}

void RtspClient::WriteMethodAnnounce()
{
    iWriterRequest.WriteMethod(RtspMethod::kAnnounce, iUri);
}

void RtspClient::WriteMethodGetParameter(const Brx& aUri)
{
    iWriterRequest.WriteMethod(RtspMethod::kGetParameter, aUri);
}

void RtspClient::WriteMethodOptions()
{
    iWriterRequest.WriteMethod(RtspMethod::kOptions, iUri);
}

void RtspClient::WriteMethodPause(const Brx& aUri)
{
    iWriterRequest.WriteMethod(RtspMethod::kPause, aUri);
}

void RtspClient::WriteMethodPlay(const Brx& aUri)
{
    iWriterRequest.WriteMethod(RtspMethod::kPlay, aUri);
}

void RtspClient::WriteMethodRecord(const Brx& aUri)
{
    iWriterRequest.WriteMethod(RtspMethod::kRecord, aUri);
}

void RtspClient::WriteMethodRedirect()
{
    iWriterRequest.WriteMethod(RtspMethod::kRedirect, iUri);
}

void RtspClient::WriteMethodSetup(const Brx& aUri)
{
    iWriterRequest.WriteMethod(RtspMethod::kSetup, aUri);
}

void RtspClient::WriteMethodSetParameter(const Brx& aUri)
{
    iWriterRequest.WriteMethod(RtspMethod::kSetParameter, aUri);
}

void RtspClient::WriteMethodFlush(const Brx& aUri)
{
    iWriterRequest.WriteMethod(RtspMethod::kFlush, aUri);
}

void RtspClient::WriteMethodTeardown(const Brx& aUri)
{
    iWriterRequest.WriteMethod(RtspMethod::kTeardown, aUri);
}

void RtspClient::WriteHeaderSeq()
{
    IWriterAscii& writer = iWriterRequest.WriteHeaderField(Brn("CSeq"));
    writer.WriteUint(iSeq++);
    writer.WriteFlush();
}

void RtspClient::WriteHeaderAccelerateStreaming(TUint aDuration, TUint aBandwidth)
{
    IWriterAscii& writer = iWriterRequest.WriteHeaderField(Brn("X-Accelerate-Streaming"));
    writer.Write(Brn("AccelDuration="));
    writer.WriteUint(aDuration);
    writer.Write(Brn(";AccelBandwidth="));
    writer.WriteUint(aBandwidth);
    writer.WriteFlush();
}

void RtspClient::WriteHeaderUserAgent()
{
    iWriterRequest.WriteHeader(RtspHeader::kUserAgent, iGuid);
}

void RtspClient::WriteHeaderAccept(const Brx& aValue)
{
    iWriterRequest.WriteHeader(RtspHeader::kAccept, aValue);
}

void RtspClient::WriteHeaderTransport(const Brx& aValue)
{
    iWriterRequest.WriteHeader(Brn("Transport"), aValue);
}

void RtspClient::WriteHeaderSupported(const Brx& aValue)
{
    iWriterRequest.WriteHeader(Brn("Supported"), aValue);
}

void RtspClient::WriteHeaderSession()
{
    iWriterRequest.WriteHeader(Brn("Session"), SessionId());
}

const Brx& RtspClient::SessionId() const
{
    return iHeaderRtspSession.SessionId();
}

TUint RtspClient::Timeout() const
{
    return iHeaderRtspSession.Timeout();
}

void RtspClient::WriteFlush()
{
    iWriterRequest.WriteFlush();
}

TUint RtspClient::Read()
{
    iReaderResponse.Read();
    return iReaderResponse.Status().Code();
}

void RtspClient::Flush()
{
    iReaderResponse.Flush();
}

void RtspClient::Interrupt()
{
    iReaderResponse.Interrupt();
}

Brn RtspClient::ReadRtsp(SdpInfo& aSdpInfo)
{
    for (;;) {
        const ReaderRtp::MsgType type = iReaderRtp.ReadType();
        if (type == ReaderRtp::eRtp) {
            return ReadRtp();
        }

        if (type == ReaderRtp::eRtspResponse) {
            iReaderResponse.Read(); // ignore responses during normal streaming, wait for Teardown response in teardown 'mode' - ToDo
        }
        else {
            try {
                iReaderRequest.Read();  // check for SET_PARAMETER & ANNOUNCE

                //if Content-Length found - read and decode this amount of data (in context)
                LOG(kHttp, "iReaderRequest.Method()");
                LOG(kHttp, iReaderRequest.Method());
                LOG(kHttp, "\n");
                LOG(kHttp, "iHeaderContentLength.Received() %d\n", iHeaderContentLength.Received());
                if(iHeaderContentLength.Received()) {
                    if(iReaderRequest.Method() == Brn(RtspMethod::kAnnounce)) {
                        LOG(kHttp, "ReadSdp()\n");
                        ReadSdp(aSdpInfo);
                        // may be able to continue without re-connecting - check! - ToDo
                    }
                    else {
                        LOG(kHttp, "probably set_parameter!\n");
                        //iReaderRequest.Read...(); //read/process extra info
                        return Brx::Empty();   // assume that we are at the end of playlist or file, so terminate
                    }
                }
            }
            catch(HttpError) {
                LOG(kHttp, "unexpected data\n");
                return Brx::Empty();   //terminate on unexpected data
            }
            catch(BufferOverflow) {
                LOG(kHttp, "data overflow\n");
                return Brx::Empty();   //terminate on unexpected data
            }
        }
    }
}

// RTSP/RTP frames consist of:
// Rtsp header:
//              1byte - magic number, 0x24
//              1byte - channel (id)
//              2bytes- frame length - 4 (i.e. excludes this header)
// RTP header:
//              1byte - flags
//              1byte - payload type
//              2bytes- sequence number
//              4bytes- timestamp
//              4bytes- source id
// Payload header:
//              2bytes- flags (eg 40,00)
//              2bytes- payload length (includes this header)

Brn RtspClient::ReadRtp()
{
    (void)iReaderUntil.Read(1); // channel
    ReaderBinary rb(iReaderUntil);
    TUint bytes = rb.ReadUintBe(2);
    (void)iReaderUntil.ReadProtocol(16);
    return iReaderUntil.ReadProtocol(bytes - 16);
}

void RtspClient::ReadSdp(ISdpHandler& aSdpHandler)
{
    aSdpHandler.Reset();
    Brn line;
    TUint remaining = iHeaderContentLength.ContentLength();
    while (remaining > 0) {
        line.Set(iReaderUntil.ReadUntil(Ascii::kLf));
        LOG(kHttp, "SDP: ");
        LOG(kHttp, line);
        LOG(kHttp, "\n");
        remaining -= line.Bytes() + 1;
        LOG(kHttp, "  remaining=%u\n", remaining);
        Parser parser(line);
        Brn type = parser.Next('=');
        Brn value = Ascii::Trim(parser.Remaining());
        if (type.Bytes() == 1) {
            aSdpHandler.Decode(type[0], value);
        }
    }
}


// SdpInfo

// Session description
//      v= (protocol version)
//      o= (owner/creator and session identifier)
//      s= (session name)
//      i=* (session information)
//      u=* (URI of description)
//      e=* (email address)
//      p=* (phone number)
//      c=* (connection information - not required if included in all media)
//      b=* (bandwidth information)

// One or more time descriptions (see below)

//      z=* (time zone adjustments)
//      k=* (encryption key)
//      a=* (zero or more session attribute lines)

// Zero or more media descriptions (see below)

// Time description
//      t= (time the session is active)
//      r=* (zero or more repeat times)

// Media description
//      m= (media name and transport address)
//      i=* (media title)
//      c=* (connection information - optional if included at session-level)
//      b=* (bandwidth information)
//      k=* (encryption key)
//      a=* (zero or more media attribute lines)

SdpInfo::SdpInfo()
{
}

const Brn kSdpInfoContentType("application/sdp");

const Brx& SdpInfo::ContentType() const
{
    return kSdpInfoContentType;
}
 
TUint SdpInfo::MediaCount() const
{
    return iMediaCount;
}
        
TUint SdpInfo::MediaAudioCount() const
{
    return iMediaAudioCount;
}
        
TUint SdpInfo::MediaVideoCount() const
{
    return iMediaVideoCount;
}
        
TUint SdpInfo::MediaApplicationCount() const
{
    return iMediaApplicationCount;
}
        
TUint SdpInfo::MediaDataCount() const
{
    return iMediaDataCount;
}        
        
TUint SdpInfo::MediaAudioPort() const
{
    return iMediaAudioPort;
}
     
const Brx& SdpInfo::MediaAudioTransport() const
{
    return iMediaAudioTransport;
}
        
const Brx& SdpInfo::MediaAudioFormat() const
{
    return iMediaAudioFormat;
}        

const Brx& SdpInfo::AudioPgmpu() const
{
    return iAudioPgmpu;
}

const Brx& SdpInfo::AudioControlUri() const
{
    return iAudioControlUri;
}

const Brx& SdpInfo::Fmtp() const
{
    return iFmtp;
}

const Brx& SdpInfo::Rsaaeskey() const
{
    return iRsaaeskey;
}

const Brx& SdpInfo::Aesiv() const
{
    return iAesiv;
}

TUint SdpInfo::AudioStream() const
{
    return iAudioStream;
}
        
const Brx& SdpInfo::SessionControlUri() const
{
    return iSessionControlUri;
}        
        
void SdpInfo::Reset()
{
    iCurrentMedia = ' ';
    iMediaCount = 0;
    iMediaAudioCount = 0;
    iMediaVideoCount = 0;
    iMediaApplicationCount = 0;
    iMediaDataCount = 0;
    iMediaAudioPort = 0;            
    iAudioPgmpu.Replace(Brx::Empty());
    iAudioControlUri.Replace(Brx::Empty());
    iAudioStream = 0;
    iSessionControlUri.Replace(Brx::Empty());
}
        
void SdpInfo::Decode(TByte aType, const Brx& aValue)
{
    switch (aType)
    {
    case 'a':
        DecodeA(aValue);
        break;
    case 'm':
        DecodeM(aValue);
        break;
    }
}

void SdpInfo::DecodeA(const Brx& aValue)
{
    Parser parser(aValue);
    Brn attribute = parser.Next(':');
    Brn remaining = parser.Remaining();
    if (attribute == Brn("pgmpu")) {
        DecodeAttributeAudioPgmpu(remaining);
    }
    // a=fmtp:96 4096 0 16 40 10 14 2 255 0 0 44100
    if (attribute == Brn("fmtp")) {
        DecodeAttributeFmtp(remaining);
    }
    if (attribute == Brn("rsaaeskey")) {
        DecodeAttributeRsaaeskey(remaining);
    }
    if (attribute == Brn("aesiv")) {
        DecodeAttributeAesiv(remaining);
    }
    if (iCurrentMedia == ' ') {
        if (attribute == Brn("control")) {
            DecodeAttributeSessionControl(remaining);
        }
    }
    if (FirstMediaAudio()) {
        if (attribute == Brn("control")) {
            DecodeAttributeAudioControl(remaining);
        }
        else if (attribute == Brn("stream")) {
            DecodeAttributeAudioStream(remaining);
        }
    }
}

void SdpInfo::DecodeAttributeAudioPgmpu(const Brx& aValue)
{
    Parser parser(aValue);
    if (parser.Next(',') != Brn("data:application/vnd.ms.wms-hdr.asfv1;base64")) {
        return;
    }
    Brn data = Ascii::Trim(parser.Remaining());
    iAudioPgmpu.Replace(data);
    Converter::FromBase64(iAudioPgmpu);
}

void SdpInfo::DecodeAttributeAudioControl(const Brx& aValue)
{
    iAudioControlUri.ReplaceThrow(aValue);
}

void SdpInfo::DecodeAttributeAudioStream(const Brx& aValue)
{
    try {
        iAudioStream = Ascii::Uint(aValue);
    }
    catch (AsciiError) {
    }
}

void SdpInfo::DecodeAttributeSessionControl(const Brx& aValue)
{
    iSessionControlUri.ReplaceThrow(aValue);
}

void SdpInfo::DecodeAttributeFmtp(const Brx& aValue)
{
    iFmtp.ReplaceThrow(aValue);
}

void SdpInfo::DecodeAttributeRsaaeskey(const Brx& aValue)
{
    Parser parser(aValue);
    Brn dataR = Ascii::Trim(parser.Remaining());
    Bwn dataW(dataR.Ptr(), dataR.Bytes());
    dataW.SetBytes(dataR.Bytes());
    Converter::FromBase64(dataW);
    iRsaaeskey.ReplaceThrow(dataW);
}

void SdpInfo::DecodeAttributeAesiv(const Brx& aValue)
{
    Parser parser(aValue);
    Brn dataR = Ascii::Trim(parser.Remaining());
    Bwn dataW(dataR.Ptr(), dataR.Bytes());
    dataW.SetBytes(dataR.Bytes());
    Converter::FromBase64(dataW);
    iAesiv.ReplaceThrow(dataW);
}

// m=<media> <port> <transport> <fmt list>

void SdpInfo::DecodeM(const Brx& aValue)
{
    iMediaCount++;
    iCurrentMedia = 'X'; // unknown

    Parser parser(aValue);
    Brn media = parser.Next();
    Brn port = parser.Next();
    Brn transport = parser.Next();
    Brn format = Ascii::Trim(parser.Remaining());
    if (media == Brn("audio")) {
        iCurrentMedia = 'A';
        iMediaAudioCount++;
        if (FirstMediaAudio()) {
            try {
                iMediaAudioPort = Ascii::Uint(port);
            }
            catch (AsciiError) {
                return;
            }

            iMediaAudioTransport.ReplaceThrow(transport);
            iMediaAudioFormat.ReplaceThrow(format);
        }
    }
    else if (media == Brn("video")) {
        iCurrentMedia = 'V';
        iMediaVideoCount++;
    }
    else if (media == Brn("application")) {
        iCurrentMedia = 'P';
        iMediaApplicationCount++;
    }
    else if (media == Brn("data")) {
        iCurrentMedia = 'D';
        iMediaDataCount++;
    }
}

TBool SdpInfo::FirstMediaAudio() const
{
    return (iCurrentMedia == 'A' && iMediaAudioCount == 1);
}
