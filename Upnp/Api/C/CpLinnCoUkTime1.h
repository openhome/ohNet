/**
 * Proxy for linn.co.uk:Time:1
 */
#ifndef HEADER_LINNCOUKTIME1_C
#define HEADER_LINNCOUKTIME1_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyLinnCoUkTime1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyLinnCoUkTime1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkTime1Create
 */
DllExport void CpProxyLinnCoUkTime1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkTime1Create
 * @param[out] aaTrackCount
 * @param[out] aaDuration
 * @param[out] aaSeconds
 */
DllExport void CpProxyLinnCoUkTime1SyncTime(THandle aHandle, uint32_t* aaTrackCount, uint32_t* aaDuration, uint32_t* aaSeconds);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkTime1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkTime1BeginTime(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkTime1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaTrackCount
 * @param[out] aaDuration
 * @param[out] aaSeconds
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkTime1EndTime(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaTrackCount, uint32_t* aaDuration, uint32_t* aaSeconds);
/**
 * Set a callback to be run when the TrackCount state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkTime1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkTime1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkTime1SetPropertyTrackCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Duration state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkTime1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkTime1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkTime1SetPropertyDurationChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Seconds state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkTime1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkTime1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkTime1SetPropertySecondsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the TrackCount property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aTrackCount
 */
DllExport void CpProxyLinnCoUkTime1PropertyTrackCount(THandle aHandle, uint32_t* aTrackCount);
/**
 * Query the value of the Duration property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aDuration
 */
DllExport void CpProxyLinnCoUkTime1PropertyDuration(THandle aHandle, uint32_t* aDuration);
/**
 * Query the value of the Seconds property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aSeconds
 */
DllExport void CpProxyLinnCoUkTime1PropertySeconds(THandle aHandle, uint32_t* aSeconds);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_LINNCOUKTIME1_C

