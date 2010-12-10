using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyZappOrgTestWidget1 : ICpProxy, IDisposable
    {
        void SyncSetReadWriteRegister(uint aRegisterIndex, uint aRegisterValue);
        void BeginSetReadWriteRegister(uint aRegisterIndex, uint aRegisterValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetReadWriteRegister(IntPtr aAsyncHandle);
        void SyncGetWidgetClass(out uint aWidgetClass);
        void BeginGetWidgetClass(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetWidgetClass(IntPtr aAsyncHandle, out uint aWidgetClass);

        void SetPropertyReadWriteRegister0Changed(CpProxy.CallbackPropertyChanged aReadWriteRegister0Changed);
        void PropertyReadWriteRegister0(out uint aReadWriteRegister0);
        void SetPropertyReadWriteRegister1Changed(CpProxy.CallbackPropertyChanged aReadWriteRegister1Changed);
        void PropertyReadWriteRegister1(out uint aReadWriteRegister1);
        void SetPropertyReadWriteRegister2Changed(CpProxy.CallbackPropertyChanged aReadWriteRegister2Changed);
        void PropertyReadWriteRegister2(out uint aReadWriteRegister2);
        void SetPropertyReadWriteRegister3Changed(CpProxy.CallbackPropertyChanged aReadWriteRegister3Changed);
        void PropertyReadWriteRegister3(out uint aReadWriteRegister3);
        void SetPropertyReadOnlyRegister4Changed(CpProxy.CallbackPropertyChanged aReadOnlyRegister4Changed);
        void PropertyReadOnlyRegister4(out uint aReadOnlyRegister4);
        void SetPropertyReadOnlyRegister5Changed(CpProxy.CallbackPropertyChanged aReadOnlyRegister5Changed);
        void PropertyReadOnlyRegister5(out uint aReadOnlyRegister5);
        void SetPropertyReadOnlyRegister6Changed(CpProxy.CallbackPropertyChanged aReadOnlyRegister6Changed);
        void PropertyReadOnlyRegister6(out uint aReadOnlyRegister6);
        void SetPropertyReadOnlyRegister7Changed(CpProxy.CallbackPropertyChanged aReadOnlyRegister7Changed);
        void PropertyReadOnlyRegister7(out uint aReadOnlyRegister7);
    }

    /// <summary>
    /// Proxy for the zapp.org:TestWidget:1 UPnP service
    /// </summary>
    public class CpProxyZappOrgTestWidget1 : CpProxy, IDisposable, ICpProxyZappOrgTestWidget1
    {
        [DllImport("CpZappOrgTestWidget1")]
        static extern IntPtr CpProxyZappOrgTestWidget1Create(IntPtr aDeviceHandle);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1Destroy(IntPtr aHandle);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1SyncSetReadWriteRegister(IntPtr aHandle, uint aRegisterIndex, uint aRegisterValue);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1BeginSetReadWriteRegister(IntPtr aHandle, uint aRegisterIndex, uint aRegisterValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe int CpProxyZappOrgTestWidget1EndSetReadWriteRegister(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1SyncGetWidgetClass(IntPtr aHandle, uint* aWidgetClass);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1BeginGetWidgetClass(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe int CpProxyZappOrgTestWidget1EndGetWidgetClass(IntPtr aHandle, IntPtr aAsync, uint* aWidgetClass);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister0Changed(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister1Changed(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister2Changed(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister3Changed(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister4Changed(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister5Changed(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister6Changed(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister7Changed(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadWriteRegister0(IntPtr aHandle, uint* aReadWriteRegister0);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadWriteRegister1(IntPtr aHandle, uint* aReadWriteRegister1);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadWriteRegister2(IntPtr aHandle, uint* aReadWriteRegister2);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadWriteRegister3(IntPtr aHandle, uint* aReadWriteRegister3);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister4(IntPtr aHandle, uint* aReadOnlyRegister4);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister5(IntPtr aHandle, uint* aReadOnlyRegister5);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister6(IntPtr aHandle, uint* aReadOnlyRegister6);
        [DllImport("CpZappOrgTestWidget1")]
        static extern unsafe void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister7(IntPtr aHandle, uint* aReadOnlyRegister7);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iReadWriteRegister0Changed;
        private CallbackPropertyChanged iReadWriteRegister1Changed;
        private CallbackPropertyChanged iReadWriteRegister2Changed;
        private CallbackPropertyChanged iReadWriteRegister3Changed;
        private CallbackPropertyChanged iReadOnlyRegister4Changed;
        private CallbackPropertyChanged iReadOnlyRegister5Changed;
        private CallbackPropertyChanged iReadOnlyRegister6Changed;
        private CallbackPropertyChanged iReadOnlyRegister7Changed;
        private Callback iCallbackReadWriteRegister0Changed;
        private Callback iCallbackReadWriteRegister1Changed;
        private Callback iCallbackReadWriteRegister2Changed;
        private Callback iCallbackReadWriteRegister3Changed;
        private Callback iCallbackReadOnlyRegister4Changed;
        private Callback iCallbackReadOnlyRegister5Changed;
        private Callback iCallbackReadOnlyRegister6Changed;
        private Callback iCallbackReadOnlyRegister7Changed;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyZappOrgTestWidget1(CpDevice aDevice)
        {
            iHandle = CpProxyZappOrgTestWidget1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        public unsafe void SyncSetReadWriteRegister(uint aRegisterIndex, uint aRegisterValue)
        {
            {
                CpProxyZappOrgTestWidget1SyncSetReadWriteRegister(iHandle, aRegisterIndex, aRegisterValue);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetReadWriteRegister().</remarks>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetReadWriteRegister(uint aRegisterIndex, uint aRegisterValue, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestWidget1BeginSetReadWriteRegister(iHandle, aRegisterIndex, aRegisterValue, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetReadWriteRegister(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyZappOrgTestWidget1EndSetReadWriteRegister(iHandle, aAsyncHandle))
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
        /// <param name="aWidgetClass"></param>
        public unsafe void SyncGetWidgetClass(out uint aWidgetClass)
        {
            fixed (uint* widgetClass = &aWidgetClass)
            {
                CpProxyZappOrgTestWidget1SyncGetWidgetClass(iHandle, widgetClass);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetWidgetClass().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetWidgetClass(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestWidget1BeginGetWidgetClass(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aWidgetClass"></param>
        public unsafe void EndGetWidgetClass(IntPtr aAsyncHandle, out uint aWidgetClass)
        {
            fixed (uint* widgetClass = &aWidgetClass)
            {
                if (0 != CpProxyZappOrgTestWidget1EndGetWidgetClass(iHandle, aAsyncHandle, widgetClass))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ReadWriteRegister0 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadWriteRegister0Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadWriteRegister0Changed(CallbackPropertyChanged aReadWriteRegister0Changed)
        {
            iReadWriteRegister0Changed = aReadWriteRegister0Changed;
            iCallbackReadWriteRegister0Changed = new Callback(PropertyReadWriteRegister0Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister0Changed(iHandle, iCallbackReadWriteRegister0Changed, ptr);
        }

        private void PropertyReadWriteRegister0Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadWriteRegister0Changed();
        }

        /// <summary>
        /// Set a delegate to be run when the ReadWriteRegister1 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadWriteRegister1Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadWriteRegister1Changed(CallbackPropertyChanged aReadWriteRegister1Changed)
        {
            iReadWriteRegister1Changed = aReadWriteRegister1Changed;
            iCallbackReadWriteRegister1Changed = new Callback(PropertyReadWriteRegister1Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister1Changed(iHandle, iCallbackReadWriteRegister1Changed, ptr);
        }

        private void PropertyReadWriteRegister1Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadWriteRegister1Changed();
        }

        /// <summary>
        /// Set a delegate to be run when the ReadWriteRegister2 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadWriteRegister2Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadWriteRegister2Changed(CallbackPropertyChanged aReadWriteRegister2Changed)
        {
            iReadWriteRegister2Changed = aReadWriteRegister2Changed;
            iCallbackReadWriteRegister2Changed = new Callback(PropertyReadWriteRegister2Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister2Changed(iHandle, iCallbackReadWriteRegister2Changed, ptr);
        }

        private void PropertyReadWriteRegister2Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadWriteRegister2Changed();
        }

        /// <summary>
        /// Set a delegate to be run when the ReadWriteRegister3 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadWriteRegister3Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadWriteRegister3Changed(CallbackPropertyChanged aReadWriteRegister3Changed)
        {
            iReadWriteRegister3Changed = aReadWriteRegister3Changed;
            iCallbackReadWriteRegister3Changed = new Callback(PropertyReadWriteRegister3Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister3Changed(iHandle, iCallbackReadWriteRegister3Changed, ptr);
        }

        private void PropertyReadWriteRegister3Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadWriteRegister3Changed();
        }

        /// <summary>
        /// Set a delegate to be run when the ReadOnlyRegister4 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadOnlyRegister4Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadOnlyRegister4Changed(CallbackPropertyChanged aReadOnlyRegister4Changed)
        {
            iReadOnlyRegister4Changed = aReadOnlyRegister4Changed;
            iCallbackReadOnlyRegister4Changed = new Callback(PropertyReadOnlyRegister4Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister4Changed(iHandle, iCallbackReadOnlyRegister4Changed, ptr);
        }

        private void PropertyReadOnlyRegister4Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadOnlyRegister4Changed();
        }

        /// <summary>
        /// Set a delegate to be run when the ReadOnlyRegister5 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadOnlyRegister5Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadOnlyRegister5Changed(CallbackPropertyChanged aReadOnlyRegister5Changed)
        {
            iReadOnlyRegister5Changed = aReadOnlyRegister5Changed;
            iCallbackReadOnlyRegister5Changed = new Callback(PropertyReadOnlyRegister5Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister5Changed(iHandle, iCallbackReadOnlyRegister5Changed, ptr);
        }

        private void PropertyReadOnlyRegister5Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadOnlyRegister5Changed();
        }

        /// <summary>
        /// Set a delegate to be run when the ReadOnlyRegister6 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadOnlyRegister6Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadOnlyRegister6Changed(CallbackPropertyChanged aReadOnlyRegister6Changed)
        {
            iReadOnlyRegister6Changed = aReadOnlyRegister6Changed;
            iCallbackReadOnlyRegister6Changed = new Callback(PropertyReadOnlyRegister6Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister6Changed(iHandle, iCallbackReadOnlyRegister6Changed, ptr);
        }

        private void PropertyReadOnlyRegister6Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadOnlyRegister6Changed();
        }

        /// <summary>
        /// Set a delegate to be run when the ReadOnlyRegister7 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadOnlyRegister7Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadOnlyRegister7Changed(CallbackPropertyChanged aReadOnlyRegister7Changed)
        {
            iReadOnlyRegister7Changed = aReadOnlyRegister7Changed;
            iCallbackReadOnlyRegister7Changed = new Callback(PropertyReadOnlyRegister7Changed);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister7Changed(iHandle, iCallbackReadOnlyRegister7Changed, ptr);
        }

        private void PropertyReadOnlyRegister7Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestWidget1 self = (CpProxyZappOrgTestWidget1)gch.Target;
            self.iReadOnlyRegister7Changed();
        }

        /// <summary>
        /// Query the value of the ReadWriteRegister0 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadWriteRegister0">Will be set to the value of the property</param>
        public unsafe void PropertyReadWriteRegister0(out uint aReadWriteRegister0)
        {
            fixed (uint* readWriteRegister0 = &aReadWriteRegister0)
            {
                CpProxyZappOrgTestWidget1PropertyReadWriteRegister0(iHandle, readWriteRegister0);
            }
        }

        /// <summary>
        /// Query the value of the ReadWriteRegister1 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadWriteRegister1">Will be set to the value of the property</param>
        public unsafe void PropertyReadWriteRegister1(out uint aReadWriteRegister1)
        {
            fixed (uint* readWriteRegister1 = &aReadWriteRegister1)
            {
                CpProxyZappOrgTestWidget1PropertyReadWriteRegister1(iHandle, readWriteRegister1);
            }
        }

        /// <summary>
        /// Query the value of the ReadWriteRegister2 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadWriteRegister2">Will be set to the value of the property</param>
        public unsafe void PropertyReadWriteRegister2(out uint aReadWriteRegister2)
        {
            fixed (uint* readWriteRegister2 = &aReadWriteRegister2)
            {
                CpProxyZappOrgTestWidget1PropertyReadWriteRegister2(iHandle, readWriteRegister2);
            }
        }

        /// <summary>
        /// Query the value of the ReadWriteRegister3 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadWriteRegister3">Will be set to the value of the property</param>
        public unsafe void PropertyReadWriteRegister3(out uint aReadWriteRegister3)
        {
            fixed (uint* readWriteRegister3 = &aReadWriteRegister3)
            {
                CpProxyZappOrgTestWidget1PropertyReadWriteRegister3(iHandle, readWriteRegister3);
            }
        }

        /// <summary>
        /// Query the value of the ReadOnlyRegister4 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadOnlyRegister4">Will be set to the value of the property</param>
        public unsafe void PropertyReadOnlyRegister4(out uint aReadOnlyRegister4)
        {
            fixed (uint* readOnlyRegister4 = &aReadOnlyRegister4)
            {
                CpProxyZappOrgTestWidget1PropertyReadOnlyRegister4(iHandle, readOnlyRegister4);
            }
        }

        /// <summary>
        /// Query the value of the ReadOnlyRegister5 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadOnlyRegister5">Will be set to the value of the property</param>
        public unsafe void PropertyReadOnlyRegister5(out uint aReadOnlyRegister5)
        {
            fixed (uint* readOnlyRegister5 = &aReadOnlyRegister5)
            {
                CpProxyZappOrgTestWidget1PropertyReadOnlyRegister5(iHandle, readOnlyRegister5);
            }
        }

        /// <summary>
        /// Query the value of the ReadOnlyRegister6 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadOnlyRegister6">Will be set to the value of the property</param>
        public unsafe void PropertyReadOnlyRegister6(out uint aReadOnlyRegister6)
        {
            fixed (uint* readOnlyRegister6 = &aReadOnlyRegister6)
            {
                CpProxyZappOrgTestWidget1PropertyReadOnlyRegister6(iHandle, readOnlyRegister6);
            }
        }

        /// <summary>
        /// Query the value of the ReadOnlyRegister7 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadOnlyRegister7">Will be set to the value of the property</param>
        public unsafe void PropertyReadOnlyRegister7(out uint aReadOnlyRegister7)
        {
            fixed (uint* readOnlyRegister7 = &aReadOnlyRegister7)
            {
                CpProxyZappOrgTestWidget1PropertyReadOnlyRegister7(iHandle, readOnlyRegister7);
            }
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyZappOrgTestWidget1()
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
                CpProxyZappOrgTestWidget1Destroy(iHandle);
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

