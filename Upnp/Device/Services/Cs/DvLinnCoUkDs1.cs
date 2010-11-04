using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvProviderLinnCoUkDs1 : IDisposable
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

        private uint iHandle;
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

        public DvProviderLinnCoUkDs1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkDs1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

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

        public unsafe void GetPropertySupportedProtocols(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkDs1GetPropertySupportedProtocols(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe bool SetPropertyTrackDuration(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkDs1SetPropertyTrackDuration(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyTrackDuration(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkDs1GetPropertyTrackDuration(iHandle, value);
            }
        }

        public unsafe bool SetPropertyTrackBitRate(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkDs1SetPropertyTrackBitRate(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyTrackBitRate(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkDs1GetPropertyTrackBitRate(iHandle, value);
            }
        }

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

        public unsafe void GetPropertyTrackLossless(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkDs1GetPropertyTrackLossless(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe bool SetPropertyTrackBitDepth(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkDs1SetPropertyTrackBitDepth(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyTrackBitDepth(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkDs1GetPropertyTrackBitDepth(iHandle, value);
            }
        }

        public unsafe bool SetPropertyTrackSampleRate(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkDs1SetPropertyTrackSampleRate(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyTrackSampleRate(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkDs1GetPropertyTrackSampleRate(iHandle, value);
            }
        }

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

        public unsafe void GetPropertyTrackCodecName(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkDs1GetPropertyTrackCodecName(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe bool SetPropertyTrackId(uint aValue)
        {
        uint changed;
            if (0 != DvProviderLinnCoUkDs1SetPropertyTrackId(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyTrackId(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvProviderLinnCoUkDs1GetPropertyTrackId(iHandle, value);
            }
        }

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

        public unsafe void GetPropertyTransportState(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkDs1GetPropertyTransportState(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        protected unsafe void EnableActionPlay()
        {
            iCallbackPlay = new CallbackPlay(DoPlay);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionPlay(iHandle, iCallbackPlay, ptr);
        }

        protected unsafe void EnableActionPause()
        {
            iCallbackPause = new CallbackPause(DoPause);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionPause(iHandle, iCallbackPause, ptr);
        }

        protected unsafe void EnableActionStop()
        {
            iCallbackStop = new CallbackStop(DoStop);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionStop(iHandle, iCallbackStop, ptr);
        }

        protected unsafe void EnableActionSeekSecondAbsolute()
        {
            iCallbackSeekSecondAbsolute = new CallbackSeekSecondAbsolute(DoSeekSecondAbsolute);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionSeekSecondAbsolute(iHandle, iCallbackSeekSecondAbsolute, ptr);
        }

        protected unsafe void EnableActionSeekSecondRelative()
        {
            iCallbackSeekSecondRelative = new CallbackSeekSecondRelative(DoSeekSecondRelative);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionSeekSecondRelative(iHandle, iCallbackSeekSecondRelative, ptr);
        }

        protected unsafe void EnableActionSeekTrackId()
        {
            iCallbackSeekTrackId = new CallbackSeekTrackId(DoSeekTrackId);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionSeekTrackId(iHandle, iCallbackSeekTrackId, ptr);
        }

        protected unsafe void EnableActionSeekTrackAbsolute()
        {
            iCallbackSeekTrackAbsolute = new CallbackSeekTrackAbsolute(DoSeekTrackAbsolute);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionSeekTrackAbsolute(iHandle, iCallbackSeekTrackAbsolute, ptr);
        }

        protected unsafe void EnableActionSeekTrackRelative()
        {
            iCallbackSeekTrackRelative = new CallbackSeekTrackRelative(DoSeekTrackRelative);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionSeekTrackRelative(iHandle, iCallbackSeekTrackRelative, ptr);
        }

        protected unsafe void EnableActionState()
        {
            iCallbackState = new CallbackState(DoState);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionState(iHandle, iCallbackState, ptr);
        }

        protected unsafe void EnableActionProtocolInfo()
        {
            iCallbackProtocolInfo = new CallbackProtocolInfo(DoProtocolInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkDs1EnableActionProtocolInfo(iHandle, iCallbackProtocolInfo, ptr);
        }

        protected virtual void Play(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Pause(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Stop(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SeekSecondAbsolute(uint aVersion, uint aaSecond)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SeekSecondRelative(uint aVersion, int aaSecond)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SeekTrackId(uint aVersion, uint aaTrackId)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SeekTrackAbsolute(uint aVersion, uint aaTrack)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SeekTrackRelative(uint aVersion, int aaTrack)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void State(uint aVersion, out string aaTransportState, out uint aaTrackDuration, out uint aaTrackBitRate, out bool aaTrackLossless, out uint aaTrackBitDepth, out uint aaTrackSampleRate, out string aaTrackCodecName, out uint aaTrackId)
        {
            throw (new ActionDisabledError());
        }

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

