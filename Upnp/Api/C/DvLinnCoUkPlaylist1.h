/**
 * Provider for the linn.co.uk:Playlist:1 UPnP service
 */
#ifndef HEADER_DVLINNCOUKPLAYLIST1_C
#define HEADER_DVLINNCOUKPLAYLIST1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderLinnCoUkPlaylist1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Read action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPlaylist1EnableActionRead
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaId
 * @param[out] aaUri
 * @param[out] aaMetaData
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Read)(void* aPtr, uint32_t aVersion, uint32_t aaId, char** aaUri, char** aaMetaData);
/**
 * Callback which runs when the ReadList action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPlaylist1EnableActionReadList
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaIdList
 * @param[out] aaMetaDataList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1ReadList)(void* aPtr, uint32_t aVersion, const char* aaIdList, char** aaMetaDataList);
/**
 * Callback which runs when the Insert action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPlaylist1EnableActionInsert
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaAfterId
 * @param[in]  aaUri
 * @param[in]  aaMetaData
 * @param[out] aaNewId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Insert)(void* aPtr, uint32_t aVersion, uint32_t aaAfterId, const char* aaUri, const char* aaMetaData, uint32_t* aaNewId);
/**
 * Callback which runs when the Delete action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPlaylist1EnableActionDelete
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Delete)(void* aPtr, uint32_t aVersion, uint32_t aaId);
/**
 * Callback which runs when the DeleteAll action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPlaylist1EnableActionDeleteAll
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1DeleteAll)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the SetRepeat action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPlaylist1EnableActionSetRepeat
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaRepeat
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1SetRepeat)(void* aPtr, uint32_t aVersion, uint32_t aaRepeat);
/**
 * Callback which runs when the Repeat action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPlaylist1EnableActionRepeat
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaRepeat
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Repeat)(void* aPtr, uint32_t aVersion, uint32_t* aaRepeat);
/**
 * Callback which runs when the SetShuffle action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPlaylist1EnableActionSetShuffle
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaShuffle
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1SetShuffle)(void* aPtr, uint32_t aVersion, uint32_t aaShuffle);
/**
 * Callback which runs when the Shuffle action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPlaylist1EnableActionShuffle
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaShuffle
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1Shuffle)(void* aPtr, uint32_t aVersion, uint32_t* aaShuffle);
/**
 * Callback which runs when the TracksMax action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPlaylist1EnableActionTracksMax
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaTracksMax
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1TracksMax)(void* aPtr, uint32_t aVersion, uint32_t* aaTracksMax);
/**
 * Callback which runs when the IdArray action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPlaylist1EnableActionIdArray
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaIdArrayToken
 * @param[out] aaIdArray
 * @param[out] aaIdArrayLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1IdArray)(void* aPtr, uint32_t aVersion, uint32_t* aaIdArrayToken, char** aaIdArray, uint32_t* aaIdArrayLen);
/**
 * Callback which runs when the IdArrayChanged action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPlaylist1EnableActionIdArrayChanged
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaIdArrayToken
 * @param[out] aaIdArrayChanged
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPlaylist1IdArrayChanged)(void* aPtr, uint32_t aVersion, uint32_t aaIdArrayToken, uint32_t* aaIdArrayChanged);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkPlaylist1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 */
DllExport void DvProviderLinnCoUkPlaylist1Destroy(THandle aProvider);

/**
 * Register a callback for the action Read
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPlaylist1EnableActionRead(THandle aProvider, CallbackPlaylist1Read aCallback, void* aPtr);
/**
 * Register a callback for the action ReadList
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPlaylist1EnableActionReadList(THandle aProvider, CallbackPlaylist1ReadList aCallback, void* aPtr);
/**
 * Register a callback for the action Insert
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPlaylist1EnableActionInsert(THandle aProvider, CallbackPlaylist1Insert aCallback, void* aPtr);
/**
 * Register a callback for the action Delete
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPlaylist1EnableActionDelete(THandle aProvider, CallbackPlaylist1Delete aCallback, void* aPtr);
/**
 * Register a callback for the action DeleteAll
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPlaylist1EnableActionDeleteAll(THandle aProvider, CallbackPlaylist1DeleteAll aCallback, void* aPtr);
/**
 * Register a callback for the action SetRepeat
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPlaylist1EnableActionSetRepeat(THandle aProvider, CallbackPlaylist1SetRepeat aCallback, void* aPtr);
/**
 * Register a callback for the action Repeat
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPlaylist1EnableActionRepeat(THandle aProvider, CallbackPlaylist1Repeat aCallback, void* aPtr);
/**
 * Register a callback for the action SetShuffle
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPlaylist1EnableActionSetShuffle(THandle aProvider, CallbackPlaylist1SetShuffle aCallback, void* aPtr);
/**
 * Register a callback for the action Shuffle
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPlaylist1EnableActionShuffle(THandle aProvider, CallbackPlaylist1Shuffle aCallback, void* aPtr);
/**
 * Register a callback for the action TracksMax
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPlaylist1EnableActionTracksMax(THandle aProvider, CallbackPlaylist1TracksMax aCallback, void* aPtr);
/**
 * Register a callback for the action IdArray
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPlaylist1EnableActionIdArray(THandle aProvider, CallbackPlaylist1IdArray aCallback, void* aPtr);
/**
 * Register a callback for the action IdArrayChanged
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPlaylist1EnableActionIdArrayChanged(THandle aProvider, CallbackPlaylist1IdArrayChanged aCallback, void* aPtr);

/**
 * Set the value of the IdArray property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[in]  aValueLen  Size in bytes pointed to by aValue
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkPlaylist1SetPropertyIdArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged);
/**
 * Get a copy of the value of the IdArray property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 * @param[out] aValueLen  Size in bytes pointed to by aValue
 */
DllExport void DvProviderLinnCoUkPlaylist1GetPropertyIdArray(THandle aProvider, char** aValue, uint32_t* aValueLen);
/**
 * Set the value of the Repeat property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkPlaylist1SetPropertyRepeat(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Repeat property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkPlaylist1GetPropertyRepeat(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Shuffle property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkPlaylist1SetPropertyShuffle(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Shuffle property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkPlaylist1GetPropertyShuffle(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the TracksMax property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkPlaylist1SetPropertyTracksMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TracksMax property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPlaylist1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkPlaylist1GetPropertyTracksMax(THandle aProvider, uint32_t* aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPLAYLIST1_C

