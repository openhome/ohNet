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

DllExport THandle DvProviderLinnCoUkProduct1Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkProduct1Destroy(THandle aProvider);

DllExport void DvProviderLinnCoUkProduct1EnableActionRoom(THandle aProvider, CallbackProduct1Room aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct1EnableActionSetRoom(THandle aProvider, CallbackProduct1SetRoom aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct1EnableActionStandby(THandle aProvider, CallbackProduct1Standby aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct1EnableActionSetStandby(THandle aProvider, CallbackProduct1SetStandby aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkProduct1SetPropertyRoom(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct1GetPropertyRoom(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkProduct1SetPropertyStandby(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct1GetPropertyStandby(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPRODUCT1_C

