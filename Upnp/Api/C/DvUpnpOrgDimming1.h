#ifndef HEADER_DVUPNPORGDIMMING1_C
#define HEADER_DVUPNPORGDIMMING1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackDimming1SetLoadLevelTarget)(void* aPtr, uint32_t aVersion, uint32_t anewLoadlevelTarget);
typedef int32_t (*CallbackDimming1GetLoadLevelTarget)(void* aPtr, uint32_t aVersion, uint32_t* aGetLoadlevelTarget);
typedef int32_t (*CallbackDimming1GetLoadLevelStatus)(void* aPtr, uint32_t aVersion, uint32_t* aretLoadlevelStatus);
typedef int32_t (*CallbackDimming1SetOnEffectLevel)(void* aPtr, uint32_t aVersion, uint32_t anewOnEffectLevel);
typedef int32_t (*CallbackDimming1SetOnEffect)(void* aPtr, uint32_t aVersion, const char* anewOnEffect);
typedef int32_t (*CallbackDimming1GetOnEffectParameters)(void* aPtr, uint32_t aVersion, char** aretOnEffect, uint32_t* aretOnEffectLevel);
typedef int32_t (*CallbackDimming1StepUp)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackDimming1StepDown)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackDimming1StartRampUp)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackDimming1StartRampDown)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackDimming1StopRamp)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackDimming1StartRampToLevel)(void* aPtr, uint32_t aVersion, uint32_t anewLoadLevelTarget, uint32_t anewRampTime);
typedef int32_t (*CallbackDimming1SetStepDelta)(void* aPtr, uint32_t aVersion, uint32_t anewStepDelta);
typedef int32_t (*CallbackDimming1GetStepDelta)(void* aPtr, uint32_t aVersion, uint32_t* aretStepDelta);
typedef int32_t (*CallbackDimming1SetRampRate)(void* aPtr, uint32_t aVersion, uint32_t anewRampRate);
typedef int32_t (*CallbackDimming1GetRampRate)(void* aPtr, uint32_t aVersion, uint32_t* aretRampRate);
typedef int32_t (*CallbackDimming1PauseRamp)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackDimming1ResumeRamp)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackDimming1GetIsRamping)(void* aPtr, uint32_t aVersion, uint32_t* aretIsRamping);
typedef int32_t (*CallbackDimming1GetRampPaused)(void* aPtr, uint32_t aVersion, uint32_t* aretRampPaused);
typedef int32_t (*CallbackDimming1GetRampTime)(void* aPtr, uint32_t aVersion, uint32_t* aretRampTime);

DllExport THandle DvProviderUpnpOrgDimming1Create(DvDeviceC aDevice);
DllExport void DvProviderUpnpOrgDimming1Destroy(THandle aProvider);

DllExport void DvProviderUpnpOrgDimming1EnableActionSetLoadLevelTarget(THandle aProvider, CallbackDimming1SetLoadLevelTarget aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionGetLoadLevelTarget(THandle aProvider, CallbackDimming1GetLoadLevelTarget aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionGetLoadLevelStatus(THandle aProvider, CallbackDimming1GetLoadLevelStatus aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionSetOnEffectLevel(THandle aProvider, CallbackDimming1SetOnEffectLevel aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionSetOnEffect(THandle aProvider, CallbackDimming1SetOnEffect aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionGetOnEffectParameters(THandle aProvider, CallbackDimming1GetOnEffectParameters aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionStepUp(THandle aProvider, CallbackDimming1StepUp aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionStepDown(THandle aProvider, CallbackDimming1StepDown aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionStartRampUp(THandle aProvider, CallbackDimming1StartRampUp aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionStartRampDown(THandle aProvider, CallbackDimming1StartRampDown aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionStopRamp(THandle aProvider, CallbackDimming1StopRamp aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionStartRampToLevel(THandle aProvider, CallbackDimming1StartRampToLevel aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionSetStepDelta(THandle aProvider, CallbackDimming1SetStepDelta aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionGetStepDelta(THandle aProvider, CallbackDimming1GetStepDelta aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionSetRampRate(THandle aProvider, CallbackDimming1SetRampRate aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionGetRampRate(THandle aProvider, CallbackDimming1GetRampRate aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionPauseRamp(THandle aProvider, CallbackDimming1PauseRamp aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionResumeRamp(THandle aProvider, CallbackDimming1ResumeRamp aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionGetIsRamping(THandle aProvider, CallbackDimming1GetIsRamping aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionGetRampPaused(THandle aProvider, CallbackDimming1GetRampPaused aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgDimming1EnableActionGetRampTime(THandle aProvider, CallbackDimming1GetRampTime aCallback, void* aPtr);

DllExport int32_t DvProviderUpnpOrgDimming1SetPropertyLoadLevelStatus(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgDimming1GetPropertyLoadLevelStatus(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderUpnpOrgDimming1SetPropertyStepDelta(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgDimming1GetPropertyStepDelta(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderUpnpOrgDimming1SetPropertyRampRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgDimming1GetPropertyRampRate(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderUpnpOrgDimming1SetPropertyIsRamping(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgDimming1GetPropertyIsRamping(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderUpnpOrgDimming1SetPropertyRampPaused(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgDimming1GetPropertyRampPaused(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGDIMMING1_C

