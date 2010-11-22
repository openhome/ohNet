/**
 * Proxy for zapp.org:TestWidget:1
 */
#ifndef HEADER_ZAPPORGTESTWIDGET1_C
#define HEADER_ZAPPORGTESTWIDGET1_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyZappOrgTestWidget1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyZappOrgTestWidget1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 */
DllExport void CpProxyZappOrgTestWidget1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 * @param[in]  aRegisterIndex
 * @param[in]  aRegisterValue
 */
DllExport void CpProxyZappOrgTestWidget1SyncSetReadWriteRegister(THandle aHandle, uint32_t aRegisterIndex, uint32_t aRegisterValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 * @param[in]  aRegisterIndex
 * @param[in]  aRegisterValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestWidget1BeginSetReadWriteRegister(THandle aHandle, uint32_t aRegisterIndex, uint32_t aRegisterValue, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestWidget1EndSetReadWriteRegister(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 * @param[out] aWidgetClass
 */
DllExport void CpProxyZappOrgTestWidget1SyncGetWidgetClass(THandle aHandle, uint32_t* aWidgetClass);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestWidget1BeginGetWidgetClass(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aWidgetClass
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyZappOrgTestWidget1EndGetWidgetClass(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aWidgetClass);
/**
 * Set a callback to be run when the ReadWriteRegister0 state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyZappOrgTestWidget1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister0Changed(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ReadWriteRegister1 state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyZappOrgTestWidget1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister1Changed(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ReadWriteRegister2 state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyZappOrgTestWidget1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister2Changed(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ReadWriteRegister3 state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyZappOrgTestWidget1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister3Changed(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ReadOnlyRegister4 state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyZappOrgTestWidget1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister4Changed(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ReadOnlyRegister5 state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyZappOrgTestWidget1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister5Changed(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ReadOnlyRegister6 state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyZappOrgTestWidget1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister6Changed(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ReadOnlyRegister7 state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyZappOrgTestWidget1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyZappOrgTestWidget1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister7Changed(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the ReadWriteRegister0 property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aReadWriteRegister0
 */
DllExport void CpProxyZappOrgTestWidget1PropertyReadWriteRegister0(THandle aHandle, uint32_t* aReadWriteRegister0);
/**
 * Query the value of the ReadWriteRegister1 property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aReadWriteRegister1
 */
DllExport void CpProxyZappOrgTestWidget1PropertyReadWriteRegister1(THandle aHandle, uint32_t* aReadWriteRegister1);
/**
 * Query the value of the ReadWriteRegister2 property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aReadWriteRegister2
 */
DllExport void CpProxyZappOrgTestWidget1PropertyReadWriteRegister2(THandle aHandle, uint32_t* aReadWriteRegister2);
/**
 * Query the value of the ReadWriteRegister3 property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aReadWriteRegister3
 */
DllExport void CpProxyZappOrgTestWidget1PropertyReadWriteRegister3(THandle aHandle, uint32_t* aReadWriteRegister3);
/**
 * Query the value of the ReadOnlyRegister4 property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aReadOnlyRegister4
 */
DllExport void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister4(THandle aHandle, uint32_t* aReadOnlyRegister4);
/**
 * Query the value of the ReadOnlyRegister5 property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aReadOnlyRegister5
 */
DllExport void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister5(THandle aHandle, uint32_t* aReadOnlyRegister5);
/**
 * Query the value of the ReadOnlyRegister6 property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aReadOnlyRegister6
 */
DllExport void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister6(THandle aHandle, uint32_t* aReadOnlyRegister6);
/**
 * Query the value of the ReadOnlyRegister7 property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aReadOnlyRegister7
 */
DllExport void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister7(THandle aHandle, uint32_t* aReadOnlyRegister7);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_ZAPPORGTESTWIDGET1_C

