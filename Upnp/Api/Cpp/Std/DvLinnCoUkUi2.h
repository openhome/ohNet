#ifndef HEADER_DVLINNCOUKUI2CPP
#define HEADER_DVLINNCOUKUI2CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Ui:2
 */
class DvProviderLinnCoUkUi2Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkUi2Cpp() {}
    bool SetPropertyDisplayBrightness(uint32_t aValue);
    void GetPropertyDisplayBrightness(uint32_t& aValue);
    bool SetPropertyDisplayBrightnessAuto(bool aValue);
    void GetPropertyDisplayBrightnessAuto(bool& aValue);
    bool SetPropertyInfraredCommands(const std::string& aValue);
    void GetPropertyInfraredCommands(std::string& aValue);
    bool SetPropertyInfraredTerminalCommands(const std::string& aValue);
    void GetPropertyInfraredTerminalCommands(std::string& aValue);
    bool SetPropertyDisplayUpsideDown(bool aValue);
    void GetPropertyDisplayUpsideDown(bool& aValue);
    bool SetPropertyDisplayScrollText(bool aValue);
    void GetPropertyDisplayScrollText(bool& aValue);
    bool SetPropertyDisplaySleep(bool aValue);
    void GetPropertyDisplaySleep(bool& aValue);
    bool SetPropertyDisplayLedOff(bool aValue);
    void GetPropertyDisplayLedOff(bool& aValue);
    bool SetPropertyTerminalInputCode(uint32_t aValue);
    void GetPropertyTerminalInputCode(uint32_t& aValue);
    bool SetPropertyTerminalInputName(const std::string& aValue);
    void GetPropertyTerminalInputName(std::string& aValue);
    bool SetPropertyDisplayPixels(const std::string& aValue);
    void GetPropertyDisplayPixels(std::string& aValue);
protected:
    DvProviderLinnCoUkUi2Cpp(DvDeviceStd& aDevice);
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
    virtual void DisplayTestPattern(uint32_t aVersion, int32_t aaTestPattern);
    virtual void DisplayFill(uint32_t aVersion);
    virtual void DisplayClear(uint32_t aVersion);
    virtual void SetTestModeEnabled(uint32_t aVersion, bool aaEnabled);
    virtual void SimulateInfraredInput(uint32_t aVersion, uint32_t aaCode);
    virtual void SimulateButtonInput(uint32_t aVersion, uint32_t aaCode);
    virtual void SimulateLightSensor(uint32_t aVersion, uint32_t aaLightLevel);
    virtual void GetLightSensorData(uint32_t aVersion, uint32_t& aaLightLevel);
    virtual void SetDisplayBrightness(uint32_t aVersion, uint32_t aaBrightness);
    virtual void SetDisplayBrightnessAuto(uint32_t aVersion, bool aaBrightnessAuto);
    virtual void SetInfraredCommands(uint32_t aVersion, const std::string& aaCommands);
    virtual void InfraredCommands(uint32_t aVersion, std::string& aaCommands);
    virtual void SetInfraredTerminalCommands(uint32_t aVersion, const std::string& aaCommands);
    virtual void InfraredTerminalCommands(uint32_t aVersion, std::string& aaCommands);
    virtual void DisplayBrightness(uint32_t aVersion, uint32_t& aaBrightness);
    virtual void DisplayBrightnessAuto(uint32_t aVersion, bool& aaBrightnessAuto);
    virtual void DisplayUpsideDown(uint32_t aVersion, bool& aaUpsideDown);
    virtual void SetDisplayUpsideDown(uint32_t aVersion, bool aaUpsideDown);
    virtual void SetDisplayScrollText(uint32_t aVersion, bool aaDisplayScrollText);
    virtual void DisplayScrollText(uint32_t aVersion, bool& aaDisplayScrollTextEnabled);
    virtual void SetDisplaySleep(uint32_t aVersion, bool aaEnabled);
    virtual void DisplaySleep(uint32_t aVersion, bool& aaEnabled);
    virtual void SetDisplayLedOff(uint32_t aVersion, bool aaOff);
    virtual void DisplayLedOff(uint32_t aVersion, bool& aaOff);
private:
    DvProviderLinnCoUkUi2Cpp();
    void DoDisplayTestPattern(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDisplayFill(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDisplayClear(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetTestModeEnabled(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSimulateInfraredInput(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSimulateButtonInput(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSimulateLightSensor(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetLightSensorData(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetDisplayBrightness(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetDisplayBrightnessAuto(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetInfraredCommands(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoInfraredCommands(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetInfraredTerminalCommands(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoInfraredTerminalCommands(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDisplayBrightness(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDisplayBrightnessAuto(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDisplayUpsideDown(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetDisplayUpsideDown(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetDisplayScrollText(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDisplayScrollText(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetDisplaySleep(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDisplaySleep(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetDisplayLedOff(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDisplayLedOff(IDviInvocation& aInvocation, uint32_t aVersion);
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

#endif // HEADER_DVLINNCOUKUI2CPP

