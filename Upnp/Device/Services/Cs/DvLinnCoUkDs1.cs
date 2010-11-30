using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    /// <summary>
    /// Provider for the linn.co.uk:Ds:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkDs1 : DvProvider, IDisposable
    {
        [DllImport("DvLinnCoUkDs1")]
        static extern uint DvProviderLinnCoUkDs1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkDs1")]
        static extern void DvProviderLinnCoUkDs1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe int DvProviderLinnCoUkDs1SetPropertySupportedProtocols(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe void DvProviderLinnCoUkDs1GetPropertySupportedProtocols(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe int DvProviderLinnCoUkDs1SetPropertyTrackDuration(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe void DvProviderLinnCoUkDs1GetPropertyTrackDuration(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe int DvProviderLinnCoUkDs1SetPropertyTrackBitRate(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe void DvProviderLinnCoUkDs1GetPropertyTrackBitRate(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe int DvProviderLinnCoUkDs1SetPropertyTrackLossless(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe void DvProviderLinnCoUkDs1GetPropertyTrackLossless(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe int DvProviderLinnCoUkDs1SetPropertyTrackBitDepth(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe void DvProviderLinnCoUkDs1GetPropertyTrackBitDepth(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe int DvProviderLinnCoUkDs1SetPropertyTrackSampleRate(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe void DvProviderLinnCoUkDs1GetPropertyTrackSampleRate(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe int DvProviderLinnCoUkDs1SetPropertyTrackCodecName(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe void DvProviderLinnCoUkDs1GetPropertyTrackCodecName(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe int DvProviderLinnCoUkDs1SetPropertyTrackId(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe void DvProviderLinnCoUkDs1GetPropertyTrackId(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe int DvProviderLinnCoUkDs1SetPropertyTransportState(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkDs1")]
        static extern unsafe void DvProviderLinnCoUkDs1GetPropertyTransportState(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkDs1")]
        static extern void DvProviderLinnCoUkDs1EnableActionPlay(uint aHandle, CallbackPlay aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDs1")]
        static extern void DvProviderLinnCoUkDs1EnableActionPause(uint aHandle, CallbackPause aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDs1")]
        static extern void DvProviderLinnCoUkDs1EnableActionStop(uint aHandle, CallbackStop aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDs1")]
        static extern void DvProviderLinnCoUkDs1EnableActionSeekSecondAbsolute(uint aHandle, CallbackSeekSecondAbsolute aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDs1")]
        static extern void DvProviderLinnCoUkDs1EnableActionSeekSecondRelative(uint aHandle, CallbackSeekSecondRelative aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDs1")]
        static extern void DvProviderLinnCoUkDs1EnableActionSeekTrackId(uint aHandle, CallbackSeekTrackId aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDs1")]
        static extern void DvProviderLinnCoUkDs1EnableActionSeekTrackAbsolute(uint aHandle, CallbackSeekTrackAbsolute aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDs1")]
        static extern void DvProviderLinnCoUkDs1EnableActionSeekTrackRelative(uint aHandle, CallbackSeekTrackRelative aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDs1")]
        static extern void DvProviderLinnCoUkDs1EnableActionState(uint aHandle, CallbackState aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDs1")]
        static extern void DvProviderLinnCoUkDs1EnableActionProtocolInfo(uint aHandle, CallbackProtocolInfo aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackPlay(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackPause(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackStop(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackSeekSecondAbsolute(IntPtr aPtr, uint aVersion, uint aaSecond);
        private unsafe delegate int CallbackSeekSecondRelative(IntPtr aPtr, uint aVersion, int aaSecond);
        private unsafe delegate int CallbackSeekTrackId(IntPtr aPtr, uint aVersion, uint aaTrackId);
        private unsafe delegate int CallbackSeekTrackAbsolute(IntPtr aPtr, uint aVersion, uint aaTrack);
        private unsafe delegate int CallbackSeekTrackRelative(IntPtr aPtr, uint aVersion, int aaTrack);
        private unsafe delegate int CallbackState(IntPtr aPtr, uint aVersion, char** aaTransportState, uint* aaTrackDuration, uint* aaTrackBitRate, int* aaTrackLossless, uint* aaTrackBitDepth, uint* aaTrackSampleRate, char** aaTrackCodecName, uint* aaTrackId);
        private unsafe delegate int CallbackProtocolInfo(IntPtr aPtr, uint aVersion, char** aaSupportedProtocols);

        private GCHandle iGch;
        private CallbackPlay iCallbackPlay;
        private CallbackPause iCallbackPause;
        private CallbackStop iCallbackStop;
        private CallbackSeekSecondAbsolute iCallbackSeekSecondAbsolute;
        private CallbackSeekSecondRelative iCallbackSeekSecondRelative;
        private CallbackSeekTrackId iCallbackSeekTrackId;
        private CallbackSeekTrackAbsolute iCallbackSeekTrackAbsolute;
        private CallbackSeekTrackRelative iCallbackSeekTrackRelative;
        private CallbackState iCallbackState;
        private CallbackProtocolInfo iCallbackProtocolInfo;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkDs1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkDs1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the SupportedProtocols property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertySupportedProtocols(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkDs1SetPropertySupportedProtocols(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the SupportedProtocols property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertySupportedProtocols(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkDs1GetPropertySupportedProtocols(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the TrackDuration property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyTrackDuration(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkDs1SetPropertyTrackDuration(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the TrackDuration property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyTrackDuration(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkDs1GetPropertyTrackDuration(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the TrackBitRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyTrackBitRate(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkDs1SetPropertyTrackBitRate(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the TrackBitRate property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyTrackBitRate(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkDs1GetPropertyTrackBitRate(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the TrackLossless property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyTrackLossless(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkDs1SetPropertyTrackLossless(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the TrackLossless property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyTrackLossless(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkDs1GetPropertyTrackLossless(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the TrackBitDepth property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyTrackBitDepth(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkDs1SetPropertyTrackBitDepth(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the TrackBitDepth property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyTrackBitDepth(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkDs1GetPropertyTrackBitDepth(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the TrackSampleRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyTrackSampleRate(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkDs1SetPropertyTrackSampleRate(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the TrackSampleRate property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyTrackSampleRate(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkDs1GetPropertyTrackSampleRate(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the TrackCodecName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyTrackCodecName(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkDs1SetPropertyTrackCodecName(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the TrackCodecName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyTrackCodecName(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkDs1GetPropertyTrackCodecName(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the TrackId property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyTrackId(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkDs1SetPropertyTrackId(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the TrackId property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyTrackId(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkDs1GetPropertyTrackId(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the TransportState property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyTransportState(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkDs1SetPropertyTransportState(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the TransportState property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyTransportState(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkDs1GetPropertyTransportState(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Signal that the action Play is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPlay must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPlay()
        {
            iCallbackPlay = new CallbackPlay(DoPlay);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionPlay(iHandle, iCallbackPlay, ptr);
        }

        /// <summary>
        /// Signal that the action Pause is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPause must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPause()
        {
            iCallbackPause = new CallbackPause(DoPause);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionPause(iHandle, iCallbackPause, ptr);
        }

        /// <summary>
        /// Signal that the action Stop is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStop must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStop()
        {
            iCallbackStop = new CallbackStop(DoStop);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionStop(iHandle, iCallbackStop, ptr);
        }

        /// <summary>
        /// Signal that the action SeekSecondAbsolute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSeekSecondAbsolute must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSeekSecondAbsolute()
        {
            iCallbackSeekSecondAbsolute = new CallbackSeekSecondAbsolute(DoSeekSecondAbsolute);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionSeekSecondAbsolute(iHandle, iCallbackSeekSecondAbsolute, ptr);
        }

        /// <summary>
        /// Signal that the action SeekSecondRelative is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSeekSecondRelative must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSeekSecondRelative()
        {
            iCallbackSeekSecondRelative = new CallbackSeekSecondRelative(DoSeekSecondRelative);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionSeekSecondRelative(iHandle, iCallbackSeekSecondRelative, ptr);
        }

        /// <summary>
        /// Signal that the action SeekTrackId is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSeekTrackId must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSeekTrackId()
        {
            iCallbackSeekTrackId = new CallbackSeekTrackId(DoSeekTrackId);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionSeekTrackId(iHandle, iCallbackSeekTrackId, ptr);
        }

        /// <summary>
        /// Signal that the action SeekTrackAbsolute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSeekTrackAbsolute must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSeekTrackAbsolute()
        {
            iCallbackSeekTrackAbsolute = new CallbackSeekTrackAbsolute(DoSeekTrackAbsolute);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionSeekTrackAbsolute(iHandle, iCallbackSeekTrackAbsolute, ptr);
        }

        /// <summary>
        /// Signal that the action SeekTrackRelative is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSeekTrackRelative must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSeekTrackRelative()
        {
            iCallbackSeekTrackRelative = new CallbackSeekTrackRelative(DoSeekTrackRelative);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionSeekTrackRelative(iHandle, iCallbackSeekTrackRelative, ptr);
        }

        /// <summary>
        /// Signal that the action State is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoState must be overridden if this is called.</remarks>
        protected unsafe void EnableActionState()
        {
            iCallbackState = new CallbackState(DoState);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionState(iHandle, iCallbackState, ptr);
        }

        /// <summary>
        /// Signal that the action ProtocolInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoProtocolInfo must be overridden if this is called.</remarks>
        protected unsafe void EnableActionProtocolInfo()
        {
            iCallbackProtocolInfo = new CallbackProtocolInfo(DoProtocolInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionProtocolInfo(iHandle, iCallbackProtocolInfo, ptr);
        }

        /// <summary>
        /// Play action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Play action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlay was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Play(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Pause action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Pause action for the owning device.
        ///
        /// Must be implemented iff EnableActionPause was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Pause(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Stop action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Stop action for the owning device.
        ///
        /// Must be implemented iff EnableActionStop was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Stop(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SeekSecondAbsolute action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SeekSecondAbsolute action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeekSecondAbsolute was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSecond"></param>
        protected virtual void SeekSecondAbsolute(uint aVersion, uint aaSecond)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SeekSecondRelative action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SeekSecondRelative action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeekSecondRelative was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSecond"></param>
        protected virtual void SeekSecondRelative(uint aVersion, int aaSecond)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SeekTrackId action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SeekTrackId action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeekTrackId was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTrackId"></param>
        protected virtual void SeekTrackId(uint aVersion, uint aaTrackId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SeekTrackAbsolute action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SeekTrackAbsolute action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeekTrackAbsolute was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTrack"></param>
        protected virtual void SeekTrackAbsolute(uint aVersion, uint aaTrack)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SeekTrackRelative action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SeekTrackRelative action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeekTrackRelative was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTrack"></param>
        protected virtual void SeekTrackRelative(uint aVersion, int aaTrack)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// State action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// State action for the owning device.
        ///
        /// Must be implemented iff EnableActionState was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTransportState"></param>
        /// <param name="aaTrackDuration"></param>
        /// <param name="aaTrackBitRate"></param>
        /// <param name="aaTrackLossless"></param>
        /// <param name="aaTrackBitDepth"></param>
        /// <param name="aaTrackSampleRate"></param>
        /// <param name="aaTrackCodecName"></param>
        /// <param name="aaTrackId"></param>
        protected virtual void State(uint aVersion, out string aaTransportState, out uint aaTrackDuration, out uint aaTrackBitRate, out bool aaTrackLossless, out uint aaTrackBitDepth, out uint aaTrackSampleRate, out string aaTrackCodecName, out uint aaTrackId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ProtocolInfo action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ProtocolInfo action for the owning device.
        ///
        /// Must be implemented iff EnableActionProtocolInfo was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSupportedProtocols"></param>
        protected virtual void ProtocolInfo(uint aVersion, out string aaSupportedProtocols)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoPlay(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            self.Play(aVersion);
            return 0;
        }

        private static unsafe int DoPause(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            self.Pause(aVersion);
            return 0;
        }

        private static unsafe int DoStop(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            self.Stop(aVersion);
            return 0;
        }

        private static unsafe int DoSeekSecondAbsolute(IntPtr aPtr, uint aVersion, uint aaSecond)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            self.SeekSecondAbsolute(aVersion, aaSecond);
            return 0;
        }

        private static unsafe int DoSeekSecondRelative(IntPtr aPtr, uint aVersion, int aaSecond)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            self.SeekSecondRelative(aVersion, aaSecond);
            return 0;
        }

        private static unsafe int DoSeekTrackId(IntPtr aPtr, uint aVersion, uint aaTrackId)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            self.SeekTrackId(aVersion, aaTrackId);
            return 0;
        }

        private static unsafe int DoSeekTrackAbsolute(IntPtr aPtr, uint aVersion, uint aaTrack)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            self.SeekTrackAbsolute(aVersion, aaTrack);
            return 0;
        }

        private static unsafe int DoSeekTrackRelative(IntPtr aPtr, uint aVersion, int aaTrack)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            self.SeekTrackRelative(aVersion, aaTrack);
            return 0;
        }

        private static unsafe int DoState(IntPtr aPtr, uint aVersion, char** aaTransportState, uint* aaTrackDuration, uint* aaTrackBitRate, int* aaTrackLossless, uint* aaTrackBitDepth, uint* aaTrackSampleRate, char** aaTrackCodecName, uint* aaTrackId)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            string aTransportState;
            uint aTrackDuration;
            uint aTrackBitRate;
            bool aTrackLossless;
            uint aTrackBitDepth;
            uint aTrackSampleRate;
            string aTrackCodecName;
            uint aTrackId;
            self.State(aVersion, out aTransportState, out aTrackDuration, out aTrackBitRate, out aTrackLossless, out aTrackBitDepth, out aTrackSampleRate, out aTrackCodecName, out aTrackId);
            *aaTransportState = (char*)Marshal.StringToHGlobalAnsi(aTransportState).ToPointer();
            *aaTrackDuration = aTrackDuration;
            *aaTrackBitRate = aTrackBitRate;
            *aaTrackLossless = (aTrackLossless ? 1 : 0);
            *aaTrackBitDepth = aTrackBitDepth;
            *aaTrackSampleRate = aTrackSampleRate;
            *aaTrackCodecName = (char*)Marshal.StringToHGlobalAnsi(aTrackCodecName).ToPointer();
            *aaTrackId = aTrackId;
            return 0;
        }

        private static unsafe int DoProtocolInfo(IntPtr aPtr, uint aVersion, char** aaSupportedProtocols)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            string aSupportedProtocols;
            self.ProtocolInfo(aVersion, out aSupportedProtocols);
            *aaSupportedProtocols = (char*)Marshal.StringToHGlobalAnsi(aSupportedProtocols).ToPointer();
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

        ~DvProviderLinnCoUkDs1()
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
            DvProviderLinnCoUkDs1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

