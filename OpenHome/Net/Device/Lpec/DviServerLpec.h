#ifndef HEADER_DVI_SERVER_LPEC
#define HEADER_DVI_SERVER_LPEC

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/DviServer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Standard.h>

#include <vector>
#include <map>

EXCEPTION(LpecParseError)

namespace OpenHome {
    class NetworkAdapter;
namespace Net {

class Lpec
{
public:
    static const Brn kMethodAlive;
    static const Brn kMethodByeBye;
    static const Brn kMethodAction;
    static const Brn kMethodSubscribe;
    static const Brn kMethodUnsubscribe;
    static const Brn kMethodResponse;
    static const Brn kMethodEvent;
    static const Brn kMethodError;
    static const Brn kBoolTrue;
    static const Brn kBoolFalse;
    static const TByte kArgumentDelimiter = '\"';
    static const Brn kMsgTerminator;
};
    
class LpecError
{
public:
    static const LpecError kCommandNotRecognised;
    static const LpecError kServiceNotSpecified;
    static const LpecError kServiceNotFound;
    static const LpecError kVersionInvalid;
    static const LpecError kVersionNotSpecified;
    static const LpecError kVersionNotSupported;
    static const LpecError kMethodNotSpecified;
    static const LpecError kMethodExecutionError;
    static const LpecError kMethodNotSupported;
    static const LpecError kInvalidCommandTerminator;
    static const LpecError kDeviceNotFound;
    static const LpecError kInvalidArgBool;
    static const LpecError kInvalidArgUint;
    static const LpecError kInvalidArgInt;
    static const LpecError kAlreadySubscribed;
    static const LpecError kTooManySubscriptions;
    static const LpecError kSubscriptionNotFound;
    static const LpecError kServiceNotSubscribed;
public:
    TUint Code() const;
    const Brx& Description() const;
protected:
    LpecError(TUint aCode, const TChar* aDescription);
private:
    TUint iCode;
    Brn iDescription;
};

class IEventWriter : public IWriter
{
public:
    virtual void Lock() = 0;
    virtual void Unlock() = 0;
    virtual TUint LpecSid(const Brx& aSid) = 0;
};

class PropertyWriterFactoryLpec : public IPropertyWriterFactory, private IPropertyWriter
{
public:
    PropertyWriterFactoryLpec(IEventWriter& aEventWriter);
    void SubscriptionAdded(DviSubscription& aSubscription);
    void Disable();
private: // from IPropertyWriterFactory
    IPropertyWriter* ClaimWriter(const IDviSubscriptionUserData* aUserData, const Brx& aSid, TUint aSequenceNumber);
    void ReleaseWriter(IPropertyWriter* aWriter);
    void NotifySubscriptionCreated(const Brx& aSid);
    void NotifySubscriptionDeleted(const Brx& aSid);
    void NotifySubscriptionExpired(const Brx& aSid);
private: // from IPropertyWriter
    void PropertyWriteString(const Brx& aName, const Brx& aValue);
    void PropertyWriteInt(const Brx& aName, TInt aValue);
    void PropertyWriteUint(const Brx& aName, TUint aValue);
    void PropertyWriteBool(const Brx& aName, TBool aValue);
    void PropertyWriteBinary(const Brx& aName, const Brx& aValue);
    void PropertyWriteEnd();
    void Release();
private:
    ~PropertyWriterFactoryLpec();
    void AddRef();
    void RemoveRef();
private:
    Mutex iLock;
    TUint iRefCount;
    IEventWriter& iEventWriter;
    TBool iEnabled;
    typedef std::map<Brn,DviSubscription*,BufferCmp> SubscriptionMap;
    SubscriptionMap iSubscriptionMap;
    Mutex iSubscriptionMapLock;
};

class DviSessionLpec : public SocketTcpSession, private IDviInvocation
{
public:
    DviSessionLpec(DvStack& aDvStack, TIpAddress aAdapter, TUint aPort);
    ~DviSessionLpec();
    void NotifyDeviceDisabled(const Brx& aName, const Brx& aUdn);
private: // from SocketTcpSession
    void Run();
private:
    void Action();
    void Subscribe();
    void Unsubscribe();
    void ParseDeviceAndService();
    void DoUnsubscribe(TUint aIndex, TBool aRespond = true);
    void ReportError(const LpecError& aError);
    void ReportErrorNoThrow(const LpecError& aError);
    void ReportErrorNoThrow(TUint aCode, const Brx& aDescription);
private: // from IDviInvocation
    void Invoke();
    TUint Version() const;
    TIpAddress Adapter() const;
    const char* ResourceUriPrefix() const;
    Endpoint ClientEndpoint() const;
    void InvocationReadStart();
    TBool InvocationReadBool(const TChar* aName);
    void InvocationReadString(const TChar* aName, Brhz& aString);
    TInt InvocationReadInt(const TChar* aName);
    TUint InvocationReadUint(const TChar* aName);
    void InvocationReadBinary(const TChar* aName, Brh& aData);
    void InvocationReadEnd();
    void InvocationReportError(TUint aCode, const Brx& aDescription);
    void InvocationWriteStart();
    void InvocationWriteBool(const TChar* aName, TBool aValue);
    void InvocationWriteInt(const TChar* aName, TInt aValue);
    void InvocationWriteUint(const TChar* aName, TUint aValue);
    void InvocationWriteBinaryStart(const TChar* aName);
    void InvocationWriteBinary(TByte aValue);
    void InvocationWriteBinary(const Brx& aValue);
    void InvocationWriteBinaryEnd(const TChar* aName);
    void InvocationWriteStringStart(const TChar* aName);
    void InvocationWriteString(TByte aValue);
    void InvocationWriteString(const Brx& aValue);
    void InvocationWriteStringEnd(const TChar* aName);
    void InvocationWriteEnd();
private: // from IEventWriter
    class SubscriptionData
    {
    public:
        SubscriptionData(DviDevice& aDevice, DviService& aService, DviSubscription& aSubscription, TUint aLpecSubscriptionId);
        TBool Matches(DviDevice& aDevice, DviService& aService) const;
        DviService& Service();
        DviSubscription* Subscription();
        TUint LpecSid() const;
    private:
        DviDevice* iDevice;
        DviService* iService;
        DviSubscription* iSubscription;
        TUint iLpecSubscriptionId;
    };
    class EventWriterAdapter : public IEventWriter, private INonCopyable
    {
    public:
        EventWriterAdapter(IWriter& aWriter, Mutex& aLock, std::vector<SubscriptionData>& aSubscriptions);
    private: // from IEventWriter
        void Write(TByte aValue);
        void Write(const Brx& aBuffer);
        void WriteFlush();
        void Lock();
        void Unlock();
        TUint LpecSid(const Brx& aSid);
    private:
        IWriter& iWriter;
        Mutex& iLock;
        std::vector<SubscriptionData>& iSubscriptions;
    };
private:
    static const TUint kMaxSubscriptions = 16; // imposed by public LPEC docs
    static const TUint kMaxReadBytes = 12000;
    static const TUint kWriteBufferBytes = 4000;
    static const TUint kMaxSubscriptionCount = 16; // FIXME - limitation copied from volkano.  Is it necessary?
    DvStack& iDvStack;
    TIpAddress iAdapter;
    TUint iPort;
    Mutex iWriteLock;
    Semaphore iShutdownSem;
    Mutex iSubscriptionLock;
    Mutex iByeByeLock;
    Mutex iDeviceLock;
    Srx* iReadBuffer;
    ReaderUntil* iReaderUntil;
    Sws<kWriteBufferBytes>* iWriteBuffer;
    EventWriterAdapter* iEventWriterAdapter;
    PropertyWriterFactoryLpec* iPropertyWriterFactory;
    std::map<Brn,DviDevice*,BufferCmp> iDeviceMap;
    Brn iRequestBuf;
    Parser iParser;
    TBool iResponseStarted;
    TBool iResponseEnded;
    TBool iActive;
    DviDevice* iTargetDevice;
    DviService* iTargetService;
    TUint iVersion;
    mutable Bws<128> iResourceUriPrefix;
    std::vector<SubscriptionData> iSubscriptions;
};
    
class DvStack;

class DviServerLpec : public DviServer
{
public:
    DviServerLpec(DvStack& aDvStack, TUint aPort = 0);
    void NotifyDeviceDisabled(const Brx& aName, const Brx& aUdn);
    TUint Port() const;
private: // from DviServerUpnp
    SocketTcpServer* CreateServer(const NetworkAdapter& aNif);
    void NotifyServerDeleted(TIpAddress aInterface);
private:
    class AdapterData
    {
    public:
        AdapterData(TIpAddress aInterface);
    public:
        TIpAddress iInterface;
        std::vector<DviSessionLpec*> iSessions;
    };
private:
    TUint iPort;
    std::vector<AdapterData*> iAdapterData;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_SERVER_LPEC
