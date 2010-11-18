/**
 * Proxy for zapp.org:TestWidgetController:1
 */
#ifndef HEADER_ZAPPORGTESTWIDGETCONTROLLER1_C
#define HEADER_ZAPPORGTESTWIDGETCONTROLLER1_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyZappOrgTestWidgetController1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyZappOrgTestWidgetController1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidgetController1Create
 */
DllExport void CpProxyZappOrgTestWidgetController1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidgetController1Create
 * @param[in]  aWidgetUdn
 */
DllExport void CpProxyZappOrgTestWidgetController1SyncCreateWidget(THandle aHandle, const char* aWidgetUdn);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidgetController1Create
 * @param[in]  aWidgetUdn
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestWidgetController1BeginCreateWidget(THandle aHandle, const char* aWidgetUdn, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidgetController1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestWidgetController1EndCreateWidget(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidgetController1Create
 * @param[in]  aWidgetUdn
 */
DllExport void CpProxyZappOrgTestWidgetController1SyncRemoveWidget(THandle aHandle, const char* aWidgetUdn);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidgetController1Create
 * @param[in]  aWidgetUdn
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestWidgetController1BeginRemoveWidget(THandle aHandle, const char* aWidgetUdn, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidgetController1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestWidgetController1EndRemoveWidget(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidgetController1Create
 * @param[in]  aWidgetUdn
 * @param[in]  aRegisterIndex
 * @param[in]  aRegisterValue
 */
DllExport void CpProxyZappOrgTestWidgetController1SyncSetWidgetRegister(THandle aHandle, const char* aWidgetUdn, uint32_t aRegisterIndex, uint32_t aRegisterValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidgetController1Create
 * @param[in]  aWidgetUdn
 * @param[in]  aRegisterIndex
 * @param[in]  aRegisterValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestWidgetController1BeginSetWidgetRegister(THandle aHandle, const char* aWidgetUdn, uint32_t aRegisterIndex, uint32_t aRegisterValue, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidgetController1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestWidgetController1EndSetWidgetRegister(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidgetController1Create
 * @param[in]  aWidgetUdn
 * @param[in]  aRegisterIndex
 * @param[out] aRegisterValue
 */
DllExport void CpProxyZappOrgTestWidgetController1SyncGetWidgetRegister(THandle aHandle, const char* aWidgetUdn, uint32_t aRegisterIndex, uint32_t* aRegisterValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidgetController1Create
 * @param[in]  aWidgetUdn
 * @param[in]  aRegisterIndex
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestWidgetController1BeginGetWidgetRegister(THandle aHandle, const char* aWidgetUdn, uint32_t aRegisterIndex, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidgetController1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aRegisterValue
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestWidgetController1EndGetWidgetRegister(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aRegisterValue);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_ZAPPORGTESTWIDGETCONTROLLER1_C

