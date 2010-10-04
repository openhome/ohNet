#ifndef HEADER_DVUPNPORGAVTRANSPORT2_C
#define HEADER_DVUPNPORGAVTRANSPORT2_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackAVTransport2SetAVTransportURI)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aCurrentURI, const char* aCurrentURIMetaData);
typedef int32_t (*CallbackAVTransport2SetNextAVTransportURI)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aNextURI, const char* aNextURIMetaData);
typedef int32_t (*CallbackAVTransport2GetMediaInfo)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
typedef int32_t (*CallbackAVTransport2GetMediaInfo_Ext)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aCurrentType, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
typedef int32_t (*CallbackAVTransport2GetTransportInfo)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed);
typedef int32_t (*CallbackAVTransport2GetPositionInfo)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int32_t* aRelCount, int32_t* aAbsCount);
typedef int32_t (*CallbackAVTransport2GetDeviceCapabilities)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes);
typedef int32_t (*CallbackAVTransport2GetTransportSettings)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aPlayMode, char** aRecQualityMode);
typedef int32_t (*CallbackAVTransport2Stop)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID);
typedef int32_t (*CallbackAVTransport2Play)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aSpeed);
typedef int32_t (*CallbackAVTransport2Pause)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID);
typedef int32_t (*CallbackAVTransport2Record)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID);
typedef int32_t (*CallbackAVTransport2Seek)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aUnit, const char* aTarget);
typedef int32_t (*CallbackAVTransport2Next)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID);
typedef int32_t (*CallbackAVTransport2Previous)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID);
typedef int32_t (*CallbackAVTransport2SetPlayMode)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aNewPlayMode);
typedef int32_t (*CallbackAVTransport2SetRecordQualityMode)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aNewRecordQualityMode);
typedef int32_t (*CallbackAVTransport2GetCurrentTransportActions)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aActions);
typedef int32_t (*CallbackAVTransport2GetDRMState)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aCurrentDRMState);
typedef int32_t (*CallbackAVTransport2GetStateVariables)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aStateVariableList, char** aStateVariableValuePairs);
typedef int32_t (*CallbackAVTransport2SetStateVariables)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aAVTransportUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, char** aStateVariableList);

DllExport THandle DvServiceUpnpOrgAVTransport2Create(DvDeviceC aDevice);
DllExport void DvServiceUpnpOrgAVTransport2Destroy(THandle aService);

DllExport void DvServiceUpnpOrgAVTransport2EnableActionSetAVTransportURI(THandle aService, CallbackAVTransport2SetAVTransportURI aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionSetNextAVTransportURI(THandle aService, CallbackAVTransport2SetNextAVTransportURI aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionGetMediaInfo(THandle aService, CallbackAVTransport2GetMediaInfo aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionGetMediaInfo_Ext(THandle aService, CallbackAVTransport2GetMediaInfo_Ext aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionGetTransportInfo(THandle aService, CallbackAVTransport2GetTransportInfo aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionGetPositionInfo(THandle aService, CallbackAVTransport2GetPositionInfo aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionGetDeviceCapabilities(THandle aService, CallbackAVTransport2GetDeviceCapabilities aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionGetTransportSettings(THandle aService, CallbackAVTransport2GetTransportSettings aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionStop(THandle aService, CallbackAVTransport2Stop aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionPlay(THandle aService, CallbackAVTransport2Play aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionPause(THandle aService, CallbackAVTransport2Pause aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionRecord(THandle aService, CallbackAVTransport2Record aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionSeek(THandle aService, CallbackAVTransport2Seek aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionNext(THandle aService, CallbackAVTransport2Next aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionPrevious(THandle aService, CallbackAVTransport2Previous aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionSetPlayMode(THandle aService, CallbackAVTransport2SetPlayMode aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionSetRecordQualityMode(THandle aService, CallbackAVTransport2SetRecordQualityMode aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionGetCurrentTransportActions(THandle aService, CallbackAVTransport2GetCurrentTransportActions aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionGetDRMState(THandle aService, CallbackAVTransport2GetDRMState aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionGetStateVariables(THandle aService, CallbackAVTransport2GetStateVariables aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgAVTransport2EnableActionSetStateVariables(THandle aService, CallbackAVTransport2SetStateVariables aCallback, void* aPtr);

DllExport int32_t DvServiceUpnpOrgAVTransport2SetPropertyLastChange(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgAVTransport2GetPropertyLastChange(THandle aService, char** aValue);
DllExport int32_t DvServiceUpnpOrgAVTransport2SetPropertyDRMState(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgAVTransport2GetPropertyDRMState(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGAVTRANSPORT2_C

