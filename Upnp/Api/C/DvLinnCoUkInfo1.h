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
DllExport void DvProviderLinnCoUkInfo1Destroy(THandle aService);

DllExport void DvProviderLinnCoUkInfo1EnableActionCounters(THandle aService, CallbackInfo1Counters aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkInfo1EnableActionTrack(THandle aService, CallbackInfo1Track aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkInfo1EnableActionDetails(THandle aService, CallbackInfo1Details aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkInfo1EnableActionMetatext(THandle aService, CallbackInfo1Metatext aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyTrackCount(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyTrackCount(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyDetailsCount(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyDetailsCount(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyMetatextCount(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyMetatextCount(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyUri(THandle aService, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyUri(THandle aService, char** aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyMetadata(THandle aService, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyMetadata(THandle aService, char** aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyDuration(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyDuration(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyBitRate(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyBitRate(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyBitDepth(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyBitDepth(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertySampleRate(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertySampleRate(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyLossless(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyLossless(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyCodecName(THandle aService, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyCodecName(THandle aService, char** aValue);
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyMetatext(THandle aService, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkInfo1GetPropertyMetatext(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKINFO1_C

