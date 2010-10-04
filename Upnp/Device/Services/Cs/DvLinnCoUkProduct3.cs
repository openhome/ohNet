using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkProduct3 : IDisposable
    {
        [DllImport("DvLinnCoUkProduct3")]
        static extern uint DvServiceLinnCoUkProduct3Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3Destroy(uint aHandle);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvServiceLinnCoUkProduct3SetPropertyProductType(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvServiceLinnCoUkProduct3GetPropertyProductType(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvServiceLinnCoUkProduct3SetPropertyProductModel(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvServiceLinnCoUkProduct3GetPropertyProductModel(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvServiceLinnCoUkProduct3SetPropertyProductName(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvServiceLinnCoUkProduct3GetPropertyProductName(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvServiceLinnCoUkProduct3SetPropertyProductRoom(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvServiceLinnCoUkProduct3GetPropertyProductRoom(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvServiceLinnCoUkProduct3SetPropertyProductStandby(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvServiceLinnCoUkProduct3GetPropertyProductStandby(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvServiceLinnCoUkProduct3SetPropertyProductSourceIndex(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvServiceLinnCoUkProduct3GetPropertyProductSourceIndex(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvServiceLinnCoUkProduct3SetPropertyProductSourceCount(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvServiceLinnCoUkProduct3GetPropertyProductSourceCount(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvServiceLinnCoUkProduct3SetPropertyProductSourceXml(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvServiceLinnCoUkProduct3GetPropertyProductSourceXml(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvServiceLinnCoUkProduct3SetPropertyStartupSourceIndex(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvServiceLinnCoUkProduct3GetPropertyStartupSourceIndex(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvServiceLinnCoUkProduct3SetPropertyStartupSourceEnabled(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvServiceLinnCoUkProduct3GetPropertyStartupSourceEnabled(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvServiceLinnCoUkProduct3SetPropertyProductAnySourceName(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvServiceLinnCoUkProduct3GetPropertyProductAnySourceName(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvServiceLinnCoUkProduct3SetPropertyProductAnySourceVisible(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvServiceLinnCoUkProduct3GetPropertyProductAnySourceVisible(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvServiceLinnCoUkProduct3SetPropertyProductAnySourceType(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvServiceLinnCoUkProduct3GetPropertyProductAnySourceType(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionType(uint aHandle, CallbackType aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionModel(uint aHandle, CallbackModel aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionName(uint aHandle, CallbackName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSetName(uint aHandle, CallbackSetName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionRoom(uint aHandle, CallbackRoom aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSetRoom(uint aHandle, CallbackSetRoom aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionStandby(uint aHandle, CallbackStandby aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSetStandby(uint aHandle, CallbackSetStandby aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSourceCount(uint aHandle, CallbackSourceCount aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSourceXml(uint aHandle, CallbackSourceXml aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSourceIndex(uint aHandle, CallbackSourceIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSetSourceIndex(uint aHandle, CallbackSetSourceIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSetSourceIndexByName(uint aHandle, CallbackSetSourceIndexByName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSetStartupSourceIndexByName(uint aHandle, CallbackSetStartupSourceIndexByName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionStartupSourceIndex(uint aHandle, CallbackStartupSourceIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSetStartupSourceIndex(uint aHandle, CallbackSetStartupSourceIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionStartupSourceEnabled(uint aHandle, CallbackStartupSourceEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSetStartupSourceEnabled(uint aHandle, CallbackSetStartupSourceEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSourceSystemName(uint aHandle, CallbackSourceSystemName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSourceName(uint aHandle, CallbackSourceName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSetSourceName(uint aHandle, CallbackSetSourceName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSourceType(uint aHandle, CallbackSourceType aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSourceVisible(uint aHandle, CallbackSourceVisible aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvServiceLinnCoUkProduct3EnableActionSetSourceVisible(uint aHandle, CallbackSetSourceVisible aCallback, IntPtr aPtr);
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
        private unsafe delegate int CallbackSourceXml(IntPtr aPtr, uint aVersion, char** aaSourceXml);
        private unsafe delegate int CallbackSourceIndex(IntPtr aPtr, uint aVersion, uint* aaSourceIndex);
        private unsafe delegate int CallbackSetSourceIndex(IntPtr aPtr, uint aVersion, uint aaSourceIndex);
        private unsafe delegate int CallbackSetSourceIndexByName(IntPtr aPtr, uint aVersion, char* aaSourceName);
        private unsafe delegate int CallbackSetStartupSourceIndexByName(IntPtr aPtr, uint aVersion, char* aaSourceName);
        private unsafe delegate int CallbackStartupSourceIndex(IntPtr aPtr, uint aVersion, uint* aaSourceIndex);
        private unsafe delegate int CallbackSetStartupSourceIndex(IntPtr aPtr, uint aVersion, uint aaSourceIndex);
        private unsafe delegate int CallbackStartupSourceEnabled(IntPtr aPtr, uint aVersion, int* aaStartupSourceEnabled);
        private unsafe delegate int CallbackSetStartupSourceEnabled(IntPtr aPtr, uint aVersion, int aaStartupSourceEnabled);
        private unsafe delegate int CallbackSourceSystemName(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char** aaSourceName);
        private unsafe delegate int CallbackSourceName(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char** aaSourceName);
        private unsafe delegate int CallbackSetSourceName(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char* aaSourceName);
        private unsafe delegate int CallbackSourceType(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char** aaSourceType);
        private unsafe delegate int CallbackSourceVisible(IntPtr aPtr, uint aVersion, uint aaSourceIndex, int* aaSourceVisible);
        private unsafe delegate int CallbackSetSourceVisible(IntPtr aPtr, uint aVersion, uint aaSourceIndex, int aaSourceVisible);

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
        private CallbackSourceXml iCallbackSourceXml;
        private CallbackSourceIndex iCallbackSourceIndex;
        private CallbackSetSourceIndex iCallbackSetSourceIndex;
        private CallbackSetSourceIndexByName iCallbackSetSourceIndexByName;
        private CallbackSetStartupSourceIndexByName iCallbackSetStartupSourceIndexByName;
        private CallbackStartupSourceIndex iCallbackStartupSourceIndex;
        private CallbackSetStartupSourceIndex iCallbackSetStartupSourceIndex;
        private CallbackStartupSourceEnabled iCallbackStartupSourceEnabled;
        private CallbackSetStartupSourceEnabled iCallbackSetStartupSourceEnabled;
        private CallbackSourceSystemName iCallbackSourceSystemName;
        private CallbackSourceName iCallbackSourceName;
        private CallbackSetSourceName iCallbackSetSourceName;
        private CallbackSourceType iCallbackSourceType;
        private CallbackSourceVisible iCallbackSourceVisible;
        private CallbackSetSourceVisible iCallbackSetSourceVisible;

        public DvServiceLinnCoUkProduct3(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkProduct3Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyProductType(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkProduct3SetPropertyProductType(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductType(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkProduct3GetPropertyProductType(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyProductModel(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkProduct3SetPropertyProductModel(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductModel(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkProduct3GetPropertyProductModel(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyProductName(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkProduct3SetPropertyProductName(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductName(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkProduct3GetPropertyProductName(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyProductRoom(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkProduct3SetPropertyProductRoom(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductRoom(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkProduct3GetPropertyProductRoom(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyProductStandby(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkProduct3SetPropertyProductStandby(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductStandby(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkProduct3GetPropertyProductStandby(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyProductSourceIndex(uint aValue)
        {
            if (0 != DvServiceLinnCoUkProduct3SetPropertyProductSourceIndex(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductSourceIndex(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkProduct3GetPropertyProductSourceIndex(iHandle, value);
            }
        }

        public unsafe void SetPropertyProductSourceCount(uint aValue)
        {
            if (0 != DvServiceLinnCoUkProduct3SetPropertyProductSourceCount(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductSourceCount(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkProduct3GetPropertyProductSourceCount(iHandle, value);
            }
        }

        public unsafe void SetPropertyProductSourceXml(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkProduct3SetPropertyProductSourceXml(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductSourceXml(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkProduct3GetPropertyProductSourceXml(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyStartupSourceIndex(uint aValue)
        {
            if (0 != DvServiceLinnCoUkProduct3SetPropertyStartupSourceIndex(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyStartupSourceIndex(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkProduct3GetPropertyStartupSourceIndex(iHandle, value);
            }
        }

        public unsafe void SetPropertyStartupSourceEnabled(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkProduct3SetPropertyStartupSourceEnabled(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyStartupSourceEnabled(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkProduct3GetPropertyStartupSourceEnabled(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyProductAnySourceName(uint aValue)
        {
            if (0 != DvServiceLinnCoUkProduct3SetPropertyProductAnySourceName(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductAnySourceName(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkProduct3GetPropertyProductAnySourceName(iHandle, value);
            }
        }

        public unsafe void SetPropertyProductAnySourceVisible(uint aValue)
        {
            if (0 != DvServiceLinnCoUkProduct3SetPropertyProductAnySourceVisible(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductAnySourceVisible(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkProduct3GetPropertyProductAnySourceVisible(iHandle, value);
            }
        }

        public unsafe void SetPropertyProductAnySourceType(uint aValue)
        {
            if (0 != DvServiceLinnCoUkProduct3SetPropertyProductAnySourceType(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyProductAnySourceType(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkProduct3GetPropertyProductAnySourceType(iHandle, value);
            }
        }

        protected unsafe void EnableActionType()
        {
            iCallbackType = new CallbackType(DoType);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionType(iHandle, iCallbackType, ptr);
        }

        protected unsafe void EnableActionModel()
        {
            iCallbackModel = new CallbackModel(DoModel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionModel(iHandle, iCallbackModel, ptr);
        }

        protected unsafe void EnableActionName()
        {
            iCallbackName = new CallbackName(DoName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionName(iHandle, iCallbackName, ptr);
        }

        protected unsafe void EnableActionSetName()
        {
            iCallbackSetName = new CallbackSetName(DoSetName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSetName(iHandle, iCallbackSetName, ptr);
        }

        protected unsafe void EnableActionRoom()
        {
            iCallbackRoom = new CallbackRoom(DoRoom);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionRoom(iHandle, iCallbackRoom, ptr);
        }

        protected unsafe void EnableActionSetRoom()
        {
            iCallbackSetRoom = new CallbackSetRoom(DoSetRoom);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSetRoom(iHandle, iCallbackSetRoom, ptr);
        }

        protected unsafe void EnableActionStandby()
        {
            iCallbackStandby = new CallbackStandby(DoStandby);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionStandby(iHandle, iCallbackStandby, ptr);
        }

        protected unsafe void EnableActionSetStandby()
        {
            iCallbackSetStandby = new CallbackSetStandby(DoSetStandby);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSetStandby(iHandle, iCallbackSetStandby, ptr);
        }

        protected unsafe void EnableActionSourceCount()
        {
            iCallbackSourceCount = new CallbackSourceCount(DoSourceCount);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSourceCount(iHandle, iCallbackSourceCount, ptr);
        }

        protected unsafe void EnableActionSourceXml()
        {
            iCallbackSourceXml = new CallbackSourceXml(DoSourceXml);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSourceXml(iHandle, iCallbackSourceXml, ptr);
        }

        protected unsafe void EnableActionSourceIndex()
        {
            iCallbackSourceIndex = new CallbackSourceIndex(DoSourceIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSourceIndex(iHandle, iCallbackSourceIndex, ptr);
        }

        protected unsafe void EnableActionSetSourceIndex()
        {
            iCallbackSetSourceIndex = new CallbackSetSourceIndex(DoSetSourceIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSetSourceIndex(iHandle, iCallbackSetSourceIndex, ptr);
        }

        protected unsafe void EnableActionSetSourceIndexByName()
        {
            iCallbackSetSourceIndexByName = new CallbackSetSourceIndexByName(DoSetSourceIndexByName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSetSourceIndexByName(iHandle, iCallbackSetSourceIndexByName, ptr);
        }

        protected unsafe void EnableActionSetStartupSourceIndexByName()
        {
            iCallbackSetStartupSourceIndexByName = new CallbackSetStartupSourceIndexByName(DoSetStartupSourceIndexByName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSetStartupSourceIndexByName(iHandle, iCallbackSetStartupSourceIndexByName, ptr);
        }

        protected unsafe void EnableActionStartupSourceIndex()
        {
            iCallbackStartupSourceIndex = new CallbackStartupSourceIndex(DoStartupSourceIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionStartupSourceIndex(iHandle, iCallbackStartupSourceIndex, ptr);
        }

        protected unsafe void EnableActionSetStartupSourceIndex()
        {
            iCallbackSetStartupSourceIndex = new CallbackSetStartupSourceIndex(DoSetStartupSourceIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSetStartupSourceIndex(iHandle, iCallbackSetStartupSourceIndex, ptr);
        }

        protected unsafe void EnableActionStartupSourceEnabled()
        {
            iCallbackStartupSourceEnabled = new CallbackStartupSourceEnabled(DoStartupSourceEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionStartupSourceEnabled(iHandle, iCallbackStartupSourceEnabled, ptr);
        }

        protected unsafe void EnableActionSetStartupSourceEnabled()
        {
            iCallbackSetStartupSourceEnabled = new CallbackSetStartupSourceEnabled(DoSetStartupSourceEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSetStartupSourceEnabled(iHandle, iCallbackSetStartupSourceEnabled, ptr);
        }

        protected unsafe void EnableActionSourceSystemName()
        {
            iCallbackSourceSystemName = new CallbackSourceSystemName(DoSourceSystemName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSourceSystemName(iHandle, iCallbackSourceSystemName, ptr);
        }

        protected unsafe void EnableActionSourceName()
        {
            iCallbackSourceName = new CallbackSourceName(DoSourceName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSourceName(iHandle, iCallbackSourceName, ptr);
        }

        protected unsafe void EnableActionSetSourceName()
        {
            iCallbackSetSourceName = new CallbackSetSourceName(DoSetSourceName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSetSourceName(iHandle, iCallbackSetSourceName, ptr);
        }

        protected unsafe void EnableActionSourceType()
        {
            iCallbackSourceType = new CallbackSourceType(DoSourceType);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSourceType(iHandle, iCallbackSourceType, ptr);
        }

        protected unsafe void EnableActionSourceVisible()
        {
            iCallbackSourceVisible = new CallbackSourceVisible(DoSourceVisible);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSourceVisible(iHandle, iCallbackSourceVisible, ptr);
        }

        protected unsafe void EnableActionSetSourceVisible()
        {
            iCallbackSetSourceVisible = new CallbackSetSourceVisible(DoSetSourceVisible);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkProduct3EnableActionSetSourceVisible(iHandle, iCallbackSetSourceVisible, ptr);
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

        protected virtual void SourceXml(uint aVersion, out string aaSourceXml)
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

        protected virtual void SetSourceIndexByName(uint aVersion, string aaSourceName)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetStartupSourceIndexByName(uint aVersion, string aaSourceName)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void StartupSourceIndex(uint aVersion, out uint aaSourceIndex)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetStartupSourceIndex(uint aVersion, uint aaSourceIndex)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void StartupSourceEnabled(uint aVersion, out bool aaStartupSourceEnabled)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetStartupSourceEnabled(uint aVersion, bool aaStartupSourceEnabled)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SourceSystemName(uint aVersion, uint aaSourceIndex, out string aaSourceName)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SourceName(uint aVersion, uint aaSourceIndex, out string aaSourceName)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetSourceName(uint aVersion, uint aaSourceIndex, string aaSourceName)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SourceType(uint aVersion, uint aaSourceIndex, out string aaSourceType)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SourceVisible(uint aVersion, uint aaSourceIndex, out bool aaSourceVisible)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetSourceVisible(uint aVersion, uint aaSourceIndex, bool aaSourceVisible)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoType(IntPtr aPtr, uint aVersion, char** aaType)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            string aType;
            self.Type(aVersion, out aType);
            *aaType = (char*)Marshal.StringToHGlobalAnsi(aType).ToPointer();
            return 0;
        }

        private static unsafe int DoModel(IntPtr aPtr, uint aVersion, char** aaModel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            string aModel;
            self.Model(aVersion, out aModel);
            *aaModel = (char*)Marshal.StringToHGlobalAnsi(aModel).ToPointer();
            return 0;
        }

        private static unsafe int DoName(IntPtr aPtr, uint aVersion, char** aaName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            string aName;
            self.Name(aVersion, out aName);
            *aaName = (char*)Marshal.StringToHGlobalAnsi(aName).ToPointer();
            return 0;
        }

        private static unsafe int DoSetName(IntPtr aPtr, uint aVersion, char* aaName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            string aName = Marshal.PtrToStringAnsi((IntPtr)aaName);
            self.SetName(aVersion, aName);
            return 0;
        }

        private static unsafe int DoRoom(IntPtr aPtr, uint aVersion, char** aaRoom)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            string aRoom;
            self.Room(aVersion, out aRoom);
            *aaRoom = (char*)Marshal.StringToHGlobalAnsi(aRoom).ToPointer();
            return 0;
        }

        private static unsafe int DoSetRoom(IntPtr aPtr, uint aVersion, char* aaRoom)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            string aRoom = Marshal.PtrToStringAnsi((IntPtr)aaRoom);
            self.SetRoom(aVersion, aRoom);
            return 0;
        }

        private static unsafe int DoStandby(IntPtr aPtr, uint aVersion, int* aaStandby)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            bool aStandby;
            self.Standby(aVersion, out aStandby);
            *aaStandby = (aStandby ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetStandby(IntPtr aPtr, uint aVersion, int aaStandby)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            bool aStandby = (aaStandby != 0);
            self.SetStandby(aVersion, aStandby);
            return 0;
        }

        private static unsafe int DoSourceCount(IntPtr aPtr, uint aVersion, uint* aaSourceCount)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            uint aSourceCount;
            self.SourceCount(aVersion, out aSourceCount);
            *aaSourceCount = aSourceCount;
            return 0;
        }

        private static unsafe int DoSourceXml(IntPtr aPtr, uint aVersion, char** aaSourceXml)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            string aSourceXml;
            self.SourceXml(aVersion, out aSourceXml);
            *aaSourceXml = (char*)Marshal.StringToHGlobalAnsi(aSourceXml).ToPointer();
            return 0;
        }

        private static unsafe int DoSourceIndex(IntPtr aPtr, uint aVersion, uint* aaSourceIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            uint aSourceIndex;
            self.SourceIndex(aVersion, out aSourceIndex);
            *aaSourceIndex = aSourceIndex;
            return 0;
        }

        private static unsafe int DoSetSourceIndex(IntPtr aPtr, uint aVersion, uint aaSourceIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            self.SetSourceIndex(aVersion, aaSourceIndex);
            return 0;
        }

        private static unsafe int DoSetSourceIndexByName(IntPtr aPtr, uint aVersion, char* aaSourceName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            string aSourceName = Marshal.PtrToStringAnsi((IntPtr)aaSourceName);
            self.SetSourceIndexByName(aVersion, aSourceName);
            return 0;
        }

        private static unsafe int DoSetStartupSourceIndexByName(IntPtr aPtr, uint aVersion, char* aaSourceName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            string aSourceName = Marshal.PtrToStringAnsi((IntPtr)aaSourceName);
            self.SetStartupSourceIndexByName(aVersion, aSourceName);
            return 0;
        }

        private static unsafe int DoStartupSourceIndex(IntPtr aPtr, uint aVersion, uint* aaSourceIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            uint aSourceIndex;
            self.StartupSourceIndex(aVersion, out aSourceIndex);
            *aaSourceIndex = aSourceIndex;
            return 0;
        }

        private static unsafe int DoSetStartupSourceIndex(IntPtr aPtr, uint aVersion, uint aaSourceIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            self.SetStartupSourceIndex(aVersion, aaSourceIndex);
            return 0;
        }

        private static unsafe int DoStartupSourceEnabled(IntPtr aPtr, uint aVersion, int* aaStartupSourceEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            bool aStartupSourceEnabled;
            self.StartupSourceEnabled(aVersion, out aStartupSourceEnabled);
            *aaStartupSourceEnabled = (aStartupSourceEnabled ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetStartupSourceEnabled(IntPtr aPtr, uint aVersion, int aaStartupSourceEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            bool aStartupSourceEnabled = (aaStartupSourceEnabled != 0);
            self.SetStartupSourceEnabled(aVersion, aStartupSourceEnabled);
            return 0;
        }

        private static unsafe int DoSourceSystemName(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char** aaSourceName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            string aSourceName;
            self.SourceSystemName(aVersion, aaSourceIndex, out aSourceName);
            *aaSourceName = (char*)Marshal.StringToHGlobalAnsi(aSourceName).ToPointer();
            return 0;
        }

        private static unsafe int DoSourceName(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char** aaSourceName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            string aSourceName;
            self.SourceName(aVersion, aaSourceIndex, out aSourceName);
            *aaSourceName = (char*)Marshal.StringToHGlobalAnsi(aSourceName).ToPointer();
            return 0;
        }

        private static unsafe int DoSetSourceName(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char* aaSourceName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            string aSourceName = Marshal.PtrToStringAnsi((IntPtr)aaSourceName);
            self.SetSourceName(aVersion, aaSourceIndex, aSourceName);
            return 0;
        }

        private static unsafe int DoSourceType(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char** aaSourceType)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            string aSourceType;
            self.SourceType(aVersion, aaSourceIndex, out aSourceType);
            *aaSourceType = (char*)Marshal.StringToHGlobalAnsi(aSourceType).ToPointer();
            return 0;
        }

        private static unsafe int DoSourceVisible(IntPtr aPtr, uint aVersion, uint aaSourceIndex, int* aaSourceVisible)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            bool aSourceVisible;
            self.SourceVisible(aVersion, aaSourceIndex, out aSourceVisible);
            *aaSourceVisible = (aSourceVisible ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetSourceVisible(IntPtr aPtr, uint aVersion, uint aaSourceIndex, int aaSourceVisible)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkProduct3 self = (DvServiceLinnCoUkProduct3)gch.Target;
            bool aSourceVisible = (aaSourceVisible != 0);
            self.SetSourceVisible(aVersion, aaSourceIndex, aSourceVisible);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkProduct3()
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
            DvServiceLinnCoUkProduct3Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

