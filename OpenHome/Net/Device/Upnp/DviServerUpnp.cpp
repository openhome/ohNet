#include <OpenHome/Net/Private/DviServerUpnp.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Net/Private/Ssdp.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/DviProtocolUpnp.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Net/Private/XmlParser.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/OsWrapper.h>

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
    if (bytes < Http::kSchemeHttp.Bytes()) {
        THROW(HttpError);
    }
    if (uri.Split(0, Http::kSchemeHttp.Bytes()) != Http::kSchemeHttp) {
        THROW(HttpError);
    }
    parser.Set(uri.Split(Http::kSchemeHttp.Bytes()));
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

SubscriptionDataUpnp::SubscriptionDataUpnp(const Endpoint& aSubscriber, const Brx& aSubscriberPath, const Http::EVersion aHttpVersion)
    : iSubscriber(aSubscriber)
    , iSubscriberPath(aSubscriberPath)
    , iHttpVersion(aHttpVersion)
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

const Http::EVersion SubscriptionDataUpnp::HttpVersion() const
{
    return iHttpVersion;
}

void SubscriptionDataUpnp::Log(IWriter& aWriter) const
{
    aWriter.Write(Brn(", subscriber: "));
    Endpoint::EndpointBuf epBuf;
    iSubscriber.AppendEndpoint(epBuf);
    aWriter.Write(epBuf);
    aWriter.Write(iSubscriberPath);
    aWriter.Write(Brn(" (HTTP/"));
    if (iHttpVersion == Http::eHttp11) {
        aWriter.Write(Brn("1.1"));
    }
    if (iHttpVersion == Http::eHttp10) {
        aWriter.Write(Brn("1.0"));
    }
    if (iHttpVersion == Http::eHttp09) {
        aWriter.Write(Brn("0.9"));
    }
    aWriter.Write(Brn(")"));
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

PropertyWriterUpnp::PropertyWriterUpnp(Environment& aEnv)
    : iEnv(aEnv)
    , iEventBody(kWriteGranularity)
{
    iWriteBuffer = new Sws<kWriteGranularity>(iSocket);
    iWriterEvent = new WriterHttpRequest(*iWriteBuffer);
    SetWriter(iEventBody);
}

void PropertyWriterUpnp::Initialise(const Endpoint& aPublisher, const Endpoint& aSubscriber,
                                    const Brx& aSubscriberPath, Http::EVersion aHttpVersion,
                                    const Brx& aSid, TUint aSequenceNumber)
{
    iPublisher = aPublisher;
    iSubscriber = aSubscriber;
    iSubscriberPath.Set(aSubscriberPath);
    iHttpVersion = aHttpVersion;
    iSid.Set(aSid);
    iSequenceNumber = aSequenceNumber;

    iEventBody.Write("<?xml version=\"1.0\"?>");
    iEventBody.Write("<e:propertyset xmlns:e=\"urn:schemas-upnp-org:event-1-0\">");
}

void PropertyWriterUpnp::Reset()
{
    try {
        iSocket.Close();
    }
    catch (NetworkError&) {}
    iEventBody.Reset();
}

void PropertyWriterUpnp::Connect()
{
#if 0
    Endpoint::AddressBuf buf;
    iSubscriber.AppendAddress(buf);
    Log::Print("PropertyWriterUpnp connecting to %s\n", buf.Ptr());
#endif
    iSocket.Open(iEnv);
    iSocket.Connect(iSubscriber, iEnv.InitParams()->TcpConnectTimeoutMs());
    //iSocket.LogVerbose(true);
}

void PropertyWriterUpnp::WriteHeaders(TUint aContentLength)
{
    iWriterEvent->WriteMethod(kUpnpMethodNotify, iSubscriberPath, iHttpVersion);

    IWriterAscii& writer = iWriterEvent->WriteHeaderField(Http::kHeaderHost);
    Endpoint::EndpointBuf buf;
    iPublisher.AppendEndpoint(buf);
    writer.Write(buf);
    writer.WriteFlush();

    iWriterEvent->WriteHeader(Http::kHeaderContentType, Brn("text/xml; charset=\"utf-8\""));
    Http::WriteHeaderContentLength(*iWriterEvent, aContentLength);
    iWriterEvent->WriteHeader(kUpnpHeaderNt, Brn("upnp:event"));
    iWriterEvent->WriteHeader(kUpnpHeaderNts, Brn("upnp:propchange"));

    writer = iWriterEvent->WriteHeaderField(HeaderSid::kHeaderSid);
    writer.Write(HeaderSid::kFieldSidPrefix);
    writer.Write(iSid);
    writer.WriteFlush();

    writer = iWriterEvent->WriteHeaderField(kUpnpHeaderSeq);
    writer.WriteUint(iSequenceNumber);
    writer.WriteFlush();

    iWriterEvent->WriteHeader(Http::kHeaderConnection, Http::kConnectionClose);
    iWriterEvent->WriteFlush();
}

PropertyWriterUpnp::~PropertyWriterUpnp()
{
    delete iWriterEvent;
    delete iWriteBuffer;
    try {
        iSocket.Close();
    }
    catch (NetworkError&) {}
}

void PropertyWriterUpnp::PropertyWriteEnd()
{
    iEventBody.Write("</e:propertyset>");

    Endpoint::AddressBuf subscriberAddress;
    iSubscriber.AppendAddress(subscriberAddress);
    try {
        Connect();
        //iSocket.LogVerbose(true);
        const Brx& body = iEventBody.Buffer();
        WriteHeaders(body.Bytes());
        iSocket.Write(body);
    }
    catch (NetworkTimeout&) {
        LOG_ERROR(kDvEvent, "PropertyWriterUpnp - NetworkTimeout eventing to %.*s\n", PBUF(subscriberAddress));
        throw;
    }
    catch (NetworkError&) {
        LOG_ERROR(kDvEvent, "PropertyWriterUpnp - NetworkError eventing to %.*s\n", PBUF(subscriberAddress));
        THROW(WriterError);
    }
    catch (HttpError&) {
        LOG_ERROR(kDvEvent, "PropertyWriterUpnp - HttpError eventing to %.*s\n", PBUF(subscriberAddress));
        THROW(WriterError);
    }
    catch (WriterError&) {
        LOG_ERROR(kDvEvent, "PropertyWriterUpnp - WriterError eventing to %.*s\n", PBUF(subscriberAddress));
        throw;
    }

    Srs<kMaxResponseBytes> readBuffer(iSocket);
    ReaderUntilS<kMaxResponseBytes> readerUntil(readBuffer);
    ReaderHttpResponse readerResponse(iEnv, readerUntil);
    readerResponse.Read(kReadTimeoutMs);
    const HttpStatus& status = readerResponse.Status();
    if (status != HttpStatus::kOk) {
        const Brx& reason = status.Reason();
        LOG_ERROR(kDvEvent, "PropertyWriter, http error %u %.*s\n", status.Code(), PBUF(reason));
    }
}


// PropertyWriterFactory

PropertyWriterFactory::PropertyWriterFactory(DvStack& aDvStack, TIpAddress aAdapter, TUint aPort)
    : iRefCount(1)
    , iDvStack(aDvStack)
    , iEnabled(true)
    , iAdapter(aAdapter)
    , iPort(aPort)
    , iSubscriptionMapLock("DMSL")
    , iFifo(aDvStack.Env().InitParams()->DvNumPublisherThreads())
{
    const TUint numWriters = iFifo.Slots();
    for (TUint i=0; i<numWriters; i++) {
        iFifo.Write(new PropertyWriterUpnp(aDvStack.Env()));
    }
}

TUint PropertyWriterFactory::Adapter() const
{
    return iAdapter;
}

void PropertyWriterFactory::SubscriptionAdded(DviSubscription& aSubscription)
{
    {
        AutoMutex _(iSubscriptionMapLock);
        Brn sidBuf(aSubscription.Sid());
        iSubscriptionMap.insert(std::pair<Brn, DviSubscription*>(sidBuf, &aSubscription));
    }
    AddRef();
}

void PropertyWriterFactory::Disable()
{
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    iEnabled = false;
    lock.Signal();
    std::vector<DviSubscription*> subscriptions;
    {
        AutoMutex _(iSubscriptionMapLock);
        SubscriptionMap::iterator it = iSubscriptionMap.begin();
        if (it != iSubscriptionMap.end()) {
            DviSubscription* subscription = it->second;
            if (subscription->TryAddRef()) {
                subscriptions.push_back(subscription);
            }
            it++;
        }
    }
    for (TUint i=0; i<(TUint)subscriptions.size(); i++) {
        DviSubscription* subscription = subscriptions[i];
        subscription->Remove();
        subscription->RemoveRef();
    }
    RemoveRef();
}

IPropertyWriter* PropertyWriterFactory::ClaimWriter(const IDviSubscriptionUserData* aUserData, const Brx& aSid, TUint aSequenceNumber)
{
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    TBool enabled = iEnabled;
    lock.Signal();
    if (!enabled) {
        return NULL;
    }
    Endpoint publisher(iPort, iAdapter);
    const SubscriptionDataUpnp* data = reinterpret_cast<const SubscriptionDataUpnp*>(aUserData->Data());
    PropertyWriterUpnp* writer = iFifo.Read();
    writer->Initialise(publisher, data->Subscriber(), data->SubscriberPath(), data->HttpVersion(), aSid, aSequenceNumber);
    return writer;
}

void PropertyWriterFactory::ReleaseWriter(IPropertyWriter* aWriter)
{
    PropertyWriterUpnp* writer = static_cast<PropertyWriterUpnp*>(aWriter);
    writer->Reset();
    iFifo.Write(writer);
}

void PropertyWriterFactory::NotifySubscriptionCreated(const Brx& /*aSid*/)
{
}

void PropertyWriterFactory::NotifySubscriptionDeleted(const Brx& aSid)
{
    AddRef();
    {
        AutoMutex _(iSubscriptionMapLock);
        Brn sid(aSid);
        SubscriptionMap::iterator it = iSubscriptionMap.find(sid);
        if (it != iSubscriptionMap.end()) {
            iSubscriptionMap.erase(it);
            RemoveRef();
        }
    }
    RemoveRef();
}

void PropertyWriterFactory::NotifySubscriptionExpired(const Brx& /*aSid*/)
{
}

void PropertyWriterFactory::LogUserData(IWriter& aWriter, const IDviSubscriptionUserData& aUserData)
{
    const SubscriptionDataUpnp* data = reinterpret_cast<const SubscriptionDataUpnp*>(aUserData.Data());
    data->Log(aWriter);
}

PropertyWriterFactory::~PropertyWriterFactory()
{
    const TUint numWriters = iFifo.Slots();
    for (TUint i=0; i<numWriters; i++) {
        delete iFifo.Read();
    }
}

void PropertyWriterFactory::AddRef()
{
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    iRefCount++;
    lock.Signal();
}

void PropertyWriterFactory::RemoveRef()
{
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    iRefCount--;
    TBool dead = (iRefCount == 0);
    lock.Signal();
    if (dead) {
        delete this;
    }
}


// DviSessionUpnp

DviSessionUpnp::DviSessionUpnp(DvStack& aDvStack, TIpAddress aInterface, TUint aPort,
                               PropertyWriterFactory& aPropertyWriterFactory,
                               IPathMapperUpnp& aPathMapper, IRedirector& aRedirector)
    : iDvStack(aDvStack)
    , iInterface(aInterface)
    , iPort(aPort)
    , iPropertyWriterFactory(aPropertyWriterFactory)
    , iPathMapper(aPathMapper)
    , iRedirector(aRedirector)
    , iShutdownSem("DSUS", 1)
{
    iReadBuffer = new Srs<1024>(*this);
    iReaderUntil = new ReaderUntilS<4096>(*iReadBuffer);
    iReaderRequest = new ReaderHttpRequest(aDvStack.Env(), *iReaderUntil);
    iDechunker = new ReaderHttpChunked(*iReaderUntil);
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
    iReaderRequest->AddHeader(iHeaderTransferEncoding);
    iReaderRequest->AddHeader(iHeaderConnection);
    iReaderRequest->AddHeader(iHeaderExpect);
    iReaderRequest->AddHeader(iHeaderSoapAction);
    iReaderRequest->AddHeader(iHeaderSid);
    iReaderRequest->AddHeader(iHeaderTimeout);
    iReaderRequest->AddHeader(iHeaderNt);
    iReaderRequest->AddHeader(iHeaderCallback);
    iReaderRequest->AddHeader(iHeaderAcceptLanguage);
    iReaderRequest->AddHeader(iHeaderUserAgent);
}

DviSessionUpnp::~DviSessionUpnp()
{
    Interrupt(true);
    iShutdownSem.Wait();
    delete iWriterResponse;
    delete iWriterBuffer;
    delete iWriterChunked;
    delete iDechunker;
    delete iReaderRequest;
    delete iReaderUntil;
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
    iSoapRequest.SetBytes(0);
    iDechunker->SetChunked(false);
    iDechunker->ReadFlush();
    iResponseStarted = false;
    iResponseEnded = false;
    Brn method;
    Brn reqUri;
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
        method.Set(iReaderRequest->Method());
        iReaderRequest->UnescapeUri();

        reqUri.Set(iReaderRequest->Uri());
        LOG(kDvDevice, "Method: %.*s, uri: %.*s\n", PBUF(method), PBUF(reqUri));

        iDvStack.NotifyControlPointUsed(iHeaderUserAgent.UserAgent());

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
        LOG(/*kDvDevice|*/kDvEvent, "HttpError handling %.*s for %.*s\n", PBUF(method), PBUF(reqUri));
        if (iErrorStatus == &HttpStatus::kOk) {
            iErrorStatus = &HttpStatus::kBadRequest;
        }
    }
    catch (ReaderError&) {
        if(OpenHome::Debug::TestLevel(OpenHome::Debug::kDvDevice|OpenHome::Debug::kDvDevice)) {
            Log::Print("ReaderError handling %.*s for %.*s\n", PBUF(method), PBUF(reqUri));
        }
        
        if (iErrorStatus == &HttpStatus::kOk) {
            iErrorStatus = &HttpStatus::kBadRequest;
        }
    }
    catch (WriterError&) {
        if(OpenHome::Debug::TestLevel(OpenHome::Debug::kDvDevice|OpenHome::Debug::kDvDevice)) {
            Log::Print("WriterError handling %.*s for %.*s\n", PBUF(method), PBUF(reqUri));
        }
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
    catch (WriterError&) {
        if(OpenHome::Debug::TestLevel(OpenHome::Debug::kDvDevice|OpenHome::Debug::kDvDevice)) {
           Log::Print("WriterError(2) handling %.*s for %.*s\n", PBUF(method), PBUF(reqUri));
        }
    }
    iShutdownSem.Signal();
}

void DviSessionUpnp::Error(const HttpStatus& aStatus)
{
    iErrorStatus = &aStatus;
    THROW(HttpError);
}

void DviSessionUpnp::Get()
{
    if (iReaderRequest->Version() == Http::eHttp11) {
        if (!iHeaderHost.Received()) {
            Error(HttpStatus::kBadRequest);
        }
    }

    Brn redirectTo;
    if (!iRedirector.RedirectUri(iReaderRequest->Uri(), redirectTo)) {
        iDvStack.DeviceMap().WriteResource(iReaderRequest->Uri(), iInterface, iHeaderAcceptLanguage.LanguageList(), *this);
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
}

void DviSessionUpnp::Post()
{
    const Brx& action = iHeaderSoapAction.Action();
    LOG(kDvInvocation, "UPnP Action called: %.*s\n", PBUF(action));

    if (iReaderRequest->Version() == Http::eHttp11) {
        if (!iHeaderHost.Received()) {
            Error(HttpStatus::kBadRequest);
        }
    }

    ParseRequestUri(DviProtocolUpnp::kControlUrlTail, &iInvocationDevice, &iInvocationService);
    AutoDeviceRef d(iInvocationDevice);
    if (iInvocationDevice != NULL && iInvocationService != NULL) {
        AutoServiceRef s(iInvocationService);
        try {
            if (iHeaderExpect.Continue()) {
                iWriterResponse->WriteStatus(HttpStatus::kContinue, Http::eHttp11);
                iWriterResponse->WriteFlush();
            }
            if (iHeaderContentLength.ContentLength() != 0) {
                TUint remaining = iHeaderContentLength.ContentLength();
                do {
                    Brn buf = iReaderUntil->Read(remaining);
                    iSoapRequest.Append(buf);
                    remaining -= buf.Bytes();
                } while (remaining > 0);
            }
            else if (!iHeaderTransferEncoding.IsChunked()) {
                iErrorStatus = &HttpStatus::kLengthRequired;
                THROW(HttpError);
            }
            else {
                iDechunker->SetChunked(true);
                for (;;) {
                    Brn buf = iDechunker->Read(kMaxRequestBytes); // expect much less than this to be returned
                    if (buf.Bytes() == 0) { // end of stream
                        break;
                    }
                    if (iSoapRequest.Bytes() + buf.Bytes() > iSoapRequest.MaxBytes()) {
                        iErrorStatus = &HttpStatus::kRequestEntityTooLarge;
                        THROW(ReaderError);
                    }
                    iSoapRequest.Append(buf);
                }
            }

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
    {
        Endpoint::EndpointBuf ep;
        iHeaderCallback.Endpoint().AppendEndpoint(ep);
        const Brx& callback = iHeaderCallback.Uri();
        LOG(kDvEvent, "Subscription request from %s%.*s for %.*s\n",
                      reinterpret_cast<const TChar*>(ep.Ptr()),
                      PBUF(callback),
                      PBUF(iReaderRequest->Uri()));
    }
    if (iHeaderSid.Received()) {
        try {
            Renew();
        }
        catch (DvSubscriptionError&) {
            LOG_ERROR(kDvEvent, "DvSubscriptionError\n");
            iErrorStatus = &HttpStatus::kPreconditionFailed;
        }
        return;
    }

    if (!iHeaderCallback.Received() || !iHeaderNt.Received()) {
        Error(HttpStatus::kPreconditionFailed);
    }
    DviDevice* device;
    DviService* service;
    ParseRequestUri(DviProtocolUpnp::kEventUrlTail, &device, &service);
    AutoDeviceRef d(device);
    AutoServiceRef s(service);
    if (device == NULL || !device->Enabled() || service == NULL) {
        Error(HttpStatus::kPreconditionFailed);
    }
    TUint duration = (iHeaderTimeout.Received()? iHeaderTimeout.Timeout() : iDvStack.Env().InitParams()->DvMaxUpdateTimeSecs());
    Brh sid;
    device->CreateSid(sid);
    SubscriptionDataUpnp* data = new SubscriptionDataUpnp(iHeaderCallback.Endpoint(), iHeaderCallback.Uri(), iReaderRequest->Version());
    DviSubscription* subscription = new DviSubscription(iDvStack, *device, iPropertyWriterFactory, data, sid);
    iPropertyWriterFactory.SubscriptionAdded(*subscription);
    iDvStack.SubscriptionManager().AddSubscription(*subscription);
    subscription->SetDuration(duration);

    try {
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
    }
    catch (AssertionFailed&) {
        throw;
    }
    catch (Exception&) {
        iDvStack.SubscriptionManager().RemoveSubscription(*subscription);
        subscription->RemoveRef();
        throw;
    }

    {
        const Brx& callback2 = iHeaderCallback.Uri();
        const Brx& sid2 = subscription->Sid();
        LOG(kDvEvent, "Subscription complete for  %.*s, sid is %.*s\n", PBUF(callback2), PBUF(sid2));
    }

    // Start subscription, prompting delivery of the first update (covering all state variables)
    service->AddSubscription(subscription);
}

void DviSessionUpnp::Unsubscribe()
{
    if (!iHeaderSid.Received()) {
        LOG_ERROR(kDvEvent, "Unsubscribe failed - no sid\n");
        Error(HttpStatus::kPreconditionFailed);
    }
    const Brx& sid = iHeaderSid.Sid();
    LOG(kDvEvent, "Unsubscribe request: %.*s in thread %.*s\n",
                  PBUF(sid), PBUF(Thread::CurrentThreadName()));

    DviDevice* device;
    DviService* service;
    ParseRequestUri(DviProtocolUpnp::kEventUrlTail, &device, &service);
    AutoDeviceRef d(device);
    AutoServiceRef s(service);
    if (device == NULL  || !device->Enabled()|| service == NULL) {
        LOG_ERROR(kDvEvent, "Unsubscribe failed - device=%p, service=%p\n", device, service);
        Error(HttpStatus::kPreconditionFailed);
    }
    DviSubscription* subscription = iDvStack.SubscriptionManager().Find(sid);
    if (subscription == NULL) {
        LOG_ERROR(kDvEvent, "Unsubscribe failed - couldn't match sid %.*s\n", PBUF(sid));
        Error(HttpStatus::kPreconditionFailed);
    }
    service->RemoveSubscription(sid);
    subscription->RemoveRef();

    if (iHeaderExpect.Continue()) {
        iWriterResponse->WriteStatus(HttpStatus::kContinue, Http::eHttp11);
        iWriterResponse->WriteFlush();
    }
    iResponseStarted = true;
    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eHttp11);
    iWriterResponse->WriteHeader(Http::kHeaderConnection, Http::kConnectionClose);
    iWriterResponse->WriteFlush();
    iResponseEnded = true;

    LOG(kDvEvent, "Unsubscribe complete: %.*s\n", PBUF(sid));
}

void DviSessionUpnp::Renew()
{
    const Brx& sid = iHeaderSid.Value();
    LOG(kDvEvent, "Renew subscription (request): %.*s for %u secs\n", PBUF(sid), iHeaderTimeout.Timeout());

    if (iHeaderCallback.Received() || iHeaderNt.Received()) {
        Error(HttpStatus::kBadRequest);
    }

    DviDevice* device;
    DviService* service;
    ParseRequestUri(DviProtocolUpnp::kEventUrlTail, &device, &service);
    AutoDeviceRef d(device);
    AutoServiceRef s(service);
    if (device == NULL  || !device->Enabled()|| service == NULL) {
        Error(HttpStatus::kPreconditionFailed);
    }

    DviSubscription* subscription = iDvStack.SubscriptionManager().Find(iHeaderSid.Sid());
    if (subscription == NULL) {
        Error(HttpStatus::kPreconditionFailed);
    }
    TUint duration = iHeaderTimeout.Timeout();
    try {
        subscription->Renew(duration);
    }
    catch (...) {
        subscription->RemoveRef();
        throw;
    }
    subscription->RemoveRef();

    iResponseStarted = true;
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
    iResponseEnded = true;

    LOG(kDvEvent, "Renew subscription (complete): %.*s for %u secs\n", PBUF(sid), duration);
}

void DviSessionUpnp::ParseRequestUri(const Brx& aUrlTail, DviDevice** aDevice, DviService** aService)
{
    Parser parser(iReaderRequest->Uri());
    if (iPathMapper.TryMapPath(iReaderRequest->Uri(), iMappedRequestUri)) {
        parser.Set(iMappedRequestUri);
    }

    Brn tmp = parser.Next('/');
    if (tmp.Bytes() > 0) {
        Error(HttpStatus::kPreconditionFailed);
    }
    Brn udn = parser.Next('/');
    DviDevice* device = iDvStack.DeviceMap().Find(udn);
    *aDevice = device;
    if (device == NULL || !device->Enabled()) {
        Error(HttpStatus::kPreconditionFailed);
    }
    Brn serviceName = parser.Next('/');
    if (parser.Remaining() != aUrlTail) {
        Error(HttpStatus::kPreconditionFailed);
    }
    *aService = device->ServiceReference(serviceName);
}

void DviSessionUpnp::WriteServerHeader(IWriterHttpHeader& aWriter)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Brn("SERVER"));
    TUint major, minor;
    Brn osName = Os::GetPlatformNameAndVersion(iDvStack.Env().OsCtx(), major, minor);
    stream.Write(osName);
    stream.Write('/');
    stream.WriteUint(major);
    stream.Write('.');
    stream.WriteUint(minor);
    stream.Write(Brn(" UPnP/1.1 ohNet/"));
    iDvStack.Env().GetVersion(major, minor);
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
        if (iReaderRequest->Version() == Http::eHttp11) { 
            iWriterResponse->WriteHeader(Http::kHeaderTransferEncoding, Http::kTransferEncodingChunked);
        }
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
        if (iReaderRequest->Version() == Http::eHttp11) { 
            iWriterChunked->SetChunked(true);
        }
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

Endpoint DviSessionUpnp::ClientEndpoint() const
{
    Endpoint ep(SocketTcpSession::ClientEndpoint());
    return ep;
}

const Brx& DviSessionUpnp::ClientUserAgent() const
{
    if (!iHeaderUserAgent.Received()) {
        return Brx::Empty();
    }
    return iHeaderUserAgent.UserAgent();
}

void DviSessionUpnp::InvocationReadStart()
{
    try {
        Brn envelope = XmlParserBasic::Find("Envelope", iSoapRequest);
        Brn body = XmlParserBasic::Find("Body", envelope);
        Brn args = XmlParserBasic::Find(iHeaderSoapAction.Action(), body);
        iSoapRequest.Replace(args);
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
        InvocationReportError(402, Brn("Invalid Args"));
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
        InvocationReportError(402, Brn("Invalid Args"));
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
        InvocationReportError(402, Brn("Invalid Args"));
    }
    catch (AsciiError&) {
        InvocationReportError(402, Brn("Invalid Args"));
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
        InvocationReportError(402, Brn("Invalid Args"));
    }
    catch (AsciiError&) {
        InvocationReportError(402, Brn("Invalid Args"));
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
        InvocationReportError(402, Brn("Invalid Args"));
    }
}

void DviSessionUpnp::InvocationReadEnd()
{
    iSoapRequest.Replace(Brx::Empty());
}

void DviSessionUpnp::InvocationReportErrorNoThrow(TUint aCode, const Brx& aDescription)
{
    if (iResponseStarted) {
        if (!iResponseEnded) {
            InvocationWriteEnd();
            iResponseEnded = true;
        }
        return;
    }

    const Brx& action = iHeaderSoapAction.Action();
    LOG(kDvInvocation, "Failure processing action: %.*s\n", PBUF(action));

    iResponseStarted = true;
    iWriterResponse->WriteStatus(HttpStatus::kInternalServerError, Http::eHttp11);
    iWriterResponse->WriteHeader(kUpnpHeaderExt, Brx::Empty());
    iWriterResponse->WriteHeader(Http::kHeaderContentType, Brn("text/xml; charset=\"utf-8\""));
    WriteServerHeader(*iWriterResponse);
    if (iReaderRequest->Version() == Http::eHttp11) { 
        iWriterResponse->WriteHeader(Http::kHeaderTransferEncoding, Http::kTransferEncodingChunked);
    }
    iWriterResponse->WriteHeader(Http::kHeaderConnection, Http::kConnectionClose);
    iWriterResponse->WriteFlush();

    if (iReaderRequest->Version() == Http::eHttp11) { 
        iWriterChunked->SetChunked(true);
    }

    iWriterBuffer->Write(Brn("<?xml version=\"1.0\"?>"));
    iWriterBuffer->Write(Brn("<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">"));
    iWriterBuffer->Write(Brn("<s:Body>"));
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
    if (iReaderRequest->Version() == Http::eHttp11) { 
        iWriterResponse->WriteHeader(Http::kHeaderTransferEncoding, Http::kTransferEncodingChunked);
    }
    iWriterResponse->WriteHeader(Http::kHeaderConnection, Http::kConnectionClose);
    iWriterResponse->WriteFlush();

    if (iReaderRequest->Version() == Http::eHttp11) { 
        iWriterChunked->SetChunked(true);
    }

    iWriterBuffer->Write(Brn("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:"));
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
    iWriterBuffer->Write(aValue ? Brn(">1</") : Brn(">0</"));
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

    const Brx& action = iHeaderSoapAction.Action();
    LOG(kDvInvocation, "Completed UPnP action: %.*s\n", PBUF(action));
}


// DviServerUpnp

DviServerUpnp::DviServerUpnp(DvStack& aDvStack, TUint aPort)
    : DviServer(aDvStack)
    , iPort(aPort)
    , iPathMapper(NULL)
{
    Initialise();
}

DviServerUpnp::~DviServerUpnp()
{
    Deinitialise();
    delete iPathMapper;
}

void DviServerUpnp::SetPathMapper(IPathMapperUpnp* aPathMapper)
{
    ASSERT(iPathMapper == NULL);
    ASSERT(aPathMapper != NULL);
    iPathMapper = aPathMapper;
}

void DviServerUpnp::Redirect(const Brx& aUriRequested, const Brx& aUriRedirectedTo)
{
    // could store a vector of redirections if required
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    iRedirectUriRequested.Set(aUriRequested);
    iRedirectUriRedirectedTo.Set(aUriRedirectedTo);
    lock.Signal();
}

SocketTcpServer* DviServerUpnp::CreateServer(const NetworkAdapter& aNif)
{
    SocketTcpServer* server = new SocketTcpServer(iDvStack.Env(), "UpnpServer", iPort, aNif.Address());
    PropertyWriterFactory* pwf = new PropertyWriterFactory(iDvStack, aNif.Address(), server->Port());
    iPropertyWriterFactories.push_back(pwf);
    const TUint numWsThreads = iDvStack.Env().InitParams()->DvNumServerThreads();
    for (TUint i=0; i<numWsThreads; i++) {
        Bws<Thread::kMaxNameBytes+1> thName;
        thName.AppendPrintf("UpnpSession %d", i);
        thName.PtrZ();
        server->Add((const TChar*)thName.Ptr(), new DviSessionUpnp(iDvStack, aNif.Address(), server->Port(), *pwf, *this, *this));
    }
    return server;
}

void DviServerUpnp::NotifyServerDeleted(TIpAddress aInterface)
{
    for (std::vector<PropertyWriterFactory*>::iterator it=iPropertyWriterFactories.begin(); it!=iPropertyWriterFactories.end(); ++it) {
        if ((*it)->Adapter() == aInterface) {
            (*it)->Disable();
            iPropertyWriterFactories.erase(it);
            break;
        }
    }
}

TBool DviServerUpnp::TryMapPath(const Brx& aReqPath, Bwx& aMappedPath)
{
    if (iPathMapper == NULL) {
        return false;
    }
    return iPathMapper->TryMapPath(aReqPath, aMappedPath);
}

TBool DviServerUpnp::RedirectUri(const Brx& aUri, Brn& aRedirectTo)
{
    if (aUri == iRedirectUriRequested) {
        aRedirectTo.Set(iRedirectUriRedirectedTo);
        return true;
    }
    return false;
}
