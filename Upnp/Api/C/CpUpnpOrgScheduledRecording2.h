/**
 * Proxy for upnp.org:ScheduledRecording:2
 */
#ifndef HEADER_UPNPORGSCHEDULEDRECORDING2_C
#define HEADER_UPNPORGSCHEDULEDRECORDING2_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyUpnpOrgScheduledRecording2 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyUpnpOrgScheduledRecording2Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 */
DllExport void CpProxyUpnpOrgScheduledRecording2Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[out] aSortCaps
 * @param[out] aSortLevelCap
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncGetSortCapabilities(THandle aHandle, char** aSortCaps, uint32_t* aSortLevelCap);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginGetSortCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aSortCaps
 * @param[out] aSortLevelCap
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndGetSortCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aSortCaps, uint32_t* aSortLevelCap);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aDataTypeID
 * @param[out] aPropertyList
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncGetPropertyList(THandle aHandle, const char* aDataTypeID, char** aPropertyList);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aDataTypeID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginGetPropertyList(THandle aHandle, const char* aDataTypeID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aPropertyList
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndGetPropertyList(THandle aHandle, ZappHandleAsync aAsync, char** aPropertyList);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aDataTypeID
 * @param[in]  aFilter
 * @param[out] aPropertyInfo
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncGetAllowedValues(THandle aHandle, const char* aDataTypeID, const char* aFilter, char** aPropertyInfo);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aDataTypeID
 * @param[in]  aFilter
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginGetAllowedValues(THandle aHandle, const char* aDataTypeID, const char* aFilter, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aPropertyInfo
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndGetAllowedValues(THandle aHandle, ZappHandleAsync aAsync, char** aPropertyInfo);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[out] aId
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncGetStateUpdateID(THandle aHandle, uint32_t* aId);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginGetStateUpdateID(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aId
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndGetStateUpdateID(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aId);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aFilter
 * @param[in]  aStartingIndex
 * @param[in]  aRequestedCount
 * @param[in]  aSortCriteria
 * @param[out] aResult
 * @param[out] aNumberReturned
 * @param[out] aTotalMatches
 * @param[out] aUpdateID
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncBrowseRecordSchedules(THandle aHandle, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aFilter
 * @param[in]  aStartingIndex
 * @param[in]  aRequestedCount
 * @param[in]  aSortCriteria
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginBrowseRecordSchedules(THandle aHandle, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 * @param[out] aNumberReturned
 * @param[out] aTotalMatches
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndBrowseRecordSchedules(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aFilter
 * @param[in]  aStartingIndex
 * @param[in]  aRequestedCount
 * @param[in]  aSortCriteria
 * @param[out] aResult
 * @param[out] aNumberReturned
 * @param[out] aTotalMatches
 * @param[out] aUpdateID
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncBrowseRecordTasks(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aFilter
 * @param[in]  aStartingIndex
 * @param[in]  aRequestedCount
 * @param[in]  aSortCriteria
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginBrowseRecordTasks(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 * @param[out] aNumberReturned
 * @param[out] aTotalMatches
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndBrowseRecordTasks(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aElements
 * @param[out] aRecordScheduleID
 * @param[out] aResult
 * @param[out] aUpdateID
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncCreateRecordSchedule(THandle aHandle, const char* aElements, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aElements
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginCreateRecordSchedule(THandle aHandle, const char* aElements, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aRecordScheduleID
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndCreateRecordSchedule(THandle aHandle, ZappHandleAsync aAsync, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordScheduleID
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncDeleteRecordSchedule(THandle aHandle, const char* aRecordScheduleID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginDeleteRecordSchedule(THandle aHandle, const char* aRecordScheduleID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndDeleteRecordSchedule(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aFilter
 * @param[out] aResult
 * @param[out] aUpdateID
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncGetRecordSchedule(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, char** aResult, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aFilter
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginGetRecordSchedule(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndGetRecordSchedule(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aUpdateID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordScheduleID
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncEnableRecordSchedule(THandle aHandle, const char* aRecordScheduleID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginEnableRecordSchedule(THandle aHandle, const char* aRecordScheduleID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndEnableRecordSchedule(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordScheduleID
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncDisableRecordSchedule(THandle aHandle, const char* aRecordScheduleID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginDisableRecordSchedule(THandle aHandle, const char* aRecordScheduleID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndDisableRecordSchedule(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordTaskID
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncDeleteRecordTask(THandle aHandle, const char* aRecordTaskID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordTaskID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginDeleteRecordTask(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndDeleteRecordTask(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordTaskID
 * @param[in]  aFilter
 * @param[out] aResult
 * @param[out] aUpdateID
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncGetRecordTask(THandle aHandle, const char* aRecordTaskID, const char* aFilter, char** aResult, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordTaskID
 * @param[in]  aFilter
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginGetRecordTask(THandle aHandle, const char* aRecordTaskID, const char* aFilter, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndGetRecordTask(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aUpdateID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordTaskID
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncEnableRecordTask(THandle aHandle, const char* aRecordTaskID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordTaskID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginEnableRecordTask(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndEnableRecordTask(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordTaskID
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncDisableRecordTask(THandle aHandle, const char* aRecordTaskID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordTaskID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginDisableRecordTask(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndDisableRecordTask(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordTaskID
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncResetRecordTask(THandle aHandle, const char* aRecordTaskID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordTaskID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginResetRecordTask(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndResetRecordTask(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordScheduleID
 * @param[out] aRecordScheduleConflictIDList
 * @param[out] aUpdateID
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncGetRecordScheduleConflicts(THandle aHandle, const char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginGetRecordScheduleConflicts(THandle aHandle, const char* aRecordScheduleID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aRecordScheduleConflictIDList
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndGetRecordScheduleConflicts(THandle aHandle, ZappHandleAsync aAsync, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordTaskID
 * @param[out] aRecordTaskConflictIDList
 * @param[out] aUpdateID
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SyncGetRecordTaskConflicts(THandle aHandle, const char* aRecordTaskID, char** aRecordTaskConflictIDList, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aRecordTaskID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2BeginGetRecordTaskConflicts(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aRecordTaskConflictIDList
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgScheduledRecording2EndGetRecordTaskConflicts(THandle aHandle, ZappHandleAsync aAsync, char** aRecordTaskConflictIDList, uint32_t* aUpdateID);
/**
 * Set a callback to be run when the LastChange state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyUpnpOrgScheduledRecording2 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording2Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgScheduledRecording2SetPropertyLastChangeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the LastChange property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aLastChange
 */
DllExport void CpProxyUpnpOrgScheduledRecording2PropertyLastChange(THandle aHandle, char** aLastChange);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_UPNPORGSCHEDULEDRECORDING2_C

