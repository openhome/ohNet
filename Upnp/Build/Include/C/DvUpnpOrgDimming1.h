/**
 * Provider for the upnp.org:Dimming:1 UPnP service
 */
#ifndef HEADER_DVUPNPORGDIMMING1_C
#define HEADER_DVUPNPORGDIMMING1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

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
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionSetLoadLevelTarget
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  anewLoadlevelTarget
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1SetLoadLevelTarget)(void* aPtr, uint32_t aVersion, uint32_t anewLoadlevelTarget);
/**
 * Callback which runs when the GetLoadLevelTarget action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetLoadLevelTarget
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aGetLoadlevelTarget
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1GetLoadLevelTarget)(void* aPtr, uint32_t aVersion, uint32_t* aGetLoadlevelTarget);
/**
 * Callback which runs when the GetLoadLevelStatus action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetLoadLevelStatus
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aretLoadlevelStatus
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1GetLoadLevelStatus)(void* aPtr, uint32_t aVersion, uint32_t* aretLoadlevelStatus);
/**
 * Callback which runs when the SetOnEffectLevel action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionSetOnEffectLevel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  anewOnEffectLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1SetOnEffectLevel)(void* aPtr, uint32_t aVersion, uint32_t anewOnEffectLevel);
/**
 * Callback which runs when the SetOnEffect action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionSetOnEffect
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  anewOnEffect
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1SetOnEffect)(void* aPtr, uint32_t aVersion, const char* anewOnEffect);
/**
 * Callback which runs when the GetOnEffectParameters action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetOnEffectParameters
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aretOnEffect
 * @param[out] aretOnEffectLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1GetOnEffectParameters)(void* aPtr, uint32_t aVersion, char** aretOnEffect, uint32_t* aretOnEffectLevel);
/**
 * Callback which runs when the StepUp action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionStepUp
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1StepUp)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the StepDown action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionStepDown
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1StepDown)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the StartRampUp action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionStartRampUp
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1StartRampUp)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the StartRampDown action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionStartRampDown
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1StartRampDown)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the StopRamp action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionStopRamp
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1StopRamp)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the StartRampToLevel action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionStartRampToLevel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  anewLoadLevelTarget
 * @param[in]  anewRampTime
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1StartRampToLevel)(void* aPtr, uint32_t aVersion, uint32_t anewLoadLevelTarget, uint32_t anewRampTime);
/**
 * Callback which runs when the SetStepDelta action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionSetStepDelta
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  anewStepDelta
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1SetStepDelta)(void* aPtr, uint32_t aVersion, uint32_t anewStepDelta);
/**
 * Callback which runs when the GetStepDelta action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetStepDelta
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aretStepDelta
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1GetStepDelta)(void* aPtr, uint32_t aVersion, uint32_t* aretStepDelta);
/**
 * Callback which runs when the SetRampRate action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionSetRampRate
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  anewRampRate
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1SetRampRate)(void* aPtr, uint32_t aVersion, uint32_t anewRampRate);
/**
 * Callback which runs when the GetRampRate action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetRampRate
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aretRampRate
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1GetRampRate)(void* aPtr, uint32_t aVersion, uint32_t* aretRampRate);
/**
 * Callback which runs when the PauseRamp action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionPauseRamp
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1PauseRamp)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the ResumeRamp action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionResumeRamp
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1ResumeRamp)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the GetIsRamping action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetIsRamping
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aretIsRamping
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1GetIsRamping)(void* aPtr, uint32_t aVersion, uint32_t* aretIsRamping);
/**
 * Callback which runs when the GetRampPaused action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetRampPaused
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aretRampPaused
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1GetRampPaused)(void* aPtr, uint32_t aVersion, uint32_t* aretRampPaused);
/**
 * Callback which runs when the GetRampTime action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgDimming1EnableActionGetRampTime
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aretRampTime
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDimming1GetRampTime)(void* aPtr, uint32_t aVersion, uint32_t* aretRampTime);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderUpnpOrgDimming1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 */
DllExport void DvProviderUpnpOrgDimming1Destroy(THandle aProvider);

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
DllExport void DvProviderUpnpOrgDimming1EnableActionSetLoadLevelTarget(THandle aProvider, CallbackDimming1SetLoadLevelTarget aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionGetLoadLevelTarget(THandle aProvider, CallbackDimming1GetLoadLevelTarget aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionGetLoadLevelStatus(THandle aProvider, CallbackDimming1GetLoadLevelStatus aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionSetOnEffectLevel(THandle aProvider, CallbackDimming1SetOnEffectLevel aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionSetOnEffect(THandle aProvider, CallbackDimming1SetOnEffect aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionGetOnEffectParameters(THandle aProvider, CallbackDimming1GetOnEffectParameters aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionStepUp(THandle aProvider, CallbackDimming1StepUp aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionStepDown(THandle aProvider, CallbackDimming1StepDown aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionStartRampUp(THandle aProvider, CallbackDimming1StartRampUp aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionStartRampDown(THandle aProvider, CallbackDimming1StartRampDown aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionStopRamp(THandle aProvider, CallbackDimming1StopRamp aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionStartRampToLevel(THandle aProvider, CallbackDimming1StartRampToLevel aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionSetStepDelta(THandle aProvider, CallbackDimming1SetStepDelta aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionGetStepDelta(THandle aProvider, CallbackDimming1GetStepDelta aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionSetRampRate(THandle aProvider, CallbackDimming1SetRampRate aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionGetRampRate(THandle aProvider, CallbackDimming1GetRampRate aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionPauseRamp(THandle aProvider, CallbackDimming1PauseRamp aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionResumeRamp(THandle aProvider, CallbackDimming1ResumeRamp aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionGetIsRamping(THandle aProvider, CallbackDimming1GetIsRamping aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionGetRampPaused(THandle aProvider, CallbackDimming1GetRampPaused aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgDimming1EnableActionGetRampTime(THandle aProvider, CallbackDimming1GetRampTime aCallback, void* aPtr);

/**
 * Set the value of the LoadLevelStatus property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderUpnpOrgDimming1SetPropertyLoadLevelStatus(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the LoadLevelStatus property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderUpnpOrgDimming1GetPropertyLoadLevelStatus(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the StepDelta property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderUpnpOrgDimming1SetPropertyStepDelta(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the StepDelta property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderUpnpOrgDimming1GetPropertyStepDelta(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the RampRate property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderUpnpOrgDimming1SetPropertyRampRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the RampRate property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderUpnpOrgDimming1GetPropertyRampRate(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the IsRamping property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderUpnpOrgDimming1SetPropertyIsRamping(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the IsRamping property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderUpnpOrgDimming1GetPropertyIsRamping(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the RampPaused property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderUpnpOrgDimming1SetPropertyRampPaused(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the RampPaused property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgDimming1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderUpnpOrgDimming1GetPropertyRampPaused(THandle aProvider, uint32_t* aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGDIMMING1_C

