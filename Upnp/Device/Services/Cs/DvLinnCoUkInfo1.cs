using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    /// <summary>
    /// Provider for the linn.co.uk:Info:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkInfo1 : DvProvider, IDisposable
    {
        [DllImport("DvLinnCoUkInfo1")]
        static extern uint DvProviderLinnCoUkInfo1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkInfo1")]
        static extern void DvProviderLinnCoUkInfo1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvProviderLinnCoUkInfo1SetPropertyTrackCount(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvProviderLinnCoUkInfo1GetPropertyTrackCount(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvProviderLinnCoUkInfo1SetPropertyDetailsCount(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvProviderLinnCoUkInfo1GetPropertyDetailsCount(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvProviderLinnCoUkInfo1SetPropertyMetatextCount(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvProviderLinnCoUkInfo1GetPropertyMetatextCount(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvProviderLinnCoUkInfo1SetPropertyUri(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvProviderLinnCoUkInfo1GetPropertyUri(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvProviderLinnCoUkInfo1SetPropertyMetadata(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvProviderLinnCoUkInfo1GetPropertyMetadata(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvProviderLinnCoUkInfo1SetPropertyDuration(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvProviderLinnCoUkInfo1GetPropertyDuration(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvProviderLinnCoUkInfo1SetPropertyBitRate(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvProviderLinnCoUkInfo1GetPropertyBitRate(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvProviderLinnCoUkInfo1SetPropertyBitDepth(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvProviderLinnCoUkInfo1GetPropertyBitDepth(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvProviderLinnCoUkInfo1SetPropertySampleRate(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvProviderLinnCoUkInfo1GetPropertySampleRate(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvProviderLinnCoUkInfo1SetPropertyLossless(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvProviderLinnCoUkInfo1GetPropertyLossless(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvProviderLinnCoUkInfo1SetPropertyCodecName(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvProviderLinnCoUkInfo1GetPropertyCodecName(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvProviderLinnCoUkInfo1SetPropertyMetatext(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvProviderLinnCoUkInfo1GetPropertyMetatext(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern void DvProviderLinnCoUkInfo1EnableActionCounters(uint aHandle, CallbackCounters aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkInfo1")]
        static extern void DvProviderLinnCoUkInfo1EnableActionTrack(uint aHandle, CallbackTrack aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkInfo1")]
        static extern void DvProviderLinnCoUkInfo1EnableActionDetails(uint aHandle, CallbackDetails aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkInfo1")]
        static extern void DvProviderLinnCoUkInfo1EnableActionMetatext(uint aHandle, CallbackMetatext aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackCounters(IntPtr aPtr, uint aVersion, uint* aaTrackCount, uint* aaDetailsCount, uint* aaMetatextCount);
        private unsafe delegate int CallbackTrack(IntPtr aPtr, uint aVersion, char** aaUri, char** aaMetadata);
        private unsafe delegate int CallbackDetails(IntPtr aPtr, uint aVersion, uint* aaDuration, uint* aaBitRate, uint* aaBitDepth, uint* aaSampleRate, int* aaLossless, char** aaCodecName);
        private unsafe delegate int CallbackMetatext(IntPtr aPtr, uint aVersion, char** aaMetatext);

        private GCHandle iGch;
        private CallbackCounters iCallbackCounters;
        private CallbackTrack iCallbackTrack;
        private CallbackDetails iCallbackDetails;
        private CallbackMetatext iCallbackMetatext;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkInfo1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkInfo1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the TrackCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyTrackCount(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkInfo1SetPropertyTrackCount(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the TrackCount property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyTrackCount(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkInfo1GetPropertyTrackCount(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the DetailsCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyDetailsCount(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkInfo1SetPropertyDetailsCount(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the DetailsCount property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyDetailsCount(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkInfo1GetPropertyDetailsCount(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the MetatextCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyMetatextCount(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkInfo1SetPropertyMetatextCount(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the MetatextCount property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyMetatextCount(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkInfo1GetPropertyMetatextCount(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the Uri property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyUri(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkInfo1SetPropertyUri(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the Uri property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyUri(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkInfo1GetPropertyUri(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the Metadata property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyMetadata(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkInfo1SetPropertyMetadata(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the Metadata property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyMetadata(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkInfo1GetPropertyMetadata(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the Duration property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyDuration(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkInfo1SetPropertyDuration(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the Duration property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyDuration(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkInfo1GetPropertyDuration(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the BitRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyBitRate(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkInfo1SetPropertyBitRate(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the BitRate property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyBitRate(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkInfo1GetPropertyBitRate(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the BitDepth property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyBitDepth(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkInfo1SetPropertyBitDepth(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the BitDepth property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyBitDepth(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkInfo1GetPropertyBitDepth(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the SampleRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertySampleRate(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkInfo1SetPropertySampleRate(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the SampleRate property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertySampleRate(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkInfo1GetPropertySampleRate(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the Lossless property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyLossless(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkInfo1SetPropertyLossless(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the Lossless property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyLossless(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkInfo1GetPropertyLossless(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the CodecName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyCodecName(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkInfo1SetPropertyCodecName(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the CodecName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyCodecName(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkInfo1GetPropertyCodecName(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the Metatext property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyMetatext(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkInfo1SetPropertyMetatext(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the Metatext property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyMetatext(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkInfo1GetPropertyMetatext(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Signal that the action Counters is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoCounters must be overridden if this is called.</remarks>
        protected unsafe void EnableActionCounters()
        {
            iCallbackCounters = new CallbackCounters(DoCounters);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkInfo1EnableActionCounters(iHandle, iCallbackCounters, ptr);
        }

        /// <summary>
        /// Signal that the action Track is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoTrack must be overridden if this is called.</remarks>
        protected unsafe void EnableActionTrack()
        {
            iCallbackTrack = new CallbackTrack(DoTrack);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkInfo1EnableActionTrack(iHandle, iCallbackTrack, ptr);
        }

        /// <summary>
        /// Signal that the action Details is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDetails must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDetails()
        {
            iCallbackDetails = new CallbackDetails(DoDetails);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkInfo1EnableActionDetails(iHandle, iCallbackDetails, ptr);
        }

        /// <summary>
        /// Signal that the action Metatext is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoMetatext must be overridden if this is called.</remarks>
        protected unsafe void EnableActionMetatext()
        {
            iCallbackMetatext = new CallbackMetatext(DoMetatext);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkInfo1EnableActionMetatext(iHandle, iCallbackMetatext, ptr);
        }

        /// <summary>
        /// Counters action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Counters action for the owning device.
        ///
        /// Must be implemented iff EnableActionCounters was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTrackCount"></param>
        /// <param name="aaDetailsCount"></param>
        /// <param name="aaMetatextCount"></param>
        protected virtual void Counters(uint aVersion, out uint aaTrackCount, out uint aaDetailsCount, out uint aaMetatextCount)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Track action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Track action for the owning device.
        ///
        /// Must be implemented iff EnableActionTrack was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        protected virtual void Track(uint aVersion, out string aaUri, out string aaMetadata)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Details action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Details action for the owning device.
        ///
        /// Must be implemented iff EnableActionDetails was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaDuration"></param>
        /// <param name="aaBitRate"></param>
        /// <param name="aaBitDepth"></param>
        /// <param name="aaSampleRate"></param>
        /// <param name="aaLossless"></param>
        /// <param name="aaCodecName"></param>
        protected virtual void Details(uint aVersion, out uint aaDuration, out uint aaBitRate, out uint aaBitDepth, out uint aaSampleRate, out bool aaLossless, out string aaCodecName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Metatext action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Metatext action for the owning device.
        ///
        /// Must be implemented iff EnableActionMetatext was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMetatext"></param>
        protected virtual void Metatext(uint aVersion, out string aaMetatext)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoCounters(IntPtr aPtr, uint aVersion, uint* aaTrackCount, uint* aaDetailsCount, uint* aaMetatextCount)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkInfo1 self = (DvProviderLinnCoUkInfo1)gch.Target;
            uint aTrackCount;
            uint aDetailsCount;
            uint aMetatextCount;
            self.Counters(aVersion, out aTrackCount, out aDetailsCount, out aMetatextCount);
            *aaTrackCount = aTrackCount;
            *aaDetailsCount = aDetailsCount;
            *aaMetatextCount = aMetatextCount;
            return 0;
        }

        private static unsafe int DoTrack(IntPtr aPtr, uint aVersion, char** aaUri, char** aaMetadata)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkInfo1 self = (DvProviderLinnCoUkInfo1)gch.Target;
            string aUri;
            string aMetadata;
            self.Track(aVersion, out aUri, out aMetadata);
            *aaUri = (char*)Marshal.StringToHGlobalAnsi(aUri).ToPointer();
            *aaMetadata = (char*)Marshal.StringToHGlobalAnsi(aMetadata).ToPointer();
            return 0;
        }

        private static unsafe int DoDetails(IntPtr aPtr, uint aVersion, uint* aaDuration, uint* aaBitRate, uint* aaBitDepth, uint* aaSampleRate, int* aaLossless, char** aaCodecName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkInfo1 self = (DvProviderLinnCoUkInfo1)gch.Target;
            uint aDuration;
            uint aBitRate;
            uint aBitDepth;
            uint aSampleRate;
            bool aLossless;
            string aCodecName;
            self.Details(aVersion, out aDuration, out aBitRate, out aBitDepth, out aSampleRate, out aLossless, out aCodecName);
            *aaDuration = aDuration;
            *aaBitRate = aBitRate;
            *aaBitDepth = aBitDepth;
            *aaSampleRate = aSampleRate;
            *aaLossless = (aLossless ? 1 : 0);
            *aaCodecName = (char*)Marshal.StringToHGlobalAnsi(aCodecName).ToPointer();
            return 0;
        }

        private static unsafe int DoMetatext(IntPtr aPtr, uint aVersion, char** aaMetatext)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkInfo1 self = (DvProviderLinnCoUkInfo1)gch.Target;
            string aMetatext;
            self.Metatext(aVersion, out aMetatext);
            *aaMetatext = (char*)Marshal.StringToHGlobalAnsi(aMetatext).ToPointer();
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

        ~DvProviderLinnCoUkInfo1()
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
            DvProviderLinnCoUkInfo1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

