/**
 * Proxy for openhome.org:TestBasic:1
 */
#ifndef HEADER_OPENHOMEORGTESTBASIC1_C
#define HEADER_OPENHOMEORGTESTBASIC1_C

#include <OsTypes.h>
#include <OhNetDefines.h>
#include <C/Async.h>
#include <C/OhNet.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CpProxyOpenhomeOrgTestBasic1
 * @ingroup Proxies
 * @{
 */

/**
 * Constructor.
 * Creates an instance of CpProxyOpenhomeOrgTestBasic1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyOpenhomeOrgTestBasic1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 */
DllExport void CpProxyOpenhomeOrgTestBasic1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValue
 * @param[out] aResult
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncIncrement(THandle aHandle, uint32_t aValue, uint32_t* aResult);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginIncrement(THandle aHandle, uint32_t aValue, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndIncrement(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aResult);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValue
 * @param[out] aResult
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncDecrement(THandle aHandle, int32_t aValue, int32_t* aResult);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginDecrement(THandle aHandle, int32_t aValue, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndDecrement(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aResult);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValue
 * @param[out] aResult
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncToggle(THandle aHandle, uint32_t aValue, uint32_t* aResult);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginToggle(THandle aHandle, uint32_t aValue, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndToggle(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aResult);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValue
 * @param[out] aResult
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncEchoString(THandle aHandle, const char* aValue, char** aResult);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginEchoString(THandle aHandle, const char* aValue, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndEchoString(THandle aHandle, OhNetHandleAsync aAsync, char** aResult);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValue
 * @param[in]  aValueLen
 * @param[out] aResult
 * @param[out] aResultLen
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncEchoBinary(THandle aHandle, const char* aValue, uint32_t aValueLen, char** aResult, uint32_t* aResultLen);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValue
 * @param[in]  aValueLen
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginEchoBinary(THandle aHandle, const char* aValue, uint32_t aValueLen, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResult
 * @param[in]  aResultLen
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndEchoBinary(THandle aHandle, OhNetHandleAsync aAsync, char** aResult, uint32_t* aResultLen);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValueUint
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncSetUint(THandle aHandle, uint32_t aValueUint);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValueUint
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginSetUint(THandle aHandle, uint32_t aValueUint, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndSetUint(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[out] aValueUint
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncGetUint(THandle aHandle, uint32_t* aValueUint);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginGetUint(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValueUint
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndGetUint(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValueUint);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValueInt
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncSetInt(THandle aHandle, int32_t aValueInt);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValueInt
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginSetInt(THandle aHandle, int32_t aValueInt, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndSetInt(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[out] aValueInt
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncGetInt(THandle aHandle, int32_t* aValueInt);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginGetInt(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValueInt
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndGetInt(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aValueInt);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValueBool
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncSetBool(THandle aHandle, uint32_t aValueBool);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValueBool
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginSetBool(THandle aHandle, uint32_t aValueBool, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndSetBool(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[out] aValueBool
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncGetBool(THandle aHandle, uint32_t* aValueBool);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginGetBool(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValueBool
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndGetBool(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValueBool);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValueUint
 * @param[in]  aValueInt
 * @param[in]  aValueBool
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncSetMultiple(THandle aHandle, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValueUint
 * @param[in]  aValueInt
 * @param[in]  aValueBool
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginSetMultiple(THandle aHandle, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndSetMultiple(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValueStr
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncSetString(THandle aHandle, const char* aValueStr);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValueStr
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginSetString(THandle aHandle, const char* aValueStr, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndSetString(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[out] aValueStr
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncGetString(THandle aHandle, char** aValueStr);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginGetString(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValueStr
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndGetString(THandle aHandle, OhNetHandleAsync aAsync, char** aValueStr);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValueBin
 * @param[in]  aValueBinLen
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncSetBinary(THandle aHandle, const char* aValueBin, uint32_t aValueBinLen);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aValueBin
 * @param[in]  aValueBinLen
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginSetBinary(THandle aHandle, const char* aValueBin, uint32_t aValueBinLen, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndSetBinary(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[out] aValueBin
 * @param[out] aValueBinLen
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncGetBinary(THandle aHandle, char** aValueBin, uint32_t* aValueBinLen);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginGetBinary(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValueBin
 * @param[in]  aValueBinLen
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndGetBinary(THandle aHandle, OhNetHandleAsync aAsync, char** aValueBin, uint32_t* aValueBinLen);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncToggleBool(THandle aHandle);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginToggleBool(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndToggleBool(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aData
 * @param[in]  aFileFullName
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncWriteFile(THandle aHandle, const char* aData, const char* aFileFullName);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aData
 * @param[in]  aFileFullName
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginWriteFile(THandle aHandle, const char* aData, const char* aFileFullName, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndWriteFile(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SyncShutdown(THandle aHandle);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1BeginShutdown(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestBasic1EndShutdown(THandle aHandle, OhNetHandleAsync aAsync);
/**
 * Set a callback to be run when the VarUint state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SetPropertyVarUintChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the VarInt state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SetPropertyVarIntChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the VarBool state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SetPropertyVarBoolChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the VarStr state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SetPropertyVarStrChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the VarBin state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestBasic1SetPropertyVarBinChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);

/**
 * Query the value of the VarUint property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[out] aVarUint
 */
DllExport void CpProxyOpenhomeOrgTestBasic1PropertyVarUint(THandle aHandle, uint32_t* aVarUint);
/**
 * Query the value of the VarInt property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[out] aVarInt
 */
DllExport void CpProxyOpenhomeOrgTestBasic1PropertyVarInt(THandle aHandle, int32_t* aVarInt);
/**
 * Query the value of the VarBool property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[out] aVarBool
 */
DllExport void CpProxyOpenhomeOrgTestBasic1PropertyVarBool(THandle aHandle, uint32_t* aVarBool);
/**
 * Query the value of the VarStr property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[out] aVarStr
 */
DllExport void CpProxyOpenhomeOrgTestBasic1PropertyVarStr(THandle aHandle, char** aVarStr);
/**
 * Query the value of the VarBin property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestBasic1Create
 * @param[out] aVarBin
 * @param[out] aLen
 */
DllExport void CpProxyOpenhomeOrgTestBasic1PropertyVarBin(THandle aHandle, char** aVarBin, uint32_t* aLen);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_OPENHOMEORGTESTBASIC1_C

