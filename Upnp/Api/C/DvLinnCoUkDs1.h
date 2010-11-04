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
DllExport void DvProviderLinnCoUkDs1Destroy(THandle aService);

DllExport void DvProviderLinnCoUkDs1EnableActionPlay(THandle aService, CallbackDs1Play aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionPause(THandle aService, CallbackDs1Pause aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionStop(THandle aService, CallbackDs1Stop aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionSeekSecondAbsolute(THandle aService, CallbackDs1SeekSecondAbsolute aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionSeekSecondRelative(THandle aService, CallbackDs1SeekSecondRelative aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionSeekTrackId(THandle aService, CallbackDs1SeekTrackId aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionSeekTrackAbsolute(THandle aService, CallbackDs1SeekTrackAbsolute aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionSeekTrackRelative(THandle aService, CallbackDs1SeekTrackRelative aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionState(THandle aService, CallbackDs1State aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkDs1EnableActionProtocolInfo(THandle aService, CallbackDs1ProtocolInfo aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkDs1SetPropertySupportedProtocols(THandle aService, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertySupportedProtocols(THandle aService, char** aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackDuration(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackDuration(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackBitRate(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackBitRate(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackLossless(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackLossless(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackBitDepth(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackBitDepth(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackSampleRate(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackSampleRate(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackCodecName(THandle aService, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackCodecName(THandle aService, char** aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackId(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackId(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTransportState(THandle aService, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkDs1GetPropertyTransportState(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKDS1_C

