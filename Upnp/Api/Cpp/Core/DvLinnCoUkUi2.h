#ifndef HEADER_DVLINNCOUKUI2
#define HEADER_DVLINNCOUKUI2

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Ui:2
 */
class DvServiceLinnCoUkUi2 : public DvService
{
public:
    virtual ~DvServiceLinnCoUkUi2() {}
    void SetPropertyDisplayBrightness(TUint aValue);
    void GetPropertyDisplayBrightness(TUint& aValue);
    void SetPropertyDisplayBrightnessAuto(TBool aValue);
    void GetPropertyDisplayBrightnessAuto(TBool& aValue);
    void SetPropertyInfraredCommands(const Brx& aValue);
    void GetPropertyInfraredCommands(Brhz& aValue);
    void SetPropertyInfraredTerminalCommands(const Brx& aValue);
    void GetPropertyInfraredTerminalCommands(Brhz& aValue);
    void SetPropertyDisplayUpsideDown(TBool aValue);
    void GetPropertyDisplayUpsideDown(TBool& aValue);
    void SetPropertyDisplayScrollText(TBool aValue);
    void GetPropertyDisplayScrollText(TBool& aValue);
    void SetPropertyDisplaySleep(TBool aValue);
    void GetPropertyDisplaySleep(TBool& aValue);
    void SetPropertyDisplayLedOff(TBool aValue);
    void GetPropertyDisplayLedOff(TBool& aValue);
    void SetPropertyTerminalInputCode(TUint aValue);
    void GetPropertyTerminalInputCode(TUint& aValue);
    void SetPropertyTerminalInputName(const Brx& aValue);
    void GetPropertyTerminalInputName(Brhz& aValue);
    void SetPropertyDisplayPixels(const Brx& aValue);
    void GetPropertyDisplayPixels(Brh& aValue);
protected:
    DvServiceLinnCoUkUi2(DvDevice& aDevice);
    void EnableActionDisplayTestPattern();
    void EnableActionDisplayFill();
    void EnableActionDisplayClear();
    void EnableActionSetTestModeEnabled();
    void EnableActionSimulateInfraredInput();
    void EnableActionSimulateButtonInput();
    void EnableActionSimulateLightSensor();
    void EnableActionGetLightSensorData();
    void EnableActionSetDisplayBrightness();
    void EnableActionSetDisplayBrightnessAuto();
    void EnableActionSetInfraredCommands();
    void EnableActionInfraredCommands();
    void EnableActionSetInfraredTerminalCommands();
    void EnableActionInfraredTerminalCommands();
    void EnableActionDisplayBrightness();
    void EnableActionDisplayBrightnessAuto();
    void EnableActionDisplayUpsideDown();
    void EnableActionSetDisplayUpsideDown();
    void EnableActionSetDisplayScrollText();
    void EnableActionDisplayScrollText();
    void EnableActionSetDisplaySleep();
    void EnableActionDisplaySleep();
    void EnableActionSetDisplayLedOff();
    void EnableActionDisplayLedOff();
private:
    virtual void DisplayTestPattern(IInvocationResponse& aResponse, TUint aVersion, TInt aaTestPattern);
    virtual void DisplayFill(IInvocationResponse& aResponse, TUint aVersion);
    virtual void DisplayClear(IInvocationResponse& aResponse, TUint aVersion);
    virtual void SetTestModeEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled);
    virtual void SimulateInfraredInput(IInvocationResponse& aResponse, TUint aVersion, TUint aaCode);
    virtual void SimulateButtonInput(IInvocationResponse& aResponse, TUint aVersion, TUint aaCode);
    virtual void SimulateLightSensor(IInvocationResponse& aResponse, TUint aVersion, TUint aaLightLevel);
    virtual void GetLightSensorData(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaLightLevel);
    virtual void SetDisplayBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aaBrightness);
    virtual void SetDisplayBrightnessAuto(IInvocationResponse& aResponse, TUint aVersion, TBool aaBrightnessAuto);
    virtual void SetInfraredCommands(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaCommands);
    virtual void InfraredCommands(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCommands);
    virtual void SetInfraredTerminalCommands(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaCommands);
    virtual void InfraredTerminalCommands(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCommands);
    virtual void DisplayBrightness(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaBrightness);
    virtual void DisplayBrightnessAuto(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaBrightnessAuto);
    virtual void DisplayUpsideDown(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaUpsideDown);
    virtual void SetDisplayUpsideDown(IInvocationResponse& aResponse, TUint aVersion, TBool aaUpsideDown);
    virtual void SetDisplayScrollText(IInvocationResponse& aResponse, TUint aVersion, TBool aaDisplayScrollText);
    virtual void DisplayScrollText(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaDisplayScrollTextEnabled);
    virtual void SetDisplaySleep(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled);
    virtual void DisplaySleep(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled);
    virtual void SetDisplayLedOff(IInvocationResponse& aResponse, TUint aVersion, TBool aaOff);
    virtual void DisplayLedOff(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaOff);
private:
    DvServiceLinnCoUkUi2();
    void DoDisplayTestPattern(IDvInvocation& aInvocation, TUint aVersion);
    void DoDisplayFill(IDvInvocation& aInvocation, TUint aVersion);
    void DoDisplayClear(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetTestModeEnabled(IDvInvocation& aInvocation, TUint aVersion);
    void DoSimulateInfraredInput(IDvInvocation& aInvocation, TUint aVersion);
    void DoSimulateButtonInput(IDvInvocation& aInvocation, TUint aVersion);
    void DoSimulateLightSensor(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetLightSensorData(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayBrightness(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayBrightnessAuto(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetInfraredCommands(IDvInvocation& aInvocation, TUint aVersion);
    void DoInfraredCommands(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetInfraredTerminalCommands(IDvInvocation& aInvocation, TUint aVersion);
    void DoInfraredTerminalCommands(IDvInvocation& aInvocation, TUint aVersion);
    void DoDisplayBrightness(IDvInvocation& aInvocation, TUint aVersion);
    void DoDisplayBrightnessAuto(IDvInvocation& aInvocation, TUint aVersion);
    void DoDisplayUpsideDown(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayUpsideDown(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayScrollText(IDvInvocation& aInvocation, TUint aVersion);
    void DoDisplayScrollText(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetDisplaySleep(IDvInvocation& aInvocation, TUint aVersion);
    void DoDisplaySleep(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayLedOff(IDvInvocation& aInvocation, TUint aVersion);
    void DoDisplayLedOff(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyDisplayBrightness;
    PropertyBool* iPropertyDisplayBrightnessAuto;
    PropertyString* iPropertyInfraredCommands;
    PropertyString* iPropertyInfraredTerminalCommands;
    PropertyBool* iPropertyDisplayUpsideDown;
    PropertyBool* iPropertyDisplayScrollText;
    PropertyBool* iPropertyDisplaySleep;
    PropertyBool* iPropertyDisplayLedOff;
    PropertyUint* iPropertyTerminalInputCode;
    PropertyString* iPropertyTerminalInputName;
    PropertyBinary* iPropertyDisplayPixels;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKUI2

