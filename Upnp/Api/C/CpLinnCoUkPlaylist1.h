/**
 * Proxy for linn.co.uk:Playlist:1
 */
#ifndef HEADER_LINNCOUKPLAYLIST1_C
#define HEADER_LINNCOUKPLAYLIST1_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyLinnCoUkPlaylist1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyLinnCoUkPlaylist1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 */
DllExport void CpProxyLinnCoUkPlaylist1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aaId
 * @param[out] aaUri
 * @param[out] aaMetaData
 */
DllExport void CpProxyLinnCoUkPlaylist1SyncRead(THandle aHandle, uint32_t aaId, char** aaUri, char** aaMetaData);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aaId
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1BeginRead(THandle aHandle, uint32_t aaId, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaUri
 * @param[out] aaMetaData
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPlaylist1EndRead(THandle aHandle, ZappHandleAsync aAsync, char** aaUri, char** aaMetaData);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aaIdList
 * @param[out] aaMetaDataList
 */
DllExport void CpProxyLinnCoUkPlaylist1SyncReadList(THandle aHandle, const char* aaIdList, char** aaMetaDataList);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aaIdList
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1BeginReadList(THandle aHandle, const char* aaIdList, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaMetaDataList
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPlaylist1EndReadList(THandle aHandle, ZappHandleAsync aAsync, char** aaMetaDataList);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aaAfterId
 * @param[in]  aaUri
 * @param[in]  aaMetaData
 * @param[out] aaNewId
 */
DllExport void CpProxyLinnCoUkPlaylist1SyncInsert(THandle aHandle, uint32_t aaAfterId, const char* aaUri, const char* aaMetaData, uint32_t* aaNewId);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aaAfterId
 * @param[in]  aaUri
 * @param[in]  aaMetaData
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1BeginInsert(THandle aHandle, uint32_t aaAfterId, const char* aaUri, const char* aaMetaData, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaNewId
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPlaylist1EndInsert(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaNewId);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aaId
 */
DllExport void CpProxyLinnCoUkPlaylist1SyncDelete(THandle aHandle, uint32_t aaId);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aaId
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1BeginDelete(THandle aHandle, uint32_t aaId, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPlaylist1EndDelete(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 */
DllExport void CpProxyLinnCoUkPlaylist1SyncDeleteAll(THandle aHandle);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1BeginDeleteAll(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPlaylist1EndDeleteAll(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aaRepeat
 */
DllExport void CpProxyLinnCoUkPlaylist1SyncSetRepeat(THandle aHandle, uint32_t aaRepeat);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aaRepeat
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1BeginSetRepeat(THandle aHandle, uint32_t aaRepeat, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPlaylist1EndSetRepeat(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[out] aaRepeat
 */
DllExport void CpProxyLinnCoUkPlaylist1SyncRepeat(THandle aHandle, uint32_t* aaRepeat);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1BeginRepeat(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaRepeat
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPlaylist1EndRepeat(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaRepeat);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aaShuffle
 */
DllExport void CpProxyLinnCoUkPlaylist1SyncSetShuffle(THandle aHandle, uint32_t aaShuffle);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aaShuffle
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1BeginSetShuffle(THandle aHandle, uint32_t aaShuffle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPlaylist1EndSetShuffle(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[out] aaShuffle
 */
DllExport void CpProxyLinnCoUkPlaylist1SyncShuffle(THandle aHandle, uint32_t* aaShuffle);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1BeginShuffle(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaShuffle
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPlaylist1EndShuffle(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaShuffle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[out] aaTracksMax
 */
DllExport void CpProxyLinnCoUkPlaylist1SyncTracksMax(THandle aHandle, uint32_t* aaTracksMax);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1BeginTracksMax(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaTracksMax
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPlaylist1EndTracksMax(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaTracksMax);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[out] aaIdArrayToken
 * @param[out] aaIdArray
 * @param[out] aaIdArrayLen
 */
DllExport void CpProxyLinnCoUkPlaylist1SyncIdArray(THandle aHandle, uint32_t* aaIdArrayToken, char** aaIdArray, uint32_t* aaIdArrayLen);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1BeginIdArray(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaIdArrayToken
 * @param[out] aaIdArray
 * @param[in]  aaIdArrayLen
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPlaylist1EndIdArray(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaIdArrayToken, char** aaIdArray, uint32_t* aaIdArrayLen);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aaIdArrayToken
 * @param[out] aaIdArrayChanged
 */
DllExport void CpProxyLinnCoUkPlaylist1SyncIdArrayChanged(THandle aHandle, uint32_t aaIdArrayToken, uint32_t* aaIdArrayChanged);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aaIdArrayToken
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1BeginIdArrayChanged(THandle aHandle, uint32_t aaIdArrayToken, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaIdArrayChanged
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPlaylist1EndIdArrayChanged(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaIdArrayChanged);
/**
 * Set a callback to be run when the IdArray state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkPlaylist1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1SetPropertyIdArrayChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Repeat state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkPlaylist1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1SetPropertyRepeatChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Shuffle state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkPlaylist1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1SetPropertyShuffleChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the TracksMax state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkPlaylist1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPlaylist1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPlaylist1SetPropertyTracksMaxChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the IdArray property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aIdArray
 * @param[out] aLen
 */
DllExport void CpProxyLinnCoUkPlaylist1PropertyIdArray(THandle aHandle, char** aIdArray, uint32_t* aLen);
/**
 * Query the value of the Repeat property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aRepeat
 */
DllExport void CpProxyLinnCoUkPlaylist1PropertyRepeat(THandle aHandle, uint32_t* aRepeat);
/**
 * Query the value of the Shuffle property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aShuffle
 */
DllExport void CpProxyLinnCoUkPlaylist1PropertyShuffle(THandle aHandle, uint32_t* aShuffle);
/**
 * Query the value of the TracksMax property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aTracksMax
 */
DllExport void CpProxyLinnCoUkPlaylist1PropertyTracksMax(THandle aHandle, uint32_t* aTracksMax);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_LINNCOUKPLAYLIST1_C

