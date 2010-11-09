#ifndef HEADER_DVLINNCOUKINFO1_C
#define HEADER_DVLINNCOUKINFO1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackInfo1Counters)(void* aPtr, uint32_t aVersion, uint32_t* aaTrackCount, uint32_t* aaDetailsCount, uint32_t* aaMetatextCount);
typedef int32_t (*CallbackInfo1Track)(void* aPtr, uint32_t aVersion, char** aaUri, char** aaMetadata);
typedef int32_t (*CallbackInfo1Details)(void* aPtr, uint32_t aVersion, uint32_t* aaDuration, uint32_t* aaBitRate, uint32_t* aaBitDepth, uint32_t* aaSampleRate, uint32_t* aaLossless, char** aaCodecName);
typedef int32_t (*CallbackInfo1Metatext)(void* aPtr, uint32_t aVersion, char** aaMetatext);

DllExport THandle DvProviderLinnCoUkInfo1Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkInfo1Destroy(THandle aProvider);

DllExport void DvProviderLinnCoUkInfo1EnableActionCounters(THandle aProvider, CallbackInfo1Counters aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkInfo1EnableActionTrack(THandle aProvider, CallbackInfo1Track aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkInfo1EnableActionDetails(THandle aProvider, CallbackInfo1Details aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkInfo1EnableActionMetatext(THandle aProvider, CallbackInfo1Metatext aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyTrackCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyTrackCount(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyDetailsCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyDetailsCount(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyMetatextCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyMetatextCount(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyUri(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyMetadata(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyDuration(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyDuration(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyBitRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyBitRate(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyBitDepth(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyBitDepth(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertySampleRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertySampleRate(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyLossless(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyLossless(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyCodecName(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyCodecName(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyMetatext(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyMetatext(THandle aProvider, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKINFO1_C

