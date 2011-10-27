#include <OpenHome/Net/Private/DviServerUpnp.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Net/Private/Ssdp.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/DviProtocolUpnp.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Net/Private/XmlParser.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Net/Private/Error.h>

#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Net;

//static const Brn kServerDescription("UPnP/1.1, ohNet UPnP Stack/3.0");
static const Brn kUpnpHeaderExt("Ext");
static const Brn kUpnpHeaderCallback("Callback");
static const Brn kUpnpHeaderNt("Nt");
static const Brn kUpnpHeaderNts("Nts");
static const Brn kUpnpHeaderSeq("Seq");

static const Brn kUpnpMethodSubscribe("SUBSCRIBE");
static const Brn kUpnpMethodUnsubscribe("UNSUBSCRIBE");
static const Brn kUpnpMethodNotify("NOTIFY");


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
    if (!Received()) {
        LOG(kDvEvent, "(null)");
        return;
    }
    Endpoint::EndpointBuf buf;
    iEndpoint.AppendEndpoint(buf);
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
        iEndpoint = OpenHome::Endpoint(Ascii::Uint(port), address);
    }
    catch (AsciiError) {
        THROW(HttpError);
    }
    Brn remaining = parser.Remaining();
    iUri.Grow(remaining.Bytes() + 1);
    iUri.Replace(Brn("/"));
    iUri.Append(remaining);
}


// HeaderAcceptLanguage

HeaderAcceptLanguage::~HeaderAcceptLanguage()
{
    ClearLanguageList();
}

const Brx& HeaderAcceptLanguage::LanguageString() const
{
    return iLanguages;
}

std::vector<char*>& HeaderAcceptLanguage::LanguageList()
{
    return iLanguageList;
}

TBool HeaderAcceptLanguage::Recognise(const Brx& aHeader)
{
	return Ascii::CaseInsensitiveEquals(aHeader, Http::kHeaderAcceptLanguage);
}

void HeaderAcceptLanguage::Process(const Brx& aValue)
{
    SetReceived();
    ClearLanguageList();
    iLanguages.Set(aValue);

    std::vector<PrioritisedLanguage> prioritisedList;
    Parser parser(iLanguages);
    while (parser.Remaining().Bytes() > 0) {
        Brn langBuf = parser.Next(',');
        Parser parser2(langBuf);
        Brn lang = parser2.Next(';');
        parser2.Set(parser2.Remaining());
        Brn qualityBuf = parser2.Next('=');
        if (qualityBuf.Bytes() > 0) {
            qualityBuf.Set(parser2.Remaining());
        }
        TUint quality = ParseQualityValue(qualityBuf);
        PrioritisedLanguage prioritisedLang;
        prioritisedLang.iLanguage = (char*)malloc(lang.Bytes()+1);
        (void)memcpy(prioritisedLang.iLanguage, lang.Ptr(), lang.Bytes());
        prioritisedLang.iLanguage[lang.Bytes()] = '\0';
        prioritisedLang.iPriority = quality;
        AddPrioritisedLanguage(prioritisedList, prioritisedLang);
    }

    for (TUint i=0; i<(TUint)prioritisedList.size(); i++) {
        iLanguageList.push_back(prioritisedList[i].iLanguage);
    }
}

void HeaderAcceptLanguage::ClearLanguageList()
{
    for (TUint i=0; i<(TUint)iLanguageList.size(); i++) {
        free(iLanguageList[i]);
    }
    iLanguageList.clear();
}

TUint HeaderAcceptLanguage::ParseQualityValue(const Brx& aBuf)
{
    if (aBuf.Bytes() == 0) {
        return kMaxQuality;
    }
    if (aBuf[0] == '1') {
        return kMaxQuality;
    }
    else if (aBuf[0] != '0') {
        // invalid value, ignore it
        return kMinQuality;
    }
    if (aBuf.Bytes() < 3 || aBuf[1] != '.' || aBuf.Bytes() > kMaxQualityChars) {
        // invalid value, ignore it
        return kMinQuality;
    }

    TUint quality = kMinQuality;
    TUint i;
    for (i=2; i<aBuf.Bytes(); i++) {
        if (!Ascii::IsDigit(aBuf[i])) {
            return 0;
        }
        quality = (quality * 10) + aBuf[i] - '0';
    }
    for (; i<kMaxQualityChars; i++) {
        quality *= 10;
    }
    return quality;
}

void HeaderAcceptLanguage::AddPrioritisedLanguage(std::vector<PrioritisedLanguage>& aList, PrioritisedLanguage& aLanguage)
{
    for (TUint i=0; i<(TUint)aList.size(); i++) {
        if (aLanguage.iPriority > aList[i].iPriority) {
            aList.insert(aList.begin()+i, aLanguage);
            return;
        }
    }
    aList.push_back(aLanguage);
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
    aPublisher.AppendEndpoint(buf);
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
    readerResponse.Read(kReadTimeoutMs);
    const HttpStatus& status = readerResponse.Status();
    if (status != HttpStatus::kOk) {
        LOG2(kDvEvent, kError, "PropertyWriter, http error %u ", status.Code());
        LOG2(kDvEvent, kError, status.Reason());
        LOG2(kDvEvent, kError, "\n");
    }
}


