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
const Brn WebSocket::kMethodGetPropertyUpdates("GetPropertyUpdates");
const Brn WebSocket::kMethodSubscriptionTimeout("SubscriptionTimeout");
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


// SubscriptionDataWs

SubscriptionDataWs::SubscriptionDataWs(const Brx& aSubscriberSid)
    : iSubscriberSid(aSubscriberSid)
{
}

const Brx& SubscriptionDataWs::SubscriberSid() const
{
    return iSubscriberSid;
}

const void* SubscriptionDataWs::Data() const
{
    return this;
}

void SubscriptionDataWs::Release()
{
    delete this;
}


// PropertyWriterWs

PropertyWriterWs::PropertyWriterWs(DviSessionWebSocket& aSession, const Brx& aSid, TUint aSequenceNumber)
    : iSession(aSession)
    , iWriter(kWriteBufGranularity)
{
    SetWriter(iWriter);
    iWriter.Write(Brn("<?xml version=\"1.0\"?>"));
    iWriter.Write(Brn("<root>"));
    WriteTag(iWriter, WebSocket::kTagMethod, WebSocket::kMethodPropertyUpdate);
    WriteTag(iWriter, WebSocket::kTagNt, WebSocket::kValueNt);
    WriteTag(iWriter, WebSocket::kTagNts, WebSocket::kValuePropChange);
    WriteTag(iWriter, WebSocket::kTagSid, aSid);
    Bws<Ascii::kMaxUintStringBytes> seq;
    (void)Ascii::AppendDec(seq, aSequenceNumber);
    WriteTag(iWriter, WebSocket::kTagSeq, seq);
    iWriter.Write(Brn("<e:propertyset xmlns:e=\"urn:schemas-upnp-org:event-1-0\">"));
}

PropertyWriterWs::~PropertyWriterWs()
{
}

void PropertyWriterWs::PropertyWriteEnd()
{
    iWriter.Write(Brn("</e:propertyset></root>"));
    Brh* buf = new Brh;
    iWriter.TransferTo(*buf);
    iSession.QueuePropertyUpdate(buf);
}


// WsProtocol

WsProtocol::WsProtocol(Srx& aReadBuffer, Swx& aWriteBuffer)
    : iReadBuffer(aReadBuffer)
    , iWriteBuffer(aWriteBuffer)
{
}


// WsProtocol76

WsProtocol76::WsProtocol76(Srx& aReadBuffer, Swx& aWriteBuffer)
    : WsProtocol(aReadBuffer, aWriteBuffer)
{
}

