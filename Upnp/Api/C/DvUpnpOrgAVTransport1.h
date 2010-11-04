#ifndef HEADER_DVUPNPORGAVTRANSPORT1_C
#define HEADER_DVUPNPORGAVTRANSPORT1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackAVTransport1SetAVTransportURI)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aCurrentURI, const char* aCurrentURIMetaData);
typedef int32_t (*CallbackAVTransport1SetNextAVTransportURI)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aNextURI, const char* aNextURIMetaData);
typedef int32_t (*CallbackAVTransport1GetMediaInfo)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
typedef int32_t (*CallbackAVTransport1GetTransportInfo)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed);
typedef int32_t (*CallbackAVTransport1GetPositionInfo)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int32_t* aRelCount, int32_t* aAbsCount);
typedef int32_t (*CallbackAVTransport1GetDeviceCapabilities)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes);
typedef int32_t (*CallbackAVTransport1GetTransportSettings)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aPlayMode, char** aRecQualityMode);
typedef int32_t (*CallbackAVTransport1Stop)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID);
typedef int32_t (*CallbackAVTransport1Play)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aSpeed);
typedef int32_t (*CallbackAVTransport1Pause)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID);
typedef int32_t (*CallbackAVTransport1Record)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID);
typedef int32_t (*CallbackAVTransport1Seek)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aUnit, const char* aTarget);
typedef int32_t (*CallbackAVTransport1Next)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID);
typedef int32_t (*CallbackAVTransport1Previous)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID);
typedef int32_t (*CallbackAVTransport1SetPlayMode)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aNewPlayMode);
typedef int32_t (*CallbackAVTransport1SetRecordQualityMode)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aNewRecordQualityMode);
typedef int32_t (*CallbackAVTransport1GetCurrentTransportActions)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aActions);

DllExport THandle DvProviderUpnpOrgAVTransport1Create(DvDeviceC aDevice);
DllExport void DvProviderUpnpOrgAVTransport1Destroy(THandle aProvider);

DllExport void DvProviderUpnpOrgAVTransport1EnableActionSetAVTransportURI(THandle aProvider, CallbackAVTransport1SetAVTransportURI aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionSetNextAVTransportURI(THandle aProvider, CallbackAVTransport1SetNextAVTransportURI aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionGetMediaInfo(THandle aProvider, CallbackAVTransport1GetMediaInfo aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionGetTransportInfo(THandle aProvider, CallbackAVTransport1GetTransportInfo aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionGetPositionInfo(THandle aProvider, CallbackAVTransport1GetPositionInfo aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionGetDeviceCapabilities(THandle aProvider, CallbackAVTransport1GetDeviceCapabilities aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionGetTransportSettings(THandle aProvider, CallbackAVTransport1GetTransportSettings aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionStop(THandle aProvider, CallbackAVTransport1Stop aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionPlay(THandle aProvider, CallbackAVTransport1Play aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionPause(THandle aProvider, CallbackAVTransport1Pause aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionRecord(THandle aProvider, CallbackAVTransport1Record aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionSeek(THandle aProvider, CallbackAVTransport1Seek aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionNext(THandle aProvider, CallbackAVTransport1Next aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionPrevious(THandle aProvider, CallbackAVTransport1Previous aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionSetPlayMode(THandle aProvider, CallbackAVTransport1SetPlayMode aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionSetRecordQualityMode(THandle aProvider, CallbackAVTransport1SetRecordQualityMode aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgAVTransport1EnableActionGetCurrentTransportActions(THandle aProvider, CallbackAVTransport1GetCurrentTransportActions aCallback, void* aPtr);

DllExport int32_t DvProviderUpnpOrgAVTransport1SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgAVTransport1GetPropertyLastChange(THandle aProvider, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGAVTRANSPORT1_C

