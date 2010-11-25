using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkMediaTime1 : ICpProxy, IDisposable
    {
        void SyncSeconds(out uint aaSeconds);
        void BeginSeconds(CpProxy.CallbackAsyncComplete aCallback);
        void EndSeconds(uint aAsyncHandle, out uint aaSeconds);

        void SetPropertySecondsChanged(CpProxy.CallbackPropertyChanged aSecondsChanged);
        void PropertySeconds(out uint aSeconds);
    }

    public class CpProxyLinnCoUkMediaTime1 : CpProxy, IDisposable, ICpProxyLinnCoUkMediaTime1
    {
        [DllImport("CpLinnCoUkMediaTime1")]
        static extern uint CpProxyLinnCoUkMediaTime1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkMediaTime1")]
        static extern void CpProxyLinnCoUkMediaTime1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkMediaTime1")]
        static extern unsafe void CpProxyLinnCoUkMediaTime1SyncSeconds(uint aHandle, uint* aaSeconds);
        [DllImport("CpLinnCoUkMediaTime1")]
        static extern unsafe void CpProxyLinnCoUkMediaTime1BeginSeconds(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkMediaTime1")]
        static extern unsafe int CpProxyLinnCoUkMediaTime1EndSeconds(uint aHandle, uint aAsync, uint* aaSeconds);
        [DllImport("CpLinnCoUkMediaTime1")]
        static extern void CpProxyLinnCoUkMediaTime1SetPropertySecondsChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkMediaTime1")]
        static extern unsafe void CpProxyLinnCoUkMediaTime1PropertySeconds(uint aHandle, uint* aSeconds);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iSecondsChanged;
        private Callback iCallbackSecondsChanged;

        public CpProxyLinnCoUkMediaTime1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkMediaTime1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncSeconds(out uint aaSeconds)
        {
			fixed (uint* aSeconds = &aaSeconds)
			{
				CpProxyLinnCoUkMediaTime1SyncSeconds(iHandle, aSeconds);
			}
        }

        public unsafe void BeginSeconds(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkMediaTime1BeginSeconds(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndSeconds(uint aAsyncHandle, out uint aaSeconds)
        {
			fixed (uint* aSeconds = &aaSeconds)
			{
				if (0 != CpProxyLinnCoUkMediaTime1EndSeconds(iHandle, aAsyncHandle, aSeconds))
				{
					throw(new ProxyError());
				}
			}
        }

        public void SetPropertySecondsChanged(CallbackPropertyChanged aSecondsChanged)
        {
            iSecondsChanged = aSecondsChanged;
            iCallbackSecondsChanged = new Callback(PropertySecondsChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkMediaTime1SetPropertySecondsChanged(iHandle, iCallbackSecondsChanged, ptr);
        }

        private void PropertySecondsChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkMediaTime1 self = (CpProxyLinnCoUkMediaTime1)gch.Target;
            self.iSecondsChanged();
        }

        public unsafe void PropertySeconds(out uint aSeconds)
        {
			fixed (uint* seconds = &aSeconds)
			{
	            CpProxyLinnCoUkMediaTime1PropertySeconds(iHandle, seconds);
			}
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkMediaTime1()
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
                CpProxyLinnCoUkMediaTime1Destroy(iHandle);
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

