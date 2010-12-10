using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyZappOrgTestLights1 : ICpProxy, IDisposable
    {
        void SyncGetCount(out uint aCount);
        void BeginGetCount(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetCount(IntPtr aAsyncHandle, out uint aCount);
        void SyncGetRoom(uint aIndex, out string aRoomName);
        void BeginGetRoom(uint aIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRoom(IntPtr aAsyncHandle, out string aRoomName);
        void SyncGetName(uint aIndex, out string aFriendlyName);
        void BeginGetName(uint aIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetName(IntPtr aAsyncHandle, out string aFriendlyName);
        void SyncGetPosition(uint aIndex, out uint aX, out uint aY, out uint aZ);
        void BeginGetPosition(uint aIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetPosition(IntPtr aAsyncHandle, out uint aX, out uint aY, out uint aZ);
        void SyncSetColor(uint aIndex, uint aColor);
        void BeginSetColor(uint aIndex, uint aColor, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetColor(IntPtr aAsyncHandle);
        void SyncGetColor(uint aIndex, out uint aColor);
        void BeginGetColor(uint aIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetColor(IntPtr aAsyncHandle, out uint aColor);
        void SyncGetColorComponents(uint aColor, out uint aBrightness, out uint aRed, out uint aGreen, out uint aBlue);
        void BeginGetColorComponents(uint aColor, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetColorComponents(IntPtr aAsyncHandle, out uint aBrightness, out uint aRed, out uint aGreen, out uint aBlue);

    }

    /// <summary>
    /// Proxy for the zapp.org:TestLights:1 UPnP service
    /// </summary>
    public class CpProxyZappOrgTestLights1 : CpProxy, IDisposable, ICpProxyZappOrgTestLights1
    {
        [DllImport("CpZappOrgTestLights1")]
        static extern IntPtr CpProxyZappOrgTestLights1Create(IntPtr aDeviceHandle);
        [DllImport("CpZappOrgTestLights1")]
        static extern void CpProxyZappOrgTestLights1Destroy(IntPtr aHandle);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1SyncGetCount(IntPtr aHandle, uint* aCount);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1BeginGetCount(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe int CpProxyZappOrgTestLights1EndGetCount(IntPtr aHandle, IntPtr aAsync, uint* aCount);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1SyncGetRoom(IntPtr aHandle, uint aIndex, char** aRoomName);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1BeginGetRoom(IntPtr aHandle, uint aIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe int CpProxyZappOrgTestLights1EndGetRoom(IntPtr aHandle, IntPtr aAsync, char** aRoomName);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1SyncGetName(IntPtr aHandle, uint aIndex, char** aFriendlyName);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1BeginGetName(IntPtr aHandle, uint aIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe int CpProxyZappOrgTestLights1EndGetName(IntPtr aHandle, IntPtr aAsync, char** aFriendlyName);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1SyncGetPosition(IntPtr aHandle, uint aIndex, uint* aX, uint* aY, uint* aZ);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1BeginGetPosition(IntPtr aHandle, uint aIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe int CpProxyZappOrgTestLights1EndGetPosition(IntPtr aHandle, IntPtr aAsync, uint* aX, uint* aY, uint* aZ);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1SyncSetColor(IntPtr aHandle, uint aIndex, uint aColor);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1BeginSetColor(IntPtr aHandle, uint aIndex, uint aColor, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe int CpProxyZappOrgTestLights1EndSetColor(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1SyncGetColor(IntPtr aHandle, uint aIndex, uint* aColor);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1BeginGetColor(IntPtr aHandle, uint aIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe int CpProxyZappOrgTestLights1EndGetColor(IntPtr aHandle, IntPtr aAsync, uint* aColor);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1SyncGetColorComponents(IntPtr aHandle, uint aColor, uint* aBrightness, uint* aRed, uint* aGreen, uint* aBlue);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe void CpProxyZappOrgTestLights1BeginGetColorComponents(IntPtr aHandle, uint aColor, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestLights1")]
        static extern unsafe int CpProxyZappOrgTestLights1EndGetColorComponents(IntPtr aHandle, IntPtr aAsync, uint* aBrightness, uint* aRed, uint* aGreen, uint* aBlue);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyZappOrgTestLights1(CpDevice aDevice)
        {
            iHandle = CpProxyZappOrgTestLights1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aCount"></param>
        public unsafe void SyncGetCount(out uint aCount)
        {
            fixed (uint* count = &aCount)
            {
                CpProxyZappOrgTestLights1SyncGetCount(iHandle, count);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetCount().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetCount(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestLights1BeginGetCount(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCount"></param>
        public unsafe void EndGetCount(IntPtr aAsyncHandle, out uint aCount)
        {
            fixed (uint* count = &aCount)
            {
                if (0 != CpProxyZappOrgTestLights1EndGetCount(iHandle, aAsyncHandle, count))
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
        /// <param name="aIndex"></param>
        /// <param name="aRoomName"></param>
        public unsafe void SyncGetRoom(uint aIndex, out string aRoomName)
        {
            char* roomName;
            {
                CpProxyZappOrgTestLights1SyncGetRoom(iHandle, aIndex, &roomName);
            }
            aRoomName = Marshal.PtrToStringAnsi((IntPtr)roomName);
            ZappFree(roomName);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRoom().</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetRoom(uint aIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestLights1BeginGetRoom(iHandle, aIndex, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRoomName"></param>
        public unsafe void EndGetRoom(IntPtr aAsyncHandle, out string aRoomName)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aFriendlyName"></param>
        public unsafe void SyncGetName(uint aIndex, out string aFriendlyName)
        {
            char* friendlyName;
            {
                CpProxyZappOrgTestLights1SyncGetName(iHandle, aIndex, &friendlyName);
            }
            aFriendlyName = Marshal.PtrToStringAnsi((IntPtr)friendlyName);
            ZappFree(friendlyName);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetName().</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetName(uint aIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestLights1BeginGetName(iHandle, aIndex, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aFriendlyName"></param>
        public unsafe void EndGetName(IntPtr aAsyncHandle, out string aFriendlyName)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aX"></param>
        /// <param name="aY"></param>
        /// <param name="aZ"></param>
        public unsafe void SyncGetPosition(uint aIndex, out uint aX, out uint aY, out uint aZ)
        {
            fixed (uint* x = &aX)
            fixed (uint* y = &aY)
            fixed (uint* z = &aZ)
            {
                CpProxyZappOrgTestLights1SyncGetPosition(iHandle, aIndex, x, y, z);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetPosition().</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetPosition(uint aIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestLights1BeginGetPosition(iHandle, aIndex, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aX"></param>
        /// <param name="aY"></param>
        /// <param name="aZ"></param>
        public unsafe void EndGetPosition(IntPtr aAsyncHandle, out uint aX, out uint aY, out uint aZ)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aColor"></param>
        public unsafe void SyncSetColor(uint aIndex, uint aColor)
        {
            {
                CpProxyZappOrgTestLights1SyncSetColor(iHandle, aIndex, aColor);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetColor().</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aColor"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetColor(uint aIndex, uint aColor, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestLights1BeginSetColor(iHandle, aIndex, aColor, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetColor(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyZappOrgTestLights1EndSetColor(iHandle, aAsyncHandle))
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
        /// <param name="aIndex"></param>
        /// <param name="aColor"></param>
        public unsafe void SyncGetColor(uint aIndex, out uint aColor)
        {
            fixed (uint* color = &aColor)
            {
                CpProxyZappOrgTestLights1SyncGetColor(iHandle, aIndex, color);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetColor().</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetColor(uint aIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestLights1BeginGetColor(iHandle, aIndex, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aColor"></param>
        public unsafe void EndGetColor(IntPtr aAsyncHandle, out uint aColor)
        {
            fixed (uint* color = &aColor)
            {
                if (0 != CpProxyZappOrgTestLights1EndGetColor(iHandle, aAsyncHandle, color))
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
        /// <param name="aColor"></param>
        /// <param name="aBrightness"></param>
        /// <param name="aRed"></param>
        /// <param name="aGreen"></param>
        /// <param name="aBlue"></param>
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

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetColorComponents().</remarks>
        /// <param name="aColor"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetColorComponents(uint aColor, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestLights1BeginGetColorComponents(iHandle, aColor, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aBrightness"></param>
        /// <param name="aRed"></param>
        /// <param name="aGreen"></param>
        /// <param name="aBlue"></param>
        public unsafe void EndGetColorComponents(IntPtr aAsyncHandle, out uint aBrightness, out uint aRed, out uint aGreen, out uint aBlue)
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

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
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
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                CpProxyZappOrgTestLights1Destroy(iHandle);
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

