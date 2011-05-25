/**
 * Proxy for av.openhome.org:Volume:1
 */
#ifndef HEADER_AVOPENHOMEORGVOLUME1_C
#define HEADER_AVOPENHOMEORGVOLUME1_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/OhNet.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CpProxyAvOpenhomeOrgVolume1
 * @ingroup Proxies
 * @{
 */

/**
 * Constructor.
 * Creates an instance of CpProxyAvOpenhomeOrgVolume1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyAvOpenhomeOrgVolume1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 */
DllExport void CpProxyAvOpenhomeOrgVolume1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[out] aVolumeMax
 * @param[out] aVolumeUnity
 * @param[out] aVolumeSteps
 * @param[out] aVolumeMilliDbPerStep
 * @param[out] aBalanceMax
 * @param[out] aFadeMax
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncCharacteristics(THandle aHandle, uint32_t* aVolumeMax, uint32_t* aVolumeUnity, uint32_t* aVolumeSteps, uint32_t* aVolumeMilliDbPerStep, uint32_t* aBalanceMax, uint32_t* aFadeMax);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginCharacteristics(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aVolumeMax
 * @param[out] aVolumeUnity
 * @param[out] aVolumeSteps
 * @param[out] aVolumeMilliDbPerStep
 * @param[out] aBalanceMax
 * @param[out] aFadeMax
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndCharacteristics(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aVolumeMax, uint32_t* aVolumeUnity, uint32_t* aVolumeSteps, uint32_t* aVolumeMilliDbPerStep, uint32_t* aBalanceMax, uint32_t* aFadeMax);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aValue
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncSetVolume(THandle aHandle, uint32_t aValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginSetVolume(THandle aHandle, uint32_t aValue, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndSetVolume(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncVolumeInc(THandle aHandle);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginVolumeInc(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndVolumeInc(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncVolumeDec(THandle aHandle);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginVolumeDec(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndVolumeDec(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[out] aValue
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncVolume(THandle aHandle, uint32_t* aValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginVolume(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValue
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndVolume(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aValue
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncSetBalance(THandle aHandle, int32_t aValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginSetBalance(THandle aHandle, int32_t aValue, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndSetBalance(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncBalanceInc(THandle aHandle);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginBalanceInc(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndBalanceInc(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncBalanceDec(THandle aHandle);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginBalanceDec(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndBalanceDec(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[out] aValue
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncBalance(THandle aHandle, int32_t* aValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginBalance(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValue
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndBalance(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aValue);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aValue
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncSetFade(THandle aHandle, int32_t aValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginSetFade(THandle aHandle, int32_t aValue, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndSetFade(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncFadeInc(THandle aHandle);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginFadeInc(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndFadeInc(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncFadeDec(THandle aHandle);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginFadeDec(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndFadeDec(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[out] aValue
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncFade(THandle aHandle, int32_t* aValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginFade(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValue
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndFade(THandle aHandle, OhNetHandleAsync aAsync, int32_t* aValue);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aValue
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncSetMute(THandle aHandle, uint32_t aValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginSetMute(THandle aHandle, uint32_t aValue, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndSetMute(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[out] aValue
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncMute(THandle aHandle, uint32_t* aValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginMute(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValue
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndMute(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[out] aValue
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SyncVolumeLimit(THandle aHandle, uint32_t* aValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1BeginVolumeLimit(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aValue
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyAvOpenhomeOrgVolume1EndVolumeLimit(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue);
/**
 * Set a callback to be run when the Volume state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgVolume1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SetPropertyVolumeChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Mute state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgVolume1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SetPropertyMuteChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Balance state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgVolume1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SetPropertyBalanceChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Fade state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgVolume1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SetPropertyFadeChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the VolumeLimit state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgVolume1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SetPropertyVolumeLimitChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the VolumeMax state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgVolume1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SetPropertyVolumeMaxChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the VolumeUnity state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgVolume1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SetPropertyVolumeUnityChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the VolumeSteps state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgVolume1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SetPropertyVolumeStepsChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the VolumeMilliDbPerStep state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgVolume1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SetPropertyVolumeMilliDbPerStepChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the BalanceMax state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgVolume1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SetPropertyBalanceMaxChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the FadeMax state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyAvOpenhomeOrgVolume1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyAvOpenhomeOrgVolume1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyAvOpenhomeOrgVolume1SetPropertyFadeMaxChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);

/**
 * Query the value of the Volume property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aVolume
 */
DllExport void CpProxyAvOpenhomeOrgVolume1PropertyVolume(THandle aHandle, uint32_t* aVolume);
/**
 * Query the value of the Mute property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aMute
 */
DllExport void CpProxyAvOpenhomeOrgVolume1PropertyMute(THandle aHandle, uint32_t* aMute);
/**
 * Query the value of the Balance property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aBalance
 */
DllExport void CpProxyAvOpenhomeOrgVolume1PropertyBalance(THandle aHandle, int32_t* aBalance);
/**
 * Query the value of the Fade property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aFade
 */
DllExport void CpProxyAvOpenhomeOrgVolume1PropertyFade(THandle aHandle, int32_t* aFade);
/**
 * Query the value of the VolumeLimit property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aVolumeLimit
 */
DllExport void CpProxyAvOpenhomeOrgVolume1PropertyVolumeLimit(THandle aHandle, uint32_t* aVolumeLimit);
/**
 * Query the value of the VolumeMax property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aVolumeMax
 */
DllExport void CpProxyAvOpenhomeOrgVolume1PropertyVolumeMax(THandle aHandle, uint32_t* aVolumeMax);
/**
 * Query the value of the VolumeUnity property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aVolumeUnity
 */
DllExport void CpProxyAvOpenhomeOrgVolume1PropertyVolumeUnity(THandle aHandle, uint32_t* aVolumeUnity);
/**
 * Query the value of the VolumeSteps property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aVolumeSteps
 */
DllExport void CpProxyAvOpenhomeOrgVolume1PropertyVolumeSteps(THandle aHandle, uint32_t* aVolumeSteps);
/**
 * Query the value of the VolumeMilliDbPerStep property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aVolumeMilliDbPerStep
 */
DllExport void CpProxyAvOpenhomeOrgVolume1PropertyVolumeMilliDbPerStep(THandle aHandle, uint32_t* aVolumeMilliDbPerStep);
/**
 * Query the value of the BalanceMax property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aBalanceMax
 */
DllExport void CpProxyAvOpenhomeOrgVolume1PropertyBalanceMax(THandle aHandle, uint32_t* aBalanceMax);
/**
 * Query the value of the FadeMax property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aFadeMax
 */
DllExport void CpProxyAvOpenhomeOrgVolume1PropertyFadeMax(THandle aHandle, uint32_t* aFadeMax);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_AVOPENHOMEORGVOLUME1_C

