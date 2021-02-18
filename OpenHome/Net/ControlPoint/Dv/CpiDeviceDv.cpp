#include <OpenHome/Net/Private/CpiDeviceDv.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Net/Private/CpiSubscription.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Env.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpiDeviceDv

CpiDeviceDv::CpiDeviceDv(CpStack& aCpStack, DviDevice& aDevice)
    : iDeviceDv(aDevice)
    , iLock("CpDv")
    , iShutdownSem("CpDv", 1)
{
    iDeviceDv.AddWeakRef();
    iDeviceCp = new CpiDevice(aCpStack, iDeviceDv.Udn(), *this, *this, NULL);
    iDeviceCp->SetReady();
    iInvocable = new Invocable(*this);
}

CpiDeviceDv::~CpiDeviceDv()
{
    iShutdownSem.Wait(); // blocks until all DviSubscriptions are deleted
    delete iInvocable;
}

CpiDevice& CpiDeviceDv::Device()
{
    return *iDeviceCp;
}

void CpiDeviceDv::InvokeAction(Invocation& aInvocation)
{
    iDeviceDv.GetDvStack().NotifyControlPointUsed(Brn("Device/local"));
    aInvocation.SetInvoker(*iInvocable);
    iDeviceCp->GetCpStack().InvocationManager().Invoke(&aInvocation);
}

TBool CpiDeviceDv::GetAttribute(const char* aKey, Brh& aValue) const
{
    const TChar* value = NULL;
    iDeviceDv.GetAttribute(aKey, &value);
    if (value != NULL) {
        aValue.Set(value);
        return true;
    }
    return false;
}

TUint CpiDeviceDv::Subscribe(CpiSubscription& aSubscription, const OpenHome::Uri& /*aSubscriber*/)
{
    Brh sid;
    iDeviceDv.CreateSid(sid);
    Brn tmp(sid);
    Brh transfer(tmp);
    aSubscription.SetSid(transfer);
    DviSubscription* subscriptionDv = new DviSubscription(iDeviceDv.GetDvStack(), iDeviceDv, *this, NULL, sid);
    subscriptionDv->AddRef(); // guard against subscription expiring before client tries to renew or unsubscribe
    iDeviceDv.GetDvStack().SubscriptionManager().AddSubscription(*subscriptionDv);

    iLock.Wait();
    if (iSubscriptions.size() == 0) {
        iShutdownSem.Wait(); // consume shutdown signal now the map is non-empty
    }
    Brn sid2(subscriptionDv->Sid());
    Subscription* subscription = new Subscription(aSubscription, subscriptionDv);
    iSubscriptions.insert(std::pair<Brn,Subscription*>(sid2, subscription));
    iDeviceCp->AddRef();
    iLock.Signal();

    DviService* service = iDeviceDv.ServiceReference(aSubscription.ServiceType());
    ASSERT(service != NULL);
    service->AddSubscription(subscriptionDv);
    service->RemoveRef();

    const TUint durationSecs = iDeviceCp->GetCpStack().Env().InitParams()->SubscriptionDurationSecs();
    return durationSecs;
}

TUint CpiDeviceDv::Renew(CpiSubscription& /*aSubscription*/)
{
    const TUint durationSecs = iDeviceCp->GetCpStack().Env().InitParams()->SubscriptionDurationSecs();
    return durationSecs;
}

void CpiDeviceDv::Unsubscribe(CpiSubscription& aSubscription, const Brx& aSid)
{
    iLock.Wait();
    Brn sid(aSid);
    SubscriptionMap::iterator it = iSubscriptions.find(sid);
    if (it == iSubscriptions.end()) {
        iLock.Signal();
        return;
    }
    Subscription* subscription = it->second;
    iLock.Signal();
    DviService* service = iDeviceDv.ServiceReference(aSubscription.ServiceType());
    if (service != NULL) {
        service->RemoveSubscription(aSid);
        service->RemoveRef();
    }
    iLock.Wait();
    subscription->iCp = NULL;
    iLock.Signal();
    subscription->iDv->RemoveRef();
    // can't safely access subscription now - RemoveRef() above may have resulted in it being deleted
}

TBool CpiDeviceDv::OrphanSubscriptionsOnSubnetChange() const
{
    return false;
}

void CpiDeviceDv::NotifyRemovedBeforeReady()
{
}

