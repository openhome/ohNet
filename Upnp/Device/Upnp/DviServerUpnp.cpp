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
#include <Zapp.h>
#include <Debug.h>
#include <Stack.h>
#include <Error.h>

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
    Endpoint::EndpointBuf buf;
    iEndpoint.GetEndpoint(buf);
    LOG(kDvEvent, buf);
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


// SubscriptionDataUpnp

SubscriptionDataUpnp::SubscriptionDataUpnp(const Endpoint& aSubscriber, const Brx& aSubscriberPath)
    : iSubscriber(aSubscriber)
    , iSubscriberPath(aSubscriberPath)
{
}

const Endpoint& SubscriptionDataUpnp::Subscriber() const
{
    return iSubscriber;
}

const Brx& SubscriptionDataUpnp::SubscriberPath() const
{
    return iSubscriberPath;
}

const void* SubscriptionDataUpnp::Data() const
{
    return this;
}

void SubscriptionDataUpnp::Release()
{
    delete this;
}


// PropertyWriterUpnp

PropertyWriterUpnp::PropertyWriterUpnp(const Endpoint& aPublisher, const Endpoint& aSubscriber, const Brx& aSubscriberPath,
                                       const Brx& aSid, TUint aSequenceNumber)
{
    iSocket.Open();
    iSocket.Connect(aSubscriber, Stack::InitParams().TcpConnectTimeoutMs());
    iWriterChunked = new WriterHttpChunked(iSocket);
    iWriteBuffer = new Sws<kMaxRequestBytes>(*iWriterChunked);
    iWriterEvent = new WriterHttpRequest(*iWriteBuffer);
    SetWriter(*iWriteBuffer);

    iWriterEvent->WriteMethod(kUpnpMethodNotify, aSubscriberPath, Http::eHttp11);

    IWriterAscii& writer = iWriterEvent->WriteHeaderField(Http::kHeaderHost);
    Endpoint::EndpointBuf buf;
    aPublisher.GetEndpoint(buf);
    writer.Write(buf);
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

PropertyWriterUpnp::~PropertyWriterUpnp()
{
    delete iWriterEvent;
    delete iWriteBuffer;
    delete iWriterChunked;
    iSocket.Close();
}

void PropertyWriterUpnp::PropertyWriteEnd()
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


// DviSessionUpnp

DviSessionUpnp::DviSessionUpnp(TIpAddress aInterface, TUint aPort)
    : iInterface(aInterface)
    , iPort(aPort)
    , iShutdownSem("DSUS", 1)
{
    iReadBuffer = new Srs<kMaxRequestBytes>(*this);
    iReaderRequest = new ReaderHttpRequest(*iReadBuffer);
    iWriterChunked = new WriterHttpChunked(*this);
    iWriterBuffer = new Sws<kMaxResponseBytes>(*iWriterChunked);
    iWriterResponse = new WriterHttpResponse(*iWriterBuffer);

    iReaderRequest->AddMethod(Http::kMethodGet);
    iReaderRequest->AddMethod(Http::kMethodPost);
    iReaderRequest->AddMethod(Http::kMethodHead);
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
    Interrupt(true);
    iShutdownSem.Wait();
    delete iWriterResponse;
    delete iWriterBuffer;
    delete iWriterChunked;
    delete iReaderRequest;
    delete iReadBuffer;
}

void DviSessionUpnp::Run()
{
    iShutdownSem.Wait();
    iErrorStatus = &HttpStatus::kOk;
    iReaderRequest->Flush();
    iWriterChunked->SetChunked(false);
    iInvocationService = NULL;
	iResourceWriterHeadersOnly = false;
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
		else if (method == Http::kMethodHead) {
			iResourceWriterHeadersOnly = true;
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
        iErrorStatus = &HttpStatus::kMethodNotAllowed;
    }
    catch (ReaderError&) {
        iErrorStatus = &HttpStatus::kBadRequest;
    }
    catch (WriterError&) {
    }
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
    catch (WriterError&) {}
    iShutdownSem.Signal();
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

    DviStack::DeviceMap().WriteResource(iReaderRequest->Uri(), iInterface, *this);
    if (iResponseStarted) {
        ASSERT(iResponseEnded);
    }
}

void DviSessionUpnp::Post()
{
    LOG(kDvInvocation, "Action called: ");
    LOG(kDvInvocation, iHeaderSoapAction.Action());
    LOG(kDvInvocation, "\n");

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
    ParseRequestUri(DviDeviceUpnp::kControlUrlTail, &device, &iInvocationService);
    if (device != NULL && iInvocationService != NULL) {
        try {
            Invoke();
        }
        catch (InvocationError&) { }
        catch (ParameterValidationError&) {
            InvocationReportErrorNoThrow(Error::eCodeParameterInvalid, Error::kDescriptionParameterInvalid);
        }
    }
    else {
        const HttpStatus* err = &HttpStatus::kNotFound;
        InvocationReportErrorNoThrow(err->Code(), err->Reason());
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
    SubscriptionDataUpnp* data = new SubscriptionDataUpnp(iHeaderCallback.Endpoint(), iHeaderCallback.Uri());
    DviSubscription* subscription = new DviSubscription(*device, *this, data, sid, duration);
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
	if (iResourceWriterHeadersOnly) {
		return;
	}
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

void DviSessionUpnp::Invoke()
{
    try {
        iInvocationService->Invoke(*this, iHeaderSoapAction.Version(), iHeaderSoapAction.Action());
    }
    catch (InvocationError&) {}
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

void DviSessionUpnp::InvocationReportErrorNoThrow(TUint aCode, const Brx& aDescription)
{
    LOG(kDvInvocation, "Failure processing action: ");
    LOG(kDvInvocation, iHeaderSoapAction.Action());
    LOG(kDvInvocation, "\n");

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
}

void DviSessionUpnp::InvocationReportError(TUint aCode, const Brx& aDescription)
{
    InvocationReportErrorNoThrow(aCode, aDescription);
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

    LOG(kDvInvocation, "Completed action: ");
    LOG(kDvInvocation, iHeaderSoapAction.Action());
    LOG(kDvInvocation, "\n");
}

IPropertyWriter* DviSessionUpnp::CreateWriter(const IDviSubscriptionUserData* aUserData,
                                              const Brx& aSid, TUint aSequenceNumber)
{
    Endpoint publisher(iPort, iInterface);
    const SubscriptionDataUpnp* data = reinterpret_cast<const SubscriptionDataUpnp*>(aUserData->Data());
    return new PropertyWriterUpnp(publisher, data->Subscriber(), data->SubscriberPath(), aSid, aSequenceNumber);
}



// DviServerUpnp

DviServerUpnp::DviServerUpnp()
{
    Initialise();
}

SocketTcpServer* DviServerUpnp::CreateServer(const NetworkInterface& aNif)
{
    SocketTcpServer* server = new SocketTcpServer("DSVU", 0, aNif.Address());
    TChar thName[5];
	const TUint numWsThreads = Stack::InitParams().DvNumServerThreads();
    for (TUint i=0; i<numWsThreads; i++) {
        (void)sprintf(&thName[0], "DS%2u", i);
        server->Add(&thName[0], new DviSessionUpnp(aNif.Address(), server->Port()));
    }
    return server;
}
