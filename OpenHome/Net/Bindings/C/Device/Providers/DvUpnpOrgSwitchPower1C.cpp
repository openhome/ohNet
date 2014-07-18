#include "DvUpnpOrgSwitchPower1.h"
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

class DvProviderUpnpOrgSwitchPower1C : public DvProvider
{
public:
    DvProviderUpnpOrgSwitchPower1C(DvDeviceC aDevice);
    TBool SetPropertyStatus(TBool aValue);
    void GetPropertyStatus(TBool& aValue);
    void EnablePropertyStatus();
    void EnableActionSetTarget(CallbackSwitchPower1SetTarget aCallback, void* aPtr);
    void EnableActionGetTarget(CallbackSwitchPower1GetTarget aCallback, void* aPtr);
    void EnableActionGetStatus(CallbackSwitchPower1GetStatus aCallback, void* aPtr);
private:
    void DoSetTarget(IDviInvocation& aInvocation);
    void DoGetTarget(IDviInvocation& aInvocation);
    void DoGetStatus(IDviInvocation& aInvocation);
private:
    CallbackSwitchPower1SetTarget iCallbackSetTarget;
    void* iPtrSetTarget;
    CallbackSwitchPower1GetTarget iCallbackGetTarget;
    void* iPtrGetTarget;
    CallbackSwitchPower1GetStatus iCallbackGetStatus;
    void* iPtrGetStatus;
    PropertyBool* iPropertyStatus;
};

DvProviderUpnpOrgSwitchPower1C::DvProviderUpnpOrgSwitchPower1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "upnp.org", "SwitchPower", 1)
{
    iPropertyStatus = NULL;
}

TBool DvProviderUpnpOrgSwitchPower1C::SetPropertyStatus(TBool aValue)
{
    ASSERT(iPropertyStatus != NULL);
    return SetPropertyBool(*iPropertyStatus, aValue);
}

void DvProviderUpnpOrgSwitchPower1C::GetPropertyStatus(TBool& aValue)
{
    ASSERT(iPropertyStatus != NULL);
    aValue = iPropertyStatus->Value();
}

void DvProviderUpnpOrgSwitchPower1C::EnablePropertyStatus()
{
    iPropertyStatus = new PropertyBool(iDvStack.Env(), new ParameterBool("Status"));
    iService->AddProperty(iPropertyStatus); // passes ownership
}

void DvProviderUpnpOrgSwitchPower1C::EnableActionSetTarget(CallbackSwitchPower1SetTarget aCallback, void* aPtr)
{
    iCallbackSetTarget = aCallback;
    iPtrSetTarget = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetTarget");
    action->AddInputParameter(new ParameterBool("newTargetValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgSwitchPower1C::DoSetTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1C::EnableActionGetTarget(CallbackSwitchPower1GetTarget aCallback, void* aPtr)
{
    iCallbackGetTarget = aCallback;
    iPtrGetTarget = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetTarget");
    action->AddOutputParameter(new ParameterBool("RetTargetValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgSwitchPower1C::DoGetTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1C::EnableActionGetStatus(CallbackSwitchPower1GetStatus aCallback, void* aPtr)
{
    iCallbackGetStatus = aCallback;
    iPtrGetStatus = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStatus");
    action->AddOutputParameter(new ParameterRelated("ResultStatus", *iPropertyStatus));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgSwitchPower1C::DoGetStatus);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgSwitchPower1C::DoSetTarget(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TBool newTargetValue = aInvocation.InvocationReadBool("newTargetValue");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetTarget != NULL);
    if (0 != iCallbackSetTarget(iPtrSetTarget, invocationC, invocationCPtr, newTargetValue)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgSwitchPower1C::DoGetTarget(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t RetTargetValue;
    ASSERT(iCallbackGetTarget != NULL);
    if (0 != iCallbackGetTarget(iPtrGetTarget, invocationC, invocationCPtr, &RetTargetValue)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respRetTargetValue(aInvocation, "RetTargetValue");
    invocation.StartResponse();
    respRetTargetValue.Write((RetTargetValue!=0));
    invocation.EndResponse();
}

void DvProviderUpnpOrgSwitchPower1C::DoGetStatus(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t ResultStatus;
    ASSERT(iCallbackGetStatus != NULL);
    if (0 != iCallbackGetStatus(iPtrGetStatus, invocationC, invocationCPtr, &ResultStatus)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respResultStatus(aInvocation, "ResultStatus");
    invocation.StartResponse();
    respResultStatus.Write((ResultStatus!=0));
    invocation.EndResponse();
}



THandle STDCALL DvProviderUpnpOrgSwitchPower1Create(DvDeviceC aDevice)
{
    return new DvProviderUpnpOrgSwitchPower1C(aDevice);
}

void STDCALL DvProviderUpnpOrgSwitchPower1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider);
}

void STDCALL DvProviderUpnpOrgSwitchPower1EnableActionSetTarget(THandle aProvider, CallbackSwitchPower1SetTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->EnableActionSetTarget(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgSwitchPower1EnableActionGetTarget(THandle aProvider, CallbackSwitchPower1GetTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->EnableActionGetTarget(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgSwitchPower1EnableActionGetStatus(THandle aProvider, CallbackSwitchPower1GetStatus aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->EnableActionGetStatus(aCallback, aPtr);
}

int32_t STDCALL DvProviderUpnpOrgSwitchPower1SetPropertyStatus(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->SetPropertyStatus((aValue!=0))? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgSwitchPower1GetPropertyStatus(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->GetPropertyStatus(val);
    *aValue = (val? 1 : 0);
}

void STDCALL DvProviderUpnpOrgSwitchPower1EnablePropertyStatus(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->EnablePropertyStatus();
}

