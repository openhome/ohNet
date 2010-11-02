#include <DviServerWebSocket.h>
#include <Network.h>
#include <Zapp.h>
#include <Stream.h>
#include <Http.h>
#include <Printer.h>
#include <Arch.h>
#include <md5.h>

using namespace Zapp;

#define WS_76_HANDSHAKE
#undef  WS_DRAFT03_READ
#undef  WS_DRAFT03_WRITE

// WebSocket

#ifdef WS_76_HANDSHAKE
const Brn WebSocket::kHeaderProtocol("Sec-WebSocket-Protocol");
const Brn WebSocket::kHeaderResponseOrigin("Sec-WebSocket-Origin");
const Brn WebSocket::kHeaderLocation("Sec-WebSocket-Location");
#else
const Brn WebSocket::kHeaderProtocol("WebSocket-Protocol");
const Brn WebSocket::kHeaderResponseOrigin("WebSocket-Origin");
const Brn WebSocket::kHeaderLocation("WebSocket-Location");
#endif
const Brn WebSocket::kHeaderOrigin("Origin");
const Brn WebSocket::kUpgradeWebSocket("WebSocket");


// HttpHeaderUpgrade

Brn HttpHeaderUpgrade::Upgrade() const
{
    return Received()? Brn(iUpgrade) : Brx::Empty();
}

TBool HttpHeaderUpgrade::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Http::kHeaderUpgrade);
}

void HttpHeaderUpgrade::Process(const Brx& aValue)
{
    SetReceived();
    iUpgrade.Set(aValue);
}


// WsHeaderKey

TUint WsHeaderKey::Key() const
{
    TUint64 num = 0;
    TUint spaces = 0;
    const TChar* ptr = (const TChar*)iKey.Ptr();
    const TUint bytes = iKey.Bytes();
    for (TUint i=0; i<bytes; i++) {
        TChar chr = ptr[i];
        if (Ascii::IsDigit(chr)) {
            num = (num*10) + Ascii::DecValue(chr);
        }
        else if (Ascii::IsWhitespace(chr)) {
            spaces++;
        }
    }
    if (spaces == 0) {
        THROW(WebSocketError); 
    }
    TUint key = (TUint)(num/spaces);
    return key;
}

WsHeaderKey::WsHeaderKey(const TChar* aHeader)
    : iHeader(aHeader)
{
}

TBool WsHeaderKey::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, iHeader);
}

void WsHeaderKey::Process(const Brx& aValue)
{
    SetReceived();
    iKey.Set(aValue);
}


// WsHeaderKey1

WsHeaderKey1::WsHeaderKey1()
    : WsHeaderKey("Sec-WebSocket-Key1")
{
}


// WsHeaderKey2

WsHeaderKey2::WsHeaderKey2()
    : WsHeaderKey("Sec-WebSocket-Key2")
{
}


// WsHeaderProtocol

const Brx& WsHeaderProtocol::Protocol() const
{
    return iProtocol;
}

TBool WsHeaderProtocol::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, WebSocket::kHeaderProtocol);
}

void WsHeaderProtocol::Process(const Brx& aValue)
{
    SetReceived();
    iProtocol.Set(aValue);
}


// WsHeaderOrigin

const Brx& WsHeaderOrigin::Origin() const
{
    return iOrigin;
}

TBool WsHeaderOrigin::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, WebSocket::kHeaderOrigin);
}

void WsHeaderOrigin::Process(const Brx& aValue)
{
    SetReceived();
    iOrigin.Set(aValue);
}


// DviSessionWebSocket

DviSessionWebSocket::DviSessionWebSocket(TIpAddress aInterface, TUint aPort)
    : iEndpoint(aPort, aInterface)
{
    iReadBuffer = new Srs<kMaxRequestBytes>(*this);
    iReaderRequest = new ReaderHttpRequest(*iReadBuffer);
    iWriterBuffer = new Sws<kMaxWriteBytes>(*this);
    iWriterResponse = new WriterHttpResponse(*iWriterBuffer);

    iReaderRequest->AddMethod(Http::kMethodGet);

    iReaderRequest->AddHeader(iHeaderHost);
    iReaderRequest->AddHeader(iHeaderConnection);
    iReaderRequest->AddHeader(iHeaderUpgrade);
    iReaderRequest->AddHeader(iHeaderKey1);
    iReaderRequest->AddHeader(iHeaderKey2);
    iReaderRequest->AddHeader(iHeaderProtocol);
    iReaderRequest->AddHeader(iHeaderOrigin);
}

DviSessionWebSocket::~DviSessionWebSocket()
{
    delete iWriterResponse;
    delete iWriterBuffer;
    delete iReaderRequest;
    delete iReadBuffer;
}

void DviSessionWebSocket::Run()
{
    LogVerbose(true);
    iErrorStatus = &HttpStatus::kOk;
    iReaderRequest->Flush();
    iExit = false;
    try {
        try {
            iReaderRequest->Read();
        }
        catch (HttpError&) {
            Error(HttpStatus::kBadRequest);
        }
        if (iReaderRequest->MethodNotAllowed()) {
            Error(HttpStatus::kMethodNotAllowed);
        }
        LogVerbose(true, true);
        Handshake();
        LogVerbose(true, true);
    }
    catch (HttpError&) {
        iErrorStatus = &HttpStatus::kBadRequest;
    }
    catch (ReaderError&) {
        iErrorStatus = &HttpStatus::kBadRequest;
    }
    catch (WebSocketError&) {
        iErrorStatus = &HttpStatus::kBadRequest;
    }
    catch (WriterError&) {
        iExit = true;
    }
    if (iErrorStatus != &HttpStatus::kOk) {
        try {
            iWriterResponse->WriteStatus(*iErrorStatus, Http::eHttp11);
            Http::WriteHeaderConnectionClose(*iWriterResponse);
            iWriterResponse->WriteFlush();
        }
        catch (WriterError&) {}
    }
    else {
        while (!iExit) {
            try {
                Read();
            }
            catch (ReaderError&) {}
            catch (WebSocketError&) {}
            catch (WriterError&) {}
            //Write(eClose, Brn(""));
            //iExit = true;
        }
    }
    Log::Print("< DviSessionWebSocket::Run\n");
}

void DviSessionWebSocket::Error(const HttpStatus& aStatus)
{
    iErrorStatus = &aStatus;
    THROW(HttpError);
}

#ifdef WS_76_HANDSHAKE
void DviSessionWebSocket::Handshake()
{
    // !!!! Add check for sub-protocol upnp-event being set
    if (!iHeaderConnection.Upgrade() || iHeaderUpgrade.Upgrade() != WebSocket::kUpgradeWebSocket ||
        !iHeaderKey1.Received() || !iHeaderKey2.Received()) {
        Log::Print("WS: Missing expected header\n");
        Error(HttpStatus::kBadRequest);
    }
    Bws<16> buf;
    TByte* ptr = const_cast<TByte*>(buf.Ptr());
    TUint key = Arch::BigEndian4(iHeaderKey1.Key());
    memcpy(ptr, &key, 4);
    ptr += 4;
    key = Arch::BigEndian4(iHeaderKey2.Key());
    memcpy(ptr, &key, 4);
    ptr += 4;
    Brn entity(iReadBuffer->Read(8));
    memcpy(ptr, entity.Ptr(), 8);
    buf.SetBytes(16);

    // calculate md5 response
    md5_state_t state;
    md5_byte_t digest[16];
	md5_init(&state);
	md5_append(&state, (const md5_byte_t*)buf.Ptr(), 16);
	md5_finish(&state, digest);
    Bws<16> resp;
    memcpy(const_cast<TByte*>(resp.Ptr()), &digest[0], 16);
    resp.SetBytes(16);

    // write response
    WriterAscii writer(*iWriterBuffer);
    writer.Write(Http::Version(Http::eHttp11));
    writer.WriteSpace();
    writer.WriteUint(HttpStatus::kSwitchingProtocols.Code());
    writer.WriteSpace();
    writer.Write(Brn("WebSocket Protocol Handshake"));
    writer.WriteNewline();
    iWriterResponse->WriteHeader(Brn("Upgrade"), Brn("WebSocket"));
    iWriterResponse->WriteHeader(Brn("Connection"), Brn("Upgrade"));
    if (iHeaderProtocol.Protocol().Bytes() > 0) {
        iWriterResponse->WriteHeader(Brn("WebSocket::kHeaderProtocol"), iHeaderProtocol.Protocol());
    }
    if (iHeaderOrigin.Origin().Bytes() > 0) {
        iWriterResponse->WriteHeader(WebSocket::kHeaderResponseOrigin, iHeaderOrigin.Origin());
    }
    Bws<1024> location;
    location.Append("ws://");
    iEndpoint.GetEndpoint(location);
    location.Append(iReaderRequest->Uri());
    iWriterResponse->WriteHeader(WebSocket::kHeaderLocation, location);
    writer.WriteNewline();
    writer.Write(resp);
    iWriterBuffer->WriteFlush(); /* don't use iWriterResponse as that'll append \r\n which will
                                    be treated as the (invalid) start of the first message we send */
}
#else
void DviSessionWebSocket::Handshake()
{
    Log::Print("WS: Handshake for ws75\n");
    // !!!! Add check for sub-protocol upnp-event being set
    if (!iHeaderConnection.Upgrade() || iHeaderUpgrade.Upgrade() != WebSocket::kUpgradeWebSocket) {
        Log::Print("WS: Missing expected header\n");
        Error(HttpStatus::kBadRequest);
    }

    // write response
    WriterAscii writer(*iWriterBuffer);
    writer.Write(Http::Version(Http::eHttp11));
    writer.WriteSpace();
    writer.WriteUint(HttpStatus::kSwitchingProtocols.Code());
    writer.WriteSpace();
    writer.Write(Brn("WebSocket Protocol Handshake"));
    writer.WriteNewline();
    iWriterResponse->WriteHeader(Brn("Upgrade"), Brn("WebSocket"));
    iWriterResponse->WriteHeader(Brn("Connection"), Brn("Upgrade"));
    if (iHeaderOrigin.Origin().Bytes() > 0) {
        Bwh origin(iHeaderOrigin.Origin());
        for (TUint i=0; i<origin.Bytes(); i++) {
            TChar chr = (TChar)origin[i];
            if (Ascii::IsUpperCase(chr)) {
                origin[i] = (TByte)Ascii::ToLowerCase(chr);
            }
        }
        iWriterResponse->WriteHeader(WebSocket::kHeaderResponseOrigin, origin);
    }
    Bws<Endpoint::kMaxEndpointBytes+6> location;
    location.Append("ws://");
    iEndpoint.GetEndpoint(location);
    location.Append('/');
    iWriterResponse->WriteHeader(WebSocket::kHeaderLocation, location);
    if (iHeaderProtocol.Protocol().Bytes() > 0) {
        iWriterResponse->WriteHeader(Brn("WebSocket::kHeaderProtocol"), iHeaderProtocol.Protocol());
    }
    iWriterBuffer->WriteFlush();
}
#endif // WS_76_HANDSHAKE
#ifdef WS_DRAFT03_READ
void DviSessionWebSocket::Read()
{
    static const TByte kBitMaskMore       = 1<<7;
    static const TByte kBitMaskRsv123     = 0x70;
    static const TByte kBitMaskOpcode     = 0xf;
    static const TByte kBitMaskRsv4       = 1<<7;
    static const TByte kBitMaskPayloadLen = 0x7f;
    // read data then validate the framing
    // most instances of unexpected content will result in us responing with BadRequest then waiting for further messages
    // unexpectedly large messages will cause us to close the socket
    Bws<2> ctrl;
    ctrl.Append(iReadBuffer->Read(2));
    Log::Print("Read control codes\n");

    // validate framing
    const TByte& byte1 = ctrl.At(0);
    const TByte& byte2 = ctrl.At(1);
    if (byte1 & kBitMaskMore) {
        Log::Print("WS: MORE bit set - fragmented packets not supported (but should be if you're seeing this error)\n");
        THROW(WebSocketError);
    }
    if ((byte1 & kBitMaskRsv123) || (byte2 & kBitMaskRsv4)) {
        Log::Print("WS: RSV bit(s) set - %u, %u - but no extension negotiated\n", (byte1 & kBitMaskRsv123) >> 4, byte2 & kBitMaskRsv4);
        THROW(WebSocketError);
    }
    WsOpcode opcode = (WsOpcode)(byte1 & kBitMaskOpcode);
    Log::Print("opcode = %u\n", opcode);
    if (opcode == 0) THROW(WebSocketError);

    TUint32 payloadLen = byte2 & kBitMaskPayloadLen;
    Log::Print("payloadLen=%u\n", payloadLen);
    if (payloadLen == 0x7f) {
        Brn extendedLen = iReadBuffer->Read(8);
        TUint64 len;
        memcpy(&len, extendedLen.Ptr(), 8);
        payloadLen = (TUint32)Arch::BigEndian8(len);
    }
    else if (payloadLen == 0x7e) {
        Brn extendedLen = iReadBuffer->Read(2);
        TUint16 len;
        memcpy(&len, extendedLen.Ptr(), 2);
        payloadLen = Arch::BigEndian2(len);
    }
    if (payloadLen > kMaxRequestBytes) {
        // larger message than we expect to handle - close the socket
        iExit = true;
        THROW(WebSocketError);
    }
    Log::Print("payloadLen=%u\n", payloadLen);
    Brn data = iReadBuffer->Read(payloadLen);
    Log::Print("Read data\n");

    switch (opcode)
    {
    case eContinuation:
        Log::Print("WS: Continuation opcode not yet supported\n");
        break;
    case eClose:
        // !!!! check that this isn't a reply to a close we initiated
        Write(eClose, data);
        iExit = true;
        break;
    case ePing:
        Write(ePong, data);
        break;
    case ePong:
        Log::Print("WS: Pong - ");
        Log::Print(data);
        Log::Print("\n");
        break;
    case eText:
        Log::Print("WS: eText\n");
        // subscribe, renew, unsubscribe
        break;
    case eBinary:
        Log::Print("WS: Binary opcode not supported\n");
        break;
    default:
        Log::Print("WS: Unexpected reserved opcode %u received\n", opcode);
        break;
    }
}
#else // !WS_DRAFT03_READ
void DviSessionWebSocket::Read()
{
    static const TByte kMsgTerminator = 0xff;
    Brn data = iReadBuffer->ReadUntil(kMsgTerminator);
    if (data[0] != 0) {
        Log::Print("WS: Unexpected leading byte - %u\n", data[0]);
        THROW(WebSocketError);
    }
    data.Set(data.Split(1, data.Bytes()-1));
    Log::Print("WS: Received data - ");
    Log::Print(data);
    Log::Print("\n");
    Write(eText, Brn("hi from server 1"));
    Write(eText, Brn("hi from server 2"));
    Write(eText, Brn("hi from server 3"));
    Write(eText, Brn("hi from server 4"));
    Write(eText, Brn("hi from server 5"));
    Close();
}
#endif // WS_DRAFT03_READ

