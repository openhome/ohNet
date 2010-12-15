using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyUpnpOrgSwitchPower1 : ICpProxy, IDisposable
    {
        void SyncSetTarget(bool anewTargetValue);
        void BeginSetTarget(bool anewTargetValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetTarget(IntPtr aAsyncHandle);
        void SyncGetTarget(out bool aRetTargetValue);
        void BeginGetTarget(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetTarget(IntPtr aAsyncHandle, out bool aRetTargetValue);
        void SyncGetStatus(out bool aResultStatus);
        void BeginGetStatus(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetStatus(IntPtr aAsyncHandle, out bool aResultStatus);
        void SetPropertyStatusChanged(CpProxy.CallbackPropertyChanged aStatusChanged);
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
        private Zapp.Core.Action iActionSetTarget;
        private Zapp.Core.Action iActionGetTarget;
        private Zapp.Core.Action iActionGetStatus;
        private PropertyBool iStatus;
        private CallbackPropertyChanged iStatusChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyUpnpOrgSwitchPower1(CpDevice aDevice)
            : base("schemas-upnp-org", "SwitchPower", 1, aDevice)
        {
            Zapp.Core.Parameter param;

            iActionSetTarget = new Zapp.Core.Action("SetTarget");
            param = new ParameterBool("newTargetValue");
            iActionSetTarget.AddInputParameter(param);

            iActionGetTarget = new Zapp.Core.Action("GetTarget");
            param = new ParameterBool("RetTargetValue");
            iActionGetTarget.AddOutputParameter(param);

            iActionGetStatus = new Zapp.Core.Action("GetStatus");
            param = new ParameterBool("ResultStatus");
            iActionGetStatus.AddOutputParameter(param);

            iStatus = new PropertyBool("Status", StatusPropertyChanged);
            AddProperty(iStatus);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="anewTargetValue"></param>
        public void SyncSetTarget(bool anewTargetValue)
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
        /// <param name="anewTargetValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetTarget(bool anewTargetValue, CallbackAsyncComplete aCallback)
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
            uint index = 0;
            aResultStatus = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the Status state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgSwitchPower1 instance will not overlap.</remarks>
        /// <param name="aStatusChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyStatusChanged(CallbackPropertyChanged aStatusChanged)
        {
            lock (this)
            {
                iStatusChanged = aStatusChanged;
            }
        }

        private void StatusPropertyChanged()
        {
            lock (this)
            {
                if (iStatusChanged != null)
                {
                    iStatusChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the Status property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aStatus">Will be set to the value of the property</param>
        public bool PropertyStatus()
        {
            return iStatus.Value();
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
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                DisposeProxy();
                iHandle = IntPtr.Zero;
                iActionSetTarget.Dispose();
                iActionGetTarget.Dispose();
                iActionGetStatus.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

