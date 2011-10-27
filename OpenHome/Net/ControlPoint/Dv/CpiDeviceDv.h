#ifndef HEADER_CP_DEVICE_SOCKET
#define HEADER_CP_DEVICE_SOCKET

#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/CpiService.h>

namespace OpenHome {
namespace Net {

class DviDevice;
class CpiSubscription;
class Uri;
class IEventProcessor;

class CpiDeviceDv : private INonCopyable, private ICpiProtocol, private ICpiDeviceObserver, private IPropertyWriterFactory
{
public:
    CpiDeviceDv(DviDevice& aDevice);
    CpiDevice& Device();
    virtual ~CpiDeviceDv() {}
private: // ICpiProtocol
    void InvokeAction(Invocation& aInvocation);
    TBool GetAttribute(const char* aKey, Brh& aValue) const;
    TUint Subscribe(CpiSubscription& aSubscription, const OpenHome::Uri& aSubscriber);
    TUint Renew(CpiSubscription& aSubscription);
    void Unsubscribe(CpiSubscription& aSubscription, const Brx& aSid);
    void NotifyRemovedBeforeReady();
private: // ICpiDeviceObserver
    void Release();
private: // IPropertyWriterFactory
    IPropertyWriter* CreateWriter(const IDviSubscriptionUserData* aUserData, const Brx& aSid, TUint aSequenceNumber);
private:
    CpiDevice* iDeviceCp;
    DviDevice& iDeviceDv;
    DviSubscription* iSubscriptionDv;
    CpiSubscription* iSubscriptionCp;
};

class Argument;

class InvocationDv : public IDviInvocation, private INonCopyable
{
public:
    InvocationDv(Invocation& aInvocation, DviService& aService);
    void Start();
private: // IDviInvocation
    void Invoke();

    TUint Version() const;
    TIpAddress Adapter() const;
    const char* ResourceUriPrefix() const;

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
private:
    OpenHome::Net::Argument* InputArgument(const TChar* aName);
    OpenHome::Net::Argument* OutputArgument(const TChar* aName);
    OpenHome::Net::Argument* Argument(const TChar* aName, const Invocation::VectorArguments& aVector, TUint& aIndex);
    void GetNextIndex(TUint& aIndex, const Invocation::VectorArguments& aVector);
private:
    Invocation& iInvocation;
    DviService& iService;
    TUint iReadIndex;
    TUint iWriteIndex;
    OpenHome::Net::Argument* iWriteArg; // used for binary & string writing only
};

class PropertyWriterDv : public IPropertyWriter, private INonCopyable
{
public:
    PropertyWriterDv(IEventProcessor& aEventProcessor);
private: // IPropertyWriter
    void PropertyWriteString(const Brx& aName, const Brx& aValue);
    void PropertyWriteInt(const Brx& aName, TInt aValue);
    void PropertyWriteUint(const Brx& aName, TUint aValue);
    void PropertyWriteBool(const Brx& aName, TBool aValue);
    void PropertyWriteBinary(const Brx& aName, const Brx& aValue);
    void PropertyWriteEnd();
private:
    IEventProcessor& iEventProcessor;
};

class OutputProcessorDv : public IOutputProcessor
{
public:
    virtual ~OutputProcessorDv() {}
private: // IOutputProcessor
    void ProcessString(const Brx& aBuffer, Brhz& aVal);
    void ProcessInt(const Brx& aBuffer, TInt& aVal);
    void ProcessUint(const Brx& aBuffer, TUint& aVal);
    void ProcessBool(const Brx& aBuffer, TBool& aVal);
    void ProcessBinary(const Brx& aBuffer, Brh& aVal);
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_CP_DEVICE_SOCKET
