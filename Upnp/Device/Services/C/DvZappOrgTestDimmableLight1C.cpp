#include <C/DvZappOrgTestDimmableLight1.h>
#include <Core/DvZappOrgTestDimmableLight1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderZappOrgTestDimmableLight1C : public DvProviderZappOrgTestDimmableLight1
{
public:
    DvProviderZappOrgTestDimmableLight1C(DvDevice& aDevice);
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

DvProviderZappOrgTestDimmableLight1C::DvProviderZappOrgTestDimmableLight1C(DvDevice& aDevice)
    : DvProviderZappOrgTestDimmableLight1(aDevice)
{
}

void DvProviderZappOrgTestDimmableLight1C::EnableActionGetLevel(CallbackTestDimmableLight1GetLevel aCallback, void* aPtr)
{
    iCallbackGetLevel = aCallback;
    iPtrGetLevel = aPtr;
    DvProviderZappOrgTestDimmableLight1::EnableActionGetLevel();
}

void DvProviderZappOrgTestDimmableLight1C::EnableActionSetLevel(CallbackTestDimmableLight1SetLevel aCallback, void* aPtr)
{
    iCallbackSetLevel = aCallback;
    iPtrSetLevel = aPtr;
    DvProviderZappOrgTestDimmableLight1::EnableActionSetLevel();
}

void DvProviderZappOrgTestDimmableLight1C::GetLevel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aLevel)
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

void DvProviderZappOrgTestDimmableLight1C::SetLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aLevel)
{
    ASSERT(iCallbackSetLevel != NULL);
    if (0 != iCallbackSetLevel(iPtrSetLevel, aVersion, aLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvProviderZappOrgTestDimmableLight1Create(DvDeviceC aDevice)
{
	return new DvProviderZappOrgTestDimmableLight1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderZappOrgTestDimmableLight1Destroy(THandle aService)
{
    delete reinterpret_cast<DvProviderZappOrgTestDimmableLight1C*>(aService);
}

void DvProviderZappOrgTestDimmableLight1EnableActionGetLevel(THandle aService, CallbackTestDimmableLight1GetLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestDimmableLight1C*>(aService)->EnableActionGetLevel(aCallback, aPtr);
}

void DvProviderZappOrgTestDimmableLight1EnableActionSetLevel(THandle aService, CallbackTestDimmableLight1SetLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestDimmableLight1C*>(aService)->EnableActionSetLevel(aCallback, aPtr);
}

int32_t DvProviderZappOrgTestDimmableLight1SetPropertyA_ARG_Level(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestDimmableLight1C*>(aService)->SetPropertyA_ARG_Level(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestDimmableLight1GetPropertyA_ARG_Level(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestDimmableLight1C*>(aService)->GetPropertyA_ARG_Level(val);
    *aValue = val;
}

