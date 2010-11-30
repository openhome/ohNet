using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderZappOrgTestWidget1 : IDisposable
    {

        /// <summary>
        /// Set the value of the ReadWriteRegister0 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadWriteRegister0(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister0 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyReadWriteRegister0(out uint aValue);

        /// <summary>
        /// Set the value of the ReadWriteRegister1 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadWriteRegister1(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister1 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyReadWriteRegister1(out uint aValue);

        /// <summary>
        /// Set the value of the ReadWriteRegister2 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadWriteRegister2(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister2 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyReadWriteRegister2(out uint aValue);

        /// <summary>
        /// Set the value of the ReadWriteRegister3 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadWriteRegister3(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister3 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyReadWriteRegister3(out uint aValue);

        /// <summary>
        /// Set the value of the ReadOnlyRegister4 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadOnlyRegister4(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister4 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyReadOnlyRegister4(out uint aValue);

        /// <summary>
        /// Set the value of the ReadOnlyRegister5 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadOnlyRegister5(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister5 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyReadOnlyRegister5(out uint aValue);

        /// <summary>
        /// Set the value of the ReadOnlyRegister6 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadOnlyRegister6(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister6 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyReadOnlyRegister6(out uint aValue);

        /// <summary>
        /// Set the value of the ReadOnlyRegister7 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyReadOnlyRegister7(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister7 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyReadOnlyRegister7(out uint aValue);
        
    }
    /// <summary>
    /// Provider for the zapp.org:TestWidget:1 UPnP service
    /// </summary>
    public class DvProviderZappOrgTestWidget1 : DvProvider, IDisposable, IDvProviderZappOrgTestWidget1
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
        [DllImport("DvZappOrgTestWidget1")]
        static extern void DvProviderZappOrgTestWidget1EnableActionGetWidgetClass(uint aHandle, CallbackGetWidgetClass aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackSetReadWriteRegister(IntPtr aPtr, uint aVersion, uint aRegisterIndex, uint aRegisterValue);
        private unsafe delegate int CallbackGetWidgetClass(IntPtr aPtr, uint aVersion, uint* aWidgetClass);

        private GCHandle iGch;
        private CallbackSetReadWriteRegister iCallbackSetReadWriteRegister;
        private CallbackGetWidgetClass iCallbackGetWidgetClass;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderZappOrgTestWidget1(DvDevice aDevice)
        {
            iHandle = DvProviderZappOrgTestWidget1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the ReadWriteRegister0 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyReadWriteRegister0(uint aValue)
        {
            uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister0(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister0 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyReadWriteRegister0(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister0(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the ReadWriteRegister1 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyReadWriteRegister1(uint aValue)
        {
            uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister1(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister1 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyReadWriteRegister1(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister1(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the ReadWriteRegister2 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyReadWriteRegister2(uint aValue)
        {
            uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister2(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister2 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyReadWriteRegister2(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister2(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the ReadWriteRegister3 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyReadWriteRegister3(uint aValue)
        {
            uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister3(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ReadWriteRegister3 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyReadWriteRegister3(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister3(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the ReadOnlyRegister4 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyReadOnlyRegister4(uint aValue)
        {
            uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister4(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister4 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyReadOnlyRegister4(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister4(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the ReadOnlyRegister5 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyReadOnlyRegister5(uint aValue)
        {
            uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister5(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister5 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyReadOnlyRegister5(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister5(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the ReadOnlyRegister6 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyReadOnlyRegister6(uint aValue)
        {
            uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister6(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister6 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyReadOnlyRegister6(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister6(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the ReadOnlyRegister7 property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyReadOnlyRegister7(uint aValue)
        {
            uint changed;
            if (0 != DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister7(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ReadOnlyRegister7 property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyReadOnlyRegister7(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister7(iHandle, value);
            }
        }

        /// <summary>
        /// Signal that the action SetReadWriteRegister is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetReadWriteRegister must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetReadWriteRegister()
        {
            iCallbackSetReadWriteRegister = new CallbackSetReadWriteRegister(DoSetReadWriteRegister);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestWidget1EnableActionSetReadWriteRegister(iHandle, iCallbackSetReadWriteRegister, ptr);
        }

        /// <summary>
        /// Signal that the action GetWidgetClass is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetWidgetClass must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetWidgetClass()
        {
            iCallbackGetWidgetClass = new CallbackGetWidgetClass(DoGetWidgetClass);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestWidget1EnableActionGetWidgetClass(iHandle, iCallbackGetWidgetClass, ptr);
        }

        /// <summary>
        /// SetReadWriteRegister action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetReadWriteRegister action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetReadWriteRegister was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        protected virtual void SetReadWriteRegister(uint aVersion, uint aRegisterIndex, uint aRegisterValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetWidgetClass action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetWidgetClass action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetWidgetClass was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aWidgetClass"></param>
        protected virtual void GetWidgetClass(uint aVersion, out uint aWidgetClass)
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

        private static unsafe int DoGetWidgetClass(IntPtr aPtr, uint aVersion, uint* aWidgetClass)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidget1 self = (DvProviderZappOrgTestWidget1)gch.Target;
            uint widgetClass;
            self.GetWidgetClass(aVersion, out widgetClass);
            *aWidgetClass = widgetClass;
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

