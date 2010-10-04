/**
 * Proxy for linn.co.uk:Preamp:4
 */
#ifndef HEADER_LINNCOUKPREAMP4_C
#define HEADER_LINNCOUKPREAMP4_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyLinnCoUkPreamp4 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyLinnCoUkPreamp4Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 */
DllExport void CpProxyLinnCoUkPreamp4Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 */
DllExport void CpProxyLinnCoUkPreamp4SyncVolumeInc(THandle aHandle);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4BeginVolumeInc(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPreamp4EndVolumeInc(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 */
DllExport void CpProxyLinnCoUkPreamp4SyncVolumeDec(THandle aHandle);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4BeginVolumeDec(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPreamp4EndVolumeDec(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aaVolume
 */
DllExport void CpProxyLinnCoUkPreamp4SyncSetVolume(THandle aHandle, uint32_t aaVolume);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aaVolume
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4BeginSetVolume(THandle aHandle, uint32_t aaVolume, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPreamp4EndSetVolume(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[out] aaVolume
 */
DllExport void CpProxyLinnCoUkPreamp4SyncVolume(THandle aHandle, uint32_t* aaVolume);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4BeginVolume(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaVolume
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPreamp4EndVolume(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaVolume);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aaMute
 */
DllExport void CpProxyLinnCoUkPreamp4SyncSetMute(THandle aHandle, uint32_t aaMute);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aaMute
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4BeginSetMute(THandle aHandle, uint32_t aaMute, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPreamp4EndSetMute(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[out] aaMute
 */
DllExport void CpProxyLinnCoUkPreamp4SyncMute(THandle aHandle, uint32_t* aaMute);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4BeginMute(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaMute
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPreamp4EndMute(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaMute);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aaBalance
 */
DllExport void CpProxyLinnCoUkPreamp4SyncSetBalance(THandle aHandle, int32_t aaBalance);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aaBalance
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4BeginSetBalance(THandle aHandle, int32_t aaBalance, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPreamp4EndSetBalance(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[out] aaBalance
 */
DllExport void CpProxyLinnCoUkPreamp4SyncBalance(THandle aHandle, int32_t* aaBalance);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4BeginBalance(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaBalance
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPreamp4EndBalance(THandle aHandle, ZappHandleAsync aAsync, int32_t* aaBalance);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aaVolumeLimit
 */
DllExport void CpProxyLinnCoUkPreamp4SyncSetVolumeLimit(THandle aHandle, uint32_t aaVolumeLimit);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aaVolumeLimit
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4BeginSetVolumeLimit(THandle aHandle, uint32_t aaVolumeLimit, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPreamp4EndSetVolumeLimit(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[out] aaVolumeLimit
 */
DllExport void CpProxyLinnCoUkPreamp4SyncVolumeLimit(THandle aHandle, uint32_t* aaVolumeLimit);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4BeginVolumeLimit(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaVolumeLimit
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPreamp4EndVolumeLimit(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaVolumeLimit);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aaStartupVolume
 */
DllExport void CpProxyLinnCoUkPreamp4SyncSetStartupVolume(THandle aHandle, uint32_t aaStartupVolume);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aaStartupVolume
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4BeginSetStartupVolume(THandle aHandle, uint32_t aaStartupVolume, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPreamp4EndSetStartupVolume(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[out] aaStartupVolume
 */
DllExport void CpProxyLinnCoUkPreamp4SyncStartupVolume(THandle aHandle, uint32_t* aaStartupVolume);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4BeginStartupVolume(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaStartupVolume
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPreamp4EndStartupVolume(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStartupVolume);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aaStartupVolumeEnabled
 */
DllExport void CpProxyLinnCoUkPreamp4SyncSetStartupVolumeEnabled(THandle aHandle, uint32_t aaStartupVolumeEnabled);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aaStartupVolumeEnabled
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4BeginSetStartupVolumeEnabled(THandle aHandle, uint32_t aaStartupVolumeEnabled, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPreamp4EndSetStartupVolumeEnabled(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[out] aaStartupVolumeEnabled
 */
DllExport void CpProxyLinnCoUkPreamp4SyncStartupVolumeEnabled(THandle aHandle, uint32_t* aaStartupVolumeEnabled);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4BeginStartupVolumeEnabled(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaStartupVolumeEnabled
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkPreamp4EndStartupVolumeEnabled(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStartupVolumeEnabled);
/**
 * Set a callback to be run when the Volume state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkPreamp4 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4SetPropertyVolumeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Mute state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkPreamp4 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4SetPropertyMuteChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Balance state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkPreamp4 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4SetPropertyBalanceChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the VolumeLimit state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkPreamp4 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4SetPropertyVolumeLimitChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the StartupVolume state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkPreamp4 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4SetPropertyStartupVolumeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the StartupVolumeEnabled state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkPreamp4 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkPreamp4Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkPreamp4SetPropertyStartupVolumeEnabledChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the Volume property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aVolume
 */
DllExport void CpProxyLinnCoUkPreamp4PropertyVolume(THandle aHandle, uint32_t* aVolume);
/**
 * Query the value of the Mute property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aMute
 */
DllExport void CpProxyLinnCoUkPreamp4PropertyMute(THandle aHandle, uint32_t* aMute);
/**
 * Query the value of the Balance property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aBalance
 */
DllExport void CpProxyLinnCoUkPreamp4PropertyBalance(THandle aHandle, int32_t* aBalance);
/**
 * Query the value of the VolumeLimit property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aVolumeLimit
 */
DllExport void CpProxyLinnCoUkPreamp4PropertyVolumeLimit(THandle aHandle, uint32_t* aVolumeLimit);
/**
 * Query the value of the StartupVolume property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aStartupVolume
 */
DllExport void CpProxyLinnCoUkPreamp4PropertyStartupVolume(THandle aHandle, uint32_t* aStartupVolume);
/**
 * Query the value of the StartupVolumeEnabled property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aStartupVolumeEnabled
 */
DllExport void CpProxyLinnCoUkPreamp4PropertyStartupVolumeEnabled(THandle aHandle, uint32_t* aStartupVolumeEnabled);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_LINNCOUKPREAMP4_C

