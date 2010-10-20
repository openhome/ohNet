#include <C/DvZappOrgTestWidgetController1.h>
#include <Core/DvZappOrgTestWidgetController1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceZappOrgTestWidgetController1C : public DvServiceZappOrgTestWidgetController1
{
public:
    DvServiceZappOrgTestWidgetController1C(DvDevice& aDevice);
    void EnableActionCreateWidget(CallbackTestWidgetController1CreateWidget aCallback, void* aPtr);
    void EnableActionRemoveWidget(CallbackTestWidgetController1RemoveWidget aCallback, void* aPtr);
    void EnableActionSetWidgetRegister(CallbackTestWidgetController1SetWidgetRegister aCallback, void* aPtr);
private:
    void CreateWidget(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn);
    void RemoveWidget(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn);
    void SetWidgetRegister(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn, TUint aRegisterIndex, TUint aRegisterValue);
private:
    CallbackTestWidgetController1CreateWidget iCallbackCreateWidget;
    void* iPtrCreateWidget;
    CallbackTestWidgetController1RemoveWidget iCallbackRemoveWidget;
    void* iPtrRemoveWidget;
    CallbackTestWidgetController1SetWidgetRegister iCallbackSetWidgetRegister;
    void* iPtrSetWidgetRegister;
};

DvServiceZappOrgTestWidgetController1C::DvServiceZappOrgTestWidgetController1C(DvDevice& aDevice)
    : DvServiceZappOrgTestWidgetController1(aDevice)
{
}

void DvServiceZappOrgTestWidgetController1C::EnableActionCreateWidget(CallbackTestWidgetController1CreateWidget aCallback, void* aPtr)
{
    iCallbackCreateWidget = aCallback;
    iPtrCreateWidget = aPtr;
    DvServiceZappOrgTestWidgetController1::EnableActionCreateWidget();
}

void DvServiceZappOrgTestWidgetController1C::EnableActionRemoveWidget(CallbackTestWidgetController1RemoveWidget aCallback, void* aPtr)
{
    iCallbackRemoveWidget = aCallback;
    iPtrRemoveWidget = aPtr;
    DvServiceZappOrgTestWidgetController1::EnableActionRemoveWidget();
}

void DvServiceZappOrgTestWidgetController1C::EnableActionSetWidgetRegister(CallbackTestWidgetController1SetWidgetRegister aCallback, void* aPtr)
{
    iCallbackSetWidgetRegister = aCallback;
    iPtrSetWidgetRegister = aPtr;
    DvServiceZappOrgTestWidgetController1::EnableActionSetWidgetRegister();
}

void DvServiceZappOrgTestWidgetController1C::CreateWidget(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn)
{
    ASSERT(iCallbackCreateWidget != NULL);
    if (0 != iCallbackCreateWidget(iPtrCreateWidget, aVersion, (const char*)aWidgetUdn.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceZappOrgTestWidgetController1C::RemoveWidget(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn)
{
    ASSERT(iCallbackRemoveWidget != NULL);
    if (0 != iCallbackRemoveWidget(iPtrRemoveWidget, aVersion, (const char*)aWidgetUdn.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceZappOrgTestWidgetController1C::SetWidgetRegister(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn, TUint aRegisterIndex, TUint aRegisterValue)
{
    ASSERT(iCallbackSetWidgetRegister != NULL);
    if (0 != iCallbackSetWidgetRegister(iPtrSetWidgetRegister, aVersion, (const char*)aWidgetUdn.Ptr(), aRegisterIndex, aRegisterValue)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvServiceZappOrgTestWidgetController1Create(DvDeviceC aDevice)
{
	return new DvServiceZappOrgTestWidgetController1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceZappOrgTestWidgetController1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceZappOrgTestWidgetController1C*>(aService);
}

void DvServiceZappOrgTestWidgetController1EnableActionCreateWidget(THandle aService, CallbackTestWidgetController1CreateWidget aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestWidgetController1C*>(aService)->EnableActionCreateWidget(aCallback, aPtr);
}

void DvServiceZappOrgTestWidgetController1EnableActionRemoveWidget(THandle aService, CallbackTestWidgetController1RemoveWidget aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestWidgetController1C*>(aService)->EnableActionRemoveWidget(aCallback, aPtr);
}

void DvServiceZappOrgTestWidgetController1EnableActionSetWidgetRegister(THandle aService, CallbackTestWidgetController1SetWidgetRegister aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestWidgetController1C*>(aService)->EnableActionSetWidgetRegister(aCallback, aPtr);
}

