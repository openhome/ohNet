using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkDs1 : ICpProxy, IDisposable
    {
        void SyncPlay();
        void BeginPlay(CpProxy.CallbackAsyncComplete aCallback);
        void EndPlay(uint aAsyncHandle);
        void SyncPause();
        void BeginPause(CpProxy.CallbackAsyncComplete aCallback);
        void EndPause(uint aAsyncHandle);
        void SyncStop();
        void BeginStop(CpProxy.CallbackAsyncComplete aCallback);
        void EndStop(uint aAsyncHandle);
        void SyncSeekSecondAbsolute(uint aaSecond);
        void BeginSeekSecondAbsolute(uint aaSecond, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeekSecondAbsolute(uint aAsyncHandle);
        void SyncSeekSecondRelative(int aaSecond);
        void BeginSeekSecondRelative(int aaSecond, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeekSecondRelative(uint aAsyncHandle);
        void SyncSeekTrackId(uint aaTrackId);
        void BeginSeekTrackId(uint aaTrackId, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeekTrackId(uint aAsyncHandle);
        void SyncSeekTrackAbsolute(uint aaTrack);
        void BeginSeekTrackAbsolute(uint aaTrack, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeekTrackAbsolute(uint aAsyncHandle);
        void SyncSeekTrackRelative(int aaTrack);
        void BeginSeekTrackRelative(int aaTrack, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeekTrackRelative(uint aAsyncHandle);
        void SyncState(out string aaTransportState, out uint aaTrackDuration, out uint aaTrackBitRate, out bool aaTrackLossless, out uint aaTrackBitDepth, out uint aaTrackSampleRate, out string aaTrackCodecName, out uint aaTrackId);
        void BeginState(CpProxy.CallbackAsyncComplete aCallback);
        void EndState(uint aAsyncHandle, out string aaTransportState, out uint aaTrackDuration, out uint aaTrackBitRate, out bool aaTrackLossless, out uint aaTrackBitDepth, out uint aaTrackSampleRate, out string aaTrackCodecName, out uint aaTrackId);
        void SyncProtocolInfo(out string aaSupportedProtocols);
        void BeginProtocolInfo(CpProxy.CallbackAsyncComplete aCallback);
        void EndProtocolInfo(uint aAsyncHandle, out string aaSupportedProtocols);

        void SetPropertySupportedProtocolsChanged(CpProxy.CallbackPropertyChanged aSupportedProtocolsChanged);
        void PropertySupportedProtocols(out string aSupportedProtocols);
        void SetPropertyTrackDurationChanged(CpProxy.CallbackPropertyChanged aTrackDurationChanged);
        void PropertyTrackDuration(out uint aTrackDuration);
        void SetPropertyTrackBitRateChanged(CpProxy.CallbackPropertyChanged aTrackBitRateChanged);
        void PropertyTrackBitRate(out uint aTrackBitRate);
        void SetPropertyTrackLosslessChanged(CpProxy.CallbackPropertyChanged aTrackLosslessChanged);
        void PropertyTrackLossless(out bool aTrackLossless);
        void SetPropertyTrackBitDepthChanged(CpProxy.CallbackPropertyChanged aTrackBitDepthChanged);
        void PropertyTrackBitDepth(out uint aTrackBitDepth);
        void SetPropertyTrackSampleRateChanged(CpProxy.CallbackPropertyChanged aTrackSampleRateChanged);
        void PropertyTrackSampleRate(out uint aTrackSampleRate);
        void SetPropertyTrackCodecNameChanged(CpProxy.CallbackPropertyChanged aTrackCodecNameChanged);
        void PropertyTrackCodecName(out string aTrackCodecName);
        void SetPropertyTrackIdChanged(CpProxy.CallbackPropertyChanged aTrackIdChanged);
        void PropertyTrackId(out uint aTrackId);
        void SetPropertyTransportStateChanged(CpProxy.CallbackPropertyChanged aTransportStateChanged);
        void PropertyTransportState(out string aTransportState);
    }

    public class CpProxyLinnCoUkDs1 : CpProxy, IDisposable, ICpProxyLinnCoUkDs1
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkDs1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkDs1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public unsafe void SyncPlay()
        {
			{
				CpProxyLinnCoUkDs1SyncPlay(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPlay().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginPlay(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginPlay(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndPlay(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndPlay(iHandle, aAsyncHandle))
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
        public unsafe void SyncPause()
        {
			{
				CpProxyLinnCoUkDs1SyncPause(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPause().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginPause(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginPause(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndPause(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndPause(iHandle, aAsyncHandle))
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
        public unsafe void SyncStop()
        {
			{
				CpProxyLinnCoUkDs1SyncStop(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStop().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStop(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginStop(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndStop(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndStop(iHandle, aAsyncHandle))
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
        /// <param name="aaSecond"></param>
        public unsafe void SyncSeekSecondAbsolute(uint aaSecond)
        {
			{
				CpProxyLinnCoUkDs1SyncSeekSecondAbsolute(iHandle, aaSecond);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeekSecondAbsolute().</remarks>
        /// <param name="aaSecond"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSeekSecondAbsolute(uint aaSecond, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginSeekSecondAbsolute(iHandle, aaSecond, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSeekSecondAbsolute(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndSeekSecondAbsolute(iHandle, aAsyncHandle))
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
        /// <param name="aaSecond"></param>
        public unsafe void SyncSeekSecondRelative(int aaSecond)
        {
			{
				CpProxyLinnCoUkDs1SyncSeekSecondRelative(iHandle, aaSecond);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeekSecondRelative().</remarks>
        /// <param name="aaSecond"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSeekSecondRelative(int aaSecond, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginSeekSecondRelative(iHandle, aaSecond, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSeekSecondRelative(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndSeekSecondRelative(iHandle, aAsyncHandle))
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
        /// <param name="aaTrackId"></param>
        public unsafe void SyncSeekTrackId(uint aaTrackId)
        {
			{
				CpProxyLinnCoUkDs1SyncSeekTrackId(iHandle, aaTrackId);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeekTrackId().</remarks>
        /// <param name="aaTrackId"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSeekTrackId(uint aaTrackId, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginSeekTrackId(iHandle, aaTrackId, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSeekTrackId(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndSeekTrackId(iHandle, aAsyncHandle))
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
        /// <param name="aaTrack"></param>
        public unsafe void SyncSeekTrackAbsolute(uint aaTrack)
        {
			{
				CpProxyLinnCoUkDs1SyncSeekTrackAbsolute(iHandle, aaTrack);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeekTrackAbsolute().</remarks>
        /// <param name="aaTrack"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSeekTrackAbsolute(uint aaTrack, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginSeekTrackAbsolute(iHandle, aaTrack, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSeekTrackAbsolute(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndSeekTrackAbsolute(iHandle, aAsyncHandle))
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
        /// <param name="aaTrack"></param>
        public unsafe void SyncSeekTrackRelative(int aaTrack)
        {
			{
				CpProxyLinnCoUkDs1SyncSeekTrackRelative(iHandle, aaTrack);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeekTrackRelative().</remarks>
        /// <param name="aaTrack"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSeekTrackRelative(int aaTrack, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginSeekTrackRelative(iHandle, aaTrack, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSeekTrackRelative(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDs1EndSeekTrackRelative(iHandle, aAsyncHandle))
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
        /// <param name="aaTransportState"></param>
        /// <param name="aaTrackDuration"></param>
        /// <param name="aaTrackBitRate"></param>
        /// <param name="aaTrackLossless"></param>
        /// <param name="aaTrackBitDepth"></param>
        /// <param name="aaTrackSampleRate"></param>
        /// <param name="aaTrackCodecName"></param>
        /// <param name="aaTrackId"></param>
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

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndState().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginState(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginState(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaTransportState"></param>
        /// <param name="aaTrackDuration"></param>
        /// <param name="aaTrackBitRate"></param>
        /// <param name="aaTrackLossless"></param>
        /// <param name="aaTrackBitDepth"></param>
        /// <param name="aaTrackSampleRate"></param>
        /// <param name="aaTrackCodecName"></param>
        /// <param name="aaTrackId"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSupportedProtocols"></param>
        public unsafe void SyncProtocolInfo(out string aaSupportedProtocols)
        {
			char* aSupportedProtocols;
			{
				CpProxyLinnCoUkDs1SyncProtocolInfo(iHandle, &aSupportedProtocols);
			}
            aaSupportedProtocols = Marshal.PtrToStringAnsi((IntPtr)aSupportedProtocols);
            ZappFree(aSupportedProtocols);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndProtocolInfo().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginProtocolInfo(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDs1BeginProtocolInfo(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSupportedProtocols"></param>
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

        /// <summary>
        /// Set a delegate to be run when the SupportedProtocols state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aSupportedProtocolsChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the TrackDuration state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTrackDurationChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the TrackBitRate state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTrackBitRateChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the TrackLossless state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTrackLosslessChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the TrackBitDepth state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTrackBitDepthChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the TrackSampleRate state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTrackSampleRateChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the TrackCodecName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTrackCodecNameChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the TrackId state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTrackIdChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the TransportState state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTransportStateChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Query the value of the SupportedProtocols property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aSupportedProtocols">Will be set to the value of the property</param>
        public unsafe void PropertySupportedProtocols(out string aSupportedProtocols)
        {
			char* ptr;
            CpProxyLinnCoUkDs1PropertySupportedProtocols(iHandle, &ptr);
            aSupportedProtocols = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the TrackDuration property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aTrackDuration">Will be set to the value of the property</param>
        public unsafe void PropertyTrackDuration(out uint aTrackDuration)
        {
			fixed (uint* trackDuration = &aTrackDuration)
			{
	            CpProxyLinnCoUkDs1PropertyTrackDuration(iHandle, trackDuration);
			}
        }

        /// <summary>
        /// Query the value of the TrackBitRate property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aTrackBitRate">Will be set to the value of the property</param>
        public unsafe void PropertyTrackBitRate(out uint aTrackBitRate)
        {
			fixed (uint* trackBitRate = &aTrackBitRate)
			{
	            CpProxyLinnCoUkDs1PropertyTrackBitRate(iHandle, trackBitRate);
			}
        }

        /// <summary>
        /// Query the value of the TrackLossless property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aTrackLossless">Will be set to the value of the property</param>
        public unsafe void PropertyTrackLossless(out bool aTrackLossless)
        {
			uint trackLossless;
	        CpProxyLinnCoUkDs1PropertyTrackLossless(iHandle, &trackLossless);
			aTrackLossless = (trackLossless != 0);
        }

        /// <summary>
        /// Query the value of the TrackBitDepth property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aTrackBitDepth">Will be set to the value of the property</param>
        public unsafe void PropertyTrackBitDepth(out uint aTrackBitDepth)
        {
			fixed (uint* trackBitDepth = &aTrackBitDepth)
			{
	            CpProxyLinnCoUkDs1PropertyTrackBitDepth(iHandle, trackBitDepth);
			}
        }

        /// <summary>
        /// Query the value of the TrackSampleRate property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aTrackSampleRate">Will be set to the value of the property</param>
        public unsafe void PropertyTrackSampleRate(out uint aTrackSampleRate)
        {
			fixed (uint* trackSampleRate = &aTrackSampleRate)
			{
	            CpProxyLinnCoUkDs1PropertyTrackSampleRate(iHandle, trackSampleRate);
			}
        }

        /// <summary>
        /// Query the value of the TrackCodecName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aTrackCodecName">Will be set to the value of the property</param>
        public unsafe void PropertyTrackCodecName(out string aTrackCodecName)
        {
			char* ptr;
            CpProxyLinnCoUkDs1PropertyTrackCodecName(iHandle, &ptr);
            aTrackCodecName = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the TrackId property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aTrackId">Will be set to the value of the property</param>
        public unsafe void PropertyTrackId(out uint aTrackId)
        {
			fixed (uint* trackId = &aTrackId)
			{
	            CpProxyLinnCoUkDs1PropertyTrackId(iHandle, trackId);
			}
        }

        /// <summary>
        /// Query the value of the TransportState property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aTransportState">Will be set to the value of the property</param>
        public unsafe void PropertyTransportState(out string aTransportState)
        {
			char* ptr;
            CpProxyLinnCoUkDs1PropertyTransportState(iHandle, &ptr);
            aTransportState = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
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
            lock (this)
            {
                if (iHandle == 0)
                {
                    return;
                }
                CpProxyLinnCoUkDs1Destroy(iHandle);
                iHandle = 0;
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

