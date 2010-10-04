/**
 * Proxy for upnp.org:ContentDirectory:2
 */
#ifndef HEADER_UPNPORGCONTENTDIRECTORY2_C
#define HEADER_UPNPORGCONTENTDIRECTORY2_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyUpnpOrgContentDirectory2 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyUpnpOrgContentDirectory2Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 */
DllExport void CpProxyUpnpOrgContentDirectory2Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[out] aSearchCaps
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncGetSearchCapabilities(THandle aHandle, char** aSearchCaps);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginGetSearchCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aSearchCaps
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndGetSearchCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aSearchCaps);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[out] aSortCaps
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncGetSortCapabilities(THandle aHandle, char** aSortCaps);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginGetSortCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aSortCaps
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndGetSortCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aSortCaps);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[out] aSortExtensionCaps
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncGetSortExtensionCapabilities(THandle aHandle, char** aSortExtensionCaps);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginGetSortExtensionCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aSortExtensionCaps
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndGetSortExtensionCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aSortExtensionCaps);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[out] aFeatureList
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncGetFeatureList(THandle aHandle, char** aFeatureList);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginGetFeatureList(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aFeatureList
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndGetFeatureList(THandle aHandle, ZappHandleAsync aAsync, char** aFeatureList);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[out] aId
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncGetSystemUpdateID(THandle aHandle, uint32_t* aId);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginGetSystemUpdateID(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aId
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndGetSystemUpdateID(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aId);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aObjectID
 * @param[in]  aBrowseFlag
 * @param[in]  aFilter
 * @param[in]  aStartingIndex
 * @param[in]  aRequestedCount
 * @param[in]  aSortCriteria
 * @param[out] aResult
 * @param[out] aNumberReturned
 * @param[out] aTotalMatches
 * @param[out] aUpdateID
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncBrowse(THandle aHandle, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aObjectID
 * @param[in]  aBrowseFlag
 * @param[in]  aFilter
 * @param[in]  aStartingIndex
 * @param[in]  aRequestedCount
 * @param[in]  aSortCriteria
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginBrowse(THandle aHandle, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 * @param[out] aNumberReturned
 * @param[out] aTotalMatches
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndBrowse(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aContainerID
 * @param[in]  aSearchCriteria
 * @param[in]  aFilter
 * @param[in]  aStartingIndex
 * @param[in]  aRequestedCount
 * @param[in]  aSortCriteria
 * @param[out] aResult
 * @param[out] aNumberReturned
 * @param[out] aTotalMatches
 * @param[out] aUpdateID
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncSearch(THandle aHandle, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aContainerID
 * @param[in]  aSearchCriteria
 * @param[in]  aFilter
 * @param[in]  aStartingIndex
 * @param[in]  aRequestedCount
 * @param[in]  aSortCriteria
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginSearch(THandle aHandle, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 * @param[out] aNumberReturned
 * @param[out] aTotalMatches
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndSearch(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aContainerID
 * @param[in]  aElements
 * @param[out] aObjectID
 * @param[out] aResult
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncCreateObject(THandle aHandle, const char* aContainerID, const char* aElements, char** aObjectID, char** aResult);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aContainerID
 * @param[in]  aElements
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginCreateObject(THandle aHandle, const char* aContainerID, const char* aElements, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aObjectID
 * @param[out] aResult
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndCreateObject(THandle aHandle, ZappHandleAsync aAsync, char** aObjectID, char** aResult);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aObjectID
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncDestroyObject(THandle aHandle, const char* aObjectID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aObjectID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginDestroyObject(THandle aHandle, const char* aObjectID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndDestroyObject(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aObjectID
 * @param[in]  aCurrentTagValue
 * @param[in]  aNewTagValue
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncUpdateObject(THandle aHandle, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aObjectID
 * @param[in]  aCurrentTagValue
 * @param[in]  aNewTagValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginUpdateObject(THandle aHandle, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndUpdateObject(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aObjectID
 * @param[in]  aNewParentID
 * @param[out] aNewObjectID
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncMoveObject(THandle aHandle, const char* aObjectID, const char* aNewParentID, char** aNewObjectID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aObjectID
 * @param[in]  aNewParentID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginMoveObject(THandle aHandle, const char* aObjectID, const char* aNewParentID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aNewObjectID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndMoveObject(THandle aHandle, ZappHandleAsync aAsync, char** aNewObjectID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aSourceURI
 * @param[in]  aDestinationURI
 * @param[out] aTransferID
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncImportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aSourceURI
 * @param[in]  aDestinationURI
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginImportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aTransferID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndImportResource(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aTransferID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aSourceURI
 * @param[in]  aDestinationURI
 * @param[out] aTransferID
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncExportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aSourceURI
 * @param[in]  aDestinationURI
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginExportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aTransferID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndExportResource(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aTransferID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aResourceURI
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncDeleteResource(THandle aHandle, const char* aResourceURI);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aResourceURI
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginDeleteResource(THandle aHandle, const char* aResourceURI, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndDeleteResource(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aTransferID
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncStopTransferResource(THandle aHandle, uint32_t aTransferID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aTransferID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginStopTransferResource(THandle aHandle, uint32_t aTransferID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndStopTransferResource(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aTransferID
 * @param[out] aTransferStatus
 * @param[out] aTransferLength
 * @param[out] aTransferTotal
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncGetTransferProgress(THandle aHandle, uint32_t aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aTransferID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginGetTransferProgress(THandle aHandle, uint32_t aTransferID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aTransferStatus
 * @param[out] aTransferLength
 * @param[out] aTransferTotal
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndGetTransferProgress(THandle aHandle, ZappHandleAsync aAsync, char** aTransferStatus, char** aTransferLength, char** aTransferTotal);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aContainerID
 * @param[in]  aObjectID
 * @param[out] aNewID
 */
DllExport void CpProxyUpnpOrgContentDirectory2SyncCreateReference(THandle aHandle, const char* aContainerID, const char* aObjectID, char** aNewID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aContainerID
 * @param[in]  aObjectID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2BeginCreateReference(THandle aHandle, const char* aContainerID, const char* aObjectID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aNewID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgContentDirectory2EndCreateReference(THandle aHandle, ZappHandleAsync aAsync, char** aNewID);
/**
 * Set a callback to be run when the SystemUpdateID state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyUpnpOrgContentDirectory2 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2SetPropertySystemUpdateIDChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ContainerUpdateIDs state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyUpnpOrgContentDirectory2 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2SetPropertyContainerUpdateIDsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the TransferIDs state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyUpnpOrgContentDirectory2 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgContentDirectory2Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgContentDirectory2SetPropertyTransferIDsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the SystemUpdateID property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aSystemUpdateID
 */
DllExport void CpProxyUpnpOrgContentDirectory2PropertySystemUpdateID(THandle aHandle, uint32_t* aSystemUpdateID);
/**
 * Query the value of the ContainerUpdateIDs property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aContainerUpdateIDs
 */
DllExport void CpProxyUpnpOrgContentDirectory2PropertyContainerUpdateIDs(THandle aHandle, char** aContainerUpdateIDs);
/**
 * Query the value of the TransferIDs property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aTransferIDs
 */
DllExport void CpProxyUpnpOrgContentDirectory2PropertyTransferIDs(THandle aHandle, char** aTransferIDs);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_UPNPORGCONTENTDIRECTORY2_C

