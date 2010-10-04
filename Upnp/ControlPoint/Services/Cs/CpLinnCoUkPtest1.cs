using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkPtest1 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkPtest1")]
        static extern uint CpProxyLinnCoUkPtest1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkPtest1")]
        static extern void CpProxyLinnCoUkPtest1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe void CpProxyLinnCoUkPtest1SyncTestComPort(uint aHandle, uint aaPort, uint* aaResult);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe void CpProxyLinnCoUkPtest1BeginTestComPort(uint aHandle, uint aaPort, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe int CpProxyLinnCoUkPtest1EndTestComPort(uint aHandle, uint aAsync, uint* aaResult);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe void CpProxyLinnCoUkPtest1SyncLedsOn(uint aHandle);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe void CpProxyLinnCoUkPtest1BeginLedsOn(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe int CpProxyLinnCoUkPtest1EndLedsOn(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe void CpProxyLinnCoUkPtest1SyncLedsOff(uint aHandle);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe void CpProxyLinnCoUkPtest1BeginLedsOff(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe int CpProxyLinnCoUkPtest1EndLedsOff(uint aHandle, uint aAsync);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;

        public CpProxyLinnCoUkPtest1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkPtest1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncTestComPort(uint aaPort, out bool aaResult)
        {
			uint aResult;
			{
				CpProxyLinnCoUkPtest1SyncTestComPort(iHandle, aaPort, &aResult);
			}
			aaResult = (aResult != 0);
        }

        public unsafe void BeginTestComPort(uint aaPort, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPtest1BeginTestComPort(iHandle, aaPort, iActionComplete, ptr);
        }

        public unsafe void EndTestComPort(uint aAsyncHandle, out bool aaResult)
        {
			uint aResult;
			{
				if (0 != CpProxyLinnCoUkPtest1EndTestComPort(iHandle, aAsyncHandle, &aResult))
				{
					throw(new ProxyError());
				}
			}
			aaResult = (aResult != 0);
        }

        public unsafe void SyncLedsOn()
        {
			{
				CpProxyLinnCoUkPtest1SyncLedsOn(iHandle);
			}
        }

        public unsafe void BeginLedsOn(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPtest1BeginLedsOn(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndLedsOn(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPtest1EndLedsOn(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncLedsOff()
        {
			{
				CpProxyLinnCoUkPtest1SyncLedsOff(iHandle);
			}
        }

        public unsafe void BeginLedsOff(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPtest1BeginLedsOff(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndLedsOff(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkPtest1EndLedsOff(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkPtest1()
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
            CpProxyLinnCoUkPtest1Destroy(handle);
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

