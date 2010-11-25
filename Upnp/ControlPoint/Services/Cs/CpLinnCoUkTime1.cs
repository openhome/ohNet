using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkTime1 : ICpProxy, IDisposable
    {
        void SyncTime(out uint aaTrackCount, out uint aaDuration, out uint aaSeconds);
        void BeginTime(CpProxy.CallbackAsyncComplete aCallback);
        void EndTime(uint aAsyncHandle, out uint aaTrackCount, out uint aaDuration, out uint aaSeconds);

        void SetPropertyTrackCountChanged(CpProxy.CallbackPropertyChanged aTrackCountChanged);
        void PropertyTrackCount(out uint aTrackCount);
        void SetPropertyDurationChanged(CpProxy.CallbackPropertyChanged aDurationChanged);
        void PropertyDuration(out uint aDuration);
        void SetPropertySecondsChanged(CpProxy.CallbackPropertyChanged aSecondsChanged);
        void PropertySeconds(out uint aSeconds);
    }

    public class CpProxyLinnCoUkTime1 : CpProxy, IDisposable, ICpProxyLinnCoUkTime1
    {
        [DllImport("CpLinnCoUkTime1")]
        static extern uint CpProxyLinnCoUkTime1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkTime1")]
        static extern void CpProxyLinnCoUkTime1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkTime1")]
        static extern unsafe void CpProxyLinnCoUkTime1SyncTime(uint aHandle, uint* aaTrackCount, uint* aaDuration, uint* aaSeconds);
        [DllImport("CpLinnCoUkTime1")]
        static extern unsafe void CpProxyLinnCoUkTime1BeginTime(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkTime1")]
        static extern unsafe int CpProxyLinnCoUkTime1EndTime(uint aHandle, uint aAsync, uint* aaTrackCount, uint* aaDuration, uint* aaSeconds);
        [DllImport("CpLinnCoUkTime1")]
        static extern void CpProxyLinnCoUkTime1SetPropertyTrackCountChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkTime1")]
        static extern void CpProxyLinnCoUkTime1SetPropertyDurationChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkTime1")]
        static extern void CpProxyLinnCoUkTime1SetPropertySecondsChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkTime1")]
        static extern unsafe void CpProxyLinnCoUkTime1PropertyTrackCount(uint aHandle, uint* aTrackCount);
        [DllImport("CpLinnCoUkTime1")]
        static extern unsafe void CpProxyLinnCoUkTime1PropertyDuration(uint aHandle, uint* aDuration);
        [DllImport("CpLinnCoUkTime1")]
        static extern unsafe void CpProxyLinnCoUkTime1PropertySeconds(uint aHandle, uint* aSeconds);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iTrackCountChanged;
        private CallbackPropertyChanged iDurationChanged;
        private CallbackPropertyChanged iSecondsChanged;
        private Callback iCallbackTrackCountChanged;
        private Callback iCallbackDurationChanged;
        private Callback iCallbackSecondsChanged;

        public CpProxyLinnCoUkTime1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkTime1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncTime(out uint aaTrackCount, out uint aaDuration, out uint aaSeconds)
        {
			fixed (uint* aTrackCount = &aaTrackCount)
			fixed (uint* aDuration = &aaDuration)
			fixed (uint* aSeconds = &aaSeconds)
			{
				CpProxyLinnCoUkTime1SyncTime(iHandle, aTrackCount, aDuration, aSeconds);
			}
        }

        public unsafe void BeginTime(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkTime1BeginTime(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndTime(uint aAsyncHandle, out uint aaTrackCount, out uint aaDuration, out uint aaSeconds)
        {
			fixed (uint* aTrackCount = &aaTrackCount)
			fixed (uint* aDuration = &aaDuration)
			fixed (uint* aSeconds = &aaSeconds)
			{
				if (0 != CpProxyLinnCoUkTime1EndTime(iHandle, aAsyncHandle, aTrackCount, aDuration, aSeconds))
				{
					throw(new ProxyError());
				}
			}
        }

        public void SetPropertyTrackCountChanged(CallbackPropertyChanged aTrackCountChanged)
        {
            iTrackCountChanged = aTrackCountChanged;
            iCallbackTrackCountChanged = new Callback(PropertyTrackCountChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkTime1SetPropertyTrackCountChanged(iHandle, iCallbackTrackCountChanged, ptr);
        }

        private void PropertyTrackCountChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkTime1 self = (CpProxyLinnCoUkTime1)gch.Target;
            self.iTrackCountChanged();
        }

        public void SetPropertyDurationChanged(CallbackPropertyChanged aDurationChanged)
        {
            iDurationChanged = aDurationChanged;
            iCallbackDurationChanged = new Callback(PropertyDurationChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkTime1SetPropertyDurationChanged(iHandle, iCallbackDurationChanged, ptr);
        }

        private void PropertyDurationChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkTime1 self = (CpProxyLinnCoUkTime1)gch.Target;
            self.iDurationChanged();
        }

        public void SetPropertySecondsChanged(CallbackPropertyChanged aSecondsChanged)
        {
            iSecondsChanged = aSecondsChanged;
            iCallbackSecondsChanged = new Callback(PropertySecondsChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkTime1SetPropertySecondsChanged(iHandle, iCallbackSecondsChanged, ptr);
        }

        private void PropertySecondsChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkTime1 self = (CpProxyLinnCoUkTime1)gch.Target;
            self.iSecondsChanged();
        }

        public unsafe void PropertyTrackCount(out uint aTrackCount)
        {
			fixed (uint* trackCount = &aTrackCount)
			{
	            CpProxyLinnCoUkTime1PropertyTrackCount(iHandle, trackCount);
			}
        }

        public unsafe void PropertyDuration(out uint aDuration)
        {
			fixed (uint* duration = &aDuration)
			{
	            CpProxyLinnCoUkTime1PropertyDuration(iHandle, duration);
			}
        }

        public unsafe void PropertySeconds(out uint aSeconds)
        {
			fixed (uint* seconds = &aSeconds)
			{
	            CpProxyLinnCoUkTime1PropertySeconds(iHandle, seconds);
			}
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkTime1()
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
                CpProxyLinnCoUkTime1Destroy(iHandle);
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

