#include <ProtocolUpnp.h>
#include <Debug.h>
#include <XmlParser.h>
#include <Parser.h>
#include <Error.h>
#include <Converter.h>
#include <Stack.h>
#include <CpiSubscription.h>
#include <Subscription.h>

using namespace Zapp;

// InvocationUpnp

InvocationUpnp::InvocationUpnp(Invocation& aInvocation)
    : iInvocation(aInvocation)
    , iReadBuffer(iSocket)
    , iReaderResponse(iReadBuffer)
{
}

InvocationUpnp::~InvocationUpnp()
{
    iInvocation.SetInterruptHandler(NULL);
    iSocket.Close();
}

void InvocationUpnp::Invoke(const Uri& aUri)
{
    LOG(kService, "> InvocationUpnp::Invoke (%p, action ", &iInvocation);
    LOG(kService, iInvocation.Action().Name());
    LOG(kService, ")\n");

    iSocket.Open();
    WriteRequest(aUri);
    iInvocation.SetInterruptHandler(this);
    ReadResponse();

    LOG(kService, "< InvocationUpnp::Invoke (%p, action ", &iInvocation);
    LOG(kService, iInvocation.Action().Name());
    LOG(kService, ")\n");
}

void InvocationUpnp::WriteServiceType(IWriterAscii& aWriter, const Invocation& aInvocation)
{
    const ServiceType& serviceType = aInvocation.ServiceType();
    aWriter.Write(serviceType.FullName());
}

void InvocationUpnp::WriteRequest(const Uri& aUri)
{
    Sws<1024> writeBuffer(iSocket);
    WriterHttpRequest writerRequest(writeBuffer);
    Bwh body;

    try {
        Endpoint endpoint(aUri.Port(), aUri.Host());
        TUint timeout = Stack::InitParams().TcpConnectTimeoutMs();
        iSocket.Connect(endpoint, timeout);
    }
    catch (NetworkTimeout&) {
        iInvocation.SetError(Error::eSocket, Error::eCodeTimeout, Error::kDescriptionSocketTimeout);
        THROW(NetworkTimeout);
    }

    try {
        InvocationBodyWriter::Write(iInvocation, body);
        WriteHeaders(writerRequest, aUri, body.Bytes());
        writeBuffer.Write(body);
        writeBuffer.WriteFlush();
    }
    catch (WriterError) {
        iInvocation.SetError(Error::eHttp, Error::kCodeUnknown, Error::kDescriptionUnknown);
        THROW(WriterError);
    }
}

void InvocationUpnp::ReadResponse()
{
    OutputProcessorUpnp outputProcessor;
    HttpHeaderContentLength headerContentLength;
    HttpHeaderTransferEncoding headerTransferEncoding;
    Bwh entity;

    iReaderResponse.AddHeader(headerContentLength);
    iReaderResponse.AddHeader(headerTransferEncoding);
    iReaderResponse.Read();
    const HttpStatus& status = iReaderResponse.Status();
    if (status != HttpStatus::kOk) {
        LOG2(kService, kError, "InvocationUpnp::ReadResponse, http error %u ", status.Code());
        LOG2(kService, kError, status.Reason());
        LOG2(kService, kError, "\n");
        if (status != HttpStatus::kInternalServerError) {
            iInvocation.SetError(Error::eHttp, status.Code(), status.Reason());
            THROW(HttpError);
        }
    }

    if (headerTransferEncoding.IsChunked()) {
        ReaderHttpChunked dechunker(iReadBuffer);
        dechunker.Read();
        dechunker.TransferTo(entity);
    }
    else {
        TUint length = headerContentLength.ContentLength();
        if (length == 0) {
            THROW(HttpError);
        }
        entity.Grow(length);
        while (length > 0) {
            TUint readBytes = (length<kMaxReadBytes? length : kMaxReadBytes);
            entity.Append(iReadBuffer.Read(readBytes));
            length -= readBytes;
        }
    }

    if (status == HttpStatus::kInternalServerError) {
        Brn envelope = XmlParserBasic::Find("Envelope", entity);
        Brn body = XmlParserBasic::Find("Body", envelope);
        Brn fault = XmlParserBasic::Find("Fault", body);
        Brn detail = XmlParserBasic::Find("detail", fault);
        Brn code = XmlParserBasic::Find("errorCode", detail);
        Brn description = XmlParserBasic::Find("errorDescription", detail);
        iInvocation.SetError(Error::eUpnp, Ascii::Uint(code), description);
        THROW(HttpError);
    }

    const Invocation::VectorArguments& outArgs = iInvocation.OutputArguments();
    const TUint count = outArgs.size();
    Brn envelope = XmlParserBasic::Find("Envelope", entity);
    Brn body = XmlParserBasic::Find("Body", envelope);
    const Brn responseTagTrailer("Response");
    const Brx& actionName = iInvocation.Action().Name();
    TUint len = actionName.Bytes() + responseTagTrailer.Bytes();
    Bwh responseTag(len);
    responseTag.Append(actionName);
    responseTag.Append(responseTagTrailer);
    Brn response = XmlParserBasic::Find(responseTag, body);
    for (TUint i=0; i<count; i++) {
        const Brx& name = outArgs[i]->Parameter().Name();
        Brn value = XmlParserBasic::Find(name, response);
        outArgs[i]->ProcessOutput(outputProcessor, value);
    }
}

