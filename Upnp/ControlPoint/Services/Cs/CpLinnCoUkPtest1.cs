using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkPtest1 : ICpProxy, IDisposable
    {
        void SyncTestComPort(uint aaPort, out bool aaResult);
        void BeginTestComPort(uint aaPort, CpProxy.CallbackAsyncComplete aCallback);
        void EndTestComPort(IntPtr aAsyncHandle, out bool aaResult);
        void SyncLedsOn();
        void BeginLedsOn(CpProxy.CallbackAsyncComplete aCallback);
        void EndLedsOn(IntPtr aAsyncHandle);
        void SyncLedsOff();
        void BeginLedsOff(CpProxy.CallbackAsyncComplete aCallback);
        void EndLedsOff(IntPtr aAsyncHandle);

    }

    /// <summary>
    /// Proxy for the linn.co.uk:Ptest:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkPtest1 : CpProxy, IDisposable, ICpProxyLinnCoUkPtest1
    {
        [DllImport("CpLinnCoUkPtest1")]
        static extern IntPtr CpProxyLinnCoUkPtest1Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkPtest1")]
        static extern void CpProxyLinnCoUkPtest1Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe void CpProxyLinnCoUkPtest1SyncTestComPort(IntPtr aHandle, uint aaPort, uint* aaResult);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe void CpProxyLinnCoUkPtest1BeginTestComPort(IntPtr aHandle, uint aaPort, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe int CpProxyLinnCoUkPtest1EndTestComPort(IntPtr aHandle, IntPtr aAsync, uint* aaResult);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe void CpProxyLinnCoUkPtest1SyncLedsOn(IntPtr aHandle);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe void CpProxyLinnCoUkPtest1BeginLedsOn(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe int CpProxyLinnCoUkPtest1EndLedsOn(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe void CpProxyLinnCoUkPtest1SyncLedsOff(IntPtr aHandle);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe void CpProxyLinnCoUkPtest1BeginLedsOff(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkPtest1")]
        static extern unsafe int CpProxyLinnCoUkPtest1EndLedsOff(IntPtr aHandle, IntPtr aAsync);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkPtest1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkPtest1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaPort"></param>
        /// <param name="aaResult"></param>
        public unsafe void SyncTestComPort(uint aaPort, out bool aaResult)
        {
            uint aResult;
            {
                CpProxyLinnCoUkPtest1SyncTestComPort(iHandle, aaPort, &aResult);
            }
            aaResult = (aResult != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndTestComPort().</remarks>
        /// <param name="aaPort"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginTestComPort(uint aaPort, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPtest1BeginTestComPort(iHandle, aaPort, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaResult"></param>
        public unsafe void EndTestComPort(IntPtr aAsyncHandle, out bool aaResult)
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public unsafe void SyncLedsOn()
        {
            {
                CpProxyLinnCoUkPtest1SyncLedsOn(iHandle);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndLedsOn().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginLedsOn(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPtest1BeginLedsOn(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndLedsOn(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkPtest1EndLedsOn(iHandle, aAsyncHandle))
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
        public unsafe void SyncLedsOff()
        {
            {
                CpProxyLinnCoUkPtest1SyncLedsOff(iHandle);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndLedsOff().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginLedsOff(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkPtest1BeginLedsOff(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndLedsOff(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkPtest1EndLedsOff(iHandle, aAsyncHandle))
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

        ~CpProxyLinnCoUkPtest1()
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
                CpProxyLinnCoUkPtest1Destroy(iHandle);
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