void WsProtocol76::Read(Brn& aData, TBool& aClosed)
{
    aData.Set(NULL, 0);
    aClosed = false;

    Brn data = iReadBuffer.ReadUntil(kMsgEnd);
    if (data.Bytes() == 1 && data[0] == kFrameCloseStart) {
        Brn msg = iReadBuffer.Read(1);
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

WsProtocol80::WsProtocol80(Srx& aReadBuffer, Swx& aWriteBuffer)
    : WsProtocol(aReadBuffer, aWriteBuffer)
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
    ctrl.Append(iReadBuffer.Read(2));
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
        Brn extendedLen = iReadBuffer.Read(8);
        TUint64 len;
        memcpy(&len, extendedLen.Ptr(), 8);
        payloadLen = (TUint32)Arch::BigEndian8(len);
    }
    else if (payloadLen == 0x7e) {
        Brn extendedLen = iReadBuffer.Read(2);
        TUint16 len;
        (void)memcpy(&len, extendedLen.Ptr(), 2);
        payloadLen = Arch::BigEndian2(len);
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
    mask.Append(iReadBuffer.Read(4));
    Brn maskedData = iReadBuffer.Read(payloadLen);
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
        LOG(kDvWebSocket, "WS: Pong - ");
        LOG(kDvWebSocket, data);
        LOG(kDvWebSocket, "\n");
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
    else if (dataLen > (1<<16)) {
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

DviSessionWebSocket::DviSessionWebSocket(TIpAddress aInterface, TUint aPort)
    : iEndpoint(aPort, aInterface)
    , iInterruptLock("WSIM")
    , iShutdownSem("WSIS", 1)
    , iPropertyUpdates(kMaxPropertyUpdates)
    , iPropertyUpdateCollection(DviStack::PropertyUpdateCollection())
    , iLongPollSem("DVLP", 0)
    , iExit(false)
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
    iReaderRequest->AddHeader(iHeadverKeyV8);
    iReaderRequest->AddHeader(iHeaderVersion);
    iReaderRequest->AddHeader(iHeaderContentLength);
}

DviSessionWebSocket::~DviSessionWebSocket()
{
    iExit = true;
    Interrupt(true);
    iLongPollSem.Signal();
    iShutdownSem.Wait();
    delete iWriterResponse;
    delete iWriterBuffer;
    delete iReaderRequest;
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
        const Brx& method = iReaderRequest->Method();
        if (method == Http::kMethodGet) {
            Handshake();
        }
        else if (method == Http::kMethodPost) {
            LongPollRequest();
            return;
        }
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
                Read();
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

    return new WsProtocol76(*iReadBuffer, *iWriterBuffer);
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
        LOG2(kDvWebSocket, kError, "WS: unexpected content of upgrade header - ");
        LOG2(kDvWebSocket, kError, iHeaderUpgrade.Upgrade());
        LOG2(kDvWebSocket, kError, "\n");
        Error(HttpStatus::kBadRequest);
    }
    if (!iHeaderProtocol.Received()) {
        LOG2(kDvWebSocket, kError, "WS: Handshake missing expected header - \"Sec-WebSocket-Protocol:\"\n");
        Error(HttpStatus::kBadRequest);
    }
    if (iHeaderProtocol.Protocol() != WebSocket::kValueProtocol) {
        LOG2(kDvWebSocket, kError, "WS: unexpected content of Sec-WebSocket-Protocol header - \n");
        LOG2(kDvWebSocket, kError, iHeaderProtocol.Protocol());
        LOG2(kDvWebSocket, kError, "\n");
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

    return new WsProtocol80(*iReadBuffer, *iWriterBuffer);
}

void DviSessionWebSocket::Read()
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
    Brn sid = XmlParserBasic::Find(WebSocket::kTagSid, aRequest);
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

    DviDevice* device = DviStack::DeviceMap().Find(udn);
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
    Brh sid2;
    device->CreateSid(sid2);
    SubscriptionDataWs* data = new SubscriptionDataWs(sid);
    DviSubscription* subscription = new DviSubscription(*device, *this, data, sid2, timeout);

    try {
        WriteSubscriptionTimeout(sid, timeout);
    }
    catch (WriterError&) {
        subscription->RemoveRef();
        THROW(WriterError);
    }

    // Start subscription, prompting delivery of the first update (covering all state variables)
    DviSubscriptionManager::AddSubscription(*subscription);
    DviSessionWebSocket::SubscriptionWrapper* wrapper = new DviSessionWebSocket::SubscriptionWrapper(*subscription, sid, *service);
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
        LOG2(kDvWebSocket, kError, "Attempt to renew an unknown subscription - ");
        LOG2(kDvWebSocket, kError, sid);
        LOG2(kDvWebSocket, kError, "\n");
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
    if (wrapper->Subscription().HasExpired()) {
        LOG2(kDvWebSocket, kError, "Attempt made to renew an expired subscription - ");
        LOG2(kDvWebSocket, kError, sid);
        LOG2(kDvWebSocket, kError, "\n");
        THROW(WebSocketError);
    }
    wrapper->Subscription().Renew(timeout);
    WriteSubscriptionTimeout(wrapper->Sid(), timeout);
}

void DviSessionWebSocket::WriteSubscriptionTimeout(const Brx& aSid, TUint aSeconds)
{
    WriterBwh writer(1024);
    writer.Write(Brn("<?xml version=\"1.0\"?>"));
    writer.Write(Brn("<root>"));
    WriteTag(writer, WebSocket::kTagMethod, WebSocket::kMethodSubscriptionTimeout);
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

IPropertyWriter* DviSessionWebSocket::CreateWriter(const IDviSubscriptionUserData* aUserData, const Brx& /*aSid*/, TUint aSequenceNumber)
{
    const SubscriptionDataWs* data = reinterpret_cast<const SubscriptionDataWs*>(aUserData->Data());
    return new PropertyWriterWs(*this, data->SubscriberSid(), aSequenceNumber);
}

void DviSessionWebSocket::NotifySubscriptionDeleted(const Brx& /*aSid*/)
{
}

void DviSessionWebSocket::NotifySubscriptionExpired(const Brx& /*aSid*/)
{
}

void DviSessionWebSocket::LongPollRequest()
{
    try {
        DoLongPollRequest();
    }
    catch (HttpError&) { }
    catch (WriterError&) { }
    catch (ReaderError&) { }
    catch (XmlError&) { }
    catch (InvalidSid&) { }
    catch (InvalidClientId&) { }
    try {
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
        }
    }
    catch (WriterError&) { }
}

void DviSessionWebSocket::DoLongPollRequest()
{
    Parser parser(iReaderRequest->Uri());
    Brn requestUri = parser.Next('/');
    Brn entity(iReadBuffer->Read(iHeaderContentLength.ContentLength()));
    if (requestUri == WebSocket::kMethodSubscribe) {
        LongPollSubscribe(entity);
    }
    else if (requestUri == WebSocket::kMethodUnsubscribe) {
        LongPollUnsubscribe(entity);
    }
    else if (requestUri == WebSocket::kMethodRenew) {
        LongPollRenew(entity);
    }
    else if (requestUri == WebSocket::kMethodGetPropertyUpdates) {
        LongPollGetPropertyUpdates(entity);
    }
    else {
        Error(HttpStatus::kBadRequest);
    }
}

void DviSessionWebSocket::LongPollSubscribe(const Brx& aRequest)
{
    LOG(kDvWebSocket, "WS: LongPollSubscribe\n");
    Brn clientId = XmlParserBasic::Find(WebSocket::kTagClientId, aRequest);
    Brn udn = XmlParserBasic::Find(WebSocket::kTagUdn, aRequest);
    Brn serviceId = XmlParserBasic::Find(WebSocket::kTagService, aRequest);
    Brn nt = XmlParserBasic::Find(WebSocket::kTagNt, aRequest);
    if (nt != WebSocket::kValueNt) {
        Error(HttpStatus::kBadRequest);
    }
    TUint timeout = 0;
    try {
        timeout = Ascii::Uint(XmlParserBasic::Find(WebSocket::kTagTimeout, aRequest));
    }
    catch (AsciiError&) {
        Error(HttpStatus::kBadRequest);
    }
    static const TUint kTimeoutLongPollSecs = 5 * 60; // set a short timeout as we won't be notified when clients vanish
    if (timeout > kTimeoutLongPollSecs) {
        timeout = kTimeoutLongPollSecs;
    }

    DviDevice* device = DviStack::DeviceMap().Find(udn);
    if (device == NULL) {
        Error(HttpStatus::kBadRequest);
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
        Error(HttpStatus::kBadRequest);
    }
    Brh sid;
    device->CreateSid(sid);
    DviSubscription* subscription = new DviSubscription(*device, iPropertyUpdateCollection, NULL, sid, timeout);

    try {
        WriterBwh writer(1024);
        writer.Write(Brn("<?xml version=\"1.0\"?>"));
        writer.Write(Brn("<root>"));
        WriteTag(writer, WebSocket::kTagMethod, WebSocket::kMethodSubscriptionTimeout);
        WriteTag(writer, WebSocket::kTagUdn, udn);
        WriteTag(writer, WebSocket::kTagService, serviceId);
        WriteTag(writer, WebSocket::kTagSid, sid);
        Bws<Ascii::kMaxUintStringBytes> timeoutBuf;
        (void)Ascii::AppendDec(timeoutBuf, timeout);
        WriteTag(writer, WebSocket::kTagTimeout, timeoutBuf);
        writer.Write(Brn("</root>"));
        Brh response;
        writer.TransferTo(response);

        LongPollWriteResponse(response);
    }
    catch (WriterError&) {
        subscription->RemoveRef();
        THROW(WriterError);
    }

    // Start subscription, prompting delivery of the first update (covering all state variables)
    iPropertyUpdateCollection.AddSubscription(clientId, subscription);
    DviSubscriptionManager::AddSubscription(*subscription);
    service->AddSubscription(subscription);
}

void DviSessionWebSocket::LongPollUnsubscribe(const Brx& aRequest)
{
    LOG(kDvWebSocket, "WS: LongPollUnsubscribe\n");
    Brn sid = XmlParserBasic::Find(WebSocket::kTagSid, aRequest);
    iPropertyUpdateCollection.RemoveSubscription(sid);

    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eHttp11);
    iResponseStarted = iResponseEnded = true;
    iWriterResponse->WriteFlush();
}

