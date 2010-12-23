#include "DvZappOrgTestWidget1C.h"
#include "DvZappOrgTestWidget1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderZappOrgTestWidget1C : public DvProviderZappOrgTestWidget1
{
public:
    DvProviderZappOrgTestWidget1C(DvDevice& aDevice);
    void EnableActionSetReadWriteRegister(CallbackTestWidget1SetReadWriteRegister aCallback, void* aPtr);
    void EnableActionGetWidgetClass(CallbackTestWidget1GetWidgetClass aCallback, void* aPtr);
private:
    void SetReadWriteRegister(IInvocationResponse& aResponse, TUint aVersion, TUint aRegisterIndex, TUint aRegisterValue);
    void GetWidgetClass(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aWidgetClass);
private:
    CallbackTestWidget1SetReadWriteRegister iCallbackSetReadWriteRegister;
    void* iPtrSetReadWriteRegister;
    CallbackTestWidget1GetWidgetClass iCallbackGetWidgetClass;
    void* iPtrGetWidgetClass;
};

DvProviderZappOrgTestWidget1C::DvProviderZappOrgTestWidget1C(DvDevice& aDevice)
    : DvProviderZappOrgTestWidget1(aDevice)
{
}

void DvProviderZappOrgTestWidget1C::EnableActionSetReadWriteRegister(CallbackTestWidget1SetReadWriteRegister aCallback, void* aPtr)
{
    iCallbackSetReadWriteRegister = aCallback;
    iPtrSetReadWriteRegister = aPtr;
    DvProviderZappOrgTestWidget1::EnableActionSetReadWriteRegister();
}

void DvProviderZappOrgTestWidget1C::EnableActionGetWidgetClass(CallbackTestWidget1GetWidgetClass aCallback, void* aPtr)
{
    iCallbackGetWidgetClass = aCallback;
    iPtrGetWidgetClass = aPtr;
    DvProviderZappOrgTestWidget1::EnableActionGetWidgetClass();
}

void DvProviderZappOrgTestWidget1C::SetReadWriteRegister(IInvocationResponse& aResponse, TUint aVersion, TUint aRegisterIndex, TUint aRegisterValue)
{
    ASSERT(iCallbackSetReadWriteRegister != NULL);
    if (0 != iCallbackSetReadWriteRegister(iPtrSetReadWriteRegister, aVersion, aRegisterIndex, aRegisterValue)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderZappOrgTestWidget1C::GetWidgetClass(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aWidgetClass)
{
    uint32_t WidgetClass;
    ASSERT(iCallbackGetWidgetClass != NULL);
    if (0 != iCallbackGetWidgetClass(iPtrGetWidgetClass, aVersion, &WidgetClass)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aWidgetClass.Write(WidgetClass);
    aResponse.End();
}



THandle DvProviderZappOrgTestWidget1Create(DvDeviceC aDevice)
{
	return new DvProviderZappOrgTestWidget1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
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

