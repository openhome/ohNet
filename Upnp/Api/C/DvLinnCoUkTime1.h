#ifndef HEADER_DVLINNCOUKTIME1_C
#define HEADER_DVLINNCOUKTIME1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackTime1Time)(void* aPtr, uint32_t aVersion, uint32_t* aaTrackCount, uint32_t* aaDuration, uint32_t* aaSeconds);

DllExport THandle DvProviderLinnCoUkTime1Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkTime1Destroy(THandle aProvider);

DllExport void DvProviderLinnCoUkTime1EnableActionTime(THandle aProvider, CallbackTime1Time aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkTime1SetPropertyTrackCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkTime1GetPropertyTrackCount(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkTime1SetPropertyDuration(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkTime1GetPropertyDuration(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkTime1SetPropertySeconds(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkTime1GetPropertySeconds(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKTIME1_C

