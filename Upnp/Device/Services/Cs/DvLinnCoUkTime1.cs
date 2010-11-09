using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvProviderLinnCoUkTime1 : DvProvider, IDisposable
    {
        [DllImport("DvLinnCoUkTime1")]
        static extern uint DvProviderLinnCoUkTime1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkTime1")]
        static extern void DvProviderLinnCoUkTime1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe int DvProviderLinnCoUkTime1SetPropertyTrackCount(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe void DvProviderLinnCoUkTime1GetPropertyTrackCount(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe int DvProviderLinnCoUkTime1SetPropertyDuration(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe void DvProviderLinnCoUkTime1GetPropertyDuration(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe int DvProviderLinnCoUkTime1SetPropertySeconds(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe void DvProviderLinnCoUkTime1GetPropertySeconds(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkTime1")]
        static extern void DvProviderLinnCoUkTime1EnableActionTime(uint aHandle, CallbackTime aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackTime(IntPtr aPtr, uint aVersion, uint* aaTrackCount, uint* aaDuration, uint* aaSeconds);

        private GCHandle iGch;
        private CallbackTime iCallbackTime;

        public DvProviderLinnCoUkTime1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkTime1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe bool SetPropertyTrackCount(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkTime1SetPropertyTrackCount(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyTrackCount(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkTime1GetPropertyTrackCount(iHandle, value);
            }
        }

        public unsafe bool SetPropertyDuration(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkTime1SetPropertyDuration(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyDuration(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkTime1GetPropertyDuration(iHandle, value);
            }
        }

        public unsafe bool SetPropertySeconds(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkTime1SetPropertySeconds(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertySeconds(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkTime1GetPropertySeconds(iHandle, value);
            }
        }

        protected unsafe void EnableActionTime()
        {
            iCallbackTime = new CallbackTime(DoTime);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkTime1EnableActionTime(iHandle, iCallbackTime, ptr);
        }

        protected virtual void Time(uint aVersion, out uint aaTrackCount, out uint aaDuration, out uint aaSeconds)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoTime(IntPtr aPtr, uint aVersion, uint* aaTrackCount, uint* aaDuration, uint* aaSeconds)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkTime1 self = (DvProviderLinnCoUkTime1)gch.Target;
            uint aTrackCount;
            uint aDuration;
            uint aSeconds;
            self.Time(aVersion, out aTrackCount, out aDuration, out aSeconds);
            *aaTrackCount = aTrackCount;
            *aaDuration = aDuration;
            *aaSeconds = aSeconds;
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderLinnCoUkTime1()
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
            DvProviderLinnCoUkTime1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

