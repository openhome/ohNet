/**
 * Proxy for linn.co.uk:Configuration:1
 */
#ifndef HEADER_LINNCOUKCONFIGURATION1_C
#define HEADER_LINNCOUKCONFIGURATION1_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyLinnCoUkConfiguration1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyLinnCoUkConfiguration1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkConfiguration1Create
 */
DllExport void CpProxyLinnCoUkConfiguration1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkConfiguration1Create
 * @param[out] aaConfigurationXml
 */
DllExport void CpProxyLinnCoUkConfiguration1SyncConfigurationXml(THandle aHandle, char** aaConfigurationXml);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkConfiguration1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkConfiguration1BeginConfigurationXml(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkConfiguration1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaConfigurationXml
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkConfiguration1EndConfigurationXml(THandle aHandle, ZappHandleAsync aAsync, char** aaConfigurationXml);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkConfiguration1Create
 * @param[out] aaParameterXml
 */
DllExport void CpProxyLinnCoUkConfiguration1SyncParameterXml(THandle aHandle, char** aaParameterXml);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkConfiguration1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkConfiguration1BeginParameterXml(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkConfiguration1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaParameterXml
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkConfiguration1EndParameterXml(THandle aHandle, ZappHandleAsync aAsync, char** aaParameterXml);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkConfiguration1Create
 * @param[in]  aaTarget
 * @param[in]  aaName
 * @param[in]  aaValue
 */
DllExport void CpProxyLinnCoUkConfiguration1SyncSetParameter(THandle aHandle, const char* aaTarget, const char* aaName, const char* aaValue);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkConfiguration1Create
 * @param[in]  aaTarget
 * @param[in]  aaName
 * @param[in]  aaValue
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkConfiguration1BeginSetParameter(THandle aHandle, const char* aaTarget, const char* aaName, const char* aaValue, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkConfiguration1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkConfiguration1EndSetParameter(THandle aHandle, ZappHandleAsync aAsync);
/**
 * Set a callback to be run when the ConfigurationXml state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkConfiguration1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkConfiguration1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkConfiguration1SetPropertyConfigurationXmlChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the ParameterXml state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkConfiguration1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkConfiguration1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkConfiguration1SetPropertyParameterXmlChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the ConfigurationXml property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aConfigurationXml
 */
DllExport void CpProxyLinnCoUkConfiguration1PropertyConfigurationXml(THandle aHandle, char** aConfigurationXml);
/**
 * Query the value of the ParameterXml property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aParameterXml
 */
DllExport void CpProxyLinnCoUkConfiguration1PropertyParameterXml(THandle aHandle, char** aParameterXml);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_LINNCOUKCONFIGURATION1_C

