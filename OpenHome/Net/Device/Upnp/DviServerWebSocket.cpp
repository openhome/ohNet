#include <OpenHome/Net/Private/DviServerWebSocket.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/md5.h>
#include <OpenHome/Net/Private/XmlParser.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/sha.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Parser.h>

#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Net;

static void WriteTag(IWriter& aWriter, const Brx& aTag, const Brx& aValue)
{
    aWriter.Write('<');
    aWriter.Write(aTag);
    aWriter.Write('>');
    aWriter.Write(aValue);
    aWriter.Write('<');
    aWriter.Write('/');
    aWriter.Write(aTag);
    aWriter.Write('>');
}


// WebSocket

const Brn WebSocket::kHeaderProtocol("Sec-WebSocket-Protocol");
const Brn WebSocket::kHeaderResponseOrigin("Sec-WebSocket-Origin");
const Brn WebSocket::kHeaderLocation("Sec-WebSocket-Location");
const Brn WebSocket::kHeaderKey("Sec-WebSocket-Key");
const Brn WebSocket::kHeaderVersion("Sec-WebSocket-Version");
const Brn WebSocket::kHeaderOrigin("Origin");
const Brn WebSocket::kUpgradeWebSocket("WebSocket");
const Brn WebSocket::kTagRoot("ROOT");
const Brn WebSocket::kTagMethod("METHOD");
const Brn WebSocket::kTagUdn("UDN");
const Brn WebSocket::kTagService("SERVICE");
const Brn WebSocket::kTagSid("SID");
const Brn WebSocket::kTagNt("NT");
const Brn WebSocket::kTagTimeout("TIMEOUT");
const Brn WebSocket::kTagNts("NTS");
const Brn WebSocket::kTagSubscription("SUBSCRIPTION");
const Brn WebSocket::kTagSeq("SEQ");
const Brn WebSocket::kTagClientId("CLIENTID");
const Brn WebSocket::kMethodSubscribe("Subscribe");
const Brn WebSocket::kMethodUnsubscribe("Unsubscribe");
const Brn WebSocket::kMethodRenew("Renew");
const Brn WebSocket::kMethodSubscriptionSid("SubscribeCompleted");
const Brn WebSocket::kMethodSubscriptionRenewed("RenewCompleted");
const Brn WebSocket::kMethodGetPropertyUpdates("GetPropertyUpdates");
const Brn WebSocket::kMethodPropertyUpdate("PropertyUpdate");
const Brn WebSocket::kValueProtocol("upnpevent.openhome.org");
const Brn WebSocket::kValueNt("upnp:event");
const Brn WebSocket::kValuePropChange("upnp:propchange");


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


// WsHeaderKey80

const Brx& WsHeaderKey80::Key() const
{
    return iKey;
}

TBool WsHeaderKey80::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, WebSocket::kHeaderKey);
}

void WsHeaderKey80::Process(const Brx& aValue)
{
    SetReceived();
    Brn suffix("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
    Brn val = Ascii::Trim(aValue);
    Bwh buf(val.Bytes() + suffix.Bytes() + 1);
    buf.Append(val);
    buf.Append(suffix);
    buf.PtrZ();
    buf.TransferTo(iKey);
}


// WsHeaderVersion

TUint WsHeaderVersion::Version() const
{
    return iVersion;
}

TBool WsHeaderVersion::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, WebSocket::kHeaderVersion);
}

void WsHeaderVersion::Process(const Brx& aValue)
{
    SetReceived();
    iVersion = Ascii::Uint(aValue);
}


// PropertyWriterWs

PropertyWriterWs* PropertyWriterWs::Create(DviSessionWebSocket& aSession, const Brx& aSid, TUint aSequenceNumber)
{ // static
    PropertyWriterWs* self = new PropertyWriterWs(aSession);
    try {
        self->WriteHeaders(aSid, aSequenceNumber);
    }
    catch (WriterError&) {
        delete self;
        throw;
    }
    return self;
}

