#include <C/DvLinnCoUkTime1.h>
#include <Core/DvLinnCoUkTime1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkTime1C : public DvProviderLinnCoUkTime1
{
public:
    DvProviderLinnCoUkTime1C(DvDevice& aDevice);
    void EnableActionTime(CallbackTime1Time aCallback, void* aPtr);
private:
    void Time(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTrackCount, IInvocationResponseUint& aaDuration, IInvocationResponseUint& aaSeconds);
private:
    CallbackTime1Time iCallbackTime;
    void* iPtrTime;
};

DvProviderLinnCoUkTime1C::DvProviderLinnCoUkTime1C(DvDevice& aDevice)
    : DvProviderLinnCoUkTime1(aDevice)
{
}

void DvProviderLinnCoUkTime1C::EnableActionTime(CallbackTime1Time aCallback, void* aPtr)
{
    iCallbackTime = aCallback;
    iPtrTime = aPtr;
    DvProviderLinnCoUkTime1::EnableActionTime();
}

void DvProviderLinnCoUkTime1C::Time(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaTrackCount, IInvocationResponseUint& aaDuration, IInvocationResponseUint& aaSeconds)
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



THandle DvProviderLinnCoUkTime1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkTime1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkTime1Destroy(THandle aService)
{
    delete reinterpret_cast<DvProviderLinnCoUkTime1C*>(aService);
}

void DvProviderLinnCoUkTime1EnableActionTime(THandle aService, CallbackTime1Time aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkTime1C*>(aService)->EnableActionTime(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkTime1SetPropertyTrackCount(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkTime1C*>(aService)->SetPropertyTrackCount(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkTime1GetPropertyTrackCount(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkTime1C*>(aService)->GetPropertyTrackCount(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkTime1SetPropertyDuration(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkTime1C*>(aService)->SetPropertyDuration(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkTime1GetPropertyDuration(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkTime1C*>(aService)->GetPropertyDuration(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkTime1SetPropertySeconds(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkTime1C*>(aService)->SetPropertySeconds(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkTime1GetPropertySeconds(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkTime1C*>(aService)->GetPropertySeconds(val);
    *aValue = val;
}

