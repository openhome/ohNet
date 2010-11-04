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

DllExport THandle DvProviderLinnCoUkDelay1Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkDelay1Destroy(THandle aProvider);

DllExport void DvProviderLinnCoUkDelay1EnableActionPresetXml(THandle aProvider, CallbackDelay1PresetXml aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDelay1EnableActionPresetIndex(THandle aProvider, CallbackDelay1PresetIndex aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDelay1EnableActionSetPresetIndex(THandle aProvider, CallbackDelay1SetPresetIndex aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDelay1EnableActionSetPresetDelay(THandle aProvider, CallbackDelay1SetPresetDelay aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDelay1EnableActionSetPresetVisible(THandle aProvider, CallbackDelay1SetPresetVisible aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDelay1EnableActionSetPresetName(THandle aProvider, CallbackDelay1SetPresetName aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDelay1EnableActionDelayMinimum(THandle aProvider, CallbackDelay1DelayMinimum aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDelay1EnableActionDelayMaximum(THandle aProvider, CallbackDelay1DelayMaximum aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDelay1EnableActionPresetCount(THandle aProvider, CallbackDelay1PresetCount aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkDelay1SetPropertyPresetXml(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDelay1GetPropertyPresetXml(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkDelay1SetPropertyPresetIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDelay1GetPropertyPresetIndex(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKDELAY1_C

