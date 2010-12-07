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
        void EndSetLoadLevelTarget(IntPtr aAsyncHandle);
        void SyncGetLoadLevelTarget(out uint aGetLoadlevelTarget);
        void BeginGetLoadLevelTarget(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetLoadLevelTarget(IntPtr aAsyncHandle, out uint aGetLoadlevelTarget);
        void SyncGetLoadLevelStatus(out uint aretLoadlevelStatus);
        void BeginGetLoadLevelStatus(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetLoadLevelStatus(IntPtr aAsyncHandle, out uint aretLoadlevelStatus);
        void SyncSetOnEffectLevel(uint anewOnEffectLevel);
        void BeginSetOnEffectLevel(uint anewOnEffectLevel, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetOnEffectLevel(IntPtr aAsyncHandle);
        void SyncSetOnEffect(string anewOnEffect);
        void BeginSetOnEffect(string anewOnEffect, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetOnEffect(IntPtr aAsyncHandle);
        void SyncGetOnEffectParameters(out string aretOnEffect, out uint aretOnEffectLevel);
        void BeginGetOnEffectParameters(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetOnEffectParameters(IntPtr aAsyncHandle, out string aretOnEffect, out uint aretOnEffectLevel);
        void SyncStepUp();
        void BeginStepUp(CpProxy.CallbackAsyncComplete aCallback);
        void EndStepUp(IntPtr aAsyncHandle);
        void SyncStepDown();
        void BeginStepDown(CpProxy.CallbackAsyncComplete aCallback);
        void EndStepDown(IntPtr aAsyncHandle);
        void SyncStartRampUp();
        void BeginStartRampUp(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartRampUp(IntPtr aAsyncHandle);
        void SyncStartRampDown();
        void BeginStartRampDown(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartRampDown(IntPtr aAsyncHandle);
        void SyncStopRamp();
        void BeginStopRamp(CpProxy.CallbackAsyncComplete aCallback);
        void EndStopRamp(IntPtr aAsyncHandle);
        void SyncStartRampToLevel(uint anewLoadLevelTarget, uint anewRampTime);
        void BeginStartRampToLevel(uint anewLoadLevelTarget, uint anewRampTime, CpProxy.CallbackAsyncComplete aCallback);
        void EndStartRampToLevel(IntPtr aAsyncHandle);
        void SyncSetStepDelta(uint anewStepDelta);
        void BeginSetStepDelta(uint anewStepDelta, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStepDelta(IntPtr aAsyncHandle);
        void SyncGetStepDelta(out uint aretStepDelta);
        void BeginGetStepDelta(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetStepDelta(IntPtr aAsyncHandle, out uint aretStepDelta);
        void SyncSetRampRate(uint anewRampRate);
        void BeginSetRampRate(uint anewRampRate, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetRampRate(IntPtr aAsyncHandle);
        void SyncGetRampRate(out uint aretRampRate);
        void BeginGetRampRate(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRampRate(IntPtr aAsyncHandle, out uint aretRampRate);
        void SyncPauseRamp();
        void BeginPauseRamp(CpProxy.CallbackAsyncComplete aCallback);
        void EndPauseRamp(IntPtr aAsyncHandle);
        void SyncResumeRamp();
        void BeginResumeRamp(CpProxy.CallbackAsyncComplete aCallback);
        void EndResumeRamp(IntPtr aAsyncHandle);
        void SyncGetIsRamping(out bool aretIsRamping);
        void BeginGetIsRamping(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetIsRamping(IntPtr aAsyncHandle, out bool aretIsRamping);
        void SyncGetRampPaused(out bool aretRampPaused);
        void BeginGetRampPaused(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRampPaused(IntPtr aAsyncHandle, out bool aretRampPaused);
        void SyncGetRampTime(out uint aretRampTime);
        void BeginGetRampTime(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRampTime(IntPtr aAsyncHandle, out uint aretRampTime);

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

    /// <summary>
    /// Proxy for the upnp.org:Dimming:1 UPnP service
    /// </summary>
    public class CpProxyUpnpOrgDimming1 : CpProxy, IDisposable, ICpProxyUpnpOrgDimming1
    {
        [DllImport("CpUpnpOrgDimming1")]
        static extern IntPtr CpProxyUpnpOrgDimming1Create(IntPtr aDeviceHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern void CpProxyUpnpOrgDimming1Destroy(IntPtr aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncSetLoadLevelTarget(IntPtr aHandle, uint anewLoadlevelTarget);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginSetLoadLevelTarget(IntPtr aHandle, uint anewLoadlevelTarget, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndSetLoadLevelTarget(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetLoadLevelTarget(IntPtr aHandle, uint* aGetLoadlevelTarget);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetLoadLevelTarget(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetLoadLevelTarget(IntPtr aHandle, IntPtr aAsync, uint* aGetLoadlevelTarget);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetLoadLevelStatus(IntPtr aHandle, uint* aretLoadlevelStatus);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetLoadLevelStatus(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetLoadLevelStatus(IntPtr aHandle, IntPtr aAsync, uint* aretLoadlevelStatus);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncSetOnEffectLevel(IntPtr aHandle, uint anewOnEffectLevel);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginSetOnEffectLevel(IntPtr aHandle, uint anewOnEffectLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndSetOnEffectLevel(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncSetOnEffect(IntPtr aHandle, char* anewOnEffect);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginSetOnEffect(IntPtr aHandle, char* anewOnEffect, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndSetOnEffect(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetOnEffectParameters(IntPtr aHandle, char** aretOnEffect, uint* aretOnEffectLevel);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetOnEffectParameters(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetOnEffectParameters(IntPtr aHandle, IntPtr aAsync, char** aretOnEffect, uint* aretOnEffectLevel);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncStepUp(IntPtr aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginStepUp(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndStepUp(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncStepDown(IntPtr aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginStepDown(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndStepDown(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncStartRampUp(IntPtr aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginStartRampUp(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndStartRampUp(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncStartRampDown(IntPtr aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginStartRampDown(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndStartRampDown(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncStopRamp(IntPtr aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginStopRamp(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndStopRamp(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncStartRampToLevel(IntPtr aHandle, uint anewLoadLevelTarget, uint anewRampTime);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginStartRampToLevel(IntPtr aHandle, uint anewLoadLevelTarget, uint anewRampTime, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndStartRampToLevel(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncSetStepDelta(IntPtr aHandle, uint anewStepDelta);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginSetStepDelta(IntPtr aHandle, uint anewStepDelta, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndSetStepDelta(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetStepDelta(IntPtr aHandle, uint* aretStepDelta);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetStepDelta(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetStepDelta(IntPtr aHandle, IntPtr aAsync, uint* aretStepDelta);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncSetRampRate(IntPtr aHandle, uint anewRampRate);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginSetRampRate(IntPtr aHandle, uint anewRampRate, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndSetRampRate(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetRampRate(IntPtr aHandle, uint* aretRampRate);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetRampRate(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetRampRate(IntPtr aHandle, IntPtr aAsync, uint* aretRampRate);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncPauseRamp(IntPtr aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginPauseRamp(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndPauseRamp(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncResumeRamp(IntPtr aHandle);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginResumeRamp(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndResumeRamp(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetIsRamping(IntPtr aHandle, uint* aretIsRamping);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetIsRamping(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetIsRamping(IntPtr aHandle, IntPtr aAsync, uint* aretIsRamping);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetRampPaused(IntPtr aHandle, uint* aretRampPaused);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetRampPaused(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetRampPaused(IntPtr aHandle, IntPtr aAsync, uint* aretRampPaused);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1SyncGetRampTime(IntPtr aHandle, uint* aretRampTime);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1BeginGetRampTime(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe int CpProxyUpnpOrgDimming1EndGetRampTime(IntPtr aHandle, IntPtr aAsync, uint* aretRampTime);
        [DllImport("CpUpnpOrgDimming1")]
        static extern void CpProxyUpnpOrgDimming1SetPropertyLoadLevelStatusChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern void CpProxyUpnpOrgDimming1SetPropertyStepDeltaChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern void CpProxyUpnpOrgDimming1SetPropertyRampRateChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern void CpProxyUpnpOrgDimming1SetPropertyIsRampingChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern void CpProxyUpnpOrgDimming1SetPropertyRampPausedChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1PropertyLoadLevelStatus(IntPtr aHandle, uint* aLoadLevelStatus);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1PropertyStepDelta(IntPtr aHandle, uint* aStepDelta);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1PropertyRampRate(IntPtr aHandle, uint* aRampRate);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1PropertyIsRamping(IntPtr aHandle, uint* aIsRamping);
        [DllImport("CpUpnpOrgDimming1")]
        static extern unsafe void CpProxyUpnpOrgDimming1PropertyRampPaused(IntPtr aHandle, uint* aRampPaused);
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
        public unsafe void EndSetLoadLevelTarget(IntPtr aAsyncHandle)
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
        public unsafe void EndGetLoadLevelTarget(IntPtr aAsyncHandle, out uint aGetLoadlevelTarget)
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
        public unsafe void EndGetLoadLevelStatus(IntPtr aAsyncHandle, out uint aretLoadlevelStatus)
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
        public unsafe void EndSetOnEffectLevel(IntPtr aAsyncHandle)
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
        public unsafe void EndSetOnEffect(IntPtr aAsyncHandle)
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
        public unsafe void EndGetOnEffectParameters(IntPtr aAsyncHandle, out string aretOnEffect, out uint aretOnEffectLevel)
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
        public unsafe void EndStepUp(IntPtr aAsyncHandle)
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
        public unsafe void EndStepDown(IntPtr aAsyncHandle)
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
        public unsafe void EndStartRampUp(IntPtr aAsyncHandle)
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
        public unsafe void EndStartRampDown(IntPtr aAsyncHandle)
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
        public unsafe void EndStopRamp(IntPtr aAsyncHandle)
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
        public unsafe void EndStartRampToLevel(IntPtr aAsyncHandle)
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
        public unsafe void EndSetStepDelta(IntPtr aAsyncHandle)
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
        public unsafe void EndGetStepDelta(IntPtr aAsyncHandle, out uint aretStepDelta)
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
        public unsafe void EndSetRampRate(IntPtr aAsyncHandle)
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
        public unsafe void EndGetRampRate(IntPtr aAsyncHandle, out uint aretRampRate)
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
        public unsafe void EndPauseRamp(IntPtr aAsyncHandle)
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
        public unsafe void EndResumeRamp(IntPtr aAsyncHandle)
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
        public unsafe void EndGetIsRamping(IntPtr aAsyncHandle, out bool aretIsRamping)
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
        public unsafe void EndGetRampPaused(IntPtr aAsyncHandle, out bool aretRampPaused)
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
        public unsafe void EndGetRampTime(IntPtr aAsyncHandle, out uint aretRampTime)
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
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                CpProxyUpnpOrgDimming1Destroy(iHandle);
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

