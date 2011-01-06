using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkDiagnostics1 : ICpProxy, IDisposable
    {
        void SyncEcho(String aIn, out String aOut);
        void BeginEcho(String aIn, CpProxy.CallbackAsyncComplete aCallback);
        void EndEcho(IntPtr aAsyncHandle, out String aOut);
        void SyncElfFile(out String aElfFile);
        void BeginElfFile(CpProxy.CallbackAsyncComplete aCallback);
        void EndElfFile(IntPtr aAsyncHandle, out String aElfFile);
        void SyncElfFingerprint(out String aElfFileFingerprint);
        void BeginElfFingerprint(CpProxy.CallbackAsyncComplete aCallback);
        void EndElfFingerprint(IntPtr aAsyncHandle, out String aElfFileFingerprint);
        void SyncCrashDataStatus(out String aCrashDataStatus);
        void BeginCrashDataStatus(CpProxy.CallbackAsyncComplete aCallback);
        void EndCrashDataStatus(IntPtr aAsyncHandle, out String aCrashDataStatus);
        void SyncCrashDataFetch(out String aCrashData);
        void BeginCrashDataFetch(CpProxy.CallbackAsyncComplete aCallback);
        void EndCrashDataFetch(IntPtr aAsyncHandle, out String aCrashData);
        void SyncCrashDataClear();
        void BeginCrashDataClear(CpProxy.CallbackAsyncComplete aCallback);
        void EndCrashDataClear(IntPtr aAsyncHandle);
        void SyncSysLog(out String aSysLog);
        void BeginSysLog(CpProxy.CallbackAsyncComplete aCallback);
        void EndSysLog(IntPtr aAsyncHandle, out String aSysLog);
        void SyncDiagnostic(String aDiagnosticType, out String aDiagnosticInfo);
        void BeginDiagnostic(String aDiagnosticType, CpProxy.CallbackAsyncComplete aCallback);
        void EndDiagnostic(IntPtr aAsyncHandle, out String aDiagnosticInfo);
        void SyncStateVariable(out uint aStateVariable);
        void BeginStateVariable(CpProxy.CallbackAsyncComplete aCallback);
        void EndStateVariable(IntPtr aAsyncHandle, out uint aStateVariable);
        void SyncSetStateVariable(uint aStateVariable);
        void BeginSetStateVariable(uint aStateVariable, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStateVariable(IntPtr aAsyncHandle);
        void SyncStateVariablePeriod(out uint aPeriod);
        void BeginStateVariablePeriod(CpProxy.CallbackAsyncComplete aCallback);
        void EndStateVariablePeriod(IntPtr aAsyncHandle, out uint aPeriod);
        void SyncSetStateVariablePeriod(uint aPeriod);
        void BeginSetStateVariablePeriod(uint aPeriod, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStateVariablePeriod(IntPtr aAsyncHandle);
        void SyncReboot(uint aDelay);
        void BeginReboot(uint aDelay, CpProxy.CallbackAsyncComplete aCallback);
        void EndReboot(IntPtr aAsyncHandle);
        void SetPropertyaStateVariableChanged(CpProxy.CallbackPropertyChanged aaStateVariableChanged);
        uint PropertyaStateVariable();
    }

    internal class SyncEchoLinnCoUkDiagnostics1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDiagnostics1 iService;
        private String iOut;

        public SyncEchoLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1 aProxy)
        {
            iService = aProxy;
        }
        public String Out()
        {
            return iOut;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndEcho(aAsyncHandle, out iOut);
        }
    };

    internal class SyncElfFileLinnCoUkDiagnostics1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDiagnostics1 iService;
        private String iElfFile;

        public SyncElfFileLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1 aProxy)
        {
            iService = aProxy;
        }
        public String ElfFile()
        {
            return iElfFile;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndElfFile(aAsyncHandle, out iElfFile);
        }
    };

    internal class SyncElfFingerprintLinnCoUkDiagnostics1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDiagnostics1 iService;
        private String iElfFileFingerprint;

        public SyncElfFingerprintLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1 aProxy)
        {
            iService = aProxy;
        }
        public String ElfFileFingerprint()
        {
            return iElfFileFingerprint;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndElfFingerprint(aAsyncHandle, out iElfFileFingerprint);
        }
    };

    internal class SyncCrashDataStatusLinnCoUkDiagnostics1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDiagnostics1 iService;
        private String iCrashDataStatus;

        public SyncCrashDataStatusLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1 aProxy)
        {
            iService = aProxy;
        }
        public String CrashDataStatus()
        {
            return iCrashDataStatus;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndCrashDataStatus(aAsyncHandle, out iCrashDataStatus);
        }
    };

    internal class SyncCrashDataFetchLinnCoUkDiagnostics1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDiagnostics1 iService;
        private String iCrashData;

        public SyncCrashDataFetchLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1 aProxy)
        {
            iService = aProxy;
        }
        public String CrashData()
        {
            return iCrashData;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndCrashDataFetch(aAsyncHandle, out iCrashData);
        }
    };

    internal class SyncCrashDataClearLinnCoUkDiagnostics1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDiagnostics1 iService;

        public SyncCrashDataClearLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndCrashDataClear(aAsyncHandle);
        }
    };

    internal class SyncSysLogLinnCoUkDiagnostics1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDiagnostics1 iService;
        private String iSysLog;

        public SyncSysLogLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1 aProxy)
        {
            iService = aProxy;
        }
        public String SysLog()
        {
            return iSysLog;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSysLog(aAsyncHandle, out iSysLog);
        }
    };

    internal class SyncDiagnosticLinnCoUkDiagnostics1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDiagnostics1 iService;
        private String iDiagnosticInfo;

        public SyncDiagnosticLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1 aProxy)
        {
            iService = aProxy;
        }
        public String DiagnosticInfo()
        {
            return iDiagnosticInfo;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDiagnostic(aAsyncHandle, out iDiagnosticInfo);
        }
    };

    internal class SyncStateVariableLinnCoUkDiagnostics1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDiagnostics1 iService;
        private uint iStateVariable;

        public SyncStateVariableLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1 aProxy)
        {
            iService = aProxy;
        }
        public uint StateVariable()
        {
            return iStateVariable;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStateVariable(aAsyncHandle, out iStateVariable);
        }
    };

    internal class SyncSetStateVariableLinnCoUkDiagnostics1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDiagnostics1 iService;

        public SyncSetStateVariableLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetStateVariable(aAsyncHandle);
        }
    };

    internal class SyncStateVariablePeriodLinnCoUkDiagnostics1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDiagnostics1 iService;
        private uint iPeriod;

        public SyncStateVariablePeriodLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1 aProxy)
        {
            iService = aProxy;
        }
        public uint Period()
        {
            return iPeriod;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStateVariablePeriod(aAsyncHandle, out iPeriod);
        }
    };

    internal class SyncSetStateVariablePeriodLinnCoUkDiagnostics1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDiagnostics1 iService;

        public SyncSetStateVariablePeriodLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetStateVariablePeriod(aAsyncHandle);
        }
    };

    internal class SyncRebootLinnCoUkDiagnostics1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDiagnostics1 iService;

        public SyncRebootLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndReboot(aAsyncHandle);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Diagnostics:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkDiagnostics1 : CpProxy, IDisposable, ICpProxyLinnCoUkDiagnostics1
    {
        private Zapp.Core.Action iActionEcho;
        private Zapp.Core.Action iActionElfFile;
        private Zapp.Core.Action iActionElfFingerprint;
        private Zapp.Core.Action iActionCrashDataStatus;
        private Zapp.Core.Action iActionCrashDataFetch;
        private Zapp.Core.Action iActionCrashDataClear;
        private Zapp.Core.Action iActionSysLog;
        private Zapp.Core.Action iActionDiagnostic;
        private Zapp.Core.Action iActionStateVariable;
        private Zapp.Core.Action iActionSetStateVariable;
        private Zapp.Core.Action iActionStateVariablePeriod;
        private Zapp.Core.Action iActionSetStateVariablePeriod;
        private Zapp.Core.Action iActionReboot;
        private PropertyUint iaStateVariable;
        private CallbackPropertyChanged iaStateVariableChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkDiagnostics1(CpDevice aDevice)
            : base("linn-co-uk", "Diagnostics", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionEcho = new Zapp.Core.Action("Echo");
            param = new ParameterString("aIn", allowedValues);
            iActionEcho.AddInputParameter(param);
            param = new ParameterString("aOut", allowedValues);
            iActionEcho.AddOutputParameter(param);

            iActionElfFile = new Zapp.Core.Action("ElfFile");
            param = new ParameterString("aElfFile", allowedValues);
            iActionElfFile.AddOutputParameter(param);

            iActionElfFingerprint = new Zapp.Core.Action("ElfFingerprint");
            param = new ParameterString("aElfFileFingerprint", allowedValues);
            iActionElfFingerprint.AddOutputParameter(param);

            iActionCrashDataStatus = new Zapp.Core.Action("CrashDataStatus");
            param = new ParameterString("aCrashDataStatus", allowedValues);
            iActionCrashDataStatus.AddOutputParameter(param);

            iActionCrashDataFetch = new Zapp.Core.Action("CrashDataFetch");
            param = new ParameterBinary("aCrashData");
            iActionCrashDataFetch.AddOutputParameter(param);

            iActionCrashDataClear = new Zapp.Core.Action("CrashDataClear");

            iActionSysLog = new Zapp.Core.Action("SysLog");
            param = new ParameterBinary("aSysLog");
            iActionSysLog.AddOutputParameter(param);

            iActionDiagnostic = new Zapp.Core.Action("Diagnostic");
            param = new ParameterString("aDiagnosticType", allowedValues);
            iActionDiagnostic.AddInputParameter(param);
            param = new ParameterString("aDiagnosticInfo", allowedValues);
            iActionDiagnostic.AddOutputParameter(param);

            iActionStateVariable = new Zapp.Core.Action("StateVariable");
            param = new ParameterUint("aStateVariable");
            iActionStateVariable.AddOutputParameter(param);

            iActionSetStateVariable = new Zapp.Core.Action("SetStateVariable");
            param = new ParameterUint("aStateVariable");
            iActionSetStateVariable.AddInputParameter(param);

            iActionStateVariablePeriod = new Zapp.Core.Action("StateVariablePeriod");
            param = new ParameterUint("aPeriod");
            iActionStateVariablePeriod.AddOutputParameter(param);

            iActionSetStateVariablePeriod = new Zapp.Core.Action("SetStateVariablePeriod");
            param = new ParameterUint("aPeriod");
            iActionSetStateVariablePeriod.AddInputParameter(param);

            iActionReboot = new Zapp.Core.Action("Reboot");
            param = new ParameterUint("aDelay");
            iActionReboot.AddInputParameter(param);

            iaStateVariable = new PropertyUint("aStateVariable", aStateVariablePropertyChanged);
            AddProperty(iaStateVariable);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIn"></param>
        /// <param name="aaOut"></param>
        public void SyncEcho(String aIn, out String aOut)
        {
            SyncEchoLinnCoUkDiagnostics1 sync = new SyncEchoLinnCoUkDiagnostics1(this);
            BeginEcho(aIn, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aOut = sync.Out();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndEcho().</remarks>
        /// <param name="aaIn"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginEcho(String aIn, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionEcho, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionEcho.InputParameter(inIndex++), aIn));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionEcho.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaOut"></param>
        public void EndEcho(IntPtr aAsyncHandle, out String aOut)
        {
            uint index = 0;
            aOut = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaElfFile"></param>
        public void SyncElfFile(out String aElfFile)
        {
            SyncElfFileLinnCoUkDiagnostics1 sync = new SyncElfFileLinnCoUkDiagnostics1(this);
            BeginElfFile(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aElfFile = sync.ElfFile();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndElfFile().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginElfFile(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionElfFile, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionElfFile.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaElfFile"></param>
        public void EndElfFile(IntPtr aAsyncHandle, out String aElfFile)
        {
            uint index = 0;
            aElfFile = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaElfFileFingerprint"></param>
        public void SyncElfFingerprint(out String aElfFileFingerprint)
        {
            SyncElfFingerprintLinnCoUkDiagnostics1 sync = new SyncElfFingerprintLinnCoUkDiagnostics1(this);
            BeginElfFingerprint(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aElfFileFingerprint = sync.ElfFileFingerprint();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndElfFingerprint().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginElfFingerprint(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionElfFingerprint, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionElfFingerprint.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaElfFileFingerprint"></param>
        public void EndElfFingerprint(IntPtr aAsyncHandle, out String aElfFileFingerprint)
        {
            uint index = 0;
            aElfFileFingerprint = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCrashDataStatus"></param>
        public void SyncCrashDataStatus(out String aCrashDataStatus)
        {
            SyncCrashDataStatusLinnCoUkDiagnostics1 sync = new SyncCrashDataStatusLinnCoUkDiagnostics1(this);
            BeginCrashDataStatus(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCrashDataStatus = sync.CrashDataStatus();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCrashDataStatus().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginCrashDataStatus(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionCrashDataStatus, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionCrashDataStatus.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaCrashDataStatus"></param>
        public void EndCrashDataStatus(IntPtr aAsyncHandle, out String aCrashDataStatus)
        {
            uint index = 0;
            aCrashDataStatus = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCrashData"></param>
        public void SyncCrashDataFetch(out String aCrashData)
        {
            SyncCrashDataFetchLinnCoUkDiagnostics1 sync = new SyncCrashDataFetchLinnCoUkDiagnostics1(this);
            BeginCrashDataFetch(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCrashData = sync.CrashData();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCrashDataFetch().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginCrashDataFetch(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionCrashDataFetch, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBinary((ParameterBinary)iActionCrashDataFetch.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaCrashData"></param>
        public void EndCrashDataFetch(IntPtr aAsyncHandle, out String aCrashData)
        {
            uint index = 0;
            aCrashData = Invocation.OutputBinary(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncCrashDataClear()
        {
            SyncCrashDataClearLinnCoUkDiagnostics1 sync = new SyncCrashDataClearLinnCoUkDiagnostics1(this);
            BeginCrashDataClear(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCrashDataClear().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginCrashDataClear(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionCrashDataClear, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndCrashDataClear(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSysLog"></param>
        public void SyncSysLog(out String aSysLog)
        {
            SyncSysLogLinnCoUkDiagnostics1 sync = new SyncSysLogLinnCoUkDiagnostics1(this);
            BeginSysLog(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSysLog = sync.SysLog();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSysLog().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSysLog(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSysLog, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBinary((ParameterBinary)iActionSysLog.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSysLog"></param>
        public void EndSysLog(IntPtr aAsyncHandle, out String aSysLog)
        {
            uint index = 0;
            aSysLog = Invocation.OutputBinary(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaDiagnosticType"></param>
        /// <param name="aaDiagnosticInfo"></param>
        public void SyncDiagnostic(String aDiagnosticType, out String aDiagnosticInfo)
        {
            SyncDiagnosticLinnCoUkDiagnostics1 sync = new SyncDiagnosticLinnCoUkDiagnostics1(this);
            BeginDiagnostic(aDiagnosticType, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aDiagnosticInfo = sync.DiagnosticInfo();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDiagnostic().</remarks>
        /// <param name="aaDiagnosticType"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDiagnostic(String aDiagnosticType, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDiagnostic, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionDiagnostic.InputParameter(inIndex++), aDiagnosticType));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionDiagnostic.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaDiagnosticInfo"></param>
        public void EndDiagnostic(IntPtr aAsyncHandle, out String aDiagnosticInfo)
        {
            uint index = 0;
            aDiagnosticInfo = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStateVariable"></param>
        public void SyncStateVariable(out uint aStateVariable)
        {
            SyncStateVariableLinnCoUkDiagnostics1 sync = new SyncStateVariableLinnCoUkDiagnostics1(this);
            BeginStateVariable(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aStateVariable = sync.StateVariable();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStateVariable().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStateVariable(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStateVariable, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionStateVariable.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaStateVariable"></param>
        public void EndStateVariable(IntPtr aAsyncHandle, out uint aStateVariable)
        {
            uint index = 0;
            aStateVariable = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStateVariable"></param>
        public void SyncSetStateVariable(uint aStateVariable)
        {
            SyncSetStateVariableLinnCoUkDiagnostics1 sync = new SyncSetStateVariableLinnCoUkDiagnostics1(this);
            BeginSetStateVariable(aStateVariable, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStateVariable().</remarks>
        /// <param name="aaStateVariable"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetStateVariable(uint aStateVariable, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetStateVariable, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetStateVariable.InputParameter(inIndex++), aStateVariable));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetStateVariable(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaPeriod"></param>
        public void SyncStateVariablePeriod(out uint aPeriod)
        {
            SyncStateVariablePeriodLinnCoUkDiagnostics1 sync = new SyncStateVariablePeriodLinnCoUkDiagnostics1(this);
            BeginStateVariablePeriod(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aPeriod = sync.Period();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStateVariablePeriod().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStateVariablePeriod(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStateVariablePeriod, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionStateVariablePeriod.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaPeriod"></param>
        public void EndStateVariablePeriod(IntPtr aAsyncHandle, out uint aPeriod)
        {
            uint index = 0;
            aPeriod = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaPeriod"></param>
        public void SyncSetStateVariablePeriod(uint aPeriod)
        {
            SyncSetStateVariablePeriodLinnCoUkDiagnostics1 sync = new SyncSetStateVariablePeriodLinnCoUkDiagnostics1(this);
            BeginSetStateVariablePeriod(aPeriod, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStateVariablePeriod().</remarks>
        /// <param name="aaPeriod"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetStateVariablePeriod(uint aPeriod, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetStateVariablePeriod, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetStateVariablePeriod.InputParameter(inIndex++), aPeriod));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetStateVariablePeriod(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaDelay"></param>
        public void SyncReboot(uint aDelay)
        {
            SyncRebootLinnCoUkDiagnostics1 sync = new SyncRebootLinnCoUkDiagnostics1(this);
            BeginReboot(aDelay, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndReboot().</remarks>
        /// <param name="aaDelay"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginReboot(uint aDelay, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionReboot, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionReboot.InputParameter(inIndex++), aDelay));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndReboot(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Set a delegate to be run when the aStateVariable state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDiagnostics1 instance will not overlap.</remarks>
        /// <param name="aaStateVariableChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyaStateVariableChanged(CallbackPropertyChanged aaStateVariableChanged)
        {
            lock (this)
            {
                iaStateVariableChanged = aaStateVariableChanged;
            }
        }

        private void aStateVariablePropertyChanged()
        {
            lock (this)
            {
                if (iaStateVariableChanged != null)
                {
                    iaStateVariableChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the aStateVariable property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aaStateVariable">Will be set to the value of the property</param>
        public uint PropertyaStateVariable()
        {
            return iaStateVariable.Value();
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkDiagnostics1()
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
                iActionEcho.Dispose();
                iActionElfFile.Dispose();
                iActionElfFingerprint.Dispose();
                iActionCrashDataStatus.Dispose();
                iActionCrashDataFetch.Dispose();
                iActionCrashDataClear.Dispose();
                iActionSysLog.Dispose();
                iActionDiagnostic.Dispose();
                iActionStateVariable.Dispose();
                iActionSetStateVariable.Dispose();
                iActionStateVariablePeriod.Dispose();
                iActionSetStateVariablePeriod.Dispose();
                iActionReboot.Dispose();
                iaStateVariable.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

