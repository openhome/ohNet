using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkProduct2 : IDisposable
    {

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
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Product:2 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkProduct2 : DvProvider, IDisposable
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkProduct2(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkProduct2Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
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
            int err = DvProviderLinnCoUkProduct2SetPropertyProductName(iHandle, value, &changed);
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
            DvProviderLinnCoUkProduct2GetPropertyProductName(iHandle, &value);
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
            int err = DvProviderLinnCoUkProduct2SetPropertyProductRoom(iHandle, value, &changed);
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
            DvProviderLinnCoUkProduct2GetPropertyProductRoom(iHandle, &value);
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
            if (0 != DvProviderLinnCoUkProduct2SetPropertyProductStandby(iHandle, value, &changed))
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
            DvProviderLinnCoUkProduct2GetPropertyProductStandby(iHandle, &value);
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
            if (0 != DvProviderLinnCoUkProduct2SetPropertyProductSourceIndex(iHandle, aValue, &changed))
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
                DvProviderLinnCoUkProduct2GetPropertyProductSourceIndex(iHandle, value);
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
            DvProviderLinnCoUkProduct2EnableActionType(iHandle, iCallbackType, ptr);
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
            DvProviderLinnCoUkProduct2EnableActionModel(iHandle, iCallbackModel, ptr);
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
            DvProviderLinnCoUkProduct2EnableActionName(iHandle, iCallbackName, ptr);
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
            DvProviderLinnCoUkProduct2EnableActionSetName(iHandle, iCallbackSetName, ptr);
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
            DvProviderLinnCoUkProduct2EnableActionRoom(iHandle, iCallbackRoom, ptr);
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
            DvProviderLinnCoUkProduct2EnableActionSetRoom(iHandle, iCallbackSetRoom, ptr);
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
            DvProviderLinnCoUkProduct2EnableActionStandby(iHandle, iCallbackStandby, ptr);
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
            DvProviderLinnCoUkProduct2EnableActionSetStandby(iHandle, iCallbackSetStandby, ptr);
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
            DvProviderLinnCoUkProduct2EnableActionSourceCount(iHandle, iCallbackSourceCount, ptr);
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
            DvProviderLinnCoUkProduct2EnableActionSourceIndex(iHandle, iCallbackSourceIndex, ptr);
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
            DvProviderLinnCoUkProduct2EnableActionSetSourceIndex(iHandle, iCallbackSetSourceIndex, ptr);
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
            DvProviderLinnCoUkProduct2EnableActionSourceType(iHandle, iCallbackSourceType, ptr);
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

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
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

