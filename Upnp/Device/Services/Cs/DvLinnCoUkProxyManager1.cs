using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkProxyManager1 : IDisposable
    {

        /// <summary>
        /// Set the value of the KontrolProductConnected property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyKontrolProductConnected(string aValue);

        /// <summary>
        /// Get a copy of the value of the KontrolProductConnected property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyKontrolProductConnected(out string aValue);

        /// <summary>
        /// Set the value of the KontrolProductComPort property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyKontrolProductComPort(uint aValue);

        /// <summary>
        /// Get a copy of the value of the KontrolProductComPort property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyKontrolProductComPort(out uint aValue);

        /// <summary>
        /// Set the value of the DiscPlayerConnected property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDiscPlayerConnected(string aValue);

        /// <summary>
        /// Get a copy of the value of the DiscPlayerConnected property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyDiscPlayerConnected(out string aValue);

        /// <summary>
        /// Set the value of the DiscPlayerComPort property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDiscPlayerComPort(uint aValue);

        /// <summary>
        /// Get a copy of the value of the DiscPlayerComPort property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyDiscPlayerComPort(out uint aValue);
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:ProxyManager:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkProxyManager1 : DvProvider, IDisposable, IDvProviderLinnCoUkProxyManager1
    {
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern uint DvProviderLinnCoUkProxyManager1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvProviderLinnCoUkProxyManager1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe int DvProviderLinnCoUkProxyManager1SetPropertyKontrolProductConnected(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe void DvProviderLinnCoUkProxyManager1GetPropertyKontrolProductConnected(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe int DvProviderLinnCoUkProxyManager1SetPropertyKontrolProductComPort(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe void DvProviderLinnCoUkProxyManager1GetPropertyKontrolProductComPort(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe int DvProviderLinnCoUkProxyManager1SetPropertyDiscPlayerConnected(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe void DvProviderLinnCoUkProxyManager1GetPropertyDiscPlayerConnected(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe int DvProviderLinnCoUkProxyManager1SetPropertyDiscPlayerComPort(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern unsafe void DvProviderLinnCoUkProxyManager1GetPropertyDiscPlayerComPort(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvProviderLinnCoUkProxyManager1EnableActionKontrolProductConnected(uint aHandle, CallbackKontrolProductConnected aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvProviderLinnCoUkProxyManager1EnableActionSetKontrolProductConnected(uint aHandle, CallbackSetKontrolProductConnected aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvProviderLinnCoUkProxyManager1EnableActionKontrolProductComPort(uint aHandle, CallbackKontrolProductComPort aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvProviderLinnCoUkProxyManager1EnableActionSetKontrolProductComPort(uint aHandle, CallbackSetKontrolProductComPort aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvProviderLinnCoUkProxyManager1EnableActionDiscPlayerConnected(uint aHandle, CallbackDiscPlayerConnected aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvProviderLinnCoUkProxyManager1EnableActionSetDiscPlayerConnected(uint aHandle, CallbackSetDiscPlayerConnected aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvProviderLinnCoUkProxyManager1EnableActionDiscPlayerComPort(uint aHandle, CallbackDiscPlayerComPort aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvProviderLinnCoUkProxyManager1EnableActionSetDiscPlayerComPort(uint aHandle, CallbackSetDiscPlayerComPort aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvProviderLinnCoUkProxyManager1EnableActionTestKontrolProductConnection(uint aHandle, CallbackTestKontrolProductConnection aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkProxyManager1")]
        static extern void DvProviderLinnCoUkProxyManager1EnableActionTestDiscPlayerConnection(uint aHandle, CallbackTestDiscPlayerConnection aCallback, IntPtr aPtr);
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkProxyManager1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkProxyManager1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the KontrolProductConnected property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyKontrolProductConnected(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkProxyManager1SetPropertyKontrolProductConnected(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the KontrolProductConnected property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyKontrolProductConnected(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkProxyManager1GetPropertyKontrolProductConnected(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the KontrolProductComPort property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyKontrolProductComPort(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkProxyManager1SetPropertyKontrolProductComPort(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the KontrolProductComPort property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyKontrolProductComPort(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkProxyManager1GetPropertyKontrolProductComPort(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the DiscPlayerConnected property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyDiscPlayerConnected(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkProxyManager1SetPropertyDiscPlayerConnected(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the DiscPlayerConnected property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyDiscPlayerConnected(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkProxyManager1GetPropertyDiscPlayerConnected(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the DiscPlayerComPort property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyDiscPlayerComPort(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkProxyManager1SetPropertyDiscPlayerComPort(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the DiscPlayerComPort property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyDiscPlayerComPort(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkProxyManager1GetPropertyDiscPlayerComPort(iHandle, value);
            }
        }

        /// <summary>
        /// Signal that the action KontrolProductConnected is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoKontrolProductConnected must be overridden if this is called.</remarks>
        protected unsafe void EnableActionKontrolProductConnected()
        {
            iCallbackKontrolProductConnected = new CallbackKontrolProductConnected(DoKontrolProductConnected);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProxyManager1EnableActionKontrolProductConnected(iHandle, iCallbackKontrolProductConnected, ptr);
        }

        /// <summary>
        /// Signal that the action SetKontrolProductConnected is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetKontrolProductConnected must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetKontrolProductConnected()
        {
            iCallbackSetKontrolProductConnected = new CallbackSetKontrolProductConnected(DoSetKontrolProductConnected);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProxyManager1EnableActionSetKontrolProductConnected(iHandle, iCallbackSetKontrolProductConnected, ptr);
        }

        /// <summary>
        /// Signal that the action KontrolProductComPort is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoKontrolProductComPort must be overridden if this is called.</remarks>
        protected unsafe void EnableActionKontrolProductComPort()
        {
            iCallbackKontrolProductComPort = new CallbackKontrolProductComPort(DoKontrolProductComPort);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProxyManager1EnableActionKontrolProductComPort(iHandle, iCallbackKontrolProductComPort, ptr);
        }

        /// <summary>
        /// Signal that the action SetKontrolProductComPort is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetKontrolProductComPort must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetKontrolProductComPort()
        {
            iCallbackSetKontrolProductComPort = new CallbackSetKontrolProductComPort(DoSetKontrolProductComPort);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProxyManager1EnableActionSetKontrolProductComPort(iHandle, iCallbackSetKontrolProductComPort, ptr);
        }

        /// <summary>
        /// Signal that the action DiscPlayerConnected is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDiscPlayerConnected must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDiscPlayerConnected()
        {
            iCallbackDiscPlayerConnected = new CallbackDiscPlayerConnected(DoDiscPlayerConnected);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProxyManager1EnableActionDiscPlayerConnected(iHandle, iCallbackDiscPlayerConnected, ptr);
        }

        /// <summary>
        /// Signal that the action SetDiscPlayerConnected is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetDiscPlayerConnected must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetDiscPlayerConnected()
        {
            iCallbackSetDiscPlayerConnected = new CallbackSetDiscPlayerConnected(DoSetDiscPlayerConnected);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProxyManager1EnableActionSetDiscPlayerConnected(iHandle, iCallbackSetDiscPlayerConnected, ptr);
        }

        /// <summary>
        /// Signal that the action DiscPlayerComPort is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDiscPlayerComPort must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDiscPlayerComPort()
        {
            iCallbackDiscPlayerComPort = new CallbackDiscPlayerComPort(DoDiscPlayerComPort);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProxyManager1EnableActionDiscPlayerComPort(iHandle, iCallbackDiscPlayerComPort, ptr);
        }

        /// <summary>
        /// Signal that the action SetDiscPlayerComPort is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetDiscPlayerComPort must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetDiscPlayerComPort()
        {
            iCallbackSetDiscPlayerComPort = new CallbackSetDiscPlayerComPort(DoSetDiscPlayerComPort);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProxyManager1EnableActionSetDiscPlayerComPort(iHandle, iCallbackSetDiscPlayerComPort, ptr);
        }

        /// <summary>
        /// Signal that the action TestKontrolProductConnection is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoTestKontrolProductConnection must be overridden if this is called.</remarks>
        protected unsafe void EnableActionTestKontrolProductConnection()
        {
            iCallbackTestKontrolProductConnection = new CallbackTestKontrolProductConnection(DoTestKontrolProductConnection);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProxyManager1EnableActionTestKontrolProductConnection(iHandle, iCallbackTestKontrolProductConnection, ptr);
        }

        /// <summary>
        /// Signal that the action TestDiscPlayerConnection is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoTestDiscPlayerConnection must be overridden if this is called.</remarks>
        protected unsafe void EnableActionTestDiscPlayerConnection()
        {
            iCallbackTestDiscPlayerConnection = new CallbackTestDiscPlayerConnection(DoTestDiscPlayerConnection);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkProxyManager1EnableActionTestDiscPlayerConnection(iHandle, iCallbackTestDiscPlayerConnection, ptr);
        }

        /// <summary>
        /// KontrolProductConnected action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// KontrolProductConnected action for the owning device.
        ///
        /// Must be implemented iff EnableActionKontrolProductConnected was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaConnected"></param>
        protected virtual void KontrolProductConnected(uint aVersion, out string aaConnected)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetKontrolProductConnected action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetKontrolProductConnected action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetKontrolProductConnected was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaConnected"></param>
        protected virtual void SetKontrolProductConnected(uint aVersion, string aaConnected)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// KontrolProductComPort action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// KontrolProductComPort action for the owning device.
        ///
        /// Must be implemented iff EnableActionKontrolProductComPort was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPort"></param>
        protected virtual void KontrolProductComPort(uint aVersion, out uint aaPort)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetKontrolProductComPort action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetKontrolProductComPort action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetKontrolProductComPort was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaConnected"></param>
        protected virtual void SetKontrolProductComPort(uint aVersion, uint aaConnected)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DiscPlayerConnected action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DiscPlayerConnected action for the owning device.
        ///
        /// Must be implemented iff EnableActionDiscPlayerConnected was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaConnected"></param>
        protected virtual void DiscPlayerConnected(uint aVersion, out string aaConnected)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDiscPlayerConnected action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDiscPlayerConnected action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDiscPlayerConnected was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaConnected"></param>
        protected virtual void SetDiscPlayerConnected(uint aVersion, string aaConnected)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DiscPlayerComPort action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DiscPlayerComPort action for the owning device.
        ///
        /// Must be implemented iff EnableActionDiscPlayerComPort was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPort"></param>
        protected virtual void DiscPlayerComPort(uint aVersion, out uint aaPort)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDiscPlayerComPort action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDiscPlayerComPort action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDiscPlayerComPort was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaConnected"></param>
        protected virtual void SetDiscPlayerComPort(uint aVersion, uint aaConnected)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// TestKontrolProductConnection action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// TestKontrolProductConnection action for the owning device.
        ///
        /// Must be implemented iff EnableActionTestKontrolProductConnection was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaResult"></param>
        protected virtual void TestKontrolProductConnection(uint aVersion, out bool aaResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// TestDiscPlayerConnection action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// TestDiscPlayerConnection action for the owning device.
        ///
        /// Must be implemented iff EnableActionTestDiscPlayerConnection was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaResult"></param>
        protected virtual void TestDiscPlayerConnection(uint aVersion, out bool aaResult)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoKontrolProductConnected(IntPtr aPtr, uint aVersion, char** aaConnected)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            string aConnected;
            self.KontrolProductConnected(aVersion, out aConnected);
            *aaConnected = (char*)Marshal.StringToHGlobalAnsi(aConnected).ToPointer();
            return 0;
        }

        private static unsafe int DoSetKontrolProductConnected(IntPtr aPtr, uint aVersion, char* aaConnected)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            string aConnected = Marshal.PtrToStringAnsi((IntPtr)aaConnected);
            self.SetKontrolProductConnected(aVersion, aConnected);
            return 0;
        }

        private static unsafe int DoKontrolProductComPort(IntPtr aPtr, uint aVersion, uint* aaPort)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            uint aPort;
            self.KontrolProductComPort(aVersion, out aPort);
            *aaPort = aPort;
            return 0;
        }

        private static unsafe int DoSetKontrolProductComPort(IntPtr aPtr, uint aVersion, uint aaConnected)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            self.SetKontrolProductComPort(aVersion, aaConnected);
            return 0;
        }

        private static unsafe int DoDiscPlayerConnected(IntPtr aPtr, uint aVersion, char** aaConnected)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            string aConnected;
            self.DiscPlayerConnected(aVersion, out aConnected);
            *aaConnected = (char*)Marshal.StringToHGlobalAnsi(aConnected).ToPointer();
            return 0;
        }

        private static unsafe int DoSetDiscPlayerConnected(IntPtr aPtr, uint aVersion, char* aaConnected)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            string aConnected = Marshal.PtrToStringAnsi((IntPtr)aaConnected);
            self.SetDiscPlayerConnected(aVersion, aConnected);
            return 0;
        }

        private static unsafe int DoDiscPlayerComPort(IntPtr aPtr, uint aVersion, uint* aaPort)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            uint aPort;
            self.DiscPlayerComPort(aVersion, out aPort);
            *aaPort = aPort;
            return 0;
        }

        private static unsafe int DoSetDiscPlayerComPort(IntPtr aPtr, uint aVersion, uint aaConnected)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            self.SetDiscPlayerComPort(aVersion, aaConnected);
            return 0;
        }

        private static unsafe int DoTestKontrolProductConnection(IntPtr aPtr, uint aVersion, int* aaResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            bool aResult;
            self.TestKontrolProductConnection(aVersion, out aResult);
            *aaResult = (aResult ? 1 : 0);
            return 0;
        }

        private static unsafe int DoTestDiscPlayerConnection(IntPtr aPtr, uint aVersion, int* aaResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProxyManager1 self = (DvProviderLinnCoUkProxyManager1)gch.Target;
            bool aResult;
            self.TestDiscPlayerConnection(aVersion, out aResult);
            *aaResult = (aResult ? 1 : 0);
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

        ~DvProviderLinnCoUkProxyManager1()
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
            DvProviderLinnCoUkProxyManager1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

