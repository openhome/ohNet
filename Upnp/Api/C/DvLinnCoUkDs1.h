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

DllExport THandle DvServiceLinnCoUkDs1Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkDs1Destroy(THandle aService);

DllExport void DvServiceLinnCoUkDs1EnableActionPlay(THandle aService, CallbackDs1Play aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDs1EnableActionPause(THandle aService, CallbackDs1Pause aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDs1EnableActionStop(THandle aService, CallbackDs1Stop aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDs1EnableActionSeekSecondAbsolute(THandle aService, CallbackDs1SeekSecondAbsolute aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDs1EnableActionSeekSecondRelative(THandle aService, CallbackDs1SeekSecondRelative aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDs1EnableActionSeekTrackId(THandle aService, CallbackDs1SeekTrackId aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDs1EnableActionSeekTrackAbsolute(THandle aService, CallbackDs1SeekTrackAbsolute aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDs1EnableActionSeekTrackRelative(THandle aService, CallbackDs1SeekTrackRelative aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDs1EnableActionState(THandle aService, CallbackDs1State aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkDs1EnableActionProtocolInfo(THandle aService, CallbackDs1ProtocolInfo aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkDs1SetPropertySupportedProtocols(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkDs1GetPropertySupportedProtocols(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkDs1SetPropertyTrackDuration(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkDs1GetPropertyTrackDuration(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkDs1SetPropertyTrackBitRate(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkDs1GetPropertyTrackBitRate(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkDs1SetPropertyTrackLossless(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkDs1GetPropertyTrackLossless(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkDs1SetPropertyTrackBitDepth(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkDs1GetPropertyTrackBitDepth(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkDs1SetPropertyTrackSampleRate(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkDs1GetPropertyTrackSampleRate(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkDs1SetPropertyTrackCodecName(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkDs1GetPropertyTrackCodecName(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkDs1SetPropertyTrackId(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkDs1GetPropertyTrackId(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkDs1SetPropertyTransportState(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkDs1GetPropertyTransportState(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKDS1_C

