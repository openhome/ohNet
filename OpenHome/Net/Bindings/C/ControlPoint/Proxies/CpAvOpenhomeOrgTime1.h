/**
 * Proxy for av.openhome.org:Time:1
 */
#ifndef HEADER_AVOPENHOMEORGTIME1_C
#define HEADER_AVOPENHOMEORGTIME1_C

#include <OpenHome/OsTypes.h>
#include <OpenHome/Defines.h>
#include <OpenHome/Net/C/Async.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CpProxyAvOpenhomeOrgTime1
 * @ingroup Proxies
 * @{
 */

/**
 * Constructor.
 * Creates an instance of CpProxyAvOpenhomeOrgTime1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle STDCALL CpProxyAvOpenhomeOrgTime1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgTime1Create
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgTime1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgTime1Create
 * @param[out] aTrackCount
 * @param[out] aDuration
 * @param[out] aSeconds
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyAvOpenhomeOrgTime1SyncTime(THandle aHandle, uint32_t* aTrackCount, uint32_t* aDuration, uint32_t* aSeconds);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgTime1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgTime1BeginTime(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgTime1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aTrackCount
 * @param[out] aDuration
 * @param[out] aSeconds
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyAvOpenhomeOrgTime1EndTime(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aTrackCount, uint32_t* aDuration, uint32_t* aSeconds);
/**
 * Set a callback to be run when the TrackCount state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgTime1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgTime1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgTime1SetPropertyTrackCountChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Duration state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgTime1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgTime1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgTime1SetPropertyDurationChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Seconds state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgTime1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgTime1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgTime1SetPropertySecondsChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);

/**
 * Query the value of the TrackCount property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgTime1Create
 * @param[out] aTrackCount
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgTime1PropertyTrackCount(THandle aHandle, uint32_t* aTrackCount);
/**
 * Query the value of the Duration property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgTime1Create
 * @param[out] aDuration
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgTime1PropertyDuration(THandle aHandle, uint32_t* aDuration);
/**
 * Query the value of the Seconds property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgTime1Create
 * @param[out] aSeconds
 */
DllExport void STDCALL CpProxyAvOpenhomeOrgTime1PropertySeconds(THandle aHandle, uint32_t* aSeconds);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_AVOPENHOMEORGTIME1_C

