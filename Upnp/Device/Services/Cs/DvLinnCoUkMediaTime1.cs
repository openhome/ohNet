using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvProviderLinnCoUkMediaTime1 : IDisposable
    {
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern uint DvProviderLinnCoUkMediaTime1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern void DvProviderLinnCoUkMediaTime1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern unsafe int DvProviderLinnCoUkMediaTime1SetPropertySeconds(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern unsafe void DvProviderLinnCoUkMediaTime1GetPropertySeconds(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkMediaTime1")]
        static extern void DvProviderLinnCoUkMediaTime1EnableActionSeconds(uint aHandle, CallbackSeconds aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackSeconds(IntPtr aPtr, uint aVersion, uint* aaSeconds);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackSeconds iCallbackSeconds;

        public DvProviderLinnCoUkMediaTime1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkMediaTime1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe bool SetPropertySeconds(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkMediaTime1SetPropertySeconds(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertySeconds(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkMediaTime1GetPropertySeconds(iHandle, value);
            }
        }

        protected unsafe void EnableActionSeconds()
        {
            iCallbackSeconds = new CallbackSeconds(DoSeconds);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkMediaTime1EnableActionSeconds(iHandle, iCallbackSeconds, ptr);
        }

        protected virtual void Seconds(uint aVersion, out uint aaSeconds)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSeconds(IntPtr aPtr, uint aVersion, uint* aaSeconds)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkMediaTime1 self = (DvProviderLinnCoUkMediaTime1)gch.Target;
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

        ~DvProviderLinnCoUkMediaTime1()
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
            DvProviderLinnCoUkMediaTime1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

