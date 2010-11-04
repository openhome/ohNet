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

DllExport THandle DvProviderLinnCoUkRadio1Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkRadio1Destroy(THandle aProvider);

DllExport void DvProviderLinnCoUkRadio1EnableActionPlay(THandle aProvider, CallbackRadio1Play aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionPause(THandle aProvider, CallbackRadio1Pause aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionStop(THandle aProvider, CallbackRadio1Stop aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionSeekSecondAbsolute(THandle aProvider, CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionSeekSecondRelative(THandle aProvider, CallbackRadio1SeekSecondRelative aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionChannel(THandle aProvider, CallbackRadio1Channel aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionSetChannel(THandle aProvider, CallbackRadio1SetChannel aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionProtocolInfo(THandle aProvider, CallbackRadio1ProtocolInfo aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionTransportState(THandle aProvider, CallbackRadio1TransportState aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionId(THandle aProvider, CallbackRadio1Id aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionSetId(THandle aProvider, CallbackRadio1SetId aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionRead(THandle aProvider, CallbackRadio1Read aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionReadList(THandle aProvider, CallbackRadio1ReadList aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionIdArray(THandle aProvider, CallbackRadio1IdArray aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionIdArrayChanged(THandle aProvider, CallbackRadio1IdArrayChanged aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkRadio1EnableActionIdsMax(THandle aProvider, CallbackRadio1IdsMax aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkRadio1SetPropertyChannelUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkRadio1GetPropertyChannelUri(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkRadio1SetPropertyChannelMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkRadio1GetPropertyChannelMetadata(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkRadio1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkRadio1GetPropertyTransportState(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkRadio1SetPropertyProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkRadio1GetPropertyProtocolInfo(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkRadio1SetPropertyId(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkRadio1GetPropertyId(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkRadio1SetPropertyIdArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkRadio1GetPropertyIdArray(THandle aProvider, char** aValue, uint32_t* aValueLen);
DllExport int32_t DvProviderLinnCoUkRadio1SetPropertyIdsMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkRadio1GetPropertyIdsMax(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKRADIO1_C

