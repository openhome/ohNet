using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvProviderZappOrgTestWidget1 : DvProvider, IDisposable
    {
        [DllImport("DvZappOrgTestWidget1")]
        static extern uint DvProviderZappOrgTestWidget1Create(uint aDeviceHandle);
        [DllImport("DvZappOrgTestWidget1")]
        static extern void DvProviderZappOrgTestWidget1Destroy(uint aHandle);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe int DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister0(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister0(uint aHandle, uint* aValue);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe int DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister1(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister1(uint aHandle, uint* aValue);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe int DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister2(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister2(uint aHandle, uint* aValue);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe int DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister3(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister3(uint aHandle, uint* aValue);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe int DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister4(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister4(uint aHandle, uint* aValue);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe int DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister5(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister5(uint aHandle, uint* aValue);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe int DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister6(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister6(uint aHandle, uint* aValue);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe int DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister7(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvZappOrgTestWidget1")]
        static extern unsafe void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister7(uint aHandle, uint* aValue);
        [DllImport("DvZappOrgTestWidget1")]
        static extern void DvProviderZappOrgTestWidget1EnableActionSetReadWriteRegister(uint aHandle, CallbackSetReadWriteRegister aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackSetReadWriteRegister(IntPtr aPtr, uint aVersion, uint aRegisterIndex, uint aRegisterValue);

        private GCHandle iGch;
        private CallbackSetReadWriteRegister iCallbackSetReadWriteRegister;

        public DvProviderZappOrgTestWidget1(DvDevice aDevice)
        {
            iHandle = DvProviderZappOrgTestWidget1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe bool SetPropertyReadWriteRegister0(uint aValue)
        {
        uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister0(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyReadWriteRegister0(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister0(iHandle, value);
            }
        }

        public unsafe bool SetPropertyReadWriteRegister1(uint aValue)
        {
        uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister1(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyReadWriteRegister1(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister1(iHandle, value);
            }
        }

        public unsafe bool SetPropertyReadWriteRegister2(uint aValue)
        {
        uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister2(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyReadWriteRegister2(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister2(iHandle, value);
            }
        }

        public unsafe bool SetPropertyReadWriteRegister3(uint aValue)
        {
        uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister3(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyReadWriteRegister3(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister3(iHandle, value);
            }
        }

        public unsafe bool SetPropertyReadOnlyRegister4(uint aValue)
        {
        uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister4(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyReadOnlyRegister4(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister4(iHandle, value);
            }
        }

        public unsafe bool SetPropertyReadOnlyRegister5(uint aValue)
        {
        uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister5(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyReadOnlyRegister5(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister5(iHandle, value);
            }
        }

        public unsafe bool SetPropertyReadOnlyRegister6(uint aValue)
        {
        uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister6(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyReadOnlyRegister6(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister6(iHandle, value);
            }
        }

        public unsafe bool SetPropertyReadOnlyRegister7(uint aValue)
        {
        uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister7(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyReadOnlyRegister7(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister7(iHandle, value);
            }
        }

        protected unsafe void EnableActionSetReadWriteRegister()
        {
            iCallbackSetReadWriteRegister = new CallbackSetReadWriteRegister(DoSetReadWriteRegister);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestWidget1EnableActionSetReadWriteRegister(iHandle, iCallbackSetReadWriteRegister, ptr);
        }

        protected virtual void SetReadWriteRegister(uint aVersion, uint aRegisterIndex, uint aRegisterValue)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSetReadWriteRegister(IntPtr aPtr, uint aVersion, uint aRegisterIndex, uint aRegisterValue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidget1 self = (DvProviderZappOrgTestWidget1)gch.Target;
            self.SetReadWriteRegister(aVersion, aRegisterIndex, aRegisterValue);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderZappOrgTestWidget1()
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
            DvProviderZappOrgTestWidget1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

