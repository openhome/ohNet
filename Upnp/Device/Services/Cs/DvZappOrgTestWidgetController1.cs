using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    /// <summary>
    /// Provider for the zapp.org:TestWidgetController:1 UPnP service
    /// </summary>
    public class DvProviderZappOrgTestWidgetController1 : DvProvider, IDisposable
    {
        [DllImport("DvZappOrgTestWidgetController1")]
        static extern uint DvProviderZappOrgTestWidgetController1Create(uint aDeviceHandle);
        [DllImport("DvZappOrgTestWidgetController1")]
        static extern void DvProviderZappOrgTestWidgetController1Destroy(uint aHandle);
        [DllImport("DvZappOrgTestWidgetController1")]
        static extern void DvProviderZappOrgTestWidgetController1EnableActionCreateWidget(uint aHandle, CallbackCreateWidget aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestWidgetController1")]
        static extern void DvProviderZappOrgTestWidgetController1EnableActionRemoveWidget(uint aHandle, CallbackRemoveWidget aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestWidgetController1")]
        static extern void DvProviderZappOrgTestWidgetController1EnableActionSetWidgetRegister(uint aHandle, CallbackSetWidgetRegister aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestWidgetController1")]
        static extern void DvProviderZappOrgTestWidgetController1EnableActionGetWidgetRegister(uint aHandle, CallbackGetWidgetRegister aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackCreateWidget(IntPtr aPtr, uint aVersion, char* aWidgetUdn, uint aWidgetClass);
        private unsafe delegate int CallbackRemoveWidget(IntPtr aPtr, uint aVersion, char* aWidgetUdn);
        private unsafe delegate int CallbackSetWidgetRegister(IntPtr aPtr, uint aVersion, char* aWidgetUdn, uint aRegisterIndex, uint aRegisterValue);
        private unsafe delegate int CallbackGetWidgetRegister(IntPtr aPtr, uint aVersion, char* aWidgetUdn, uint aRegisterIndex, uint* aRegisterValue);

        private GCHandle iGch;
        private CallbackCreateWidget iCallbackCreateWidget;
        private CallbackRemoveWidget iCallbackRemoveWidget;
        private CallbackSetWidgetRegister iCallbackSetWidgetRegister;
        private CallbackGetWidgetRegister iCallbackGetWidgetRegister;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderZappOrgTestWidgetController1(DvDevice aDevice)
        {
            iHandle = DvProviderZappOrgTestWidgetController1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Signal that the action CreateWidget is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoCreateWidget must be overridden if this is called.</remarks>
        protected unsafe void EnableActionCreateWidget()
        {
            iCallbackCreateWidget = new CallbackCreateWidget(DoCreateWidget);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestWidgetController1EnableActionCreateWidget(iHandle, iCallbackCreateWidget, ptr);
        }

        /// <summary>
        /// Signal that the action RemoveWidget is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoRemoveWidget must be overridden if this is called.</remarks>
        protected unsafe void EnableActionRemoveWidget()
        {
            iCallbackRemoveWidget = new CallbackRemoveWidget(DoRemoveWidget);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestWidgetController1EnableActionRemoveWidget(iHandle, iCallbackRemoveWidget, ptr);
        }

        /// <summary>
        /// Signal that the action SetWidgetRegister is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetWidgetRegister must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetWidgetRegister()
        {
            iCallbackSetWidgetRegister = new CallbackSetWidgetRegister(DoSetWidgetRegister);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestWidgetController1EnableActionSetWidgetRegister(iHandle, iCallbackSetWidgetRegister, ptr);
        }

        /// <summary>
        /// Signal that the action GetWidgetRegister is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetWidgetRegister must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetWidgetRegister()
        {
            iCallbackGetWidgetRegister = new CallbackGetWidgetRegister(DoGetWidgetRegister);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestWidgetController1EnableActionGetWidgetRegister(iHandle, iCallbackGetWidgetRegister, ptr);
        }

        /// <summary>
        /// CreateWidget action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// CreateWidget action for the owning device.
        ///
        /// Must be implemented iff EnableActionCreateWidget was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aWidgetClass"></param>
        protected virtual void CreateWidget(uint aVersion, string aWidgetUdn, uint aWidgetClass)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// RemoveWidget action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// RemoveWidget action for the owning device.
        ///
        /// Must be implemented iff EnableActionRemoveWidget was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aWidgetUdn"></param>
        protected virtual void RemoveWidget(uint aVersion, string aWidgetUdn)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetWidgetRegister action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetWidgetRegister action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetWidgetRegister was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        protected virtual void SetWidgetRegister(uint aVersion, string aWidgetUdn, uint aRegisterIndex, uint aRegisterValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetWidgetRegister action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetWidgetRegister action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetWidgetRegister was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        protected virtual void GetWidgetRegister(uint aVersion, string aWidgetUdn, uint aRegisterIndex, out uint aRegisterValue)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoCreateWidget(IntPtr aPtr, uint aVersion, char* aWidgetUdn, uint aWidgetClass)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidgetController1 self = (DvProviderZappOrgTestWidgetController1)gch.Target;
            string widgetUdn = Marshal.PtrToStringAnsi((IntPtr)aWidgetUdn);
            self.CreateWidget(aVersion, widgetUdn, aWidgetClass);
            return 0;
        }

        private static unsafe int DoRemoveWidget(IntPtr aPtr, uint aVersion, char* aWidgetUdn)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidgetController1 self = (DvProviderZappOrgTestWidgetController1)gch.Target;
            string widgetUdn = Marshal.PtrToStringAnsi((IntPtr)aWidgetUdn);
            self.RemoveWidget(aVersion, widgetUdn);
            return 0;
        }

        private static unsafe int DoSetWidgetRegister(IntPtr aPtr, uint aVersion, char* aWidgetUdn, uint aRegisterIndex, uint aRegisterValue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidgetController1 self = (DvProviderZappOrgTestWidgetController1)gch.Target;
            string widgetUdn = Marshal.PtrToStringAnsi((IntPtr)aWidgetUdn);
            self.SetWidgetRegister(aVersion, widgetUdn, aRegisterIndex, aRegisterValue);
            return 0;
        }

        private static unsafe int DoGetWidgetRegister(IntPtr aPtr, uint aVersion, char* aWidgetUdn, uint aRegisterIndex, uint* aRegisterValue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidgetController1 self = (DvProviderZappOrgTestWidgetController1)gch.Target;
            string widgetUdn = Marshal.PtrToStringAnsi((IntPtr)aWidgetUdn);
            uint registerValue;
            self.GetWidgetRegister(aVersion, widgetUdn, aRegisterIndex, out registerValue);
            *aRegisterValue = registerValue;
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

        ~DvProviderZappOrgTestWidgetController1()
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
            DvProviderZappOrgTestWidgetController1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

