/**
 * Provider for the linn.co.uk:Ui:2 UPnP service
 */
#ifndef HEADER_DVLINNCOUKUI2_C
#define HEADER_DVLINNCOUKUI2_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback which runs when the DisplayTestPattern action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionDisplayTestPattern
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaTestPattern
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2DisplayTestPattern)(void* aPtr, uint32_t aVersion, int32_t aaTestPattern);
/**
 * Callback which runs when the DisplayFill action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionDisplayFill
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2DisplayFill)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the DisplayClear action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionDisplayClear
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2DisplayClear)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the SetTestModeEnabled action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionSetTestModeEnabled
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaEnabled
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2SetTestModeEnabled)(void* aPtr, uint32_t aVersion, uint32_t aaEnabled);
/**
 * Callback which runs when the SimulateInfraredInput action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionSimulateInfraredInput
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaCode
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2SimulateInfraredInput)(void* aPtr, uint32_t aVersion, uint32_t aaCode);
/**
 * Callback which runs when the SimulateButtonInput action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionSimulateButtonInput
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaCode
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2SimulateButtonInput)(void* aPtr, uint32_t aVersion, uint32_t aaCode);
/**
 * Callback which runs when the SimulateLightSensor action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionSimulateLightSensor
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaLightLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2SimulateLightSensor)(void* aPtr, uint32_t aVersion, uint32_t aaLightLevel);
/**
 * Callback which runs when the GetLightSensorData action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionGetLightSensorData
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaLightLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2GetLightSensorData)(void* aPtr, uint32_t aVersion, uint32_t* aaLightLevel);
/**
 * Callback which runs when the SetDisplayBrightness action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionSetDisplayBrightness
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaBrightness
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2SetDisplayBrightness)(void* aPtr, uint32_t aVersion, uint32_t aaBrightness);
/**
 * Callback which runs when the SetDisplayBrightnessAuto action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionSetDisplayBrightnessAuto
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaBrightnessAuto
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2SetDisplayBrightnessAuto)(void* aPtr, uint32_t aVersion, uint32_t aaBrightnessAuto);
/**
 * Callback which runs when the SetInfraredCommands action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionSetInfraredCommands
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaCommands
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2SetInfraredCommands)(void* aPtr, uint32_t aVersion, const char* aaCommands);
/**
 * Callback which runs when the InfraredCommands action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionInfraredCommands
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaCommands
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2InfraredCommands)(void* aPtr, uint32_t aVersion, char** aaCommands);
/**
 * Callback which runs when the SetInfraredTerminalCommands action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionSetInfraredTerminalCommands
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaCommands
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2SetInfraredTerminalCommands)(void* aPtr, uint32_t aVersion, const char* aaCommands);
/**
 * Callback which runs when the InfraredTerminalCommands action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionInfraredTerminalCommands
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaCommands
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2InfraredTerminalCommands)(void* aPtr, uint32_t aVersion, char** aaCommands);
/**
 * Callback which runs when the DisplayBrightness action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionDisplayBrightness
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaBrightness
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2DisplayBrightness)(void* aPtr, uint32_t aVersion, uint32_t* aaBrightness);
/**
 * Callback which runs when the DisplayBrightnessAuto action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionDisplayBrightnessAuto
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaBrightnessAuto
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2DisplayBrightnessAuto)(void* aPtr, uint32_t aVersion, uint32_t* aaBrightnessAuto);
/**
 * Callback which runs when the DisplayUpsideDown action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionDisplayUpsideDown
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaUpsideDown
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2DisplayUpsideDown)(void* aPtr, uint32_t aVersion, uint32_t* aaUpsideDown);
/**
 * Callback which runs when the SetDisplayUpsideDown action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionSetDisplayUpsideDown
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaUpsideDown
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2SetDisplayUpsideDown)(void* aPtr, uint32_t aVersion, uint32_t aaUpsideDown);
/**
 * Callback which runs when the SetDisplayScrollText action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionSetDisplayScrollText
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaDisplayScrollText
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2SetDisplayScrollText)(void* aPtr, uint32_t aVersion, uint32_t aaDisplayScrollText);
/**
 * Callback which runs when the DisplayScrollText action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionDisplayScrollText
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaDisplayScrollTextEnabled
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2DisplayScrollText)(void* aPtr, uint32_t aVersion, uint32_t* aaDisplayScrollTextEnabled);
/**
 * Callback which runs when the SetDisplaySleep action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionSetDisplaySleep
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaEnabled
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2SetDisplaySleep)(void* aPtr, uint32_t aVersion, uint32_t aaEnabled);
/**
 * Callback which runs when the DisplaySleep action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionDisplaySleep
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaEnabled
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2DisplaySleep)(void* aPtr, uint32_t aVersion, uint32_t* aaEnabled);
/**
 * Callback which runs when the SetDisplayLedOff action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionSetDisplayLedOff
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaOff
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2SetDisplayLedOff)(void* aPtr, uint32_t aVersion, uint32_t aaOff);
/**
 * Callback which runs when the DisplayLedOff action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkUi2EnableActionDisplayLedOff
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaOff
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackUi2DisplayLedOff)(void* aPtr, uint32_t aVersion, uint32_t* aaOff);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkUi2Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 */
DllExport void DvProviderLinnCoUkUi2Destroy(THandle aProvider);

