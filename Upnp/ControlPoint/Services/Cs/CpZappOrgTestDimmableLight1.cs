using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyZappOrgTestDimmableLight1 : CpProxy, IDisposable
    {
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern IntPtr CpProxyZappOrgTestDimmableLight1Create(IntPtr aDeviceHandle);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern void CpProxyZappOrgTestDimmableLight1Destroy(IntPtr aHandle);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern unsafe void CpProxyZappOrgTestDimmableLight1SyncGetLevel(IntPtr aHandle, uint* aLevel);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern unsafe void CpProxyZappOrgTestDimmableLight1BeginGetLevel(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern unsafe int CpProxyZappOrgTestDimmableLight1EndGetLevel(IntPtr aHandle, IntPtr aAsync, uint* aLevel);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern unsafe void CpProxyZappOrgTestDimmableLight1SyncSetLevel(IntPtr aHandle, uint aLevel);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern unsafe void CpProxyZappOrgTestDimmableLight1BeginSetLevel(IntPtr aHandle, uint aLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestDimmableLight1")]
        static extern unsafe int CpProxyZappOrgTestDimmableLight1EndSetLevel(IntPtr aHandle, IntPtr aAsync);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;

        public CpProxyZappOrgTestDimmableLight1(CpDevice aDevice)
        {
            iHandle = CpProxyZappOrgTestDimmableLight1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncGetLevel(out uint aLevel)
        {
			fixed (uint* level = &aLevel)
			{
				CpProxyZappOrgTestDimmableLight1SyncGetLevel(iHandle, level);
			}
        }

        public unsafe void BeginGetLevel(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestDimmableLight1BeginGetLevel(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetLevel(IntPtr aAsyncHandle, out uint aLevel)
        {
			fixed (uint* level = &aLevel)
			{
				if (0 != CpProxyZappOrgTestDimmableLight1EndGetLevel(iHandle, aAsyncHandle, level))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetLevel(uint aLevel)
        {
			{
				CpProxyZappOrgTestDimmableLight1SyncSetLevel(iHandle, aLevel);
			}
        }

        public unsafe void BeginSetLevel(uint aLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestDimmableLight1BeginSetLevel(iHandle, aLevel, iActionComplete, ptr);
        }

        public unsafe void EndSetLevel(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestDimmableLight1EndSetLevel(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyZappOrgTestDimmableLight1()
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
            CpProxyZappOrgTestDimmableLight1Destroy(handle);
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

