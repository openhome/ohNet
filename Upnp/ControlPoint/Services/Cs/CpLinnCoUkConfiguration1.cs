using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkConfiguration1 : ICpProxy, IDisposable
    {
        void SyncConfigurationXml(out string aaConfigurationXml);
        void BeginConfigurationXml(CpProxy.CallbackAsyncComplete aCallback);
        void EndConfigurationXml(IntPtr aAsyncHandle, out string aaConfigurationXml);
        void SyncParameterXml(out string aaParameterXml);
        void BeginParameterXml(CpProxy.CallbackAsyncComplete aCallback);
        void EndParameterXml(IntPtr aAsyncHandle, out string aaParameterXml);
        void SyncSetParameter(string aaTarget, string aaName, string aaValue);
        void BeginSetParameter(string aaTarget, string aaName, string aaValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetParameter(IntPtr aAsyncHandle);

        void SetPropertyConfigurationXmlChanged(CpProxy.CallbackPropertyChanged aConfigurationXmlChanged);
        void PropertyConfigurationXml(out string aConfigurationXml);
        void SetPropertyParameterXmlChanged(CpProxy.CallbackPropertyChanged aParameterXmlChanged);
        void PropertyParameterXml(out string aParameterXml);
    }

    /// <summary>
    /// Proxy for the linn.co.uk:Configuration:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkConfiguration1 : CpProxy, IDisposable, ICpProxyLinnCoUkConfiguration1
    {
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern IntPtr CpProxyLinnCoUkConfiguration1Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern void CpProxyLinnCoUkConfiguration1Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1SyncConfigurationXml(IntPtr aHandle, char** aaConfigurationXml);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1BeginConfigurationXml(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe int CpProxyLinnCoUkConfiguration1EndConfigurationXml(IntPtr aHandle, IntPtr aAsync, char** aaConfigurationXml);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1SyncParameterXml(IntPtr aHandle, char** aaParameterXml);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1BeginParameterXml(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe int CpProxyLinnCoUkConfiguration1EndParameterXml(IntPtr aHandle, IntPtr aAsync, char** aaParameterXml);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1SyncSetParameter(IntPtr aHandle, char* aaTarget, char* aaName, char* aaValue);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1BeginSetParameter(IntPtr aHandle, char* aaTarget, char* aaName, char* aaValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe int CpProxyLinnCoUkConfiguration1EndSetParameter(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern void CpProxyLinnCoUkConfiguration1SetPropertyConfigurationXmlChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern void CpProxyLinnCoUkConfiguration1SetPropertyParameterXmlChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1PropertyConfigurationXml(IntPtr aHandle, char** aConfigurationXml);
        [DllImport("CpLinnCoUkConfiguration1")]
        static extern unsafe void CpProxyLinnCoUkConfiguration1PropertyParameterXml(IntPtr aHandle, char** aParameterXml);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iConfigurationXmlChanged;
        private CallbackPropertyChanged iParameterXmlChanged;
        private Callback iCallbackConfigurationXmlChanged;
        private Callback iCallbackParameterXmlChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkConfiguration1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkConfiguration1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaConfigurationXml"></param>
        public unsafe void SyncConfigurationXml(out string aaConfigurationXml)
        {
            char* aConfigurationXml;
            {
                CpProxyLinnCoUkConfiguration1SyncConfigurationXml(iHandle, &aConfigurationXml);
            }
            aaConfigurationXml = Marshal.PtrToStringAnsi((IntPtr)aConfigurationXml);
            ZappFree(aConfigurationXml);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndConfigurationXml().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginConfigurationXml(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkConfiguration1BeginConfigurationXml(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaConfigurationXml"></param>
        public unsafe void EndConfigurationXml(IntPtr aAsyncHandle, out string aaConfigurationXml)
        {
            char* aConfigurationXml;
            {
                if (0 != CpProxyLinnCoUkConfiguration1EndConfigurationXml(iHandle, aAsyncHandle, &aConfigurationXml))
                {
                    throw(new ProxyError());
                }
            }
            aaConfigurationXml = Marshal.PtrToStringAnsi((IntPtr)aConfigurationXml);
            ZappFree(aConfigurationXml);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaParameterXml"></param>
        public unsafe void SyncParameterXml(out string aaParameterXml)
        {
            char* aParameterXml;
            {
                CpProxyLinnCoUkConfiguration1SyncParameterXml(iHandle, &aParameterXml);
            }
            aaParameterXml = Marshal.PtrToStringAnsi((IntPtr)aParameterXml);
            ZappFree(aParameterXml);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndParameterXml().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginParameterXml(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkConfiguration1BeginParameterXml(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaParameterXml"></param>
        public unsafe void EndParameterXml(IntPtr aAsyncHandle, out string aaParameterXml)
        {
            char* aParameterXml;
            {
                if (0 != CpProxyLinnCoUkConfiguration1EndParameterXml(iHandle, aAsyncHandle, &aParameterXml))
                {
                    throw(new ProxyError());
                }
            }
            aaParameterXml = Marshal.PtrToStringAnsi((IntPtr)aParameterXml);
            ZappFree(aParameterXml);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaTarget"></param>
        /// <param name="aaName"></param>
        /// <param name="aaValue"></param>
        public unsafe void SyncSetParameter(string aaTarget, string aaName, string aaValue)
        {
            char* aTarget = (char*)Marshal.StringToHGlobalAnsi(aaTarget);
            char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
            char* aValue = (char*)Marshal.StringToHGlobalAnsi(aaValue);
            {
                CpProxyLinnCoUkConfiguration1SyncSetParameter(iHandle, aTarget, aName, aValue);
            }
            Marshal.FreeHGlobal((IntPtr)aTarget);
            Marshal.FreeHGlobal((IntPtr)aName);
            Marshal.FreeHGlobal((IntPtr)aValue);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetParameter().</remarks>
        /// <param name="aaTarget"></param>
        /// <param name="aaName"></param>
        /// <param name="aaValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetParameter(string aaTarget, string aaName, string aaValue, CallbackAsyncComplete aCallback)
        {
            char* aTarget = (char*)Marshal.StringToHGlobalAnsi(aaTarget);
            char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
            char* aValue = (char*)Marshal.StringToHGlobalAnsi(aaValue);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkConfiguration1BeginSetParameter(iHandle, aTarget, aName, aValue, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aTarget);
            Marshal.FreeHGlobal((IntPtr)aName);
            Marshal.FreeHGlobal((IntPtr)aValue);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetParameter(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkConfiguration1EndSetParameter(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ConfigurationXml state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkConfiguration1 instance will not overlap.</remarks>
        /// <param name="aConfigurationXmlChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyConfigurationXmlChanged(CallbackPropertyChanged aConfigurationXmlChanged)
        {
            iConfigurationXmlChanged = aConfigurationXmlChanged;
            iCallbackConfigurationXmlChanged = new Callback(PropertyConfigurationXmlChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkConfiguration1SetPropertyConfigurationXmlChanged(iHandle, iCallbackConfigurationXmlChanged, ptr);
        }

        private void PropertyConfigurationXmlChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkConfiguration1 self = (CpProxyLinnCoUkConfiguration1)gch.Target;
            self.iConfigurationXmlChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the ParameterXml state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkConfiguration1 instance will not overlap.</remarks>
        /// <param name="aParameterXmlChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyParameterXmlChanged(CallbackPropertyChanged aParameterXmlChanged)
        {
            iParameterXmlChanged = aParameterXmlChanged;
            iCallbackParameterXmlChanged = new Callback(PropertyParameterXmlChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkConfiguration1SetPropertyParameterXmlChanged(iHandle, iCallbackParameterXmlChanged, ptr);
        }

        private void PropertyParameterXmlChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkConfiguration1 self = (CpProxyLinnCoUkConfiguration1)gch.Target;
            self.iParameterXmlChanged();
        }

        /// <summary>
        /// Query the value of the ConfigurationXml property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aConfigurationXml">Will be set to the value of the property</param>
        public unsafe void PropertyConfigurationXml(out string aConfigurationXml)
        {
            char* ptr;
            CpProxyLinnCoUkConfiguration1PropertyConfigurationXml(iHandle, &ptr);
            aConfigurationXml = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the ParameterXml property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aParameterXml">Will be set to the value of the property</param>
        public unsafe void PropertyParameterXml(out string aParameterXml)
        {
            char* ptr;
            CpProxyLinnCoUkConfiguration1PropertyParameterXml(iHandle, &ptr);
            aParameterXml = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkConfiguration1()
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
                CpProxyLinnCoUkConfiguration1Destroy(iHandle);
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

