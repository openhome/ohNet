#include "DvLinnCoUkPtest1C.h"
#include "DvLinnCoUkPtest1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkPtest1C : public DvProviderLinnCoUkPtest1
{
public:
    DvProviderLinnCoUkPtest1C(DvDevice& aDevice);
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

DvProviderLinnCoUkPtest1C::DvProviderLinnCoUkPtest1C(DvDevice& aDevice)
    : DvProviderLinnCoUkPtest1(aDevice)
{
}

void DvProviderLinnCoUkPtest1C::EnableActionTestComPort(CallbackPtest1TestComPort aCallback, void* aPtr)
{
    iCallbackTestComPort = aCallback;
    iPtrTestComPort = aPtr;
    DvProviderLinnCoUkPtest1::EnableActionTestComPort();
}

void DvProviderLinnCoUkPtest1C::EnableActionLedsOn(CallbackPtest1LedsOn aCallback, void* aPtr)
{
    iCallbackLedsOn = aCallback;
    iPtrLedsOn = aPtr;
    DvProviderLinnCoUkPtest1::EnableActionLedsOn();
}

void DvProviderLinnCoUkPtest1C::EnableActionLedsOff(CallbackPtest1LedsOff aCallback, void* aPtr)
{
    iCallbackLedsOff = aCallback;
    iPtrLedsOff = aPtr;
    DvProviderLinnCoUkPtest1::EnableActionLedsOff();
}

void DvProviderLinnCoUkPtest1C::TestComPort(IInvocationResponse& aResponse, TUint aVersion, TUint aaPort, IInvocationResponseBool& aaResult)
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

void DvProviderLinnCoUkPtest1C::LedsOn(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackLedsOn != NULL);
    if (0 != iCallbackLedsOn(iPtrLedsOn, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkPtest1C::LedsOff(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackLedsOff != NULL);
    if (0 != iCallbackLedsOff(iPtrLedsOff, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvProviderLinnCoUkPtest1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkPtest1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkPtest1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkPtest1C*>(aProvider);
}

void DvProviderLinnCoUkPtest1EnableActionTestComPort(THandle aProvider, CallbackPtest1TestComPort aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPtest1C*>(aProvider)->EnableActionTestComPort(aCallback, aPtr);
}

void DvProviderLinnCoUkPtest1EnableActionLedsOn(THandle aProvider, CallbackPtest1LedsOn aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPtest1C*>(aProvider)->EnableActionLedsOn(aCallback, aPtr);
}

void DvProviderLinnCoUkPtest1EnableActionLedsOff(THandle aProvider, CallbackPtest1LedsOff aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkPtest1C*>(aProvider)->EnableActionLedsOff(aCallback, aPtr);
}

