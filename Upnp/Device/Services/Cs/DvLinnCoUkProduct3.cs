using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkProduct3 : IDisposable
    {

        /// <summary>
        /// Set the value of the ProductType property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductType(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductType property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyProductType(out string aValue);

        /// <summary>
        /// Set the value of the ProductModel property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductModel(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductModel property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyProductModel(out string aValue);

        /// <summary>
        /// Set the value of the ProductName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductName(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyProductName(out string aValue);

        /// <summary>
        /// Set the value of the ProductRoom property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductRoom(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductRoom property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyProductRoom(out string aValue);

        /// <summary>
        /// Set the value of the ProductStandby property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductStandby(bool aValue);

        /// <summary>
        /// Get a copy of the value of the ProductStandby property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyProductStandby(out bool aValue);

        /// <summary>
        /// Set the value of the ProductSourceIndex property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductSourceIndex(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ProductSourceIndex property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyProductSourceIndex(out uint aValue);

        /// <summary>
        /// Set the value of the ProductSourceCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductSourceCount(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ProductSourceCount property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyProductSourceCount(out uint aValue);

        /// <summary>
        /// Set the value of the ProductSourceXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductSourceXml(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductSourceXml property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyProductSourceXml(out string aValue);

        /// <summary>
        /// Set the value of the StartupSourceIndex property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyStartupSourceIndex(uint aValue);

        /// <summary>
        /// Get a copy of the value of the StartupSourceIndex property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyStartupSourceIndex(out uint aValue);

        /// <summary>
        /// Set the value of the StartupSourceEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyStartupSourceEnabled(bool aValue);

        /// <summary>
        /// Get a copy of the value of the StartupSourceEnabled property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyStartupSourceEnabled(out bool aValue);

        /// <summary>
        /// Set the value of the ProductAnySourceName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductAnySourceName(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ProductAnySourceName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyProductAnySourceName(out uint aValue);

        /// <summary>
        /// Set the value of the ProductAnySourceVisible property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductAnySourceVisible(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ProductAnySourceVisible property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyProductAnySourceVisible(out uint aValue);

        /// <summary>
        /// Set the value of the ProductAnySourceType property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductAnySourceType(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ProductAnySourceType property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyProductAnySourceType(out uint aValue);
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Product:3 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkProduct3 : DvProvider, IDisposable
    {
        [DllImport("DvLinnCoUkProduct3")]
        static extern uint DvProviderLinnCoUkProduct3Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3Destroy(uint aHandle);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvProviderLinnCoUkProduct3SetPropertyProductType(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvProviderLinnCoUkProduct3GetPropertyProductType(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvProviderLinnCoUkProduct3SetPropertyProductModel(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvProviderLinnCoUkProduct3GetPropertyProductModel(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvProviderLinnCoUkProduct3SetPropertyProductName(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvProviderLinnCoUkProduct3GetPropertyProductName(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvProviderLinnCoUkProduct3SetPropertyProductRoom(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvProviderLinnCoUkProduct3GetPropertyProductRoom(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvProviderLinnCoUkProduct3SetPropertyProductStandby(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvProviderLinnCoUkProduct3GetPropertyProductStandby(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvProviderLinnCoUkProduct3SetPropertyProductSourceIndex(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvProviderLinnCoUkProduct3GetPropertyProductSourceIndex(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvProviderLinnCoUkProduct3SetPropertyProductSourceCount(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvProviderLinnCoUkProduct3GetPropertyProductSourceCount(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvProviderLinnCoUkProduct3SetPropertyProductSourceXml(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvProviderLinnCoUkProduct3GetPropertyProductSourceXml(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvProviderLinnCoUkProduct3SetPropertyStartupSourceIndex(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvProviderLinnCoUkProduct3GetPropertyStartupSourceIndex(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvProviderLinnCoUkProduct3SetPropertyStartupSourceEnabled(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvProviderLinnCoUkProduct3GetPropertyStartupSourceEnabled(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvProviderLinnCoUkProduct3SetPropertyProductAnySourceName(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceName(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvProviderLinnCoUkProduct3SetPropertyProductAnySourceVisible(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceVisible(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe int DvProviderLinnCoUkProduct3SetPropertyProductAnySourceType(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProduct3")]
        static extern unsafe void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceType(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionType(uint aHandle, CallbackType aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionModel(uint aHandle, CallbackModel aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionName(uint aHandle, CallbackName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSetName(uint aHandle, CallbackSetName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionRoom(uint aHandle, CallbackRoom aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSetRoom(uint aHandle, CallbackSetRoom aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionStandby(uint aHandle, CallbackStandby aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSetStandby(uint aHandle, CallbackSetStandby aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSourceCount(uint aHandle, CallbackSourceCount aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSourceXml(uint aHandle, CallbackSourceXml aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSourceIndex(uint aHandle, CallbackSourceIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSetSourceIndex(uint aHandle, CallbackSetSourceIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSetSourceIndexByName(uint aHandle, CallbackSetSourceIndexByName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceIndexByName(uint aHandle, CallbackSetStartupSourceIndexByName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionStartupSourceIndex(uint aHandle, CallbackStartupSourceIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceIndex(uint aHandle, CallbackSetStartupSourceIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionStartupSourceEnabled(uint aHandle, CallbackStartupSourceEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceEnabled(uint aHandle, CallbackSetStartupSourceEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSourceSystemName(uint aHandle, CallbackSourceSystemName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSourceName(uint aHandle, CallbackSourceName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSetSourceName(uint aHandle, CallbackSetSourceName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSourceType(uint aHandle, CallbackSourceType aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSourceVisible(uint aHandle, CallbackSourceVisible aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProduct3")]
        static extern void DvProviderLinnCoUkProduct3EnableActionSetSourceVisible(uint aHandle, CallbackSetSourceVisible aCallback, IntPtr aPtr);
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkProduct3(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkProduct3Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the ProductType property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyProductType(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkProduct3SetPropertyProductType(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ProductType property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyProductType(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkProduct3GetPropertyProductType(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the ProductModel property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyProductModel(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkProduct3SetPropertyProductModel(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ProductModel property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyProductModel(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkProduct3GetPropertyProductModel(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the ProductName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyProductName(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkProduct3SetPropertyProductName(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ProductName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyProductName(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkProduct3GetPropertyProductName(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the ProductRoom property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyProductRoom(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkProduct3SetPropertyProductRoom(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ProductRoom property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyProductRoom(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkProduct3GetPropertyProductRoom(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the ProductStandby property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyProductStandby(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkProduct3SetPropertyProductStandby(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ProductStandby property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyProductStandby(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkProduct3GetPropertyProductStandby(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the ProductSourceIndex property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyProductSourceIndex(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkProduct3SetPropertyProductSourceIndex(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ProductSourceIndex property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyProductSourceIndex(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkProduct3GetPropertyProductSourceIndex(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the ProductSourceCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyProductSourceCount(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkProduct3SetPropertyProductSourceCount(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ProductSourceCount property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyProductSourceCount(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkProduct3GetPropertyProductSourceCount(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the ProductSourceXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyProductSourceXml(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkProduct3SetPropertyProductSourceXml(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ProductSourceXml property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyProductSourceXml(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkProduct3GetPropertyProductSourceXml(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the StartupSourceIndex property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyStartupSourceIndex(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkProduct3SetPropertyStartupSourceIndex(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the StartupSourceIndex property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyStartupSourceIndex(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkProduct3GetPropertyStartupSourceIndex(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the StartupSourceEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyStartupSourceEnabled(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkProduct3SetPropertyStartupSourceEnabled(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the StartupSourceEnabled property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyStartupSourceEnabled(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkProduct3GetPropertyStartupSourceEnabled(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the ProductAnySourceName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyProductAnySourceName(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkProduct3SetPropertyProductAnySourceName(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ProductAnySourceName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyProductAnySourceName(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkProduct3GetPropertyProductAnySourceName(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the ProductAnySourceVisible property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyProductAnySourceVisible(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkProduct3SetPropertyProductAnySourceVisible(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ProductAnySourceVisible property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyProductAnySourceVisible(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkProduct3GetPropertyProductAnySourceVisible(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the ProductAnySourceType property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyProductAnySourceType(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkProduct3SetPropertyProductAnySourceType(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ProductAnySourceType property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyProductAnySourceType(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkProduct3GetPropertyProductAnySourceType(iHandle, value);
            }
        }

        /// <summary>
        /// Signal that the action Type is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoType must be overridden if this is called.</remarks>
        protected unsafe void EnableActionType()
        {
            iCallbackType = new CallbackType(DoType);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionType(iHandle, iCallbackType, ptr);
        }

        /// <summary>
        /// Signal that the action Model is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoModel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionModel()
        {
            iCallbackModel = new CallbackModel(DoModel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionModel(iHandle, iCallbackModel, ptr);
        }

        /// <summary>
        /// Signal that the action Name is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionName()
        {
            iCallbackName = new CallbackName(DoName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionName(iHandle, iCallbackName, ptr);
        }

        /// <summary>
        /// Signal that the action SetName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetName()
        {
            iCallbackSetName = new CallbackSetName(DoSetName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSetName(iHandle, iCallbackSetName, ptr);
        }

        /// <summary>
        /// Signal that the action Room is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoRoom must be overridden if this is called.</remarks>
        protected unsafe void EnableActionRoom()
        {
            iCallbackRoom = new CallbackRoom(DoRoom);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionRoom(iHandle, iCallbackRoom, ptr);
        }

        /// <summary>
        /// Signal that the action SetRoom is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetRoom must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetRoom()
        {
            iCallbackSetRoom = new CallbackSetRoom(DoSetRoom);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSetRoom(iHandle, iCallbackSetRoom, ptr);
        }

        /// <summary>
        /// Signal that the action Standby is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStandby must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStandby()
        {
            iCallbackStandby = new CallbackStandby(DoStandby);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionStandby(iHandle, iCallbackStandby, ptr);
        }

        /// <summary>
        /// Signal that the action SetStandby is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStandby must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStandby()
        {
            iCallbackSetStandby = new CallbackSetStandby(DoSetStandby);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSetStandby(iHandle, iCallbackSetStandby, ptr);
        }

        /// <summary>
        /// Signal that the action SourceCount is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSourceCount must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSourceCount()
        {
            iCallbackSourceCount = new CallbackSourceCount(DoSourceCount);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSourceCount(iHandle, iCallbackSourceCount, ptr);
        }

        /// <summary>
        /// Signal that the action SourceXml is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSourceXml must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSourceXml()
        {
            iCallbackSourceXml = new CallbackSourceXml(DoSourceXml);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSourceXml(iHandle, iCallbackSourceXml, ptr);
        }

        /// <summary>
        /// Signal that the action SourceIndex is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSourceIndex must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSourceIndex()
        {
            iCallbackSourceIndex = new CallbackSourceIndex(DoSourceIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSourceIndex(iHandle, iCallbackSourceIndex, ptr);
        }

        /// <summary>
        /// Signal that the action SetSourceIndex is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetSourceIndex must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetSourceIndex()
        {
            iCallbackSetSourceIndex = new CallbackSetSourceIndex(DoSetSourceIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSetSourceIndex(iHandle, iCallbackSetSourceIndex, ptr);
        }

        /// <summary>
        /// Signal that the action SetSourceIndexByName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetSourceIndexByName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetSourceIndexByName()
        {
            iCallbackSetSourceIndexByName = new CallbackSetSourceIndexByName(DoSetSourceIndexByName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSetSourceIndexByName(iHandle, iCallbackSetSourceIndexByName, ptr);
        }

        /// <summary>
        /// Signal that the action SetStartupSourceIndexByName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStartupSourceIndexByName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStartupSourceIndexByName()
        {
            iCallbackSetStartupSourceIndexByName = new CallbackSetStartupSourceIndexByName(DoSetStartupSourceIndexByName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSetStartupSourceIndexByName(iHandle, iCallbackSetStartupSourceIndexByName, ptr);
        }

        /// <summary>
        /// Signal that the action StartupSourceIndex is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStartupSourceIndex must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStartupSourceIndex()
        {
            iCallbackStartupSourceIndex = new CallbackStartupSourceIndex(DoStartupSourceIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionStartupSourceIndex(iHandle, iCallbackStartupSourceIndex, ptr);
        }

        /// <summary>
        /// Signal that the action SetStartupSourceIndex is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStartupSourceIndex must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStartupSourceIndex()
        {
            iCallbackSetStartupSourceIndex = new CallbackSetStartupSourceIndex(DoSetStartupSourceIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSetStartupSourceIndex(iHandle, iCallbackSetStartupSourceIndex, ptr);
        }

        /// <summary>
        /// Signal that the action StartupSourceEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStartupSourceEnabled must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStartupSourceEnabled()
        {
            iCallbackStartupSourceEnabled = new CallbackStartupSourceEnabled(DoStartupSourceEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionStartupSourceEnabled(iHandle, iCallbackStartupSourceEnabled, ptr);
        }

        /// <summary>
        /// Signal that the action SetStartupSourceEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStartupSourceEnabled must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStartupSourceEnabled()
        {
            iCallbackSetStartupSourceEnabled = new CallbackSetStartupSourceEnabled(DoSetStartupSourceEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSetStartupSourceEnabled(iHandle, iCallbackSetStartupSourceEnabled, ptr);
        }

        /// <summary>
        /// Signal that the action SourceSystemName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSourceSystemName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSourceSystemName()
        {
            iCallbackSourceSystemName = new CallbackSourceSystemName(DoSourceSystemName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSourceSystemName(iHandle, iCallbackSourceSystemName, ptr);
        }

        /// <summary>
        /// Signal that the action SourceName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSourceName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSourceName()
        {
            iCallbackSourceName = new CallbackSourceName(DoSourceName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSourceName(iHandle, iCallbackSourceName, ptr);
        }

        /// <summary>
        /// Signal that the action SetSourceName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetSourceName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetSourceName()
        {
            iCallbackSetSourceName = new CallbackSetSourceName(DoSetSourceName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSetSourceName(iHandle, iCallbackSetSourceName, ptr);
        }

        /// <summary>
        /// Signal that the action SourceType is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSourceType must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSourceType()
        {
            iCallbackSourceType = new CallbackSourceType(DoSourceType);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSourceType(iHandle, iCallbackSourceType, ptr);
        }

        /// <summary>
        /// Signal that the action SourceVisible is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSourceVisible must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSourceVisible()
        {
            iCallbackSourceVisible = new CallbackSourceVisible(DoSourceVisible);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSourceVisible(iHandle, iCallbackSourceVisible, ptr);
        }

        /// <summary>
        /// Signal that the action SetSourceVisible is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetSourceVisible must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetSourceVisible()
        {
            iCallbackSetSourceVisible = new CallbackSetSourceVisible(DoSetSourceVisible);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProduct3EnableActionSetSourceVisible(iHandle, iCallbackSetSourceVisible, ptr);
        }

        /// <summary>
        /// Type action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Type action for the owning device.
        ///
        /// Must be implemented iff EnableActionType was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaType"></param>
        protected virtual void Type(uint aVersion, out string aaType)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Model action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Model action for the owning device.
        ///
        /// Must be implemented iff EnableActionModel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaModel"></param>
        protected virtual void Model(uint aVersion, out string aaModel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Name action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Name action for the owning device.
        ///
        /// Must be implemented iff EnableActionName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaName"></param>
        protected virtual void Name(uint aVersion, out string aaName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaName"></param>
        protected virtual void SetName(uint aVersion, string aaName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Room action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Room action for the owning device.
        ///
        /// Must be implemented iff EnableActionRoom was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaRoom"></param>
        protected virtual void Room(uint aVersion, out string aaRoom)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetRoom action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetRoom action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetRoom was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaRoom"></param>
        protected virtual void SetRoom(uint aVersion, string aaRoom)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Standby action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Standby action for the owning device.
        ///
        /// Must be implemented iff EnableActionStandby was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStandby"></param>
        protected virtual void Standby(uint aVersion, out bool aaStandby)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStandby action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStandby action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStandby was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStandby"></param>
        protected virtual void SetStandby(uint aVersion, bool aaStandby)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceCount action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceCount action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceCount was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceCount"></param>
        protected virtual void SourceCount(uint aVersion, out uint aaSourceCount)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceXml action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceXml action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceXml was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceXml"></param>
        protected virtual void SourceXml(uint aVersion, out string aaSourceXml)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceIndex action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceIndex action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceIndex was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        protected virtual void SourceIndex(uint aVersion, out uint aaSourceIndex)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetSourceIndex action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetSourceIndex action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetSourceIndex was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        protected virtual void SetSourceIndex(uint aVersion, uint aaSourceIndex)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetSourceIndexByName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetSourceIndexByName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetSourceIndexByName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceName"></param>
        protected virtual void SetSourceIndexByName(uint aVersion, string aaSourceName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStartupSourceIndexByName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStartupSourceIndexByName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStartupSourceIndexByName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceName"></param>
        protected virtual void SetStartupSourceIndexByName(uint aVersion, string aaSourceName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StartupSourceIndex action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StartupSourceIndex action for the owning device.
        ///
        /// Must be implemented iff EnableActionStartupSourceIndex was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        protected virtual void StartupSourceIndex(uint aVersion, out uint aaSourceIndex)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStartupSourceIndex action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStartupSourceIndex action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStartupSourceIndex was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        protected virtual void SetStartupSourceIndex(uint aVersion, uint aaSourceIndex)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StartupSourceEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StartupSourceEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionStartupSourceEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStartupSourceEnabled"></param>
        protected virtual void StartupSourceEnabled(uint aVersion, out bool aaStartupSourceEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStartupSourceEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStartupSourceEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStartupSourceEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStartupSourceEnabled"></param>
        protected virtual void SetStartupSourceEnabled(uint aVersion, bool aaStartupSourceEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceSystemName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceSystemName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceSystemName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceName"></param>
        protected virtual void SourceSystemName(uint aVersion, uint aaSourceIndex, out string aaSourceName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceName"></param>
        protected virtual void SourceName(uint aVersion, uint aaSourceIndex, out string aaSourceName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetSourceName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetSourceName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetSourceName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceName"></param>
        protected virtual void SetSourceName(uint aVersion, uint aaSourceIndex, string aaSourceName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceType action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceType action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceType was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceType"></param>
        protected virtual void SourceType(uint aVersion, uint aaSourceIndex, out string aaSourceType)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceVisible action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceVisible action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceVisible was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceVisible"></param>
        protected virtual void SourceVisible(uint aVersion, uint aaSourceIndex, out bool aaSourceVisible)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetSourceVisible action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetSourceVisible action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetSourceVisible was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceVisible"></param>
        protected virtual void SetSourceVisible(uint aVersion, uint aaSourceIndex, bool aaSourceVisible)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoType(IntPtr aPtr, uint aVersion, char** aaType)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            string aType;
            self.Type(aVersion, out aType);
            *aaType = (char*)Marshal.StringToHGlobalAnsi(aType).ToPointer();
            return 0;
        }

        private static unsafe int DoModel(IntPtr aPtr, uint aVersion, char** aaModel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            string aModel;
            self.Model(aVersion, out aModel);
            *aaModel = (char*)Marshal.StringToHGlobalAnsi(aModel).ToPointer();
            return 0;
        }

        private static unsafe int DoName(IntPtr aPtr, uint aVersion, char** aaName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            string aName;
            self.Name(aVersion, out aName);
            *aaName = (char*)Marshal.StringToHGlobalAnsi(aName).ToPointer();
            return 0;
        }

        private static unsafe int DoSetName(IntPtr aPtr, uint aVersion, char* aaName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            string aName = Marshal.PtrToStringAnsi((IntPtr)aaName);
            self.SetName(aVersion, aName);
            return 0;
        }

        private static unsafe int DoRoom(IntPtr aPtr, uint aVersion, char** aaRoom)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            string aRoom;
            self.Room(aVersion, out aRoom);
            *aaRoom = (char*)Marshal.StringToHGlobalAnsi(aRoom).ToPointer();
            return 0;
        }

        private static unsafe int DoSetRoom(IntPtr aPtr, uint aVersion, char* aaRoom)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            string aRoom = Marshal.PtrToStringAnsi((IntPtr)aaRoom);
            self.SetRoom(aVersion, aRoom);
            return 0;
        }

        private static unsafe int DoStandby(IntPtr aPtr, uint aVersion, int* aaStandby)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            bool aStandby;
            self.Standby(aVersion, out aStandby);
            *aaStandby = (aStandby ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetStandby(IntPtr aPtr, uint aVersion, int aaStandby)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            bool aStandby = (aaStandby != 0);
            self.SetStandby(aVersion, aStandby);
            return 0;
        }

        private static unsafe int DoSourceCount(IntPtr aPtr, uint aVersion, uint* aaSourceCount)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            uint aSourceCount;
            self.SourceCount(aVersion, out aSourceCount);
            *aaSourceCount = aSourceCount;
            return 0;
        }

        private static unsafe int DoSourceXml(IntPtr aPtr, uint aVersion, char** aaSourceXml)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            string aSourceXml;
            self.SourceXml(aVersion, out aSourceXml);
            *aaSourceXml = (char*)Marshal.StringToHGlobalAnsi(aSourceXml).ToPointer();
            return 0;
        }

        private static unsafe int DoSourceIndex(IntPtr aPtr, uint aVersion, uint* aaSourceIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            uint aSourceIndex;
            self.SourceIndex(aVersion, out aSourceIndex);
            *aaSourceIndex = aSourceIndex;
            return 0;
        }

        private static unsafe int DoSetSourceIndex(IntPtr aPtr, uint aVersion, uint aaSourceIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            self.SetSourceIndex(aVersion, aaSourceIndex);
            return 0;
        }

        private static unsafe int DoSetSourceIndexByName(IntPtr aPtr, uint aVersion, char* aaSourceName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            string aSourceName = Marshal.PtrToStringAnsi((IntPtr)aaSourceName);
            self.SetSourceIndexByName(aVersion, aSourceName);
            return 0;
        }

        private static unsafe int DoSetStartupSourceIndexByName(IntPtr aPtr, uint aVersion, char* aaSourceName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            string aSourceName = Marshal.PtrToStringAnsi((IntPtr)aaSourceName);
            self.SetStartupSourceIndexByName(aVersion, aSourceName);
            return 0;
        }

        private static unsafe int DoStartupSourceIndex(IntPtr aPtr, uint aVersion, uint* aaSourceIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            uint aSourceIndex;
            self.StartupSourceIndex(aVersion, out aSourceIndex);
            *aaSourceIndex = aSourceIndex;
            return 0;
        }

        private static unsafe int DoSetStartupSourceIndex(IntPtr aPtr, uint aVersion, uint aaSourceIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            self.SetStartupSourceIndex(aVersion, aaSourceIndex);
            return 0;
        }

        private static unsafe int DoStartupSourceEnabled(IntPtr aPtr, uint aVersion, int* aaStartupSourceEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            bool aStartupSourceEnabled;
            self.StartupSourceEnabled(aVersion, out aStartupSourceEnabled);
            *aaStartupSourceEnabled = (aStartupSourceEnabled ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetStartupSourceEnabled(IntPtr aPtr, uint aVersion, int aaStartupSourceEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            bool aStartupSourceEnabled = (aaStartupSourceEnabled != 0);
            self.SetStartupSourceEnabled(aVersion, aStartupSourceEnabled);
            return 0;
        }

        private static unsafe int DoSourceSystemName(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char** aaSourceName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            string aSourceName;
            self.SourceSystemName(aVersion, aaSourceIndex, out aSourceName);
            *aaSourceName = (char*)Marshal.StringToHGlobalAnsi(aSourceName).ToPointer();
            return 0;
        }

        private static unsafe int DoSourceName(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char** aaSourceName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            string aSourceName;
            self.SourceName(aVersion, aaSourceIndex, out aSourceName);
            *aaSourceName = (char*)Marshal.StringToHGlobalAnsi(aSourceName).ToPointer();
            return 0;
        }

        private static unsafe int DoSetSourceName(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char* aaSourceName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            string aSourceName = Marshal.PtrToStringAnsi((IntPtr)aaSourceName);
            self.SetSourceName(aVersion, aaSourceIndex, aSourceName);
            return 0;
        }

        private static unsafe int DoSourceType(IntPtr aPtr, uint aVersion, uint aaSourceIndex, char** aaSourceType)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            string aSourceType;
            self.SourceType(aVersion, aaSourceIndex, out aSourceType);
            *aaSourceType = (char*)Marshal.StringToHGlobalAnsi(aSourceType).ToPointer();
            return 0;
        }

        private static unsafe int DoSourceVisible(IntPtr aPtr, uint aVersion, uint aaSourceIndex, int* aaSourceVisible)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            bool aSourceVisible;
            self.SourceVisible(aVersion, aaSourceIndex, out aSourceVisible);
            *aaSourceVisible = (aSourceVisible ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetSourceVisible(IntPtr aPtr, uint aVersion, uint aaSourceIndex, int aaSourceVisible)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            bool aSourceVisible = (aaSourceVisible != 0);
            self.SetSourceVisible(aVersion, aaSourceIndex, aSourceVisible);
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderLinnCoUkProduct3()
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
            DvProviderLinnCoUkProduct3Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

