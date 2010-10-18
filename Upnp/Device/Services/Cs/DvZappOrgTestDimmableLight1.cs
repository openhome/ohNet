using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceZappOrgTestDimmableLight1 : IDisposable
    {
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern IntPtr DvServiceZappOrgTestDimmableLight1Create(IntPtr aDeviceHandle);
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern void DvServiceZappOrgTestDimmableLight1Destroy(IntPtr aHandle);
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern void DvServiceZappOrgTestDimmableLight1EnableActionGetLevel(IntPtr aHandle, CallbackGetLevel aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern void DvServiceZappOrgTestDimmableLight1EnableActionSetLevel(IntPtr aHandle, CallbackSetLevel aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackGetLevel(IntPtr aPtr, uint aVersion, uint* aLevel);
        private unsafe delegate int CallbackSetLevel(IntPtr aPtr, uint aVersion, uint aLevel);

        private IntPtr iHandle;
        private GCHandle iGch;
        private CallbackGetLevel iCallbackGetLevel;
        private CallbackSetLevel iCallbackSetLevel;

        public DvServiceZappOrgTestDimmableLight1(DvDevice aDevice)
        {
            iHandle = DvServiceZappOrgTestDimmableLight1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        protected unsafe void EnableActionGetLevel()
        {
            iCallbackGetLevel = new CallbackGetLevel(DoGetLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestDimmableLight1EnableActionGetLevel(iHandle, iCallbackGetLevel, ptr);
        }

        protected unsafe void EnableActionSetLevel()
        {
            iCallbackSetLevel = new CallbackSetLevel(DoSetLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestDimmableLight1EnableActionSetLevel(iHandle, iCallbackSetLevel, ptr);
        }

        protected virtual void GetLevel(uint aVersion, out uint aLevel)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetLevel(uint aVersion, uint aLevel)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoGetLevel(IntPtr aPtr, uint aVersion, uint* aLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestDimmableLight1 self = (DvServiceZappOrgTestDimmableLight1)gch.Target;
            uint level;
            self.GetLevel(aVersion, out level);
            *aLevel = level;
            return 0;
        }

        private static unsafe int DoSetLevel(IntPtr aPtr, uint aVersion, uint aLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestDimmableLight1 self = (DvServiceZappOrgTestDimmableLight1)gch.Target;
            self.SetLevel(aVersion, aLevel);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceZappOrgTestDimmableLight1()
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
            DvServiceZappOrgTestDimmableLight1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

