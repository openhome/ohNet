using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkPreamp4 : ICpProxy, IDisposable
    {
        void SyncVolumeInc();
        void BeginVolumeInc(CpProxy.CallbackAsyncComplete aCallback);
        void EndVolumeInc(uint aAsyncHandle);
        void SyncVolumeDec();
        void BeginVolumeDec(CpProxy.CallbackAsyncComplete aCallback);
        void EndVolumeDec(uint aAsyncHandle);
        void SyncSetVolume(uint aaVolume);
        void BeginSetVolume(uint aaVolume, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetVolume(uint aAsyncHandle);
        void SyncVolume(out uint aaVolume);
        void BeginVolume(CpProxy.CallbackAsyncComplete aCallback);
        void EndVolume(uint aAsyncHandle, out uint aaVolume);
        void SyncSetMute(bool aaMute);
        void BeginSetMute(bool aaMute, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetMute(uint aAsyncHandle);
        void SyncMute(out bool aaMute);
        void BeginMute(CpProxy.CallbackAsyncComplete aCallback);
        void EndMute(uint aAsyncHandle, out bool aaMute);
        void SyncSetBalance(int aaBalance);
        void BeginSetBalance(int aaBalance, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetBalance(uint aAsyncHandle);
        void SyncBalance(out int aaBalance);
        void BeginBalance(CpProxy.CallbackAsyncComplete aCallback);
        void EndBalance(uint aAsyncHandle, out int aaBalance);
        void SyncSetVolumeLimit(uint aaVolumeLimit);
        void BeginSetVolumeLimit(uint aaVolumeLimit, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetVolumeLimit(uint aAsyncHandle);
        void SyncVolumeLimit(out uint aaVolumeLimit);
        void BeginVolumeLimit(CpProxy.CallbackAsyncComplete aCallback);
        void EndVolumeLimit(uint aAsyncHandle, out uint aaVolumeLimit);
        void SyncSetStartupVolume(uint aaStartupVolume);
        void BeginSetStartupVolume(uint aaStartupVolume, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStartupVolume(uint aAsyncHandle);
        void SyncStartupVolume(out uint aaStartupVolume);
        void BeginStartupVolume(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartupVolume(uint aAsyncHandle, out uint aaStartupVolume);
        void SyncSetStartupVolumeEnabled(bool aaStartupVolumeEnabled);
        void BeginSetStartupVolumeEnabled(bool aaStartupVolumeEnabled, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStartupVolumeEnabled(uint aAsyncHandle);
        void SyncStartupVolumeEnabled(out bool aaStartupVolumeEnabled);
        void BeginStartupVolumeEnabled(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartupVolumeEnabled(uint aAsyncHandle, out bool aaStartupVolumeEnabled);

        void SetPropertyVolumeChanged(CpProxy.CallbackPropertyChanged aVolumeChanged);
        void PropertyVolume(out uint aVolume);
        void SetPropertyMuteChanged(CpProxy.CallbackPropertyChanged aMuteChanged);
        void PropertyMute(out bool aMute);
        void SetPropertyBalanceChanged(CpProxy.CallbackPropertyChanged aBalanceChanged);
        void PropertyBalance(out int aBalance);
        void SetPropertyVolumeLimitChanged(CpProxy.CallbackPropertyChanged aVolumeLimitChanged);
        void PropertyVolumeLimit(out uint aVolumeLimit);
        void SetPropertyStartupVolumeChanged(CpProxy.CallbackPropertyChanged aStartupVolumeChanged);
        void PropertyStartupVolume(out uint aStartupVolume);
        void SetPropertyStartupVolumeEnabledChanged(CpProxy.CallbackPropertyChanged aStartupVolumeEnabledChanged);
        void PropertyStartupVolumeEnabled(out bool aStartupVolumeEnabled);
    }

    public class CpProxyLinnCoUkPreamp4 : CpProxy, IDisposable, ICpProxyLinnCoUkPreamp4
    {
        [DllImport("CpLinnCoUkPreamp4")]
        static extern uint CpProxyLinnCoUkPreamp4Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern void CpProxyLinnCoUkPreamp4Destroy(uint aHandle);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncVolumeInc(uint aHandle);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginVolumeInc(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndVolumeInc(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncVolumeDec(uint aHandle);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginVolumeDec(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndVolumeDec(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncSetVolume(uint aHandle, uint aaVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginSetVolume(uint aHandle, uint aaVolume, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndSetVolume(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncVolume(uint aHandle, uint* aaVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginVolume(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndVolume(uint aHandle, uint aAsync, uint* aaVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncSetMute(uint aHandle, uint aaMute);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginSetMute(uint aHandle, uint aaMute, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndSetMute(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncMute(uint aHandle, uint* aaMute);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginMute(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndMute(uint aHandle, uint aAsync, uint* aaMute);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncSetBalance(uint aHandle, int aaBalance);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginSetBalance(uint aHandle, int aaBalance, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndSetBalance(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncBalance(uint aHandle, int* aaBalance);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginBalance(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndBalance(uint aHandle, uint aAsync, int* aaBalance);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncSetVolumeLimit(uint aHandle, uint aaVolumeLimit);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginSetVolumeLimit(uint aHandle, uint aaVolumeLimit, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndSetVolumeLimit(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncVolumeLimit(uint aHandle, uint* aaVolumeLimit);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginVolumeLimit(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndVolumeLimit(uint aHandle, uint aAsync, uint* aaVolumeLimit);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncSetStartupVolume(uint aHandle, uint aaStartupVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginSetStartupVolume(uint aHandle, uint aaStartupVolume, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndSetStartupVolume(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncStartupVolume(uint aHandle, uint* aaStartupVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginStartupVolume(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndStartupVolume(uint aHandle, uint aAsync, uint* aaStartupVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncSetStartupVolumeEnabled(uint aHandle, uint aaStartupVolumeEnabled);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginSetStartupVolumeEnabled(uint aHandle, uint aaStartupVolumeEnabled, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndSetStartupVolumeEnabled(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncStartupVolumeEnabled(uint aHandle, uint* aaStartupVolumeEnabled);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginStartupVolumeEnabled(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndStartupVolumeEnabled(uint aHandle, uint aAsync, uint* aaStartupVolumeEnabled);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern void CpProxyLinnCoUkPreamp4SetPropertyVolumeChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern void CpProxyLinnCoUkPreamp4SetPropertyMuteChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern void CpProxyLinnCoUkPreamp4SetPropertyBalanceChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern void CpProxyLinnCoUkPreamp4SetPropertyVolumeLimitChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern void CpProxyLinnCoUkPreamp4SetPropertyStartupVolumeChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern void CpProxyLinnCoUkPreamp4SetPropertyStartupVolumeEnabledChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4PropertyVolume(uint aHandle, uint* aVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4PropertyMute(uint aHandle, uint* aMute);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4PropertyBalance(uint aHandle, int* aBalance);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4PropertyVolumeLimit(uint aHandle, uint* aVolumeLimit);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4PropertyStartupVolume(uint aHandle, uint* aStartupVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4PropertyStartupVolumeEnabled(uint aHandle, uint* aStartupVolumeEnabled);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iVolumeChanged;
        private CallbackPropertyChanged iMuteChanged;
        private CallbackPropertyChanged iBalanceChanged;
        private CallbackPropertyChanged iVolumeLimitChanged;
        private CallbackPropertyChanged iStartupVolumeChanged;
        private CallbackPropertyChanged iStartupVolumeEnabledChanged;
        private Callback iCallbackVolumeChanged;
        private Callback iCallbackMuteChanged;
        private Callback iCallbackBalanceChanged;
        private Callback iCallbackVolumeLimitChanged;
        private Callback iCallbackStartupVolumeChanged;
        private Callback iCallbackStartupVolumeEnabledChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkPreamp4(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkPreamp4Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public unsafe void SyncVolumeInc()
        {
			{
				CpProxyLinnCoUkPreamp4SyncVolumeInc(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndVolumeInc().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginVolumeInc(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginVolumeInc(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndVolumeInc(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndVolumeInc(iHandle, aAsyncHandle))
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
        public unsafe void SyncVolumeDec()
        {
			{
				CpProxyLinnCoUkPreamp4SyncVolumeDec(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndVolumeDec().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginVolumeDec(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginVolumeDec(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndVolumeDec(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndVolumeDec(iHandle, aAsyncHandle))
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
        /// <param name="aaVolume"></param>
        public unsafe void SyncSetVolume(uint aaVolume)
        {
			{
				CpProxyLinnCoUkPreamp4SyncSetVolume(iHandle, aaVolume);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetVolume().</remarks>
        /// <param name="aaVolume"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetVolume(uint aaVolume, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginSetVolume(iHandle, aaVolume, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetVolume(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndSetVolume(iHandle, aAsyncHandle))
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
        /// <param name="aaVolume"></param>
        public unsafe void SyncVolume(out uint aaVolume)
        {
			fixed (uint* aVolume = &aaVolume)
			{
				CpProxyLinnCoUkPreamp4SyncVolume(iHandle, aVolume);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndVolume().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginVolume(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginVolume(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaVolume"></param>
        public unsafe void EndVolume(uint aAsyncHandle, out uint aaVolume)
        {
			fixed (uint* aVolume = &aaVolume)
			{
				if (0 != CpProxyLinnCoUkPreamp4EndVolume(iHandle, aAsyncHandle, aVolume))
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
        /// <param name="aaMute"></param>
        public unsafe void SyncSetMute(bool aaMute)
        {
			uint aMute = (aaMute? 1u : 0u);
			{
				CpProxyLinnCoUkPreamp4SyncSetMute(iHandle, aMute);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetMute().</remarks>
        /// <param name="aaMute"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetMute(bool aaMute, CallbackAsyncComplete aCallback)
        {
			uint aMute = (aaMute? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginSetMute(iHandle, aMute, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetMute(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndSetMute(iHandle, aAsyncHandle))
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
        /// <param name="aaMute"></param>
        public unsafe void SyncMute(out bool aaMute)
        {
			uint aMute;
			{
				CpProxyLinnCoUkPreamp4SyncMute(iHandle, &aMute);
			}
			aaMute = (aMute != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndMute().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginMute(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginMute(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaMute"></param>
        public unsafe void EndMute(uint aAsyncHandle, out bool aaMute)
        {
			uint aMute;
			{
				if (0 != CpProxyLinnCoUkPreamp4EndMute(iHandle, aAsyncHandle, &aMute))
				{
					throw(new ProxyError());
				}
			}
			aaMute = (aMute != 0);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaBalance"></param>
        public unsafe void SyncSetBalance(int aaBalance)
        {
			{
				CpProxyLinnCoUkPreamp4SyncSetBalance(iHandle, aaBalance);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetBalance().</remarks>
        /// <param name="aaBalance"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetBalance(int aaBalance, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginSetBalance(iHandle, aaBalance, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetBalance(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndSetBalance(iHandle, aAsyncHandle))
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
        /// <param name="aaBalance"></param>
        public unsafe void SyncBalance(out int aaBalance)
        {
			fixed (int* aBalance = &aaBalance)
			{
				CpProxyLinnCoUkPreamp4SyncBalance(iHandle, aBalance);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndBalance().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginBalance(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginBalance(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaBalance"></param>
        public unsafe void EndBalance(uint aAsyncHandle, out int aaBalance)
        {
			fixed (int* aBalance = &aaBalance)
			{
				if (0 != CpProxyLinnCoUkPreamp4EndBalance(iHandle, aAsyncHandle, aBalance))
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
        /// <param name="aaVolumeLimit"></param>
        public unsafe void SyncSetVolumeLimit(uint aaVolumeLimit)
        {
			{
				CpProxyLinnCoUkPreamp4SyncSetVolumeLimit(iHandle, aaVolumeLimit);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetVolumeLimit().</remarks>
        /// <param name="aaVolumeLimit"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetVolumeLimit(uint aaVolumeLimit, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginSetVolumeLimit(iHandle, aaVolumeLimit, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetVolumeLimit(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndSetVolumeLimit(iHandle, aAsyncHandle))
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
        /// <param name="aaVolumeLimit"></param>
        public unsafe void SyncVolumeLimit(out uint aaVolumeLimit)
        {
			fixed (uint* aVolumeLimit = &aaVolumeLimit)
			{
				CpProxyLinnCoUkPreamp4SyncVolumeLimit(iHandle, aVolumeLimit);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndVolumeLimit().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginVolumeLimit(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginVolumeLimit(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaVolumeLimit"></param>
        public unsafe void EndVolumeLimit(uint aAsyncHandle, out uint aaVolumeLimit)
        {
			fixed (uint* aVolumeLimit = &aaVolumeLimit)
			{
				if (0 != CpProxyLinnCoUkPreamp4EndVolumeLimit(iHandle, aAsyncHandle, aVolumeLimit))
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
        /// <param name="aaStartupVolume"></param>
        public unsafe void SyncSetStartupVolume(uint aaStartupVolume)
        {
			{
				CpProxyLinnCoUkPreamp4SyncSetStartupVolume(iHandle, aaStartupVolume);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStartupVolume().</remarks>
        /// <param name="aaStartupVolume"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetStartupVolume(uint aaStartupVolume, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginSetStartupVolume(iHandle, aaStartupVolume, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetStartupVolume(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndSetStartupVolume(iHandle, aAsyncHandle))
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
        /// <param name="aaStartupVolume"></param>
        public unsafe void SyncStartupVolume(out uint aaStartupVolume)
        {
			fixed (uint* aStartupVolume = &aaStartupVolume)
			{
				CpProxyLinnCoUkPreamp4SyncStartupVolume(iHandle, aStartupVolume);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartupVolume().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStartupVolume(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginStartupVolume(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaStartupVolume"></param>
        public unsafe void EndStartupVolume(uint aAsyncHandle, out uint aaStartupVolume)
        {
			fixed (uint* aStartupVolume = &aaStartupVolume)
			{
				if (0 != CpProxyLinnCoUkPreamp4EndStartupVolume(iHandle, aAsyncHandle, aStartupVolume))
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
        /// <param name="aaStartupVolumeEnabled"></param>
        public unsafe void SyncSetStartupVolumeEnabled(bool aaStartupVolumeEnabled)
        {
			uint aStartupVolumeEnabled = (aaStartupVolumeEnabled? 1u : 0u);
			{
				CpProxyLinnCoUkPreamp4SyncSetStartupVolumeEnabled(iHandle, aStartupVolumeEnabled);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStartupVolumeEnabled().</remarks>
        /// <param name="aaStartupVolumeEnabled"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetStartupVolumeEnabled(bool aaStartupVolumeEnabled, CallbackAsyncComplete aCallback)
        {
			uint aStartupVolumeEnabled = (aaStartupVolumeEnabled? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginSetStartupVolumeEnabled(iHandle, aStartupVolumeEnabled, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetStartupVolumeEnabled(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndSetStartupVolumeEnabled(iHandle, aAsyncHandle))
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
        /// <param name="aaStartupVolumeEnabled"></param>
        public unsafe void SyncStartupVolumeEnabled(out bool aaStartupVolumeEnabled)
        {
			uint aStartupVolumeEnabled;
			{
				CpProxyLinnCoUkPreamp4SyncStartupVolumeEnabled(iHandle, &aStartupVolumeEnabled);
			}
			aaStartupVolumeEnabled = (aStartupVolumeEnabled != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartupVolumeEnabled().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStartupVolumeEnabled(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginStartupVolumeEnabled(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaStartupVolumeEnabled"></param>
        public unsafe void EndStartupVolumeEnabled(uint aAsyncHandle, out bool aaStartupVolumeEnabled)
        {
			uint aStartupVolumeEnabled;
			{
				if (0 != CpProxyLinnCoUkPreamp4EndStartupVolumeEnabled(iHandle, aAsyncHandle, &aStartupVolumeEnabled))
				{
					throw(new ProxyError());
				}
			}
			aaStartupVolumeEnabled = (aStartupVolumeEnabled != 0);
        }

        /// <summary>
        /// Set a delegate to be run when the Volume state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPreamp4 instance will not overlap.</remarks>
        /// <param name="aVolumeChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVolumeChanged(CallbackPropertyChanged aVolumeChanged)
        {
            iVolumeChanged = aVolumeChanged;
            iCallbackVolumeChanged = new Callback(PropertyVolumeChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkPreamp4SetPropertyVolumeChanged(iHandle, iCallbackVolumeChanged, ptr);
        }

        private void PropertyVolumeChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkPreamp4 self = (CpProxyLinnCoUkPreamp4)gch.Target;
            self.iVolumeChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the Mute state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPreamp4 instance will not overlap.</remarks>
        /// <param name="aMuteChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyMuteChanged(CallbackPropertyChanged aMuteChanged)
        {
            iMuteChanged = aMuteChanged;
            iCallbackMuteChanged = new Callback(PropertyMuteChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkPreamp4SetPropertyMuteChanged(iHandle, iCallbackMuteChanged, ptr);
        }

        private void PropertyMuteChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkPreamp4 self = (CpProxyLinnCoUkPreamp4)gch.Target;
            self.iMuteChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the Balance state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPreamp4 instance will not overlap.</remarks>
        /// <param name="aBalanceChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyBalanceChanged(CallbackPropertyChanged aBalanceChanged)
        {
            iBalanceChanged = aBalanceChanged;
            iCallbackBalanceChanged = new Callback(PropertyBalanceChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkPreamp4SetPropertyBalanceChanged(iHandle, iCallbackBalanceChanged, ptr);
        }

        private void PropertyBalanceChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkPreamp4 self = (CpProxyLinnCoUkPreamp4)gch.Target;
            self.iBalanceChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the VolumeLimit state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPreamp4 instance will not overlap.</remarks>
        /// <param name="aVolumeLimitChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVolumeLimitChanged(CallbackPropertyChanged aVolumeLimitChanged)
        {
            iVolumeLimitChanged = aVolumeLimitChanged;
            iCallbackVolumeLimitChanged = new Callback(PropertyVolumeLimitChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkPreamp4SetPropertyVolumeLimitChanged(iHandle, iCallbackVolumeLimitChanged, ptr);
        }

        private void PropertyVolumeLimitChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkPreamp4 self = (CpProxyLinnCoUkPreamp4)gch.Target;
            self.iVolumeLimitChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the StartupVolume state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPreamp4 instance will not overlap.</remarks>
        /// <param name="aStartupVolumeChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyStartupVolumeChanged(CallbackPropertyChanged aStartupVolumeChanged)
        {
            iStartupVolumeChanged = aStartupVolumeChanged;
            iCallbackStartupVolumeChanged = new Callback(PropertyStartupVolumeChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkPreamp4SetPropertyStartupVolumeChanged(iHandle, iCallbackStartupVolumeChanged, ptr);
        }

        private void PropertyStartupVolumeChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkPreamp4 self = (CpProxyLinnCoUkPreamp4)gch.Target;
            self.iStartupVolumeChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the StartupVolumeEnabled state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPreamp4 instance will not overlap.</remarks>
        /// <param name="aStartupVolumeEnabledChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyStartupVolumeEnabledChanged(CallbackPropertyChanged aStartupVolumeEnabledChanged)
        {
            iStartupVolumeEnabledChanged = aStartupVolumeEnabledChanged;
            iCallbackStartupVolumeEnabledChanged = new Callback(PropertyStartupVolumeEnabledChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkPreamp4SetPropertyStartupVolumeEnabledChanged(iHandle, iCallbackStartupVolumeEnabledChanged, ptr);
        }

        private void PropertyStartupVolumeEnabledChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkPreamp4 self = (CpProxyLinnCoUkPreamp4)gch.Target;
            self.iStartupVolumeEnabledChanged();
        }

        /// <summary>
        /// Query the value of the Volume property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aVolume">Will be set to the value of the property</param>
        public unsafe void PropertyVolume(out uint aVolume)
        {
			fixed (uint* volume = &aVolume)
			{
	            CpProxyLinnCoUkPreamp4PropertyVolume(iHandle, volume);
			}
        }

        /// <summary>
        /// Query the value of the Mute property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aMute">Will be set to the value of the property</param>
        public unsafe void PropertyMute(out bool aMute)
        {
			uint mute;
	        CpProxyLinnCoUkPreamp4PropertyMute(iHandle, &mute);
			aMute = (mute != 0);
        }

        /// <summary>
        /// Query the value of the Balance property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aBalance">Will be set to the value of the property</param>
        public unsafe void PropertyBalance(out int aBalance)
        {
			fixed (int* balance = &aBalance)
			{
	            CpProxyLinnCoUkPreamp4PropertyBalance(iHandle, balance);
			}
        }

        /// <summary>
        /// Query the value of the VolumeLimit property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aVolumeLimit">Will be set to the value of the property</param>
        public unsafe void PropertyVolumeLimit(out uint aVolumeLimit)
        {
			fixed (uint* volumeLimit = &aVolumeLimit)
			{
	            CpProxyLinnCoUkPreamp4PropertyVolumeLimit(iHandle, volumeLimit);
			}
        }

        /// <summary>
        /// Query the value of the StartupVolume property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aStartupVolume">Will be set to the value of the property</param>
        public unsafe void PropertyStartupVolume(out uint aStartupVolume)
        {
			fixed (uint* startupVolume = &aStartupVolume)
			{
	            CpProxyLinnCoUkPreamp4PropertyStartupVolume(iHandle, startupVolume);
			}
        }

        /// <summary>
        /// Query the value of the StartupVolumeEnabled property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aStartupVolumeEnabled">Will be set to the value of the property</param>
        public unsafe void PropertyStartupVolumeEnabled(out bool aStartupVolumeEnabled)
        {
			uint startupVolumeEnabled;
	        CpProxyLinnCoUkPreamp4PropertyStartupVolumeEnabled(iHandle, &startupVolumeEnabled);
			aStartupVolumeEnabled = (startupVolumeEnabled != 0);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkPreamp4()
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
                CpProxyLinnCoUkPreamp4Destroy(iHandle);
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

