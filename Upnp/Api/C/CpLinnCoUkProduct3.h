/**
 * Proxy for linn.co.uk:Product:3
 */
#ifndef HEADER_LINNCOUKPRODUCT3_C
#define HEADER_LINNCOUKPRODUCT3_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyLinnCoUkProduct3 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyLinnCoUkProduct3Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 */
DllExport void CpProxyLinnCoUkProduct3Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[out] aaType
 */
DllExport void CpProxyLinnCoUkProduct3SyncType(THandle aHandle, char** aaType);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginType(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaType
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndType(THandle aHandle, ZappHandleAsync aAsync, char** aaType);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[out] aaModel
 */
DllExport void CpProxyLinnCoUkProduct3SyncModel(THandle aHandle, char** aaModel);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginModel(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaModel
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndModel(THandle aHandle, ZappHandleAsync aAsync, char** aaModel);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[out] aaName
 */
DllExport void CpProxyLinnCoUkProduct3SyncName(THandle aHandle, char** aaName);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginName(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaName
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndName(THandle aHandle, ZappHandleAsync aAsync, char** aaName);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaName
 */
DllExport void CpProxyLinnCoUkProduct3SyncSetName(THandle aHandle, const char* aaName);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaName
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSetName(THandle aHandle, const char* aaName, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSetName(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[out] aaRoom
 */
DllExport void CpProxyLinnCoUkProduct3SyncRoom(THandle aHandle, char** aaRoom);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginRoom(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaRoom
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndRoom(THandle aHandle, ZappHandleAsync aAsync, char** aaRoom);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaRoom
 */
DllExport void CpProxyLinnCoUkProduct3SyncSetRoom(THandle aHandle, const char* aaRoom);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaRoom
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSetRoom(THandle aHandle, const char* aaRoom, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSetRoom(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[out] aaStandby
 */
DllExport void CpProxyLinnCoUkProduct3SyncStandby(THandle aHandle, uint32_t* aaStandby);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginStandby(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaStandby
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndStandby(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStandby);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaStandby
 */
DllExport void CpProxyLinnCoUkProduct3SyncSetStandby(THandle aHandle, uint32_t aaStandby);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaStandby
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSetStandby(THandle aHandle, uint32_t aaStandby, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSetStandby(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[out] aaSourceCount
 */
DllExport void CpProxyLinnCoUkProduct3SyncSourceCount(THandle aHandle, uint32_t* aaSourceCount);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSourceCount(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaSourceCount
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSourceCount(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceCount);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[out] aaSourceXml
 */
DllExport void CpProxyLinnCoUkProduct3SyncSourceXml(THandle aHandle, char** aaSourceXml);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSourceXml(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaSourceXml
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSourceXml(THandle aHandle, ZappHandleAsync aAsync, char** aaSourceXml);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[out] aaSourceIndex
 */
DllExport void CpProxyLinnCoUkProduct3SyncSourceIndex(THandle aHandle, uint32_t* aaSourceIndex);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSourceIndex(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaSourceIndex
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSourceIndex(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceIndex);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 */
DllExport void CpProxyLinnCoUkProduct3SyncSetSourceIndex(THandle aHandle, uint32_t aaSourceIndex);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSetSourceIndex(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSetSourceIndex(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceName
 */
DllExport void CpProxyLinnCoUkProduct3SyncSetSourceIndexByName(THandle aHandle, const char* aaSourceName);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceName
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSetSourceIndexByName(THandle aHandle, const char* aaSourceName, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSetSourceIndexByName(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceName
 */
DllExport void CpProxyLinnCoUkProduct3SyncSetStartupSourceIndexByName(THandle aHandle, const char* aaSourceName);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceName
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSetStartupSourceIndexByName(THandle aHandle, const char* aaSourceName, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSetStartupSourceIndexByName(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[out] aaSourceIndex
 */
DllExport void CpProxyLinnCoUkProduct3SyncStartupSourceIndex(THandle aHandle, uint32_t* aaSourceIndex);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginStartupSourceIndex(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaSourceIndex
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndStartupSourceIndex(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceIndex);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 */
DllExport void CpProxyLinnCoUkProduct3SyncSetStartupSourceIndex(THandle aHandle, uint32_t aaSourceIndex);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSetStartupSourceIndex(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSetStartupSourceIndex(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[out] aaStartupSourceEnabled
 */
DllExport void CpProxyLinnCoUkProduct3SyncStartupSourceEnabled(THandle aHandle, uint32_t* aaStartupSourceEnabled);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginStartupSourceEnabled(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaStartupSourceEnabled
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndStartupSourceEnabled(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStartupSourceEnabled);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaStartupSourceEnabled
 */
DllExport void CpProxyLinnCoUkProduct3SyncSetStartupSourceEnabled(THandle aHandle, uint32_t aaStartupSourceEnabled);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaStartupSourceEnabled
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSetStartupSourceEnabled(THandle aHandle, uint32_t aaStartupSourceEnabled, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSetStartupSourceEnabled(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 * @param[out] aaSourceName
 */
DllExport void CpProxyLinnCoUkProduct3SyncSourceSystemName(THandle aHandle, uint32_t aaSourceIndex, char** aaSourceName);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSourceSystemName(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaSourceName
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSourceSystemName(THandle aHandle, ZappHandleAsync aAsync, char** aaSourceName);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 * @param[out] aaSourceName
 */
DllExport void CpProxyLinnCoUkProduct3SyncSourceName(THandle aHandle, uint32_t aaSourceIndex, char** aaSourceName);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSourceName(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaSourceName
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSourceName(THandle aHandle, ZappHandleAsync aAsync, char** aaSourceName);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 * @param[in]  aaSourceName
 */
DllExport void CpProxyLinnCoUkProduct3SyncSetSourceName(THandle aHandle, uint32_t aaSourceIndex, const char* aaSourceName);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 * @param[in]  aaSourceName
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSetSourceName(THandle aHandle, uint32_t aaSourceIndex, const char* aaSourceName, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSetSourceName(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 * @param[out] aaSourceType
 */
DllExport void CpProxyLinnCoUkProduct3SyncSourceType(THandle aHandle, uint32_t aaSourceIndex, char** aaSourceType);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSourceType(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaSourceType
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSourceType(THandle aHandle, ZappHandleAsync aAsync, char** aaSourceType);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 * @param[out] aaSourceVisible
 */
DllExport void CpProxyLinnCoUkProduct3SyncSourceVisible(THandle aHandle, uint32_t aaSourceIndex, uint32_t* aaSourceVisible);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSourceVisible(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaSourceVisible
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSourceVisible(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceVisible);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 * @param[in]  aaSourceVisible
 */
DllExport void CpProxyLinnCoUkProduct3SyncSetSourceVisible(THandle aHandle, uint32_t aaSourceIndex, uint32_t aaSourceVisible);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aaSourceIndex
 * @param[in]  aaSourceVisible
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3BeginSetSourceVisible(THandle aHandle, uint32_t aaSourceIndex, uint32_t aaSourceVisible, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProduct3EndSetSourceVisible(THandle aHandle, ZappHandleAsync aAsync);
/**
 * Set a callback to be run when the ProductType state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProduct3 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3SetPropertyProductTypeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ProductModel state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProduct3 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3SetPropertyProductModelChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ProductName state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProduct3 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3SetPropertyProductNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ProductRoom state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProduct3 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3SetPropertyProductRoomChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ProductStandby state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProduct3 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3SetPropertyProductStandbyChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ProductSourceIndex state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProduct3 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3SetPropertyProductSourceIndexChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ProductSourceCount state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProduct3 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3SetPropertyProductSourceCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ProductSourceXml state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProduct3 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3SetPropertyProductSourceXmlChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the StartupSourceIndex state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProduct3 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3SetPropertyStartupSourceIndexChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the StartupSourceEnabled state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProduct3 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3SetPropertyStartupSourceEnabledChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ProductAnySourceName state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProduct3 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ProductAnySourceVisible state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProduct3 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceVisibleChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ProductAnySourceType state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProduct3 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProduct3Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceTypeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the ProductType property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aProductType
 */
DllExport void CpProxyLinnCoUkProduct3PropertyProductType(THandle aHandle, char** aProductType);
/**
 * Query the value of the ProductModel property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aProductModel
 */
DllExport void CpProxyLinnCoUkProduct3PropertyProductModel(THandle aHandle, char** aProductModel);
/**
 * Query the value of the ProductName property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aProductName
 */
DllExport void CpProxyLinnCoUkProduct3PropertyProductName(THandle aHandle, char** aProductName);
/**
 * Query the value of the ProductRoom property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aProductRoom
 */
DllExport void CpProxyLinnCoUkProduct3PropertyProductRoom(THandle aHandle, char** aProductRoom);
/**
 * Query the value of the ProductStandby property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aProductStandby
 */
DllExport void CpProxyLinnCoUkProduct3PropertyProductStandby(THandle aHandle, uint32_t* aProductStandby);
/**
 * Query the value of the ProductSourceIndex property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aProductSourceIndex
 */
DllExport void CpProxyLinnCoUkProduct3PropertyProductSourceIndex(THandle aHandle, uint32_t* aProductSourceIndex);
/**
 * Query the value of the ProductSourceCount property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aProductSourceCount
 */
DllExport void CpProxyLinnCoUkProduct3PropertyProductSourceCount(THandle aHandle, uint32_t* aProductSourceCount);
/**
 * Query the value of the ProductSourceXml property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aProductSourceXml
 */
DllExport void CpProxyLinnCoUkProduct3PropertyProductSourceXml(THandle aHandle, char** aProductSourceXml);
/**
 * Query the value of the StartupSourceIndex property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aStartupSourceIndex
 */
DllExport void CpProxyLinnCoUkProduct3PropertyStartupSourceIndex(THandle aHandle, uint32_t* aStartupSourceIndex);
/**
 * Query the value of the StartupSourceEnabled property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aStartupSourceEnabled
 */
DllExport void CpProxyLinnCoUkProduct3PropertyStartupSourceEnabled(THandle aHandle, uint32_t* aStartupSourceEnabled);
/**
 * Query the value of the ProductAnySourceName property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aProductAnySourceName
 */
DllExport void CpProxyLinnCoUkProduct3PropertyProductAnySourceName(THandle aHandle, uint32_t* aProductAnySourceName);
/**
 * Query the value of the ProductAnySourceVisible property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aProductAnySourceVisible
 */
DllExport void CpProxyLinnCoUkProduct3PropertyProductAnySourceVisible(THandle aHandle, uint32_t* aProductAnySourceVisible);
/**
 * Query the value of the ProductAnySourceType property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aProductAnySourceType
 */
DllExport void CpProxyLinnCoUkProduct3PropertyProductAnySourceType(THandle aHandle, uint32_t* aProductAnySourceType);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_LINNCOUKPRODUCT3_C

