#include "DvZappOrgTestWidget1.h"
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

class DvProviderZappOrgTestWidget1C : public DvProvider
{
public:
    DvProviderZappOrgTestWidget1C(DvDeviceC aDevice);
    TBool SetPropertyReadWriteRegister0(TUint aValue);
    void GetPropertyReadWriteRegister0(TUint& aValue);
    TBool SetPropertyReadWriteRegister1(TUint aValue);
    void GetPropertyReadWriteRegister1(TUint& aValue);
    TBool SetPropertyReadWriteRegister2(TUint aValue);
    void GetPropertyReadWriteRegister2(TUint& aValue);
    TBool SetPropertyReadWriteRegister3(TUint aValue);
    void GetPropertyReadWriteRegister3(TUint& aValue);
    TBool SetPropertyReadOnlyRegister4(TUint aValue);
    void GetPropertyReadOnlyRegister4(TUint& aValue);
    TBool SetPropertyReadOnlyRegister5(TUint aValue);
    void GetPropertyReadOnlyRegister5(TUint& aValue);
    TBool SetPropertyReadOnlyRegister6(TUint aValue);
    void GetPropertyReadOnlyRegister6(TUint& aValue);
    TBool SetPropertyReadOnlyRegister7(TUint aValue);
    void GetPropertyReadOnlyRegister7(TUint& aValue);
    void EnableActionSetReadWriteRegister(CallbackTestWidget1SetReadWriteRegister aCallback, void* aPtr);
    void EnableActionGetWidgetClass(CallbackTestWidget1GetWidgetClass aCallback, void* aPtr);
private:
    void DoSetReadWriteRegister(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetWidgetClass(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackTestWidget1SetReadWriteRegister iCallbackSetReadWriteRegister;
    void* iPtrSetReadWriteRegister;
    CallbackTestWidget1GetWidgetClass iCallbackGetWidgetClass;
    void* iPtrGetWidgetClass;
    PropertyUint* iPropertyReadWriteRegister0;
    PropertyUint* iPropertyReadWriteRegister1;
    PropertyUint* iPropertyReadWriteRegister2;
    PropertyUint* iPropertyReadWriteRegister3;
    PropertyUint* iPropertyReadOnlyRegister4;
    PropertyUint* iPropertyReadOnlyRegister5;
    PropertyUint* iPropertyReadOnlyRegister6;
    PropertyUint* iPropertyReadOnlyRegister7;
};

DvProviderZappOrgTestWidget1C::DvProviderZappOrgTestWidget1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "zapp.org", "TestWidget", 1)
{
    
    iPropertyReadWriteRegister0 = new PropertyUint(new ParameterUint("ReadWriteRegister0"));
    iService->AddProperty(iPropertyReadWriteRegister0); // passes ownership
    iPropertyReadWriteRegister1 = new PropertyUint(new ParameterUint("ReadWriteRegister1"));
    iService->AddProperty(iPropertyReadWriteRegister1); // passes ownership
    iPropertyReadWriteRegister2 = new PropertyUint(new ParameterUint("ReadWriteRegister2"));
    iService->AddProperty(iPropertyReadWriteRegister2); // passes ownership
    iPropertyReadWriteRegister3 = new PropertyUint(new ParameterUint("ReadWriteRegister3"));
    iService->AddProperty(iPropertyReadWriteRegister3); // passes ownership
    iPropertyReadOnlyRegister4 = new PropertyUint(new ParameterUint("ReadOnlyRegister4"));
    iService->AddProperty(iPropertyReadOnlyRegister4); // passes ownership
    iPropertyReadOnlyRegister5 = new PropertyUint(new ParameterUint("ReadOnlyRegister5"));
    iService->AddProperty(iPropertyReadOnlyRegister5); // passes ownership
    iPropertyReadOnlyRegister6 = new PropertyUint(new ParameterUint("ReadOnlyRegister6"));
    iService->AddProperty(iPropertyReadOnlyRegister6); // passes ownership
    iPropertyReadOnlyRegister7 = new PropertyUint(new ParameterUint("ReadOnlyRegister7"));
    iService->AddProperty(iPropertyReadOnlyRegister7); // passes ownership
}

TBool DvProviderZappOrgTestWidget1C::SetPropertyReadWriteRegister0(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadWriteRegister0, aValue);
}

void DvProviderZappOrgTestWidget1C::GetPropertyReadWriteRegister0(TUint& aValue)
{
    aValue = iPropertyReadWriteRegister0->Value();
}

TBool DvProviderZappOrgTestWidget1C::SetPropertyReadWriteRegister1(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadWriteRegister1, aValue);
}

void DvProviderZappOrgTestWidget1C::GetPropertyReadWriteRegister1(TUint& aValue)
{
    aValue = iPropertyReadWriteRegister1->Value();
}

TBool DvProviderZappOrgTestWidget1C::SetPropertyReadWriteRegister2(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadWriteRegister2, aValue);
}

void DvProviderZappOrgTestWidget1C::GetPropertyReadWriteRegister2(TUint& aValue)
{
    aValue = iPropertyReadWriteRegister2->Value();
}

