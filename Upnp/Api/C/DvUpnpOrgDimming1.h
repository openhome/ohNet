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

DllExport THandle DvServiceUpnpOrgDimming1Create(DvDeviceC aDevice);
DllExport void DvServiceUpnpOrgDimming1Destroy(THandle aService);

DllExport void DvServiceUpnpOrgDimming1EnableActionSetLoadLevelTarget(THandle aService, CallbackDimming1SetLoadLevelTarget aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionGetLoadLevelTarget(THandle aService, CallbackDimming1GetLoadLevelTarget aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionGetLoadLevelStatus(THandle aService, CallbackDimming1GetLoadLevelStatus aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionSetOnEffectLevel(THandle aService, CallbackDimming1SetOnEffectLevel aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionSetOnEffect(THandle aService, CallbackDimming1SetOnEffect aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionGetOnEffectParameters(THandle aService, CallbackDimming1GetOnEffectParameters aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionStepUp(THandle aService, CallbackDimming1StepUp aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionStepDown(THandle aService, CallbackDimming1StepDown aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionStartRampUp(THandle aService, CallbackDimming1StartRampUp aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionStartRampDown(THandle aService, CallbackDimming1StartRampDown aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionStopRamp(THandle aService, CallbackDimming1StopRamp aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionStartRampToLevel(THandle aService, CallbackDimming1StartRampToLevel aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionSetStepDelta(THandle aService, CallbackDimming1SetStepDelta aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionGetStepDelta(THandle aService, CallbackDimming1GetStepDelta aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionSetRampRate(THandle aService, CallbackDimming1SetRampRate aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionGetRampRate(THandle aService, CallbackDimming1GetRampRate aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionPauseRamp(THandle aService, CallbackDimming1PauseRamp aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionResumeRamp(THandle aService, CallbackDimming1ResumeRamp aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionGetIsRamping(THandle aService, CallbackDimming1GetIsRamping aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionGetRampPaused(THandle aService, CallbackDimming1GetRampPaused aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgDimming1EnableActionGetRampTime(THandle aService, CallbackDimming1GetRampTime aCallback, void* aPtr);

DllExport int32_t DvServiceUpnpOrgDimming1SetPropertyLoadLevelStatus(THandle aService, uint32_t aValue);
DllExport void DvServiceUpnpOrgDimming1GetPropertyLoadLevelStatus(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceUpnpOrgDimming1SetPropertyStepDelta(THandle aService, uint32_t aValue);
DllExport void DvServiceUpnpOrgDimming1GetPropertyStepDelta(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceUpnpOrgDimming1SetPropertyRampRate(THandle aService, uint32_t aValue);
DllExport void DvServiceUpnpOrgDimming1GetPropertyRampRate(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceUpnpOrgDimming1SetPropertyIsRamping(THandle aService, uint32_t aValue);
DllExport void DvServiceUpnpOrgDimming1GetPropertyIsRamping(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceUpnpOrgDimming1SetPropertyRampPaused(THandle aService, uint32_t aValue);
DllExport void DvServiceUpnpOrgDimming1GetPropertyRampPaused(THandle aService, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGDIMMING1_C

