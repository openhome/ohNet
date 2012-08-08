using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
{
    public interface IDvProviderUpnpOrgDimming1 : IDisposable
    {

        /// <summary>
        /// Set the value of the LoadLevelStatus property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyLoadLevelStatus(uint aValue);

        /// <summary>
        /// Get a copy of the value of the LoadLevelStatus property
        /// </summary>
        /// <returns>Value of the LoadLevelStatus property.</param>
        uint PropertyLoadLevelStatus();

        /// <summary>
        /// Set the value of the StepDelta property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyStepDelta(uint aValue);

        /// <summary>
        /// Get a copy of the value of the StepDelta property
        /// </summary>
        /// <returns>Value of the StepDelta property.</param>
        uint PropertyStepDelta();

        /// <summary>
        /// Set the value of the RampRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyRampRate(uint aValue);

        /// <summary>
        /// Get a copy of the value of the RampRate property
        /// </summary>
        /// <returns>Value of the RampRate property.</param>
        uint PropertyRampRate();

        /// <summary>
        /// Set the value of the IsRamping property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyIsRamping(bool aValue);

        /// <summary>
        /// Get a copy of the value of the IsRamping property
        /// </summary>
        /// <returns>Value of the IsRamping property.</param>
        bool PropertyIsRamping();

        /// <summary>
        /// Set the value of the RampPaused property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyRampPaused(bool aValue);

        /// <summary>
        /// Get a copy of the value of the RampPaused property
        /// </summary>
        /// <returns>Value of the RampPaused property.</param>
        bool PropertyRampPaused();
        
    }
    /// <summary>
    /// Provider for the upnp.org:Dimming:1 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgDimming1 : DvProvider, IDisposable, IDvProviderUpnpOrgDimming1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateSetLoadLevelTarget;
        private ActionDelegate iDelegateGetLoadLevelTarget;
        private ActionDelegate iDelegateGetLoadLevelStatus;
        private ActionDelegate iDelegateSetOnEffectLevel;
        private ActionDelegate iDelegateSetOnEffect;
        private ActionDelegate iDelegateGetOnEffectParameters;
        private ActionDelegate iDelegateStepUp;
        private ActionDelegate iDelegateStepDown;
        private ActionDelegate iDelegateStartRampUp;
        private ActionDelegate iDelegateStartRampDown;
        private ActionDelegate iDelegateStopRamp;
        private ActionDelegate iDelegateStartRampToLevel;
        private ActionDelegate iDelegateSetStepDelta;
        private ActionDelegate iDelegateGetStepDelta;
        private ActionDelegate iDelegateSetRampRate;
        private ActionDelegate iDelegateGetRampRate;
        private ActionDelegate iDelegatePauseRamp;
        private ActionDelegate iDelegateResumeRamp;
        private ActionDelegate iDelegateGetIsRamping;
        private ActionDelegate iDelegateGetRampPaused;
        private ActionDelegate iDelegateGetRampTime;
        private PropertyUint iPropertyLoadLevelStatus;
        private PropertyUint iPropertyStepDelta;
        private PropertyUint iPropertyRampRate;
        private PropertyBool iPropertyIsRamping;
        private PropertyBool iPropertyRampPaused;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgDimming1(DvDevice aDevice)
            : base(aDevice, "upnp.org", "Dimming", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Enable the LoadLevelStatus property.
        /// </summary>
        public void EnablePropertyLoadLevelStatus()
        {
            iPropertyLoadLevelStatus = new PropertyUint(new ParameterUint("LoadLevelStatus", 0, 100));
            AddProperty(iPropertyLoadLevelStatus);
        }

        /// <summary>
        /// Enable the StepDelta property.
        /// </summary>
        public void EnablePropertyStepDelta()
        {
            iPropertyStepDelta = new PropertyUint(new ParameterUint("StepDelta", 1, 100));
            AddProperty(iPropertyStepDelta);
        }

        /// <summary>
        /// Enable the RampRate property.
        /// </summary>
        public void EnablePropertyRampRate()
        {
            iPropertyRampRate = new PropertyUint(new ParameterUint("RampRate", 0, 100));
            AddProperty(iPropertyRampRate);
        }

        /// <summary>
        /// Enable the IsRamping property.
        /// </summary>
        public void EnablePropertyIsRamping()
        {
            iPropertyIsRamping = new PropertyBool(new ParameterBool("IsRamping"));
            AddProperty(iPropertyIsRamping);
        }

        /// <summary>
        /// Enable the RampPaused property.
        /// </summary>
        public void EnablePropertyRampPaused()
        {
            iPropertyRampPaused = new PropertyBool(new ParameterBool("RampPaused"));
            AddProperty(iPropertyRampPaused);
        }

        /// <summary>
        /// Set the value of the LoadLevelStatus property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyLoadLevelStatus has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyLoadLevelStatus(uint aValue)
        {
            if (iPropertyLoadLevelStatus == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyLoadLevelStatus, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the LoadLevelStatus property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyLoadLevelStatus has previously been called.</remarks>
        /// <returns>Value of the LoadLevelStatus property.</returns>
        public uint PropertyLoadLevelStatus()
        {
            if (iPropertyLoadLevelStatus == null)
                throw new PropertyDisabledError();
            return iPropertyLoadLevelStatus.Value();
        }

        /// <summary>
        /// Set the value of the StepDelta property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyStepDelta has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyStepDelta(uint aValue)
        {
            if (iPropertyStepDelta == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyStepDelta, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the StepDelta property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyStepDelta has previously been called.</remarks>
        /// <returns>Value of the StepDelta property.</returns>
        public uint PropertyStepDelta()
        {
            if (iPropertyStepDelta == null)
                throw new PropertyDisabledError();
            return iPropertyStepDelta.Value();
        }

        /// <summary>
        /// Set the value of the RampRate property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyRampRate has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyRampRate(uint aValue)
        {
            if (iPropertyRampRate == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyRampRate, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the RampRate property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyRampRate has previously been called.</remarks>
        /// <returns>Value of the RampRate property.</returns>
        public uint PropertyRampRate()
        {
            if (iPropertyRampRate == null)
                throw new PropertyDisabledError();
            return iPropertyRampRate.Value();
        }

        /// <summary>
        /// Set the value of the IsRamping property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyIsRamping has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyIsRamping(bool aValue)
        {
            if (iPropertyIsRamping == null)
                throw new PropertyDisabledError();
            return SetPropertyBool(iPropertyIsRamping, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the IsRamping property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyIsRamping has previously been called.</remarks>
        /// <returns>Value of the IsRamping property.</returns>
        public bool PropertyIsRamping()
        {
            if (iPropertyIsRamping == null)
                throw new PropertyDisabledError();
            return iPropertyIsRamping.Value();
        }

        /// <summary>
        /// Set the value of the RampPaused property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyRampPaused has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyRampPaused(bool aValue)
        {
            if (iPropertyRampPaused == null)
                throw new PropertyDisabledError();
            return SetPropertyBool(iPropertyRampPaused, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the RampPaused property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyRampPaused has previously been called.</remarks>
        /// <returns>Value of the RampPaused property.</returns>
        public bool PropertyRampPaused()
        {
            if (iPropertyRampPaused == null)
                throw new PropertyDisabledError();
            return iPropertyRampPaused.Value();
        }

        /// <summary>
        /// Signal that the action SetLoadLevelTarget is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetLoadLevelTarget must be overridden if this is called.</remarks>
        protected void EnableActionSetLoadLevelTarget()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetLoadLevelTarget");
            action.AddInputParameter(new ParameterUint("newLoadlevelTarget", 0, 100));
            iDelegateSetLoadLevelTarget = new ActionDelegate(DoSetLoadLevelTarget);
            EnableAction(action, iDelegateSetLoadLevelTarget, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetLoadLevelTarget is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetLoadLevelTarget must be overridden if this is called.</remarks>
        protected void EnableActionGetLoadLevelTarget()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetLoadLevelTarget");
            action.AddOutputParameter(new ParameterUint("GetLoadlevelTarget", 0, 100));
            iDelegateGetLoadLevelTarget = new ActionDelegate(DoGetLoadLevelTarget);
            EnableAction(action, iDelegateGetLoadLevelTarget, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetLoadLevelStatus is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetLoadLevelStatus must be overridden if this is called.</remarks>
        protected void EnableActionGetLoadLevelStatus()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetLoadLevelStatus");
            action.AddOutputParameter(new ParameterRelated("retLoadlevelStatus", iPropertyLoadLevelStatus));
            iDelegateGetLoadLevelStatus = new ActionDelegate(DoGetLoadLevelStatus);
            EnableAction(action, iDelegateGetLoadLevelStatus, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetOnEffectLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetOnEffectLevel must be overridden if this is called.</remarks>
        protected void EnableActionSetOnEffectLevel()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetOnEffectLevel");
            action.AddInputParameter(new ParameterUint("newOnEffectLevel", 0, 100));
            iDelegateSetOnEffectLevel = new ActionDelegate(DoSetOnEffectLevel);
            EnableAction(action, iDelegateSetOnEffectLevel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetOnEffect is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetOnEffect must be overridden if this is called.</remarks>
        protected void EnableActionSetOnEffect()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetOnEffect");
            List<String> allowedValues = new List<String>();
            allowedValues.Add("OnEffectLevel");
            allowedValues.Add("LastSetting");
            allowedValues.Add("Default");
            action.AddInputParameter(new ParameterString("newOnEffect", allowedValues));
            allowedValues.Clear();
            iDelegateSetOnEffect = new ActionDelegate(DoSetOnEffect);
            EnableAction(action, iDelegateSetOnEffect, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetOnEffectParameters is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetOnEffectParameters must be overridden if this is called.</remarks>
        protected void EnableActionGetOnEffectParameters()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetOnEffectParameters");
            List<String> allowedValues = new List<String>();
            allowedValues.Add("OnEffectLevel");
            allowedValues.Add("LastSetting");
            allowedValues.Add("Default");
            action.AddOutputParameter(new ParameterString("retOnEffect", allowedValues));
            allowedValues.Clear();
            action.AddOutputParameter(new ParameterUint("retOnEffectLevel", 0, 100));
            iDelegateGetOnEffectParameters = new ActionDelegate(DoGetOnEffectParameters);
            EnableAction(action, iDelegateGetOnEffectParameters, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action StepUp is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// StepUp must be overridden if this is called.</remarks>
        protected void EnableActionStepUp()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("StepUp");
            iDelegateStepUp = new ActionDelegate(DoStepUp);
            EnableAction(action, iDelegateStepUp, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action StepDown is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// StepDown must be overridden if this is called.</remarks>
        protected void EnableActionStepDown()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("StepDown");
            iDelegateStepDown = new ActionDelegate(DoStepDown);
            EnableAction(action, iDelegateStepDown, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action StartRampUp is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// StartRampUp must be overridden if this is called.</remarks>
        protected void EnableActionStartRampUp()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("StartRampUp");
            iDelegateStartRampUp = new ActionDelegate(DoStartRampUp);
            EnableAction(action, iDelegateStartRampUp, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action StartRampDown is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// StartRampDown must be overridden if this is called.</remarks>
        protected void EnableActionStartRampDown()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("StartRampDown");
            iDelegateStartRampDown = new ActionDelegate(DoStartRampDown);
            EnableAction(action, iDelegateStartRampDown, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action StopRamp is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// StopRamp must be overridden if this is called.</remarks>
        protected void EnableActionStopRamp()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("StopRamp");
            iDelegateStopRamp = new ActionDelegate(DoStopRamp);
            EnableAction(action, iDelegateStopRamp, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action StartRampToLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// StartRampToLevel must be overridden if this is called.</remarks>
        protected void EnableActionStartRampToLevel()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("StartRampToLevel");
            action.AddInputParameter(new ParameterUint("newLoadLevelTarget", 0, 100));
            action.AddInputParameter(new ParameterUint("newRampTime"));
            iDelegateStartRampToLevel = new ActionDelegate(DoStartRampToLevel);
            EnableAction(action, iDelegateStartRampToLevel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetStepDelta is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetStepDelta must be overridden if this is called.</remarks>
        protected void EnableActionSetStepDelta()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetStepDelta");
            action.AddInputParameter(new ParameterRelated("newStepDelta", iPropertyStepDelta));
            iDelegateSetStepDelta = new ActionDelegate(DoSetStepDelta);
            EnableAction(action, iDelegateSetStepDelta, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetStepDelta is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetStepDelta must be overridden if this is called.</remarks>
        protected void EnableActionGetStepDelta()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetStepDelta");
            action.AddOutputParameter(new ParameterRelated("retStepDelta", iPropertyStepDelta));
            iDelegateGetStepDelta = new ActionDelegate(DoGetStepDelta);
            EnableAction(action, iDelegateGetStepDelta, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetRampRate is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetRampRate must be overridden if this is called.</remarks>
        protected void EnableActionSetRampRate()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetRampRate");
            action.AddInputParameter(new ParameterRelated("newRampRate", iPropertyRampRate));
            iDelegateSetRampRate = new ActionDelegate(DoSetRampRate);
            EnableAction(action, iDelegateSetRampRate, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetRampRate is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetRampRate must be overridden if this is called.</remarks>
        protected void EnableActionGetRampRate()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetRampRate");
            action.AddOutputParameter(new ParameterRelated("retRampRate", iPropertyRampRate));
            iDelegateGetRampRate = new ActionDelegate(DoGetRampRate);
            EnableAction(action, iDelegateGetRampRate, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PauseRamp is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// PauseRamp must be overridden if this is called.</remarks>
        protected void EnableActionPauseRamp()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("PauseRamp");
            iDelegatePauseRamp = new ActionDelegate(DoPauseRamp);
            EnableAction(action, iDelegatePauseRamp, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ResumeRamp is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// ResumeRamp must be overridden if this is called.</remarks>
        protected void EnableActionResumeRamp()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("ResumeRamp");
            iDelegateResumeRamp = new ActionDelegate(DoResumeRamp);
            EnableAction(action, iDelegateResumeRamp, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetIsRamping is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetIsRamping must be overridden if this is called.</remarks>
        protected void EnableActionGetIsRamping()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetIsRamping");
            action.AddOutputParameter(new ParameterRelated("retIsRamping", iPropertyIsRamping));
            iDelegateGetIsRamping = new ActionDelegate(DoGetIsRamping);
            EnableAction(action, iDelegateGetIsRamping, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetRampPaused is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetRampPaused must be overridden if this is called.</remarks>
        protected void EnableActionGetRampPaused()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetRampPaused");
            action.AddOutputParameter(new ParameterRelated("retRampPaused", iPropertyRampPaused));
            iDelegateGetRampPaused = new ActionDelegate(DoGetRampPaused);
            EnableAction(action, iDelegateGetRampPaused, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetRampTime is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetRampTime must be overridden if this is called.</remarks>
        protected void EnableActionGetRampTime()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetRampTime");
            action.AddOutputParameter(new ParameterUint("retRampTime"));
            iDelegateGetRampTime = new ActionDelegate(DoGetRampTime);
            EnableAction(action, iDelegateGetRampTime, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// SetLoadLevelTarget action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetLoadLevelTarget action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetLoadLevelTarget was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="anewLoadlevelTarget"></param>
        protected virtual void SetLoadLevelTarget(IDvInvocation aInvocation, uint anewLoadlevelTarget)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetLoadLevelTarget action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetLoadLevelTarget action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetLoadLevelTarget was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aGetLoadlevelTarget"></param>
        protected virtual void GetLoadLevelTarget(IDvInvocation aInvocation, out uint aGetLoadlevelTarget)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetLoadLevelStatus action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetLoadLevelStatus action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetLoadLevelStatus was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aretLoadlevelStatus"></param>
        protected virtual void GetLoadLevelStatus(IDvInvocation aInvocation, out uint aretLoadlevelStatus)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetOnEffectLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetOnEffectLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetOnEffectLevel was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="anewOnEffectLevel"></param>
        protected virtual void SetOnEffectLevel(IDvInvocation aInvocation, uint anewOnEffectLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetOnEffect action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetOnEffect action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetOnEffect was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="anewOnEffect"></param>
        protected virtual void SetOnEffect(IDvInvocation aInvocation, string anewOnEffect)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetOnEffectParameters action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetOnEffectParameters action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetOnEffectParameters was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aretOnEffect"></param>
        /// <param name="aretOnEffectLevel"></param>
        protected virtual void GetOnEffectParameters(IDvInvocation aInvocation, out string aretOnEffect, out uint aretOnEffectLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StepUp action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StepUp action for the owning device.
        ///
        /// Must be implemented iff EnableActionStepUp was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void StepUp(IDvInvocation aInvocation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StepDown action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StepDown action for the owning device.
        ///
        /// Must be implemented iff EnableActionStepDown was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void StepDown(IDvInvocation aInvocation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StartRampUp action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StartRampUp action for the owning device.
        ///
        /// Must be implemented iff EnableActionStartRampUp was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void StartRampUp(IDvInvocation aInvocation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StartRampDown action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StartRampDown action for the owning device.
        ///
        /// Must be implemented iff EnableActionStartRampDown was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void StartRampDown(IDvInvocation aInvocation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StopRamp action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StopRamp action for the owning device.
        ///
        /// Must be implemented iff EnableActionStopRamp was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void StopRamp(IDvInvocation aInvocation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StartRampToLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StartRampToLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionStartRampToLevel was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="anewLoadLevelTarget"></param>
        /// <param name="anewRampTime"></param>
        protected virtual void StartRampToLevel(IDvInvocation aInvocation, uint anewLoadLevelTarget, uint anewRampTime)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStepDelta action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStepDelta action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStepDelta was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="anewStepDelta"></param>
        protected virtual void SetStepDelta(IDvInvocation aInvocation, uint anewStepDelta)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetStepDelta action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetStepDelta action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetStepDelta was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aretStepDelta"></param>
        protected virtual void GetStepDelta(IDvInvocation aInvocation, out uint aretStepDelta)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetRampRate action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetRampRate action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetRampRate was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="anewRampRate"></param>
        protected virtual void SetRampRate(IDvInvocation aInvocation, uint anewRampRate)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetRampRate action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetRampRate action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetRampRate was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aretRampRate"></param>
        protected virtual void GetRampRate(IDvInvocation aInvocation, out uint aretRampRate)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PauseRamp action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PauseRamp action for the owning device.
        ///
        /// Must be implemented iff EnableActionPauseRamp was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void PauseRamp(IDvInvocation aInvocation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ResumeRamp action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ResumeRamp action for the owning device.
        ///
        /// Must be implemented iff EnableActionResumeRamp was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void ResumeRamp(IDvInvocation aInvocation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetIsRamping action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetIsRamping action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetIsRamping was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aretIsRamping"></param>
        protected virtual void GetIsRamping(IDvInvocation aInvocation, out bool aretIsRamping)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetRampPaused action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetRampPaused action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetRampPaused was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aretRampPaused"></param>
        protected virtual void GetRampPaused(IDvInvocation aInvocation, out bool aretRampPaused)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetRampTime action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetRampTime action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetRampTime was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aretRampTime"></param>
        protected virtual void GetRampTime(IDvInvocation aInvocation, out uint aretRampTime)
        {
            throw (new ActionDisabledError());
        }

        private static int DoSetLoadLevelTarget(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint newLoadlevelTarget;
            try
            {
                invocation.ReadStart();
                newLoadlevelTarget = invocation.ReadUint("newLoadlevelTarget");
                invocation.ReadEnd();
                self.SetLoadLevelTarget(invocation, newLoadlevelTarget);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetLoadLevelTarget");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SetLoadLevelTarget"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetLoadLevelTarget", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetLoadLevelTarget", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetLoadLevelTarget(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint getLoadlevelTarget;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetLoadLevelTarget(invocation, out getLoadlevelTarget);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetLoadLevelTarget");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetLoadLevelTarget"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetLoadLevelTarget", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("GetLoadlevelTarget", getLoadlevelTarget);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetLoadLevelTarget", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetLoadLevelStatus(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint retLoadlevelStatus;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetLoadLevelStatus(invocation, out retLoadlevelStatus);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetLoadLevelStatus");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetLoadLevelStatus"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetLoadLevelStatus", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("retLoadlevelStatus", retLoadlevelStatus);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetLoadLevelStatus", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetOnEffectLevel(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint newOnEffectLevel;
            try
            {
                invocation.ReadStart();
                newOnEffectLevel = invocation.ReadUint("newOnEffectLevel");
                invocation.ReadEnd();
                self.SetOnEffectLevel(invocation, newOnEffectLevel);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetOnEffectLevel");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SetOnEffectLevel"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetOnEffectLevel", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetOnEffectLevel", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetOnEffect(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string newOnEffect;
            try
            {
                invocation.ReadStart();
                newOnEffect = invocation.ReadString("newOnEffect");
                invocation.ReadEnd();
                self.SetOnEffect(invocation, newOnEffect);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetOnEffect");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SetOnEffect"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetOnEffect", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetOnEffect", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetOnEffectParameters(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string retOnEffect;
            uint retOnEffectLevel;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetOnEffectParameters(invocation, out retOnEffect, out retOnEffectLevel);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetOnEffectParameters");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetOnEffectParameters"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetOnEffectParameters", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("retOnEffect", retOnEffect);
                invocation.WriteUint("retOnEffectLevel", retOnEffectLevel);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetOnEffectParameters", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoStepUp(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.StepUp(invocation);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "StepUp");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "StepUp"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "StepUp", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "StepUp", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoStepDown(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.StepDown(invocation);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "StepDown");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "StepDown"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "StepDown", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "StepDown", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoStartRampUp(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.StartRampUp(invocation);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "StartRampUp");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "StartRampUp"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "StartRampUp", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "StartRampUp", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoStartRampDown(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.StartRampDown(invocation);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "StartRampDown");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "StartRampDown"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "StartRampDown", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "StartRampDown", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoStopRamp(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.StopRamp(invocation);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "StopRamp");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "StopRamp"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "StopRamp", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "StopRamp", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoStartRampToLevel(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint newLoadLevelTarget;
            uint newRampTime;
            try
            {
                invocation.ReadStart();
                newLoadLevelTarget = invocation.ReadUint("newLoadLevelTarget");
                newRampTime = invocation.ReadUint("newRampTime");
                invocation.ReadEnd();
                self.StartRampToLevel(invocation, newLoadLevelTarget, newRampTime);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "StartRampToLevel");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "StartRampToLevel"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "StartRampToLevel", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "StartRampToLevel", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetStepDelta(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint newStepDelta;
            try
            {
                invocation.ReadStart();
                newStepDelta = invocation.ReadUint("newStepDelta");
                invocation.ReadEnd();
                self.SetStepDelta(invocation, newStepDelta);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetStepDelta");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SetStepDelta"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetStepDelta", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetStepDelta", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetStepDelta(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint retStepDelta;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetStepDelta(invocation, out retStepDelta);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetStepDelta");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetStepDelta"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetStepDelta", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("retStepDelta", retStepDelta);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetStepDelta", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetRampRate(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint newRampRate;
            try
            {
                invocation.ReadStart();
                newRampRate = invocation.ReadUint("newRampRate");
                invocation.ReadEnd();
                self.SetRampRate(invocation, newRampRate);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetRampRate");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "SetRampRate"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetRampRate", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "SetRampRate", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetRampRate(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint retRampRate;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetRampRate(invocation, out retRampRate);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetRampRate");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetRampRate"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetRampRate", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("retRampRate", retRampRate);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetRampRate", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoPauseRamp(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.PauseRamp(invocation);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "PauseRamp");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "PauseRamp"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PauseRamp", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "PauseRamp", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoResumeRamp(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ResumeRamp(invocation);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "ResumeRamp");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "ResumeRamp"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ResumeRamp", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ResumeRamp", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetIsRamping(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool retIsRamping;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetIsRamping(invocation, out retIsRamping);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetIsRamping");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetIsRamping"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetIsRamping", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("retIsRamping", retIsRamping);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetIsRamping", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetRampPaused(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool retRampPaused;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetRampPaused(invocation, out retRampPaused);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetRampPaused");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetRampPaused"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetRampPaused", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("retRampPaused", retRampPaused);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetRampPaused", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetRampTime(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint retRampTime;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetRampTime(invocation, out retRampTime);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetRampTime");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetRampTime"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetRampTime", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("retRampTime", retRampTime);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetRampTime", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public virtual void Dispose()
        {
            if (DisposeProvider())
                iGch.Free();
        }
    }
}