TBool DvProviderZappOrgTestWidget1C::SetPropertyReadWriteRegister3(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadWriteRegister3, aValue);
}

void DvProviderZappOrgTestWidget1C::GetPropertyReadWriteRegister3(TUint& aValue)
{
    aValue = iPropertyReadWriteRegister3->Value();
}

TBool DvProviderZappOrgTestWidget1C::SetPropertyReadOnlyRegister4(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadOnlyRegister4, aValue);
}

void DvProviderZappOrgTestWidget1C::GetPropertyReadOnlyRegister4(TUint& aValue)
{
    aValue = iPropertyReadOnlyRegister4->Value();
}

TBool DvProviderZappOrgTestWidget1C::SetPropertyReadOnlyRegister5(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadOnlyRegister5, aValue);
}

void DvProviderZappOrgTestWidget1C::GetPropertyReadOnlyRegister5(TUint& aValue)
{
    aValue = iPropertyReadOnlyRegister5->Value();
}

TBool DvProviderZappOrgTestWidget1C::SetPropertyReadOnlyRegister6(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadOnlyRegister6, aValue);
}

void DvProviderZappOrgTestWidget1C::GetPropertyReadOnlyRegister6(TUint& aValue)
{
    aValue = iPropertyReadOnlyRegister6->Value();
}

TBool DvProviderZappOrgTestWidget1C::SetPropertyReadOnlyRegister7(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadOnlyRegister7, aValue);
}

void DvProviderZappOrgTestWidget1C::GetPropertyReadOnlyRegister7(TUint& aValue)
{
    aValue = iPropertyReadOnlyRegister7->Value();
}

void DvProviderZappOrgTestWidget1C::EnableActionSetReadWriteRegister(CallbackTestWidget1SetReadWriteRegister aCallback, void* aPtr)
{
    iCallbackSetReadWriteRegister = aCallback;
    iPtrSetReadWriteRegister = aPtr;
    Zapp::Action* action = new Zapp::Action("SetReadWriteRegister");
    action->AddInputParameter(new ParameterUint("RegisterIndex"));
    action->AddInputParameter(new ParameterUint("RegisterValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidget1C::DoSetReadWriteRegister);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidget1C::EnableActionGetWidgetClass(CallbackTestWidget1GetWidgetClass aCallback, void* aPtr)
{
    iCallbackGetWidgetClass = aCallback;
    iPtrGetWidgetClass = aPtr;
    Zapp::Action* action = new Zapp::Action("GetWidgetClass");
    action->AddOutputParameter(new ParameterUint("WidgetClass"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidget1C::DoGetWidgetClass);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidget1C::DoSetReadWriteRegister(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint RegisterIndex = aInvocation.InvocationReadUint("RegisterIndex");
    TUint RegisterValue = aInvocation.InvocationReadUint("RegisterValue");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetReadWriteRegister != NULL);
    if (0 != iCallbackSetReadWriteRegister(iPtrSetReadWriteRegister, aVersion, RegisterIndex, RegisterValue)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderZappOrgTestWidget1C::DoGetWidgetClass(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t WidgetClass;
    ASSERT(iCallbackGetWidgetClass != NULL);
    if (0 != iCallbackGetWidgetClass(iPtrGetWidgetClass, aVersion, &WidgetClass)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respWidgetClass(aInvocation, "WidgetClass");
    resp.Start();
    respWidgetClass.Write(WidgetClass);
    resp.End();
}



THandle DvProviderZappOrgTestWidget1Create(DvDeviceC aDevice)
{
	return new DvProviderZappOrgTestWidget1C(aDevice);
}

void DvProviderZappOrgTestWidget1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider);
}

void DvProviderZappOrgTestWidget1EnableActionSetReadWriteRegister(THandle aProvider, CallbackTestWidget1SetReadWriteRegister aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->EnableActionSetReadWriteRegister(aCallback, aPtr);
}

void DvProviderZappOrgTestWidget1EnableActionGetWidgetClass(THandle aProvider, CallbackTestWidget1GetWidgetClass aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->EnableActionGetWidgetClass(aCallback, aPtr);
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister0(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->SetPropertyReadWriteRegister0(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister0(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->GetPropertyReadWriteRegister0(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister1(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->SetPropertyReadWriteRegister1(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister1(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->GetPropertyReadWriteRegister1(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister2(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->SetPropertyReadWriteRegister2(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister2(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->GetPropertyReadWriteRegister2(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister3(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->SetPropertyReadWriteRegister3(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister3(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->GetPropertyReadWriteRegister3(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister4(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->SetPropertyReadOnlyRegister4(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister4(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->GetPropertyReadOnlyRegister4(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister5(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->SetPropertyReadOnlyRegister5(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister5(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->GetPropertyReadOnlyRegister5(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister6(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->SetPropertyReadOnlyRegister6(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister6(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->GetPropertyReadOnlyRegister6(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister7(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->SetPropertyReadOnlyRegister7(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister7(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aProvider)->GetPropertyReadOnlyRegister7(val);
    *aValue = val;
}

