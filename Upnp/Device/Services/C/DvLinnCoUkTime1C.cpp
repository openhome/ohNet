#include <C/DvLinnCoUkTime1.h>
#include <Core/DvLinnCoUkTime1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkTime1C : public DvServiceLinnCoUkTime1
{
public:
    DvServiceLinnCoUkTime1C(DvDevice& aDevice);
    void EnableActionTime(CallbackTime1Time aCallback, void* aPtr);
private:
    void Time(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTrackCount, IInvocationResponseUint& aaDuration, IInvocationResponseUint& aaSeconds);
private:
    CallbackTime1Time iCallbackTime;
    void* iPtrTime;
};

DvServiceLinnCoUkTime1C::DvServiceLinnCoUkTime1C(DvDevice& aDevice)
    : DvServiceLinnCoUkTime1(aDevice)
{
}

void DvServiceLinnCoUkTime1C::EnableActionTime(CallbackTime1Time aCallback, void* aPtr)
{
    iCallbackTime = aCallback;
    iPtrTime = aPtr;
    DvServiceLinnCoUkTime1::EnableActionTime();
}

void DvServiceLinnCoUkTime1C::Time(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTrackCount, IInvocationResponseUint& aaDuration, IInvocationResponseUint& aaSeconds)
{
    uint32_t aTrackCount;
    uint32_t aDuration;
    uint32_t aSeconds;
    ASSERT(iCallbackTime != NULL);
    if (0 != iCallbackTime(iPtrTime, aVersion, &aTrackCount, &aDuration, &aSeconds)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaTrackCount.Write(aTrackCount);
    aaDuration.Write(aDuration);
    aaSeconds.Write(aSeconds);
    aResponse.End();
}



THandle DvServiceLinnCoUkTime1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkTime1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkTime1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkTime1C*>(aService);
}

void DvServiceLinnCoUkTime1EnableActionTime(THandle aService, CallbackTime1Time aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkTime1C*>(aService)->EnableActionTime(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkTime1SetPropertyTrackCount(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkTime1C*>(aService)->SetPropertyTrackCount(aValue);
    return 0;
}

void DvServiceLinnCoUkTime1GetPropertyTrackCount(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkTime1C*>(aService)->GetPropertyTrackCount(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkTime1SetPropertyDuration(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkTime1C*>(aService)->SetPropertyDuration(aValue);
    return 0;
}

void DvServiceLinnCoUkTime1GetPropertyDuration(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkTime1C*>(aService)->GetPropertyDuration(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkTime1SetPropertySeconds(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkTime1C*>(aService)->SetPropertySeconds(aValue);
    return 0;
}

void DvServiceLinnCoUkTime1GetPropertySeconds(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkTime1C*>(aService)->GetPropertySeconds(val);
    *aValue = val;
}

