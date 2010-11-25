using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
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

        public DvProviderLinnCoUkInfo1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkInfo1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe bool SetPropertyTrackCount(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkInfo1SetPropertyTrackCount(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyTrackCount(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkInfo1GetPropertyTrackCount(iHandle, value);
            }
        }

        public unsafe bool SetPropertyDetailsCount(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkInfo1SetPropertyDetailsCount(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyDetailsCount(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkInfo1GetPropertyDetailsCount(iHandle, value);
            }
        }

        public unsafe bool SetPropertyMetatextCount(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkInfo1SetPropertyMetatextCount(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyMetatextCount(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkInfo1GetPropertyMetatextCount(iHandle, value);
            }
        }

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

        public unsafe void GetPropertyUri(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkInfo1GetPropertyUri(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

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

        public unsafe void GetPropertyMetadata(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkInfo1GetPropertyMetadata(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe bool SetPropertyDuration(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkInfo1SetPropertyDuration(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyDuration(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkInfo1GetPropertyDuration(iHandle, value);
            }
        }

        public unsafe bool SetPropertyBitRate(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkInfo1SetPropertyBitRate(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyBitRate(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkInfo1GetPropertyBitRate(iHandle, value);
            }
        }

        public unsafe bool SetPropertyBitDepth(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkInfo1SetPropertyBitDepth(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyBitDepth(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkInfo1GetPropertyBitDepth(iHandle, value);
            }
        }

        public unsafe bool SetPropertySampleRate(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkInfo1SetPropertySampleRate(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertySampleRate(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkInfo1GetPropertySampleRate(iHandle, value);
            }
        }

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

        public unsafe void GetPropertyLossless(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkInfo1GetPropertyLossless(iHandle, &value);
            aValue = (value != 0);
        }

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

        public unsafe void GetPropertyCodecName(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkInfo1GetPropertyCodecName(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

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

        public unsafe void GetPropertyMetatext(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkInfo1GetPropertyMetatext(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        protected unsafe void EnableActionCounters()
        {
            iCallbackCounters = new CallbackCounters(DoCounters);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkInfo1EnableActionCounters(iHandle, iCallbackCounters, ptr);
        }

        protected unsafe void EnableActionTrack()
        {
            iCallbackTrack = new CallbackTrack(DoTrack);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkInfo1EnableActionTrack(iHandle, iCallbackTrack, ptr);
        }

        protected unsafe void EnableActionDetails()
        {
            iCallbackDetails = new CallbackDetails(DoDetails);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkInfo1EnableActionDetails(iHandle, iCallbackDetails, ptr);
        }

        protected unsafe void EnableActionMetatext()
        {
            iCallbackMetatext = new CallbackMetatext(DoMetatext);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkInfo1EnableActionMetatext(iHandle, iCallbackMetatext, ptr);
        }

        protected virtual void Counters(uint aVersion, out uint aaTrackCount, out uint aaDetailsCount, out uint aaMetatextCount)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Track(uint aVersion, out string aaUri, out string aaMetadata)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Details(uint aVersion, out uint aaDuration, out uint aaBitRate, out uint aaBitDepth, out uint aaSampleRate, out bool aaLossless, out string aaCodecName)
        {
            throw (new ActionDisabledError());
        }

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