void InvocationUpnp::WriteHeaders(WriterHttpRequest& aWriterRequest, const Uri& aUri, TUint aBodyBytes)
{
    const Brn kContentType("text/xml; charset=\"utf-8\"");
    const Brn kSoapAction("SOAPACTION");

    aWriterRequest.WriteMethod(Http::kMethodPost, aUri.Path(), Http::eHttp10);

    Http::WriteHeaderHostAndPort(aWriterRequest, aUri);
    Http::WriteHeaderContentLength(aWriterRequest, aBodyBytes);
    Http::WriteHeaderContentType(aWriterRequest, kContentType);

    IWriterAscii& writerField = aWriterRequest.WriteHeaderField(kSoapAction);
    writerField.Write('\"');
    WriteServiceType(writerField, iInvocation);
    writerField.Write('#');
    writerField.Write(iInvocation.Action().Name());
    writerField.Write('\"');
    writerField.WriteNewline();

    writerField.WriteNewline();
}

void InvocationUpnp::Interrupt()
{
    /* Assumes that interrupting the socket is always safe, regardless of whether we're
       using it or one of its stream/http wrappers */
    iSocket.Interrupt(true);
}


// InvocationBodyWriter

void InvocationBodyWriter::Write(const Invocation& aInvocation, Bwh& aBody)
{
    InvocationBodyWriter self;
    self.Write(aInvocation);
    self.iBody.TransferTo(aBody);
}

InvocationBodyWriter::InvocationBodyWriter()
    : iBody(kBufferGranularity)
    , iWriteBuffer(iBody)
    , iWriterAscii(iWriteBuffer)
{
}

