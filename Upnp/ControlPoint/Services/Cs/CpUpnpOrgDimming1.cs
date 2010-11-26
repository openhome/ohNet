using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyUpnpOrgDimming1 : ICpProxy, IDisposable
    {
        void SyncSetLoadLevelTarget(uint anewLoadlevelTarget);
        void BeginSetLoadLevelTarget(uint anewLoadlevelTarget, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetLoadLevelTarget(uint aAsyncHandle);
        void SyncGetLoadLevelTarget(out uint aGetLoadlevelTarget);
        void BeginGetLoadLevelTarget(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetLoadLevelTarget(uint aAsyncHandle, out uint aGetLoadlevelTarget);
        void SyncGetLoadLevelStatus(out uint aretLoadlevelStatus);
        void BeginGetLoadLevelStatus(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetLoadLevelStatus(uint aAsyncHandle, out uint aretLoadlevelStatus);
        void SyncSetOnEffectLevel(uint anewOnEffectLevel);
        void BeginSetOnEffectLevel(uint anewOnEffectLevel, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetOnEffectLevel(uint aAsyncHandle);
        void SyncSetOnEffect(string anewOnEffect);
        void BeginSetOnEffect(string anewOnEffect, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetOnEffect(uint aAsyncHandle);
        void SyncGetOnEffectParameters(out string aretOnEffect, out uint aretOnEffectLevel);
        void BeginGetOnEffectParameters(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetOnEffectParameters(uint aAsyncHandle, out string aretOnEffect, out uint aretOnEffectLevel);
        void SyncStepUp();
        void BeginStepUp(CpProxy.CallbackAsyncComplete aCallback);
        void EndStepUp(uint aAsyncHandle);
        void SyncStepDown();
        void BeginStepDown(CpProxy.CallbackAsyncComplete aCallback);
        void EndStepDown(uint aAsyncHandle);
        void SyncStartRampUp();
        void BeginStartRampUp(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartRampUp(uint aAsyncHandle);
        void SyncStartRampDown();
        void BeginStartRampDown(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartRampDown(uint aAsyncHandle);
        void SyncStopRamp();
        void BeginStopRamp(CpProxy.CallbackAsyncComplete aCallback);
        void EndStopRamp(uint aAsyncHandle);
        void SyncStartRampToLevel(uint anewLoadLevelTarget, uint anewRampTime);
        void BeginStartRampToLevel(uint anewLoadLevelTarget, uint anewRampTime, CpProxy.CallbackAsyncComplete aCallback);
        void EndStartRampToLevel(uint aAsyncHandle);
        void SyncSetStepDelta(uint anewStepDelta);
        void BeginSetStepDelta(uint anewStepDelta, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStepDelta(uint aAsyncHandle);
        void SyncGetStepDelta(out uint aretStepDelta);
        void BeginGetStepDelta(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetStepDelta(uint aAsyncHandle, out uint aretStepDelta);
        void SyncSetRampRate(uint anewRampRate);
        void BeginSetRampRate(uint anewRampRate, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetRampRate(uint aAsyncHandle);
        void SyncGetRampRate(out uint aretRampRate);
        void BeginGetRampRate(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRampRate(uint aAsyncHandle, out uint aretRampRate);
        void SyncPauseRamp();
        void BeginPauseRamp(CpProxy.CallbackAsyncComplete aCallback);
        void EndPauseRamp(uint aAsyncHandle);
        void SyncResumeRamp();
        void BeginResumeRamp(CpProxy.CallbackAsyncComplete aCallback);
        void EndResumeRamp(uint aAsyncHandle);
        void SyncGetIsRamping(out bool aretIsRamping);
        void BeginGetIsRamping(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetIsRamping(uint aAsyncHandle, out bool aretIsRamping);
        void SyncGetRampPaused(out bool aretRampPaused);
        void BeginGetRampPaused(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRampPaused(uint aAsyncHandle, out bool aretRampPaused);
        void SyncGetRampTime(out uint aretRampTime);
        void BeginGetRampTime(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRampTime(uint aAsyncHandle, out uint aretRampTime);

        void SetPropertyLoadLevelStatusChanged(CpProxy.CallbackPropertyChanged aLoadLevelStatusChanged);
        void PropertyLoadLevelStatus(out uint aLoadLevelStatus);
        void SetPropertyStepDeltaChanged(CpProxy.CallbackPropertyChanged aStepDeltaChanged);
        void PropertyStepDelta(out uint aStepDelta);
        void SetPropertyRampRateChanged(CpProxy.CallbackPropertyChanged aRampRateChanged);
        void PropertyRampRate(out uint aRampRate);
        void SetPropertyIsRampingChanged(CpProxy.CallbackPropertyChanged aIsRampingChanged);
        void PropertyIsRamping(out bool aIsRamping);
        void SetPropertyRampPausedChanged(CpProxy.CallbackPropertyChanged aRampPausedChanged);
        void PropertyRampPaused(out bool aRampPaused);
    }

    public class CpProxyUpnpOrgDimming1 : CpProxy, IDisposable, ICpProxyUpnpOrgDimming1
    {
        [DllImport("CpUpnpOrgDimming1")]
        static extern uint CpProxyUpnpOrgDimming1Create(uint aDeviceHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern void CpProxyUpnpOrgDimming1Destroy(uint aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncSetLoadLevelTarget(uint aHandle, uint anewLoadlevelTarget);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginSetLoadLevelTarget(uint aHandle, uint anewLoadlevelTarget, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndSetLoadLevelTarget(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetLoadLevelTarget(uint aHandle, uint* aGetLoadlevelTarget);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetLoadLevelTarget(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetLoadLevelTarget(uint aHandle, uint aAsync, uint* aGetLoadlevelTarget);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetLoadLevelStatus(uint aHandle, uint* aretLoadlevelStatus);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetLoadLevelStatus(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetLoadLevelStatus(uint aHandle, uint aAsync, uint* aretLoadlevelStatus);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncSetOnEffectLevel(uint aHandle, uint anewOnEffectLevel);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginSetOnEffectLevel(uint aHandle, uint anewOnEffectLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndSetOnEffectLevel(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncSetOnEffect(uint aHandle, char* anewOnEffect);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginSetOnEffect(uint aHandle, char* anewOnEffect, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndSetOnEffect(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetOnEffectParameters(uint aHandle, char** aretOnEffect, uint* aretOnEffectLevel);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetOnEffectParameters(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetOnEffectParameters(uint aHandle, uint aAsync, char** aretOnEffect, uint* aretOnEffectLevel);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncStepUp(uint aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginStepUp(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndStepUp(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncStepDown(uint aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginStepDown(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndStepDown(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncStartRampUp(uint aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginStartRampUp(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndStartRampUp(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncStartRampDown(uint aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginStartRampDown(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndStartRampDown(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncStopRamp(uint aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginStopRamp(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndStopRamp(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncStartRampToLevel(uint aHandle, uint anewLoadLevelTarget, uint anewRampTime);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginStartRampToLevel(uint aHandle, uint anewLoadLevelTarget, uint anewRampTime, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndStartRampToLevel(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncSetStepDelta(uint aHandle, uint anewStepDelta);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginSetStepDelta(uint aHandle, uint anewStepDelta, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndSetStepDelta(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetStepDelta(uint aHandle, uint* aretStepDelta);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetStepDelta(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetStepDelta(uint aHandle, uint aAsync, uint* aretStepDelta);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncSetRampRate(uint aHandle, uint anewRampRate);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginSetRampRate(uint aHandle, uint anewRampRate, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndSetRampRate(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetRampRate(uint aHandle, uint* aretRampRate);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetRampRate(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetRampRate(uint aHandle, uint aAsync, uint* aretRampRate);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncPauseRamp(uint aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginPauseRamp(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndPauseRamp(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncResumeRamp(uint aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginResumeRamp(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndResumeRamp(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetIsRamping(uint aHandle, uint* aretIsRamping);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetIsRamping(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetIsRamping(uint aHandle, uint aAsync, uint* aretIsRamping);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetRampPaused(uint aHandle, uint* aretRampPaused);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetRampPaused(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetRampPaused(uint aHandle, uint aAsync, uint* aretRampPaused);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetRampTime(uint aHandle, uint* aretRampTime);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetRampTime(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetRampTime(uint aHandle, uint aAsync, uint* aretRampTime);
        [DllImport("CpUpnpOrgDimming1")]
        static extern void CpProxyUpnpOrgDimming1SetPropertyLoadLevelStatusChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern void CpProxyUpnpOrgDimming1SetPropertyStepDeltaChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern void CpProxyUpnpOrgDimming1SetPropertyRampRateChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern void CpProxyUpnpOrgDimming1SetPropertyIsRampingChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern void CpProxyUpnpOrgDimming1SetPropertyRampPausedChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1PropertyLoadLevelStatus(uint aHandle, uint* aLoadLevelStatus);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1PropertyStepDelta(uint aHandle, uint* aStepDelta);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1PropertyRampRate(uint aHandle, uint* aRampRate);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1PropertyIsRamping(uint aHandle, uint* aIsRamping);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1PropertyRampPaused(uint aHandle, uint* aRampPaused);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iLoadLevelStatusChanged;
        private CallbackPropertyChanged iStepDeltaChanged;
        private CallbackPropertyChanged iRampRateChanged;
        private CallbackPropertyChanged iIsRampingChanged;
        private CallbackPropertyChanged iRampPausedChanged;
        private Callback iCallbackLoadLevelStatusChanged;
        private Callback iCallbackStepDeltaChanged;
        private Callback iCallbackRampRateChanged;
        private Callback iCallbackIsRampingChanged;
        private Callback iCallbackRampPausedChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyUpnpOrgDimming1(CpDevice aDevice)
        {
            iHandle = CpProxyUpnpOrgDimming1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="anewLoadlevelTarget"></param>
        public unsafe void SyncSetLoadLevelTarget(uint anewLoadlevelTarget)
        {
			{
				CpProxyUpnpOrgDimming1SyncSetLoadLevelTarget(iHandle, anewLoadlevelTarget);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetLoadLevelTarget().</remarks>
        /// <param name="anewLoadlevelTarget"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetLoadLevelTarget(uint anewLoadlevelTarget, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginSetLoadLevelTarget(iHandle, anewLoadlevelTarget, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetLoadLevelTarget(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndSetLoadLevelTarget(iHandle, aAsyncHandle))
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
        /// <param name="aGetLoadlevelTarget"></param>
        public unsafe void SyncGetLoadLevelTarget(out uint aGetLoadlevelTarget)
        {
			fixed (uint* getLoadlevelTarget = &aGetLoadlevelTarget)
			{
				CpProxyUpnpOrgDimming1SyncGetLoadLevelTarget(iHandle, getLoadlevelTarget);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetLoadLevelTarget().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetLoadLevelTarget(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetLoadLevelTarget(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aGetLoadlevelTarget"></param>
        public unsafe void EndGetLoadLevelTarget(uint aAsyncHandle, out uint aGetLoadlevelTarget)
        {
			fixed (uint* getLoadlevelTarget = &aGetLoadlevelTarget)
			{
				if (0 != CpProxyUpnpOrgDimming1EndGetLoadLevelTarget(iHandle, aAsyncHandle, getLoadlevelTarget))
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
        /// <param name="aretLoadlevelStatus"></param>
        public unsafe void SyncGetLoadLevelStatus(out uint aretLoadlevelStatus)
        {
			fixed (uint* retLoadlevelStatus = &aretLoadlevelStatus)
			{
				CpProxyUpnpOrgDimming1SyncGetLoadLevelStatus(iHandle, retLoadlevelStatus);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetLoadLevelStatus().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetLoadLevelStatus(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetLoadLevelStatus(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aretLoadlevelStatus"></param>
        public unsafe void EndGetLoadLevelStatus(uint aAsyncHandle, out uint aretLoadlevelStatus)
        {
			fixed (uint* retLoadlevelStatus = &aretLoadlevelStatus)
			{
				if (0 != CpProxyUpnpOrgDimming1EndGetLoadLevelStatus(iHandle, aAsyncHandle, retLoadlevelStatus))
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
        /// <param name="anewOnEffectLevel"></param>
        public unsafe void SyncSetOnEffectLevel(uint anewOnEffectLevel)
        {
			{
				CpProxyUpnpOrgDimming1SyncSetOnEffectLevel(iHandle, anewOnEffectLevel);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetOnEffectLevel().</remarks>
        /// <param name="anewOnEffectLevel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetOnEffectLevel(uint anewOnEffectLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginSetOnEffectLevel(iHandle, anewOnEffectLevel, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetOnEffectLevel(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndSetOnEffectLevel(iHandle, aAsyncHandle))
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
        /// <param name="anewOnEffect"></param>
        public unsafe void SyncSetOnEffect(string anewOnEffect)
        {
			char* newOnEffect = (char*)Marshal.StringToHGlobalAnsi(anewOnEffect);
			{
				CpProxyUpnpOrgDimming1SyncSetOnEffect(iHandle, newOnEffect);
			}
			Marshal.FreeHGlobal((IntPtr)newOnEffect);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetOnEffect().</remarks>
        /// <param name="anewOnEffect"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetOnEffect(string anewOnEffect, CallbackAsyncComplete aCallback)
        {
			char* newOnEffect = (char*)Marshal.StringToHGlobalAnsi(anewOnEffect);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginSetOnEffect(iHandle, newOnEffect, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)newOnEffect);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetOnEffect(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndSetOnEffect(iHandle, aAsyncHandle))
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
        /// <param name="aretOnEffect"></param>
        /// <param name="aretOnEffectLevel"></param>
        public unsafe void SyncGetOnEffectParameters(out string aretOnEffect, out uint aretOnEffectLevel)
        {
			char* retOnEffect;
			fixed (uint* retOnEffectLevel = &aretOnEffectLevel)
			{
				CpProxyUpnpOrgDimming1SyncGetOnEffectParameters(iHandle, &retOnEffect, retOnEffectLevel);
			}
            aretOnEffect = Marshal.PtrToStringAnsi((IntPtr)retOnEffect);
            ZappFree(retOnEffect);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetOnEffectParameters().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetOnEffectParameters(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetOnEffectParameters(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aretOnEffect"></param>
        /// <param name="aretOnEffectLevel"></param>
        public unsafe void EndGetOnEffectParameters(uint aAsyncHandle, out string aretOnEffect, out uint aretOnEffectLevel)
        {
			char* retOnEffect;
			fixed (uint* retOnEffectLevel = &aretOnEffectLevel)
			{
				if (0 != CpProxyUpnpOrgDimming1EndGetOnEffectParameters(iHandle, aAsyncHandle, &retOnEffect, retOnEffectLevel))
				{
					throw(new ProxyError());
				}
			}
            aretOnEffect = Marshal.PtrToStringAnsi((IntPtr)retOnEffect);
            ZappFree(retOnEffect);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public unsafe void SyncStepUp()
        {
			{
				CpProxyUpnpOrgDimming1SyncStepUp(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStepUp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStepUp(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginStepUp(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndStepUp(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndStepUp(iHandle, aAsyncHandle))
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
        public unsafe void SyncStepDown()
        {
			{
				CpProxyUpnpOrgDimming1SyncStepDown(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStepDown().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStepDown(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginStepDown(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndStepDown(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndStepDown(iHandle, aAsyncHandle))
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
        public unsafe void SyncStartRampUp()
        {
			{
				CpProxyUpnpOrgDimming1SyncStartRampUp(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartRampUp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStartRampUp(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginStartRampUp(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndStartRampUp(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndStartRampUp(iHandle, aAsyncHandle))
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
        public unsafe void SyncStartRampDown()
        {
			{
				CpProxyUpnpOrgDimming1SyncStartRampDown(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartRampDown().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStartRampDown(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginStartRampDown(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndStartRampDown(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndStartRampDown(iHandle, aAsyncHandle))
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
        public unsafe void SyncStopRamp()
        {
			{
				CpProxyUpnpOrgDimming1SyncStopRamp(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStopRamp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStopRamp(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginStopRamp(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndStopRamp(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndStopRamp(iHandle, aAsyncHandle))
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
        /// <param name="anewLoadLevelTarget"></param>
        /// <param name="anewRampTime"></param>
        public unsafe void SyncStartRampToLevel(uint anewLoadLevelTarget, uint anewRampTime)
        {
			{
				CpProxyUpnpOrgDimming1SyncStartRampToLevel(iHandle, anewLoadLevelTarget, anewRampTime);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartRampToLevel().</remarks>
        /// <param name="anewLoadLevelTarget"></param>
        /// <param name="anewRampTime"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStartRampToLevel(uint anewLoadLevelTarget, uint anewRampTime, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginStartRampToLevel(iHandle, anewLoadLevelTarget, anewRampTime, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndStartRampToLevel(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndStartRampToLevel(iHandle, aAsyncHandle))
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
        /// <param name="anewStepDelta"></param>
        public unsafe void SyncSetStepDelta(uint anewStepDelta)
        {
			{
				CpProxyUpnpOrgDimming1SyncSetStepDelta(iHandle, anewStepDelta);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStepDelta().</remarks>
        /// <param name="anewStepDelta"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetStepDelta(uint anewStepDelta, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginSetStepDelta(iHandle, anewStepDelta, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetStepDelta(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndSetStepDelta(iHandle, aAsyncHandle))
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
        /// <param name="aretStepDelta"></param>
        public unsafe void SyncGetStepDelta(out uint aretStepDelta)
        {
			fixed (uint* retStepDelta = &aretStepDelta)
			{
				CpProxyUpnpOrgDimming1SyncGetStepDelta(iHandle, retStepDelta);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetStepDelta().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetStepDelta(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetStepDelta(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aretStepDelta"></param>
        public unsafe void EndGetStepDelta(uint aAsyncHandle, out uint aretStepDelta)
        {
			fixed (uint* retStepDelta = &aretStepDelta)
			{
				if (0 != CpProxyUpnpOrgDimming1EndGetStepDelta(iHandle, aAsyncHandle, retStepDelta))
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
        /// <param name="anewRampRate"></param>
        public unsafe void SyncSetRampRate(uint anewRampRate)
        {
			{
				CpProxyUpnpOrgDimming1SyncSetRampRate(iHandle, anewRampRate);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetRampRate().</remarks>
        /// <param name="anewRampRate"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetRampRate(uint anewRampRate, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginSetRampRate(iHandle, anewRampRate, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetRampRate(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndSetRampRate(iHandle, aAsyncHandle))
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
        /// <param name="aretRampRate"></param>
        public unsafe void SyncGetRampRate(out uint aretRampRate)
        {
			fixed (uint* retRampRate = &aretRampRate)
			{
				CpProxyUpnpOrgDimming1SyncGetRampRate(iHandle, retRampRate);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRampRate().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetRampRate(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetRampRate(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aretRampRate"></param>
        public unsafe void EndGetRampRate(uint aAsyncHandle, out uint aretRampRate)
        {
			fixed (uint* retRampRate = &aretRampRate)
			{
				if (0 != CpProxyUpnpOrgDimming1EndGetRampRate(iHandle, aAsyncHandle, retRampRate))
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
        public unsafe void SyncPauseRamp()
        {
			{
				CpProxyUpnpOrgDimming1SyncPauseRamp(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPauseRamp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginPauseRamp(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginPauseRamp(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndPauseRamp(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndPauseRamp(iHandle, aAsyncHandle))
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
        public unsafe void SyncResumeRamp()
        {
			{
				CpProxyUpnpOrgDimming1SyncResumeRamp(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndResumeRamp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginResumeRamp(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginResumeRamp(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndResumeRamp(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndResumeRamp(iHandle, aAsyncHandle))
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
        /// <param name="aretIsRamping"></param>
        public unsafe void SyncGetIsRamping(out bool aretIsRamping)
        {
			uint retIsRamping;
			{
				CpProxyUpnpOrgDimming1SyncGetIsRamping(iHandle, &retIsRamping);
			}
			aretIsRamping = (retIsRamping != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetIsRamping().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetIsRamping(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetIsRamping(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aretIsRamping"></param>
        public unsafe void EndGetIsRamping(uint aAsyncHandle, out bool aretIsRamping)
        {
			uint retIsRamping;
			{
				if (0 != CpProxyUpnpOrgDimming1EndGetIsRamping(iHandle, aAsyncHandle, &retIsRamping))
				{
					throw(new ProxyError());
				}
			}
			aretIsRamping = (retIsRamping != 0);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aretRampPaused"></param>
        public unsafe void SyncGetRampPaused(out bool aretRampPaused)
        {
			uint retRampPaused;
			{
				CpProxyUpnpOrgDimming1SyncGetRampPaused(iHandle, &retRampPaused);
			}
			aretRampPaused = (retRampPaused != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRampPaused().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetRampPaused(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetRampPaused(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aretRampPaused"></param>
        public unsafe void EndGetRampPaused(uint aAsyncHandle, out bool aretRampPaused)
        {
			uint retRampPaused;
			{
				if (0 != CpProxyUpnpOrgDimming1EndGetRampPaused(iHandle, aAsyncHandle, &retRampPaused))
				{
					throw(new ProxyError());
				}
			}
			aretRampPaused = (retRampPaused != 0);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aretRampTime"></param>
        public unsafe void SyncGetRampTime(out uint aretRampTime)
        {
			fixed (uint* retRampTime = &aretRampTime)
			{
				CpProxyUpnpOrgDimming1SyncGetRampTime(iHandle, retRampTime);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRampTime().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetRampTime(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetRampTime(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aretRampTime"></param>
        public unsafe void EndGetRampTime(uint aAsyncHandle, out uint aretRampTime)
        {
			fixed (uint* retRampTime = &aretRampTime)
			{
				if (0 != CpProxyUpnpOrgDimming1EndGetRampTime(iHandle, aAsyncHandle, retRampTime))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Set a delegate to be run when the LoadLevelStatus state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aLoadLevelStatusChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyLoadLevelStatusChanged(CallbackPropertyChanged aLoadLevelStatusChanged)
        {
            iLoadLevelStatusChanged = aLoadLevelStatusChanged;
            iCallbackLoadLevelStatusChanged = new Callback(PropertyLoadLevelStatusChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgDimming1SetPropertyLoadLevelStatusChanged(iHandle, iCallbackLoadLevelStatusChanged, ptr);
        }

        private void PropertyLoadLevelStatusChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgDimming1 self = (CpProxyUpnpOrgDimming1)gch.Target;
            self.iLoadLevelStatusChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the StepDelta state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aStepDeltaChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyStepDeltaChanged(CallbackPropertyChanged aStepDeltaChanged)
        {
            iStepDeltaChanged = aStepDeltaChanged;
            iCallbackStepDeltaChanged = new Callback(PropertyStepDeltaChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgDimming1SetPropertyStepDeltaChanged(iHandle, iCallbackStepDeltaChanged, ptr);
        }

        private void PropertyStepDeltaChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgDimming1 self = (CpProxyUpnpOrgDimming1)gch.Target;
            self.iStepDeltaChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the RampRate state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aRampRateChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyRampRateChanged(CallbackPropertyChanged aRampRateChanged)
        {
            iRampRateChanged = aRampRateChanged;
            iCallbackRampRateChanged = new Callback(PropertyRampRateChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgDimming1SetPropertyRampRateChanged(iHandle, iCallbackRampRateChanged, ptr);
        }

        private void PropertyRampRateChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgDimming1 self = (CpProxyUpnpOrgDimming1)gch.Target;
            self.iRampRateChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the IsRamping state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aIsRampingChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyIsRampingChanged(CallbackPropertyChanged aIsRampingChanged)
        {
            iIsRampingChanged = aIsRampingChanged;
            iCallbackIsRampingChanged = new Callback(PropertyIsRampingChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgDimming1SetPropertyIsRampingChanged(iHandle, iCallbackIsRampingChanged, ptr);
        }

        private void PropertyIsRampingChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgDimming1 self = (CpProxyUpnpOrgDimming1)gch.Target;
            self.iIsRampingChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the RampPaused state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aRampPausedChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyRampPausedChanged(CallbackPropertyChanged aRampPausedChanged)
        {
            iRampPausedChanged = aRampPausedChanged;
            iCallbackRampPausedChanged = new Callback(PropertyRampPausedChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgDimming1SetPropertyRampPausedChanged(iHandle, iCallbackRampPausedChanged, ptr);
        }

        private void PropertyRampPausedChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgDimming1 self = (CpProxyUpnpOrgDimming1)gch.Target;
            self.iRampPausedChanged();
        }

        /// <summary>
        /// Query the value of the LoadLevelStatus property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aLoadLevelStatus">Will be set to the value of the property</param>
        public unsafe void PropertyLoadLevelStatus(out uint aLoadLevelStatus)
        {
			fixed (uint* loadLevelStatus = &aLoadLevelStatus)
			{
	            CpProxyUpnpOrgDimming1PropertyLoadLevelStatus(iHandle, loadLevelStatus);
			}
        }

        /// <summary>
        /// Query the value of the StepDelta property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aStepDelta">Will be set to the value of the property</param>
        public unsafe void PropertyStepDelta(out uint aStepDelta)
        {
			fixed (uint* stepDelta = &aStepDelta)
			{
	            CpProxyUpnpOrgDimming1PropertyStepDelta(iHandle, stepDelta);
			}
        }

        /// <summary>
        /// Query the value of the RampRate property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aRampRate">Will be set to the value of the property</param>
        public unsafe void PropertyRampRate(out uint aRampRate)
        {
			fixed (uint* rampRate = &aRampRate)
			{
	            CpProxyUpnpOrgDimming1PropertyRampRate(iHandle, rampRate);
			}
        }

        /// <summary>
        /// Query the value of the IsRamping property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aIsRamping">Will be set to the value of the property</param>
        public unsafe void PropertyIsRamping(out bool aIsRamping)
        {
			uint isRamping;
	        CpProxyUpnpOrgDimming1PropertyIsRamping(iHandle, &isRamping);
			aIsRamping = (isRamping != 0);
        }

        /// <summary>
        /// Query the value of the RampPaused property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aRampPaused">Will be set to the value of the property</param>
        public unsafe void PropertyRampPaused(out bool aRampPaused)
        {
			uint rampPaused;
	        CpProxyUpnpOrgDimming1PropertyRampPaused(iHandle, &rampPaused);
			aRampPaused = (rampPaused != 0);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyUpnpOrgDimming1()
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
                CpProxyUpnpOrgDimming1Destroy(iHandle);
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

