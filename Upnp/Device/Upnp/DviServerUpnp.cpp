#include <DviServerUpnp.h>
#include <Network.h>
#include <NetworkInterfaceList.h>
#include <Http.h>
#include <Ascii.h>
#include <Parser.h>
#include <Ssdp.h>
#include <Stack.h>
#include <DviStack.h>
#include <DviDevice.h>
#include <DviDeviceUpnp.h>
#include <Printer.h>
#include <XmlParser.h>
#include <Converter.h>
#include <Stream.h>
#include <Stack.h>
#include <Zapp.h>
#include <Debug.h>

using namespace Zapp;

//static const Brn kServerDescription("UPnP/1.1, Zapp UPnP Stack/3.0");
static const Brn kUpnpHeaderExt("Ext");
static const Brn kUpnpHeaderCallback("Callback");
static const Brn kUpnpHeaderNt("Nt");
static const Brn kUpnpHeaderNts("Nts");
static const Brn kUpnpHeaderSeq("Seq");

static const Brn kUpnpMethodSubscribe("SUBSCRIBE");
static const Brn kUpnpMethodUnsubscribe("UNSUBSCRIBE");
static const Brn kUpnpMethodNotify("NOTIFY");


// HeaderExpect

TBool HeaderExpect::Continue() const
{
    return (Received()? iContinue : false);
}

TBool HeaderExpect::Recognise(const Brx& aHeader)
{
    return (Ascii::CaseInsensitiveEquals(aHeader, Http::kHeaderExpect));
}

void HeaderExpect::Process(const Brx& aValue)
{
    SetReceived();
    iContinue = (aValue == Http::kExpect100Continue);
}


// HeaderSoapAction

const Brx& HeaderSoapAction::Domain() const
{
    return iDomain;
}

const Brx& HeaderSoapAction::Type() const
{
    return iType;
}

TUint HeaderSoapAction::Version() const
{
    return iVersion;
}

const Brx& HeaderSoapAction::Action() const
{
    return iAction;
}

TBool HeaderSoapAction::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Brn("SoapAction"));
}

void HeaderSoapAction::Process(const Brx& aValue)
{
    SetReceived();

    // remove quotes if present
    Brn value(aValue);
    TUint bytes = value.Bytes();
    if (bytes >= 2 && value[0] == '\"' && value[bytes - 1] == '\"') {
        value.Set(aValue.Ptr() + 1, bytes - 2);
    }

    Parser parser(value);
    if (parser.Next(':') != Brn("urn")) {
        THROW(HttpError);
    }

    Brn domain = parser.Next(':');
    iDomain.Grow(domain.Bytes() + 10);
    Ssdp::UpnpDomainToCanonical(domain, iDomain);
    if (!iDomain.Bytes()) {
        THROW(HttpError);
    }

    if (parser.Next(':') != Brn("service")) {
        THROW(HttpError);
    }

    iType.Set(parser.Next(':'));
    if (!iType.Bytes()) {
        THROW(HttpError);
    }

    try {
        iVersion = Ascii::Uint(parser.Next('#'));
    }
    catch (AsciiError) { // version not numeric
        THROW(HttpError);
    }

    iAction.Set(Ascii::Trim(parser.Remaining()));
    if (!iAction.Bytes()) {
        THROW(HttpError);
    }
}


// HeaderCallback

const Endpoint& HeaderCallback::Endpoint() const
{
	return iEndpoint;
}

const Brx& HeaderCallback::Uri() const
{
	return iUri;
}

void HeaderCallback::Log()
{
    TIpAddress addr = iEndpoint.Address();
    LOG(kDvEvent, "%u.%u.%u.%u:%u", addr&0xff, (addr>>8)&0xff, (addr>>16)&0xff, (addr>>24)&0xff, iEndpoint.Port());
    LOG(kDvEvent, iUri);
}

TBool HeaderCallback::Recognise(const Brx& aHeader)
{
	return Ascii::CaseInsensitiveEquals(aHeader, kUpnpHeaderCallback);
}

void HeaderCallback::Process(const Brx& aValue)
{
    SetReceived();

    Parser parser(aValue);
    parser.Next('<');
    Brn uri = parser.Next('>');
    TUint bytes = uri.Bytes();
    if (bytes < Http::kUriPrefix.Bytes()) {
        THROW(HttpError);
    }
    if (uri.Split(0, Http::kUriPrefix.Bytes()) != Http::kUriPrefix) {
        THROW(HttpError);
    }
    parser.Set(uri.Split(Http::kUriPrefix.Bytes()));
    Brn address = parser.Next(':');
    Brn port = parser.Next('/');
    try {
        iEndpoint = Zapp::Endpoint(Ascii::Uint(port), address);
    }
    catch (AsciiError) {
        THROW(HttpError);
    }
    Brn remaining = parser.Remaining();
    iUri.Grow(remaining.Bytes() + 1);
    iUri.Replace(Brn("/"));
    iUri.Append(remaining);
}


