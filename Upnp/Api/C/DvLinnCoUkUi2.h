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

DllExport THandle DvServiceLinnCoUkUi2Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkUi2Destroy(THandle aService);

DllExport void DvServiceLinnCoUkUi2EnableActionDisplayTestPattern(THandle aService, CallbackUi2DisplayTestPattern aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionDisplayFill(THandle aService, CallbackUi2DisplayFill aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionDisplayClear(THandle aService, CallbackUi2DisplayClear aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionSetTestModeEnabled(THandle aService, CallbackUi2SetTestModeEnabled aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionSimulateInfraredInput(THandle aService, CallbackUi2SimulateInfraredInput aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionSimulateButtonInput(THandle aService, CallbackUi2SimulateButtonInput aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionSimulateLightSensor(THandle aService, CallbackUi2SimulateLightSensor aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionGetLightSensorData(THandle aService, CallbackUi2GetLightSensorData aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionSetDisplayBrightness(THandle aService, CallbackUi2SetDisplayBrightness aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionSetDisplayBrightnessAuto(THandle aService, CallbackUi2SetDisplayBrightnessAuto aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionSetInfraredCommands(THandle aService, CallbackUi2SetInfraredCommands aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionInfraredCommands(THandle aService, CallbackUi2InfraredCommands aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionSetInfraredTerminalCommands(THandle aService, CallbackUi2SetInfraredTerminalCommands aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionInfraredTerminalCommands(THandle aService, CallbackUi2InfraredTerminalCommands aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionDisplayBrightness(THandle aService, CallbackUi2DisplayBrightness aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionDisplayBrightnessAuto(THandle aService, CallbackUi2DisplayBrightnessAuto aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionDisplayUpsideDown(THandle aService, CallbackUi2DisplayUpsideDown aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionSetDisplayUpsideDown(THandle aService, CallbackUi2SetDisplayUpsideDown aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionSetDisplayScrollText(THandle aService, CallbackUi2SetDisplayScrollText aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionDisplayScrollText(THandle aService, CallbackUi2DisplayScrollText aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionSetDisplaySleep(THandle aService, CallbackUi2SetDisplaySleep aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionDisplaySleep(THandle aService, CallbackUi2DisplaySleep aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionSetDisplayLedOff(THandle aService, CallbackUi2SetDisplayLedOff aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkUi2EnableActionDisplayLedOff(THandle aService, CallbackUi2DisplayLedOff aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkUi2SetPropertyDisplayBrightness(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkUi2GetPropertyDisplayBrightness(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkUi2SetPropertyDisplayBrightnessAuto(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkUi2GetPropertyDisplayBrightnessAuto(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkUi2SetPropertyInfraredCommands(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkUi2GetPropertyInfraredCommands(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkUi2SetPropertyInfraredTerminalCommands(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkUi2GetPropertyInfraredTerminalCommands(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkUi2SetPropertyDisplayUpsideDown(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkUi2GetPropertyDisplayUpsideDown(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkUi2SetPropertyDisplayScrollText(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkUi2GetPropertyDisplayScrollText(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkUi2SetPropertyDisplaySleep(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkUi2GetPropertyDisplaySleep(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkUi2SetPropertyDisplayLedOff(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkUi2GetPropertyDisplayLedOff(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkUi2SetPropertyTerminalInputCode(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkUi2GetPropertyTerminalInputCode(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkUi2SetPropertyTerminalInputName(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkUi2GetPropertyTerminalInputName(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkUi2SetPropertyDisplayPixels(THandle aService, const char* aValue, uint32_t aValueLen);
DllExport void DvServiceLinnCoUkUi2GetPropertyDisplayPixels(THandle aService, char** aValue, uint32_t* aValueLen);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKUI2_C

