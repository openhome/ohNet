/**
 * Provider for the upnp.org:Dimming:1 UPnP service
 */
#ifndef HEADER_DVUPNPORGDIMMING1_C
#define HEADER_DVUPNPORGDIMMING1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderUpnpOrgDimming1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the SetLoadLevelTarget action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionSetLoadLevelTarget
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  anewLoadlevelTarget
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1SetLoadLevelTarget)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t anewLoadlevelTarget);
/**
 * Callback which runs when the GetLoadLevelTarget action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetLoadLevelTarget
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aGetLoadlevelTarget
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1GetLoadLevelTarget)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aGetLoadlevelTarget);
/**
 * Callback which runs when the GetLoadLevelStatus action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetLoadLevelStatus
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aretLoadlevelStatus
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1GetLoadLevelStatus)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aretLoadlevelStatus);
/**
 * Callback which runs when the SetOnEffectLevel action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionSetOnEffectLevel
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  anewOnEffectLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1SetOnEffectLevel)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t anewOnEffectLevel);
/**
 * Callback which runs when the SetOnEffect action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionSetOnEffect
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  anewOnEffect
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1SetOnEffect)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* anewOnEffect);
/**
 * Callback which runs when the GetOnEffectParameters action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetOnEffectParameters
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aretOnEffect
 * @param[out] aretOnEffectLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1GetOnEffectParameters)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aretOnEffect, uint32_t* aretOnEffectLevel);
/**
 * Callback which runs when the StepUp action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionStepUp
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1StepUp)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the StepDown action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionStepDown
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1StepDown)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the StartRampUp action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionStartRampUp
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1StartRampUp)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the StartRampDown action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionStartRampDown
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1StartRampDown)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the StopRamp action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionStopRamp
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1StopRamp)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the StartRampToLevel action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionStartRampToLevel
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  anewLoadLevelTarget
 * @param[in]  anewRampTime
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1StartRampToLevel)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t anewLoadLevelTarget, uint32_t anewRampTime);
/**
 * Callback which runs when the SetStepDelta action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionSetStepDelta
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  anewStepDelta
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1SetStepDelta)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t anewStepDelta);
/**
 * Callback which runs when the GetStepDelta action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetStepDelta
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aretStepDelta
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1GetStepDelta)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aretStepDelta);
/**
 * Callback which runs when the SetRampRate action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionSetRampRate
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  anewRampRate
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1SetRampRate)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t anewRampRate);
/**
 * Callback which runs when the GetRampRate action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetRampRate
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aretRampRate
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1GetRampRate)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aretRampRate);
/**
 * Callback which runs when the PauseRamp action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionPauseRamp
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1PauseRamp)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the ResumeRamp action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionResumeRamp
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1ResumeRamp)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the GetIsRamping action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetIsRamping
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aretIsRamping
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1GetIsRamping)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aretIsRamping);
/**
 * Callback which runs when the GetRampPaused action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetRampPaused
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aretRampPaused
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1GetRampPaused)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aretRampPaused);
/**
 * Callback which runs when the GetRampTime action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetRampTime
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aretRampTime
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackDimming1GetRampTime)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aretRampTime);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderUpnpOrgDimming1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1Destroy(THandle aProvider);

/**
 * Enable the LoadLevelStatus property.
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnablePropertyLoadLevelStatus(THandle aProvider);
/**
 * Enable the StepDelta property.
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnablePropertyStepDelta(THandle aProvider);
/**
 * Enable the RampRate property.
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnablePropertyRampRate(THandle aProvider);
/**
 * Enable the IsRamping property.
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnablePropertyIsRamping(THandle aProvider);
/**
 * Enable the RampPaused property.
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnablePropertyRampPaused(THandle aProvider);

/**
 * Register a callback for the action SetLoadLevelTarget
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionSetLoadLevelTarget(THandle aProvider, CallbackDimming1SetLoadLevelTarget aCallback, void* aPtr);
/**
 * Register a callback for the action GetLoadLevelTarget
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionGetLoadLevelTarget(THandle aProvider, CallbackDimming1GetLoadLevelTarget aCallback, void* aPtr);
/**
 * Register a callback for the action GetLoadLevelStatus
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionGetLoadLevelStatus(THandle aProvider, CallbackDimming1GetLoadLevelStatus aCallback, void* aPtr);
/**
 * Register a callback for the action SetOnEffectLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionSetOnEffectLevel(THandle aProvider, CallbackDimming1SetOnEffectLevel aCallback, void* aPtr);
/**
 * Register a callback for the action SetOnEffect
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionSetOnEffect(THandle aProvider, CallbackDimming1SetOnEffect aCallback, void* aPtr);
/**
 * Register a callback for the action GetOnEffectParameters
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionGetOnEffectParameters(THandle aProvider, CallbackDimming1GetOnEffectParameters aCallback, void* aPtr);
/**
 * Register a callback for the action StepUp
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionStepUp(THandle aProvider, CallbackDimming1StepUp aCallback, void* aPtr);
/**
 * Register a callback for the action StepDown
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionStepDown(THandle aProvider, CallbackDimming1StepDown aCallback, void* aPtr);
/**
 * Register a callback for the action StartRampUp
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionStartRampUp(THandle aProvider, CallbackDimming1StartRampUp aCallback, void* aPtr);
/**
 * Register a callback for the action StartRampDown
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionStartRampDown(THandle aProvider, CallbackDimming1StartRampDown aCallback, void* aPtr);
/**
 * Register a callback for the action StopRamp
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionStopRamp(THandle aProvider, CallbackDimming1StopRamp aCallback, void* aPtr);
/**
 * Register a callback for the action StartRampToLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionStartRampToLevel(THandle aProvider, CallbackDimming1StartRampToLevel aCallback, void* aPtr);
/**
 * Register a callback for the action SetStepDelta
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionSetStepDelta(THandle aProvider, CallbackDimming1SetStepDelta aCallback, void* aPtr);
/**
 * Register a callback for the action GetStepDelta
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionGetStepDelta(THandle aProvider, CallbackDimming1GetStepDelta aCallback, void* aPtr);
/**
 * Register a callback for the action SetRampRate
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionSetRampRate(THandle aProvider, CallbackDimming1SetRampRate aCallback, void* aPtr);
/**
 * Register a callback for the action GetRampRate
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionGetRampRate(THandle aProvider, CallbackDimming1GetRampRate aCallback, void* aPtr);
/**
 * Register a callback for the action PauseRamp
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionPauseRamp(THandle aProvider, CallbackDimming1PauseRamp aCallback, void* aPtr);
/**
 * Register a callback for the action ResumeRamp
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionResumeRamp(THandle aProvider, CallbackDimming1ResumeRamp aCallback, void* aPtr);
/**
 * Register a callback for the action GetIsRamping
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionGetIsRamping(THandle aProvider, CallbackDimming1GetIsRamping aCallback, void* aPtr);
/**
 * Register a callback for the action GetRampPaused
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionGetRampPaused(THandle aProvider, CallbackDimming1GetRampPaused aCallback, void* aPtr);
/**
 * Register a callback for the action GetRampTime
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1EnableActionGetRampTime(THandle aProvider, CallbackDimming1GetRampTime aCallback, void* aPtr);

/**
 * Set the value of the LoadLevelStatus property
 *
 * Can only be called if DvProviderUpnpOrgDimming1EnablePropertyLoadLevelStatus has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgDimming1SetPropertyLoadLevelStatus(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the LoadLevelStatus property
 *
 * Can only be called if DvProviderUpnpOrgDimming1EnablePropertyLoadLevelStatus has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1GetPropertyLoadLevelStatus(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the StepDelta property
 *
 * Can only be called if DvProviderUpnpOrgDimming1EnablePropertyStepDelta has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgDimming1SetPropertyStepDelta(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the StepDelta property
 *
 * Can only be called if DvProviderUpnpOrgDimming1EnablePropertyStepDelta has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1GetPropertyStepDelta(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the RampRate property
 *
 * Can only be called if DvProviderUpnpOrgDimming1EnablePropertyRampRate has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgDimming1SetPropertyRampRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the RampRate property
 *
 * Can only be called if DvProviderUpnpOrgDimming1EnablePropertyRampRate has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1GetPropertyRampRate(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the IsRamping property
 *
 * Can only be called if DvProviderUpnpOrgDimming1EnablePropertyIsRamping has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgDimming1SetPropertyIsRamping(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the IsRamping property
 *
 * Can only be called if DvProviderUpnpOrgDimming1EnablePropertyIsRamping has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1GetPropertyIsRamping(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the RampPaused property
 *
 * Can only be called if DvProviderUpnpOrgDimming1EnablePropertyRampPaused has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgDimming1SetPropertyRampPaused(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the RampPaused property
 *
 * Can only be called if DvProviderUpnpOrgDimming1EnablePropertyRampPaused has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderUpnpOrgDimming1GetPropertyRampPaused(THandle aProvider, uint32_t* aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGDIMMING1_C

