using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyZappOrgTestBasic1 : ICpProxy, IDisposable
    {
        void SyncIncrement(uint aValue, out uint aResult);
        void BeginIncrement(uint aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndIncrement(IntPtr aAsyncHandle, out uint aResult);
        void SyncDecrement(int aValue, out int aResult);
        void BeginDecrement(int aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndDecrement(IntPtr aAsyncHandle, out int aResult);
        void SyncToggle(bool aValue, out bool aResult);
        void BeginToggle(bool aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndToggle(IntPtr aAsyncHandle, out bool aResult);
        void SyncEchoString(String aValue, out String aResult);
        void BeginEchoString(String aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndEchoString(IntPtr aAsyncHandle, out String aResult);
        void SyncEchoBinary(String aValue, out String aResult);
        void BeginEchoBinary(String aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndEchoBinary(IntPtr aAsyncHandle, out String aResult);
        void SyncSetUint(uint aValueUint);
        void BeginSetUint(uint aValueUint, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetUint(IntPtr aAsyncHandle);
        void SyncGetUint(out uint aValueUint);
        void BeginGetUint(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetUint(IntPtr aAsyncHandle, out uint aValueUint);
        void SyncSetInt(int aValueInt);
        void BeginSetInt(int aValueInt, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetInt(IntPtr aAsyncHandle);
        void SyncGetInt(out int aValueInt);
        void BeginGetInt(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetInt(IntPtr aAsyncHandle, out int aValueInt);
        void SyncSetBool(bool aValueBool);
        void BeginSetBool(bool aValueBool, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetBool(IntPtr aAsyncHandle);
        void SyncGetBool(out bool aValueBool);
        void BeginGetBool(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetBool(IntPtr aAsyncHandle, out bool aValueBool);
        void SyncSetMultiple(uint aValueUint, int aValueInt, bool aValueBool);
        void BeginSetMultiple(uint aValueUint, int aValueInt, bool aValueBool, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetMultiple(IntPtr aAsyncHandle);
        void SyncSetString(String aValueStr);
        void BeginSetString(String aValueStr, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetString(IntPtr aAsyncHandle);
        void SyncGetString(out String aValueStr);
        void BeginGetString(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetString(IntPtr aAsyncHandle, out String aValueStr);
        void SyncSetBinary(String aValueBin);
        void BeginSetBinary(String aValueBin, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetBinary(IntPtr aAsyncHandle);
        void SyncGetBinary(out String aValueBin);
        void BeginGetBinary(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetBinary(IntPtr aAsyncHandle, out String aValueBin);
        void SyncToggleBool();
        void BeginToggleBool(CpProxy.CallbackAsyncComplete aCallback);
        void EndToggleBool(IntPtr aAsyncHandle);
        void SyncWriteFile(String aData, String aFileFullName);
        void BeginWriteFile(String aData, String aFileFullName, CpProxy.CallbackAsyncComplete aCallback);
        void EndWriteFile(IntPtr aAsyncHandle);
        void SyncShutdown();
        void BeginShutdown(CpProxy.CallbackAsyncComplete aCallback);
        void EndShutdown(IntPtr aAsyncHandle);
        void SetPropertyVarUintChanged(CpProxy.CallbackPropertyChanged aVarUintChanged);
        uint PropertyVarUint();
        void SetPropertyVarIntChanged(CpProxy.CallbackPropertyChanged aVarIntChanged);
        int PropertyVarInt();
        void SetPropertyVarBoolChanged(CpProxy.CallbackPropertyChanged aVarBoolChanged);
        bool PropertyVarBool();
        void SetPropertyVarStrChanged(CpProxy.CallbackPropertyChanged aVarStrChanged);
        String PropertyVarStr();
        void SetPropertyVarBinChanged(CpProxy.CallbackPropertyChanged aVarBinChanged);
        String PropertyVarBin();
    }

    internal class SyncIncrementZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;
        private uint iResult;

        public SyncIncrementZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public uint Result()
        {
            return iResult;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndIncrement(aAsyncHandle, out iResult);
        }
    };

    internal class SyncDecrementZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;
        private int iResult;

        public SyncDecrementZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public int Result()
        {
            return iResult;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDecrement(aAsyncHandle, out iResult);
        }
    };

    internal class SyncToggleZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;
        private bool iResult;

        public SyncToggleZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public bool Result()
        {
            return iResult;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndToggle(aAsyncHandle, out iResult);
        }
    };

    internal class SyncEchoStringZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;
        private String iResult;

        public SyncEchoStringZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public String Result()
        {
            return iResult;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndEchoString(aAsyncHandle, out iResult);
        }
    };

    internal class SyncEchoBinaryZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;
        private String iResult;

        public SyncEchoBinaryZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public String Result()
        {
            return iResult;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndEchoBinary(aAsyncHandle, out iResult);
        }
    };

    internal class SyncSetUintZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;

        public SyncSetUintZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetUint(aAsyncHandle);
        }
    };

    internal class SyncGetUintZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;
        private uint iValueUint;

        public SyncGetUintZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public uint ValueUint()
        {
            return iValueUint;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetUint(aAsyncHandle, out iValueUint);
        }
    };

    internal class SyncSetIntZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;

        public SyncSetIntZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetInt(aAsyncHandle);
        }
    };

    internal class SyncGetIntZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;
        private int iValueInt;

        public SyncGetIntZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public int ValueInt()
        {
            return iValueInt;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetInt(aAsyncHandle, out iValueInt);
        }
    };

    internal class SyncSetBoolZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;

        public SyncSetBoolZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetBool(aAsyncHandle);
        }
    };

    internal class SyncGetBoolZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;
        private bool iValueBool;

        public SyncGetBoolZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public bool ValueBool()
        {
            return iValueBool;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetBool(aAsyncHandle, out iValueBool);
        }
    };

    internal class SyncSetMultipleZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;

        public SyncSetMultipleZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetMultiple(aAsyncHandle);
        }
    };

    internal class SyncSetStringZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;

        public SyncSetStringZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetString(aAsyncHandle);
        }
    };

    internal class SyncGetStringZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;
        private String iValueStr;

        public SyncGetStringZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public String ValueStr()
        {
            return iValueStr;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetString(aAsyncHandle, out iValueStr);
        }
    };

    internal class SyncSetBinaryZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;

        public SyncSetBinaryZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetBinary(aAsyncHandle);
        }
    };

    internal class SyncGetBinaryZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;
        private String iValueBin;

        public SyncGetBinaryZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public String ValueBin()
        {
            return iValueBin;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetBinary(aAsyncHandle, out iValueBin);
        }
    };

    internal class SyncToggleBoolZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;

        public SyncToggleBoolZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndToggleBool(aAsyncHandle);
        }
    };

    internal class SyncWriteFileZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;

        public SyncWriteFileZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndWriteFile(aAsyncHandle);
        }
    };

    internal class SyncShutdownZappOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyZappOrgTestBasic1 iService;

        public SyncShutdownZappOrgTestBasic1(CpProxyZappOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndShutdown(aAsyncHandle);
        }
    };

    /// <summary>
    /// Proxy for the zapp.org:TestBasic:1 UPnP service
    /// </summary>
    public class CpProxyZappOrgTestBasic1 : CpProxy, IDisposable, ICpProxyZappOrgTestBasic1
    {
        private Zapp.Core.Action iActionIncrement;
        private Zapp.Core.Action iActionDecrement;
        private Zapp.Core.Action iActionToggle;
        private Zapp.Core.Action iActionEchoString;
        private Zapp.Core.Action iActionEchoBinary;
        private Zapp.Core.Action iActionSetUint;
        private Zapp.Core.Action iActionGetUint;
        private Zapp.Core.Action iActionSetInt;
        private Zapp.Core.Action iActionGetInt;
        private Zapp.Core.Action iActionSetBool;
        private Zapp.Core.Action iActionGetBool;
        private Zapp.Core.Action iActionSetMultiple;
        private Zapp.Core.Action iActionSetString;
        private Zapp.Core.Action iActionGetString;
        private Zapp.Core.Action iActionSetBinary;
        private Zapp.Core.Action iActionGetBinary;
        private Zapp.Core.Action iActionToggleBool;
        private Zapp.Core.Action iActionWriteFile;
        private Zapp.Core.Action iActionShutdown;
        private PropertyUint iVarUint;
        private PropertyInt iVarInt;
        private PropertyBool iVarBool;
        private PropertyString iVarStr;
        private PropertyBinary iVarBin;
        private CallbackPropertyChanged iVarUintChanged;
        private CallbackPropertyChanged iVarIntChanged;
        private CallbackPropertyChanged iVarBoolChanged;
        private CallbackPropertyChanged iVarStrChanged;
        private CallbackPropertyChanged iVarBinChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyZappOrgTestBasic1(CpDevice aDevice)
            : base("zapp-org", "TestBasic", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionIncrement = new Zapp.Core.Action("Increment");
            param = new ParameterUint("Value");
            iActionIncrement.AddInputParameter(param);
            param = new ParameterUint("Result");
            iActionIncrement.AddOutputParameter(param);

            iActionDecrement = new Zapp.Core.Action("Decrement");
            param = new ParameterInt("Value");
            iActionDecrement.AddInputParameter(param);
            param = new ParameterInt("Result");
            iActionDecrement.AddOutputParameter(param);

            iActionToggle = new Zapp.Core.Action("Toggle");
            param = new ParameterBool("Value");
            iActionToggle.AddInputParameter(param);
            param = new ParameterBool("Result");
            iActionToggle.AddOutputParameter(param);

            iActionEchoString = new Zapp.Core.Action("EchoString");
            param = new ParameterString("Value", allowedValues);
            iActionEchoString.AddInputParameter(param);
            param = new ParameterString("Result", allowedValues);
            iActionEchoString.AddOutputParameter(param);

            iActionEchoBinary = new Zapp.Core.Action("EchoBinary");
            param = new ParameterBinary("Value");
            iActionEchoBinary.AddInputParameter(param);
            param = new ParameterBinary("Result");
            iActionEchoBinary.AddOutputParameter(param);

            iActionSetUint = new Zapp.Core.Action("SetUint");
            param = new ParameterUint("ValueUint");
            iActionSetUint.AddInputParameter(param);

            iActionGetUint = new Zapp.Core.Action("GetUint");
            param = new ParameterUint("ValueUint");
            iActionGetUint.AddOutputParameter(param);

            iActionSetInt = new Zapp.Core.Action("SetInt");
            param = new ParameterInt("ValueInt");
            iActionSetInt.AddInputParameter(param);

            iActionGetInt = new Zapp.Core.Action("GetInt");
            param = new ParameterInt("ValueInt");
            iActionGetInt.AddOutputParameter(param);

            iActionSetBool = new Zapp.Core.Action("SetBool");
            param = new ParameterBool("ValueBool");
            iActionSetBool.AddInputParameter(param);

            iActionGetBool = new Zapp.Core.Action("GetBool");
            param = new ParameterBool("ValueBool");
            iActionGetBool.AddOutputParameter(param);

            iActionSetMultiple = new Zapp.Core.Action("SetMultiple");
            param = new ParameterUint("ValueUint");
            iActionSetMultiple.AddInputParameter(param);
            param = new ParameterInt("ValueInt");
            iActionSetMultiple.AddInputParameter(param);
            param = new ParameterBool("ValueBool");
            iActionSetMultiple.AddInputParameter(param);

            iActionSetString = new Zapp.Core.Action("SetString");
            param = new ParameterString("ValueStr", allowedValues);
            iActionSetString.AddInputParameter(param);

            iActionGetString = new Zapp.Core.Action("GetString");
            param = new ParameterString("ValueStr", allowedValues);
            iActionGetString.AddOutputParameter(param);

            iActionSetBinary = new Zapp.Core.Action("SetBinary");
            param = new ParameterBinary("ValueBin");
            iActionSetBinary.AddInputParameter(param);

            iActionGetBinary = new Zapp.Core.Action("GetBinary");
            param = new ParameterBinary("ValueBin");
            iActionGetBinary.AddOutputParameter(param);

            iActionToggleBool = new Zapp.Core.Action("ToggleBool");

            iActionWriteFile = new Zapp.Core.Action("WriteFile");
            param = new ParameterString("Data", allowedValues);
            iActionWriteFile.AddInputParameter(param);
            param = new ParameterString("FileFullName", allowedValues);
            iActionWriteFile.AddInputParameter(param);

            iActionShutdown = new Zapp.Core.Action("Shutdown");

            iVarUint = new PropertyUint("VarUint", VarUintPropertyChanged);
            AddProperty(iVarUint);
            iVarInt = new PropertyInt("VarInt", VarIntPropertyChanged);
            AddProperty(iVarInt);
            iVarBool = new PropertyBool("VarBool", VarBoolPropertyChanged);
            AddProperty(iVarBool);
            iVarStr = new PropertyString("VarStr", VarStrPropertyChanged);
            AddProperty(iVarStr);
            iVarBin = new PropertyBinary("VarBin", VarBinPropertyChanged);
            AddProperty(iVarBin);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        public void SyncIncrement(uint aValue, out uint aResult)
        {
            SyncIncrementZappOrgTestBasic1 sync = new SyncIncrementZappOrgTestBasic1(this);
            BeginIncrement(aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndIncrement().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginIncrement(uint aValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionIncrement, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionIncrement.InputParameter(inIndex++), aValue));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionIncrement.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        public void EndIncrement(IntPtr aAsyncHandle, out uint aResult)
        {
            uint index = 0;
            aResult = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        public void SyncDecrement(int aValue, out int aResult)
        {
            SyncDecrementZappOrgTestBasic1 sync = new SyncDecrementZappOrgTestBasic1(this);
            BeginDecrement(aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDecrement().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDecrement(int aValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDecrement, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionDecrement.InputParameter(inIndex++), aValue));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionDecrement.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        public void EndDecrement(IntPtr aAsyncHandle, out int aResult)
        {
            uint index = 0;
            aResult = Invocation.OutputInt(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        public void SyncToggle(bool aValue, out bool aResult)
        {
            SyncToggleZappOrgTestBasic1 sync = new SyncToggleZappOrgTestBasic1(this);
            BeginToggle(aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndToggle().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginToggle(bool aValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionToggle, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionToggle.InputParameter(inIndex++), aValue));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionToggle.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        public void EndToggle(IntPtr aAsyncHandle, out bool aResult)
        {
            uint index = 0;
            aResult = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        public void SyncEchoString(String aValue, out String aResult)
        {
            SyncEchoStringZappOrgTestBasic1 sync = new SyncEchoStringZappOrgTestBasic1(this);
            BeginEchoString(aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndEchoString().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginEchoString(String aValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionEchoString, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionEchoString.InputParameter(inIndex++), aValue));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionEchoString.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        public void EndEchoString(IntPtr aAsyncHandle, out String aResult)
        {
            uint index = 0;
            aResult = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        public void SyncEchoBinary(String aValue, out String aResult)
        {
            SyncEchoBinaryZappOrgTestBasic1 sync = new SyncEchoBinaryZappOrgTestBasic1(this);
            BeginEchoBinary(aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndEchoBinary().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginEchoBinary(String aValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionEchoBinary, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBinary((ParameterBinary)iActionEchoBinary.InputParameter(inIndex++), aValue));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBinary((ParameterBinary)iActionEchoBinary.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        public void EndEchoBinary(IntPtr aAsyncHandle, out String aResult)
        {
            uint index = 0;
            aResult = Invocation.OutputBinary(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueUint"></param>
        public void SyncSetUint(uint aValueUint)
        {
            SyncSetUintZappOrgTestBasic1 sync = new SyncSetUintZappOrgTestBasic1(this);
            BeginSetUint(aValueUint, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetUint().</remarks>
        /// <param name="aValueUint"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetUint(uint aValueUint, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetUint, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetUint.InputParameter(inIndex++), aValueUint));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetUint(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueUint"></param>
        public void SyncGetUint(out uint aValueUint)
        {
            SyncGetUintZappOrgTestBasic1 sync = new SyncGetUintZappOrgTestBasic1(this);
            BeginGetUint(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValueUint = sync.ValueUint();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetUint().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetUint(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetUint, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetUint.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValueUint"></param>
        public void EndGetUint(IntPtr aAsyncHandle, out uint aValueUint)
        {
            uint index = 0;
            aValueUint = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueInt"></param>
        public void SyncSetInt(int aValueInt)
        {
            SyncSetIntZappOrgTestBasic1 sync = new SyncSetIntZappOrgTestBasic1(this);
            BeginSetInt(aValueInt, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetInt().</remarks>
        /// <param name="aValueInt"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetInt(int aValueInt, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetInt, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionSetInt.InputParameter(inIndex++), aValueInt));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetInt(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueInt"></param>
        public void SyncGetInt(out int aValueInt)
        {
            SyncGetIntZappOrgTestBasic1 sync = new SyncGetIntZappOrgTestBasic1(this);
            BeginGetInt(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValueInt = sync.ValueInt();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetInt().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetInt(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetInt, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionGetInt.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValueInt"></param>
        public void EndGetInt(IntPtr aAsyncHandle, out int aValueInt)
        {
            uint index = 0;
            aValueInt = Invocation.OutputInt(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueBool"></param>
        public void SyncSetBool(bool aValueBool)
        {
            SyncSetBoolZappOrgTestBasic1 sync = new SyncSetBoolZappOrgTestBasic1(this);
            BeginSetBool(aValueBool, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetBool().</remarks>
        /// <param name="aValueBool"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetBool(bool aValueBool, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetBool, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetBool.InputParameter(inIndex++), aValueBool));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetBool(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueBool"></param>
        public void SyncGetBool(out bool aValueBool)
        {
            SyncGetBoolZappOrgTestBasic1 sync = new SyncGetBoolZappOrgTestBasic1(this);
            BeginGetBool(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValueBool = sync.ValueBool();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetBool().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetBool(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetBool, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionGetBool.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValueBool"></param>
        public void EndGetBool(IntPtr aAsyncHandle, out bool aValueBool)
        {
            uint index = 0;
            aValueBool = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueUint"></param>
        /// <param name="aValueInt"></param>
        /// <param name="aValueBool"></param>
        public void SyncSetMultiple(uint aValueUint, int aValueInt, bool aValueBool)
        {
            SyncSetMultipleZappOrgTestBasic1 sync = new SyncSetMultipleZappOrgTestBasic1(this);
            BeginSetMultiple(aValueUint, aValueInt, aValueBool, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetMultiple().</remarks>
        /// <param name="aValueUint"></param>
        /// <param name="aValueInt"></param>
        /// <param name="aValueBool"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetMultiple(uint aValueUint, int aValueInt, bool aValueBool, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetMultiple, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetMultiple.InputParameter(inIndex++), aValueUint));
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionSetMultiple.InputParameter(inIndex++), aValueInt));
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetMultiple.InputParameter(inIndex++), aValueBool));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetMultiple(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueStr"></param>
        public void SyncSetString(String aValueStr)
        {
            SyncSetStringZappOrgTestBasic1 sync = new SyncSetStringZappOrgTestBasic1(this);
            BeginSetString(aValueStr, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetString().</remarks>
        /// <param name="aValueStr"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetString(String aValueStr, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetString, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetString.InputParameter(inIndex++), aValueStr));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetString(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueStr"></param>
        public void SyncGetString(out String aValueStr)
        {
            SyncGetStringZappOrgTestBasic1 sync = new SyncGetStringZappOrgTestBasic1(this);
            BeginGetString(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValueStr = sync.ValueStr();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetString().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetString(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetString, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetString.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValueStr"></param>
        public void EndGetString(IntPtr aAsyncHandle, out String aValueStr)
        {
            uint index = 0;
            aValueStr = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueBin"></param>
        public void SyncSetBinary(String aValueBin)
        {
            SyncSetBinaryZappOrgTestBasic1 sync = new SyncSetBinaryZappOrgTestBasic1(this);
            BeginSetBinary(aValueBin, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetBinary().</remarks>
        /// <param name="aValueBin"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetBinary(String aValueBin, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetBinary, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBinary((ParameterBinary)iActionSetBinary.InputParameter(inIndex++), aValueBin));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetBinary(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueBin"></param>
        public void SyncGetBinary(out String aValueBin)
        {
            SyncGetBinaryZappOrgTestBasic1 sync = new SyncGetBinaryZappOrgTestBasic1(this);
            BeginGetBinary(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValueBin = sync.ValueBin();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetBinary().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetBinary(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetBinary, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBinary((ParameterBinary)iActionGetBinary.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValueBin"></param>
        public void EndGetBinary(IntPtr aAsyncHandle, out String aValueBin)
        {
            uint index = 0;
            aValueBin = Invocation.OutputBinary(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncToggleBool()
        {
            SyncToggleBoolZappOrgTestBasic1 sync = new SyncToggleBoolZappOrgTestBasic1(this);
            BeginToggleBool(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndToggleBool().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginToggleBool(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionToggleBool, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndToggleBool(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aData"></param>
        /// <param name="aFileFullName"></param>
        public void SyncWriteFile(String aData, String aFileFullName)
        {
            SyncWriteFileZappOrgTestBasic1 sync = new SyncWriteFileZappOrgTestBasic1(this);
            BeginWriteFile(aData, aFileFullName, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndWriteFile().</remarks>
        /// <param name="aData"></param>
        /// <param name="aFileFullName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginWriteFile(String aData, String aFileFullName, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionWriteFile, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionWriteFile.InputParameter(inIndex++), aData));
            invocation.AddInput(new ArgumentString((ParameterString)iActionWriteFile.InputParameter(inIndex++), aFileFullName));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndWriteFile(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncShutdown()
        {
            SyncShutdownZappOrgTestBasic1 sync = new SyncShutdownZappOrgTestBasic1(this);
            BeginShutdown(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndShutdown().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginShutdown(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionShutdown, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndShutdown(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Set a delegate to be run when the VarUint state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarUintChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarUintChanged(CallbackPropertyChanged aVarUintChanged)
        {
            lock (this)
            {
                iVarUintChanged = aVarUintChanged;
            }
        }

        private void VarUintPropertyChanged()
        {
            lock (this)
            {
                if (iVarUintChanged != null)
                {
                    iVarUintChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VarInt state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarIntChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarIntChanged(CallbackPropertyChanged aVarIntChanged)
        {
            lock (this)
            {
                iVarIntChanged = aVarIntChanged;
            }
        }

        private void VarIntPropertyChanged()
        {
            lock (this)
            {
                if (iVarIntChanged != null)
                {
                    iVarIntChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VarBool state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarBoolChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarBoolChanged(CallbackPropertyChanged aVarBoolChanged)
        {
            lock (this)
            {
                iVarBoolChanged = aVarBoolChanged;
            }
        }

        private void VarBoolPropertyChanged()
        {
            lock (this)
            {
                if (iVarBoolChanged != null)
                {
                    iVarBoolChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VarStr state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarStrChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarStrChanged(CallbackPropertyChanged aVarStrChanged)
        {
            lock (this)
            {
                iVarStrChanged = aVarStrChanged;
            }
        }

        private void VarStrPropertyChanged()
        {
            lock (this)
            {
                if (iVarStrChanged != null)
                {
                    iVarStrChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VarBin state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarBinChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarBinChanged(CallbackPropertyChanged aVarBinChanged)
        {
            lock (this)
            {
                iVarBinChanged = aVarBinChanged;
            }
        }

        private void VarBinPropertyChanged()
        {
            lock (this)
            {
                if (iVarBinChanged != null)
                {
                    iVarBinChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the VarUint property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aVarUint">Will be set to the value of the property</param>
        public uint PropertyVarUint()
        {
            return iVarUint.Value();
        }

        /// <summary>
        /// Query the value of the VarInt property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aVarInt">Will be set to the value of the property</param>
        public int PropertyVarInt()
        {
            return iVarInt.Value();
        }

        /// <summary>
        /// Query the value of the VarBool property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aVarBool">Will be set to the value of the property</param>
        public bool PropertyVarBool()
        {
            return iVarBool.Value();
        }

        /// <summary>
        /// Query the value of the VarStr property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aVarStr">Will be set to the value of the property</param>
        public String PropertyVarStr()
        {
            return iVarStr.Value();
        }

        /// <summary>
        /// Query the value of the VarBin property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aVarBin">Will be set to the value of the property</param>
        public String PropertyVarBin()
        {
            return iVarBin.Value();
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyZappOrgTestBasic1()
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
                iActionIncrement.Dispose();
                iActionDecrement.Dispose();
                iActionToggle.Dispose();
                iActionEchoString.Dispose();
                iActionEchoBinary.Dispose();
                iActionSetUint.Dispose();
                iActionGetUint.Dispose();
                iActionSetInt.Dispose();
                iActionGetInt.Dispose();
                iActionSetBool.Dispose();
                iActionGetBool.Dispose();
                iActionSetMultiple.Dispose();
                iActionSetString.Dispose();
                iActionGetString.Dispose();
                iActionSetBinary.Dispose();
                iActionGetBinary.Dispose();
                iActionToggleBool.Dispose();
                iActionWriteFile.Dispose();
                iActionShutdown.Dispose();
                iVarUint.Dispose();
                iVarInt.Dispose();
                iVarBool.Dispose();
                iVarStr.Dispose();
                iVarBin.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

