#include <C/DvLinnCoUkUi2.h>
#include <Core/DvLinnCoUkUi2.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkUi2C : public DvServiceLinnCoUkUi2
{
public:
    DvServiceLinnCoUkUi2C(DvDevice& aDevice);
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

DvServiceLinnCoUkUi2C::DvServiceLinnCoUkUi2C(DvDevice& aDevice)
    : DvServiceLinnCoUkUi2(aDevice)
{
}

void DvServiceLinnCoUkUi2C::EnableActionDisplayTestPattern(CallbackUi2DisplayTestPattern aCallback, void* aPtr)
{
    iCallbackDisplayTestPattern = aCallback;
    iPtrDisplayTestPattern = aPtr;
    DvServiceLinnCoUkUi2::EnableActionDisplayTestPattern();
}

void DvServiceLinnCoUkUi2C::EnableActionDisplayFill(CallbackUi2DisplayFill aCallback, void* aPtr)
{
    iCallbackDisplayFill = aCallback;
    iPtrDisplayFill = aPtr;
    DvServiceLinnCoUkUi2::EnableActionDisplayFill();
}

void DvServiceLinnCoUkUi2C::EnableActionDisplayClear(CallbackUi2DisplayClear aCallback, void* aPtr)
{
    iCallbackDisplayClear = aCallback;
    iPtrDisplayClear = aPtr;
    DvServiceLinnCoUkUi2::EnableActionDisplayClear();
}

void DvServiceLinnCoUkUi2C::EnableActionSetTestModeEnabled(CallbackUi2SetTestModeEnabled aCallback, void* aPtr)
{
    iCallbackSetTestModeEnabled = aCallback;
    iPtrSetTestModeEnabled = aPtr;
    DvServiceLinnCoUkUi2::EnableActionSetTestModeEnabled();
}

void DvServiceLinnCoUkUi2C::EnableActionSimulateInfraredInput(CallbackUi2SimulateInfraredInput aCallback, void* aPtr)
{
    iCallbackSimulateInfraredInput = aCallback;
    iPtrSimulateInfraredInput = aPtr;
    DvServiceLinnCoUkUi2::EnableActionSimulateInfraredInput();
}

void DvServiceLinnCoUkUi2C::EnableActionSimulateButtonInput(CallbackUi2SimulateButtonInput aCallback, void* aPtr)
{
    iCallbackSimulateButtonInput = aCallback;
    iPtrSimulateButtonInput = aPtr;
    DvServiceLinnCoUkUi2::EnableActionSimulateButtonInput();
}

void DvServiceLinnCoUkUi2C::EnableActionSimulateLightSensor(CallbackUi2SimulateLightSensor aCallback, void* aPtr)
{
    iCallbackSimulateLightSensor = aCallback;
    iPtrSimulateLightSensor = aPtr;
    DvServiceLinnCoUkUi2::EnableActionSimulateLightSensor();
}

void DvServiceLinnCoUkUi2C::EnableActionGetLightSensorData(CallbackUi2GetLightSensorData aCallback, void* aPtr)
{
    iCallbackGetLightSensorData = aCallback;
    iPtrGetLightSensorData = aPtr;
    DvServiceLinnCoUkUi2::EnableActionGetLightSensorData();
}

void DvServiceLinnCoUkUi2C::EnableActionSetDisplayBrightness(CallbackUi2SetDisplayBrightness aCallback, void* aPtr)
{
    iCallbackSetDisplayBrightness = aCallback;
    iPtrSetDisplayBrightness = aPtr;
    DvServiceLinnCoUkUi2::EnableActionSetDisplayBrightness();
}

void DvServiceLinnCoUkUi2C::EnableActionSetDisplayBrightnessAuto(CallbackUi2SetDisplayBrightnessAuto aCallback, void* aPtr)
{
    iCallbackSetDisplayBrightnessAuto = aCallback;
    iPtrSetDisplayBrightnessAuto = aPtr;
    DvServiceLinnCoUkUi2::EnableActionSetDisplayBrightnessAuto();
}

void DvServiceLinnCoUkUi2C::EnableActionSetInfraredCommands(CallbackUi2SetInfraredCommands aCallback, void* aPtr)
{
    iCallbackSetInfraredCommands = aCallback;
    iPtrSetInfraredCommands = aPtr;
    DvServiceLinnCoUkUi2::EnableActionSetInfraredCommands();
}

void DvServiceLinnCoUkUi2C::EnableActionInfraredCommands(CallbackUi2InfraredCommands aCallback, void* aPtr)
{
    iCallbackInfraredCommands = aCallback;
    iPtrInfraredCommands = aPtr;
    DvServiceLinnCoUkUi2::EnableActionInfraredCommands();
}

void DvServiceLinnCoUkUi2C::EnableActionSetInfraredTerminalCommands(CallbackUi2SetInfraredTerminalCommands aCallback, void* aPtr)
{
    iCallbackSetInfraredTerminalCommands = aCallback;
    iPtrSetInfraredTerminalCommands = aPtr;
    DvServiceLinnCoUkUi2::EnableActionSetInfraredTerminalCommands();
}

void DvServiceLinnCoUkUi2C::EnableActionInfraredTerminalCommands(CallbackUi2InfraredTerminalCommands aCallback, void* aPtr)
{
    iCallbackInfraredTerminalCommands = aCallback;
    iPtrInfraredTerminalCommands = aPtr;
    DvServiceLinnCoUkUi2::EnableActionInfraredTerminalCommands();
}

void DvServiceLinnCoUkUi2C::EnableActionDisplayBrightness(CallbackUi2DisplayBrightness aCallback, void* aPtr)
{
    iCallbackDisplayBrightness = aCallback;
    iPtrDisplayBrightness = aPtr;
    DvServiceLinnCoUkUi2::EnableActionDisplayBrightness();
}

void DvServiceLinnCoUkUi2C::EnableActionDisplayBrightnessAuto(CallbackUi2DisplayBrightnessAuto aCallback, void* aPtr)
{
    iCallbackDisplayBrightnessAuto = aCallback;
    iPtrDisplayBrightnessAuto = aPtr;
    DvServiceLinnCoUkUi2::EnableActionDisplayBrightnessAuto();
}

void DvServiceLinnCoUkUi2C::EnableActionDisplayUpsideDown(CallbackUi2DisplayUpsideDown aCallback, void* aPtr)
{
    iCallbackDisplayUpsideDown = aCallback;
    iPtrDisplayUpsideDown = aPtr;
    DvServiceLinnCoUkUi2::EnableActionDisplayUpsideDown();
}

void DvServiceLinnCoUkUi2C::EnableActionSetDisplayUpsideDown(CallbackUi2SetDisplayUpsideDown aCallback, void* aPtr)
{
    iCallbackSetDisplayUpsideDown = aCallback;
    iPtrSetDisplayUpsideDown = aPtr;
    DvServiceLinnCoUkUi2::EnableActionSetDisplayUpsideDown();
}

void DvServiceLinnCoUkUi2C::EnableActionSetDisplayScrollText(CallbackUi2SetDisplayScrollText aCallback, void* aPtr)
{
    iCallbackSetDisplayScrollText = aCallback;
    iPtrSetDisplayScrollText = aPtr;
    DvServiceLinnCoUkUi2::EnableActionSetDisplayScrollText();
}

void DvServiceLinnCoUkUi2C::EnableActionDisplayScrollText(CallbackUi2DisplayScrollText aCallback, void* aPtr)
{
    iCallbackDisplayScrollText = aCallback;
    iPtrDisplayScrollText = aPtr;
    DvServiceLinnCoUkUi2::EnableActionDisplayScrollText();
}

void DvServiceLinnCoUkUi2C::EnableActionSetDisplaySleep(CallbackUi2SetDisplaySleep aCallback, void* aPtr)
{
    iCallbackSetDisplaySleep = aCallback;
    iPtrSetDisplaySleep = aPtr;
    DvServiceLinnCoUkUi2::EnableActionSetDisplaySleep();
}

void DvServiceLinnCoUkUi2C::EnableActionDisplaySleep(CallbackUi2DisplaySleep aCallback, void* aPtr)
{
    iCallbackDisplaySleep = aCallback;
    iPtrDisplaySleep = aPtr;
    DvServiceLinnCoUkUi2::EnableActionDisplaySleep();
}

void DvServiceLinnCoUkUi2C::EnableActionSetDisplayLedOff(CallbackUi2SetDisplayLedOff aCallback, void* aPtr)
{
    iCallbackSetDisplayLedOff = aCallback;
    iPtrSetDisplayLedOff = aPtr;
    DvServiceLinnCoUkUi2::EnableActionSetDisplayLedOff();
}

void DvServiceLinnCoUkUi2C::EnableActionDisplayLedOff(CallbackUi2DisplayLedOff aCallback, void* aPtr)
{
    iCallbackDisplayLedOff = aCallback;
    iPtrDisplayLedOff = aPtr;
    DvServiceLinnCoUkUi2::EnableActionDisplayLedOff();
}

void DvServiceLinnCoUkUi2C::DisplayTestPattern(IInvocationResponse& aResponse, TUint aVersion, TInt aaTestPattern)
{
    ASSERT(iCallbackDisplayTestPattern != NULL);
    if (0 != iCallbackDisplayTestPattern(iPtrDisplayTestPattern, aVersion, aaTestPattern)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::DisplayFill(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackDisplayFill != NULL);
    if (0 != iCallbackDisplayFill(iPtrDisplayFill, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::DisplayClear(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackDisplayClear != NULL);
    if (0 != iCallbackDisplayClear(iPtrDisplayClear, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::SetTestModeEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled)
{
    ASSERT(iCallbackSetTestModeEnabled != NULL);
    if (0 != iCallbackSetTestModeEnabled(iPtrSetTestModeEnabled, aVersion, aaEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::SimulateInfraredInput(IInvocationResponse& aResponse, TUint aVersion, TUint aaCode)
{
    ASSERT(iCallbackSimulateInfraredInput != NULL);
    if (0 != iCallbackSimulateInfraredInput(iPtrSimulateInfraredInput, aVersion, aaCode)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::SimulateButtonInput(IInvocationResponse& aResponse, TUint aVersion, TUint aaCode)
{
    ASSERT(iCallbackSimulateButtonInput != NULL);
    if (0 != iCallbackSimulateButtonInput(iPtrSimulateButtonInput, aVersion, aaCode)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::SimulateLightSensor(IInvocationResponse& aResponse, TUint aVersion, TUint aaLightLevel)
{
    ASSERT(iCallbackSimulateLightSensor != NULL);
    if (0 != iCallbackSimulateLightSensor(iPtrSimulateLightSensor, aVersion, aaLightLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::GetLightSensorData(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaLightLevel)
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

void DvServiceLinnCoUkUi2C::SetDisplayBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aaBrightness)
{
    ASSERT(iCallbackSetDisplayBrightness != NULL);
    if (0 != iCallbackSetDisplayBrightness(iPtrSetDisplayBrightness, aVersion, aaBrightness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::SetDisplayBrightnessAuto(IInvocationResponse& aResponse, TUint aVersion, TBool aaBrightnessAuto)
{
    ASSERT(iCallbackSetDisplayBrightnessAuto != NULL);
    if (0 != iCallbackSetDisplayBrightnessAuto(iPtrSetDisplayBrightnessAuto, aVersion, aaBrightnessAuto)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::SetInfraredCommands(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaCommands)
{
    ASSERT(iCallbackSetInfraredCommands != NULL);
    if (0 != iCallbackSetInfraredCommands(iPtrSetInfraredCommands, aVersion, (const char*)aaCommands.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::InfraredCommands(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCommands)
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

void DvServiceLinnCoUkUi2C::SetInfraredTerminalCommands(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaCommands)
{
    ASSERT(iCallbackSetInfraredTerminalCommands != NULL);
    if (0 != iCallbackSetInfraredTerminalCommands(iPtrSetInfraredTerminalCommands, aVersion, (const char*)aaCommands.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::InfraredTerminalCommands(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCommands)
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

void DvServiceLinnCoUkUi2C::DisplayBrightness(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaBrightness)
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

void DvServiceLinnCoUkUi2C::DisplayBrightnessAuto(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaBrightnessAuto)
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

void DvServiceLinnCoUkUi2C::DisplayUpsideDown(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaUpsideDown)
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

void DvServiceLinnCoUkUi2C::SetDisplayUpsideDown(IInvocationResponse& aResponse, TUint aVersion, TBool aaUpsideDown)
{
    ASSERT(iCallbackSetDisplayUpsideDown != NULL);
    if (0 != iCallbackSetDisplayUpsideDown(iPtrSetDisplayUpsideDown, aVersion, aaUpsideDown)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::SetDisplayScrollText(IInvocationResponse& aResponse, TUint aVersion, TBool aaDisplayScrollText)
{
    ASSERT(iCallbackSetDisplayScrollText != NULL);
    if (0 != iCallbackSetDisplayScrollText(iPtrSetDisplayScrollText, aVersion, aaDisplayScrollText)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::DisplayScrollText(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaDisplayScrollTextEnabled)
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

void DvServiceLinnCoUkUi2C::SetDisplaySleep(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled)
{
    ASSERT(iCallbackSetDisplaySleep != NULL);
    if (0 != iCallbackSetDisplaySleep(iPtrSetDisplaySleep, aVersion, aaEnabled)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::DisplaySleep(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled)
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

void DvServiceLinnCoUkUi2C::SetDisplayLedOff(IInvocationResponse& aResponse, TUint aVersion, TBool aaOff)
{
    ASSERT(iCallbackSetDisplayLedOff != NULL);
    if (0 != iCallbackSetDisplayLedOff(iPtrSetDisplayLedOff, aVersion, aaOff)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkUi2C::DisplayLedOff(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaOff)
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



THandle DvServiceLinnCoUkUi2Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkUi2C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkUi2Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService);
}

void DvServiceLinnCoUkUi2EnableActionDisplayTestPattern(THandle aService, CallbackUi2DisplayTestPattern aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionDisplayTestPattern(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionDisplayFill(THandle aService, CallbackUi2DisplayFill aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionDisplayFill(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionDisplayClear(THandle aService, CallbackUi2DisplayClear aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionDisplayClear(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionSetTestModeEnabled(THandle aService, CallbackUi2SetTestModeEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionSetTestModeEnabled(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionSimulateInfraredInput(THandle aService, CallbackUi2SimulateInfraredInput aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionSimulateInfraredInput(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionSimulateButtonInput(THandle aService, CallbackUi2SimulateButtonInput aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionSimulateButtonInput(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionSimulateLightSensor(THandle aService, CallbackUi2SimulateLightSensor aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionSimulateLightSensor(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionGetLightSensorData(THandle aService, CallbackUi2GetLightSensorData aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionGetLightSensorData(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionSetDisplayBrightness(THandle aService, CallbackUi2SetDisplayBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionSetDisplayBrightness(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionSetDisplayBrightnessAuto(THandle aService, CallbackUi2SetDisplayBrightnessAuto aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionSetDisplayBrightnessAuto(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionSetInfraredCommands(THandle aService, CallbackUi2SetInfraredCommands aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionSetInfraredCommands(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionInfraredCommands(THandle aService, CallbackUi2InfraredCommands aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionInfraredCommands(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionSetInfraredTerminalCommands(THandle aService, CallbackUi2SetInfraredTerminalCommands aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionSetInfraredTerminalCommands(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionInfraredTerminalCommands(THandle aService, CallbackUi2InfraredTerminalCommands aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionInfraredTerminalCommands(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionDisplayBrightness(THandle aService, CallbackUi2DisplayBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionDisplayBrightness(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionDisplayBrightnessAuto(THandle aService, CallbackUi2DisplayBrightnessAuto aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionDisplayBrightnessAuto(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionDisplayUpsideDown(THandle aService, CallbackUi2DisplayUpsideDown aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionDisplayUpsideDown(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionSetDisplayUpsideDown(THandle aService, CallbackUi2SetDisplayUpsideDown aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionSetDisplayUpsideDown(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionSetDisplayScrollText(THandle aService, CallbackUi2SetDisplayScrollText aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionSetDisplayScrollText(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionDisplayScrollText(THandle aService, CallbackUi2DisplayScrollText aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionDisplayScrollText(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionSetDisplaySleep(THandle aService, CallbackUi2SetDisplaySleep aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionSetDisplaySleep(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionDisplaySleep(THandle aService, CallbackUi2DisplaySleep aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionDisplaySleep(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionSetDisplayLedOff(THandle aService, CallbackUi2SetDisplayLedOff aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionSetDisplayLedOff(aCallback, aPtr);
}

void DvServiceLinnCoUkUi2EnableActionDisplayLedOff(THandle aService, CallbackUi2DisplayLedOff aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->EnableActionDisplayLedOff(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkUi2SetPropertyDisplayBrightness(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->SetPropertyDisplayBrightness(aValue);
    return 0;
}

void DvServiceLinnCoUkUi2GetPropertyDisplayBrightness(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->GetPropertyDisplayBrightness(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkUi2SetPropertyDisplayBrightnessAuto(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->SetPropertyDisplayBrightnessAuto((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkUi2GetPropertyDisplayBrightnessAuto(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->GetPropertyDisplayBrightnessAuto(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceLinnCoUkUi2SetPropertyInfraredCommands(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->SetPropertyInfraredCommands(buf);
    return 0;
}

void DvServiceLinnCoUkUi2GetPropertyInfraredCommands(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->GetPropertyInfraredCommands(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkUi2SetPropertyInfraredTerminalCommands(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->SetPropertyInfraredTerminalCommands(buf);
    return 0;
}

void DvServiceLinnCoUkUi2GetPropertyInfraredTerminalCommands(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->GetPropertyInfraredTerminalCommands(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkUi2SetPropertyDisplayUpsideDown(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->SetPropertyDisplayUpsideDown((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkUi2GetPropertyDisplayUpsideDown(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->GetPropertyDisplayUpsideDown(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceLinnCoUkUi2SetPropertyDisplayScrollText(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->SetPropertyDisplayScrollText((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkUi2GetPropertyDisplayScrollText(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->GetPropertyDisplayScrollText(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceLinnCoUkUi2SetPropertyDisplaySleep(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->SetPropertyDisplaySleep((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkUi2GetPropertyDisplaySleep(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->GetPropertyDisplaySleep(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceLinnCoUkUi2SetPropertyDisplayLedOff(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->SetPropertyDisplayLedOff((aValue!=0));
    return 0;
}

void DvServiceLinnCoUkUi2GetPropertyDisplayLedOff(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->GetPropertyDisplayLedOff(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceLinnCoUkUi2SetPropertyTerminalInputCode(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->SetPropertyTerminalInputCode(aValue);
    return 0;
}

void DvServiceLinnCoUkUi2GetPropertyTerminalInputCode(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->GetPropertyTerminalInputCode(val);
    *aValue = val;
}

int32_t DvServiceLinnCoUkUi2SetPropertyTerminalInputName(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->SetPropertyTerminalInputName(buf);
    return 0;
}

void DvServiceLinnCoUkUi2GetPropertyTerminalInputName(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->GetPropertyTerminalInputName(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceLinnCoUkUi2SetPropertyDisplayPixels(THandle aService, const char* aValue, uint32_t aValueLen)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->SetPropertyDisplayPixels(buf);
    return 0;
}

void DvServiceLinnCoUkUi2GetPropertyDisplayPixels(THandle aService, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvServiceLinnCoUkUi2C*>(aService)->GetPropertyDisplayPixels(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

