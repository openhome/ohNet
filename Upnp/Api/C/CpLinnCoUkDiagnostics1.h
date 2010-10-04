/**
 * Proxy for linn.co.uk:Diagnostics:1
 */
#ifndef HEADER_LINNCOUKDIAGNOSTICS1_C
#define HEADER_LINNCOUKDIAGNOSTICS1_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyLinnCoUkDiagnostics1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyLinnCoUkDiagnostics1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 */
DllExport void CpProxyLinnCoUkDiagnostics1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aaIn
 * @param[out] aaOut
 */
DllExport void CpProxyLinnCoUkDiagnostics1SyncEcho(THandle aHandle, const char* aaIn, char** aaOut);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aaIn
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkDiagnostics1BeginEcho(THandle aHandle, const char* aaIn, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaOut
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkDiagnostics1EndEcho(THandle aHandle, ZappHandleAsync aAsync, char** aaOut);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[out] aaElfFile
 */
DllExport void CpProxyLinnCoUkDiagnostics1SyncElfFile(THandle aHandle, char** aaElfFile);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkDiagnostics1BeginElfFile(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaElfFile
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkDiagnostics1EndElfFile(THandle aHandle, ZappHandleAsync aAsync, char** aaElfFile);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[out] aaElfFileFingerprint
 */
DllExport void CpProxyLinnCoUkDiagnostics1SyncElfFingerprint(THandle aHandle, char** aaElfFileFingerprint);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkDiagnostics1BeginElfFingerprint(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaElfFileFingerprint
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkDiagnostics1EndElfFingerprint(THandle aHandle, ZappHandleAsync aAsync, char** aaElfFileFingerprint);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[out] aaCrashDataStatus
 */
DllExport void CpProxyLinnCoUkDiagnostics1SyncCrashDataStatus(THandle aHandle, char** aaCrashDataStatus);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkDiagnostics1BeginCrashDataStatus(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaCrashDataStatus
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkDiagnostics1EndCrashDataStatus(THandle aHandle, ZappHandleAsync aAsync, char** aaCrashDataStatus);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[out] aaCrashData
 * @param[out] aaCrashDataLen
 */
DllExport void CpProxyLinnCoUkDiagnostics1SyncCrashDataFetch(THandle aHandle, char** aaCrashData, uint32_t* aaCrashDataLen);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkDiagnostics1BeginCrashDataFetch(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaCrashData
 * @param[in]  aaCrashDataLen
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkDiagnostics1EndCrashDataFetch(THandle aHandle, ZappHandleAsync aAsync, char** aaCrashData, uint32_t* aaCrashDataLen);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 */
DllExport void CpProxyLinnCoUkDiagnostics1SyncCrashDataClear(THandle aHandle);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkDiagnostics1BeginCrashDataClear(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkDiagnostics1EndCrashDataClear(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[out] aaSysLog
 * @param[out] aaSysLogLen
 */
DllExport void CpProxyLinnCoUkDiagnostics1SyncSysLog(THandle aHandle, char** aaSysLog, uint32_t* aaSysLogLen);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkDiagnostics1BeginSysLog(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaSysLog
 * @param[in]  aaSysLogLen
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkDiagnostics1EndSysLog(THandle aHandle, ZappHandleAsync aAsync, char** aaSysLog, uint32_t* aaSysLogLen);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aaDiagnosticType
 * @param[out] aaDiagnosticInfo
 */
DllExport void CpProxyLinnCoUkDiagnostics1SyncDiagnostic(THandle aHandle, const char* aaDiagnosticType, char** aaDiagnosticInfo);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aaDiagnosticType
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkDiagnostics1BeginDiagnostic(THandle aHandle, const char* aaDiagnosticType, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaDiagnosticInfo
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkDiagnostics1EndDiagnostic(THandle aHandle, ZappHandleAsync aAsync, char** aaDiagnosticInfo);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[out] aaStateVariable
 */
DllExport void CpProxyLinnCoUkDiagnostics1SyncStateVariable(THandle aHandle, uint32_t* aaStateVariable);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkDiagnostics1BeginStateVariable(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaStateVariable
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkDiagnostics1EndStateVariable(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStateVariable);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aaStateVariable
 */
DllExport void CpProxyLinnCoUkDiagnostics1SyncSetStateVariable(THandle aHandle, uint32_t aaStateVariable);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aaStateVariable
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkDiagnostics1BeginSetStateVariable(THandle aHandle, uint32_t aaStateVariable, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkDiagnostics1EndSetStateVariable(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[out] aaPeriod
 */
DllExport void CpProxyLinnCoUkDiagnostics1SyncStateVariablePeriod(THandle aHandle, uint32_t* aaPeriod);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkDiagnostics1BeginStateVariablePeriod(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaPeriod
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkDiagnostics1EndStateVariablePeriod(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaPeriod);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aaPeriod
 */
DllExport void CpProxyLinnCoUkDiagnostics1SyncSetStateVariablePeriod(THandle aHandle, uint32_t aaPeriod);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aaPeriod
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkDiagnostics1BeginSetStateVariablePeriod(THandle aHandle, uint32_t aaPeriod, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkDiagnostics1EndSetStateVariablePeriod(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aaDelay
 */
DllExport void CpProxyLinnCoUkDiagnostics1SyncReboot(THandle aHandle, uint32_t aaDelay);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aaDelay
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkDiagnostics1BeginReboot(THandle aHandle, uint32_t aaDelay, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkDiagnostics1EndReboot(THandle aHandle, ZappHandleAsync aAsync);
/**
 * Set a callback to be run when the aStateVariable state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkDiagnostics1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkDiagnostics1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkDiagnostics1SetPropertyaStateVariableChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the aStateVariable property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aaStateVariable
 */
DllExport void CpProxyLinnCoUkDiagnostics1PropertyaStateVariable(THandle aHandle, uint32_t* aaStateVariable);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_LINNCOUKDIAGNOSTICS1_C