// PropertyWriter

PropertyWriter::PropertyWriter(const Endpoint& aPublisher, const Endpoint& aSubscriber, const Brx& aSubscriberPath,
                               const Brx& aSid, TUint aSequenceNumber)
{
    iSocket.Open();
    iSocket.Connect(aSubscriber, Stack::InitParams().TcpConnectTimeoutMs());
    iWriterChunked = new WriterHttpChunked(iSocket);
    iWriteBuffer = new Sws<kMaxRequestBytes>(*iWriterChunked);
    iWriterEvent = new WriterHttpRequest(*iWriteBuffer);

    iWriterEvent->WriteMethod(kUpnpMethodNotify, aSubscriberPath, Http::eHttp11);

    IWriterAscii& writer = iWriterEvent->WriteHeaderField(Http::kHeaderHost);
    static const TUint kMaxAddressBytes = 21; // xxx.xxx.xxx.xxx:xxxxx
    Bws<kMaxAddressBytes> host;
    TIpAddress addr = aPublisher.Address();
    (void)Ascii::AppendDec(host, addr&0xff);
    host.Append('.');
    (void)Ascii::AppendDec(host, (addr>>8)&0xff);
    host.Append('.');
    (void)Ascii::AppendDec(host, (addr>>16)&0xff);
    host.Append('.');
    (void)Ascii::AppendDec(host, (addr>>24)&0xff);
    host.Append(':');
    (void)Ascii::AppendDec(host, aPublisher.Port());
    writer.Write(host);
    writer.WriteFlush();

    iWriterEvent->WriteHeader(Http::kHeaderContentType, Brn("text/xml; charset=\"utf-8\""));
    iWriterEvent->WriteHeader(kUpnpHeaderNt, Brn("upnp:event"));
    iWriterEvent->WriteHeader(kUpnpHeaderNts, Brn("upnp:propchange"));

    writer = iWriterEvent->WriteHeaderField(HeaderSid::kHeaderSid);
    writer.Write(HeaderSid::kFieldSidPrefix);
    writer.Write(aSid);
    writer.WriteFlush();

    iWriterEvent->WriteHeader(Http::kHeaderTransferEncoding, Http::kTransferEncodingChunked);

    writer = iWriterEvent->WriteHeaderField(kUpnpHeaderSeq);
    writer.WriteUint(aSequenceNumber);
    writer.WriteFlush();

    iWriterEvent->WriteHeader(Http::kHeaderConnection, Http::kConnectionClose);
    iWriterEvent->WriteFlush();
    iWriterChunked->SetChunked(true);

    iWriteBuffer->Write(Brn("<?xml version=\"1.0\"?>"));
    iWriteBuffer->Write(Brn("<e:propertyset xmlns:e=\"urn:schemas-upnp-org:event-1-0\">"));
}

PropertyWriter::~PropertyWriter()
{
    delete iWriterEvent;
    delete iWriteBuffer;
    delete iWriterChunked;
    iSocket.Close();
}

void PropertyWriter::PropertyWriteString(const Brx& aName, const Brx& aValue)
{
    WriterBwh writer(1024);
    Converter::ToXmlEscaped(writer, aValue);
    Brh buf;
    writer.TransferTo(buf);
    WriteVariable(aName, buf);
}

void PropertyWriter::PropertyWriteInt(const Brx& aName, TInt aValue)
{
    Bws<Ascii::kMaxIntStringBytes> buf;
    (void)Ascii::AppendDec(buf, aValue);
    WriteVariable(aName, buf);
}

void PropertyWriter::PropertyWriteUint(const Brx& aName, TUint aValue)
{
    Bws<Ascii::kMaxUintStringBytes> buf;
    (void)Ascii::AppendDec(buf, aValue);
    WriteVariable(aName, buf);
}

void PropertyWriter::PropertyWriteBool(const Brx& aName, TBool aValue)
{
    PropertyWriteUint(aName, (aValue? 1 : 0));
}

void PropertyWriter::PropertyWriteBinary(const Brx& aName, const Brx& aValue)
{
    WriterBwh writer(1024);
    Converter::ToBase64(writer, aValue);
    Brh buf;
    writer.TransferTo(buf);
    WriteVariable(aName, buf);
}

void PropertyWriter::PropertyWriteEnd()
{
    iWriteBuffer->Write(Brn("</e:propertyset>"));
    iWriteBuffer->WriteFlush();

    Srs<kMaxResponseBytes> readBuffer(iSocket);
    ReaderHttpResponse readerResponse(readBuffer);
    readerResponse.Read();
    const HttpStatus& status = readerResponse.Status();
    if (status != HttpStatus::kOk) {
        LOG2(kDvEvent, kError, "PropertyWriter, http error %u ", status.Code());
        LOG2(kDvEvent, kError, status.Reason());
        LOG2(kDvEvent, kError, "\n");
    }
}

