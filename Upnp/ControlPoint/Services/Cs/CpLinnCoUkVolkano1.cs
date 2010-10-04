using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkVolkano1 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkVolkano1")]
        static extern uint CpProxyLinnCoUkVolkano1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern void CpProxyLinnCoUkVolkano1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncReboot(uint aHandle);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginReboot(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndReboot(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncBootMode(uint aHandle, char** aaMode);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginBootMode(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndBootMode(uint aHandle, uint aAsync, char** aaMode);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncSetBootMode(uint aHandle, char* aaMode);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginSetBootMode(uint aHandle, char* aaMode, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndSetBootMode(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncBspType(uint aHandle, char** aaBspType);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginBspType(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndBspType(uint aHandle, uint aAsync, char** aaBspType);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncUglyName(uint aHandle, char** aaUglyName);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginUglyName(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndUglyName(uint aHandle, uint aAsync, char** aaUglyName);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncMacAddress(uint aHandle, char** aaMacAddress);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginMacAddress(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndMacAddress(uint aHandle, uint aAsync, char** aaMacAddress);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncProductId(uint aHandle, char** aaProductNumber);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginProductId(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndProductId(uint aHandle, uint aAsync, char** aaProductNumber);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncBoardId(uint aHandle, uint aaIndex, char** aaBoardNumber);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginBoardId(uint aHandle, uint aaIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndBoardId(uint aHandle, uint aAsync, char** aaBoardNumber);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncBoardType(uint aHandle, uint aaIndex, char** aaBoardNumber);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginBoardType(uint aHandle, uint aaIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndBoardType(uint aHandle, uint aAsync, char** aaBoardNumber);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncMaxBoards(uint aHandle, uint* aaMaxBoards);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginMaxBoards(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndMaxBoards(uint aHandle, uint aAsync, uint* aaMaxBoards);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncSoftwareVersion(uint aHandle, char** aaSoftwareVersion);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginSoftwareVersion(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndSoftwareVersion(uint aHandle, uint aAsync, char** aaSoftwareVersion);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;

        public CpProxyLinnCoUkVolkano1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkVolkano1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncReboot()
        {
			{
				CpProxyLinnCoUkVolkano1SyncReboot(iHandle);
			}
        }

        public unsafe void BeginReboot(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginReboot(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndReboot(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkVolkano1EndReboot(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncBootMode(out string aaMode)
        {
			char* aMode;
			{
				CpProxyLinnCoUkVolkano1SyncBootMode(iHandle, &aMode);
			}
            aaMode = Marshal.PtrToStringAnsi((IntPtr)aMode);
            ZappFree(aMode);
        }

        public unsafe void BeginBootMode(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginBootMode(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndBootMode(uint aAsyncHandle, out string aaMode)
        {
			char* aMode;
			{
				if (0 != CpProxyLinnCoUkVolkano1EndBootMode(iHandle, aAsyncHandle, &aMode))
				{
					throw(new ProxyError());
				}
			}
            aaMode = Marshal.PtrToStringAnsi((IntPtr)aMode);
            ZappFree(aMode);
        }

        public unsafe void SyncSetBootMode(string aaMode)
        {
			char* aMode = (char*)Marshal.StringToHGlobalAnsi(aaMode);
			{
				CpProxyLinnCoUkVolkano1SyncSetBootMode(iHandle, aMode);
			}
			Marshal.FreeHGlobal((IntPtr)aMode);
        }

        public unsafe void BeginSetBootMode(string aaMode, CallbackAsyncComplete aCallback)
        {
			char* aMode = (char*)Marshal.StringToHGlobalAnsi(aaMode);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginSetBootMode(iHandle, aMode, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aMode);
        }

        public unsafe void EndSetBootMode(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkVolkano1EndSetBootMode(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncBspType(out string aaBspType)
        {
			char* aBspType;
			{
				CpProxyLinnCoUkVolkano1SyncBspType(iHandle, &aBspType);
			}
            aaBspType = Marshal.PtrToStringAnsi((IntPtr)aBspType);
            ZappFree(aBspType);
        }

        public unsafe void BeginBspType(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginBspType(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndBspType(uint aAsyncHandle, out string aaBspType)
        {
			char* aBspType;
			{
				if (0 != CpProxyLinnCoUkVolkano1EndBspType(iHandle, aAsyncHandle, &aBspType))
				{
					throw(new ProxyError());
				}
			}
            aaBspType = Marshal.PtrToStringAnsi((IntPtr)aBspType);
            ZappFree(aBspType);
        }

        public unsafe void SyncUglyName(out string aaUglyName)
        {
			char* aUglyName;
			{
				CpProxyLinnCoUkVolkano1SyncUglyName(iHandle, &aUglyName);
			}
            aaUglyName = Marshal.PtrToStringAnsi((IntPtr)aUglyName);
            ZappFree(aUglyName);
        }

        public unsafe void BeginUglyName(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginUglyName(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndUglyName(uint aAsyncHandle, out string aaUglyName)
        {
			char* aUglyName;
			{
				if (0 != CpProxyLinnCoUkVolkano1EndUglyName(iHandle, aAsyncHandle, &aUglyName))
				{
					throw(new ProxyError());
				}
			}
            aaUglyName = Marshal.PtrToStringAnsi((IntPtr)aUglyName);
            ZappFree(aUglyName);
        }

        public unsafe void SyncMacAddress(out string aaMacAddress)
        {
			char* aMacAddress;
			{
				CpProxyLinnCoUkVolkano1SyncMacAddress(iHandle, &aMacAddress);
			}
            aaMacAddress = Marshal.PtrToStringAnsi((IntPtr)aMacAddress);
            ZappFree(aMacAddress);
        }

        public unsafe void BeginMacAddress(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginMacAddress(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndMacAddress(uint aAsyncHandle, out string aaMacAddress)
        {
			char* aMacAddress;
			{
				if (0 != CpProxyLinnCoUkVolkano1EndMacAddress(iHandle, aAsyncHandle, &aMacAddress))
				{
					throw(new ProxyError());
				}
			}
            aaMacAddress = Marshal.PtrToStringAnsi((IntPtr)aMacAddress);
            ZappFree(aMacAddress);
        }

        public unsafe void SyncProductId(out string aaProductNumber)
        {
			char* aProductNumber;
			{
				CpProxyLinnCoUkVolkano1SyncProductId(iHandle, &aProductNumber);
			}
            aaProductNumber = Marshal.PtrToStringAnsi((IntPtr)aProductNumber);
            ZappFree(aProductNumber);
        }

        public unsafe void BeginProductId(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginProductId(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndProductId(uint aAsyncHandle, out string aaProductNumber)
        {
			char* aProductNumber;
			{
				if (0 != CpProxyLinnCoUkVolkano1EndProductId(iHandle, aAsyncHandle, &aProductNumber))
				{
					throw(new ProxyError());
				}
			}
            aaProductNumber = Marshal.PtrToStringAnsi((IntPtr)aProductNumber);
            ZappFree(aProductNumber);
        }

        public unsafe void SyncBoardId(uint aaIndex, out string aaBoardNumber)
        {
			char* aBoardNumber;
			{
				CpProxyLinnCoUkVolkano1SyncBoardId(iHandle, aaIndex, &aBoardNumber);
			}
            aaBoardNumber = Marshal.PtrToStringAnsi((IntPtr)aBoardNumber);
            ZappFree(aBoardNumber);
        }

        public unsafe void BeginBoardId(uint aaIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginBoardId(iHandle, aaIndex, iActionComplete, ptr);
        }

        public unsafe void EndBoardId(uint aAsyncHandle, out string aaBoardNumber)
        {
			char* aBoardNumber;
			{
				if (0 != CpProxyLinnCoUkVolkano1EndBoardId(iHandle, aAsyncHandle, &aBoardNumber))
				{
					throw(new ProxyError());
				}
			}
            aaBoardNumber = Marshal.PtrToStringAnsi((IntPtr)aBoardNumber);
            ZappFree(aBoardNumber);
        }

        public unsafe void SyncBoardType(uint aaIndex, out string aaBoardNumber)
        {
			char* aBoardNumber;
			{
				CpProxyLinnCoUkVolkano1SyncBoardType(iHandle, aaIndex, &aBoardNumber);
			}
            aaBoardNumber = Marshal.PtrToStringAnsi((IntPtr)aBoardNumber);
            ZappFree(aBoardNumber);
        }

        public unsafe void BeginBoardType(uint aaIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginBoardType(iHandle, aaIndex, iActionComplete, ptr);
        }

        public unsafe void EndBoardType(uint aAsyncHandle, out string aaBoardNumber)
        {
			char* aBoardNumber;
			{
				if (0 != CpProxyLinnCoUkVolkano1EndBoardType(iHandle, aAsyncHandle, &aBoardNumber))
				{
					throw(new ProxyError());
				}
			}
            aaBoardNumber = Marshal.PtrToStringAnsi((IntPtr)aBoardNumber);
            ZappFree(aBoardNumber);
        }

        public unsafe void SyncMaxBoards(out uint aaMaxBoards)
        {
			fixed (uint* aMaxBoards = &aaMaxBoards)
			{
				CpProxyLinnCoUkVolkano1SyncMaxBoards(iHandle, aMaxBoards);
			}
        }

        public unsafe void BeginMaxBoards(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginMaxBoards(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndMaxBoards(uint aAsyncHandle, out uint aaMaxBoards)
        {
			fixed (uint* aMaxBoards = &aaMaxBoards)
			{
				if (0 != CpProxyLinnCoUkVolkano1EndMaxBoards(iHandle, aAsyncHandle, aMaxBoards))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSoftwareVersion(out string aaSoftwareVersion)
        {
			char* aSoftwareVersion;
			{
				CpProxyLinnCoUkVolkano1SyncSoftwareVersion(iHandle, &aSoftwareVersion);
			}
            aaSoftwareVersion = Marshal.PtrToStringAnsi((IntPtr)aSoftwareVersion);
            ZappFree(aSoftwareVersion);
        }

        public unsafe void BeginSoftwareVersion(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginSoftwareVersion(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndSoftwareVersion(uint aAsyncHandle, out string aaSoftwareVersion)
        {
			char* aSoftwareVersion;
			{
				if (0 != CpProxyLinnCoUkVolkano1EndSoftwareVersion(iHandle, aAsyncHandle, &aSoftwareVersion))
				{
					throw(new ProxyError());
				}
			}
            aaSoftwareVersion = Marshal.PtrToStringAnsi((IntPtr)aSoftwareVersion);
            ZappFree(aSoftwareVersion);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkVolkano1()
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
            CpProxyLinnCoUkVolkano1Destroy(handle);
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

