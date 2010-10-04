using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkInfo1 : IDisposable
    {
        [DllImport("DvLinnCoUkInfo1")]
        static extern uint DvServiceLinnCoUkInfo1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkInfo1")]
        static extern void DvServiceLinnCoUkInfo1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvServiceLinnCoUkInfo1SetPropertyTrackCount(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvServiceLinnCoUkInfo1GetPropertyTrackCount(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvServiceLinnCoUkInfo1SetPropertyDetailsCount(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvServiceLinnCoUkInfo1GetPropertyDetailsCount(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvServiceLinnCoUkInfo1SetPropertyMetatextCount(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvServiceLinnCoUkInfo1GetPropertyMetatextCount(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvServiceLinnCoUkInfo1SetPropertyUri(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvServiceLinnCoUkInfo1GetPropertyUri(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvServiceLinnCoUkInfo1SetPropertyMetadata(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvServiceLinnCoUkInfo1GetPropertyMetadata(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvServiceLinnCoUkInfo1SetPropertyDuration(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvServiceLinnCoUkInfo1GetPropertyDuration(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvServiceLinnCoUkInfo1SetPropertyBitRate(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvServiceLinnCoUkInfo1GetPropertyBitRate(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvServiceLinnCoUkInfo1SetPropertyBitDepth(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvServiceLinnCoUkInfo1GetPropertyBitDepth(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvServiceLinnCoUkInfo1SetPropertySampleRate(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvServiceLinnCoUkInfo1GetPropertySampleRate(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvServiceLinnCoUkInfo1SetPropertyLossless(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvServiceLinnCoUkInfo1GetPropertyLossless(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvServiceLinnCoUkInfo1SetPropertyCodecName(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvServiceLinnCoUkInfo1GetPropertyCodecName(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe int DvServiceLinnCoUkInfo1SetPropertyMetatext(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern unsafe void DvServiceLinnCoUkInfo1GetPropertyMetatext(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkInfo1")]
        static extern void DvServiceLinnCoUkInfo1EnableActionCounters(uint aHandle, CallbackCounters aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkInfo1")]
        static extern void DvServiceLinnCoUkInfo1EnableActionTrack(uint aHandle, CallbackTrack aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkInfo1")]
        static extern void DvServiceLinnCoUkInfo1EnableActionDetails(uint aHandle, CallbackDetails aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkInfo1")]
        static extern void DvServiceLinnCoUkInfo1EnableActionMetatext(uint aHandle, CallbackMetatext aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackCounters(IntPtr aPtr, uint aVersion, uint* aaTrackCount, uint* aaDetailsCount, uint* aaMetatextCount);
        private unsafe delegate int CallbackTrack(IntPtr aPtr, uint aVersion, char** aaUri, char** aaMetadata);
        private unsafe delegate int CallbackDetails(IntPtr aPtr, uint aVersion, uint* aaDuration, uint* aaBitRate, uint* aaBitDepth, uint* aaSampleRate, int* aaLossless, char** aaCodecName);
        private unsafe delegate int CallbackMetatext(IntPtr aPtr, uint aVersion, char** aaMetatext);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackCounters iCallbackCounters;
        private CallbackTrack iCallbackTrack;
        private CallbackDetails iCallbackDetails;
        private CallbackMetatext iCallbackMetatext;

        public DvServiceLinnCoUkInfo1(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkInfo1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyTrackCount(uint aValue)
        {
            if (0 != DvServiceLinnCoUkInfo1SetPropertyTrackCount(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyTrackCount(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkInfo1GetPropertyTrackCount(iHandle, value);
            }
        }

        public unsafe void SetPropertyDetailsCount(uint aValue)
        {
            if (0 != DvServiceLinnCoUkInfo1SetPropertyDetailsCount(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyDetailsCount(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkInfo1GetPropertyDetailsCount(iHandle, value);
            }
        }

        public unsafe void SetPropertyMetatextCount(uint aValue)
        {
            if (0 != DvServiceLinnCoUkInfo1SetPropertyMetatextCount(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyMetatextCount(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkInfo1GetPropertyMetatextCount(iHandle, value);
            }
        }

        public unsafe void SetPropertyUri(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkInfo1SetPropertyUri(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyUri(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkInfo1GetPropertyUri(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyMetadata(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkInfo1SetPropertyMetadata(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyMetadata(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkInfo1GetPropertyMetadata(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyDuration(uint aValue)
        {
            if (0 != DvServiceLinnCoUkInfo1SetPropertyDuration(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyDuration(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkInfo1GetPropertyDuration(iHandle, value);
            }
        }

        public unsafe void SetPropertyBitRate(uint aValue)
        {
            if (0 != DvServiceLinnCoUkInfo1SetPropertyBitRate(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyBitRate(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkInfo1GetPropertyBitRate(iHandle, value);
            }
        }

        public unsafe void SetPropertyBitDepth(uint aValue)
        {
            if (0 != DvServiceLinnCoUkInfo1SetPropertyBitDepth(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyBitDepth(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkInfo1GetPropertyBitDepth(iHandle, value);
            }
        }

        public unsafe void SetPropertySampleRate(uint aValue)
        {
            if (0 != DvServiceLinnCoUkInfo1SetPropertySampleRate(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertySampleRate(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkInfo1GetPropertySampleRate(iHandle, value);
            }
        }

        public unsafe void SetPropertyLossless(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkInfo1SetPropertyLossless(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyLossless(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkInfo1GetPropertyLossless(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyCodecName(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkInfo1SetPropertyCodecName(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyCodecName(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkInfo1GetPropertyCodecName(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyMetatext(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkInfo1SetPropertyMetatext(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyMetatext(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkInfo1GetPropertyMetatext(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        protected unsafe void EnableActionCounters()
        {
            iCallbackCounters = new CallbackCounters(DoCounters);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkInfo1EnableActionCounters(iHandle, iCallbackCounters, ptr);
        }

        protected unsafe void EnableActionTrack()
        {
            iCallbackTrack = new CallbackTrack(DoTrack);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkInfo1EnableActionTrack(iHandle, iCallbackTrack, ptr);
        }

        protected unsafe void EnableActionDetails()
        {
            iCallbackDetails = new CallbackDetails(DoDetails);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkInfo1EnableActionDetails(iHandle, iCallbackDetails, ptr);
        }

        protected unsafe void EnableActionMetatext()
        {
            iCallbackMetatext = new CallbackMetatext(DoMetatext);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkInfo1EnableActionMetatext(iHandle, iCallbackMetatext, ptr);
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
            DvServiceLinnCoUkInfo1 self = (DvServiceLinnCoUkInfo1)gch.Target;
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
            DvServiceLinnCoUkInfo1 self = (DvServiceLinnCoUkInfo1)gch.Target;
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
            DvServiceLinnCoUkInfo1 self = (DvServiceLinnCoUkInfo1)gch.Target;
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
            DvServiceLinnCoUkInfo1 self = (DvServiceLinnCoUkInfo1)gch.Target;
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

        ~DvServiceLinnCoUkInfo1()
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
            DvServiceLinnCoUkInfo1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

