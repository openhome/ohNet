/**
 * Provider for the upnp.org:AVTransport:1 UPnP service
 */
#ifndef HEADER_DVUPNPORGAVTRANSPORT1_C
#define HEADER_DVUPNPORGAVTRANSPORT1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderUpnpOrgAVTransport1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the SetAVTransportURI action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionSetAVTransportURI
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aCurrentURI
 * @param[in]  aCurrentURIMetaData
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport1SetAVTransportURI)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aCurrentURI, const char* aCurrentURIMetaData);
/**
 * Callback which runs when the SetNextAVTransportURI action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionSetNextAVTransportURI
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aNextURI
 * @param[in]  aNextURIMetaData
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport1SetNextAVTransportURI)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aNextURI, const char* aNextURIMetaData);
/**
 * Callback which runs when the GetMediaInfo action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionGetMediaInfo
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
typedef int32_t (STDCALL *CallbackAVTransport1GetMediaInfo)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
/**
 * Callback which runs when the GetTransportInfo action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionGetTransportInfo
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
typedef int32_t (STDCALL *CallbackAVTransport1GetTransportInfo)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed);
/**
 * Callback which runs when the GetPositionInfo action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionGetPositionInfo
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
typedef int32_t (STDCALL *CallbackAVTransport1GetPositionInfo)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int32_t* aRelCount, int32_t* aAbsCount);
/**
 * Callback which runs when the GetDeviceCapabilities action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionGetDeviceCapabilities
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
typedef int32_t (STDCALL *CallbackAVTransport1GetDeviceCapabilities)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes);
/**
 * Callback which runs when the GetTransportSettings action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionGetTransportSettings
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aPlayMode
 * @param[out] aRecQualityMode
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport1GetTransportSettings)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, char** aPlayMode, char** aRecQualityMode);
/**
 * Callback which runs when the Stop action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionStop
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport1Stop)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID);
/**
 * Callback which runs when the Play action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionPlay
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aSpeed
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport1Play)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aSpeed);
/**
 * Callback which runs when the Pause action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionPause
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport1Pause)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID);
/**
 * Callback which runs when the Record action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionRecord
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport1Record)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID);
/**
 * Callback which runs when the Seek action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionSeek
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aUnit
 * @param[in]  aTarget
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport1Seek)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aUnit, const char* aTarget);
/**
 * Callback which runs when the Next action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionNext
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport1Next)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID);
/**
 * Callback which runs when the Previous action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionPrevious
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport1Previous)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID);
/**
 * Callback which runs when the SetPlayMode action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionSetPlayMode
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aNewPlayMode
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport1SetPlayMode)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aNewPlayMode);
/**
 * Callback which runs when the SetRecordQualityMode action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionSetRecordQualityMode
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aNewRecordQualityMode
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport1SetRecordQualityMode)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aNewRecordQualityMode);
/**
 * Callback which runs when the GetCurrentTransportActions action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgAVTransport1EnableActionGetCurrentTransportActions
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aActions
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackAVTransport1GetCurrentTransportActions)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, char** aActions);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderUpnpOrgAVTransport1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1Destroy(THandle aProvider);

/**
 * Enable the LastChange property.
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnablePropertyLastChange(THandle aProvider);

/**
 * Register a callback for the action SetAVTransportURI
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionSetAVTransportURI(THandle aProvider, CallbackAVTransport1SetAVTransportURI aCallback, void* aPtr);
/**
 * Register a callback for the action SetNextAVTransportURI
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionSetNextAVTransportURI(THandle aProvider, CallbackAVTransport1SetNextAVTransportURI aCallback, void* aPtr);
/**
 * Register a callback for the action GetMediaInfo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionGetMediaInfo(THandle aProvider, CallbackAVTransport1GetMediaInfo aCallback, void* aPtr);
/**
 * Register a callback for the action GetTransportInfo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionGetTransportInfo(THandle aProvider, CallbackAVTransport1GetTransportInfo aCallback, void* aPtr);
/**
 * Register a callback for the action GetPositionInfo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionGetPositionInfo(THandle aProvider, CallbackAVTransport1GetPositionInfo aCallback, void* aPtr);
/**
 * Register a callback for the action GetDeviceCapabilities
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionGetDeviceCapabilities(THandle aProvider, CallbackAVTransport1GetDeviceCapabilities aCallback, void* aPtr);
/**
 * Register a callback for the action GetTransportSettings
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionGetTransportSettings(THandle aProvider, CallbackAVTransport1GetTransportSettings aCallback, void* aPtr);
/**
 * Register a callback for the action Stop
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionStop(THandle aProvider, CallbackAVTransport1Stop aCallback, void* aPtr);
/**
 * Register a callback for the action Play
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionPlay(THandle aProvider, CallbackAVTransport1Play aCallback, void* aPtr);
/**
 * Register a callback for the action Pause
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionPause(THandle aProvider, CallbackAVTransport1Pause aCallback, void* aPtr);
/**
 * Register a callback for the action Record
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionRecord(THandle aProvider, CallbackAVTransport1Record aCallback, void* aPtr);
/**
 * Register a callback for the action Seek
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionSeek(THandle aProvider, CallbackAVTransport1Seek aCallback, void* aPtr);
/**
 * Register a callback for the action Next
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionNext(THandle aProvider, CallbackAVTransport1Next aCallback, void* aPtr);
/**
 * Register a callback for the action Previous
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionPrevious(THandle aProvider, CallbackAVTransport1Previous aCallback, void* aPtr);
/**
 * Register a callback for the action SetPlayMode
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionSetPlayMode(THandle aProvider, CallbackAVTransport1SetPlayMode aCallback, void* aPtr);
/**
 * Register a callback for the action SetRecordQualityMode
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionSetRecordQualityMode(THandle aProvider, CallbackAVTransport1SetRecordQualityMode aCallback, void* aPtr);
/**
 * Register a callback for the action GetCurrentTransportActions
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1EnableActionGetCurrentTransportActions(THandle aProvider, CallbackAVTransport1GetCurrentTransportActions aCallback, void* aPtr);

/**
 * Set the value of the LastChange property
 *
 * Can only be called if DvProviderUpnpOrgAVTransport1EnablePropertyLastChange has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgAVTransport1SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the LastChange property
 *
 * Can only be called if DvProviderUpnpOrgAVTransport1EnablePropertyLastChange has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgAVTransport1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgAVTransport1GetPropertyLastChange(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGAVTRANSPORT1_C

