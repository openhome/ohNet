using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    /// <summary>
    /// Provider for the upnp.org:Dimming:1 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgDimming1 : DvProvider, IDisposable
    {
        [DllImport("DvUpnpOrgDimming1")]
        static extern uint DvProviderUpnpOrgDimming1Create(uint aDeviceHandle);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1Destroy(uint aHandle);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe int DvProviderUpnpOrgDimming1SetPropertyLoadLevelStatus(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe void DvProviderUpnpOrgDimming1GetPropertyLoadLevelStatus(uint aHandle, uint* aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe int DvProviderUpnpOrgDimming1SetPropertyStepDelta(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe void DvProviderUpnpOrgDimming1GetPropertyStepDelta(uint aHandle, uint* aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe int DvProviderUpnpOrgDimming1SetPropertyRampRate(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe void DvProviderUpnpOrgDimming1GetPropertyRampRate(uint aHandle, uint* aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe int DvProviderUpnpOrgDimming1SetPropertyIsRamping(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe void DvProviderUpnpOrgDimming1GetPropertyIsRamping(uint aHandle, int* aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe int DvProviderUpnpOrgDimming1SetPropertyRampPaused(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe void DvProviderUpnpOrgDimming1GetPropertyRampPaused(uint aHandle, int* aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionSetLoadLevelTarget(uint aHandle, CallbackSetLoadLevelTarget aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionGetLoadLevelTarget(uint aHandle, CallbackGetLoadLevelTarget aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionGetLoadLevelStatus(uint aHandle, CallbackGetLoadLevelStatus aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionSetOnEffectLevel(uint aHandle, CallbackSetOnEffectLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionSetOnEffect(uint aHandle, CallbackSetOnEffect aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionGetOnEffectParameters(uint aHandle, CallbackGetOnEffectParameters aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionStepUp(uint aHandle, CallbackStepUp aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionStepDown(uint aHandle, CallbackStepDown aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionStartRampUp(uint aHandle, CallbackStartRampUp aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionStartRampDown(uint aHandle, CallbackStartRampDown aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionStopRamp(uint aHandle, CallbackStopRamp aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionStartRampToLevel(uint aHandle, CallbackStartRampToLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionSetStepDelta(uint aHandle, CallbackSetStepDelta aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionGetStepDelta(uint aHandle, CallbackGetStepDelta aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionSetRampRate(uint aHandle, CallbackSetRampRate aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionGetRampRate(uint aHandle, CallbackGetRampRate aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionPauseRamp(uint aHandle, CallbackPauseRamp aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionResumeRamp(uint aHandle, CallbackResumeRamp aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionGetIsRamping(uint aHandle, CallbackGetIsRamping aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionGetRampPaused(uint aHandle, CallbackGetRampPaused aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvProviderUpnpOrgDimming1EnableActionGetRampTime(uint aHandle, CallbackGetRampTime aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackSetLoadLevelTarget(IntPtr aPtr, uint aVersion, uint anewLoadlevelTarget);
        private unsafe delegate int CallbackGetLoadLevelTarget(IntPtr aPtr, uint aVersion, uint* aGetLoadlevelTarget);
        private unsafe delegate int CallbackGetLoadLevelStatus(IntPtr aPtr, uint aVersion, uint* aretLoadlevelStatus);
        private unsafe delegate int CallbackSetOnEffectLevel(IntPtr aPtr, uint aVersion, uint anewOnEffectLevel);
        private unsafe delegate int CallbackSetOnEffect(IntPtr aPtr, uint aVersion, char* anewOnEffect);
        private unsafe delegate int CallbackGetOnEffectParameters(IntPtr aPtr, uint aVersion, char** aretOnEffect, uint* aretOnEffectLevel);
        private unsafe delegate int CallbackStepUp(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackStepDown(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackStartRampUp(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackStartRampDown(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackStopRamp(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackStartRampToLevel(IntPtr aPtr, uint aVersion, uint anewLoadLevelTarget, uint anewRampTime);
        private unsafe delegate int CallbackSetStepDelta(IntPtr aPtr, uint aVersion, uint anewStepDelta);
        private unsafe delegate int CallbackGetStepDelta(IntPtr aPtr, uint aVersion, uint* aretStepDelta);
        private unsafe delegate int CallbackSetRampRate(IntPtr aPtr, uint aVersion, uint anewRampRate);
        private unsafe delegate int CallbackGetRampRate(IntPtr aPtr, uint aVersion, uint* aretRampRate);
        private unsafe delegate int CallbackPauseRamp(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackResumeRamp(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackGetIsRamping(IntPtr aPtr, uint aVersion, int* aretIsRamping);
        private unsafe delegate int CallbackGetRampPaused(IntPtr aPtr, uint aVersion, int* aretRampPaused);
        private unsafe delegate int CallbackGetRampTime(IntPtr aPtr, uint aVersion, uint* aretRampTime);

        private GCHandle iGch;
        private CallbackSetLoadLevelTarget iCallbackSetLoadLevelTarget;
        private CallbackGetLoadLevelTarget iCallbackGetLoadLevelTarget;
        private CallbackGetLoadLevelStatus iCallbackGetLoadLevelStatus;
        private CallbackSetOnEffectLevel iCallbackSetOnEffectLevel;
        private CallbackSetOnEffect iCallbackSetOnEffect;
        private CallbackGetOnEffectParameters iCallbackGetOnEffectParameters;
        private CallbackStepUp iCallbackStepUp;
        private CallbackStepDown iCallbackStepDown;
        private CallbackStartRampUp iCallbackStartRampUp;
        private CallbackStartRampDown iCallbackStartRampDown;
        private CallbackStopRamp iCallbackStopRamp;
        private CallbackStartRampToLevel iCallbackStartRampToLevel;
        private CallbackSetStepDelta iCallbackSetStepDelta;
        private CallbackGetStepDelta iCallbackGetStepDelta;
        private CallbackSetRampRate iCallbackSetRampRate;
        private CallbackGetRampRate iCallbackGetRampRate;
        private CallbackPauseRamp iCallbackPauseRamp;
        private CallbackResumeRamp iCallbackResumeRamp;
        private CallbackGetIsRamping iCallbackGetIsRamping;
        private CallbackGetRampPaused iCallbackGetRampPaused;
        private CallbackGetRampTime iCallbackGetRampTime;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgDimming1(DvDevice aDevice)
        {
            iHandle = DvProviderUpnpOrgDimming1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the LoadLevelStatus property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyLoadLevelStatus(uint aValue)
        {
            uint changed;
            if (0 != DvProviderUpnpOrgDimming1SetPropertyLoadLevelStatus(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the LoadLevelStatus property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyLoadLevelStatus(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderUpnpOrgDimming1GetPropertyLoadLevelStatus(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the StepDelta property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyStepDelta(uint aValue)
        {
            uint changed;
            if (0 != DvProviderUpnpOrgDimming1SetPropertyStepDelta(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the StepDelta property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyStepDelta(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderUpnpOrgDimming1GetPropertyStepDelta(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the RampRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyRampRate(uint aValue)
        {
            uint changed;
            if (0 != DvProviderUpnpOrgDimming1SetPropertyRampRate(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the RampRate property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyRampRate(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderUpnpOrgDimming1GetPropertyRampRate(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the IsRamping property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyIsRamping(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderUpnpOrgDimming1SetPropertyIsRamping(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the IsRamping property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyIsRamping(out bool aValue)
        {
            int value;
            DvProviderUpnpOrgDimming1GetPropertyIsRamping(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the RampPaused property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyRampPaused(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderUpnpOrgDimming1SetPropertyRampPaused(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the RampPaused property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyRampPaused(out bool aValue)
        {
            int value;
            DvProviderUpnpOrgDimming1GetPropertyRampPaused(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Signal that the action SetLoadLevelTarget is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetLoadLevelTarget must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetLoadLevelTarget()
        {
            iCallbackSetLoadLevelTarget = new CallbackSetLoadLevelTarget(DoSetLoadLevelTarget);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionSetLoadLevelTarget(iHandle, iCallbackSetLoadLevelTarget, ptr);
        }

        /// <summary>
        /// Signal that the action GetLoadLevelTarget is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetLoadLevelTarget must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetLoadLevelTarget()
        {
            iCallbackGetLoadLevelTarget = new CallbackGetLoadLevelTarget(DoGetLoadLevelTarget);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionGetLoadLevelTarget(iHandle, iCallbackGetLoadLevelTarget, ptr);
        }

        /// <summary>
        /// Signal that the action GetLoadLevelStatus is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetLoadLevelStatus must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetLoadLevelStatus()
        {
            iCallbackGetLoadLevelStatus = new CallbackGetLoadLevelStatus(DoGetLoadLevelStatus);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionGetLoadLevelStatus(iHandle, iCallbackGetLoadLevelStatus, ptr);
        }

        /// <summary>
        /// Signal that the action SetOnEffectLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetOnEffectLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetOnEffectLevel()
        {
            iCallbackSetOnEffectLevel = new CallbackSetOnEffectLevel(DoSetOnEffectLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionSetOnEffectLevel(iHandle, iCallbackSetOnEffectLevel, ptr);
        }

        /// <summary>
        /// Signal that the action SetOnEffect is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetOnEffect must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetOnEffect()
        {
            iCallbackSetOnEffect = new CallbackSetOnEffect(DoSetOnEffect);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionSetOnEffect(iHandle, iCallbackSetOnEffect, ptr);
        }

        /// <summary>
        /// Signal that the action GetOnEffectParameters is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetOnEffectParameters must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetOnEffectParameters()
        {
            iCallbackGetOnEffectParameters = new CallbackGetOnEffectParameters(DoGetOnEffectParameters);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionGetOnEffectParameters(iHandle, iCallbackGetOnEffectParameters, ptr);
        }

        /// <summary>
        /// Signal that the action StepUp is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStepUp must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStepUp()
        {
            iCallbackStepUp = new CallbackStepUp(DoStepUp);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionStepUp(iHandle, iCallbackStepUp, ptr);
        }

        /// <summary>
        /// Signal that the action StepDown is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStepDown must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStepDown()
        {
            iCallbackStepDown = new CallbackStepDown(DoStepDown);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionStepDown(iHandle, iCallbackStepDown, ptr);
        }

        /// <summary>
        /// Signal that the action StartRampUp is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStartRampUp must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStartRampUp()
        {
            iCallbackStartRampUp = new CallbackStartRampUp(DoStartRampUp);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionStartRampUp(iHandle, iCallbackStartRampUp, ptr);
        }

        /// <summary>
        /// Signal that the action StartRampDown is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStartRampDown must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStartRampDown()
        {
            iCallbackStartRampDown = new CallbackStartRampDown(DoStartRampDown);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionStartRampDown(iHandle, iCallbackStartRampDown, ptr);
        }

        /// <summary>
        /// Signal that the action StopRamp is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStopRamp must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStopRamp()
        {
            iCallbackStopRamp = new CallbackStopRamp(DoStopRamp);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionStopRamp(iHandle, iCallbackStopRamp, ptr);
        }

        /// <summary>
        /// Signal that the action StartRampToLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStartRampToLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStartRampToLevel()
        {
            iCallbackStartRampToLevel = new CallbackStartRampToLevel(DoStartRampToLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionStartRampToLevel(iHandle, iCallbackStartRampToLevel, ptr);
        }

        /// <summary>
        /// Signal that the action SetStepDelta is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStepDelta must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStepDelta()
        {
            iCallbackSetStepDelta = new CallbackSetStepDelta(DoSetStepDelta);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionSetStepDelta(iHandle, iCallbackSetStepDelta, ptr);
        }

        /// <summary>
        /// Signal that the action GetStepDelta is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetStepDelta must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetStepDelta()
        {
            iCallbackGetStepDelta = new CallbackGetStepDelta(DoGetStepDelta);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionGetStepDelta(iHandle, iCallbackGetStepDelta, ptr);
        }

        /// <summary>
        /// Signal that the action SetRampRate is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetRampRate must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetRampRate()
        {
            iCallbackSetRampRate = new CallbackSetRampRate(DoSetRampRate);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionSetRampRate(iHandle, iCallbackSetRampRate, ptr);
        }

        /// <summary>
        /// Signal that the action GetRampRate is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRampRate must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRampRate()
        {
            iCallbackGetRampRate = new CallbackGetRampRate(DoGetRampRate);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionGetRampRate(iHandle, iCallbackGetRampRate, ptr);
        }

        /// <summary>
        /// Signal that the action PauseRamp is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPauseRamp must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPauseRamp()
        {
            iCallbackPauseRamp = new CallbackPauseRamp(DoPauseRamp);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionPauseRamp(iHandle, iCallbackPauseRamp, ptr);
        }

        /// <summary>
        /// Signal that the action ResumeRamp is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoResumeRamp must be overridden if this is called.</remarks>
        protected unsafe void EnableActionResumeRamp()
        {
            iCallbackResumeRamp = new CallbackResumeRamp(DoResumeRamp);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionResumeRamp(iHandle, iCallbackResumeRamp, ptr);
        }

        /// <summary>
        /// Signal that the action GetIsRamping is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetIsRamping must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetIsRamping()
        {
            iCallbackGetIsRamping = new CallbackGetIsRamping(DoGetIsRamping);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionGetIsRamping(iHandle, iCallbackGetIsRamping, ptr);
        }

        /// <summary>
        /// Signal that the action GetRampPaused is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRampPaused must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRampPaused()
        {
            iCallbackGetRampPaused = new CallbackGetRampPaused(DoGetRampPaused);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionGetRampPaused(iHandle, iCallbackGetRampPaused, ptr);
        }

        /// <summary>
        /// Signal that the action GetRampTime is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRampTime must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRampTime()
        {
            iCallbackGetRampTime = new CallbackGetRampTime(DoGetRampTime);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgDimming1EnableActionGetRampTime(iHandle, iCallbackGetRampTime, ptr);
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

        private static unsafe int DoSetLoadLevelTarget(IntPtr aPtr, uint aVersion, uint anewLoadlevelTarget)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            self.SetLoadLevelTarget(aVersion, anewLoadlevelTarget);
            return 0;
        }

        private static unsafe int DoGetLoadLevelTarget(IntPtr aPtr, uint aVersion, uint* aGetLoadlevelTarget)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            uint getLoadlevelTarget;
            self.GetLoadLevelTarget(aVersion, out getLoadlevelTarget);
            *aGetLoadlevelTarget = getLoadlevelTarget;
            return 0;
        }

        private static unsafe int DoGetLoadLevelStatus(IntPtr aPtr, uint aVersion, uint* aretLoadlevelStatus)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            uint retLoadlevelStatus;
            self.GetLoadLevelStatus(aVersion, out retLoadlevelStatus);
            *aretLoadlevelStatus = retLoadlevelStatus;
            return 0;
        }

        private static unsafe int DoSetOnEffectLevel(IntPtr aPtr, uint aVersion, uint anewOnEffectLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            self.SetOnEffectLevel(aVersion, anewOnEffectLevel);
            return 0;
        }

        private static unsafe int DoSetOnEffect(IntPtr aPtr, uint aVersion, char* anewOnEffect)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            string newOnEffect = Marshal.PtrToStringAnsi((IntPtr)anewOnEffect);
            self.SetOnEffect(aVersion, newOnEffect);
            return 0;
        }

        private static unsafe int DoGetOnEffectParameters(IntPtr aPtr, uint aVersion, char** aretOnEffect, uint* aretOnEffectLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            string retOnEffect;
            uint retOnEffectLevel;
            self.GetOnEffectParameters(aVersion, out retOnEffect, out retOnEffectLevel);
            *aretOnEffect = (char*)Marshal.StringToHGlobalAnsi(retOnEffect).ToPointer();
            *aretOnEffectLevel = retOnEffectLevel;
            return 0;
        }

        private static unsafe int DoStepUp(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            self.StepUp(aVersion);
            return 0;
        }

        private static unsafe int DoStepDown(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            self.StepDown(aVersion);
            return 0;
        }

        private static unsafe int DoStartRampUp(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            self.StartRampUp(aVersion);
            return 0;
        }

        private static unsafe int DoStartRampDown(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            self.StartRampDown(aVersion);
            return 0;
        }

        private static unsafe int DoStopRamp(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            self.StopRamp(aVersion);
            return 0;
        }

        private static unsafe int DoStartRampToLevel(IntPtr aPtr, uint aVersion, uint anewLoadLevelTarget, uint anewRampTime)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            self.StartRampToLevel(aVersion, anewLoadLevelTarget, anewRampTime);
            return 0;
        }

        private static unsafe int DoSetStepDelta(IntPtr aPtr, uint aVersion, uint anewStepDelta)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            self.SetStepDelta(aVersion, anewStepDelta);
            return 0;
        }

        private static unsafe int DoGetStepDelta(IntPtr aPtr, uint aVersion, uint* aretStepDelta)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            uint retStepDelta;
            self.GetStepDelta(aVersion, out retStepDelta);
            *aretStepDelta = retStepDelta;
            return 0;
        }

        private static unsafe int DoSetRampRate(IntPtr aPtr, uint aVersion, uint anewRampRate)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            self.SetRampRate(aVersion, anewRampRate);
            return 0;
        }

        private static unsafe int DoGetRampRate(IntPtr aPtr, uint aVersion, uint* aretRampRate)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            uint retRampRate;
            self.GetRampRate(aVersion, out retRampRate);
            *aretRampRate = retRampRate;
            return 0;
        }

        private static unsafe int DoPauseRamp(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            self.PauseRamp(aVersion);
            return 0;
        }

        private static unsafe int DoResumeRamp(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            self.ResumeRamp(aVersion);
            return 0;
        }

        private static unsafe int DoGetIsRamping(IntPtr aPtr, uint aVersion, int* aretIsRamping)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            bool retIsRamping;
            self.GetIsRamping(aVersion, out retIsRamping);
            *aretIsRamping = (retIsRamping ? 1 : 0);
            return 0;
        }

        private static unsafe int DoGetRampPaused(IntPtr aPtr, uint aVersion, int* aretRampPaused)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            bool retRampPaused;
            self.GetRampPaused(aVersion, out retRampPaused);
            *aretRampPaused = (retRampPaused ? 1 : 0);
            return 0;
        }

        private static unsafe int DoGetRampTime(IntPtr aPtr, uint aVersion, uint* aretRampTime)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgDimming1 self = (DvProviderUpnpOrgDimming1)gch.Target;
            uint retRampTime;
            self.GetRampTime(aVersion, out retRampTime);
            *aretRampTime = retRampTime;
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
            uint handle;
            lock (this)
            {
                if (iHandle == 0)
                {
                    return;
                }
                handle = iHandle;
                iHandle = 0;
            }
            DvProviderUpnpOrgDimming1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

