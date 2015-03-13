/**
 * Invocation of a UPnP request on a particular device
 */

#ifndef HEADER_PROTOCOL_UPNP
#define HEADER_PROTOCOL_UPNP

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Stream.h>

namespace OpenHome {
namespace Net {

class CpStack;
class CpiSubscription;

class InvocationUpnp : private IInterruptHandler
{
public:
    InvocationUpnp(CpStack& aCpStack, Invocation& aInvocation);
    ~InvocationUpnp();
    void Invoke(const Uri& aUri);
    static void WriteServiceType(IWriterAscii& aWriter, const Invocation& aInvocation);
private:
    void WriteRequest(const Uri& aUri);
    void ReadResponse();
    void WriteHeaders(WriterHttpRequest& aWriterRequest, const Uri& aUri, TUint aBodyBytes);
    // IInterruptHandler
    void Interrupt();
private:
    static const TUint kMaxReadBytes = 16 * 1024;
    static const TUint kResponseTimeoutMs = 60 * 1000;
    CpStack& iCpStack;
    Invocation& iInvocation;
    OpenHome::SocketTcpClient iSocket;
    Srs<1024> iReadBuffer;
    ReaderUntilS<1024> iReaderUntil;
    ReaderHttpResponse iReaderResponse;
};

/**
 * Write the body (entity) of a http invocation request
 *
 * Intended for internal use only
 */
class InvocationBodyWriter : public IInputArgumentProcessor
{
public:
    static void Write(const Invocation& aInvocation, Bwh& aBody);
private:
    InvocationBodyWriter();
    void Write(const Invocation& aInvocation);
    // IInputArgumentProcessor
    void ProcessString(const Brx& aVal);
    void ProcessInt(TInt aVal);
    void ProcessUint(TUint aVal);
    void ProcessBool(TBool aVal);
    void ProcessBinary(const Brx& aVal);
private:
    static const TInt kBufferGranularity = 4096;
    WriterBwh iBody;
    Sws<kBufferGranularity> iWriteBuffer;
    WriterAscii iWriterAscii;
};

class EventUpnp : private IInterruptHandler, private INonCopyable
{
public:
    EventUpnp(CpStack& aCpStack, CpiSubscription& aSubscription);
    ~EventUpnp();
    void Subscribe(const Uri& aPublisher, const Uri& aSubscriber, TUint& aDurationSecs);
    void RenewSubscription(const Uri& aPublisher, TUint& aDurationSecs);
    void Unsubscribe(const Uri& aPublisher, const Brx& aSid);
private:
    void Interrupt();
private:
    void SubscribeWriteRequest(const Uri& aPublisher, const Uri& aSubscriber, TUint aDurationSecs);
    void SubscribeReadResponse(Brh& aSid, TUint& aDurationSecs);
    void RenewSubscriptionWriteRequest(const Uri& aPublisher, TUint aDurationSecs);
    void UnsubscribeWriteRequest(const Uri& aPublisher, const Brx& aSid);
    void UnsubscribeReadResponse();
    static void WriteHeaderSid(WriterHttpRequest& aWriterRequest, const Brx& aSid);
    static void WriteHeaderTimeout(WriterHttpRequest& aWriterRequest, TUint aSeconds);
private:
    static const TUint kSubscribeTimeoutMs   = 60 * 1000;
    static const TUint kUnsubscribeTimeoutMs =  5 * 1000;
private:
    CpStack& iCpStack;
    CpiSubscription& iSubscription;
    OpenHome::SocketTcpClient iSocket;
    Srs<1024> iReadBuffer;
    ReaderUntilS<1024> iReaderUntil;
};

class OutputProcessorUpnp : public IOutputProcessor
{
public:
    void ProcessString(const Brx& aBuffer, Brhz& aVal);
    void ProcessInt(const Brx& aBuffer, TInt& aVal);
    void ProcessUint(const Brx& aBuffer, TUint& aVal);
    void ProcessBool(const Brx& aBuffer, TBool& aVal);
    void ProcessBinary(const Brx& aBuffer, Brh& aVal);
};

class HeaderNts : public HttpHeader
{
public:
    const Brx& Value() const;
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    Brh iValue;
};

class HeaderSeq : public HttpHeader
{
public:
    TUint Seq() const;
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    TUint iSeq;
};


} // namespace Net
} // namespace OpenHome

#endif // HEADER_PROTOCOL_UPNP
