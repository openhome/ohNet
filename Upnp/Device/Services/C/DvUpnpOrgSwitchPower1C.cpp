#include <C/DvUpnpOrgSwitchPower1.h>
#include <Core/DvUpnpOrgSwitchPower1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceUpnpOrgSwitchPower1C : public DvServiceUpnpOrgSwitchPower1
{
public:
    DvServiceUpnpOrgSwitchPower1C(DvDevice& aDevice);
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

DvServiceUpnpOrgSwitchPower1C::DvServiceUpnpOrgSwitchPower1C(DvDevice& aDevice)
    : DvServiceUpnpOrgSwitchPower1(aDevice)
{
}

void DvServiceUpnpOrgSwitchPower1C::EnableActionSetTarget(CallbackSwitchPower1SetTarget aCallback, void* aPtr)
{
    iCallbackSetTarget = aCallback;
    iPtrSetTarget = aPtr;
    DvServiceUpnpOrgSwitchPower1::EnableActionSetTarget();
}

void DvServiceUpnpOrgSwitchPower1C::EnableActionGetTarget(CallbackSwitchPower1GetTarget aCallback, void* aPtr)
{
    iCallbackGetTarget = aCallback;
    iPtrGetTarget = aPtr;
    DvServiceUpnpOrgSwitchPower1::EnableActionGetTarget();
}

void DvServiceUpnpOrgSwitchPower1C::EnableActionGetStatus(CallbackSwitchPower1GetStatus aCallback, void* aPtr)
{
    iCallbackGetStatus = aCallback;
    iPtrGetStatus = aPtr;
    DvServiceUpnpOrgSwitchPower1::EnableActionGetStatus();
}

void DvServiceUpnpOrgSwitchPower1C::SetTarget(IInvocationResponse& aResponse, TUint aVersion, TBool anewTargetValue)
{
    ASSERT(iCallbackSetTarget != NULL);
    if (0 != iCallbackSetTarget(iPtrSetTarget, aVersion, anewTargetValue)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgSwitchPower1C::GetTarget(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aRetTargetValue)
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

void DvServiceUpnpOrgSwitchPower1C::GetStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aResultStatus)
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



THandle DvServiceUpnpOrgSwitchPower1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceUpnpOrgSwitchPower1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceUpnpOrgSwitchPower1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceUpnpOrgSwitchPower1C*>(aService);
}

void DvServiceUpnpOrgSwitchPower1EnableActionSetTarget(THandle aService, CallbackSwitchPower1SetTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgSwitchPower1C*>(aService)->EnableActionSetTarget(aCallback, aPtr);
}

void DvServiceUpnpOrgSwitchPower1EnableActionGetTarget(THandle aService, CallbackSwitchPower1GetTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgSwitchPower1C*>(aService)->EnableActionGetTarget(aCallback, aPtr);
}

void DvServiceUpnpOrgSwitchPower1EnableActionGetStatus(THandle aService, CallbackSwitchPower1GetStatus aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgSwitchPower1C*>(aService)->EnableActionGetStatus(aCallback, aPtr);
}

int32_t DvServiceUpnpOrgSwitchPower1SetPropertyStatus(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceUpnpOrgSwitchPower1C*>(aService)->SetPropertyStatus((aValue!=0));
    return 0;
}

void DvServiceUpnpOrgSwitchPower1GetPropertyStatus(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceUpnpOrgSwitchPower1C*>(aService)->GetPropertyStatus(val);
    *aValue = (val? 1 : 0);
}

