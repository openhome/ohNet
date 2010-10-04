/**
 * Proxy for linn.co.uk:ProxyManager:1
 */
#ifndef HEADER_LINNCOUKPROXYMANAGER1_C
#define HEADER_LINNCOUKPROXYMANAGER1_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyLinnCoUkProxyManager1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyLinnCoUkProxyManager1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 */
DllExport void CpProxyLinnCoUkProxyManager1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[out] aaConnected
 */
DllExport void CpProxyLinnCoUkProxyManager1SyncKontrolProductConnected(THandle aHandle, char** aaConnected);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProxyManager1BeginKontrolProductConnected(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaConnected
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProxyManager1EndKontrolProductConnected(THandle aHandle, ZappHandleAsync aAsync, char** aaConnected);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aaConnected
 */
DllExport void CpProxyLinnCoUkProxyManager1SyncSetKontrolProductConnected(THandle aHandle, const char* aaConnected);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aaConnected
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProxyManager1BeginSetKontrolProductConnected(THandle aHandle, const char* aaConnected, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProxyManager1EndSetKontrolProductConnected(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[out] aaPort
 */
DllExport void CpProxyLinnCoUkProxyManager1SyncKontrolProductComPort(THandle aHandle, uint32_t* aaPort);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProxyManager1BeginKontrolProductComPort(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaPort
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProxyManager1EndKontrolProductComPort(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaPort);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aaConnected
 */
DllExport void CpProxyLinnCoUkProxyManager1SyncSetKontrolProductComPort(THandle aHandle, uint32_t aaConnected);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aaConnected
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProxyManager1BeginSetKontrolProductComPort(THandle aHandle, uint32_t aaConnected, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProxyManager1EndSetKontrolProductComPort(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[out] aaConnected
 */
DllExport void CpProxyLinnCoUkProxyManager1SyncDiscPlayerConnected(THandle aHandle, char** aaConnected);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProxyManager1BeginDiscPlayerConnected(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaConnected
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProxyManager1EndDiscPlayerConnected(THandle aHandle, ZappHandleAsync aAsync, char** aaConnected);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aaConnected
 */
DllExport void CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerConnected(THandle aHandle, const char* aaConnected);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aaConnected
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerConnected(THandle aHandle, const char* aaConnected, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProxyManager1EndSetDiscPlayerConnected(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[out] aaPort
 */
DllExport void CpProxyLinnCoUkProxyManager1SyncDiscPlayerComPort(THandle aHandle, uint32_t* aaPort);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProxyManager1BeginDiscPlayerComPort(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaPort
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProxyManager1EndDiscPlayerComPort(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaPort);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aaConnected
 */
DllExport void CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerComPort(THandle aHandle, uint32_t aaConnected);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aaConnected
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerComPort(THandle aHandle, uint32_t aaConnected, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProxyManager1EndSetDiscPlayerComPort(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[out] aaResult
 */
DllExport void CpProxyLinnCoUkProxyManager1SyncTestKontrolProductConnection(THandle aHandle, uint32_t* aaResult);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProxyManager1BeginTestKontrolProductConnection(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaResult
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProxyManager1EndTestKontrolProductConnection(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaResult);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[out] aaResult
 */
DllExport void CpProxyLinnCoUkProxyManager1SyncTestDiscPlayerConnection(THandle aHandle, uint32_t* aaResult);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProxyManager1BeginTestDiscPlayerConnection(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaResult
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkProxyManager1EndTestDiscPlayerConnection(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaResult);
/**
 * Set a callback to be run when the KontrolProductConnected state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProxyManager1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProxyManager1SetPropertyKontrolProductConnectedChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the KontrolProductComPort state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProxyManager1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProxyManager1SetPropertyKontrolProductComPortChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the DiscPlayerConnected state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProxyManager1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProxyManager1SetPropertyDiscPlayerConnectedChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the DiscPlayerComPort state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkProxyManager1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkProxyManager1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkProxyManager1SetPropertyDiscPlayerComPortChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the KontrolProductConnected property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aKontrolProductConnected
 */
DllExport void CpProxyLinnCoUkProxyManager1PropertyKontrolProductConnected(THandle aHandle, char** aKontrolProductConnected);
/**
 * Query the value of the KontrolProductComPort property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aKontrolProductComPort
 */
DllExport void CpProxyLinnCoUkProxyManager1PropertyKontrolProductComPort(THandle aHandle, uint32_t* aKontrolProductComPort);
/**
 * Query the value of the DiscPlayerConnected property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aDiscPlayerConnected
 */
DllExport void CpProxyLinnCoUkProxyManager1PropertyDiscPlayerConnected(THandle aHandle, char** aDiscPlayerConnected);
/**
 * Query the value of the DiscPlayerComPort property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aDiscPlayerComPort
 */
DllExport void CpProxyLinnCoUkProxyManager1PropertyDiscPlayerComPort(THandle aHandle, uint32_t* aDiscPlayerComPort);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_LINNCOUKPROXYMANAGER1_C