void DviSessionWebSocket::LongPollRenew(const Brx& aRequest)
{
    LOG(kDvWebSocket, "WS: LongPollRenew\n");
    Brn sid = XmlParserBasic::Find(WebSocket::kTagSid, aRequest);
    TUint timeout;
    try {
        timeout = Ascii::Uint(XmlParserBasic::Find(WebSocket::kTagTimeout, aRequest));
    }
    catch (AsciiError&) {
        THROW(XmlError);
    }
    DviSubscription* subscription = DviSubscriptionManager::Find(sid);
    if (subscription == NULL) {
        Error(HttpStatus::kBadRequest);
    }
    subscription->Renew(timeout);

    WriterBwh writer(1024);
    writer.Write(Brn("<?xml version=\"1.0\"?>"));
    writer.Write(Brn("<root>"));
    WriteTag(writer, WebSocket::kTagMethod, WebSocket::kMethodSubscriptionTimeout);
    WriteTag(writer, WebSocket::kTagSid, sid);
    Bws<Ascii::kMaxUintStringBytes> timeoutBuf;
    (void)Ascii::AppendDec(timeoutBuf, timeout);
    WriteTag(writer, WebSocket::kTagTimeout, timeoutBuf);
    writer.Write(Brn("</root>"));
    Brh response;
    writer.TransferTo(response);

    LongPollWriteResponse(response);
}

