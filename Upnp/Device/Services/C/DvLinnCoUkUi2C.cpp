#include <C/DvLinnCoUkUi2.h>
#include <Core/DvLinnCoUkUi2.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkUi2C : public DvProviderLinnCoUkUi2
{
public:
    DvProviderLinnCoUkUi2C(DvDevice& aDevice);
    void EnableActionDisplayTestPattern(CallbackUi2DisplayTestPattern aCallback, void* aPtr);
    void EnableActionDisplayFill(CallbackUi2DisplayFill aCallback, void* aPtr);
    void EnableActionDisplayClear(CallbackUi2DisplayClear aCallback, void* aPtr);
    void EnableActionSetTestModeEnabled(CallbackUi2SetTestModeEnabled aCallback, void* aPtr);
    void EnableActionSimulateInfraredInput(CallbackUi2SimulateInfraredInput aCallback, void* aPtr);
    void EnableActionSimulateButtonInput(CallbackUi2SimulateButtonInput aCallback, void* aPtr);
    void EnableActionSimulateLightSensor(CallbackUi2SimulateLightSensor aCallback, void* aPtr);
    void EnableActionGetLightSensorData(CallbackUi2GetLightSensorData aCallback, void* aPtr);
    void EnableActionSetDisplayBrightness(CallbackUi2SetDisplayBrightness aCallback, void* aPtr);
    void EnableActionSetDisplayBrightnessAuto(CallbackUi2SetDisplayBrightnessAuto aCallback, void* aPtr);
    void EnableActionSetInfraredCommands(CallbackUi2SetInfraredCommands aCallback, void* aPtr);
    void EnableActionInfraredCommands(CallbackUi2InfraredCommands aCallback, void* aPtr);
    void EnableActionSetInfraredTerminalCommands(CallbackUi2SetInfraredTerminalCommands aCallback, void* aPtr);
    void EnableActionInfraredTerminalCommands(CallbackUi2InfraredTerminalCommands aCallback, void* aPtr);
    void EnableActionDisplayBrightness(CallbackUi2DisplayBrightness aCallback, void* aPtr);
    void EnableActionDisplayBrightnessAuto(CallbackUi2DisplayBrightnessAuto aCallback, void* aPtr);
    void EnableActionDisplayUpsideDown(CallbackUi2DisplayUpsideDown aCallback, void* aPtr);
    void EnableActionSetDisplayUpsideDown(CallbackUi2SetDisplayUpsideDown aCallback, void* aPtr);
    void EnableActionSetDisplayScrollText(CallbackUi2SetDisplayScrollText aCallback, void* aPtr);
    void EnableActionDisplayScrollText(CallbackUi2DisplayScrollText aCallback, void* aPtr);
    void EnableActionSetDisplaySleep(CallbackUi2SetDisplaySleep aCallback, void* aPtr);
    void EnableActionDisplaySleep(CallbackUi2DisplaySleep aCallback, void* aPtr);
    void EnableActionSetDisplayLedOff(CallbackUi2SetDisplayLedOff aCallback, void* aPtr);
    void EnableActionDisplayLedOff(CallbackUi2DisplayLedOff aCallback, void* aPtr);
private:
    void DisplayTestPattern(IInvocationResponse& aResponse, TUint aVersion, TInt aaTestPattern);
    void DisplayFill(IInvocationResponse& aResponse, TUint aVersion);
    void DisplayClear(IInvocationResponse& aResponse, TUint aVersion);
    void SetTestModeEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled);
    void SimulateInfraredInput(IInvocationResponse& aResponse, TUint aVersion, TUint aaCode);
    void SimulateButtonInput(IInvocationResponse& aResponse, TUint aVersion, TUint aaCode);
    void SimulateLightSensor(IInvocationResponse& aResponse, TUint aVersion, TUint aaLightLevel);
    void GetLightSensorData(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaLightLevel);
    void SetDisplayBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aaBrightness);
    void SetDisplayBrightnessAuto(IInvocationResponse& aResponse, TUint aVersion, TBool aaBrightnessAuto);
    void SetInfraredCommands(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaCommands);
    void InfraredCommands(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCommands);
    void SetInfraredTerminalCommands(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaCommands);
    void InfraredTerminalCommands(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCommands);
    void DisplayBrightness(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaBrightness);
    void DisplayBrightnessAuto(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaBrightnessAuto);
    void DisplayUpsideDown(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaUpsideDown);
    void SetDisplayUpsideDown(IInvocationResponse& aResponse, TUint aVersion, TBool aaUpsideDown);
    void SetDisplayScrollText(IInvocationResponse& aResponse, TUint aVersion, TBool aaDisplayScrollText);
    void DisplayScrollText(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaDisplayScrollTextEnabled);
    void SetDisplaySleep(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled);
    void DisplaySleep(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled);
    void SetDisplayLedOff(IInvocationResponse& aResponse, TUint aVersion, TBool aaOff);
    void DisplayLedOff(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaOff);
