using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyUpnpOrgDimming1 : CpProxy, IDisposable
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

        public CpProxyUpnpOrgDimming1(CpDevice aDevice)
        {
            iHandle = CpProxyUpnpOrgDimming1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncSetLoadLevelTarget(uint anewLoadlevelTarget)
        {
			{
				CpProxyUpnpOrgDimming1SyncSetLoadLevelTarget(iHandle, anewLoadlevelTarget);
			}
        }

        public unsafe void BeginSetLoadLevelTarget(uint anewLoadlevelTarget, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginSetLoadLevelTarget(iHandle, anewLoadlevelTarget, iActionComplete, ptr);
        }

        public unsafe void EndSetLoadLevelTarget(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndSetLoadLevelTarget(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetLoadLevelTarget(out uint aGetLoadlevelTarget)
        {
			fixed (uint* getLoadlevelTarget = &aGetLoadlevelTarget)
			{
				CpProxyUpnpOrgDimming1SyncGetLoadLevelTarget(iHandle, getLoadlevelTarget);
			}
        }

        public unsafe void BeginGetLoadLevelTarget(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetLoadLevelTarget(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void SyncGetLoadLevelStatus(out uint aretLoadlevelStatus)
        {
			fixed (uint* retLoadlevelStatus = &aretLoadlevelStatus)
			{
				CpProxyUpnpOrgDimming1SyncGetLoadLevelStatus(iHandle, retLoadlevelStatus);
			}
        }

        public unsafe void BeginGetLoadLevelStatus(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetLoadLevelStatus(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void SyncSetOnEffectLevel(uint anewOnEffectLevel)
        {
			{
				CpProxyUpnpOrgDimming1SyncSetOnEffectLevel(iHandle, anewOnEffectLevel);
			}
        }

        public unsafe void BeginSetOnEffectLevel(uint anewOnEffectLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginSetOnEffectLevel(iHandle, anewOnEffectLevel, iActionComplete, ptr);
        }

        public unsafe void EndSetOnEffectLevel(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndSetOnEffectLevel(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetOnEffect(string anewOnEffect)
        {
			char* newOnEffect = (char*)Marshal.StringToHGlobalAnsi(anewOnEffect);
			{
				CpProxyUpnpOrgDimming1SyncSetOnEffect(iHandle, newOnEffect);
			}
			Marshal.FreeHGlobal((IntPtr)newOnEffect);
        }

        public unsafe void BeginSetOnEffect(string anewOnEffect, CallbackAsyncComplete aCallback)
        {
			char* newOnEffect = (char*)Marshal.StringToHGlobalAnsi(anewOnEffect);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginSetOnEffect(iHandle, newOnEffect, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)newOnEffect);
        }

        public unsafe void EndSetOnEffect(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndSetOnEffect(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

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

        public unsafe void BeginGetOnEffectParameters(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetOnEffectParameters(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void SyncStepUp()
        {
			{
				CpProxyUpnpOrgDimming1SyncStepUp(iHandle);
			}
        }

        public unsafe void BeginStepUp(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginStepUp(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndStepUp(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndStepUp(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStepDown()
        {
			{
				CpProxyUpnpOrgDimming1SyncStepDown(iHandle);
			}
        }

        public unsafe void BeginStepDown(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginStepDown(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndStepDown(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndStepDown(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStartRampUp()
        {
			{
				CpProxyUpnpOrgDimming1SyncStartRampUp(iHandle);
			}
        }

        public unsafe void BeginStartRampUp(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginStartRampUp(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndStartRampUp(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndStartRampUp(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStartRampDown()
        {
			{
				CpProxyUpnpOrgDimming1SyncStartRampDown(iHandle);
			}
        }

        public unsafe void BeginStartRampDown(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginStartRampDown(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndStartRampDown(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndStartRampDown(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStopRamp()
        {
			{
				CpProxyUpnpOrgDimming1SyncStopRamp(iHandle);
			}
        }

        public unsafe void BeginStopRamp(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginStopRamp(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndStopRamp(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndStopRamp(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStartRampToLevel(uint anewLoadLevelTarget, uint anewRampTime)
        {
			{
				CpProxyUpnpOrgDimming1SyncStartRampToLevel(iHandle, anewLoadLevelTarget, anewRampTime);
			}
        }

        public unsafe void BeginStartRampToLevel(uint anewLoadLevelTarget, uint anewRampTime, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginStartRampToLevel(iHandle, anewLoadLevelTarget, anewRampTime, iActionComplete, ptr);
        }

        public unsafe void EndStartRampToLevel(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndStartRampToLevel(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetStepDelta(uint anewStepDelta)
        {
			{
				CpProxyUpnpOrgDimming1SyncSetStepDelta(iHandle, anewStepDelta);
			}
        }

        public unsafe void BeginSetStepDelta(uint anewStepDelta, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginSetStepDelta(iHandle, anewStepDelta, iActionComplete, ptr);
        }

        public unsafe void EndSetStepDelta(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndSetStepDelta(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetStepDelta(out uint aretStepDelta)
        {
			fixed (uint* retStepDelta = &aretStepDelta)
			{
				CpProxyUpnpOrgDimming1SyncGetStepDelta(iHandle, retStepDelta);
			}
        }

        public unsafe void BeginGetStepDelta(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetStepDelta(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void SyncSetRampRate(uint anewRampRate)
        {
			{
				CpProxyUpnpOrgDimming1SyncSetRampRate(iHandle, anewRampRate);
			}
        }

        public unsafe void BeginSetRampRate(uint anewRampRate, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginSetRampRate(iHandle, anewRampRate, iActionComplete, ptr);
        }

        public unsafe void EndSetRampRate(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndSetRampRate(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetRampRate(out uint aretRampRate)
        {
			fixed (uint* retRampRate = &aretRampRate)
			{
				CpProxyUpnpOrgDimming1SyncGetRampRate(iHandle, retRampRate);
			}
        }

        public unsafe void BeginGetRampRate(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetRampRate(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void SyncPauseRamp()
        {
			{
				CpProxyUpnpOrgDimming1SyncPauseRamp(iHandle);
			}
        }

        public unsafe void BeginPauseRamp(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginPauseRamp(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndPauseRamp(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndPauseRamp(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncResumeRamp()
        {
			{
				CpProxyUpnpOrgDimming1SyncResumeRamp(iHandle);
			}
        }

        public unsafe void BeginResumeRamp(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginResumeRamp(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndResumeRamp(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgDimming1EndResumeRamp(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetIsRamping(out bool aretIsRamping)
        {
			uint retIsRamping;
			{
				CpProxyUpnpOrgDimming1SyncGetIsRamping(iHandle, &retIsRamping);
			}
			aretIsRamping = (retIsRamping != 0);
        }

        public unsafe void BeginGetIsRamping(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetIsRamping(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void SyncGetRampPaused(out bool aretRampPaused)
        {
			uint retRampPaused;
			{
				CpProxyUpnpOrgDimming1SyncGetRampPaused(iHandle, &retRampPaused);
			}
			aretRampPaused = (retRampPaused != 0);
        }

        public unsafe void BeginGetRampPaused(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetRampPaused(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void SyncGetRampTime(out uint aretRampTime)
        {
			fixed (uint* retRampTime = &aretRampTime)
			{
				CpProxyUpnpOrgDimming1SyncGetRampTime(iHandle, retRampTime);
			}
        }

        public unsafe void BeginGetRampTime(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgDimming1BeginGetRampTime(iHandle, iActionComplete, ptr);
        }

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

        public unsafe void PropertyLoadLevelStatus(out uint aLoadLevelStatus)
        {
			fixed (uint* loadLevelStatus = &aLoadLevelStatus)
			{
	            CpProxyUpnpOrgDimming1PropertyLoadLevelStatus(iHandle, loadLevelStatus);
			}
        }

        public unsafe void PropertyStepDelta(out uint aStepDelta)
        {
			fixed (uint* stepDelta = &aStepDelta)
			{
	            CpProxyUpnpOrgDimming1PropertyStepDelta(iHandle, stepDelta);
			}
        }

        public unsafe void PropertyRampRate(out uint aRampRate)
        {
			fixed (uint* rampRate = &aRampRate)
			{
	            CpProxyUpnpOrgDimming1PropertyRampRate(iHandle, rampRate);
			}
        }

        public unsafe void PropertyIsRamping(out bool aIsRamping)
        {
			uint isRamping;
	        CpProxyUpnpOrgDimming1PropertyIsRamping(iHandle, &isRamping);
			aIsRamping = (isRamping != 0);
        }

        public unsafe void PropertyRampPaused(out bool aRampPaused)
        {
			uint rampPaused;
	        CpProxyUpnpOrgDimming1PropertyRampPaused(iHandle, &rampPaused);
			aRampPaused = (rampPaused != 0);
        }

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
            CpProxyUpnpOrgDimming1Destroy(handle);
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

