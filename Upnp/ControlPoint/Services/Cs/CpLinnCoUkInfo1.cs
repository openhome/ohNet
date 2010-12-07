using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkInfo1 : ICpProxy, IDisposable
    {
        void SyncCounters(out uint aaTrackCount, out uint aaDetailsCount, out uint aaMetatextCount);
        void BeginCounters(CpProxy.CallbackAsyncComplete aCallback);
        void EndCounters(IntPtr aAsyncHandle, out uint aaTrackCount, out uint aaDetailsCount, out uint aaMetatextCount);
        void SyncTrack(out string aaUri, out string aaMetadata);
        void BeginTrack(CpProxy.CallbackAsyncComplete aCallback);
        void EndTrack(IntPtr aAsyncHandle, out string aaUri, out string aaMetadata);
        void SyncDetails(out uint aaDuration, out uint aaBitRate, out uint aaBitDepth, out uint aaSampleRate, out bool aaLossless, out string aaCodecName);
        void BeginDetails(CpProxy.CallbackAsyncComplete aCallback);
        void EndDetails(IntPtr aAsyncHandle, out uint aaDuration, out uint aaBitRate, out uint aaBitDepth, out uint aaSampleRate, out bool aaLossless, out string aaCodecName);
        void SyncMetatext(out string aaMetatext);
        void BeginMetatext(CpProxy.CallbackAsyncComplete aCallback);
        void EndMetatext(IntPtr aAsyncHandle, out string aaMetatext);

        void SetPropertyTrackCountChanged(CpProxy.CallbackPropertyChanged aTrackCountChanged);
        void PropertyTrackCount(out uint aTrackCount);
        void SetPropertyDetailsCountChanged(CpProxy.CallbackPropertyChanged aDetailsCountChanged);
        void PropertyDetailsCount(out uint aDetailsCount);
        void SetPropertyMetatextCountChanged(CpProxy.CallbackPropertyChanged aMetatextCountChanged);
        void PropertyMetatextCount(out uint aMetatextCount);
        void SetPropertyUriChanged(CpProxy.CallbackPropertyChanged aUriChanged);
        void PropertyUri(out string aUri);
        void SetPropertyMetadataChanged(CpProxy.CallbackPropertyChanged aMetadataChanged);
        void PropertyMetadata(out string aMetadata);
        void SetPropertyDurationChanged(CpProxy.CallbackPropertyChanged aDurationChanged);
        void PropertyDuration(out uint aDuration);
        void SetPropertyBitRateChanged(CpProxy.CallbackPropertyChanged aBitRateChanged);
        void PropertyBitRate(out uint aBitRate);
        void SetPropertyBitDepthChanged(CpProxy.CallbackPropertyChanged aBitDepthChanged);
        void PropertyBitDepth(out uint aBitDepth);
        void SetPropertySampleRateChanged(CpProxy.CallbackPropertyChanged aSampleRateChanged);
        void PropertySampleRate(out uint aSampleRate);
        void SetPropertyLosslessChanged(CpProxy.CallbackPropertyChanged aLosslessChanged);
        void PropertyLossless(out bool aLossless);
        void SetPropertyCodecNameChanged(CpProxy.CallbackPropertyChanged aCodecNameChanged);
        void PropertyCodecName(out string aCodecName);
        void SetPropertyMetatextChanged(CpProxy.CallbackPropertyChanged aMetatextChanged);
        void PropertyMetatext(out string aMetatext);
    }

    /// <summary>
    /// Proxy for the linn.co.uk:Info:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkInfo1 : CpProxy, IDisposable, ICpProxyLinnCoUkInfo1
    {
        [DllImport("CpLinnCoUkInfo1")]
        static extern IntPtr CpProxyLinnCoUkInfo1Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1SyncCounters(IntPtr aHandle, uint* aaTrackCount, uint* aaDetailsCount, uint* aaMetatextCount);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1BeginCounters(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe int CpProxyLinnCoUkInfo1EndCounters(IntPtr aHandle, IntPtr aAsync, uint* aaTrackCount, uint* aaDetailsCount, uint* aaMetatextCount);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1SyncTrack(IntPtr aHandle, char** aaUri, char** aaMetadata);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1BeginTrack(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe int CpProxyLinnCoUkInfo1EndTrack(IntPtr aHandle, IntPtr aAsync, char** aaUri, char** aaMetadata);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1SyncDetails(IntPtr aHandle, uint* aaDuration, uint* aaBitRate, uint* aaBitDepth, uint* aaSampleRate, uint* aaLossless, char** aaCodecName);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1BeginDetails(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe int CpProxyLinnCoUkInfo1EndDetails(IntPtr aHandle, IntPtr aAsync, uint* aaDuration, uint* aaBitRate, uint* aaBitDepth, uint* aaSampleRate, uint* aaLossless, char** aaCodecName);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1SyncMetatext(IntPtr aHandle, char** aaMetatext);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1BeginMetatext(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe int CpProxyLinnCoUkInfo1EndMetatext(IntPtr aHandle, IntPtr aAsync, char** aaMetatext);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyTrackCountChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyDetailsCountChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyMetatextCountChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyUriChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyMetadataChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyDurationChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyBitRateChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyBitDepthChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertySampleRateChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyLosslessChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyCodecNameChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern void CpProxyLinnCoUkInfo1SetPropertyMetatextChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyTrackCount(IntPtr aHandle, uint* aTrackCount);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyDetailsCount(IntPtr aHandle, uint* aDetailsCount);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyMetatextCount(IntPtr aHandle, uint* aMetatextCount);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyUri(IntPtr aHandle, char** aUri);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyMetadata(IntPtr aHandle, char** aMetadata);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyDuration(IntPtr aHandle, uint* aDuration);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyBitRate(IntPtr aHandle, uint* aBitRate);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyBitDepth(IntPtr aHandle, uint* aBitDepth);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertySampleRate(IntPtr aHandle, uint* aSampleRate);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyLossless(IntPtr aHandle, uint* aLossless);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyCodecName(IntPtr aHandle, char** aCodecName);
        [DllImport("CpLinnCoUkInfo1")]
        static extern unsafe void CpProxyLinnCoUkInfo1PropertyMetatext(IntPtr aHandle, char** aMetatext);
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkInfo1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkInfo1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaTrackCount"></param>
        /// <param name="aaDetailsCount"></param>
        /// <param name="aaMetatextCount"></param>
        public unsafe void SyncCounters(out uint aaTrackCount, out uint aaDetailsCount, out uint aaMetatextCount)
        {
            fixed (uint* aTrackCount = &aaTrackCount)
            fixed (uint* aDetailsCount = &aaDetailsCount)
            fixed (uint* aMetatextCount = &aaMetatextCount)
            {
                CpProxyLinnCoUkInfo1SyncCounters(iHandle, aTrackCount, aDetailsCount, aMetatextCount);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCounters().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginCounters(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkInfo1BeginCounters(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaTrackCount"></param>
        /// <param name="aaDetailsCount"></param>
        /// <param name="aaMetatextCount"></param>
        public unsafe void EndCounters(IntPtr aAsyncHandle, out uint aaTrackCount, out uint aaDetailsCount, out uint aaMetatextCount)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
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

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndTrack().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginTrack(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkInfo1BeginTrack(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        public unsafe void EndTrack(IntPtr aAsyncHandle, out string aaUri, out string aaMetadata)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaDuration"></param>
        /// <param name="aaBitRate"></param>
        /// <param name="aaBitDepth"></param>
        /// <param name="aaSampleRate"></param>
        /// <param name="aaLossless"></param>
        /// <param name="aaCodecName"></param>
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

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDetails().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDetails(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkInfo1BeginDetails(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaDuration"></param>
        /// <param name="aaBitRate"></param>
        /// <param name="aaBitDepth"></param>
        /// <param name="aaSampleRate"></param>
        /// <param name="aaLossless"></param>
        /// <param name="aaCodecName"></param>
        public unsafe void EndDetails(IntPtr aAsyncHandle, out uint aaDuration, out uint aaBitRate, out uint aaBitDepth, out uint aaSampleRate, out bool aaLossless, out string aaCodecName)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaMetatext"></param>
        public unsafe void SyncMetatext(out string aaMetatext)
        {
            char* aMetatext;
            {
                CpProxyLinnCoUkInfo1SyncMetatext(iHandle, &aMetatext);
            }
            aaMetatext = Marshal.PtrToStringAnsi((IntPtr)aMetatext);
            ZappFree(aMetatext);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndMetatext().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginMetatext(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkInfo1BeginMetatext(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaMetatext"></param>
        public unsafe void EndMetatext(IntPtr aAsyncHandle, out string aaMetatext)
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

        /// <summary>
        /// Set a delegate to be run when the TrackCount state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkInfo1 instance will not overlap.</remarks>
        /// <param name="aTrackCountChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the DetailsCount state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkInfo1 instance will not overlap.</remarks>
        /// <param name="aDetailsCountChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the MetatextCount state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkInfo1 instance will not overlap.</remarks>
        /// <param name="aMetatextCountChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the Uri state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkInfo1 instance will not overlap.</remarks>
        /// <param name="aUriChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the Metadata state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkInfo1 instance will not overlap.</remarks>
        /// <param name="aMetadataChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the Duration state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkInfo1 instance will not overlap.</remarks>
        /// <param name="aDurationChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the BitRate state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkInfo1 instance will not overlap.</remarks>
        /// <param name="aBitRateChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the BitDepth state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkInfo1 instance will not overlap.</remarks>
        /// <param name="aBitDepthChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the SampleRate state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkInfo1 instance will not overlap.</remarks>
        /// <param name="aSampleRateChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the Lossless state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkInfo1 instance will not overlap.</remarks>
        /// <param name="aLosslessChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the CodecName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkInfo1 instance will not overlap.</remarks>
        /// <param name="aCodecNameChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the Metatext state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkInfo1 instance will not overlap.</remarks>
        /// <param name="aMetatextChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Query the value of the TrackCount property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTrackCount">Will be set to the value of the property</param>
        public unsafe void PropertyTrackCount(out uint aTrackCount)
        {
            fixed (uint* trackCount = &aTrackCount)
            {
                CpProxyLinnCoUkInfo1PropertyTrackCount(iHandle, trackCount);
            }
        }

        /// <summary>
        /// Query the value of the DetailsCount property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDetailsCount">Will be set to the value of the property</param>
        public unsafe void PropertyDetailsCount(out uint aDetailsCount)
        {
            fixed (uint* detailsCount = &aDetailsCount)
            {
                CpProxyLinnCoUkInfo1PropertyDetailsCount(iHandle, detailsCount);
            }
        }

        /// <summary>
        /// Query the value of the MetatextCount property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aMetatextCount">Will be set to the value of the property</param>
        public unsafe void PropertyMetatextCount(out uint aMetatextCount)
        {
            fixed (uint* metatextCount = &aMetatextCount)
            {
                CpProxyLinnCoUkInfo1PropertyMetatextCount(iHandle, metatextCount);
            }
        }

        /// <summary>
        /// Query the value of the Uri property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aUri">Will be set to the value of the property</param>
        public unsafe void PropertyUri(out string aUri)
        {
            char* ptr;
            CpProxyLinnCoUkInfo1PropertyUri(iHandle, &ptr);
            aUri = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the Metadata property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aMetadata">Will be set to the value of the property</param>
        public unsafe void PropertyMetadata(out string aMetadata)
        {
            char* ptr;
            CpProxyLinnCoUkInfo1PropertyMetadata(iHandle, &ptr);
            aMetadata = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the Duration property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDuration">Will be set to the value of the property</param>
        public unsafe void PropertyDuration(out uint aDuration)
        {
            fixed (uint* duration = &aDuration)
            {
                CpProxyLinnCoUkInfo1PropertyDuration(iHandle, duration);
            }
        }

        /// <summary>
        /// Query the value of the BitRate property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aBitRate">Will be set to the value of the property</param>
        public unsafe void PropertyBitRate(out uint aBitRate)
        {
            fixed (uint* bitRate = &aBitRate)
            {
                CpProxyLinnCoUkInfo1PropertyBitRate(iHandle, bitRate);
            }
        }

        /// <summary>
        /// Query the value of the BitDepth property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aBitDepth">Will be set to the value of the property</param>
        public unsafe void PropertyBitDepth(out uint aBitDepth)
        {
            fixed (uint* bitDepth = &aBitDepth)
            {
                CpProxyLinnCoUkInfo1PropertyBitDepth(iHandle, bitDepth);
            }
        }

        /// <summary>
        /// Query the value of the SampleRate property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aSampleRate">Will be set to the value of the property</param>
        public unsafe void PropertySampleRate(out uint aSampleRate)
        {
            fixed (uint* sampleRate = &aSampleRate)
            {
                CpProxyLinnCoUkInfo1PropertySampleRate(iHandle, sampleRate);
            }
        }

        /// <summary>
        /// Query the value of the Lossless property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aLossless">Will be set to the value of the property</param>
        public unsafe void PropertyLossless(out bool aLossless)
        {
            uint lossless;
            CpProxyLinnCoUkInfo1PropertyLossless(iHandle, &lossless);
            aLossless = (lossless != 0);
        }

        /// <summary>
        /// Query the value of the CodecName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aCodecName">Will be set to the value of the property</param>
        public unsafe void PropertyCodecName(out string aCodecName)
        {
            char* ptr;
            CpProxyLinnCoUkInfo1PropertyCodecName(iHandle, &ptr);
            aCodecName = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the Metatext property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aMetatext">Will be set to the value of the property</param>
        public unsafe void PropertyMetatext(out string aMetatext)
        {
            char* ptr;
            CpProxyLinnCoUkInfo1PropertyMetatext(iHandle, &ptr);
            aMetatext = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
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
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                CpProxyLinnCoUkInfo1Destroy(iHandle);
                iHandle = IntPtr.Zero;
            }
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

