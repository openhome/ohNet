#include <C/DvZappOrgTestWidget1.h>
#include <Core/DvZappOrgTestWidget1.h>
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
private:
    void SetReadWriteRegister(IInvocationResponse& aResponse, TUint aVersion, TUint aRegisterIndex, TUint aRegisterValue);
private:
    CallbackTestWidget1SetReadWriteRegister iCallbackSetReadWriteRegister;
    void* iPtrSetReadWriteRegister;
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



THandle DvProviderZappOrgTestWidget1Create(DvDeviceC aDevice)
{
	return new DvProviderZappOrgTestWidget1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderZappOrgTestWidget1Destroy(THandle aService)
{
    delete reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService);
}

void DvProviderZappOrgTestWidget1EnableActionSetReadWriteRegister(THandle aService, CallbackTestWidget1SetReadWriteRegister aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->EnableActionSetReadWriteRegister(aCallback, aPtr);
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister0(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->SetPropertyReadWriteRegister0(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister0(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->GetPropertyReadWriteRegister0(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister1(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->SetPropertyReadWriteRegister1(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister1(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->GetPropertyReadWriteRegister1(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister2(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->SetPropertyReadWriteRegister2(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister2(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->GetPropertyReadWriteRegister2(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister3(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->SetPropertyReadWriteRegister3(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister3(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->GetPropertyReadWriteRegister3(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister4(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->SetPropertyReadOnlyRegister4(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister4(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->GetPropertyReadOnlyRegister4(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister5(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->SetPropertyReadOnlyRegister5(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister5(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->GetPropertyReadOnlyRegister5(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister6(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->SetPropertyReadOnlyRegister6(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister6(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->GetPropertyReadOnlyRegister6(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister7(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->SetPropertyReadOnlyRegister7(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister7(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestWidget1C*>(aService)->GetPropertyReadOnlyRegister7(val);
    *aValue = val;
}