PropertyWriterWs::PropertyWriterWs(DviSessionWebSocket& aSession)
    : iSession(aSession)
    , iWriter(kWriteBufGranularity)
{
    SetWriter(iWriter);
}

PropertyWriterWs::~PropertyWriterWs()
{
}

void PropertyWriterWs::WriteHeaders(const Brx& aSid, TUint aSequenceNumber)
{
    iWriter.Write(Brn("<?xml version=\"1.0\"?>"));
    iWriter.Write(Brn("<root>"));
    iWriter.Write('<');
    iWriter.Write(WebSocket::kTagSubscription);
    iWriter.Write('>');
    WriteTag(iWriter, WebSocket::kTagMethod, WebSocket::kMethodPropertyUpdate);
    WriteTag(iWriter, WebSocket::kTagNt, WebSocket::kValueNt);
    WriteTag(iWriter, WebSocket::kTagNts, WebSocket::kValuePropChange);
    WriteTag(iWriter, WebSocket::kTagSid, aSid);
    Bws<Ascii::kMaxUintStringBytes> seq;
    (void)Ascii::AppendDec(seq, aSequenceNumber);
    WriteTag(iWriter, WebSocket::kTagSeq, seq);
    iWriter.Write(Brn("<e:propertyset xmlns:e=\"urn:schemas-upnp-org:event-1-0\">"));
}

void PropertyWriterWs::PropertyWriteEnd()
{
    iWriter.Write(Brn("</e:propertyset>"));
    iWriter.Write('<');
    iWriter.Write('/');
    iWriter.Write(WebSocket::kTagSubscription);
    iWriter.Write('>');
    iWriter.Write(Brn("</root>"));
    Brh* buf = new Brh;
    iWriter.TransferTo(*buf);
    iSession.QueuePropertyUpdate(buf);
}


// WsProtocol

WsProtocol::~WsProtocol()
{
}

WsProtocol::WsProtocol(ReaderUntil& aReaderUntil, Swx& aWriteBuffer)
    : iReaderUntil(aReaderUntil)
    , iWriteBuffer(aWriteBuffer)
{
}


// WsProtocol76

WsProtocol76::WsProtocol76(ReaderUntil& aReaderUntil, Swx& aWriteBuffer)
    : WsProtocol(aReaderUntil, aWriteBuffer)
{
}

void WsProtocol76::Read(Brn& aData, TBool& aClosed)
{
    aData.Set(NULL, 0);
    aClosed = false;

    Brn data = iReaderUntil.ReadUntil(kMsgEnd);
    if (data.Bytes() == 1 && data[0] == kFrameCloseStart) {
        Brn msg = iReaderUntil.Read(1);
        if (msg[0] != kMsgCloseEnd) {
            THROW(WebSocketError);
        }
        LOG(kDvWebSocket, "WS: Received close cmd from browser\n");
        Close();
        aClosed = true;
        return;
    }
    if (data[0] != kFrameMsgStart) {
        LOG2(kDvWebSocket, kError, "WS: Unexpected leading byte - %u\n", data[0]);
        THROW(WebSocketError);
    }
    aData.Set(data.Split(1, data.Bytes()-1));
}

void WsProtocol76::Write(const Brx& aData)
{
    iWriteBuffer.Write(kFrameMsgStart);
    iWriteBuffer.Write(aData);
    iWriteBuffer.Write(kMsgEnd);
    iWriteBuffer.WriteFlush();
}

void WsProtocol76::Close()
{
    try {
        iWriteBuffer.Write(kFrameCloseStart);
        iWriteBuffer.Write(kMsgCloseEnd);
        iWriteBuffer.WriteFlush();
    }
    catch (WriterError&) {}
}


// WsProtocol80

