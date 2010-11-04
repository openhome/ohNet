#ifndef HEADER_DVLINNCOUKMEDIATIME1_C
#define HEADER_DVLINNCOUKMEDIATIME1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackMediaTime1Seconds)(void* aPtr, uint32_t aVersion, uint32_t* aaSeconds);

DllExport THandle DvProviderLinnCoUkMediaTime1Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkMediaTime1Destroy(THandle aProvider);

DllExport void DvProviderLinnCoUkMediaTime1EnableActionSeconds(THandle aProvider, CallbackMediaTime1Seconds aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkMediaTime1SetPropertySeconds(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkMediaTime1GetPropertySeconds(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKMEDIATIME1_C

