#ifndef HEADER_DVLINNCOUKPRODUCT2_C
#define HEADER_DVLINNCOUKPRODUCT2_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackProduct2Type)(void* aPtr, uint32_t aVersion, char** aaType);
typedef int32_t (*CallbackProduct2Model)(void* aPtr, uint32_t aVersion, char** aaModel);
typedef int32_t (*CallbackProduct2Name)(void* aPtr, uint32_t aVersion, char** aaName);
typedef int32_t (*CallbackProduct2SetName)(void* aPtr, uint32_t aVersion, const char* aaName);
typedef int32_t (*CallbackProduct2Room)(void* aPtr, uint32_t aVersion, char** aaRoom);
typedef int32_t (*CallbackProduct2SetRoom)(void* aPtr, uint32_t aVersion, const char* aaRoom);
typedef int32_t (*CallbackProduct2Standby)(void* aPtr, uint32_t aVersion, uint32_t* aaStandby);
typedef int32_t (*CallbackProduct2SetStandby)(void* aPtr, uint32_t aVersion, uint32_t aaStandby);
typedef int32_t (*CallbackProduct2SourceCount)(void* aPtr, uint32_t aVersion, uint32_t* aaSourceCount);
typedef int32_t (*CallbackProduct2SourceIndex)(void* aPtr, uint32_t aVersion, uint32_t* aaSourceIndex);
typedef int32_t (*CallbackProduct2SetSourceIndex)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex);
typedef int32_t (*CallbackProduct2SourceType)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex, char** aaSourceType);

DllExport THandle DvProviderLinnCoUkProduct2Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkProduct2Destroy(THandle aProvider);

DllExport void DvProviderLinnCoUkProduct2EnableActionType(THandle aProvider, CallbackProduct2Type aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct2EnableActionModel(THandle aProvider, CallbackProduct2Model aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct2EnableActionName(THandle aProvider, CallbackProduct2Name aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct2EnableActionSetName(THandle aProvider, CallbackProduct2SetName aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct2EnableActionRoom(THandle aProvider, CallbackProduct2Room aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct2EnableActionSetRoom(THandle aProvider, CallbackProduct2SetRoom aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct2EnableActionStandby(THandle aProvider, CallbackProduct2Standby aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct2EnableActionSetStandby(THandle aProvider, CallbackProduct2SetStandby aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct2EnableActionSourceCount(THandle aProvider, CallbackProduct2SourceCount aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct2EnableActionSourceIndex(THandle aProvider, CallbackProduct2SourceIndex aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct2EnableActionSetSourceIndex(THandle aProvider, CallbackProduct2SetSourceIndex aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProduct2EnableActionSourceType(THandle aProvider, CallbackProduct2SourceType aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkProduct2SetPropertyProductName(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct2GetPropertyProductName(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkProduct2SetPropertyProductRoom(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct2GetPropertyProductRoom(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkProduct2SetPropertyProductStandby(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct2GetPropertyProductStandby(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkProduct2SetPropertyProductSourceIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProduct2GetPropertyProductSourceIndex(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPRODUCT2_C

