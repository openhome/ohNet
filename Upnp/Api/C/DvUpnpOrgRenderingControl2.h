#ifndef HEADER_DVUPNPORGRENDERINGCONTROL2_C
#define HEADER_DVUPNPORGRENDERINGCONTROL2_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackRenderingControl2ListPresets)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aCurrentPresetNameList);
typedef int32_t (*CallbackRenderingControl2SelectPreset)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aPresetName);
typedef int32_t (*CallbackRenderingControl2GetBrightness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBrightness);
typedef int32_t (*CallbackRenderingControl2SetBrightness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBrightness);
typedef int32_t (*CallbackRenderingControl2GetContrast)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentContrast);
typedef int32_t (*CallbackRenderingControl2SetContrast)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredContrast);
typedef int32_t (*CallbackRenderingControl2GetSharpness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentSharpness);
typedef int32_t (*CallbackRenderingControl2SetSharpness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredSharpness);
typedef int32_t (*CallbackRenderingControl2GetRedVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentRedVideoGain);
typedef int32_t (*CallbackRenderingControl2SetRedVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain);
typedef int32_t (*CallbackRenderingControl2GetGreenVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoGain);
typedef int32_t (*CallbackRenderingControl2SetGreenVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain);
typedef int32_t (*CallbackRenderingControl2GetBlueVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoGain);
typedef int32_t (*CallbackRenderingControl2SetBlueVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain);
typedef int32_t (*CallbackRenderingControl2GetRedVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentRedVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl2SetRedVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl2GetGreenVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl2SetGreenVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl2GetBlueVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl2SetBlueVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl2GetColorTemperature)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentColorTemperature);
typedef int32_t (*CallbackRenderingControl2SetColorTemperature)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredColorTemperature);
typedef int32_t (*CallbackRenderingControl2GetHorizontalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t* aCurrentHorizontalKeystone);
typedef int32_t (*CallbackRenderingControl2SetHorizontalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone);
typedef int32_t (*CallbackRenderingControl2GetVerticalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t* aCurrentVerticalKeystone);
typedef int32_t (*CallbackRenderingControl2SetVerticalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone);
typedef int32_t (*CallbackRenderingControl2GetMute)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentMute);
typedef int32_t (*CallbackRenderingControl2SetMute)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute);
typedef int32_t (*CallbackRenderingControl2GetVolume)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentVolume);
typedef int32_t (*CallbackRenderingControl2SetVolume)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume);
typedef int32_t (*CallbackRenderingControl2GetVolumeDB)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t* aCurrentVolume);
typedef int32_t (*CallbackRenderingControl2SetVolumeDB)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume);
typedef int32_t (*CallbackRenderingControl2GetVolumeDBRange)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t* aMinValue, int32_t* aMaxValue);
typedef int32_t (*CallbackRenderingControl2GetLoudness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentLoudness);
typedef int32_t (*CallbackRenderingControl2SetLoudness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness);
typedef int32_t (*CallbackRenderingControl2GetStateVariables)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aStateVariableList, char** aStateVariableValuePairs);
typedef int32_t (*CallbackRenderingControl2SetStateVariables)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aRenderingControlUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, char** aStateVariableList);

DllExport THandle DvServiceUpnpOrgRenderingControl2Create(DvDeviceC aDevice);
DllExport void DvServiceUpnpOrgRenderingControl2Destroy(THandle aService);

DllExport void DvServiceUpnpOrgRenderingControl2EnableActionListPresets(THandle aService, CallbackRenderingControl2ListPresets aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSelectPreset(THandle aService, CallbackRenderingControl2SelectPreset aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetBrightness(THandle aService, CallbackRenderingControl2GetBrightness aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetBrightness(THandle aService, CallbackRenderingControl2SetBrightness aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetContrast(THandle aService, CallbackRenderingControl2GetContrast aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetContrast(THandle aService, CallbackRenderingControl2SetContrast aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetSharpness(THandle aService, CallbackRenderingControl2GetSharpness aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetSharpness(THandle aService, CallbackRenderingControl2SetSharpness aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetRedVideoGain(THandle aService, CallbackRenderingControl2GetRedVideoGain aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetRedVideoGain(THandle aService, CallbackRenderingControl2SetRedVideoGain aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetGreenVideoGain(THandle aService, CallbackRenderingControl2GetGreenVideoGain aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetGreenVideoGain(THandle aService, CallbackRenderingControl2SetGreenVideoGain aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetBlueVideoGain(THandle aService, CallbackRenderingControl2GetBlueVideoGain aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetBlueVideoGain(THandle aService, CallbackRenderingControl2SetBlueVideoGain aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetRedVideoBlackLevel(THandle aService, CallbackRenderingControl2GetRedVideoBlackLevel aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetRedVideoBlackLevel(THandle aService, CallbackRenderingControl2SetRedVideoBlackLevel aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetGreenVideoBlackLevel(THandle aService, CallbackRenderingControl2GetGreenVideoBlackLevel aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetGreenVideoBlackLevel(THandle aService, CallbackRenderingControl2SetGreenVideoBlackLevel aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetBlueVideoBlackLevel(THandle aService, CallbackRenderingControl2GetBlueVideoBlackLevel aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetBlueVideoBlackLevel(THandle aService, CallbackRenderingControl2SetBlueVideoBlackLevel aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetColorTemperature(THandle aService, CallbackRenderingControl2GetColorTemperature aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetColorTemperature(THandle aService, CallbackRenderingControl2SetColorTemperature aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetHorizontalKeystone(THandle aService, CallbackRenderingControl2GetHorizontalKeystone aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetHorizontalKeystone(THandle aService, CallbackRenderingControl2SetHorizontalKeystone aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetVerticalKeystone(THandle aService, CallbackRenderingControl2GetVerticalKeystone aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetVerticalKeystone(THandle aService, CallbackRenderingControl2SetVerticalKeystone aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetMute(THandle aService, CallbackRenderingControl2GetMute aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetMute(THandle aService, CallbackRenderingControl2SetMute aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetVolume(THandle aService, CallbackRenderingControl2GetVolume aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetVolume(THandle aService, CallbackRenderingControl2SetVolume aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetVolumeDB(THandle aService, CallbackRenderingControl2GetVolumeDB aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetVolumeDB(THandle aService, CallbackRenderingControl2SetVolumeDB aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetVolumeDBRange(THandle aService, CallbackRenderingControl2GetVolumeDBRange aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetLoudness(THandle aService, CallbackRenderingControl2GetLoudness aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetLoudness(THandle aService, CallbackRenderingControl2SetLoudness aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionGetStateVariables(THandle aService, CallbackRenderingControl2GetStateVariables aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl2EnableActionSetStateVariables(THandle aService, CallbackRenderingControl2SetStateVariables aCallback, void* aPtr);

DllExport int32_t DvServiceUpnpOrgRenderingControl2SetPropertyLastChange(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgRenderingControl2GetPropertyLastChange(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGRENDERINGCONTROL2_C

