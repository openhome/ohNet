#include "DvOpenhomeOrgSubscriptionLongPoll1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/C/DvInvocation.h>
#include <OpenHome/Net/C/DvInvocationPrivate.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class DvProviderOpenhomeOrgSubscriptionLongPoll1C : public DvProvider
{
public:
    DvProviderOpenhomeOrgSubscriptionLongPoll1C(DvDeviceC aDevice);
    void EnableActionSubscribe(CallbackSubscriptionLongPoll1Subscribe aCallback, void* aPtr);
    void EnableActionUnsubscribe(CallbackSubscriptionLongPoll1Unsubscribe aCallback, void* aPtr);
    void EnableActionRenew(CallbackSubscriptionLongPoll1Renew aCallback, void* aPtr);
    void EnableActionGetPropertyUpdates(CallbackSubscriptionLongPoll1GetPropertyUpdates aCallback, void* aPtr);
private:
    void DoSubscribe(IDviInvocation& aInvocation);
    void DoUnsubscribe(IDviInvocation& aInvocation);
    void DoRenew(IDviInvocation& aInvocation);
    void DoGetPropertyUpdates(IDviInvocation& aInvocation);
private:
    CallbackSubscriptionLongPoll1Subscribe iCallbackSubscribe;
    void* iPtrSubscribe;
    CallbackSubscriptionLongPoll1Unsubscribe iCallbackUnsubscribe;
    void* iPtrUnsubscribe;
    CallbackSubscriptionLongPoll1Renew iCallbackRenew;
    void* iPtrRenew;
    CallbackSubscriptionLongPoll1GetPropertyUpdates iCallbackGetPropertyUpdates;
    void* iPtrGetPropertyUpdates;
};

