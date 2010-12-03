using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkComponent1 : IDisposable
    {

        /// <summary>
        /// Set the value of the AmplifierEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyAmplifierEnabled(bool aValue);

        /// <summary>
        /// Get a copy of the value of the AmplifierEnabled property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyAmplifierEnabled(out bool aValue);

        /// <summary>
        /// Set the value of the AmplifierAttenuation property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyAmplifierAttenuation(string aValue);

        /// <summary>
        /// Get a copy of the value of the AmplifierAttenuation property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyAmplifierAttenuation(out string aValue);

        /// <summary>
        /// Set the value of the VolumeControlEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVolumeControlEnabled(bool aValue);

        /// <summary>
        /// Get a copy of the value of the VolumeControlEnabled property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyVolumeControlEnabled(out bool aValue);

        /// <summary>
        /// Set the value of the DigitalAudioOutputRaw property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDigitalAudioOutputRaw(bool aValue);

        /// <summary>
        /// Get a copy of the value of the DigitalAudioOutputRaw property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyDigitalAudioOutputRaw(out bool aValue);
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Component:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkComponent1 : DvProvider, IDisposable, IDvProviderLinnCoUkComponent1
    {
        [DllImport("DvLinnCoUkComponent1")]
        static extern uint DvProviderLinnCoUkComponent1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvProviderLinnCoUkComponent1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe int DvProviderLinnCoUkComponent1SetPropertyAmplifierEnabled(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe void DvProviderLinnCoUkComponent1GetPropertyAmplifierEnabled(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe int DvProviderLinnCoUkComponent1SetPropertyAmplifierAttenuation(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe void DvProviderLinnCoUkComponent1GetPropertyAmplifierAttenuation(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe int DvProviderLinnCoUkComponent1SetPropertyVolumeControlEnabled(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe void DvProviderLinnCoUkComponent1GetPropertyVolumeControlEnabled(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe int DvProviderLinnCoUkComponent1SetPropertyDigitalAudioOutputRaw(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe void DvProviderLinnCoUkComponent1GetPropertyDigitalAudioOutputRaw(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvProviderLinnCoUkComponent1EnableActionAmplifierEnabled(uint aHandle, CallbackAmplifierEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvProviderLinnCoUkComponent1EnableActionSetAmplifierEnabled(uint aHandle, CallbackSetAmplifierEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvProviderLinnCoUkComponent1EnableActionAmplifierAttenuation(uint aHandle, CallbackAmplifierAttenuation aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvProviderLinnCoUkComponent1EnableActionSetAmplifierAttenuation(uint aHandle, CallbackSetAmplifierAttenuation aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvProviderLinnCoUkComponent1EnableActionSetVolumeControlEnabled(uint aHandle, CallbackSetVolumeControlEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvProviderLinnCoUkComponent1EnableActionVolumeControlEnabled(uint aHandle, CallbackVolumeControlEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvProviderLinnCoUkComponent1EnableActionSetDigitalAudioOutputRaw(uint aHandle, CallbackSetDigitalAudioOutputRaw aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvProviderLinnCoUkComponent1EnableActionDigitalAudioOutputRaw(uint aHandle, CallbackDigitalAudioOutputRaw aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvProviderLinnCoUkComponent1EnableActionAmplifierOverTemperature(uint aHandle, CallbackAmplifierOverTemperature aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvProviderLinnCoUkComponent1EnableActionEthernetLinkConnected(uint aHandle, CallbackEthernetLinkConnected aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvProviderLinnCoUkComponent1EnableActionLocate(uint aHandle, CallbackLocate aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackAmplifierEnabled(IntPtr aPtr, uint aVersion, int* aaEnabled);
        private unsafe delegate int CallbackSetAmplifierEnabled(IntPtr aPtr, uint aVersion, int aaEnabled);
        private unsafe delegate int CallbackAmplifierAttenuation(IntPtr aPtr, uint aVersion, char** aaAttenuation);
        private unsafe delegate int CallbackSetAmplifierAttenuation(IntPtr aPtr, uint aVersion, char* aaAttenuation);
        private unsafe delegate int CallbackSetVolumeControlEnabled(IntPtr aPtr, uint aVersion, int aaEnabled);
        private unsafe delegate int CallbackVolumeControlEnabled(IntPtr aPtr, uint aVersion, int* aaEnabled);
        private unsafe delegate int CallbackSetDigitalAudioOutputRaw(IntPtr aPtr, uint aVersion, int aaRaw);
        private unsafe delegate int CallbackDigitalAudioOutputRaw(IntPtr aPtr, uint aVersion, int* aaRaw);
        private unsafe delegate int CallbackAmplifierOverTemperature(IntPtr aPtr, uint aVersion, int* aaOverTemperature);
        private unsafe delegate int CallbackEthernetLinkConnected(IntPtr aPtr, uint aVersion, int* aaLinkConnected);
        private unsafe delegate int CallbackLocate(IntPtr aPtr, uint aVersion);

        private GCHandle iGch;
        private CallbackAmplifierEnabled iCallbackAmplifierEnabled;
        private CallbackSetAmplifierEnabled iCallbackSetAmplifierEnabled;
        private CallbackAmplifierAttenuation iCallbackAmplifierAttenuation;
        private CallbackSetAmplifierAttenuation iCallbackSetAmplifierAttenuation;
        private CallbackSetVolumeControlEnabled iCallbackSetVolumeControlEnabled;
        private CallbackVolumeControlEnabled iCallbackVolumeControlEnabled;
        private CallbackSetDigitalAudioOutputRaw iCallbackSetDigitalAudioOutputRaw;
        private CallbackDigitalAudioOutputRaw iCallbackDigitalAudioOutputRaw;
        private CallbackAmplifierOverTemperature iCallbackAmplifierOverTemperature;
        private CallbackEthernetLinkConnected iCallbackEthernetLinkConnected;
        private CallbackLocate iCallbackLocate;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkComponent1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkComponent1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the AmplifierEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyAmplifierEnabled(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkComponent1SetPropertyAmplifierEnabled(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the AmplifierEnabled property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyAmplifierEnabled(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkComponent1GetPropertyAmplifierEnabled(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the AmplifierAttenuation property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyAmplifierAttenuation(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkComponent1SetPropertyAmplifierAttenuation(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the AmplifierAttenuation property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyAmplifierAttenuation(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkComponent1GetPropertyAmplifierAttenuation(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the VolumeControlEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyVolumeControlEnabled(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkComponent1SetPropertyVolumeControlEnabled(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the VolumeControlEnabled property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyVolumeControlEnabled(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkComponent1GetPropertyVolumeControlEnabled(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the DigitalAudioOutputRaw property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyDigitalAudioOutputRaw(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkComponent1SetPropertyDigitalAudioOutputRaw(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the DigitalAudioOutputRaw property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyDigitalAudioOutputRaw(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkComponent1GetPropertyDigitalAudioOutputRaw(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Signal that the action AmplifierEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoAmplifierEnabled must be overridden if this is called.</remarks>
        protected unsafe void EnableActionAmplifierEnabled()
        {
            iCallbackAmplifierEnabled = new CallbackAmplifierEnabled(DoAmplifierEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkComponent1EnableActionAmplifierEnabled(iHandle, iCallbackAmplifierEnabled, ptr);
        }

        /// <summary>
        /// Signal that the action SetAmplifierEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetAmplifierEnabled must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetAmplifierEnabled()
        {
            iCallbackSetAmplifierEnabled = new CallbackSetAmplifierEnabled(DoSetAmplifierEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkComponent1EnableActionSetAmplifierEnabled(iHandle, iCallbackSetAmplifierEnabled, ptr);
        }

        /// <summary>
        /// Signal that the action AmplifierAttenuation is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoAmplifierAttenuation must be overridden if this is called.</remarks>
        protected unsafe void EnableActionAmplifierAttenuation()
        {
            iCallbackAmplifierAttenuation = new CallbackAmplifierAttenuation(DoAmplifierAttenuation);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkComponent1EnableActionAmplifierAttenuation(iHandle, iCallbackAmplifierAttenuation, ptr);
        }

        /// <summary>
        /// Signal that the action SetAmplifierAttenuation is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetAmplifierAttenuation must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetAmplifierAttenuation()
        {
            iCallbackSetAmplifierAttenuation = new CallbackSetAmplifierAttenuation(DoSetAmplifierAttenuation);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkComponent1EnableActionSetAmplifierAttenuation(iHandle, iCallbackSetAmplifierAttenuation, ptr);
        }

        /// <summary>
        /// Signal that the action SetVolumeControlEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetVolumeControlEnabled must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetVolumeControlEnabled()
        {
            iCallbackSetVolumeControlEnabled = new CallbackSetVolumeControlEnabled(DoSetVolumeControlEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkComponent1EnableActionSetVolumeControlEnabled(iHandle, iCallbackSetVolumeControlEnabled, ptr);
        }

        /// <summary>
        /// Signal that the action VolumeControlEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoVolumeControlEnabled must be overridden if this is called.</remarks>
        protected unsafe void EnableActionVolumeControlEnabled()
        {
            iCallbackVolumeControlEnabled = new CallbackVolumeControlEnabled(DoVolumeControlEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkComponent1EnableActionVolumeControlEnabled(iHandle, iCallbackVolumeControlEnabled, ptr);
        }

        /// <summary>
        /// Signal that the action SetDigitalAudioOutputRaw is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetDigitalAudioOutputRaw must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetDigitalAudioOutputRaw()
        {
            iCallbackSetDigitalAudioOutputRaw = new CallbackSetDigitalAudioOutputRaw(DoSetDigitalAudioOutputRaw);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkComponent1EnableActionSetDigitalAudioOutputRaw(iHandle, iCallbackSetDigitalAudioOutputRaw, ptr);
        }

        /// <summary>
        /// Signal that the action DigitalAudioOutputRaw is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDigitalAudioOutputRaw must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDigitalAudioOutputRaw()
        {
            iCallbackDigitalAudioOutputRaw = new CallbackDigitalAudioOutputRaw(DoDigitalAudioOutputRaw);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkComponent1EnableActionDigitalAudioOutputRaw(iHandle, iCallbackDigitalAudioOutputRaw, ptr);
        }

        /// <summary>
        /// Signal that the action AmplifierOverTemperature is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoAmplifierOverTemperature must be overridden if this is called.</remarks>
        protected unsafe void EnableActionAmplifierOverTemperature()
        {
            iCallbackAmplifierOverTemperature = new CallbackAmplifierOverTemperature(DoAmplifierOverTemperature);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkComponent1EnableActionAmplifierOverTemperature(iHandle, iCallbackAmplifierOverTemperature, ptr);
        }

        /// <summary>
        /// Signal that the action EthernetLinkConnected is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoEthernetLinkConnected must be overridden if this is called.</remarks>
        protected unsafe void EnableActionEthernetLinkConnected()
        {
            iCallbackEthernetLinkConnected = new CallbackEthernetLinkConnected(DoEthernetLinkConnected);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkComponent1EnableActionEthernetLinkConnected(iHandle, iCallbackEthernetLinkConnected, ptr);
        }

        /// <summary>
        /// Signal that the action Locate is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoLocate must be overridden if this is called.</remarks>
        protected unsafe void EnableActionLocate()
        {
            iCallbackLocate = new CallbackLocate(DoLocate);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkComponent1EnableActionLocate(iHandle, iCallbackLocate, ptr);
        }

        /// <summary>
        /// AmplifierEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// AmplifierEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionAmplifierEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaEnabled"></param>
        protected virtual void AmplifierEnabled(uint aVersion, out bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetAmplifierEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetAmplifierEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetAmplifierEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaEnabled"></param>
        protected virtual void SetAmplifierEnabled(uint aVersion, bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// AmplifierAttenuation action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// AmplifierAttenuation action for the owning device.
        ///
        /// Must be implemented iff EnableActionAmplifierAttenuation was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaAttenuation"></param>
        protected virtual void AmplifierAttenuation(uint aVersion, out string aaAttenuation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetAmplifierAttenuation action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetAmplifierAttenuation action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetAmplifierAttenuation was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaAttenuation"></param>
        protected virtual void SetAmplifierAttenuation(uint aVersion, string aaAttenuation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetVolumeControlEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetVolumeControlEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetVolumeControlEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaEnabled"></param>
        protected virtual void SetVolumeControlEnabled(uint aVersion, bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// VolumeControlEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// VolumeControlEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionVolumeControlEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaEnabled"></param>
        protected virtual void VolumeControlEnabled(uint aVersion, out bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDigitalAudioOutputRaw action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDigitalAudioOutputRaw action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDigitalAudioOutputRaw was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaRaw"></param>
        protected virtual void SetDigitalAudioOutputRaw(uint aVersion, bool aaRaw)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DigitalAudioOutputRaw action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DigitalAudioOutputRaw action for the owning device.
        ///
        /// Must be implemented iff EnableActionDigitalAudioOutputRaw was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaRaw"></param>
        protected virtual void DigitalAudioOutputRaw(uint aVersion, out bool aaRaw)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// AmplifierOverTemperature action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// AmplifierOverTemperature action for the owning device.
        ///
        /// Must be implemented iff EnableActionAmplifierOverTemperature was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaOverTemperature"></param>
        protected virtual void AmplifierOverTemperature(uint aVersion, out bool aaOverTemperature)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// EthernetLinkConnected action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// EthernetLinkConnected action for the owning device.
        ///
        /// Must be implemented iff EnableActionEthernetLinkConnected was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaLinkConnected"></param>
        protected virtual void EthernetLinkConnected(uint aVersion, out bool aaLinkConnected)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Locate action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Locate action for the owning device.
        ///
        /// Must be implemented iff EnableActionLocate was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Locate(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoAmplifierEnabled(IntPtr aPtr, uint aVersion, int* aaEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            bool aEnabled;
            self.AmplifierEnabled(aVersion, out aEnabled);
            *aaEnabled = (aEnabled ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetAmplifierEnabled(IntPtr aPtr, uint aVersion, int aaEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            bool aEnabled = (aaEnabled != 0);
            self.SetAmplifierEnabled(aVersion, aEnabled);
            return 0;
        }

        private static unsafe int DoAmplifierAttenuation(IntPtr aPtr, uint aVersion, char** aaAttenuation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            string aAttenuation;
            self.AmplifierAttenuation(aVersion, out aAttenuation);
            *aaAttenuation = (char*)Marshal.StringToHGlobalAnsi(aAttenuation).ToPointer();
            return 0;
        }

        private static unsafe int DoSetAmplifierAttenuation(IntPtr aPtr, uint aVersion, char* aaAttenuation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            string aAttenuation = Marshal.PtrToStringAnsi((IntPtr)aaAttenuation);
            self.SetAmplifierAttenuation(aVersion, aAttenuation);
            return 0;
        }

        private static unsafe int DoSetVolumeControlEnabled(IntPtr aPtr, uint aVersion, int aaEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            bool aEnabled = (aaEnabled != 0);
            self.SetVolumeControlEnabled(aVersion, aEnabled);
            return 0;
        }

        private static unsafe int DoVolumeControlEnabled(IntPtr aPtr, uint aVersion, int* aaEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            bool aEnabled;
            self.VolumeControlEnabled(aVersion, out aEnabled);
            *aaEnabled = (aEnabled ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetDigitalAudioOutputRaw(IntPtr aPtr, uint aVersion, int aaRaw)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            bool aRaw = (aaRaw != 0);
            self.SetDigitalAudioOutputRaw(aVersion, aRaw);
            return 0;
        }

        private static unsafe int DoDigitalAudioOutputRaw(IntPtr aPtr, uint aVersion, int* aaRaw)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            bool aRaw;
            self.DigitalAudioOutputRaw(aVersion, out aRaw);
            *aaRaw = (aRaw ? 1 : 0);
            return 0;
        }

        private static unsafe int DoAmplifierOverTemperature(IntPtr aPtr, uint aVersion, int* aaOverTemperature)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            bool aOverTemperature;
            self.AmplifierOverTemperature(aVersion, out aOverTemperature);
            *aaOverTemperature = (aOverTemperature ? 1 : 0);
            return 0;
        }

        private static unsafe int DoEthernetLinkConnected(IntPtr aPtr, uint aVersion, int* aaLinkConnected)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            bool aLinkConnected;
            self.EthernetLinkConnected(aVersion, out aLinkConnected);
            *aaLinkConnected = (aLinkConnected ? 1 : 0);
            return 0;
        }

        private static unsafe int DoLocate(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkComponent1 self = (DvProviderLinnCoUkComponent1)gch.Target;
            self.Locate(aVersion);
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

        ~DvProviderLinnCoUkComponent1()
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
            DvProviderLinnCoUkComponent1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

