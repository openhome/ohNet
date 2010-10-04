using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkMediaTime1 : IDisposable
    {
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern uint DvServiceLinnCoUkMediaTime1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern void DvServiceLinnCoUkMediaTime1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern unsafe int DvServiceLinnCoUkMediaTime1SetPropertySeconds(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern unsafe void DvServiceLinnCoUkMediaTime1GetPropertySeconds(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern void DvServiceLinnCoUkMediaTime1EnableActionSeconds(uint aHandle, CallbackSeconds aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackSeconds(IntPtr aPtr, uint aVersion, uint* aaSeconds);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackSeconds iCallbackSeconds;

        public DvServiceLinnCoUkMediaTime1(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkMediaTime1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertySeconds(uint aValue)
        {
            if (0 != DvServiceLinnCoUkMediaTime1SetPropertySeconds(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertySeconds(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkMediaTime1GetPropertySeconds(iHandle, value);
            }
        }

        protected unsafe void EnableActionSeconds()
        {
            iCallbackSeconds = new CallbackSeconds(DoSeconds);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkMediaTime1EnableActionSeconds(iHandle, iCallbackSeconds, ptr);
        }

        protected virtual void Seconds(uint aVersion, out uint aaSeconds)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSeconds(IntPtr aPtr, uint aVersion, uint* aaSeconds)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkMediaTime1 self = (DvServiceLinnCoUkMediaTime1)gch.Target;
            uint aSeconds;
            self.Seconds(aVersion, out aSeconds);
            *aaSeconds = aSeconds;
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkMediaTime1()
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
            DvServiceLinnCoUkMediaTime1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

