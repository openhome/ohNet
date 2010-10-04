using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyZappOrgTestLights1 : CpProxy, IDisposable
    {
        [DllImport("CpZappOrgTestLights1")]
        static extern uint CpProxyZappOrgTestLights1Create(uint aDeviceHandle);
        [DllImport("CpZappOrgTestLights1")]
        static extern void CpProxyZappOrgTestLights1Destroy(uint aHandle);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1SyncGetCount(uint aHandle, uint* aCount);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1BeginGetCount(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe int CpProxyZappOrgTestLights1EndGetCount(uint aHandle, uint aAsync, uint* aCount);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1SyncGetRoom(uint aHandle, uint aIndex, char** aRoomName);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1BeginGetRoom(uint aHandle, uint aIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe int CpProxyZappOrgTestLights1EndGetRoom(uint aHandle, uint aAsync, char** aRoomName);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1SyncGetName(uint aHandle, uint aIndex, char** aFriendlyName);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1BeginGetName(uint aHandle, uint aIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe int CpProxyZappOrgTestLights1EndGetName(uint aHandle, uint aAsync, char** aFriendlyName);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1SyncGetPosition(uint aHandle, uint aIndex, uint* aX, uint* aY, uint* aZ);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1BeginGetPosition(uint aHandle, uint aIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe int CpProxyZappOrgTestLights1EndGetPosition(uint aHandle, uint aAsync, uint* aX, uint* aY, uint* aZ);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1SyncSetColor(uint aHandle, uint aIndex, uint aColor);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1BeginSetColor(uint aHandle, uint aIndex, uint aColor, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe int CpProxyZappOrgTestLights1EndSetColor(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1SyncGetColor(uint aHandle, uint aIndex, uint* aColor);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1BeginGetColor(uint aHandle, uint aIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe int CpProxyZappOrgTestLights1EndGetColor(uint aHandle, uint aAsync, uint* aColor);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1SyncGetColorComponents(uint aHandle, uint aColor, uint* aBrightness, uint* aRed, uint* aGreen, uint* aBlue);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1BeginGetColorComponents(uint aHandle, uint aColor, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe int CpProxyZappOrgTestLights1EndGetColorComponents(uint aHandle, uint aAsync, uint* aBrightness, uint* aRed, uint* aGreen, uint* aBlue);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;

        public CpProxyZappOrgTestLights1(CpDevice aDevice)
        {
            iHandle = CpProxyZappOrgTestLights1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncGetCount(out uint aCount)
        {
			fixed (uint* count = &aCount)
			{
				CpProxyZappOrgTestLights1SyncGetCount(iHandle, count);
			}
        }

        public unsafe void BeginGetCount(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestLights1BeginGetCount(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetCount(uint aAsyncHandle, out uint aCount)
        {
			fixed (uint* count = &aCount)
			{
				if (0 != CpProxyZappOrgTestLights1EndGetCount(iHandle, aAsyncHandle, count))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetRoom(uint aIndex, out string aRoomName)
        {
			char* roomName;
			{
				CpProxyZappOrgTestLights1SyncGetRoom(iHandle, aIndex, &roomName);
			}
            aRoomName = Marshal.PtrToStringAnsi((IntPtr)roomName);
            ZappFree(roomName);
        }

        public unsafe void BeginGetRoom(uint aIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestLights1BeginGetRoom(iHandle, aIndex, iActionComplete, ptr);
        }

        public unsafe void EndGetRoom(uint aAsyncHandle, out string aRoomName)
        {
			char* roomName;
			{
				if (0 != CpProxyZappOrgTestLights1EndGetRoom(iHandle, aAsyncHandle, &roomName))
				{
					throw(new ProxyError());
				}
			}
            aRoomName = Marshal.PtrToStringAnsi((IntPtr)roomName);
            ZappFree(roomName);
        }

        public unsafe void SyncGetName(uint aIndex, out string aFriendlyName)
        {
			char* friendlyName;
			{
				CpProxyZappOrgTestLights1SyncGetName(iHandle, aIndex, &friendlyName);
			}
            aFriendlyName = Marshal.PtrToStringAnsi((IntPtr)friendlyName);
            ZappFree(friendlyName);
        }

        public unsafe void BeginGetName(uint aIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestLights1BeginGetName(iHandle, aIndex, iActionComplete, ptr);
        }

        public unsafe void EndGetName(uint aAsyncHandle, out string aFriendlyName)
        {
			char* friendlyName;
			{
				if (0 != CpProxyZappOrgTestLights1EndGetName(iHandle, aAsyncHandle, &friendlyName))
				{
					throw(new ProxyError());
				}
			}
            aFriendlyName = Marshal.PtrToStringAnsi((IntPtr)friendlyName);
            ZappFree(friendlyName);
        }

        public unsafe void SyncGetPosition(uint aIndex, out uint aX, out uint aY, out uint aZ)
        {
			fixed (uint* x = &aX)
			fixed (uint* y = &aY)
			fixed (uint* z = &aZ)
			{
				CpProxyZappOrgTestLights1SyncGetPosition(iHandle, aIndex, x, y, z);
			}
        }

        public unsafe void BeginGetPosition(uint aIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestLights1BeginGetPosition(iHandle, aIndex, iActionComplete, ptr);
        }

        public unsafe void EndGetPosition(uint aAsyncHandle, out uint aX, out uint aY, out uint aZ)
        {
			fixed (uint* x = &aX)
			fixed (uint* y = &aY)
			fixed (uint* z = &aZ)
			{
				if (0 != CpProxyZappOrgTestLights1EndGetPosition(iHandle, aAsyncHandle, x, y, z))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetColor(uint aIndex, uint aColor)
        {
			{
				CpProxyZappOrgTestLights1SyncSetColor(iHandle, aIndex, aColor);
			}
        }

        public unsafe void BeginSetColor(uint aIndex, uint aColor, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestLights1BeginSetColor(iHandle, aIndex, aColor, iActionComplete, ptr);
        }

        public unsafe void EndSetColor(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestLights1EndSetColor(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetColor(uint aIndex, out uint aColor)
        {
			fixed (uint* color = &aColor)
			{
				CpProxyZappOrgTestLights1SyncGetColor(iHandle, aIndex, color);
			}
        }

        public unsafe void BeginGetColor(uint aIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestLights1BeginGetColor(iHandle, aIndex, iActionComplete, ptr);
        }

        public unsafe void EndGetColor(uint aAsyncHandle, out uint aColor)
        {
			fixed (uint* color = &aColor)
			{
				if (0 != CpProxyZappOrgTestLights1EndGetColor(iHandle, aAsyncHandle, color))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetColorComponents(uint aColor, out uint aBrightness, out uint aRed, out uint aGreen, out uint aBlue)
        {
			fixed (uint* brightness = &aBrightness)
			fixed (uint* red = &aRed)
			fixed (uint* green = &aGreen)
			fixed (uint* blue = &aBlue)
			{
				CpProxyZappOrgTestLights1SyncGetColorComponents(iHandle, aColor, brightness, red, green, blue);
			}
        }

        public unsafe void BeginGetColorComponents(uint aColor, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestLights1BeginGetColorComponents(iHandle, aColor, iActionComplete, ptr);
        }

        public unsafe void EndGetColorComponents(uint aAsyncHandle, out uint aBrightness, out uint aRed, out uint aGreen, out uint aBlue)
        {
			fixed (uint* brightness = &aBrightness)
			fixed (uint* red = &aRed)
			fixed (uint* green = &aGreen)
			fixed (uint* blue = &aBlue)
			{
				if (0 != CpProxyZappOrgTestLights1EndGetColorComponents(iHandle, aAsyncHandle, brightness, red, green, blue))
				{
					throw(new ProxyError());
				}
			}
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyZappOrgTestLights1()
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
            CpProxyZappOrgTestLights1Destroy(handle);
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

