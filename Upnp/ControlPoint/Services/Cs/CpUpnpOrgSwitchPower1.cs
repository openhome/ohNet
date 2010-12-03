using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyUpnpOrgSwitchPower1 : ICpProxy, IDisposable
    {
        void SyncSetTarget(bool anewTargetValue);
        void BeginSetTarget(bool anewTargetValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetTarget(uint aAsyncHandle);
        void SyncGetTarget(out bool aRetTargetValue);
        void BeginGetTarget(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetTarget(uint aAsyncHandle, out bool aRetTargetValue);
        void SyncGetStatus(out bool aResultStatus);
        void BeginGetStatus(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetStatus(uint aAsyncHandle, out bool aResultStatus);

        void SetPropertyStatusChanged(CpProxy.CallbackPropertyChanged aStatusChanged);
        void PropertyStatus(out bool aStatus);
    }

    /// <summary>
    /// Proxy for the upnp.org:SwitchPower:1 UPnP service
    /// </summary>
    public class CpProxyUpnpOrgSwitchPower1 : CpProxy, IDisposable, ICpProxyUpnpOrgSwitchPower1
    {
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern uint CpProxyUpnpOrgSwitchPower1Create(uint aDeviceHandle);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern void CpProxyUpnpOrgSwitchPower1Destroy(uint aHandle);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe void CpProxyUpnpOrgSwitchPower1SyncSetTarget(uint aHandle, uint anewTargetValue);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe void CpProxyUpnpOrgSwitchPower1BeginSetTarget(uint aHandle, uint anewTargetValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe int CpProxyUpnpOrgSwitchPower1EndSetTarget(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe void CpProxyUpnpOrgSwitchPower1SyncGetTarget(uint aHandle, uint* aRetTargetValue);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe void CpProxyUpnpOrgSwitchPower1BeginGetTarget(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe int CpProxyUpnpOrgSwitchPower1EndGetTarget(uint aHandle, uint aAsync, uint* aRetTargetValue);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe void CpProxyUpnpOrgSwitchPower1SyncGetStatus(uint aHandle, uint* aResultStatus);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe void CpProxyUpnpOrgSwitchPower1BeginGetStatus(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe int CpProxyUpnpOrgSwitchPower1EndGetStatus(uint aHandle, uint aAsync, uint* aResultStatus);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern void CpProxyUpnpOrgSwitchPower1SetPropertyStatusChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgSwitchPower1")]
        static extern unsafe void CpProxyUpnpOrgSwitchPower1PropertyStatus(uint aHandle, uint* aStatus);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iStatusChanged;
        private Callback iCallbackStatusChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyUpnpOrgSwitchPower1(CpDevice aDevice)
        {
            iHandle = CpProxyUpnpOrgSwitchPower1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="anewTargetValue"></param>
        public unsafe void SyncSetTarget(bool anewTargetValue)
        {
            uint newTargetValue = (anewTargetValue? 1u : 0u);
            {
                CpProxyUpnpOrgSwitchPower1SyncSetTarget(iHandle, newTargetValue);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetTarget().</remarks>
        /// <param name="anewTargetValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetTarget(bool anewTargetValue, CallbackAsyncComplete aCallback)
        {
            uint newTargetValue = (anewTargetValue? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgSwitchPower1BeginSetTarget(iHandle, newTargetValue, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetTarget(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyUpnpOrgSwitchPower1EndSetTarget(iHandle, aAsyncHandle))
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
        /// <param name="aRetTargetValue"></param>
        public unsafe void SyncGetTarget(out bool aRetTargetValue)
        {
            uint retTargetValue;
            {
                CpProxyUpnpOrgSwitchPower1SyncGetTarget(iHandle, &retTargetValue);
            }
            aRetTargetValue = (retTargetValue != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetTarget().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetTarget(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgSwitchPower1BeginGetTarget(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRetTargetValue"></param>
        public unsafe void EndGetTarget(uint aAsyncHandle, out bool aRetTargetValue)
        {
            uint retTargetValue;
            {
                if (0 != CpProxyUpnpOrgSwitchPower1EndGetTarget(iHandle, aAsyncHandle, &retTargetValue))
                {
                    throw(new ProxyError());
                }
            }
            aRetTargetValue = (retTargetValue != 0);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aResultStatus"></param>
        public unsafe void SyncGetStatus(out bool aResultStatus)
        {
            uint resultStatus;
            {
                CpProxyUpnpOrgSwitchPower1SyncGetStatus(iHandle, &resultStatus);
            }
            aResultStatus = (resultStatus != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetStatus().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetStatus(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgSwitchPower1BeginGetStatus(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResultStatus"></param>
        public unsafe void EndGetStatus(uint aAsyncHandle, out bool aResultStatus)
        {
            uint resultStatus;
            {
                if (0 != CpProxyUpnpOrgSwitchPower1EndGetStatus(iHandle, aAsyncHandle, &resultStatus))
                {
                    throw(new ProxyError());
                }
            }
            aResultStatus = (resultStatus != 0);
        }

        /// <summary>
        /// Set a delegate to be run when the Status state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgSwitchPower1 instance will not overlap.</remarks>
        /// <param name="aStatusChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyStatusChanged(CallbackPropertyChanged aStatusChanged)
        {
            iStatusChanged = aStatusChanged;
            iCallbackStatusChanged = new Callback(PropertyStatusChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgSwitchPower1SetPropertyStatusChanged(iHandle, iCallbackStatusChanged, ptr);
        }

        private void PropertyStatusChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgSwitchPower1 self = (CpProxyUpnpOrgSwitchPower1)gch.Target;
            self.iStatusChanged();
        }

        /// <summary>
        /// Query the value of the Status property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aStatus">Will be set to the value of the property</param>
        public unsafe void PropertyStatus(out bool aStatus)
        {
            uint status;
            CpProxyUpnpOrgSwitchPower1PropertyStatus(iHandle, &status);
            aStatus = (status != 0);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyUpnpOrgSwitchPower1()
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
                CpProxyUpnpOrgSwitchPower1Destroy(iHandle);
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

