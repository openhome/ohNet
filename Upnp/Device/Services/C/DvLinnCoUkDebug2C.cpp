#include <C/DvLinnCoUkDebug2.h>
#include <Core/DvLinnCoUkDebug2.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkDebug2C : public DvServiceLinnCoUkDebug2
{
public:
    DvServiceLinnCoUkDebug2C(DvDevice& aDevice);
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

DvServiceLinnCoUkDebug2C::DvServiceLinnCoUkDebug2C(DvDevice& aDevice)
    : DvServiceLinnCoUkDebug2(aDevice)
{
}

void DvServiceLinnCoUkDebug2C::EnableActionSetDebugLevel(CallbackDebug2SetDebugLevel aCallback, void* aPtr)
{
    iCallbackSetDebugLevel = aCallback;
    iPtrSetDebugLevel = aPtr;
    DvServiceLinnCoUkDebug2::EnableActionSetDebugLevel();
}

void DvServiceLinnCoUkDebug2C::EnableActionDebugLevel(CallbackDebug2DebugLevel aCallback, void* aPtr)
{
    iCallbackDebugLevel = aCallback;
    iPtrDebugLevel = aPtr;
    DvServiceLinnCoUkDebug2::EnableActionDebugLevel();
}

void DvServiceLinnCoUkDebug2C::EnableActionMemWrite(CallbackDebug2MemWrite aCallback, void* aPtr)
{
    iCallbackMemWrite = aCallback;
    iPtrMemWrite = aPtr;
    DvServiceLinnCoUkDebug2::EnableActionMemWrite();
}

void DvServiceLinnCoUkDebug2C::SetDebugLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aaDebugLevel)
{
    ASSERT(iCallbackSetDebugLevel != NULL);
    if (0 != iCallbackSetDebugLevel(iPtrSetDebugLevel, aVersion, aaDebugLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDebug2C::DebugLevel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDebugLevel)
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

void DvServiceLinnCoUkDebug2C::MemWrite(IInvocationResponse& aResponse, TUint aVersion, TUint aaMemAddress, const Brx& aaMemData)
{
    ASSERT(iCallbackMemWrite != NULL);
    if (0 != iCallbackMemWrite(iPtrMemWrite, aVersion, aaMemAddress, (const char*)aaMemData.Ptr(), aaMemData.Bytes())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvServiceLinnCoUkDebug2Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkDebug2C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkDebug2Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkDebug2C*>(aService);
}

void DvServiceLinnCoUkDebug2EnableActionSetDebugLevel(THandle aService, CallbackDebug2SetDebugLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDebug2C*>(aService)->EnableActionSetDebugLevel(aCallback, aPtr);
}

void DvServiceLinnCoUkDebug2EnableActionDebugLevel(THandle aService, CallbackDebug2DebugLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDebug2C*>(aService)->EnableActionDebugLevel(aCallback, aPtr);
}

void DvServiceLinnCoUkDebug2EnableActionMemWrite(THandle aService, CallbackDebug2MemWrite aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDebug2C*>(aService)->EnableActionMemWrite(aCallback, aPtr);
}

