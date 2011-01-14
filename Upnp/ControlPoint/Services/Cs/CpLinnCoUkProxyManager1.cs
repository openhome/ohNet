using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkProxyManager1 : ICpProxy, IDisposable
    {
        void SyncKontrolProductConnected(out String aConnected);
        void BeginKontrolProductConnected(CpProxy.CallbackAsyncComplete aCallback);
        void EndKontrolProductConnected(IntPtr aAsyncHandle, out String aConnected);
        void SyncSetKontrolProductConnected(String aConnected);
        void BeginSetKontrolProductConnected(String aConnected, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetKontrolProductConnected(IntPtr aAsyncHandle);
        void SyncKontrolProductComPort(out uint aPort);
        void BeginKontrolProductComPort(CpProxy.CallbackAsyncComplete aCallback);
        void EndKontrolProductComPort(IntPtr aAsyncHandle, out uint aPort);
        void SyncSetKontrolProductComPort(uint aConnected);
        void BeginSetKontrolProductComPort(uint aConnected, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetKontrolProductComPort(IntPtr aAsyncHandle);
        void SyncDiscPlayerConnected(out String aConnected);
        void BeginDiscPlayerConnected(CpProxy.CallbackAsyncComplete aCallback);
        void EndDiscPlayerConnected(IntPtr aAsyncHandle, out String aConnected);
        void SyncSetDiscPlayerConnected(String aConnected);
        void BeginSetDiscPlayerConnected(String aConnected, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDiscPlayerConnected(IntPtr aAsyncHandle);
        void SyncDiscPlayerComPort(out uint aPort);
        void BeginDiscPlayerComPort(CpProxy.CallbackAsyncComplete aCallback);
        void EndDiscPlayerComPort(IntPtr aAsyncHandle, out uint aPort);
        void SyncSetDiscPlayerComPort(uint aConnected);
        void BeginSetDiscPlayerComPort(uint aConnected, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDiscPlayerComPort(IntPtr aAsyncHandle);
        void SyncTestKontrolProductConnection(out bool aResult);
        void BeginTestKontrolProductConnection(CpProxy.CallbackAsyncComplete aCallback);
        void EndTestKontrolProductConnection(IntPtr aAsyncHandle, out bool aResult);
        void SyncTestDiscPlayerConnection(out bool aResult);
        void BeginTestDiscPlayerConnection(CpProxy.CallbackAsyncComplete aCallback);
        void EndTestDiscPlayerConnection(IntPtr aAsyncHandle, out bool aResult);
        void SetPropertyKontrolProductConnectedChanged(CpProxy.CallbackPropertyChanged aKontrolProductConnectedChanged);
        String PropertyKontrolProductConnected();
        void SetPropertyKontrolProductComPortChanged(CpProxy.CallbackPropertyChanged aKontrolProductComPortChanged);
        uint PropertyKontrolProductComPort();
        void SetPropertyDiscPlayerConnectedChanged(CpProxy.CallbackPropertyChanged aDiscPlayerConnectedChanged);
        String PropertyDiscPlayerConnected();
        void SetPropertyDiscPlayerComPortChanged(CpProxy.CallbackPropertyChanged aDiscPlayerComPortChanged);
        uint PropertyDiscPlayerComPort();
    }

    internal class SyncKontrolProductConnectedLinnCoUkProxyManager1 : SyncProxyAction
    {
        private CpProxyLinnCoUkProxyManager1 iService;
        private String iConnected;

        public SyncKontrolProductConnectedLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1 aProxy)
        {
            iService = aProxy;
        }
        public String Connected()
        {
            return iConnected;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndKontrolProductConnected(aAsyncHandle, out iConnected);
        }
    };

    internal class SyncSetKontrolProductConnectedLinnCoUkProxyManager1 : SyncProxyAction
    {
        private CpProxyLinnCoUkProxyManager1 iService;

        public SyncSetKontrolProductConnectedLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetKontrolProductConnected(aAsyncHandle);
        }
    };

    internal class SyncKontrolProductComPortLinnCoUkProxyManager1 : SyncProxyAction
    {
        private CpProxyLinnCoUkProxyManager1 iService;
        private uint iPort;

        public SyncKontrolProductComPortLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1 aProxy)
        {
            iService = aProxy;
        }
        public uint Port()
        {
            return iPort;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndKontrolProductComPort(aAsyncHandle, out iPort);
        }
    };

    internal class SyncSetKontrolProductComPortLinnCoUkProxyManager1 : SyncProxyAction
    {
        private CpProxyLinnCoUkProxyManager1 iService;

        public SyncSetKontrolProductComPortLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetKontrolProductComPort(aAsyncHandle);
        }
    };

    internal class SyncDiscPlayerConnectedLinnCoUkProxyManager1 : SyncProxyAction
    {
        private CpProxyLinnCoUkProxyManager1 iService;
        private String iConnected;

        public SyncDiscPlayerConnectedLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1 aProxy)
        {
            iService = aProxy;
        }
        public String Connected()
        {
            return iConnected;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDiscPlayerConnected(aAsyncHandle, out iConnected);
        }
    };

    internal class SyncSetDiscPlayerConnectedLinnCoUkProxyManager1 : SyncProxyAction
    {
        private CpProxyLinnCoUkProxyManager1 iService;

        public SyncSetDiscPlayerConnectedLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetDiscPlayerConnected(aAsyncHandle);
        }
    };

    internal class SyncDiscPlayerComPortLinnCoUkProxyManager1 : SyncProxyAction
    {
        private CpProxyLinnCoUkProxyManager1 iService;
        private uint iPort;

        public SyncDiscPlayerComPortLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1 aProxy)
        {
            iService = aProxy;
        }
        public uint Port()
        {
            return iPort;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDiscPlayerComPort(aAsyncHandle, out iPort);
        }
    };

    internal class SyncSetDiscPlayerComPortLinnCoUkProxyManager1 : SyncProxyAction
    {
        private CpProxyLinnCoUkProxyManager1 iService;

        public SyncSetDiscPlayerComPortLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetDiscPlayerComPort(aAsyncHandle);
        }
    };

    internal class SyncTestKontrolProductConnectionLinnCoUkProxyManager1 : SyncProxyAction
    {
        private CpProxyLinnCoUkProxyManager1 iService;
        private bool iResult;

        public SyncTestKontrolProductConnectionLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1 aProxy)
        {
            iService = aProxy;
        }
        public bool Result()
        {
            return iResult;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndTestKontrolProductConnection(aAsyncHandle, out iResult);
        }
    };

    internal class SyncTestDiscPlayerConnectionLinnCoUkProxyManager1 : SyncProxyAction
    {
        private CpProxyLinnCoUkProxyManager1 iService;
        private bool iResult;

        public SyncTestDiscPlayerConnectionLinnCoUkProxyManager1(CpProxyLinnCoUkProxyManager1 aProxy)
        {
            iService = aProxy;
        }
        public bool Result()
        {
            return iResult;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndTestDiscPlayerConnection(aAsyncHandle, out iResult);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:ProxyManager:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkProxyManager1 : CpProxy, IDisposable, ICpProxyLinnCoUkProxyManager1
    {
        private Zapp.Core.Action iActionKontrolProductConnected;
        private Zapp.Core.Action iActionSetKontrolProductConnected;
        private Zapp.Core.Action iActionKontrolProductComPort;
        private Zapp.Core.Action iActionSetKontrolProductComPort;
        private Zapp.Core.Action iActionDiscPlayerConnected;
        private Zapp.Core.Action iActionSetDiscPlayerConnected;
        private Zapp.Core.Action iActionDiscPlayerComPort;
        private Zapp.Core.Action iActionSetDiscPlayerComPort;
        private Zapp.Core.Action iActionTestKontrolProductConnection;
        private Zapp.Core.Action iActionTestDiscPlayerConnection;
        private PropertyString iKontrolProductConnected;
        private PropertyUint iKontrolProductComPort;
        private PropertyString iDiscPlayerConnected;
        private PropertyUint iDiscPlayerComPort;
        private CallbackPropertyChanged iKontrolProductConnectedChanged;
        private CallbackPropertyChanged iKontrolProductComPortChanged;
        private CallbackPropertyChanged iDiscPlayerConnectedChanged;
        private CallbackPropertyChanged iDiscPlayerComPortChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkProxyManager1(CpDevice aDevice)
            : base("linn-co-uk", "ProxyManager", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionKontrolProductConnected = new Zapp.Core.Action("KontrolProductConnected");
            allowedValues.Add("None");
            allowedValues.Add("Klimax Kontrol");
            allowedValues.Add("Akurate Kontrol");
            allowedValues.Add("Kisto");
            allowedValues.Add("Kinos");
            allowedValues.Add("Majik Kontrol");
            allowedValues.Add("Majik-I");
            allowedValues.Add("Unidisk SC");
            allowedValues.Add("Classik Movie");
            allowedValues.Add("Classik Music");
            allowedValues.Add("Roomamp 2");
            param = new ParameterString("aConnected", allowedValues);
            iActionKontrolProductConnected.AddOutputParameter(param);
            allowedValues.Clear();

            iActionSetKontrolProductConnected = new Zapp.Core.Action("SetKontrolProductConnected");
            allowedValues.Add("None");
            allowedValues.Add("Klimax Kontrol");
            allowedValues.Add("Akurate Kontrol");
            allowedValues.Add("Kisto");
            allowedValues.Add("Kinos");
            allowedValues.Add("Majik Kontrol");
            allowedValues.Add("Majik-I");
            allowedValues.Add("Unidisk SC");
            allowedValues.Add("Classik Movie");
            allowedValues.Add("Classik Music");
            allowedValues.Add("Roomamp 2");
            param = new ParameterString("aConnected", allowedValues);
            iActionSetKontrolProductConnected.AddInputParameter(param);
            allowedValues.Clear();

            iActionKontrolProductComPort = new Zapp.Core.Action("KontrolProductComPort");
            param = new ParameterUint("aPort");
            iActionKontrolProductComPort.AddOutputParameter(param);

            iActionSetKontrolProductComPort = new Zapp.Core.Action("SetKontrolProductComPort");
            param = new ParameterUint("aConnected");
            iActionSetKontrolProductComPort.AddInputParameter(param);

            iActionDiscPlayerConnected = new Zapp.Core.Action("DiscPlayerConnected");
            allowedValues.Add("None");
            allowedValues.Add("CD12");
            allowedValues.Add("Akurate CD");
            allowedValues.Add("Unidisk 1.1");
            allowedValues.Add("Unidisk 2.1");
            allowedValues.Add("Majik CD");
            allowedValues.Add("Unidisk SC");
            allowedValues.Add("Classik Movie");
            allowedValues.Add("Classik Music");
            param = new ParameterString("aConnected", allowedValues);
            iActionDiscPlayerConnected.AddOutputParameter(param);
            allowedValues.Clear();

            iActionSetDiscPlayerConnected = new Zapp.Core.Action("SetDiscPlayerConnected");
            allowedValues.Add("None");
            allowedValues.Add("CD12");
            allowedValues.Add("Akurate CD");
            allowedValues.Add("Unidisk 1.1");
            allowedValues.Add("Unidisk 2.1");
            allowedValues.Add("Majik CD");
            allowedValues.Add("Unidisk SC");
            allowedValues.Add("Classik Movie");
            allowedValues.Add("Classik Music");
            param = new ParameterString("aConnected", allowedValues);
            iActionSetDiscPlayerConnected.AddInputParameter(param);
            allowedValues.Clear();

            iActionDiscPlayerComPort = new Zapp.Core.Action("DiscPlayerComPort");
            param = new ParameterUint("aPort");
            iActionDiscPlayerComPort.AddOutputParameter(param);

            iActionSetDiscPlayerComPort = new Zapp.Core.Action("SetDiscPlayerComPort");
            param = new ParameterUint("aConnected");
            iActionSetDiscPlayerComPort.AddInputParameter(param);

            iActionTestKontrolProductConnection = new Zapp.Core.Action("TestKontrolProductConnection");
            param = new ParameterBool("aResult");
            iActionTestKontrolProductConnection.AddOutputParameter(param);

            iActionTestDiscPlayerConnection = new Zapp.Core.Action("TestDiscPlayerConnection");
            param = new ParameterBool("aResult");
            iActionTestDiscPlayerConnection.AddOutputParameter(param);

            iKontrolProductConnected = new PropertyString("KontrolProductConnected", KontrolProductConnectedPropertyChanged);
            AddProperty(iKontrolProductConnected);
            iKontrolProductComPort = new PropertyUint("KontrolProductComPort", KontrolProductComPortPropertyChanged);
            AddProperty(iKontrolProductComPort);
            iDiscPlayerConnected = new PropertyString("DiscPlayerConnected", DiscPlayerConnectedPropertyChanged);
            AddProperty(iDiscPlayerConnected);
            iDiscPlayerComPort = new PropertyUint("DiscPlayerComPort", DiscPlayerComPortPropertyChanged);
            AddProperty(iDiscPlayerComPort);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaConnected"></param>
        public void SyncKontrolProductConnected(out String aConnected)
        {
            SyncKontrolProductConnectedLinnCoUkProxyManager1 sync = new SyncKontrolProductConnectedLinnCoUkProxyManager1(this);
            BeginKontrolProductConnected(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aConnected = sync.Connected();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndKontrolProductConnected().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginKontrolProductConnected(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionKontrolProductConnected, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionKontrolProductConnected.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaConnected"></param>
        public void EndKontrolProductConnected(IntPtr aAsyncHandle, out String aConnected)
        {
            uint index = 0;
            aConnected = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaConnected"></param>
        public void SyncSetKontrolProductConnected(String aConnected)
        {
            SyncSetKontrolProductConnectedLinnCoUkProxyManager1 sync = new SyncSetKontrolProductConnectedLinnCoUkProxyManager1(this);
            BeginSetKontrolProductConnected(aConnected, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetKontrolProductConnected().</remarks>
        /// <param name="aaConnected"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetKontrolProductConnected(String aConnected, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetKontrolProductConnected, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetKontrolProductConnected.InputParameter(inIndex++), aConnected));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetKontrolProductConnected(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaPort"></param>
        public void SyncKontrolProductComPort(out uint aPort)
        {
            SyncKontrolProductComPortLinnCoUkProxyManager1 sync = new SyncKontrolProductComPortLinnCoUkProxyManager1(this);
            BeginKontrolProductComPort(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aPort = sync.Port();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndKontrolProductComPort().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginKontrolProductComPort(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionKontrolProductComPort, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionKontrolProductComPort.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaPort"></param>
        public void EndKontrolProductComPort(IntPtr aAsyncHandle, out uint aPort)
        {
            uint index = 0;
            aPort = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaConnected"></param>
        public void SyncSetKontrolProductComPort(uint aConnected)
        {
            SyncSetKontrolProductComPortLinnCoUkProxyManager1 sync = new SyncSetKontrolProductComPortLinnCoUkProxyManager1(this);
            BeginSetKontrolProductComPort(aConnected, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetKontrolProductComPort().</remarks>
        /// <param name="aaConnected"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetKontrolProductComPort(uint aConnected, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetKontrolProductComPort, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetKontrolProductComPort.InputParameter(inIndex++), aConnected));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetKontrolProductComPort(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaConnected"></param>
        public void SyncDiscPlayerConnected(out String aConnected)
        {
            SyncDiscPlayerConnectedLinnCoUkProxyManager1 sync = new SyncDiscPlayerConnectedLinnCoUkProxyManager1(this);
            BeginDiscPlayerConnected(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aConnected = sync.Connected();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDiscPlayerConnected().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDiscPlayerConnected(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDiscPlayerConnected, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionDiscPlayerConnected.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaConnected"></param>
        public void EndDiscPlayerConnected(IntPtr aAsyncHandle, out String aConnected)
        {
            uint index = 0;
            aConnected = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaConnected"></param>
        public void SyncSetDiscPlayerConnected(String aConnected)
        {
            SyncSetDiscPlayerConnectedLinnCoUkProxyManager1 sync = new SyncSetDiscPlayerConnectedLinnCoUkProxyManager1(this);
            BeginSetDiscPlayerConnected(aConnected, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetDiscPlayerConnected().</remarks>
        /// <param name="aaConnected"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetDiscPlayerConnected(String aConnected, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetDiscPlayerConnected, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetDiscPlayerConnected.InputParameter(inIndex++), aConnected));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetDiscPlayerConnected(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaPort"></param>
        public void SyncDiscPlayerComPort(out uint aPort)
        {
            SyncDiscPlayerComPortLinnCoUkProxyManager1 sync = new SyncDiscPlayerComPortLinnCoUkProxyManager1(this);
            BeginDiscPlayerComPort(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aPort = sync.Port();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDiscPlayerComPort().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDiscPlayerComPort(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDiscPlayerComPort, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionDiscPlayerComPort.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaPort"></param>
        public void EndDiscPlayerComPort(IntPtr aAsyncHandle, out uint aPort)
        {
            uint index = 0;
            aPort = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaConnected"></param>
        public void SyncSetDiscPlayerComPort(uint aConnected)
        {
            SyncSetDiscPlayerComPortLinnCoUkProxyManager1 sync = new SyncSetDiscPlayerComPortLinnCoUkProxyManager1(this);
            BeginSetDiscPlayerComPort(aConnected, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetDiscPlayerComPort().</remarks>
        /// <param name="aaConnected"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetDiscPlayerComPort(uint aConnected, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetDiscPlayerComPort, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetDiscPlayerComPort.InputParameter(inIndex++), aConnected));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetDiscPlayerComPort(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaResult"></param>
        public void SyncTestKontrolProductConnection(out bool aResult)
        {
            SyncTestKontrolProductConnectionLinnCoUkProxyManager1 sync = new SyncTestKontrolProductConnectionLinnCoUkProxyManager1(this);
            BeginTestKontrolProductConnection(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndTestKontrolProductConnection().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginTestKontrolProductConnection(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionTestKontrolProductConnection, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionTestKontrolProductConnection.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaResult"></param>
        public void EndTestKontrolProductConnection(IntPtr aAsyncHandle, out bool aResult)
        {
            uint index = 0;
            aResult = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaResult"></param>
        public void SyncTestDiscPlayerConnection(out bool aResult)
        {
            SyncTestDiscPlayerConnectionLinnCoUkProxyManager1 sync = new SyncTestDiscPlayerConnectionLinnCoUkProxyManager1(this);
            BeginTestDiscPlayerConnection(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndTestDiscPlayerConnection().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginTestDiscPlayerConnection(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionTestDiscPlayerConnection, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionTestDiscPlayerConnection.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaResult"></param>
        public void EndTestDiscPlayerConnection(IntPtr aAsyncHandle, out bool aResult)
        {
            uint index = 0;
            aResult = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the KontrolProductConnected state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProxyManager1 instance will not overlap.</remarks>
        /// <param name="aKontrolProductConnectedChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyKontrolProductConnectedChanged(CallbackPropertyChanged aKontrolProductConnectedChanged)
        {
            lock (iPropertyLock)
            {
                iKontrolProductConnectedChanged = aKontrolProductConnectedChanged;
            }
        }

        private void KontrolProductConnectedPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iKontrolProductConnectedChanged != null)
                {
                    iKontrolProductConnectedChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the KontrolProductComPort state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProxyManager1 instance will not overlap.</remarks>
        /// <param name="aKontrolProductComPortChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyKontrolProductComPortChanged(CallbackPropertyChanged aKontrolProductComPortChanged)
        {
            lock (iPropertyLock)
            {
                iKontrolProductComPortChanged = aKontrolProductComPortChanged;
            }
        }

        private void KontrolProductComPortPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iKontrolProductComPortChanged != null)
                {
                    iKontrolProductComPortChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the DiscPlayerConnected state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProxyManager1 instance will not overlap.</remarks>
        /// <param name="aDiscPlayerConnectedChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDiscPlayerConnectedChanged(CallbackPropertyChanged aDiscPlayerConnectedChanged)
        {
            lock (iPropertyLock)
            {
                iDiscPlayerConnectedChanged = aDiscPlayerConnectedChanged;
            }
        }

        private void DiscPlayerConnectedPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iDiscPlayerConnectedChanged != null)
                {
                    iDiscPlayerConnectedChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the DiscPlayerComPort state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProxyManager1 instance will not overlap.</remarks>
        /// <param name="aDiscPlayerComPortChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDiscPlayerComPortChanged(CallbackPropertyChanged aDiscPlayerComPortChanged)
        {
            lock (iPropertyLock)
            {
                iDiscPlayerComPortChanged = aDiscPlayerComPortChanged;
            }
        }

        private void DiscPlayerComPortPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iDiscPlayerComPortChanged != null)
                {
                    iDiscPlayerComPortChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the KontrolProductConnected property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aKontrolProductConnected">Will be set to the value of the property</param>
        public String PropertyKontrolProductConnected()
        {
            return iKontrolProductConnected.Value();
        }

        /// <summary>
        /// Query the value of the KontrolProductComPort property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aKontrolProductComPort">Will be set to the value of the property</param>
        public uint PropertyKontrolProductComPort()
        {
            return iKontrolProductComPort.Value();
        }

        /// <summary>
        /// Query the value of the DiscPlayerConnected property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDiscPlayerConnected">Will be set to the value of the property</param>
        public String PropertyDiscPlayerConnected()
        {
            return iDiscPlayerConnected.Value();
        }

        /// <summary>
        /// Query the value of the DiscPlayerComPort property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDiscPlayerComPort">Will be set to the value of the property</param>
        public uint PropertyDiscPlayerComPort()
        {
            return iDiscPlayerComPort.Value();
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkProxyManager1()
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
                iActionKontrolProductConnected.Dispose();
                iActionSetKontrolProductConnected.Dispose();
                iActionKontrolProductComPort.Dispose();
                iActionSetKontrolProductComPort.Dispose();
                iActionDiscPlayerConnected.Dispose();
                iActionSetDiscPlayerConnected.Dispose();
                iActionDiscPlayerComPort.Dispose();
                iActionSetDiscPlayerComPort.Dispose();
                iActionTestKontrolProductConnection.Dispose();
                iActionTestDiscPlayerConnection.Dispose();
                iKontrolProductConnected.Dispose();
                iKontrolProductComPort.Dispose();
                iDiscPlayerConnected.Dispose();
                iDiscPlayerComPort.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