void DviSessionWebSocket::LongPollGetPropertyUpdates(const Brx& aRequest)
{
    LOG(kDvWebSocket, "WS: LongPollGetPropertyUpdates\n");
    Brn clientId = XmlParserBasic::Find(WebSocket::kTagClientId, aRequest);
    try {
        iPropertyUpdateCollection.SetClientSignal(clientId, &iLongPollSem);
        iLongPollSem.Wait(30*1000);
        iPropertyUpdateCollection.SetClientSignal(clientId, NULL);
        if (!iExit) {
            WriterBwh writer(1024);
            iPropertyUpdateCollection.WriteUpdates(clientId, writer);
            Brh response;
            writer.TransferTo(response);
            LongPollWriteResponse(response);
        }
    }
    catch (Timeout&) {
        iPropertyUpdateCollection.SetClientSignal(clientId, NULL);
    }
}

void DviSessionWebSocket::LongPollWriteResponse(const Brx& aResponse)
{
    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eHttp11);
    iResponseStarted = true;
    Http::WriteHeaderContentLength(*iWriterResponse, aResponse.Bytes());
    Http::WriteHeaderConnectionClose(*iWriterResponse);
    iWriterResponse->Write(Brn("\r\n"));
    iWriterResponse->Write(aResponse);
    iResponseEnded = true;
    iWriterResponse->WriteFlush();
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


// PropertyUpdate

PropertyUpdate::Property::Property(const Brx& aName, const Brx& aValue)
    : iName(aName)
    , iValue(aValue)
{
}

PropertyUpdate::Property::Property(const Brx& aName, WriterBwh& aValue)
    : iName(aName)
{
    aValue.TransferTo(iValue);
}

const Brx& PropertyUpdate::Property::Name() const
{
    return iName;
}

const Brx& PropertyUpdate::Property::Value() const
{
    return iValue;
}

void PropertyUpdate::Property::TransferValueTo(Property& aDest)
{
    iValue.TransferTo(aDest.iValue);
}

PropertyUpdate::PropertyUpdate(const Brx& aSid, TUint aSeqNum)
    : iSid(aSid)
    , iSeqNum(aSeqNum)
{
}

PropertyUpdate::~PropertyUpdate()
{
    for (TUint i=0; i<(TUint)iProperties.size(); i++) {
        delete iProperties[i];
    }
}

void PropertyUpdate::Add(const Brx& aName, const Brx& aValue)
{
    iProperties.push_back(new Property(aName, aValue));
}

void PropertyUpdate::Add(const Brx& aName, WriterBwh& aValue)
{
    iProperties.push_back(new Property(aName, aValue));
}

const Brx& PropertyUpdate::Sid() const
{
    return iSid;
}

TUint PropertyUpdate::SeqNum() const
{
    return iSeqNum;
}

void PropertyUpdate::Merge(PropertyUpdate& aPropertyUpdate)
{
    ASSERT(iSid == aPropertyUpdate.Sid());
    ASSERT(iSeqNum < aPropertyUpdate.SeqNum());
    iSeqNum = aPropertyUpdate.SeqNum();
    for (TUint i=(TUint)aPropertyUpdate.iProperties.size() - 1; i >= 0; i--) {
        TBool found = false;
        Property* prop = aPropertyUpdate.iProperties[i];
        for (TUint j=0; j<iProperties.size(); j++) {
            if (iProperties[j]->Name() == prop->Name()) {
                prop->TransferValueTo(*(iProperties[j]));
                found = true;
                break;
            }
        }
        if (!found) {
            iProperties.push_back(prop);
            aPropertyUpdate.iProperties.erase(aPropertyUpdate.iProperties.begin() + i);
        }
    }
}

void PropertyUpdate::Write(IWriter& aWriter)
{
    WriteTag(aWriter, WebSocket::kTagMethod, WebSocket::kMethodPropertyUpdate);
    WriteTag(aWriter, WebSocket::kTagNt, WebSocket::kValueNt);
    WriteTag(aWriter, WebSocket::kTagNts, WebSocket::kValuePropChange);
    WriteTag(aWriter, WebSocket::kTagSid, iSid);
    Bws<Ascii::kMaxUintStringBytes> seq;
    (void)Ascii::AppendDec(seq, iSeqNum);
    WriteTag(aWriter, WebSocket::kTagSeq, seq);
    aWriter.Write(Brn("<e:propertyset xmlns:e=\"urn:schemas-upnp-org:event-1-0\">"));
    for (TUint i=0; i<(TUint)iProperties.size(); i++) {
        WriteTag(aWriter, iProperties[i]->Name(), iProperties[i]->Value());
    }
    aWriter.Write(Brn("</e:propertyset></root>"));
    aWriter.Write('<');
    aWriter.Write(WebSocket::kTagSubscription);
    aWriter.Write('/');
    aWriter.Write('>');
}


// PropertyWriterPolled

PropertyWriterPolled::PropertyWriterPolled(IPolledUpdateMerger& aMerger, const Brx& aSid, TUint aSeqNum)
    : iMerger(aMerger)
{
    iPropertyUpdate = new PropertyUpdate(aSid, aSeqNum);
}

PropertyWriterPolled::~PropertyWriterPolled()
{
    delete iPropertyUpdate;
}

void PropertyWriterPolled::PropertyWriteString(const Brx& aName, const Brx& aValue)
{
    WriterBwh writer(1024);
    Converter::ToXmlEscaped(writer, aValue);
    iPropertyUpdate->Add(aName, writer);
}

void PropertyWriterPolled::PropertyWriteInt(const Brx& aName, TInt aValue)
{
    Bws<Ascii::kMaxIntStringBytes> buf;
    (void)Ascii::AppendDec(buf, aValue);
    iPropertyUpdate->Add(aName, buf);
}

void PropertyWriterPolled::PropertyWriteUint(const Brx& aName, TUint aValue)
{
    Bws<Ascii::kMaxUintStringBytes> buf;
    (void)Ascii::AppendDec(buf, aValue);
    iPropertyUpdate->Add(aName, buf);
}

void PropertyWriterPolled::PropertyWriteBool(const Brx& aName, TBool aValue)
{
    PropertyWriteUint(aName, (aValue? 1 : 0));
}

void PropertyWriterPolled::PropertyWriteBinary(const Brx& aName, const Brx& aValue)
{
    WriterBwh writer(1024);
    Converter::ToBase64(writer, aValue);
    iPropertyUpdate->Add(aName, writer);
}

void PropertyWriterPolled::PropertyWriteEnd()
{
    iPropertyUpdate = iMerger.MergeUpdate(iPropertyUpdate);
}

   
// PropertyUpdatesFlattened

PropertyUpdatesFlattened::PropertyUpdatesFlattened(const Brx& aClientId)
    : iClientId(aClientId)
{
}

