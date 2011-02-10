using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkComponent1 : IDisposable
    {

        /// <summary>
        /// Set the value of the AmplifierEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyAmplifierEnabled(bool aValue);

        /// <summary>
        /// Get a copy of the value of the AmplifierEnabled property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyAmplifierEnabled();

        /// <summary>
        /// Set the value of the AmplifierAttenuation property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyAmplifierAttenuation(string aValue);

        /// <summary>
        /// Get a copy of the value of the AmplifierAttenuation property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyAmplifierAttenuation();

        /// <summary>
        /// Set the value of the VolumeControlEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVolumeControlEnabled(bool aValue);

        /// <summary>
        /// Get a copy of the value of the VolumeControlEnabled property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyVolumeControlEnabled();

        /// <summary>
        /// Set the value of the DigitalAudioOutputRaw property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDigitalAudioOutputRaw(bool aValue);

        /// <summary>
        /// Get a copy of the value of the DigitalAudioOutputRaw property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyDigitalAudioOutputRaw();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Component:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkComponent1 : DvProvider, IDisposable, IDvProviderLinnCoUkComponent1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateAmplifierEnabled;
        private ActionDelegate iDelegateSetAmplifierEnabled;
        private ActionDelegate iDelegateAmplifierAttenuation;
        private ActionDelegate iDelegateSetAmplifierAttenuation;
        private ActionDelegate iDelegateSetVolumeControlEnabled;
        private ActionDelegate iDelegateVolumeControlEnabled;
        private ActionDelegate iDelegateSetDigitalAudioOutputRaw;
        private ActionDelegate iDelegateDigitalAudioOutputRaw;
        private ActionDelegate iDelegateAmplifierOverTemperature;
        private ActionDelegate iDelegateEthernetLinkConnected;
        private ActionDelegate iDelegateLocate;
        private PropertyBool iPropertyAmplifierEnabled;
        private PropertyString iPropertyAmplifierAttenuation;
        private PropertyBool iPropertyVolumeControlEnabled;
        private PropertyBool iPropertyDigitalAudioOutputRaw;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkComponent1(DvDevice aDevice)
            : base(aDevice, "linn.co.uk", "Component", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyAmplifierEnabled = new PropertyBool(new ParameterBool("AmplifierEnabled"));
            AddProperty(iPropertyAmplifierEnabled);
            allowedValues.Add("-12dB");
            allowedValues.Add("-9dB");
            allowedValues.Add("-6dB");
            allowedValues.Add("0dB");
            iPropertyAmplifierAttenuation = new PropertyString(new ParameterString("AmplifierAttenuation", allowedValues));
            AddProperty(iPropertyAmplifierAttenuation);
            allowedValues.Clear();
            iPropertyVolumeControlEnabled = new PropertyBool(new ParameterBool("VolumeControlEnabled"));
            AddProperty(iPropertyVolumeControlEnabled);
            iPropertyDigitalAudioOutputRaw = new PropertyBool(new ParameterBool("DigitalAudioOutputRaw"));
            AddProperty(iPropertyDigitalAudioOutputRaw);
        }

        /// <summary>
        /// Set the value of the AmplifierEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyAmplifierEnabled(bool aValue)
        {
            return SetPropertyBool(iPropertyAmplifierEnabled, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the AmplifierEnabled property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyAmplifierEnabled()
        {
            return iPropertyAmplifierEnabled.Value();
        }

        /// <summary>
        /// Set the value of the AmplifierAttenuation property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyAmplifierAttenuation(string aValue)
        {
            return SetPropertyString(iPropertyAmplifierAttenuation, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the AmplifierAttenuation property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyAmplifierAttenuation()
        {
            return iPropertyAmplifierAttenuation.Value();
        }

        /// <summary>
        /// Set the value of the VolumeControlEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVolumeControlEnabled(bool aValue)
        {
            return SetPropertyBool(iPropertyVolumeControlEnabled, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VolumeControlEnabled property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyVolumeControlEnabled()
        {
            return iPropertyVolumeControlEnabled.Value();
        }

        /// <summary>
        /// Set the value of the DigitalAudioOutputRaw property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDigitalAudioOutputRaw(bool aValue)
        {
            return SetPropertyBool(iPropertyDigitalAudioOutputRaw, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the DigitalAudioOutputRaw property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyDigitalAudioOutputRaw()
        {
            return iPropertyDigitalAudioOutputRaw.Value();
        }

        /// <summary>
        /// Signal that the action AmplifierEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// AmplifierEnabled must be overridden if this is called.</remarks>
        protected void EnableActionAmplifierEnabled()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("AmplifierEnabled");
            action.AddOutputParameter(new ParameterRelated("aEnabled", iPropertyAmplifierEnabled));
            iDelegateAmplifierEnabled = new ActionDelegate(DoAmplifierEnabled);
            EnableAction(action, iDelegateAmplifierEnabled, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetAmplifierEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetAmplifierEnabled must be overridden if this is called.</remarks>
        protected void EnableActionSetAmplifierEnabled()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetAmplifierEnabled");
            action.AddInputParameter(new ParameterRelated("aEnabled", iPropertyAmplifierEnabled));
            iDelegateSetAmplifierEnabled = new ActionDelegate(DoSetAmplifierEnabled);
            EnableAction(action, iDelegateSetAmplifierEnabled, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action AmplifierAttenuation is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// AmplifierAttenuation must be overridden if this is called.</remarks>
        protected void EnableActionAmplifierAttenuation()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("AmplifierAttenuation");
            action.AddOutputParameter(new ParameterRelated("aAttenuation", iPropertyAmplifierAttenuation));
            iDelegateAmplifierAttenuation = new ActionDelegate(DoAmplifierAttenuation);
            EnableAction(action, iDelegateAmplifierAttenuation, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetAmplifierAttenuation is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetAmplifierAttenuation must be overridden if this is called.</remarks>
        protected void EnableActionSetAmplifierAttenuation()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetAmplifierAttenuation");
            action.AddInputParameter(new ParameterRelated("aAttenuation", iPropertyAmplifierAttenuation));
            iDelegateSetAmplifierAttenuation = new ActionDelegate(DoSetAmplifierAttenuation);
            EnableAction(action, iDelegateSetAmplifierAttenuation, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetVolumeControlEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetVolumeControlEnabled must be overridden if this is called.</remarks>
        protected void EnableActionSetVolumeControlEnabled()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetVolumeControlEnabled");
            action.AddInputParameter(new ParameterRelated("aEnabled", iPropertyVolumeControlEnabled));
            iDelegateSetVolumeControlEnabled = new ActionDelegate(DoSetVolumeControlEnabled);
            EnableAction(action, iDelegateSetVolumeControlEnabled, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action VolumeControlEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// VolumeControlEnabled must be overridden if this is called.</remarks>
        protected void EnableActionVolumeControlEnabled()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("VolumeControlEnabled");
            action.AddOutputParameter(new ParameterRelated("aEnabled", iPropertyVolumeControlEnabled));
            iDelegateVolumeControlEnabled = new ActionDelegate(DoVolumeControlEnabled);
            EnableAction(action, iDelegateVolumeControlEnabled, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetDigitalAudioOutputRaw is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetDigitalAudioOutputRaw must be overridden if this is called.</remarks>
        protected void EnableActionSetDigitalAudioOutputRaw()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetDigitalAudioOutputRaw");
            action.AddInputParameter(new ParameterRelated("aRaw", iPropertyDigitalAudioOutputRaw));
            iDelegateSetDigitalAudioOutputRaw = new ActionDelegate(DoSetDigitalAudioOutputRaw);
            EnableAction(action, iDelegateSetDigitalAudioOutputRaw, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DigitalAudioOutputRaw is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DigitalAudioOutputRaw must be overridden if this is called.</remarks>
        protected void EnableActionDigitalAudioOutputRaw()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DigitalAudioOutputRaw");
            action.AddOutputParameter(new ParameterRelated("aRaw", iPropertyDigitalAudioOutputRaw));
            iDelegateDigitalAudioOutputRaw = new ActionDelegate(DoDigitalAudioOutputRaw);
            EnableAction(action, iDelegateDigitalAudioOutputRaw, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action AmplifierOverTemperature is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// AmplifierOverTemperature must be overridden if this is called.</remarks>
        protected void EnableActionAmplifierOverTemperature()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("AmplifierOverTemperature");
            action.AddOutputParameter(new ParameterBool("aOverTemperature"));
            iDelegateAmplifierOverTemperature = new ActionDelegate(DoAmplifierOverTemperature);
            EnableAction(action, iDelegateAmplifierOverTemperature, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action EthernetLinkConnected is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// EthernetLinkConnected must be overridden if this is called.</remarks>
        protected void EnableActionEthernetLinkConnected()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("EthernetLinkConnected");
            action.AddOutputParameter(new ParameterBool("aLinkConnected"));
            iDelegateEthernetLinkConnected = new ActionDelegate(DoEthernetLinkConnected);
            EnableAction(action, iDelegateEthernetLinkConnected, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Locate is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Locate must be overridden if this is called.</remarks>
        protected void EnableActionLocate()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Locate");
            iDelegateLocate = new ActionDelegate(DoLocate);
            EnableAction(action, iDelegateLocate, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// AmplifierEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// AmplifierEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionAmplifierEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaEnabled"></param>
        protected virtual void AmplifierEnabled(uint aVersion, out bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetAmplifierEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetAmplifierEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetAmplifierEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaEnabled"></param>
        protected virtual void SetAmplifierEnabled(uint aVersion, bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// AmplifierAttenuation action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// AmplifierAttenuation action for the owning device.
        ///
        /// Must be implemented iff EnableActionAmplifierAttenuation was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaAttenuation"></param>
        protected virtual void AmplifierAttenuation(uint aVersion, out string aaAttenuation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetAmplifierAttenuation action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetAmplifierAttenuation action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetAmplifierAttenuation was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaAttenuation"></param>
        protected virtual void SetAmplifierAttenuation(uint aVersion, string aaAttenuation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetVolumeControlEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetVolumeControlEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetVolumeControlEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaEnabled"></param>
        protected virtual void SetVolumeControlEnabled(uint aVersion, bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// VolumeControlEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// VolumeControlEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionVolumeControlEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaEnabled"></param>
        protected virtual void VolumeControlEnabled(uint aVersion, out bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDigitalAudioOutputRaw action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDigitalAudioOutputRaw action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDigitalAudioOutputRaw was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaRaw"></param>
        protected virtual void SetDigitalAudioOutputRaw(uint aVersion, bool aaRaw)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DigitalAudioOutputRaw action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DigitalAudioOutputRaw action for the owning device.
        ///
        /// Must be implemented iff EnableActionDigitalAudioOutputRaw was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaRaw"></param>
        protected virtual void DigitalAudioOutputRaw(uint aVersion, out bool aaRaw)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// AmplifierOverTemperature action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// AmplifierOverTemperature action for the owning device.
        ///
        /// Must be implemented iff EnableActionAmplifierOverTemperature was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaOverTemperature"></param>
        protected virtual void AmplifierOverTemperature(uint aVersion, out bool aaOverTemperature)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// EthernetLinkConnected action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// EthernetLinkConnected action for the owning device.
        ///
        /// Must be implemented iff EnableActionEthernetLinkConnected was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaLinkConnected"></param>
        protected virtual void EthernetLinkConnected(uint aVersion, out bool aaLinkConnected)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Locate action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Locate action for the owning device.
        ///
        /// Must be implemented iff EnableActionLocate was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Locate(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        private static int DoAmplifierEnabled(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aEnabled;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.AmplifierEnabled(aVersion, out aEnabled);
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

        private static int DoSetAmplifierEnabled(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aEnabled;
            try
            {
                invocation.ReadStart();
                aEnabled = invocation.ReadBool("aEnabled");
                invocation.ReadEnd();
                self.SetAmplifierEnabled(aVersion, aEnabled);
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

        private static int DoAmplifierAttenuation(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aAttenuation;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.AmplifierAttenuation(aVersion, out aAttenuation);
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
                invocation.WriteString("aAttenuation", aAttenuation);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetAmplifierAttenuation(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aAttenuation;
            try
            {
                invocation.ReadStart();
                aAttenuation = invocation.ReadString("aAttenuation");
                invocation.ReadEnd();
                self.SetAmplifierAttenuation(aVersion, aAttenuation);
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

        private static int DoSetVolumeControlEnabled(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aEnabled;
            try
            {
                invocation.ReadStart();
                aEnabled = invocation.ReadBool("aEnabled");
                invocation.ReadEnd();
                self.SetVolumeControlEnabled(aVersion, aEnabled);
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

        private static int DoVolumeControlEnabled(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aEnabled;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.VolumeControlEnabled(aVersion, out aEnabled);
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

        private static int DoSetDigitalAudioOutputRaw(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aRaw;
            try
            {
                invocation.ReadStart();
                aRaw = invocation.ReadBool("aRaw");
                invocation.ReadEnd();
                self.SetDigitalAudioOutputRaw(aVersion, aRaw);
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

        private static int DoDigitalAudioOutputRaw(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aRaw;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.DigitalAudioOutputRaw(aVersion, out aRaw);
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
                invocation.WriteBool("aRaw", aRaw);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoAmplifierOverTemperature(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aOverTemperature;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.AmplifierOverTemperature(aVersion, out aOverTemperature);
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
                invocation.WriteBool("aOverTemperature", aOverTemperature);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoEthernetLinkConnected(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aLinkConnected;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.EthernetLinkConnected(aVersion, out aLinkConnected);
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
                invocation.WriteBool("aLinkConnected", aLinkConnected);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoLocate(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Locate(aVersion);
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

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderLinnCoUkComponent1()
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

