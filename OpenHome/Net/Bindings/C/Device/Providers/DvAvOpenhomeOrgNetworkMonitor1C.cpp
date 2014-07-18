#include "DvAvOpenhomeOrgNetworkMonitor1.h"
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

class DvProviderAvOpenhomeOrgNetworkMonitor1C : public DvProvider
{
public:
    DvProviderAvOpenhomeOrgNetworkMonitor1C(DvDeviceC aDevice);
    TBool SetPropertyName(const Brx& aValue);
    void GetPropertyName(Brhz& aValue);
    TBool SetPropertySender(TUint aValue);
    void GetPropertySender(TUint& aValue);
    TBool SetPropertyReceiver(TUint aValue);
    void GetPropertyReceiver(TUint& aValue);
    TBool SetPropertyResults(TUint aValue);
    void GetPropertyResults(TUint& aValue);
    void EnablePropertyName();
    void EnablePropertySender();
    void EnablePropertyReceiver();
    void EnablePropertyResults();
    void EnableActionName(CallbackNetworkMonitor1Name aCallback, void* aPtr);
    void EnableActionPorts(CallbackNetworkMonitor1Ports aCallback, void* aPtr);
private:
    void DoName(IDviInvocation& aInvocation);
    void DoPorts(IDviInvocation& aInvocation);
private:
    CallbackNetworkMonitor1Name iCallbackName;
    void* iPtrName;
    CallbackNetworkMonitor1Ports iCallbackPorts;
    void* iPtrPorts;
    PropertyString* iPropertyName;
    PropertyUint* iPropertySender;
    PropertyUint* iPropertyReceiver;
    PropertyUint* iPropertyResults;
};

DvProviderAvOpenhomeOrgNetworkMonitor1C::DvProviderAvOpenhomeOrgNetworkMonitor1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "av.openhome.org", "NetworkMonitor", 1)
{
    iPropertyName = NULL;
    iPropertySender = NULL;
    iPropertyReceiver = NULL;
    iPropertyResults = NULL;
}

