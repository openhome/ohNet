#ifndef HEADER_SSDP_BASE
#define HEADER_SSDP_BASE

#include <OpenHome/Private/Http.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Network.h>

namespace OpenHome {

class Environment;
    
namespace Net {

class DvStack;

enum ESsdpTarget
{
    eSsdpUnknown,
    eSsdpRoot,
    eSsdpUuid,
    eSsdpDeviceType,
    eSsdpServiceType,
    eSsdpAll
};

class Ssdp
{
public:
    static const TByte kUrnSeparator;
    static const TUint kMulticastPort;
    static const Brn kUrn;
    static const Brn kMulticastAddress;
    static const Brn kMulticastAddressAndPort;
    static const Brn kMethodNotify;
    static const Brn kMethodMsearch;
    static const Brn kMethodUri;
    static const Brn kStatusOk;
    static const Brn kHeaderHost;
    static const Brn kHeaderServer;
    static const Brn kHeaderCacheControl;
    static const Brn kHeaderLocation;
    static const Brn kHeaderNt;
    static const Brn kHeaderSt;
    static const Brn kHeaderUsn;
    static const Brn kHeaderNts;
    static const Brn kHeaderExt;
    static const Brn kHeaderMan;
    static const Brn kHeaderMx;
    static const Brn kHeaderBootId;
    static const Brn kHeaderNextBootId;
    static const Brn kHeaderConfigId;
    static const Brn kHeaderSearchPort;
    static const Brn kDeviceSeparator;
    static const Brn kServiceSeparator;
public:
    static void UpnpDomainToCanonical(const Brx& aUpnpDomain, Bwx& aCanonicalDomain);
    static void CanonicalDomainToUpnp(const Brx& aCanonicalDomain, Bwx& aUpnpDomain);
    static void WriteRoot(IWriter& aWriter);
    static void WriteUuid(IWriter& aWriter, const Brx& aUuid);
    static void WriteDeviceType(IWriter& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion);
    static void WriteServiceType(IWriter& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion);
    static void WriteMethodNotify(IWriterHttpMethod& aWriter);
    static void WriteMethodMsearch(IWriterHttpMethod& aWriter);
    static void WriteHost(IWriterHttpHeader& aWriter);
    static void WriteMan(IWriterHttpHeader& aWriter);
    static void WriteMx(IWriterHttpHeader& aWriter, TUint aSeconds);
    static void WriteSearchTypeRoot(IWriterHttpHeader& aWriter);
    static void WriteSearchTypeUuid(IWriterHttpHeader& aWriter, const Brx& aUuid);
    static void WriteSearchTypeDeviceType(IWriterHttpHeader& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion);
    static void WriteSearchTypeServiceType(IWriterHttpHeader& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion);
    static void WriteSearchTypeAll(IWriterHttpHeader& aWriter);
    static void WriteServer(Environment& aEnv, IWriterHttpHeader& aWriter);
    static void WriteMaxAge(Environment& aEnv, IWriterHttpHeader& aWriter);
    static void WriteLocation(IWriterHttpHeader& aWriter, const Brx& aUrl);
    static void WriteSubTypeAlive(IWriterHttpHeader& aWriter);
    static void WriteSubTypeByeBye(IWriterHttpHeader& aWriter);
    static void WriteStatus(IWriterHttpStatus& aWriter);
    static void WriteExt(IWriterHttpHeader& aWriter);
    static void WriteNotificationTypeRoot(IWriterHttpHeader& aWriter);
    static void WriteNotificationTypeUuid(IWriterHttpHeader& aWriter, const Brx& aUuid);
    static void WriteNotificationTypeDeviceType(IWriterHttpHeader& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion);
    static void WriteNotificationTypeServiceType(IWriterHttpHeader& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion);
    static void WriteUsnRoot(IWriterHttpHeader& aWriter, const Brx& aUuid);
    static void WriteUsnUuid(IWriterHttpHeader& aWriter, const Brx& aUuid);
    static void WriteUsnDeviceType(IWriterHttpHeader& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid);
    static void WriteUsnServiceType(IWriterHttpHeader& aWriter, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid);
    static void WriteBootId(DvStack& aDvStack, IWriterHttpHeader& aWriter);
    static void WriteNextBootId(DvStack& aDvStack, IWriterHttpHeader& aWriter);
    static void WriteConfigId(IWriterHttpHeader& aWriter, TUint aConfigId);
    static void WriteSearchPort(IWriterHttpHeader& aWriter, TUint aPort);
    static TBool ParseUrnDevice(const Brx& aUrn, Brn& aDomainName, Brn& aDeviceType, TUint& aVer);
    static TBool ParseUrnService(const Brx& aUrn, Brn& aDomainName, Brn& aDeviceType, TUint& aVer);
private:
    static TBool ParseUrn(const Brx& aUrn, const Brx& aType, Brn& aDomainName, Brn& aDeviceType, TUint& aVer);
};

class SsdpHeaderCacheControl : public HttpHeader
{
public:
    TUint MaxAge() const;
private:
    // IHttpHeader
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    TUint iMaxAge;
};

class SsdpHeaderServer : public HttpHeader
{
private:
    // IHttpHeader
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
};

class SsdpHeaderSt : public HttpHeader
{
    static const TUint kMaxUuidBytes = 64;
    static const TUint kMaxDomainBytes = 64;
    static const TUint kMaxTypeBytes = 64;
public:
    ESsdpTarget Target() const;
    const Brx& Uuid() const;
    const Brx& Domain() const;
    const Brx& Type() const;
    TUint Version() const;
private:
    // IHttpHeader
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    ESsdpTarget iTarget;
    Bws<kMaxUuidBytes> iUuid;
    Bws<kMaxDomainBytes> iDomain;
    Bws<kMaxTypeBytes> iType;
    TUint iVersion;
};

class SsdpHeaderNt : public HttpHeader
{
    static const TUint kMaxUuidBytes = 64;
    static const TUint kMaxDomainBytes = 64;
    static const TUint kMaxTypeBytes = 64;
public:
    ESsdpTarget Target() const;
    const Brx& Uuid() const;
    const Brx& Domain() const;
    const Brx& Type() const;
    TUint Version() const;
private:
    // IHttpHeader
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    ESsdpTarget iTarget;
    Bws<kMaxUuidBytes> iUuid;
    Bws<kMaxDomainBytes> iDomain;
    Bws<kMaxTypeBytes> iType;
    TUint iVersion;
};

class SsdpHeaderUsn : public HttpHeader
{
    static const TUint kMaxUuidBytes = 64;
    static const TUint kMaxDomainBytes = 64;
    static const TUint kMaxTypeBytes = 64;
public:
    ESsdpTarget Target() const;
    const Brx& Uuid() const;
    const Brx& Domain() const;
    const Brx& Type() const;
    TUint Version() const;
private:
    // IHttpHeader
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    ESsdpTarget iTarget;
    Bws<kMaxUuidBytes> iUuid;
    Bws<kMaxDomainBytes> iDomain;
    Bws<kMaxTypeBytes> iType;
    TUint iVersion;
};

class SsdpHeaderHost : public HttpHeader
{
private:
    // IHttpHeader
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
};

class SsdpHeaderMan : public HttpHeader
{
private:
    // IHttpHeader
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
};

class SsdpHeaderMx : public HttpHeader
{
public:
    TUint Mx() const;
private:
    // IHttpHeader
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    TUint iMx;
};

class SsdpHeaderNts : public HttpHeader
{
public:
    TBool Alive() const;
private:
    // IHttpHeader
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    TBool iAlive;
};

class SsdpHeaderExt : public HttpHeader
{
private:
    // IHttpHeader
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
};

class SsdpWriterMsearchRequest
{
public:
    SsdpWriterMsearchRequest(IWriter& aWriter);
    void MsearchRoot(TUint aSeconds);
    void MsearchUuid(const Brx& aUuid, TUint aSeconds);
    void MsearchDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion, TUint aSeconds);
    void MsearchServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion, TUint aSeconds);
    void MsearchAll(TUint aSeconds);
private:
    void Msearch(TUint aSeconds);
private:
    static const TUint kMinMsearchSeconds = 1;
    static const TUint kMaxMsearchSeconds = 120;
private:
    WriterHttpRequest iWriter;
};

