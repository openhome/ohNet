using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkPreamp4 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkPreamp4")]
        static extern IntPtr CpProxyLinnCoUkPreamp4Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern void CpProxyLinnCoUkPreamp4Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncVolumeInc(IntPtr aHandle);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginVolumeInc(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndVolumeInc(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncVolumeDec(IntPtr aHandle);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginVolumeDec(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndVolumeDec(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncSetVolume(IntPtr aHandle, uint aaVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginSetVolume(IntPtr aHandle, uint aaVolume, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndSetVolume(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncVolume(IntPtr aHandle, uint* aaVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginVolume(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndVolume(IntPtr aHandle, IntPtr aAsync, uint* aaVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncSetMute(IntPtr aHandle, uint aaMute);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginSetMute(IntPtr aHandle, uint aaMute, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndSetMute(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncMute(IntPtr aHandle, uint* aaMute);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginMute(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndMute(IntPtr aHandle, IntPtr aAsync, uint* aaMute);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncSetBalance(IntPtr aHandle, int aaBalance);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginSetBalance(IntPtr aHandle, int aaBalance, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndSetBalance(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncBalance(IntPtr aHandle, int* aaBalance);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginBalance(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndBalance(IntPtr aHandle, IntPtr aAsync, int* aaBalance);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncSetVolumeLimit(IntPtr aHandle, uint aaVolumeLimit);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginSetVolumeLimit(IntPtr aHandle, uint aaVolumeLimit, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndSetVolumeLimit(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncVolumeLimit(IntPtr aHandle, uint* aaVolumeLimit);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginVolumeLimit(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndVolumeLimit(IntPtr aHandle, IntPtr aAsync, uint* aaVolumeLimit);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncSetStartupVolume(IntPtr aHandle, uint aaStartupVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginSetStartupVolume(IntPtr aHandle, uint aaStartupVolume, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndSetStartupVolume(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncStartupVolume(IntPtr aHandle, uint* aaStartupVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginStartupVolume(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndStartupVolume(IntPtr aHandle, IntPtr aAsync, uint* aaStartupVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncSetStartupVolumeEnabled(IntPtr aHandle, uint aaStartupVolumeEnabled);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginSetStartupVolumeEnabled(IntPtr aHandle, uint aaStartupVolumeEnabled, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndSetStartupVolumeEnabled(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4SyncStartupVolumeEnabled(IntPtr aHandle, uint* aaStartupVolumeEnabled);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4BeginStartupVolumeEnabled(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe int CpProxyLinnCoUkPreamp4EndStartupVolumeEnabled(IntPtr aHandle, IntPtr aAsync, uint* aaStartupVolumeEnabled);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern void CpProxyLinnCoUkPreamp4SetPropertyVolumeChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern void CpProxyLinnCoUkPreamp4SetPropertyMuteChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern void CpProxyLinnCoUkPreamp4SetPropertyBalanceChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern void CpProxyLinnCoUkPreamp4SetPropertyVolumeLimitChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern void CpProxyLinnCoUkPreamp4SetPropertyStartupVolumeChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern void CpProxyLinnCoUkPreamp4SetPropertyStartupVolumeEnabledChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4PropertyVolume(IntPtr aHandle, uint* aVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4PropertyMute(IntPtr aHandle, uint* aMute);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4PropertyBalance(IntPtr aHandle, int* aBalance);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4PropertyVolumeLimit(IntPtr aHandle, uint* aVolumeLimit);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4PropertyStartupVolume(IntPtr aHandle, uint* aStartupVolume);
        [DllImport("CpLinnCoUkPreamp4")]
        static extern unsafe void CpProxyLinnCoUkPreamp4PropertyStartupVolumeEnabled(IntPtr aHandle, uint* aStartupVolumeEnabled);
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

        public CpProxyLinnCoUkPreamp4(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkPreamp4Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncVolumeInc()
        {
			{
				CpProxyLinnCoUkPreamp4SyncVolumeInc(iHandle);
			}
        }

        public unsafe void BeginVolumeInc(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginVolumeInc(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndVolumeInc(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndVolumeInc(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncVolumeDec()
        {
			{
				CpProxyLinnCoUkPreamp4SyncVolumeDec(iHandle);
			}
        }

        public unsafe void BeginVolumeDec(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginVolumeDec(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndVolumeDec(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndVolumeDec(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetVolume(uint aaVolume)
        {
			{
				CpProxyLinnCoUkPreamp4SyncSetVolume(iHandle, aaVolume);
			}
        }

        public unsafe void BeginSetVolume(uint aaVolume, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginSetVolume(iHandle, aaVolume, iActionComplete, ptr);
        }

        public unsafe void EndSetVolume(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndSetVolume(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncVolume(out uint aaVolume)
        {
			fixed (uint* aVolume = &aaVolume)
			{
				CpProxyLinnCoUkPreamp4SyncVolume(iHandle, aVolume);
			}
        }

        public unsafe void BeginVolume(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginVolume(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndVolume(IntPtr aAsyncHandle, out uint aaVolume)
        {
			fixed (uint* aVolume = &aaVolume)
			{
				if (0 != CpProxyLinnCoUkPreamp4EndVolume(iHandle, aAsyncHandle, aVolume))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetMute(bool aaMute)
        {
			uint aMute = (aaMute? 1u : 0u);
			{
				CpProxyLinnCoUkPreamp4SyncSetMute(iHandle, aMute);
			}
        }

        public unsafe void BeginSetMute(bool aaMute, CallbackAsyncComplete aCallback)
        {
			uint aMute = (aaMute? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginSetMute(iHandle, aMute, iActionComplete, ptr);
        }

        public unsafe void EndSetMute(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndSetMute(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncMute(out bool aaMute)
        {
			uint aMute;
			{
				CpProxyLinnCoUkPreamp4SyncMute(iHandle, &aMute);
			}
			aaMute = (aMute != 0);
        }

        public unsafe void BeginMute(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginMute(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndMute(IntPtr aAsyncHandle, out bool aaMute)
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

        public unsafe void SyncSetBalance(int aaBalance)
        {
			{
				CpProxyLinnCoUkPreamp4SyncSetBalance(iHandle, aaBalance);
			}
        }

        public unsafe void BeginSetBalance(int aaBalance, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginSetBalance(iHandle, aaBalance, iActionComplete, ptr);
        }

        public unsafe void EndSetBalance(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndSetBalance(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncBalance(out int aaBalance)
        {
			fixed (int* aBalance = &aaBalance)
			{
				CpProxyLinnCoUkPreamp4SyncBalance(iHandle, aBalance);
			}
        }

        public unsafe void BeginBalance(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginBalance(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndBalance(IntPtr aAsyncHandle, out int aaBalance)
        {
			fixed (int* aBalance = &aaBalance)
			{
				if (0 != CpProxyLinnCoUkPreamp4EndBalance(iHandle, aAsyncHandle, aBalance))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetVolumeLimit(uint aaVolumeLimit)
        {
			{
				CpProxyLinnCoUkPreamp4SyncSetVolumeLimit(iHandle, aaVolumeLimit);
			}
        }

        public unsafe void BeginSetVolumeLimit(uint aaVolumeLimit, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginSetVolumeLimit(iHandle, aaVolumeLimit, iActionComplete, ptr);
        }

        public unsafe void EndSetVolumeLimit(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndSetVolumeLimit(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncVolumeLimit(out uint aaVolumeLimit)
        {
			fixed (uint* aVolumeLimit = &aaVolumeLimit)
			{
				CpProxyLinnCoUkPreamp4SyncVolumeLimit(iHandle, aVolumeLimit);
			}
        }

        public unsafe void BeginVolumeLimit(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginVolumeLimit(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndVolumeLimit(IntPtr aAsyncHandle, out uint aaVolumeLimit)
        {
			fixed (uint* aVolumeLimit = &aaVolumeLimit)
			{
				if (0 != CpProxyLinnCoUkPreamp4EndVolumeLimit(iHandle, aAsyncHandle, aVolumeLimit))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetStartupVolume(uint aaStartupVolume)
        {
			{
				CpProxyLinnCoUkPreamp4SyncSetStartupVolume(iHandle, aaStartupVolume);
			}
        }

        public unsafe void BeginSetStartupVolume(uint aaStartupVolume, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginSetStartupVolume(iHandle, aaStartupVolume, iActionComplete, ptr);
        }

        public unsafe void EndSetStartupVolume(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndSetStartupVolume(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStartupVolume(out uint aaStartupVolume)
        {
			fixed (uint* aStartupVolume = &aaStartupVolume)
			{
				CpProxyLinnCoUkPreamp4SyncStartupVolume(iHandle, aStartupVolume);
			}
        }

        public unsafe void BeginStartupVolume(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginStartupVolume(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndStartupVolume(IntPtr aAsyncHandle, out uint aaStartupVolume)
        {
			fixed (uint* aStartupVolume = &aaStartupVolume)
			{
				if (0 != CpProxyLinnCoUkPreamp4EndStartupVolume(iHandle, aAsyncHandle, aStartupVolume))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetStartupVolumeEnabled(bool aaStartupVolumeEnabled)
        {
			uint aStartupVolumeEnabled = (aaStartupVolumeEnabled? 1u : 0u);
			{
				CpProxyLinnCoUkPreamp4SyncSetStartupVolumeEnabled(iHandle, aStartupVolumeEnabled);
			}
        }

        public unsafe void BeginSetStartupVolumeEnabled(bool aaStartupVolumeEnabled, CallbackAsyncComplete aCallback)
        {
			uint aStartupVolumeEnabled = (aaStartupVolumeEnabled? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginSetStartupVolumeEnabled(iHandle, aStartupVolumeEnabled, iActionComplete, ptr);
        }

        public unsafe void EndSetStartupVolumeEnabled(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPreamp4EndSetStartupVolumeEnabled(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStartupVolumeEnabled(out bool aaStartupVolumeEnabled)
        {
			uint aStartupVolumeEnabled;
			{
				CpProxyLinnCoUkPreamp4SyncStartupVolumeEnabled(iHandle, &aStartupVolumeEnabled);
			}
			aaStartupVolumeEnabled = (aStartupVolumeEnabled != 0);
        }

        public unsafe void BeginStartupVolumeEnabled(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPreamp4BeginStartupVolumeEnabled(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndStartupVolumeEnabled(IntPtr aAsyncHandle, out bool aaStartupVolumeEnabled)
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

        public unsafe void PropertyVolume(out uint aVolume)
        {
			fixed (uint* volume = &aVolume)
			{
	            CpProxyLinnCoUkPreamp4PropertyVolume(iHandle, volume);
			}
        }

        public unsafe void PropertyMute(out bool aMute)
        {
			uint mute;
	        CpProxyLinnCoUkPreamp4PropertyMute(iHandle, &mute);
			aMute = (mute != 0);
        }

        public unsafe void PropertyBalance(out int aBalance)
        {
			fixed (int* balance = &aBalance)
			{
	            CpProxyLinnCoUkPreamp4PropertyBalance(iHandle, balance);
			}
        }

        public unsafe void PropertyVolumeLimit(out uint aVolumeLimit)
        {
			fixed (uint* volumeLimit = &aVolumeLimit)
			{
	            CpProxyLinnCoUkPreamp4PropertyVolumeLimit(iHandle, volumeLimit);
			}
        }

        public unsafe void PropertyStartupVolume(out uint aStartupVolume)
        {
			fixed (uint* startupVolume = &aStartupVolume)
			{
	            CpProxyLinnCoUkPreamp4PropertyStartupVolume(iHandle, startupVolume);
			}
        }

        public unsafe void PropertyStartupVolumeEnabled(out bool aStartupVolumeEnabled)
        {
			uint startupVolumeEnabled;
	        CpProxyLinnCoUkPreamp4PropertyStartupVolumeEnabled(iHandle, &startupVolumeEnabled);
			aStartupVolumeEnabled = (startupVolumeEnabled != 0);
        }

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
            CpProxyLinnCoUkPreamp4Destroy(handle);
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

