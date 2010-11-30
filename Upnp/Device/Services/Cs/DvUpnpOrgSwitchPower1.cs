using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderUpnpOrgSwitchPower1 : IDisposable
    {

        /// <summary>
        /// Set the value of the Status property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyStatus(bool aValue);

        /// <summary>
        /// Get a copy of the value of the Status property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyStatus(out bool aValue);
        
    }
    /// <summary>
    /// Provider for the upnp.org:SwitchPower:1 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgSwitchPower1 : DvProvider, IDisposable, IDvProviderUpnpOrgSwitchPower1
    {
        [DllImport("DvUpnpOrgSwitchPower1")]
        static extern uint DvProviderUpnpOrgSwitchPower1Create(uint aDeviceHandle);
        [DllImport("DvUpnpOrgSwitchPower1")]
        static extern void DvProviderUpnpOrgSwitchPower1Destroy(uint aHandle);
        [DllImport("DvUpnpOrgSwitchPower1")]
        static extern unsafe int DvProviderUpnpOrgSwitchPower1SetPropertyStatus(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvUpnpOrgSwitchPower1")]
        static extern unsafe void DvProviderUpnpOrgSwitchPower1GetPropertyStatus(uint aHandle, int* aValue);
        [DllImport("DvUpnpOrgSwitchPower1")]
        static extern void DvProviderUpnpOrgSwitchPower1EnableActionSetTarget(uint aHandle, CallbackSetTarget aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgSwitchPower1")]
        static extern void DvProviderUpnpOrgSwitchPower1EnableActionGetTarget(uint aHandle, CallbackGetTarget aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgSwitchPower1")]
        static extern void DvProviderUpnpOrgSwitchPower1EnableActionGetStatus(uint aHandle, CallbackGetStatus aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackSetTarget(IntPtr aPtr, uint aVersion, int anewTargetValue);
        private unsafe delegate int CallbackGetTarget(IntPtr aPtr, uint aVersion, int* aRetTargetValue);
        private unsafe delegate int CallbackGetStatus(IntPtr aPtr, uint aVersion, int* aResultStatus);

        private GCHandle iGch;
        private CallbackSetTarget iCallbackSetTarget;
        private CallbackGetTarget iCallbackGetTarget;
        private CallbackGetStatus iCallbackGetStatus;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgSwitchPower1(DvDevice aDevice)
        {
            iHandle = DvProviderUpnpOrgSwitchPower1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the Status property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyStatus(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderUpnpOrgSwitchPower1SetPropertyStatus(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the Status property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyStatus(out bool aValue)
        {
            int value;
            DvProviderUpnpOrgSwitchPower1GetPropertyStatus(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Signal that the action SetTarget is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetTarget must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetTarget()
        {
            iCallbackSetTarget = new CallbackSetTarget(DoSetTarget);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgSwitchPower1EnableActionSetTarget(iHandle, iCallbackSetTarget, ptr);
        }

        /// <summary>
        /// Signal that the action GetTarget is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetTarget must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetTarget()
        {
            iCallbackGetTarget = new CallbackGetTarget(DoGetTarget);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgSwitchPower1EnableActionGetTarget(iHandle, iCallbackGetTarget, ptr);
        }

        /// <summary>
        /// Signal that the action GetStatus is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetStatus must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetStatus()
        {
            iCallbackGetStatus = new CallbackGetStatus(DoGetStatus);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgSwitchPower1EnableActionGetStatus(iHandle, iCallbackGetStatus, ptr);
        }

        /// <summary>
        /// SetTarget action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetTarget action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetTarget was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="anewTargetValue"></param>
        protected virtual void SetTarget(uint aVersion, bool anewTargetValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetTarget action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetTarget action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetTarget was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRetTargetValue"></param>
        protected virtual void GetTarget(uint aVersion, out bool aRetTargetValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetStatus action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetStatus action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetStatus was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aResultStatus"></param>
        protected virtual void GetStatus(uint aVersion, out bool aResultStatus)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSetTarget(IntPtr aPtr, uint aVersion, int anewTargetValue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgSwitchPower1 self = (DvProviderUpnpOrgSwitchPower1)gch.Target;
            bool newTargetValue = (anewTargetValue != 0);
            self.SetTarget(aVersion, newTargetValue);
            return 0;
        }

        private static unsafe int DoGetTarget(IntPtr aPtr, uint aVersion, int* aRetTargetValue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgSwitchPower1 self = (DvProviderUpnpOrgSwitchPower1)gch.Target;
            bool retTargetValue;
            self.GetTarget(aVersion, out retTargetValue);
            *aRetTargetValue = (retTargetValue ? 1 : 0);
            return 0;
        }

        private static unsafe int DoGetStatus(IntPtr aPtr, uint aVersion, int* aResultStatus)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgSwitchPower1 self = (DvProviderUpnpOrgSwitchPower1)gch.Target;
            bool resultStatus;
            self.GetStatus(aVersion, out resultStatus);
            *aResultStatus = (resultStatus ? 1 : 0);
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

        ~DvProviderUpnpOrgSwitchPower1()
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
            DvProviderUpnpOrgSwitchPower1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

