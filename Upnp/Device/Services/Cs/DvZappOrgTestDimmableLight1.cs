using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceZappOrgTestDimmableLight1 : IDisposable
    {
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern uint DvServiceZappOrgTestDimmableLight1Create(uint aDeviceHandle);
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern void DvServiceZappOrgTestDimmableLight1Destroy(uint aHandle);
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern unsafe int DvServiceZappOrgTestDimmableLight1SetPropertyA_ARG_Level(uint aHandle, uint aValue);
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern unsafe void DvServiceZappOrgTestDimmableLight1GetPropertyA_ARG_Level(uint aHandle, uint* aValue);
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern void DvServiceZappOrgTestDimmableLight1EnableActionGetLevel(uint aHandle, CallbackGetLevel aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern void DvServiceZappOrgTestDimmableLight1EnableActionSetLevel(uint aHandle, CallbackSetLevel aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackGetLevel(IntPtr aPtr, uint aVersion, uint* aLevel);
        private unsafe delegate int CallbackSetLevel(IntPtr aPtr, uint aVersion, uint aLevel);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackGetLevel iCallbackGetLevel;
        private CallbackSetLevel iCallbackSetLevel;

        public DvServiceZappOrgTestDimmableLight1(DvDevice aDevice)
        {
            iHandle = DvServiceZappOrgTestDimmableLight1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyA_ARG_Level(uint aValue)
        {
            if (0 != DvServiceZappOrgTestDimmableLight1SetPropertyA_ARG_Level(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyA_ARG_Level(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceZappOrgTestDimmableLight1GetPropertyA_ARG_Level(iHandle, value);
            }
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
            DvServiceZappOrgTestDimmableLight1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

