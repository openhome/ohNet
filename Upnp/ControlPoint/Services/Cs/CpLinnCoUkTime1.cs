using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkTime1 : ICpProxy, IDisposable
    {
        void SyncTime(out uint aaTrackCount, out uint aaDuration, out uint aaSeconds);
        void BeginTime(CpProxy.CallbackAsyncComplete aCallback);
        void EndTime(uint aAsyncHandle, out uint aaTrackCount, out uint aaDuration, out uint aaSeconds);

        void SetPropertyTrackCountChanged(CpProxy.CallbackPropertyChanged aTrackCountChanged);
        void PropertyTrackCount(out uint aTrackCount);
        void SetPropertyDurationChanged(CpProxy.CallbackPropertyChanged aDurationChanged);
        void PropertyDuration(out uint aDuration);
        void SetPropertySecondsChanged(CpProxy.CallbackPropertyChanged aSecondsChanged);
        void PropertySeconds(out uint aSeconds);
    }

    /// <summary>
    /// Proxy for the linn.co.uk:Time:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkTime1 : CpProxy, IDisposable, ICpProxyLinnCoUkTime1
    {
        [DllImport("CpLinnCoUkTime1")]
        static extern uint CpProxyLinnCoUkTime1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkTime1")]
        static extern void CpProxyLinnCoUkTime1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkTime1")]
        static extern unsafe void CpProxyLinnCoUkTime1SyncTime(uint aHandle, uint* aaTrackCount, uint* aaDuration, uint* aaSeconds);
        [DllImport("CpLinnCoUkTime1")]
        static extern unsafe void CpProxyLinnCoUkTime1BeginTime(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkTime1")]
        static extern unsafe int CpProxyLinnCoUkTime1EndTime(uint aHandle, uint aAsync, uint* aaTrackCount, uint* aaDuration, uint* aaSeconds);
        [DllImport("CpLinnCoUkTime1")]
        static extern void CpProxyLinnCoUkTime1SetPropertyTrackCountChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkTime1")]
        static extern void CpProxyLinnCoUkTime1SetPropertyDurationChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkTime1")]
        static extern void CpProxyLinnCoUkTime1SetPropertySecondsChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkTime1")]
        static extern unsafe void CpProxyLinnCoUkTime1PropertyTrackCount(uint aHandle, uint* aTrackCount);
        [DllImport("CpLinnCoUkTime1")]
        static extern unsafe void CpProxyLinnCoUkTime1PropertyDuration(uint aHandle, uint* aDuration);
        [DllImport("CpLinnCoUkTime1")]
        static extern unsafe void CpProxyLinnCoUkTime1PropertySeconds(uint aHandle, uint* aSeconds);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iTrackCountChanged;
        private CallbackPropertyChanged iDurationChanged;
        private CallbackPropertyChanged iSecondsChanged;
        private Callback iCallbackTrackCountChanged;
        private Callback iCallbackDurationChanged;
        private Callback iCallbackSecondsChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkTime1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkTime1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaTrackCount"></param>
        /// <param name="aaDuration"></param>
        /// <param name="aaSeconds"></param>
        public unsafe void SyncTime(out uint aaTrackCount, out uint aaDuration, out uint aaSeconds)
        {
            fixed (uint* aTrackCount = &aaTrackCount)
            fixed (uint* aDuration = &aaDuration)
            fixed (uint* aSeconds = &aaSeconds)
            {
                CpProxyLinnCoUkTime1SyncTime(iHandle, aTrackCount, aDuration, aSeconds);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndTime().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginTime(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkTime1BeginTime(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaTrackCount"></param>
        /// <param name="aaDuration"></param>
        /// <param name="aaSeconds"></param>
        public unsafe void EndTime(uint aAsyncHandle, out uint aaTrackCount, out uint aaDuration, out uint aaSeconds)
        {
            fixed (uint* aTrackCount = &aaTrackCount)
            fixed (uint* aDuration = &aaDuration)
            fixed (uint* aSeconds = &aaSeconds)
            {
                if (0 != CpProxyLinnCoUkTime1EndTime(iHandle, aAsyncHandle, aTrackCount, aDuration, aSeconds))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the TrackCount state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkTime1 instance will not overlap.</remarks>
        /// <param name="aTrackCountChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTrackCountChanged(CallbackPropertyChanged aTrackCountChanged)
        {
            iTrackCountChanged = aTrackCountChanged;
            iCallbackTrackCountChanged = new Callback(PropertyTrackCountChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkTime1SetPropertyTrackCountChanged(iHandle, iCallbackTrackCountChanged, ptr);
        }

        private void PropertyTrackCountChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkTime1 self = (CpProxyLinnCoUkTime1)gch.Target;
            self.iTrackCountChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the Duration state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkTime1 instance will not overlap.</remarks>
        /// <param name="aDurationChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDurationChanged(CallbackPropertyChanged aDurationChanged)
        {
            iDurationChanged = aDurationChanged;
            iCallbackDurationChanged = new Callback(PropertyDurationChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkTime1SetPropertyDurationChanged(iHandle, iCallbackDurationChanged, ptr);
        }

        private void PropertyDurationChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkTime1 self = (CpProxyLinnCoUkTime1)gch.Target;
            self.iDurationChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the Seconds state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkTime1 instance will not overlap.</remarks>
        /// <param name="aSecondsChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySecondsChanged(CallbackPropertyChanged aSecondsChanged)
        {
            iSecondsChanged = aSecondsChanged;
            iCallbackSecondsChanged = new Callback(PropertySecondsChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkTime1SetPropertySecondsChanged(iHandle, iCallbackSecondsChanged, ptr);
        }

        private void PropertySecondsChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkTime1 self = (CpProxyLinnCoUkTime1)gch.Target;
            self.iSecondsChanged();
        }

        /// <summary>
        /// Query the value of the TrackCount property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTrackCount">Will be set to the value of the property</param>
        public unsafe void PropertyTrackCount(out uint aTrackCount)
        {
            fixed (uint* trackCount = &aTrackCount)
            {
                CpProxyLinnCoUkTime1PropertyTrackCount(iHandle, trackCount);
            }
        }

        /// <summary>
        /// Query the value of the Duration property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDuration">Will be set to the value of the property</param>
        public unsafe void PropertyDuration(out uint aDuration)
        {
            fixed (uint* duration = &aDuration)
            {
                CpProxyLinnCoUkTime1PropertyDuration(iHandle, duration);
            }
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
                CpProxyLinnCoUkTime1PropertySeconds(iHandle, seconds);
            }
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkTime1()
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
                CpProxyLinnCoUkTime1Destroy(iHandle);
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