#ifdef WS_DRAFT03_WRITE
void DviSessionWebSocket::Write(WsOpcode aOpcode, const Brx& aData)
{
    iWriterBuffer->Write((TByte)aOpcode);
    const TUint dataLen = aData.Bytes();
    if (dataLen < 126) {
        iWriterBuffer->Write((TByte)dataLen);
    }
    else if (dataLen > (1<<16)) {
        iWriterBuffer->Write((TByte)0x7e);
        TUint16 len = (TUint16)dataLen;
        len = Arch::BigEndian2(len);
        Bws<2> lenBuf;
        (void)memcpy((TByte*)lenBuf.Ptr(), &len, 2);
        lenBuf.SetBytes(2);
        iWriterBuffer->Write(lenBuf);
    }
    else {
        iWriterBuffer->Write((TByte)0x7f);
        TUint64 len = dataLen;
        len = Arch::BigEndian8(len);
        Bws<8> lenBuf;
        (void)memcpy((TByte*)lenBuf.Ptr(), &len, 8);
        lenBuf.SetBytes(8);
        iWriterBuffer->Write(lenBuf);
    }
    iWriterBuffer->Write(aData);
    iWriterBuffer->WriteFlush();
}
#else // !WS_DRAFT03_WRITE
void DviSessionWebSocket::Write(WsOpcode /*aOpcode*/, const Brx& aData)
{
    static const TByte kWriteBufStart = (TByte)'\0';
    static const TByte kWriteBufEnd = (TByte)'\xff';
    iWriterBuffer->Write(kWriteBufStart);
    iWriterBuffer->Write(aData);
    iWriterBuffer->Write(kWriteBufEnd);
    iWriterBuffer->WriteFlush();
}
#endif // WS_DRAFT03_WRITE

void DviSessionWebSocket::Close()
{
    static const TByte kFrameClose = (TByte)'\xff';
    iWriterBuffer->Write(kFrameClose);
    iWriterBuffer->WriteFlush();
    iExit = true;
}

IPropertyWriter* DviSessionWebSocket::CreateWriter(const Endpoint& /*aSubscriber*/, const Brx& /*aSubscriberPath*/,
                                                   const Brx& /*aSid*/, TUint /*aSequenceNumber*/)
{
    return NULL;
}

    
// DviServerWebSocket

DviServerWebSocket::DviServerWebSocket()
{
    Initialise();
}

SocketTcpServer* DviServerWebSocket::CreateServer(const NetworkInterface& aNif)
{
    SocketTcpServer* server = new SocketTcpServer("WSSV", 54321, aNif.Address());
    server->Add("DSES", new DviSessionWebSocket(aNif.Address(), server->Port()));
    return server;
}
