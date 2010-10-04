using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkInfo1 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkInfo1")]
        static extern uint CpProxyLinnCoUkInfo1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1SyncCounters(uint aHandle, uint* aaTrackCount, uint* aaDetailsCount, uint* aaMetatextCount);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1BeginCounters(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe int CpProxyLinnCoUkInfo1EndCounters(uint aHandle, uint aAsync, uint* aaTrackCount, uint* aaDetailsCount, uint* aaMetatextCount);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1SyncTrack(uint aHandle, char** aaUri, char** aaMetadata);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1BeginTrack(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe int CpProxyLinnCoUkInfo1EndTrack(uint aHandle, uint aAsync, char** aaUri, char** aaMetadata);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1SyncDetails(uint aHandle, uint* aaDuration, uint* aaBitRate, uint* aaBitDepth, uint* aaSampleRate, uint* aaLossless, char** aaCodecName);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1BeginDetails(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe int CpProxyLinnCoUkInfo1EndDetails(uint aHandle, uint aAsync, uint* aaDuration, uint* aaBitRate, uint* aaBitDepth, uint* aaSampleRate, uint* aaLossless, char** aaCodecName);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1SyncMetatext(uint aHandle, char** aaMetatext);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1BeginMetatext(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe int CpProxyLinnCoUkInfo1EndMetatext(uint aHandle, uint aAsync, char** aaMetatext);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyTrackCountChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyDetailsCountChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyMetatextCountChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyUriChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyMetadataChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyDurationChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyBitRateChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyBitDepthChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertySampleRateChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyLosslessChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyCodecNameChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyMetatextChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyTrackCount(uint aHandle, uint* aTrackCount);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyDetailsCount(uint aHandle, uint* aDetailsCount);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyMetatextCount(uint aHandle, uint* aMetatextCount);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyUri(uint aHandle, char** aUri);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyMetadata(uint aHandle, char** aMetadata);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyDuration(uint aHandle, uint* aDuration);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyBitRate(uint aHandle, uint* aBitRate);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyBitDepth(uint aHandle, uint* aBitDepth);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertySampleRate(uint aHandle, uint* aSampleRate);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyLossless(uint aHandle, uint* aLossless);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyCodecName(uint aHandle, char** aCodecName);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyMetatext(uint aHandle, char** aMetatext);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iTrackCountChanged;
        private CallbackPropertyChanged iDetailsCountChanged;
        private CallbackPropertyChanged iMetatextCountChanged;
        private CallbackPropertyChanged iUriChanged;
        private CallbackPropertyChanged iMetadataChanged;
        private CallbackPropertyChanged iDurationChanged;
        private CallbackPropertyChanged iBitRateChanged;
        private CallbackPropertyChanged iBitDepthChanged;
        private CallbackPropertyChanged iSampleRateChanged;
        private CallbackPropertyChanged iLosslessChanged;
        private CallbackPropertyChanged iCodecNameChanged;
        private CallbackPropertyChanged iMetatextChanged;
        private Callback iCallbackTrackCountChanged;
        private Callback iCallbackDetailsCountChanged;
        private Callback iCallbackMetatextCountChanged;
        private Callback iCallbackUriChanged;
        private Callback iCallbackMetadataChanged;
        private Callback iCallbackDurationChanged;
        private Callback iCallbackBitRateChanged;
        private Callback iCallbackBitDepthChanged;
        private Callback iCallbackSampleRateChanged;
        private Callback iCallbackLosslessChanged;
        private Callback iCallbackCodecNameChanged;
        private Callback iCallbackMetatextChanged;

        public CpProxyLinnCoUkInfo1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkInfo1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncCounters(out uint aaTrackCount, out uint aaDetailsCount, out uint aaMetatextCount)
        {
			fixed (uint* aTrackCount = &aaTrackCount)
			fixed (uint* aDetailsCount = &aaDetailsCount)
			fixed (uint* aMetatextCount = &aaMetatextCount)
			{
				CpProxyLinnCoUkInfo1SyncCounters(iHandle, aTrackCount, aDetailsCount, aMetatextCount);
			}
        }

        public unsafe void BeginCounters(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkInfo1BeginCounters(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndCounters(uint aAsyncHandle, out uint aaTrackCount, out uint aaDetailsCount, out uint aaMetatextCount)
        {
			fixed (uint* aTrackCount = &aaTrackCount)
			fixed (uint* aDetailsCount = &aaDetailsCount)
			fixed (uint* aMetatextCount = &aaMetatextCount)
			{
				if (0 != CpProxyLinnCoUkInfo1EndCounters(iHandle, aAsyncHandle, aTrackCount, aDetailsCount, aMetatextCount))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncTrack(out string aaUri, out string aaMetadata)
        {
			char* aUri;
			char* aMetadata;
			{
				CpProxyLinnCoUkInfo1SyncTrack(iHandle, &aUri, &aMetadata);
			}
            aaUri = Marshal.PtrToStringAnsi((IntPtr)aUri);
            ZappFree(aUri);
            aaMetadata = Marshal.PtrToStringAnsi((IntPtr)aMetadata);
            ZappFree(aMetadata);
        }

        public unsafe void BeginTrack(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkInfo1BeginTrack(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndTrack(uint aAsyncHandle, out string aaUri, out string aaMetadata)
        {
			char* aUri;
			char* aMetadata;
			{
				if (0 != CpProxyLinnCoUkInfo1EndTrack(iHandle, aAsyncHandle, &aUri, &aMetadata))
				{
					throw(new ProxyError());
				}
			}
            aaUri = Marshal.PtrToStringAnsi((IntPtr)aUri);
            ZappFree(aUri);
            aaMetadata = Marshal.PtrToStringAnsi((IntPtr)aMetadata);
            ZappFree(aMetadata);
        }

        public unsafe void SyncDetails(out uint aaDuration, out uint aaBitRate, out uint aaBitDepth, out uint aaSampleRate, out bool aaLossless, out string aaCodecName)
        {
			uint aLossless;
			char* aCodecName;
			fixed (uint* aDuration = &aaDuration)
			fixed (uint* aBitRate = &aaBitRate)
			fixed (uint* aBitDepth = &aaBitDepth)
			fixed (uint* aSampleRate = &aaSampleRate)
			{
				CpProxyLinnCoUkInfo1SyncDetails(iHandle, aDuration, aBitRate, aBitDepth, aSampleRate, &aLossless, &aCodecName);
			}
			aaLossless = (aLossless != 0);
            aaCodecName = Marshal.PtrToStringAnsi((IntPtr)aCodecName);
            ZappFree(aCodecName);
        }

        public unsafe void BeginDetails(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkInfo1BeginDetails(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDetails(uint aAsyncHandle, out uint aaDuration, out uint aaBitRate, out uint aaBitDepth, out uint aaSampleRate, out bool aaLossless, out string aaCodecName)
        {
			uint aLossless;
			char* aCodecName;
			fixed (uint* aDuration = &aaDuration)
			fixed (uint* aBitRate = &aaBitRate)
			fixed (uint* aBitDepth = &aaBitDepth)
			fixed (uint* aSampleRate = &aaSampleRate)
			{
				if (0 != CpProxyLinnCoUkInfo1EndDetails(iHandle, aAsyncHandle, aDuration, aBitRate, aBitDepth, aSampleRate, &aLossless, &aCodecName))
				{
					throw(new ProxyError());
				}
			}
			aaLossless = (aLossless != 0);
            aaCodecName = Marshal.PtrToStringAnsi((IntPtr)aCodecName);
            ZappFree(aCodecName);
        }

        public unsafe void SyncMetatext(out string aaMetatext)
        {
			char* aMetatext;
			{
				CpProxyLinnCoUkInfo1SyncMetatext(iHandle, &aMetatext);
			}
            aaMetatext = Marshal.PtrToStringAnsi((IntPtr)aMetatext);
            ZappFree(aMetatext);
        }

        public unsafe void BeginMetatext(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkInfo1BeginMetatext(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndMetatext(uint aAsyncHandle, out string aaMetatext)
        {
			char* aMetatext;
			{
				if (0 != CpProxyLinnCoUkInfo1EndMetatext(iHandle, aAsyncHandle, &aMetatext))
				{
					throw(new ProxyError());
				}
			}
            aaMetatext = Marshal.PtrToStringAnsi((IntPtr)aMetatext);
            ZappFree(aMetatext);
        }

        public void SetPropertyTrackCountChanged(CallbackPropertyChanged aTrackCountChanged)
        {
            iTrackCountChanged = aTrackCountChanged;
            iCallbackTrackCountChanged = new Callback(PropertyTrackCountChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkInfo1SetPropertyTrackCountChanged(iHandle, iCallbackTrackCountChanged, ptr);
        }

        private void PropertyTrackCountChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkInfo1 self = (CpProxyLinnCoUkInfo1)gch.Target;
            self.iTrackCountChanged();
        }

        public void SetPropertyDetailsCountChanged(CallbackPropertyChanged aDetailsCountChanged)
        {
            iDetailsCountChanged = aDetailsCountChanged;
            iCallbackDetailsCountChanged = new Callback(PropertyDetailsCountChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkInfo1SetPropertyDetailsCountChanged(iHandle, iCallbackDetailsCountChanged, ptr);
        }

        private void PropertyDetailsCountChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkInfo1 self = (CpProxyLinnCoUkInfo1)gch.Target;
            self.iDetailsCountChanged();
        }

        public void SetPropertyMetatextCountChanged(CallbackPropertyChanged aMetatextCountChanged)
        {
            iMetatextCountChanged = aMetatextCountChanged;
            iCallbackMetatextCountChanged = new Callback(PropertyMetatextCountChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkInfo1SetPropertyMetatextCountChanged(iHandle, iCallbackMetatextCountChanged, ptr);
        }

        private void PropertyMetatextCountChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkInfo1 self = (CpProxyLinnCoUkInfo1)gch.Target;
            self.iMetatextCountChanged();
        }

        public void SetPropertyUriChanged(CallbackPropertyChanged aUriChanged)
        {
            iUriChanged = aUriChanged;
            iCallbackUriChanged = new Callback(PropertyUriChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkInfo1SetPropertyUriChanged(iHandle, iCallbackUriChanged, ptr);
        }

        private void PropertyUriChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkInfo1 self = (CpProxyLinnCoUkInfo1)gch.Target;
            self.iUriChanged();
        }

        public void SetPropertyMetadataChanged(CallbackPropertyChanged aMetadataChanged)
        {
            iMetadataChanged = aMetadataChanged;
            iCallbackMetadataChanged = new Callback(PropertyMetadataChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkInfo1SetPropertyMetadataChanged(iHandle, iCallbackMetadataChanged, ptr);
        }

        private void PropertyMetadataChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkInfo1 self = (CpProxyLinnCoUkInfo1)gch.Target;
            self.iMetadataChanged();
        }

        public void SetPropertyDurationChanged(CallbackPropertyChanged aDurationChanged)
        {
            iDurationChanged = aDurationChanged;
            iCallbackDurationChanged = new Callback(PropertyDurationChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkInfo1SetPropertyDurationChanged(iHandle, iCallbackDurationChanged, ptr);
        }

        private void PropertyDurationChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkInfo1 self = (CpProxyLinnCoUkInfo1)gch.Target;
            self.iDurationChanged();
        }

        public void SetPropertyBitRateChanged(CallbackPropertyChanged aBitRateChanged)
        {
            iBitRateChanged = aBitRateChanged;
            iCallbackBitRateChanged = new Callback(PropertyBitRateChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkInfo1SetPropertyBitRateChanged(iHandle, iCallbackBitRateChanged, ptr);
        }

        private void PropertyBitRateChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkInfo1 self = (CpProxyLinnCoUkInfo1)gch.Target;
            self.iBitRateChanged();
        }

        public void SetPropertyBitDepthChanged(CallbackPropertyChanged aBitDepthChanged)
        {
            iBitDepthChanged = aBitDepthChanged;
            iCallbackBitDepthChanged = new Callback(PropertyBitDepthChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkInfo1SetPropertyBitDepthChanged(iHandle, iCallbackBitDepthChanged, ptr);
        }

        private void PropertyBitDepthChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkInfo1 self = (CpProxyLinnCoUkInfo1)gch.Target;
            self.iBitDepthChanged();
        }

        public void SetPropertySampleRateChanged(CallbackPropertyChanged aSampleRateChanged)
        {
            iSampleRateChanged = aSampleRateChanged;
            iCallbackSampleRateChanged = new Callback(PropertySampleRateChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkInfo1SetPropertySampleRateChanged(iHandle, iCallbackSampleRateChanged, ptr);
        }

        private void PropertySampleRateChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkInfo1 self = (CpProxyLinnCoUkInfo1)gch.Target;
            self.iSampleRateChanged();
        }

        public void SetPropertyLosslessChanged(CallbackPropertyChanged aLosslessChanged)
        {
            iLosslessChanged = aLosslessChanged;
            iCallbackLosslessChanged = new Callback(PropertyLosslessChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkInfo1SetPropertyLosslessChanged(iHandle, iCallbackLosslessChanged, ptr);
        }

        private void PropertyLosslessChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkInfo1 self = (CpProxyLinnCoUkInfo1)gch.Target;
            self.iLosslessChanged();
        }

        public void SetPropertyCodecNameChanged(CallbackPropertyChanged aCodecNameChanged)
        {
            iCodecNameChanged = aCodecNameChanged;
            iCallbackCodecNameChanged = new Callback(PropertyCodecNameChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkInfo1SetPropertyCodecNameChanged(iHandle, iCallbackCodecNameChanged, ptr);
        }

        private void PropertyCodecNameChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkInfo1 self = (CpProxyLinnCoUkInfo1)gch.Target;
            self.iCodecNameChanged();
        }

        public void SetPropertyMetatextChanged(CallbackPropertyChanged aMetatextChanged)
        {
            iMetatextChanged = aMetatextChanged;
            iCallbackMetatextChanged = new Callback(PropertyMetatextChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkInfo1SetPropertyMetatextChanged(iHandle, iCallbackMetatextChanged, ptr);
        }

        private void PropertyMetatextChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkInfo1 self = (CpProxyLinnCoUkInfo1)gch.Target;
            self.iMetatextChanged();
        }

        public unsafe void PropertyTrackCount(out uint aTrackCount)
        {
			fixed (uint* trackCount = &aTrackCount)
			{
	            CpProxyLinnCoUkInfo1PropertyTrackCount(iHandle, trackCount);
			}
        }

        public unsafe void PropertyDetailsCount(out uint aDetailsCount)
        {
			fixed (uint* detailsCount = &aDetailsCount)
			{
	            CpProxyLinnCoUkInfo1PropertyDetailsCount(iHandle, detailsCount);
			}
        }

        public unsafe void PropertyMetatextCount(out uint aMetatextCount)
        {
			fixed (uint* metatextCount = &aMetatextCount)
			{
	            CpProxyLinnCoUkInfo1PropertyMetatextCount(iHandle, metatextCount);
			}
        }

        public unsafe void PropertyUri(out string aUri)
        {
			char* ptr;
            CpProxyLinnCoUkInfo1PropertyUri(iHandle, &ptr);
            aUri = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyMetadata(out string aMetadata)
        {
			char* ptr;
            CpProxyLinnCoUkInfo1PropertyMetadata(iHandle, &ptr);
            aMetadata = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyDuration(out uint aDuration)
        {
			fixed (uint* duration = &aDuration)
			{
	            CpProxyLinnCoUkInfo1PropertyDuration(iHandle, duration);
			}
        }

        public unsafe void PropertyBitRate(out uint aBitRate)
        {
			fixed (uint* bitRate = &aBitRate)
			{
	            CpProxyLinnCoUkInfo1PropertyBitRate(iHandle, bitRate);
			}
        }

        public unsafe void PropertyBitDepth(out uint aBitDepth)
        {
			fixed (uint* bitDepth = &aBitDepth)
			{
	            CpProxyLinnCoUkInfo1PropertyBitDepth(iHandle, bitDepth);
			}
        }

        public unsafe void PropertySampleRate(out uint aSampleRate)
        {
			fixed (uint* sampleRate = &aSampleRate)
			{
	            CpProxyLinnCoUkInfo1PropertySampleRate(iHandle, sampleRate);
			}
        }

        public unsafe void PropertyLossless(out bool aLossless)
        {
			uint lossless;
	        CpProxyLinnCoUkInfo1PropertyLossless(iHandle, &lossless);
			aLossless = (lossless != 0);
        }

        public unsafe void PropertyCodecName(out string aCodecName)
        {
			char* ptr;
            CpProxyLinnCoUkInfo1PropertyCodecName(iHandle, &ptr);
            aCodecName = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyMetatext(out string aMetatext)
        {
			char* ptr;
            CpProxyLinnCoUkInfo1PropertyMetatext(iHandle, &ptr);
            aMetatext = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkInfo1()
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
            CpProxyLinnCoUkInfo1Destroy(handle);
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

