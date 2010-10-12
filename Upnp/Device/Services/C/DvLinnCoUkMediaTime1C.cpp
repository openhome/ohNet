#include <C/DvLinnCoUkMediaTime1.h>
#include <Core/DvLinnCoUkMediaTime1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkMediaTime1C : public DvServiceLinnCoUkMediaTime1
{
public:
    DvServiceLinnCoUkMediaTime1C(DvDevice& aDevice);
    void EnableActionSeconds(CallbackMediaTime1Seconds aCallback, void* aPtr);
private:
    void Seconds(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSeconds);
private:
    CallbackMediaTime1Seconds iCallbackSeconds;
    void* iPtrSeconds;
};

DvServiceLinnCoUkMediaTime1C::DvServiceLinnCoUkMediaTime1C(DvDevice& aDevice)
    : DvServiceLinnCoUkMediaTime1(aDevice)
{
}

void DvServiceLinnCoUkMediaTime1C::EnableActionSeconds(CallbackMediaTime1Seconds aCallback, void* aPtr)
{
    iCallbackSeconds = aCallback;
    iPtrSeconds = aPtr;
    DvServiceLinnCoUkMediaTime1::EnableActionSeconds();
}

void DvServiceLinnCoUkMediaTime1C::Seconds(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSeconds)
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



THandle DvServiceLinnCoUkMediaTime1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkMediaTime1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkMediaTime1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkMediaTime1C*>(aService);
}

void DvServiceLinnCoUkMediaTime1EnableActionSeconds(THandle aService, CallbackMediaTime1Seconds aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkMediaTime1C*>(aService)->EnableActionSeconds(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkMediaTime1SetPropertySeconds(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkMediaTime1C*>(aService)->SetPropertySeconds(aValue);
    return 0;
}

void DvServiceLinnCoUkMediaTime1GetPropertySeconds(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkMediaTime1C*>(aService)->GetPropertySeconds(val);
    *aValue = val;
}

