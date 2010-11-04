#include <C/DvLinnCoUkDebug2.h>
#include <Core/DvLinnCoUkDebug2.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkDebug2C : public DvProviderLinnCoUkDebug2
{
public:
    DvProviderLinnCoUkDebug2C(DvDevice& aDevice);
    void EnableActionSetDebugLevel(CallbackDebug2SetDebugLevel aCallback, void* aPtr);
    void EnableActionDebugLevel(CallbackDebug2DebugLevel aCallback, void* aPtr);
    void EnableActionMemWrite(CallbackDebug2MemWrite aCallback, void* aPtr);
private:
    void SetDebugLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aaDebugLevel);
    void DebugLevel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDebugLevel);
    void MemWrite(IInvocationResponse& aResponse, TUint aVersion, TUint aaMemAddress, const Brx& aaMemData);
private:
    CallbackDebug2SetDebugLevel iCallbackSetDebugLevel;
    void* iPtrSetDebugLevel;
    CallbackDebug2DebugLevel iCallbackDebugLevel;
    void* iPtrDebugLevel;
    CallbackDebug2MemWrite iCallbackMemWrite;
    void* iPtrMemWrite;
};

DvProviderLinnCoUkDebug2C::DvProviderLinnCoUkDebug2C(DvDevice& aDevice)
    : DvProviderLinnCoUkDebug2(aDevice)
{
}

void DvProviderLinnCoUkDebug2C::EnableActionSetDebugLevel(CallbackDebug2SetDebugLevel aCallback, void* aPtr)
{
    iCallbackSetDebugLevel = aCallback;
    iPtrSetDebugLevel = aPtr;
    DvProviderLinnCoUkDebug2::EnableActionSetDebugLevel();
}

void DvProviderLinnCoUkDebug2C::EnableActionDebugLevel(CallbackDebug2DebugLevel aCallback, void* aPtr)
{
    iCallbackDebugLevel = aCallback;
    iPtrDebugLevel = aPtr;
    DvProviderLinnCoUkDebug2::EnableActionDebugLevel();
}

void DvProviderLinnCoUkDebug2C::EnableActionMemWrite(CallbackDebug2MemWrite aCallback, void* aPtr)
{
    iCallbackMemWrite = aCallback;
    iPtrMemWrite = aPtr;
    DvProviderLinnCoUkDebug2::EnableActionMemWrite();
}

void DvProviderLinnCoUkDebug2C::SetDebugLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aaDebugLevel)
{
    ASSERT(iCallbackSetDebugLevel != NULL);
    if (0 != iCallbackSetDebugLevel(iPtrSetDebugLevel, aVersion, aaDebugLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkDebug2C::DebugLevel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDebugLevel)
{
    uint32_t aDebugLevel;
    ASSERT(iCallbackDebugLevel != NULL);
    if (0 != iCallbackDebugLevel(iPtrDebugLevel, aVersion, &aDebugLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaDebugLevel.Write(aDebugLevel);
    aResponse.End();
}

void DvProviderLinnCoUkDebug2C::MemWrite(IInvocationResponse& aResponse, TUint aVersion, TUint aaMemAddress, const Brx& aaMemData)
{
    ASSERT(iCallbackMemWrite != NULL);
    if (0 != iCallbackMemWrite(iPtrMemWrite, aVersion, aaMemAddress, (const char*)aaMemData.Ptr(), aaMemData.Bytes())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvProviderLinnCoUkDebug2Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkDebug2C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkDebug2Destroy(THandle aService)
{
    delete reinterpret_cast<DvProviderLinnCoUkDebug2C*>(aService);
}

void DvProviderLinnCoUkDebug2EnableActionSetDebugLevel(THandle aService, CallbackDebug2SetDebugLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDebug2C*>(aService)->EnableActionSetDebugLevel(aCallback, aPtr);
}

void DvProviderLinnCoUkDebug2EnableActionDebugLevel(THandle aService, CallbackDebug2DebugLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDebug2C*>(aService)->EnableActionDebugLevel(aCallback, aPtr);
}

void DvProviderLinnCoUkDebug2EnableActionMemWrite(THandle aService, CallbackDebug2MemWrite aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDebug2C*>(aService)->EnableActionMemWrite(aCallback, aPtr);
}