class SsdpNotifier
{
public:
    enum ENotificationType
    {
        EAlive
       ,EByeBye
       ,EUpdate
    };
public:
    SsdpNotifier(DvStack& aDvStack);
    void Start(TIpAddress aInterface, TUint aConfigId);
    // ISsdpNotify-based services
    void SsdpNotifyRoot(const Brx& aUuid, const Brx& aUri, ENotificationType aNotificationType);
    void SsdpNotifyUuid(const Brx& aUuid, const Brx& aUri, ENotificationType aNotificationType);
    void SsdpNotifyDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri, ENotificationType aNotificationType);
    void SsdpNotifyServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri, ENotificationType aNotificationType);
private:
    void SsdpNotify(const Brx& aUri, ENotificationType aNotificationType);
private:
    static const TUint kMaxBufferBytes = 1024;
private:
    DvStack& iDvStack;
    SocketUdp iSocket;
    UdpWriter iSocketWriter;
    Sws<kMaxBufferBytes> iBuffer;
    WriterHttpRequest iWriter;
    TUint iConfigId;
};

class ISsdpNotify
{
public:
    virtual void SsdpNotifyRoot(const Brx& aUuid, const Brx& aUri) = 0;
    virtual void SsdpNotifyUuid(const Brx& aUuid, const Brx& aUri) = 0;
    virtual void SsdpNotifyDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri) = 0;
    virtual void SsdpNotifyServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri) = 0;
    virtual ~ISsdpNotify() {}
};

class SsdpNotifierAlive : public ISsdpNotify, public INonCopyable
{
public:
    SsdpNotifierAlive(SsdpNotifier& aNotifier);
    // ISsdpNotify
    void SsdpNotifyRoot(const Brx& aUuid, const Brx& aUri);
    void SsdpNotifyUuid(const Brx& aUuid, const Brx& aUri);
    void SsdpNotifyDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri);
    void SsdpNotifyServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri);
private:
    SsdpNotifier& iNotifier;
};

class SsdpNotifierByeBye : public ISsdpNotify, public INonCopyable
{
public:
    SsdpNotifierByeBye(SsdpNotifier& aNotifier);
    // ISsdpNotify
    void SsdpNotifyRoot(const Brx& aUuid, const Brx& aUri);
    void SsdpNotifyUuid(const Brx& aUuid, const Brx& aUri);
    void SsdpNotifyDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri);
    void SsdpNotifyServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri);
private:
    SsdpNotifier& iNotifier;
};

class SsdpNotifierUpdate : public ISsdpNotify, public INonCopyable
{
public:
    SsdpNotifierUpdate(SsdpNotifier& aNotifier);
    // ISsdpNotify
    void SsdpNotifyRoot(const Brx& aUuid, const Brx& aUri);
    void SsdpNotifyUuid(const Brx& aUuid, const Brx& aUri);
    void SsdpNotifyDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri);
    void SsdpNotifyServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri);
private:
    SsdpNotifier& iNotifier;
};

class SsdpMsearchResponder : public ISsdpNotify
{
public:
    SsdpMsearchResponder(DvStack& aDvStack);
    void SetRemote(const Endpoint& aEndpoint, TUint aConfigId, TIpAddress aAdapter);
    // ISsdpNotify
    void SsdpNotifyRoot(const Brx& aUuid, const Brx& aUri);
    void SsdpNotifyUuid(const Brx& aUuid, const Brx& aUri);
    void SsdpNotifyDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri);
    void SsdpNotifyServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri);
private:
    void SsdpNotify(const Brx& aUri);
    void Flush();
private:
    static const TUint kMaxBufferBytes = 1024;
private:
    DvStack& iDvStack;
    Bws<kMaxBufferBytes> iResponse;
    WriterBuffer iBuffer;
    WriterHttpResponse iWriter;
    TUint iConfigId;
    Endpoint iRemote;
    TIpAddress iAdapter;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_SSDP_BASE