/**
 * Register a callback for the action DisplayTestPattern
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayTestPattern(THandle aProvider, CallbackUi2DisplayTestPattern aCallback, void* aPtr);
/**
 * Register a callback for the action DisplayFill
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayFill(THandle aProvider, CallbackUi2DisplayFill aCallback, void* aPtr);
/**
 * Register a callback for the action DisplayClear
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayClear(THandle aProvider, CallbackUi2DisplayClear aCallback, void* aPtr);
/**
 * Register a callback for the action SetTestModeEnabled
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionSetTestModeEnabled(THandle aProvider, CallbackUi2SetTestModeEnabled aCallback, void* aPtr);
/**
 * Register a callback for the action SimulateInfraredInput
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionSimulateInfraredInput(THandle aProvider, CallbackUi2SimulateInfraredInput aCallback, void* aPtr);
/**
 * Register a callback for the action SimulateButtonInput
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionSimulateButtonInput(THandle aProvider, CallbackUi2SimulateButtonInput aCallback, void* aPtr);
/**
 * Register a callback for the action SimulateLightSensor
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionSimulateLightSensor(THandle aProvider, CallbackUi2SimulateLightSensor aCallback, void* aPtr);
/**
 * Register a callback for the action GetLightSensorData
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionGetLightSensorData(THandle aProvider, CallbackUi2GetLightSensorData aCallback, void* aPtr);
/**
 * Register a callback for the action SetDisplayBrightness
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionSetDisplayBrightness(THandle aProvider, CallbackUi2SetDisplayBrightness aCallback, void* aPtr);
/**
 * Register a callback for the action SetDisplayBrightnessAuto
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionSetDisplayBrightnessAuto(THandle aProvider, CallbackUi2SetDisplayBrightnessAuto aCallback, void* aPtr);
/**
 * Register a callback for the action SetInfraredCommands
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionSetInfraredCommands(THandle aProvider, CallbackUi2SetInfraredCommands aCallback, void* aPtr);
/**
 * Register a callback for the action InfraredCommands
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionInfraredCommands(THandle aProvider, CallbackUi2InfraredCommands aCallback, void* aPtr);
/**
 * Register a callback for the action SetInfraredTerminalCommands
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionSetInfraredTerminalCommands(THandle aProvider, CallbackUi2SetInfraredTerminalCommands aCallback, void* aPtr);
/**
 * Register a callback for the action InfraredTerminalCommands
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionInfraredTerminalCommands(THandle aProvider, CallbackUi2InfraredTerminalCommands aCallback, void* aPtr);
/**
 * Register a callback for the action DisplayBrightness
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayBrightness(THandle aProvider, CallbackUi2DisplayBrightness aCallback, void* aPtr);
/**
 * Register a callback for the action DisplayBrightnessAuto
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayBrightnessAuto(THandle aProvider, CallbackUi2DisplayBrightnessAuto aCallback, void* aPtr);
/**
 * Register a callback for the action DisplayUpsideDown
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayUpsideDown(THandle aProvider, CallbackUi2DisplayUpsideDown aCallback, void* aPtr);
/**
 * Register a callback for the action SetDisplayUpsideDown
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionSetDisplayUpsideDown(THandle aProvider, CallbackUi2SetDisplayUpsideDown aCallback, void* aPtr);
/**
 * Register a callback for the action SetDisplayScrollText
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionSetDisplayScrollText(THandle aProvider, CallbackUi2SetDisplayScrollText aCallback, void* aPtr);
/**
 * Register a callback for the action DisplayScrollText
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayScrollText(THandle aProvider, CallbackUi2DisplayScrollText aCallback, void* aPtr);
/**
 * Register a callback for the action SetDisplaySleep
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionSetDisplaySleep(THandle aProvider, CallbackUi2SetDisplaySleep aCallback, void* aPtr);
/**
 * Register a callback for the action DisplaySleep
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionDisplaySleep(THandle aProvider, CallbackUi2DisplaySleep aCallback, void* aPtr);
/**
 * Register a callback for the action SetDisplayLedOff
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionSetDisplayLedOff(THandle aProvider, CallbackUi2SetDisplayLedOff aCallback, void* aPtr);
/**
 * Register a callback for the action DisplayLedOff
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkUi2EnableActionDisplayLedOff(THandle aProvider, CallbackUi2DisplayLedOff aCallback, void* aPtr);

/**
 * Set the value of the DisplayBrightness property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyDisplayBrightness(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the DisplayBrightness property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkUi2GetPropertyDisplayBrightness(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the DisplayBrightnessAuto property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyDisplayBrightnessAuto(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the DisplayBrightnessAuto property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkUi2GetPropertyDisplayBrightnessAuto(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the InfraredCommands property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyInfraredCommands(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the InfraredCommands property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkUi2GetPropertyInfraredCommands(THandle aProvider, char** aValue);
/**
 * Set the value of the InfraredTerminalCommands property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyInfraredTerminalCommands(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the InfraredTerminalCommands property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkUi2GetPropertyInfraredTerminalCommands(THandle aProvider, char** aValue);
/**
 * Set the value of the DisplayUpsideDown property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyDisplayUpsideDown(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the DisplayUpsideDown property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkUi2GetPropertyDisplayUpsideDown(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the DisplayScrollText property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyDisplayScrollText(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the DisplayScrollText property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkUi2GetPropertyDisplayScrollText(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the DisplaySleep property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyDisplaySleep(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the DisplaySleep property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkUi2GetPropertyDisplaySleep(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the DisplayLedOff property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyDisplayLedOff(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the DisplayLedOff property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkUi2GetPropertyDisplayLedOff(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the TerminalInputCode property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyTerminalInputCode(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TerminalInputCode property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkUi2GetPropertyTerminalInputCode(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the TerminalInputName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyTerminalInputName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TerminalInputName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkUi2GetPropertyTerminalInputName(THandle aProvider, char** aValue);
/**
 * Set the value of the DisplayPixels property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[in]  aValueLen  Size in bytes pointed to by aValue
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkUi2SetPropertyDisplayPixels(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged);
/**
 * Get a copy of the value of the DisplayPixels property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkUi2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 * @param[out] aValueLen  Size in bytes pointed to by aValue
 */
DllExport void DvProviderLinnCoUkUi2GetPropertyDisplayPixels(THandle aProvider, char** aValue, uint32_t* aValueLen);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKUI2_C