private:
    CallbackUi2DisplayTestPattern iCallbackDisplayTestPattern;
    void* iPtrDisplayTestPattern;
    CallbackUi2DisplayFill iCallbackDisplayFill;
    void* iPtrDisplayFill;
    CallbackUi2DisplayClear iCallbackDisplayClear;
    void* iPtrDisplayClear;
    CallbackUi2SetTestModeEnabled iCallbackSetTestModeEnabled;
    void* iPtrSetTestModeEnabled;
    CallbackUi2SimulateInfraredInput iCallbackSimulateInfraredInput;
    void* iPtrSimulateInfraredInput;
    CallbackUi2SimulateButtonInput iCallbackSimulateButtonInput;
    void* iPtrSimulateButtonInput;
    CallbackUi2SimulateLightSensor iCallbackSimulateLightSensor;
    void* iPtrSimulateLightSensor;
    CallbackUi2GetLightSensorData iCallbackGetLightSensorData;
    void* iPtrGetLightSensorData;
    CallbackUi2SetDisplayBrightness iCallbackSetDisplayBrightness;
    void* iPtrSetDisplayBrightness;
    CallbackUi2SetDisplayBrightnessAuto iCallbackSetDisplayBrightnessAuto;
    void* iPtrSetDisplayBrightnessAuto;
    CallbackUi2SetInfraredCommands iCallbackSetInfraredCommands;
    void* iPtrSetInfraredCommands;
    CallbackUi2InfraredCommands iCallbackInfraredCommands;
    void* iPtrInfraredCommands;
    CallbackUi2SetInfraredTerminalCommands iCallbackSetInfraredTerminalCommands;
    void* iPtrSetInfraredTerminalCommands;
    CallbackUi2InfraredTerminalCommands iCallbackInfraredTerminalCommands;
    void* iPtrInfraredTerminalCommands;
    CallbackUi2DisplayBrightness iCallbackDisplayBrightness;
    void* iPtrDisplayBrightness;
    CallbackUi2DisplayBrightnessAuto iCallbackDisplayBrightnessAuto;
    void* iPtrDisplayBrightnessAuto;
    CallbackUi2DisplayUpsideDown iCallbackDisplayUpsideDown;
    void* iPtrDisplayUpsideDown;
    CallbackUi2SetDisplayUpsideDown iCallbackSetDisplayUpsideDown;
    void* iPtrSetDisplayUpsideDown;
    CallbackUi2SetDisplayScrollText iCallbackSetDisplayScrollText;
    void* iPtrSetDisplayScrollText;
    CallbackUi2DisplayScrollText iCallbackDisplayScrollText;
    void* iPtrDisplayScrollText;
    CallbackUi2SetDisplaySleep iCallbackSetDisplaySleep;
    void* iPtrSetDisplaySleep;
    CallbackUi2DisplaySleep iCallbackDisplaySleep;
    void* iPtrDisplaySleep;
    CallbackUi2SetDisplayLedOff iCallbackSetDisplayLedOff;
    void* iPtrSetDisplayLedOff;
    CallbackUi2DisplayLedOff iCallbackDisplayLedOff;
    void* iPtrDisplayLedOff;
};

