using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkConfiguration1 : IDisposable
    {

        /// <summary>
        /// Set the value of the ConfigurationXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyConfigurationXml(string aValue);

        /// <summary>
        /// Get a copy of the value of the ConfigurationXml property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyConfigurationXml(out string aValue);

        /// <summary>
        /// Set the value of the ParameterXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyParameterXml(string aValue);

        /// <summary>
        /// Get a copy of the value of the ParameterXml property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyParameterXml(out string aValue);
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Configuration:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkConfiguration1 : DvProvider, IDisposable, IDvProviderLinnCoUkConfiguration1
    {
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern uint DvProviderLinnCoUkConfiguration1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern void DvProviderLinnCoUkConfiguration1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern unsafe int DvProviderLinnCoUkConfiguration1SetPropertyConfigurationXml(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern unsafe void DvProviderLinnCoUkConfiguration1GetPropertyConfigurationXml(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern unsafe int DvProviderLinnCoUkConfiguration1SetPropertyParameterXml(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern unsafe void DvProviderLinnCoUkConfiguration1GetPropertyParameterXml(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern void DvProviderLinnCoUkConfiguration1EnableActionConfigurationXml(uint aHandle, CallbackConfigurationXml aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern void DvProviderLinnCoUkConfiguration1EnableActionParameterXml(uint aHandle, CallbackParameterXml aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern void DvProviderLinnCoUkConfiguration1EnableActionSetParameter(uint aHandle, CallbackSetParameter aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackConfigurationXml(IntPtr aPtr, uint aVersion, char** aaConfigurationXml);
        private unsafe delegate int CallbackParameterXml(IntPtr aPtr, uint aVersion, char** aaParameterXml);
        private unsafe delegate int CallbackSetParameter(IntPtr aPtr, uint aVersion, char* aaTarget, char* aaName, char* aaValue);

        private GCHandle iGch;
        private CallbackConfigurationXml iCallbackConfigurationXml;
        private CallbackParameterXml iCallbackParameterXml;
        private CallbackSetParameter iCallbackSetParameter;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkConfiguration1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkConfiguration1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the ConfigurationXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyConfigurationXml(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkConfiguration1SetPropertyConfigurationXml(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ConfigurationXml property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyConfigurationXml(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkConfiguration1GetPropertyConfigurationXml(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the ParameterXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyParameterXml(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkConfiguration1SetPropertyParameterXml(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ParameterXml property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyParameterXml(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkConfiguration1GetPropertyParameterXml(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Signal that the action ConfigurationXml is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoConfigurationXml must be overridden if this is called.</remarks>
        protected unsafe void EnableActionConfigurationXml()
        {
            iCallbackConfigurationXml = new CallbackConfigurationXml(DoConfigurationXml);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkConfiguration1EnableActionConfigurationXml(iHandle, iCallbackConfigurationXml, ptr);
        }

        /// <summary>
        /// Signal that the action ParameterXml is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoParameterXml must be overridden if this is called.</remarks>
        protected unsafe void EnableActionParameterXml()
        {
            iCallbackParameterXml = new CallbackParameterXml(DoParameterXml);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkConfiguration1EnableActionParameterXml(iHandle, iCallbackParameterXml, ptr);
        }

        /// <summary>
        /// Signal that the action SetParameter is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetParameter must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetParameter()
        {
            iCallbackSetParameter = new CallbackSetParameter(DoSetParameter);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkConfiguration1EnableActionSetParameter(iHandle, iCallbackSetParameter, ptr);
        }

        /// <summary>
        /// ConfigurationXml action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ConfigurationXml action for the owning device.
        ///
        /// Must be implemented iff EnableActionConfigurationXml was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaConfigurationXml"></param>
        protected virtual void ConfigurationXml(uint aVersion, out string aaConfigurationXml)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ParameterXml action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ParameterXml action for the owning device.
        ///
        /// Must be implemented iff EnableActionParameterXml was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaParameterXml"></param>
        protected virtual void ParameterXml(uint aVersion, out string aaParameterXml)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetParameter action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetParameter action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetParameter was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTarget"></param>
        /// <param name="aaName"></param>
        /// <param name="aaValue"></param>
        protected virtual void SetParameter(uint aVersion, string aaTarget, string aaName, string aaValue)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoConfigurationXml(IntPtr aPtr, uint aVersion, char** aaConfigurationXml)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkConfiguration1 self = (DvProviderLinnCoUkConfiguration1)gch.Target;
            string aConfigurationXml;
            self.ConfigurationXml(aVersion, out aConfigurationXml);
            *aaConfigurationXml = (char*)Marshal.StringToHGlobalAnsi(aConfigurationXml).ToPointer();
            return 0;
        }

        private static unsafe int DoParameterXml(IntPtr aPtr, uint aVersion, char** aaParameterXml)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkConfiguration1 self = (DvProviderLinnCoUkConfiguration1)gch.Target;
            string aParameterXml;
            self.ParameterXml(aVersion, out aParameterXml);
            *aaParameterXml = (char*)Marshal.StringToHGlobalAnsi(aParameterXml).ToPointer();
            return 0;
        }

        private static unsafe int DoSetParameter(IntPtr aPtr, uint aVersion, char* aaTarget, char* aaName, char* aaValue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkConfiguration1 self = (DvProviderLinnCoUkConfiguration1)gch.Target;
            string aTarget = Marshal.PtrToStringAnsi((IntPtr)aaTarget);
            string aName = Marshal.PtrToStringAnsi((IntPtr)aaName);
            string aValue = Marshal.PtrToStringAnsi((IntPtr)aaValue);
            self.SetParameter(aVersion, aTarget, aName, aValue);
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

        ~DvProviderLinnCoUkConfiguration1()
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
            DvProviderLinnCoUkConfiguration1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

