using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkUi2 : IDisposable
    {

        /// <summary>
        /// Set the value of the DisplayBrightness property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDisplayBrightness(uint aValue);

        /// <summary>
        /// Get a copy of the value of the DisplayBrightness property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyDisplayBrightness();

        /// <summary>
        /// Set the value of the DisplayBrightnessAuto property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDisplayBrightnessAuto(bool aValue);

        /// <summary>
        /// Get a copy of the value of the DisplayBrightnessAuto property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyDisplayBrightnessAuto();

        /// <summary>
        /// Set the value of the InfraredCommands property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyInfraredCommands(string aValue);

        /// <summary>
        /// Get a copy of the value of the InfraredCommands property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyInfraredCommands();

        /// <summary>
        /// Set the value of the InfraredTerminalCommands property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyInfraredTerminalCommands(string aValue);

        /// <summary>
        /// Get a copy of the value of the InfraredTerminalCommands property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyInfraredTerminalCommands();

        /// <summary>
        /// Set the value of the DisplayUpsideDown property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDisplayUpsideDown(bool aValue);

        /// <summary>
        /// Get a copy of the value of the DisplayUpsideDown property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyDisplayUpsideDown();

        /// <summary>
        /// Set the value of the DisplayScrollText property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDisplayScrollText(bool aValue);

        /// <summary>
        /// Get a copy of the value of the DisplayScrollText property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyDisplayScrollText();

        /// <summary>
        /// Set the value of the DisplaySleep property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDisplaySleep(bool aValue);

        /// <summary>
        /// Get a copy of the value of the DisplaySleep property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyDisplaySleep();

        /// <summary>
        /// Set the value of the DisplayLedOff property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDisplayLedOff(bool aValue);

        /// <summary>
        /// Get a copy of the value of the DisplayLedOff property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyDisplayLedOff();

        /// <summary>
        /// Set the value of the TerminalInputCode property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTerminalInputCode(uint aValue);

        /// <summary>
        /// Get a copy of the value of the TerminalInputCode property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyTerminalInputCode();

        /// <summary>
        /// Set the value of the TerminalInputName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTerminalInputName(string aValue);

        /// <summary>
        /// Get a copy of the value of the TerminalInputName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyTerminalInputName();

        /// <summary>
        /// Set the value of the DisplayPixels property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDisplayPixels(string aValue);

        /// <summary>
        /// Get a copy of the value of the DisplayPixels property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyDisplayPixels();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Ui:2 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkUi2 : DvProvider, IDisposable, IDvProviderLinnCoUkUi2
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateDisplayTestPattern;
        private ActionDelegate iDelegateDisplayFill;
        private ActionDelegate iDelegateDisplayClear;
        private ActionDelegate iDelegateSetTestModeEnabled;
        private ActionDelegate iDelegateSimulateInfraredInput;
        private ActionDelegate iDelegateSimulateButtonInput;
        private ActionDelegate iDelegateSimulateLightSensor;
        private ActionDelegate iDelegateGetLightSensorData;
        private ActionDelegate iDelegateSetDisplayBrightness;
        private ActionDelegate iDelegateSetDisplayBrightnessAuto;
        private ActionDelegate iDelegateSetInfraredCommands;
        private ActionDelegate iDelegateInfraredCommands;
        private ActionDelegate iDelegateSetInfraredTerminalCommands;
        private ActionDelegate iDelegateInfraredTerminalCommands;
        private ActionDelegate iDelegateDisplayBrightness;
        private ActionDelegate iDelegateDisplayBrightnessAuto;
        private ActionDelegate iDelegateDisplayUpsideDown;
        private ActionDelegate iDelegateSetDisplayUpsideDown;
        private ActionDelegate iDelegateSetDisplayScrollText;
        private ActionDelegate iDelegateDisplayScrollText;
        private ActionDelegate iDelegateSetDisplaySleep;
        private ActionDelegate iDelegateDisplaySleep;
        private ActionDelegate iDelegateSetDisplayLedOff;
        private ActionDelegate iDelegateDisplayLedOff;
        private PropertyUint iPropertyDisplayBrightness;
        private PropertyBool iPropertyDisplayBrightnessAuto;
        private PropertyString iPropertyInfraredCommands;
        private PropertyString iPropertyInfraredTerminalCommands;
        private PropertyBool iPropertyDisplayUpsideDown;
        private PropertyBool iPropertyDisplayScrollText;
        private PropertyBool iPropertyDisplaySleep;
        private PropertyBool iPropertyDisplayLedOff;
        private PropertyUint iPropertyTerminalInputCode;
        private PropertyString iPropertyTerminalInputName;
        private PropertyBinary iPropertyDisplayPixels;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkUi2(DvDevice aDevice)
            : base(aDevice, "linn-co-uk", "Ui", 2)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyDisplayBrightness = new PropertyUint(new ParameterUint("DisplayBrightness"));
            AddProperty(iPropertyDisplayBrightness);
            iPropertyDisplayBrightnessAuto = new PropertyBool(new ParameterBool("DisplayBrightnessAuto"));
            AddProperty(iPropertyDisplayBrightnessAuto);
            allowedValues.Add("None");
            allowedValues.Add("All");
            allowedValues.Add("Cd");
            allowedValues.Add("Dvd");
            iPropertyInfraredCommands = new PropertyString(new ParameterString("InfraredCommands", allowedValues));
            AddProperty(iPropertyInfraredCommands);
            allowedValues.Clear();
            allowedValues.Add("None");
            allowedValues.Add("All");
            allowedValues.Add("Cd");
            allowedValues.Add("Dvd");
            iPropertyInfraredTerminalCommands = new PropertyString(new ParameterString("InfraredTerminalCommands", allowedValues));
            AddProperty(iPropertyInfraredTerminalCommands);
            allowedValues.Clear();
            iPropertyDisplayUpsideDown = new PropertyBool(new ParameterBool("DisplayUpsideDown"));
            AddProperty(iPropertyDisplayUpsideDown);
            iPropertyDisplayScrollText = new PropertyBool(new ParameterBool("DisplayScrollText"));
            AddProperty(iPropertyDisplayScrollText);
            iPropertyDisplaySleep = new PropertyBool(new ParameterBool("DisplaySleep"));
            AddProperty(iPropertyDisplaySleep);
            iPropertyDisplayLedOff = new PropertyBool(new ParameterBool("DisplayLedOff"));
            AddProperty(iPropertyDisplayLedOff);
            iPropertyTerminalInputCode = new PropertyUint(new ParameterUint("TerminalInputCode"));
            AddProperty(iPropertyTerminalInputCode);
            iPropertyTerminalInputName = new PropertyString(new ParameterString("TerminalInputName", allowedValues));
            AddProperty(iPropertyTerminalInputName);
            iPropertyDisplayPixels = new PropertyBinary(new ParameterBinary("DisplayPixels"));
            AddProperty(iPropertyDisplayPixels);
        }

        /// <summary>
        /// Set the value of the DisplayBrightness property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDisplayBrightness(uint aValue)
        {
            return SetPropertyUint(iPropertyDisplayBrightness, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the DisplayBrightness property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyDisplayBrightness()
        {
            return iPropertyDisplayBrightness.Value();
        }

        /// <summary>
        /// Set the value of the DisplayBrightnessAuto property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDisplayBrightnessAuto(bool aValue)
        {
            return SetPropertyBool(iPropertyDisplayBrightnessAuto, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the DisplayBrightnessAuto property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyDisplayBrightnessAuto()
        {
            return iPropertyDisplayBrightnessAuto.Value();
        }

        /// <summary>
        /// Set the value of the InfraredCommands property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyInfraredCommands(string aValue)
        {
            return SetPropertyString(iPropertyInfraredCommands, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the InfraredCommands property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyInfraredCommands()
        {
            return iPropertyInfraredCommands.Value();
        }

        /// <summary>
        /// Set the value of the InfraredTerminalCommands property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyInfraredTerminalCommands(string aValue)
        {
            return SetPropertyString(iPropertyInfraredTerminalCommands, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the InfraredTerminalCommands property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyInfraredTerminalCommands()
        {
            return iPropertyInfraredTerminalCommands.Value();
        }

        /// <summary>
        /// Set the value of the DisplayUpsideDown property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDisplayUpsideDown(bool aValue)
        {
            return SetPropertyBool(iPropertyDisplayUpsideDown, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the DisplayUpsideDown property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyDisplayUpsideDown()
        {
            return iPropertyDisplayUpsideDown.Value();
        }

        /// <summary>
        /// Set the value of the DisplayScrollText property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDisplayScrollText(bool aValue)
        {
            return SetPropertyBool(iPropertyDisplayScrollText, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the DisplayScrollText property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyDisplayScrollText()
        {
            return iPropertyDisplayScrollText.Value();
        }

        /// <summary>
        /// Set the value of the DisplaySleep property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDisplaySleep(bool aValue)
        {
            return SetPropertyBool(iPropertyDisplaySleep, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the DisplaySleep property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyDisplaySleep()
        {
            return iPropertyDisplaySleep.Value();
        }

        /// <summary>
        /// Set the value of the DisplayLedOff property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDisplayLedOff(bool aValue)
        {
            return SetPropertyBool(iPropertyDisplayLedOff, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the DisplayLedOff property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyDisplayLedOff()
        {
            return iPropertyDisplayLedOff.Value();
        }

        /// <summary>
        /// Set the value of the TerminalInputCode property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTerminalInputCode(uint aValue)
        {
            return SetPropertyUint(iPropertyTerminalInputCode, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TerminalInputCode property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyTerminalInputCode()
        {
            return iPropertyTerminalInputCode.Value();
        }

        /// <summary>
        /// Set the value of the TerminalInputName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTerminalInputName(string aValue)
        {
            return SetPropertyString(iPropertyTerminalInputName, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TerminalInputName property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyTerminalInputName()
        {
            return iPropertyTerminalInputName.Value();
        }

        /// <summary>
        /// Set the value of the DisplayPixels property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDisplayPixels(string aValue)
        {
            return SetPropertyBinary(iPropertyDisplayPixels, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the DisplayPixels property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyDisplayPixels()
        {
            return iPropertyDisplayPixels.Value();
        }

        /// <summary>
        /// Signal that the action DisplayTestPattern is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DisplayTestPattern must be overridden if this is called.</remarks>
        protected void EnableActionDisplayTestPattern()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DisplayTestPattern");
            action.AddInputParameter(new ParameterInt("aTestPattern", 0, 6));
            iDelegateDisplayTestPattern = new ActionDelegate(DoDisplayTestPattern);
            EnableAction(action, iDelegateDisplayTestPattern, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DisplayFill is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DisplayFill must be overridden if this is called.</remarks>
        protected void EnableActionDisplayFill()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DisplayFill");
            iDelegateDisplayFill = new ActionDelegate(DoDisplayFill);
            EnableAction(action, iDelegateDisplayFill, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DisplayClear is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DisplayClear must be overridden if this is called.</remarks>
        protected void EnableActionDisplayClear()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DisplayClear");
            iDelegateDisplayClear = new ActionDelegate(DoDisplayClear);
            EnableAction(action, iDelegateDisplayClear, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetTestModeEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetTestModeEnabled must be overridden if this is called.</remarks>
        protected void EnableActionSetTestModeEnabled()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetTestModeEnabled");
            action.AddInputParameter(new ParameterBool("aEnabled"));
            iDelegateSetTestModeEnabled = new ActionDelegate(DoSetTestModeEnabled);
            EnableAction(action, iDelegateSetTestModeEnabled, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SimulateInfraredInput is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SimulateInfraredInput must be overridden if this is called.</remarks>
        protected void EnableActionSimulateInfraredInput()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SimulateInfraredInput");
            action.AddInputParameter(new ParameterRelated("aCode", iPropertyTerminalInputCode));
            iDelegateSimulateInfraredInput = new ActionDelegate(DoSimulateInfraredInput);
            EnableAction(action, iDelegateSimulateInfraredInput, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SimulateButtonInput is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SimulateButtonInput must be overridden if this is called.</remarks>
        protected void EnableActionSimulateButtonInput()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SimulateButtonInput");
            action.AddInputParameter(new ParameterRelated("aCode", iPropertyTerminalInputCode));
            iDelegateSimulateButtonInput = new ActionDelegate(DoSimulateButtonInput);
            EnableAction(action, iDelegateSimulateButtonInput, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SimulateLightSensor is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SimulateLightSensor must be overridden if this is called.</remarks>
        protected void EnableActionSimulateLightSensor()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SimulateLightSensor");
            action.AddInputParameter(new ParameterUint("aLightLevel"));
            iDelegateSimulateLightSensor = new ActionDelegate(DoSimulateLightSensor);
            EnableAction(action, iDelegateSimulateLightSensor, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetLightSensorData is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetLightSensorData must be overridden if this is called.</remarks>
        protected void EnableActionGetLightSensorData()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetLightSensorData");
            action.AddOutputParameter(new ParameterUint("aLightLevel"));
            iDelegateGetLightSensorData = new ActionDelegate(DoGetLightSensorData);
            EnableAction(action, iDelegateGetLightSensorData, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetDisplayBrightness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetDisplayBrightness must be overridden if this is called.</remarks>
        protected void EnableActionSetDisplayBrightness()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetDisplayBrightness");
            action.AddInputParameter(new ParameterRelated("aBrightness", iPropertyDisplayBrightness));
            iDelegateSetDisplayBrightness = new ActionDelegate(DoSetDisplayBrightness);
            EnableAction(action, iDelegateSetDisplayBrightness, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetDisplayBrightnessAuto is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetDisplayBrightnessAuto must be overridden if this is called.</remarks>
        protected void EnableActionSetDisplayBrightnessAuto()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetDisplayBrightnessAuto");
            action.AddInputParameter(new ParameterRelated("aBrightnessAuto", iPropertyDisplayBrightnessAuto));
            iDelegateSetDisplayBrightnessAuto = new ActionDelegate(DoSetDisplayBrightnessAuto);
            EnableAction(action, iDelegateSetDisplayBrightnessAuto, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetInfraredCommands is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetInfraredCommands must be overridden if this is called.</remarks>
        protected void EnableActionSetInfraredCommands()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetInfraredCommands");
            action.AddInputParameter(new ParameterRelated("aCommands", iPropertyInfraredCommands));
            iDelegateSetInfraredCommands = new ActionDelegate(DoSetInfraredCommands);
            EnableAction(action, iDelegateSetInfraredCommands, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action InfraredCommands is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// InfraredCommands must be overridden if this is called.</remarks>
        protected void EnableActionInfraredCommands()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("InfraredCommands");
            action.AddOutputParameter(new ParameterRelated("aCommands", iPropertyInfraredCommands));
            iDelegateInfraredCommands = new ActionDelegate(DoInfraredCommands);
            EnableAction(action, iDelegateInfraredCommands, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetInfraredTerminalCommands is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetInfraredTerminalCommands must be overridden if this is called.</remarks>
        protected void EnableActionSetInfraredTerminalCommands()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetInfraredTerminalCommands");
            action.AddInputParameter(new ParameterRelated("aCommands", iPropertyInfraredTerminalCommands));
            iDelegateSetInfraredTerminalCommands = new ActionDelegate(DoSetInfraredTerminalCommands);
            EnableAction(action, iDelegateSetInfraredTerminalCommands, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action InfraredTerminalCommands is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// InfraredTerminalCommands must be overridden if this is called.</remarks>
        protected void EnableActionInfraredTerminalCommands()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("InfraredTerminalCommands");
            action.AddOutputParameter(new ParameterRelated("aCommands", iPropertyInfraredTerminalCommands));
            iDelegateInfraredTerminalCommands = new ActionDelegate(DoInfraredTerminalCommands);
            EnableAction(action, iDelegateInfraredTerminalCommands, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DisplayBrightness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DisplayBrightness must be overridden if this is called.</remarks>
        protected void EnableActionDisplayBrightness()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DisplayBrightness");
            action.AddOutputParameter(new ParameterRelated("aBrightness", iPropertyDisplayBrightness));
            iDelegateDisplayBrightness = new ActionDelegate(DoDisplayBrightness);
            EnableAction(action, iDelegateDisplayBrightness, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DisplayBrightnessAuto is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DisplayBrightnessAuto must be overridden if this is called.</remarks>
        protected void EnableActionDisplayBrightnessAuto()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DisplayBrightnessAuto");
            action.AddOutputParameter(new ParameterRelated("aBrightnessAuto", iPropertyDisplayBrightnessAuto));
            iDelegateDisplayBrightnessAuto = new ActionDelegate(DoDisplayBrightnessAuto);
            EnableAction(action, iDelegateDisplayBrightnessAuto, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DisplayUpsideDown is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DisplayUpsideDown must be overridden if this is called.</remarks>
        protected void EnableActionDisplayUpsideDown()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DisplayUpsideDown");
            action.AddOutputParameter(new ParameterRelated("aUpsideDown", iPropertyDisplayUpsideDown));
            iDelegateDisplayUpsideDown = new ActionDelegate(DoDisplayUpsideDown);
            EnableAction(action, iDelegateDisplayUpsideDown, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetDisplayUpsideDown is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetDisplayUpsideDown must be overridden if this is called.</remarks>
        protected void EnableActionSetDisplayUpsideDown()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetDisplayUpsideDown");
            action.AddInputParameter(new ParameterRelated("aUpsideDown", iPropertyDisplayUpsideDown));
            iDelegateSetDisplayUpsideDown = new ActionDelegate(DoSetDisplayUpsideDown);
            EnableAction(action, iDelegateSetDisplayUpsideDown, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetDisplayScrollText is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetDisplayScrollText must be overridden if this is called.</remarks>
        protected void EnableActionSetDisplayScrollText()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetDisplayScrollText");
            action.AddInputParameter(new ParameterRelated("aDisplayScrollText", iPropertyDisplayScrollText));
            iDelegateSetDisplayScrollText = new ActionDelegate(DoSetDisplayScrollText);
            EnableAction(action, iDelegateSetDisplayScrollText, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DisplayScrollText is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DisplayScrollText must be overridden if this is called.</remarks>
        protected void EnableActionDisplayScrollText()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DisplayScrollText");
            action.AddOutputParameter(new ParameterRelated("aDisplayScrollTextEnabled", iPropertyDisplayScrollText));
            iDelegateDisplayScrollText = new ActionDelegate(DoDisplayScrollText);
            EnableAction(action, iDelegateDisplayScrollText, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetDisplaySleep is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetDisplaySleep must be overridden if this is called.</remarks>
        protected void EnableActionSetDisplaySleep()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetDisplaySleep");
            action.AddInputParameter(new ParameterRelated("aEnabled", iPropertyDisplaySleep));
            iDelegateSetDisplaySleep = new ActionDelegate(DoSetDisplaySleep);
            EnableAction(action, iDelegateSetDisplaySleep, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DisplaySleep is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DisplaySleep must be overridden if this is called.</remarks>
        protected void EnableActionDisplaySleep()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DisplaySleep");
            action.AddOutputParameter(new ParameterRelated("aEnabled", iPropertyDisplaySleep));
            iDelegateDisplaySleep = new ActionDelegate(DoDisplaySleep);
            EnableAction(action, iDelegateDisplaySleep, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetDisplayLedOff is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetDisplayLedOff must be overridden if this is called.</remarks>
        protected void EnableActionSetDisplayLedOff()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetDisplayLedOff");
            action.AddInputParameter(new ParameterRelated("aOff", iPropertyDisplayLedOff));
            iDelegateSetDisplayLedOff = new ActionDelegate(DoSetDisplayLedOff);
            EnableAction(action, iDelegateSetDisplayLedOff, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DisplayLedOff is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DisplayLedOff must be overridden if this is called.</remarks>
        protected void EnableActionDisplayLedOff()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DisplayLedOff");
            action.AddOutputParameter(new ParameterRelated("aOff", iPropertyDisplayLedOff));
            iDelegateDisplayLedOff = new ActionDelegate(DoDisplayLedOff);
            EnableAction(action, iDelegateDisplayLedOff, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// DisplayTestPattern action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayTestPattern action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayTestPattern was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTestPattern"></param>
        protected virtual void DisplayTestPattern(uint aVersion, int aaTestPattern)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplayFill action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayFill action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayFill was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void DisplayFill(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplayClear action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayClear action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayClear was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void DisplayClear(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetTestModeEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetTestModeEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetTestModeEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaEnabled"></param>
        protected virtual void SetTestModeEnabled(uint aVersion, bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SimulateInfraredInput action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SimulateInfraredInput action for the owning device.
        ///
        /// Must be implemented iff EnableActionSimulateInfraredInput was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCode"></param>
        protected virtual void SimulateInfraredInput(uint aVersion, uint aaCode)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SimulateButtonInput action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SimulateButtonInput action for the owning device.
        ///
        /// Must be implemented iff EnableActionSimulateButtonInput was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCode"></param>
        protected virtual void SimulateButtonInput(uint aVersion, uint aaCode)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SimulateLightSensor action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SimulateLightSensor action for the owning device.
        ///
        /// Must be implemented iff EnableActionSimulateLightSensor was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaLightLevel"></param>
        protected virtual void SimulateLightSensor(uint aVersion, uint aaLightLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetLightSensorData action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetLightSensorData action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetLightSensorData was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaLightLevel"></param>
        protected virtual void GetLightSensorData(uint aVersion, out uint aaLightLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDisplayBrightness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDisplayBrightness action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDisplayBrightness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaBrightness"></param>
        protected virtual void SetDisplayBrightness(uint aVersion, uint aaBrightness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDisplayBrightnessAuto action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDisplayBrightnessAuto action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDisplayBrightnessAuto was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaBrightnessAuto"></param>
        protected virtual void SetDisplayBrightnessAuto(uint aVersion, bool aaBrightnessAuto)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetInfraredCommands action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetInfraredCommands action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetInfraredCommands was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCommands"></param>
        protected virtual void SetInfraredCommands(uint aVersion, string aaCommands)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// InfraredCommands action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// InfraredCommands action for the owning device.
        ///
        /// Must be implemented iff EnableActionInfraredCommands was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCommands"></param>
        protected virtual void InfraredCommands(uint aVersion, out string aaCommands)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetInfraredTerminalCommands action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetInfraredTerminalCommands action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetInfraredTerminalCommands was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCommands"></param>
        protected virtual void SetInfraredTerminalCommands(uint aVersion, string aaCommands)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// InfraredTerminalCommands action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// InfraredTerminalCommands action for the owning device.
        ///
        /// Must be implemented iff EnableActionInfraredTerminalCommands was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCommands"></param>
        protected virtual void InfraredTerminalCommands(uint aVersion, out string aaCommands)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplayBrightness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayBrightness action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayBrightness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaBrightness"></param>
        protected virtual void DisplayBrightness(uint aVersion, out uint aaBrightness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplayBrightnessAuto action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayBrightnessAuto action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayBrightnessAuto was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaBrightnessAuto"></param>
        protected virtual void DisplayBrightnessAuto(uint aVersion, out bool aaBrightnessAuto)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplayUpsideDown action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayUpsideDown action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayUpsideDown was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUpsideDown"></param>
        protected virtual void DisplayUpsideDown(uint aVersion, out bool aaUpsideDown)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDisplayUpsideDown action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDisplayUpsideDown action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDisplayUpsideDown was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUpsideDown"></param>
        protected virtual void SetDisplayUpsideDown(uint aVersion, bool aaUpsideDown)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDisplayScrollText action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDisplayScrollText action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDisplayScrollText was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaDisplayScrollText"></param>
        protected virtual void SetDisplayScrollText(uint aVersion, bool aaDisplayScrollText)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplayScrollText action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayScrollText action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayScrollText was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaDisplayScrollTextEnabled"></param>
        protected virtual void DisplayScrollText(uint aVersion, out bool aaDisplayScrollTextEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDisplaySleep action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDisplaySleep action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDisplaySleep was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaEnabled"></param>
        protected virtual void SetDisplaySleep(uint aVersion, bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplaySleep action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplaySleep action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplaySleep was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaEnabled"></param>
        protected virtual void DisplaySleep(uint aVersion, out bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDisplayLedOff action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDisplayLedOff action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDisplayLedOff was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaOff"></param>
        protected virtual void SetDisplayLedOff(uint aVersion, bool aaOff)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplayLedOff action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayLedOff action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayLedOff was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaOff"></param>
        protected virtual void DisplayLedOff(uint aVersion, out bool aaOff)
        {
            throw (new ActionDisabledError());
        }

        private static int DoDisplayTestPattern(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int aTestPattern;
            try
            {
                invocation.ReadStart();
                aTestPattern = invocation.ReadInt("aTestPattern");
                invocation.ReadEnd();
                self.DisplayTestPattern(aVersion, aTestPattern);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoDisplayFill(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.DisplayFill(aVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoDisplayClear(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.DisplayClear(aVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetTestModeEnabled(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aEnabled;
            try
            {
                invocation.ReadStart();
                aEnabled = invocation.ReadBool("aEnabled");
                invocation.ReadEnd();
                self.SetTestModeEnabled(aVersion, aEnabled);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSimulateInfraredInput(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aCode;
            try
            {
                invocation.ReadStart();
                aCode = invocation.ReadUint("aCode");
                invocation.ReadEnd();
                self.SimulateInfraredInput(aVersion, aCode);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSimulateButtonInput(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aCode;
            try
            {
                invocation.ReadStart();
                aCode = invocation.ReadUint("aCode");
                invocation.ReadEnd();
                self.SimulateButtonInput(aVersion, aCode);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSimulateLightSensor(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aLightLevel;
            try
            {
                invocation.ReadStart();
                aLightLevel = invocation.ReadUint("aLightLevel");
                invocation.ReadEnd();
                self.SimulateLightSensor(aVersion, aLightLevel);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetLightSensorData(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aLightLevel;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetLightSensorData(aVersion, out aLightLevel);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("aLightLevel", aLightLevel);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetDisplayBrightness(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aBrightness;
            try
            {
                invocation.ReadStart();
                aBrightness = invocation.ReadUint("aBrightness");
                invocation.ReadEnd();
                self.SetDisplayBrightness(aVersion, aBrightness);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetDisplayBrightnessAuto(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aBrightnessAuto;
            try
            {
                invocation.ReadStart();
                aBrightnessAuto = invocation.ReadBool("aBrightnessAuto");
                invocation.ReadEnd();
                self.SetDisplayBrightnessAuto(aVersion, aBrightnessAuto);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetInfraredCommands(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aCommands;
            try
            {
                invocation.ReadStart();
                aCommands = invocation.ReadString("aCommands");
                invocation.ReadEnd();
                self.SetInfraredCommands(aVersion, aCommands);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoInfraredCommands(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aCommands;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.InfraredCommands(aVersion, out aCommands);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aCommands", aCommands);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetInfraredTerminalCommands(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aCommands;
            try
            {
                invocation.ReadStart();
                aCommands = invocation.ReadString("aCommands");
                invocation.ReadEnd();
                self.SetInfraredTerminalCommands(aVersion, aCommands);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoInfraredTerminalCommands(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aCommands;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.InfraredTerminalCommands(aVersion, out aCommands);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aCommands", aCommands);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoDisplayBrightness(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aBrightness;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.DisplayBrightness(aVersion, out aBrightness);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("aBrightness", aBrightness);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoDisplayBrightnessAuto(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aBrightnessAuto;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.DisplayBrightnessAuto(aVersion, out aBrightnessAuto);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("aBrightnessAuto", aBrightnessAuto);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoDisplayUpsideDown(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aUpsideDown;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.DisplayUpsideDown(aVersion, out aUpsideDown);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("aUpsideDown", aUpsideDown);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetDisplayUpsideDown(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aUpsideDown;
            try
            {
                invocation.ReadStart();
                aUpsideDown = invocation.ReadBool("aUpsideDown");
                invocation.ReadEnd();
                self.SetDisplayUpsideDown(aVersion, aUpsideDown);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetDisplayScrollText(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aDisplayScrollText;
            try
            {
                invocation.ReadStart();
                aDisplayScrollText = invocation.ReadBool("aDisplayScrollText");
                invocation.ReadEnd();
                self.SetDisplayScrollText(aVersion, aDisplayScrollText);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoDisplayScrollText(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aDisplayScrollTextEnabled;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.DisplayScrollText(aVersion, out aDisplayScrollTextEnabled);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("aDisplayScrollTextEnabled", aDisplayScrollTextEnabled);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetDisplaySleep(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aEnabled;
            try
            {
                invocation.ReadStart();
                aEnabled = invocation.ReadBool("aEnabled");
                invocation.ReadEnd();
                self.SetDisplaySleep(aVersion, aEnabled);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoDisplaySleep(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aEnabled;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.DisplaySleep(aVersion, out aEnabled);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("aEnabled", aEnabled);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetDisplayLedOff(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aOff;
            try
            {
                invocation.ReadStart();
                aOff = invocation.ReadBool("aOff");
                invocation.ReadEnd();
                self.SetDisplayLedOff(aVersion, aOff);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoDisplayLedOff(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aOff;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.DisplayLedOff(aVersion, out aOff);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("aOff", aOff);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderLinnCoUkUi2()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                DisposeProvider();
                iHandle = IntPtr.Zero;
            }
            iGch.Free();
        }
    }
}

