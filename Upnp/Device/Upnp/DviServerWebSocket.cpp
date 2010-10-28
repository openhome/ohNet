#include <DviServerWebSocket.h>
#include <Network.h>
#include <Zapp.h>
#include <Stream.h>
#include <Http.h>
#include <Printer.h>
#include <Arch.h>
#include <md5.h>

using namespace Zapp;

// WebSocket

const Brn WebSocket::kHeaderProtocol("Sec-WebSocket-Protocol");
const Brn WebSocket::kHeaderOrigin("Origin");
const Brn WebSocket::kHeaderResponseOrigin("Sec-WebSocket-Origin");
const Brn WebSocket::kHeaderLocation("Sec-WebSocket-Location");
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
    iWriterChunked = new WriterHttpChunked(*this);
    iWriterBuffer = new Sws<kMaxResponseBytes>(*iWriterChunked);
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
    delete iWriterChunked;
    delete iReaderRequest;
    delete iReadBuffer;
}

void DviSessionWebSocket::Run()
{
    iErrorStatus = &HttpStatus::kOk;
    iReaderRequest->Flush();
    iWriterChunked->SetChunked(false);
    // check headers
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
        const Brx& method = iReaderRequest->Method();
        //iResponseStarted = false;
        //iResponseEnded = false;
        if (method == Http::kMethodGet) {
            Get();
        }
    }
    catch (HttpError&) {
        if (iReaderRequest->MethodNotAllowed()) {
            Error(HttpStatus::kMethodNotAllowed);
        }
    }
    catch (ReaderError&) {
        iErrorStatus = &HttpStatus::kBadRequest;
    }
    catch (WriterError&) {
    }
/*
    if (!iResponseStarted) {
        if (iErrorStatus == &HttpStatus::kOk) {
            iErrorStatus = &HttpStatus::kNotFound;
        }
        iWriterResponse->WriteStatus(*iErrorStatus, Http::eHttp11);
        Http::WriteHeaderConnectionClose(*iWriterResponse);
        iWriterResponse->WriteFlush();
    }
    else if (!iResponseEnded) {
        iWriterResponse->WriteFlush();
    }*/
}

void DviSessionWebSocket::Error(const HttpStatus& aStatus)
{
    iErrorStatus = &aStatus;
    THROW(HttpError);
}

void DviSessionWebSocket::Get()
{
    if (!iHeaderConnection.Upgrade() || iHeaderUpgrade.Upgrade() != WebSocket::kUpgradeWebSocket ||
        !iHeaderKey1.Received() || !iHeaderKey2.Received()) {
        Log::Print("Missing expected header\n");
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
    Log::Print("Processing connection: key1=%u, key2=%u, entity=", iHeaderKey1.Key(), iHeaderKey2.Key());
    Log::Print(entity);
    Log::Print("\n");

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
    Bws<Endpoint::kMaxEndpointBytes+6> location;
    location.Append("ws://");
    iEndpoint.GetEndpoint(location);
    location.Append('/');
    iWriterResponse->WriteHeader(WebSocket::kHeaderLocation, location);
    writer.WriteNewline();
    writer.Write(resp);
    iWriterResponse->WriteFlush();
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
