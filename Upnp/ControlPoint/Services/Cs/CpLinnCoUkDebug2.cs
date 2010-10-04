using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkDebug2 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkDebug2")]
        static extern uint CpProxyLinnCoUkDebug2Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkDebug2")]
        static extern void CpProxyLinnCoUkDebug2Destroy(uint aHandle);
        [DllImport("CpLinnCoUkDebug2")]
        static extern unsafe void CpProxyLinnCoUkDebug2SyncSetDebugLevel(uint aHandle, uint aaDebugLevel);
        [DllImport("CpLinnCoUkDebug2")]
        static extern unsafe void CpProxyLinnCoUkDebug2BeginSetDebugLevel(uint aHandle, uint aaDebugLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDebug2")]
        static extern unsafe int CpProxyLinnCoUkDebug2EndSetDebugLevel(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkDebug2")]
        static extern unsafe void CpProxyLinnCoUkDebug2SyncDebugLevel(uint aHandle, uint* aaDebugLevel);
        [DllImport("CpLinnCoUkDebug2")]
        static extern unsafe void CpProxyLinnCoUkDebug2BeginDebugLevel(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDebug2")]
        static extern unsafe int CpProxyLinnCoUkDebug2EndDebugLevel(uint aHandle, uint aAsync, uint* aaDebugLevel);
        [DllImport("CpLinnCoUkDebug2")]
        static extern unsafe void CpProxyLinnCoUkDebug2SyncMemWrite(uint aHandle, uint aaMemAddress, char* aaMemData, uint aaMemDataLen);
        [DllImport("CpLinnCoUkDebug2")]
        static extern unsafe void CpProxyLinnCoUkDebug2BeginMemWrite(uint aHandle, uint aaMemAddress, char* aaMemData, uint aaMemDataLen, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkDebug2")]
        static extern unsafe int CpProxyLinnCoUkDebug2EndMemWrite(uint aHandle, uint aAsync);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;

        public CpProxyLinnCoUkDebug2(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkDebug2Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncSetDebugLevel(uint aaDebugLevel)
        {
			{
				CpProxyLinnCoUkDebug2SyncSetDebugLevel(iHandle, aaDebugLevel);
			}
        }

        public unsafe void BeginSetDebugLevel(uint aaDebugLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDebug2BeginSetDebugLevel(iHandle, aaDebugLevel, iActionComplete, ptr);
        }

        public unsafe void EndSetDebugLevel(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDebug2EndSetDebugLevel(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDebugLevel(out uint aaDebugLevel)
        {
			fixed (uint* aDebugLevel = &aaDebugLevel)
			{
				CpProxyLinnCoUkDebug2SyncDebugLevel(iHandle, aDebugLevel);
			}
        }

        public unsafe void BeginDebugLevel(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDebug2BeginDebugLevel(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDebugLevel(uint aAsyncHandle, out uint aaDebugLevel)
        {
			fixed (uint* aDebugLevel = &aaDebugLevel)
			{
				if (0 != CpProxyLinnCoUkDebug2EndDebugLevel(iHandle, aAsyncHandle, aDebugLevel))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncMemWrite(uint aaMemAddress, string aaMemData)
        {
			char* aMemData = (char*)Marshal.StringToHGlobalAnsi(aaMemData);
			uint aMemDataLen = (uint)aaMemData.Length;
			{
				CpProxyLinnCoUkDebug2SyncMemWrite(iHandle, aaMemAddress, aMemData, aMemDataLen);
			}
			Marshal.FreeHGlobal((IntPtr)aMemData);
        }

        public unsafe void BeginMemWrite(uint aaMemAddress, string aaMemData, CallbackAsyncComplete aCallback)
        {
			char* aMemData = (char*)Marshal.StringToHGlobalAnsi(aaMemData);
			uint aMemDataLen = (uint)aaMemData.Length;
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDebug2BeginMemWrite(iHandle, aaMemAddress, aMemData, aMemDataLen, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aMemData);
        }

        public unsafe void EndMemWrite(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkDebug2EndMemWrite(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkDebug2()
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
            CpProxyLinnCoUkDebug2Destroy(handle);
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

