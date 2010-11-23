#ifndef HEADER_DVLINNCOUKUI2
#define HEADER_DVLINNCOUKUI2

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

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
class DvProviderLinnCoUkUi2 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkUi2() {}
    /**
     * Set the value of the DisplayBrightness property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDisplayBrightness(TUint aValue);
    /**
     * Get a copy of the value of the DisplayBrightness property
     */
    void GetPropertyDisplayBrightness(TUint& aValue);
    /**
     * Set the value of the DisplayBrightnessAuto property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDisplayBrightnessAuto(TBool aValue);
    /**
     * Get a copy of the value of the DisplayBrightnessAuto property
     */
    void GetPropertyDisplayBrightnessAuto(TBool& aValue);
    /**
     * Set the value of the InfraredCommands property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyInfraredCommands(const Brx& aValue);
    /**
     * Get a copy of the value of the InfraredCommands property
     */
    void GetPropertyInfraredCommands(Brhz& aValue);
    /**
     * Set the value of the InfraredTerminalCommands property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyInfraredTerminalCommands(const Brx& aValue);
    /**
     * Get a copy of the value of the InfraredTerminalCommands property
     */
    void GetPropertyInfraredTerminalCommands(Brhz& aValue);
    /**
     * Set the value of the DisplayUpsideDown property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDisplayUpsideDown(TBool aValue);
    /**
     * Get a copy of the value of the DisplayUpsideDown property
     */
    void GetPropertyDisplayUpsideDown(TBool& aValue);
    /**
     * Set the value of the DisplayScrollText property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDisplayScrollText(TBool aValue);
    /**
     * Get a copy of the value of the DisplayScrollText property
     */
    void GetPropertyDisplayScrollText(TBool& aValue);
    /**
     * Set the value of the DisplaySleep property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDisplaySleep(TBool aValue);
    /**
     * Get a copy of the value of the DisplaySleep property
     */
    void GetPropertyDisplaySleep(TBool& aValue);
    /**
     * Set the value of the DisplayLedOff property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDisplayLedOff(TBool aValue);
    /**
     * Get a copy of the value of the DisplayLedOff property
     */
    void GetPropertyDisplayLedOff(TBool& aValue);
    /**
     * Set the value of the TerminalInputCode property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTerminalInputCode(TUint aValue);
    /**
     * Get a copy of the value of the TerminalInputCode property
     */
    void GetPropertyTerminalInputCode(TUint& aValue);
    /**
     * Set the value of the TerminalInputName property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTerminalInputName(const Brx& aValue);
    /**
     * Get a copy of the value of the TerminalInputName property
     */
    void GetPropertyTerminalInputName(Brhz& aValue);
    /**
     * Set the value of the DisplayPixels property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDisplayPixels(const Brx& aValue);
    /**
     * Get a copy of the value of the DisplayPixels property
     */
    void GetPropertyDisplayPixels(Brh& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkUi2(DvDevice& aDevice);
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
    virtual void DisplayTestPattern(IInvocationResponse& aResponse, TUint aVersion, TInt aaTestPattern);
    /**
     * DisplayFill action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayFill action for the owning device.
     * Must be implemented iff EnableActionDisplayFill was called.
     */
    virtual void DisplayFill(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * DisplayClear action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayClear action for the owning device.
     * Must be implemented iff EnableActionDisplayClear was called.
     */
    virtual void DisplayClear(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * SetTestModeEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetTestModeEnabled action for the owning device.
     * Must be implemented iff EnableActionSetTestModeEnabled was called.
     */
    virtual void SetTestModeEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled);
    /**
     * SimulateInfraredInput action.
     *
     * Will be called when the device stack receives an invocation of the
     * SimulateInfraredInput action for the owning device.
     * Must be implemented iff EnableActionSimulateInfraredInput was called.
     */
    virtual void SimulateInfraredInput(IInvocationResponse& aResponse, TUint aVersion, TUint aaCode);
    /**
     * SimulateButtonInput action.
     *
     * Will be called when the device stack receives an invocation of the
     * SimulateButtonInput action for the owning device.
     * Must be implemented iff EnableActionSimulateButtonInput was called.
     */
    virtual void SimulateButtonInput(IInvocationResponse& aResponse, TUint aVersion, TUint aaCode);
    /**
     * SimulateLightSensor action.
     *
     * Will be called when the device stack receives an invocation of the
     * SimulateLightSensor action for the owning device.
     * Must be implemented iff EnableActionSimulateLightSensor was called.
     */
    virtual void SimulateLightSensor(IInvocationResponse& aResponse, TUint aVersion, TUint aaLightLevel);
    /**
     * GetLightSensorData action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetLightSensorData action for the owning device.
     * Must be implemented iff EnableActionGetLightSensorData was called.
     */
    virtual void GetLightSensorData(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaLightLevel);
    /**
     * SetDisplayBrightness action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDisplayBrightness action for the owning device.
     * Must be implemented iff EnableActionSetDisplayBrightness was called.
     */
    virtual void SetDisplayBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aaBrightness);
    /**
     * SetDisplayBrightnessAuto action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDisplayBrightnessAuto action for the owning device.
     * Must be implemented iff EnableActionSetDisplayBrightnessAuto was called.
     */
    virtual void SetDisplayBrightnessAuto(IInvocationResponse& aResponse, TUint aVersion, TBool aaBrightnessAuto);
    /**
     * SetInfraredCommands action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetInfraredCommands action for the owning device.
     * Must be implemented iff EnableActionSetInfraredCommands was called.
     */
    virtual void SetInfraredCommands(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaCommands);
    /**
     * InfraredCommands action.
     *
     * Will be called when the device stack receives an invocation of the
     * InfraredCommands action for the owning device.
     * Must be implemented iff EnableActionInfraredCommands was called.
     */
    virtual void InfraredCommands(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCommands);
    /**
     * SetInfraredTerminalCommands action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetInfraredTerminalCommands action for the owning device.
     * Must be implemented iff EnableActionSetInfraredTerminalCommands was called.
     */
    virtual void SetInfraredTerminalCommands(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaCommands);
    /**
     * InfraredTerminalCommands action.
     *
     * Will be called when the device stack receives an invocation of the
     * InfraredTerminalCommands action for the owning device.
     * Must be implemented iff EnableActionInfraredTerminalCommands was called.
     */
    virtual void InfraredTerminalCommands(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCommands);
    /**
     * DisplayBrightness action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayBrightness action for the owning device.
     * Must be implemented iff EnableActionDisplayBrightness was called.
     */
    virtual void DisplayBrightness(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaBrightness);
    /**
     * DisplayBrightnessAuto action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayBrightnessAuto action for the owning device.
     * Must be implemented iff EnableActionDisplayBrightnessAuto was called.
     */
    virtual void DisplayBrightnessAuto(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaBrightnessAuto);
    /**
     * DisplayUpsideDown action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayUpsideDown action for the owning device.
     * Must be implemented iff EnableActionDisplayUpsideDown was called.
     */
    virtual void DisplayUpsideDown(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaUpsideDown);
    /**
     * SetDisplayUpsideDown action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDisplayUpsideDown action for the owning device.
     * Must be implemented iff EnableActionSetDisplayUpsideDown was called.
     */
    virtual void SetDisplayUpsideDown(IInvocationResponse& aResponse, TUint aVersion, TBool aaUpsideDown);
    /**
     * SetDisplayScrollText action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDisplayScrollText action for the owning device.
     * Must be implemented iff EnableActionSetDisplayScrollText was called.
     */
    virtual void SetDisplayScrollText(IInvocationResponse& aResponse, TUint aVersion, TBool aaDisplayScrollText);
    /**
     * DisplayScrollText action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayScrollText action for the owning device.
     * Must be implemented iff EnableActionDisplayScrollText was called.
     */
    virtual void DisplayScrollText(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaDisplayScrollTextEnabled);
    /**
     * SetDisplaySleep action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDisplaySleep action for the owning device.
     * Must be implemented iff EnableActionSetDisplaySleep was called.
     */
    virtual void SetDisplaySleep(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled);
    /**
     * DisplaySleep action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplaySleep action for the owning device.
     * Must be implemented iff EnableActionDisplaySleep was called.
     */
    virtual void DisplaySleep(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled);
    /**
     * SetDisplayLedOff action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDisplayLedOff action for the owning device.
     * Must be implemented iff EnableActionSetDisplayLedOff was called.
     */
    virtual void SetDisplayLedOff(IInvocationResponse& aResponse, TUint aVersion, TBool aaOff);
    /**
     * DisplayLedOff action.
     *
     * Will be called when the device stack receives an invocation of the
     * DisplayLedOff action for the owning device.
     * Must be implemented iff EnableActionDisplayLedOff was called.
     */
    virtual void DisplayLedOff(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaOff);
private:
    DvProviderLinnCoUkUi2();
    void DoDisplayTestPattern(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplayFill(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplayClear(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetTestModeEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoSimulateInfraredInput(IDviInvocation& aInvocation, TUint aVersion);
    void DoSimulateButtonInput(IDviInvocation& aInvocation, TUint aVersion);
    void DoSimulateLightSensor(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetLightSensorData(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayBrightness(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayBrightnessAuto(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetInfraredCommands(IDviInvocation& aInvocation, TUint aVersion);
    void DoInfraredCommands(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetInfraredTerminalCommands(IDviInvocation& aInvocation, TUint aVersion);
    void DoInfraredTerminalCommands(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplayBrightness(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplayBrightnessAuto(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplayUpsideDown(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayUpsideDown(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayScrollText(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplayScrollText(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDisplaySleep(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplaySleep(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDisplayLedOff(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisplayLedOff(IDviInvocation& aInvocation, TUint aVersion);
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