DvProviderOpenhomeOrgSubscriptionLongPoll1C::DvProviderOpenhomeOrgSubscriptionLongPoll1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "openhome.org", "SubscriptionLongPoll", 1)
{
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1C::EnableActionSubscribe(CallbackSubscriptionLongPoll1Subscribe aCallback, void* aPtr)
{
    iCallbackSubscribe = aCallback;
    iPtrSubscribe = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Subscribe");
    action->AddInputParameter(new ParameterString("ClientId"));
    action->AddInputParameter(new ParameterString("Udn"));
    action->AddInputParameter(new ParameterString("Service"));
    action->AddInputParameter(new ParameterUint("RequestedDuration"));
    action->AddOutputParameter(new ParameterString("Sid"));
    action->AddOutputParameter(new ParameterUint("Duration"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgSubscriptionLongPoll1C::DoSubscribe);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1C::EnableActionUnsubscribe(CallbackSubscriptionLongPoll1Unsubscribe aCallback, void* aPtr)
{
    iCallbackUnsubscribe = aCallback;
    iPtrUnsubscribe = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Unsubscribe");
    action->AddInputParameter(new ParameterString("Sid"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgSubscriptionLongPoll1C::DoUnsubscribe);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1C::EnableActionRenew(CallbackSubscriptionLongPoll1Renew aCallback, void* aPtr)
{
    iCallbackRenew = aCallback;
    iPtrRenew = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Renew");
    action->AddInputParameter(new ParameterString("Sid"));
    action->AddInputParameter(new ParameterUint("RequestedDuration"));
    action->AddOutputParameter(new ParameterUint("Duration"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgSubscriptionLongPoll1C::DoRenew);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1C::EnableActionGetPropertyUpdates(CallbackSubscriptionLongPoll1GetPropertyUpdates aCallback, void* aPtr)
{
    iCallbackGetPropertyUpdates = aCallback;
    iPtrGetPropertyUpdates = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetPropertyUpdates");
    action->AddInputParameter(new ParameterString("ClientId"));
    action->AddOutputParameter(new ParameterString("Updates"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgSubscriptionLongPoll1C::DoGetPropertyUpdates);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1C::DoSubscribe(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz ClientId;
    aInvocation.InvocationReadString("ClientId", ClientId);
    Brhz Udn;
    aInvocation.InvocationReadString("Udn", Udn);
    Brhz Service;
    aInvocation.InvocationReadString("Service", Service);
    TUint RequestedDuration = aInvocation.InvocationReadUint("RequestedDuration");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Sid;
    uint32_t Duration;
    ASSERT(iCallbackSubscribe != NULL);
    if (0 != iCallbackSubscribe(iPtrSubscribe, invocationC, invocationCPtr, (const char*)ClientId.Ptr(), (const char*)Udn.Ptr(), (const char*)Service.Ptr(), RequestedDuration, &Sid, &Duration)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respSid(aInvocation, "Sid");
    DviInvocationResponseUint respDuration(aInvocation, "Duration");
    invocation.StartResponse();
    Brhz bufSid((const TChar*)Sid);
    OhNetFreeExternal(Sid);
    respSid.Write(bufSid);
    respSid.WriteFlush();
    respDuration.Write(Duration);
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1C::DoUnsubscribe(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz Sid;
    aInvocation.InvocationReadString("Sid", Sid);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackUnsubscribe != NULL);
    if (0 != iCallbackUnsubscribe(iPtrUnsubscribe, invocationC, invocationCPtr, (const char*)Sid.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1C::DoRenew(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz Sid;
    aInvocation.InvocationReadString("Sid", Sid);
    TUint RequestedDuration = aInvocation.InvocationReadUint("RequestedDuration");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Duration;
    ASSERT(iCallbackRenew != NULL);
    if (0 != iCallbackRenew(iPtrRenew, invocationC, invocationCPtr, (const char*)Sid.Ptr(), RequestedDuration, &Duration)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respDuration(aInvocation, "Duration");
    invocation.StartResponse();
    respDuration.Write(Duration);
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgSubscriptionLongPoll1C::DoGetPropertyUpdates(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz ClientId;
    aInvocation.InvocationReadString("ClientId", ClientId);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Updates;
    ASSERT(iCallbackGetPropertyUpdates != NULL);
    if (0 != iCallbackGetPropertyUpdates(iPtrGetPropertyUpdates, invocationC, invocationCPtr, (const char*)ClientId.Ptr(), &Updates)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respUpdates(aInvocation, "Updates");
    invocation.StartResponse();
    Brhz bufUpdates((const TChar*)Updates);
    OhNetFreeExternal(Updates);
    respUpdates.Write(bufUpdates);
    respUpdates.WriteFlush();
    invocation.EndResponse();
}



THandle STDCALL DvProviderOpenhomeOrgSubscriptionLongPoll1Create(DvDeviceC aDevice)
{
    return new DvProviderOpenhomeOrgSubscriptionLongPoll1C(aDevice);
}

void STDCALL DvProviderOpenhomeOrgSubscriptionLongPoll1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderOpenhomeOrgSubscriptionLongPoll1C*>(aProvider);
}

void STDCALL DvProviderOpenhomeOrgSubscriptionLongPoll1EnableActionSubscribe(THandle aProvider, CallbackSubscriptionLongPoll1Subscribe aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgSubscriptionLongPoll1C*>(aProvider)->EnableActionSubscribe(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgSubscriptionLongPoll1EnableActionUnsubscribe(THandle aProvider, CallbackSubscriptionLongPoll1Unsubscribe aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgSubscriptionLongPoll1C*>(aProvider)->EnableActionUnsubscribe(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgSubscriptionLongPoll1EnableActionRenew(THandle aProvider, CallbackSubscriptionLongPoll1Renew aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgSubscriptionLongPoll1C*>(aProvider)->EnableActionRenew(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgSubscriptionLongPoll1EnableActionGetPropertyUpdates(THandle aProvider, CallbackSubscriptionLongPoll1GetPropertyUpdates aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgSubscriptionLongPoll1C*>(aProvider)->EnableActionGetPropertyUpdates(aCallback, aPtr);
}

