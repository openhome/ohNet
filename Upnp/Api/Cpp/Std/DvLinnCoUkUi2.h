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
 * Provider for the linn.co.uk:Ui:2 UPnP service
 */
class DvProviderLinnCoUkUi2Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkUi2Cpp() {}
    /**
     * Set the value of the DisplayBrightness property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDisplayBrightness(uint32_t aValue);
    /**
     * Get a copy of the value of the DisplayBrightness property
     */
    void GetPropertyDisplayBrightness(uint32_t& aValue);
    /**
     * Set the value of the DisplayBrightnessAuto property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDisplayBrightnessAuto(bool aValue);
    /**
     * Get a copy of the value of the DisplayBrightnessAuto property
     */
    void GetPropertyDisplayBrightnessAuto(bool& aValue);
    /**
     * Set the value of the InfraredCommands property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyInfraredCommands(const std::string& aValue);
    /**
     * Get a copy of the value of the InfraredCommands property
     */
    void GetPropertyInfraredCommands(std::string& aValue);
    /**
     * Set the value of the InfraredTerminalCommands property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyInfraredTerminalCommands(const std::string& aValue);
    /**
     * Get a copy of the value of the InfraredTerminalCommands property
     */
    void GetPropertyInfraredTerminalCommands(std::string& aValue);
    /**
     * Set the value of the DisplayUpsideDown property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDisplayUpsideDown(bool aValue);
    /**
     * Get a copy of the value of the DisplayUpsideDown property
     */
    void GetPropertyDisplayUpsideDown(bool& aValue);
    /**
     * Set the value of the DisplayScrollText property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDisplayScrollText(bool aValue);
    /**
     * Get a copy of the value of the DisplayScrollText property
     */
    void GetPropertyDisplayScrollText(bool& aValue);
    /**
     * Set the value of the DisplaySleep property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDisplaySleep(bool aValue);
    /**
     * Get a copy of the value of the DisplaySleep property
     */
    void GetPropertyDisplaySleep(bool& aValue);
    /**
     * Set the value of the DisplayLedOff property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDisplayLedOff(bool aValue);
    /**
     * Get a copy of the value of the DisplayLedOff property
     */
    void GetPropertyDisplayLedOff(bool& aValue);
    /**
     * Set the value of the TerminalInputCode property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTerminalInputCode(uint32_t aValue);
    /**
     * Get a copy of the value of the TerminalInputCode property
     */
    void GetPropertyTerminalInputCode(uint32_t& aValue);
    /**
     * Set the value of the TerminalInputName property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTerminalInputName(const std::string& aValue);
    /**
     * Get a copy of the value of the TerminalInputName property
     */
    void GetPropertyTerminalInputName(std::string& aValue);
    /**
     * Set the value of the DisplayPixels property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDisplayPixels(const std::string& aValue);
    /**
     * Get a copy of the value of the DisplayPixels property
     */
    void GetPropertyDisplayPixels(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkUi2Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action DisplayTestPattern is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDisplayTestPattern must be overridden if this is called.
     */
    void EnableActionDisplayTestPattern();
    /**
     * Signal that the action DisplayFill is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDisplayFill must be overridden if this is called.
     */
    void EnableActionDisplayFill();
    /**
     * Signal that the action DisplayClear is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDisplayClear must be overridden if this is called.
     */
    void EnableActionDisplayClear();
    /**
     * Signal that the action SetTestModeEnabled is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetTestModeEnabled must be overridden if this is called.
     */
    void EnableActionSetTestModeEnabled();
    /**
     * Signal that the action SimulateInfraredInput is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSimulateInfraredInput must be overridden if this is called.
     */
    void EnableActionSimulateInfraredInput();
    /**
     * Signal that the action SimulateButtonInput is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSimulateButtonInput must be overridden if this is called.
     */
    void EnableActionSimulateButtonInput();
    /**
     * Signal that the action SimulateLightSensor is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSimulateLightSensor must be overridden if this is called.
     */
    void EnableActionSimulateLightSensor();
    /**
     * Signal that the action GetLightSensorData is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetLightSensorData must be overridden if this is called.
     */
    void EnableActionGetLightSensorData();
    /**
     * Signal that the action SetDisplayBrightness is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetDisplayBrightness must be overridden if this is called.
     */
    void EnableActionSetDisplayBrightness();
    /**
     * Signal that the action SetDisplayBrightnessAuto is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetDisplayBrightnessAuto must be overridden if this is called.
     */
    void EnableActionSetDisplayBrightnessAuto();
    /**
     * Signal that the action SetInfraredCommands is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetInfraredCommands must be overridden if this is called.
     */
    void EnableActionSetInfraredCommands();
    /**
     * Signal that the action InfraredCommands is supported.
     * The action's availability will be published in the device's service.xml.
     * DoInfraredCommands must be overridden if this is called.
     */
    void EnableActionInfraredCommands();
    /**
     * Signal that the action SetInfraredTerminalCommands is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetInfraredTerminalCommands must be overridden if this is called.
     */
    void EnableActionSetInfraredTerminalCommands();
    /**
     * Signal that the action InfraredTerminalCommands is supported.
     * The action's availability will be published in the device's service.xml.
     * DoInfraredTerminalCommands must be overridden if this is called.
     */
    void EnableActionInfraredTerminalCommands();
    /**
     * Signal that the action DisplayBrightness is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDisplayBrightness must be overridden if this is called.
     */
    void EnableActionDisplayBrightness();
    /**
     * Signal that the action DisplayBrightnessAuto is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDisplayBrightnessAuto must be overridden if this is called.
     */
    void EnableActionDisplayBrightnessAuto();
    /**
     * Signal that the action DisplayUpsideDown is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDisplayUpsideDown must be overridden if this is called.
     */
    void EnableActionDisplayUpsideDown();
    /**
     * Signal that the action SetDisplayUpsideDown is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetDisplayUpsideDown must be overridden if this is called.
     */
    void EnableActionSetDisplayUpsideDown();
    /**
     * Signal that the action SetDisplayScrollText is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetDisplayScrollText must be overridden if this is called.
     */
    void EnableActionSetDisplayScrollText();
    /**
     * Signal that the action DisplayScrollText is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDisplayScrollText must be overridden if this is called.
     */
    void EnableActionDisplayScrollText();
    /**
     * Signal that the action SetDisplaySleep is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetDisplaySleep must be overridden if this is called.
     */
    void EnableActionSetDisplaySleep();
    /**
     * Signal that the action DisplaySleep is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDisplaySleep must be overridden if this is called.
     */
    void EnableActionDisplaySleep();
    /**
     * Signal that the action SetDisplayLedOff is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetDisplayLedOff must be overridden if this is called.
     */
    void EnableActionSetDisplayLedOff();
    /**
     * Signal that the action DisplayLedOff is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDisplayLedOff must be overridden if this is called.
     */
    void EnableActionDisplayLedOff();
private:
    /**
     * DisplayTestPattern action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayTestPattern action for the owning device.
     * Must be implemented iff EnableActionDisplayTestPattern was called.
     */
    virtual void DisplayTestPattern(uint32_t aVersion, int32_t aaTestPattern);
    /**
     * DisplayFill action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayFill action for the owning device.
     * Must be implemented iff EnableActionDisplayFill was called.
     */
    virtual void DisplayFill(uint32_t aVersion);
    /**
     * DisplayClear action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayClear action for the owning device.
     * Must be implemented iff EnableActionDisplayClear was called.
     */
    virtual void DisplayClear(uint32_t aVersion);
    /**
     * SetTestModeEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetTestModeEnabled action for the owning device.
     * Must be implemented iff EnableActionSetTestModeEnabled was called.
     */
    virtual void SetTestModeEnabled(uint32_t aVersion, bool aaEnabled);
    /**
     * SimulateInfraredInput action.
     *
     * Will be called when the device stack receives an invocation of the
     * SimulateInfraredInput action for the owning device.
     * Must be implemented iff EnableActionSimulateInfraredInput was called.
     */
    virtual void SimulateInfraredInput(uint32_t aVersion, uint32_t aaCode);
    /**
     * SimulateButtonInput action.
     *
     * Will be called when the device stack receives an invocation of the
     * SimulateButtonInput action for the owning device.
     * Must be implemented iff EnableActionSimulateButtonInput was called.
     */
    virtual void SimulateButtonInput(uint32_t aVersion, uint32_t aaCode);
    /**
     * SimulateLightSensor action.
     *
     * Will be called when the device stack receives an invocation of the
     * SimulateLightSensor action for the owning device.
     * Must be implemented iff EnableActionSimulateLightSensor was called.
     */
    virtual void SimulateLightSensor(uint32_t aVersion, uint32_t aaLightLevel);
    /**
     * GetLightSensorData action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetLightSensorData action for the owning device.
     * Must be implemented iff EnableActionGetLightSensorData was called.
     */
    virtual void GetLightSensorData(uint32_t aVersion, uint32_t& aaLightLevel);
    /**
     * SetDisplayBrightness action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDisplayBrightness action for the owning device.
     * Must be implemented iff EnableActionSetDisplayBrightness was called.
     */
    virtual void SetDisplayBrightness(uint32_t aVersion, uint32_t aaBrightness);
    /**
     * SetDisplayBrightnessAuto action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDisplayBrightnessAuto action for the owning device.
     * Must be implemented iff EnableActionSetDisplayBrightnessAuto was called.
     */
    virtual void SetDisplayBrightnessAuto(uint32_t aVersion, bool aaBrightnessAuto);
    /**
     * SetInfraredCommands action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetInfraredCommands action for the owning device.
     * Must be implemented iff EnableActionSetInfraredCommands was called.
     */
    virtual void SetInfraredCommands(uint32_t aVersion, const std::string& aaCommands);
    /**
     * InfraredCommands action.
     *
     * Will be called when the device stack receives an invocation of the
     * InfraredCommands action for the owning device.
     * Must be implemented iff EnableActionInfraredCommands was called.
     */
    virtual void InfraredCommands(uint32_t aVersion, std::string& aaCommands);
    /**
     * SetInfraredTerminalCommands action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetInfraredTerminalCommands action for the owning device.
     * Must be implemented iff EnableActionSetInfraredTerminalCommands was called.
     */
    virtual void SetInfraredTerminalCommands(uint32_t aVersion, const std::string& aaCommands);
    /**
     * InfraredTerminalCommands action.
     *
     * Will be called when the device stack receives an invocation of the
     * InfraredTerminalCommands action for the owning device.
     * Must be implemented iff EnableActionInfraredTerminalCommands was called.
     */
    virtual void InfraredTerminalCommands(uint32_t aVersion, std::string& aaCommands);
    /**
     * DisplayBrightness action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayBrightness action for the owning device.
     * Must be implemented iff EnableActionDisplayBrightness was called.
     */
    virtual void DisplayBrightness(uint32_t aVersion, uint32_t& aaBrightness);
    /**
     * DisplayBrightnessAuto action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayBrightnessAuto action for the owning device.
     * Must be implemented iff EnableActionDisplayBrightnessAuto was called.
     */
    virtual void DisplayBrightnessAuto(uint32_t aVersion, bool& aaBrightnessAuto);
    /**
     * DisplayUpsideDown action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayUpsideDown action for the owning device.
     * Must be implemented iff EnableActionDisplayUpsideDown was called.
     */
    virtual void DisplayUpsideDown(uint32_t aVersion, bool& aaUpsideDown);
    /**
     * SetDisplayUpsideDown action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDisplayUpsideDown action for the owning device.
     * Must be implemented iff EnableActionSetDisplayUpsideDown was called.
     */
    virtual void SetDisplayUpsideDown(uint32_t aVersion, bool aaUpsideDown);
    /**
     * SetDisplayScrollText action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDisplayScrollText action for the owning device.
     * Must be implemented iff EnableActionSetDisplayScrollText was called.
     */
    virtual void SetDisplayScrollText(uint32_t aVersion, bool aaDisplayScrollText);
    /**
     * DisplayScrollText action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayScrollText action for the owning device.
     * Must be implemented iff EnableActionDisplayScrollText was called.
     */
    virtual void DisplayScrollText(uint32_t aVersion, bool& aaDisplayScrollTextEnabled);
    /**
     * SetDisplaySleep action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDisplaySleep action for the owning device.
     * Must be implemented iff EnableActionSetDisplaySleep was called.
     */
    virtual void SetDisplaySleep(uint32_t aVersion, bool aaEnabled);
    /**
     * DisplaySleep action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplaySleep action for the owning device.
     * Must be implemented iff EnableActionDisplaySleep was called.
     */
    virtual void DisplaySleep(uint32_t aVersion, bool& aaEnabled);
    /**
     * SetDisplayLedOff action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDisplayLedOff action for the owning device.
     * Must be implemented iff EnableActionSetDisplayLedOff was called.
     */
    virtual void SetDisplayLedOff(uint32_t aVersion, bool aaOff);
    /**
     * DisplayLedOff action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayLedOff action for the owning device.
     * Must be implemented iff EnableActionDisplayLedOff was called.
     */
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

