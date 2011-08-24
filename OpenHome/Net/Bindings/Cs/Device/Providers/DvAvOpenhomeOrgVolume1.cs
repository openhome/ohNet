using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
{
    public interface IDvProviderAvOpenhomeOrgVolume1 : IDisposable
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
        /// <returns>Value of the Volume property.</param>
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
        /// <returns>Value of the Mute property.</param>
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
        /// <returns>Value of the Balance property.</param>
        int PropertyBalance();

        /// <summary>
        /// Set the value of the Fade property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyFade(int aValue);

        /// <summary>
        /// Get a copy of the value of the Fade property
        /// </summary>
        /// <returns>Value of the Fade property.</param>
        int PropertyFade();

        /// <summary>
        /// Set the value of the VolumeLimit property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVolumeLimit(uint aValue);

        /// <summary>
        /// Get a copy of the value of the VolumeLimit property
        /// </summary>
        /// <returns>Value of the VolumeLimit property.</param>
        uint PropertyVolumeLimit();

        /// <summary>
        /// Set the value of the VolumeMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVolumeMax(uint aValue);

        /// <summary>
        /// Get a copy of the value of the VolumeMax property
        /// </summary>
        /// <returns>Value of the VolumeMax property.</param>
        uint PropertyVolumeMax();

        /// <summary>
        /// Set the value of the VolumeUnity property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVolumeUnity(uint aValue);

        /// <summary>
        /// Get a copy of the value of the VolumeUnity property
        /// </summary>
        /// <returns>Value of the VolumeUnity property.</param>
        uint PropertyVolumeUnity();

        /// <summary>
        /// Set the value of the VolumeSteps property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVolumeSteps(uint aValue);

        /// <summary>
        /// Get a copy of the value of the VolumeSteps property
        /// </summary>
        /// <returns>Value of the VolumeSteps property.</param>
        uint PropertyVolumeSteps();

        /// <summary>
        /// Set the value of the VolumeMilliDbPerStep property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVolumeMilliDbPerStep(uint aValue);

        /// <summary>
        /// Get a copy of the value of the VolumeMilliDbPerStep property
        /// </summary>
        /// <returns>Value of the VolumeMilliDbPerStep property.</param>
        uint PropertyVolumeMilliDbPerStep();

        /// <summary>
        /// Set the value of the BalanceMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyBalanceMax(uint aValue);

        /// <summary>
        /// Get a copy of the value of the BalanceMax property
        /// </summary>
        /// <returns>Value of the BalanceMax property.</param>
        uint PropertyBalanceMax();

        /// <summary>
        /// Set the value of the FadeMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyFadeMax(uint aValue);

        /// <summary>
        /// Get a copy of the value of the FadeMax property
        /// </summary>
        /// <returns>Value of the FadeMax property.</param>
        uint PropertyFadeMax();
        
    }
    /// <summary>
    /// Provider for the av.openhome.org:Volume:1 UPnP service
    /// </summary>
    public class DvProviderAvOpenhomeOrgVolume1 : DvProvider, IDisposable, IDvProviderAvOpenhomeOrgVolume1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateCharacteristics;
        private ActionDelegate iDelegateSetVolume;
        private ActionDelegate iDelegateVolumeInc;
        private ActionDelegate iDelegateVolumeDec;
        private ActionDelegate iDelegateVolume;
        private ActionDelegate iDelegateSetBalance;
        private ActionDelegate iDelegateBalanceInc;
        private ActionDelegate iDelegateBalanceDec;
        private ActionDelegate iDelegateBalance;
        private ActionDelegate iDelegateSetFade;
        private ActionDelegate iDelegateFadeInc;
        private ActionDelegate iDelegateFadeDec;
        private ActionDelegate iDelegateFade;
        private ActionDelegate iDelegateSetMute;
        private ActionDelegate iDelegateMute;
        private ActionDelegate iDelegateVolumeLimit;
        private PropertyUint iPropertyVolume;
        private PropertyBool iPropertyMute;
        private PropertyInt iPropertyBalance;
        private PropertyInt iPropertyFade;
        private PropertyUint iPropertyVolumeLimit;
        private PropertyUint iPropertyVolumeMax;
        private PropertyUint iPropertyVolumeUnity;
        private PropertyUint iPropertyVolumeSteps;
        private PropertyUint iPropertyVolumeMilliDbPerStep;
        private PropertyUint iPropertyBalanceMax;
        private PropertyUint iPropertyFadeMax;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderAvOpenhomeOrgVolume1(DvDevice aDevice)
            : base(aDevice, "av.openhome.org", "Volume", 1)
        {
            iGch = GCHandle.Alloc(this);
            iPropertyVolume = new PropertyUint(new ParameterUint("Volume"));
            AddProperty(iPropertyVolume);
            iPropertyMute = new PropertyBool(new ParameterBool("Mute"));
            AddProperty(iPropertyMute);
            iPropertyBalance = new PropertyInt(new ParameterInt("Balance"));
            AddProperty(iPropertyBalance);
            iPropertyFade = new PropertyInt(new ParameterInt("Fade"));
            AddProperty(iPropertyFade);
            iPropertyVolumeLimit = new PropertyUint(new ParameterUint("VolumeLimit"));
            AddProperty(iPropertyVolumeLimit);
            iPropertyVolumeMax = new PropertyUint(new ParameterUint("VolumeMax"));
            AddProperty(iPropertyVolumeMax);
            iPropertyVolumeUnity = new PropertyUint(new ParameterUint("VolumeUnity"));
            AddProperty(iPropertyVolumeUnity);
            iPropertyVolumeSteps = new PropertyUint(new ParameterUint("VolumeSteps"));
            AddProperty(iPropertyVolumeSteps);
            iPropertyVolumeMilliDbPerStep = new PropertyUint(new ParameterUint("VolumeMilliDbPerStep"));
            AddProperty(iPropertyVolumeMilliDbPerStep);
            iPropertyBalanceMax = new PropertyUint(new ParameterUint("BalanceMax"));
            AddProperty(iPropertyBalanceMax);
            iPropertyFadeMax = new PropertyUint(new ParameterUint("FadeMax"));
            AddProperty(iPropertyFadeMax);
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
        /// <returns>Value of the Volume property.</returns>
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
        /// <returns>Value of the Mute property.</returns>
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
        /// <returns>Value of the Balance property.</returns>
        public int PropertyBalance()
        {
            return iPropertyBalance.Value();
        }

        /// <summary>
        /// Set the value of the Fade property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyFade(int aValue)
        {
            return SetPropertyInt(iPropertyFade, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Fade property
        /// </summary>
        /// <returns>Value of the Fade property.</returns>
        public int PropertyFade()
        {
            return iPropertyFade.Value();
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
        /// <returns>Value of the VolumeLimit property.</returns>
        public uint PropertyVolumeLimit()
        {
            return iPropertyVolumeLimit.Value();
        }

        /// <summary>
        /// Set the value of the VolumeMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVolumeMax(uint aValue)
        {
            return SetPropertyUint(iPropertyVolumeMax, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VolumeMax property
        /// </summary>
        /// <returns>Value of the VolumeMax property.</returns>
        public uint PropertyVolumeMax()
        {
            return iPropertyVolumeMax.Value();
        }

        /// <summary>
        /// Set the value of the VolumeUnity property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVolumeUnity(uint aValue)
        {
            return SetPropertyUint(iPropertyVolumeUnity, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VolumeUnity property
        /// </summary>
        /// <returns>Value of the VolumeUnity property.</returns>
        public uint PropertyVolumeUnity()
        {
            return iPropertyVolumeUnity.Value();
        }

        /// <summary>
        /// Set the value of the VolumeSteps property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVolumeSteps(uint aValue)
        {
            return SetPropertyUint(iPropertyVolumeSteps, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VolumeSteps property
        /// </summary>
        /// <returns>Value of the VolumeSteps property.</returns>
        public uint PropertyVolumeSteps()
        {
            return iPropertyVolumeSteps.Value();
        }

        /// <summary>
        /// Set the value of the VolumeMilliDbPerStep property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVolumeMilliDbPerStep(uint aValue)
        {
            return SetPropertyUint(iPropertyVolumeMilliDbPerStep, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VolumeMilliDbPerStep property
        /// </summary>
        /// <returns>Value of the VolumeMilliDbPerStep property.</returns>
        public uint PropertyVolumeMilliDbPerStep()
        {
            return iPropertyVolumeMilliDbPerStep.Value();
        }

        /// <summary>
        /// Set the value of the BalanceMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyBalanceMax(uint aValue)
        {
            return SetPropertyUint(iPropertyBalanceMax, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the BalanceMax property
        /// </summary>
        /// <returns>Value of the BalanceMax property.</returns>
        public uint PropertyBalanceMax()
        {
            return iPropertyBalanceMax.Value();
        }

        /// <summary>
        /// Set the value of the FadeMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyFadeMax(uint aValue)
        {
            return SetPropertyUint(iPropertyFadeMax, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the FadeMax property
        /// </summary>
        /// <returns>Value of the FadeMax property.</returns>
        public uint PropertyFadeMax()
        {
            return iPropertyFadeMax.Value();
        }

        /// <summary>
        /// Signal that the action Characteristics is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Characteristics must be overridden if this is called.</remarks>
        protected void EnableActionCharacteristics()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Characteristics");
            action.AddOutputParameter(new ParameterRelated("VolumeMax", iPropertyVolumeMax));
            action.AddOutputParameter(new ParameterRelated("VolumeUnity", iPropertyVolumeUnity));
            action.AddOutputParameter(new ParameterRelated("VolumeSteps", iPropertyVolumeSteps));
            action.AddOutputParameter(new ParameterRelated("VolumeMilliDbPerStep", iPropertyVolumeMilliDbPerStep));
            action.AddOutputParameter(new ParameterRelated("BalanceMax", iPropertyBalanceMax));
            action.AddOutputParameter(new ParameterRelated("FadeMax", iPropertyFadeMax));
            iDelegateCharacteristics = new ActionDelegate(DoCharacteristics);
            EnableAction(action, iDelegateCharacteristics, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetVolume is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetVolume must be overridden if this is called.</remarks>
        protected void EnableActionSetVolume()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetVolume");
            action.AddInputParameter(new ParameterRelated("Value", iPropertyVolume));
            iDelegateSetVolume = new ActionDelegate(DoSetVolume);
            EnableAction(action, iDelegateSetVolume, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action VolumeInc is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// VolumeInc must be overridden if this is called.</remarks>
        protected void EnableActionVolumeInc()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("VolumeInc");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("VolumeDec");
            iDelegateVolumeDec = new ActionDelegate(DoVolumeDec);
            EnableAction(action, iDelegateVolumeDec, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Volume is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Volume must be overridden if this is called.</remarks>
        protected void EnableActionVolume()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Volume");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyVolume));
            iDelegateVolume = new ActionDelegate(DoVolume);
            EnableAction(action, iDelegateVolume, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetBalance is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetBalance must be overridden if this is called.</remarks>
        protected void EnableActionSetBalance()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetBalance");
            action.AddInputParameter(new ParameterRelated("Value", iPropertyBalance));
            iDelegateSetBalance = new ActionDelegate(DoSetBalance);
            EnableAction(action, iDelegateSetBalance, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action BalanceInc is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// BalanceInc must be overridden if this is called.</remarks>
        protected void EnableActionBalanceInc()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("BalanceInc");
            iDelegateBalanceInc = new ActionDelegate(DoBalanceInc);
            EnableAction(action, iDelegateBalanceInc, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action BalanceDec is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// BalanceDec must be overridden if this is called.</remarks>
        protected void EnableActionBalanceDec()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("BalanceDec");
            iDelegateBalanceDec = new ActionDelegate(DoBalanceDec);
            EnableAction(action, iDelegateBalanceDec, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Balance is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Balance must be overridden if this is called.</remarks>
        protected void EnableActionBalance()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Balance");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyBalance));
            iDelegateBalance = new ActionDelegate(DoBalance);
            EnableAction(action, iDelegateBalance, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetFade is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetFade must be overridden if this is called.</remarks>
        protected void EnableActionSetFade()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetFade");
            action.AddInputParameter(new ParameterRelated("Value", iPropertyFade));
            iDelegateSetFade = new ActionDelegate(DoSetFade);
            EnableAction(action, iDelegateSetFade, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action FadeInc is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// FadeInc must be overridden if this is called.</remarks>
        protected void EnableActionFadeInc()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("FadeInc");
            iDelegateFadeInc = new ActionDelegate(DoFadeInc);
            EnableAction(action, iDelegateFadeInc, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action FadeDec is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// FadeDec must be overridden if this is called.</remarks>
        protected void EnableActionFadeDec()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("FadeDec");
            iDelegateFadeDec = new ActionDelegate(DoFadeDec);
            EnableAction(action, iDelegateFadeDec, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Fade is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Fade must be overridden if this is called.</remarks>
        protected void EnableActionFade()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Fade");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyFade));
            iDelegateFade = new ActionDelegate(DoFade);
            EnableAction(action, iDelegateFade, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetMute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetMute must be overridden if this is called.</remarks>
        protected void EnableActionSetMute()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetMute");
            action.AddInputParameter(new ParameterRelated("Value", iPropertyMute));
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Mute");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyMute));
            iDelegateMute = new ActionDelegate(DoMute);
            EnableAction(action, iDelegateMute, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action VolumeLimit is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// VolumeLimit must be overridden if this is called.</remarks>
        protected void EnableActionVolumeLimit()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("VolumeLimit");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyVolumeLimit));
            iDelegateVolumeLimit = new ActionDelegate(DoVolumeLimit);
            EnableAction(action, iDelegateVolumeLimit, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Characteristics action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Characteristics action for the owning device.
        ///
        /// Must be implemented iff EnableActionCharacteristics was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aVolumeMax"></param>
        /// <param name="aVolumeUnity"></param>
        /// <param name="aVolumeSteps"></param>
        /// <param name="aVolumeMilliDbPerStep"></param>
        /// <param name="aBalanceMax"></param>
        /// <param name="aFadeMax"></param>
        protected virtual void Characteristics(IDvInvocation aInvocation, out uint aVolumeMax, out uint aVolumeUnity, out uint aVolumeSteps, out uint aVolumeMilliDbPerStep, out uint aBalanceMax, out uint aFadeMax)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void SetVolume(IDvInvocation aInvocation, uint aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// VolumeInc action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// VolumeInc action for the owning device.
        ///
        /// Must be implemented iff EnableActionVolumeInc was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void VolumeInc(IDvInvocation aInvocation)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void VolumeDec(IDvInvocation aInvocation)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void Volume(IDvInvocation aInvocation, out uint aValue)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void SetBalance(IDvInvocation aInvocation, int aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// BalanceInc action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// BalanceInc action for the owning device.
        ///
        /// Must be implemented iff EnableActionBalanceInc was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void BalanceInc(IDvInvocation aInvocation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// BalanceDec action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// BalanceDec action for the owning device.
        ///
        /// Must be implemented iff EnableActionBalanceDec was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void BalanceDec(IDvInvocation aInvocation)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void Balance(IDvInvocation aInvocation, out int aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetFade action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetFade action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetFade was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void SetFade(IDvInvocation aInvocation, int aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// FadeInc action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// FadeInc action for the owning device.
        ///
        /// Must be implemented iff EnableActionFadeInc was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void FadeInc(IDvInvocation aInvocation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// FadeDec action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// FadeDec action for the owning device.
        ///
        /// Must be implemented iff EnableActionFadeDec was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void FadeDec(IDvInvocation aInvocation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Fade action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Fade action for the owning device.
        ///
        /// Must be implemented iff EnableActionFade was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void Fade(IDvInvocation aInvocation, out int aValue)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void SetMute(IDvInvocation aInvocation, bool aValue)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void Mute(IDvInvocation aInvocation, out bool aValue)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void VolumeLimit(IDvInvocation aInvocation, out uint aValue)
        {
            throw (new ActionDisabledError());
        }

        private static int DoCharacteristics(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint volumeMax;
            uint volumeUnity;
            uint volumeSteps;
            uint volumeMilliDbPerStep;
            uint balanceMax;
            uint fadeMax;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Characteristics(invocation, out volumeMax, out volumeUnity, out volumeSteps, out volumeMilliDbPerStep, out balanceMax, out fadeMax);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("VolumeMax", volumeMax);
                invocation.WriteUint("VolumeUnity", volumeUnity);
                invocation.WriteUint("VolumeSteps", volumeSteps);
                invocation.WriteUint("VolumeMilliDbPerStep", volumeMilliDbPerStep);
                invocation.WriteUint("BalanceMax", balanceMax);
                invocation.WriteUint("FadeMax", fadeMax);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSetVolume(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadUint("Value");
                invocation.ReadEnd();
                self.SetVolume(invocation, value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoVolumeInc(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.VolumeInc(invocation);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoVolumeDec(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.VolumeDec(invocation);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoVolume(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Volume(invocation, out value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSetBalance(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int value;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadInt("Value");
                invocation.ReadEnd();
                self.SetBalance(invocation, value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoBalanceInc(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.BalanceInc(invocation);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoBalanceDec(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.BalanceDec(invocation);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoBalance(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Balance(invocation, out value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteInt("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSetFade(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int value;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadInt("Value");
                invocation.ReadEnd();
                self.SetFade(invocation, value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoFadeInc(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.FadeInc(invocation);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoFadeDec(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.FadeDec(invocation);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoFade(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Fade(invocation, out value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteInt("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSetMute(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool value;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadBool("Value");
                invocation.ReadEnd();
                self.SetMute(invocation, value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoMute(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Mute(invocation, out value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoVolumeLimit(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgVolume1 self = (DvProviderAvOpenhomeOrgVolume1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.VolumeLimit(invocation, out value);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public virtual void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderAvOpenhomeOrgVolume1()
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

