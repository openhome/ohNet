using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
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
        /// <param name="aValue">Property's value will be copied here</param>
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
        /// <param name="aValue">Property's value will be copied here</param>
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
        /// <param name="aValue">Property's value will be copied here</param>
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
        /// <param name="aValue">Property's value will be copied here</param>
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
        /// <param name="aValue">Property's value will be copied here</param>
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
            iPropertyLoadLevelStatus = new PropertyUint(new ParameterUint("LoadLevelStatus", 0, 100));
            AddProperty(iPropertyLoadLevelStatus);
            iPropertyStepDelta = new PropertyUint(new ParameterUint("StepDelta", 1, 100));
            AddProperty(iPropertyStepDelta);
            iPropertyRampRate = new PropertyUint(new ParameterUint("RampRate", 0, 100));
            AddProperty(iPropertyRampRate);
            iPropertyIsRamping = new PropertyBool(new ParameterBool("IsRamping"));
            AddProperty(iPropertyIsRamping);
            iPropertyRampPaused = new PropertyBool(new ParameterBool("RampPaused"));
            AddProperty(iPropertyRampPaused);
        }

        /// <summary>
        /// Set the value of the LoadLevelStatus property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyLoadLevelStatus(uint aValue)
        {
            return SetPropertyUint(iPropertyLoadLevelStatus, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the LoadLevelStatus property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyLoadLevelStatus()
        {
            return iPropertyLoadLevelStatus.Value();
        }

        /// <summary>
        /// Set the value of the StepDelta property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyStepDelta(uint aValue)
        {
            return SetPropertyUint(iPropertyStepDelta, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the StepDelta property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyStepDelta()
        {
            return iPropertyStepDelta.Value();
        }

        /// <summary>
        /// Set the value of the RampRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyRampRate(uint aValue)
        {
            return SetPropertyUint(iPropertyRampRate, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the RampRate property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyRampRate()
        {
            return iPropertyRampRate.Value();
        }

        /// <summary>
        /// Set the value of the IsRamping property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyIsRamping(bool aValue)
        {
            return SetPropertyBool(iPropertyIsRamping, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the IsRamping property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyIsRamping()
        {
            return iPropertyIsRamping.Value();
        }

        /// <summary>
        /// Set the value of the RampPaused property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyRampPaused(bool aValue)
        {
            return SetPropertyBool(iPropertyRampPaused, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the RampPaused property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyRampPaused()
        {
            return iPropertyRampPaused.Value();
        }

        /// <summary>
        /// Signal that the action SetLoadLevelTarget is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetLoadLevelTarget must be overridden if this is called.</remarks>
        protected void EnableActionSetLoadLevelTarget()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetLoadLevelTarget");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetLoadLevelTarget");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetLoadLevelStatus");
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
            Zapp.Core.Action action = new Zapp.Core.Action("SetOnEffectLevel");
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
            Zapp.Core.Action action = new Zapp.Core.Action("SetOnEffect");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetOnEffectParameters");
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
            Zapp.Core.Action action = new Zapp.Core.Action("StepUp");
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
            Zapp.Core.Action action = new Zapp.Core.Action("StepDown");
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
            Zapp.Core.Action action = new Zapp.Core.Action("StartRampUp");
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
            Zapp.Core.Action action = new Zapp.Core.Action("StartRampDown");
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
            Zapp.Core.Action action = new Zapp.Core.Action("StopRamp");
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
            Zapp.Core.Action action = new Zapp.Core.Action("StartRampToLevel");
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
            Zapp.Core.Action action = new Zapp.Core.Action("SetStepDelta");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetStepDelta");
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
            Zapp.Core.Action action = new Zapp.Core.Action("SetRampRate");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetRampRate");
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
            Zapp.Core.Action action = new Zapp.Core.Action("PauseRamp");
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
            Zapp.Core.Action action = new Zapp.Core.Action("ResumeRamp");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetIsRamping");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetRampPaused");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetRampTime");
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="anewLoadlevelTarget"></param>
        protected virtual void SetLoadLevelTarget(uint aVersion, uint anewLoadlevelTarget)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aGetLoadlevelTarget"></param>
        protected virtual void GetLoadLevelTarget(uint aVersion, out uint aGetLoadlevelTarget)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aretLoadlevelStatus"></param>
        protected virtual void GetLoadLevelStatus(uint aVersion, out uint aretLoadlevelStatus)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="anewOnEffectLevel"></param>
        protected virtual void SetOnEffectLevel(uint aVersion, uint anewOnEffectLevel)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="anewOnEffect"></param>
        protected virtual void SetOnEffect(uint aVersion, string anewOnEffect)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aretOnEffect"></param>
        /// <param name="aretOnEffectLevel"></param>
        protected virtual void GetOnEffectParameters(uint aVersion, out string aretOnEffect, out uint aretOnEffectLevel)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void StepUp(uint aVersion)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void StepDown(uint aVersion)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void StartRampUp(uint aVersion)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void StartRampDown(uint aVersion)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void StopRamp(uint aVersion)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="anewLoadLevelTarget"></param>
        /// <param name="anewRampTime"></param>
        protected virtual void StartRampToLevel(uint aVersion, uint anewLoadLevelTarget, uint anewRampTime)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="anewStepDelta"></param>
        protected virtual void SetStepDelta(uint aVersion, uint anewStepDelta)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aretStepDelta"></param>
        protected virtual void GetStepDelta(uint aVersion, out uint aretStepDelta)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="anewRampRate"></param>
        protected virtual void SetRampRate(uint aVersion, uint anewRampRate)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aretRampRate"></param>
        protected virtual void GetRampRate(uint aVersion, out uint aretRampRate)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void PauseRamp(uint aVersion)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void ResumeRamp(uint aVersion)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aretIsRamping"></param>
        protected virtual void GetIsRamping(uint aVersion, out bool aretIsRamping)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aretRampPaused"></param>
        protected virtual void GetRampPaused(uint aVersion, out bool aretRampPaused)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aretRampTime"></param>
        protected virtual void GetRampTime(uint aVersion, out uint aretRampTime)
        {
            throw (new ActionDisabledError());
        }

        private static int DoSetLoadLevelTarget(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.SetLoadLevelTarget(aVersion, newLoadlevelTarget);
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

        private static int DoGetLoadLevelTarget(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint getLoadlevelTarget;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetLoadLevelTarget(aVersion, out getLoadlevelTarget);
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
                invocation.WriteUint("GetLoadlevelTarget", getLoadlevelTarget);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetLoadLevelStatus(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint retLoadlevelStatus;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetLoadLevelStatus(aVersion, out retLoadlevelStatus);
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
                invocation.WriteUint("retLoadlevelStatus", retLoadlevelStatus);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetOnEffectLevel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.SetOnEffectLevel(aVersion, newOnEffectLevel);
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

        private static int DoSetOnEffect(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.SetOnEffect(aVersion, newOnEffect);
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

        private static int DoGetOnEffectParameters(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.GetOnEffectParameters(aVersion, out retOnEffect, out retOnEffectLevel);
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
                invocation.WriteString("retOnEffect", retOnEffect);
                invocation.WriteUint("retOnEffectLevel", retOnEffectLevel);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoStepUp(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.StepUp(aVersion);
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

        private static int DoStepDown(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.StepDown(aVersion);
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

        private static int DoStartRampUp(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.StartRampUp(aVersion);
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

        private static int DoStartRampDown(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.StartRampDown(aVersion);
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

        private static int DoStopRamp(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.StopRamp(aVersion);
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

        private static int DoStartRampToLevel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.StartRampToLevel(aVersion, newLoadLevelTarget, newRampTime);
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

        private static int DoSetStepDelta(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.SetStepDelta(aVersion, newStepDelta);
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

        private static int DoGetStepDelta(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint retStepDelta;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetStepDelta(aVersion, out retStepDelta);
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
                invocation.WriteUint("retStepDelta", retStepDelta);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetRampRate(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.SetRampRate(aVersion, newRampRate);
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

        private static int DoGetRampRate(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint retRampRate;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetRampRate(aVersion, out retRampRate);
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
                invocation.WriteUint("retRampRate", retRampRate);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoPauseRamp(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.PauseRamp(aVersion);
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

        private static int DoResumeRamp(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ResumeRamp(aVersion);
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

        private static int DoGetIsRamping(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool retIsRamping;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetIsRamping(aVersion, out retIsRamping);
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
                invocation.WriteBool("retIsRamping", retIsRamping);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetRampPaused(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool retRampPaused;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetRampPaused(aVersion, out retRampPaused);
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
                invocation.WriteBool("retRampPaused", retRampPaused);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetRampTime(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint retRampTime;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetRampTime(aVersion, out retRampTime);
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
                invocation.WriteUint("retRampTime", retRampTime);
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

        ~DvProviderUpnpOrgDimming1()
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

