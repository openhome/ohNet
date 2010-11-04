using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvProviderZappOrgTestDimmableLight1 : DvProvider, IDisposable
    {
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern uint DvProviderZappOrgTestDimmableLight1Create(uint aDeviceHandle);
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern void DvProviderZappOrgTestDimmableLight1Destroy(uint aHandle);
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern unsafe int DvProviderZappOrgTestDimmableLight1SetPropertyA_ARG_Level(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern unsafe void DvProviderZappOrgTestDimmableLight1GetPropertyA_ARG_Level(uint aHandle, uint* aValue);
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern void DvProviderZappOrgTestDimmableLight1EnableActionGetLevel(uint aHandle, CallbackGetLevel aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestDimmableLight1")]
        static extern void DvProviderZappOrgTestDimmableLight1EnableActionSetLevel(uint aHandle, CallbackSetLevel aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackGetLevel(IntPtr aPtr, uint aVersion, uint* aLevel);
        private unsafe delegate int CallbackSetLevel(IntPtr aPtr, uint aVersion, uint aLevel);

        private GCHandle iGch;
        private CallbackGetLevel iCallbackGetLevel;
        private CallbackSetLevel iCallbackSetLevel;

        public DvProviderZappOrgTestDimmableLight1(DvDevice aDevice)
        {
            iHandle = DvProviderZappOrgTestDimmableLight1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe bool SetPropertyA_ARG_Level(uint aValue)
        {
        uint changed;
            if (0 != DvProviderZappOrgTestDimmableLight1SetPropertyA_ARG_Level(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyA_ARG_Level(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderZappOrgTestDimmableLight1GetPropertyA_ARG_Level(iHandle, value);
            }
        }

        protected unsafe void EnableActionGetLevel()
        {
            iCallbackGetLevel = new CallbackGetLevel(DoGetLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestDimmableLight1EnableActionGetLevel(iHandle, iCallbackGetLevel, ptr);
        }

        protected unsafe void EnableActionSetLevel()
        {
            iCallbackSetLevel = new CallbackSetLevel(DoSetLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestDimmableLight1EnableActionSetLevel(iHandle, iCallbackSetLevel, ptr);
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
            DvProviderZappOrgTestDimmableLight1 self = (DvProviderZappOrgTestDimmableLight1)gch.Target;
            uint level;
            self.GetLevel(aVersion, out level);
            *aLevel = level;
            return 0;
        }

        private static unsafe int DoSetLevel(IntPtr aPtr, uint aVersion, uint aLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestDimmableLight1 self = (DvProviderZappOrgTestDimmableLight1)gch.Target;
            self.SetLevel(aVersion, aLevel);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderZappOrgTestDimmableLight1()
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
            DvProviderZappOrgTestDimmableLight1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

