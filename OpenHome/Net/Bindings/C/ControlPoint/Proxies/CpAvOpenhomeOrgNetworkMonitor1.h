/**
 * Proxy for av.openhome.org:NetworkMonitor:1
 */
#ifndef HEADER_AVOPENHOMEORGNETWORKMONITOR1_C
#define HEADER_AVOPENHOMEORGNETWORKMONITOR1_C

#include <OpenHome/OsTypes.h>
#include <OpenHome/Defines.h>
#include <OpenHome/Net/C/Async.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CpProxyAvOpenhomeOrgNetworkMonitor1
 * @ingroup Proxies
 * @{
 */

/**
 * Constructor.
 * Creates an instance of CpProxyAvOpenhomeOrgNetworkMonitor1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 * @param[out] aName
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1SyncName(THandle aHandle, char** aName);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1BeginName(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aName
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1EndName(THandle aHandle, OhNetHandleAsync aAsync, char** aName);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 * @param[out] aSender
 * @param[out] aReceiver
 * @param[out] aResults
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1SyncPorts(THandle aHandle, uint32_t* aSender, uint32_t* aReceiver, uint32_t* aResults);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1BeginPorts(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aSender
 * @param[out] aReceiver
 * @param[out] aResults
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1EndPorts(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aSender, uint32_t* aReceiver, uint32_t* aResults);
/**
 * Set a callback to be run when the Name state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgNetworkMonitor1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1SetPropertyNameChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Sender state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgNetworkMonitor1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1SetPropertySenderChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Receiver state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgNetworkMonitor1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1SetPropertyReceiverChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Results state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgNetworkMonitor1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1SetPropertyResultsChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);

/**
 * Query the value of the Name property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 * @param[out] aName
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1PropertyName(THandle aHandle, char** aName);
/**
 * Query the value of the Sender property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 * @param[out] aSender
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1PropertySender(THandle aHandle, uint32_t* aSender);
/**
 * Query the value of the Receiver property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 * @param[out] aReceiver
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1PropertyReceiver(THandle aHandle, uint32_t* aReceiver);
/**
 * Query the value of the Results property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgNetworkMonitor1Create
 * @param[out] aResults
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgNetworkMonitor1PropertyResults(THandle aHandle, uint32_t* aResults);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_AVOPENHOMEORGNETWORKMONITOR1_C

