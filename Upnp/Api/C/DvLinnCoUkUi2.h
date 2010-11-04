#ifndef HEADER_DVLINNCOUKUI2_C
#define HEADER_DVLINNCOUKUI2_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackUi2DisplayTestPattern)(void* aPtr, uint32_t aVersion, int32_t aaTestPattern);
typedef int32_t (*CallbackUi2DisplayFill)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackUi2DisplayClear)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackUi2SetTestModeEnabled)(void* aPtr, uint32_t aVersion, uint32_t aaEnabled);
typedef int32_t (*CallbackUi2SimulateInfraredInput)(void* aPtr, uint32_t aVersion, uint32_t aaCode);
typedef int32_t (*CallbackUi2SimulateButtonInput)(void* aPtr, uint32_t aVersion, uint32_t aaCode);
typedef int32_t (*CallbackUi2SimulateLightSensor)(void* aPtr, uint32_t aVersion, uint32_t aaLightLevel);
typedef int32_t (*CallbackUi2GetLightSensorData)(void* aPtr, uint32_t aVersion, uint32_t* aaLightLevel);
typedef int32_t (*CallbackUi2SetDisplayBrightness)(void* aPtr, uint32_t aVersion, uint32_t aaBrightness);
typedef int32_t (*CallbackUi2SetDisplayBrightnessAuto)(void* aPtr, uint32_t aVersion, uint32_t aaBrightnessAuto);
typedef int32_t (*CallbackUi2SetInfraredCommands)(void* aPtr, uint32_t aVersion, const char* aaCommands);
typedef int32_t (*CallbackUi2InfraredCommands)(void* aPtr, uint32_t aVersion, char** aaCommands);
typedef int32_t (*CallbackUi2SetInfraredTerminalCommands)(void* aPtr, uint32_t aVersion, const char* aaCommands);
typedef int32_t (*CallbackUi2InfraredTerminalCommands)(void* aPtr, uint32_t aVersion, char** aaCommands);
typedef int32_t (*CallbackUi2DisplayBrightness)(void* aPtr, uint32_t aVersion, uint32_t* aaBrightness);
typedef int32_t (*CallbackUi2DisplayBrightnessAuto)(void* aPtr, uint32_t aVersion, uint32_t* aaBrightnessAuto);
typedef int32_t (*CallbackUi2DisplayUpsideDown)(void* aPtr, uint32_t aVersion, uint32_t* aaUpsideDown);
typedef int32_t (*CallbackUi2SetDisplayUpsideDown)(void* aPtr, uint32_t aVersion, uint32_t aaUpsideDown);
typedef int32_t (*CallbackUi2SetDisplayScrollText)(void* aPtr, uint32_t aVersion, uint32_t aaDisplayScrollText);
typedef int32_t (*CallbackUi2DisplayScrollText)(void* aPtr, uint32_t aVersion, uint32_t* aaDisplayScrollTextEnabled);
typedef int32_t (*CallbackUi2SetDisplaySleep)(void* aPtr, uint32_t aVersion, uint32_t aaEnabled);
typedef int32_t (*CallbackUi2DisplaySleep)(void* aPtr, uint32_t aVersion, uint32_t* aaEnabled);
typedef int32_t (*CallbackUi2SetDisplayLedOff)(void* aPtr, uint32_t aVersion, uint32_t aaOff);
typedef int32_t (*CallbackUi2DisplayLedOff)(void* aPtr, uint32_t aVersion, uint32_t* aaOff);

DllExport THandle DvProviderLinnCoUkUi2Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkUi2Destroy(THandle aProvider);

DllExport void DvProviderLinnCoUkUi2EnableActionDisplayTestPattern(THandle aProvider, CallbackUi2DisplayTestPattern aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayFill(THandle aProvider, CallbackUi2DisplayFill aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayClear(THandle aProvider, CallbackUi2DisplayClear aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionSetTestModeEnabled(THandle aProvider, CallbackUi2SetTestModeEnabled aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionSimulateInfraredInput(THandle aProvider, CallbackUi2SimulateInfraredInput aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionSimulateButtonInput(THandle aProvider, CallbackUi2SimulateButtonInput aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionSimulateLightSensor(THandle aProvider, CallbackUi2SimulateLightSensor aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionGetLightSensorData(THandle aProvider, CallbackUi2GetLightSensorData aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionSetDisplayBrightness(THandle aProvider, CallbackUi2SetDisplayBrightness aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionSetDisplayBrightnessAuto(THandle aProvider, CallbackUi2SetDisplayBrightnessAuto aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionSetInfraredCommands(THandle aProvider, CallbackUi2SetInfraredCommands aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionInfraredCommands(THandle aProvider, CallbackUi2InfraredCommands aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionSetInfraredTerminalCommands(THandle aProvider, CallbackUi2SetInfraredTerminalCommands aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionInfraredTerminalCommands(THandle aProvider, CallbackUi2InfraredTerminalCommands aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayBrightness(THandle aProvider, CallbackUi2DisplayBrightness aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayBrightnessAuto(THandle aProvider, CallbackUi2DisplayBrightnessAuto aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayUpsideDown(THandle aProvider, CallbackUi2DisplayUpsideDown aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionSetDisplayUpsideDown(THandle aProvider, CallbackUi2SetDisplayUpsideDown aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionSetDisplayScrollText(THandle aProvider, CallbackUi2SetDisplayScrollText aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayScrollText(THandle aProvider, CallbackUi2DisplayScrollText aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionSetDisplaySleep(THandle aProvider, CallbackUi2SetDisplaySleep aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionDisplaySleep(THandle aProvider, CallbackUi2DisplaySleep aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionSetDisplayLedOff(THandle aProvider, CallbackUi2SetDisplayLedOff aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayLedOff(THandle aProvider, CallbackUi2DisplayLedOff aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkUi2SetPropertyDisplayBrightness(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkUi2GetPropertyDisplayBrightness(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyDisplayBrightnessAuto(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkUi2GetPropertyDisplayBrightnessAuto(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyInfraredCommands(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkUi2GetPropertyInfraredCommands(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyInfraredTerminalCommands(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkUi2GetPropertyInfraredTerminalCommands(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyDisplayUpsideDown(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkUi2GetPropertyDisplayUpsideDown(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyDisplayScrollText(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkUi2GetPropertyDisplayScrollText(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyDisplaySleep(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkUi2GetPropertyDisplaySleep(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyDisplayLedOff(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkUi2GetPropertyDisplayLedOff(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyTerminalInputCode(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkUi2GetPropertyTerminalInputCode(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyTerminalInputName(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkUi2GetPropertyTerminalInputName(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyDisplayPixels(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkUi2GetPropertyDisplayPixels(THandle aProvider, char** aValue, uint32_t* aValueLen);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKUI2_C

