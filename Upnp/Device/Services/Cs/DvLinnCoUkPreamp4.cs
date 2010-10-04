using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkPreamp4 : IDisposable
    {
        [DllImport("DvLinnCoUkPreamp4")]
        static extern uint DvServiceLinnCoUkPreamp4Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4Destroy(uint aHandle);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe int DvServiceLinnCoUkPreamp4SetPropertyVolume(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe void DvServiceLinnCoUkPreamp4GetPropertyVolume(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe int DvServiceLinnCoUkPreamp4SetPropertyMute(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe void DvServiceLinnCoUkPreamp4GetPropertyMute(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe int DvServiceLinnCoUkPreamp4SetPropertyBalance(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe void DvServiceLinnCoUkPreamp4GetPropertyBalance(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe int DvServiceLinnCoUkPreamp4SetPropertyVolumeLimit(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe void DvServiceLinnCoUkPreamp4GetPropertyVolumeLimit(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe int DvServiceLinnCoUkPreamp4SetPropertyStartupVolume(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe void DvServiceLinnCoUkPreamp4GetPropertyStartupVolume(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe int DvServiceLinnCoUkPreamp4SetPropertyStartupVolumeEnabled(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe void DvServiceLinnCoUkPreamp4GetPropertyStartupVolumeEnabled(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4EnableActionVolumeInc(uint aHandle, CallbackVolumeInc aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4EnableActionVolumeDec(uint aHandle, CallbackVolumeDec aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4EnableActionSetVolume(uint aHandle, CallbackSetVolume aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4EnableActionVolume(uint aHandle, CallbackVolume aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4EnableActionSetMute(uint aHandle, CallbackSetMute aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4EnableActionMute(uint aHandle, CallbackMute aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4EnableActionSetBalance(uint aHandle, CallbackSetBalance aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4EnableActionBalance(uint aHandle, CallbackBalance aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4EnableActionSetVolumeLimit(uint aHandle, CallbackSetVolumeLimit aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4EnableActionVolumeLimit(uint aHandle, CallbackVolumeLimit aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4EnableActionSetStartupVolume(uint aHandle, CallbackSetStartupVolume aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4EnableActionStartupVolume(uint aHandle, CallbackStartupVolume aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4EnableActionSetStartupVolumeEnabled(uint aHandle, CallbackSetStartupVolumeEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvServiceLinnCoUkPreamp4EnableActionStartupVolumeEnabled(uint aHandle, CallbackStartupVolumeEnabled aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackVolumeInc(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackVolumeDec(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackSetVolume(IntPtr aPtr, uint aVersion, uint aaVolume);
        private unsafe delegate int CallbackVolume(IntPtr aPtr, uint aVersion, uint* aaVolume);
        private unsafe delegate int CallbackSetMute(IntPtr aPtr, uint aVersion, int aaMute);
        private unsafe delegate int CallbackMute(IntPtr aPtr, uint aVersion, int* aaMute);
        private unsafe delegate int CallbackSetBalance(IntPtr aPtr, uint aVersion, int aaBalance);
        private unsafe delegate int CallbackBalance(IntPtr aPtr, uint aVersion, int* aaBalance);
        private unsafe delegate int CallbackSetVolumeLimit(IntPtr aPtr, uint aVersion, uint aaVolumeLimit);
        private unsafe delegate int CallbackVolumeLimit(IntPtr aPtr, uint aVersion, uint* aaVolumeLimit);
        private unsafe delegate int CallbackSetStartupVolume(IntPtr aPtr, uint aVersion, uint aaStartupVolume);
        private unsafe delegate int CallbackStartupVolume(IntPtr aPtr, uint aVersion, uint* aaStartupVolume);
        private unsafe delegate int CallbackSetStartupVolumeEnabled(IntPtr aPtr, uint aVersion, int aaStartupVolumeEnabled);
        private unsafe delegate int CallbackStartupVolumeEnabled(IntPtr aPtr, uint aVersion, int* aaStartupVolumeEnabled);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackVolumeInc iCallbackVolumeInc;
        private CallbackVolumeDec iCallbackVolumeDec;
        private CallbackSetVolume iCallbackSetVolume;
        private CallbackVolume iCallbackVolume;
        private CallbackSetMute iCallbackSetMute;
        private CallbackMute iCallbackMute;
        private CallbackSetBalance iCallbackSetBalance;
        private CallbackBalance iCallbackBalance;
        private CallbackSetVolumeLimit iCallbackSetVolumeLimit;
        private CallbackVolumeLimit iCallbackVolumeLimit;
        private CallbackSetStartupVolume iCallbackSetStartupVolume;
        private CallbackStartupVolume iCallbackStartupVolume;
        private CallbackSetStartupVolumeEnabled iCallbackSetStartupVolumeEnabled;
        private CallbackStartupVolumeEnabled iCallbackStartupVolumeEnabled;

        public DvServiceLinnCoUkPreamp4(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkPreamp4Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyVolume(uint aValue)
        {
            if (0 != DvServiceLinnCoUkPreamp4SetPropertyVolume(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyVolume(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkPreamp4GetPropertyVolume(iHandle, value);
            }
        }

        public unsafe void SetPropertyMute(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkPreamp4SetPropertyMute(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyMute(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkPreamp4GetPropertyMute(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyBalance(int aValue)
        {
            if (0 != DvServiceLinnCoUkPreamp4SetPropertyBalance(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyBalance(out int aValue)
        {
            fixed (int* value = &aValue)
			{
                DvServiceLinnCoUkPreamp4GetPropertyBalance(iHandle, value);
            }
        }

        public unsafe void SetPropertyVolumeLimit(uint aValue)
        {
            if (0 != DvServiceLinnCoUkPreamp4SetPropertyVolumeLimit(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyVolumeLimit(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkPreamp4GetPropertyVolumeLimit(iHandle, value);
            }
        }

        public unsafe void SetPropertyStartupVolume(uint aValue)
        {
            if (0 != DvServiceLinnCoUkPreamp4SetPropertyStartupVolume(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyStartupVolume(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkPreamp4GetPropertyStartupVolume(iHandle, value);
            }
        }

        public unsafe void SetPropertyStartupVolumeEnabled(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkPreamp4SetPropertyStartupVolumeEnabled(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyStartupVolumeEnabled(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkPreamp4GetPropertyStartupVolumeEnabled(iHandle, &value);
            aValue = (value != 0);
        }

        protected unsafe void EnableActionVolumeInc()
        {
            iCallbackVolumeInc = new CallbackVolumeInc(DoVolumeInc);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPreamp4EnableActionVolumeInc(iHandle, iCallbackVolumeInc, ptr);
        }

        protected unsafe void EnableActionVolumeDec()
        {
            iCallbackVolumeDec = new CallbackVolumeDec(DoVolumeDec);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPreamp4EnableActionVolumeDec(iHandle, iCallbackVolumeDec, ptr);
        }

        protected unsafe void EnableActionSetVolume()
        {
            iCallbackSetVolume = new CallbackSetVolume(DoSetVolume);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPreamp4EnableActionSetVolume(iHandle, iCallbackSetVolume, ptr);
        }

        protected unsafe void EnableActionVolume()
        {
            iCallbackVolume = new CallbackVolume(DoVolume);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPreamp4EnableActionVolume(iHandle, iCallbackVolume, ptr);
        }

        protected unsafe void EnableActionSetMute()
        {
            iCallbackSetMute = new CallbackSetMute(DoSetMute);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPreamp4EnableActionSetMute(iHandle, iCallbackSetMute, ptr);
        }

        protected unsafe void EnableActionMute()
        {
            iCallbackMute = new CallbackMute(DoMute);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPreamp4EnableActionMute(iHandle, iCallbackMute, ptr);
        }

        protected unsafe void EnableActionSetBalance()
        {
            iCallbackSetBalance = new CallbackSetBalance(DoSetBalance);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPreamp4EnableActionSetBalance(iHandle, iCallbackSetBalance, ptr);
        }

        protected unsafe void EnableActionBalance()
        {
            iCallbackBalance = new CallbackBalance(DoBalance);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPreamp4EnableActionBalance(iHandle, iCallbackBalance, ptr);
        }

        protected unsafe void EnableActionSetVolumeLimit()
        {
            iCallbackSetVolumeLimit = new CallbackSetVolumeLimit(DoSetVolumeLimit);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPreamp4EnableActionSetVolumeLimit(iHandle, iCallbackSetVolumeLimit, ptr);
        }

        protected unsafe void EnableActionVolumeLimit()
        {
            iCallbackVolumeLimit = new CallbackVolumeLimit(DoVolumeLimit);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPreamp4EnableActionVolumeLimit(iHandle, iCallbackVolumeLimit, ptr);
        }

        protected unsafe void EnableActionSetStartupVolume()
        {
            iCallbackSetStartupVolume = new CallbackSetStartupVolume(DoSetStartupVolume);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPreamp4EnableActionSetStartupVolume(iHandle, iCallbackSetStartupVolume, ptr);
        }

        protected unsafe void EnableActionStartupVolume()
        {
            iCallbackStartupVolume = new CallbackStartupVolume(DoStartupVolume);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPreamp4EnableActionStartupVolume(iHandle, iCallbackStartupVolume, ptr);
        }

        protected unsafe void EnableActionSetStartupVolumeEnabled()
        {
            iCallbackSetStartupVolumeEnabled = new CallbackSetStartupVolumeEnabled(DoSetStartupVolumeEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPreamp4EnableActionSetStartupVolumeEnabled(iHandle, iCallbackSetStartupVolumeEnabled, ptr);
        }

        protected unsafe void EnableActionStartupVolumeEnabled()
        {
            iCallbackStartupVolumeEnabled = new CallbackStartupVolumeEnabled(DoStartupVolumeEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPreamp4EnableActionStartupVolumeEnabled(iHandle, iCallbackStartupVolumeEnabled, ptr);
        }

        protected virtual void VolumeInc(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void VolumeDec(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetVolume(uint aVersion, uint aaVolume)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Volume(uint aVersion, out uint aaVolume)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetMute(uint aVersion, bool aaMute)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Mute(uint aVersion, out bool aaMute)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetBalance(uint aVersion, int aaBalance)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Balance(uint aVersion, out int aaBalance)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetVolumeLimit(uint aVersion, uint aaVolumeLimit)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void VolumeLimit(uint aVersion, out uint aaVolumeLimit)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetStartupVolume(uint aVersion, uint aaStartupVolume)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void StartupVolume(uint aVersion, out uint aaStartupVolume)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetStartupVolumeEnabled(uint aVersion, bool aaStartupVolumeEnabled)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void StartupVolumeEnabled(uint aVersion, out bool aaStartupVolumeEnabled)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoVolumeInc(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPreamp4 self = (DvServiceLinnCoUkPreamp4)gch.Target;
            self.VolumeInc(aVersion);
            return 0;
        }

        private static unsafe int DoVolumeDec(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPreamp4 self = (DvServiceLinnCoUkPreamp4)gch.Target;
            self.VolumeDec(aVersion);
            return 0;
        }

        private static unsafe int DoSetVolume(IntPtr aPtr, uint aVersion, uint aaVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPreamp4 self = (DvServiceLinnCoUkPreamp4)gch.Target;
            self.SetVolume(aVersion, aaVolume);
            return 0;
        }

        private static unsafe int DoVolume(IntPtr aPtr, uint aVersion, uint* aaVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPreamp4 self = (DvServiceLinnCoUkPreamp4)gch.Target;
            uint aVolume;
            self.Volume(aVersion, out aVolume);
            *aaVolume = aVolume;
            return 0;
        }

        private static unsafe int DoSetMute(IntPtr aPtr, uint aVersion, int aaMute)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPreamp4 self = (DvServiceLinnCoUkPreamp4)gch.Target;
            bool aMute = (aaMute != 0);
            self.SetMute(aVersion, aMute);
            return 0;
        }

        private static unsafe int DoMute(IntPtr aPtr, uint aVersion, int* aaMute)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPreamp4 self = (DvServiceLinnCoUkPreamp4)gch.Target;
            bool aMute;
            self.Mute(aVersion, out aMute);
            *aaMute = (aMute ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetBalance(IntPtr aPtr, uint aVersion, int aaBalance)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPreamp4 self = (DvServiceLinnCoUkPreamp4)gch.Target;
            self.SetBalance(aVersion, aaBalance);
            return 0;
        }

        private static unsafe int DoBalance(IntPtr aPtr, uint aVersion, int* aaBalance)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPreamp4 self = (DvServiceLinnCoUkPreamp4)gch.Target;
            int aBalance;
            self.Balance(aVersion, out aBalance);
            *aaBalance = aBalance;
            return 0;
        }

        private static unsafe int DoSetVolumeLimit(IntPtr aPtr, uint aVersion, uint aaVolumeLimit)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPreamp4 self = (DvServiceLinnCoUkPreamp4)gch.Target;
            self.SetVolumeLimit(aVersion, aaVolumeLimit);
            return 0;
        }

        private static unsafe int DoVolumeLimit(IntPtr aPtr, uint aVersion, uint* aaVolumeLimit)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPreamp4 self = (DvServiceLinnCoUkPreamp4)gch.Target;
            uint aVolumeLimit;
            self.VolumeLimit(aVersion, out aVolumeLimit);
            *aaVolumeLimit = aVolumeLimit;
            return 0;
        }

        private static unsafe int DoSetStartupVolume(IntPtr aPtr, uint aVersion, uint aaStartupVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPreamp4 self = (DvServiceLinnCoUkPreamp4)gch.Target;
            self.SetStartupVolume(aVersion, aaStartupVolume);
            return 0;
        }

        private static unsafe int DoStartupVolume(IntPtr aPtr, uint aVersion, uint* aaStartupVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPreamp4 self = (DvServiceLinnCoUkPreamp4)gch.Target;
            uint aStartupVolume;
            self.StartupVolume(aVersion, out aStartupVolume);
            *aaStartupVolume = aStartupVolume;
            return 0;
        }

        private static unsafe int DoSetStartupVolumeEnabled(IntPtr aPtr, uint aVersion, int aaStartupVolumeEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPreamp4 self = (DvServiceLinnCoUkPreamp4)gch.Target;
            bool aStartupVolumeEnabled = (aaStartupVolumeEnabled != 0);
            self.SetStartupVolumeEnabled(aVersion, aStartupVolumeEnabled);
            return 0;
        }

        private static unsafe int DoStartupVolumeEnabled(IntPtr aPtr, uint aVersion, int* aaStartupVolumeEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPreamp4 self = (DvServiceLinnCoUkPreamp4)gch.Target;
            bool aStartupVolumeEnabled;
            self.StartupVolumeEnabled(aVersion, out aStartupVolumeEnabled);
            *aaStartupVolumeEnabled = (aStartupVolumeEnabled ? 1 : 0);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkPreamp4()
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
            DvServiceLinnCoUkPreamp4Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

