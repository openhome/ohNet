#include <C/DvLinnCoUkPtest1.h>
#include <Core/DvLinnCoUkPtest1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkPtest1C : public DvServiceLinnCoUkPtest1
{
public:
    DvServiceLinnCoUkPtest1C(DvDevice& aDevice);
    void EnableActionTestComPort(CallbackPtest1TestComPort aCallback, void* aPtr);
    void EnableActionLedsOn(CallbackPtest1LedsOn aCallback, void* aPtr);
    void EnableActionLedsOff(CallbackPtest1LedsOff aCallback, void* aPtr);
private:
    void TestComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaPort, IInvocationResponseBool& aaResult);
    void LedsOn(IInvocationResponse& aResponse, TUint aVersion);
    void LedsOff(IInvocationResponse& aResponse, TUint aVersion);
private:
    CallbackPtest1TestComPort iCallbackTestComPort;
    void* iPtrTestComPort;
    CallbackPtest1LedsOn iCallbackLedsOn;
    void* iPtrLedsOn;
    CallbackPtest1LedsOff iCallbackLedsOff;
    void* iPtrLedsOff;
};

DvServiceLinnCoUkPtest1C::DvServiceLinnCoUkPtest1C(DvDevice& aDevice)
    : DvServiceLinnCoUkPtest1(aDevice)
{
}

void DvServiceLinnCoUkPtest1C::EnableActionTestComPort(CallbackPtest1TestComPort aCallback, void* aPtr)
{
    iCallbackTestComPort = aCallback;
    iPtrTestComPort = aPtr;
    DvServiceLinnCoUkPtest1::EnableActionTestComPort();
}

void DvServiceLinnCoUkPtest1C::EnableActionLedsOn(CallbackPtest1LedsOn aCallback, void* aPtr)
{
    iCallbackLedsOn = aCallback;
    iPtrLedsOn = aPtr;
    DvServiceLinnCoUkPtest1::EnableActionLedsOn();
}

void DvServiceLinnCoUkPtest1C::EnableActionLedsOff(CallbackPtest1LedsOff aCallback, void* aPtr)
{
    iCallbackLedsOff = aCallback;
    iPtrLedsOff = aPtr;
    DvServiceLinnCoUkPtest1::EnableActionLedsOff();
}

void DvServiceLinnCoUkPtest1C::TestComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaPort, IInvocationResponseBool& aaResult)
{
    uint32_t aResult;
    ASSERT(iCallbackTestComPort != NULL);
    if (0 != iCallbackTestComPort(iPtrTestComPort, aVersion, aaPort, &aResult)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaResult.Write((aResult!=0));
    aResponse.End();
}

void DvServiceLinnCoUkPtest1C::LedsOn(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackLedsOn != NULL);
    if (0 != iCallbackLedsOn(iPtrLedsOn, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkPtest1C::LedsOff(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackLedsOff != NULL);
    if (0 != iCallbackLedsOff(iPtrLedsOff, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvServiceLinnCoUkPtest1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkPtest1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkPtest1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkPtest1C*>(aService);
}

void DvServiceLinnCoUkPtest1EnableActionTestComPort(THandle aService, CallbackPtest1TestComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPtest1C*>(aService)->EnableActionTestComPort(aCallback, aPtr);
}

void DvServiceLinnCoUkPtest1EnableActionLedsOn(THandle aService, CallbackPtest1LedsOn aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPtest1C*>(aService)->EnableActionLedsOn(aCallback, aPtr);
}

void DvServiceLinnCoUkPtest1EnableActionLedsOff(THandle aService, CallbackPtest1LedsOff aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkPtest1C*>(aService)->EnableActionLedsOff(aCallback, aPtr);
}