TUint CpiDeviceDv::Version(const TChar* /*aDomain*/, const TChar* /*aName*/, TUint aProxyVersion) const
{
    return aProxyVersion; /* FIXME - could use DviDevice to determine actual version of service
                             Since we're in the same binary as that service, it isn't unusual to
                             expect cp to know which dv versions it is talking to however... */
}

void CpiDeviceDv::Release()
{
    iDeviceDv.RemoveWeakRef();
    iDeviceCp = NULL; // device will delete itself when this returns;
    delete this;
}

IPropertyWriter* CpiDeviceDv::ClaimWriter(const IDviSubscriptionUserData* /*aUserData*/,
                                          const Brx& aSid, TUint aSequenceNumber)
{
    AutoMutex _(iLock);
    Brn sid(aSid);
    SubscriptionMap::iterator it = iSubscriptions.find(sid);
    if (it == iSubscriptions.end()) {
        Log::Print("!!! CpiDeviceDv::ClaimWriter failed to find subscription\n");
        return NULL;
    }
    Subscription* subscription = it->second;
    ASSERT(subscription->iCp != NULL);
    if (!subscription->iCp->UpdateSequenceNumber(aSequenceNumber)) {
        subscription->iCp->SetNotificationError();
        return NULL;
    }
    subscription->iCp->Unlock();
    return new PropertyWriterDv(*(subscription->iCp));
}

void CpiDeviceDv::ReleaseWriter(IPropertyWriter* aWriter)
{
    delete aWriter;
}

void CpiDeviceDv::NotifySubscriptionCreated(const Brx& /*aSid*/)
{
}

void CpiDeviceDv::NotifySubscriptionDeleted(const Brx& aSid)
{
    {
        AutoMutex _(iLock);
        Brn sid(aSid);
        SubscriptionMap::iterator it = iSubscriptions.find(sid);
        ASSERT(it != iSubscriptions.end());
        delete it->second;
        iSubscriptions.erase(it);
        if (iSubscriptions.size() == 0) {
            iShutdownSem.Signal(); // unblock shutdown now we have no subscriptions that may be trying to event out updates
        }
    }
    iDeviceCp->RemoveRef();
}

void CpiDeviceDv::NotifySubscriptionExpired(const Brx& /*aSid*/)
{
}

void CpiDeviceDv::LogUserData(IWriter& aWriter, const IDviSubscriptionUserData& /*aUserData*/)
{
    aWriter.Write(Brn(", protocol: Dv"));
}


// class CpiDeviceDv::Invocable

CpiDeviceDv::Invocable::Invocable(CpiDeviceDv& aDevice)
    : iDevice(aDevice)
{
}

void CpiDeviceDv::Invocable::InvokeAction(Invocation& aInvocation)
{
    const OpenHome::Net::ServiceType& serviceType = aInvocation.ServiceType();
    DviService* service = iDevice.iDeviceDv.ServiceReference(serviceType);
    if (service == NULL) {
        LOG_ERROR(kCpDeviceDv, "CpiDeviceDv::Invocable::InvokeAction failed lookup for service %.*s:%.*s:%u\n",
                                  PBUF(serviceType.Domain()), PBUF(serviceType.Name()), serviceType.Version());
        const HttpStatus& err = HttpStatus::kNotFound;
        aInvocation.SetError(Error::eUpnp, err.Code(), err.Reason());
    }
    else {
        InvocationDv stream(aInvocation, *service);
        stream.Start();
        service->RemoveRef();
    }
}


// InvocationDv

InvocationDv::InvocationDv(Invocation& aInvocation, DviService& aService)
    : iInvocation(aInvocation)
    , iService(aService)
    , iWriteArg(NULL)
{
}

void InvocationDv::Start()
{
    Invoke();
}

void InvocationDv::Invoke()
{
    const Brx& actionName = iInvocation.Action().Name();
    try {
        iService.InvokeDirect(*this, actionName);
    }
    catch (InvocationError&) {}
    catch (ParameterValidationError&) {
        InvocationReportError(Error::eCodeParameterInvalid, Error::kDescriptionParameterInvalid);
    }
}

TUint InvocationDv::Version() const
{
    return iInvocation.ServiceType().Version();
}