PropertyUpdatesFlattened::~PropertyUpdatesFlattened()
{
    UpdatesMap::iterator it = iUpdatesMap.begin();
    while (it != iUpdatesMap.end()) {
        delete it->second;
        it++;
    }
    SubscriptionMap::iterator it2 = iSubscriptionMap.begin();
    while (it2 != iSubscriptionMap.end()) {
        it2->second->RemoveRef();
        it2++;
    }
}

const Brx& PropertyUpdatesFlattened::ClientId() const
{
    return iClientId;
}

void PropertyUpdatesFlattened::AddSubscription(DviSubscription* aSubscription)
{
    Brn buf(aSubscription->Sid());
    iSubscriptionMap.insert(std::pair<Brn,DviSubscription*>(buf, aSubscription));
}

void PropertyUpdatesFlattened::RemoveSubscription(const Brx& aSid)
{
    Brn sid(aSid);
    SubscriptionMap::iterator it = iSubscriptionMap.find(sid);
    if (it != iSubscriptionMap.end()) {
        it->second->RemoveRef();
        iSubscriptionMap.erase(it);
    }
    // remove any pending updates for this subscription too
    UpdatesMap::iterator it2 = iUpdatesMap.find(sid);
    if (it2 != iUpdatesMap.end()) {
        delete it2->second;
        iUpdatesMap.erase(it2);
    }
}

TBool PropertyUpdatesFlattened::ContainsSubscription(const Brx& aSid) const
{
    Brn sid(aSid);
    return (iSubscriptionMap.find(sid) != iSubscriptionMap.end());
}

TBool PropertyUpdatesFlattened::IsEmpty() const
{
    return (iSubscriptionMap.size() == 0);
}

PropertyUpdate* PropertyUpdatesFlattened::MergeUpdate(PropertyUpdate* aUpdate)
{
    PropertyUpdate* ret = aUpdate;
    Brn sid(aUpdate->Sid());
    UpdatesMap::iterator it = iUpdatesMap.find(sid);
    if (it == iUpdatesMap.end()) {
        iUpdatesMap.insert(std::pair<Brn,PropertyUpdate*>(sid, aUpdate));
        ret = NULL;
    }
    else {
        it->second->Merge(*aUpdate);
    }
    if (iSem != NULL) {
        iSem->Signal();
        iSem = NULL;
    }
    return ret;
}

void PropertyUpdatesFlattened::SetClientSignal(Semaphore* aSem)
{
    iSem = aSem;
    if (aSem != NULL && iSubscriptionMap.size() > 0) {
        aSem->Signal();
        aSem = NULL;
    }
}

void PropertyUpdatesFlattened::WriteUpdates(IWriter& aWriter)
{
    aWriter.Write(Brn("<root>"));
    UpdatesMap::iterator it = iUpdatesMap.begin();
    while (it != iUpdatesMap.end()) {
        aWriter.Write('<');
        aWriter.Write(WebSocket::kTagSubscription);
        aWriter.Write('>');
        it->second->Write(aWriter);
        aWriter.Write('<');
        aWriter.Write(WebSocket::kTagSubscription);
        aWriter.Write('/');
        aWriter.Write('>');
        delete it->second;
        it++;
    }
    iUpdatesMap.clear();
    aWriter.Write(Brn("</root>"));
}


// DviPropertyUpdateCollection

DviPropertyUpdateCollection::DviPropertyUpdateCollection()
    : iLock("MPUC")
{
}

DviPropertyUpdateCollection::~DviPropertyUpdateCollection()
{
    // we rely on DviPropertyUpdateCollection being deleted after DviSubscriptionManager
    // ...this means we can assume that all subscriptions have already been deleted
    // ...so we can destroy our remaining objects without worrying about publisher threads being in the process of writing updates
    for (TUint i=0; i<(TUint)iUpdates.size(); i++) {
        delete iUpdates[i];
    }
}

void DviPropertyUpdateCollection::AddSubscription(const Brx& aClientId, DviSubscription* aSubscription)
{
    AutoMutex a(iLock);
    PropertyUpdatesFlattened* updates = FindByClientId(aClientId);
    if (updates == NULL) {
        updates = new PropertyUpdatesFlattened(aClientId);
        iUpdates.push_back(updates);
    }
    updates->AddSubscription(aSubscription);
}

