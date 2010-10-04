/**
 * Proxy for upnp.org:SwitchPower:1
 */
#ifndef HEADER_UPNPORGSWITCHPOWER1_C
#define HEADER_UPNPORGSWITCHPOWER1_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyUpnpOrgSwitchPower1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyUpnpOrgSwitchPower1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgSwitchPower1Create
 */
DllExport void CpProxyUpnpOrgSwitchPower1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgSwitchPower1Create
 * @param[in]  anewTargetValue
 */
DllExport void CpProxyUpnpOrgSwitchPower1SyncSetTarget(THandle aHandle, uint32_t anewTargetValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgSwitchPower1Create
 * @param[in]  anewTargetValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgSwitchPower1BeginSetTarget(THandle aHandle, uint32_t anewTargetValue, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgSwitchPower1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgSwitchPower1EndSetTarget(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgSwitchPower1Create
 * @param[out] aRetTargetValue
 */
DllExport void CpProxyUpnpOrgSwitchPower1SyncGetTarget(THandle aHandle, uint32_t* aRetTargetValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgSwitchPower1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgSwitchPower1BeginGetTarget(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgSwitchPower1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aRetTargetValue
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgSwitchPower1EndGetTarget(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aRetTargetValue);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgSwitchPower1Create
 * @param[out] aResultStatus
 */
DllExport void CpProxyUpnpOrgSwitchPower1SyncGetStatus(THandle aHandle, uint32_t* aResultStatus);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgSwitchPower1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgSwitchPower1BeginGetStatus(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgSwitchPower1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aResultStatus
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgSwitchPower1EndGetStatus(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aResultStatus);
/**
 * Set a callback to be run when the Status state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyUpnpOrgSwitchPower1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgSwitchPower1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgSwitchPower1SetPropertyStatusChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the Status property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aStatus
 */
DllExport void CpProxyUpnpOrgSwitchPower1PropertyStatus(THandle aHandle, uint32_t* aStatus);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_UPNPORGSWITCHPOWER1_C

