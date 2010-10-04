/**
 * Proxy for upnp.org:RenderingControl:2
 */
#ifndef HEADER_UPNPORGRENDERINGCONTROL2_C
#define HEADER_UPNPORGRENDERINGCONTROL2_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyUpnpOrgRenderingControl2 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyUpnpOrgRenderingControl2Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 */
DllExport void CpProxyUpnpOrgRenderingControl2Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentPresetNameList
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncListPresets(THandle aHandle, uint32_t aInstanceID, char** aCurrentPresetNameList);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginListPresets(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentPresetNameList
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndListPresets(THandle aHandle, ZappHandleAsync aAsync, char** aCurrentPresetNameList);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aPresetName
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSelectPreset(THandle aHandle, uint32_t aInstanceID, const char* aPresetName);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aPresetName
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSelectPreset(THandle aHandle, uint32_t aInstanceID, const char* aPresetName, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSelectPreset(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentBrightness
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBrightness);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetBrightness(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentBrightness
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetBrightness(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentBrightness);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredBrightness
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBrightness);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredBrightness
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetBrightness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBrightness, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetBrightness(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentContrast
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentContrast);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetContrast(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentContrast
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetContrast(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentContrast);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredContrast
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredContrast);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredContrast
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetContrast(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredContrast, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetContrast(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentSharpness
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentSharpness);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetSharpness(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentSharpness
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetSharpness(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentSharpness);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredSharpness
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredSharpness);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredSharpness
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetSharpness(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredSharpness, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetSharpness(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentRedVideoGain
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentRedVideoGain);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetRedVideoGain(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentRedVideoGain
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetRedVideoGain(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentRedVideoGain);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredRedVideoGain
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredRedVideoGain
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetRedVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetRedVideoGain(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentGreenVideoGain
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoGain);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentGreenVideoGain
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetGreenVideoGain(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentGreenVideoGain);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredGreenVideoGain
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredGreenVideoGain
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetGreenVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetGreenVideoGain(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentBlueVideoGain
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoGain);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentBlueVideoGain
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetBlueVideoGain(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentBlueVideoGain);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredBlueVideoGain
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredBlueVideoGain
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetBlueVideoGain(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetBlueVideoGain(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentRedVideoBlackLevel
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentRedVideoBlackLevel);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentRedVideoBlackLevel
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetRedVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentRedVideoBlackLevel);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredRedVideoBlackLevel
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredRedVideoBlackLevel
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetRedVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetRedVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentGreenVideoBlackLevel
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoBlackLevel);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentGreenVideoBlackLevel
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetGreenVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentGreenVideoBlackLevel);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredGreenVideoBlackLevel
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredGreenVideoBlackLevel
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetGreenVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetGreenVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentBlueVideoBlackLevel
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoBlackLevel);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentBlueVideoBlackLevel
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetBlueVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentBlueVideoBlackLevel);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredBlueVideoBlackLevel
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredBlueVideoBlackLevel
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetBlueVideoBlackLevel(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetBlueVideoBlackLevel(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentColorTemperature
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t* aCurrentColorTemperature);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetColorTemperature(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentColorTemperature
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetColorTemperature(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentColorTemperature);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredColorTemperature
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredColorTemperature);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredColorTemperature
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetColorTemperature(THandle aHandle, uint32_t aInstanceID, uint32_t aDesiredColorTemperature, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetColorTemperature(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentHorizontalKeystone
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t* aCurrentHorizontalKeystone);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentHorizontalKeystone
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetHorizontalKeystone(THandle aHandle, ZappHandleAsync aAsync, int32_t* aCurrentHorizontalKeystone);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredHorizontalKeystone
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredHorizontalKeystone
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetHorizontalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetHorizontalKeystone(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentVerticalKeystone
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t* aCurrentVerticalKeystone);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentVerticalKeystone
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetVerticalKeystone(THandle aHandle, ZappHandleAsync aAsync, int32_t* aCurrentVerticalKeystone);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredVerticalKeystone
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aDesiredVerticalKeystone
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetVerticalKeystone(THandle aHandle, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetVerticalKeystone(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aCurrentMute
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentMute);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentMute
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetMute(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentMute);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredMute
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredMute
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetMute(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetMute(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aCurrentVolume
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentVolume);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentVolume
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetVolume(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentVolume);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredVolume
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredVolume
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetVolume(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetVolume(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aCurrentVolume
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t* aCurrentVolume);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentVolume
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetVolumeDB(THandle aHandle, ZappHandleAsync aAsync, int32_t* aCurrentVolume);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredVolume
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredVolume
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetVolumeDB(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetVolumeDB(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aMinValue
 * @param[out] aMaxValue
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetVolumeDBRange(THandle aHandle, uint32_t aInstanceID, const char* aChannel, int32_t* aMinValue, int32_t* aMaxValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetVolumeDBRange(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aMinValue
 * @param[out] aMaxValue
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetVolumeDBRange(THandle aHandle, ZappHandleAsync aAsync, int32_t* aMinValue, int32_t* aMaxValue);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aCurrentLoudness
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentLoudness);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentLoudness
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetLoudness(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCurrentLoudness);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredLoudness
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredLoudness
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetLoudness(THandle aHandle, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetLoudness(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aStateVariableList
 * @param[out] aStateVariableValuePairs
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncGetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aStateVariableList, char** aStateVariableValuePairs);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aStateVariableList
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginGetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aStateVariableList, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aStateVariableValuePairs
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndGetStateVariables(THandle aHandle, ZappHandleAsync aAsync, char** aStateVariableValuePairs);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aRenderingControlUDN
 * @param[in]  aServiceType
 * @param[in]  aServiceId
 * @param[in]  aStateVariableValuePairs
 * @param[out] aStateVariableList
 */
DllExport void CpProxyUpnpOrgRenderingControl2SyncSetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aRenderingControlUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, char** aStateVariableList);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aInstanceID
 * @param[in]  aRenderingControlUDN
 * @param[in]  aServiceType
 * @param[in]  aServiceId
 * @param[in]  aStateVariableValuePairs
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2BeginSetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aRenderingControlUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aStateVariableList
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgRenderingControl2EndSetStateVariables(THandle aHandle, ZappHandleAsync aAsync, char** aStateVariableList);
/**
 * Set a callback to be run when the LastChange state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyUpnpOrgRenderingControl2 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgRenderingControl2Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgRenderingControl2SetPropertyLastChangeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the LastChange property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aLastChange
 */
DllExport void CpProxyUpnpOrgRenderingControl2PropertyLastChange(THandle aHandle, char** aLastChange);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_UPNPORGRENDERINGCONTROL2_C

