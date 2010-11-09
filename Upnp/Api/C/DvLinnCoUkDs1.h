#ifndef HEADER_DVLINNCOUKDS1_C
#define HEADER_DVLINNCOUKDS1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackDs1Play)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackDs1Pause)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackDs1Stop)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackDs1SeekSecondAbsolute)(void* aPtr, uint32_t aVersion, uint32_t aaSecond);
typedef int32_t (*CallbackDs1SeekSecondRelative)(void* aPtr, uint32_t aVersion, int32_t aaSecond);
typedef int32_t (*CallbackDs1SeekTrackId)(void* aPtr, uint32_t aVersion, uint32_t aaTrackId);
typedef int32_t (*CallbackDs1SeekTrackAbsolute)(void* aPtr, uint32_t aVersion, uint32_t aaTrack);
typedef int32_t (*CallbackDs1SeekTrackRelative)(void* aPtr, uint32_t aVersion, int32_t aaTrack);
typedef int32_t (*CallbackDs1State)(void* aPtr, uint32_t aVersion, char** aaTransportState, uint32_t* aaTrackDuration, uint32_t* aaTrackBitRate, uint32_t* aaTrackLossless, uint32_t* aaTrackBitDepth, uint32_t* aaTrackSampleRate, char** aaTrackCodecName, uint32_t* aaTrackId);
typedef int32_t (*CallbackDs1ProtocolInfo)(void* aPtr, uint32_t aVersion, char** aaSupportedProtocols);

DllExport THandle DvProviderLinnCoUkDs1Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkDs1Destroy(THandle aProvider);

DllExport void DvProviderLinnCoUkDs1EnableActionPlay(THandle aProvider, CallbackDs1Play aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionPause(THandle aProvider, CallbackDs1Pause aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionStop(THandle aProvider, CallbackDs1Stop aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionSeekSecondAbsolute(THandle aProvider, CallbackDs1SeekSecondAbsolute aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionSeekSecondRelative(THandle aProvider, CallbackDs1SeekSecondRelative aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionSeekTrackId(THandle aProvider, CallbackDs1SeekTrackId aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionSeekTrackAbsolute(THandle aProvider, CallbackDs1SeekTrackAbsolute aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionSeekTrackRelative(THandle aProvider, CallbackDs1SeekTrackRelative aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionState(THandle aProvider, CallbackDs1State aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionProtocolInfo(THandle aProvider, CallbackDs1ProtocolInfo aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkDs1SetPropertySupportedProtocols(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertySupportedProtocols(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackDuration(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackDuration(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackBitRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackBitRate(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackLossless(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackLossless(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackBitDepth(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackBitDepth(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackSampleRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackSampleRate(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackCodecName(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackCodecName(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackId(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackId(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTransportState(THandle aProvider, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKDS1_C

