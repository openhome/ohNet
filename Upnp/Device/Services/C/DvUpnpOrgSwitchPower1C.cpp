#include <C/DvUpnpOrgSwitchPower1.h>
#include <Core/DvUpnpOrgSwitchPower1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderUpnpOrgSwitchPower1C : public DvProviderUpnpOrgSwitchPower1
{
public:
    DvProviderUpnpOrgSwitchPower1C(DvDevice& aDevice);
    void EnableActionSetTarget(CallbackSwitchPower1SetTarget aCallback, void* aPtr);
    void EnableActionGetTarget(CallbackSwitchPower1GetTarget aCallback, void* aPtr);
    void EnableActionGetStatus(CallbackSwitchPower1GetStatus aCallback, void* aPtr);
private:
    void SetTarget(IInvocationResponse& aResponse, TUint aVersion, TBool anewTargetValue);
    void GetTarget(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aRetTargetValue);
    void GetStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aResultStatus);
private:
    CallbackSwitchPower1SetTarget iCallbackSetTarget;
    void* iPtrSetTarget;
    CallbackSwitchPower1GetTarget iCallbackGetTarget;
    void* iPtrGetTarget;
    CallbackSwitchPower1GetStatus iCallbackGetStatus;
    void* iPtrGetStatus;
};

DvProviderUpnpOrgSwitchPower1C::DvProviderUpnpOrgSwitchPower1C(DvDevice& aDevice)
    : DvProviderUpnpOrgSwitchPower1(aDevice)
{
}

void DvProviderUpnpOrgSwitchPower1C::EnableActionSetTarget(CallbackSwitchPower1SetTarget aCallback, void* aPtr)
{
    iCallbackSetTarget = aCallback;
    iPtrSetTarget = aPtr;
    DvProviderUpnpOrgSwitchPower1::EnableActionSetTarget();
}

void DvProviderUpnpOrgSwitchPower1C::EnableActionGetTarget(CallbackSwitchPower1GetTarget aCallback, void* aPtr)
{
    iCallbackGetTarget = aCallback;
    iPtrGetTarget = aPtr;
    DvProviderUpnpOrgSwitchPower1::EnableActionGetTarget();
}

void DvProviderUpnpOrgSwitchPower1C::EnableActionGetStatus(CallbackSwitchPower1GetStatus aCallback, void* aPtr)
{
    iCallbackGetStatus = aCallback;
    iPtrGetStatus = aPtr;
    DvProviderUpnpOrgSwitchPower1::EnableActionGetStatus();
}

void DvProviderUpnpOrgSwitchPower1C::SetTarget(IInvocationResponse& aResponse, TUint aVersion, TBool anewTargetValue)
{
    ASSERT(iCallbackSetTarget != NULL);
    if (0 != iCallbackSetTarget(iPtrSetTarget, aVersion, anewTargetValue)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgSwitchPower1C::GetTarget(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aRetTargetValue)
{
    uint32_t RetTargetValue;
    ASSERT(iCallbackGetTarget != NULL);
    if (0 != iCallbackGetTarget(iPtrGetTarget, aVersion, &RetTargetValue)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aRetTargetValue.Write((RetTargetValue!=0));
    aResponse.End();
}

void DvProviderUpnpOrgSwitchPower1C::GetStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aResultStatus)
{
    uint32_t ResultStatus;
    ASSERT(iCallbackGetStatus != NULL);
    if (0 != iCallbackGetStatus(iPtrGetStatus, aVersion, &ResultStatus)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResultStatus.Write((ResultStatus!=0));
    aResponse.End();
}



THandle DvProviderUpnpOrgSwitchPower1Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgSwitchPower1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderUpnpOrgSwitchPower1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider);
}

void DvProviderUpnpOrgSwitchPower1EnableActionSetTarget(THandle aProvider, CallbackSwitchPower1SetTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->EnableActionSetTarget(aCallback, aPtr);
}

void DvProviderUpnpOrgSwitchPower1EnableActionGetTarget(THandle aProvider, CallbackSwitchPower1GetTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->EnableActionGetTarget(aCallback, aPtr);
}

void DvProviderUpnpOrgSwitchPower1EnableActionGetStatus(THandle aProvider, CallbackSwitchPower1GetStatus aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->EnableActionGetStatus(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgSwitchPower1SetPropertyStatus(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->SetPropertyStatus((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgSwitchPower1GetPropertyStatus(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderUpnpOrgSwitchPower1C*>(aProvider)->GetPropertyStatus(val);
    *aValue = (val? 1 : 0);
}

