#include <C/DvZappOrgTestDimmableLight1.h>
#include <Core/DvZappOrgTestDimmableLight1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceZappOrgTestDimmableLight1C : public DvServiceZappOrgTestDimmableLight1
{
public:
    DvServiceZappOrgTestDimmableLight1C(DvDevice& aDevice);
    void EnableActionGetLevel(CallbackTestDimmableLight1GetLevel aCallback, void* aPtr);
    void EnableActionSetLevel(CallbackTestDimmableLight1SetLevel aCallback, void* aPtr);
private:
    void GetLevel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aLevel);
    void SetLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aLevel);
private:
    CallbackTestDimmableLight1GetLevel iCallbackGetLevel;
    void* iPtrGetLevel;
    CallbackTestDimmableLight1SetLevel iCallbackSetLevel;
    void* iPtrSetLevel;
};

DvServiceZappOrgTestDimmableLight1C::DvServiceZappOrgTestDimmableLight1C(DvDevice& aDevice)
    : DvServiceZappOrgTestDimmableLight1(aDevice)
{
}

void DvServiceZappOrgTestDimmableLight1C::EnableActionGetLevel(CallbackTestDimmableLight1GetLevel aCallback, void* aPtr)
{
    iCallbackGetLevel = aCallback;
    iPtrGetLevel = aPtr;
    DvServiceZappOrgTestDimmableLight1::EnableActionGetLevel();
}

void DvServiceZappOrgTestDimmableLight1C::EnableActionSetLevel(CallbackTestDimmableLight1SetLevel aCallback, void* aPtr)
{
    iCallbackSetLevel = aCallback;
    iPtrSetLevel = aPtr;
    DvServiceZappOrgTestDimmableLight1::EnableActionSetLevel();
}

void DvServiceZappOrgTestDimmableLight1C::GetLevel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aLevel)
{
    uint32_t Level;
    ASSERT(iCallbackGetLevel != NULL);
    if (0 != iCallbackGetLevel(iPtrGetLevel, aVersion, &Level)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aLevel.Write(Level);
    aResponse.End();
}

void DvServiceZappOrgTestDimmableLight1C::SetLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aLevel)
{
    ASSERT(iCallbackSetLevel != NULL);
    if (0 != iCallbackSetLevel(iPtrSetLevel, aVersion, aLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvServiceZappOrgTestDimmableLight1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceZappOrgTestDimmableLight1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceZappOrgTestDimmableLight1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceZappOrgTestDimmableLight1C*>(aService);
}

void DvServiceZappOrgTestDimmableLight1EnableActionGetLevel(THandle aService, CallbackTestDimmableLight1GetLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestDimmableLight1C*>(aService)->EnableActionGetLevel(aCallback, aPtr);
}

void DvServiceZappOrgTestDimmableLight1EnableActionSetLevel(THandle aService, CallbackTestDimmableLight1SetLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestDimmableLight1C*>(aService)->EnableActionSetLevel(aCallback, aPtr);
}

int32_t DvServiceZappOrgTestDimmableLight1SetPropertyA_ARG_Level(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceZappOrgTestDimmableLight1C*>(aService)->SetPropertyA_ARG_Level(aValue);
    return 0;
}

void DvServiceZappOrgTestDimmableLight1GetPropertyA_ARG_Level(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceZappOrgTestDimmableLight1C*>(aService)->GetPropertyA_ARG_Level(val);
    *aValue = val;
}

