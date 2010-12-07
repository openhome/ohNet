#include <DviServerWebSocket.h>
#include <Network.h>
#include <Zapp.h>
#include <Stream.h>
#include <Http.h>
#include <Printer.h>
#include <Arch.h>
#include <md5.h>
#include <XmlParser.h>
#include <DviStack.h>
#include <DviDevice.h>
#include <DviSubscription.h>
#include <Fifo.h>
#include <Debug.h>

using namespace Zapp;

#define WS_76_HANDSHAKE
#undef  WS_DRAFT03_READ
#undef  WS_DRAFT03_WRITE

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
const Brn WebSocket::kTagRoot("ROOT");
const Brn WebSocket::kTagMethod("METHOD");
const Brn WebSocket::kTagUdn("UDN");
const Brn WebSocket::kTagService("SERVICE");
const Brn WebSocket::kTagSid("SID");
const Brn WebSocket::kTagNt("NT");
const Brn WebSocket::kTagTimeout("TIMEOUT");
const Brn WebSocket::kTagNts("NTS");
const Brn WebSocket::kTagSeq("SEQ");
const Brn WebSocket::kMethodSubscribe("Subscribe");
const Brn WebSocket::kMethodUnsubscribe("Unsubscribe");
const Brn WebSocket::kMethodRenew("Renew");
const Brn WebSocket::kMethodSubscriptionTimeout("SubscriptionTimeout");
const Brn WebSocket::kMethodPropertyUpdate("PropertyUpdate");
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
    iWriter.Write(Brn("</root>"));
    Brh* buf = new Brh;
    iWriter.TransferTo(*buf);
    iSession.QueuePropertyUpdate(buf);
}


// DviSessionWebSocket

DviSessionWebSocket::DviSessionWebSocket(TIpAddress aInterface, TUint aPort)
    : iEndpoint(aPort, aInterface)
    , iInterruptLock("WSIM")
    , iShutdownSem("WSIS", 1)
    , iPropertyUpdates(kMaxPropertyUpdates)
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
    Interrupt(true);
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
            iReaderRequest->Read();
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
                Interrupt(false);
                WritePropertyUpdates();
                LOG(kDvWebSocket, "WS: Wait for next request (or interrupt)\n");
                Read();
            }
            catch (ReaderError&) {
                if (iPropertyUpdates.SlotsUsed() == 0) {
                    LOG2(kDvWebSocket, kError, "WS: Exception - ReaderError\n");
                    WriteConnectionClose();
                    iExit = true;
                }
            }
            catch (WebSocketError&) {
                LOG2(kDvWebSocket, kError, "WS: Exception - WebSocketError\n");
                WriteConnectionClose();
                iExit = true;
            }
            catch (WriterError&) {
                LOG2(kDvWebSocket, kError, "WS: Exception - WriterError\n");
                iExit = true;
            }
            catch (XmlError&) {
                LOG2(kDvWebSocket, kError, "WS: Exception - XmlError\n");
                WriteConnectionClose();
                iExit = true;
            }
        }
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

