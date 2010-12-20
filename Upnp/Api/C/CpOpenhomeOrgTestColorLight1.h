/**
 * Proxy for openhome.org:TestColorLight:1
 */
#ifndef HEADER_OPENHOMEORGTESTCOLORLIGHT1_C
#define HEADER_OPENHOMEORGTESTCOLORLIGHT1_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CpProxyOpenhomeOrgTestColorLight1
 * @ingroup Proxies
 * @{
 */

/**
 * Constructor.
 * Creates an instance of CpProxyOpenhomeOrgTestColorLight1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyOpenhomeOrgTestColorLight1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestColorLight1Create
 */
DllExport void CpProxyOpenhomeOrgTestColorLight1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestColorLight1Create
 * @param[out] aFriendlyName
 */
DllExport void CpProxyOpenhomeOrgTestColorLight1SyncGetName(THandle aHandle, char** aFriendlyName);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestColorLight1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestColorLight1BeginGetName(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestColorLight1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aFriendlyName
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestColorLight1EndGetName(THandle aHandle, ZappHandleAsync aAsync, char** aFriendlyName);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestColorLight1Create
 * @param[in]  aRed
 * @param[in]  aGreen
 * @param[in]  aBlue
 */
DllExport void CpProxyOpenhomeOrgTestColorLight1SyncSetColor(THandle aHandle, uint32_t aRed, uint32_t aGreen, uint32_t aBlue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestColorLight1Create
 * @param[in]  aRed
 * @param[in]  aGreen
 * @param[in]  aBlue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestColorLight1BeginSetColor(THandle aHandle, uint32_t aRed, uint32_t aGreen, uint32_t aBlue, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestColorLight1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestColorLight1EndSetColor(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestColorLight1Create
 * @param[out] aRed
 * @param[out] aGreen
 * @param[out] aBlue
 */
DllExport void CpProxyOpenhomeOrgTestColorLight1SyncGetColor(THandle aHandle, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestColorLight1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestColorLight1BeginGetColor(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestColorLight1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aRed
 * @param[out] aGreen
 * @param[out] aBlue
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestColorLight1EndGetColor(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestColorLight1Create
 * @param[out] aRed
 * @param[out] aGreen
 * @param[out] aBlue
 */
DllExport void CpProxyOpenhomeOrgTestColorLight1SyncGetMaxColors(THandle aHandle, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestColorLight1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyOpenhomeOrgTestColorLight1BeginGetMaxColors(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestColorLight1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aRed
 * @param[out] aGreen
 * @param[out] aBlue
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyOpenhomeOrgTestColorLight1EndGetMaxColors(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue);


/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_OPENHOMEORGTESTCOLORLIGHT1_C