WsProtocol80::WsProtocol80(ReaderUntil& aReaderUntil, Swx& aWriteBuffer)
    : WsProtocol(aReaderUntil, aWriteBuffer)
    , iReaderProtocol(aReaderUntil)
{
}

void WsProtocol80::Read(Brn& aData, TBool& aClosed)
{
    aData.Set(NULL, 0);
    aClosed = false;

    static const TByte kBitMaskFinalFragment = 1<<7;
    static const TByte kBitMaskRsv123        = 0x70;
    static const TByte kBitMaskOpcode        = 0xf;
    static const TByte kBitMaskPayloadMask   = 1<<7;
    static const TByte kBitMaskPayloadLen    = 0x7f;

    // validate framing
    Bws<2> ctrl;
    ctrl.Append(iReaderProtocol.Read(2));
    const TByte& byte0 = ctrl.At(0);
    const TByte& byte1 = ctrl.At(1);
    const TBool fragment = ((byte0 & kBitMaskFinalFragment) == 0);
    if (byte0 & kBitMaskRsv123) {
        LOG2(kDvWebSocket, kError, "WS: RSV bit(s) set - %u - but no extension negotiated\n", (byte0 & kBitMaskRsv123) >> 4);
        Close(kCloseProtocolError);
        aClosed = true;
        return;
    }
    if ((byte1 & kBitMaskPayloadMask) == 0) {
        LOG2(kDvWebSocket, kError, "WS: mask bit not set\n");
        Close(kCloseProtocolError);
        aClosed = true;
        return;
    }
    WsOpcode opcode = (WsOpcode)(byte0 & kBitMaskOpcode);
    switch (opcode)
    {
    case eContinuation:
        // test for already having stored some data from a previous text (non-final) message??
        break;
    case eText:
        break;
    case eClose:
        aClosed = true;
        return;
    case ePing:
    case ePong:
        if (fragment) {
            Close(kCloseProtocolError);
            aClosed = true;
            return;
        }
        break;
    case eBinary:
        LOG2(kDvWebSocket, kError, "WS: received unexpected binary data\n");
        Close(kCloseUnsupportedData);
        aClosed = true;
        return;
    default:
        LOG2(kDvWebSocket, kError, "WS: Unexpected reserved opcode %u received\n", opcode);
        Close(kCloseProtocolError);
        aClosed = true;
        return;
    }

    // calculate payload length
    TUint32 payloadLen = byte1 & kBitMaskPayloadLen;
    if (payloadLen == 0x7f) {
        ReaderBinary rb(iReaderUntil);
        payloadLen = (TUint32)rb.ReadUint64Be(8);
    }
    else if (payloadLen == 0x7e) {
        ReaderBinary rb(iReaderUntil);
        payloadLen = rb.ReadUintBe(2);
    }
    if (payloadLen > DviSessionWebSocket::kMaxRequestBytes) {
        // larger message than we expect to handle - close the socket
        Close(kCloseMsgTooLong);
        aClosed = true;
        return;
    }

    // read/decode payload
    // decoding is in-place since we'll have no future use for the original data after decoding it
    Bws<4> mask;
    mask.Append(iReaderProtocol.Read(4));
    Brn maskedData = iReaderProtocol.Read(payloadLen);
    Bwn data(maskedData.Ptr(), maskedData.Bytes());
    for (TUint i=0; i<maskedData.Bytes(); i++) {
        data.Append((TByte)(maskedData[i] ^ mask[i%4]));
    }

    // now, finally, process the message
    switch (opcode)
    {
    case eText:
        iMessage.SetBytes(0);
        // fallthrough
    case eContinuation:
        if (iMessage.Bytes() > 0 || fragment) {
            iMessage.Grow(iMessage.Bytes() + data.Bytes());
            iMessage.Append(data);
        }
        if (!fragment) {
            if (iMessage.Bytes() > 0) {
                aData.Set(iMessage);
            }
            else {
                aData.Set(data);
            }
        }
        break;
    case ePing:
        Write(ePong, data);
        break;
    case ePong:
        LOG(kDvWebSocket, "WS: Pong - %.*s\n", PBUF(data));
        break;
    default:
        // should have filtered out all other cases in the earlier switch
        ASSERTS();
        break;
    }
}

