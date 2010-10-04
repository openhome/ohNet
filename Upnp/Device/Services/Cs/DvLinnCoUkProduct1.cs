using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkProduct1 : IDisposable
    {
        [DllImport("DvLinnCoUkProduct1")]
        static extern uint DvServiceLinnCoUkProduct1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkProduct1")]
        static extern void DvServiceLinnCoUkProduct1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkProduct1")]
        static extern unsafe int DvServiceLinnCoUkProduct1SetPropertyRoom(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkProduct1")]
        static extern unsafe void DvServiceLinnCoUkProduct1GetPropertyRoom(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct1")]
        static extern unsafe int DvServiceLinnCoUkProduct1SetPropertyStandby(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkProduct1")]
        static extern unsafe void DvServiceLinnCoUkProduct1GetPropertyStandby(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkProduct1")]
        static extern void DvServiceLinnCoUkProduct1EnableActionRoom(uint aHandle, CallbackRoom aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct1")]
        static extern void DvServiceLinnCoUkProduct1EnableActionSetRoom(uint aHandle, CallbackSetRoom aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct1")]
        static extern void DvServiceLinnCoUkProduct1EnableActionStandby(uint aHandle, CallbackStandby aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct1")]
        static extern void DvServiceLinnCoUkProduct1EnableActionSetStandby(uint aHandle, CallbackSetStandby aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackRoom(IntPtr aPtr, uint aVersion, char** aaRoom);
        private unsafe delegate int CallbackSetRoom(IntPtr aPtr, uint aVersion, char* aaRoom);
        private unsafe delegate int CallbackStandby(IntPtr aPtr, uint aVersion, int* aaStandby);
        private unsafe delegate int CallbackSetStandby(IntPtr aPtr, uint aVersion, int aaStandby);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackRoom iCallbackRoom;
        private CallbackSetRoom iCallbackSetRoom;
        private CallbackStandby iCallbackStandby;
        private CallbackSetStandby iCallbackSetStandby;

        public DvServiceLinnCoUkProduct1(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkProduct1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyRoom(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkProduct1SetPropertyRoom(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyRoom(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkProduct1GetPropertyRoom(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyStandby(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkProduct1SetPropertyStandby(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyStandby(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkProduct1GetPropertyStandby(iHandle, &value);
            aValue = (value != 0);
        }

        protected unsafe void EnableActionRoom()
        {
            iCallbackRoom = new CallbackRoom(DoRoom);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct1EnableActionRoom(iHandle, iCallbackRoom, ptr);
        }

        protected unsafe void EnableActionSetRoom()
        {
            iCallbackSetRoom = new CallbackSetRoom(DoSetRoom);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct1EnableActionSetRoom(iHandle, iCallbackSetRoom, ptr);
        }

        protected unsafe void EnableActionStandby()
        {
            iCallbackStandby = new CallbackStandby(DoStandby);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct1EnableActionStandby(iHandle, iCallbackStandby, ptr);
        }

        protected unsafe void EnableActionSetStandby()
        {
            iCallbackSetStandby = new CallbackSetStandby(DoSetStandby);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct1EnableActionSetStandby(iHandle, iCallbackSetStandby, ptr);
        }

        protected virtual void Room(uint aVersion, out string aaRoom)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetRoom(uint aVersion, string aaRoom)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Standby(uint aVersion, out bool aaStandby)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetStandby(uint aVersion, bool aaStandby)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoRoom(IntPtr aPtr, uint aVersion, char** aaRoom)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct1 self = (DvServiceLinnCoUkProduct1)gch.Target;
            string aRoom;
            self.Room(aVersion, out aRoom);
            *aaRoom = (char*)Marshal.StringToHGlobalAnsi(aRoom).ToPointer();
            return 0;
        }

        private static unsafe int DoSetRoom(IntPtr aPtr, uint aVersion, char* aaRoom)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct1 self = (DvServiceLinnCoUkProduct1)gch.Target;
            string aRoom = Marshal.PtrToStringAnsi((IntPtr)aaRoom);
            self.SetRoom(aVersion, aRoom);
            return 0;
        }

        private static unsafe int DoStandby(IntPtr aPtr, uint aVersion, int* aaStandby)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct1 self = (DvServiceLinnCoUkProduct1)gch.Target;
            bool aStandby;
            self.Standby(aVersion, out aStandby);
            *aaStandby = (aStandby ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetStandby(IntPtr aPtr, uint aVersion, int aaStandby)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct1 self = (DvServiceLinnCoUkProduct1)gch.Target;
            bool aStandby = (aaStandby != 0);
            self.SetStandby(aVersion, aStandby);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkProduct1()
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
            DvServiceLinnCoUkProduct1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

