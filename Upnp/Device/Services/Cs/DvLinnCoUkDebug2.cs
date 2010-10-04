using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkDebug2 : IDisposable
    {
        [DllImport("DvLinnCoUkDebug2")]
        static extern uint DvServiceLinnCoUkDebug2Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkDebug2")]
        static extern void DvServiceLinnCoUkDebug2Destroy(uint aHandle);
        [DllImport("DvLinnCoUkDebug2")]
        static extern void DvServiceLinnCoUkDebug2EnableActionSetDebugLevel(uint aHandle, CallbackSetDebugLevel aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDebug2")]
        static extern void DvServiceLinnCoUkDebug2EnableActionDebugLevel(uint aHandle, CallbackDebugLevel aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDebug2")]
        static extern void DvServiceLinnCoUkDebug2EnableActionMemWrite(uint aHandle, CallbackMemWrite aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackSetDebugLevel(IntPtr aPtr, uint aVersion, uint aaDebugLevel);
        private unsafe delegate int CallbackDebugLevel(IntPtr aPtr, uint aVersion, uint* aaDebugLevel);
        private unsafe delegate int CallbackMemWrite(IntPtr aPtr, uint aVersion, uint aaMemAddress, char* aaMemData, int aaMemDataLen);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackSetDebugLevel iCallbackSetDebugLevel;
        private CallbackDebugLevel iCallbackDebugLevel;
        private CallbackMemWrite iCallbackMemWrite;

        public DvServiceLinnCoUkDebug2(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkDebug2Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        protected unsafe void EnableActionSetDebugLevel()
        {
            iCallbackSetDebugLevel = new CallbackSetDebugLevel(DoSetDebugLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDebug2EnableActionSetDebugLevel(iHandle, iCallbackSetDebugLevel, ptr);
        }

        protected unsafe void EnableActionDebugLevel()
        {
            iCallbackDebugLevel = new CallbackDebugLevel(DoDebugLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDebug2EnableActionDebugLevel(iHandle, iCallbackDebugLevel, ptr);
        }

        protected unsafe void EnableActionMemWrite()
        {
            iCallbackMemWrite = new CallbackMemWrite(DoMemWrite);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDebug2EnableActionMemWrite(iHandle, iCallbackMemWrite, ptr);
        }

        protected virtual void SetDebugLevel(uint aVersion, uint aaDebugLevel)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DebugLevel(uint aVersion, out uint aaDebugLevel)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void MemWrite(uint aVersion, uint aaMemAddress, string aaMemData)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSetDebugLevel(IntPtr aPtr, uint aVersion, uint aaDebugLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDebug2 self = (DvServiceLinnCoUkDebug2)gch.Target;
            self.SetDebugLevel(aVersion, aaDebugLevel);
            return 0;
        }

        private static unsafe int DoDebugLevel(IntPtr aPtr, uint aVersion, uint* aaDebugLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDebug2 self = (DvServiceLinnCoUkDebug2)gch.Target;
            uint aDebugLevel;
            self.DebugLevel(aVersion, out aDebugLevel);
            *aaDebugLevel = aDebugLevel;
            return 0;
        }

        private static unsafe int DoMemWrite(IntPtr aPtr, uint aVersion, uint aaMemAddress, char* aaMemData, int aaMemDataLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDebug2 self = (DvServiceLinnCoUkDebug2)gch.Target;
            string aMemData = Marshal.PtrToStringAnsi((IntPtr)aaMemData, aaMemDataLen);
            self.MemWrite(aVersion, aaMemAddress, aMemData);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkDebug2()
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
            DvServiceLinnCoUkDebug2Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