void WsProtocol80::Write(const Brx& aData)
{
    Write(eText, aData);
}

void WsProtocol80::Close()
{
    Close(kCloseNormal);
}

void WsProtocol80::Write(WsOpcode aOpcode, const Brx& aData)
{
    TByte b = 0x80 | (TByte)aOpcode;
    iWriteBuffer.Write(b);
    const TUint dataLen = aData.Bytes();
    if (dataLen < 126) {
        iWriteBuffer.Write((TByte)dataLen);
    }
    else if (dataLen < (1<<16)) {
        iWriteBuffer.Write((TByte)0x7e);
        TUint16 len = (TUint16)dataLen;
        len = Arch::BigEndian2(len);
        Bws<2> lenBuf;
        (void)memcpy((TByte*)lenBuf.Ptr(), &len, 2);
        lenBuf.SetBytes(2);
        iWriteBuffer.Write(lenBuf);
    }
    else {
        iWriteBuffer.Write((TByte)0x7f);
        TUint64 len = dataLen;
        len = Arch::BigEndian8(len);
        Bws<8> lenBuf;
        (void)memcpy((TByte*)lenBuf.Ptr(), &len, 8);
        lenBuf.SetBytes(8);
        iWriteBuffer.Write(lenBuf);
    }
    iWriteBuffer.Write(aData);
    iWriteBuffer.WriteFlush();
}

void WsProtocol80::Close(TUint16 aCode)
{
    TUint16 reason = Arch::BigEndian2(aCode);
    Brn data((const TByte*)&reason, 2);
    try {
        Write(eClose, data);
    }
    catch (WriterError&) {}
}


// DviSessionWebSocket

DviSessionWebSocket::DviSessionWebSocket(DvStack& aDvStack, TIpAddress aInterface, TUint aPort)
    : iDvStack(aDvStack)
    , iEndpoint(aPort, aInterface)
    , iExit(false)
    , iInterruptLock("WSIM")
    , iShutdownSem("WSIS", 1)
    , iPropertyUpdates(kMaxPropertyUpdates)
{
    iReadBuffer = new Srs<1024>(*this);
    iReaderUntil = new ReaderUntilS<kMaxRequestBytes>(*iReadBuffer);
    iReaderRequest = new ReaderHttpRequest(iDvStack.Env(), *iReaderUntil);
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
    iReaderRequest->AddHeader(iHeadverKeyV8);
    iReaderRequest->AddHeader(iHeaderVersion);
    iReaderRequest->AddHeader(iHeaderContentLength);
}

DviSessionWebSocket::~DviSessionWebSocket()
{
    iExit = true;
    Interrupt(true);
    iShutdownSem.Wait();
    delete iWriterResponse;
    delete iWriterBuffer;
    delete iReaderRequest;
    delete iReaderUntil;
    delete iReadBuffer;
}

void DviSessionWebSocket::QueuePropertyUpdate(Brh* aUpdate)
{
    iInterruptLock.Wait();
    iPropertyUpdates.Write(aUpdate);
    Interrupt(true);
    iInterruptLock.Signal();
}

