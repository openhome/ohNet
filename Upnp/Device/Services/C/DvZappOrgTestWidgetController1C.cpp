#include "DvZappOrgTestWidgetController1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

class DvProviderZappOrgTestWidgetController1C : public DvProvider
{
public:
    DvProviderZappOrgTestWidgetController1C(DvDeviceC aDevice);
    void EnableActionCreateWidget(CallbackTestWidgetController1CreateWidget aCallback, void* aPtr);
    void EnableActionRemoveWidget(CallbackTestWidgetController1RemoveWidget aCallback, void* aPtr);
    void EnableActionSetWidgetRegister(CallbackTestWidgetController1SetWidgetRegister aCallback, void* aPtr);
    void EnableActionGetWidgetRegister(CallbackTestWidgetController1GetWidgetRegister aCallback, void* aPtr);
private:
    void DoCreateWidget(IDviInvocation& aInvocation, TUint aVersion);
    void DoRemoveWidget(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetWidgetRegister(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetWidgetRegister(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackTestWidgetController1CreateWidget iCallbackCreateWidget;
    void* iPtrCreateWidget;
    CallbackTestWidgetController1RemoveWidget iCallbackRemoveWidget;
    void* iPtrRemoveWidget;
    CallbackTestWidgetController1SetWidgetRegister iCallbackSetWidgetRegister;
    void* iPtrSetWidgetRegister;
    CallbackTestWidgetController1GetWidgetRegister iCallbackGetWidgetRegister;
    void* iPtrGetWidgetRegister;
};

DvProviderZappOrgTestWidgetController1C::DvProviderZappOrgTestWidgetController1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "zapp.org", "TestWidgetController", 1)
{
    
}

void DvProviderZappOrgTestWidgetController1C::EnableActionCreateWidget(CallbackTestWidgetController1CreateWidget aCallback, void* aPtr)
{
    iCallbackCreateWidget = aCallback;
    iPtrCreateWidget = aPtr;
    Zapp::Action* action = new Zapp::Action("CreateWidget");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    action->AddInputParameter(new ParameterUint("WidgetClass"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidgetController1C::DoCreateWidget);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidgetController1C::EnableActionRemoveWidget(CallbackTestWidgetController1RemoveWidget aCallback, void* aPtr)
{
    iCallbackRemoveWidget = aCallback;
    iPtrRemoveWidget = aPtr;
    Zapp::Action* action = new Zapp::Action("RemoveWidget");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidgetController1C::DoRemoveWidget);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidgetController1C::EnableActionSetWidgetRegister(CallbackTestWidgetController1SetWidgetRegister aCallback, void* aPtr)
{
    iCallbackSetWidgetRegister = aCallback;
    iPtrSetWidgetRegister = aPtr;
    Zapp::Action* action = new Zapp::Action("SetWidgetRegister");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    action->AddInputParameter(new ParameterUint("RegisterIndex"));
    action->AddInputParameter(new ParameterUint("RegisterValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidgetController1C::DoSetWidgetRegister);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidgetController1C::EnableActionGetWidgetRegister(CallbackTestWidgetController1GetWidgetRegister aCallback, void* aPtr)
{
    iCallbackGetWidgetRegister = aCallback;
    iPtrGetWidgetRegister = aPtr;
    Zapp::Action* action = new Zapp::Action("GetWidgetRegister");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    action->AddInputParameter(new ParameterUint("RegisterIndex"));
    action->AddOutputParameter(new ParameterUint("RegisterValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidgetController1C::DoGetWidgetRegister);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidgetController1C::DoCreateWidget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz WidgetUdn;
    aInvocation.InvocationReadString("WidgetUdn", WidgetUdn);
    TUint WidgetClass = aInvocation.InvocationReadUint("WidgetClass");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackCreateWidget != NULL);
    if (0 != iCallbackCreateWidget(iPtrCreateWidget, aVersion, (const char*)WidgetUdn.Ptr(), WidgetClass)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderZappOrgTestWidgetController1C::DoRemoveWidget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz WidgetUdn;
    aInvocation.InvocationReadString("WidgetUdn", WidgetUdn);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackRemoveWidget != NULL);
    if (0 != iCallbackRemoveWidget(iPtrRemoveWidget, aVersion, (const char*)WidgetUdn.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderZappOrgTestWidgetController1C::DoSetWidgetRegister(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz WidgetUdn;
    aInvocation.InvocationReadString("WidgetUdn", WidgetUdn);
    TUint RegisterIndex = aInvocation.InvocationReadUint("RegisterIndex");
    TUint RegisterValue = aInvocation.InvocationReadUint("RegisterValue");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetWidgetRegister != NULL);
    if (0 != iCallbackSetWidgetRegister(iPtrSetWidgetRegister, aVersion, (const char*)WidgetUdn.Ptr(), RegisterIndex, RegisterValue)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderZappOrgTestWidgetController1C::DoGetWidgetRegister(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz WidgetUdn;
    aInvocation.InvocationReadString("WidgetUdn", WidgetUdn);
    TUint RegisterIndex = aInvocation.InvocationReadUint("RegisterIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t RegisterValue;
    ASSERT(iCallbackGetWidgetRegister != NULL);
    if (0 != iCallbackGetWidgetRegister(iPtrGetWidgetRegister, aVersion, (const char*)WidgetUdn.Ptr(), RegisterIndex, &RegisterValue)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respRegisterValue(aInvocation, "RegisterValue");
    resp.Start();
    respRegisterValue.Write(RegisterValue);
    resp.End();
}



THandle DvProviderZappOrgTestWidgetController1Create(DvDeviceC aDevice)
{
	return new DvProviderZappOrgTestWidgetController1C(aDevice);
}

void DvProviderZappOrgTestWidgetController1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderZappOrgTestWidgetController1C*>(aProvider);
}

void DvProviderZappOrgTestWidgetController1EnableActionCreateWidget(THandle aProvider, CallbackTestWidgetController1CreateWidget aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestWidgetController1C*>(aProvider)->EnableActionCreateWidget(aCallback, aPtr);
}

void DvProviderZappOrgTestWidgetController1EnableActionRemoveWidget(THandle aProvider, CallbackTestWidgetController1RemoveWidget aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestWidgetController1C*>(aProvider)->EnableActionRemoveWidget(aCallback, aPtr);
}

void DvProviderZappOrgTestWidgetController1EnableActionSetWidgetRegister(THandle aProvider, CallbackTestWidgetController1SetWidgetRegister aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestWidgetController1C*>(aProvider)->EnableActionSetWidgetRegister(aCallback, aPtr);
}

void DvProviderZappOrgTestWidgetController1EnableActionGetWidgetRegister(THandle aProvider, CallbackTestWidgetController1GetWidgetRegister aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestWidgetController1C*>(aProvider)->EnableActionGetWidgetRegister(aCallback, aPtr);
}

