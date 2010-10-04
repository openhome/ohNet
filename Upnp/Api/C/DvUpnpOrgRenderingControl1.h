#ifndef HEADER_DVUPNPORGRENDERINGCONTROL1_C
#define HEADER_DVUPNPORGRENDERINGCONTROL1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackRenderingControl1ListPresets)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aCurrentPresetNameList);
typedef int32_t (*CallbackRenderingControl1SelectPreset)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aPresetName);
typedef int32_t (*CallbackRenderingControl1GetBrightness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBrightness);
typedef int32_t (*CallbackRenderingControl1SetBrightness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBrightness);
typedef int32_t (*CallbackRenderingControl1GetContrast)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentContrast);
typedef int32_t (*CallbackRenderingControl1SetContrast)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredContrast);
typedef int32_t (*CallbackRenderingControl1GetSharpness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentSharpness);
typedef int32_t (*CallbackRenderingControl1SetSharpness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredSharpness);
typedef int32_t (*CallbackRenderingControl1GetRedVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentRedVideoGain);
typedef int32_t (*CallbackRenderingControl1SetRedVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain);
typedef int32_t (*CallbackRenderingControl1GetGreenVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoGain);
typedef int32_t (*CallbackRenderingControl1SetGreenVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain);
typedef int32_t (*CallbackRenderingControl1GetBlueVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoGain);
typedef int32_t (*CallbackRenderingControl1SetBlueVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain);
typedef int32_t (*CallbackRenderingControl1GetRedVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentRedVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl1SetRedVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl1GetGreenVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl1SetGreenVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl1GetBlueVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl1SetBlueVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl1GetColorTemperature)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentColorTemperature);
typedef int32_t (*CallbackRenderingControl1SetColorTemperature)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredColorTemperature);
typedef int32_t (*CallbackRenderingControl1GetHorizontalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t* aCurrentHorizontalKeystone);
typedef int32_t (*CallbackRenderingControl1SetHorizontalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone);
typedef int32_t (*CallbackRenderingControl1GetVerticalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t* aCurrentVerticalKeystone);
typedef int32_t (*CallbackRenderingControl1SetVerticalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone);
typedef int32_t (*CallbackRenderingControl1GetMute)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentMute);
typedef int32_t (*CallbackRenderingControl1SetMute)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute);
typedef int32_t (*CallbackRenderingControl1GetVolume)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentVolume);
typedef int32_t (*CallbackRenderingControl1SetVolume)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume);
typedef int32_t (*CallbackRenderingControl1GetVolumeDB)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t* aCurrentVolume);
typedef int32_t (*CallbackRenderingControl1SetVolumeDB)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume);
typedef int32_t (*CallbackRenderingControl1GetVolumeDBRange)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t* aMinValue, int32_t* aMaxValue);
typedef int32_t (*CallbackRenderingControl1GetLoudness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentLoudness);
typedef int32_t (*CallbackRenderingControl1SetLoudness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness);

DllExport THandle DvServiceUpnpOrgRenderingControl1Create(DvDeviceC aDevice);
DllExport void DvServiceUpnpOrgRenderingControl1Destroy(THandle aService);

DllExport void DvServiceUpnpOrgRenderingControl1EnableActionListPresets(THandle aService, CallbackRenderingControl1ListPresets aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSelectPreset(THandle aService, CallbackRenderingControl1SelectPreset aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetBrightness(THandle aService, CallbackRenderingControl1GetBrightness aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetBrightness(THandle aService, CallbackRenderingControl1SetBrightness aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetContrast(THandle aService, CallbackRenderingControl1GetContrast aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetContrast(THandle aService, CallbackRenderingControl1SetContrast aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetSharpness(THandle aService, CallbackRenderingControl1GetSharpness aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetSharpness(THandle aService, CallbackRenderingControl1SetSharpness aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetRedVideoGain(THandle aService, CallbackRenderingControl1GetRedVideoGain aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetRedVideoGain(THandle aService, CallbackRenderingControl1SetRedVideoGain aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetGreenVideoGain(THandle aService, CallbackRenderingControl1GetGreenVideoGain aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetGreenVideoGain(THandle aService, CallbackRenderingControl1SetGreenVideoGain aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetBlueVideoGain(THandle aService, CallbackRenderingControl1GetBlueVideoGain aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetBlueVideoGain(THandle aService, CallbackRenderingControl1SetBlueVideoGain aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetRedVideoBlackLevel(THandle aService, CallbackRenderingControl1GetRedVideoBlackLevel aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetRedVideoBlackLevel(THandle aService, CallbackRenderingControl1SetRedVideoBlackLevel aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetGreenVideoBlackLevel(THandle aService, CallbackRenderingControl1GetGreenVideoBlackLevel aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetGreenVideoBlackLevel(THandle aService, CallbackRenderingControl1SetGreenVideoBlackLevel aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetBlueVideoBlackLevel(THandle aService, CallbackRenderingControl1GetBlueVideoBlackLevel aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetBlueVideoBlackLevel(THandle aService, CallbackRenderingControl1SetBlueVideoBlackLevel aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetColorTemperature(THandle aService, CallbackRenderingControl1GetColorTemperature aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetColorTemperature(THandle aService, CallbackRenderingControl1SetColorTemperature aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetHorizontalKeystone(THandle aService, CallbackRenderingControl1GetHorizontalKeystone aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetHorizontalKeystone(THandle aService, CallbackRenderingControl1SetHorizontalKeystone aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetVerticalKeystone(THandle aService, CallbackRenderingControl1GetVerticalKeystone aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetVerticalKeystone(THandle aService, CallbackRenderingControl1SetVerticalKeystone aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetMute(THandle aService, CallbackRenderingControl1GetMute aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetMute(THandle aService, CallbackRenderingControl1SetMute aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetVolume(THandle aService, CallbackRenderingControl1GetVolume aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetVolume(THandle aService, CallbackRenderingControl1SetVolume aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetVolumeDB(THandle aService, CallbackRenderingControl1GetVolumeDB aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetVolumeDB(THandle aService, CallbackRenderingControl1SetVolumeDB aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetVolumeDBRange(THandle aService, CallbackRenderingControl1GetVolumeDBRange aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionGetLoudness(THandle aService, CallbackRenderingControl1GetLoudness aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgRenderingControl1EnableActionSetLoudness(THandle aService, CallbackRenderingControl1SetLoudness aCallback, void* aPtr);

DllExport int32_t DvServiceUpnpOrgRenderingControl1SetPropertyLastChange(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgRenderingControl1GetPropertyLastChange(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGRENDERINGCONTROL1_C

