using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkDs1 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkDs1")]
        static extern uint CpProxyLinnCoUkDs1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncPlay(uint aHandle);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginPlay(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndPlay(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncPause(uint aHandle);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginPause(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndPause(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncStop(uint aHandle);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginStop(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndStop(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncSeekSecondAbsolute(uint aHandle, uint aaSecond);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginSeekSecondAbsolute(uint aHandle, uint aaSecond, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndSeekSecondAbsolute(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncSeekSecondRelative(uint aHandle, int aaSecond);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginSeekSecondRelative(uint aHandle, int aaSecond, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndSeekSecondRelative(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncSeekTrackId(uint aHandle, uint aaTrackId);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginSeekTrackId(uint aHandle, uint aaTrackId, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndSeekTrackId(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncSeekTrackAbsolute(uint aHandle, uint aaTrack);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginSeekTrackAbsolute(uint aHandle, uint aaTrack, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndSeekTrackAbsolute(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncSeekTrackRelative(uint aHandle, int aaTrack);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginSeekTrackRelative(uint aHandle, int aaTrack, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndSeekTrackRelative(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncState(uint aHandle, char** aaTransportState, uint* aaTrackDuration, uint* aaTrackBitRate, uint* aaTrackLossless, uint* aaTrackBitDepth, uint* aaTrackSampleRate, char** aaTrackCodecName, uint* aaTrackId);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginState(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndState(uint aHandle, uint aAsync, char** aaTransportState, uint* aaTrackDuration, uint* aaTrackBitRate, uint* aaTrackLossless, uint* aaTrackBitDepth, uint* aaTrackSampleRate, char** aaTrackCodecName, uint* aaTrackId);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1SyncProtocolInfo(uint aHandle, char** aaSupportedProtocols);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1BeginProtocolInfo(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe int CpProxyLinnCoUkDs1EndProtocolInfo(uint aHandle, uint aAsync, char** aaSupportedProtocols);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertySupportedProtocolsChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTrackDurationChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTrackBitRateChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTrackLosslessChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTrackBitDepthChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTrackSampleRateChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTrackCodecNameChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTrackIdChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern void CpProxyLinnCoUkDs1SetPropertyTransportStateChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertySupportedProtocols(uint aHandle, char** aSupportedProtocols);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTrackDuration(uint aHandle, uint* aTrackDuration);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTrackBitRate(uint aHandle, uint* aTrackBitRate);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTrackLossless(uint aHandle, uint* aTrackLossless);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTrackBitDepth(uint aHandle, uint* aTrackBitDepth);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTrackSampleRate(uint aHandle, uint* aTrackSampleRate);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTrackCodecName(uint aHandle, char** aTrackCodecName);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTrackId(uint aHandle, uint* aTrackId);
        [DllImport("CpLinnCoUkDs1")]
        static extern unsafe void CpProxyLinnCoUkDs1PropertyTransportState(uint aHandle, char** aTransportState);
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

        public unsafe void EndPlay(uint aAsyncHandle)
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

        public unsafe void EndPause(uint aAsyncHandle)
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

        public unsafe void EndStop(uint aAsyncHandle)
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

        public unsafe void EndSeekSecondAbsolute(uint aAsyncHandle)
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

        public unsafe void EndSeekSecondRelative(uint aAsyncHandle)
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

        public unsafe void EndSeekTrackId(uint aAsyncHandle)
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

        public unsafe void EndSeekTrackAbsolute(uint aAsyncHandle)
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

        public unsafe void EndSeekTrackRelative(uint aAsyncHandle)
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

        public unsafe void EndState(uint aAsyncHandle, out string aaTransportState, out uint aaTrackDuration, out uint aaTrackBitRate, out bool aaTrackLossless, out uint aaTrackBitDepth, out uint aaTrackSampleRate, out string aaTrackCodecName, out uint aaTrackId)
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

        public unsafe void EndProtocolInfo(uint aAsyncHandle, out string aaSupportedProtocols)
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