void PropertyWriter::WriteVariable(const Brx& aName, const Brx& aValue)
{
    iWriteBuffer->Write(Brn("<e:property>"));
    iWriteBuffer->Write('<');
    iWriteBuffer->Write(aName);
    iWriteBuffer->Write('>');
    iWriteBuffer->Write(aValue);
    iWriteBuffer->Write(Brn("</"));
    iWriteBuffer->Write(aName);
    iWriteBuffer->Write('>');
    iWriteBuffer->Write(Brn("</e:property>"));
}


// DviSessionUpnp

DviSessionUpnp::DviSessionUpnp(TIpAddress aInterface, TUint aPort)
    : iInterface(aInterface)
    , iPort(aPort)
{
    iReadBuffer = new Srs<kMaxRequestBytes>(*this);
    iReaderRequest = new ReaderHttpRequest(*iReadBuffer);
    iWriterChunked = new WriterHttpChunked(*this);
    iWriterBuffer = new Sws<kMaxResponseBytes>(*iWriterChunked);
    iWriterResponse = new WriterHttpResponse(*iWriterBuffer);

    iReaderRequest->AddMethod(Http::kMethodGet);
    iReaderRequest->AddMethod(Http::kMethodPost);
//    iReaderRequest->AddMethod(HttpMethod::kHead);
    iReaderRequest->AddMethod(kUpnpMethodSubscribe);
    iReaderRequest->AddMethod(kUpnpMethodUnsubscribe);

    iReaderRequest->AddHeader(iHeaderHost);
    iReaderRequest->AddHeader(iHeaderContentLength);
    iReaderRequest->AddHeader(iHeaderConnection);
    iReaderRequest->AddHeader(iHeaderExpect);
    iReaderRequest->AddHeader(iHeaderSoapAction);
    iReaderRequest->AddHeader(iHeaderSid);
    iReaderRequest->AddHeader(iHeaderTimeout);
    iReaderRequest->AddHeader(iHeaderNt);
    iReaderRequest->AddHeader(iHeaderCallback);
}

DviSessionUpnp::~DviSessionUpnp()
{
    delete iWriterResponse;
    delete iWriterBuffer;
    delete iWriterChunked;
    delete iReaderRequest;
    delete iReadBuffer;
}