const TIpAddress& InvocationDv::Adapter() const
{
    return kIpAddressV4AllAdapters;
}

const char* InvocationDv::ResourceUriPrefix() const
{
    return NULL;
}

Endpoint InvocationDv::ClientEndpoint() const
{
    return Endpoint(0, kIpAddressV4AllAdapters);
}

const Brx& InvocationDv::ClientUserAgent() const
{
    return Brx::Empty();
}

void InvocationDv::InvocationReadStart()
{
    iReadIndex = 0;
}

TBool InvocationDv::InvocationReadBool(const TChar* aName)
{
    ArgumentBool* arg = static_cast<ArgumentBool*>(InputArgument(aName));
    return arg->Value();
}

void InvocationDv::InvocationReadString(const TChar* aName, Brhz& aString)
{
    ArgumentString* arg = static_cast<ArgumentString*>(InputArgument(aName));
    aString.Set(arg->Value());
}

TInt InvocationDv::InvocationReadInt(const TChar* aName)
{
    ArgumentInt* arg = static_cast<ArgumentInt*>(InputArgument(aName));
    return arg->Value();
}

TUint InvocationDv::InvocationReadUint(const TChar* aName)
{
    ArgumentUint* arg = static_cast<ArgumentUint*>(InputArgument(aName));
    return arg->Value();
}

void InvocationDv::InvocationReadBinary(const TChar* aName, Brh& aData)
{
    ArgumentBinary* arg = static_cast<ArgumentBinary*>(InputArgument(aName));
    aData.Set(arg->Value());
}

void InvocationDv::InvocationReadEnd()
{
}

void InvocationDv::InvocationReportError(TUint aCode, const Brx& aDescription)
{
    iInvocation.SetError(Error::eUpnp, aCode, aDescription);
    THROW(InvocationError);
}

void InvocationDv::InvocationWriteStart()
{
    iWriteIndex = 0;
}

void InvocationDv::InvocationWriteBool(const TChar* aName, TBool aValue)
{
    Bws<1> buf;
    buf.SetBytes(1);
    buf[0] = (aValue? 1 : 0);
    OutputProcessorDv procDv;
    OutputArgument(aName)->ProcessOutput(procDv, buf);
}

void InvocationDv::InvocationWriteInt(const TChar* aName, TInt aValue)
{
    Bws<4> buf((const TByte*)&aValue, 4);
    OutputProcessorDv procDv;
    OutputArgument(aName)->ProcessOutput(procDv, buf);
}

void InvocationDv::InvocationWriteUint(const TChar* aName, TUint aValue)
{
    Bws<4> buf((const TByte*)&aValue, 4);
    OutputProcessorDv procDv;
    OutputArgument(aName)->ProcessOutput(procDv, buf);
}

void InvocationDv::InvocationWriteBinaryStart(const TChar* aName)
{
    ASSERT(iWriteArg == NULL);
    iWriteArg = OutputArgument(aName);
    ASSERT(static_cast<ArgumentBinary*>(iWriteArg)->Value().Bytes() == 0);
}

void InvocationDv::InvocationWriteBinary(TByte aValue)
{
    // binary and string writing are the same here since we're not base64 encoding or xml escaping the data
    InvocationWriteString(aValue);
}

void InvocationDv::InvocationWriteBinary(const Brx& aValue)
{
    InvocationWriteString(aValue);
}

void InvocationDv::InvocationWriteBinaryEnd(const TChar* aName)
{
    InvocationWriteStringEnd(aName);
}

void InvocationDv::InvocationWriteStringStart(const TChar* aName)
{
    ASSERT(iWriteArg == NULL);
    iWriteArg = OutputArgument(aName);
    ASSERT(static_cast<ArgumentString*>(iWriteArg)->Value().Bytes() == 0);
}

void InvocationDv::InvocationWriteString(TByte aValue)
{
    Brn buf(&aValue, 1);
    InvocationWriteString(buf);
}

void InvocationDv::InvocationWriteString(const Brx& aValue)
{
    ASSERT(iWriteArg != NULL);
    OutputProcessorDv procDv;
    iWriteArg->ProcessOutput(procDv, aValue);
}

void InvocationDv::InvocationWriteStringEnd(const TChar* /*aName*/)
{
    iWriteArg = NULL;
}

void InvocationDv::InvocationWriteEnd()
{
}

