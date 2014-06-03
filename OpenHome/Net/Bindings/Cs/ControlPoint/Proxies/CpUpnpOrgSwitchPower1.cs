using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyUpnpOrgSwitchPower1 : ICpProxy, IDisposable
    {
        void SyncSetTarget(bool aNewTargetValue);
        void BeginSetTarget(bool aNewTargetValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetTarget(IntPtr aAsyncHandle);
        void SyncGetTarget(out bool aRetTargetValue);
        void BeginGetTarget(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetTarget(IntPtr aAsyncHandle, out bool aRetTargetValue);
        void SyncGetStatus(out bool aResultStatus);
        void BeginGetStatus(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetStatus(IntPtr aAsyncHandle, out bool aResultStatus);
        void SetPropertyStatusChanged(System.Action aStatusChanged);
        bool PropertyStatus();
    }

    internal class SyncSetTargetUpnpOrgSwitchPower1 : SyncProxyAction
    {
        private CpProxyUpnpOrgSwitchPower1 iService;

        public SyncSetTargetUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetTarget(aAsyncHandle);
        }
    };

    internal class SyncGetTargetUpnpOrgSwitchPower1 : SyncProxyAction
    {
        private CpProxyUpnpOrgSwitchPower1 iService;
        private bool iRetTargetValue;

        public SyncGetTargetUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1 aProxy)
        {
            iService = aProxy;
        }
        public bool RetTargetValue()
        {
            return iRetTargetValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetTarget(aAsyncHandle, out iRetTargetValue);
        }
    };

    internal class SyncGetStatusUpnpOrgSwitchPower1 : SyncProxyAction
    {
        private CpProxyUpnpOrgSwitchPower1 iService;
        private bool iResultStatus;

        public SyncGetStatusUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1 aProxy)
        {
            iService = aProxy;
        }
        public bool ResultStatus()
        {
            return iResultStatus;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetStatus(aAsyncHandle, out iResultStatus);
        }
    };

    /// <summary>
    /// Proxy for the upnp.org:SwitchPower:1 UPnP service
    /// </summary>
    public class CpProxyUpnpOrgSwitchPower1 : CpProxy, IDisposable, ICpProxyUpnpOrgSwitchPower1
    {
        private OpenHome.Net.Core.Action iActionSetTarget;
        private OpenHome.Net.Core.Action iActionGetTarget;
        private OpenHome.Net.Core.Action iActionGetStatus;
        private PropertyBool iStatus;
        private System.Action iStatusChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyUpnpOrgSwitchPower1(CpDevice aDevice)
            : base("schemas-upnp-org", "SwitchPower", 1, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            

            iActionSetTarget = new OpenHome.Net.Core.Action("SetTarget");
            param = new ParameterBool("newTargetValue");
            iActionSetTarget.AddInputParameter(param);

            iActionGetTarget = new OpenHome.Net.Core.Action("GetTarget");
            param = new ParameterBool("RetTargetValue");
            iActionGetTarget.AddOutputParameter(param);

            iActionGetStatus = new OpenHome.Net.Core.Action("GetStatus");
            param = new ParameterBool("ResultStatus");
            iActionGetStatus.AddOutputParameter(param);

            iStatus = new PropertyBool("Status", StatusPropertyChanged);
            AddProperty(iStatus);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aNewTargetValue"></param>
        public void SyncSetTarget(bool aNewTargetValue)
        {
            SyncSetTargetUpnpOrgSwitchPower1 sync = new SyncSetTargetUpnpOrgSwitchPower1(this);
            BeginSetTarget(aNewTargetValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetTarget().</remarks>
        /// <param name="aNewTargetValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetTarget(bool aNewTargetValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetTarget, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetTarget.InputParameter(inIndex++), aNewTargetValue));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetTarget(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRetTargetValue"></param>
        public void SyncGetTarget(out bool aRetTargetValue)
        {
            SyncGetTargetUpnpOrgSwitchPower1 sync = new SyncGetTargetUpnpOrgSwitchPower1(this);
            BeginGetTarget(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetTargetValue = sync.RetTargetValue();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetTarget().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetTarget(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetTarget, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionGetTarget.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRetTargetValue"></param>
        public void EndGetTarget(IntPtr aAsyncHandle, out bool aRetTargetValue)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aRetTargetValue = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aResultStatus"></param>
        public void SyncGetStatus(out bool aResultStatus)
        {
            SyncGetStatusUpnpOrgSwitchPower1 sync = new SyncGetStatusUpnpOrgSwitchPower1(this);
            BeginGetStatus(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResultStatus = sync.ResultStatus();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetStatus().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetStatus(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetStatus, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionGetStatus.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResultStatus"></param>
        public void EndGetStatus(IntPtr aAsyncHandle, out bool aResultStatus)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aResultStatus = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the Status state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgSwitchPower1 instance will not overlap.</remarks>
        /// <param name="aStatusChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyStatusChanged(System.Action aStatusChanged)
        {
            lock (iPropertyLock)
            {
                iStatusChanged = aStatusChanged;
            }
        }

        private void StatusPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iStatusChanged);
            }
        }

        /// <summary>
        /// Query the value of the Status property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Status property</returns>
        public bool PropertyStatus()
        {
            PropertyReadLock();
            bool val;
            try
            {
                val = iStatus.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                    return;
                DisposeProxy();
                iHandle = IntPtr.Zero;
            }
            iActionSetTarget.Dispose();
            iActionGetTarget.Dispose();
            iActionGetStatus.Dispose();
            iStatus.Dispose();
        }
    }
}