void DviSessionWebSocket::Run()
{
    iShutdownSem.Wait();
    iErrorStatus = &HttpStatus::kOk;
    iReaderRequest->Flush();
    iExit = false;
    try {
        try {
            iReaderRequest->Read(kReadTimeoutMs);
        }
        catch (HttpError&) {
            Error(HttpStatus::kBadRequest);
        }
        if (iReaderRequest->MethodNotAllowed()) {
            Error(HttpStatus::kMethodNotAllowed);
        }
        Handshake();
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
                WritePropertyUpdates();
                LOG(kDvWebSocket, "WS: Wait for next request (or interrupt)\n");
                DoRead();
            }
            catch (ReaderError&) {
                if (iPropertyUpdates.SlotsUsed() == 0) {
                    LOG2(kDvWebSocket, kError, "WS: Exception - ReaderError\n");
                    iProtocol->Close();
                    iExit = true;
                }
            }
            catch (WebSocketError&) {
                LOG2(kDvWebSocket, kError, "WS: Exception - WebSocketError\n");
                iProtocol->Close();
                iExit = true;
            }
            catch (WriterError&) {
                LOG2(kDvWebSocket, kError, "WS: Exception - WriterError\n");
                iExit = true;
            }
            catch (XmlError&) {
                LOG2(kDvWebSocket, kError, "WS: Exception - XmlError\n");
                iProtocol->Close();
                iExit = true;
            }
        }
        delete iProtocol;
        iProtocol = NULL;
        while (iPropertyUpdates.SlotsUsed() > 0) {
            delete iPropertyUpdates.Read();
        }
        Map::iterator it = iMap.begin();
        while (it != iMap.end()) {
            delete it->second;
            it++;
        }
        iMap.clear();
    }
    iShutdownSem.Signal();
}

void DviSessionWebSocket::Error(const HttpStatus& aStatus)
{
    iErrorStatus = &aStatus;
    THROW(HttpError);
}

void DviSessionWebSocket::Handshake()
{
    if (iHeaderKey1.Received()) {
        iProtocol = Handshake76();
    }
    else if (iHeadverKeyV8.Received()) {
        iProtocol = Handshake80();
    }
    else {
        LOG2(kDvWebSocket, kError, "WS: Handshake not recognised\n");
        Error(HttpStatus::kBadRequest);
    }
}

