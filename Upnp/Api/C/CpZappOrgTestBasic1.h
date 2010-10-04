/**
 * Proxy for zapp.org:TestBasic:1
 */
#ifndef HEADER_ZAPPORGTESTBASIC1_C
#define HEADER_ZAPPORGTESTBASIC1_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyZappOrgTestBasic1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyZappOrgTestBasic1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 */
DllExport void CpProxyZappOrgTestBasic1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValue
 * @param[out] aResult
 */
DllExport void CpProxyZappOrgTestBasic1SyncIncrement(THandle aHandle, uint32_t aValue, uint32_t* aResult);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginIncrement(THandle aHandle, uint32_t aValue, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndIncrement(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aResult);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValue
 * @param[out] aResult
 */
DllExport void CpProxyZappOrgTestBasic1SyncDecrement(THandle aHandle, int32_t aValue, int32_t* aResult);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginDecrement(THandle aHandle, int32_t aValue, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndDecrement(THandle aHandle, ZappHandleAsync aAsync, int32_t* aResult);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValue
 * @param[out] aResult
 */
DllExport void CpProxyZappOrgTestBasic1SyncToggle(THandle aHandle, uint32_t aValue, uint32_t* aResult);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginToggle(THandle aHandle, uint32_t aValue, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndToggle(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aResult);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValue
 * @param[out] aResult
 */
DllExport void CpProxyZappOrgTestBasic1SyncEchoString(THandle aHandle, const char* aValue, char** aResult);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginEchoString(THandle aHandle, const char* aValue, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndEchoString(THandle aHandle, ZappHandleAsync aAsync, char** aResult);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValue
 * @param[in]  aValueLen
 * @param[out] aResult
 * @param[out] aResultLen
 */
DllExport void CpProxyZappOrgTestBasic1SyncEchoBinary(THandle aHandle, const char* aValue, uint32_t aValueLen, char** aResult, uint32_t* aResultLen);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValue
 * @param[in]  aValueLen
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginEchoBinary(THandle aHandle, const char* aValue, uint32_t aValueLen, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 * @param[in]  aResultLen
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndEchoBinary(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aResultLen);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValueUint
 */
DllExport void CpProxyZappOrgTestBasic1SyncSetUint(THandle aHandle, uint32_t aValueUint);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValueUint
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginSetUint(THandle aHandle, uint32_t aValueUint, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndSetUint(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[out] aValueUint
 */
DllExport void CpProxyZappOrgTestBasic1SyncGetUint(THandle aHandle, uint32_t* aValueUint);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginGetUint(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValueUint
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndGetUint(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aValueUint);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValueInt
 */
DllExport void CpProxyZappOrgTestBasic1SyncSetInt(THandle aHandle, int32_t aValueInt);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValueInt
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginSetInt(THandle aHandle, int32_t aValueInt, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndSetInt(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[out] aValueInt
 */
DllExport void CpProxyZappOrgTestBasic1SyncGetInt(THandle aHandle, int32_t* aValueInt);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginGetInt(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValueInt
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndGetInt(THandle aHandle, ZappHandleAsync aAsync, int32_t* aValueInt);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValueBool
 */
DllExport void CpProxyZappOrgTestBasic1SyncSetBool(THandle aHandle, uint32_t aValueBool);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValueBool
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginSetBool(THandle aHandle, uint32_t aValueBool, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndSetBool(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[out] aValueBool
 */
DllExport void CpProxyZappOrgTestBasic1SyncGetBool(THandle aHandle, uint32_t* aValueBool);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginGetBool(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValueBool
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndGetBool(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aValueBool);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValueUint
 * @param[in]  aValueInt
 * @param[in]  aValueBool
 */
DllExport void CpProxyZappOrgTestBasic1SyncSetMultiple(THandle aHandle, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValueUint
 * @param[in]  aValueInt
 * @param[in]  aValueBool
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginSetMultiple(THandle aHandle, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndSetMultiple(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValueStr
 */
DllExport void CpProxyZappOrgTestBasic1SyncSetString(THandle aHandle, const char* aValueStr);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValueStr
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginSetString(THandle aHandle, const char* aValueStr, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndSetString(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[out] aValueStr
 */
DllExport void CpProxyZappOrgTestBasic1SyncGetString(THandle aHandle, char** aValueStr);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginGetString(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValueStr
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndGetString(THandle aHandle, ZappHandleAsync aAsync, char** aValueStr);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValueBin
 * @param[in]  aValueBinLen
 */
DllExport void CpProxyZappOrgTestBasic1SyncSetBinary(THandle aHandle, const char* aValueBin, uint32_t aValueBinLen);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aValueBin
 * @param[in]  aValueBinLen
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginSetBinary(THandle aHandle, const char* aValueBin, uint32_t aValueBinLen, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndSetBinary(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[out] aValueBin
 * @param[out] aValueBinLen
 */
DllExport void CpProxyZappOrgTestBasic1SyncGetBinary(THandle aHandle, char** aValueBin, uint32_t* aValueBinLen);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1BeginGetBinary(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValueBin
 * @param[in]  aValueBinLen
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestBasic1EndGetBinary(THandle aHandle, ZappHandleAsync aAsync, char** aValueBin, uint32_t* aValueBinLen);
/**
 * Set a callback to be run when the VarUint state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyZappOrgTestBasic1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1SetPropertyVarUintChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the VarInt state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyZappOrgTestBasic1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1SetPropertyVarIntChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the VarBool state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyZappOrgTestBasic1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1SetPropertyVarBoolChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the VarStr state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyZappOrgTestBasic1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1SetPropertyVarStrChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the VarBin state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyZappOrgTestBasic1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestBasic1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestBasic1SetPropertyVarBinChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the VarUint property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aVarUint
 */
DllExport void CpProxyZappOrgTestBasic1PropertyVarUint(THandle aHandle, uint32_t* aVarUint);
/**
 * Query the value of the VarInt property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aVarInt
 */
DllExport void CpProxyZappOrgTestBasic1PropertyVarInt(THandle aHandle, int32_t* aVarInt);
/**
 * Query the value of the VarBool property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aVarBool
 */
DllExport void CpProxyZappOrgTestBasic1PropertyVarBool(THandle aHandle, uint32_t* aVarBool);
/**
 * Query the value of the VarStr property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aVarStr
 */
DllExport void CpProxyZappOrgTestBasic1PropertyVarStr(THandle aHandle, char** aVarStr);
/**
 * Query the value of the VarBin property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aVarBin
 * @param[out] aLen
 */
DllExport void CpProxyZappOrgTestBasic1PropertyVarBin(THandle aHandle, char** aVarBin, uint32_t* aLen);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_ZAPPORGTESTBASIC1_C

