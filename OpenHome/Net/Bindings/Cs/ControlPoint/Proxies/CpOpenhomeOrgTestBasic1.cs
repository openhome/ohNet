using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyOpenhomeOrgTestBasic1 : ICpProxy, IDisposable
    {
        void SyncIncrement(uint aValue, out uint aResult);
        void BeginIncrement(uint aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndIncrement(IntPtr aAsyncHandle, out uint aResult);
        void SyncEchoAllowedRangeUint(uint aValue, out uint aResult);
        void BeginEchoAllowedRangeUint(uint aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndEchoAllowedRangeUint(IntPtr aAsyncHandle, out uint aResult);
        void SyncDecrement(int aValue, out int aResult);
        void BeginDecrement(int aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndDecrement(IntPtr aAsyncHandle, out int aResult);
        void SyncToggle(bool aValue, out bool aResult);
        void BeginToggle(bool aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndToggle(IntPtr aAsyncHandle, out bool aResult);
        void SyncEchoString(String aValue, out String aResult);
        void BeginEchoString(String aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndEchoString(IntPtr aAsyncHandle, out String aResult);
        void SyncEchoAllowedValueString(String aValue, out String aResult);
        void BeginEchoAllowedValueString(String aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndEchoAllowedValueString(IntPtr aAsyncHandle, out String aResult);
        void SyncEchoBinary(byte[] aValue, out byte[] aResult);
        void BeginEchoBinary(byte[] aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndEchoBinary(IntPtr aAsyncHandle, out byte[] aResult);
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
        void SyncGetMultiple(out uint aValueUint, out int aValueInt, out bool aValueBool);
        void BeginGetMultiple(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetMultiple(IntPtr aAsyncHandle, out uint aValueUint, out int aValueInt, out bool aValueBool);
        void SyncSetString(String aValueStr);
        void BeginSetString(String aValueStr, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetString(IntPtr aAsyncHandle);
        void SyncGetString(out String aValueStr);
        void BeginGetString(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetString(IntPtr aAsyncHandle, out String aValueStr);
        void SyncSetBinary(byte[] aValueBin);
        void BeginSetBinary(byte[] aValueBin, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetBinary(IntPtr aAsyncHandle);
        void SyncGetBinary(out byte[] aValueBin);
        void BeginGetBinary(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetBinary(IntPtr aAsyncHandle, out byte[] aValueBin);
        void SyncToggleBool();
        void BeginToggleBool(CpProxy.CallbackAsyncComplete aCallback);
        void EndToggleBool(IntPtr aAsyncHandle);
        void SyncReportError();
        void BeginReportError(CpProxy.CallbackAsyncComplete aCallback);
        void EndReportError(IntPtr aAsyncHandle);
        void SyncWriteFile(String aData, String aFileFullName);
        void BeginWriteFile(String aData, String aFileFullName, CpProxy.CallbackAsyncComplete aCallback);
        void EndWriteFile(IntPtr aAsyncHandle);
        void SyncShutdown();
        void BeginShutdown(CpProxy.CallbackAsyncComplete aCallback);
        void EndShutdown(IntPtr aAsyncHandle);
        void SetPropertyVarUintChanged(System.Action aVarUintChanged);
        uint PropertyVarUint();
        void SetPropertyVarIntChanged(System.Action aVarIntChanged);
        int PropertyVarInt();
        void SetPropertyVarBoolChanged(System.Action aVarBoolChanged);
        bool PropertyVarBool();
        void SetPropertyVarStrChanged(System.Action aVarStrChanged);
        String PropertyVarStr();
        void SetPropertyVarBinChanged(System.Action aVarBinChanged);
        byte[] PropertyVarBin();
    }

    internal class SyncIncrementOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;
        private uint iResult;

        public SyncIncrementOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
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

    internal class SyncEchoAllowedRangeUintOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;
        private uint iResult;

        public SyncEchoAllowedRangeUintOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public uint Result()
        {
            return iResult;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndEchoAllowedRangeUint(aAsyncHandle, out iResult);
        }
    };

    internal class SyncDecrementOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;
        private int iResult;

        public SyncDecrementOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
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

    internal class SyncToggleOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;
        private bool iResult;

        public SyncToggleOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
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

    internal class SyncEchoStringOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;
        private String iResult;

        public SyncEchoStringOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
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

    internal class SyncEchoAllowedValueStringOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;
        private String iResult;

        public SyncEchoAllowedValueStringOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public String Result()
        {
            return iResult;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndEchoAllowedValueString(aAsyncHandle, out iResult);
        }
    };

    internal class SyncEchoBinaryOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;
        private byte[] iResult;

        public SyncEchoBinaryOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public byte[] Result()
        {
            return iResult;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndEchoBinary(aAsyncHandle, out iResult);
        }
    };

    internal class SyncSetUintOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;

        public SyncSetUintOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetUint(aAsyncHandle);
        }
    };

    internal class SyncGetUintOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;
        private uint iValueUint;

        public SyncGetUintOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
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

    internal class SyncSetIntOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;

        public SyncSetIntOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetInt(aAsyncHandle);
        }
    };

    internal class SyncGetIntOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;
        private int iValueInt;

        public SyncGetIntOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
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

    internal class SyncSetBoolOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;

        public SyncSetBoolOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetBool(aAsyncHandle);
        }
    };

    internal class SyncGetBoolOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;
        private bool iValueBool;

        public SyncGetBoolOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
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

    internal class SyncSetMultipleOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;

        public SyncSetMultipleOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetMultiple(aAsyncHandle);
        }
    };

    internal class SyncGetMultipleOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;
        private uint iValueUint;
        private int iValueInt;
        private bool iValueBool;

        public SyncGetMultipleOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public uint ValueUint()
        {
            return iValueUint;
        }
        public int ValueInt()
        {
            return iValueInt;
        }
        public bool ValueBool()
        {
            return iValueBool;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetMultiple(aAsyncHandle, out iValueUint, out iValueInt, out iValueBool);
        }
    };

    internal class SyncSetStringOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;

        public SyncSetStringOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetString(aAsyncHandle);
        }
    };

    internal class SyncGetStringOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;
        private String iValueStr;

        public SyncGetStringOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
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

    internal class SyncSetBinaryOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;

        public SyncSetBinaryOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetBinary(aAsyncHandle);
        }
    };

    internal class SyncGetBinaryOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;
        private byte[] iValueBin;

        public SyncGetBinaryOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        public byte[] ValueBin()
        {
            return iValueBin;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetBinary(aAsyncHandle, out iValueBin);
        }
    };

    internal class SyncToggleBoolOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;

        public SyncToggleBoolOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndToggleBool(aAsyncHandle);
        }
    };

    internal class SyncReportErrorOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;

        public SyncReportErrorOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndReportError(aAsyncHandle);
        }
    };

    internal class SyncWriteFileOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;

        public SyncWriteFileOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndWriteFile(aAsyncHandle);
        }
    };

    internal class SyncShutdownOpenhomeOrgTestBasic1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestBasic1 iService;

        public SyncShutdownOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndShutdown(aAsyncHandle);
        }
    };

    /// <summary>
    /// Proxy for the openhome.org:TestBasic:1 UPnP service
    /// </summary>
    public class CpProxyOpenhomeOrgTestBasic1 : CpProxy, IDisposable, ICpProxyOpenhomeOrgTestBasic1
    {
        private OpenHome.Net.Core.Action iActionIncrement;
        private OpenHome.Net.Core.Action iActionEchoAllowedRangeUint;
        private OpenHome.Net.Core.Action iActionDecrement;
        private OpenHome.Net.Core.Action iActionToggle;
        private OpenHome.Net.Core.Action iActionEchoString;
        private OpenHome.Net.Core.Action iActionEchoAllowedValueString;
        private OpenHome.Net.Core.Action iActionEchoBinary;
        private OpenHome.Net.Core.Action iActionSetUint;
        private OpenHome.Net.Core.Action iActionGetUint;
        private OpenHome.Net.Core.Action iActionSetInt;
        private OpenHome.Net.Core.Action iActionGetInt;
        private OpenHome.Net.Core.Action iActionSetBool;
        private OpenHome.Net.Core.Action iActionGetBool;
        private OpenHome.Net.Core.Action iActionSetMultiple;
        private OpenHome.Net.Core.Action iActionGetMultiple;
        private OpenHome.Net.Core.Action iActionSetString;
        private OpenHome.Net.Core.Action iActionGetString;
        private OpenHome.Net.Core.Action iActionSetBinary;
        private OpenHome.Net.Core.Action iActionGetBinary;
        private OpenHome.Net.Core.Action iActionToggleBool;
        private OpenHome.Net.Core.Action iActionReportError;
        private OpenHome.Net.Core.Action iActionWriteFile;
        private OpenHome.Net.Core.Action iActionShutdown;
        private PropertyUint iVarUint;
        private PropertyInt iVarInt;
        private PropertyBool iVarBool;
        private PropertyString iVarStr;
        private PropertyBinary iVarBin;
        private System.Action iVarUintChanged;
        private System.Action iVarIntChanged;
        private System.Action iVarBoolChanged;
        private System.Action iVarStrChanged;
        private System.Action iVarBinChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyOpenhomeOrgTestBasic1(ICpDevice aDevice)
            : base("openhome-org", "TestBasic", 1, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionIncrement = new OpenHome.Net.Core.Action("Increment");
            param = new ParameterUint("Value");
            iActionIncrement.AddInputParameter(param);
            param = new ParameterUint("Result");
            iActionIncrement.AddOutputParameter(param);

            iActionEchoAllowedRangeUint = new OpenHome.Net.Core.Action("EchoAllowedRangeUint");
            param = new ParameterUint("Value", 10, 20);
            iActionEchoAllowedRangeUint.AddInputParameter(param);
            param = new ParameterUint("Result");
            iActionEchoAllowedRangeUint.AddOutputParameter(param);

            iActionDecrement = new OpenHome.Net.Core.Action("Decrement");
            param = new ParameterInt("Value");
            iActionDecrement.AddInputParameter(param);
            param = new ParameterInt("Result");
            iActionDecrement.AddOutputParameter(param);

            iActionToggle = new OpenHome.Net.Core.Action("Toggle");
            param = new ParameterBool("Value");
            iActionToggle.AddInputParameter(param);
            param = new ParameterBool("Result");
            iActionToggle.AddOutputParameter(param);

            iActionEchoString = new OpenHome.Net.Core.Action("EchoString");
            param = new ParameterString("Value", allowedValues);
            iActionEchoString.AddInputParameter(param);
            param = new ParameterString("Result", allowedValues);
            iActionEchoString.AddOutputParameter(param);

            iActionEchoAllowedValueString = new OpenHome.Net.Core.Action("EchoAllowedValueString");
            allowedValues.Add("One");
            allowedValues.Add("Two");
            allowedValues.Add("Three");
            allowedValues.Add("Four");
            param = new ParameterString("Value", allowedValues);
            iActionEchoAllowedValueString.AddInputParameter(param);
            allowedValues.Clear();
            param = new ParameterString("Result", allowedValues);
            iActionEchoAllowedValueString.AddOutputParameter(param);

            iActionEchoBinary = new OpenHome.Net.Core.Action("EchoBinary");
            param = new ParameterBinary("Value");
            iActionEchoBinary.AddInputParameter(param);
            param = new ParameterBinary("Result");
            iActionEchoBinary.AddOutputParameter(param);

            iActionSetUint = new OpenHome.Net.Core.Action("SetUint");
            param = new ParameterUint("ValueUint");
            iActionSetUint.AddInputParameter(param);

            iActionGetUint = new OpenHome.Net.Core.Action("GetUint");
            param = new ParameterUint("ValueUint");
            iActionGetUint.AddOutputParameter(param);

            iActionSetInt = new OpenHome.Net.Core.Action("SetInt");
            param = new ParameterInt("ValueInt");
            iActionSetInt.AddInputParameter(param);

            iActionGetInt = new OpenHome.Net.Core.Action("GetInt");
            param = new ParameterInt("ValueInt");
            iActionGetInt.AddOutputParameter(param);

            iActionSetBool = new OpenHome.Net.Core.Action("SetBool");
            param = new ParameterBool("ValueBool");
            iActionSetBool.AddInputParameter(param);

            iActionGetBool = new OpenHome.Net.Core.Action("GetBool");
            param = new ParameterBool("ValueBool");
            iActionGetBool.AddOutputParameter(param);

            iActionSetMultiple = new OpenHome.Net.Core.Action("SetMultiple");
            param = new ParameterUint("ValueUint");
            iActionSetMultiple.AddInputParameter(param);
            param = new ParameterInt("ValueInt");
            iActionSetMultiple.AddInputParameter(param);
            param = new ParameterBool("ValueBool");
            iActionSetMultiple.AddInputParameter(param);

            iActionGetMultiple = new OpenHome.Net.Core.Action("GetMultiple");
            param = new ParameterUint("ValueUint");
            iActionGetMultiple.AddOutputParameter(param);
            param = new ParameterInt("ValueInt");
            iActionGetMultiple.AddOutputParameter(param);
            param = new ParameterBool("ValueBool");
            iActionGetMultiple.AddOutputParameter(param);

            iActionSetString = new OpenHome.Net.Core.Action("SetString");
            param = new ParameterString("ValueStr", allowedValues);
            iActionSetString.AddInputParameter(param);

            iActionGetString = new OpenHome.Net.Core.Action("GetString");
            param = new ParameterString("ValueStr", allowedValues);
            iActionGetString.AddOutputParameter(param);

            iActionSetBinary = new OpenHome.Net.Core.Action("SetBinary");
            param = new ParameterBinary("ValueBin");
            iActionSetBinary.AddInputParameter(param);

            iActionGetBinary = new OpenHome.Net.Core.Action("GetBinary");
            param = new ParameterBinary("ValueBin");
            iActionGetBinary.AddOutputParameter(param);

            iActionToggleBool = new OpenHome.Net.Core.Action("ToggleBool");

            iActionReportError = new OpenHome.Net.Core.Action("ReportError");

            iActionWriteFile = new OpenHome.Net.Core.Action("WriteFile");
            param = new ParameterString("Data", allowedValues);
            iActionWriteFile.AddInputParameter(param);
            param = new ParameterString("FileFullName", allowedValues);
            iActionWriteFile.AddInputParameter(param);

            iActionShutdown = new OpenHome.Net.Core.Action("Shutdown");

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
            
            iPropertyLock = new Mutex();
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
            SyncIncrementOpenhomeOrgTestBasic1 sync = new SyncIncrementOpenhomeOrgTestBasic1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
        public void SyncEchoAllowedRangeUint(uint aValue, out uint aResult)
        {
            SyncEchoAllowedRangeUintOpenhomeOrgTestBasic1 sync = new SyncEchoAllowedRangeUintOpenhomeOrgTestBasic1(this);
            BeginEchoAllowedRangeUint(aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndEchoAllowedRangeUint().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginEchoAllowedRangeUint(uint aValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionEchoAllowedRangeUint, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionEchoAllowedRangeUint.InputParameter(inIndex++), aValue));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionEchoAllowedRangeUint.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        public void EndEchoAllowedRangeUint(IntPtr aAsyncHandle, out uint aResult)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            SyncDecrementOpenhomeOrgTestBasic1 sync = new SyncDecrementOpenhomeOrgTestBasic1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            SyncToggleOpenhomeOrgTestBasic1 sync = new SyncToggleOpenhomeOrgTestBasic1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            SyncEchoStringOpenhomeOrgTestBasic1 sync = new SyncEchoStringOpenhomeOrgTestBasic1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
        public void SyncEchoAllowedValueString(String aValue, out String aResult)
        {
            SyncEchoAllowedValueStringOpenhomeOrgTestBasic1 sync = new SyncEchoAllowedValueStringOpenhomeOrgTestBasic1(this);
            BeginEchoAllowedValueString(aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndEchoAllowedValueString().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginEchoAllowedValueString(String aValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionEchoAllowedValueString, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionEchoAllowedValueString.InputParameter(inIndex++), aValue));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionEchoAllowedValueString.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        public void EndEchoAllowedValueString(IntPtr aAsyncHandle, out String aResult)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
        public void SyncEchoBinary(byte[] aValue, out byte[] aResult)
        {
            SyncEchoBinaryOpenhomeOrgTestBasic1 sync = new SyncEchoBinaryOpenhomeOrgTestBasic1(this);
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
        public void BeginEchoBinary(byte[] aValue, CallbackAsyncComplete aCallback)
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
        public void EndEchoBinary(IntPtr aAsyncHandle, out byte[] aResult)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            SyncSetUintOpenhomeOrgTestBasic1 sync = new SyncSetUintOpenhomeOrgTestBasic1(this);
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
        /// <param name="aValueUint"></param>
        public void SyncGetUint(out uint aValueUint)
        {
            SyncGetUintOpenhomeOrgTestBasic1 sync = new SyncGetUintOpenhomeOrgTestBasic1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            SyncSetIntOpenhomeOrgTestBasic1 sync = new SyncSetIntOpenhomeOrgTestBasic1(this);
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
        /// <param name="aValueInt"></param>
        public void SyncGetInt(out int aValueInt)
        {
            SyncGetIntOpenhomeOrgTestBasic1 sync = new SyncGetIntOpenhomeOrgTestBasic1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            SyncSetBoolOpenhomeOrgTestBasic1 sync = new SyncSetBoolOpenhomeOrgTestBasic1(this);
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
        /// <param name="aValueBool"></param>
        public void SyncGetBool(out bool aValueBool)
        {
            SyncGetBoolOpenhomeOrgTestBasic1 sync = new SyncGetBoolOpenhomeOrgTestBasic1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            SyncSetMultipleOpenhomeOrgTestBasic1 sync = new SyncSetMultipleOpenhomeOrgTestBasic1(this);
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
        /// <param name="aValueUint"></param>
        /// <param name="aValueInt"></param>
        /// <param name="aValueBool"></param>
        public void SyncGetMultiple(out uint aValueUint, out int aValueInt, out bool aValueBool)
        {
            SyncGetMultipleOpenhomeOrgTestBasic1 sync = new SyncGetMultipleOpenhomeOrgTestBasic1(this);
            BeginGetMultiple(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValueUint = sync.ValueUint();
            aValueInt = sync.ValueInt();
            aValueBool = sync.ValueBool();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetMultiple().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetMultiple(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetMultiple, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetMultiple.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionGetMultiple.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionGetMultiple.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValueUint"></param>
        /// <param name="aValueInt"></param>
        /// <param name="aValueBool"></param>
        public void EndGetMultiple(IntPtr aAsyncHandle, out uint aValueUint, out int aValueInt, out bool aValueBool)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aValueUint = Invocation.OutputUint(aAsyncHandle, index++);
            aValueInt = Invocation.OutputInt(aAsyncHandle, index++);
            aValueBool = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueStr"></param>
        public void SyncSetString(String aValueStr)
        {
            SyncSetStringOpenhomeOrgTestBasic1 sync = new SyncSetStringOpenhomeOrgTestBasic1(this);
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
        /// <param name="aValueStr"></param>
        public void SyncGetString(out String aValueStr)
        {
            SyncGetStringOpenhomeOrgTestBasic1 sync = new SyncGetStringOpenhomeOrgTestBasic1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aValueStr = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueBin"></param>
        public void SyncSetBinary(byte[] aValueBin)
        {
            SyncSetBinaryOpenhomeOrgTestBasic1 sync = new SyncSetBinaryOpenhomeOrgTestBasic1(this);
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
        public void BeginSetBinary(byte[] aValueBin, CallbackAsyncComplete aCallback)
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
        /// <param name="aValueBin"></param>
        public void SyncGetBinary(out byte[] aValueBin)
        {
            SyncGetBinaryOpenhomeOrgTestBasic1 sync = new SyncGetBinaryOpenhomeOrgTestBasic1(this);
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
        public void EndGetBinary(IntPtr aAsyncHandle, out byte[] aValueBin)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            SyncToggleBoolOpenhomeOrgTestBasic1 sync = new SyncToggleBoolOpenhomeOrgTestBasic1(this);
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
        public void SyncReportError()
        {
            SyncReportErrorOpenhomeOrgTestBasic1 sync = new SyncReportErrorOpenhomeOrgTestBasic1(this);
            BeginReportError(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndReportError().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginReportError(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionReportError, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndReportError(IntPtr aAsyncHandle)
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
        /// <param name="aData"></param>
        /// <param name="aFileFullName"></param>
        public void SyncWriteFile(String aData, String aFileFullName)
        {
            SyncWriteFileOpenhomeOrgTestBasic1 sync = new SyncWriteFileOpenhomeOrgTestBasic1(this);
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
        public void SyncShutdown()
        {
            SyncShutdownOpenhomeOrgTestBasic1 sync = new SyncShutdownOpenhomeOrgTestBasic1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VarUint state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyOpenhomeOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarUintChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarUintChanged(System.Action aVarUintChanged)
        {
            lock (iPropertyLock)
            {
                iVarUintChanged = aVarUintChanged;
            }
        }

        private void VarUintPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iVarUintChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VarInt state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyOpenhomeOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarIntChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarIntChanged(System.Action aVarIntChanged)
        {
            lock (iPropertyLock)
            {
                iVarIntChanged = aVarIntChanged;
            }
        }

        private void VarIntPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iVarIntChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VarBool state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyOpenhomeOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarBoolChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarBoolChanged(System.Action aVarBoolChanged)
        {
            lock (iPropertyLock)
            {
                iVarBoolChanged = aVarBoolChanged;
            }
        }

        private void VarBoolPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iVarBoolChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VarStr state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyOpenhomeOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarStrChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarStrChanged(System.Action aVarStrChanged)
        {
            lock (iPropertyLock)
            {
                iVarStrChanged = aVarStrChanged;
            }
        }

        private void VarStrPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iVarStrChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VarBin state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyOpenhomeOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarBinChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarBinChanged(System.Action aVarBinChanged)
        {
            lock (iPropertyLock)
            {
                iVarBinChanged = aVarBinChanged;
            }
        }

        private void VarBinPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iVarBinChanged);
            }
        }

        /// <summary>
        /// Query the value of the VarUint property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the VarUint property</returns>
        public uint PropertyVarUint()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iVarUint.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the VarInt property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the VarInt property</returns>
        public int PropertyVarInt()
        {
            PropertyReadLock();
            int val;
            try
            {
                val = iVarInt.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the VarBool property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the VarBool property</returns>
        public bool PropertyVarBool()
        {
            PropertyReadLock();
            bool val;
            try
            {
                val = iVarBool.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the VarStr property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the VarStr property</returns>
        public String PropertyVarStr()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iVarStr.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the VarBin property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the VarBin property</returns>
        public byte[] PropertyVarBin()
        {
            PropertyReadLock();
            byte[] val;
            try
            {
                val = iVarBin.Value();
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
            iActionIncrement.Dispose();
            iActionEchoAllowedRangeUint.Dispose();
            iActionDecrement.Dispose();
            iActionToggle.Dispose();
            iActionEchoString.Dispose();
            iActionEchoAllowedValueString.Dispose();
            iActionEchoBinary.Dispose();
            iActionSetUint.Dispose();
            iActionGetUint.Dispose();
            iActionSetInt.Dispose();
            iActionGetInt.Dispose();
            iActionSetBool.Dispose();
            iActionGetBool.Dispose();
            iActionSetMultiple.Dispose();
            iActionGetMultiple.Dispose();
            iActionSetString.Dispose();
            iActionGetString.Dispose();
            iActionSetBinary.Dispose();
            iActionGetBinary.Dispose();
            iActionToggleBool.Dispose();
            iActionReportError.Dispose();
            iActionWriteFile.Dispose();
            iActionShutdown.Dispose();
            iVarUint.Dispose();
            iVarInt.Dispose();
            iVarBool.Dispose();
            iVarStr.Dispose();
            iVarBin.Dispose();
        }
    }
}

