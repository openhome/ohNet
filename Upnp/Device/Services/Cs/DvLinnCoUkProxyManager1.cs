using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkProxyManager1 : IDisposable
    {
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern uint DvServiceLinnCoUkProxyManager1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvServiceLinnCoUkProxyManager1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe int DvServiceLinnCoUkProxyManager1SetPropertyKontrolProductConnected(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe void DvServiceLinnCoUkProxyManager1GetPropertyKontrolProductConnected(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe int DvServiceLinnCoUkProxyManager1SetPropertyKontrolProductComPort(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe void DvServiceLinnCoUkProxyManager1GetPropertyKontrolProductComPort(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe int DvServiceLinnCoUkProxyManager1SetPropertyDiscPlayerConnected(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe void DvServiceLinnCoUkProxyManager1GetPropertyDiscPlayerConnected(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe int DvServiceLinnCoUkProxyManager1SetPropertyDiscPlayerComPort(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe void DvServiceLinnCoUkProxyManager1GetPropertyDiscPlayerComPort(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvServiceLinnCoUkProxyManager1EnableActionKontrolProductConnected(uint aHandle, CallbackKontrolProductConnected aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvServiceLinnCoUkProxyManager1EnableActionSetKontrolProductConnected(uint aHandle, CallbackSetKontrolProductConnected aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvServiceLinnCoUkProxyManager1EnableActionKontrolProductComPort(uint aHandle, CallbackKontrolProductComPort aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvServiceLinnCoUkProxyManager1EnableActionSetKontrolProductComPort(uint aHandle, CallbackSetKontrolProductComPort aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvServiceLinnCoUkProxyManager1EnableActionDiscPlayerConnected(uint aHandle, CallbackDiscPlayerConnected aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvServiceLinnCoUkProxyManager1EnableActionSetDiscPlayerConnected(uint aHandle, CallbackSetDiscPlayerConnected aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvServiceLinnCoUkProxyManager1EnableActionDiscPlayerComPort(uint aHandle, CallbackDiscPlayerComPort aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvServiceLinnCoUkProxyManager1EnableActionSetDiscPlayerComPort(uint aHandle, CallbackSetDiscPlayerComPort aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvServiceLinnCoUkProxyManager1EnableActionTestKontrolProductConnection(uint aHandle, CallbackTestKontrolProductConnection aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvServiceLinnCoUkProxyManager1EnableActionTestDiscPlayerConnection(uint aHandle, CallbackTestDiscPlayerConnection aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackKontrolProductConnected(IntPtr aPtr, uint aVersion, char** aaConnected);
        private unsafe delegate int CallbackSetKontrolProductConnected(IntPtr aPtr, uint aVersion, char* aaConnected);
        private unsafe delegate int CallbackKontrolProductComPort(IntPtr aPtr, uint aVersion, uint* aaPort);
        private unsafe delegate int CallbackSetKontrolProductComPort(IntPtr aPtr, uint aVersion, uint aaConnected);
        private unsafe delegate int CallbackDiscPlayerConnected(IntPtr aPtr, uint aVersion, char** aaConnected);
        private unsafe delegate int CallbackSetDiscPlayerConnected(IntPtr aPtr, uint aVersion, char* aaConnected);
        private unsafe delegate int CallbackDiscPlayerComPort(IntPtr aPtr, uint aVersion, uint* aaPort);
        private unsafe delegate int CallbackSetDiscPlayerComPort(IntPtr aPtr, uint aVersion, uint aaConnected);
        private unsafe delegate int CallbackTestKontrolProductConnection(IntPtr aPtr, uint aVersion, int* aaResult);
        private unsafe delegate int CallbackTestDiscPlayerConnection(IntPtr aPtr, uint aVersion, int* aaResult);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackKontrolProductConnected iCallbackKontrolProductConnected;
        private CallbackSetKontrolProductConnected iCallbackSetKontrolProductConnected;
        private CallbackKontrolProductComPort iCallbackKontrolProductComPort;
        private CallbackSetKontrolProductComPort iCallbackSetKontrolProductComPort;
        private CallbackDiscPlayerConnected iCallbackDiscPlayerConnected;
        private CallbackSetDiscPlayerConnected iCallbackSetDiscPlayerConnected;
        private CallbackDiscPlayerComPort iCallbackDiscPlayerComPort;
        private CallbackSetDiscPlayerComPort iCallbackSetDiscPlayerComPort;
        private CallbackTestKontrolProductConnection iCallbackTestKontrolProductConnection;
        private CallbackTestDiscPlayerConnection iCallbackTestDiscPlayerConnection;

        public DvServiceLinnCoUkProxyManager1(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkProxyManager1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyKontrolProductConnected(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkProxyManager1SetPropertyKontrolProductConnected(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyKontrolProductConnected(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkProxyManager1GetPropertyKontrolProductConnected(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyKontrolProductComPort(uint aValue)
        {
            if (0 != DvServiceLinnCoUkProxyManager1SetPropertyKontrolProductComPort(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyKontrolProductComPort(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkProxyManager1GetPropertyKontrolProductComPort(iHandle, value);
            }
        }

        public unsafe void SetPropertyDiscPlayerConnected(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkProxyManager1SetPropertyDiscPlayerConnected(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyDiscPlayerConnected(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkProxyManager1GetPropertyDiscPlayerConnected(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyDiscPlayerComPort(uint aValue)
        {
            if (0 != DvServiceLinnCoUkProxyManager1SetPropertyDiscPlayerComPort(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyDiscPlayerComPort(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkProxyManager1GetPropertyDiscPlayerComPort(iHandle, value);
            }
        }

        protected unsafe void EnableActionKontrolProductConnected()
        {
            iCallbackKontrolProductConnected = new CallbackKontrolProductConnected(DoKontrolProductConnected);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProxyManager1EnableActionKontrolProductConnected(iHandle, iCallbackKontrolProductConnected, ptr);
        }

        protected unsafe void EnableActionSetKontrolProductConnected()
        {
            iCallbackSetKontrolProductConnected = new CallbackSetKontrolProductConnected(DoSetKontrolProductConnected);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProxyManager1EnableActionSetKontrolProductConnected(iHandle, iCallbackSetKontrolProductConnected, ptr);
        }

        protected unsafe void EnableActionKontrolProductComPort()
        {
            iCallbackKontrolProductComPort = new CallbackKontrolProductComPort(DoKontrolProductComPort);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProxyManager1EnableActionKontrolProductComPort(iHandle, iCallbackKontrolProductComPort, ptr);
        }

        protected unsafe void EnableActionSetKontrolProductComPort()
        {
            iCallbackSetKontrolProductComPort = new CallbackSetKontrolProductComPort(DoSetKontrolProductComPort);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProxyManager1EnableActionSetKontrolProductComPort(iHandle, iCallbackSetKontrolProductComPort, ptr);
        }

        protected unsafe void EnableActionDiscPlayerConnected()
        {
            iCallbackDiscPlayerConnected = new CallbackDiscPlayerConnected(DoDiscPlayerConnected);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProxyManager1EnableActionDiscPlayerConnected(iHandle, iCallbackDiscPlayerConnected, ptr);
        }

        protected unsafe void EnableActionSetDiscPlayerConnected()
        {
            iCallbackSetDiscPlayerConnected = new CallbackSetDiscPlayerConnected(DoSetDiscPlayerConnected);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProxyManager1EnableActionSetDiscPlayerConnected(iHandle, iCallbackSetDiscPlayerConnected, ptr);
        }

        protected unsafe void EnableActionDiscPlayerComPort()
        {
            iCallbackDiscPlayerComPort = new CallbackDiscPlayerComPort(DoDiscPlayerComPort);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProxyManager1EnableActionDiscPlayerComPort(iHandle, iCallbackDiscPlayerComPort, ptr);
        }

        protected unsafe void EnableActionSetDiscPlayerComPort()
        {
            iCallbackSetDiscPlayerComPort = new CallbackSetDiscPlayerComPort(DoSetDiscPlayerComPort);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProxyManager1EnableActionSetDiscPlayerComPort(iHandle, iCallbackSetDiscPlayerComPort, ptr);
        }

        protected unsafe void EnableActionTestKontrolProductConnection()
        {
            iCallbackTestKontrolProductConnection = new CallbackTestKontrolProductConnection(DoTestKontrolProductConnection);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProxyManager1EnableActionTestKontrolProductConnection(iHandle, iCallbackTestKontrolProductConnection, ptr);
        }

        protected unsafe void EnableActionTestDiscPlayerConnection()
        {
            iCallbackTestDiscPlayerConnection = new CallbackTestDiscPlayerConnection(DoTestDiscPlayerConnection);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProxyManager1EnableActionTestDiscPlayerConnection(iHandle, iCallbackTestDiscPlayerConnection, ptr);
        }

        protected virtual void KontrolProductConnected(uint aVersion, out string aaConnected)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetKontrolProductConnected(uint aVersion, string aaConnected)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void KontrolProductComPort(uint aVersion, out uint aaPort)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetKontrolProductComPort(uint aVersion, uint aaConnected)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DiscPlayerConnected(uint aVersion, out string aaConnected)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetDiscPlayerConnected(uint aVersion, string aaConnected)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DiscPlayerComPort(uint aVersion, out uint aaPort)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetDiscPlayerComPort(uint aVersion, uint aaConnected)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void TestKontrolProductConnection(uint aVersion, out bool aaResult)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void TestDiscPlayerConnection(uint aVersion, out bool aaResult)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoKontrolProductConnected(IntPtr aPtr, uint aVersion, char** aaConnected)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProxyManager1 self = (DvServiceLinnCoUkProxyManager1)gch.Target;
            string aConnected;
            self.KontrolProductConnected(aVersion, out aConnected);
            *aaConnected = (char*)Marshal.StringToHGlobalAnsi(aConnected).ToPointer();
            return 0;
        }

        private static unsafe int DoSetKontrolProductConnected(IntPtr aPtr, uint aVersion, char* aaConnected)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProxyManager1 self = (DvServiceLinnCoUkProxyManager1)gch.Target;
            string aConnected = Marshal.PtrToStringAnsi((IntPtr)aaConnected);
            self.SetKontrolProductConnected(aVersion, aConnected);
            return 0;
        }

        private static unsafe int DoKontrolProductComPort(IntPtr aPtr, uint aVersion, uint* aaPort)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProxyManager1 self = (DvServiceLinnCoUkProxyManager1)gch.Target;
            uint aPort;
            self.KontrolProductComPort(aVersion, out aPort);
            *aaPort = aPort;
            return 0;
        }

        private static unsafe int DoSetKontrolProductComPort(IntPtr aPtr, uint aVersion, uint aaConnected)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProxyManager1 self = (DvServiceLinnCoUkProxyManager1)gch.Target;
            self.SetKontrolProductComPort(aVersion, aaConnected);
            return 0;
        }

        private static unsafe int DoDiscPlayerConnected(IntPtr aPtr, uint aVersion, char** aaConnected)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProxyManager1 self = (DvServiceLinnCoUkProxyManager1)gch.Target;
            string aConnected;
            self.DiscPlayerConnected(aVersion, out aConnected);
            *aaConnected = (char*)Marshal.StringToHGlobalAnsi(aConnected).ToPointer();
            return 0;
        }

        private static unsafe int DoSetDiscPlayerConnected(IntPtr aPtr, uint aVersion, char* aaConnected)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProxyManager1 self = (DvServiceLinnCoUkProxyManager1)gch.Target;
            string aConnected = Marshal.PtrToStringAnsi((IntPtr)aaConnected);
            self.SetDiscPlayerConnected(aVersion, aConnected);
            return 0;
        }

        private static unsafe int DoDiscPlayerComPort(IntPtr aPtr, uint aVersion, uint* aaPort)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProxyManager1 self = (DvServiceLinnCoUkProxyManager1)gch.Target;
            uint aPort;
            self.DiscPlayerComPort(aVersion, out aPort);
            *aaPort = aPort;
            return 0;
        }

        private static unsafe int DoSetDiscPlayerComPort(IntPtr aPtr, uint aVersion, uint aaConnected)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProxyManager1 self = (DvServiceLinnCoUkProxyManager1)gch.Target;
            self.SetDiscPlayerComPort(aVersion, aaConnected);
            return 0;
        }

        private static unsafe int DoTestKontrolProductConnection(IntPtr aPtr, uint aVersion, int* aaResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProxyManager1 self = (DvServiceLinnCoUkProxyManager1)gch.Target;
            bool aResult;
            self.TestKontrolProductConnection(aVersion, out aResult);
            *aaResult = (aResult ? 1 : 0);
            return 0;
        }

        private static unsafe int DoTestDiscPlayerConnection(IntPtr aPtr, uint aVersion, int* aaResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProxyManager1 self = (DvServiceLinnCoUkProxyManager1)gch.Target;
            bool aResult;
            self.TestDiscPlayerConnection(aVersion, out aResult);
            *aaResult = (aResult ? 1 : 0);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkProxyManager1()
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
            DvServiceLinnCoUkProxyManager1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

