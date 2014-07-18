/**
 * Provider for the av.openhome.org:NetworkMonitor:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGNETWORKMONITOR1_C
#define HEADER_DVAVOPENHOMEORGNETWORKMONITOR1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderAvOpenhomeOrgNetworkMonitor1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Name action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgNetworkMonitor1EnableActionName
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackNetworkMonitor1Name)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aName);
/**
 * Callback which runs when the Ports action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgNetworkMonitor1EnableActionPorts
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aSender
 * @param[out] aReceiver
 * @param[out] aResults
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackNetworkMonitor1Ports)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aSender, uint32_t* aReceiver, uint32_t* aResults);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgNetworkMonitor1Create
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1Destroy(THandle aProvider);

/**
 * Enable the Name property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertyName(THandle aProvider);
/**
 * Enable the Sender property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertySender(THandle aProvider);
/**
 * Enable the Receiver property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertyReceiver(THandle aProvider);
/**
 * Enable the Results property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertyResults(THandle aProvider);

/**
 * Register a callback for the action Name
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgNetworkMonitor1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1EnableActionName(THandle aProvider, CallbackNetworkMonitor1Name aCallback, void* aPtr);
/**
 * Register a callback for the action Ports
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgNetworkMonitor1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1EnableActionPorts(THandle aProvider, CallbackNetworkMonitor1Ports aCallback, void* aPtr);

/**
 * Set the value of the Name property
 *
 * Can only be called if DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertyName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgNetworkMonitor1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1SetPropertyName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Name property
 *
 * Can only be called if DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertyName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgNetworkMonitor1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1GetPropertyName(THandle aProvider, char** aValue);
/**
 * Set the value of the Sender property
 *
 * Can only be called if DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertySender has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgNetworkMonitor1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1SetPropertySender(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Sender property
 *
 * Can only be called if DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertySender has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgNetworkMonitor1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1GetPropertySender(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Receiver property
 *
 * Can only be called if DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertyReceiver has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgNetworkMonitor1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1SetPropertyReceiver(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Receiver property
 *
 * Can only be called if DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertyReceiver has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgNetworkMonitor1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1GetPropertyReceiver(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Results property
 *
 * Can only be called if DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertyResults has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgNetworkMonitor1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1SetPropertyResults(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Results property
 *
 * Can only be called if DvProviderAvOpenhomeOrgNetworkMonitor1EnablePropertyResults has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgNetworkMonitor1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgNetworkMonitor1GetPropertyResults(THandle aProvider, uint32_t* aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGNETWORKMONITOR1_C

