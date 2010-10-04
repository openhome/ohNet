#ifndef HEADER_DVLINNCOUKTIME1_C
#define HEADER_DVLINNCOUKTIME1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackTime1Time)(void* aPtr, uint32_t aVersion, uint32_t* aaTrackCount, uint32_t* aaDuration, uint32_t* aaSeconds);

DllExport THandle DvServiceLinnCoUkTime1Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkTime1Destroy(THandle aService);

DllExport void DvServiceLinnCoUkTime1EnableActionTime(THandle aService, CallbackTime1Time aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkTime1SetPropertyTrackCount(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkTime1GetPropertyTrackCount(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkTime1SetPropertyDuration(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkTime1GetPropertyDuration(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkTime1SetPropertySeconds(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkTime1GetPropertySeconds(THandle aService, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKTIME1_C

