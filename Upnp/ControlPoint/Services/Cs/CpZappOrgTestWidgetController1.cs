using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyZappOrgTestWidgetController1 : ICpProxy, IDisposable
    {
        void SyncCreateWidget(String aWidgetUdn, uint aWidgetClass);
        void BeginCreateWidget(String aWidgetUdn, uint aWidgetClass, CpProxy.CallbackAsyncComplete aCallback);
        void EndCreateWidget(IntPtr aAsyncHandle);
        void SyncRemoveWidget(String aWidgetUdn);
        void BeginRemoveWidget(String aWidgetUdn, CpProxy.CallbackAsyncComplete aCallback);
        void EndRemoveWidget(IntPtr aAsyncHandle);
        void SyncSetWidgetRegister(String aWidgetUdn, uint aRegisterIndex, uint aRegisterValue);
        void BeginSetWidgetRegister(String aWidgetUdn, uint aRegisterIndex, uint aRegisterValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetWidgetRegister(IntPtr aAsyncHandle);
        void SyncGetWidgetRegister(String aWidgetUdn, uint aRegisterIndex, out uint aRegisterValue);
        void BeginGetWidgetRegister(String aWidgetUdn, uint aRegisterIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetWidgetRegister(IntPtr aAsyncHandle, out uint aRegisterValue);
    }

    internal class SyncCreateWidgetZappOrgTestWidgetController1 : SyncProxyAction
    {
        private CpProxyZappOrgTestWidgetController1 iService;

        public SyncCreateWidgetZappOrgTestWidgetController1(CpProxyZappOrgTestWidgetController1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndCreateWidget(aAsyncHandle);
        }
    };

    internal class SyncRemoveWidgetZappOrgTestWidgetController1 : SyncProxyAction
    {
        private CpProxyZappOrgTestWidgetController1 iService;

        public SyncRemoveWidgetZappOrgTestWidgetController1(CpProxyZappOrgTestWidgetController1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndRemoveWidget(aAsyncHandle);
        }
    };

    internal class SyncSetWidgetRegisterZappOrgTestWidgetController1 : SyncProxyAction
    {
        private CpProxyZappOrgTestWidgetController1 iService;

        public SyncSetWidgetRegisterZappOrgTestWidgetController1(CpProxyZappOrgTestWidgetController1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetWidgetRegister(aAsyncHandle);
        }
    };

    internal class SyncGetWidgetRegisterZappOrgTestWidgetController1 : SyncProxyAction
    {
        private CpProxyZappOrgTestWidgetController1 iService;
        private uint iRegisterValue;

        public SyncGetWidgetRegisterZappOrgTestWidgetController1(CpProxyZappOrgTestWidgetController1 aProxy)
        {
            iService = aProxy;
        }
        public uint RegisterValue()
        {
            return iRegisterValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetWidgetRegister(aAsyncHandle, out iRegisterValue);
        }
    };

    /// <summary>
    /// Proxy for the zapp.org:TestWidgetController:1 UPnP service
    /// </summary>
    public class CpProxyZappOrgTestWidgetController1 : CpProxy, IDisposable, ICpProxyZappOrgTestWidgetController1
    {
        private Zapp.Core.Action iActionCreateWidget;
        private Zapp.Core.Action iActionRemoveWidget;
        private Zapp.Core.Action iActionSetWidgetRegister;
        private Zapp.Core.Action iActionGetWidgetRegister;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyZappOrgTestWidgetController1(CpDevice aDevice)
            : base("zapp-org", "TestWidgetController", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionCreateWidget = new Zapp.Core.Action("CreateWidget");
            param = new ParameterString("WidgetUdn", allowedValues);
            iActionCreateWidget.AddInputParameter(param);
            param = new ParameterUint("WidgetClass");
            iActionCreateWidget.AddInputParameter(param);

            iActionRemoveWidget = new Zapp.Core.Action("RemoveWidget");
            param = new ParameterString("WidgetUdn", allowedValues);
            iActionRemoveWidget.AddInputParameter(param);

            iActionSetWidgetRegister = new Zapp.Core.Action("SetWidgetRegister");
            param = new ParameterString("WidgetUdn", allowedValues);
            iActionSetWidgetRegister.AddInputParameter(param);
            param = new ParameterUint("RegisterIndex");
            iActionSetWidgetRegister.AddInputParameter(param);
            param = new ParameterUint("RegisterValue");
            iActionSetWidgetRegister.AddInputParameter(param);

            iActionGetWidgetRegister = new Zapp.Core.Action("GetWidgetRegister");
            param = new ParameterString("WidgetUdn", allowedValues);
            iActionGetWidgetRegister.AddInputParameter(param);
            param = new ParameterUint("RegisterIndex");
            iActionGetWidgetRegister.AddInputParameter(param);
            param = new ParameterUint("RegisterValue");
            iActionGetWidgetRegister.AddOutputParameter(param);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aWidgetClass"></param>
        public void SyncCreateWidget(String aWidgetUdn, uint aWidgetClass)
        {
            SyncCreateWidgetZappOrgTestWidgetController1 sync = new SyncCreateWidgetZappOrgTestWidgetController1(this);
            BeginCreateWidget(aWidgetUdn, aWidgetClass, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCreateWidget().</remarks>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aWidgetClass"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginCreateWidget(String aWidgetUdn, uint aWidgetClass, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionCreateWidget, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionCreateWidget.InputParameter(inIndex++), aWidgetUdn));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionCreateWidget.InputParameter(inIndex++), aWidgetClass));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndCreateWidget(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aWidgetUdn"></param>
        public void SyncRemoveWidget(String aWidgetUdn)
        {
            SyncRemoveWidgetZappOrgTestWidgetController1 sync = new SyncRemoveWidgetZappOrgTestWidgetController1(this);
            BeginRemoveWidget(aWidgetUdn, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndRemoveWidget().</remarks>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginRemoveWidget(String aWidgetUdn, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionRemoveWidget, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionRemoveWidget.InputParameter(inIndex++), aWidgetUdn));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndRemoveWidget(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        public void SyncSetWidgetRegister(String aWidgetUdn, uint aRegisterIndex, uint aRegisterValue)
        {
            SyncSetWidgetRegisterZappOrgTestWidgetController1 sync = new SyncSetWidgetRegisterZappOrgTestWidgetController1(this);
            BeginSetWidgetRegister(aWidgetUdn, aRegisterIndex, aRegisterValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetWidgetRegister().</remarks>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetWidgetRegister(String aWidgetUdn, uint aRegisterIndex, uint aRegisterValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetWidgetRegister, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetWidgetRegister.InputParameter(inIndex++), aWidgetUdn));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetWidgetRegister.InputParameter(inIndex++), aRegisterIndex));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetWidgetRegister.InputParameter(inIndex++), aRegisterValue));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetWidgetRegister(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        public void SyncGetWidgetRegister(String aWidgetUdn, uint aRegisterIndex, out uint aRegisterValue)
        {
            SyncGetWidgetRegisterZappOrgTestWidgetController1 sync = new SyncGetWidgetRegisterZappOrgTestWidgetController1(this);
            BeginGetWidgetRegister(aWidgetUdn, aRegisterIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRegisterValue = sync.RegisterValue();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetWidgetRegister().</remarks>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetWidgetRegister(String aWidgetUdn, uint aRegisterIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetWidgetRegister, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetWidgetRegister.InputParameter(inIndex++), aWidgetUdn));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetWidgetRegister.InputParameter(inIndex++), aRegisterIndex));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetWidgetRegister.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRegisterValue"></param>
        public void EndGetWidgetRegister(IntPtr aAsyncHandle, out uint aRegisterValue)
        {
            uint index = 0;
            aRegisterValue = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyZappOrgTestWidgetController1()
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
                iActionCreateWidget.Dispose();
                iActionRemoveWidget.Dispose();
                iActionSetWidgetRegister.Dispose();
                iActionGetWidgetRegister.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

