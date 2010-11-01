#include <C/DvZappOrgTestWidget1.h>
#include <Core/DvZappOrgTestWidget1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceZappOrgTestWidget1C : public DvServiceZappOrgTestWidget1
{
public:
    DvServiceZappOrgTestWidget1C(DvDevice& aDevice);
    void EnableActionSetReadWriteRegister(CallbackTestWidget1SetReadWriteRegister aCallback, void* aPtr);
private:
    void SetReadWriteRegister(IInvocationResponse& aResponse, TUint aVersion, TUint aRegisterIndex, TUint aRegisterValue);
private:
    CallbackTestWidget1SetReadWriteRegister iCallbackSetReadWriteRegister;
    void* iPtrSetReadWriteRegister;
};

DvServiceZappOrgTestWidget1C::DvServiceZappOrgTestWidget1C(DvDevice& aDevice)
    : DvServiceZappOrgTestWidget1(aDevice)
{
}

void DvServiceZappOrgTestWidget1C::EnableActionSetReadWriteRegister(CallbackTestWidget1SetReadWriteRegister aCallback, void* aPtr)
{
    iCallbackSetReadWriteRegister = aCallback;
    iPtrSetReadWriteRegister = aPtr;
    DvServiceZappOrgTestWidget1::EnableActionSetReadWriteRegister();
}

void DvServiceZappOrgTestWidget1C::SetReadWriteRegister(IInvocationResponse& aResponse, TUint aVersion, TUint aRegisterIndex, TUint aRegisterValue)
{
    ASSERT(iCallbackSetReadWriteRegister != NULL);
    if (0 != iCallbackSetReadWriteRegister(iPtrSetReadWriteRegister, aVersion, aRegisterIndex, aRegisterValue)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvServiceZappOrgTestWidget1Create(DvDeviceC aDevice)
{
	return new DvServiceZappOrgTestWidget1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceZappOrgTestWidget1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService);
}

void DvServiceZappOrgTestWidget1EnableActionSetReadWriteRegister(THandle aService, CallbackTestWidget1SetReadWriteRegister aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->EnableActionSetReadWriteRegister(aCallback, aPtr);
}

int32_t DvServiceZappOrgTestWidget1SetPropertyReadWriteRegister0(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->SetPropertyReadWriteRegister0(aValue)? 1 : 0);
    return 0;
}

void DvServiceZappOrgTestWidget1GetPropertyReadWriteRegister0(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->GetPropertyReadWriteRegister0(val);
    *aValue = val;
}

int32_t DvServiceZappOrgTestWidget1SetPropertyReadWriteRegister1(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->SetPropertyReadWriteRegister1(aValue)? 1 : 0);
    return 0;
}

void DvServiceZappOrgTestWidget1GetPropertyReadWriteRegister1(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->GetPropertyReadWriteRegister1(val);
    *aValue = val;
}

int32_t DvServiceZappOrgTestWidget1SetPropertyReadWriteRegister2(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->SetPropertyReadWriteRegister2(aValue)? 1 : 0);
    return 0;
}

void DvServiceZappOrgTestWidget1GetPropertyReadWriteRegister2(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->GetPropertyReadWriteRegister2(val);
    *aValue = val;
}

int32_t DvServiceZappOrgTestWidget1SetPropertyReadWriteRegister3(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->SetPropertyReadWriteRegister3(aValue)? 1 : 0);
    return 0;
}

void DvServiceZappOrgTestWidget1GetPropertyReadWriteRegister3(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->GetPropertyReadWriteRegister3(val);
    *aValue = val;
}

int32_t DvServiceZappOrgTestWidget1SetPropertyReadOnlyRegister4(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->SetPropertyReadOnlyRegister4(aValue)? 1 : 0);
    return 0;
}

void DvServiceZappOrgTestWidget1GetPropertyReadOnlyRegister4(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->GetPropertyReadOnlyRegister4(val);
    *aValue = val;
}

int32_t DvServiceZappOrgTestWidget1SetPropertyReadOnlyRegister5(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->SetPropertyReadOnlyRegister5(aValue)? 1 : 0);
    return 0;
}

void DvServiceZappOrgTestWidget1GetPropertyReadOnlyRegister5(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->GetPropertyReadOnlyRegister5(val);
    *aValue = val;
}

int32_t DvServiceZappOrgTestWidget1SetPropertyReadOnlyRegister6(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->SetPropertyReadOnlyRegister6(aValue)? 1 : 0);
    return 0;
}

void DvServiceZappOrgTestWidget1GetPropertyReadOnlyRegister6(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->GetPropertyReadOnlyRegister6(val);
    *aValue = val;
}

int32_t DvServiceZappOrgTestWidget1SetPropertyReadOnlyRegister7(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->SetPropertyReadOnlyRegister7(aValue)? 1 : 0);
    return 0;
}

void DvServiceZappOrgTestWidget1GetPropertyReadOnlyRegister7(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceZappOrgTestWidget1C*>(aService)->GetPropertyReadOnlyRegister7(val);
    *aValue = val;
}

