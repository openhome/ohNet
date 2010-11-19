#ifndef HEADER_CP_DEVICE_SOCKET
#define HEADER_CP_DEVICE_SOCKET

#include <CpiDevice.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <DviService.h>
#include <DviSubscription.h>
#include <Service.h>
#include <CpiService.h>

namespace Zapp {

class DviDevice;
class CpiSubscription;
class Uri;
class IEventProcessor;

class CpiDeviceDv : private INonCopyable, private ICpiProtocol, private ICpiDeviceObserver, private IPropertyWriterFactory
{
public:
    CpiDeviceDv(DviDevice& aDevice);
    CpiDevice& Device();
private:
    DviService* Service(const ServiceType& aServiceType);
private: // ICpiProtocol
    void InvokeAction(Invocation& aInvocation);
    TBool GetAttribute(const char* aKey, Brh& aValue) const;
    TUint Subscribe(CpiSubscription& aSubscription, const Uri& aSubscriber);
    TUint Renew(CpiSubscription& aSubscription);
    void Unsubscribe(CpiSubscription& aSubscription, const Brx& aSid);
private: // ICpiDeviceObserver
    void Release();
private: // IPropertyWriterFactory
    IPropertyWriter* CreateWriter(const IDviSubscriptionUserData& aUserData, const Brx& aSid, TUint aSequenceNumber);
private:
    CpiDevice* iDeviceCp;
    DviDevice& iDeviceDv;
    DviSubscription* iSubscriptionDv;
    CpiSubscription* iSubscriptionCp;
};

class Argument;

class InvocationDv : public IDviInvocation
{
public:
    InvocationDv(Invocation& aInvocation, DviService& aService);
    void Start();
private: // IDviInvocation
    void Invoke();

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
    Zapp::Argument* InputArgument(const TChar* aName);
    Zapp::Argument* OutputArgument(const TChar* aName);
    Zapp::Argument* Argument(const TChar* aName, const Invocation::VectorArguments& aVector, TUint& aIndex);
    void GetNextIndex(TUint& aIndex, const Invocation::VectorArguments& aVector);
private:
    Invocation& iInvocation;
    DviService& iService;
    Semaphore iSem;
    TUint iReadIndex;
    TUint iWriteIndex;
    Zapp::Argument* iWriteArg; // used for binary & string writing only
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
private: // IOutputProcessor
    void ProcessString(const Brx& aBuffer, Brhz& aVal);
    void ProcessInt(const Brx& aBuffer, TInt& aVal);
    void ProcessUint(const Brx& aBuffer, TUint& aVal);
    void ProcessBool(const Brx& aBuffer, TBool& aVal);
    void ProcessBinary(const Brx& aBuffer, Brh& aVal);
};

} // namespace Zapp

#endif // HEADER_CP_DEVICE_SOCKET