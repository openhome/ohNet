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

DllExport THandle DvServiceUpnpOrgAVTransport1Create(DvDeviceC aDevice);
DllExport void DvServiceUpnpOrgAVTransport1Destroy(THandle aService);

DllExport void DvServiceUpnpOrgAVTransport1EnableActionSetAVTransportURI(THandle aService, CallbackAVTransport1SetAVTransportURI aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionSetNextAVTransportURI(THandle aService, CallbackAVTransport1SetNextAVTransportURI aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionGetMediaInfo(THandle aService, CallbackAVTransport1GetMediaInfo aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionGetTransportInfo(THandle aService, CallbackAVTransport1GetTransportInfo aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionGetPositionInfo(THandle aService, CallbackAVTransport1GetPositionInfo aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionGetDeviceCapabilities(THandle aService, CallbackAVTransport1GetDeviceCapabilities aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionGetTransportSettings(THandle aService, CallbackAVTransport1GetTransportSettings aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionStop(THandle aService, CallbackAVTransport1Stop aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionPlay(THandle aService, CallbackAVTransport1Play aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionPause(THandle aService, CallbackAVTransport1Pause aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionRecord(THandle aService, CallbackAVTransport1Record aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionSeek(THandle aService, CallbackAVTransport1Seek aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionNext(THandle aService, CallbackAVTransport1Next aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionPrevious(THandle aService, CallbackAVTransport1Previous aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionSetPlayMode(THandle aService, CallbackAVTransport1SetPlayMode aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionSetRecordQualityMode(THandle aService, CallbackAVTransport1SetRecordQualityMode aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport1EnableActionGetCurrentTransportActions(THandle aService, CallbackAVTransport1GetCurrentTransportActions aCallback, void* aPtr);

DllExport int32_t DvServiceUpnpOrgAVTransport1SetPropertyLastChange(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgAVTransport1GetPropertyLastChange(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGAVTRANSPORT1_C