void DviSessionUpnp::Run()
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
        iResponseStarted = false;
        iResponseEnded = false;
        if (method == Http::kMethodGet) {
            Get();
        }
        else if (method == Http::kMethodPost) {
            Post();
        }
        else if (method == kUpnpMethodSubscribe) {
            Subscribe();
        }
        else if (method == kUpnpMethodUnsubscribe) {
            Unsubscribe();
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

void DviSessionUpnp::Error(const HttpStatus& aStatus)
{
    iErrorStatus = &aStatus;
    THROW(HttpError);
}

void DviSessionUpnp::Get()
{
#if 0
    Log::Print("Get - ");
    Log::Print(iReaderRequest->Uri());
    Log::Print("\n");
#endif
    if (iReaderRequest->Version() == Http::eHttp11) {
        if (!iHeaderHost.Received()) {
            Error(HttpStatus::kBadRequest);
        }
    }

    // !!!! accept-language handling
    DviStack::DeviceMap().WriteResource(iReaderRequest->Uri(), iInterface, *this);
    if (iResponseStarted) {
        ASSERT(iResponseEnded);
    }
}

void DviSessionUpnp::Post()
{
    LOG(KDvInvocation, "Action called: ");
    LOG(KDvInvocation, iHeaderSoapAction.Action());
    LOG(KDvInvocation, "\n");

    if (iReaderRequest->Version() == Http::eHttp11) {
        if (!iHeaderHost.Received()) {
            Error(HttpStatus::kBadRequest);
        }
    }
    if (iHeaderExpect.Continue()) {
        iWriterResponse->WriteStatus(HttpStatus::kContinue, Http::eHttp11);
        iWriterResponse->WriteFlush();
    }
    if (iHeaderContentLength.ContentLength() == 0) {
        Error(HttpStatus::kBadRequest);
    }

    iSoapRequest.Set(iReadBuffer->Read(iHeaderContentLength.ContentLength()));

    DviDevice* device;
    DviService* service;
    ParseRequestUri(DviDeviceUpnp::kControlUrlTail, &device, &service);
    if (device == NULL || service == NULL) {
        try {
            const HttpStatus* err = &HttpStatus::kNotFound;
            InvocationReportError(err->Code(), err->Reason());
        }
        catch (InvocationError&) {}
    }
    TBool completed = false;
    try {
        if (service != NULL) {
            service->Invoke(*this, iHeaderSoapAction.Version(), iHeaderSoapAction.Action());
            completed = true;
        }
    }
    catch (InvocationError&) {}
    if (completed) {
        LOG(KDvInvocation, "Completed action: ");
        LOG(KDvInvocation, iHeaderSoapAction.Action());
        LOG(KDvInvocation, "\n");
    }
}

void DviSessionUpnp::Subscribe()
{
    LOG(kDvEvent, "Subscription request from ");
    iHeaderCallback.Log();
    LOG(kDvEvent, "\n");
    if (iHeaderSid.Received()) {
        Renew();
        return;
    }

    if (!iHeaderCallback.Received() || !iHeaderNt.Received() || !iHeaderTimeout.Received()) {
        Error(HttpStatus::kPreconditionFailed);
    }
    DviDevice* device;
    DviService* service;
    ParseRequestUri(DviDeviceUpnp::kEventUrlTail, &device, &service);
    if (device == NULL || service == NULL) {
        Error(HttpStatus::kPreconditionFailed);
    }
    TUint duration = iHeaderTimeout.Timeout();
    Brh sid;
    device->CreateSid(sid);
    DviSubscription* subscription = new DviSubscription(*device, *this, iHeaderCallback.Endpoint(), iHeaderCallback.Uri(), sid, duration);
    DviSubscriptionManager::AddSubscription(*subscription);

    if (iHeaderExpect.Continue()) {
        iWriterResponse->WriteStatus(HttpStatus::kContinue, Http::eHttp11);
        iWriterResponse->WriteFlush();
    }
    // respond to subscription request
    iResponseStarted = true;
    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eHttp11);
	WriteServerHeader(*iWriterResponse);
    IWriterAscii& writerSid = iWriterResponse->WriteHeaderField(HeaderSid::kHeaderSid);
    writerSid.Write(HeaderSid::kFieldSidPrefix);
    writerSid.Write(subscription->Sid());
    writerSid.WriteFlush();
    IWriterAscii& writerTimeout = iWriterResponse->WriteHeaderField(HeaderTimeout::kHeaderTimeout);
    writerTimeout.Write(HeaderTimeout::kFieldTimeoutPrefix);
    writerTimeout.WriteUint(duration);
    writerTimeout.WriteFlush();
   	iWriterResponse->WriteHeader(Http::kHeaderConnection, Http::kConnectionClose);
    iWriterResponse->WriteFlush();
    iResponseEnded = true;

    LOG(kDvEvent, "Subscription complete for ");
    iHeaderCallback.Log();
    LOG(kDvEvent, ", sid is ");
    LOG(kDvEvent, subscription->Sid());
    LOG(kDvEvent, "\n");

    // Start subscription, prompting delivery of the first update (covering all state variables)
    service->AddSubscription(subscription);
}

void DviSessionUpnp::Unsubscribe()
{
    LOG(kDvEvent, "Unsubscribe request: ");
    LOG(kDvEvent, iHeaderSid.Sid());
    LOG(kDvEvent, "\n");

    if (!iHeaderSid.Received()) {
        LOG2(kDvEvent, kError, "Unsubscribe failed - no sid\n");
        Error(HttpStatus::kPreconditionFailed);
    }

    DviDevice* device;
    DviService* service;
    ParseRequestUri(DviDeviceUpnp::kEventUrlTail, &device, &service);
    if (device == NULL || service == NULL) {
        LOG2(kDvEvent, kError, "Unsubscribe failed - device=%p, service=%p\n", device, service);
        Error(HttpStatus::kPreconditionFailed);
    }
    DviSubscription* subscription = DviSubscriptionManager::Find(iHeaderSid.Sid());
    if (subscription == NULL) {
        LOG2(kDvEvent, kError, "Unsubscribe failed - couldn't match sid ");
        LOG2(kDvEvent, kError, iHeaderSid.Sid());
        LOG2(kDvEvent, kError, "\n");
        Error(HttpStatus::kPreconditionFailed);
    }
    service->RemoveSubscription(iHeaderSid.Sid());

    if (iHeaderExpect.Continue()) {
        iWriterResponse->WriteStatus(HttpStatus::kContinue, Http::eHttp11);
        iWriterResponse->WriteFlush();
    }
    iResponseStarted = true;
    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eHttp11);
   	iWriterResponse->WriteHeader(Http::kHeaderConnection, Http::kConnectionClose);
    iWriterResponse->WriteFlush();
    iResponseEnded = true;

    LOG(kDvEvent, "Unsubscribe complete: ");
    LOG(kDvEvent, iHeaderSid.Sid());
    LOG(kDvEvent, "\n");
}

