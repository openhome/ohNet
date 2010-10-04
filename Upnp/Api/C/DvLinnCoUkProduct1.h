#ifndef HEADER_DVLINNCOUKPRODUCT1_C
#define HEADER_DVLINNCOUKPRODUCT1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackProduct1Room)(void* aPtr, uint32_t aVersion, char** aaRoom);
typedef int32_t (*CallbackProduct1SetRoom)(void* aPtr, uint32_t aVersion, const char* aaRoom);
typedef int32_t (*CallbackProduct1Standby)(void* aPtr, uint32_t aVersion, uint32_t* aaStandby);
typedef int32_t (*CallbackProduct1SetStandby)(void* aPtr, uint32_t aVersion, uint32_t aaStandby);

DllExport THandle DvServiceLinnCoUkProduct1Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkProduct1Destroy(THandle aService);

DllExport void DvServiceLinnCoUkProduct1EnableActionRoom(THandle aService, CallbackProduct1Room aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct1EnableActionSetRoom(THandle aService, CallbackProduct1SetRoom aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct1EnableActionStandby(THandle aService, CallbackProduct1Standby aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProduct1EnableActionSetStandby(THandle aService, CallbackProduct1SetStandby aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkProduct1SetPropertyRoom(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkProduct1GetPropertyRoom(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkProduct1SetPropertyStandby(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkProduct1GetPropertyStandby(THandle aService, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPRODUCT1_C