OpenHome::Net::Argument* InvocationDv::InputArgument(const TChar* aName)
{
    return Argument(aName, iInvocation.InputArguments(), iReadIndex);
}

OpenHome::Net::Argument* InvocationDv::OutputArgument(const TChar* aName)
{
    return Argument(aName, iInvocation.OutputArguments(), iWriteIndex);
}

OpenHome::Net::Argument* InvocationDv::Argument(const TChar* aName, const Invocation::VectorArguments& aVector, TUint& aIndex)
{
    OpenHome::Net::Argument* ret = NULL;
    Brn name(aName);
    TUint index = aIndex;
    do {
        OpenHome::Net::Argument* arg = aVector[index];
        if (arg->Parameter().Name() == name) {
            ret = arg;
            break;
        }
        GetNextIndex(index, aVector);
    } while (index != aIndex);
    ASSERT(ret != NULL);
    GetNextIndex(aIndex, aVector);
    return ret;
}

void InvocationDv::GetNextIndex(TUint& aIndex, const Invocation::VectorArguments& aVector)
{
    aIndex++;
    if (aIndex == aVector.size()) {
        aIndex = 0;
    }
}


// PropertyWriterDv

PropertyWriterDv::PropertyWriterDv(IEventProcessor& aEventProcessor)
    : iEventProcessor(aEventProcessor)
{
    iEventProcessor.EventUpdateStart();
}

void PropertyWriterDv::PropertyWriteString(const Brx& aName, const Brx& aValue)
{
    OutputProcessorDv procDv;
    iEventProcessor.EventUpdate(aName, aValue, procDv);
}

void PropertyWriterDv::PropertyWriteInt(const Brx& aName, TInt aValue)
{
    Bws<4> buf((const TByte*)&aValue, 4);
    OutputProcessorDv procDv;
    iEventProcessor.EventUpdate(aName, buf, procDv);
}

void PropertyWriterDv::PropertyWriteUint(const Brx& aName, TUint aValue)
{
    Bws<4> buf((const TByte*)&aValue, 4);
    OutputProcessorDv procDv;
    iEventProcessor.EventUpdate(aName, buf, procDv);
}

void PropertyWriterDv::PropertyWriteBool(const Brx& aName, TBool aValue)
{
    Bws<1> buf;
    buf.SetBytes(1);
    buf[0] = (aValue? 1 : 0);
    OutputProcessorDv procDv;
    iEventProcessor.EventUpdate(aName, buf, procDv);
}

void PropertyWriterDv::PropertyWriteBinary(const Brx& aName, const Brx& aValue)
{
    OutputProcessorDv procDv;
    iEventProcessor.EventUpdate(aName, aValue, procDv);
}

void PropertyWriterDv::PropertyWriteEnd()
{
    iEventProcessor.EventUpdateEnd();
}

void PropertyWriterDv::Release()
{
    delete this;
}


// OutputProcessorDv

void OutputProcessorDv::ProcessString(const Brx& aBuffer, Brhz& aVal)
{
    TUint bytes = aVal.Bytes() + aBuffer.Bytes();
    Bwh tmp(bytes + 1);
    tmp.Append(aVal);
    tmp.Append(aBuffer);
    tmp.Append((TByte)0);
    tmp.SetBytes(bytes);
    tmp.TransferTo(aVal);
}

void OutputProcessorDv::ProcessInt(const Brx& aBuffer, TInt& aVal)
{
    ASSERT(aBuffer.Bytes() == 4);
    (void)memcpy(&aVal, aBuffer.Ptr(), 4);
}

void OutputProcessorDv::ProcessUint(const Brx& aBuffer, TUint& aVal)
{
    ASSERT(aBuffer.Bytes() == 4);
    (void)memcpy(&aVal, aBuffer.Ptr(), 4);
}

void OutputProcessorDv::ProcessBool(const Brx& aBuffer, TBool& aVal)
{
    ASSERT(aBuffer.Bytes() == 1);
    aVal = (aBuffer[0] != 0);
}

void OutputProcessorDv::ProcessBinary(const Brx& aBuffer, Brh& aVal)
{
    Bwh tmp(aVal.Bytes() + aBuffer.Bytes());
    tmp.Append(aVal);
    tmp.Append(aBuffer);
    tmp.TransferTo(aVal);
}
