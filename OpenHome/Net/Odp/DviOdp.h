#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Json.h>

#include <atomic>

namespace OpenHome {
    class IWriter;
    class Timer;
namespace Net {
    class DvStack;
    class DviDevice;
    class DviService;

class IOdpSession
{
public:
    virtual IWriter& WriteLock() = 0;
    virtual void WriteUnlock() = 0;
    virtual void WriteEnd() = 0;
    virtual TIpAddress Adapter() const = 0;
    virtual const Brx& ClientUserAgentDefault() const = 0;
    virtual ~IOdpSession() {}
};

class PropertyWriterFactoryOdp : public IPropertyWriterFactory
                               , private IPropertyWriter
                               , private INonCopyable
{
public:
    PropertyWriterFactoryOdp(IOdpSession& aSession, DvStack& aDvStack);
    void Disable();
private:
    ~PropertyWriterFactoryOdp();
    void AddRef();
    void RemoveRef();
    void Renew();
    void ScheduleRenewTimer();
private: // from IPropertyWriterFactory
    IPropertyWriter* ClaimWriter(const IDviSubscriptionUserData* aUserData,
                                 const Brx& aSid, TUint aSequenceNumber) override;
    void ReleaseWriter(IPropertyWriter* aWriter) override;
    void NotifySubscriptionCreated(const Brx& aSid) override;
    void NotifySubscriptionDeleted(const Brx& aSid) override;
    void NotifySubscriptionExpired(const Brx& aSid) override;
    void LogUserData(IWriter& aWriter, const IDviSubscriptionUserData& aUserData) override;
private: // from IPropertyWriter
    void PropertyWriteString(const Brx& aName, const Brx& aValue) override;
    void PropertyWriteInt(const Brx& aName, TInt aValue) override;
    void PropertyWriteUint(const Brx& aName, TUint aValue) override;
    void PropertyWriteBool(const Brx& aName, TBool aValue) override;
    void PropertyWriteBinary(const Brx& aName, const Brx& aValue) override;
    void PropertyWriteEnd() override;
private:
    Mutex iLock;
    IOdpSession& iSession;
    DviSubscriptionManager& iSubscriptionManager;
    TBool iEnabled;
    std::atomic<TUint> iRefCount;
    std::map<Brn, Brn, BufferCmp> iSubscriptions;
    IWriter* iWriter;
    WriterJsonObject iWriterNotify;
    WriterJsonObject iWriterProperties;
    Timer* iRenewTimer;
    TUint iDuration;
};

class DviOdp : private IDviInvocation
             , private INonCopyable
{
public:
    static const TUint kServiceVersionInvalid;
    static const TUint kErrCodeSubscriptionUnknown;
    static const Brn kErrMsgSubscriptionUnknown;
    static const TUint kErrCodeSubscriptionNoDevice;
    static const Brn kErrMsgSubscriptionNoDevice;
    static const TUint kErrCodeSubscriptionNoService;
    static const Brn kErrMsgSubscriptionNoService;
    static const TUint kErrCodeSubscriptionNoServiceVersion;
    static const Brn kErrMsgSubscriptionNoServiceVersion;
public:
    DviOdp(DvStack& aDvStack, IOdpSession& aSession);
    void Announce();
    void Disable();
    void Process(const Brx& aJsonRequest);
private:
    void LogParseErrorThrow(const TChar* aEx, const Brx& aJson);
    void Action();
    void Subscribe();
    void Unsubscribe();
    void ParseDeviceAndService();
    void ParseDeviceAndService(Brn& aDeviceAlias,
                               Brn& aServiceName,
                               TUint& aServiceVersion);
private: // from IDviInvocation
    void Invoke() override;
    TUint Version() const override;
    TIpAddress Adapter() const override;
    const char* ResourceUriPrefix() const override;
    Endpoint ClientEndpoint() const override;
    const Brx& ClientUserAgent() const override;
    void InvocationReadStart() override;
    TBool InvocationReadBool(const TChar* aName) override;
    void InvocationReadString(const TChar* aName, Brhz& aString) override;
    TInt InvocationReadInt(const TChar* aName) override;
    TUint InvocationReadUint(const TChar* aName) override;
    void InvocationReadBinary(const TChar* aName, Brh& aData) override;
    void InvocationReadEnd() override;
    void InvocationReportError(TUint aCode, const Brx& aDescription) override;
    void InvocationWriteStart() override;
    void InvocationWriteBool(const TChar* aName, TBool aValue) override;
    void InvocationWriteInt(const TChar* aName, TInt aValue) override;
    void InvocationWriteUint(const TChar* aName, TUint aValue) override;
    void InvocationWriteBinaryStart(const TChar* aName) override;
    void InvocationWriteBinary(TByte aValue) override;
    void InvocationWriteBinary(const Brx& aValue) override;
    void InvocationWriteBinaryEnd(const TChar* aName) override;
    void InvocationWriteStringStart(const TChar* aName) override;
    void InvocationWriteString(TByte aValue) override;
    void InvocationWriteString(const Brx& aValue) override;
    void InvocationWriteStringEnd(const TChar* aName) override;
    void InvocationWriteEnd() override;
private:
    DvStack& iDvStack;
    IOdpSession& iSession;
    PropertyWriterFactoryOdp* iPropertyWriterFactory;
    IWriter* iWriter;
    JsonParser iParserReq;
    JsonParser iParserArgs;
    DviDevice* iDevice;
    DviService* iService;
    TUint iServiceVersion;
    WriterJsonObject iWriterResponse;
    WriterJsonObject iWriterResponseArgs;
    WriterJsonValueString iWriterStringStreamed;
    TBool iResponseStarted;
    TBool iResponseEnded;
    mutable Brn iClientUserAgent;
};

// takes write locked session, unlocks on destruction
class AutoOdpSession : private INonCopyable
{
public:
    AutoOdpSession(IOdpSession& aSession);
    ~AutoOdpSession();
private:
    IOdpSession& iSession;
};

} // namespace Net
} // namespace OpenHome