void DviSessionUpnp::Renew()
{
    LOG(kDvEvent, "Renew subscription (request): ");
    LOG(kDvEvent, iHeaderSid.Sid());
    LOG(kDvEvent, "for %u secs\n", iHeaderTimeout.Timeout());

    if (iHeaderCallback.Received() || iHeaderNt.Received()) {
        Error(HttpStatus::kBadRequest);
    }

    DviDevice* device;
    DviService* service;
    ParseRequestUri(DviDeviceUpnp::kEventUrlTail, &device, &service);
    if (device == NULL || service == NULL) {
        Error(HttpStatus::kPreconditionFailed);
    }

    DviSubscription* subscription = DviSubscriptionManager::Find(iHeaderSid.Sid());
    if (subscription == NULL) {
        Error(HttpStatus::kPreconditionFailed);
    }
    TUint duration = iHeaderTimeout.Timeout();
    subscription->Renew(duration);

    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eHttp11);
	WriteServerHeader(*iWriterResponse);
    IWriterAscii& writerSid = iWriterResponse->WriteHeaderField(HeaderSid::kHeaderSid);
    writerSid.Write(HeaderSid::kFieldSidPrefix);
    writerSid.Write(iHeaderSid.Sid());
    writerSid.WriteFlush();
    IWriterAscii& writerTimeout = iWriterResponse->WriteHeaderField(HeaderTimeout::kHeaderTimeout);
    writerTimeout.Write(HeaderTimeout::kFieldTimeoutPrefix);
    writerTimeout.WriteUint(duration);
    writerTimeout.WriteFlush();
   	iWriterResponse->WriteHeader(Http::kHeaderConnection, Http::kConnectionClose);
    iWriterResponse->WriteFlush();

    LOG(kDvEvent, "Renew subscription (complete): ");
    LOG(kDvEvent, iHeaderSid.Sid());
    LOG(kDvEvent, "for %u secs\n", duration);
}

void DviSessionUpnp::ParseRequestUri(const Brx& aUrlTail, DviDevice** aDevice, DviService** aService)
{
    Parser parser(iReaderRequest->Uri());
    Brn tmp = parser.Next('/');
    if (tmp.Bytes() > 0) {
        Error(HttpStatus::kPreconditionFailed);
    }
    Brn udn = parser.Next('/');
    DviDevice* device = DviDeviceMap::Find(udn);
    *aDevice = device;
    if (device == NULL) {
        Error(HttpStatus::kPreconditionFailed);
    }
    Brn serviceName = parser.Next('/');
    if (parser.Remaining() != aUrlTail) {
        Error(HttpStatus::kPreconditionFailed);
    }
    const TUint count = device->ServiceCount();
    for (TUint i=0; i<count; i++) {
        DviService& service = device->Service(i);
        if (service.ServiceType().PathUpnp() == serviceName) {
            *aService = &service;
            break;
        }
    }
}

void DviSessionUpnp::WriteServerHeader(IWriterHttpHeader& aWriter)
{
	IWriterAscii& stream = aWriter.WriteHeaderField(Brn("SERVER"));
	TUint major, minor;
	Brn osName = Os::GetPlatformNameAndVersion(major, minor);
	stream.Write(osName);
	stream.Write('/');
	stream.WriteUint(major);
	stream.Write('.');
	stream.WriteUint(minor);
	stream.Write(Brn(" UPnP/1.1 Zapp/"));
	Stack::GetVersion(major, minor);
	stream.WriteUint(major);
	stream.Write('.');
	stream.WriteUint(minor);
	stream.WriteFlush();
}

void DviSessionUpnp::WriteResourceBegin(TUint aTotalBytes, const TChar* aMimeType)
{
    if (iHeaderExpect.Continue()) {
        iWriterResponse->WriteStatus(HttpStatus::kContinue, Http::eHttp11);
        iWriterResponse->WriteFlush();
    }
    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eHttp11);
    if (aTotalBytes > 0) {
        Http::WriteHeaderContentLength(*iWriterResponse, aTotalBytes);
    }
    else {
        iWriterResponse->WriteHeader(Http::kHeaderTransferEncoding, Http::kTransferEncodingChunked);
    }
	if (aMimeType != NULL) {
		IWriterAscii& writer = iWriterResponse->WriteHeaderField(Http::kHeaderContentType);
		writer.Write(Brn(aMimeType));
		writer.Write(Brn("; charset=\"utf-8\""));
		writer.WriteFlush();
	}
    Http::WriteHeaderConnectionClose(*iWriterResponse);
    iWriterResponse->WriteFlush();
    if (aTotalBytes == 0) {
        iWriterChunked->SetChunked(true);
    }
    iResponseStarted = true;
}

