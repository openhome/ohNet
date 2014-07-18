/**
 * Provider for the av.openhome.org:Playlist:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGPLAYLIST1_C
#define HEADER_DVAVOPENHOMEORGPLAYLIST1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderAvOpenhomeOrgPlaylist1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Play action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionPlay
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1Play)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the Pause action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionPause
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1Pause)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the Stop action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionStop
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1Stop)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the Next action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionNext
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1Next)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the Previous action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionPrevious
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1Previous)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the SetRepeat action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionSetRepeat
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1SetRepeat)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue);
/**
 * Callback which runs when the Repeat action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionRepeat
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1Repeat)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);
/**
 * Callback which runs when the SetShuffle action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionSetShuffle
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1SetShuffle)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue);
/**
 * Callback which runs when the Shuffle action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionShuffle
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1Shuffle)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);
/**
 * Callback which runs when the SeekSecondAbsolute action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekSecondAbsolute
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1SeekSecondAbsolute)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue);
/**
 * Callback which runs when the SeekSecondRelative action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekSecondRelative
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1SeekSecondRelative)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, int32_t aValue);
/**
 * Callback which runs when the SeekId action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekId
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1SeekId)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue);
/**
 * Callback which runs when the SeekIndex action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekIndex
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1SeekIndex)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue);
/**
 * Callback which runs when the TransportState action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionTransportState
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1TransportState)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValue);
/**
 * Callback which runs when the Id action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionId
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1Id)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);
/**
 * Callback which runs when the Read action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionRead
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aId
 * @param[out] aUri
 * @param[out] aMetadata
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1Read)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aId, char** aUri, char** aMetadata);
/**
 * Callback which runs when the ReadList action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionReadList
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aIdList
 * @param[out] aTrackList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1ReadList)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aIdList, char** aTrackList);
/**
 * Callback which runs when the Insert action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionInsert
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aAfterId
 * @param[in]  aUri
 * @param[in]  aMetadata
 * @param[out] aNewId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1Insert)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aAfterId, const char* aUri, const char* aMetadata, uint32_t* aNewId);
/**
 * Callback which runs when the DeleteId action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionDeleteId
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1DeleteId)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue);
/**
 * Callback which runs when the DeleteAll action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionDeleteAll
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1DeleteAll)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the TracksMax action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionTracksMax
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1TracksMax)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);
/**
 * Callback which runs when the IdArray action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionIdArray
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aToken
 * @param[out] aArray
 * @param[out] aArrayLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1IdArray)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aToken, char** aArray, uint32_t* aArrayLen);
/**
 * Callback which runs when the IdArrayChanged action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionIdArrayChanged
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aToken
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1IdArrayChanged)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aToken, uint32_t* aValue);
/**
 * Callback which runs when the ProtocolInfo action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionProtocolInfo
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylist1ProtocolInfo)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderAvOpenhomeOrgPlaylist1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1Destroy(THandle aProvider);

/**
 * Enable the TransportState property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnablePropertyTransportState(THandle aProvider);
/**
 * Enable the Repeat property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnablePropertyRepeat(THandle aProvider);
/**
 * Enable the Shuffle property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnablePropertyShuffle(THandle aProvider);
/**
 * Enable the Id property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnablePropertyId(THandle aProvider);
/**
 * Enable the IdArray property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnablePropertyIdArray(THandle aProvider);
/**
 * Enable the TracksMax property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnablePropertyTracksMax(THandle aProvider);
/**
 * Enable the ProtocolInfo property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnablePropertyProtocolInfo(THandle aProvider);

/**
 * Register a callback for the action Play
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionPlay(THandle aProvider, CallbackPlaylist1Play aCallback, void* aPtr);
/**
 * Register a callback for the action Pause
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionPause(THandle aProvider, CallbackPlaylist1Pause aCallback, void* aPtr);
/**
 * Register a callback for the action Stop
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionStop(THandle aProvider, CallbackPlaylist1Stop aCallback, void* aPtr);
/**
 * Register a callback for the action Next
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionNext(THandle aProvider, CallbackPlaylist1Next aCallback, void* aPtr);
/**
 * Register a callback for the action Previous
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionPrevious(THandle aProvider, CallbackPlaylist1Previous aCallback, void* aPtr);
/**
 * Register a callback for the action SetRepeat
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionSetRepeat(THandle aProvider, CallbackPlaylist1SetRepeat aCallback, void* aPtr);
/**
 * Register a callback for the action Repeat
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionRepeat(THandle aProvider, CallbackPlaylist1Repeat aCallback, void* aPtr);
/**
 * Register a callback for the action SetShuffle
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionSetShuffle(THandle aProvider, CallbackPlaylist1SetShuffle aCallback, void* aPtr);
/**
 * Register a callback for the action Shuffle
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionShuffle(THandle aProvider, CallbackPlaylist1Shuffle aCallback, void* aPtr);
/**
 * Register a callback for the action SeekSecondAbsolute
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekSecondAbsolute(THandle aProvider, CallbackPlaylist1SeekSecondAbsolute aCallback, void* aPtr);
/**
 * Register a callback for the action SeekSecondRelative
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekSecondRelative(THandle aProvider, CallbackPlaylist1SeekSecondRelative aCallback, void* aPtr);
/**
 * Register a callback for the action SeekId
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekId(THandle aProvider, CallbackPlaylist1SeekId aCallback, void* aPtr);
/**
 * Register a callback for the action SeekIndex
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekIndex(THandle aProvider, CallbackPlaylist1SeekIndex aCallback, void* aPtr);
/**
 * Register a callback for the action TransportState
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionTransportState(THandle aProvider, CallbackPlaylist1TransportState aCallback, void* aPtr);
/**
 * Register a callback for the action Id
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionId(THandle aProvider, CallbackPlaylist1Id aCallback, void* aPtr);
/**
 * Register a callback for the action Read
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionRead(THandle aProvider, CallbackPlaylist1Read aCallback, void* aPtr);
/**
 * Register a callback for the action ReadList
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionReadList(THandle aProvider, CallbackPlaylist1ReadList aCallback, void* aPtr);
/**
 * Register a callback for the action Insert
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionInsert(THandle aProvider, CallbackPlaylist1Insert aCallback, void* aPtr);
/**
 * Register a callback for the action DeleteId
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionDeleteId(THandle aProvider, CallbackPlaylist1DeleteId aCallback, void* aPtr);
/**
 * Register a callback for the action DeleteAll
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionDeleteAll(THandle aProvider, CallbackPlaylist1DeleteAll aCallback, void* aPtr);
/**
 * Register a callback for the action TracksMax
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionTracksMax(THandle aProvider, CallbackPlaylist1TracksMax aCallback, void* aPtr);
/**
 * Register a callback for the action IdArray
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionIdArray(THandle aProvider, CallbackPlaylist1IdArray aCallback, void* aPtr);
/**
 * Register a callback for the action IdArrayChanged
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionIdArrayChanged(THandle aProvider, CallbackPlaylist1IdArrayChanged aCallback, void* aPtr);
/**
 * Register a callback for the action ProtocolInfo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1EnableActionProtocolInfo(THandle aProvider, CallbackPlaylist1ProtocolInfo aCallback, void* aPtr);

/**
 * Set the value of the TransportState property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylist1EnablePropertyTransportState has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgPlaylist1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TransportState property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylist1EnablePropertyTransportState has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1GetPropertyTransportState(THandle aProvider, char** aValue);
/**
 * Set the value of the Repeat property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylist1EnablePropertyRepeat has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgPlaylist1SetPropertyRepeat(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Repeat property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylist1EnablePropertyRepeat has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1GetPropertyRepeat(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Shuffle property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylist1EnablePropertyShuffle has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgPlaylist1SetPropertyShuffle(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Shuffle property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylist1EnablePropertyShuffle has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1GetPropertyShuffle(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Id property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylist1EnablePropertyId has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgPlaylist1SetPropertyId(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Id property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylist1EnablePropertyId has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1GetPropertyId(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the IdArray property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylist1EnablePropertyIdArray has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[in]  aValueLen  Size in bytes pointed to by aValue
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgPlaylist1SetPropertyIdArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged);
/**
 * Get a copy of the value of the IdArray property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylist1EnablePropertyIdArray has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 * @param[out] aValueLen  Size in bytes pointed to by aValue
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1GetPropertyIdArray(THandle aProvider, char** aValue, uint32_t* aValueLen);
/**
 * Set the value of the TracksMax property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylist1EnablePropertyTracksMax has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgPlaylist1SetPropertyTracksMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TracksMax property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylist1EnablePropertyTracksMax has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1GetPropertyTracksMax(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ProtocolInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylist1EnablePropertyProtocolInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgPlaylist1SetPropertyProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProtocolInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylist1EnablePropertyProtocolInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylist1GetPropertyProtocolInfo(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGPLAYLIST1_C

