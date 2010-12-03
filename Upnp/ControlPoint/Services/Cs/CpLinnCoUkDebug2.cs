using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkDebug2 : ICpProxy, IDisposable
    {
        void SyncSetDebugLevel(uint aaDebugLevel);
        void BeginSetDebugLevel(uint aaDebugLevel, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDebugLevel(uint aAsyncHandle);
        void SyncDebugLevel(out uint aaDebugLevel);
        void BeginDebugLevel(CpProxy.CallbackAsyncComplete aCallback);
        void EndDebugLevel(uint aAsyncHandle, out uint aaDebugLevel);
        void SyncMemWrite(uint aaMemAddress, string aaMemData);
        void BeginMemWrite(uint aaMemAddress, string aaMemData, CpProxy.CallbackAsyncComplete aCallback);
        void EndMemWrite(uint aAsyncHandle);

    }

    /// <summary>
    /// Proxy for the linn.co.uk:Debug:2 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkDebug2 : CpProxy, IDisposable, ICpProxyLinnCoUkDebug2
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkDebug2(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkDebug2Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaDebugLevel"></param>
        public unsafe void SyncSetDebugLevel(uint aaDebugLevel)
        {
            {
                CpProxyLinnCoUkDebug2SyncSetDebugLevel(iHandle, aaDebugLevel);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetDebugLevel().</remarks>
        /// <param name="aaDebugLevel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetDebugLevel(uint aaDebugLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDebug2BeginSetDebugLevel(iHandle, aaDebugLevel, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetDebugLevel(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkDebug2EndSetDebugLevel(iHandle, aAsyncHandle))
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
        /// <param name="aaDebugLevel"></param>
        public unsafe void SyncDebugLevel(out uint aaDebugLevel)
        {
            fixed (uint* aDebugLevel = &aaDebugLevel)
            {
                CpProxyLinnCoUkDebug2SyncDebugLevel(iHandle, aDebugLevel);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDebugLevel().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDebugLevel(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDebug2BeginDebugLevel(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaDebugLevel"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaMemAddress"></param>
        /// <param name="aaMemData"></param>
        public unsafe void SyncMemWrite(uint aaMemAddress, string aaMemData)
        {
            char* aMemData = (char*)Marshal.StringToHGlobalAnsi(aaMemData);
            uint aMemDataLen = (uint)aaMemData.Length;
            {
                CpProxyLinnCoUkDebug2SyncMemWrite(iHandle, aaMemAddress, aMemData, aMemDataLen);
            }
            Marshal.FreeHGlobal((IntPtr)aMemData);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndMemWrite().</remarks>
        /// <param name="aaMemAddress"></param>
        /// <param name="aaMemData"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginMemWrite(uint aaMemAddress, string aaMemData, CallbackAsyncComplete aCallback)
        {
            char* aMemData = (char*)Marshal.StringToHGlobalAnsi(aaMemData);
            uint aMemDataLen = (uint)aaMemData.Length;
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkDebug2BeginMemWrite(iHandle, aaMemAddress, aMemData, aMemDataLen, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aMemData);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndMemWrite(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkDebug2EndMemWrite(iHandle, aAsyncHandle))
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

        ~CpProxyLinnCoUkDebug2()
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
                CpProxyLinnCoUkDebug2Destroy(iHandle);
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

