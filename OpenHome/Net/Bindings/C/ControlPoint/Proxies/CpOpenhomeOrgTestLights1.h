/**
 * Proxy for openhome.org:TestLights:1
 */
#ifndef HEADER_OPENHOMEORGTESTLIGHTS1_C
#define HEADER_OPENHOMEORGTESTLIGHTS1_C

#include <OpenHome/OsTypes.h>
#include <OpenHome/Defines.h>
#include <OpenHome/Net/C/Async.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CpProxyOpenhomeOrgTestLights1
 * @ingroup Proxies
 * @{
 */

/**
 * Constructor.
 * Creates an instance of CpProxyOpenhomeOrgTestLights1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle STDCALL CpProxyOpenhomeOrgTestLights1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 */
DllExport void STDCALL CpProxyOpenhomeOrgTestLights1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[out] aCount
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgTestLights1SyncGetCount(THandle aHandle, uint32_t* aCount);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyOpenhomeOrgTestLights1BeginGetCount(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCount
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgTestLights1EndGetCount(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCount);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aIndex
 * @param[out] aRoomName
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgTestLights1SyncGetRoom(THandle aHandle, uint32_t aIndex, char** aRoomName);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aIndex
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyOpenhomeOrgTestLights1BeginGetRoom(THandle aHandle, uint32_t aIndex, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aRoomName
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgTestLights1EndGetRoom(THandle aHandle, OhNetHandleAsync aAsync, char** aRoomName);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aIndex
 * @param[out] aFriendlyName
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgTestLights1SyncGetName(THandle aHandle, uint32_t aIndex, char** aFriendlyName);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aIndex
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyOpenhomeOrgTestLights1BeginGetName(THandle aHandle, uint32_t aIndex, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aFriendlyName
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgTestLights1EndGetName(THandle aHandle, OhNetHandleAsync aAsync, char** aFriendlyName);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aIndex
 * @param[out] aX
 * @param[out] aY
 * @param[out] aZ
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgTestLights1SyncGetPosition(THandle aHandle, uint32_t aIndex, uint32_t* aX, uint32_t* aY, uint32_t* aZ);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aIndex
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyOpenhomeOrgTestLights1BeginGetPosition(THandle aHandle, uint32_t aIndex, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aX
 * @param[out] aY
 * @param[out] aZ
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgTestLights1EndGetPosition(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aX, uint32_t* aY, uint32_t* aZ);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aIndex
 * @param[in]  aColor
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgTestLights1SyncSetColor(THandle aHandle, uint32_t aIndex, uint32_t aColor);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aIndex
 * @param[in]  aColor
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyOpenhomeOrgTestLights1BeginSetColor(THandle aHandle, uint32_t aIndex, uint32_t aColor, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgTestLights1EndSetColor(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aIndex
 * @param[out] aColor
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgTestLights1SyncGetColor(THandle aHandle, uint32_t aIndex, uint32_t* aColor);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aIndex
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyOpenhomeOrgTestLights1BeginGetColor(THandle aHandle, uint32_t aIndex, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aColor
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgTestLights1EndGetColor(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aColor);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aColor
 * @param[out] aBrightness
 * @param[out] aRed
 * @param[out] aGreen
 * @param[out] aBlue
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgTestLights1SyncGetColorComponents(THandle aHandle, uint32_t aColor, uint32_t* aBrightness, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aColor
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyOpenhomeOrgTestLights1BeginGetColorComponents(THandle aHandle, uint32_t aColor, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgTestLights1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aBrightness
 * @param[out] aRed
 * @param[out] aGreen
 * @param[out] aBlue
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgTestLights1EndGetColorComponents(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aBrightness, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue);


/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_OPENHOMEORGTESTLIGHTS1_C