void DviSessionUpnp::WriteResource(const TByte* aData, TUint aBytes)
{
    Brn buf(aData, aBytes);
#if 0
    Log::Print("Writing resource...\n");
    Log::Print(buf);
    Log::Print("\n\n");
#endif
    iWriterBuffer->Write(buf);
}

void DviSessionUpnp::WriteResourceEnd()
{
    iResponseEnded = true;
    iWriterBuffer->WriteFlush();
}

void DviSessionUpnp::InvocationReadStart()
{
    try {
        Brn envelope = XmlParserBasic::Find("Envelope", iSoapRequest);
        Brn body = XmlParserBasic::Find("Body", envelope);
        Brn args = XmlParserBasic::Find(iHeaderSoapAction.Action(), body);
        iSoapRequest.Set(args);
    }
    catch (XmlError&) {
        InvocationReportError(501, Brn("Invalid XML"));
    }
}

TBool DviSessionUpnp::InvocationReadBool(const TChar* aName)
{
    try {
        Brn value = XmlParserBasic::Find(aName, iSoapRequest);
        try {
            TUint num = Ascii::Uint(value);
            return (num != 0);
        }
        catch (AsciiError) {
            if (value == Brn("true")) {
                return true;
            }
            else if (value == Brn("false")) {
                return false;
            }
            THROW(XmlError);
        }
    }
    catch (XmlError&) {
        InvocationReportError(501, Brn("Invalid XML"));
    }
    return false;
}

void DviSessionUpnp::InvocationReadString(const TChar* aName, Brhz& aString)
{
    try {
        Brn value = XmlParserBasic::Find(aName, iSoapRequest);
        if (value.Bytes()) {
            Bwh writable(value.Bytes()+1);
			writable.Append(value);
            Converter::FromXmlEscaped(writable);
            writable.PtrZ();
            writable.TransferTo(aString);
        }
    }
    catch (XmlError&) {
        InvocationReportError(501, Brn("Invalid XML"));
    }
}

TInt DviSessionUpnp::InvocationReadInt(const TChar* aName)
{
    try {
        Brn value = XmlParserBasic::Find(aName, iSoapRequest);
        TInt num = Ascii::Int(value);
        return num;
    }
    catch (XmlError&) {
        InvocationReportError(501, Brn("Invalid XML"));
    }
    catch (AsciiError&) {
        InvocationReportError(501, Brn("Invalid XML"));
    }
    return 0;
}

TUint DviSessionUpnp::InvocationReadUint(const TChar* aName)
{
    try {
        Brn value = XmlParserBasic::Find(aName, iSoapRequest);
        TUint num = Ascii::Uint(value);
        return num;
    }
    catch (XmlError&) {
        InvocationReportError(501, Brn("Invalid XML"));
    }
    catch (AsciiError&) {
        InvocationReportError(501, Brn("Invalid XML"));
    }
    return 0;
}

void DviSessionUpnp::InvocationReadBinary(const TChar* aName, Brh& aData)
{
    try {
        Brn value = XmlParserBasic::Find(aName, iSoapRequest);
        if (value.Bytes()) {
            Bwh writable(value.Bytes()+1);
			writable.Append(value);
            Converter::FromBase64(writable);
            writable.TransferTo(aData);
        }
    }
    catch (XmlError&) {
        InvocationReportError(501, Brn("Invalid XML"));
    }
}

void DviSessionUpnp::InvocationReadEnd()
{
    iSoapRequest.Set(Brx::Empty());
}

