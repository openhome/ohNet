#ifndef HEADER_DVLINNCOUKRADIO1_C
#define HEADER_DVLINNCOUKRADIO1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackRadio1Play)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackRadio1Pause)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackRadio1Stop)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackRadio1SeekSecondAbsolute)(void* aPtr, uint32_t aVersion, uint32_t aaSecond);
typedef int32_t (*CallbackRadio1SeekSecondRelative)(void* aPtr, uint32_t aVersion, int32_t aaSecond);
typedef int32_t (*CallbackRadio1Channel)(void* aPtr, uint32_t aVersion, char** aaUri, char** aaMetadata);
typedef int32_t (*CallbackRadio1SetChannel)(void* aPtr, uint32_t aVersion, const char* aaUri, const char* aaMetadata);
typedef int32_t (*CallbackRadio1ProtocolInfo)(void* aPtr, uint32_t aVersion, char** aaInfo);
typedef int32_t (*CallbackRadio1TransportState)(void* aPtr, uint32_t aVersion, char** aaState);
typedef int32_t (*CallbackRadio1Id)(void* aPtr, uint32_t aVersion, uint32_t* aaId);
typedef int32_t (*CallbackRadio1SetId)(void* aPtr, uint32_t aVersion, uint32_t aaId, const char* aaUri);
typedef int32_t (*CallbackRadio1Read)(void* aPtr, uint32_t aVersion, uint32_t aaId, char** aaMetadata);
typedef int32_t (*CallbackRadio1ReadList)(void* aPtr, uint32_t aVersion, const char* aaIdList, char** aaMetadataList);
typedef int32_t (*CallbackRadio1IdArray)(void* aPtr, uint32_t aVersion, uint32_t* aaIdArrayToken, char** aaIdArray, uint32_t* aaIdArrayLen);
typedef int32_t (*CallbackRadio1IdArrayChanged)(void* aPtr, uint32_t aVersion, uint32_t aaIdArrayToken, uint32_t* aaIdArrayChanged);
typedef int32_t (*CallbackRadio1IdsMax)(void* aPtr, uint32_t aVersion, uint32_t* aaIdsMax);

DllExport THandle DvServiceLinnCoUkRadio1Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkRadio1Destroy(THandle aService);

DllExport void DvServiceLinnCoUkRadio1EnableActionPlay(THandle aService, CallbackRadio1Play aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionPause(THandle aService, CallbackRadio1Pause aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionStop(THandle aService, CallbackRadio1Stop aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionSeekSecondAbsolute(THandle aService, CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionSeekSecondRelative(THandle aService, CallbackRadio1SeekSecondRelative aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionChannel(THandle aService, CallbackRadio1Channel aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionSetChannel(THandle aService, CallbackRadio1SetChannel aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionProtocolInfo(THandle aService, CallbackRadio1ProtocolInfo aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionTransportState(THandle aService, CallbackRadio1TransportState aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionId(THandle aService, CallbackRadio1Id aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionSetId(THandle aService, CallbackRadio1SetId aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionRead(THandle aService, CallbackRadio1Read aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionReadList(THandle aService, CallbackRadio1ReadList aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionIdArray(THandle aService, CallbackRadio1IdArray aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionIdArrayChanged(THandle aService, CallbackRadio1IdArrayChanged aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkRadio1EnableActionIdsMax(THandle aService, CallbackRadio1IdsMax aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkRadio1SetPropertyChannelUri(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkRadio1GetPropertyChannelUri(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkRadio1SetPropertyChannelMetadata(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkRadio1GetPropertyChannelMetadata(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkRadio1SetPropertyTransportState(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkRadio1GetPropertyTransportState(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkRadio1SetPropertyProtocolInfo(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkRadio1GetPropertyProtocolInfo(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkRadio1SetPropertyId(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkRadio1GetPropertyId(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkRadio1SetPropertyIdArray(THandle aService, const char* aValue, uint32_t aValueLen);
DllExport void DvServiceLinnCoUkRadio1GetPropertyIdArray(THandle aService, char** aValue, uint32_t* aValueLen);
DllExport int32_t DvServiceLinnCoUkRadio1SetPropertyIdsMax(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkRadio1GetPropertyIdsMax(THandle aService, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKRADIO1_C

