using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderUpnpOrgRenderingControl1 : IDisposable
    {

        /// <summary>
        /// Set the value of the LastChange property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyLastChange(string aValue);

        /// <summary>
        /// Get a copy of the value of the LastChange property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyLastChange();
        
    }
    /// <summary>
    /// Provider for the upnp.org:RenderingControl:1 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgRenderingControl1 : DvProvider, IDisposable, IDvProviderUpnpOrgRenderingControl1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateListPresets;
        private ActionDelegate iDelegateSelectPreset;
        private ActionDelegate iDelegateGetBrightness;
        private ActionDelegate iDelegateSetBrightness;
        private ActionDelegate iDelegateGetContrast;
        private ActionDelegate iDelegateSetContrast;
        private ActionDelegate iDelegateGetSharpness;
        private ActionDelegate iDelegateSetSharpness;
        private ActionDelegate iDelegateGetRedVideoGain;
        private ActionDelegate iDelegateSetRedVideoGain;
        private ActionDelegate iDelegateGetGreenVideoGain;
        private ActionDelegate iDelegateSetGreenVideoGain;
        private ActionDelegate iDelegateGetBlueVideoGain;
        private ActionDelegate iDelegateSetBlueVideoGain;
        private ActionDelegate iDelegateGetRedVideoBlackLevel;
        private ActionDelegate iDelegateSetRedVideoBlackLevel;
        private ActionDelegate iDelegateGetGreenVideoBlackLevel;
        private ActionDelegate iDelegateSetGreenVideoBlackLevel;
        private ActionDelegate iDelegateGetBlueVideoBlackLevel;
        private ActionDelegate iDelegateSetBlueVideoBlackLevel;
        private ActionDelegate iDelegateGetColorTemperature;
        private ActionDelegate iDelegateSetColorTemperature;
        private ActionDelegate iDelegateGetHorizontalKeystone;
        private ActionDelegate iDelegateSetHorizontalKeystone;
        private ActionDelegate iDelegateGetVerticalKeystone;
        private ActionDelegate iDelegateSetVerticalKeystone;
        private ActionDelegate iDelegateGetMute;
        private ActionDelegate iDelegateSetMute;
        private ActionDelegate iDelegateGetVolume;
        private ActionDelegate iDelegateSetVolume;
        private ActionDelegate iDelegateGetVolumeDB;
        private ActionDelegate iDelegateSetVolumeDB;
        private ActionDelegate iDelegateGetVolumeDBRange;
        private ActionDelegate iDelegateGetLoudness;
        private ActionDelegate iDelegateSetLoudness;
        private PropertyString iPropertyLastChange;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgRenderingControl1(DvDevice aDevice)
            : base(aDevice, "schemas-upnp-org", "RenderingControl", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyLastChange = new PropertyString(new ParameterString("LastChange", allowedValues));
            AddProperty(iPropertyLastChange);
        }

        /// <summary>
        /// Set the value of the LastChange property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyLastChange(string aValue)
        {
            return SetPropertyString(iPropertyLastChange, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the LastChange property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyLastChange()
        {
            return iPropertyLastChange.Value();
        }

        /// <summary>
        /// Signal that the action ListPresets is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoListPresets must be overridden if this is called.</remarks>
        protected unsafe void EnableActionListPresets()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("ListPresets");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterString("CurrentPresetNameList", allowedValues));
            iDelegateListPresets = new ActionDelegate(DoListPresets);
            EnableAction(action, iDelegateListPresets, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SelectPreset is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSelectPreset must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSelectPreset()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SelectPreset");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("FactoryDefaults");
            action.AddInputParameter(new ParameterString("PresetName", allowedValues));
            allowedValues.Clear();
            iDelegateSelectPreset = new ActionDelegate(DoSelectPreset);
            EnableAction(action, iDelegateSelectPreset, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetBrightness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetBrightness must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetBrightness()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetBrightness");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterUint("CurrentBrightness", 0, 0, 1));
            iDelegateGetBrightness = new ActionDelegate(DoGetBrightness);
            EnableAction(action, iDelegateGetBrightness, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetBrightness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetBrightness must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetBrightness()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetBrightness");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterUint("DesiredBrightness", 0, 0, 1));
            iDelegateSetBrightness = new ActionDelegate(DoSetBrightness);
            EnableAction(action, iDelegateSetBrightness, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetContrast is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetContrast must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetContrast()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetContrast");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterUint("CurrentContrast", 0, 0, 1));
            iDelegateGetContrast = new ActionDelegate(DoGetContrast);
            EnableAction(action, iDelegateGetContrast, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetContrast is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetContrast must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetContrast()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetContrast");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterUint("DesiredContrast", 0, 0, 1));
            iDelegateSetContrast = new ActionDelegate(DoSetContrast);
            EnableAction(action, iDelegateSetContrast, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetSharpness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetSharpness must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetSharpness()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetSharpness");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterUint("CurrentSharpness", 0, 0, 1));
            iDelegateGetSharpness = new ActionDelegate(DoGetSharpness);
            EnableAction(action, iDelegateGetSharpness, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetSharpness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetSharpness must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetSharpness()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetSharpness");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterUint("DesiredSharpness", 0, 0, 1));
            iDelegateSetSharpness = new ActionDelegate(DoSetSharpness);
            EnableAction(action, iDelegateSetSharpness, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetRedVideoGain is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRedVideoGain must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRedVideoGain()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetRedVideoGain");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterUint("CurrentRedVideoGain"));
            iDelegateGetRedVideoGain = new ActionDelegate(DoGetRedVideoGain);
            EnableAction(action, iDelegateGetRedVideoGain, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetRedVideoGain is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetRedVideoGain must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetRedVideoGain()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetRedVideoGain");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterUint("DesiredRedVideoGain"));
            iDelegateSetRedVideoGain = new ActionDelegate(DoSetRedVideoGain);
            EnableAction(action, iDelegateSetRedVideoGain, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetGreenVideoGain is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetGreenVideoGain must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetGreenVideoGain()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetGreenVideoGain");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterUint("CurrentGreenVideoGain", 0, 0, 1));
            iDelegateGetGreenVideoGain = new ActionDelegate(DoGetGreenVideoGain);
            EnableAction(action, iDelegateGetGreenVideoGain, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetGreenVideoGain is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetGreenVideoGain must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetGreenVideoGain()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetGreenVideoGain");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterUint("DesiredGreenVideoGain", 0, 0, 1));
            iDelegateSetGreenVideoGain = new ActionDelegate(DoSetGreenVideoGain);
            EnableAction(action, iDelegateSetGreenVideoGain, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetBlueVideoGain is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetBlueVideoGain must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetBlueVideoGain()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetBlueVideoGain");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterUint("CurrentBlueVideoGain", 0, 0, 1));
            iDelegateGetBlueVideoGain = new ActionDelegate(DoGetBlueVideoGain);
            EnableAction(action, iDelegateGetBlueVideoGain, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetBlueVideoGain is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetBlueVideoGain must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetBlueVideoGain()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetBlueVideoGain");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterUint("DesiredBlueVideoGain", 0, 0, 1));
            iDelegateSetBlueVideoGain = new ActionDelegate(DoSetBlueVideoGain);
            EnableAction(action, iDelegateSetBlueVideoGain, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetRedVideoBlackLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRedVideoBlackLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRedVideoBlackLevel()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetRedVideoBlackLevel");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterUint("CurrentRedVideoBlackLevel", 0, 0, 1));
            iDelegateGetRedVideoBlackLevel = new ActionDelegate(DoGetRedVideoBlackLevel);
            EnableAction(action, iDelegateGetRedVideoBlackLevel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetRedVideoBlackLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetRedVideoBlackLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetRedVideoBlackLevel()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetRedVideoBlackLevel");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterUint("DesiredRedVideoBlackLevel", 0, 0, 1));
            iDelegateSetRedVideoBlackLevel = new ActionDelegate(DoSetRedVideoBlackLevel);
            EnableAction(action, iDelegateSetRedVideoBlackLevel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetGreenVideoBlackLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetGreenVideoBlackLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetGreenVideoBlackLevel()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetGreenVideoBlackLevel");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterUint("CurrentGreenVideoBlackLevel", 0, 0, 1));
            iDelegateGetGreenVideoBlackLevel = new ActionDelegate(DoGetGreenVideoBlackLevel);
            EnableAction(action, iDelegateGetGreenVideoBlackLevel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetGreenVideoBlackLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetGreenVideoBlackLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetGreenVideoBlackLevel()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetGreenVideoBlackLevel");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterUint("DesiredGreenVideoBlackLevel", 0, 0, 1));
            iDelegateSetGreenVideoBlackLevel = new ActionDelegate(DoSetGreenVideoBlackLevel);
            EnableAction(action, iDelegateSetGreenVideoBlackLevel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetBlueVideoBlackLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetBlueVideoBlackLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetBlueVideoBlackLevel()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetBlueVideoBlackLevel");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterUint("CurrentBlueVideoBlackLevel", 0, 0, 1));
            iDelegateGetBlueVideoBlackLevel = new ActionDelegate(DoGetBlueVideoBlackLevel);
            EnableAction(action, iDelegateGetBlueVideoBlackLevel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetBlueVideoBlackLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetBlueVideoBlackLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetBlueVideoBlackLevel()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetBlueVideoBlackLevel");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterUint("DesiredBlueVideoBlackLevel", 0, 0, 1));
            iDelegateSetBlueVideoBlackLevel = new ActionDelegate(DoSetBlueVideoBlackLevel);
            EnableAction(action, iDelegateSetBlueVideoBlackLevel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetColorTemperature is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetColorTemperature must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetColorTemperature()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetColorTemperature");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterUint("CurrentColorTemperature", 0, 0, 1));
            iDelegateGetColorTemperature = new ActionDelegate(DoGetColorTemperature);
            EnableAction(action, iDelegateGetColorTemperature, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetColorTemperature is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetColorTemperature must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetColorTemperature()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetColorTemperature");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterUint("DesiredColorTemperature", 0, 0, 1));
            iDelegateSetColorTemperature = new ActionDelegate(DoSetColorTemperature);
            EnableAction(action, iDelegateSetColorTemperature, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetHorizontalKeystone is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetHorizontalKeystone must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetHorizontalKeystone()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetHorizontalKeystone");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterInt("CurrentHorizontalKeystone"));
            iDelegateGetHorizontalKeystone = new ActionDelegate(DoGetHorizontalKeystone);
            EnableAction(action, iDelegateGetHorizontalKeystone, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetHorizontalKeystone is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetHorizontalKeystone must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetHorizontalKeystone()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetHorizontalKeystone");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterInt("DesiredHorizontalKeystone"));
            iDelegateSetHorizontalKeystone = new ActionDelegate(DoSetHorizontalKeystone);
            EnableAction(action, iDelegateSetHorizontalKeystone, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetVerticalKeystone is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetVerticalKeystone must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetVerticalKeystone()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetVerticalKeystone");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddOutputParameter(new ParameterInt("CurrentVerticalKeystone"));
            iDelegateGetVerticalKeystone = new ActionDelegate(DoGetVerticalKeystone);
            EnableAction(action, iDelegateGetVerticalKeystone, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetVerticalKeystone is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetVerticalKeystone must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetVerticalKeystone()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetVerticalKeystone");
            action.AddInputParameter(new ParameterUint("InstanceID"));
            action.AddInputParameter(new ParameterInt("DesiredVerticalKeystone"));
            iDelegateSetVerticalKeystone = new ActionDelegate(DoSetVerticalKeystone);
            EnableAction(action, iDelegateSetVerticalKeystone, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetMute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetMute must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetMute()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetMute");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("Master");
            action.AddInputParameter(new ParameterString("Channel", allowedValues));
            allowedValues.Clear();
            action.AddOutputParameter(new ParameterBool("CurrentMute"));
            iDelegateGetMute = new ActionDelegate(DoGetMute);
            EnableAction(action, iDelegateGetMute, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetMute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetMute must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetMute()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetMute");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("Master");
            action.AddInputParameter(new ParameterString("Channel", allowedValues));
            allowedValues.Clear();
            action.AddInputParameter(new ParameterBool("DesiredMute"));
            iDelegateSetMute = new ActionDelegate(DoSetMute);
            EnableAction(action, iDelegateSetMute, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetVolume is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetVolume must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetVolume()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetVolume");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("Master");
            action.AddInputParameter(new ParameterString("Channel", allowedValues));
            allowedValues.Clear();
            action.AddOutputParameter(new ParameterUint("CurrentVolume", 0, 0, 1));
            iDelegateGetVolume = new ActionDelegate(DoGetVolume);
            EnableAction(action, iDelegateGetVolume, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetVolume is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetVolume must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetVolume()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetVolume");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("Master");
            action.AddInputParameter(new ParameterString("Channel", allowedValues));
            allowedValues.Clear();
            action.AddInputParameter(new ParameterUint("DesiredVolume", 0, 0, 1));
            iDelegateSetVolume = new ActionDelegate(DoSetVolume);
            EnableAction(action, iDelegateSetVolume, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetVolumeDB is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetVolumeDB must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetVolumeDB()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetVolumeDB");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("Master");
            action.AddInputParameter(new ParameterString("Channel", allowedValues));
            allowedValues.Clear();
            action.AddOutputParameter(new ParameterInt("CurrentVolume"));
            iDelegateGetVolumeDB = new ActionDelegate(DoGetVolumeDB);
            EnableAction(action, iDelegateGetVolumeDB, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetVolumeDB is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetVolumeDB must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetVolumeDB()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetVolumeDB");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("Master");
            action.AddInputParameter(new ParameterString("Channel", allowedValues));
            allowedValues.Clear();
            action.AddInputParameter(new ParameterInt("DesiredVolume"));
            iDelegateSetVolumeDB = new ActionDelegate(DoSetVolumeDB);
            EnableAction(action, iDelegateSetVolumeDB, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetVolumeDBRange is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetVolumeDBRange must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetVolumeDBRange()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetVolumeDBRange");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("Master");
            action.AddInputParameter(new ParameterString("Channel", allowedValues));
            allowedValues.Clear();
            action.AddOutputParameter(new ParameterInt("MinValue"));
            action.AddOutputParameter(new ParameterInt("MaxValue"));
            iDelegateGetVolumeDBRange = new ActionDelegate(DoGetVolumeDBRange);
            EnableAction(action, iDelegateGetVolumeDBRange, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetLoudness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetLoudness must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetLoudness()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetLoudness");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("Master");
            action.AddInputParameter(new ParameterString("Channel", allowedValues));
            allowedValues.Clear();
            action.AddOutputParameter(new ParameterBool("CurrentLoudness"));
            iDelegateGetLoudness = new ActionDelegate(DoGetLoudness);
            EnableAction(action, iDelegateGetLoudness, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetLoudness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetLoudness must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetLoudness()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetLoudness");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("InstanceID"));
            allowedValues.Add("Master");
            action.AddInputParameter(new ParameterString("Channel", allowedValues));
            allowedValues.Clear();
            action.AddInputParameter(new ParameterBool("DesiredLoudness"));
            iDelegateSetLoudness = new ActionDelegate(DoSetLoudness);
            EnableAction(action, iDelegateSetLoudness, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// ListPresets action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ListPresets action for the owning device.
        ///
        /// Must be implemented iff EnableActionListPresets was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentPresetNameList"></param>
        protected virtual void ListPresets(uint aVersion, uint aInstanceID, out string aCurrentPresetNameList)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SelectPreset action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SelectPreset action for the owning device.
        ///
        /// Must be implemented iff EnableActionSelectPreset was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aPresetName"></param>
        protected virtual void SelectPreset(uint aVersion, uint aInstanceID, string aPresetName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetBrightness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetBrightness action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetBrightness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentBrightness"></param>
        protected virtual void GetBrightness(uint aVersion, uint aInstanceID, out uint aCurrentBrightness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetBrightness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetBrightness action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetBrightness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredBrightness"></param>
        protected virtual void SetBrightness(uint aVersion, uint aInstanceID, uint aDesiredBrightness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetContrast action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetContrast action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetContrast was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentContrast"></param>
        protected virtual void GetContrast(uint aVersion, uint aInstanceID, out uint aCurrentContrast)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetContrast action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetContrast action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetContrast was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredContrast"></param>
        protected virtual void SetContrast(uint aVersion, uint aInstanceID, uint aDesiredContrast)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetSharpness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetSharpness action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetSharpness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentSharpness"></param>
        protected virtual void GetSharpness(uint aVersion, uint aInstanceID, out uint aCurrentSharpness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetSharpness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetSharpness action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetSharpness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredSharpness"></param>
        protected virtual void SetSharpness(uint aVersion, uint aInstanceID, uint aDesiredSharpness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetRedVideoGain action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetRedVideoGain action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetRedVideoGain was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentRedVideoGain"></param>
        protected virtual void GetRedVideoGain(uint aVersion, uint aInstanceID, out uint aCurrentRedVideoGain)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetRedVideoGain action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetRedVideoGain action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetRedVideoGain was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredRedVideoGain"></param>
        protected virtual void SetRedVideoGain(uint aVersion, uint aInstanceID, uint aDesiredRedVideoGain)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetGreenVideoGain action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetGreenVideoGain action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetGreenVideoGain was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentGreenVideoGain"></param>
        protected virtual void GetGreenVideoGain(uint aVersion, uint aInstanceID, out uint aCurrentGreenVideoGain)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetGreenVideoGain action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetGreenVideoGain action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetGreenVideoGain was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredGreenVideoGain"></param>
        protected virtual void SetGreenVideoGain(uint aVersion, uint aInstanceID, uint aDesiredGreenVideoGain)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetBlueVideoGain action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetBlueVideoGain action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetBlueVideoGain was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentBlueVideoGain"></param>
        protected virtual void GetBlueVideoGain(uint aVersion, uint aInstanceID, out uint aCurrentBlueVideoGain)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetBlueVideoGain action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetBlueVideoGain action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetBlueVideoGain was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredBlueVideoGain"></param>
        protected virtual void SetBlueVideoGain(uint aVersion, uint aInstanceID, uint aDesiredBlueVideoGain)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetRedVideoBlackLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetRedVideoBlackLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetRedVideoBlackLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentRedVideoBlackLevel"></param>
        protected virtual void GetRedVideoBlackLevel(uint aVersion, uint aInstanceID, out uint aCurrentRedVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetRedVideoBlackLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetRedVideoBlackLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetRedVideoBlackLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredRedVideoBlackLevel"></param>
        protected virtual void SetRedVideoBlackLevel(uint aVersion, uint aInstanceID, uint aDesiredRedVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetGreenVideoBlackLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetGreenVideoBlackLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetGreenVideoBlackLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentGreenVideoBlackLevel"></param>
        protected virtual void GetGreenVideoBlackLevel(uint aVersion, uint aInstanceID, out uint aCurrentGreenVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetGreenVideoBlackLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetGreenVideoBlackLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetGreenVideoBlackLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredGreenVideoBlackLevel"></param>
        protected virtual void SetGreenVideoBlackLevel(uint aVersion, uint aInstanceID, uint aDesiredGreenVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetBlueVideoBlackLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetBlueVideoBlackLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetBlueVideoBlackLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentBlueVideoBlackLevel"></param>
        protected virtual void GetBlueVideoBlackLevel(uint aVersion, uint aInstanceID, out uint aCurrentBlueVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetBlueVideoBlackLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetBlueVideoBlackLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetBlueVideoBlackLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredBlueVideoBlackLevel"></param>
        protected virtual void SetBlueVideoBlackLevel(uint aVersion, uint aInstanceID, uint aDesiredBlueVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetColorTemperature action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetColorTemperature action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetColorTemperature was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentColorTemperature"></param>
        protected virtual void GetColorTemperature(uint aVersion, uint aInstanceID, out uint aCurrentColorTemperature)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetColorTemperature action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetColorTemperature action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetColorTemperature was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredColorTemperature"></param>
        protected virtual void SetColorTemperature(uint aVersion, uint aInstanceID, uint aDesiredColorTemperature)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetHorizontalKeystone action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetHorizontalKeystone action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetHorizontalKeystone was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentHorizontalKeystone"></param>
        protected virtual void GetHorizontalKeystone(uint aVersion, uint aInstanceID, out int aCurrentHorizontalKeystone)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetHorizontalKeystone action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetHorizontalKeystone action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetHorizontalKeystone was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredHorizontalKeystone"></param>
        protected virtual void SetHorizontalKeystone(uint aVersion, uint aInstanceID, int aDesiredHorizontalKeystone)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetVerticalKeystone action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetVerticalKeystone action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetVerticalKeystone was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentVerticalKeystone"></param>
        protected virtual void GetVerticalKeystone(uint aVersion, uint aInstanceID, out int aCurrentVerticalKeystone)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetVerticalKeystone action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetVerticalKeystone action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetVerticalKeystone was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredVerticalKeystone"></param>
        protected virtual void SetVerticalKeystone(uint aVersion, uint aInstanceID, int aDesiredVerticalKeystone)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetMute action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetMute action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetMute was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCurrentMute"></param>
        protected virtual void GetMute(uint aVersion, uint aInstanceID, string aChannel, out bool aCurrentMute)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetMute action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetMute action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetMute was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredMute"></param>
        protected virtual void SetMute(uint aVersion, uint aInstanceID, string aChannel, bool aDesiredMute)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetVolume action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetVolume action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetVolume was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCurrentVolume"></param>
        protected virtual void GetVolume(uint aVersion, uint aInstanceID, string aChannel, out uint aCurrentVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetVolume action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetVolume action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetVolume was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredVolume"></param>
        protected virtual void SetVolume(uint aVersion, uint aInstanceID, string aChannel, uint aDesiredVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetVolumeDB action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetVolumeDB action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetVolumeDB was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCurrentVolume"></param>
        protected virtual void GetVolumeDB(uint aVersion, uint aInstanceID, string aChannel, out int aCurrentVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetVolumeDB action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetVolumeDB action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetVolumeDB was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredVolume"></param>
        protected virtual void SetVolumeDB(uint aVersion, uint aInstanceID, string aChannel, int aDesiredVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetVolumeDBRange action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetVolumeDBRange action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetVolumeDBRange was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aMinValue"></param>
        /// <param name="aMaxValue"></param>
        protected virtual void GetVolumeDBRange(uint aVersion, uint aInstanceID, string aChannel, out int aMinValue, out int aMaxValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetLoudness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetLoudness action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetLoudness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCurrentLoudness"></param>
        protected virtual void GetLoudness(uint aVersion, uint aInstanceID, string aChannel, out bool aCurrentLoudness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetLoudness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetLoudness action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetLoudness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredLoudness"></param>
        protected virtual void SetLoudness(uint aVersion, uint aInstanceID, string aChannel, bool aDesiredLoudness)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoListPresets(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                string currentPresetNameList;
                self.ListPresets(aVersion, instanceID, out currentPresetNameList);
                invocation.WriteStart();
                invocation.WriteString("CurrentPresetNameList", currentPresetNameList);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSelectPreset(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                string presetName = invocation.ReadString("PresetName");
                invocation.ReadEnd();
                self.SelectPreset(aVersion, instanceID, presetName);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetBrightness(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                uint currentBrightness;
                self.GetBrightness(aVersion, instanceID, out currentBrightness);
                invocation.WriteStart();
                invocation.WriteUint("CurrentBrightness", currentBrightness);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetBrightness(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                uint desiredBrightness = invocation.ReadUint("DesiredBrightness");
                invocation.ReadEnd();
                self.SetBrightness(aVersion, instanceID, desiredBrightness);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetContrast(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                uint currentContrast;
                self.GetContrast(aVersion, instanceID, out currentContrast);
                invocation.WriteStart();
                invocation.WriteUint("CurrentContrast", currentContrast);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetContrast(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                uint desiredContrast = invocation.ReadUint("DesiredContrast");
                invocation.ReadEnd();
                self.SetContrast(aVersion, instanceID, desiredContrast);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetSharpness(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                uint currentSharpness;
                self.GetSharpness(aVersion, instanceID, out currentSharpness);
                invocation.WriteStart();
                invocation.WriteUint("CurrentSharpness", currentSharpness);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetSharpness(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                uint desiredSharpness = invocation.ReadUint("DesiredSharpness");
                invocation.ReadEnd();
                self.SetSharpness(aVersion, instanceID, desiredSharpness);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetRedVideoGain(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                uint currentRedVideoGain;
                self.GetRedVideoGain(aVersion, instanceID, out currentRedVideoGain);
                invocation.WriteStart();
                invocation.WriteUint("CurrentRedVideoGain", currentRedVideoGain);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetRedVideoGain(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                uint desiredRedVideoGain = invocation.ReadUint("DesiredRedVideoGain");
                invocation.ReadEnd();
                self.SetRedVideoGain(aVersion, instanceID, desiredRedVideoGain);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetGreenVideoGain(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                uint currentGreenVideoGain;
                self.GetGreenVideoGain(aVersion, instanceID, out currentGreenVideoGain);
                invocation.WriteStart();
                invocation.WriteUint("CurrentGreenVideoGain", currentGreenVideoGain);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetGreenVideoGain(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                uint desiredGreenVideoGain = invocation.ReadUint("DesiredGreenVideoGain");
                invocation.ReadEnd();
                self.SetGreenVideoGain(aVersion, instanceID, desiredGreenVideoGain);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetBlueVideoGain(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                uint currentBlueVideoGain;
                self.GetBlueVideoGain(aVersion, instanceID, out currentBlueVideoGain);
                invocation.WriteStart();
                invocation.WriteUint("CurrentBlueVideoGain", currentBlueVideoGain);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetBlueVideoGain(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                uint desiredBlueVideoGain = invocation.ReadUint("DesiredBlueVideoGain");
                invocation.ReadEnd();
                self.SetBlueVideoGain(aVersion, instanceID, desiredBlueVideoGain);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetRedVideoBlackLevel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                uint currentRedVideoBlackLevel;
                self.GetRedVideoBlackLevel(aVersion, instanceID, out currentRedVideoBlackLevel);
                invocation.WriteStart();
                invocation.WriteUint("CurrentRedVideoBlackLevel", currentRedVideoBlackLevel);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetRedVideoBlackLevel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                uint desiredRedVideoBlackLevel = invocation.ReadUint("DesiredRedVideoBlackLevel");
                invocation.ReadEnd();
                self.SetRedVideoBlackLevel(aVersion, instanceID, desiredRedVideoBlackLevel);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetGreenVideoBlackLevel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                uint currentGreenVideoBlackLevel;
                self.GetGreenVideoBlackLevel(aVersion, instanceID, out currentGreenVideoBlackLevel);
                invocation.WriteStart();
                invocation.WriteUint("CurrentGreenVideoBlackLevel", currentGreenVideoBlackLevel);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetGreenVideoBlackLevel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                uint desiredGreenVideoBlackLevel = invocation.ReadUint("DesiredGreenVideoBlackLevel");
                invocation.ReadEnd();
                self.SetGreenVideoBlackLevel(aVersion, instanceID, desiredGreenVideoBlackLevel);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetBlueVideoBlackLevel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                uint currentBlueVideoBlackLevel;
                self.GetBlueVideoBlackLevel(aVersion, instanceID, out currentBlueVideoBlackLevel);
                invocation.WriteStart();
                invocation.WriteUint("CurrentBlueVideoBlackLevel", currentBlueVideoBlackLevel);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetBlueVideoBlackLevel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                uint desiredBlueVideoBlackLevel = invocation.ReadUint("DesiredBlueVideoBlackLevel");
                invocation.ReadEnd();
                self.SetBlueVideoBlackLevel(aVersion, instanceID, desiredBlueVideoBlackLevel);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetColorTemperature(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                uint currentColorTemperature;
                self.GetColorTemperature(aVersion, instanceID, out currentColorTemperature);
                invocation.WriteStart();
                invocation.WriteUint("CurrentColorTemperature", currentColorTemperature);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetColorTemperature(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                uint desiredColorTemperature = invocation.ReadUint("DesiredColorTemperature");
                invocation.ReadEnd();
                self.SetColorTemperature(aVersion, instanceID, desiredColorTemperature);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetHorizontalKeystone(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                int currentHorizontalKeystone;
                self.GetHorizontalKeystone(aVersion, instanceID, out currentHorizontalKeystone);
                invocation.WriteStart();
                invocation.WriteInt("CurrentHorizontalKeystone", currentHorizontalKeystone);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetHorizontalKeystone(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                int desiredHorizontalKeystone = invocation.ReadInt("DesiredHorizontalKeystone");
                invocation.ReadEnd();
                self.SetHorizontalKeystone(aVersion, instanceID, desiredHorizontalKeystone);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetVerticalKeystone(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                invocation.ReadEnd();
                int currentVerticalKeystone;
                self.GetVerticalKeystone(aVersion, instanceID, out currentVerticalKeystone);
                invocation.WriteStart();
                invocation.WriteInt("CurrentVerticalKeystone", currentVerticalKeystone);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetVerticalKeystone(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                int desiredVerticalKeystone = invocation.ReadInt("DesiredVerticalKeystone");
                invocation.ReadEnd();
                self.SetVerticalKeystone(aVersion, instanceID, desiredVerticalKeystone);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetMute(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                string channel = invocation.ReadString("Channel");
                invocation.ReadEnd();
                bool currentMute;
                self.GetMute(aVersion, instanceID, channel, out currentMute);
                invocation.WriteStart();
                invocation.WriteBool("CurrentMute", currentMute);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetMute(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                string channel = invocation.ReadString("Channel");
                bool desiredMute = invocation.ReadBool("DesiredMute");
                invocation.ReadEnd();
                self.SetMute(aVersion, instanceID, channel, desiredMute);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetVolume(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                string channel = invocation.ReadString("Channel");
                invocation.ReadEnd();
                uint currentVolume;
                self.GetVolume(aVersion, instanceID, channel, out currentVolume);
                invocation.WriteStart();
                invocation.WriteUint("CurrentVolume", currentVolume);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetVolume(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                string channel = invocation.ReadString("Channel");
                uint desiredVolume = invocation.ReadUint("DesiredVolume");
                invocation.ReadEnd();
                self.SetVolume(aVersion, instanceID, channel, desiredVolume);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetVolumeDB(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                string channel = invocation.ReadString("Channel");
                invocation.ReadEnd();
                int currentVolume;
                self.GetVolumeDB(aVersion, instanceID, channel, out currentVolume);
                invocation.WriteStart();
                invocation.WriteInt("CurrentVolume", currentVolume);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetVolumeDB(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                string channel = invocation.ReadString("Channel");
                int desiredVolume = invocation.ReadInt("DesiredVolume");
                invocation.ReadEnd();
                self.SetVolumeDB(aVersion, instanceID, channel, desiredVolume);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetVolumeDBRange(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                string channel = invocation.ReadString("Channel");
                invocation.ReadEnd();
                int minValue;
                int maxValue;
                self.GetVolumeDBRange(aVersion, instanceID, channel, out minValue, out maxValue);
                invocation.WriteStart();
                invocation.WriteInt("MinValue", minValue);
                invocation.WriteInt("MaxValue", maxValue);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoGetLoudness(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                string channel = invocation.ReadString("Channel");
                invocation.ReadEnd();
                bool currentLoudness;
                self.GetLoudness(aVersion, instanceID, channel, out currentLoudness);
                invocation.WriteStart();
                invocation.WriteBool("CurrentLoudness", currentLoudness);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetLoudness(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl1 self = (DvProviderUpnpOrgRenderingControl1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint instanceID = invocation.ReadUint("InstanceID");
                string channel = invocation.ReadString("Channel");
                bool desiredLoudness = invocation.ReadBool("DesiredLoudness");
                invocation.ReadEnd();
                self.SetLoudness(aVersion, instanceID, channel, desiredLoudness);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
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

        ~DvProviderUpnpOrgRenderingControl1()
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

