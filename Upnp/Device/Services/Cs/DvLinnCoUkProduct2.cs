using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvProviderLinnCoUkProduct2 : IDisposable
    {
        [DllImport("DvLinnCoUkProduct2")]
        static extern uint DvProviderLinnCoUkProduct2Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvProviderLinnCoUkProduct2Destroy(uint aHandle);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe int DvProviderLinnCoUkProduct2SetPropertyProductName(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe void DvProviderLinnCoUkProduct2GetPropertyProductName(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe int DvProviderLinnCoUkProduct2SetPropertyProductRoom(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe void DvProviderLinnCoUkProduct2GetPropertyProductRoom(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe int DvProviderLinnCoUkProduct2SetPropertyProductStandby(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe void DvProviderLinnCoUkProduct2GetPropertyProductStandby(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe int DvProviderLinnCoUkProduct2SetPropertyProductSourceIndex(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct2")]
        static extern unsafe void DvProviderLinnCoUkProduct2GetPropertyProductSourceIndex(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvProviderLinnCoUkProduct2EnableActionType(uint aHandle, CallbackType aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvProviderLinnCoUkProduct2EnableActionModel(uint aHandle, CallbackModel aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvProviderLinnCoUkProduct2EnableActionName(uint aHandle, CallbackName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvProviderLinnCoUkProduct2EnableActionSetName(uint aHandle, CallbackSetName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvProviderLinnCoUkProduct2EnableActionRoom(uint aHandle, CallbackRoom aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvProviderLinnCoUkProduct2EnableActionSetRoom(uint aHandle, CallbackSetRoom aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvProviderLinnCoUkProduct2EnableActionStandby(uint aHandle, CallbackStandby aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvProviderLinnCoUkProduct2EnableActionSetStandby(uint aHandle, CallbackSetStandby aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvProviderLinnCoUkProduct2EnableActionSourceCount(uint aHandle, CallbackSourceCount aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvProviderLinnCoUkProduct2EnableActionSourceIndex(uint aHandle, CallbackSourceIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvProviderLinnCoUkProduct2EnableActionSetSourceIndex(uint aHandle, CallbackSetSourceIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct2")]
        static extern void DvProviderLinnCoUkProduct2EnableActionSourceType(uint aHandle, CallbackSourceType aCallback, IntPtr aPtr);
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

        public DvProviderLinnCoUkProduct2(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkProduct2Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe bool SetPropertyProductName(string aValue)
        {
        uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkProduct2SetPropertyProductName(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyProductName(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkProduct2GetPropertyProductName(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe bool SetPropertyProductRoom(string aValue)
        {
        uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkProduct2SetPropertyProductRoom(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyProductRoom(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkProduct2GetPropertyProductRoom(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe bool SetPropertyProductStandby(bool aValue)
        {
        uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkProduct2SetPropertyProductStandby(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyProductStandby(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkProduct2GetPropertyProductStandby(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe bool SetPropertyProductSourceIndex(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkProduct2SetPropertyProductSourceIndex(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyProductSourceIndex(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkProduct2GetPropertyProductSourceIndex(iHandle, value);
            }
        }

        protected unsafe void EnableActionType()
        {
            iCallbackType = new CallbackType(DoType);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct2EnableActionType(iHandle, iCallbackType, ptr);
        }

        protected unsafe void EnableActionModel()
        {
            iCallbackModel = new CallbackModel(DoModel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct2EnableActionModel(iHandle, iCallbackModel, ptr);
        }

        protected unsafe void EnableActionName()
        {
            iCallbackName = new CallbackName(DoName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct2EnableActionName(iHandle, iCallbackName, ptr);
        }

        protected unsafe void EnableActionSetName()
        {
            iCallbackSetName = new CallbackSetName(DoSetName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct2EnableActionSetName(iHandle, iCallbackSetName, ptr);
        }

        protected unsafe void EnableActionRoom()
        {
            iCallbackRoom = new CallbackRoom(DoRoom);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct2EnableActionRoom(iHandle, iCallbackRoom, ptr);
        }

        protected unsafe void EnableActionSetRoom()
        {
            iCallbackSetRoom = new CallbackSetRoom(DoSetRoom);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct2EnableActionSetRoom(iHandle, iCallbackSetRoom, ptr);
        }

        protected unsafe void EnableActionStandby()
        {
            iCallbackStandby = new CallbackStandby(DoStandby);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct2EnableActionStandby(iHandle, iCallbackStandby, ptr);
        }

        protected unsafe void EnableActionSetStandby()
        {
            iCallbackSetStandby = new CallbackSetStandby(DoSetStandby);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct2EnableActionSetStandby(iHandle, iCallbackSetStandby, ptr);
        }

        protected unsafe void EnableActionSourceCount()
        {
            iCallbackSourceCount = new CallbackSourceCount(DoSourceCount);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct2EnableActionSourceCount(iHandle, iCallbackSourceCount, ptr);
        }

        protected unsafe void EnableActionSourceIndex()
        {
            iCallbackSourceIndex = new CallbackSourceIndex(DoSourceIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct2EnableActionSourceIndex(iHandle, iCallbackSourceIndex, ptr);
        }

        protected unsafe void EnableActionSetSourceIndex()
        {
            iCallbackSetSourceIndex = new CallbackSetSourceIndex(DoSetSourceIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct2EnableActionSetSourceIndex(iHandle, iCallbackSetSourceIndex, ptr);
        }

        protected unsafe void EnableActionSourceType()
        {
            iCallbackSourceType = new CallbackSourceType(DoSourceType);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct2EnableActionSourceType(iHandle, iCallbackSourceType, ptr);
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
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            string aType;
            self.Type(aVersion, out aType);
            *aaType = (char*)Marshal.StringToHGlobalAnsi(aType).ToPointer();
            return 0;
        }

        private static unsafe int DoModel(IntPtr aPtr, uint aVersion, char** aaModel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            string aModel;
            self.Model(aVersion, out aModel);
            *aaModel = (char*)Marshal.StringToHGlobalAnsi(aModel).ToPointer();
            return 0;
        }

        private static unsafe int DoName(IntPtr aPtr, uint aVersion, char** aaName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            string aName;
            self.Name(aVersion, out aName);
            *aaName = (char*)Marshal.StringToHGlobalAnsi(aName).ToPointer();
            return 0;
        }

        private static unsafe int DoSetName(IntPtr aPtr, uint aVersion, char* aaName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            string aName = Marshal.PtrToStringAnsi((IntPtr)aaName);
            self.SetName(aVersion, aName);
            return 0;
        }

        private static unsafe int DoRoom(IntPtr aPtr, uint aVersion, char** aaRoom)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            string aRoom;
            self.Room(aVersion, out aRoom);
            *aaRoom = (char*)Marshal.StringToHGlobalAnsi(aRoom).ToPointer();
            return 0;
        }

        private static unsafe int DoSetRoom(IntPtr aPtr, uint aVersion, char* aaRoom)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            string aRoom = Marshal.PtrToStringAnsi((IntPtr)aaRoom);
            self.SetRoom(aVersion, aRoom);
            return 0;
        }

        private static unsafe int DoStandby(IntPtr aPtr, uint aVersion, int* aaStandby)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            bool aStandby;
            self.Standby(aVersion, out aStandby);
            *aaStandby = (aStandby ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetStandby(IntPtr aPtr, uint aVersion, int aaStandby)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            bool aStandby = (aaStandby != 0);
            self.SetStandby(aVersion, aStandby);
            return 0;
        }

        private static unsafe int DoSourceCount(IntPtr aPtr, uint aVersion, uint* aaSourceCount)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            uint aSourceCount;
            self.SourceCount(aVersion, out aSourceCount);
            *aaSourceCount = aSourceCount;
            return 0;
        }

        private static unsafe int DoSourceIndex(IntPtr aPtr, uint aVersion, uint* aaSourceIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            uint aSourceIndex;
            self.SourceIndex(aVersion, out aSourceIndex);
            *aaSourceIndex = aSourceIndex;
            return 0;
        }

        private static unsafe int DoSetSourceIndex(IntPtr aPtr, uint aVersion, uint aaSourceIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            self.SetSourceIndex(aVersion, aaSourceIndex);
            return 0;
        }

        private static unsafe int DoSourceType(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char** aaSourceType)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
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

        ~DvProviderLinnCoUkProduct2()
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
            DvProviderLinnCoUkProduct2Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

