using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkPtest1 : IDisposable
    {
        [DllImport("DvLinnCoUkPtest1")]
        static extern uint DvServiceLinnCoUkPtest1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkPtest1")]
        static extern void DvServiceLinnCoUkPtest1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkPtest1")]
        static extern void DvServiceLinnCoUkPtest1EnableActionTestComPort(uint aHandle, CallbackTestComPort aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPtest1")]
        static extern void DvServiceLinnCoUkPtest1EnableActionLedsOn(uint aHandle, CallbackLedsOn aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPtest1")]
        static extern void DvServiceLinnCoUkPtest1EnableActionLedsOff(uint aHandle, CallbackLedsOff aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackTestComPort(IntPtr aPtr, uint aVersion, uint aaPort, int* aaResult);
        private unsafe delegate int CallbackLedsOn(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackLedsOff(IntPtr aPtr, uint aVersion);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackTestComPort iCallbackTestComPort;
        private CallbackLedsOn iCallbackLedsOn;
        private CallbackLedsOff iCallbackLedsOff;

        public DvServiceLinnCoUkPtest1(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkPtest1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        protected unsafe void EnableActionTestComPort()
        {
            iCallbackTestComPort = new CallbackTestComPort(DoTestComPort);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPtest1EnableActionTestComPort(iHandle, iCallbackTestComPort, ptr);
        }

        protected unsafe void EnableActionLedsOn()
        {
            iCallbackLedsOn = new CallbackLedsOn(DoLedsOn);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPtest1EnableActionLedsOn(iHandle, iCallbackLedsOn, ptr);
        }

        protected unsafe void EnableActionLedsOff()
        {
            iCallbackLedsOff = new CallbackLedsOff(DoLedsOff);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkPtest1EnableActionLedsOff(iHandle, iCallbackLedsOff, ptr);
        }

        protected virtual void TestComPort(uint aVersion, uint aaPort, out bool aaResult)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void LedsOn(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void LedsOff(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoTestComPort(IntPtr aPtr, uint aVersion, uint aaPort, int* aaResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPtest1 self = (DvServiceLinnCoUkPtest1)gch.Target;
            bool aResult;
            self.TestComPort(aVersion, aaPort, out aResult);
            *aaResult = (aResult ? 1 : 0);
            return 0;
        }

        private static unsafe int DoLedsOn(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPtest1 self = (DvServiceLinnCoUkPtest1)gch.Target;
            self.LedsOn(aVersion);
            return 0;
        }

        private static unsafe int DoLedsOff(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkPtest1 self = (DvServiceLinnCoUkPtest1)gch.Target;
            self.LedsOff(aVersion);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkPtest1()
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
            DvServiceLinnCoUkPtest1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

