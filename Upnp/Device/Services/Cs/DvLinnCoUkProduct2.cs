using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkProduct2 : IDisposable
    {
        [DllImport("DvLinnCoUkProduct2")]
        static extern uint DvServiceLinnCoUkProduct2Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvServiceLinnCoUkProduct2Destroy(uint aHandle);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe int DvServiceLinnCoUkProduct2SetPropertyProductName(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe void DvServiceLinnCoUkProduct2GetPropertyProductName(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe int DvServiceLinnCoUkProduct2SetPropertyProductRoom(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe void DvServiceLinnCoUkProduct2GetPropertyProductRoom(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe int DvServiceLinnCoUkProduct2SetPropertyProductStandby(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe void DvServiceLinnCoUkProduct2GetPropertyProductStandby(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe int DvServiceLinnCoUkProduct2SetPropertyProductSourceIndex(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe void DvServiceLinnCoUkProduct2GetPropertyProductSourceIndex(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvServiceLinnCoUkProduct2EnableActionType(uint aHandle, CallbackType aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvServiceLinnCoUkProduct2EnableActionModel(uint aHandle, CallbackModel aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvServiceLinnCoUkProduct2EnableActionName(uint aHandle, CallbackName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvServiceLinnCoUkProduct2EnableActionSetName(uint aHandle, CallbackSetName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvServiceLinnCoUkProduct2EnableActionRoom(uint aHandle, CallbackRoom aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvServiceLinnCoUkProduct2EnableActionSetRoom(uint aHandle, CallbackSetRoom aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvServiceLinnCoUkProduct2EnableActionStandby(uint aHandle, CallbackStandby aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvServiceLinnCoUkProduct2EnableActionSetStandby(uint aHandle, CallbackSetStandby aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvServiceLinnCoUkProduct2EnableActionSourceCount(uint aHandle, CallbackSourceCount aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvServiceLinnCoUkProduct2EnableActionSourceIndex(uint aHandle, CallbackSourceIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvServiceLinnCoUkProduct2EnableActionSetSourceIndex(uint aHandle, CallbackSetSourceIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvServiceLinnCoUkProduct2EnableActionSourceType(uint aHandle, CallbackSourceType aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackType(IntPtr aPtr, uint aVersion, char** aaType);
        private unsafe delegate int CallbackModel(IntPtr aPtr, uint aVersion, char** aaModel);
        private unsafe delegate int CallbackName(IntPtr aPtr, uint aVersion, char** aaName);
        private unsafe delegate int CallbackSetName(IntPtr aPtr, uint aVersion, char* aaName);
        private unsafe delegate int CallbackRoom(IntPtr aPtr, uint aVersion, char** aaRoom);
        private unsafe delegate int CallbackSetRoom(IntPtr aPtr, uint aVersion, char* aaRoom);
        private unsafe delegate int CallbackStandby(IntPtr aPtr, uint aVersion, int* aaStandby);
        private unsafe delegate int CallbackSetStandby(IntPtr aPtr, uint aVersion, int aaStandby);
        private unsafe delegate int CallbackSourceCount(IntPtr aPtr, uint aVersion, uint* aaSourceCount);
        private unsafe delegate int CallbackSourceIndex(IntPtr aPtr, uint aVersion, uint* aaSourceIndex);
        private unsafe delegate int CallbackSetSourceIndex(IntPtr aPtr, uint aVersion, uint aaSourceIndex);
        private unsafe delegate int CallbackSourceType(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char** aaSourceType);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackType iCallbackType;
        private CallbackModel iCallbackModel;
        private CallbackName iCallbackName;
        private CallbackSetName iCallbackSetName;
        private CallbackRoom iCallbackRoom;
        private CallbackSetRoom iCallbackSetRoom;
        private CallbackStandby iCallbackStandby;
        private CallbackSetStandby iCallbackSetStandby;
        private CallbackSourceCount iCallbackSourceCount;
        private CallbackSourceIndex iCallbackSourceIndex;
        private CallbackSetSourceIndex iCallbackSetSourceIndex;
        private CallbackSourceType iCallbackSourceType;

        public DvServiceLinnCoUkProduct2(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkProduct2Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyProductName(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkProduct2SetPropertyProductName(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductName(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkProduct2GetPropertyProductName(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyProductRoom(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkProduct2SetPropertyProductRoom(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductRoom(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkProduct2GetPropertyProductRoom(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyProductStandby(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkProduct2SetPropertyProductStandby(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductStandby(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkProduct2GetPropertyProductStandby(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyProductSourceIndex(uint aValue)
        {
            if (0 != DvServiceLinnCoUkProduct2SetPropertyProductSourceIndex(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductSourceIndex(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkProduct2GetPropertyProductSourceIndex(iHandle, value);
            }
        }

        protected unsafe void EnableActionType()
        {
            iCallbackType = new CallbackType(DoType);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct2EnableActionType(iHandle, iCallbackType, ptr);
        }

        protected unsafe void EnableActionModel()
        {
            iCallbackModel = new CallbackModel(DoModel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct2EnableActionModel(iHandle, iCallbackModel, ptr);
        }

        protected unsafe void EnableActionName()
        {
            iCallbackName = new CallbackName(DoName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct2EnableActionName(iHandle, iCallbackName, ptr);
        }

        protected unsafe void EnableActionSetName()
        {
            iCallbackSetName = new CallbackSetName(DoSetName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct2EnableActionSetName(iHandle, iCallbackSetName, ptr);
        }

        protected unsafe void EnableActionRoom()
        {
            iCallbackRoom = new CallbackRoom(DoRoom);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct2EnableActionRoom(iHandle, iCallbackRoom, ptr);
        }

        protected unsafe void EnableActionSetRoom()
        {
            iCallbackSetRoom = new CallbackSetRoom(DoSetRoom);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct2EnableActionSetRoom(iHandle, iCallbackSetRoom, ptr);
        }

        protected unsafe void EnableActionStandby()
        {
            iCallbackStandby = new CallbackStandby(DoStandby);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct2EnableActionStandby(iHandle, iCallbackStandby, ptr);
        }

        protected unsafe void EnableActionSetStandby()
        {
            iCallbackSetStandby = new CallbackSetStandby(DoSetStandby);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct2EnableActionSetStandby(iHandle, iCallbackSetStandby, ptr);
        }

        protected unsafe void EnableActionSourceCount()
        {
            iCallbackSourceCount = new CallbackSourceCount(DoSourceCount);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct2EnableActionSourceCount(iHandle, iCallbackSourceCount, ptr);
        }

        protected unsafe void EnableActionSourceIndex()
        {
            iCallbackSourceIndex = new CallbackSourceIndex(DoSourceIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct2EnableActionSourceIndex(iHandle, iCallbackSourceIndex, ptr);
        }

        protected unsafe void EnableActionSetSourceIndex()
        {
            iCallbackSetSourceIndex = new CallbackSetSourceIndex(DoSetSourceIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct2EnableActionSetSourceIndex(iHandle, iCallbackSetSourceIndex, ptr);
        }

        protected unsafe void EnableActionSourceType()
        {
            iCallbackSourceType = new CallbackSourceType(DoSourceType);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct2EnableActionSourceType(iHandle, iCallbackSourceType, ptr);
        }

        protected virtual void Type(uint aVersion, out string aaType)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Model(uint aVersion, out string aaModel)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Name(uint aVersion, out string aaName)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetName(uint aVersion, string aaName)
        {
            throw (new ActionDisabledError());
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

        protected virtual void SourceCount(uint aVersion, out uint aaSourceCount)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SourceIndex(uint aVersion, out uint aaSourceIndex)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetSourceIndex(uint aVersion, uint aaSourceIndex)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SourceType(uint aVersion, uint aaSourceIndex, out string aaSourceType)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoType(IntPtr aPtr, uint aVersion, char** aaType)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct2 self = (DvServiceLinnCoUkProduct2)gch.Target;
            string aType;
            self.Type(aVersion, out aType);
            *aaType = (char*)Marshal.StringToHGlobalAnsi(aType).ToPointer();
            return 0;
        }

        private static unsafe int DoModel(IntPtr aPtr, uint aVersion, char** aaModel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct2 self = (DvServiceLinnCoUkProduct2)gch.Target;
            string aModel;
            self.Model(aVersion, out aModel);
            *aaModel = (char*)Marshal.StringToHGlobalAnsi(aModel).ToPointer();
            return 0;
        }

        private static unsafe int DoName(IntPtr aPtr, uint aVersion, char** aaName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct2 self = (DvServiceLinnCoUkProduct2)gch.Target;
            string aName;
            self.Name(aVersion, out aName);
            *aaName = (char*)Marshal.StringToHGlobalAnsi(aName).ToPointer();
            return 0;
        }

        private static unsafe int DoSetName(IntPtr aPtr, uint aVersion, char* aaName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct2 self = (DvServiceLinnCoUkProduct2)gch.Target;
            string aName = Marshal.PtrToStringAnsi((IntPtr)aaName);
            self.SetName(aVersion, aName);
            return 0;
        }

        private static unsafe int DoRoom(IntPtr aPtr, uint aVersion, char** aaRoom)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct2 self = (DvServiceLinnCoUkProduct2)gch.Target;
            string aRoom;
            self.Room(aVersion, out aRoom);
            *aaRoom = (char*)Marshal.StringToHGlobalAnsi(aRoom).ToPointer();
            return 0;
        }

        private static unsafe int DoSetRoom(IntPtr aPtr, uint aVersion, char* aaRoom)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct2 self = (DvServiceLinnCoUkProduct2)gch.Target;
            string aRoom = Marshal.PtrToStringAnsi((IntPtr)aaRoom);
            self.SetRoom(aVersion, aRoom);
            return 0;
        }

        private static unsafe int DoStandby(IntPtr aPtr, uint aVersion, int* aaStandby)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct2 self = (DvServiceLinnCoUkProduct2)gch.Target;
            bool aStandby;
            self.Standby(aVersion, out aStandby);
            *aaStandby = (aStandby ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetStandby(IntPtr aPtr, uint aVersion, int aaStandby)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct2 self = (DvServiceLinnCoUkProduct2)gch.Target;
            bool aStandby = (aaStandby != 0);
            self.SetStandby(aVersion, aStandby);
            return 0;
        }

        private static unsafe int DoSourceCount(IntPtr aPtr, uint aVersion, uint* aaSourceCount)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct2 self = (DvServiceLinnCoUkProduct2)gch.Target;
            uint aSourceCount;
            self.SourceCount(aVersion, out aSourceCount);
            *aaSourceCount = aSourceCount;
            return 0;
        }

        private static unsafe int DoSourceIndex(IntPtr aPtr, uint aVersion, uint* aaSourceIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct2 self = (DvServiceLinnCoUkProduct2)gch.Target;
            uint aSourceIndex;
            self.SourceIndex(aVersion, out aSourceIndex);
            *aaSourceIndex = aSourceIndex;
            return 0;
        }

        private static unsafe int DoSetSourceIndex(IntPtr aPtr, uint aVersion, uint aaSourceIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct2 self = (DvServiceLinnCoUkProduct2)gch.Target;
            self.SetSourceIndex(aVersion, aaSourceIndex);
            return 0;
        }

        private static unsafe int DoSourceType(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char** aaSourceType)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct2 self = (DvServiceLinnCoUkProduct2)gch.Target;
            string aSourceType;
            self.SourceType(aVersion, aaSourceIndex, out aSourceType);
            *aaSourceType = (char*)Marshal.StringToHGlobalAnsi(aSourceType).ToPointer();
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkProduct2()
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
            DvServiceLinnCoUkProduct2Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

