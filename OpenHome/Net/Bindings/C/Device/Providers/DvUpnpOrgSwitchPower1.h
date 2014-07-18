/**
 * Provider for the upnp.org:SwitchPower:1 UPnP service
 */
#ifndef HEADER_DVUPNPORGSWITCHPOWER1_C
#define HEADER_DVUPNPORGSWITCHPOWER1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderUpnpOrgSwitchPower1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the SetTarget action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgSwitchPower1EnableActionSetTarget
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  anewTargetValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackSwitchPower1SetTarget)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t anewTargetValue);
/**
 * Callback which runs when the GetTarget action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgSwitchPower1EnableActionGetTarget
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aRetTargetValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackSwitchPower1GetTarget)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aRetTargetValue);
/**
 * Callback which runs when the GetStatus action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgSwitchPower1EnableActionGetStatus
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aResultStatus
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackSwitchPower1GetStatus)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aResultStatus);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderUpnpOrgSwitchPower1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgSwitchPower1Create
 */
DllExport void STDCALL DvProviderUpnpOrgSwitchPower1Destroy(THandle aProvider);

/**
 * Enable the Status property.
 */
DllExport void STDCALL DvProviderUpnpOrgSwitchPower1EnablePropertyStatus(THandle aProvider);

/**
 * Register a callback for the action SetTarget
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgSwitchPower1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgSwitchPower1EnableActionSetTarget(THandle aProvider, CallbackSwitchPower1SetTarget aCallback, void* aPtr);
/**
 * Register a callback for the action GetTarget
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgSwitchPower1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgSwitchPower1EnableActionGetTarget(THandle aProvider, CallbackSwitchPower1GetTarget aCallback, void* aPtr);
/**
 * Register a callback for the action GetStatus
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgSwitchPower1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgSwitchPower1EnableActionGetStatus(THandle aProvider, CallbackSwitchPower1GetStatus aCallback, void* aPtr);

/**
 * Set the value of the Status property
 *
 * Can only be called if DvProviderUpnpOrgSwitchPower1EnablePropertyStatus has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgSwitchPower1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgSwitchPower1SetPropertyStatus(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Status property
 *
 * Can only be called if DvProviderUpnpOrgSwitchPower1EnablePropertyStatus has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgSwitchPower1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderUpnpOrgSwitchPower1GetPropertyStatus(THandle aProvider, uint32_t* aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGSWITCHPOWER1_C