// DviSessionUpnp

DviSessionUpnp::DviSessionUpnp(TIpAddress aInterface, TUint aPort, IRedirector& aRedirector)
    : iInterface(aInterface)
    , iPort(aPort)
    , iRedirector(aRedirector)
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
    iReaderRequest->AddHeader(iHeaderAcceptLanguage);
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
            iReaderRequest->Read(kReadTimeoutMs);
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
    Stack::Mutex().Wait();
    Log::Print("Get - ");
    Log::Print(iReaderRequest->Uri());
    Log::Print("\n");
    Stack::Mutex().Signal();
#endif
    if (iReaderRequest->Version() == Http::eHttp11) {
        if (!iHeaderHost.Received()) {
            Error(HttpStatus::kBadRequest);
        }
    }

    Brn redirectTo;
    if (!iRedirector.RedirectUri(iReaderRequest->Uri(), redirectTo)) {
        DviStack::DeviceMap().WriteResource(iReaderRequest->Uri(), iInterface, iHeaderAcceptLanguage.LanguageList(), *this);
    }
    else {
        iResponseStarted = true;
        iWriterResponse->WriteStatus(HttpStatus::kMovedPermanently, Http::eHttp11);
        IWriterAscii& writerLocation = iWriterResponse->WriteHeaderField(Http::kHeaderLocation);
        writerLocation.Write(Brn("http://"));
        Endpoint endpt(iPort, iInterface);
        Bws<Endpoint::kMaxEndpointBytes> endptBuf;
        endpt.AppendEndpoint(endptBuf);
        writerLocation.Write(endptBuf);
        writerLocation.Write(redirectTo);
        writerLocation.WriteFlush();
        iWriterResponse->WriteFlush();
        iResponseEnded = true;
    }
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

    ParseRequestUri(DviProtocolUpnp::kControlUrlTail, &iInvocationDevice, &iInvocationService);
    if (iInvocationDevice != NULL && iInvocationService != NULL) {
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
    ParseRequestUri(DviProtocolUpnp::kEventUrlTail, &device, &service);
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
    ParseRequestUri(DviProtocolUpnp::kEventUrlTail, &device, &service);
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
    ParseRequestUri(DviProtocolUpnp::kEventUrlTail, &device, &service);
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
	stream.Write(Brn(" UPnP/1.1 ohNet/"));
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
        iInvocationService->Invoke(*this, iHeaderSoapAction.Action());
    }
    catch (InvocationError&) {}
}

TUint DviSessionUpnp::Version() const
{
    return iHeaderSoapAction.Version();
}

TIpAddress DviSessionUpnp::Adapter() const
{
    return iInterface;
}

const char* DviSessionUpnp::ResourceUriPrefix() const
{
    // !!!! should really read this from DvDeviceUpnp rather than duplicating knowledge here
    iResourceUriPrefix.SetBytes(0);
    iResourceUriPrefix.Append("http://");
    Endpoint ep(iPort, iInterface);
    ep.AppendEndpoint(iResourceUriPrefix);
    iResourceUriPrefix.Append("/");
    iResourceUriPrefix.Append(iInvocationDevice->Udn());
    iResourceUriPrefix.Append("/");
    iResourceUriPrefix.Append("Upnp");
    iResourceUriPrefix.Append("/");
    iResourceUriPrefix.Append("resource");
    iResourceUriPrefix.Append("/");
    iResourceUriPrefix.PtrZ();
    return (const char*)iResourceUriPrefix.Ptr();
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
		Bwh writable(value.Bytes()+1);
		if (value.Bytes()) {
			writable.Append(value);
			Converter::FromXmlEscaped(writable);
		}
		writable.PtrZ();
		writable.TransferTo(aString);
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

DviServerUpnp::DviServerUpnp(TUint aPort)
    : iPort(aPort)
{
    Initialise();
}

void DviServerUpnp::Redirect(const Brx& aUriRequested, const Brx& aUriRedirectedTo)
{
    // could store a vector of redirections if required
    Stack::Mutex().Wait();
    iRedirectUriRequested.Set(aUriRequested);
    iRedirectUriRedirectedTo.Set(aUriRedirectedTo);
    Stack::Mutex().Signal();
}

SocketTcpServer* DviServerUpnp::CreateServer(const NetworkAdapter& aNif)
{
    SocketTcpServer* server = new SocketTcpServer("DSVU", iPort, aNif.Address());
    TChar thName[5];
	const TUint numWsThreads = Stack::InitParams().DvNumServerThreads();
    for (TUint i=0; i<numWsThreads; i++) {
        (void)sprintf(&thName[0], "DS%2lu", i);
        server->Add(&thName[0], new DviSessionUpnp(aNif.Address(), server->Port(), *this));
    }
    return server;
}

TBool DviServerUpnp::RedirectUri(const Brx& aUri, Brn& aRedirectTo)
{
    if (aUri == iRedirectUriRequested) {
        aRedirectTo.Set(iRedirectUriRedirectedTo);
        return true;
    }
    return false;
}
