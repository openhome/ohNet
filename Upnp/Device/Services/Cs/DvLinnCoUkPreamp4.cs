using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkPreamp4 : IDisposable
    {

        /// <summary>
        /// Set the value of the Volume property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVolume(uint aValue);

        /// <summary>
        /// Get a copy of the value of the Volume property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyVolume();

        /// <summary>
        /// Set the value of the Mute property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyMute(bool aValue);

        /// <summary>
        /// Get a copy of the value of the Mute property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyMute();

        /// <summary>
        /// Set the value of the Balance property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyBalance(int aValue);

        /// <summary>
        /// Get a copy of the value of the Balance property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        int PropertyBalance();

        /// <summary>
        /// Set the value of the VolumeLimit property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVolumeLimit(uint aValue);

        /// <summary>
        /// Get a copy of the value of the VolumeLimit property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyVolumeLimit();

        /// <summary>
        /// Set the value of the StartupVolume property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyStartupVolume(uint aValue);

        /// <summary>
        /// Get a copy of the value of the StartupVolume property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyStartupVolume();

        /// <summary>
        /// Set the value of the StartupVolumeEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyStartupVolumeEnabled(bool aValue);

        /// <summary>
        /// Get a copy of the value of the StartupVolumeEnabled property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyStartupVolumeEnabled();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Preamp:4 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkPreamp4 : DvProvider, IDisposable, IDvProviderLinnCoUkPreamp4
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateVolumeInc;
        private ActionDelegate iDelegateVolumeDec;
        private ActionDelegate iDelegateSetVolume;
        private ActionDelegate iDelegateVolume;
        private ActionDelegate iDelegateSetMute;
        private ActionDelegate iDelegateMute;
        private ActionDelegate iDelegateSetBalance;
        private ActionDelegate iDelegateBalance;
        private ActionDelegate iDelegateSetVolumeLimit;
        private ActionDelegate iDelegateVolumeLimit;
        private ActionDelegate iDelegateSetStartupVolume;
        private ActionDelegate iDelegateStartupVolume;
        private ActionDelegate iDelegateSetStartupVolumeEnabled;
        private ActionDelegate iDelegateStartupVolumeEnabled;
        private PropertyUint iPropertyVolume;
        private PropertyBool iPropertyMute;
        private PropertyInt iPropertyBalance;
        private PropertyUint iPropertyVolumeLimit;
        private PropertyUint iPropertyStartupVolume;
        private PropertyBool iPropertyStartupVolumeEnabled;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkPreamp4(DvDevice aDevice)
            : base(aDevice, "linn.co.uk", "Preamp", 4)
        {
            iGch = GCHandle.Alloc(this);
            iPropertyVolume = new PropertyUint(new ParameterUint("Volume"));
            AddProperty(iPropertyVolume);
            iPropertyMute = new PropertyBool(new ParameterBool("Mute"));
            AddProperty(iPropertyMute);
            iPropertyBalance = new PropertyInt(new ParameterInt("Balance"));
            AddProperty(iPropertyBalance);
            iPropertyVolumeLimit = new PropertyUint(new ParameterUint("VolumeLimit"));
            AddProperty(iPropertyVolumeLimit);
            iPropertyStartupVolume = new PropertyUint(new ParameterUint("StartupVolume"));
            AddProperty(iPropertyStartupVolume);
            iPropertyStartupVolumeEnabled = new PropertyBool(new ParameterBool("StartupVolumeEnabled"));
            AddProperty(iPropertyStartupVolumeEnabled);
        }

        /// <summary>
        /// Set the value of the Volume property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVolume(uint aValue)
        {
            return SetPropertyUint(iPropertyVolume, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Volume property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyVolume()
        {
            return iPropertyVolume.Value();
        }

        /// <summary>
        /// Set the value of the Mute property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyMute(bool aValue)
        {
            return SetPropertyBool(iPropertyMute, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Mute property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyMute()
        {
            return iPropertyMute.Value();
        }

        /// <summary>
        /// Set the value of the Balance property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyBalance(int aValue)
        {
            return SetPropertyInt(iPropertyBalance, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Balance property
        /// </summary>
        /// <returns>The value of the property</returns>
        public int PropertyBalance()
        {
            return iPropertyBalance.Value();
        }

        /// <summary>
        /// Set the value of the VolumeLimit property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVolumeLimit(uint aValue)
        {
            return SetPropertyUint(iPropertyVolumeLimit, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VolumeLimit property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyVolumeLimit()
        {
            return iPropertyVolumeLimit.Value();
        }

        /// <summary>
        /// Set the value of the StartupVolume property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyStartupVolume(uint aValue)
        {
            return SetPropertyUint(iPropertyStartupVolume, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the StartupVolume property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyStartupVolume()
        {
            return iPropertyStartupVolume.Value();
        }

        /// <summary>
        /// Set the value of the StartupVolumeEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyStartupVolumeEnabled(bool aValue)
        {
            return SetPropertyBool(iPropertyStartupVolumeEnabled, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the StartupVolumeEnabled property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyStartupVolumeEnabled()
        {
            return iPropertyStartupVolumeEnabled.Value();
        }

        /// <summary>
        /// Signal that the action VolumeInc is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// VolumeInc must be overridden if this is called.</remarks>
        protected void EnableActionVolumeInc()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("VolumeInc");
            iDelegateVolumeInc = new ActionDelegate(DoVolumeInc);
            EnableAction(action, iDelegateVolumeInc, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action VolumeDec is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// VolumeDec must be overridden if this is called.</remarks>
        protected void EnableActionVolumeDec()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("VolumeDec");
            iDelegateVolumeDec = new ActionDelegate(DoVolumeDec);
            EnableAction(action, iDelegateVolumeDec, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetVolume is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetVolume must be overridden if this is called.</remarks>
        protected void EnableActionSetVolume()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetVolume");
            action.AddInputParameter(new ParameterUint("aVolume"));
            iDelegateSetVolume = new ActionDelegate(DoSetVolume);
            EnableAction(action, iDelegateSetVolume, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Volume is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Volume must be overridden if this is called.</remarks>
        protected void EnableActionVolume()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Volume");
            action.AddOutputParameter(new ParameterUint("aVolume"));
            iDelegateVolume = new ActionDelegate(DoVolume);
            EnableAction(action, iDelegateVolume, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetMute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetMute must be overridden if this is called.</remarks>
        protected void EnableActionSetMute()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetMute");
            action.AddInputParameter(new ParameterBool("aMute"));
            iDelegateSetMute = new ActionDelegate(DoSetMute);
            EnableAction(action, iDelegateSetMute, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Mute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Mute must be overridden if this is called.</remarks>
        protected void EnableActionMute()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Mute");
            action.AddOutputParameter(new ParameterBool("aMute"));
            iDelegateMute = new ActionDelegate(DoMute);
            EnableAction(action, iDelegateMute, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetBalance is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetBalance must be overridden if this is called.</remarks>
        protected void EnableActionSetBalance()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetBalance");
            action.AddInputParameter(new ParameterInt("aBalance"));
            iDelegateSetBalance = new ActionDelegate(DoSetBalance);
            EnableAction(action, iDelegateSetBalance, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Balance is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Balance must be overridden if this is called.</remarks>
        protected void EnableActionBalance()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Balance");
            action.AddOutputParameter(new ParameterInt("aBalance"));
            iDelegateBalance = new ActionDelegate(DoBalance);
            EnableAction(action, iDelegateBalance, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetVolumeLimit is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetVolumeLimit must be overridden if this is called.</remarks>
        protected void EnableActionSetVolumeLimit()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetVolumeLimit");
            action.AddInputParameter(new ParameterUint("aVolumeLimit"));
            iDelegateSetVolumeLimit = new ActionDelegate(DoSetVolumeLimit);
            EnableAction(action, iDelegateSetVolumeLimit, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action VolumeLimit is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// VolumeLimit must be overridden if this is called.</remarks>
        protected void EnableActionVolumeLimit()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("VolumeLimit");
            action.AddOutputParameter(new ParameterUint("aVolumeLimit"));
            iDelegateVolumeLimit = new ActionDelegate(DoVolumeLimit);
            EnableAction(action, iDelegateVolumeLimit, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetStartupVolume is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetStartupVolume must be overridden if this is called.</remarks>
        protected void EnableActionSetStartupVolume()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetStartupVolume");
            action.AddInputParameter(new ParameterUint("aStartupVolume"));
            iDelegateSetStartupVolume = new ActionDelegate(DoSetStartupVolume);
            EnableAction(action, iDelegateSetStartupVolume, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action StartupVolume is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// StartupVolume must be overridden if this is called.</remarks>
        protected void EnableActionStartupVolume()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("StartupVolume");
            action.AddOutputParameter(new ParameterUint("aStartupVolume"));
            iDelegateStartupVolume = new ActionDelegate(DoStartupVolume);
            EnableAction(action, iDelegateStartupVolume, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetStartupVolumeEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetStartupVolumeEnabled must be overridden if this is called.</remarks>
        protected void EnableActionSetStartupVolumeEnabled()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetStartupVolumeEnabled");
            action.AddInputParameter(new ParameterBool("aStartupVolumeEnabled"));
            iDelegateSetStartupVolumeEnabled = new ActionDelegate(DoSetStartupVolumeEnabled);
            EnableAction(action, iDelegateSetStartupVolumeEnabled, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action StartupVolumeEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// StartupVolumeEnabled must be overridden if this is called.</remarks>
        protected void EnableActionStartupVolumeEnabled()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("StartupVolumeEnabled");
            action.AddOutputParameter(new ParameterBool("aStartupVolumeEnabled"));
            iDelegateStartupVolumeEnabled = new ActionDelegate(DoStartupVolumeEnabled);
            EnableAction(action, iDelegateStartupVolumeEnabled, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// VolumeInc action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// VolumeInc action for the owning device.
        ///
        /// Must be implemented iff EnableActionVolumeInc was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void VolumeInc(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// VolumeDec action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// VolumeDec action for the owning device.
        ///
        /// Must be implemented iff EnableActionVolumeDec was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void VolumeDec(uint aVersion)
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
        /// <param name="aaVolume"></param>
        protected virtual void SetVolume(uint aVersion, uint aaVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Volume action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Volume action for the owning device.
        ///
        /// Must be implemented iff EnableActionVolume was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaVolume"></param>
        protected virtual void Volume(uint aVersion, out uint aaVolume)
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
        /// <param name="aaMute"></param>
        protected virtual void SetMute(uint aVersion, bool aaMute)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Mute action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Mute action for the owning device.
        ///
        /// Must be implemented iff EnableActionMute was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMute"></param>
        protected virtual void Mute(uint aVersion, out bool aaMute)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetBalance action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetBalance action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetBalance was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaBalance"></param>
        protected virtual void SetBalance(uint aVersion, int aaBalance)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Balance action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Balance action for the owning device.
        ///
        /// Must be implemented iff EnableActionBalance was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaBalance"></param>
        protected virtual void Balance(uint aVersion, out int aaBalance)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetVolumeLimit action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetVolumeLimit action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetVolumeLimit was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaVolumeLimit"></param>
        protected virtual void SetVolumeLimit(uint aVersion, uint aaVolumeLimit)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// VolumeLimit action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// VolumeLimit action for the owning device.
        ///
        /// Must be implemented iff EnableActionVolumeLimit was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaVolumeLimit"></param>
        protected virtual void VolumeLimit(uint aVersion, out uint aaVolumeLimit)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStartupVolume action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStartupVolume action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStartupVolume was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStartupVolume"></param>
        protected virtual void SetStartupVolume(uint aVersion, uint aaStartupVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StartupVolume action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StartupVolume action for the owning device.
        ///
        /// Must be implemented iff EnableActionStartupVolume was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStartupVolume"></param>
        protected virtual void StartupVolume(uint aVersion, out uint aaStartupVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStartupVolumeEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStartupVolumeEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStartupVolumeEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStartupVolumeEnabled"></param>
        protected virtual void SetStartupVolumeEnabled(uint aVersion, bool aaStartupVolumeEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StartupVolumeEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StartupVolumeEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionStartupVolumeEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStartupVolumeEnabled"></param>
        protected virtual void StartupVolumeEnabled(uint aVersion, out bool aaStartupVolumeEnabled)
        {
            throw (new ActionDisabledError());
        }

        private static int DoVolumeInc(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.VolumeInc(aVersion);
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

        private static int DoVolumeDec(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.VolumeDec(aVersion);
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

        private static int DoSetVolume(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aVolume;
            try
            {
                invocation.ReadStart();
                aVolume = invocation.ReadUint("aVolume");
                invocation.ReadEnd();
                self.SetVolume(aVersion, aVolume);
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

        private static int DoVolume(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aVolume;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Volume(aVersion, out aVolume);
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
                invocation.WriteUint("aVolume", aVolume);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetMute(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aMute;
            try
            {
                invocation.ReadStart();
                aMute = invocation.ReadBool("aMute");
                invocation.ReadEnd();
                self.SetMute(aVersion, aMute);
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

        private static int DoMute(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aMute;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Mute(aVersion, out aMute);
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
                invocation.WriteBool("aMute", aMute);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetBalance(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int aBalance;
            try
            {
                invocation.ReadStart();
                aBalance = invocation.ReadInt("aBalance");
                invocation.ReadEnd();
                self.SetBalance(aVersion, aBalance);
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

        private static int DoBalance(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int aBalance;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Balance(aVersion, out aBalance);
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
                invocation.WriteInt("aBalance", aBalance);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetVolumeLimit(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aVolumeLimit;
            try
            {
                invocation.ReadStart();
                aVolumeLimit = invocation.ReadUint("aVolumeLimit");
                invocation.ReadEnd();
                self.SetVolumeLimit(aVersion, aVolumeLimit);
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

        private static int DoVolumeLimit(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aVolumeLimit;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.VolumeLimit(aVersion, out aVolumeLimit);
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
                invocation.WriteUint("aVolumeLimit", aVolumeLimit);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetStartupVolume(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aStartupVolume;
            try
            {
                invocation.ReadStart();
                aStartupVolume = invocation.ReadUint("aStartupVolume");
                invocation.ReadEnd();
                self.SetStartupVolume(aVersion, aStartupVolume);
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

        private static int DoStartupVolume(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aStartupVolume;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.StartupVolume(aVersion, out aStartupVolume);
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
                invocation.WriteUint("aStartupVolume", aStartupVolume);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetStartupVolumeEnabled(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aStartupVolumeEnabled;
            try
            {
                invocation.ReadStart();
                aStartupVolumeEnabled = invocation.ReadBool("aStartupVolumeEnabled");
                invocation.ReadEnd();
                self.SetStartupVolumeEnabled(aVersion, aStartupVolumeEnabled);
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

        private static int DoStartupVolumeEnabled(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool aStartupVolumeEnabled;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.StartupVolumeEnabled(aVersion, out aStartupVolumeEnabled);
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
                invocation.WriteBool("aStartupVolumeEnabled", aStartupVolumeEnabled);
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

        ~DvProviderLinnCoUkPreamp4()
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

