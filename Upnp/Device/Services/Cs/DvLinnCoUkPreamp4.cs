using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkPreamp4 : IDisposable
    {

        /// <summary>
        /// Set the value of the Volume property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVolume(uint aValue);

        /// <summary>
        /// Get a copy of the value of the Volume property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyVolume(out uint aValue);

        /// <summary>
        /// Set the value of the Mute property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyMute(bool aValue);

        /// <summary>
        /// Get a copy of the value of the Mute property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyMute(out bool aValue);

        /// <summary>
        /// Set the value of the Balance property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyBalance(int aValue);

        /// <summary>
        /// Get a copy of the value of the Balance property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyBalance(out int aValue);

        /// <summary>
        /// Set the value of the VolumeLimit property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVolumeLimit(uint aValue);

        /// <summary>
        /// Get a copy of the value of the VolumeLimit property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyVolumeLimit(out uint aValue);

        /// <summary>
        /// Set the value of the StartupVolume property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyStartupVolume(uint aValue);

        /// <summary>
        /// Get a copy of the value of the StartupVolume property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyStartupVolume(out uint aValue);

        /// <summary>
        /// Set the value of the StartupVolumeEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyStartupVolumeEnabled(bool aValue);

        /// <summary>
        /// Get a copy of the value of the StartupVolumeEnabled property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyStartupVolumeEnabled(out bool aValue);
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Preamp:4 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkPreamp4 : DvProvider, IDisposable
    {
        [DllImport("DvLinnCoUkPreamp4")]
        static extern uint DvProviderLinnCoUkPreamp4Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4Destroy(uint aHandle);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe int DvProviderLinnCoUkPreamp4SetPropertyVolume(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe void DvProviderLinnCoUkPreamp4GetPropertyVolume(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe int DvProviderLinnCoUkPreamp4SetPropertyMute(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe void DvProviderLinnCoUkPreamp4GetPropertyMute(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe int DvProviderLinnCoUkPreamp4SetPropertyBalance(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe void DvProviderLinnCoUkPreamp4GetPropertyBalance(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe int DvProviderLinnCoUkPreamp4SetPropertyVolumeLimit(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe void DvProviderLinnCoUkPreamp4GetPropertyVolumeLimit(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe int DvProviderLinnCoUkPreamp4SetPropertyStartupVolume(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe void DvProviderLinnCoUkPreamp4GetPropertyStartupVolume(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe int DvProviderLinnCoUkPreamp4SetPropertyStartupVolumeEnabled(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern unsafe void DvProviderLinnCoUkPreamp4GetPropertyStartupVolumeEnabled(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4EnableActionVolumeInc(uint aHandle, CallbackVolumeInc aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4EnableActionVolumeDec(uint aHandle, CallbackVolumeDec aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4EnableActionSetVolume(uint aHandle, CallbackSetVolume aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4EnableActionVolume(uint aHandle, CallbackVolume aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4EnableActionSetMute(uint aHandle, CallbackSetMute aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4EnableActionMute(uint aHandle, CallbackMute aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4EnableActionSetBalance(uint aHandle, CallbackSetBalance aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4EnableActionBalance(uint aHandle, CallbackBalance aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4EnableActionSetVolumeLimit(uint aHandle, CallbackSetVolumeLimit aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4EnableActionVolumeLimit(uint aHandle, CallbackVolumeLimit aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4EnableActionSetStartupVolume(uint aHandle, CallbackSetStartupVolume aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4EnableActionStartupVolume(uint aHandle, CallbackStartupVolume aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4EnableActionSetStartupVolumeEnabled(uint aHandle, CallbackSetStartupVolumeEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkPreamp4")]
        static extern void DvProviderLinnCoUkPreamp4EnableActionStartupVolumeEnabled(uint aHandle, CallbackStartupVolumeEnabled aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackVolumeInc(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackVolumeDec(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackSetVolume(IntPtr aPtr, uint aVersion, uint aaVolume);
        private unsafe delegate int CallbackVolume(IntPtr aPtr, uint aVersion, uint* aaVolume);
        private unsafe delegate int CallbackSetMute(IntPtr aPtr, uint aVersion, int aaMute);
        private unsafe delegate int CallbackMute(IntPtr aPtr, uint aVersion, int* aaMute);
        private unsafe delegate int CallbackSetBalance(IntPtr aPtr, uint aVersion, int aaBalance);
        private unsafe delegate int CallbackBalance(IntPtr aPtr, uint aVersion, int* aaBalance);
        private unsafe delegate int CallbackSetVolumeLimit(IntPtr aPtr, uint aVersion, uint aaVolumeLimit);
        private unsafe delegate int CallbackVolumeLimit(IntPtr aPtr, uint aVersion, uint* aaVolumeLimit);
        private unsafe delegate int CallbackSetStartupVolume(IntPtr aPtr, uint aVersion, uint aaStartupVolume);
        private unsafe delegate int CallbackStartupVolume(IntPtr aPtr, uint aVersion, uint* aaStartupVolume);
        private unsafe delegate int CallbackSetStartupVolumeEnabled(IntPtr aPtr, uint aVersion, int aaStartupVolumeEnabled);
        private unsafe delegate int CallbackStartupVolumeEnabled(IntPtr aPtr, uint aVersion, int* aaStartupVolumeEnabled);

        private GCHandle iGch;
        private CallbackVolumeInc iCallbackVolumeInc;
        private CallbackVolumeDec iCallbackVolumeDec;
        private CallbackSetVolume iCallbackSetVolume;
        private CallbackVolume iCallbackVolume;
        private CallbackSetMute iCallbackSetMute;
        private CallbackMute iCallbackMute;
        private CallbackSetBalance iCallbackSetBalance;
        private CallbackBalance iCallbackBalance;
        private CallbackSetVolumeLimit iCallbackSetVolumeLimit;
        private CallbackVolumeLimit iCallbackVolumeLimit;
        private CallbackSetStartupVolume iCallbackSetStartupVolume;
        private CallbackStartupVolume iCallbackStartupVolume;
        private CallbackSetStartupVolumeEnabled iCallbackSetStartupVolumeEnabled;
        private CallbackStartupVolumeEnabled iCallbackStartupVolumeEnabled;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkPreamp4(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkPreamp4Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the Volume property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyVolume(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkPreamp4SetPropertyVolume(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the Volume property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyVolume(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkPreamp4GetPropertyVolume(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the Mute property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyMute(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkPreamp4SetPropertyMute(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the Mute property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyMute(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkPreamp4GetPropertyMute(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the Balance property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyBalance(int aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkPreamp4SetPropertyBalance(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the Balance property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyBalance(out int aValue)
        {
            fixed (int* value = &aValue)
            {
                DvProviderLinnCoUkPreamp4GetPropertyBalance(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the VolumeLimit property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyVolumeLimit(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkPreamp4SetPropertyVolumeLimit(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the VolumeLimit property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyVolumeLimit(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkPreamp4GetPropertyVolumeLimit(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the StartupVolume property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyStartupVolume(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkPreamp4SetPropertyStartupVolume(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the StartupVolume property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyStartupVolume(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkPreamp4GetPropertyStartupVolume(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the StartupVolumeEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyStartupVolumeEnabled(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkPreamp4SetPropertyStartupVolumeEnabled(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the StartupVolumeEnabled property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyStartupVolumeEnabled(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkPreamp4GetPropertyStartupVolumeEnabled(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Signal that the action VolumeInc is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoVolumeInc must be overridden if this is called.</remarks>
        protected unsafe void EnableActionVolumeInc()
        {
            iCallbackVolumeInc = new CallbackVolumeInc(DoVolumeInc);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPreamp4EnableActionVolumeInc(iHandle, iCallbackVolumeInc, ptr);
        }

        /// <summary>
        /// Signal that the action VolumeDec is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoVolumeDec must be overridden if this is called.</remarks>
        protected unsafe void EnableActionVolumeDec()
        {
            iCallbackVolumeDec = new CallbackVolumeDec(DoVolumeDec);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPreamp4EnableActionVolumeDec(iHandle, iCallbackVolumeDec, ptr);
        }

        /// <summary>
        /// Signal that the action SetVolume is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetVolume must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetVolume()
        {
            iCallbackSetVolume = new CallbackSetVolume(DoSetVolume);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPreamp4EnableActionSetVolume(iHandle, iCallbackSetVolume, ptr);
        }

        /// <summary>
        /// Signal that the action Volume is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoVolume must be overridden if this is called.</remarks>
        protected unsafe void EnableActionVolume()
        {
            iCallbackVolume = new CallbackVolume(DoVolume);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPreamp4EnableActionVolume(iHandle, iCallbackVolume, ptr);
        }

        /// <summary>
        /// Signal that the action SetMute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetMute must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetMute()
        {
            iCallbackSetMute = new CallbackSetMute(DoSetMute);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPreamp4EnableActionSetMute(iHandle, iCallbackSetMute, ptr);
        }

        /// <summary>
        /// Signal that the action Mute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoMute must be overridden if this is called.</remarks>
        protected unsafe void EnableActionMute()
        {
            iCallbackMute = new CallbackMute(DoMute);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPreamp4EnableActionMute(iHandle, iCallbackMute, ptr);
        }

        /// <summary>
        /// Signal that the action SetBalance is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetBalance must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetBalance()
        {
            iCallbackSetBalance = new CallbackSetBalance(DoSetBalance);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPreamp4EnableActionSetBalance(iHandle, iCallbackSetBalance, ptr);
        }

        /// <summary>
        /// Signal that the action Balance is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoBalance must be overridden if this is called.</remarks>
        protected unsafe void EnableActionBalance()
        {
            iCallbackBalance = new CallbackBalance(DoBalance);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPreamp4EnableActionBalance(iHandle, iCallbackBalance, ptr);
        }

        /// <summary>
        /// Signal that the action SetVolumeLimit is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetVolumeLimit must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetVolumeLimit()
        {
            iCallbackSetVolumeLimit = new CallbackSetVolumeLimit(DoSetVolumeLimit);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPreamp4EnableActionSetVolumeLimit(iHandle, iCallbackSetVolumeLimit, ptr);
        }

        /// <summary>
        /// Signal that the action VolumeLimit is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoVolumeLimit must be overridden if this is called.</remarks>
        protected unsafe void EnableActionVolumeLimit()
        {
            iCallbackVolumeLimit = new CallbackVolumeLimit(DoVolumeLimit);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPreamp4EnableActionVolumeLimit(iHandle, iCallbackVolumeLimit, ptr);
        }

        /// <summary>
        /// Signal that the action SetStartupVolume is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStartupVolume must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStartupVolume()
        {
            iCallbackSetStartupVolume = new CallbackSetStartupVolume(DoSetStartupVolume);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPreamp4EnableActionSetStartupVolume(iHandle, iCallbackSetStartupVolume, ptr);
        }

        /// <summary>
        /// Signal that the action StartupVolume is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStartupVolume must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStartupVolume()
        {
            iCallbackStartupVolume = new CallbackStartupVolume(DoStartupVolume);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPreamp4EnableActionStartupVolume(iHandle, iCallbackStartupVolume, ptr);
        }

        /// <summary>
        /// Signal that the action SetStartupVolumeEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStartupVolumeEnabled must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStartupVolumeEnabled()
        {
            iCallbackSetStartupVolumeEnabled = new CallbackSetStartupVolumeEnabled(DoSetStartupVolumeEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPreamp4EnableActionSetStartupVolumeEnabled(iHandle, iCallbackSetStartupVolumeEnabled, ptr);
        }

        /// <summary>
        /// Signal that the action StartupVolumeEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStartupVolumeEnabled must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStartupVolumeEnabled()
        {
            iCallbackStartupVolumeEnabled = new CallbackStartupVolumeEnabled(DoStartupVolumeEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkPreamp4EnableActionStartupVolumeEnabled(iHandle, iCallbackStartupVolumeEnabled, ptr);
        }

        /// <summary>
        /// VolumeInc action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// VolumeInc action for the owning device.
        ///
        /// Must be implemented iff EnableActionVolumeInc was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void VolumeInc(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// VolumeDec action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// VolumeDec action for the owning device.
        ///
        /// Must be implemented iff EnableActionVolumeDec was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void VolumeDec(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetVolume action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetVolume action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetVolume was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaVolume"></param>
        protected virtual void SetVolume(uint aVersion, uint aaVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Volume action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Volume action for the owning device.
        ///
        /// Must be implemented iff EnableActionVolume was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaVolume"></param>
        protected virtual void Volume(uint aVersion, out uint aaVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetMute action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetMute action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetMute was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMute"></param>
        protected virtual void SetMute(uint aVersion, bool aaMute)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Mute action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Mute action for the owning device.
        ///
        /// Must be implemented iff EnableActionMute was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMute"></param>
        protected virtual void Mute(uint aVersion, out bool aaMute)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetBalance action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetBalance action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetBalance was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaBalance"></param>
        protected virtual void SetBalance(uint aVersion, int aaBalance)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Balance action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Balance action for the owning device.
        ///
        /// Must be implemented iff EnableActionBalance was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaBalance"></param>
        protected virtual void Balance(uint aVersion, out int aaBalance)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetVolumeLimit action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetVolumeLimit action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetVolumeLimit was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaVolumeLimit"></param>
        protected virtual void SetVolumeLimit(uint aVersion, uint aaVolumeLimit)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// VolumeLimit action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// VolumeLimit action for the owning device.
        ///
        /// Must be implemented iff EnableActionVolumeLimit was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaVolumeLimit"></param>
        protected virtual void VolumeLimit(uint aVersion, out uint aaVolumeLimit)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStartupVolume action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStartupVolume action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStartupVolume was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStartupVolume"></param>
        protected virtual void SetStartupVolume(uint aVersion, uint aaStartupVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StartupVolume action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StartupVolume action for the owning device.
        ///
        /// Must be implemented iff EnableActionStartupVolume was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStartupVolume"></param>
        protected virtual void StartupVolume(uint aVersion, out uint aaStartupVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStartupVolumeEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStartupVolumeEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStartupVolumeEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStartupVolumeEnabled"></param>
        protected virtual void SetStartupVolumeEnabled(uint aVersion, bool aaStartupVolumeEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StartupVolumeEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StartupVolumeEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionStartupVolumeEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStartupVolumeEnabled"></param>
        protected virtual void StartupVolumeEnabled(uint aVersion, out bool aaStartupVolumeEnabled)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoVolumeInc(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            self.VolumeInc(aVersion);
            return 0;
        }

        private static unsafe int DoVolumeDec(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            self.VolumeDec(aVersion);
            return 0;
        }

        private static unsafe int DoSetVolume(IntPtr aPtr, uint aVersion, uint aaVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            self.SetVolume(aVersion, aaVolume);
            return 0;
        }

        private static unsafe int DoVolume(IntPtr aPtr, uint aVersion, uint* aaVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            uint aVolume;
            self.Volume(aVersion, out aVolume);
            *aaVolume = aVolume;
            return 0;
        }

        private static unsafe int DoSetMute(IntPtr aPtr, uint aVersion, int aaMute)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            bool aMute = (aaMute != 0);
            self.SetMute(aVersion, aMute);
            return 0;
        }

        private static unsafe int DoMute(IntPtr aPtr, uint aVersion, int* aaMute)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            bool aMute;
            self.Mute(aVersion, out aMute);
            *aaMute = (aMute ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetBalance(IntPtr aPtr, uint aVersion, int aaBalance)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            self.SetBalance(aVersion, aaBalance);
            return 0;
        }

        private static unsafe int DoBalance(IntPtr aPtr, uint aVersion, int* aaBalance)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            int aBalance;
            self.Balance(aVersion, out aBalance);
            *aaBalance = aBalance;
            return 0;
        }

        private static unsafe int DoSetVolumeLimit(IntPtr aPtr, uint aVersion, uint aaVolumeLimit)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            self.SetVolumeLimit(aVersion, aaVolumeLimit);
            return 0;
        }

        private static unsafe int DoVolumeLimit(IntPtr aPtr, uint aVersion, uint* aaVolumeLimit)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            uint aVolumeLimit;
            self.VolumeLimit(aVersion, out aVolumeLimit);
            *aaVolumeLimit = aVolumeLimit;
            return 0;
        }

        private static unsafe int DoSetStartupVolume(IntPtr aPtr, uint aVersion, uint aaStartupVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            self.SetStartupVolume(aVersion, aaStartupVolume);
            return 0;
        }

        private static unsafe int DoStartupVolume(IntPtr aPtr, uint aVersion, uint* aaStartupVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            uint aStartupVolume;
            self.StartupVolume(aVersion, out aStartupVolume);
            *aaStartupVolume = aStartupVolume;
            return 0;
        }

        private static unsafe int DoSetStartupVolumeEnabled(IntPtr aPtr, uint aVersion, int aaStartupVolumeEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            bool aStartupVolumeEnabled = (aaStartupVolumeEnabled != 0);
            self.SetStartupVolumeEnabled(aVersion, aStartupVolumeEnabled);
            return 0;
        }

        private static unsafe int DoStartupVolumeEnabled(IntPtr aPtr, uint aVersion, int* aaStartupVolumeEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPreamp4 self = (DvProviderLinnCoUkPreamp4)gch.Target;
            bool aStartupVolumeEnabled;
            self.StartupVolumeEnabled(aVersion, out aStartupVolumeEnabled);
            *aaStartupVolumeEnabled = (aStartupVolumeEnabled ? 1 : 0);
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

        ~DvProviderLinnCoUkPreamp4()
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
            DvProviderLinnCoUkPreamp4Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

