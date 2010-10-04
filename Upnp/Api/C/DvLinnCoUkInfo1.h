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

DllExport THandle DvServiceLinnCoUkInfo1Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkInfo1Destroy(THandle aService);

DllExport void DvServiceLinnCoUkInfo1EnableActionCounters(THandle aService, CallbackInfo1Counters aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkInfo1EnableActionTrack(THandle aService, CallbackInfo1Track aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkInfo1EnableActionDetails(THandle aService, CallbackInfo1Details aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkInfo1EnableActionMetatext(THandle aService, CallbackInfo1Metatext aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkInfo1SetPropertyTrackCount(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkInfo1GetPropertyTrackCount(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkInfo1SetPropertyDetailsCount(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkInfo1GetPropertyDetailsCount(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkInfo1SetPropertyMetatextCount(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkInfo1GetPropertyMetatextCount(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkInfo1SetPropertyUri(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkInfo1GetPropertyUri(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkInfo1SetPropertyMetadata(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkInfo1GetPropertyMetadata(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkInfo1SetPropertyDuration(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkInfo1GetPropertyDuration(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkInfo1SetPropertyBitRate(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkInfo1GetPropertyBitRate(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkInfo1SetPropertyBitDepth(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkInfo1GetPropertyBitDepth(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkInfo1SetPropertySampleRate(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkInfo1GetPropertySampleRate(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkInfo1SetPropertyLossless(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkInfo1GetPropertyLossless(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkInfo1SetPropertyCodecName(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkInfo1GetPropertyCodecName(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkInfo1SetPropertyMetatext(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkInfo1GetPropertyMetatext(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKINFO1_C

