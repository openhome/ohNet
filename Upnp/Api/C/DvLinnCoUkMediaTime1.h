#ifndef HEADER_DVLINNCOUKMEDIATIME1_C
#define HEADER_DVLINNCOUKMEDIATIME1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackMediaTime1Seconds)(void* aPtr, uint32_t aVersion, uint32_t* aaSeconds);

DllExport THandle DvServiceLinnCoUkMediaTime1Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkMediaTime1Destroy(THandle aService);

DllExport void DvServiceLinnCoUkMediaTime1EnableActionSeconds(THandle aService, CallbackMediaTime1Seconds aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkMediaTime1SetPropertySeconds(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkMediaTime1GetPropertySeconds(THandle aService, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKMEDIATIME1_C

