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

    /// <summary>
    /// Proxy for the linn.co.uk:MediaTime:1 UPnP service
    /// </summary>
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkMediaTime1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkMediaTime1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSeconds"></param>
        public unsafe void SyncSeconds(out uint aaSeconds)
        {
            fixed (uint* aSeconds = &aaSeconds)
            {
                CpProxyLinnCoUkMediaTime1SyncSeconds(iHandle, aSeconds);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeconds().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSeconds(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkMediaTime1BeginSeconds(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSeconds"></param>
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

        /// <summary>
        /// Set a delegate to be run when the Seconds state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkMediaTime1 instance will not overlap.</remarks>
        /// <param name="aSecondsChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Query the value of the Seconds property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aSeconds">Will be set to the value of the property</param>
        public unsafe void PropertySeconds(out uint aSeconds)
        {
            fixed (uint* seconds = &aSeconds)
            {
                CpProxyLinnCoUkMediaTime1PropertySeconds(iHandle, seconds);
            }
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
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

