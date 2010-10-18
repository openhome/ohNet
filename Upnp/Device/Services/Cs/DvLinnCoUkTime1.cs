using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkTime1 : IDisposable
    {
        [DllImport("DvLinnCoUkTime1")]
        static extern IntPtr DvServiceLinnCoUkTime1Create(IntPtr aDeviceHandle);
        [DllImport("DvLinnCoUkTime1")]
        static extern void DvServiceLinnCoUkTime1Destroy(IntPtr aHandle);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe int DvServiceLinnCoUkTime1SetPropertyTrackCount(IntPtr aHandle, uint aValue);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe void DvServiceLinnCoUkTime1GetPropertyTrackCount(IntPtr aHandle, uint* aValue);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe int DvServiceLinnCoUkTime1SetPropertyDuration(IntPtr aHandle, uint aValue);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe void DvServiceLinnCoUkTime1GetPropertyDuration(IntPtr aHandle, uint* aValue);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe int DvServiceLinnCoUkTime1SetPropertySeconds(IntPtr aHandle, uint aValue);
        [DllImport("DvLinnCoUkTime1")]
        static extern unsafe void DvServiceLinnCoUkTime1GetPropertySeconds(IntPtr aHandle, uint* aValue);
        [DllImport("DvLinnCoUkTime1")]
        static extern void DvServiceLinnCoUkTime1EnableActionTime(IntPtr aHandle, CallbackTime aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackTime(IntPtr aPtr, uint aVersion, uint* aaTrackCount, uint* aaDuration, uint* aaSeconds);

        private IntPtr iHandle;
        private GCHandle iGch;
        private CallbackTime iCallbackTime;

        public DvServiceLinnCoUkTime1(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkTime1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyTrackCount(uint aValue)
        {
            if (0 != DvServiceLinnCoUkTime1SetPropertyTrackCount(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyTrackCount(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkTime1GetPropertyTrackCount(iHandle, value);
            }
        }

        public unsafe void SetPropertyDuration(uint aValue)
        {
            if (0 != DvServiceLinnCoUkTime1SetPropertyDuration(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyDuration(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkTime1GetPropertyDuration(iHandle, value);
            }
        }

        public unsafe void SetPropertySeconds(uint aValue)
        {
            if (0 != DvServiceLinnCoUkTime1SetPropertySeconds(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertySeconds(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkTime1GetPropertySeconds(iHandle, value);
            }
        }

        protected unsafe void EnableActionTime()
        {
            iCallbackTime = new CallbackTime(DoTime);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkTime1EnableActionTime(iHandle, iCallbackTime, ptr);
        }

        protected virtual void Time(uint aVersion, out uint aaTrackCount, out uint aaDuration, out uint aaSeconds)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoTime(IntPtr aPtr, uint aVersion, uint* aaTrackCount, uint* aaDuration, uint* aaSeconds)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkTime1 self = (DvServiceLinnCoUkTime1)gch.Target;
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

        ~DvServiceLinnCoUkTime1()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            IntPtr handle;
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                handle = iHandle;
                iHandle = IntPtr.Zero;
            }
            DvServiceLinnCoUkTime1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