#ifdef WS_76_HANDSHAKE
void DviSessionWebSocket::Handshake()
{
    if (!iHeaderConnection.Upgrade() || iHeaderUpgrade.Upgrade() != WebSocket::kUpgradeWebSocket ||
        !iHeaderKey1.Received() || !iHeaderKey2.Received() ||
        !iHeaderProtocol.Received() || iHeaderProtocol.Protocol() != WebSocket::kValueNt) {
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
    iWriterResponse->WriteHeader(WebSocket::kHeaderProtocol, WebSocket::kValueNt);
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
    // !!!! Add check for sub-protocol upnp-event being set
    if (!iHeaderConnection.Upgrade() || iHeaderUpgrade.Upgrade() != WebSocket::kUpgradeWebSocket) {
        LOG2(kDvWebSocket, kError, "WS: Handshake missing expected header\n");
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
        iWriterResponse->WriteHeader(WebSocket::kHeaderProtocol, iHeaderProtocol.Protocol());
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
        LOG2(kDvWebSocket, kError, "WS: MORE bit set - fragmented packets not supported (but should be if you're seeing this error)\n");
        THROW(WebSocketError);
    }
    if ((byte1 & kBitMaskRsv123) || (byte2 & kBitMaskRsv4)) {
        LOG2(kDvWebSocket, kError, "WS: RSV bit(s) set - %u, %u - but no extension negotiated\n", (byte1 & kBitMaskRsv123) >> 4, byte2 & kBitMaskRsv4);
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
        LOG2(kDvWebSocket, kError, "WS: Continuation opcode not yet supported\n");
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
        LOG(kDvWebSocket, "WS: Pong - ");
        LOG(kDvWebSocket, data);
        LOG(kDvWebSocket, "\n");
        break;
    case eText:
        Log::Print("WS: eText\n");
        // subscribe, renew, unsubscribe
        break;
    case eBinary:
        LOG2(kDvWebSocket, kError, "WS: Binary opcode not supported\n");
        break;
    default:
        LOG2(kDvWebSocket, kError, "WS: Unexpected reserved opcode %u received\n", opcode);
        break;
    }
}
#else // !WS_DRAFT03_READ
void DviSessionWebSocket::Read()
{
    Brn data = iReadBuffer->ReadUntil(kMsgEnd);
    if (data.Bytes() == 1 && data[0] == kFrameCloseStart) {
        Brn msg = iReadBuffer->Read(1);
        if (msg[0] != kMsgCloseEnd) {
            THROW(WebSocketError);
        }
        WriteConnectionClose();
        iExit = true;
        return;
    }
    if (data[0] != kFrameMsgStart) {
        LOG2(kDvWebSocket, kError, "WS: Unexpected leading byte - %u\n", data[0]);
        THROW(WebSocketError);
    }
    data.Set(data.Split(1, data.Bytes()-1));
    AutoMutex a(iInterruptLock);

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
    //LogVerbose(true, true);
    iWriterBuffer->Write(kFrameMsgStart);
    iWriterBuffer->Write(aData);
    iWriterBuffer->Write(kMsgEnd);
    iWriterBuffer->WriteFlush();
    //LogVerbose(true, false);
}
#endif // WS_DRAFT03_WRITE

void DviSessionWebSocket::WriteConnectionClose()
{
    // !!!! will need a different implementation for draft03
    try {
        iWriterBuffer->Write(kFrameCloseStart);
        iWriterBuffer->Write(kMsgCloseEnd);
        iWriterBuffer->WriteFlush();
    }
    catch (WriterError&) {}
    iExit = true;
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
    service->AddSubscription(subscription);
    DviSessionWebSocket::SubscriptionWrapper* wrapper = new DviSessionWebSocket::SubscriptionWrapper(*subscription, sid, *service);
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
    Write(eText, resp);
}

void DviSessionWebSocket::WritePropertyUpdates()
{
    AutoMutex a(iInterruptLock);
    while (iPropertyUpdates.SlotsUsed() > 0) {
        LOG(kDvWebSocket, "WS: Write property update\n");
        Brh* msg = iPropertyUpdates.Read();
        Write(eText, *msg);
        delete msg;
    }
}

IPropertyWriter* DviSessionWebSocket::CreateWriter(const IDviSubscriptionUserData* aUserData, const Brx& /*aSid*/, TUint aSequenceNumber)
{
    const SubscriptionDataWs* data = reinterpret_cast<const SubscriptionDataWs*>(aUserData->Data());
    return new PropertyWriterWs(*this, data->SubscriberSid(), aSequenceNumber);
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

DviServerWebSocket::DviServerWebSocket()
{
    if (Stack::InitParams().DvNumWebSocketThreads() > 0) {
        Initialise();
    }    
}

SocketTcpServer* DviServerWebSocket::CreateServer(const NetworkInterface& aNif)
{
    SocketTcpServer* server = new SocketTcpServer("WSSV", 54321, aNif.Address());
    TChar thName[5];
	const TUint numWsThreads = Stack::InitParams().DvNumWebSocketThreads();
    for (TUint i=0; i<numWsThreads; i++) {
        (void)sprintf(&thName[0], "WS%2u", i);
        server->Add(&thName[0], new DviSessionWebSocket(aNif.Address(), server->Port()));
    }
    return server;
}
