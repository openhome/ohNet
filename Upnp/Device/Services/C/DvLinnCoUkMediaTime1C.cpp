#include <C/DvLinnCoUkMediaTime1.h>
#include <Core/DvLinnCoUkMediaTime1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkMediaTime1C : public DvProviderLinnCoUkMediaTime1
{
public:
    DvProviderLinnCoUkMediaTime1C(DvDevice& aDevice);
    void EnableActionSeconds(CallbackMediaTime1Seconds aCallback, void* aPtr);
private:
    void Seconds(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSeconds);
private:
    CallbackMediaTime1Seconds iCallbackSeconds;
    void* iPtrSeconds;
};

DvProviderLinnCoUkMediaTime1C::DvProviderLinnCoUkMediaTime1C(DvDevice& aDevice)
    : DvProviderLinnCoUkMediaTime1(aDevice)
{
}

void DvProviderLinnCoUkMediaTime1C::EnableActionSeconds(CallbackMediaTime1Seconds aCallback, void* aPtr)
{
    iCallbackSeconds = aCallback;
    iPtrSeconds = aPtr;
    DvProviderLinnCoUkMediaTime1::EnableActionSeconds();
}

void DvProviderLinnCoUkMediaTime1C::Seconds(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSeconds)
{
    uint32_t aSeconds;
    ASSERT(iCallbackSeconds != NULL);
    if (0 != iCallbackSeconds(iPtrSeconds, aVersion, &aSeconds)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaSeconds.Write(aSeconds);
    aResponse.End();
}



THandle DvProviderLinnCoUkMediaTime1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkMediaTime1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkMediaTime1Destroy(THandle aService)
{
    delete reinterpret_cast<DvProviderLinnCoUkMediaTime1C*>(aService);
}

void DvProviderLinnCoUkMediaTime1EnableActionSeconds(THandle aService, CallbackMediaTime1Seconds aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkMediaTime1C*>(aService)->EnableActionSeconds(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkMediaTime1SetPropertySeconds(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkMediaTime1C*>(aService)->SetPropertySeconds(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkMediaTime1GetPropertySeconds(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkMediaTime1C*>(aService)->GetPropertySeconds(val);
    *aValue = val;
}