TBool DvProviderAvOpenhomeOrgNetworkMonitor1C::SetPropertyName(const Brx& aValue)
{
    ASSERT(iPropertyName != NULL);
    return SetPropertyString(*iPropertyName, aValue);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1C::GetPropertyName(Brhz& aValue)
{
    ASSERT(iPropertyName != NULL);
    aValue.Set(iPropertyName->Value());
}

TBool DvProviderAvOpenhomeOrgNetworkMonitor1C::SetPropertySender(TUint aValue)
{
    ASSERT(iPropertySender != NULL);
    return SetPropertyUint(*iPropertySender, aValue);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1C::GetPropertySender(TUint& aValue)
{
    ASSERT(iPropertySender != NULL);
    aValue = iPropertySender->Value();
}

TBool DvProviderAvOpenhomeOrgNetworkMonitor1C::SetPropertyReceiver(TUint aValue)
{
    ASSERT(iPropertyReceiver != NULL);
    return SetPropertyUint(*iPropertyReceiver, aValue);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1C::GetPropertyReceiver(TUint& aValue)
{
    ASSERT(iPropertyReceiver != NULL);
    aValue = iPropertyReceiver->Value();
}

TBool DvProviderAvOpenhomeOrgNetworkMonitor1C::SetPropertyResults(TUint aValue)
{
    ASSERT(iPropertyResults != NULL);
    return SetPropertyUint(*iPropertyResults, aValue);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1C::GetPropertyResults(TUint& aValue)
{
    ASSERT(iPropertyResults != NULL);
    aValue = iPropertyResults->Value();
}

void DvProviderAvOpenhomeOrgNetworkMonitor1C::EnablePropertyName()
{
    iPropertyName = new PropertyString(iDvStack.Env(), new ParameterString("Name"));
    iService->AddProperty(iPropertyName); // passes ownership
}

void DvProviderAvOpenhomeOrgNetworkMonitor1C::EnablePropertySender()
{
    iPropertySender = new PropertyUint(iDvStack.Env(), new ParameterUint("Sender"));
    iService->AddProperty(iPropertySender); // passes ownership
}

void DvProviderAvOpenhomeOrgNetworkMonitor1C::EnablePropertyReceiver()
{
    iPropertyReceiver = new PropertyUint(iDvStack.Env(), new ParameterUint("Receiver"));
    iService->AddProperty(iPropertyReceiver); // passes ownership
}

void DvProviderAvOpenhomeOrgNetworkMonitor1C::EnablePropertyResults()
{
    iPropertyResults = new PropertyUint(iDvStack.Env(), new ParameterUint("Results"));
    iService->AddProperty(iPropertyResults); // passes ownership
}

void DvProviderAvOpenhomeOrgNetworkMonitor1C::EnableActionName(CallbackNetworkMonitor1Name aCallback, void* aPtr)
{
    iCallbackName = aCallback;
    iPtrName = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Name");
    action->AddOutputParameter(new ParameterRelated("Name", *iPropertyName));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgNetworkMonitor1C::DoName);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1C::EnableActionPorts(CallbackNetworkMonitor1Ports aCallback, void* aPtr)
{
    iCallbackPorts = aCallback;
    iPtrPorts = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Ports");
    action->AddOutputParameter(new ParameterRelated("Sender", *iPropertySender));
    action->AddOutputParameter(new ParameterRelated("Receiver", *iPropertyReceiver));
    action->AddOutputParameter(new ParameterRelated("Results", *iPropertyResults));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgNetworkMonitor1C::DoPorts);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgNetworkMonitor1C::DoName(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Name;
    ASSERT(iCallbackName != NULL);
    if (0 != iCallbackName(iPtrName, invocationC, invocationCPtr, &Name)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respName(aInvocation, "Name");
    invocation.StartResponse();
    Brhz bufName((const TChar*)Name);
    OhNetFreeExternal(Name);
    respName.Write(bufName);
    respName.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgNetworkMonitor1C::DoPorts(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Sender;
    uint32_t Receiver;
    uint32_t Results;
    ASSERT(iCallbackPorts != NULL);
    if (0 != iCallbackPorts(iPtrPorts, invocationC, invocationCPtr, &Sender, &Receiver, &Results)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respSender(aInvocation, "Sender");
    DviInvocationResponseUint respReceiver(aInvocation, "Receiver");
    DviInvocationResponseUint respResults(aInvocation, "Results");
    invocation.StartResponse();
    respSender.Write(Sender);
    respReceiver.Write(Receiver);
    respResults.Write(Results);
    invocation.EndResponse();
}



THandle STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1Create(DvDeviceC aDevice)
{
    return new DvProviderAvOpenhomeOrgNetworkMonitor1C(aDevice);
}

void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider);
}

void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1EnableActionName(THandle aProvider, CallbackNetworkMonitor1Name aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider)->EnableActionName(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1EnableActionPorts(THandle aProvider, CallbackNetworkMonitor1Ports aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider)->EnableActionPorts(aCallback, aPtr);
}

int32_t STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1SetPropertyName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider)->SetPropertyName(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1GetPropertyName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider)->GetPropertyName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1SetPropertySender(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider)->SetPropertySender(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1GetPropertySender(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider)->GetPropertySender(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1SetPropertyReceiver(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider)->SetPropertyReceiver(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1GetPropertyReceiver(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider)->GetPropertyReceiver(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1SetPropertyResults(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider)->SetPropertyResults(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1GetPropertyResults(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider)->GetPropertyResults(val);
    *aValue = val;
}

void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertyName(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider)->EnablePropertyName();
}

void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertySender(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider)->EnablePropertySender();
}

void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertyReceiver(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider)->EnablePropertyReceiver();
}

void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertyResults(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgNetworkMonitor1C*>(aProvider)->EnablePropertyResults();
}

