/**
 * Provider for the av.openhome.org:Playlist:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGPLAYLIST1_C
#define HEADER_DVAVOPENHOMEORGPLAYLIST1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

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
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionPlay
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Play)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the Pause action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionPause
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Pause)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the Stop action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionStop
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Stop)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the Next action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionNext
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Next)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the Previous action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionPrevious
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Previous)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the SetRepeat action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionSetRepeat
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1SetRepeat)(void* aPtr, uint32_t aVersion, uint32_t aValue);
/**
 * Callback which runs when the Repeat action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionRepeat
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Repeat)(void* aPtr, uint32_t aVersion, uint32_t* aValue);
/**
 * Callback which runs when the SetShuffle action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionSetShuffle
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1SetShuffle)(void* aPtr, uint32_t aVersion, uint32_t aValue);
/**
 * Callback which runs when the Shuffle action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionShuffle
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Shuffle)(void* aPtr, uint32_t aVersion, uint32_t* aValue);
/**
 * Callback which runs when the SeekSecondAbsolute action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekSecondAbsolute
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1SeekSecondAbsolute)(void* aPtr, uint32_t aVersion, uint32_t aValue);
/**
 * Callback which runs when the SeekSecondRelative action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekSecondRelative
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1SeekSecondRelative)(void* aPtr, uint32_t aVersion, int32_t aValue);
/**
 * Callback which runs when the SeekId action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekId
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1SeekId)(void* aPtr, uint32_t aVersion, uint32_t aValue);
/**
 * Callback which runs when the SeekIndex action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekIndex
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1SeekIndex)(void* aPtr, uint32_t aVersion, uint32_t aValue);
/**
 * Callback which runs when the TransportState action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionTransportState
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1TransportState)(void* aPtr, uint32_t aVersion, char** aValue);
/**
 * Callback which runs when the Id action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionId
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Id)(void* aPtr, uint32_t aVersion, uint32_t* aValue);
/**
 * Callback which runs when the Read action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionRead
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aId
 * @param[out] aUri
 * @param[out] aMetadata
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Read)(void* aPtr, uint32_t aVersion, uint32_t aId, char** aUri, char** aMetadata);
/**
 * Callback which runs when the ReadList action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionReadList
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aIdList
 * @param[out] aTrackList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1ReadList)(void* aPtr, uint32_t aVersion, const char* aIdList, char** aTrackList);
/**
 * Callback which runs when the Insert action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionInsert
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aAfterId
 * @param[in]  aUri
 * @param[in]  aMetadata
 * @param[out] aNewId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Insert)(void* aPtr, uint32_t aVersion, uint32_t aAfterId, const char* aUri, const char* aMetadata, uint32_t* aNewId);
/**
 * Callback which runs when the DeleteId action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionDeleteId
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1DeleteId)(void* aPtr, uint32_t aVersion, uint32_t aValue);
/**
 * Callback which runs when the DeleteAll action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionDeleteAll
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1DeleteAll)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the TracksMax action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionTracksMax
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1TracksMax)(void* aPtr, uint32_t aVersion, uint32_t* aValue);
/**
 * Callback which runs when the IdArray action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionIdArray
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aToken
 * @param[out] aArray
 * @param[out] aArrayLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1IdArray)(void* aPtr, uint32_t aVersion, uint32_t* aToken, char** aArray, uint32_t* aArrayLen);
/**
 * Callback which runs when the IdArrayChanged action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionIdArrayChanged
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aToken
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1IdArrayChanged)(void* aPtr, uint32_t aVersion, uint32_t aToken, uint32_t* aValue);
/**
 * Callback which runs when the ProtocolInfo action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgPlaylist1EnableActionProtocolInfo
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1ProtocolInfo)(void* aPtr, uint32_t aVersion, char** aValue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderAvOpenhomeOrgPlaylist1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 */
DllExport void DvProviderAvOpenhomeOrgPlaylist1Destroy(THandle aProvider);

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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionPlay(THandle aProvider, CallbackPlaylist1Play aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionPause(THandle aProvider, CallbackPlaylist1Pause aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionStop(THandle aProvider, CallbackPlaylist1Stop aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionNext(THandle aProvider, CallbackPlaylist1Next aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionPrevious(THandle aProvider, CallbackPlaylist1Previous aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionSetRepeat(THandle aProvider, CallbackPlaylist1SetRepeat aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionRepeat(THandle aProvider, CallbackPlaylist1Repeat aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionSetShuffle(THandle aProvider, CallbackPlaylist1SetShuffle aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionShuffle(THandle aProvider, CallbackPlaylist1Shuffle aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekSecondAbsolute(THandle aProvider, CallbackPlaylist1SeekSecondAbsolute aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekSecondRelative(THandle aProvider, CallbackPlaylist1SeekSecondRelative aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekId(THandle aProvider, CallbackPlaylist1SeekId aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionSeekIndex(THandle aProvider, CallbackPlaylist1SeekIndex aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionTransportState(THandle aProvider, CallbackPlaylist1TransportState aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionId(THandle aProvider, CallbackPlaylist1Id aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionRead(THandle aProvider, CallbackPlaylist1Read aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionReadList(THandle aProvider, CallbackPlaylist1ReadList aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionInsert(THandle aProvider, CallbackPlaylist1Insert aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionDeleteId(THandle aProvider, CallbackPlaylist1DeleteId aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionDeleteAll(THandle aProvider, CallbackPlaylist1DeleteAll aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionTracksMax(THandle aProvider, CallbackPlaylist1TracksMax aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionIdArray(THandle aProvider, CallbackPlaylist1IdArray aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionIdArrayChanged(THandle aProvider, CallbackPlaylist1IdArrayChanged aCallback, void* aPtr);
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
DllExport void DvProviderAvOpenhomeOrgPlaylist1EnableActionProtocolInfo(THandle aProvider, CallbackPlaylist1ProtocolInfo aCallback, void* aPtr);

/**
 * Set the value of the TransportState property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgPlaylist1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TransportState property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderAvOpenhomeOrgPlaylist1GetPropertyTransportState(THandle aProvider, char** aValue);
/**
 * Set the value of the Repeat property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgPlaylist1SetPropertyRepeat(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Repeat property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgPlaylist1GetPropertyRepeat(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Shuffle property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgPlaylist1SetPropertyShuffle(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Shuffle property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgPlaylist1GetPropertyShuffle(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Id property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgPlaylist1SetPropertyId(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Id property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgPlaylist1GetPropertyId(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the IdArray property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[in]  aValueLen  Size in bytes pointed to by aValue
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgPlaylist1SetPropertyIdArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged);
/**
 * Get a copy of the value of the IdArray property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 * @param[out] aValueLen  Size in bytes pointed to by aValue
 */
DllExport void DvProviderAvOpenhomeOrgPlaylist1GetPropertyIdArray(THandle aProvider, char** aValue, uint32_t* aValueLen);
/**
 * Set the value of the TracksMax property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgPlaylist1SetPropertyTracksMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TracksMax property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgPlaylist1GetPropertyTracksMax(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ProtocolInfo property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgPlaylist1SetPropertyProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProtocolInfo property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylist1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderAvOpenhomeOrgPlaylist1GetPropertyProtocolInfo(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGPLAYLIST1_C

