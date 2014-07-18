/**
 * Provider for the av.openhome.org:PlaylistManager:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGPLAYLISTMANAGER1_C
#define HEADER_DVAVOPENHOMEORGPLAYLISTMANAGER1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderAvOpenhomeOrgPlaylistManager1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Metadata action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionMetadata
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aMetadata
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1Metadata)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aMetadata);
/**
 * Callback which runs when the ImagesXml action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionImagesXml
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aImagesXml
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1ImagesXml)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aImagesXml);
/**
 * Callback which runs when the PlaylistReadArray action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistReadArray
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aId
 * @param[out] aArray
 * @param[out] aArrayLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1PlaylistReadArray)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aId, char** aArray, uint32_t* aArrayLen);
/**
 * Callback which runs when the PlaylistReadList action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistReadList
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aIdList
 * @param[out] aPlaylistList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1PlaylistReadList)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aIdList, char** aPlaylistList);
/**
 * Callback which runs when the PlaylistRead action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistRead
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aId
 * @param[out] aName
 * @param[out] aDescription
 * @param[out] aImageId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1PlaylistRead)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aId, char** aName, char** aDescription, uint32_t* aImageId);
/**
 * Callback which runs when the PlaylistSetName action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistSetName
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aId
 * @param[in]  aName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1PlaylistSetName)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aId, const char* aName);
/**
 * Callback which runs when the PlaylistSetDescription action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistSetDescription
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aId
 * @param[in]  aDescription
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1PlaylistSetDescription)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aId, const char* aDescription);
/**
 * Callback which runs when the PlaylistSetImageId action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistSetImageId
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aId
 * @param[in]  aImageId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1PlaylistSetImageId)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aId, uint32_t aImageId);
/**
 * Callback which runs when the PlaylistInsert action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistInsert
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aAfterId
 * @param[in]  aName
 * @param[in]  aDescription
 * @param[in]  aImageId
 * @param[out] aNewId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1PlaylistInsert)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aAfterId, const char* aName, const char* aDescription, uint32_t aImageId, uint32_t* aNewId);
/**
 * Callback which runs when the PlaylistDeleteId action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistDeleteId
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1PlaylistDeleteId)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue);
/**
 * Callback which runs when the PlaylistMove action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistMove
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aId
 * @param[in]  aAfterId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1PlaylistMove)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aId, uint32_t aAfterId);
/**
 * Callback which runs when the PlaylistsMax action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistsMax
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1PlaylistsMax)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);
/**
 * Callback which runs when the TracksMax action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionTracksMax
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1TracksMax)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);
/**
 * Callback which runs when the PlaylistArrays action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistArrays
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aToken
 * @param[out] aIdArray
 * @param[out] aIdArrayLen
 * @param[out] aTokenArray
 * @param[out] aTokenArrayLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1PlaylistArrays)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aToken, char** aIdArray, uint32_t* aIdArrayLen, char** aTokenArray, uint32_t* aTokenArrayLen);
/**
 * Callback which runs when the PlaylistArraysChanged action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistArraysChanged
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aToken
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1PlaylistArraysChanged)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aToken, uint32_t* aValue);
/**
 * Callback which runs when the Read action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionRead
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aId
 * @param[in]  aTrackId
 * @param[out] aMetadata
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1Read)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aId, uint32_t aTrackId, char** aMetadata);
/**
 * Callback which runs when the ReadList action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionReadList
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aId
 * @param[in]  aTrackIdList
 * @param[out] aTrackList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1ReadList)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aId, const char* aTrackIdList, char** aTrackList);
/**
 * Callback which runs when the Insert action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionInsert
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aId
 * @param[in]  aAfterTrackId
 * @param[in]  aMetadata
 * @param[out] aNewTrackId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1Insert)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aId, uint32_t aAfterTrackId, const char* aMetadata, uint32_t* aNewTrackId);
/**
 * Callback which runs when the DeleteId action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionDeleteId
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aId
 * @param[in]  aTrackId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1DeleteId)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aId, uint32_t aTrackId);
/**
 * Callback which runs when the DeleteAll action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgPlaylistManager1EnableActionDeleteAll
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackPlaylistManager1DeleteAll)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aId);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderAvOpenhomeOrgPlaylistManager1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1Destroy(THandle aProvider);

/**
 * Enable the Metadata property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyMetadata(THandle aProvider);
/**
 * Enable the ImagesXml property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyImagesXml(THandle aProvider);
/**
 * Enable the IdArray property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyIdArray(THandle aProvider);
/**
 * Enable the TokenArray property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyTokenArray(THandle aProvider);
/**
 * Enable the PlaylistsMax property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyPlaylistsMax(THandle aProvider);
/**
 * Enable the TracksMax property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyTracksMax(THandle aProvider);

/**
 * Register a callback for the action Metadata
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionMetadata(THandle aProvider, CallbackPlaylistManager1Metadata aCallback, void* aPtr);
/**
 * Register a callback for the action ImagesXml
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionImagesXml(THandle aProvider, CallbackPlaylistManager1ImagesXml aCallback, void* aPtr);
/**
 * Register a callback for the action PlaylistReadArray
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistReadArray(THandle aProvider, CallbackPlaylistManager1PlaylistReadArray aCallback, void* aPtr);
/**
 * Register a callback for the action PlaylistReadList
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistReadList(THandle aProvider, CallbackPlaylistManager1PlaylistReadList aCallback, void* aPtr);
/**
 * Register a callback for the action PlaylistRead
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistRead(THandle aProvider, CallbackPlaylistManager1PlaylistRead aCallback, void* aPtr);
/**
 * Register a callback for the action PlaylistSetName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistSetName(THandle aProvider, CallbackPlaylistManager1PlaylistSetName aCallback, void* aPtr);
/**
 * Register a callback for the action PlaylistSetDescription
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistSetDescription(THandle aProvider, CallbackPlaylistManager1PlaylistSetDescription aCallback, void* aPtr);
/**
 * Register a callback for the action PlaylistSetImageId
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistSetImageId(THandle aProvider, CallbackPlaylistManager1PlaylistSetImageId aCallback, void* aPtr);
/**
 * Register a callback for the action PlaylistInsert
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistInsert(THandle aProvider, CallbackPlaylistManager1PlaylistInsert aCallback, void* aPtr);
/**
 * Register a callback for the action PlaylistDeleteId
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistDeleteId(THandle aProvider, CallbackPlaylistManager1PlaylistDeleteId aCallback, void* aPtr);
/**
 * Register a callback for the action PlaylistMove
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistMove(THandle aProvider, CallbackPlaylistManager1PlaylistMove aCallback, void* aPtr);
/**
 * Register a callback for the action PlaylistsMax
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistsMax(THandle aProvider, CallbackPlaylistManager1PlaylistsMax aCallback, void* aPtr);
/**
 * Register a callback for the action TracksMax
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionTracksMax(THandle aProvider, CallbackPlaylistManager1TracksMax aCallback, void* aPtr);
/**
 * Register a callback for the action PlaylistArrays
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistArrays(THandle aProvider, CallbackPlaylistManager1PlaylistArrays aCallback, void* aPtr);
/**
 * Register a callback for the action PlaylistArraysChanged
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistArraysChanged(THandle aProvider, CallbackPlaylistManager1PlaylistArraysChanged aCallback, void* aPtr);
/**
 * Register a callback for the action Read
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionRead(THandle aProvider, CallbackPlaylistManager1Read aCallback, void* aPtr);
/**
 * Register a callback for the action ReadList
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionReadList(THandle aProvider, CallbackPlaylistManager1ReadList aCallback, void* aPtr);
/**
 * Register a callback for the action Insert
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionInsert(THandle aProvider, CallbackPlaylistManager1Insert aCallback, void* aPtr);
/**
 * Register a callback for the action DeleteId
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionDeleteId(THandle aProvider, CallbackPlaylistManager1DeleteId aCallback, void* aPtr);
/**
 * Register a callback for the action DeleteAll
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionDeleteAll(THandle aProvider, CallbackPlaylistManager1DeleteAll aCallback, void* aPtr);

/**
 * Set the value of the Metadata property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyMetadata has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgPlaylistManager1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Metadata property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyMetadata has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1GetPropertyMetadata(THandle aProvider, char** aValue);
/**
 * Set the value of the ImagesXml property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyImagesXml has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgPlaylistManager1SetPropertyImagesXml(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ImagesXml property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyImagesXml has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1GetPropertyImagesXml(THandle aProvider, char** aValue);
/**
 * Set the value of the IdArray property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyIdArray has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[in]  aValueLen  Size in bytes pointed to by aValue
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgPlaylistManager1SetPropertyIdArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged);
/**
 * Get a copy of the value of the IdArray property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyIdArray has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 * @param[out] aValueLen  Size in bytes pointed to by aValue
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1GetPropertyIdArray(THandle aProvider, char** aValue, uint32_t* aValueLen);
/**
 * Set the value of the TokenArray property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyTokenArray has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[in]  aValueLen  Size in bytes pointed to by aValue
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgPlaylistManager1SetPropertyTokenArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged);
/**
 * Get a copy of the value of the TokenArray property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyTokenArray has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 * @param[out] aValueLen  Size in bytes pointed to by aValue
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1GetPropertyTokenArray(THandle aProvider, char** aValue, uint32_t* aValueLen);
/**
 * Set the value of the PlaylistsMax property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyPlaylistsMax has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgPlaylistManager1SetPropertyPlaylistsMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the PlaylistsMax property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyPlaylistsMax has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1GetPropertyPlaylistsMax(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the TracksMax property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyTracksMax has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgPlaylistManager1SetPropertyTracksMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TracksMax property
 *
 * Can only be called if DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyTracksMax has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgPlaylistManager1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1GetPropertyTracksMax(THandle aProvider, uint32_t* aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGPLAYLISTMANAGER1_C

