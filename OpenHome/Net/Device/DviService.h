#ifndef HEADER_DVISERVICE
#define HEADER_DVISERVICE

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Core/OhNet.h>

#include <vector>

EXCEPTION(InvocationError)

namespace OpenHome {
namespace Net {

class IDviInvocation
{
public:
    virtual void Invoke() = 0;

    virtual TUint Version() const = 0;
    virtual TIpAddress Adapter() const = 0;
    virtual const char* ResourceUriPrefix() const = 0;
    virtual Endpoint ClientEndpoint() const = 0;

    virtual void InvocationReadStart() = 0;
    virtual TBool InvocationReadBool(const TChar* aName) = 0;
    virtual void InvocationReadString(const TChar* aName, Brhz& aString) = 0;
    virtual TInt InvocationReadInt(const TChar* aName) = 0;
    virtual TUint InvocationReadUint(const TChar* aName) = 0;
    virtual void InvocationReadBinary(const TChar* aName, Brh& aData) = 0;
    virtual void InvocationReadEnd() = 0;

    virtual void InvocationReportError(TUint aCode, const Brx& aDescription) = 0;

    virtual void InvocationWriteStart() = 0;
    virtual void InvocationWriteBool(const TChar* aName, TBool aValue) = 0;
    virtual void InvocationWriteInt(const TChar* aName, TInt aValue) = 0;
    virtual void InvocationWriteUint(const TChar* aName, TUint aValue) = 0;
    virtual void InvocationWriteBinaryStart(const TChar* aName) = 0;
    virtual void InvocationWriteBinary(TByte aValue) = 0;
    virtual void InvocationWriteBinary(const Brx& aValue) = 0;
    virtual void InvocationWriteBinaryEnd(const TChar* aName) = 0;
    virtual void InvocationWriteStringStart(const TChar* aName) = 0;
    virtual void InvocationWriteString(TByte aValue) = 0;
    virtual void InvocationWriteString(const Brx& aValue) = 0;
    virtual void InvocationWriteStringEnd(const TChar* aName) = 0;
    virtual void InvocationWriteEnd() = 0;

    virtual ~IDviInvocation() {}
};

class DvAction
{
public:
    DvAction(OpenHome::Net::Action* aAction, FunctorDviInvocation aFunctor);
    OpenHome::Net::Action* Action();
    const OpenHome::Net::Action* Action() const;
    FunctorDviInvocation Functor() const;
private:
    OpenHome::Net::Action* iAction;
    FunctorDviInvocation iFunctor;
};

class DviDevice;
class DvStack;

class DviService : public Service, private IStackObject
{
public:
    DviService(DvStack& aDvStack, const TChar* aDomain, const TChar* aName, TUint aVersion);
    void AddRef();
    void RemoveRef();
    void StopSubscriptions();
    void Enable();
    void Disable();

    DllExport void AddAction(Action* aAction, FunctorDviInvocation aFunctor);
    const std::vector<DvAction>& DvActions() const;
    void Invoke(IDviInvocation& aInvocation, const Brx& aActionName);

    void PropertiesLock();
    void PropertiesUnlock();
    DllExport void AddProperty(Property* aProperty);
    const std::vector<Property*>& Properties() const;
    void PublishPropertyUpdates();

    void AddSubscription(DviSubscription* aSubscription);
    void RemoveSubscription(const Brx& aSid);
private:
    ~DviService();
    void InvocationCompleted();
    TBool AssertPropertiesInitialised() const;
private: // from IStackObject
    void ListObjectDetails() const;
private:
    DvStack& iDvStack;
    Mutex iLock;
    TUint iRefCount;
    Mutex iPropertiesLock;
    std::vector<DvAction> iDvActions;
    std::vector<Property*> iProperties;
    std::vector<DviSubscription*> iSubscriptions;
    TBool iDisabled;
    TUint iCurrentInvocationCount;
    Semaphore iDisabledSem;
};

/**
 * Utility class.
 *
 * Create an AutoServiceRef on the stack using a reference to a DviService.
 * It will automatically call RemoveRef on stack cleanup (ie on return or when
 * an exception passes up).
 */
class AutoServiceRef : public INonCopyable
{
public:
    AutoServiceRef(DviService*& aService);
    ~AutoServiceRef();
private:
    DviService*& iService;
};

class DllExportClass DviInvocation : public IDvInvocation, private INonCopyable
{
public:
    DllExport DviInvocation(IDviInvocation& aInvocation);
    virtual TUint Version() const;
    virtual void Error(TInt aCode, const Brx& aReason);
    virtual void StartResponse();
    virtual void EndResponse();
    virtual TIpAddress Adapter() const;
    virtual const char* ResourceUriPrefix() const;
    virtual Endpoint ClientEndpoint() const;
private:
    IDviInvocation& iInvocation;
};

class DllExportClass DviInvocationResponseBool : public IDvInvocationResponseBool, private INonCopyable
{
public:
    DllExport DviInvocationResponseBool(IDviInvocation& aInvocation, const TChar* aName);
    void Write(TBool aValue);
private:
    IDviInvocation& iInvocation;
    const TChar* iName;
};

class DllExportClass DviInvocationResponseUint : public IDvInvocationResponseUint, private INonCopyable
{
public:
    DllExport DviInvocationResponseUint(IDviInvocation& aInvocation, const TChar* aName);
    void Write(TUint aValue);
private:
    IDviInvocation& iInvocation;
    const TChar* iName;
};

class DllExportClass DviInvocationResponseInt : public IDvInvocationResponseInt, private INonCopyable
{
public:
    DllExport DviInvocationResponseInt(IDviInvocation& aInvocation, const TChar* aName);
    void Write(TInt aValue);
private:
    IDviInvocation& iInvocation;
    const TChar* iName;
};

class DllExportClass DviInvocationResponseBinary : public IDvInvocationResponseBinary, private INonCopyable
{
public:
    DllExport DviInvocationResponseBinary(IDviInvocation& aInvocation, const TChar* aName);
    // IWriter
    void Write(TByte aValue);
    void Write(const Brx& aValue);
    void WriteFlush();
private:
    void CheckFirst();
private:
    IDviInvocation& iInvocation;
    const TChar* iName;
    TBool iFirst;
};

class DllExportClass DviInvocationResponseString : public IDvInvocationResponseString, private INonCopyable
{
public:
    DllExport DviInvocationResponseString(IDviInvocation& aInvocation, const TChar* aName);
    // IWriter
    void Write(TByte aValue);
    void Write(const Brx& aValue);
    void WriteFlush();
private:
    void CheckFirst();
private:
    IDviInvocation& iInvocation;
    const TChar* iName;
    TBool iFirst;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVISERVICE
