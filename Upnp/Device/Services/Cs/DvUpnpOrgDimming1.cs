using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceUpnpOrgDimming1 : IDisposable
    {
        [DllImport("DvUpnpOrgDimming1")]
        static extern uint DvServiceUpnpOrgDimming1Create(uint aDeviceHandle);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1Destroy(uint aHandle);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe int DvServiceUpnpOrgDimming1SetPropertyLoadLevelStatus(uint aHandle, uint aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe void DvServiceUpnpOrgDimming1GetPropertyLoadLevelStatus(uint aHandle, uint* aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe int DvServiceUpnpOrgDimming1SetPropertyStepDelta(uint aHandle, uint aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe void DvServiceUpnpOrgDimming1GetPropertyStepDelta(uint aHandle, uint* aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe int DvServiceUpnpOrgDimming1SetPropertyRampRate(uint aHandle, uint aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe void DvServiceUpnpOrgDimming1GetPropertyRampRate(uint aHandle, uint* aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe int DvServiceUpnpOrgDimming1SetPropertyIsRamping(uint aHandle, int aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe void DvServiceUpnpOrgDimming1GetPropertyIsRamping(uint aHandle, int* aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe int DvServiceUpnpOrgDimming1SetPropertyRampPaused(uint aHandle, int aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern unsafe void DvServiceUpnpOrgDimming1GetPropertyRampPaused(uint aHandle, int* aValue);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionSetLoadLevelTarget(uint aHandle, CallbackSetLoadLevelTarget aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionGetLoadLevelTarget(uint aHandle, CallbackGetLoadLevelTarget aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionGetLoadLevelStatus(uint aHandle, CallbackGetLoadLevelStatus aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionSetOnEffectLevel(uint aHandle, CallbackSetOnEffectLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionSetOnEffect(uint aHandle, CallbackSetOnEffect aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionGetOnEffectParameters(uint aHandle, CallbackGetOnEffectParameters aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionStepUp(uint aHandle, CallbackStepUp aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionStepDown(uint aHandle, CallbackStepDown aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionStartRampUp(uint aHandle, CallbackStartRampUp aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionStartRampDown(uint aHandle, CallbackStartRampDown aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionStopRamp(uint aHandle, CallbackStopRamp aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionStartRampToLevel(uint aHandle, CallbackStartRampToLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionSetStepDelta(uint aHandle, CallbackSetStepDelta aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionGetStepDelta(uint aHandle, CallbackGetStepDelta aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionSetRampRate(uint aHandle, CallbackSetRampRate aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionGetRampRate(uint aHandle, CallbackGetRampRate aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionPauseRamp(uint aHandle, CallbackPauseRamp aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionResumeRamp(uint aHandle, CallbackResumeRamp aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionGetIsRamping(uint aHandle, CallbackGetIsRamping aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionGetRampPaused(uint aHandle, CallbackGetRampPaused aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgDimming1")]
        static extern void DvServiceUpnpOrgDimming1EnableActionGetRampTime(uint aHandle, CallbackGetRampTime aCallback, IntPtr aPtr);
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

        private uint iHandle;
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

        public DvServiceUpnpOrgDimming1(DvDevice aDevice)
        {
            iHandle = DvServiceUpnpOrgDimming1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyLoadLevelStatus(uint aValue)
        {
            if (0 != DvServiceUpnpOrgDimming1SetPropertyLoadLevelStatus(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyLoadLevelStatus(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceUpnpOrgDimming1GetPropertyLoadLevelStatus(iHandle, value);
            }
        }

        public unsafe void SetPropertyStepDelta(uint aValue)
        {
            if (0 != DvServiceUpnpOrgDimming1SetPropertyStepDelta(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyStepDelta(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceUpnpOrgDimming1GetPropertyStepDelta(iHandle, value);
            }
        }

        public unsafe void SetPropertyRampRate(uint aValue)
        {
            if (0 != DvServiceUpnpOrgDimming1SetPropertyRampRate(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyRampRate(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceUpnpOrgDimming1GetPropertyRampRate(iHandle, value);
            }
        }

        public unsafe void SetPropertyIsRamping(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceUpnpOrgDimming1SetPropertyIsRamping(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyIsRamping(out bool aValue)
        {
            int value;
            DvServiceUpnpOrgDimming1GetPropertyIsRamping(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyRampPaused(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceUpnpOrgDimming1SetPropertyRampPaused(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyRampPaused(out bool aValue)
        {
            int value;
            DvServiceUpnpOrgDimming1GetPropertyRampPaused(iHandle, &value);
            aValue = (value != 0);
        }

        protected unsafe void EnableActionSetLoadLevelTarget()
        {
            iCallbackSetLoadLevelTarget = new CallbackSetLoadLevelTarget(DoSetLoadLevelTarget);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionSetLoadLevelTarget(iHandle, iCallbackSetLoadLevelTarget, ptr);
        }

        protected unsafe void EnableActionGetLoadLevelTarget()
        {
            iCallbackGetLoadLevelTarget = new CallbackGetLoadLevelTarget(DoGetLoadLevelTarget);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionGetLoadLevelTarget(iHandle, iCallbackGetLoadLevelTarget, ptr);
        }

        protected unsafe void EnableActionGetLoadLevelStatus()
        {
            iCallbackGetLoadLevelStatus = new CallbackGetLoadLevelStatus(DoGetLoadLevelStatus);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionGetLoadLevelStatus(iHandle, iCallbackGetLoadLevelStatus, ptr);
        }

        protected unsafe void EnableActionSetOnEffectLevel()
        {
            iCallbackSetOnEffectLevel = new CallbackSetOnEffectLevel(DoSetOnEffectLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionSetOnEffectLevel(iHandle, iCallbackSetOnEffectLevel, ptr);
        }

        protected unsafe void EnableActionSetOnEffect()
        {
            iCallbackSetOnEffect = new CallbackSetOnEffect(DoSetOnEffect);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionSetOnEffect(iHandle, iCallbackSetOnEffect, ptr);
        }

        protected unsafe void EnableActionGetOnEffectParameters()
        {
            iCallbackGetOnEffectParameters = new CallbackGetOnEffectParameters(DoGetOnEffectParameters);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionGetOnEffectParameters(iHandle, iCallbackGetOnEffectParameters, ptr);
        }

        protected unsafe void EnableActionStepUp()
        {
            iCallbackStepUp = new CallbackStepUp(DoStepUp);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionStepUp(iHandle, iCallbackStepUp, ptr);
        }

        protected unsafe void EnableActionStepDown()
        {
            iCallbackStepDown = new CallbackStepDown(DoStepDown);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionStepDown(iHandle, iCallbackStepDown, ptr);
        }

        protected unsafe void EnableActionStartRampUp()
        {
            iCallbackStartRampUp = new CallbackStartRampUp(DoStartRampUp);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionStartRampUp(iHandle, iCallbackStartRampUp, ptr);
        }

        protected unsafe void EnableActionStartRampDown()
        {
            iCallbackStartRampDown = new CallbackStartRampDown(DoStartRampDown);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionStartRampDown(iHandle, iCallbackStartRampDown, ptr);
        }

        protected unsafe void EnableActionStopRamp()
        {
            iCallbackStopRamp = new CallbackStopRamp(DoStopRamp);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionStopRamp(iHandle, iCallbackStopRamp, ptr);
        }

        protected unsafe void EnableActionStartRampToLevel()
        {
            iCallbackStartRampToLevel = new CallbackStartRampToLevel(DoStartRampToLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionStartRampToLevel(iHandle, iCallbackStartRampToLevel, ptr);
        }

        protected unsafe void EnableActionSetStepDelta()
        {
            iCallbackSetStepDelta = new CallbackSetStepDelta(DoSetStepDelta);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionSetStepDelta(iHandle, iCallbackSetStepDelta, ptr);
        }

        protected unsafe void EnableActionGetStepDelta()
        {
            iCallbackGetStepDelta = new CallbackGetStepDelta(DoGetStepDelta);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionGetStepDelta(iHandle, iCallbackGetStepDelta, ptr);
        }

        protected unsafe void EnableActionSetRampRate()
        {
            iCallbackSetRampRate = new CallbackSetRampRate(DoSetRampRate);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionSetRampRate(iHandle, iCallbackSetRampRate, ptr);
        }

        protected unsafe void EnableActionGetRampRate()
        {
            iCallbackGetRampRate = new CallbackGetRampRate(DoGetRampRate);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionGetRampRate(iHandle, iCallbackGetRampRate, ptr);
        }

        protected unsafe void EnableActionPauseRamp()
        {
            iCallbackPauseRamp = new CallbackPauseRamp(DoPauseRamp);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionPauseRamp(iHandle, iCallbackPauseRamp, ptr);
        }

        protected unsafe void EnableActionResumeRamp()
        {
            iCallbackResumeRamp = new CallbackResumeRamp(DoResumeRamp);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionResumeRamp(iHandle, iCallbackResumeRamp, ptr);
        }

        protected unsafe void EnableActionGetIsRamping()
        {
            iCallbackGetIsRamping = new CallbackGetIsRamping(DoGetIsRamping);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionGetIsRamping(iHandle, iCallbackGetIsRamping, ptr);
        }

        protected unsafe void EnableActionGetRampPaused()
        {
            iCallbackGetRampPaused = new CallbackGetRampPaused(DoGetRampPaused);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionGetRampPaused(iHandle, iCallbackGetRampPaused, ptr);
        }

        protected unsafe void EnableActionGetRampTime()
        {
            iCallbackGetRampTime = new CallbackGetRampTime(DoGetRampTime);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgDimming1EnableActionGetRampTime(iHandle, iCallbackGetRampTime, ptr);
        }

        protected virtual void SetLoadLevelTarget(uint aVersion, uint anewLoadlevelTarget)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetLoadLevelTarget(uint aVersion, out uint aGetLoadlevelTarget)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetLoadLevelStatus(uint aVersion, out uint aretLoadlevelStatus)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetOnEffectLevel(uint aVersion, uint anewOnEffectLevel)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetOnEffect(uint aVersion, string anewOnEffect)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetOnEffectParameters(uint aVersion, out string aretOnEffect, out uint aretOnEffectLevel)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void StepUp(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void StepDown(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void StartRampUp(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void StartRampDown(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void StopRamp(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void StartRampToLevel(uint aVersion, uint anewLoadLevelTarget, uint anewRampTime)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetStepDelta(uint aVersion, uint anewStepDelta)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetStepDelta(uint aVersion, out uint aretStepDelta)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetRampRate(uint aVersion, uint anewRampRate)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetRampRate(uint aVersion, out uint aretRampRate)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void PauseRamp(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void ResumeRamp(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetIsRamping(uint aVersion, out bool aretIsRamping)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetRampPaused(uint aVersion, out bool aretRampPaused)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetRampTime(uint aVersion, out uint aretRampTime)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSetLoadLevelTarget(IntPtr aPtr, uint aVersion, uint anewLoadlevelTarget)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            self.SetLoadLevelTarget(aVersion, anewLoadlevelTarget);
            return 0;
        }

        private static unsafe int DoGetLoadLevelTarget(IntPtr aPtr, uint aVersion, uint* aGetLoadlevelTarget)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            uint getLoadlevelTarget;
            self.GetLoadLevelTarget(aVersion, out getLoadlevelTarget);
            *aGetLoadlevelTarget = getLoadlevelTarget;
            return 0;
        }

        private static unsafe int DoGetLoadLevelStatus(IntPtr aPtr, uint aVersion, uint* aretLoadlevelStatus)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            uint retLoadlevelStatus;
            self.GetLoadLevelStatus(aVersion, out retLoadlevelStatus);
            *aretLoadlevelStatus = retLoadlevelStatus;
            return 0;
        }

        private static unsafe int DoSetOnEffectLevel(IntPtr aPtr, uint aVersion, uint anewOnEffectLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            self.SetOnEffectLevel(aVersion, anewOnEffectLevel);
            return 0;
        }

        private static unsafe int DoSetOnEffect(IntPtr aPtr, uint aVersion, char* anewOnEffect)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            string newOnEffect = Marshal.PtrToStringAnsi((IntPtr)anewOnEffect);
            self.SetOnEffect(aVersion, newOnEffect);
            return 0;
        }

        private static unsafe int DoGetOnEffectParameters(IntPtr aPtr, uint aVersion, char** aretOnEffect, uint* aretOnEffectLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
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
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            self.StepUp(aVersion);
            return 0;
        }

        private static unsafe int DoStepDown(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            self.StepDown(aVersion);
            return 0;
        }

        private static unsafe int DoStartRampUp(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            self.StartRampUp(aVersion);
            return 0;
        }

        private static unsafe int DoStartRampDown(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            self.StartRampDown(aVersion);
            return 0;
        }

        private static unsafe int DoStopRamp(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            self.StopRamp(aVersion);
            return 0;
        }

        private static unsafe int DoStartRampToLevel(IntPtr aPtr, uint aVersion, uint anewLoadLevelTarget, uint anewRampTime)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            self.StartRampToLevel(aVersion, anewLoadLevelTarget, anewRampTime);
            return 0;
        }

        private static unsafe int DoSetStepDelta(IntPtr aPtr, uint aVersion, uint anewStepDelta)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            self.SetStepDelta(aVersion, anewStepDelta);
            return 0;
        }

        private static unsafe int DoGetStepDelta(IntPtr aPtr, uint aVersion, uint* aretStepDelta)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            uint retStepDelta;
            self.GetStepDelta(aVersion, out retStepDelta);
            *aretStepDelta = retStepDelta;
            return 0;
        }

        private static unsafe int DoSetRampRate(IntPtr aPtr, uint aVersion, uint anewRampRate)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            self.SetRampRate(aVersion, anewRampRate);
            return 0;
        }

        private static unsafe int DoGetRampRate(IntPtr aPtr, uint aVersion, uint* aretRampRate)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            uint retRampRate;
            self.GetRampRate(aVersion, out retRampRate);
            *aretRampRate = retRampRate;
            return 0;
        }

        private static unsafe int DoPauseRamp(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            self.PauseRamp(aVersion);
            return 0;
        }

        private static unsafe int DoResumeRamp(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            self.ResumeRamp(aVersion);
            return 0;
        }

        private static unsafe int DoGetIsRamping(IntPtr aPtr, uint aVersion, int* aretIsRamping)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            bool retIsRamping;
            self.GetIsRamping(aVersion, out retIsRamping);
            *aretIsRamping = (retIsRamping ? 1 : 0);
            return 0;
        }

        private static unsafe int DoGetRampPaused(IntPtr aPtr, uint aVersion, int* aretRampPaused)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            bool retRampPaused;
            self.GetRampPaused(aVersion, out retRampPaused);
            *aretRampPaused = (retRampPaused ? 1 : 0);
            return 0;
        }

        private static unsafe int DoGetRampTime(IntPtr aPtr, uint aVersion, uint* aretRampTime)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgDimming1 self = (DvServiceUpnpOrgDimming1)gch.Target;
            uint retRampTime;
            self.GetRampTime(aVersion, out retRampTime);
            *aretRampTime = retRampTime;
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceUpnpOrgDimming1()
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
            DvServiceUpnpOrgDimming1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