void DviPropertyUpdateCollection::RemoveSubscription(const Brx& aSid)
{
    AutoMutex a(iLock);
    TUint index;
    PropertyUpdatesFlattened* updates = FindBySid(aSid, index);
    if (updates == NULL) {
        THROW(InvalidSid);
    }
    updates->RemoveSubscription(aSid);
    if (updates->IsEmpty()) {
        delete updates;
        iUpdates.erase(iUpdates.begin() + index);
    }
}

void DviPropertyUpdateCollection::SetClientSignal(const Brx& aClientId, Semaphore* aSem)
{
    AutoMutex a(iLock);
    PropertyUpdatesFlattened* updates = FindByClientId(aClientId);
    if (updates == NULL) {
        THROW(InvalidClientId);
    }
    updates->SetClientSignal(aSem);
}

void DviPropertyUpdateCollection::WriteUpdates(const Brx& aClientId, IWriter& aWriter)
{
    AutoMutex a(iLock);
    PropertyUpdatesFlattened* updates = FindByClientId(aClientId);
    if (updates == NULL) {
        THROW(InvalidClientId);
    }
    updates->WriteUpdates(aWriter);
}

PropertyUpdatesFlattened* DviPropertyUpdateCollection::FindByClientId(const Brx& aClientId)
{
    TUint ignore;
    return FindByClientId(aClientId, ignore);
}

PropertyUpdatesFlattened* DviPropertyUpdateCollection::FindByClientId(const Brx& aClientId, TUint& aIndex)
{
    // assumes called with iLock held
    for (TUint i=0; i<(TUint)iUpdates.size(); i++) {
        PropertyUpdatesFlattened* updates = iUpdates[i];
        if (updates->ClientId() == aClientId) {
            aIndex = i;
            return updates;
        }
    }
    aIndex = 0xffffffff;
    return NULL;
}

PropertyUpdatesFlattened* DviPropertyUpdateCollection::FindBySid(const Brx& aSid)
{
    TUint ignore;
    return FindBySid(aSid, ignore);
}

PropertyUpdatesFlattened* DviPropertyUpdateCollection::FindBySid(const Brx& aSid, TUint& aIndex)
{
    // assumes called with iLock held
    for (TUint i=0; i<(TUint)iUpdates.size(); i++) {
        PropertyUpdatesFlattened* updates = iUpdates[i];
        if (updates->ContainsSubscription(aSid)) {
            aIndex = i;
            return updates;
        }
    }
    aIndex = 0xffffffff;
    return NULL;
}

IPropertyWriter* DviPropertyUpdateCollection::CreateWriter(const IDviSubscriptionUserData* /*aUserData*/, const Brx& aSid, TUint aSequenceNumber)
{
    AutoMutex a(iLock);
    if (FindBySid(aSid) != NULL) {
        return new PropertyWriterPolled(*this, aSid, aSequenceNumber);
    }
    return NULL;
}

void DviPropertyUpdateCollection::NotifySubscriptionDeleted(const Brx& /*aSid*/)
{
}

void DviPropertyUpdateCollection::NotifySubscriptionExpired(const Brx& aSid)
{
    try {
        RemoveSubscription(aSid);
    }
    catch (InvalidSid&) { }
}

PropertyUpdate* DviPropertyUpdateCollection::MergeUpdate(PropertyUpdate* aUpdate)
{
    AutoMutex a(iLock);
    PropertyUpdatesFlattened* updates = FindBySid(aUpdate->Sid());
    if (updates == NULL) {
        delete aUpdate;
        return NULL;
    }
    return updates->MergeUpdate(aUpdate);
}

    
// DviServerWebSocket

DviServerWebSocket::DviServerWebSocket()
{
    if (Stack::InitParams().DvNumWebSocketThreads() > 0) {
        Initialise();
    }
}

SocketTcpServer* DviServerWebSocket::CreateServer(const NetworkAdapter& aNif)
{
    SocketTcpServer* server = new SocketTcpServer("WSSV", Stack::InitParams().DvWebSocketPort(), aNif.Address());
    TChar thName[5];
	const TUint numWsThreads = Stack::InitParams().DvNumWebSocketThreads();
    for (TUint i=0; i<numWsThreads; i++) {
        (void)sprintf(&thName[0], "WS%2lu", (unsigned long)i);
        server->Add(&thName[0], new DviSessionWebSocket(aNif.Address(), server->Port()));
    }
    return server;
}