void DviSessionUpnp::InvocationReportError(TUint aCode, const Brx& aDescription)
{
    LOG(KDvInvocation, "Failure processing action: ");
    LOG(KDvInvocation, iHeaderSoapAction.Action());
    LOG(KDvInvocation, "\n");

    iResponseStarted = true;
    iWriterResponse->WriteStatus(HttpStatus::kInternalServerError, Http::eHttp11);
    iWriterResponse->WriteHeader(kUpnpHeaderExt, Brx::Empty());
    iWriterResponse->WriteHeader(Http::kHeaderContentType, Brn("text/xml; charset=\"utf-8\""));
	WriteServerHeader(*iWriterResponse);
    iWriterResponse->WriteHeader(Http::kHeaderTransferEncoding, Http::kTransferEncodingChunked);
    iWriterResponse->WriteHeader(Http::kHeaderConnection, Http::kConnectionClose);
    iWriterResponse->WriteFlush();

    iWriterChunked->SetChunked(true);

    iWriterBuffer->Write(Brn("<?xml version=\"1.0\"?>"));
    iWriterBuffer->Write(Brn("<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\">"));
    iWriterBuffer->Write(Brn("<s:Body s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">"));
    iWriterBuffer->Write(Brn("<s:Fault><faultcode>s:Client</faultcode><faultstring>UPnPError</faultstring><detail><UPnPError xmlns=\"urn:schemas-upnp-org:control-1-0\"><errorCode>"));
    Bws<Ascii::kMaxUintStringBytes> code;
    Ascii::AppendDec(code, aCode);
    iWriterBuffer->Write(code);
    iWriterBuffer->Write(Brn("</errorCode><errorDescription>"));
    iWriterBuffer->Write(aDescription);
    iWriterBuffer->Write(Brn("</errorDescription></UPnPError></detail></s:Fault></s:Body></s:Envelope>"));
    iWriterBuffer->WriteFlush();
    iResponseEnded = true;

    THROW(InvocationError);
}

void DviSessionUpnp::InvocationWriteStart()
{
    iResponseStarted = true;
    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eHttp11);
    iWriterResponse->WriteHeader(kUpnpHeaderExt, Brx::Empty());
    iWriterResponse->WriteHeader(Http::kHeaderContentType, Brn("text/xml; charset=\"utf-8\""));
	WriteServerHeader(*iWriterResponse);
    iWriterResponse->WriteHeader(Http::kHeaderTransferEncoding, Http::kTransferEncodingChunked);
    iWriterResponse->WriteHeader(Http::kHeaderConnection, Http::kConnectionClose);
    iWriterResponse->WriteFlush();

    iWriterChunked->SetChunked(true);

    iWriterBuffer->Write(Brn("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\"><s:Body s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><u:"));
    iWriterBuffer->Write(iHeaderSoapAction.Action());
    iWriterBuffer->Write(Brn("Response xmlns:u=\""));
    Ssdp::WriteServiceType(*iWriterBuffer, iHeaderSoapAction.Domain(), iHeaderSoapAction.Type(), iHeaderSoapAction.Version());
    iWriterBuffer->Write(Brn("\">"));
}

void DviSessionUpnp::InvocationWriteBool(const TChar* aName, TBool aValue)
{
    Brn name(aName);
    iWriterBuffer->Write('<');
    iWriterBuffer->Write(name);
    iWriterBuffer->Write(aValue ? Brn(">true</") : Brn(">false</"));
    iWriterBuffer->Write(name);
    iWriterBuffer->Write('>');
}

void DviSessionUpnp::InvocationWriteInt(const TChar* aName, TInt aValue)
{
    Brn name(aName);
    iWriterBuffer->Write('<');
    iWriterBuffer->Write(name);
    iWriterBuffer->Write('>');
    Bws<Ascii::kMaxIntStringBytes> val;
    (void)Ascii::AppendDec(val, aValue);
    iWriterBuffer->Write(val);
    iWriterBuffer->Write('<');
    iWriterBuffer->Write('/');
    iWriterBuffer->Write(name);
    iWriterBuffer->Write('>');
}

void DviSessionUpnp::InvocationWriteUint(const TChar* aName, TUint aValue)
{
    Brn name(aName);
    iWriterBuffer->Write('<');
    iWriterBuffer->Write(name);
    iWriterBuffer->Write('>');
    Bws<Ascii::kMaxUintStringBytes> val;
    (void)Ascii::AppendDec(val, aValue);
    iWriterBuffer->Write(val);
    iWriterBuffer->Write('<');
    iWriterBuffer->Write('/');
    iWriterBuffer->Write(name);
    iWriterBuffer->Write('>');
}

void DviSessionUpnp::InvocationWriteBinaryStart(const TChar* aName)
{
    Brn name(aName);
    iWriterBuffer->Write('<');
    iWriterBuffer->Write(name);
    iWriterBuffer->Write('>');
}

void DviSessionUpnp::InvocationWriteBinary(TByte aValue)
{
    Brn buf(&aValue, 1);
    InvocationWriteBinary(buf);
}

void DviSessionUpnp::InvocationWriteBinary(const Brx& aValue)
{
    Converter::ToBase64(*iWriterBuffer, aValue);
}

void DviSessionUpnp::InvocationWriteBinaryEnd(const TChar* aName)
{
    Brn name(aName);
    iWriterBuffer->Write('<');
    iWriterBuffer->Write('/');
    iWriterBuffer->Write(name);
    iWriterBuffer->Write('>');
}

void DviSessionUpnp::InvocationWriteStringStart(const TChar* aName)
{
    Brn name(aName);
    iWriterBuffer->Write('<');
    iWriterBuffer->Write(name);
    iWriterBuffer->Write('>');
}

void DviSessionUpnp::InvocationWriteString(TByte aValue)
{
    Brn buf(&aValue, 1);
    InvocationWriteString(buf);
}

void DviSessionUpnp::InvocationWriteString(const Brx& aValue)
{
    Converter::ToXmlEscaped(*iWriterBuffer, aValue);
}

void DviSessionUpnp::InvocationWriteStringEnd(const TChar* aName)
{
    Brn name(aName);
    iWriterBuffer->Write('<');
    iWriterBuffer->Write('/');
    iWriterBuffer->Write(name);
    iWriterBuffer->Write('>');
}

void DviSessionUpnp::InvocationWriteEnd()
{
    iResponseEnded = true;
    iWriterBuffer->Write(Brn("</u:"));
    iWriterBuffer->Write(iHeaderSoapAction.Action());
    iWriterBuffer->Write(Brn("Response></s:Body></s:Envelope>"));
    iWriterBuffer->WriteFlush();
}

IPropertyWriter* DviSessionUpnp::CreateWriter(const Endpoint& aSubscriber, const Brx& aSubscriberPath,
                                              const Brx& aSid, TUint aSequenceNumber)
{
    Endpoint publisher(iPort, iInterface);
    return new PropertyWriter(publisher, aSubscriber, aSubscriberPath, aSid, aSequenceNumber);
}



// DviServerUpnp

DviServerUpnp::DviServerUpnp()
    : iLock("DSUM")
{
    Functor functor = MakeFunctor(*this, &DviServerUpnp::SubnetChanged);
    NetworkInterfaceList& nifList = Stack::NetworkInterfaceList();
    iSubnetChangeListenerId = nifList.AddSubnetChangeListener(functor);
    iLock.Wait();
    std::vector<NetworkInterface*>* subnetList = nifList.CreateSubnetList();
    for (TUint i=0; i<subnetList->size(); i++) {
        CreateServer(*(*subnetList)[i]);
    }
    NetworkInterfaceList::DestroySubnetList(subnetList);
    iLock.Signal();
}

DviServerUpnp::~DviServerUpnp()
{
    iLock.Wait();
    Stack::NetworkInterfaceList().RemoveSubnetChangeListener(iSubnetChangeListenerId);
    for (TUint i=0; i<iServers.size(); i++) {
        delete iServers[i];
    }
    iServers.clear();
    iLock.Signal();
}

TUint DviServerUpnp::Port(TIpAddress aInterface)
{
    DviServerUpnp& self = DviStack::ServerUpnp();
    AutoMutex a(self.iLock);
    for (TUint i=0; i<self.iServers.size(); i++) {
        DviServerUpnp::Server* server = self.iServers[i];
        if (server->Interface() == aInterface) {
            return server->Port();
        }
    }
    return 0;
}

void DviServerUpnp::CreateServer(const NetworkInterface& aNif)
{
    DviServerUpnp::Server* server = new DviServerUpnp::Server(aNif);
    iServers.push_back(server);
}

void DviServerUpnp::SubnetChanged()
{
    /* DviDeviceUpnp relies on servers being available on all appropriate interfaces.
       We assume this happens through DviServerUpnp being created before any devices
       so registering for subnet change notification earlier.  Assuming NetworkInterfaceList
       always runs its listeners in the order they registered, we'll have updated before
       any device listeners are run. */

    iLock.Wait();
    NetworkInterfaceList& interfaceList = Stack::NetworkInterfaceList();
    std::vector<NetworkInterface*>* subnetList = interfaceList.CreateSubnetList();
    const std::vector<NetworkInterface*>& nifList = interfaceList.List();
    TUint i;
    // remove servers whose interface is no longer available
    for (i=0; i<iServers.size(); i++) {
        DviServerUpnp::Server* server = iServers[i];
        if (FindInterface(server->Interface(), nifList) == -1) {
            delete server;
            iServers.erase(iServers.begin() + i);
        }
    }
    // add servers for new subnets
    for (i=0; i<subnetList->size(); i++) {
        NetworkInterface* subnet = (*subnetList)[i];
        if (FindServer(subnet->Subnet()) == -1) {
            CreateServer(*subnet);
        }
    }

    iLock.Signal();
    NetworkInterfaceList::DestroySubnetList(subnetList);
}

TInt DviServerUpnp::FindInterface(TIpAddress aInterface, const std::vector<NetworkInterface*>& aNifList)
{
    for (TUint i=0; i<aNifList.size(); i++) {
        if (aNifList[i]->Address() == aInterface) {
            return i;
        }
    }
    return -1;
}

TInt DviServerUpnp::FindServer(TIpAddress aSubnet)
{
    for (TUint i=0; i<iServers.size(); i++) {
        if (iServers[i]->Subnet() == aSubnet) {
            return i;
        }
    }
    return -1;
}


//  DviServerUpnp::Server

DviServerUpnp::Server::Server(const NetworkInterface& aNif)
{
    iServer = new SocketTcpServer("DSVU", 0, aNif.Address());
    iServer->Add("DSES", new DviSessionUpnp(aNif.Address(), Port()));
    iNif = aNif.Clone();
}

DviServerUpnp::Server::~Server()
{
    delete iServer;
    delete iNif;
}