DvProviderLinnCoUkUi2C::DvProviderLinnCoUkUi2C(DvDevice& aDevice)
    : DvProviderLinnCoUkUi2(aDevice)
{
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayTestPattern(CallbackUi2DisplayTestPattern aCallback, void* aPtr)
{
    iCallbackDisplayTestPattern = aCallback;
    iPtrDisplayTestPattern = aPtr;
    DvProviderLinnCoUkUi2::EnableActionDisplayTestPattern();
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayFill(CallbackUi2DisplayFill aCallback, void* aPtr)
{
    iCallbackDisplayFill = aCallback;
    iPtrDisplayFill = aPtr;
    DvProviderLinnCoUkUi2::EnableActionDisplayFill();
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayClear(CallbackUi2DisplayClear aCallback, void* aPtr)
{
    iCallbackDisplayClear = aCallback;
    iPtrDisplayClear = aPtr;
    DvProviderLinnCoUkUi2::EnableActionDisplayClear();
}

void DvProviderLinnCoUkUi2C::EnableActionSetTestModeEnabled(CallbackUi2SetTestModeEnabled aCallback, void* aPtr)
{
    iCallbackSetTestModeEnabled = aCallback;
    iPtrSetTestModeEnabled = aPtr;
    DvProviderLinnCoUkUi2::EnableActionSetTestModeEnabled();
}

void DvProviderLinnCoUkUi2C::EnableActionSimulateInfraredInput(CallbackUi2SimulateInfraredInput aCallback, void* aPtr)
{
    iCallbackSimulateInfraredInput = aCallback;
    iPtrSimulateInfraredInput = aPtr;
    DvProviderLinnCoUkUi2::EnableActionSimulateInfraredInput();
}

void DvProviderLinnCoUkUi2C::EnableActionSimulateButtonInput(CallbackUi2SimulateButtonInput aCallback, void* aPtr)
{
    iCallbackSimulateButtonInput = aCallback;
    iPtrSimulateButtonInput = aPtr;
    DvProviderLinnCoUkUi2::EnableActionSimulateButtonInput();
}

void DvProviderLinnCoUkUi2C::EnableActionSimulateLightSensor(CallbackUi2SimulateLightSensor aCallback, void* aPtr)
{
    iCallbackSimulateLightSensor = aCallback;
    iPtrSimulateLightSensor = aPtr;
    DvProviderLinnCoUkUi2::EnableActionSimulateLightSensor();
}

void DvProviderLinnCoUkUi2C::EnableActionGetLightSensorData(CallbackUi2GetLightSensorData aCallback, void* aPtr)
{
    iCallbackGetLightSensorData = aCallback;
    iPtrGetLightSensorData = aPtr;
    DvProviderLinnCoUkUi2::EnableActionGetLightSensorData();
}

void DvProviderLinnCoUkUi2C::EnableActionSetDisplayBrightness(CallbackUi2SetDisplayBrightness aCallback, void* aPtr)
{
    iCallbackSetDisplayBrightness = aCallback;
    iPtrSetDisplayBrightness = aPtr;
    DvProviderLinnCoUkUi2::EnableActionSetDisplayBrightness();
}

void DvProviderLinnCoUkUi2C::EnableActionSetDisplayBrightnessAuto(CallbackUi2SetDisplayBrightnessAuto aCallback, void* aPtr)
{
    iCallbackSetDisplayBrightnessAuto = aCallback;
    iPtrSetDisplayBrightnessAuto = aPtr;
    DvProviderLinnCoUkUi2::EnableActionSetDisplayBrightnessAuto();
}

void DvProviderLinnCoUkUi2C::EnableActionSetInfraredCommands(CallbackUi2SetInfraredCommands aCallback, void* aPtr)
{
    iCallbackSetInfraredCommands = aCallback;
    iPtrSetInfraredCommands = aPtr;
    DvProviderLinnCoUkUi2::EnableActionSetInfraredCommands();
}

void DvProviderLinnCoUkUi2C::EnableActionInfraredCommands(CallbackUi2InfraredCommands aCallback, void* aPtr)
{
    iCallbackInfraredCommands = aCallback;
    iPtrInfraredCommands = aPtr;
    DvProviderLinnCoUkUi2::EnableActionInfraredCommands();
}

void DvProviderLinnCoUkUi2C::EnableActionSetInfraredTerminalCommands(CallbackUi2SetInfraredTerminalCommands aCallback, void* aPtr)
{
    iCallbackSetInfraredTerminalCommands = aCallback;
    iPtrSetInfraredTerminalCommands = aPtr;
    DvProviderLinnCoUkUi2::EnableActionSetInfraredTerminalCommands();
}

void DvProviderLinnCoUkUi2C::EnableActionInfraredTerminalCommands(CallbackUi2InfraredTerminalCommands aCallback, void* aPtr)
{
    iCallbackInfraredTerminalCommands = aCallback;
    iPtrInfraredTerminalCommands = aPtr;
    DvProviderLinnCoUkUi2::EnableActionInfraredTerminalCommands();
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayBrightness(CallbackUi2DisplayBrightness aCallback, void* aPtr)
{
    iCallbackDisplayBrightness = aCallback;
    iPtrDisplayBrightness = aPtr;
    DvProviderLinnCoUkUi2::EnableActionDisplayBrightness();
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayBrightnessAuto(CallbackUi2DisplayBrightnessAuto aCallback, void* aPtr)
{
    iCallbackDisplayBrightnessAuto = aCallback;
    iPtrDisplayBrightnessAuto = aPtr;
    DvProviderLinnCoUkUi2::EnableActionDisplayBrightnessAuto();
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayUpsideDown(CallbackUi2DisplayUpsideDown aCallback, void* aPtr)
{
    iCallbackDisplayUpsideDown = aCallback;
    iPtrDisplayUpsideDown = aPtr;
    DvProviderLinnCoUkUi2::EnableActionDisplayUpsideDown();
}

void DvProviderLinnCoUkUi2C::EnableActionSetDisplayUpsideDown(CallbackUi2SetDisplayUpsideDown aCallback, void* aPtr)
{
    iCallbackSetDisplayUpsideDown = aCallback;
    iPtrSetDisplayUpsideDown = aPtr;
    DvProviderLinnCoUkUi2::EnableActionSetDisplayUpsideDown();
}

void DvProviderLinnCoUkUi2C::EnableActionSetDisplayScrollText(CallbackUi2SetDisplayScrollText aCallback, void* aPtr)
{
    iCallbackSetDisplayScrollText = aCallback;
    iPtrSetDisplayScrollText = aPtr;
    DvProviderLinnCoUkUi2::EnableActionSetDisplayScrollText();
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayScrollText(CallbackUi2DisplayScrollText aCallback, void* aPtr)
{
    iCallbackDisplayScrollText = aCallback;
    iPtrDisplayScrollText = aPtr;
    DvProviderLinnCoUkUi2::EnableActionDisplayScrollText();
}

void DvProviderLinnCoUkUi2C::EnableActionSetDisplaySleep(CallbackUi2SetDisplaySleep aCallback, void* aPtr)
{
    iCallbackSetDisplaySleep = aCallback;
    iPtrSetDisplaySleep = aPtr;
    DvProviderLinnCoUkUi2::EnableActionSetDisplaySleep();
}

void DvProviderLinnCoUkUi2C::EnableActionDisplaySleep(CallbackUi2DisplaySleep aCallback, void* aPtr)
{
    iCallbackDisplaySleep = aCallback;
    iPtrDisplaySleep = aPtr;
    DvProviderLinnCoUkUi2::EnableActionDisplaySleep();
}

void DvProviderLinnCoUkUi2C::EnableActionSetDisplayLedOff(CallbackUi2SetDisplayLedOff aCallback, void* aPtr)
{
    iCallbackSetDisplayLedOff = aCallback;
    iPtrSetDisplayLedOff = aPtr;
    DvProviderLinnCoUkUi2::EnableActionSetDisplayLedOff();
}

void DvProviderLinnCoUkUi2C::EnableActionDisplayLedOff(CallbackUi2DisplayLedOff aCallback, void* aPtr)
{
    iCallbackDisplayLedOff = aCallback;
    iPtrDisplayLedOff = aPtr;
    DvProviderLinnCoUkUi2::EnableActionDisplayLedOff();
}

void DvProviderLinnCoUkUi2C::DisplayTestPattern(IInvocationResponse& aResponse, TUint aVersion, TInt aaTestPattern)
{
    ASSERT(iCallbackDisplayTestPattern != NULL);
    if (0 != iCallbackDisplayTestPattern(iPtrDisplayTestPattern, aVersion, aaTestPattern)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::DisplayFill(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackDisplayFill != NULL);
    if (0 != iCallbackDisplayFill(iPtrDisplayFill, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::DisplayClear(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackDisplayClear != NULL);
    if (0 != iCallbackDisplayClear(iPtrDisplayClear, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::SetTestModeEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled)
{
    ASSERT(iCallbackSetTestModeEnabled != NULL);
    if (0 != iCallbackSetTestModeEnabled(iPtrSetTestModeEnabled, aVersion, aaEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::SimulateInfraredInput(IInvocationResponse& aResponse, TUint aVersion, TUint aaCode)
{
    ASSERT(iCallbackSimulateInfraredInput != NULL);
    if (0 != iCallbackSimulateInfraredInput(iPtrSimulateInfraredInput, aVersion, aaCode)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::SimulateButtonInput(IInvocationResponse& aResponse, TUint aVersion, TUint aaCode)
{
    ASSERT(iCallbackSimulateButtonInput != NULL);
    if (0 != iCallbackSimulateButtonInput(iPtrSimulateButtonInput, aVersion, aaCode)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::SimulateLightSensor(IInvocationResponse& aResponse, TUint aVersion, TUint aaLightLevel)
{
    ASSERT(iCallbackSimulateLightSensor != NULL);
    if (0 != iCallbackSimulateLightSensor(iPtrSimulateLightSensor, aVersion, aaLightLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::GetLightSensorData(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaLightLevel)
{
    uint32_t aLightLevel;
    ASSERT(iCallbackGetLightSensorData != NULL);
    if (0 != iCallbackGetLightSensorData(iPtrGetLightSensorData, aVersion, &aLightLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaLightLevel.Write(aLightLevel);
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::SetDisplayBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aaBrightness)
{
    ASSERT(iCallbackSetDisplayBrightness != NULL);
    if (0 != iCallbackSetDisplayBrightness(iPtrSetDisplayBrightness, aVersion, aaBrightness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::SetDisplayBrightnessAuto(IInvocationResponse& aResponse, TUint aVersion, TBool aaBrightnessAuto)
{
    ASSERT(iCallbackSetDisplayBrightnessAuto != NULL);
    if (0 != iCallbackSetDisplayBrightnessAuto(iPtrSetDisplayBrightnessAuto, aVersion, aaBrightnessAuto)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::SetInfraredCommands(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaCommands)
{
    ASSERT(iCallbackSetInfraredCommands != NULL);
    if (0 != iCallbackSetInfraredCommands(iPtrSetInfraredCommands, aVersion, (const char*)aaCommands.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::InfraredCommands(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCommands)
{
    char* aCommands;
    ASSERT(iCallbackInfraredCommands != NULL);
    if (0 != iCallbackInfraredCommands(iPtrInfraredCommands, aVersion, &aCommands)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaCommands((const TChar*)aCommands);
    ZappFreeExternal(aCommands);
    aaCommands.Write(bufaCommands);
    aaCommands.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::SetInfraredTerminalCommands(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaCommands)
{
    ASSERT(iCallbackSetInfraredTerminalCommands != NULL);
    if (0 != iCallbackSetInfraredTerminalCommands(iPtrSetInfraredTerminalCommands, aVersion, (const char*)aaCommands.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::InfraredTerminalCommands(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCommands)
{
    char* aCommands;
    ASSERT(iCallbackInfraredTerminalCommands != NULL);
    if (0 != iCallbackInfraredTerminalCommands(iPtrInfraredTerminalCommands, aVersion, &aCommands)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaCommands((const TChar*)aCommands);
    ZappFreeExternal(aCommands);
    aaCommands.Write(bufaCommands);
    aaCommands.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::DisplayBrightness(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaBrightness)
{
    uint32_t aBrightness;
    ASSERT(iCallbackDisplayBrightness != NULL);
    if (0 != iCallbackDisplayBrightness(iPtrDisplayBrightness, aVersion, &aBrightness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaBrightness.Write(aBrightness);
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::DisplayBrightnessAuto(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaBrightnessAuto)
{
    uint32_t aBrightnessAuto;
    ASSERT(iCallbackDisplayBrightnessAuto != NULL);
    if (0 != iCallbackDisplayBrightnessAuto(iPtrDisplayBrightnessAuto, aVersion, &aBrightnessAuto)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaBrightnessAuto.Write((aBrightnessAuto!=0));
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::DisplayUpsideDown(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaUpsideDown)
{
    uint32_t aUpsideDown;
    ASSERT(iCallbackDisplayUpsideDown != NULL);
    if (0 != iCallbackDisplayUpsideDown(iPtrDisplayUpsideDown, aVersion, &aUpsideDown)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaUpsideDown.Write((aUpsideDown!=0));
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::SetDisplayUpsideDown(IInvocationResponse& aResponse, TUint aVersion, TBool aaUpsideDown)
{
    ASSERT(iCallbackSetDisplayUpsideDown != NULL);
    if (0 != iCallbackSetDisplayUpsideDown(iPtrSetDisplayUpsideDown, aVersion, aaUpsideDown)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::SetDisplayScrollText(IInvocationResponse& aResponse, TUint aVersion, TBool aaDisplayScrollText)
{
    ASSERT(iCallbackSetDisplayScrollText != NULL);
    if (0 != iCallbackSetDisplayScrollText(iPtrSetDisplayScrollText, aVersion, aaDisplayScrollText)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::DisplayScrollText(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaDisplayScrollTextEnabled)
{
    uint32_t aDisplayScrollTextEnabled;
    ASSERT(iCallbackDisplayScrollText != NULL);
    if (0 != iCallbackDisplayScrollText(iPtrDisplayScrollText, aVersion, &aDisplayScrollTextEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaDisplayScrollTextEnabled.Write((aDisplayScrollTextEnabled!=0));
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::SetDisplaySleep(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled)
{
    ASSERT(iCallbackSetDisplaySleep != NULL);
    if (0 != iCallbackSetDisplaySleep(iPtrSetDisplaySleep, aVersion, aaEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::DisplaySleep(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled)
{
    uint32_t aEnabled;
    ASSERT(iCallbackDisplaySleep != NULL);
    if (0 != iCallbackDisplaySleep(iPtrDisplaySleep, aVersion, &aEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaEnabled.Write((aEnabled!=0));
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::SetDisplayLedOff(IInvocationResponse& aResponse, TUint aVersion, TBool aaOff)
{
    ASSERT(iCallbackSetDisplayLedOff != NULL);
    if (0 != iCallbackSetDisplayLedOff(iPtrSetDisplayLedOff, aVersion, aaOff)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkUi2C::DisplayLedOff(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaOff)
{
    uint32_t aOff;
    ASSERT(iCallbackDisplayLedOff != NULL);
    if (0 != iCallbackDisplayLedOff(iPtrDisplayLedOff, aVersion, &aOff)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaOff.Write((aOff!=0));
    aResponse.End();
}



THandle DvProviderLinnCoUkUi2Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkUi2C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkUi2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider);
}

void DvProviderLinnCoUkUi2EnableActionDisplayTestPattern(THandle aProvider, CallbackUi2DisplayTestPattern aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayTestPattern(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplayFill(THandle aProvider, CallbackUi2DisplayFill aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayFill(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplayClear(THandle aProvider, CallbackUi2DisplayClear aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayClear(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetTestModeEnabled(THandle aProvider, CallbackUi2SetTestModeEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetTestModeEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSimulateInfraredInput(THandle aProvider, CallbackUi2SimulateInfraredInput aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSimulateInfraredInput(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSimulateButtonInput(THandle aProvider, CallbackUi2SimulateButtonInput aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSimulateButtonInput(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSimulateLightSensor(THandle aProvider, CallbackUi2SimulateLightSensor aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSimulateLightSensor(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionGetLightSensorData(THandle aProvider, CallbackUi2GetLightSensorData aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionGetLightSensorData(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetDisplayBrightness(THandle aProvider, CallbackUi2SetDisplayBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetDisplayBrightness(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetDisplayBrightnessAuto(THandle aProvider, CallbackUi2SetDisplayBrightnessAuto aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetDisplayBrightnessAuto(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetInfraredCommands(THandle aProvider, CallbackUi2SetInfraredCommands aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetInfraredCommands(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionInfraredCommands(THandle aProvider, CallbackUi2InfraredCommands aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionInfraredCommands(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetInfraredTerminalCommands(THandle aProvider, CallbackUi2SetInfraredTerminalCommands aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetInfraredTerminalCommands(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionInfraredTerminalCommands(THandle aProvider, CallbackUi2InfraredTerminalCommands aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionInfraredTerminalCommands(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplayBrightness(THandle aProvider, CallbackUi2DisplayBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayBrightness(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplayBrightnessAuto(THandle aProvider, CallbackUi2DisplayBrightnessAuto aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayBrightnessAuto(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplayUpsideDown(THandle aProvider, CallbackUi2DisplayUpsideDown aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayUpsideDown(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetDisplayUpsideDown(THandle aProvider, CallbackUi2SetDisplayUpsideDown aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetDisplayUpsideDown(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetDisplayScrollText(THandle aProvider, CallbackUi2SetDisplayScrollText aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetDisplayScrollText(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplayScrollText(THandle aProvider, CallbackUi2DisplayScrollText aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayScrollText(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetDisplaySleep(THandle aProvider, CallbackUi2SetDisplaySleep aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetDisplaySleep(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplaySleep(THandle aProvider, CallbackUi2DisplaySleep aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplaySleep(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionSetDisplayLedOff(THandle aProvider, CallbackUi2SetDisplayLedOff aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionSetDisplayLedOff(aCallback, aPtr);
}

void DvProviderLinnCoUkUi2EnableActionDisplayLedOff(THandle aProvider, CallbackUi2DisplayLedOff aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->EnableActionDisplayLedOff(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkUi2SetPropertyDisplayBrightness(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyDisplayBrightness(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyDisplayBrightness(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyDisplayBrightness(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkUi2SetPropertyDisplayBrightnessAuto(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyDisplayBrightnessAuto((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyDisplayBrightnessAuto(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyDisplayBrightnessAuto(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkUi2SetPropertyInfraredCommands(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyInfraredCommands(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyInfraredCommands(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyInfraredCommands(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkUi2SetPropertyInfraredTerminalCommands(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyInfraredTerminalCommands(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyInfraredTerminalCommands(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyInfraredTerminalCommands(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkUi2SetPropertyDisplayUpsideDown(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyDisplayUpsideDown((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyDisplayUpsideDown(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyDisplayUpsideDown(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkUi2SetPropertyDisplayScrollText(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyDisplayScrollText((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyDisplayScrollText(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyDisplayScrollText(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkUi2SetPropertyDisplaySleep(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyDisplaySleep((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyDisplaySleep(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyDisplaySleep(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkUi2SetPropertyDisplayLedOff(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyDisplayLedOff((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyDisplayLedOff(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyDisplayLedOff(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkUi2SetPropertyTerminalInputCode(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyTerminalInputCode(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyTerminalInputCode(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyTerminalInputCode(val);
    *aValue = val;
}

int32_t DvProviderLinnCoUkUi2SetPropertyTerminalInputName(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyTerminalInputName(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyTerminalInputName(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyTerminalInputName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkUi2SetPropertyDisplayPixels(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->SetPropertyDisplayPixels(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkUi2GetPropertyDisplayPixels(THandle aProvider, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvProviderLinnCoUkUi2C*>(aProvider)->GetPropertyDisplayPixels(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

