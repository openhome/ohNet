/**
 * Proxy for upnp.org:ScheduledRecording:1
 */
#ifndef HEADER_UPNPORGSCHEDULEDRECORDING1_C
#define HEADER_UPNPORGSCHEDULEDRECORDING1_C

#include <OpenHome/OsTypes.h>
#include <OpenHome/Defines.h>
#include <OpenHome/Net/C/Async.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CpProxyUpnpOrgScheduledRecording1
 * @ingroup Proxies
 * @{
 */

/**
 * Constructor.
 * Creates an instance of CpProxyUpnpOrgScheduledRecording1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle STDCALL CpProxyUpnpOrgScheduledRecording1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[out] aSortCaps
 * @param[out] aSortLevelCap
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetSortCapabilities(THandle aHandle, char** aSortCaps, uint32_t* aSortLevelCap);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetSortCapabilities(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aSortCaps
 * @param[out] aSortLevelCap
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetSortCapabilities(THandle aHandle, OhNetHandleAsync aAsync, char** aSortCaps, uint32_t* aSortLevelCap);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aDataTypeID
 * @param[out] aPropertyList
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetPropertyList(THandle aHandle, const char* aDataTypeID, char** aPropertyList);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aDataTypeID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetPropertyList(THandle aHandle, const char* aDataTypeID, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aPropertyList
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetPropertyList(THandle aHandle, OhNetHandleAsync aAsync, char** aPropertyList);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aDataTypeID
 * @param[in]  aFilter
 * @param[out] aPropertyInfo
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetAllowedValues(THandle aHandle, const char* aDataTypeID, const char* aFilter, char** aPropertyInfo);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aDataTypeID
 * @param[in]  aFilter
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetAllowedValues(THandle aHandle, const char* aDataTypeID, const char* aFilter, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aPropertyInfo
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetAllowedValues(THandle aHandle, OhNetHandleAsync aAsync, char** aPropertyInfo);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[out] aId
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetStateUpdateID(THandle aHandle, uint32_t* aId);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetStateUpdateID(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aId
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetStateUpdateID(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aId);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aFilter
 * @param[in]  aStartingIndex
 * @param[in]  aRequestedCount
 * @param[in]  aSortCriteria
 * @param[out] aResult
 * @param[out] aNumberReturned
 * @param[out] aTotalMatches
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncBrowseRecordSchedules(THandle aHandle, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aFilter
 * @param[in]  aStartingIndex
 * @param[in]  aRequestedCount
 * @param[in]  aSortCriteria
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginBrowseRecordSchedules(THandle aHandle, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 * @param[out] aNumberReturned
 * @param[out] aTotalMatches
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndBrowseRecordSchedules(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aFilter
 * @param[in]  aStartingIndex
 * @param[in]  aRequestedCount
 * @param[in]  aSortCriteria
 * @param[out] aResult
 * @param[out] aNumberReturned
 * @param[out] aTotalMatches
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncBrowseRecordTasks(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aFilter
 * @param[in]  aStartingIndex
 * @param[in]  aRequestedCount
 * @param[in]  aSortCriteria
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginBrowseRecordTasks(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 * @param[out] aNumberReturned
 * @param[out] aTotalMatches
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndBrowseRecordTasks(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aElements
 * @param[out] aRecordScheduleID
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncCreateRecordSchedule(THandle aHandle, const char* aElements, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aElements
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginCreateRecordSchedule(THandle aHandle, const char* aElements, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aRecordScheduleID
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndCreateRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordScheduleID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncDeleteRecordSchedule(THandle aHandle, const char* aRecordScheduleID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginDeleteRecordSchedule(THandle aHandle, const char* aRecordScheduleID, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndDeleteRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aFilter
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetRecordSchedule(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, char** aResult, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aFilter
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetRecordSchedule(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aUpdateID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordScheduleID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncEnableRecordSchedule(THandle aHandle, const char* aRecordScheduleID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginEnableRecordSchedule(THandle aHandle, const char* aRecordScheduleID, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndEnableRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordScheduleID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncDisableRecordSchedule(THandle aHandle, const char* aRecordScheduleID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginDisableRecordSchedule(THandle aHandle, const char* aRecordScheduleID, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndDisableRecordSchedule(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncDeleteRecordTask(THandle aHandle, const char* aRecordTaskID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordTaskID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginDeleteRecordTask(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndDeleteRecordTask(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordTaskID
 * @param[in]  aFilter
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetRecordTask(THandle aHandle, const char* aRecordTaskID, const char* aFilter, char** aResult, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordTaskID
 * @param[in]  aFilter
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetRecordTask(THandle aHandle, const char* aRecordTaskID, const char* aFilter, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetRecordTask(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aUpdateID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncEnableRecordTask(THandle aHandle, const char* aRecordTaskID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordTaskID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginEnableRecordTask(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndEnableRecordTask(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncDisableRecordTask(THandle aHandle, const char* aRecordTaskID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordTaskID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginDisableRecordTask(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndDisableRecordTask(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncResetRecordTask(THandle aHandle, const char* aRecordTaskID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordTaskID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginResetRecordTask(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndResetRecordTask(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordScheduleID
 * @param[out] aRecordScheduleConflictIDList
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetRecordScheduleConflicts(THandle aHandle, const char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordScheduleID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetRecordScheduleConflicts(THandle aHandle, const char* aRecordScheduleID, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aRecordScheduleConflictIDList
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetRecordScheduleConflicts(THandle aHandle, OhNetHandleAsync aAsync, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordTaskID
 * @param[out] aRecordTaskConflictIDList
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1SyncGetRecordTaskConflicts(THandle aHandle, const char* aRecordTaskID, char** aRecordTaskConflictIDList, uint32_t* aUpdateID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aRecordTaskID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1BeginGetRecordTaskConflicts(THandle aHandle, const char* aRecordTaskID, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aRecordTaskConflictIDList
 * @param[out] aUpdateID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyUpnpOrgScheduledRecording1EndGetRecordTaskConflicts(THandle aHandle, OhNetHandleAsync aAsync, char** aRecordTaskConflictIDList, uint32_t* aUpdateID);
/**
 * Set a callback to be run when the LastChange state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyUpnpOrgScheduledRecording1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1SetPropertyLastChangeChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);

/**
 * Query the value of the LastChange property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgScheduledRecording1Create
 * @param[out] aLastChange
 */
DllExport void STDCALL CpProxyUpnpOrgScheduledRecording1PropertyLastChange(THandle aHandle, char** aLastChange);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_UPNPORGSCHEDULEDRECORDING1_C

