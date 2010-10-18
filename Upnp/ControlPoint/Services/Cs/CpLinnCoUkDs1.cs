using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkDs1 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkDs1")]
        static extern IntPtr CpProxyLinnCoUkDs1Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncPlay(IntPtr aHandle);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginPlay(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndPlay(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncPause(IntPtr aHandle);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginPause(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndPause(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncStop(IntPtr aHandle);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginStop(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndStop(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncSeekSecondAbsolute(IntPtr aHandle, uint aaSecond);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginSeekSecondAbsolute(IntPtr aHandle, uint aaSecond, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndSeekSecondAbsolute(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncSeekSecondRelative(IntPtr aHandle, int aaSecond);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginSeekSecondRelative(IntPtr aHandle, int aaSecond, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndSeekSecondRelative(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncSeekTrackId(IntPtr aHandle, uint aaTrackId);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginSeekTrackId(IntPtr aHandle, uint aaTrackId, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndSeekTrackId(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncSeekTrackAbsolute(IntPtr aHandle, uint aaTrack);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginSeekTrackAbsolute(IntPtr aHandle, uint aaTrack, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndSeekTrackAbsolute(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncSeekTrackRelative(IntPtr aHandle, int aaTrack);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginSeekTrackRelative(IntPtr aHandle, int aaTrack, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndSeekTrackRelative(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncState(IntPtr aHandle, char** aaTransportState, uint* aaTrackDuration, uint* aaTrackBitRate, uint* aaTrackLossless, uint* aaTrackBitDepth, uint* aaTrackSampleRate, char** aaTrackCodecName, uint* aaTrackId);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginState(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndState(IntPtr aHandle, IntPtr aAsync, char** aaTransportState, uint* aaTrackDuration, uint* aaTrackBitRate, uint* aaTrackLossless, uint* aaTrackBitDepth, uint* aaTrackSampleRate, char** aaTrackCodecName, uint* aaTrackId);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncProtocolInfo(IntPtr aHandle, char** aaSupportedProtocols);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginProtocolInfo(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndProtocolInfo(IntPtr aHandle, IntPtr aAsync, char** aaSupportedProtocols);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertySupportedProtocolsChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTrackDurationChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTrackBitRateChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTrackLosslessChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTrackBitDepthChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTrackSampleRateChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTrackCodecNameChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTrackIdChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTransportStateChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertySupportedProtocols(IntPtr aHandle, char** aSupportedProtocols);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTrackDuration(IntPtr aHandle, uint* aTrackDuration);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTrackBitRate(IntPtr aHandle, uint* aTrackBitRate);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTrackLossless(IntPtr aHandle, uint* aTrackLossless);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTrackBitDepth(IntPtr aHandle, uint* aTrackBitDepth);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTrackSampleRate(IntPtr aHandle, uint* aTrackSampleRate);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTrackCodecName(IntPtr aHandle, char** aTrackCodecName);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTrackId(IntPtr aHandle, uint* aTrackId);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTransportState(IntPtr aHandle, char** aTransportState);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iSupportedProtocolsChanged;
        private CallbackPropertyChanged iTrackDurationChanged;
        private CallbackPropertyChanged iTrackBitRateChanged;
        private CallbackPropertyChanged iTrackLosslessChanged;
        private CallbackPropertyChanged iTrackBitDepthChanged;
        private CallbackPropertyChanged iTrackSampleRateChanged;
        private CallbackPropertyChanged iTrackCodecNameChanged;
        private CallbackPropertyChanged iTrackIdChanged;
        private CallbackPropertyChanged iTransportStateChanged;
        private Callback iCallbackSupportedProtocolsChanged;
        private Callback iCallbackTrackDurationChanged;
        private Callback iCallbackTrackBitRateChanged;
        private Callback iCallbackTrackLosslessChanged;
        private Callback iCallbackTrackBitDepthChanged;
        private Callback iCallbackTrackSampleRateChanged;
        private Callback iCallbackTrackCodecNameChanged;
        private Callback iCallbackTrackIdChanged;
        private Callback iCallbackTransportStateChanged;

        public CpProxyLinnCoUkDs1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkDs1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncPlay()
        {
			{
				CpProxyLinnCoUkDs1SyncPlay(iHandle);
			}
        }

        public unsafe void BeginPlay(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginPlay(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndPlay(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndPlay(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncPause()
        {
			{
				CpProxyLinnCoUkDs1SyncPause(iHandle);
			}
        }

        public unsafe void BeginPause(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginPause(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndPause(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndPause(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStop()
        {
			{
				CpProxyLinnCoUkDs1SyncStop(iHandle);
			}
        }

        public unsafe void BeginStop(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginStop(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndStop(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndStop(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSeekSecondAbsolute(uint aaSecond)
        {
			{
				CpProxyLinnCoUkDs1SyncSeekSecondAbsolute(iHandle, aaSecond);
			}
        }

        public unsafe void BeginSeekSecondAbsolute(uint aaSecond, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginSeekSecondAbsolute(iHandle, aaSecond, iActionComplete, ptr);
        }

        public unsafe void EndSeekSecondAbsolute(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndSeekSecondAbsolute(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSeekSecondRelative(int aaSecond)
        {
			{
				CpProxyLinnCoUkDs1SyncSeekSecondRelative(iHandle, aaSecond);
			}
        }

        public unsafe void BeginSeekSecondRelative(int aaSecond, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginSeekSecondRelative(iHandle, aaSecond, iActionComplete, ptr);
        }

        public unsafe void EndSeekSecondRelative(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndSeekSecondRelative(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSeekTrackId(uint aaTrackId)
        {
			{
				CpProxyLinnCoUkDs1SyncSeekTrackId(iHandle, aaTrackId);
			}
        }

        public unsafe void BeginSeekTrackId(uint aaTrackId, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginSeekTrackId(iHandle, aaTrackId, iActionComplete, ptr);
        }

        public unsafe void EndSeekTrackId(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndSeekTrackId(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSeekTrackAbsolute(uint aaTrack)
        {
			{
				CpProxyLinnCoUkDs1SyncSeekTrackAbsolute(iHandle, aaTrack);
			}
        }

        public unsafe void BeginSeekTrackAbsolute(uint aaTrack, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginSeekTrackAbsolute(iHandle, aaTrack, iActionComplete, ptr);
        }

        public unsafe void EndSeekTrackAbsolute(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndSeekTrackAbsolute(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSeekTrackRelative(int aaTrack)
        {
			{
				CpProxyLinnCoUkDs1SyncSeekTrackRelative(iHandle, aaTrack);
			}
        }

        public unsafe void BeginSeekTrackRelative(int aaTrack, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginSeekTrackRelative(iHandle, aaTrack, iActionComplete, ptr);
        }

        public unsafe void EndSeekTrackRelative(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndSeekTrackRelative(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncState(out string aaTransportState, out uint aaTrackDuration, out uint aaTrackBitRate, out bool aaTrackLossless, out uint aaTrackBitDepth, out uint aaTrackSampleRate, out string aaTrackCodecName, out uint aaTrackId)
        {
			char* aTransportState;
			uint aTrackLossless;
			char* aTrackCodecName;
			fixed (uint* aTrackDuration = &aaTrackDuration)
			fixed (uint* aTrackBitRate = &aaTrackBitRate)
			fixed (uint* aTrackBitDepth = &aaTrackBitDepth)
			fixed (uint* aTrackSampleRate = &aaTrackSampleRate)
			fixed (uint* aTrackId = &aaTrackId)
			{
				CpProxyLinnCoUkDs1SyncState(iHandle, &aTransportState, aTrackDuration, aTrackBitRate, &aTrackLossless, aTrackBitDepth, aTrackSampleRate, &aTrackCodecName, aTrackId);
			}
            aaTransportState = Marshal.PtrToStringAnsi((IntPtr)aTransportState);
            ZappFree(aTransportState);
			aaTrackLossless = (aTrackLossless != 0);
            aaTrackCodecName = Marshal.PtrToStringAnsi((IntPtr)aTrackCodecName);
            ZappFree(aTrackCodecName);
        }

        public unsafe void BeginState(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginState(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndState(IntPtr aAsyncHandle, out string aaTransportState, out uint aaTrackDuration, out uint aaTrackBitRate, out bool aaTrackLossless, out uint aaTrackBitDepth, out uint aaTrackSampleRate, out string aaTrackCodecName, out uint aaTrackId)
        {
			char* aTransportState;
			uint aTrackLossless;
			char* aTrackCodecName;
			fixed (uint* aTrackDuration = &aaTrackDuration)
			fixed (uint* aTrackBitRate = &aaTrackBitRate)
			fixed (uint* aTrackBitDepth = &aaTrackBitDepth)
			fixed (uint* aTrackSampleRate = &aaTrackSampleRate)
			fixed (uint* aTrackId = &aaTrackId)
			{
				if (0 != CpProxyLinnCoUkDs1EndState(iHandle, aAsyncHandle, &aTransportState, aTrackDuration, aTrackBitRate, &aTrackLossless, aTrackBitDepth, aTrackSampleRate, &aTrackCodecName, aTrackId))
				{
					throw(new ProxyError());
				}
			}
            aaTransportState = Marshal.PtrToStringAnsi((IntPtr)aTransportState);
            ZappFree(aTransportState);
			aaTrackLossless = (aTrackLossless != 0);
            aaTrackCodecName = Marshal.PtrToStringAnsi((IntPtr)aTrackCodecName);
            ZappFree(aTrackCodecName);
        }

        public unsafe void SyncProtocolInfo(out string aaSupportedProtocols)
        {
			char* aSupportedProtocols;
			{
				CpProxyLinnCoUkDs1SyncProtocolInfo(iHandle, &aSupportedProtocols);
			}
            aaSupportedProtocols = Marshal.PtrToStringAnsi((IntPtr)aSupportedProtocols);
            ZappFree(aSupportedProtocols);
        }

        public unsafe void BeginProtocolInfo(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginProtocolInfo(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndProtocolInfo(IntPtr aAsyncHandle, out string aaSupportedProtocols)
        {
			char* aSupportedProtocols;
			{
				if (0 != CpProxyLinnCoUkDs1EndProtocolInfo(iHandle, aAsyncHandle, &aSupportedProtocols))
				{
					throw(new ProxyError());
				}
			}
            aaSupportedProtocols = Marshal.PtrToStringAnsi((IntPtr)aSupportedProtocols);
            ZappFree(aSupportedProtocols);
        }

        public void SetPropertySupportedProtocolsChanged(CallbackPropertyChanged aSupportedProtocolsChanged)
        {
            iSupportedProtocolsChanged = aSupportedProtocolsChanged;
            iCallbackSupportedProtocolsChanged = new Callback(PropertySupportedProtocolsChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkDs1SetPropertySupportedProtocolsChanged(iHandle, iCallbackSupportedProtocolsChanged, ptr);
        }

        private void PropertySupportedProtocolsChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkDs1 self = (CpProxyLinnCoUkDs1)gch.Target;
            self.iSupportedProtocolsChanged();
        }

        public void SetPropertyTrackDurationChanged(CallbackPropertyChanged aTrackDurationChanged)
        {
            iTrackDurationChanged = aTrackDurationChanged;
            iCallbackTrackDurationChanged = new Callback(PropertyTrackDurationChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkDs1SetPropertyTrackDurationChanged(iHandle, iCallbackTrackDurationChanged, ptr);
        }

        private void PropertyTrackDurationChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkDs1 self = (CpProxyLinnCoUkDs1)gch.Target;
            self.iTrackDurationChanged();
        }

        public void SetPropertyTrackBitRateChanged(CallbackPropertyChanged aTrackBitRateChanged)
        {
            iTrackBitRateChanged = aTrackBitRateChanged;
            iCallbackTrackBitRateChanged = new Callback(PropertyTrackBitRateChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkDs1SetPropertyTrackBitRateChanged(iHandle, iCallbackTrackBitRateChanged, ptr);
        }

        private void PropertyTrackBitRateChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkDs1 self = (CpProxyLinnCoUkDs1)gch.Target;
            self.iTrackBitRateChanged();
        }

        public void SetPropertyTrackLosslessChanged(CallbackPropertyChanged aTrackLosslessChanged)
        {
            iTrackLosslessChanged = aTrackLosslessChanged;
            iCallbackTrackLosslessChanged = new Callback(PropertyTrackLosslessChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkDs1SetPropertyTrackLosslessChanged(iHandle, iCallbackTrackLosslessChanged, ptr);
        }

        private void PropertyTrackLosslessChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkDs1 self = (CpProxyLinnCoUkDs1)gch.Target;
            self.iTrackLosslessChanged();
        }

        public void SetPropertyTrackBitDepthChanged(CallbackPropertyChanged aTrackBitDepthChanged)
        {
            iTrackBitDepthChanged = aTrackBitDepthChanged;
            iCallbackTrackBitDepthChanged = new Callback(PropertyTrackBitDepthChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkDs1SetPropertyTrackBitDepthChanged(iHandle, iCallbackTrackBitDepthChanged, ptr);
        }

        private void PropertyTrackBitDepthChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkDs1 self = (CpProxyLinnCoUkDs1)gch.Target;
            self.iTrackBitDepthChanged();
        }

        public void SetPropertyTrackSampleRateChanged(CallbackPropertyChanged aTrackSampleRateChanged)
        {
            iTrackSampleRateChanged = aTrackSampleRateChanged;
            iCallbackTrackSampleRateChanged = new Callback(PropertyTrackSampleRateChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkDs1SetPropertyTrackSampleRateChanged(iHandle, iCallbackTrackSampleRateChanged, ptr);
        }

        private void PropertyTrackSampleRateChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkDs1 self = (CpProxyLinnCoUkDs1)gch.Target;
            self.iTrackSampleRateChanged();
        }

        public void SetPropertyTrackCodecNameChanged(CallbackPropertyChanged aTrackCodecNameChanged)
        {
            iTrackCodecNameChanged = aTrackCodecNameChanged;
            iCallbackTrackCodecNameChanged = new Callback(PropertyTrackCodecNameChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkDs1SetPropertyTrackCodecNameChanged(iHandle, iCallbackTrackCodecNameChanged, ptr);
        }

        private void PropertyTrackCodecNameChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkDs1 self = (CpProxyLinnCoUkDs1)gch.Target;
            self.iTrackCodecNameChanged();
        }

        public void SetPropertyTrackIdChanged(CallbackPropertyChanged aTrackIdChanged)
        {
            iTrackIdChanged = aTrackIdChanged;
            iCallbackTrackIdChanged = new Callback(PropertyTrackIdChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkDs1SetPropertyTrackIdChanged(iHandle, iCallbackTrackIdChanged, ptr);
        }

        private void PropertyTrackIdChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkDs1 self = (CpProxyLinnCoUkDs1)gch.Target;
            self.iTrackIdChanged();
        }

        public void SetPropertyTransportStateChanged(CallbackPropertyChanged aTransportStateChanged)
        {
            iTransportStateChanged = aTransportStateChanged;
            iCallbackTransportStateChanged = new Callback(PropertyTransportStateChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkDs1SetPropertyTransportStateChanged(iHandle, iCallbackTransportStateChanged, ptr);
        }

        private void PropertyTransportStateChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkDs1 self = (CpProxyLinnCoUkDs1)gch.Target;
            self.iTransportStateChanged();
        }

        public unsafe void PropertySupportedProtocols(out string aSupportedProtocols)
        {
			char* ptr;
            CpProxyLinnCoUkDs1PropertySupportedProtocols(iHandle, &ptr);
            aSupportedProtocols = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyTrackDuration(out uint aTrackDuration)
        {
			fixed (uint* trackDuration = &aTrackDuration)
			{
	            CpProxyLinnCoUkDs1PropertyTrackDuration(iHandle, trackDuration);
			}
        }

        public unsafe void PropertyTrackBitRate(out uint aTrackBitRate)
        {
			fixed (uint* trackBitRate = &aTrackBitRate)
			{
	            CpProxyLinnCoUkDs1PropertyTrackBitRate(iHandle, trackBitRate);
			}
        }

        public unsafe void PropertyTrackLossless(out bool aTrackLossless)
        {
			uint trackLossless;
	        CpProxyLinnCoUkDs1PropertyTrackLossless(iHandle, &trackLossless);
			aTrackLossless = (trackLossless != 0);
        }

        public unsafe void PropertyTrackBitDepth(out uint aTrackBitDepth)
        {
			fixed (uint* trackBitDepth = &aTrackBitDepth)
			{
	            CpProxyLinnCoUkDs1PropertyTrackBitDepth(iHandle, trackBitDepth);
			}
        }

        public unsafe void PropertyTrackSampleRate(out uint aTrackSampleRate)
        {
			fixed (uint* trackSampleRate = &aTrackSampleRate)
			{
	            CpProxyLinnCoUkDs1PropertyTrackSampleRate(iHandle, trackSampleRate);
			}
        }

        public unsafe void PropertyTrackCodecName(out string aTrackCodecName)
        {
			char* ptr;
            CpProxyLinnCoUkDs1PropertyTrackCodecName(iHandle, &ptr);
            aTrackCodecName = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyTrackId(out uint aTrackId)
        {
			fixed (uint* trackId = &aTrackId)
			{
	            CpProxyLinnCoUkDs1PropertyTrackId(iHandle, trackId);
			}
        }

        public unsafe void PropertyTransportState(out string aTransportState)
        {
			char* ptr;
            CpProxyLinnCoUkDs1PropertyTransportState(iHandle, &ptr);
            aTransportState = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkDs1()
        {
            DoDispose(false);
        }

        private void DoDispose(bool aDisposing)
        {
            IntPtr handle;
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                handle = iHandle;
                iHandle = IntPtr.Zero;
            }
            CpProxyLinnCoUkDs1Destroy(handle);
            iGch.Free();
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
            else
            {
                DisposeProxy();
            }
        }
    }
}