void InvocationBodyWriter::Write(const Invocation& aInvocation)
{
    const Brn kXmlVers("<?xml version=\"1.0\"?>");
    const Brn kEnvelopeOpen("<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/"
                            "\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">");
    const Brn kEnvelopeClose("</s:Envelope>");
    const Brn kBodyOpen("<s:Body>");
    const Brn kBodyClose("</s:Body>");
    const Brn kActionOpenStart("<u:");
    const Brn kActionNs(" xmlns:u=\"");
    const Brn kActionCloseStart("</u:");

    iWriteBuffer.Write(kXmlVers);
    iWriterAscii.WriteNewline();
    iWriteBuffer.Write(kEnvelopeOpen);
    iWriterAscii.WriteNewline();
    iWriteBuffer.Write(kBodyOpen);
    iWriterAscii.WriteNewline();
    iWriteBuffer.Write(kActionOpenStart);
    iWriteBuffer.Write(aInvocation.Action().Name());
    iWriteBuffer.Write(kActionNs);
    InvocationUpnp::WriteServiceType(iWriterAscii, aInvocation);
    iWriteBuffer.Write('\"');
    iWriteBuffer.Write('>');
    iWriterAscii.WriteNewline();
    const Invocation::VectorArguments& inArgs = aInvocation.InputArguments();
    const TUint count = inArgs.size();
    for (TUint i=0; i<count; i++) {
        iWriteBuffer.Write('<');
        const Brx& argName = inArgs[i]->Parameter().Name();
        iWriteBuffer.Write(argName);
        iWriteBuffer.Write('>');
        inArgs[i]->ProcessInput(*this);
        iWriteBuffer.Write('<');
        iWriteBuffer.Write('/');
        iWriteBuffer.Write(argName);
        iWriteBuffer.Write('>');
        iWriterAscii.WriteNewline();
    }
    iWriteBuffer.Write(kActionCloseStart);
    iWriteBuffer.Write(aInvocation.Action().Name());
    iWriteBuffer.Write('>');
    iWriterAscii.WriteNewline();
    iWriteBuffer.Write(kBodyClose);
    iWriterAscii.WriteNewline();
    iWriteBuffer.Write(kEnvelopeClose);
    iWriterAscii.WriteNewline();
    iWriteBuffer.WriteFlush();
}

void InvocationBodyWriter::ProcessString(const Brx& aVal)
{
    Converter::ToXmlEscaped(iWriteBuffer, aVal);
}

void InvocationBodyWriter::ProcessInt(TInt aVal)
{
    iWriterAscii.WriteInt(aVal);
}

void InvocationBodyWriter::ProcessUint(TUint aVal)
{
    iWriterAscii.WriteUint(aVal);
}

void InvocationBodyWriter::ProcessBool(TBool aVal)
{
    iWriterAscii.WriteUint((aVal? 1 : 0));
}

void InvocationBodyWriter::ProcessBinary(const Brx& aVal)
{
    Converter::ToBase64(iWriteBuffer, aVal);
}


// EventUpnp

EventUpnp::EventUpnp(Subscription& aSubscription)
    : iSubscription(aSubscription)
{
}

EventUpnp::~EventUpnp()
{
    iSubscription.SetInterruptHandler(NULL);
    iSocket.Close();
}

void EventUpnp::Subscribe(const Uri& aPublisher, const Uri& aSubscriber, TUint& aDurationSecs)
{
    iSocket.Open();
    iSubscription.SetInterruptHandler(this);
    Endpoint endpoint(aPublisher.Port(), aPublisher.Host());
    TUint timeout = Stack::InitParams().TcpConnectTimeoutMs();
    iSocket.Connect(endpoint, timeout);

    SubscribeWriteRequest(aPublisher, aSubscriber, aDurationSecs);
    Brh sid;
    SubscribeReadResponse(sid, aDurationSecs);
    iSubscription.SetSid(sid);
}

void EventUpnp::RenewSubscription(const Uri& aPublisher, TUint& aDurationSecs)
{
    iSocket.Open();
    iSubscription.SetInterruptHandler(this);
    Endpoint endpoint(aPublisher.Port(), aPublisher.Host());
    TUint timeout = Stack::InitParams().TcpConnectTimeoutMs();
    iSocket.Connect(endpoint, timeout);

    RenewSubscriptionWriteRequest(aPublisher, aDurationSecs);
    Brh tmp;
    SubscribeReadResponse(tmp, aDurationSecs);
    if (tmp != iSubscription.Sid()) {
        THROW(HttpError);
    }
}

void EventUpnp::Unsubscribe(const Uri& aPublisher, const Brx& aSid)
{
    iSocket.Open();
    Endpoint endpoint(aPublisher.Port(), aPublisher.Host());
    TUint timeout = Stack::InitParams().TcpConnectTimeoutMs();
    iSocket.Connect(endpoint, timeout);

    UnsubscribeWriteRequest(aPublisher, aSid);
    UnsubscribeReadResponse();
}

void EventUpnp::Interrupt()
{
    /* Assumes that interrupting the socket is always safe, regardless of whether we're
       using it or one of its stream/http wrappers */
    iSocket.Interrupt(true);
}

void EventUpnp::ProcessNotification(const Brx& aNotification, PropertyMap& aProperties)
{
    OutputProcessorUpnp outputProcessor;
    Brn propertySet = XmlParserBasic::Find("propertyset", aNotification);
    Brn property;
    Brn remaining;
    try {
        for (;;) {
            property.Set(XmlParserBasic::Find("property", propertySet, remaining));
            property.Set(Ascii::Trim(property));
            if (property.Bytes() < 8 || property[0] != '<') {
                THROW(XmlError);
            }
            if (property[1] == '/') {
                ASSERTS();
            }
            Parser parser(property);
            (void)parser.Next('<');
            Brn tagName = parser.Next('>');
            Brn val = parser.Next('<');
            Brn closingTag = parser.Next('/');
            closingTag.Set(parser.Next('>'));
            if (tagName != closingTag) {
                THROW(XmlError);
            }

            PropertyMap::iterator it = aProperties.find(tagName);
            if (it != aProperties.end()) {
                try {
                    it->second->Process(outputProcessor, val);
                }
                catch(AsciiError&) {
                    THROW(XmlError);
                }
            }

            propertySet.Set(remaining);
        }
    }
    catch(XmlError&) {}
    PropertyMap::iterator it = aProperties.begin();
    while (it != aProperties.end()) {
        it->second->ReportChanged();
		it++;
    }
}

void EventUpnp::SubscribeWriteRequest(const Uri& aPublisher, const Uri& aSubscriber, TUint aDurationSecs)
{
    const Brn kRequestMethod("SUBSCRIBE");
    const Brn kMethodCallback("CALLBACK");
    const Brn kMethodNt("NT");
    const Brn kFieldNt("upnp:event");
    Sws<1024> writeBuffer(iSocket);
    WriterHttpRequest writerRequest(writeBuffer);

    writerRequest.WriteMethod(kRequestMethod, aPublisher.PathAndQuery(), Http::eHttp11);
    Http::WriteHeaderHostAndPort(writerRequest, aPublisher);

    IWriterAscii& writerField = writerRequest.WriteHeaderField(kMethodCallback);
    writerField.Write('<');
    writerField.Write(aSubscriber.AbsoluteUri());
    writerField.Write('>');
    writerField.WriteNewline();

    writerField = writerRequest.WriteHeaderField(kMethodNt);
    writerField.Write(kFieldNt);
    writerField.WriteNewline();

    WriteHeaderTimeout(writerRequest, aDurationSecs);

    writerField.WriteNewline();
    writerRequest.WriteFlush();
}

void EventUpnp::SubscribeReadResponse(Brh& aSid, TUint& aDurationSecs)
{
    Srs<1024> readBuffer(iSocket);
    ReaderHttpResponse readerResponse(readBuffer);
    HeaderSid headerSid;
    HeaderTimeout headerTimeout;

    readerResponse.AddHeader(headerSid);
    readerResponse.AddHeader(headerTimeout);
    readerResponse.Read();
    const HttpStatus& status = readerResponse.Status();
    if (status != HttpStatus::kOk) {
        LOG2(kEvent, kError, "EventUpnp::SubscribeReadResponse, http error %u ", status.Code());
        LOG2(kEvent, kError, status.Reason());
        LOG2(kEvent, kError, "\n");
        THROW(HttpError);
    }

    Brh& sid = headerSid.Sid();
    if (sid.Bytes() == 0) {
        THROW(HttpError);
    }
    sid.TransferTo(aSid);

    aDurationSecs = headerTimeout.Timeout();
    if (aDurationSecs == 0) {
        THROW(HttpError);
    }
}

void EventUpnp::RenewSubscriptionWriteRequest(const Uri& aPublisher, TUint aDurationSecs)
{
    const Brn kRequestMethod("SUBSCRIBE");
    const Brn kMethodCallback("CALLBACK");
    const Brn kMethodNt("NT");
    const Brn kFieldNt("upnp:event");
    Sws<1024> writeBuffer(iSocket);
    WriterHttpRequest writerRequest(writeBuffer);
    WriterAscii writerAscii(writeBuffer);

    writerRequest.WriteMethod(kRequestMethod, aPublisher.Path(), Http::eHttp11);
    Http::WriteHeaderHostAndPort(writerRequest, aPublisher);
    WriteHeaderSid(writerRequest, iSubscription.Sid());
    WriteHeaderTimeout(writerRequest, aDurationSecs);
    writerAscii.WriteNewline();
    writerRequest.WriteFlush();
}

void EventUpnp::UnsubscribeWriteRequest(const Uri& aPublisher, const Brx& aSid)
{
    const Brn kRequestMethod("UNSUBSCRIBE");
    Sws<1024> writeBuffer(iSocket);
    WriterHttpRequest writerRequest(writeBuffer);
    WriterAscii writerAscii(writeBuffer);

    writerRequest.WriteMethod(kRequestMethod, aPublisher.Path(), Http::eHttp11);
    Http::WriteHeaderHostAndPort(writerRequest, aPublisher);
    WriteHeaderSid(writerRequest, aSid);
    writerAscii.WriteNewline();
    writerRequest.WriteFlush();
}

void EventUpnp::UnsubscribeReadResponse()
{
    Srs<1024> readBuffer(iSocket);
    ReaderHttpResponse readerResponse(readBuffer);
    readerResponse.Read();
    const HttpStatus& status = readerResponse.Status();
    if (status != HttpStatus::kOk) {
        LOG2(kEvent, kError, "EventUpnp::Unsubscribe, http error %u ", status.Code());
        LOG2(kEvent, kError, status.Reason());
        LOG2(kEvent, kError, "\n");
        // don't throw an exception here - clients will ignore any later events with unrecognised SIDs
    }
}

void EventUpnp::WriteHeaderSid(WriterHttpRequest& aWriterRequest, const Brx& aSid)
{
    IWriterAscii& writerField = aWriterRequest.WriteHeaderField(HeaderSid::kHeaderSid);
    writerField.Write(HeaderSid::kFieldSidPrefix);
    writerField.Write(aSid);
    writerField.WriteNewline();
}

void EventUpnp::WriteHeaderTimeout(WriterHttpRequest& aWriterRequest, TUint aSeconds)
{
    IWriterAscii& writerField = aWriterRequest.WriteHeaderField(HeaderTimeout::kHeaderTimeout);
    writerField.Write(HeaderTimeout::kFieldTimeoutPrefix);
    writerField.WriteUint(aSeconds);
    writerField.WriteNewline();
}


// OutputProcessorUpnp

void OutputProcessorUpnp::ProcessString(const Brx& aBuffer, Brhz& aVal)
{
	// Constructs Bwn over the Brhz in order to save copying twice
	aVal.Set(aBuffer);
	Bwn writeable(aVal.Ptr(), aVal.Bytes(), aVal.Bytes());
    Converter::FromXmlEscaped(writeable);
    aVal.Shrink(writeable.Bytes());
}

void OutputProcessorUpnp::ProcessInt(const Brx& aBuffer, TInt& aVal)
{
    aVal = Ascii::Int(aBuffer);
}

void OutputProcessorUpnp::ProcessUint(const Brx& aBuffer, TUint& aVal)
{
    aVal = Ascii::Uint(aBuffer);
}

void OutputProcessorUpnp::ProcessBool(const Brx& aBuffer, TBool& aVal)
{
    try {
        TInt val = Ascii::Int(aBuffer);
        aVal = (val!=0);
    }
    catch(AsciiError) {
        static const Brn kBoolTrue("true");
        static const Brn kBoolFalse("false");
        static const Brn kBoolYes("yes");
        static const Brn kBoolNo("no");
        if (aBuffer==kBoolTrue || aBuffer==kBoolYes) {
            aVal = true;
        }
        else if (aBuffer==kBoolFalse || aBuffer==kBoolNo) {
            aVal = false;
        }
        else {
            THROW(XmlError);
        }
    }
}

void OutputProcessorUpnp::ProcessBinary(const Brx& aBuffer, Brh& aVal)
{
    Bwh copy(aBuffer);
    Converter::FromBase64(copy);
    copy.TransferTo(aVal);
}


// HeaderNts

const Brx& HeaderNts::Value() const
{
    return iValue;
}

TBool HeaderNts::Recognise(const Brx& aHeader)
{
    const Brn kHeaderNts("Nts");
    return (Ascii::CaseInsensitiveEquals(aHeader, kHeaderNts));
}

void HeaderNts::Process(const Brx& aValue)
{
    SetReceived();
    iValue.Set(aValue);
}


// HeaderSeq

TUint HeaderSeq::Seq() const
{
    return (Received()? iSeq : 0);
}

TBool HeaderSeq::Recognise(const Brx& aHeader)
{
    const Brn kHeaderSeq("Seq");
    return (Ascii::CaseInsensitiveEquals(aHeader, kHeaderSeq));
}

void HeaderSeq::Process(const Brx& aValue)
{
    try {
        iSeq = Ascii::Uint(aValue);
	    SetReceived();
    }
    catch(AsciiError&) {
        THROW(HttpError);
    }
}
