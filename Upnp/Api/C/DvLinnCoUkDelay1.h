#ifndef HEADER_DVLINNCOUKDELAY1_C
#define HEADER_DVLINNCOUKDELAY1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackDelay1PresetXml)(void* aPtr, uint32_t aVersion, char** aaPresetXml);
typedef int32_t (*CallbackDelay1PresetIndex)(void* aPtr, uint32_t aVersion, uint32_t* aaIndex);
typedef int32_t (*CallbackDelay1SetPresetIndex)(void* aPtr, uint32_t aVersion, uint32_t aaIndex);
typedef int32_t (*CallbackDelay1SetPresetDelay)(void* aPtr, uint32_t aVersion, uint32_t aaIndex, uint32_t aaDelay);
typedef int32_t (*CallbackDelay1SetPresetVisible)(void* aPtr, uint32_t aVersion, uint32_t aaIndex, uint32_t aaVisible);
typedef int32_t (*CallbackDelay1SetPresetName)(void* aPtr, uint32_t aVersion, uint32_t aaIndex, const char* aaName);
typedef int32_t (*CallbackDelay1DelayMinimum)(void* aPtr, uint32_t aVersion, uint32_t* aaDelay);
typedef int32_t (*CallbackDelay1DelayMaximum)(void* aPtr, uint32_t aVersion, uint32_t* aaDelay);
typedef int32_t (*CallbackDelay1PresetCount)(void* aPtr, uint32_t aVersion, uint32_t* aaCount);

DllExport THandle DvServiceLinnCoUkDelay1Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkDelay1Destroy(THandle aService);

DllExport void DvServiceLinnCoUkDelay1EnableActionPresetXml(THandle aService, CallbackDelay1PresetXml aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDelay1EnableActionPresetIndex(THandle aService, CallbackDelay1PresetIndex aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDelay1EnableActionSetPresetIndex(THandle aService, CallbackDelay1SetPresetIndex aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDelay1EnableActionSetPresetDelay(THandle aService, CallbackDelay1SetPresetDelay aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDelay1EnableActionSetPresetVisible(THandle aService, CallbackDelay1SetPresetVisible aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDelay1EnableActionSetPresetName(THandle aService, CallbackDelay1SetPresetName aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDelay1EnableActionDelayMinimum(THandle aService, CallbackDelay1DelayMinimum aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDelay1EnableActionDelayMaximum(THandle aService, CallbackDelay1DelayMaximum aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDelay1EnableActionPresetCount(THandle aService, CallbackDelay1PresetCount aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkDelay1SetPropertyPresetXml(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkDelay1GetPropertyPresetXml(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkDelay1SetPropertyPresetIndex(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkDelay1GetPropertyPresetIndex(THandle aService, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKDELAY1_C