WsProtocol* DviSessionWebSocket::Handshake76()
{
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
    iWriterResponse->WriteHeader(WebSocket::kHeaderProtocol, WebSocket::kValueProtocol);
    if (iHeaderOrigin.Origin().Bytes() > 0) {
        iWriterResponse->WriteHeader(WebSocket::kHeaderResponseOrigin, iHeaderOrigin.Origin());
    }
    Bws<1024> location;
    location.Append("ws://");
    location.Append(iHeaderHost.Host());
    location.Append(iReaderRequest->Uri());
    iWriterResponse->WriteHeader(WebSocket::kHeaderLocation, location);
    writer.WriteNewline();
    writer.WriteFlush();

    if (!iHeaderConnection.Upgrade() || iHeaderUpgrade.Upgrade() != WebSocket::kUpgradeWebSocket ||
        !iHeaderKey1.Received() || !iHeaderKey2.Received() ||
        !iHeaderProtocol.Received() || iHeaderProtocol.Protocol() != WebSocket::kValueProtocol) {
        LOG2(kDvWebSocket, kError, "WS: Handshake missing expected header\n");
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

    writer.Write(resp);
    iWriterBuffer->WriteFlush(); /* don't use iWriterResponse as that'll append \r\n which will
                                    be treated as the (invalid) start of the first message we send */

    return new WsProtocol76(*iReaderUntil, *iWriterBuffer);
}

WsProtocol* DviSessionWebSocket::Handshake80()
{
    if (!iHeaderConnection.Upgrade()) {
        LOG2(kDvWebSocket, kError, "WS: Handshake missing expected header - \"Connection: Upgrade\"\n");
        Error(HttpStatus::kBadRequest);
    }
    if (!iHeaderUpgrade.Received()) {
        LOG2(kDvWebSocket, kError, "WS: Handshake missing expected header - \"Upgrade:\"\n");
        Error(HttpStatus::kBadRequest);
    }
    if (iHeaderUpgrade.Upgrade() != Brn("websocket")) {
        const Brx& header = iHeaderUpgrade.Upgrade();
        LOG2(kDvWebSocket, kError, "WS: unexpected content of upgrade header - %.*s\n", PBUF(header));
        Error(HttpStatus::kBadRequest);
    }
    if (!iHeaderProtocol.Received()) {
        LOG2(kDvWebSocket, kError, "WS: Handshake missing expected header - \"Sec-WebSocket-Protocol:\"\n");
        Error(HttpStatus::kBadRequest);
    }
    if (iHeaderProtocol.Protocol() != WebSocket::kValueProtocol) {
        const Brx& header = iHeaderProtocol.Protocol();
        LOG2(kDvWebSocket, kError, "WS: unexpected content of Sec-WebSocket-Protocol header - %.*s\n", PBUF(header));
        Error(HttpStatus::kBadRequest);
    }
    if (!iHeadverKeyV8.Received()) {
        LOG2(kDvWebSocket, kError, "WS: Handshake missing expected header - \"Sec-WebSocket-Version:\"\n");
        Error(HttpStatus::kBadRequest);
    }
    if (iHeaderVersion.Version() < 8 || iHeaderVersion.Version() > 13) {
        LOG2(kDvWebSocket, kError, "WS: unexpected content of Sec-WebSocket-Version header - %u\n", iHeaderVersion.Version());
        Error(HttpStatus::kBadRequest);
    }

    // write response
    iWriterResponse->WriteStatus(HttpStatus::kSwitchingProtocols, Http::eHttp11);
    iWriterResponse->WriteHeader(Brn("Upgrade"), Brn("websocket"));
    iWriterResponse->WriteHeader(Brn("Connection"), Brn("Upgrade"));
    SHA1Context* sha1ctx = (SHA1Context*)malloc(sizeof(*sha1ctx));
    (void)SHA1Reset(sha1ctx);
    const Brx& key = iHeadverKeyV8.Key();
    (void)SHA1Input(sha1ctx, key.Ptr(), key.Bytes());
    uint8_t digest[SHA1HashSize];
    (void)SHA1Result(sha1ctx, digest);
    free(sha1ctx);
    IWriterAscii& stream = iWriterResponse->WriteHeaderField(Brn("Sec-WebSocket-Accept"));
    Brn digestBuf(&digest[0], SHA1HashSize);
    Converter::ToBase64(stream, digestBuf);
    stream.WriteFlush();
    stream = iWriterResponse->WriteHeaderField(Brn("Sec-WebSocket-Protocol"));
    stream.Write(iHeaderProtocol.Protocol());
    stream.WriteFlush();
    iWriterResponse->WriteFlush();

    return new WsProtocol80(*iReaderUntil, *iWriterBuffer);
}

void DviSessionWebSocket::DoRead()
{
    Brn data;
    TBool closed;
    iProtocol->Read(data, closed);
    if (closed) {
        iExit = true;
        return;
    }
    if (data.Bytes() > 0) {
        AutoMutex a(iInterruptLock);
        Interrupt(false);

        Brn doc = XmlParserBasic::Find(WebSocket::kTagRoot, data);
        Brn method = XmlParserBasic::Find(WebSocket::kTagMethod, doc);
        if (method == WebSocket::kMethodSubscribe) {
            Subscribe(data);
        }
        else if (method == WebSocket::kMethodUnsubscribe) {
            Unsubscribe(data);
        }
        else if (method == WebSocket::kMethodRenew) {
            Renew(data);
        }
        else {
            THROW(WebSocketError);
        }
    }
}

void DviSessionWebSocket::Subscribe(const Brx& aRequest)
{
    LOG(kDvWebSocket, "WS: Subscribe\n");
    Brn udn = XmlParserBasic::Find(WebSocket::kTagUdn, aRequest);
    Brn serviceId = XmlParserBasic::Find(WebSocket::kTagService, aRequest);
    Brn nt = XmlParserBasic::Find(WebSocket::kTagNt, aRequest);
    if (nt != WebSocket::kValueNt) {
        THROW(WebSocketError);
    }
    TUint timeout;
    try {
        timeout = Ascii::Uint(XmlParserBasic::Find(WebSocket::kTagTimeout, aRequest));
    }
    catch (AsciiError&) {
        THROW(XmlError);
    }
    timeout += 10;

    DviDevice* device = iDvStack.DeviceMap().Find(udn);
    if (device == NULL) {
        THROW(WebSocketError);
    }
    DviService* service = NULL;
    const TUint serviceCount = device->ServiceCount();
    for (TUint i=0; i<serviceCount; i++) {
        DviService* s = &device->Service(i);
        if (s->ServiceType().PathUpnp() == serviceId) {
            service = s;
            break;
        }
    }
    if (service == NULL) {
        THROW(WebSocketError);
    }
    Brh sid;
    device->CreateSid(sid);
    DviSubscription* subscription = new DviSubscription(iDvStack, *device, *this, NULL, sid);
    subscription->SetDuration(timeout);
    Brn sidBuf(subscription->Sid());

    try {
        WriteSubscriptionSid(udn, serviceId, sidBuf, timeout);
    }
    catch (WriterError&) {
        subscription->RemoveRef();
        THROW(WriterError);
    }

    // Start subscription, prompting delivery of the first update (covering all state variables)
    iDvStack.SubscriptionManager().AddSubscription(*subscription);
    DviSessionWebSocket::SubscriptionWrapper* wrapper = new DviSessionWebSocket::SubscriptionWrapper(*subscription, sidBuf, *service);
    service->AddSubscription(subscription);
    Brn key(wrapper->Sid());
    iMap.insert(std::pair<Brn,DviSessionWebSocket::SubscriptionWrapper*>(key, wrapper));
}

void DviSessionWebSocket::Unsubscribe(const Brx& aRequest)
{
    LOG(kDvWebSocket, "WS: Unsubscribe\n");
    Brn sid = XmlParserBasic::Find(WebSocket::kTagSid, aRequest);
    Map::iterator it = iMap.find(sid);
    if (it != iMap.end()) {
        delete it->second;
        iMap.erase(it);
    }
}

void DviSessionWebSocket::Renew(const Brx& aRequest)
{
    LOG(kDvWebSocket, "WS: Renew\n");
    Brn sid = XmlParserBasic::Find(WebSocket::kTagSid, aRequest);
    Map::iterator it = iMap.find(sid);
    if (it == iMap.end()) {
        LOG2(kDvWebSocket, kError, "Attempt to renew an unknown subscription - %.*s\n", PBUF(sid));
        THROW(WebSocketError);
    }
    TUint timeout;
    try {
        timeout = Ascii::Uint(XmlParserBasic::Find(WebSocket::kTagTimeout, aRequest));
    }
    catch (AsciiError&) {
        THROW(XmlError);
    }
    DviSessionWebSocket::SubscriptionWrapper* wrapper = it->second;
    try {
        wrapper->Subscription().Renew(timeout);
    }
    catch (DvSubscriptionError&) {
        LOG2(kDvWebSocket, kError, "Attempt made to renew an expired subscription - %.*s\n", PBUF(sid));
        THROW(WebSocketError);
    }
    WriteSubscriptionRenewed(wrapper->Sid(), timeout);
}

void DviSessionWebSocket::WriteSubscriptionSid(const Brx& aDevice, const Brx& aService, const Brx& aSid, TUint aSeconds)
{
    WriterBwh writer(1024);
    writer.Write(Brn("<?xml version=\"1.0\"?>"));
    writer.Write(Brn("<root>"));
    WriteTag(writer, WebSocket::kTagMethod, WebSocket::kMethodSubscriptionSid);
    WriteTag(writer, WebSocket::kTagUdn, aDevice);
    WriteTag(writer, WebSocket::kTagService, aService);
    WriteTag(writer, WebSocket::kTagSid, aSid);
    Bws<Ascii::kMaxUintStringBytes> timeout;
    (void)Ascii::AppendDec(timeout, aSeconds);
    WriteTag(writer, WebSocket::kTagTimeout, timeout);
    writer.Write(Brn("</root>"));
    Brh resp;
    writer.TransferTo(resp);
    iProtocol->Write(resp);
}

void DviSessionWebSocket::WriteSubscriptionRenewed(const Brx& aSid, TUint aSeconds)
{
    WriterBwh writer(1024);
    writer.Write(Brn("<?xml version=\"1.0\"?>"));
    writer.Write(Brn("<root>"));
    WriteTag(writer, WebSocket::kTagMethod, WebSocket::kMethodSubscriptionRenewed);
    WriteTag(writer, WebSocket::kTagSid, aSid);
    Bws<Ascii::kMaxUintStringBytes> timeout;
    (void)Ascii::AppendDec(timeout, aSeconds);
    WriteTag(writer, WebSocket::kTagTimeout, timeout);
    writer.Write(Brn("</root>"));
    Brh resp;
    writer.TransferTo(resp);
    iProtocol->Write(resp);
}

void DviSessionWebSocket::WritePropertyUpdates()
{
    AutoMutex a(iInterruptLock);
    Interrupt(false);
    while (iPropertyUpdates.SlotsUsed() > 0) {
        LOG(kDvWebSocket, "WS: Write property update\n");
        Brh* msg = iPropertyUpdates.Read();
        iProtocol->Write(*msg);
        delete msg;
    }
}

IPropertyWriter* DviSessionWebSocket::ClaimWriter(const IDviSubscriptionUserData* /*aUserData*/, const Brx& aSid, TUint aSequenceNumber)
{
    return PropertyWriterWs::Create(*this, aSid, aSequenceNumber);
}

void DviSessionWebSocket::ReleaseWriter(IPropertyWriter* aWriter)
{
    delete aWriter;
}

void DviSessionWebSocket::NotifySubscriptionCreated(const Brx& /*aSid*/)
{
}

void DviSessionWebSocket::NotifySubscriptionDeleted(const Brx& /*aSid*/)
{
}

void DviSessionWebSocket::NotifySubscriptionExpired(const Brx& /*aSid*/)
{
}


// DviSessionWebSocket::SubscriptionWrapper

DviSessionWebSocket::SubscriptionWrapper::SubscriptionWrapper(DviSubscription& aSubscription, const Brx& aSid, DviService& aService)
    : iSubscription(aSubscription)
    , iSid(aSid)
    , iService(aService)
{
    iSubscription.AddRef();
    iService.AddRef();
}

DviSessionWebSocket::SubscriptionWrapper::~SubscriptionWrapper()
{
    iService.RemoveSubscription(iSubscription.Sid());
    iService.RemoveRef();
    iSubscription.RemoveRef();
}


// DviServerWebSocket

DviServerWebSocket::DviServerWebSocket(DvStack& aDvStack)
    : DviServer(aDvStack)
{
    if (iDvStack.Env().InitParams()->DvNumWebSocketThreads() > 0) {
        Initialise();
    }
}

SocketTcpServer* DviServerWebSocket::CreateServer(const NetworkAdapter& aNif)
{
    SocketTcpServer* server = new SocketTcpServer(iDvStack.Env(), "WsServer", iDvStack.Env().InitParams()->DvWebSocketPort(), aNif.Address());
    const TUint numWsThreads = iDvStack.Env().InitParams()->DvNumWebSocketThreads();
    for (TUint i=0; i<numWsThreads; i++) {
        Bws<Thread::kMaxNameBytes+1> thName;
        thName.AppendPrintf("WsSession %d", i);
        thName.PtrZ();
        server->Add((const TChar*)thName.Ptr(), new DviSessionWebSocket(iDvStack, aNif.Address(), server->Port()));
    }
    return server;
}
