#include "DvZappOrgTestWidgetController1C.h"
#include "DvZappOrgTestWidgetController1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderZappOrgTestWidgetController1C : public DvProviderZappOrgTestWidgetController1
{
public:
    DvProviderZappOrgTestWidgetController1C(DvDevice& aDevice);
    void EnableActionCreateWidget(CallbackTestWidgetController1CreateWidget aCallback, void* aPtr);
    void EnableActionRemoveWidget(CallbackTestWidgetController1RemoveWidget aCallback, void* aPtr);
    void EnableActionSetWidgetRegister(CallbackTestWidgetController1SetWidgetRegister aCallback, void* aPtr);
    void EnableActionGetWidgetRegister(CallbackTestWidgetController1GetWidgetRegister aCallback, void* aPtr);
private:
    void CreateWidget(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn, TUint aWidgetClass);
    void RemoveWidget(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn);
    void SetWidgetRegister(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn, TUint aRegisterIndex, TUint aRegisterValue);
    void GetWidgetRegister(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn, TUint aRegisterIndex, IInvocationResponseUint& aRegisterValue);
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

DvProviderZappOrgTestWidgetController1C::DvProviderZappOrgTestWidgetController1C(DvDevice& aDevice)
    : DvProviderZappOrgTestWidgetController1(aDevice)
{
}

void DvProviderZappOrgTestWidgetController1C::EnableActionCreateWidget(CallbackTestWidgetController1CreateWidget aCallback, void* aPtr)
{
    iCallbackCreateWidget = aCallback;
    iPtrCreateWidget = aPtr;
    DvProviderZappOrgTestWidgetController1::EnableActionCreateWidget();
}

void DvProviderZappOrgTestWidgetController1C::EnableActionRemoveWidget(CallbackTestWidgetController1RemoveWidget aCallback, void* aPtr)
{
    iCallbackRemoveWidget = aCallback;
    iPtrRemoveWidget = aPtr;
    DvProviderZappOrgTestWidgetController1::EnableActionRemoveWidget();
}

void DvProviderZappOrgTestWidgetController1C::EnableActionSetWidgetRegister(CallbackTestWidgetController1SetWidgetRegister aCallback, void* aPtr)
{
    iCallbackSetWidgetRegister = aCallback;
    iPtrSetWidgetRegister = aPtr;
    DvProviderZappOrgTestWidgetController1::EnableActionSetWidgetRegister();
}

void DvProviderZappOrgTestWidgetController1C::EnableActionGetWidgetRegister(CallbackTestWidgetController1GetWidgetRegister aCallback, void* aPtr)
{
    iCallbackGetWidgetRegister = aCallback;
    iPtrGetWidgetRegister = aPtr;
    DvProviderZappOrgTestWidgetController1::EnableActionGetWidgetRegister();
}

void DvProviderZappOrgTestWidgetController1C::CreateWidget(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn, TUint aWidgetClass)
{
    ASSERT(iCallbackCreateWidget != NULL);
    if (0 != iCallbackCreateWidget(iPtrCreateWidget, aVersion, (const char*)aWidgetUdn.Ptr(), aWidgetClass)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderZappOrgTestWidgetController1C::RemoveWidget(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn)
{
    ASSERT(iCallbackRemoveWidget != NULL);
    if (0 != iCallbackRemoveWidget(iPtrRemoveWidget, aVersion, (const char*)aWidgetUdn.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderZappOrgTestWidgetController1C::SetWidgetRegister(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn, TUint aRegisterIndex, TUint aRegisterValue)
{
    ASSERT(iCallbackSetWidgetRegister != NULL);
    if (0 != iCallbackSetWidgetRegister(iPtrSetWidgetRegister, aVersion, (const char*)aWidgetUdn.Ptr(), aRegisterIndex, aRegisterValue)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderZappOrgTestWidgetController1C::GetWidgetRegister(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn, TUint aRegisterIndex, IInvocationResponseUint& aRegisterValue)
{
    uint32_t RegisterValue;
    ASSERT(iCallbackGetWidgetRegister != NULL);
    if (0 != iCallbackGetWidgetRegister(iPtrGetWidgetRegister, aVersion, (const char*)aWidgetUdn.Ptr(), aRegisterIndex, &RegisterValue)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aRegisterValue.Write(RegisterValue);
    aResponse.End();
}



THandle DvProviderZappOrgTestWidgetController1Create(DvDeviceC aDevice)
{
	return new DvProviderZappOrgTestWidgetController1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
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

