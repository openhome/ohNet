/**
 * Provider for the upnp.org:AVTransport:2 UPnP service
 */
#ifndef HEADER_DVUPNPORGAVTRANSPORT2_C
#define HEADER_DVUPNPORGAVTRANSPORT2_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderUpnpOrgAVTransport2
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the SetAVTransportURI action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionSetAVTransportURI
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aCurrentURI
 * @param[in]  aCurrentURIMetaData
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2SetAVTransportURI)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aCurrentURI, const char* aCurrentURIMetaData);
/**
 * Callback which runs when the SetNextAVTransportURI action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionSetNextAVTransportURI
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aNextURI
 * @param[in]  aNextURIMetaData
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2SetNextAVTransportURI)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aNextURI, const char* aNextURIMetaData);
/**
 * Callback which runs when the GetMediaInfo action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionGetMediaInfo
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aNrTracks
 * @param[out] aMediaDuration
 * @param[out] aCurrentURI
 * @param[out] aCurrentURIMetaData
 * @param[out] aNextURI
 * @param[out] aNextURIMetaData
 * @param[out] aPlayMedium
 * @param[out] aRecordMedium
 * @param[out] aWriteStatus
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2GetMediaInfo)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
/**
 * Callback which runs when the GetMediaInfo_Ext action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionGetMediaInfo_Ext
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentType
 * @param[out] aNrTracks
 * @param[out] aMediaDuration
 * @param[out] aCurrentURI
 * @param[out] aCurrentURIMetaData
 * @param[out] aNextURI
 * @param[out] aNextURIMetaData
 * @param[out] aPlayMedium
 * @param[out] aRecordMedium
 * @param[out] aWriteStatus
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2GetMediaInfo_Ext)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, char** aCurrentType, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
/**
 * Callback which runs when the GetTransportInfo action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionGetTransportInfo
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentTransportState
 * @param[out] aCurrentTransportStatus
 * @param[out] aCurrentSpeed
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2GetTransportInfo)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed);
/**
 * Callback which runs when the GetPositionInfo action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionGetPositionInfo
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aTrack
 * @param[out] aTrackDuration
 * @param[out] aTrackMetaData
 * @param[out] aTrackURI
 * @param[out] aRelTime
 * @param[out] aAbsTime
 * @param[out] aRelCount
 * @param[out] aAbsCount
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2GetPositionInfo)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int32_t* aRelCount, int32_t* aAbsCount);
/**
 * Callback which runs when the GetDeviceCapabilities action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionGetDeviceCapabilities
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aPlayMedia
 * @param[out] aRecMedia
 * @param[out] aRecQualityModes
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2GetDeviceCapabilities)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes);
/**
 * Callback which runs when the GetTransportSettings action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionGetTransportSettings
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aPlayMode
 * @param[out] aRecQualityMode
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2GetTransportSettings)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, char** aPlayMode, char** aRecQualityMode);
/**
 * Callback which runs when the Stop action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionStop
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2Stop)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID);
/**
 * Callback which runs when the Play action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionPlay
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aSpeed
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2Play)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aSpeed);
/**
 * Callback which runs when the Pause action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionPause
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2Pause)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID);
/**
 * Callback which runs when the Record action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionRecord
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2Record)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID);
/**
 * Callback which runs when the Seek action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionSeek
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aUnit
 * @param[in]  aTarget
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2Seek)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aUnit, const char* aTarget);
/**
 * Callback which runs when the Next action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionNext
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2Next)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID);
/**
 * Callback which runs when the Previous action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionPrevious
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2Previous)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID);
/**
 * Callback which runs when the SetPlayMode action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionSetPlayMode
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aNewPlayMode
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2SetPlayMode)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aNewPlayMode);
/**
 * Callback which runs when the SetRecordQualityMode action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionSetRecordQualityMode
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aNewRecordQualityMode
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2SetRecordQualityMode)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aNewRecordQualityMode);
/**
 * Callback which runs when the GetCurrentTransportActions action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionGetCurrentTransportActions
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aActions
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2GetCurrentTransportActions)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, char** aActions);
/**
 * Callback which runs when the GetDRMState action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionGetDRMState
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentDRMState
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2GetDRMState)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, char** aCurrentDRMState);
/**
 * Callback which runs when the GetStateVariables action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionGetStateVariables
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aStateVariableList
 * @param[out] aStateVariableValuePairs
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2GetStateVariables)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aStateVariableList, char** aStateVariableValuePairs);
/**
 * Callback which runs when the SetStateVariables action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport2EnableActionSetStateVariables
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aAVTransportUDN
 * @param[in]  aServiceType
 * @param[in]  aServiceId
 * @param[in]  aStateVariableValuePairs
 * @param[out] aStateVariableList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport2SetStateVariables)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aAVTransportUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, char** aStateVariableList);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderUpnpOrgAVTransport2Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2Destroy(THandle aProvider);

/**
 * Enable the LastChange property.
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnablePropertyLastChange(THandle aProvider);
/**
 * Enable the DRMState property.
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnablePropertyDRMState(THandle aProvider);

/**
 * Register a callback for the action SetAVTransportURI
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionSetAVTransportURI(THandle aProvider, CallbackAVTransport2SetAVTransportURI aCallback, void* aPtr);
/**
 * Register a callback for the action SetNextAVTransportURI
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionSetNextAVTransportURI(THandle aProvider, CallbackAVTransport2SetNextAVTransportURI aCallback, void* aPtr);
/**
 * Register a callback for the action GetMediaInfo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetMediaInfo(THandle aProvider, CallbackAVTransport2GetMediaInfo aCallback, void* aPtr);
/**
 * Register a callback for the action GetMediaInfo_Ext
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetMediaInfo_Ext(THandle aProvider, CallbackAVTransport2GetMediaInfo_Ext aCallback, void* aPtr);
/**
 * Register a callback for the action GetTransportInfo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetTransportInfo(THandle aProvider, CallbackAVTransport2GetTransportInfo aCallback, void* aPtr);
/**
 * Register a callback for the action GetPositionInfo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetPositionInfo(THandle aProvider, CallbackAVTransport2GetPositionInfo aCallback, void* aPtr);
/**
 * Register a callback for the action GetDeviceCapabilities
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetDeviceCapabilities(THandle aProvider, CallbackAVTransport2GetDeviceCapabilities aCallback, void* aPtr);
/**
 * Register a callback for the action GetTransportSettings
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetTransportSettings(THandle aProvider, CallbackAVTransport2GetTransportSettings aCallback, void* aPtr);
/**
 * Register a callback for the action Stop
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionStop(THandle aProvider, CallbackAVTransport2Stop aCallback, void* aPtr);
/**
 * Register a callback for the action Play
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionPlay(THandle aProvider, CallbackAVTransport2Play aCallback, void* aPtr);
/**
 * Register a callback for the action Pause
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionPause(THandle aProvider, CallbackAVTransport2Pause aCallback, void* aPtr);
/**
 * Register a callback for the action Record
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionRecord(THandle aProvider, CallbackAVTransport2Record aCallback, void* aPtr);
/**
 * Register a callback for the action Seek
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionSeek(THandle aProvider, CallbackAVTransport2Seek aCallback, void* aPtr);
/**
 * Register a callback for the action Next
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionNext(THandle aProvider, CallbackAVTransport2Next aCallback, void* aPtr);
/**
 * Register a callback for the action Previous
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionPrevious(THandle aProvider, CallbackAVTransport2Previous aCallback, void* aPtr);
/**
 * Register a callback for the action SetPlayMode
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionSetPlayMode(THandle aProvider, CallbackAVTransport2SetPlayMode aCallback, void* aPtr);
/**
 * Register a callback for the action SetRecordQualityMode
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionSetRecordQualityMode(THandle aProvider, CallbackAVTransport2SetRecordQualityMode aCallback, void* aPtr);
/**
 * Register a callback for the action GetCurrentTransportActions
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetCurrentTransportActions(THandle aProvider, CallbackAVTransport2GetCurrentTransportActions aCallback, void* aPtr);
/**
 * Register a callback for the action GetDRMState
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetDRMState(THandle aProvider, CallbackAVTransport2GetDRMState aCallback, void* aPtr);
/**
 * Register a callback for the action GetStateVariables
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionGetStateVariables(THandle aProvider, CallbackAVTransport2GetStateVariables aCallback, void* aPtr);
/**
 * Register a callback for the action SetStateVariables
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2EnableActionSetStateVariables(THandle aProvider, CallbackAVTransport2SetStateVariables aCallback, void* aPtr);

/**
 * Set the value of the LastChange property
 *
 * Can only be called if DvProviderUpnpOrgAVTransport2EnablePropertyLastChange has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgAVTransport2SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the LastChange property
 *
 * Can only be called if DvProviderUpnpOrgAVTransport2EnablePropertyLastChange has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2GetPropertyLastChange(THandle aProvider, char** aValue);
/**
 * Set the value of the DRMState property
 *
 * Can only be called if DvProviderUpnpOrgAVTransport2EnablePropertyDRMState has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgAVTransport2SetPropertyDRMState(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the DRMState property
 *
 * Can only be called if DvProviderUpnpOrgAVTransport2EnablePropertyDRMState has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgAVTransport2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport2GetPropertyDRMState(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGAVTRANSPORT2_C

